#include "stdafx.h"
#include "app.h"

WORD word_code_13DF = 0;
WORD word_code_13E1 = 0;
WORD word_code_13E3 = 0;
WORD word_code_13E5 = 0;
BYTE byte_code_13E7 = 0;

void start()
{
  _push(_ds);
  _ax = 0x0000;
  _push(_ax);
  sub_5C60();
  _ax = SEG_DATA;
  _ds = _ax;
  sub_13AA();
  memory[adr(_ds, 0x690)] = 4;
  *(WORD*)&memory[adr(_ds, 0x6DF8)] = 0;
  memory[adr(_ds, 0x69B)] = 0;
  sub_1419();
  sub_13E8();
  _ax = (*(WORD*)&memory[adr(_ds, 0x693)]) + 0x0240;
  *(WORD*)&memory[adr(_ds, 0x6E00)] = _ax;
  _ax = 0x0004;
  _interrupt(0x10);
  _al = 0x04;
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_3F;
  _al = 0x06;
loc_3F:
  memory[adr(_ds, 0x690)] = _al;
  _ah = 0x0b;
  _bx = 0x0101;
  _interrupt(0x10);
  *(WORD*)&memory[adr(_ds, 0x416)] = 0;
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  sub_1D31();
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_65;
  _dx = 0x03d9;
  _al = 0x20;
  _out(_dx, _al);
loc_65:
  sub_2E10();
  sub_26E1();
  sub_26DA();
  memory[adr(_ds, 0x41A)] = 0;
  _ax = 0xffff;
  *(WORD*)&memory[adr(_ds, 0x41D)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x41F)] = _ax;
  memory[adr(_ds, 0x0)] = 0xff;
loc_81:
  sub_2690();
  *(WORD*)&memory[adr(_ds, 0x8)] = 0;
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  sub_1D31();
  sub_5B21();
  sub_5CB0();
  sub_5B21();
  if (memory[adr(_ds, 0x41A)] != 0)
    goto loc_AE;
loc_A3:
  sub_5B21();
  sub_5EE5();
  memory[adr(_ds, 0x41A)] = 1;
loc_AE:
  _ax = *(WORD*)&memory[adr(_ds, 0x6DF8)];
  *(WORD*)&memory[adr(_ds, 0x8)] = _ax;
  memory[adr(_ds, 0x1F80)] = 3;
  sub_26DA();
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  sub_1D31();
  sub_5B21();
  *(WORD*)&memory[adr(_ds, 0x1C30)] = 0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x412)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x414)] = 0;
  memory[adr(_ds, 0x418)] = 0;
  memory[adr(_ds, 0x419)] = 0;
  memory[adr(_ds, 0x41C)] = 0;
  memory[adr(_ds, 0x41B)] = 0;
  sub_5B21();
loc_F3:
  if (memory[adr(_ds, 0x1F80)] == 0)
    goto loc_81;
  if (memory[adr(_ds, 0x41B)] != 0)
    goto loc_AE;
  if (memory[adr(_ds, 0x41C)] != 0)
    goto loc_A3;
  sub_2A00();
  sub_5400();
  memory[adr(_ds, 0x1F81)] = 0xff;
  sub_5B21();
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  if (memory[adr(_ds, 0x419)] == 0)
    goto loc_137;
  sub_7A1();
  memory[adr(_ds, 0x550)] = 2;
  memory[adr(_ds, 0x576)] = 1;
  memory[adr(_ds, 0x578)] = 0x20;
  goto loc_140;
loc_137:
  *(WORD*)&memory[adr(_ds, 0x579)] = 0;
  sub_70D();
loc_140:
  sub_1E40();
  sub_1830();
  sub_2210();
  sub_2330();
  sub_26F2();
  sub_26FC();
  sub_58BD();
loc_155:
  if (memory[adr(_ds, 0x1F80)] != 0)
    goto loc_15F;
  goto loc_81;
loc_15F:
  sub_1338();
  if (memory[adr(_ds, 0x41C)] == 0)
    goto loc_16C;
  goto loc_A3;
loc_16C:
  if (memory[adr(_ds, 0x41B)] == 0)
    goto loc_176;
  goto loc_AE;
loc_176:
  sub_1200();
  sub_8E5();
  sub_1E63();
  if (memory[adr(_ds, 0x1CB8)] != 0)
    goto loc_191;
  memory[adr(_ds, 0x40F)] += 1;
  if (memory[adr(_ds, 0x40F)] & 3)
    goto loc_155;
loc_191:
  sub_546D();
  sub_4A0();
  sub_1936();
  sub_184B();
  sub_2216();
  sub_237B();
  sub_26B3();
  if (memory[adr(_ds, 0x551)] == 0)
    goto loc_155;
  if (memory[adr(_ds, 0x1F80)] != 0)
    goto loc_1B7;
  goto loc_81;
loc_1B7:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x410)] = _dx;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  *(WORD*)&memory[adr(_ds, 0x1)] = _ax;
  _al = memory[adr(_ds, 0x57B)];
  memory[adr(_ds, 0x3)] = _al;
  memory[adr(_ds, 0x419)] = 1;
  if (memory[adr(_ds, 0x418)] == 0)
    goto loc_1E5;
  memory[adr(_ds, 0x418)] = 0;
  *(WORD*)&memory[adr(_ds, 0x4)] = 7;
  goto loc_238;
loc_1E5:
  sub_2DFD();
  if (!(_dl & 0xa0))
    goto loc_20A;
  _bx = (*(WORD*)&memory[adr(_ds, 0x8)]) & 0x0003;
  if (_bx == 0x0003)
    goto loc_20A;
  _cl = 0x02;
  _bx <<= _cl;
  _dx &= 0x0003;
  _bx += _dx;
  _al = memory[adr(_ds, _bx + 1057)];
  goto loc_21C;
loc_20A:
  sub_2DFD();
  _dx &= 0x0007;
  if (_dx >= 0x0005)
    goto loc_20A;
  _bx = _dx;
  _al = memory[adr(_ds, _bx + 1069)];
loc_21C:
  _ah = 0;
  if (_ax != *(WORD*)&memory[adr(_ds, 0x41D)])
    goto loc_22A;
  if (_ax == *(WORD*)&memory[adr(_ds, 0x41F)])
    goto loc_1E5;
loc_22A:
  *(WORD*)&memory[adr(_ds, 0x4)] = _ax;
  _cx = *(WORD*)&memory[adr(_ds, 0x41D)];
  *(WORD*)&memory[adr(_ds, 0x41F)] = _cx;
  *(WORD*)&memory[adr(_ds, 0x41D)] = _ax;
loc_238:
  *(WORD*)&memory[adr(_ds, 0x6)] = 0;
  _bx = *(WORD*)&memory[adr(_ds, 0x4)];
  if (_bx <= 0x0007)
    goto loc_249;
  _bx = 0;
loc_249:
  _bx <<= 1;
  switch (_bx)
  {
    case 0: goto loc_3E2;
    case 2: goto loc_3E2;
    case 4: goto loc_459;
    case 6: goto loc_394;
    case 8: goto loc_349;
    case 10: goto loc_2FE;
    case 12: goto loc_2AA;
    case 14: goto loc_260;
    default:
      _ASSERT(0);
  }
loc_260:
  *(WORD*)&memory[adr(_ds, 0x4)] = 7;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_1E40();
  sub_3405();
  sub_6100();
  sub_4F59();
  sub_58BD();
loc_27E:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_6106();
  sub_2F66();
  sub_2E60();
  sub_4C10();
  _al = (((memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
  if (_al == 0)
    goto loc_27E;
  goto loc_427;
loc_2AA:
  *(WORD*)&memory[adr(_ds, 0x4)] = 6;
  sub_1BF0();
  sub_2790();
  nullsub_1();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_2C5:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_4943();
  sub_47D6();
  sub_8E5();
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_2E3;
  sub_1E63();
  goto loc_2E6;
loc_2E3:
  sub_3150();
loc_2E6:
  _al = ((((memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41B)]) | memory[adr(_ds, 0x41C)];
  if (_al == 0)
    goto loc_2C5;
  goto loc_427;
loc_2FE:
  *(WORD*)&memory[adr(_ds, 0x4)] = 5;
  sub_1BF0();
  sub_2790();
  sub_457A();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_319:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_45AB();
  sub_4340();
  sub_8E5();
  sub_3150();
  sub_1E63();
  _al = ((((memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
  if (_al == 0)
    goto loc_319;
  goto loc_427;
loc_349:
  *(WORD*)&memory[adr(_ds, 0x4)] = 4;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_4090();
  sub_58BD();
loc_364:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3E90();
  sub_40C2();
  sub_3150();
  sub_1E63();
  _al = ((((memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
  if (_al == 0)
    goto loc_364;
  goto loc_427;
loc_394:
  *(WORD*)&memory[adr(_ds, 0x4)] = 3;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_3B30();
  sub_3C90();
  sub_58BD();
loc_3B2:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3CB1();
  sub_3B42();
  sub_3150();
  sub_1E63();
  _al = ((((memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
  if (_al == 0)
    goto loc_3B2;
  goto loc_427;
loc_3E2:
  *(WORD*)&memory[adr(_ds, 0x4)] = 1;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_3FA:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3150();
  sub_1E63();
  sub_3850();
  if (memory[adr(_ds, 0x554)] != 0)
    goto loc_459;
  _al = (((memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x551)]) | memory[adr(_ds, 0x41B)]) | memory[adr(_ds, 0x41C)];
  if (_al == 0)
    goto loc_3FA;
loc_427:
  if (memory[adr(_ds, 0x41B)] == 0)
    goto loc_431;
  goto loc_AE;
loc_431:
  if (memory[adr(_ds, 0x41C)] == 0)
    goto loc_43B;
  goto loc_A3;
loc_43B:
  if (memory[adr(_ds, 0x552)] == 0)
    goto loc_447;
  memory[adr(_ds, 0x419)] = 0;
loc_447:
  _ax = *(WORD*)&memory[adr(_ds, 0x4)];
  *(WORD*)&memory[adr(_ds, 0x6)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  sub_1BF0();
  goto loc_F3;
loc_459:
  *(WORD*)&memory[adr(_ds, 0x4)] = 2;
  sub_1BF0();
  sub_2790();
  sub_35C9();
  sub_7A1();
  memory[adr(_ds, 0x1CBF)] = 0;
  memory[adr(_ds, 0x1CB8)] = 0;
  sub_58BD();
loc_478:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3675();
  sub_37E5();
  _al = (((memory[adr(_ds, 0x552)]) | memory[adr(_ds, 0x553)]) | memory[adr(_ds, 0x41C)]) | memory[adr(_ds, 0x41B)];
  if (_al == 0)
    goto loc_478;
  goto loc_427;
}

void sub_4A0()
{
  memory[adr(_ds, 0x531)] -= 1;
  if (memory[adr(_ds, 0x531)] == 0)
    goto loc_4A7;
  return;
loc_4A7:
  memory[adr(_ds, 0x531)] += 1;
  sub_13D8();
  if (_al != 0)
    return;
  if (memory[adr(_ds, 0x55A)] != 0)
    return;
  if (memory[adr(_ds, 0x1673)] != 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x544)])
    return;
  *(WORD*)&memory[adr(_ds, 0x544)] = _dx;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _al = memory[adr(_ds, _bx + 1330)];
  if (memory[adr(_ds, 0x57B)] > 0x60)
    goto loc_4DF;
  _al >>= 2;
loc_4DF:
  memory[adr(_ds, 0x531)] = _al;
  _bx = *(WORD*)&memory[adr(_ds, 0x52F)];
  sub_658();
  if (flags.zero)
    goto loc_50C;
  _al = (memory[adr(_ds, 0x525)]) + memory[adr(_ds, _bx + 1321)];
  if (_al < 0x04)
    return;
loc_4F6:
  sub_2DFD();
  _dl &= 0x03;
  if (_dl == memory[adr(_ds, 0x52F)])
    goto loc_4F6;
  if (_dl == 0x03)
    goto loc_4F6;
  _bl = _dl;
  goto loc_535;
loc_50C:
  _al = memory[adr(_ds, _bx + 1321)];
  memory[adr(_ds, 0x525)] += _al;
  if (memory[adr(_ds, 0x525)] < 4)
    goto loc_583;
  sub_2DFD();
  if (_dl > 0x40)
    goto loc_539;
loc_523:
  sub_2DFD();
  _dl &= 0x03;
  if (_dl == 0x03)
    goto loc_523;
  _bl = _dl;
  sub_658();
  if (!flags.zero)
    goto loc_523;
loc_535:
  *(WORD*)&memory[adr(_ds, 0x52F)] = _bx;
loc_539:
  _al = memory[adr(_ds, _bx + 1318)];
  memory[adr(_ds, 0x525)] = _al;
  _ax = SEG_DATA;
  _es = _ax;
  _di = 0x04d7;
  _ah = memory[adr(_ds, _bx + 1324)];
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl = memory[adr(_ds, _bx + 10938)];
  _bh = _ah;
  sub_67D();
  if (*(WORD*)&memory[adr(_ds, 0x52F)] == 1)
    goto loc_56E;
  memory[adr(_ds, 0x540)] >>= 1;
  sub_633();
  memory[adr(_ds, 0x540)] >>= 1;
  goto loc_57C;
loc_56E:
  _al = (memory[adr(_ds, 0x540)]) >> 2;
  sub_633();
  memory[adr(_ds, 0x540)] >>= 1;
loc_57C:
  sub_633();
  _bx = *(WORD*)&memory[adr(_ds, 0x52F)];
loc_583:
  if (memory[adr(_ds, 0x4D6)] == 0)
    goto loc_5D0;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  if (_bl == 0x01)
    goto loc_5BF;
  *(WORD*)&memory[adr(_ds, 0x55F)] += 1;
  _ax += 0x0004;
  if (_ax < 0x0123)
    goto loc_5CD;
loc_59E:
  memory[adr(_ds, 0x55B)] = 0x11;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x576)] = 1;
  memory[adr(_ds, 0x578)] = 0x18;
  memory[adr(_ds, 0x572)] = 1;
  memory[adr(_ds, 0x55C)] = 0;
  goto loc_5D0;
loc_5BF:
  *(WORD*)&memory[adr(_ds, 0x55F)] -= 1;
  flags.carry = _ax < 0x0004;
  _ax -= 0x0004;
  if (flags.carry)
    goto loc_59E;
  if (_ax < 0x0008)
    goto loc_59E;
loc_5CD:
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
loc_5D0:
  _push(_ds);
  _bx <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 1309)];
  *(WORD*)&memory[adr(_ds, 0x523)] = _ax;
  _si = *(WORD*)&memory[adr(_ds, _bx + 1303)];
  _ax = 0xb800;
  _ds = _ax;
  _es = _ax;
  _di = _si;
  if (_bx != 0x0002)
    goto loc_5F1;
  flags.direction = false;
  _di -= 1;
  goto loc_5F3;
loc_5F1:
  flags.direction = true;
  _di += 1;
loc_5F3:
  _cx = 0x027f;
  _push(_di);
  _push(_si);
  _rep_movsb<MemB800, MemB800, DirBackward>();
  _si = _pop();
  _di = _pop();
  _si += 0x2000;
  _di += 0x2000;
  _cx = 0x0280;
  _rep_movsb<MemB800, MemB800, DirBackward>();
  _ds = _pop();
  _di = *(WORD*)&memory[adr(_ds, 0x523)];
  _bl = memory[adr(_ds, 0x525)];
  _bh = 0;
  _bx += 0x04d7;
  _cx = 0x10;
loc_61B:
  _al = memory[adr(_ds, _bx)];
  _videoWrite8(_esAssume(0xb800), _di, _al);
  _bx += 0x0004;
  _di = _di ^ 0x2000;
  if (_di & 0x2000)
    goto loc_630;
  _di += 0x50;
loc_630:
  if (--_cx)
    goto loc_61B;
}

void sub_633()
{
  _ah = flags.toByte();
  _bx = *(WORD*)&memory[adr(_ds, 0x52F)];
  _bl = memory[adr(_ds, _bx + 1345)];
  _cx = 0x0005;
  if (_bl == 0x09)
    goto loc_64E;
loc_644:
  flags.fromByte(_ah);
  _ASSERT(0 /* check carry */); _rcr(memory[adr(_ds, _bx + 4118)], 1);
  _ah = flags.toByte();
  _bx += 1;
  if (--_cx)
    goto loc_644;
  return;
loc_64E:
  flags.fromByte(_ah);
  _ASSERT(0 /* check carry */); _rcl(memory[adr(_ds, _bx + 4118)], 1);
  _ah = flags.toByte();
  _bx -= 1;
  if (--_cx)
    goto loc_64E;
}

void sub_658()
{
  memory[adr(_ds, 0x4D6)] = 0;
  _al = memory[adr(_ds, 0x57C)];
  flags.zero = _al == memory[adr(_ds, _bx + 1341)];
  if (_al < memory[adr(_ds, _bx + 1341)])
    goto loc_679;
  flags.zero = _al == memory[adr(_ds, _bx + 1338)];
  if (_al >= memory[adr(_ds, _bx + 1338)])
    goto loc_679;
  flags.zero = memory[adr(_ds, 0x55C)] == 1;
  if (memory[adr(_ds, 0x55C)] >= 1)
    goto loc_674;
  return;
loc_674:
  memory[adr(_ds, 0x4D6)] = 1;
loc_679:
  flags.zero = true;
}

// class CIReturn
void sub_67D()
{
  memory[adr(_ds, 0x540)] = 0;
  flags.direction = false;
  _cx = 0x20;
  _ax = 0xaaaa;
  _rep_stosw<MemData, DirForward>();
  _di -= 0x40;
  _ax = 0x4444;
  *(WORD*)&memory[adr(_es, _di + 4)] = _ax;
  *(WORD*)&memory[adr(_es, _di + 6)] = _ax;
  sub_2DFD();
  if (_dl < _bl)
    return;
  if (_dh > _bh)
    goto loc_6A5;
  return;
loc_6A5:
  sub_2DFD();
  if (_dl < 0x18)
    goto loc_6C7;
  if (_dl < 0x60)
    goto loc_6D0;
  _push(_di);
  sub_6DE();
  _al <<= 1;
  memory[adr(_ds, 0x540)] = _al;
  _di = _pop();
  _di += 0x0002;
  sub_6DE();
  memory[adr(_ds, 0x540)] |= _al;
  return;
loc_6C7:
  _cx = 0x20;
  _si = 0x0490;
  goto loc_6D6;
loc_6D0:
  _cx = 0x10;
  _si = 0x0460;
loc_6D6:
  _rep_movsw<MemData, MemData, DirForward>();
  memory[adr(_ds, 0x540)] = 3;
}

void sub_6DE()
{
  sub_2DFD();
  _dx &= 0x0006;
  if (_dl != 0x06)
    goto loc_6ED;
  _al = 0;
  return;
loc_6ED:
  _bx = _dx;
  _si = *(WORD*)&memory[adr(_ds, _bx + 1232)];
  _cx = 0x0008;
loc_6F6:
  _lodsw<MemData, DirForward>();
  _stosw<MemData, DirForward>();
  _di += 0x0002;
  if (--_cx)
    goto loc_6F6;
  _al = 0x01;
}

void sub_700()
{
  *(WORD*)&memory[adr(_ds, 0x57D)] = 0;
  *(WORD*)&memory[adr(_ds, 0x684)] = 0;
}

void sub_70D()
{
  _cx = 0x0000;
  _ah = 0x01;
  if (*(WORD*)&memory[adr(_ds, 0x579)] < 0xa0)
    goto loc_71F;
  _cx = 0x0128;
  _ah = 0xff;
loc_71F:
  memory[adr(_ds, 0x56E)] = _ah;
  memory[adr(_ds, 0x558)] = 3;
  memory[adr(_ds, 0x559)] = 0x0c;
  _dl = 0xb4;
  *(WORD*)&memory[adr(_ds, 0x579)] = _cx;
  memory[adr(_ds, 0x57B)] = _dl;
  memory[adr(_ds, 0x57C)] = 0xe6;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x561)] = 2819;
  sub_1124();
  memory[adr(_ds, 0x571)] = 0;
  *(WORD*)&memory[adr(_ds, 0x572)] = 2;
  memory[adr(_ds, 0x576)] = 1;
  memory[adr(_ds, 0x55B)] = 0;
  memory[adr(_ds, 0x550)] = 0;
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x55A)] = 0;
  memory[adr(_ds, 0x583)] = 0;
  memory[adr(_ds, 0x698)] = 0;
  memory[adr(_ds, 0x699)] = 0;
  memory[adr(_ds, 0x551)] = 0;
  memory[adr(_ds, 0x584)] = 0;
  memory[adr(_ds, 0x552)] = 0;
  *(WORD*)&memory[adr(_ds, 0x554)] = 0;
  memory[adr(_ds, 0x553)] = 0;
  memory[adr(_ds, 0x127C)] = 0;
  sub_700();
}

void sub_7A1()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x4)];
  if (_bx != 0x0000)
    goto loc_7B5;
  _cx = *(WORD*)&memory[adr(_ds, 0x1)];
  _dl = memory[adr(_ds, 0x3)];
  goto loc_7BF;
loc_7B5:
  _dl = memory[adr(_ds, _bx + 1513)];
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 1497)];
loc_7BF:
  *(WORD*)&memory[adr(_ds, 0x579)] = _cx;
  memory[adr(_ds, 0x57B)] = _dl;
  _al = _dl + 0x32;
  memory[adr(_ds, 0x57C)] = _al;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0xFB2)];
  *(WORD*)&memory[adr(_ds, 0x569)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0xFBE)];
  *(WORD*)&memory[adr(_ds, 0x567)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x561)] = _ax;
  sub_1124();
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x56E)] = 0;
  memory[adr(_ds, 0x576)] = 1;
  memory[adr(_ds, 0x578)] = 0x40;
  _al = 0x0a;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_805;
  _al = 0;
loc_805:
  memory[adr(_ds, 0x55B)] = _al;
  memory[adr(_ds, 0x550)] = 0;
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x55A)] = 0;
  memory[adr(_ds, 0x583)] = 0;
  memory[adr(_ds, 0x698)] = 0;
  memory[adr(_ds, 0x699)] = 0;
  memory[adr(_ds, 0x551)] = 0;
  memory[adr(_ds, 0x584)] = 0;
  memory[adr(_ds, 0x552)] = 0;
  *(WORD*)&memory[adr(_ds, 0x554)] = 0;
  memory[adr(_ds, 0x553)] = 0;
  memory[adr(_ds, 0x127C)] = 0;
  sub_700();
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 2)
    return;
  memory[adr(_ds, 0x576)] = 0x10;
  *(WORD*)&memory[adr(_ds, 0x574)] = 0x10;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5F1)] = _dx;
  memory[adr(_ds, 0x5F3)] = 0;
  memory[adr(_ds, 0x5F4)] = 5;
  memory[adr(_ds, 0x5F5)] = 1;
}

void sub_872()
{
  *(WORD*)&memory[adr(_ds, 0x592A)] = 1024;
  if (memory[adr(_ds, 0x584)] == 0)
    goto loc_880;
  return;
loc_880:
  memory[adr(_ds, 0x576)] = 8;
  _dl = 0xff;
  _al = memory[adr(_ds, 0x57B)];
  if (_al >= memory[adr(_ds, 0x2652)])
    goto loc_892;
  _dl = 0x01;
loc_892:
  memory[adr(_ds, 0x571)] = _dl;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x2650)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x2650)];
  _dl = 0xff;
  if (!flags.carry && (_ax != 0))
    goto loc_8A5;
  _dl = 0x01;
  _ax = (~_ax);
loc_8A5:
  memory[adr(_ds, 0x56E)] = _dl;
  if (_ah == 0x00)
    goto loc_8B1;
  _ax = 0xff;
loc_8B1:
  _al = (~_al);
  if (_al >= 0x30)
    goto loc_8B9;
  _al = 0x30;
loc_8B9:
  _bl = _al >> 2;
  _al -= _bl;
  memory[adr(_ds, 0x578)] = _al;
  _cl = 0x05;
  _al >>= _cl;
  *(WORD*)&memory[adr(_ds, 0x572)] = _ax;
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x39E0)] = 0;
  memory[adr(_ds, 0x577)] = 1;
  memory[adr(_ds, 0x55B)] = 0x10;
  memory[adr(_ds, 0x584)] = 1;
}

void sub_8E5()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x57D)])
    goto loc_8FD;
  if (*(WORD*)&memory[adr(_ds, 0x684)] == 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x684)] -= 1;
  if (*(WORD*)&memory[adr(_ds, 0x684)] == 0)
    goto loc_90C;
  return;
loc_8FD:
  _ax = 0x20;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_909;
  _ax >>= 1;
loc_909:
  *(WORD*)&memory[adr(_ds, 0x684)] = _ax;
loc_90C:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 2)
    goto loc_91D;
  _cl = (memory[adr(_ds, 0x571)]) | memory[adr(_ds, 0x56E)];
  if (_cl != 0)
    goto loc_926;
loc_91D:
  _push(_dx);
  _push(_ax);
  sub_13D8();
  _ax = _pop();
  _dx = _pop();
  if (_al == 0)
    return;
loc_926:
  *(WORD*)&memory[adr(_ds, 0x57D)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x57F)] = _ax;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 4)
    goto loc_93B;
  if (memory[adr(_ds, 0x39E1)] != 0)
    return;
loc_93B:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 6)
    goto loc_949;
  if (memory[adr(_ds, 0x44BD)] != 0)
    return;
loc_949:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 2)
    goto loc_953;
  goto loc_BAC;
loc_953:
  _si = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  _ax = (*(WORD*)&memory[adr(_ds, 0x57D)]) - *(WORD*)&memory[adr(_ds, 0x5F1)];
  if (_ax < *(WORD*)&memory[adr(_ds, _si + 1417)])
    goto loc_9D6;
  if (_ax < *(WORD*)&memory[adr(_ds, _si + 1433)])
    goto loc_971;
  memory[adr(_ds, 0x552)] = 1;
loc_971:
  memory[adr(_ds, 0x5F5)] -= 1;
  if (memory[adr(_ds, 0x5F5)] != 0)
    goto loc_9B9;
  sub_597F();
  memory[adr(_ds, 0x5F5)] = 6;
  _al = memory[adr(_ds, 0x5F4)];
  if (memory[adr(_ds, 0x57B)] < 0xb3)
    goto loc_992;
  if (_al >= 0xc8)
    goto loc_992;
  _al += 0x1e;
  memory[adr(_ds, 0x5F4)] = _al;
loc_992:
  _dl = memory[adr(_ds, 0x57B)];
  flags.carry = _dl < _al;
  _dl -= _al;
  if (!flags.carry)
    goto loc_99C;
  _dl = 0;
loc_99C:
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl &= 0xf8;
  sub_2CB0();
  _di = _ax;
  _si = 0x064e;
  _ax = 0xb800;
  _es = _ax;
  _bp = 0x0e;
  _cx = 0x0503;
  sub_2D35();
loc_9B9:
  memory[adr(_ds, 0x56E)] = 0;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x5F3)] = 1;
  memory[adr(_ds, 0x576)] = 0x20;
  _bx = 0;
  _ah = 0x0b;
  _interrupt(0x10);
  goto loc_A86;
loc_9D6:
  _si = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  _bx = 0;
  if (_ax < *(WORD*)&memory[adr(_ds, _si + 1449)])
    goto loc_9F6;
  _bl += 1;
  if (_ax < *(WORD*)&memory[adr(_ds, _si + 1465)])
    goto loc_9F6;
  _bl = 0x05;
  if (_ax < *(WORD*)&memory[adr(_ds, _si + 1481)])
    goto loc_9F6;
  _bl -= 1;
loc_9F6:
  _ah = 0x0b;
  _interrupt(0x10);
  _al = memory[adr(_ds, 0x56E)];
  memory[adr(_ds, 0x56F)] = _al;
  _al = memory[adr(_ds, 0x571)];
  memory[adr(_ds, 0x570)] = _al;
  _al = memory[adr(_ds, 0x698)];
  if (_al != 0x00)
    goto loc_A1A;
  if (*(WORD*)&memory[adr(_ds, 0x574)] < 0x10)
    goto loc_A2E;
  *(WORD*)&memory[adr(_ds, 0x574)] -= 1;
  goto loc_A37;
loc_A1A:
  if (_al != memory[adr(_ds, 0x56E)])
    goto loc_A2E;
  if (*(WORD*)&memory[adr(_ds, 0x574)] >= 0x30)
    goto loc_A37;
  *(WORD*)&memory[adr(_ds, 0x574)] += 3;
  goto loc_A37;
loc_A2E:
  memory[adr(_ds, 0x56E)] = _al;
  *(WORD*)&memory[adr(_ds, 0x574)] = 0x20;
loc_A37:
  _ax = *(WORD*)&memory[adr(_ds, 0x574)];
  _cl = 0x03;
  _ax >>= _cl;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl <<= 1;
  if (_ax <= *(WORD*)&memory[adr(_ds, _bx + 1644)])
    goto loc_A4E;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 1644)];
loc_A4E:
  *(WORD*)&memory[adr(_ds, 0x572)] = _ax;
  sub_FC9();
  _al = memory[adr(_ds, 0x699)];
  if (_al != 0x00)
    goto loc_A6A;
  _al = (~_al);
  if (memory[adr(_ds, 0x576)] < 0x10)
    goto loc_A7E;
  memory[adr(_ds, 0x576)] -= 1;
  goto loc_A86;
loc_A6A:
  if (_al != memory[adr(_ds, 0x571)])
    goto loc_A7E;
  if (memory[adr(_ds, 0x576)] >= 0x40)
    goto loc_A86;
  memory[adr(_ds, 0x576)] += 4;
  goto loc_A86;
loc_A7E:
  memory[adr(_ds, 0x571)] = _al;
  memory[adr(_ds, 0x576)] = 0x20;
loc_A86:
  _si = *(WORD*)&memory[adr(_ds, 0x8)];
  _dl = memory[adr(_ds, 0x57B)];
  _cl = 0x04;
  _bl = (memory[adr(_ds, 0x576)]) >> _cl;
  if (_bl <= memory[adr(_ds, _si + 1660)])
    goto loc_AA0;
  _bl = memory[adr(_ds, _si + 1660)];
loc_AA0:
  _al = memory[adr(_ds, 0x571)];
  if (_al < 0x01)
    goto loc_ACE;
  if (_al != 0x01)
    goto loc_AB4;
  _dl += _bl;
  if (_dl < 0xb4)
    goto loc_ACE;
  _dl = 0xb3;
  goto loc_ACE;
loc_AB4:
  flags.carry = _dl < _bl;
  _dl -= _bl;
  if (flags.carry)
    goto loc_ABD;
  if (_dl > 0x03)
    goto loc_ACE;
loc_ABD:
  _ax = *(WORD*)&memory[adr(_ds, 0x9B8)];
  if (_ax != *(WORD*)&memory[adr(_ds, 0x55D)])
    goto loc_ACC;
  _ax = *(WORD*)&memory[adr(_ds, 0x57D)];
  *(WORD*)&memory[adr(_ds, 0x5F1)] = _ax;
loc_ACC:
  _dl = 0x02;
loc_ACE:
  memory[adr(_ds, 0x57B)] = _dl;
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x563)] = _ax;
  if (memory[adr(_ds, 0x5F3)] == 0)
    goto loc_AE9;
  _bx = 0x10;
  goto loc_B64;
loc_AE9:
  _al = memory[adr(_ds, 0x56E)];
  if (_al != memory[adr(_ds, 0x56F)])
    goto loc_AFB;
  _al = memory[adr(_ds, 0x571)];
  if (_al == memory[adr(_ds, 0x570)])
    goto loc_B00;
loc_AFB:
  _bx = 0x18;
  goto loc_B64;
loc_B00:
  *(WORD*)&memory[adr(_ds, 0x587)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x587)];
  _al = (memory[adr(_ds, 0x698)]) | memory[adr(_ds, 0x699)];
  if (_al != 0)
    goto loc_B13;
  _bl >>= 1;
loc_B13:
  if (memory[adr(_ds, 0x57B)] < 0xb3)
    goto loc_B21;
  if (memory[adr(_ds, 0x571)] == 1)
    goto loc_B3C;
loc_B21:
  if (memory[adr(_ds, 0x57B)] > 4)
    goto loc_B2F;
  if (memory[adr(_ds, 0x699)] != 0)
    goto loc_B53;
loc_B2F:
  _al = memory[adr(_ds, 0x576)];
  _ah = 0;
  _ax >>= 1;
  if (_ax >= *(WORD*)&memory[adr(_ds, 0x574)])
    goto loc_B53;
loc_B3C:
  if (memory[adr(_ds, 0x56E)] == 0)
    goto loc_B53;
  _bx &= 0x0006;
  if (memory[adr(_ds, 0x56E)] == 1)
    goto loc_B64;
  _bl |= 0x08;
  goto loc_B64;
loc_B53:
  _bx &= 0x0002;
  _bl |= 0x10;
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_B64;
  _bl += 0x04;
loc_B64:
  _ax = *(WORD*)&memory[adr(_ds, _bx + 2470)];
  *(WORD*)&memory[adr(_ds, 0x55D)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 2496)];
  *(WORD*)&memory[adr(_ds, 0x565)] = _ax;
  _al = 0x30;
  _cx = 0x02bc;
  if (memory[adr(_ds, 0x697)] < 0xfd)
    goto loc_B97;
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_B85;
  _al = 0x08;
  _cx = 0x03e8;
loc_B85:
  if (memory[adr(_ds, 0x57B)] > _al)
    goto loc_B97;
loc_B8B:
  sub_13D8();
  if (_al != 0)
    goto loc_B8B;
loc_B90:
  sub_13D8();
  if (_al == 0)
    goto loc_B90;
  _Sleep(_cx);
loc_B97:
  sub_11E3();
  _ax = *(WORD*)&memory[adr(_ds, 0x563)];
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  sub_1145();
  sub_34A0();
  if (!flags.carry)
    return;
  sub_1145();
  return;
loc_BAC:
  sub_1B7A();
  if (!flags.carry)
    goto loc_BB2;
  return;
loc_BB2:
  if (memory[adr(_ds, 0x1CB8)] != 0)
    return;
  if (memory[adr(_ds, 0x558)] == 0)
    goto loc_C1C;
  if (memory[adr(_ds, 0x559)] == 0)
    goto loc_BD3;
  if (memory[adr(_ds, 0x1CBF)] != 0)
    return;
  memory[adr(_ds, 0x559)] -= 1;
  return;
loc_BD3:
  memory[adr(_ds, 0x558)] -= 1;
  if (memory[adr(_ds, 0x558)] != 0)
    goto loc_BE5;
  *(WORD*)&memory[adr(_ds, 0x572)] = 8;
  sub_FC9();
  goto loc_C1C;
loc_BE5:
  sub_1020();
  *(WORD*)&memory[adr(_ds, 0x55D)] = _bx;
  _al = memory[adr(_ds, 0x558)];
  _ah = memory[adr(_ds, 0x56E)];
  sub_F87();
  if (memory[adr(_ds, 0x558)] == 2)
    goto loc_C00;
  sub_11E3();
loc_C00:
  sub_1B7A();
  if (flags.carry)
    return;
  sub_20F5();
  if (flags.carry)
    return;
  _dl = memory[adr(_ds, 0x57B)];
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  sub_1145();
  return;
loc_C1C:
  if (memory[adr(_ds, 0x55C)] < 1)
    goto loc_C6A;
  if (memory[adr(_ds, 0x55C)] != 1)
    goto loc_C5F;
  memory[adr(_ds, 0x55C)] += 1;
  *(WORD*)&memory[adr(_ds, 0x572)] = 6;
  _dl = memory[adr(_ds, 0x57B)];
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x563)] = _ax;
  sub_11E3();
  sub_1B7A();
  if (flags.carry)
    return;
  sub_20F5();
  if (flags.carry)
    return;
  _ax = *(WORD*)&memory[adr(_ds, 0x563)];
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x565)] = 3587;
  *(WORD*)&memory[adr(_ds, 0x55D)] = 2522;
  sub_1145();
loc_C5F:
  if (memory[adr(_ds, 0x699)] != 0)
    goto loc_E78;
  return;
  goto loc_E78;
loc_C6A:
  if (memory[adr(_ds, 0x571)] != 0)
    goto loc_C74;
  goto loc_E23;
loc_C74:
  sub_FC9();
  if (!flags.carry)
    goto loc_C90;
  memory[adr(_ds, 0x56E)] = 0;
  memory[adr(_ds, 0x576)] = 2;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x55B)] = 0;
  goto loc_CC1;
loc_C90:
  _al = memory[adr(_ds, 0x578)];
  flags.carry = memory[adr(_ds, 0x577)] < _al;
  memory[adr(_ds, 0x577)] -= _al;
  if (!flags.carry)
    goto loc_CC1;
  if (memory[adr(_ds, 0x571)] == 1)
    goto loc_CB6;
  if (memory[adr(_ds, 0x576)] <= 1)
    goto loc_CAE;
  memory[adr(_ds, 0x576)] -= 1;
  goto loc_CC1;
loc_CAE:
  memory[adr(_ds, 0x571)] = 1;
  goto loc_CC1;
loc_CB6:
  if (memory[adr(_ds, 0x576)] >= 4)
    goto loc_CC1;
  memory[adr(_ds, 0x576)] += 1;
loc_CC1:
  if (memory[adr(_ds, 0x55A)] != 0)
    goto loc_CE7;
  if (memory[adr(_ds, 0x55B)] == 0)
    goto loc_CD5;
  memory[adr(_ds, 0x55B)] -= 1;
  if (memory[adr(_ds, 0x55B)] != 0)
    goto loc_CE7;
loc_CD5:
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_CE7;
  sub_1608();
  if (!flags.carry)
    goto loc_CE7;
  _al = memory[adr(_ds, 0x57C)];
  goto loc_D29;
loc_CE7:
  _al = memory[adr(_ds, 0x57C)];
  if (memory[adr(_ds, 0x571)] == 1)
    goto loc_D06;
  flags.carry = _al < memory[adr(_ds, 0x576)];
  _al = _al - memory[adr(_ds, 0x576)];
  if (!flags.carry)
    goto loc_D4F;
  _al = 0;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x576)] = 1;
  goto loc_D4F;
loc_D06:
  _al = _al + memory[adr(_ds, 0x576)];
  if (_al <= 0xe6)
    goto loc_D4F;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_D22;
  if (_al < 0xf8)
    goto loc_D4F;
  _al = 0xf8;
  memory[adr(_ds, 0x551)] = 1;
  goto loc_D4F;
loc_D22:
  _al = 0xe6;
  memory[adr(_ds, 0x550)] = 0;
loc_D29:
  memory[adr(_ds, 0x571)] = 0;
  memory[adr(_ds, 0x584)] = 0;
  *(WORD*)&memory[adr(_ds, 0x572)] = 2;
  memory[adr(_ds, 0x55B)] = 0;
  memory[adr(_ds, 0x55A)] = 0;
  if (memory[adr(_ds, 0x55C)] == 0)
    goto loc_D4F;
  _push(_ax);
  sub_5AC2();
  _ax = _pop();
loc_D4F:
  memory[adr(_ds, 0x57C)] = _al;
  flags.carry = _al < 0x32;
  _al -= 0x32;
  if (!flags.carry)
    goto loc_D58;
  _al = 0;
