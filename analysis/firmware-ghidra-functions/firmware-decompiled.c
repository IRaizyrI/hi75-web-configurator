
===== FUN_CODE_0006 CODE:0006 size=4 =====

void FUN_CODE_0006(void)

{
  FADDR = 1;
  return;
}



===== FUN_CODE_0056 CODE:0056 size=13 =====

void FUN_CODE_0056(void)

{
  byte bVar1;
  
  FIFLG = 0xff;
  bVar1 = TCON;
  TCON = bVar1 | 0x87;
  bVar1 = P3;
  P3 = bVar1 | 0x6d;
  bVar1 = DAT_SFR_f8;
  DAT_SFR_f8 = bVar1 | 0x10;
  return;
}



===== FUN_CODE_006e CODE:006e size=142 =====

void FUN_CODE_006e(void)

{
  byte bVar1;
  
  bVar1 = PSW1;
  PSW1 = bVar1 & 0xfe;
  bVar1 = CMOD;
  CMOD = bVar1 | 1;
  bVar1 = PSW1;
  PSW1 = bVar1 & 0xfd;
  bVar1 = CMOD;
  CMOD = bVar1 | 2;
  bVar1 = PSW1;
  PSW1 = bVar1 & 0xfb;
  bVar1 = CMOD;
  CMOD = bVar1 | 4;
  bVar1 = PSW1;
  PSW1 = bVar1 & 0xf7;
  bVar1 = CMOD;
  CMOD = bVar1 | 8;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 & 0xf7;
  bVar1 = CCAP4L;
  CCAP4L = bVar1 | 8;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 & 0xef;
  bVar1 = CCAP4L;
  CCAP4L = bVar1 | 0x10;
  FIFLG_0 = 0;
  FIFLG_1 = 0;
  FIFLG_2 = 0;
  FIFLG_3 = 0;
  FIFLG_4 = 0;
  FIFLG_5 = 0;
  FIFLG_6 = 0;
  FIFLG_7 = 0;
  IT0 = 0;
  IE0 = 0;
  IT1 = 0;
  TF1 = 0;
  RXD = 0;
  INT0 = 0;
  INT1 = 0;
  T1 = 0;
  WR = 0;
  F8_4 = 0;
  P0_5 = 0;
  P0_6 = 0;
  P0_7 = 0;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 1;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 2;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 4;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 8;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 0x10;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 0x20;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 0x40;
  bVar1 = RXCNTH;
  RXCNTH = bVar1 | 0x80;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 | 1;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 | 2;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 | 4;
  bVar1 = RXCNTL;
  RXCNTL = bVar1 | 0x80;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 1;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 4;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 8;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 0x20;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 0x40;
  bVar1 = PSW1;
  PSW1 = bVar1 | 0x10;
  bVar1 = EPCON;
  EPCON = bVar1 | 0x20;
  bVar1 = EPCON;
  EPCON = bVar1 | 0x40;
  bVar1 = EPCON;
  EPCON = bVar1 | 0x80;
  return;
}



===== FUN_CODE_0100 CODE:0100 size=129 =====

void FUN_CODE_0100(void)

{
  DAT_EXTMEM_0f41 = 0x11;
  DAT_EXTMEM_0f42 = 0;
  DAT_EXTMEM_0f1b = uEXTMEM1100;
  DAT_EXTMEM_0f1c = uEXTMEM1101;
  DAT_EXTMEM_0f1d = uEXTMEM1102;
  DAT_EXTMEM_0f1e = uEXTMEM1103;
  DAT_EXTMEM_0f1f = uEXTMEM1104;
  DAT_EXTMEM_0f20 = uEXTMEM1105;
  DAT_EXTMEM_0f21 = uEXTMEM1106;
  DAT_EXTMEM_0f22 = uEXTMEM1107;
  return;
}



===== FUN_CODE_0181 CODE:0181 size=120 =====

char FUN_CODE_0181(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  char param_5)

{
  byte bVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_0f15 = 0;
  DAT_EXTMEM_0f16 = 0;
  DAT_EXTMEM_0f0e = param_3;
  DAT_EXTMEM_0f0f = param_2;
  DAT_EXTMEM_0f10 = param_1;
  DAT_EXTMEM_0f11 = param_4;
  DAT_EXTMEM_0f12 = param_5;
  while (bVar1 = DAT_EXTMEM_0f13 - (((DAT_EXTMEM_0f16 < DAT_EXTMEM_0f14) << 7) >> 7),
        DAT_EXTMEM_0f15 < bVar1) {
    uVar2 = FUN_CODE_41e3(CONCAT11(DAT_EXTMEM_0f15,DAT_EXTMEM_0f16),DAT_EXTMEM_0f10,DAT_EXTMEM_0f0f,
                          DAT_EXTMEM_0f0e,DAT_EXTMEM_0f12,DAT_EXTMEM_0f11 >> 1);
    FUN_CODE_aa4c(uVar2);
    IEN1 = 0;
    DAT_EXTMEM_0f12 = DAT_EXTMEM_0f12 + '\x01';
    if (DAT_EXTMEM_0f12 == '\0') {
      DAT_EXTMEM_0f11 = DAT_EXTMEM_0f11 + 1;
    }
    DAT_EXTMEM_0f16 = DAT_EXTMEM_0f16 + 1;
    if (DAT_EXTMEM_0f16 == 0) {
      DAT_EXTMEM_0f15 = DAT_EXTMEM_0f15 + 1;
    }
  }
  return DAT_EXTMEM_0f15 - bVar1;
}



===== FUN_CODE_0200 CODE:0200 size=727 =====

