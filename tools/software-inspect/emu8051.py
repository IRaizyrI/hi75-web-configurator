"""Small 8051 emulator for analysing the Hi75 firmware image offline.

Code space is the 64 KB image (firmware.bin is 0x0000-0xEFFF; bootloader is
not needed). SFR reads come from `sfr` (default 0) and can be overridden with
hooks. Nothing here talks to hardware.
"""

PSW, ACC, B, SP, DPL, DPH = 0xD0, 0xE0, 0xF0, 0x81, 0x82, 0x83


class Halt(Exception):
    pass


class CPU:
    def __init__(self, code):
        self.code = bytearray(code) + bytearray(0x10000 - len(code))
        self.iram = bytearray(256)
        self.sfr = bytearray(256)
        self.xram = bytearray(0x10000)
        self.pc = 0
        self.sfr[SP] = 7
        self.steps = 0
        self.sfr_read_hooks = {}
        self.sfr_write_hooks = {}
        self.xram_write_hooks = []
        self.trace = None
        self.breakpoints = {}

    # --- memory helpers ---
    def rd_direct(self, a):
        if a < 0x80:
            return self.iram[a]
        if a in self.sfr_read_hooks:
            return self.sfr_read_hooks[a](self) & 0xFF
        return self.sfr[a]

    def wr_direct(self, a, v):
        v &= 0xFF
        if a < 0x80:
            self.iram[a] = v
        else:
            self.sfr[a] = v
            if a in self.sfr_write_hooks:
                self.sfr_write_hooks[a](self, v)

    def rd_ind(self, a):
        return self.iram[a]

    def wr_ind(self, a, v):
        self.iram[a] = v & 0xFF

    def rd_x(self, a):
        return self.xram[a & 0xFFFF]

    def wr_x(self, a, v):
        a &= 0xFFFF
        self.xram[a] = v & 0xFF
        for hook in self.xram_write_hooks:
            hook(self, a, v & 0xFF)

    @property
    def a(self):
        return self.sfr[ACC]

    @a.setter
    def a(self, v):
        self.sfr[ACC] = v & 0xFF

    def reg_base(self):
        return self.sfr[PSW] & 0x18

    def r(self, n):
        return self.iram[self.reg_base() + n]

    def set_r(self, n, v):
        self.iram[self.reg_base() + n] = v & 0xFF

    def bit_addr(self, b):
        return (0x20 + (b >> 3), b & 7) if b < 0x80 else (b & 0xF8, b & 7)

    def rd_bit(self, b):
        a, n = self.bit_addr(b)
        return (self.rd_direct(a) >> n) & 1

    def wr_bit(self, b, v):
        a, n = self.bit_addr(b)
        cur = self.iram[a] if a < 0x80 else self.sfr[a]
        cur = (cur | (1 << n)) if v else (cur & ~(1 << n))
        self.wr_direct(a, cur)

    @property
    def cy(self):
        return self.sfr[PSW] >> 7

    def set_cy(self, v):
        self.sfr[PSW] = (self.sfr[PSW] & 0x7F) | (0x80 if v else 0)

    def dptr(self):
        return self.sfr[DPH] << 8 | self.sfr[DPL]

    def set_dptr(self, v):
        self.sfr[DPH] = (v >> 8) & 0xFF
        self.sfr[DPL] = v & 0xFF

    def push(self, v):
        self.sfr[SP] = (self.sfr[SP] + 1) & 0xFF
        self.iram[self.sfr[SP]] = v & 0xFF

    def pop(self):
        v = self.iram[self.sfr[SP]]
        self.sfr[SP] = (self.sfr[SP] - 1) & 0xFF
        return v

    def fetch(self):
        v = self.code[self.pc]
        self.pc = (self.pc + 1) & 0xFFFF
        return v

    def rel(self):
        o = self.fetch()
        return o - 256 if o > 127 else o

    # --- arithmetic ---
    def add(self, v, carry=0):
        a = self.a
        res = a + v + carry
        ac = ((a & 0xF) + (v & 0xF) + carry) > 0xF
        ov = (~(a ^ v) & (a ^ res) & 0x80) != 0
        psw = self.sfr[PSW] & ~0xC4
        psw |= (0x80 if res > 0xFF else 0) | (0x40 if ac else 0) | (0x04 if ov else 0)
        self.sfr[PSW] = psw
        self.a = res

    def subb(self, v):
        a, c = self.a, self.cy
        res = a - v - c
        ac = ((a & 0xF) - (v & 0xF) - c) < 0
        ov = ((a ^ v) & (a ^ res) & 0x80) != 0
        psw = self.sfr[PSW] & ~0xC4
        psw |= (0x80 if res < 0 else 0) | (0x40 if ac else 0) | (0x04 if ov else 0)
        self.sfr[PSW] = psw
        self.a = res

    # --- execution ---
    def call(self, addr, max_steps=2_000_000):
        """Run a subroutine at addr until it returns to a sentinel."""
        self.push(0xFF)
        self.push(0xFF)
        sp0 = self.sfr[SP]
        self.pc = addr
        return self.run(max_steps, stop=lambda c: c.pc == 0xFFFF and c.sfr[SP] == (sp0 - 2) & 0xFF)

    def run(self, max_steps, stop=None):
        for _ in range(max_steps):
            if stop and stop(self):
                return True
            if self.pc in self.breakpoints:
                self.breakpoints[self.pc](self)
            self.step()
        return False

    def step(self):
        self.steps += 1
        pc0 = self.pc
        op = self.fetch()
        if self.trace:
            self.trace(self, pc0, op)
        lo = op & 0x0F
        if op & 0x1F == 0x01:  # AJMP
            a = self.fetch()
            self.pc = (self.pc & 0xF800) | ((op >> 5) << 8) | a
            return
        if op & 0x1F == 0x11:  # ACALL
            a = self.fetch()
            self.push(self.pc & 0xFF)
            self.push(self.pc >> 8)
            self.pc = (self.pc & 0xF800) | ((op >> 5) << 8) | a
            return
        # register / indirect operand helpers for the regular 0x?6-0x?F columns
        def src():
            if lo >= 8:
                return self.r(lo - 8)
            if lo in (6, 7):
                return self.rd_ind(self.r(lo - 6))
            raise AssertionError

        def dst(v):
            if lo >= 8:
                self.set_r(lo - 8, v)
            else:
                self.wr_ind(self.r(lo - 6), v)

        hi = op >> 4
        regular = lo >= 6
        if regular:
            if hi == 0x0: dst(src() + 1); return
            if hi == 0x1: dst(src() - 1); return
            if hi == 0x2: self.add(src()); return
            if hi == 0x3: self.add(src(), self.cy); return
            if hi == 0x4: self.a = self.a | src(); return
            if hi == 0x5: self.a = self.a & src(); return
            if hi == 0x6: self.a = self.a ^ src(); return
            if hi == 0x7: dst(self.fetch()); return
            if hi == 0x8: d = self.fetch(); self.wr_direct(d, src()); return
            if hi == 0x9: self.subb(src()); return
            if hi == 0xA:
                if op == 0xA6 or op == 0xA7 or lo >= 8:
                    dst(self.rd_direct(self.fetch())); return
            if hi == 0xB:
                imm = self.fetch(); r = self.rel(); v = src()
                self.set_cy(v < imm)
                if v != imm: self.pc = (self.pc + r) & 0xFFFF
                return
            if hi == 0xC:
                v = src(); dst(self.a); self.a = v; return
            if hi == 0xD:
                if lo >= 8:
                    r = self.rel(); v = (self.r(lo - 8) - 1) & 0xFF; self.set_r(lo - 8, v)
                    if v: self.pc = (self.pc + r) & 0xFFFF
                    return
                # XCHD
                p = self.r(lo - 6); v = self.iram[p]
                self.iram[p] = (v & 0xF0) | (self.a & 0x0F); self.a = (self.a & 0xF0) | (v & 0x0F); return
            if hi == 0xE: self.a = src(); return
            if hi == 0xF: dst(self.a); return
        f = OPS.get(op)
        if f is None:
            raise Halt(f"unimplemented opcode {op:02x} at {pc0:04x}")
        f(self)


