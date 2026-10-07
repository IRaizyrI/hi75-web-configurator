"""Minimal 8051 disassembler for the saved Hi75 firmware image.

Usage: python dis8051.py firmware.bin START [END | +COUNT]
Prints one instruction per line. Branch targets are absolute addresses.
"""
import sys

REGS = [f"R{i}" for i in range(8)]


def _table():
    t = {}
    # (mnemonic template, length). Placeholders: {d} direct, {d2} second direct,
    # {i} immediate, {i16} imm16, {r} rel, {b} bit, {a11} ajmp, {a16} addr16
    t[0x00] = ("NOP", 1)
    t[0x02] = ("LJMP {a16}", 3)
    t[0x03] = ("RR A", 1)
    t[0x04] = ("INC A", 1)
    t[0x05] = ("INC {d}", 2)
    t[0x06] = ("INC @R0", 1); t[0x07] = ("INC @R1", 1)
    t[0x10] = ("JBC {b},{r}", 3)
    t[0x12] = ("LCALL {a16}", 3)
    t[0x13] = ("RRC A", 1)
    t[0x14] = ("DEC A", 1)
    t[0x15] = ("DEC {d}", 2)
    t[0x16] = ("DEC @R0", 1); t[0x17] = ("DEC @R1", 1)
    t[0x20] = ("JB {b},{r}", 3)
    t[0x22] = ("RET", 1)
    t[0x23] = ("RL A", 1)
    t[0x24] = ("ADD A,{i}", 2)
    t[0x25] = ("ADD A,{d}", 2)
    t[0x26] = ("ADD A,@R0", 1); t[0x27] = ("ADD A,@R1", 1)
    t[0x30] = ("JNB {b},{r}", 3)
    t[0x32] = ("RETI", 1)
    t[0x33] = ("RLC A", 1)
    t[0x34] = ("ADDC A,{i}", 2)
    t[0x35] = ("ADDC A,{d}", 2)
    t[0x36] = ("ADDC A,@R0", 1); t[0x37] = ("ADDC A,@R1", 1)
    t[0x40] = ("JC {r}", 2)
    t[0x42] = ("ORL {d},A", 2)
    t[0x43] = ("ORL {d},{i}", 3)
    t[0x44] = ("ORL A,{i}", 2)
    t[0x45] = ("ORL A,{d}", 2)
    t[0x46] = ("ORL A,@R0", 1); t[0x47] = ("ORL A,@R1", 1)
    t[0x50] = ("JNC {r}", 2)
    t[0x52] = ("ANL {d},A", 2)
    t[0x53] = ("ANL {d},{i}", 3)
    t[0x54] = ("ANL A,{i}", 2)
    t[0x55] = ("ANL A,{d}", 2)
    t[0x56] = ("ANL A,@R0", 1); t[0x57] = ("ANL A,@R1", 1)
    t[0x60] = ("JZ {r}", 2)
    t[0x62] = ("XRL {d},A", 2)
    t[0x63] = ("XRL {d},{i}", 3)
    t[0x64] = ("XRL A,{i}", 2)
    t[0x65] = ("XRL A,{d}", 2)
    t[0x66] = ("XRL A,@R0", 1); t[0x67] = ("XRL A,@R1", 1)
    t[0x70] = ("JNZ {r}", 2)
    t[0x72] = ("ORL C,{b}", 2)
    t[0x73] = ("JMP @A+DPTR", 1)
    t[0x74] = ("MOV A,{i}", 2)
    t[0x75] = ("MOV {d},{i}", 3)
    t[0x76] = ("MOV @R0,{i}", 2); t[0x77] = ("MOV @R1,{i}", 2)
    t[0x80] = ("SJMP {r}", 2)
    t[0x82] = ("ANL C,{b}", 2)
    t[0x83] = ("MOVC A,@A+PC", 1)
    t[0x84] = ("DIV AB", 1)
    t[0x85] = ("MOV {d2},{d}", 3)  # src first in encoding
    t[0x86] = ("MOV {d},@R0", 2); t[0x87] = ("MOV {d},@R1", 2)
    t[0x90] = ("MOV DPTR,{i16}", 3)
    t[0x92] = ("MOV {b},C", 2)
    t[0x93] = ("MOVC A,@A+DPTR", 1)
    t[0x94] = ("SUBB A,{i}", 2)
    t[0x95] = ("SUBB A,{d}", 2)
    t[0x96] = ("SUBB A,@R0", 1); t[0x97] = ("SUBB A,@R1", 1)
    t[0xA0] = ("ORL C,/{b}", 2)
    t[0xA2] = ("MOV C,{b}", 2)
    t[0xA3] = ("INC DPTR", 1)
    t[0xA4] = ("MUL AB", 1)
    t[0xA5] = ("DB 0xA5", 1)
    t[0xA6] = ("MOV @R0,{d}", 2); t[0xA7] = ("MOV @R1,{d}", 2)
    t[0xB0] = ("ANL C,/{b}", 2)
    t[0xB2] = ("CPL {b}", 2)
    t[0xB3] = ("CPL C", 1)
    t[0xB4] = ("CJNE A,{i},{r}", 3)
    t[0xB5] = ("CJNE A,{d},{r}", 3)
    t[0xB6] = ("CJNE @R0,{i},{r}", 3); t[0xB7] = ("CJNE @R1,{i},{r}", 3)
    t[0xC0] = ("PUSH {d}", 2)
    t[0xC2] = ("CLR {b}", 2)
    t[0xC3] = ("CLR C", 1)
    t[0xC4] = ("SWAP A", 1)
    t[0xC5] = ("XCH A,{d}", 2)
    t[0xC6] = ("XCH A,@R0", 1); t[0xC7] = ("XCH A,@R1", 1)
    t[0xD0] = ("POP {d}", 2)
    t[0xD2] = ("SETB {b}", 2)
    t[0xD3] = ("SETB C", 1)
    t[0xD4] = ("DA A", 1)
    t[0xD5] = ("DJNZ {d},{r}", 3)
    t[0xD6] = ("XCHD A,@R0", 1); t[0xD7] = ("XCHD A,@R1", 1)
    t[0xE0] = ("MOVX A,@DPTR", 1)
    t[0xE2] = ("MOVX A,@R0", 1); t[0xE3] = ("MOVX A,@R1", 1)
    t[0xE4] = ("CLR A", 1)
    t[0xE5] = ("MOV A,{d}", 2)
    t[0xE6] = ("MOV A,@R0", 1); t[0xE7] = ("MOV A,@R1", 1)
    t[0xF0] = ("MOVX @DPTR,A", 1)
    t[0xF2] = ("MOVX @R0,A", 1); t[0xF3] = ("MOVX @R1,A", 1)
    t[0xF4] = ("CPL A", 1)
    t[0xF5] = ("MOV {d},A", 2)
    t[0xF6] = ("MOV @R0,A", 1); t[0xF7] = ("MOV @R1,A", 1)
    for n in range(8):
        t[0x01 + n * 0x20] = ("AJMP {a11}", 2)
        t[0x11 + n * 0x20] = ("ACALL {a11}", 2)
        r = REGS[n]
        t[0x08 + n] = (f"INC {r}", 1)
        t[0x18 + n] = (f"DEC {r}", 1)
        t[0x28 + n] = (f"ADD A,{r}", 1)
        t[0x38 + n] = (f"ADDC A,{r}", 1)
        t[0x48 + n] = (f"ORL A,{r}", 1)
        t[0x58 + n] = (f"ANL A,{r}", 1)
        t[0x68 + n] = (f"XRL A,{r}", 1)
        t[0x78 + n] = (f"MOV {r},{{i}}", 2)
        t[0x88 + n] = (f"MOV {{d}},{r}", 2)
        t[0x98 + n] = (f"SUBB A,{r}", 1)
        t[0xA8 + n] = (f"MOV {r},{{d}}", 2)
        t[0xB8 + n] = (f"CJNE {r},{{i}},{{r}}", 3)
        t[0xC8 + n] = (f"XCH A,{r}", 1)
        t[0xD8 + n] = (f"DJNZ {r},{{r}}", 2)
        t[0xE8 + n] = (f"MOV A,{r}", 1)
        t[0xF8 + n] = (f"MOV {r},A", 1)
    return t