loc_D58:
  memory[adr(_ds, 0x57B)] = _al;
  _dl = memory[adr(_ds, 0x57B)];
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x563)] = _ax;
  if (memory[adr(_ds, 0x583)] != 0)
    goto loc_D73;
  sub_11E3();
loc_D73:
  sub_1B7A();
  if (flags.carry)
    goto loc_DC4;
  sub_20F5();
  if (flags.carry)
    goto loc_DC4;
  _ax = *(WORD*)&memory[adr(_ds, 0x563)];
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  if (memory[adr(_ds, 0x584)] == 0)
    goto loc_DA1;
  *(WORD*)&memory[adr(_ds, 0x585)] += 2;
  _bx = (*(WORD*)&memory[adr(_ds, 0x585)]) & 0x0e;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 4034)];
  _bx = *(WORD*)&memory[adr(_ds, _bx + 4050)];
  goto loc_DA8;
loc_DA1:
  _ax = *(WORD*)&memory[adr(_ds, 0x569)];
  _bx = *(WORD*)&memory[adr(_ds, 0x567)];
loc_DA8:
  *(WORD*)&memory[adr(_ds, 0x55D)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x565)] = _bx;
  _al = 0x32;
  flags.carry = _al < memory[adr(_ds, 0x57C)];
  _al = _al - memory[adr(_ds, 0x57C)];
  if (_al == 0)
    goto loc_DDE;
  if (flags.carry)
    goto loc_DDE;
  _cx = 0x0168;
  _Sleep(_cx);
  flags.carry = _bh < _al;
  _bh -= _al;
  if (_bh == 0)
    goto loc_DC4;
  if (!flags.carry)
    goto loc_DCA;
loc_DC4:
  memory[adr(_ds, 0x583)] = 1;
  return;
loc_DCA:
  *(WORD*)&memory[adr(_ds, 0x565)] = _bx;
  _ah = _bl << 1;
  _ax = (_ah * _al) + *(WORD*)&memory[adr(_ds, 0x569)];
  *(WORD*)&memory[adr(_ds, 0x55D)] = _ax;
  goto loc_E1F;
loc_DDE:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_DEE;
  _al = memory[adr(_ds, 0x57B)];
  flags.carry = _al < 0xbb;
  _al -= 0xbb;
  if (flags.carry)
    goto loc_E1F;
  if (!flags.carry)
    goto loc_DFC;
loc_DEE:
  if (memory[adr(_ds, 0x550)] != 2)
    goto loc_E1F;
  _al = memory[adr(_ds, 0x57B)];
  flags.carry = _al < 0x5e;
  _al -= 0x5e;
  if (flags.carry)
    goto loc_E1F;
loc_DFC:
  flags.carry = _bh < _al;
  _bh -= _al;
  if (_bh == 0)
    goto loc_E02;
  if (!flags.carry)
    goto loc_E16;
loc_E02:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_E0F;
  memory[adr(_ds, 0x551)] = 1;
  return;
loc_E0F:
  sub_70D();
  sub_59CB();
  return;
loc_E16:
  *(WORD*)&memory[adr(_ds, 0x565)] = _bx;
  memory[adr(_ds, 0x576)] = 2;
loc_E1F:
  sub_1145();
  return;
loc_E23:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 7)
    goto loc_E31;
  if (memory[adr(_ds, 0x57B)] >= 0xb4)
    goto loc_E78;
loc_E31:
  sub_1608();
  if (flags.carry)
    goto loc_E43;
  memory[adr(_ds, 0x56E)] = 0;
  memory[adr(_ds, 0x571)] = 1;
  goto loc_EB1;
loc_E43:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 0)
    goto loc_E78;
  sub_22F7();
  if (flags.carry)
    goto loc_E56;
  memory[adr(_ds, 0x56C)] = 0;
  goto loc_E78;
loc_E56:
  if (memory[adr(_ds, 0x56C)] != 0)
    goto loc_E60;
  sub_591F();
loc_E60:
  memory[adr(_ds, 0x699)] = 1;
  memory[adr(_ds, 0x56C)] = 1;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_E74;
  _dl = 0xff;
loc_E74:
  memory[adr(_ds, 0x698)] = _dl;
loc_E78:
  _al = memory[adr(_ds, 0x56E)];
  memory[adr(_ds, 0x56F)] = _al;
  _al = memory[adr(_ds, 0x698)];
  memory[adr(_ds, 0x56E)] = _al;
  _al = memory[adr(_ds, 0x699)];
  memory[adr(_ds, 0x571)] = _al;
  if (_al != 0x00)
    goto loc_E91;
  goto loc_F34;
loc_E91:
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_EC9;
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    goto loc_EB1;
  memory[adr(_ds, 0x571)] = 0;
  memory[adr(_ds, 0x584)] = 0;
  memory[adr(_ds, 0x699)] = 0;
  goto loc_F34;
loc_EB1:
  _ah = 0x01;
  _al = 0x20;
  memory[adr(_ds, 0x55B)] = 8;
  if (memory[adr(_ds, 0x550)] != 1)
    goto loc_EF1;
  memory[adr(_ds, 0x550)] = 0;
  goto loc_EF1;
loc_EC9:
  memory[adr(_ds, 0x55B)] = 0;
  _ax = *(WORD*)&memory[adr(_ds, 0x572)];
  _bl = _al;
  if (_al <= 0x02)
    goto loc_ED9;
  _al -= 0x02;
loc_ED9:
  *(WORD*)&memory[adr(_ds, 0x572)] = _ax;
  _ah = 0x08;
  _al = _bl ^ 0x0f;
  _cl = 0x04;
  _al <<= _cl;
  if (memory[adr(_ds, 0x550)] != 1)
    goto loc_EF1;
  memory[adr(_ds, 0x550)] += 1;
loc_EF1:
  memory[adr(_ds, 0x578)] = _al;
  memory[adr(_ds, 0x576)] = _ah;
  memory[adr(_ds, 0x577)] = 1;
  memory[adr(_ds, 0x55C)] = 0;
  _bl = ((memory[adr(_ds, 0x56E)]) + 1) << 1;
  if (memory[adr(_ds, 0x571)] == 0xff)
    goto loc_F14;
  _bl += 0x06;
loc_F14:
  _bh = 0;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 4010)];
  *(WORD*)&memory[adr(_ds, 0x569)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 4022)];
  *(WORD*)&memory[adr(_ds, 0x567)] = _ax;
  memory[adr(_ds, 0x39E0)] = 0;
  if (memory[adr(_ds, 0x127C)] == 0)
    return;
  sub_58F8();
  return;
loc_F34:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 0)
    goto loc_F45;
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 7)
    goto loc_F45;
  sub_3445();
loc_F45:
  sub_FC9();
  _dl = memory[adr(_ds, 0x57B)];
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x563)] = _ax;
  _al = (memory[adr(_ds, 0x56E)]) | memory[adr(_ds, 0x571)];
  if (_al != 0)
    goto loc_F63;
  sub_1069();
  return;
loc_F63:
  sub_1020();
  *(WORD*)&memory[adr(_ds, 0x55D)] = _bx;
  sub_11E3();
  sub_1B7A();
  if (flags.carry)
    return;
  sub_20F5();
  if (flags.carry)
    return;
  _ax = *(WORD*)&memory[adr(_ds, 0x563)];
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x565)] = 2819;
  sub_1145();
}

void sub_F87()
{
  _cx = 0x0b03;
  _cl -= _al;
  *(WORD*)&memory[adr(_ds, 0x565)] = _cx;
  if (_ah == 0xff)
    goto loc_FA6;
  _ah = 0;
  _al <<= 1;
  *(WORD*)&memory[adr(_ds, 0x55D)] += _ax;
  *(WORD*)&memory[adr(_ds, 0x579)] = 0;
  goto loc_FB4;
loc_FA6:
  _ah = 0;
  _al = ((_al << 1) << 1) << 1;
  _ax += 0x0128;
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
loc_FB4:
  _push(_ds);
  _es = _pop();
  _si = *(WORD*)&memory[adr(_ds, 0x55D)];
  _di = 0x0e;
  _al = 0x03;
  sub_2D70();
  *(WORD*)&memory[adr(_ds, 0x55D)] = 0x0e;
}

void sub_FC9()
{
  *(WORD*)&memory[adr(_ds, 0x5F6)] = 8;
  *(WORD*)&memory[adr(_ds, 0x5F8)] = 291;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_FE8;
  *(WORD*)&memory[adr(_ds, 0x5F6)] = 0x24;
  *(WORD*)&memory[adr(_ds, 0x5F8)] = 271;
loc_FE8:
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  if (memory[adr(_ds, 0x56E)] < 1)
    goto loc_101E;
  if (memory[adr(_ds, 0x56E)] != 1)
    goto loc_1007;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x572)];
  if (_ax < *(WORD*)&memory[adr(_ds, 0x5F8)])
    goto loc_101B;
  _ax = (*(WORD*)&memory[adr(_ds, 0x5F8)]) - 1;
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  flags.carry = true;
  return;
loc_1007:
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x572)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x572)];
  if (flags.carry)
    goto loc_1013;
  if (_ax >= *(WORD*)&memory[adr(_ds, 0x5F6)])
    goto loc_101B;
loc_1013:
  _ax = *(WORD*)&memory[adr(_ds, 0x5F6)];
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  flags.carry = true;
  return;
loc_101B:
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
loc_101E:
  flags.carry = false;
}

void sub_1020()
{
  _al = memory[adr(_ds, 0x56E)];
  if (_al == memory[adr(_ds, 0x56F)])
    goto loc_102F;
  *(WORD*)&memory[adr(_ds, 0x572)] = 2;
loc_102F:
  if (*(WORD*)&memory[adr(_ds, 0x572)] >= 8)
    goto loc_1045;
  memory[adr(_ds, 0x577)] -= 1;
  _al = (memory[adr(_ds, 0x577)]) & 0x03;
  if (_al != 0)
    goto loc_1045;
  *(WORD*)&memory[adr(_ds, 0x572)] += 1;
loc_1045:
  _bl = (memory[adr(_ds, 0x56B)]) + 1;
  if (_bl < 0x06)
    goto loc_1052;
  _bl = 0x00;
loc_1052:
  memory[adr(_ds, 0x56B)] = _bl;
  if (memory[adr(_ds, 0x56E)] != 0xff)
    goto loc_1060;
  _bl += 0x06;
loc_1060:
  _bl <<= 1;
  _bh = 0;
  _bx = *(WORD*)&memory[adr(_ds, _bx + 3962)];
}

void sub_1069()
{
  *(WORD*)&memory[adr(_ds, 0x572)] = 2;
  memory[adr(_ds, 0x577)] = 8;
  if (*(WORD*)&memory[adr(_ds, 0x561)] != 3074)
    goto loc_1087;
  memory[adr(_ds, 0x56D)] += 1;
  if (memory[adr(_ds, 0x56D)] & 7)
    return;
loc_1087:
  sub_11E3();
  sub_1B7A();
  if (flags.carry)
    return;
  sub_20F5();
  if (flags.carry)
    return;
  sub_2DFD();
  _bl = _dl;
  _bx &= 0x0e;
  _si = *(WORD*)&memory[adr(_ds, _bx + 3986)];
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x55F)];
  _bp = 0x05fa;
  *(WORD*)&memory[adr(_ds, 0x561)] = 3074;
  _cx = 0x0602;
  sub_2D35();
  sub_2DFD();
  _bl = _dl;
  _bx &= 0x0006;
  _si = *(WORD*)&memory[adr(_ds, _bx + 4002)];
  _di = (*(WORD*)&memory[adr(_ds, 0x55F)]) + 0xf0;
  _bp = 0x0612;
  _cx = 0x0602;
  sub_2D35();
  memory[adr(_ds, 0x583)] = 0;
}

void sub_10DD()
{
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x576)] = 2;
  memory[adr(_ds, 0x578)] = 1;
  memory[adr(_ds, 0x577)] = 0xff;
  memory[adr(_ds, 0x56E)] = 0;
  memory[adr(_ds, 0x55A)] = 1;
  _ax = *(WORD*)&memory[adr(_ds, 0xFAC)];
  *(WORD*)&memory[adr(_ds, 0x569)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0xFB8)];
  *(WORD*)&memory[adr(_ds, 0x567)] = _ax;
  memory[adr(_ds, 0x550)] = 2;
}

void sub_1112()
{
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = memory[adr(_ds, 0x57B)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x55F)] = _ax;
  sub_1124();
}

void sub_1124()
{
  _ax = SEG_DATA;
  _es = _ax;
  _di = 0x05fa;
  _push(_ds);
  _si = *(WORD*)&memory[adr(_ds, 0x55F)];
  _ax = 0xb800;
  _ds = _ax;
  _cx = *(WORD*)&memory[adr(_es, 1377)];
  sub_2DCA();
  _ds = _pop();
  memory[adr(_ds, 0x583)] = 0;
}

void sub_1145()
{
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x55F)];
  _bp = 0x05fa;
  _si = *(WORD*)&memory[adr(_ds, 0x55D)];
  _cx = *(WORD*)&memory[adr(_ds, 0x565)];
  *(WORD*)&memory[adr(_ds, 0x561)] = _cx;
  memory[adr(_ds, 0x583)] = 0;
  sub_2D35();
}

void sub_1166()
{
  _dl = memory[adr(_ds, 0x57B)];
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _cx < 0x0c;
  _cx -= 0x0c;
  if (!flags.carry)
    goto loc_1175;
  _cx = 0;
loc_1175:
  if (_cx < 0x010f)
    goto loc_117E;
  _cx = 0x010e;
loc_117E:
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x581)] = _ax;
  _di = _ax;
  _ax = 0xb800;
  _es = _ax;
  _bp = 0x0e;
  _si = 0x1679;
  _cx = 0x1205;
  sub_2CCC();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x57F)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5A3C)] = 0;
  *(WORD*)&memory[adr(_ds, 0x5A3E)] = 0;
loc_11AB:
  sub_5A1C();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x57F)];
  if (_dx < 0x0a)
    goto loc_11AB;
  sub_5B21();
  _di = *(WORD*)&memory[adr(_ds, 0x581)];
  _si = 0x0e;
  _cx = 0x1205;
  memory[adr(_ds, 0x583)] = 0;
  sub_2D9D();
  if (memory[adr(_ds, 0x1678)] == 0)
    return;
  if (memory[adr(_ds, 0x1F80)] == 0)
    return;
  memory[adr(_ds, 0x1F80)] -= 1;
}

void sub_11E3()
{
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x55F)];
  _si = 0x05fa;
  _cx = *(WORD*)&memory[adr(_ds, 0x561)];
  sub_2D9D();
}

void sub_1200()
{
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x69F)];
  if (_ax >= 0x0002)
    goto loc_1210;
  return;
loc_1210:
  *(WORD*)&memory[adr(_ds, 0x69F)] = _dx;
  if (memory[adr(_ds, 0x69B)] != 0)
    goto loc_122E;
  sub_12C1();
  sub_13B7();
  _dx = _ax;
loc_1223:
  sub_13B7();
  _ax -= _dx;
  if (_ax < 0xf8ed)
    goto loc_1223;
  return;
loc_122E:
  _dx = 0x0201;
  _in(_al, _dx);
  _al &= 0x10;
  memory[adr(_ds, 0x69A)] = _al;
  memory[adr(_ds, 0x69E)] = 3;
  sub_13B7();
  *(WORD*)&memory[adr(_ds, 0x69C)] = _ax;
  _out(_dx, _al);
  _cx = 0x07d0;
loc_1246:
  _in(_al, _dx);
  if (_al & 0x01)
    goto loc_125E;
  if (!(memory[adr(_ds, 0x69E)] & 1))
    goto loc_125E;
  memory[adr(_ds, 0x69E)] &= 0xfe;
  sub_12A1();
  memory[adr(_ds, 0x698)] = _bl;
loc_125E:
  if (_al & 0x02)
    goto loc_1275;
  if (!(memory[adr(_ds, 0x69E)] & 2))
    goto loc_1275;
  memory[adr(_ds, 0x69E)] &= 0xfd;
  sub_12A1();
  memory[adr(_ds, 0x699)] = _bl;
loc_1275:
  if (!(memory[adr(_ds, 0x69E)] & 3))
    return;
  sub_13B7();
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x69C)];
  if (--_cx && _ax != 0x1964)
    goto loc_1246;
  if (!(memory[adr(_ds, 0x69E)] & 1))
    goto loc_1294;
  memory[adr(_ds, 0x698)] = 0xff;
loc_1294:
  if (!(memory[adr(_ds, 0x69E)] & 2))
    return;
  memory[adr(_ds, 0x699)] = 0xff;
}

void sub_12A1()
{
  _push(_ax);
  sub_13B7();
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x69C)];
  _bx = _ax;
  _ax = _pop();
  if (_bx >= 0xf5e6)
    goto loc_12B5;
  _bl = 0x01;
  return;
loc_12B5:
  if (_bx >= 0xfafa)
    goto loc_12BE;
  _bl = 0;
  return;
loc_12BE:
  _bl = 0xff;
}

void sub_12C1()
{
  _al = memory[adr(_ds, 0x6BA)];
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_12D3;
  _al = (_al & memory[adr(_ds, 0x6BD)]) & memory[adr(_ds, 0x6BE)];
loc_12D3:
  _al = _al ^ 0x80;
  if (_al == 0)
    goto loc_12D9;
  _al = 0x01;
loc_12D9:
  memory[adr(_ds, 0x699)] = _al;
  _al = memory[adr(_ds, 0x6B8)];
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_12EE;
  _al = (_al & memory[adr(_ds, 0x6BC)]) & memory[adr(_ds, 0x6BF)];
loc_12EE:
  _al = _al ^ 0x80;
  if (_al == 0)
    goto loc_12F7;
  memory[adr(_ds, 0x699)] = 0xff;
loc_12F7:
  _al = memory[adr(_ds, 0x6B9)];
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_1309;
  _al = (_al & memory[adr(_ds, 0x6BC)]) & memory[adr(_ds, 0x6BD)];
loc_1309:
  _al = _al ^ 0x80;
  if (_al == 0)
    goto loc_130F;
  _al = 0x01;
loc_130F:
  memory[adr(_ds, 0x698)] = _al;
  _al = memory[adr(_ds, 0x6BB)];
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_1324;
  _al = (_al & memory[adr(_ds, 0x6BE)]) & memory[adr(_ds, 0x6BF)];
loc_1324:
  _al = _al ^ 0x80;
  if (_al == 0)
    goto loc_132D;
  memory[adr(_ds, 0x698)] = 0xff;
loc_132D:
  _al = memory[adr(_ds, 0x6B7)];
  _cl = 0x03;
  _al >>= _cl;
  memory[adr(_ds, 0x69A)] = _al;
}

void sub_1338()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
  if (_ax == *(WORD*)&memory[adr(_ds, 0x691)])
    return;
  *(WORD*)&memory[adr(_ds, 0x691)] = _ax;
  if (memory[adr(_ds, 0x6C0)] & 0x80)
    goto loc_1358;
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
  if (_ax == *(WORD*)&memory[adr(_ds, 0x6E00)])
    return;
  sub_5E70();
  return;
loc_1358:
  if (!(memory[adr(_ds, 0x6C9)] & 0x80))
    goto loc_1360;
  return;
loc_1360:
  if (memory[adr(_ds, 0x6CC)] & 0x80)
    goto loc_136D;
  memory[adr(_ds, 0x1F80)] = 9;
  return;
loc_136D:
  if (!(memory[adr(_ds, 0x6C1)] & 0x80))
    goto loc_13A5;
  if (memory[adr(_ds, 0x6CB)] & 0x80)
    goto loc_1381;
  memory[adr(_ds, 0x41C)] = 0xff;
  return;
loc_1381:
  if (memory[adr(_ds, 0x6C8)] & 0x80)
    goto loc_138E;
  memory[adr(_ds, 0x41B)] = 0xff;
  return;
loc_138E:
  if (memory[adr(_ds, 0x6C7)] & 0x80)
    return;
  memory[adr(_ds, 0x0)] = (~memory[adr(_ds, 0x0)]);
  if (memory[adr(_ds, 0x0)] != 0)
    return;
  sub_5B21();
  return;
  return;
loc_13A5:
  sub_147F();
  _ax = _pop();
}

void sub_13AA()
{
  _ax = 0xf000;
  _es = _ax;
  _al = 0xff;
  memory[adr(_ds, 0x697)] = _al;
}

void sub_13B7()
{
  _al = 0x00;
  _out(0x43, _al);
  _in(_al, 0x40);
  _ah = _al;
  _in(_al, 0x40);
  _xchg(_al, _ah);
}

// class CICall
// class CIAssignment
// class CIAlu
// class CIAssignment
// class CICompare
// class CIConditionalJump
// class CIReturn
// class CILabel
// class CICompare
// class CIReturn
void sub_13D8()
{
  _dx = 0x03da;
  _in(_al, _dx);
  _al &= 0x08;
}

// class CIData
// class CIData
// class CIData
// class CIData
// class CIData
void sub_13E8()
{
  _push(_ax);
  _push(_es);
  _push(_di);
  _push(_cx);
  _ax = SEG_DATA;
  _es = _ax;
  flags.direction = false;
  _di = 0x06b7;
  _cx = 0x16;
  _al = 0x80;
  _rep_stosb<MemData, DirForward>();
  _ax = (*(WORD*)&memory[adr(_es, 1683)]) - 0x70;
  *(WORD*)&memory[adr(_es, 1681)] = _ax;
  _ax = 0x40;
  _es = _ax;
  _al = memory[adr(_es, 18)];
  byte_code_13E7 = _al;
  _cx = _pop();
  _di = _pop();
  _es = _pop();
  _ax = _pop();
}

void sub_1419()
{
  _ax = 0;
  _es = _ax;
  _ax = *(WORD*)&memory[adr(_es, 36)];
  _bx = *(WORD*)&memory[adr(_es, 38)];
  _cx = *(WORD*)&memory[adr(_es, 288)];
  _dx = *(WORD*)&memory[adr(_es, 290)];
  word_code_13DF = _ax;
  word_code_13E1 = _bx;
  word_code_13E3 = _cx;
  word_code_13E5 = _dx;
  _bx = 0x14b3;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_1450;
  _bx = 0x14fb;
loc_1450:
  flags.interrupt = false;
  *(WORD*)&memory[adr(_es, 36)] = _bx;
  *(WORD*)&memory[adr(_es, 38)] = _cs;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_147D;
  *(WORD*)&memory[adr(_es, 288)] = 0x1554;
  *(WORD*)&memory[adr(_es, 290)] = _cs;
  _ax = 0x40;
  _es = _ax;
  _al = (memory[adr(_es, 24)]) | 0x01;
  memory[adr(_es, 24)] = _al;
loc_147D:
  flags.interrupt = true;
}

void sub_147F()
{
  _ax = 0;
  _es = _ax;
  _ax = word_code_13DF;
  _bx = word_code_13E1;
  _cx = word_code_13E3;
  _dx = word_code_13E5;
  flags.interrupt = false;
  *(WORD*)&memory[adr(_es, 36)] = _ax;
  *(WORD*)&memory[adr(_es, 38)] = _bx;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_14B1;
  *(WORD*)&memory[adr(_es, 288)] = _cx;
  *(WORD*)&memory[adr(_es, 290)] = _dx;
loc_14B1:
  flags.interrupt = true;
}

// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CITwoArgOp
// class CIAssignment
// class CIAlu
// class CITest
// class CIConditionalJump
// class CIAlu
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIZeroArgOp
// class CIString
// class CIConditionalJump
// class CIAlu
// class CIAlu
// class CIAssignment
// class CILabel
// class CITwoArgOp
// class CIAssignment
// class CIAlu
// class CITwoArgOp
// class CIAssignment
// class CITwoArgOp
// class CICall
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CITwoArgOp
// class CISingleArgOp
// class CIReturn
// class CIZeroArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAlu
// class CITest
// class CIConditionalJump
// class CIAlu
// class CILabel
// class CICompare
// class CIConditionalJump
// class CICompare
// class CIConditionalJump
// class CISingleArgOp
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CISingleArgOp
// class CICompare
// class CIConditionalJump
// class CILabel
// class CICall
// class CIJump
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIZeroArgOp
// class CIString
// class CIConditionalJump
// class CIAlu
// class CIAlu
// class CIAssignment
// class CILabel
// class CICall
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CISingleArgOp
// class CIReturn
// class CILabel
// class CISingleArgOp
// class CIReturn
// class CILabel
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIAssignment
// class CIJump
void sub_1572()
{
  _al = (memory[adr(_es, 1737)]) | memory[adr(_es, 1719)];
  if (_al != 0x00)
    return;
  if (memory[adr(_es, 1738)] & 0x80)
    goto loc_158D;
  _al = 0x20;
  _out(0x20, _al);
  goto loc_1557;
loc_158D:
  if (memory[adr(_es, 1721)] & 0x80)
    goto loc_15A4;
  if (memory[adr(_es, 1680)] < 1)
    return;
  memory[adr(_es, 1680)] -= 1;
  goto loc_15B9;
loc_15A4:
  if (memory[adr(_es, 1723)] & 0x80)
    return;
  if (memory[adr(_es, 1680)] >= 7)
    return;
  memory[adr(_es, 1680)] += 1;
loc_15B9:
  _push(_dx);
  _al = 0x02;
  _dx = 0x03d4;
  _out(_dx, _al);
  _al = (memory[adr(_es, 1680)]) + 0x27;
  _dx += 1;
  _out(_dx, _al);
  _dx = _pop();
}

void sub_15D0()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _cl = memory[adr(_ds, _bx + 4110)];
loc_15D8:
  sub_2DFD();
  _dl &= 0x07;
  if (_dl > _cl)
    goto loc_15D8;
  _dl = _dl + memory[adr(_ds, _bx + 4102)];
  if (_dl == memory[adr(_ds, 0x1028)])
    goto loc_15D8;
  memory[adr(_ds, 0x1028)] = _dl;
  _bl = _dl;
  _cl = memory[adr(_ds, _bx + 4080)];
  _dl = 0x88;
  if (_cl & 0x80)
    goto loc_15FF;
  _dl = 0x90;
loc_15FF:
  _cx = ((_cx & 0x7f) << 1) << 1;
}

void sub_1608()
{
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_1613;
  sub_30FA();
  return;
loc_1613:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 0)
    goto loc_161E;
  sub_16C6();
  return;
loc_161E:
  _al = (memory[adr(_ds, 0x57B)]) & 0xf8;
  if (_al == 0x60)
    goto loc_1630;
  sub_1657();
  if (flags.carry)
    return;
  sub_17AD();
  return;
loc_1630:
  if (memory[adr(_ds, 0x550)] >= 2)
    goto loc_1655;
  memory[adr(_ds, 0x57B)] = _al;
  _al += 0x32;
  memory[adr(_ds, 0x57C)] = _al;
  if (memory[adr(_ds, 0x550)] == 1)
    goto loc_1653;
  memory[adr(_ds, 0x550)] = 1;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x556)] = _dx;
loc_1653:
  flags.carry = true;
  return;
loc_1655:
  flags.carry = false;
}

void sub_1657()
{
  _cl = ((memory[adr(_ds, 0x57B)]) + 0x02) & 0xf8;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl = memory[adr(_ds, _bx + 4102)];
loc_1669:
  _al = memory[adr(_ds, _bx + 4080)];
  if (_al != 0x00)
    goto loc_1678;
  memory[adr(_ds, 0x127C)] = 0;
  flags.carry = false;
  return;
loc_1678:
  _bx += 1;
  _ch = 0x88;
  if (_al & 0x80)
    goto loc_1681;
  _ch = 0x90;
loc_1681:
  if (_cl != _ch)
    goto loc_1669;
  _ax = ((_ax & 0x7f) << 1) << 1;
  _dx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0xfff8;
  if (_dx < _ax)
    goto loc_1669;
  _dx = ((*(WORD*)&memory[adr(_ds, 0x579)]) - 0x0f) & 0xfff8;
  if (_dx > _ax)
    goto loc_1669;
  _ch -= 0x02;
  memory[adr(_ds, 0x57B)] = _ch;
  _ch += 0x32;
  memory[adr(_ds, 0x57C)] = _ch;
  if (memory[adr(_ds, 0x127C)] != 0)
    goto loc_16C4;
  memory[adr(_ds, 0x127C)] = 1;
  sub_590E();
loc_16C4:
  flags.carry = true;
}

void sub_16C6()
{
  memory[adr(_ds, 0x39E0)] = 0;
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_16FC;
  _ax = (*(WORD*)&memory[adr(_ds, 0x2650)]) - 0x0004;
  _dl = (memory[adr(_ds, 0x2652)]) - 0x08;
  _si = 0x0c;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e10;
  sub_2E29();
  if (!flags.carry)
    goto loc_16FC;
  memory[adr(_ds, 0x551)] = 1;
  flags.carry = false;
  return;
loc_16FC:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 3)
    goto loc_170E;
  sub_3C43();
  if (!flags.carry)
    goto loc_170E;
  memory[adr(_ds, 0x55C)] = 1;
  return;
loc_170E:
  _cl = (memory[adr(_ds, 0x57B)]) & 0xf8;
  _bx = *(WORD*)&memory[adr(_ds, ((*(WORD*)&memory[adr(_ds, 0x4)]) << 1) + 4713)];
loc_171F:
  _ch = memory[adr(_ds, _bx + 4137)];
  if (_ch != 0x00)
    goto loc_172A;
  flags.carry = false;
  return;
loc_172A:
  _al = memory[adr(_ds, _bx + 4233)];
  memory[adr(_ds, 0x127B)] = _al;
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 4521)];
  *(WORD*)&memory[adr(_ds, 0x1279)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 4329)];
  _bl >>= 1;
  _bx += 1;
  if (_cl != _ch)
    goto loc_171F;
  _dx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0xfff8;
  if (_dx < _ax)
    goto loc_171F;
  _dx = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _dx < *(WORD*)&memory[adr(_ds, 0x1279)];
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x1279)];
  if (!flags.carry)
    goto loc_175D;
  _dx = 0;
loc_175D:
  _dx &= 0xfffc;
  if (_dx > _ax)
    goto loc_171F;
  memory[adr(_ds, 0x57B)] = _ch;
  _ch += 0x32;
  memory[adr(_ds, 0x57C)] = _ch;
  _al = memory[adr(_ds, 0x127B)];
  memory[adr(_ds, 0x55C)] = _al;
  if (_al == 0x00)
    goto loc_1780;
  *(WORD*)&memory[adr(_ds, 0x579)] &= 0xfffc;
loc_1780:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 4)
    goto loc_1797;
  _bx -= 1;
  flags.carry = _bx < 0x27;
  _bx -= 0x27;
  if (flags.carry)
    goto loc_1797;
  if (_bx >= 0x10)
    goto loc_1797;
  _bx += 1;
  memory[adr(_ds, 0x39E0)] = _bl;
loc_1797:
  flags.carry = true;
}

void sub_1799()
{
  _cl = 0x03;
  _bx >>= _cl;
  _ch = _bl;
  _cl = 0x03;
  _bx >>= _cl;
  _cl = _ch & 0x07;
  _ch = 0x80 >> _cl;
}

void sub_17AD()
{
  _dl = (memory[adr(_ds, 0x57B)]) & 0xf8;
  _bx = 0;
  if (_dl == 0x08)
    goto loc_17C9;
  _bl += 1;
  if (_dl == 0x28)
    goto loc_17C9;
  _bl += 1;
  if (_dl != 0x48)
    goto loc_1810;
loc_17C9:
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  if (_bx != *(WORD*)&memory[adr(_ds, 0x52F)])
    goto loc_17FC;
  if (memory[adr(_ds, 0x525)] > 3)
    goto loc_17FC;
  if (_bl == 0x01)
    goto loc_17EE;
  _cx = 0x0004;
  _cl = ((_cl - memory[adr(_ds, 0x525)]) << 1) << 1;
  _ax += _cx;
  goto loc_17FC;
loc_17EE:
  _ch = 0;
  _cl = (((memory[adr(_ds, 0x525)]) + 1) << 1) << 1;
  _ax -= _cx;
loc_17FC:
  _bl = memory[adr(_ds, _bx + 4133)];
  _si = _bx;
  _bx = _ax + 0x0a;
  sub_1799();
  if (memory[adr(_ds, _bx + _si + 4118)] & _ch)
    goto loc_1812;
loc_1810:
  flags.carry = false;
  return;
loc_1812:
  memory[adr(_ds, 0x57B)] = _dl;
  _dl += 0x32;
  memory[adr(_ds, 0x57C)] = _dl;
  *(WORD*)&memory[adr(_ds, 0x579)] &= 0xfff8;
  memory[adr(_ds, 0x55C)] = 1;
  flags.carry = true;
}

void sub_1830()
{
  memory[adr(_ds, 0x1665)] = 0;
  memory[adr(_ds, 0x1673)] = 0;
  memory[adr(_ds, 0x1677)] = 0;
  memory[adr(_ds, 0x1678)] = 0;
  *(WORD*)&memory[adr(_ds, 0x166C)] = 9;
}

void sub_184B()
{
  if (memory[adr(_ds, 0x1673)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x17EC)])
    goto loc_185D;
  return;
loc_185D:
  *(WORD*)&memory[adr(_ds, 0x17EC)] = _dx;
  if (memory[adr(_ds, 0x1677)] == 0)
    goto loc_187F;
  _ax = (*(WORD*)&memory[adr(_ds, 0x1671)]) & 0xfff8;
  _bx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0xfff8;
  if (_ax != _bx)
    goto loc_187F;
  memory[adr(_ds, 0x1674)] = 0;
loc_187F:
  memory[adr(_ds, 0x17E9)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x17EA)] > 1)
    goto loc_188E;
  *(WORD*)&memory[adr(_ds, 0x17EA)] -= 1;
loc_188E:
  _ax = *(WORD*)&memory[adr(_ds, 0x1671)];
  _dx = *(WORD*)&memory[adr(_ds, 0x17EA)];
  _cl = 0x03;
  _dl >>= _cl;
  if (memory[adr(_ds, 0x1674)] < 1)
    goto loc_18B5;
  if (memory[adr(_ds, 0x1674)] != 1)
    goto loc_18AF;
  _ax += _dx;
  if (_ax < 0x012f)
    goto loc_18B5;
  _ax = 0x012e;
  goto loc_18B5;
loc_18AF:
  flags.carry = _ax < _dx;
  _ax -= _dx;
  if (!flags.carry)
    goto loc_18B5;
  _ax = 0;
loc_18B5:
  *(WORD*)&memory[adr(_ds, 0x1671)] = _ax;
  _bx = *(WORD*)&memory[adr(_ds, 0x17DF)];
  _al = ((memory[adr(_ds, 0x17E9)]) >> 1) + memory[adr(_ds, 0x1673)];
  _dl = _al;
  flags.carry = _al < memory[adr(_ds, 0x1676)];
  _al = _al - memory[adr(_ds, 0x1676)];
  if (flags.carry)
    goto loc_18E1;
  flags.carry = _bh < _al;
  _bh -= _al;
  if (_bh == 0)
    goto loc_18D3;
  if (!flags.carry)
    goto loc_18E1;
loc_18D3:
  memory[adr(_ds, 0x1673)] = 0;
  memory[adr(_ds, 0x1678)] = 0;
  sub_1922();
  return;
loc_18E1:
  memory[adr(_ds, 0x1673)] = _dl;
  _cx = *(WORD*)&memory[adr(_ds, 0x1671)];
  *(WORD*)&memory[adr(_ds, 0x17E1)] = _bx;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x17E7)] = _ax;
  if (memory[adr(_ds, 0x17E9)] == 2)
    goto loc_18FD;
  sub_1922();
loc_18FD:
  sub_1B7A();
  if (flags.carry)
    return;
  _di = *(WORD*)&memory[adr(_ds, 0x17E7)];
  *(WORD*)&memory[adr(_ds, 0x17E5)] = _di;
  _cx = *(WORD*)&memory[adr(_ds, 0x17E1)];
  *(WORD*)&memory[adr(_ds, 0x17E3)] = _cx;
  _ax = 0xb800;
  _es = _ax;
  _si = *(WORD*)&memory[adr(_ds, 0x17DD)];
  _bp = 0x17ee;
  sub_2CCC();
}

void sub_1922()
{
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x17E5)];
  _si = 0x17ee;
  _cx = *(WORD*)&memory[adr(_ds, 0x17E3)];
  sub_2D9D();
}

void sub_1936()
{
  memory[adr(_ds, 0x166A)] -= 1;
  if (memory[adr(_ds, 0x166A)] == 0)
    goto loc_193D;
  return;
loc_193D:
  memory[adr(_ds, 0x166A)] = 0x0d;
  sub_13D8();
  if (_al != 0)
    return;
  if (memory[adr(_ds, 0x1665)] == 0)
    goto loc_1951;
  sub_1B05();
loc_1951:
  if (memory[adr(_ds, 0x1673)] != 0)
    return;
  if (memory[adr(_ds, 0x1665)] != 0)
    goto loc_19CD;
  if (memory[adr(_ds, 0x57B)] > 0x60)
    return;
  memory[adr(_ds, 0x1677)] = 0;
  if (memory[adr(_ds, 0x550)] != 1)
    goto loc_198A;
  if (memory[adr(_ds, 0x418)] != 0)
    goto loc_198A;
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x556)];
  if (_dx < 0x48)
    goto loc_198A;
  memory[adr(_ds, 0x1677)] += 1;
loc_198A:
  sub_2DFD();
  if (memory[adr(_ds, 0x1677)] == 0)
    goto loc_199A;
  _dl &= 0x03;
  goto loc_19A2;
loc_199A:
  _dl &= 0x0f;
  if (_dl >= 0x0c)
    return;
loc_19A2:
  memory[adr(_ds, 0x1669)] = _dl;
  sub_1AEA();
  *(WORD*)&memory[adr(_ds, 0x1666)] = _cx;
  memory[adr(_ds, 0x1668)] = _dl;
  sub_1B05();
  if (flags.carry)
    goto loc_198A;
  memory[adr(_ds, 0x1665)] = 0x1d;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 6174)];
  *(WORD*)&memory[adr(_ds, 0x166C)] = _ax;
  memory[adr(_ds, 0x1670)] = 1;
loc_19CD:
  sub_1B05();
  if (flags.carry)
    return;
  memory[adr(_ds, 0x1664)] = 0;
  sub_1B4C();
  if (!flags.carry)
    goto loc_19E1;
  memory[adr(_ds, 0x1664)] += 1;
  return;
loc_19E1:
  if (memory[adr(_ds, 0x1665)] != 0x10)
    goto loc_19F0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x166E)] = _dx;
loc_19F0:
  if (memory[adr(_ds, 0x1665)] != 0x0f)
    goto loc_1A76;
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x166E)];
  if (_dx >= *(WORD*)&memory[adr(_ds, 0x166C)])
    goto loc_1A76;
  if (memory[adr(_ds, 0x1670)] == 0)
    return;
  if (memory[adr(_ds, 0x1673)] != 0)
    return;
  if (memory[adr(_ds, 0x418)] != 0)
    return;
  memory[adr(_ds, 0x1670)] -= 1;
  memory[adr(_ds, 0x1678)] = 1;
  _al = memory[adr(_ds, 0x1668)];
  memory[adr(_ds, 0x1673)] = _al;
  sub_2DFD();
  _dx = (_dx & 0x0f) + *(WORD*)&memory[adr(_ds, 0x1666)];
  *(WORD*)&memory[adr(_ds, 0x1671)] = _dx;
  _al = 0x01;
  if (_dx < *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_1A42;
  _al = 0xff;
loc_1A42:
  memory[adr(_ds, 0x1674)] = _al;
  sub_2DFD();
  _bl = _dl;
  _bx &= 0x0006;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 6089)];
  *(WORD*)&memory[adr(_ds, 0x17DD)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 6097)];
  *(WORD*)&memory[adr(_ds, 0x17DF)] = _ax;
  _bl >>= 1;
  _al = memory[adr(_ds, _bx + 6105)];
  memory[adr(_ds, 0x1676)] = _al;
  *(WORD*)&memory[adr(_ds, 0x17EA)] = 0x20;
  memory[adr(_ds, 0x17E9)] = 1;
  memory[adr(_ds, 0x1675)] = 0;
  return;
