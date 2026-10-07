"""Boot the dumped firmware in emu8051 and inject synthetic key events.

Used to design and verify the knob-rotation patch offline.
"""
import pickle
import sys
from pathlib import Path

from emu8051 import CPU

ROOT = Path(__file__).resolve().parents[2]
FW = ROOT / "backup/dumps/20260919T085231Z/firmware.bin"
CACHE = Path(__file__).with_name(".boot-state.pkl")


def load_code(path=FW):
    code = bytearray(Path(path).read_bytes())
    code[0xA9A8] = 0x22  # skip the millisecond busy-wait used during init
    return code


def booted(code, steps=600_000, cache=True):
    key = hash(bytes(code))
    if cache and CACHE.exists():
        state = pickle.loads(CACHE.read_bytes())
        if state["key"] == key:
            c = CPU(code)
            c.iram[:], c.sfr[:], c.xram[:], c.pc = state["iram"], state["sfr"], state["xram"], state["pc"]
            return c
    c = CPU(code)
    c.run(steps)
    if cache:
        CACHE.write_bytes(pickle.dumps({"key": key, "iram": c.iram, "sfr": c.sfr, "xram": c.xram, "pc": c.pc}))
    return c


def key_event_stub(matrix, press):
    """Same sequence the matrix scan (CODE 0x1E3E / 0x1EFC) uses."""
    col, row = divmod(matrix, 6)
    s = [0xC2 if press else 0xD2, 0x42, 0x90, 0x08, 0xC0, 0x74, 0x01 if press else 0x81, 0xF0,
         0x90, 0x02, 0xE0, 0x74, matrix, 0xF0]
    if press:
        s += [0x12, 0xA9, 0x6B, 0x7D, row, 0x7F, col, 0x12, 0x0F, 0x73]
    else:
        s += [0xC2, 0x73, 0x7D, row, 0x7F, col, 0x12, 0x60, 0x40]
    return bytes(s + [0x22])


def inject(c, matrix, press, at=0xAE00):
    stub = key_event_stub(matrix, press)
    c.code[at:at + len(stub)] = stub
    writes = []
    hook = lambda cpu, a, v: writes.append((a, v))
    c.xram_write_hooks.append(hook)
    pc, sp = c.pc, c.sfr[0x81]
    ok = c.call(at, 300_000)
    c.xram_write_hooks.remove(hook)
    c.pc = pc
    return ok, writes


if __name__ == "__main__":
    c = booted(load_code())
    for m in map(int, sys.argv[1:] or ["9"]):
        ok, w = inject(c, m, True)
        print("press", m, ok, [(hex(a), hex(v)) for a, v in w])
        ok, w = inject(c, m, False)
        print("release", m, ok, [(hex(a), hex(v)) for a, v in w])
