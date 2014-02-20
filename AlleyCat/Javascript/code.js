sub_5CB0_pc = 0;
sub_5EE5_pc = 0;
sub_5F97_pc = 0;
sub_1338_pc = 0;
sub_5E70_pc = 0;
sub_1200_pc = 0;
sub_5B28_pc = 0;
sub_546D_pc = 0;

function pcvalid()
{
  if (typeof sub_5CB0_pc == 'undefined') return false;
  if (typeof sub_5EE5_pc == 'undefined') return false;
  if (typeof sub_5F97_pc == 'undefined') return false;
  if (typeof sub_1338_pc == 'undefined') return false;
  if (typeof sub_5E70_pc == 'undefined') return false;
  if (typeof sub_1200_pc == 'undefined') return false;
  if (typeof sub_5B28_pc == 'undefined') return false;
  if (typeof sub_546D_pc == 'undefined') return false;

  return true;
}

// sub_1338
function start(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(ds);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_5C60();
    r16[ax] = seg_data;
    ds = r16[ax];
    sub_13AA();
    _data[0x690] = 4;
    _data16set(0x6DF8, 0);
    _data[0x69B] = 0;
    sub_1419();
    sub_13E8();
    r16[ax] = _data16get(0x693);
    r16[ax] += 0x240;
    _data16set(0x6E00, r16[ax]);
    r16[ax] = 4;
    _int(0x10);
    r8[al] = 4;
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x3F; continue; }
    r8[al] = 6;
  case 0x3F:
    _data[0x690] = r8[al];
    r8[ah] = 0x0B;
    r16[bx] = 0x101;
    _int(0x10);
    _data16set(0x416, 0);
    _data16set(0x4, 0);
    sub_1D31();
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x65; continue; }
    r16[dx] = 0x3D9;
    r8[al] = 0x20;
    _out(r16[dx], r8[al]);
  case 0x65:
    sub_2E10();
    sub_26E1();
    sub_26DA();
    _data[0x41A] = 0;
    r16[ax] = 0x0FFFF;
    _data16set(0x41D, r16[ax]);
    _data16set(0x41F, r16[ax]);
    _data[0x0] = 0x0FF;
  case 0x81:
    sub_2690();
    _data16set(0x8, 0);
    _data16set(0x4, 0);
    sub_1D31();
    sub_5B21();

    sub_5CB0_pc = 0;
  case 0x0001:
    sub_5CB0_pc = sub_5CB0(sub_5CB0_pc);
    if ( sub_5CB0_pc != -1)
      return 0x0001;

    sub_5B21();
    if ( _data[0x41A] != 0 ) // jnz 
      { wPos = 0xAE; continue; }
  case 0xA3:
    sub_5B21();
    sub_5EE5_pc = 0;
  case 0x0002:
    sub_5EE5_pc = sub_5EE5(sub_5EE5_pc);
    if ( sub_5EE5_pc != -1 )
      return 0x0002;
    _data[0x41A] = 1;
  case 0xAE:
    r16[ax] = _data16get(0x6DF8);
    _data16set(0x8, r16[ax]);
    _data[0x1F80] = 3;
    sub_26DA();
    _data16set(0x4, 0);
    sub_1D31();
    sub_5B21();
    _data16set(0x1C30, 0);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x412, r16[dx]);
    _data16set(0x414, 0);
    _data[0x418] = 0;
    _data[0x419] = 0;
    _data[0x41C] = 0;
    _data[0x41B] = 0;
    sub_5B21();
  case 0xF3:
    if ( _data[0x1F80] == 0 ) // jz 
      { wPos = 0x81; continue; }
    if ( _data[0x41B] != 0 ) // jnz 
      { wPos = 0xAE; continue; }
    if ( _data[0x41C] != 0 ) // jnz 
      { wPos = 0xA3; continue; }
    sub_2A00();
    sub_5400();
    _data[0x1F81] = 0x0FF;
    sub_5B21();
    _data16set(0x4, 0);
    if ( _data[0x419] == 0 ) // jz 
      { wPos = 0x137; continue; }
    sub_7A1();
    _data[0x550] = 2;
    _data[0x576] = 1;
    _data[0x578] = 0x20;
    wPos = 0x140;
      continue;
  case 0x137:
    _data16set(0x579, 0);
    sub_70D();
  case 0x140:
    sub_1E40();
    sub_1830();
    sub_2210();
    sub_2330();
    sub_26F2();
    sub_26FC();
    sub_58BD();
  case 0x155:
    if ( _data[0x1F80] != 0 ) // jnz 
      { wPos = 0x15F; continue; }
    wPos = 0x81;
      continue;
  case 0x15F:

    sub_1338_pc = 0;
  case 0x0006:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x0006;

    if ( _data[0x41C] == 0 ) // jz 
      { wPos = 0x16C; continue; }
    wPos = 0xA3;
      continue;
  case 0x16C:
    if ( _data[0x41B] == 0 ) // jz 
      { wPos = 0x176; continue; }
    wPos = 0xAE;
      continue;
  case 0x176:
    sub_1200_pc = 0;
  case 0xf010:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf010;
    sub_8E5();
    sub_1E63();
    if ( _data[0x1CB8] != 0 ) // jnz 
      { wPos = 0x191; continue; }
    _data[0x40F] = _data[0x40F] + 1;
    if ( _data[0x40F] & 3 ) // jnz 
      { wPos = 0x155; continue; }
  case 0x191:

    sub_546D_pc = 0;
  case 0xF01A:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01A;

    sub_4A0();
    sub_1936();
    sub_184B();
    sub_2216();
    sub_237B();
    sub_26B3();
    if ( _data[0x551] == 0 ) // jz 
      { wPos = 0x155; continue; }
    if ( _data[0x1F80] != 0 ) // jnz 
      { wPos = 0x1B7; continue; }
    wPos = 0x81;
      continue;
  case 0x1B7:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x410, r16[dx]);
    r16[ax] = _data16get(0x579);
    _data16set(0x1, r16[ax]);
    r8[al] = _data[0x57B];
    _data[0x3] = r8[al];
    _data[0x419] = 1;
    if ( _data[0x418] == 0 ) // jz 
      { wPos = 0x1E5; continue; }
    _data[0x418] = 0;
    _data16set(0x4, 7);
    wPos = 0x238;
      continue;
  case 0x1E5:
    sub_2DFD();
    if ( !(r8[dl] & 0x0A0) ) // jz 
      { wPos = 0x20A; continue; }
    r16[bx] = _data16get(0x8);
    r16[bx] &= 3;
    if ( r16[bx] == 3 ) // jz 
      { wPos = 0x20A; continue; }
    r8[cl] = 2;
    r16[bx] <<= r8[cl];
    r16[dx] &= 3;
    r16[bx] += r16[dx];
    r8[al] = _data[r16[bx] + 0x421];
    wPos = 0x21C;
      continue;
  case 0x20A:
    sub_2DFD();
    r16[dx] &= 7;
    if ( r16[dx] >= 5 ) // jnb 
      { wPos = 0x20A; continue; }
    r16[bx] = r16[dx];
    r8[al] = _data[r16[bx] + 0x42D];
  case 0x21C:
    r8[ah] = 0;
    if ( r16[ax] != _data16get(0x41D) ) // jnz 
      { wPos = 0x22A; continue; }
    if ( r16[ax] == _data16get(0x41F) ) // jz 
      { wPos = 0x1E5; continue; }
  case 0x22A:
    _data16set(0x4, r16[ax]);
    r16[cx] = _data16get(0x41D);
    _data16set(0x41F, r16[cx]);
    _data16set(0x41D, r16[ax]);
  case 0x238:
    _data16set(0x6, 0);
    r16[bx] = _data16get(0x4);
    if ( r16[bx] <= 7 ) // jbe 
      { wPos = 0x249; continue; }
    r16[bx] = 0;
  case 0x249:
    r16[bx] <<= 1;
alert("xxx");
/*
    unknown_command(); // jmp	cs:off_code_250[r16[bx]];
  WORD off_code_250 =  offset loc_code_3E2;
    unknown_command(); // dw offset loc_code_3E2
    unknown_command(); // dw offset loc_code_459
    unknown_command(); // dw offset loc_code_394
    unknown_command(); // dw offset loc_code_349
    unknown_command(); // dw offset loc_code_2FE
    unknown_command(); // dw offset loc_code_2AA
    unknown_command(); // dw offset loc_code_260
*/
    _data16set(0x4, 7);
    sub_1BF0();
    sub_2790();
    sub_7A1();
    sub_1E40();
    sub_3405();
    sub_6100();
    sub_4F59();
    sub_58BD();
  case 0x27E:

    sub_1338_pc = 0;
  case 0x0007:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x0007;

    sub_1200_pc = 0;
  case 0xf011:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf011;

    sub_546D_pc = 0;
  case 0xF01B:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01B;

    sub_8E5();
    sub_6106();
    sub_2F66();
    sub_2E60();
    sub_4C10();
    r8[al] = _data[0x551];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x41C];
    r8[al] |= _data[0x41B];
    if ( !r8[al] ) // jz 
      { wPos = 0x27E; continue; }
    wPos = 0x427;
      continue;
    _data16set(0x4, 6);
    sub_1BF0();
    sub_2790();
    nullsub_1();
    sub_7A1();
    sub_3405();
    sub_1E40();
    sub_58BD();
  case 0x2C5:

    sub_1338_pc = 0;
  case 0x0008:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x0008;

    sub_1200_pc = 0;
  case 0xf012:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf012;

    sub_546D_pc = 0;
  case 0xF01C:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01C;

    sub_4943();
    sub_47D6();
    sub_8E5();
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x2E3; continue; }
    sub_1E63();
    wPos = 0x2E6;
      continue;
  case 0x2E3:
    sub_3150();
  case 0x2E6:
    r8[al] = _data[0x551];
    r8[al] |= _data[0x552];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x41B];
    r8[al] |= _data[0x41C];
    if ( !r8[al] ) // jz 
      { wPos = 0x2C5; continue; }
    wPos = 0x427;
      continue;
    _data16set(0x4, 5);
    sub_1BF0();
    sub_2790();
    sub_457A();
    sub_7A1();
    sub_3405();
    sub_1E40();
    sub_58BD();
  case 0x319:

    sub_1338_pc = 0;
  case 0x0009:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x0009;

    sub_1200_pc = 0;
  case 0xf013:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf013;

    sub_546D_pc = 0;
  case 0xF01D:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01D;

    sub_45AB();
    sub_4340();
    sub_8E5();
    sub_3150();
    sub_1E63();
    r8[al] = _data[0x552];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x551];
    r8[al] |= _data[0x41C];
    r8[al] |= _data[0x41B];
    if ( !r8[al] ) // jz 
      { wPos = 0x319; continue; }
    wPos = 0x427;
      continue;
    _data16set(0x4, 4);
    sub_1BF0();
    sub_2790();
    sub_7A1();
    sub_3405();
    sub_1E40();
    sub_4090();
    sub_58BD();
  case 0x364:

    sub_1338_pc = 0;
  case 0x000a:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x000a;

    sub_1200_pc = 0;
  case 0xf014:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf014;

    sub_546D_pc = 0;
  case 0xF01E:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01E;

    sub_8E5();
    sub_3E90();
    sub_40C2();
    sub_3150();
    sub_1E63();
    r8[al] = _data[0x552];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x551];
    r8[al] |= _data[0x41C];
    r8[al] |= _data[0x41B];
    if ( !r8[al] ) // jz 
      { wPos = 0x364; continue; }
    wPos = 0x427;
      continue;
    _data16set(0x4, 3);
    sub_1BF0();
    sub_2790();
    sub_7A1();
    sub_3405();
    sub_1E40();
    sub_3B30();
    sub_3C90();
    sub_58BD();
  case 0x3B2:

    sub_1338_pc = 0;
  case 0x000b:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x000b;

    sub_1200_pc = 0;
  case 0xf015:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf015;

    sub_546D_pc = 0;
  case 0xF01F:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF01F;

    sub_8E5();
    sub_3CB1();
    sub_3B42();
    sub_3150();
    sub_1E63();
    r8[al] = _data[0x552];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x551];
    r8[al] |= _data[0x41C];
    r8[al] |= _data[0x41B];
    if ( !r8[al] ) // jz 
      { wPos = 0x3B2; continue; }
    wPos = 0x427;
      continue;
    _data16set(0x4, 1);
    sub_1BF0();
    sub_2790();
    sub_7A1();
    sub_3405();
    sub_1E40();
    sub_58BD();
  case 0x3FA:


    sub_1338_pc = 0;
  case 0x000b:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x000b;

    sub_1200_pc = 0;
  case 0xf016:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf016;


    sub_546D_pc = 0;
  case 0xF020:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF020;

    sub_8E5();
    sub_3150();
    sub_1E63();
    sub_3850();
    if ( _data[0x554] != 0 ) // jnz 
      { wPos = 0x459; continue; }
    r8[al] = _data[0x552];
    r8[al] |= _data[0x551];
    r8[al] |= _data[0x41B];
    r8[al] |= _data[0x41C];
    if ( !r8[al] ) // jz 
      { wPos = 0x3FA; continue; }
  case 0x427:
    if ( _data[0x41B] == 0 ) // jz 
      { wPos = 0x431; continue; }
    wPos = 0xAE;
      continue;
  case 0x431:
    if ( _data[0x41C] == 0 ) // jz 
      { wPos = 0x43B; continue; }
    wPos = 0xA3;
      continue;
  case 0x43B:
    if ( _data[0x552] == 0 ) // jz 
      { wPos = 0x447; continue; }
    _data[0x419] = 0;
  case 0x447:
    r16[ax] = _data16get(0x4);
    _data16set(0x6, r16[ax]);
    _data16set(0x4, 0);
    sub_1BF0();
    wPos = 0xF3;
      continue;
  case 0x459:
    _data16set(0x4, 2);
    sub_1BF0();
    sub_2790();
    sub_35C9();
    sub_7A1();
    _data[0x1CBF] = 0;
    _data[0x1CB8] = 0;
    sub_58BD();
  case 0x478:

    sub_1338_pc = 0;
  case 0x000d:
    sub_1338_pc = sub_1338(sub_1338_pc);
    if ( sub_1338_pc != -1 )
      return 0x000d;

    sub_1200_pc = 0;
  case 0xf017:
    sub_1200_pc = sub_1200(sub_1200_pc);
    if ( sub_1200_pc != -1 )
      return 0xf017;

    sub_546D_pc = 0;
  case 0xF021:
    sub_546D_pc = sub_546D( sub_546D_pc );
    if ( sub_546D_pc != -1 )
      return 0xF021;

    sub_8E5();
    sub_3675();
    sub_37E5();
    r8[al] = _data[0x552];
    r8[al] |= _data[0x553];
    r8[al] |= _data[0x41C];
    r8[al] |= _data[0x41B];
    if ( !r8[al] ) // jz 
      { wPos = 0x478; continue; }
    wPos = 0x427;
      continue;
    wPos = -1;
  }
}
function sub_4A0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x531]--;
    if ( !_data[0x531] ) // jz 
      { wPos = 0x4A7; continue; }
    return;
  case 0x4A7:
    _data[0x531] = _data[0x531] + 1;
    if ( _data[0x55A] != 0 ) // jnz 
      return;
    if ( _data[0x1673] != 0 ) // jnz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x544) ) // jz 
      return;
    _data16set(0x544, r16[dx]);
    r16[bx] = _data16get(0x8);
    r8[al] = _data[r16[bx] + 0x532];
    if ( _data[0x57B] > 0x60 ) // ja 
      { wPos = 0x4DF; continue; }
    r8[al] >>= 1;
    r8[al] >>= 1;
  case 0x4DF:
    _data[0x531] = r8[al];
    r16[bx] = _data16get(0x52F);
    sub_658();
    if ( zf ) // jz 
      { wPos = 0x50C; continue; }
    r8[al] = _data[0x525];
    r8[al] += _data16get(r16[bx] + 0x529);
    if ( r8[al] < 4 ) // jb 
      return;
  case 0x4F6:
    sub_2DFD();
    r8[dl] &= 3;
    if ( r8[dl] == _data[0x52F] ) // jz 
      { wPos = 0x4F6; continue; }
    if ( r8[dl] == 3 ) // jz 
      { wPos = 0x4F6; continue; }
    r8[bl] = r8[dl];
    wPos = 0x535;
      continue;
  case 0x50C:
    r8[al] = _data[r16[bx] + 0x529];
    _data[0x525] += r8[al];
    if ( _data[0x525] < 4 ) // jb 
      { wPos = 0x583; continue; }
    sub_2DFD();
    if ( r8[dl] > 0x40 ) // ja 
      { wPos = 0x539; continue; }
  case 0x523:
    sub_2DFD();
    r8[dl] &= 3;
    if ( r8[dl] == 3 ) // jz 
      { wPos = 0x523; continue; }
    r8[bl] = r8[dl];
    sub_658();
    if ( !zf ) // jnz 
      { wPos = 0x523; continue; }
  case 0x535:
    _data16set(0x52F, r16[bx]);
  case 0x539:
    r8[al] = _data[r16[bx] + 0x526];
    _data[0x525] = r8[al];
    r16[ax] = seg_data;
    es = r16[ax];
    di = 0x4D7;
    r8[ah] = _data[r16[bx] + 0x52C];
    r16[bx] = _data16get(0x8);
    r8[bl] = _data[r16[bx] + 0x2ABA];
    r8[bh] = r8[ah];
    sub_67D();
    if ( _data16get(0x52F) == 1 ) // jz 
      { wPos = 0x56E; continue; }
    _data[0x540] >>= 1;
    sub_633();
    _data[0x540] >>= 1;
    wPos = 0x57C;
      continue;
  case 0x56E:
    r8[al] = _data[0x540];
    r8[al] >>= 1;
    r8[al] >>= 1;
    sub_633();
    _data[0x540] >>= 1;
  case 0x57C:
    sub_633();
    r16[bx] = _data16get(0x52F);
  case 0x583:
    if ( _data[0x4D6] == 0 ) // jz 
      { wPos = 0x5D0; continue; }
    r16[ax] = _data16get(0x579);
    if ( r8[bl] == 1 ) // jz 
      { wPos = 0x5BF; continue; }
    _data16set(0x55F, _data16get(0x55F) + 1);
    r16[ax] += 4;
    if ( r16[ax] < 0x123 ) // jb 
      { wPos = 0x5CD; continue; }
  case 0x59E:
    _data[0x55B] = 0x11;
    _data[0x571] = 1;
    _data[0x576] = 1;
    _data[0x578] = 0x18;
    _data[0x572] = 1;
    _data[0x55C] = 0;
    wPos = 0x5D0;
      continue;
  case 0x5BF:
    _data16set(0x55F, _data16get(0x55F) -1);
    cf = (r16[ax] < 4); // cf-insertion
    r16[ax] -= 4;
    if ( cf ) // jb 
      { wPos = 0x59E; continue; }
    if ( r16[ax] < 8 ) // jb 
      { wPos = 0x59E; continue; }
  case 0x5CD:
    _data16set(0x579, r16[ax]);
  case 0x5D0:
    _push(ds);
    r16[bx] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x51D);
    _data16set(0x523, r16[ax]);
    si = _data16get(r16[bx] + 0x517);
    r16[ax] = 0x0B800;
    ds = r16[ax];
    es = r16[ax];
    di = si;
    if ( r16[bx] != 2 ) // jnz 
      { wPos = 0x5F1; continue; }
    _cld();
    di--;
    wPos = 0x5F3;
      continue;
  case 0x5F1:
    _std();
    di = di + 1;
  case 0x5F3:
    r16[cx] = 0x27F;
    _push(di);
    _push(si);
    _rep_movsb();
    si = _pop();
    di = _pop();
    si += 0x2000;
    di += 0x2000;
    r16[cx] = 0x280;
    _rep_movsb();
    ds = _pop();
    di = _data16get(0x523);
    r8[bl] = _data[0x525];
    r8[bh] = 0;
    r16[bx] += 0x4D7;
    r16[cx] = 0x10;
  case 0x61B:
    r8[al] = _data[r16[bx]];
    _video[di] = r8[al];
    r16[bx] += 4;
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x630; continue; }
    di += 0x50;
  case 0x630:
    if ( --r16[cx] )
      { wPos = 0x61B; continue; }
    wPos = -1;
  }
}
function sub_633()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _lahf();
    r16[bx] = _data16get(0x52F);
    r8[bl] = _data[r16[bx] + 0x541];
    r16[cx] = 5;
    if ( r8[bl] == 9 ) // jz 
      { wPos = 0x64E; continue; }
  case 0x644:
  //
    _sahf();
    _data[r16[bx] + 0x1016] = _rcr16(_data[r16[bx] + 0x1016], 1);
    _lahf();
    r16[bx] = r16[bx] + 1;
    if ( --r16[cx] )
      { wPos = 0x644; continue; }
    return;
  case 0x64E:
  //
    _sahf();
    _rcl(_data[r16[bx] + 0x1016], 1);
    _lahf();
    r16[bx]--;
    if ( --r16[cx] )
      { wPos = 0x64E; continue; }
    wPos = -1;
  }
}
function sub_658()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    zf = 0; // TODO!
    _data[0x4D6] = 0;
    r8[al] = _data[0x57C];
    if ( r8[al] < _data16get(r16[bx] + 0x53D) ) // jb 
      { wPos = 0x679; continue; }
    if ( r8[al] >= _data16get(r16[bx] + 0x53A) ) // jnb 
      { wPos = 0x679; continue; }
    if ( _data[0x55C] >= 1 ) // jnb 
      { wPos = 0x674; continue; }
    return;
  case 0x674:
    _data[0x4D6] = 1;
  case 0x679:
    zf = 1; //fix_code(); // zf=1
    wPos = -1;
  }
}
function sub_67D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x540] = 0;
    _cld();
    r16[cx] = 0x20;
    r16[ax] = 0x0AAAA;
    _rep_stosw();
    di -= 0x40;
    r16[ax] = 0x4444;
    _data16set(es*16+di+4, r16[ax]);
    _data16set(es*16+di+6, r16[ax]);
    sub_2DFD();
    if ( r8[dl] < r8[bl] ) // jb 
      return;
    if ( r8[dh] > r8[bh] ) // ja 
      { wPos = 0x6A5; continue; }
    return;
  case 0x6A5:
    sub_2DFD();
    if ( r8[dl] < 0x18 ) // jb 
      { wPos = 0x6C7; continue; }
    if ( r8[dl] < 0x60 ) // jb 
      { wPos = 0x6D0; continue; }
    _push(di);
    sub_6DE();
    r8[al] <<= 1;
    _data[0x540] = r8[al];
    di = _pop();
    di += 2;
    sub_6DE();
    _data16set(0x540, _data16get(0x540) | r8[al]);
    return;
  case 0x6C7:
    r16[cx] = 0x20;
    si = 0x490;
    wPos = 0x6D6;
      continue;
  case 0x6D0:
    r16[cx] = 0x10;
    si = 0x460;
  case 0x6D6:
    _rep_movsw();
    _data[0x540] = 3;
    wPos = -1;
  }
}
function sub_6DE()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    sub_2DFD();
    r16[dx] &= 6;
    if ( r8[dl] != 6 ) // jnz 
      { wPos = 0x6ED; continue; }
    r8[al] = 0;
    return;
  case 0x6ED:
    r16[bx] = r16[dx];
    si = _data16get(r16[bx] + 0x4D0);
    r16[cx] = 8;
  case 0x6F6:
    _lodsw();
    _stosw();
    di += 2;
    if ( --r16[cx] )
      { wPos = 0x6F6; continue; }
    r8[al] = 1;
    wPos = -1;
  }
}
function sub_700()
{
  _data16set(0x57D, 0);
  _data16set(0x684, 0);
}
function sub_70D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 0;
    r8[ah] = 1;
    if ( _data16get(0x579) < 0x0A0 ) // jb 
      { wPos = 0x71F; continue; }
    r16[cx] = 0x128;
    r8[ah] = 0x0FF;
  case 0x71F:
    _data[0x56E] = r8[ah];
    _data[0x558] = 3;
    _data[0x559] = 0x0C;
    r8[dl] = 0x0B4;
    _data16set(0x579, r16[cx]);
    _data[0x57B] = r8[dl];
    _data[0x57C] = 0x0E6;
    sub_2CB0();
    _data16set(0x55F, r16[ax]);
    _data16set(0x561, 0x0B03);
    sub_1124();
    _data[0x571] = 0;
    _data16set(0x572, 2);
    _data[0x576] = 1;
    _data[0x55B] = 0;
    _data[0x550] = 0;
    _data[0x55C] = 0;
    _data[0x55A] = 0;
    _data[0x583] = 0;
    _data[0x698] = 0;
    _data[0x699] = 0;
    _data[0x551] = 0;
    _data[0x584] = 0;
    _data[0x552] = 0;
    _data16set(0x554, 0);
    _data[0x553] = 0;
    _data[0x127C] = 0;
    sub_700();
    wPos = -1;
  }
}
function sub_7A1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = _data16get(4);
    if ( r16[bx] != 0 ) // jnz 
      { wPos = 0x7B5; continue; }
    r16[cx] = _data16get(1);
    r8[dl] = _data[3];
    wPos = 0x7BF;
      continue;
  case 0x7B5:
    r8[dl] = _data[r16[bx] + 0x5E9];
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x5D9);
  case 0x7BF:
    _data16set(0x579, r16[cx]);
    _data[0x57B] = r8[dl];
    r8[al] = r8[dl];
    r8[al] += 0x32;
    _data[0x57C] = r8[al];
    sub_2CB0();
    _data16set(0x55F, r16[ax]);
    r16[ax] = _data16get(0x0FB2);
    _data16set(0x569, r16[ax]);
    r16[ax] = _data16get(0x0FBE);
    _data16set(0x567, r16[ax]);
    _data16set(0x561, r16[ax]);
    sub_1124();
    _data[0x571] = 1;
    _data[0x56E] = 0;
    _data[0x576] = 1;
    _data[0x578] = 0x40;
    r8[al] = 0x0A;
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0x805; continue; }
    r8[al] = 0;
  case 0x805:
    _data[0x55B] = r8[al];
    _data[0x550] = 0;
    _data[0x55C] = 0;
    _data[0x55A] = 0;
    _data[0x583] = 0;
    _data[0x698] = 0;
    _data[0x699] = 0;
    _data[0x551] = 0;
    _data[0x584] = 0;
    _data[0x552] = 0;
    _data16set(0x554, 0);
    _data[0x553] = 0;
    _data[0x127C] = 0;
    sub_700();
    if ( _data16get(4) != 2 ) // jnz 
      return;
    _data[0x576] = 0x10;
    _data16set(0x574, 0x10);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x5F1, r16[dx]);
    _data[0x5F3] = 0;
    _data[0x5F4] = 5;
    _data[0x5F5] = 1;
    wPos = -1;
  }
}
function sub_872()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x592A, 0x400);
    if ( _data[0x584] == 0 ) // jz 
      { wPos = 0x880; continue; }
    return;
  case 0x880:
    _data[0x576] = 8;
    r8[dl] = 0x0FF;
    r8[al] = _data[0x57B];
    if ( r8[al] >= _data16get(0x2652) ) // jnb 
      { wPos = 0x892; continue; }
    r8[dl] = 1;
  case 0x892:
    _data[0x571] = r8[dl];
    r16[ax] = _data16get(0x579);
    r16[ax] -= _data16get(0x2650);
    r8[dl] = 0x0FF;
    if ( unknown_condition() ) // ja cf=0 & zf=0
      { wPos = 0x8A5; continue; }
    r8[dl] = 1;
    r16[ax] = ~ r16[ax];
  case 0x8A5:
    _data[0x56E] = r8[dl];
    if ( r8[ah] == 0 ) // jz 
      { wPos = 0x8B1; continue; }
    r16[ax] = 0x0FF;
  case 0x8B1:
    r8[al] = ~ r8[al];
    if ( r8[al] >= 0x30 ) // jnb 
      { wPos = 0x8B9; continue; }
    r8[al] = 0x30;
  case 0x8B9:
    r8[bl] = r8[al];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[al] -= r8[bl];
    _data[0x578] = r8[al];
    r8[cl] = 5;
    r8[al] >>= r8[cl];
    _data16set(0x572, r16[ax]);
    _data[0x55C] = 0;
    _data[0x39E0] = 0;
    _data[0x577] = 1;
    _data[0x55B] = 0x10;
    _data[0x584] = 1;
    wPos = -1;
  }
}
function sub_8E5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x57D) ) // jnz 
      { wPos = 0x8FD; continue; }
    if ( _data16get(0x684) == 0 ) // jz 
      return;
    _data16set(0x684, _data16get(0x684) -1);
    if ( !_data16get(0x684) ) // jz 
      { wPos = 0x90C; continue; }
    return;
  case 0x8FD:
    r16[ax] = 0x20;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x909; continue; }
    r16[ax] >>= 1;
  case 0x909:
    _data16set(0x684, r16[ax]);
  case 0x90C:
    if ( _data16get(4) == 2 ) // jz 
      { wPos = 0x91D; continue; }
    r8[cl] = _data[0x571];
    r8[cl] |= _data16get(0x56E);
    if ( r8[cl] ) // jnz 
      { wPos = 0x926; continue; }
  case 0x91D:
    _push(r16[dx]);
    _push(r16[ax]);
  zf = 0;
    r16[ax] = _pop();
    r16[dx] = _pop();
    if ( zf ) // jz 
      return;
  case 0x926:
    _data16set(0x57D, r16[dx]);
    _data16set(0x57F, r16[ax]);
    if ( _data16get(4) != 4 ) // jnz 
      { wPos = 0x93B; continue; }
    if ( _data[0x39E1] != 0 ) // jnz 
      return;
  case 0x93B:
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x949; continue; }
    if ( _data[0x44BD] != 0 ) // jnz 
      return;
  case 0x949:
    if ( _data16get(4) == 2 ) // jz 
      { wPos = 0x953; continue; }
    wPos = 0xBAC;
      continue;
  case 0x953:
    si = _data16get(8);
    si <<= 1;
    r16[ax] = _data16get(0x57D);
    r16[ax] -= _data16get(0x5F1);
    if ( r16[ax] < _data16get(si + 0x589) ) // jb 
      { wPos = 0x9D6; continue; }
    if ( r16[ax] < _data16get(si + 0x599) ) // jb 
      { wPos = 0x971; continue; }
    _data[0x552] = 1;
  case 0x971:
    _data[0x5F5]--;
    if ( _data[0x5F5] ) // jnz 
      { wPos = 0x9B9; continue; }
    sub_597F();
    _data[0x5F5] = 6;
    r8[al] = _data[0x5F4];
    if ( _data[0x57B] < 0x0B3 ) // jb 
      { wPos = 0x992; continue; }
    if ( r8[al] >= 0x0C8 ) // jnb 
      { wPos = 0x992; continue; }
    r8[al] += 0x1E;
    _data[0x5F4] = r8[al];
  case 0x992:
    r8[dl] = _data[0x57B];
    cf = (r8[dl] < r8[al]); // cf-insertion
    r8[dl] -= r8[al];
    if ( !cf ) // jnb 
      { wPos = 0x99C; continue; }
    r8[dl] = 0;
  case 0x99C:
    r16[cx] = _data16get(0x579);
    r8[dl] &= 0x0F8;
    sub_2CB0();
    di = r16[ax];
    si = 0x64E;
    r16[ax] = 0x0B800;
    es = r16[ax];
    bp = 0x0E;
    r16[cx] = 0x503;
    sub_2D35();
  case 0x9B9:
    _data[0x56E] = 0;
    _data[0x571] = 1;
    _data[0x5F3] = 1;
    _data[0x576] = 0x20;
    r16[bx] = 0;
    r8[ah] = 0x0B;
    _int(0x10);
    wPos = 0xA86;
      continue;
  case 0x9D6:
    si = _data16get(8);
    si <<= 1;
    r16[bx] = 0;
    if ( r16[ax] < _data16get(si + 0x5A9) ) // jb 
      { wPos = 0x9F6; continue; }
    r8[bl] = r8[bl] + 1;
    if ( r16[ax] < _data16get(si + 0x5B9) ) // jb 
      { wPos = 0x9F6; continue; }
    r8[bl] = 5;
    if ( r16[ax] < _data16get(si + 0x5C9) ) // jb 
      { wPos = 0x9F6; continue; }
    r8[bl]--;
  case 0x9F6:
    r8[ah] = 0x0B;
    _int(0x10);
    r8[al] = _data[0x56E];
    _data[0x56F] = r8[al];
    r8[al] = _data[0x571];
    _data[0x570] = r8[al];
    r8[al] = _data[0x698];
    if ( r8[al] != 0 ) // jnz 
      { wPos = 0xA1A; continue; }
    if ( _data16get(0x574) < 0x10 ) // jb 
      { wPos = 0xA2E; continue; }
    _data16set(0x574, _data16get(0x574) -1);
    wPos = 0xA37;
      continue;
  case 0xA1A:
    if ( r8[al] != _data16get(0x56E) ) // jnz 
      { wPos = 0xA2E; continue; }
    if ( _data16get(0x574) >= 0x30 ) // jnb 
      { wPos = 0xA37; continue; }
    _data16set(0x574, _data16get(0x574) + 3);
    wPos = 0xA37;
      continue;
  case 0xA2E:
    _data[0x56E] = r8[al];
    _data16set(0x574, 0x20);
  case 0xA37:
    r16[ax] = _data16get(0x574);
    r8[cl] = 3;
    r16[ax] >>= r8[cl];
    r16[bx] = _data16get(8);
    r8[bl] <<= 1;
    if ( r16[ax] <= _data16get(r16[bx] + 0x66C) ) // jbe 
      { wPos = 0xA4E; continue; }
    r16[ax] = _data16get(r16[bx] + 0x66C);
  case 0xA4E:
    _data16set(0x572, r16[ax]);
    sub_FC9();
    r8[al] = _data[0x699];
    if ( r8[al] != 0 ) // jnz 
      { wPos = 0xA6A; continue; }
    r8[al] = ~ r8[al];
    if ( _data[0x576] < 0x10 ) // jb 
      { wPos = 0xA7E; continue; }
    _data[0x576]--;
    wPos = 0xA86;
      continue;
  case 0xA6A:
    if ( r8[al] != _data16get(0x571) ) // jnz 
      { wPos = 0xA7E; continue; }
    if ( _data[0x576] >= 0x40 ) // jnb 
      { wPos = 0xA86; continue; }
    _data[0x576] += 4;
    wPos = 0xA86;
      continue;
  case 0xA7E:
    _data[0x571] = r8[al];
    _data[0x576] = 0x20;
  case 0xA86:
    si = _data16get(8);
    r8[dl] = _data[0x57B];
    r8[cl] = 4;
    r8[bl] = _data[0x576];
    r8[bl] >>= r8[cl];
    if ( r8[bl] <= _data16get(si + 0x67C) ) // jbe 
      { wPos = 0xAA0; continue; }
    r8[bl] = _data[si + 0x67C];
  case 0xAA0:
    r8[al] = _data[0x571];
    if ( r8[al] < 1 ) // jb 
      { wPos = 0xACE; continue; }
    if ( r8[al] != 1 ) // jnz 
      { wPos = 0xAB4; continue; }
    r8[dl] += r8[bl];
    if ( r8[dl] < 0x0B4 ) // jb 
      { wPos = 0xACE; continue; }
    r8[dl] = 0x0B3;
    wPos = 0xACE;
      continue;
  case 0xAB4:
    cf = (r8[dl] < r8[bl]); // cf-insertion
    r8[dl] -= r8[bl];
    if ( cf ) // jb 
      { wPos = 0xABD; continue; }
    if ( r8[dl] > 3 ) // ja 
      { wPos = 0xACE; continue; }
  case 0xABD:
    r16[ax] = _data16get(0x9B8);
    if ( r16[ax] != _data16get(0x55D) ) // jnz 
      { wPos = 0xACC; continue; }
    r16[ax] = _data16get(0x57D);
    _data16set(0x5F1, r16[ax]);
  case 0xACC:
    r8[dl] = 2;
  case 0xACE:
    _data[0x57B] = r8[dl];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x563, r16[ax]);
    if ( _data[0x5F3] == 0 ) // jz 
      { wPos = 0xAE9; continue; }
    r16[bx] = 0x10;
    wPos = 0xB64;
      continue;
  case 0xAE9:
    r8[al] = _data[0x56E];
    if ( r8[al] != _data16get(0x56F) ) // jnz 
      { wPos = 0xAFB; continue; }
    r8[al] = _data[0x571];
    if ( r8[al] == _data16get(0x570) ) // jz 
      { wPos = 0xB00; continue; }
  case 0xAFB:
    r16[bx] = 0x18;
    wPos = 0xB64;
      continue;
  case 0xB00:
    _data16set(0x587, _data16get(0x587) + 1);
    r16[bx] = _data16get(0x587);
    r8[al] = _data[0x698];
    r8[al] |= _data16get(0x699);
    if ( r8[al] ) // jnz 
      { wPos = 0xB13; continue; }
    r8[bl] >>= 1;
  case 0xB13:
    if ( _data[0x57B] < 0x0B3 ) // jb 
      { wPos = 0xB21; continue; }
    if ( _data[0x571] == 1 ) // jz 
      { wPos = 0xB3C; continue; }
  case 0xB21:
    if ( _data[0x57B] > 4 ) // ja 
      { wPos = 0xB2F; continue; }
    if ( _data[0x699] != 0 ) // jnz 
      { wPos = 0xB53; continue; }
  case 0xB2F:
    r8[al] = _data[0x576];
    r8[ah] = 0;
    r16[ax] >>= 1;
    if ( r16[ax] >= _data16get(0x574) ) // jnb 
      { wPos = 0xB53; continue; }
  case 0xB3C:
    if ( _data[0x56E] == 0 ) // jz 
      { wPos = 0xB53; continue; }
    r16[bx] &= 6;
    if ( _data[0x56E] == 1 ) // jz 
      { wPos = 0xB64; continue; }
    r8[bl] |= 8;
    wPos = 0xB64;
      continue;
  case 0xB53:
    r16[bx] &= 2;
    r8[bl] |= 0x10;
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0xB64; continue; }
    r8[bl] += 4;
  case 0xB64:
    r16[ax] = _data16get(r16[bx] + 0x9A6);
    _data16set(0x55D, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x9C0);
    _data16set(0x565, r16[ax]);
    r8[al] = 0x30;
    r16[cx] = 0x2BC;
    if ( _data[0x697] < 0x0FD ) // jb 
      { wPos = 0xB97; continue; }
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0xB85; continue; }
    r8[al] = 8;
    r16[cx] = 0x3E8;
  case 0xB85:
    if ( _data16get(0x57B) > r8[al] ) // ja 
      { wPos = 0xB97; continue; }
  case 0xB95:
    if ( --r16[cx] )
      { wPos = 0xB95; continue; }
  case 0xB97:
    sub_11E3();
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    sub_1145();
    sub_34A0();
    if ( unknown_condition() ) // jnb cf=0
      return;
    sub_1145();
    return;
  case 0xBAC:
    sub_1B7A();
    if ( !cf ) // jnb 
      { wPos = 0xBB2; continue; }
    return;
  case 0xBB2:
    if ( _data[0x1CB8] != 0 ) // jnz 
      return;
    if ( _data[0x558] == 0 ) // jz 
      { wPos = 0xC1C; continue; }
    if ( _data[0x559] == 0 ) // jz 
      { wPos = 0xBD3; continue; }
    if ( _data[0x1CBF] != 0 ) // jnz 
      return;
    _data[0x559]--;
    return;
  case 0xBD3:
    _data[0x558]--;
    if ( _data[0x558] ) // jnz 
      { wPos = 0xBE5; continue; }
    _data16set(0x572, 8);
    sub_FC9();
    wPos = 0xC1C;
      continue;
  case 0xBE5:
    sub_1020();
    _data16set(0x55D, r16[bx]);
    r8[al] = _data[0x558];
    r8[ah] = _data[0x56E];
    sub_F87();
    if ( _data[0x558] == 2 ) // jz 
      { wPos = 0xC00; continue; }
    sub_11E3();
  case 0xC00:
    sub_1B7A();
    if ( cf ) // jb 
      return;
    sub_20F5();
    if ( cf ) // jb 
      return;
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x55F, r16[ax]);
    sub_1145();
    return;
  case 0xC1C:
    if ( _data[0x55C] < 1 ) // jb 
      { wPos = 0xC6A; continue; }
    if ( _data[0x55C] != 1 ) // jnz 
      { wPos = 0xC5F; continue; }
    _data[0x55C] = _data[0x55C] + 1;
    _data16set(0x572, 6);
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x563, r16[ax]);
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return;
    sub_20F5();
    if ( cf ) // jb 
      return;
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    _data16set(0x565, 0x0E03);
    _data16set(0x55D, 0x9DA);
    sub_1145();
  case 0xC5F:
    if ( _data[0x699] != 0 ) // jnz 
      { wPos = 0xC67; continue; }
    return;
  case 0xC67:
    wPos = 0xE78;
      continue;
  case 0xC6A:
    if ( _data[0x571] != 0 ) // jnz 
      { wPos = 0xC74; continue; }
    wPos = 0xE23;
      continue;
  case 0xC74:
    sub_FC9();
    if ( !cf ) // jnb cf=0
      { wPos = 0xC90; continue; }
    _data[0x56E] = 0;
    _data[0x576] = 2;
    _data[0x571] = 1;
    _data[0x55B] = 0;
    wPos = 0xCC1;
      continue;
  case 0xC90:
    r8[al] = _data[0x578];
    cf = (_data16get(0x577) < r8[al]); // cf-insertion
    _data16set(0x577, _data16get(0x577) - r8[al]);
    if ( !cf ) // jnb 
      { wPos = 0xCC1; continue; }
    if ( _data[0x571] == 1 ) // jz 
      { wPos = 0xCB6; continue; }
    if ( _data[0x576] <= 1 ) // jbe 
      { wPos = 0xCAE; continue; }
    _data[0x576]--;
    wPos = 0xCC1;
      continue;
  case 0xCAE:
    _data[0x571] = 1;
    wPos = 0xCC1;
      continue;
  case 0xCB6:
    if ( _data[0x576] >= 4 ) // jnb 
      { wPos = 0xCC1; continue; }
    _data[0x576] = _data[0x576] + 1;
  case 0xCC1:
    if ( _data[0x55A] != 0 ) // jnz 
      { wPos = 0xCE7; continue; }
    if ( _data[0x55B] == 0 ) // jz 
      { wPos = 0xCD5; continue; }
    _data[0x55B]--;
    if ( _data[0x55B] ) // jnz 
      { wPos = 0xCE7; continue; }
  case 0xCD5:
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0xCE7; continue; }
    sub_1608();
    if ( !cf ) // jnb 
      { wPos = 0xCE7; continue; }
    r8[al] = _data[0x57C];
    wPos = 0xD29;
      continue;
  case 0xCE7:
    r8[al] = _data[0x57C];
    if ( _data[0x571] == 1 ) // jz 
      { wPos = 0xD06; continue; }
    cf = (r8[al] < _data16get(0x576)); // cf-insertion
    r8[al] -= _data16get(0x576);
    if ( !cf ) // jnb 
      { wPos = 0xD4F; continue; }
    r8[al] = 0;
    _data[0x571] = 1;
    _data[0x576] = 1;
    wPos = 0xD4F;
      continue;
  case 0xD06:
    r8[al] += _data16get(0x576);
    if ( r8[al] <= 0x0E6 ) // jbe 
      { wPos = 0xD4F; continue; }
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xD22; continue; }
    if ( r8[al] < 0x0F8 ) // jb 
      { wPos = 0xD4F; continue; }
    r8[al] = 0x0F8;
    _data[0x551] = 1;
    wPos = 0xD4F;
      continue;
  case 0xD22:
    r8[al] = 0x0E6;
    _data[0x550] = 0;
  case 0xD29:
    _data[0x571] = 0;
    _data[0x584] = 0;
    _data16set(0x572, 2);
    _data[0x55B] = 0;
    _data[0x55A] = 0;
    if ( _data[0x55C] == 0 ) // jz 
      { wPos = 0xD4F; continue; }
    _push(r16[ax]);
    sub_5AC2();
    r16[ax] = _pop();
  case 0xD4F:
    _data[0x57C] = r8[al];
    cf = (r8[al] < 0x32); // cf-insertion
    r8[al] -= 0x32;
    if ( !cf ) // jnb 
      { wPos = 0xD58; continue; }
    r8[al] = 0;
  case 0xD58:
    _data[0x57B] = r8[al];
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x563, r16[ax]);
    if ( _data[0x583] != 0 ) // jnz 
      { wPos = 0xD73; continue; }
    sub_11E3();
  case 0xD73:
    sub_1B7A();
    if ( cf ) // jb 
      { wPos = 0xDC4; continue; }
    sub_20F5();
    if ( cf ) // jb 
      { wPos = 0xDC4; continue; }
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    if ( _data[0x584] == 0 ) // jz 
      { wPos = 0xDA1; continue; }
    _data16set(0x585, _data16get(0x585) + 2);
    r16[bx] = _data16get(0x585);
    r16[bx] &= 0x0E;
    r16[ax] = _data16get(r16[bx] + 0x0FC2);
    r16[bx] = _data16get(r16[bx] + 0x0FD2);
    wPos = 0xDA8;
      continue;
  case 0xDA1:
    r16[ax] = _data16get(0x569);
    r16[bx] = _data16get(0x567);
  case 0xDA8:
    _data16set(0x55D, r16[ax]);
    _data16set(0x565, r16[bx]);
    r8[al] = 0x32;
    zf = (r8[al] == _data16get(0x57C)); // zf-insertion
    r8[al] -= _data16get(0x57C);
    if ( zf ) // jz 
      { wPos = 0xDDE; continue; }
    cf = (r8[al] < _data16get(0x57C)); // cf-insertion
  // dummy
    if ( cf ) // jb 
      { wPos = 0xDDE; continue; }
    r16[cx] = 0x168;
  case 0xDBC:
    if ( --r16[cx] )
      { wPos = 0xDBC; continue; }
    zf = (r8[bh] == r8[al]); // zf-insertion
    r8[bh] -= r8[al];
    if ( zf ) // jz 
      { wPos = 0xDC4; continue; }
    cf = (r8[bh] < r8[al]); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0xDCA; continue; }
  case 0xDC4:
    _data[0x583] = 1;
    return;
  case 0xDCA:
    _data16set(0x565, r16[bx]);
    r8[ah] = r8[bl];
    r8[ah] <<= 1;
    r16[ax] = r8[ah] * r8[al];
    r16[ax] += _data16get(0x569);
    _data16set(0x55D, r16[ax]);
    wPos = 0xE1F;
      continue;
  case 0xDDE:
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xDEE; continue; }
    r8[al] = _data[0x57B];
    cf = (r8[al] < 0x0BB); // cf-insertion
    r8[al] -= 0x0BB;
    if ( cf ) // jb 
      { wPos = 0xE1F; continue; }
    cf = (r8[al] < 0x0BB); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0xDFC; continue; }
  case 0xDEE:
    if ( _data[0x550] != 2 ) // jnz 
      { wPos = 0xE1F; continue; }
    r8[al] = _data[0x57B];
    cf = (r8[al] < 0x5E); // cf-insertion
    r8[al] -= 0x5E;
    if ( cf ) // jb 
      { wPos = 0xE1F; continue; }
  case 0xDFC:
    zf = (r8[bh] == r8[al]); // zf-insertion
    r8[bh] -= r8[al];
    if ( zf ) // jz 
      { wPos = 0xE02; continue; }
    cf = (r8[bh] < r8[al]); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0xE16; continue; }
  case 0xE02:
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xE0F; continue; }
    _data[0x551] = 1;
    return;
  case 0xE0F:
    sub_70D();
    sub_59CB();
    return;
  case 0xE16:
    _data16set(0x565, r16[bx]);
    _data[0x576] = 2;
  case 0xE1F:
    sub_1145();
    return;
  case 0xE23:
    if ( _data16get(4) == 7 ) // jz 
      { wPos = 0xE31; continue; }
    if ( _data[0x57B] >= 0x0B4 ) // jnb 
      { wPos = 0xE78; continue; }
  case 0xE31:
    sub_1608();
    if ( cf ) // jb 
      { wPos = 0xE43; continue; }
    _data[0x56E] = 0;
    _data[0x571] = 1;
    wPos = 0xEB1;
      continue;
  case 0xE43:
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0xE78; continue; }
    sub_22F7();
    if ( cf ) // jb 
      { wPos = 0xE56; continue; }
    _data[0x56C] = 0;
    wPos = 0xE78;
      continue;
  case 0xE56:
    if ( _data[0x56C] != 0 ) // jnz 
      { wPos = 0xE60; continue; }
    sub_591F();
  case 0xE60:
    _data[0x699] = 1;
    _data[0x56C] = 1;
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0xE74; continue; }
    r8[dl] = 0x0FF;
  case 0xE74:
    _data[0x698] = r8[dl];
  case 0xE78:
    r8[al] = _data[0x56E];
    _data[0x56F] = r8[al];
    r8[al] = _data[0x698];
    _data[0x56E] = r8[al];
    r8[al] = _data[0x699];
    _data[0x571] = r8[al];
    if ( r8[al] != 0 ) // jnz 
      { wPos = 0xE91; continue; }
    wPos = 0xF34;
      continue;
  case 0xE91:
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0xEC9; continue; }
    if ( _data[0x57B] < 0x0B4 ) // jb 
      { wPos = 0xEB1; continue; }
    _data[0x571] = 0;
    _data[0x584] = 0;
    _data[0x699] = 0;
    wPos = 0xF34;
      continue;
  case 0xEB1:
    r8[ah] = 1;
    r8[al] = 0x20;
    _data[0x55B] = 8;
    if ( _data[0x550] != 1 ) // jnz 
      { wPos = 0xEF1; continue; }
    _data[0x550] = 0;
    wPos = 0xEF1;
      continue;
  case 0xEC9:
    _data[0x55B] = 0;
    r16[ax] = _data16get(0x572);
    r8[bl] = r8[al];
    if ( r8[al] <= 2 ) // jbe 
      { wPos = 0xED9; continue; }
    r8[al] -= 2;
  case 0xED9:
    _data16set(0x572, r16[ax]);
    r8[ah] = 8;
    r8[al] = r8[bl];
    r8[al] = r8[al] ^ 0x0F;
    r8[cl] = 4;
    r8[al] <<= r8[cl];
    if ( _data[0x550] != 1 ) // jnz 
      { wPos = 0xEF1; continue; }
    _data[0x550] = _data[0x550] + 1;
  case 0xEF1:
    _data[0x578] = r8[al];
    _data[0x576] = r8[ah];
    _data[0x577] = 1;
    _data[0x55C] = 0;
    r8[bl] = _data[0x56E];
    r8[bl] = r8[bl] + 1;
    r8[bl] <<= 1;
    if ( _data[0x571] == 0x0FF ) // jz 
      { wPos = 0xF14; continue; }
    r8[bl] += 6;
  case 0xF14:
    r8[bh] = 0;
    r16[ax] = _data16get(r16[bx] + 0x0FAA);
    _data16set(0x569, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x0FB6);
    _data16set(0x567, r16[ax]);
    _data[0x39E0] = 0;
    if ( _data[0x127C] == 0 ) // jz 
      return;
    sub_58F8();
    return;
  case 0xF34:
    if ( _data16get(4) == 0 ) // jz 
      { wPos = 0xF45; continue; }
    if ( _data16get(4) == 7 ) // jz 
      { wPos = 0xF45; continue; }
    sub_3445();
  case 0xF45:
    sub_FC9();
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x563, r16[ax]);
    r8[al] = _data[0x56E];
    r8[al] |= _data16get(0x571);
    if ( r8[al] ) // jnz 
      { wPos = 0xF63; continue; }
    sub_1069();
    return;
  case 0xF63:
    sub_1020();
    _data16set(0x55D, r16[bx]);
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return;
    sub_20F5();
    if ( cf ) // jb 
      return;
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    _data16set(0x565, 0x0B03);
    sub_1145();
    wPos = -1;
  }
}
function sub_F87()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 0x0B03;
    r8[cl] -= r8[al];
    _data16set(0x565, r16[cx]);
    if ( r8[ah] == 0x0FF ) // jz 
      { wPos = 0xFA6; continue; }
    r8[ah] = 0;
    r8[al] <<= 1;
    _data16set(0x55D, _data16get(0x55D) + r16[ax]);
    _data16set(0x579, 0);
    wPos = 0xFB4;
      continue;
  case 0xFA6:
    r8[ah] = 0;
    r8[al] <<= 1;
    r8[al] <<= 1;
    r8[al] <<= 1;
    r16[ax] += 0x128;
    _data16set(0x579, r16[ax]);
  case 0xFB4:
    _push(ds);
    es = _pop();
    si = _data16get(0x55D);
    di = 0x0E;
    r8[al] = 3;
    sub_2D70();
    _data16set(0x55D, 0x0E);
    wPos = -1;
  }
}
function sub_FC9()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x5F6, 8);
    _data16set(0x5F8, 0x123);
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xFE8; continue; }
    _data16set(0x5F6, 0x24);
    _data16set(0x5F8, 0x10F);
  case 0xFE8:
    r16[ax] = _data16get(0x579);
    if ( _data[0x56E] < 1 ) // jb 
      { wPos = 0x101E; continue; }
    if ( _data[0x56E] != 1 ) // jnz 
      { wPos = 0x1007; continue; }
    r16[ax] += _data16get(0x572);
    if ( r16[ax] < _data16get(0x5F8) ) // jb 
      { wPos = 0x101B; continue; }
    r16[ax] = _data16get(0x5F8);
    r16[ax]--;
    _data16set(0x579, r16[ax]);
    _stc();
    return;
  case 0x1007:
    cf = (r16[ax] < _data16get(0x572)); // cf-insertion
    r16[ax] -= _data16get(0x572);
    if ( cf ) // jb 
      { wPos = 0x1013; continue; }
    if ( r16[ax] >= _data16get(0x5F6) ) // jnb 
      { wPos = 0x101B; continue; }
  case 0x1013:
    r16[ax] = _data16get(0x5F6);
    _data16set(0x579, r16[ax]);
    _stc();
    return;
  case 0x101B:
    _data16set(0x579, r16[ax]);
  case 0x101E:
    _clc();
    wPos = -1;
  }
}
function sub_1020()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x56E];
    if ( r8[al] == _data16get(0x56F) ) // jz 
      { wPos = 0x102F; continue; }
    _data16set(0x572, 2);
  case 0x102F:
    if ( _data16get(0x572) >= 8 ) // jnb 
      { wPos = 0x1045; continue; }
    _data[0x577]--;
    r8[al] = _data[0x577];
    r8[al] &= 3;
    if ( r8[al] ) // jnz 
      { wPos = 0x1045; continue; }
    _data16set(0x572, _data16get(0x572) + 1);
  case 0x1045:
    r8[bl] = _data[0x56B];
    r8[bl] = r8[bl] + 1;
    if ( r8[bl] < 6 ) // jb 
      { wPos = 0x1052; continue; }
    r8[bl] = 0;
  case 0x1052:
    _data[0x56B] = r8[bl];
    if ( _data[0x56E] != 0x0FF ) // jnz 
      { wPos = 0x1060; continue; }
    r8[bl] += 6;
  case 0x1060:
    r8[bl] <<= 1;
    r8[bh] = 0;
    r16[bx] = _data16get(r16[bx] + 0x0F7A);
    wPos = -1;
  }
}
function sub_1069()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x572, 2);
    _data[0x577] = 8;
    if ( _data16get(0x561) != 0x0C02 ) // jnz 
      { wPos = 0x1087; continue; }
    _data[0x56D] = _data[0x56D] + 1;
    if ( _data[0x56D] & 7 ) // jnz 
      return;
  case 0x1087:
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return;
    sub_20F5();
    if ( cf ) // jb 
      return;
    sub_2DFD();
    r8[bl] = r8[dl];
    r16[bx] &= 0x0E;
    si = _data16get(r16[bx] + 0x0F92);
    r16[ax] = 0x0B800;
    es = r16[ax];
    di = _data16get(0x55F);
    bp = 0x5FA;
    _data16set(0x561, 0x0C02);
    r16[cx] = 0x602;
    sub_2D35();
    sub_2DFD();
    r8[bl] = r8[dl];
    r16[bx] &= 6;
    si = _data16get(r16[bx] + 0x0FA2);
    di = _data16get(0x55F);
    di += 0x0F0;
    bp = 0x612;
    r16[cx] = 0x602;
    sub_2D35();
    _data[0x583] = 0;
    wPos = -1;
  }
}
function sub_10DD()
{
  _data[0x55C] = 0;
  _data[0x571] = 1;
  _data[0x576] = 2;
  _data[0x578] = 1;
  _data[0x577] = 0x0FF;
  _data[0x56E] = 0;
  _data[0x55A] = 1;
  r16[ax] = _data16get(0x0FAC);
  _data16set(0x569, r16[ax]);
  r16[ax] = _data16get(0x0FB8);
  _data16set(0x567, r16[ax]);
  _data[0x550] = 2;
}
function sub_1112()
{
  r16[cx] = _data16get(0x579);
  r8[dl] = _data[0x57B];
  sub_2CB0();
  _data16set(0x55F, r16[ax]);
  sub_1124();
}
function sub_1124()
{
  r16[ax] = seg_data;
  es = r16[ax];
  di = 0x5FA;
  _push(ds);
  si = _data16get(0x55F);
  r16[ax] = 0x0B800;
  ds = r16[ax];
  r16[cx] = _data16get(es*16+0x561);
  sub_2DCA();
  ds = _pop();
  _data[0x583] = 0;
}
function sub_1145()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x55F);
  bp = 0x5FA;
  si = _data16get(0x55D);
  r16[cx] = _data16get(0x565);
  _data16set(0x561, r16[cx]);
  _data[0x583] = 0;
  sub_2D35();
}
function sub_1166()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    cf = (r16[cx] < 0x0C); // cf-insertion
    r16[cx] -= 0x0C;
    if ( !cf ) // jnb 
      { wPos = 0x1175; continue; }
    r16[cx] = 0;
  case 0x1175:
    if ( r16[cx] < 0x10F ) // jb 
      { wPos = 0x117E; continue; }
    r16[cx] = 0x10E;
  case 0x117E:
    sub_2CB0();
    _data16set(0x581, r16[ax]);
    di = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    bp = 0x0E;
    si = 0x1679;
    r16[cx] = 0x1205;
    sub_2CCC();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x57F, r16[dx]);
    _data16set(0x5A3C, 0);
    _data16set(0x5A3E, 0);
  case 0x11AB:
    sub_5A1C();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x57F);
    if ( r16[dx] < 0x0A ) // jb 
      { wPos = 0x11AB; continue; }
    sub_5B21();
    di = _data16get(0x581);
    si = 0x0E;
    r16[cx] = 0x1205;
    _data[0x583] = 0;
    sub_2D9D();
    if ( _data[0x1678] == 0 ) // jz 
      return;
    if ( _data[0x1F80] == 0 ) // jz 
      return;
    _data[0x1F80]--;
    wPos = -1;
  }
}
function sub_11E3()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x55F);
  si = 0x5FA;
  r16[cx] = _data16get(0x561);
  sub_2D9D();
}
function sub_1200(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x69F);
    if ( r16[ax] >= 2 ) // jnb 
      { wPos = 0x1210; continue; }
    return -1;
  case 0x1210:
    _data16set(0x69F, r16[dx]);
    if ( _data[0x69B] != 0 ) // jnz 
      { wPos = 0x122E; continue; }
    sub_12C1();
    sub_13B7();
    r16[dx] = r16[ax];
  case 0x1223:
    sub_13B7();
    r16[ax] -= r16[dx];
    if ( r16[ax] < 0x0F8ED ) // jb 
      { wPos = 0x1223; return wPos; }
    return -1;
  case 0x122E:
    r16[dx] = 0x201;
    r8[al] =_in(r16[dx]);
    r8[al] &= 0x10;
    _data[0x69A] = r8[al];
    _data[0x69E] = 3;
    sub_13B7();
    _data16set(0x69C, r16[ax]);
    _out(r16[dx], r8[al]);
    r16[cx] = 0x7D0;
  case 0x1246:
    r8[al] =_in(r16[dx]);
    if ( r8[al] & 1 ) // jnz 
      { wPos = 0x125E; continue; }
    if ( !(_data[0x69E] & 1) ) // jz 
      { wPos = 0x125E; continue; }
    _data[0x69E] &= 0x0FE;
    sub_12A1();
    _data[0x698] = r8[bl];
  case 0x125E:
    if ( r8[al] & 2 ) // jnz 
      { wPos = 0x1275; continue; }
    if ( !(_data[0x69E] & 2) ) // jz 
      { wPos = 0x1275; continue; }
    _data[0x69E] &= 0x0FD;
    sub_12A1();
    _data[0x699] = r8[bl];
  case 0x1275:
    if ( !(_data[0x69E] & 3) ) // jz 
      return -1;
    sub_13B7();
    r16[ax] -= _data16get(0x69C);
    if ( --r16[cx] && (r16[ax] != 0x1964) )
      { wPos = 0x1246; return wPos; }
    if ( !(_data[0x69E] & 1) ) // jz 
      { wPos = 0x1294; continue; }
    _data[0x698] = 0x0FF;
  case 0x1294:
    if ( !(_data[0x69E] & 2) ) // jz 
      return -1;
    _data[0x699] = 0x0FF;
    wPos = -1;
  }
  return -1;
}
function sub_12A1()
{
alert("check 1");
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(r16[ax]);
    sub_13B7();
    r16[ax] -= _data16get(0x69C);
    r16[bx] = r16[ax];
    r16[ax] = _pop();
    if ( r16[bx] >= 0x0F5E6 ) // jnb 
      { wPos = 0x12B5; continue; }
    r8[bl] = 1;
    return;
  case 0x12B5:
    if ( r16[bx] >= 0x0FAFA ) // jnb 
      { wPos = 0x12BE; continue; }
    r8[bl] = 0;
    return;
  case 0x12BE:
    r8[bl] = 0x0FF;
    wPos = -1;
  }
}
function sub_12C1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x6BA];
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x12D3; continue; }
    r8[al] &= _data16get(0x6BD);
    r8[al] &= _data16get(0x6BE);
  case 0x12D3:
    r8[al] = r8[al] ^ 0x80;
    if ( !r8[al] ) // jz 
      { wPos = 0x12D9; continue; }
    r8[al] = 1;
  case 0x12D9:
    _data[0x699] = r8[al];
    r8[al] = _data[0x6B8];
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x12EE; continue; }
    r8[al] &= _data16get(0x6BC);
    r8[al] &= _data16get(0x6BF);
  case 0x12EE:
    r8[al] = r8[al] ^ 0x80;
    if ( !r8[al] ) // jz 
      { wPos = 0x12F7; continue; }
    _data[0x699] = 0x0FF;
  case 0x12F7:
    r8[al] = _data[0x6B9];
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x1309; continue; }
    r8[al] &= _data16get(0x6BC);
    r8[al] &= _data16get(0x6BD);
  case 0x1309:
    r8[al] = r8[al] ^ 0x80;
    if ( !r8[al] ) // jz 
      { wPos = 0x130F; continue; }
    r8[al] = 1;
  case 0x130F:
    _data[0x698] = r8[al];
    r8[al] = _data[0x6BB];
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x1324; continue; }
    r8[al] &= _data16get(0x6BE);
    r8[al] &= _data16get(0x6BF);
  case 0x1324:
    r8[al] = r8[al] ^ 0x80;
    if ( !r8[al] ) // jz 
      { wPos = 0x132D; continue; }
    _data[0x698] = 0x0FF;
  case 0x132D:
    r8[al] = _data[0x6B7];
    r8[cl] = 3;
    r8[al] >>= r8[cl];
    _data[0x69A] = r8[al];
    wPos = -1;
  }
}
function sub_1338(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x693);
    if ( r16[ax] == _data16get(0x691) ) // jz 
      return -1;
    _data16set(0x691, r16[ax]);
    if ( _data[0x6C0] & 0x80 ) // jnz 
      { wPos = 0x1358; continue; }
    r16[ax] = _data16get(0x693);
    if ( r16[ax] == _data16get(0x6E00) ) // jz 
      return;

    sub_5E70_pc = 0;
  case 0x0005:
    sub_5E70_pc = sub_5E70( sub_5E70_pc );
    if ( sub_5E70_pc != -1 )
      return 0x0005;

    return -1;
  case 0x1358:
    if ( !(_data[0x6C9] & 0x80) ) // jz 
      { wPos = 0x1360; continue; }
    return -1;
  case 0x1360:
    if ( _data[0x6CC] & 0x80 ) // jnz 
      { wPos = 0x136D; continue; }
    _data[0x1F80] = 9;
    return -1;
  case 0x136D:
    if ( !(_data[0x6C1] & 0x80) ) // jz 
      { wPos = 0x13A5; continue; }
    if ( _data[0x6CB] & 0x80 ) // jnz 
      { wPos = 0x1381; continue; }
    _data[0x41C] = 0x0FF;
    return -1;
  case 0x1381:
    if ( _data[0x6C8] & 0x80 ) // jnz 
      { wPos = 0x138E; continue; }
    _data[0x41B] = 0x0FF;
    return -1;
  case 0x138E:
    if ( _data[0x6C7] & 0x80 ) // jnz 
      return -1;
    _data[0] = ~ _data[0];
    if ( _data[0] != 0 ) // jnz 
      return -1;
    sub_5B21();
    return -1;
    return -1;
  case 0x13A5:
    sub_147F();
    r16[ax] = _pop();
    unknown_command(); // retf
    wPos = -1;
  }
  return -1;
}
function sub_13AA()
{
  r16[ax] = 0x0F000;
  es = r16[ax];
  r8[al] = 0xff;
  _data[0x697] = r8[al];
}
function sub_13B7()
{
  r8[al] = 0;
  _out(0x43, r8[al]);
  r8[al] = _in(0x40);
  r8[ah] = r8[al];
  r8[al] = _in(0x40);
  var temp = r8[al]; r8[al] = r8[ah]; r8[ah] = temp;
  //_xchg(r8[al], r8[ah]);
}
/*
zf = 0;
{
  r16[dx] = 0x3DA;
  r8[al] =_in(r16[dx]);
  r8[al] &= 8;
  return r8[al];
*/
function sub_13B7()
{
  r8[al] = 0;
  _out(0x43, r8[al]);
  r8[al] =_in(0x40);
  r8[ah] = r8[al];
  r8[al] =_in(0x40);
  var temp = r8[al]; r8[al] = r8[ah]; r8[ah] = temp;
  //_xchg(r8[al], r8[ah]);
}
function sub_13E8()
{
  _push(r16[ax]);
  _push(es);
  _push(di);
  _push(r16[cx]);
  r16[ax] = seg_data;
  es = r16[ax];
  _cld();
  di = 0x6B7;
  r16[cx] = 0x16;
  r8[al] = 0x80;
  _rep_stosb();
  r16[ax] = _data16get(es*16+0x693);
  r16[ax] -= 0x70;
  _data16set(es*16+0x691, r16[ax]);
  r16[ax] = 0x40;
  es = r16[ax];
  r8[al] = _data[es*16+0x12];
  byte_code_13E7 = r8[al];
  r16[cx] = _pop();
  di = _pop();
  es = _pop();
  r16[ax] = _pop();
}
function sub_1419()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0;
    es = r16[ax];
    r16[ax] = _data16get(es*16+0x24);
    r16[bx] = _data16get(es*16+0x26);
    r16[cx] = _data16get(es*16+0x120);
    r16[dx] = _data16get(es*16+0x122);
    word_code_13DF = r16[ax];
    word_code_13E1 = r16[bx];
    word_code_13E3 = r16[cx];
    word_code_13E5 = r16[dx];
    r16[bx] = 0x14B3;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x1450; continue; }
    r16[bx] = 0x14FB;
  case 0x1450:
    _cli();
    _data16set(es*16+0x24, r16[bx]);
    _data16set(es*16+0x26, cs);
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x147D; continue; }
  //  _data16set(es*16+0x120, &loc_code_1554);
    _data16set(es*16+0x122, cs);
    r16[ax] = 0x40;
    es = r16[ax];
    r8[al] = _data[es*16+0x18];
    r8[al] |= 1;
    _data[es*16+0x18] = r8[al];
  case 0x147D:
    _sti();
    wPos = -1;
  }
}
function sub_147F()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0;
    es = r16[ax];
    r16[ax] = word_code_13DF;
    r16[bx] = word_code_13E1;
    r16[cx] = word_code_13E3;
    r16[dx] = word_code_13E5;
    _cli();
    _data16set(es*16+0x24, r16[ax]);
    _data16set(es*16+0x26, r16[bx]);
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x14B1; continue; }
    _data16set(es*16+0x120, r16[cx]);
    _data16set(es*16+0x122, r16[dx]);
  case 0x14B1:
    _sti();
    wPos = -1;
  }
}
function sub_1572()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[es*16+0x6C9];
    r8[al] |= _data16get(es*16+0x6B7);
    if ( r8[al] != 0 ) // jnz 
      return;
    if ( _data[es*16+0x6CA] & 0x80 ) // jnz 
      { wPos = 0x158D; continue; }
    r8[al] = 0x20;
    _out(0x20, r8[al]);
    wPos = 0x1557;
      continue;
  case 0x158D:
    if ( _data[es*16+0x6B9] & 0x80 ) // jnz 
      { wPos = 0x15A4; continue; }
    if ( _data[es*16+0x690] < 1 ) // jb 
      return;
    _data[es*16+0x690]--;
    wPos = 0x15B9;
      continue;
  case 0x15A4:
    if ( _data[es*16+0x6BB] & 0x80 ) // jnz 
      return;
    if ( _data[es*16+0x690] >= 7 ) // jnb 
      return;
    _data[es*16+0x690] = _data[es*16+0x690] + 1;
  case 0x15B9:
    _push(r16[dx]);
    r8[al] = 2;
    r16[dx] = 0x3D4;
    _out(r16[dx], r8[al]);
    r8[al] = _data[es*16+0x690];
    r8[al] += 0x27;
    r16[dx] = r16[dx] + 1;
    _out(r16[dx], r8[al]);
    r16[dx] = _pop();
    wPos = -1;
  }
}
function sub_15D0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = _data16get(8);
    r8[cl] = _data[r16[bx] + 0x100E];
  case 0x15D8:
    sub_2DFD();
    r8[dl] &= 7;
    if ( r8[dl] > r8[cl] ) // ja 
      { wPos = 0x15D8; continue; }
    r8[dl] += _data16get(r16[bx] + 0x1006);
    if ( r8[dl] == _data16get(0x1028) ) // jz 
      { wPos = 0x15D8; continue; }
    _data[0x1028] = r8[dl];
    r8[bl] = r8[dl];
    r8[cl] = _data[r16[bx] + 0x0FF0];
    r8[dl] = 0x88;
    if ( r8[cl] & 0x80 ) // jnz 
      { wPos = 0x15FF; continue; }
    r8[dl] = 0x90;
  case 0x15FF:
    r16[cx] &= 0x7F;
    r16[cx] <<= 1;
    r16[cx] <<= 1;
    wPos = -1;
  }
}
function sub_1608()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0x1613; continue; }
    sub_30FA();
    return;
  case 0x1613:
    if ( _data16get(4) == 0 ) // jz 
      { wPos = 0x161E; continue; }
    sub_16C6();
    return;
  case 0x161E:
    r8[al] = _data[0x57B];
    r8[al] &= 0x0F8;
    if ( r8[al] == 0x60 ) // jz 
      { wPos = 0x1630; continue; }
    sub_1657();
    if ( cf ) // jb cf=1
      return;
    sub_17AD();
    return;
  case 0x1630:
    if ( _data[0x550] >= 2 ) // jnb 
      { wPos = 0x1655; continue; }
    _data[0x57B] = r8[al];
    r8[al] += 0x32;
    _data[0x57C] = r8[al];
    if ( _data[0x550] == 1 ) // jz 
      { wPos = 0x1653; continue; }
    _data[0x550] = 1;
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x556, r16[dx]);
  case 0x1653:
    _stc();
    return;
  case 0x1655:
    _clc();
    wPos = -1;
  }
}
function sub_1657()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[cl] = _data[0x57B];
    r8[cl] += 2;
    r8[cl] &= 0x0F8;
    r16[bx] = _data16get(8);
    r8[bl] = _data[r16[bx] + 0x1006];
  case 0x1669:
    r8[al] = _data[r16[bx] + 0x0FF0];
    if ( r8[al] != 0 ) // jnz 
      { wPos = 0x1678; continue; }
    _data[0x127C] = 0;
    _clc();
    return;
  case 0x1678:
    r16[bx] = r16[bx] + 1;
    r8[ch] = 0x88;
    if ( r8[al] & 0x80 ) // jnz 
      { wPos = 0x1681; continue; }
    r8[ch] = 0x90;
  case 0x1681:
    if ( r8[cl] != r8[ch] ) // jnz 
      { wPos = 0x1669; continue; }
    r16[ax] &= 0x7F;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[dx] = _data16get(0x579);
    r16[dx] &= 0x0FFF8;
    if ( r16[dx] < r16[ax] ) // jb 
      { wPos = 0x1669; continue; }
    r16[dx] = _data16get(0x579);
    r16[dx] -= 0x0F;
    r16[dx] &= 0x0FFF8;
    if ( r16[dx] > r16[ax] ) // ja 
      { wPos = 0x1669; continue; }
    r8[ch] -= 2;
    _data[0x57B] = r8[ch];
    r8[ch] += 0x32;
    _data[0x57C] = r8[ch];
    if ( _data[0x127C] != 0 ) // jnz 
      { wPos = 0x16C4; continue; }
    _data[0x127C] = 1;
    sub_590E();
  case 0x16C4:
    _stc();
    wPos = -1;
  }
}
function sub_16C6()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x39E0] = 0;
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0x16FC; continue; }
    r16[ax] = _data16get(0x2650);
    r16[ax] -= 4;
    r8[dl] = _data[0x2652];
    r8[dl] -= 8;
    si = 0x0C;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E10;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      { wPos = 0x16FC; continue; }
    _data[0x551] = 1;
    _clc();
    return;
  case 0x16FC:
    if ( _data16get(4) != 3 ) // jnz 
      { wPos = 0x170E; continue; }
    sub_3C43();
    if ( !cf ) // jnb cf=0
      { wPos = 0x170E; continue; }
    _data[0x55C] = 1;
    return;
  case 0x170E:
    r8[cl] = _data[0x57B];
    r8[cl] &= 0x0F8;
    r16[bx] = _data16get(4);
    r16[bx] <<= 1;
    r16[bx] = _data16get(r16[bx] + 0x1269);
  case 0x171F:
    r8[ch] = _data[r16[bx] + 0x1029];
    if ( r8[ch] != 0 ) // jnz 
      { wPos = 0x172A; continue; }
    _clc();
    return;
  case 0x172A:
    r8[al] = _data[r16[bx] + 0x1089];
    _data[0x127B] = r8[al];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x11A9);
    _data16set(0x1279, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x10E9);
    r8[bl] >>= 1;
    r16[bx] = r16[bx] + 1;
    if ( r8[cl] != r8[ch] ) // jnz 
      { wPos = 0x171F; continue; }
    r16[dx] = _data16get(0x579);
    r16[dx] &= 0x0FFF8;
    if ( r16[dx] < r16[ax] ) // jb 
      { wPos = 0x171F; continue; }
    r16[dx] = _data16get(0x579);
    cf = (r16[dx] < _data16get(0x1279)); // cf-insertion
    r16[dx] -= _data16get(0x1279);
    if ( !cf ) // jnb 
      { wPos = 0x175D; continue; }
    r16[dx] = 0;
  case 0x175D:
    r16[dx] &= 0x0FFFC;
    if ( r16[dx] > r16[ax] ) // ja 
      { wPos = 0x171F; continue; }
    _data[0x57B] = r8[ch];
    r8[ch] += 0x32;
    _data[0x57C] = r8[ch];
    r8[al] = _data[0x127B];
    _data[0x55C] = r8[al];
    if ( r8[al] == 0 ) // jz 
      { wPos = 0x1780; continue; }
    _data16set(0x579, _data16get(0x579) & 0x0FFFC);
  case 0x1780:
    if ( _data16get(4) != 4 ) // jnz 
      { wPos = 0x1797; continue; }
    r16[bx]--;
    cf = (r16[bx] < 0x27); // cf-insertion
    r16[bx] -= 0x27;
    if ( cf ) // jb 
      { wPos = 0x1797; continue; }
    if ( r16[bx] >= 0x10 ) // jnb 
      { wPos = 0x1797; continue; }
    r16[bx] = r16[bx] + 1;
    _data[0x39E0] = r8[bl];
  case 0x1797:
    _stc();
    wPos = -1;
  }
}
function sub_1799()
{
  r8[cl] = 3;
  r16[bx] >>= r8[cl];
  r8[ch] = r8[bl];
  r8[cl] = 3;
  r16[bx] >>= r8[cl];
  r8[cl] = r8[ch];
  r8[cl] &= 7;
  r8[ch] = 0x80;
  r8[ch] >>= r8[cl];
}
function sub_17AD()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[dl] = _data[0x57B];
    r8[dl] &= 0x0F8;
    r16[bx] = 0;
    if ( r8[dl] == 8 ) // jz 
      { wPos = 0x17C9; continue; }
    r8[bl] = r8[bl] + 1;
    if ( r8[dl] == 0x28 ) // jz 
      { wPos = 0x17C9; continue; }
    r8[bl] = r8[bl] + 1;
    if ( r8[dl] != 0x48 ) // jnz 
      { wPos = 0x1810; continue; }
  case 0x17C9:
    r16[ax] = _data16get(0x579);
    if ( r16[bx] != _data16get(0x52F) ) // jnz 
      { wPos = 0x17FC; continue; }
    if ( _data[0x525] > 3 ) // ja 
      { wPos = 0x17FC; continue; }
    if ( r8[bl] == 1 ) // jz 
      { wPos = 0x17EE; continue; }
    r16[cx] = 4;
    r8[cl] -= _data16get(0x525);
    r8[cl] <<= 1;
    r8[cl] <<= 1;
    r16[ax] += r16[cx];
    wPos = 0x17FC;
      continue;
  case 0x17EE:
    r8[ch] = 0;
    r8[cl] = _data[0x525];
    r8[cl] = r8[cl] + 1;
    r8[cl] <<= 1;
    r8[cl] <<= 1;
    r16[ax] -= r16[cx];
  case 0x17FC:
    r8[bl] = _data[r16[bx] + 0x1025];
    si = r16[bx];
    r16[bx] = r16[ax];
    r16[bx] += 0x0A;
    sub_1799();
    if ( _data16get(r16[bx] + si + 0x1016) & r8[ch] ) // jnz 
      { wPos = 0x1812; continue; }
  case 0x1810:
    _clc();
    return;
  case 0x1812:
    _data[0x57B] = r8[dl];
    r8[dl] += 0x32;
    _data[0x57C] = r8[dl];
    _data16set(0x579, _data16get(0x579) & 0x0FFF8);
    _data[0x55C] = 1;
    _stc();
    wPos = -1;
  }
}
function sub_1830()
{
  _data[0x1665] = 0;
  _data[0x1673] = 0;
  _data[0x1677] = 0;
  _data[0x1678] = 0;
  _data16set(0x166C, 9);
}
function sub_184B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1673] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x17EC) ) // jnz 
      { wPos = 0x185D; continue; }
    return;
  case 0x185D:
    _data16set(0x17EC, r16[dx]);
    if ( _data[0x1677] == 0 ) // jz 
      { wPos = 0x187F; continue; }
    r16[ax] = _data16get(0x1671);
    r16[ax] &= 0x0FFF8;
    r16[bx] = _data16get(0x579);
    r16[bx] &= 0x0FFF8;
    if ( r16[ax] != r16[bx] ) // jnz 
      { wPos = 0x187F; continue; }
    _data[0x1674] = 0;
  case 0x187F:
    _data[0x17E9] = _data[0x17E9] + 1;
    if ( _data16get(0x17EA) > 1 ) // ja 
      { wPos = 0x188E; continue; }
    _data16set(0x17EA, _data16get(0x17EA) -1);
  case 0x188E:
    r16[ax] = _data16get(0x1671);
    r16[dx] = _data16get(0x17EA);
    r8[cl] = 3;
    r8[dl] >>= r8[cl];
    if ( _data[0x1674] < 1 ) // jb 
      { wPos = 0x18B5; continue; }
    if ( _data[0x1674] != 1 ) // jnz 
      { wPos = 0x18AF; continue; }
    r16[ax] += r16[dx];
    if ( r16[ax] < 0x12F ) // jb 
      { wPos = 0x18B5; continue; }
    r16[ax] = 0x12E;
    wPos = 0x18B5;
      continue;
  case 0x18AF:
    cf = (r16[ax] < r16[dx]); // cf-insertion
    r16[ax] -= r16[dx];
    if ( !cf ) // jnb 
      { wPos = 0x18B5; continue; }
    r16[ax] = 0;
  case 0x18B5:
    _data16set(0x1671, r16[ax]);
    r16[bx] = _data16get(0x17DF);
    r8[al] = _data[0x17E9];
    r8[al] >>= 1;
    r8[al] += _data16get(0x1673);
    r8[dl] = r8[al];
    cf = (r8[al] < _data16get(0x1676)); // cf-insertion
    r8[al] -= _data16get(0x1676);
    if ( cf ) // jb 
      { wPos = 0x18E1; continue; }
    zf = (r8[bh] == r8[al]); // zf-insertion
    r8[bh] -= r8[al];
    if ( zf ) // jz 
      { wPos = 0x18D3; continue; }
    cf = (r8[bh] < r8[al]); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0x18E1; continue; }
  case 0x18D3:
    _data[0x1673] = 0;
    _data[0x1678] = 0;
    sub_1922();
    return;
  case 0x18E1:
    _data[0x1673] = r8[dl];
    r16[cx] = _data16get(0x1671);
    _data16set(0x17E1, r16[bx]);
    sub_2CB0();
    _data16set(0x17E7, r16[ax]);
    if ( _data[0x17E9] == 2 ) // jz 
      { wPos = 0x18FD; continue; }
    sub_1922();
  case 0x18FD:
    sub_1B7A();
    if ( cf ) // jb 
      return;
    di = _data16get(0x17E7);
    _data16set(0x17E5, di);
    r16[cx] = _data16get(0x17E1);
    _data16set(0x17E3, r16[cx]);
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = _data16get(0x17DD);
    bp = 0x17EE;
    sub_2CCC();
    wPos = -1;
  }
}
function sub_1922()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x17E5);
  si = 0x17EE;
  r16[cx] = _data16get(0x17E3);
  sub_2D9D();
}
function sub_1936()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x166A]--;
    if ( !_data[0x166A] ) // jz 
      { wPos = 0x193D; continue; }
    return;
  case 0x193D:
    _data[0x166A] = 0x0D;
    if ( _data[0x1665] == 0 ) // jz 
      { wPos = 0x1951; continue; }
    sub_1B05();
  case 0x1951:
    if ( _data[0x1673] != 0 ) // jnz 
      return;
    if ( _data[0x1665] != 0 ) // jnz 
      { wPos = 0x19CD; continue; }
    if ( _data[0x57B] > 0x60 ) // ja 
      return;
    _data[0x1677] = 0;
    if ( _data[0x550] != 1 ) // jnz 
      { wPos = 0x198A; continue; }
    if ( _data[0x418] != 0 ) // jnz 
      { wPos = 0x198A; continue; }
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x556);
    if ( r16[dx] < 0x48 ) // jb 
      { wPos = 0x198A; continue; }
    _data[0x1677] = _data[0x1677] + 1;
  case 0x198A:
    sub_2DFD();
    if ( _data[0x1677] == 0 ) // jz 
      { wPos = 0x199A; continue; }
    r8[dl] &= 3;
    wPos = 0x19A2;
      continue;
  case 0x199A:
    r8[dl] &= 0x0F;
    if ( r8[dl] >= 0x0C ) // jnb 
      return;
  case 0x19A2:
    _data[0x1669] = r8[dl];
    sub_1AEA();
    _data16set(0x1666, r16[cx]);
    _data[0x1668] = r8[dl];
    sub_1B05();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x198A; continue; }
    _data[0x1665] = 0x1D;
    r16[bx] = _data16get(8);
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x181E);
    _data16set(0x166C, r16[ax]);
    _data[0x1670] = 1;
  case 0x19CD:
    sub_1B05();
    if ( unknown_condition() ) // jb cf=1
      return;
    _data[0x1664] = 0;
    sub_1B4C();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x19E1; continue; }
    _data[0x1664] = _data[0x1664] + 1;
    return;
  case 0x19E1:
    if ( _data[0x1665] != 0x10 ) // jnz 
      { wPos = 0x19F0; continue; }
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x166E, r16[dx]);
  case 0x19F0:
    if ( _data[0x1665] != 0x0F ) // jnz 
      { wPos = 0x1A76; continue; }
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x166E);
    if ( r16[dx] >= _data16get(0x166C) ) // jnb 
      { wPos = 0x1A76; continue; }
    if ( _data[0x1670] == 0 ) // jz 
      return;
    if ( _data[0x1673] != 0 ) // jnz 
      return;
    if ( _data[0x418] != 0 ) // jnz 
      return;
    _data[0x1670]--;
    _data[0x1678] = 1;
    r8[al] = _data[0x1668];
    _data[0x1673] = r8[al];
    sub_2DFD();
    r16[dx] &= 0x0F;
    r16[dx] += _data16get(0x1666);
    _data16set(0x1671, r16[dx]);
    r8[al] = 1;
    if ( r16[dx] < _data16get(0x579) ) // jb 
      { wPos = 0x1A42; continue; }
    r8[al] = 0x0FF;
  case 0x1A42:
    _data[0x1674] = r8[al];
    sub_2DFD();
    r8[bl] = r8[dl];
    r16[bx] &= 6;
    r16[ax] = _data16get(r16[bx] + 0x17C9);
    _data16set(0x17DD, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x17D1);
    _data16set(0x17DF, r16[ax]);
    r8[bl] >>= 1;
    r8[al] = _data[r16[bx] + 0x17D9];
    _data[0x1676] = r8[al];
    _data16set(0x17EA, 0x20);
    _data[0x17E9] = 1;
    _data[0x1675] = 0;
    return;
  case 0x1A76:
    _data[0x1665]--;
    r16[cx] = _data16get(0x1666);
    r8[dl] = _data[0x1668];
    if ( _data[0x1665] <= 0x0E ) // jbe 
      { wPos = 0x1A93; continue; }
    r8[dl] += _data16get(0x1665);
    r8[dl] -= 0x0E;
    wPos = 0x1A9A;
      continue;
  case 0x1A93:
    r8[dl] += 0x0E;
    r8[dl] -= _data16get(0x1665);
  case 0x1A9A:
    _data[0x166B] = r8[dl];
    sub_2CB0();
    di = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    _cld();
    r16[cx] = 4;
    if ( _data[0x1665] <= 0x0E ) // jbe 
      { wPos = 0x1AD7; continue; }
    if ( _data[0x418] == 0 ) // jz 
      { wPos = 0x1AD2; continue; }
    r8[al] = _data[0x166B];
    r8[al] -= _data16get(0x1668);
    r8[ah] = 0;
    r8[cl] = 3;
    r16[ax] <<= r8[cl];
    r16[ax] += 0x15E0;
    si = r16[ax];
    r16[cx] = 4;
    _rep_movsw();
    return;
  case 0x1AD2:
    r16[ax] = 0;
    _rep_stosw();
    return;
  case 0x1AD7:
    r8[al] = _data[0x166B];
    r8[al] -= _data16get(0x1668);
    r8[ah] = 0x0A;
    r16[ax] = r8[ah] * r8[al];
    r16[ax] += 0x2681;
    si = r16[ax];
    _rep_movsw();
    wPos = -1;
  }
}
function sub_1AEA()
{
  r8[bh] = 0;
  r8[bl] = r8[dl];
  r8[bl] &= 3;
  r8[bl] <<= 1;
  r16[cx] = _data16get(r16[bx] + 0x1658);
  r8[bl] = r8[dl];
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bl] &= 3;
  r8[dl] = _data[r16[bx] + 0x1660];
}
function sub_1B05()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x1666);
    r8[dl] = _data[0x1668];
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    si = 0x20;
    di = 0x18;
    r16[cx] = 0x0E0F;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      return;
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0x1B4A; continue; }
    if ( _data[0x55A] != 0 ) // jnz 
      { wPos = 0x1B4A; continue; }
    if ( _data[0x57B] >= 0x60 ) // jnb 
      { wPos = 0x1B4A; continue; }
    if ( _data[0x1665] < 5 ) // jb 
      { wPos = 0x1B4A; continue; }
    if ( _data[0x1665] >= 0x19 ) // jnb 
      { wPos = 0x1B4A; continue; }
    _data[0x551] = 1;
  case 0x1B4A:
    _stc();
    wPos = -1;
  }
}
function sub_1B4C()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x1669];
    if ( r8[al] >= 8 ) // jnb 
      { wPos = 0x1B78; continue; }
    r16[bx] = 2;
    if ( !(r8[al] & 4) ) // jz 
      { wPos = 0x1B5C; continue; }
    r8[bl] <<= 1;
  case 0x1B5C:
    r16[ax] = _data16get(r16[bx] + 0x1F30);
    r16[ax] += 0x10;
    if ( r16[ax] < _data16get(0x1666) ) // jb 
      { wPos = 0x1B78; continue; }
    cf = (r16[ax] < 0x30); // cf-insertion
    r16[ax] -= 0x30;
    if ( !cf ) // jnb 
      { wPos = 0x1B70; continue; }
    r16[ax] = 0;
  case 0x1B70:
    if ( r16[ax] > _data16get(0x1666) ) // ja 
      { wPos = 0x1B78; continue; }
    _stc();
    return;
  case 0x1B78:
    _clc();
    wPos = -1;
  }
}
function sub_1B7A()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0x1BE1; continue; }
    r8[dl] = _data[0x1673];
    if ( r8[dl] == 0 ) // jz 
      { wPos = 0x1BE1; continue; }
    r16[cx] = _data16get(0x17DF);
    var temp = r8[cl]; r8[cl] = r8[ch]; r8[ch] = temp;
    // _xchg(r8[cl], r8[ch]);
    si = 0x10;
    r16[ax] = _data16get(0x1671);
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r8[ch] = 0x0E;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      return;
    sub_11E3();
    sub_1922();
    sub_10DD();
    if ( _data[0x1675] != 0 ) // jnz 
      { wPos = 0x1BDF; continue; }
    _data[0x1675] = 1;
    sub_1166();
    r8[dl] = 1;
    if ( _data[0x1674] == 0x0FF ) // jz 
      { wPos = 0x1BCB; continue; }
    r8[dl] = 0x0FF;
  case 0x1BCB:
    _data[0x1674] = r8[dl];
    _data16set(0x17EA, 0x60);
    _data[0x17E9] = 1;
    _data[0x55C] = 0;
  case 0x1BDF:
    _stc();
    return;
  case 0x1BE1:
    _clc();
    wPos = -1;
  }
}
function sub_1BF0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = 0;
    r8[ah] = 0x0B;
    _int(0x10);
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x1C12; continue; }
    if ( _data[0x553] == 0 ) // jz 
      { wPos = 0x1C12; continue; }
    sub_528B();
    _data16set(0x579, 0x98);
    _data[0x57B] = 0x5F;
  case 0x1C12:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _cld();
    _data16set(0x1839, 0);
    sub_1C67();
    sub_5B21();
    sub_1D31();
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0x1C49; continue; }
    if ( _data[0x553] == 0 ) // jz 
      { wPos = 0x1C46; continue; }
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x1C41; continue; }
    sub_5313();
    wPos = 0x1C49;
      continue;
  case 0x1C41:
    sub_38B0();
    wPos = 0x1C49;
      continue;
  case 0x1C46:
    sub_1D76();
  case 0x1C49:
    if ( _data16get(4) == 7 ) // jz 
      { wPos = 0x1C5A; continue; }
    r16[ax] = 0x0AAAA;
    if ( _data16get(4) != 2 ) // jnz 
      { wPos = 0x1C5D; continue; }
  case 0x1C5A:
    r16[ax] = 0x5555;
  case 0x1C5D:
    _data16set(0x1839, r16[ax]);
    sub_1C67();
    sub_5B21();
    wPos = -1;
  }
}
function sub_1C67()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    nullsub_2();
    _data16set(0x1835, 1);
    _data[0x1837] = 8;
    r16[cx] = _data16get(0x579);
    r8[dl] = _data[0x57B];
    r16[cx] += 0x0C;
    r16[cx] &= 0x0FFF0;
    r8[dl] += 8;
    _data[0x1838] = 0;
  case 0x1C8C:
    sub_5897();
    _data16set(0x1832, r16[cx]);
    _data[0x1834] = r8[dl];
    sub_2CB0();
    di = r16[ax];
    r8[bl] = _data[0x1837];
  case 0x1CA0:
    r16[ax] = _data16get(0x1839);
    r16[cx] = _data16get(0x1835);
    r16[cx] >>= 1;
    r16[cx] >>= 1;
    r16[cx] >>= 1;
    _rep_stosw();
    r16[cx] = _data16get(0x1835);
    r16[cx] >>= 1;
    r16[cx] >>= 1;
    r16[cx] &= 0x0FE;
    di -= r16[cx];
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x1CCA; continue; }
    di += 0x50;
  case 0x1CCA:
    r8[bl]--;
    if ( r8[bl] ) // jnz 
      { wPos = 0x1CA0; continue; }
    if ( _data[0x1838] != 0x0F ) // jnz 
      { wPos = 0x1CD6; continue; }
    return;
  case 0x1CD6:
    _data16set(0x1835, _data16get(0x1835) + 0x20);
    _data[0x1837] += 0x10;
    r16[cx] = _data16get(0x1832);
    r8[dl] = _data[0x1834];
    cf = (r16[cx] < 0x10); // cf-insertion
    r16[cx] -= 0x10;
    if ( !cf ) // jnb 
      { wPos = 0x1CF4; continue; }
    r16[cx] = 0;
    _data[0x1838] |= 1;
  case 0x1CF4:
    r16[ax] = _data16get(0x1835);
    r16[ax] += r16[cx];
    if ( r16[ax] < 0x140 ) // jb 
      { wPos = 0x1D0B; continue; }
    r16[ax] = 0x140;
    r16[ax] -= r16[cx];
    _data16set(0x1835, r16[ax]);
    _data[0x1838] |= 2;
  case 0x1D0B:
    cf = (r8[dl] < 8); // cf-insertion
    r8[dl] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x1D17; continue; }
    r8[dl] = 0;
    _data[0x1838] |= 4;
  case 0x1D17:
    r8[al] = _data[0x1837];
    r8[al] += r8[dl];
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x1D22; continue; }
    if ( r8[al] < 0x0C8 ) // jb 
      { wPos = 0x1D2E; continue; }
  case 0x1D22:
    r8[al] = 0x0C8;
    r8[al] -= r8[dl];
    _data[0x1837] = r8[al];
    _data[0x1838] |= 8;
  case 0x1D2E:
    wPos = 0x1C8C;
      continue;
    wPos = -1;
  }
}
function sub_1D31()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x1D48; continue; }
    r8[ah] = 0x0B;
    r8[bh] = 1;
    si = _data16get(4);
    r8[bl] = _data[si + 0x1853];
    _int(0x10);
    wPos = 0x1D67;
      continue;
  case 0x1D48:
    si = _data16get(4);
    r8[bl] = 1;
    r8[bh] = _data[si + 0x183B];
    sub_1D6E();
    r8[bl] = 2;
    r8[bh] = _data[si + 0x1843];
    sub_1D6E();
    r8[bl] = 3;
    r8[bh] = _data[si + 0x184B];
    sub_1D6E();
  case 0x1D67:
    r8[ah] = 0x0B;
    r16[bx] = 0;
    _int(0x10);
    wPos = -1;
  }
}
function sub_1D6E()
{
  r16[ax] = 0x1000;
  _push(si);
  _int(0x10);
  si = _pop();
}
function sub_1D76()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x1D81; continue; }
    sub_6040();
    return;
  case 0x1D81:
    sub_57D5();
    r16[ax] = 0x185B;
    if ( _data[0x552] == 0 ) // jz 
      { wPos = 0x1DC6; continue; }
    r16[bx] = _data16get(0x1C30);
    _data16set(0x1C30, _data16get(0x1C30) + 2);
    r16[bx] &= 6;
    r16[ax] = _data16get(r16[bx] + 0x1C26);
    if ( _data[0x1F80] == 0 ) // jz 
      { wPos = 0x1DAA; continue; }
    _data[0x1F80]--;
  case 0x1DAA:
    if ( _data[0x552] != 0x0DD ) // jnz 
      { wPos = 0x1DC6; continue; }
    if ( _data16get(8) == 0 ) // jz 
      { wPos = 0x1DC6; continue; }
    if ( _data[0x1F80] < 1 ) // jb 
      { wPos = 0x1DC6; continue; }
    sub_5BE0();
    sub_5B21();
    return;
  case 0x1DC6:
    _data16set(0x1C2E, r16[ax]);
    _data16set(0x1C1B, 0x8080);
    _data[0x1C1D] = 0x1C;
  case 0x1DD4:
    sub_1E17();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x1830, r16[dx]);
  case 0x1DDF:
    sub_57E4();
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x1830) ) // jz 
      { wPos = 0x1DDF; continue; }
    if ( _data[0x1C1D] > 0x14 ) // ja 
      { wPos = 0x1E02; continue; }
    r8[bh] = 0;
    r8[bl] = _data[0x1C1D];
    r8[bl] &= 6;
    r16[ax] = _data16get(r16[bx] + 0x1C1E);
    wPos = 0x1E0A;
      continue;
  case 0x1E02:
    r16[ax] = _data16get(0x1C1B);
    _stc();
    fix_code(); // fix carry flag
    r8[al] = _rcr8(r8[al], 1);
    r8[ah] = r8[al];
  case 0x1E0A:
    _data16set(0x1C1B, r16[ax]);
    _data[0x1C1D]--;
    if ( _data[0x1C1D] ) // jnz 
      { wPos = 0x1DD4; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_1E17()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _push(ds);
    es = _pop();
    si = _data16get(0x1C2E);
    di = 0x0E;
    r16[cx] = 0x60;
  case 0x1E24:
    _lodsw();
    r16[ax] &= _data16get(0x1C1B);
    _stosw();
    if ( --r16[cx] )
      { wPos = 0x1E24; continue; }
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x0E;
    di = 0x0ED0;
    r16[cx] = 0x0C08;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_1E40()
{
  _data[0x1CBF] = 0;
  _data16set(0x1CE1, 0);
  _data[0x1CC0] = 0;
  _data[0x1CC1] = 0;
  _data[0x1CB8] = 0;
  _data[0x1CC8] = 0x0B1;
  sub_5450();
}
function sub_1E63()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[cx] = r16[dx];
    r16[dx] -= _data16get(0x1CC9);
    r16[ax] = _data16get(0x1CE1);
    r16[ax] &= 1;
    r16[ax] += 1;
    if ( r16[dx] >= r16[ax] ) // jnb 
      { wPos = 0x1E7B; continue; }
    return;
  case 0x1E7B:
    _data16set(0x1CC9, r16[cx]);
    _data16set(0x1CE1, _data16get(0x1CE1) + 1);
    if ( _data[0x1CC1] == 0 ) // jz 
      { wPos = 0x1EE2; continue; }
    _data[0x1CC1]--;
    if ( _data[0x1CC1] ) // jnz 
      { wPos = 0x1EC9; continue; }
    sub_5B21();
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x1EC2; continue; }
    if ( _data16get(4) == 0 ) // jz 
      { wPos = 0x1EB7; continue; }
    _data[0x552] = 0x0DD;
    _data16set(0x579, 0x0A0);
    _data[0x57B] = 0x60;
    return;
  case 0x1EB7:
    if ( _data[0x1F80] == 0 ) // jz 
      { wPos = 0x1EC2; continue; }
    _data[0x1F80]--;
  case 0x1EC2:
    sub_20E1();
    sub_1E40();
    return;
  case 0x1EC9:
    sub_2022();
    r16[ax] = 0x104;
    r8[al] -= _data16get(0x1CC1);
    if ( _data[0x1CD0] == 0x0FF ) // jz 
      { wPos = 0x1EDC; continue; }
    r8[ah] = 0x0FF;
  case 0x1EDC:
    sub_2059();
    wPos = 0x1FFB;
      continue;
  case 0x1EE2:
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x1F0C; continue; }
    r8[dl] = _data[0x1CB8];
    if ( _data16get(0x1CB9) == 0 ) // jz 
      { wPos = 0x1F02; continue; }
    _data16set(0x1CB9, _data16get(0x1CB9) -1);
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x1F02; continue; }
    r8[dl] = 0x0FF;
  case 0x1F02:
    _data[0x1CD0] = r8[dl];
    r16[ax] = _data16get(0x1CC6);
    wPos = 0x1FAB;
      continue;
  case 0x1F0C:
    if ( _data[0x1CBF] != 0 ) // jnz 
      { wPos = 0x1F75; continue; }
    if ( _data[0x1CC0] != 0 ) // jnz 
      { wPos = 0x1F57; continue; }
    if ( _data[0x1D58] != 0 ) // jnz 
      { wPos = 0x1F3D; continue; }
    if ( _data[0x57B] < 0x0B4 ) // jb 
      return;
    if ( _data[0x558] != 0 ) // jnz 
      return;
    sub_2DFD();
    r16[bx] = _data16get(8);
    if ( r8[dl] < _data16get(r16[bx] + 0x1CD1) ) // jb 
      { wPos = 0x1F3D; continue; }
    return;
  case 0x1F3D:
    r8[al] = 1;
    _data16set(0x59BA, 0);
    if ( _data16get(0x579) >= 0x0A0 ) // jnb 
      { wPos = 0x1F4F; continue; }
    r8[al] = 0x0FF;
  case 0x1F4F:
    _data[0x1CD0] = r8[al];
    _data[0x1CC0] = 4;
  case 0x1F57:
    _data[0x1CC0]--;
    if ( _data[0x1CC0] ) // jnz 
      { wPos = 0x1F65; continue; }
    _data[0x1CBF] = 1;
    wPos = 0x1F75;
      continue;
  case 0x1F65:
    sub_2022();
    r8[al] = _data[0x1CC0];
    r8[ah] = _data[0x1CD0];
    sub_2059();
    wPos = 0x1FFB;
      continue;
  case 0x1F75:
    _data[0x1D58] = 0;
    r16[ax] = _data16get(0x1CC6);
    if ( _data[0x57B] < 0x0B4 ) // jb 
      { wPos = 0x1FAB; continue; }
    if ( _data[0x558] != 0 ) // jnz 
      { wPos = 0x1FAB; continue; }
    sub_2DFD();
    r16[bx] = _data16get(8);
    if ( r8[dl] > _data16get(r16[bx] + 0x1CD9) ) // ja 
      { wPos = 0x1FAB; continue; }
    if ( r16[ax] > _data16get(0x579) ) // ja 
      { wPos = 0x1FA6; continue; }
    _data[0x1CD0] = 1;
    wPos = 0x1FAB;
      continue;
  case 0x1FA6:
    _data[0x1CD0] = 0x0FF;
  case 0x1FAB:
    if ( _data[0x1CD0] < 1 ) // jb 
      { wPos = 0x1FEF; continue; }
    if ( _data[0x1CD0] == 1 ) // jz 
      { wPos = 0x1FE2; continue; }
    cf = (r16[ax] < 8); // cf-insertion
    r16[ax] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x1FEF; continue; }
    r16[ax] = 0;
  case 0x1FBB:
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x1FCC; continue; }
    if ( _data16get(0x1CB9) != 0 ) // jnz 
      { wPos = 0x1FEF; continue; }
    wPos = 0x1FDA;
      continue;
  case 0x1FCC:
    if ( _data[0x57B] < 0x0B4 ) // jb 
      { wPos = 0x1FDA; continue; }
    if ( _data[0x558] == 0 ) // jz 
      { wPos = 0x1FEF; continue; }
  case 0x1FDA:
    _data[0x1CC1] = 4;
    wPos = 0x1FEF;
      continue;
  case 0x1FE2:
    r16[ax] += 8;
    if ( r16[ax] < 0x11E ) // jb 
      { wPos = 0x1FEF; continue; }
    r16[ax] = 0x11E;
    wPos = 0x1FBB;
      continue;
  case 0x1FEF:
    _data16set(0x1CC6, r16[ax]);
    sub_2022();
    _data16set(0x1CC4, 0x0F04);
  case 0x1FFB:
    r16[cx] = _data16get(0x1CC6);
    r8[dl] = _data[0x1CC8];
    sub_2CB0();
    _data16set(0x1CCD, r16[ax]);
    if ( _data[0x1CC0] == 3 ) // jz 
      { wPos = 0x2013; continue; }
    sub_20E1();
  case 0x2013:
    sub_20F5();
    if ( cf ) // jb 
      return;
    r16[ax] = _data16get(0x1CCD);
    _data16set(0x1CBD, r16[ax]);
    sub_209B();
    wPos = -1;
  }
}
function sub_2022()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[bh] = 0;
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x203B; continue; }
    _data[0x1CCF] = _data[0x1CCF] + 1;
    r8[bl] = _data[0x1CCF];
    r8[bl] &= 6;
    r8[bl] |= 8;
    if ( r8[bl] ) // jnz 
      { wPos = 0x2051; continue; }
  case 0x203B:
    _data[0x1CCF] += 2;
    r8[bl] = _data[0x1CCF];
    r8[bl] &= 2;
    if ( _data[0x1CD0] != 1 ) // jnz 
      { wPos = 0x2051; continue; }
    r8[bl] |= 4;
  case 0x2051:
    r16[ax] = _data16get(r16[bx] + 0x15C8);
    _data16set(0x1CBB, r16[ax]);
    wPos = -1;
  }
}
function sub_2059()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 0x0F04;
    r8[cl] -= r8[al];
    _data16set(0x1CC4, r16[cx]);
    if ( r8[ah] == 0x0FF ) // jz 
      { wPos = 0x2078; continue; }
    r8[ah] = 0;
    r8[al] <<= 1;
    _data16set(0x1CBB, _data16get(0x1CBB) + r16[ax]);
    _data16set(0x1CC6, 0);
    wPos = 0x2086;
      continue;
  case 0x2078:
    r8[ah] = 0;
    r8[al] <<= 1;
    r8[al] <<= 1;
    r8[al] <<= 1;
    r16[ax] += 0x120;
    _data16set(0x1CC6, r16[ax]);
  case 0x2086:
    _push(ds);
    es = _pop();
    si = _data16get(0x1CBB);
    di = 0x0E;
    r8[al] = 4;
    sub_2D70();
    _data16set(0x1CBB, 0x0E);
    wPos = -1;
  }
}
function sub_209B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = _data16get(0x1CC4);
    _data16set(0x1CC2, r16[cx]);
    r16[ax] = 0x0B800;
    if ( _data[0x1CB8] != 0 ) // jnz 
      { wPos = 0x20BE; continue; }
    es = r16[ax];
    di = _data16get(0x1CBD);
    si = _data16get(0x1CBB);
    bp = 0x1C40;
    sub_2CCC();
    return;
  case 0x20BE:
    _push(ds);
    ds = r16[ax];
    es = _pop();
    _push(es);
    _push(ds);
    si = _data16get(es*16+0x1CBD);
    di = 0x1C40;
    sub_2DCA();
    es = _pop();
    ds = _pop();
    si = _data16get(0x1CBB);
    di = _data16get(0x1CBD);
    r16[cx] = _data16get(0x1CC4);
    sub_2D9D();
    wPos = -1;
  }
}
function sub_20E1()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x1CBD);
  si = 0x1C40;
  r16[cx] = _data16get(0x1CC2);
  sub_2D9D();
}
function sub_20F5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1CB8] != 0 ) // jnz 
      { wPos = 0x2134; continue; }
    r8[al] = _data[0x1CBF];
    r8[al] |= _data16get(0x1CC0);
    r8[al] |= _data16get(0x1CC1);
    if ( !r8[al] ) // jz 
      { wPos = 0x2134; continue; }
    if ( _data[0x57B] < 0x0A3 ) // jb 
      { wPos = 0x2134; continue; }
    if ( _data[0x558] != 0 ) // jnz 
      { wPos = 0x2134; continue; }
    r16[ax] = _data16get(0x1CC6);
    r16[ax] += 0x20;
    if ( r16[ax] < _data16get(0x579) ) // jb 
      { wPos = 0x2134; continue; }
    cf = (r16[ax] < 0x38); // cf-insertion
    r16[ax] -= 0x38;
    if ( !cf ) // jnb 
      { wPos = 0x212A; continue; }
    r16[ax] = 0;
  case 0x212A:
    if ( r16[ax] > _data16get(0x579) ) // ja 
      { wPos = 0x2134; continue; }
    sub_2136();
    return;
  case 0x2134:
    _clc();
    wPos = -1;
  }
}
function sub_2136()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x2149; continue; }
    r8[al] = _data[0x57B];
    _data[0x1CC8] = r8[al];
    r16[ax] = _data16get(0x579);
    _data16set(0x1CC6, r16[ax]);
  case 0x2149:
    r16[ax] = _data16get(0x1CC6);
    r16[ax] += _data16get(0x579);
    r16[ax] >>= 1;
    if ( r16[ax] < 0x118 ) // jb 
      { wPos = 0x215A; continue; }
    r16[ax] = 0x117;
  case 0x215A:
    _data16set(0x1CC6, r16[ax]);
    r8[bl] = 1;
    if ( r16[ax] > 0x0A0 ) // ja 
      { wPos = 0x216E; continue; }
    r8[bl] = 0x0FF;
    r16[dx] = 0x0A1;
    r16[dx] -= r16[ax];
    wPos = 0x2173;
      continue;
  case 0x216E:
    r16[ax] -= 0x9F;
    r16[dx] = r16[ax];
  case 0x2173:
    _data[0x1CB8] = r8[bl];
    _data[0x1CBF] = 1;
    _data[0x1CC1] = 0;
    r8[cl] = 3;
    r16[dx] >>= r8[cl];
    _data16set(0x1CB9, r16[dx]);
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x21BD; continue; }
    sub_11E3();
    r8[al] = _data[0x1CB8];
    _push(r16[ax]);
    _data[0x1CB8] = 0;
    _data16set(0x1CC4, 0x0F04);
    r16[ax] = _data16get(0x15C8);
    _data16set(0x1CBB, r16[ax]);
    r16[cx] = _data16get(0x1CC6);
    r8[dl] = _data[0x1CC8];
    sub_2CB0();
    _data16set(0x1CBD, r16[ax]);
    sub_209B();
    r16[ax] = _pop();
    _data[0x1CB8] = r8[al];
  case 0x21BD:
    sub_20E1();
    sub_11E3();
    r16[ax] = 0;
    if ( _data16get(0x579) >= 0x0A0 ) // jnb 
      { wPos = 0x21D1; continue; }
    r16[ax] = 0x122;
  case 0x21D1:
    _data16set(0x579, r16[ax]);
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0x21DE; continue; }
    sub_70D();
  case 0x21DE:
    _stc();
    wPos = -1;
  }
}
function sub_21E0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x1CBF];
    r8[al] |= _data16get(0x1CC0);
    r8[al] |= _data16get(0x1CC1);
    if ( !r8[al] ) // jz 
      { wPos = 0x2209; continue; }
    r16[ax] = _data16get(0x327D);
    r8[dl] = _data[0x327F];
    si = 0x10;
    r16[bx] = _data16get(0x1CC6);
    r8[dh] = _data[0x1CC8];
    di = 0x20;
    r16[cx] = 0x0F1E;
    sub_2E29();
    return;
  case 0x2209:
    _clc();
    wPos = -1;
  }
}
function sub_2210()
{
  _data[0x1D59] = 0;
}
function sub_2216()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x1D5A) ) // jnz 
      { wPos = 0x2221; continue; }
    return;
  case 0x2221:
    r16[cx] = r16[dx];
    _data16set(0x1D5A, r16[cx]);
    sub_22F7();
    if ( cf ) // jb 
      return;
    if ( _data[0x1D59] != 0 ) // jnz 
      { wPos = 0x226D; continue; }
    if ( _data[0x57B] == 0x86 ) // jz 
      { wPos = 0x224E; continue; }
    if ( _data[0x57B] == 0x8E ) // jz 
      { wPos = 0x224E; continue; }
    sub_2DFD();
    if ( r8[dl] > 5 ) // ja 
      return;
  case 0x224E:
    sub_15D0();
    r8[dl] += 3;
    _data[0x1D5E] = r8[dl];
    sub_2DFD();
    r16[dx] &= 7;
    r16[cx] += r16[dx];
    r16[cx] += 6;
    _data16set(0x1D5C, r16[cx]);
    _data[0x1D59] = 0x1B;
  case 0x226D:
    _data[0x1D59]--;
    r16[cx] = _data16get(0x1D5C);
    r8[dl] = _data[0x1D5E];
    if ( _data[0x1D59] <= 0x0D ) // jbe 
      { wPos = 0x2291; continue; }
    r8[dl] += _data16get(0x1D59);
    r8[dl] -= 0x0F;
    r16[bx] = 0x1B02;
    r8[bh] -= _data16get(0x1D59);
    wPos = 0x229F;
      continue;
  case 0x2291:
    r8[dl] += 0x0C;
    r8[dl] -= _data16get(0x1D59);
    r16[bx] = 2;
    r8[bh] += _data16get(0x1D59);
  case 0x229F:
    _data16set(0x1D64, r16[bx]);
    _data[0x1D5F] = r8[dl];
    sub_2CB0();
    _data16set(0x1D62, r16[ax]);
    sub_22DC();
    sub_22F7();
    if ( cf ) // jb 
      return;
    if ( _data[0x1D59] != 0 ) // jnz 
      { wPos = 0x22BD; continue; }
    return;
  case 0x22BD:
    r16[ax] = 0x0B800;
    es = r16[ax];
    di = _data16get(0x1D62);
    si = 0x1CF0;
    _data16set(0x1D60, di);
    r16[cx] = _data16get(0x1D64);
    _data16set(0x1D66, r16[cx]);
    bp = 0x1D24;
    sub_2CCC();
    wPos = -1;
  }
}
function sub_22DC()
{
  if ( _data[0x1D59] == 0x1A ) // jz 
    return;
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x1D60);
  si = 0x1D24;
  r16[cx] = _data16get(0x1D66);
  sub_2D9D();
}
function sub_22F7()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1D59] != 0 ) // jnz 
      { wPos = 0x2300; continue; }
    _clc();
    return;
  case 0x2300:
    r16[cx] = _data16get(0x1D64);
    var temp = r8[cl]; r8[cl] = r8[ch]; r8[ch] = temp;
    //_xchg(r8[ch], r8[cl]);
    r16[ax] = _data16get(0x1D5C);
    r8[dl] = _data[0x1D5F];
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r8[ch] = 0x0E;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      return;
    _data[0x1D58] = 1;
    wPos = -1;
  }
}
function sub_2330()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x1F6C, 0);
    r16[ax] = 0;
    r8[dl] = 1;
    if ( _data16get(0x579) > 0x0A0 ) // ja 
      { wPos = 0x2347; continue; }
    r16[ax] = 0x12C;
    r8[dl] = 0x0FF;
  case 0x2347:
    _data16set(0x1F30, r16[ax]);
    _data16set(0x1F32, r16[ax]);
    _data16set(0x1F34, r16[ax]);
    _data[0x1F3C] = r8[dl];
    _data[0x1F3D] = r8[dl];
    _data[0x1F3E] = r8[dl];
    _data[0x1F48] = 1;
    _data[0x1F49] = 1;
    _data[0x1F4A] = 1;
    _data[0x1F50] = 0;
    _data[0x1F51] = 0;
    _data[0x1F52] = 0;
    wPos = -1;
  }
}
function sub_237B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x1F65) ) // jnz 
      { wPos = 0x2386; continue; }
    return;
  case 0x2386:
    _data16set(0x1F65, r16[dx]);
    if ( _data[0x55A] != 0 ) // jnz 
      return;
    r16[bx] = _data16get(0x1F6C);
    r16[bx] = r16[bx] + 1;
    if ( r16[bx] < 3 ) // jb 
      { wPos = 0x239E; continue; }
    r16[bx] = 0;
  case 0x239E:
    _data16set(0x1F6C, r16[bx]);
    sub_265E();
    if ( cf ) // jb cf=1
      return;
    sub_2567();
    if ( cf ) // jb cf=1
      return;
    r16[bx] = _data16get(0x1F6C);
    if ( _data[r16[bx] + 0x1F50] == 0 ) // jz 
      { wPos = 0x23EB; continue; }
    r8[ah] = 0;
    _int(0x1A);
    r16[bx] = _data16get(0x1F6C);
    r8[bl] <<= 1;
    r16[dx] -= _data16get(r16[bx] + 0x1F53);
    if ( r16[dx] < 0x36 ) // jb 
      return;
    r8[dl] = 1;
    r16[ax] = 0;
    if ( _data16get(0x579) > 0x0A0 ) // ja 
      { wPos = 0x23DC; continue; }
    r16[ax] = 0x12C;
    r8[dl] = 0x0FF;
  case 0x23DC:
    _data16set(r16[bx] + 0x1F30, r16[ax]);
    r8[bl] >>= 1;
    _data[r16[bx] + 0x1F50] = 0;
    _data[r16[bx] + 0x1F3C] = r8[dl];
  case 0x23EB:
    r8[dl] = _data[r16[bx] + 0x1F3C];
    _data[r16[bx] + 0x1F3F] = r8[dl];
    if ( _data[0x1664] == 0 ) // jz 
      { wPos = 0x2403; continue; }
    _data16set(0x1F69, 0x0C);
    wPos = 0x2418;
      continue;
  case 0x2403:
    r16[ax] = 8;
    if ( _data[0x57B] <= 0x60 ) // jbe 
      { wPos = 0x240F; continue; }
    r8[al] >>= 1;
  case 0x240F:
    _data16set(0x1F69, r16[ax]);
    if ( r16[bx] != _data16get(0x52F) ) // jnz 
      { wPos = 0x2425; continue; }
  case 0x2418:
    if ( _data[r16[bx] + 0x1F3C] != 0 ) // jnz 
      { wPos = 0x2425; continue; }
    sub_2DFD();
    wPos = 0x248A;
      continue;
  case 0x2425:
    if ( _data[0x55C] == 0 ) // jz 
      { wPos = 0x2466; continue; }
    r8[al] = _data[r16[bx] + 0x1F36];
    if ( r8[al] > _data16get(0x57B) ) // ja 
      { wPos = 0x2466; continue; }
    r8[al] += 0x10;
    if ( r8[al] < _data16get(0x57B) ) // jb 
      { wPos = 0x2466; continue; }
    sub_2DFD();
    si = _data16get(8);
    if ( r8[dl] > _data16get(si + 0x1F6E) ) // ja 
      { wPos = 0x2466; continue; }
    _data16set(0x1F69, 0x0C);
    r8[al] = 1;
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x1F30);
    r8[bl] >>= 1;
    if ( r16[cx] < _data16get(0x579) ) // jb 
      { wPos = 0x2463; continue; }
    r8[al] = 0x0FF;
  case 0x2463:
    wPos = 0x2492;
      continue;
  case 0x2466:
    r8[cl] = 0x18;
    if ( _data[0x57B] <= 0x60 ) // jbe 
      { wPos = 0x247A; continue; }
    r8[cl] = 0x28;
    if ( _data[r16[bx] + 0x1F3C] != 0 ) // jnz 
      { wPos = 0x247A; continue; }
    r8[cl] = 0x10;
  case 0x247A:
    sub_2DFD();
    if ( r8[dl] > r8[cl] ) // ja 
      { wPos = 0x2496; continue; }
    r8[al] = 0;
    if ( _data[r16[bx] + 0x1F3C] != 0 ) // jnz 
      { wPos = 0x2492; continue; }
  case 0x248A:
    r8[al] = r8[dl];
    r8[al] &= 1;
    if ( r8[al] ) // jnz 
      { wPos = 0x2492; continue; }
    r8[al] = 0x0FF;
  case 0x2492:
    _data[r16[bx] + 0x1F3C] = r8[al];
  case 0x2496:
    r8[dl] = _data[r16[bx] + 0x1F3C];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x1F30);
    if ( r8[dl] < 1 ) // jb 
      { wPos = 0x24C2; continue; }
    if ( r8[dl] != 1 ) // jnz 
      { wPos = 0x24B8; continue; }
    r16[ax] += _data16get(0x1F69);
    if ( r16[ax] < 0x12F ) // jb 
      { wPos = 0x24C2; continue; }
    r16[ax] = 0x12E;
    r8[dl] = 0x0FF;
    wPos = 0x24C2;
      continue;
  case 0x24B8:
    cf = (r16[ax] < _data16get(0x1F69)); // cf-insertion
    r16[ax] -= _data16get(0x1F69);
    if ( !cf ) // jnb 
      { wPos = 0x24C2; continue; }
    r16[ax] = 0;
    r8[dl] = 1;
  case 0x24C2:
    _data16set(r16[bx] + 0x1F30, r16[ax]);
    r8[bl] >>= 1;
    _data[r16[bx] + 0x1F3C] = r8[dl];
    r8[dl] = _data[r16[bx] + 0x1F36];
    r16[cx] = r16[ax];
    sub_2CB0();
    _data16set(0x1F4B, r16[ax]);
    r16[bx] = _data16get(0x1F6C);
    if ( _data[r16[bx] + 0x1F48] != 0 ) // jnz 
      { wPos = 0x24F0; continue; }
    r8[al] = _data[r16[bx] + 0x1F3C];
    r8[al] |= _data16get(r16[bx] + 0x1F3F);
    if ( !r8[al] ) // jz 
      { wPos = 0x24F0; continue; }
    sub_254D();
  case 0x24F0:
    sub_265E();
    if ( cf ) // jb cf=1
      return;
    sub_2567();
    if ( !cf ) // jnb cf=0
      { wPos = 0x24FB; continue; }
    return;
  case 0x24FB:
    r16[bx] = _data16get(0x1F6C);
    _data[r16[bx] + 0x1F48] = 0;
    if ( _data[r16[bx] + 0x1F3C] != 0 ) // jnz 
      { wPos = 0x2518; continue; }
    if ( _data[r16[bx] + 0x1F3F] == 0 ) // jz 
      return;
    si = 0x1E30;
    wPos = 0x2533;
      continue;
  case 0x2518:
    si = 0x1E50;
    _data[r16[bx] + 0x1F4D] = _data[r16[bx] + 0x1F4D] + 1;
    if ( _data[r16[bx] + 0x1F4D] & 1 ) // jnz 
      { wPos = 0x2529; continue; }
    si += 0x20;
  case 0x2529:
    if ( _data[r16[bx] + 0x1F3C] == 1 ) // jz 
      { wPos = 0x2533; continue; }
    si += 0x40;
  case 0x2533:
    r8[bl] <<= 1;
    di = _data16get(0x1F4B);
    _data16set(r16[bx] + 0x1F42, di);
    r16[ax] = 0x0B800;
    es = r16[ax];
    bp = _data16get(r16[bx] + 0x1F59);
    r16[cx] = 0x802;
    sub_2D35();
    wPos = -1;
  }
}
function sub_254D()
{
  r16[bx] = _data16get(0x1F6C);
  r8[bl] <<= 1;
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(r16[bx] + 0x1F42);
  si = _data16get(r16[bx] + 0x1F59);
  r16[cx] = 0x802;
  sub_2D9D();
}
function sub_2567()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = _data16get(0x1F6C);
    r8[dl] = _data[r16[bx] + 0x1F36];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x1F30);
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E08;
    sub_2E29();
    if ( cf ) // jb cf=1
      { wPos = 0x258E; continue; }
    return;
//    wPos = 0xlocret_code_265D;
//      continue;
  case 0x258E:
    r16[bx] = _data16get(0x1F6C);
    if ( _data[r16[bx] + 0x1F50] != 0 ) // jnz 
      { wPos = 0x260C; continue; }
    if ( _data[0x57C] < 0x26 ) // jb 
      { wPos = 0x260C; continue; }
    if ( _data[0x55C] == 0 ) // jz 
      { wPos = 0x260E; continue; }
    _data[0x55C] = 0;
    _data[0x55B] = 0x11;
    _data[0x571] = 1;
    _data[0x56E] = 0;
    r16[bx] = _data16get(0x1F6C);
    r8[bl] <<= 1;
    di = _data16get(r16[bx] + 0x1F42);
    if ( _data16get(r16[bx] + 0x1F30) < 0x10 ) // jb 
      { wPos = 0x25CF; continue; }
    di -= 4;
  case 0x25CF:
    _data16set(0x1F67, di);
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x1D70;
    bp = 0x0E;
    r16[cx] = 0x806;
    sub_2CCC();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x1F65, r16[dx]);
  case 0x25EC:
    sub_5A90();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x1F65);
    if ( r16[dx] < 8 ) // jb 
      { wPos = 0x25EC; continue; }
    sub_5B21();
    di = _data16get(0x1F67);
    si = 0x0E;
    r16[cx] = 0x806;
    sub_2D9D();
  case 0x260C:
    _stc();
    return;
  case 0x260E:
    r8[ah] = 0;
    _int(0x1A);
    r16[bx] = _data16get(0x1F6C);
    _data[r16[bx] + 0x1F50] = 1;
    _data[r16[bx] + 0x1F3C] = 1;
    r8[bl] <<= 1;
    _data16set(r16[bx] + 0x1F53, r16[dx]);
    sub_11E3();
    r16[bx] = _data16get(0x1F6C);
    r8[bl] <<= 1;
    si = _data16get(r16[bx] + 0x1F5F);
    di = _data16get(r16[bx] + 0x1F42);
    r16[ax] = 0x0B800;
    es = r16[ax];
    bp = 0x0E;
    r16[cx] = 0x802;
    sub_2CCC();
    sub_1124();
    r16[bx] = _data16get(0x1F6C);
    r8[al] = _data[r16[bx] + 0x1F39];
    sub_2706();
    r16[ax] = 0x3E8;
    r16[bx] = 0x2EE;
    sub_593B();
    _stc();
    wPos = -1;
  }
}
function sub_265E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1673] != 0 ) // jnz 
      { wPos = 0x2667; continue; }
    _clc();
    return;
  case 0x2667:
    r16[bx] = _data16get(0x1F6C);
    r8[dl] = _data[r16[bx] + 0x1F36];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x1F30);
    si = 0x10;
    di = si;
    r16[bx] = _data16get(0x1671);
    r8[dh] = _data[0x1673];
    r16[cx] = 0x0C08;
    sub_2E29();
    wPos = -1;
  }
}
function sub_2690()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(ds);
    es = _pop();
    r16[cx] = 7;
    si = 0x1F82;
  case 0x2698:
    _lodsb();
    r16[bx] = 7;
    r16[bx] -= r16[cx];
    if ( --r16[cx] && (r8[al] == _data16get(r16[bx] + 0x1F89)) )
      { wPos = 0x2698; continue; }
    if ( r8[al] > _data16get(r16[bx] + 0x1F89) ) // ja 
      { wPos = 0x26A7; continue; }
    return;
  case 0x26A7:
    si = 0x1F82;
    di = 0x1F89;
    r16[cx] = 7;
    _rep_movsb();
    wPos = -1;
  }
}
function sub_26B3()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x1F80];
    if ( r8[al] != _data16get(0x1F81) ) // jnz 
      { wPos = 0x26BD; continue; }
    return;
  case 0x26BD:
    _data[0x1F81] = r8[al];
    r8[ah] = 0;
    r8[cl] = 4;
    r16[ax] <<= r8[cl];
    r16[ax] += 0x2720;
    si = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    di = 0x1260;
    r16[cx] = 0x801;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_26DA()
{
  di = 0x1F82;
  sub_26E8();
}
function sub_26E1()
{
  di = 0x1F89;
  sub_26E8();
}
function sub_26E8()
{
  _push(ds);
  es = _pop();
  r16[cx] = 7;
  r8[al] = 0;
  _rep_stosb();
}
function sub_26F2()
{
  r16[bx] = 0x1F89;
  di = 0x12CA;
  sub_2739();
}
function sub_26FC()
{
  r16[bx] = 0x1F82;
  di = 0x143C;
  sub_2739();
}
function sub_2706()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 6;
  case 0x2709:
    r16[bx] = r16[cx];
    r8[ah] = 0;
    r8[al] += _data16get(r16[bx] + 0x1F81);
    _aaa();
    _data[r16[bx] + 0x1F81] = r8[al];
    r8[al] = r8[ah];
    if ( --r16[cx] )
      { wPos = 0x2709; continue; }
    sub_26FC();
    wPos = -1;
  }
}
function sub_271E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(r16[cx]);
    _push(r16[ax]);
    _push(r16[bx]);
    _clc();
    _pushf();
    r16[cx] = 7;
  case 0x2726:
    _popf();
    r16[bx] = r16[cx];
    r16[bx]--;
    r8[al] = _data[r16[bx] + di];
    unknown_condition(); // verify cf
    r8[al] = r8[al] + _data16get(r16[bx] + si) + cf;
    _aaa();
    _data[r16[bx] + di] = r8[al];
    _pushf();
    if ( --r16[cx] )
      { wPos = 0x2726; continue; }
    _popf();
    r16[bx] = _pop();
    r16[ax] = _pop();
    r16[cx] = _pop();
    wPos = -1;
  }
}
function sub_2739()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _data16set(0x1F90, di);
    _data16set(0x1F93, r16[bx]);
    _data[0x1F92] = 0;
  case 0x274B:
    r16[bx] = _data16get(0x1F93);
    r8[al] = _data[r16[bx]];
    r8[ah] = 0;
    r8[cl] = 4;
    r16[ax] <<= r8[cl];
    r16[ax] += 0x2720;
    si = r16[ax];
    di = _data16get(0x1F90);
    r16[cx] = 0x801;
    sub_2D9D();
    _data16set(0x1F90, _data16get(0x1F90) + 2);
    _data16set(0x1F93, _data16get(0x1F93) + 1);
    _data[0x1F92] = _data[0x1F92] + 1;
    if ( _data[0x1F92] == 7 ) // jz 
      return;
    if ( _data[0x1F92] != 3 ) // jnz 
      { wPos = 0x274B; continue; }
    _data16set(0x1F90, _data16get(0x1F90) + 2);
    wPos = 0x274B;
      continue;
    wPos = -1;
  }
}
function sub_2790()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    if ( _data16get(4) != 2 ) // jnz 
      { wPos = 0x27EE; continue; }
    _cld();
    di = 0;
    r16[ax] = 0x0AAAA;
    r16[cx] = 0x50;
    _rep_stosw();
    di = 0x2000;
    r16[cx] = 0x50;
    _rep_stosw();
    _data16set(0x2654, 0);
  case 0x27B5:
    sub_2DFD();
    r16[dx] &= 0x18;
    if ( r8[dl] == _data16get(0x2653) ) // jz 
      { wPos = 0x27B5; continue; }
    _data[0x2653] = r8[dl];
    r16[bx] = _data16get(0x2654);
    _data[r16[bx] + 0x2656] = r8[dl];
    r16[dx] += 0x2020;
    si = r16[dx];
    di = r16[bx];
    di <<= 1;
    di += 0x0A0;
    r16[cx] = 0x401;
    sub_2D9D();
    _data16set(0x2654, _data16get(0x2654) + 1);
    if ( _data16get(0x2654) < 0x28 ) // jb 
      { wPos = 0x27B5; continue; }
    return;
  case 0x27EE:
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0x27F9; continue; }
    sub_300F();
    return;
  case 0x27F9:
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x283E; continue; }
    r16[ax] = 0;
    sub_29A0();
    r16[bx] = 0x2570;
    r16[ax] = 0x64A;
    sub_2B24();
    _data16set(0x2650, 0x48);
    _data[0x2652] = 0x38;
    r16[ax] = 0x0DD2;
    sub_2958();
    r16[ax] = 0x0DF6;
    sub_2970();
    si = 0x1FA0;
    di = 0x67E;
    r16[cx] = 0x1002;
    sub_2D9D();
    r16[bx] = 0x2344;
    r16[ax] = 0x0B84;
    sub_2B24();
    sub_4B47();
    return;
  case 0x283E:
    if ( _data16get(4) != 5 ) // jnz 
      { wPos = 0x288D; continue; }
    r16[ax] = 0x640;
    sub_29A0();
    r16[bx] = 0x2570;
    r16[ax] = 0x0CB6;
    sub_2B24();
    _data16set(0x2650, 0x0F8);
    _data[0x2652] = 0x60;
    r16[ax] = 0x140E;
    sub_2958();
    r16[ax] = 0x1434;
    sub_2970();
    r16[ax] = 0x143E;
    sub_2970();
    r16[ax] = 0x16A0;
    sub_2988();
    r16[bx] = 0x2344;
    r16[ax] = 0x1184;
    sub_2B24();
    si = 0x1FE0;
    di = 0x0DD6;
    r16[cx] = 0x1002;
    sub_2D9D();
    return;
  case 0x288D:
    if ( _data16get(4) != 4 ) // jnz 
      { wPos = 0x28BE; continue; }
    r16[ax] = 0x640;
    sub_29A0();
    r16[bx] = 0x2570;
    r16[ax] = 0x0CBA;
    sub_2B24();
    _data16set(0x2650, 0x108);
    _data[0x2652] = 0x60;
    r16[ax] = 0x1439;
    sub_2958();
    r16[ax] = 0x16C0;
    sub_2945();
    sub_3F9E();
    return;
  case 0x28BE:
    if ( _data16get(4) != 3 ) // jnz 
      { wPos = 0x2909; continue; }
    r16[ax] = 0x640;
    sub_29A0();
    r16[bx] = 0x2570;
    r16[ax] = 0x0C90;
    sub_2B24();
    _data16set(0x2650, 0x60);
    _data[0x2652] = 0x60;
    r16[ax] = 0x140C;
    sub_2958();
    r16[ax] = 0x1418;
    sub_2970();
    r16[bx] = 0x2344;
    r16[ax] = 0x1184;
    sub_2B24();
    r16[bx] = 0x2344;
    r16[ax] = 0x11A2;
    sub_2B24();
    r16[bx] = 0x2624;
    r16[ax] = 0;
    sub_2B24();
    sub_3BDB();
    return;
  case 0x2909:
    r16[ax] = 0x640;
    sub_29A0();
    r16[bx] = 0x2570;
    r16[ax] = 0x0CA0;
    sub_2B24();
    _data16set(0x2650, 0x0A0);
    _data[0x2652] = 0x60;
    r16[ax] = 0x1406;
    sub_2958();
    r16[bx] = 0x2344;
    r16[ax] = 0x11C4;
    sub_2B24();
    r16[ax] = 0x1422;
    sub_2970();
    r16[ax] = 0x1690;
    sub_2988();
    r16[ax] = 0x16B6;
    sub_2945();
    wPos = -1;
  }
}
function sub_2945()
{
  _data16set(0x2634, r16[ax]);
  r16[bx] = 0x2384;
  sub_2B24();
  r16[ax] = _data16get(0x2634);
  r16[bx] = 0x238C;
  sub_2B24();
}
function sub_2958()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x2634, r16[ax]);
    si = 8;
  case 0x295E:
    r16[ax] = _data16get(0x2634);
    r16[bx] = _data16get(si + 0x2634);
    _push(si);
    sub_2B24();
    si = _pop();
    zf = (si == 2); // zf-insertion
    si -= 2;
    if ( !zf ) // jnz 
      { wPos = 0x295E; continue; }
    wPos = -1;
  }
}
function sub_2970()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x2634, r16[ax]);
    si = 0x0A;
  case 0x2976:
    r16[ax] = _data16get(0x2634);
    r16[bx] = _data16get(si + 0x263C);
    _push(si);
    sub_2B24();
    si = _pop();
    zf = (si == 2); // zf-insertion
    si -= 2;
    if ( !zf ) // jnz 
      { wPos = 0x2976; continue; }
    wPos = -1;
  }
}
function sub_2988()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x2634, r16[ax]);
    si = 8;
  case 0x298E:
    r16[ax] = _data16get(0x2634);
    r16[bx] = _data16get(si + 0x2646);
    _push(si);
    sub_2B24();
    si = _pop();
    zf = (si == 2); // zf-insertion
    si -= 2;
    if ( !zf ) // jnz 
      { wPos = 0x298E; continue; }
    wPos = -1;
  }
}
function sub_29A0()
{
  _data16set(0x267E, r16[ax]);
  r16[bx] = 0x251C;
  sub_2B24();
  r16[ax] = 0;
  _cld();
  di = _data16get(0x267E);
  di += 0x284;
  r16[cx] = 0x24;
  _rep_stosw();
  di = _data16get(0x267E);
  di += 0x1184;
  r16[cx] = 0x24;
  _rep_stosw();
  di = _data16get(0x267E);
  di += 0x2284;
  r8[al] = 0x2A;
  sub_29E1();
  di = _data16get(0x267E);
  di += 0x22CB;
  r8[al] = 0x0A8;
  sub_29E1();
}
function sub_29E1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 0x5F;
  case 0x29E4:
    _video[di] = r8[al];
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x29F4; continue; }
    di += 0x50;
  case 0x29F4:
    if ( --r16[cx] )
      { wPos = 0x29E4; continue; }
    wPos = -1;
  }
}
function sub_2A00()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  _cld();
  di = 0;
  r16[ax] = 0x0AAAA;
  r16[cx] = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  r16[cx] = 0x0FA0;
  _rep_stosw();
  sub_2B9E();
  r16[bx] = 0x28A0;
  r16[ax] = 0;
  sub_2B24();
  sub_2A68();
  sub_2C84();
  sub_2B8B();
  sub_2A80();
}
function sub_2A30()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  _cld();
  di = 0;
  r16[ax] = 0x0AAAA;
  r16[cx] = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  r16[cx] = 0x0FA0;
  _rep_stosw();
  sub_2B9E();
  r16[bx] = 0x28A0;
  r16[ax] = 0;
  sub_2B24();
  sub_2A68();
  r16[ax] = _data16get(8);
  _push(r16[ax]);
  _data16set(8, 1);
  sub_2C84();
  r16[ax] = _pop();
  _data16set(8, r16[ax]);
}
function sub_2A68()
{
  r16[bx] = _data16get(0x6DF8);
  r16[bx] &= 3;
  r8[bl] <<= 1;
  si = _data16get(r16[bx] + 0x2AD1);
  di = 0x1902;
  r16[cx] = 0x801;
  sub_2D9D();
}
function sub_2A80()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = 0x0F;
  case 0x2A83:
    _data[r16[bx] + 0x1015] = 0;
    r16[bx]--;
    if ( r16[bx] ) // jnz 
      { wPos = 0x2A83; continue; }
    di = 0x140;
    r8[bh] = 0x80;
    _data16set(0x2ACA, 0);
    sub_2AC6();
    di = 0x640;
    r8[bh] = 0x30;
    _data16set(0x2ACA, 5);
    sub_2AC6();
    di = 0x0B40;
    r8[bh] = 0;
    _data16set(0x2ACA, 0x0A);
    sub_2AC6();
    _data[0x525] = 0x10;
    _data16set(0x52F, 0);
    _data[0x531] = 1;
    wPos = -1;
  }
}
function sub_2AC6()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x2AC9] = r8[bh];
    _data[0x2AC4] = 0;
  case 0x2ACF:
    _push(di);
    _push(es);
    r16[bx] = _data16get(8);
    r8[bl] = _data[r16[bx] + 0x2ABA];
    r8[bh] = _data[0x2AC9];
    r16[ax] = seg_data;
    es = r16[ax];
    di = 0x4D7;
    sub_67D();
    es = _pop();
    di = _pop();
    _push(di);
    si = 0x4D7;
    r16[cx] = 0x1002;
    sub_2D9D();
    r8[bh] = 0;
    r8[bl] = _data[0x2AC4];
    r8[cl] = r8[bl];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[cl] = ~ r8[cl];
    r8[cl] &= 3;
    r8[cl] <<= 1;
    r8[al] = _data[0x540];
    r8[al] <<= r8[cl];
    si = _data16get(0x2ACA);
    _data16set(r16[bx] + si + 0x1016, _data16get(r16[bx] + si + 0x1016) | r8[al]);
    di = _pop();
    di += 4;
    _data[0x2AC4] = _data[0x2AC4] + 1;
    if ( _data[0x2AC4] < 0x14 ) // jb 
      { wPos = 0x2ACF; continue; }
    wPos = -1;
  }
}
function sub_2B24()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = _data16get(r16[bx]);
    _data16set(0x2AC7, r16[cx]);
    _data16set(0x2ACC, r16[ax]);
    r16[bx] += 2;
  case 0x2B30:
    si = _data16get(r16[bx]);
    if ( si != 0x0FFFF ) // jnz 
      { wPos = 0x2B39; continue; }
    return;
  case 0x2B39:
    di = _data16get(r16[bx] + 2);
    di += _data16get(0x2ACC);
    _cld();
    _data[0x2AD0] = r8[ch];
    r8[ch] = 0;
    _data16set(0x2ACE, r16[cx]);
  case 0x2B4B:
    r16[cx] = _data16get(0x2ACE);
    _rep_movsb();
    di -= _data16get(0x2ACE);
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x2B62; continue; }
    di += 0x50;
  case 0x2B62:
    _data[0x2AD0]--;
    if ( _data[0x2AD0] ) // jnz 
      { wPos = 0x2B4B; continue; }
    r16[bx] += 4;
    r16[cx] = _data16get(0x2AC7);
    wPos = 0x2B30;
      continue;
    wPos = -1;
  }
}
function sub_2B71()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x2AC4] = 4;
  case 0x2B76:
    si = 0x2680;
    r16[cx] = 0x1005;
    _push(di);
    sub_2D9D();
    di = _pop();
    di += 0x14;
    _data[0x2AC4]--;
    if ( _data[0x2AC4] ) // jnz 
      { wPos = 0x2B76; continue; }
    wPos = -1;
  }
}
function sub_2B8B()
{
  di = 0x3C5;
  sub_2B71();
  di = 0x8C5;
  sub_2B71();
  di = 0x0DC5;
  sub_2B71();
}
function sub_2B9E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x2AC2, 0x103E);
  case 0x2BA4:
    _data16set(0x2AC2, _data16get(0x2AC2) + 2);
    di = _data16get(0x2AC2);
    if ( di >= 0x1090 ) // jnb 
      { wPos = 0x2BD2; continue; }
  case 0x2BB3:
    sub_2DFD();
    r16[dx] &= 0x30;
    if ( r8[dl] == _data16get(0x2AC4) ) // jz 
      { wPos = 0x2BB3; continue; }
    _data[0x2AC4] = r8[dl];
    r16[dx] += 0x2904;
    si = r16[dx];
    r16[cx] = 0x801;
    sub_2D9D();
    wPos = 0x2BA4;
      continue;
  case 0x2BD2:
    di = 0x1180;
    r16[ax] = 0x5655;
    r16[cx] = 0x500;
    _cld();
    _rep_stosw();
    di = 0x3180;
    r16[cx] = 0x500;
    _rep_stosw();
    _data16set(0x2AC2, 0x2944);
  case 0x2BEC:
    _data[0x2AC4] = 9;
  case 0x2BF1:
    sub_2DFD();
    r16[dx] &= 0x776;
    r16[dx] += 0x12C0;
    di = r16[dx];
    si = _data16get(0x2AC2);
    r16[cx] = 0x501;
    sub_2D9D();
    _data[0x2AC4]--;
    if ( _data[0x2AC4] ) // jnz 
      { wPos = 0x2BF1; continue; }
    _data16set(0x2AC2, _data16get(0x2AC2) + 0x0A);
    if ( _data16get(0x2AC2) < 0x296C ) // jb 
      { wPos = 0x2BEC; continue; }
    _data[0x2AC4] = 5;
  case 0x2C20:
    sub_2DFD();
    r16[dx] &= 0x3E;
    r16[dx] += 0x3A98;
    di = r16[dx];
    si = 0x296C;
    r16[cx] = 0x501;
    sub_2D9D();
    _data[0x2AC4]--;
    if ( _data[0x2AC4] ) // jnz 
      { wPos = 0x2C20; continue; }
    wPos = -1;
  }
}
function sub_2C3D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x2AC2, di);
    r8[al] = 3;
    if ( di < 0x1720 ) // jb 
      { wPos = 0x2C4B; continue; }
    r8[al]--;
  case 0x2C4B:
    _data[0x2AC4] = r8[al];
    _data16set(0x2AC2, _data16get(0x2AC2) + 0x1E0);
    si = 0x2976;
    r16[cx] = 0x0C05;
    sub_2D9D();
  case 0x2C5D:
    di = _data16get(0x2AC2);
    _data16set(0x2AC2, _data16get(0x2AC2) + 0x140);
    si = 0x29EE;
    r16[cx] = 0x804;
    sub_2D9D();
    _data[0x2AC4]--;
    if ( _data[0x2AC4] ) // jnz 
      { wPos = 0x2C5D; continue; }
    di = _data16get(0x2AC2);
    si = 0x2A2E;
    r16[cx] = 0x0B04;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_2C84()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[bx] = _data16get(8);
    r8[bl] = _data[r16[bx] + 0x2AB2];
  case 0x2C8C:
    _data16set(0x2AC5, r16[bx]);
    di = _data16get(r16[bx] + 0x2A86);
    if ( di != 0 ) // jnz 
      { wPos = 0x2C9A; continue; }
    return;
  case 0x2C9A:
    sub_2C3D();
    r16[bx] = _data16get(0x2AC5);
    r16[bx] += 2;
    wPos = 0x2C8C;
      continue;
    wPos = -1;
  }
}
function sub_2CB0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = r8[dl];
    r8[ah] = 0x28;
    r16[ax] = r8[ah] * r8[al];
    if ( !(r8[dl] & 1) ) // jz 
      { wPos = 0x2CBE; continue; }
    r16[ax] += 0x1FD8;
  case 0x2CBE:
    r16[dx] = r16[cx];
    r16[dx] >>= 1;
    r16[dx] >>= 1;
    r16[ax] += r16[dx];
    r8[cl] &= 3;
    r8[cl] <<= 1;
    wPos = -1;
  }
}
function sub_2CCC()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data[0x2AE0] = r8[cl];
    _data[0x2AE2] = r8[ch];
    r8[ch] = 0;
    r16[dx] = 0x0FF0;
  case 0x2CDA:
    r8[cl] = _data[0x2AE0];
  case 0x2CDE:
    r16[dx] = 0x30C0;
    r16[bx] = _video16get(0*es*16+di);
    _data16set(bp+0, r16[bx]);
    _lodsw();
    _data16set(0x2AE3, r16[ax]);
  case 0x2CEC:
    if ( r8[ah] & r8[dl] ) // jnz 
      { wPos = 0x2CF2; continue; }
    r8[ah] |= r8[dl];
  case 0x2CF2:
    if ( r8[ah] & r8[dh] ) // jnz 
      { wPos = 0x2CF8; continue; }
    r8[ah] |= r8[dh];
  case 0x2CF8:
    if ( r8[al] & r8[dl] ) // jnz 
      { wPos = 0x2CFE; continue; }
    r8[al] |= r8[dl];
  case 0x2CFE:
    if ( r8[al] & r8[dh] ) // jnz 
      { wPos = 0x2D04; continue; }
    r8[al] |= r8[dh];
  case 0x2D04:
    r16[dx] = r16[dx] ^ 0x33CC;
    if ( r8[dh] & 3 ) // jnz 
      { wPos = 0x2CEC; continue; }
    r16[ax] &= r16[bx];
    r16[ax] |= _data16get(0x2AE3);
    _stosw();
    bp += 2;
    if ( --r16[cx] )
      { wPos = 0x2CDE; continue; }
    di -= _data16get(0x2AE0);
    di -= _data16get(0x2AE0);
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x2D2E; continue; }
    di += 0x50;
  case 0x2D2E:
    _data[0x2AE2]--;
    if ( _data[0x2AE2] ) // jnz 
      { wPos = 0x2CDA; continue; }
    wPos = -1;
  }
}
function sub_2D35()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data[0x2AE0] = r8[cl];
    _data[0x2AE2] = r8[ch];
    r8[ch] = 0;
  case 0x2D40:
    r8[cl] = _data[0x2AE0];
  case 0x2D44:
    r16[bx] = _video16get(0*es*16+di);
    _data16set(bp+0, r16[bx]);
    _lodsw();
    r16[ax] &= r16[bx];
    _stosw();
    bp += 2;
    if ( --r16[cx] )
      { wPos = 0x2D44; continue; }
    di -= _data16get(0x2AE0);
    di -= _data16get(0x2AE0);
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x2D69; continue; }
    di += 0x50;
  case 0x2D69:
    _data[0x2AE2]--;
    if ( _data[0x2AE2] ) // jnz 
      { wPos = 0x2D40; continue; }
    wPos = -1;
  }
}
function sub_2D70()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data16set(0x2AE9, si);
    _data[0x2AE0] = r8[cl];
    _data[0x2AE2] = r8[ch];
    r8[al] <<= 1;
    _data[0x2AEB] = r8[al];
    r8[ch] = 0;
  case 0x2D84:
    r8[cl] = _data[0x2AE0];
    _rep_movsw();
    r8[cl] = _data[0x2AEB];
    _data16set(0x2AE9, _data16get(0x2AE9) + r16[cx]);
    si = _data16get(0x2AE9);
    _data[0x2AE2]--;
    if ( _data[0x2AE2] ) // jnz 
      { wPos = 0x2D84; continue; }
    wPos = -1;
  }
}
function sub_2D9D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data[0x2AE0] = r8[cl];
    _data[0x2AE2] = r8[ch];
    r8[ch] = 0;
  case 0x2DA8:
    r8[cl] = _data[0x2AE0];
    _rep_movsw();
    di -= _data16get(0x2AE0);
    di -= _data16get(0x2AE0);
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x2DC3; continue; }
    di += 0x50;
  case 0x2DC3:
    _data[0x2AE2]--;
    if ( _data[0x2AE2] ) // jnz 
      { wPos = 0x2DA8; continue; }
    wPos = -1;
  }
}
function sub_2DCA()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data[es*16+0x2AE0] = r8[cl];
    _data[es*16+0x2AE2] = r8[ch];
    r8[ch] = 0;
  case 0x2DD7:
    r8[cl] = _data[es*16+0x2AE0];
    _rep_movsw();
    si -= _data16get(es*16+0x2AE0);
    si -= _data16get(es*16+0x2AE0);
    si = si ^ 0x2000;
    if ( si & 0x2000 ) // jnz 
      { wPos = 0x2DF5; continue; }
    si += 0x50;
  case 0x2DF5:
    _data[es*16+0x2AE2]--;
    if ( _data[es*16+0x2AE2] ) // jnz 
      { wPos = 0x2DD7; continue; }
    wPos = -1;
  }
}
function sub_2DFD()
{
  r16[dx] = _data16get(0x2AE5);
  r8[dl] = r8[dl] ^ r8[dh];
  r8[dl] >>= 1;
  cf = r8[dl] & 1 ? 1 : 0;
  r8[dl] >>= 1;
  _data16set(0x2AE5, _rcr16(_data16get(0x2AE5), 1));
  r16[dx] = _data16get(0x2AE5);
}
function sub_2E10()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = 0;
    _out(0x43, r8[al]);
    r8[al] =_in(0x40);
    r8[ah] = r8[al];
    r8[al] =_in(0x40);
    if ( r16[ax] != 0 ) // jnz 
      { wPos = 0x2E25; continue; }
    r16[ax] = 0x0FA59;
  case 0x2E25:
    _data16set(0x2AE5, r16[ax]);
    wPos = -1;
  }
}
function sub_2E29()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] += si;
    if ( r16[ax] < r16[bx] ) // jb 
      { wPos = 0x2E4F; continue; }
    r16[ax] -= si;
    cf = (r16[ax] < di); // cf-insertion
    r16[ax] -= di;
    if ( !cf ) // jnb 
      { wPos = 0x2E37; continue; }
    r16[ax] = 0;
  case 0x2E37:
    if ( r16[ax] > r16[bx] ) // ja 
      { wPos = 0x2E4F; continue; }
    r8[dl] += r8[cl];
    if ( r8[dl] < r8[dh] ) // jb 
      { wPos = 0x2E4F; continue; }
    r8[dl] -= r8[cl];
    cf = (r8[dl] < r8[ch]); // cf-insertion
    r8[dl] -= r8[ch];
    if ( !cf ) // jnb 
      { wPos = 0x2E49; continue; }
    r8[dl] = 0;
  case 0x2E49:
    if ( r8[dl] > r8[dh] ) // ja 
      { wPos = 0x2E4F; continue; }
    _stc();
    return;
  case 0x2E4F:
    _clc();
    wPos = -1;
  }
}
function sub_2E60()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(0x2E8D) < 8 ) // jb 
      { wPos = 0x2E68; continue; }
    return;
  case 0x2E68:
    if ( _data[0x69A] != 0 ) // jnz 
      return;
    _data16set(0x2E92, 0x0FFFF);
    _data[0x2E91] = 0x0FF;
    r16[cx] = 7;
  case 0x2E7D:
    r16[bx] = r16[cx];
    r16[bx]--;
    r8[al] = _data[0x57B];
    cf = (r8[al] < _data16get(r16[bx] + 0x2BD4)); // cf-insertion
    r8[al] -= _data16get(r16[bx] + 0x2BD4);
    if ( !cf ) // jnb 
      { wPos = 0x2E8B; continue; }
    r8[al] = ~ r8[al];
  case 0x2E8B:
    if ( r8[al] > _data16get(0x2E91) ) // ja 
      { wPos = 0x2E98; continue; }
    _data[0x2E91] = r8[al];
    _data16set(0x2E92, r16[bx]);
  case 0x2E98:
    if ( --r16[cx] )
      { wPos = 0x2E7D; continue; }
    if ( _data16get(0x2E92) != 0x0FFFF ) // jnz 
      { wPos = 0x2EA8; continue; }
    _data16set(0x2E92, 0);
  case 0x2EA8:
    r16[bx] = _data16get(0x2E8D);
    si = _data16get(0x2E92);
    r8[al] = _data[si + 0x2BD4];
    _data[r16[bx] + 0x2B6A] = r8[al];
    _data[0x2E98] = r8[al];
    r16[ax] = _data16get(0x579);
    r8[bl] <<= 1;
    if ( r16[ax] < 0x108 ) // jb 
      { wPos = 0x2EC8; continue; }
    r16[ax] = 0x107;
  case 0x2EC8:
    r16[ax] &= 0x0FFC;
    _data16set(r16[bx] + 0x2B5A, r16[ax]);
    _data16set(0x2E96, r16[ax]);
    r16[cx] = 8;
  case 0x2ED5:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( r16[bx] == _data16get(0x2E8D) ) // jz 
      { wPos = 0x2F07; continue; }
    if ( _data[r16[bx] + 0x2B72] == 0 ) // jz 
      { wPos = 0x2F07; continue; }
    _push(r16[cx]);
    r8[dl] = _data[r16[bx] + 0x2B6A];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x2B5A);
    r16[bx] = _data16get(0x2E96);
    r8[dh] = _data[0x2E98];
    si = 0x18;
    di = si;
    r16[cx] = 0x0F0F;
    sub_2E29();
    r16[cx] = _pop();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x2F07; continue; }
    return;
  case 0x2F07:
    if ( --r16[cx] )
      { wPos = 0x2ED5; continue; }
    sub_11E3();
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x2F16; continue; }
    sub_622B();
  case 0x2F16:
    r16[bx] = _data16get(0x2E8D);
    _data16set(0x2E94, r16[bx]);
    _data[r16[bx] + 0x2B72] = 1;
    r8[dl] = _data[r16[bx] + 0x2B6A];
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x2B5A);
    sub_2CB0();
    di = r16[ax];
    si = 0x2AF0;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x0F03;
    sub_2D9D();
    _data16set(0x2E8D, 0x0FFFF);
    r16[bx] = 0;
    r8[ah] = 0x0B;
    _int(0x10);
    sub_4E3E();
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x2F59; continue; }
    sub_61FA();
  case 0x2F59:
    sub_1145();
    r16[ax] = 0x3E8;
    r16[bx] = 0x4A5;
    sub_593B();
    wPos = -1;
  }
}
function sub_2F66()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x2E8F) ) // jnz 
      { wPos = 0x2F71; continue; }
    return;
  case 0x2F71:
    _data16set(0x2E8F, r16[dx]);
    if ( _data16get(0x2E8D) < 8 ) // jb 
      { wPos = 0x2FAC; continue; }
    r16[cx] = 8;
  case 0x2F7F:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( _data[r16[bx] + 0x2B72] == 0 ) // jz 
      { wPos = 0x2FAA; continue; }
    _push(r16[cx]);
    r8[dl] = _data[r16[bx] + 0x2B6A];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x2B5A);
    si = 0x18;
    di = si;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    r16[cx] = 0x0E0F;
    sub_2E29();
    r16[cx] = _pop();
    if ( cf ) // jb cf=1
      { wPos = 0x2FB3; continue; }
  case 0x2FAA:
    if ( --r16[cx] )
      { wPos = 0x2F7F; continue; }
  case 0x2FAC:
    _data16set(0x2E94, 0x0FFFF);
    return;
  case 0x2FB3:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( r16[bx] == _data16get(0x2E94) ) // jz 
      return;
    _push(r16[bx]);
    sub_11E3();
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x2FCA; continue; }
    sub_622B();
  case 0x2FCA:
    r16[bx] = _pop();
    _data[r16[bx] + 0x2B72] = 0;
    r8[dl] = _data[r16[bx] + 0x2B6A];
    _data16set(0x2E8D, r16[bx]);
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x2B5A);
    sub_2CB0();
    di = r16[ax];
    si = 0x2B7A;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x0F03;
    sub_2D9D();
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x2FFB; continue; }
    sub_61FA();
  case 0x2FFB:
    sub_1145();
    r16[bx] = 1;
    r8[ah] = 0x0B;
    _int(0x10);
    r16[ax] = 0x3E8;
    r16[bx] = 0x349;
    sub_593B();
    wPos = -1;
  }
}
function sub_300F()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0;
    r16[bx] = 0x2E24;
    sub_2B24();
    _data[0x2E8A] = 0x0BF;
    _data16set(0x2E8B, 0);
  case 0x3022:
    _data16set(0x2E88, 0x20);
  case 0x3028:
    r16[bx] = 0;
    if ( _data[0x2E8A] == 0x0BF ) // jz 
      { wPos = 0x3039; continue; }
    sub_2DFD();
    r8[bl] = r8[dl];
    r8[bl] &= 2;
  case 0x3039:
    r16[cx] = _data16get(0x2E88);
    r8[dl] = _data[0x2E8A];
    _push(r16[bx]);
    sub_30E3();
    r16[bx] = _pop();
    si = _data16get(0x2E8B);
    r16[ax] = _data16get(0x2E88);
    r8[cl] = 4;
    r16[ax] >>= r8[cl];
    cf = (r16[ax] < 2); // cf-insertion
    r16[ax] -= 2;
    if ( !cf ) // jnb 
      { wPos = 0x3058; continue; }
    r16[ax] = 0;
  case 0x3058:
    if ( r16[ax] < 0x12 ) // jb 
      { wPos = 0x3060; continue; }
    r16[ax] = 0x11;
  case 0x3060:
    r8[dl] = _data[si + 0x2BDB];
    r8[dh] = 0;
    r16[ax] += r16[dx];
    si = r16[ax];
    _data[si + 0x2BE2] = r8[bl];
    _data16set(0x2E88, _data16get(0x2E88) + 0x10);
    if ( _data16get(0x2E88) < 0x111 ) // jb 
      { wPos = 0x3028; continue; }
    _data16set(0x2E8B, _data16get(0x2E8B) + 1);
    _data[0x2E8A] -= 0x18;
    if ( _data[0x2E8A] >= 0x2F ) // jnb 
      { wPos = 0x3022; continue; }
    r16[ax] = 0x0FFFF;
    _data16set(0x2E8D, r16[ax]);
    _data16set(0x2E94, r16[ax]);
    r16[ax] = 0;
    _data16set(0x2B72, r16[ax]);
    _data16set(0x2B74, r16[ax]);
    _data16set(0x2B76, r16[ax]);
    _data16set(0x2B78, r16[ax]);
    r16[cx] = _data16get(0x414);
    if ( r16[cx] != 0 ) // jnz 
      { wPos = 0x30B0; continue; }
    r16[cx] = r16[cx] + 1;
    _data16set(0x414, r16[cx]);
  case 0x30B0:
    if ( r16[cx] <= 8 ) // jbe 
      { wPos = 0x30B8; continue; }
    r16[cx] = 8;
  case 0x30B8:
    r16[bx] = r16[cx];
    r16[bx]--;
    _data[r16[bx] + 0x2B72] = 1;
    r8[dl] = 0x0B0;
    _data[r16[bx] + 0x2B6A] = r8[dl];
    _push(r16[cx]);
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x2B4A);
    _data16set(r16[bx] + 0x2B5A, r16[cx]);
    sub_2CB0();
    di = r16[ax];
    si = 0x2AF0;
    r16[cx] = 0x0F03;
    sub_2D9D();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x30B8; continue; }
    wPos = -1;
  }
}
function sub_30E3()
{
  _push(r16[bx]);
  sub_2CB0();
  di = r16[ax];
  r16[ax] = 0x0B800;
  es = r16[ax];
  r16[bx] = _pop();
  si = _data16get(r16[bx] + 0x2E20);
  r16[cx] = 0x802;
  sub_2D9D();
}
function sub_30FA()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x57B];
    r8[al] -= 5;
    r8[al] &= 0x0F8;
    r16[cx] = 7;
  case 0x3104:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( r8[al] == _data16get(r16[bx] + 0x2BD4) ) // jz 
      { wPos = 0x3111; continue; }
    if ( --r16[cx] )
      { wPos = 0x3104; continue; }
    wPos = 0x314D;
      continue;
  case 0x3111:
    r8[ch] = r8[al];
    r16[ax] = _data16get(0x579);
    r16[ax] += 7;
    r8[cl] = 4;
    r16[ax] >>= r8[cl];
    cf = (r16[ax] < 2); // cf-insertion
    r16[ax] -= 2;
    if ( !cf ) // jnb 
      { wPos = 0x3124; continue; }
    r16[ax] = 0;
  case 0x3124:
    if ( r16[ax] < 0x12 ) // jb 
      { wPos = 0x312C; continue; }
    r16[ax] = 0x11;
  case 0x312C:
    r8[dl] = _data[r16[bx] + 0x2BDB];
    r8[dh] = 0;
    r16[ax] += r16[dx];
    si = r16[ax];
    if ( _data[si + 0x2BE2] != 0 ) // jnz 
      { wPos = 0x314D; continue; }
    r8[ch] += 5;
    _data[0x57B] = r8[ch];
    r8[ch] += 0x32;
    _data[0x57C] = r8[ch];
    _stc();
    return;
  case 0x314D:
    _clc();
    wPos = -1;
  }
}
function sub_3150()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[bx] = _data16get(4);
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x32F2);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x328C);
    if ( r16[ax] >= r16[cx] ) // jnb 
      { wPos = 0x3169; continue; }
    return;
  case 0x3169:
    _data16set(0x328C, r16[dx]);
    sub_33BA();
    if ( unknown_condition() ) // jb cf=1
      return;
    sub_21E0();
    if ( unknown_condition() ) // jb cf=1
      return;
    _data[0x32EA] = _data[0x32EA] + 1;
    sub_2DFD();
    r8[al] = _data[0x32EA];
    r8[al] &= r8[dl];
    _data16set(0x32EB, _data16get(0x32EB) ^ r8[al]);
    r16[ax] = _data16get(0x327D);
    r16[ax] -= _data16get(0x579);
    r8[dl] = 0x0FF;
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3196; continue; }
    r16[ax] = ~ r16[ax];
    r8[dl] = 1;
  case 0x3196:
    _data[0x32ED] = r8[dl];
    r8[bl] = _data[0x327F];
    r8[bl] += 0x14;
    r8[bl] -= _data16get(0x57B);
    r8[dl] = 0x0FF;
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x31AD; continue; }
    r8[bl] = ~ r8[bl];
    r8[dl] = 1;
  case 0x31AD:
    _data[0x32EE] = r8[dl];
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r8[bl] >>= 1;
    r8[al] += r8[bl];
    _data[0x32EC] = r8[al];
    r16[bx] = _data16get(0x328A);
    if ( r16[bx] < 0x27 ) // jb 
      { wPos = 0x31CC; continue; }
    r16[bx] = 0x26;
    _data16set(0x328A, r16[bx]);
  case 0x31CC:
    if ( _data[r16[bx] + 0x328E] != 0 ) // jnz 
      { wPos = 0x324B; continue; }
    _data16set(0x328A, _data16get(0x328A) -1);
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x410);
    r8[cl] = 3;
    r16[dx] >>= r8[cl];
    r8[al] = _data[0x32EC];
    cf = (r8[al] < r8[dl]); // cf-insertion
    r8[al] -= r8[dl];
    if ( !cf ) // jnb 
      { wPos = 0x31EC; continue; }
    r8[al] = 0;
  case 0x31EC:
    if ( r8[al] < _data16get(0x32EB) ) // jb 
      { wPos = 0x3212; continue; }
    _data[0x3281] = 1;
    sub_2DFD();
    if ( r8[dl] == 0 ) // jz 
      { wPos = 0x320B; continue; }
    if ( r8[dl] > 7 ) // ja 
      { wPos = 0x320F; continue; }
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x320B; continue; }
    r8[dl] = 0x0FF;
  case 0x320B:
    _data[0x3280] = r8[dl];
  case 0x320F:
    wPos = 0x32AC;
      continue;
  case 0x3212:
    r8[al] = _data[0x32EB];
    r8[al] &= 0x2F;
    if ( r8[al] ) // jnz 
      { wPos = 0x3238; continue; }
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x3223; continue; }
    r8[dl] = 0x0FF;
  case 0x3223:
    _data[0x3280] = r8[dl];
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x3231; continue; }
    r8[dl] = 0x0FF;
  case 0x3231:
    _data[0x3281] = r8[dl];
    wPos = 0x32AC;
      continue;
  case 0x3238:
    r8[al] &= 7;
    if ( r8[al] ) // jnz 
      { wPos = 0x32AC; continue; }
    r8[al] = _data[0x32ED];
    _data[0x3280] = r8[al];
    r8[al] = _data[0x32EE];
    _data[0x3281] = r8[al];
    wPos = 0x32AC;
      continue;
  case 0x324B:
    _data[0x3281] = 1;
    r16[ax] = r16[bx];
    r8[cl] = 3;
    r16[ax] <<= r8[cl];
    if ( _data16get(0x327D) == r16[ax] ) // jz 
      { wPos = 0x3269; continue; }
    r8[dl] = 1;
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x3262; continue; }
    r8[dl] = 0x0FF;
  case 0x3262:
    _data[0x3280] = r8[dl];
    wPos = 0x32AC;
      continue;
  case 0x3269:
    _data[0x3280] = 0;
    if ( _data[0x327F] != 0x0A5 ) // jnz 
      { wPos = 0x32AC; continue; }
    _data[0x3281] = 0;
    if ( _data16get(0x327A) == 6 ) // jz 
      { wPos = 0x3288; continue; }
    if ( _data16get(0x327A) != 0x12 ) // jnz 
      { wPos = 0x32AC; continue; }
  case 0x3288:
    _push(r16[bx]);
    si = 0x31E8;
    di = _data16get(0x3282);
    r16[cx] = 0x1E02;
    r16[ax] = 0x0B800;
    es = r16[ax];
    sub_2D9D();
    r16[bx] = _pop();
    _data[r16[bx] + 0x328E]--;
    r8[al] = _data[r16[bx] + 0x328E];
    sub_347F();
    _data[0x3286] = 1;
  case 0x32AC:
    r16[cx] = _data16get(0x327D);
    r8[dl] = _data[0x327F];
    _data16set(0x32EF, r16[cx]);
    _data[0x32F1] = r8[dl];
    if ( _data[0x3280] < 1 ) // jb 
      { wPos = 0x32DA; continue; }
    if ( _data[0x3280] != 1 ) // jnz 
      { wPos = 0x32D3; continue; }
    r16[cx] += 8;
    if ( r16[cx] < 0x131 ) // jb 
      { wPos = 0x32DA; continue; }
    r16[cx] = 0x130;
    wPos = 0x32DA;
      continue;
  case 0x32D3:
    cf = (r16[cx] < 8); // cf-insertion
    r16[cx] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x32DA; continue; }
    r16[cx] = 0;
  case 0x32DA:
    r16[cx] &= 0x0FFF8;
    _data16set(0x327D, r16[cx]);
    if ( _data[0x3281] < 1 ) // jb 
      { wPos = 0x32FE; continue; }
    if ( _data[0x3281] != 1 ) // jnz 
      { wPos = 0x32F7; continue; }
    r8[dl] += 2;
    if ( r8[dl] < 0x0A6 ) // jb 
      { wPos = 0x32FE; continue; }
    r8[dl] = 0x0A5;
    wPos = 0x32FE;
      continue;
  case 0x32F7:
    cf = (r8[dl] < 2); // cf-insertion
    r8[dl] -= 2;
    if ( !cf ) // jnb 
      { wPos = 0x32FE; continue; }
    r8[dl] = 0;
  case 0x32FE:
    _data[0x327F] = r8[dl];
    sub_2CB0();
    _data16set(0x3284, r16[ax]);
    sub_33BA();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3328; continue; }
  case 0x330D:
    _data[0x3280] = 0;
    _data[0x3281] = 0;
    r16[cx] = _data16get(0x32EF);
    _data16set(0x327D, r16[cx]);
    r8[dl] = _data[0x32F1];
    _data[0x327F] = r8[dl];
    return;
  case 0x3328:
    sub_21E0();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x330D; continue; }
    sub_33A0();
    _data16set(0x327A, _data16get(0x327A) + 2);
    sub_3339();
    wPos = -1;
  }
}
function sub_3339()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
  case 0x3339:
    r16[bx] = _data16get(0x327A);
    r16[ax] = _data16get(r16[bx] + 0x3260);
    if ( r16[ax] != 0 ) // jnz 
      { wPos = 0x334B; continue; }
    _data16set(0x327A, r16[ax]);
    wPos = 0x3339;
      continue;
  case 0x334B:
    si = r16[ax];
    di = _data16get(0x3284);
    _data16set(0x3282, di);
    bp = 0x31E8;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x1E02;
    _data[0x3286] = 0;
    _cld();
    _data[0x3289] = r8[ch];
    r8[ch] = 0;
    _data16set(0x3287, r16[cx]);
  case 0x3370:
    r16[cx] = _data16get(0x3287);
  case 0x3374:
    r16[bx] = _video16get(es*16+di);
    _data16set(bp+0, r16[bx]);
    _lodsw();
    r16[ax] |= r16[bx];
    _stosw();
    bp += 2;
    if ( --r16[cx] )
      { wPos = 0x3374; continue; }
    di -= _data16get(0x3287);
    di -= _data16get(0x3287);
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x3399; continue; }
    di += 0x50;
  case 0x3399:
    _data[0x3289]--;
    if ( _data[0x3289] ) // jnz 
      { wPos = 0x3370; continue; }
    wPos = -1;
  }
}
function sub_33A0()
{
  if ( _data[0x3286] != 0 ) // jnz 
    return;
  r16[ax] = 0x0B800;
  es = r16[ax];
  si = 0x31E8;
  di = _data16get(0x3282);
  r16[cx] = 0x1E02;
  sub_2D9D();
}
function sub_33BA()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1CB8] != 0 ) // jnz 
      { wPos = 0x3403; continue; }
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x33D3; continue; }
    if ( _data[0x44BD] == 0 ) // jz 
      { wPos = 0x33D3; continue; }
    sub_47B0();
    return;
  case 0x33D3:
    r16[ax] = _data16get(0x327D);
    r8[dl] = _data[0x327F];
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E1E;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      { wPos = 0x3403; continue; }
    if ( _data16get(4) != 4 ) // jnz 
      { wPos = 0x33FE; continue; }
    if ( _data[0x39E1] != 0 ) // jnz 
      { wPos = 0x3401; continue; }
  case 0x33FE:
    sub_872();
  case 0x3401:
    _stc();
    return;
  case 0x3403:
    _clc();
    wPos = -1;
  }
}
function sub_3405()
{
  _cld();
  r16[ax] = 0;
  _push(ds);
  es = _pop();
  di = 0x328E;
  r16[cx] = 0x14;
  _rep_stosw();
  _data16set(0x32B6, 0x0FF);
  _data16set(0x327A, 0);
  _data16set(0x327D, 0);
  _data[0x327F] = 0x0A0;
  _data[0x3286] = 1;
  _data[0x3280] = 0;
  _data[0x3281] = 0;
  sub_2DFD();
  _data[0x32EB] = r8[dl];
  _data[0x32EA] = 0x6C;
}
function sub_3445()
{
  if ( _data[0x57B] < 0x0B4 ) // jb 
    return;
  if ( _data[0x56E] == 0 ) // jz 
    return;
  r16[ax] = _data16get(0x579);
  r16[ax] += 0x0C;
  r8[cl] = 3;
  r16[ax] >>= r8[cl];
  if ( r16[ax] > 0x27 ) // ja 
    return;
  if ( r16[ax] == _data16get(0x32B6) ) // jz 
    return;
  _data16set(0x32B6, r16[ax]);
  r16[bx] = r16[ax];
  r8[al] = _data[r16[bx] + 0x328E];
  if ( r8[al] >= 4 ) // jnb 
    return;
  r8[al] = r8[al] + 1;
  _data[r16[bx] + 0x328E] = r8[al];
  sub_347F();
}
function sub_347F()
{
  r8[ah] = 0x0A;
  r16[ax] = r8[ah] * r8[al];
  r16[ax] += 0x32B8;
  si = r16[ax];
  di = r16[bx];
  di <<= 1;
  di += 0x1E00;
  r16[ax] = 0x0B800;
  es = r16[ax];
  r16[cx] = 0x501;
  sub_2D9D();
}
function sub_34A0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x3511, 0);
    _data[0x351B] = 0;
  case 0x34AB:
    r16[bx] = _data16get(0x3511);
    if ( _data[r16[bx] + 0x34A7] == 0 ) // jz 
      { wPos = 0x34B9; continue; }
  case 0x34B6:
    wPos = 0x35AD;
      continue;
  case 0x34B9:
    si = r16[bx];
    si <<= 1;
    r16[ax] = _data16get(si + 0x3447);
    r8[dl] = _data[r16[bx] + 0x3477];
    di = 0;
    if ( r16[bx] < 0x0C ) // jb 
      { wPos = 0x34D0; continue; }
    di = 2;
  case 0x34D0:
    si = _data16get(di + 0x3513);
    r16[cx] = _data16get(di + 0x3517);
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r8[ch] = 0x0E;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      { wPos = 0x34B6; continue; }
    r16[bx] = _data16get(0x3511);
    if ( r16[bx] < 0x0C ) // jb 
      { wPos = 0x356F; continue; }
    if ( _data[0x553] != 0 ) // jnz 
      { wPos = 0x356F; continue; }
    if ( _data[0x5F3] != 0 ) // jnz 
      { wPos = 0x356F; continue; }
    _data[0x552] = 1;
    r16[cx] = _data16get(0x579);
    cf = (r16[cx] < 8); // cf-insertion
    r16[cx] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x3511; continue; }
    r16[cx] = 0;
  case 0x3511:
    if ( r16[cx] < 0x117 ) // jb 
      { wPos = 0x351A; continue; }
    r16[cx] = 0x116;
  case 0x351A:
    r8[dl] = _data[0x57B];
    if ( r8[dl] < 0x0B5 ) // jb 
      { wPos = 0x3525; continue; }
    r8[dl] = 0x0B4;
  case 0x3525:
    sub_2CB0();
    di = r16[ax];
    si = 0x3350;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x1205;
    sub_2D9D();
    sub_5797();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x3509, r16[dx]);
  case 0x3543:
    _push(r16[dx]);
    sub_57A6();
    sub_57A6();
    r16[dx] = _pop();
    r16[bx] = 1;
    if ( r8[dl] & 1 ) // jnz 
      { wPos = 0x355A; continue; }
    r8[bl] = 0x0F;
  case 0x355A:
    r8[ah] = 0x0B;
    _int(0x10);
    sub_57A6();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x3509);
    if ( r16[dx] < 0x0D ) // jb 
      { wPos = 0x3543; continue; }
    return;
  case 0x356F:
    _data[0x351B] = _data[0x351B] + 1;
    r16[ax] = 0x5DC;
    r16[bx] = 0x425;
    sub_593B();
    if ( _data[0x351B] != 1 ) // jnz 
      { wPos = 0x3586; continue; }
    sub_11E3();
  case 0x3586:
    r16[bx] = _data16get(0x3511);
    sub_37C1();
    r16[bx] = _data16get(0x3511);
    _data[r16[bx] + 0x34A7] = 1;
    if ( r16[bx] >= 0x0C ) // jnb 
      { wPos = 0x35AD; continue; }
    _data[0x3410]--;
    if ( _data[0x3410] ) // jnz 
      { wPos = 0x35AD; continue; }
    if ( _data[0x5F3] != 0 ) // jnz 
      { wPos = 0x35AD; continue; }
    _data[0x553] = 1;
  case 0x35AD:
    _data16set(0x3511, _data16get(0x3511) + 1);
    if ( _data16get(0x3511) >= 0x18 ) // jnb 
      { wPos = 0x35BB; continue; }
    wPos = 0x34AB;
      continue;
  case 0x35BB:
    if ( _data[0x351B] == 0 ) // jz 
      { wPos = 0x35C7; continue; }
    sub_363D();
    _stc();
    return;
  case 0x35C7:
    _clc();
    wPos = -1;
  }
}
function sub_35C9()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x3411, 0);
    _data16set(0x3415, 0);
    _data[0x3410] = 0x0C;
    r16[cx] = 0x18;
  case 0x35DD:
    r16[bx] = r16[cx];
    r16[bx]--;
    _data[r16[bx] + 0x348F] = 1;
    _data[r16[bx] + 0x34A7] = 0;
    r8[al] = _data[r16[bx] + 0x34F1];
    _data[r16[bx] + 0x3477] = r8[al];
    _data[r16[bx] + 0x342F] = 1;
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x3601; continue; }
    r8[dl] = ~ r8[dl];
  case 0x3601:
    _data[r16[bx] + 0x3417] = r8[dl];
    r16[bx] <<= 1;
    sub_2DFD();
    r8[dh] = 0;
    _data16set(r16[bx] + 0x3447, r16[dx]);
    if ( --r16[cx] )
      { wPos = 0x35DD; continue; }
    r16[bx] = _data16get(8);
    r8[cl] = _data[r16[bx] + 0x351C];
    r8[ch] = 0;
  case 0x361C:
    sub_2DFD();
    r8[dl] &= 0x0F;
    if ( r8[dl] >= 0x0C ) // jnb 
      { wPos = 0x361C; continue; }
    r8[bl] = r8[dl];
    r8[bl] += 0x0C;
    r8[bh] = 0;
    if ( _data[r16[bx] + 0x34A7] != 0 ) // jnz 
      { wPos = 0x361C; continue; }
    _data[r16[bx] + 0x34A7] = 1;
    if ( --r16[cx] )
      { wPos = 0x361C; continue; }
    wPos = -1;
  }
}
function sub_363D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
  case 0x363D:
    r16[cx] = 0x0C;
  case 0x3640:
    r16[bx] = r16[cx];
    r16[bx] += 0x0B;
    if ( _data[r16[bx] + 0x34A7] == 0 ) // jz 
      { wPos = 0x3672; continue; }
    r16[ax] = 0;
    r8[dl] = 1;
    _data[r16[bx] + 0x34A7] = r8[al];
    if ( _data16get(0x579) > 0x0A0 ) // ja 
      { wPos = 0x3661; continue; }
    r16[ax] = 0x12E;
    r8[dl] = 0x0FF;
  case 0x3661:
    _data[r16[bx] + 0x3417] = r8[dl];
    r8[bl] <<= 1;
    _data16set(r16[bx] + 0x3447, r16[ax]);
    _data[0x351B]--;
    if ( _data[0x351B] ) // jnz 
      { wPos = 0x363D; continue; }
    return;
  case 0x3672:
    if ( --r16[cx] )
      { wPos = 0x3640; continue; }
    wPos = -1;
  }
}
function sub_3675()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x3509) ) // jnz 
      { wPos = 0x3680; continue; }
    return;
  case 0x3680:
    _data16set(0x350B, r16[dx]);
    _data16set(0x3415, _data16get(0x3415) + 1);
    r16[bx] = _data16get(0x3415);
    if ( r16[bx] < 0x18 ) // jb 
      { wPos = 0x36A4; continue; }
    r16[bx] = 0;
    _data16set(0x3415, r16[bx]);
    _data16set(0x3411, _data16get(0x3411) ^ 0x0C);
    _data16set(0x3413, _data16get(0x3413) + 8);
    wPos = 0x36B7;
      continue;
  case 0x36A4:
    if ( r16[bx] != 0x0C ) // jnz 
      { wPos = 0x36BD; continue; }
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x36B7; continue; }
    if ( _data[0x57B] < 0x30 ) // jb 
      { wPos = 0x36BD; continue; }
  case 0x36B7:
    r16[ax] = _data16get(0x350B);
    _data16set(0x3509, r16[ax]);
  case 0x36BD:
    si = r16[bx];
    si <<= 1;
    if ( _data[r16[bx] + 0x34A7] != 0 ) // jnz 
      return;
    sub_2DFD();
    if ( r8[dl] > 0x10 ) // ja 
      { wPos = 0x36E9; continue; }
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x36D7; continue; }
    r8[dl] = ~ r8[dl];
  case 0x36D7:
    _data[r16[bx] + 0x3417] = r8[dl];
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x36E5; continue; }
    r8[dl] = ~ r8[dl];
  case 0x36E5:
    _data[r16[bx] + 0x342F] = r8[dl];
  case 0x36E9:
    r16[cx] = 4;
    if ( r16[bx] < 0x0C ) // jb 
      { wPos = 0x36F3; continue; }
    r8[cl] >>= 1;
  case 0x36F3:
    r16[ax] = _data16get(si + 0x3447);
    if ( _data[r16[bx] + 0x3417] == 1 ) // jz 
      { wPos = 0x370B; continue; }
    cf = (r16[ax] < r16[cx]); // cf-insertion
    r16[ax] -= r16[cx];
    if ( !cf ) // jnb 
      { wPos = 0x371A; continue; }
    r16[ax] = 0;
    _data[r16[bx] + 0x3417] = 1;
    wPos = 0x371A;
      continue;
  case 0x370B:
    r16[ax] += r16[cx];
    if ( r16[ax] < 0x12F ) // jb 
      { wPos = 0x371A; continue; }
    r16[ax] = 0x12E;
    _data[r16[bx] + 0x3417] = 0x0FF;
  case 0x371A:
    _data16set(si + 0x3447, r16[ax]);
    r8[al] = _data[r16[bx] + 0x3477];
    if ( _data[r16[bx] + 0x342F] == 1 ) // jz 
      { wPos = 0x373C; continue; }
    r8[al]--;
    if ( r8[al] >= _data16get(r16[bx] + 0x34F1) ) // jnb 
      { wPos = 0x3750; continue; }
    r8[al] = _data[r16[bx] + 0x34F1];
    _data[r16[bx] + 0x342F] = 1;
    wPos = 0x3750;
      continue;
  case 0x373C:
    r8[al] = r8[al] + 1;
    r8[dl] = _data[r16[bx] + 0x34F1];
    r8[dl] += 0x18;
    if ( r8[al] <= r8[dl] ) // jbe 
      { wPos = 0x3750; continue; }
    r8[al] = r8[dl];
    _data[r16[bx] + 0x342F] = 0x0FF;
  case 0x3750:
    _data[r16[bx] + 0x3477] = r8[al];
    r8[dl] = r8[al];
    r16[cx] = _data16get(si + 0x3447);
    sub_2CB0();
    _data16set(0x34EF, r16[ax]);
    r16[bx] = _data16get(0x3415);
    sub_37C1();
    r16[bx] = _data16get(0x3415);
    si = r16[bx];
    si <<= 1;
    di = _data16get(0x34EF);
    _data16set(si + 0x34BF, di);
    _data[r16[bx] + 0x348F] = 0;
    r16[ax] = 0x0B800;
    es = r16[ax];
    if ( r16[bx] < 0x0C ) // jb 
      { wPos = 0x379F; continue; }
    si = r16[bx];
    r8[cl] = 3;
    si <<= r8[cl];
    si += _data16get(0x3413);
    si &= 0x18;
    si += 0x3330;
    r16[cx] = 0x202;
    sub_2D9D();
    return;
  case 0x379F:
    si = _data16get(0x3411);
    if ( r8[bl] & 1 ) // jnz 
      { wPos = 0x37AC; continue; }
    si = si ^ 0x0C;
  case 0x37AC:
    if ( _data[r16[bx] + 0x3417] == 1 ) // jz 
      { wPos = 0x37B6; continue; }
    si += 0x18;
  case 0x37B6:
    si += 0x3300;
    r16[cx] = 0x601;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_37C1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[r16[bx] + 0x348F] != 0 ) // jnz 
      return;
    r16[bx] <<= 1;
    si = 0x3404;
    di = _data16get(r16[bx] + 0x34BF);
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x601;
    if ( r16[bx] < 0x18 ) // jb 
      { wPos = 0x37E1; continue; }
    r16[cx] = 0x202;
  case 0x37E1:
    sub_2D9D();
    wPos = -1;
  }
}
function sub_37E5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x350F);
    if ( r16[ax] < 8 ) // jb 
      return;
    _data16set(0x350D, _data16get(0x350D) + 1);
    r16[bx] = _data16get(0x350D);
    if ( r16[bx] < 0x28 ) // jb 
      { wPos = 0x380B; continue; }
    r16[bx] = 0;
    _data16set(0x350D, r16[bx]);
    _data16set(0x350F, r16[dx]);
  case 0x380B:
    di = r16[bx];
    di <<= 1;
    if ( _data[0x57B] > 7 ) // ja 
      { wPos = 0x3829; continue; }
    r16[ax] = _data16get(0x579);
    r8[cl] = 2;
    r16[ax] >>= r8[cl];
    r16[ax] = r16[ax] + 1;
    cf = (r16[ax] < di); // cf-insertion
    r16[ax] -= di;
    if ( !cf ) // jnb 
      { wPos = 0x3824; continue; }
    r16[ax] = ~ r16[ax];
  case 0x3824:
    if ( r16[ax] < 4 ) // jb 
      return;
  case 0x3829:
    di += 0x0A0;
    r8[al] = _data[r16[bx] + 0x2656];
    r8[al] += 8;
    _data[r16[bx] + 0x2656] = r8[al];
    r16[ax] &= 0x18;
    r16[ax] += 0x2020;
    si = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x401;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_3850()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x35DA);
    if ( r16[ax] >= 6 ) // jnb 
      { wPos = 0x3860; continue; }
    return;
  case 0x3860:
    _data16set(0x35DA, r16[dx]);
    _data16set(0x35D8, _data16get(0x35D8) + 2);
    r16[bx] = _data16get(0x35D8);
    r16[bx] &= 6;
    si = _data16get(r16[bx] + 0x35D0);
    di = 0x15C9;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x0A02;
    sub_2D9D();
    r16[ax] = 0x0E4;
    r8[dl] = 0x8A;
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E0A;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      return;
    _data[0x554] = 1;
    wPos = -1;
  }
}
function sub_38B0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x38BA; continue; }
    wPos = 0x38D3;
      continue;
  case 0x38BA:
    _data16set(0x414, _data16get(0x414) + 1);
    _data[0x418] = 1;
    r16[dx] = 0x0AAAA;
    sub_3A96();
    r16[ax] = 0;
    _data[0x369F] = 0;
    sub_3AAC();
  case 0x38D3:
    r8[ah] = 0;
    _int(0x1A);
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x38EF; continue; }
    r16[dx] -= _data16get(0x412);
    r16[ax] = 0x2A30;
    cf = (r16[ax] < r16[dx]); // cf-insertion
    r16[ax] -= r16[dx];
    if ( !cf ) // jnb 
      { wPos = 0x38EB; continue; }
    r16[ax] = 0;
  case 0x38EB:
    r16[ax] >>= 1;
    wPos = 0x390E;
      continue;
  case 0x38EF:
    r16[dx] -= _data16get(0x410);
    r16[ax] = 0x546;
    if ( _data16get(6) != 6 ) // jnz 
      { wPos = 0x38FF; continue; }
    r16[ax] <<= 1;
  case 0x38FF:
    cf = (r16[ax] < r16[dx]); // cf-insertion
    r16[ax] -= r16[dx];
    if ( !cf ) // jnb 
      { wPos = 0x3905; continue; }
    r16[ax] = 0;
  case 0x3905:
    if ( _data16get(6) == 6 ) // jz 
      { wPos = 0x390E; continue; }
    r16[ax] <<= 1;
  case 0x390E:
    _data16set(0x3697, r16[ax]);
    sub_3AF4();
    r16[bx] = _data16get(6);
    r8[bl] <<= 1;
    si = _data16get(r16[bx] + 0x36CC);
    di = 0x368D;
    sub_271E();
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x396E; continue; }
    r16[bx] = _data16get(8);
    r8[bl] <<= 1;
    r16[ax] = r16[bx];
    r16[cx] = _data16get(r16[bx] + 0x36DC);
    if ( _data16get(0x2E8D) >= 8 ) // jnb 
      { wPos = 0x3943; continue; }
    r16[cx] <<= 1;
    r16[ax] += 0x10;
  case 0x3943:
    _data16set(0x370C, r16[ax]);
  case 0x3946:
    si = 0x368D;
    di = 0x1F82;
    _push(r16[cx]);
    sub_271E();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x3946; continue; }
    sub_39FA();
    _data[0x369E] = 0x38;
    _data[0x3699] = 1;
    _data16set(0x3722, 0x44);
    sub_3A3A();
    sub_3A6C();
    wPos = 0x39A7;
      continue;
  case 0x396E:
    si = 0x368D;
    di = 0x1F82;
    sub_271E();
    _data[0x3699] = 2;
    _data16set(0x3722, 0x1E);
    r16[dx] = 0x0FFFF;
    sub_3A96();
    r16[ax] = 0x0A8C;
    r16[ax] -= _data16get(0x3697);
    r8[cl] = 4;
    r16[ax] >>= r8[cl];
    r8[al] &= 0x0F0;
    _data[0x369E] = r8[al];
    r8[ah] = 0x28;
    r16[ax] = r8[ah] * r8[al];
    _data[0x369F] = 1;
    sub_3AAC();
    sub_3A3A();
  case 0x39A7:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x3695, r16[dx]);
  case 0x39AF:
    if ( _data16get(6) != 7 ) // jnz 
      { wPos = 0x39BB; continue; }
    sub_5B63();
    wPos = 0x39BE;
      continue;
  case 0x39BB:
    sub_5835();
  case 0x39BE:
    sub_3A1C();
    r16[dx] -= _data16get(0x3695);
    if ( r16[dx] < _data16get(0x3722) ) // jb 
      { wPos = 0x39AF; continue; }
    r16[bx] = 0;
    r8[ah] = 0x0B;
    _int(0x10);
    if ( _data16get(6) == 7 ) // jz 
      { wPos = 0x39DC; continue; }
    sub_5B21();
    return;
  case 0x39DC:
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x0E;
    di = 0x8E4;
    r16[cx] = 0x804;
    sub_2D9D();
    si = 0x4E;
    di = 0x0C94;
    r16[cx] = 0x814;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_39FA()
{
  _push(ds);
  es = _pop();
  r16[ax] = 0x0B800;
  ds = r16[ax];
  r16[cx] = 0x804;
  di = 0x0E;
  si = 0x8E4;
  sub_2DCA();
  r16[cx] = 0x814;
  di = 0x4E;
  si = 0x0C94;
  sub_2DCA();
  _push(es);
  ds = _pop();
}
function sub_3A1C()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    _push(r16[dx]);
    r16[dx] = _pop();
    _push(r16[dx]);
    r16[bx] = 0;
    if ( r16[dx] & 4 ) // jnz 
      { wPos = 0x3A34; continue; }
    r8[bl] = _data[0x3699];
  case 0x3A34:
    r8[ah] = 0x0B;
    _int(0x10);
    r16[dx] = _pop();
    wPos = -1;
  }
}
function sub_3A3A()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 2;
    r8[dh] = _data[0x369E];
    r8[cl] = 3;
    r8[dh] >>= r8[cl];
    r8[dl] = 0x12;
    r8[bh] = 0;
    _int(0x10);
    _data16set(0x36A0, 3);
  case 0x3A50:
    r16[bx] = _data16get(0x36A0);
    r8[al] = _data[r16[bx] + 0x368D];
    r8[al] += 0x30;
    r8[ah] = 0x0E;
    r8[bl] = 3;
    _int(0x10);
    _data16set(0x36A0, _data16get(0x36A0) + 1);
    if ( _data16get(0x36A0) < 7 ) // jb 
      { wPos = 0x3A50; continue; }
    wPos = -1;
  }
}
function sub_3A6C()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 2;
    r8[dl] = 0x0A;
    r8[dh] = r8[dl];
    r16[bx] = 0;
    _int(0x10);
    r16[bx] = _data16get(0x370C);
    r16[ax] = _data16get(r16[bx] + 0x36EC);
    _data16set(0x3720, r16[ax]);
    r16[bx] = 0;
  case 0x3A83:
    r8[ah] = 0x0E;
    r8[al] = _data[r16[bx] + 0x370E];
    _push(r16[bx]);
    r8[bl] = 3;
    _int(0x10);
    r16[bx] = _pop();
    r16[bx] = r16[bx] + 1;
    if ( r16[bx] < 0x14 ) // jb 
      { wPos = 0x3A83; continue; }
    wPos = -1;
  }
}
function sub_3A96()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    r16[ax] = seg_data;
    es = r16[ax];
    di = 0x0E;
    si = 0x35E0;
    r16[cx] = 0x1E;
  case 0x3AA5:
    _lodsw();
    r16[ax] &= r16[dx];
    _stosw();
    if ( --r16[cx] )
      { wPos = 0x3AA5; continue; }
    wPos = -1;
  }
}
function sub_3AAC()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x369A, r16[ax]);
    r16[ax] = 0x0B800;
    es = r16[ax];
    sub_5829();
    r16[ax] = 0x1B80;
  case 0x3ABA:
    r16[bx] = 0x361C;
    _data16set(0x369C, r16[ax]);
    sub_2B24();
    if ( _data[0x369F] == 0 ) // jz 
      { wPos = 0x3AE2; continue; }
    sub_5869();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x3695, r16[dx]);
  case 0x3AD5:
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x3695);
    if ( r16[dx] < 2 ) // jb 
      { wPos = 0x3AD5; continue; }
  case 0x3AE2:
    r16[ax] = _data16get(0x369C);
    cf = (r16[ax] < 0x280); // cf-insertion
    r16[ax] -= 0x280;
    if ( cf ) // jb 
      { wPos = 0x3AF0; continue; }
    if ( r16[ax] >= _data16get(0x369A) ) // jnb 
      { wPos = 0x3ABA; continue; }
  case 0x3AF0:
    sub_5B21();
    wPos = -1;
  }
}
function sub_3AF4()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x368B, r16[ax]);
    r16[ax] = 0;
    _data16set(0x368D, r16[ax]);
    _data16set(0x368F, r16[ax]);
    _data16set(0x3691, r16[ax]);
    _data16set(0x3693, r16[ax]);
    r16[bx] = 0x3684;
    r16[dx] = 0x1000;
  case 0x3B0B:
    if ( !(_data16get(0x368B) & r16[dx]) ) // jz 
      { wPos = 0x3B19; continue; }
    si = r16[bx];
    di = 0x368D;
    sub_271E();
  case 0x3B19:
    r16[bx] -= 7;
    r16[dx] >>= 1;
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3B0B; continue; }
    wPos = -1;
  }
}
function sub_3B30()
{
  _data[0x37AF] = 3;
  r16[ax] = 1;
  _data16set(0x37B0, r16[ax]);
  _data16set(0x37B2, r16[ax]);
  _data16set(0x37B4, r16[ax]);
}
function sub_3B42()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x37B8) ) // jnz 
      { wPos = 0x3B4D; continue; }
    return;
  case 0x3B4D:
    _data16set(0x37B8, r16[dx]);
    _data16set(0x37B6, 4);
  case 0x3B57:
    r16[bx] = _data16get(0x37B6);
    if ( _data16get(r16[bx] + 0x37B0) == 0 ) // jz 
      { wPos = 0x3B9B; continue; }
    r16[ax] = _data16get(r16[bx] + 0x37A3);
    r8[dl] = 0x18;
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E10;
    sub_2E29();
    if ( !cf ) // jnb cf=0
      { wPos = 0x3B9B; continue; }
    r16[ax] = 0x0C00;
    r16[bx] = 0x8FD;
    sub_593B();
    sub_11E3();
    sub_3E38();
    r16[bx] = _data16get(0x37B6);
    sub_3BA3();
    sub_1124();
    sub_3E14();
    return;
  case 0x3B9B:
    cf = (_data16get(0x37B6) < 2); // cf-insertion
    _data16set(0x37B6, _data16get(0x37B6) - 2);
    if ( !cf ) // jnb 
      { wPos = 0x3B57; continue; }
    wPos = -1;
  }
}
function sub_3BA3()
{
  _data16set(r16[bx] + 0x37B0, 0);
  _push(ds);
  es = _pop();
  _cld();
  r16[ax] = 0x0AAAA;
  di = 0x0E;
  si = di;
  r16[cx] = 0x20;
  _rep_stosw();
  di = _data16get(r16[bx] + 0x37A9);
  r16[ax] = 0x0B800;
  es = r16[ax];
  r16[cx] = 0x1002;
  sub_2D9D();
  _data[0x37AF]--;
  if ( _data[0x37AF] ) // jnz 
    return;
  if ( _data[0x552] != 0 ) // jnz 
    return;
  _data[0x553] = 1;
}
function sub_3BDB()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _data16set(0x37A0, 0x66A);
    r16[cx] = 0x10;
  case 0x3BE9:
    r16[ax] = 0;
    r16[bx] = r16[ax];
  case 0x3BED:
    _data[0x37A2] = r8[al];
    r8[ah] = 0;
    r16[ax] += 0x3730;
    si = r16[ax];
    di = _data16get(0x37A0);
    di += r16[bx];
    _push(r16[cx]);
    r16[cx] = 0x801;
    _push(r16[bx]);
    sub_2D9D();
    r16[bx] = _pop();
    r16[cx] = _pop();
    r16[bx] += 2;
    if ( r16[bx] < 0x1E ) // jb 
      { wPos = 0x3C1E; continue; }
    if ( r16[bx] != 0x1E ) // jnz 
      { wPos = 0x3C15; continue; }
    r8[al] = 0x20;
    wPos = 0x3BED;
      continue;
  case 0x3C15:
    _data16set(0x37A0, _data16get(0x37A0) + 0x140);
    if ( --r16[cx] )
      { wPos = 0x3BE9; continue; }
    return;
  case 0x3C1E:
    if ( _data[0x37A2] == 0x50 ) // jz 
      { wPos = 0x3C36; continue; }
    if ( r8[cl] & 1 ) // jnz 
      { wPos = 0x3C36; continue; }
    sub_2DFD();
    if ( r8[dl] < 0x40 ) // jb 
      { wPos = 0x3C36; continue; }
    r8[al] = 0x10;
    wPos = 0x3BED;
      continue;
  case 0x3C36:
    sub_2DFD();
    r8[al] = r8[dl];
    r8[al] -= r8[bl];
    r8[al] &= 0x30;
    r8[al] += 0x30;
    wPos = 0x3BED;
      continue;
    wPos = -1;
  }
}
function sub_3C43()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x579);
    r16[ax] &= 0x0FFFC;
    if ( r16[ax] < 0x0A4 ) // jb 
      { wPos = 0x3C7F; continue; }
    if ( r16[ax] > 0x118 ) // ja 
      { wPos = 0x3C7F; continue; }
    r8[dl] = _data[0x57B];
    r8[dl] -= 2;
    r8[dl] &= 0x0F8;
    if ( !(r8[dl] & 8) ) // jz 
      { wPos = 0x3C7F; continue; }
    if ( r8[dl] < 0x28 ) // jb 
      { wPos = 0x3C7F; continue; }
    if ( r8[dl] > 0x0A0 ) // ja 
      { wPos = 0x3C7F; continue; }
    _data16set(0x579, r16[ax]);
    r8[dl] += 2;
    _data[0x57B] = r8[dl];
    r8[dl] += 0x32;
    _data[0x57C] = r8[dl];
    _stc();
    return;
  case 0x3C7F:
    _clc();
    wPos = -1;
  }
}
function sub_3C90()
{
  _data[0x3966] = 8;
  _data[0x396A] = 1;
  _data[0x3967] = 0;
  _data[0x396D] = 2;
  _data16set(0x3964, 0x118);
  _data16set(0x396B, 0);
}
function sub_3CB1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x39C8);
    if ( r16[ax] >= 2 ) // jnb 
      { wPos = 0x3CC1; continue; }
    return;
  case 0x3CC1:
    _data16set(0x39C8, r16[dx]);
    sub_3E52();
    if ( unknown_condition() ) // jb cf=1
      return;
    sub_3E6E();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3CD2; continue; }
    wPos = 0x3D90;
      continue;
  case 0x3CD2:
    r16[bx] = _data16get(8);
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x39CC);
    _data16set(0x39C6, r16[ax]);
    r16[ax] = _data16get(0x3964);
    _data16set(0x39C3, r16[ax]);
    r8[dl] = _data[0x3966];
    _data[0x39C5] = r8[dl];
    if ( r8[dl] != 8 ) // jnz 
      { wPos = 0x3D25; continue; }
    r16[ax] &= 0x0FFF8;
    r16[dx] = _data16get(0x579);
    r16[dx] &= 0x0FFF8;
    if ( r16[ax] != r16[dx] ) // jnz 
      { wPos = 0x3D0D; continue; }
    _data[0x3967] = 1;
    _data[0x396E] = 1;
    wPos = 0x3D25;
      continue;
  case 0x3D0D:
    r16[ax] = _data16get(0x3964);
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x3D1C; continue; }
    cf = (r16[ax] < _data16get(0x39C6)); // cf-insertion
    r16[ax] -= _data16get(0x39C6);
    if ( !cf ) // jnb 
      { wPos = 0x3D20; continue; }
    r16[ax] = 0;
    wPos = 0x3D20;
      continue;
  case 0x3D1C:
    r16[ax] += _data16get(0x39C6);
  case 0x3D20:
    _data16set(0x3964, r16[ax]);
    wPos = 0x3D79;
      continue;
  case 0x3D25:
    r8[al] = _data[0x3966];
    _data[0x396E] = _data[0x396E] + 1;
    r8[dl] = _data[0x396E];
    r8[dl] >>= 1;
    r8[dl] >>= 1;
    r8[dl] &= 3;
    r8[dl] += 2;
    if ( _data[0x3967] == 1 ) // jz 
      { wPos = 0x3D52; continue; }
    cf = (r8[al] < r8[dl]); // cf-insertion
    r8[al] -= r8[dl];
    if ( cf ) // jb 
      { wPos = 0x3D49; continue; }
    if ( r8[al] >= 9 ) // jnb 
      { wPos = 0x3D76; continue; }
  case 0x3D49:
    r8[al] = 8;
    _data[0x3967] = 0;
    wPos = 0x3D76;
      continue;
  case 0x3D52:
    r8[al] += r8[dl];
    if ( r8[al] > _data16get(0x57B) ) // ja 
      { wPos = 0x3D71; continue; }
    r16[bx] = _data16get(0x3964);
    cf = (r16[bx] < _data16get(0x579)); // cf-insertion
    r16[bx] -= _data16get(0x579);
    if ( !cf ) // jnb 
      { wPos = 0x3D66; continue; }
    r16[bx] = ~ r16[bx];
  case 0x3D66:
    if ( r16[bx] > 0x30 ) // ja 
      { wPos = 0x3D71; continue; }
    if ( r8[al] < 0x0A0 ) // jb 
      { wPos = 0x3D76; continue; }
    r8[al] = 0x9F;
  case 0x3D71:
    _data[0x3967] = 0x0FF;
  case 0x3D76:
    _data[0x3966] = r8[al];
  case 0x3D79:
    sub_3E52();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3D8B; continue; }
    r16[ax] = _data16get(0x39C3);
    _data16set(0x3964, r16[ax]);
    r8[al] = _data[0x39C5];
    _data[0x3966] = r8[al];
    return;
  case 0x3D8B:
    sub_3E6E();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x3DEE; continue; }
  case 0x3D90:
    if ( _data[0x553] == 0 ) // jz 
      { wPos = 0x3D98; continue; }
    return;
  case 0x3D98:
    r16[cx] = _data16get(0x579);
    cf = (r16[cx] < 0x0C); // cf-insertion
    r16[cx] -= 0x0C;
    if ( !cf ) // jnb 
      { wPos = 0x3DA3; continue; }
    r16[cx] = 0;
  case 0x3DA3:
    if ( r16[cx] < 0x10F ) // jb 
      { wPos = 0x3DAC; continue; }
    r16[cx] = 0x10E;
  case 0x3DAC:
    r8[dl] = _data[0x57B];
    cf = (r8[dl] < 4); // cf-insertion
    r8[dl] -= 4;
    if ( !cf ) // jnb 
      { wPos = 0x3DB7; continue; }
    r8[dl] = 0;
  case 0x3DB7:
    sub_2CB0();
    di = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x37C0;
    bp = 0x0E;
    r16[cx] = 0x1506;
    sub_2CCC();
    sub_56F4();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x39C8, r16[dx]);
  case 0x3DD8:
    sub_5704();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x39C8);
    if ( r16[dx] < 9 ) // jb 
      { wPos = 0x3DD8; continue; }
    _data[0x552] = 1;
    return;
  case 0x3DEE:
    r16[cx] = _data16get(0x3964);
    r8[dl] = _data[0x3966];
    sub_2CB0();
    _data16set(0x39CA, r16[ax]);
    sub_3E38();
    _data[0x396D]--;
    if ( _data[0x396D] ) // jnz 
      { wPos = 0x3E10; continue; }
    _data[0x396D] = 2;
    _data16set(0x396B, _data16get(0x396B) ^ 0x54);
  case 0x3E10:
    sub_3E14();
    wPos = -1;
  }
}
function sub_3E14()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x39CA);
  _data16set(0x3968, di);
  bp = 0x396F;
  _data[0x396A] = 0;
  si = _data16get(0x396B);
  si += 0x38BC;
  r16[cx] = 0x0E03;
  sub_2CCC();
}
function sub_3E38()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  if ( _data[0x396A] != 0 ) // jnz 
    return;
  di = _data16get(0x3968);
  si = 0x396F;
  r16[cx] = 0x0E03;
  sub_2D9D();
}
function sub_3E52()
{
  r16[ax] = _data16get(0x3964);
  r8[dl] = _data[0x3966];
  si = 0x18;
  r16[bx] = _data16get(0x327D);
  r8[dh] = _data[0x327F];
  di = 0x10;
  r16[cx] = 0x1E0E;
  sub_2E29();
}
function sub_3E6E()
{
  r16[ax] = _data16get(0x3964);
  r8[dl] = _data[0x3966];
  si = 0x18;
  di = si;
  r16[bx] = _data16get(0x579);
  r8[dh] = _data[0x57B];
  r16[cx] = 0x0E0E;
  sub_2E29();
}
function sub_3E90()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x39E1] == 0 ) // jz 
      { wPos = 0x3EA4; continue; }
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x3D16) ) // jz 
      return;
    wPos = 0x3F35;
      continue;
  case 0x3EA4:
    if ( _data[0x584] != 0 ) // jnz 
      return;
    if ( _data[0x69A] != 0 ) // jnz 
      return;
    if ( _data[0x39E0] != 0 ) // jnz 
      { wPos = 0x3EBA; continue; }
    return;
  case 0x3EBA:
    sub_4065();
    if ( unknown_condition() ) // jb cf=1
      return;
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x3D18);
    if ( r16[ax] < 0x0C ) // jb 
      return;
    _data16set(0x3D18, r16[dx]);
    _data[0x55C] = 0;
    r8[bl] = _data[0x39E0];
    r8[bl]--;
    r8[bh] = 0;
    si = r16[bx];
    r8[cl] = 2;
    si <<= r8[cl];
    r16[ax] = _data16get(si + 0x3C5A);
    _data16set(0x39E2, r16[ax]);
    r16[ax] = 0;
    if ( r8[bl] >= 3 ) // jnb 
      { wPos = 0x3EF5; continue; }
    r8[al] = 0x80;
  case 0x3EF5:
    _data16set(0x39E4, r16[ax]);
    r8[bl] = _data[r16[bx] + 0x3CE3];
    si = r16[bx];
    r8[cl] = 2;
    si <<= r8[cl];
    r16[ax] = _data16get(si + 0x3C5A);
    _data16set(0x39E6, r16[ax]);
    r16[ax] = 0;
    if ( r8[bl] >= 3 ) // jnb 
      { wPos = 0x3F12; continue; }
    r8[al] = 0x80;
  case 0x3F12:
    _data16set(0x39E8, r16[ax]);
    r8[al] = _data[r16[bx] + 0x1050];
    _data[0x3D05] = r8[al];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x1137);
    r16[ax] += 8;
    _data16set(0x3D03, r16[ax]);
    sub_11E3();
    _data[0x39E1] = 0x0E;
    _data[0x69A] = 0x10;
  case 0x3F35:
    if ( _data[0x1CBF] != 0 ) // jnz 
      { wPos = 0x3F3F; continue; }
    sub_33A0();
  case 0x3F3F:
    _data[0x39E1] -= 2;
    r8[bh] = 0;
    r8[bl] = _data[0x39E1];
    if ( r8[bl] < 8 ) // jb 
      { wPos = 0x3F58; continue; }
    di = _data16get(0x39E2);
    r16[ax] = _data16get(0x39E4);
    wPos = 0x3F70;
      continue;
  case 0x3F58:
    di = _data16get(0x39E6);
    r8[al] = _data[0x3D05];
    _data[0x57B] = r8[al];
    r8[al] += 0x32;
    _data[0x57C] = r8[al];
    r16[ax] = _data16get(0x3D03);
    _data16set(0x579, r16[ax]);
    r16[ax] = _data16get(0x39E8);
  case 0x3F70:
    r16[ax] += _data16get(r16[bx] + 0x3D06);
    si = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x1002;
    sub_2D9D();
    if ( _data[0x1CBF] != 0 ) // jnz 
      { wPos = 0x3F8B; continue; }
    sub_3339();
  case 0x3F8B:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x3D16, r16[dx]);
    if ( _data[0x39E1] != 0 ) // jnz 
      return;
    sub_1112();
    wPos = -1;
  }
}
function sub_3F9E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _data[0x39E0] = 0;
    _data[0x39E1] = 0;
    _data16set(0x3CBF, 0x506);
    _data16set(0x3CC1, 0);
  case 0x3FB9:
    r16[bx] = _data16get(0x3CC1);
    r8[cl] = _data[r16[bx] + 0x3CAE];
    r16[bx] = 0;
    r8[ch] = r8[bl];
  case 0x3FC5:
    si = 0x3AEA;
    sub_2DFD();
    if ( r8[dl] > 0x30 ) // ja 
      { wPos = 0x3FDB; continue; }
    si = 0x3AF8;
    if ( r8[dl] & 4 ) // jnz 
      { wPos = 0x3FDB; continue; }
    si = 0x3B02;
  case 0x3FDB:
    di = _data16get(0x3CBF);
    di += r16[bx];
    _push(r16[cx]);
    _push(r16[bx]);
    r16[cx] = 0x801;
    sub_2D9D();
    r16[bx] = _pop();
    r16[cx] = _pop();
    r16[bx] += 2;
    if ( --r16[cx] )
      { wPos = 0x3FC5; continue; }
    _data16set(0x3CBF, _data16get(0x3CBF) + 0x140);
    _data16set(0x3CC1, _data16get(0x3CC1) + 1);
    if ( _data16get(0x3CC1) < 0x11 ) // jb 
      { wPos = 0x3FB9; continue; }
    r16[bx] = 0x3C22;
    r16[ax] = 0;
    sub_2B24();
    r16[bx] = 0x3C3E;
    r16[ax] = 0;
    sub_2B24();
    r16[bx] = 0x3C9A;
    r16[ax] = 0;
    sub_2B24();
    r16[bx] = 0x3C56;
    r16[ax] = 0;
    sub_2B24();
    si = 0x3CAA;
    di = 0x8EC;
    r16[cx] = 0x102;
    bp = 0x0E;
    sub_2D35();
    si = 0;
    r16[bx] = _data16get(8);
    r8[cl] = 3;
    r8[bl] &= r8[cl];
    r8[bl] <<= r8[cl];
  case 0x403C:
    r8[al] = _data[r16[bx] + 0x3CC3];
    r8[ah] = r8[al];
    r8[cl] = 4;
    r8[al] >>= r8[cl];
    _data[si + 0x3CE3] = r8[al];
    _data[si + 0x3CF3] = 0;
    r8[ah] &= 0x0F;
    _data[si + 0x3CE4] = r8[ah];
    _data[si + 0x3CF4] = 0;
    si += 2;
    r16[bx] = r16[bx] + 1;
    if ( si < 0x10 ) // jb 
      { wPos = 0x403C; continue; }
    wPos = -1;
  }
}
function sub_4065()
{
  r16[ax] = _data16get(0x327D);
  r8[dl] = _data[0x327F];
  si = 0x10;
  r16[bx] = _data16get(0x579);
  r8[dh] = _data[0x57B];
  di = 0x18;
  r16[cx] = 0x0E1E;
  sub_2E29();
}
function sub_4090()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 4;
  case 0x4093:
    r16[bx] = r16[cx];
    r16[bx]--;
    si = r16[bx];
    si <<= 1;
    _data[r16[bx] + 0x3EAE] = 1;
    _data[r16[bx] + 0x3EB2] = 0;
    sub_4277();
    sub_2DFD();
    r8[dl] &= 0x0F;
    r8[dl] += 0x14;
    _data[r16[bx] + 0x3EB6] = r8[dl];
    if ( --r16[cx] )
      { wPos = 0x4093; continue; }
    _data16set(0x3EDA, 0);
    _data[0x3ED8] = 4;
    wPos = -1;
  }
}
function sub_40C2()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x3EDC) ) // jnz 
      { wPos = 0x40CD; continue; }
    return;
  case 0x40CD:
    _data16set(0x3EDA, _data16get(0x3EDA) + 1);
    r16[bx] = _data16get(0x3EDA);
    if ( r16[bx] <= 2 ) // jbe 
      { wPos = 0x40E5; continue; }
    if ( r16[bx] < 4 ) // jb 
      { wPos = 0x40E9; continue; }
    r16[bx] = 0;
    _data16set(0x3EDA, r16[bx]);
  case 0x40E5:
    _data16set(0x3EDC, r16[dx]);
  case 0x40E9:
    si = r16[bx];
    si <<= 1;
    if ( _data[r16[bx] + 0x3EB2] != 0 ) // jnz 
      return;
    sub_42DB();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x40FC; continue; }
    wPos = 0x4124;
      continue;
  case 0x40FC:
    sub_42FC();
    if ( unknown_condition() ) // jb cf=1
      return;
    if ( _data[r16[bx] + 0x3EB6] != 0 ) // jnz 
      { wPos = 0x4118; continue; }
    sub_4277();
    sub_2DFD();
    r8[dl] &= 7;
    r8[dl] += 0x14;
    _data[r16[bx] + 0x3EB6] = r8[dl];
  case 0x4118:
    _data[r16[bx] + 0x3EB6]--;
    sub_42DB();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x4124; continue; }
    wPos = 0x4181;
      continue;
  case 0x4124:
    if ( _data[r16[bx] + 0x3EAE] != 0 ) // jnz 
      return;
    if ( _data[r16[bx] + 0x3EB6] < 0x14 ) // jb 
      { wPos = 0x4133; continue; }
    return;
  case 0x4133:
    sub_11E3();
    sub_4254();
    r16[bx] = _data16get(0x3EDA);
    _data[r16[bx] + 0x3EB2] = 1;
    sub_1124();
    _data[0x55C] = 0;
    _data[0x3ED8]--;
    if ( _data[0x3ED8] ) // jnz 
      { wPos = 0x4155; continue; }
    _data[0x553] = 1;
  case 0x4155:
    r8[al] = 4;
    r8[al] -= _data16get(0x3ED8);
    r8[cl] = 2;
    r8[al] <<= r8[cl];
    r8[ah] = 0;
    r16[ax] += 0x51;
    di = r16[ax];
    bp = 0x0E;
    si = 0x3D20;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x0C02;
    sub_2D35();
    r16[ax] = 0x3E8;
    r16[bx] = 0x2EE;
    sub_593B();
    return;
  case 0x4181:
    sub_42B4();
    di = _data16get(8);
    di <<= 1;
    bp = _data16get(di + 0x3EDE);
    sub_431C();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x41B0; continue; }
    if ( _data[r16[bx] + 0x3EB6] < 2 ) // jb 
      { wPos = 0x41B0; continue; }
    r8[al] = 1;
    if ( _data[r16[bx] + 0x3EB6] <= 0x11 ) // jbe 
      { wPos = 0x41AC; continue; }
    if ( _data[r16[bx] + 0x3EB6] >= 0x14 ) // jnb 
      { wPos = 0x41B0; continue; }
    r8[al]--;
  case 0x41AC:
    _data[r16[bx] + 0x3EB6] = r8[al];
  case 0x41B0:
    r8[al] = _data[r16[bx] + 0x3EB6];
    if ( r8[al] <= 1 ) // jbe 
      { wPos = 0x41D8; continue; }
    if ( r8[al] < 0x12 ) // jb 
      { wPos = 0x41F8; continue; }
    r8[al] = 1;
    if ( _data16get(si + 0x3EBA) >= 3 ) // jnb 
      { wPos = 0x41C7; continue; }
    r8[al] = 3;
  case 0x41C7:
    _data16set(r16[bx] + 0x3ED4, _data16get(r16[bx] + 0x3ED4) + r8[al]);
    if ( _data[r16[bx] + 0x3EB6] < 0x13 ) // jb 
      { wPos = 0x41F3; continue; }
    if ( _data[r16[bx] + 0x3EB6] == 0x13 ) // jz 
      { wPos = 0x41EE; continue; }
    r16[ax] = 0;
    wPos = 0x4204;
      continue;
  case 0x41D8:
    r8[al] = 1;
    if ( _data16get(si + 0x3EBA) >= 3 ) // jnb 
      { wPos = 0x41E3; continue; }
    r8[al] = 3;
  case 0x41E3:
    _data16set(r16[bx] + 0x3ED4, _data16get(r16[bx] + 0x3ED4) + r8[al]);
    if ( _data[r16[bx] + 0x3EB6] >= 1 ) // jnb 
      { wPos = 0x41F3; continue; }
  case 0x41EE:
    r16[ax] = 0x3DB0;
    wPos = 0x4204;
      continue;
  case 0x41F3:
    r16[ax] = 0x3D80;
    wPos = 0x4204;
      continue;
  case 0x41F8:
    r8[al] <<= 1;
    di = r16[ax];
    di &= 2;
    r16[ax] = _data16get(di + 0x3DE0);
  case 0x4204:
    _data16set(0x3ECA, r16[ax]);
    r8[dl] = _data[r16[bx] + 0x3ED4];
    r16[cx] = _data16get(si + 0x3ECC);
    sub_2CB0();
    _data16set(0x3DE4, r16[ax]);
    sub_4254();
    r16[bx] = _data16get(0x3EDA);
    si = r16[bx];
    si <<= 1;
    sub_42FC();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4226; continue; }
    return;
  case 0x4226:
    if ( _data16get(0x3ECA) != 0 ) // jnz 
      { wPos = 0x4233; continue; }
    _data[r16[bx] + 0x3EAE] = 1;
    return;
  case 0x4233:
    _data[r16[bx] + 0x3EAE] = 0;
    di = _data16get(0x3DE4);
    _data16set(si + 0x3EA6, di);
    r16[ax] = 0x0B800;
    es = r16[ax];
    bp = _data16get(si + 0x3EC2);
    r16[cx] = 0x0C02;
    si = _data16get(0x3ECA);
    sub_2D35();
    wPos = -1;
  }
}
function sub_4254()
{
  r16[bx] = _data16get(0x3EDA);
  si = r16[bx];
  si <<= 1;
  if ( _data[r16[bx] + 0x3EAE] != 0 ) // jnz 
    return;
  di = _data16get(si + 0x3EA6);
  r16[cx] = 0x0C02;
  si = _data16get(si + 0x3EC2);
  r16[ax] = 0x0B800;
  es = r16[ax];
  sub_2D9D();
}
function sub_4277()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x3ED9] = 0x20;
  case 0x427C:
    sub_2DFD();
    r16[dx] &= 0x0F;
    di = 0;
  case 0x4285:
    if ( di == si ) // jz 
      { wPos = 0x428F; continue; }
    if ( r16[dx] == _data16get(di + 0x3EBA) ) // jz 
      { wPos = 0x427C; continue; }
  case 0x428F:
    di += 2;
    if ( di < 8 ) // jb 
      { wPos = 0x4285; continue; }
    _data16set(si + 0x3EBA, r16[dx]);
    sub_42B4();
    if ( _data[0x3ED9] == 0 ) // jz 
      return;
    bp = 0x32;
    sub_431C();
    if ( unknown_condition() ) // jnb cf=0
      return;
    _data[0x3ED9]--;
    wPos = 0x427C;
      continue;
    wPos = -1;
  }
}
function sub_42B4()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    di = _data16get(si + 0x3EBA);
    r8[al] = _data[di + 0x1050];
    r8[dl] = 0x0A;
    if ( di >= 3 ) // jnb 
      { wPos = 0x42C5; continue; }
    r8[dl] = 0;
  case 0x42C5:
    r8[al] -= r8[dl];
    r8[al] += 3;
    _data[r16[bx] + 0x3ED4] = r8[al];
    di <<= 1;
    r16[ax] = _data16get(di + 0x1137);
    r16[ax] += 8;
    _data16set(si + 0x3ECC, r16[ax]);
    wPos = -1;
  }
}
function sub_42DB()
{
  _push(si);
  _push(r16[bx]);
  r16[ax] = _data16get(si + 0x3ECC);
  r8[dl] = _data[r16[bx] + 0x3ED4];
  si = 0x10;
  r16[bx] = _data16get(0x579);
  r8[dh] = _data[0x57B];
  di = 0x18;
  r16[cx] = 0x0E0C;
  sub_2E29();
  r16[bx] = _pop();
  si = _pop();
}
function sub_42FC()
{
  _push(si);
  _push(r16[bx]);
  r16[ax] = _data16get(si + 0x3ECC);
  r8[dl] = _data[r16[bx] + 0x3ED4];
  si = 0x10;
  r16[bx] = _data16get(0x327D);
  r8[dh] = _data[0x327F];
  di = si;
  r16[cx] = 0x1E0C;
  sub_2E29();
  r16[bx] = _pop();
  si = _pop();
}
function sub_431C()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(si + 0x3ECC);
    cf = (r16[ax] < _data16get(0x579)); // cf-insertion
    r16[ax] -= _data16get(0x579);
    if ( !cf ) // jnb 
      { wPos = 0x4328; continue; }
    r16[ax] = ~ r16[ax];
  case 0x4328:
    r8[dl] = _data[r16[bx] + 0x3ED4];
    cf = (r8[dl] < _data16get(0x57B)); // cf-insertion
    r8[dl] -= _data16get(0x57B);
    if ( !cf ) // jnb 
      { wPos = 0x4334; continue; }
    r8[dl] = ~ r8[dl];
  case 0x4334:
    r8[dh] = 0;
    r16[ax] += r16[dx];
    if ( r16[ax] < bp ) // jb 
      { wPos = 0x433E; continue; }
    _clc();
    return;
  case 0x433E:
    _stc();
    wPos = -1;
  }
}
function sub_4340()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x40B5) ) // jnz 
      { wPos = 0x434B; continue; }
    return;
  case 0x434B:
    _data[0x40FF] = _data[0x40FF] + 1;
    if ( !(_data[0x40FF] & 3) ) // jz 
      { wPos = 0x435A; continue; }
    _data16set(0x40B5, r16[dx]);
  case 0x435A:
    if ( _data[0x40AA] < 0x0A4 ) // jb 
      return;
    sub_452D();
    sub_4557();
    if ( unknown_condition() ) // jb cf=1
      return;
    sub_2DFD();
    if ( r8[dl] > 0x30 ) // ja 
      { wPos = 0x439C; continue; }
    sub_44FB();
    si = _data16get(8);
    si <<= 1;
    r16[ax] = _data16get(si + 0x40CE);
    if ( _data16get(0x40CC) > r16[ax] ) // ja 
      { wPos = 0x439C; continue; }
    sub_595D();
    _data16set(0x40C8, 0x0FF);
    r8[al] = _data[0x40CA];
    _data[0x40B7] = r8[al];
    r8[al] = _data[0x40CB];
    _data[0x40B8] = r8[al];
    wPos = 0x442E;
      continue;
  case 0x439C:
    if ( _data16get(0x40C8) > 0x0A ) // ja 
      { wPos = 0x43B1; continue; }
    sub_2DFD();
    if ( r8[dl] > 6 ) // ja 
      { wPos = 0x43B4; continue; }
    _data16set(0x40C8, 0x0FF);
  case 0x43B1:
    wPos = 0x4402;
      continue;
  case 0x43B4:
    r16[bx] = _data16get(0x40C8);
    si = r16[bx];
    si <<= 1;
    r8[dl] = 0;
    r16[ax] = _data16get(0x40B2);
    r16[ax] &= 0x0FFC;
    if ( r16[ax] == _data16get(si + 0x40DE) ) // jz 
      { wPos = 0x43D0; continue; }
    r8[dl] = r8[dl] + 1;
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x43D0; continue; }
    r8[dl] = 0x0FF;
  case 0x43D0:
    _data[0x40B7] = r8[dl];
    r8[dl] = 0;
    r8[al] = _data[0x40B4];
    r8[al] &= 0x0FE;
    if ( r8[al] == _data16get(r16[bx] + 0x40F4) ) // jz 
      { wPos = 0x43E7; continue; }
    r8[dl] = r8[dl] + 1;
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x43E7; continue; }
    r8[dl] = 0x0FF;
  case 0x43E7:
    _data[0x40B8] = r8[dl];
    r8[dl] |= _data16get(0x40B7);
    if ( r8[dl] ) // jnz 
      { wPos = 0x442E; continue; }
    sub_2DFD();
    if ( r8[dl] > 0x10 ) // ja 
      { wPos = 0x442E; continue; }
    _data16set(0x40C8, 0x0FF);
    sub_595D();
  case 0x4402:
    sub_2DFD();
    if ( r8[dl] > 0x30 ) // ja 
      { wPos = 0x4423; continue; }
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x4411; continue; }
    r8[dl] = 0x0FF;
  case 0x4411:
    _data[0x40B7] = r8[dl];
    sub_2DFD();
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x441F; continue; }
    r8[dl] = 0x0FF;
  case 0x441F:
    _data[0x40B8] = r8[dl];
  case 0x4423:
    sub_2DFD();
    r16[dx] &= 0x0FF;
    _data16set(0x40C8, r16[dx]);
  case 0x442E:
    r8[al] = _data[0x40B4];
    if ( _data[0x40B8] < 1 ) // jb 
      { wPos = 0x4459; continue; }
    if ( _data[0x40B8] != 1 ) // jnz 
      { wPos = 0x4449; continue; }
    r8[al] += 2;
    if ( r8[al] < 0x0A8 ) // jb 
      { wPos = 0x4456; continue; }
    r8[al] = 0x0A7;
    _data[0x40B8] = 0x0FF;
    wPos = 0x4456;
      continue;
  case 0x4449:
    r8[al] -= 2;
    if ( r8[al] >= 0x30 ) // jnb 
      { wPos = 0x4456; continue; }
    r8[al] = 0x30;
    _data[0x40B8] = 1;
  case 0x4456:
    _data[0x40B4] = r8[al];
  case 0x4459:
    r16[ax] = _data16get(0x40B2);
    if ( _data[0x40B7] < 1 ) // jb 
      { wPos = 0x4486; continue; }
    if ( _data[0x40B7] != 1 ) // jnz 
      { wPos = 0x4477; continue; }
    r16[ax] += 4;
    if ( r16[ax] < 0x136 ) // jb 
      { wPos = 0x4483; continue; }
    r16[ax] = 0x135;
    _data[0x40B7] = 0x0FF;
    wPos = 0x4483;
      continue;
  case 0x4477:
    cf = (r16[ax] < 4); // cf-insertion
    r16[ax] -= 4;
    if ( !cf ) // jnb 
      { wPos = 0x4483; continue; }
    r16[ax] = 0;
    _data[0x40B7] = 1;
  case 0x4483:
    _data16set(0x40B2, r16[ax]);
  case 0x4486:
    sub_452D();
    r16[cx] = _data16get(0x40B2);
    r8[dl] = _data[0x40B4];
    sub_2CB0();
    _data16set(0x40BC, r16[ax]);
    r16[ax] = 0x0B800;
    es = r16[ax];
    if ( _data[0x40B9] != 0 ) // jnz 
      { wPos = 0x44B0; continue; }
    si = 0x3F2C;
    di = _data16get(0x40BA);
    r16[cx] = 0x501;
    sub_2D9D();
  case 0x44B0:
    sub_4557();
    if ( unknown_condition() ) // jb cf=1
      return;
    _data[0x40B9] = 0;
    _data16set(0x40BE, _data16get(0x40BE) + 2);
    r16[bx] = _data16get(0x40BE);
    r16[bx] &= 6;
    si = _data16get(r16[bx] + 0x40C0);
    if ( _data[0x40B7] != 0x0FF ) // jnz 
      { wPos = 0x44D5; continue; }
    si += 0x1E;
  case 0x44D5:
    di = _data16get(0x40BC);
    _data16set(0x40BA, di);
    bp = 0x3F2C;
    r16[cx] = 0x501;
    sub_2CCC();
    wPos = -1;
  }
}
function sub_44E7()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x571] != 0 ) // jnz 
      { wPos = 0x44F9; continue; }
    r8[al] = _data[0x57B];
    r8[al] &= 0x0F8;
    if ( r8[al] != 0x88 ) // jnz 
      { wPos = 0x44F9; continue; }
    _stc();
    return;
  case 0x44F9:
    _clc();
    wPos = -1;
  }
}
function sub_44FB()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x40B2);
    r8[dl] = 1;
    cf = (r16[ax] < _data16get(0x579)); // cf-insertion
    r16[ax] -= _data16get(0x579);
    if ( !cf ) // jnb 
      { wPos = 0x450A; continue; }
    r16[ax] = ~ r16[ax];
    r8[dl] = 0x0FF;
  case 0x450A:
    _data[0x40CA] = r8[dl];
    _data16set(0x40CC, r16[ax]);
    r8[al] = _data[0x40B4];
    r8[dl] = 1;
    cf = (r8[al] < _data16get(0x57B)); // cf-insertion
    r8[al] -= _data16get(0x57B);
    if ( !cf ) // jnb 
      { wPos = 0x4520; continue; }
    r8[al] = ~ r8[al];
    r8[dl] = 0x0FF;
  case 0x4520:
    _data[0x40CB] = r8[dl];
    r8[ah] = 0;
    r16[ax] <<= 1;
    _data16set(0x40CC, _data16get(0x40CC) + r16[ax]);
    wPos = -1;
  }
}
function sub_452D()
{
  r16[ax] = _data16get(0x40B2);
  r8[dl] = _data[0x40B4];
  si = 8;
  r16[bx] = _data16get(0x579);
  r8[dh] = _data[0x57B];
  di = 0x18;
  r16[cx] = 0x0E05;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return;
  if ( _data[0x552] != 0 ) // jnz 
    return;
  _data[0x553] = 1;
}
function sub_4557()
{
  r16[ax] = _data16get(0x40B2);
  r8[dl] = _data[0x40B4];
  si = 8;
  r16[bx] = _data16get(0x327D);
  r8[dh] = _data[0x327F];
  di = 0x10;
  r16[cx] = 0x1E05;
  sub_2E29();
  if ( !cf ) // jnb cf=0
    return;
  _data[0x40B8] = 0x0FF;
}
function sub_457A()
{
  r16[cx] = 0x90;
  r8[dl] = 0x86;
  _data16set(0x40A8, r16[cx]);
  _data[0x40AA] = r8[dl];
  sub_2CB0();
  _data16set(0x40AB, r16[ax]);
  sub_4759();
  _data[0x40AF] = 0;
  _data[0x40B1] = 0;
  _data[0x40B9] = 1;
  _data[0x40B8] = 0;
  _data16set(0x40C8, 0x0FF);
}
function sub_45AB()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x40AD) ) // jnz 
      { wPos = 0x45B6; continue; }
    return;
  case 0x45B6:
    _data16set(0x40AD, r16[dx]);
    if ( _data[0x40AA] >= 0x0A4 ) // jnb 
      return;
    sub_4786();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x45D6; continue; }
    sub_44E7();
    if ( unknown_condition() ) // jnb cf=0
      return;
    _data[0x571] = 1;
    _data[0x55B] = 0x10;
    return;
  case 0x45D6:
    sub_473E();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4649; continue; }
    if ( _data[0x40AF] != 0 ) // jnz 
      { wPos = 0x45FA; continue; }
    r8[al] = _data[0x56E];
    if ( r8[al] != 0 ) // jnz 
      { wPos = 0x45F7; continue; }
    r8[al] = r8[al] + 1;
    r16[bx] = _data16get(0x40A8);
    if ( r16[bx] > _data16get(0x579) ) // ja 
      { wPos = 0x45F7; continue; }
    r8[al] = 0x0FF;
  case 0x45F7:
    _data[0x40B0] = r8[al];
  case 0x45FA:
    _data[0x40AF] = 1;
    r16[cx] = 0x20;
  case 0x4602:
    r16[ax] = _data16get(0x579);
    r8[dl] = 1;
    if ( _data[0x40B0] != 1 ) // jnz 
      { wPos = 0x4615; continue; }
    r16[ax] -= 8;
    r8[dl] = 0x0FF;
    wPos = 0x4618;
      continue;
  case 0x4615:
    r16[ax] += 8;
  case 0x4618:
    _data16set(0x579, r16[ax]);
    _data[0x56E] = r8[dl];
    r8[al] = _data[0x57B];
    if ( _data[0x571] < 1 ) // jb 
      { wPos = 0x4639; continue; }
    if ( _data[0x571] != 1 ) // jnz 
      { wPos = 0x462F; continue; }
    r8[al] -= 3;
    wPos = 0x4631;
      continue;
  case 0x462F:
    r8[al] += 3;
  case 0x4631:
    _data[0x57B] = r8[al];
    r8[al] += 0x32;
    _data[0x57C] = r8[al];
  case 0x4639:
    _push(r16[cx]);
    sub_473E();
    r16[cx] = _pop();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4642; continue; }
    if ( --r16[cx] )
      { wPos = 0x4602; continue; }
  case 0x4642:
    sub_11E3();
    sub_1112();
    return;
  case 0x4649:
    if ( _data[0x40B1] != 0 ) // jnz 
      { wPos = 0x46A2; continue; }
    if ( _data[0x40AF] == 0 ) // jz 
      return;
    r16[ax] = _data16get(0x40A8);
    if ( _data[0x40B0] != 1 ) // jnz 
      { wPos = 0x4666; continue; }
    r16[ax] += 8;
    wPos = 0x4669;
      continue;
  case 0x4666:
    r16[ax] -= 8;
  case 0x4669:
    _data16set(0x40A8, r16[ax]);
    sub_473E();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4672; continue; }
    return;
  case 0x4672:
    r16[ax] = 0x0C00;
    r16[bx] = 0x0B54;
    sub_593B();
    _data[0x40AF] = 0;
    r16[cx] = _data16get(0x40A8);
    r8[dl] = _data[0x40AA];
    sub_2CB0();
    _data16set(0x40AB, r16[ax]);
    sub_4773();
    sub_4759();
    r16[ax] = _data16get(0x40A8);
    if ( r16[ax] < 0x78 ) // jb 
      { wPos = 0x46A2; continue; }
    if ( r16[ax] > 0x0A8 ) // ja 
      { wPos = 0x46A2; continue; }
    return;
  case 0x46A2:
    _data[0x40B1] = 1;
    if ( _data[0x1CBF] == 0 ) // jz 
      { wPos = 0x46BE; continue; }
    sub_44E7();
    if ( unknown_condition() ) // jnb cf=0
      return;
    _data[0x571] = 1;
    _data[0x55B] = 0x10;
    return;
  case 0x46BE:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x40AD) ) // jz 
      { wPos = 0x46A2; continue; }
    _data16set(0x40AD, r16[dx]);
    if ( _data[0] == 0 ) // jz 
      { wPos = 0x46EC; continue; }
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r8[al] = _data[0x40AA];
    r8[ah] = 0;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
  case 0x46EC:
    r8[dl] = _data[0x40AA];
    if ( r8[dl] >= 0x0A4 ) // jnb 
      { wPos = 0x470E; continue; }
    r8[dl] += 5;
    _data[0x40AA] = r8[dl];
    r16[cx] = _data16get(0x40A8);
    sub_2CB0();
    _data16set(0x40AB, r16[ax]);
    sub_4773();
    sub_4759();
    wPos = 0x46BE;
      continue;
  case 0x470E:
    sub_5B21();
    sub_4773();
    bp = 0x401E;
    _data16set(0x40A6, _data16get(0x40A6) -1);
    di = _data16get(0x40A6);
    si = 0x3F36;
    r16[cx] = 0x1104;
    sub_2D35();
    r16[ax] = _data16get(0x40A8);
    _data16set(0x40B2, r16[ax]);
    r8[al] = _data[0x40AA];
    _data[0x40B4] = r8[al];
    sub_44FB();
    r8[al] = _data[0x40CA];
    _data[0x40B7] = r8[al];
    wPos = -1;
  }
}
function sub_473E()
{
  r16[ax] = _data16get(0x40A8);
  r8[dl] = _data[0x40AA];
  si = 0x18;
  r16[bx] = _data16get(0x579);
  r8[dh] = _data[0x57B];
  di = si;
  r16[cx] = 0x0E10;
  sub_2E29();
}
function sub_4759()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  bp = 0x401E;
  si = 0x3FBE;
  di = _data16get(0x40AB);
  _data16set(0x40A6, di);
  r16[cx] = 0x1003;
  sub_2D35();
}
function sub_4773()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  si = 0x401E;
  di = _data16get(0x40A6);
  r16[cx] = 0x1003;
  sub_2D9D();
}
function sub_4786()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x327F] < 0x66 ) // jb 
      { wPos = 0x47A4; continue; }
    r16[ax] = _data16get(0x40A8);
    r16[ax] -= 0x14;
    if ( r16[ax] > _data16get(0x327D) ) // ja 
      { wPos = 0x47A4; continue; }
    r16[ax] += 0x30;
    if ( r16[ax] < _data16get(0x327D) ) // jb 
      { wPos = 0x47A4; continue; }
    _stc();
    return;
  case 0x47A4:
    _clc();
    wPos = -1;
  }
}
function sub_47B0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x327D);
    r8[dl] = _data[0x327F];
    si = 0x10;
    r16[bx] = _data16get(0x579);
    cf = (r16[bx] < 8); // cf-insertion
    r16[bx] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x47C5; continue; }
    r16[bx] = 0;
  case 0x47C5:
    r8[dh] = _data[0x57B];
    r8[dh] += 3;
    di = 0x28;
    r16[cx] = 0x0E1E;
    sub_2E29();
    wPos = -1;
  }
}
function sub_47D6()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x44D7);
    si = _data16get(8);
    si <<= 1;
    if ( r16[ax] > _data16get(si + 0x44DC) ) // ja 
      { wPos = 0x47ED; continue; }
    return;
  case 0x47ED:
    _data16set(0x44D7, r16[dx]);
    if ( _data[0x1CB8] != 0 ) // jnz 
      return;
    _data[0x44FC] = 0;
    r16[cx] = 0x0C;
  case 0x4800:
    r16[bx] = r16[cx];
    r16[bx]--;
    r8[bl] <<= 1;
    if ( _data16get(r16[bx] + 0x4441) == 0 ) // jz 
      { wPos = 0x487D; continue; }
    r16[ax] = _data16get(r16[bx] + 0x43F9);
    if ( r8[al] != _data16get(0x57B) ) // jnz 
      { wPos = 0x485D; continue; }
    r16[ax] = _data16get(r16[bx] + 0x43E1);
    cf = (r16[ax] < _data16get(0x579)); // cf-insertion
    r16[ax] -= _data16get(0x579);
    if ( !cf ) // jnb 
      { wPos = 0x4822; continue; }
    r16[ax] = ~ r16[ax];
  case 0x4822:
    si = _data16get(8);
    si <<= 1;
    if ( r16[ax] > _data16get(si + 0x44EC) ) // ja 
      { wPos = 0x485D; continue; }
    if ( _data16get(r16[bx] + 0x4459) < 2 ) // jb 
      { wPos = 0x484C; continue; }
    r16[ax] = _data16get(r16[bx] + 0x4411);
    _data16set(0x44DA, r16[ax]);
    sub_488D();
    sub_48A1();
    sub_3339();
    sub_1145();
    sub_2136();
    return;
  case 0x484C:
    _data16set(r16[bx] + 0x4459, _data16get(r16[bx] + 0x4459) + 1);
    if ( _data16get(r16[bx] + 0x4459) < 2 ) // jb 
      { wPos = 0x4870; continue; }
    _data[0x44FC] = _data[0x44FC] + 1;
    wPos = 0x4870;
      continue;
  case 0x485D:
    if ( _data16get(r16[bx] + 0x4459) == 0 ) // jz 
      { wPos = 0x487D; continue; }
    sub_2DFD();
    if ( r8[dl] > 0x38 ) // ja 
      { wPos = 0x4870; continue; }
    _data16set(r16[bx] + 0x4459, _data16get(r16[bx] + 0x4459) -1);
  case 0x4870:
    _push(r16[cx]);
    _push(r16[bx]);
    sub_48D7();
    r16[bx] = _pop();
    sub_4916();
    sub_48C1();
    r16[cx] = _pop();
  case 0x487D:
    if ( --r16[cx] )
      { wPos = 0x488A; continue; }
    if ( _data[0x44FC] == 0 ) // jz 
      return;
    sub_5691();
    return;
  case 0x488A:
    wPos = 0x4800;
      continue;
    wPos = -1;
  }
}
function sub_488D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x44BD] == 0 ) // jz 
      { wPos = 0x489D; continue; }
    sub_4B03();
    _data[0x44BD] = 0;
    return;
  case 0x489D:
    sub_11E3();
    wPos = -1;
  }
}
function sub_48A1()
{
  _push(ds);
  es = _pop();
  _cld();
  di = 0x0E;
  si = di;
  r16[ax] = 0x0AAAA;
  r16[cx] = 0x41;
  _rep_stosw();
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x44DA);
  r16[cx] = 0x0D05;
  sub_2D9D();
}
function sub_48C1()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x44D9] == 0 ) // jz 
      return;
    if ( _data[0x44BD] == 0 ) // jz 
      { wPos = 0x48D3; continue; }
    sub_4B1D();
    return;
  case 0x48D3:
    sub_1145();
    wPos = -1;
  }
}
function sub_48D7()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x44D9] = 0;
    r16[ax] = _data16get(r16[bx] + 0x43E1);
    r16[dx] = _data16get(r16[bx] + 0x43F9);
    r16[ax] -= 0x14;
    si = 0x28;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    r16[cx] = 0x0E06;
    di = 0x18;
    sub_2E29();
    if ( unknown_condition() ) // jnb cf=0
      return;
    _data[0x44D9] = 1;
    if ( _data[0x44BD] == 0 ) // jz 
      { wPos = 0x4912; continue; }
    sub_4B03();
    return;
  case 0x4912:
    sub_11E3();
    wPos = -1;
  }
}
function sub_4916()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(r16[bx] + 0x4411);
    si = _data16get(r16[bx] + 0x4459);
    si <<= 1;
    si += 0x4100;
    r16[ax] += 0x0A7;
    if ( _data16get(r16[bx] + 0x4429) == 0x429C ) // jz 
      { wPos = 0x4935; continue; }
    r16[ax] -= 6;
    si += 6;
  case 0x4935:
    di = r16[ax];
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x101;
    sub_2D9D();
    wPos = -1;
  }
}
function sub_4943()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1CB8] != 0 ) // jnz 
      return;
    if ( _data[0x44BE] == 0 ) // jz 
      { wPos = 0x495C; continue; }
    r8[al] = _data[0x44BE];
    _data[0x698] = r8[al];
    _data[0x699] = 0;
  case 0x495C:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x44D3) ) // jnz 
      { wPos = 0x4967; continue; }
    return;
  case 0x4967:
    _data16set(0x44D3, r16[dx]);
    if ( _data[0x584] == 0 ) // jz 
      { wPos = 0x4995; continue; }
    if ( _data[0x44BD] == 0 ) // jz 
      return;
    sub_4B03();
    sub_33A0();
    sub_1124();
    sub_3339();
    _data[0x44BD] = 0;
    _data[0x43E0] = 1;
    _data[0x44BE] = 0;
    return;
  case 0x4995:
    if ( _data[0x69A] == 0 ) // jz 
      { wPos = 0x499F; continue; }
    wPos = 0x49F9;
      continue;
  case 0x499F:
    r16[ax] = 0x0FFFF;
    _data16set(0x44C1, r16[ax]);
    _data16set(0x44BF, r16[ax]);
    r16[cx] = 0x0C;
    si = _data16get(0x579);
    r8[dl] = _data[0x57B];
    r8[dl] += 8;
  case 0x49B6:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( _data[r16[bx] + 0x44C4] < 1 ) // jb 
      { wPos = 0x49F0; continue; }
    if ( r8[dl] != _data16get(r16[bx] + 0x4499) ) // jnz 
      { wPos = 0x49F0; continue; }
    r16[ax] = si;
    r8[bl] <<= 1;
    r8[dh] = 0x0FF;
    cf = (r16[ax] < _data16get(r16[bx] + 0x4481)); // cf-insertion
    r16[ax] -= _data16get(r16[bx] + 0x4481);
    if ( !cf ) // jnb 
      { wPos = 0x49D6; continue; }
    r16[ax] = ~ r16[ax];
    r8[dh] = 1;
  case 0x49D6:
    if ( r16[ax] > _data16get(0x44BF) ) // ja 
      { wPos = 0x49F0; continue; }
    _data16set(0x44BF, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x44A5);
    _data16set(0x44D1, r16[ax]);
    r8[bl] >>= 1;
    _data16set(0x44C1, r16[bx]);
    _data[0x44C3] = r8[dh];
  case 0x49F0:
    if ( --r16[cx] )
      { wPos = 0x49B6; continue; }
    if ( _data16get(0x44C1) < 0x0C ) // jb 
      { wPos = 0x4A20; continue; }
  case 0x49F9:
    if ( _data[0x44BD] == 0 ) // jz 
      { wPos = 0x4A0B; continue; }
    sub_4B03();
    sub_1145();
    _data[0x69A] = 0x10;
  case 0x4A0B:
    _data[0x44BD] = 0;
    _data[0x43E0] = 1;
    _data[0x44D0] = 0;
    _data[0x44BE] = 0;
    return;
  case 0x4A20:
    if ( _data16get(0x44BF) < 4 ) // jb 
      { wPos = 0x4A4B; continue; }
    if ( _data16get(0x44BF) > 8 ) // ja 
      { wPos = 0x4A33; continue; }
    _data[0x572] = 4;
  case 0x4A33:
    r8[al] = _data[0x44C3];
    _data[0x698] = r8[al];
    _data[0x56E] = r8[al];
    _data[0x44BE] = r8[al];
    _data[0x699] = 0;
    _data[0x571] = 0;
    wPos = 0x49F9;
      continue;
  case 0x4A4B:
    _data[0x44BE] = 0;
    if ( _data[0x44BD] != 0 ) // jnz 
      { wPos = 0x4A5D; continue; }
    sub_11E3();
    sub_1124();
  case 0x4A5D:
    _data[0x44BD] = 1;
    r8[al] = 0;
    _data[0x44D0] += 0x30;
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4A6D; continue; }
    r8[al] = r8[al] + 1;
  case 0x4A6D:
    _data[0x44D5] = r8[al];
    r16[cx] = _data16get(0x579);
    r16[cx] &= 0x0FFC;
    r8[dl] = _data[0x57B];
    r8[dl] += 3;
    if ( _data16get(0x44D1) == 0x410C ) // jz 
      { wPos = 0x4A95; continue; }
    r16[cx] += 8;
    if ( r16[cx] < 0x127 ) // jb 
      { wPos = 0x4A9C; continue; }
    r16[cx] = 0x126;
    wPos = 0x4A9C;
      continue;
  case 0x4A95:
    cf = (r16[cx] < 8); // cf-insertion
    r16[cx] -= 8;
    if ( !cf ) // jnb 
      { wPos = 0x4A9C; continue; }
    r16[cx] = 0;
  case 0x4A9C:
    sub_2CB0();
    _data16set(0x43DC, r16[ax]);
    sub_4B03();
    if ( _data[0x44D5] == 0 ) // jz 
      { wPos = 0x4AFF; continue; }
    r16[bx] = _data16get(0x44C1);
    if ( _data[r16[bx] + 0x44C4] == 0 ) // jz 
      { wPos = 0x4AFF; continue; }
    _data[r16[bx] + 0x44C4]--;
    if ( _data[r16[bx] + 0x44C4] ) // jnz 
      { wPos = 0x4AE7; continue; }
    _push(r16[bx]);
    r16[ax] = 0x8FD;
    r16[bx] = 0x723;
    sub_593B();
    r16[bx] = _pop();
    _data[0x698] = 0;
    _data[0x44BE] = 0;
    _data[0x69A] = 0x10;
    _data[0x44D6]--;
    if ( _data[0x44D6] ) // jnz 
      { wPos = 0x4AE7; continue; }
    _data[0x553] = 1;
  case 0x4AE7:
    _push(r16[bx]);
    sub_47B0();
    r16[bx] = _pop();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4AFC; continue; }
    _push(r16[bx]);
    sub_33A0();
    r16[bx] = _pop();
    sub_4BC8();
    sub_3339();
    wPos = 0x4AFF;
      continue;
  case 0x4AFC:
    sub_4BC8();
  case 0x4AFF:
    sub_4B1D();
    wPos = -1;
  }
}
function sub_4B03()
{
  if ( _data[0x43E0] != 0 ) // jnz 
    return;
  di = _data16get(0x43DE);
  si = 0x43A0;
  r16[ax] = 0x0B800;
  es = r16[ax];
  r16[cx] = 0x0A03;
  sub_2D9D();
}
function sub_4B1D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x43E0] = 0;
    r16[ax] = 0x0B800;
    es = r16[ax];
    di = _data16get(0x43DC);
    _data16set(0x43DE, di);
    bp = 0x43A0;
    si = _data16get(0x44D1);
    if ( _data[0x44D0] < 0x80 ) // jb 
      { wPos = 0x4B40; continue; }
    si += 0x3C;
  case 0x4B40:
    r16[cx] = 0x0A03;
    sub_2D35();
    wPos = -1;
  }
}
function sub_4B47()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(ds);
    es = _pop();
    r16[ax] = 0;
    di = 0x4441;
    r16[cx] = 0x0C;
    _rep_stosw();
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[bx] = _data16get(8);
    r8[cl] = _data[r16[bx] + 0x4471];
    r8[ch] = 0;
  case 0x4B62:
    sub_2DFD();
    r8[bl] = r8[dl];
    r16[bx] &= 0x1E;
    if ( r8[bl] >= 0x18 ) // jnb 
      { wPos = 0x4B62; continue; }
    if ( _data16get(r16[bx] + 0x4441) != 0 ) // jnz 
      { wPos = 0x4B62; continue; }
    _data16set(r16[bx] + 0x4459, 0);
    _data16set(r16[bx] + 0x4441, 1);
    _push(r16[cx]);
    si = _data16get(r16[bx] + 0x4429);
    di = _data16get(r16[bx] + 0x4411);
    r16[cx] = 0x0D05;
    sub_2D9D();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x4B62; continue; }
    r16[cx] = 0x0C;
  case 0x4B98:
    r16[bx] = r16[cx];
    r16[bx]--;
    si = _data16get(8);
    r8[dl] = _data[si + 0x4479];
    _data[r16[bx] + 0x44C4] = r8[dl];
    _push(r16[cx]);
    sub_4BC8();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x4B98; continue; }
    _data[0x44D0] = 0;
    _data[0x44BD] = 0;
    _data[0x43E0] = 1;
    _data[0x44D6] = 0x0C;
    _data[0x44BE] = 0;
    wPos = -1;
  }
}
function sub_4BC8()
{
  sub_4BE8();
  di = r16[ax];
  r8[al] = _data[r16[bx] + 0x44C4];
  r8[ah] = 0;
  r8[cl] = 5;
  r16[ax] <<= r8[cl];
  r16[ax] += 0x41FC;
  si = r16[ax];
  r16[cx] = 0x802;
  r16[ax] = 0x0B800;
  es = r16[ax];
  sub_2D9D();
}
function sub_4BE8()
{
  _push(r16[bx]);
  r8[dl] = _data[r16[bx] + 0x4499];
  r8[bl] <<= 1;
  r16[cx] = _data16get(r16[bx] + 0x4481);
  sub_2CB0();
  r16[bx] = _pop();
}
function sub_4C10()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x45B8) ) // jnz 
      { wPos = 0x4C1B; continue; }
    return;
  case 0x4C1B:
    _data16set(0x45B6, _data16get(0x45B6) + 1);
    r16[bx] = _data16get(0x45B6);
    if ( r16[bx] == 1 ) // jz 
      { wPos = 0x4C38; continue; }
    if ( r16[bx] == 4 ) // jz 
      { wPos = 0x4C38; continue; }
    if ( r16[bx] < 7 ) // jb 
      { wPos = 0x4C3C; continue; }
    r16[bx] = 0;
    _data16set(0x45B6, r16[bx]);
  case 0x4C38:
    _data16set(0x45B8, r16[dx]);
  case 0x4C3C:
    sub_4FCD();
    sub_502D();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4C45; continue; }
    return;
  case 0x4C45:
    if ( _data16get(0x454F) == 0 ) // jz 
      { wPos = 0x4C8C; continue; }
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x454F);
    r16[bx] = _data16get(8);
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x45C7);
    if ( _data16get(0x45B6) != 0 ) // jnz 
      { wPos = 0x4C67; continue; }
    r16[ax] <<= 1;
  case 0x4C67:
    if ( r16[dx] < r16[ax] ) // jb 
      return;
    _data16set(0x454F, 0);
    _data[0x454E] = 1;
    r16[ax] = 0x24;
    if ( _data16get(0x579) > 0x0A0 ) // ja 
      { wPos = 0x4C84; continue; }
    r16[ax] = 0x108;
  case 0x4C84:
    _data16set(0x4548, r16[ax]);
    _data[0x454A] = 0;
  case 0x4C8C:
    sub_4DD0();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4C99; continue; }
    r16[bx] = _data16get(0x45B6);
    sub_4FBB();
    return;
  case 0x4C99:
    if ( _data[0x4553] == 0 ) // jz 
      { wPos = 0x4CB8; continue; }
    _data[0x4553]--;
    if ( _data[0x4553] ) // jnz 
      { wPos = 0x4CB5; continue; }
    r8[dl] = 1;
    if ( _data[0x454A] == 0x0FF ) // jz 
      { wPos = 0x4CB1; continue; }
    r8[dl] = 0x0FF;
  case 0x4CB1:
    _data[0x454A] = r8[dl];
  case 0x4CB5:
    wPos = 0x4D14;
      continue;
  case 0x4CB8:
    r8[al] = _data[0x454B];
    if ( r8[al] > _data16get(0x57B) ) // ja 
      { wPos = 0x4D14; continue; }
    if ( _data16get(0x45B6) != 6 ) // jnz 
      { wPos = 0x4CCF; continue; }
    if ( _data[0x57B] < 0x28 ) // jb 
      { wPos = 0x4CDC; continue; }
  case 0x4CCF:
    sub_2DFD();
    r16[bx] = _data16get(8);
    if ( r8[dl] > _data16get(r16[bx] + 0x45BF) ) // ja 
      { wPos = 0x4D14; continue; }
  case 0x4CDC:
    r8[dl] = 0;
    r16[ax] = _data16get(0x4548);
    r16[ax] &= 0x0FF8;
    r16[cx] = _data16get(0x579);
    r16[cx] &= 0x0FF8;
    if ( r16[ax] == r16[cx] ) // jz 
      { wPos = 0x4CF6; continue; }
    r8[dl] = 1;
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x4CF6; continue; }
    r8[dl] = 0x0FF;
  case 0x4CF6:
    _data[0x454A] = r8[dl];
    if ( _data[0x57B] < 0x28 ) // jb 
      { wPos = 0x4D14; continue; }
    if ( _data16get(0x45B6) != 6 ) // jnz 
      { wPos = 0x4D14; continue; }
    r8[al] = 1;
    if ( r8[dl] == 0x0FF ) // jz 
      { wPos = 0x4D11; continue; }
    r8[al] = 0x0FF;
  case 0x4D11:
    _data[0x454A] = r8[al];
  case 0x4D14:
    _data16set(0x45BC, 8);
    if ( _data[0x4553] == 0 ) // jz 
      { wPos = 0x4D27; continue; }
    _data16set(0x45BC, 4);
  case 0x4D27:
    r16[ax] = _data16get(0x4548);
    if ( _data[0x454A] >= 1 ) // jnb 
      { wPos = 0x4D46; continue; }
    sub_2DFD();
    if ( r8[dl] > 0x10 ) // ja 
      { wPos = 0x4DA1; continue; }
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x4D40; continue; }
    r8[dl] = 0x0FF;
  case 0x4D40:
    _data[0x454A] = r8[dl];
    wPos = 0x4DA1;
      continue;
  case 0x4D46:
    if ( unknown_condition() ) // jnz 
      { wPos = 0x4D60; continue; }
    r16[ax] += _data16get(0x45BC);
    if ( r16[ax] < 0x10B ) // jb 
      { wPos = 0x4D78; continue; }
    r16[ax] = 0x10A;
    _data[0x454A] = 0x0FF;
    _data[0x4553] = 0;
    wPos = 0x4D78;
      continue;
  case 0x4D60:
    cf = (r16[ax] < _data16get(0x45BC)); // cf-insertion
    r16[ax] -= _data16get(0x45BC);
    if ( cf ) // jb 
      { wPos = 0x4D6B; continue; }
    if ( r16[ax] > 0x24 ) // ja 
      { wPos = 0x4D78; continue; }
  case 0x4D6B:
    r16[ax] = 0x25;
    _data[0x454A] = 1;
    _data[0x4553] = 0;
  case 0x4D78:
    _data16set(0x4548, r16[ax]);
    _data16set(0x4551, _data16get(0x4551) + 2);
    if ( _data16get(0x4551) < 0x0C ) // jb 
      { wPos = 0x4D8D; continue; }
    _data16set(0x4551, 0);
  case 0x4D8D:
    if ( _data[0x4553] != 0 ) // jnz 
      { wPos = 0x4DA1; continue; }
    sub_2DFD();
    if ( r8[dl] > 8 ) // ja 
      { wPos = 0x4DA1; continue; }
    _data[0x454A] = 0;
  case 0x4DA1:
    r16[cx] = _data16get(0x4548);
    r8[dl] = _data[0x454B];
    sub_2CB0();
    _data16set(0x45BA, r16[ax]);
    sub_502D();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x4DB5; continue; }
    return;
  case 0x4DB5:
    sub_4DD0();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x4DC8; continue; }
    sub_4F4A();
    sub_4F10();
    _data[0x45BE] = 0;
    sub_4E75();
  case 0x4DC8:
    r16[bx] = _data16get(0x45B6);
    sub_4FBB();
    wPos = -1;
  }
}
function sub_4DD0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(0x579);
    r8[dl] = _data[0x57B];
    si = 0x18;
    di = si;
    r16[bx] = _data16get(0x4548);
    r8[dh] = _data[0x454B];
    r16[cx] = 0x0C0E;
    sub_2E29();
    if ( unknown_condition() ) // jnb cf=0
      return;
    if ( _data16get(0x45B6) != 6 ) // jnz 
      { wPos = 0x4E00; continue; }
    _data[0x553] = 1;
    sub_11E3();
    sub_4F4A();
    _stc();
    return;
  case 0x4E00:
    sub_11E3();
    sub_4F4A();
    sub_1145();
    _data[0x55B] = 4;
    _data[0x571] = 1;
    _data[0x576] = 4;
    _data[0x578] = 8;
    _data[0x4553] = 4;
    r8[dl] = 1;
    r16[ax] = _data16get(0x4548);
    if ( r16[ax] > _data16get(0x579) ) // ja 
      { wPos = 0x4E2F; continue; }
    r8[dl] = 0x0FF;
  case 0x4E2F:
    _data[0x454A] = r8[dl];
    r16[ax] = 0x0CE4;
    r16[bx] = 0x123B;
    sub_593B();
    _stc();
    wPos = -1;
  }
}
function sub_4E3E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x45BE] = 1;
    r16[ax] = _data16get(0x45B6);
    _push(r16[ax]);
    _data16set(0x45B6, 0);
  case 0x4E4D:
    r16[bx] = _data16get(0x45B6);
    sub_4FCD();
    if ( _data16get(0x454F) != 0 ) // jnz 
      { wPos = 0x4E65; continue; }
    sub_4E75();
    r16[bx] = _data16get(0x45B6);
    sub_4FBB();
  case 0x4E65:
    _data16set(0x45B6, _data16get(0x45B6) + 1);
    if ( _data16get(0x45B6) < 7 ) // jb 
      { wPos = 0x4E4D; continue; }
    r16[ax] = _pop();
    _data16set(0x45B6, r16[ax]);
    wPos = -1;
  }
}
function sub_4E75()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 8;
  case 0x4E78:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( _data[r16[bx] + 0x2B72] == 0 ) // jz 
      { wPos = 0x4EA3; continue; }
    _push(r16[cx]);
    r8[dl] = _data[r16[bx] + 0x2B6A];
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x2B5A);
    si = 0x18;
    di = si;
    r16[bx] = _data16get(0x4548);
    r8[dh] = _data[0x454B];
    r16[cx] = 0x0C0F;
    sub_2E29();
    r16[cx] = _pop();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x4EA6; continue; }
  case 0x4EA3:
    if ( --r16[cx] )
      { wPos = 0x4E78; continue; }
    return;
  case 0x4EA6:
    _push(r16[cx]);
    if ( _data[0x45BE] != 0 ) // jnz 
      { wPos = 0x4EBB; continue; }
    sub_11E3();
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x4EBB; continue; }
    sub_622B();
  case 0x4EBB:
    sub_4F4A();
    r16[cx] = _pop();
    r16[bx] = r16[cx];
    r16[bx]--;
    _data[r16[bx] + 0x2B72] = 0;
    r8[dl] = _data[r16[bx] + 0x2B6A];
    r8[bl] <<= 1;
    r16[cx] = _data16get(r16[bx] + 0x2B5A);
    sub_2CB0();
    di = r16[ax];
    si = 0x2B7A;
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[cx] = 0x0F03;
    sub_2D9D();
    if ( _data[0x45BE] != 0 ) // jnz 
      { wPos = 0x4EF8; continue; }
    if ( _data[0x70F2] == 0 ) // jz 
      { wPos = 0x4EF5; continue; }
    sub_61FA();
  case 0x4EF5:
    sub_1145();
  case 0x4EF8:
    r16[dx] = 0;
    if ( _data16get(0x45B6) == 6 ) // jz 
      { wPos = 0x4F0B; continue; }
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != 0 ) // jnz 
      { wPos = 0x4F0B; continue; }
    r16[dx]--;
  case 0x4F0B:
    _data16set(0x454F, r16[dx]);
    wPos = -1;
  }
}
function sub_4F10()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x454E] = 0;
    si = 0x4500;
    if ( _data[0x454A] == 0 ) // jz 
      { wPos = 0x4F3E; continue; }
    r16[bx] = _data16get(0x4551);
    if ( _data[0x4553] == 0 ) // jz 
      { wPos = 0x4F30; continue; }
    r8[bl] &= 2;
    r8[bl] += 0x0C;
  case 0x4F30:
    if ( _data[0x454A] != 0x0FF ) // jnz 
      { wPos = 0x4F3A; continue; }
    r16[bx] += 0x10;
  case 0x4F3A:
    si = _data16get(r16[bx] + 0x4A60);
  case 0x4F3E:
    di = _data16get(0x45BA);
    _data16set(0x454C, di);
    sub_4FDF();
    wPos = -1;
  }
}
function sub_4F4A()
{
  if ( _data[0x454E] != 0 ) // jnz 
    return;
  di = _data16get(0x454C);
  sub_5008();
}
function sub_4F59()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x45B6, 0);
  case 0x4F5F:
    sub_2DFD();
    r16[dx] &= 0x7F;
    r16[dx] += 0x60;
    _data16set(0x4548, r16[dx]);
    _data[0x454A] = 0;
    _data[0x454E] = 1;
    _data16set(0x4551, 0);
    _data[0x4553] = 0;
    r16[dx] = 0;
    if ( _data16get(0x45B6) != 0 ) // jnz 
      { wPos = 0x4F95; continue; }
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != 0 ) // jnz 
      { wPos = 0x4F95; continue; }
    r16[dx]--;
  case 0x4F95:
    _data16set(0x454F, r16[dx]);
    r16[bx] = _data16get(0x45B6);
    r8[al] = _data[r16[bx] + 0x2BD4];
    r8[al] += 3;
    _data[0x454B] = r8[al];
    sub_4FBB();
    _data16set(0x45B6, _data16get(0x45B6) + 1);
    if ( _data16get(0x45B6) < 7 ) // jb 
      { wPos = 0x4F5F; continue; }
    _data16set(0x45B6, 0);
    wPos = -1;
  }
}
function sub_4FBB()
{
  _push(ds);
  es = _pop();
  r8[bl] <<= 1;
  _cld();
  di = _data16get(r16[bx] + 0x45A8);
  si = 0x4548;
  r16[cx] = 0x0C;
  _rep_movsb();
}
function sub_4FCD()
{
  _push(ds);
  es = _pop();
  r8[bl] <<= 1;
  _cld();
  si = _data16get(r16[bx] + 0x45A8);
  di = 0x4548;
  r16[cx] = 0x0C;
  _rep_movsb();
}
function sub_4FDF()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _cld();
    r8[dh] = 0x0C;
  case 0x4FE7:
    r16[cx] = 3;
  case 0x4FEA:
    r16[bx] = _data16get(es*16+di);
    _lodsw();
    r16[ax] |= r16[bx];
    _stosw();
    if ( --r16[cx] )
      { wPos = 0x4FEA; continue; }
    di -= 6;
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x5003; continue; }
    di += 0x50;
  case 0x5003:
    r8[dh]--;
    if ( r8[dh] ) // jnz 
      { wPos = 0x4FE7; continue; }
    wPos = -1;
  }
}
function sub_5008()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _cld();
    r8[dh] = 0x0C;
    r16[ax] = 0x5555;
  case 0x5013:
    r16[cx] = 3;
    _rep_stosw();
    di -= 6;
    di = di ^ 0x2000;
    if ( di & 0x2000 ) // jnz 
      { wPos = 0x5028; continue; }
    di += 0x50;
  case 0x5028:
    r8[dh]--;
    if ( r8[dh] ) // jnz 
      { wPos = 0x5013; continue; }
    wPos = -1;
  }
}
function sub_502D()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x70F2] != 0 ) // jnz 
      { wPos = 0x5036; continue; }
    _clc();
    return;
  case 0x5036:
    r16[ax] = _data16get(0x70F3);
    r8[dl] = _data[0x70F5];
    si = 0x10;
    r16[bx] = _data16get(0x4548);
    r8[dh] = _data[0x454B];
    di = 0x18;
    r16[cx] = 0x0C08;
    sub_2E29();
    wPos = -1;
  }
}
function sub_5060()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[ax] = _data16get(0x579);
    if ( r16[ax] < 0x117 ) // jb 
      { wPos = 0x5070; continue; }
    r16[ax] = 0x116;
  case 0x5070:
    cf = (r16[ax] < 0x10); // cf-insertion
    r16[ax] -= 0x10;
    if ( !cf ) // jnb 
      { wPos = 0x5077; continue; }
    r16[ax] = 0;
  case 0x5077:
    r16[ax] &= 0x0FF0;
    _data16set(0x579, r16[ax]);
    _data[0x57B] = 0x14;
    cf = (r16[ax] < 0x80); // cf-insertion
    r16[ax] -= 0x80;
    if ( !cf ) // jnb 
      { wPos = 0x5089; continue; }
    r16[ax] = ~ r16[ax];
  case 0x5089:
    r8[cl] = 3;
    r16[ax] >>= r8[cl];
    if ( r16[ax] <= 0x0D ) // jbe 
      { wPos = 0x5095; continue; }
    r16[ax] = 0x0D;
  case 0x5095:
    r16[ax] += 2;
    _data16set(0x4D6A, r16[ax]);
    _data16set(0x4DD6, 0x0A);
  case 0x50A1:
    if ( _data16get(0x4DD6) == 0x0A ) // jz 
      { wPos = 0x50AB; continue; }
    sub_5B63();
  case 0x50AB:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x4A80, r16[dx]);
    r16[ax] = _data16get(0x579);
    r16[cx] = r16[ax];
    r16[cx] &= 0x0FF0;
    if ( r16[cx] != 0x80 ) // jnz 
      { wPos = 0x50C6; continue; }
    r16[ax] = r16[cx];
    wPos = 0x50D2;
      continue;
  case 0x50C6:
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x50CE; continue; }
    r16[ax] -= _data16get(0x4D6A);
    wPos = 0x50D2;
      continue;
  case 0x50CE:
    r16[ax] += _data16get(0x4D6A);
  case 0x50D2:
    _data16set(0x579, r16[ax]);
    if ( _data[0x57B] < 0x54 ) // jb 
      { wPos = 0x50DD; continue; }
    return;
  case 0x50DD:
    _data[0x57B] += 8;
    r16[cx] = _data16get(0x579);
    r16[cx] += 4;
    r8[dl] = _data[0x57B];
    sub_2CB0();
    di = r16[ax];
    _data16set(0x4DD8, di);
    si = 0x4B8A;
    bp = 0x0E;
    r16[cx] = 0x2007;
    sub_2CCC();
    di = _data16get(0x4DD8);
    di += 0x0F3;
    si = 0x4A82;
    r16[cx] = 0x0D04;
    sub_2D9D();
    if ( _data16get(0x4DD6) != 0x0A ) // jnz 
      { wPos = 0x5120; continue; }
    sub_572E();
    sub_5B54();
  case 0x5120:
    sub_5B63();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x4A80);
    if ( r16[dx] < _data16get(0x4DD6) ) // jb 
      { wPos = 0x5120; continue; }
    if ( _data16get(0x4DD6) != 0x0A ) // jnz 
      { wPos = 0x5141; continue; }
    sub_38B0();
    r16[bx] = 0;
    r8[ah] = 0x0B;
    _int(0x10);
  case 0x5141:
    _data16set(0x4DD6, 2);
    wPos = 0x50A1;
      continue;
    wPos = -1;
  }
}
function sub_514A()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 3;
  case 0x514D:
    r16[bx] = 3;
    r16[bx] -= r16[cx];
    r16[bx] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x4DA4);
    _data16set(0x4D6A, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4DAA);
    _data16set(0x4D6C, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4D98);
    _data16set(0x4DCC, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4D9E);
    _data16set(0x4DCE, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4DB0);
    _data16set(0x4DD0, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4DB6);
    _data16set(0x4DD2, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4DBC);
    _data16set(0x4DD4, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4D92);
    _data16set(0x4DCA, r16[ax]);
    r16[ax] = _data16get(r16[bx] + 0x4DC2);
    _data16set(0x4DC8, r16[ax]);
    _push(r16[cx]);
    sub_519B();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x514D; continue; }
    wPos = -1;
  }
}
function sub_519B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 8;
    _data[0x4D91] = 1;
  case 0x51A3:
    _push(r16[cx]);
    sub_5B63();
    r16[cx] = _pop();
    r16[bx] = r16[cx];
    r16[bx]--;
    r16[bx] <<= 1;
    r16[ax] = _data16get(0x4DCC);
    _data16set(r16[bx] + 0x4D4A, r16[ax]);
    r16[ax] = _data16get(0x4DCE);
    _data16set(r16[bx] + 0x4D5A, r16[ax]);
    if ( --r16[cx] )
      { wPos = 0x51A3; continue; }
    r16[ax] = 0x0B800;
    es = r16[ax];
    _data[0x4D6E] = 0;
  case 0x51C7:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x4A80, r16[dx]);
    r16[cx] = 8;
  case 0x51D2:
    _push(r16[cx]);
    sub_5B63();
    r16[cx] = _pop();
    r16[bx] = r16[cx];
    r16[bx]--;
    r16[bx] <<= 1;
    _push(r16[cx]);
    _push(r16[bx]);
    if ( _data[0x4D91] == 0 ) // jz 
      { wPos = 0x51EA; continue; }
    if ( r16[cx] != 8 ) // jnz 
      { wPos = 0x5205; continue; }
  case 0x51EA:
    r16[cx] = _data16get(r16[bx] + 0x4D4A);
    r16[dx] = _data16get(r16[bx] + 0x4D5A);
    sub_2CB0();
    di = r16[ax];
    si = _data16get(0x4DCA);
    bp = 0x0E;
    r16[cx] = _data16get(0x4DD4);
    sub_2CCC();
  case 0x5205:
    r16[bx] = _pop();
    r16[cx] = _pop();
    sub_522A();
    if ( --r16[cx] )
      { wPos = 0x51D2; continue; }
  case 0x520C:
    sub_5B63();
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x4A80);
    if ( r16[dx] < _data16get(0x4DC8) ) // jb 
      { wPos = 0x520C; continue; }
    _data[0x4D91] = 0;
    if ( _data[0x4D6E] == 0 ) // jz 
      { wPos = 0x51C7; continue; }
    wPos = -1;
  }
}
function sub_522A()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = _data16get(r16[bx] + 0x4D4A);
    if ( _data16get(r16[bx] + 0x4D6F) < 1 ) // jb 
      { wPos = 0x525A; continue; }
    if ( _data16get(r16[bx] + 0x4D6F) != 1 ) // jnz 
      { wPos = 0x524A; continue; }
    r16[ax] += _data16get(0x4D6A);
    if ( r16[ax] <= _data16get(0x4DD0) ) // jbe 
      { wPos = 0x5256; continue; }
    r16[ax] = _data16get(0x4DD0);
    _data[0x4D6E] = _data[0x4D6E] + 1;
    wPos = 0x5256;
      continue;
  case 0x524A:
    cf = (r16[ax] < _data16get(0x4D6A)); // cf-insertion
    r16[ax] -= _data16get(0x4D6A);
    if ( !cf ) // jnb 
      { wPos = 0x5256; continue; }
    r16[ax] = 0;
    _data[0x4D6E] = _data[0x4D6E] + 1;
  case 0x5256:
    _data16set(r16[bx] + 0x4D4A, r16[ax]);
  case 0x525A:
    r16[ax] = _data16get(r16[bx] + 0x4D5A);
    if ( _data16get(r16[bx] + 0x4D7F) < 1 ) // jb 
      return;
    if ( _data16get(r16[bx] + 0x4D7F) != 1 ) // jnz 
      { wPos = 0x527A; continue; }
    r16[ax] += _data16get(0x4D6C);
    if ( r16[ax] <= _data16get(0x4DD2) ) // jbe 
      { wPos = 0x5286; continue; }
    r16[ax] = _data16get(0x4DD2);
    _data[0x4D6E] = _data[0x4D6E] + 1;
    wPos = 0x5286;
      continue;
  case 0x527A:
    cf = (r16[ax] < _data16get(0x4D6C)); // cf-insertion
    r16[ax] -= _data16get(0x4D6C);
    if ( !cf ) // jnb 
      { wPos = 0x5286; continue; }
    r16[ax] = 0;
    _data[0x4D6E] = _data[0x4D6E] + 1;
  case 0x5286:
    _data16set(r16[bx] + 0x4D5A, r16[ax]);
    wPos = -1;
  }
}
function sub_528B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    sub_5B54();
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x529C; continue; }
    r8[ah] = 0x0B;
    r16[bx] = 0x101;
    _int(0x10);
  case 0x529C:
    sub_5060();
    sub_514A();
    sub_5BBF();
    if ( _data[0x1F80] >= 9 ) // jnb 
      { wPos = 0x52B0; continue; }
    _data[0x1F80] = _data[0x1F80] + 1;
  case 0x52B0:
    if ( _data16get(8) >= 7 ) // jnb 
      { wPos = 0x52BB; continue; }
    _data16set(8, _data16get(8) + 1);
  case 0x52BB:
    _data16set(0x414, 0);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x412, r16[dx]);
    sub_5B21();
    wPos = -1;
  }
}
function sub_52D0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x52C4) ) // jz 
      return;
    _data16set(0x52C4, r16[dx]);
    r16[bx] = _data16get(0x52C6);
    _data16set(0x52C6, _data16get(0x52C6) + 2);
    r16[ax] = _data16get(r16[bx] + 0x52CA);
    if ( r16[ax] != _data16get(0x52C8) ) // jnz 
      { wPos = 0x52FC; continue; }
    sub_5B21();
    return;
  case 0x52FC:
    _data16set(0x52C8, r16[ax]);
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x52C8);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5313()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(8) < 2 ) // jb 
      return;
    _data16set(0x5016, 0);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x52C0, r16[dx]);
    _data16set(0x52C2, r16[dx]);
    _data16set(0x52C4, r16[dx]);
    _data16set(0x52C6, 0);
    _data16set(0x52C8, 0);
  case 0x533C:
    sub_5368();
    _data16set(0x5016, _data16get(0x5016) ^ 2);
  case 0x5345:
    sub_52D0();
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x52C0);
    if ( r16[ax] < 5 ) // jb 
      { wPos = 0x5345; continue; }
    _data16set(0x52C0, r16[dx]);
    r16[dx] -= _data16get(0x52C2);
    if ( r16[dx] < 0x28 ) // jb 
      { wPos = 0x533C; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_5368()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[bx] = _data16get(8);
    r16[bx] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x52AE);
    _data16set(0x5010, r16[ax]);
  case 0x537A:
    r16[bx] = _data16get(0x5010);
    di = _data16get(r16[bx]);
    if ( di != 0 ) // jnz 
      { wPos = 0x5386; continue; }
    return;
  case 0x5386:
    r16[bx] = _data16get(r16[bx] + 2);
    r16[bx] = r16[bx] ^ _data16get(0x5016);
    r16[bx] &= 2;
    si = _data16get(r16[bx] + 0x5012);
    r16[cx] = 0x2304;
    sub_2D9D();
    sub_52D0();
    _data16set(0x5010, _data16get(0x5010) + 4);
    wPos = 0x537A;
      continue;
    wPos = -1;
  }
}
function sub_53B0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x5322) ) // jz 
      return;
    _data16set(0x5322, r16[dx]);
    r16[bx] = _data16get(0x5320);
    r8[bl] = _data[r16[bx] + 0x538C];
    if ( r8[bl] == 0x66 ) // jz 
      { wPos = 0x53DD; continue; }
    r8[bh] = 0;
    _data16set(0x5320, _data16get(0x5320) + 1);
    if ( r16[bx] != 0 ) // jnz 
      { wPos = 0x53E1; continue; }
  case 0x53DD:
    sub_5B21();
    return;
  case 0x53E1:
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(r16[bx] + 0x5324);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5400()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[bx] = _data16get(8);
    r16[bx] &= 7;
    r16[bx] <<= 1;
    r16[ax] = r16[bx];
    r16[bx] = _data16get(r16[bx] + 0x5908);
    r8[cl] = 3;
    r16[ax] <<= r8[cl];
    _data16set(0x5918, r16[ax]);
  case 0x541C:
    di = _data16get(r16[bx]);
    if ( di == 0x0FFFF ) // jz 
      return;
    sub_2DFD();
    r16[dx] &= 0x0E;
    r16[dx] += _data16get(0x5918);
    si = r16[dx];
    si = _data16get(si + 0x5888);
    r16[cx] = _data16get(si + 0x5858);
    si = _data16get(si + 0x584C);
    _push(r16[bx]);
    sub_2D9D();
    r16[bx] = _pop();
    r16[bx] += 2;
    wPos = 0x541C;
      continue;
    wPos = -1;
  }
}
function sub_5450()
{
  _data[0x5B0F] = 0x0C;
  _data16set(0x5B0C, 1);
  _data16set(0x5B12, 0x1FF);
  _data16set(0x5B0A, 0x0F);
  _data[0x5B0E] = 1;
}
function sub_546D(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return -1;
    if ( _data[0x1CB8] == 0 ) // jz 
      { wPos = 0x54F8; continue; }
    r8[ah] = 0;
    _int(0x1A);
    if ( _data[0x5B0F] != 0 ) // jnz 
      { wPos = 0x54A6; continue; }
    if ( r16[dx] == _data16get(0x5B10) ) // jz 
      return -1;
    _data16set(0x5B10, r16[dx]);
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x5B12);
    r16[ax] &= 0x1FF;
    r16[ax] += 0x0C8;
    sub_5889();
    _data16set(0x5B12, _data16get(0x5B12) - 0x4B);
    return -1;
  case 0x54A6:
    if ( r16[dx] == _data16get(0x5B10) ) // jz 
      { wPos = 0x54B4; continue; }
    _data16set(0x5B10, r16[dx]);
    _data[0x5B0F]--;
  case 0x54B4:
    _data[0x5B0E]--;
    if ( _data[0x5B0E] ) // jnz 
      return -1;
    r8[al] = 1;
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x54C5; continue; }
    r8[al] <<= 1;
  case 0x54C5:
    _data[0x5B0E] = r8[al];
    sub_2DFD();
    if ( r8[dl] > 4 ) // ja 
      { wPos = 0x54D4; continue; }
    _data16set(0x5B0C, _data16get(0x5B0C) + 1);
  case 0x54D4:
    if ( !(_data16get(0x5B0C) & 1) ) // jz 
      { wPos = 0x54E1; continue; }
    _data16set(0x5B0A, _data16get(0x5B0A) + 7);
  case 0x54E1:
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    sub_2DFD();
    r16[ax] = r16[dx];
    r16[ax] &= _data16get(0x5B0A);
    r16[ax] &= 0x1FF;
    r16[ax] += 0x190;
    sub_5889();
    return -1;
  case 0x54F8:
    r8[ah] = 0;
    _int(0x1A);
    if ( _data[0x5920] == 0 ) // jz 
      { wPos = 0x5522; continue; }
    if ( r16[dx] == _data16get(0x5921) ) // jz 
      return -1;
    _data16set(0x5921, r16[dx]);
    _data[0x5920]--;
    if ( !_data[0x5920] ) // jz 
      { wPos = 0x551E; continue; }
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x5923);
    sub_5889();
    return -1;
  case 0x551E:
    sub_5B21();
    return -1;
  case 0x5522:
    if ( r16[dx] == _data16get(0x5925) ) // jz 
      return -1;
    si = 3;
    r8[al] = _data[0x1CBF];
    r8[al] |= _data16get(0x5B07);
    if ( r8[al] ) // jnz 
      { wPos = 0x5549; continue; }
    si = 1;
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0x5549; continue; }
    si--;
    if ( _data[0x1673] == 0 ) // jz 
      { wPos = 0x5549; continue; }
    si = 2;
  case 0x5549:
    di = si;
    di <<= 1;
    r8[al] = _data[0x584];
    r8[al] |= _data16get(0x5B07);
    if ( r8[al] ) // jnz 
      { wPos = 0x5563; continue; }
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x5925);
    if ( r16[ax] >= _data16get(di + 0x59F2) ) // jnb 
      { wPos = 0x5563; continue; }
    return -1;
  case 0x5563:
    _data16set(0x5925, r16[dx]);
    if ( _data[0x1CBF] != 0 ) // jnz 
      { wPos = 0x5579; continue; }
    if ( _data[0x5B07] == 0 ) // jz 
      { wPos = 0x559E; continue; }
    _data[0x5B07]--;
  case 0x5579:
    _data16set(0x592E, 0x1200);
    r16[bx] = _data16get(0x59BA);
    if ( r16[bx] < 6 ) // jb 
      { wPos = 0x558E; continue; }
    r16[bx] = 0;
    _data16set(0x59BA, r16[bx]);
  case 0x558E:
    _data16set(0x59BA, _data16get(0x59BA) + 2);
    r16[ax] = _data16get(r16[bx] + 0x5A44);
    _data16set(0x592A, r16[ax]);

    sub_5B28_pc = 0;
  case 0xF016:
    sub_5B28_pc = sub_5B28(sub_5B28_pc);
    if (sub_5B28_pc != -1)
      return 0xF016;

    return -1;
  case 0x559E:
    if ( si != 2 ) // jnz 
      { wPos = 0x55BB; continue; }
    r8[al] = _data[0x1673];
    r8[ah] = 0;
    r8[cl] = 4;
    r16[ax] <<= r8[cl];
    r16[ax] += 0x200;
    _data16set(0x592A, r16[ax]);
    _data16set(0x592E, 0x1800);
    wPos = 0x568D;
      continue;
  case 0x55BB:
    r16[ax] = _data16get(di + 0x5A02);
    _data16set(0x592E, r16[ax]);
    cf = _data[0x5927] & 1;
    _data[0x5927] >>= 1;
    if ( cf ) // jnb cf=0
      { wPos = 0x5623; continue; }
    _data16set(0x592E, 0x1000);
    _data[0x5927] = 0x80;
    _data[0x5928] = _data[0x5928] + 1;
    r8[al] = _data[0x5928];
    r8[al] &= _data16get(si + 0x59FA);
    if ( r8[al] ) // jnz 
      { wPos = 0x5616; continue; }
    r8[dl] = _data[si + 0x5A0A];
    _data16set(0x5929, _data16get(0x5929) + r8[dl]);
    sub_2DFD();
    if ( r8[dl] > _data16get(si + 0x5A0C) ) // ja 
      { wPos = 0x55F8; continue; }
    r8[dl] &= 7;
    _data[0x592D] = r8[dl];
  case 0x55F8:
    sub_2DFD();
    r16[dx] &= 0x0FF;
    r16[dx] <<= 1;
    r8[cl] = 1;
    if ( !(r8[dl] & 2) ) // jz 
      { wPos = 0x560E; continue; }
    r8[cl] = 0x0FF;
    r16[dx] += 0x300;
  case 0x560E:
    _data16set(0x592A, r16[dx]);
    _data[0x592C] = r8[cl];
  case 0x5616:
    r8[ah] = _data[0x5929];
    r8[ah] &= _data16get(si + 0x59FC);
    r8[al] |= r8[ah];
    _data[0x5928] = r8[al];
  case 0x5623:
    if ( _data[0x592C] == 0x0FF ) // jz 
      { wPos = 0x5640; continue; }
    _data16set(0x5A54, _data16get(0x5A54) + 2);
    r16[bx] = _data16get(0x5A54);
    r16[bx] &= 0x0E;
    r16[ax] = _data16get(r16[bx] + 0x5A44);
    _data16set(0x592A, r16[ax]);
    wPos = 0x5653;
      continue;
  case 0x5640:
    if ( _data16get(0x592A) > 0x0C8 ) // ja 
      { wPos = 0x564E; continue; }
    _data16set(0x592A, 0x500);
  case 0x564E:
    _data16set(0x592A, _data16get(0x592A) - 0x19);
  case 0x5653:
    if ( _data[0x584] == 0 ) // jz 
      { wPos = 0x5667; continue; }
    _data16set(0x592E, 0x2000);
    _data[0x592C] = 0x0FF;
    if ( unknown_condition() ) // jnz 
      { wPos = 0x568D; continue; }
  case 0x5667:
    r8[bl] = _data[0x5928];
    r8[bh] = 0;
    r16[bx] += _data16get(di + 0x59FE);
    r8[al] = _data[r16[bx] + 0x59C2];
    r8[al] &= _data16get(0x5927);
    if ( r8[al] ) // jnz 
      { wPos = 0x568D; continue; }
    if ( _data[0x592D] == 0 ) // jz 
      return -1;
    _data[0x592D]--;
    r16[ax] = _data16get(di + 0x5A06);
    _data16set(0x592E, r16[ax]);
  case 0x568D:

    sub_5B28_pc = 0;
  case 0xF017:
    sub_5B28_pc = sub_5B28(sub_5B28_pc);
    if (sub_5B28_pc != -1)
      return 0xF017;
    wPos = -1;
  }
  return wPos;
}
function sub_5691()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    sub_5B21();
    r8[ah] = 0x0B;
    r16[bx] = 4;
    _int(0x10);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x5AE2, r16[dx]);
    _data16set(0x5AE4, 0);
    r8[al] = 2;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x56B4; continue; }
    r8[al] >>= 1;
  case 0x56B4:
    _data[0x5B06] = r8[al];
  case 0x56B7:
    if ( _data[0] == 0 ) // jz 
      { wPos = 0x56D8; continue; }
    _data16set(0x5AE4, _data16get(0x5AE4) + 1);
    r16[bx] = _data16get(0x5AE4);
    r8[cl] = _data[0x5B06];
    r16[bx] >>= r8[cl];
    r16[bx] &= 0x1F;
    r8[al] =_in(0x61);
    r8[al] = r8[al] ^ _data16get(r16[bx] + 0x5AE6);
    _out(0x61, r8[al]);
  case 0x56D8:
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x5AE2);
    if ( r16[dx] < 2 ) // jb 
      { wPos = 0x56B7; continue; }
    r8[ah] = 0x0B;
    r16[bx] = 0;
    _int(0x10);
    _data[0x5B07] = 0x0C;
    sub_5B21();
    wPos = -1;
  }
}
function sub_56F4()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x200;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x5700; continue; }
    r16[ax] <<= 1;
  case 0x5700:
    _data16set(0x5AD0, r16[ax]);
    wPos = -1;
  }
}
function sub_5704()
{
  _data16set(0x5AD0, _data16get(0x5AD0) + 1);
  r16[bx] = _data16get(0x5AD0);
  r16[dx] = r16[bx];
  r8[cl] = 9;
  r16[dx] >>= r8[cl];
  r8[cl] = r8[dl];
  r8[cl] &= 0x0F;
  r16[bx] >>= r8[cl];
  r16[bx] &= 0x0F;
  r8[dl] = _data[r16[bx] + 0x5AD2];
  r8[dl] &= _data16get(0);
  r8[al] =_in(0x61);
  r8[al] &= 0x0FC;
  r8[al] |= r8[dl];
  _out(0x61, r8[al]);
}
function sub_572E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x5ACB, 0x1F4);
  case 0x5734:
    sub_576E();
    _data16set(0x5ACB, _data16get(0x5ACB) - 0x1E);
    if ( _data16get(0x5ACB) > 0x0C8 ) // ja 
      { wPos = 0x5734; continue; }
    _data16set(0x5ACB, 0x1F4);
  case 0x574A:
    sub_576E();
    _data16set(0x5ACB, _data16get(0x5ACB) - 0x14);
    if ( _data16get(0x5ACB) > 0x12C ) // ja 
      { wPos = 0x574A; continue; }
  case 0x575A:
    sub_576E();
    _data16set(0x5ACB, _data16get(0x5ACB) + 0x1E);
    if ( _data16get(0x5ACB) < 0x320 ) // jb 
      { wPos = 0x575A; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_576E()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[cx] = 0x1000;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x577A; continue; }
    r16[cx] >>= 1;
  case 0x577A:
    if ( --r16[cx] )
      { wPos = 0x577A; continue; }
    if ( _data[0] == 0 ) // jz 
      return;
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x5ACB);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5797()
{
  sub_5B21();
  _data[0x5ACF] = 0;
  _data16set(0x5ACD, 8);
}
function sub_57A6()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data[0x5ACF] = _data[0x5ACF] + 1;
    r8[dl] = 0;
    r8[al] = _data[0x5ACF];
    r8[al] &= 0x3F;
    if ( r8[al] ) // jnz 
      { wPos = 0x57B7; continue; }
    _data16set(0x5ACD, _data16get(0x5ACD) + 1);
  case 0x57B7:
    r16[bx] = _data16get(0x5ACD);
    r8[cl] = 2;
    r16[bx] >>= r8[cl];
    r8[bl] &= 0x1F;
    if ( r8[al] < r8[bl] ) // jb 
      { wPos = 0x57C8; continue; }
    r8[dl] = 2;
  case 0x57C8:
    r8[dl] &= _data16get(0);
    r8[al] =_in(0x61);
    r8[al] &= 0x0FD;
    r8[al] |= r8[dl];
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_57D5()
{
  _data16set(0x5A85, 0);
  r8[ah] = 0;
  _int(0x1A);
  _data16set(0x5A83, r16[dx]);
}
function sub_57E4()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x5A83);
    if ( r16[ax] < 2 ) // jb 
      return;
    _data16set(0x5A83, r16[dx]);
    r16[bx] = _data16get(0x5A85);
    _data16set(0x5A85, _data16get(0x5A85) + 2);
    if ( _data[0x552] == 0 ) // jz 
      { wPos = 0x581B; continue; }
    r16[ax] = _data16get(r16[bx] + 0x5AA3);
    if ( r16[ax] != 0 ) // jnz 
      { wPos = 0x581F; continue; }
    sub_5B21();
    return;
  case 0x581B:
    r16[ax] = _data16get(r16[bx] + 0x5A87);
  case 0x581F:
    _push(r16[ax]);
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _pop();
    sub_5889();
    wPos = -1;
  }
}
function sub_5829()
{
  _data16set(0x5A62, 0);
  _data[0x5A82] = 0;
}
function sub_5835()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x5A80) ) // jnz 
      { wPos = 0x5847; continue; }
    return;
  case 0x5847:
    _data16set(0x5A80, r16[dx]);
    _data[0x5A82] = _data[0x5A82] + 1;
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[bx] = _data16get(0x5A62);
    if ( _data[0x5A82] & 1 ) // jnz 
      { wPos = 0x5861; continue; }
    r16[bx] += 2;
  case 0x5861:
    r16[ax] = _data16get(r16[bx] + 0x5A64);
    sub_5889();
    wPos = -1;
  }
}
function sub_5869()
{
  if ( _data[0] == 0 ) // jz 
    return;
  _push(r16[bx]);
  _push(r16[ax]);
  r8[al] = 0x0B6;
  _out(0x43, r8[al]);
  r16[bx] = _data16get(0x5A62);
  _data16set(0x5A62, _data16get(0x5A62) + 2);
  r16[ax] = _data16get(r16[bx] + 0x5A64);
  sub_5889();
  r16[ax] = _pop();
  r16[bx] = _pop();
}
function sub_5889()
{
  _out(0x42, r8[al]);
  r8[al] = r8[ah];
  _out(0x42, r8[al]);
  r8[al] =_in(0x61);
  r8[al] |= 3;
  _out(0x61, r8[al]);
}
function sub_5897()
{
  if ( _data[0] == 0 ) // jz 
    return;
  _push(r16[ax]);
  _push(r16[cx]);
  _push(r16[dx]);
  r8[al] = 0x0B6;
  _out(0x43, r8[al]);
  r16[bx] = _data16get(0x5A56);
  r16[bx] &= 6;
  _data16set(0x5A56, _data16get(0x5A56) + 2);
  r16[ax] = _data16get(r16[bx] + 0x5A5A);
  sub_5889();
  r16[dx] = _pop();
  r16[cx] = _pop();
  r16[ax] = _pop();
}
function sub_58BD()
{
  _data[0x5927] = 0x80;
  _data[0x5928] = 0;
  _data[0x5929] = 0;
  _data16set(0x592A, 0x500);
  _data[0x592C] = 0x0FF;
  _data[0x592D] = 0;
  _data[0x5920] = 0;
  _data[0x5B07] = 0;
  _data16set(0x5B08, 0);
  _data16set(0x5B0C, 1);
  _data[0x5B0E] = 1;
}
function sub_58F8()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1CBF] != 0 ) // jnz 
      { wPos = 0x5908; continue; }
    r16[bx] = 0x390;
    r16[cx] = 0x1800;
    sub_59A3();
  case 0x5908:
    _data[0x127C] = 0;
    wPos = -1;
  }
}
function sub_590E()
{
  if ( _data[0x1CBF] != 0 ) // jnz 
    return;
  r16[bx] = 0x400;
  r16[cx] = 0x1800;
  sub_59A3();
}
function sub_591F()
{
  r16[bx] = 0x7D0;
  r16[cx] = 0x1800;
  sub_59A3();
  r16[bx] = 0x0A6E;
  r16[cx] = 0x1800;
  sub_59A3();
  r16[bx] = 0x0DEC;
  r16[cx] = 0x1800;
  sub_59A3();
}
function sub_593B()
{
  if ( _data[0] == 0 ) // jz 
    return;
  _data16set(0x5923, r16[bx]);
  _push(r16[ax]);
  r8[al] = 0x0B6;
  _out(0x43, r8[al]);
  r16[ax] = _pop();
  sub_5889();
  _data[0x5920] = 2;
  r8[ah] = 0;
  _int(0x1A);
  _data16set(0x5921, r16[dx]);
}
function sub_595D()
{
  if ( _data[0] == 0 ) // jz 
    return;
  if ( _data[0x5920] != 0 ) // jnz 
    return;
  sub_2DFD();
  r16[ax] = r16[dx];
  r16[ax] &= 0x7F;
  r16[ax] += 0x0AA;
  r16[bx] = r16[ax];
  r16[ax] += 0x1E;
  sub_593B();
}
function sub_597F()
{
  if ( _data[0] == 0 ) // jz 
    return;
  r16[ax] = 0x1200;
  r16[bx] = 0x1312;
  r16[ax] += _data16get(0x5B08);
  r16[bx] += _data16get(0x5B08);
  _data16set(0x5B08, _data16get(0x5B08) + 0x15E);
  sub_593B();
  _data[0x5B07] = 0x18;
}
function sub_59A3()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = r16[bx];
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x59C5; continue; }
    r16[cx] >>= 1;
  case 0x59C5:
    if ( --r16[cx] )
      { wPos = 0x59C5; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_59CB()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] =_in(0x61);
    r8[al] &= 0x0FE;
    _out(0x61, r8[al]);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x5A40, r16[dx]);
    _data16set(0x5A42, 0);
  case 0x59DF:
    r16[ax] = _data16get(0x5A42);
    r8[cl] = 6;
    r16[ax] >>= r8[cl];
    if ( unknown_condition() ) // jnz 
      { wPos = 0x59E9; continue; }
    r16[ax] = r16[ax] + 1;
  case 0x59E9:
    r16[cx] = r16[ax];
  case 0x59EB:
    _push(r16[cx]);
    r8[ah] = 0;
    _int(0x1A);
    r16[cx] = _pop();
    r16[dx] -= _data16get(0x5A40);
    if ( r16[dx] < 2 ) // jb 
      { wPos = 0x59EB; continue; }
    if ( r16[dx] >= 7 ) // jnb 
      { wPos = 0x5A18; continue; }
    if ( --r16[cx] )
      { wPos = 0x59EB; continue; }
    sub_2DFD();
    r8[dl] &= 2;
    r8[dl] &= _data16get(0);
    r8[al] =_in(0x61);
    r8[al] = r8[al] ^ r8[dl];
    _out(0x61, r8[al]);
    _data16set(0x5A42, _data16get(0x5A42) + 7);
    wPos = 0x59DF;
      continue;
  case 0x5A18:
    sub_5B21();
    wPos = -1;
  }
}
function sub_5A1C()
{
  alert("check 2");
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    sub_13B7();
    r16[bx] = _data16get(0x5A16);
    cf = (r16[bx] < r16[ax]); // cf-insertion
    r16[bx] -= r16[ax];
    if ( cf ) // jb 
      { wPos = 0x5A35; continue; }
    if ( r16[bx] > 0x260 ) // ja 
      { wPos = 0x5A35; continue; }
    return;
  case 0x5A35:
    _data16set(0x5A16, r16[ax]);
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    _data16set(0x5A18, _data16get(0x5A18) + 1);
    r16[bx] = _data16get(0x5A18);
    r16[bx] &= 0x1E;
    r16[ax] = _data16get(0x5A3C);
    r16[ax] &= 0x3FF;
    if ( r16[ax] < 0x180 ) // jb 
      { wPos = 0x5A59; continue; }
    r16[cx] = 0x180;
    r16[cx] -= r16[ax];
    var temp = r16[ax]; r16[ax] = r16[cx]; r16[cx] = temp;
    //_xchg(r16[ax], r16[cx]);
  case 0x5A59:
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] += _data16get(r16[bx] + 0x5A1A);
    r16[bx] = 1;
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x5A6D; continue; }
    r8[bl] <<= 1;
  case 0x5A6D:
    _data16set(0x5A3E, _data16get(0x5A3E) + r16[bx]);
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    _data16set(0x5A3C, _data16get(0x5A3C) + r16[bx]);
    r16[dx] = _data16get(0x5A3E);
    r8[cl] = 3;
    r16[dx] >>= r8[cl];
    r16[ax] += r16[dx];
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5A90()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x5A14) ) // jnz 
      { wPos = 0x5AA2; continue; }
    return;
  case 0x5AA2:
    _data16set(0x5A14, r16[dx]);
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    sub_2DFD();
    r16[ax] = r16[dx];
    r16[ax] &= 0x70;
    r16[ax] += 0x200;
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5AC2()
{
  alert("check3 ");
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x5A12, 0x338);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x5A10, r16[dx]);
    sub_13B7();
    _data16set(0x5A0E, r16[ax]);
  case 0x5AD6:
    sub_13B7();
    r16[dx] = r16[ax];
    r16[ax] -= _data16get(0x5A0E);
    if ( r16[ax] < 0x9C40 ) // jb 
      { wPos = 0x5B10; continue; }
    _data16set(0x5A0E, r16[dx]);
    if ( _data[0] == 0 ) // jz 
      { wPos = 0x5B10; continue; }
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    sub_2DFD();
    r16[ax] = r16[dx];
    r16[ax] &= 0x7FF;
    r16[ax] += _data16get(0x5A12);
    _data16set(0x5A12, _data16get(0x5A12) - 2);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
  case 0x5B10:
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x5A10);
    if ( r16[dx] < 2 ) // jb 
      { wPos = 0x5AD6; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_5B21()
{
  r8[al] =_in(0x61);
  r8[al] &= 0x0FC;
  _out(0x61, r8[al]);
}
function sub_5B28(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x592A);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    sub_13B7();
    r16[cx] = r16[ax];
  case 0x5B40:
    sub_13B7();
    r16[dx] = r16[cx];
    r16[dx] -= r16[ax];
    if ( r16[dx] < _data16get(0x592E) ) // jb 
      { wPos = 0x5B40; return wPos; }
    r8[al] =_in(0x61);
    r8[al] &= 0x0FC;
    _out(0x61, r8[al]);
    wPos = -1;
  }
  return wPos;
}
function sub_5B54()
{
  _data16set(0x59BE, 0);
  r8[ah] = 0;
  _int(0x1A);
  _data16set(0x59C0, r16[dx]);
}
function sub_5B63()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0] == 0 ) // jz 
      return;
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x59C0);
    if ( r16[ax] >= 2 ) // jnb 
      { wPos = 0x5B7A; continue; }
    return;
  case 0x5B7A:
    _data16set(0x59C0, r16[dx]);
    r16[bx] = _data16get(0x59BE);
    r16[bx] &= 0x0FE;
    if ( r16[bx] < 0x86 ) // jb 
      { wPos = 0x5B92; continue; }
    r16[bx] = 0;
    _data16set(0x59BE, r16[bx]);
  case 0x5B92:
    _data16set(0x59BE, _data16get(0x59BE) + 2);
    r16[ax] = _data16get(r16[bx] + 0x5934);
    r16[cx] = _data16get(0x59BC);
    _data16set(0x59BC, r16[ax]);
    if ( r16[ax] != r16[cx] ) // jnz 
      { wPos = 0x5BAA; continue; }
    sub_5B21();
    return;
  case 0x5BAA:
    r16[cx] = r16[ax];
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = r16[cx];
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    wPos = -1;
  }
}
function sub_5BBF()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
  case 0x5BBF:
    if ( _data[0] == 0 ) // jz 
      return;
    sub_5B63();
    if ( _data16get(0x59BE) < 0x7C ) // jb 
      { wPos = 0x5BBF; continue; }
    wPos = -1;
  }
}
function sub_5BE0()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x5F66, r16[dx]);
    _data16set(0x5F60, 0);
  case 0x5BEE:
    r16[ax] = 0x0B800;
    es = r16[ax];
    r16[bx] = _data16get(0x5F60);
    _data16set(0x5F60, _data16get(0x5F60) + 2);
    r16[bx] &= 2;
    si = _data16get(r16[bx] + 0x5F62);
    di = 0x0A74;
    r16[cx] = 0x4404;
    sub_2D9D();
  case 0x5C0D:
    sub_57E4();
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x5F66);
    if ( r16[ax] < 4 ) // jb 
      { wPos = 0x5C0D; continue; }
    _data16set(0x5F66, r16[dx]);
    if ( _data16get(0x5F60) != 4 ) // jnz 
      { wPos = 0x5C36; continue; }
    si = 0x5F68;
    di = 0x668;
    r16[cx] = 0x1004;
    sub_2D9D();
  case 0x5C36:
    r16[bx] = _data16get(0x5F60);
    cf = (r16[bx] < 8); // cf-insertion
    r16[bx] -= 8;
    if ( cf ) // jb 
      { wPos = 0x5C51; continue; }
    if ( r16[bx] >= 6 ) // jnb 
      { wPos = 0x5C51; continue; }
    si = 0x5FE8;
    di = _data16get(r16[bx] + 0x60E4);
    r16[cx] = 0x1506;
    sub_2D9D();
  case 0x5C51:
    if ( _data16get(0x5F60) < 0x10 ) // jb 
      { wPos = 0x5BEE; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_5C60()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _int(0x11);
    r8[al] &= 0x30;
    if ( r8[al] != 0x30 ) // jnz 
      return;
    r16[ax] = 0x0B800;
    ds = r16[ax];
    r16[ax] = 0x55AA;
    _data16set(0, r16[ax]);
    r16[ax] = _data16get(0);
    if ( r16[ax] != 0x55AA ) // jnz 
      { wPos = 0x5C96; continue; }
    si = 0x60F0;
    sub_5C9E();
    r16[ax] = 0x40;
    ds = r16[ax];
    r16[ax] = _data16get(0x10);
    r8[al] &= 0x0CF;
    r8[al] |= 0x10;
    _data16set(0x10, r16[ax]);
    r16[ax] = 4;
    _int(0x10);
    return;
  case 0x5C96:
    si = 0x6112;
    sub_5C9E();
  case 0x5C9C:
    wPos = 0x5C9C;
      continue;
    wPos = -1;
  }
}
function sub_5C9E()
{
  r16[ax] = seg_data;
  ds = r16[ax];
  sub_5E2B();
}
function sub_5CB0(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _data16set(0x4, 0);
    sub_1830();
    sub_2330();
    sub_2A30();
    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x6152;
    r16[cx] = 0x1D0B;
    di = 0x0BD;
    sub_2D9D();
    si = 0x63D0;
    r16[cx] = 0x160E;
    di = 0x69E;
    sub_2D9D();
    si = 0x6638;
    r16[cx] = 0x0C03;
    di = 0x0A78;
    sub_2D9D();
    si = 0x6680;
    r16[cx] = 0x80E;
    di = 0x0CA8;
    sub_2D9D();
    si = 0x6760;
    r16[cx] = 0x0B0C;
    di = 0x1D6E;
    sub_2D9D();
    si = 0x6868;
    r16[cx] = 0x804;
    di = 0x1DEC;
    sub_2D9D();
    _data16set(0x6A8D, 0);
    sub_5E3B();
    _data16set(0x579, 0);
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
    r16[ax] = _data16get(0x693);
    _data16set(0x6150, r16[ax]);
  case 0x5D54:
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x6A8B, r16[dx]);
    _data16set(0x5322, r16[dx]);
    _data16set(0x6A93, r16[dx]);
    r16[dx] -= 0x30;
    _data16set(0x6A88, r16[dx]);
    _data16set(0x5320, 0);
  case 0x5D71:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x6A93);
    if ( r16[ax] < 0x24 ) // jb 
      { wPos = 0x5D89; continue; }
    _data16set(0x6A93, r16[dx]);
    _push(r16[dx]);
    sub_5E3B();
    r16[dx] = _pop();
  case 0x5D89:
    r16[dx] -= _data16get(0x6A8B);
    r16[ax] = _data16get(0x56DA);
    if ( _data[0x41A] == 0 ) // jz 
      { wPos = 0x5DA0; continue; }
    r16[ax] += 0x48;
    if ( r16[dx] >= r16[ax] ) // jnb 
      { wPos = 0x5D54; continue; }
    wPos = 0x5DA7;
      continue;
  case 0x5DA0:
    r16[ax] += 6;
    if ( r16[dx] > r16[ax] ) // ja 
      return -1;
  case 0x5DA7:
    sub_53B0();
    sub_5DD4();
    if ( _data[0x69B] == 0 ) // jz 
      { wPos = 0x5DCA; continue; }
    r16[dx] = 0x201;
    r8[al] =_in(r16[dx]);
    r8[al] &= 0x10;
    if ( !r8[al] ) // jz 
      { wPos = 0x5DC3; continue; }
    _data[0x6A8A] = 1;
    wPos = 0x5DCA;
      continue;
  case 0x5DC3:
    if ( _data[0x6A8A] != 0 ) // jnz 
      return -1;
  case 0x5DCA:
    //Sleep(5);
//    tick();
    r16[ax] = _data16get(0x6150);
    if ( r16[ax] == _data16get(0x693) ) // jz 
      { return 0x5D71; }
    wPos = -1;
  }
  return wPos;
}
function sub_5DD4()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(0x579) > 0x20 ) // ja 
      { wPos = 0x5DE2; continue; }
    _data[0x698] = 1;
    wPos = 0x5E1C;
      continue;
  case 0x5DE2:
    if ( _data16get(0x579) < 0x120 ) // jb 
      { wPos = 0x5DF1; continue; }
    _data[0x698] = 0x0FF;
    wPos = 0x5E1C;
      continue;
  case 0x5DF1:
    r8[ah] = 0;
    _int(0x1A);
    r16[ax] = r16[dx];
    r16[ax] -= _data16get(0x6A88);
    if ( r16[ax] < 0x12 ) // jb 
      { wPos = 0x5E1C; continue; }
    _data16set(0x6A88, r16[dx]);
    sub_2DFD();
    _data[0x698] = 0;
    if ( r8[dl] > 0x0A0 ) // ja 
      { wPos = 0x5E1C; continue; }
    r8[dl] &= 1;
    if ( r8[dl] ) // jnz 
      { wPos = 0x5E18; continue; }
    r8[dl] = 0x0FF;
  case 0x5E18:
    _data[0x698] = r8[dl];
  case 0x5E1C:
    _data16set(0x572, 4);
    sub_8E5();
    wPos = -1;
  }
}
function sub_5E2B()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
  case 0x5E2B:
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      return;
    _push(si);
    r8[bl] = 2;
    r8[ah] = 0x0E;
    _int(0x10);
    si = _pop();
    wPos = 0x5E2B;
      continue;
    wPos = -1;
  }
}
function sub_5E3B()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  _data16set(0x6A8D, _data16get(0x6A8D) + 2);
  r16[bx] = _data16get(0x6A8D);
  r16[bx] &= 2;
  si = _data16get(r16[bx] + 0x6A8F);
  r16[cx] = 0x0C0A;
  di = 0x1D38;
  sub_2D9D();
}
function sub_5E5B()
{
  r8[dl] = 0;
  r8[bh] = r8[dl];
  r8[ah] = 2;
  _int(0x10);
}
function sub_5E70(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    sub_5B21();
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x6DFC, r16[dx]);
    _data16set(0x6DFE, r16[cx]);
    _push(ds);
    _push(ds);
    es = _pop();
    r16[ax] = 0x0B800;
    ds = r16[ax];
    si = 0x0DCA;
    di = 0x0E;
    r16[cx] = 0x1020;
    sub_2DCA();
    ds = _pop();
    r16[dx] = 0x0B05;
    r8[bh] = 0;
    r8[ah] = 2;
    _int(0x10);
    si = 0x6D91;
    _cld();
    sub_5E2B();
    r16[dx] = 0x0C05;
    r8[bh] = 0;
    r8[ah] = 2;
    _int(0x10);
    si = 0x6DB2;
    if ( _data[0x69B] == 0 ) // jz 
      { wPos = 0x5EBA; continue; }
    si = 0x6DD3;
  case 0x5EBA:
    _cld();
    sub_5E2B();

    sub_5F97_pc = 0;
  case 0x0003:
    sub_5F97_pc = sub_5F97(sub_5F97_pc);
    if ( sub_5F97_pc != -1 ) 
      return 0x0003;

    r16[ax] = 0x0B800;
    es = r16[ax];
    si = 0x0E;
    di = 0x0DCA;
    r16[cx] = 0x1020;
    sub_2D9D();
    r8[ah] = 1;
    r16[cx] = _data16get(0x6DFE);
    r16[dx] = _data16get(0x6DFC);
    _int(0x1A);
    r16[ax] = _data16get(0x693);
    _data16set(0x6E00, r16[ax]);
    wPos = -1;
  }
  return -1;
}
function sub_5EE5(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    sub_5B21();
  case 0x5EE8:
    sub_5FCD();
    _data16set(0x6D8F, 0);
    sub_5FB1();
  case 0x5EF4:
    r16[ax] = _data16get(0x693);
  case 0x5EF7:
    if ( r16[ax] == _data16get(0x693) ) // jz 
      { wPos = 0x5EF7; return wPos; }
    if ( !(_data[0x6C1] & 0x80) ) // jz 
      { wPos = 0x5F12; continue; }
    if ( _data[0x6C2] & 0x80 ) // jnz 
      { wPos = 0x5EF4; continue; }
    _data[0x69B] = 0;
    wPos = 0x5F1C;
      continue;
  case 0x5F12:
    sub_5FE5();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x5EE8; continue; }
    _data[0x69B] = 1;
  case 0x5F1C:
    r16[cx] = 5;
  case 0x5F1F:
    _push(r16[cx]);
    sub_5FB1();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x5F1F; continue; }
  case 0x5F26:
    r16[ax] = _data16get(0x693);
  case 0x5F29:
    if ( r16[ax] == _data16get(0x693) ) // jz 
      { wPos = 0x5F29; return wPos; }
    r16[ax] = 0;
    if ( !(_data[0x6C3] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    r16[ax] = r16[ax] + 1;
    if ( !(_data[0x6C4] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    r16[ax] = r16[ax] + 1;
    if ( !(_data[0x6C5] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    r16[ax] = r16[ax] + 1;
    if ( _data[0x6C6] & 0x80 ) // jnz 
      { wPos = 0x5F26; continue; }
  case 0x5F50:
    _data16set(0x6DF8, r16[ax]);
    r16[cx] = 5;
  case 0x5F56:
    _push(r16[cx]);
    sub_5FB1();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { wPos = 0x5F56; continue; }
    if ( _data[0x69B] == 0 ) // jz 
      { wPos = 0x5F7E; continue; }
    _data16set(0x6D8F, 0x20);
    sub_5FB1();
    sub_5FB1();
    _data16set(0x6D8F, 0x18);
    sub_5FB1();
    sub_5FB1();
    wPos = 0x5F93;
      continue;
  case 0x5F7E:
    _data16set(0x6D8F, 0x1C);
    sub_5FB1();
    sub_5FB1();
    _data16set(0x6D8F, 0x16);
    sub_5FB1();
  case 0x5F93:

    sub_5F97_pc = 0;
  case 0x0004:
    sub_5F97_pc = sub_5F97(sub_5F97_pc);
    if ( sub_5F97_pc != -1 ) 
      return 0x0004;

    wPos = -1;
  }
  return -1;
}
function sub_5F97(wPos)
{
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x69B] == 0 ) // jz 
      { wPos = 0x5FA7; continue; }
  case 0x5F9E:
    r16[dx] = 0x201;
    r8[al] =_in(r16[dx]);
    r8[al] &= 0x10;
    if ( r8[al] ) // jnz 
      { wPos = 0x5F9E; continue; }
    return -1;
  case 0x5FA7:
    r16[ax] = _data16get(0x693);
  case 0x5FAA:
    if ( r16[ax] == _data16get(0x693) ) // jz 
      { wPos = 0x5FAA; return wPos; }
    wPos = -1;
  }
  return -1;
}
function sub_5FB1()
{
  r16[bx] = _data16get(0x6D8F);
  r16[dx] = _data16get(r16[bx] + 0x6D63);
  sub_5E5B();
  r16[bx] = _data16get(0x6D8F);
  _data16set(0x6D8F, _data16get(0x6D8F) + 2);
  si = _data16get(r16[bx] + 0x6D37);
  sub_5E2B();
}
function sub_5FCD()
{
  _cld();
  r16[ax] = 0x0B800;
  es = r16[ax];
  r16[ax] = 0;
  di = r16[ax];
  r16[cx] = 0x0FA0;
  _rep_stosw();
  di = 0x2000;
  r16[cx] = 0x0FA0;
  _rep_stosw();
}
function sub_5FE5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _int(0x11);
    if ( !(r16[ax] & 0x1000) ) // jz 
      { wPos = 0x5FF6; continue; }
    sub_600F();
    if ( unknown_condition() ) // jnb cf=0
      return;
    sub_600F();
    if ( unknown_condition() ) // jnb cf=0
      return;
  case 0x5FF6:
    _data16set(0x6D8F, 0x24);
    r16[cx] = 4;
  case 0x5FFF:
    sub_5FB1();
    if ( --r16[cx] )
      { wPos = 0x5FFF; continue; }
    r16[ax] = _data16get(0x693);
  case 0x6007:
    if ( r16[ax] == _data16get(0x693) ) // jz 
      { wPos = 0x6007; continue; }
    _stc();
    wPos = -1;
  }
}
function sub_600F()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[dx] = 0x201;
    _out(r16[dx], r8[al]);
    r8[ah] = 0;
    _int(0x1A);
    _data16set(0x6DFA, r16[dx]);
  case 0x601B:
    r16[dx] = 0x201;
    r8[al] =_in(r16[dx]);
    if ( r8[al] & 3 ) // jnz 
      { wPos = 0x6025; continue; }
    _clc();
    return;
  case 0x6025:
    r8[ah] = 0;
    _int(0x1A);
    r16[dx] -= _data16get(0x6DFA);
    if ( r16[dx] < 0x12 ) // jb 
      { wPos = 0x601B; continue; }
    _stc();
    wPos = -1;
  }
}
function sub_6040()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _cld();
    _push(ds);
    es = _pop();
    di = 0x0E;
    r16[cx] = 0x24;
    r16[ax] = 0;
    _rep_stosw();
    _data16set(0x6F24, 0x25);
    r16[ax] = 0x0B800;
    es = r16[ax];
  case 0x6058:
    si = 0x0E;
    di = _data16get(0x6F24);
    r16[cx] = 0x0C03;
    sub_2D9D();
    _data16set(0x6F24, _data16get(0x6F24) + 0x1E0);
    si = 0x6E10;
    di = _data16get(0x6F24);
    r16[cx] = 0x0C03;
    sub_2D9D();
  case 0x607D:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x6F26) ) // jz 
      { wPos = 0x607D; continue; }
    _data16set(0x6F26, r16[dx]);
    if ( _data[0] == 0 ) // jz 
      { wPos = 0x60A7; continue; }
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x6F24);
    r16[ax] >>= 1;
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] =_in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
  case 0x60A7:
    if ( _data16get(0x6F24) < 0x1A40 ) // jb 
      { wPos = 0x6058; continue; }
    si = 0x6E58;
    di = _data16get(0x6F24);
    r16[cx] = 0x1106;
    sub_2D9D();
  case 0x60BC:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] == _data16get(0x6F28) ) // jz 
      { wPos = 0x60BC; continue; }
    _data16set(0x6F28, r16[dx]);
    if ( _data[0] == 0 ) // jz 
      { wPos = 0x60E6; continue; }
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = 0x0C00;
    if ( !(r8[dl] & 1) ) // jz 
      { wPos = 0x60E0; continue; }
    r16[ax] = 0x0B54;
  case 0x60E0:
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
  case 0x60E6:
    r16[dx] -= _data16get(0x6F26);
    if ( r16[dx] < 0x12 ) // jb 
      { wPos = 0x60BC; continue; }
    sub_5B21();
    wPos = -1;
  }
}
function sub_6100()
{
  _data[0x70F2] = 0;
}
function sub_6106()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[ah] = 0;
    _int(0x1A);
    if ( r16[dx] != _data16get(0x70EE) ) // jnz 
      { wPos = 0x6111; continue; }
    return;
  case 0x6111:
    _data16set(0x70EE, r16[dx]);
    sub_62A6();
    if ( unknown_condition() ) // jnb cf=0
      { wPos = 0x6129; continue; }
    sub_11E3();
    sub_622B();
    sub_1145();
    _data[0x70F2] = 0;
    return;
  case 0x6129:
    if ( _data[0x70F2] != 0 ) // jnz 
      { wPos = 0x619E; continue; }
  case 0x6130:
    sub_2DFD();
    r16[bx] = r16[dx];
    r16[bx] &= 0x1F;
    if ( r8[bl] < 0x10 ) // jb 
      { wPos = 0x6166; continue; }
    r8[bl] -= 0x10;
    if ( r8[bl] > 9 ) // ja 
      { wPos = 0x6130; continue; }
    r8[dl] = 1;
    if ( r8[bl] < 5 ) // jb 
      { wPos = 0x614F; continue; }
    r8[dl] = 0x0FF;
  case 0x614F:
    _data[0x70F6] = r8[dl];
    _data[0x70F5] = 6;
    r8[bl] <<= 1;
    r16[ax] = _data16get(r16[bx] + 0x70B8);
    r16[ax] += 4;
    _data16set(0x70F3, r16[ax]);
    wPos = 0x6188;
      continue;
  case 0x6166:
    r16[ax] = 0x0C;
    r8[dl] = 1;
    if ( !(r8[bl] & 8) ) // jz 
      { wPos = 0x6175; continue; }
    r16[ax] = 0x120;
    r8[dl] = 0x0FF;
  case 0x6175:
    _data16set(0x70F3, r16[ax]);
    _data[0x70F6] = r8[dl];
    r8[bl] &= 7;
    r8[al] = _data[r16[bx] + 0x70B0];
    r8[al] += 8;
    _data[0x70F5] = r8[al];
  case 0x6188:
    _data[0x70F2] = 1;
    _data[0x70F7] = 1;
    _data16set(0x70F0, 0);
    _data16set(0x70EC, 0x0FFFF);
  case 0x619E:
    if ( _data16get(0x70F0) >= 0x0A0 ) // jnb 
      { wPos = 0x61AB; continue; }
    _data16set(0x70F0, _data16get(0x70F0) + 4);
  case 0x61AB:
    _data[0x70F5] += 2;
    if ( _data[0x70F5] > 0x0BF ) // ja 
      { wPos = 0x61D4; continue; }
    if ( _data[0x70F6] == 1 ) // jz 
      { wPos = 0x61C7; continue; }
    cf = (_data16get(0x70F3) < 5); // cf-insertion
    _data16set(0x70F3, _data16get(0x70F3) - 5);
    if ( cf ) // jb 
      { wPos = 0x61D4; continue; }
    wPos = 0x61DD;
      continue;
  case 0x61C7:
    _data16set(0x70F3, _data16get(0x70F3) + 5);
    if ( _data16get(0x70F3) < 0x12C ) // jb 
      { wPos = 0x61DD; continue; }
  case 0x61D4:
    _data[0x70F2] = 0;
    sub_622B();
    return;
  case 0x61DD:
    r16[cx] = _data16get(0x70F3);
    r8[dl] = _data[0x70F5];
    sub_2CB0();
    _data16set(0x70FA, r16[ax]);
    sub_62A6();
    if ( unknown_condition() ) // jb cf=1
      { wPos = 0x61D4; continue; }
    sub_6245();
    sub_622B();
    sub_61FA();
    wPos = -1;
  }
}
function sub_61FA()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r16[ax] = 0x0B800;
    es = r16[ax];
    _data[0x70F7] = 0;
    r16[ax] = _data16get(0x70F0);
    r16[ax] &= 0x1E0;
    r16[ax] += 0x6F30;
    if ( _data[0x70F6] == 0x0FF ) // jz 
      { wPos = 0x6217; continue; }
    r16[ax] += 0x0C0;
  case 0x6217:
    si = r16[ax];
    di = _data16get(0x70FA);
    _data16set(0x70F8, di);
    bp = 0x70CC;
    r16[cx] = 0x802;
    sub_2CCC();
    wPos = -1;
  }
}
function sub_622B()
{
  if ( _data[0x70F7] != 0 ) // jnz 
    return;
  r16[ax] = 0x0B800;
  es = r16[ax];
  si = 0x70CC;
  di = _data16get(0x70F8);
  r16[cx] = 0x802;
  sub_2D9D();
}
function sub_6245()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    r8[al] = _data[0x70F5];
    r8[al] -= 8;
    r8[al] &= 0x0F8;
    r16[cx] = 7;
  case 0x624F:
    r16[bx] = r16[cx];
    r16[bx]--;
    if ( r8[al] == _data16get(r16[bx] + 0x2BD4) ) // jz 
      { wPos = 0x625B; continue; }
    if ( --r16[cx] )
      { wPos = 0x624F; continue; }
    return;
  case 0x625B:
    r16[ax] = _data16get(0x70F3);
    r8[cl] = 4;
    r16[ax] >>= r8[cl];
    cf = (r16[ax] < 2); // cf-insertion
    r16[ax] -= 2;
    if ( cf ) // jb 
      return;
    if ( r16[ax] >= 0x10 ) // jnb 
      return;
    di = r16[ax];
    r8[dl] = _data[r16[bx] + 0x2BDB];
    r8[dh] = 0;
    r16[ax] += r16[dx];
    if ( r16[ax] == _data16get(0x70EC) ) // jz 
      return;
    _data16set(0x70EC, r16[ax]);
    si = r16[ax];
    _data[si + 0x2BE2] = _data[si + 0x2BE2] ^ 2;
    r8[al] = _data[si + 0x2BE2];
    r8[ah] = 0;
    di <<= 1;
    r16[cx] = _data16get(di + 0x70FC);
    r8[dl] = _data[r16[bx] + 0x7120];
    _push(r16[ax]);
    _push(r16[cx]);
    _push(r16[dx]);
    sub_622B();
    r16[dx] = _pop();
    r16[cx] = _pop();
    r16[bx] = _pop();
    sub_30E3();
    sub_61FA();
    wPos = -1;
  }
}
function sub_62A6()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x70F2] != 0 ) // jnz 
      { wPos = 0x62AF; continue; }
    _clc();
    return;
  case 0x62AF:
    r16[ax] = _data16get(0x70F3);
    r8[dl] = _data[0x70F5];
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r16[cx] = 0x0E08;
    sub_2E29();
    if ( unknown_condition() ) // jnb cf=0
      return;
    _data[0x571] = 1;
    _data[0x576] = 2;
    _data[0x578] = 0x20;
    _data[0x55B] = 8;
    r16[ax] = 0x91D;
    r16[bx] = 0x0CE4;
    sub_593B();
    _stc();
    wPos = -1;
  }
}