loc_1A76:
  memory[adr(_ds, 0x1665)] -= 1;
  _cx = *(WORD*)&memory[adr(_ds, 0x1666)];
  _dl = memory[adr(_ds, 0x1668)];
  if (memory[adr(_ds, 0x1665)] <= 0x0e)
    goto loc_1A93;
  _dl = (_dl + memory[adr(_ds, 0x1665)]) - 0x0e;
  goto loc_1A9A;
loc_1A93:
  _dl = (_dl + 0x0e) - memory[adr(_ds, 0x1665)];
loc_1A9A:
  memory[adr(_ds, 0x166B)] = _dl;
  sub_2CB0();
  _di = _ax;
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  _cx = 0x0004;
  if (memory[adr(_ds, 0x1665)] <= 0x0e)
    goto loc_1AD7;
  if (memory[adr(_ds, 0x418)] == 0)
    goto loc_1AD2;
  _al = (memory[adr(_ds, 0x166B)]) - memory[adr(_ds, 0x1668)];
  _ah = 0;
  _cl = 0x03;
  _ax = (_ax << _cl) + 0x15e0;
  _si = _ax;
  _cx = 0x0004;
  _rep_movsw<MemB800, MemData, DirForward>();
  return;
loc_1AD2:
  _ax = 0;
  _rep_stosw<MemB800, DirForward>();
  return;
loc_1AD7:
  _al = (memory[adr(_ds, 0x166B)]) - memory[adr(_ds, 0x1668)];
  _ah = 0x0a;
  _ax = (_ah * _al) + 0x2681;
  _si = _ax;
  _rep_movsw<MemB800, MemData, DirForward>();
}

void sub_1AEA()
{
  _bh = 0;
  _bl = (_dl & 0x03) << 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 5720)];
  _bl = (_dl >> 2) & 0x03;
  _dl = memory[adr(_ds, _bx + 5728)];
}

void sub_1B05()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x1666)];
  _dl = memory[adr(_ds, 0x1668)];
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _si = 0x20;
  _di = 0x18;
  _cx = 0x0e0f;
  sub_2E29();
  if (!flags.carry)
    return;
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_1B4A;
  if (memory[adr(_ds, 0x55A)] != 0)
    goto loc_1B4A;
  if (memory[adr(_ds, 0x57B)] >= 0x60)
    goto loc_1B4A;
  if (memory[adr(_ds, 0x1665)] < 5)
    goto loc_1B4A;
  if (memory[adr(_ds, 0x1665)] >= 0x19)
    goto loc_1B4A;
  memory[adr(_ds, 0x551)] = 1;
loc_1B4A:
  flags.carry = true;
}

void sub_1B4C()
{
  _al = memory[adr(_ds, 0x1669)];
  if (_al >= 0x08)
    goto loc_1B78;
  _bx = 0x0002;
  if (!(_al & 0x04))
    goto loc_1B5C;
  _bl <<= 1;
loc_1B5C:
  _ax = (*(WORD*)&memory[adr(_ds, _bx + 7984)]) + 0x10;
  if (_ax < *(WORD*)&memory[adr(_ds, 0x1666)])
    goto loc_1B78;
  flags.carry = _ax < 0x30;
  _ax -= 0x30;
  if (!flags.carry)
    goto loc_1B70;
  _ax = 0;
loc_1B70:
  if (_ax > *(WORD*)&memory[adr(_ds, 0x1666)])
    goto loc_1B78;
  flags.carry = true;
  return;
loc_1B78:
  flags.carry = false;
}

void sub_1B7A()
{
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 0)
    goto loc_1BE1;
  _dl = memory[adr(_ds, 0x1673)];
  if (_dl == 0x00)
    goto loc_1BE1;
  _cx = *(WORD*)&memory[adr(_ds, 0x17DF)];
  _xchg(_cl, _ch);
  _si = 0x10;
  _ax = *(WORD*)&memory[adr(_ds, 0x1671)];
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _ch = 0x0e;
  sub_2E29();
  if (!flags.carry)
    return;
  sub_11E3();
  sub_1922();
  sub_10DD();
  if (memory[adr(_ds, 0x1675)] != 0)
    goto loc_1BDF;
  memory[adr(_ds, 0x1675)] = 1;
  sub_1166();
  _dl = 0x01;
  if (memory[adr(_ds, 0x1674)] == 0xff)
    goto loc_1BCB;
  _dl = 0xff;
loc_1BCB:
  memory[adr(_ds, 0x1674)] = _dl;
  *(WORD*)&memory[adr(_ds, 0x17EA)] = 0x60;
  memory[adr(_ds, 0x17E9)] = 1;
  memory[adr(_ds, 0x55C)] = 0;
loc_1BDF:
  flags.carry = true;
  return;
loc_1BE1:
  flags.carry = false;
}

void sub_1BF0()
{
  _bx = 0;
  _ah = 0x0b;
  _interrupt(0x10);
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_1C12;
  if (memory[adr(_ds, 0x553)] == 0)
    goto loc_1C12;
  sub_528B();
  *(WORD*)&memory[adr(_ds, 0x579)] = 0x98;
  memory[adr(_ds, 0x57B)] = 0x5f;
loc_1C12:
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  *(WORD*)&memory[adr(_ds, 0x1839)] = 0;
  sub_1C67();
  sub_5B21();
  sub_1D31();
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 0)
    goto loc_1C49;
  if (memory[adr(_ds, 0x553)] == 0)
    goto loc_1C46;
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_1C41;
  sub_5313();
  goto loc_1C49;
loc_1C41:
  sub_38B0();
  goto loc_1C49;
loc_1C46:
  sub_1D76();
loc_1C49:
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 7)
    goto loc_1C5A;
  _ax = 0xaaaa;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 2)
    goto loc_1C5D;
loc_1C5A:
  _ax = 0x5555;
loc_1C5D:
  *(WORD*)&memory[adr(_ds, 0x1839)] = _ax;
  sub_1C67();
  sub_5B21();
}

void sub_1C67()
{
  nullsub_2();
  *(WORD*)&memory[adr(_ds, 0x1835)] = 1;
  memory[adr(_ds, 0x1837)] = 8;
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = memory[adr(_ds, 0x57B)];
  _cx = (_cx + 0x0c) & 0xfff0;
  _dl += 0x08;
  memory[adr(_ds, 0x1838)] = 0;
loc_1C8C:
  sub_5897();
  *(WORD*)&memory[adr(_ds, 0x1832)] = _cx;
  memory[adr(_ds, 0x1834)] = _dl;
  sub_2CB0();
  _di = _ax;
  _bl = memory[adr(_ds, 0x1837)];
loc_1CA0:
  _ax = *(WORD*)&memory[adr(_ds, 0x1839)];
  _cx = (*(WORD*)&memory[adr(_ds, 0x1835)]) >> 3;
  _rep_stosw<MemB800, DirForward>();
  _cx = ((*(WORD*)&memory[adr(_ds, 0x1835)]) >> 2) & 0xfe;
  _di = (_di - _cx) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_1CCA;
  _di += 0x50;
loc_1CCA:
  _bl -= 1;
  if (_bl != 0)
    goto loc_1CA0;
  if (memory[adr(_ds, 0x1838)] != 0x0f)
    goto loc_1CD6;
  return;
loc_1CD6:
  *(WORD*)&memory[adr(_ds, 0x1835)] += 0x20;
  memory[adr(_ds, 0x1837)] += 0x10;
  _cx = *(WORD*)&memory[adr(_ds, 0x1832)];
  _dl = memory[adr(_ds, 0x1834)];
  flags.carry = _cx < 0x10;
  _cx -= 0x10;
  if (!flags.carry)
    goto loc_1CF4;
  _cx = 0;
  memory[adr(_ds, 0x1838)] |= 1;
loc_1CF4:
  _ax = (*(WORD*)&memory[adr(_ds, 0x1835)]) + _cx;
  if (_ax < 0x0140)
    goto loc_1D0B;
  _ax = 0x0140 - _cx;
  *(WORD*)&memory[adr(_ds, 0x1835)] = _ax;
  memory[adr(_ds, 0x1838)] |= 2;
loc_1D0B:
  flags.carry = _dl < 0x08;
  _dl -= 0x08;
  if (!flags.carry)
    goto loc_1D17;
  _dl = 0;
  memory[adr(_ds, 0x1838)] |= 4;
loc_1D17:
  _al = memory[adr(_ds, 0x1837)];
  flags.carry = (_al + _dl) >= 0x100;
  _al += _dl;
  if (flags.carry)
    goto loc_1D22;
  if (_al < 0xc8)
    goto loc_1C8C;
loc_1D22:
  _al = 0xc8 - _dl;
  memory[adr(_ds, 0x1837)] = _al;
  memory[adr(_ds, 0x1838)] |= 8;
  goto loc_1C8C;
}

void sub_1D31()
{
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_1D48;
  _ah = 0x0b;
  _bh = 0x01;
  _si = *(WORD*)&memory[adr(_ds, 0x4)];
  _bl = memory[adr(_ds, _si + 6227)];
  _interrupt(0x10);
  goto loc_1D67;
loc_1D48:
  _si = *(WORD*)&memory[adr(_ds, 0x4)];
  _bl = 0x01;
  _bh = memory[adr(_ds, _si + 6203)];
  sub_1D6E();
  _bl = 0x02;
  _bh = memory[adr(_ds, _si + 6211)];
  sub_1D6E();
  _bl = 0x03;
  _bh = memory[adr(_ds, _si + 6219)];
  sub_1D6E();
loc_1D67:
  _ah = 0x0b;
  _bx = 0;
  _interrupt(0x10);
}

void sub_1D6E()
{
  _ax = 0x1000;
  _push(_si);
  _interrupt(0x10);
  _si = _pop();
}

void sub_1D76()
{
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_1D81;
  sub_6040();
  return;
loc_1D81:
  sub_57D5();
  _ax = 0x185b;
  if (memory[adr(_ds, 0x552)] == 0)
    goto loc_1DC6;
  _bx = *(WORD*)&memory[adr(_ds, 0x1C30)];
  *(WORD*)&memory[adr(_ds, 0x1C30)] += 2;
  _bx &= 0x0006;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 7206)];
  if (memory[adr(_ds, 0x1F80)] == 0)
    goto loc_1DAA;
  memory[adr(_ds, 0x1F80)] -= 1;
loc_1DAA:
  if (memory[adr(_ds, 0x552)] != 0xdd)
    goto loc_1DC6;
  if (*(WORD*)&memory[adr(_ds, 0x8)] == 0)
    goto loc_1DC6;
  if (memory[adr(_ds, 0x1F80)] < 1)
    goto loc_1DC6;
  sub_5BE0();
  sub_5B21();
  return;
loc_1DC6:
  *(WORD*)&memory[adr(_ds, 0x1C2E)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x1C1B)] = 32896;
  memory[adr(_ds, 0x1C1D)] = 0x1c;
loc_1DD4:
  sub_1E17();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x1830)] = _dx;
loc_1DDF:
  sub_57E4();
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x1830)])
    goto loc_1DDF;
  if (memory[adr(_ds, 0x1C1D)] > 0x14)
    goto loc_1E02;
  _bh = 0;
  _bl = (memory[adr(_ds, 0x1C1D)]) & 0x06;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 7198)];
  goto loc_1E0A;
loc_1E02:
  _ax = *(WORD*)&memory[adr(_ds, 0x1C1B)];
  flags.carry = true;
  _ASSERT(0 /* check carry */); _rcr(_al, 1);
  _ah = _al;
loc_1E0A:
  *(WORD*)&memory[adr(_ds, 0x1C1B)] = _ax;
  memory[adr(_ds, 0x1C1D)] -= 1;
  if (memory[adr(_ds, 0x1C1D)] != 0)
    goto loc_1DD4;
  sub_5B21();
}

void sub_1E17()
{
  flags.direction = false;
  _push(_ds);
  _es = _pop();
  _si = *(WORD*)&memory[adr(_ds, 0x1C2E)];
  _di = 0x0e;
  _cx = 0x60;
loc_1E24:
  _lodsw<MemData, DirForward>();
  _ax = _ax & *(WORD*)&memory[adr(_ds, 0x1C1B)];
  _stosw<MemData, DirForward>();
  if (--_cx)
    goto loc_1E24;
  _ax = 0xb800;
  _es = _ax;
  _si = 0x0e;
  _di = 0x0ed0;
  _cx = 0x0c08;
  sub_2D9D();
}

void sub_1E40()
{
  memory[adr(_ds, 0x1CBF)] = 0;
  *(WORD*)&memory[adr(_ds, 0x1CE1)] = 0;
  memory[adr(_ds, 0x1CC0)] = 0;
  memory[adr(_ds, 0x1CC1)] = 0;
  memory[adr(_ds, 0x1CB8)] = 0;
  memory[adr(_ds, 0x1CC8)] = 0xb1;
  sub_5450();
}

void sub_1E63()
{
  _ah = 0;
  _interrupt(0x1a);
  _cx = _dx;
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x1CC9)];
  _ax = ((*(WORD*)&memory[adr(_ds, 0x1CE1)]) & 0x0001) + 0x0001;
  if (_dx >= _ax)
    goto loc_1E7B;
  return;
loc_1E7B:
  sub_13D8();
  if (_al == 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x1CC9)] = _cx;
  *(WORD*)&memory[adr(_ds, 0x1CE1)] += 1;
  if (memory[adr(_ds, 0x1CC1)] == 0)
    goto loc_1EE2;
  memory[adr(_ds, 0x1CC1)] -= 1;
  if (memory[adr(_ds, 0x1CC1)] != 0)
    goto loc_1EC9;
  sub_5B21();
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_1EC2;
  if (*(WORD*)&memory[adr(_ds, 0x4)] == 0)
    goto loc_1EB7;
  memory[adr(_ds, 0x552)] = 0xdd;
  *(WORD*)&memory[adr(_ds, 0x579)] = 0xa0;
  memory[adr(_ds, 0x57B)] = 0x60;
  return;
loc_1EB7:
  if (memory[adr(_ds, 0x1F80)] == 0)
    goto loc_1EC2;
  memory[adr(_ds, 0x1F80)] -= 1;
loc_1EC2:
  sub_20E1();
  sub_1E40();
  return;
loc_1EC9:
  sub_2022();
  _ax = 0x0104;
  _al = _al - memory[adr(_ds, 0x1CC1)];
  if (memory[adr(_ds, 0x1CD0)] == 0xff)
    goto loc_1EDC;
  _ah = 0xff;
loc_1EDC:
  sub_2059();
  goto loc_1FFB;
loc_1EE2:
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_1F0C;
  _dl = memory[adr(_ds, 0x1CB8)];
  if (*(WORD*)&memory[adr(_ds, 0x1CB9)] == 0)
    goto loc_1F02;
  *(WORD*)&memory[adr(_ds, 0x1CB9)] -= 1;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_1F02;
  _dl = 0xff;
loc_1F02:
  memory[adr(_ds, 0x1CD0)] = _dl;
  _ax = *(WORD*)&memory[adr(_ds, 0x1CC6)];
  goto loc_1FAB;
loc_1F0C:
  if (memory[adr(_ds, 0x1CBF)] != 0)
    goto loc_1F75;
  if (memory[adr(_ds, 0x1CC0)] != 0)
    goto loc_1F57;
  if (memory[adr(_ds, 0x1D58)] != 0)
    goto loc_1F3D;
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    return;
  if (memory[adr(_ds, 0x558)] != 0)
    return;
  sub_2DFD();
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  if (_dl < memory[adr(_ds, _bx + 7377)])
    goto loc_1F3D;
  return;
loc_1F3D:
  _al = 0x01;
  *(WORD*)&memory[adr(_ds, 0x59BA)] = 0;
  if (*(WORD*)&memory[adr(_ds, 0x579)] >= 0xa0)
    goto loc_1F4F;
  _al = 0xff;
loc_1F4F:
  memory[adr(_ds, 0x1CD0)] = _al;
  memory[adr(_ds, 0x1CC0)] = 4;
loc_1F57:
  memory[adr(_ds, 0x1CC0)] -= 1;
  if (memory[adr(_ds, 0x1CC0)] != 0)
    goto loc_1F65;
  memory[adr(_ds, 0x1CBF)] = 1;
  goto loc_1F75;
loc_1F65:
  sub_2022();
  _al = memory[adr(_ds, 0x1CC0)];
  _ah = memory[adr(_ds, 0x1CD0)];
  sub_2059();
  goto loc_1FFB;
loc_1F75:
  memory[adr(_ds, 0x1D58)] = 0;
  _ax = *(WORD*)&memory[adr(_ds, 0x1CC6)];
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    goto loc_1FAB;
  if (memory[adr(_ds, 0x558)] != 0)
    goto loc_1FAB;
  sub_2DFD();
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  if (_dl > memory[adr(_ds, _bx + 7385)])
    goto loc_1FAB;
  if (_ax > *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_1FA6;
  memory[adr(_ds, 0x1CD0)] = 1;
  goto loc_1FAB;
loc_1FA6:
  memory[adr(_ds, 0x1CD0)] = 0xff;
loc_1FAB:
  if (memory[adr(_ds, 0x1CD0)] < 1)
    goto loc_1FEF;
  if (memory[adr(_ds, 0x1CD0)] == 1)
    goto loc_1FE2;
  flags.carry = _ax < 0x0008;
  _ax -= 0x0008;
  if (!flags.carry)
    goto loc_1FEF;
  _ax = 0;
loc_1FBB:
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_1FCC;
  if (*(WORD*)&memory[adr(_ds, 0x1CB9)] != 0)
    goto loc_1FEF;
  goto loc_1FDA;
loc_1FCC:
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    goto loc_1FDA;
  if (memory[adr(_ds, 0x558)] == 0)
    goto loc_1FEF;
loc_1FDA:
  memory[adr(_ds, 0x1CC1)] = 4;
  goto loc_1FEF;
loc_1FE2:
  _ax += 0x0008;
  if (_ax < 0x011e)
    goto loc_1FEF;
  _ax = 0x011e;
  goto loc_1FBB;
loc_1FEF:
  *(WORD*)&memory[adr(_ds, 0x1CC6)] = _ax;
  sub_2022();
  *(WORD*)&memory[adr(_ds, 0x1CC4)] = 3844;
loc_1FFB:
  _cx = *(WORD*)&memory[adr(_ds, 0x1CC6)];
  _dl = memory[adr(_ds, 0x1CC8)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x1CCD)] = _ax;
  if (memory[adr(_ds, 0x1CC0)] == 3)
    goto loc_2013;
  sub_20E1();
loc_2013:
  sub_20F5();
  if (flags.carry)
    return;
  _ax = *(WORD*)&memory[adr(_ds, 0x1CCD)];
  *(WORD*)&memory[adr(_ds, 0x1CBD)] = _ax;
  sub_209B();
}

void sub_2022()
{
  _bh = 0;
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_203B;
  memory[adr(_ds, 0x1CCF)] += 1;
  _bl = ((memory[adr(_ds, 0x1CCF)]) & 0x06) | 0x08;
  if (_bl != 0)
    goto loc_2051;
loc_203B:
  memory[adr(_ds, 0x1CCF)] += 2;
  _bl = (memory[adr(_ds, 0x1CCF)]) & 0x02;
  if (memory[adr(_ds, 0x1CD0)] != 1)
    goto loc_2051;
  _bl |= 0x04;
loc_2051:
  _ax = *(WORD*)&memory[adr(_ds, _bx + 5576)];
  *(WORD*)&memory[adr(_ds, 0x1CBB)] = _ax;
}

void sub_2059()
{
  _cx = 0x0f04;
  _cl -= _al;
  *(WORD*)&memory[adr(_ds, 0x1CC4)] = _cx;
  if (_ah == 0xff)
    goto loc_2078;
  _ah = 0;
  _al <<= 1;
  *(WORD*)&memory[adr(_ds, 0x1CBB)] += _ax;
  *(WORD*)&memory[adr(_ds, 0x1CC6)] = 0;
  goto loc_2086;
loc_2078:
  _ah = 0;
  _al = ((_al << 1) << 1) << 1;
  _ax += 0x0120;
  *(WORD*)&memory[adr(_ds, 0x1CC6)] = _ax;
loc_2086:
  _push(_ds);
  _es = _pop();
  _si = *(WORD*)&memory[adr(_ds, 0x1CBB)];
  _di = 0x0e;
  _al = 0x04;
  sub_2D70();
  *(WORD*)&memory[adr(_ds, 0x1CBB)] = 0x0e;
}

void sub_209B()
{
  _cx = *(WORD*)&memory[adr(_ds, 0x1CC4)];
  *(WORD*)&memory[adr(_ds, 0x1CC2)] = _cx;
  _ax = 0xb800;
  if (memory[adr(_ds, 0x1CB8)] != 0)
    goto loc_20BE;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x1CBD)];
  _si = *(WORD*)&memory[adr(_ds, 0x1CBB)];
  _bp = 0x1c40;
  sub_2CCC();
  return;
loc_20BE:
  _push(_ds);
  _ds = _ax;
  _es = _pop();
  _push(_es);
  _push(_ds);
  _si = *(WORD*)&memory[adr(_es, 7357)];
  _di = 0x1c40;
  sub_2DCA();
  _es = _pop();
  _ds = _pop();
  _si = *(WORD*)&memory[adr(_ds, 0x1CBB)];
  _di = *(WORD*)&memory[adr(_ds, 0x1CBD)];
  _cx = *(WORD*)&memory[adr(_ds, 0x1CC4)];
  sub_2D9D();
}

void sub_20E1()
{
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x1CBD)];
  _si = 0x1c40;
  _cx = *(WORD*)&memory[adr(_ds, 0x1CC2)];
  sub_2D9D();
}

void sub_20F5()
{
  if (memory[adr(_ds, 0x1CB8)] != 0)
    goto loc_2134;
  _al = ((memory[adr(_ds, 0x1CBF)]) | memory[adr(_ds, 0x1CC0)]) | memory[adr(_ds, 0x1CC1)];
  if (_al == 0)
    goto loc_2134;
  if (memory[adr(_ds, 0x57B)] < 0xa3)
    goto loc_2134;
  if (memory[adr(_ds, 0x558)] != 0)
    goto loc_2134;
  _ax = (*(WORD*)&memory[adr(_ds, 0x1CC6)]) + 0x20;
  if (_ax < *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_2134;
  flags.carry = _ax < 0x38;
  _ax -= 0x38;
  if (!flags.carry)
    goto loc_212A;
  _ax = 0;
loc_212A:
  if (_ax > *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_2134;
  sub_2136();
  return;
loc_2134:
  flags.carry = false;
}

void sub_2136()
{
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 6)
    goto loc_2149;
  _al = memory[adr(_ds, 0x57B)];
  memory[adr(_ds, 0x1CC8)] = _al;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  *(WORD*)&memory[adr(_ds, 0x1CC6)] = _ax;
loc_2149:
  _ax = ((*(WORD*)&memory[adr(_ds, 0x1CC6)]) + *(WORD*)&memory[adr(_ds, 0x579)]) >> 1;
  if (_ax < 0x0118)
    goto loc_215A;
  _ax = 0x0117;
loc_215A:
  *(WORD*)&memory[adr(_ds, 0x1CC6)] = _ax;
  _bl = 0x01;
  if (_ax > 0xa0)
    goto loc_216E;
  _bl = 0xff;
  _dx = 0xa1 - _ax;
  goto loc_2173;
loc_216E:
  _ax -= 0x9f;
  _dx = _ax;
loc_2173:
  memory[adr(_ds, 0x1CB8)] = _bl;
  memory[adr(_ds, 0x1CBF)] = 1;
  memory[adr(_ds, 0x1CC1)] = 0;
  _cl = 0x03;
  _dx >>= _cl;
  *(WORD*)&memory[adr(_ds, 0x1CB9)] = _dx;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 6)
    goto loc_21BD;
  sub_11E3();
  _al = memory[adr(_ds, 0x1CB8)];
  _push(_ax);
  memory[adr(_ds, 0x1CB8)] = 0;
  *(WORD*)&memory[adr(_ds, 0x1CC4)] = 3844;
  _ax = *(WORD*)&memory[adr(_ds, 0x15C8)];
  *(WORD*)&memory[adr(_ds, 0x1CBB)] = _ax;
  _cx = *(WORD*)&memory[adr(_ds, 0x1CC6)];
  _dl = memory[adr(_ds, 0x1CC8)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x1CBD)] = _ax;
  sub_209B();
  _ax = _pop();
  memory[adr(_ds, 0x1CB8)] = _al;
loc_21BD:
  sub_20E1();
  sub_11E3();
  _ax = 0x0000;
  if (*(WORD*)&memory[adr(_ds, 0x579)] >= 0xa0)
    goto loc_21D1;
  _ax = 0x0122;
loc_21D1:
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 0)
    goto loc_21DE;
  sub_70D();
loc_21DE:
  flags.carry = true;
}

void sub_21E0()
{
  _al = ((memory[adr(_ds, 0x1CBF)]) | memory[adr(_ds, 0x1CC0)]) | memory[adr(_ds, 0x1CC1)];
  if (_al == 0)
    goto loc_2209;
  _ax = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dl = memory[adr(_ds, 0x327F)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x1CC6)];
  _dh = memory[adr(_ds, 0x1CC8)];
  _di = 0x20;
  _cx = 0x0f1e;
  sub_2E29();
  return;
loc_2209:
  flags.carry = false;
}

void sub_2210()
{
  memory[adr(_ds, 0x1D59)] = 0;
}

void sub_2216()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x1D5A)])
    goto loc_2221;
  return;
loc_2221:
  _cx = _dx;
  sub_13D8();
  if (_al == 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x1D5A)] = _cx;
  sub_22F7();
  if (flags.carry)
    return;
  if (memory[adr(_ds, 0x1D59)] != 0)
    goto loc_226D;
  if (memory[adr(_ds, 0x57B)] == 0x86)
    goto loc_224E;
  if (memory[adr(_ds, 0x57B)] == 0x8e)
    goto loc_224E;
  sub_2DFD();
  if (_dl > 0x05)
    return;
loc_224E:
  sub_15D0();
  _dl += 0x03;
  memory[adr(_ds, 0x1D5E)] = _dl;
  sub_2DFD();
  _dx &= 0x0007;
  _cx = (_cx + _dx) + 0x0006;
  *(WORD*)&memory[adr(_ds, 0x1D5C)] = _cx;
  memory[adr(_ds, 0x1D59)] = 0x1b;
loc_226D:
  memory[adr(_ds, 0x1D59)] -= 1;
  _cx = *(WORD*)&memory[adr(_ds, 0x1D5C)];
  _dl = memory[adr(_ds, 0x1D5E)];
  if (memory[adr(_ds, 0x1D59)] <= 0x0d)
    goto loc_2291;
  _dl = (_dl + memory[adr(_ds, 0x1D59)]) - 0x0f;
  _bx = 0x1b02;
  _bh = _bh - memory[adr(_ds, 0x1D59)];
  goto loc_229F;
loc_2291:
  _dl = (_dl + 0x0c) - memory[adr(_ds, 0x1D59)];
  _bx = 0x0002;
  _bh = _bh + memory[adr(_ds, 0x1D59)];
loc_229F:
  *(WORD*)&memory[adr(_ds, 0x1D64)] = _bx;
  memory[adr(_ds, 0x1D5F)] = _dl;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x1D62)] = _ax;
  sub_22DC();
  sub_22F7();
  if (flags.carry)
    return;
  if (memory[adr(_ds, 0x1D59)] != 0)
    goto loc_22BD;
  return;
loc_22BD:
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x1D62)];
  _si = 0x1cf0;
  *(WORD*)&memory[adr(_ds, 0x1D60)] = _di;
  _cx = *(WORD*)&memory[adr(_ds, 0x1D64)];
  *(WORD*)&memory[adr(_ds, 0x1D66)] = _cx;
  _bp = 0x1d24;
  sub_2CCC();
}

void sub_22DC()
{
  if (memory[adr(_ds, 0x1D59)] == 0x1a)
    return;
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x1D60)];
  _si = 0x1d24;
  _cx = *(WORD*)&memory[adr(_ds, 0x1D66)];
  sub_2D9D();
}

void sub_22F7()
{
  if (memory[adr(_ds, 0x1D59)] != 0)
    goto loc_2300;
  flags.carry = false;
  return;
loc_2300:
  _cx = *(WORD*)&memory[adr(_ds, 0x1D64)];
  _xchg(_ch, _cl);
  _ax = *(WORD*)&memory[adr(_ds, 0x1D5C)];
  _dl = memory[adr(_ds, 0x1D5F)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _ch = 0x0e;
  sub_2E29();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x1D58)] = 1;
}

void sub_2330()
{
  *(WORD*)&memory[adr(_ds, 0x1F6C)] = 0;
  _ax = 0;
  _dl = 0x01;
  if (*(WORD*)&memory[adr(_ds, 0x579)] > 0xa0)
    goto loc_2347;
  _ax = 0x012c;
  _dl = 0xff;
loc_2347:
  *(WORD*)&memory[adr(_ds, 0x1F30)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x1F32)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x1F34)] = _ax;
  memory[adr(_ds, 0x1F3C)] = _dl;
  memory[adr(_ds, 0x1F3D)] = _dl;
  memory[adr(_ds, 0x1F3E)] = _dl;
  memory[adr(_ds, 0x1F48)] = 1;
  memory[adr(_ds, 0x1F49)] = 1;
  memory[adr(_ds, 0x1F4A)] = 1;
  memory[adr(_ds, 0x1F50)] = 0;
  memory[adr(_ds, 0x1F51)] = 0;
  memory[adr(_ds, 0x1F52)] = 0;
}

void sub_237B()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x1F65)])
    goto loc_2386;
  return;
loc_2386:
  *(WORD*)&memory[adr(_ds, 0x1F65)] = _dx;
  if (memory[adr(_ds, 0x55A)] != 0)
    return;
  _bx = (*(WORD*)&memory[adr(_ds, 0x1F6C)]) + 1;
  if (_bx < 0x0003)
    goto loc_239E;
  _bx = 0x0000;
loc_239E:
  *(WORD*)&memory[adr(_ds, 0x1F6C)] = _bx;
  sub_265E();
  if (flags.carry)
    return;
  sub_2567();
  if (flags.carry)
    return;
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  if (memory[adr(_ds, _bx + 8016)] == 0)
    goto loc_23EB;
  _ah = 0;
  _interrupt(0x1a);
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _bl <<= 1;
  _dx = _dx - *(WORD*)&memory[adr(_ds, _bx + 8019)];
  if (_dx < 0x36)
    return;
  _dl = 0x01;
  _ax = 0x0000;
  if (*(WORD*)&memory[adr(_ds, 0x579)] > 0xa0)
    goto loc_23DC;
  _ax = 0x012c;
  _dl = 0xff;
loc_23DC:
  *(WORD*)&memory[adr(_ds, _bx + 7984)] = _ax;
  _bl >>= 1;
  memory[adr(_ds, _bx + 8016)] = 0;
  memory[adr(_ds, _bx + 7996)] = _dl;
loc_23EB:
  _dl = memory[adr(_ds, _bx + 7996)];
  memory[adr(_ds, _bx + 7999)] = _dl;
  if (memory[adr(_ds, 0x1664)] == 0)
    goto loc_2403;
  *(WORD*)&memory[adr(_ds, 0x1F69)] = 0x0c;
  goto loc_2418;
loc_2403:
  _ax = 0x0008;
  if (memory[adr(_ds, 0x57B)] <= 0x60)
    goto loc_240F;
  _al >>= 1;
loc_240F:
  *(WORD*)&memory[adr(_ds, 0x1F69)] = _ax;
  if (_bx != *(WORD*)&memory[adr(_ds, 0x52F)])
    goto loc_2425;
loc_2418:
  if (memory[adr(_ds, _bx + 7996)] != 0)
    goto loc_2425;
  sub_2DFD();
  goto loc_248A;
loc_2425:
  if (memory[adr(_ds, 0x55C)] == 0)
    goto loc_2466;
  _al = memory[adr(_ds, _bx + 7990)];
  if (_al > memory[adr(_ds, 0x57B)])
    goto loc_2466;
  _al += 0x10;
  if (_al < memory[adr(_ds, 0x57B)])
    goto loc_2466;
  sub_2DFD();
  _si = *(WORD*)&memory[adr(_ds, 0x8)];
  if (_dl > memory[adr(_ds, _si + 8046)])
    goto loc_2466;
  *(WORD*)&memory[adr(_ds, 0x1F69)] = 0x0c;
  _al = 0x01;
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 7984)];
  _bl >>= 1;
  if (_cx < *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_2492;
  _al = 0xff;
  goto loc_2492;
loc_2466:
  _cl = 0x18;
  if (memory[adr(_ds, 0x57B)] <= 0x60)
    goto loc_247A;
  _cl = 0x28;
  if (memory[adr(_ds, _bx + 7996)] != 0)
    goto loc_247A;
  _cl = 0x10;
loc_247A:
  sub_2DFD();
  if (_dl > _cl)
    goto loc_2496;
  _al = 0x00;
  if (memory[adr(_ds, _bx + 7996)] != 0)
    goto loc_2492;
loc_248A:
  _al = _dl & 0x01;
  if (_al != 0)
    goto loc_2492;
  _al = 0xff;
loc_2492:
  memory[adr(_ds, _bx + 7996)] = _al;
loc_2496:
  _dl = memory[adr(_ds, _bx + 7996)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 7984)];
  if (_dl < 0x01)
    goto loc_24C2;
  if (_dl != 0x01)
    goto loc_24B8;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x1F69)];
  if (_ax < 0x012f)
    goto loc_24C2;
  _ax = 0x012e;
  _dl = 0xff;
  goto loc_24C2;
loc_24B8:
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x1F69)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x1F69)];
  if (!flags.carry)
    goto loc_24C2;
  _ax = 0;
  _dl = 0x01;
loc_24C2:
  *(WORD*)&memory[adr(_ds, _bx + 7984)] = _ax;
  _bl >>= 1;
  memory[adr(_ds, _bx + 7996)] = _dl;
  _dl = memory[adr(_ds, _bx + 7990)];
  _cx = _ax;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x1F4B)] = _ax;
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  if (memory[adr(_ds, _bx + 8008)] != 0)
    goto loc_24F0;
  _al = (memory[adr(_ds, _bx + 7996)]) | memory[adr(_ds, _bx + 7999)];
  if (_al == 0)
    goto loc_24F0;
  sub_254D();
loc_24F0:
  sub_265E();
  if (flags.carry)
    return;
  sub_2567();
  if (!flags.carry)
    goto loc_24FB;
  return;
loc_24FB:
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  memory[adr(_ds, _bx + 8008)] = 0;
  if (memory[adr(_ds, _bx + 7996)] != 0)
    goto loc_2518;
  if (memory[adr(_ds, _bx + 7999)] == 0)
    return;
  _si = 0x1e30;
  goto loc_2533;
loc_2518:
  _si = 0x1e50;
  memory[adr(_ds, _bx + 8013)] += 1;
  if (memory[adr(_ds, _bx + 8013)] & 1)
    goto loc_2529;
  _si += 0x20;
loc_2529:
  if (memory[adr(_ds, _bx + 7996)] == 1)
    goto loc_2533;
  _si += 0x40;
loc_2533:
  _bl <<= 1;
  _di = *(WORD*)&memory[adr(_ds, 0x1F4B)];
  *(WORD*)&memory[adr(_ds, _bx + 8002)] = _di;
  _ax = 0xb800;
  _es = _ax;
  _bp = *(WORD*)&memory[adr(_ds, _bx + 8025)];
  _cx = 0x0802;
  sub_2D35();
}

void sub_254D()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _bl <<= 1;
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, _bx + 8002)];
  _si = *(WORD*)&memory[adr(_ds, _bx + 8025)];
  _cx = 0x0802;
  sub_2D9D();
}

void sub_2567()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _dl = memory[adr(_ds, _bx + 7990)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 7984)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e08;
  sub_2E29();
  if (flags.carry)
    goto loc_258E;
  return;
loc_258E:
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  if (memory[adr(_ds, _bx + 8016)] != 0)
    goto loc_260C;
  if (memory[adr(_ds, 0x57C)] < 0x26)
    goto loc_260C;
  if (memory[adr(_ds, 0x55C)] == 0)
    goto loc_260E;
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x55B)] = 0x11;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x56E)] = 0;
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _bl <<= 1;
  _di = *(WORD*)&memory[adr(_ds, _bx + 8002)];
  if (*(WORD*)&memory[adr(_ds, _bx + 7984)] < 0x10)
    goto loc_25CF;
  _di -= 0x0004;
loc_25CF:
  *(WORD*)&memory[adr(_ds, 0x1F67)] = _di;
  _ax = 0xb800;
  _es = _ax;
  _si = 0x1d70;
  _bp = 0x0e;
  _cx = 0x0806;
  sub_2CCC();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x1F65)] = _dx;
loc_25EC:
  sub_5A90();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x1F65)];
  if (_dx < 0x0008)
    goto loc_25EC;
  sub_5B21();
  _di = *(WORD*)&memory[adr(_ds, 0x1F67)];
  _si = 0x0e;
  _cx = 0x0806;
  sub_2D9D();
loc_260C:
  flags.carry = true;
  return;
loc_260E:
  _ah = 0;
  _interrupt(0x1a);
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  memory[adr(_ds, _bx + 8016)] = 1;
  memory[adr(_ds, _bx + 7996)] = 1;
  _bl <<= 1;
  *(WORD*)&memory[adr(_ds, _bx + 8019)] = _dx;
  sub_11E3();
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _bl <<= 1;
  _si = *(WORD*)&memory[adr(_ds, _bx + 8031)];
  _di = *(WORD*)&memory[adr(_ds, _bx + 8002)];
  _ax = 0xb800;
  _es = _ax;
  _bp = 0x0e;
  _cx = 0x0802;
  sub_2CCC();
  sub_1124();
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _al = memory[adr(_ds, _bx + 7993)];
  sub_2706();
  _ax = 0x03e8;
  _bx = 0x02ee;
  sub_593B();
  flags.carry = true;
}

void sub_265E()
{
  if (memory[adr(_ds, 0x1673)] != 0)
    goto loc_2667;
  flags.carry = false;
  return;
loc_2667:
  _bx = *(WORD*)&memory[adr(_ds, 0x1F6C)];
  _dl = memory[adr(_ds, _bx + 7990)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 7984)];
  _si = 0x10;
  _di = _si;
  _bx = *(WORD*)&memory[adr(_ds, 0x1671)];
  _dh = memory[adr(_ds, 0x1673)];
  _cx = 0x0c08;
  sub_2E29();
}