byte FUN_CODE_0200(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  
  if (DAT_EXTMEM_0f40 == '\x04') {
    DAT_EXTMEM_0f40 = '\0';
    DAT_EXTMEM_0f41 = '\x11';
    DAT_EXTMEM_0f42 = 0;
    pbVar5 = &DAT_EXTMEM_0f34;
    bVar3 = bEXTMEM1100;
  }
  else if (DAT_EXTMEM_0f40 == '\x06') {
    bVar3 = 0;
    pbVar5 = &DAT_EXTMEM_0f40;
  }
  else {
    if (DAT_EXTMEM_0f40 == '\t') {
      bVar3 = DAT_EXTMEM_0f36;
      if (DAT_EXTMEM_0f36 == 0) {
        bVar3 = DAT_EXTMEM_0f37 ^ 6;
      }
      if (bVar3 == 0) {
        DAT_EXTMEM_0f41 = '\x11';
        DAT_EXTMEM_0f42 = 0;
        if ((bEXTMEM1100 == 5) && (cEXTMEM1101 == 'u')) {
          DAT_EXTMEM_0f40 = '\0';
          bVar3 = FUN_CODE_ac53(0);
        }
        else {
          DAT_EXTMEM_0f09 = 0;
          DAT_EXTMEM_0f0a = 0;
          do {
            *(undefined1 *)(DAT_EXTMEM_0f0a + 0x76) = BANK0_R5;
            DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + 1;
            if (DAT_EXTMEM_0f0a == 0) {
              DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + 1;
            }
            bVar3 = DAT_EXTMEM_0f09;
            if (DAT_EXTMEM_0f09 == 0) {
              bVar3 = DAT_EXTMEM_0f0a ^ 8;
            }
          } while (bVar3 != 0);
          DAT_EXTMEM_0389 = DAT_INTMEM_78;
          DAT_EXTMEM_02e2 = DAT_INTMEM_7a;
          DAT_EXTMEM_0d0f = DAT_INTMEM_7b;
          DAT_EXTMEM_038a = DAT_INTMEM_7d;
          DAT_EXTMEM_038b = DAT_INTMEM_7c;
          bVar3 = DAT_INTMEM_7c;
        }
      }
      else {
        cVar2 = ((DAT_EXTMEM_0f37 < 8) << 7) >> 7;
        bVar1 = DAT_EXTMEM_0f36 < (byte)-cVar2;
        bVar3 = DAT_EXTMEM_0f36 + cVar2;
        if (!bVar1) {
          if (DAT_EXTMEM_0f30 < (byte)-(((DAT_EXTMEM_0f31 < 8U - ((bVar1 << 7) >> 7)) << 7) >> 7)) {
            DAT_EXTMEM_0f41 = 0x11;
            DAT_EXTMEM_0f42 = 0;
            DAT_EXTMEM_0f09 = 0;
            DAT_EXTMEM_0f0a = 0;
            do {
              puVar6 = (undefined1 *)CONCAT11(DAT_EXTMEM_0f09 + 0x11,DAT_EXTMEM_0f0a);
              *(undefined1 *)(DAT_EXTMEM_0f0a + 0x76) = BANK0_R5;
              DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + 1;
              if (DAT_EXTMEM_0f0a == 0) {
                DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + 1;
              }
              bVar3 = DAT_EXTMEM_0f09;
              if (DAT_EXTMEM_0f09 == 0) {
                bVar3 = DAT_EXTMEM_0f0a ^ 8;
              }
            } while (bVar3 != 0);
            FUN_CODE_aad9(*puVar6);
            DAT_EXTMEM_0f30 = 0;
            DAT_EXTMEM_0f31 = 8;
            DAT_EXTMEM_0389 = DAT_INTMEM_78;
            DAT_EXTMEM_02e2 = DAT_INTMEM_7a;
            DAT_EXTMEM_0d0f = DAT_INTMEM_7b;
            DAT_EXTMEM_038a = DAT_INTMEM_7d;
            DAT_EXTMEM_038b = DAT_INTMEM_7c;
          }
          DAT_EXTMEM_0f07 = 0;
          DAT_EXTMEM_0f08 = 0;
          do {
            DAT_EXTMEM_0f41 = '\x11';
            DAT_EXTMEM_0f42 = 0;
            DAT_EXTMEM_0f09 = 0;
            DAT_EXTMEM_0f0a = 0;
            do {
              bVar3 = DAT_EXTMEM_0f31 - 8;
              bVar4 = DAT_EXTMEM_0f30 + (-1 - (((7 < DAT_EXTMEM_0f31) << 7) >> 7));
              if (DAT_INTMEM_77 == 8) {
                if (bVar4 < 1U - (((bVar3 < 0x7a) << 7) >> 7)) {
                  *(undefined1 *)
                   CONCAT11((bVar4 - (((0xad < bVar3) << 7) >> 7)) + '\x01',DAT_EXTMEM_0f31 + 0x4a)
                       = *(undefined1 *)
                          CONCAT11(DAT_EXTMEM_0f41 +
                                   (DAT_EXTMEM_0f09 -
                                   ((CARRY1(DAT_EXTMEM_0f42,DAT_EXTMEM_0f0a) << 7) >> 7)),
                                   DAT_EXTMEM_0f42 + DAT_EXTMEM_0f0a);
                }
              }
              else if (bVar4 < 2U - (((bVar3 < 8) << 7) >> 7)) {
                *(undefined1 *)
                 CONCAT11((bVar4 - (((0x45 < bVar3) << 7) >> 7)) + '\t',DAT_EXTMEM_0f31 + 0xb2) =
                     *(undefined1 *)
                      CONCAT11(DAT_EXTMEM_0f41 +
                               (DAT_EXTMEM_0f09 -
                               ((CARRY1(DAT_EXTMEM_0f42,DAT_EXTMEM_0f0a) << 7) >> 7)),
                               DAT_EXTMEM_0f42 + DAT_EXTMEM_0f0a);
              }
              DAT_EXTMEM_0f31 = DAT_EXTMEM_0f31 + 1;
              if (DAT_EXTMEM_0f31 == 0) {
                DAT_EXTMEM_0f30 = DAT_EXTMEM_0f30 + 1;
              }
              DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + 1;
              if (DAT_EXTMEM_0f0a == 0) {
                DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + 1;
              }
              bVar3 = DAT_EXTMEM_0f09;
              if (DAT_EXTMEM_0f09 == 0) {
                bVar3 = DAT_EXTMEM_0f0a ^ 8;
              }
            } while (bVar3 != 0);
            bVar3 = DAT_EXTMEM_0f36 ^ DAT_EXTMEM_0f30;
            if (bVar3 == 0) {
              bVar3 = DAT_EXTMEM_0f37 ^ DAT_EXTMEM_0f31;
            }
            if (bVar3 == 0) {
              bVar4 = DAT_SFR_9b;
              DAT_SFR_9b = bVar4 & 0xf0;
              bVar4 = HADDR;
              HADDR = bVar4 | 4;
              if (DAT_EXTMEM_0317 != 0) {
                DAT_EXTMEM_0f40 = bVar3;
                return DAT_EXTMEM_0317;
              }
              DAT_EXTMEM_0f40 = bVar3;
              if ((DAT_INTMEM_77 != 8) && ((DAT_INTMEM_77 & 0xf0) != 0x80)) {
                _7_2 = 1;
                if (_a_3 == '\0') {
                  DAT_EXTMEM_098e = 0;
                  DAT_EXTMEM_098f = 200;
                }
                else {
                  DAT_EXTMEM_098e = 0xb;
                  DAT_EXTMEM_098f = 0xb8;
                }
                FUN_CODE_0056();
              }
              if (DAT_INTMEM_77 != 0xaa) {
                bVar3 = DAT_INTMEM_77 - 3;
                if (7 < bVar3) {
                  return bVar3;
                }
                    /* WARNING: Could not recover jumptable at 0x0494. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                bVar3 = (*(code *)(CONCAT11((char)((ushort)bVar3 * 3 >> 8) + '\x04',0x95) +
                                  ((ushort)bVar3 * 3 & 0xff)))();
                return bVar3;
              }
              DAT_EXTMEM_08bc = DAT_INTMEM_77;
              DAT_EXTMEM_08bd = DAT_INTMEM_78;
              DAT_EXTMEM_08be = 0;
              _7_4 = 1;
              return 0;
            }
            FUN_CODE_aad9();
            DAT_EXTMEM_0f08 = DAT_EXTMEM_0f08 + 1;
            if (DAT_EXTMEM_0f08 == 0) {
              DAT_EXTMEM_0f07 = DAT_EXTMEM_0f07 + 1;
            }
            cVar2 = ((DAT_EXTMEM_0f08 < 0x40) << 7) >> 7;
            bVar3 = DAT_EXTMEM_0f07 + cVar2;
          } while (DAT_EXTMEM_0f07 < (byte)-cVar2);
        }
      }
      goto LAB_CODE_05e3;
    }
    bVar3 = 0;
    pbVar5 = &DAT_EXTMEM_0f40;
  }
  *pbVar5 = bVar3;
LAB_CODE_05e3:
  bVar4 = DAT_SFR_9b;
  DAT_SFR_9b = bVar4 & 0xf0;
  bVar4 = HADDR;
  HADDR = bVar4 | 4;
  return bVar3;
}



===== FUN_CODE_0f73 CODE:0f73 size=369 =====

void FUN_CODE_0f73(char param_1,byte param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  undefined2 uStack_1;
  
  BANK1_R7 = param_3;
  BANK2_R0 = param_2;
  if (_d_4 == '\0') {
    if (_8_4 == '\x01') {
      if (_8_3 == '\x01') {
        *(undefined1 *)
         CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) = 0;
        if (DAT_EXTMEM_031f != 0) {
          cVar3 = '\0';
          cVar2 = DAT_EXTMEM_0309 * '\x02';
          uStack_1 = (byte *)((ushort)(cVar2 - 0x28) << 8);
          bVar1 = DAT_EXTMEM_02e0;
          FUN_CODE_4392(uStack_1,4);
          FUN_CODE_4345();
          if (((param_1 != '\0' || param_2 != 0) || cVar2 != '\0') || cVar3 != '\0') {
            if (_8_0 != '\0') {
              _8_0 = '\0';
              pcVar4 = (char *)CONCAT11('\r' - (((0xe8 < bVar1) << 7) >> 7),bVar1 + 0x17);
              *pcVar4 = *pcVar4 + '\x01';
            }
            if (*(byte *)CONCAT11('\r' - (((0xe8 < DAT_EXTMEM_02e0) << 7) >> 7),
                                  DAT_EXTMEM_02e0 + 0x17) < DAT_EXTMEM_031f) {
              cVar2 = '\b' - (((0x66 < BANK1_R7) << 7) >> 7);
              uStack_1 = (byte *)CONCAT11(cVar2,BANK1_R7 + 0x99);
              *uStack_1 = *(byte *)CONCAT11(cVar2,BANK1_R7 + 0x99) | (&DAT_CODE_abeb)[BANK2_R0];
              return;
            }
          }
        }
        *(undefined1 *)
         CONCAT11('\r' - (((0xe8 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0x17) = 0;
        cVar2 = '\b' - (((0x66 < BANK1_R7) << 7) >> 7);
        uStack_1 = (byte *)CONCAT11(cVar2,BANK1_R7 + 0x99);
        *uStack_1 = *(byte *)CONCAT11(cVar2,BANK1_R7 + 0x99) & (&DAT_CODE_abe3)[BANK2_R0];
      }
      else {
        *(undefined1 *)
         CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) = 2;
      }
    }
    else {
      *(undefined1 *)
       CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) = 1;
    }
    if ((((((DAT_EXTMEM_02e0 == 0xc) || (DAT_EXTMEM_02e0 == 0x12)) || (DAT_EXTMEM_02e0 == 0x18)) ||
         ((((DAT_EXTMEM_02e0 == 0x1e || (DAT_EXTMEM_02e0 == 0x24)) ||
           ((DAT_EXTMEM_02e0 == 0x2a || ((DAT_EXTMEM_02e0 == 0x30 || (DAT_EXTMEM_02e0 == 0x36))))))
          || (DAT_EXTMEM_02e0 == 0x3c)))) ||
        (((DAT_EXTMEM_02e0 == 0x42 || (DAT_EXTMEM_02e0 == 0x48)) || (DAT_EXTMEM_02e0 == 0x4e)))) &&
       (DAT_EXTMEM_0324 == '\x01')) {
      if (*(char *)CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6)
          == '\x01') {
        *(undefined1 *)
         CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) = 0;
      }
      else {
        *(undefined1 *)
         CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) = 1;
      }
    }
    FUN_CODE_3108();
    FUN_CODE_6ffd();
  }
  return;
}



===== FUN_CODE_1108 CODE:1108 size=1814 =====

byte FUN_CODE_1108(char *param_1)

{
  bool bVar1;
  undefined1 uVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  char cVar8;
  undefined1 *puVar9;
  undefined2 uVar10;
  byte *pbVar11;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0ed6 = 0;
  DAT_EXTMEM_0ed9 = '\0';
  DAT_EXTMEM_0eda = 0;
  DAT_EXTMEM_0edb = 0xff;
  DAT_EXTMEM_0edc = 1;
  if (DAT_EXTMEM_030e == '\0') {
    if (DAT_EXTMEM_0312 == '\0') {
      bVar7 = DAT_EXTMEM_009d * '\x02';
      cVar3 = -((CARRY1(DAT_EXTMEM_009d,DAT_EXTMEM_009d) << 7) >> 7);
      _4_3 = *(byte *)CONCAT11((cVar3 - (((0xbe < bVar7) << 7) >> 7)) + '\x03',bVar7 + 0x41) >> 7;
      DAT_EXTMEM_011c =
           *(byte *)CONCAT11((cVar3 - (((0xbd < bVar7) << 7) >> 7)) + '\x03',bVar7 + 0x42) & 0xf;
      bVar7 = DAT_EXTMEM_009d * '\x02';
      DAT_EXTMEM_0d14 =
           *(byte *)CONCAT11((CARRY1(DAT_EXTMEM_009d,DAT_EXTMEM_009d) - (((0xbe < bVar7) << 7) >> 7)
                             ) + '\x03',bVar7 + 0x41) & 0x1f;
      bVar7 = *(byte *)CONCAT11((CARRY1(DAT_EXTMEM_009d,DAT_EXTMEM_009d) -
                                (((0xbd < bVar7) << 7) >> 7)) + '\x03',bVar7 + 0x42) & 0xf0;
      FUN_CODE_4331(4,0,0,0);
      DAT_EXTMEM_0d98 = bVar7;
    }
    else {
      DAT_EXTMEM_0d14 =
           *(byte *)CONCAT11('\x03' - (((0xa1 < DAT_EXTMEM_009d) << 7) >> 7),DAT_EXTMEM_009d + 0x5e)
      ;
    }
  }
  else {
    _4_3 = DAT_EXTMEM_0311 >> 7;
    DAT_EXTMEM_0d14 = DAT_EXTMEM_030f;
    DAT_EXTMEM_0d98 = DAT_EXTMEM_0310;
    DAT_EXTMEM_011c = DAT_EXTMEM_0311 & 0xf;
  }
  if (DAT_EXTMEM_0d15 == '\0') {
    bVar7 = 0;
LAB_CODE_13fb:
    if (_a_2 == '\x01') {
      _a_2 = '\0';
      DAT_EXTMEM_0ed7 = 0;
      DAT_EXTMEM_0ed8 = (char *)0x0;
      do {
        for (DAT_EXTMEM_0ed2 = 0; (DAT_EXTMEM_0ed2 < 6) << 7 < '\0';
            DAT_EXTMEM_0ed2 = DAT_EXTMEM_0ed2 + 1) {
          IEN1 = 0;
          bVar7 = DAT_EXTMEM_0ed2;
          FUN_CODE_7e03(DAT_EXTMEM_0ed8);
          if (bVar7 == 0) {
            uVar10 = 0x152;
            bVar7 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x12);
            uStack_1 = (byte *)CONCAT11(bVar7 * '\x12' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            bVar6 = DAT_EXTMEM_0ed2;
            FUN_CODE_4392(3);
            bVar7 = (byte)((ushort)*uStack_1 * 4);
            bVar5 = *(byte *)CONCAT11('%' - (((0x19 < bVar6 * '\x03') << 7) >> 7),
                                      bVar6 * '\x03' - 0x1a);
            cVar8 = bVar5 + bVar7;
            cVar3 = (char)((ushort)*uStack_1 * 4 >> 8) - ((CARRY1(bVar5,bVar7) << 7) >> 7);
            uVar10 = 0x59e;
            bVar7 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x24);
            uStack_1 = (byte *)CONCAT11(bVar7 * '$' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            FUN_CODE_4392(DAT_EXTMEM_0ed2,6);
            *uStack_1 = cVar3;
            uStack_1[1] = cVar8;
            uVar10 = 0x153;
            bVar7 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x12);
            pbVar11 = (byte *)CONCAT11(bVar7 * '\x12' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            FUN_CODE_4392(bVar6,3);
            bVar7 = (byte)((ushort)*pbVar11 * 4);
            bVar6 = *(byte *)CONCAT11('%' - (((0x18 < bVar6 * '\x03') << 7) >> 7),
                                      bVar6 * '\x03' - 0x19);
            cVar8 = bVar6 + bVar7;
            cVar3 = (char)((ushort)*pbVar11 * 4 >> 8) - ((CARRY1(bVar6,bVar7) << 7) >> 7);
            uVar10 = 0x5a0;
            bVar7 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x24);
            uStack_1 = (byte *)CONCAT11(bVar7 * '$' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            bVar7 = DAT_EXTMEM_0ed2;
            FUN_CODE_4392(6);
            *uStack_1 = cVar3;
            uStack_1[1] = cVar8;
            uVar10 = 0x154;
            bVar6 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x12);
            pbVar11 = (byte *)CONCAT11(bVar6 * '\x12' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            FUN_CODE_4392(bVar7,3);
            bVar6 = (byte)((ushort)*pbVar11 * 4);
            bVar7 = *(byte *)CONCAT11('%' - (((0x17 < bVar7 * '\x03') << 7) >> 7),
                                      bVar7 * '\x03' - 0x18);
            cVar8 = bVar7 + bVar6;
            cVar3 = (char)((ushort)*pbVar11 * 4 >> 8) - ((CARRY1(bVar7,bVar6) << 7) >> 7);
            uVar10 = 0x5a2;
            bVar7 = DAT_EXTMEM_0ed7;
            FUN_CODE_4392(DAT_EXTMEM_0ed8,0x24);
            uStack_1 = (byte *)CONCAT11(bVar7 * '$' + (char)((ushort)uVar10 >> 8),(char)uVar10);
            FUN_CODE_4392(DAT_EXTMEM_0ed2,6);
            *uStack_1 = cVar3;
            uStack_1[1] = cVar8;
          }
        }
        DAT_EXTMEM_0ed8 = DAT_EXTMEM_0ed8 + '\x01';
        if (DAT_EXTMEM_0ed8 == (char *)0x0) {
          DAT_EXTMEM_0ed7 = DAT_EXTMEM_0ed7 + 1;
        }
        cVar3 = ((DAT_EXTMEM_0ed8 < &BANK2_R5) << 7) >> 7;
        bVar7 = DAT_EXTMEM_0ed7 + cVar3;
      } while (DAT_EXTMEM_0ed7 < (byte)-cVar3);
    }
    bVar6 = DAT_EXTMEM_011c;
    if ((_a_3 == '\0') && (_b_1 == '\0')) {
      if ((_6_3 == '\x01') || (_3_5 == '\0')) {
        if (_7_1 == '\0') {
          if ((&DAT_CODE_9cfe)[DAT_EXTMEM_009d] + 1 <= DAT_EXTMEM_0d98) {
            DAT_EXTMEM_0d98 = (&DAT_CODE_9cfe)[DAT_EXTMEM_009d];
          }
          if ((&DAT_CODE_9d17)[DAT_EXTMEM_009d] + 1 <= DAT_EXTMEM_0d14) {
            DAT_EXTMEM_0d14 = (&DAT_CODE_9d17)[DAT_EXTMEM_009d];
          }
          DAT_EXTMEM_0ecb = DAT_EXTMEM_009d;
          DAT_EXTMEM_0ece = DAT_EXTMEM_0d14;
          DAT_EXTMEM_0ecf = DAT_EXTMEM_0d98;
          if (_3_3 != '\0') {
            DAT_EXTMEM_0ecb = 0;
          }
          if (_d_4 != '\0') {
            DAT_EXTMEM_0ecb = 0;
          }
          if (_b_3 != '\0') {
            DAT_EXTMEM_0ecb = 0;
          }
          if (((((DAT_EXTMEM_0ecb == 4) || (DAT_EXTMEM_0ecb == 7)) || (DAT_EXTMEM_0ecb == 9)) ||
              ((DAT_EXTMEM_0ecb == 0xc || (DAT_EXTMEM_0ecb == 0x2d)))) &&
             (bVar7 = *(byte *)CONCAT11('\x03' - (((100 < DAT_EXTMEM_095f) << 7) >> 7),
                                        DAT_EXTMEM_095f + 0x9b), bVar7 < 0x7e)) {
            DAT_EXTMEM_0edc = 0;
            DAT_EXTMEM_0edb = bVar7;
            *(undefined1 *)
             CONCAT11('\x03' - (((100 < DAT_EXTMEM_095f) << 7) >> 7),DAT_EXTMEM_095f + 0x9b) = 0xff;
            _a_1 = '\x01';
            DAT_EXTMEM_095f = DAT_EXTMEM_095f + 1;
            if (9 < DAT_EXTMEM_095f) {
              DAT_EXTMEM_095f = 0;
            }
            DAT_EXTMEM_0300 = 0;
            DAT_EXTMEM_0301 = 0;
            DAT_EXTMEM_0978 = 0;
          }
          if (((_a_1 == '\x01') || (DAT_EXTMEM_0892 != BANK0_R6)) ||
             ((DAT_EXTMEM_0893 != BANK0_R7 ||
              ((DAT_EXTMEM_09aa != BANK0_R6 || (DAT_EXTMEM_0305 != DAT_EXTMEM_0ecf)))))) {
            _a_1 = '\0';
            if ((DAT_EXTMEM_0892 != BANK0_R6) || (DAT_EXTMEM_0893 != bVar6)) {
              DAT_EXTMEM_0892 = DAT_EXTMEM_0ecb;
              DAT_EXTMEM_0893 = bVar6;
              _4_1 = '\x01';
              _4_2 = '\0';
              FUN_CODE_aac3(0);
              FUN_CODE_ab5a();
            }
            cVar3 = (DAT_EXTMEM_09aa < BANK0_R7) << 7;
            if (((DAT_EXTMEM_09aa != BANK0_R7) || (DAT_EXTMEM_0305 != DAT_EXTMEM_0ecf)) &&
               ((DAT_EXTMEM_0ecb == 1 ||
                ((DAT_EXTMEM_0ecb == 8 ||
                 (cVar3 = (DAT_EXTMEM_0ecb < 0x20) << 7, DAT_EXTMEM_0ecb >= 0x20)))))) {
              _4_1 = '\x01';
            }
            DAT_EXTMEM_09aa = DAT_EXTMEM_0ece;
            DAT_EXTMEM_0305 = DAT_EXTMEM_0ecf;
            cVar8 = FUN_CODE_439e(DAT_EXTMEM_0ecb);
            *param_1 = *param_1 + -1;
            bVar7 = cVar8 - ((char)param_1 - (cVar3 >> 7));
            nop();
            *param_1 = *param_1 + -1;
            _0_1 = _0_1 ^ 1;
            *param_1 = *param_1 + -1;
            if (_4_1 != '\0') {
              _4_1 = '\0';
              _4_2 = '\x01';
              _6_2 = 0;
              _a_5 = 0;
              FUN_CODE_acad(bVar7 >> 4 | bVar7 * '\x10');
            }
            bVar7 = (&DAT_CODE_2cb7)[DAT_EXTMEM_0d98];
            DAT_EXTMEM_08b7 = 0;
            DAT_EXTMEM_08b8 = bVar7;
          }
          else {
            bVar7 = 0;
          }
          if (_4_2 == '\x01') {
            if (DAT_EXTMEM_0892 == 0x20) {
              cVar3 = ((DAT_EXTMEM_0301 < 100) << 7) >> 7;
              bVar7 = DAT_EXTMEM_0300 + cVar3;
              if ((byte)-cVar3 <= DAT_EXTMEM_0300) {
                DAT_EXTMEM_0300 = 0;
                DAT_EXTMEM_0301 = 0;
                bVar7 = FUN_CODE_8c98(0);
              }
            }
            else if (DAT_EXTMEM_0892 == 0x26) {
              if (4 < DAT_EXTMEM_0978) {
                DAT_EXTMEM_0978 = 0;
                DAT_EXTMEM_0d14 = 4;
                FUN_CODE_5c49();
              }
              cVar3 = ((DAT_EXTMEM_0301 == 0) << 7) >> 7;
              bVar7 = DAT_EXTMEM_0300 + cVar3;
              if ((byte)-cVar3 <= DAT_EXTMEM_0300) {
                DAT_EXTMEM_011c = 7;
                DAT_EXTMEM_0d14 = 4;
                if (DAT_EXTMEM_0ec8 == '\0') {
                  FUN_CODE_ab5a();
                  DAT_EXTMEM_009d = DAT_EXTMEM_0e1f;
                  _a_1 = '\x01';
                  _6_3 = '\0';
                }
                FUN_CODE_84c6();
                DAT_EXTMEM_0300 = 0;
                DAT_EXTMEM_0301 = 0;
                return 0;
              }
            }
            else {
              bVar7 = DAT_EXTMEM_0892;
              if ((DAT_EXTMEM_0892 < 0x12) << 7 < '\0') {
                    /* WARNING: Could not recover jumptable at 0x1b3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                bVar7 = (*(code *)((ushort)(DAT_EXTMEM_0892 * '\x03') + 0x1b3d))();
                return bVar7;
              }
            }
          }
        }
        else {
          cVar3 = ((DAT_EXTMEM_0301 < 100) << 7) >> 7;
          bVar7 = DAT_EXTMEM_0300 + cVar3;
          if ((byte)-cVar3 <= DAT_EXTMEM_0300) {
            FUN_CODE_a4b6(bVar7,0xff,0xff,0xff);
            DAT_EXTMEM_0300 = 0;
            DAT_EXTMEM_0301 = 0;
            return 0;
          }
        }
      }
      else {
        cVar3 = ((DAT_EXTMEM_0301 < 100) << 7) >> 7;
        bVar7 = DAT_EXTMEM_0300 + cVar3;
        if ((byte)-cVar3 <= DAT_EXTMEM_0300) {
          FUN_CODE_ab5a(bVar7);
          DAT_EXTMEM_0300 = 0;
          DAT_EXTMEM_0301 = 0;
          return 0;
        }
      }
    }
    return bVar7;
  }
  DAT_EXTMEM_0d15 = DAT_EXTMEM_0d15 + -1;
  DAT_EXTMEM_0eda = (byte)((ushort)DAT_EXTMEM_0895 * 200);
  DAT_EXTMEM_0ed9 = (char)((ushort)DAT_EXTMEM_0895 * 200 >> 8);
  DAT_EXTMEM_0304 =
       *(char **)CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda) << 7) >> 7)) + '\t',
                          DAT_EXTMEM_0eda + 0xba);
  DAT_EXTMEM_0303 = (char *)0x0;
  *(undefined1 *)
   CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda) << 7) >> 7)) + '\t',DAT_EXTMEM_0eda + 0xba
           ) = 0;
  DAT_EXTMEM_0eda = DAT_EXTMEM_0eda + 1;
  if (DAT_EXTMEM_0eda == 0) {
    DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
  }
  pcVar4 = DAT_EXTMEM_0303;
  if (DAT_EXTMEM_0303 == (char *)0x0) {
    pcVar4 = DAT_EXTMEM_0304;
  }
  if (pcVar4 == (char *)0x0) goto LAB_CODE_1253;
  DAT_EXTMEM_0ed7 = 0;
  DAT_EXTMEM_0ed8 = (char *)0x0;
  while (DAT_EXTMEM_0ed7 < 1U - (((DAT_EXTMEM_0ed8 < &DAT_INTMEM_7a) << 7) >> 7)) {
    *(undefined1 *)
     CONCAT11((DAT_EXTMEM_0ed7 - ((((char *)0xad < DAT_EXTMEM_0ed8) << 7) >> 7)) + '\x01',
              DAT_EXTMEM_0ed8 + 'R') = 0;
    DAT_EXTMEM_0ed8 = DAT_EXTMEM_0ed8 + '\x01';
    if (DAT_EXTMEM_0ed8 == (char *)0x0) {
      DAT_EXTMEM_0ed7 = DAT_EXTMEM_0ed7 + 1;
    }
  }
  _a_2 = '\x01';
  _a_3 = '\x01';
  puVar9 = &DAT_EXTMEM_0d9a;
  do {
    *puVar9 = 0;
    puVar9[1] = 0;
LAB_CODE_1253:
    while( true ) {
      pcVar4 = DAT_EXTMEM_0303;
      if (DAT_EXTMEM_0303 == (char *)0x0) {
        pcVar4 = DAT_EXTMEM_0304;
      }
      if (pcVar4 == (char *)0x0) {
        bVar6 = DAT_EXTMEM_0895 + 1;
        bVar7 = DAT_EXTMEM_0895 - 2;
        DAT_EXTMEM_0895 = bVar6;
        if (2 < bVar6) {
          bVar7 = 0;
          DAT_EXTMEM_0895 = 0;
        }
        goto LAB_CODE_13fb;
      }
      DAT_EXTMEM_011d =
           *(undefined1 *)
            CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda) << 7) >> 7)) + '\t',
                     DAT_EXTMEM_0eda + 0xba);
      if (DAT_EXTMEM_0eda == 0xff) {
        DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
      }
      uEXTMEM0000 = *(undefined1 *)
                     CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda + 1) << 7) >> 7)) + '\t',
                              DAT_EXTMEM_0eda + 0xbb);
      if (DAT_EXTMEM_0eda == 0xfe) {
        DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
      }
      DAT_EXTMEM_0e20 =
           *(undefined1 *)
            CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda + 2) << 7) >> 7)) + '\t',
                     DAT_EXTMEM_0eda + 0xbc);
      if (DAT_EXTMEM_0eda == 0xfd) {
        DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
      }
      DAT_EXTMEM_0c4f =
           *(char **)CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda + 3) << 7) >> 7)) + '\t',
                              DAT_EXTMEM_0eda + 0xbd);
      DAT_EXTMEM_0eda = DAT_EXTMEM_0eda + 4;
      if (DAT_EXTMEM_0eda == 0) {
        DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
      }
      DAT_EXTMEM_0ed7 = 0;
      DAT_EXTMEM_0ed8 = (char *)0x0;
      while ((DAT_EXTMEM_0ed7 < (byte)-(((DAT_EXTMEM_0ed8 < DAT_EXTMEM_0c4f) << 7) >> 7)) << 7 <
             '\0') {
        bVar7 = *(byte *)CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda) << 7) >> 7)) + '\t',
                                  DAT_EXTMEM_0eda + 0xba) / 6;
        bVar6 = *(byte *)CONCAT11((DAT_EXTMEM_0ed9 - (((0x45 < DAT_EXTMEM_0eda) << 7) >> 7)) + '\t',
                                  DAT_EXTMEM_0eda + 0xba) % 6;
        if ((bVar7 < 0x15) && (bVar6 < 6)) {
          bVar5 = (byte)((ushort)bVar7 * 0x12);
          puVar9 = (undefined1 *)
                   CONCAT11((char)((ushort)bVar7 * 0x12 >> 8) +
                            ('\x01' - (((0xad < bVar5) << 7) >> 7)),bVar5 + 0x52);
          uVar2 = DAT_EXTMEM_011d;
          FUN_CODE_4392(bVar6,3);
          *puVar9 = uVar2;
          bVar5 = (byte)((ushort)bVar7 * 0x12);
          puVar9 = (undefined1 *)
                   CONCAT11((char)((ushort)bVar7 * 0x12 >> 8) +
                            ('\x01' - (((0xac < bVar5) << 7) >> 7)),bVar5 + 0x53);
          uVar2 = uEXTMEM0000;
          FUN_CODE_4392(bVar6,3);
          *puVar9 = uVar2;
          bVar5 = (byte)((ushort)bVar7 * 0x12);
          puVar9 = (undefined1 *)
                   CONCAT11((char)((ushort)bVar7 * 0x12 >> 8) +
                            ('\x01' - (((0xab < bVar5) << 7) >> 7)),bVar5 + 0x54);
          uVar2 = DAT_EXTMEM_0e20;
          FUN_CODE_4392(bVar6,3);
          *puVar9 = uVar2;
        }
        DAT_EXTMEM_0eda = DAT_EXTMEM_0eda + 1;
        if (DAT_EXTMEM_0eda == 0) {
          DAT_EXTMEM_0ed9 = DAT_EXTMEM_0ed9 + '\x01';
        }
        DAT_EXTMEM_0ed8 = DAT_EXTMEM_0ed8 + '\x01';
        if (DAT_EXTMEM_0ed8 == (char *)0x0) {
          DAT_EXTMEM_0ed7 = DAT_EXTMEM_0ed7 + 1;
        }
      }
      param_1 = DAT_EXTMEM_0c4f;
      if ((DAT_EXTMEM_0303 <
          (char *)(("\"" < DAT_EXTMEM_0c4f) -
                  (((DAT_EXTMEM_0304 < DAT_EXTMEM_0c4f + '\x04') << 7) >> 7))) << 7 < '\0') break;
      bVar1 = DAT_EXTMEM_0304 < DAT_EXTMEM_0c4f + '\x04';
      DAT_EXTMEM_0304 = DAT_EXTMEM_0304 + -(char)(DAT_EXTMEM_0c4f + '\x04');
      DAT_EXTMEM_0303 = DAT_EXTMEM_0303 + -(("\"" < DAT_EXTMEM_0c4f) - ((bVar1 << 7) >> 7));
    }
    puVar9 = &DAT_EXTMEM_0303;
  } while( true );
}



===== FUN_CODE_1ded CODE:1ded size=2041 =====

void FUN_CODE_1ded(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  undefined2 uStack_1;
  
  BANK1_R6 = DAT_EXTMEM_030c;
  if (DAT_EXTMEM_0317 == '\x02') {
    BANK1_R6 = DAT_EXTMEM_030c + 1;
  }
  BANK1_R0 = 0;
  do {
    DAT_INTMEM_22 = *(undefined1 *)CONCAT11('\t' - (((0x6f < BANK1_R0) << 7) >> 7),BANK1_R0 + 0x90);
    DAT_INTMEM_21 = *(undefined1 *)CONCAT11('\t' - (((0x9f < BANK1_R0) << 7) >> 7),BANK1_R0 + 0x60);
    DAT_INTMEM_20 = *(undefined1 *)CONCAT11('\b' - (((0x66 < BANK1_R0) << 7) >> 7),BANK1_R0 + 0x99);
    BANK1_R1 = BANK1_R0 * '\x06';
    bVar1 = _1_0;
    if (_2_0 != 0) {
      bVar1 = _1_0 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_0) << 7) < '\0') {
      if (_2_0 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x61 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9e)) {
          *(undefined1 *)
           CONCAT11(-(((0x61 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9e) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          DAT_EXTMEM_02e0 = BANK1_R1;
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abeb;
          _e_3 = _0_0 & 1;
          FUN_CODE_6040(0,BANK1_R0);
          bVar1 = _2_0;
          if (_1_0 != 0) {
            bVar1 = _2_0 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_0 & 1;
            FUN_CODE_9108(0,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x61 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9e
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9c;
        cVar3 = '\r' - (((99 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((99 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9c
                             )) {
          *(undefined1 *)
           CONCAT11('\r' - (((99 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9c) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          DAT_EXTMEM_02e0 = BANK1_R1;
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe3;
          FUN_CODE_a96b();
          FUN_CODE_0f73(0,BANK1_R0);
          bVar1 = _2_0;
          if (_1_0 != 0) {
            bVar1 = _2_0 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_0 & 1;
            FUN_CODE_9108(0,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((99 < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0x9c);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9e;
        cVar3 = -(((0x61 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    BANK1_R1 = BANK1_R1 + '\x01';
    bVar1 = _1_1;
    if (_2_1 != 0) {
      bVar1 = _1_1 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_1) << 7) < '\0') {
      if (_2_1 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x60 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9f)) {
          *(undefined1 *)
           CONCAT11(-(((0x60 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9f) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abec;
          _e_3 = _0_1 & 1;
          FUN_CODE_6040(1,BANK1_R0);
          bVar1 = _2_1;
          if (_1_1 != 0) {
            bVar1 = _2_1 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_1 & 1;
            FUN_CODE_9108(1,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x60 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9f
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9d;
        cVar3 = '\r' - (((0x62 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((0x62 < BANK1_R0 * '\x06') << 7) >> 7),
                              BANK1_R0 * '\x06' + 0x9d)) {
          *(undefined1 *)
           CONCAT11('\r' - (((0x62 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9d) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe4;
          FUN_CODE_a96b();
          FUN_CODE_0f73(1,BANK1_R0);
          bVar1 = _2_1;
          if (_1_1 != 0) {
            bVar1 = _2_1 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_1 & 1;
            FUN_CODE_9108(1,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((0x62 < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0x9d);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9f;
        cVar3 = -(((0x60 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    BANK1_R1 = BANK1_R1 + '\x01';
    bVar1 = _1_2;
    if (_2_2 != 0) {
      bVar1 = _1_2 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_2) << 7) < '\0') {
      if (_2_2 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x5f < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa0)) {
          *(undefined1 *)
           CONCAT11(-(((0x5f < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa0) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abed;
          _e_3 = _0_2 & 1;
          FUN_CODE_6040(2,BANK1_R0);
          bVar1 = _2_2;
          if (_1_2 != 0) {
            bVar1 = _2_2 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_2 & 1;
            FUN_CODE_9108(2,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x5f < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa0
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9e;
        cVar3 = '\r' - (((0x61 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((0x61 < BANK1_R0 * '\x06') << 7) >> 7),
                              BANK1_R0 * '\x06' + 0x9e)) {
          *(undefined1 *)
           CONCAT11('\r' - (((0x61 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9e) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe5;
          FUN_CODE_a96b();
          FUN_CODE_0f73(2,BANK1_R0);
          bVar1 = _2_2;
          if (_1_2 != 0) {
            bVar1 = _2_2 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_2 & 1;
            FUN_CODE_9108(2,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((0x61 < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0x9e);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa0;
        cVar3 = -(((0x5f < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    BANK1_R1 = BANK1_R1 + '\x01';
    bVar1 = _1_3;
    if (_2_3 != 0) {
      bVar1 = _1_3 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_3) << 7) < '\0') {
      if (_2_3 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x5e < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa1)) {
          *(undefined1 *)
           CONCAT11(-(((0x5e < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa1) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abee;
          _e_3 = _0_3 & 1;
          FUN_CODE_6040(3,BANK1_R0);
          bVar1 = _2_3;
          if (_1_3 != 0) {
            bVar1 = _2_3 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_3 & 1;
            FUN_CODE_9108(3,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x5e < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa1
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0x9f;
        cVar3 = '\r' - (((0x60 < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((0x60 < BANK1_R0 * '\x06') << 7) >> 7),
                              BANK1_R0 * '\x06' + 0x9f)) {
          *(undefined1 *)
           CONCAT11('\r' - (((0x60 < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0x9f) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe6;
          FUN_CODE_a96b();
          FUN_CODE_0f73(3,BANK1_R0);
          bVar1 = _2_3;
          if (_1_3 != 0) {
            bVar1 = _2_3 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_3 & 1;
            FUN_CODE_9108(3,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((0x60 < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0x9f);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa1;
        cVar3 = -(((0x5e < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    BANK1_R1 = BANK1_R1 + '\x01';
    bVar1 = _1_4;
    if (_2_4 != 0) {
      bVar1 = _1_4 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_4) << 7) < '\0') {
      if (_2_4 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x5d < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa2)) {
          *(undefined1 *)
           CONCAT11(-(((0x5d < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa2) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abef;
          _e_3 = _0_4 & 1;
          FUN_CODE_6040(4,BANK1_R0);
          bVar1 = _2_4;
          if (_1_4 != 0) {
            bVar1 = _2_4 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_4 & 1;
            FUN_CODE_9108(4,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x5d < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa2
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa0;
        cVar3 = '\r' - (((0x5f < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((0x5f < BANK1_R0 * '\x06') << 7) >> 7),
                              BANK1_R0 * '\x06' + 0xa0)) {
          *(undefined1 *)
           CONCAT11('\r' - (((0x5f < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa0) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe7;
          FUN_CODE_a96b();
          FUN_CODE_0f73(4,BANK1_R0);
          bVar1 = _2_4;
          if (_1_4 != 0) {
            bVar1 = _2_4 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_4 & 1;
            FUN_CODE_9108(4,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((0x5f < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0xa0);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa2;
        cVar3 = -(((0x5d < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    BANK1_R1 = BANK1_R1 + '\x01';
    bVar1 = _1_5;
    if (_2_5 != 0) {
      bVar1 = _1_5 & 1 ^ 1;
    }
    if ((char)((bVar1 & 1 | _0_5) << 7) < '\0') {
      if (_2_5 == 1) {
        if (BANK1_R6 <=
            *(byte *)CONCAT11(-(((0x5c < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa3)) {
          *(undefined1 *)
           CONCAT11(-(((0x5c < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa3) = 0;
          _8_2 = 1;
          DAT_EXTMEM_08c0 = 0x81;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) | DAT_CODE_abf0;
          _e_3 = _0_5 & 1;
          FUN_CODE_6040(5,BANK1_R0);
          bVar1 = _2_5;
          if (_1_5 != 0) {
            bVar1 = _2_5 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_5 & 1;
            FUN_CODE_9108(5,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11(-(((0x5c < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa3
                                 );
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa1;
        cVar3 = '\r' - (((0x5e < BANK1_R0 * '\x06') << 7) >> 7);
      }
      else {
        if (BANK1_R6 <=
            *(byte *)CONCAT11('\r' - (((0x5e < BANK1_R0 * '\x06') << 7) >> 7),
                              BANK1_R0 * '\x06' + 0xa1)) {
          *(undefined1 *)
           CONCAT11('\r' - (((0x5e < BANK1_R0 * '\x06') << 7) >> 7),BANK1_R0 * '\x06' + 0xa1) = 0;
          _8_2 = 0;
          DAT_EXTMEM_08c0 = 1;
          DAT_EXTMEM_02e0 = BANK1_R1;
          cVar3 = '\t' - (((0x9f < BANK1_R0) << 7) >> 7);
          uStack_1 = (byte *)CONCAT11(cVar3,BANK1_R0 + 0x60);
          *uStack_1 = *(byte *)CONCAT11(cVar3,BANK1_R0 + 0x60) & DAT_CODE_abe8;
          FUN_CODE_a96b();
          FUN_CODE_0f73(5,BANK1_R0);
          bVar1 = _2_5;
          if (_1_5 != 0) {
            bVar1 = _2_5 & 1 ^ 1;
          }
          if ((char)(bVar1 << 7) < '\0') {
            _e_3 = _0_5 & 1;
            FUN_CODE_9108(5,BANK1_R0);
          }
        }
        pcVar4 = (char *)CONCAT11('\r' - (((0x5e < BANK1_R0 * '\x06') << 7) >> 7),
                                  BANK1_R0 * '\x06' + 0xa1);
        *pcVar4 = *pcVar4 + '\x01';
        cVar2 = BANK1_R0 * '\x06' + 0xa3;
        cVar3 = -(((0x5c < BANK1_R0 * '\x06') << 7) >> 7);
      }
      *(undefined1 *)CONCAT11(cVar3,cVar2) = 0;
    }
    bVar1 = BANK1_R0;
    BANK1_R0 = BANK1_R0 + 1;
  } while (BANK1_R0 < 0x15);
  FUN_CODE_a96b(bVar1 - 0x14);
  cVar3 = DAT_EXTMEM_0323;
  if (DAT_EXTMEM_0323 == '\0') {
    if (((_5_6 != '\0') && (_5_5 != '\x01')) && (_a_0 != '\x01')) {
      _5_6 = '\0';
      if (_5_7 == '\0') {
        DAT_EXTMEM_09b8 = 0xea;
      }
      else {
        DAT_EXTMEM_09b8 = 0xe9;
      }
      cVar3 = '\0';
      DAT_EXTMEM_09b9 = 0;
      _a_0 = '\x01';
      _5_5 = '\x01';
      DAT_INTMEM_6f = 0;
    }
    if ((_5_5 != '\0') && (_a_0 != '\x01')) {
      bVar1 = DAT_INTMEM_6f + 1;
      cVar3 = DAT_INTMEM_6f - 9;
      DAT_INTMEM_6f = bVar1;
      if (9 < bVar1) {
        cVar3 = '\0';
        DAT_INTMEM_6f = 0;
        _5_5 = '\0';
        DAT_EXTMEM_09b8 = 0;
        DAT_EXTMEM_09b9 = 0;
        _a_0 = '\x01';
      }
    }
  }
  if (_7_7 != '\0') {
    _7_7 = '\0';
    FUN_CODE_9e73(cVar3);
  }
  if (DAT_EXTMEM_0317 == '\0') {
    FUN_CODE_ac69();
    return;
  }
  FUN_CODE_3a4f();
  return;
}



===== FUN_CODE_308d CODE:308d size=99 =====

char FUN_CODE_308d(char param_1,byte param_2,char param_3,byte param_4,char param_5,byte param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_0ed7 = 0;
  DAT_EXTMEM_0ed8 = 0;
  DAT_EXTMEM_0ed1 = param_5;
  DAT_EXTMEM_0ed2 = param_6;
  DAT_EXTMEM_0ed3 = param_3;
  DAT_EXTMEM_0ed4 = param_4;
  DAT_EXTMEM_0ed5 = param_1;
  DAT_EXTMEM_0ed6 = param_2;
  while( true ) {
    bVar1 = DAT_EXTMEM_0ed5 - (((DAT_EXTMEM_0ed8 < DAT_EXTMEM_0ed6) << 7) >> 7);
    if (bVar1 <= DAT_EXTMEM_0ed7) break;
    *(undefined1 *)
     CONCAT11(DAT_EXTMEM_0ed3 +
              (DAT_EXTMEM_0ed7 - ((CARRY1(DAT_EXTMEM_0ed4,DAT_EXTMEM_0ed8) << 7) >> 7)),
              DAT_EXTMEM_0ed4 + DAT_EXTMEM_0ed8) =
         *(undefined1 *)
          CONCAT11(DAT_EXTMEM_0ed1 +
                   (DAT_EXTMEM_0ed7 - ((CARRY1(DAT_EXTMEM_0ed2,DAT_EXTMEM_0ed8) << 7) >> 7)),
                   DAT_EXTMEM_0ed2 + DAT_EXTMEM_0ed8);
    IEN1 = 0;
    DAT_EXTMEM_0ed8 = DAT_EXTMEM_0ed8 + 1;
    if (DAT_EXTMEM_0ed8 == 0) {
      DAT_EXTMEM_0ed7 = DAT_EXTMEM_0ed7 + 1;
    }
  }
  return DAT_EXTMEM_0ed7 - bVar1;
}



===== FUN_CODE_3108 CODE:3108 size=1270 =====

void FUN_CODE_3108(char param_1,char param_2,char param_3)

{
  short sVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  char cVar7;
  short sStack_1;
  
  if (*(char *)CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) ==
      '\x01') {
    cVar4 = '\0';
    cVar7 = DAT_EXTMEM_0309 * '\x02';
    sStack_1 = (ushort)(cVar7 - 0x30) << 8;
    bVar2 = DAT_EXTMEM_02e0;
    FUN_CODE_4392(sStack_1,4);
    FUN_CODE_4345();
    BANK2_R1 = param_1;
    BANK2_R2 = param_2;
    BANK2_R3 = cVar7;
    BANK2_R4 = cVar4;
    if (((param_1 == '\0' && param_2 == '\0') && cVar7 == '\0') && cVar4 == '\0') {
      if ((DAT_EXTMEM_0324 < 2) << 7 < '\0') {
        bVar2 = DAT_EXTMEM_02e0;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x34,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)),DAT_EXTMEM_02e0);
        DAT_EXTMEM_0d10 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)bVar2 * 4 >> 8) + -0x34,(char)((ushort)bVar2 * 4)));
        FUN_CODE_431e(8);
        DAT_EXTMEM_0d11 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x34,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)));
        FUN_CODE_431e(0x10);
        sVar1 = (ushort)bVar2 * 4;
        cVar7 = (char)((ushort)sVar1 >> 8) + -0x34;
      }
      else {
        bVar2 = DAT_EXTMEM_02e0;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x32,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)));
        DAT_EXTMEM_0d10 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)bVar2 * 4 >> 8) + -0x32,(char)((ushort)bVar2 * 4)));
        FUN_CODE_431e(8);
        DAT_EXTMEM_0d11 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x32,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)));
        FUN_CODE_431e(0x10);
        sVar1 = (ushort)bVar2 * 4;
        cVar7 = (char)((ushort)sVar1 >> 8) + -0x32;
      }
      uVar5 = (undefined1)sVar1;
      DAT_EXTMEM_0d12 = cVar4;
    }
    else {
      if ((DAT_EXTMEM_0324 < 2) << 7 < '\0') {
        bVar3 = DAT_EXTMEM_02e0;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x30,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)),DAT_EXTMEM_02e0);
        DAT_EXTMEM_0d10 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)bVar3 * 4 >> 8) + -0x30,(char)((ushort)bVar3 * 4)));
        FUN_CODE_431e(8);
        DAT_EXTMEM_0d11 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x30,
                               (char)((ushort)DAT_EXTMEM_02e0 * 4)));
        FUN_CODE_431e(0x10);
        DAT_EXTMEM_0d12 = cVar4;
        FUN_CODE_4345(CONCAT11((char)((ushort)bVar3 * 4 >> 8) + -0x30,(char)((ushort)bVar3 * 4)));
        FUN_CODE_431e(0x18);
        DAT_EXTMEM_0d13 = cVar4;
        if ((bVar2 == 0xc) && (DAT_EXTMEM_0324 == 0)) {
          DAT_EXTMEM_0d10 = '#';
          DAT_EXTMEM_0d11 = '\x02';
          DAT_EXTMEM_0d12 = '\0';
          DAT_EXTMEM_0d13 = '\x02';
        }
        if ((DAT_EXTMEM_02e0 == 0x12) && (DAT_EXTMEM_0324 == 0)) {
          DAT_EXTMEM_0d10 = -0x76;
          DAT_EXTMEM_0d11 = '\x01';
          DAT_EXTMEM_0d12 = '\0';
          DAT_EXTMEM_0d13 = '\x02';
        }
        if (DAT_EXTMEM_02e0 != 0x1e) {
          return;
        }
        if (DAT_EXTMEM_0324 != 0) {
          return;
        }
        DAT_EXTMEM_0d10 = 8;
        DAT_EXTMEM_0d11 = 0;
        DAT_EXTMEM_0d12 = 8;
        DAT_EXTMEM_0d13 = 0;
        return;
      }
      bVar2 = DAT_EXTMEM_02e0;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x2e,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)),DAT_EXTMEM_02e0);
      DAT_EXTMEM_0d10 = cVar4;
      FUN_CODE_4345(CONCAT11((char)((ushort)bVar2 * 4 >> 8) + -0x2e,(char)((ushort)bVar2 * 4)));
      FUN_CODE_431e(8);
      DAT_EXTMEM_0d11 = cVar4;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x2e,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)));
      FUN_CODE_431e(0x10);
      uVar5 = (undefined1)((ushort)bVar2 * 4);
      cVar7 = (char)((ushort)bVar2 * 4 >> 8) + -0x2e;
      DAT_EXTMEM_0d12 = cVar4;
    }
  }
  else {
    if (*(char *)CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6) ==
        '\x02') {
      cVar4 = '\0';
      cVar7 = DAT_EXTMEM_0309 * '\x02';
      sStack_1 = (ushort)(cVar7 - 0x2c) << 8;
      FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
      FUN_CODE_4345();
      BANK2_R1 = param_1;
      BANK2_R2 = param_2;
      BANK2_R3 = cVar7;
      BANK2_R4 = cVar4;
      if (((param_1 == '\0' && param_2 == '\0') && cVar7 == '\0') && cVar4 == '\0') {
        uVar5 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x34) << 8;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        uVar6 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x34) << 8;
        DAT_EXTMEM_0d10 = uVar5;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(8);
        uVar5 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x34) << 8;
        DAT_EXTMEM_0d11 = uVar6;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(0x10);
        cVar7 = -0x34;
        DAT_EXTMEM_0d12 = uVar5;
      }
      else {
        uVar5 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x2c) << 8;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        uVar6 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x2c) << 8;
        DAT_EXTMEM_0d10 = uVar5;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(8);
        uVar5 = 0;
        sStack_1 = (ushort)(DAT_EXTMEM_0309 * '\x02' - 0x2c) << 8;
        DAT_EXTMEM_0d11 = uVar6;
        FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(0x10);
        cVar7 = -0x2c;
        DAT_EXTMEM_0d12 = uVar5;
      }
      uVar5 = 0;
      sStack_1 = (ushort)(byte)(cVar7 + DAT_EXTMEM_0309 * '\x02') << 8;
      FUN_CODE_4392(DAT_EXTMEM_02e0,sStack_1,4);
      FUN_CODE_4345();
      FUN_CODE_431e(0x18);
      DAT_EXTMEM_0d13 = uVar5;
      return;
    }
    if ((DAT_EXTMEM_0324 < 2) << 7 < '\0') {
      bVar2 = DAT_EXTMEM_02e0;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x34,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)),DAT_EXTMEM_02e0);
      DAT_EXTMEM_0d10 = param_3;
      FUN_CODE_4345(CONCAT11((char)((ushort)bVar2 * 4 >> 8) + -0x34,(char)((ushort)bVar2 * 4)));
      FUN_CODE_431e(8);
      DAT_EXTMEM_0d11 = param_3;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x34,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)));
      FUN_CODE_431e(0x10);
      uVar5 = (undefined1)((ushort)bVar2 * 4);
      cVar7 = (char)((ushort)bVar2 * 4 >> 8) + -0x34;
      DAT_EXTMEM_0d12 = param_3;
    }
    else {
      bVar2 = DAT_EXTMEM_02e0;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x32,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)));
      DAT_EXTMEM_0d10 = param_3;
      FUN_CODE_4345(CONCAT11((char)((ushort)bVar2 * 4 >> 8) + -0x32,(char)((ushort)bVar2 * 4)));
      FUN_CODE_431e(8);
      DAT_EXTMEM_0d11 = param_3;
      FUN_CODE_4345(CONCAT11((char)((ushort)DAT_EXTMEM_02e0 * 4 >> 8) + -0x32,
                             (char)((ushort)DAT_EXTMEM_02e0 * 4)));
      FUN_CODE_431e(0x10);
      uVar5 = (undefined1)((ushort)bVar2 * 4);
      cVar7 = (char)((ushort)bVar2 * 4 >> 8) + -0x32;
      DAT_EXTMEM_0d12 = param_3;
    }
  }
  cVar4 = DAT_EXTMEM_0d12;
  FUN_CODE_4345(CONCAT11(cVar7,uVar5));
  FUN_CODE_431e(0x18);
  DAT_EXTMEM_0d13 = cVar4;
  return;
}



===== FUN_CODE_3a4f CODE:3a4f size=844 =====

char FUN_CODE_3a4f(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  
  bVar2 = DAT_EXTMEM_0306;
  if (((_a_4 == '\x01') || (_7_0 == '\x01')) || (_a_6 == '\x01')) {
    if (*(char *)CONCAT11('\f' - (((0xad < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),
                          DAT_EXTMEM_0306 * '\x1c' + 0x52) == '\0') {
      *(undefined1 *)
       CONCAT11('\f' - (((0xad < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),
                DAT_EXTMEM_0306 * '\x1c' + 0x52) = 2;
      *(char *)CONCAT11('\f' - (((0xac < bVar2 * '\x1c') << 7) >> 7),bVar2 * '\x1c' + 0x53) =
           DAT_EXTMEM_08ae;
      FUN_CODE_41a4(BANK0_R1,0xb0,8,1,
                    ((char)((ushort)DAT_EXTMEM_0306 * 0x1c >> 8) -
                    (((0xab < (byte)((ushort)DAT_EXTMEM_0306 * 0x1c)) << 7) >> 7)) + '\f',1,0,5);
      bVar2 = DAT_EXTMEM_0306;
      *(undefined1 *)
       CONCAT11('\f' - (((0xa6 < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),
                DAT_EXTMEM_0306 * '\x1c' + 0x59) = 0;
      FUN_CODE_41a4(BANK0_R1,0x7c,9,1,
                    ((char)((ushort)bVar2 * 0x1c >> 8) -
                    (((0xa5 < (byte)((ushort)bVar2 * 0x1c)) << 7) >> 7)) + '\f',1,0,0x10);
      DAT_EXTMEM_0306 = DAT_EXTMEM_0306 + 1;
      _a_4 = '\0';
      _a_6 = '\0';
      _7_0 = '\0';
    }
  }
  else if (((_a_0 == '\x01') || (_9_0 == '\x01')) &&
          (*(char *)CONCAT11('\f' - (((0xad < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),
                             DAT_EXTMEM_0306 * '\x1c' + 0x52) == '\0')) {
    *(undefined1 *)
     CONCAT11('\f' - (((0xad < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),DAT_EXTMEM_0306 * '\x1c' + 0x52
             ) = 3;
    *(undefined1 *)CONCAT11('\f' - (((0xac < bVar2 * '\x1c') << 7) >> 7),bVar2 * '\x1c' + 0x53) =
         DAT_EXTMEM_09b8;
    bVar1 = DAT_EXTMEM_0306;
    *(undefined1 *)
     CONCAT11('\f' - (((0xab < DAT_EXTMEM_0306 * '\x1c') << 7) >> 7),DAT_EXTMEM_0306 * '\x1c' + 0x54
             ) = DAT_EXTMEM_09b9;
    *(undefined1 *)CONCAT11('\f' - (((0xaa < bVar1 * '\x1c') << 7) >> 7),bVar1 * '\x1c' + 0x55) =
         DAT_EXTMEM_097a;
    FUN_CODE_41a4(BANK0_R1,0xac,9,1,
                  ((char)((ushort)bVar2 * 0x1c >> 8) -
                  (((0xa9 < (byte)((ushort)bVar2 * 0x1c)) << 7) >> 7)) + '\f',1,0,7);
    DAT_EXTMEM_0306 = DAT_EXTMEM_0306 + 1;
    _a_0 = '\0';
    _9_0 = '\0';
    FUN_CODE_43ca(0xad,9,1,0,0,6);
  }
  _7_3 = 0;
  _6_7 = 0;
  if (5 < DAT_EXTMEM_0306) {
    DAT_EXTMEM_0306 = 0;
  }
  if (DAT_INTMEM_31 != '\0') {
    DAT_INTMEM_31 = DAT_INTMEM_31 + -1;
  }
  if (DAT_INTMEM_31 != '\0') {
    _6_7 = 0;
    _7_3 = 0;
    return DAT_INTMEM_31;
  }
  if (_c_1 != '\0') {
    _6_7 = 0;
    _7_3 = 0;
    return '\0';
  }
  cVar3 = T0;
  if (cVar3 != '\x01') {
    _6_7 = 0;
    _7_3 = 0;
    return '\0';
  }
  DAT_INTMEM_31 = 1;
  if (*(char *)CONCAT11('\f' - (((0xad < DAT_EXTMEM_0308 * '\x1c') << 7) >> 7),
                        DAT_EXTMEM_0308 * '\x1c' + 0x52) == '\x02') {
    T0 = 0;
    bVar2 = RXFLG;
    RXFLG = bVar2 | 0x10;
    T0 = 0;
    DAT_INTMEM_33 = 1;
    bVar2 = (byte)((ushort)DAT_EXTMEM_0308 * 0x1c);
    FUN_CODE_41a4(0x34,bVar2 + 0x52,
                  ((char)((ushort)DAT_EXTMEM_0308 * 0x1c >> 8) - (((0xad < bVar2) << 7) >> 7)) +
                  '\f',1,0,0,0,0x1c);
    FUN_CODE_a2a0(0x1e,6);
    *(undefined1 *)
     CONCAT11('\f' - (((0xad < DAT_EXTMEM_0308 * '\x1c') << 7) >> 7),DAT_EXTMEM_0308 * '\x1c' + 0x52
             ) = 0;
  }
  else {
    if (*(char *)CONCAT11('\f' - (((0xad < DAT_EXTMEM_0308 * '\x1c') << 7) >> 7),
                          DAT_EXTMEM_0308 * '\x1c' + 0x52) != '\x03') {
      if (DAT_EXTMEM_0306 == DAT_EXTMEM_0308) {
        if (_b_2 == '\0') {
          if (_b_5 == '\0') {
            if (((_c_4 != '\x01') && (_f_4 != '\0')) && (DAT_EXTMEM_0c3f == '\x02')) {
              if (_f_3 == '\x01') {
                DAT_EXTMEM_08ae = '\0';
                DAT_EXTMEM_08af = '\0';
                DAT_EXTMEM_08b0 = '\0';
                DAT_EXTMEM_08b1 = 0;
                DAT_EXTMEM_08b2 = 0;
                DAT_EXTMEM_08b3 = 0;
                DAT_EXTMEM_08b4 = 0;
                _f_3 = '\0';
                _7_0 = '\x01';
                DAT_INTMEM_32 = DAT_INTMEM_32 + 1;
                if (2 < DAT_INTMEM_32) {
                  DAT_INTMEM_32 = 0;
                  _f_4 = '\0';
                }
              }
              else if ((DAT_EXTMEM_08ae == '\0') && (DAT_EXTMEM_08b0 == '\0')) {
                DAT_EXTMEM_08ae = DAT_EXTMEM_08b0;
                DAT_EXTMEM_08af = DAT_EXTMEM_08b0;
                DAT_EXTMEM_08b0 = '\x01';
                DAT_EXTMEM_08b1 = 0;
                DAT_EXTMEM_08b2 = 0;
                DAT_EXTMEM_08b3 = 0;
                DAT_EXTMEM_08b4 = 0;
                _f_3 = '\x01';
                _7_0 = '\x01';
              }
            }
            goto LAB_CODE_3d8f;
          }
          _b_5 = '\0';
          FUN_CODE_43ca(0x33,0,0,0,0,0x17);
          DAT_INTMEM_3a = 7;
          DAT_INTMEM_3b = DAT_EXTMEM_0309;
        }
        else {
          _b_2 = '\0';
          FUN_CODE_43ca(0x33,0,0,0,0,0x17);
          DAT_INTMEM_3a = 5;
          DAT_INTMEM_3b = DAT_EXTMEM_0c31;
          if (_d_3 != '\x01') {
            DAT_INTMEM_3c = 1;
          }
          if (_6_0 != '\0') {
            DAT_INTMEM_3c = DAT_INTMEM_3c | 0x10;
          }
        }
        DAT_INTMEM_39 = 4;
        DAT_INTMEM_38 = 0;
        DAT_INTMEM_37 = 1;
        DAT_INTMEM_36 = 10;
        DAT_INTMEM_35 = 0x13;
        FUN_CODE_a758();
      }
      else {
        _7_7 = 1;
      }
      goto LAB_CODE_3d8f;
    }
    T0 = 0;
    bVar2 = RXFLG;
    RXFLG = bVar2 | 0x10;
    T0 = 0;
    DAT_INTMEM_33 = 1;
    bVar2 = (byte)((ushort)DAT_EXTMEM_0308 * 0x1c);
    FUN_CODE_41a4(0x34,bVar2 + 0x52,
                  ((char)((ushort)DAT_EXTMEM_0308 * 0x1c >> 8) - (((0xad < bVar2) << 7) >> 7)) +
                  '\f',1,0,0,0,0xb);
    FUN_CODE_a2a0(0xd,6);
    *(undefined1 *)
     CONCAT11('\f' - (((0xad < DAT_EXTMEM_0308 * '\x1c') << 7) >> 7),DAT_EXTMEM_0308 * '\x1c' + 0x52
             ) = 0;
  }
  DAT_EXTMEM_0308 = DAT_EXTMEM_0308 + 1;
  if (DAT_EXTMEM_0317 == '\x02') {
    DAT_INTMEM_31 = 4;
  }
LAB_CODE_3d8f:
  cVar3 = DAT_EXTMEM_0308 - 6;
  if (5 < DAT_EXTMEM_0308) {
    cVar3 = '\0';
    DAT_EXTMEM_0308 = 0;
  }
  return cVar3;
}



===== FUN_CODE_41a4 CODE:41a4 size=45 =====

char FUN_CODE_41a4(undefined1 param_1,char param_2,char param_3,char param_4,char param_5)

{
  byte bVar1;
  char cVar2;
  
  if (param_5 != '\0') {
    param_4 = param_4 + '\x01';
  }
  if (((param_5 != '\0' || param_4 != '\0') && (param_3 + 2U < 4)) &&
     (bVar1 = param_2 + 2, bVar1 < 4)) {
    bVar1 = (bVar1 * '\x02' | bVar1 >> 7) << 1 | (bVar1 & 0x7f) >> 6 | param_3 + 2U;
                    /* WARNING: Could not recover jumptable at 0x41c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cVar2 = (*(code *)((ushort)(bVar1 << 1 | bVar1 >> 7) + 0x4124))(param_1);
    return cVar2;
  }
  return param_3;
}



===== FUN_CODE_41ca CODE:41ca size=25 =====

undefined1 FUN_CODE_41ca(undefined1 *param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)CONCAT11(param_2,param_1);
  }
  if (param_3 == '\0') {
    return *param_1;
  }
  if (param_3 == -2) {
    return *(undefined1 *)ZEXT12(param_1);
  }
  return *(undefined1 *)CONCAT11(param_2,param_1);
}



===== FUN_CODE_41e3 CODE:41e3 size=45 =====

undefined1 FUN_CODE_41e3(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2);
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2);
  }
  return *(undefined1 *)
          CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
}



===== FUN_CODE_4244 CODE:4244 size=18 =====

char FUN_CODE_4244(char param_1,byte param_2,char param_3,byte param_4)

{
  return param_3 * param_2 + param_4 * param_1 + (char)((ushort)param_4 * (ushort)param_2 >> 8);
}



===== FUN_CODE_4256 CODE:4256 size=85 =====

byte FUN_CODE_4256(char param_1,byte param_2,byte param_3,byte param_4)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  
  if (param_1 != '\0') {
    bVar2 = 0;
    cVar3 = '\b';
    do {
      bVar1 = CARRY1(param_4,param_4);
      param_4 = param_4 * '\x02';
      bVar4 = param_3 << 1 | bVar1;
      bVar6 = bVar2 << 1 | param_3 >> 7;
      bVar5 = param_1 - (((bVar4 < param_2 - ((char)bVar2 >> 7)) << 7) >> 7);
      bVar2 = bVar6;
      if (bVar6 >= bVar5) {
        bVar4 = bVar4 - (param_2 - (((bVar6 < bVar5) << 7) >> 7));
        param_4 = param_4 + 1;
        bVar2 = bVar6 - bVar5;
      }
      cVar3 = cVar3 + -1;
      param_3 = bVar4;
    } while (cVar3 != '\0');
    return bVar4;
  }
  if (param_3 == 0) {
    if (param_2 != 0) {
      param_4 = param_4 / param_2;
    }
    return param_4;
  }
  bVar2 = 0;
  bVar5 = param_3;
  if (param_2 != 0) {
    bVar5 = param_3 / param_2;
    bVar2 = param_3 % param_2;
  }
  cVar3 = OV;
  if (cVar3 != '\x01') {
    cVar3 = '\b';
    bVar5 = bVar2;
LAB_CODE_4294:
    do {
      bVar1 = CARRY1(param_4,param_4);
      param_4 = param_4 * '\x02';
      bVar2 = bVar5 << 1 | bVar1;
      if ((char)bVar5 < '\0') {
        bVar5 = bVar2 - param_2;
      }
      else {
        bVar4 = param_2 - ((char)bVar5 >> 7);
        bVar6 = bVar2 - bVar4;
        bVar5 = bVar6;
        if (bVar2 < bVar4) {
          cVar3 = cVar3 + -1;
          bVar5 = bVar2;
          if (cVar3 == '\0') {
            return bVar6;
          }
          goto LAB_CODE_4294;
        }
      }
      param_4 = param_4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
  }
  return bVar5;
}



===== FUN_CODE_42ab CODE:42ab size=54 =====

char FUN_CODE_42ab(char param_1,char param_2,char param_3,char param_4)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  
  F0 = 0;
  if (param_1 < '\0') {
    bVar2 = F0;
    F0 = bVar2 ^ 1;
    bVar1 = param_2 != '\0';
    param_2 = -param_2;
    param_1 = -(param_1 - ((bVar1 << 7) >> 7));
  }
  if (param_3 < '\0') {
    bVar2 = F0;
    F0 = bVar2 ^ 1;
    bVar1 = param_4 != '\0';
    param_4 = -param_4;
    param_3 = -(param_3 - ((bVar1 << 7) >> 7));
    FUN_CODE_4256(param_1,param_2,param_3,param_4);
    cVar4 = -(param_1 - (((param_2 != '\0') << 7) >> 7));
  }
  else {
    cVar4 = FUN_CODE_4256(param_1,param_2);
  }
  cVar3 = F0;
  if (cVar3 != '\0') {
    cVar4 = -(param_3 - (((param_4 != '\0') << 7) >> 7));
  }
  return cVar4;
}



===== FUN_CODE_42e1 CODE:42e1 size=22 =====

void FUN_CODE_42e1(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}



===== FUN_CODE_431e CODE:431e size=19 =====

byte FUN_CODE_431e(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  byte bVar1;
  
  for (bVar1 = param_1; bVar1 != 0; bVar1 = bVar1 - 1) {
    param_1 = param_5 >> 1 | param_4 << 7;
    param_5 = param_1;
    param_4 = param_4 >> 1 | param_3 << 7;
    param_3 = param_3 >> 1 | param_2 << 7;
    param_2 = param_2 >> 1;
  }
  return param_1;
}



===== FUN_CODE_4331 CODE:4331 size=20 =====

byte FUN_CODE_4331(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  byte bVar1;
  
  for (bVar1 = param_1; bVar1 != 0; bVar1 = bVar1 - 1) {
    param_1 = param_5 >> 1 | param_4 << 7;
    param_5 = param_1;
    param_4 = param_4 >> 1 | param_3 << 7;
    param_3 = param_3 >> 1 | param_2 << 7;
    param_2 = param_2 >> 1 | param_2 & 0x80;
  }
  return param_1;
}



===== FUN_CODE_4345 CODE:4345 size=16 =====

undefined1 FUN_CODE_4345(short param_1)

{
  return *(undefined1 *)(param_1 + 3);
}



===== FUN_CODE_4355 CODE:4355 size=12 =====

void FUN_CODE_4355(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                  undefined1 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return;
}



===== FUN_CODE_4361 CODE:4361 size=23 =====

void FUN_CODE_4361(undefined2 param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  UNRECOVERED_JUMPTABLE = (code *)CONCAT11(uStackX_0,in_stack_000000ff);
  FUN_CODE_4378((char)((ushort)param_1 >> 8),(char)param_1);
  FUN_CODE_4378();
  FUN_CODE_4378();
  FUN_CODE_4378();
                    /* WARNING: Could not recover jumptable at 0x4377. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



===== FUN_CODE_4378 CODE:4378 size=26 =====

undefined1 FUN_CODE_4378(undefined1 *param_1,undefined1 param_2,undefined1 param_3)

{
  *(undefined1 *)CONCAT11(param_2,param_3) = *param_1;
  return *param_1;
}



===== FUN_CODE_4392 CODE:4392 size=12 =====

char FUN_CODE_4392(byte param_1,undefined2 param_2,byte param_3)

{
  return (char)((ushort)param_1 * (ushort)param_3 >> 8) +
         ((char)((ushort)param_2 >> 8) -
         ((CARRY1((byte)((ushort)param_1 * (ushort)param_3),(byte)param_2) << 7) >> 7));
}



===== FUN_CODE_439e CODE:439e size=38 =====

void FUN_CODE_439e(char param_1)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 3) {
    if (pcVar1[2] == param_1) goto LAB_CODE_43ae;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_43ae:
                    /* WARNING: Could not recover jumptable at 0x43b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}



===== FUN_CODE_43c4 CODE:43c4 size=6 =====

void FUN_CODE_43c4(undefined1 param_1,undefined1 param_2)

{
                    /* WARNING: Could not recover jumptable at 0x43c9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)CONCAT11(param_2,param_1))();
  return;
}



===== FUN_CODE_43ca CODE:43ca size=44 =====

void FUN_CODE_43ca(undefined1 *param_1,undefined1 param_2,char param_3,undefined1 param_4,
                  char param_5,char param_6)

{
  undefined1 *puVar1;
  
  if (param_6 != '\0' || param_5 != '\0') {
    if (param_6 != '\0') {
      param_5 = param_5 + '\x01';
    }
    if (param_3 != '\x01') {
      if (param_3 == '\0') {
        do {
          *param_1 = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
      }
      else if (param_3 == -2) {
        do {
          *(undefined1 *)ZEXT12(param_1) = param_4;
          param_1 = param_1 + '\x01';
          param_6 = param_6 + -1;
        } while (param_6 != '\0');
        return;
      }
      return;
    }
    puVar1 = (undefined1 *)CONCAT11(param_2,param_1);
    do {
      do {
        *puVar1 = param_4;
        puVar1 = puVar1 + 1;
        param_6 = param_6 + -1;
      } while (param_6 != '\0');
      param_5 = param_5 + -1;
    } while (param_5 != '\0');
  }
  return;
}



===== FUN_CODE_43f6 CODE:43f6 size=12 =====

undefined1 FUN_CODE_43f6(short param_1)

{
  return *(undefined1 *)(param_1 + 3);
}



===== FUN_CODE_4402 CODE:4402 size=808 =====

byte FUN_CODE_4402(byte param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  undefined1 *puVar4;
  
  if (_6_3 != '\0') {
    return param_1;
  }
  if (DAT_EXTMEM_0329 == '\0') {
    if (DAT_EXTMEM_0323 == '\0') {
      DAT_EXTMEM_0696 = '\x04';
      DAT_EXTMEM_0697 = 0;
      DAT_EXTMEM_0698 = '\x04';
      DAT_EXTMEM_0699 = 0;
      DAT_EXTMEM_06b8 = '\x04';
      DAT_EXTMEM_06b9 = 0;
    }
    else {
      bVar3 = *(byte *)CONCAT11((DAT_EXTMEM_09b3 - (((0x7f < DAT_EXTMEM_09b4) << 7) >> 7)) + -0x3c,
                                DAT_EXTMEM_09b4 + 0x80);
      bVar2 = (byte)((ushort)bVar3 * 4);
      DAT_EXTMEM_06b9 = DAT_CODE_25f5 + bVar2;
      DAT_EXTMEM_06b8 = (char)((ushort)bVar3 * 4 >> 8) - ((CARRY1(DAT_CODE_25f5,bVar2) << 7) >> 7);
      bVar2 = (byte)((ushort)bVar3 * 4);
      DAT_EXTMEM_0697 = DAT_CODE_25f6 + bVar2;
      DAT_EXTMEM_0696 = (char)((ushort)bVar3 * 4 >> 8) - ((CARRY1(DAT_CODE_25f6,bVar2) << 7) >> 7);
      bVar2 = (byte)((ushort)bVar3 * 4);
      DAT_EXTMEM_0699 = DAT_CODE_25f7 + bVar2;
      DAT_EXTMEM_0698 = (char)((ushort)bVar3 * 4 >> 8) - ((CARRY1(DAT_CODE_25f7,bVar2) << 7) >> 7);
      DAT_EXTMEM_09b4 = DAT_EXTMEM_09b4 + 1;
      if (DAT_EXTMEM_09b4 == 0) {
        DAT_EXTMEM_09b3 = DAT_EXTMEM_09b3 + 1;
      }
      if ((byte)-(((DAT_EXTMEM_09b4 < 0x81) << 7) >> 7) <= DAT_EXTMEM_09b3) {
        DAT_EXTMEM_09b3 = 0;
        DAT_EXTMEM_09b4 = 0;
      }
    }
  }
  else {
    DAT_EXTMEM_0696 = '\0';
    DAT_EXTMEM_0697 = DAT_CODE_25f6;
    DAT_EXTMEM_0698 = '\0';
    DAT_EXTMEM_0699 = DAT_CODE_25f7;
    DAT_EXTMEM_06b8 = '\0';
    DAT_EXTMEM_06b9 = DAT_CODE_25f5;
  }
  if ((_a_5 == '\x01') || (_b_6 != '\0')) {
    if ((byte)-(((DAT_EXTMEM_0e1b < 0xf0) << 7) >> 7) <= DAT_EXTMEM_0e1a) {
      DAT_EXTMEM_0e1a = 0;
      DAT_EXTMEM_0e1b = 0;
      if ((_b_6 == '\0') || (DAT_EXTMEM_0d16 != 0)) {
        DAT_EXTMEM_0d16 = DAT_EXTMEM_0d16 - 1;
        if ((DAT_EXTMEM_0d16 & 1) == 0) {
          _5_0 = 0;
          _5_1 = '\0';
          _5_2 = '\0';
          _5_3 = '\0';
        }
        else {
          _5_0 = 1;
          _5_1 = '\x01';
          _5_2 = '\x01';
          _5_3 = '\x01';
        }
      }
      else {
        _b_6 = '\0';
      }
    }
  }
  else {
    _5_0 = (DAT_EXTMEM_0f34 & 1) != 0;
    _5_1 = (DAT_EXTMEM_0f34 >> 1 & 1) != 0;
    _5_2 = (DAT_EXTMEM_0f34 >> 2 & 1) != 0;
    if (_9_6 == '\0') {
      _5_3 = '\0';
    }
    else {
      _5_3 = '\x01';
    }
  }
  if (_5_3 == '\0') {
    DAT_EXTMEM_0650 = 0;
    DAT_EXTMEM_0651 = DAT_CODE_25f7;
  }
  else {
    DAT_EXTMEM_0650 = 4;
    DAT_EXTMEM_0651 = 0;
  }
  if (_5_2 == '\0') {
    DAT_EXTMEM_064e = 0;
    DAT_EXTMEM_064f = DAT_CODE_25f6;
  }
  else {
    DAT_EXTMEM_064e = 4;
    DAT_EXTMEM_064f = 0;
  }
  if (_5_1 == '\0') {
    DAT_EXTMEM_064c = 0;
    DAT_EXTMEM_064d = DAT_CODE_25f5;
  }
  else {
    DAT_EXTMEM_064c = 4;
    DAT_EXTMEM_064d = 0;
  }
  bVar3 = DAT_EXTMEM_064d;
  DAT_EXTMEM_0694 = DAT_EXTMEM_06b8;
  DAT_EXTMEM_0695 = DAT_EXTMEM_06b9;
  if ((_3_4 != '\x01') ||
     (cVar1 = ((DAT_EXTMEM_0e1d < 0xf1) << 7) >> 7, bVar3 = DAT_EXTMEM_0e1c + cVar1,
     DAT_EXTMEM_0e1c < (byte)-cVar1)) goto LAB_CODE_46ec;
  DAT_EXTMEM_0e1c = 0;
  DAT_EXTMEM_0e1d = 0;
  _6_4 = _6_4 ^ 1;
  if (_6_4 == 1) {
    if (DAT_EXTMEM_0324 == '\0') {
      DAT_EXTMEM_05f2 = 0;
      DAT_EXTMEM_05f3 = DAT_CODE_25ec;
      goto LAB_CODE_4676;
    }
    if (DAT_EXTMEM_0324 == '\x02') {
      DAT_EXTMEM_0616 = 0;
      DAT_EXTMEM_0617 = DAT_CODE_25ec;
      goto LAB_CODE_469d;
    }
    if (DAT_EXTMEM_0324 == '\x03') {
      DAT_EXTMEM_063a = 0;
      DAT_EXTMEM_063b = DAT_CODE_25ec;
      goto LAB_CODE_46c4;
    }
    if (DAT_EXTMEM_0324 == '\x01') {
      DAT_EXTMEM_05ce = 0;
      DAT_EXTMEM_05cf = DAT_CODE_25ec;
      goto LAB_CODE_464f;
    }
  }
  else {
    if (DAT_EXTMEM_0324 == '\0') {
      DAT_EXTMEM_05f2 = 4;
      DAT_EXTMEM_05f3 = 0;
LAB_CODE_4676:
      DAT_EXTMEM_05f4 = 0;
      DAT_EXTMEM_05f5 = DAT_CODE_25ed;
      puVar4 = &DAT_EXTMEM_05f6;
    }
    else if (DAT_EXTMEM_0324 == '\x02') {
      DAT_EXTMEM_0616 = 4;
      DAT_EXTMEM_0617 = 0;
LAB_CODE_469d:
      DAT_EXTMEM_0618 = 0;
      DAT_EXTMEM_0619 = DAT_CODE_25ed;
      puVar4 = &DAT_EXTMEM_061a;
    }
    else if (DAT_EXTMEM_0324 == '\x03') {
      DAT_EXTMEM_063a = 4;
      DAT_EXTMEM_063b = 0;
LAB_CODE_46c4:
      DAT_EXTMEM_063c = 0;
      DAT_EXTMEM_063d = DAT_CODE_25ed;
      puVar4 = &DAT_EXTMEM_063e;
    }
    else {
      if (DAT_EXTMEM_0324 != '\x01') goto LAB_CODE_46dc;
      DAT_EXTMEM_05ce = 4;
      DAT_EXTMEM_05cf = 0;
LAB_CODE_464f:
      DAT_EXTMEM_05d0 = 0;
      DAT_EXTMEM_05d1 = DAT_CODE_25ed;
      puVar4 = &DAT_EXTMEM_05d2;
    }
    *puVar4 = 0;
    puVar4[1] = DAT_CODE_25ee;
  }
LAB_CODE_46dc:
  bVar2 = DAT_EXTMEM_0e1e + 1;
  bVar3 = DAT_EXTMEM_0e1e - 6;
  DAT_EXTMEM_0e1e = bVar2;
  if (6 < bVar2) {
    DAT_EXTMEM_0e1e = 0;
    _3_4 = '\0';
    bVar3 = 0;
  }
LAB_CODE_46ec:
  if ((_8_4 != '\x01') && (_3_4 != '\x01')) {
    if (DAT_EXTMEM_0324 == '\0') {
      puVar4 = &DAT_EXTMEM_05f2;
    }
    else if (DAT_EXTMEM_0324 == '\x02') {
      puVar4 = &DAT_EXTMEM_0616;
    }
    else if (DAT_EXTMEM_0324 == '\x03') {
      puVar4 = &DAT_EXTMEM_063a;
    }
    else {
      if (DAT_EXTMEM_0324 - 1U != 0) {
        return DAT_EXTMEM_0324 - 1U;
      }
      puVar4 = &DAT_EXTMEM_05ce;
    }
    *puVar4 = 4;
    puVar4[1] = 0;
    puVar4[2] = 4;
    puVar4[3] = 0;
    puVar4[4] = 4;
    bVar3 = 0;
    puVar4[5] = 0;
  }
  return bVar3;
}



===== FUN_CODE_472a CODE:472a size=12 =====

/* WARNING: Removing unreachable block (CODE,0x4749) */
/* WARNING: Removing unreachable block (CODE,0x49da) */
/* WARNING: Removing unreachable block (CODE,0x49a1) */
/* WARNING: Removing unreachable block (CODE,0x49a3) */
/* WARNING: Removing unreachable block (CODE,0x49d8) */
/* WARNING: Removing unreachable block (CODE,0x49fa) */
/* WARNING: Removing unreachable block (CODE,0x4a08) */

byte FUN_CODE_472a(undefined1 param_1,undefined2 param_2,byte param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  byte bVar5;
  byte bVar6;
  char in_PSW;
  undefined1 *puVar7;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0ee3 = *(byte *)CONCAT11((char)((ushort)param_2 >> 8) - (in_PSW >> 7),param_1);
  bVar2 = param_3 - 0x15;
  DAT_EXTMEM_0ee4 = param_3;
  if (param_3 < 0x15) {
    if (DAT_EXTMEM_011c == '\a') {
      FUN_CODE_a0dd();
      FUN_CODE_42ab(0,0xc0);
      bVar2 = (byte)((ushort)BANK0_R5 * 3);
      uVar4 = *(undefined1 *)
               CONCAT11((char)((ushort)BANK0_R5 * 3 >> 8) + ('\'' - (((0x16 < bVar2) << 7) >> 7)),
                        bVar2 - 0x17);
      bVar2 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar2) << 7) >> 7)),bVar2 + 0x24);
      bVar2 = DAT_EXTMEM_0ee3;
      bVar5 = DAT_EXTMEM_0ee4;
      bVar6 = BANK0_R5;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar4;
      bVar3 = (byte)((ushort)bVar6 * 3);
      uVar4 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar6 * 3 >> 8) + ('\'' - (((0x15 < bVar3) << 7) >> 7)),
                        bVar3 - 0x16);
      bVar3 = (byte)((ushort)bVar5 * 0x12);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar5 * 0x12 >> 8) + ('\x04' - (((0xda < bVar3) << 7) >> 7)),
                        bVar3 + 0x25);
      FUN_CODE_4392(bVar2,3);
      *puVar7 = uVar4;
      bVar2 = (byte)((ushort)bVar6 * 3);
      uVar4 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar6 * 3 >> 8) + ('\'' - (((0x14 < bVar2) << 7) >> 7)),
                        bVar2 - 0x15);
      bVar2 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar2) << 7) >> 7)),bVar2 + 0x26);
      bVar2 = DAT_EXTMEM_0ee3;
    }
    else {
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) + -0x38,
                          (char)((ushort)DAT_EXTMEM_0892 * 0x15));
      cVar1 = DAT_EXTMEM_011c;
      bVar2 = DAT_EXTMEM_0892;
      FUN_CODE_4392(3,DAT_EXTMEM_011c);
      uVar4 = *uStack_1;
      bVar5 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar5) << 7) >> 7)),bVar5 + 0x24);
      FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
      *uStack_1 = uVar4;
      bVar5 = (byte)((ushort)bVar2 * 0x15);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar2 * 0x15 >> 8) + (-0x38 - (((0xfe < bVar5) << 7) >> 7)),
                        bVar5 + 1);
      FUN_CODE_4392(cVar1,3);
      uVar4 = *puVar7;
      bVar2 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xda < bVar2) << 7) >> 7)),bVar2 + 0x25);
      bVar2 = DAT_EXTMEM_0ee3;
      bVar5 = DAT_EXTMEM_0ee4;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar4;
      bVar6 = (byte)((ushort)DAT_EXTMEM_0892 * 0x15);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) +
                          (-0x38 - (((0xfd < bVar6) << 7) >> 7)),bVar6 + 2);
      FUN_CODE_4392(DAT_EXTMEM_011c,3);
      uVar4 = *uStack_1;
      bVar6 = (byte)((ushort)bVar5 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)bVar5 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar6) << 7) >> 7)),bVar6 + 0x26);
    }
    FUN_CODE_4392(bVar2,3);
    *uStack_1 = uVar4;
    bVar5 = DAT_EXTMEM_0ee4;
    bVar2 = DAT_EXTMEM_0ee3;
    bVar6 = DAT_EXTMEM_0ee4 * '\x06' + 0x17;
    *(undefined1 *)
     CONCAT11(-((CARRY1(bVar6,DAT_EXTMEM_0ee3) << 7) >> 7) -
              (((0xe8 < DAT_EXTMEM_0ee4 * '\x06') << 7) >> 7),bVar6 + DAT_EXTMEM_0ee3) = 0x20;
    if (DAT_EXTMEM_009d == '\t') {
      bVar2 = 0;
    }
    else {
      FUN_CODE_7e03(bVar5);
      if (bVar2 == 0) {
        bVar2 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
        uStack_1 = (undefined1 *)
                   CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                            ('\x04' - (((0xdb < bVar2) << 7) >> 7)),bVar2 + 0x24);
        bVar2 = DAT_EXTMEM_0ee3;
        bVar5 = DAT_EXTMEM_0ee4;
        FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
        DAT_EXTMEM_011d = *uStack_1;
        bVar6 = (byte)((ushort)bVar5 * 0x12);
        puVar7 = (undefined1 *)
                 CONCAT11((char)((ushort)bVar5 * 0x12 >> 8) +
                          ('\x04' - (((0xda < bVar6) << 7) >> 7)),bVar6 + 0x25);
        FUN_CODE_4392(bVar2,3);
        uEXTMEM0000 = *puVar7;
        bVar2 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
        uStack_1 = (undefined1 *)
                   CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                            ('\x04' - (((0xd9 < bVar2) << 7) >> 7)),bVar2 + 0x26);
        FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
        DAT_EXTMEM_0e20 = *uStack_1;
        FUN_CODE_9819();
        DAT_EXTMEM_0eef = DAT_EXTMEM_0e3e;
        DAT_EXTMEM_0ef0 = DAT_EXTMEM_0e3b;
        bVar2 = FUN_CODE_6e7f(DAT_EXTMEM_0e42,DAT_EXTMEM_0ee3,DAT_EXTMEM_0ee4);
      }
    }
  }
  return bVar2;
}



