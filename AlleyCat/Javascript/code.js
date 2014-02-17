
function start()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _push(ds);
    set_ax(0);
    _push(get_ax());
    sub_5C60();
    set_ax(seg_data);
    ds = get_ax();
    sub_13AA();
    _data[0x690] = 4;
    _data16set(0x6DF8, 0);
    _data[0x69B] = 0;
    sub_1419();
    sub_13E8();
    set_ax(_data16get(0x693));
    set_ax(get_ax() + 0x240);
    _data16set(0x6E00, get_ax());
    set_ax(4);
    _int(0x10);
    al = 4;
    if ( _data[0x697] != 0x0FD ) // !jz
      al = 6;
    _data[0x690] = al;
    ah = 0x0B;
    set_bx(0x101);
    _int(0x10);
    _data16set(0x416, 0);
    _data16set(0x4, 0);
    sub_1D31();
    if ( _data[0x697] == 0x0FD ) // jz 
      { wPos = 0x65; continue; }
    set_dx(0x3D9);
    al = 0x20;
    _out(get_dx(), al);
  case 0x65:
    sub_2E10();
    sub_26E1();
    sub_26DA();
    _data[0x41A] = 0;
    set_ax(0x0FFFF);
    _data16set(0x41D, get_ax());
    _data16set(0x41F, get_ax());
    _data[0x0] = 0x0FF;
    sub_2690();
    _data16set(0x8, 0);
    _data16set(0x4, 0);
    sub_1D31();
    sub_5B21();