void sub_2690()
{
  _push(_ds);
  _es = _pop();
  _cx = 0x0007;
  _si = 0x1f82;
loc_2698:
  _lodsb<MemData, DirAuto>();
  _bx = 0x0007 - _cx;
  if (--_cx && _al == memory[adr(_ds, _bx + 8073)])
    goto loc_2698;
  if (_al > memory[adr(_ds, _bx + 8073)])
    goto loc_26A7;
  return;
loc_26A7:
  _si = 0x1f82;
  _di = 0x1f89;
  _cx = 0x0007;
  _rep_movsb<MemData, MemData, DirAuto>();
}

void sub_26B3()
{
  _al = memory[adr(_ds, 0x1F80)];
  if (_al != memory[adr(_ds, 0x1F81)])
    goto loc_26BD;
  return;
loc_26BD:
  memory[adr(_ds, 0x1F81)] = _al;
  _ah = 0;
  _cl = 0x04;
  _ax = (_ax << _cl) + 0x2720;
  _si = _ax;
  _ax = 0xb800;
  _es = _ax;
  _di = 0x1260;
  _cx = 0x0801;
  sub_2D9D();
}

void sub_26DA()
{
  _di = 0x1f82;
  sub_26E8();
}

void sub_26E1()
{
  _di = 0x1f89;
  sub_26E8();
}

void sub_26E8()
{
  _push(_ds);
  _es = _pop();
  _cx = 0x0007;
  _al = 0;
  _rep_stosb<MemData, DirAuto>();
}

void sub_26F2()
{
  _bx = 0x1f89;
  _di = 0x12ca;
  sub_2739();
}

void sub_26FC()
{
  _bx = 0x1f82;
  _di = 0x143c;
  sub_2739();
}

void sub_2706()
{
  _cx = 0x0006;
loc_2709:
  _bx = _cx;
  _ah = 0x00;
  _al = _al + memory[adr(_ds, _bx + 8065)];
  _ASSERT(0 /* check carry */); _aaa();
  memory[adr(_ds, _bx + 8065)] = _al;
  _al = _ah;
  if (--_cx)
    goto loc_2709;
  sub_26FC();
}

void sub_271E()
{
  _push(_cx);
  _push(_ax);
  _push(_bx);
  flags.carry = false;
  _pushf();
  _cx = 0x0007;
loc_2726:
  _popf();
  _bx = _cx - 1;
  _al = (memory[adr(_ds, _bx + _di)]) + memory[adr(_ds, _bx + _si)] + flags.carry; _ASSERT(0 /* add with carry */);
  _ASSERT(0 /* check carry */); _aaa();
  memory[adr(_ds, _bx + _di)] = _al;
  _pushf();
  if (--_cx)
    goto loc_2726;
  _popf();
  _bx = _pop();
  _ax = _pop();
  _cx = _pop();
}

void sub_2739()
{
  _ax = 0xb800;
  _es = _ax;
  *(WORD*)&memory[adr(_ds, 0x1F90)] = _di;
  *(WORD*)&memory[adr(_ds, 0x1F93)] = _bx;
  memory[adr(_ds, 0x1F92)] = 0;
loc_274B:
  _bx = *(WORD*)&memory[adr(_ds, 0x1F93)];
  _al = memory[adr(_ds, _bx)];
  _ah = 0;
  _cl = 0x04;
  _ax = (_ax << _cl) + 0x2720;
  _si = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x1F90)];
  _cx = 0x0801;
  sub_2D9D();
  *(WORD*)&memory[adr(_ds, 0x1F90)] += 2;
  *(WORD*)&memory[adr(_ds, 0x1F93)] += 1;
  memory[adr(_ds, 0x1F92)] += 1;
  if (memory[adr(_ds, 0x1F92)] == 7)
    return;
  if (memory[adr(_ds, 0x1F92)] != 3)
    goto loc_274B;
  *(WORD*)&memory[adr(_ds, 0x1F90)] += 2;
  goto loc_274B;
}

void sub_2790()
{
  _ax = 0xb800;
  _es = _ax;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 2)
    goto loc_27EE;
  flags.direction = false;
  _di = 0;
  _ax = 0xaaaa;
  _cx = 0x50;
  _rep_stosw<MemB800, DirForward>();
  _di = 0x2000;
  _cx = 0x50;
  _rep_stosw<MemB800, DirForward>();
  *(WORD*)&memory[adr(_ds, 0x2654)] = 0;
loc_27B5:
  sub_2DFD();
  _dx &= 0x18;
  if (_dl == memory[adr(_ds, 0x2653)])
    goto loc_27B5;
  memory[adr(_ds, 0x2653)] = _dl;
  _bx = *(WORD*)&memory[adr(_ds, 0x2654)];
  memory[adr(_ds, _bx + 9814)] = _dl;
  _dx += 0x2020;
  _si = _dx;
  _di = (_bx << 1) + 0xa0;
  _cx = 0x0401;
  sub_2D9D();
  *(WORD*)&memory[adr(_ds, 0x2654)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x2654)] < 0x28)
    goto loc_27B5;
  return;
loc_27EE:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 7)
    goto loc_27F9;
  sub_300F();
  return;
loc_27F9:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 6)
    goto loc_283E;
  _ax = 0;
  sub_29A0();
  _bx = 0x2570;
  _ax = 0x064a;
  sub_2B24();
  *(WORD*)&memory[adr(_ds, 0x2650)] = 0x48;
  memory[adr(_ds, 0x2652)] = 0x38;
  _ax = 0x0dd2;
  sub_2958();
  _ax = 0x0df6;
  sub_2970();
  _si = 0x1fa0;
  _di = 0x067e;
  _cx = 0x1002;
  sub_2D9D();
  _bx = 0x2344;
  _ax = 0x0b84;
  sub_2B24();
  sub_4B47();
  return;
loc_283E:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 5)
    goto loc_288D;
  _ax = 0x0640;
  sub_29A0();
  _bx = 0x2570;
  _ax = 0x0cb6;
  sub_2B24();
  *(WORD*)&memory[adr(_ds, 0x2650)] = 0xf8;
  memory[adr(_ds, 0x2652)] = 0x60;
  _ax = 0x140e;
  sub_2958();
  _ax = 0x1434;
  sub_2970();
  _ax = 0x143e;
  sub_2970();
  _ax = 0x16a0;
  sub_2988();
  _bx = 0x2344;
  _ax = 0x1184;
  sub_2B24();
  _si = 0x1fe0;
  _di = 0x0dd6;
  _cx = 0x1002;
  sub_2D9D();
  return;
loc_288D:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 4)
    goto loc_28BE;
  _ax = 0x0640;
  sub_29A0();
  _bx = 0x2570;
  _ax = 0x0cba;
  sub_2B24();
  *(WORD*)&memory[adr(_ds, 0x2650)] = 264;
  memory[adr(_ds, 0x2652)] = 0x60;
  _ax = 0x1439;
  sub_2958();
  _ax = 0x16c0;
  sub_2945();
  sub_3F9E();
  return;
loc_28BE:
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 3)
    goto loc_2909;
  _ax = 0x0640;
  sub_29A0();
  _bx = 0x2570;
  _ax = 0x0c90;
  sub_2B24();
  *(WORD*)&memory[adr(_ds, 0x2650)] = 0x60;
  memory[adr(_ds, 0x2652)] = 0x60;
  _ax = 0x140c;
  sub_2958();
  _ax = 0x1418;
  sub_2970();
  _bx = 0x2344;
  _ax = 0x1184;
  sub_2B24();
  _bx = 0x2344;
  _ax = 0x11a2;
  sub_2B24();
  _bx = 0x2624;
  _ax = 0;
  sub_2B24();
  sub_3BDB();
  return;
loc_2909:
  _ax = 0x0640;
  sub_29A0();
  _bx = 0x2570;
  _ax = 0x0ca0;
  sub_2B24();
  *(WORD*)&memory[adr(_ds, 0x2650)] = 0xa0;
  memory[adr(_ds, 0x2652)] = 0x60;
  _ax = 0x1406;
  sub_2958();
  _bx = 0x2344;
  _ax = 0x11c4;
  sub_2B24();
  _ax = 0x1422;
  sub_2970();
  _ax = 0x1690;
  sub_2988();
  _ax = 0x16b6;
  sub_2945();
}

void sub_2945()
{
  *(WORD*)&memory[adr(_ds, 0x2634)] = _ax;
  _bx = 0x2384;
  sub_2B24();
  _ax = *(WORD*)&memory[adr(_ds, 0x2634)];
  _bx = 0x238c;
  sub_2B24();
}

void sub_2958()
{
  *(WORD*)&memory[adr(_ds, 0x2634)] = _ax;
  _si = 0x0008;
loc_295E:
  _ax = *(WORD*)&memory[adr(_ds, 0x2634)];
  _bx = *(WORD*)&memory[adr(_ds, _si + 9780)];
  _push(_si);
  sub_2B24();
  _si = _pop();
  _si -= 0x0002;
  if (_si != 0)
    goto loc_295E;
}

void sub_2970()
{
  *(WORD*)&memory[adr(_ds, 0x2634)] = _ax;
  _si = 0x0a;
loc_2976:
  _ax = *(WORD*)&memory[adr(_ds, 0x2634)];
  _bx = *(WORD*)&memory[adr(_ds, _si + 9788)];
  _push(_si);
  sub_2B24();
  _si = _pop();
  _si -= 0x0002;
  if (_si != 0)
    goto loc_2976;
}

void sub_2988()
{
  *(WORD*)&memory[adr(_ds, 0x2634)] = _ax;
  _si = 0x0008;
loc_298E:
  _ax = *(WORD*)&memory[adr(_ds, 0x2634)];
  _bx = *(WORD*)&memory[adr(_ds, _si + 9798)];
  _push(_si);
  sub_2B24();
  _si = _pop();
  _si -= 0x0002;
  if (_si != 0)
    goto loc_298E;
}

void sub_29A0()
{
  *(WORD*)&memory[adr(_ds, 0x267E)] = _ax;
  _bx = 0x251c;
  sub_2B24();
  _ax = 0;
  flags.direction = false;
  _di = (*(WORD*)&memory[adr(_ds, 0x267E)]) + 0x0284;
  _cx = 0x24;
  _rep_stosw<MemB800, DirForward>();
  _di = (*(WORD*)&memory[adr(_ds, 0x267E)]) + 0x1184;
  _cx = 0x24;
  _rep_stosw<MemB800, DirForward>();
  _di = (*(WORD*)&memory[adr(_ds, 0x267E)]) + 0x2284;
  _al = 0x2a;
  sub_29E1();
  _di = (*(WORD*)&memory[adr(_ds, 0x267E)]) + 0x22cb;
  _al = 0xa8;
  sub_29E1();
}

void sub_29E1()
{
  _cx = 0x5f;
loc_29E4:
  _videoWrite8(_esAssume(0xb800), _di, _al);
  _di = _di ^ 0x2000;
  if (_di & 0x2000)
    goto loc_29F4;
  _di += 0x50;
loc_29F4:
  if (--_cx)
    goto loc_29E4;
}

void sub_2A00()
{
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  _di = 0;
  _ax = 0xaaaa;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
  _di = 0x2000;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
  sub_2B9E();
  _bx = 0x28a0;
  _ax = 0;
  sub_2B24();
  sub_2A68();
  sub_2C84();
  sub_2B8B();
  sub_2A80();
}

void sub_2A30()
{
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  _di = 0;
  _ax = 0xaaaa;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
  _di = 0x2000;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
  sub_2B9E();
  _bx = 0x28a0;
  _ax = 0;
  sub_2B24();
  sub_2A68();
  _ax = *(WORD*)&memory[adr(_ds, 0x8)];
  _push(_ax);
  *(WORD*)&memory[adr(_ds, 0x8)] = 1;
  sub_2C84();
  _ax = _pop();
  *(WORD*)&memory[adr(_ds, 0x8)] = _ax;
}

void sub_2A68()
{
  _bx = (*(WORD*)&memory[adr(_ds, 0x6DF8)]) & 0x0003;
  _bl <<= 1;
  _si = *(WORD*)&memory[adr(_ds, _bx + 10961)];
  _di = 0x1902;
  _cx = 0x0801;
  sub_2D9D();
}

void sub_2A80()
{
  _bx = 0x0f;
loc_2A83:
  memory[adr(_ds, _bx + 4117)] = 0;
  _bx -= 1;
  if (_bx != 0)
    goto loc_2A83;
  _di = 0x0140;
  _bh = 0x80;
  *(WORD*)&memory[adr(_ds, 0x2ACA)] = 0;
  sub_2AC6();
  _di = 0x0640;
  _bh = 0x30;
  *(WORD*)&memory[adr(_ds, 0x2ACA)] = 5;
  sub_2AC6();
  _di = 0x0b40;
  _bh = 0x00;
  *(WORD*)&memory[adr(_ds, 0x2ACA)] = 0x0a;
  sub_2AC6();
  memory[adr(_ds, 0x525)] = 0x10;
  *(WORD*)&memory[adr(_ds, 0x52F)] = 0;
  memory[adr(_ds, 0x531)] = 1;
}

void sub_2AC6()
{
  memory[adr(_ds, 0x2AC9)] = _bh;
  memory[adr(_ds, 0x2AC4)] = 0;
loc_2ACF:
  _push(_di);
  _push(_es);
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl = memory[adr(_ds, _bx + 10938)];
  _bh = memory[adr(_ds, 0x2AC9)];
  _ax = SEG_DATA;
  _es = _ax;
  _di = 0x04d7;
  sub_67D();
  _es = _pop();
  _di = _pop();
  _push(_di);
  _si = 0x04d7;
  _cx = 0x1002;
  sub_2D9D();
  _bh = 0;
  _bl = memory[adr(_ds, 0x2AC4)];
  _cl = _bl;
  _bl >>= 2;
  _cl = ((~_cl) & 0x03) << 1;
  _al = (memory[adr(_ds, 0x540)]) << _cl;
  _si = *(WORD*)&memory[adr(_ds, 0x2ACA)];
  memory[adr(_ds, _bx + _si + 4118)] |= _al;
  _di = _pop();
  _di += 0x0004;
  memory[adr(_ds, 0x2AC4)] += 1;
  if (memory[adr(_ds, 0x2AC4)] < 0x14)
    goto loc_2ACF;
}

void sub_2B24()
{
  _cx = *(WORD*)&memory[adr(_ds, _bx)];
  *(WORD*)&memory[adr(_ds, 0x2AC7)] = _cx;
  *(WORD*)&memory[adr(_ds, 0x2ACC)] = _ax;
  _bx += 0x0002;
loc_2B30:
  _si = *(WORD*)&memory[adr(_ds, _bx)];
  if (_si != 0xffff)
    goto loc_2B39;
  return;
loc_2B39:
  _di = (*(WORD*)&memory[adr(_ds, _bx + 2)]) + *(WORD*)&memory[adr(_ds, 0x2ACC)];
  flags.direction = false;
  memory[adr(_ds, 0x2AD0)] = _ch;
  _ch = 0;
  *(WORD*)&memory[adr(_ds, 0x2ACE)] = _cx;
loc_2B4B:
  _cx = *(WORD*)&memory[adr(_ds, 0x2ACE)];
  _rep_movsb<MemB800, MemData, DirForward>();
  _di = (_di - *(WORD*)&memory[adr(_ds, 0x2ACE)]) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_2B62;
  _di += 0x50;
loc_2B62:
  memory[adr(_ds, 0x2AD0)] -= 1;
  if (memory[adr(_ds, 0x2AD0)] != 0)
    goto loc_2B4B;
  _bx += 0x0004;
  _cx = *(WORD*)&memory[adr(_ds, 0x2AC7)];
  goto loc_2B30;
}

void sub_2B71()
{
  memory[adr(_ds, 0x2AC4)] = 4;
loc_2B76:
  _si = 0x2680;
  _cx = 0x1005;
  _push(_di);
  sub_2D9D();
  _di = _pop();
  _di += 0x14;
  memory[adr(_ds, 0x2AC4)] -= 1;
  if (memory[adr(_ds, 0x2AC4)] != 0)
    goto loc_2B76;
}

void sub_2B8B()
{
  _di = 0x03c5;
  sub_2B71();
  _di = 0x08c5;
  sub_2B71();
  _di = 0x0dc5;
  sub_2B71();
}

void sub_2B9E()
{
  *(WORD*)&memory[adr(_ds, 0x2AC2)] = 4158;
loc_2BA4:
  *(WORD*)&memory[adr(_ds, 0x2AC2)] += 2;
  _di = *(WORD*)&memory[adr(_ds, 0x2AC2)];
  if (_di >= 0x1090)
    goto loc_2BD2;
loc_2BB3:
  sub_2DFD();
  _dx &= 0x30;
  if (_dl == memory[adr(_ds, 0x2AC4)])
    goto loc_2BB3;
  memory[adr(_ds, 0x2AC4)] = _dl;
  _dx += 0x2904;
  _si = _dx;
  _cx = 0x0801;
  sub_2D9D();
  goto loc_2BA4;
loc_2BD2:
  _di = 0x1180;
  _ax = 0x5655;
  _cx = 0x0500;
  flags.direction = false;
  _rep_stosw<MemB800, DirForward>();
  _di = 0x3180;
  _cx = 0x0500;
  _rep_stosw<MemB800, DirForward>();
  *(WORD*)&memory[adr(_ds, 0x2AC2)] = 10564;
loc_2BEC:
  memory[adr(_ds, 0x2AC4)] = 9;
loc_2BF1:
  sub_2DFD();
  _dx = (_dx & 0x0776) + 0x12c0;
  _di = _dx;
  _si = *(WORD*)&memory[adr(_ds, 0x2AC2)];
  _cx = 0x0501;
  sub_2D9D();
  memory[adr(_ds, 0x2AC4)] -= 1;
  if (memory[adr(_ds, 0x2AC4)] != 0)
    goto loc_2BF1;
  *(WORD*)&memory[adr(_ds, 0x2AC2)] += 0x0a;
  if (*(WORD*)&memory[adr(_ds, 0x2AC2)] < 10604)
    goto loc_2BEC;
  memory[adr(_ds, 0x2AC4)] = 5;
loc_2C20:
  sub_2DFD();
  _dx = (_dx & 0x3e) + 0x3a98;
  _di = _dx;
  _si = 0x296c;
  _cx = 0x0501;
  sub_2D9D();
  memory[adr(_ds, 0x2AC4)] -= 1;
  if (memory[adr(_ds, 0x2AC4)] != 0)
    goto loc_2C20;
}

void sub_2C3D()
{
  *(WORD*)&memory[adr(_ds, 0x2AC2)] = _di;
  _al = 0x03;
  if (_di < 0x1720)
    goto loc_2C4B;
  _al -= 1;
loc_2C4B:
  memory[adr(_ds, 0x2AC4)] = _al;
  *(WORD*)&memory[adr(_ds, 0x2AC2)] += 480;
  _si = 0x2976;
  _cx = 0x0c05;
  sub_2D9D();
loc_2C5D:
  _di = *(WORD*)&memory[adr(_ds, 0x2AC2)];
  *(WORD*)&memory[adr(_ds, 0x2AC2)] += 320;
  _si = 0x29ee;
  _cx = 0x0804;
  sub_2D9D();
  memory[adr(_ds, 0x2AC4)] -= 1;
  if (memory[adr(_ds, 0x2AC4)] != 0)
    goto loc_2C5D;
  _di = *(WORD*)&memory[adr(_ds, 0x2AC2)];
  _si = 0x2a2e;
  _cx = 0x0b04;
  sub_2D9D();
}

void sub_2C84()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl = memory[adr(_ds, _bx + 10930)];
loc_2C8C:
  *(WORD*)&memory[adr(_ds, 0x2AC5)] = _bx;
  _di = *(WORD*)&memory[adr(_ds, _bx + 10886)];
  if (_di != 0x0000)
    goto loc_2C9A;
  return;
loc_2C9A:
  sub_2C3D();
  _bx = (*(WORD*)&memory[adr(_ds, 0x2AC5)]) + 0x0002;
  goto loc_2C8C;
}

// class CIReturn
void sub_2CB0()
{
  _al = _dl;
  _ah = 0x28;
  _ax = _ah * _al;
  if (!(_dl & 0x01))
    goto loc_2CBE;
  _ax += 0x1fd8;
loc_2CBE:
  _dx = _cx >> 2;
  _ax += _dx;
  _cl = (_cl & 0x03) << 1;
}

void sub_2CCC()
{
  flags.direction = false;
  memory[adr(_ds, 0x2AE0)] = _cl;
  memory[adr(_ds, 0x2AE2)] = _ch;
  _ch = 0;
  _dx = 0x0ff0;
loc_2CDA:
  _cl = memory[adr(_ds, 0x2AE0)];
loc_2CDE:
  _dx = 0x30c0;
  _bx = _videoRead16(_esAssume(0xb800), _di);
  *(WORD*)&memory[adr(_ds, _bp + 0)] = _bx;
  _lodsw<MemData, DirForward>();
  *(WORD*)&memory[adr(_ds, 0x2AE3)] = _ax;
loc_2CEC:
  if (_ah & _dl)
    goto loc_2CF2;
  _ah |= _dl;
loc_2CF2:
  if (_ah & _dh)
    goto loc_2CF8;
  _ah |= _dh;
loc_2CF8:
  if (_al & _dl)
    goto loc_2CFE;
  _al |= _dl;
loc_2CFE:
  if (_al & _dh)
    goto loc_2D04;
  _al |= _dh;
loc_2D04:
  _dx = _dx ^ 0x33cc;
  if (_dh & 0x03)
    goto loc_2CEC;
  _ax = (_ax & _bx) | *(WORD*)&memory[adr(_ds, 0x2AE3)];
  _stosw<MemB800, DirForward>();
  _bp += 0x0002;
  if (--_cx)
    goto loc_2CDE;
  _di = ((_di - *(WORD*)&memory[adr(_ds, 0x2AE0)]) - *(WORD*)&memory[adr(_ds, 0x2AE0)]) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_2D2E;
  _di += 0x50;
loc_2D2E:
  memory[adr(_ds, 0x2AE2)] -= 1;
  if (memory[adr(_ds, 0x2AE2)] != 0)
    goto loc_2CDA;
}

void sub_2D35()
{
  flags.direction = false;
  memory[adr(_ds, 0x2AE0)] = _cl;
  memory[adr(_ds, 0x2AE2)] = _ch;
  _ch = 0;
loc_2D40:
  _cl = memory[adr(_ds, 0x2AE0)];
loc_2D44:
  _bx = _videoRead16(_esAssume(0xb800), _di);
  *(WORD*)&memory[adr(_ds, _bp + 0)] = _bx;
  _lodsw<MemData, DirForward>();
  _ax &= _bx;
  _stosw<MemB800, DirForward>();
  _bp += 0x0002;
  if (--_cx)
    goto loc_2D44;
  _di = ((_di - *(WORD*)&memory[adr(_ds, 0x2AE0)]) - *(WORD*)&memory[adr(_ds, 0x2AE0)]) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_2D69;
  _di += 0x50;
loc_2D69:
  memory[adr(_ds, 0x2AE2)] -= 1;
  if (memory[adr(_ds, 0x2AE2)] != 0)
    goto loc_2D40;
}

void sub_2D70()
{
  flags.direction = false;
  *(WORD*)&memory[adr(_ds, 0x2AE9)] = _si;
  memory[adr(_ds, 0x2AE0)] = _cl;
  memory[adr(_ds, 0x2AE2)] = _ch;
  _al <<= 1;
  memory[adr(_ds, 0x2AEB)] = _al;
  _ch = 0;
loc_2D84:
  _cl = memory[adr(_ds, 0x2AE0)];
  _rep_movsw<MemData, MemData, DirForward>();
  _cl = memory[adr(_ds, 0x2AEB)];
  *(WORD*)&memory[adr(_ds, 0x2AE9)] += _cx;
  _si = *(WORD*)&memory[adr(_ds, 0x2AE9)];
  memory[adr(_ds, 0x2AE2)] -= 1;
  if (memory[adr(_ds, 0x2AE2)] != 0)
    goto loc_2D84;
}

void sub_2D9D()
{
  flags.direction = false;
  memory[adr(_ds, 0x2AE0)] = _cl;
  memory[adr(_ds, 0x2AE2)] = _ch;
  _ch = 0;
loc_2DA8:
  _cl = memory[adr(_ds, 0x2AE0)];
  _rep_movsw<MemB800, MemData, DirForward>();
  _di = ((_di - *(WORD*)&memory[adr(_ds, 0x2AE0)]) - *(WORD*)&memory[adr(_ds, 0x2AE0)]) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_2DC3;
  _di += 0x50;
loc_2DC3:
  memory[adr(_ds, 0x2AE2)] -= 1;
  if (memory[adr(_ds, 0x2AE2)] != 0)
    goto loc_2DA8;
}

void sub_2DCA()
{
  flags.direction = false;
  memory[adr(_es, 10976)] = _cl;
  memory[adr(_es, 10978)] = _ch;
  _ch = 0;
loc_2DD7:
  _cl = memory[adr(_es, 10976)];
  _rep_movsw<MemData, MemB800, DirForward>();
  _si = ((_si - *(WORD*)&memory[adr(_es, 10976)]) - *(WORD*)&memory[adr(_es, 10976)]) ^ 0x2000;
  if (_si & 0x2000)
    goto loc_2DF5;
  _si += 0x50;
loc_2DF5:
  memory[adr(_es, 10978)] -= 1;
  if (memory[adr(_es, 10978)] != 0)
    goto loc_2DD7;
}

void sub_2DFD()
{
  _dx = *(WORD*)&memory[adr(_ds, 0x2AE5)];
  _dl = (_dl ^ _dh) >> 2;
  _ASSERT(0 /* check carry */); _rcr(*(WORD*)&memory[adr(_ds, 0x2AE5)], 1);
  _dx = *(WORD*)&memory[adr(_ds, 0x2AE5)];
}

void sub_2E10()
{
  _al = 0x00;
  _out(0x43, _al);
  _in(_al, 0x40);
  _ah = _al;
  _in(_al, 0x40);
  if (_ax != 0x0000)
    goto loc_2E25;
  _ax = 0xfa59;
loc_2E25:
  *(WORD*)&memory[adr(_ds, 0x2AE5)] = _ax;
}

void sub_2E29()
{
  _ax += _si;
  if (_ax < _bx)
    goto loc_2E4F;
  _ax -= _si;
  flags.carry = _ax < _di;
  _ax -= _di;
  if (!flags.carry)
    goto loc_2E37;
  _ax = 0;
loc_2E37:
  if (_ax > _bx)
    goto loc_2E4F;
  _dl += _cl;
  if (_dl < _dh)
    goto loc_2E4F;
  _dl -= _cl;
  flags.carry = _dl < _ch;
  _dl -= _ch;
  if (!flags.carry)
    goto loc_2E49;
  _dl = 0;
loc_2E49:
  if (_dl > _dh)
    goto loc_2E4F;
  flags.carry = true;
  return;
loc_2E4F:
  flags.carry = false;
}

void sub_2E60()
{
  if (*(WORD*)&memory[adr(_ds, 0x2E8D)] < 8)
    goto loc_2E68;
  return;
loc_2E68:
  if (memory[adr(_ds, 0x69A)] != 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x2E92)] = 0xffff;
  memory[adr(_ds, 0x2E91)] = 0xff;
  _cx = 0x0007;
loc_2E7D:
  _bx = _cx - 1;
  _al = memory[adr(_ds, 0x57B)];
  flags.carry = _al < memory[adr(_ds, _bx + 11220)];
  _al = _al - memory[adr(_ds, _bx + 11220)];
  if (!flags.carry)
    goto loc_2E8B;
  _al = (~_al);
loc_2E8B:
  if (_al > memory[adr(_ds, 0x2E91)])
    goto loc_2E98;
  memory[adr(_ds, 0x2E91)] = _al;
  *(WORD*)&memory[adr(_ds, 0x2E92)] = _bx;
loc_2E98:
  if (--_cx)
    goto loc_2E7D;
  if (*(WORD*)&memory[adr(_ds, 0x2E92)] != 0xffff)
    goto loc_2EA8;
  *(WORD*)&memory[adr(_ds, 0x2E92)] = 0;
loc_2EA8:
  _bx = *(WORD*)&memory[adr(_ds, 0x2E8D)];
  _si = *(WORD*)&memory[adr(_ds, 0x2E92)];
  _al = memory[adr(_ds, _si + 11220)];
  memory[adr(_ds, _bx + 11114)] = _al;
  memory[adr(_ds, 0x2E98)] = _al;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  _bl <<= 1;
  if (_ax < 0x0108)
    goto loc_2EC8;
  _ax = 0x0107;
loc_2EC8:
  _ax &= 0x0ffc;
  *(WORD*)&memory[adr(_ds, _bx + 11098)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x2E96)] = _ax;
  _cx = 0x0008;
loc_2ED5:
  _bx = _cx - 1;
  if (_bx == *(WORD*)&memory[adr(_ds, 0x2E8D)])
    goto loc_2F07;
  if (memory[adr(_ds, _bx + 11122)] == 0)
    goto loc_2F07;
  _push(_cx);
  _dl = memory[adr(_ds, _bx + 11114)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  _bx = *(WORD*)&memory[adr(_ds, 0x2E96)];
  _dh = memory[adr(_ds, 0x2E98)];
  _si = 0x18;
  _di = _si;
  _cx = 0x0f0f;
  sub_2E29();
  _cx = _pop();
  if (!flags.carry)
    goto loc_2F07;
  return;
loc_2F07:
  if (--_cx)
    goto loc_2ED5;
  sub_11E3();
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_2F16;
  sub_622B();
loc_2F16:
  _bx = *(WORD*)&memory[adr(_ds, 0x2E8D)];
  *(WORD*)&memory[adr(_ds, 0x2E94)] = _bx;
  memory[adr(_ds, _bx + 11122)] = 1;
  _dl = memory[adr(_ds, _bx + 11114)];
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  sub_2CB0();
  _di = _ax;
  _si = 0x2af0;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0f03;
  sub_2D9D();
  *(WORD*)&memory[adr(_ds, 0x2E8D)] = 0xffff;
  _bx = 0;
  _ah = 0x0b;
  _interrupt(0x10);
  sub_4E3E();
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_2F59;
  sub_61FA();
loc_2F59:
  sub_1145();
  _ax = 0x03e8;
  _bx = 0x04a5;
  sub_593B();
}

void sub_2F66()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x2E8F)])
    goto loc_2F71;
  return;
loc_2F71:
  *(WORD*)&memory[adr(_ds, 0x2E8F)] = _dx;
  if (*(WORD*)&memory[adr(_ds, 0x2E8D)] < 8)
    goto loc_2FAC;
  _cx = 0x0008;
loc_2F7F:
  _bx = _cx - 1;
  if (memory[adr(_ds, _bx + 11122)] == 0)
    goto loc_2FAA;
  _push(_cx);
  _dl = memory[adr(_ds, _bx + 11114)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  _si = 0x18;
  _di = _si;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _cx = 0x0e0f;
  sub_2E29();
  _cx = _pop();
  if (flags.carry)
    goto loc_2FB3;
loc_2FAA:
  if (--_cx)
    goto loc_2F7F;
loc_2FAC:
  *(WORD*)&memory[adr(_ds, 0x2E94)] = 0xffff;
  return;
loc_2FB3:
  _bx = _cx - 1;
  if (_bx == *(WORD*)&memory[adr(_ds, 0x2E94)])
    return;
  _push(_bx);
  sub_11E3();
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_2FCA;
  sub_622B();
loc_2FCA:
  _bx = _pop();
  memory[adr(_ds, _bx + 11122)] = 0;
  _dl = memory[adr(_ds, _bx + 11114)];
  *(WORD*)&memory[adr(_ds, 0x2E8D)] = _bx;
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  sub_2CB0();
  _di = _ax;
  _si = 0x2b7a;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0f03;
  sub_2D9D();
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_2FFB;
  sub_61FA();
loc_2FFB:
  sub_1145();
  _bx = 0x0001;
  _ah = 0x0b;
  _interrupt(0x10);
  _ax = 0x03e8;
  _bx = 0x0349;
  sub_593B();
}

void sub_300F()
{
  _ax = 0;
  _bx = 0x2e24;
  sub_2B24();
  memory[adr(_ds, 0x2E8A)] = 0xbf;
  *(WORD*)&memory[adr(_ds, 0x2E8B)] = 0;
loc_3022:
  *(WORD*)&memory[adr(_ds, 0x2E88)] = 0x20;
loc_3028:
  _bx = 0;
  if (memory[adr(_ds, 0x2E8A)] == 0xbf)
    goto loc_3039;
  sub_2DFD();
  _bl = _dl & 0x02;
loc_3039:
  _cx = *(WORD*)&memory[adr(_ds, 0x2E88)];
  _dl = memory[adr(_ds, 0x2E8A)];
  _push(_bx);
  sub_30E3();
  _bx = _pop();
  _si = *(WORD*)&memory[adr(_ds, 0x2E8B)];
  _ax = *(WORD*)&memory[adr(_ds, 0x2E88)];
  _cl = 0x04;
  _ax >>= _cl;
  flags.carry = _ax < 0x0002;
  _ax -= 0x0002;
  if (!flags.carry)
    goto loc_3058;
  _ax = 0;
loc_3058:
  if (_ax < 0x12)
    goto loc_3060;
  _ax = 0x11;
loc_3060:
  _dl = memory[adr(_ds, _si + 11227)];
  _dh = 0;
  _ax += _dx;
  _si = _ax;
  memory[adr(_ds, _si + 11234)] = _bl;
  *(WORD*)&memory[adr(_ds, 0x2E88)] += 0x10;
  if (*(WORD*)&memory[adr(_ds, 0x2E88)] < 273)
    goto loc_3028;
  *(WORD*)&memory[adr(_ds, 0x2E8B)] += 1;
  memory[adr(_ds, 0x2E8A)] -= 0x18;
  if (memory[adr(_ds, 0x2E8A)] >= 0x2f)
    goto loc_3022;
  _ax = 0xffff;
  *(WORD*)&memory[adr(_ds, 0x2E8D)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x2E94)] = _ax;
  _ax = 0;
  *(WORD*)&memory[adr(_ds, 0x2B72)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x2B74)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x2B76)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x2B78)] = _ax;
  _cx = *(WORD*)&memory[adr(_ds, 0x414)];
  if (_cx != 0x0000)
    goto loc_30B0;
  _cx += 1;
  *(WORD*)&memory[adr(_ds, 0x414)] = _cx;
loc_30B0:
  if (_cx <= 0x0008)
    goto loc_30B8;
  _cx = 0x0008;
loc_30B8:
  _bx = _cx - 1;
  memory[adr(_ds, _bx + 11122)] = 1;
  _dl = 0xb0;
  memory[adr(_ds, _bx + 11114)] = _dl;
  _push(_cx);
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 11082)];
  *(WORD*)&memory[adr(_ds, _bx + 11098)] = _cx;
  sub_2CB0();
  _di = _ax;
  _si = 0x2af0;
  _cx = 0x0f03;
  sub_2D9D();
  _cx = _pop();
  if (--_cx)
    goto loc_30B8;
}

void sub_30E3()
{
  _push(_bx);
  sub_2CB0();
  _di = _ax;
  _ax = 0xb800;
  _es = _ax;
  _bx = _pop();
  _si = *(WORD*)&memory[adr(_ds, _bx + 11808)];
  _cx = 0x0802;
  sub_2D9D();
}

void sub_30FA()
{
  _al = ((memory[adr(_ds, 0x57B)]) - 0x05) & 0xf8;
  _cx = 0x0007;
loc_3104:
  _bx = _cx - 1;
  if (_al == memory[adr(_ds, _bx + 11220)])
    goto loc_3111;
  if (--_cx)
    goto loc_3104;
  goto loc_314D;
loc_3111:
  _ch = _al;
  _ax = (*(WORD*)&memory[adr(_ds, 0x579)]) + 0x0007;
  _cl = 0x04;
  _ax >>= _cl;
  flags.carry = _ax < 0x0002;
  _ax -= 0x0002;
  if (!flags.carry)
    goto loc_3124;
  _ax = 0;
loc_3124:
  if (_ax < 0x12)
    goto loc_312C;
  _ax = 0x11;
loc_312C:
  _dl = memory[adr(_ds, _bx + 11227)];
  _dh = 0;
  _ax += _dx;
  _si = _ax;
  if (memory[adr(_ds, _si + 11234)] != 0)
    goto loc_314D;
  _ch += 0x05;
  memory[adr(_ds, 0x57B)] = _ch;
  _ch += 0x32;
  memory[adr(_ds, 0x57C)] = _ch;
  flags.carry = true;
  return;
loc_314D:
  flags.carry = false;
}

void sub_3150()
{
  _ah = 0;
  _interrupt(0x1a);
  _bx = *(WORD*)&memory[adr(_ds, 0x4)];
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 13042)];
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x328C)];
  if (_ax >= _cx)
    goto loc_3169;
  return;
loc_3169:
  *(WORD*)&memory[adr(_ds, 0x328C)] = _dx;
  sub_33BA();
  if (flags.carry)
    return;
  sub_21E0();
  if (flags.carry)
    return;
  memory[adr(_ds, 0x32EA)] += 1;
  sub_2DFD();
  _al = (memory[adr(_ds, 0x32EA)]) & _dl;
  memory[adr(_ds, 0x32EB)] = memory[adr(_ds, 0x32EB)] ^ _al;
  _ax = *(WORD*)&memory[adr(_ds, 0x327D)];
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x579)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = 0xff;
  if (!flags.carry)
    goto loc_3196;
  _ax = (~_ax);
  _dl = 0x01;
loc_3196:
  memory[adr(_ds, 0x32ED)] = _dl;
  _bl = (memory[adr(_ds, 0x327F)]) + 0x14;
  flags.carry = _bl < memory[adr(_ds, 0x57B)];
  _bl = _bl - memory[adr(_ds, 0x57B)];
  _dl = 0xff;
  if (!flags.carry)
    goto loc_31AD;
  _bl = (~_bl);
  _dl = 0x01;
loc_31AD:
  memory[adr(_ds, 0x32EE)] = _dl;
  _ax >>= 2;
  _bl >>= 1;
  _al += _bl;
  memory[adr(_ds, 0x32EC)] = _al;
  _bx = *(WORD*)&memory[adr(_ds, 0x328A)];
  if (_bx < 0x27)
    goto loc_31CC;
  _bx = 0x26;
  *(WORD*)&memory[adr(_ds, 0x328A)] = _bx;
loc_31CC:
  if (memory[adr(_ds, _bx + 12942)] != 0)
    goto loc_324B;
  *(WORD*)&memory[adr(_ds, 0x328A)] -= 1;
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x410)];
  _cl = 0x03;
  _dx >>= _cl;
  _al = memory[adr(_ds, 0x32EC)];
  flags.carry = _al < _dl;
  _al -= _dl;
  if (!flags.carry)
    goto loc_31EC;
  _al = 0;
loc_31EC:
  if (_al < memory[adr(_ds, 0x32EB)])
    goto loc_3212;
  memory[adr(_ds, 0x3281)] = 1;
  sub_2DFD();
  if (_dl == 0x00)
    goto loc_320B;
  if (_dl > 0x07)
    goto loc_32AC;
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_320B;
  _dl = 0xff;
loc_320B:
  memory[adr(_ds, 0x3280)] = _dl;
  goto loc_32AC;
loc_3212:
  _al = (memory[adr(_ds, 0x32EB)]) & 0x2f;
  if (_al != 0)
    goto loc_3238;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_3223;
  _dl = 0xff;
loc_3223:
  memory[adr(_ds, 0x3280)] = _dl;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_3231;
  _dl = 0xff;