===== FUN_CODE_4736 CODE:4736 size=744 =====

byte FUN_CODE_4736(char param_1,byte param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  undefined1 *puVar7;
  undefined2 uStack_1;
  
  if (0x14 < param_2) {
    DAT_EXTMEM_0ee3 = param_3;
    DAT_EXTMEM_0ee4 = param_2;
    return param_2 - 0x15;
  }
  DAT_EXTMEM_0ee3 = param_3;
  DAT_EXTMEM_0ee4 = param_2;
  if (param_1 == '\0') {
    if (DAT_EXTMEM_009d == '\t') {
      bVar1 = param_2 * '\x06' + 0x17;
      *(undefined1 *)
       CONCAT11(-((CARRY1(bVar1,param_3) << 7) >> 7) - (((0xe8 < param_2 * '\x06') << 7) >> 7),
                bVar1 + param_3) = 0;
    }
    else {
      bVar1 = 0;
      do {
        bVar4 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
        bVar5 = bVar4 + 0x24;
        cVar6 = (char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                ('\x04' - (((0xdb < bVar4) << 7) >> 7));
        FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
        *(undefined1 *)CONCAT11(cVar6 - ((CARRY1(bVar5,bVar1) << 7) >> 7),bVar5 + bVar1) = 0;
        bVar1 = bVar1 + 1;
      } while (bVar1 != 3);
    }
    bVar1 = DAT_EXTMEM_0ee3;
    FUN_CODE_7e03(DAT_EXTMEM_0ee4);
    if (bVar1 != 0) {
      return bVar1;
    }
    DAT_EXTMEM_0eef = 0;
    DAT_EXTMEM_0ef0 = 0;
    uVar3 = 0;
  }
  else {
    if (DAT_EXTMEM_011c == '\a') {
      FUN_CODE_a0dd();
      FUN_CODE_42ab(0,0xc0);
      bVar1 = (byte)((ushort)BANK0_R5 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)BANK0_R5 * 3 >> 8) + ('\'' - (((0x16 < bVar1) << 7) >> 7)),
                        bVar1 - 0x17);
      bVar1 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar1) << 7) >> 7)),bVar1 + 0x24);
      bVar1 = DAT_EXTMEM_0ee3;
      bVar4 = DAT_EXTMEM_0ee4;
      bVar5 = BANK0_R5;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar3;
      bVar2 = (byte)((ushort)bVar5 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar5 * 3 >> 8) + ('\'' - (((0x15 < bVar2) << 7) >> 7)),
                        bVar2 - 0x16);
      bVar2 = (byte)((ushort)bVar4 * 0x12);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar4 * 0x12 >> 8) + ('\x04' - (((0xda < bVar2) << 7) >> 7)),
                        bVar2 + 0x25);
      FUN_CODE_4392(bVar1,3);
      *puVar7 = uVar3;
      bVar1 = (byte)((ushort)bVar5 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar5 * 3 >> 8) + ('\'' - (((0x14 < bVar1) << 7) >> 7)),
                        bVar1 - 0x15);
      bVar1 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar1) << 7) >> 7)),bVar1 + 0x26);
      bVar1 = DAT_EXTMEM_0ee3;
    }
    else {
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) + -0x38,
                          (char)((ushort)DAT_EXTMEM_0892 * 0x15));
      cVar6 = DAT_EXTMEM_011c;
      bVar1 = DAT_EXTMEM_0892;
      FUN_CODE_4392(3,DAT_EXTMEM_011c);
      uVar3 = *uStack_1;
      bVar4 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar4) << 7) >> 7)),bVar4 + 0x24);
      FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
      *uStack_1 = uVar3;
      bVar4 = (byte)((ushort)bVar1 * 0x15);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar1 * 0x15 >> 8) + (-0x38 - (((0xfe < bVar4) << 7) >> 7)),
                        bVar4 + 1);
      FUN_CODE_4392(cVar6,3);
      uVar3 = *puVar7;
      bVar1 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xda < bVar1) << 7) >> 7)),bVar1 + 0x25);
      bVar1 = DAT_EXTMEM_0ee3;
      bVar4 = DAT_EXTMEM_0ee4;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar3;
      bVar5 = (byte)((ushort)DAT_EXTMEM_0892 * 0x15);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) +
                          (-0x38 - (((0xfd < bVar5) << 7) >> 7)),bVar5 + 2);
      FUN_CODE_4392(DAT_EXTMEM_011c,3);
      uVar3 = *uStack_1;
      bVar5 = (byte)((ushort)bVar4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)bVar4 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar5) << 7) >> 7)),bVar5 + 0x26);
    }
    FUN_CODE_4392(bVar1,3);
    *uStack_1 = uVar3;
    bVar4 = DAT_EXTMEM_0ee4;
    bVar1 = DAT_EXTMEM_0ee3;
    bVar5 = DAT_EXTMEM_0ee4 * '\x06' + 0x17;
    *(undefined1 *)
     CONCAT11(-((CARRY1(bVar5,DAT_EXTMEM_0ee3) << 7) >> 7) -
              (((0xe8 < DAT_EXTMEM_0ee4 * '\x06') << 7) >> 7),bVar5 + DAT_EXTMEM_0ee3) = 0x20;
    if (DAT_EXTMEM_009d == '\t') {
      return 0;
    }
    FUN_CODE_7e03(bVar4);
    if (bVar1 != 0) {
      return bVar1;
    }
    bVar1 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
    uStack_1 = (undefined1 *)
               CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                        ('\x04' - (((0xdb < bVar1) << 7) >> 7)),bVar1 + 0x24);
    bVar1 = DAT_EXTMEM_0ee3;
    bVar4 = DAT_EXTMEM_0ee4;
    FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
    DAT_EXTMEM_011d = *uStack_1;
    bVar5 = (byte)((ushort)bVar4 * 0x12);
    puVar7 = (undefined1 *)
             CONCAT11((char)((ushort)bVar4 * 0x12 >> 8) + ('\x04' - (((0xda < bVar5) << 7) >> 7)),
                      bVar5 + 0x25);
    FUN_CODE_4392(bVar1,3);
    uEXTMEM0000 = *puVar7;
    bVar1 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
    uStack_1 = (undefined1 *)
               CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                        ('\x04' - (((0xd9 < bVar1) << 7) >> 7)),bVar1 + 0x26);
    FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
    DAT_EXTMEM_0e20 = *uStack_1;
    FUN_CODE_9819();
    DAT_EXTMEM_0eef = DAT_EXTMEM_0e3e;
    DAT_EXTMEM_0ef0 = DAT_EXTMEM_0e3b;
    uVar3 = DAT_EXTMEM_0e42;
  }
  bVar1 = FUN_CODE_6e7f(uVar3,DAT_EXTMEM_0ee3,DAT_EXTMEM_0ee4);
  return bVar1;
}



===== FUN_CODE_4f8a CODE:4f8a size=990 =====

/* WARNING: Instruction at (CODE,0x52fc) overlaps instruction at (CODE,0x52fb)
    */
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Possible PIC construction at 0x5296: Changing call to branch */

byte FUN_CODE_4f8a(byte param_1,byte param_2,char param_3,byte param_4,byte param_5)