//    sub_5CB0();
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
    set_cx(0);
    ah = 1;
    if ( _data16get(0x579) < 0x0A0 ) // jb 
      { wPos = 0x71F; continue; }
    set_cx(0x128);
    ah = 0x0FF;
  case 0x71F:
    _data[0x56E] = ah;
    _data[0x558] = 3;
    _data[0x559] = 0x0C;
    dl = 0x0B4;
    _data16set(0x579, get_cx());
    _data[0x57B] = dl;
    _data[0x57C] = 0x0E6;
    sub_2CB0();
    _data16set(0x55F, get_ax());
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
function sub_8E5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    ah = 0;
    _int(0x1A);
    if ( get_dx() != _data16get(0x57D) ) // jnz 
      { wPos = 0x8FD; continue; }
    if ( _data16get(0x684) == 0 ) // jz 
      return -1;
    _data16set(0x684, _data16get(0x684) -1);
    if ( !_data16get(0x684) ) // jz 
      { wPos = 0x90C; continue; }
    return -1;
  case 0x8FD:
    set_ax(0x20);
    if ( _data[0x697] == 0x0FD ) // !jnz
      set_ax(get_ax() >> 1);
    _data16set(0x684, get_ax());
  case 0x90C:
    if ( _data16get(4) == 2 ) // jz 
      { wPos = 0x91D; continue; }
    cl = _data[0x571];
    cl |= _data16get(0x56E);
    if ( cl ) // jnz 
      { wPos = 0x926; continue; }
  case 0x91D:
    _push(get_dx());
    _push(get_ax());
  zf = 0;
    set_ax(_pop());
    set_dx(_pop());
    if ( zf ) // jz 
      return -1;
  case 0x926:
    _data16set(0x57D, get_dx());
    _data16set(0x57F, get_ax());
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
    set_ax(_data16get(0x57D));
    set_ax(get_ax() - _data16get(0x5F1));
    if ( get_ax() < _data16get(si + 0x589) ) // jb 
      { wPos = 0x9D6; continue; }
    if ( get_ax() < _data16get(si + 0x599) ) // jb 
      { wPos = 0x971; continue; }
    _data[0x552] = 1;
  case 0x971:
    _data[0x5F5]--;
    if ( _data[0x5F5] ) // jnz 
      { wPos = 0x9B9; continue; }
    sub_597F();
    _data[0x5F5] = 6;
    al = _data[0x5F4];
    if ( _data[0x57B] < 0x0B3 ) // jb 
      { wPos = 0x992; continue; }
    if ( al < 0x0C8 ) // !jnb
    {
      al += 0x1E;
      _data[0x5F4] = al;
    }
  case 0x992:
    dl = _data[0x57B];
    cf = (dl < al); // cf-insertion
    dl -= al;
    if ( cf ) // !jnb
      dl = 0;
    set_cx(_data16get(0x579));
    dl &= 0x0F8;
    sub_2CB0();
    di = get_ax();
    si = 0x64E;
    set_ax(0x0B800);
    es = get_ax();
    bp = 0x0E;
    set_cx(0x503);
    sub_2D35();
  case 0x9B9:
    _data[0x56E] = 0;

    _data[0x571] = 1;
    _data[0x5F3] = 1;
    _data[0x576] = 0x20;
    set_bx(0);
    ah = 0x0B;
    _int(0x10);
    wPos = 0xA86;
      continue;
  case 0x9D6:
    si = _data16get(8);
    si <<= 1;
    set_bx(0);
    if ( get_ax() < _data16get(si + 0x5A9) ) // jb 
      { wPos = 0x9F6; continue; }
    bl = bl + 1;
    if ( get_ax() < _data16get(si + 0x5B9) ) // jb 
      { wPos = 0x9F6; continue; }
    bl = 5;
    if ( get_ax() < _data16get(si + 0x5C9) ) // jb 
      { wPos = 0x9F6; continue; }
    bl--;
  case 0x9F6:
    ah = 0x0B;
    _int(0x10);
    al = _data[0x56E];
    _data[0x56F] = al;
    al = _data[0x571];
    _data[0x570] = al;
    al = _data[0x698];
		if ( _data[0x698] == 0 ) unknown_condition();

    if ( al != 0 ) // jnz 
      { wPos = 0xA1A; continue; }
    if ( _data16get(0x574) < 0x10 ) // jb 
      { wPos = 0xA2E; continue; }
    _data16set(0x574, _data16get(0x574) -1);
    wPos = 0xA37;
      continue;
  case 0xA1A:
    if ( al != _data16get(0x56E) ) // jnz 
      { wPos = 0xA2E; continue; }
    if ( _data16get(0x574) >= 0x30 ) // jnb 
      { wPos = 0xA37; continue; }
    _data16set(0x574, _data16get(0x574) + 3);
    wPos = 0xA37;
      continue;
  case 0xA2E:
    _data[0x56E] = al;


	_data16set(0x574, 0x20);
  case 0xA37:
    set_ax(_data16get(0x574));
    cl = 3;
    set_ax(get_ax() >> cl);
    set_bx(_data16get(8));
    bl <<= 1;
    if ( get_ax() <= _data16get(get_bx() + 0x66C) ) // jbe 
      { wPos = 0xA4E; continue; }
    set_ax(_data16get(get_bx() + 0x66C));
  case 0xA4E:
    _data16set(0x572, get_ax());
    sub_FC9();
    al = _data[0x699];
    if ( al != 0 ) // jnz 
      { wPos = 0xA6A; continue; }
    al = ~ al;
    if ( _data[0x576] < 0x10 ) // jb 
      { wPos = 0xA7E; continue; }
    _data[0x576]--;
    wPos = 0xA86;
      continue;
  case 0xA6A:
    if ( al != _data16get(0x571) ) // jnz 
      { wPos = 0xA7E; continue; }
    if ( _data[0x576] >= 0x40 ) // jnb 
      { wPos = 0xA86; continue; }
    _data[0x576] += 4;
    wPos = 0xA86;
      continue;
  case 0xA7E:
    _data[0x571] = al;
    _data[0x576] = 0x20;
  case 0xA86:
    si = _data16get(8);
    dl = _data[0x57B];
    cl = 4;
    bl = _data[0x576];
    bl >>= cl;
    if ( bl <= _data16get(si + 0x67C) ) // jbe 
      { wPos = 0xAA0; continue; }
    bl = _data[si + 0x67C];
  case 0xAA0:
    al = _data[0x571];
    if ( al < 1 ) // jb 
      { wPos = 0xACE; continue; }
    if ( al != 1 ) // jnz 
      { wPos = 0xAB4; continue; }
    dl += bl;
    if ( dl < 0x0B4 ) // jb 
      { wPos = 0xACE; continue; }
    dl = 0x0B3;
    wPos = 0xACE;
      continue;
  case 0xAB4:
    cf = (dl < bl); // cf-insertion
    dl -= bl;
    if ( cf ) // jb 
      { wPos = 0xABD; continue; }
    if ( dl > 3 ) // ja 
      { wPos = 0xACE; continue; }
  case 0xABD:
    set_ax(_data16get(0x9B8));
    if ( get_ax() != _data16get(0x55D) ) // jnz 
      { wPos = 0xACC; continue; }
    set_ax(_data16get(0x57D));
    _data16set(0x5F1, get_ax());
  case 0xACC:
    dl = 2;
  case 0xACE:
    _data[0x57B] = dl;
    set_cx(_data16get(0x579));
    sub_2CB0();
    _data16set(0x563, get_ax());
    if ( _data[0x5F3] == 0 ) // jz 
      { wPos = 0xAE9; continue; }
    set_bx(0x10);
    wPos = 0xB64;
      continue;
  case 0xAE9:
    al = _data[0x56E];
    if ( al != _data16get(0x56F) ) // jnz 
      { wPos = 0xAFB; continue; }
    al = _data[0x571];
    if ( al == _data16get(0x570) ) // jz 
      { wPos = 0xB00; continue; }
  case 0xAFB:
    set_bx(0x18);
    wPos = 0xB64;
      continue;
  case 0xB00:
    _data16set(0x587, _data16get(0x587) + 1);
    set_bx(_data16get(0x587));
    al = _data[0x698];
    al |= _data16get(0x699);
    if ( !al ) // !jnz
      bl >>= 1;
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
    al = _data[0x576];
    ah = 0;
    set_ax(get_ax() >> 1);
    if ( get_ax() >= _data16get(0x574) ) // jnb 
      { wPos = 0xB53; continue; }
  case 0xB3C:
    if ( _data[0x56E] == 0 ) // jz 
      { wPos = 0xB53; continue; }
    set_bx(get_bx() & 6);
    if ( _data[0x56E] == 1 ) // jz 
      { wPos = 0xB64; continue; }
    bl |= 8;
    wPos = 0xB64;
      continue;
  case 0xB53:
    set_bx(get_bx() & 2);
    bl |= 0x10;
    if ( _data[0x571] == 1 ) // !jnz
      bl += 4;
  case 0xB64:
    set_ax(_data16get(get_bx() + 0x9A6));
    _data16set(0x55D, get_ax());
    set_ax(_data16get(get_bx() + 0x9C0));
    _data16set(0x565, get_ax());
    al = 0x30;
    set_cx(0x2BC);
    if ( _data[0x697] < 0x0FD ) // jb 
      { wPos = 0xB97; continue; }
    if ( _data[0x697] != 0x0FD ) // !jz
    {
      al = 8;
      set_cx(0x3E8);
    }
    if ( _data16get(0x57B) > al ) // ja 
      { wPos = 0xB97; continue; }
  case 0xB95:
    if ( decrement_cx() )
      { wPos = 0xB95; continue; }
  case 0xB97:
    sub_11E3();
    set_ax(_data16get(0x563));
    _data16set(0x55F, get_ax());
    sub_1145();
    sub_34A0();
    if ( unknown_condition() ) // jnb cf=0
      return -1;
    sub_1145();
    return -1;
  case 0xBAC:
    sub_1B7A();
    if ( cf ) // !jnb
      return -1;
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
    _data16set(0x55D, get_bx());
    al = _data[0x558];
    ah = _data[0x56E];
    sub_F87();
    if ( _data[0x558] != 2 ) // !jz
      sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    dl = _data[0x57B];
    set_cx(_data16get(0x579));
    sub_2CB0();
    _data16set(0x55F, get_ax());
    sub_1145();
    return -1;
  case 0xC1C:
    if ( _data[0x55C] < 1 ) // jb 
      { wPos = 0xC6A; continue; }
    if ( _data[0x55C] != 1 ) // jnz 
      { wPos = 0xC5F; continue; }
    _data[0x55C] = _data[0x55C] + 1;
    _data16set(0x572, 6);
    dl = _data[0x57B];
    set_cx(_data16get(0x579));
    sub_2CB0();
    _data16set(0x563, get_ax());
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    set_ax(_data16get(0x563));
    _data16set(0x55F, get_ax());
    _data16set(0x565, 0x0E03);
    _data16set(0x55D, 0x9DA);
    sub_1145();
  case 0xC5F:
    if ( _data[0x699] == 0 ) // !jnz
      return -1;
    wPos = 0xE78;
      continue;
  case 0xC6A:
    if ( _data[0x571] == 0 ) // !jnz
      { wPos = 0xE23; continue; }
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
    al = _data[0x578];
    cf = (_data16get(0x577) < al); // cf-insertion
    _data16set(0x577, _data16get(0x577) - al);
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
    if ( _data[0x576] < 4 ) // !jnb
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
    al = _data[0x57C];
    wPos = 0xD29;
      continue;
  case 0xCE7:
    al = _data[0x57C];
    if ( _data[0x571] == 1 ) // jz 
      { wPos = 0xD06; continue; }
    cf = (al < _data16get(0x576)); // cf-insertion
    al -= _data16get(0x576);
    if ( !cf ) // jnb 
      { wPos = 0xD4F; continue; }
    al = 0;
    _data[0x571] = 1;
    _data[0x576] = 1;
    wPos = 0xD4F;
      continue;
  case 0xD06:
    al += _data16get(0x576);
    if ( al <= 0x0E6 ) // jbe 
      { wPos = 0xD4F; continue; }
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xD22; continue; }
    if ( al < 0x0F8 ) // jb 
      { wPos = 0xD4F; continue; }
    al = 0x0F8;
    _data[0x551] = 1;
    wPos = 0xD4F;
      continue;
  case 0xD22:
    al = 0x0E6;
    _data[0x550] = 0;
  case 0xD29:
    _data[0x571] = 0;
    _data[0x584] = 0;
    _data16set(0x572, 2);
    _data[0x55B] = 0;
    _data[0x55A] = 0;
    if ( _data[0x55C] == 0 ) // jz 
      { wPos = 0xD4F; continue; }
    _push(get_ax());
    sub_5AC2();
    set_ax(_pop());
  case 0xD4F:
    _data[0x57C] = al;
    cf = (al < 0x32); // cf-insertion
    al -= 0x32;
    if ( cf ) // !jnb
      al = 0;
    _data[0x57B] = al;
    dl = _data[0x57B];
    set_cx(_data16get(0x579));
    sub_2CB0();
    _data16set(0x563, get_ax());
    if ( _data[0x583] == 0 ) // !jnz
      sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      { wPos = 0xDC4; continue; }
    sub_20F5();
    if ( cf ) // jb 
      { wPos = 0xDC4; continue; }
    set_ax(_data16get(0x563));
    _data16set(0x55F, get_ax());
    if ( _data[0x584] == 0 ) // jz 
      { wPos = 0xDA1; continue; }
    _data16set(0x585, _data16get(0x585) + 2);
    set_bx(_data16get(0x585));
    set_bx(get_bx() & 0x0E);
    set_ax(_data16get(get_bx() + 0x0FC2));
    set_bx(_data16get(get_bx() + 0x0FD2));
    wPos = 0xDA8;
      continue;
  case 0xDA1:
    set_ax(_data16get(0x569));
    set_bx(_data16get(0x567));
  case 0xDA8:
    _data16set(0x55D, get_ax());
    _data16set(0x565, get_bx());
    al = 0x32;
    zf = (al == _data16get(0x57C)); // zf-insertion
    al -= _data16get(0x57C);
    if ( zf ) // jz 
      { wPos = 0xDDE; continue; }
    cf = (al < _data16get(0x57C)); // cf-insertion
  // dummy
    if ( cf ) // jb 
      { wPos = 0xDDE; continue; }
    set_cx(0x168);
  case 0xDBC:
    if ( decrement_cx() )
      { wPos = 0xDBC; continue; }
    zf = (bh == al); // zf-insertion
    bh -= al;
    if ( zf ) // jz 
      { wPos = 0xDC4; continue; }
    cf = (bh < al); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0xDCA; continue; }
  case 0xDC4:
    _data[0x583] = 1;
    return -1;
  case 0xDCA:
    _data16set(0x565, get_bx());
    ah = bl;
    ah <<= 1;
    set_ax(ah * al);
    set_ax(get_ax() + _data16get(0x569));
    _data16set(0x55D, get_ax());
    wPos = 0xE1F;
      continue;
  case 0xDDE:
    if ( _data16get(4) != 7 ) // jnz 
      { wPos = 0xDEE; continue; }
    al = _data[0x57B];
    cf = (al < 0x0BB); // cf-insertion
    al -= 0x0BB;
    if ( cf ) // jb 
      { wPos = 0xE1F; continue; }
    cf = (al < 0x0BB); // cf-insertion
  // dummy
    if ( !cf ) // jnb 
      { wPos = 0xDFC; continue; }
  case 0xDEE:
    if ( _data[0x550] != 2 ) // jnz 
      { wPos = 0xE1F; continue; }
    al = _data[0x57B];
    cf = (al < 0x5E); // cf-insertion
    al -= 0x5E;
    if ( cf ) // jb 
      { wPos = 0xE1F; continue; }
  case 0xDFC:
    zf = (bh == al); // zf-insertion
    bh -= al;
    if ( zf ) // jz 
      { wPos = 0xE02; continue; }
    cf = (bh < al); // cf-insertion
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
    _data16set(0x565, get_bx());
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
    if ( _data[0x56C] == 0 ) // !jnz
      sub_591F();
    _data[0x699] = 1;
    _data[0x56C] = 1;
    sub_2DFD();
    dl &= 1;
    if ( !dl ) // !jnz
      dl = 0x0FF;
    _data[0x698] = dl;
	if ( _data[0x698] == 0 ) unknown_condition();
  case 0xE78:
    al = _data[0x56E];
    _data[0x56F] = al;
    al = _data[0x698];
    _data[0x56E] = al;

    al = _data[0x699];
    _data[0x571] = al;
    if ( al == 0 ) // !jnz
      { wPos = 0xF34; continue; }
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
    ah = 1;
    al = 0x20;
    _data[0x55B] = 8;
    if ( _data[0x550] != 1 ) // jnz 
      { wPos = 0xEF1; continue; }
    _data[0x550] = 0;
    wPos = 0xEF1;
      continue;
  case 0xEC9:
    _data[0x55B] = 0;
    set_ax(_data16get(0x572));
    bl = al;
    if ( al > 2 ) // !jbe
      al -= 2;
    _data16set(0x572, get_ax());
    ah = 8;
    al = bl;
    al = al ^ 0x0F;
    cl = 4;
    al <<= cl;
    if ( _data[0x550] == 1 ) // !jnz
      _data[0x550] = _data[0x550] + 1;
  case 0xEF1:
    _data[0x578] = al;
    _data[0x576] = ah;
    _data[0x577] = 1;
    _data[0x55C] = 0;
    bl = _data[0x56E];
    bl = bl + 1;
    bl <<= 1;
    if ( _data[0x571] != 0x0FF ) // !jz
      bl += 6;
    bh = 0;
    set_ax(_data16get(get_bx() + 0x0FAA));
    _data16set(0x569, get_ax());
    set_ax(_data16get(get_bx() + 0x0FB6));
    _data16set(0x567, get_ax());
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
    dl = _data[0x57B];
    set_cx(_data16get(0x579));
    sub_2CB0();
    _data16set(0x563, get_ax());
    al = _data[0x56E];
    al |= _data16get(0x571);
    if ( !al ) // !jnz
    {
      sub_1069();
      return -1;
    }
    sub_1020();
    _data16set(0x55D, get_bx());
    sub_11E3();
    sub_1B7A();
    if ( cf ) // jb 
      return -1;
    sub_20F5();
    if ( cf ) // jb 
      return -1;
    set_ax(_data16get(0x563));
    _data16set(0x55F, get_ax());
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
    set_cx(0x0B03);
    cl -= al;
    _data16set(0x565, get_cx());
    if ( ah == 0x0FF ) // jz 
      { wPos = 0xFA6; continue; }
    ah = 0;
    al <<= 1;
    _data16set(0x55D, _data16get(0x55D) + get_ax());
    _data16set(0x579, 0);
    wPos = 0xFB4;
      continue;
  case 0xFA6:
    ah = 0;
    al <<= 1;
    al <<= 1;
    al <<= 1;
    set_ax(get_ax() + 0x128);
    _data16set(0x579, get_ax());
  case 0xFB4:
    _push(ds);
    es = _pop();
    si = _data16get(0x55D);
    di = 0x0E;
    al = 3;
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
    set_ax(_data16get(0x579));
    if ( _data[0x56E] < 1 ) // jb 
      { wPos = 0x101E; continue; }
    if ( _data[0x56E] != 1 ) // jnz 
      { wPos = 0x1007; continue; }
    set_ax(get_ax() + _data16get(0x572));
    if ( get_ax() < _data16get(0x5F8) ) // jb 
      { wPos = 0x101B; continue; }
    set_ax(_data16get(0x5F8));
    set_ax(get_ax() -1);
    _data16set(0x579, get_ax());
    _stc();
    return -1;
  case 0x1007:
    cf = (get_ax() < _data16get(0x572)); // cf-insertion
    set_ax(get_ax() - _data16get(0x572));
    if ( cf ) // jb 
      { wPos = 0x1013; continue; }
    if ( get_ax() >= _data16get(0x5F6) ) // jnb 
      { wPos = 0x101B; continue; }
  case 0x1013:
    set_ax(_data16get(0x5F6));
    _data16set(0x579, get_ax());
    _stc();
    return -1;
  case 0x101B:
    _data16set(0x579, get_ax());
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
    al = _data[0x56E];
    if ( al == _data16get(0x56F) ) // jz 
      { wPos = 0x102F; continue; }
    _data16set(0x572, 2);
  case 0x102F:
    if ( _data16get(0x572) >= 8 ) // jnb 
      { wPos = 0x1045; continue; }
    _data[0x577]--;
    al = _data[0x577];
    al &= 3;
    if ( !al ) // !jnz
      _data16set(0x572, _data16get(0x572) + 1);
  case 0x1045:
    bl = _data[0x56B];
    bl = bl + 1;
    if ( bl >= 6 ) // !jb
      bl = 0;
    _data[0x56B] = bl;
    if ( _data[0x56E] == 0x0FF ) // !jnz
      bl += 6;
    bl <<= 1;
    bh = 0;
    set_bx(_data16get(get_bx() + 0x0F7A));
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
    bl = dl;
    set_bx(get_bx() & 0x0E);
    si = _data16get(get_bx() + 0x0F92);
    set_ax(0x0B800);
    es = get_ax();
    di = _data16get(0x55F);
    bp = 0x5FA;
    _data16set(0x561, 0x0C02);
    set_cx(0x602);
    sub_2D35();
    sub_2DFD();
    bl = dl;
    set_bx(get_bx() & 6);
    si = _data16get(get_bx() + 0x0FA2);
    di = _data16get(0x55F);
    di += 0x0F0;
    bp = 0x612;
    set_cx(0x602);
    sub_2D35();
    _data[0x583] = 0;
    wPos = -1;
  }
}
function sub_1124()
{
  set_ax(seg_data);
  es = get_ax();
  di = 0x5FA;
  _push(ds);
  si = _data16get(0x55F);
  set_ax(0x0B800);
  ds = get_ax();
  set_cx(_data16get(es*16+0x561));
  sub_2DCA();
  ds = _pop();
  _data[0x583] = 0;
}
function sub_1145()
{
  set_ax(0x0B800);
  es = get_ax();
  di = _data16get(0x55F);
  bp = 0x5FA;
  si = _data16get(0x55D);
  set_cx(_data16get(0x565));
  _data16set(0x561, get_cx());
  _data[0x583] = 0;
  sub_2D35();
}
function sub_11E3()
{
  set_ax(0x0B800);
  es = get_ax();
  di = _data16get(0x55F);
  si = 0x5FA;
  set_cx(_data16get(0x561));
  sub_2D9D();
}
function sub_13AA()
{
  set_ax(0x0F000);
  es = get_ax();
  al = 0xff;
  _data[0x697] = al;
}
function sub_13E8()
{
  _push(get_ax());
  _push(es);
  _push(di);
  _push(get_cx());
  set_ax(seg_data);
  es = get_ax();
  _cld();
  di = 0x6B7;
  set_cx(0x16);
  al = 0x80;
  _rep_stosb();
  set_ax(_data16get(es*16+0x693));
  set_ax(get_ax() - 0x70);
  _data16set(es*16+0x691, get_ax());
  set_ax(0x40);
  es = get_ax();
  al = _data[es*16+0x12];
  set_cx(_pop());
  di = _pop();
  es = _pop();
  set_ax(_pop());
}
function sub_1419()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    set_ax(0);
    es = get_ax();
    set_ax(_data16get(es*16+0x24));
    set_bx(_data16get(es*16+0x26));
    set_cx(_data16get(es*16+0x120));
    set_dx(_data16get(es*16+0x122));
    set_bx(0x14B3);
    if ( _data[0x697] == 0x0FD ) // !jnz
      set_bx(0x14FB);
    _cli();
    _data16set(es*16+0x24, get_bx());
    _data16set(es*16+0x26, cs);
    if ( _data[0x697] != 0x0FD ) // jnz 
      { wPos = 0x147D; continue; }
  //  _data16set(es*16+0x120, &loc_code_1554);
    _data16set(es*16+0x122, cs);
    set_ax(0x40);
    es = get_ax();
    al = _data[es*16+0x18];
    al |= 1;
    _data[es*16+0x18] = al;
  case 0x147D:
    _sti();
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
    return -1;
  case 0x1613:
    if ( _data16get(4) == 0 ) // jz 
      { wPos = 0x161E; continue; }
    sub_16C6();
    return -1;
  case 0x161E:
    al = _data[0x57B];
    al &= 0x0F8;
    if ( al == 0x60 ) // jz 
      { wPos = 0x1630; continue; }
    sub_1657();
    if ( unknown_condition() ) // jb cf=1
      return -1;
    sub_17AD();
    return -1;
  case 0x1630:
    if ( _data[0x550] >= 2 ) // jnb 
      { wPos = 0x1655; continue; }
    _data[0x57B] = al;
    al += 0x32;
    _data[0x57C] = al;
    if ( _data[0x550] == 1 ) // jz 
      { wPos = 0x1653; continue; }
    _data[0x550] = 1;
    ah = 0;
    _int(0x1A);
    _data16set(0x556, get_dx());
  case 0x1653:
    _stc();
    return -1;
  case 0x1655:
    _clc();
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
function sub_1B7A()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data16get(4) != 0 ) // jnz 
      { wPos = 0x1BE1; continue; }
    dl = _data[0x1673];
    if ( dl == 0 ) // jz 
      { wPos = 0x1BE1; continue; }
    set_cx(_data16get(0x17DF));
    _xchg(cl, ch);
    si = 0x10;
    set_ax(_data16get(0x1671));
    set_bx(_data16get(0x579));
    dh = _data[0x57B];
    di = 0x18;
    ch = 0x0E;
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
    dl = 1;
    if ( _data[0x1674] != 0x0FF ) // !jz
      dl = 0x0FF;
    _data[0x1674] = dl;
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
    ah = 0x0B;
    bh = 1;
    si = _data16get(4);
    bl = _data[si + 0x1853];
    _int(0x10);
    wPos = 0x1D67;
      continue;
  case 0x1D48:
    si = _data16get(4);
    bl = 1;
    bh = _data[si + 0x183B];
    sub_1D6E();
    bl = 2;
    bh = _data[si + 0x1843];
    sub_1D6E();
    bl = 3;
    bh = _data[si + 0x184B];
    sub_1D6E();
  case 0x1D67:
    ah = 0x0B;
    set_bx(0);
    _int(0x10);
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
function sub_20F5()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    if ( _data[0x1CB8] != 0 ) // jnz 
      { wPos = 0x2134; continue; }
    al = _data[0x1CBF];
    al |= _data16get(0x1CC0);
    al |= _data16get(0x1CC1);
    if ( !al ) // jz 
      { wPos = 0x2134; continue; }
    if ( _data[0x57B] < 0x0A3 ) // jb 
      { wPos = 0x2134; continue; }
    if ( _data[0x558] != 0 ) // jnz 
      { wPos = 0x2134; continue; }
    set_ax(_data16get(0x1CC6));
    set_ax(get_ax() + 0x20);
    if ( get_ax() < _data16get(0x579) ) // jb 
      { wPos = 0x2134; continue; }
    cf = (get_ax() < 0x38); // cf-insertion
    set_ax(get_ax() - 0x38);
    if ( cf ) // !jnb
      set_ax(0);
    if ( get_ax() > _data16get(0x579) ) // ja 
      { wPos = 0x2134; continue; }
    sub_2136();
    return -1;
  case 0x2134:
    _clc();
    wPos = -1;
  }
}
function sub_22F7()
{
  if ( _data[0x1D59] == 0 ) // !jnz
  {
    _clc();
    return -1;
  }
  set_cx(_data16get(0x1D64));
  _xchg(ch, cl);
  set_ax(_data16get(0x1D5C));
  dl = _data[0x1D5F];
  si = 0x10;
  set_bx(_data16get(0x579));
  dh = _data[0x57B];
  di = 0x18;
  ch = 0x0E;
  sub_2E29();
  if ( unknown_condition() ) // jnb cf=0
    return -1;
  _data[0x1D58] = 1;
}
function sub_2330()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _data16set(0x1F6C, 0);
    set_ax(0);
    dl = 1;
    if ( _data16get(0x579) > 0x0A0 ) // ja 
      { wPos = 0x2347; continue; }
    set_ax(0x12C);
    dl = 0x0FF;
  case 0x2347:
    _data16set(0x1F30, get_ax());
    _data16set(0x1F32, get_ax());
    _data16set(0x1F34, get_ax());
    _data[0x1F3C] = dl;
    _data[0x1F3D] = dl;
    _data[0x1F3E] = dl;
    _data[0x1F48] = 1;
    _data[0x1F49] = 1;
    _data[0x1F4A] = 1;
    _data[0x1F50] = 0;
    _data[0x1F51] = 0;
    _data[0x1F52] = 0;
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
    set_cx(7);
    si = 0x1F82;
  case 0x2698:
    _lodsb();
    set_bx(7);
    set_bx(get_bx() - get_cx());
    if ( decrement_cx() && (al == _data16get(get_bx() + 0x1F89)) )
      { wPos = 0x2698; continue; }
    if ( al > _data16get(get_bx() + 0x1F89) ) // ja 
      { wPos = 0x26A7; continue; }
    return -1;
  case 0x26A7:
    si = 0x1F82;
    di = 0x1F89;
    set_cx(7);
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
    al = _data[0x1F80];
    if ( al != _data16get(0x1F81) ) // jnz 
      { wPos = 0x26BD; continue; }
    return -1;
  case 0x26BD:
    _data[0x1F81] = al;
    ah = 0;
    cl = 4;
    set_ax(get_ax() << cl);
    set_ax(get_ax() + 0x2720);
    si = get_ax();
    set_ax(0x0B800);
    es = get_ax();
    di = 0x1260;
    set_cx(0x801);
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
  set_cx(7);
  al = 0;
  _rep_stosb();
}
function sub_26F2()
{
  set_bx(0x1F89);
  di = 0x12CA;
  sub_2739();
}
function sub_26FC()
{
  set_bx(0x1F82);
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
    set_ax(0x0B800);
    es = get_ax();
    _data16set(0x1F90, di);
    _data16set(0x1F93, get_bx());
    _data[0x1F92] = 0;
  case 0x274B:
    set_bx(_data16get(0x1F93));
    al = _data[get_bx()];
    ah = 0;
    cl = 4;
    set_ax(get_ax() << cl);
    set_ax(get_ax() + 0x2720);
    si = get_ax();
    di = _data16get(0x1F90);
    set_cx(0x801);
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
}
function sub_2A30()
{
  set_ax(0x0B800);
  es = get_ax();
  _cld();
  di = 0;
  set_ax(0x0AAAA);
  set_cx(0x0FA0);
  _rep_stosw();
  di = 0x2000;
  set_cx(0x0FA0);
  _rep_stosw();
  sub_2B9E();
  set_bx(0x28A0);
  set_ax(0);
  sub_2B24();
  sub_2A68();
  set_ax(_data16get(8));
  _push(get_ax());
  _data16set(8, 1);
  sub_2C84();
  set_ax(_pop());
  _data16set(8, get_ax());
}
function sub_2A68()
{
  set_bx(_data16get(0x6DF8));
  set_bx(get_bx() & 3);
  bl <<= 1;
  si = _data16get(get_bx() + 0x2AD1);
  di = 0x1902;
  set_cx(0x801);
  sub_2D9D();
}
function sub_2B24()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    set_cx(_data16get(get_bx()));
    _data16set(0x2AC7, get_cx());
    _data16set(0x2ACC, get_ax());
    set_bx(get_bx() + 2);
  case 0x2B30:
    si = _data16get(get_bx());
    if ( si == 0x0FFFF ) // !jnz
      return -1;
    di = _data16get(get_bx() + 2);
    di += _data16get(0x2ACC);
    _cld();
    _data[0x2AD0] = ch;
    ch = 0;
    _data16set(0x2ACE, get_cx());
  case 0x2B4B:
    set_cx(_data16get(0x2ACE));
    _rep_movsb();
    di -= _data16get(0x2ACE);
    di = di ^ 0x2000;
    if ( !(di & 0x2000) ) // !jnz
      di += 0x50;
    _data[0x2AD0]--;
    if ( _data[0x2AD0] ) // jnz 
      { wPos = 0x2B4B; continue; }
    set_bx(get_bx() + 4);
    set_cx(_data16get(0x2AC7));
    wPos = 0x2B30;
      continue;
    wPos = -1;
  }
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
    set_dx(get_dx() & 0x30);
    if ( dl == _data16get(0x2AC4) ) // jz 
      { wPos = 0x2BB3; continue; }
    _data[0x2AC4] = dl;
    set_dx(get_dx() + 0x2904);
    si = get_dx();
    set_cx(0x801);
    sub_2D9D();
    wPos = 0x2BA4;
      continue;
  case 0x2BD2:
    di = 0x1180;
    set_ax(0x5655);
    set_cx(0x500);
    _cld();
    _rep_stosw();
    di = 0x3180;
    set_cx(0x500);
    _rep_stosw();
    _data16set(0x2AC2, 0x2944);
  case 0x2BEC:
    _data[0x2AC4] = 9;
  case 0x2BF1:
    sub_2DFD();
    set_dx(get_dx() & 0x776);
    set_dx(get_dx() + 0x12C0);
    di = get_dx();
    si = _data16get(0x2AC2);
    set_cx(0x501);
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
    set_dx(get_dx() & 0x3E);
    set_dx(get_dx() + 0x3A98);
    di = get_dx();
    si = 0x296C;
    set_cx(0x501);
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
    al = 3;
    if ( di >= 0x1720 ) // !jb
      al--;
    _data[0x2AC4] = al;
    _data16set(0x2AC2, _data16get(0x2AC2) + 0x1E0);
    si = 0x2976;
    set_cx(0x0C05);
    sub_2D9D();
  case 0x2C5D:
    di = _data16get(0x2AC2);
    _data16set(0x2AC2, _data16get(0x2AC2) + 0x140);
    si = 0x29EE;
    set_cx(0x804);
    sub_2D9D();
    _data[0x2AC4]--;
    if ( _data[0x2AC4] ) // jnz 
      { wPos = 0x2C5D; continue; }
    di = _data16get(0x2AC2);
    si = 0x2A2E;
    set_cx(0x0B04);
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
    set_bx(_data16get(8));
    bl = _data[get_bx() + 0x2AB2];
  case 0x2C8C:
    _data16set(0x2AC5, get_bx());
    di = _data16get(get_bx() + 0x2A86);
    if ( di == 0 ) // !jnz
      return -1;
    sub_2C3D();
    set_bx(_data16get(0x2AC5));
    set_bx(get_bx() + 2);
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
    al = dl;
    ah = 0x28;
    set_ax(ah * al);
    if ( !(dl & 1) ) // jz 
      { wPos = 0x2CBE; continue; }
    set_ax(get_ax() + 0x1FD8);
  case 0x2CBE:
    set_dx(get_cx());
    set_dx(get_dx() >> 1);
    set_dx(get_dx() >> 1);
    set_ax(get_ax() + get_dx());
    cl &= 3;
    cl <<= 1;
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
    _data[0x2AE0] = cl;
    _data[0x2AE2] = ch;
    ch = 0;
  case 0x2D40:
    cl = _data[0x2AE0];
  case 0x2D44:
    set_bx(_video16get(0*es*16+di));
    _data16set(bp+0, get_bx());
    _lodsw();
    set_ax(get_ax() & get_bx());
    _stosw();
    bp += 2;
    if ( decrement_cx() )
      { wPos = 0x2D44; continue; }
    di -= _data16get(0x2AE0);
    di -= _data16get(0x2AE0);
    di = di ^ 0x2000;
    if ( !(di & 0x2000) ) // !jnz
      di += 0x50;
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
    _data[0x2AE0] = cl;
    _data[0x2AE2] = ch;
    al <<= 1;
    _data[0x2AEB] = al;
    ch = 0;
  case 0x2D84:
    cl = _data[0x2AE0];
    _rep_movsw();
    cl = _data[0x2AEB];
    _data16set(0x2AE9, _data16get(0x2AE9) + get_cx());
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
    _data[0x2AE0] = cl;
    _data[0x2AE2] = ch;
    ch = 0;
  case 0x2DA8:
    cl = _data[0x2AE0];
    _rep_movsw();
    di -= _data16get(0x2AE0);
    di -= _data16get(0x2AE0);
    di = di ^ 0x2000;
    if ( !(di & 0x2000) ) // !jnz
      di += 0x50;
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
    _data[es*16+0x2AE0] = cl;
    _data[es*16+0x2AE2] = ch;
    ch = 0;
  case 0x2DD7:
    cl = _data[es*16+0x2AE0];
    _rep_movsw();
    si -= _data16get(es*16+0x2AE0);
    si -= _data16get(es*16+0x2AE0);
    si = si ^ 0x2000;
    if ( !(si & 0x2000) ) // !jnz
      si += 0x50;
    _data[es*16+0x2AE2]--;
    if ( _data[es*16+0x2AE2] ) // jnz 
      { wPos = 0x2DD7; continue; }
    wPos = -1;
  }
}
function sub_2DFD()
{
  set_dx(_data16get(0x2AE5));
  dl = dl ^ dh;
  dl >>= 1;
  cf = dl & 1 ? 1 : 0;
  dl >>= 1;
  var w = _data16get(0x2AE5);
  w = _rcr(w, 1);
  _data16set(0x2AE5, w);
  set_dx(_data16get(0x2AE5));
}
function sub_2E10()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    al = 0;
    _out(0x43, al);
    _in(al, 0x40);
    ah = al;
    _in(al, 0x40);
    if ( get_ax() != 0 ) // jnz 
      { wPos = 0x2E25; continue; }
    set_ax(0x0FA59);
  case 0x2E25:
    _data16set(0x2AE5, get_ax());
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
function sub_5C60()
{
  var wPos = 0;
  while (wPos != -1)
  switch (wPos)
  {
    case 0:
    _int(0x11);
    al &= 0x30;
    if ( al != 0x30 ) // jnz 
      return -1;
    set_ax(0x0B800);
    ds = get_ax();
    set_ax(0x55AA);
    _data16set(0, get_ax());
    set_ax(_data16get(0));
    if ( get_ax() != 0x55AA ) // jnz 
      { wPos = 0x5C96; continue; }
    si = 0x60F0;
    sub_5C9E();
    set_ax(0x40);
    ds = get_ax();
    set_ax(_data16get(0x10));
    al &= 0x0CF;
    al |= 0x10;
    _data16set(0x10, get_ax());
    set_ax(4);
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
    set_ax(0x0B800);
    es = get_ax();
    si = 0x6152;
    set_cx(0x1D0B);
    di = 0x0BD;
    sub_2D9D();
    si = 0x63D0;
    set_cx(0x160E);
    di = 0x69E;
    sub_2D9D();
    si = 0x6638;
    set_cx(0x0C03);
    di = 0x0A78;
    sub_2D9D();
    si = 0x6680;
    set_cx(0x80E);
    di = 0x0CA8;
    sub_2D9D();
    si = 0x6760;
    set_cx(0x0B0C);
    di = 0x1D6E;
    sub_2D9D();
    si = 0x6868;
    set_cx(0x804);
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
    set_ax(_data16get(0x693));
    _data16set(0x6150, get_ax());
  case 0x5D54:
    ah = 0;
    _int(0x1A);
    _data16set(0x6A8B, get_dx());
    _data16set(0x5322, get_dx());
    _data16set(0x6A93, get_dx());
    set_dx(get_dx() - 0x30);
    _data16set(0x6A88, get_dx());
    _data16set(0x5320, 0);
  case 0x5D71:
    ah = 0;
    _int(0x1A);
    set_ax(get_dx());
    set_ax(get_ax() - _data16get(0x6A93));
    if ( get_ax() < 0x24 ) // jb 
      { wPos = 0x5D89; continue; }
    _data16set(0x6A93, get_dx());
    _push(get_dx());
    sub_5E3B();
    set_dx(_pop());
  case 0x5D89:
    set_dx(get_dx() - _data16get(0x6A8B));
    set_ax(_data16get(0x56DA));
    if ( _data[0x41A] == 0 ) // jz 
      { wPos = 0x5DA0; continue; }
    set_ax(get_ax() + 0x48);
    if ( get_dx() >= get_ax() ) // jnb 
      { wPos = 0x5D54; continue; }
    wPos = 0x5DA7;
      continue;
  case 0x5DA0:
    set_ax(get_ax() + 6);
    if ( get_dx() > get_ax() ) // ja 
      return -1;
  case 0x5DA7:
    sub_53B0();
    sub_5DD4();
    if ( _data[0x69B] == 0 ) // jz 
      { wPos = 0x5DCA; continue; }
    set_dx(0x201);
    _in(al, get_dx());
    al &= 0x10;
    if ( !al ) // jz 
      { wPos = 0x5DC3; continue; }
    _data[0x6A8A] = 1;
    wPos = 0x5DCA;
      continue;
  case 0x5DC3:
    if ( _data[0x6A8A] != 0 ) // jnz 
      return -1;
  case 0x5DCA:
//    Sleep(5);
//    tick();
    set_ax(_data16get(0x6150));
    if ( get_ax() == _data16get(0x693) ) // jz 
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
    ah = 0;
    _int(0x1A);
    set_ax(get_dx());
    set_ax(get_ax() - _data16get(0x6A88));
    if ( get_ax() < 0x12 ) // jb 
      { wPos = 0x5E1C; continue; }
    _data16set(0x6A88, get_dx());
    sub_2DFD();
    _data[0x698] = 0;
    if ( dl > 0x0A0 ) // ja 
      { wPos = 0x5E1C; continue; }
    dl &= 1;
    if ( !dl ) // !jnz
      dl = 0x0FF;
    _data[0x698] = dl;
  case 0x5E1C:
    _data16set(0x572, 4);
    sub_8E5();
    wPos = -1;
  }
}
function sub_5E3B()
{
  set_ax(0x0B800);
  es = get_ax();
  _data16set(0x6A8D, _data16get(0x6A8D) + 2);
  set_bx(_data16get(0x6A8D));
  set_bx(get_bx() & 2);
  si = _data16get(get_bx() + 0x6A8F);
  set_cx(0x0C0A);
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
    set_ax(_data16get(0x693));
  case 0x5EF7:
    if ( get_ax() == _data16get(0x693) ) // jz 
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
    set_cx(5);
  case 0x5F1F:
    _push(get_cx());
    sub_5FB1();
    set_cx(_pop());
    if ( decrement_cx() )
      { wPos = 0x5F1F; continue; }
  case 0x5F26:
    set_ax(_data16get(0x693));
  case 0x5F29:
    if ( get_ax() == _data16get(0x693) ) // jz 
      { wPos = 0x5F29; continue; }
    set_ax(0);
    if ( !(_data[0x6C3] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    set_ax(get_ax() + 1);
    if ( !(_data[0x6C4] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    set_ax(get_ax() + 1);
    if ( !(_data[0x6C5] & 0x80) ) // jz 
      { wPos = 0x5F50; continue; }
    set_ax(get_ax() + 1);
    if ( _data[0x6C6] & 0x80 ) // jnz 
      { wPos = 0x5F26; continue; }
  case 0x5F50:
    _data16set(0x6DF8, get_ax());
    set_cx(5);
  case 0x5F56:
    _push(get_cx());
    sub_5FB1();
    set_cx(_pop());
    if ( decrement_cx() )
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
//function sub_2E10() {}
function sub_3445() {}
function sub_58F8() {}
function sub_591F() {}