loc_3231:
  memory[adr(_ds, 0x3281)] = _dl;
  goto loc_32AC;
loc_3238:
  _al &= 0x07;
  if (_al != 0)
    goto loc_32AC;
  _al = memory[adr(_ds, 0x32ED)];
  memory[adr(_ds, 0x3280)] = _al;
  _al = memory[adr(_ds, 0x32EE)];
  memory[adr(_ds, 0x3281)] = _al;
  goto loc_32AC;
loc_324B:
  memory[adr(_ds, 0x3281)] = 1;
  _ax = _bx;
  _cl = 0x03;
  _ax <<= _cl;
  if (*(WORD*)&memory[adr(_ds, 0x327D)] == _ax)
    goto loc_3269;
  _dl = 0x01;
  if (*(WORD*)&memory[adr(_ds, 0x327D)] < _ax)
    goto loc_3262;
  _dl = 0xff;
loc_3262:
  memory[adr(_ds, 0x3280)] = _dl;
  goto loc_32AC;
loc_3269:
  memory[adr(_ds, 0x3280)] = 0;
  if (memory[adr(_ds, 0x327F)] != 0xa5)
    goto loc_32AC;
  memory[adr(_ds, 0x3281)] = 0;
  if (*(WORD*)&memory[adr(_ds, 0x327A)] == 6)
    goto loc_3288;
  if (*(WORD*)&memory[adr(_ds, 0x327A)] != 0x12)
    goto loc_32AC;
loc_3288:
  _push(_bx);
  _si = 0x31e8;
  _di = *(WORD*)&memory[adr(_ds, 0x3282)];
  _cx = 0x1e02;
  _ax = 0xb800;
  _es = _ax;
  sub_2D9D();
  _bx = _pop();
  memory[adr(_ds, _bx + 12942)] -= 1;
  _al = memory[adr(_ds, _bx + 12942)];
  sub_347F();
  memory[adr(_ds, 0x3286)] = 1;
loc_32AC:
  _cx = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dl = memory[adr(_ds, 0x327F)];
  *(WORD*)&memory[adr(_ds, 0x32EF)] = _cx;
  memory[adr(_ds, 0x32F1)] = _dl;
  if (memory[adr(_ds, 0x3280)] < 1)
    goto loc_32DA;
  if (memory[adr(_ds, 0x3280)] != 1)
    goto loc_32D3;
  _cx += 0x0008;
  if (_cx < 0x0131)
    goto loc_32DA;
  _cx = 0x0130;
  goto loc_32DA;
loc_32D3:
  flags.carry = _cx < 0x0008;
  _cx -= 0x0008;
  if (!flags.carry)
    goto loc_32DA;
  _cx = 0;
loc_32DA:
  _cx &= 0xfff8;
  *(WORD*)&memory[adr(_ds, 0x327D)] = _cx;
  if (memory[adr(_ds, 0x3281)] < 1)
    goto loc_32FE;
  if (memory[adr(_ds, 0x3281)] != 1)
    goto loc_32F7;
  _dl += 0x02;
  if (_dl < 0xa6)
    goto loc_32FE;
  _dl = 0xa5;
  goto loc_32FE;
loc_32F7:
  flags.carry = _dl < 0x02;
  _dl -= 0x02;
  if (!flags.carry)
    goto loc_32FE;
  _dl = 0;
loc_32FE:
  memory[adr(_ds, 0x327F)] = _dl;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x3284)] = _ax;
  sub_33BA();
  if (!flags.carry)
    goto loc_3328;
loc_330D:
  memory[adr(_ds, 0x3280)] = 0;
  memory[adr(_ds, 0x3281)] = 0;
  _cx = *(WORD*)&memory[adr(_ds, 0x32EF)];
  *(WORD*)&memory[adr(_ds, 0x327D)] = _cx;
  _dl = memory[adr(_ds, 0x32F1)];
  memory[adr(_ds, 0x327F)] = _dl;
  return;
loc_3328:
  sub_21E0();
  if (flags.carry)
    goto loc_330D;
  sub_33A0();
  *(WORD*)&memory[adr(_ds, 0x327A)] += 2;
  sub_3339();
}

void sub_3339()
{
sub_3339:
  _bx = *(WORD*)&memory[adr(_ds, 0x327A)];
  _ax = *(WORD*)&memory[adr(_ds, _bx + 12896)];
  if (_ax != 0x0000)
    goto loc_334B;
  *(WORD*)&memory[adr(_ds, 0x327A)] = _ax;
  goto sub_3339;
loc_334B:
  _si = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x3284)];
  *(WORD*)&memory[adr(_ds, 0x3282)] = _di;
  _bp = 0x31e8;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x1e02;
  memory[adr(_ds, 0x3286)] = 0;
  flags.direction = false;
  memory[adr(_ds, 0x3289)] = _ch;
  _ch = 0;
  *(WORD*)&memory[adr(_ds, 0x3287)] = _cx;
loc_3370:
  _cx = *(WORD*)&memory[adr(_ds, 0x3287)];
loc_3374:
  _bx = _videoRead16(_esAssume(0xb800), _di);
  *(WORD*)&memory[adr(_ds, _bp + 0)] = _bx;
  _lodsw<MemData, DirForward>();
  _ax |= _bx;
  _stosw<MemB800, DirForward>();
  _bp += 0x0002;
  if (--_cx)
    goto loc_3374;
  _di = ((_di - *(WORD*)&memory[adr(_ds, 0x3287)]) - *(WORD*)&memory[adr(_ds, 0x3287)]) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_3399;
  _di += 0x50;
loc_3399:
  memory[adr(_ds, 0x3289)] -= 1;
  if (memory[adr(_ds, 0x3289)] != 0)
    goto loc_3370;
}

void sub_33A0()
{
  if (memory[adr(_ds, 0x3286)] != 0)
    return;
  _ax = 0xb800;
  _es = _ax;
  _si = 0x31e8;
  _di = *(WORD*)&memory[adr(_ds, 0x3282)];
  _cx = 0x1e02;
  sub_2D9D();
}

void sub_33BA()
{
  if (memory[adr(_ds, 0x1CB8)] != 0)
    goto loc_3403;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 6)
    goto loc_33D3;
  if (memory[adr(_ds, 0x44BD)] == 0)
    goto loc_33D3;
  sub_47B0();
  return;
loc_33D3:
  _ax = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dl = memory[adr(_ds, 0x327F)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e1e;
  sub_2E29();
  if (!flags.carry)
    goto loc_3403;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 4)
    goto loc_33FE;
  if (memory[adr(_ds, 0x39E1)] != 0)
    goto loc_3401;
loc_33FE:
  sub_872();
loc_3401:
  flags.carry = true;
  return;
loc_3403:
  flags.carry = false;
}

void sub_3405()
{
  flags.direction = false;
  _ax = 0;
  _push(_ds);
  _es = _pop();
  _di = 0x328e;
  _cx = 0x14;
  _rep_stosw<MemData, DirForward>();
  *(WORD*)&memory[adr(_ds, 0x32B6)] = 0xff;
  *(WORD*)&memory[adr(_ds, 0x327A)] = 0;
  *(WORD*)&memory[adr(_ds, 0x327D)] = 0;
  memory[adr(_ds, 0x327F)] = 0xa0;
  memory[adr(_ds, 0x3286)] = 1;
  memory[adr(_ds, 0x3280)] = 0;
  memory[adr(_ds, 0x3281)] = 0;
  sub_2DFD();
  memory[adr(_ds, 0x32EB)] = _dl;
  memory[adr(_ds, 0x32EA)] = 0x6c;
}

void sub_3445()
{
  if (memory[adr(_ds, 0x57B)] < 0xb4)
    return;
  if (memory[adr(_ds, 0x56E)] == 0)
    return;
  _ax = (*(WORD*)&memory[adr(_ds, 0x579)]) + 0x0c;
  _cl = 0x03;
  _ax >>= _cl;
  if (_ax > 0x27)
    return;
  if (_ax == *(WORD*)&memory[adr(_ds, 0x32B6)])
    return;
  *(WORD*)&memory[adr(_ds, 0x32B6)] = _ax;
  _bx = _ax;
  _al = memory[adr(_ds, _bx + 12942)];
  if (_al >= 0x04)
    return;
  _al += 1;
  memory[adr(_ds, _bx + 12942)] = _al;
  sub_347F();
}

void sub_347F()
{
  _ah = 0x0a;
  _ax = (_ah * _al) + 0x32b8;
  _si = _ax;
  _di = (_bx << 1) + 0x1e00;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0501;
  sub_2D9D();
}

void sub_34A0()
{
  *(WORD*)&memory[adr(_ds, 0x3511)] = 0;
  memory[adr(_ds, 0x351B)] = 0;
loc_34AB:
  _bx = *(WORD*)&memory[adr(_ds, 0x3511)];
  flags.zero = memory[adr(_ds, _bx + 13479)] == 0; flags.carry = memory[adr(_ds, _bx + 13479)] < 0;
  if (memory[adr(_ds, _bx + 13479)] == 0)
    goto loc_34B9;
  goto loc_35AD;
loc_34B9:
  _si = _bx << 1;
  _ax = *(WORD*)&memory[adr(_ds, _si + 13383)];
  _dl = memory[adr(_ds, _bx + 13431)];
  _di = 0x0000;
  flags.zero = _bx == 0x0c; flags.carry = _bx < 0x0c;
  if (_bx < 0x0c)
    goto loc_34D0;
  _di = 0x0002;
loc_34D0:
  _si = *(WORD*)&memory[adr(_ds, _di + 13587)];
  _cx = *(WORD*)&memory[adr(_ds, _di + 13591)];
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _ch = 0x0e;
  sub_2E29();
  if (!flags.carry)
    goto loc_35AD;
  _bx = *(WORD*)&memory[adr(_ds, 0x3511)];
  flags.zero = _bx == 0x0c; flags.carry = _bx < 0x0c;
  if (_bx < 0x0c)
    goto loc_356F;
  flags.zero = memory[adr(_ds, 0x553)] == 0; flags.carry = memory[adr(_ds, 0x553)] < 0;
  if (memory[adr(_ds, 0x553)] != 0)
    goto loc_356F;
  flags.zero = memory[adr(_ds, 0x5F3)] == 0; flags.carry = memory[adr(_ds, 0x5F3)] < 0;
  if (memory[adr(_ds, 0x5F3)] != 0)
    goto loc_356F;
  memory[adr(_ds, 0x552)] = 1;
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _cx < 0x0008;
  _cx -= 0x0008;
  if (!flags.carry)
    goto loc_3511;
  _cx = 0;
loc_3511:
  flags.zero = _cx == 0x0117; flags.carry = _cx < 0x0117;
  if (_cx < 0x0117)
    goto loc_351A;
  _cx = 0x0116;
loc_351A:
  _dl = memory[adr(_ds, 0x57B)];
  flags.zero = _dl == 0xb5; flags.carry = _dl < 0xb5;
  if (_dl < 0xb5)
    goto loc_3525;
  _dl = 0xb4;
loc_3525:
  sub_2CB0();
  _di = _ax;
  _si = 0x3350;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x1205;
  sub_2D9D();
  sub_5797();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x3509)] = _dx;
loc_3543:
  _push(_dx);
loc_3544:
  sub_57A6();
  sub_13D8();
  if (_al == 0)
    goto loc_3544;
  sub_57A6();
  _dx = _pop();
  _bx = 0x0001;
  if (_dl & 0x01)
    goto loc_355A;
  _bl = 0x0f;
loc_355A:
  _ah = 0x0b;
  _interrupt(0x10);
  sub_57A6();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x3509)];
  flags.zero = _dx == 0x0d; flags.carry = _dx < 0x0d;
  if (_dx < 0x0d)
    goto loc_3543;
  return;
loc_356F:
  memory[adr(_ds, 0x351B)] += 1;
  _ax = 0x05dc;
  _bx = 0x0425;
  sub_593B();
  flags.zero = memory[adr(_ds, 0x351B)] == 1; flags.carry = memory[adr(_ds, 0x351B)] < 1;
  if (memory[adr(_ds, 0x351B)] != 1)
    goto loc_3586;
  sub_11E3();
loc_3586:
  _bx = *(WORD*)&memory[adr(_ds, 0x3511)];
  sub_37C1();
  _bx = *(WORD*)&memory[adr(_ds, 0x3511)];
  memory[adr(_ds, _bx + 13479)] = 1;
  flags.zero = _bx == 0x0c; flags.carry = _bx < 0x0c;
  if (_bx >= 0x0c)
    goto loc_35AD;
  memory[adr(_ds, 0x3410)] -= 1;
  if (memory[adr(_ds, 0x3410)] != 0)
    goto loc_35AD;
  flags.zero = memory[adr(_ds, 0x5F3)] == 0; flags.carry = memory[adr(_ds, 0x5F3)] < 0;
  if (memory[adr(_ds, 0x5F3)] != 0)
    goto loc_35AD;
  memory[adr(_ds, 0x553)] = 1;
loc_35AD:
  *(WORD*)&memory[adr(_ds, 0x3511)] += 1;
  flags.zero = *(WORD*)&memory[adr(_ds, 0x3511)] == 0x18; flags.carry = *(WORD*)&memory[adr(_ds, 0x3511)] < 0x18;
  if (*(WORD*)&memory[adr(_ds, 0x3511)] >= 0x18)
    goto loc_35BB;
  goto loc_34AB;
loc_35BB:
  flags.zero = memory[adr(_ds, 0x351B)] == 0; flags.carry = memory[adr(_ds, 0x351B)] < 0;
  if (memory[adr(_ds, 0x351B)] == 0)
    goto loc_35C7;
  sub_363D();
  flags.carry = true;
  return;
loc_35C7:
  flags.carry = false;
}

void sub_35C9()
{
  *(WORD*)&memory[adr(_ds, 0x3411)] = 0;
  *(WORD*)&memory[adr(_ds, 0x3415)] = 0;
  memory[adr(_ds, 0x3410)] = 0x0c;
  _cx = 0x18;
loc_35DD:
  _bx = _cx - 1;
  memory[adr(_ds, _bx + 13455)] = 1;
  memory[adr(_ds, _bx + 13479)] = 0;
  _al = memory[adr(_ds, _bx + 13553)];
  memory[adr(_ds, _bx + 13431)] = _al;
  memory[adr(_ds, _bx + 13359)] = 1;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_3601;
  _dl = (~_dl);
loc_3601:
  memory[adr(_ds, _bx + 13335)] = _dl;
  _bx <<= 1;
  sub_2DFD();
  _dh = 0;
  *(WORD*)&memory[adr(_ds, _bx + 13383)] = _dx;
  if (--_cx)
    goto loc_35DD;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _cl = memory[adr(_ds, _bx + 13596)];
  _ch = 0;
loc_361C:
  sub_2DFD();
  _dl &= 0x0f;
  if (_dl >= 0x0c)
    goto loc_361C;
  _bl = _dl + 0x0c;
  _bh = 0;
  if (memory[adr(_ds, _bx + 13479)] != 0)
    goto loc_361C;
  memory[adr(_ds, _bx + 13479)] = 1;
  if (--_cx)
    goto loc_361C;
}

void sub_363D()
{
sub_363D:
  _cx = 0x0c;
loc_3640:
  _bx = _cx + 0x0b;
  if (memory[adr(_ds, _bx + 13479)] == 0)
    goto loc_3672;
  _ax = 0;
  _dl = 0x01;
  memory[adr(_ds, _bx + 13479)] = _al;
  if (*(WORD*)&memory[adr(_ds, 0x579)] > 0xa0)
    goto loc_3661;
  _ax = 0x012e;
  _dl = 0xff;
loc_3661:
  memory[adr(_ds, _bx + 13335)] = _dl;
  _bl <<= 1;
  *(WORD*)&memory[adr(_ds, _bx + 13383)] = _ax;
  memory[adr(_ds, 0x351B)] -= 1;
  if (memory[adr(_ds, 0x351B)] != 0)
    goto sub_363D;
  return;
loc_3672:
  if (--_cx)
    goto loc_3640;
}

void sub_3675()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x3509)])
    goto loc_3680;
  return;
loc_3680:
  *(WORD*)&memory[adr(_ds, 0x350B)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x3415)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x3415)];
  if (_bx < 0x18)
    goto loc_36A4;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x3415)] = _bx;
  *(WORD*)&memory[adr(_ds, 0x3411)] = *(WORD*)&memory[adr(_ds, 0x3411)] ^ 0x0c;
  *(WORD*)&memory[adr(_ds, 0x3413)] += 8;
  goto loc_36B7;
loc_36A4:
  if (_bx != 0x0c)
    goto loc_36BD;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_36B7;
  if (memory[adr(_ds, 0x57B)] < 0x30)
    goto loc_36BD;
loc_36B7:
  _ax = *(WORD*)&memory[adr(_ds, 0x350B)];
  *(WORD*)&memory[adr(_ds, 0x3509)] = _ax;
loc_36BD:
  _si = _bx << 1;
  if (memory[adr(_ds, _bx + 13479)] != 0)
    return;
  sub_2DFD();
  if (_dl > 0x10)
    goto loc_36E9;
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_36D7;
  _dl = (~_dl);
loc_36D7:
  memory[adr(_ds, _bx + 13335)] = _dl;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_36E5;
  _dl = (~_dl);
loc_36E5:
  memory[adr(_ds, _bx + 13359)] = _dl;
loc_36E9:
  _cx = 0x0004;
  if (_bx < 0x0c)
    goto loc_36F3;
  _cl >>= 1;
loc_36F3:
  _ax = *(WORD*)&memory[adr(_ds, _si + 13383)];
  if (memory[adr(_ds, _bx + 13335)] == 1)
    goto loc_370B;
  flags.carry = _ax < _cx;
  _ax -= _cx;
  if (!flags.carry)
    goto loc_371A;
  _ax = 0;
  memory[adr(_ds, _bx + 13335)] = 1;
  goto loc_371A;
loc_370B:
  _ax += _cx;
  if (_ax < 0x012f)
    goto loc_371A;
  _ax = 0x012e;
  memory[adr(_ds, _bx + 13335)] = 0xff;
loc_371A:
  *(WORD*)&memory[adr(_ds, _si + 13383)] = _ax;
  _al = memory[adr(_ds, _bx + 13431)];
  if (memory[adr(_ds, _bx + 13359)] == 1)
    goto loc_373C;
  _al -= 1;
  if (_al >= memory[adr(_ds, _bx + 13553)])
    goto loc_3750;
  _al = memory[adr(_ds, _bx + 13553)];
  memory[adr(_ds, _bx + 13359)] = 1;
  goto loc_3750;
loc_373C:
  _al += 1;
  _dl = (memory[adr(_ds, _bx + 13553)]) + 0x18;
  if (_al <= _dl)
    goto loc_3750;
  _al = _dl;
  memory[adr(_ds, _bx + 13359)] = 0xff;
loc_3750:
  memory[adr(_ds, _bx + 13431)] = _al;
  _dl = _al;
  _cx = *(WORD*)&memory[adr(_ds, _si + 13383)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x34EF)] = _ax;
  _bx = *(WORD*)&memory[adr(_ds, 0x3415)];
  sub_37C1();
  _bx = *(WORD*)&memory[adr(_ds, 0x3415)];
  _si = _bx << 1;
  _di = *(WORD*)&memory[adr(_ds, 0x34EF)];
  *(WORD*)&memory[adr(_ds, _si + 13503)] = _di;
  memory[adr(_ds, _bx + 13455)] = 0;
  _ax = 0xb800;
  _es = _ax;
  if (_bx < 0x0c)
    goto loc_379F;
  _si = _bx;
  _cl = 0x03;
  _si = (((_si << _cl) + *(WORD*)&memory[adr(_ds, 0x3413)]) & 0x18) + 0x3330;
  _cx = 0x0202;
  sub_2D9D();
  return;
loc_379F:
  _si = *(WORD*)&memory[adr(_ds, 0x3411)];
  if (_bl & 0x01)
    goto loc_37AC;
  _si = _si ^ 0x0c;
loc_37AC:
  if (memory[adr(_ds, _bx + 13335)] == 1)
    goto loc_37B6;
  _si += 0x18;
loc_37B6:
  _si += 0x3300;
  _cx = 0x0601;
  sub_2D9D();
}

void sub_37C1()
{
  if (memory[adr(_ds, _bx + 13455)] != 0)
    return;
  _bx <<= 1;
  _si = 0x3404;
  _di = *(WORD*)&memory[adr(_ds, _bx + 13503)];
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0601;
  if (_bx < 0x18)
    goto loc_37E1;
  _cx = 0x0202;
loc_37E1:
  sub_2D9D();
}

void sub_37E5()
{
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x350F)];
  if (_ax < 0x0008)
    return;
  *(WORD*)&memory[adr(_ds, 0x350D)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x350D)];
  if (_bx < 0x28)
    goto loc_380B;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x350D)] = _bx;
  *(WORD*)&memory[adr(_ds, 0x350F)] = _dx;
loc_380B:
  _di = _bx << 1;
  if (memory[adr(_ds, 0x57B)] > 7)
    goto loc_3829;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  _cl = 0x02;
  _ax = (_ax >> _cl) + 1;
  flags.carry = _ax < _di;
  _ax -= _di;
  if (!flags.carry)
    goto loc_3824;
  _ax = (~_ax);
loc_3824:
  if (_ax < 0x0004)
    return;
loc_3829:
  _di += 0xa0;
  _al = (memory[adr(_ds, _bx + 9814)]) + 0x08;
  memory[adr(_ds, _bx + 9814)] = _al;
  _ax = (_ax & 0x18) + 0x2020;
  _si = _ax;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0401;
  sub_2D9D();
}

void sub_3850()
{
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x35DA)];
  if (_ax >= 0x0006)
    goto loc_3860;
  return;
loc_3860:
  *(WORD*)&memory[adr(_ds, 0x35DA)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x35D8)] += 2;
  _bx = (*(WORD*)&memory[adr(_ds, 0x35D8)]) & 0x0006;
  _si = *(WORD*)&memory[adr(_ds, _bx + 13776)];
  _di = 0x15c9;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0a02;
  sub_2D9D();
  _ax = 0xe4;
  _dl = 0x8a;
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e0a;
  sub_2E29();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x554)] = 1;
}

void sub_38B0()
{
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_38BA;
  goto loc_38D3;
loc_38BA:
  *(WORD*)&memory[adr(_ds, 0x414)] += 1;
  memory[adr(_ds, 0x418)] = 1;
  _dx = 0xaaaa;
  sub_3A96();
  _ax = 0;
  memory[adr(_ds, 0x369F)] = 0;
  sub_3AAC();
loc_38D3:
  _ah = 0;
  _interrupt(0x1a);
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_38EF;
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x412)];
  _ax = 0x2a30;
  flags.carry = _ax < _dx;
  _ax -= _dx;
  if (!flags.carry)
    goto loc_38EB;
  _ax = 0;
loc_38EB:
  _ax >>= 1;
  goto loc_390E;
loc_38EF:
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x410)];
  _ax = 0x0546;
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 6)
    goto loc_38FF;
  _ax <<= 1;
loc_38FF:
  flags.carry = _ax < _dx;
  _ax -= _dx;
  if (!flags.carry)
    goto loc_3905;
  _ax = 0;
loc_3905:
  if (*(WORD*)&memory[adr(_ds, 0x6)] == 6)
    goto loc_390E;
  _ax <<= 1;
loc_390E:
  *(WORD*)&memory[adr(_ds, 0x3697)] = _ax;
  sub_3AF4();
  _bx = *(WORD*)&memory[adr(_ds, 0x6)];
  _bl <<= 1;
  _si = *(WORD*)&memory[adr(_ds, _bx + 14028)];
  _di = 0x368d;
  sub_271E();
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_396E;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl <<= 1;
  _ax = _bx;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 14044)];
  if (*(WORD*)&memory[adr(_ds, 0x2E8D)] >= 8)
    goto loc_3943;
  _cx <<= 1;
  _ax += 0x10;
loc_3943:
  *(WORD*)&memory[adr(_ds, 0x370C)] = _ax;
loc_3946:
  _si = 0x368d;
  _di = 0x1f82;
  _push(_cx);
  sub_271E();
  _cx = _pop();
  if (--_cx)
    goto loc_3946;
  sub_39FA();
  memory[adr(_ds, 0x369E)] = 0x38;
  memory[adr(_ds, 0x3699)] = 1;
  *(WORD*)&memory[adr(_ds, 0x3722)] = 0x44;
  sub_3A3A();
  sub_3A6C();
  goto loc_39A7;
loc_396E:
  _si = 0x368d;
  _di = 0x1f82;
  sub_271E();
  memory[adr(_ds, 0x3699)] = 2;
  *(WORD*)&memory[adr(_ds, 0x3722)] = 0x1e;
  _dx = 0xffff;
  sub_3A96();
  _ax = 0x0a8c - *(WORD*)&memory[adr(_ds, 0x3697)];
  _cl = 0x04;
  _ax >>= _cl;
  _al &= 0xf0;
  memory[adr(_ds, 0x369E)] = _al;
  _ah = 0x28;
  _ax = _ah * _al;
  memory[adr(_ds, 0x369F)] = 1;
  sub_3AAC();
  sub_3A3A();
loc_39A7:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x3695)] = _dx;
loc_39AF:
  if (*(WORD*)&memory[adr(_ds, 0x6)] != 7)
    goto loc_39BB;
  sub_5B63();
  goto loc_39BE;
loc_39BB:
  sub_5835();
loc_39BE:
  sub_3A1C();
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x3695)];
  if (_dx < *(WORD*)&memory[adr(_ds, 0x3722)])
    goto loc_39AF;
  _bx = 0;
  _ah = 0x0b;
  _interrupt(0x10);
  if (*(WORD*)&memory[adr(_ds, 0x6)] == 7)
    goto loc_39DC;
  sub_5B21();
  return;
loc_39DC:
  _ax = 0xb800;
  _es = _ax;
  _si = 0x0e;
  _di = 0x08e4;
  _cx = 0x0804;
  sub_2D9D();
  _si = 0x4e;
  _di = 0x0c94;
  _cx = 0x0814;
  sub_2D9D();
}

void sub_39FA()
{
  _push(_ds);
  _es = _pop();
  _ax = 0xb800;
  _ds = _ax;
  _cx = 0x0804;
  _di = 0x0e;
  _si = 0x08e4;
  sub_2DCA();
  _cx = 0x0814;
  _di = 0x4e;
  _si = 0x0c94;
  sub_2DCA();
  _push(_es);
  _ds = _pop();
}

void sub_3A1C()
{
  _ah = 0;
  _interrupt(0x1a);
  _push(_dx);
loc_3A21:
  sub_13D8();
  if (_al == 0)
    goto loc_3A21;
  _dx = _pop();
  _push(_dx);
  _bx = 0;
  if (_dx & 0x0004)
    goto loc_3A34;
  _bl = memory[adr(_ds, 0x3699)];
loc_3A34:
  _ah = 0x0b;
  _interrupt(0x10);
  _dx = _pop();
}

void sub_3A3A()
{
  _ah = 0x02;
  _dh = memory[adr(_ds, 0x369E)];
  _cl = 0x03;
  _dh >>= _cl;
  _dl = 0x12;
  _bh = 0;
  _interrupt(0x10);
  *(WORD*)&memory[adr(_ds, 0x36A0)] = 3;
loc_3A50:
  _bx = *(WORD*)&memory[adr(_ds, 0x36A0)];
  _al = (memory[adr(_ds, _bx + 13965)]) + 0x30;
  _ah = 0x0e;
  _bl = 0x03;
  _interrupt(0x10);
  *(WORD*)&memory[adr(_ds, 0x36A0)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x36A0)] < 7)
    goto loc_3A50;
}

void sub_3A6C()
{
  _ah = 0x02;
  _dl = 0x0a;
  _dh = _dl;
  _bx = 0;
  _interrupt(0x10);
  _bx = *(WORD*)&memory[adr(_ds, 0x370C)];
  _ax = *(WORD*)&memory[adr(_ds, _bx + 14060)];
  *(WORD*)&memory[adr(_ds, 0x3720)] = _ax;
  _bx = 0;
loc_3A83:
  _ah = 0x0e;
  _al = memory[adr(_ds, _bx + 14094)];
  _push(_bx);
  _bl = 0x03;
  _interrupt(0x10);
  _bx = _pop();
  _bx += 1;
  if (_bx < 0x14)
    goto loc_3A83;
}

void sub_3A96()
{
  flags.direction = false;
  _ax = SEG_DATA;
  _es = _ax;
  _di = 0x0e;
  _si = 0x35e0;
  _cx = 0x1e;
loc_3AA5:
  _lodsw<MemData, DirForward>();
  _ax &= _dx;
  _stosw<MemData, DirForward>();
  if (--_cx)
    goto loc_3AA5;
}

void sub_3AAC()
{
  *(WORD*)&memory[adr(_ds, 0x369A)] = _ax;
  _ax = 0xb800;
  _es = _ax;
  sub_5829();
  _ax = 0x1b80;
loc_3ABA:
  _bx = 0x361c;
  *(WORD*)&memory[adr(_ds, 0x369C)] = _ax;
  sub_2B24();
  if (memory[adr(_ds, 0x369F)] == 0)
    goto loc_3AE2;
  sub_5869();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x3695)] = _dx;
loc_3AD5:
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x3695)];
  if (_dx < 0x0002)
    goto loc_3AD5;
loc_3AE2:
  _ax = *(WORD*)&memory[adr(_ds, 0x369C)];
  flags.carry = _ax < 0x0280;
  _ax -= 0x0280;
  if (flags.carry)
    goto loc_3AF0;
  if (_ax >= *(WORD*)&memory[adr(_ds, 0x369A)])
    goto loc_3ABA;
loc_3AF0:
  sub_5B21();
}

void sub_3AF4()
{
  *(WORD*)&memory[adr(_ds, 0x368B)] = _ax;
  _ax = 0;
  *(WORD*)&memory[adr(_ds, 0x368D)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x368F)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x3691)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x3693)] = _ax;
  _bx = 0x3684;
  _dx = 0x1000;
loc_3B0B:
  if (!(*(WORD*)&memory[adr(_ds, 0x368B)] & _dx))
    goto loc_3B19;
  _si = _bx;
  _di = 0x368d;
  sub_271E();
loc_3B19:
  _bx -= 0x0007;
  flags.carry = _dx & 1;
  _dx >>= 1;
  if (!flags.carry)
    goto loc_3B0B;
}

void sub_3B30()
{
  memory[adr(_ds, 0x37AF)] = 3;
  _ax = 0x0001;
  *(WORD*)&memory[adr(_ds, 0x37B0)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x37B2)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x37B4)] = _ax;
}

void sub_3B42()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x37B8)])
    goto loc_3B4D;
  return;
loc_3B4D:
  *(WORD*)&memory[adr(_ds, 0x37B8)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x37B6)] = 4;
loc_3B57:
  _bx = *(WORD*)&memory[adr(_ds, 0x37B6)];
  if (*(WORD*)&memory[adr(_ds, _bx + 14256)] == 0)
    goto loc_3B9B;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 14243)];
  _dl = 0x18;
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e10;
  sub_2E29();
  if (!flags.carry)
    goto loc_3B9B;
  _ax = 0x0c00;
  _bx = 0x08fd;
  sub_593B();
  sub_11E3();
  sub_3E38();
  _bx = *(WORD*)&memory[adr(_ds, 0x37B6)];
  sub_3BA3();
  sub_1124();
  sub_3E14();
  return;
loc_3B9B:
  flags.carry = *(WORD*)&memory[adr(_ds, 0x37B6)] < 2;
  *(WORD*)&memory[adr(_ds, 0x37B6)] -= 2;
  if (!flags.carry)
    goto loc_3B57;
}

void sub_3BA3()
{
  *(WORD*)&memory[adr(_ds, _bx + 14256)] = 0;
  _push(_ds);
  _es = _pop();
  flags.direction = false;
  _ax = 0xaaaa;
  _di = 0x0e;
  _si = _di;
  _cx = 0x20;
  _rep_stosw<MemData, DirForward>();
  _di = *(WORD*)&memory[adr(_ds, _bx + 14249)];
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x1002;
  sub_2D9D();
  memory[adr(_ds, 0x37AF)] -= 1;
  if (memory[adr(_ds, 0x37AF)] != 0)
    return;
  if (memory[adr(_ds, 0x552)] != 0)
    return;
  memory[adr(_ds, 0x553)] = 1;
}

void sub_3BDB()
{
  _ax = 0xb800;
  _es = _ax;
  *(WORD*)&memory[adr(_ds, 0x37A0)] = 1642;
  _cx = 0x10;
loc_3BE9:
  _ax = 0;
  _bx = _ax;
loc_3BED:
  memory[adr(_ds, 0x37A2)] = _al;
  _ah = 0;
  _ax += 0x3730;
  _si = _ax;
  _di = (*(WORD*)&memory[adr(_ds, 0x37A0)]) + _bx;
  _push(_cx);
  _cx = 0x0801;
  _push(_bx);
  sub_2D9D();
  _bx = _pop();
  _cx = _pop();
  _bx += 0x0002;
  if (_bx < 0x1e)
    goto loc_3C1E;
  if (_bx != 0x1e)
    goto loc_3C15;
  _al = 0x20;
  goto loc_3BED;
loc_3C15:
  *(WORD*)&memory[adr(_ds, 0x37A0)] += 320;
  if (--_cx)
    goto loc_3BE9;
  return;
loc_3C1E:
  if (memory[adr(_ds, 0x37A2)] == 0x50)
    goto loc_3C36;
  if (_cl & 0x01)
    goto loc_3C36;
  sub_2DFD();
  if (_dl < 0x40)
    goto loc_3C36;
  _al = 0x10;
  goto loc_3BED;
loc_3C36:
  sub_2DFD();
  _al = ((_dl - _bl) & 0x30) + 0x30;
  goto loc_3BED;
}

void sub_3C43()
{
  _ax = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0xfffc;
  if (_ax < 0xa4)
    goto loc_3C7F;
  if (_ax > 0x0118)
    goto loc_3C7F;
  _dl = ((memory[adr(_ds, 0x57B)]) - 0x02) & 0xf8;
  if (!(_dl & 0x08))
    goto loc_3C7F;
  if (_dl < 0x28)
    goto loc_3C7F;
  if (_dl > 0xa0)
    goto loc_3C7F;
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  _dl += 0x02;
  memory[adr(_ds, 0x57B)] = _dl;
  _dl += 0x32;
  memory[adr(_ds, 0x57C)] = _dl;
  flags.carry = true;
  return;
loc_3C7F:
  flags.carry = false;
}

void sub_3C90()
{
  memory[adr(_ds, 0x3966)] = 8;
  memory[adr(_ds, 0x396A)] = 1;
  memory[adr(_ds, 0x3967)] = 0;
  memory[adr(_ds, 0x396D)] = 2;
  *(WORD*)&memory[adr(_ds, 0x3964)] = 280;
  *(WORD*)&memory[adr(_ds, 0x396B)] = 0;
}

void sub_3CB1()
{
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x39C8)];
  if (_ax >= 0x0002)
    goto loc_3CC1;
  return;
loc_3CC1:
  *(WORD*)&memory[adr(_ds, 0x39C8)] = _dx;
  sub_3E52();
  if (flags.carry)
    return;
  sub_3E6E();
  if (!flags.carry)
    goto loc_3CD2;
  goto loc_3D90;
loc_3CD2:
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 14796)];
  *(WORD*)&memory[adr(_ds, 0x39C6)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x3964)];
  *(WORD*)&memory[adr(_ds, 0x39C3)] = _ax;
  _dl = memory[adr(_ds, 0x3966)];
  memory[adr(_ds, 0x39C5)] = _dl;
  if (_dl != 0x08)
    goto loc_3D25;
  _ax &= 0xfff8;
  _dx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0xfff8;
  if (_ax != _dx)
    goto loc_3D0D;
  memory[adr(_ds, 0x3967)] = 1;
  memory[adr(_ds, 0x396E)] = 1;
  goto loc_3D25;
loc_3D0D:
  _ax = *(WORD*)&memory[adr(_ds, 0x3964)];
  if (_ax < _dx)
    goto loc_3D1C;
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x39C6)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x39C6)];
  if (!flags.carry)
    goto loc_3D20;
  _ax = 0;
  goto loc_3D20;
loc_3D1C:
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x39C6)];
loc_3D20:
  *(WORD*)&memory[adr(_ds, 0x3964)] = _ax;
  goto loc_3D79;
loc_3D25:
  _al = memory[adr(_ds, 0x3966)];
  memory[adr(_ds, 0x396E)] += 1;
  _dl = (((memory[adr(_ds, 0x396E)]) >> 2) & 0x03) + 0x02;
  if (memory[adr(_ds, 0x3967)] == 1)
    goto loc_3D52;
  flags.carry = _al < _dl;
  _al -= _dl;
  if (flags.carry)
    goto loc_3D49;
  if (_al >= 0x09)
    goto loc_3D76;
loc_3D49:
  _al = 0x08;
  memory[adr(_ds, 0x3967)] = 0;
  goto loc_3D76;
loc_3D52:
  _al += _dl;
  if (_al > memory[adr(_ds, 0x57B)])
    goto loc_3D71;
  _bx = *(WORD*)&memory[adr(_ds, 0x3964)];
  flags.carry = _bx < *(WORD*)&memory[adr(_ds, 0x579)];
  _bx = _bx - *(WORD*)&memory[adr(_ds, 0x579)];
  if (!flags.carry)
    goto loc_3D66;
  _bx = (~_bx);
loc_3D66:
  if (_bx > 0x30)
    goto loc_3D71;
  if (_al < 0xa0)
    goto loc_3D76;
  _al = 0x9f;
loc_3D71:
  memory[adr(_ds, 0x3967)] = 0xff;
loc_3D76:
  memory[adr(_ds, 0x3966)] = _al;
loc_3D79:
  sub_3E52();
  if (!flags.carry)
    goto loc_3D8B;
  _ax = *(WORD*)&memory[adr(_ds, 0x39C3)];
  *(WORD*)&memory[adr(_ds, 0x3964)] = _ax;
  _al = memory[adr(_ds, 0x39C5)];
  memory[adr(_ds, 0x3966)] = _al;
  return;
loc_3D8B:
  sub_3E6E();
  if (!flags.carry)
    goto loc_3DEE;
loc_3D90:
  if (memory[adr(_ds, 0x553)] == 0)
    goto loc_3D98;
  return;
loc_3D98:
  _cx = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _cx < 0x0c;
  _cx -= 0x0c;
  if (!flags.carry)
    goto loc_3DA3;
  _cx = 0;
loc_3DA3:
  if (_cx < 0x010f)
    goto loc_3DAC;
  _cx = 0x010e;
loc_3DAC:
  _dl = memory[adr(_ds, 0x57B)];
  flags.carry = _dl < 0x04;
  _dl -= 0x04;
  if (!flags.carry)
    goto loc_3DB7;
  _dl = 0;
loc_3DB7:
  sub_2CB0();
  _di = _ax;
  _ax = 0xb800;
  _es = _ax;
  _si = 0x37c0;
  _bp = 0x0e;
  _cx = 0x1506;
  sub_2CCC();
  sub_56F4();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x39C8)] = _dx;
loc_3DD8:
  sub_5704();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x39C8)];
  if (_dx < 0x0009)
    goto loc_3DD8;
  memory[adr(_ds, 0x552)] = 1;
  return;