{
  bool bVar1;
  ushort uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  undefined1 uVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  char cVar13;
  undefined1 *puVar14;
  byte *pbVar15;
  char *pcVar16;
  
  puVar11 = (undefined1 *)0x0;
  if ((_8_1 != '\x01') || (_9_0 != '\0')) {
    return param_1;
  }
  _8_1 = 0;
  bVar3 = 0;
LAB_CODE_4f9a:
  if (*(char *)CONCAT11('\f' - (((0xcd < bVar3) << 7) >> 7),bVar3 + 0x32) == '\0') {
    cVar13 = (0xbf < bVar3) << 7;
    bVar8 = bVar3 + 0x40;
code_c0x50d0:
    pbVar15 = (byte *)(ushort)bVar8;
    bVar8 = 0;
code_c0x50d3:
    pbVar15 = (byte *)CONCAT11(bVar8 + ('\f' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_47:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *pbVar15 = 0;
    cVar13 = (0x73 < bVar3) << 7;
    bVar8 = bVar3 + 0x8c;
code_c0x50dc:
    pbVar15 = (byte *)(ushort)bVar8;
    bVar8 = 0;
code_c0x50df:
    pbVar15 = (byte *)CONCAT11(bVar8 + ('\x03' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_4b:
                    /* WARNING: This code block may not be properly labeled as switch case */
    bVar8 = 0;
code_c0x50e4:
    *pbVar15 = bVar8;
  }
  else {
    _8_1 = 1;
    if (*(char *)CONCAT11('\f' - (((0xbf < bVar3) << 7) >> 7),bVar3 + 0x40) == '\0') {
      _9_0 = '\x01';
      *(undefined1 *)CONCAT11('\f' - (((0xbf < bVar3) << 7) >> 7),bVar3 + 0x40) =
           *(undefined1 *)CONCAT11('\x03' - (((0x73 < bVar3) << 7) >> 7),bVar3 + 0x8c);
      bVar7 = bVar3 + 1;
      cVar13 = (0xcd < bVar3) << 7;
      bVar8 = bVar3 + 0x32;
code_c0x4fdc:
      bVar9 = bVar3;
      if ((*(byte *)CONCAT11('\f' - (cVar13 >> 7),bVar8) & 1) != 1) goto switchD_CODE_5001_caseD_26;
      if (0xc < bVar3) goto LAB_CODE_508b;
      uVar2 = (ushort)bVar3 * 3;
      bVar8 = (byte)uVar2;
      bVar6 = (byte)(uVar2 >> 8);
      bVar1 = 0xaf < bVar6;
      cVar13 = bVar1 << 7;
      pbVar15 = (byte *)CONCAT11(bVar6 + 0x50,2);
      bVar4 = bVar7;
      bVar5 = param_5;
      bVar9 = bVar8;
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      switch(bVar3) {
      default:
        break;
      case 1:
        break;
      case 2:
        break;
      case 3:
        break;
      case 4:
        break;
      case 5:
LAB_CODE_5039:
        puVar14 = &DAT_EXTMEM_09b2;
LAB_CODE_5046:
        *puVar14 = 1;
        goto LAB_CODE_508b;
      case 6:
switchD_CODE_5001_caseD_14:
                    /* WARNING: This code block may not be properly labeled as switch case */
        pbVar15 = (byte *)0x9b2;
switchD_CODE_5001_caseD_15:
                    /* WARNING: This code block may not be properly labeled as switch case */
LAB_CODE_504e:
        bVar8 = 0xff;
        goto switchD_CODE_5001_caseD_1a;
      case 7:
        puVar14 = &DAT_EXTMEM_09b1;
        goto LAB_CODE_5046;
      case 8:
        pbVar15 = &DAT_EXTMEM_09b1;
        goto LAB_CODE_504e;
      case 9:
switchD_CODE_5001_caseD_1b:
                    /* WARNING: This code block may not be properly labeled as switch case */
        pbVar15 = (byte *)0x9ad;
switchD_CODE_5001_caseD_1c:
                    /* WARNING: This code block may not be properly labeled as switch case */
LAB_CODE_5060:
        bVar8 = 0xff;
switchD_CODE_5001_caseD_20:
                    /* WARNING: This code block may not be properly labeled as switch case */
        *pbVar15 = bVar8;
        pbVar15[1] = bVar8;
switchD_CODE_5001_caseD_21:
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto LAB_CODE_508b;
      case 10:
        pbVar15 = &DAT_EXTMEM_09ad;
        goto LAB_CODE_506a;
      case 0xb:
        goto LAB_CODE_505d;
      case 0xc:
        pbVar15 = &DAT_EXTMEM_09af;
LAB_CODE_506a:
                    /* WARNING: This code block may not be properly labeled as switch case */
        *pbVar15 = 1;
        bVar8 = 0;
switchD_CODE_5001_caseD_24:
                    /* WARNING: This code block may not be properly labeled as switch case */
        pbVar15[1] = bVar8;
        goto LAB_CODE_508b;
      case 0xe:
        goto switchD_CODE_5001_caseD_e;
      case 0xf:
        goto switchD_CODE_5001_caseD_f;
      case 0x10:
        goto switchD_CODE_5001_caseD_10;
      case 0x11:
        goto switchD_CODE_5001_caseD_11;
      case 0x12:
        goto LAB_CODE_5039;
      case 0x13:
        bVar8 = P0_0;
                    /* WARNING: This code block may not be properly labeled as switch case */
        P0_0 = bVar8 ^ 1;
      case 0x14:
        goto switchD_CODE_5001_caseD_14;
      case 0x15:
        goto switchD_CODE_5001_caseD_15;
      case 0x16:
                    /* WARNING: This code block may not be properly labeled as switch case */
        puVar11['\x01'] = 0x47;
        puVar11['\x02'] = 0x50;
        func_0x5574(param_2 + 1);
      case 0x17:
                    /* WARNING: This code block may not be properly labeled as switch case */
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      case 0x18:
        goto switchD_CODE_5001_caseD_18;
      case 0x19:
        goto switchD_CODE_5001_caseD_19;
      case 0x1a:
        goto switchD_CODE_5001_caseD_1a;
      case 0x1b:
        goto switchD_CODE_5001_caseD_1b;
      case 0x1c:
        goto switchD_CODE_5001_caseD_1c;
      case 0x1d:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_2 = param_2 + 1;
        param_4 = P0;
      case 0x1e:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_4 = param_4 + 1;
LAB_CODE_505d:
        pbVar15 = &DAT_EXTMEM_09af;
        goto LAB_CODE_5060;
      case 0x1f:
      case 0x20:
        goto switchD_CODE_5001_caseD_20;
      case 0x21:
        goto switchD_CODE_5001_caseD_21;
      case 0x22:
      case 0x23:
        _8_1 = 1;
        _9_0 = 1;
        halt_baddata();
      case 0x24:
        goto switchD_CODE_5001_caseD_24;
      case 0x25:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_2 = param_2 - 1;
        bVar9 = bVar3;
      case 0x26:
switchD_CODE_5001_caseD_26:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (bVar9 < 5) {
switchD_CODE_5001_caseD_28:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_09ac;
switchD_CODE_5001_caseD_29:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = *pbVar15;
          bVar8 = bVar3;
switchD_CODE_5001_caseD_2a:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_CODE_abe3;
switchD_CODE_5001_caseD_2b:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = pbVar15[bVar8];
          bVar8 = param_5;
switchD_CODE_5001_caseD_2c:
                    /* WARNING: This code block may not be properly labeled as switch case */
          DAT_EXTMEM_09ac = bVar8 & bVar7;
        }
        goto LAB_CODE_508b;
      case 0x27:
        return bVar8;
      case 0x28:
        goto switchD_CODE_5001_caseD_28;
      case 0x29:
        goto switchD_CODE_5001_caseD_29;
      case 0x2a:
        goto switchD_CODE_5001_caseD_2a;
      case 0x2b:
        goto switchD_CODE_5001_caseD_2b;
      case 0x2c:
        goto switchD_CODE_5001_caseD_2c;
      case 0x2d:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar3 = bVar6;
        goto LAB_CODE_508b;
      case 0x2e:
                    /* WARNING: This code block may not be properly labeled as switch case */
        return bVar8;
      case 0x2f:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x5091;
      case 0x30:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar3 = bVar3 + 1;
        goto code_c0x5091;
      case 0x31:
        goto switchD_CODE_5001_caseD_31;
      case 0x32:
        goto switchD_CODE_5001_caseD_32;
      case 0x33:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_5 = param_5 + 1;
        goto code_c0x509c;
      case 0x34:
        goto switchD_CODE_5001_caseD_34;
      case 0x35:
        goto switchD_CODE_5001_caseD_35;
      case 0x36:
        goto switchD_CODE_5001_caseD_36;
      case 0x37:
        goto switchD_CODE_5001_caseD_37;
      case 0x38:
        goto LAB_CODE_50ab;
      case 0x39:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_5 = bVar8 + 1;
        goto code_c0x50af;
      case 0x3a:
                    /* WARNING: This code block may not be properly labeled as switch case */
        return bVar8;
      case 0x3b:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x50b5;
      case 0x3c:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar3 = bVar3 + 1;
        goto code_c0x50b5;
      case 0x3d:
        goto switchD_CODE_5001_caseD_3d;
      case 0x3e:
        goto switchD_CODE_5001_caseD_3e;
      case 0x3f:
                    /* WARNING: This code block may not be properly labeled as switch case */
        return bVar8;
      case 0x40:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x50c4;
      case 0x41:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar3 = bVar3 + 1;
        goto code_c0x50c4;
      case 0x42:
        goto switchD_CODE_5001_caseD_42;
      case 0x43:
        goto switchD_CODE_5001_caseD_43;
      case 0x44:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (cVar13 < '\0') {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
        goto code_c0x50d0;
      case 0x45:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x50d3;
      case 0x46:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar3 = bVar3 + 1;
        goto code_c0x50d3;
      case 0x47:
        goto switchD_CODE_5001_caseD_47;
      case 0x48:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bINTMEM2c = bVar3;
        goto code_c0x50dc;
      case 0x49:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x50df;
      case 0x4a:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = bVar8 >> 1 | bVar8 << 7;
        goto code_c0x50df;
      case 0x4b:
        goto switchD_CODE_5001_caseD_4b;
      case 0x4c:
        goto switchD_CODE_5001_caseD_4c;
      case 0x4d:
        goto switchD_CODE_5001_caseD_4d;
      case 0x4e:
                    /* WARNING: This code block may not be properly labeled as switch case */
        _8_1 = 1;
        _9_0 = 1;
        return (bVar8 | param_5) - (param_3 - (cVar13 >> 7));
      case 0x4f:
                    /* WARNING: This code block may not be properly labeled as switch case */
        nop();
        _8_1 = 1;
        _9_0 = 1;
        halt_baddata();
      case 0x50:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x51:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x52:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x53:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x54:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x55:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x56:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x57:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x58:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = 1;
      case 0x59:
                    /* WARNING: This code block may not be properly labeled as switch case */
        *pbVar15 = bVar8;
        DAT_EXTMEM_0edd = 0;
switchD_CODE_5001_caseD_5b:
        while( true ) {
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_5c:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = *pbVar15;
          cVar13 = '\0';
          bVar8 = param_5;
switchD_CODE_5001_caseD_5d:
                    /* WARNING: This code block may not be properly labeled as switch case */
          if (0xfU - (cVar13 >> 7) <= bVar8) break;
LAB_CODE_5120:
          bVar7 = *pbVar15;
          bVar8 = bVar7;
switchD_CODE_5001_caseD_60:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar1 = 0x17 < bVar8;
          pbVar15 = (byte *)(ushort)(bVar8 - 0x18);
          bVar8 = 0;
code_c0x5127:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)CONCAT11(bVar8 + ('\x02' - ((bVar1 << 7) >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_63:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_4 = *pbVar15;
          cVar13 = (0x3d < bVar7) << 7;
          bVar8 = bVar7 - 0x3e;
code_c0x5130:
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
code_c0x5133:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)CONCAT11(bVar8 + ('\b' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_67:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = *pbVar15 | param_4;
switchD_CODE_5001_caseD_68:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = (0xc4 < param_5) << 7;
          bVar8 = param_5 + 0x3b;
switchD_CODE_5001_caseD_69:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
switchD_CODE_5001_caseD_6a:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *(byte *)CONCAT11(bVar8 + ('\x01' - (cVar13 >> 7)),(char)pbVar15) | bVar7;
switchD_CODE_5001_caseD_6c:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = bVar8;
code_c0x5147:
          bVar8 = 1;
switchD_CODE_5001_caseD_6d:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = CARRY1(bVar8,param_5) << 7;
          pbVar15 = (byte *)(ushort)(bVar8 + param_5);
switchD_CODE_5001_caseD_6e:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = -(cVar13 >> 7);
switchD_CODE_5001_caseD_6f:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *(byte *)CONCAT11(bVar8,(char)pbVar15);
switchD_CODE_5001_caseD_70:
                    /* WARNING: This code block may not be properly labeled as switch case */
          DAT_EXTMEM_0edf = bVar8 | bVar7;
code_c0x5157:
          bVar8 = 0;
switchD_CODE_5001_caseD_72:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_0ede;
switchD_CODE_5001_caseD_73:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *pbVar15 = bVar8;
          while( true ) {
            pbVar15 = (byte *)0xede;
            bVar5 = DAT_EXTMEM_0ede;
            bVar8 = DAT_EXTMEM_0ede;
switchD_CODE_5001_caseD_75:
                    /* WARNING: This code block may not be properly labeled as switch case */
            cVar13 = (bVar8 < 6) << 7;
switchD_CODE_5001_caseD_76:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_5 = bVar5;
            if (-1 < cVar13) break;
LAB_CODE_5169:
            pbVar15 = pbVar15 + 1;
switchD_CODE_5001_caseD_78:
                    /* WARNING: This code block may not be properly labeled as switch case */
            if ((*pbVar15 & 1) == 1) {
LAB_CODE_5171:
                    /* WARNING: This code block may not be properly labeled as switch case */
              DAT_EXTMEM_0ee2 = '\0';
switchD_CODE_5001_caseD_7c:
                    /* WARNING: This code block may not be properly labeled as switch case */
              pbVar15 = &DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_7d:
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar7 = *pbVar15;
              bVar8 = param_5;
switchD_CODE_5001_caseD_7e:
                    /* WARNING: This code block may not be properly labeled as switch case */
              uVar2 = CONCAT11(0x15,bVar8);
switchD_CODE_5001_caseD_7f:
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar8 = (char)uVar2 * (char)(uVar2 >> 8);
              cVar13 = (0x53 < bVar8) << 7;
              bVar8 = bVar8 + 0xac;
switchD_CODE_5001_caseD_80:
                    /* WARNING: This code block may not be properly labeled as switch case */
              pbVar15 = (byte *)(ushort)bVar8;
              bVar8 = 0;
switchD_CODE_5001_caseD_81:
                    /* WARNING: This code block may not be properly labeled as switch case */
              cVar13 = bVar8 + ('+' - (cVar13 >> 7));
              bVar8 = (byte)pbVar15;
              pbVar15 = (byte *)CONCAT11(cVar13,bVar8);
switchD_CODE_5001_caseD_83:
                    /* WARNING: This code block may not be properly labeled as switch case */
              cVar13 = CARRY1(bVar8,bVar7) << 7;
              pbVar15 = (byte *)CONCAT11((char)((ushort)pbVar15 >> 8),bVar8 + bVar7);
switchD_CODE_5001_caseD_84:
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar8 = (char)((ushort)pbVar15 >> 8) - (cVar13 >> 7);
switchD_CODE_5001_caseD_85:
                    /* WARNING: This code block may not be properly labeled as switch case */
              pbVar15 = (byte *)CONCAT11(bVar8,(char)pbVar15);
              bVar8 = 0;
switchD_CODE_5001_caseD_86:
                    /* WARNING: This code block may not be properly labeled as switch case */
              DAT_EXTMEM_0ee0 = pbVar15[bVar8];
              bVar8 = param_5;
switchD_CODE_5001_caseD_88:
                    /* WARNING: This code block may not be properly labeled as switch case */
              uVar2 = CONCAT11(0x15,bVar8);
switchD_CODE_5001_caseD_89:
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar8 = (char)uVar2 * (char)(uVar2 >> 8);
              cVar13 = (0xd5 < bVar8) << 7;
              bVar8 = bVar8 + 0x2a;
switchD_CODE_5001_caseD_8a:
                    /* WARNING: This code block may not be properly labeled as switch case */
              pbVar15 = (byte *)(ushort)bVar8;
              bVar8 = 0;
switchD_CODE_5001_caseD_8b:
                    /* WARNING: This code block may not be properly labeled as switch case */
              cVar13 = bVar8 + (',' - (cVar13 >> 7));
              bVar8 = (byte)pbVar15;
              pbVar15 = (byte *)CONCAT11(cVar13,bVar8);
switchD_CODE_5001_caseD_8d:
                    /* WARNING: This code block may not be properly labeled as switch case */
              cVar13 = CARRY1(bVar8,bVar7) << 7;
              pbVar15 = (byte *)CONCAT11((char)((ushort)pbVar15 >> 8),bVar8 + bVar7);
switchD_CODE_5001_caseD_8e:
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar8 = (char)((ushort)pbVar15 >> 8) - (cVar13 >> 7);
switchD_CODE_5001_caseD_8f:
                    /* WARNING: This code block may not be properly labeled as switch case */
              pbVar15 = (byte *)CONCAT11(bVar8,(char)pbVar15);
              bVar8 = 0;
switchD_CODE_5001_caseD_90:
                    /* WARNING: This code block may not be properly labeled as switch case */
              DAT_EXTMEM_0ee1 = pbVar15[bVar8];
              pbVar15 = &DAT_EXTMEM_0ee1;
                    /* WARNING: This code block may not be properly labeled as switch case */
              bVar8 = DAT_EXTMEM_0ee1;
              if (_4_3 == '\0') {
switchD_CODE_5001_caseD_a2:
                    /* WARNING: This code block may not be properly labeled as switch case */
                param_5 = bVar8;
                bVar8 = DAT_EXTMEM_0ee0;
switchD_CODE_5001_caseD_a4:
                    /* WARNING: This code block may not be properly labeled as switch case */
                puVar11['\x01'] = 0xf3;
                puVar11['\x02'] = 0x51;
                FUN_CODE_4736(bVar8,1,param_5);
              }
              else {
code_c0x51ba:
                bVar8 = *pbVar15;
switchD_CODE_5001_caseD_93:
                    /* WARNING: This code block may not be properly labeled as switch case */
                param_5 = bVar8;
switchD_CODE_5001_caseD_95:
                    /* WARNING: This code block may not be properly labeled as switch case */
                puVar11['\x01'] = 0xc6;
                puVar11['\x02'] = 0x51;
                FUN_CODE_4736(0,param_5);
                bVar8 = DAT_EXTMEM_0ee1;
                    /* WARNING: This code block may not be properly labeled as switch case */
switchD_CODE_5001_caseD_98:
                    /* WARNING: This code block may not be properly labeled as switch case */
                param_5 = bVar8;
switchD_CODE_5001_caseD_9a:
                    /* WARNING: This code block may not be properly labeled as switch case */
                puVar11['\x01'] = 0xd5;
                puVar11['\x02'] = 0x51;
                FUN_CODE_a5fe(0,param_5);
                    /* WARNING: This code block may not be properly labeled as switch case */
                bVar8 = DAT_EXTMEM_0ee1;
switchD_CODE_5001_caseD_9d:
                    /* WARNING: This code block may not be properly labeled as switch case */
                param_5 = bVar8;
                bVar8 = DAT_EXTMEM_0ee0;
switchD_CODE_5001_caseD_9f:
                    /* WARNING: This code block may not be properly labeled as switch case */
                puVar11['\x01'] = 0xe2;
                puVar11['\x02'] = 0x51;
                FUN_CODE_6b03(bVar8,param_5);
switchD_CODE_5001_caseD_a0:
                    /* WARNING: This code block may not be properly labeled as switch case */
              }
            }
LAB_CODE_51f3:
            pbVar15 = &DAT_EXTMEM_0edf;
            bVar8 = DAT_EXTMEM_0edf;
                    /* WARNING: This code block may not be properly labeled as switch case */
switchD_CODE_5001_caseD_a7:
                    /* WARNING: This code block may not be properly labeled as switch case */
            *pbVar15 = bVar8 >> 1;
switchD_CODE_5001_caseD_a8:
                    /* WARNING: This code block may not be properly labeled as switch case */
            pbVar15 = &DAT_EXTMEM_0ede;
switchD_CODE_5001_caseD_a9:
                    /* WARNING: This code block may not be properly labeled as switch case */
            *pbVar15 = *pbVar15 + 1;
switchD_CODE_5001_caseD_aa:
                    /* WARNING: This code block may not be properly labeled as switch case */
          }
switchD_CODE_5001_caseD_ab:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_ac:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *pbVar15 = *pbVar15 + 1;
switchD_CODE_5001_caseD_ad:
                    /* WARNING: This code block may not be properly labeled as switch case */
        }
switchD_CODE_5001_caseD_ae:
                    /* WARNING: This code block may not be properly labeled as switch case */
        DAT_EXTMEM_0edd = 0;
LAB_CODE_5211:
        while( true ) {
          pbVar15 = &DAT_EXTMEM_0edd;
          bVar8 = DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_b1:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = bVar8;
          if (0xe < param_5) break;
switchD_CODE_5001_caseD_b3:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = *pbVar15;
          cVar13 = (0x3d < bVar7) << 7;
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)(bVar7 - 0x3e);
switchD_CODE_5001_caseD_b5:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = 0;
code_c0x5222:
          bVar8 = bVar8 + ('\b' - (cVar13 >> 7));
switchD_CODE_5001_caseD_b6:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)CONCAT11(bVar8,(char)pbVar15);
          bVar8 = *pbVar15;
switchD_CODE_5001_caseD_b7:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *pbVar15 = bVar8 >> 1;
switchD_CODE_5001_caseD_b8:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = (0x17 < bVar7) << 7;
          bVar8 = bVar7 - 0x18;
switchD_CODE_5001_caseD_b9:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
switchD_CODE_5001_caseD_ba:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pcVar16 = (char *)CONCAT11(bVar8 + ('\x02' - (cVar13 >> 7)),(char)pbVar15);
          *pcVar16 = *pcVar16 * '\x02';
          bVar8 = param_5;
switchD_CODE_5001_caseD_bd:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = (bVar8 == 0) << 7;
switchD_CODE_5001_caseD_be:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = DAT_EXTMEM_0edd;
          if (-1 < cVar13) {
switchD_CODE_5001_caseD_c0:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_5 = bVar8;
            cVar13 = (0xc4 < param_5) << 7;
            bVar8 = param_5 + 0x3b;
switchD_CODE_5001_caseD_c1:
                    /* WARNING: This code block may not be properly labeled as switch case */
            pbVar15 = (byte *)(ushort)bVar8;
            bVar8 = 0;
switchD_CODE_5001_caseD_c2:
                    /* WARNING: This code block may not be properly labeled as switch case */
            bVar7 = *(byte *)CONCAT11(bVar8 + ('\x01' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_c4:
                    /* WARNING: This code block may not be properly labeled as switch case */
            cVar13 = (0xc5 < param_5) << 7;
            bVar8 = param_5 + 0x3a;
switchD_CODE_5001_caseD_c5:
                    /* WARNING: This code block may not be properly labeled as switch case */
            pbVar15 = (byte *)(ushort)bVar8;
            bVar8 = 0;
switchD_CODE_5001_caseD_c6:
                    /* WARNING: This code block may not be properly labeled as switch case */
            *(byte *)CONCAT11(bVar8 + ('\x01' - (cVar13 >> 7)),(char)pbVar15) = bVar7;
          }
switchD_CODE_5001_caseD_c8:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_c9:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = *pbVar15;
          cVar13 = '\0';
          bVar8 = param_5;
switchD_CODE_5001_caseD_ca:
                    /* WARNING: This code block may not be properly labeled as switch case */
          if (bVar8 < 0x14U - (cVar13 >> 7)) {
code_c0x5264:
            bVar7 = 0;
switchD_CODE_5001_caseD_cc:
                    /* WARNING: This code block may not be properly labeled as switch case */
            cVar13 = '\0';
            bVar8 = 0xd;
switchD_CODE_5001_caseD_cd:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_4 = param_5 - (cVar13 >> 7);
            cVar13 = (bVar8 < param_4) << 7;
            param_4 = bVar8 - param_4;
            bVar8 = 0;
switchD_CODE_5001_caseD_ce:
                    /* WARNING: This code block may not be properly labeled as switch case */
            bVar3 = bVar8 - (bVar7 - (cVar13 >> 7));
            cVar13 = (0xfe < param_4) << 7;
            pbVar15 = (byte *)(ushort)(param_4 + 1);
            bVar8 = 0;
switchD_CODE_5001_caseD_d1:
                    /* WARNING: This code block may not be properly labeled as switch case */
            pbVar15 = (byte *)CONCAT11(bVar8 + (bVar3 - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_d2:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_4 = *pbVar15;
            cVar13 = '\0';
switchD_CODE_5001_caseD_d3:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_5 = param_5 - (cVar13 >> 7);
            cVar13 = (0xe < param_5) << 7;
            bVar8 = 0xe - param_5;
switchD_CODE_5001_caseD_d4:
                    /* WARNING: This code block may not be properly labeled as switch case */
            param_5 = bVar8;
            bVar8 = -(bVar7 - (cVar13 >> 7));
switchD_CODE_5001_caseD_d5:
                    /* WARNING: This code block may not be properly labeled as switch case */
            bVar7 = bVar8;
            bVar8 = 1;
switchD_CODE_5001_caseD_d6:
                    /* WARNING: This code block may not be properly labeled as switch case */
            cVar13 = CARRY1(bVar8,param_5) << 7;
            pbVar15 = (byte *)(ushort)(bVar8 + param_5);
switchD_CODE_5001_caseD_d7:
                    /* WARNING: This code block may not be properly labeled as switch case */
            bVar8 = 0;
code_c0x5289:
            bVar8 = bVar8 + (bVar7 - (cVar13 >> 7));
switchD_CODE_5001_caseD_d8:
                    /* WARNING: This code block may not be properly labeled as switch case */
            pbVar15 = (byte *)CONCAT11(bVar8,(char)pbVar15);
            bVar8 = param_4;
switchD_CODE_5001_caseD_d9:
                    /* WARNING: This code block may not be properly labeled as switch case */
            *pbVar15 = bVar8;
          }
          pbVar15 = &DAT_EXTMEM_0edd;
          bVar8 = DAT_EXTMEM_0edd;
code_c0x5292:
          bVar8 = bVar8 + 1;
switchD_CODE_5001_caseD_db:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *pbVar15 = bVar8;
        }
        bVar8 = 0;
        DAT_EXTMEM_0149 = 0;
switchD_CODE_5001_caseD_de:
                    /* WARNING: This code block may not be properly labeled as switch case */
        pbVar15 = (byte *)0x1;
switchD_CODE_5001_caseD_df:
                    /* WARNING: This code block may not be properly labeled as switch case */
        *pbVar15 = bVar8;
        DAT_EXTMEM_0edd = bVar8;
switchD_CODE_5001_caseD_e2:
        do {
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = bVar8;
          cVar13 = (0x3d < param_5) << 7;
          bVar8 = param_5 - 0x3e;
switchD_CODE_5001_caseD_e3:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
switchD_CODE_5001_caseD_e4:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = *(byte *)CONCAT11(bVar8 + ('\b' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_e6:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = (0xc4 < param_5) << 7;
          bVar8 = param_5 + 0x3b;
switchD_CODE_5001_caseD_e7:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
switchD_CODE_5001_caseD_e8:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *(byte *)CONCAT11(bVar8 + ('\x01' - (cVar13 >> 7)),(char)pbVar15) | bVar7;
switchD_CODE_5001_caseD_ea:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = bVar8;
          bVar4 = DAT_EXTMEM_0edd;
          bVar8 = DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_ec:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar1 = 0x17 < bVar8;
          pbVar15 = (byte *)(ushort)(bVar8 - 0x18);
          bVar8 = 0;
          bVar7 = bVar4;
code_c0x52cb:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)CONCAT11(bVar8 + ('\x02' - ((bVar1 << 7) >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_ef:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = *pbVar15 | param_5;
switchD_CODE_5001_caseD_f0:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = (0xc4 < bVar7) << 7;
          bVar8 = bVar7 + 0x3b;
switchD_CODE_5001_caseD_f1:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)bVar8;
          bVar8 = 0;
switchD_CODE_5001_caseD_f2:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *(byte *)CONCAT11(bVar8 + ('\x01' - (cVar13 >> 7)),(char)pbVar15) = param_5;
switchD_CODE_5001_caseD_f4:
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = &DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_f5:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *pbVar15;
code_c0x52e2:
          param_5 = bVar8;
          cVar13 = (0x3d < param_5) << 7;
                    /* WARNING: This code block may not be properly labeled as switch case */
          pbVar15 = (byte *)(ushort)(param_5 - 0x3e);
switchD_CODE_5001_caseD_f7:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = 0;
code_c0x52e8:
          bVar8 = bVar8 + ('\b' - (cVar13 >> 7));
switchD_CODE_5001_caseD_f8:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *(byte *)CONCAT11(bVar8,(char)pbVar15);
switchD_CODE_5001_caseD_f9:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar7 = bVar8;
          bVar8 = 1;
switchD_CODE_5001_caseD_fa:
                    /* WARNING: This code block may not be properly labeled as switch case */
          cVar13 = CARRY1(bVar8,param_5) << 7;
          pbVar15 = (byte *)(ushort)(bVar8 + param_5);
switchD_CODE_5001_caseD_fb:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = -(cVar13 >> 7);
switchD_CODE_5001_caseD_fc:
                    /* WARNING: This code block may not be properly labeled as switch case */
          bVar8 = *(byte *)CONCAT11(bVar8,(char)pbVar15);
switchD_CODE_5001_caseD_fd:
                    /* WARNING: This code block may not be properly labeled as switch case */
          param_5 = bVar8 | bVar7;
          bVar8 = DAT_EXTMEM_0edd;
switchD_CODE_5001_caseD_ff:
                    /* WARNING: This code block may not be properly labeled as switch case */
          *(byte *)CONCAT11(-(((0xfe < bVar8) << 7) >> 7),bVar8 + 1) =
               *(byte *)CONCAT11('\x02' - (((0x17 < bVar8) << 7) >> 7),bVar8 - 0x18) | param_5;
          DAT_EXTMEM_0edd = DAT_EXTMEM_0edd + 1;
          bVar8 = DAT_EXTMEM_0edd;
        } while (DAT_EXTMEM_0edd != 0xf);
        if (DAT_EXTMEM_0ee2 != '\0') {
          _f_7 = 1;
        }
        bVar3 = DAT_EXTMEM_0892 ^ 0xd;
        if (bVar3 == 0) {
          bVar8 = DAT_EXTMEM_08ba + 1;
          bVar3 = DAT_EXTMEM_08ba - 5;
          DAT_EXTMEM_08ba = bVar8;
          if (5 < bVar8) {
            DAT_EXTMEM_08ba = 0;
            if (_4_7 != '\0') {
              _4_7 = 0;
              DAT_EXTMEM_08c8 = DAT_EXTMEM_08c8 | 1;
              DAT_EXTMEM_02ee = DAT_EXTMEM_02ee | 1;
              DAT_EXTMEM_0141 = DAT_EXTMEM_0141 | 1;
              DAT_EXTMEM_0007 = DAT_EXTMEM_0007 | 1;
              return DAT_EXTMEM_0007;
            }
            _4_7 = '\x01';
            DAT_EXTMEM_08c8 = DAT_EXTMEM_08c8 | 0x20;
            DAT_EXTMEM_02ee = DAT_EXTMEM_02ee | 0x20;
            DAT_EXTMEM_0141 = DAT_EXTMEM_0141 | 0x20;
            bVar3 = DAT_EXTMEM_0007 | 0x20;
            DAT_EXTMEM_0007 = bVar3;
          }
        }
        return bVar3;
      case 0x5a:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (param_4 != 1) {
                    /* WARNING: Bad instruction - Truncating control flow here */
          halt_baddata();
        }
      case 0x5b:
        goto switchD_CODE_5001_caseD_5b;
      case 0x5c:
        goto switchD_CODE_5001_caseD_5c;
      case 0x5d:
        goto switchD_CODE_5001_caseD_5d;
      case 0x5e:
        goto switchD_CODE_5001_caseD_ae;
      case 0x5f:
        goto LAB_CODE_5120;
      case 0x60:
        goto switchD_CODE_5001_caseD_60;
      case 0x61:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar1 = (bool)(bVar1 & bVar8 >> 4 & 1);
        goto code_c0x5127;
      case 0x62:
        _8_1 = 1;
        _9_0 = 1;
        halt_baddata();
      case 99:
        goto switchD_CODE_5001_caseD_63;
      case 100:
                    /* WARNING: This code block may not be properly labeled as switch case */
        _5_6 = 0;
        goto code_c0x5130;
      case 0x65:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x5133;
      case 0x66:
        goto code_c0x5133;
      case 0x67:
        goto switchD_CODE_5001_caseD_67;
      case 0x68:
        goto switchD_CODE_5001_caseD_68;
      case 0x69:
        goto switchD_CODE_5001_caseD_69;
      case 0x6a:
        goto switchD_CODE_5001_caseD_6a;
      case 0x6b:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x5144);
        goto switchD_CODE_5001_caseD_6a;
      case 0x6c:
        goto switchD_CODE_5001_caseD_6c;
      case 0x6d:
        goto switchD_CODE_5001_caseD_6d;
      case 0x6e:
        goto switchD_CODE_5001_caseD_6e;
      case 0x6f:
        goto switchD_CODE_5001_caseD_6f;
      case 0x70:
        goto switchD_CODE_5001_caseD_70;
      case 0x71:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_5 = param_5 - 1;
        if (param_5 != 0) goto code_c0x5147;
        goto code_c0x5157;
      case 0x72:
        goto switchD_CODE_5001_caseD_72;
      case 0x73:
        goto switchD_CODE_5001_caseD_73;
      case 0x74:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar7 = bVar3;
        bVar5 = bVar8;
        if (bVar3 != 0) goto switchD_CODE_5001_caseD_6a;
      case 0x75:
        goto switchD_CODE_5001_caseD_75;
      case 0x76:
        goto switchD_CODE_5001_caseD_76;
      case 0x77:
                    /* WARNING: This code block may not be properly labeled as switch case */
        BANK0_R3 = BANK0_R3 & bVar8;
        goto LAB_CODE_5169;
      case 0x78:
        goto switchD_CODE_5001_caseD_78;
      case 0x79:
        goto LAB_CODE_51f3;
      case 0x7a:
                    /* WARNING: This code block may not be properly labeled as switch case */
        *(byte *)(ushort)param_2 = bVar8;
        goto LAB_CODE_5171;
      case 0x7b:
        goto LAB_CODE_5171;
      case 0x7c:
        goto switchD_CODE_5001_caseD_7c;
      case 0x7d:
        goto switchD_CODE_5001_caseD_7d;
      case 0x7e:
        goto switchD_CODE_5001_caseD_7e;
      case 0x7f:
        goto switchD_CODE_5001_caseD_7f;
      case 0x80:
        goto switchD_CODE_5001_caseD_80;
      case 0x81:
        goto switchD_CODE_5001_caseD_81;
      case 0x82:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x5189);
        goto switchD_CODE_5001_caseD_81;
      case 0x83:
        goto switchD_CODE_5001_caseD_83;
      case 0x84:
        goto switchD_CODE_5001_caseD_84;
      case 0x85:
        goto switchD_CODE_5001_caseD_85;
      case 0x86:
        goto switchD_CODE_5001_caseD_86;
      case 0x87:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_86;
      case 0x88:
        goto switchD_CODE_5001_caseD_88;
      case 0x89:
        goto switchD_CODE_5001_caseD_89;
      case 0x8a:
        goto switchD_CODE_5001_caseD_8a;
      case 0x8b:
        goto switchD_CODE_5001_caseD_8b;
      case 0x8c:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x51a7);
        goto switchD_CODE_5001_caseD_8b;
      case 0x8d:
        goto switchD_CODE_5001_caseD_8d;
      case 0x8e:
        goto switchD_CODE_5001_caseD_8e;
      case 0x8f:
        goto switchD_CODE_5001_caseD_8f;
      case 0x90:
        goto switchD_CODE_5001_caseD_90;
      case 0x91:
        *pbVar15 = bVar8;
        puVar11['\x01'] = 0xf4;
        puVar11['\x02'] = 0x57;
        func_0xa424();
        goto code_c0x57e0;
      case 0x92:
        goto code_c0x51ba;
      case 0x93:
        goto switchD_CODE_5001_caseD_93;
      case 0x94:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_93;
      case 0x95:
        goto switchD_CODE_5001_caseD_95;
      case 0x96:
        goto switchD_CODE_5001_caseD_95;
      case 0x97:
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto code_c0x57e0;
      case 0x98:
        goto switchD_CODE_5001_caseD_98;
      case 0x99:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_98;
      case 0x9a:
        goto switchD_CODE_5001_caseD_9a;
      case 0x9b:
                    /* WARNING: Bad instruction - Truncating control flow here */
                    /* WARNING: This code block may not be properly labeled as switch case */
        halt_baddata();
      case 0x9c:
        goto code_c0x57e0;
      case 0x9d:
        goto switchD_CODE_5001_caseD_9d;
      case 0x9e:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_9d;
      case 0x9f:
        goto switchD_CODE_5001_caseD_9f;
      case 0xa0:
        goto switchD_CODE_5001_caseD_a0;
      case 0xa1:
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto code_c0x57e0;
      case 0xa2:
        goto switchD_CODE_5001_caseD_a2;
      case 0xa3:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_a2;
      case 0xa4:
        goto switchD_CODE_5001_caseD_a4;
      case 0xa5:
        goto LAB_CODE_51f3;
      case 0xa6:
        goto code_c0x51f5;
      case 0xa7:
        goto switchD_CODE_5001_caseD_a7;
      case 0xa8:
        goto switchD_CODE_5001_caseD_a8;
      case 0xa9:
        goto switchD_CODE_5001_caseD_a9;
      case 0xaa:
        goto switchD_CODE_5001_caseD_aa;
      case 0xab:
        goto switchD_CODE_5001_caseD_ab;
      case 0xac:
        goto switchD_CODE_5001_caseD_ac;
      case 0xad:
        goto switchD_CODE_5001_caseD_ad;
      case 0xae:
        goto switchD_CODE_5001_caseD_ae;
      case 0xaf:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (param_4 != 1) {
                    /* WARNING: Call to offcut address within same function */
          puVar11['\x01'] = 3;
          puVar11['\x02'] = 0x52;
          func_0x525c();
          goto switchD_CODE_5001_caseD_ab;
        }
        goto LAB_CODE_5211;
      case 0xb0:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_4 = param_4 - 1;
        if (param_4 == 0) goto switchD_CODE_5001_caseD_b1;
code_c0x51f5:
        param_5 = param_5 - 1;
        if (param_5 == 0) goto switchD_CODE_5001_caseD_a7;
code_c0x57e0:
        do {
          puVar11['\x01'] = 0xe4;
          puVar11['\x02'] = 0x57;
          FUN_CODE_4392(param_4);
          *pbVar15 = param_5;
          bVar3 = (byte)((ushort)DAT_EXTMEM_0eed * 0x12);
          puVar11['\x01'] =
               (char)((ushort)DAT_EXTMEM_0eed * 0x12 >> 8) + ('\x04' - (((0xd9 < bVar3) << 7) >> 7))
          ;
          puVar11['\x02'] = bVar3 + 0x26;
          pbVar15 = *(byte **)(puVar11 + '\x01');
          puVar11['\x01'] = 0xf;
          puVar11['\x02'] = 0x58;
          bVar3 = DAT_EXTMEM_0e20;
          FUN_CODE_4392(bEXTMEM0eee,3);
          *pbVar15 = bVar3;
          while( true ) {
            do {
              do {
                do {
                  do {
                    bVar8 = bEXTMEM0ee9;
                    bEXTMEM0ee9 = bEXTMEM0ee9 + 1;
                    if (4 < bEXTMEM0ee9) {
                      return bVar8 - 4;
                    }
                    IEN1 = 0;
                    puVar11['\x01'] = 0x6d;
                    puVar11['\x02'] = 0x56;
                    FUN_CODE_a0dd(0);
                    cVar13 = cEXTMEM0ec3 + bVar3;
                    bVar3 = 0x84;
                    puVar11['\x01'] = 0x7d;
                    puVar11['\x02'] = 0x56;
                    FUN_CODE_42ab(cVar13);
                    DAT_EXTMEM_0eed = *(byte *)((ushort)bVar3 + 0x2bac);
                    bEXTMEM0eeb = bVar3;
                  } while (0xe < DAT_EXTMEM_0eed);
                  IEN1 = 0;
                  bEXTMEM0eee = *(byte *)((ushort)bVar3 + 0x2c2a);
                  puVar11['\x01'] = 0xa5;
                  puVar11['\x02'] = 0x56;
                  FUN_CODE_a0dd();
                  bVar7 = 0xc0;
                  puVar11['\x01'] = 0xac;
                  puVar11['\x02'] = 0x56;
                  FUN_CODE_42ab(0);
                  bVar8 = DAT_EXTMEM_0eed;
                  bVar9 = DAT_EXTMEM_0eed * '\x06' + 0x17;
                  bVar3 = bEXTMEM0eee;
                  bEXTMEM0eeb = bVar7;
                } while (*(char *)CONCAT11(-((CARRY1(bVar9,bEXTMEM0eee) << 7) >> 7) -
                                           (((0xe8 < DAT_EXTMEM_0eed * '\x06') << 7) >> 7),
                                           bVar9 + bEXTMEM0eee) != '\0');
                bVar3 = 1;
                cVar13 = BANK0_R7 + '\x01';
                while (cVar13 = cVar13 + -1, cVar13 != '\0') {
                  bVar3 = bVar3 << 1;
                }
              } while ((bVar3 & *(byte *)CONCAT11('\f' - (((5 < DAT_EXTMEM_0eed) << 7) >> 7),
                                                  DAT_EXTMEM_0eed - 6)) != 0);
              bVar3 = DAT_EXTMEM_0eed * '\x06' + 0x17;
              *(undefined1 *)
               CONCAT11(-((CARRY1(bVar3,bEXTMEM0eee) << 7) >> 7) -
                        (((0xe8 < DAT_EXTMEM_0eed * '\x06') << 7) >> 7),bVar3 + bEXTMEM0eee) = 0;
              puVar11['\x01'] = 0x2a;
              puVar11['\x02'] = 0x57;
              FUN_CODE_a5fe(1,bVar8);
              puVar11['\x01'] = 0x37;
              puVar11['\x02'] = 0x57;
              bVar3 = bEXTMEM0eee;
              FUN_CODE_7e03(DAT_EXTMEM_0eed);
            } while (bVar3 != 0);
            if (DAT_EXTMEM_011c != '\a') break;
            bVar3 = 0;
            do {
              bVar8 = (byte)((ushort)bEXTMEM0eeb * 3);
              bVar7 = bVar8 - 0x17;
              uVar10 = *(undefined1 *)
                        CONCAT11(((char)((ushort)bEXTMEM0eeb * 3 >> 8) +
                                 ('\'' - (((0x16 < bVar8) << 7) >> 7))) -
                                 ((CARRY1(bVar7,bVar3) << 7) >> 7),bVar7 + bVar3);
              bVar8 = (byte)((ushort)DAT_EXTMEM_0eed * 0x12);
              puVar11['\x01'] =
                   (char)((ushort)DAT_EXTMEM_0eed * 0x12 >> 8) +
                   ('\x04' - (((0xdb < bVar8) << 7) >> 7));
              puVar11['\x02'] = bVar8 + 0x24;
              bVar8 = puVar11['\x02'];
              cVar13 = puVar11['\x01'];
              puVar11['\x01'] = 0x89;
              puVar11['\x02'] = 0x57;
              FUN_CODE_4392(bEXTMEM0eee,3);
              *(undefined1 *)CONCAT11(cVar13 - ((CARRY1(bVar8,bVar3) << 7) >> 7),bVar8 + bVar3) =
                   uVar10;
              bVar3 = bVar3 + 1;
            } while (bVar3 != 3);
            bVar3 = 3;
          }
          bVar3 = (byte)((ushort)DAT_EXTMEM_0eed * 0x12);
          puVar11['\x01'] =
               (char)((ushort)DAT_EXTMEM_0eed * 0x12 >> 8) + ('\x04' - (((0xdb < bVar3) << 7) >> 7))
          ;
          puVar11['\x02'] = bVar3 + 0x24;
          puVar14 = *(undefined1 **)(puVar11 + '\x01');
          puVar11['\x01'] = 199;
          puVar11['\x02'] = 0x57;
          param_4 = bEXTMEM0eee;
          bVar3 = DAT_EXTMEM_0eed;
          uVar10 = DAT_EXTMEM_011d;
          FUN_CODE_4392(bEXTMEM0eee,3);
          *puVar14 = uVar10;
          bVar8 = (byte)((ushort)bVar3 * 0x12);
          pbVar15 = (byte *)CONCAT11((char)((ushort)bVar3 * 0x12 >> 8) +
                                     ('\x04' - (((0xda < bVar8) << 7) >> 7)),bVar8 + 0x25);
          param_5 = bEXTMEM0000;
        } while( true );
      case 0xb1:
        goto switchD_CODE_5001_caseD_b1;
      case 0xb2:
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto switchD_CODE_5001_caseD_b1;
      case 0xb3:
        goto switchD_CODE_5001_caseD_b3;
      case 0xb4:
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x5222;
      case 0xb5:
        goto switchD_CODE_5001_caseD_b5;
      case 0xb6:
        goto switchD_CODE_5001_caseD_b6;
      case 0xb7:
        goto switchD_CODE_5001_caseD_b7;
      case 0xb8:
        goto switchD_CODE_5001_caseD_b8;
      case 0xb9:
        goto switchD_CODE_5001_caseD_b9;
      case 0xba:
        goto switchD_CODE_5001_caseD_ba;
      case 0xbb:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x5234);
        goto switchD_CODE_5001_caseD_ba;
      case 0xbc:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *pbVar15;
        goto switchD_CODE_5001_caseD_ba;
      case 0xbd:
        goto switchD_CODE_5001_caseD_bd;
      case 0xbe:
        goto switchD_CODE_5001_caseD_be;
      case 0xbf:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar7 = bVar3 + 2;
        if (param_4 != 1) goto code_c0x5222;
      case 0xc0:
        goto switchD_CODE_5001_caseD_c0;
      case 0xc1:
        goto switchD_CODE_5001_caseD_c1;
      case 0xc2:
        goto switchD_CODE_5001_caseD_c2;
      case 0xc3:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x524c);
        goto switchD_CODE_5001_caseD_c2;
      case 0xc4:
        goto switchD_CODE_5001_caseD_c4;
      case 0xc5:
        goto switchD_CODE_5001_caseD_c5;
      case 0xc6:
        goto switchD_CODE_5001_caseD_c6;
      case 199:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x5258);
        goto switchD_CODE_5001_caseD_c6;
      case 200:
        goto switchD_CODE_5001_caseD_c8;
      case 0xc9:
        goto switchD_CODE_5001_caseD_c9;
      case 0xca:
        goto switchD_CODE_5001_caseD_ca;
      case 0xcb:
        goto code_c0x5264;
      case 0xcc:
        goto switchD_CODE_5001_caseD_cc;
      case 0xcd:
        goto switchD_CODE_5001_caseD_cd;
      case 0xce:
        goto switchD_CODE_5001_caseD_ce;
      case 0xcf:
        bVar7 = bVar8;
        bVar8 = bVar3;
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto switchD_CODE_5001_caseD_f;
      case 0xd0:
        goto switchD_CODE_5001_caseD_d0;
      case 0xd1:
        goto switchD_CODE_5001_caseD_d1;
      case 0xd2:
        goto switchD_CODE_5001_caseD_d2;
      case 0xd3:
        goto switchD_CODE_5001_caseD_d3;
      case 0xd4:
        goto switchD_CODE_5001_caseD_d4;
      case 0xd5:
        goto switchD_CODE_5001_caseD_d5;
      case 0xd6:
        goto switchD_CODE_5001_caseD_d6;
      case 0xd7:
        goto switchD_CODE_5001_caseD_d7;
      case 0xd8:
        goto switchD_CODE_5001_caseD_d8;
      case 0xd9:
        goto switchD_CODE_5001_caseD_d9;
      case 0xda:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (param_4 == 1) goto code_c0x5292;
switchD_CODE_5001_caseD_d0:
                    /* WARNING: This code block may not be properly labeled as switch case */
        cVar13 = (bVar1 & _e_4) << 7;
        nop();
        goto switchD_CODE_5001_caseD_d1;
      case 0xdb:
        goto switchD_CODE_5001_caseD_db;
      case 0xdc:
                    /* WARNING: This code block may not be properly labeled as switch case */
        puVar11['\x01'] = 0x98;
        puVar12 = puVar11 + '\x02';
        puVar11 = puVar11 + '\x02';
        *puVar12 = 0x52;
        goto code_c0x50e4;
      case 0xdd:
                    /* WARNING: This code block may not be properly labeled as switch case */
        goto LAB_CODE_508b;
      case 0xde:
        goto switchD_CODE_5001_caseD_de;
      case 0xdf:
        goto switchD_CODE_5001_caseD_df;
      case 0xe0:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = DAT_EXTMEM_0edd;
        if (param_4 != 1) goto LAB_CODE_5211;
        goto switchD_CODE_5001_caseD_e2;
      case 0xe1:
        goto switchD_CODE_5001_caseD_e1;
      case 0xe2:
        goto switchD_CODE_5001_caseD_e2;
      case 0xe3:
        goto switchD_CODE_5001_caseD_e3;
      case 0xe4:
        goto switchD_CODE_5001_caseD_e4;
      case 0xe5:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x52b2);
        goto switchD_CODE_5001_caseD_e4;
      case 0xe6:
        goto switchD_CODE_5001_caseD_e6;
      case 0xe7:
        goto switchD_CODE_5001_caseD_e7;
      case 0xe8:
        goto switchD_CODE_5001_caseD_e8;
      case 0xe9:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x52be);
        goto switchD_CODE_5001_caseD_e8;
      case 0xea:
        goto switchD_CODE_5001_caseD_ea;
      case 0xeb:
        goto switchD_CODE_5001_caseD_eb;
      case 0xec:
        goto switchD_CODE_5001_caseD_ec;
      case 0xed:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar1 = (bool)(bVar1 & bVar8 >> 4 & 1);
        goto code_c0x52cb;
      case 0xee:
                    /* WARNING: Bad instruction - Truncating control flow here */
        halt_baddata();
      case 0xef:
        goto switchD_CODE_5001_caseD_ef;
      case 0xf0:
        goto switchD_CODE_5001_caseD_f0;
      case 0xf1:
        goto switchD_CODE_5001_caseD_f1;
      case 0xf2:
        goto switchD_CODE_5001_caseD_f2;
      case 0xf3:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar8 = *(byte *)((uVar2 & 0xff) + 0x52dc);
        goto switchD_CODE_5001_caseD_f2;
      case 0xf4:
        goto switchD_CODE_5001_caseD_f4;
      case 0xf5:
        goto switchD_CODE_5001_caseD_f5;
      case 0xf6:
        cVar13 = (bVar1 & bVar8 >> 4 & 1) << 7;
        goto code_c0x52e8;
      case 0xf7:
        goto switchD_CODE_5001_caseD_f7;
      case 0xf8:
        goto switchD_CODE_5001_caseD_f8;
      case 0xf9:
        goto switchD_CODE_5001_caseD_f9;
      case 0xfa:
        goto switchD_CODE_5001_caseD_fa;
      case 0xfb:
        goto switchD_CODE_5001_caseD_fb;
      case 0xfc:
        goto switchD_CODE_5001_caseD_fc;
      case 0xfd:
        goto switchD_CODE_5001_caseD_fd;
      case 0xfe:
                    /* WARNING: This code block may not be properly labeled as switch case */
        if (param_4 == 1) goto switchD_CODE_5001_caseD_ff;
        param_4 = param_4 - 2;
        if (param_4 == 0) goto code_c0x52e2;
        bVar7 = bVar3 + 4;
switchD_CODE_5001_caseD_eb:
                    /* WARNING: This code block may not be properly labeled as switch case */
        param_4 = param_4 - 1;
        bVar4 = bVar8;
        if (param_4 == 0) goto switchD_CODE_5001_caseD_ec;
switchD_CODE_5001_caseD_e1:
                    /* WARNING: This code block may not be properly labeled as switch case */
        bVar7 = bVar7 + 1;
        param_4 = param_4 - 1;
        if (param_4 != 0) {
          nop();
          goto code_c0x5289;
        }
        goto switchD_CODE_5001_caseD_e2;
      case 0xff:
        goto switchD_CODE_5001_caseD_ff;
      }
      pbVar15 = &DAT_EXTMEM_09ac;
switchD_CODE_5001_caseD_e:
                    /* WARNING: This code block may not be properly labeled as switch case */
      bVar7 = *pbVar15;
      bVar8 = bVar3;
switchD_CODE_5001_caseD_f:
                    /* WARNING: This code block may not be properly labeled as switch case */
      pbVar15 = &DAT_CODE_abe3;
switchD_CODE_5001_caseD_10:
                    /* WARNING: This code block may not be properly labeled as switch case */
      param_4 = ~pbVar15[bVar8];
switchD_CODE_5001_caseD_11:
                    /* WARNING: This code block may not be properly labeled as switch case */
      DAT_EXTMEM_09ac = bVar7 | param_4;
      goto LAB_CODE_508b;
    }
  }
  goto LAB_CODE_50e5;
switchD_CODE_5001_caseD_18:
                    /* WARNING: This code block may not be properly labeled as switch case */
  if (!bVar1) goto code_c0x504c;
  goto code_c0x4fdc;
code_c0x504c:
  param_2 = param_2 + 1;
switchD_CODE_5001_caseD_19:
                    /* WARNING: This code block may not be properly labeled as switch case */
  puVar11['\x01'] = 0x4f;
  puVar11['\x02'] = 0x50;
  bVar8 = func_0x5574();
switchD_CODE_5001_caseD_1a:
                    /* WARNING: This code block may not be properly labeled as switch case */
  *pbVar15 = bVar8;
LAB_CODE_508b:
  cVar13 = (0xcd < bVar3) << 7;
  pbVar15 = (byte *)(ushort)(bVar3 + 0x32);
  bVar8 = 0;
code_c0x5091:
  pbVar15 = (byte *)CONCAT11(bVar8 + ('\f' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_31:
                    /* WARNING: This code block may not be properly labeled as switch case */
  param_5 = *pbVar15;
  cVar13 = '\0';
  bVar8 = param_5;
switchD_CODE_5001_caseD_32:
                    /* WARNING: This code block may not be properly labeled as switch case */
  if (bVar8 < 0xfeU - (cVar13 >> 7)) {
code_c0x509c:
    bVar8 = 0x32;
switchD_CODE_5001_caseD_34:
                    /* WARNING: This code block may not be properly labeled as switch case */
    cVar13 = CARRY1(bVar8,bVar3) << 7;
    pbVar15 = (byte *)(ushort)(bVar8 + bVar3);
switchD_CODE_5001_caseD_35:
                    /* WARNING: This code block may not be properly labeled as switch case */
    bVar8 = 0xc - (cVar13 >> 7);
switchD_CODE_5001_caseD_36:
                    /* WARNING: This code block may not be properly labeled as switch case */
    pbVar15 = (byte *)CONCAT11(bVar8,(char)pbVar15);
    bVar8 = *pbVar15;
switchD_CODE_5001_caseD_37:
                    /* WARNING: This code block may not be properly labeled as switch case */
    *pbVar15 = bVar8 - 1;
  }
  else {
LAB_CODE_50ab:
    if (param_5 == 0xff) {
code_c0x50af:
      cVar13 = (0xcd < bVar3) << 7;
      pbVar15 = (byte *)(ushort)(bVar3 + 0x32);
      bVar8 = 0;
code_c0x50b5:
      pbVar15 = (byte *)CONCAT11(bVar8 + ('\f' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_3d:
                    /* WARNING: This code block may not be properly labeled as switch case */
      *pbVar15 = 0xfe;
switchD_CODE_5001_caseD_3e:
                    /* WARNING: This code block may not be properly labeled as switch case */
    }
    else {
      cVar13 = (0xcd < bVar3) << 7;
      pbVar15 = (byte *)(ushort)(bVar3 + 0x32);
      bVar8 = 0;
code_c0x50c4:
      pbVar15 = (byte *)CONCAT11(bVar8 + ('\f' - (cVar13 >> 7)),(char)pbVar15);
switchD_CODE_5001_caseD_42:
                    /* WARNING: This code block may not be properly labeled as switch case */
      *pbVar15 = 0xff;
switchD_CODE_5001_caseD_43:
                    /* WARNING: This code block may not be properly labeled as switch case */
    }
  }
LAB_CODE_50e5:
  bVar3 = bVar3 + 1;
switchD_CODE_5001_caseD_4c:
                    /* WARNING: This code block may not be properly labeled as switch case */
  bVar8 = bVar3 ^ 0xd;
switchD_CODE_5001_caseD_4d:
                    /* WARNING: This code block may not be properly labeled as switch case */
  if (bVar8 == 0) {
    return 0;
  }
  goto LAB_CODE_4f9a;
}



===== FUN_CODE_5c49 CODE:5c49 size=520 =====

char FUN_CODE_5c49(void)

{
  ushort uVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte *pbVar6;
  char *pcVar7;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0edf = 1;
  DAT_EXTMEM_0edd = 0;
  do {
    for (DAT_EXTMEM_0ede = 0; bVar4 = DAT_EXTMEM_0edd, (DAT_EXTMEM_0ede < 6) << 7 < '\0';
        DAT_EXTMEM_0ede = DAT_EXTMEM_0ede + 1) {
      cVar2 = BANK0_R7 + '\x01';
      bVar4 = DAT_EXTMEM_0edf;
      while (cVar2 = cVar2 + -1, cVar2 != '\0') {
        bVar4 = bVar4 << 1;
      }
      if ((*(byte *)CONCAT11('\f' - (((5 < DAT_EXTMEM_0edd) << 7) >> 7),DAT_EXTMEM_0edd - 6) & bVar4
          ) == 0) {
        bVar4 = (byte)((ushort)DAT_EXTMEM_0edd * 0x12);
        uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0edd * 0x12 >> 8) +
                                    ('\x04' - (((0xdb < bVar4) << 7) >> 7)),bVar4 + 0x24);
        bVar4 = DAT_EXTMEM_0ede;
        bVar3 = DAT_EXTMEM_0edd;
        FUN_CODE_4392(3,DAT_EXTMEM_0ede);
        DAT_EXTMEM_0e43 = *uStack_1;
        bVar5 = (byte)((ushort)bVar3 * 0x12);
        pbVar6 = (byte *)CONCAT11((char)((ushort)bVar3 * 0x12 >> 8) +
                                  ('\x04' - (((0xda < bVar5) << 7) >> 7)),bVar5 + 0x25);
        FUN_CODE_4392(bVar4,3);
        DAT_EXTMEM_0e3f = *pbVar6;
        bVar4 = (byte)((ushort)DAT_EXTMEM_0edd * 0x12);
        uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0edd * 0x12 >> 8) +
                                    ('\x04' - (((0xd9 < bVar4) << 7) >> 7)),bVar4 + 0x26);
        bVar4 = DAT_EXTMEM_0ede;
        bVar3 = DAT_EXTMEM_0edd;
        FUN_CODE_4392(3);
        DAT_EXTMEM_0e3c = *uStack_1;
        bVar5 = bVar3 * '\x06' + 0x17;
        bVar4 = *(byte *)CONCAT11(-((CARRY1(bVar5,bVar4) << 7) >> 7) -
                                  (((0xe8 < bVar3 * '\x06') << 7) >> 7),bVar5 + bVar4);
        uVar1 = (ushort)DAT_EXTMEM_0e43 * (ushort)bVar4;
        cVar2 = '\x05';
        do {
          uVar1 = uVar1 >> 1;
          DAT_EXTMEM_011d = (undefined1)uVar1;
          cVar2 = cVar2 + -1;
        } while (cVar2 != '\0');
        uVar1 = (ushort)DAT_EXTMEM_0e3f * (ushort)bVar4;
        cVar2 = '\x05';
        do {
          uVar1 = uVar1 >> 1;
          uEXTMEM0000 = (undefined1)uVar1;
          cVar2 = cVar2 + -1;
        } while (cVar2 != '\0');
        bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
        uVar1 = (ushort)DAT_EXTMEM_0e3c *
                (ushort)*(byte *)CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                                          (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),
                                          bVar4 + DAT_EXTMEM_0ede);
        cVar2 = '\x05';
        do {
          uVar1 = uVar1 >> 1;
          DAT_EXTMEM_0e20 = (undefined1)uVar1;
          cVar2 = cVar2 + -1;
        } while (cVar2 != '\0');
        cVar2 = BANK0_R4;
        FUN_CODE_7e03(DAT_EXTMEM_0edd);
        if (cVar2 == '\0') {
          FUN_CODE_9819();
          FUN_CODE_6e62(0xedd);
        }
        if (DAT_EXTMEM_0892 == '\r') {
          bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
          if ((*(byte *)CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                                 (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),
                                 bVar4 + DAT_EXTMEM_0ede) < 2) << 7 < '\0') {
            bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
            *(undefined1 *)
             CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                      (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),bVar4 + DAT_EXTMEM_0ede) = 0;
          }
          else {
            bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
            pcVar7 = (char *)CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                                      (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),
                                      bVar4 + DAT_EXTMEM_0ede);
            *pcVar7 = *pcVar7 + -2;
          }
        }
        else {
          bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
          if (*(char *)CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                                (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),
                                bVar4 + DAT_EXTMEM_0ede) != '\0') {
            bVar4 = DAT_EXTMEM_0edd * '\x06' + 0x17;
            pcVar7 = (char *)CONCAT11(-((CARRY1(bVar4,DAT_EXTMEM_0ede) << 7) >> 7) -
                                      (((0xe8 < DAT_EXTMEM_0edd * '\x06') << 7) >> 7),
                                      bVar4 + DAT_EXTMEM_0ede);
            *pcVar7 = *pcVar7 + -1;
          }
        }
      }
    }
    DAT_EXTMEM_0edd = DAT_EXTMEM_0edd + 1;
  } while (DAT_EXTMEM_0edd < 0xf);
  return bVar4 - 0xe;
}



