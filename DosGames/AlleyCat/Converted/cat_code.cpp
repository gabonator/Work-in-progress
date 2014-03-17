#include "cat_code.h"

/*
  unknown_command(); // public start
*/
void start()
{
  _push(ds);
  ax = 0;
  _push(ax);
  sub_5C60();
  ax = seg_data;
  ds = ax;
  sub_13AA();
  _data[0x690] = 4;
  *(WORD*)&_data[0x6DF8] = 0;
  _data[0x69B] = 0;
  sub_1419();
  sub_13E8();
  ax = *(WORD*)&_data[0x693];
  ax += 0x240;
  *(WORD*)&_data[0x6E00] = ax;
  ax = 4;
  _int(0x10);
  al = 4;
  if ( _data[0x697] == 0x0FD ) // jz 
    goto loc_code_3F;
  al = 6;
loc_code_3F:
  _data[0x690] = al;
  ah = 0x0B;
  bx = 0x101;
  _int(0x10);
  *(WORD*)&_data[0x416] = 0;
  *(WORD*)&_data[0x4] = 0;
  sub_1D31();
  if ( _data[0x697] == 0x0FD ) // jz 
    goto loc_code_65;
  dx = 0x3D9;
  al = 0x20;
  _out(dx, al);
loc_code_65:
  sub_2E10();
  sub_26E1();
  sub_26DA();
  _data[0x41A] = 0;
  ax = 0x0FFFF;
  *(WORD*)&_data[0x41D] = ax;
  *(WORD*)&_data[0x41F] = ax;
  _data[0x0] = 0x0FF;
loc_code_81:
  sub_2690();
  *(WORD*)&_data[0x8] = 0;
  *(WORD*)&_data[0x4] = 0;
  sub_1D31();
  sub_5B21();
  sub_5CB0();
  sub_5B21();
  if ( _data[0x41A] != 0 ) // jnz 
    goto loc_code_AE;
loc_code_A3:
  sub_5B21();
  sub_5EE5();
  _data[0x41A] = 1;
loc_code_AE:
  ax = *(WORD*)&_data[0x6DF8];
  *(WORD*)&_data[0x8] = ax;
  _data[0x1F80] = 3;
  sub_26DA();
  *(WORD*)&_data[0x4] = 0;
  sub_1D31();
  sub_5B21();
  *(WORD*)&_data[0x1C30] = 0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[0x412] = dx;
  *(WORD*)&_data[0x414] = 0;
  _data[0x418] = 0;
  _data[0x419] = 0;
  _data[0x41C] = 0;
  _data[0x41B] = 0;
  sub_5B21();
loc_code_F3:
  if ( _data[0x1F80] == 0 ) // jz 
    goto loc_code_81;
  if ( _data[0x41B] != 0 ) // jnz 
    goto loc_code_AE;
  if ( _data[0x41C] != 0 ) // jnz 
    goto loc_code_A3;
  sub_2A00();
  sub_5400();
  _data[0x1F81] = 0x0FF;
  sub_5B21();
  *(WORD*)&_data[0x4] = 0;
  if ( _data[0x419] == 0 ) // jz 
    goto loc_code_137;
  sub_7A1();
  _data[0x550] = 2;
  _data[0x576] = 1;
  _data[0x578] = 0x20;
  goto loc_code_140;
loc_code_137:
  *(WORD*)&_data[0x579] = 0;
  sub_70D();
loc_code_140:
  sub_1E40();
  sub_1830();
  sub_2210();
  sub_2330();
  sub_26F2();
  sub_26FC();
  sub_58BD();
loc_code_155:
  if ( _data[0x1F80] != 0 ) // jnz 
    goto loc_code_15F;
  goto loc_code_81;
loc_code_15F:
  sub_1338();
  if ( _data[0x41C] == 0 ) // jz 
    goto loc_code_16C;
  goto loc_code_A3;
loc_code_16C:
  if ( _data[0x41B] == 0 ) // jz 
    goto loc_code_176;
  goto loc_code_AE;
loc_code_176:
  sub_1200();
  sub_8E5();
  sub_1E63();
  if ( _data[0x1CB8] != 0 ) // jnz 
    goto loc_code_191;
  _data[0x40F]++;
  if ( _data[0x40F] & 3 ) // jnz 
    goto loc_code_155;
loc_code_191:
  sub_546D();
  sub_4A0();
  sub_1936();
  sub_184B();
  sub_2216();
  sub_237B();
  sub_26B3();
  if ( _data[0x551] == 0 ) // jz 
    goto loc_code_155;
  if ( _data[0x1F80] != 0 ) // jnz 
    goto loc_code_1B7;
  goto loc_code_81;
loc_code_1B7:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[0x410] = dx;
  ax = *(WORD*)&_data[0x579];
  *(WORD*)&_data[0x1] = ax;
  al = _data[0x57B];
  _data[0x3] = al;
  _data[0x419] = 1;
  if ( _data[0x418] == 0 ) // jz 
    goto loc_code_1E5;
  _data[0x418] = 0;
  *(WORD*)&_data[0x4] = 7;
  goto loc_code_238;
loc_code_1E5:
  sub_2DFD();
  if ( !(dl & 0x0A0) ) // jz 
    goto loc_code_20A;
  bx = *(WORD*)&_data[0x8];
  bx &= 3;
  if ( bx == 3 ) // jz 
    goto loc_code_20A;
  cl = 2;
  bx <<= cl;
  dx &= 3;
  bx += dx;
  al = _data[bx + 0x421];
  goto loc_code_21C;
loc_code_20A:
  sub_2DFD();
  dx &= 7;
  if ( dx >= 5 ) // jnb 
    goto loc_code_20A;
  bx = dx;
  al = _data[bx + 0x42D];
loc_code_21C:
  ah = 0;
  if ( ax != *(WORD*)&_data[0x41D] ) // jnz 
    goto loc_code_22A;
  if ( ax == *(WORD*)&_data[0x41F] ) // jz 
    goto loc_code_1E5;
loc_code_22A:
  *(WORD*)&_data[0x4] = ax;
  cx = *(WORD*)&_data[0x41D];
  *(WORD*)&_data[0x41F] = cx;
  *(WORD*)&_data[0x41D] = ax;
loc_code_238:
  *(WORD*)&_data[0x6] = 0;
  bx = *(WORD*)&_data[0x4];
  if ( bx <= 7 ) // jbe 
    goto loc_code_249;
  bx = 0;
loc_code_249:
  printf("Jump to room %d!\n", bx);
  bx <<= 1;
  unknown_command(); // jmp	cs:off_code_250[bx];
/////WORD off_code_250 =  offset loc_code_3E2;
  unknown_command(); // dw offset loc_code_3E2
  unknown_command(); // dw offset loc_code_459
  unknown_command(); // dw offset loc_code_394
  unknown_command(); // dw offset loc_code_349
  unknown_command(); // dw offset loc_code_2FE
  unknown_command(); // dw offset loc_code_2AA
  unknown_command(); // dw offset loc_code_260
loc_code_260:
  *(WORD*)&_data[0x4] = 7;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_1E40();
  sub_3405();
  sub_6100();
  sub_4F59();
  sub_58BD();
loc_code_27E:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_6106();
  sub_2F66();
  sub_2E60();
  sub_4C10();
  al = _data[0x551];
  al |= _data[0x553];
  al |= _data[0x41C];
  al |= _data[0x41B];
  if ( !al ) // jz 
    goto loc_code_27E;
  goto loc_code_427;
loc_code_2AA:
  *(WORD*)&_data[0x4] = 6;
  sub_1BF0();
  sub_2790();
  nullsub_1();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_code_2C5:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_4943();
  sub_47D6();
  sub_8E5();
  if ( _data[0x1CB8] == 0 ) // jz 
    goto loc_code_2E3;
  sub_1E63();
  goto loc_code_2E6;
loc_code_2E3:
  sub_3150();
loc_code_2E6:
  al = _data[0x551];
  al |= _data[0x552];
  al |= _data[0x553];
  al |= _data[0x41B];
  al |= _data[0x41C];
  if ( !al ) // jz 
    goto loc_code_2C5;
  goto loc_code_427;
loc_code_2FE:
  *(WORD*)&_data[0x4] = 5;
  sub_1BF0();
  sub_2790();
  sub_457A();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_code_319:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_45AB();
  sub_4340();
  sub_8E5();
  sub_3150();
  sub_1E63();
  al = _data[0x552];
  al |= _data[0x553];
  al |= _data[0x551];
  al |= _data[0x41C];
  al |= _data[0x41B];
  if ( !al ) // jz 
    goto loc_code_319;
  goto loc_code_427;
loc_code_349:
  *(WORD*)&_data[0x4] = 4;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_4090();
  sub_58BD();
loc_code_364:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3E90();
  sub_40C2();
  sub_3150();
  sub_1E63();
  al = _data[0x552];
  al |= _data[0x553];
  al |= _data[0x551];
  al |= _data[0x41C];
  al |= _data[0x41B];
  if ( !al ) // jz 
    goto loc_code_364;
  goto loc_code_427;
loc_code_394:
  *(WORD*)&_data[0x4] = 3;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_3B30();
  sub_3C90();
  sub_58BD();
loc_code_3B2:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3CB1();
  sub_3B42();
  sub_3150();
  sub_1E63();
  al = _data[0x552];
  al |= _data[0x553];
  al |= _data[0x551];
  al |= _data[0x41C];
  al |= _data[0x41B];
  if ( !al ) // jz 
    goto loc_code_3B2;
  goto loc_code_427;
loc_code_3E2:
  *(WORD*)&_data[0x4] = 1;
  sub_1BF0();
  sub_2790();
  sub_7A1();
  sub_3405();
  sub_1E40();
  sub_58BD();
loc_code_3FA:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3150();
  sub_1E63();
  sub_3850();
  if ( _data[0x554] != 0 ) // jnz 
    goto loc_code_459;
  al = _data[0x552];
  al |= _data[0x551];
  al |= _data[0x41B];
  al |= _data[0x41C];
  if ( !al ) // jz 
    goto loc_code_3FA;
loc_code_427:
  if ( _data[0x41B] == 0 ) // jz 
    goto loc_code_431;
  goto loc_code_AE;
loc_code_431:
  if ( _data[0x41C] == 0 ) // jz 
    goto loc_code_43B;
  goto loc_code_A3;
loc_code_43B:
  if ( _data[0x552] == 0 ) // jz 
    goto loc_code_447;
  _data[0x419] = 0;
loc_code_447:
  ax = *(WORD*)&_data[0x4];
  *(WORD*)&_data[0x6] = ax;
  *(WORD*)&_data[0x4] = 0;
  sub_1BF0();
  goto loc_code_F3;
loc_code_459:
  *(WORD*)&_data[0x4] = 2;
  sub_1BF0();
  sub_2790();
  sub_35C9();
  sub_7A1();
  _data[0x1CBF] = 0;
  _data[0x1CB8] = 0;
  sub_58BD();
loc_code_478:
  sub_1338();
  sub_1200();
  sub_546D();
  sub_8E5();
  sub_3675();
  sub_37E5();
  al = _data[0x552];
  al |= _data[0x553];
  al |= _data[0x41C];
  al |= _data[0x41B];
  if ( !al ) // jz 
    goto loc_code_478;
  goto loc_code_427;
}

/*
  unknown_command(); // align 4
*/
void sub_4A0()
{
  _data[0x531]--;
  if ( !_data[0x531] ) // jz 
    goto loc_code_4A7;
  return;
loc_code_4A7:
  _data[0x531]++;
  if ( sub_13D8() ) // jnz 
    return;
  if ( _data[0x55A] != 0 ) // jnz 
    return;
  if ( _data[0x1673] != 0 ) // jnz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[0x544] ) // jz 
    return;
  *(WORD*)&_data[0x544] = dx;
  bx = *(WORD*)&_data[0x8];
  al = _data[bx + 0x532];
  if ( _data[0x57B] > 0x60 ) // ja 
    goto loc_code_4DF;
  al >>= 1;
  al >>= 1;
loc_code_4DF:
  _data[0x531] = al;
  bx = *(WORD*)&_data[0x52F];
  sub_658();
  if ( zf ) // jz 
    goto loc_code_50C;
  al = _data[0x525];
  al += *(WORD*)&_data[bx + 0x529];
  if ( al < 4 ) // jb 
    return;
loc_code_4F6:
  sub_2DFD();
  dl &= 3;
  if ( dl == _data[0x52F] ) // jz 
    goto loc_code_4F6;
  if ( dl == 3 ) // jz 
    goto loc_code_4F6;
  bl = dl;
  goto loc_code_535;
loc_code_50C:
  al = _data[bx + 0x529];
  _data[0x525] += al;
  if ( _data[0x525] < 4 ) // jb 
    goto loc_code_583;
  sub_2DFD();
  if ( dl > 0x40 ) // ja 
    goto loc_code_539;
loc_code_523:
  sub_2DFD();
  dl &= 3;
  if ( dl == 3 ) // jz 
    goto loc_code_523;
  bl = dl;
  sub_658();
  if ( !zf ) // jnz 
    goto loc_code_523;
loc_code_535:
  *(WORD*)&_data[0x52F] = bx;
loc_code_539:
  al = _data[bx + 0x526];
  _data[0x525] = al;
  ax = seg_data;
  es = ax;
  di = 0x4D7;
  ah = _data[bx + 0x52C];
  bx = *(WORD*)&_data[0x8];
  bl = _data[bx + 0x2ABA];
  bh = ah;
  sub_67D();
  if ( *(WORD*)&_data[0x52F] == 1 ) // jz 
    goto loc_code_56E;
  _data[0x540] >>= 1;
  sub_633();
  _data[0x540] >>= 1;
  goto loc_code_57C;
loc_code_56E:
  al = _data[0x540];
  al >>= 1;
  al >>= 1;
  sub_633();
  _data[0x540] >>= 1;
loc_code_57C:
  sub_633();
  bx = *(WORD*)&_data[0x52F];
loc_code_583:
  if ( _data[0x4D6] == 0 ) // jz 
    goto loc_code_5D0;
  ax = *(WORD*)&_data[0x579];
  if ( bl == 1 ) // jz 
    goto loc_code_5BF;
  (*(WORD*)&_data[0x55F])++;
  ax += 4;
  if ( ax < 0x123 ) // jb 
    goto loc_code_5CD;
loc_code_59E:
  _data[0x55B] = 0x11;
  _data[0x571] = 1;
  _data[0x576] = 1;
  _data[0x578] = 0x18;
  _data[0x572] = 1;
  _data[0x55C] = 0;
  goto loc_code_5D0;
loc_code_5BF:
  (*(WORD*)&_data[0x55F])--;
  cf = (ax < 4); // cf-insertion
  ax -= 4;
  if ( cf ) // jb 
    goto loc_code_59E;
  if ( ax < 8 ) // jb 
    goto loc_code_59E;
loc_code_5CD:
  *(WORD*)&_data[0x579] = ax;
loc_code_5D0:
  _push(ds);
  bx <<= 1;
  ax = *(WORD*)&_data[bx + 0x51D];
  *(WORD*)&_data[0x523] = ax;
  si = *(WORD*)&_data[bx + 0x517];
  ax = 0x0B800;
  ds = ax;
  es = ax;
  di = si;
  if ( bx != 2 ) // jnz 
    goto loc_code_5F1;
  _cld();
  di--;
  goto loc_code_5F3;
loc_code_5F1:
  _std();
  di++;
loc_code_5F3:
  cx = 0x27F;
  _push(di);
  _push(si);
  _rep_movsb();
  _pop(si);
  _pop(di);
  si += 0x2000;
  di += 0x2000;
  cx = 0x280;
  _rep_movsb();
  _pop(ds);
  di = *(WORD*)&_data[ds*16+0x523];
  bl = _data[ds*16+0x525];
  bh = 0;
  bx += 0x4D7;
  cx = 0x10;
loc_code_61B:
  al = _data[bx];
  _video[0*es*16+di] = al;
  bx += 4;
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_630;
  di += 0x50;
loc_code_630:
  if ( --cx )
    goto loc_code_61B;
}

void sub_633()
{
  _lahf();
  bx = *(WORD*)&_data[ds*16+0x52F];
  bl = _data[bx + 0x541];
  cx = 5;
  if ( bl == 9 ) // jz 
    goto loc_code_64E;
loc_code_644:
//
  _sahf();
  _rcr(_data[bx + 0x1016], 1);
  _lahf();
  bx++;
  if ( --cx )
    goto loc_code_644;
  return;
loc_code_64E:
//
  _sahf();
  _rcl(_data[bx + 0x1016], 1);
  _lahf();
  bx--;
  if ( --cx )
    goto loc_code_64E;
}

void sub_658()
{
	zf = 0;
  _data[ds*16+0x4D6] = 0;
  al = _data[ds*16+0x57C];
  if ( al < _data[bx + 0x53D] ) // jb 
    goto loc_code_679;
  if ( al >= _data[bx + 0x53A] ) // jnb 
    goto loc_code_679;
  if ( _data[ds*16+0x55C] >= 1 ) // jnb 
    goto loc_code_674;
  return;
loc_code_674:
  _data[ds*16+0x4D6] = 1;
loc_code_679:
  zf = 1;
  //fix_code(); // zf=1
}

/*
  return;
*/
void sub_67D()
{
  _data[ds*16+0x540] = 0;
  _cld();
  cx = 0x20;
  ax = 0x0AAAA;
  _rep_stosw();
  di -= 0x40;
  ax = 0x4444;
  *(WORD*)&_data[es*16+di+4] = ax;
  *(WORD*)&_data[es*16+di+6] = ax;
  sub_2DFD();
  if ( dl < bl ) // jb 
    return;
  if ( dh > bh ) // ja 
    goto loc_code_6A5;
  return;
loc_code_6A5:
  sub_2DFD();
  if ( dl < 0x18 ) // jb 
    goto loc_code_6C7;
  if ( dl < 0x60 ) // jb 
    goto loc_code_6D0;
  _push(di);
  sub_6DE();
  al <<= 1;
  _data[ds*16+0x540] = al;
  _pop(di);
  di += 2;
  sub_6DE();
  *(WORD*)&_data[ds*16+0x540] |= al;
  return;
loc_code_6C7:
  cx = 0x20;
  si = 0x490;
  goto loc_code_6D6;
loc_code_6D0:
  cx = 0x10;
  si = 0x460;
loc_code_6D6:
  _rep_movsw();
  _data[ds*16+0x540] = 3;
}

void sub_6DE()
{
  sub_2DFD();
  dx &= 6;
  if ( dl != 6 ) // jnz 
    goto loc_code_6ED;
  al = 0;
  return;
loc_code_6ED:
  bx = dx;
  si = *(WORD*)&_data[bx + 0x4D0];
  cx = 8;
loc_code_6F6:
  _lodsw();
  _stosw();
  di += 2;
  if ( --cx )
    goto loc_code_6F6;
  al = 1;
}

void sub_700()
{
  *(WORD*)&_data[ds*16+0x57D] = 0;
  *(WORD*)&_data[ds*16+0x684] = 0;
}

void sub_70D()
{
  cx = 0;
  ah = 1;
  if ( *(WORD*)&_data[ds*16+0x579] < 0x0A0 ) // jb 
    goto loc_code_71F;
  cx = 0x128;
  ah = 0x0FF;
loc_code_71F:
  _data[ds*16+0x56E] = ah; /////////////////////
  _data[ds*16+0x558] = 3;
  _data[ds*16+0x559] = 0x0C;
  dl = 0x0B4;
  *(WORD*)&_data[ds*16+0x579] = cx;
  _data[ds*16+0x57B] = dl;
  _data[ds*16+0x57C] = 0x0E6;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x55F] = ax;
  *(WORD*)&_data[ds*16+0x561] = 0x0B03;
  sub_1124();
  _data[ds*16+0x571] = 0;
  *(WORD*)&_data[ds*16+0x572] = 2;
  _data[ds*16+0x576] = 1;
  _data[ds*16+0x55B] = 0;
  _data[ds*16+0x550] = 0;
  _data[ds*16+0x55C] = 0;
  _data[ds*16+0x55A] = 0;
  _data[ds*16+0x583] = 0;
  _data[ds*16+0x698] = 0;
  _data[ds*16+0x699] = 0;
  _data[ds*16+0x551] = 0;
  _data[ds*16+0x584] = 0;
  _data[ds*16+0x552] = 0;
  *(WORD*)&_data[ds*16+0x554] = 0;
  _data[ds*16+0x553] = 0;
  _data[ds*16+0x127C] = 0;
  sub_700();
}

void sub_7A1()
{
  bx = *(WORD*)&_data[ds*16+4];
  if ( bx != 0 ) // jnz 
    goto loc_code_7B5;
  cx = *(WORD*)&_data[ds*16+1];
  dl = _data[ds*16+3];
  goto loc_code_7BF;
loc_code_7B5:
  dl = _data[bx + 0x5E9];
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x5D9];
loc_code_7BF:
  *(WORD*)&_data[ds*16+0x579] = cx;
  _data[ds*16+0x57B] = dl;
  al = dl;
  al += 0x32;
  _data[ds*16+0x57C] = al;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x55F] = ax;
  ax = *(WORD*)&_data[ds*16+0x0FB2];
  *(WORD*)&_data[ds*16+0x569] = ax;
  ax = *(WORD*)&_data[ds*16+0x0FBE];
  *(WORD*)&_data[ds*16+0x567] = ax;
  *(WORD*)&_data[ds*16+0x561] = ax;
  sub_1124();
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x56E] = 0;
  _data[ds*16+0x576] = 1;
  _data[ds*16+0x578] = 0x40;
  al = 0x0A;
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_805;
  al = 0;
loc_code_805:
  _data[ds*16+0x55B] = al;
  _data[ds*16+0x550] = 0;
  _data[ds*16+0x55C] = 0;
  _data[ds*16+0x55A] = 0;
  _data[ds*16+0x583] = 0;
  _data[ds*16+0x698] = 0;
  _data[ds*16+0x699] = 0;
  _data[ds*16+0x551] = 0;
  _data[ds*16+0x584] = 0;
  _data[ds*16+0x552] = 0;
  *(WORD*)&_data[ds*16+0x554] = 0;
  _data[ds*16+0x553] = 0;
  _data[ds*16+0x127C] = 0;
  sub_700();
  if ( *(WORD*)&_data[ds*16+4] != 2 ) // jnz 
    return;
  _data[ds*16+0x576] = 0x10;
  *(WORD*)&_data[ds*16+0x574] = 0x10;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5F1] = dx;
  _data[ds*16+0x5F3] = 0;
  _data[ds*16+0x5F4] = 5;
  _data[ds*16+0x5F5] = 1;
}

void sub_872()
{
  *(WORD*)&_data[ds*16+0x592A] = 0x400;
  if ( _data[ds*16+0x584] == 0 ) // jz 
    goto loc_code_880;
  return;
loc_code_880:
  _data[ds*16+0x576] = 8;
  dl = 0x0FF;
  al = _data[ds*16+0x57B];
  if ( al >= _data[ds*16+0x2652] ) // jnb 
    goto loc_code_892;
  dl = 1;
loc_code_892:
  _data[ds*16+0x571] = dl;
  ax = *(WORD*)&_data[ds*16+0x579];
  ax -= *(WORD*)&_data[ds*16+0x2650];
  dl = 0x0FF;
  if ( unknown_condition() ) // ja cf=0 & zf=0
    goto loc_code_8A5;
  dl = 1;
  ax = ~ax;
loc_code_8A5:
  _data[ds*16+0x56E] = dl;
  if ( ah == 0 ) // jz 
    goto loc_code_8B1;
  ax = 0x0FF;
loc_code_8B1:
  al = ~al;
  if ( al >= 0x30 ) // jnb 
    goto loc_code_8B9;
  al = 0x30;
loc_code_8B9:
  bl = al;
  bl >>= 1;
  bl >>= 1;
  al -= bl;
  _data[ds*16+0x578] = al;
  cl = 5;
  al >>= cl;
  *(WORD*)&_data[ds*16+0x572] = ax;
  _data[ds*16+0x55C] = 0;
  _data[ds*16+0x39E0] = 0;
  _data[ds*16+0x577] = 1;
  _data[ds*16+0x55B] = 0x10;
  _data[ds*16+0x584] = 1;
}

void sub_8E5()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x57D] ) // jnz 
    goto loc_code_8FD;
  if ( *(WORD*)&_data[ds*16+0x684] == 0 ) // jz 
    return;
  (*(WORD*)&_data[ds*16+0x684])--;
  if ( !*(WORD*)&_data[ds*16+0x684] ) // jz 
    goto loc_code_90C;
  return;
loc_code_8FD:
  ax = 0x20;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_909;
  ax >>= 1;
loc_code_909:
  *(WORD*)&_data[ds*16+0x684] = ax;
loc_code_90C:
  if ( *(WORD*)&_data[ds*16+4] == 2 ) // jz 
    goto loc_code_91D;
  cl = _data[ds*16+0x571];
  cl |= *(WORD*)&_data[ds*16+0x56E];
  if ( cl ) // jnz 
    goto loc_code_926;
loc_code_91D:
  _push(dx);
  _push(ax);
  zf = sub_13D8() == 0;
  _pop(ax);
  _pop(dx);
  if ( zf ) // jz 
    return;
loc_code_926:
  *(WORD*)&_data[ds*16+0x57D] = dx;
  *(WORD*)&_data[ds*16+0x57F] = ax;
  if ( *(WORD*)&_data[ds*16+4] != 4 ) // jnz 
    goto loc_code_93B;
  if ( _data[ds*16+0x39E1] != 0 ) // jnz 
    return;
loc_code_93B:
  if ( *(WORD*)&_data[ds*16+4] != 6 ) // jnz 
    goto loc_code_949;
  if ( _data[ds*16+0x44BD] != 0 ) // jnz 
    return;
loc_code_949:
  if ( *(WORD*)&_data[ds*16+4] == 2 ) // jz 
    goto loc_code_953;
  goto loc_code_BAC;
loc_code_953:
  si = *(WORD*)&_data[ds*16+8];
  si <<= 1;
  ax = *(WORD*)&_data[ds*16+0x57D];
  ax -= *(WORD*)&_data[ds*16+0x5F1];
  if ( ax < *(WORD*)&_data[si + 0x589] ) // jb 
    goto loc_code_9D6;
  if ( ax < *(WORD*)&_data[si + 0x599] ) // jb 
    goto loc_code_971;
  _data[ds*16+0x552] = 1;
loc_code_971:
  (_data[ds*16+0x5F5])--;
  if ( _data[ds*16+0x5F5] ) // jnz 
    goto loc_code_9B9;
  sub_597F();
  _data[ds*16+0x5F5] = 6;
  al = _data[ds*16+0x5F4];
  if ( _data[ds*16+0x57B] < 0x0B3 ) // jb 
    goto loc_code_992;
  if ( al >= 0x0C8 ) // jnb 
    goto loc_code_992;
  al += 0x1E;
  _data[ds*16+0x5F4] = al;
loc_code_992:
  dl = _data[ds*16+0x57B];
  cf = (dl < al); // cf-insertion
  dl -= al;
  if ( !cf ) // jnb 
    goto loc_code_99C;
  dl = 0;
loc_code_99C:
  cx = *(WORD*)&_data[ds*16+0x579];
  dl &= 0x0F8;
  sub_2CB0();
  di = ax;
  si = 0x64E;
  ax = 0x0B800;
  es = ax;
  bp = 0x0E;
  cx = 0x503;
  sub_2D35();
loc_code_9B9:
  _data[ds*16+0x56E] = 0;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x5F3] = 1;
  _data[ds*16+0x576] = 0x20;
  bx = 0;
  ah = 0x0B;
  _int(0x10);
  goto loc_code_A86;
loc_code_9D6:
  si = *(WORD*)&_data[ds*16+8];
  si <<= 1;
  bx = 0;
  if ( ax < *(WORD*)&_data[si + 0x5A9] ) // jb 
    goto loc_code_9F6;
  bl++;
  if ( ax < *(WORD*)&_data[si + 0x5B9] ) // jb 
    goto loc_code_9F6;
  bl = 5;
  if ( ax < *(WORD*)&_data[si + 0x5C9] ) // jb 
    goto loc_code_9F6;
  bl--;
loc_code_9F6:
  ah = 0x0B;
  _int(0x10);
  al = _data[ds*16+0x56E];
  _data[ds*16+0x56F] = al;
  al = _data[ds*16+0x571];
  _data[ds*16+0x570] = al;
  al = _data[ds*16+0x698];
  if ( al != 0 ) // jnz 
    goto loc_code_A1A;
  if ( *(WORD*)&_data[ds*16+0x574] < 0x10 ) // jb 
    goto loc_code_A2E;
  (*(WORD*)&_data[ds*16+0x574])--;
  goto loc_code_A37;
loc_code_A1A:
  if ( al != _data[ds*16+0x56E] ) // jnz 
    goto loc_code_A2E;
  if ( *(WORD*)&_data[ds*16+0x574] >= 0x30 ) // jnb 
    goto loc_code_A37;
  *(WORD*)&_data[ds*16+0x574] += 3;
  goto loc_code_A37;
loc_code_A2E:
  _data[ds*16+0x56E] = al;
  *(WORD*)&_data[ds*16+0x574] = 0x20;
loc_code_A37:
  ax = *(WORD*)&_data[ds*16+0x574];
  cl = 3;
  ax >>= cl;
  bx = *(WORD*)&_data[ds*16+8];
  bl <<= 1;
  if ( ax <= *(WORD*)&_data[bx + 0x66C] ) // jbe 
    goto loc_code_A4E;
  ax = *(WORD*)&_data[bx + 0x66C];
loc_code_A4E:
  *(WORD*)&_data[ds*16+0x572] = ax;
  sub_FC9();
  al = _data[ds*16+0x699];
  if ( al != 0 ) // jnz 
    goto loc_code_A6A;
  al = ~al;
  if ( _data[ds*16+0x576] < 0x10 ) // jb 
    goto loc_code_A7E;
  (_data[ds*16+0x576])--;
  goto loc_code_A86;
loc_code_A6A:
  if ( al != _data[ds*16+0x571] ) // jnz 
    goto loc_code_A7E;
  if ( _data[ds*16+0x576] >= 0x40 ) // jnb 
    goto loc_code_A86;
  _data[ds*16+0x576] += 4;
  goto loc_code_A86;
loc_code_A7E:
  _data[ds*16+0x571] = al;
  _data[ds*16+0x576] = 0x20;
loc_code_A86:
  si = *(WORD*)&_data[ds*16+8];
  dl = _data[ds*16+0x57B];
  cl = 4;
  bl = _data[ds*16+0x576];
  bl >>= cl;
  if ( bl <= _data[si + 0x67C] ) // jbe 
    goto loc_code_AA0;
  bl = _data[si + 0x67C];
loc_code_AA0:
  al = _data[ds*16+0x571];
  if ( al < 1 ) // jb 
    goto loc_code_ACE;
  if ( unknown_condition() ) // jnz 
    goto loc_code_AB4;
  dl += bl;
  if ( dl < 0x0B4 ) // jb 
    goto loc_code_ACE;
  dl = 0x0B3;
  goto loc_code_ACE;
loc_code_AB4:
  cf = (dl < bl); // cf-insertion
  dl -= bl;
  if ( cf ) // jb 
    goto loc_code_ABD;
  if ( dl > 3 ) // ja 
    goto loc_code_ACE;
loc_code_ABD:
  ax = *(WORD*)&_data[ds*16+0x9B8];
  if ( ax != *(WORD*)&_data[ds*16+0x55D] ) // jnz 
    goto loc_code_ACC;
  ax = *(WORD*)&_data[ds*16+0x57D];
  *(WORD*)&_data[ds*16+0x5F1] = ax;
loc_code_ACC:
  dl = 2;
loc_code_ACE:
  _data[ds*16+0x57B] = dl;
  cx = *(WORD*)&_data[ds*16+0x579];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x563] = ax;
  if ( _data[ds*16+0x5F3] == 0 ) // jz 
    goto loc_code_AE9;
  bx = 0x10;
  goto loc_code_B64;
loc_code_AE9:
  al = _data[ds*16+0x56E];
  if ( al != _data[ds*16+0x56F] ) // jnz 
    goto loc_code_AFB;
  al = _data[ds*16+0x571];
  if ( al == _data[ds*16+0x570] ) // jz 
    goto loc_code_B00;
loc_code_AFB:
  bx = 0x18;
  goto loc_code_B64;
loc_code_B00:
  (*(WORD*)&_data[ds*16+0x587])++;
  bx = *(WORD*)&_data[ds*16+0x587];
  al = _data[ds*16+0x698];
  al |= *(WORD*)&_data[ds*16+0x699];
  if ( al ) // jnz 
    goto loc_code_B13;
  bl >>= 1;
loc_code_B13:
  if ( _data[ds*16+0x57B] < 0x0B3 ) // jb 
    goto loc_code_B21;
  if ( _data[ds*16+0x571] == 1 ) // jz 
    goto loc_code_B3C;
loc_code_B21:
  if ( _data[ds*16+0x57B] > 4 ) // ja 
    goto loc_code_B2F;
  if ( _data[ds*16+0x699] != 0 ) // jnz 
    goto loc_code_B53;
loc_code_B2F:
  al = _data[ds*16+0x576];
  ah = 0;
  ax >>= 1;
  if ( ax >= *(WORD*)&_data[ds*16+0x574] ) // jnb 
    goto loc_code_B53;
loc_code_B3C:
  if ( _data[ds*16+0x56E] == 0 ) // jz 
    goto loc_code_B53;
  bx &= 6;
  if ( _data[ds*16+0x56E] == 1 ) // jz 
    goto loc_code_B64;
  bl |= 8;
  goto loc_code_B64;
loc_code_B53:
  bx &= 2;
  bl |= 0x10;
  if ( _data[ds*16+0x571] != 1 ) // jnz 
    goto loc_code_B64;
  bl += 4;
loc_code_B64:
  ax = *(WORD*)&_data[bx + 0x9A6];
  *(WORD*)&_data[ds*16+0x55D] = ax;
  ax = *(WORD*)&_data[bx + 0x9C0];
  *(WORD*)&_data[ds*16+0x565] = ax;
  al = 0x30;
  cx = 0x2BC;
  if ( _data[ds*16+0x697] < 0x0FD ) // jb 
    goto loc_code_B97;
  if ( unknown_condition() ) // jz 
    goto loc_code_B85;
  al = 8;
  cx = 0x3E8;
loc_code_B85:
  if ( _data[ds*16+0x57B] > al ) // ja 
    goto loc_code_B97;
loc_code_B8B:
  if ( sub_13D8() ) // jnz 
    goto loc_code_B8B;
loc_code_B90:
  if ( !sub_13D8() ) // jz 
    goto loc_code_B90;
loc_code_B95:
  if ( --cx )
    goto loc_code_B95;
loc_code_B97:
  sub_11E3();
  ax = *(WORD*)&_data[ds*16+0x563];
  *(WORD*)&_data[ds*16+0x55F] = ax;
  sub_1145();
  sub_34A0();
  if ( unknown_condition() ) // jnb cf=0
    return;
  sub_1145();
  return;
loc_code_BAC:
  sub_1B7A();
  if ( !cf ) // jnb 
    goto loc_code_BB2;
  return;
loc_code_BB2:
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x558] == 0 ) // jz 
    goto loc_code_C1C;
  if ( _data[ds*16+0x559] == 0 ) // jz 
    goto loc_code_BD3;
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    return;
  (_data[ds*16+0x559])--;
  return;
loc_code_BD3:
  (_data[ds*16+0x558])--;
  if ( _data[ds*16+0x558] ) // jnz 
    goto loc_code_BE5;
  *(WORD*)&_data[ds*16+0x572] = 8;
  sub_FC9();
  goto loc_code_C1C;
loc_code_BE5:
  sub_1020();
  *(WORD*)&_data[ds*16+0x55D] = bx;
  al = _data[ds*16+0x558];
  ah = _data[ds*16+0x56E];
  sub_F87();
  if ( _data[ds*16+0x558] == 2 ) // jz 
    goto loc_code_C00;
  sub_11E3();
loc_code_C00:
  sub_1B7A();
  if ( cf ) // jb 
    return;
  sub_20F5();
  if ( cf ) // jb 
    return;
  dl = _data[ds*16+0x57B];
  cx = *(WORD*)&_data[ds*16+0x579];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x55F] = ax;
  sub_1145();
  return;
loc_code_C1C:
  if ( _data[ds*16+0x55C] < 1 ) // jb 
    goto loc_code_C6A;
  if ( _data[ds*16+0x55C] != 1 ) // jnz 
    goto loc_code_C5F;
  (_data[ds*16+0x55C])++;
  *(WORD*)&_data[ds*16+0x572] = 6;
  dl = _data[ds*16+0x57B];
  cx = *(WORD*)&_data[ds*16+0x579];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x563] = ax;
  sub_11E3();
  sub_1B7A();
  if ( cf ) // jb 
    return;
  sub_20F5();
  if ( cf ) // jb 
    return;
  ax = *(WORD*)&_data[ds*16+0x563];
  *(WORD*)&_data[ds*16+0x55F] = ax;
  *(WORD*)&_data[ds*16+0x565] = 0x0E03;
  *(WORD*)&_data[ds*16+0x55D] = 0x9DA;
  sub_1145();
loc_code_C5F:
  if ( _data[ds*16+0x699] != 0 ) // jnz 
    goto loc_code_C67;
  return;
loc_code_C67:
  goto loc_code_E78;
loc_code_C6A:
  if ( _data[ds*16+0x571] != 0 ) // jnz 
    goto loc_code_C74;
  goto loc_code_E23;
loc_code_C74:
  sub_FC9();
  if ( !cf ) // jnb cf=0
    goto loc_code_C90;
  _data[ds*16+0x56E] = 0;
  _data[ds*16+0x576] = 2;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x55B] = 0;
  goto loc_code_CC1;
loc_code_C90:
  al = _data[ds*16+0x578];
  cf = (*(WORD*)&_data[ds*16+0x577] < al); // cf-insertion
  *(WORD*)&_data[ds*16+0x577] -= al;
  if ( !cf ) // jnb 
    goto loc_code_CC1;
  if ( _data[ds*16+0x571] == 1 ) // jz 
    goto loc_code_CB6;
  if ( _data[ds*16+0x576] <= 1 ) // jbe 
    goto loc_code_CAE;
  (_data[ds*16+0x576])--;
  goto loc_code_CC1;
loc_code_CAE:
  _data[ds*16+0x571] = 1;
  goto loc_code_CC1;
loc_code_CB6:
  if ( _data[ds*16+0x576] >= 4 ) // jnb 
    goto loc_code_CC1;
  (_data[ds*16+0x576])++;
loc_code_CC1:
  if ( _data[ds*16+0x55A] != 0 ) // jnz 
    goto loc_code_CE7;
  if ( _data[ds*16+0x55B] == 0 ) // jz 
    goto loc_code_CD5;
  (_data[ds*16+0x55B])--;
  if ( _data[ds*16+0x55B] ) // jnz 
    goto loc_code_CE7;
loc_code_CD5:
  if ( _data[ds*16+0x571] != 1 ) // jnz 
    goto loc_code_CE7;
  sub_1608();
  if ( !cf ) // jnb 
    goto loc_code_CE7;
  al = _data[ds*16+0x57C];
  goto loc_code_D29;
loc_code_CE7:
  al = _data[ds*16+0x57C];
  if ( _data[ds*16+0x571] == 1 ) // jz 
    goto loc_code_D06;
  cf = (al < *(WORD*)&_data[ds*16+0x576]); // cf-insertion
  al -= *(WORD*)&_data[ds*16+0x576];
  if ( !cf ) // jnb 
    goto loc_code_D4F;
  al = 0;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x576] = 1;
  goto loc_code_D4F;
loc_code_D06:
  al += *(WORD*)&_data[ds*16+0x576];
  if ( al <= 0x0E6 ) // jbe 
    goto loc_code_D4F;
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_D22;
  if ( al < 0x0F8 ) // jb 
    goto loc_code_D4F;
  al = 0x0F8;
  _data[ds*16+0x551] = 1;
  goto loc_code_D4F;
loc_code_D22:
  al = 0x0E6;
  _data[ds*16+0x550] = 0;
loc_code_D29:
  _data[ds*16+0x571] = 0;
  _data[ds*16+0x584] = 0;
  *(WORD*)&_data[ds*16+0x572] = 2;
  _data[ds*16+0x55B] = 0;
  _data[ds*16+0x55A] = 0;
  if ( _data[ds*16+0x55C] == 0 ) // jz 
    goto loc_code_D4F;
  _push(ax);
  sub_5AC2();
  _pop(ax);
loc_code_D4F:
  _data[ds*16+0x57C] = al;
  cf = (al < 0x32); // cf-insertion
  al -= 0x32;
  if ( !cf ) // jnb 
    goto loc_code_D58;
  al = 0;
loc_code_D58:
  _data[ds*16+0x57B] = al;
  dl = _data[ds*16+0x57B];
  cx = *(WORD*)&_data[ds*16+0x579];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x563] = ax;
  if ( _data[ds*16+0x583] != 0 ) // jnz 
    goto loc_code_D73;
  sub_11E3();
loc_code_D73:
  sub_1B7A();
  if ( cf ) // jb 
    goto loc_code_DC4;
  sub_20F5();
  if ( cf ) // jb 
    goto loc_code_DC4;
  ax = *(WORD*)&_data[ds*16+0x563];
  *(WORD*)&_data[ds*16+0x55F] = ax;
  if ( _data[ds*16+0x584] == 0 ) // jz 
    goto loc_code_DA1;
  *(WORD*)&_data[ds*16+0x585] += 2;
  bx = *(WORD*)&_data[ds*16+0x585];
  bx &= 0x0E;
  ax = *(WORD*)&_data[bx + 0x0FC2];
  bx = *(WORD*)&_data[bx + 0x0FD2];
  goto loc_code_DA8;
loc_code_DA1:
  ax = *(WORD*)&_data[ds*16+0x569];
  bx = *(WORD*)&_data[ds*16+0x567];
loc_code_DA8:
  *(WORD*)&_data[ds*16+0x55D] = ax;
  *(WORD*)&_data[ds*16+0x565] = bx;
  al = 0x32;
  zf = (al == *(WORD*)&_data[ds*16+0x57C]); // zf-insertion
  cf = (al < *(WORD*)&_data[ds*16+0x57C]); // zf-insertion
  al -= *(WORD*)&_data[ds*16+0x57C];
  if ( zf ) // jz 
    goto loc_code_DDE;
  if ( cf ) // jb cf=1
    goto loc_code_DDE;
  cx = 0x168;
loc_code_DBC:
  if ( --cx )
    goto loc_code_DBC;
  zf = (bh == al); // zf-insertion
  cf = (bh < al); // zf-insertion
  bh -= al;
  if ( zf ) // jz 
    goto loc_code_DC4;
  if ( !cf ) // jnb cf=0
    goto loc_code_DCA;
loc_code_DC4:
  _data[ds*16+0x583] = 1;
  return;
loc_code_DCA:
  *(WORD*)&_data[ds*16+0x565] = bx;
  ah = bl;
  ah <<= 1;
  ax = (WORD)ah * (WORD)al;

  ax += *(WORD*)&_data[ds*16+0x569];
  *(WORD*)&_data[ds*16+0x55D] = ax;
  goto loc_code_E1F;
loc_code_DDE:
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_DEE;
  al = _data[ds*16+0x57B];
  cf = (al < 0x0BB); // cf-insertion
  al -= 0x0BB;
  if ( cf ) // jb 
    goto loc_code_E1F;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_DFC;
loc_code_DEE:
  if ( _data[ds*16+0x550] != 2 ) // jnz 
    goto loc_code_E1F;
  al = _data[ds*16+0x57B];
  cf = (al < 0x5E); // cf-insertion
  al -= 0x5E;
  if ( cf ) // jb 
    goto loc_code_E1F;
loc_code_DFC:
  zf = (bh == al); // zf-insertion
  bh -= al;
  if ( zf ) // jz 
    goto loc_code_E02;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_E16;
loc_code_E02:
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_E0F;
  _data[ds*16+0x551] = 1;
  return;
loc_code_E0F:
  sub_70D();
  sub_59CB();
  return;
loc_code_E16:
  *(WORD*)&_data[ds*16+0x565] = bx;
  _data[ds*16+0x576] = 2;
loc_code_E1F:
  sub_1145();
  return;
loc_code_E23:
  if ( *(WORD*)&_data[ds*16+4] == 7 ) // jz 
    goto loc_code_E31;
  if ( _data[ds*16+0x57B] >= 0x0B4 ) // jnb 
    goto loc_code_E78;
loc_code_E31:
  sub_1608();
  if ( cf ) // jb 
    goto loc_code_E43;
  _data[ds*16+0x56E] = 0;
  _data[ds*16+0x571] = 1;
  goto loc_code_EB1;
loc_code_E43:
  if ( *(WORD*)&_data[ds*16+4] != 0 ) // jnz 
    goto loc_code_E78;
  sub_22F7();
  if ( cf ) // jb 
    goto loc_code_E56;
  _data[ds*16+0x56C] = 0;
  goto loc_code_E78;
loc_code_E56:
  if ( _data[ds*16+0x56C] != 0 ) // jnz 
    goto loc_code_E60;
  sub_591F();
loc_code_E60:
  _data[ds*16+0x699] = 1;
  _data[ds*16+0x56C] = 1;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_E74;
  dl = 0x0FF;
loc_code_E74:
  _data[ds*16+0x698] = dl;
loc_code_E78:
  al = _data[ds*16+0x56E];
  _data[ds*16+0x56F] = al;////////////
  al = _data[ds*16+0x698];
  _data[ds*16+0x56E] = al;
  al = _data[ds*16+0x699];
  _data[ds*16+0x571] = al;
  if ( al != 0 ) // jnz 
    goto loc_code_E91;
  goto loc_code_F34;
loc_code_E91:
  if ( _data[ds*16+0x571] != 1 ) // jnz 
    goto loc_code_EC9;
  if ( _data[ds*16+0x57B] < 0x0B4 ) // jb 
    goto loc_code_EB1;
  _data[ds*16+0x571] = 0;
  _data[ds*16+0x584] = 0;
  _data[ds*16+0x699] = 0;
  goto loc_code_F34;
loc_code_EB1:
  ah = 1;
  al = 0x20;
  _data[ds*16+0x55B] = 8;
  if ( _data[ds*16+0x550] != 1 ) // jnz 
    goto loc_code_EF1;
  _data[ds*16+0x550] = 0;
  goto loc_code_EF1;
loc_code_EC9:
  _data[ds*16+0x55B] = 0;
  ax = *(WORD*)&_data[ds*16+0x572];
  bl = al;
  if ( al <= 2 ) // jbe 
    goto loc_code_ED9;
  al -= 2;
loc_code_ED9:
  *(WORD*)&_data[ds*16+0x572] = ax;
  ah = 8;
  al = bl;
  al ^= 0x0F;
  cl = 4;
  al <<= cl;
  if ( _data[ds*16+0x550] != 1 ) // jnz 
    goto loc_code_EF1;
  (_data[ds*16+0x550])++;
loc_code_EF1:
  _data[ds*16+0x578] = al;
  _data[ds*16+0x576] = ah;
  _data[ds*16+0x577] = 1;
  _data[ds*16+0x55C] = 0;
  bl = _data[ds*16+0x56E];
  bl++;
  bl <<= 1;
  if ( _data[ds*16+0x571] == 0x0FF ) // jz 
    goto loc_code_F14;
  bl += 6;
loc_code_F14:
  bh = 0;
  ax = *(WORD*)&_data[bx + 0x0FAA];
  *(WORD*)&_data[ds*16+0x569] = ax;
  ax = *(WORD*)&_data[bx + 0x0FB6];
  *(WORD*)&_data[ds*16+0x567] = ax;
  _data[ds*16+0x39E0] = 0;
  if ( _data[ds*16+0x127C] == 0 ) // jz 
    return;
  sub_58F8();
  return;
loc_code_F34:
  if ( *(WORD*)&_data[ds*16+4] == 0 ) // jz 
    goto loc_code_F45;
  if ( *(WORD*)&_data[ds*16+4] == 7 ) // jz 
    goto loc_code_F45;
  sub_3445();
loc_code_F45:
  sub_FC9();
  dl = _data[ds*16+0x57B];
  cx = *(WORD*)&_data[ds*16+0x579];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x563] = ax;
  al = _data[ds*16+0x56E];
  al |= *(WORD*)&_data[ds*16+0x571];
				///////							 if ( (GetTickCount()/500) & 1) al = 0;
  // al = pohyb
  if ( al ) // jnz 
    goto loc_code_F63;
  sub_1069();
  return;
loc_code_F63:
  sub_1020();
  *(WORD*)&_data[ds*16+0x55D] = bx;
  sub_11E3();
  sub_1B7A();
  if ( cf ) // jb 
    return;
  sub_20F5();
  if ( cf ) // jb 
    return;
  ax = *(WORD*)&_data[ds*16+0x563];
  *(WORD*)&_data[ds*16+0x55F] = ax;   /// podozrive
  *(WORD*)&_data[ds*16+0x565] = 0x0B03;
  sub_1145();
}

void sub_F87()
{
  cx = 0x0B03;
  cl -= al;
  *(WORD*)&_data[ds*16+0x565] = cx;
  if ( ah == 0x0FF ) // jz 
    goto loc_code_FA6;
  ah = 0;
  al <<= 1;
  *(WORD*)&_data[ds*16+0x55D] += ax;
  *(WORD*)&_data[ds*16+0x579] = 0;
  goto loc_code_FB4;
loc_code_FA6:
  ah = 0;
  al <<= 1;
  al <<= 1;
  al <<= 1;
  ax += 0x128;
  *(WORD*)&_data[ds*16+0x579] = ax;
loc_code_FB4:
  _push(ds);
  _pop(es);
  si = *(WORD*)&_data[ds*16+0x55D];
  di = 0x0E;
  al = 3;
  sub_2D70();
  *(WORD*)&_data[ds*16+0x55D] = 0x0E;
}

void sub_FC9()
{
  *(WORD*)&_data[ds*16+0x5F6] = 8;
  *(WORD*)&_data[ds*16+0x5F8] = 0x123;
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_FE8;
  *(WORD*)&_data[ds*16+0x5F6] = 0x24;
  *(WORD*)&_data[ds*16+0x5F8] = 0x10F;
loc_code_FE8:
  ax = *(WORD*)&_data[ds*16+0x579];
  if ( _data[ds*16+0x56E] < 1 ) // jb 
    goto loc_code_101E;
  if ( _data[ds*16+0x56E] != 1 ) // jnz 
    goto loc_code_1007;
  ax += *(WORD*)&_data[ds*16+0x572]; //////// poloha
  if ( ax < *(WORD*)&_data[ds*16+0x5F8] ) // jb 
    goto loc_code_101B;
  ax = *(WORD*)&_data[ds*16+0x5F8];
  ax--;
  *(WORD*)&_data[ds*16+0x579] = ax;
  _stc();
  return;
loc_code_1007:
  cf = (ax < *(WORD*)&_data[ds*16+0x572]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x572]; ///////// poloha
  if ( cf ) // jb 
    goto loc_code_1013;
  if ( ax >= *(WORD*)&_data[ds*16+0x5F6] ) // jnb 
    goto loc_code_101B;
loc_code_1013:
  ax = *(WORD*)&_data[ds*16+0x5F6];
  *(WORD*)&_data[ds*16+0x579] = ax;
  _stc();
  return;
loc_code_101B:
  *(WORD*)&_data[ds*16+0x579] = ax;
loc_code_101E:
  _clc();
}

void sub_1020()
{
  al = _data[ds*16+0x56E];
  if ( al == _data[ds*16+0x56F] ) // jz 
    goto loc_code_102F;
  *(WORD*)&_data[ds*16+0x572] = 2;// velkost kroku, rychlost, speed
loc_code_102F:
  if ( *(WORD*)&_data[ds*16+0x572] >= 8 ) // jnb 
    goto loc_code_1045;
  (_data[ds*16+0x577])--;
  al = _data[ds*16+0x577];
  al &= 3;
  if ( al ) // jnz 
    goto loc_code_1045;
  (*(WORD*)&_data[ds*16+0x572])++;
loc_code_1045:
  bl = _data[ds*16+0x56B];
  bl++;
  if ( bl < 6 ) // jb 
    goto loc_code_1052;
  bl = 0;
loc_code_1052:
  _data[ds*16+0x56B] = bl;
  if ( _data[ds*16+0x56E] != 0x0FF ) // jnz 
    goto loc_code_1060;
  bl += 6;
loc_code_1060:
  bl <<= 1;
  bh = 0;
  bx = *(WORD*)&_data[bx + 0x0F7A];
}

void sub_1069()
{
  *(WORD*)&_data[ds*16+0x572] = 2;
  _data[ds*16+0x577] = 8;
  if ( *(WORD*)&_data[ds*16+0x561] != 0x0C02 ) // jnz 
    goto loc_code_1087;
  (_data[ds*16+0x56D])++;
  if ( _data[ds*16+0x56D] & 7 ) // jnz 
    return;
loc_code_1087:
  sub_11E3();
  sub_1B7A();
  if ( cf ) // jb 
    return;
  sub_20F5();
  if ( cf ) // jb 
    return;
  sub_2DFD();
  bl = dl;
  bx &= 0x0E;
  si = *(WORD*)&_data[bx + 0x0F92];
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x55F];
  bp = 0x5FA;
  *(WORD*)&_data[ds*16+0x561] = 0x0C02;
  cx = 0x602;
  sub_2D35();
  sub_2DFD();
  bl = dl;
  bx &= 6;
  si = *(WORD*)&_data[bx + 0x0FA2];
  di = *(WORD*)&_data[ds*16+0x55F];
  di += 0x0F0;
  bp = 0x612;
  cx = 0x602;
  sub_2D35();
  _data[ds*16+0x583] = 0;
}

void sub_10DD()
{
  _data[ds*16+0x55C] = 0;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x576] = 2;
  _data[ds*16+0x578] = 1;
  _data[ds*16+0x577] = 0x0FF;
  _data[ds*16+0x56E] = 0;
  _data[ds*16+0x55A] = 1;
  ax = *(WORD*)&_data[ds*16+0x0FAC];
  *(WORD*)&_data[ds*16+0x569] = ax;
  ax = *(WORD*)&_data[ds*16+0x0FB8];
  *(WORD*)&_data[ds*16+0x567] = ax;
  _data[ds*16+0x550] = 2;
}

void sub_1112()
{
  cx = *(WORD*)&_data[ds*16+0x579];
  dl = _data[ds*16+0x57B];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x55F] = ax;
  sub_1124();
}

void sub_1124()
{
  ax = seg_data;
  es = ax;
  di = 0x5FA;
  _push(ds);
  si = *(WORD*)&_data[ds*16+0x55F];
  ax = 0x0B800;
  ds = ax;
  cx = *(WORD*)&_data[es*16+0x561];
  sub_2DCA();
  _pop(ds);
  _data[ds*16+0x583] = 0;
}

void sub_1145()
{
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x55F];
  bp = 0x5FA;
  si = *(WORD*)&_data[ds*16+0x55D];
  cx = *(WORD*)&_data[ds*16+0x565];
  *(WORD*)&_data[ds*16+0x561] = cx;
  _data[ds*16+0x583] = 0;
  sub_2D35();
}

void sub_1166()
{
  dl = _data[ds*16+0x57B];
  cx = *(WORD*)&_data[ds*16+0x579];
  cf = (cx < 0x0C); // cf-insertion
  cx -= 0x0C;
  if ( !cf ) // jnb 
    goto loc_code_1175;
  cx = 0;
loc_code_1175:
  if ( cx < 0x10F ) // jb 
    goto loc_code_117E;
  cx = 0x10E;
loc_code_117E:
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x581] = ax;
  di = ax;
  ax = 0x0B800;
  es = ax;
  bp = 0x0E;
  si = 0x1679;
  cx = 0x1205;
  sub_2CCC();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x57F] = dx;
  *(WORD*)&_data[ds*16+0x5A3C] = 0;
  *(WORD*)&_data[ds*16+0x5A3E] = 0;
loc_code_11AB:
  sub_5A1C();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x57F];
  if ( dx < 0x0A ) // jb 
    goto loc_code_11AB;
  sub_5B21();
  di = *(WORD*)&_data[ds*16+0x581];
  si = 0x0E;
  cx = 0x1205;
  _data[ds*16+0x583] = 0;
  sub_2D9D();
  if ( _data[ds*16+0x1678] == 0 ) // jz 
    return;
  if ( _data[ds*16+0x1F80] == 0 ) // jz 
    return;
  (_data[ds*16+0x1F80])--;
}

void sub_11E3()
{
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x55F];
  si = 0x5FA;
  cx = *(WORD*)&_data[ds*16+0x561];
  sub_2D9D();
}

/*
  unknown_command(); // align 10h
*/
void sub_1200()
{
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x69F];
  if ( ax >= 2 ) // jnb 
    goto loc_code_1210;
  return;
loc_code_1210:
  *(WORD*)&_data[ds*16+0x69F] = dx;
  if ( _data[ds*16+0x69B] != 0 ) // jnz 
    goto loc_code_122E;
  sub_12C1();
  sub_13B7();
  dx = ax;
loc_code_1223:
  sub_13B7();
  ax -= dx;
  if ( ax < 0x0F8ED ) // jb 
    goto loc_code_1223;
  return;
loc_code_122E:
  dx = 0x201;
  _in(al, dx);
  al &= 0x10;
  _data[ds*16+0x69A] = al;
  _data[ds*16+0x69E] = 3;
  sub_13B7();
  *(WORD*)&_data[ds*16+0x69C] = ax;
  _out(dx, al);
  cx = 0x7D0;
loc_code_1246:
  _in(al, dx);
  if ( al & 1 ) // jnz 
    goto loc_code_125E;
  if ( !(_data[ds*16+0x69E] & 1) ) // jz 
    goto loc_code_125E;
  _data[ds*16+0x69E] &= 0x0FE;
  sub_12A1();
  _data[ds*16+0x698] = bl;
loc_code_125E:
  if ( al & 2 ) // jnz 
    goto loc_code_1275;
  if ( !(_data[ds*16+0x69E] & 2) ) // jz 
    goto loc_code_1275;
  _data[ds*16+0x69E] &= 0x0FD;
  sub_12A1();
  _data[ds*16+0x699] = bl;
loc_code_1275:
  if ( !(_data[ds*16+0x69E] & 3) ) // jz 
    return;
  sub_13B7();
  ax -= *(WORD*)&_data[ds*16+0x69C];
  if ( --cx && (ax != 0x1964) )
    goto loc_code_1246;
  if ( !(_data[ds*16+0x69E] & 1) ) // jz 
    goto loc_code_1294;
  _data[ds*16+0x698] = 0x0FF;
loc_code_1294:
  if ( !(_data[ds*16+0x69E] & 2) ) // jz 
    return;
  _data[ds*16+0x699] = 0x0FF;
}

void sub_12A1()
{
  _push(ax);
  sub_13B7();
  ax -= *(WORD*)&_data[ds*16+0x69C];
  bx = ax;
  _pop(ax);
  if ( bx >= 0x0F5E6 ) // jnb 
    goto loc_code_12B5;
  bl = 1;
  return;
loc_code_12B5:
  if ( bx >= 0x0FAFA ) // jnb 
    goto loc_code_12BE;
  bl = 0;
  return;
loc_code_12BE:
  bl = 0x0FF;
}

void sub_12C1()
{
  al = _data[ds*16+0x6BA];
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_12D3;
  al &= *(WORD*)&_data[ds*16+0x6BD];
  al &= *(WORD*)&_data[ds*16+0x6BE];
loc_code_12D3:
  al ^= 0x80;
  if ( !al ) // jz 
    goto loc_code_12D9;
  al = 1;
loc_code_12D9:
  _data[ds*16+0x699] = al;
  al = _data[ds*16+0x6B8];
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_12EE;
  al &= *(WORD*)&_data[ds*16+0x6BC];
  al &= *(WORD*)&_data[ds*16+0x6BF];
loc_code_12EE:
  al ^= 0x80;
  if ( !al ) // jz 
    goto loc_code_12F7;
  _data[ds*16+0x699] = 0x0FF;
loc_code_12F7:
  al = _data[ds*16+0x6B9];
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_1309;
  al &= *(WORD*)&_data[ds*16+0x6BC];
  al &= *(WORD*)&_data[ds*16+0x6BD];
loc_code_1309:
  al ^= 0x80;
  if ( !al ) // jz 
    goto loc_code_130F;
  al = 1;
loc_code_130F:
  _data[ds*16+0x698] = al;
  al = _data[ds*16+0x6BB];
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_1324;
  al &= *(WORD*)&_data[ds*16+0x6BE];
  al &= *(WORD*)&_data[ds*16+0x6BF];
loc_code_1324:
  al ^= 0x80;
  if ( !al ) // jz 
    goto loc_code_132D;
  _data[ds*16+0x698] = 0x0FF;
loc_code_132D:
  al = _data[ds*16+0x6B7];
  cl = 3;
  al >>= cl;
  _data[ds*16+0x69A] = al;
}

void sub_1338()
{
  ax = *(WORD*)&_data[ds*16+0x693];
  if ( ax == *(WORD*)&_data[ds*16+0x691] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x691] = ax;
  if ( _data[ds*16+0x6C0] & 0x80 ) // jnz 
    goto loc_code_1358;
  ax = *(WORD*)&_data[ds*16+0x693];
  if ( ax == *(WORD*)&_data[ds*16+0x6E00] ) // jz 
    return;
  sub_5E70();
  return;
loc_code_1358:
  if ( !(_data[ds*16+0x6C9] & 0x80) ) // jz 
    goto loc_code_1360;
  return;
loc_code_1360:
  if ( _data[ds*16+0x6CC] & 0x80 ) // jnz 
    goto loc_code_136D;
  _data[ds*16+0x1F80] = 9;
  return;
loc_code_136D:
  if ( !(_data[ds*16+0x6C1] & 0x80) ) // jz 
    goto loc_code_13A5;
  if ( _data[ds*16+0x6CB] & 0x80 ) // jnz 
    goto loc_code_1381;
  _data[ds*16+0x41C] = 0x0FF;
  return;
loc_code_1381:
  if ( _data[ds*16+0x6C8] & 0x80 ) // jnz 
    goto loc_code_138E;
  _data[ds*16+0x41B] = 0x0FF;
  return;
loc_code_138E:
  if ( _data[ds*16+0x6C7] & 0x80 ) // jnz 
    return;
  _data[ds*16+0] = ~_data[ds*16+0];
  if ( _data[ds*16+0] != 0 ) // jnz 
    return;
  sub_5B21();
  return;
  return;
loc_code_13A5:
  sub_147F();
  _pop(ax);
  unknown_command(); // retf
}

void sub_13AA()
{
  ax = 0x0F000;
  es = ax;
  al = 0xff; ///_data[es*16+0x0FFFE];
  _data[ds*16+0x697] = al;
}

void sub_13B7()
{
  al = 0;
  _out(0x43, al);
  _in(al, 0x40);
  ah = al;
  _in(al, 0x40);
  _xchg(al, ah);
}

/*
  sub_13B7();
  bx = ax;
  ax -= cx;
  cx = bx;
  if ( ax >= dx ) // jnb 
    goto loc_code_13D5;
  return;
loc_code_13D5:
  fix_code(); // zf=1
  return;
*/
BYTE sub_13D8()
{
  dx = 0x3DA;
  _in(al, dx);
  al &= 8;
  return al;
}

/*
*/
WORD word_code_13DF =  0;
WORD word_code_13E1 =  0;
WORD word_code_13E3 =  0;
WORD word_code_13E5 =  0;
BYTE byte_code_13E7 =  0;
void sub_13E8()
{
  _push(ax);
  _push(es);
  _push(di);
  _push(cx);
  ax = seg_data;
  es = ax;
  _cld();
  di = 0x6B7;
  cx = 0x16;
  al = 0x80;
  _rep_stosb();
  ax = *(WORD*)&_data[es*16+0x693];
  ax -= 0x70;
  *(WORD*)&_data[es*16+0x691] = ax;
  ax = 0x40;
  es = ax;
  al = _data[es*16+0x12];
  byte_code_13E7 = al;
  _pop(cx);
  _pop(di);
  _pop(es);
  _pop(ax);
}

void sub_1419()
{
  ax = 0;
  es = ax;
  ax = *(WORD*)&_data[es*16+0x24];
  bx = *(WORD*)&_data[es*16+0x26];
  cx = *(WORD*)&_data[es*16+0x120];
  dx = *(WORD*)&_data[es*16+0x122];
  word_code_13DF = ax;
  word_code_13E1 = bx;
  word_code_13E3 = cx;
  word_code_13E5 = dx;
  bx = 0x14B3;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_1450;
  bx = 0x14FB;
loc_code_1450:
  _cli();
  *(WORD*)&_data[es*16+0x24] = bx;
  *(WORD*)&_data[es*16+0x26] = cs;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_147D;
////  *(WORD*)&_data[es*16+0x120] = &loc_code_1554;
  *(WORD*)&_data[es*16+0x122] = cs;
  ax = 0x40;
  es = ax;
  al = _data[es*16+0x18];
  al |= 1;
  _data[es*16+0x18] = al;
loc_code_147D:
  _sti();
}

void sub_147F()
{
  ax = 0;
  es = ax;
  ax = word_code_13DF;
  bx = word_code_13E1;
  cx = word_code_13E3;
  dx = word_code_13E5;
  _cli();
  *(WORD*)&_data[es*16+0x24] = ax;
  *(WORD*)&_data[es*16+0x26] = bx;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_14B1;
  *(WORD*)&_data[es*16+0x120] = cx;
  *(WORD*)&_data[es*16+0x122] = dx;
loc_code_14B1:
  _sti();
}

/*
  _push(ax);
  _push(es);
  _push(di);
  _push(cx);
  di = seg_data;
  es = di;
  _in(al, 0x60);
  ah = al;
  al &= 0x7F;
  if ( ah & 0x80 ) // jnz 
    goto loc_code_14CC;
  (*(WORD*)&_data[es*16+0x693])++;
loc_code_14CC:
  di = 0x6A1;
  cx = 0x16;
  _cld();
  unknown_command(); // repne scasb
  if ( unknown_condition() ) // jnz 
    goto loc_code_14E3;
  di -= 0x6A2;
  ah &= 0x80;
  _data[es*16+di+6B7h] = ah;
loc_code_14E3:
  _in(al, 0x61);
  ah = al;
  al |= 0x80;
  _out(0x61, al);
  al = ah;
  _out(0x61, al);
  sub_1572();
  _pop(cx);
  _pop(di);
  _pop(es);
  al = 0x20;
  _out(0x20, al);
  _pop(ax);
  unknown_command(); // iret
  _sti();
  _push(ax);
  _push(es);
  _push(di);
  _push(cx);
  di = seg_data;
  es = di;
  ah = al;
  al &= 0x7F;
  if ( ah & 0x80 ) // jnz 
    goto loc_code_1513;
  (*(WORD*)&_data[es*16+0x693])++;
loc_code_1513:
  if ( ah == 0x0FF ) // jz 
    goto loc_code_1530;
  if ( ah == 0x55 ) // jz 
    goto loc_code_1530;
  _push(es);
  di = 0x40;
  es = di;
  cl = _data[es*16+0x12];
  _pop(es);
  if ( cl == byte_code_13E7 ) // jz 
    goto loc_code_1535;
loc_code_1530:
  sub_13E8();
  goto loc_code_154C;
loc_code_1535:
  di = 0x6A1;
  cx = 0x16;
  _cld();
  unknown_command(); // repne scasb
  if ( unknown_condition() ) // jnz 
    goto loc_code_154C;
  di -= 0x6A2;
  ah &= 0x80;
  _data[es*16+di+6B7h] = ah;
loc_code_154C:
  sub_1572();
  _pop(cx);
  _pop(di);
  _pop(es);
  _pop(ax);
  unknown_command(); // iret
loc_code_1554:
  _int(9);
  unknown_command(); // iret
loc_code_1557:
  ax = 0x0F000;
  ss = ax;
  ax = 0x40;
  ds = ax;
  bx = 0x72;
  *(WORD*)&_data[bx] = 0x1234;
  ax = 0;
  es = ax;
  goto far ptr	0F000h:0E05Bh;
*/
void sub_1572()
{
  al = _data[es*16+0x6C9];
  al |= *(WORD*)&_data[es*16+0x6B7];
  if ( al != 0 ) // jnz 
    return;
  if ( _data[es*16+0x6CA] & 0x80 ) // jnz 
    goto loc_code_158D;
  al = 0x20;
  _out(0x20, al);
////  goto loc_code_1557;
loc_code_158D:
  if ( _data[es*16+0x6B9] & 0x80 ) // jnz 
    goto loc_code_15A4;
  if ( _data[es*16+0x690] < 1 ) // jb 
    return;
  (_data[es*16+0x690])--;
  goto loc_code_15B9;
loc_code_15A4:
  if ( _data[es*16+0x6BB] & 0x80 ) // jnz 
    return;
  if ( _data[es*16+0x690] >= 7 ) // jnb 
    return;
  (_data[es*16+0x690])++;
loc_code_15B9:
  _push(dx);
  al = 2;
  dx = 0x3D4;
  _out(dx, al);
  al = _data[es*16+0x690];
  al += 0x27;
  dx++;
  _out(dx, al);
  _pop(dx);
}

/*
  unknown_command(); // align 8
*/
void sub_15D0()
{
  bx = *(WORD*)&_data[ds*16+8];
  cl = _data[bx + 0x100E];
loc_code_15D8:
  sub_2DFD();
  dl &= 7;
  if ( dl > cl ) // ja 
    goto loc_code_15D8;
  dl += *(WORD*)&_data[bx + 0x1006];
  if ( dl == _data[ds*16+0x1028] ) // jz 
    goto loc_code_15D8;
  _data[ds*16+0x1028] = dl;
  bl = dl;
  cl = _data[bx + 0x0FF0];
  dl = 0x88;
  if ( cl & 0x80 ) // jnz 
    goto loc_code_15FF;
  dl = 0x90;
loc_code_15FF:
  cx &= 0x7F;
  cx <<= 1;
  cx <<= 1;
}

void sub_1608()
{
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_1613;
  sub_30FA();
  return;
loc_code_1613:
  if ( *(WORD*)&_data[ds*16+4] == 0 ) // jz 
    goto loc_code_161E;
  sub_16C6();
  return;
loc_code_161E:
  al = _data[ds*16+0x57B];
  al &= 0x0F8;
  if ( al == 0x60 ) // jz 
    goto loc_code_1630;
  sub_1657();
  if ( cf ) // jb cf=1
    return;
  sub_17AD();
  return;
loc_code_1630:
  if ( _data[ds*16+0x550] >= 2 ) // jnb 
    goto loc_code_1655;
  _data[ds*16+0x57B] = al;
  al += 0x32;
  _data[ds*16+0x57C] = al;
  if ( _data[ds*16+0x550] == 1 ) // jz 
    goto loc_code_1653;
  _data[ds*16+0x550] = 1;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x556] = dx;
loc_code_1653:
  _stc();
  return;
loc_code_1655:
  _clc();
}

void sub_1657()
{
  cl = _data[ds*16+0x57B];
  cl += 2;
  cl &= 0x0F8;
  bx = *(WORD*)&_data[ds*16+8];
  bl = _data[bx + 0x1006];
loc_code_1669:
  al = _data[bx + 0x0FF0];
  if ( al != 0 ) // jnz 
    goto loc_code_1678;
  _data[ds*16+0x127C] = 0;
  _clc();
  return;
loc_code_1678:
  bx++;
  ch = 0x88;
  if ( al & 0x80 ) // jnz 
    goto loc_code_1681;
  ch = 0x90;
loc_code_1681:
  if ( cl != ch ) // jnz 
    goto loc_code_1669;
  ax &= 0x7F;
  ax <<= 1;
  ax <<= 1;
  dx = *(WORD*)&_data[ds*16+0x579];
  dx &= 0x0FFF8;
  if ( dx < ax ) // jb 
    goto loc_code_1669;
  dx = *(WORD*)&_data[ds*16+0x579];
  dx -= 0x0F;
  dx &= 0x0FFF8;
  if ( dx > ax ) // ja 
    goto loc_code_1669;
  ch -= 2;
  _data[ds*16+0x57B] = ch;
  ch += 0x32;
  _data[ds*16+0x57C] = ch;
  if ( _data[ds*16+0x127C] != 0 ) // jnz 
    goto loc_code_16C4;
  _data[ds*16+0x127C] = 1;
  sub_590E();
loc_code_16C4:
  _stc();
}

void sub_16C6()
{
  _data[ds*16+0x39E0] = 0;
  if ( _data[ds*16+0x571] != 1 ) // jnz 
    goto loc_code_16FC;
  ax = *(WORD*)&_data[ds*16+0x2650];
  ax -= 4;
  dl = _data[ds*16+0x2652];
  dl -= 8;
  si = 0x0C;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E10;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_16FC;
  _data[ds*16+0x551] = 1;
  _clc();
  return;
loc_code_16FC:
  if ( *(WORD*)&_data[ds*16+4] != 3 ) // jnz 
    goto loc_code_170E;
  sub_3C43();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_170E;
  _data[ds*16+0x55C] = 1;
  return;
loc_code_170E:
  cl = _data[ds*16+0x57B];
  cl &= 0x0F8;
  bx = *(WORD*)&_data[ds*16+4];
  bx <<= 1;
  bx = *(WORD*)&_data[bx + 0x1269];
loc_code_171F:
  ch = _data[bx + 0x1029];
  if ( ch != 0 ) // jnz 
    goto loc_code_172A;
  _clc();
  return;
loc_code_172A:
  al = _data[bx + 0x1089];
  _data[ds*16+0x127B] = al;
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x11A9];
  *(WORD*)&_data[ds*16+0x1279] = ax;
  ax = *(WORD*)&_data[bx + 0x10E9];
  bl >>= 1;
  bx++;
  if ( cl != ch ) // jnz 
    goto loc_code_171F;
  dx = *(WORD*)&_data[ds*16+0x579];
  dx &= 0x0FFF8;
  if ( dx < ax ) // jb 
    goto loc_code_171F;
  dx = *(WORD*)&_data[ds*16+0x579];
  cf = (dx < *(WORD*)&_data[ds*16+0x1279]); // cf-insertion
  dx -= *(WORD*)&_data[ds*16+0x1279];
  if ( !cf ) // jnb 
    goto loc_code_175D;
  dx = 0;
loc_code_175D:
  dx &= 0x0FFFC;
  if ( dx > ax ) // ja 
    goto loc_code_171F;
  _data[ds*16+0x57B] = ch;
  ch += 0x32;
  _data[ds*16+0x57C] = ch;
  al = _data[ds*16+0x127B];
  _data[ds*16+0x55C] = al;
  if ( al == 0 ) // jz 
    goto loc_code_1780;
  *(WORD*)&_data[ds*16+0x579] &= 0x0FFFC;
loc_code_1780:
  if ( *(WORD*)&_data[ds*16+4] != 4 ) // jnz 
    goto loc_code_1797;
  bx--;
  cf = (bx < 0x27); // cf-insertion
  bx -= 0x27;
  if ( cf ) // jb 
    goto loc_code_1797;
  if ( bx >= 0x10 ) // jnb 
    goto loc_code_1797;
  bx++;
  _data[ds*16+0x39E0] = bl;
loc_code_1797:
  _stc();
}

void sub_1799()
{
  cl = 3;
  bx >>= cl;
  ch = bl;
  cl = 3;
  bx >>= cl;
  cl = ch;
  cl &= 7;
  ch = 0x80;
  ch >>= cl;
}

void sub_17AD()
{
  dl = _data[ds*16+0x57B];
  dl &= 0x0F8;
  bx = 0;
  if ( dl == 8 ) // jz 
    goto loc_code_17C9;
  bl++;
  if ( dl == 0x28 ) // jz 
    goto loc_code_17C9;
  bl++;
  if ( dl != 0x48 ) // jnz 
    goto loc_code_1810;
loc_code_17C9:
  ax = *(WORD*)&_data[ds*16+0x579];
  if ( bx != *(WORD*)&_data[ds*16+0x52F] ) // jnz 
    goto loc_code_17FC;
  if ( _data[ds*16+0x525] > 3 ) // ja 
    goto loc_code_17FC;
  if ( bl == 1 ) // jz 
    goto loc_code_17EE;
  cx = 4;
  cl -= *(WORD*)&_data[ds*16+0x525];
  cl <<= 1;
  cl <<= 1;
  ax += cx;
  goto loc_code_17FC;
loc_code_17EE:
  ch = 0;
  cl = _data[ds*16+0x525];
  cl++;
  cl <<= 1;
  cl <<= 1;
  ax -= cx;
loc_code_17FC:
  bl = _data[bx + 0x1025];
  si = bx;
  bx = ax;
  bx += 0x0A;
  sub_1799();
  if ( *(WORD*)&_data[bx + si + 0x1016] & ch ) // jnz 
    goto loc_code_1812;
loc_code_1810:
  _clc();
  return;
loc_code_1812:
  _data[ds*16+0x57B] = dl;
  dl += 0x32;
  _data[ds*16+0x57C] = dl;
  *(WORD*)&_data[ds*16+0x579] &= 0x0FFF8;
  _data[ds*16+0x55C] = 1;
  _stc();
}

/*
  unknown_command(); // align 8
*/
void sub_1830()
{
  _data[ds*16+0x1665] = 0;
  _data[ds*16+0x1673] = 0;
  _data[ds*16+0x1677] = 0;
  _data[ds*16+0x1678] = 0;
  *(WORD*)&_data[ds*16+0x166C] = 9;
}

void sub_184B()
{
  if ( _data[ds*16+0x1673] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x17EC] ) // jnz 
    goto loc_code_185D;
  return;
loc_code_185D:
  *(WORD*)&_data[ds*16+0x17EC] = dx;
  if ( _data[ds*16+0x1677] == 0 ) // jz 
    goto loc_code_187F;
  ax = *(WORD*)&_data[ds*16+0x1671];
  ax &= 0x0FFF8;
  bx = *(WORD*)&_data[ds*16+0x579];
  bx &= 0x0FFF8;
  if ( ax != bx ) // jnz 
    goto loc_code_187F;
  _data[ds*16+0x1674] = 0;
loc_code_187F:
  (_data[ds*16+0x17E9])++;
  if ( *(WORD*)&_data[ds*16+0x17EA] > 1 ) // ja 
    goto loc_code_188E;
  (*(WORD*)&_data[ds*16+0x17EA])--;
loc_code_188E:
  ax = *(WORD*)&_data[ds*16+0x1671];
  dx = *(WORD*)&_data[ds*16+0x17EA];
  cl = 3;
  dl >>= cl;
  if ( _data[ds*16+0x1674] < 1 ) // jb 
    goto loc_code_18B5;
  if ( _data[ds*16+0x1674] != 1) // jnz 
    goto loc_code_18AF;
  ax += dx;
  if ( ax < 0x12F ) // jb 
    goto loc_code_18B5;
  ax = 0x12E;
  goto loc_code_18B5;
loc_code_18AF:
  cf = (ax < dx); // cf-insertion
  ax -= dx;
  if ( !cf ) // jnb 
    goto loc_code_18B5;
  ax = 0;
loc_code_18B5:
  *(WORD*)&_data[ds*16+0x1671] = ax;
  bx = *(WORD*)&_data[ds*16+0x17DF];
  al = _data[ds*16+0x17E9];
  al >>= 1;
  al += *(WORD*)&_data[ds*16+0x1673];
  dl = al;
  cf = (al < *(WORD*)&_data[ds*16+0x1676]); // cf-insertion
  al -= *(WORD*)&_data[ds*16+0x1676];
  if ( cf ) // jb 
    goto loc_code_18E1;
  zf = (bh == al); // zf-insertion
  cf = (bh < al); // zf-insertion
  bh -= al;
  if ( zf ) // jz 
    goto loc_code_18D3;
  if ( !cf ) // jnb cf=0
    goto loc_code_18E1;
loc_code_18D3:
  _data[ds*16+0x1673] = 0;
  _data[ds*16+0x1678] = 0;
  sub_1922();
  return;
loc_code_18E1:
  _data[ds*16+0x1673] = dl;
  cx = *(WORD*)&_data[ds*16+0x1671];
  *(WORD*)&_data[ds*16+0x17E1] = bx;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x17E7] = ax;
  if ( _data[ds*16+0x17E9] == 2 ) // jz 
    goto loc_code_18FD;
  sub_1922();
loc_code_18FD:
  sub_1B7A();
  if ( cf ) // jb 
    return;
  di = *(WORD*)&_data[ds*16+0x17E7];
  *(WORD*)&_data[ds*16+0x17E5] = di;
  cx = *(WORD*)&_data[ds*16+0x17E1];
  *(WORD*)&_data[ds*16+0x17E3] = cx;
  ax = 0x0B800;
  es = ax;
  si = *(WORD*)&_data[ds*16+0x17DD];
  bp = 0x17EE;
  sub_2CCC();
}

void sub_1922()
{
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x17E5];
  si = 0x17EE;
  cx = *(WORD*)&_data[ds*16+0x17E3];
  sub_2D9D();
}

void sub_1936()
{
  (_data[ds*16+0x166A])--;
  if ( !_data[ds*16+0x166A] ) // jz 
    goto loc_code_193D;
  return;
loc_code_193D:
  _data[ds*16+0x166A] = 0x0D;
  if ( sub_13D8() ) // jnz 
    return;
  if ( _data[ds*16+0x1665] == 0 ) // jz 
    goto loc_code_1951;
  sub_1B05();
loc_code_1951:
  if ( _data[ds*16+0x1673] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x1665] != 0 ) // jnz 
    goto loc_code_19CD;
  if ( _data[ds*16+0x57B] > 0x60 ) // ja 
    return;
  _data[ds*16+0x1677] = 0;
  if ( _data[ds*16+0x550] != 1 ) // jnz 
    goto loc_code_198A;
  if ( _data[ds*16+0x418] != 0 ) // jnz 
    goto loc_code_198A;
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x556];
  if ( dx < 0x48 ) // jb 
    goto loc_code_198A;
  (_data[ds*16+0x1677])++;
loc_code_198A:
  sub_2DFD();
  if ( _data[ds*16+0x1677] == 0 ) // jz 
    goto loc_code_199A;
  dl &= 3;
  goto loc_code_19A2;
loc_code_199A:
  dl &= 0x0F;
  if ( dl >= 0x0C ) // jnb 
    return;
loc_code_19A2:
  _data[ds*16+0x1669] = dl;
  sub_1AEA();
  *(WORD*)&_data[ds*16+0x1666] = cx;
  _data[ds*16+0x1668] = dl;
  sub_1B05();
  if ( cf ) // jb cf=1
    goto loc_code_198A;
  _data[ds*16+0x1665] = 0x1D;
  bx = *(WORD*)&_data[ds*16+8];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x181E];
  *(WORD*)&_data[ds*16+0x166C] = ax;
  _data[ds*16+0x1670] = 1;
loc_code_19CD:
  sub_1B05();
  if ( cf ) // jb cf=1
    return;
  _data[ds*16+0x1664] = 0;
  sub_1B4C();
  if ( !cf ) // jnb cf=0
    goto loc_code_19E1;
  (_data[ds*16+0x1664])++;
  return;
loc_code_19E1:
  if ( _data[ds*16+0x1665] != 0x10 ) // jnz 
    goto loc_code_19F0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x166E] = dx;
loc_code_19F0:
  if ( _data[ds*16+0x1665] != 0x0F ) // jnz 
    goto loc_code_1A76;
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x166E];
  if ( dx >= *(WORD*)&_data[ds*16+0x166C] ) // jnb 
    goto loc_code_1A76;
  if ( _data[ds*16+0x1670] == 0 ) // jz 
    return;
  if ( _data[ds*16+0x1673] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x418] != 0 ) // jnz 
    return;
  (_data[ds*16+0x1670])--;
  _data[ds*16+0x1678] = 1;
  al = _data[ds*16+0x1668];
  _data[ds*16+0x1673] = al;
  sub_2DFD();
  dx &= 0x0F;
  dx += *(WORD*)&_data[ds*16+0x1666];
  *(WORD*)&_data[ds*16+0x1671] = dx;
  al = 1;
  if ( dx < *(WORD*)&_data[ds*16+0x579] ) // jb 
    goto loc_code_1A42;
  al = 0x0FF;
loc_code_1A42:
  _data[ds*16+0x1674] = al;
  sub_2DFD();
  bl = dl;
  bx &= 6;
  ax = *(WORD*)&_data[bx + 0x17C9];
  *(WORD*)&_data[ds*16+0x17DD] = ax;
  ax = *(WORD*)&_data[bx + 0x17D1];
  *(WORD*)&_data[ds*16+0x17DF] = ax;
  bl >>= 1;
  al = _data[bx + 0x17D9];
  _data[ds*16+0x1676] = al;
  *(WORD*)&_data[ds*16+0x17EA] = 0x20;
  _data[ds*16+0x17E9] = 1;
  _data[ds*16+0x1675] = 0;
  return;
loc_code_1A76:
  (_data[ds*16+0x1665])--;
  cx = *(WORD*)&_data[ds*16+0x1666];
  dl = _data[ds*16+0x1668];
  if ( _data[ds*16+0x1665] <= 0x0E ) // jbe 
    goto loc_code_1A93;
  dl += *(WORD*)&_data[ds*16+0x1665];
  dl -= 0x0E;
  goto loc_code_1A9A;
loc_code_1A93:
  dl += 0x0E;
  dl -= *(WORD*)&_data[ds*16+0x1665];
loc_code_1A9A:
  _data[ds*16+0x166B] = dl;
  sub_2CB0();
  di = ax;
  ax = 0x0B800;
  es = ax;
  _cld();
  cx = 4;
  if ( _data[ds*16+0x1665] <= 0x0E ) // jbe 
    goto loc_code_1AD7;
  if ( _data[ds*16+0x418] == 0 ) // jz 
    goto loc_code_1AD2;
  al = _data[ds*16+0x166B];
  al -= *(WORD*)&_data[ds*16+0x1668];
  ah = 0;
  cl = 3;
  ax <<= cl;
  ax += 0x15E0;
  si = ax;
  cx = 4;
  _rep_movsw();
  return;
loc_code_1AD2:
  ax = 0;
  _rep_stosw();
  return;
loc_code_1AD7:
  al = _data[ds*16+0x166B];
  al -= *(WORD*)&_data[ds*16+0x1668];
  ah = 0x0A;
  ax = (WORD)ah * (WORD)al;

  ax += 0x2681;
  si = ax;
  _rep_movsw();
}

void sub_1AEA()
{
  bh = 0;
  bl = dl;
  bl &= 3;
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x1658];
  bl = dl;
  bl >>= 1;
  bl >>= 1;
  bl &= 3;
  dl = _data[bx + 0x1660];
}

void sub_1B05()
{
  ax = *(WORD*)&_data[ds*16+0x1666];
  dl = _data[ds*16+0x1668];
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  si = 0x20;
  di = 0x18;
  cx = 0x0E0F;
  sub_2E29();
  if ( !cf ) // jnb cf=0
    return;
  if ( _data[ds*16+0x571] != 1 ) // jnz 
    goto loc_code_1B4A;
  if ( _data[ds*16+0x55A] != 0 ) // jnz 
    goto loc_code_1B4A;
  if ( _data[ds*16+0x57B] >= 0x60 ) // jnb 
    goto loc_code_1B4A;
  if ( _data[ds*16+0x1665] < 5 ) // jb 
    goto loc_code_1B4A;
  if ( _data[ds*16+0x1665] >= 0x19 ) // jnb 
    goto loc_code_1B4A;
  _data[ds*16+0x551] = 1;
loc_code_1B4A:
  _stc();
}

void sub_1B4C()
{
  al = _data[ds*16+0x1669];
  if ( al >= 8 ) // jnb 
    goto loc_code_1B78;
  bx = 2;
  if ( !(al & 4) ) // jz 
    goto loc_code_1B5C;
  bl <<= 1;
loc_code_1B5C:
  ax = *(WORD*)&_data[bx + 0x1F30];
  ax += 0x10;
  if ( ax < *(WORD*)&_data[ds*16+0x1666] ) // jb 
    goto loc_code_1B78;
  cf = (ax < 0x30); // cf-insertion
  ax -= 0x30;
  if ( !cf ) // jnb 
    goto loc_code_1B70;
  ax = 0;
loc_code_1B70:
  if ( ax > *(WORD*)&_data[ds*16+0x1666] ) // ja 
    goto loc_code_1B78;
  _stc();
  return;
loc_code_1B78:
  _clc();
}

void sub_1B7A()
{
  if ( *(WORD*)&_data[ds*16+4] != 0 ) // jnz 
    goto loc_code_1BE1;
  dl = _data[ds*16+0x1673];
  if ( dl == 0 ) // jz 
    goto loc_code_1BE1;
  cx = *(WORD*)&_data[ds*16+0x17DF];
  _xchg(cl, ch);
  si = 0x10;
  ax = *(WORD*)&_data[ds*16+0x1671];
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  ch = 0x0E;
  sub_2E29();
  if ( !cf ) // jnb cf=0
    return;
  sub_11E3();
  sub_1922();
  sub_10DD();
  if ( _data[ds*16+0x1675] != 0 ) // jnz 
    goto loc_code_1BDF;
  _data[ds*16+0x1675] = 1;
  sub_1166();
  dl = 1;
  if ( _data[ds*16+0x1674] == 0x0FF ) // jz 
    goto loc_code_1BCB;
  dl = 0x0FF;
loc_code_1BCB:
  _data[ds*16+0x1674] = dl;
  *(WORD*)&_data[ds*16+0x17EA] = 0x60;
  _data[ds*16+0x17E9] = 1;
  _data[ds*16+0x55C] = 0;
loc_code_1BDF:
  _stc();
  return;
loc_code_1BE1:
  _clc();
}

/*
  unknown_command(); // align 10h
*/
void sub_1BF0()
{
  bx = 0;
  ah = 0x0B;
  _int(0x10);
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_1C12;
  if ( _data[ds*16+0x553] == 0 ) // jz 
    goto loc_code_1C12;
  sub_528B();
  *(WORD*)&_data[ds*16+0x579] = 0x98;
  _data[ds*16+0x57B] = 0x5F;
loc_code_1C12:
  ax = 0x0B800;
  es = ax;
  _cld();
  *(WORD*)&_data[ds*16+0x1839] = 0;
  sub_1C67();
  sub_5B21();
  sub_1D31();
  if ( *(WORD*)&_data[ds*16+4] != 0 ) // jnz 
    goto loc_code_1C49;
  if ( _data[ds*16+0x553] == 0 ) // jz 
    goto loc_code_1C46;
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_1C41;
  sub_5313();
  goto loc_code_1C49;
loc_code_1C41:
  sub_38B0();
  goto loc_code_1C49;
loc_code_1C46:
  sub_1D76();
loc_code_1C49:
  if ( *(WORD*)&_data[ds*16+4] == 7 ) // jz 
    goto loc_code_1C5A;
  ax = 0x0AAAA;
  if ( *(WORD*)&_data[ds*16+4] != 2 ) // jnz 
    goto loc_code_1C5D;
loc_code_1C5A:
  ax = 0x5555;
loc_code_1C5D:
  *(WORD*)&_data[ds*16+0x1839] = ax;
  sub_1C67();
  sub_5B21();
}

void sub_1C67()
{
  nullsub_2();
  *(WORD*)&_data[ds*16+0x1835] = 1;
  _data[ds*16+0x1837] = 8;
  cx = *(WORD*)&_data[ds*16+0x579];
  dl = _data[ds*16+0x57B];
  cx += 0x0C;
  cx &= 0x0FFF0;
  dl += 8;
  _data[ds*16+0x1838] = 0;
loc_code_1C8C:
  sub_5897();
  *(WORD*)&_data[ds*16+0x1832] = cx;
  _data[ds*16+0x1834] = dl;
  sub_2CB0();
  di = ax;
  bl = _data[ds*16+0x1837];
loc_code_1CA0:
  ax = *(WORD*)&_data[ds*16+0x1839];
  cx = *(WORD*)&_data[ds*16+0x1835];
  cx >>= 1;
  cx >>= 1;
  cx >>= 1;
  _rep_stosw();
  cx = *(WORD*)&_data[ds*16+0x1835];
  cx >>= 1;
  cx >>= 1;
  cx &= 0x0FE;
  di -= cx;
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_1CCA;
  di += 0x50;
loc_code_1CCA:
  bl--;
  if ( bl ) // jnz 
    goto loc_code_1CA0;
  if ( _data[ds*16+0x1838] != 0x0F ) // jnz 
    goto loc_code_1CD6;
  return;
loc_code_1CD6:
  *(WORD*)&_data[ds*16+0x1835] += 0x20;
  _data[ds*16+0x1837] += 0x10;
  cx = *(WORD*)&_data[ds*16+0x1832];
  dl = _data[ds*16+0x1834];
  cf = (cx < 0x10); // cf-insertion
  cx -= 0x10;
  if ( !cf ) // jnb 
    goto loc_code_1CF4;
  cx = 0;
  _data[ds*16+0x1838] |= 1;
loc_code_1CF4:
  ax = *(WORD*)&_data[ds*16+0x1835];
  ax += cx;
  if ( ax < 0x140 ) // jb 
    goto loc_code_1D0B;
  ax = 0x140;
  ax -= cx;
  *(WORD*)&_data[ds*16+0x1835] = ax;
  _data[ds*16+0x1838] |= 2;
loc_code_1D0B:
  cf = (dl < 8); // cf-insertion
  dl -= 8;
  if ( !cf ) // jnb 
    goto loc_code_1D17;
  dl = 0;
  _data[ds*16+0x1838] |= 4;
loc_code_1D17:
  al = _data[ds*16+0x1837];
  al += dl;
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_1D22;
  if ( al < 0x0C8 ) // jb 
    goto loc_code_1D2E;
loc_code_1D22:
  al = 0x0C8;
  al -= dl;
  _data[ds*16+0x1837] = al;
  _data[ds*16+0x1838] |= 8;
loc_code_1D2E:
  goto loc_code_1C8C;
}

void sub_1D31()
{
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_1D48;
  ah = 0x0B;
  bh = 1;
  si = *(WORD*)&_data[ds*16+4];
  bl = _data[si + 0x1853];
  _int(0x10);
  goto loc_code_1D67;
loc_code_1D48:
  si = *(WORD*)&_data[ds*16+4];
  bl = 1;
  bh = _data[si + 0x183B];
  sub_1D6E();
  bl = 2;
  bh = _data[si + 0x1843];
  sub_1D6E();
  bl = 3;
  bh = _data[si + 0x184B];
  sub_1D6E();
loc_code_1D67:
  ah = 0x0B;
  bx = 0;
  _int(0x10);
}

void sub_1D6E()
{
  ax = 0x1000;
  _push(si);
  _int(0x10);
  _pop(si);
}

void sub_1D76()
{
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_1D81;
  sub_6040();
  return;
loc_code_1D81:
  sub_57D5();
  ax = 0x185B;
  if ( _data[ds*16+0x552] == 0 ) // jz 
    goto loc_code_1DC6;
  bx = *(WORD*)&_data[ds*16+0x1C30];
  *(WORD*)&_data[ds*16+0x1C30] += 2;
  bx &= 6;
  ax = *(WORD*)&_data[bx + 0x1C26];
  if ( _data[ds*16+0x1F80] == 0 ) // jz 
    goto loc_code_1DAA;
  (_data[ds*16+0x1F80])--;
loc_code_1DAA:
  if ( _data[ds*16+0x552] != 0x0DD ) // jnz 
    goto loc_code_1DC6;
  if ( *(WORD*)&_data[ds*16+8] == 0 ) // jz 
    goto loc_code_1DC6;
  if ( _data[ds*16+0x1F80] < 1 ) // jb 
    goto loc_code_1DC6;
  sub_5BE0();
  sub_5B21();
  return;
loc_code_1DC6:
  *(WORD*)&_data[ds*16+0x1C2E] = ax;
  *(WORD*)&_data[ds*16+0x1C1B] = 0x8080;
  _data[ds*16+0x1C1D] = 0x1C;
loc_code_1DD4:
  sub_1E17();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x1830] = dx;
loc_code_1DDF:
  sub_57E4();
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x1830] ) // jz 
    goto loc_code_1DDF;
  if ( _data[ds*16+0x1C1D] > 0x14 ) // ja 
    goto loc_code_1E02;
  bh = 0;
  bl = _data[ds*16+0x1C1D];
  bl &= 6;
  ax = *(WORD*)&_data[bx + 0x1C1E];
  goto loc_code_1E0A;
loc_code_1E02:
  ax = *(WORD*)&_data[ds*16+0x1C1B];
  _stc();
  fix_code(); // fix carry flag
  _rcr(al, 1);
  ah = al;
loc_code_1E0A:
  *(WORD*)&_data[ds*16+0x1C1B] = ax;
  (_data[ds*16+0x1C1D])--;
  if ( _data[ds*16+0x1C1D] ) // jnz 
    goto loc_code_1DD4;
  sub_5B21();
}

void sub_1E17()
{
  _cld();
  _push(ds);
  _pop(es);
  si = *(WORD*)&_data[ds*16+0x1C2E];
  di = 0x0E;
  cx = 0x60;
loc_code_1E24:
  _lodsw();
  ax &= *(WORD*)&_data[ds*16+0x1C1B];
  _stosw();
  if ( --cx )
    goto loc_code_1E24;
  ax = 0x0B800;
  es = ax;
  si = 0x0E;
  di = 0x0ED0;
  cx = 0x0C08;
  sub_2D9D();
}

/*
  unknown_command(); // align 4
*/
void sub_1E40()
{
  _data[ds*16+0x1CBF] = 0;
  *(WORD*)&_data[ds*16+0x1CE1] = 0;
  _data[ds*16+0x1CC0] = 0;
  _data[ds*16+0x1CC1] = 0;
  _data[ds*16+0x1CB8] = 0;
  _data[ds*16+0x1CC8] = 0x0B1;
  sub_5450();
}

void sub_1E63()
{
  ah = 0;
  _int(0x1A);
  cx = dx;
  dx -= *(WORD*)&_data[ds*16+0x1CC9];
  ax = *(WORD*)&_data[ds*16+0x1CE1];
  ax &= 1;
  ax += 1;
  if ( dx >= ax ) // jnb 
    goto loc_code_1E7B;
  return;
loc_code_1E7B:
  if ( !sub_13D8() ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x1CC9] = cx;
  (*(WORD*)&_data[ds*16+0x1CE1])++;
  if ( _data[ds*16+0x1CC1] == 0 ) // jz 
    goto loc_code_1EE2;
  (_data[ds*16+0x1CC1])--;
  if ( _data[ds*16+0x1CC1] ) // jnz 
    goto loc_code_1EC9;
  sub_5B21();
  if ( _data[ds*16+0x1CB8] == 0 ) // jz 
    goto loc_code_1EC2;
  if ( *(WORD*)&_data[ds*16+4] == 0 ) // jz 
    goto loc_code_1EB7;
  _data[ds*16+0x552] = 0x0DD;
  *(WORD*)&_data[ds*16+0x579] = 0x0A0;
  _data[ds*16+0x57B] = 0x60;
  return;
loc_code_1EB7:
  if ( _data[ds*16+0x1F80] == 0 ) // jz 
    goto loc_code_1EC2;
  (_data[ds*16+0x1F80])--;
loc_code_1EC2:
  sub_20E1();
  sub_1E40();
  return;
loc_code_1EC9:
  sub_2022();
  ax = 0x104;
  al -= *(WORD*)&_data[ds*16+0x1CC1];
  if ( _data[ds*16+0x1CD0] == 0x0FF ) // jz 
    goto loc_code_1EDC;
  ah = 0x0FF;
loc_code_1EDC:
  sub_2059();
  goto loc_code_1FFB;
loc_code_1EE2:
  if ( _data[ds*16+0x1CB8] == 0 ) // jz 
    goto loc_code_1F0C;
  dl = _data[ds*16+0x1CB8];
  if ( *(WORD*)&_data[ds*16+0x1CB9] == 0 ) // jz 
    goto loc_code_1F02;
  (*(WORD*)&_data[ds*16+0x1CB9])--;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_1F02;
  dl = 0x0FF;
loc_code_1F02:
  _data[ds*16+0x1CD0] = dl;
  ax = *(WORD*)&_data[ds*16+0x1CC6];
  goto loc_code_1FAB;
loc_code_1F0C:
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    goto loc_code_1F75;
  if ( _data[ds*16+0x1CC0] != 0 ) // jnz 
    goto loc_code_1F57;
  if ( _data[ds*16+0x1D58] != 0 ) // jnz 
    goto loc_code_1F3D;
  if ( _data[ds*16+0x57B] < 0x0B4 ) // jb 
    return;
  if ( _data[ds*16+0x558] != 0 ) // jnz 
    return;
  sub_2DFD();
  bx = *(WORD*)&_data[ds*16+8];
  if ( dl < _data[bx + 0x1CD1] ) // jb 
    goto loc_code_1F3D;
  return;
loc_code_1F3D:
  al = 1;
  *(WORD*)&_data[ds*16+0x59BA] = 0;
  if ( *(WORD*)&_data[ds*16+0x579] >= 0x0A0 ) // jnb 
    goto loc_code_1F4F;
  al = 0x0FF;
loc_code_1F4F:
  _data[ds*16+0x1CD0] = al;
  _data[ds*16+0x1CC0] = 4;
loc_code_1F57:
  (_data[ds*16+0x1CC0])--;
  if ( _data[ds*16+0x1CC0] ) // jnz 
    goto loc_code_1F65;
  _data[ds*16+0x1CBF] = 1;
  goto loc_code_1F75;
loc_code_1F65:
  sub_2022();
  al = _data[ds*16+0x1CC0];
  ah = _data[ds*16+0x1CD0];
  sub_2059();
  goto loc_code_1FFB;
loc_code_1F75:
  _data[ds*16+0x1D58] = 0;
  ax = *(WORD*)&_data[ds*16+0x1CC6];
  if ( _data[ds*16+0x57B] < 0x0B4 ) // jb 
    goto loc_code_1FAB;
  if ( _data[ds*16+0x558] != 0 ) // jnz 
    goto loc_code_1FAB;
  sub_2DFD();
  bx = *(WORD*)&_data[ds*16+8];
  if ( dl > _data[bx + 0x1CD9] ) // ja 
    goto loc_code_1FAB;
  if ( ax > *(WORD*)&_data[ds*16+0x579] ) // ja 
    goto loc_code_1FA6;
  _data[ds*16+0x1CD0] = 1;
  goto loc_code_1FAB;
loc_code_1FA6:
  _data[ds*16+0x1CD0] = 0x0FF;
loc_code_1FAB:
 // _ASSERT(_data[ds*16+0x1CD0]<5);
  if ( _data[ds*16+0x1CD0] < 1 ) // jb 
    goto loc_code_1FEF;
  if ( _data[ds*16+0x1CD0] == 1 ) // jz 
    goto loc_code_1FE2;
  cf = (ax < 8); // cf-insertion
  ax -= 8;
  if ( !cf ) // jnb 
    goto loc_code_1FEF;
  ax = 0;
loc_code_1FBB:
  if ( _data[ds*16+0x1CB8] == 0 ) // jz 
    goto loc_code_1FCC;
  if ( *(WORD*)&_data[ds*16+0x1CB9] != 0 ) // jnz 
    goto loc_code_1FEF;
  goto loc_code_1FDA;
loc_code_1FCC:
  if ( _data[ds*16+0x57B] < 0x0B4 ) // jb 
    goto loc_code_1FDA;
  if ( _data[ds*16+0x558] == 0 ) // jz 
    goto loc_code_1FEF;
loc_code_1FDA:
  _data[ds*16+0x1CC1] = 4;
  goto loc_code_1FEF;
loc_code_1FE2:
  ax += 8;
  if ( ax < 0x11E ) // jb 
    goto loc_code_1FEF;
  ax = 0x11E;
  goto loc_code_1FBB;
loc_code_1FEF:
  *(WORD*)&_data[ds*16+0x1CC6] = ax;
  sub_2022();
  *(WORD*)&_data[ds*16+0x1CC4] = 0x0F04;
loc_code_1FFB:
  cx = *(WORD*)&_data[ds*16+0x1CC6];
  dl = _data[ds*16+0x1CC8];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x1CCD] = ax;
  if ( _data[ds*16+0x1CC0] == 3 ) // jz 
    goto loc_code_2013;
  sub_20E1();
loc_code_2013:
  sub_20F5();
  if ( cf ) // jb 
    return;
  ax = *(WORD*)&_data[ds*16+0x1CCD];
  *(WORD*)&_data[ds*16+0x1CBD] = ax;
  sub_209B();
}

void sub_2022()
{
  bh = 0;
  if ( _data[ds*16+0x1CB8] == 0 ) // jz 
    goto loc_code_203B;
  (_data[ds*16+0x1CCF])++;
  bl = _data[ds*16+0x1CCF];
  bl &= 6;
  bl |= 8;
  if ( bl ) // jnz 
    goto loc_code_2051;
loc_code_203B:
  _data[ds*16+0x1CCF] += 2;
  bl = _data[ds*16+0x1CCF];
  bl &= 2;
  if ( _data[ds*16+0x1CD0] != 1 ) // jnz 
    goto loc_code_2051;
  bl |= 4;
loc_code_2051:
  ax = *(WORD*)&_data[bx + 0x15C8];
  *(WORD*)&_data[ds*16+0x1CBB] = ax;
}

void sub_2059()
{
  cx = 0x0F04;
  cl -= al;
  *(WORD*)&_data[ds*16+0x1CC4] = cx;
  if ( ah == 0x0FF ) // jz 
    goto loc_code_2078;
  ah = 0;
  al <<= 1;
  *(WORD*)&_data[ds*16+0x1CBB] += ax;
  *(WORD*)&_data[ds*16+0x1CC6] = 0;
  goto loc_code_2086;
loc_code_2078:
  ah = 0;
  al <<= 1;
  al <<= 1;
  al <<= 1;
  ax += 0x120;
  *(WORD*)&_data[ds*16+0x1CC6] = ax;
loc_code_2086:
  _push(ds);
  _pop(es);
  si = *(WORD*)&_data[ds*16+0x1CBB];
  di = 0x0E;
  al = 4;
  sub_2D70();
  *(WORD*)&_data[ds*16+0x1CBB] = 0x0E;
}

void sub_209B()
{
  cx = *(WORD*)&_data[ds*16+0x1CC4];
  *(WORD*)&_data[ds*16+0x1CC2] = cx;
  ax = 0x0B800;
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    goto loc_code_20BE;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x1CBD];
  si = *(WORD*)&_data[ds*16+0x1CBB];
  bp = 0x1C40;
  sub_2CCC();
  return;
loc_code_20BE:
  _push(ds);
  ds = ax;
  _pop(es);
  _push(es);
  _push(ds);
  si = *(WORD*)&_data[es*16+0x1CBD];
  di = 0x1C40;
  sub_2DCA();
  _pop(es);
  _pop(ds);
  si = *(WORD*)&_data[ds*16+0x1CBB];
  di = *(WORD*)&_data[ds*16+0x1CBD];
  cx = *(WORD*)&_data[ds*16+0x1CC4];
  sub_2D9D();
}

void sub_20E1()
{
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x1CBD];
  si = 0x1C40;
  cx = *(WORD*)&_data[ds*16+0x1CC2];
  sub_2D9D();
}

void sub_20F5()
{
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    goto loc_code_2134;
  al = _data[ds*16+0x1CBF];
  al |= *(WORD*)&_data[ds*16+0x1CC0];
  al |= *(WORD*)&_data[ds*16+0x1CC1];
  if ( !al ) // jz 
    goto loc_code_2134;
  if ( _data[ds*16+0x57B] < 0x0A3 ) // jb 
    goto loc_code_2134;
  if ( _data[ds*16+0x558] != 0 ) // jnz 
    goto loc_code_2134;
  ax = *(WORD*)&_data[ds*16+0x1CC6];
  ax += 0x20;
  if ( ax < *(WORD*)&_data[ds*16+0x579] ) // jb 
    goto loc_code_2134;
  cf = (ax < 0x38); // cf-insertion
  ax -= 0x38;
  if ( !cf ) // jnb 
    goto loc_code_212A;
  ax = 0;
loc_code_212A:
  if ( ax > *(WORD*)&_data[ds*16+0x579] ) // ja 
    goto loc_code_2134;
  sub_2136();
  return;
loc_code_2134:
  _clc();
}

void sub_2136()
{
  if ( *(WORD*)&_data[ds*16+4] != 6 ) // jnz 
    goto loc_code_2149;
  al = _data[ds*16+0x57B];
  _data[ds*16+0x1CC8] = al;
  ax = *(WORD*)&_data[ds*16+0x579];
  *(WORD*)&_data[ds*16+0x1CC6] = ax;
loc_code_2149:
  ax = *(WORD*)&_data[ds*16+0x1CC6];
  ax += *(WORD*)&_data[ds*16+0x579];
  ax >>= 1;
  if ( ax < 0x118 ) // jb 
    goto loc_code_215A;
  ax = 0x117;
loc_code_215A:
  *(WORD*)&_data[ds*16+0x1CC6] = ax;
  bl = 1;
  if ( ax > 0x0A0 ) // ja 
    goto loc_code_216E;
  bl = 0x0FF;
  dx = 0x0A1;
  dx -= ax;
  goto loc_code_2173;
loc_code_216E:
  ax -= 0x9F;
  dx = ax;
loc_code_2173:
  _data[ds*16+0x1CB8] = bl;
  _data[ds*16+0x1CBF] = 1;
  _data[ds*16+0x1CC1] = 0;
  cl = 3;
  dx >>= cl;
  *(WORD*)&_data[ds*16+0x1CB9] = dx;
  if ( *(WORD*)&_data[ds*16+4] != 6 ) // jnz 
    goto loc_code_21BD;
  sub_11E3();
  al = _data[ds*16+0x1CB8];
  _push(ax);
  _data[ds*16+0x1CB8] = 0;
  *(WORD*)&_data[ds*16+0x1CC4] = 0x0F04;
  ax = *(WORD*)&_data[ds*16+0x15C8];
  *(WORD*)&_data[ds*16+0x1CBB] = ax;
  cx = *(WORD*)&_data[ds*16+0x1CC6];
  dl = _data[ds*16+0x1CC8];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x1CBD] = ax;
  sub_209B();
  _pop(ax);
  _data[ds*16+0x1CB8] = al;
loc_code_21BD:
  sub_20E1();
  sub_11E3();
  ax = 0;
  if ( *(WORD*)&_data[ds*16+0x579] >= 0x0A0 ) // jnb 
    goto loc_code_21D1;
  ax = 0x122;
loc_code_21D1:
  *(WORD*)&_data[ds*16+0x579] = ax;
  if ( *(WORD*)&_data[ds*16+4] != 0 ) // jnz 
    goto loc_code_21DE;
  sub_70D();
loc_code_21DE:
  _stc();
}

void sub_21E0()
{
  al = _data[ds*16+0x1CBF];
  al |= *(WORD*)&_data[ds*16+0x1CC0];
  al |= *(WORD*)&_data[ds*16+0x1CC1];
  if ( !al ) // jz 
    goto loc_code_2209;
  ax = *(WORD*)&_data[ds*16+0x327D];
  dl = _data[ds*16+0x327F];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x1CC6];
  dh = _data[ds*16+0x1CC8];
  di = 0x20;
  cx = 0x0F1E;
  sub_2E29();
  return;
loc_code_2209:
  _clc();
}

/*
  unknown_command(); // align 8
*/
void sub_2210()
{
  _data[ds*16+0x1D59] = 0;
}

void sub_2216()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x1D5A] ) // jnz 
    goto loc_code_2221;
  return;
loc_code_2221:
  cx = dx;
  if ( !sub_13D8() ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x1D5A] = cx;
  sub_22F7();
  if ( cf ) // jb 
    return;
  if ( _data[ds*16+0x1D59] != 0 ) // jnz 
    goto loc_code_226D;
  if ( _data[ds*16+0x57B] == 0x86 ) // jz 
    goto loc_code_224E;
  if ( _data[ds*16+0x57B] == 0x8E ) // jz 
    goto loc_code_224E;
  sub_2DFD();
  if ( dl > 5 ) // ja 
    return;
loc_code_224E:
  sub_15D0();
  dl += 3;
  _data[ds*16+0x1D5E] = dl;
  sub_2DFD();
  dx &= 7;
  cx += dx;
  cx += 6;
  *(WORD*)&_data[ds*16+0x1D5C] = cx;
  _data[ds*16+0x1D59] = 0x1B;
loc_code_226D:
  (_data[ds*16+0x1D59])--;
  cx = *(WORD*)&_data[ds*16+0x1D5C];
  dl = _data[ds*16+0x1D5E];
  if ( _data[ds*16+0x1D59] <= 0x0D ) // jbe 
    goto loc_code_2291;
  dl += *(WORD*)&_data[ds*16+0x1D59];
  dl -= 0x0F;
  bx = 0x1B02;
  bh -= *(WORD*)&_data[ds*16+0x1D59];
  goto loc_code_229F;
loc_code_2291:
  dl += 0x0C;
  dl -= *(WORD*)&_data[ds*16+0x1D59];
  bx = 2;
  bh += *(WORD*)&_data[ds*16+0x1D59];
loc_code_229F:
  *(WORD*)&_data[ds*16+0x1D64] = bx;
  _data[ds*16+0x1D5F] = dl;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x1D62] = ax;
  sub_22DC();
  sub_22F7();
  if ( cf ) // jb 
    return;
  if ( _data[ds*16+0x1D59] != 0 ) // jnz 
    goto loc_code_22BD;
  return;
loc_code_22BD:
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x1D62];
  si = 0x1CF0;
  *(WORD*)&_data[ds*16+0x1D60] = di;
  cx = *(WORD*)&_data[ds*16+0x1D64];
  *(WORD*)&_data[ds*16+0x1D66] = cx;
  bp = 0x1D24;
  sub_2CCC();
}

void sub_22DC()
{
  if ( _data[ds*16+0x1D59] == 0x1A ) // jz 
    return;
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x1D60];
  si = 0x1D24;
  cx = *(WORD*)&_data[ds*16+0x1D66];
  sub_2D9D();
}

void sub_22F7()
{
  if ( _data[ds*16+0x1D59] != 0 ) // jnz 
    goto loc_code_2300;
  _clc();
  return;
loc_code_2300:
  cx = *(WORD*)&_data[ds*16+0x1D64];
  _xchg(ch, cl);
  ax = *(WORD*)&_data[ds*16+0x1D5C];
  dl = _data[ds*16+0x1D5F];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  ch = 0x0E;
  sub_2E29();
  if ( !cf ) // jnb cf=0
    return;
  _data[ds*16+0x1D58] = 1;
}

/*
  unknown_command(); // align 10h
*/
void sub_2330()
{
  *(WORD*)&_data[ds*16+0x1F6C] = 0;
  ax = 0;
  dl = 1;
  if ( *(WORD*)&_data[ds*16+0x579] > 0x0A0 ) // ja 
    goto loc_code_2347;
  ax = 0x12C;
  dl = 0x0FF;
loc_code_2347:
  *(WORD*)&_data[ds*16+0x1F30] = ax;
  *(WORD*)&_data[ds*16+0x1F32] = ax;
  *(WORD*)&_data[ds*16+0x1F34] = ax;
  _data[ds*16+0x1F3C] = dl;
  _data[ds*16+0x1F3D] = dl;
  _data[ds*16+0x1F3E] = dl;
  _data[ds*16+0x1F48] = 1;
  _data[ds*16+0x1F49] = 1;
  _data[ds*16+0x1F4A] = 1;
  _data[ds*16+0x1F50] = 0;
  _data[ds*16+0x1F51] = 0;
  _data[ds*16+0x1F52] = 0;
}

void sub_237B()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x1F65] ) // jnz 
    goto loc_code_2386;
  return;
loc_code_2386:
  *(WORD*)&_data[ds*16+0x1F65] = dx;
  if ( _data[ds*16+0x55A] != 0 ) // jnz 
    return;
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  bx++;
  if ( bx < 3 ) // jb 
    goto loc_code_239E;
  bx = 0;
loc_code_239E:
  *(WORD*)&_data[ds*16+0x1F6C] = bx;
  sub_265E();
  if ( cf ) // jb cf=1
    return;
  sub_2567();
  if ( cf ) // jb cf=1
    return;
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  if ( _data[bx + 0x1F50] == 0 ) // jz 
    goto loc_code_23EB;
  ah = 0;
  _int(0x1A);
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  bl <<= 1;
  dx -= *(WORD*)&_data[bx + 0x1F53];
  if ( dx < 0x36 ) // jb 
    return;
  dl = 1;
  ax = 0;
  if ( *(WORD*)&_data[ds*16+0x579] > 0x0A0 ) // ja 
    goto loc_code_23DC;
  ax = 0x12C;
  dl = 0x0FF;
loc_code_23DC:
  *(WORD*)&_data[bx + 0x1F30] = ax;
  bl >>= 1;
  _data[bx + 0x1F50] = 0;
  _data[bx + 0x1F3C] = dl;
loc_code_23EB:
  dl = _data[bx + 0x1F3C];
  _data[bx + 0x1F3F] = dl;
  if ( _data[ds*16+0x1664] == 0 ) // jz 
    goto loc_code_2403;
  *(WORD*)&_data[ds*16+0x1F69] = 0x0C;
  goto loc_code_2418;
loc_code_2403:
  ax = 8;
  if ( _data[ds*16+0x57B] <= 0x60 ) // jbe 
    goto loc_code_240F;
  al >>= 1;
loc_code_240F:
  *(WORD*)&_data[ds*16+0x1F69] = ax;
  if ( bx != *(WORD*)&_data[ds*16+0x52F] ) // jnz 
    goto loc_code_2425;
loc_code_2418:
  if ( _data[bx + 0x1F3C] != 0 ) // jnz 
    goto loc_code_2425;
  sub_2DFD();
  goto loc_code_248A;
loc_code_2425:
  if ( _data[ds*16+0x55C] == 0 ) // jz 
    goto loc_code_2466;
  al = _data[bx + 0x1F36];
  if ( al > _data[ds*16+0x57B] ) // ja 
    goto loc_code_2466;
  al += 0x10;
  if ( al < _data[ds*16+0x57B] ) // jb 
    goto loc_code_2466;
  sub_2DFD();
  si = *(WORD*)&_data[ds*16+8];
  if ( dl > _data[si + 0x1F6E] ) // ja 
    goto loc_code_2466;
  *(WORD*)&_data[ds*16+0x1F69] = 0x0C;
  al = 1;
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x1F30];
  bl >>= 1;
  if ( cx < *(WORD*)&_data[ds*16+0x579] ) // jb 
    goto loc_code_2463;
  al = 0x0FF;
loc_code_2463:
  goto loc_code_2492;
loc_code_2466:
  cl = 0x18;
  if ( _data[ds*16+0x57B] <= 0x60 ) // jbe 
    goto loc_code_247A;
  cl = 0x28;
  if ( _data[bx + 0x1F3C] != 0 ) // jnz 
    goto loc_code_247A;
  cl = 0x10;
loc_code_247A:
  sub_2DFD();
  if ( dl > cl ) // ja 
    goto loc_code_2496;
  al = 0;
  if ( _data[bx + 0x1F3C] != 0 ) // jnz 
    goto loc_code_2492;
loc_code_248A:
  al = dl;
  al &= 1;
  if ( al ) // jnz 
    goto loc_code_2492;
  al = 0x0FF;
loc_code_2492:
  _data[bx + 0x1F3C] = al;
loc_code_2496:
  dl = _data[bx + 0x1F3C];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x1F30];
  if ( dl < 1 ) // jb 
    goto loc_code_24C2;
  if ( dl != 1 ) // jnz 
    goto loc_code_24B8;
  ax += *(WORD*)&_data[ds*16+0x1F69];
  if ( ax < 0x12F ) // jb 
    goto loc_code_24C2;
  ax = 0x12E;
  dl = 0x0FF;
  goto loc_code_24C2;
loc_code_24B8:
  cf = (ax < *(WORD*)&_data[ds*16+0x1F69]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x1F69];
  if ( !cf ) // jnb 
    goto loc_code_24C2;
  ax = 0;
  dl = 1;
loc_code_24C2:
  *(WORD*)&_data[bx + 0x1F30] = ax;
  bl >>= 1;
  _data[bx + 0x1F3C] = dl;
  dl = _data[bx + 0x1F36];
  cx = ax;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x1F4B] = ax;
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  if ( _data[bx + 0x1F48] != 0 ) // jnz 
    goto loc_code_24F0;
  al = _data[bx + 0x1F3C];
  al |= *(WORD*)&_data[bx + 0x1F3F];
  if ( !al ) // jz 
    goto loc_code_24F0;
  sub_254D();
loc_code_24F0:
  sub_265E();
  if ( cf ) // jb cf=1
    return;
  sub_2567();
  if ( !cf ) // jnb cf=0
    goto loc_code_24FB;
  return;
loc_code_24FB:
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  _data[bx + 0x1F48] = 0;
  if ( _data[bx + 0x1F3C] != 0 ) // jnz 
    goto loc_code_2518;
  if ( _data[bx + 0x1F3F] == 0 ) // jz 
    return;
  si = 0x1E30;
  goto loc_code_2533;
loc_code_2518:
  si = 0x1E50;
  _data[bx + 0x1F4D]++;
  if ( _data[bx + 0x1F4D] & 1 ) // jnz 
    goto loc_code_2529;
  si += 0x20;
loc_code_2529:
  if ( _data[bx + 0x1F3C] == 1 ) // jz 
    goto loc_code_2533;
  si += 0x40;
loc_code_2533:
  bl <<= 1;
  di = *(WORD*)&_data[ds*16+0x1F4B];
  *(WORD*)&_data[bx + 0x1F42] = di;
  ax = 0x0B800;
  es = ax;
  bp = *(WORD*)&_data[bx + 0x1F59];
  cx = 0x802;
  sub_2D35();
}

void sub_254D()
{
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  bl <<= 1;
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[bx + 0x1F42];
  si = *(WORD*)&_data[bx + 0x1F59];
  cx = 0x802;
  sub_2D9D();
}

void sub_2567()
{
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  dl = _data[bx + 0x1F36];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x1F30];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E08;
  sub_2E29();
  if ( cf ) // jb cf=1
    goto loc_code_258E;
  return;
  ///goto locret_code_265D;
loc_code_258E:
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  if ( _data[bx + 0x1F50] != 0 ) // jnz 
    goto loc_code_260C;
  if ( _data[ds*16+0x57C] < 0x26 ) // jb 
    goto loc_code_260C;
  if ( _data[ds*16+0x55C] == 0 ) // jz 
    goto loc_code_260E;
  _data[ds*16+0x55C] = 0;
  _data[ds*16+0x55B] = 0x11;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x56E] = 0;
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  bl <<= 1;
  di = *(WORD*)&_data[bx + 0x1F42];
  if ( *(WORD*)&_data[bx + 0x1F30] < 0x10 ) // jb 
    goto loc_code_25CF;
  di -= 4;
loc_code_25CF:
  *(WORD*)&_data[ds*16+0x1F67] = di;
  ax = 0x0B800;
  es = ax;
  si = 0x1D70;
  bp = 0x0E;
  cx = 0x806;
  sub_2CCC();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x1F65] = dx;
loc_code_25EC:
  sub_5A90();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x1F65];
  if ( dx < 8 ) // jb 
    goto loc_code_25EC;
  sub_5B21();
  di = *(WORD*)&_data[ds*16+0x1F67];
  si = 0x0E;
  cx = 0x806;
  sub_2D9D();
loc_code_260C:
  _stc();
  return;
loc_code_260E:
  ah = 0;
  _int(0x1A);
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  _data[bx + 0x1F50] = 1;
  _data[bx + 0x1F3C] = 1;
  bl <<= 1;
  *(WORD*)&_data[bx + 0x1F53] = dx;
  sub_11E3();
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  bl <<= 1;
  si = *(WORD*)&_data[bx + 0x1F5F];
  di = *(WORD*)&_data[bx + 0x1F42];
  ax = 0x0B800;
  es = ax;
  bp = 0x0E;
  cx = 0x802;
  sub_2CCC();
  sub_1124();
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  al = _data[bx + 0x1F39];
  sub_2706();
  ax = 0x3E8;
  bx = 0x2EE;
  sub_593B();
  _stc();
}

void sub_265E()
{
  if ( _data[ds*16+0x1673] != 0 ) // jnz 
    goto loc_code_2667;
  _clc();
  return;
loc_code_2667:
  bx = *(WORD*)&_data[ds*16+0x1F6C];
  dl = _data[bx + 0x1F36];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x1F30];
  si = 0x10;
  di = si;
  bx = *(WORD*)&_data[ds*16+0x1671];
  dh = _data[ds*16+0x1673];
  cx = 0x0C08;
  sub_2E29();
}

/*
  unknown_command(); // align 8
*/
void sub_2690()
{
  _push(ds);
  _pop(es);
  cx = 7;
  si = 0x1F82;
loc_code_2698:
  _lodsb();
  bx = 7;
  bx -= cx;
  if ( --cx && (al == _data[bx + 0x1F89]) )
    goto loc_code_2698;
  if ( al > _data[bx + 0x1F89] ) // ja 
    goto loc_code_26A7;
  return;
loc_code_26A7:
  si = 0x1F82;
  di = 0x1F89;
  cx = 7;
  _rep_movsb();
}

void sub_26B3()
{
  al = _data[ds*16+0x1F80];
  if ( al != _data[ds*16+0x1F81] ) // jnz 
    goto loc_code_26BD;
  return;
loc_code_26BD:
  _data[ds*16+0x1F81] = al;
  ah = 0;
  cl = 4;
  ax <<= cl;
  ax += 0x2720;
  si = ax;
  ax = 0x0B800;
  es = ax;
  di = 0x1260;
  cx = 0x801;
  sub_2D9D();
}

void sub_26DA()
{
  di = 0x1F82;
  sub_26E8();
}

void sub_26E1()
{
  di = 0x1F89;
  sub_26E8();
}

void sub_26E8()
{
  _push(ds);
  _pop(es);
  cx = 7;
  al = 0;
  _rep_stosb();
}

void sub_26F2()
{
  bx = 0x1F89;
  di = 0x12CA;
  sub_2739();
}

void sub_26FC()
{
  bx = 0x1F82;
  di = 0x143C;
  sub_2739();
}

void sub_2706()
{
  cx = 6;
loc_code_2709:
  bx = cx;
  ah = 0;
  al += *(WORD*)&_data[bx + 0x1F81];
  _aaa();
  _data[bx + 0x1F81] = al;
  al = ah;
  if ( --cx )
    goto loc_code_2709;
  sub_26FC();
}

void sub_271E()
{
  _push(cx);
  _push(ax);
  _push(bx);
  _clc();
  _pushf();
  cx = 7;
loc_code_2726:
  _popf();
  bx = cx;
  bx--;
  al = _data[bx + di];
  unknown_condition(); // verify cf
  al += *(WORD*)&_data[bx + si] + cf;
  _aaa();
  _data[bx + di] = al;
  _pushf();
  if ( --cx )
    goto loc_code_2726;
  _popf();
  _pop(bx);
  _pop(ax);
  _pop(cx);
}

void sub_2739()
{
  ax = 0x0B800;
  es = ax;
  *(WORD*)&_data[ds*16+0x1F90] = di;
  *(WORD*)&_data[ds*16+0x1F93] = bx;
  _data[ds*16+0x1F92] = 0;
loc_code_274B:
  bx = *(WORD*)&_data[ds*16+0x1F93];
  al = _data[bx];
  ah = 0;
  cl = 4;
  ax <<= cl;
  ax += 0x2720;
  si = ax;
  di = *(WORD*)&_data[ds*16+0x1F90];
  cx = 0x801;
  sub_2D9D();
  *(WORD*)&_data[ds*16+0x1F90] += 2;
  (*(WORD*)&_data[ds*16+0x1F93])++;
  (_data[ds*16+0x1F92])++;
  if ( _data[ds*16+0x1F92] == 7 ) // jz 
    return;
  if ( _data[ds*16+0x1F92] != 3 ) // jnz 
    goto loc_code_274B;
  *(WORD*)&_data[ds*16+0x1F90] += 2;
  goto loc_code_274B;
}

/*
  unknown_command(); // align 8
*/
void sub_2790()
{
  ax = 0x0B800;
  es = ax;
  if ( *(WORD*)&_data[ds*16+4] != 2 ) // jnz 
    goto loc_code_27EE;
  _cld();
  di = 0;
  ax = 0x0AAAA;
  cx = 0x50;
  _rep_stosw();
  di = 0x2000;
  cx = 0x50;
  _rep_stosw();
  *(WORD*)&_data[ds*16+0x2654] = 0;
loc_code_27B5:
  sub_2DFD();
  dx &= 0x18;
  if ( dl == _data[ds*16+0x2653] ) // jz 
    goto loc_code_27B5;
  _data[ds*16+0x2653] = dl;
  bx = *(WORD*)&_data[ds*16+0x2654];
  _data[bx + 0x2656] = dl;
  dx += 0x2020;
  si = dx;
  di = bx;
  di <<= 1;
  di += 0x0A0;
  cx = 0x401;
  sub_2D9D();
  (*(WORD*)&_data[ds*16+0x2654])++;
  if ( *(WORD*)&_data[ds*16+0x2654] < 0x28 ) // jb 
    goto loc_code_27B5;
  return;
loc_code_27EE:
  if ( *(WORD*)&_data[ds*16+4] != 7 ) // jnz 
    goto loc_code_27F9;
  sub_300F();
  return;
loc_code_27F9:
  if ( *(WORD*)&_data[ds*16+4] != 6 ) // jnz 
    goto loc_code_283E;
  ax = 0;
  sub_29A0();
  bx = 0x2570;
  ax = 0x64A;
  sub_2B24();
  *(WORD*)&_data[ds*16+0x2650] = 0x48;
  _data[ds*16+0x2652] = 0x38;
  ax = 0x0DD2;
  sub_2958();
  ax = 0x0DF6;
  sub_2970();
  si = 0x1FA0;
  di = 0x67E;
  cx = 0x1002;
  sub_2D9D();
  bx = 0x2344;
  ax = 0x0B84;
  sub_2B24();
  sub_4B47();
  return;
loc_code_283E:
  if ( *(WORD*)&_data[ds*16+4] != 5 ) // jnz 
    goto loc_code_288D;
  ax = 0x640;
  sub_29A0();
  bx = 0x2570;
  ax = 0x0CB6;
  sub_2B24();
  *(WORD*)&_data[ds*16+0x2650] = 0x0F8;
  _data[ds*16+0x2652] = 0x60;
  ax = 0x140E;
  sub_2958();
  ax = 0x1434;
  sub_2970();
  ax = 0x143E;
  sub_2970();
  ax = 0x16A0;
  sub_2988();
  bx = 0x2344;
  ax = 0x1184;
  sub_2B24();
  si = 0x1FE0;
  di = 0x0DD6;
  cx = 0x1002;
  sub_2D9D();
  return;
loc_code_288D:
  if ( *(WORD*)&_data[ds*16+4] != 4 ) // jnz 
    goto loc_code_28BE;
  ax = 0x640;
  sub_29A0();
  bx = 0x2570;
  ax = 0x0CBA;
  sub_2B24();
  *(WORD*)&_data[ds*16+0x2650] = 0x108;
  _data[ds*16+0x2652] = 0x60;
  ax = 0x1439;
  sub_2958();
  ax = 0x16C0;
  sub_2945();
  sub_3F9E();
  return;
loc_code_28BE:
  if ( *(WORD*)&_data[ds*16+4] != 3 ) // jnz 
    goto loc_code_2909;
  ax = 0x640;
  sub_29A0();
  bx = 0x2570;
  ax = 0x0C90;
  sub_2B24();
  *(WORD*)&_data[ds*16+0x2650] = 0x60;
  _data[ds*16+0x2652] = 0x60;
  ax = 0x140C;
  sub_2958();
  ax = 0x1418;
  sub_2970();
  bx = 0x2344;
  ax = 0x1184;
  sub_2B24();
  bx = 0x2344;
  ax = 0x11A2;
  sub_2B24();
  bx = 0x2624;
  ax = 0;
  sub_2B24();
  sub_3BDB();
  return;
loc_code_2909:
  ax = 0x640;
  sub_29A0();
  bx = 0x2570;
  ax = 0x0CA0;
  sub_2B24();
  *(WORD*)&_data[ds*16+0x2650] = 0x0A0;
  _data[ds*16+0x2652] = 0x60;
  ax = 0x1406;
  sub_2958();
  bx = 0x2344;
  ax = 0x11C4;
  sub_2B24();
  ax = 0x1422;
  sub_2970();
  ax = 0x1690;
  sub_2988();
  ax = 0x16B6;
  sub_2945();
}

void sub_2945()
{
  *(WORD*)&_data[ds*16+0x2634] = ax;
  bx = 0x2384;
  sub_2B24();
  ax = *(WORD*)&_data[ds*16+0x2634];
  bx = 0x238C;
  sub_2B24();
}

void sub_2958()
{
  *(WORD*)&_data[ds*16+0x2634] = ax;
  si = 8;
loc_code_295E:
  ax = *(WORD*)&_data[ds*16+0x2634];
  bx = *(WORD*)&_data[si + 0x2634];
  _push(si);
  sub_2B24();
  _pop(si);
  zf = (si == 2); // zf-insertion
  si -= 2;
  if ( !zf ) // jnz 
    goto loc_code_295E;
}

void sub_2970()
{
  *(WORD*)&_data[ds*16+0x2634] = ax;
  si = 0x0A;
loc_code_2976:
  ax = *(WORD*)&_data[ds*16+0x2634];
  bx = *(WORD*)&_data[si + 0x263C];
  _push(si);
  sub_2B24();
  _pop(si);
  zf = (si == 2); // zf-insertion
  si -= 2;
  if ( !zf ) // jnz 
    goto loc_code_2976;
}

void sub_2988()
{
  *(WORD*)&_data[ds*16+0x2634] = ax;
  si = 8;
loc_code_298E:
  ax = *(WORD*)&_data[ds*16+0x2634];
  bx = *(WORD*)&_data[si + 0x2646];
  _push(si);
  sub_2B24();
  _pop(si);
  zf = (si == 2); // zf-insertion
  si -= 2;
  if ( !zf ) // jnz 
    goto loc_code_298E;
}

void sub_29A0()
{
  *(WORD*)&_data[ds*16+0x267E] = ax;
  bx = 0x251C;
  sub_2B24();
  ax = 0;
  _cld();
  di = *(WORD*)&_data[ds*16+0x267E];
  di += 0x284;
  cx = 0x24;
  _rep_stosw();
  di = *(WORD*)&_data[ds*16+0x267E];
  di += 0x1184;
  cx = 0x24;
  _rep_stosw();
  di = *(WORD*)&_data[ds*16+0x267E];
  di += 0x2284;
  al = 0x2A;
  sub_29E1();
  di = *(WORD*)&_data[ds*16+0x267E];
  di += 0x22CB;
  al = 0x0A8;
  sub_29E1();
}

void sub_29E1()
{
  cx = 0x5F;
loc_code_29E4:
  _data[es*16+di] = al;
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_29F4;
  di += 0x50;
loc_code_29F4:
  if ( --cx )
    goto loc_code_29E4;
}

/*
  unknown_command(); // align 10h
*/
void sub_2A00()
{
  ax = 0x0B800;
  es = ax;
  _cld();
  di = 0;
  ax = 0x0AAAA;
  cx = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  cx = 0x0FA0;
  _rep_stosw();
  sub_2B9E();
  bx = 0x28A0;
  ax = 0;
  sub_2B24();
  sub_2A68();
  sub_2C84();
  sub_2B8B();
  sub_2A80();
}

void sub_2A30()
{
  ax = 0x0B800;
  es = ax;
  _cld();
  di = 0;
  ax = 0x0AAAA;
  cx = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  cx = 0x0FA0;
  _rep_stosw();
  sub_2B9E();
  bx = 0x28A0;
  ax = 0;
  sub_2B24();
  sub_2A68();
  ax = *(WORD*)&_data[ds*16+8];
  _push(ax);
  *(WORD*)&_data[ds*16+8] = 1;
  sub_2C84();
  _pop(ax);
  *(WORD*)&_data[ds*16+8] = ax;
}

void sub_2A68()
{
  bx = *(WORD*)&_data[ds*16+0x6DF8];
  bx &= 3;
  bl <<= 1;
  si = *(WORD*)&_data[bx + 0x2AD1];
  di = 0x1902;
  cx = 0x801;
  sub_2D9D();
}

void sub_2A80()
{
  bx = 0x0F;
loc_code_2A83:
  _data[bx + 0x1015] = 0;
  bx--;
  if ( bx ) // jnz 
    goto loc_code_2A83;
  di = 0x140;
  bh = 0x80;
  *(WORD*)&_data[ds*16+0x2ACA] = 0;
  sub_2AC6();
  di = 0x640;
  bh = 0x30;
  *(WORD*)&_data[ds*16+0x2ACA] = 5;
  sub_2AC6();
  di = 0x0B40;
  bh = 0;
  *(WORD*)&_data[ds*16+0x2ACA] = 0x0A;
  sub_2AC6();
  _data[ds*16+0x525] = 0x10;
  *(WORD*)&_data[ds*16+0x52F] = 0;
  _data[ds*16+0x531] = 1;
}

void sub_2AC6()
{
  _data[ds*16+0x2AC9] = bh;
  _data[ds*16+0x2AC4] = 0;
loc_code_2ACF:
  _push(di);
  _push(es);
  bx = *(WORD*)&_data[ds*16+8];
  bl = _data[bx + 0x2ABA];
  bh = _data[ds*16+0x2AC9];
  ax = seg_data;
  es = ax;
  di = 0x4D7;
  sub_67D();
  _pop(es);
  _pop(di);
  _push(di);
  si = 0x4D7;
  cx = 0x1002;
  sub_2D9D();
  bh = 0;
  bl = _data[ds*16+0x2AC4];
  cl = bl;
  bl >>= 1;
  bl >>= 1;
  cl = ~cl;
  cl &= 3;
  cl <<= 1;
  al = _data[ds*16+0x540];
  al <<= cl;
  si = *(WORD*)&_data[ds*16+0x2ACA];
  *(WORD*)&_data[bx + si + 0x1016] |= al;
  _pop(di);
  di += 4;
  (_data[ds*16+0x2AC4])++;
  if ( _data[ds*16+0x2AC4] < 0x14 ) // jb 
    goto loc_code_2ACF;
}

void sub_2B24()
{
  cx = *(WORD*)&_data[bx];
  *(WORD*)&_data[ds*16+0x2AC7] = cx;
  *(WORD*)&_data[ds*16+0x2ACC] = ax;
  bx += 2;
loc_code_2B30:
  si = *(WORD*)&_data[bx];
  if ( si != 0x0FFFF ) // jnz 
    goto loc_code_2B39;
  return;
loc_code_2B39:
  di = *(WORD*)&_data[bx + 2];
  di += *(WORD*)&_data[ds*16+0x2ACC];
  _cld();
  _data[ds*16+0x2AD0] = ch;
  ch = 0;
  *(WORD*)&_data[ds*16+0x2ACE] = cx;
loc_code_2B4B:
  cx = *(WORD*)&_data[ds*16+0x2ACE];
  _rep_movsb();
  di -= *(WORD*)&_data[ds*16+0x2ACE];
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_2B62;
  di += 0x50;
loc_code_2B62:
  (_data[ds*16+0x2AD0])--;
  if ( _data[ds*16+0x2AD0] ) // jnz 
    goto loc_code_2B4B;
  bx += 4;
  cx = *(WORD*)&_data[ds*16+0x2AC7];
  goto loc_code_2B30;
}

void sub_2B71()
{
  _data[ds*16+0x2AC4] = 4;
loc_code_2B76:
  si = 0x2680;
  cx = 0x1005;
  _push(di);
  sub_2D9D();
  _pop(di);
  di += 0x14;
  (_data[ds*16+0x2AC4])--;
  if ( _data[ds*16+0x2AC4] ) // jnz 
    goto loc_code_2B76;
}

void sub_2B8B()
{
  di = 0x3C5;
  sub_2B71();
  di = 0x8C5;
  sub_2B71();
  di = 0x0DC5;
  sub_2B71();
}

void sub_2B9E()
{
  *(WORD*)&_data[ds*16+0x2AC2] = 0x103E;
loc_code_2BA4:
  *(WORD*)&_data[ds*16+0x2AC2] += 2;
  di = *(WORD*)&_data[ds*16+0x2AC2];
  if ( di >= 0x1090 ) // jnb 
    goto loc_code_2BD2;
loc_code_2BB3:
  sub_2DFD();
  dx &= 0x30;
  if ( dl == _data[ds*16+0x2AC4] ) // jz 
    goto loc_code_2BB3;
  _data[ds*16+0x2AC4] = dl;
  dx += 0x2904;
  si = dx;
  cx = 0x801;
  sub_2D9D();
  goto loc_code_2BA4;
loc_code_2BD2:
  di = 0x1180;
  ax = 0x5655;
  cx = 0x500;
  _cld();
  _rep_stosw();
  di = 0x3180;
  cx = 0x500;
  _rep_stosw();
  *(WORD*)&_data[ds*16+0x2AC2] = 0x2944;
loc_code_2BEC:
  _data[ds*16+0x2AC4] = 9;
loc_code_2BF1:
  sub_2DFD();
  dx &= 0x776;
  dx += 0x12C0;
  di = dx;
  si = *(WORD*)&_data[ds*16+0x2AC2];
  cx = 0x501;
  sub_2D9D();
  (_data[ds*16+0x2AC4])--;
  if ( _data[ds*16+0x2AC4] ) // jnz 
    goto loc_code_2BF1;
  *(WORD*)&_data[ds*16+0x2AC2] += 0x0A;
  if ( *(WORD*)&_data[ds*16+0x2AC2] < 0x296C ) // jb 
    goto loc_code_2BEC;
  _data[ds*16+0x2AC4] = 5;
loc_code_2C20:
  sub_2DFD();
  dx &= 0x3E;
  dx += 0x3A98;
  di = dx;
  si = 0x296C;
  cx = 0x501;
  sub_2D9D();
  (_data[ds*16+0x2AC4])--;
  if ( _data[ds*16+0x2AC4] ) // jnz 
    goto loc_code_2C20;
}

void sub_2C3D()
{
  *(WORD*)&_data[ds*16+0x2AC2] = di;
  al = 3;
  if ( di < 0x1720 ) // jb 
    goto loc_code_2C4B;
  al--;
loc_code_2C4B:
  _data[ds*16+0x2AC4] = al;
  *(WORD*)&_data[ds*16+0x2AC2] += 0x1E0;
  si = 0x2976;
  cx = 0x0C05;
  sub_2D9D();
loc_code_2C5D:
  di = *(WORD*)&_data[ds*16+0x2AC2];
  *(WORD*)&_data[ds*16+0x2AC2] += 0x140;
  si = 0x29EE;
  cx = 0x804;
  sub_2D9D();
  (_data[ds*16+0x2AC4])--;
  if ( _data[ds*16+0x2AC4] ) // jnz 
    goto loc_code_2C5D;
  di = *(WORD*)&_data[ds*16+0x2AC2];
  si = 0x2A2E;
  cx = 0x0B04;
  sub_2D9D();
}

void sub_2C84()
{
  bx = *(WORD*)&_data[ds*16+8];
  bl = _data[bx + 0x2AB2];
loc_code_2C8C:
  *(WORD*)&_data[ds*16+0x2AC5] = bx;
  di = *(WORD*)&_data[bx + 0x2A86];
  if ( di != 0 ) // jnz 
    goto loc_code_2C9A;
  return;
loc_code_2C9A:
  sub_2C3D();
  bx = *(WORD*)&_data[ds*16+0x2AC5];
  bx += 2;
  goto loc_code_2C8C;
}

/*
  return;
  unknown_command(); // align 10h
*/
void sub_2CB0() 
{
  al = dl;
  ah = 0x28; // nieco s y-suradnicou
  ax = (WORD)ah * (WORD)al;

  if ( !(dl & 1) ) // jz 
    goto loc_code_2CBE;
  ax += 0x1FD8;
loc_code_2CBE:
  dx = cx;
  dx >>= 1;
  dx >>= 1;
  ax += dx;
  cl &= 3;
  cl <<= 1;
}

void sub_2CCC()	// PUT IMAGE OR
{
  _cld();
  _data[ds*16+0x2AE0] = cl;
  _data[ds*16+0x2AE2] = ch;
  ch = 0;
  dx = 0x0FF0;
loc_code_2CDA:
  cl = _data[ds*16+0x2AE0];
loc_code_2CDE:
  dx = 0x30C0;
  _ASSERT( es == 0xb800 && ds == 0);
  bx = *(WORD*)&_video[0*es*16+di];
  *(WORD*)&_data[ds*16+bp+0] = bx;
  _lodsw();
  *(WORD*)&_data[ds*16+0x2AE3] = ax;
loc_code_2CEC:
  if ( ah & dl ) // jnz 
    goto loc_code_2CF2;
  ah |= dl;
loc_code_2CF2:
  if ( ah & dh ) // jnz 
    goto loc_code_2CF8;
  ah |= dh;
loc_code_2CF8:
  if ( al & dl ) // jnz 
    goto loc_code_2CFE;
  al |= dl;
loc_code_2CFE:
  if ( al & dh ) // jnz 
    goto loc_code_2D04;
  al |= dh;
loc_code_2D04:
  dx ^= 0x33CC;
  if ( dh & 3 ) // jnz 
    goto loc_code_2CEC;
  ax &= bx;
  ax |= *(WORD*)&_data[ds*16+0x2AE3];
  _stosw();
  bp += 2;
  if ( --cx )
    goto loc_code_2CDE;
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_2D2E;
  di += 0x50;
loc_code_2D2E:
  (_data[ds*16+0x2AE2])--;
  if ( _data[ds*16+0x2AE2] ) // jnz 
    goto loc_code_2CDA;
}

void sub_2D35() // put image AND
{
  _cld();
  _data[ds*16+0x2AE0] = cl;
  _data[ds*16+0x2AE2] = ch;
  ch = 0;
loc_code_2D40:
  cl = _data[ds*16+0x2AE0];
  _ASSERT( cl > 0 );
loc_code_2D44:
  _ASSERT( es == 0xb800 && ds == 0);
  bx = *(WORD*)&_video[0*es*16+di];
  *(WORD*)&_data[ds*16+bp+0] = bx;
  _lodsw();
  ax &= bx;
  _stosw();
  bp += 2;
  if ( --cx )
    goto loc_code_2D44;
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_2D69;
  di += 0x50;
loc_code_2D69:
  (_data[ds*16+0x2AE2])--;
  if ( _data[ds*16+0x2AE2] ) // jnz 
    goto loc_code_2D40;
}

void sub_2D70()
{
  _cld();
  *(WORD*)&_data[ds*16+0x2AE9] = si;
  _data[ds*16+0x2AE0] = cl;
  _data[ds*16+0x2AE2] = ch;
  al <<= 1;
  _data[ds*16+0x2AEB] = al;
  ch = 0;
loc_code_2D84:
  cl = _data[ds*16+0x2AE0];
  _rep_movsw();
  cl = _data[ds*16+0x2AEB];
  *(WORD*)&_data[ds*16+0x2AE9] += cx;
  si = *(WORD*)&_data[ds*16+0x2AE9];
  (_data[ds*16+0x2AE2])--;
  if ( _data[ds*16+0x2AE2] ) // jnz 
    goto loc_code_2D84;
}

void sub_2D9D()		// PUT IMAGE ok
{
  _cld();
  _data[ds*16+0x2AE0] = cl;
  _data[ds*16+0x2AE2] = ch;
  ch = 0;
loc_code_2DA8:
  cl = _data[ds*16+0x2AE0];
  _rep_movsw();
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di -= *(WORD*)&_data[ds*16+0x2AE0];
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_2DC3;
  di += 0x50;
loc_code_2DC3:
  (_data[ds*16+0x2AE2])--;
  if ( _data[ds*16+0x2AE2] ) // jnz 
    goto loc_code_2DA8;
}

void sub_2DCA()
{
  _cld();
  _data[es*16+0x2AE0] = cl;
  _data[es*16+0x2AE2] = ch;
  ch = 0;
loc_code_2DD7:
  cl = _data[es*16+0x2AE0];
  _rep_movsw();
  si -= *(WORD*)&_data[es*16+0x2AE0];
  si -= *(WORD*)&_data[es*16+0x2AE0];
  si ^= 0x2000;
  if ( si & 0x2000 ) // jnz 
    goto loc_code_2DF5;
  si += 0x50;
loc_code_2DF5:
  (_data[es*16+0x2AE2])--;
  if ( _data[es*16+0x2AE2] ) // jnz 
    goto loc_code_2DD7;
}

void sub_2DFD()
{
  dx = *(WORD*)&_data[ds*16+0x2AE5];
  dl ^= dh;
  dl >>= 1;
  cf = dl & 1 ? 1 : 0;
  dl >>= 1;
  _rcr(*(WORD*)&_data[ds*16+0x2AE5], 1);
  dx = *(WORD*)&_data[ds*16+0x2AE5];
}

void sub_2E10()
{
  al = 0;
  _out(0x43, al);
  _in(al, 0x40);
  ah = al;
  _in(al, 0x40);
  if ( ax != 0 ) // jnz 
    goto loc_code_2E25;
  ax = 0x0FA59;
loc_code_2E25:
  *(WORD*)&_data[ds*16+0x2AE5] = ax;
}

void sub_2E29()
{
  ax += si;
  if ( ax < bx ) // jb 
    goto loc_code_2E4F;
  ax -= si;
  cf = (ax < di); // cf-insertion
  ax -= di;
  if ( !cf ) // jnb 
    goto loc_code_2E37;
  ax = 0;
loc_code_2E37:
  if ( ax > bx ) // ja 
    goto loc_code_2E4F;
  dl += cl;
  if ( dl < dh ) // jb 
    goto loc_code_2E4F;
  dl -= cl;
  cf = (dl < ch); // cf-insertion
  dl -= ch;
  if ( !cf ) // jnb 
    goto loc_code_2E49;
  dl = 0;
loc_code_2E49:
  if ( dl > dh ) // ja 
    goto loc_code_2E4F;
  _stc();
  return;
loc_code_2E4F:
  _clc();
}

/*
  unknown_command(); // align 10h
*/
void sub_2E60()
{
  if ( *(WORD*)&_data[ds*16+0x2E8D] < 8 ) // jb 
    goto loc_code_2E68;
  return;
loc_code_2E68:
  if ( _data[ds*16+0x69A] != 0 ) // jnz 
    return;
  *(WORD*)&_data[ds*16+0x2E92] = 0x0FFFF;
  _data[ds*16+0x2E91] = 0x0FF;
  cx = 7;
loc_code_2E7D:
  bx = cx;
  bx--;
  al = _data[ds*16+0x57B];
  cf = (al < *(WORD*)&_data[bx + 0x2BD4]); // cf-insertion
  al -= *(WORD*)&_data[bx + 0x2BD4];
  if ( !cf ) // jnb 
    goto loc_code_2E8B;
  al = ~al;
loc_code_2E8B:
  if ( al > _data[ds*16+0x2E91] ) // ja 
    goto loc_code_2E98;
  _data[ds*16+0x2E91] = al;
  *(WORD*)&_data[ds*16+0x2E92] = bx;
loc_code_2E98:
  if ( --cx )
    goto loc_code_2E7D;
  if ( *(WORD*)&_data[ds*16+0x2E92] != 0x0FFFF ) // jnz 
    goto loc_code_2EA8;
  *(WORD*)&_data[ds*16+0x2E92] = 0;
loc_code_2EA8:
  bx = *(WORD*)&_data[ds*16+0x2E8D];
  si = *(WORD*)&_data[ds*16+0x2E92];
  al = _data[si + 0x2BD4];
  _data[bx + 0x2B6A] = al;
  _data[ds*16+0x2E98] = al;
  ax = *(WORD*)&_data[ds*16+0x579];
  bl <<= 1;
  if ( ax < 0x108 ) // jb 
    goto loc_code_2EC8;
  ax = 0x107;
loc_code_2EC8:
  ax &= 0x0FFC;
  *(WORD*)&_data[bx + 0x2B5A] = ax;
  *(WORD*)&_data[ds*16+0x2E96] = ax;
  cx = 8;
loc_code_2ED5:
  bx = cx;
  bx--;
  if ( bx == *(WORD*)&_data[ds*16+0x2E8D] ) // jz 
    goto loc_code_2F07;
  if ( _data[bx + 0x2B72] == 0 ) // jz 
    goto loc_code_2F07;
  _push(cx);
  dl = _data[bx + 0x2B6A];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x2B5A];
  bx = *(WORD*)&_data[ds*16+0x2E96];
  dh = _data[ds*16+0x2E98];
  si = 0x18;
  di = si;
  cx = 0x0F0F;
  sub_2E29();
  _pop(cx);
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_2F07;
  return;
loc_code_2F07:
  if ( --cx )
    goto loc_code_2ED5;
  sub_11E3();
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_2F16;
  sub_622B();
loc_code_2F16:
  bx = *(WORD*)&_data[ds*16+0x2E8D];
  *(WORD*)&_data[ds*16+0x2E94] = bx;
  _data[bx + 0x2B72] = 1;
  dl = _data[bx + 0x2B6A];
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x2B5A];
  sub_2CB0();
  di = ax;
  si = 0x2AF0;
  ax = 0x0B800;
  es = ax;
  cx = 0x0F03;
  sub_2D9D();
  *(WORD*)&_data[ds*16+0x2E8D] = 0x0FFFF;
  bx = 0;
  ah = 0x0B;
  _int(0x10);
  sub_4E3E();
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_2F59;
  sub_61FA();
loc_code_2F59:
  sub_1145();
  ax = 0x3E8;
  bx = 0x4A5;
  sub_593B();
}

void sub_2F66()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x2E8F] ) // jnz 
    goto loc_code_2F71;
  return;
loc_code_2F71:
  *(WORD*)&_data[ds*16+0x2E8F] = dx;
  if ( *(WORD*)&_data[ds*16+0x2E8D] < 8 ) // jb 
    goto loc_code_2FAC;
  cx = 8;
loc_code_2F7F:
  bx = cx;
  bx--;
  if ( _data[bx + 0x2B72] == 0 ) // jz 
    goto loc_code_2FAA;
  _push(cx);
  dl = _data[bx + 0x2B6A];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x2B5A];
  si = 0x18;
  di = si;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  cx = 0x0E0F;
  sub_2E29();
  _pop(cx);
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_2FB3;
loc_code_2FAA:
  if ( --cx )
    goto loc_code_2F7F;
loc_code_2FAC:
  *(WORD*)&_data[ds*16+0x2E94] = 0x0FFFF;
  return;
loc_code_2FB3:
  bx = cx;
  bx--;
  if ( bx == *(WORD*)&_data[ds*16+0x2E94] ) // jz 
    return;
  _push(bx);
  sub_11E3();
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_2FCA;
  sub_622B();
loc_code_2FCA:
  _pop(bx);
  _data[bx + 0x2B72] = 0;
  dl = _data[bx + 0x2B6A];
  *(WORD*)&_data[ds*16+0x2E8D] = bx;
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x2B5A];
  sub_2CB0();
  di = ax;
  si = 0x2B7A;
  ax = 0x0B800;
  es = ax;
  cx = 0x0F03;
  sub_2D9D();
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_2FFB;
  sub_61FA();
loc_code_2FFB:
  sub_1145();
  bx = 1;
  ah = 0x0B;
  _int(0x10);
  ax = 0x3E8;
  bx = 0x349;
  sub_593B();
}

void sub_300F()
{
  ax = 0;
  bx = 0x2E24;
  sub_2B24();
  _data[ds*16+0x2E8A] = 0x0BF;
  *(WORD*)&_data[ds*16+0x2E8B] = 0;
loc_code_3022:
  *(WORD*)&_data[ds*16+0x2E88] = 0x20;
loc_code_3028:
  bx = 0;
  if ( _data[ds*16+0x2E8A] == 0x0BF ) // jz 
    goto loc_code_3039;
  sub_2DFD();
  bl = dl;
  bl &= 2;
loc_code_3039:
  cx = *(WORD*)&_data[ds*16+0x2E88];
  dl = _data[ds*16+0x2E8A];
  _push(bx);
  sub_30E3();
  _pop(bx);
  si = *(WORD*)&_data[ds*16+0x2E8B];
  ax = *(WORD*)&_data[ds*16+0x2E88];
  cl = 4;
  ax >>= cl;
  cf = (ax < 2); // cf-insertion
  ax -= 2;
  if ( !cf ) // jnb 
    goto loc_code_3058;
  ax = 0;
loc_code_3058:
  if ( ax < 0x12 ) // jb 
    goto loc_code_3060;
  ax = 0x11;
loc_code_3060:
  dl = _data[si + 0x2BDB];
  dh = 0;
  ax += dx;
  si = ax;
  _data[si + 0x2BE2] = bl;
  *(WORD*)&_data[ds*16+0x2E88] += 0x10;
  if ( *(WORD*)&_data[ds*16+0x2E88] < 0x111 ) // jb 
    goto loc_code_3028;
  (*(WORD*)&_data[ds*16+0x2E8B])++;
  _data[ds*16+0x2E8A] -= 0x18;
  if ( _data[ds*16+0x2E8A] >= 0x2F ) // jnb 
    goto loc_code_3022;
  ax = 0x0FFFF;
  *(WORD*)&_data[ds*16+0x2E8D] = ax;
  *(WORD*)&_data[ds*16+0x2E94] = ax;
  ax = 0;
  *(WORD*)&_data[ds*16+0x2B72] = ax;
  *(WORD*)&_data[ds*16+0x2B74] = ax;
  *(WORD*)&_data[ds*16+0x2B76] = ax;
  *(WORD*)&_data[ds*16+0x2B78] = ax;
  cx = *(WORD*)&_data[ds*16+0x414];
  if ( cx != 0 ) // jnz 
    goto loc_code_30B0;
  cx++;
  *(WORD*)&_data[ds*16+0x414] = cx;
loc_code_30B0:
  if ( cx <= 8 ) // jbe 
    goto loc_code_30B8;
  cx = 8;
loc_code_30B8:
  bx = cx;
  bx--;
  _data[bx + 0x2B72] = 1;
  dl = 0x0B0;
  _data[bx + 0x2B6A] = dl;
  _push(cx);
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x2B4A];
  *(WORD*)&_data[bx + 0x2B5A] = cx;
  sub_2CB0();
  di = ax;
  si = 0x2AF0;
  cx = 0x0F03;
  sub_2D9D();
  _pop(cx);
  if ( --cx )
    goto loc_code_30B8;
}

void sub_30E3()
{
  _push(bx);
  sub_2CB0();
  di = ax;
  ax = 0x0B800;
  es = ax;
  _pop(bx);
  si = *(WORD*)&_data[bx + 0x2E20];
  cx = 0x802;
  sub_2D9D();
}

void sub_30FA()
{
  al = _data[ds*16+0x57B];
  al -= 5;
  al &= 0x0F8;
  cx = 7;
loc_code_3104:
  bx = cx;
  bx--;
  if ( al == _data[bx + 0x2BD4] ) // jz 
    goto loc_code_3111;
  if ( --cx )
    goto loc_code_3104;
  goto loc_code_314D;
loc_code_3111:
  ch = al;
  ax = *(WORD*)&_data[ds*16+0x579];
  ax += 7;
  cl = 4;
  ax >>= cl;
  cf = (ax < 2); // cf-insertion
  ax -= 2;
  if ( !cf ) // jnb 
    goto loc_code_3124;
  ax = 0;
loc_code_3124:
  if ( ax < 0x12 ) // jb 
    goto loc_code_312C;
  ax = 0x11;
loc_code_312C:
  dl = _data[bx + 0x2BDB];
  dh = 0;
  ax += dx;
  si = ax;
  if ( _data[si + 0x2BE2] != 0 ) // jnz 
    goto loc_code_314D;
  ch += 5;
  _data[ds*16+0x57B] = ch;
  ch += 0x32;
  _data[ds*16+0x57C] = ch;
  _stc();
  return;
loc_code_314D:
  _clc();
}

/*
  unknown_command(); // align 2
*/
void sub_3150()
{
  ah = 0;
  _int(0x1A);
  bx = *(WORD*)&_data[ds*16+4];
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x32F2];
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x328C];
  if ( ax >= cx ) // jnb 
    goto loc_code_3169;
  return;
loc_code_3169:
  *(WORD*)&_data[ds*16+0x328C] = dx;
  sub_33BA();
  if ( unknown_condition() ) // jb cf=1
    return;
  sub_21E0();
  if ( unknown_condition() ) // jb cf=1
    return;
  (_data[ds*16+0x32EA])++;
  sub_2DFD();
  al = _data[ds*16+0x32EA];
  al &= dl;
  *(WORD*)&_data[ds*16+0x32EB] ^= al;
  ax = *(WORD*)&_data[ds*16+0x327D];
  ax -= *(WORD*)&_data[ds*16+0x579];
  dl = 0x0FF;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3196;
  ax = ~ax;
  dl = 1;
loc_code_3196:
  _data[ds*16+0x32ED] = dl;
  bl = _data[ds*16+0x327F];
  bl += 0x14;
  bl -= *(WORD*)&_data[ds*16+0x57B];
  dl = 0x0FF;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_31AD;
  bl = ~bl;
  dl = 1;
loc_code_31AD:
  _data[ds*16+0x32EE] = dl;
  ax >>= 1;
  ax >>= 1;
  bl >>= 1;
  al += bl;
  _data[ds*16+0x32EC] = al;
  bx = *(WORD*)&_data[ds*16+0x328A];
  if ( bx < 0x27 ) // jb 
    goto loc_code_31CC;
  bx = 0x26;
  *(WORD*)&_data[ds*16+0x328A] = bx;
loc_code_31CC:
  if ( _data[bx + 0x328E] != 0 ) // jnz 
    goto loc_code_324B;
  (*(WORD*)&_data[ds*16+0x328A])--;
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x410];
  cl = 3;
  dx >>= cl;
  al = _data[ds*16+0x32EC];
  cf = (al < dl); // cf-insertion
  al -= dl;
  if ( !cf ) // jnb 
    goto loc_code_31EC;
  al = 0;
loc_code_31EC:
  if ( al < _data[ds*16+0x32EB] ) // jb 
    goto loc_code_3212;
  _data[ds*16+0x3281] = 1;
  sub_2DFD();
  if ( dl == 0 ) // jz 
    goto loc_code_320B;
  if ( dl > 7 ) // ja 
    goto loc_code_320F;
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_320B;
  dl = 0x0FF;
loc_code_320B:
  _data[ds*16+0x3280] = dl;
loc_code_320F:
  goto loc_code_32AC;
loc_code_3212:
  al = _data[ds*16+0x32EB];
  al &= 0x2F;
  if ( al ) // jnz 
    goto loc_code_3238;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_3223;
  dl = 0x0FF;
loc_code_3223:
  _data[ds*16+0x3280] = dl;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_3231;
  dl = 0x0FF;
loc_code_3231:
  _data[ds*16+0x3281] = dl;
  goto loc_code_32AC;
loc_code_3238:
  al &= 7;
  if ( al ) // jnz 
    goto loc_code_32AC;
  al = _data[ds*16+0x32ED];
  _data[ds*16+0x3280] = al;
  al = _data[ds*16+0x32EE];
  _data[ds*16+0x3281] = al;
  goto loc_code_32AC;
loc_code_324B:
  _data[ds*16+0x3281] = 1;
  ax = bx;
  cl = 3;
  ax <<= cl;
  if ( *(WORD*)&_data[ds*16+0x327D] == ax ) // jz 
    goto loc_code_3269;
  dl = 1;
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_3262;
  dl = 0x0FF;
loc_code_3262:
  _data[ds*16+0x3280] = dl;
  goto loc_code_32AC;
loc_code_3269:
  _data[ds*16+0x3280] = 0;
  if ( _data[ds*16+0x327F] != 0x0A5 ) // jnz 
    goto loc_code_32AC;
  _data[ds*16+0x3281] = 0;
  if ( *(WORD*)&_data[ds*16+0x327A] == 6 ) // jz 
    goto loc_code_3288;
  if ( *(WORD*)&_data[ds*16+0x327A] != 0x12 ) // jnz 
    goto loc_code_32AC;
loc_code_3288:
  _push(bx);
  si = 0x31E8;
  di = *(WORD*)&_data[ds*16+0x3282];
  cx = 0x1E02;
  ax = 0x0B800;
  es = ax;
  sub_2D9D();
  _pop(bx);
  _data[bx + 0x328E]--;
  al = _data[bx + 0x328E];
  sub_347F();
  _data[ds*16+0x3286] = 1;
loc_code_32AC:
  cx = *(WORD*)&_data[ds*16+0x327D];
  dl = _data[ds*16+0x327F];
  *(WORD*)&_data[ds*16+0x32EF] = cx;
  _data[ds*16+0x32F1] = dl;
  if ( _data[ds*16+0x3280] < 1 ) // jb 
    goto loc_code_32DA;
  if ( unknown_condition() ) // jnz 
    goto loc_code_32D3;
  cx += 8;
  if ( cx < 0x131 ) // jb 
    goto loc_code_32DA;
  cx = 0x130;
  goto loc_code_32DA;
loc_code_32D3:
  cf = (cx < 8); // cf-insertion
  cx -= 8;
  if ( !cf ) // jnb 
    goto loc_code_32DA;
  cx = 0;
loc_code_32DA:
  cx &= 0x0FFF8;
  *(WORD*)&_data[ds*16+0x327D] = cx;
  if ( _data[ds*16+0x3281] < 1 ) // jb 
    goto loc_code_32FE;
  if ( unknown_condition() ) // jnz 
    goto loc_code_32F7;
  dl += 2;
  if ( dl < 0x0A6 ) // jb 
    goto loc_code_32FE;
  dl = 0x0A5;
  goto loc_code_32FE;
loc_code_32F7:
  cf = (dl < 2); // cf-insertion
  dl -= 2;
  if ( !cf ) // jnb 
    goto loc_code_32FE;
  dl = 0;
loc_code_32FE:
  _data[ds*16+0x327F] = dl;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x3284] = ax;
  sub_33BA();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3328;
loc_code_330D:
  _data[ds*16+0x3280] = 0;
  _data[ds*16+0x3281] = 0;
  cx = *(WORD*)&_data[ds*16+0x32EF];
  *(WORD*)&_data[ds*16+0x327D] = cx;
  dl = _data[ds*16+0x32F1];
  _data[ds*16+0x327F] = dl;
  return;
loc_code_3328:
  sub_21E0();
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_330D;
  sub_33A0();
  *(WORD*)&_data[ds*16+0x327A] += 2;
  sub_3339();
}

void sub_3339()
{
sub_code_3339:
  bx = *(WORD*)&_data[ds*16+0x327A];
  ax = *(WORD*)&_data[bx + 0x3260];
  if ( ax != 0 ) // jnz 
    goto loc_code_334B;
  *(WORD*)&_data[ds*16+0x327A] = ax;
  goto sub_code_3339;
loc_code_334B:
  si = ax;
  di = *(WORD*)&_data[ds*16+0x3284];
  *(WORD*)&_data[ds*16+0x3282] = di;
  bp = 0x31E8;
  ax = 0x0B800;
  es = ax;
  cx = 0x1E02;
  _data[ds*16+0x3286] = 0;
  _cld();
  _data[ds*16+0x3289] = ch;
  ch = 0;
  *(WORD*)&_data[ds*16+0x3287] = cx;
loc_code_3370:
  cx = *(WORD*)&_data[ds*16+0x3287];
loc_code_3374:
  bx = *(WORD*)&_data[es*16+di];
  *(WORD*)&_data[ds*16+bp+0] = bx;
  _lodsw();
  ax |= bx;
  _stosw();
  bp += 2;
  if ( --cx )
    goto loc_code_3374;
  di -= *(WORD*)&_data[ds*16+0x3287];
  di -= *(WORD*)&_data[ds*16+0x3287];
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_3399;
  di += 0x50;
loc_code_3399:
  (_data[ds*16+0x3289])--;
  if ( _data[ds*16+0x3289] ) // jnz 
    goto loc_code_3370;
}

void sub_33A0()
{
  if ( _data[ds*16+0x3286] != 0 ) // jnz 
    return;
  ax = 0x0B800;
  es = ax;
  si = 0x31E8;
  di = *(WORD*)&_data[ds*16+0x3282];
  cx = 0x1E02;
  sub_2D9D();
}

void sub_33BA()
{
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    goto loc_code_3403;
  if ( *(WORD*)&_data[ds*16+4] != 6 ) // jnz 
    goto loc_code_33D3;
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    goto loc_code_33D3;
  sub_47B0();
  return;
loc_code_33D3:
  ax = *(WORD*)&_data[ds*16+0x327D];
  dl = _data[ds*16+0x327F];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E1E;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3403;
  if ( *(WORD*)&_data[ds*16+4] != 4 ) // jnz 
    goto loc_code_33FE;
  if ( _data[ds*16+0x39E1] != 0 ) // jnz 
    goto loc_code_3401;
loc_code_33FE:
  sub_872();
loc_code_3401:
  _stc();
  return;
loc_code_3403:
  _clc();
}

void sub_3405()
{
  _cld();
  ax = 0;
  _push(ds);
  _pop(es);
  di = 0x328E;
  cx = 0x14;
  _rep_stosw();
  *(WORD*)&_data[ds*16+0x32B6] = 0x0FF;
  *(WORD*)&_data[ds*16+0x327A] = 0;
  *(WORD*)&_data[ds*16+0x327D] = 0;
  _data[ds*16+0x327F] = 0x0A0;
  _data[ds*16+0x3286] = 1;
  _data[ds*16+0x3280] = 0;
  _data[ds*16+0x3281] = 0;
  sub_2DFD();
  _data[ds*16+0x32EB] = dl;
  _data[ds*16+0x32EA] = 0x6C;
}

void sub_3445()
{
  if ( _data[ds*16+0x57B] < 0x0B4 ) // jb 
    return;
  if ( _data[ds*16+0x56E] == 0 ) // jz 
    return;
  ax = *(WORD*)&_data[ds*16+0x579];
  ax += 0x0C;
  cl = 3;
  ax >>= cl;
  if ( ax > 0x27 ) // ja 
    return;
  if ( ax == *(WORD*)&_data[ds*16+0x32B6] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x32B6] = ax;
  bx = ax;
  al = _data[bx + 0x328E];
  if ( al >= 4 ) // jnb 
    return;
  al++;
  _data[bx + 0x328E] = al;
  sub_347F();
}

void sub_347F()
{
  ah = 0x0A;
  ax = (WORD)ah * (WORD)al;

  ax += 0x32B8;
  si = ax;
  di = bx;
  di <<= 1;
  di += 0x1E00;
  ax = 0x0B800;
  es = ax;
  cx = 0x501;
  sub_2D9D();
}

/*
  unknown_command(); // align 8
*/
void sub_34A0()
{
  *(WORD*)&_data[ds*16+0x3511] = 0;
  _data[ds*16+0x351B] = 0;
loc_code_34AB:
  bx = *(WORD*)&_data[ds*16+0x3511];
  if ( _data[bx + 0x34A7] == 0 ) // jz 
    goto loc_code_34B9;
loc_code_34B6:
  goto loc_code_35AD;
loc_code_34B9:
  si = bx;
  si <<= 1;
  ax = *(WORD*)&_data[si + 0x3447];
  dl = _data[bx + 0x3477];
  di = 0;
  if ( bx < 0x0C ) // jb 
    goto loc_code_34D0;
  di = 2;
loc_code_34D0:
  si = *(WORD*)&_data[di + 0x3513];
  cx = *(WORD*)&_data[di + 0x3517];
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  ch = 0x0E;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_34B6;
  bx = *(WORD*)&_data[ds*16+0x3511];
  if ( bx < 0x0C ) // jb 
    goto loc_code_356F;
  if ( _data[ds*16+0x553] != 0 ) // jnz 
    goto loc_code_356F;
  if ( _data[ds*16+0x5F3] != 0 ) // jnz 
    goto loc_code_356F;
  _data[ds*16+0x552] = 1;
  cx = *(WORD*)&_data[ds*16+0x579];
  cf = (cx < 8); // cf-insertion
  cx -= 8;
  if ( !cf ) // jnb 
    goto loc_code_3511;
  cx = 0;
loc_code_3511:
  if ( cx < 0x117 ) // jb 
    goto loc_code_351A;
  cx = 0x116;
loc_code_351A:
  dl = _data[ds*16+0x57B];
  if ( dl < 0x0B5 ) // jb 
    goto loc_code_3525;
  dl = 0x0B4;
loc_code_3525:
  sub_2CB0();
  di = ax;
  si = 0x3350;
  ax = 0x0B800;
  es = ax;
  cx = 0x1205;
  sub_2D9D();
  sub_5797();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x3509] = dx;
loc_code_3543:
  _push(dx);
loc_code_3544:
  sub_57A6();
  if ( !sub_13D8() ) // jz 
    goto loc_code_3544;
  sub_57A6();
  _pop(dx);
  bx = 1;
  if ( dl & 1 ) // jnz 
    goto loc_code_355A;
  bl = 0x0F;
loc_code_355A:
  ah = 0x0B;
  _int(0x10);
  sub_57A6();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x3509];
  if ( dx < 0x0D ) // jb 
    goto loc_code_3543;
  return;
loc_code_356F:
  (_data[ds*16+0x351B])++;
  ax = 0x5DC;
  bx = 0x425;
  sub_593B();
  if ( _data[ds*16+0x351B] != 1 ) // jnz 
    goto loc_code_3586;
  sub_11E3();
loc_code_3586:
  bx = *(WORD*)&_data[ds*16+0x3511];
  sub_37C1();
  bx = *(WORD*)&_data[ds*16+0x3511];
  _data[bx + 0x34A7] = 1;
  if ( bx >= 0x0C ) // jnb 
    goto loc_code_35AD;
  (_data[ds*16+0x3410])--;
  if ( _data[ds*16+0x3410] ) // jnz 
    goto loc_code_35AD;
  if ( _data[ds*16+0x5F3] != 0 ) // jnz 
    goto loc_code_35AD;
  _data[ds*16+0x553] = 1;
loc_code_35AD:
  (*(WORD*)&_data[ds*16+0x3511])++;
  if ( *(WORD*)&_data[ds*16+0x3511] >= 0x18 ) // jnb 
    goto loc_code_35BB;
  goto loc_code_34AB;
loc_code_35BB:
  if ( _data[ds*16+0x351B] == 0 ) // jz 
    goto loc_code_35C7;
  sub_363D();
  _stc();
  return;
loc_code_35C7:
  _clc();
}

void sub_35C9()
{
  *(WORD*)&_data[ds*16+0x3411] = 0;
  *(WORD*)&_data[ds*16+0x3415] = 0;
  _data[ds*16+0x3410] = 0x0C;
  cx = 0x18;
loc_code_35DD:
  bx = cx;
  bx--;
  _data[bx + 0x348F] = 1;
  _data[bx + 0x34A7] = 0;
  al = _data[bx + 0x34F1];
  _data[bx + 0x3477] = al;
  _data[bx + 0x342F] = 1;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_3601;
  dl = ~dl;
loc_code_3601:
  _data[bx + 0x3417] = dl;
  bx <<= 1;
  sub_2DFD();
  dh = 0;
  *(WORD*)&_data[bx + 0x3447] = dx;
  if ( --cx )
    goto loc_code_35DD;
  bx = *(WORD*)&_data[ds*16+8];
  cl = _data[bx + 0x351C];
  ch = 0;
loc_code_361C:
  sub_2DFD();
  dl &= 0x0F;
  if ( dl >= 0x0C ) // jnb 
    goto loc_code_361C;
  bl = dl;
  bl += 0x0C;
  bh = 0;
  if ( _data[bx + 0x34A7] != 0 ) // jnz 
    goto loc_code_361C;
  _data[bx + 0x34A7] = 1;
  if ( --cx )
    goto loc_code_361C;
}

void sub_363D()
{
sub_code_363D:
  cx = 0x0C;
loc_code_3640:
  bx = cx;
  bx += 0x0B;
  if ( _data[bx + 0x34A7] == 0 ) // jz 
    goto loc_code_3672;
  ax = 0;
  dl = 1;
  _data[bx + 0x34A7] = al;
  if ( *(WORD*)&_data[ds*16+0x579] > 0x0A0 ) // ja 
    goto loc_code_3661;
  ax = 0x12E;
  dl = 0x0FF;
loc_code_3661:
  _data[bx + 0x3417] = dl;
  bl <<= 1;
  *(WORD*)&_data[bx + 0x3447] = ax;
  (_data[ds*16+0x351B])--;
  if ( _data[ds*16+0x351B] ) // jnz 
    goto sub_code_363D;
  return;
loc_code_3672:
  if ( --cx )
    goto loc_code_3640;
}

void sub_3675()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x3509] ) // jnz 
    goto loc_code_3680;
  return;
loc_code_3680:
  *(WORD*)&_data[ds*16+0x350B] = dx;
  (*(WORD*)&_data[ds*16+0x3415])++;
  bx = *(WORD*)&_data[ds*16+0x3415];
  if ( bx < 0x18 ) // jb 
    goto loc_code_36A4;
  bx = 0;
  *(WORD*)&_data[ds*16+0x3415] = bx;
  *(WORD*)&_data[ds*16+0x3411] ^= 0x0C;
  *(WORD*)&_data[ds*16+0x3413] += 8;
  goto loc_code_36B7;
loc_code_36A4:
  if ( bx != 0x0C ) // jnz 
    goto loc_code_36BD;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_36B7;
  if ( _data[ds*16+0x57B] < 0x30 ) // jb 
    goto loc_code_36BD;
loc_code_36B7:
  ax = *(WORD*)&_data[ds*16+0x350B];
  *(WORD*)&_data[ds*16+0x3509] = ax;
loc_code_36BD:
  si = bx;
  si <<= 1;
  if ( _data[bx + 0x34A7] != 0 ) // jnz 
    return;
  sub_2DFD();
  if ( dl > 0x10 ) // ja 
    goto loc_code_36E9;
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_36D7;
  dl = ~dl;
loc_code_36D7:
  _data[bx + 0x3417] = dl;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_36E5;
  dl = ~dl;
loc_code_36E5:
  _data[bx + 0x342F] = dl;
loc_code_36E9:
  cx = 4;
  if ( bx < 0x0C ) // jb 
    goto loc_code_36F3;
  cl >>= 1;
loc_code_36F3:
  ax = *(WORD*)&_data[si + 0x3447];
  if ( _data[bx + 0x3417] == 1 ) // jz 
    goto loc_code_370B;
  cf = (ax < cx); // cf-insertion
  ax -= cx;
  if ( !cf ) // jnb 
    goto loc_code_371A;
  ax = 0;
  _data[bx + 0x3417] = 1;
  goto loc_code_371A;
loc_code_370B:
  ax += cx;
  if ( ax < 0x12F ) // jb 
    goto loc_code_371A;
  ax = 0x12E;
  _data[bx + 0x3417] = 0x0FF;
loc_code_371A:
  *(WORD*)&_data[si + 0x3447] = ax;
  al = _data[bx + 0x3477];
  if ( _data[bx + 0x342F] == 1 ) // jz 
    goto loc_code_373C;
  al--;
  if ( al >= _data[bx + 0x34F1] ) // jnb 
    goto loc_code_3750;
  al = _data[bx + 0x34F1];
  _data[bx + 0x342F] = 1;
  goto loc_code_3750;
loc_code_373C:
  al++;
  dl = _data[bx + 0x34F1];
  dl += 0x18;
  if ( al <= dl ) // jbe 
    goto loc_code_3750;
  al = dl;
  _data[bx + 0x342F] = 0x0FF;
loc_code_3750:
  _data[bx + 0x3477] = al;
  dl = al;
  cx = *(WORD*)&_data[si + 0x3447];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x34EF] = ax;
  bx = *(WORD*)&_data[ds*16+0x3415];
  sub_37C1();
  bx = *(WORD*)&_data[ds*16+0x3415];
  si = bx;
  si <<= 1;
  di = *(WORD*)&_data[ds*16+0x34EF];
  *(WORD*)&_data[si + 0x34BF] = di;
  _data[bx + 0x348F] = 0;
  ax = 0x0B800;
  es = ax;
  if ( bx < 0x0C ) // jb 
    goto loc_code_379F;
  si = bx;
  cl = 3;
  si <<= cl;
  si += *(WORD*)&_data[ds*16+0x3413];
  si &= 0x18;
  si += 0x3330;
  cx = 0x202;
  sub_2D9D();
  return;
loc_code_379F:
  si = *(WORD*)&_data[ds*16+0x3411];
  if ( bl & 1 ) // jnz 
    goto loc_code_37AC;
  si ^= 0x0C;
loc_code_37AC:
  if ( _data[bx + 0x3417] == 1 ) // jz 
    goto loc_code_37B6;
  si += 0x18;
loc_code_37B6:
  si += 0x3300;
  cx = 0x601;
  sub_2D9D();
}

void sub_37C1()
{
  if ( _data[bx + 0x348F] != 0 ) // jnz 
    return;
  bx <<= 1;
  si = 0x3404;
  di = *(WORD*)&_data[bx + 0x34BF];
  ax = 0x0B800;
  es = ax;
  cx = 0x601;
  if ( bx < 0x18 ) // jb 
    goto loc_code_37E1;
  cx = 0x202;
loc_code_37E1:
  sub_2D9D();
}

void sub_37E5()
{
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x350F];
  if ( ax < 8 ) // jb 
    return;
  (*(WORD*)&_data[ds*16+0x350D])++;
  bx = *(WORD*)&_data[ds*16+0x350D];
  if ( bx < 0x28 ) // jb 
    goto loc_code_380B;
  bx = 0;
  *(WORD*)&_data[ds*16+0x350D] = bx;
  *(WORD*)&_data[ds*16+0x350F] = dx;
loc_code_380B:
  di = bx;
  di <<= 1;
  if ( _data[ds*16+0x57B] > 7 ) // ja 
    goto loc_code_3829;
  ax = *(WORD*)&_data[ds*16+0x579];
  cl = 2;
  ax >>= cl;
  ax++;
  cf = (ax < di); // cf-insertion
  ax -= di;
  if ( !cf ) // jnb 
    goto loc_code_3824;
  ax = ~ax;
loc_code_3824:
  if ( ax < 4 ) // jb 
    return;
loc_code_3829:
  di += 0x0A0;
  al = _data[bx + 0x2656];
  al += 8;
  _data[bx + 0x2656] = al;
  ax &= 0x18;
  ax += 0x2020;
  si = ax;
  ax = 0x0B800;
  es = ax;
  cx = 0x401;
  sub_2D9D();
}

/*
  unknown_command(); // align 8
*/
void sub_3850()
{
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x35DA];
  if ( ax >= 6 ) // jnb 
    goto loc_code_3860;
  return;
loc_code_3860:
  *(WORD*)&_data[ds*16+0x35DA] = dx;
  *(WORD*)&_data[ds*16+0x35D8] += 2;
  bx = *(WORD*)&_data[ds*16+0x35D8];
  bx &= 6;
  si = *(WORD*)&_data[bx + 0x35D0];
  di = 0x15C9;
  ax = 0x0B800;
  es = ax;
  cx = 0x0A02;
  sub_2D9D();
  ax = 0x0E4;
  dl = 0x8A;
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E0A;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x554] = 1;
}

/*
  unknown_command(); // align 10h
*/
void sub_38B0()
{
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_38BA;
  goto loc_code_38D3;
loc_code_38BA:
  (*(WORD*)&_data[ds*16+0x414])++;
  _data[ds*16+0x418] = 1;
  dx = 0x0AAAA;
  sub_3A96();
  ax = 0;
  _data[ds*16+0x369F] = 0;
  sub_3AAC();
loc_code_38D3:
  ah = 0;
  _int(0x1A);
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_38EF;
  dx -= *(WORD*)&_data[ds*16+0x412];
  ax = 0x2A30;
  cf = (ax < dx); // cf-insertion
  ax -= dx;
  if ( !cf ) // jnb 
    goto loc_code_38EB;
  ax = 0;
loc_code_38EB:
  ax >>= 1;
  goto loc_code_390E;
loc_code_38EF:
  dx -= *(WORD*)&_data[ds*16+0x410];
  ax = 0x546;
  if ( *(WORD*)&_data[ds*16+6] != 6 ) // jnz 
    goto loc_code_38FF;
  ax <<= 1;
loc_code_38FF:
  cf = (ax < dx); // cf-insertion
  ax -= dx;
  if ( !cf ) // jnb 
    goto loc_code_3905;
  ax = 0;
loc_code_3905:
  if ( *(WORD*)&_data[ds*16+6] == 6 ) // jz 
    goto loc_code_390E;
  ax <<= 1;
loc_code_390E:
  *(WORD*)&_data[ds*16+0x3697] = ax;
  sub_3AF4();
  bx = *(WORD*)&_data[ds*16+6];
  bl <<= 1;
  si = *(WORD*)&_data[bx + 0x36CC];
  di = 0x368D;
  sub_271E();
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_396E;
  bx = *(WORD*)&_data[ds*16+8];
  bl <<= 1;
  ax = bx;
  cx = *(WORD*)&_data[bx + 0x36DC];
  if ( *(WORD*)&_data[ds*16+0x2E8D] >= 8 ) // jnb 
    goto loc_code_3943;
  cx <<= 1;
  ax += 0x10;
loc_code_3943:
  *(WORD*)&_data[ds*16+0x370C] = ax;
loc_code_3946:
  si = 0x368D;
  di = 0x1F82;
  _push(cx);
  sub_271E();
  _pop(cx);
  if ( --cx )
    goto loc_code_3946;
  sub_39FA();
  _data[ds*16+0x369E] = 0x38;
  _data[ds*16+0x3699] = 1;
  *(WORD*)&_data[ds*16+0x3722] = 0x44;
  sub_3A3A();
  sub_3A6C();
  goto loc_code_39A7;
loc_code_396E:
  si = 0x368D;
  di = 0x1F82;
  sub_271E();
  _data[ds*16+0x3699] = 2;
  *(WORD*)&_data[ds*16+0x3722] = 0x1E;
  dx = 0x0FFFF;
  sub_3A96();
  ax = 0x0A8C;
  ax -= *(WORD*)&_data[ds*16+0x3697];
  cl = 4;
  ax >>= cl;
  al &= 0x0F0;
  _data[ds*16+0x369E] = al;
  ah = 0x28;
  ax = (WORD)ah * (WORD)al;

  _data[ds*16+0x369F] = 1;
  sub_3AAC();
  sub_3A3A();
loc_code_39A7:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x3695] = dx;
loc_code_39AF:
  if ( *(WORD*)&_data[ds*16+6] != 7 ) // jnz 
    goto loc_code_39BB;
  sub_5B63();
  goto loc_code_39BE;
loc_code_39BB:
  sub_5835();
loc_code_39BE:
  sub_3A1C();
  dx -= *(WORD*)&_data[ds*16+0x3695];
  if ( dx < *(WORD*)&_data[ds*16+0x3722] ) // jb 
    goto loc_code_39AF;
  bx = 0;
  ah = 0x0B;
  _int(0x10);
  if ( *(WORD*)&_data[ds*16+6] == 7 ) // jz 
    goto loc_code_39DC;
  sub_5B21();
  return;
loc_code_39DC:
  ax = 0x0B800;
  es = ax;
  si = 0x0E;
  di = 0x8E4;
  cx = 0x804;
  sub_2D9D();
  si = 0x4E;
  di = 0x0C94;
  cx = 0x814;
  sub_2D9D();
}

void sub_39FA()
{
  _push(ds);
  _pop(es);
  ax = 0x0B800;
  ds = ax;
  cx = 0x804;
  di = 0x0E;
  si = 0x8E4;
  sub_2DCA();
  cx = 0x814;
  di = 0x4E;
  si = 0x0C94;
  sub_2DCA();
  _push(es);
  _pop(ds);
}

void sub_3A1C()
{
  ah = 0;
  _int(0x1A);
  _push(dx);
loc_code_3A21:
  if ( !sub_13D8() ) // jz 
    goto loc_code_3A21;
  _pop(dx);
  _push(dx);
  bx = 0;
  if ( dx & 4 ) // jnz 
    goto loc_code_3A34;
  bl = _data[ds*16+0x3699];
loc_code_3A34:
  ah = 0x0B;
  _int(0x10);
  _pop(dx);
}

void sub_3A3A()
{
  ah = 2;
  dh = _data[ds*16+0x369E];
  cl = 3;
  dh >>= cl;
  dl = 0x12;
  bh = 0;
  _int(0x10);
  *(WORD*)&_data[ds*16+0x36A0] = 3;
loc_code_3A50:
  bx = *(WORD*)&_data[ds*16+0x36A0];
  al = _data[bx + 0x368D];
  al += 0x30;
  ah = 0x0E;
  bl = 3;
  _int(0x10);
  (*(WORD*)&_data[ds*16+0x36A0])++;
  if ( *(WORD*)&_data[ds*16+0x36A0] < 7 ) // jb 
    goto loc_code_3A50;
}

void sub_3A6C()
{
  ah = 2;
  dl = 0x0A;
  dh = dl;
  bx = 0;
  _int(0x10);
  bx = *(WORD*)&_data[ds*16+0x370C];
  ax = *(WORD*)&_data[bx + 0x36EC];
  *(WORD*)&_data[ds*16+0x3720] = ax;
  bx = 0;
loc_code_3A83:
  ah = 0x0E;
  al = _data[bx + 0x370E];
  _push(bx);
  bl = 3;
  _int(0x10);
  _pop(bx);
  bx++;
  if ( bx < 0x14 ) // jb 
    goto loc_code_3A83;
}

void sub_3A96()
{
  _cld();
  ax = seg_data;
  es = ax;
  di = 0x0E;
  si = 0x35E0;
  cx = 0x1E;
loc_code_3AA5:
  _lodsw();
  ax &= dx;
  _stosw();
  if ( --cx )
    goto loc_code_3AA5;
}

void sub_3AAC()
{
  *(WORD*)&_data[ds*16+0x369A] = ax;
  ax = 0x0B800;
  es = ax;
  sub_5829();
  ax = 0x1B80;
loc_code_3ABA:
  bx = 0x361C;
  *(WORD*)&_data[ds*16+0x369C] = ax;
  sub_2B24();
  if ( _data[ds*16+0x369F] == 0 ) // jz 
    goto loc_code_3AE2;
  sub_5869();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x3695] = dx;
loc_code_3AD5:
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x3695];
  if ( dx < 2 ) // jb 
    goto loc_code_3AD5;
loc_code_3AE2:
  ax = *(WORD*)&_data[ds*16+0x369C];
  cf = (ax < 0x280); // cf-insertion
  ax -= 0x280;
  if ( cf ) // jb 
    goto loc_code_3AF0;
  if ( ax >= *(WORD*)&_data[ds*16+0x369A] ) // jnb 
    goto loc_code_3ABA;
loc_code_3AF0:
  sub_5B21();
}

void sub_3AF4()
{
  *(WORD*)&_data[ds*16+0x368B] = ax;
  ax = 0;
  *(WORD*)&_data[ds*16+0x368D] = ax;
  *(WORD*)&_data[ds*16+0x368F] = ax;
  *(WORD*)&_data[ds*16+0x3691] = ax;
  *(WORD*)&_data[ds*16+0x3693] = ax;
  bx = 0x3684;
  dx = 0x1000;
loc_code_3B0B:
  if ( !(*(WORD*)&_data[ds*16+0x368B] & dx) ) // jz 
    goto loc_code_3B19;
  si = bx;
  di = 0x368D;
  sub_271E();
loc_code_3B19:
  bx -= 7;
  dx >>= 1;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3B0B;
}

/*
  unknown_command(); // align 10h
*/
void sub_3B30()
{
  _data[ds*16+0x37AF] = 3;
  ax = 1;
  *(WORD*)&_data[ds*16+0x37B0] = ax;
  *(WORD*)&_data[ds*16+0x37B2] = ax;
  *(WORD*)&_data[ds*16+0x37B4] = ax;
}

void sub_3B42()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x37B8] ) // jnz 
    goto loc_code_3B4D;
  return;
loc_code_3B4D:
  *(WORD*)&_data[ds*16+0x37B8] = dx;
  *(WORD*)&_data[ds*16+0x37B6] = 4;
loc_code_3B57:
  bx = *(WORD*)&_data[ds*16+0x37B6];
  if ( *(WORD*)&_data[bx + 0x37B0] == 0 ) // jz 
    goto loc_code_3B9B;
  ax = *(WORD*)&_data[bx + 0x37A3];
  dl = 0x18;
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E10;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3B9B;
  ax = 0x0C00;
  bx = 0x8FD;
  sub_593B();
  sub_11E3();
  sub_3E38();
  bx = *(WORD*)&_data[ds*16+0x37B6];
  sub_3BA3();
  sub_1124();
  sub_3E14();
  return;
loc_code_3B9B:
  cf = (*(WORD*)&_data[ds*16+0x37B6] < 2); // cf-insertion
  *(WORD*)&_data[ds*16+0x37B6] -= 2;
  if ( !cf ) // jnb 
    goto loc_code_3B57;
}

void sub_3BA3()
{
  *(WORD*)&_data[bx + 0x37B0] = 0;
  _push(ds);
  _pop(es);
  _cld();
  ax = 0x0AAAA;
  di = 0x0E;
  si = di;
  cx = 0x20;
  _rep_stosw();
  di = *(WORD*)&_data[bx + 0x37A9];
  ax = 0x0B800;
  es = ax;
  cx = 0x1002;
  sub_2D9D();
  (_data[ds*16+0x37AF])--;
  if ( _data[ds*16+0x37AF] ) // jnz 
    return;
  if ( _data[ds*16+0x552] != 0 ) // jnz 
    return;
  _data[ds*16+0x553] = 1;
}

void sub_3BDB()
{
  ax = 0x0B800;
  es = ax;
  *(WORD*)&_data[ds*16+0x37A0] = 0x66A;
  cx = 0x10;
loc_code_3BE9:
  ax = 0;
  bx = ax;
loc_code_3BED:
  _data[ds*16+0x37A2] = al;
  ah = 0;
  ax += 0x3730;
  si = ax;
  di = *(WORD*)&_data[ds*16+0x37A0];
  di += bx;
  _push(cx);
  cx = 0x801;
  _push(bx);
  sub_2D9D();
  _pop(bx);
  _pop(cx);
  bx += 2;
  if ( bx < 0x1E ) // jb 
    goto loc_code_3C1E;
  if ( unknown_condition() ) // jnz 
    goto loc_code_3C15;
  al = 0x20;
  goto loc_code_3BED;
loc_code_3C15:
  *(WORD*)&_data[ds*16+0x37A0] += 0x140;
  if ( --cx )
    goto loc_code_3BE9;
  return;
loc_code_3C1E:
  if ( _data[ds*16+0x37A2] == 0x50 ) // jz 
    goto loc_code_3C36;
  if ( cl & 1 ) // jnz 
    goto loc_code_3C36;
  sub_2DFD();
  if ( dl < 0x40 ) // jb 
    goto loc_code_3C36;
  al = 0x10;
  goto loc_code_3BED;
loc_code_3C36:
  sub_2DFD();
  al = dl;
  al -= bl;
  al &= 0x30;
  al += 0x30;
  goto loc_code_3BED;
}

void sub_3C43()
{
  ax = *(WORD*)&_data[ds*16+0x579];
  ax &= 0x0FFFC;
  if ( ax < 0x0A4 ) // jb 
    goto loc_code_3C7F;
  if ( ax > 0x118 ) // ja 
    goto loc_code_3C7F;
  dl = _data[ds*16+0x57B];
  dl -= 2;
  dl &= 0x0F8;
  if ( !(dl & 8) ) // jz 
    goto loc_code_3C7F;
  if ( dl < 0x28 ) // jb 
    goto loc_code_3C7F;
  if ( dl > 0x0A0 ) // ja 
    goto loc_code_3C7F;
  *(WORD*)&_data[ds*16+0x579] = ax;
  dl += 2;
  _data[ds*16+0x57B] = dl;
  dl += 0x32;
  _data[ds*16+0x57C] = dl;
  _stc();
  return;
loc_code_3C7F:
  _clc();
}

/*
  unknown_command(); // align 10h
*/
void sub_3C90()
{
  _data[ds*16+0x3966] = 8;
  _data[ds*16+0x396A] = 1;
  _data[ds*16+0x3967] = 0;
  _data[ds*16+0x396D] = 2;
  *(WORD*)&_data[ds*16+0x3964] = 0x118;
  *(WORD*)&_data[ds*16+0x396B] = 0;
}

void sub_3CB1()
{
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x39C8];
  if ( ax >= 2 ) // jnb 
    goto loc_code_3CC1;
  return;
loc_code_3CC1:
  *(WORD*)&_data[ds*16+0x39C8] = dx;
  sub_3E52();
  if ( unknown_condition() ) // jb cf=1
    return;
  sub_3E6E();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3CD2;
  goto loc_code_3D90;
loc_code_3CD2:
  bx = *(WORD*)&_data[ds*16+8];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x39CC];
  *(WORD*)&_data[ds*16+0x39C6] = ax;
  ax = *(WORD*)&_data[ds*16+0x3964];
  *(WORD*)&_data[ds*16+0x39C3] = ax;
  dl = _data[ds*16+0x3966];
  _data[ds*16+0x39C5] = dl;
  if ( dl != 8 ) // jnz 
    goto loc_code_3D25;
  ax &= 0x0FFF8;
  dx = *(WORD*)&_data[ds*16+0x579];
  dx &= 0x0FFF8;
  if ( ax != dx ) // jnz 
    goto loc_code_3D0D;
  _data[ds*16+0x3967] = 1;
  _data[ds*16+0x396E] = 1;
  goto loc_code_3D25;
loc_code_3D0D:
  ax = *(WORD*)&_data[ds*16+0x3964];
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_3D1C;
  cf = (ax < *(WORD*)&_data[ds*16+0x39C6]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x39C6];
  if ( !cf ) // jnb 
    goto loc_code_3D20;
  ax = 0;
  goto loc_code_3D20;
loc_code_3D1C:
  ax += *(WORD*)&_data[ds*16+0x39C6];
loc_code_3D20:
  *(WORD*)&_data[ds*16+0x3964] = ax;
  goto loc_code_3D79;
loc_code_3D25:
  al = _data[ds*16+0x3966];
  (_data[ds*16+0x396E])++;
  dl = _data[ds*16+0x396E];
  dl >>= 1;
  dl >>= 1;
  dl &= 3;
  dl += 2;
  if ( _data[ds*16+0x3967] == 1 ) // jz 
    goto loc_code_3D52;
  cf = (al < dl); // cf-insertion
  al -= dl;
  if ( cf ) // jb 
    goto loc_code_3D49;
  if ( al >= 9 ) // jnb 
    goto loc_code_3D76;
loc_code_3D49:
  al = 8;
  _data[ds*16+0x3967] = 0;
  goto loc_code_3D76;
loc_code_3D52:
  al += dl;
  if ( al > _data[ds*16+0x57B] ) // ja 
    goto loc_code_3D71;
  bx = *(WORD*)&_data[ds*16+0x3964];
  cf = (bx < *(WORD*)&_data[ds*16+0x579]); // cf-insertion
  bx -= *(WORD*)&_data[ds*16+0x579];
  if ( !cf ) // jnb 
    goto loc_code_3D66;
  bx = ~bx;
loc_code_3D66:
  if ( bx > 0x30 ) // ja 
    goto loc_code_3D71;
  if ( al < 0x0A0 ) // jb 
    goto loc_code_3D76;
  al = 0x9F;
loc_code_3D71:
  _data[ds*16+0x3967] = 0x0FF;
loc_code_3D76:
  _data[ds*16+0x3966] = al;
loc_code_3D79:
  sub_3E52();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3D8B;
  ax = *(WORD*)&_data[ds*16+0x39C3];
  *(WORD*)&_data[ds*16+0x3964] = ax;
  al = _data[ds*16+0x39C5];
  _data[ds*16+0x3966] = al;
  return;
loc_code_3D8B:
  sub_3E6E();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_3DEE;
loc_code_3D90:
  if ( _data[ds*16+0x553] == 0 ) // jz 
    goto loc_code_3D98;
  return;
loc_code_3D98:
  cx = *(WORD*)&_data[ds*16+0x579];
  cf = (cx < 0x0C); // cf-insertion
  cx -= 0x0C;
  if ( !cf ) // jnb 
    goto loc_code_3DA3;
  cx = 0;
loc_code_3DA3:
  if ( cx < 0x10F ) // jb 
    goto loc_code_3DAC;
  cx = 0x10E;
loc_code_3DAC:
  dl = _data[ds*16+0x57B];
  cf = (dl < 4); // cf-insertion
  dl -= 4;
  if ( !cf ) // jnb 
    goto loc_code_3DB7;
  dl = 0;
loc_code_3DB7:
  sub_2CB0();
  di = ax;
  ax = 0x0B800;
  es = ax;
  si = 0x37C0;
  bp = 0x0E;
  cx = 0x1506;
  sub_2CCC();
  sub_56F4();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x39C8] = dx;
loc_code_3DD8:
  sub_5704();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x39C8];
  if ( dx < 9 ) // jb 
    goto loc_code_3DD8;
  _data[ds*16+0x552] = 1;
  return;
loc_code_3DEE:
  cx = *(WORD*)&_data[ds*16+0x3964];
  dl = _data[ds*16+0x3966];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x39CA] = ax;
  sub_3E38();
  (_data[ds*16+0x396D])--;
  if ( _data[ds*16+0x396D] ) // jnz 
    goto loc_code_3E10;
  _data[ds*16+0x396D] = 2;
  *(WORD*)&_data[ds*16+0x396B] ^= 0x54;
loc_code_3E10:
  sub_3E14();
}

void sub_3E14()
{
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x39CA];
  *(WORD*)&_data[ds*16+0x3968] = di;
  bp = 0x396F;
  _data[ds*16+0x396A] = 0;
  si = *(WORD*)&_data[ds*16+0x396B];
  si += 0x38BC;
  cx = 0x0E03;
  sub_2CCC();
}

void sub_3E38()
{
  ax = 0x0B800;
  es = ax;
  if ( _data[ds*16+0x396A] != 0 ) // jnz 
    return;
  di = *(WORD*)&_data[ds*16+0x3968];
  si = 0x396F;
  cx = 0x0E03;
  sub_2D9D();
}

void sub_3E52()
{
  ax = *(WORD*)&_data[ds*16+0x3964];
  dl = _data[ds*16+0x3966];
  si = 0x18;
  bx = *(WORD*)&_data[ds*16+0x327D];
  dh = _data[ds*16+0x327F];
  di = 0x10;
  cx = 0x1E0E;
  sub_2E29();
}

void sub_3E6E()
{
  ax = *(WORD*)&_data[ds*16+0x3964];
  dl = _data[ds*16+0x3966];
  si = 0x18;
  di = si;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  cx = 0x0E0E;
  sub_2E29();
}

/*
  unknown_command(); // align 8
*/
void sub_3E90()
{
  if ( _data[ds*16+0x39E1] == 0 ) // jz 
    goto loc_code_3EA4;
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x3D16] ) // jz 
    return;
  goto loc_code_3F35;
loc_code_3EA4:
  if ( _data[ds*16+0x584] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x69A] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x39E0] != 0 ) // jnz 
    goto loc_code_3EBA;
  return;
loc_code_3EBA:
  sub_4065();
  if ( unknown_condition() ) // jb cf=1
    return;
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x3D18];
  if ( ax < 0x0C ) // jb 
    return;
  *(WORD*)&_data[ds*16+0x3D18] = dx;
  _data[ds*16+0x55C] = 0;
  bl = _data[ds*16+0x39E0];
  bl--;
  bh = 0;
  si = bx;
  cl = 2;
  si <<= cl;
  ax = *(WORD*)&_data[si + 0x3C5A];
  *(WORD*)&_data[ds*16+0x39E2] = ax;
  ax = 0;
  if ( bl >= 3 ) // jnb 
    goto loc_code_3EF5;
  al = 0x80;
loc_code_3EF5:
  *(WORD*)&_data[ds*16+0x39E4] = ax;
  bl = _data[bx + 0x3CE3];
  si = bx;
  cl = 2;
  si <<= cl;
  ax = *(WORD*)&_data[si + 0x3C5A];
  *(WORD*)&_data[ds*16+0x39E6] = ax;
  ax = 0;
  if ( bl >= 3 ) // jnb 
    goto loc_code_3F12;
  al = 0x80;
loc_code_3F12:
  *(WORD*)&_data[ds*16+0x39E8] = ax;
  al = _data[bx + 0x1050];
  _data[ds*16+0x3D05] = al;
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x1137];
  ax += 8;
  *(WORD*)&_data[ds*16+0x3D03] = ax;
  sub_11E3();
  _data[ds*16+0x39E1] = 0x0E;
  _data[ds*16+0x69A] = 0x10;
loc_code_3F35:
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    goto loc_code_3F3F;
  sub_33A0();
loc_code_3F3F:
  _data[ds*16+0x39E1] -= 2;
  bh = 0;
  bl = _data[ds*16+0x39E1];
  if ( bl < 8 ) // jb 
    goto loc_code_3F58;
  di = *(WORD*)&_data[ds*16+0x39E2];
  ax = *(WORD*)&_data[ds*16+0x39E4];
  goto loc_code_3F70;
loc_code_3F58:
  di = *(WORD*)&_data[ds*16+0x39E6];
  al = _data[ds*16+0x3D05];
  _data[ds*16+0x57B] = al;
  al += 0x32;
  _data[ds*16+0x57C] = al;
  ax = *(WORD*)&_data[ds*16+0x3D03];
  *(WORD*)&_data[ds*16+0x579] = ax;
  ax = *(WORD*)&_data[ds*16+0x39E8];
loc_code_3F70:
  ax += *(WORD*)&_data[bx + 0x3D06];
  si = ax;
  ax = 0x0B800;
  es = ax;
  cx = 0x1002;
  sub_2D9D();
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    goto loc_code_3F8B;
  sub_3339();
loc_code_3F8B:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x3D16] = dx;
  if ( _data[ds*16+0x39E1] != 0 ) // jnz 
    return;
  sub_1112();
}

void sub_3F9E()
{
  ax = 0x0B800;
  es = ax;
  _data[ds*16+0x39E0] = 0;
  _data[ds*16+0x39E1] = 0;
  *(WORD*)&_data[ds*16+0x3CBF] = 0x506;
  *(WORD*)&_data[ds*16+0x3CC1] = 0;
loc_code_3FB9:
  bx = *(WORD*)&_data[ds*16+0x3CC1];
  cl = _data[bx + 0x3CAE];
  bx = 0;
  ch = bl;
loc_code_3FC5:
  si = 0x3AEA;
  sub_2DFD();
  if ( dl > 0x30 ) // ja 
    goto loc_code_3FDB;
  si = 0x3AF8;
  if ( dl & 4 ) // jnz 
    goto loc_code_3FDB;
  si = 0x3B02;
loc_code_3FDB:
  di = *(WORD*)&_data[ds*16+0x3CBF];
  di += bx;
  _push(cx);
  _push(bx);
  cx = 0x801;
  sub_2D9D();
  _pop(bx);
  _pop(cx);
  bx += 2;
  if ( --cx )
    goto loc_code_3FC5;
  *(WORD*)&_data[ds*16+0x3CBF] += 0x140;
  (*(WORD*)&_data[ds*16+0x3CC1])++;
  if ( *(WORD*)&_data[ds*16+0x3CC1] < 0x11 ) // jb 
    goto loc_code_3FB9;
  bx = 0x3C22;
  ax = 0;
  sub_2B24();
  bx = 0x3C3E;
  ax = 0;
  sub_2B24();
  bx = 0x3C9A;
  ax = 0;
  sub_2B24();
  bx = 0x3C56;
  ax = 0;
  sub_2B24();
  si = 0x3CAA;
  di = 0x8EC;
  cx = 0x102;
  bp = 0x0E;
  sub_2D35();
  si = 0;
  bx = *(WORD*)&_data[ds*16+8];
  cl = 3;
  bl &= cl;
  bl <<= cl;
loc_code_403C:
  al = _data[bx + 0x3CC3];
  ah = al;
  cl = 4;
  al >>= cl;
  _data[si + 0x3CE3] = al;
  _data[si + 0x3CF3] = 0;
  ah &= 0x0F;
  _data[si + 0x3CE4] = ah;
  _data[si + 0x3CF4] = 0;
  si += 2;
  bx++;
  if ( si < 0x10 ) // jb 
    goto loc_code_403C;
}

void sub_4065()
{
  ax = *(WORD*)&_data[ds*16+0x327D];
  dl = _data[ds*16+0x327F];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E1E;
  sub_2E29();
}

/*
  unknown_command(); // align 10h
*/
void sub_4090()
{
  cx = 4;
loc_code_4093:
  bx = cx;
  bx--;
  si = bx;
  si <<= 1;
  _data[bx + 0x3EAE] = 1;
  _data[bx + 0x3EB2] = 0;
  sub_4277();
  sub_2DFD();
  dl &= 0x0F;
  dl += 0x14;
  _data[bx + 0x3EB6] = dl;
  if ( --cx )
    goto loc_code_4093;
  *(WORD*)&_data[ds*16+0x3EDA] = 0;
  _data[ds*16+0x3ED8] = 4;
}

void sub_40C2()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x3EDC] ) // jnz 
    goto loc_code_40CD;
  return;
loc_code_40CD:
  (*(WORD*)&_data[ds*16+0x3EDA])++;
  bx = *(WORD*)&_data[ds*16+0x3EDA];
  if ( bx <= 2 ) // jbe 
    goto loc_code_40E5;
  if ( bx < 4 ) // jb 
    goto loc_code_40E9;
  bx = 0;
  *(WORD*)&_data[ds*16+0x3EDA] = bx;
loc_code_40E5:
  *(WORD*)&_data[ds*16+0x3EDC] = dx;
loc_code_40E9:
  si = bx;
  si <<= 1;
  if ( _data[bx + 0x3EB2] != 0 ) // jnz 
    return;
  sub_42DB();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_40FC;
  goto loc_code_4124;
loc_code_40FC:
  sub_42FC();
  if ( unknown_condition() ) // jb cf=1
    return;
  if ( _data[bx + 0x3EB6] != 0 ) // jnz 
    goto loc_code_4118;
  sub_4277();
  sub_2DFD();
  dl &= 7;
  dl += 0x14;
  _data[bx + 0x3EB6] = dl;
loc_code_4118:
  _data[bx + 0x3EB6]--;
  sub_42DB();
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_4124;
  goto loc_code_4181;
loc_code_4124:
  if ( _data[bx + 0x3EAE] != 0 ) // jnz 
    return;
  if ( _data[bx + 0x3EB6] < 0x14 ) // jb 
    goto loc_code_4133;
  return;
loc_code_4133:
  sub_11E3();
  sub_4254();
  bx = *(WORD*)&_data[ds*16+0x3EDA];
  _data[bx + 0x3EB2] = 1;
  sub_1124();
  _data[ds*16+0x55C] = 0;
  (_data[ds*16+0x3ED8])--;
  if ( _data[ds*16+0x3ED8] ) // jnz 
    goto loc_code_4155;
  _data[ds*16+0x553] = 1;
loc_code_4155:
  al = 4;
  al -= *(WORD*)&_data[ds*16+0x3ED8];
  cl = 2;
  al <<= cl;
  ah = 0;
  ax += 0x51;
  di = ax;
  bp = 0x0E;
  si = 0x3D20;
  ax = 0x0B800;
  es = ax;
  cx = 0x0C02;
  sub_2D35();
  ax = 0x3E8;
  bx = 0x2EE;
  sub_593B();
  return;
loc_code_4181:
  sub_42B4();
  di = *(WORD*)&_data[ds*16+8];
  di <<= 1;
  bp = *(WORD*)&_data[di + 0x3EDE];
  sub_431C();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_41B0;
  if ( _data[bx + 0x3EB6] < 2 ) // jb 
    goto loc_code_41B0;
  al = 1;
  if ( _data[bx + 0x3EB6] <= 0x11 ) // jbe 
    goto loc_code_41AC;
  if ( _data[bx + 0x3EB6] >= 0x14 ) // jnb 
    goto loc_code_41B0;
  al--;
loc_code_41AC:
  _data[bx + 0x3EB6] = al;
loc_code_41B0:
  al = _data[bx + 0x3EB6];
  if ( al <= 1 ) // jbe 
    goto loc_code_41D8;
  if ( al < 0x12 ) // jb 
    goto loc_code_41F8;
  al = 1;
  if ( *(WORD*)&_data[si + 0x3EBA] >= 3 ) // jnb 
    goto loc_code_41C7;
  al = 3;
loc_code_41C7:
  *(WORD*)&_data[bx + 0x3ED4] += al;
  if ( _data[bx + 0x3EB6] < 0x13 ) // jb 
    goto loc_code_41F3;
  if ( unknown_condition() ) // jz 
    goto loc_code_41EE;
  ax = 0;
  goto loc_code_4204;
loc_code_41D8:
  al = 1;
  if ( *(WORD*)&_data[si + 0x3EBA] >= 3 ) // jnb 
    goto loc_code_41E3;
  al = 3;
loc_code_41E3:
  *(WORD*)&_data[bx + 0x3ED4] += al;
  if ( _data[bx + 0x3EB6] >= 1 ) // jnb 
    goto loc_code_41F3;
loc_code_41EE:
  ax = 0x3DB0;
  goto loc_code_4204;
loc_code_41F3:
  ax = 0x3D80;
  goto loc_code_4204;
loc_code_41F8:
  al <<= 1;
  di = ax;
  di &= 2;
  ax = *(WORD*)&_data[di + 0x3DE0];
loc_code_4204:
  *(WORD*)&_data[ds*16+0x3ECA] = ax;
  dl = _data[bx + 0x3ED4];
  cx = *(WORD*)&_data[si + 0x3ECC];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x3DE4] = ax;
  sub_4254();
  bx = *(WORD*)&_data[ds*16+0x3EDA];
  si = bx;
  si <<= 1;
  sub_42FC();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4226;
  return;
loc_code_4226:
  if ( *(WORD*)&_data[ds*16+0x3ECA] != 0 ) // jnz 
    goto loc_code_4233;
  _data[bx + 0x3EAE] = 1;
  return;
loc_code_4233:
  _data[bx + 0x3EAE] = 0;
  di = *(WORD*)&_data[ds*16+0x3DE4];
  *(WORD*)&_data[si + 0x3EA6] = di;
  ax = 0x0B800;
  es = ax;
  bp = *(WORD*)&_data[si + 0x3EC2];
  cx = 0x0C02;
  si = *(WORD*)&_data[ds*16+0x3ECA];
  sub_2D35();
}

void sub_4254()
{
  bx = *(WORD*)&_data[ds*16+0x3EDA];
  si = bx;
  si <<= 1;
  if ( _data[bx + 0x3EAE] != 0 ) // jnz 
    return;
  di = *(WORD*)&_data[si + 0x3EA6];
  cx = 0x0C02;
  si = *(WORD*)&_data[si + 0x3EC2];
  ax = 0x0B800;
  es = ax;
  sub_2D9D();
}

void sub_4277()
{
  _data[ds*16+0x3ED9] = 0x20;
loc_code_427C:
  sub_2DFD();
  dx &= 0x0F;
  di = 0;
loc_code_4285:
  if ( di == si ) // jz 
    goto loc_code_428F;
  if ( dx == *(WORD*)&_data[di + 0x3EBA] ) // jz 
    goto loc_code_427C;
loc_code_428F:
  di += 2;
  if ( di < 8 ) // jb 
    goto loc_code_4285;
  *(WORD*)&_data[si + 0x3EBA] = dx;
  sub_42B4();
  if ( _data[ds*16+0x3ED9] == 0 ) // jz 
    return;
  bp = 0x32;
  sub_431C();
  if ( unknown_condition() ) // jnb cf=0
    return;
  (_data[ds*16+0x3ED9])--;
  goto loc_code_427C;
}

void sub_42B4()
{
  di = *(WORD*)&_data[si + 0x3EBA];
  al = _data[di + 0x1050];
  dl = 0x0A;
  if ( di >= 3 ) // jnb 
    goto loc_code_42C5;
  dl = 0;
loc_code_42C5:
  al -= dl;
  al += 3;
  _data[bx + 0x3ED4] = al;
  di <<= 1;
  ax = *(WORD*)&_data[di + 0x1137];
  ax += 8;
  *(WORD*)&_data[si + 0x3ECC] = ax;
}

void sub_42DB()
{
  _push(si);
  _push(bx);
  ax = *(WORD*)&_data[si + 0x3ECC];
  dl = _data[bx + 0x3ED4];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E0C;
  sub_2E29();
  _pop(bx);
  _pop(si);
}

void sub_42FC()
{
  _push(si);
  _push(bx);
  ax = *(WORD*)&_data[si + 0x3ECC];
  dl = _data[bx + 0x3ED4];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x327D];
  dh = _data[ds*16+0x327F];
  di = si;
  cx = 0x1E0C;
  sub_2E29();
  _pop(bx);
  _pop(si);
}

void sub_431C()
{
  ax = *(WORD*)&_data[si + 0x3ECC];
  cf = (ax < *(WORD*)&_data[ds*16+0x579]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x579];
  if ( !cf ) // jnb 
    goto loc_code_4328;
  ax = ~ax;
loc_code_4328:
  dl = _data[bx + 0x3ED4];
  cf = (dl < *(WORD*)&_data[ds*16+0x57B]); // cf-insertion
  dl -= *(WORD*)&_data[ds*16+0x57B];
  if ( !cf ) // jnb 
    goto loc_code_4334;
  dl = ~dl;
loc_code_4334:
  dh = 0;
  ax += dx;
  if ( ax < bp ) // jb 
    goto loc_code_433E;
  _clc();
  return;
loc_code_433E:
  _stc();
}

void sub_4340()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x40B5] ) // jnz 
    goto loc_code_434B;
  return;
loc_code_434B:
  (_data[ds*16+0x40FF])++;
  if ( !(_data[ds*16+0x40FF] & 3) ) // jz 
    goto loc_code_435A;
  *(WORD*)&_data[ds*16+0x40B5] = dx;
loc_code_435A:
  if ( _data[ds*16+0x40AA] < 0x0A4 ) // jb 
    return;
  sub_452D();
  sub_4557();
  if ( unknown_condition() ) // jb cf=1
    return;
  sub_2DFD();
  if ( dl > 0x30 ) // ja 
    goto loc_code_439C;
  sub_44FB();
  si = *(WORD*)&_data[ds*16+8];
  si <<= 1;
  ax = *(WORD*)&_data[si + 0x40CE];
  if ( *(WORD*)&_data[ds*16+0x40CC] > ax ) // ja 
    goto loc_code_439C;
  sub_595D();
  *(WORD*)&_data[ds*16+0x40C8] = 0x0FF;
  al = _data[ds*16+0x40CA];
  _data[ds*16+0x40B7] = al;
  al = _data[ds*16+0x40CB];
  _data[ds*16+0x40B8] = al;
  goto loc_code_442E;
loc_code_439C:
  if ( *(WORD*)&_data[ds*16+0x40C8] > 0x0A ) // ja 
    goto loc_code_43B1;
  sub_2DFD();
  if ( dl > 6 ) // ja 
    goto loc_code_43B4;
  *(WORD*)&_data[ds*16+0x40C8] = 0x0FF;
loc_code_43B1:
  goto loc_code_4402;
loc_code_43B4:
  bx = *(WORD*)&_data[ds*16+0x40C8];
  si = bx;
  si <<= 1;
  dl = 0;
  ax = *(WORD*)&_data[ds*16+0x40B2];
  ax &= 0x0FFC;
  if ( ax == *(WORD*)&_data[si + 0x40DE] ) // jz 
    goto loc_code_43D0;
  dl++;
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_43D0;
  dl = 0x0FF;
loc_code_43D0:
  _data[ds*16+0x40B7] = dl;
  dl = 0;
  al = _data[ds*16+0x40B4];
  al &= 0x0FE;
  if ( al == _data[bx + 0x40F4] ) // jz 
    goto loc_code_43E7;
  dl++;
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_43E7;
  dl = 0x0FF;
loc_code_43E7:
  _data[ds*16+0x40B8] = dl;
  dl |= *(WORD*)&_data[ds*16+0x40B7];
  if ( dl ) // jnz 
    goto loc_code_442E;
  sub_2DFD();
  if ( dl > 0x10 ) // ja 
    goto loc_code_442E;
  *(WORD*)&_data[ds*16+0x40C8] = 0x0FF;
  sub_595D();
loc_code_4402:
  sub_2DFD();
  if ( dl > 0x30 ) // ja 
    goto loc_code_4423;
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_4411;
  dl = 0x0FF;
loc_code_4411:
  _data[ds*16+0x40B7] = dl;
  sub_2DFD();
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_441F;
  dl = 0x0FF;
loc_code_441F:
  _data[ds*16+0x40B8] = dl;
loc_code_4423:
  sub_2DFD();
  dx &= 0x0FF;
  *(WORD*)&_data[ds*16+0x40C8] = dx;
loc_code_442E:
  al = _data[ds*16+0x40B4];
  if ( _data[ds*16+0x40B8] < 1 ) // jb 
    goto loc_code_4459;
  if ( unknown_condition() ) // jnz 
    goto loc_code_4449;
  al += 2;
  if ( al < 0x0A8 ) // jb 
    goto loc_code_4456;
  al = 0x0A7;
  _data[ds*16+0x40B8] = 0x0FF;
  goto loc_code_4456;
loc_code_4449:
  al -= 2;
  if ( al >= 0x30 ) // jnb 
    goto loc_code_4456;
  al = 0x30;
  _data[ds*16+0x40B8] = 1;
loc_code_4456:
  _data[ds*16+0x40B4] = al;
loc_code_4459:
  ax = *(WORD*)&_data[ds*16+0x40B2];
  if ( _data[ds*16+0x40B7] < 1 ) // jb 
    goto loc_code_4486;
  if ( unknown_condition() ) // jnz 
    goto loc_code_4477;
  ax += 4;
  if ( ax < 0x136 ) // jb 
    goto loc_code_4483;
  ax = 0x135;
  _data[ds*16+0x40B7] = 0x0FF;
  goto loc_code_4483;
loc_code_4477:
  cf = (ax < 4); // cf-insertion
  ax -= 4;
  if ( !cf ) // jnb 
    goto loc_code_4483;
  ax = 0;
  _data[ds*16+0x40B7] = 1;
loc_code_4483:
  *(WORD*)&_data[ds*16+0x40B2] = ax;
loc_code_4486:
  sub_452D();
  cx = *(WORD*)&_data[ds*16+0x40B2];
  dl = _data[ds*16+0x40B4];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x40BC] = ax;
  ax = 0x0B800;
  es = ax;
  if ( _data[ds*16+0x40B9] != 0 ) // jnz 
    goto loc_code_44B0;
  si = 0x3F2C;
  di = *(WORD*)&_data[ds*16+0x40BA];
  cx = 0x501;
  sub_2D9D();
loc_code_44B0:
  sub_4557();
  if ( unknown_condition() ) // jb cf=1
    return;
  _data[ds*16+0x40B9] = 0;
  *(WORD*)&_data[ds*16+0x40BE] += 2;
  bx = *(WORD*)&_data[ds*16+0x40BE];
  bx &= 6;
  si = *(WORD*)&_data[bx + 0x40C0];
  if ( _data[ds*16+0x40B7] != 0x0FF ) // jnz 
    goto loc_code_44D5;
  si += 0x1E;
loc_code_44D5:
  di = *(WORD*)&_data[ds*16+0x40BC];
  *(WORD*)&_data[ds*16+0x40BA] = di;
  bp = 0x3F2C;
  cx = 0x501;
  sub_2CCC();
}

void sub_44E7()
{
  if ( _data[ds*16+0x571] != 0 ) // jnz 
    goto loc_code_44F9;
  al = _data[ds*16+0x57B];
  al &= 0x0F8;
  if ( al != 0x88 ) // jnz 
    goto loc_code_44F9;
  _stc();
  return;
loc_code_44F9:
  _clc();
}

void sub_44FB()
{
  ax = *(WORD*)&_data[ds*16+0x40B2];
  dl = 1;
  cf = (ax < *(WORD*)&_data[ds*16+0x579]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x579];
  if ( !cf ) // jnb 
    goto loc_code_450A;
  ax = ~ax;
  dl = 0x0FF;
loc_code_450A:
  _data[ds*16+0x40CA] = dl;
  *(WORD*)&_data[ds*16+0x40CC] = ax;
  al = _data[ds*16+0x40B4];
  dl = 1;
  cf = (al < *(WORD*)&_data[ds*16+0x57B]); // cf-insertion
  al -= *(WORD*)&_data[ds*16+0x57B];
  if ( !cf ) // jnb 
    goto loc_code_4520;
  al = ~al;
  dl = 0x0FF;
loc_code_4520:
  _data[ds*16+0x40CB] = dl;
  ah = 0;
  ax <<= 1;
  *(WORD*)&_data[ds*16+0x40CC] += ax;
}

void sub_452D()
{
  ax = *(WORD*)&_data[ds*16+0x40B2];
  dl = _data[ds*16+0x40B4];
  si = 8;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E05;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  if ( _data[ds*16+0x552] != 0 ) // jnz 
    return;
  _data[ds*16+0x553] = 1;
}

void sub_4557()
{
  ax = *(WORD*)&_data[ds*16+0x40B2];
  dl = _data[ds*16+0x40B4];
  si = 8;
  bx = *(WORD*)&_data[ds*16+0x327D];
  dh = _data[ds*16+0x327F];
  di = 0x10;
  cx = 0x1E05;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x40B8] = 0x0FF;
}

void sub_457A()
{
  cx = 0x90;
  dl = 0x86;
  *(WORD*)&_data[ds*16+0x40A8] = cx;
  _data[ds*16+0x40AA] = dl;
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x40AB] = ax;
  sub_4759();
  _data[ds*16+0x40AF] = 0;
  _data[ds*16+0x40B1] = 0;
  _data[ds*16+0x40B9] = 1;
  _data[ds*16+0x40B8] = 0;
  *(WORD*)&_data[ds*16+0x40C8] = 0x0FF;
}

void sub_45AB()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x40AD] ) // jnz 
    goto loc_code_45B6;
  return;
loc_code_45B6:
  *(WORD*)&_data[ds*16+0x40AD] = dx;
  if ( _data[ds*16+0x40AA] >= 0x0A4 ) // jnb 
    return;
  sub_4786();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_45D6;
  sub_44E7();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x55B] = 0x10;
  return;
loc_code_45D6:
  sub_473E();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4649;
  if ( _data[ds*16+0x40AF] != 0 ) // jnz 
    goto loc_code_45FA;
  al = _data[ds*16+0x56E];
  if ( al != 0 ) // jnz 
    goto loc_code_45F7;
  al++;
  bx = *(WORD*)&_data[ds*16+0x40A8];
  if ( bx > *(WORD*)&_data[ds*16+0x579] ) // ja 
    goto loc_code_45F7;
  al = 0x0FF;
loc_code_45F7:
  _data[ds*16+0x40B0] = al;
loc_code_45FA:
  _data[ds*16+0x40AF] = 1;
  cx = 0x20;
loc_code_4602:
  ax = *(WORD*)&_data[ds*16+0x579];
  dl = 1;
  if ( _data[ds*16+0x40B0] != 1 ) // jnz 
    goto loc_code_4615;
  ax -= 8;
  dl = 0x0FF;
  goto loc_code_4618;
loc_code_4615:
  ax += 8;
loc_code_4618:
  *(WORD*)&_data[ds*16+0x579] = ax;
  _data[ds*16+0x56E] = dl;
  al = _data[ds*16+0x57B];
  if ( _data[ds*16+0x571] < 1 ) // jb 
    goto loc_code_4639;
  if ( unknown_condition() ) // jnz 
    goto loc_code_462F;
  al -= 3;
  goto loc_code_4631;
loc_code_462F:
  al += 3;
loc_code_4631:
  _data[ds*16+0x57B] = al;
  al += 0x32;
  _data[ds*16+0x57C] = al;
loc_code_4639:
  _push(cx);
  sub_473E();
  _pop(cx);
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4642;
  if ( --cx )
    goto loc_code_4602;
loc_code_4642:
  sub_11E3();
  sub_1112();
  return;
loc_code_4649:
  if ( _data[ds*16+0x40B1] != 0 ) // jnz 
    goto loc_code_46A2;
  if ( _data[ds*16+0x40AF] == 0 ) // jz 
    return;
  ax = *(WORD*)&_data[ds*16+0x40A8];
  if ( _data[ds*16+0x40B0] != 1 ) // jnz 
    goto loc_code_4666;
  ax += 8;
  goto loc_code_4669;
loc_code_4666:
  ax -= 8;
loc_code_4669:
  *(WORD*)&_data[ds*16+0x40A8] = ax;
  sub_473E();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4672;
  return;
loc_code_4672:
  ax = 0x0C00;
  bx = 0x0B54;
  sub_593B();
  _data[ds*16+0x40AF] = 0;
  cx = *(WORD*)&_data[ds*16+0x40A8];
  dl = _data[ds*16+0x40AA];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x40AB] = ax;
  sub_4773();
  sub_4759();
  ax = *(WORD*)&_data[ds*16+0x40A8];
  if ( ax < 0x78 ) // jb 
    goto loc_code_46A2;
  if ( ax > 0x0A8 ) // ja 
    goto loc_code_46A2;
  return;
loc_code_46A2:
  _data[ds*16+0x40B1] = 1;
  if ( _data[ds*16+0x1CBF] == 0 ) // jz 
    goto loc_code_46BE;
  sub_44E7();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x55B] = 0x10;
  return;
loc_code_46BE:
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x40AD] ) // jz 
    goto loc_code_46A2;
  *(WORD*)&_data[ds*16+0x40AD] = dx;
  if ( _data[ds*16+0] == 0 ) // jz 
    goto loc_code_46EC;
  al = 0x0B6;
  _out(0x43, al);
  al = _data[ds*16+0x40AA];
  ah = 0;
  ax <<= 1;
  ax <<= 1;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
loc_code_46EC:
  dl = _data[ds*16+0x40AA];
  if ( dl >= 0x0A4 ) // jnb 
    goto loc_code_470E;
  dl += 5;
  _data[ds*16+0x40AA] = dl;
  cx = *(WORD*)&_data[ds*16+0x40A8];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x40AB] = ax;
  sub_4773();
  sub_4759();
  goto loc_code_46BE;
loc_code_470E:
  sub_5B21();
  sub_4773();
  bp = 0x401E;
  (*(WORD*)&_data[ds*16+0x40A6])--;
  di = *(WORD*)&_data[ds*16+0x40A6];
  si = 0x3F36;
  cx = 0x1104;
  sub_2D35();
  ax = *(WORD*)&_data[ds*16+0x40A8];
  *(WORD*)&_data[ds*16+0x40B2] = ax;
  al = _data[ds*16+0x40AA];
  _data[ds*16+0x40B4] = al;
  sub_44FB();
  al = _data[ds*16+0x40CA];
  _data[ds*16+0x40B7] = al;
}

void sub_473E()
{
  ax = *(WORD*)&_data[ds*16+0x40A8];
  dl = _data[ds*16+0x40AA];
  si = 0x18;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = si;
  cx = 0x0E10;
  sub_2E29();
}

void sub_4759()
{
  ax = 0x0B800;
  es = ax;
  bp = 0x401E;
  si = 0x3FBE;
  di = *(WORD*)&_data[ds*16+0x40AB];
  *(WORD*)&_data[ds*16+0x40A6] = di;
  cx = 0x1003;
  sub_2D35();
}

void sub_4773()
{
  ax = 0x0B800;
  es = ax;
  si = 0x401E;
  di = *(WORD*)&_data[ds*16+0x40A6];
  cx = 0x1003;
  sub_2D9D();
}

void sub_4786()
{
  if ( _data[ds*16+0x327F] < 0x66 ) // jb 
    goto loc_code_47A4;
  ax = *(WORD*)&_data[ds*16+0x40A8];
  ax -= 0x14;
  if ( ax > *(WORD*)&_data[ds*16+0x327D] ) // ja 
    goto loc_code_47A4;
  ax += 0x30;
  if ( ax < *(WORD*)&_data[ds*16+0x327D] ) // jb 
    goto loc_code_47A4;
  _stc();
  return;
loc_code_47A4:
  _clc();
}

/*
  unknown_command(); // align 10h
*/
void sub_47B0()
{
  ax = *(WORD*)&_data[ds*16+0x327D];
  dl = _data[ds*16+0x327F];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  cf = (bx < 8); // cf-insertion
  bx -= 8;
  if ( !cf ) // jnb 
    goto loc_code_47C5;
  bx = 0;
loc_code_47C5:
  dh = _data[ds*16+0x57B];
  dh += 3;
  di = 0x28;
  cx = 0x0E1E;
  sub_2E29();
}

void sub_47D6()
{
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x44D7];
  si = *(WORD*)&_data[ds*16+8];
  si <<= 1;
  if ( ax > *(WORD*)&_data[si + 0x44DC] ) // ja 
    goto loc_code_47ED;
  return;
loc_code_47ED:
  *(WORD*)&_data[ds*16+0x44D7] = dx;
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    return;
  _data[ds*16+0x44FC] = 0;
  cx = 0x0C;
loc_code_4800:
  bx = cx;
  bx--;
  bl <<= 1;
  if ( *(WORD*)&_data[bx + 0x4441] == 0 ) // jz 
    goto loc_code_487D;
  ax = *(WORD*)&_data[bx + 0x43F9];
  if ( al != _data[ds*16+0x57B] ) // jnz 
    goto loc_code_485D;
  ax = *(WORD*)&_data[bx + 0x43E1];
  cf = (ax < *(WORD*)&_data[ds*16+0x579]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x579];
  if ( !cf ) // jnb 
    goto loc_code_4822;
  ax = ~ax;
loc_code_4822:
  si = *(WORD*)&_data[ds*16+8];
  si <<= 1;
  if ( ax > *(WORD*)&_data[si + 0x44EC] ) // ja 
    goto loc_code_485D;
  if ( *(WORD*)&_data[bx + 0x4459] < 2 ) // jb 
    goto loc_code_484C;
  ax = *(WORD*)&_data[bx + 0x4411];
  *(WORD*)&_data[ds*16+0x44DA] = ax;
  sub_488D();
  sub_48A1();
  sub_3339();
  sub_1145();
  sub_2136();
  return;
loc_code_484C:
  (*(WORD*)&_data[bx + 0x4459])++;
  if ( *(WORD*)&_data[bx + 0x4459] < 2 ) // jb 
    goto loc_code_4870;
  (_data[ds*16+0x44FC])++;
  goto loc_code_4870;
loc_code_485D:
  if ( *(WORD*)&_data[bx + 0x4459] == 0 ) // jz 
    goto loc_code_487D;
  sub_2DFD();
  if ( dl > 0x38 ) // ja 
    goto loc_code_4870;
  (*(WORD*)&_data[bx + 0x4459])--;
loc_code_4870:
  _push(cx);
  _push(bx);
  sub_48D7();
  _pop(bx);
  sub_4916();
  sub_48C1();
  _pop(cx);
loc_code_487D:
  if ( --cx )
    goto loc_code_488A;
  if ( _data[ds*16+0x44FC] == 0 ) // jz 
    return;
  sub_5691();
  return;
loc_code_488A:
  goto loc_code_4800;
}

void sub_488D()
{
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    goto loc_code_489D;
  sub_4B03();
  _data[ds*16+0x44BD] = 0;
  return;
loc_code_489D:
  sub_11E3();
}

void sub_48A1()
{
  _push(ds);
  _pop(es);
  _cld();
  di = 0x0E;
  si = di;
  ax = 0x0AAAA;
  cx = 0x41;
  _rep_stosw();
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x44DA];
  cx = 0x0D05;
  sub_2D9D();
}

void sub_48C1()
{
  if ( _data[ds*16+0x44D9] == 0 ) // jz 
    return;
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    goto loc_code_48D3;
  sub_4B1D();
  return;
loc_code_48D3:
  sub_1145();
}

void sub_48D7()
{
  _data[ds*16+0x44D9] = 0;
  ax = *(WORD*)&_data[bx + 0x43E1];
  dx = *(WORD*)&_data[bx + 0x43F9];
  ax -= 0x14;
  si = 0x28;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  cx = 0x0E06;
  di = 0x18;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x44D9] = 1;
loc_code_4902:
  if ( !sub_13D8() ) // jz 
    goto loc_code_4902;
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    goto loc_code_4912;
  sub_4B03();
  return;
loc_code_4912:
  sub_11E3();
}

void sub_4916()
{
  ax = *(WORD*)&_data[bx + 0x4411];
  si = *(WORD*)&_data[bx + 0x4459];
  si <<= 1;
  si += 0x4100;
  ax += 0x0A7;
  if ( *(WORD*)&_data[bx + 0x4429] == 0x429C ) // jz 
    goto loc_code_4935;
  ax -= 6;
  si += 6;
loc_code_4935:
  di = ax;
  ax = 0x0B800;
  es = ax;
  cx = 0x101;
  sub_2D9D();
}

void sub_4943()
{
  if ( _data[ds*16+0x1CB8] != 0 ) // jnz 
    return;
  if ( _data[ds*16+0x44BE] == 0 ) // jz 
    goto loc_code_495C;
  al = _data[ds*16+0x44BE];
  _data[ds*16+0x698] = al;
  _data[ds*16+0x699] = 0;
loc_code_495C:
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x44D3] ) // jnz 
    goto loc_code_4967;
  return;
loc_code_4967:
  *(WORD*)&_data[ds*16+0x44D3] = dx;
  if ( _data[ds*16+0x584] == 0 ) // jz 
    goto loc_code_4995;
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    return;
  sub_4B03();
  sub_33A0();
  sub_1124();
  sub_3339();
  _data[ds*16+0x44BD] = 0;
  _data[ds*16+0x43E0] = 1;
  _data[ds*16+0x44BE] = 0;
  return;
loc_code_4995:
  if ( _data[ds*16+0x69A] == 0 ) // jz 
    goto loc_code_499F;
  goto loc_code_49F9;
loc_code_499F:
  ax = 0x0FFFF;
  *(WORD*)&_data[ds*16+0x44C1] = ax;
  *(WORD*)&_data[ds*16+0x44BF] = ax;
  cx = 0x0C;
  si = *(WORD*)&_data[ds*16+0x579];
  dl = _data[ds*16+0x57B];
  dl += 8;
loc_code_49B6:
  bx = cx;
  bx--;
  if ( _data[bx + 0x44C4] < 1 ) // jb 
    goto loc_code_49F0;
  if ( dl != _data[bx + 0x4499] ) // jnz 
    goto loc_code_49F0;
  ax = si;
  bl <<= 1;
  dh = 0x0FF;
  cf = (ax < *(WORD*)&_data[bx + 0x4481]); // cf-insertion
  ax -= *(WORD*)&_data[bx + 0x4481];
  if ( !cf ) // jnb 
    goto loc_code_49D6;
  ax = ~ax;
  dh = 1;
loc_code_49D6:
  if ( ax > *(WORD*)&_data[ds*16+0x44BF] ) // ja 
    goto loc_code_49F0;
  *(WORD*)&_data[ds*16+0x44BF] = ax;
  ax = *(WORD*)&_data[bx + 0x44A5];
  *(WORD*)&_data[ds*16+0x44D1] = ax;
  bl >>= 1;
  *(WORD*)&_data[ds*16+0x44C1] = bx;
  _data[ds*16+0x44C3] = dh;
loc_code_49F0:
  if ( --cx )
    goto loc_code_49B6;
  if ( *(WORD*)&_data[ds*16+0x44C1] < 0x0C ) // jb 
    goto loc_code_4A20;
loc_code_49F9:
  if ( _data[ds*16+0x44BD] == 0 ) // jz 
    goto loc_code_4A0B;
  sub_4B03();
  sub_1145();
  _data[ds*16+0x69A] = 0x10;
loc_code_4A0B:
  _data[ds*16+0x44BD] = 0;
  _data[ds*16+0x43E0] = 1;
  _data[ds*16+0x44D0] = 0;
  _data[ds*16+0x44BE] = 0;
  return;
loc_code_4A20:
  if ( *(WORD*)&_data[ds*16+0x44BF] < 4 ) // jb 
    goto loc_code_4A4B;
  if ( *(WORD*)&_data[ds*16+0x44BF] > 8 ) // ja 
    goto loc_code_4A33;
  _data[ds*16+0x572] = 4;
loc_code_4A33:
  al = _data[ds*16+0x44C3];
  _data[ds*16+0x698] = al;
  _data[ds*16+0x56E] = al;
  _data[ds*16+0x44BE] = al;
  _data[ds*16+0x699] = 0;
  _data[ds*16+0x571] = 0;
  goto loc_code_49F9;
loc_code_4A4B:
  _data[ds*16+0x44BE] = 0;
  if ( _data[ds*16+0x44BD] != 0 ) // jnz 
    goto loc_code_4A5D;
  sub_11E3();
  sub_1124();
loc_code_4A5D:
  _data[ds*16+0x44BD] = 1;
  al = 0;
  _data[ds*16+0x44D0] += 0x30;
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4A6D;
  al++;
loc_code_4A6D:
  _data[ds*16+0x44D5] = al;
  cx = *(WORD*)&_data[ds*16+0x579];
  cx &= 0x0FFC;
  dl = _data[ds*16+0x57B];
  dl += 3;
  if ( *(WORD*)&_data[ds*16+0x44D1] == 0x410C ) // jz 
    goto loc_code_4A95;
  cx += 8;
  if ( cx < 0x127 ) // jb 
    goto loc_code_4A9C;
  cx = 0x126;
  goto loc_code_4A9C;
loc_code_4A95:
  cf = (cx < 8); // cf-insertion
  cx -= 8;
  if ( !cf ) // jnb 
    goto loc_code_4A9C;
  cx = 0;
loc_code_4A9C:
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x43DC] = ax;
loc_code_4AA2:
  if ( !sub_13D8() ) // jz 
    goto loc_code_4AA2;
  sub_4B03();
  if ( _data[ds*16+0x44D5] == 0 ) // jz 
    goto loc_code_4AFF;
  bx = *(WORD*)&_data[ds*16+0x44C1];
  if ( _data[bx + 0x44C4] == 0 ) // jz 
    goto loc_code_4AFF;
  _data[bx + 0x44C4]--;
  if ( _data[bx + 0x44C4] ) // jnz 
    goto loc_code_4AE7;
  _push(bx);
  ax = 0x8FD;
  bx = 0x723;
  sub_593B();
  _pop(bx);
  _data[ds*16+0x698] = 0;
  _data[ds*16+0x44BE] = 0;
  _data[ds*16+0x69A] = 0x10;
  (_data[ds*16+0x44D6])--;
  if ( _data[ds*16+0x44D6] ) // jnz 
    goto loc_code_4AE7;
  _data[ds*16+0x553] = 1;
loc_code_4AE7:
  _push(bx);
  sub_47B0();
  _pop(bx);
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4AFC;
  _push(bx);
  sub_33A0();
  _pop(bx);
  sub_4BC8();
  sub_3339();
  goto loc_code_4AFF;
loc_code_4AFC:
  sub_4BC8();
loc_code_4AFF:
  sub_4B1D();
}

void sub_4B03()
{
  if ( _data[ds*16+0x43E0] != 0 ) // jnz 
    return;
  di = *(WORD*)&_data[ds*16+0x43DE];
  si = 0x43A0;
  ax = 0x0B800;
  es = ax;
  cx = 0x0A03;
  sub_2D9D();
}

void sub_4B1D()
{
  _data[ds*16+0x43E0] = 0;
  ax = 0x0B800;
  es = ax;
  di = *(WORD*)&_data[ds*16+0x43DC];
  *(WORD*)&_data[ds*16+0x43DE] = di;
  bp = 0x43A0;
  si = *(WORD*)&_data[ds*16+0x44D1];
  if ( _data[ds*16+0x44D0] < 0x80 ) // jb 
    goto loc_code_4B40;
  si += 0x3C;
loc_code_4B40:
  cx = 0x0A03;
  sub_2D35();
}

void sub_4B47()
{
  _push(ds);
  _pop(es);
  ax = 0;
  di = 0x4441;
  cx = 0x0C;
  _rep_stosw();
  ax = 0x0B800;
  es = ax;
  bx = *(WORD*)&_data[ds*16+8];
  cl = _data[bx + 0x4471];
  ch = 0;
loc_code_4B62:
  sub_2DFD();
  bl = dl;
  bx &= 0x1E;
  if ( bl >= 0x18 ) // jnb 
    goto loc_code_4B62;
  if ( *(WORD*)&_data[bx + 0x4441] != 0 ) // jnz 
    goto loc_code_4B62;
  *(WORD*)&_data[bx + 0x4459] = 0;
  *(WORD*)&_data[bx + 0x4441] = 1;
  _push(cx);
  si = *(WORD*)&_data[bx + 0x4429];
  di = *(WORD*)&_data[bx + 0x4411];
  cx = 0x0D05;
  sub_2D9D();
  _pop(cx);
  if ( --cx )
    goto loc_code_4B62;
  cx = 0x0C;
loc_code_4B98:
  bx = cx;
  bx--;
  si = *(WORD*)&_data[ds*16+8];
  dl = _data[si + 0x4479];
  _data[bx + 0x44C4] = dl;
  _push(cx);
  sub_4BC8();
  _pop(cx);
  if ( --cx )
    goto loc_code_4B98;
  _data[ds*16+0x44D0] = 0;
  _data[ds*16+0x44BD] = 0;
  _data[ds*16+0x43E0] = 1;
  _data[ds*16+0x44D6] = 0x0C;
  _data[ds*16+0x44BE] = 0;
}

void sub_4BC8()
{
  sub_4BE8();
  di = ax;
  al = _data[bx + 0x44C4];
  ah = 0;
  cl = 5;
  ax <<= cl;
  ax += 0x41FC;
  si = ax;
  cx = 0x802;
  ax = 0x0B800;
  es = ax;
  sub_2D9D();
}

void sub_4BE8()
{
  _push(bx);
  dl = _data[bx + 0x4499];
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x4481];
  sub_2CB0();
  _pop(bx);
}

/*
  unknown_command(); // align 10h
  return;
  return;
  return;
  _clc();
  return;
  _clc();
  return;
  return;
  unknown_command(); // align 8
*/
void sub_4C10()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x45B8] ) // jnz 
    goto loc_code_4C1B;
  return;
loc_code_4C1B:
  (*(WORD*)&_data[ds*16+0x45B6])++;
  bx = *(WORD*)&_data[ds*16+0x45B6];
  if ( bx == 1 ) // jz 
    goto loc_code_4C38;
  if ( bx == 4 ) // jz 
    goto loc_code_4C38;
  if ( bx < 7 ) // jb 
    goto loc_code_4C3C;
  bx = 0;
  *(WORD*)&_data[ds*16+0x45B6] = bx;
loc_code_4C38:
  *(WORD*)&_data[ds*16+0x45B8] = dx;
loc_code_4C3C:
  sub_4FCD();
  sub_502D();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4C45;
  return;
loc_code_4C45:
  if ( *(WORD*)&_data[ds*16+0x454F] == 0 ) // jz 
    goto loc_code_4C8C;
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x454F];
  bx = *(WORD*)&_data[ds*16+8];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x45C7];
  if ( *(WORD*)&_data[ds*16+0x45B6] != 0 ) // jnz 
    goto loc_code_4C67;
  ax <<= 1;
loc_code_4C67:
  if ( dx < ax ) // jb 
    return;
  *(WORD*)&_data[ds*16+0x454F] = 0;
  _data[ds*16+0x454E] = 1;
  ax = 0x24;
  if ( *(WORD*)&_data[ds*16+0x579] > 0x0A0 ) // ja 
    goto loc_code_4C84;
  ax = 0x108;
loc_code_4C84:
  *(WORD*)&_data[ds*16+0x4548] = ax;
  _data[ds*16+0x454A] = 0;
loc_code_4C8C:
  sub_4DD0();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4C99;
  bx = *(WORD*)&_data[ds*16+0x45B6];
  sub_4FBB();
  return;
loc_code_4C99:
  if ( _data[ds*16+0x4553] == 0 ) // jz 
    goto loc_code_4CB8;
  (_data[ds*16+0x4553])--;
  if ( _data[ds*16+0x4553] ) // jnz 
    goto loc_code_4CB5;
  dl = 1;
  if ( _data[ds*16+0x454A] == 0x0FF ) // jz 
    goto loc_code_4CB1;
  dl = 0x0FF;
loc_code_4CB1:
  _data[ds*16+0x454A] = dl;
loc_code_4CB5:
  goto loc_code_4D14;
loc_code_4CB8:
  al = _data[ds*16+0x454B];
  if ( al > _data[ds*16+0x57B] ) // ja 
    goto loc_code_4D14;
  if ( *(WORD*)&_data[ds*16+0x45B6] != 6 ) // jnz 
    goto loc_code_4CCF;
  if ( _data[ds*16+0x57B] < 0x28 ) // jb 
    goto loc_code_4CDC;
loc_code_4CCF:
  sub_2DFD();
  bx = *(WORD*)&_data[ds*16+8];
  if ( dl > _data[bx + 0x45BF] ) // ja 
    goto loc_code_4D14;
loc_code_4CDC:
  dl = 0;
  ax = *(WORD*)&_data[ds*16+0x4548];
  ax &= 0x0FF8;
  cx = *(WORD*)&_data[ds*16+0x579];
  cx &= 0x0FF8;
  if ( ax == cx ) // jz 
    goto loc_code_4CF6;
  dl = 1;
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_4CF6;
  dl = 0x0FF;
loc_code_4CF6:
  _data[ds*16+0x454A] = dl;
  if ( _data[ds*16+0x57B] < 0x28 ) // jb 
    goto loc_code_4D14;
  if ( *(WORD*)&_data[ds*16+0x45B6] != 6 ) // jnz 
    goto loc_code_4D14;
  al = 1;
  if ( dl == 0x0FF ) // jz 
    goto loc_code_4D11;
  al = 0x0FF;
loc_code_4D11:
  _data[ds*16+0x454A] = al;
loc_code_4D14:
  *(WORD*)&_data[ds*16+0x45BC] = 8;
  if ( _data[ds*16+0x4553] == 0 ) // jz 
    goto loc_code_4D27;
  *(WORD*)&_data[ds*16+0x45BC] = 4;
loc_code_4D27:
  ax = *(WORD*)&_data[ds*16+0x4548];
  if ( _data[ds*16+0x454A] >= 1 ) // jnb 
    goto loc_code_4D46;
  sub_2DFD();
  if ( dl > 0x10 ) // ja 
    goto loc_code_4DA1;
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_4D40;
  dl = 0x0FF;
loc_code_4D40:
  _data[ds*16+0x454A] = dl;
  goto loc_code_4DA1;
loc_code_4D46:
  if ( unknown_condition() ) // jnz 
    goto loc_code_4D60;
  ax += *(WORD*)&_data[ds*16+0x45BC];
  if ( ax < 0x10B ) // jb 
    goto loc_code_4D78;
  ax = 0x10A;
  _data[ds*16+0x454A] = 0x0FF;
  _data[ds*16+0x4553] = 0;
  goto loc_code_4D78;
loc_code_4D60:
  cf = (ax < *(WORD*)&_data[ds*16+0x45BC]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x45BC];
  if ( cf ) // jb 
    goto loc_code_4D6B;
  if ( ax > 0x24 ) // ja 
    goto loc_code_4D78;
loc_code_4D6B:
  ax = 0x25;
  _data[ds*16+0x454A] = 1;
  _data[ds*16+0x4553] = 0;
loc_code_4D78:
  *(WORD*)&_data[ds*16+0x4548] = ax;
  *(WORD*)&_data[ds*16+0x4551] += 2;
  if ( *(WORD*)&_data[ds*16+0x4551] < 0x0C ) // jb 
    goto loc_code_4D8D;
  *(WORD*)&_data[ds*16+0x4551] = 0;
loc_code_4D8D:
  if ( _data[ds*16+0x4553] != 0 ) // jnz 
    goto loc_code_4DA1;
  sub_2DFD();
  if ( dl > 8 ) // ja 
    goto loc_code_4DA1;
  _data[ds*16+0x454A] = 0;
loc_code_4DA1:
  cx = *(WORD*)&_data[ds*16+0x4548];
  dl = _data[ds*16+0x454B];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x45BA] = ax;
  sub_502D();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_4DB5;
  return;
loc_code_4DB5:
  sub_4DD0();
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_4DC8;
  sub_4F4A();
  sub_4F10();
  _data[ds*16+0x45BE] = 0;
  sub_4E75();
loc_code_4DC8:
  bx = *(WORD*)&_data[ds*16+0x45B6];
  sub_4FBB();
}

void sub_4DD0()
{
  ax = *(WORD*)&_data[ds*16+0x579];
  dl = _data[ds*16+0x57B];
  si = 0x18;
  di = si;
  bx = *(WORD*)&_data[ds*16+0x4548];
  dh = _data[ds*16+0x454B];
  cx = 0x0C0E;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  if ( *(WORD*)&_data[ds*16+0x45B6] != 6 ) // jnz 
    goto loc_code_4E00;
  _data[ds*16+0x553] = 1;
  sub_11E3();
  sub_4F4A();
  _stc();
  return;
loc_code_4E00:
  sub_11E3();
  sub_4F4A();
  sub_1145();
  _data[ds*16+0x55B] = 4;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x576] = 4;
  _data[ds*16+0x578] = 8;
  _data[ds*16+0x4553] = 4;
  dl = 1;
  ax = *(WORD*)&_data[ds*16+0x4548];
  if ( ax > *(WORD*)&_data[ds*16+0x579] ) // ja 
    goto loc_code_4E2F;
  dl = 0x0FF;
loc_code_4E2F:
  _data[ds*16+0x454A] = dl;
  ax = 0x0CE4;
  bx = 0x123B;
  sub_593B();
  _stc();
}

void sub_4E3E()
{
  _data[ds*16+0x45BE] = 1;
  ax = *(WORD*)&_data[ds*16+0x45B6];
  _push(ax);
  *(WORD*)&_data[ds*16+0x45B6] = 0;
loc_code_4E4D:
  bx = *(WORD*)&_data[ds*16+0x45B6];
  sub_4FCD();
  if ( *(WORD*)&_data[ds*16+0x454F] != 0 ) // jnz 
    goto loc_code_4E65;
  sub_4E75();
  bx = *(WORD*)&_data[ds*16+0x45B6];
  sub_4FBB();
loc_code_4E65:
  (*(WORD*)&_data[ds*16+0x45B6])++;
  if ( *(WORD*)&_data[ds*16+0x45B6] < 7 ) // jb 
    goto loc_code_4E4D;
  _pop(ax);
  *(WORD*)&_data[ds*16+0x45B6] = ax;
}

void sub_4E75()
{
  cx = 8;
loc_code_4E78:
  bx = cx;
  bx--;
  if ( _data[bx + 0x2B72] == 0 ) // jz 
    goto loc_code_4EA3;
  _push(cx);
  dl = _data[bx + 0x2B6A];
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x2B5A];
  si = 0x18;
  di = si;
  bx = *(WORD*)&_data[ds*16+0x4548];
  dh = _data[ds*16+0x454B];
  cx = 0x0C0F;
  sub_2E29();
  _pop(cx);
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_4EA6;
loc_code_4EA3:
  if ( --cx )
    goto loc_code_4E78;
  return;
loc_code_4EA6:
  _push(cx);
  if ( _data[ds*16+0x45BE] != 0 ) // jnz 
    goto loc_code_4EBB;
  sub_11E3();
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_4EBB;
  sub_622B();
loc_code_4EBB:
  sub_4F4A();
  _pop(cx);
  bx = cx;
  bx--;
  _data[bx + 0x2B72] = 0;
  dl = _data[bx + 0x2B6A];
  bl <<= 1;
  cx = *(WORD*)&_data[bx + 0x2B5A];
  sub_2CB0();
  di = ax;
  si = 0x2B7A;
  ax = 0x0B800;
  es = ax;
  cx = 0x0F03;
  sub_2D9D();
  if ( _data[ds*16+0x45BE] != 0 ) // jnz 
    goto loc_code_4EF8;
  if ( _data[ds*16+0x70F2] == 0 ) // jz 
    goto loc_code_4EF5;
  sub_61FA();
loc_code_4EF5:
  sub_1145();
loc_code_4EF8:
  dx = 0;
  if ( *(WORD*)&_data[ds*16+0x45B6] == 6 ) // jz 
    goto loc_code_4F0B;
  ah = 0;
  _int(0x1A);
  if ( dx != 0 ) // jnz 
    goto loc_code_4F0B;
  dx--;
loc_code_4F0B:
  *(WORD*)&_data[ds*16+0x454F] = dx;
}

void sub_4F10()
{
  _data[ds*16+0x454E] = 0;
  si = 0x4500;
  if ( _data[ds*16+0x454A] == 0 ) // jz 
    goto loc_code_4F3E;
  bx = *(WORD*)&_data[ds*16+0x4551];
  if ( _data[ds*16+0x4553] == 0 ) // jz 
    goto loc_code_4F30;
  bl &= 2;
  bl += 0x0C;
loc_code_4F30:
  if ( _data[ds*16+0x454A] != 0x0FF ) // jnz 
    goto loc_code_4F3A;
  bx += 0x10;
loc_code_4F3A:
  si = *(WORD*)&_data[bx + 0x4A60];
loc_code_4F3E:
  di = *(WORD*)&_data[ds*16+0x45BA];
  *(WORD*)&_data[ds*16+0x454C] = di;
  sub_4FDF();
}

void sub_4F4A()
{
  if ( _data[ds*16+0x454E] != 0 ) // jnz 
    return;
  di = *(WORD*)&_data[ds*16+0x454C];
  sub_5008();
}

void sub_4F59()
{
  *(WORD*)&_data[ds*16+0x45B6] = 0;
loc_code_4F5F:
  sub_2DFD();
  dx &= 0x7F;
  dx += 0x60;
  *(WORD*)&_data[ds*16+0x4548] = dx;
  _data[ds*16+0x454A] = 0;
  _data[ds*16+0x454E] = 1;
  *(WORD*)&_data[ds*16+0x4551] = 0;
  _data[ds*16+0x4553] = 0;
  dx = 0;
  if ( *(WORD*)&_data[ds*16+0x45B6] != 0 ) // jnz 
    goto loc_code_4F95;
  ah = 0;
  _int(0x1A);
  if ( dx != 0 ) // jnz 
    goto loc_code_4F95;
  dx--;
loc_code_4F95:
  *(WORD*)&_data[ds*16+0x454F] = dx;
  bx = *(WORD*)&_data[ds*16+0x45B6];
  al = _data[bx + 0x2BD4];
  al += 3;
  _data[ds*16+0x454B] = al;
  sub_4FBB();
  (*(WORD*)&_data[ds*16+0x45B6])++;
  if ( *(WORD*)&_data[ds*16+0x45B6] < 7 ) // jb 
    goto loc_code_4F5F;
  *(WORD*)&_data[ds*16+0x45B6] = 0;
}

void sub_4FBB()
{
  _push(ds);
  _pop(es);
  bl <<= 1;
  _cld();
  di = *(WORD*)&_data[bx + 0x45A8];
  si = 0x4548;
  cx = 0x0C;
  _rep_movsb();
}

void sub_4FCD()
{
  _push(ds);
  _pop(es);
  bl <<= 1;
  _cld();
  si = *(WORD*)&_data[bx + 0x45A8];
  di = 0x4548;
  cx = 0x0C;
  _rep_movsb();
}

void sub_4FDF()
{
  ax = 0x0B800;
  es = ax;
  _cld();
  dh = 0x0C;
loc_code_4FE7:
  cx = 3;
loc_code_4FEA:
  bx = *(WORD*)&_data[es*16+di];
  _lodsw();
  ax |= bx;
  _stosw();
  if ( --cx )
    goto loc_code_4FEA;
  di -= 6;
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_5003;
  di += 0x50;
loc_code_5003:
  dh--;
  if ( dh ) // jnz 
    goto loc_code_4FE7;
}

void sub_5008()
{
  ax = 0x0B800;
  es = ax;
  _cld();
  dh = 0x0C;
  ax = 0x5555;
loc_code_5013:
  cx = 3;
  _rep_stosw();
  di -= 6;
  di ^= 0x2000;
  if ( di & 0x2000 ) // jnz 
    goto loc_code_5028;
  di += 0x50;
loc_code_5028:
  dh--;
  if ( dh ) // jnz 
    goto loc_code_5013;
}

void sub_502D()
{
  if ( _data[ds*16+0x70F2] != 0 ) // jnz 
    goto loc_code_5036;
  _clc();
  return;
loc_code_5036:
  ax = *(WORD*)&_data[ds*16+0x70F3];
  dl = _data[ds*16+0x70F5];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x4548];
  dh = _data[ds*16+0x454B];
  di = 0x18;
  cx = 0x0C08;
  sub_2E29();
}

/*
  unknown_command(); // align 10h
*/
void sub_5060()
{
  ax = 0x0B800;
  es = ax;
  ax = *(WORD*)&_data[ds*16+0x579];
  if ( ax < 0x117 ) // jb 
    goto loc_code_5070;
  ax = 0x116;
loc_code_5070:
  cf = (ax < 0x10); // cf-insertion
  ax -= 0x10;
  if ( !cf ) // jnb 
    goto loc_code_5077;
  ax = 0;
loc_code_5077:
  ax &= 0x0FF0;
  *(WORD*)&_data[ds*16+0x579] = ax;
  _data[ds*16+0x57B] = 0x14;
  cf = (ax < 0x80); // cf-insertion
  ax -= 0x80;
  if ( !cf ) // jnb 
    goto loc_code_5089;
  ax = ~ax;
loc_code_5089:
  cl = 3;
  ax >>= cl;
  if ( ax <= 0x0D ) // jbe 
    goto loc_code_5095;
  ax = 0x0D;
loc_code_5095:
  ax += 2;
  *(WORD*)&_data[ds*16+0x4D6A] = ax;
  *(WORD*)&_data[ds*16+0x4DD6] = 0x0A;
loc_code_50A1:
  if ( *(WORD*)&_data[ds*16+0x4DD6] == 0x0A ) // jz 
    goto loc_code_50AB;
  sub_5B63();
loc_code_50AB:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x4A80] = dx;
  ax = *(WORD*)&_data[ds*16+0x579];
  cx = ax;
  cx &= 0x0FF0;
  if ( cx != 0x80 ) // jnz 
    goto loc_code_50C6;
  ax = cx;
  goto loc_code_50D2;
loc_code_50C6:
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_50CE;
  ax -= *(WORD*)&_data[ds*16+0x4D6A];
  goto loc_code_50D2;
loc_code_50CE:
  ax += *(WORD*)&_data[ds*16+0x4D6A];
loc_code_50D2:
  *(WORD*)&_data[ds*16+0x579] = ax;
  if ( _data[ds*16+0x57B] < 0x54 ) // jb 
    goto loc_code_50DD;
  return;
loc_code_50DD:
  _data[ds*16+0x57B] += 8;
  cx = *(WORD*)&_data[ds*16+0x579];
  cx += 4;
  dl = _data[ds*16+0x57B];
  sub_2CB0();
  di = ax;
  *(WORD*)&_data[ds*16+0x4DD8] = di;
  si = 0x4B8A;
  bp = 0x0E;
  cx = 0x2007;
  sub_2CCC();
  di = *(WORD*)&_data[ds*16+0x4DD8];
  di += 0x0F3;
  si = 0x4A82;
  cx = 0x0D04;
  sub_2D9D();
  if ( *(WORD*)&_data[ds*16+0x4DD6] != 0x0A ) // jnz 
    goto loc_code_5120;
  sub_572E();
  sub_5B54();
loc_code_5120:
  sub_5B63();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x4A80];
  if ( dx < *(WORD*)&_data[ds*16+0x4DD6] ) // jb 
    goto loc_code_5120;
  if ( *(WORD*)&_data[ds*16+0x4DD6] != 0x0A ) // jnz 
    goto loc_code_5141;
  sub_38B0();
  bx = 0;
  ah = 0x0B;
  _int(0x10);
loc_code_5141:
  *(WORD*)&_data[ds*16+0x4DD6] = 2;
  goto loc_code_50A1;
}

void sub_514A()
{
  cx = 3;
loc_code_514D:
  bx = 3;
  bx -= cx;
  bx <<= 1;
  ax = *(WORD*)&_data[bx + 0x4DA4];
  *(WORD*)&_data[ds*16+0x4D6A] = ax;
  ax = *(WORD*)&_data[bx + 0x4DAA];
  *(WORD*)&_data[ds*16+0x4D6C] = ax;
  ax = *(WORD*)&_data[bx + 0x4D98];
  *(WORD*)&_data[ds*16+0x4DCC] = ax;
  ax = *(WORD*)&_data[bx + 0x4D9E];
  *(WORD*)&_data[ds*16+0x4DCE] = ax;
  ax = *(WORD*)&_data[bx + 0x4DB0];
  *(WORD*)&_data[ds*16+0x4DD0] = ax;
  ax = *(WORD*)&_data[bx + 0x4DB6];
  *(WORD*)&_data[ds*16+0x4DD2] = ax;
  ax = *(WORD*)&_data[bx + 0x4DBC];
  *(WORD*)&_data[ds*16+0x4DD4] = ax;
  ax = *(WORD*)&_data[bx + 0x4D92];
  *(WORD*)&_data[ds*16+0x4DCA] = ax;
  ax = *(WORD*)&_data[bx + 0x4DC2];
  *(WORD*)&_data[ds*16+0x4DC8] = ax;
  _push(cx);
  sub_519B();
  _pop(cx);
  if ( --cx )
    goto loc_code_514D;
}

void sub_519B()
{
  cx = 8;
  _data[ds*16+0x4D91] = 1;
loc_code_51A3:
  _push(cx);
  sub_5B63();
  _pop(cx);
  bx = cx;
  bx--;
  bx <<= 1;
  ax = *(WORD*)&_data[ds*16+0x4DCC];
  *(WORD*)&_data[bx + 0x4D4A] = ax;
  ax = *(WORD*)&_data[ds*16+0x4DCE];
  *(WORD*)&_data[bx + 0x4D5A] = ax;
  if ( --cx )
    goto loc_code_51A3;
  ax = 0x0B800;
  es = ax;
  _data[ds*16+0x4D6E] = 0;
loc_code_51C7:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x4A80] = dx;
  cx = 8;
loc_code_51D2:
  _push(cx);
  sub_5B63();
  _pop(cx);
  bx = cx;
  bx--;
  bx <<= 1;
  _push(cx);
  _push(bx);
  if ( _data[ds*16+0x4D91] == 0 ) // jz 
    goto loc_code_51EA;
  if ( cx != 8 ) // jnz 
    goto loc_code_5205;
loc_code_51EA:
  cx = *(WORD*)&_data[bx + 0x4D4A];
  dx = *(WORD*)&_data[bx + 0x4D5A];
  sub_2CB0();
  di = ax;
  si = *(WORD*)&_data[ds*16+0x4DCA];
  bp = 0x0E;
  cx = *(WORD*)&_data[ds*16+0x4DD4];
  sub_2CCC();
loc_code_5205:
  _pop(bx);
  _pop(cx);
  sub_522A();
  if ( --cx )
    goto loc_code_51D2;
loc_code_520C:
  sub_5B63();
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x4A80];
  if ( dx < *(WORD*)&_data[ds*16+0x4DC8] ) // jb 
    goto loc_code_520C;
  _data[ds*16+0x4D91] = 0;
  if ( _data[ds*16+0x4D6E] == 0 ) // jz 
    goto loc_code_51C7;
}

void sub_522A()
{
  ax = *(WORD*)&_data[bx + 0x4D4A];
  if ( *(WORD*)&_data[bx + 0x4D6F] < 1 ) // jb 
    goto loc_code_525A;
  if ( unknown_condition() ) // jnz 
    goto loc_code_524A;
  ax += *(WORD*)&_data[ds*16+0x4D6A];
  if ( ax <= *(WORD*)&_data[ds*16+0x4DD0] ) // jbe 
    goto loc_code_5256;
  ax = *(WORD*)&_data[ds*16+0x4DD0];
  (_data[ds*16+0x4D6E])++;
  goto loc_code_5256;
loc_code_524A:
  cf = (ax < *(WORD*)&_data[ds*16+0x4D6A]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x4D6A];
  if ( !cf ) // jnb 
    goto loc_code_5256;
  ax = 0;
  (_data[ds*16+0x4D6E])++;
loc_code_5256:
  *(WORD*)&_data[bx + 0x4D4A] = ax;
loc_code_525A:
  ax = *(WORD*)&_data[bx + 0x4D5A];
  if ( *(WORD*)&_data[bx + 0x4D7F] < 1 ) // jb 
    return;
  if ( unknown_condition() ) // jnz 
    goto loc_code_527A;
  ax += *(WORD*)&_data[ds*16+0x4D6C];
  if ( ax <= *(WORD*)&_data[ds*16+0x4DD2] ) // jbe 
    goto loc_code_5286;
  ax = *(WORD*)&_data[ds*16+0x4DD2];
  (_data[ds*16+0x4D6E])++;
  goto loc_code_5286;
loc_code_527A:
  cf = (ax < *(WORD*)&_data[ds*16+0x4D6C]); // cf-insertion
  ax -= *(WORD*)&_data[ds*16+0x4D6C];
  if ( !cf ) // jnb 
    goto loc_code_5286;
  ax = 0;
  (_data[ds*16+0x4D6E])++;
loc_code_5286:
  *(WORD*)&_data[bx + 0x4D5A] = ax;
}

void sub_528B()
{
  sub_5B54();
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_529C;
  ah = 0x0B;
  bx = 0x101;
  _int(0x10);
loc_code_529C:
  sub_5060();
  sub_514A();
  sub_5BBF();
  if ( _data[ds*16+0x1F80] >= 9 ) // jnb 
    goto loc_code_52B0;
  (_data[ds*16+0x1F80])++;
loc_code_52B0:
  if ( *(WORD*)&_data[ds*16+8] >= 7 ) // jnb 
    goto loc_code_52BB;
  (*(WORD*)&_data[ds*16+8])++;
loc_code_52BB:
  *(WORD*)&_data[ds*16+0x414] = 0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x412] = dx;
  sub_5B21();
}

/*
  unknown_command(); // align 4
*/
void sub_52D0()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x52C4] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x52C4] = dx;
  bx = *(WORD*)&_data[ds*16+0x52C6];
  *(WORD*)&_data[ds*16+0x52C6] += 2;
  ax = *(WORD*)&_data[bx + 0x52CA];
  if ( ax != *(WORD*)&_data[ds*16+0x52C8] ) // jnz 
    goto loc_code_52FC;
  sub_5B21();
  return;
loc_code_52FC:
  *(WORD*)&_data[ds*16+0x52C8] = ax;
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x52C8];
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5313()
{
  if ( *(WORD*)&_data[ds*16+8] < 2 ) // jb 
    return;
  *(WORD*)&_data[ds*16+0x5016] = 0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x52C0] = dx;
  *(WORD*)&_data[ds*16+0x52C2] = dx;
  *(WORD*)&_data[ds*16+0x52C4] = dx;
  *(WORD*)&_data[ds*16+0x52C6] = 0;
  *(WORD*)&_data[ds*16+0x52C8] = 0;
loc_code_533C:
  sub_5368();
  *(WORD*)&_data[ds*16+0x5016] ^= 2;
loc_code_5345:
  sub_52D0();
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x52C0];
  if ( ax < 5 ) // jb 
    goto loc_code_5345;
  *(WORD*)&_data[ds*16+0x52C0] = dx;
  dx -= *(WORD*)&_data[ds*16+0x52C2];
  if ( dx < 0x28 ) // jb 
    goto loc_code_533C;
  sub_5B21();
}

void sub_5368()
{
  ax = 0x0B800;
  es = ax;
  bx = *(WORD*)&_data[ds*16+8];
  bx <<= 1;
  ax = *(WORD*)&_data[bx + 0x52AE];
  *(WORD*)&_data[ds*16+0x5010] = ax;
loc_code_537A:
  bx = *(WORD*)&_data[ds*16+0x5010];
  di = *(WORD*)&_data[bx];
  if ( di != 0 ) // jnz 
    goto loc_code_5386;
  return;
loc_code_5386:
  bx = *(WORD*)&_data[bx + 2];
  bx ^= *(WORD*)&_data[ds*16+0x5016];
  bx &= 2;
  si = *(WORD*)&_data[bx + 0x5012];
  cx = 0x2304;
  sub_2D9D();
  sub_52D0();
  *(WORD*)&_data[ds*16+0x5010] += 4;
  goto loc_code_537A;
}

/*
  unknown_command(); // align 10h
*/
void sub_53B0()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x5322] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x5322] = dx;
  bx = *(WORD*)&_data[ds*16+0x5320];
  bl = _data[bx + 0x538C];
  if ( bl == 0x66 ) // jz 
    goto loc_code_53DD;
  bh = 0;
  (*(WORD*)&_data[ds*16+0x5320])++;
  if ( bx != 0 ) // jnz 
    goto loc_code_53E1;
loc_code_53DD:
  sub_5B21();
  return;
loc_code_53E1:
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[bx + 0x5324];
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

/*
  unknown_command(); // align 10h
*/
void sub_5400()
{
  ax = 0x0B800;
  es = ax;
  bx = *(WORD*)&_data[ds*16+8];
  bx &= 7;
  bx <<= 1;
  ax = bx;
  bx = *(WORD*)&_data[bx + 0x5908];
  cl = 3;
  ax <<= cl;
  *(WORD*)&_data[ds*16+0x5918] = ax;
loc_code_541C:
  di = *(WORD*)&_data[bx];
  if ( di == 0x0FFFF ) // jz 
    return;
  sub_2DFD();
  dx &= 0x0E;
  dx += *(WORD*)&_data[ds*16+0x5918];
  si = dx;
  si = *(WORD*)&_data[si + 0x5888];
  cx = *(WORD*)&_data[si + 0x5858];
  si = *(WORD*)&_data[si + 0x584C];
  _push(bx);
  sub_2D9D();
  _pop(bx);
  bx += 2;
  goto loc_code_541C;
}

/*
  unknown_command(); // align 10h
*/
void sub_5450()
{
  _data[ds*16+0x5B0F] = 0x0C;
  *(WORD*)&_data[ds*16+0x5B0C] = 1;
  *(WORD*)&_data[ds*16+0x5B12] = 0x1FF;
  *(WORD*)&_data[ds*16+0x5B0A] = 0x0F;
  _data[ds*16+0x5B0E] = 1;
}

void sub_546D()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  if ( _data[ds*16+0x1CB8] == 0 ) // jz 
    goto loc_code_54F8;
  ah = 0;
  _int(0x1A);
  if ( _data[ds*16+0x5B0F] != 0 ) // jnz 
    goto loc_code_54A6;
  if ( dx == *(WORD*)&_data[ds*16+0x5B10] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x5B10] = dx;
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x5B12];
  ax &= 0x1FF;
  ax += 0x0C8;
  sub_5889();
  *(WORD*)&_data[ds*16+0x5B12] -= 0x4B;
  return;
loc_code_54A6:
  if ( dx == *(WORD*)&_data[ds*16+0x5B10] ) // jz 
    goto loc_code_54B4;
  *(WORD*)&_data[ds*16+0x5B10] = dx;
  (_data[ds*16+0x5B0F])--;
loc_code_54B4:
  (_data[ds*16+0x5B0E])--;
  if ( _data[ds*16+0x5B0E] ) // jnz 
    return;
  al = 1;
  if ( _data[ds*16+0x697] == 0x0FD ) // jz 
    goto loc_code_54C5;
  al <<= 1;
loc_code_54C5:
  _data[ds*16+0x5B0E] = al;
  sub_2DFD();
  if ( dl > 4 ) // ja 
    goto loc_code_54D4;
  (*(WORD*)&_data[ds*16+0x5B0C])++;
loc_code_54D4:
  if ( !(*(WORD*)&_data[ds*16+0x5B0C] & 1) ) // jz 
    goto loc_code_54E1;
  *(WORD*)&_data[ds*16+0x5B0A] += 7;
loc_code_54E1:
  al = 0x0B6;
  _out(0x43, al);
  sub_2DFD();
  ax = dx;
  ax &= *(WORD*)&_data[ds*16+0x5B0A];
  ax &= 0x1FF;
  ax += 0x190;
  sub_5889();
  return;
loc_code_54F8:
  ah = 0;
  _int(0x1A);
  if ( _data[ds*16+0x5920] == 0 ) // jz 
    goto loc_code_5522;
  if ( dx == *(WORD*)&_data[ds*16+0x5921] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x5921] = dx;
  (_data[ds*16+0x5920])--;
  if ( !_data[ds*16+0x5920] ) // jz 
    goto loc_code_551E;
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x5923];
  sub_5889();
  return;
loc_code_551E:
  sub_5B21();
  return;
loc_code_5522:
  if ( dx == *(WORD*)&_data[ds*16+0x5925] ) // jz 
    return;
  si = 3;
  al = _data[ds*16+0x1CBF];
  al |= *(WORD*)&_data[ds*16+0x5B07];
  if ( al ) // jnz 
    goto loc_code_5549;
  si = 1;
  if ( *(WORD*)&_data[ds*16+4] != 0 ) // jnz 
    goto loc_code_5549;
  si--;
  if ( _data[ds*16+0x1673] == 0 ) // jz 
    goto loc_code_5549;
  si = 2;
loc_code_5549:
  di = si;
  di <<= 1;
  al = _data[ds*16+0x584];
  al |= *(WORD*)&_data[ds*16+0x5B07];
  if ( al ) // jnz 
    goto loc_code_5563;
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x5925];
  if ( ax >= *(WORD*)&_data[di + 0x59F2] ) // jnb 
    goto loc_code_5563;
  return;
loc_code_5563:
  *(WORD*)&_data[ds*16+0x5925] = dx;
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    goto loc_code_5579;
  if ( _data[ds*16+0x5B07] == 0 ) // jz 
    goto loc_code_559E;
  (_data[ds*16+0x5B07])--;
loc_code_5579:
  *(WORD*)&_data[ds*16+0x592E] = 0x1200;
  bx = *(WORD*)&_data[ds*16+0x59BA];
  if ( bx < 6 ) // jb 
    goto loc_code_558E;
  bx = 0;
  *(WORD*)&_data[ds*16+0x59BA] = bx;
loc_code_558E:
  *(WORD*)&_data[ds*16+0x59BA] += 2;
  ax = *(WORD*)&_data[bx + 0x5A44];
  *(WORD*)&_data[ds*16+0x592A] = ax;
  sub_5B28();
  return;
loc_code_559E:
  if ( si != 2 ) // jnz 
    goto loc_code_55BB;
  al = _data[ds*16+0x1673];
  ah = 0;
  cl = 4;
  ax <<= cl;
  ax += 0x200;
  *(WORD*)&_data[ds*16+0x592A] = ax;
  *(WORD*)&_data[ds*16+0x592E] = 0x1800;
  goto loc_code_568D;
loc_code_55BB:
  ax = *(WORD*)&_data[di + 0x5A02];
  *(WORD*)&_data[ds*16+0x592E] = ax;
  cf = _data[ds*16+0x5927] & 1;
  _data[ds*16+0x5927] >>= 1;
  if ( !cf ) // jnb cf=0
    goto loc_code_5623;
  *(WORD*)&_data[ds*16+0x592E] = 0x1000;
  _data[ds*16+0x5927] = 0x80;
  (_data[ds*16+0x5928])++;
  al = _data[ds*16+0x5928];
  al &= *(WORD*)&_data[si + 0x59FA];
  if ( al ) // jnz 
    goto loc_code_5616;
  dl = _data[si + 0x5A0A];
  *(WORD*)&_data[ds*16+0x5929] += dl;
  sub_2DFD();
  if ( dl > _data[si + 0x5A0C] ) // ja 
    goto loc_code_55F8;
  dl &= 7;
  _data[ds*16+0x592D] = dl;
loc_code_55F8:
  sub_2DFD();
  dx &= 0x0FF;
  dx <<= 1;
  cl = 1;
  if ( !(dl & 2) ) // jz 
    goto loc_code_560E;
  cl = 0x0FF;
  dx += 0x300;
loc_code_560E:
  *(WORD*)&_data[ds*16+0x592A] = dx;
  _data[ds*16+0x592C] = cl;
loc_code_5616:
  ah = _data[ds*16+0x5929];
  ah &= *(WORD*)&_data[si + 0x59FC];
  al |= ah;
  _data[ds*16+0x5928] = al;
loc_code_5623:
  if ( _data[ds*16+0x592C] == 0x0FF ) // jz 
    goto loc_code_5640;
  *(WORD*)&_data[ds*16+0x5A54] += 2;
  bx = *(WORD*)&_data[ds*16+0x5A54];
  bx &= 0x0E;
  ax = *(WORD*)&_data[bx + 0x5A44];
  *(WORD*)&_data[ds*16+0x592A] = ax;
  goto loc_code_5653;
loc_code_5640:
  if ( *(WORD*)&_data[ds*16+0x592A] > 0x0C8 ) // ja 
    goto loc_code_564E;
  *(WORD*)&_data[ds*16+0x592A] = 0x500;
loc_code_564E:
  *(WORD*)&_data[ds*16+0x592A] -= 0x19;
loc_code_5653:
  if ( _data[ds*16+0x584] == 0 ) // jz 
    goto loc_code_5667;
  *(WORD*)&_data[ds*16+0x592E] = 0x2000;
  _data[ds*16+0x592C] = 0x0FF;
  if ( unknown_condition() ) // jnz 
    goto loc_code_568D;
loc_code_5667:
  bl = _data[ds*16+0x5928];
  bh = 0;
  bx += *(WORD*)&_data[di + 0x59FE];
  al = _data[bx + 0x59C2];
  al &= *(WORD*)&_data[ds*16+0x5927];
  if ( al ) // jnz 
    goto loc_code_568D;
  if ( _data[ds*16+0x592D] == 0 ) // jz 
    return;
  (_data[ds*16+0x592D])--;
  ax = *(WORD*)&_data[di + 0x5A06];
  *(WORD*)&_data[ds*16+0x592E] = ax;
loc_code_568D:
  sub_5B28();
}

void sub_5691()
{
  sub_5B21();
  ah = 0x0B;
  bx = 4;
  _int(0x10);
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5AE2] = dx;
  *(WORD*)&_data[ds*16+0x5AE4] = 0;
  al = 2;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_56B4;
  al >>= 1;
loc_code_56B4:
  _data[ds*16+0x5B06] = al;
loc_code_56B7:
  if ( _data[ds*16+0] == 0 ) // jz 
    goto loc_code_56D8;
  (*(WORD*)&_data[ds*16+0x5AE4])++;
  bx = *(WORD*)&_data[ds*16+0x5AE4];
  cl = _data[ds*16+0x5B06];
  bx >>= cl;
  bx &= 0x1F;
  _in(al, 0x61);
  al ^= *(WORD*)&_data[bx + 0x5AE6];
  _out(0x61, al);
loc_code_56D8:
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x5AE2];
  if ( dx < 2 ) // jb 
    goto loc_code_56B7;
  ah = 0x0B;
  bx = 0;
  _int(0x10);
  _data[ds*16+0x5B07] = 0x0C;
  sub_5B21();
}

void sub_56F4()
{
  ax = 0x200;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_5700;
  ax <<= 1;
loc_code_5700:
  *(WORD*)&_data[ds*16+0x5AD0] = ax;
}

void sub_5704()
{
  (*(WORD*)&_data[ds*16+0x5AD0])++;
  bx = *(WORD*)&_data[ds*16+0x5AD0];
  dx = bx;
  cl = 9;
  dx >>= cl;
  cl = dl;
  cl &= 0x0F;
  bx >>= cl;
  bx &= 0x0F;
  dl = _data[bx + 0x5AD2];
  dl &= *(WORD*)&_data[ds*16+0];
  _in(al, 0x61);
  al &= 0x0FC;
  al |= dl;
  _out(0x61, al);
}

void sub_572E()
{
  *(WORD*)&_data[ds*16+0x5ACB] = 0x1F4;
loc_code_5734:
  sub_576E();
  *(WORD*)&_data[ds*16+0x5ACB] -= 0x1E;
  if ( *(WORD*)&_data[ds*16+0x5ACB] > 0x0C8 ) // ja 
    goto loc_code_5734;
  *(WORD*)&_data[ds*16+0x5ACB] = 0x1F4;
loc_code_574A:
  sub_576E();
  *(WORD*)&_data[ds*16+0x5ACB] -= 0x14;
  if ( *(WORD*)&_data[ds*16+0x5ACB] > 0x12C ) // ja 
    goto loc_code_574A;
loc_code_575A:
  sub_576E();
  *(WORD*)&_data[ds*16+0x5ACB] += 0x1E;
  if ( *(WORD*)&_data[ds*16+0x5ACB] < 0x320 ) // jb 
    goto loc_code_575A;
  sub_5B21();
}

void sub_576E()
{
  cx = 0x1000;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_577A;
  cx >>= 1;
loc_code_577A:
  if ( --cx )
    goto loc_code_577A;
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x5ACB];
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5797()
{
  sub_5B21();
  _data[ds*16+0x5ACF] = 0;
  *(WORD*)&_data[ds*16+0x5ACD] = 8;
}

void sub_57A6()
{
  (_data[ds*16+0x5ACF])++;
  dl = 0;
  al = _data[ds*16+0x5ACF];
  al &= 0x3F;
  if ( al ) // jnz 
    goto loc_code_57B7;
  (*(WORD*)&_data[ds*16+0x5ACD])++;
loc_code_57B7:
  bx = *(WORD*)&_data[ds*16+0x5ACD];
  cl = 2;
  bx >>= cl;
  bl &= 0x1F;
  if ( al < bl ) // jb 
    goto loc_code_57C8;
  dl = 2;
loc_code_57C8:
  dl &= *(WORD*)&_data[ds*16+0];
  _in(al, 0x61);
  al &= 0x0FD;
  al |= dl;
  _out(0x61, al);
}

void sub_57D5()
{
  *(WORD*)&_data[ds*16+0x5A85] = 0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5A83] = dx;
}

void sub_57E4()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x5A83];
  if ( ax < 2 ) // jb 
    return;
  *(WORD*)&_data[ds*16+0x5A83] = dx;
  bx = *(WORD*)&_data[ds*16+0x5A85];
  *(WORD*)&_data[ds*16+0x5A85] += 2;
  if ( _data[ds*16+0x552] == 0 ) // jz 
    goto loc_code_581B;
  ax = *(WORD*)&_data[bx + 0x5AA3];
  if ( ax != 0 ) // jnz 
    goto loc_code_581F;
  sub_5B21();
  return;
loc_code_581B:
  ax = *(WORD*)&_data[bx + 0x5A87];
loc_code_581F:
  _push(ax);
  al = 0x0B6;
  _out(0x43, al);
  _pop(ax);
  sub_5889();
}

void sub_5829()
{
  *(WORD*)&_data[ds*16+0x5A62] = 0;
  _data[ds*16+0x5A82] = 0;
}

void sub_5835()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x5A80] ) // jnz 
    goto loc_code_5847;
  return;
loc_code_5847:
  *(WORD*)&_data[ds*16+0x5A80] = dx;
  (_data[ds*16+0x5A82])++;
  al = 0x0B6;
  _out(0x43, al);
  bx = *(WORD*)&_data[ds*16+0x5A62];
  if ( _data[ds*16+0x5A82] & 1 ) // jnz 
    goto loc_code_5861;
  bx += 2;
loc_code_5861:
  ax = *(WORD*)&_data[bx + 0x5A64];
  sub_5889();
}

void sub_5869()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  _push(bx);
  _push(ax);
  al = 0x0B6;
  _out(0x43, al);
  bx = *(WORD*)&_data[ds*16+0x5A62];
  *(WORD*)&_data[ds*16+0x5A62] += 2;
  ax = *(WORD*)&_data[bx + 0x5A64];
  sub_5889();
  _pop(ax);
  _pop(bx);
}

void sub_5889()
{
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5897()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  _push(ax);
  _push(cx);
  _push(dx);
  al = 0x0B6;
  _out(0x43, al);
  bx = *(WORD*)&_data[ds*16+0x5A56];
  bx &= 6;
  *(WORD*)&_data[ds*16+0x5A56] += 2;
  ax = *(WORD*)&_data[bx + 0x5A5A];
  sub_5889();
  _pop(dx);
  _pop(cx);
  _pop(ax);
}

void sub_58BD()
{
  _data[ds*16+0x5927] = 0x80;
  _data[ds*16+0x5928] = 0;
  _data[ds*16+0x5929] = 0;
  *(WORD*)&_data[ds*16+0x592A] = 0x500;
  _data[ds*16+0x592C] = 0x0FF;
  _data[ds*16+0x592D] = 0;
  _data[ds*16+0x5920] = 0;
  _data[ds*16+0x5B07] = 0;
  *(WORD*)&_data[ds*16+0x5B08] = 0;
  *(WORD*)&_data[ds*16+0x5B0C] = 1;
  _data[ds*16+0x5B0E] = 1;
}

void sub_58F8()
{
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    goto loc_code_5908;
  bx = 0x390;
  cx = 0x1800;
  sub_59A3();
loc_code_5908:
  _data[ds*16+0x127C] = 0;
}

void sub_590E()
{
  if ( _data[ds*16+0x1CBF] != 0 ) // jnz 
    return;
  bx = 0x400;
  cx = 0x1800;
  sub_59A3();
}

void sub_591F()
{
  bx = 0x7D0;
  cx = 0x1800;
  sub_59A3();
  bx = 0x0A6E;
  cx = 0x1800;
  sub_59A3();
  bx = 0x0DEC;
  cx = 0x1800;
  sub_59A3();
}

void sub_593B()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x5923] = bx;
  _push(ax);
  al = 0x0B6;
  _out(0x43, al);
  _pop(ax);
  sub_5889();
  _data[ds*16+0x5920] = 2;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5921] = dx;
}

void sub_595D()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  if ( _data[ds*16+0x5920] != 0 ) // jnz 
    return;
  sub_2DFD();
  ax = dx;
  ax &= 0x7F;
  ax += 0x0AA;
  bx = ax;
  ax += 0x1E;
  sub_593B();
}

void sub_597F()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ax = 0x1200;
  bx = 0x1312;
  ax += *(WORD*)&_data[ds*16+0x5B08];
  bx += *(WORD*)&_data[ds*16+0x5B08];
  *(WORD*)&_data[ds*16+0x5B08] += 0x15E;
  sub_593B();
  _data[ds*16+0x5B07] = 0x18;
}

void sub_59A3()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  al = 0x0B6;
  _out(0x43, al);
  ax = bx;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_59C5;
  cx >>= 1;
loc_code_59C5:
  if ( --cx )
    goto loc_code_59C5;
  sub_5B21();
}

void sub_59CB()
{
  _in(al, 0x61);
  al &= 0x0FE;
  _out(0x61, al);
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5A40] = dx;
  *(WORD*)&_data[ds*16+0x5A42] = 0;
loc_code_59DF:
  ax = *(WORD*)&_data[ds*16+0x5A42];
  cl = 6;
  ax >>= cl;
  if ( unknown_condition() ) // jnz 
    goto loc_code_59E9;
  ax++;
loc_code_59E9:
  cx = ax;
loc_code_59EB:
  _push(cx);
  ah = 0;
  _int(0x1A);
  _pop(cx);
  dx -= *(WORD*)&_data[ds*16+0x5A40];
  if ( dx < 2 ) // jb 
    goto loc_code_59EB;
  if ( dx >= 7 ) // jnb 
    goto loc_code_5A18;
  if ( --cx )
    goto loc_code_59EB;
  sub_2DFD();
  dl &= 2;
  dl &= *(WORD*)&_data[ds*16+0];
  _in(al, 0x61);
  al ^= dl;
  _out(0x61, al);
  *(WORD*)&_data[ds*16+0x5A42] += 7;
  goto loc_code_59DF;
loc_code_5A18:
  sub_5B21();
}

void sub_5A1C()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  sub_13B7();
  bx = *(WORD*)&_data[ds*16+0x5A16];
  cf = (bx < ax); // cf-insertion
  bx -= ax;
  if ( cf ) // jb 
    goto loc_code_5A35;
  if ( bx > 0x260 ) // ja 
    goto loc_code_5A35;
  return;
loc_code_5A35:
  *(WORD*)&_data[ds*16+0x5A16] = ax;
  al = 0x0B6;
  _out(0x43, al);
  (*(WORD*)&_data[ds*16+0x5A18])++;
  bx = *(WORD*)&_data[ds*16+0x5A18];
  bx &= 0x1E;
  ax = *(WORD*)&_data[ds*16+0x5A3C];
  ax &= 0x3FF;
  if ( ax < 0x180 ) // jb 
    goto loc_code_5A59;
  cx = 0x180;
  cx -= ax;
  _xchg(ax, cx);
loc_code_5A59:
  ax >>= 1;
  ax >>= 1;
  ax += *(WORD*)&_data[bx + 0x5A1A];
  bx = 1;
  if ( _data[ds*16+0x697] != 0x0FD ) // jnz 
    goto loc_code_5A6D;
  bl <<= 1;
loc_code_5A6D:
  *(WORD*)&_data[ds*16+0x5A3E] += bx;
  bx <<= 1;
  bx <<= 1;
  *(WORD*)&_data[ds*16+0x5A3C] += bx;
  dx = *(WORD*)&_data[ds*16+0x5A3E];
  cl = 3;
  dx >>= cl;
  ax += dx;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5A90()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x5A14] ) // jnz 
    goto loc_code_5AA2;
  return;
loc_code_5AA2:
  *(WORD*)&_data[ds*16+0x5A14] = dx;
  al = 0x0B6;
  _out(0x43, al);
  sub_2DFD();
  ax = dx;
  ax &= 0x70;
  ax += 0x200;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5AC2()
{
  *(WORD*)&_data[ds*16+0x5A12] = 0x338;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5A10] = dx;
  sub_13B7();
  *(WORD*)&_data[ds*16+0x5A0E] = ax;
loc_code_5AD6:
  sub_13B7();
  dx = ax;
  ax -= *(WORD*)&_data[ds*16+0x5A0E];
  if ( ax < 0x9C40 ) // jb 
    goto loc_code_5B10;
  *(WORD*)&_data[ds*16+0x5A0E] = dx;
  if ( _data[ds*16+0] == 0 ) // jz 
    goto loc_code_5B10;
  al = 0x0B6;
  _out(0x43, al);
  sub_2DFD();
  ax = dx;
  ax &= 0x7FF;
  ax += *(WORD*)&_data[ds*16+0x5A12];
  *(WORD*)&_data[ds*16+0x5A12] -= 2;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
loc_code_5B10:
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x5A10];
  if ( dx < 2 ) // jb 
    goto loc_code_5AD6;
  sub_5B21();
}

void sub_5B21()
{
  _in(al, 0x61);
  al &= 0x0FC;
  _out(0x61, al);
}

void sub_5B28()
{
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x592A];
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
  sub_13B7();
  cx = ax;
loc_code_5B40:
  sub_13B7();
  dx = cx;
  dx -= ax;
  if ( dx < *(WORD*)&_data[ds*16+0x592E] ) // jb 
    goto loc_code_5B40;
  _in(al, 0x61);
  al &= 0x0FC;
  _out(0x61, al);
}

void sub_5B54()
{
  *(WORD*)&_data[ds*16+0x59BE] = 0;
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x59C0] = dx;
}

void sub_5B63()
{
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x59C0];
  if ( ax >= 2 ) // jnb 
    goto loc_code_5B7A;
  return;
loc_code_5B7A:
  *(WORD*)&_data[ds*16+0x59C0] = dx;
  bx = *(WORD*)&_data[ds*16+0x59BE];
  bx &= 0x0FE;
  if ( bx < 0x86 ) // jb 
    goto loc_code_5B92;
  bx = 0;
  *(WORD*)&_data[ds*16+0x59BE] = bx;
loc_code_5B92:
  *(WORD*)&_data[ds*16+0x59BE] += 2;
  ax = *(WORD*)&_data[bx + 0x5934];
  cx = *(WORD*)&_data[ds*16+0x59BC];
  *(WORD*)&_data[ds*16+0x59BC] = ax;
  if ( ax != cx ) // jnz 
    goto loc_code_5BAA;
  sub_5B21();
  return;
loc_code_5BAA:
  cx = ax;
  al = 0x0B6;
  _out(0x43, al);
  ax = cx;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
}

void sub_5BBF()
{
sub_code_5BBF:
  if ( _data[ds*16+0] == 0 ) // jz 
    return;
  sub_5B63();
  if ( *(WORD*)&_data[ds*16+0x59BE] < 0x7C ) // jb 
    goto sub_code_5BBF;
}

/*
  unknown_command(); // align 10h
*/
void sub_5BE0()
{
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x5F66] = dx;
  *(WORD*)&_data[ds*16+0x5F60] = 0;
loc_code_5BEE:
  ax = 0x0B800;
  es = ax;
  bx = *(WORD*)&_data[ds*16+0x5F60];
  *(WORD*)&_data[ds*16+0x5F60] += 2;
  bx &= 2;
  si = *(WORD*)&_data[bx + 0x5F62];
  di = 0x0A74;
  cx = 0x4404;
  sub_2D9D();
loc_code_5C0D:
  sub_57E4();
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[ds*16+0x5F66];
  if ( ax < 4 ) // jb 
    goto loc_code_5C0D;
  *(WORD*)&_data[ds*16+0x5F66] = dx;
  if ( *(WORD*)&_data[ds*16+0x5F60] != 4 ) // jnz 
    goto loc_code_5C36;
  si = 0x5F68;
  di = 0x668;
  cx = 0x1004;
  sub_2D9D();
loc_code_5C36:
  bx = *(WORD*)&_data[ds*16+0x5F60];
  cf = (bx < 8); // cf-insertion
  bx -= 8;
  if ( cf ) // jb 
    goto loc_code_5C51;
  if ( bx >= 6 ) // jnb 
    goto loc_code_5C51;
  si = 0x5FE8;
  di = *(WORD*)&_data[bx + 0x60E4];
  cx = 0x1506;
  sub_2D9D();
loc_code_5C51:
  if ( *(WORD*)&_data[ds*16+0x5F60] < 0x10 ) // jb 
    goto loc_code_5BEE;
  sub_5B21();
}

/*
  unknown_command(); // align 8
*/
void sub_5C60()
{
  _int(0x11);
  al &= 0x30;
  if ( al != 0x30 ) // jnz 
    return;
  ax = 0x0B800;
  ds = ax;
  ax = 0x55AA;
  *(WORD*)&_data[ds*16+0] = ax;
  ax = *(WORD*)&_data[ds*16+0];
  if ( ax != 0x55AA ) // jnz 
    goto loc_code_5C96;
  si = 0x60F0;
  sub_5C9E();
  ax = 0x40;
  ds = ax;
  ax = *(WORD*)&_data[ds*16+0x10];
  al &= 0x0CF;
  al |= 0x10;
  *(WORD*)&_data[ds*16+0x10] = ax;
  ax = 4;
  _int(0x10);
  return;
loc_code_5C96:
  si = 0x6112;
  sub_5C9E();
loc_code_5C9C:
  goto loc_code_5C9C;
}

void sub_5C9E()
{
  ax = seg_data;
  ds = ax;
  sub_5E2B();
}

/*
  unknown_command(); // align 10h
*/
void sub_5CB0()
{
  _cld();
  *(WORD*)&_data[0x4] = 0;
  sub_1830();
  sub_2330();
  sub_2A30();
  ax = 0x0B800;
  es = ax;
  si = 0x6152;
  cx = 0x1D0B;
  di = 0x0BD;
  sub_2D9D();
  si = 0x63D0;
  cx = 0x160E;
  di = 0x69E;
  sub_2D9D();
  si = 0x6638;
  cx = 0x0C03;
  di = 0x0A78;
  sub_2D9D();
  si = 0x6680;
  cx = 0x80E;
  di = 0x0CA8;
  sub_2D9D();
  si = 0x6760;
  cx = 0x0B0C;
  di = 0x1D6E;
  sub_2D9D();
  si = 0x6868;
  cx = 0x804;
  di = 0x1DEC;
  sub_2D9D();
  *(WORD*)&_data[0x6A8D] = 0;
  sub_5E3B();
  *(WORD*)&_data[0x579] = 0;
  sub_70D();
  _data[0x57B] = 0x60;
  _data[0x57C] = 0x92;
  sub_26F2();
  sub_26FC();
  _data[0x1F80] = 9;
  _data[0x1F81] = 0x0FF;
  sub_26B3();
  sub_1E40();
  _data[0x698] = 0;
  _data[0x699] = 0;
  _data[0x6A8A] = 0;
  ax = *(WORD*)&_data[0x693];
  *(WORD*)&_data[0x6150] = ax;
loc_code_5D54:
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[0x6A8B] = dx;
  *(WORD*)&_data[0x5322] = dx;
  *(WORD*)&_data[0x6A93] = dx;
  dx -= 0x30;
  *(WORD*)&_data[0x6A88] = dx;
  *(WORD*)&_data[0x5320] = 0;
loc_code_5D71:
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[0x6A93];
  if ( ax < 0x24 ) // jb 
    goto loc_code_5D89;
  *(WORD*)&_data[0x6A93] = dx;
  _push(dx);
  sub_5E3B();
  _pop(dx);
loc_code_5D89:
  dx -= *(WORD*)&_data[0x6A8B];
  ax = *(WORD*)&_data[0x56DA];
  if ( _data[0x41A] == 0 ) // jz 
    goto loc_code_5DA0;
  ax += 0x48;
  if ( dx >= ax ) // jnb 
    goto loc_code_5D54;
  goto loc_code_5DA7;
loc_code_5DA0:
  ax += 6;
  if ( dx > ax ) // ja 
    return;
loc_code_5DA7:
  sub_53B0();
  sub_5DD4();
  if ( _data[0x69B] == 0 ) // jz 
    goto loc_code_5DCA;
  dx = 0x201;
  _in(al, dx);
  al &= 0x10;
  if ( !al ) // jz 
    goto loc_code_5DC3;
  _data[0x6A8A] = 1;
  goto loc_code_5DCA;
loc_code_5DC3:
  if ( _data[0x6A8A] != 0 ) // jnz 
    return;
loc_code_5DCA:
  ax = *(WORD*)&_data[0x6150];
  if ( ax == *(WORD*)&_data[0x693] ) // jz 
    goto loc_code_5D71;
}

void sub_5DD4()
{
  if ( *(WORD*)&_data[0x579] > 0x20 ) // ja 
    goto loc_code_5DE2;
  _data[0x698] = 1;
  goto loc_code_5E1C;
loc_code_5DE2:
  if ( *(WORD*)&_data[0x579] < 0x120 ) // jb 
    goto loc_code_5DF1;
  _data[0x698] = 0x0FF;
  goto loc_code_5E1C;
loc_code_5DF1:
  ah = 0;
  _int(0x1A);
  ax = dx;
  ax -= *(WORD*)&_data[0x6A88];
  if ( ax < 0x12 ) // jb 
    goto loc_code_5E1C;
  *(WORD*)&_data[0x6A88] = dx;
  sub_2DFD();
  _data[0x698] = 0;
  if ( dl > 0x0A0 ) // ja 
    goto loc_code_5E1C;
  dl &= 1;
  if ( dl ) // jnz 
    goto loc_code_5E18;
  dl = 0x0FF;
loc_code_5E18:
  _data[0x698] = dl;
loc_code_5E1C:
  if ( !sub_13D8() ) // jz 
    return;
  *(WORD*)&_data[0x572] = 4;
  sub_8E5();
}

void sub_5E2B()
{
sub_code_5E2B:
  _lodsb();
  if ( al == 0 ) // jz 
    return;
  _push(si);
  bl = 2;
  ah = 0x0E;
  _int(0x10);
  _pop(si);
  goto sub_code_5E2B;
}

void sub_5E3B()
{
  ax = 0x0B800;
  es = ax;
  *(WORD*)&_data[0x6A8D] += 2;
  bx = *(WORD*)&_data[0x6A8D];
  bx &= 2;
  si = *(WORD*)&_data[bx + 0x6A8F];
  cx = 0x0C0A;
  di = 0x1D38;
  sub_2D9D();
}

void sub_5E5B()
{
  dl = 0;
  bh = dl;
  ah = 2;
  _int(0x10);
}

/*
  unknown_command(); // align 10h
*/
void sub_5E70()
{
  sub_5B21();
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[0x6DFC] = dx;
  *(WORD*)&_data[0x6DFE] = cx;
  _push(ds);
  _push(ds);
  _pop(es);
  ax = 0x0B800;
  ds = ax;
  si = 0x0DCA;
  di = 0x0E;
  cx = 0x1020;
  sub_2DCA();
  _pop(ds);
  dx = 0x0B05;
  bh = 0;
  ah = 2;
  _int(0x10);
  si = 0x6D91;
  _cld();
  sub_5E2B();
  dx = 0x0C05;
  bh = 0;
  ah = 2;
  _int(0x10);
  si = 0x6DB2;
  if ( _data[ds*16+0x69B] == 0 ) // jz 
    goto loc_code_5EBA;
  si = 0x6DD3;
loc_code_5EBA:
  _cld();
  sub_5E2B();
  sub_5F97();
  ax = 0x0B800;
  es = ax;
  si = 0x0E;
  di = 0x0DCA;
  cx = 0x1020;
  sub_2D9D();
  ah = 1;
  cx = *(WORD*)&_data[ds*16+0x6DFE];
  dx = *(WORD*)&_data[ds*16+0x6DFC];
  _int(0x1A);
  ax = *(WORD*)&_data[ds*16+0x693];
  *(WORD*)&_data[ds*16+0x6E00] = ax;
}

void sub_5EE5()
{
  sub_5B21();
loc_code_5EE8:
  sub_5FCD();
  *(WORD*)&_data[ds*16+0x6D8F] = 0;
  sub_5FB1();
loc_code_5EF4:
  ax = *(WORD*)&_data[ds*16+0x693];
loc_code_5EF7:
  tick();
  if ( ax == *(WORD*)&_data[ds*16+0x693] ) // jz 
    goto loc_code_5EF7;
  if ( !(_data[ds*16+0x6C1] & 0x80) ) // jz 
    goto loc_code_5F12;
  if ( _data[ds*16+0x6C2] & 0x80 ) // jnz 
    goto loc_code_5EF4;
  _data[ds*16+0x69B] = 0;
  goto loc_code_5F1C;
loc_code_5F12:
  sub_5FE5();
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_5EE8;
  _data[ds*16+0x69B] = 1;
loc_code_5F1C:
  cx = 5;
loc_code_5F1F:
  _push(cx);
  sub_5FB1();
  _pop(cx);
  if ( --cx )
    goto loc_code_5F1F;
loc_code_5F26:
  ax = *(WORD*)&_data[ds*16+0x693];
loc_code_5F29:
  tick();
  if ( ax == *(WORD*)&_data[ds*16+0x693] ) // jz 
    goto loc_code_5F29;
  ax = 0;
  if ( !(_data[ds*16+0x6C3] & 0x80) ) // jz 
    goto loc_code_5F50;
  ax++;
  if ( !(_data[ds*16+0x6C4] & 0x80) ) // jz 
    goto loc_code_5F50;
  ax++;
  if ( !(_data[ds*16+0x6C5] & 0x80) ) // jz 
    goto loc_code_5F50;
  ax++;
  if ( _data[ds*16+0x6C6] & 0x80 ) // jnz 
    goto loc_code_5F26;
loc_code_5F50:
  *(WORD*)&_data[ds*16+0x6DF8] = ax;
  cx = 5;
loc_code_5F56:
  _push(cx);
  sub_5FB1();
  _pop(cx);
  if ( --cx )
    goto loc_code_5F56;
  if ( _data[ds*16+0x69B] == 0 ) // jz 
    goto loc_code_5F7E;
  *(WORD*)&_data[ds*16+0x6D8F] = 0x20;
  sub_5FB1();
  sub_5FB1();
  *(WORD*)&_data[ds*16+0x6D8F] = 0x18;
  sub_5FB1();
  sub_5FB1();
  goto loc_code_5F93;
loc_code_5F7E:
  *(WORD*)&_data[ds*16+0x6D8F] = 0x1C;
  sub_5FB1();
  sub_5FB1();
  *(WORD*)&_data[ds*16+0x6D8F] = 0x16;
  sub_5FB1();
loc_code_5F93:
  sub_5F97();
}

void sub_5F97()
{
  if ( _data[ds*16+0x69B] == 0 ) // jz 
    goto loc_code_5FA7;
loc_code_5F9E:
  dx = 0x201;
  _in(al, dx);
  al &= 0x10;
  if ( al ) // jnz 
    goto loc_code_5F9E;
  return;
loc_code_5FA7:
  ax = *(WORD*)&_data[ds*16+0x693];
loc_code_5FAA:
  tick();
  if ( ax == *(WORD*)&_data[ds*16+0x693] ) // jz 
    goto loc_code_5FAA;
}

void sub_5FB1()
{
  bx = *(WORD*)&_data[ds*16+0x6D8F];
  dx = *(WORD*)&_data[bx + 0x6D63];
  sub_5E5B();
  bx = *(WORD*)&_data[ds*16+0x6D8F];
  *(WORD*)&_data[ds*16+0x6D8F] += 2;
  si = *(WORD*)&_data[bx + 0x6D37];
  sub_5E2B();
}

void sub_5FCD()
{
  _cld();
  ax = 0x0B800;
  es = ax;
  ax = 0;
  di = ax;
  cx = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  cx = 0x0FA0;
  _rep_stosw();
}

void sub_5FE5()
{
  _int(0x11);
  if ( !(ax & 0x1000) ) // jz 
    goto loc_code_5FF6;
  sub_600F();
  if ( unknown_condition() ) // jnb cf=0
    return;
  sub_600F();
  if ( unknown_condition() ) // jnb cf=0
    return;
loc_code_5FF6:
  *(WORD*)&_data[ds*16+0x6D8F] = 0x24;
  cx = 4;
loc_code_5FFF:
  sub_5FB1();
  if ( --cx )
    goto loc_code_5FFF;
  ax = *(WORD*)&_data[ds*16+0x693];
loc_code_6007:
  tick();
  if ( ax == *(WORD*)&_data[ds*16+0x693] ) // jz 
    goto loc_code_6007;
  _stc();
}

void sub_600F()
{
  dx = 0x201;
  _out(dx, al);
  ah = 0;
  _int(0x1A);
  *(WORD*)&_data[ds*16+0x6DFA] = dx;
loc_code_601B:
  dx = 0x201;
  _in(al, dx);
  if ( al & 3 ) // jnz 
    goto loc_code_6025;
  _clc();
  return;
loc_code_6025:
  ah = 0;
  _int(0x1A);
  dx -= *(WORD*)&_data[ds*16+0x6DFA];
  if ( dx < 0x12 ) // jb 
    goto loc_code_601B;
  _stc();
}

/*
  unknown_command(); // align 10h
*/
void sub_6040()
{
  _cld();
  _push(ds);
  _pop(es);
  di = 0x0E;
  cx = 0x24;
  ax = 0;
  _rep_stosw();
  *(WORD*)&_data[ds*16+0x6F24] = 0x25;
  ax = 0x0B800;
  es = ax;
loc_code_6058:
  if ( !sub_13D8() ) // jz 
    goto loc_code_6058;
  si = 0x0E;
  di = *(WORD*)&_data[ds*16+0x6F24];
  cx = 0x0C03;
  sub_2D9D();
  *(WORD*)&_data[ds*16+0x6F24] += 0x1E0;
  si = 0x6E10;
  di = *(WORD*)&_data[ds*16+0x6F24];
  cx = 0x0C03;
  sub_2D9D();
loc_code_607D:
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x6F26] ) // jz 
    goto loc_code_607D;
  *(WORD*)&_data[ds*16+0x6F26] = dx;
  if ( _data[ds*16+0] == 0 ) // jz 
    goto loc_code_60A7;
  al = 0x0B6;
  _out(0x43, al);
  ax = *(WORD*)&_data[ds*16+0x6F24];
  ax >>= 1;
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
  _in(al, 0x61);
  al |= 3;
  _out(0x61, al);
loc_code_60A7:
  if ( *(WORD*)&_data[ds*16+0x6F24] < 0x1A40 ) // jb 
    goto loc_code_6058;
  si = 0x6E58;
  di = *(WORD*)&_data[ds*16+0x6F24];
  cx = 0x1106;
  sub_2D9D();
loc_code_60BC:
  ah = 0;
  _int(0x1A);
  if ( dx == *(WORD*)&_data[ds*16+0x6F28] ) // jz 
    goto loc_code_60BC;
  *(WORD*)&_data[ds*16+0x6F28] = dx;
  if ( _data[ds*16+0] == 0 ) // jz 
    goto loc_code_60E6;
  al = 0x0B6;
  _out(0x43, al);
  ax = 0x0C00;
  if ( !(dl & 1) ) // jz 
    goto loc_code_60E0;
  ax = 0x0B54;
loc_code_60E0:
  _out(0x42, al);
  al = ah;
  _out(0x42, al);
loc_code_60E6:
  dx -= *(WORD*)&_data[ds*16+0x6F26];
  if ( dx < 0x12 ) // jb 
    goto loc_code_60BC;
  sub_5B21();
}

/*
  unknown_command(); // align 10h
*/
void sub_6100()
{
  _data[ds*16+0x70F2] = 0;
}

void sub_6106()
{
  ah = 0;
  _int(0x1A);
  if ( dx != *(WORD*)&_data[ds*16+0x70EE] ) // jnz 
    goto loc_code_6111;
  return;
loc_code_6111:
  *(WORD*)&_data[ds*16+0x70EE] = dx;
  sub_62A6();
  if ( unknown_condition() ) // jnb cf=0
    goto loc_code_6129;
  sub_11E3();
  sub_622B();
  sub_1145();
  _data[ds*16+0x70F2] = 0;
  return;
loc_code_6129:
  if ( _data[ds*16+0x70F2] != 0 ) // jnz 
    goto loc_code_619E;
loc_code_6130:
  sub_2DFD();
  bx = dx;
  bx &= 0x1F;
  if ( bl < 0x10 ) // jb 
    goto loc_code_6166;
  bl -= 0x10;
  if ( bl > 9 ) // ja 
    goto loc_code_6130;
  dl = 1;
  if ( bl < 5 ) // jb 
    goto loc_code_614F;
  dl = 0x0FF;
loc_code_614F:
  _data[ds*16+0x70F6] = dl;
  _data[ds*16+0x70F5] = 6;
  bl <<= 1;
  ax = *(WORD*)&_data[bx + 0x70B8];
  ax += 4;
  *(WORD*)&_data[ds*16+0x70F3] = ax;
  goto loc_code_6188;
loc_code_6166:
  ax = 0x0C;
  dl = 1;
  if ( !(bl & 8) ) // jz 
    goto loc_code_6175;
  ax = 0x120;
  dl = 0x0FF;
loc_code_6175:
  *(WORD*)&_data[ds*16+0x70F3] = ax;
  _data[ds*16+0x70F6] = dl;
  bl &= 7;
  al = _data[bx + 0x70B0];
  al += 8;
  _data[ds*16+0x70F5] = al;
loc_code_6188:
  _data[ds*16+0x70F2] = 1;
  _data[ds*16+0x70F7] = 1;
  *(WORD*)&_data[ds*16+0x70F0] = 0;
  *(WORD*)&_data[ds*16+0x70EC] = 0x0FFFF;
loc_code_619E:
  if ( *(WORD*)&_data[ds*16+0x70F0] >= 0x0A0 ) // jnb 
    goto loc_code_61AB;
  *(WORD*)&_data[ds*16+0x70F0] += 4;
loc_code_61AB:
  _data[ds*16+0x70F5] += 2;
  if ( _data[ds*16+0x70F5] > 0x0BF ) // ja 
    goto loc_code_61D4;
  if ( _data[ds*16+0x70F6] == 1 ) // jz 
    goto loc_code_61C7;
  cf = (*(WORD*)&_data[ds*16+0x70F3] < 5); // cf-insertion
  *(WORD*)&_data[ds*16+0x70F3] -= 5;
  if ( cf ) // jb 
    goto loc_code_61D4;
  goto loc_code_61DD;
loc_code_61C7:
  *(WORD*)&_data[ds*16+0x70F3] += 5;
  if ( *(WORD*)&_data[ds*16+0x70F3] < 0x12C ) // jb 
    goto loc_code_61DD;
loc_code_61D4:
  _data[ds*16+0x70F2] = 0;
  sub_622B();
  return;
loc_code_61DD:
  cx = *(WORD*)&_data[ds*16+0x70F3];
  dl = _data[ds*16+0x70F5];
  sub_2CB0();
  *(WORD*)&_data[ds*16+0x70FA] = ax;
  sub_62A6();
  if ( unknown_condition() ) // jb cf=1
    goto loc_code_61D4;
  sub_6245();
  sub_622B();
  sub_61FA();
}

void sub_61FA()
{
  ax = 0x0B800;
  es = ax;
  _data[ds*16+0x70F7] = 0;
  ax = *(WORD*)&_data[ds*16+0x70F0];
  ax &= 0x1E0;
  ax += 0x6F30;
  if ( _data[ds*16+0x70F6] == 0x0FF ) // jz 
    goto loc_code_6217;
  ax += 0x0C0;
loc_code_6217:
  si = ax;
  di = *(WORD*)&_data[ds*16+0x70FA];
  *(WORD*)&_data[ds*16+0x70F8] = di;
  bp = 0x70CC;
  cx = 0x802;
  sub_2CCC();
}

void sub_622B()
{
  if ( _data[ds*16+0x70F7] != 0 ) // jnz 
    return;
  ax = 0x0B800;
  es = ax;
  si = 0x70CC;
  di = *(WORD*)&_data[ds*16+0x70F8];
  cx = 0x802;
  sub_2D9D();
}

void sub_6245()
{
  al = _data[ds*16+0x70F5];
  al -= 8;
  al &= 0x0F8;
  cx = 7;
loc_code_624F:
  bx = cx;
  bx--;
  if ( al == _data[bx + 0x2BD4] ) // jz 
    goto loc_code_625B;
  if ( --cx )
    goto loc_code_624F;
  return;
loc_code_625B:
  ax = *(WORD*)&_data[ds*16+0x70F3];
  cl = 4;
  ax >>= cl;
  cf = (ax < 2); // cf-insertion
  ax -= 2;
  if ( cf ) // jb 
    return;
  if ( ax >= 0x10 ) // jnb 
    return;
  di = ax;
  dl = _data[bx + 0x2BDB];
  dh = 0;
  ax += dx;
  if ( ax == *(WORD*)&_data[ds*16+0x70EC] ) // jz 
    return;
  *(WORD*)&_data[ds*16+0x70EC] = ax;
  si = ax;
  _data[si + 0x2BE2] ^= 2;
  al = _data[si + 0x2BE2];
  ah = 0;
  di <<= 1;
  cx = *(WORD*)&_data[di + 0x70FC];
  dl = _data[bx + 0x7120];
  _push(ax);
  _push(cx);
  _push(dx);
  sub_622B();
  _pop(dx);
  _pop(cx);
  _pop(bx);
  sub_30E3();
  sub_61FA();
}

void sub_62A6()
{
  if ( _data[ds*16+0x70F2] != 0 ) // jnz 
    goto loc_code_62AF;
  _clc();
  return;
loc_code_62AF:
  ax = *(WORD*)&_data[ds*16+0x70F3];
  dl = _data[ds*16+0x70F5];
  si = 0x10;
  bx = *(WORD*)&_data[ds*16+0x579];
  dh = _data[ds*16+0x57B];
  di = 0x18;
  cx = 0x0E08;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  _data[ds*16+0x571] = 1;
  _data[ds*16+0x576] = 2;
  _data[ds*16+0x578] = 0x20;
  _data[ds*16+0x55B] = 8;
  ax = 0x91D;
  bx = 0x0CE4;
  sub_593B();
  _stc();
}

/*
  unknown_command(); // code		ends
  unknown_command(); // end start
  unknown_command(); // end star
*/