loc_3DEE:
  _cx = *(WORD*)&memory[adr(_ds, 0x3964)];
  _dl = memory[adr(_ds, 0x3966)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x39CA)] = _ax;
  sub_3E38();
  memory[adr(_ds, 0x396D)] -= 1;
  if (memory[adr(_ds, 0x396D)] != 0)
    goto loc_3E10;
  memory[adr(_ds, 0x396D)] = 2;
  *(WORD*)&memory[adr(_ds, 0x396B)] = *(WORD*)&memory[adr(_ds, 0x396B)] ^ 0x54;
loc_3E10:
  sub_3E14();
}

void sub_3E14()
{
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x39CA)];
  *(WORD*)&memory[adr(_ds, 0x3968)] = _di;
  _bp = 0x396f;
  memory[adr(_ds, 0x396A)] = 0;
  _si = (*(WORD*)&memory[adr(_ds, 0x396B)]) + 0x38bc;
  _cx = 0x0e03;
  sub_2CCC();
}

void sub_3E38()
{
  _ax = 0xb800;
  _es = _ax;
  if (memory[adr(_ds, 0x396A)] != 0)
    return;
  _di = *(WORD*)&memory[adr(_ds, 0x3968)];
  _si = 0x396f;
  _cx = 0x0e03;
  sub_2D9D();
}

void sub_3E52()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x3964)];
  _dl = memory[adr(_ds, 0x3966)];
  _si = 0x18;
  _bx = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dh = memory[adr(_ds, 0x327F)];
  _di = 0x10;
  _cx = 0x1e0e;
  sub_2E29();
}

void sub_3E6E()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x3964)];
  _dl = memory[adr(_ds, 0x3966)];
  _si = 0x18;
  _di = _si;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _cx = 0x0e0e;
  sub_2E29();
}

void sub_3E90()
{
  if (memory[adr(_ds, 0x39E1)] == 0)
    goto loc_3EA4;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x3D16)])
    return;
  goto loc_3F35;
loc_3EA4:
  if (memory[adr(_ds, 0x584)] != 0)
    return;
  if (memory[adr(_ds, 0x69A)] != 0)
    return;
  if (memory[adr(_ds, 0x39E0)] != 0)
    goto loc_3EBA;
  return;
loc_3EBA:
  sub_4065();
  if (flags.carry)
    return;
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x3D18)];
  if (_ax < 0x0c)
    return;
  *(WORD*)&memory[adr(_ds, 0x3D18)] = _dx;
  memory[adr(_ds, 0x55C)] = 0;
  _bl = (memory[adr(_ds, 0x39E0)]) - 1;
  _bh = 0;
  _si = _bx;
  _cl = 0x02;
  _si <<= _cl;
  _ax = *(WORD*)&memory[adr(_ds, _si + 15450)];
  *(WORD*)&memory[adr(_ds, 0x39E2)] = _ax;
  _ax = 0;
  if (_bl >= 0x03)
    goto loc_3EF5;
  _al = 0x80;
loc_3EF5:
  *(WORD*)&memory[adr(_ds, 0x39E4)] = _ax;
  _bl = memory[adr(_ds, _bx + 15587)];
  _si = _bx;
  _cl = 0x02;
  _si <<= _cl;
  _ax = *(WORD*)&memory[adr(_ds, _si + 15450)];
  *(WORD*)&memory[adr(_ds, 0x39E6)] = _ax;
  _ax = 0;
  if (_bl >= 0x03)
    goto loc_3F12;
  _al = 0x80;
loc_3F12:
  *(WORD*)&memory[adr(_ds, 0x39E8)] = _ax;
  _al = memory[adr(_ds, _bx + 4176)];
  memory[adr(_ds, 0x3D05)] = _al;
  _bl <<= 1;
  _ax = (*(WORD*)&memory[adr(_ds, _bx + 4407)]) + 0x0008;
  *(WORD*)&memory[adr(_ds, 0x3D03)] = _ax;
  sub_11E3();
  memory[adr(_ds, 0x39E1)] = 0x0e;
  memory[adr(_ds, 0x69A)] = 0x10;
loc_3F35:
  if (memory[adr(_ds, 0x1CBF)] != 0)
    goto loc_3F3F;
  sub_33A0();
loc_3F3F:
  memory[adr(_ds, 0x39E1)] -= 2;
  _bh = 0;
  _bl = memory[adr(_ds, 0x39E1)];
  if (_bl < 0x08)
    goto loc_3F58;
  _di = *(WORD*)&memory[adr(_ds, 0x39E2)];
  _ax = *(WORD*)&memory[adr(_ds, 0x39E4)];
  goto loc_3F70;
loc_3F58:
  _di = *(WORD*)&memory[adr(_ds, 0x39E6)];
  _al = memory[adr(_ds, 0x3D05)];
  memory[adr(_ds, 0x57B)] = _al;
  _al += 0x32;
  memory[adr(_ds, 0x57C)] = _al;
  _ax = *(WORD*)&memory[adr(_ds, 0x3D03)];
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x39E8)];
loc_3F70:
  _ax = _ax + *(WORD*)&memory[adr(_ds, _bx + 15622)];
  _si = _ax;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x1002;
  sub_2D9D();
  if (memory[adr(_ds, 0x1CBF)] != 0)
    goto loc_3F8B;
  sub_3339();
loc_3F8B:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x3D16)] = _dx;
  if (memory[adr(_ds, 0x39E1)] != 0)
    return;
  sub_1112();
}

void sub_3F9E()
{
  _ax = 0xb800;
  _es = _ax;
  memory[adr(_ds, 0x39E0)] = 0;
  memory[adr(_ds, 0x39E1)] = 0;
  *(WORD*)&memory[adr(_ds, 0x3CBF)] = 1286;
  *(WORD*)&memory[adr(_ds, 0x3CC1)] = 0;
loc_3FB9:
  _bx = *(WORD*)&memory[adr(_ds, 0x3CC1)];
  _cl = memory[adr(_ds, _bx + 15534)];
  _bx = 0;
  _ch = _bl;
loc_3FC5:
  _si = 0x3aea;
  sub_2DFD();
  if (_dl > 0x30)
    goto loc_3FDB;
  _si = 0x3af8;
  if (_dl & 0x04)
    goto loc_3FDB;
  _si = 0x3b02;
loc_3FDB:
  _di = (*(WORD*)&memory[adr(_ds, 0x3CBF)]) + _bx;
  _push(_cx);
  _push(_bx);
  _cx = 0x0801;
  sub_2D9D();
  _bx = _pop();
  _cx = _pop();
  _bx += 0x0002;
  if (--_cx)
    goto loc_3FC5;
  *(WORD*)&memory[adr(_ds, 0x3CBF)] += 320;
  *(WORD*)&memory[adr(_ds, 0x3CC1)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x3CC1)] < 0x11)
    goto loc_3FB9;
  _bx = 0x3c22;
  _ax = 0;
  sub_2B24();
  _bx = 0x3c3e;
  _ax = 0;
  sub_2B24();
  _bx = 0x3c9a;
  _ax = 0;
  sub_2B24();
  _bx = 0x3c56;
  _ax = 0;
  sub_2B24();
  _si = 0x3caa;
  _di = 0x08ec;
  _cx = 0x0102;
  _bp = 0x0e;
  sub_2D35();
  _si = 0;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _cl = 0x03;
  _bl = (_bl & _cl) << _cl;
loc_403C:
  _al = memory[adr(_ds, _bx + 15555)];
  _ah = _al;
  _cl = 0x04;
  _al >>= _cl;
  memory[adr(_ds, _si + 15587)] = _al;
  memory[adr(_ds, _si + 15603)] = 0;
  _ah &= 0x0f;
  memory[adr(_ds, _si + 15588)] = _ah;
  memory[adr(_ds, _si + 15604)] = 0;
  _si += 0x0002;
  _bx += 1;
  if (_si < 0x10)
    goto loc_403C;
}

void sub_4065()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dl = memory[adr(_ds, 0x327F)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e1e;
  sub_2E29();
}

void sub_4090()
{
  _cx = 0x0004;
loc_4093:
  _bx = _cx - 1;
  _si = _bx << 1;
  memory[adr(_ds, _bx + 16046)] = 1;
  memory[adr(_ds, _bx + 16050)] = 0;
  sub_4277();
  sub_2DFD();
  _dl = (_dl & 0x0f) + 0x14;
  memory[adr(_ds, _bx + 16054)] = _dl;
  if (--_cx)
    goto loc_4093;
  *(WORD*)&memory[adr(_ds, 0x3EDA)] = 0;
  memory[adr(_ds, 0x3ED8)] = 4;
}

void sub_40C2()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x3EDC)])
    goto loc_40CD;
  return;
loc_40CD:
  *(WORD*)&memory[adr(_ds, 0x3EDA)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x3EDA)];
  if (_bx <= 0x0002)
    goto loc_40E5;
  if (_bx < 0x0004)
    goto loc_40E9;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x3EDA)] = _bx;
loc_40E5:
  *(WORD*)&memory[adr(_ds, 0x3EDC)] = _dx;
loc_40E9:
  _si = _bx << 1;
  if (memory[adr(_ds, _bx + 16050)] != 0)
    return;
  sub_42DB();
  if (!flags.carry)
    goto loc_40FC;
  goto loc_4124;
loc_40FC:
  sub_42FC();
  if (flags.carry)
    return;
  if (memory[adr(_ds, _bx + 16054)] != 0)
    goto loc_4118;
  sub_4277();
  sub_2DFD();
  _dl = (_dl & 0x07) + 0x14;
  memory[adr(_ds, _bx + 16054)] = _dl;
loc_4118:
  memory[adr(_ds, _bx + 16054)] -= 1;
  sub_42DB();
  if (flags.carry)
    goto loc_4124;
  goto loc_4181;
loc_4124:
  if (memory[adr(_ds, _bx + 16046)] != 0)
    return;
  if (memory[adr(_ds, _bx + 16054)] < 0x14)
    goto loc_4133;
  return;
loc_4133:
  sub_11E3();
  sub_4254();
  _bx = *(WORD*)&memory[adr(_ds, 0x3EDA)];
  memory[adr(_ds, _bx + 16050)] = 1;
  sub_1124();
  memory[adr(_ds, 0x55C)] = 0;
  memory[adr(_ds, 0x3ED8)] -= 1;
  if (memory[adr(_ds, 0x3ED8)] != 0)
    goto loc_4155;
  memory[adr(_ds, 0x553)] = 1;
loc_4155:
  _al = 0x04 - memory[adr(_ds, 0x3ED8)];
  _cl = 0x02;
  _al <<= _cl;
  _ah = 0;
  _ax += 0x51;
  _di = _ax;
  _bp = 0x0e;
  _si = 0x3d20;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0c02;
  sub_2D35();
  _ax = 0x03e8;
  _bx = 0x02ee;
  sub_593B();
  return;
loc_4181:
  sub_42B4();
  _di = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  _bp = *(WORD*)&memory[adr(_ds, _di + 16094)];
  sub_431C();
  if (!flags.carry)
    goto loc_41B0;
  if (memory[adr(_ds, _bx + 16054)] < 2)
    goto loc_41B0;
  _al = 0x01;
  if (memory[adr(_ds, _bx + 16054)] <= 0x11)
    goto loc_41AC;
  if (memory[adr(_ds, _bx + 16054)] >= 0x14)
    goto loc_41B0;
  _al -= 1;
loc_41AC:
  memory[adr(_ds, _bx + 16054)] = _al;
loc_41B0:
  _al = memory[adr(_ds, _bx + 16054)];
  if (_al <= 0x01)
    goto loc_41D8;
  if (_al < 0x12)
    goto loc_41F8;
  _al = 0x01;
  if (*(WORD*)&memory[adr(_ds, _si + 16058)] >= 3)
    goto loc_41C7;
  _al = 0x03;
loc_41C7:
  memory[adr(_ds, _bx + 16084)] += _al;
  if (memory[adr(_ds, _bx + 16054)] < 0x13)
    goto loc_41F3;
  if (memory[adr(_ds, _bx + 16054)] == 0x13)
    goto loc_41EE;
  _ax = 0;
  goto loc_4204;
loc_41D8:
  _al = 0x01;
  if (*(WORD*)&memory[adr(_ds, _si + 16058)] >= 3)
    goto loc_41E3;
  _al = 0x03;
loc_41E3:
  memory[adr(_ds, _bx + 16084)] += _al;
  if (memory[adr(_ds, _bx + 16054)] >= 1)
    goto loc_41F3;
loc_41EE:
  _ax = 0x3db0;
  goto loc_4204;
loc_41F3:
  _ax = 0x3d80;
  goto loc_4204;
loc_41F8:
  _al <<= 1;
  _di = _ax & 0x0002;
  _ax = *(WORD*)&memory[adr(_ds, _di + 15840)];
loc_4204:
  *(WORD*)&memory[adr(_ds, 0x3ECA)] = _ax;
  _dl = memory[adr(_ds, _bx + 16084)];
  _cx = *(WORD*)&memory[adr(_ds, _si + 16076)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x3DE4)] = _ax;
  sub_4254();
  _bx = *(WORD*)&memory[adr(_ds, 0x3EDA)];
  _si = _bx << 1;
  sub_42FC();
  if (!flags.carry)
    goto loc_4226;
  return;
loc_4226:
  if (*(WORD*)&memory[adr(_ds, 0x3ECA)] != 0)
    goto loc_4233;
  memory[adr(_ds, _bx + 16046)] = 1;
  return;
loc_4233:
  memory[adr(_ds, _bx + 16046)] = 0;
  _di = *(WORD*)&memory[adr(_ds, 0x3DE4)];
  *(WORD*)&memory[adr(_ds, _si + 16038)] = _di;
  _ax = 0xb800;
  _es = _ax;
  _bp = *(WORD*)&memory[adr(_ds, _si + 16066)];
  _cx = 0x0c02;
  _si = *(WORD*)&memory[adr(_ds, 0x3ECA)];
  sub_2D35();
}

void sub_4254()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x3EDA)];
  _si = _bx << 1;
  if (memory[adr(_ds, _bx + 16046)] != 0)
    return;
  _di = *(WORD*)&memory[adr(_ds, _si + 16038)];
  _cx = 0x0c02;
  _si = *(WORD*)&memory[adr(_ds, _si + 16066)];
  _ax = 0xb800;
  _es = _ax;
  sub_2D9D();
}

void sub_4277()
{
  memory[adr(_ds, 0x3ED9)] = 0x20;
loc_427C:
  sub_2DFD();
  _dx &= 0x0f;
  _di = 0;
loc_4285:
  if (_di == _si)
    goto loc_428F;
  if (_dx == *(WORD*)&memory[adr(_ds, _di + 16058)])
    goto loc_427C;
loc_428F:
  _di += 0x0002;
  if (_di < 0x0008)
    goto loc_4285;
  *(WORD*)&memory[adr(_ds, _si + 16058)] = _dx;
  sub_42B4();
  if (memory[adr(_ds, 0x3ED9)] == 0)
    return;
  _bp = 0x32;
  sub_431C();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x3ED9)] -= 1;
  goto loc_427C;
}

void sub_42B4()
{
  _di = *(WORD*)&memory[adr(_ds, _si + 16058)];
  _al = memory[adr(_ds, _di + 4176)];
  _dl = 0x0a;
  if (_di >= 0x0003)
    goto loc_42C5;
  _dl = 0;
loc_42C5:
  _al = (_al - _dl) + 0x03;
  memory[adr(_ds, _bx + 16084)] = _al;
  _di <<= 1;
  _ax = (*(WORD*)&memory[adr(_ds, _di + 4407)]) + 0x0008;
  *(WORD*)&memory[adr(_ds, _si + 16076)] = _ax;
}

void sub_42DB()
{
  _push(_si);
  _push(_bx);
  _ax = *(WORD*)&memory[adr(_ds, _si + 16076)];
  _dl = memory[adr(_ds, _bx + 16084)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e0c;
  sub_2E29();
  _bx = _pop();
  _si = _pop();
}

void sub_42FC()
{
  _push(_si);
  _push(_bx);
  _ax = *(WORD*)&memory[adr(_ds, _si + 16076)];
  _dl = memory[adr(_ds, _bx + 16084)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dh = memory[adr(_ds, 0x327F)];
  _di = _si;
  _cx = 0x1e0c;
  sub_2E29();
  _bx = _pop();
  _si = _pop();
}

void sub_431C()
{
  _ax = *(WORD*)&memory[adr(_ds, _si + 16076)];
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x579)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x579)];
  if (!flags.carry)
    goto loc_4328;
  _ax = (~_ax);
loc_4328:
  _dl = memory[adr(_ds, _bx + 16084)];
  flags.carry = _dl < memory[adr(_ds, 0x57B)];
  _dl = _dl - memory[adr(_ds, 0x57B)];
  if (!flags.carry)
    goto loc_4334;
  _dl = (~_dl);
loc_4334:
  _dh = 0;
  _ax += _dx;
  if (_ax < _bp)
    goto loc_433E;
  flags.carry = false;
  return;
loc_433E:
  flags.carry = true;
}

void sub_4340()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x40B5)])
    goto loc_434B;
  return;
loc_434B:
  memory[adr(_ds, 0x40FF)] += 1;
  if (!(memory[adr(_ds, 0x40FF)] & 3))
    goto loc_435A;
  *(WORD*)&memory[adr(_ds, 0x40B5)] = _dx;
loc_435A:
  if (memory[adr(_ds, 0x40AA)] < 0xa4)
    return;
  sub_452D();
  sub_4557();
  if (flags.carry)
    return;
  sub_2DFD();
  if (_dl > 0x30)
    goto loc_439C;
  sub_44FB();
  _si = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  _ax = *(WORD*)&memory[adr(_ds, _si + 16590)];
  if (*(WORD*)&memory[adr(_ds, 0x40CC)] > _ax)
    goto loc_439C;
  sub_595D();
  *(WORD*)&memory[adr(_ds, 0x40C8)] = 0xff;
  _al = memory[adr(_ds, 0x40CA)];
  memory[adr(_ds, 0x40B7)] = _al;
  _al = memory[adr(_ds, 0x40CB)];
  memory[adr(_ds, 0x40B8)] = _al;
  goto loc_442E;
loc_439C:
  if (*(WORD*)&memory[adr(_ds, 0x40C8)] > 0x0a)
    goto loc_4402;
  sub_2DFD();
  if (_dl > 0x06)
    goto loc_43B4;
  *(WORD*)&memory[adr(_ds, 0x40C8)] = 0xff;
  goto loc_4402;
loc_43B4:
  _bx = *(WORD*)&memory[adr(_ds, 0x40C8)];
  _si = _bx << 1;
  _dl = 0;
  _ax = (*(WORD*)&memory[adr(_ds, 0x40B2)]) & 0x0ffc;
  if (_ax == *(WORD*)&memory[adr(_ds, _si + 16606)])
    goto loc_43D0;
  _dl += 1;
  if ((char)_dl < 0)
    goto loc_43D0;
  _dl = 0xff;
loc_43D0:
  memory[adr(_ds, 0x40B7)] = _dl;
  _dl = 0;
  _al = (memory[adr(_ds, 0x40B4)]) & 0xfe;
  if (_al == memory[adr(_ds, _bx + 16628)])
    goto loc_43E7;
  _dl += 1;
  if ((char)_dl < 0)
    goto loc_43E7;
  _dl = 0xff;
loc_43E7:
  memory[adr(_ds, 0x40B8)] = _dl;
  _dl = _dl | memory[adr(_ds, 0x40B7)];
  if (_dl != 0)
    goto loc_442E;
  sub_2DFD();
  if (_dl > 0x10)
    goto loc_442E;
  *(WORD*)&memory[adr(_ds, 0x40C8)] = 0xff;
  sub_595D();
loc_4402:
  sub_2DFD();
  if (_dl > 0x30)
    goto loc_4423;
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_4411;
  _dl = 0xff;
loc_4411:
  memory[adr(_ds, 0x40B7)] = _dl;
  sub_2DFD();
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_441F;
  _dl = 0xff;
loc_441F:
  memory[adr(_ds, 0x40B8)] = _dl;
loc_4423:
  sub_2DFD();
  _dx &= 0xff;
  *(WORD*)&memory[adr(_ds, 0x40C8)] = _dx;
loc_442E:
  _al = memory[adr(_ds, 0x40B4)];
  if (memory[adr(_ds, 0x40B8)] < 1)
    goto loc_4459;
  if (memory[adr(_ds, 0x40B8)] != 1)
    goto loc_4449;
  _al += 0x02;
  if (_al < 0xa8)
    goto loc_4456;
  _al = 0xa7;
  memory[adr(_ds, 0x40B8)] = 0xff;
  goto loc_4456;
loc_4449:
  _al -= 0x02;
  if (_al >= 0x30)
    goto loc_4456;
  _al = 0x30;
  memory[adr(_ds, 0x40B8)] = 1;
loc_4456:
  memory[adr(_ds, 0x40B4)] = _al;
loc_4459:
  _ax = *(WORD*)&memory[adr(_ds, 0x40B2)];
  if (memory[adr(_ds, 0x40B7)] < 1)
    goto loc_4486;
  if (memory[adr(_ds, 0x40B7)] != 1)
    goto loc_4477;
  _ax += 0x0004;
  if (_ax < 0x0136)
    goto loc_4483;
  _ax = 0x0135;
  memory[adr(_ds, 0x40B7)] = 0xff;
  goto loc_4483;
loc_4477:
  flags.carry = _ax < 0x0004;
  _ax -= 0x0004;
  if (!flags.carry)
    goto loc_4483;
  _ax = 0;
  memory[adr(_ds, 0x40B7)] = 1;
loc_4483:
  *(WORD*)&memory[adr(_ds, 0x40B2)] = _ax;
loc_4486:
  sub_452D();
  _cx = *(WORD*)&memory[adr(_ds, 0x40B2)];
  _dl = memory[adr(_ds, 0x40B4)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x40BC)] = _ax;
  _ax = 0xb800;
  _es = _ax;
  if (memory[adr(_ds, 0x40B9)] != 0)
    goto loc_44B0;
  _si = 0x3f2c;
  _di = *(WORD*)&memory[adr(_ds, 0x40BA)];
  _cx = 0x0501;
  sub_2D9D();
loc_44B0:
  sub_4557();
  if (flags.carry)
    return;
  memory[adr(_ds, 0x40B9)] = 0;
  *(WORD*)&memory[adr(_ds, 0x40BE)] += 2;
  _bx = (*(WORD*)&memory[adr(_ds, 0x40BE)]) & 0x0006;
  _si = *(WORD*)&memory[adr(_ds, _bx + 16576)];
  if (memory[adr(_ds, 0x40B7)] != 0xff)
    goto loc_44D5;
  _si += 0x1e;
loc_44D5:
  _di = *(WORD*)&memory[adr(_ds, 0x40BC)];
  *(WORD*)&memory[adr(_ds, 0x40BA)] = _di;
  _bp = 0x3f2c;
  _cx = 0x0501;
  sub_2CCC();
}

void sub_44E7()
{
  if (memory[adr(_ds, 0x571)] != 0)
    goto loc_44F9;
  _al = (memory[adr(_ds, 0x57B)]) & 0xf8;
  if (_al != 0x88)
    goto loc_44F9;
  flags.carry = true;
  return;
loc_44F9:
  flags.carry = false;
}

void sub_44FB()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x40B2)];
  _dl = 0x01;
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x579)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x579)];
  if (!flags.carry)
    goto loc_450A;
  _ax = (~_ax);
  _dl = 0xff;
loc_450A:
  memory[adr(_ds, 0x40CA)] = _dl;
  *(WORD*)&memory[adr(_ds, 0x40CC)] = _ax;
  _al = memory[adr(_ds, 0x40B4)];
  _dl = 0x01;
  flags.carry = _al < memory[adr(_ds, 0x57B)];
  _al = _al - memory[adr(_ds, 0x57B)];
  if (!flags.carry)
    goto loc_4520;
  _al = (~_al);
  _dl = 0xff;
loc_4520:
  memory[adr(_ds, 0x40CB)] = _dl;
  _ah = 0;
  _ax <<= 1;
  *(WORD*)&memory[adr(_ds, 0x40CC)] += _ax;
}

void sub_452D()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x40B2)];
  _dl = memory[adr(_ds, 0x40B4)];
  _si = 0x0008;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e05;
  sub_2E29();
  if (!flags.carry)
    return;
  if (memory[adr(_ds, 0x552)] != 0)
    return;
  memory[adr(_ds, 0x553)] = 1;
}

void sub_4557()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x40B2)];
  _dl = memory[adr(_ds, 0x40B4)];
  _si = 0x0008;
  _bx = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dh = memory[adr(_ds, 0x327F)];
  _di = 0x10;
  _cx = 0x1e05;
  sub_2E29();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x40B8)] = 0xff;
}

void sub_457A()
{
  _cx = 0x90;
  _dl = 0x86;
  *(WORD*)&memory[adr(_ds, 0x40A8)] = _cx;
  memory[adr(_ds, 0x40AA)] = _dl;
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x40AB)] = _ax;
  sub_4759();
  memory[adr(_ds, 0x40AF)] = 0;
  memory[adr(_ds, 0x40B1)] = 0;
  memory[adr(_ds, 0x40B9)] = 1;
  memory[adr(_ds, 0x40B8)] = 0;
  *(WORD*)&memory[adr(_ds, 0x40C8)] = 0xff;
}

void sub_45AB()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x40AD)])
    goto loc_45B6;
  return;
loc_45B6:
  *(WORD*)&memory[adr(_ds, 0x40AD)] = _dx;
  if (memory[adr(_ds, 0x40AA)] >= 0xa4)
    return;
  sub_4786();
  if (!flags.carry)
    goto loc_45D6;
  sub_44E7();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x55B)] = 0x10;
  return;
loc_45D6:
  sub_473E();
  if (!flags.carry)
    goto loc_4649;
  if (memory[adr(_ds, 0x40AF)] != 0)
    goto loc_45FA;
  _al = memory[adr(_ds, 0x56E)];
  if (_al != 0x00)
    goto loc_45F7;
  _al += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x40A8)];
  if (_bx > *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_45F7;
  _al = 0xff;
loc_45F7:
  memory[adr(_ds, 0x40B0)] = _al;
loc_45FA:
  memory[adr(_ds, 0x40AF)] = 1;
  _cx = 0x20;
loc_4602:
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = 0x01;
  if (memory[adr(_ds, 0x40B0)] != 1)
    goto loc_4615;
  _ax -= 0x0008;
  _dl = 0xff;
  goto loc_4618;
loc_4615:
  _ax += 0x0008;
loc_4618:
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  memory[adr(_ds, 0x56E)] = _dl;
  _al = memory[adr(_ds, 0x57B)];
  if (memory[adr(_ds, 0x571)] < 1)
    goto loc_4639;
  if (memory[adr(_ds, 0x571)] != 1)
    goto loc_462F;
  _al -= 0x03;
  goto loc_4631;
loc_462F:
  _al += 0x03;
loc_4631:
  memory[adr(_ds, 0x57B)] = _al;
  _al += 0x32;
  memory[adr(_ds, 0x57C)] = _al;
loc_4639:
  _push(_cx);
  sub_473E();
  _cx = _pop();
  if (!flags.carry)
    goto loc_4642;
  if (--_cx)
    goto loc_4602;
loc_4642:
  sub_11E3();
  sub_1112();
  return;
loc_4649:
  if (memory[adr(_ds, 0x40B1)] != 0)
    goto loc_46A2;
  if (memory[adr(_ds, 0x40AF)] == 0)
    return;
  _ax = *(WORD*)&memory[adr(_ds, 0x40A8)];
  if (memory[adr(_ds, 0x40B0)] != 1)
    goto loc_4666;
  _ax += 0x0008;
  goto loc_4669;
loc_4666:
  _ax -= 0x0008;
loc_4669:
  *(WORD*)&memory[adr(_ds, 0x40A8)] = _ax;
  sub_473E();
  if (!flags.carry)
    goto loc_4672;
  return;
loc_4672:
  _ax = 0x0c00;
  _bx = 0x0b54;
  sub_593B();
  memory[adr(_ds, 0x40AF)] = 0;
  _cx = *(WORD*)&memory[adr(_ds, 0x40A8)];
  _dl = memory[adr(_ds, 0x40AA)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x40AB)] = _ax;
  sub_4773();
  sub_4759();
  _ax = *(WORD*)&memory[adr(_ds, 0x40A8)];
  if (_ax < 0x78)
    goto loc_46A2;
  if (_ax > 0xa8)
    goto loc_46A2;
  return;
loc_46A2:
  memory[adr(_ds, 0x40B1)] = 1;
  if (memory[adr(_ds, 0x1CBF)] == 0)
    goto loc_46BE;
  sub_44E7();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x55B)] = 0x10;
  return;
loc_46BE:
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x40AD)])
    goto loc_46A2;
  *(WORD*)&memory[adr(_ds, 0x40AD)] = _dx;
  if (memory[adr(_ds, 0x0)] == 0)
    goto loc_46EC;
  _al = 0xb6;
  _out(0x43, _al);
  _al = memory[adr(_ds, 0x40AA)];
  _ah = 0;
  _ax = (_ax << 1) << 1;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
loc_46EC:
  _dl = memory[adr(_ds, 0x40AA)];
  if (_dl >= 0xa4)
    goto loc_470E;
  _dl += 0x05;
  memory[adr(_ds, 0x40AA)] = _dl;
  _cx = *(WORD*)&memory[adr(_ds, 0x40A8)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x40AB)] = _ax;
  sub_4773();
  sub_4759();
  goto loc_46BE;
loc_470E:
  sub_5B21();
  sub_4773();
  _bp = 0x401e;
  *(WORD*)&memory[adr(_ds, 0x40A6)] -= 1;
  _di = *(WORD*)&memory[adr(_ds, 0x40A6)];
  _si = 0x3f36;
  _cx = 0x1104;
  sub_2D35();
  _ax = *(WORD*)&memory[adr(_ds, 0x40A8)];
  *(WORD*)&memory[adr(_ds, 0x40B2)] = _ax;
  _al = memory[adr(_ds, 0x40AA)];
  memory[adr(_ds, 0x40B4)] = _al;
  sub_44FB();
  _al = memory[adr(_ds, 0x40CA)];
  memory[adr(_ds, 0x40B7)] = _al;
}

void sub_473E()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x40A8)];
  _dl = memory[adr(_ds, 0x40AA)];
  _si = 0x18;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = _si;
  _cx = 0x0e10;
  sub_2E29();
}

void sub_4759()
{
  _ax = 0xb800;
  _es = _ax;
  _bp = 0x401e;
  _si = 0x3fbe;
  _di = *(WORD*)&memory[adr(_ds, 0x40AB)];
  *(WORD*)&memory[adr(_ds, 0x40A6)] = _di;
  _cx = 0x1003;
  sub_2D35();
}

void sub_4773()
{
  _ax = 0xb800;
  _es = _ax;
  _si = 0x401e;
  _di = *(WORD*)&memory[adr(_ds, 0x40A6)];
  _cx = 0x1003;
  sub_2D9D();
}

void sub_4786()
{
  if (memory[adr(_ds, 0x327F)] < 0x66)
    goto loc_47A4;
  _ax = (*(WORD*)&memory[adr(_ds, 0x40A8)]) - 0x14;
  if (_ax > *(WORD*)&memory[adr(_ds, 0x327D)])
    goto loc_47A4;
  _ax += 0x30;
  if (_ax < *(WORD*)&memory[adr(_ds, 0x327D)])
    goto loc_47A4;
  flags.carry = true;
  return;
loc_47A4:
  flags.carry = false;
}

void sub_47B0()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x327D)];
  _dl = memory[adr(_ds, 0x327F)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  flags.carry = _bx < 0x0008;
  _bx -= 0x0008;
  if (!flags.carry)
    goto loc_47C5;
  _bx = 0;
loc_47C5:
  _dh = (memory[adr(_ds, 0x57B)]) + 0x03;
  _di = 0x28;
  _cx = 0x0e1e;
  sub_2E29();
}

void sub_47D6()
{
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x44D7)];
  _si = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  if (_ax > *(WORD*)&memory[adr(_ds, _si + 17628)])
    goto loc_47ED;
  return;
loc_47ED:
  *(WORD*)&memory[adr(_ds, 0x44D7)] = _dx;
  if (memory[adr(_ds, 0x1CB8)] != 0)
    return;
  memory[adr(_ds, 0x44FC)] = 0;
  _cx = 0x0c;
loc_4800:
  _bx = _cx - 1;
  _bl <<= 1;
  if (*(WORD*)&memory[adr(_ds, _bx + 17473)] == 0)
    goto loc_487D;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17401)];
  if (_al != memory[adr(_ds, 0x57B)])
    goto loc_485D;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17377)];
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x579)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x579)];
  if (!flags.carry)
    goto loc_4822;
  _ax = (~_ax);
loc_4822:
  _si = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  if (_ax > *(WORD*)&memory[adr(_ds, _si + 17644)])
    goto loc_485D;
  if (*(WORD*)&memory[adr(_ds, _bx + 17497)] < 2)
    goto loc_484C;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17425)];
  *(WORD*)&memory[adr(_ds, 0x44DA)] = _ax;
  sub_488D();
  sub_48A1();
  sub_3339();
  sub_1145();
  sub_2136();
  return;
loc_484C:
  *(WORD*)&memory[adr(_ds, _bx + 17497)] += 1;
  if (*(WORD*)&memory[adr(_ds, _bx + 17497)] < 2)
    goto loc_4870;
  memory[adr(_ds, 0x44FC)] += 1;
  goto loc_4870;
loc_485D:
  if (*(WORD*)&memory[adr(_ds, _bx + 17497)] == 0)
    goto loc_487D;
  sub_2DFD();
  if (_dl > 0x38)
    goto loc_4870;
  *(WORD*)&memory[adr(_ds, _bx + 17497)] -= 1;
loc_4870:
  _push(_cx);
  _push(_bx);
  sub_48D7();
  _bx = _pop();
  sub_4916();
  sub_48C1();
  _cx = _pop();
loc_487D:
  if (--_cx)
    goto loc_4800;
  if (memory[adr(_ds, 0x44FC)] == 0)
    return;
  sub_5691();
  return;
  goto loc_4800;
}

void sub_488D()
{
  if (memory[adr(_ds, 0x44BD)] == 0)
    goto loc_489D;
  sub_4B03();
  memory[adr(_ds, 0x44BD)] = 0;
  return;
loc_489D:
  sub_11E3();
}

void sub_48A1()
{
  _push(_ds);
  _es = _pop();
  flags.direction = false;
  _di = 0x0e;
  _si = _di;
  _ax = 0xaaaa;
  _cx = 0x41;
  _rep_stosw<MemData, DirForward>();
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x44DA)];
  _cx = 0x0d05;
  sub_2D9D();
}

void sub_48C1()
{
  if (memory[adr(_ds, 0x44D9)] == 0)
    return;
  if (memory[adr(_ds, 0x44BD)] == 0)
    goto loc_48D3;
  sub_4B1D();
  return;
loc_48D3:
  sub_1145();
}

void sub_48D7()
{
  memory[adr(_ds, 0x44D9)] = 0;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17377)];
  _dx = *(WORD*)&memory[adr(_ds, _bx + 17401)];
  _ax -= 0x14;
  _si = 0x28;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _cx = 0x0e06;
  _di = 0x18;
  sub_2E29();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x44D9)] = 1;
loc_4902:
  sub_13D8();
  if (_al == 0)
    goto loc_4902;
  if (memory[adr(_ds, 0x44BD)] == 0)
    goto loc_4912;
  sub_4B03();
  return;
loc_4912:
  sub_11E3();
}

void sub_4916()
{
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17425)];
  _si = ((*(WORD*)&memory[adr(_ds, _bx + 17497)]) << 1) + 0x4100;
  _ax += 0xa7;
  if (*(WORD*)&memory[adr(_ds, _bx + 17449)] == 17052)
    goto loc_4935;
  _ax -= 0x0006;
  _si += 0x0006;
loc_4935:
  _di = _ax;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0101;
  sub_2D9D();
}

void sub_4943()
{
  if (memory[adr(_ds, 0x1CB8)] != 0)
    return;
  if (memory[adr(_ds, 0x44BE)] == 0)
    goto loc_495C;
  _al = memory[adr(_ds, 0x44BE)];
  memory[adr(_ds, 0x698)] = _al;
  memory[adr(_ds, 0x699)] = 0;
loc_495C:
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x44D3)])
    goto loc_4967;
  return;
loc_4967:
  *(WORD*)&memory[adr(_ds, 0x44D3)] = _dx;
  if (memory[adr(_ds, 0x584)] == 0)
    goto loc_4995;
  if (memory[adr(_ds, 0x44BD)] == 0)
    return;
  sub_4B03();
  sub_33A0();
  sub_1124();
  sub_3339();
  memory[adr(_ds, 0x44BD)] = 0;
  memory[adr(_ds, 0x43E0)] = 1;
  memory[adr(_ds, 0x44BE)] = 0;
  return;
loc_4995:
  if (memory[adr(_ds, 0x69A)] == 0)
    goto loc_499F;
  goto loc_49F9;
loc_499F:
  _ax = 0xffff;
  *(WORD*)&memory[adr(_ds, 0x44C1)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x44BF)] = _ax;
  _cx = 0x0c;
  _si = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = (memory[adr(_ds, 0x57B)]) + 0x08;
loc_49B6:
  _bx = _cx - 1;
  if (memory[adr(_ds, _bx + 17604)] < 1)
    goto loc_49F0;
  if (_dl != memory[adr(_ds, _bx + 17561)])
    goto loc_49F0;
  _ax = _si;
  _bl <<= 1;
  _dh = 0xff;
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, _bx + 17537)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, _bx + 17537)];
  if (!flags.carry)
    goto loc_49D6;
  _ax = (~_ax);
  _dh = 0x01;
loc_49D6:
  if (_ax > *(WORD*)&memory[adr(_ds, 0x44BF)])
    goto loc_49F0;
  *(WORD*)&memory[adr(_ds, 0x44BF)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17573)];
  *(WORD*)&memory[adr(_ds, 0x44D1)] = _ax;
  _bl >>= 1;
  *(WORD*)&memory[adr(_ds, 0x44C1)] = _bx;
  memory[adr(_ds, 0x44C3)] = _dh;
loc_49F0:
  if (--_cx)
    goto loc_49B6;
  if (*(WORD*)&memory[adr(_ds, 0x44C1)] < 0x0c)
    goto loc_4A20;
loc_49F9:
  if (memory[adr(_ds, 0x44BD)] == 0)
    goto loc_4A0B;
  sub_4B03();
  sub_1145();
  memory[adr(_ds, 0x69A)] = 0x10;
loc_4A0B:
  memory[adr(_ds, 0x44BD)] = 0;
  memory[adr(_ds, 0x43E0)] = 1;
  memory[adr(_ds, 0x44D0)] = 0;
  memory[adr(_ds, 0x44BE)] = 0;
  return;
loc_4A20:
  if (*(WORD*)&memory[adr(_ds, 0x44BF)] < 4)
    goto loc_4A4B;
  if (*(WORD*)&memory[adr(_ds, 0x44BF)] > 8)
    goto loc_4A33;
  memory[adr(_ds, 0x572)] = 4;
loc_4A33:
  _al = memory[adr(_ds, 0x44C3)];
  memory[adr(_ds, 0x698)] = _al;
  memory[adr(_ds, 0x56E)] = _al;
  memory[adr(_ds, 0x44BE)] = _al;
  memory[adr(_ds, 0x699)] = 0;
  memory[adr(_ds, 0x571)] = 0;
  goto loc_49F9;