===== FUN_CODE_5e51 CODE:5e51 size=495 =====

void FUN_CODE_5e51(void)

{
  DAT_EXTMEM_ff81 = 8;
  DAT_EXTMEM_ff82 = 8;
  DAT_EXTMEM_ff83 = 8;
  DAT_EXTMEM_ff84 = 8;
  DAT_EXTMEM_ff85 = 8;
  DAT_EXTMEM_ff9c = 4;
  DAT_EXTMEM_ff98 = 0xb0;
  DAT_EXTMEM_ffb8 = 0;
  DAT_EXTMEM_ffa0 = 0xc3;
  DAT_EXTMEM_ffe8 = 0;
  DAT_EXTMEM_ffd0 = 0xc3;
  DAT_EXTMEM_ffb9 = 0;
  DAT_EXTMEM_ffa1 = 0xc4;
  DAT_EXTMEM_ffe9 = 0;
  DAT_EXTMEM_ffd1 = 0xc4;
  DAT_EXTMEM_ffba = 0;
  DAT_EXTMEM_ffa2 = 0xc5;
  DAT_EXTMEM_ffea = 0;
  DAT_EXTMEM_ffd2 = 0xc5;
  DAT_EXTMEM_ffbb = 0;
  DAT_EXTMEM_ffa3 = 0xc0;
  DAT_EXTMEM_ffeb = 0;
  DAT_EXTMEM_ffd3 = 0xc0;
  DAT_EXTMEM_ffbc = 0;
  DAT_EXTMEM_ffa4 = 0xc1;
  DAT_EXTMEM_ffec = 0;
  DAT_EXTMEM_ffd4 = 0xc1;
  DAT_EXTMEM_ffbd = 0;
  DAT_EXTMEM_ffa5 = 0xc2;
  DAT_EXTMEM_ffed = 0;
  DAT_EXTMEM_ffd5 = 0xc2;
  DAT_EXTMEM_ff87 = 8;
  DAT_EXTMEM_ff88 = 8;
  DAT_EXTMEM_ff89 = 8;
  DAT_EXTMEM_ff8a = 8;
  DAT_EXTMEM_ff8b = 8;
  DAT_EXTMEM_ff9d = 4;
  DAT_EXTMEM_ff99 = 0xb0;
  DAT_EXTMEM_ffbe = 0;
  DAT_EXTMEM_ffa6 = 0xba;
  DAT_EXTMEM_ffee = 0;
  DAT_EXTMEM_ffd6 = 0xba;
  DAT_EXTMEM_ffbf = 0;
  DAT_EXTMEM_ffa7 = 0xbb;
  DAT_EXTMEM_ffef = 0;
  DAT_EXTMEM_ffd7 = 0xbb;
  DAT_EXTMEM_ffc0 = 0;
  DAT_EXTMEM_ffa8 = 0xbc;
  DAT_EXTMEM_fff0 = 0;
  DAT_EXTMEM_ffd8 = 0xbc;
  DAT_EXTMEM_ffc1 = 0;
  DAT_EXTMEM_ffa9 = 0xbd;
  DAT_EXTMEM_fff1 = 0;
  DAT_EXTMEM_ffd9 = 0xbd;
  DAT_EXTMEM_ffc2 = 0;
  DAT_EXTMEM_ffaa = 0xbe;
  DAT_EXTMEM_fff2 = 0;
  DAT_EXTMEM_ffda = 0xbe;
  DAT_EXTMEM_ffc3 = 0;
  DAT_EXTMEM_ffab = 0xbf;
  DAT_EXTMEM_fff3 = 0;
  DAT_EXTMEM_ffdb = 0xbf;
  DAT_EXTMEM_ff8d = 8;
  DAT_EXTMEM_ff8e = 8;
  DAT_EXTMEM_ff8f = 8;
  DAT_EXTMEM_ff90 = 8;
  DAT_EXTMEM_ff91 = 8;
  DAT_EXTMEM_ff9e = 4;
  DAT_EXTMEM_ff9a = 0xb0;
  DAT_EXTMEM_ffc4 = 0;
  DAT_EXTMEM_ffac = 0xb4;
  DAT_EXTMEM_fff4 = 0;
  DAT_EXTMEM_ffdc = 0xb4;
  DAT_EXTMEM_ffc5 = 0;
  DAT_EXTMEM_ffad = 0xb5;
  DAT_EXTMEM_fff5 = 0;
  DAT_EXTMEM_ffdd = 0xb5;
  DAT_EXTMEM_ffc6 = 0;
  DAT_EXTMEM_ffae = 0xb6;
  DAT_EXTMEM_fff6 = 0;
  DAT_EXTMEM_ffde = 0xb6;
  DAT_EXTMEM_ffc7 = 0;
  DAT_EXTMEM_ffaf = 0xb7;
  DAT_EXTMEM_fff7 = 0;
  DAT_EXTMEM_ffdf = 0xb7;
  DAT_EXTMEM_ffc8 = 0;
  DAT_EXTMEM_ffb0 = 0xb8;
  DAT_EXTMEM_fff8 = 0;
  DAT_EXTMEM_ffe0 = 0xb8;
  DAT_EXTMEM_ffc9 = 0;
  DAT_EXTMEM_ffb1 = 0xb9;
  DAT_EXTMEM_fff9 = 0;
  DAT_EXTMEM_ffe1 = 0xb9;
  DAT_EXTMEM_ff80 = 0x89;
  DAT_EXTMEM_ff86 = 0x89;
  DAT_EXTMEM_ff8c = 0x89;
  FUN_CODE_a841(0,1);
  return;
}



===== FUN_CODE_6040 CODE:6040 size=487 =====

void FUN_CODE_6040(byte param_1,byte param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined2 uStack_1;
  
  BANK1_R7 = param_2;
  BANK2_R0 = param_1;
  if (_d_4 == '\0') {
    if (_e_3 == '\x01') {
      if (DAT_EXTMEM_031f != '\0') {
        _8_2 = 0;
        DAT_EXTMEM_08c0 = 1;
        uVar2 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        uVar3 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d10 = uVar2;
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(8);
        uVar2 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d11 = uVar3;
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(0x10);
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d12 = uVar2;
        FUN_CODE_6fe9(DAT_EXTMEM_02e0,uStack_1);
        if (DAT_EXTMEM_0317 == '\0') {
          FUN_CODE_ac69();
        }
        else {
          FUN_CODE_3a4f();
        }
        FUN_CODE_a9a8(6);
        _8_2 = 1;
        DAT_EXTMEM_08c0 = 0x81;
        uVar2 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        uVar3 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d10 = uVar2;
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(8);
        uVar2 = 0;
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d11 = uVar3;
        FUN_CODE_4392(DAT_EXTMEM_02e0,uStack_1,4);
        FUN_CODE_4345();
        FUN_CODE_431e(0x10);
        uStack_1 = (byte *)((ushort)(DAT_EXTMEM_0309 * '\x02' - 0x28) << 8);
        DAT_EXTMEM_0d12 = uVar2;
        FUN_CODE_6fe9(DAT_EXTMEM_02e0,uStack_1);
      }
      *(undefined1 *)CONCAT11('\r' - (((0xe8 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0x17)
           = 0;
      cVar1 = '\b' - (((0x66 < BANK1_R7) << 7) >> 7);
      uStack_1 = (byte *)CONCAT11(cVar1,BANK1_R7 + 0x99);
      *uStack_1 = *(byte *)CONCAT11(cVar1,BANK1_R7 + 0x99) & (&DAT_CODE_abe3)[BANK2_R0];
      return;
    }
    FUN_CODE_3108();
    FUN_CODE_6ffd();
    *(undefined1 *)CONCAT11('\x03' - (((0x59 < DAT_EXTMEM_02e0) << 7) >> 7),DAT_EXTMEM_02e0 + 0xa6)
         = 0;
  }
  return;
}



===== FUN_CODE_63f8 CODE:63f8 size=460 =====

byte FUN_CODE_63f8(void)

{
  bool bVar1;
  undefined1 uVar2;
  byte bVar3;
  
  bVar3 = DAT_SFR_9a;
  if ((bVar3 >> 2 & 1) != 0) {
    return bVar3;
  }
  if (DAT_EXTMEM_0317 != 0) {
    return DAT_EXTMEM_0317;
  }
  bVar1 = false;
  DAT_EXTMEM_0f01 = '\0';
  if (_a_0 != '\0') {
    _6_7 = 1;
    _a_0 = '\0';
    DAT_EXTMEM_0eff = 0;
    DAT_EXTMEM_09b7 = 2;
    DAT_EXTMEM_0f02 = 1;
    DAT_EXTMEM_0f03 = 9;
    DAT_EXTMEM_0f04 = 0xb7;
    bVar1 = true;
    goto LAB_CODE_6533;
  }
  if (_7_3 == '\0') {
    if (_7_4 == '\0') {
      if (_a_6 == '\0') {
        if (_9_0 != '\0') {
          _6_7 = 1;
          _9_0 = '\0';
          DAT_EXTMEM_0eff = 4;
          DAT_EXTMEM_09ab = 7;
          DAT_EXTMEM_0f02 = 1;
          DAT_EXTMEM_0f03 = 9;
          DAT_EXTMEM_0f04 = 0xab;
          bVar1 = true;
          DAT_EXTMEM_0f01 = '\x01';
          goto LAB_CODE_6533;
        }
        if (_b_2 == '\0') {
          if (_b_5 == '\0') goto LAB_CODE_6533;
          _b_5 = '\0';
          DAT_EXTMEM_0eff = 5;
          DAT_EXTMEM_0095 = 6;
          DAT_EXTMEM_0096 = 10;
          DAT_EXTMEM_0097 = 7;
          DAT_EXTMEM_0098 = DAT_EXTMEM_0309;
          DAT_EXTMEM_0f03 = 0;
          DAT_EXTMEM_0f04 = 0x95;
        }
        else {
          _b_2 = '\0';
          DAT_EXTMEM_0eff = 5;
          DAT_EXTMEM_0095 = 6;
          DAT_EXTMEM_0096 = 10;
          DAT_EXTMEM_0097 = 5;
          DAT_EXTMEM_0098 = DAT_EXTMEM_0c31;
          if (_d_3 != '\x01') {
            DAT_EXTMEM_0099 = 1;
          }
          if (_6_0 != '\0') {
            DAT_EXTMEM_0099 = DAT_EXTMEM_0099 | 0x10;
          }
          DAT_EXTMEM_0f03 = 0;
          DAT_EXTMEM_0f04 = 0x95;
        }
      }
      else {
        _a_6 = '\0';
        DAT_EXTMEM_0eff = 3;
        DAT_EXTMEM_097c = 4;
        DAT_EXTMEM_0f03 = 9;
        DAT_EXTMEM_0f04 = 0x7c;
      }
    }
    else {
      _7_4 = '\0';
      DAT_EXTMEM_0eff = 2;
      DAT_EXTMEM_08bb = 3;
      DAT_EXTMEM_0f03 = 8;
      DAT_EXTMEM_0f04 = 0xbb;
    }
  }
  else {
    _7_3 = '\0';
    DAT_EXTMEM_0eff = 1;
    DAT_EXTMEM_0979 = 1;
    DAT_EXTMEM_0f03 = 9;
    DAT_EXTMEM_0f04 = 0x79;
  }
  _6_7 = 1;
  DAT_EXTMEM_0f02 = 1;
  bVar1 = true;
LAB_CODE_6533:
  if (bVar1) {
    DAT_EXTMEM_0f3c = '\x11';
    DAT_EXTMEM_0f3d = 0x80;
    for (DAT_EXTMEM_0efe = 0; DAT_EXTMEM_0efe < (byte)(&DAT_CODE_5564)[DAT_EXTMEM_0eff];
        DAT_EXTMEM_0efe = DAT_EXTMEM_0efe + 1) {
      bVar3 = DAT_EXTMEM_0efe;
      uVar2 = FUN_CODE_41ca(DAT_EXTMEM_0f04,DAT_EXTMEM_0f03,DAT_EXTMEM_0f02);
      *(undefined1 *)
       CONCAT11(DAT_EXTMEM_0f3c - ((CARRY1(DAT_EXTMEM_0f3d,bVar3) << 7) >> 7),
                DAT_EXTMEM_0f3d + bVar3) = uVar2;
      FUN_CODE_42e1(0,0xf03,1);
    }
    DAT_SFR_9d = (&DAT_CODE_5564)[DAT_EXTMEM_0eff];
    bVar3 = DAT_SFR_9a;
    DAT_SFR_9a = bVar3 | 4;
  }
  _6_7 = 0;
  bVar3 = 0;
  if (DAT_EXTMEM_0f01 != '\0') {
    DAT_EXTMEM_0f01 = '\0';
    for (DAT_EXTMEM_0efe = 2; bVar3 = DAT_EXTMEM_0efe - 8, DAT_EXTMEM_0efe < 8;
        DAT_EXTMEM_0efe = DAT_EXTMEM_0efe + 1) {
      *(undefined1 *)CONCAT11('\t' - (((0x54 < DAT_EXTMEM_0efe) << 7) >> 7),DAT_EXTMEM_0efe + 0xab)
           = 0;
    }
  }
  return bVar3;
}



===== FUN_CODE_6b03 CODE:6b03 size=434 =====

void FUN_CODE_6b03(byte param_1,byte param_2)

{
  char cVar1;
  byte bVar2;
  undefined1 uVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  undefined1 *puVar7;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0ee3 = param_2;
  DAT_EXTMEM_0ee4 = param_1;
  FUN_CODE_7e03();
  if (param_2 == 0) {
    if (DAT_EXTMEM_011c == '\a') {
      FUN_CODE_a0dd();
      FUN_CODE_42ab(0,0xc0);
      bVar5 = (byte)((ushort)BANK0_R5 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)BANK0_R5 * 3 >> 8) + ('\'' - (((0x16 < bVar5) << 7) >> 7)),
                        bVar5 - 0x17);
      bVar5 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar5) << 7) >> 7)),bVar5 + 0x24);
      bVar5 = DAT_EXTMEM_0ee3;
      bVar4 = DAT_EXTMEM_0ee4;
      bVar6 = BANK0_R5;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar3;
      bVar2 = (byte)((ushort)bVar6 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar6 * 3 >> 8) + ('\'' - (((0x15 < bVar2) << 7) >> 7)),
                        bVar2 - 0x16);
      bVar2 = (byte)((ushort)bVar4 * 0x12);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar4 * 0x12 >> 8) + ('\x04' - (((0xda < bVar2) << 7) >> 7)),
                        bVar2 + 0x25);
      FUN_CODE_4392(bVar5,3);
      *puVar7 = uVar3;
      bVar5 = (byte)((ushort)bVar6 * 3);
      uVar3 = *(undefined1 *)
               CONCAT11((char)((ushort)bVar6 * 3 >> 8) + ('\'' - (((0x14 < bVar5) << 7) >> 7)),
                        bVar5 - 0x15);
      bVar5 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar5) << 7) >> 7)),bVar5 + 0x26);
      bVar5 = DAT_EXTMEM_0ee3;
    }
    else {
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) + -0x38,
                          (char)((ushort)DAT_EXTMEM_0892 * 0x15));
      cVar1 = DAT_EXTMEM_011c;
      bVar5 = DAT_EXTMEM_0892;
      FUN_CODE_4392(3,DAT_EXTMEM_011c);
      uVar3 = *uStack_1;
      bVar4 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xdb < bVar4) << 7) >> 7)),bVar4 + 0x24);
      FUN_CODE_4392(DAT_EXTMEM_0ee3,3);
      *uStack_1 = uVar3;
      bVar4 = (byte)((ushort)bVar5 * 0x15);
      puVar7 = (undefined1 *)
               CONCAT11((char)((ushort)bVar5 * 0x15 >> 8) + (-0x38 - (((0xfe < bVar4) << 7) >> 7)),
                        bVar4 + 1);
      FUN_CODE_4392(cVar1,3);
      uVar3 = *puVar7;
      bVar5 = (byte)((ushort)DAT_EXTMEM_0ee4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0ee4 * 0x12 >> 8) +
                          ('\x04' - (((0xda < bVar5) << 7) >> 7)),bVar5 + 0x25);
      bVar5 = DAT_EXTMEM_0ee3;
      bVar4 = DAT_EXTMEM_0ee4;
      FUN_CODE_4392(3,DAT_EXTMEM_0ee3);
      *uStack_1 = uVar3;
      bVar6 = (byte)((ushort)DAT_EXTMEM_0892 * 0x15);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)DAT_EXTMEM_0892 * 0x15 >> 8) +
                          (-0x38 - (((0xfd < bVar6) << 7) >> 7)),bVar6 + 2);
      FUN_CODE_4392(DAT_EXTMEM_011c,3);
      uVar3 = *uStack_1;
      bVar6 = (byte)((ushort)bVar4 * 0x12);
      uStack_1 = (undefined1 *)
                 CONCAT11((char)((ushort)bVar4 * 0x12 >> 8) +
                          ('\x04' - (((0xd9 < bVar6) << 7) >> 7)),bVar6 + 0x26);
    }
    FUN_CODE_4392(bVar5,3);
    *uStack_1 = uVar3;
    bVar5 = DAT_EXTMEM_0ee4 * '\x06' + 0x17;
    *(undefined1 *)
     CONCAT11(-((CARRY1(bVar5,DAT_EXTMEM_0ee3) << 7) >> 7) -
              (((0xe8 < DAT_EXTMEM_0ee4 * '\x06') << 7) >> 7),bVar5 + DAT_EXTMEM_0ee3) = 0;
  }
  return;
}