def _ops():
    o = {}

    def j(c, t):
        c.pc = t & 0xFFFF

    o[0x00] = lambda c: None
    o[0x02] = lambda c: j(c, c.fetch() << 8 | c.fetch())
    o[0x03] = lambda c: setattr(c, "a", (c.a >> 1) | ((c.a & 1) << 7))
    o[0x04] = lambda c: setattr(c, "a", c.a + 1)
    def inc_d(c): d = c.fetch(); c.wr_direct(d, c.rd_direct(d) + 1)
    o[0x05] = inc_d
    def jbc(c):
        b = c.fetch(); r = c.rel()
        if c.rd_bit(b): c.wr_bit(b, 0); c.pc = (c.pc + r) & 0xFFFF
    o[0x10] = jbc
    def lcall(c):
        t = c.fetch() << 8 | c.fetch(); c.push(c.pc & 0xFF); c.push(c.pc >> 8); c.pc = t
    o[0x12] = lcall
    def rrc(c): cy = c.cy; c.set_cy(c.a & 1); c.a = (c.a >> 1) | (cy << 7)
    o[0x13] = rrc
    o[0x14] = lambda c: setattr(c, "a", c.a - 1)
    def dec_d(c): d = c.fetch(); c.wr_direct(d, c.rd_direct(d) - 1)
    o[0x15] = dec_d
    def jb(c):
        b = c.fetch(); r = c.rel()
        if c.rd_bit(b): c.pc = (c.pc + r) & 0xFFFF
    o[0x20] = jb
    def ret(c): h = c.pop(); l = c.pop(); c.pc = h << 8 | l
    o[0x22] = ret
    o[0x32] = ret
    o[0x23] = lambda c: setattr(c, "a", ((c.a << 1) | (c.a >> 7)) & 0xFF)
    o[0x24] = lambda c: c.add(c.fetch())
    o[0x25] = lambda c: c.add(c.rd_direct(c.fetch()))
    def jnb(c):
        b = c.fetch(); r = c.rel()
        if not c.rd_bit(b): c.pc = (c.pc + r) & 0xFFFF
    o[0x30] = jnb
    def rlc(c): cy = c.cy; c.set_cy(c.a >> 7); c.a = ((c.a << 1) | cy) & 0xFF
    o[0x33] = rlc
    o[0x34] = lambda c: c.add(c.fetch(), c.cy)
    o[0x35] = lambda c: c.add(c.rd_direct(c.fetch()), c.cy)
    def jc(c): r = c.rel(); c.pc = (c.pc + r) & 0xFFFF if c.cy else c.pc
    o[0x40] = jc
    def logic_d_a(f):
        def g(c): d = c.fetch(); c.wr_direct(d, f(c.rd_direct(d), c.a))
        return g
    def logic_d_i(f):
        def g(c): d = c.fetch(); i = c.fetch(); c.wr_direct(d, f(c.rd_direct(d), i))
        return g
    for base, f in ((0x40, lambda x, y: x | y), (0x50, lambda x, y: x & y), (0x60, lambda x, y: x ^ y)):
        o[base + 2] = logic_d_a(f)
        o[base + 3] = logic_d_i(f)
        o[base + 4] = (lambda f: lambda c: setattr(c, "a", f(c.a, c.fetch())))(f)
        o[base + 5] = (lambda f: lambda c: setattr(c, "a", f(c.a, c.rd_direct(c.fetch()))))(f)
    def jnc(c): r = c.rel(); c.pc = c.pc if c.cy else (c.pc + r) & 0xFFFF
    o[0x50] = jnc
    def jz(c): r = c.rel(); c.pc = (c.pc + r) & 0xFFFF if c.a == 0 else c.pc
    o[0x60] = jz
    def jnz(c): r = c.rel(); c.pc = (c.pc + r) & 0xFFFF if c.a != 0 else c.pc
    o[0x70] = jnz
    o[0x72] = lambda c: c.set_cy(c.cy | c.rd_bit(c.fetch()))
    o[0x73] = lambda c: j(c, c.dptr() + c.a)
    o[0x74] = lambda c: setattr(c, "a", c.fetch())
    def mov_d_i(c): d = c.fetch(); c.wr_direct(d, c.fetch())
    o[0x75] = mov_d_i
    def sjmp(c): r = c.rel(); c.pc = (c.pc + r) & 0xFFFF
    o[0x80] = sjmp
    o[0x82] = lambda c: c.set_cy(c.cy & c.rd_bit(c.fetch()))
    o[0x83] = lambda c: setattr(c, "a", c.code[(c.pc + c.a) & 0xFFFF])
    def div(c):
        b = c.sfr[B]
        psw = c.sfr[PSW] & ~0x84
        if b == 0:
            c.sfr[PSW] = psw | 0x04
        else:
            q, r = divmod(c.a, b); c.a = q; c.sfr[B] = r; c.sfr[PSW] = psw
    o[0x84] = div
    def mov_d_d(c): s = c.fetch(); d = c.fetch(); c.wr_direct(d, c.rd_direct(s))
    o[0x85] = mov_d_d
    def mov_dptr(c): c.sfr[DPH] = c.fetch(); c.sfr[DPL] = c.fetch()
    o[0x90] = mov_dptr
    o[0x92] = lambda c: c.wr_bit(c.fetch(), c.cy)
    o[0x93] = lambda c: setattr(c, "a", c.code[(c.dptr() + c.a) & 0xFFFF])
    o[0x94] = lambda c: c.subb(c.fetch())
    o[0x95] = lambda c: c.subb(c.rd_direct(c.fetch()))
    o[0xA0] = lambda c: c.set_cy(c.cy | (1 - c.rd_bit(c.fetch())))
    o[0xA2] = lambda c: c.set_cy(c.rd_bit(c.fetch()))
    o[0xA3] = lambda c: c.set_dptr(c.dptr() + 1)
    def mul(c):
        p = c.a * c.sfr[B]; c.a = p & 0xFF; c.sfr[B] = p >> 8
        c.sfr[PSW] = (c.sfr[PSW] & ~0x84) | (0x04 if p > 0xFF else 0)
    o[0xA4] = mul
    o[0xB0] = lambda c: c.set_cy(c.cy & (1 - c.rd_bit(c.fetch())))
    def cpl_b(c): b = c.fetch(); c.wr_bit(b, 1 - c.rd_bit(b))
    o[0xB2] = cpl_b
    o[0xB3] = lambda c: c.set_cy(1 - c.cy)
    def cjne_a_i(c):
        i = c.fetch(); r = c.rel(); c.set_cy(c.a < i)
        if c.a != i: c.pc = (c.pc + r) & 0xFFFF
    o[0xB4] = cjne_a_i
    def cjne_a_d(c):
        v = c.rd_direct(c.fetch()); r = c.rel(); c.set_cy(c.a < v)
        if c.a != v: c.pc = (c.pc + r) & 0xFFFF
    o[0xB5] = cjne_a_d
    o[0xC0] = lambda c: c.push(c.rd_direct(c.fetch()))
    o[0xC2] = lambda c: c.wr_bit(c.fetch(), 0)
    o[0xC3] = lambda c: c.set_cy(0)
    o[0xC4] = lambda c: setattr(c, "a", ((c.a << 4) | (c.a >> 4)) & 0xFF)
    def xch_d(c): d = c.fetch(); v = c.rd_direct(d); c.wr_direct(d, c.a); c.a = v
    o[0xC5] = xch_d
    def pop_d(c): d = c.fetch(); c.wr_direct(d, c.pop())
    o[0xD0] = pop_d
    o[0xD2] = lambda c: c.wr_bit(c.fetch(), 1)
    o[0xD3] = lambda c: c.set_cy(1)
    def da(c):
        a = c.a
        if (a & 0xF) > 9 or (c.sfr[PSW] & 0x40): a += 6
        if (a >> 4) > 9 or c.cy or a > 0xFF: a += 0x60; c.set_cy(1)
        c.a = a
    o[0xD4] = da
    def djnz_d(c):
        d = c.fetch(); r = c.rel(); v = (c.rd_direct(d) - 1) & 0xFF; c.wr_direct(d, v)
        if v: c.pc = (c.pc + r) & 0xFFFF
    o[0xD5] = djnz_d
    o[0xE0] = lambda c: setattr(c, "a", c.rd_x(c.dptr()))
    o[0xE2] = lambda c: setattr(c, "a", c.rd_x(c.sfr[0xA0] << 8 | c.r(0)))
    o[0xE3] = lambda c: setattr(c, "a", c.rd_x(c.sfr[0xA0] << 8 | c.r(1)))
    o[0xE4] = lambda c: setattr(c, "a", 0)
    o[0xE5] = lambda c: setattr(c, "a", c.rd_direct(c.fetch()))
    o[0xF0] = lambda c: c.wr_x(c.dptr(), c.a)
    o[0xF2] = lambda c: c.wr_x(c.sfr[0xA0] << 8 | c.r(0), c.a)
    o[0xF3] = lambda c: c.wr_x(c.sfr[0xA0] << 8 | c.r(1), c.a)
    o[0xF4] = lambda c: setattr(c, "a", ~c.a)
    o[0xF5] = lambda c: c.wr_direct(c.fetch(), c.a)
    o[0xA5] = lambda c: None
    return o


OPS = _ops()