loc_4A4B:
  memory[adr(_ds, 0x44BE)] = 0;
  if (memory[adr(_ds, 0x44BD)] != 0)
    goto loc_4A5D;
  sub_11E3();
  sub_1124();
loc_4A5D:
  memory[adr(_ds, 0x44BD)] = 1;
  _al = 0;
  flags.carry = (memory[adr(_ds, 0x44D0)] + 0x30) >= 0x100;
  memory[adr(_ds, 0x44D0)] += 0x30;
  if (!flags.carry)
    goto loc_4A6D;
  _al += 1;
loc_4A6D:
  memory[adr(_ds, 0x44D5)] = _al;
  _cx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0x0ffc;
  _dl = (memory[adr(_ds, 0x57B)]) + 0x03;
  if (*(WORD*)&memory[adr(_ds, 0x44D1)] == 16652)
    goto loc_4A95;
  _cx += 0x0008;
  if (_cx < 0x0127)
    goto loc_4A9C;
  _cx = 0x0126;
  goto loc_4A9C;
loc_4A95:
  flags.carry = _cx < 0x0008;
  _cx -= 0x0008;
  if (!flags.carry)
    goto loc_4A9C;
  _cx = 0;
loc_4A9C:
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x43DC)] = _ax;
loc_4AA2:
  sub_13D8();
  if (_al == 0)
    goto loc_4AA2;
  sub_4B03();
  if (memory[adr(_ds, 0x44D5)] == 0)
    goto loc_4AFF;
  _bx = *(WORD*)&memory[adr(_ds, 0x44C1)];
  if (memory[adr(_ds, _bx + 17604)] == 0)
    goto loc_4AFF;
  memory[adr(_ds, _bx + 17604)] -= 1;
  if (memory[adr(_ds, _bx + 17604)] != 0)
    goto loc_4AE7;
  _push(_bx);
  _ax = 0x08fd;
  _bx = 0x0723;
  sub_593B();
  _bx = _pop();
  memory[adr(_ds, 0x698)] = 0;
  memory[adr(_ds, 0x44BE)] = 0;
  memory[adr(_ds, 0x69A)] = 0x10;
  memory[adr(_ds, 0x44D6)] -= 1;
  if (memory[adr(_ds, 0x44D6)] != 0)
    goto loc_4AE7;
  memory[adr(_ds, 0x553)] = 1;
loc_4AE7:
  _push(_bx);
  sub_47B0();
  _bx = _pop();
  if (!flags.carry)
    goto loc_4AFC;
  _push(_bx);
  sub_33A0();
  _bx = _pop();
  sub_4BC8();
  sub_3339();
  goto loc_4AFF;
loc_4AFC:
  sub_4BC8();
loc_4AFF:
  sub_4B1D();
}

void sub_4B03()
{
  if (memory[adr(_ds, 0x43E0)] != 0)
    return;
  _di = *(WORD*)&memory[adr(_ds, 0x43DE)];
  _si = 0x43a0;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0a03;
  sub_2D9D();
}

void sub_4B1D()
{
  memory[adr(_ds, 0x43E0)] = 0;
  _ax = 0xb800;
  _es = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x43DC)];
  *(WORD*)&memory[adr(_ds, 0x43DE)] = _di;
  _bp = 0x43a0;
  _si = *(WORD*)&memory[adr(_ds, 0x44D1)];
  if (memory[adr(_ds, 0x44D0)] < 0x80)
    goto loc_4B40;
  _si += 0x3c;
loc_4B40:
  _cx = 0x0a03;
  sub_2D35();
}

void sub_4B47()
{
  _push(_ds);
  _es = _pop();
  _ax = 0;
  _di = 0x4441;
  _cx = 0x0c;
  _rep_stosw<MemData, DirForward>();
  _ax = 0xb800;
  _es = _ax;
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _cl = memory[adr(_ds, _bx + 17521)];
  _ch = 0;
loc_4B62:
  sub_2DFD();
  _bl = _dl;
  _bx &= 0x1e;
  if (_bl >= 0x18)
    goto loc_4B62;
  if (*(WORD*)&memory[adr(_ds, _bx + 17473)] != 0)
    goto loc_4B62;
  *(WORD*)&memory[adr(_ds, _bx + 17497)] = 0;
  *(WORD*)&memory[adr(_ds, _bx + 17473)] = 1;
  _push(_cx);
  _si = *(WORD*)&memory[adr(_ds, _bx + 17449)];
  _di = *(WORD*)&memory[adr(_ds, _bx + 17425)];
  _cx = 0x0d05;
  sub_2D9D();
  _cx = _pop();
  if (--_cx)
    goto loc_4B62;
  _cx = 0x0c;
loc_4B98:
  _bx = _cx - 1;
  _si = *(WORD*)&memory[adr(_ds, 0x8)];
  _dl = memory[adr(_ds, _si + 17529)];
  memory[adr(_ds, _bx + 17604)] = _dl;
  _push(_cx);
  sub_4BC8();
  _cx = _pop();
  if (--_cx)
    goto loc_4B98;
  memory[adr(_ds, 0x44D0)] = 0;
  memory[adr(_ds, 0x44BD)] = 0;
  memory[adr(_ds, 0x43E0)] = 1;
  memory[adr(_ds, 0x44D6)] = 0x0c;
  memory[adr(_ds, 0x44BE)] = 0;
}

void sub_4BC8()
{
  sub_4BE8();
  _di = _ax;
  _al = memory[adr(_ds, _bx + 17604)];
  _ah = 0;
  _cl = 0x05;
  _ax = (_ax << _cl) + 0x41fc;
  _si = _ax;
  _cx = 0x0802;
  _ax = 0xb800;
  _es = _ax;
  sub_2D9D();
}

void sub_4BE8()
{
  _push(_bx);
  _dl = memory[adr(_ds, _bx + 17561)];
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 17537)];
  sub_2CB0();
  _bx = _pop();
}

// class CIReturn
// class CIReturn
// class CIReturn
// class CIZeroArgOp
// class CIReturn
// class CIZeroArgOp
// class CIReturn
// class CIReturn
void sub_4C10()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x45B8)])
    goto loc_4C1B;
  return;
loc_4C1B:
  *(WORD*)&memory[adr(_ds, 0x45B6)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  if (_bx == 0x0001)
    goto loc_4C38;
  if (_bx == 0x0004)
    goto loc_4C38;
  if (_bx < 0x0007)
    goto loc_4C3C;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x45B6)] = _bx;
loc_4C38:
  *(WORD*)&memory[adr(_ds, 0x45B8)] = _dx;
loc_4C3C:
  sub_4FCD();
  sub_502D();
  if (!flags.carry)
    goto loc_4C45;
  return;
loc_4C45:
  if (*(WORD*)&memory[adr(_ds, 0x454F)] == 0)
    goto loc_4C8C;
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x454F)];
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 17863)];
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] != 0)
    goto loc_4C67;
  _ax <<= 1;
loc_4C67:
  if (_dx < _ax)
    return;
  *(WORD*)&memory[adr(_ds, 0x454F)] = 0;
  memory[adr(_ds, 0x454E)] = 1;
  _ax = 0x24;
  if (*(WORD*)&memory[adr(_ds, 0x579)] > 0xa0)
    goto loc_4C84;
  _ax = 0x0108;
loc_4C84:
  *(WORD*)&memory[adr(_ds, 0x4548)] = _ax;
  memory[adr(_ds, 0x454A)] = 0;
loc_4C8C:
  sub_4DD0();
  if (!flags.carry)
    goto loc_4C99;
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  sub_4FBB();
  return;
loc_4C99:
  if (memory[adr(_ds, 0x4553)] == 0)
    goto loc_4CB8;
  memory[adr(_ds, 0x4553)] -= 1;
  if (memory[adr(_ds, 0x4553)] != 0)
    goto loc_4D14;
  _dl = 0x01;
  if (memory[adr(_ds, 0x454A)] == 0xff)
    goto loc_4CB1;
  _dl = 0xff;
loc_4CB1:
  memory[adr(_ds, 0x454A)] = _dl;
  goto loc_4D14;
loc_4CB8:
  _al = memory[adr(_ds, 0x454B)];
  if (_al > memory[adr(_ds, 0x57B)])
    goto loc_4D14;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] != 6)
    goto loc_4CCF;
  if (memory[adr(_ds, 0x57B)] < 0x28)
    goto loc_4CDC;
loc_4CCF:
  sub_2DFD();
  _bx = *(WORD*)&memory[adr(_ds, 0x8)];
  if (_dl > memory[adr(_ds, _bx + 17855)])
    goto loc_4D14;
loc_4CDC:
  _dl = 0;
  _ax = (*(WORD*)&memory[adr(_ds, 0x4548)]) & 0x0ff8;
  _cx = (*(WORD*)&memory[adr(_ds, 0x579)]) & 0x0ff8;
  if (_ax == _cx)
    goto loc_4CF6;
  _dl = 0x01;
  if (_ax < _cx)
    goto loc_4CF6;
  _dl = 0xff;
loc_4CF6:
  memory[adr(_ds, 0x454A)] = _dl;
  if (memory[adr(_ds, 0x57B)] < 0x28)
    goto loc_4D14;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] != 6)
    goto loc_4D14;
  _al = 0x01;
  if (_dl == 0xff)
    goto loc_4D11;
  _al = 0xff;
loc_4D11:
  memory[adr(_ds, 0x454A)] = _al;
loc_4D14:
  *(WORD*)&memory[adr(_ds, 0x45BC)] = 8;
  if (memory[adr(_ds, 0x4553)] == 0)
    goto loc_4D27;
  *(WORD*)&memory[adr(_ds, 0x45BC)] = 4;
loc_4D27:
  _ax = *(WORD*)&memory[adr(_ds, 0x4548)];
  if (memory[adr(_ds, 0x454A)] >= 1)
    goto loc_4D46;
  sub_2DFD();
  if (_dl > 0x10)
    goto loc_4DA1;
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_4D40;
  _dl = 0xff;
loc_4D40:
  memory[adr(_ds, 0x454A)] = _dl;
  goto loc_4DA1;
loc_4D46:
  if (memory[adr(_ds, 0x454A)] != 1)
    goto loc_4D60;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x45BC)];
  if (_ax < 0x010b)
    goto loc_4D78;
  _ax = 0x010a;
  memory[adr(_ds, 0x454A)] = 0xff;
  memory[adr(_ds, 0x4553)] = 0;
  goto loc_4D78;
loc_4D60:
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x45BC)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x45BC)];
  if (flags.carry)
    goto loc_4D6B;
  if (_ax > 0x24)
    goto loc_4D78;
loc_4D6B:
  _ax = 0x25;
  memory[adr(_ds, 0x454A)] = 1;
  memory[adr(_ds, 0x4553)] = 0;
loc_4D78:
  *(WORD*)&memory[adr(_ds, 0x4548)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x4551)] += 2;
  if (*(WORD*)&memory[adr(_ds, 0x4551)] < 0x0c)
    goto loc_4D8D;
  *(WORD*)&memory[adr(_ds, 0x4551)] = 0;
loc_4D8D:
  if (memory[adr(_ds, 0x4553)] != 0)
    goto loc_4DA1;
  sub_2DFD();
  if (_dl > 0x08)
    goto loc_4DA1;
  memory[adr(_ds, 0x454A)] = 0;
loc_4DA1:
  _cx = *(WORD*)&memory[adr(_ds, 0x4548)];
  _dl = memory[adr(_ds, 0x454B)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x45BA)] = _ax;
  sub_502D();
  if (!flags.carry)
    goto loc_4DB5;
  return;
loc_4DB5:
  sub_4DD0();
  if (flags.carry)
    goto loc_4DC8;
  sub_4F4A();
  sub_4F10();
  memory[adr(_ds, 0x45BE)] = 0;
  sub_4E75();
loc_4DC8:
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  sub_4FBB();
}

void sub_4DD0()
{
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  _dl = memory[adr(_ds, 0x57B)];
  _si = 0x18;
  _di = _si;
  _bx = *(WORD*)&memory[adr(_ds, 0x4548)];
  _dh = memory[adr(_ds, 0x454B)];
  _cx = 0x0c0e;
  sub_2E29();
  if (!flags.carry)
    return;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] != 6)
    goto loc_4E00;
  memory[adr(_ds, 0x553)] = 1;
  sub_11E3();
  sub_4F4A();
  flags.carry = true;
  return;
loc_4E00:
  sub_11E3();
  sub_4F4A();
  sub_1145();
  memory[adr(_ds, 0x55B)] = 4;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x576)] = 4;
  memory[adr(_ds, 0x578)] = 8;
  memory[adr(_ds, 0x4553)] = 4;
  _dl = 0x01;
  _ax = *(WORD*)&memory[adr(_ds, 0x4548)];
  if (_ax > *(WORD*)&memory[adr(_ds, 0x579)])
    goto loc_4E2F;
  _dl = 0xff;
loc_4E2F:
  memory[adr(_ds, 0x454A)] = _dl;
  _ax = 0x0ce4;
  _bx = 0x123b;
  sub_593B();
  flags.carry = true;
}

void sub_4E3E()
{
  memory[adr(_ds, 0x45BE)] = 1;
  _ax = *(WORD*)&memory[adr(_ds, 0x45B6)];
  _push(_ax);
  *(WORD*)&memory[adr(_ds, 0x45B6)] = 0;
loc_4E4D:
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  sub_4FCD();
  if (*(WORD*)&memory[adr(_ds, 0x454F)] != 0)
    goto loc_4E65;
  sub_4E75();
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  sub_4FBB();
loc_4E65:
  *(WORD*)&memory[adr(_ds, 0x45B6)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] < 7)
    goto loc_4E4D;
  _ax = _pop();
  *(WORD*)&memory[adr(_ds, 0x45B6)] = _ax;
}

void sub_4E75()
{
  _cx = 0x0008;
loc_4E78:
  _bx = _cx - 1;
  if (memory[adr(_ds, _bx + 11122)] == 0)
    goto loc_4EA3;
  _push(_cx);
  _dl = memory[adr(_ds, _bx + 11114)];
  _bl <<= 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  _si = 0x18;
  _di = _si;
  _bx = *(WORD*)&memory[adr(_ds, 0x4548)];
  _dh = memory[adr(_ds, 0x454B)];
  _cx = 0x0c0f;
  sub_2E29();
  _cx = _pop();
  if (flags.carry)
    goto loc_4EA6;
loc_4EA3:
  if (--_cx)
    goto loc_4E78;
  return;
loc_4EA6:
  _push(_cx);
  if (memory[adr(_ds, 0x45BE)] != 0)
    goto loc_4EBB;
  sub_11E3();
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_4EBB;
  sub_622B();
loc_4EBB:
  sub_4F4A();
  _cx = _pop();
  _bx = _cx - 1;
  memory[adr(_ds, _bx + 11122)] = 0;
  _dl = memory[adr(_ds, _bx + 11114)];
  _bl <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _bx + 11098)];
  sub_2CB0();
  _di = _ax;
  _si = 0x2b7a;
  _ax = 0xb800;
  _es = _ax;
  _cx = 0x0f03;
  sub_2D9D();
  if (memory[adr(_ds, 0x45BE)] != 0)
    goto loc_4EF8;
  if (memory[adr(_ds, 0x70F2)] == 0)
    goto loc_4EF5;
  sub_61FA();
loc_4EF5:
  sub_1145();
loc_4EF8:
  _dx = 0;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] == 6)
    goto loc_4F0B;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != 0x0000)
    goto loc_4F0B;
  _dx -= 1;
loc_4F0B:
  *(WORD*)&memory[adr(_ds, 0x454F)] = _dx;
}

void sub_4F10()
{
  memory[adr(_ds, 0x454E)] = 0;
  _si = 0x4500;
  if (memory[adr(_ds, 0x454A)] == 0)
    goto loc_4F3E;
  _bx = *(WORD*)&memory[adr(_ds, 0x4551)];
  if (memory[adr(_ds, 0x4553)] == 0)
    goto loc_4F30;
  _bl = (_bl & 0x02) + 0x0c;
loc_4F30:
  if (memory[adr(_ds, 0x454A)] != 0xff)
    goto loc_4F3A;
  _bx += 0x10;
loc_4F3A:
  _si = *(WORD*)&memory[adr(_ds, _bx + 19040)];
loc_4F3E:
  _di = *(WORD*)&memory[adr(_ds, 0x45BA)];
  *(WORD*)&memory[adr(_ds, 0x454C)] = _di;
  sub_4FDF();
}

void sub_4F4A()
{
  if (memory[adr(_ds, 0x454E)] != 0)
    return;
  _di = *(WORD*)&memory[adr(_ds, 0x454C)];
  sub_5008();
}

void sub_4F59()
{
  *(WORD*)&memory[adr(_ds, 0x45B6)] = 0;
loc_4F5F:
  sub_2DFD();
  _dx = (_dx & 0x7f) + 0x60;
  *(WORD*)&memory[adr(_ds, 0x4548)] = _dx;
  memory[adr(_ds, 0x454A)] = 0;
  memory[adr(_ds, 0x454E)] = 1;
  *(WORD*)&memory[adr(_ds, 0x4551)] = 0;
  memory[adr(_ds, 0x4553)] = 0;
  _dx = 0;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] != 0)
    goto loc_4F95;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != 0x0000)
    goto loc_4F95;
  _dx -= 1;
loc_4F95:
  *(WORD*)&memory[adr(_ds, 0x454F)] = _dx;
  _bx = *(WORD*)&memory[adr(_ds, 0x45B6)];
  _al = (memory[adr(_ds, _bx + 11220)]) + 0x03;
  memory[adr(_ds, 0x454B)] = _al;
  sub_4FBB();
  *(WORD*)&memory[adr(_ds, 0x45B6)] += 1;
  if (*(WORD*)&memory[adr(_ds, 0x45B6)] < 7)
    goto loc_4F5F;
  *(WORD*)&memory[adr(_ds, 0x45B6)] = 0;
}

void sub_4FBB()
{
  _push(_ds);
  _es = _pop();
  _bl <<= 1;
  flags.direction = false;
  _di = *(WORD*)&memory[adr(_ds, _bx + 17832)];
  _si = 0x4548;
  _cx = 0x0c;
  _rep_movsb<MemData, MemData, DirForward>();
}

void sub_4FCD()
{
  _push(_ds);
  _es = _pop();
  _bl <<= 1;
  flags.direction = false;
  _si = *(WORD*)&memory[adr(_ds, _bx + 17832)];
  _di = 0x4548;
  _cx = 0x0c;
  _rep_movsb<MemData, MemData, DirForward>();
}

void sub_4FDF()
{
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  _dh = 0x0c;
loc_4FE7:
  _cx = 0x0003;
loc_4FEA:
  _bx = _videoRead16(_esAssume(0xb800), _di);
  _lodsw<MemData, DirForward>();
  _ax |= _bx;
  _stosw<MemB800, DirForward>();
  if (--_cx)
    goto loc_4FEA;
  _di = (_di - 0x0006) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_5003;
  _di += 0x50;
loc_5003:
  _dh -= 1;
  if (_dh != 0)
    goto loc_4FE7;
}

void sub_5008()
{
  _ax = 0xb800;
  _es = _ax;
  flags.direction = false;
  _dh = 0x0c;
  _ax = 0x5555;
loc_5013:
  _cx = 0x0003;
  _rep_stosw<MemB800, DirForward>();
  _di = (_di - 0x0006) ^ 0x2000;
  if (_di & 0x2000)
    goto loc_5028;
  _di += 0x50;
loc_5028:
  _dh -= 1;
  if (_dh != 0)
    goto loc_5013;
}

void sub_502D()
{
  if (memory[adr(_ds, 0x70F2)] != 0)
    goto loc_5036;
  flags.carry = false;
  return;
loc_5036:
  _ax = *(WORD*)&memory[adr(_ds, 0x70F3)];
  _dl = memory[adr(_ds, 0x70F5)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x4548)];
  _dh = memory[adr(_ds, 0x454B)];
  _di = 0x18;
  _cx = 0x0c08;
  sub_2E29();
}

void sub_5060()
{
  _ax = 0xb800;
  _es = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  if (_ax < 0x0117)
    goto loc_5070;
  _ax = 0x0116;
loc_5070:
  flags.carry = _ax < 0x10;
  _ax -= 0x10;
  if (!flags.carry)
    goto loc_5077;
  _ax = 0;
loc_5077:
  _ax &= 0x0ff0;
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  memory[adr(_ds, 0x57B)] = 0x14;
  flags.carry = _ax < 0x80;
  _ax -= 0x80;
  if (!flags.carry)
    goto loc_5089;
  _ax = (~_ax);
loc_5089:
  _cl = 0x03;
  _ax >>= _cl;
  if (_ax <= 0x0d)
    goto loc_5095;
  _ax = 0x0d;
loc_5095:
  _ax += 0x0002;
  *(WORD*)&memory[adr(_ds, 0x4D6A)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x4DD6)] = 0x0a;
loc_50A1:
  if (*(WORD*)&memory[adr(_ds, 0x4DD6)] == 0x0a)
    goto loc_50AB;
  sub_5B63();
loc_50AB:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x4A80)] = _dx;
  _ax = *(WORD*)&memory[adr(_ds, 0x579)];
  _cx = _ax & 0x0ff0;
  if (_cx != 0x80)
    goto loc_50C6;
  _ax = _cx;
  goto loc_50D2;
loc_50C6:
  if (_cx < 0x80)
    goto loc_50CE;
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x4D6A)];
  goto loc_50D2;
loc_50CE:
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x4D6A)];
loc_50D2:
  *(WORD*)&memory[adr(_ds, 0x579)] = _ax;
  if (memory[adr(_ds, 0x57B)] < 0x54)
    goto loc_50DD;
  return;
loc_50DD:
  memory[adr(_ds, 0x57B)] += 8;
  _cx = (*(WORD*)&memory[adr(_ds, 0x579)]) + 0x0004;
  _dl = memory[adr(_ds, 0x57B)];
  sub_2CB0();
  _di = _ax;
  *(WORD*)&memory[adr(_ds, 0x4DD8)] = _di;
  _si = 0x4b8a;
  _bp = 0x0e;
  _cx = 0x2007;
  sub_2CCC();
  _di = (*(WORD*)&memory[adr(_ds, 0x4DD8)]) + 0xf3;
  _si = 0x4a82;
  _cx = 0x0d04;
  sub_2D9D();
  if (*(WORD*)&memory[adr(_ds, 0x4DD6)] != 0x0a)
    goto loc_5120;
  sub_572E();
  sub_5B54();
loc_5120:
  sub_5B63();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x4A80)];
  if (_dx < *(WORD*)&memory[adr(_ds, 0x4DD6)])
    goto loc_5120;
  if (*(WORD*)&memory[adr(_ds, 0x4DD6)] != 0x0a)
    goto loc_5141;
  sub_38B0();
  _bx = 0;
  _ah = 0x0b;
  _interrupt(0x10);
loc_5141:
  *(WORD*)&memory[adr(_ds, 0x4DD6)] = 2;
  goto loc_50A1;
}

void sub_514A()
{
  _cx = 0x0003;
loc_514D:
  _bx = (0x0003 - _cx) << 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19876)];
  *(WORD*)&memory[adr(_ds, 0x4D6A)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19882)];
  *(WORD*)&memory[adr(_ds, 0x4D6C)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19864)];
  *(WORD*)&memory[adr(_ds, 0x4DCC)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19870)];
  *(WORD*)&memory[adr(_ds, 0x4DCE)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19888)];
  *(WORD*)&memory[adr(_ds, 0x4DD0)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19894)];
  *(WORD*)&memory[adr(_ds, 0x4DD2)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19900)];
  *(WORD*)&memory[adr(_ds, 0x4DD4)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19858)];
  *(WORD*)&memory[adr(_ds, 0x4DCA)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19906)];
  *(WORD*)&memory[adr(_ds, 0x4DC8)] = _ax;
  _push(_cx);
  sub_519B();
  _cx = _pop();
  if (--_cx)
    goto loc_514D;
}

void sub_519B()
{
  _cx = 0x0008;
  memory[adr(_ds, 0x4D91)] = 1;
loc_51A3:
  _push(_cx);
  sub_5B63();
  _cx = _pop();
  _bx = (_cx - 1) << 1;
  _ax = *(WORD*)&memory[adr(_ds, 0x4DCC)];
  *(WORD*)&memory[adr(_ds, _bx + 19786)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x4DCE)];
  *(WORD*)&memory[adr(_ds, _bx + 19802)] = _ax;
  if (--_cx)
    goto loc_51A3;
  _ax = 0xb800;
  _es = _ax;
  memory[adr(_ds, 0x4D6E)] = 0;
loc_51C7:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x4A80)] = _dx;
  _cx = 0x0008;
loc_51D2:
  _push(_cx);
  sub_5B63();
  _cx = _pop();
  _bx = (_cx - 1) << 1;
  _push(_cx);
  _push(_bx);
  if (memory[adr(_ds, 0x4D91)] == 0)
    goto loc_51EA;
  if (_cx != 0x0008)
    goto loc_5205;
loc_51EA:
  _cx = *(WORD*)&memory[adr(_ds, _bx + 19786)];
  _dx = *(WORD*)&memory[adr(_ds, _bx + 19802)];
  sub_2CB0();
  _di = _ax;
  _si = *(WORD*)&memory[adr(_ds, 0x4DCA)];
  _bp = 0x0e;
  _cx = *(WORD*)&memory[adr(_ds, 0x4DD4)];
  sub_2CCC();
loc_5205:
  _bx = _pop();
  _cx = _pop();
  sub_522A();
  if (--_cx)
    goto loc_51D2;
loc_520C:
  sub_5B63();
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x4A80)];
  if (_dx < *(WORD*)&memory[adr(_ds, 0x4DC8)])
    goto loc_520C;
  memory[adr(_ds, 0x4D91)] = 0;
  if (memory[adr(_ds, 0x4D6E)] == 0)
    goto loc_51C7;
}

void sub_522A()
{
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19786)];
  if (*(WORD*)&memory[adr(_ds, _bx + 19823)] < 1)
    goto loc_525A;
  if (*(WORD*)&memory[adr(_ds, _bx + 19823)] != 1)
    goto loc_524A;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x4D6A)];
  if (_ax <= *(WORD*)&memory[adr(_ds, 0x4DD0)])
    goto loc_5256;
  _ax = *(WORD*)&memory[adr(_ds, 0x4DD0)];
  memory[adr(_ds, 0x4D6E)] += 1;
  goto loc_5256;
loc_524A:
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x4D6A)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x4D6A)];
  if (!flags.carry)
    goto loc_5256;
  _ax = 0;
  memory[adr(_ds, 0x4D6E)] += 1;
loc_5256:
  *(WORD*)&memory[adr(_ds, _bx + 19786)] = _ax;
loc_525A:
  _ax = *(WORD*)&memory[adr(_ds, _bx + 19802)];
  if (*(WORD*)&memory[adr(_ds, _bx + 19839)] < 1)
    return;
  if (*(WORD*)&memory[adr(_ds, _bx + 19839)] != 1)
    goto loc_527A;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x4D6C)];
  if (_ax <= *(WORD*)&memory[adr(_ds, 0x4DD2)])
    goto loc_5286;
  _ax = *(WORD*)&memory[adr(_ds, 0x4DD2)];
  memory[adr(_ds, 0x4D6E)] += 1;
  goto loc_5286;
loc_527A:
  flags.carry = _ax < *(WORD*)&memory[adr(_ds, 0x4D6C)];
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x4D6C)];
  if (!flags.carry)
    goto loc_5286;
  _ax = 0;
  memory[adr(_ds, 0x4D6E)] += 1;
loc_5286:
  *(WORD*)&memory[adr(_ds, _bx + 19802)] = _ax;
}

void sub_528B()
{
  sub_5B54();
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_529C;
  _ah = 0x0b;
  _bx = 0x0101;
  _interrupt(0x10);
loc_529C:
  sub_5060();
  sub_514A();
  sub_5BBF();
  if (memory[adr(_ds, 0x1F80)] >= 9)
    goto loc_52B0;
  memory[adr(_ds, 0x1F80)] += 1;
loc_52B0:
  if (*(WORD*)&memory[adr(_ds, 0x8)] >= 7)
    goto loc_52BB;
  *(WORD*)&memory[adr(_ds, 0x8)] += 1;
loc_52BB:
  *(WORD*)&memory[adr(_ds, 0x414)] = 0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x412)] = _dx;
  sub_5B21();
}

void sub_52D0()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x52C4)])
    return;
  *(WORD*)&memory[adr(_ds, 0x52C4)] = _dx;
  _bx = *(WORD*)&memory[adr(_ds, 0x52C6)];
  *(WORD*)&memory[adr(_ds, 0x52C6)] += 2;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 21194)];
  if (_ax != *(WORD*)&memory[adr(_ds, 0x52C8)])
    goto loc_52FC;
  sub_5B21();
  return;
loc_52FC:
  *(WORD*)&memory[adr(_ds, 0x52C8)] = _ax;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = *(WORD*)&memory[adr(_ds, 0x52C8)];
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5313()
{
  if (*(WORD*)&memory[adr(_ds, 0x8)] < 2)
    return;
  *(WORD*)&memory[adr(_ds, 0x5016)] = 0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x52C0)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x52C2)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x52C4)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x52C6)] = 0;
  *(WORD*)&memory[adr(_ds, 0x52C8)] = 0;
loc_533C:
  sub_5368();
  *(WORD*)&memory[adr(_ds, 0x5016)] = *(WORD*)&memory[adr(_ds, 0x5016)] ^ 2;
loc_5345:
  sub_52D0();
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x52C0)];
  if (_ax < 0x0005)
    goto loc_5345;
  *(WORD*)&memory[adr(_ds, 0x52C0)] = _dx;
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x52C2)];
  if (_dx < 0x28)
    goto loc_533C;
  sub_5B21();
}

void sub_5368()
{
  _ax = 0xb800;
  _es = _ax;
  _bx = (*(WORD*)&memory[adr(_ds, 0x8)]) << 1;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 21166)];
  *(WORD*)&memory[adr(_ds, 0x5010)] = _ax;
loc_537A:
  _bx = *(WORD*)&memory[adr(_ds, 0x5010)];
  _di = *(WORD*)&memory[adr(_ds, _bx)];
  if (_di != 0x0000)
    goto loc_5386;
  return;
loc_5386:
  _bx = ((*(WORD*)&memory[adr(_ds, _bx + 2)]) ^ *(WORD*)&memory[adr(_ds, 0x5016)]) & 0x0002;
  _si = *(WORD*)&memory[adr(_ds, _bx + 20498)];
  _cx = 0x2304;
  sub_2D9D();
  sub_52D0();
  *(WORD*)&memory[adr(_ds, 0x5010)] += 4;
  goto loc_537A;
}

void sub_53B0()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x5322)])
    return;
  *(WORD*)&memory[adr(_ds, 0x5322)] = _dx;
  _bx = *(WORD*)&memory[adr(_ds, 0x5320)];
  _bl = memory[adr(_ds, _bx + 21388)];
  if (_bl == 0x66)
    goto loc_53DD;
  _bh = 0;
  *(WORD*)&memory[adr(_ds, 0x5320)] += 1;
  if (_bx != 0x0000)
    goto loc_53E1;
loc_53DD:
  sub_5B21();
  return;
loc_53E1:
  _al = 0xb6;
  _out(0x43, _al);
  _ax = *(WORD*)&memory[adr(_ds, _bx + 21284)];
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5400()
{
  _ax = 0xb800;
  _es = _ax;
  _bx = ((*(WORD*)&memory[adr(_ds, 0x8)]) & 0x0007) << 1;
  _ax = _bx;
  _bx = *(WORD*)&memory[adr(_ds, _bx + 22792)];
  _cl = 0x03;
  _ax <<= _cl;
  *(WORD*)&memory[adr(_ds, 0x5918)] = _ax;
loc_541C:
  _di = *(WORD*)&memory[adr(_ds, _bx)];
  if (_di == 0xffff)
    return;
  sub_2DFD();
  _dx = (_dx & 0x0e) + *(WORD*)&memory[adr(_ds, 0x5918)];
  _si = *(WORD*)&memory[adr(_ds, _dx + 22664)];
  _cx = *(WORD*)&memory[adr(_ds, _si + 22616)];
  _si = *(WORD*)&memory[adr(_ds, _si + 22604)];
  _push(_bx);
  sub_2D9D();
  _bx = _pop();
  _bx += 0x0002;
  goto loc_541C;
}

void sub_5450()
{
  memory[adr(_ds, 0x5B0F)] = 0x0c;
  *(WORD*)&memory[adr(_ds, 0x5B0C)] = 1;
  *(WORD*)&memory[adr(_ds, 0x5B12)] = 511;
  *(WORD*)&memory[adr(_ds, 0x5B0A)] = 0x0f;
  memory[adr(_ds, 0x5B0E)] = 1;
}

void sub_546D()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  if (memory[adr(_ds, 0x1CB8)] == 0)
    goto loc_54F8;
  _ah = 0;
  _interrupt(0x1a);
  if (memory[adr(_ds, 0x5B0F)] != 0)
    goto loc_54A6;
  if (_dx == *(WORD*)&memory[adr(_ds, 0x5B10)])
    return;
  *(WORD*)&memory[adr(_ds, 0x5B10)] = _dx;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = ((*(WORD*)&memory[adr(_ds, 0x5B12)]) & 0x01ff) + 0xc8;
  sub_5889();
  *(WORD*)&memory[adr(_ds, 0x5B12)] -= 0x4b;
  return;
loc_54A6:
  if (_dx == *(WORD*)&memory[adr(_ds, 0x5B10)])
    goto loc_54B4;
  *(WORD*)&memory[adr(_ds, 0x5B10)] = _dx;
  memory[adr(_ds, 0x5B0F)] -= 1;
loc_54B4:
  memory[adr(_ds, 0x5B0E)] -= 1;
  if (memory[adr(_ds, 0x5B0E)] != 0)
    return;
  _al = 0x01;
  if (memory[adr(_ds, 0x697)] == 0xfd)
    goto loc_54C5;
  _al <<= 1;
loc_54C5:
  memory[adr(_ds, 0x5B0E)] = _al;
  sub_2DFD();
  if (_dl > 0x04)
    goto loc_54D4;
  *(WORD*)&memory[adr(_ds, 0x5B0C)] += 1;
loc_54D4:
  if (!(*(WORD*)&memory[adr(_ds, 0x5B0C)] & 1))
    goto loc_54E1;
  *(WORD*)&memory[adr(_ds, 0x5B0A)] += 7;
loc_54E1:
  _al = 0xb6;
  _out(0x43, _al);
  sub_2DFD();
  _ax = ((_dx & *(WORD*)&memory[adr(_ds, 0x5B0A)]) & 0x01ff) + 0x0190;
  sub_5889();
  return;
loc_54F8:
  _ah = 0;
  _interrupt(0x1a);
  if (memory[adr(_ds, 0x5920)] == 0)
    goto loc_5522;
  if (_dx == *(WORD*)&memory[adr(_ds, 0x5921)])
    return;
  *(WORD*)&memory[adr(_ds, 0x5921)] = _dx;
  memory[adr(_ds, 0x5920)] -= 1;
  if (memory[adr(_ds, 0x5920)] == 0)
    goto loc_551E;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = *(WORD*)&memory[adr(_ds, 0x5923)];
  sub_5889();
  return;
loc_551E:
  sub_5B21();
  return;
loc_5522:
  if (_dx == *(WORD*)&memory[adr(_ds, 0x5925)])
    return;
  _si = 0x0003;
  _al = (memory[adr(_ds, 0x1CBF)]) | memory[adr(_ds, 0x5B07)];
  if (_al != 0)
    goto loc_5549;
  _si = 0x0001;
  if (*(WORD*)&memory[adr(_ds, 0x4)] != 0)
    goto loc_5549;
  _si -= 1;
  if (memory[adr(_ds, 0x1673)] == 0)
    goto loc_5549;
  _si = 0x0002;
loc_5549:
  _di = _si << 1;
  _al = (memory[adr(_ds, 0x584)]) | memory[adr(_ds, 0x5B07)];
  if (_al != 0)
    goto loc_5563;
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x5925)];
  if (_ax >= *(WORD*)&memory[adr(_ds, _di + 23026)])
    goto loc_5563;
  return;
loc_5563:
  *(WORD*)&memory[adr(_ds, 0x5925)] = _dx;
  if (memory[adr(_ds, 0x1CBF)] != 0)
    goto loc_5579;
  if (memory[adr(_ds, 0x5B07)] == 0)
    goto loc_559E;
  memory[adr(_ds, 0x5B07)] -= 1;
loc_5579:
  *(WORD*)&memory[adr(_ds, 0x592E)] = 4608;
  _bx = *(WORD*)&memory[adr(_ds, 0x59BA)];
  if (_bx < 0x0006)
    goto loc_558E;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x59BA)] = _bx;
loc_558E:
  *(WORD*)&memory[adr(_ds, 0x59BA)] += 2;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23108)];
  *(WORD*)&memory[adr(_ds, 0x592A)] = _ax;
  sub_5B28();
  return;
loc_559E:
  if (_si != 0x0002)
    goto loc_55BB;
  _al = memory[adr(_ds, 0x1673)];
  _ah = 0;
  _cl = 0x04;
  _ax = (_ax << _cl) + 0x0200;
  *(WORD*)&memory[adr(_ds, 0x592A)] = _ax;
  *(WORD*)&memory[adr(_ds, 0x592E)] = 6144;
  goto loc_568D;
loc_55BB:
  _ax = *(WORD*)&memory[adr(_ds, _di + 23042)];
  *(WORD*)&memory[adr(_ds, 0x592E)] = _ax;
  flags.carry = memory[adr(_ds, 0x5927)] & 1;
  memory[adr(_ds, 0x5927)] >>= 1;
  if (!flags.carry)
    goto loc_5623;
  *(WORD*)&memory[adr(_ds, 0x592E)] = 4096;
  memory[adr(_ds, 0x5927)] = 0x80;
  memory[adr(_ds, 0x5928)] += 1;
  _al = (memory[adr(_ds, 0x5928)]) & memory[adr(_ds, _si + 23034)];
  if (_al != 0)
    goto loc_5616;
  _dl = memory[adr(_ds, _si + 23050)];
  memory[adr(_ds, 0x5929)] += _dl;
  sub_2DFD();
  if (_dl > memory[adr(_ds, _si + 23052)])
    goto loc_55F8;
  _dl &= 0x07;
  memory[adr(_ds, 0x592D)] = _dl;
loc_55F8:
  sub_2DFD();
  _dx = (_dx & 0xff) << 1;
  _cl = 0x01;
  if (!(_dl & 0x02))
    goto loc_560E;
  _cl = 0xff;
  _dx += 0x0300;
loc_560E:
  *(WORD*)&memory[adr(_ds, 0x592A)] = _dx;
  memory[adr(_ds, 0x592C)] = _cl;
loc_5616:
  _ah = (memory[adr(_ds, 0x5929)]) & memory[adr(_ds, _si + 23036)];
  _al |= _ah;
  memory[adr(_ds, 0x5928)] = _al;
loc_5623:
  if (memory[adr(_ds, 0x592C)] == 0xff)
    goto loc_5640;
  *(WORD*)&memory[adr(_ds, 0x5A54)] += 2;
  _bx = (*(WORD*)&memory[adr(_ds, 0x5A54)]) & 0x0e;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23108)];
  *(WORD*)&memory[adr(_ds, 0x592A)] = _ax;
  goto loc_5653;