===== FUN_CODE_6e62 CODE:6e62 size=2 =====

char FUN_CODE_6e62(byte *param_1)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  byte *pbVar8;
  undefined2 uStack_1;
  
  bVar5 = *param_1;
  bVar6 = param_1[1];
  DAT_EXTMEM_0eef = DAT_EXTMEM_0e3e;
  DAT_EXTMEM_0ef0 = DAT_EXTMEM_0e3b;
  cVar2 = bVar5 - 0x15;
  DAT_EXTMEM_0eec = bVar5;
  DAT_EXTMEM_0eed = bVar6;
  if (((bVar5 < 0x15) << 7 < '\0') && (cVar2 = bVar6 - 6, (bVar6 < 6) << 7 < '\0')) {
    bVar3 = (byte)((ushort)bVar5 * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)bVar5 * 0x12 >> 8) +
                                ('\x01' - (((0xad < bVar3) << 7) >> 7)),bVar3 + 0x52);
    bVar3 = DAT_EXTMEM_0e42;
    FUN_CODE_4392(3,bVar6);
    *uStack_1 = bVar3;
    bVar4 = (byte)((ushort)bVar5 * 0x12);
    pbVar8 = (byte *)CONCAT11((char)((ushort)bVar5 * 0x12 >> 8) +
                              ('\x01' - (((0xac < bVar4) << 7) >> 7)),bVar4 + 0x53);
    bVar5 = DAT_EXTMEM_0eef;
    FUN_CODE_4392(bVar6,3);
    *pbVar8 = bVar5;
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x12 >> 8) +
                                ('\x01' - (((0xab < bVar5) << 7) >> 7)),bVar5 + 0x54);
    bVar5 = DAT_EXTMEM_0eed;
    bVar6 = DAT_EXTMEM_0ef0;
    FUN_CODE_4392(3);
    *uStack_1 = bVar6;
    bVar6 = (byte)((ushort)bVar3 * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x19 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x1a);
    cVar1 = '\0';
    cVar7 = bVar5 + bVar6;
    cVar2 = (char)((ushort)bVar3 * 4 >> 8) - ((CARRY1(bVar5,bVar6) << 7) >> 7);
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x61 < bVar5) << 7) >> 7)),bVar5 + 0x9e);
    bVar5 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar7;
    bVar6 = (byte)((ushort)DAT_EXTMEM_0eef * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x18 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x19);
    cVar7 = bVar5 + bVar6;
    cVar2 = cVar1 + ((char)((ushort)DAT_EXTMEM_0eef * 4 >> 8) - ((CARRY1(bVar5,bVar6) << 7) >> 7));
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5f < bVar5) << 7) >> 7)),bVar5 + 0xa0);
    bVar5 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar7;
    bVar6 = (byte)((ushort)DAT_EXTMEM_0ef0 * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x17 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x18);
    cVar2 = bVar5 + bVar6;
    cVar1 = cVar1 + ((char)((ushort)DAT_EXTMEM_0ef0 * 4 >> 8) - ((CARRY1(bVar5,bVar6) << 7) >> 7));
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5d < bVar5) << 7) >> 7)),bVar5 + 0xa2);
    FUN_CODE_4392(DAT_EXTMEM_0eed,6);
    *uStack_1 = cVar1;
    uStack_1[1] = cVar2;
  }
  return cVar2;
}



===== FUN_CODE_6e64 CODE:6e64 size=22 =====

char FUN_CODE_6e64(byte param_1,byte *param_2)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  byte *pbVar7;
  undefined2 uStack_1;
  
  bVar5 = *param_2;
  DAT_EXTMEM_0eef = DAT_EXTMEM_0e3e;
  DAT_EXTMEM_0ef0 = DAT_EXTMEM_0e3b;
  cVar2 = param_1 - 0x15;
  DAT_EXTMEM_0eec = param_1;
  DAT_EXTMEM_0eed = bVar5;
  if (((param_1 < 0x15) << 7 < '\0') && (cVar2 = bVar5 - 6, (bVar5 < 6) << 7 < '\0')) {
    bVar3 = (byte)((ushort)param_1 * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)param_1 * 0x12 >> 8) +
                                ('\x01' - (((0xad < bVar3) << 7) >> 7)),bVar3 + 0x52);
    bVar3 = DAT_EXTMEM_0e42;
    FUN_CODE_4392(3,bVar5);
    *uStack_1 = bVar3;
    bVar4 = (byte)((ushort)param_1 * 0x12);
    pbVar7 = (byte *)CONCAT11((char)((ushort)param_1 * 0x12 >> 8) +
                              ('\x01' - (((0xac < bVar4) << 7) >> 7)),bVar4 + 0x53);
    bVar4 = DAT_EXTMEM_0eef;
    FUN_CODE_4392(bVar5,3);
    *pbVar7 = bVar4;
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x12 >> 8) +
                                ('\x01' - (((0xab < bVar5) << 7) >> 7)),bVar5 + 0x54);
    bVar5 = DAT_EXTMEM_0eed;
    bVar4 = DAT_EXTMEM_0ef0;
    FUN_CODE_4392(3);
    *uStack_1 = bVar4;
    bVar4 = (byte)((ushort)bVar3 * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x19 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x1a);
    cVar1 = '\0';
    cVar6 = bVar5 + bVar4;
    cVar2 = (char)((ushort)bVar3 * 4 >> 8) - ((CARRY1(bVar5,bVar4) << 7) >> 7);
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x61 < bVar5) << 7) >> 7)),bVar5 + 0x9e);
    bVar5 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar6;
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eef * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x18 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x19);
    cVar6 = bVar5 + bVar3;
    cVar2 = cVar1 + ((char)((ushort)DAT_EXTMEM_0eef * 4 >> 8) - ((CARRY1(bVar5,bVar3) << 7) >> 7));
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5f < bVar5) << 7) >> 7)),bVar5 + 0xa0);
    bVar5 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar6;
    bVar3 = (byte)((ushort)DAT_EXTMEM_0ef0 * 4);
    bVar5 = *(byte *)CONCAT11('%' - (((0x17 < bVar5 * '\x03') << 7) >> 7),bVar5 * '\x03' - 0x18);
    cVar2 = bVar5 + bVar3;
    cVar1 = cVar1 + ((char)((ushort)DAT_EXTMEM_0ef0 * 4 >> 8) - ((CARRY1(bVar5,bVar3) << 7) >> 7));
    bVar5 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5d < bVar5) << 7) >> 7)),bVar5 + 0xa2);
    FUN_CODE_4392(DAT_EXTMEM_0eed,6);
    *uStack_1 = cVar1;
    uStack_1[1] = cVar2;
  }
  return cVar2;
}



===== FUN_CODE_6e7a CODE:6e7a size=5 =====

char FUN_CODE_6e7a(byte *param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  byte *pbVar6;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0ef0 = *param_1;
  cVar2 = param_4 - 0x15;
  DAT_EXTMEM_0eec = param_4;
  DAT_EXTMEM_0eed = param_3;
  if (((param_4 < 0x15) << 7 < '\0') && (cVar2 = param_3 - 6, (param_3 < 6) << 7 < '\0')) {
    bVar3 = (byte)((ushort)param_4 * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)param_4 * 0x12 >> 8) +
                                ('\x01' - (((0xad < bVar3) << 7) >> 7)),bVar3 + 0x52);
    FUN_CODE_4392(3,param_3);
    *uStack_1 = param_2;
    bVar3 = (byte)((ushort)param_4 * 0x12);
    pbVar6 = (byte *)CONCAT11((char)((ushort)param_4 * 0x12 >> 8) +
                              ('\x01' - (((0xac < bVar3) << 7) >> 7)),bVar3 + 0x53);
    bVar3 = DAT_EXTMEM_0eef;
    FUN_CODE_4392(param_3,3);
    *pbVar6 = bVar3;
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x12 >> 8) +
                                ('\x01' - (((0xab < bVar3) << 7) >> 7)),bVar3 + 0x54);
    bVar3 = DAT_EXTMEM_0eed;
    bVar4 = DAT_EXTMEM_0ef0;
    FUN_CODE_4392(3);
    *uStack_1 = bVar4;
    bVar4 = (byte)((ushort)param_2 * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x19 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x1a);
    cVar1 = '\0';
    cVar5 = bVar3 + bVar4;
    cVar2 = (char)((ushort)param_2 * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7);
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x61 < bVar3) << 7) >> 7)),bVar3 + 0x9e);
    bVar3 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar5;
    bVar4 = (byte)((ushort)DAT_EXTMEM_0eef * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x18 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x19);
    cVar5 = bVar3 + bVar4;
    cVar2 = cVar1 + ((char)((ushort)DAT_EXTMEM_0eef * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7));
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5f < bVar3) << 7) >> 7)),bVar3 + 0xa0);
    bVar3 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar5;
    bVar4 = (byte)((ushort)DAT_EXTMEM_0ef0 * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x17 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x18);
    cVar2 = bVar3 + bVar4;
    cVar1 = cVar1 + ((char)((ushort)DAT_EXTMEM_0ef0 * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7));
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5d < bVar3) << 7) >> 7)),bVar3 + 0xa2);
    FUN_CODE_4392(DAT_EXTMEM_0eed,6);
    *uStack_1 = cVar1;
    uStack_1[1] = cVar2;
  }
  return cVar2;
}



===== FUN_CODE_6e7f CODE:6e7f size=362 =====

char FUN_CODE_6e7f(byte param_1,byte param_2,byte param_3)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  byte *pbVar6;
  undefined2 uStack_1;
  
  cVar2 = param_3 - 0x15;
  DAT_EXTMEM_0eec = param_3;
  DAT_EXTMEM_0eed = param_2;
  if (((param_3 < 0x15) << 7 < '\0') && (cVar2 = param_2 - 6, (param_2 < 6) << 7 < '\0')) {
    bVar3 = (byte)((ushort)param_3 * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)param_3 * 0x12 >> 8) +
                                ('\x01' - (((0xad < bVar3) << 7) >> 7)),bVar3 + 0x52);
    FUN_CODE_4392(3,param_2);
    *uStack_1 = param_1;
    bVar3 = (byte)((ushort)param_3 * 0x12);
    pbVar6 = (byte *)CONCAT11((char)((ushort)param_3 * 0x12 >> 8) +
                              ('\x01' - (((0xac < bVar3) << 7) >> 7)),bVar3 + 0x53);
    bVar3 = DAT_EXTMEM_0eef;
    FUN_CODE_4392(param_2,3);
    *pbVar6 = bVar3;
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x12);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x12 >> 8) +
                                ('\x01' - (((0xab < bVar3) << 7) >> 7)),bVar3 + 0x54);
    bVar3 = DAT_EXTMEM_0eed;
    bVar4 = DAT_EXTMEM_0ef0;
    FUN_CODE_4392(3);
    *uStack_1 = bVar4;
    bVar4 = (byte)((ushort)param_1 * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x19 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x1a);
    cVar1 = '\0';
    cVar5 = bVar3 + bVar4;
    cVar2 = (char)((ushort)param_1 * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7);
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x61 < bVar3) << 7) >> 7)),bVar3 + 0x9e);
    bVar3 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar5;
    bVar4 = (byte)((ushort)DAT_EXTMEM_0eef * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x18 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x19);
    cVar5 = bVar3 + bVar4;
    cVar2 = cVar1 + ((char)((ushort)DAT_EXTMEM_0eef * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7));
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5f < bVar3) << 7) >> 7)),bVar3 + 0xa0);
    bVar3 = DAT_EXTMEM_0eed;
    FUN_CODE_4392(6);
    *uStack_1 = cVar2;
    uStack_1[1] = cVar5;
    bVar4 = (byte)((ushort)DAT_EXTMEM_0ef0 * 4);
    bVar3 = *(byte *)CONCAT11('%' - (((0x17 < bVar3 * '\x03') << 7) >> 7),bVar3 * '\x03' - 0x18);
    cVar2 = bVar3 + bVar4;
    cVar1 = cVar1 + ((char)((ushort)DAT_EXTMEM_0ef0 * 4 >> 8) - ((CARRY1(bVar3,bVar4) << 7) >> 7));
    bVar3 = (byte)((ushort)DAT_EXTMEM_0eec * 0x24);
    uStack_1 = (byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0eec * 0x24 >> 8) +
                                ('\x05' - (((0x5d < bVar3) << 7) >> 7)),bVar3 + 0xa2);
    FUN_CODE_4392(DAT_EXTMEM_0eed,6);
    *uStack_1 = cVar1;
    uStack_1[1] = cVar2;
  }
  return cVar2;
}



===== FUN_CODE_6fe9 CODE:6fe9 size=20 =====

/* WARNING: Removing unreachable block (CODE,0x7065) */
/* WARNING: Removing unreachable block (CODE,0x706b) */
/* WARNING: Removing unreachable block (CODE,0x706e) */
/* WARNING: Removing unreachable block (CODE,0x7068) */

void FUN_CODE_6fe9(undefined1 param_1)

{
  char cVar1;
  
  FUN_CODE_4392(4);
  FUN_CODE_4345();
  FUN_CODE_431e(0x18);
  DAT_EXTMEM_0d13 = param_1;
  BANK2_R1 = 0;
  if (((_8_2 != '\x01') && (_9_4 != '\0')) && (_9_2 != '\0')) {
    _9_2 = 0;
    _9_4 = 0;
    _9_3 = 1;
    _7_7 = 1;
    return;
  }
  cVar1 = FUN_CODE_439e(param_1);
  if (cVar1 != '\0') {
    FUN_CODE_7ccb();
    return;
  }
  nop();
  if ((_9_5 != '\x01') && (_a_5 != '\x01')) {
    DAT_EXTMEM_08bd = 0;
    DAT_EXTMEM_08be = 0;
    if (_8_2 != '\x01') {
      DAT_EXTMEM_08bd = DAT_EXTMEM_0d11;
      DAT_EXTMEM_08be = DAT_EXTMEM_0d10;
    }
    DAT_EXTMEM_08bc = DAT_EXTMEM_0d13;
    _7_4 = 1;
    return;
  }
  return;
}



===== FUN_CODE_6ffd CODE:6ffd size=51 =====

/* WARNING: Removing unreachable block (CODE,0x7065) */
/* WARNING: Removing unreachable block (CODE,0x706b) */
/* WARNING: Removing unreachable block (CODE,0x706e) */
/* WARNING: Removing unreachable block (CODE,0x7068) */

void FUN_CODE_6ffd(void)

{
  char cVar1;
  
  BANK2_R1 = 0;
  if (((_8_2 != '\x01') && (_9_4 != '\0')) && (_9_2 != '\0')) {
    _9_2 = 0;
    _9_4 = 0;
    _9_3 = 1;
    _7_7 = 1;
    return;
  }
  cVar1 = FUN_CODE_439e(DAT_EXTMEM_0d13);
  if (cVar1 != '\0') {
    FUN_CODE_7ccb();
    return;
  }
  nop();
  if ((_9_5 != '\x01') && (_a_5 != '\x01')) {
    DAT_EXTMEM_08bd = 0;
    DAT_EXTMEM_08be = 0;
    if (_8_2 != '\x01') {
      DAT_EXTMEM_08bd = DAT_EXTMEM_0d11;
      DAT_EXTMEM_08be = DAT_EXTMEM_0d10;
    }
    DAT_EXTMEM_08bc = DAT_EXTMEM_0d13;
    _7_4 = 1;
    return;
  }
  return;
}



===== FUN_CODE_7108 CODE:7108 size=392 =====

void FUN_CODE_7108(void)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = 0;
  cVar1 = '\0';
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x4c,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x66,0xcc,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x4a,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x67,0xce,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x48,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x68,0xd0,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x46,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x69,0xd2,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x44,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x6a,0xd4,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x42,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x6b,0xd6,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x40,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x6c,0xd8,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x3e,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(0x6d,0xda,0);
  return;
}



===== FUN_CODE_7ccb CODE:7ccb size=159 =====

byte FUN_CODE_7ccb(void)

