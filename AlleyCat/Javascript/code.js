function start()
{
  var wPos = 0;
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
    sub_2690();
    _data16set(0x8, 0);
    _data16set(0x4, 0);
    sub_1D31();
    sub_5B21();
//    sub_5CB0();
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
      return -1;
    _data16set(0x684, _data16get(0x684) -1);
    if ( !_data16get(0x684) ) // jz 
      { wPos = 0x90C; continue; }
    return -1;
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
      return -1;
  case 0x926:
    _data16set(0x57D, r16[dx]);
    _data16set(0x57F, r16[ax]);
    if ( _data16get(4) != 4 ) // jnz 
      { wPos = 0x93B; continue; }
    if ( _data[0x39E1] != 0 ) // jnz 
      return -1;
  case 0x93B:
    if ( _data16get(4) != 6 ) // jnz 
      { wPos = 0x949; continue; }
    if ( _data[0x44BD] != 0 ) // jnz 
      return -1;
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
      return -1;
    sub_1145();
    return -1;
  case 0xBAC:
    sub_1B7A();
    if ( !cf ) // jnb 
      { wPos = 0xBB2; continue; }
    return -1;
  case 0xBB2:
    if ( _data[0x1CB8] != 0 ) // jnz 
      return -1;
    if ( _data[0x558] == 0 ) // jz 
      { wPos = 0xC1C; continue; }
    if ( _data[0x559] == 0 ) // jz 
      { wPos = 0xBD3; continue; }
    if ( _data[0x1CBF] != 0 ) // jnz 
      return -1;
    _data[0x559]--;
    return -1;
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
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    r8[dl] = _data[0x57B];
    r16[cx] = _data16get(0x579);
    sub_2CB0();
    _data16set(0x55F, r16[ax]);
    sub_1145();
    return -1;
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
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    _data16set(0x565, 0x0E03);
    _data16set(0x55D, 0x9DA);
    sub_1145();
  case 0xC5F:
    if ( _data[0x699] != 0 ) // jnz 
      { wPos = 0xC67; continue; }
    return -1;
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
    if ( unknown_condition() ) // jnb cf=0
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
    return -1;
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
    return -1;
  case 0xE0F:
    sub_70D();
    sub_59CB();
    return -1;
  case 0xE16:
    _data16set(0x565, r16[bx]);
    _data[0x576] = 2;
  case 0xE1F:
    sub_1145();
    return -1;
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
      return -1;
    sub_58F8();
    return -1;
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
    return -1;
  case 0xF63:
    sub_1020();
    _data16set(0x55D, r16[bx]);
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    r16[ax] = _data16get(0x563);
    _data16set(0x55F, r16[ax]);
    _data16set(0x565, 0x0B03);
    sub_1145();
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
    return -1;
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
    return -1;
  case 0x101B:
    _data16set(0x579, r16[ax]);
  case 0x101E:
    _clc();
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
      return -1;
  case 0x1087:
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
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
  return wPos;
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
function sub_11E3()
{
  r16[ax] = 0x0B800;
  es = r16[ax];
  di = _data16get(0x55F);
  si = 0x5FA;
  r16[cx] = _data16get(0x561);
  sub_2D9D();
}
function sub_13AA()
{
  r16[ax] = 0x0F000;
  es = r16[ax];
  r8[al] = 0xff;
  _data[0x697] = r8[al];
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
  return wPos;
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
    return -1;
  case 0x1613:
    if ( _data16get(4) == 0 ) // jz 
      { wPos = 0x161E; continue; }
    sub_16C6();
    return -1;
  case 0x161E:
    r8[al] = _data[0x57B];
    r8[al] &= 0x0F8;
    if ( r8[al] == 0x60 ) // jz 
      { wPos = 0x1630; continue; }
    sub_1657();
    if ( unknown_condition() ) // jb cf=1
      return -1;
    sub_17AD();
    return -1;
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
    return -1;
  case 0x1655:
    _clc();
    wPos = -1;
  }
  return wPos;
}
function sub_1830()
{
  _data[0x1665] = 0;
  _data[0x1673] = 0;
  _data[0x1677] = 0;
  _data[0x1678] = 0;
  _data16set(0x166C, 9);
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
    _xchg(r8[cl], r8[ch]);
    si = 0x10;
    r16[ax] = _data16get(0x1671);
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r8[ch] = 0x0E;
    sub_2E29();
    if ( unknown_condition() ) // jnb cf=0
      return -1;
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
    return -1;
  case 0x1BE1:
    _clc();
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
    return -1;
  case 0x2134:
    _clc();
    wPos = -1;
  }
  return wPos;
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
    return -1;
  case 0x2300:
    r16[cx] = _data16get(0x1D64);
    _xchg(r8[ch], r8[cl]);
    r16[ax] = _data16get(0x1D5C);
    r8[dl] = _data[0x1D5F];
    si = 0x10;
    r16[bx] = _data16get(0x579);
    r8[dh] = _data[0x57B];
    di = 0x18;
    r8[ch] = 0x0E;
    sub_2E29();
    if ( unknown_condition() ) // jnb cf=0
      return -1;
    _data[0x1D58] = 1;
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
    return -1;
  case 0x26A7:
    si = 0x1F82;
    di = 0x1F89;
    r16[cx] = 7;
    _rep_movsb();
    wPos = -1;
  }
  return wPos;
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
    return -1;
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
  return wPos;
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
      return -1;
    if ( _data[0x1F92] != 3 ) // jnz 
      { wPos = 0x274B; continue; }
    _data16set(0x1F90, _data16get(0x1F90) + 2);
    wPos = 0x274B;
      continue;
    wPos = -1;
  }
  return wPos;
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
    return -1;
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
  return wPos;
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
    if ( r8[dl] == _data[0x2AC4] ) // jz 
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
  return wPos;
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
  return wPos;
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
    return -1;
  case 0x2C9A:
    sub_2C3D();
    r16[bx] = _data16get(0x2AC5);
    r16[bx] += 2;
    wPos = 0x2C8C;
      continue;
    wPos = -1;
  }
  return wPos;
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
  return wPos;
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
  return wPos;
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
  return wPos;
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
  return wPos;
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
  return wPos;
}
function sub_2DFD()
{
  r16[dx] = _data16get(0x2AE5);
  r8[dl] = r8[dl] ^ r8[dh];
  r8[dl] >>= 1;
  cf = r8[dl] & 1 ? 1 : 0;
  r8[dl] >>= 1;
  _data16set( 0x2AE5, _rcr16(_data16get(0x2AE5), 1) );
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
    _in(r8[al], 0x40);
    r8[ah] = r8[al];
    _in(r8[al], 0x40);
    if ( r16[ax] != 0 ) // jnz 
      { wPos = 0x2E25; continue; }
    r16[ax] = 0x0FA59;
  case 0x2E25:
    _data16set(0x2AE5, r16[ax]);
    wPos = -1;
  }
  return wPos;
}
function sub_5450()
{
  _data[0x5B0F] = 0x0C;
  _data16set(0x5B0C, 1);
  _data16set(0x5B12, 0x1FF);
  _data16set(0x5B0A, 0x0F);
  _data[0x5B0E] = 1;
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
      return -1;
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
    return -1;
  case 0x5C96:
    si = 0x6112;
    sub_5C9E();
  case 0x5C9C:
    wPos = 0x5C9C;
      continue;
    wPos = -1;
  }
  return wPos;
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
    _in(r8[al], r16[dx]);
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
  //  Sleep(5);
  //  tick();
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
  return wPos;
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
function sub_5EE5()
{
  var wPos = 0;
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
      { wPos = 0x5EF7; continue; }
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
      { wPos = 0x5F29; continue; }
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
    sub_5F97();
    wPos = -1;
  }
  return wPos;
}

function sub_5AC2() {} 
function sub_59CB() {} 
function sub_2051() {} 
function sub_20E1() {} 
function sub_209B() {} 
function sub_1799() {} 
function sub_3C43() {} 
function sub_30FA() {} 
function sub_590E() {} 
function sub_16C6() {} 
function sub_1657() {} 
function sub_17AD() {} 
function sub_2136() {} 
function sub_2E29() {} 
function sub_1922() {} 
function sub_10DD() {} 
function sub_1166() {} 
function sub_5FCD() {} 
function sub_5FB1() {} 
function sub_5FE5() {} 
function sub_5F97() {} 
function sub_34A0() {} 
function sub_597F() {} 
function sub_1D6E() {} 
function sub_5C9E() {} 
function sub_53B0() {} 
function sub_5B21() {} 
function sub_3445() {} 