loc_5640:
  if (*(WORD*)&memory[adr(_ds, 0x592A)] > 0xc8)
    goto loc_564E;
  *(WORD*)&memory[adr(_ds, 0x592A)] = 1280;
loc_564E:
  *(WORD*)&memory[adr(_ds, 0x592A)] -= 0x19;
loc_5653:
  if (memory[adr(_ds, 0x584)] == 0)
    goto loc_5667;
  *(WORD*)&memory[adr(_ds, 0x592E)] = 8192;
  memory[adr(_ds, 0x592C)] = 0xff;
  if (memory[adr(_ds, 0x584)] != 0)
    goto loc_568D;
loc_5667:
  _bl = memory[adr(_ds, 0x5928)];
  _bh = 0;
  _bx = _bx + *(WORD*)&memory[adr(_ds, _di + 23038)];
  _al = (memory[adr(_ds, _bx + 22978)]) & memory[adr(_ds, 0x5927)];
  if (_al != 0)
    goto loc_568D;
  if (memory[adr(_ds, 0x592D)] == 0)
    return;
  memory[adr(_ds, 0x592D)] -= 1;
  _ax = *(WORD*)&memory[adr(_ds, _di + 23046)];
  *(WORD*)&memory[adr(_ds, 0x592E)] = _ax;
loc_568D:
  sub_5B28();
}

void sub_5691()
{
  sub_5B21();
  _ah = 0x0b;
  _bx = 0x0004;
  _interrupt(0x10);
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5AE2)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5AE4)] = 0;
  _al = 0x02;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_56B4;
  _al >>= 1;
loc_56B4:
  memory[adr(_ds, 0x5B06)] = _al;
loc_56B7:
  if (memory[adr(_ds, 0x0)] == 0)
    goto loc_56D8;
  *(WORD*)&memory[adr(_ds, 0x5AE4)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x5AE4)];
  _cl = memory[adr(_ds, 0x5B06)];
  _bx = (_bx >> _cl) & 0x1f;
  _in(_al, 0x61);
  _al = _al ^ memory[adr(_ds, _bx + 23270)];
  _out(0x61, _al);
loc_56D8:
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x5AE2)];
  if (_dx < 0x0002)
    goto loc_56B7;
  _ah = 0x0b;
  _bx = 0;
  _interrupt(0x10);
  memory[adr(_ds, 0x5B07)] = 0x0c;
  sub_5B21();
}

void sub_56F4()
{
  _ax = 0x0200;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_5700;
  _ax <<= 1;
loc_5700:
  *(WORD*)&memory[adr(_ds, 0x5AD0)] = _ax;
}

void sub_5704()
{
  *(WORD*)&memory[adr(_ds, 0x5AD0)] += 1;
  _bx = *(WORD*)&memory[adr(_ds, 0x5AD0)];
  _dx = _bx;
  _cl = 0x09;
  _dx >>= _cl;
  _cl = _dl & 0x0f;
  _bx = (_bx >> _cl) & 0x0f;
  _dl = (memory[adr(_ds, _bx + 23250)]) & memory[adr(_ds, 0x0)];
  _in(_al, 0x61);
  _al = (_al & 0xfc) | _dl;
  _out(0x61, _al);
}

void sub_572E()
{
  *(WORD*)&memory[adr(_ds, 0x5ACB)] = 500;
loc_5734:
  sub_576E();
  *(WORD*)&memory[adr(_ds, 0x5ACB)] -= 0x1e;
  if (*(WORD*)&memory[adr(_ds, 0x5ACB)] > 0xc8)
    goto loc_5734;
  *(WORD*)&memory[adr(_ds, 0x5ACB)] = 500;
loc_574A:
  sub_576E();
  *(WORD*)&memory[adr(_ds, 0x5ACB)] -= 0x14;
  if (*(WORD*)&memory[adr(_ds, 0x5ACB)] > 300)
    goto loc_574A;
loc_575A:
  sub_576E();
  *(WORD*)&memory[adr(_ds, 0x5ACB)] += 0x1e;
  if (*(WORD*)&memory[adr(_ds, 0x5ACB)] < 800)
    goto loc_575A;
  sub_5B21();
}

void sub_576E()
{
  _cx = 0x1000;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_577A;
  _cx >>= 1;
loc_577A:
  _Sleep(_cx);
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = *(WORD*)&memory[adr(_ds, 0x5ACB)];
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5797()
{
  sub_5B21();
  memory[adr(_ds, 0x5ACF)] = 0;
  *(WORD*)&memory[adr(_ds, 0x5ACD)] = 8;
}

void sub_57A6()
{
  memory[adr(_ds, 0x5ACF)] += 1;
  _dl = 0;
  _al = (memory[adr(_ds, 0x5ACF)]) & 0x3f;
  if (_al != 0)
    goto loc_57B7;
  *(WORD*)&memory[adr(_ds, 0x5ACD)] += 1;
loc_57B7:
  _bx = *(WORD*)&memory[adr(_ds, 0x5ACD)];
  _cl = 0x02;
  _bx >>= _cl;
  _bl &= 0x1f;
  if (_al < _bl)
    goto loc_57C8;
  _dl = 0x02;
loc_57C8:
  _dl = _dl & memory[adr(_ds, 0x0)];
  _in(_al, 0x61);
  _al = (_al & 0xfd) | _dl;
  _out(0x61, _al);
}

void sub_57D5()
{
  *(WORD*)&memory[adr(_ds, 0x5A85)] = 0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5A83)] = _dx;
}

void sub_57E4()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x5A83)];
  if (_ax < 0x0002)
    return;
  *(WORD*)&memory[adr(_ds, 0x5A83)] = _dx;
  _bx = *(WORD*)&memory[adr(_ds, 0x5A85)];
  *(WORD*)&memory[adr(_ds, 0x5A85)] += 2;
  if (memory[adr(_ds, 0x552)] == 0)
    goto loc_581B;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23203)];
  if (_ax != 0x0000)
    goto loc_581F;
  sub_5B21();
  return;
loc_581B:
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23175)];
loc_581F:
  _push(_ax);
  _al = 0xb6;
  _out(0x43, _al);
  _ax = _pop();
  sub_5889();
}

void sub_5829()
{
  *(WORD*)&memory[adr(_ds, 0x5A62)] = 0;
  memory[adr(_ds, 0x5A82)] = 0;
}

void sub_5835()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x5A80)])
    goto loc_5847;
  return;
loc_5847:
  *(WORD*)&memory[adr(_ds, 0x5A80)] = _dx;
  memory[adr(_ds, 0x5A82)] += 1;
  _al = 0xb6;
  _out(0x43, _al);
  _bx = *(WORD*)&memory[adr(_ds, 0x5A62)];
  if (memory[adr(_ds, 0x5A82)] & 1)
    goto loc_5861;
  _bx += 0x0002;
loc_5861:
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23140)];
  sub_5889();
}

void sub_5869()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _push(_bx);
  _push(_ax);
  _al = 0xb6;
  _out(0x43, _al);
  _bx = *(WORD*)&memory[adr(_ds, 0x5A62)];
  *(WORD*)&memory[adr(_ds, 0x5A62)] += 2;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23140)];
  sub_5889();
  _ax = _pop();
  _bx = _pop();
}

void sub_5889()
{
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5897()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _push(_ax);
  _push(_cx);
  _push(_dx);
  _al = 0xb6;
  _out(0x43, _al);
  _bx = (*(WORD*)&memory[adr(_ds, 0x5A56)]) & 0x0006;
  *(WORD*)&memory[adr(_ds, 0x5A56)] += 2;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 23130)];
  sub_5889();
  _dx = _pop();
  _cx = _pop();
  _ax = _pop();
}

void sub_58BD()
{
  memory[adr(_ds, 0x5927)] = 0x80;
  memory[adr(_ds, 0x5928)] = 0;
  memory[adr(_ds, 0x5929)] = 0;
  *(WORD*)&memory[adr(_ds, 0x592A)] = 1280;
  memory[adr(_ds, 0x592C)] = 0xff;
  memory[adr(_ds, 0x592D)] = 0;
  memory[adr(_ds, 0x5920)] = 0;
  memory[adr(_ds, 0x5B07)] = 0;
  *(WORD*)&memory[adr(_ds, 0x5B08)] = 0;
  *(WORD*)&memory[adr(_ds, 0x5B0C)] = 1;
  memory[adr(_ds, 0x5B0E)] = 1;
}

void sub_58F8()
{
  if (memory[adr(_ds, 0x1CBF)] != 0)
    goto loc_5908;
  _bx = 0x0390;
  _cx = 0x1800;
  sub_59A3();
loc_5908:
  memory[adr(_ds, 0x127C)] = 0;
}

void sub_590E()
{
  if (memory[adr(_ds, 0x1CBF)] != 0)
    return;
  _bx = 0x0400;
  _cx = 0x1800;
  sub_59A3();
}

void sub_591F()
{
  _bx = 0x07d0;
  _cx = 0x1800;
  sub_59A3();
  _bx = 0x0a6e;
  _cx = 0x1800;
  sub_59A3();
  _bx = 0x0dec;
  _cx = 0x1800;
  sub_59A3();
}

void sub_593B()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x5923)] = _bx;
  _push(_ax);
  _al = 0xb6;
  _out(0x43, _al);
  _ax = _pop();
  sub_5889();
  memory[adr(_ds, 0x5920)] = 2;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5921)] = _dx;
}

void sub_595D()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  if (memory[adr(_ds, 0x5920)] != 0)
    return;
  sub_2DFD();
  _ax = (_dx & 0x7f) + 0xaa;
  _bx = _ax;
  _ax += 0x1e;
  sub_593B();
}

void sub_597F()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ax = 0x1200;
  _bx = 0x1312;
  _ax = _ax + *(WORD*)&memory[adr(_ds, 0x5B08)];
  _bx = _bx + *(WORD*)&memory[adr(_ds, 0x5B08)];
  *(WORD*)&memory[adr(_ds, 0x5B08)] += 350;
  sub_593B();
  memory[adr(_ds, 0x5B07)] = 0x18;
}

void sub_59A3()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = _bx;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_59C5;
  _cx >>= 1;
loc_59C5:
  _Sleep(_cx);
  sub_5B21();
}

void sub_59CB()
{
  _in(_al, 0x61);
  _al &= 0xfe;
  _out(0x61, _al);
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5A40)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5A42)] = 0;
loc_59DF:
  _ax = *(WORD*)&memory[adr(_ds, 0x5A42)];
  _cl = 0x06;
  _ax >>= _cl;
  if (_ax != 0)
    goto loc_59E9;
  _ax += 1;
loc_59E9:
  _cx = _ax;
loc_59EB:
  _push(_cx);
  _ah = 0;
  _interrupt(0x1a);
  _cx = _pop();
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x5A40)];
  if (_dx < 0x0002)
    goto loc_59EB;
  if (_dx >= 0x0007)
    goto loc_5A18;
  if (--_cx)
    goto loc_59EB;
  sub_2DFD();
  _dl = (_dl & 0x02) & memory[adr(_ds, 0x0)];
  _in(_al, 0x61);
  _al = _al ^ _dl;
  _out(0x61, _al);
  *(WORD*)&memory[adr(_ds, 0x5A42)] += 7;
  goto loc_59DF;
loc_5A18:
  sub_5B21();
}

void sub_5A1C()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  sub_13B7();
  _bx = *(WORD*)&memory[adr(_ds, 0x5A16)];
  flags.carry = _bx < _ax;
  _bx -= _ax;
  if (flags.carry)
    goto loc_5A35;
  if (_bx > 0x0260)
    goto loc_5A35;
  return;
loc_5A35:
  *(WORD*)&memory[adr(_ds, 0x5A16)] = _ax;
  _al = 0xb6;
  _out(0x43, _al);
  *(WORD*)&memory[adr(_ds, 0x5A18)] += 1;
  _bx = (*(WORD*)&memory[adr(_ds, 0x5A18)]) & 0x1e;
  _ax = (*(WORD*)&memory[adr(_ds, 0x5A3C)]) & 0x03ff;
  if (_ax < 0x0180)
    goto loc_5A59;
  _cx = 0x0180 - _ax;
  _xchg(_ax, _cx);
loc_5A59:
  _ax = (_ax >> 2) + *(WORD*)&memory[adr(_ds, _bx + 23066)];
  _bx = 0x0001;
  if (memory[adr(_ds, 0x697)] != 0xfd)
    goto loc_5A6D;
  _bl <<= 1;
loc_5A6D:
  *(WORD*)&memory[adr(_ds, 0x5A3E)] += _bx;
  _bx = (_bx << 1) << 1;
  *(WORD*)&memory[adr(_ds, 0x5A3C)] += _bx;
  _dx = *(WORD*)&memory[adr(_ds, 0x5A3E)];
  _cl = 0x03;
  _dx >>= _cl;
  _ax += _dx;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5A90()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x5A14)])
    goto loc_5AA2;
  return;
loc_5AA2:
  *(WORD*)&memory[adr(_ds, 0x5A14)] = _dx;
  _al = 0xb6;
  _out(0x43, _al);
  sub_2DFD();
  _ax = (_dx & 0x70) + 0x0200;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5AC2()
{
  *(WORD*)&memory[adr(_ds, 0x5A12)] = 824;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5A10)] = _dx;
  sub_13B7();
  *(WORD*)&memory[adr(_ds, 0x5A0E)] = _ax;
loc_5AD6:
  sub_13B7();
  _dx = _ax;
  _ax = _ax - *(WORD*)&memory[adr(_ds, 0x5A0E)];
  if (_ax < 0x9c40)
    goto loc_5B10;
  *(WORD*)&memory[adr(_ds, 0x5A0E)] = _dx;
  if (memory[adr(_ds, 0x0)] == 0)
    goto loc_5B10;
  _al = 0xb6;
  _out(0x43, _al);
  sub_2DFD();
  _ax = (_dx & 0x07ff) + *(WORD*)&memory[adr(_ds, 0x5A12)];
  *(WORD*)&memory[adr(_ds, 0x5A12)] -= 2;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
loc_5B10:
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x5A10)];
  if (_dx < 0x0002)
    goto loc_5AD6;
  sub_5B21();
}

void sub_5B21()
{
  _in(_al, 0x61);
  _al &= 0xfc;
  _out(0x61, _al);
}

void sub_5B28()
{
  _al = 0xb6;
  _out(0x43, _al);
  _ax = *(WORD*)&memory[adr(_ds, 0x592A)];
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
  sub_13B7();
  _cx = _ax;
loc_5B40:
  sub_13B7();
  _dx = _cx - _ax;
  if (_dx < *(WORD*)&memory[adr(_ds, 0x592E)])
    goto loc_5B40;
  _in(_al, 0x61);
  _al &= 0xfc;
  _out(0x61, _al);
}

void sub_5B54()
{
  *(WORD*)&memory[adr(_ds, 0x59BE)] = 0;
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x59C0)] = _dx;
}

void sub_5B63()
{
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x59C0)];
  if (_ax >= 0x0002)
    goto loc_5B7A;
  return;
loc_5B7A:
  *(WORD*)&memory[adr(_ds, 0x59C0)] = _dx;
  _bx = (*(WORD*)&memory[adr(_ds, 0x59BE)]) & 0xfe;
  if (_bx < 0x86)
    goto loc_5B92;
  _bx = 0;
  *(WORD*)&memory[adr(_ds, 0x59BE)] = _bx;
loc_5B92:
  *(WORD*)&memory[adr(_ds, 0x59BE)] += 2;
  _ax = *(WORD*)&memory[adr(_ds, _bx + 22836)];
  _cx = *(WORD*)&memory[adr(_ds, 0x59BC)];
  *(WORD*)&memory[adr(_ds, 0x59BC)] = _ax;
  if (_ax != _cx)
    goto loc_5BAA;
  sub_5B21();
  return;
loc_5BAA:
  _cx = _ax;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = _cx;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
}

void sub_5BBF()
{
sub_5BBF:
  if (memory[adr(_ds, 0x0)] == 0)
    return;
  sub_5B63();
  if (*(WORD*)&memory[adr(_ds, 0x59BE)] < 0x7c)
    goto sub_5BBF;
}

void sub_5BE0()
{
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x5F66)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5F60)] = 0;
loc_5BEE:
  _ax = 0xb800;
  _es = _ax;
  _bx = *(WORD*)&memory[adr(_ds, 0x5F60)];
  *(WORD*)&memory[adr(_ds, 0x5F60)] += 2;
  _bx &= 0x0002;
  _si = *(WORD*)&memory[adr(_ds, _bx + 24418)];
  _di = 0x0a74;
  _cx = 0x4404;
  sub_2D9D();
loc_5C0D:
  sub_57E4();
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x5F66)];
  if (_ax < 0x0004)
    goto loc_5C0D;
  *(WORD*)&memory[adr(_ds, 0x5F66)] = _dx;
  if (*(WORD*)&memory[adr(_ds, 0x5F60)] != 4)
    goto loc_5C36;
  _si = 0x5f68;
  _di = 0x0668;
  _cx = 0x1004;
  sub_2D9D();
loc_5C36:
  _bx = *(WORD*)&memory[adr(_ds, 0x5F60)];
  flags.carry = _bx < 0x0008;
  _bx -= 0x0008;
  if (flags.carry)
    goto loc_5C51;
  if (_bx >= 0x0006)
    goto loc_5C51;
  _si = 0x5fe8;
  _di = *(WORD*)&memory[adr(_ds, _bx + 24804)];
  _cx = 0x1506;
  sub_2D9D();
loc_5C51:
  if (*(WORD*)&memory[adr(_ds, 0x5F60)] < 0x10)
    goto loc_5BEE;
  sub_5B21();
}

void sub_5C60()
{
  _interrupt(0x11);
  _al &= 0x30;
  if (_al != 0x30)
    return;
  _ax = 0xb800;
  _ds = _ax;
  _ax = 0x55aa;
  *(WORD*)&memory[adr(_ds, 0x0)] = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x0)];
  if (_ax != 0x55aa)
    goto loc_5C96;
  _si = 0x60f0;
  sub_5C9E();
  _ax = 0x40;
  _ds = _ax;
  _ax = *(WORD*)&memory[adr(_ds, 0x10)];
  _al = (_al & 0xcf) | 0x10;
  *(WORD*)&memory[adr(_ds, 0x10)] = _ax;
  _ax = 0x0004;
  _interrupt(0x10);
  return;
loc_5C96:
  _si = 0x6112;
  sub_5C9E();
  _InfiniteLoop();
}

void sub_5C9E()
{
  _ax = SEG_DATA;
  _ds = _ax;
  sub_5E2B();
}

void sub_5CB0()
{
  flags.direction = false;
  *(WORD*)&memory[adr(_ds, 0x4)] = 0;
  sub_1830();
  sub_2330();
  sub_2A30();
  _ax = 0xb800;
  _es = _ax;
  _si = 0x6152;
  _cx = 0x1d0b;
  _di = 0xbd;
  sub_2D9D();
  _si = 0x63d0;
  _cx = 0x160e;
  _di = 0x069e;
  sub_2D9D();
  _si = 0x6638;
  _cx = 0x0c03;
  _di = 0x0a78;
  sub_2D9D();
  _si = 0x6680;
  _cx = 0x080e;
  _di = 0x0ca8;
  sub_2D9D();
  _si = 0x6760;
  _cx = 0x0b0c;
  _di = 0x1d6e;
  sub_2D9D();
  _si = 0x6868;
  _cx = 0x0804;
  _di = 0x1dec;
  sub_2D9D();
  *(WORD*)&memory[adr(_ds, 0x6A8D)] = 0;
  sub_5E3B();
  *(WORD*)&memory[adr(_ds, 0x579)] = 0;
  sub_70D();
  memory[adr(_ds, 0x57B)] = 0x60;
  memory[adr(_ds, 0x57C)] = 0x92;
  sub_26F2();
  sub_26FC();
  memory[adr(_ds, 0x1F80)] = 9;
  memory[adr(_ds, 0x1F81)] = 0xff;
  sub_26B3();
  sub_1E40();
  memory[adr(_ds, 0x698)] = 0;
  memory[adr(_ds, 0x699)] = 0;
  memory[adr(_ds, 0x6A8A)] = 0;
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
  *(WORD*)&memory[adr(_ds, 0x6150)] = _ax;
loc_5D54:
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x6A8B)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5322)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x6A93)] = _dx;
  _dx -= 0x30;
  *(WORD*)&memory[adr(_ds, 0x6A88)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x5320)] = 0;
loc_5D71:
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x6A93)];
  if (_ax < 0x24)
    goto loc_5D89;
  *(WORD*)&memory[adr(_ds, 0x6A93)] = _dx;
  _push(_dx);
  sub_5E3B();
  _dx = _pop();
loc_5D89:
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x6A8B)];
  _ax = *(WORD*)&memory[adr(_ds, 0x56DA)];
  if (memory[adr(_ds, 0x41A)] == 0)
    goto loc_5DA0;
  _ax += 0x48;
  if (_dx >= _ax)
    goto loc_5D54;
  goto loc_5DA7;
loc_5DA0:
  _ax += 0x0006;
  if (_dx > _ax)
    return;
loc_5DA7:
  sub_53B0();
  sub_5DD4();
  if (memory[adr(_ds, 0x69B)] == 0)
    goto loc_5DCA;
  _dx = 0x0201;
  _in(_al, _dx);
  _al &= 0x10;
  if (_al == 0)
    goto loc_5DC3;
  memory[adr(_ds, 0x6A8A)] = 1;
  goto loc_5DCA;
loc_5DC3:
  if (memory[adr(_ds, 0x6A8A)] != 0)
    return;
loc_5DCA:
  _ax = *(WORD*)&memory[adr(_ds, 0x6150)];
  if (_ax == *(WORD*)&memory[adr(_ds, 0x693)])
    goto loc_5D71;
}

void sub_5DD4()
{
  if (*(WORD*)&memory[adr(_ds, 0x579)] > 0x20)
    goto loc_5DE2;
  memory[adr(_ds, 0x698)] = 1;
  goto loc_5E1C;
loc_5DE2:
  if (*(WORD*)&memory[adr(_ds, 0x579)] < 288)
    goto loc_5DF1;
  memory[adr(_ds, 0x698)] = 0xff;
  goto loc_5E1C;
loc_5DF1:
  _ah = 0;
  _interrupt(0x1a);
  _ax = _dx - *(WORD*)&memory[adr(_ds, 0x6A88)];
  if (_ax < 0x12)
    goto loc_5E1C;
  *(WORD*)&memory[adr(_ds, 0x6A88)] = _dx;
  sub_2DFD();
  memory[adr(_ds, 0x698)] = 0;
  if (_dl > 0xa0)
    goto loc_5E1C;
  _dl &= 0x01;
  if (_dl != 0)
    goto loc_5E18;
  _dl = 0xff;
loc_5E18:
  memory[adr(_ds, 0x698)] = _dl;
loc_5E1C:
  sub_13D8();
  if (_al == 0)
    return;
  *(WORD*)&memory[adr(_ds, 0x572)] = 4;
  sub_8E5();
}

void sub_5E2B()
{
sub_5E2B:
  _lodsb<MemData, DirForward>();
  if (_al == 0x00)
    return;
  _push(_si);
  _bl = 0x02;
  _ah = 0x0e;
  _interrupt(0x10);
  _si = _pop();
  goto sub_5E2B;
}

void sub_5E3B()
{
  _ax = 0xb800;
  _es = _ax;
  *(WORD*)&memory[adr(_ds, 0x6A8D)] += 2;
  _bx = (*(WORD*)&memory[adr(_ds, 0x6A8D)]) & 0x0002;
  _si = *(WORD*)&memory[adr(_ds, _bx + 27279)];
  _cx = 0x0c0a;
  _di = 0x1d38;
  sub_2D9D();
}

void sub_5E5B()
{
  _dl = 0x00;
  _bh = _dl;
  _ah = 0x02;
  _interrupt(0x10);
}

void sub_5E70()
{
  sub_5B21();
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x6DFC)] = _dx;
  *(WORD*)&memory[adr(_ds, 0x6DFE)] = _cx;
  _push(_ds);
  _push(_ds);
  _es = _pop();
  _ax = 0xb800;
  _ds = _ax;
  _si = 0x0dca;
  _di = 0x0e;
  _cx = 0x1020;
  sub_2DCA();
  _ds = _pop();
  _dx = 0x0b05;
  _bh = 0x00;
  _ah = 0x02;
  _interrupt(0x10);
  _si = 0x6d91;
  flags.direction = false;
  sub_5E2B();
  _dx = 0x0c05;
  _bh = 0x00;
  _ah = 0x02;
  _interrupt(0x10);
  _si = 0x6db2;
  if (memory[adr(_ds, 0x69B)] == 0)
    goto loc_5EBA;
  _si = 0x6dd3;
loc_5EBA:
  flags.direction = false;
  sub_5E2B();
  sub_5F97();
  _ax = 0xb800;
  _es = _ax;
  _si = 0x0e;
  _di = 0x0dca;
  _cx = 0x1020;
  sub_2D9D();
  _ah = 0x01;
  _cx = *(WORD*)&memory[adr(_ds, 0x6DFE)];
  _dx = *(WORD*)&memory[adr(_ds, 0x6DFC)];
  _interrupt(0x1a);
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
  *(WORD*)&memory[adr(_ds, 0x6E00)] = _ax;
}

void sub_5EE5()
{
  sub_5B21();
loc_5EE8:
  sub_5FCD();
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0;
  sub_5FB1();
loc_5EF4:
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
loc_5EF7:
  _DeadLoop();
  if (_ax == *(WORD*)&memory[adr(_ds, 0x693)])
    goto loc_5EF7;
  if (!(memory[adr(_ds, 0x6C1)] & 0x80))
    goto loc_5F12;
  if (memory[adr(_ds, 0x6C2)] & 0x80)
    goto loc_5EF4;
  memory[adr(_ds, 0x69B)] = 0;
  goto loc_5F1C;
loc_5F12:
  sub_5FE5();
  if (flags.carry)
    goto loc_5EE8;
  memory[adr(_ds, 0x69B)] = 1;
loc_5F1C:
  _cx = 0x0005;
loc_5F1F:
  _push(_cx);
  sub_5FB1();
  _cx = _pop();
  if (--_cx)
    goto loc_5F1F;
loc_5F26:
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
loc_5F29:
  _DeadLoop();
  if (_ax == *(WORD*)&memory[adr(_ds, 0x693)])
    goto loc_5F29;
  _ax = 0;
  if (!(memory[adr(_ds, 0x6C3)] & 0x80))
    goto loc_5F50;
  _ax += 1;
  if (!(memory[adr(_ds, 0x6C4)] & 0x80))
    goto loc_5F50;
  _ax += 1;
  if (!(memory[adr(_ds, 0x6C5)] & 0x80))
    goto loc_5F50;
  _ax += 1;
  if (memory[adr(_ds, 0x6C6)] & 0x80)
    goto loc_5F26;
loc_5F50:
  *(WORD*)&memory[adr(_ds, 0x6DF8)] = _ax;
  _cx = 0x0005;
loc_5F56:
  _push(_cx);
  sub_5FB1();
  _cx = _pop();
  if (--_cx)
    goto loc_5F56;
  if (memory[adr(_ds, 0x69B)] == 0)
    goto loc_5F7E;
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0x20;
  sub_5FB1();
  sub_5FB1();
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0x18;
  sub_5FB1();
  sub_5FB1();
  goto loc_5F93;
loc_5F7E:
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0x1c;
  sub_5FB1();
  sub_5FB1();
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0x16;
  sub_5FB1();
loc_5F93:
  sub_5F97();
}

void sub_5F97()
{
  if (memory[adr(_ds, 0x69B)] == 0)
    goto loc_5FA7;
loc_5F9E:
  _dx = 0x0201;
  _in(_al, _dx);
  _al &= 0x10;
  if (_al != 0)
    goto loc_5F9E;
  return;
loc_5FA7:
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
loc_5FAA:
  _DeadLoop();
  if (_ax == *(WORD*)&memory[adr(_ds, 0x693)])
    goto loc_5FAA;
}

void sub_5FB1()
{
  _bx = *(WORD*)&memory[adr(_ds, 0x6D8F)];
  _dx = *(WORD*)&memory[adr(_ds, _bx + 28003)];
  sub_5E5B();
  _bx = *(WORD*)&memory[adr(_ds, 0x6D8F)];
  *(WORD*)&memory[adr(_ds, 0x6D8F)] += 2;
  _si = *(WORD*)&memory[adr(_ds, _bx + 27959)];
  sub_5E2B();
}

void sub_5FCD()
{
  flags.direction = false;
  _ax = 0xb800;
  _es = _ax;
  _ax = 0;
  _di = _ax;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
  _di = 0x2000;
  _cx = 0x0fa0;
  _rep_stosw<MemB800, DirForward>();
}

void sub_5FE5()
{
  _interrupt(0x11);
  if (!(_ax & 0x1000))
    goto loc_5FF6;
  sub_600F();
  if (!flags.carry)
    return;
  sub_600F();
  if (!flags.carry)
    return;
loc_5FF6:
  *(WORD*)&memory[adr(_ds, 0x6D8F)] = 0x24;
  _cx = 0x0004;
loc_5FFF:
  sub_5FB1();
  if (--_cx)
    goto loc_5FFF;
  _ax = *(WORD*)&memory[adr(_ds, 0x693)];
loc_6007:
  _DeadLoop();
  if (_ax == *(WORD*)&memory[adr(_ds, 0x693)])
    goto loc_6007;
  flags.carry = true;
}

void sub_600F()
{
  _dx = 0x0201;
  _out(_dx, _al);
  _ah = 0;
  _interrupt(0x1a);
  *(WORD*)&memory[adr(_ds, 0x6DFA)] = _dx;
loc_601B:
  _dx = 0x0201;
  _in(_al, _dx);
  if (_al & 0x03)
    goto loc_6025;
  flags.carry = false;
  return;
loc_6025:
  _ah = 0;
  _interrupt(0x1a);
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x6DFA)];
  if (_dx < 0x12)
    goto loc_601B;
  flags.carry = true;
}

void sub_6040()
{
  flags.direction = false;
  _push(_ds);
  _es = _pop();
  _di = 0x0e;
  _cx = 0x24;
  _ax = 0;
  _rep_stosw<MemData, DirForward>();
  *(WORD*)&memory[adr(_ds, 0x6F24)] = 0x25;
  _ax = 0xb800;
  _es = _ax;
loc_6058:
  sub_13D8();
  if (_al == 0)
    goto loc_6058;
  _si = 0x0e;
  _di = *(WORD*)&memory[adr(_ds, 0x6F24)];
  _cx = 0x0c03;
  sub_2D9D();
  *(WORD*)&memory[adr(_ds, 0x6F24)] += 480;
  _si = 0x6e10;
  _di = *(WORD*)&memory[adr(_ds, 0x6F24)];
  _cx = 0x0c03;
  sub_2D9D();
loc_607D:
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x6F26)])
    goto loc_607D;
  *(WORD*)&memory[adr(_ds, 0x6F26)] = _dx;
  if (memory[adr(_ds, 0x0)] == 0)
    goto loc_60A7;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = (*(WORD*)&memory[adr(_ds, 0x6F24)]) >> 1;
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
  _in(_al, 0x61);
  _al |= 0x03;
  _out(0x61, _al);
loc_60A7:
  if (*(WORD*)&memory[adr(_ds, 0x6F24)] < 6720)
    goto loc_6058;
  _si = 0x6e58;
  _di = *(WORD*)&memory[adr(_ds, 0x6F24)];
  _cx = 0x1106;
  sub_2D9D();
loc_60BC:
  _ah = 0;
  _interrupt(0x1a);
  if (_dx == *(WORD*)&memory[adr(_ds, 0x6F28)])
    goto loc_60BC;
  *(WORD*)&memory[adr(_ds, 0x6F28)] = _dx;
  if (memory[adr(_ds, 0x0)] == 0)
    goto loc_60E6;
  _al = 0xb6;
  _out(0x43, _al);
  _ax = 0x0c00;
  if (!(_dl & 0x01))
    goto loc_60E0;
  _ax = 0x0b54;
loc_60E0:
  _out(0x42, _al);
  _al = _ah;
  _out(0x42, _al);
loc_60E6:
  _dx = _dx - *(WORD*)&memory[adr(_ds, 0x6F26)];
  if (_dx < 0x12)
    goto loc_60BC;
  sub_5B21();
}

void sub_6100()
{
  memory[adr(_ds, 0x70F2)] = 0;
}

void sub_6106()
{
  _ah = 0;
  _interrupt(0x1a);
  if (_dx != *(WORD*)&memory[adr(_ds, 0x70EE)])
    goto loc_6111;
  return;
loc_6111:
  *(WORD*)&memory[adr(_ds, 0x70EE)] = _dx;
  sub_62A6();
  if (!flags.carry)
    goto loc_6129;
  sub_11E3();
  sub_622B();
  sub_1145();
  memory[adr(_ds, 0x70F2)] = 0;
  return;
loc_6129:
  if (memory[adr(_ds, 0x70F2)] != 0)
    goto loc_619E;
loc_6130:
  sub_2DFD();
  _bx = _dx & 0x1f;
  if (_bl < 0x10)
    goto loc_6166;
  _bl -= 0x10;
  if (_bl > 0x09)
    goto loc_6130;
  _dl = 0x01;
  if (_bl < 0x05)
    goto loc_614F;
  _dl = 0xff;
loc_614F:
  memory[adr(_ds, 0x70F6)] = _dl;
  memory[adr(_ds, 0x70F5)] = 6;
  _bl <<= 1;
  _ax = (*(WORD*)&memory[adr(_ds, _bx + 28856)]) + 0x0004;
  *(WORD*)&memory[adr(_ds, 0x70F3)] = _ax;
  goto loc_6188;
loc_6166:
  _ax = 0x0c;
  _dl = 0x01;
  if (!(_bl & 0x08))
    goto loc_6175;
  _ax = 0x0120;
  _dl = 0xff;
loc_6175:
  *(WORD*)&memory[adr(_ds, 0x70F3)] = _ax;
  memory[adr(_ds, 0x70F6)] = _dl;
  _bl &= 0x07;
  _al = (memory[adr(_ds, _bx + 28848)]) + 0x08;
  memory[adr(_ds, 0x70F5)] = _al;
loc_6188:
  memory[adr(_ds, 0x70F2)] = 1;
  memory[adr(_ds, 0x70F7)] = 1;
  *(WORD*)&memory[adr(_ds, 0x70F0)] = 0;
  *(WORD*)&memory[adr(_ds, 0x70EC)] = 0xffff;
loc_619E:
  if (*(WORD*)&memory[adr(_ds, 0x70F0)] >= 0xa0)
    goto loc_61AB;
  *(WORD*)&memory[adr(_ds, 0x70F0)] += 4;
loc_61AB:
  memory[adr(_ds, 0x70F5)] += 2;
  if (memory[adr(_ds, 0x70F5)] > 0xbf)
    goto loc_61D4;
  if (memory[adr(_ds, 0x70F6)] == 1)
    goto loc_61C7;
  flags.carry = *(WORD*)&memory[adr(_ds, 0x70F3)] < 5;
  *(WORD*)&memory[adr(_ds, 0x70F3)] -= 5;
  if (flags.carry)
    goto loc_61D4;
  goto loc_61DD;
loc_61C7:
  *(WORD*)&memory[adr(_ds, 0x70F3)] += 5;
  if (*(WORD*)&memory[adr(_ds, 0x70F3)] < 300)
    goto loc_61DD;
loc_61D4:
  memory[adr(_ds, 0x70F2)] = 0;
  sub_622B();
  return;
loc_61DD:
  _cx = *(WORD*)&memory[adr(_ds, 0x70F3)];
  _dl = memory[adr(_ds, 0x70F5)];
  sub_2CB0();
  *(WORD*)&memory[adr(_ds, 0x70FA)] = _ax;
  sub_62A6();
  if (flags.carry)
    goto loc_61D4;
  sub_6245();
  sub_622B();
  sub_61FA();
}

void sub_61FA()
{
  _ax = 0xb800;
  _es = _ax;
  memory[adr(_ds, 0x70F7)] = 0;
  _ax = ((*(WORD*)&memory[adr(_ds, 0x70F0)]) & 0x01e0) + 0x6f30;
  if (memory[adr(_ds, 0x70F6)] == 0xff)
    goto loc_6217;
  _ax += 0xc0;
loc_6217:
  _si = _ax;
  _di = *(WORD*)&memory[adr(_ds, 0x70FA)];
  *(WORD*)&memory[adr(_ds, 0x70F8)] = _di;
  _bp = 0x70cc;
  _cx = 0x0802;
  sub_2CCC();
}

void sub_622B()
{
  if (memory[adr(_ds, 0x70F7)] != 0)
    return;
  _ax = 0xb800;
  _es = _ax;
  _si = 0x70cc;
  _di = *(WORD*)&memory[adr(_ds, 0x70F8)];
  _cx = 0x0802;
  sub_2D9D();
}

void sub_6245()
{
  _al = ((memory[adr(_ds, 0x70F5)]) - 0x08) & 0xf8;
  _cx = 0x0007;
loc_624F:
  _bx = _cx - 1;
  if (_al == memory[adr(_ds, _bx + 11220)])
    goto loc_625B;
  if (--_cx)
    goto loc_624F;
  return;
loc_625B:
  _ax = *(WORD*)&memory[adr(_ds, 0x70F3)];
  _cl = 0x04;
  _ax >>= _cl;
  flags.carry = _ax < 0x0002;
  _ax -= 0x0002;
  if (flags.carry)
    return;
  if (_ax >= 0x10)
    return;
  _di = _ax;
  _dl = memory[adr(_ds, _bx + 11227)];
  _dh = 0;
  _ax += _dx;
  if (_ax == *(WORD*)&memory[adr(_ds, 0x70EC)])
    return;
  *(WORD*)&memory[adr(_ds, 0x70EC)] = _ax;
  _si = _ax;
  memory[adr(_ds, _si + 11234)] = memory[adr(_ds, _si + 11234)] ^ 2;
  _al = memory[adr(_ds, _si + 11234)];
  _ah = 0;
  _di <<= 1;
  _cx = *(WORD*)&memory[adr(_ds, _di + 28924)];
  _dl = memory[adr(_ds, _bx + 28960)];
  _push(_ax);
  _push(_cx);
  _push(_dx);
  sub_622B();
  _dx = _pop();
  _cx = _pop();
  _bx = _pop();
  sub_30E3();
  sub_61FA();
}

void sub_62A6()
{
  if (memory[adr(_ds, 0x70F2)] != 0)
    goto loc_62AF;
  flags.carry = false;
  return;
loc_62AF:
  _ax = *(WORD*)&memory[adr(_ds, 0x70F3)];
  _dl = memory[adr(_ds, 0x70F5)];
  _si = 0x10;
  _bx = *(WORD*)&memory[adr(_ds, 0x579)];
  _dh = memory[adr(_ds, 0x57B)];
  _di = 0x18;
  _cx = 0x0e08;
  sub_2E29();
  if (!flags.carry)
    return;
  memory[adr(_ds, 0x571)] = 1;
  memory[adr(_ds, 0x576)] = 2;
  memory[adr(_ds, 0x578)] = 0x20;
  memory[adr(_ds, 0x55B)] = 8;
  _ax = 0x091d;
  _bx = 0x0ce4;
  sub_593B();
  flags.carry = true;
}