{
  ushort uVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  
  cVar2 = DAT_EXTMEM_0d12;
  bVar3 = DAT_EXTMEM_0d12 - 1;
  if (_8_2 == '\0') {
    if ((DAT_EXTMEM_0d12 - 1U < 0xd) << 7 < '\0') {
      uVar1 = (ushort)(DAT_EXTMEM_0d12 - 1U) * 3;
                    /* WARNING: Could not recover jumptable at 0x7d2d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      bVar3 = (*(code *)(CONCAT11((char)(uVar1 >> 8) + '}',0x2e) + (uVar1 & 0xff)))();
      return bVar3;
    }
    bVar4 = DAT_EXTMEM_0d11 - 2;
    if (1 < DAT_EXTMEM_0d11) {
      *(byte *)CONCAT11('\f' - (((0xcd < bVar3) << 7) >> 7),DAT_EXTMEM_0d12 + '1') =
           DAT_EXTMEM_0d11 * '\x02';
      bVar4 = DAT_EXTMEM_0d10;
      *(byte *)CONCAT11('\x03' - (((0x73 < bVar3) << 7) >> 7),cVar2 + -0x75) = DAT_EXTMEM_0d10;
      *(byte *)CONCAT11('\f' - (((0xbf < bVar3) << 7) >> 7),cVar2 + '?') = bVar4;
      _8_1 = 1;
    }
    _9_0 = 1;
  }
  else {
    if (DAT_EXTMEM_0d12 - 1U < 5) {
      DAT_EXTMEM_09ac = DAT_EXTMEM_09ac & (&DAT_CODE_abe3)[bVar3];
      _9_0 = 1;
    }
    bVar4 = ~DAT_EXTMEM_0d11;
    if (bVar4 == 0) {
      *(undefined1 *)CONCAT11('\f' - (((0xcd < bVar3) << 7) >> 7),DAT_EXTMEM_0d12 + '1') = 0;
      *(undefined1 *)CONCAT11('\x03' - (((0x73 < bVar3) << 7) >> 7),cVar2 + -0x75) = 0;
      return 0;
    }
  }
  return bVar4;
}



===== FUN_CODE_7e03 CODE:7e03 size=232 =====

void FUN_CODE_7e03(char param_1,char param_2)

{
  if (_b_4 != '\0') {
    return;
  }
  if (_d_4 != '\0') {
    return;
  }
  if ((param_2 == '\x05') && (param_1 == '\x04')) {
    return;
  }
  if ((param_2 == '\x05') && (param_1 == '\x06')) {
    return;
  }
  if ((param_2 == '\x05') && (param_1 == '\a')) {
    return;
  }
  if (_6_3 != '\0') {
    return;
  }
  if ((((param_2 == '\x02') && (param_1 == '\x01')) && (_3_4 != '\0')) &&
     (DAT_EXTMEM_0324 == '\x01')) {
    return;
  }
  if (((param_2 == '\x02') && (param_1 == '\x02')) && ((_3_4 != '\0' && (DAT_EXTMEM_0324 == '\0'))))
  {
    return;
  }
  if (((param_2 == '\x02') && (param_1 == '\x03')) &&
     ((_3_4 != '\0' && (DAT_EXTMEM_0324 == '\x02')))) {
    return;
  }
  if ((((param_2 == '\x02') && (param_1 == '\x04')) && (_3_4 != '\0')) &&
     (DAT_EXTMEM_0324 == '\x03')) {
    return;
  }
  if (((param_2 == '\x02') && (param_1 == '\x01')) &&
     ((_3_4 != '\x01' && ((_8_4 != '\x01' && (DAT_EXTMEM_0324 == '\x01')))))) {
    return;
  }
  if ((param_2 == '\x02') &&
     ((((param_1 == '\x02' && (_3_4 != '\x01')) && (_8_4 != '\x01')) && (DAT_EXTMEM_0324 == '\0'))))
  {
    return;
  }
  if (((param_2 == '\x02') && (param_1 == '\x03')) &&
     ((_3_4 != '\x01' && ((_8_4 != '\x01' && (DAT_EXTMEM_0324 == '\x02')))))) {
    return;
  }
  if (((param_2 == '\x02') && (((param_1 == '\x04' && (_3_4 != '\x01')) && (_8_4 != '\x01')))) &&
     (DAT_EXTMEM_0324 == '\x03')) {
    return;
  }
  return;
}



===== FUN_CODE_80ed CODE:80ed size=253 =====

char FUN_CODE_80ed(void)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  
  IEN1 = 0;
  if (DAT_EXTMEM_095d < 0xbU - (((DAT_EXTMEM_095e < 0xb8) << 7) >> 7)) goto LAB_CODE_81c8;
  DAT_EXTMEM_095d = 0;
  DAT_EXTMEM_095e = 0;
  if (_b_7 != '\0') {
    _b_7 = '\0';
    _b_4 = 1;
    FUN_CODE_ac7b();
    FUN_CODE_ac82();
    FUN_CODE_a4b6(0,0,0);
    FUN_CODE_9792();
    FUN_CODE_868e();
    FUN_CODE_7108();
    FUN_CODE_a4b6(0,0,0xff);
    FUN_CODE_a9a8(200);
    FUN_CODE_a4b6(0,0,0);
    FUN_CODE_a9a8(200);
    FUN_CODE_a4b6(0,0xff,0);
    FUN_CODE_a9a8(200);
    FUN_CODE_a4b6(0,0,0);
    FUN_CODE_a9a8(200);
    FUN_CODE_a4b6(0xff,0,0);
    FUN_CODE_a9a8(200);
    FUN_CODE_a4b6(0,0,0);
    FUN_CODE_a9a8(200);
    _b_4 = 0;
    _a_1 = 1;
    _4_1 = 1;
    _c_5 = '\0';
    _7_1 = 0;
    _3_3 = 0;
    _d_2 = 0;
    _4_6 = 0;
  }
  if (_c_5 != '\0') {
    DAT_EXTMEM_0e36 = 0;
    _c_5 = '\0';
    FUN_CODE_ac82();
    uVar2 = DAT_EXTMEM_0315;
    if (DAT_EXTMEM_0317 != '\x02') {
      if (DAT_EXTMEM_0317 != '\x01') goto LAB_CODE_81a7;
      uVar2 = 0;
    }
    FUN_CODE_ac47(uVar2,1);
  }
LAB_CODE_81a7:
  if (_5_4 != '\0') {
    _5_4 = '\0';
    _3_1 = 1;
    DAT_EXTMEM_0323 = DAT_EXTMEM_0323 == '\0';
    DAT_EXTMEM_09b3 = 0;
    DAT_EXTMEM_09b4 = 0;
    _c_0 = 1;
  }
LAB_CODE_81c8:
  bVar1 = 0x1f - (((DAT_EXTMEM_0c4e < 0x40) << 7) >> 7);
  cVar3 = DAT_EXTMEM_0c4d - bVar1;
  if (bVar1 <= DAT_EXTMEM_0c4d) {
    cVar3 = '\0';
    DAT_EXTMEM_0c4d = 0;
    DAT_EXTMEM_0c4e = 0;
    if (_7_6 != '\0') {
      _7_6 = '\0';
      _c_4 = 1;
      cVar3 = FUN_CODE_a72f(3);
      _3_3 = 1;
    }
  }
  return cVar3;
}



===== FUN_CODE_84c6 CODE:84c6 size=229 =====

void FUN_CODE_84c6(void)

{
  char cVar1;
  byte bVar2;
  
  DAT_EXTMEM_0edd = DAT_EXTMEM_0ec5;
  DAT_EXTMEM_0ede = DAT_EXTMEM_0ec6;
  DAT_EXTMEM_0edf = DAT_EXTMEM_0ec7;
  bVar2 = DAT_EXTMEM_0ec5 * '\x15' + 0xac;
  FUN_CODE_472a(*(undefined1 *)
                 CONCAT11(('+' - (((0x53 < DAT_EXTMEM_0ec5 * '\x15') << 7) >> 7)) -
                          ((CARRY1(bVar2,DAT_EXTMEM_0ec6) << 7) >> 7),bVar2 + DAT_EXTMEM_0ec6));
  if (DAT_EXTMEM_0edf == '\0') {
    DAT_EXTMEM_0ede = DAT_EXTMEM_0ede - 1;
    if ((DAT_EXTMEM_0ede < 0xf) << 7 < '\0') goto LAB_CODE_8562;
    DAT_EXTMEM_0edf = -1;
    DAT_EXTMEM_0ede = 0;
  }
  else {
    DAT_EXTMEM_0ede = DAT_EXTMEM_0ede + 1;
    if ((DAT_EXTMEM_0ede < 0xf) << 7 < '\0') goto LAB_CODE_8562;
    DAT_EXTMEM_0edf = '\0';
    DAT_EXTMEM_0ede = 0xe;
  }
  if (DAT_EXTMEM_0ec8 == 0) {
    DAT_EXTMEM_0edd = DAT_EXTMEM_0edd - 1;
  }
  else {
    DAT_EXTMEM_0edd = DAT_EXTMEM_0edd + 1;
  }
LAB_CODE_8562:
  cVar1 = (DAT_EXTMEM_0edd < 6) << 7;
  if ((cVar1 < '\0') || (0xffU - (cVar1 >> 7) <= DAT_EXTMEM_0edd)) {
    if (DAT_EXTMEM_0edd == 0xff) {
      DAT_EXTMEM_0ec8 = ~DAT_EXTMEM_0ec8;
      DAT_EXTMEM_0edd = 1;
    }
  }
  else {
    DAT_EXTMEM_0ec8 = ~DAT_EXTMEM_0ec8;
    DAT_EXTMEM_0edd = 4;
  }
  DAT_EXTMEM_0ec5 = DAT_EXTMEM_0edd;
  DAT_EXTMEM_0ec6 = DAT_EXTMEM_0ede;
  DAT_EXTMEM_0ec7 = DAT_EXTMEM_0edf;
  return;
}



===== FUN_CODE_868e CODE:868e size=203 =====

void FUN_CODE_868e(void)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = 0;
  cVar1 = '\0';
  do {
    if (*(char *)CONCAT11((cVar1 - (((0x85 < bVar2) << 7) >> 7)) + -0x35,bVar2 + 0x7a) == -1) {
      *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) = 0;
      *(undefined1 *)CONCAT11((cVar1 - (((199 < bVar2) << 7) >> 7)) + '\n',bVar2 + 0x38) = 0;
      *(undefined1 *)CONCAT11((cVar1 - (((0x49 < bVar2) << 7) >> 7)) + '\n',bVar2 + 0xb6) = 0xff;
    }
    else {
      *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) = 0;
      *(undefined1 *)CONCAT11((cVar1 - (((199 < bVar2) << 7) >> 7)) + '\n',bVar2 + 0x38) = 0;
      *(undefined1 *)CONCAT11((cVar1 - (((0x49 < bVar2) << 7) >> 7)) + '\n',bVar2 + 0xb6) = 0;
    }
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while (bVar2 != 0x7e || cVar1 != '\0');
  cVar1 = '\x01';
  bVar2 = 0x7a;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x36,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((cVar1 != '\x01') || (bVar2 != 0xf8));
  FUN_CODE_a252(0x65,0xca,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x4e,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar1 != '\x02'));
  FUN_CODE_a252(100,200,0);
  return;
}



===== FUN_CODE_8759 CODE:8759 size=202 =====

char FUN_CODE_8759(void)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  
  FUN_CODE_80ed();
  if (DAT_EXTMEM_08d7 < 10) {
    return DAT_EXTMEM_08d7 - 10;
  }
  DAT_EXTMEM_08d7 = 0;
  _9_7 = DAT_EXTMEM_031a != '\0';
  if (DAT_EXTMEM_0318 == '\0') {
    _9_6 = 0;
  }
  else if (DAT_EXTMEM_0324 == '\0') {
    _9_6 = 1;
  }
  else {
    _9_6 = 0;
  }
  _9_5 = DAT_EXTMEM_0319 != '\0';
  FUN_CODE_4402();
  if (DAT_EXTMEM_0317 != '\0') {
    if (DAT_EXTMEM_09a7 == '\x03') {
      if (DAT_EXTMEM_0321 == 0) goto LAB_CODE_87e3;
      bVar1 = (char)((ushort)DAT_EXTMEM_0321 * 0x1e >> 8) -
              (((DAT_EXTMEM_09a9 < (char)((ushort)DAT_EXTMEM_0321 * 0x1e) + 1U) << 7) >> 7);
    }
    else {
      if (DAT_EXTMEM_0c30 == 0) goto LAB_CODE_87e3;
      bVar1 = (char)((ushort)DAT_EXTMEM_0c30 * 10 >> 8) -
              (((DAT_EXTMEM_09a9 < (char)((ushort)DAT_EXTMEM_0c30 * 10) + 1U) << 7) >> 7);
    }
    if (bVar1 <= DAT_EXTMEM_09a8) {
      DAT_EXTMEM_09a8 = 0;
      DAT_EXTMEM_09a9 = 0;
      _9_1 = 1;
    }
  }
LAB_CODE_87e3:
  DAT_EXTMEM_0d9b = DAT_EXTMEM_0d9b + 1;
  if (DAT_EXTMEM_0d9b == 0) {
    DAT_EXTMEM_0d9a = DAT_EXTMEM_0d9a + 1;
  }
  cVar2 = ((DAT_EXTMEM_0d9b < 0xc9) << 7) >> 7;
  cVar3 = DAT_EXTMEM_0d9a + cVar2;
  if ((byte)-cVar2 <= DAT_EXTMEM_0d9a) {
    if ((_a_3 != '\0') && (DAT_EXTMEM_0313 == '\x12')) {
      DAT_EXTMEM_0314 = 0x20;
      DAT_EXTMEM_009d = 0x20;
      DAT_EXTMEM_0312 = 1;
    }
    cVar3 = '\0';
    DAT_EXTMEM_0d9a = 0;
    DAT_EXTMEM_0d9b = 0;
    _a_3 = '\0';
  }
  return cVar3;
}



===== FUN_CODE_8823 CODE:8823 size=197 =====

void FUN_CODE_8823(void)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  byte bVar4;
  undefined1 *puVar5;
  
  _f_1 = 0;
  DAT_EXTMEM_0f25 = 0;
  DAT_EXTMEM_0f26 = 0;
  _e_7 = 0;
  _f_2 = 0;
  _7_7 = 1;
  _8_4 = 1;
  _8_3 = 1;
  _c_2 = 1;
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11('\t' - (((0x9f < bVar2) << 7) >> 7),bVar2 + 0x60) = 0xff;
    *(undefined1 *)CONCAT11('\t' - (((0x6f < bVar2) << 7) >> 7),bVar2 + 0x90) = 0xff;
    *(undefined1 *)CONCAT11('\b' - (((0x66 < bVar2) << 7) >> 7),bVar2 + 0x99) = 0;
    bVar1 = 0;
    do {
      bVar4 = bVar2 * '\x06' + 0x9e;
      *(undefined1 *)
       CONCAT11(-((CARRY1(bVar4,bVar1) << 7) >> 7) - (((0x61 < bVar2 * '\x06') << 7) >> 7),
                bVar4 + bVar1) = 0;
      bVar4 = bVar2 * '\x06' + 0x9c;
      *(undefined1 *)
       CONCAT11(('\r' - (((99 < bVar2 * '\x06') << 7) >> 7)) - ((CARRY1(bVar4,bVar1) << 7) >> 7),
                bVar4 + bVar1) = 0;
      bVar1 = bVar1 + 1;
    } while (bVar1 != 6);
    bVar2 = bVar2 + 1;
  } while (bVar2 != 0x15);
  cVar3 = '\t';
  puVar5 = &DAT_EXTMEM_08ae;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  cVar3 = '\x02';
  puVar5 = &DAT_EXTMEM_0979;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  cVar3 = '\x04';
  puVar5 = &DAT_EXTMEM_08bb;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  cVar3 = '\x10';
  puVar5 = &DAT_EXTMEM_097c;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  cVar3 = '\b';
  puVar5 = &DAT_EXTMEM_09ab;
  do {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  cVar3 = '\n';
  puVar5 = &DAT_EXTMEM_039b;
  do {
    *puVar5 = 0xff;
    puVar5 = puVar5 + 1;
    cVar3 = cVar3 + -1;
  } while (cVar3 != '\0');
  DAT_EXTMEM_0c3f = 2;
  _6_7 = 0;
  _c_3 = 0;
  FUN_CODE_a92c();
  return;
}



===== FUN_CODE_8c98 CODE:8c98 size=181 =====

char FUN_CODE_8c98(undefined1 param_1)

{
  byte bVar1;
  byte bVar2;
  
  _4_5 = 0;
  DAT_EXTMEM_0ede = 0;
  DAT_EXTMEM_0edd = param_1;
  do {
    for (DAT_EXTMEM_0edf = 0; bVar1 = DAT_EXTMEM_0ede, (DAT_EXTMEM_0edf < 0x15) << 7 < '\0';
        DAT_EXTMEM_0edf = DAT_EXTMEM_0edf + 1) {
      bVar1 = (byte)((ushort)DAT_EXTMEM_0edf * 6);
      DAT_EXTMEM_011d =
           *(undefined1 *)
            CONCAT11(((char)((ushort)DAT_EXTMEM_0edf * 6 >> 8) + -0x36) -
                     ((CARRY1(bVar1,DAT_EXTMEM_0ede) << 7) >> 7),bVar1 + DAT_EXTMEM_0ede);
      bVar1 = (byte)((ushort)DAT_EXTMEM_0edf * 6);
      bVar2 = bVar1 + 0x7e;
      uEXTMEM0000 = *(undefined1 *)
                     CONCAT11(((char)((ushort)DAT_EXTMEM_0edf * 6 >> 8) +
                              (-0x36 - (((0x81 < bVar1) << 7) >> 7))) -
                              ((CARRY1(bVar2,DAT_EXTMEM_0ede) << 7) >> 7),bVar2 + DAT_EXTMEM_0ede);
      bVar1 = (byte)((ushort)DAT_EXTMEM_0edf * 6);
      bVar2 = bVar1 - 4;
      DAT_EXTMEM_0e20 =
           *(undefined1 *)
            CONCAT11(((char)((ushort)DAT_EXTMEM_0edf * 6 >> 8) + (-0x36 - (((3 < bVar1) << 7) >> 7))
                     ) - ((CARRY1(bVar2,DAT_EXTMEM_0ede) << 7) >> 7),bVar2 + DAT_EXTMEM_0ede);
      if ((DAT_EXTMEM_0edf < 0x15) &&
         (bVar1 = DAT_EXTMEM_0ede, FUN_CODE_7e03(DAT_EXTMEM_0edf), bVar1 == 0)) {
        FUN_CODE_9819();
        FUN_CODE_6e64(DAT_EXTMEM_0edf,0xede);
      }
    }
    DAT_EXTMEM_0ede = DAT_EXTMEM_0ede + 1;
  } while (DAT_EXTMEM_0ede < 6);
  return bVar1 - 5;
}



===== FUN_CODE_8eb6 CODE:8eb6 size=41 =====

/* WARNING: Removing unreachable block (CODE,0x8f29) */
/* WARNING: Removing unreachable block (CODE,0x8ee4) */
/* WARNING: Removing unreachable block (CODE,0x8eef) */
/* WARNING: Removing unreachable block (CODE,0x8ef5) */
/* WARNING: Removing unreachable block (CODE,0x8efa) */

byte FUN_CODE_8eb6(byte param_1)

{
  char cVar1;
  undefined1 uVar2;
  byte bVar3;
  
  EA = 0;
  DAT_EXTMEM_0137 = 9;
  DAT_EXTMEM_0138 = 6;
  IEN1 = 0;
  TXCNTH = BANK0_R2 * '\x02' | param_1 & 1;
  CCAP1H = BANK0_R5;
  CCAP2H = BANK0_R3;
  uVar2 = 0x6e;
  bVar3 = TXCNTH;
  bVar3 = DAT_EXTMEM_0302 ^ bVar3 >> 1;
  if ((bVar3 == 0) &&
     ((DAT_EXTMEM_0302 < 99 || (bVar3 = DAT_EXTMEM_0302 + 0x8a, 0x75 < DAT_EXTMEM_0302)))) {
    bVar3 = 0;
    DAT_EXTMEM_0137 = 0;
    DAT_EXTMEM_0138 = 0;
    uVar2 = 0;
    DAT_EXTMEM_0302 = 0;
  }
  cVar1 = EA;
  if (cVar1 != '\x01') {
    TXSTAT = uVar2;
    TXDAT = 5;
    TXCON = 10;
    TXFLG = DAT_EXTMEM_0137;
    TXCNTL = DAT_EXTMEM_0138;
    nop();
    nop();
    nop();
    nop();
    bVar3 = 0;
    DAT_EXTMEM_0137 = 0;
    DAT_EXTMEM_0138 = 0;
    TXSTAT = 0;
    TXDAT = 0;
    TXCON = 0;
    TXFLG = 0;
    TXCNTL = 0;
  }
  return bVar3;
}



===== FUN_CODE_8edf CODE:8edf size=135 =====

byte FUN_CODE_8edf(char param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  if (param_1 == -0x1a) {
    bVar3 = TXCNTH;
    bVar3 = DAT_EXTMEM_0302 * '\x02' ^ bVar3;
  }
  else {
    if (param_1 != 'n') {
      DAT_EXTMEM_0137 = 0;
      DAT_EXTMEM_0138 = 0;
      DAT_EXTMEM_0302 = 0;
      return 0;
    }
    bVar3 = TXCNTH;
    bVar3 = DAT_EXTMEM_0302 ^ bVar3 >> 1;
  }
  if ((bVar3 == 0) &&
     ((DAT_EXTMEM_0302 < 99 ||
      (bVar1 = 0x76 - (((DAT_EXTMEM_0302 < 99) << 7) >> 7), bVar3 = DAT_EXTMEM_0302 - bVar1,
      bVar1 <= DAT_EXTMEM_0302)))) {
    bVar3 = 0;
    DAT_EXTMEM_0137 = 0;
    DAT_EXTMEM_0138 = 0;
    param_1 = '\0';
    DAT_EXTMEM_0302 = 0;
  }
  cVar2 = EA;
  if (cVar2 != '\x01') {
    TXSTAT = param_1;
    TXDAT = 5;
    TXCON = 10;
    TXFLG = DAT_EXTMEM_0137;
    TXCNTL = DAT_EXTMEM_0138;
    nop();
    nop();
    nop();
    nop();
    bVar3 = 0;
    DAT_EXTMEM_0137 = 0;
    DAT_EXTMEM_0138 = 0;
    TXSTAT = 0;
    TXDAT = 0;
    TXCON = 0;
    TXFLG = 0;
    TXCNTL = 0;
  }
  return bVar3;
}



===== FUN_CODE_8f66 CODE:8f66 size=175 =====

void FUN_CODE_8f66(void)

{
  byte bVar1;
  
  DAT_EXTMEM_02e3 = 0;
  DAT_EXTMEM_02e4 = 0;
  DAT_EXTMEM_0f2f = DAT_SFR_92;
  if (DAT_EXTMEM_0f2f == 0) {
    DAT_EXTMEM_0f32 = DPX;
    if (DAT_EXTMEM_0f32 != 0) {
      if ((DAT_EXTMEM_0f32 >> 6 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xbf;
        bVar1 = DAT_SFR_9a;
        DAT_SFR_9a = bVar1 | 1;
        return;
      }
      if ((DAT_EXTMEM_0f32 >> 5 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xdf;
        return;
      }
      if ((DAT_EXTMEM_0f32 >> 4 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xef;
        FUN_CODE_0200();
        goto LAB_CODE_8fef;
      }
      if ((DAT_EXTMEM_0f32 >> 2 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xfb;
        return;
      }
      if ((DAT_EXTMEM_0f32 >> 1 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xfd;
        return;
      }
      if ((DAT_EXTMEM_0f32 & 1) != 0) {
        bVar1 = DPX;
        DPX = bVar1 & 0xfe;
        FUN_CODE_a1c0();
      }
    }
  }
  else {
    if ((DAT_EXTMEM_0f2f >> 3 & 1) != 0) {
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0xf7;
      return;
    }
    bVar1 = DAT_SFR_92;
    DAT_SFR_92 = bVar1 & 0xe7;
    bVar1 = DAT_SFR_92;
    DAT_SFR_92 = bVar1 & 0x9f;
    if ((char)DAT_EXTMEM_0f2f < '\0') {
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0x7f;
      FUN_CODE_a887();
      return;
    }
    if ((DAT_EXTMEM_0f2f >> 4 & 1) != 0) {
      FUN_CODE_95f2();
      return;
    }
    if ((DAT_EXTMEM_0f2f >> 2 & 1) != 0) {
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0xfb;
      return;
    }
    if ((DAT_EXTMEM_0f2f >> 1 & 1) != 0) {
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0xfd;
      FUN_CODE_a8cb();
      return;
    }
    if ((DAT_EXTMEM_0f2f & 1) != 0) {
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0xfe;
      bVar1 = DAT_SFR_91;
      DAT_SFR_91 = bVar1 | 0x20;
      nop();
      nop();
      nop();
      nop();
      nop();
      nop();
      bVar1 = DAT_SFR_91;
      DAT_SFR_91 = bVar1 & 0xdf;
      FUN_CODE_a887();
LAB_CODE_8fef:
      bVar1 = DAT_SFR_92;
      DAT_SFR_92 = bVar1 & 0xbf;
      bVar1 = HADDR;
      HADDR = bVar1 | 1;
      return;
    }
  }
  return;
}



===== FUN_CODE_9015 CODE:9015 size=173 =====

byte FUN_CODE_9015(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  
  if (DAT_EXTMEM_0f2e == 0 && DAT_EXTMEM_0f2d == 0) {
    DAT_EXTMEM_0f40 = 2;
    bVar3 = DAT_SFR_9b;
    DAT_SFR_9b = bVar3 & 0xf0;
    _f_0 = 0;
    return 2;
  }
  if ((DAT_EXTMEM_0f2d < (byte)-(((DAT_EXTMEM_0f2e < 9) << 7) >> 7)) << 7 < '\0') {
    bVar3 = DAT_EXTMEM_0f2d;
    if (DAT_EXTMEM_0f2d == 0) {
      bVar3 = DAT_EXTMEM_0f2e ^ 8;
    }
    if (bVar3 != 0) {
      DAT_EXTMEM_0f40 = 2;
      if (_f_0 == '\0') {
        FUN_CODE_9570(DAT_EXTMEM_0f2e,DAT_EXTMEM_0f38,DAT_EXTMEM_0f39);
      }
      else {
        FUN_CODE_a369(DAT_EXTMEM_0f18,BANK0_R6,1,DAT_EXTMEM_0f2e,DAT_EXTMEM_0f17);
      }
      DAT_EXTMEM_0f35 = 0;
      bVar3 = DAT_SFR_9b;
      DAT_SFR_9b = bVar3 & 0xf0;
      bVar3 = DAT_SFR_9b;
      DAT_SFR_9b = bVar3 | DAT_EXTMEM_0f2e;
      _f_0 = 0;
      return DAT_EXTMEM_0f2e;
    }
    FUN_CODE_9565(1,0xf40);
    bVar3 = 0;
    DAT_EXTMEM_0f2d = 0;
    DAT_EXTMEM_0f2e = '\0';
    pbVar4 = &DAT_EXTMEM_0f35;
  }
  else {
    DAT_EXTMEM_0f40 = 1;
    DAT_EXTMEM_0f2e = DAT_EXTMEM_0f2e - 8;
    FUN_CODE_9565();
    bVar1 = 0xf7 < DAT_EXTMEM_0f39;
    DAT_EXTMEM_0f39 = DAT_EXTMEM_0f39 + 8;
    pbVar4 = &DAT_EXTMEM_0f38;
    bVar3 = DAT_EXTMEM_0f38 - ((bVar1 << 7) >> 7);
  }
  *pbVar4 = bVar3;
  bVar2 = DAT_SFR_9b;
  DAT_SFR_9b = bVar2 & 0xf0;
  bVar2 = DAT_SFR_9b;
  DAT_SFR_9b = bVar2 | 8;
  return bVar3;
}



===== FUN_CODE_9108 CODE:9108 size=169 =====

byte FUN_CODE_9108(byte param_1,byte param_2)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  
  if (_d_4 != '\0') {
    return param_1;
  }
  if (_e_3 != '\0') {
    return param_1;
  }
  bVar2 = 0;
  if ((DAT_EXTMEM_009d != '\x04') && (bVar2 = 0, DAT_EXTMEM_009d != '\a')) {
    if (DAT_EXTMEM_009d != '\f') {
      bVar2 = 0;
      if (DAT_EXTMEM_009d == '-') goto LAB_CODE_915b;
      if (DAT_EXTMEM_009d != '\t') {
        if (DAT_EXTMEM_08db == DAT_EXTMEM_095f) {
          return 0;
        }
        DAT_EXTMEM_08db = 0;
        DAT_EXTMEM_095f = 0;
        bVar2 = FUN_CODE_43ca(0x9b,3,1,0xff,0,10);
        return bVar2;
      }
    }
    bVar2 = 1;
    cVar1 = BANK0_R6 + '\x01';
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar2 = bVar2 << 1;
    }
    cVar1 = ((5 < param_2) << 7) >> 7;
    if (_8_2 == '\x01') {
      pbVar4 = (byte *)CONCAT11('\f' - cVar1,param_2 - 6);
      bVar2 = *pbVar4 & ~bVar2;
      *pbVar4 = bVar2;
    }
    else {
      pbVar4 = (byte *)CONCAT11('\f' - cVar1,param_2 - 6);
      bVar2 = *pbVar4 | bVar2;
      *pbVar4 = bVar2;
    }
  }
LAB_CODE_915b:
  if ((_8_2 != '\x01') &&
     (bVar2 = ~*(byte *)CONCAT11('\x03' - (((100 < DAT_EXTMEM_08db) << 7) >> 7),
                                 DAT_EXTMEM_08db + 0x9b), bVar2 == 0)) {
    *(undefined1 *)CONCAT11('\x03' - (((100 < DAT_EXTMEM_08db) << 7) >> 7),DAT_EXTMEM_08db + 0x9b) =
         DAT_EXTMEM_02e0;
    bVar3 = DAT_EXTMEM_08db + 1;
    bVar2 = DAT_EXTMEM_08db - 9;
    DAT_EXTMEM_08db = bVar3;
    if (9 < bVar3) {
      DAT_EXTMEM_08db = 0;
      return 0;
    }
  }
  return bVar2;
}



===== FUN_CODE_9259 CODE:9259 size=166 =====

void FUN_CODE_9259(void)

{
  EA = 0;
  FUN_CODE_a94c();
  FUN_CODE_8823();
  FUN_CODE_99ac();
  EA = 1;
  FUN_CODE_a887();
  FUN_CODE_a9a8(200);
  _8_2 = 1;
  _6_3 = '\x01';
  DAT_EXTMEM_095d = 0;
  DAT_EXTMEM_095e = 0;
  DAT_EXTMEM_0e36 = 0;
  DAT_INTMEM_74 = 6;
  BANK3_R3 = 6;
  BANK3_R2 = 0xff;
  DAT_EXTMEM_02e6 = 3;
  DAT_EXTMEM_02e7 = 0xa6;
  FUN_CODE_aa33();
  FUN_CODE_9ed3();
  do {
    IEN1 = 0;
    if ((_c_0 != '\0') && (_b_1 != '\x01')) {
      FUN_CODE_9dad(0);
      _c_0 = '\0';
      _c_2 = '\x01';
      _9_4 = 0;
    }
    if ((_c_2 != '\0') && (_b_1 != '\x01')) {
      FUN_CODE_99ac();
      _a_1 = 1;
      _c_2 = '\0';
      _b_5 = 1;
      if (_6_3 != '\0') {
        DAT_EXTMEM_0e1f = DAT_EXTMEM_009d;
        DAT_EXTMEM_009d = 0x26;
      }
    }
    if (_b_1 != '\x01') {
      FUN_CODE_1108();
      FUN_CODE_8759();
      FUN_CODE_a65e();
      FUN_CODE_4f8a();
    }
    if (((_f_1 == '\x01') || (0x27U - (((DAT_EXTMEM_02e4 < 0x11) << 7) >> 7) <= DAT_EXTMEM_02e3)) &&
       (DAT_EXTMEM_0317 == 0)) {
      IEN1 = 0;
      _f_1 = '\0';
      DAT_EXTMEM_02e3 = DAT_EXTMEM_0317;
      DAT_EXTMEM_02e4 = DAT_EXTMEM_0317;
      FUN_CODE_9708();
    }
  } while( true );
}



===== vector_target_0000 CODE:93a0 size=146 =====

void vector_target_0000(void)

{
  undefined1 *puVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  byte *pbVar5;
  byte bVar6;
  byte bVar7;
  undefined1 *puVar8;
  byte *pbVar9;
  byte *pbVar10;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar8 = (undefined1 *)0x0;
  cVar4 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar8 = 0;
      puVar8 = puVar8 + 1;
      cVar4 = cVar4 + -1;
    } while (cVar4 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0x7d;
  pbVar9 = &DAT_CODE_967d;
  while( true ) {
    bVar3 = 1;
    bVar6 = *pbVar9;
    if (bVar6 == 0) break;
    bVar7 = bVar6 & 0x3f;
    pbVar10 = pbVar9 + 1;
    if (bVar7 >> 5 != 0) {
      bVar3 = bVar6 & 0x1f;
      bVar7 = pbVar9[1];
      pbVar10 = pbVar9 + 2;
      if (bVar7 != 0) {
        bVar3 = bVar3 + 1;
      }
    }
    pbVar9 = pbVar10;
    cVar2 = CARRY1(bVar6 & 0xc0,bVar6 & 0xc0) << 7;
    if ((bVar6 & 0x40) == 0) {
      pbVar5 = (byte *)*pbVar9;
      pbVar9 = pbVar9 + 1;
      do {
        bVar3 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        if (cVar2 < '\0') {
          *(byte *)ZEXT12(pbVar5) = bVar3;
        }
        else {
          *pbVar5 = bVar3;
        }
        pbVar5 = pbVar5 + '\x01';
        bVar7 = bVar7 - 1;
      } while (bVar7 != 0);
    }
    else if (cVar2 < '\0') {
      do {
        bVar3 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        pbVar5 = (byte *)((bVar3 & 0x7f) >> 3 | 0x20);
        bVar6 = *(byte *)((ushort)((bVar3 & 7) + 0xc) + 0x93e1);
        if ((char)bVar3 < '\0') {
          bVar6 = bVar6 | *pbVar5;
        }
        else {
          bVar6 = ~bVar6 & *pbVar5;
        }
        *pbVar5 = bVar6;
        bVar7 = bVar7 - 1;
      } while (bVar7 != 0);
    }
    else {
      pbVar10 = *(byte **)pbVar9;
      pbVar9 = pbVar9 + 2;
      do {
        do {
          bVar6 = *pbVar9;
          pbVar9 = pbVar9 + 1;
          *pbVar10 = bVar6;
          pbVar10 = pbVar10 + 1;
          bVar7 = bVar7 - 1;
        } while (bVar7 != 0);
        bVar3 = bVar3 - 1;
      } while (bVar3 != 0);
    }
  }
  FUN_CODE_9259();
  return;
}



===== FUN_CODE_9565 CODE:9565 size=11 =====

char FUN_CODE_9565(undefined1 param_1,undefined1 *param_2)

{
  byte bVar1;
  
  *param_2 = param_1;
  DAT_EXTMEM_0f09 = DAT_EXTMEM_0f38;
  DAT_EXTMEM_0f0a = DAT_EXTMEM_0f39;
  DAT_EXTMEM_0f41 = '\x11';
  DAT_EXTMEM_0f42 = 8;
  if (_e_6 == '\0') {
    for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
      *(undefined1 *)
       CONCAT11(DAT_EXTMEM_0f41 - ((CARRY1(DAT_EXTMEM_0f42,bVar1) << 7) >> 7),
                DAT_EXTMEM_0f42 + bVar1) = *(undefined1 *)CONCAT11(DAT_EXTMEM_0f09,DAT_EXTMEM_0f0a);
      DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + '\x01';
      if (DAT_EXTMEM_0f0a == '\0') {
        DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + '\x01';
      }
    }
  }
  else {
    for (bVar1 = 0; bVar1 < 8; bVar1 = bVar1 + 1) {
      *(undefined1 *)
       CONCAT11(DAT_EXTMEM_0f41 - ((CARRY1(DAT_EXTMEM_0f42,bVar1) << 7) >> 7),
                DAT_EXTMEM_0f42 + bVar1) = *(undefined1 *)CONCAT11(DAT_EXTMEM_0f09,DAT_EXTMEM_0f0a);
      DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + '\x01';
      if (DAT_EXTMEM_0f0a == '\0') {
        DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + '\x01';
      }
    }
  }
  return bVar1 - 8;
}



===== FUN_CODE_9570 CODE:9570 size=130 =====

char FUN_CODE_9570(byte param_1,char param_2,char param_3)

{
  byte bVar1;
  char cVar2;
  
  DAT_EXTMEM_0f41 = '\x11';
  DAT_EXTMEM_0f42 = 8;
  DAT_EXTMEM_0f09 = param_2;
  DAT_EXTMEM_0f0a = param_3;
  if (_e_6 == '\0') {
    for (bVar1 = 0; cVar2 = bVar1 - param_1, bVar1 < param_1; bVar1 = bVar1 + 1) {
      *(undefined1 *)
       CONCAT11(DAT_EXTMEM_0f41 - ((CARRY1(DAT_EXTMEM_0f42,bVar1) << 7) >> 7),
                DAT_EXTMEM_0f42 + bVar1) = *(undefined1 *)CONCAT11(DAT_EXTMEM_0f09,DAT_EXTMEM_0f0a);
      DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + '\x01';
      if (DAT_EXTMEM_0f0a == '\0') {
        DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + '\x01';
      }
    }
  }
  else {
    for (bVar1 = 0; cVar2 = bVar1 - param_1, bVar1 < param_1; bVar1 = bVar1 + 1) {
      *(undefined1 *)
       CONCAT11(DAT_EXTMEM_0f41 - ((CARRY1(DAT_EXTMEM_0f42,bVar1) << 7) >> 7),
                DAT_EXTMEM_0f42 + bVar1) = *(undefined1 *)CONCAT11(DAT_EXTMEM_0f09,DAT_EXTMEM_0f0a);
      DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + '\x01';
      if (DAT_EXTMEM_0f0a == '\0') {
        DAT_EXTMEM_0f09 = DAT_EXTMEM_0f09 + '\x01';
      }
    }
  }
  return cVar2;
}



===== FUN_CODE_95f2 CODE:95f2 size=139 =====

void FUN_CODE_95f2(void)

{
  bool bVar1;
  byte bVar2;
  short sVar3;
  
  DAT_EXTMEM_0f07 = 0x55;
  DAT_EXTMEM_0f08 = 0xa9;
  DAT_EXTMEM_0f35 = 0;
  FUN_CODE_0100();
  DAT_EXTMEM_0f3e = '\0';
  while( true ) {
    bVar2 = DAT_EXTMEM_0f07;
    if ((*(char *)CONCAT11(DAT_EXTMEM_0f07,DAT_EXTMEM_0f08) == BANK0_R4) &&
       (bVar2 = DAT_EXTMEM_0f1c,
       *(char *)(CONCAT11(DAT_EXTMEM_0f07,DAT_EXTMEM_0f08) + 1) == BANK0_R6)) break;
    bVar1 = 0xfc < DAT_EXTMEM_0f08;
    DAT_EXTMEM_0f08 = DAT_EXTMEM_0f08 + 3;
    DAT_EXTMEM_0f07 = DAT_EXTMEM_0f07 - ((bVar1 << 7) >> 7);
    if (0x55U - (((DAT_EXTMEM_0f08 < 0xe8) << 7) >> 7) <= DAT_EXTMEM_0f07) {
LAB_CODE_9661:
      sVar3 = CONCAT11('U' - (((0x95U < (byte)(DAT_EXTMEM_0f3e * '\x03')) << 7) >> 7),
                       DAT_EXTMEM_0f3e * '\x03' + 0x6a);
      FUN_CODE_43c4(*(undefined1 *)(sVar3 + 2),*(undefined1 *)(sVar3 + 1),DAT_EXTMEM_0f1b,bVar2);
      return;
    }
  }
  DAT_EXTMEM_0f3e = *(char *)(CONCAT11(DAT_EXTMEM_0f07,DAT_EXTMEM_0f08) + 2);
  bVar2 = DAT_EXTMEM_0f07;
  goto LAB_CODE_9661;
}



===== FUN_CODE_9708 CODE:9708 size=138 =====

void FUN_CODE_9708(void)

{
  byte bVar1;
  
  DAT_EXTMEM_0f25 = 0;
  DAT_EXTMEM_0f26 = 0;
  _6_7 = 0;
  FUN_CODE_a6dd();
  EA = 0;
  EX0 = 0;
  _f_5 = '\0';
  FUN_CODE_006e();
  P0_7 = 1;
  HIFLG = 0;
  DAT_SFR_ba = 0xf3;
  DAT_SFR_b6 = 0x40;
  bVar1 = IE;
  IE = bVar1 | 2;
  EA = 1;
  bVar1 = DAT_SFR_91;
  DAT_SFR_91 = bVar1 | 1;
  bVar1 = IPL1;
  IPL1 = bVar1 & 0xfb;
  bVar1 = DAT_SFR_bc;
  DAT_SFR_bc = bVar1 & 0xfe;
  bVar1 = DAT_SFR_bc;
  DAT_SFR_bc = bVar1 & 0xfd;
  bVar1 = DAT_SFR_94;
  DAT_SFR_94 = bVar1 | 0x85;
  bVar1 = DAT_SFR_92;
  DAT_SFR_92 = bVar1 & 0x7a;
  SADDR = 1;
  nop();
  nop();
  nop();
  nop();
  nop();
  DAT_SFR_8e = 0x55;
  bVar1 = PCON;
  PCON = bVar1 | 2;
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_a325(0);
  IEN1 = 0;
  DAT_SFR_bc = 3;
  IPL1 = 0xc;
  bVar1 = DAT_SFR_92;
  DAT_SFR_92 = bVar1 & 0xfd;
  bVar1 = DAT_SFR_91;
  DAT_SFR_91 = bVar1 & 0xfe;
  if ((_f_5 != '\0') && (_e_7 != '\0')) {
    bVar1 = DAT_SFR_91;
    DAT_SFR_91 = bVar1 | 2;
    _f_5 = '\0';
  }
  DAT_SFR_94 = 0x5f;
  bVar1 = SADDR;
  SADDR = bVar1 | 1;
  FUN_CODE_9f89(0);
  DAT_EXTMEM_0f25 = 0;
  DAT_EXTMEM_0f26 = 0;
  _f_1 = 0;
  EA = 1;
  EX0 = 1;
  _6_7 = 0;
  FUN_CODE_5e51();
  FUN_CODE_aa33();
  bVar1 = SADDR;
  SADDR = bVar1 & 0xbf;
  return;
}



===== FUN_CODE_9792 CODE:9792 size=135 =====

void FUN_CODE_9792(void)

{
  char cVar1;
  byte bVar2;
  undefined1 *puVar3;
  
  bVar2 = 0;
  cVar1 = '\0';
  DAT_EXTMEM_0ed1 = 0;
  DAT_EXTMEM_0ed2 = 0;
  DAT_EXTMEM_0ed3 = 0;
  DAT_EXTMEM_0ed4 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11(cVar1 + -0x3c,bVar2);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while (bVar2 != 0x80 || cVar1 != '\0');
  DAT_EXTMEM_09c6 = DAT_EXTMEM_0315;
  DAT_EXTMEM_09c8 = DAT_EXTMEM_0317;
  FUN_CODE_a252(99,0xc6,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0xf6 < bVar2) << 7) >> 7)) + '\x03',bVar2 + 9) =
         *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while (bVar2 != 0x80 || cVar1 != '\0');
  if ((DAT_EXTMEM_0312 == '\0') << 7 < '\0') {
    puVar3 = &DAT_EXTMEM_0313;
  }
  else {
    puVar3 = &DAT_EXTMEM_0314;
  }
  DAT_EXTMEM_009d = *puVar3;
  return;
}



===== FUN_CODE_9819 CODE:9819 size=135 =====

void FUN_CODE_9819(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_0eec = (&DAT_CODE_25fb)[DAT_EXTMEM_0d14];
  uVar1 = DAT_EXTMEM_011d;
  FUN_CODE_ac5e(DAT_EXTMEM_0eec);
  uVar2 = uEXTMEM0000;
  DAT_EXTMEM_0e41 = param_1;
  DAT_EXTMEM_0e42 = uVar1;
  FUN_CODE_ac5e(DAT_EXTMEM_0eec);
  uVar1 = DAT_EXTMEM_0e20;
  DAT_EXTMEM_0e3d = param_1;
  DAT_EXTMEM_0e3e = uVar2;
  FUN_CODE_ac5e(DAT_EXTMEM_0eec);
  DAT_EXTMEM_0e3a = param_1;
  DAT_EXTMEM_0e3b = uVar1;
  FUN_CODE_ac2d(0x50);
  FUN_CODE_ac2d(0x50);
  FUN_CODE_ac2d(0x50);
  return;
}



===== FUN_CODE_99ac CODE:99ac size=132 =====

void FUN_CODE_99ac(void)

{
  byte bVar1;
  undefined1 *puVar2;
  
  DAT_EXTMEM_0ecb = 0;
  DAT_EXTMEM_0ecc = 0;
  DAT_EXTMEM_0ecd = 0;
  DAT_EXTMEM_0ece = 0;
  DAT_EXTMEM_0ecf = 0;
  DAT_EXTMEM_0ed0 = 0;
  FUN_CODE_308d(0,0x80,9,0xba,0xc6,0);
  if ((DAT_EXTMEM_0a38 == 'Z') && (DAT_EXTMEM_0a39 == -0x5b)) {
    DAT_EXTMEM_0ecb = 0;
    DAT_EXTMEM_0ecc = 0;
    do {
      *(undefined1 *)
       CONCAT11((DAT_EXTMEM_0ecb - (((0xf6 < DAT_EXTMEM_0ecc) << 7) >> 7)) + '\x03',
                DAT_EXTMEM_0ecc + 9) =
           *(undefined1 *)
            CONCAT11((DAT_EXTMEM_0ecb - (((0x45 < DAT_EXTMEM_0ecc) << 7) >> 7)) + '\t',
                     DAT_EXTMEM_0ecc + 0xba);
      DAT_EXTMEM_0ecc = DAT_EXTMEM_0ecc + 1;
      if (DAT_EXTMEM_0ecc == 0) {
        DAT_EXTMEM_0ecb = DAT_EXTMEM_0ecb + 1;
      }
      bVar1 = DAT_EXTMEM_0ecb;
      if (DAT_EXTMEM_0ecb == 0) {
        bVar1 = DAT_EXTMEM_0ecc ^ 0x80;
      }
    } while (bVar1 != 0);
    if ((DAT_EXTMEM_0312 == '\0') << 7 < '\0') {
      puVar2 = &DAT_EXTMEM_0313;
    }
    else {
      puVar2 = &DAT_EXTMEM_0314;
    }
    DAT_EXTMEM_009d = *puVar2;
    return;
  }
  FUN_CODE_9792();
  return;
}



===== FUN_CODE_9a30 CODE:9a30 size=120 =====

void FUN_CODE_9a30(undefined1 param_1)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  
  DAT_EXTMEM_0edf = 0;
  DAT_EXTMEM_0ede = param_1;
  do {
    bVar2 = 0;
    do {
      DAT_EXTMEM_0ee0 = 0;
      do {
        bVar3 = (byte)((ushort)DAT_EXTMEM_0edf * 0x12);
        bVar4 = bVar3 + 0x24;
        cVar5 = (char)((ushort)DAT_EXTMEM_0edf * 0x12 >> 8) +
                ('\x04' - (((0xdb < bVar3) << 7) >> 7));
        bVar3 = DAT_EXTMEM_0ee0;
        uVar1 = DAT_EXTMEM_0ede;
        FUN_CODE_4392(bVar2,3);
        *(undefined1 *)CONCAT11(cVar5 - ((CARRY1(bVar4,bVar3) << 7) >> 7),bVar4 + bVar3) = uVar1;
        DAT_EXTMEM_0ee0 = DAT_EXTMEM_0ee0 + 1;
      } while (DAT_EXTMEM_0ee0 != 3);
      bVar3 = DAT_EXTMEM_0edf * '\x06' + 0x17;
      *(undefined1 *)
       CONCAT11(-((CARRY1(bVar3,bVar2) << 7) >> 7) - (((0xe8 < DAT_EXTMEM_0edf * '\x06') << 7) >> 7)
                ,bVar3 + bVar2) = DAT_EXTMEM_0ede;
      bVar2 = bVar2 + 1;
    } while (bVar2 != 6);
    DAT_EXTMEM_0edf = DAT_EXTMEM_0edf + 1;
  } while (DAT_EXTMEM_0edf != 0x15);
  return;
}