TABLE = _table()


def decode(code, pc):
    op = code[pc]
    tmpl, ln = TABLE[op]
    ops = code[pc + 1:pc + ln]
    nxt = pc + ln
    f = {}
    k = 0
    order = []
    # Collect placeholders in order of appearance, except MOV d2,d (0x85) is src,dst.
    import re
    names = re.findall(r"\{(\w+)\}", tmpl)
    if op == 0x85:
        f["d"], f["d2"] = f"0x{ops[0]:02x}", f"0x{ops[1]:02x}"
        return tmpl.format(**f), ln
    for nm in names:
        if nm in ("d", "d2", "b"):
            f[nm] = f"0x{ops[k]:02x}"; k += 1
        elif nm == "i":
            f[nm] = f"#0x{ops[k]:02x}"; k += 1
        elif nm == "i16":
            f[nm] = f"#0x{ops[k] << 8 | ops[k + 1]:04x}"; k += 2
        elif nm == "a16":
            f[nm] = f"0x{ops[k] << 8 | ops[k + 1]:04x}"; k += 2
        elif nm == "a11":
            f[nm] = f"0x{(nxt & 0xF800) | ((op >> 5) << 8) | ops[k]:04x}"; k += 1
        elif nm == "r":
            rel = ops[k] - 256 if ops[k] > 127 else ops[k]
            f[nm] = f"0x{(nxt + rel) & 0xFFFF:04x}"; k += 1
    return tmpl.format(**f), ln


def main():
    code = open(sys.argv[1], "rb").read()
    start = int(sys.argv[2], 0)
    end_arg = sys.argv[3] if len(sys.argv) > 3 else "+40"
    count = int(end_arg[1:], 0) if end_arg.startswith("+") else None
    end = None if count else int(end_arg, 0)
    pc, n = start, 0
    while pc < len(code) and (end is None or pc < end) and (count is None or n < count):
        text, ln = decode(code, pc)
        print(f"{pc:04x}: {code[pc:pc + ln].hex(' '):<9} {text}")
        pc += ln
        n += 1


if __name__ == "__main__":
    main()
