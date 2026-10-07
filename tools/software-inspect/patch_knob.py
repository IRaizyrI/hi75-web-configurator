"""Build a firmware image where knob rotation acts as two keymap keys (v2).

Stock behaviour (CODE 0x2594): a knob step sends consumer Vol+/Vol- directly.
Patched behaviour: clockwise presses matrix 75, counter-clockwise matrix 76
(both unused on the Hi75), released after the firmware's existing ~10-tick
hold, so they follow the base/Fn keymaps like any other key.

Usage: python patch_knob.py firmware.bin out.bin
Only touches the application image; the bootloader is never part of it.
"""
import hashlib
import sys
from pathlib import Path

STOCK_SHA256 = None  # filled in from backup/dumps/.../SHA256SUMS at runtime check below
KNOB_VAR = 0x0FF0      # XRAM byte above everything the firmware addresses (max 0x0F69); zeroed at boot
CW, CCW = 75, 76       # matrix 12*6+3 and 12*6+4
CODE_AT = 0xACC0       # inside the zero-filled gap 0xACB9-0xB0F0 after the code


def asm_routines():
    var_hi, var_lo = KNOB_VAR >> 8, KNOB_VAR & 0xFF
    press = [
        0x90, var_hi, var_lo, 0xF0,      # MOV DPTR,#KNOB_VAR ; MOVX @DPTR,A
        0xFF,                            # MOV R7,A
        0xC2, 0x42,                      # CLR 0x42            (press)
        0x90, 0x08, 0xC0, 0x74, 0x01, 0xF0,  # [0x08C0] = 1
        0x90, 0x02, 0xE0, 0xEF, 0xF0,    # [0x02E0] = matrix
        0x12, 0xA9, 0x6B,                # LCALL 0xA96B        (activity timers)
        0x90, 0x02, 0xE0, 0xE0, 0x24, 0xB8, 0xFD,  # R5 = matrix - 72 (row)
        0x7F, 0x0C,                      # R7 = column 12
        0x12, 0x0F, 0x73,                # LCALL 0x0F73        (key press handler)
        0x22,
    ]
    release = [
        0x90, var_hi, var_lo, 0xE0,      # A = KNOB_VAR
        0x60, 0x1C,                      # JZ done
        0xFF, 0xE4, 0xF0,                # R7 = A ; KNOB_VAR = 0
        0xD2, 0x42,                      # SETB 0x42           (release)
        0x90, 0x08, 0xC0, 0x74, 0x81, 0xF0,  # [0x08C0] = 0x81
        0x90, 0x02, 0xE0, 0xEF, 0xF0,    # [0x02E0] = matrix
        0xC2, 0x73,                      # CLR 0x73            (not a layer-3 key)
        0xEF, 0x24, 0xB8, 0xFD,          # R5 = matrix - 72
        0x7F, 0x0C,                      # R7 = 12
        0x12, 0x60, 0x40,                # LCALL 0x6040        (key release handler)
        0x22,                            # done: RET
    ]
    # fix JZ offset: from end of JZ (offset 6) to the final RET
    release[5] = len(release) - 1 - 6
    return press, release


def patches():
    press, release = asm_routines()
    press_at = CODE_AT
    release_at = CODE_AT + len(press)
    p_hi, p_lo, r_hi, r_lo = press_at >> 8, press_at & 0xFF, release_at >> 8, release_at & 0xFF
    knob_step = [
        0x74, CCW,             # MOV A,#76
        0x30, 0x2F, 0x02,      # JNB 0x2F,+2   (0x2F set = clockwise; stock sent Vol+)
        0x74, CW,              # MOV A,#75
        0x12, p_hi, p_lo,      # LCALL knob_press
        0xD2, 0x2D,            # SETB 0x2D     (hold timer running)
        0x78, 0x6F, 0x76, 0x00,  # MOV R0,#0x6F ; MOV @R0,#0
        0x80, 0x05,            # SJMP 0x25B6
        0, 0, 0, 0, 0,
    ]
    return [
        # (address, stock bytes, new bytes, purpose)
        (0x259F, "90 09 b8 30 2f 04 74 e9 80 02 74 ea f0 e4 a3 f0 d2 50 d2 2d 78 6f f6",
         knob_step, "knob step: press matrix 75/76 instead of sending Vol+/Vol-"),
        (0x25C9, "90 09 b8 f0 a3 f0 d2 50",
         [0x12, r_hi, r_lo, 0, 0, 0, 0, 0], "hold elapsed: release the knob key"),
        (0x2592, "70 3d", [0x00, 0x00], "v2: don't skip knob steps while the custom-knob-press flag (0x0323) is set"),
        (0x7F32, "60 29", [0x80, 0x29], "counter-clockwise: always use the key path (ignore lighting-knob mode)"),
        (0x7F68, "60 76", [0x80, 0x76], "clockwise: always use the key path (ignore lighting-knob mode)"),
        (CODE_AT, " ".join(["00"] * (len(press) + len(release))), press + release, "new routines in free space"),
    ]


def apply(image):
    out = bytearray(image)
    for addr, stock, new, why in patches():
        stock_b = bytes.fromhex(stock)
        assert len(stock_b) == len(new), (hex(addr), len(stock_b), len(new))
        if out[addr:addr + len(new)] != stock_b:
            raise SystemExit(f"Unexpected bytes at {addr:#06x} ({why}); refusing to patch an unknown image")
        out[addr:addr + len(new)] = bytes(new)
    return out


if __name__ == "__main__":
    src, dst = Path(sys.argv[1]), Path(sys.argv[2])
    image = src.read_bytes()
    out = apply(image)
    dst.write_bytes(out)
    print(f"stock   {hashlib.sha256(image).hexdigest()}")
    print(f"patched {hashlib.sha256(out).hexdigest()}  ({sum(a != b for a, b in zip(image, out))} bytes changed)")