===== FUN_CODE_9b1f CODE:9b1f size=118 =====

void FUN_CODE_9b1f(void)

{
  if (DAT_EXTMEM_0d12 == '\x02') {
    if (_8_2 != '\x01') {
      _7_7 = 1;
      _9_2 = 1;
    }
  }
  else if (DAT_EXTMEM_0d12 == '\x04') {
    if (((_8_2 != '\0') && (DAT_EXTMEM_02ce == '\0')) && (DAT_EXTMEM_02cf == BANK0_R7)) {
      _7_7 = 1;
      _9_3 = 1;
      _9_4 = 0;
      FUN_CODE_3a4f(DAT_EXTMEM_0d10);
      return;
    }
  }
  else {
    if (DAT_EXTMEM_0d12 != '\x01') {
      return;
    }
    if (_8_2 == '\x01') {
      return;
    }
    _7_7 = 1;
  }
  if (_8_2 != '\x01') {
    FUN_CODE_4361(0x2db);
    nop();
    nop();
    nop();
    nop();
    _9_4 = 1;
    DAT_EXTMEM_02ce = '\0';
    DAT_EXTMEM_02cf = DAT_EXTMEM_0d10;
    DAT_EXTMEM_02d1 = 0;
    DAT_EXTMEM_02d2 = DAT_EXTMEM_0d11;
    DAT_EXTMEM_02d0 = DAT_EXTMEM_0d12;
    DAT_EXTMEM_02cc = 0;
    DAT_EXTMEM_02cd = 0;
  }
  return;
}



===== vector_target_0003 CODE:9d49 size=100 =====

undefined1 vector_target_0003(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  undefined1 uVar11;
  undefined1 uVar12;
  
  uVar12 = BANK0_R7;
  uVar11 = BANK0_R6;
  uVar10 = BANK0_R5;
  uVar9 = BANK0_R4;
  uVar8 = BANK0_R3;
  uVar7 = BANK0_R2;
  uVar6 = BANK0_R1;
  uVar5 = BANK0_R0;
  uVar3 = DAT_SFR_86;
  uVar4 = WCON;
  uVar1 = DPXL;
  uVar2 = DAT_SFR_85;
  DAT_SFR_86 = 0;
  WCON = 0;
  TR2 = 0;
  if ((((_c_0 != '\x01') && (_c_2 != '\x01')) && (_b_1 != '\x01')) && (_7_2 != '\x01')) {
    FUN_CODE_1ded();
  }
  TF2 = 0;
  DAT_SFR_86 = 0;
  DAT_SFR_85 = uVar2;
  DPXL = uVar1;
  WCON = uVar4;
  DAT_SFR_86 = uVar3;
  BANK0_R7 = uVar12;
  BANK0_R6 = uVar11;
  BANK0_R5 = uVar10;
  BANK0_R4 = uVar9;
  BANK0_R3 = uVar8;
  BANK0_R2 = uVar7;
  BANK0_R1 = uVar6;
  BANK0_R0 = uVar5;
  return param_1;
}



===== FUN_CODE_9dad CODE:9dad size=100 =====

void FUN_CODE_9dad(void)

{
  char cVar1;
  byte bVar2;
  
  DAT_EXTMEM_0ecc = 0;
  DAT_EXTMEM_0ecd = 0;
  FUN_CODE_308d(0,0x80,9,0xba,0xc6,0);
  cVar1 = '\0';
  bVar2 = 0;
  do {
    *(undefined1 *)CONCAT11((cVar1 - (((0x45 < bVar2) << 7) >> 7)) + '\t',bVar2 + 0xba) =
         *(undefined1 *)CONCAT11((cVar1 - (((0xf6 < bVar2) << 7) >> 7)) + '\x03',bVar2 + 9);
    bVar2 = bVar2 + 1;
    if (bVar2 == 0) {
      cVar1 = cVar1 + '\x01';
    }
  } while (bVar2 != 0x80 || cVar1 != '\0');
  IEN1 = 0;
  bVar2 = EA;
  _e_0 = bVar2 & 1;
  EA = 0;
  FUN_CODE_aaee(0);
  DAT_EXTMEM_0302 = 99;
  FUN_CODE_a62f(99);
  DAT_EXTMEM_0302 = 0;
  _b_1 = 1;
  DAT_INTMEM_72 = 0;
  DAT_INTMEM_73 = 0;
  FUN_CODE_aa97();
  EA = _e_0 & 1;
  return;
}



===== FUN_CODE_9e73 CODE:9e73 size=96 =====

void FUN_CODE_9e73(void)

{
  char cVar1;
  
  FUN_CODE_43ca(0xae,8,1,0,0,8);
  FUN_CODE_43ca(0x7c,9,1,0,0,0x10);
  DAT_EXTMEM_09b7 = 2;
  DAT_EXTMEM_09b8 = 0;
  DAT_EXTMEM_09b9 = 0;
  DAT_EXTMEM_0979 = 1;
  DAT_EXTMEM_097a = 0;
  _7_0 = 1;
  _a_0 = 1;
  _7_3 = 1;
  _a_6 = 1;
  DAT_EXTMEM_0c3f = 2;
  cVar1 = '\0';
  do {
    *(undefined1 *)
     CONCAT11('\f' - (((0xadU < (byte)(cVar1 * '\x1c')) << 7) >> 7),cVar1 * '\x1c' + 0x52) = 0;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x06');
  DAT_EXTMEM_0308 = 0;
  DAT_EXTMEM_0306 = 0;
  return;
}



===== FUN_CODE_9ed3 CODE:9ed3 size=91 =====

char FUN_CODE_9ed3(void)

{
  char cVar1;
  
  DAT_EXTMEM_0ecb = 0;
  while( true ) {
    if (8 < DAT_EXTMEM_0ecb) {
      return DAT_EXTMEM_0ecb - 9;
    }
    if (**(char **)CONCAT11(-0x55 - (((0x86 < DAT_EXTMEM_0ecb * '\x02') << 7) >> 7),
                            DAT_EXTMEM_0ecb * '\x02' + 0x79) != -0x5b) break;
    DAT_EXTMEM_0ecb = DAT_EXTMEM_0ecb + 1;
  }
  FUN_CODE_a9a8(200);
  FUN_CODE_a9a8(200);
  FUN_CODE_a9a8(200);
  FUN_CODE_a9a8(200);
  FUN_CODE_a9a8(200);
  FUN_CODE_a9a8(200);
  FUN_CODE_9792();
  FUN_CODE_868e();
  cVar1 = FUN_CODE_7108();
  return cVar1;
}



===== FUN_CODE_9f89 CODE:9f89 size=90 =====

undefined1 FUN_CODE_9f89(void)

{
  EPCON = 0x9c;
  RXSTAT = 0x3f;
  RXDAT = 0x3f;
  RXCON = 0x3f;
  RXFLG = 0x4d;
  RXCNTL = 0x87;
  RXCNTH = 0xff;
  PSW1 = 0x60;
  CL = 0xf8;
  CCAP0L = 0x3f;
  CCAP1L = 0x3f;
  CCAP2L = 0x3f;
  CCAP3L = 0x6f;
  CCAP4L = 0x9f;
  DAT_SFR_ef = 0xff;
  CMOD = 0xdf;
  P0 = 0x1c;
  P1 = 0;
  SCON = 0;
  P2 = 0;
  P3 = 0x4d;
  TCON = 0x87;
  FIFLG = 0xff;
  DAT_SFR_f8 = 0;
  TH0 = 5;
  DAT_SFR_a5 = 0;
  TH0 = 0x45;
  WDTRST = 0;
  TH0 = 0x85;
  DAT_SFR_bb = 0;
  TH0 = 0xc5;
  TH1 = 0;
  return 0;
}



===== FUN_CODE_a0dd CODE:a0dd size=62 =====

byte FUN_CODE_a0dd(byte param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  FUN_CODE_43f6(0xf5a);
  cVar1 = '\x10';
  if (((param_1 == 0 && param_2 == 0) && param_3 == 0) && param_4 == 0) {
    param_1 = 0xa5;
    param_2 = 0xa5;
  }
  do {
    bVar5 = param_1 >> 1;
    bVar2 = param_2 >> 1 | param_1 << 7;
    bVar3 = param_3 >> 1 | param_2 << 7;
    bVar4 = param_4 >> 1 | param_3 << 7;
    if ((char)(param_4 << 7) < '\0') {
      bVar5 = bVar5 ^ 0xcc;
      bVar2 = bVar2 ^ 0x4c;
      bVar3 = bVar3 ^ 0x4e;
      bVar4 = bVar4 ^ 0xce;
    }
    cVar1 = cVar1 + -1;
    param_1 = bVar5;
    param_2 = bVar2;
    param_3 = bVar3;
    param_4 = bVar4;
  } while (cVar1 != '\0');
  FUN_CODE_4355(0xf5a);
  return bVar3 & 0x7f;
}



===== FUN_CODE_a1c0 CODE:a1c0 size=74 =====

char FUN_CODE_a1c0(void)

{
  byte bVar1;
  char cVar2;
  
  if (DAT_EXTMEM_0f40 == '\x01') {
    cVar2 = FUN_CODE_9015();
    bVar1 = HADDR;
    HADDR = bVar1 | 4;
    bVar1 = DAT_SFR_92;
    DAT_SFR_92 = bVar1 & 0xbf;
    bVar1 = HADDR;
    HADDR = bVar1 | 1;
    return cVar2;
  }
  if ((DAT_EXTMEM_0f40 != '\x02') && (DAT_EXTMEM_0f40 != '\t')) {
    DAT_EXTMEM_0f40 = 0;
    bVar1 = HADDR;
    HADDR = bVar1 | 8;
    bVar1 = DAT_SFR_92;
    DAT_SFR_92 = bVar1 & 0xbf;
    bVar1 = HADDR;
    HADDR = bVar1 | 1;
    cVar2 = DAT_EXTMEM_0f1b;
    if ((DAT_EXTMEM_0f1b == '\0') && (cVar2 = DAT_EXTMEM_0f1c, DAT_EXTMEM_0f1c == '\x05')) {
      DAT_SFR_96 = DAT_EXTMEM_0f1d;
      cVar2 = DAT_EXTMEM_0f1d;
    }
    return cVar2;
  }
  bVar1 = DAT_SFR_92;
  DAT_SFR_92 = bVar1 & 0xbf;
  bVar1 = HADDR;
  HADDR = bVar1 | 1;
  bVar1 = HADDR;
  HADDR = bVar1 | 8;
  return DAT_EXTMEM_0f40;
}



===== FUN_CODE_a20a CODE:a20a size=72 =====

void FUN_CODE_a20a(void)

{
  byte bVar1;
  
  bVar1 = SBUF;
  if (((bVar1 >> 2 & 1) != 1) && (DAT_EXTMEM_0317 == '\0')) {
    if (_7_0 != '\0') {
      _7_0 = '\0';
      DAT_EXTMEM_0f3a = '\x11';
      DAT_EXTMEM_0f3b = 0x20;
      bVar1 = 0;
      do {
        *(undefined1 *)
         CONCAT11(DAT_EXTMEM_0f3a - ((CARRY1(DAT_EXTMEM_0f3b,bVar1) << 7) >> 7),
                  DAT_EXTMEM_0f3b + bVar1) =
             *(undefined1 *)CONCAT11('\b' - (((0x51 < bVar1) << 7) >> 7),bVar1 + 0xae);
        bVar1 = bVar1 + 1;
      } while (bVar1 != 8);
      DAT_SFR_9c = 8;
      bVar1 = SBUF;
      SBUF = bVar1 | 4;
    }
    _6_7 = 0;
  }
  return;
}



===== FUN_CODE_a252 CODE:a252 size=71 =====

void FUN_CODE_a252(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  byte bVar1;
  
  bVar1 = EA;
  _e_5 = bVar1 & 1;
  EA = 0;
  DAT_EXTMEM_0f0b = param_2;
  DAT_EXTMEM_0f0c = param_3;
  DAT_EXTMEM_0f0d = param_1;
  FUN_CODE_aaee();
  DAT_EXTMEM_0302 = DAT_EXTMEM_0f0d;
  FUN_CODE_a62f(DAT_EXTMEM_0f0d);
  DAT_EXTMEM_0f13 = 2;
  DAT_EXTMEM_0f14 = 0;
  FUN_CODE_0181(0xba,9,1,DAT_EXTMEM_0f0b,DAT_EXTMEM_0f0c);
  DAT_EXTMEM_0302 = 0;
  FUN_CODE_aa97();
  EA = _e_5 & 1;
  return;
}



===== FUN_CODE_a299 CODE:a299 size=1 =====

undefined1 FUN_CODE_a299(char param_1)

{
  byte bVar1;
  
  *(undefined1 *)(param_1 + '\x01') = 0;
  _c_1 = 1;
  T0 = 0;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 0x10;
  T0 = 0;
  for (bVar1 = 0; bVar1 < 5; bVar1 = bVar1 + 1) {
  }
  DAT_INTMEM_38 = BANK0_R6;
  DAT_INTMEM_70 = 0;
  DAT_INTMEM_74 = BANK0_R7;
  DAT_INTMEM_75 = BANK0_R3;
  DAT_INTMEM_71 = 0;
  DAT_SFR_aa = DAT_INTMEM_33;
  return DAT_INTMEM_33;
}



===== FUN_CODE_a29a CODE:a29a size=6 =====

undefined1 FUN_CODE_a29a(undefined1 param_1,char param_2)

{
  byte bVar1;
  
  *(undefined1 *)(param_2 + '\x01') = param_1;
  _c_1 = 1;
  T0 = 0;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 0x10;
  T0 = 0;
  for (bVar1 = 0; bVar1 < 5; bVar1 = bVar1 + 1) {
  }
  DAT_INTMEM_38 = BANK0_R6;
  DAT_INTMEM_70 = 0;
  DAT_INTMEM_74 = BANK0_R7;
  DAT_INTMEM_75 = BANK0_R3;
  DAT_INTMEM_71 = 0;
  DAT_SFR_aa = DAT_INTMEM_33;
  return DAT_INTMEM_33;
}



===== FUN_CODE_a2a0 CODE:a2a0 size=64 =====

undefined1 FUN_CODE_a2a0(char param_1)

{
  byte bVar1;
  
  _c_1 = 1;
  T0 = 0;
  bVar1 = RXFLG;
  RXFLG = bVar1 | 0x10;
  T0 = 0;
  for (bVar1 = 0; bVar1 < param_1 - 1U; bVar1 = bVar1 + 1) {
  }
  *(undefined1 *)(param_1 + '2') = BANK0_R6;
  DAT_INTMEM_70 = 0;
  DAT_INTMEM_74 = BANK0_R7;
  DAT_INTMEM_75 = BANK0_R3;
  DAT_INTMEM_71 = 0;
  DAT_SFR_aa = DAT_INTMEM_33;
  return DAT_INTMEM_33;
}



===== FUN_CODE_a325 CODE:a325 size=22 =====

char FUN_CODE_a325(char param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  IEN1 = param_1;
  EA = 0;
  DAT_SFR_b6 = param_1;
  HIFLG = param_1;
  DAT_SFR_ba = param_1;
  bVar2 = IE;
  IE = bVar2 & 0xfd;
  bVar2 = IPL1;
  IPL1 = bVar2 | 8;
  bVar2 = DAT_SFR_bc;
  DAT_SFR_bc = bVar2 | 2;
  IEN1 = 0;
  bVar3 = 0;
  bVar2 = 0;
  while (bVar1 = param_1 - (((bVar3 < 0x14) << 7) >> 7), bVar2 < bVar1) {
    IEN1 = 0;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    bVar3 = bVar3 + 1;
    if (bVar3 == 0) {
      bVar2 = bVar2 + 1;
    }
  }
  return bVar2 - bVar1;
}



===== FUN_CODE_a33b CODE:a33b size=33 =====

char FUN_CODE_a33b(char param_1,byte param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  IEN1 = 0;
  bVar3 = 0;
  bVar2 = 0;
  while (bVar1 = param_1 - (((bVar3 < param_2) << 7) >> 7), bVar2 < bVar1) {
    IEN1 = 0;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    bVar3 = bVar3 + 1;
    if (bVar3 == 0) {
      bVar2 = bVar2 + 1;
    }
  }
  return bVar2 - bVar1;
}



===== FUN_CODE_a369 CODE:a369 size=68 =====

void FUN_CODE_a369(byte param_1)

{
  byte bVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_0f41 = '\x11';
  DAT_EXTMEM_0f42 = 8;
  DAT_EXTMEM_0f0a = 0;
  DAT_EXTMEM_0f09 = param_1;
  while( true ) {
    if (DAT_EXTMEM_0f09 <= DAT_EXTMEM_0f0a) break;
    bVar1 = DAT_EXTMEM_0f0a;
    uVar2 = FUN_CODE_41ca(DAT_EXTMEM_0f0a - DAT_EXTMEM_0f09);
    *(undefined1 *)
     CONCAT11(DAT_EXTMEM_0f41 - ((CARRY1(DAT_EXTMEM_0f42,bVar1) << 7) >> 7),DAT_EXTMEM_0f42 + bVar1)
         = uVar2;
    DAT_EXTMEM_0f0a = DAT_EXTMEM_0f0a + 1;
  }
  return;
}



===== vector_target_003B CODE:a3f1 size=67 =====

undefined1 vector_target_003B(undefined1 param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 uVar10;
  
  uVar10 = BANK0_R7;
  uVar9 = BANK0_R6;
  uVar8 = BANK0_R5;
  uVar7 = BANK0_R4;
  uVar6 = BANK0_R3;
  uVar5 = BANK0_R2;
  uVar4 = BANK0_R1;
  uVar3 = BANK0_R0;
  uVar1 = DAT_SFR_86;
  uVar2 = WCON;
  FUN_CODE_8f66();
  WCON = uVar2;
  DAT_SFR_86 = uVar1;
  BANK0_R7 = uVar10;
  BANK0_R6 = uVar9;
  BANK0_R5 = uVar8;
  BANK0_R4 = uVar7;
  BANK0_R3 = uVar6;
  BANK0_R2 = uVar5;
  BANK0_R1 = uVar4;
  BANK0_R0 = uVar3;
  return param_1;
}



===== FUN_CODE_a4b6 CODE:a4b6 size=60 =====

void FUN_CODE_a4b6(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  cVar1 = '\0';
  DAT_EXTMEM_0ede = param_3;
  DAT_EXTMEM_0edf = param_2;
  DAT_EXTMEM_0ee0 = param_1;
  do {
    cVar2 = '\0';
    do {
      IEN1 = 0;
      cVar3 = BANK0_R2;
      FUN_CODE_7e03(0,BANK0_R1);
      if (cVar3 == '\0') {
        DAT_EXTMEM_0eef = DAT_EXTMEM_0edf;
        FUN_CODE_6e7a(0xee0,DAT_EXTMEM_0ede,BANK0_R2,BANK0_R1);
      }
      cVar2 = cVar2 + '\x01';
    } while (cVar2 != '\x06');
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x15');
  return;
}



===== FUN_CODE_a5fe CODE:a5fe size=49 =====

void FUN_CODE_a5fe(char param_1,byte param_2)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  
  bVar2 = 1;
  cVar1 = BANK0_R7 + '\x01';
  while (cVar1 = cVar1 + -1, cVar1 != '\0') {
    bVar2 = bVar2 << 1;
  }
  if (param_1 != '\0') {
    pbVar3 = (byte *)CONCAT11('\f' - (((5 < param_2) << 7) >> 7),param_2 - 6);
    *pbVar3 = *pbVar3 | bVar2;
    return;
  }
  pbVar3 = (byte *)CONCAT11('\f' - (((5 < param_2) << 7) >> 7),param_2 - 6);
  *pbVar3 = *pbVar3 & ~bVar2;
  return;
}



===== FUN_CODE_a62f CODE:a62f size=47 =====

char FUN_CODE_a62f(byte param_1)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = param_1 + 0x9d;
  if (param_1 >= 99) {
    bVar1 = 0x76 - (((param_1 < 99) << 7) >> 7);
    if (bVar1 <= param_1) {
      return param_1 - bVar1;
    }
    cVar2 = DAT_EXTMEM_0302;
    if (DAT_EXTMEM_0302 == BANK0_R7) {
      EA = 0;
      DAT_EXTMEM_0137 = 9;
      DAT_EXTMEM_0138 = 6;
      IEN1 = 0;
      TXCNTH = param_1 * '\x02';
      cVar2 = FUN_CODE_8edf(param_1 * '\x02',0xe6);
    }
  }
  return cVar2;
}



===== FUN_CODE_a65e CODE:a65e size=43 =====

void FUN_CODE_a65e(void)

{
  byte bVar1;
  
  if (_c_7 != '\0') {
    _c_7 = '\0';
    bVar1 = SADDR;
    SADDR = bVar1 & 0xfe;
    if (DAT_EXTMEM_0e1f == ' ') {
      FUN_CODE_a252(0x65,0x65,0xca,0);
    }
    _4_5 = 0;
    DAT_EXTMEM_009d = DAT_EXTMEM_0e1f;
    bVar1 = SADDR;
    SADDR = bVar1 | 1;
  }
  return;
}



===== FUN_CODE_a6dd CODE:a6dd size=41 =====

void FUN_CODE_a6dd(void)

{
  DAT_EXTMEM_ff80 = 1;
  DAT_EXTMEM_ff81 = 1;
  DAT_EXTMEM_ff82 = 1;
  DAT_EXTMEM_ff83 = 1;
  DAT_EXTMEM_ff84 = 1;
  DAT_EXTMEM_ff85 = 1;
  DAT_EXTMEM_ff86 = 1;
  DAT_EXTMEM_ff87 = 1;
  DAT_EXTMEM_ff88 = 1;
  DAT_EXTMEM_ff89 = 1;
  DAT_EXTMEM_ff8a = 1;
  DAT_EXTMEM_ff8b = 1;
  DAT_EXTMEM_ff8c = 1;
  DAT_EXTMEM_ff8d = 1;
  DAT_EXTMEM_ff8e = 1;
  DAT_EXTMEM_ff8f = 1;
  DAT_EXTMEM_ff90 = 1;
  DAT_EXTMEM_ff91 = 1;
  return;
}



===== FUN_CODE_a72f CODE:a72f size=41 =====

void FUN_CODE_a72f(undefined1 param_1)

{
  char cVar1;
  
  DAT_EXTMEM_0ecc = param_1;
  if ((_c_1 != '\x01') && (cVar1 = T0, cVar1 != '\0')) {
    FUN_CODE_43ca(0x33,0,0,0,0,0x20);
    DAT_INTMEM_33 = 1;
    DAT_INTMEM_34 = 4;
    FUN_CODE_a29a(DAT_EXTMEM_0ecc);
  }
  return;
}



===== FUN_CODE_a758 CODE:a758 size=41 =====

void FUN_CODE_a758(void)

{
  char cVar1;
  
  if ((_c_1 != '\x01') && (cVar1 = T0, cVar1 != '\0')) {
    DAT_INTMEM_33 = 1;
    DAT_INTMEM_34 = 8;
    DAT_INTMEM_48 = '\0';
    cVar1 = '\x02';
    do {
      DAT_INTMEM_48 = *(char *)(cVar1 + '3') + DAT_INTMEM_48;
      cVar1 = cVar1 + '\x01';
    } while (cVar1 != '\x15');
    FUN_CODE_a2a0(0x17,6);
  }
  return;
}



===== FUN_CODE_a841 CODE:a841 size=35 =====

char FUN_CODE_a841(void)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  
  CCAPM0 = 3;
  cVar2 = BANK0_R7;
  uVar3 = BANK0_R2;
  FUN_CODE_4244(BANK0_R6,BANK0_R7,0xb,0xb8,BANK0_R2,BANK0_R3);
  CCAPM4 = uVar3;
  CCAPM3 = cVar2 * -0x48;
  CCAPM0 = 0xc3;
  bVar1 = SADDR;
  SADDR = bVar1 | 0x20;
  return cVar2 * -0x48;
}



===== FUN_CODE_a887 CODE:a887 size=34 =====

void FUN_CODE_a887(void)

{
  if (DAT_EXTMEM_0317 == '\0') {
    DAT_SFR_96 = 0;
    DAT_SFR_94 = 0x5f;
    DAT_SFR_95 = 0x77;
    DAT_SFR_91 = 0xc4;
    DAT_EXTMEM_0f27 = 1;
    DAT_EXTMEM_0f29 = 1;
    DAT_EXTMEM_0f25 = 0;
    DAT_EXTMEM_0f26 = 0;
  }
  return;
}



===== FUN_CODE_a8cb CODE:a8cb size=33 =====

byte FUN_CODE_a8cb(void)

{
  byte bVar1;
  
  bVar1 = 3 - (((DAT_EXTMEM_0f26 < 0xe9) << 7) >> 7);
  if (bVar1 <= DAT_EXTMEM_0f25) {
    _f_1 = 1;
    return DAT_EXTMEM_0f25 - bVar1;
  }
  bVar1 = DAT_EXTMEM_0f26 + 1;
  DAT_EXTMEM_0f26 = bVar1;
  if (bVar1 == 0) {
    bVar1 = DAT_EXTMEM_0f25 + 1;
    DAT_EXTMEM_0f25 = bVar1;
  }
  return bVar1;
}



===== FUN_CODE_a92c CODE:a92c size=32 =====

void FUN_CODE_a92c(void)

{
  char cVar1;
  char cVar2;
  
  cVar1 = '\0';
  do {
    cVar2 = '\0';
    do {
      IEN1 = 0;
      DAT_EXTMEM_0eef = 0;
      DAT_EXTMEM_0ef0 = 0;
      FUN_CODE_6e7f(0,BANK0_R2,BANK0_R1);
      cVar2 = cVar2 + '\x01';
    } while (cVar2 != '\x06');
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x15');
  return;
}



===== FUN_CODE_a94c CODE:a94c size=31 =====

void FUN_CODE_a94c(void)

{
  FUN_CODE_aa18();
  FUN_CODE_0006();
  FUN_CODE_a33b(1,0xf4);
  FUN_CODE_9f89();
  FUN_CODE_ab8b();
  FUN_CODE_5e51();
  FUN_CODE_ac9b();
  FUN_CODE_aca1();
  FUN_CODE_aaad();
  return;
}



===== FUN_CODE_a96b CODE:a96b size=31 =====

void FUN_CODE_a96b(void)

{
  if (_8_2 != '\x01') {
    _9_1 = 0;
    DAT_EXTMEM_09a8 = 0;
    DAT_EXTMEM_09a9 = 0;
    DAT_EXTMEM_0f43 = 0;
    DAT_EXTMEM_0f44 = 0;
    DAT_EXTMEM_0f25 = 0;
    DAT_EXTMEM_0f26 = 0;
    DAT_EXTMEM_02e3 = 0;
    DAT_EXTMEM_02e4 = 0;
  }
  return;
}



===== FUN_CODE_a9a8 CODE:a9a8 size=28 =====

void FUN_CODE_a9a8(void)

{
  char cVar1;
  byte bVar2;
  
  while (BANK0_R7 != '\0') {
    for (bVar2 = 0; bVar2 < 5; bVar2 = bVar2 + 1) {
      cVar1 = '\0';
      do {
        IEN1 = 0;
        cVar1 = cVar1 + '\x01';
      } while (cVar1 != -1);
    }
  }
  return;
}



===== FUN_CODE_aa18 CODE:aa18 size=27 =====

void FUN_CODE_aa18(void)

{
  IPL1 = 8;
  FUN_CODE_a33b(0,5);
  DAT_SFR_bc = 2;
  FUN_CODE_a33b(0,200);
  DAT_SFR_bc = 3;
  IPL1 = 0xc;
  return;
}



===== FUN_CODE_aa33 CODE:aa33 size=25 =====

void FUN_CODE_aa33(void)

{
  byte bVar1;
  
  DAT_EXTMEM_ff80 = DAT_EXTMEM_ff80 | 0xc0;
  DAT_EXTMEM_ff86 = DAT_EXTMEM_ff86 | 0x80;
  DAT_EXTMEM_ff8c = DAT_EXTMEM_ff8c | 0x80;
  bVar1 = SADDR;
  SADDR = bVar1 | 2;
  return;
}



===== FUN_CODE_aa4c CODE:aa4c size=25 =====

byte FUN_CODE_aa4c(void)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_0302 ^ BANK0_R7;
  if (((bVar1 == 0) && (bVar1 = BANK0_R7 + 0x9d, 0x62 < BANK0_R7)) &&
     (bVar1 = BANK0_R7 + 0x8a, BANK0_R7 < 0x76)) {
    bVar1 = FUN_CODE_8eb6(bVar1);
  }
  return bVar1;
}



===== FUN_CODE_aa65 CODE:aa65 size=25 =====

void FUN_CODE_aa65(void)

{
  char cVar1;
  
  if ((_c_1 != '\x01') && (cVar1 = T0, cVar1 != '\0')) {
    DAT_INTMEM_33 = 1;
    DAT_INTMEM_34 = 1;
    DAT_INTMEM_35 = BANK0_R7;
    DAT_INTMEM_36 = BANK0_R7;
    FUN_CODE_a299(BANK0_R5);
  }
  return;
}



===== FUN_CODE_aa97 CODE:aa97 size=22 =====

void FUN_CODE_aa97(void)

{
  DAT_EXTMEM_ff86 = 0x89;
  DAT_EXTMEM_ff8c = 0x89;
  DAT_EXTMEM_ff80 = 0xc9;
  return;
}



===== FUN_CODE_aaad CODE:aaad size=22 =====

undefined1 FUN_CODE_aaad(void)

{
  byte bVar1;
  
  bVar1 = IE;
  IE = bVar1 | 1;
  SADDR = 0x21;
  DAT_SFR_ba = 0;
  DAT_SFR_b6 = 0;
  DAT_SFR_b4 = 0;
  IP = 0;
  DAT_SFR_b5 = 0x42;
  SADEN = 0x41;
  return 0;
}



===== FUN_CODE_aac3 CODE:aac3 size=22 =====

void FUN_CODE_aac3(undefined1 param_1)

{
  byte bVar1;
  
  IEN1 = 0;
  bVar1 = 0;
  do {
    *(undefined1 *)CONCAT11('\f' - (((5 < bVar1) << 7) >> 7),bVar1 - 6) = param_1;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 0x15);
  return;
}



===== FUN_CODE_aad9 CODE:aad9 size=21 =====

void FUN_CODE_aad9(void)

{
  byte bVar1;
  
  bVar1 = DAT_SFR_9e;
  DAT_SFR_9e = bVar1 & 0xf0;
  bVar1 = HADDR;
  HADDR = bVar1 | 4;
  bVar1 = DAT_SFR_92;
  DAT_SFR_92 = bVar1 & 0xbf;
  bVar1 = HADDR;
  HADDR = bVar1 | 1;
  do {
    bVar1 = DPX;
  } while ((bVar1 >> 4 & 1) == 0);
  bVar1 = DPX;
  DPX = bVar1 & 0xef;
  return;
}



===== FUN_CODE_aaee CODE:aaee size=20 =====

void FUN_CODE_aaee(void)

{
  byte bVar1;
  
  DAT_EXTMEM_ff80 = DAT_EXTMEM_ff80 & 0xbf;
  FIFLG = 0xff;
  bVar1 = TCON;
  TCON = bVar1 | 0x87;
  bVar1 = P3;
  P3 = bVar1 | 0x6d;
  bVar1 = DAT_SFR_f8;
  DAT_SFR_f8 = bVar1 | 0x10;
  return;
}



===== FUN_CODE_ab5a CODE:ab5a size=12 =====

void FUN_CODE_ab5a(void)

{
  FUN_CODE_a4b6(0,0,0);
  FUN_CODE_9a30(0);
  return;
}



===== FUN_CODE_ab8b CODE:ab8b size=18 =====

undefined1 FUN_CODE_ab8b(void)

{
  TH2 = 0xff;
  TL2 = 0xeb;
  RCAP2H = 0xff;
  RCAP2L = 0xeb;
  T2MOD = 0;
  T2CON = 0;
  return 0;
}



===== FUN_CODE_ac2d CODE:ac2d size=13 =====

byte FUN_CODE_ac2d(byte param_1,undefined1 param_2,byte param_3)

{
  byte bVar1;
  undefined1 uVar2;
  
  bVar1 = DAT_SFR_86;
  DAT_SFR_86 = bVar1 | 8;
  EPINDEX = param_2;
  if (param_1 != 0) {
    param_3 = param_3 / param_1;
  }
  uVar2 = EPINDEX;
  return param_3;
}



===== FUN_CODE_ac47 CODE:ac47 size=12 =====

void FUN_CODE_ac47(void)

{
  FUN_CODE_aa65();
  _d_1 = 0;
  BANK3_R3 = 6;
  BANK3_R2 = 0xff;
  return;
}



===== FUN_CODE_ac53 CODE:ac53 size=10 =====

/* WARNING: Control flow encountered bad instruction data */

void FUN_CODE_ac53(void)

{
  EA = 0;
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



===== FUN_CODE_ac5e CODE:ac5e size=11 =====

char FUN_CODE_ac5e(char param_1,char param_2)

{
  byte bVar1;
  
  bVar1 = DAT_SFR_86;
  DAT_SFR_86 = bVar1 & 0xf3;
  return param_2 * param_1;
}



===== FUN_CODE_ac69 CODE:ac69 size=10 =====

void FUN_CODE_ac69(void)

{
  if (_d_4 != '\x01') {
    FUN_CODE_a20a();
    FUN_CODE_63f8();
  }
  return;
}



===== FUN_CODE_ac7b CODE:ac7b size=7 =====

void FUN_CODE_ac7b(void)

{
  _7_7 = 1;
  FUN_CODE_a9a8(0x14);
  return;
}



===== FUN_CODE_ac82 CODE:ac82 size=7 =====

void FUN_CODE_ac82(void)

{
  _7_7 = 1;
  FUN_CODE_a9a8(10);
  return;
}



===== vector_target_000B CODE:ac89 size=6 =====

void vector_target_000B(void)

{
  HIFLG = 0;
  _f_5 = 1;
  return;
}



===== vector_target_0013 CODE:ac8f size=6 =====

void vector_target_0013(void)

{
  byte bVar1;
  
  bVar1 = DAT_SFR_b6;
  DAT_SFR_b6 = bVar1 & 0xfd;
  _f_5 = 1;
  return;
}



===== vector_target_001B CODE:ac95 size=6 =====

void vector_target_001B(void)

{
  byte bVar1;
  
  bVar1 = DAT_SFR_b6;
  DAT_SFR_b6 = bVar1 & 0xfe;
  _f_5 = 1;
  return;
}



===== FUN_CODE_ac9b CODE:ac9b size=6 =====

undefined1 FUN_CODE_ac9b(void)

{
  FIE = 0;
  HIE = 0;
  return 0;
}



===== FUN_CODE_aca1 CODE:aca1 size=6 =====

undefined1 FUN_CODE_aca1(void)

{
  IPH1 = 0;
  TMOD = 0;
  return 0;
}



===== FUN_CODE_acad CODE:acad size=6 =====

void FUN_CODE_acad(void)

{
  DAT_EXTMEM_08bf = 0;
  return;
}


