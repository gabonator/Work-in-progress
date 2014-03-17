var word_code_D93 = 0;
var byte_code_D95 = 0;
var byte_code_D96 = 0;
_pc_103 = 0;
_pc_A9 = 0;
_pc_CF = 0;

function pcvalid()
{ 
  if ( typeof(_pc_103) == "undefined" ) return false;
  if ( typeof(_pc_A9) == "undefined" ) return false;
  return true;
}

function start(_pc)
{
  while (1)
  switch (_pc)
  {
    case 0:
    STAT(0);
    r16[ax] = seg_dseg;
    ds = r16[ax];
    r16[bx] = 0x9670;
    r16[bx] += 0x0F;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[ax] += r16[bx];
    _data16set(0x94E8, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94EA, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94EC, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94EE, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94F0, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94F2, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94F4, r16[ax]);
    r16[ax] += 0x800;
    _data16set(0x94F6, r16[ax]);
    _int(0x12);
    if ( r16[ax] >= 0x200 ) // jnb 
      { _pc = 0x67; break; }
    r16[dx] = 7;
    r8[ah] = 9;
    _int(0x21);
    r16[ax] = 0x4C00;
    _int(0x21);
    _pc = 0x6E;
      break;
  case 0x67:
    r16[dx] = 0x2A;
    r8[ah] = 9;
    _int(0x21);
  case 0x6E:
    sub_600();
    sub_333C();
    sub_2762();
    sub_5EC();
    sub_442();
    sub_588();
    sub_591();
    sub_382A();
    _data[0x9501] = 0;
  case 0x8B:
    _pc_A9 = 0;
  case 0x10008B:
    _pc_A9 = sub_A9(_pc_A9);
    if ( _pc_A9 != -1 )
      return 0x10008B;
    _pc_CF = 0;

  case 0x11008B:
    _pc_CF = sub_CF(_pc_CF);
    if ( _pc_CF != -1 )
      return 0x11008B;

    sub_FD();
    _pc = 0x8B;
    break;
  }
  return _pc;
}
function sub_A9(_pc)
{
  switch (_pc)
  {
    case 0:
  _pc_103 = 0;
    case 0x100000:
  _pc_103 = sub_103(_pc_103);
  if ( _pc_103 != -1 )
    return 0x100000;

    case 1:
  _data[0x9500] = 0;
  _data[0x94FE] = 1;
  _data[0x94FC] = 0x10;
  _data[0x94FF] = 0;
  _data[0x9502] = 0;
  sub_DA7();
  sub_3423();
  sub_21DC();
  }
  return -1;
}
function sub_CF(_pc)
{
//  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xCF);
  case 0xCF:
    sub_1C0();
    sub_FDA();
    r8[al] = _data[0x94FF];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0xE4; continue; }
    sub_32FE();
    sub_B8E();
    _pc = 0xED;
    return _pc;
      continue;
  case 0xE4:
    sub_34A8();
    sub_31A4();
    sub_B8E();
  case 0xED:
    // TODO: hit testing 
    /////////////////
    //sub_220D(); // <--- problem!
    sub_3383();
    r8[al] = _data[0x9500];
    if ( r8[al] != 0 ) // jnz 
      return -1;
    _pc = 0xCF;
      return _pc;
      continue;
    _pc = -1;
  }
  return _pc;
}
function sub_FD()
{
  STAT(0xFD);
  _data[0x6] = 1;
}
function sub_103(_pc)
{
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x103);
    r8[al] = _data[0x6];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x115; continue; }
    _data16set(0x8E7E, 0x0DA);
    sub_279F();
    _pc = 0x11E;
      continue;
  case 0x115:
    _data16set(0x8E7E, 0x0E9);
    sub_28DA();
  case 0x11E:
    sub_39B8();
    sub_3472();
    _data[0x9503] = 1;
    _data16set(0x8E80, 0);
    sub_D98();
  case 0x132:
    return 0x100132;
  case 0x100132:
    sub_1C0();
    sub_FDA();
    sub_3498();
    //tick();
    sub_B8E();
    sub_3383();
    r16[ax] = _data16get(0x954C);
    if ( r16[ax] & 0x80 ) // jnz 
      { _pc = 0x197; continue; }
    _data16set(0x8E80, _data16get(0x8E80) + 1);
    r16[bx] = _data16get(0x8E80);
    if ( r16[bx] & 7 ) // jnz 
      { _pc = 0x195; continue; }
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] += _data16get(0x8E7E);
    r8[al] = _data[r16[bx]];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x195; continue; }
    if ( r8[al] == 0x0FF ) // jz 
      { _pc = 0x197; continue; }
    if ( r8[al] != 0x0FE ) // jnz 
      { _pc = 0x180; continue; }
    r8[al] = _data[0x9546];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x17B; continue; }
    sub_29DB();
    _pc = 0x17E;
      continue;
  case 0x17B:
    sub_1AD();
  case 0x17E:
    _pc = 0x195;
      continue;
  case 0x180:
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0x189; continue; }
    sub_19D();
    _pc = 0x195;
      continue;
  case 0x189:
    r8[al] &= 0x3F;
    _push(r16[ax]);
    sub_19D();
    r16[ax] = _pop();
    r8[al] = r8[al] + 1;
    sub_19D();
  case 0x195:
    _pc = 0x132;
      continue;
  case 0x197:
    _data[0x9503] = 0;
    _pc = -1;
  }
  return _pc;
}
function sub_19D()
{
  STAT(0x19D);
  si = 0x109;
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x120;
  sub_2121();
  sub_B58();
}
function sub_1AD()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1AD);
    r16[cx] = 0x1F40;
  case 0x1B0:
    _push(r16[cx]);
    sub_1C0();
    r16[cx] = _pop();
    r16[ax] = _data16get(0x954C);
    if ( !(r8[al] & 0x80) ) // jz 
      { _pc = 0x1BD; continue; }
    return;
  case 0x1BD:
    if ( --r16[cx] )
      { _pc = 0x1B0; continue; }
    _pc = -1;
  }
}
function sub_1C0()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1C0);
    r16[bx] = 0x8E8A;
    si = 0x3D;
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x1D5; continue; }
    si = 0x3E;
  case 0x1CF:
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x1CF; continue; }
  case 0x1D5:
    si = 0x3B;
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x1E1; continue; }
    sub_33B();
  case 0x1E1:
    r16[bx] = 0x8E8A;
    si = _data16get(0x8F0D);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x1F6; continue; }
    _data16set(0x954C, 1);
    _pc = 0x20E;
      continue;
  case 0x1F6:
    si = _data16get(0x8F0F);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x208; continue; }
    _data16set(0x954C, 2);
    _pc = 0x20E;
      continue;
  case 0x208:
    _data16set(0x954C, 0);
  case 0x20E:
    si = _data16get(0x8F11);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x21F; continue; }
    _data16set(0x954C, _data16get(0x954C) | 4);
    _pc = 0x22E;
      continue;
  case 0x21F:
    si = _data16get(0x8F13);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x22E; continue; }
    _data16set(0x954C, _data16get(0x954C) | 8);
  case 0x22E:
    si = _data16get(0x8F15);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x23E; continue; }
    _data16set(0x954C, _data16get(0x954C) | 0x80);
  case 0x23E:
    si = _data16get(0x8F17);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x24D; continue; }
    _data16set(0x954C, _data16get(0x954C) | 0x40);
  case 0x24D:
    si = _data16get(0x8F19);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x25C; continue; }
    _data16set(0x954C, _data16get(0x954C) | 0x20);
  case 0x25C:
    si = _data16get(0x8F1B);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x28C; continue; }
    sub_2C45();
    r16[bx] = 0x8E8A;
  case 0x26C:
    tick();
    r8[al] = _data[OFS(r16[bx] + 0x15)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x27C; continue; }
    r8[al] = _data[OFS(r16[bx] + 0x31)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x27C; continue; }
    _pc = 0x26C;
      continue;
  case 0x27C:
    r16[bx] = 0x8E8A;
    r8[al] = _data[OFS(r16[bx] + 0x15)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x289; continue; }
    _pc = 0x96;
      continue;
  case 0x289:
    sub_529();
  case 0x28C:
    r16[bx] = 0x8E8A;
    si = 0x3C;
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x2C5; continue; }
    r8[al] = _data[0x9505];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x2B0; continue; }
    r8[al] = 0x0E;
    sub_3840();
    _data[0x9505] = 1;
    _data[0x9506] = 0;
    _pc = 0x2C3;
      continue;
  case 0x2B0:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x2C3; continue; }
    _data[0x9505] = 3;
    _data[0x9506] = 1;
    r8[al] = 0x0D;
    sub_3840();
  case 0x2C3:
    _pc = 0x2DC;
      continue;
  case 0x2C5:
    r8[al] = _data[0x9505];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x2D3; continue; }
    _data[0x9505] = 2;
    _pc = 0x2DC;
      continue;
  case 0x2D3:
    if ( r8[al] != 3 ) // jnz 
      { _pc = 0x2DC; continue; }
    _data[0x9505] = 0;
  case 0x2DC:
    r8[al] = _data[0x8F0A];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x2E4; continue; }
    return;
  case 0x2E4:
    r16[ax] = 3;
    _int(0x33);
    if ( !(r16[bx] & 1) ) // jz 
      { _pc = 0x2F5; continue; }
    _data16set(0x954C, _data16get(0x954C) | 0x80);
  case 0x2F5:
    if ( !(r16[bx] & 2) ) // jz 
      { _pc = 0x300; continue; }
    _data16set(0x954C, _data16get(0x954C) | 0x20);
  case 0x300:
    r16[ax] = _data16get(0x954C);
    r16[ax] &= 0x0F;
    if ( !r16[ax] ) // jz 
      { _pc = 0x309; continue; }
    return;
  case 0x309:
    r16[ax] = 0x0B;
    _int(0x33);
    if ( _short(r16[cx]) >= _short(0x0FFFB) ) // jge 
      { _pc = 0x31A; continue; }
    _data16set(0x954C, _data16get(0x954C) | 1);
    _pc = 0x324;
      continue;
  case 0x31A:
    if ( _short(r16[cx]) <= _short(5) ) // jle 
      { _pc = 0x324; continue; }
    _data16set(0x954C, _data16get(0x954C) | 2);
  case 0x324:
    if ( _short(r16[dx]) >= _short(0x0FFF6) ) // jge 
      { _pc = 0x330; continue; }
    _data16set(0x954C, _data16get(0x954C) | 4);
    return;
  case 0x330:
    if ( _short(r16[dx]) <= _short(0x0A) ) // jle 
      return;
    _data16set(0x954C, _data16get(0x954C) | 8);
    return;
  case 0x96:
    _ASSERT(0);
    _pc = -1;
  }
}
function sub_33B()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x33B);
    sub_2C07();
    r8[al] = 4;
    sub_2C9A();
    sub_4F3();
    _data16set(0x8F15, r16[ax]);
    r8[al] = 0;
    sub_2C9A();
  case 0x34E:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x34E; continue; }
    _data16set(0x8F0D, r16[ax]);
    r8[al] = 1;
    sub_2C9A();
  case 0x35F:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x35F; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x35F; continue; }
    _data16set(0x8F0F, r16[ax]);
    r8[al] = 2;
    sub_2C9A();
  case 0x376:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x376; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x376; continue; }
    if ( r16[ax] == _data16get(0x8F0F) ) // jz 
      { _pc = 0x376; continue; }
    _data16set(0x8F11, r16[ax]);
    r8[al] = 3;
    sub_2C9A();
  case 0x393:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x393; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x393; continue; }
    if ( r16[ax] == _data16get(0x8F0F) ) // jz 
      { _pc = 0x393; continue; }
    if ( r16[ax] == _data16get(0x8F11) ) // jz 
      { _pc = 0x393; continue; }
    _data16set(0x8F13, r16[ax]);
    r8[al] = 6;
    sub_2C9A();
  case 0x3B6:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x3B6; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x3B6; continue; }
    if ( r16[ax] == _data16get(0x8F0F) ) // jz 
      { _pc = 0x3B6; continue; }
    if ( r16[ax] == _data16get(0x8F11) ) // jz 
      { _pc = 0x3B6; continue; }
    if ( r16[ax] == _data16get(0x8F13) ) // jz 
      { _pc = 0x3B6; continue; }
    _data16set(0x8F17, r16[ax]);
    r8[al] = 7;
    sub_2C9A();
  case 0x3DF:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x3DF; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x3DF; continue; }
    if ( r16[ax] == _data16get(0x8F0F) ) // jz 
      { _pc = 0x3DF; continue; }
    if ( r16[ax] == _data16get(0x8F11) ) // jz 
      { _pc = 0x3DF; continue; }
    if ( r16[ax] == _data16get(0x8F13) ) // jz 
      { _pc = 0x3DF; continue; }
    if ( r16[ax] == _data16get(0x8F17) ) // jz 
      { _pc = 0x3DF; continue; }
    _data16set(0x8F19, r16[ax]);
    r8[al] = 5;
    sub_2C9A();
  case 0x40E:
    sub_4F3();
    if ( r16[ax] == _data16get(0x8F15) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F0D) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F0F) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F11) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F13) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F17) ) // jz 
      { _pc = 0x40E; continue; }
    if ( r16[ax] == _data16get(0x8F19) ) // jz 
      { _pc = 0x40E; continue; }
    _data16set(0x8F1B, r16[ax]);
    sub_529();
    _pc = -1;
  }
}
function sub_442()
{
  STAT(0x442);
  _data16set(0x8F0B, 0);
  _data16set(0x8F0D, 0x4B);
  _data16set(0x8F0F, 0x4D);
  _data16set(0x8F11, 0x48);
  _data16set(0x8F13, 0x50);
  _data16set(0x8F15, 0x39);
  _data16set(0x8F17, 0x31);
  _data16set(0x8F19, 0x32);
  _data16set(0x8F1B, 0x10);
  r16[ax] = ds;
  es = r16[ax];
  r16[ax] = 0;
  r16[cx] = 0x40;
  di = 0x8E8A;
  _rep_stosw();
  r8[al] = 9;
  r8[ah] = 0x35;
  _int(0x21);
  _data16set(0x8E84, r16[bx]);
  _data16set(0x8E82, es);
  _push(ds);
  r16[dx] = 0x4B7;
  r16[ax] = cs;
  ds = r16[ax];
  r8[al] = 9;
  r8[ah] = 0x25;
  _int(0x21);
  ds = _pop();
}
function sub_4A5()
{
  STAT(0x4A5);
  r16[dx] = _data16get(0x8E84);
  r16[ax] = _data16get(0x8E82);
  _push(ds);
  ds = r16[ax];
  r8[al] = 9;
  r8[ah] = 0x25;
  _int(0x21);
  ds = _pop();
}
function sub_4F3()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x4F3);
    _cld();
  case 0x4F4:
    si = 0x8E8A;
  case 0x4F7:
    tick();
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x520; continue; }
    r16[ax] = si;
    r16[ax] -= 0x8E8B;
    if ( r16[ax] == 0x3B ) // jz 
      { _pc = 0x520; continue; }
    if ( r16[ax] == 0x3C ) // jz 
      { _pc = 0x520; continue; }
    if ( r16[ax] == 0x3D ) // jz 
      { _pc = 0x520; continue; }
    if ( r16[ax] == 0x3E ) // jz 
      { _pc = 0x520; continue; }
    if ( r16[ax] == 0x2A ) // jz 
      { _pc = 0x520; continue; }
    if ( r16[ax] == 0x36 ) // jz 
      { _pc = 0x520; continue; }
    return;
  case 0x520:
    if ( si != 0x8F0A ) // jnz 
      { _pc = 0x4F7; continue; }
    _pc = 0x4F4;
      continue;
    _pc = -1;
  }
}
function sub_529()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x529);
  case 0x529:
    si = 0x8E8A;
    r8[ah] = 0;
  case 0x52E:
    tick();
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x535; continue; }
    r8[ah] = r8[ah] + 1;
  case 0x535:
    if ( si != 0x8F0A ) // jnz 
      { _pc = 0x52E; continue; }
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x529; continue; }
    _pc = -1;
  }
}
function sub_541()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x541);
    r16[cx] = 0x4E20;
  case 0x544:
    si = 0x8E8A;
    r8[ah] = 0;
    _cld();
  case 0x54A:
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x557; continue; }
    r8[ah] = 1;
    if ( si != _data16get(0x8F0B) ) // jnz 
      { _pc = 0x55F; continue; }
  case 0x557:
    if ( si == 0x8F0A ) // jz 
      { _pc = 0x55F; continue; }
    _pc = 0x54A;
      continue;
  case 0x55F:
    if ( si == _data16get(0x8F0B) ) // jz 
      { _pc = 0x578; continue; }
    _data16set(0x8F0B, si);
    si -= 0x8E8B;
    r8[al] = _data[ADR(ds, si + 0x5A)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x576; continue; }
    if ( r8s[al] >= 0 ) // jns 
      return;
    r8[al] = 0;
    return;
  case 0x576:
    _pc = 0x583;
      continue;
  case 0x578:
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x583; continue; }
    _data16set(0x8F0B, 0);
  case 0x583:
    if ( --r16[cx] )
      { _pc = 0x544; continue; }
    r8[al] = 0;
    _pc = -1;
  }
}
function sub_588()
{
  STAT(0x588);
  r16[ax] = 0;
  _int(0x33);
  _data[0x8F0A] = r8[al];
}
function sub_591()
{
  STAT(0x591);
  r8[al] = 0x1C;
  r8[ah] = 0x35;
  _int(0x21);
  _data16set(0x8E88, r16[bx]);
  _data16set(0x8E86, es);
  _push(ds);
  r16[dx] = 0x5CE;
  r16[ax] = cs;
  ds = r16[ax];
  r8[al] = 0x1C;
  r8[ah] = 0x25;
  _int(0x21);
  ds = _pop();
  r8[al] = 0x36;
  _out(0x43, r8[al]);
  r16[ax] = 0x4D0E;
  _out(0x40, r8[al]);
  r8[al] = r8[ah];
  _out(0x40, r8[al]);
}
function sub_5BC()
{
  STAT(0x5BC);
  r16[dx] = _data16get(0x8E88);
  r16[ax] = _data16get(0x8E86);
  _push(ds);
  ds = r16[ax];
  r8[al] = 0x1C;
  r8[ah] = 0x25;
  _int(0x21);
  ds = _pop();
}
function sub_5EC()
{
  STAT(0x5EC);
  _push(ds);
  r16[dx] = 0x5FC;
  r16[ax] = cs;
  ds = r16[ax];
  r8[al] = 0x24;
  r8[ah] = 0x25;
  _int(0x21);
  ds = _pop();
}
function sub_600()
{
  STAT(0x600);
  r16[dx] = 0x1E2;
  r16[ax] = _data16get(0x94E8);
  sub_637();
  r16[dx] = 0x1EA;
  r16[ax] = _data16get(0x94EA);
  sub_637();
  r16[dx] = 0x1F2;
  r16[ax] = _data16get(0x94EC);
  sub_637();
  r16[dx] = 0x1F9;
  r16[ax] = _data16get(0x94EE);
  sub_637();
  r16[dx] = 0x203;
  r16[ax] = _data16get(0x94F0);
  sub_637();
  r16[dx] = 0x20B;
  r16[ax] = _data16get(0x94F2);
  sub_637();
}
function sub_637()
{
  STAT(0x637);
  _data16set(0x8F20, r16[ax]);
  di = 0;
  r16[cx] = 0x7D00;
  sub_64D();
}
function sub_644()
{
  STAT(0x644);
  r16[ax] = ds;
  _data16set(0x8F20, r16[ax]);
  sub_64D();
}
function sub_64D()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x64D);
    _push(di);
    _push(r16[cx]);
    r16[ax] = 0x3D00;
    _int(0x21);
    r16[cx] = _pop();
    r16[dx] = _pop();
    if ( !cf ) // jnb 
      { _pc = 0x659; continue; }
    return;
  case 0x659:
    _data16set(0x8F1E, r16[ax]);
    r16[bx] = r16[ax];
    r16[ax] = _data16get(0x8F20);
    _push(ds);
    ds = r16[ax];
    r16[ax] = 0x3F00;
    _int(0x21);
    ds = _pop();
    r16[ax] = 0x3E00;
    r16[bx] = _data16get(0x8F1E);
    _int(0x21);
    _pc = -1;
  }
}
function sub_674()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x674);
    _push(di);
    _push(r16[cx]);
    r16[cx] = 0;
    r16[ax] = 0x3C00;
    _int(0x21);
    r16[cx] = _pop();
    r16[dx] = _pop();
    if ( !cf ) // jnb 
      { _pc = 0x683; continue; }
    return;
  case 0x683:
    _data16set(0x8F1E, r16[ax]);
    r16[bx] = r16[ax];
    r16[ax] = 0x4000;
    _int(0x21);
    if ( !cf ) // jnb 
      { _pc = 0x690; continue; }
    return;
  case 0x690:
    r16[ax] = 0x3E00;
    r16[bx] = _data16get(0x8F1E);
    _int(0x21);
    _pc = -1;
  }
}
function sub_69A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x69A);
    r8[al] = _data[0x9501];
    r8[bl] = r8[al];
    r8[bl] <<= 1;
    r8[bl] += r8[al];
    r8[bl] += _data[0x9502];
    r8[bh] = 0;
    r16[bx] <<= 1;
    si = _data16get(OFS(r16[bx] + 0x244));
    di = 0x9229;
    r16[cx] = 0x40;
    r16[ax] = ds;
    es = r16[ax];
    r16[ax] = 0;
    _cld();
    _rep_stosw();
    di = 0x9229;
  case 0x6C2:
    _lodsb();
    if ( r8[al] == 0x0FF ) // jz 
      { _pc = 0x6EB; continue; }
    r8[al] <<= 1;
    r8[al] <<= 1;
    r8[ah] = r8[al];
    _lodsb();
    r8[al] <<= 1;
    r8[bl] = r8[al];
    r8[bh] = 0;
    r8[al] = 0;
    r16[ax] |= _data16get(OFS(r16[bx] + 0x0CD7));
    r16[cx] = r16[ax];
    _lodsb();
    r8[al] = - r8[al];
    r8[al] += 0x3F;
    r8[al] <<= 1;
    r8[bl] = r8[al];
    _ASSERT( ds == 0 );
    _data16set(OFS(r16[bx] - 0x6DD7), _data16get(OFS(r16[bx] - 0x6DD7)) | r16[cx]);
    _pc = 0x6C2;
      continue;
  case 0x6EB:
    r8[al] = _data[0x9501];
    r8[bl] = r8[al];
    r8[bl] <<= 1;
    r8[bl] += r8[al];
    r8[bl] += _data[0x9502];
    r8[bh] = 0;
    r16[bx] <<= 1;
    si = _data16get(OFS(r16[bx] + 0x214));
    di = 0x8F29;
    r16[cx] = 0x300;
    r8[bl] = 0;
  case 0x708:
    r8[bl]--;
    if ( r8s[bl] >= 0 ) // jns 
      { _pc = 0x72C; continue; }
    _lodsb();
    r8[dl] = r8[al];
    r8[dl] &= 0x3F;
    r8[al] &= 0x0C0;
    if ( r8[al] ) // jnz 
      { _pc = 0x71A; continue; }
    r8[bl] = 0;
    _pc = 0x72C;
      continue;
  case 0x71A:
    if ( r8[al] != 0x40 ) // jnz 
      { _pc = 0x722; continue; }
    r8[bl] = 1;
    _pc = 0x72C;
      continue;
  case 0x722:
    if ( r8[al] != 0x80 ) // jnz 
      { _pc = 0x72A; continue; }
    r8[bl] = 2;
    _pc = 0x72C;
      continue;
  case 0x72A:
    r8[bl] = 3;
  case 0x72C:
    _data[di] = r8[dl];
    di = di + 1;
    if ( --r16[cx] )
      { _pc = 0x708; continue; }
    di = 0;
    r16[ax] = 0x0A800;
    es = r16[ax];
    r16[dx] = 0x3CE;
    r8[ah] = 0;
    r8[al] = 0;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F01;
    _out(r16[dx], r16[ax]);
    r16[cx] = 0x4000;
    _rep_stosw();
    r16[ax] = 0x8F29;
    _data16set(0x8F25, r16[ax]);
    _data16set(0x8F23, 0x3F0);
    r16[cx] = 0x40;
  case 0x759:
    _push(r16[cx]);
    _data[0x8F22] = 0;
    sub_7AF();
    _data16set(0x279, 0);
    _data[0x27D] = 8;
    _data16set(0x283, _data16get(0x283) + 8);
    si = 0x274;
    sub_BC5();
    _data16set(0x279, 8);
    _data[0x27D] = 0x18;
    r16[cx] = 0x0A;
  case 0x786:
    _push(r16[cx]);
    sub_7AF();
    si = 0x274;
    sub_BC5();
    _data16set(0x279, _data16get(0x279) + 0x18);
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x786; continue; }
    _data[0x27D] = 8;
    sub_7AF();
    si = 0x274;
    sub_BC5();
    _data16set(0x8F23, _data16get(0x8F23) - 0x10);
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x759; continue; }
    _pc = -1;
  }
}
function sub_7AF()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x7AF);
    r8[al] = _data[0x8F22];
    _data[0x277] = r8[al];
    r16[bx] = _data16get(0x8F25);
    r8[al] = _data[r16[bx]];
    r16[bx] = r16[bx] + 1;
    _data16set(0x8F25, r16[bx]);
    r8[bh] = 0;
    r8[bl] = r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x51D)];
    _data[0x27E] = r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x571)];
    _data[0x8F22] += r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x547)];
    _cbw();
    r16[ax] += _data16get(0x8F23);
    _data16set(0x27B, r16[ax]);
    if ( r16[bx] < 0x26 ) // jb 
      { _pc = 0x7EC; continue; }
    _data16set(0x281, 2);
    _pc = 0x7F2;
      continue;
  case 0x7EC:
    _data16set(0x281, 4);
  case 0x7F2:
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] + 0x5EF));
    _data16set(0x283, r16[bx]);
    _pc = -1;
  }
}
function sub_7FD()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x7FD);
    // var_8		= word ptr -8
    // var_6		= word ptr -6
    // var_4		= word ptr -4
    // var_2		= word ptr -2
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    sp -= 8;
    r16[ax] = _stack16get(bp + arg_2);
    r16[ax] += 0x10;
    r8[cl] = 0x18;
    _div(r8[cl]);
    _push(r16[ax]);
    r8[ah] = 0;
    _stack16set(OFS(bp + var_2), r16[ax]);
    r16[ax] = _pop();
    r8[al] = r8[ah];
    r8[ah] = 0;
    r8[cl] = 3;
    _div(r8[cl]);
    r8[ah] = 0;
    _stack16set(OFS(bp + var_4), r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    r16[ax] &= 0x3FF;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] = - r16[ax];
    r16[ax] += 0x3F;
    _stack16set(OFS(bp + var_6), r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    r16[ax] &= 0x0F;
    r16[ax] >>= 1;
    _stack16set(OFS(bp + var_8), r16[ax]);
    r16[ax] = _stack16get(bp + var_6);
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[bx] = r16[ax];
    r16[ax] <<= 1;
    r16[bx] += r16[ax];
    r16[bx] += 0x8F29;
    si = r16[bx];
    r16[bx] += _stack16get(bp + var_2);
    r8[al] = _data[r16[bx]];
    r8[ah] = 0;
    _push(r16[ax]);
    r16[ax] <<= 1;
    r16[bx] = r16[ax];
    r16[bx] = _data16get(OFS(r16[bx] + 0x643));
    r16[ax] = _stack16get(bp + var_8);
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[bx] += r16[ax];
    r16[bx] += _stack16get(bp + var_4);
    r8[cl] = _data[r16[bx]];
    _push(r16[cx]);
    r8[cl] &= 0x1F;
    if ( !(r8[cl] & 0x10) ) // jz 
      { _pc = 0x881; continue; }
    r8[cl] |= 0x0E0;
  case 0x881:
    r16[dx] = _stack16get(bp + var_2);
    _cld();
  case 0x885:
    if ( r16[dx] == 0 ) // jz 
      { _pc = 0x896; continue; }
    _lodsb();
    r8[bh] = 0;
    r8[bl] = r8[al];
    r8[cl] += _data[OFS(r16[bx] + 0x571)];
    r16[dx]--;
    _pc = 0x885;
      continue;
  case 0x896:
    r8[al] = r8[cl];
    _cbw();
    r16[cx] = _pop();
    r16[bx] = _pop();
    if ( r8[cl] & 0x80 ) // jnz 
      { _pc = 0x8A6; continue; }
    r8[bl] = _data[OFS(r16[bx] + 0x59B)];
    _pc = 0x8AA;
      continue;
  case 0x8A6:
    r8[bl] = _data[OFS(r16[bx] + 0x5C5)];
  case 0x8AA:
    r8[bh] = 0;
    r16[cx] = _stack16get(bp + var_6);
    r16[cx] = - r16[cx];
    r16[cx] += 0x3F;
    sp = bp;
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_8BA()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x8BA);
    // arg_0		= word ptr  4
    _push(bp);
    bp = sp;
    r16[bx] = _stack16get(bp + arg_0);
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] - 0x6DD7));
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x946; continue; }
    _push(r16[ax]);
    r8[ah] >>= 1;
    r8[ah] >>= 1;
    r8[bl] = r8[ah];
    r8[bh] = 0;
    r16[bx] <<= 1;
    si = _data16get(OFS(r16[bx] + 0x28B));
    if ( r8[ah] < 0x0F ) // jb 
      { _pc = 0x902; continue; }
    if ( r8[ah] > 0x14 ) // ja 
      { _pc = 0x902; continue; }
    r8[ah] -= 0x0F;
    _data[ADR(ds, si + 1)] = r8[ah];
    r8[bl] = r8[ah];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] - 0x6AD2)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x8F9; continue; }
    r16[ax] = _pop();
    _pc = 0x946;
      continue;
  case 0x8F9:
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x32E));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
  case 0x902:
    _data[ADR(ds, si + 0x13)] = 0x0A;
    r16[ax] = _stack16get(bp + arg_0);
    _data[ADR(ds, si + 0x14)] = r8[al];
    r16[ax] = _pop();
    r16[cx] = 0x0A;
  case 0x910:
    cf = r16[ax] & 1; // cf-insertion
    r16[ax] >>= 1;
    if ( !cf ) // jnb 
      { _pc = 0x941; continue; }
    _push(r16[ax]);
    _push(r16[cx]);
    sub_94A();
    r8[al] = _data[ADR(ds, si + 0x13)];
    r8[ah] = 0;
    _push(r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    _push(r16[ax]);
    sub_9E9();
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x932; continue; }
    _push(si);
    sub_B58();
    si = _pop();
    _pc = 0x93F;
      continue;
  case 0x932:
    _push(si);
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x93E; continue; }
    sub_A1B();
  case 0x93E:
    si = _pop();
  case 0x93F:
    r16[cx] = _pop();
    r16[ax] = _pop();
  case 0x941:
    _data[ADR(ds, si + 0x13)]--;
    if ( --r16[cx] )
      { _pc = 0x910; continue; }
  case 0x946:
    bp = _pop();
    _retn(2);
    _pc = -1;
  }
}
function sub_94A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x94A);
    r8[dl] = _data[ADR(ds, si + 0x13)];
    _push(si);
    r8[al] = 0x3F;
    r8[al] -= _data[ADR(ds, si + 0x14)];
    r8[al] <<= 1;
    r8[al] <<= 1;
    r8[ah] = 0;
    si = r16[ax];
    r16[ax] <<= 1;
    si += r16[ax];
    si += 0x8F29;
    r8[cl] = 0;
    _cld();
  case 0x966:
    if ( r8[dl] == 0 ) // jz 
      { _pc = 0x978; continue; }
    _lodsb();
    r8[bh] = 0;
    r8[bl] = r8[al];
    r8[cl] += _data[OFS(r16[bx] + 0x571)];
    r8[dl]--;
    _pc = 0x966;
      continue;
  case 0x978:
    si = _pop();
    _data[ADR(ds, si + 3)] = r8[cl];
    r8[al] = _data[ADR(ds, si + 0x14)];
    r8[ah] = 0;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[ADR(ds, si + 0x13)];
    r8[ah] = 0;
    r16[ax] <<= 1;
    r16[cx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] += r16[cx];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] -= 4;
    _data16set(ADR(ds, si + 5), r16[ax]);
    _pc = -1;
  }
}
function sub_9A4()
{
  STAT(0x9A4);
  di = 0x92A9;
  r16[cx] = 0x0C0;
  r16[ax] = ds;
  es = r16[ax];
  r16[ax] = 0x0FFFF;
  _cld();
  _rep_stosw();
}
function sub_9B5()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x9B5);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    // arg_4		= word ptr  8
    _push(bp);
    bp = sp;
    si = _stack16get(bp + arg_4);
    sub_A1B();
    r16[bx] = _stack16get(bp + arg_2);
    r16[bx] <<= 1;
    r16[cx] = _data16get(OFS(r16[bx] + 0x0CEB));
    r16[bx] = _stack16get(bp + arg_0);
    r16[bx] <<= 1;
    r8[al] = _data[0x9502];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x9D9; continue; }
    r16[bx] += 0x80;
    _pc = 0x9E1;
      continue;
  case 0x9D9:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x9E1; continue; }
    r16[bx] += 0x100;
  case 0x9E1:
    _data16set(OFS(r16[bx] - 0x6D57), _data16get(OFS(r16[bx] - 0x6D57)) & r16[cx]);
    bp = _pop();
    _retn(6);
    _pc = -1;
  }
}
function sub_9E9()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x9E9);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[bx] = _stack16get(bp + arg_2);
    r16[bx] <<= 1;
    r16[cx] = _data16get(OFS(r16[bx] + 0x0CEB));
    r16[bx] = _stack16get(bp + arg_0);
    r16[bx] <<= 1;
    r8[al] = _data[0x9502];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0xA07; continue; }
    r16[bx] += 0x80;
    _pc = 0xA0F;
      continue;
  case 0xA07:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0xA0F; continue; }
    r16[bx] += 0x100;
  case 0xA0F:
    r16[cx] = ~ r16[cx];
    r16[ax] = _data16get(OFS(r16[bx] - 0x6D57));
    r16[ax] &= r16[cx];
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_A1B()
{
  STAT(0xA1B);
  r8[al] = _data[ADR(ds, si + 0x12)];
  r8[al] <<= 1;
  r8[bl] = r8[al];
  r8[bh] = 0;
  di = _data16get(OFS(r16[bx] + 0x31E));
  r8[al] = _data[di];
  _data[ADR(ds, si)] = r8[al];
  r8[al] = _data[OFS(di + 9)];
  _data[ADR(ds, si + 9)] = r8[al];
  r8[al] = _data[OFS(di + 0x0A)];
  _data[ADR(ds, si + 0x0A)] = r8[al];
  r8[al] = _data[OFS(di + 0x0B)];
  _data[ADR(ds, si + 0x0B)] = r8[al];
  r8[al] = _data[OFS(di + 0x0C)];
  _data[ADR(ds, si + 0x0C)] = r8[al];
  r16[ax] = _data16get(OFS(di + 0x0F));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
  r8[al] = _data[OFS(di + 0x12)];
  _data[ADR(ds, si + 0x12)] = r8[al];
}
function sub_A51()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xA51);
    r8[bl] = _data[0x1B9E];
    r8[bh] = 0;
    r16[bx] <<= 1;
    si = r16[bx];
    r8[al] = _data[0x9502];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0xA68; continue; }
    si += 0x80;
    _pc = 0xA70;
      continue;
  case 0xA68:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0xA70; continue; }
    si += 0x100;
  case 0xA70:
    _ASSERT( ds == 0 );
    r16[ax] = _data16get(ADR(ds, si));
    r16[ax] &= _data16get(OFS(r16[bx] - 0x6DD7));
    //////////// CHEAT MODE ON
    //r16[ax] = 0;
    ////////////
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0xAD1; continue; }
    r8[bl] = r8[ah];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x2B5)];
    if ( r8[cl] == 0 ) // jz 
      { _pc = 0xAD1; continue; }
    _data[0x9429] = r8[cl];
    _data16set(0x942C, 0x0A);
    r16[bx] <<= 1;
    r16[dx] = _data16get(OFS(r16[bx] + 0x2CA));
    r16[bx] = _data16get(OFS(r16[bx] + 0x2F4));
    r16[cx] = 0x0A;
  case 0xAA5:
    cf = r16[ax] & 1; // cf-insertion
    r16[ax] >>= 1;
    if ( !cf ) // jnb 
      { _pc = 0xAC8; continue; }
    _push(r16[bx]);
    r16[bx] -= r16[dx];
    if ( _short(r16[bx]) > _short(_data16get(0x1B8F)) ) // jg 
      { _pc = 0xAC7; continue; }
    r16[bx] += r16[dx];
    r16[bx] += r16[dx];
    if ( _short(r16[bx]) < _short(_data16get(0x1B8F)) ) // jl 
      { _pc = 0xAC7; continue; }
    r16[ax] = _pop();
    r8[al] = _data[0x9429];
    r8[ah] = 0;
    r16[bx] = _data16get(0x942C);
    return;
  case 0xAC7:
    r16[bx] = _pop();
  case 0xAC8:
    r16[bx] -= 0x18;
    _data16set(0x942C, _data16get(0x942C) -1);
    if ( --r16[cx] )
      { _pc = 0xAA5; continue; }
  case 0xAD1:
    r16[ax] = 0;
    _pc = -1;
  }
}
function sub_AD5()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xAD5);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[bx] = _stack16get(bp + arg_0);
    r16[bx] <<= 1;
    si = r16[bx];
    r8[al] = _data[0x9502];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0xAEC; continue; }
    si += 0x80;
    _pc = 0xAF4;
      continue;
  case 0xAEC:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0xAF4; continue; }
    si += 0x100;
  case 0xAF4:
    r16[ax] = _data16get(ADR(ds, si));
    r16[ax] &= _data16get(OFS(r16[bx] - 0x6DD7));
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0xB51; continue; }
    r8[bl] = r8[ah];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x2B5)];
    if ( r8[cl] == 0 ) // jz 
      { _pc = 0xB51; continue; }
    _data16set(0x942C, 0x0A);
    r16[bx] <<= 1;
    r16[dx] = _data16get(OFS(r16[bx] + 0x2CA));
    r16[dx] -= 0x0E;
    r16[bx] = _data16get(OFS(r16[bx] + 0x2F4));
    r16[cx] = 0x0A;
  case 0xB28:
    cf = r16[ax] & 1; // cf-insertion
    r16[ax] >>= 1;
    if ( !cf ) // jnb 
      { _pc = 0xB48; continue; }
    _push(r16[bx]);
    r16[bx] -= r16[dx];
    if ( _short(r16[bx]) > _stack16gets(bp + arg_2) ) // jg 
      { _pc = 0xB47; continue; }
    r16[bx] += r16[dx];
    r16[bx] += r16[dx];
    if ( _short(r16[bx]) < _stack16gets(bp + arg_2) ) // jl 
      { _pc = 0xB47; continue; }
    r16[ax] = _pop();
    r16[ax] = 1;
    r16[bx] = _data16get(0x942C);
    _pc = 0xB54;
      continue;
  case 0xB47:
    r16[bx] = _pop();
  case 0xB48:
    r16[bx] -= 0x18;
    _data16set(0x942C, _data16get(0x942C) -1);
    if ( --r16[cx] )
      { _pc = 0xB28; continue; }
  case 0xB51:
    r16[ax] = 0;
  case 0xB54:
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_B58()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xB58);
    r16[ax] = seg_dseg;
    es = r16[ax];
    di = 0x1B8A;
  case 0xB60:
    r8[al] = _data[di];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0xB78; continue; }
    if ( r8[al] & 1 ) // jnz 
      { _pc = 0xB73; continue; }
    _push(di);
    r16[cx] = 0x17;
    _cld();
    _rep_movsb();
    si = _pop();
    return;
  case 0xB73:
    di += 0x17;
    _pc = 0xB60;
      continue;
  case 0xB78:
    si = 0;
    _pc = -1;
  }
}
function sub_B7C()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xB7C);
    si = 0x1B8A;
  case 0xB7F:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      return;
    _data[ADR(ds, si)] = 0;
    si += 0x17;
    _pc = 0xB7F;
      continue;
    _pc = -1;
  }
}
function sub_B8E()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xB8E);
    r16[ax] = _data16get(0x94F8);
    _data16set(0x942E, r16[ax]);
    word_code_D93 = 0x28;
    _data16set(0x9430, 1);
    r16[cx] = 7;
  case 0xBA4:
    si = 0x1B8A;
  case 0xBA7:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0xBC2; continue; }
    if ( !(r8[al] & 1) ) // jz 
      { _pc = 0xBBD; continue; }
    if ( r8[cl] != _data[ADR(ds, si + 2)] ) // jnz 
      { _pc = 0xBBD; continue; }
    _push(r16[cx]);
    _push(si);
    sub_BDC();
    si = _pop();
    r16[cx] = _pop();
  case 0xBBD:
    si += 0x17;
    _pc = 0xBA7;
      continue;
  case 0xBC2:
    if ( --r16[cx] )
      { _pc = 0xBA4; continue; }
    _pc = -1;
  }
}
function sub_BC5()
{
  STAT(0xBC5);
  r16[ax] = 0x0A800;
  _data16set(0x942E, r16[ax]);
  word_code_D93 = 0x20;
  _data16set(0x9430, 0);
  sub_BDC();
}
function sub_BDC()
{
  STAT(0xBDC);
  r8[al] = _data[ADR(ds, si + 0x0B)];
  _cbw();
  r16[bx] = _data16get(ADR(ds, si + 5));
  r16[bx] -= r16[ax];
  _push(r16[bx]);
  r8[al] = _data[ADR(ds, si + 3)];
  r8[al] += _data[ADR(ds, si + 0x0C)];
  _cbw();
  r16[ax] = - r16[ax];
  r16[ax] += _data16get(ADR(ds, si + 7));
  _push(r16[ax]);
  r8[al] = _data[ADR(ds, si + 9)];
  r8[ah] = 0;
  _push(r16[ax]);
  r8[al] = _data[ADR(ds, si + 0x0A)];
  r8[ah] = 0;
  _push(r16[ax]);
  r16[bx] = _data16get(ADR(ds, si + 0x0D));
  r16[bx] = _data16get(OFS(r16[bx] - 0x6B18));
  r8[al] = _data[ADR(ds, si + 0x11)];
  byte_code_D95 = r8[al];
  r8[cl] = r8[al];
  r8[cl] <<= 1;
  r8[cl] <<= 1;
  r8[cl] <<= 1;
  r8[cl] <<= 1;
  r8[al] |= r8[cl];
  byte_code_D96 = r8[al];
  si = _data16get(ADR(ds, si + 0x0F));
  sub_C24();
}

function sub_C24()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xC24);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    // arg_4		= word ptr  8
    // arg_6		= word ptr  0Ah
    _push(bp);
    bp = sp;
    r16[ax] = _data16get(0x9430);
    if ( r16[ax] != 0 ) // jnz 
      { _pc = 0xC32; continue; }
    _pc = 0xCBC;
      continue;
  case 0xC32:
    r16[ax] = _stack16get(bp + arg_4);
    r16[ax] -= _data16get(0x9528);
    r16[ax] &= 0x3FF;
    if ( !(r16[ax] & 0x200) ) // jz 
      { _pc = 0xC44; continue; }
    r16[ax] |= 0x0FC00;
  case 0xC44:
    _stack16set(OFS(bp + arg_4), r16[ax]);
    if ( _short(r16[ax]) >= _short(0) ) // jge 
      { _pc = 0xC77; continue; }
    _stack16set(OFS(bp + arg_0), _stack16get(bp + arg_0) + r16[ax]);
    if ( _stack16gets(bp + arg_0) >= 0 ) // jns 
      { _pc = 0xC54; continue; }
    _pc = 0xD8F;
      continue;
  case 0xC54:
    if ( _stack16get(bp + arg_0) != 0 ) // jnz 
      { _pc = 0xC59; continue; }
    _pc = 0xD8F;
      continue;
  case 0xC59:
    r16[ax] = - r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[cx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[cx] += r16[ax];
    r16[cx] <<= 1;
    r16[cx] <<= 1;
    si += r16[cx];
    r16[ax] = 0;
    _stack16set(OFS(bp + arg_4), r16[ax]);
    _pc = 0xC8F;
      continue;
  case 0xC77:
    r16[ax] += _stack16get(bp + arg_0);
    r16[ax] -= 0x0A0;
    if ( _short(r16[ax]) < 0 ) // js 
      { _pc = 0xC8F; continue; }
    r16[ax] = - r16[ax];
    r16[ax] += _stack16get(bp + arg_0);
    if ( _short(r16[ax]) > _short(0) ) // jg 
      { _pc = 0xC8C; continue; }
    _pc = 0xD8F;
      continue;
  case 0xC8C:
    _stack16set(OFS(bp + arg_0), r16[ax]);
  case 0xC8F:
    r16[ax] = 0x20;
    _stack16set(OFS(bp + arg_6), _stack16get(bp + arg_6) + r16[ax]);
    r16[ax] = 8;
    _stack16set(OFS(bp + arg_4), _stack16get(bp + arg_4) + r16[ax]);
    r16[ax] = _stack16get(bp + arg_6);
    if ( _short(r16[ax]) >= _short(0x20) ) // jge 
      { _pc = 0xCAB; continue; }
    r16[ax] = 0x20;
    _stack16set(OFS(bp + arg_6), r16[ax]);
    _pc = 0xCBC;
      continue;
  case 0xCAB:
    r16[ax] += _stack16get(bp + arg_2);
    if ( _short(r16[ax]) <= _short(0x120) ) // jle 
      { _pc = 0xCBC; continue; }
    r16[ax] = 0x120;
    r16[ax] -= _stack16get(bp + arg_2);
    _stack16set(OFS(bp + arg_6), r16[ax]);
  case 0xCBC:
    _push(ds);
    _push(r16[bx]);
    r16[dx] = 0x3CE;
    r16[ax] = 0x0A05;
    _out(r16[dx], r16[ax]);
    r16[ax] = 7;
    _out(r16[dx], r16[ax]);
    r16[ax] = _stack16get(bp + arg_6);
    r16[bx] = _stack16get(bp + arg_4);
    _push(r16[cx]);
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    r16[cx] = word_code_D93;
    if ( r16[cx] != 0x28 ) // jnz 
      { _pc = 0xCE4; continue; }
    di = r16[bx];
    _pc = 0xCE7;
      continue;
  case 0xCE4:
    di = 0;
  case 0xCE7:
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    di += r16[bx];
    r8[cl] = r8[al];
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    di += r16[ax];
    r8[cl] &= 7;
    r16[ax] = 0x80;
    r16[ax] >>= r8[cl];
    r8[ah] = r8[al];
    r16[bx] = _data16get(0x942E);
    es = r16[bx];
    r16[cx] = _pop();
    r16[cx] = _stack16get(bp + arg_2);
    r16[cx] >>= 1;
    r8[al] = 8;
    ds = _pop();
    r16[bx] = _stack16get(bp + arg_0); 
  case 0xD13:
    _push(r16[ax]);
    _push(r16[bx]);
    _push(r16[cx]);
    _push(di);
    _push(si);
  case 0xD18:
    r8[bh] = byte_code_D96;
  case 0xD1D:
    r8[bl] = _data[ADR(ds, si)];
    si = si + 1;
    if ( r8[bh] != r8[bl] ) // jnz 
      { _pc = 0xD3A; continue; }
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0xD2F; continue; }
    r8[ah] = 0x40;
    di = di + 1;
    if ( --r16[cx] )
      { _pc = 0xD1D; continue; }
    _pc = 0xD6D;
      continue;
  case 0xD2F:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0xD36; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0xD36:
    if ( --r16[cx] )
      { _pc = 0xD1D; continue; }
    _pc = 0xD6D;
      continue;
  case 0xD3A:
    r8[bh] = r8[bl];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    if ( r8[bl] == byte_code_D95 ) // jz 
      { _pc = 0xD4F; continue; }
    _out(r16[dx], r16[ax]);
    _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bl]);
  case 0xD4F:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0xD56; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0xD56:
    r8[bh] &= 0x0F;
    if ( r8[bh] == byte_code_D95 ) // jz 
      { _pc = 0xD64; continue; }
    _out(r16[dx], r16[ax]);
    _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bh]);
  case 0xD64:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0xD6B; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0xD6B:
    if ( --r16[cx] )
      { _pc = 0xD18; continue; }
  case 0xD6D:
    si = _pop();
    si += 0x0A0;
    di = _pop();
    di += word_code_D93;
    di &= 0x7FFF;
    r16[cx] = _pop();
    r16[bx] = _pop();
    r16[ax] = _pop();
    r16[bx]--;
_ASSERT( r16[bx] < 200 && r16[cx] < 200 );
    if ( r16[bx] ) // jnz 
      { _pc = 0xD13; continue; }
    ds = _pop();
    r16[ax] = 0x0FF08;
    _out(r16[dx], r16[ax]);
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F07;
    _out(r16[dx], r16[ax]);
  case 0xD8F:
    bp = _pop();
    _retn(8);
    _pc = -1;
  }
}

function sub_D98()
{
  STAT(0xD98);
  _data16set(0x9528, 0x1A);
  _data[0x9513] = 0;
  sub_B7C();
}
function sub_DA7()
{
  STAT(0xDA7);
  sub_9A4();
  sub_69A();
  _data[0x9519] = 0;
  _data[0x951A] = 0;
  _data[0x951B] = 0;
  sub_E3D();
}
function sub_DC0()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xDC0);
    _data[0x94FE] = _data[0x94FE] + 1;
    r8[al] = _data[0x94FE];
    if ( r8[al] < 6 ) // jb 
      { _pc = 0xDD3; continue; }
    _data16set(0x94FC, 0x30);
    _pc = 0xDE5;
      continue;
  case 0xDD3:
    if ( r8[al] < 3 ) // jb 
      { _pc = 0xDDF; continue; }
    _data16set(0x94FC, 0x20);
    _pc = 0xDE5;
      continue;
  case 0xDDF:
    _data16set(0x94FC, 0x10);
  case 0xDE5:
    _data[0x9501] = _data[0x9501] + 1;
    r8[al] = _data[0x9501];
    if ( r8[al] <= 7 ) // jbe 
      { _pc = 0xDF5; continue; }
    _data[0x9501] = 1;
  case 0xDF5:
    sub_9A4();
    sub_69A();
    _data[0x9519] = 0;
    sub_E3D();
    sub_2A7F();
    _pc = -1;
  }
}
function sub_E07()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xE07);
    r16[ax] = _data16get(0x9534);
    if ( r16[ax] != 0 ) // jnz 
      { _pc = 0xE15; continue; }
    _data[0x9500] = 1;
    return;
  case 0xE15:
    sub_2329();
    r8[al] = _data[0x9502];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xE27; continue; }
    _data[0x9502] = 0;
    sub_69A();
  case 0xE27:
    sub_2200();
    _data[0x9519] = 1;
    _data[0x951A] = 0;
    _data[0x951B] = 0;
    sub_E3D();
    _pc = -1;
  }
}
function sub_E3D()
{
  STAT(0xE3D);
  r8[bl] = _data[0x9501];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x14F5));
  r16[ax] &= 0x3FF;
  _data16set(0x9528, r16[ax]);
  r16[ax] = _data16get(0x94FC);
  _data16set(0x952A, r16[ax]);
  _data16set(0x950A, 0x80);
  _data[0x950E] = 0;
  _data16set(0x950F, 0);
  _data16set(0x9511, 0);
  _data[0x9513] = 0;
  _data[0x9515] = 0;
  _data[0x9517] = 0;
  _data[0x9432] = 0;
  sub_E84();
}
function sub_E84()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xE84);
    r8[al] = _data[0x950E];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xE93; continue; }
    _data[0x950E] = 0;
    sub_69A();
  case 0xE93:
    _data16set(0x952C, 0);
    sub_B7C();
    si = 0x0D32;
    sub_B58();
    r16[ax] = _data16get(0x950A);
    _data16set(0x1B8F, r16[ax]);
    sub_1B57();
    r16[ax] = _data16get(0x9528);
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] -= 3;
    r16[ax] &= 0x3F;
    _data16set(0x9507, r16[ax]);
    r16[cx] = 0x0F;
  case 0xEC2:
    _push(r16[cx]);
    _push(r16[ax]);
    _push(r16[ax]);
    sub_8BA();
    r16[ax] = _pop();
    r16[cx] = _pop();
    r16[ax] = r16[ax] + 1;
    r16[ax] &= 0x3F;
    if ( --r16[cx] )
      { _pc = 0xEC2; continue; }
    r8[al] = _data[0x9432];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xEEA; continue; }
    si = 0x1B8A;
    r16[bx] = 0x0D49;
    _data[ADR(ds, si + 4)] = 0x0A;
    sub_2121();
    _data[0x1B9C] = 0x23;
    return;
  case 0xEEA:
    r8[al] = _data[0x9519];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xF08; continue; }
    _data[0x9519] = 0;
    si = 0x0DA2;
    r16[ax] = _data16get(0x1B91);
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0x1B8D];
    _data[ADR(ds, si + 3)] = r8[al];
    sub_B58();
  case 0xF08:
    sub_F9D();
    r8[al] = _data[0x951A];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xF23; continue; }
    _data[0x951A] = 1;
    si = 0x0DC3;
    _data[ADR(ds, si)] &= 0x0DF;
    sub_1CD9();
    sub_B58();
  case 0xF23:
    r8[al] = _data[0x951B];
    if ( r8[al] == 0 ) // jz 
      return;
    _data[0x951B] = 1;
    si = 0x0DC3;
    _data[ADR(ds, si)] |= 0x20;
    sub_1CD9();
    sub_B58();
    _pc = -1;
  }
}
function sub_F3C()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0xF3C);
    _data[0x951C] = 0;
    sub_2DDC();
    _data16set(0x9528, 0x1A);
    _data16set(0x9547, 0);
    _data16set(0x951E, 0);
    _data[0x9524] = 0;
    _data[0x9549] = 3;
    sub_B7C();
    si = 0x0D04;
    sub_B58();
    sub_2DF6();
    r8[al] = _data[0x951A];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xF84; continue; }
    _data[0x951A] = 1;
    si = 0x0D1B;
    _data[ADR(ds, si)] &= 0x0DF;
    sub_2F50();
    sub_B58();
  case 0xF84:
    r8[al] = _data[0x951B];
    if ( r8[al] == 0 ) // jz 
      return;
    _data[0x951B] = 1;
    si = 0x0D1B;
    _data[ADR(ds, si)] |= 0x20;
    sub_2F50();
    sub_B58();
    _pc = -1;
  }
}
function sub_F9D()
{
  STAT(0xF9D);
  r16[ax] = _data16get(0x1B8F);
  _data16set(0x9433, r16[ax]);
  _data16set(0x9435, r16[ax]);
  _data16set(0x9437, r16[ax]);
  _data16set(0x9439, r16[ax]);
  r16[ax] = _data16get(0x1B91);
  _data16set(0x943B, r16[ax]);
  _data16set(0x943D, r16[ax]);
  _data16set(0x943F, r16[ax]);
  _data16set(0x9441, r16[ax]);
  r8[al] = _data[0x1B8E];
  _data[0x9443] = r8[al];
  _data[0x9444] = r8[al];
  _data[0x9445] = r8[al];
  _data[0x9446] = r8[al];
  r8[al] = _data[0x1B8D];
  _data[0x9447] = r8[al];
  _data[0x9448] = r8[al];
  _data[0x9449] = r8[al];
  _data[0x944A] = r8[al];
}
function sub_FDA()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
  case 0xFDA:
    STAT(0xFDA);
    r8[al] = _data[0x94FF];
    _data[0x9509] = r8[al];
    si = 0x1B8A;
  case 0xFE3:
    r8[al] = _data[0x9513];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xFF5; continue; }
    sub_E07();
    r8[al] = _data[0x9500];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0xFDA; continue; }
    return;
  case 0xFF5:
    r8[al] = _data[0x94FF];
    if ( r8[al] == _data[0x9509] ) // jz 
      { _pc = 0x1036; continue; }
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x100E; continue; }
    r8[al] = 0x0B;
    sub_3840();
    sub_F3C();
    _pc = 0xFDA;
      continue;
    _pc = 0x1036;
      continue;
  case 0x100E:
    r8[al] = 0x0B;
    sub_3840();
    r8[al] = _data[0x951D];
    if ( r8[al] != 0x0F0 ) // jnz 
      { _pc = 0x101F; continue; }
    sub_DC0();
    _pc = 0x1034;
      continue;
  case 0x101F:
    r8[al] = _data[0x1BA0];
    r8[al] &= 0x7F;
    if ( r8[al] <= 0x28 ) // jbe 
      { _pc = 0x1031; continue; }
    if ( r8[al] >= 0x58 ) // jnb 
      { _pc = 0x1031; continue; }
    _data[0x9432] = 1;
  case 0x1031:
    sub_E84();
  case 0x1034:
    _pc = 0xFDA;
      continue;
  case 0x1036:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      return;
    if ( !(r8[al] & 2) ) // jz 
      { _pc = 0x1054; continue; }
    _push(si);
    r8[bl] = _data[ADR(ds, si + 0x12)];
    if ( r8[bl] == 0 ) // jz 
      { _pc = 0x1053; continue; }
    r8[bh] = 0;
    r16[bx]--;
    r16[bx] <<= 1;
    //unknown_command(); // call	cs:off_code_105A[bx]
    switch ( r16[bx] >> 1 )
    {
    case 0: sub_1108(); break;
    case 1: sub_176C(); break;
    case 2: sub_1783(); break;
    case 3: sub_10C6(); break;
    case 4: sub_17AC(); break;
    case 5: sub_17D6(); break;
    case 6: sub_18A9(); break;
    case 7: sub_1A9E(); break;
    case 8: sub_10C6(); break;
    case 9: sub_1993(); break;
    case 10: sub_19C2(); break;
    case 11: sub_2E02(); break;
    case 12: sub_10C6(); break;
    case 13: sub_2FE8(); break;
    case 14: sub_300A(); break;
    case 15: sub_16FE(); break;
    case 16: sub_12CB(); break;
    case 17: sub_10C6(); break;
    case 18: sub_12EB(); break;
    case 19: sub_15FC(); break;
    case 20: sub_16DF(); break;
    case 21: sub_16D6(); break;
    case 22: sub_1740(); break;
    case 23: sub_1384(); break;
    case 24: sub_13A8(); break;
    case 25: sub_14F0(); break;
    case 26: sub_10F3(); break;
    case 27: sub_18C7(); break;
    case 28: sub_1429(); break;
    case 29: sub_17F4(); break;
    case 30: sub_171F(); break;
    case 31: sub_1B09(); break;
    case 32: sub_1B4A(); break;
    case 33: sub_2F50(); break;
    case 34: sub_12A7(); break;
  	  _ASSERT(0);
    }
  case 0x1053:
    si = _pop();
  case 0x1054:
    si += 0x17;
    _pc = 0xFE3;
      continue;
    _pc = -1;
  }
}
function sub_10A0()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x10A0);
    r8[al] = _data[ADR(ds, si + 0x0A)];
    r8[al] -= _data[ADR(ds, si + 3)];
    r8[al] -= _data[ADR(ds, si + 0x0C)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 7));
    r16[ax] &= 0x3FF;
    r16[bx] = _data16get(0x9528);
    if ( r16[ax] >= r16[bx] ) // jnb 
      { _pc = 0x10BB; continue; }
    r16[ax] += 0x400;
  case 0x10BB:
    r16[ax] -= r16[bx];
    if ( r16[ax] <= 0x200 ) // jbe 
      return;
    _data[ADR(ds, si)] = 0;
    _pc = -1;
  }
}
function sub_10C6()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x10C6);
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] += _data[ADR(ds, si + 0x0C)];
    _cbw();
    r16[ax] = - r16[ax];
    r16[ax] += _data16get(ADR(ds, si + 7));
    r16[ax] &= 0x3FF;
    r16[bx] = _data16get(0x9528);
    r16[bx] += 0x0A0;
    r16[bx] &= 0x3FF;
    if ( r16[ax] >= r16[bx] ) // jnb 
      { _pc = 0x10E8; continue; }
    r16[ax] += 0x400;
  case 0x10E8:
    r16[ax] -= r16[bx];
    if ( r16[ax] >= 0x200 ) // jnb 
      return;
    _data[ADR(ds, si)] = 0;
    _pc = -1;
  }
}
function sub_10F3()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x10F3);
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[al] = _data[ADR(ds, si + 0x16)];
    if ( r8[al] <= 8 ) // jbe 
      { _pc = 0x10FF; continue; }
    r8[al] = 8;
  case 0x10FF:
    r8[ah] = 0;
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - r16[ax]);
    sub_10A0();
    _pc = -1;
  }
}
function sub_1108()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1108);
    sub_1B80();
    sub_1BB9();
    r16[bx] = _data16get(0x954C);
    r16[ax] = _data16get(0x952C);
    if ( !(r8[bl] & 1) ) // jz 
      { _pc = 0x1131; continue; }
    r16[ax] -= 1;
    if ( _short(r16[ax]) < 0 ) // js 
      { _pc = 0x1127; continue; }
    if ( _short(r16[ax]) <= _short(4) ) // jle 
      { _pc = 0x1127; continue; }
    r16[ax] = 4;
  case 0x1127:
    if ( _short(r16[ax]) >= _short(0x0FFE8) ) // jge 
      { _pc = 0x112F; continue; }
    r16[ax] = 0x0FFE8;
  case 0x112F:
    _pc = 0x1158;
      continue;
  case 0x1131:
    if ( !(r8[bl] & 2) ) // jz 
      { _pc = 0x114D; continue; }
    r16[ax] += 1;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1143; continue; }
    if ( _short(r16[ax]) >= _short(0x0FFFC) ) // jge 
      { _pc = 0x1143; continue; }
    r16[ax] = 0x0FFFC;
  case 0x1143:
    if ( _short(r16[ax]) <= _short(0x18) ) // jle 
      { _pc = 0x114B; continue; }
    r16[ax] = 0x18;
  case 0x114B:
    _pc = 0x1158;
      continue;
  case 0x114D:
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x1158; continue; }
    if ( _short(r16[ax]) <= _short(0) ) // jle 
      { _pc = 0x1157; continue; }
    r16[ax]--;
    _pc = 0x1158;
      continue;
  case 0x1157:
    r16[ax] = r16[ax] + 1;
  case 0x1158:
    _data16set(0x952C, r16[ax]);
    r16[ax] += 3;
    r16[ax] = _sar16(r16[ax]);
    r16[ax] = _sar16(r16[ax]);
    //unknown_command(); // sar	ax, 1
    //unknown_command(); // sar	ax, 1
    r16[ax] += _data16get(0x1B8F);
    if ( _short(r16[ax]) >= _short(0x14) ) // jge 
      { _pc = 0x1174; continue; }
    r16[ax] = 0x14;
    _data16set(0x952C, 0);
  case 0x1174:
    if ( _short(r16[ax]) <= _short(0x0EC) ) // jle 
      { _pc = 0x1182; continue; }
    r16[ax] = 0x0EC;
    _data16set(0x952C, 0);
  case 0x1182:
    _data16set(0x1B8F, r16[ax]);
    r8[al] = _data[0x1B8E];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x118F; continue; }
    sub_1B57();
  case 0x118F:
    sub_1C78();
    sub_A51();
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x119F; continue; }
    sub_1C56();
    _pc = 0x11BC;
      continue;
  case 0x119F:
    _data[0x1B9E] = _data[0x1B9E] + 1;
    _data[0x1B9E] &= 0x3F;
    sub_A51();
  //  r16[ax] = 0;					// CLEAR HIT TEST ----- TODO!
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x11B3; continue; }
    // hit - test
    sub_1C56();
  case 0x11B3:
    _data[0x1B9E]--;
    _data[0x1B9E] &= 0x3F;
  case 0x11BC:
    r16[ax] = _data16get(0x9542);
    if ( _short(r16[ax]) > _short(0) ) // jg 
      { _pc = 0x11C8; continue; }
    sub_1C33();
    return;
  case 0x11C8:
    r8[al] = _data[0x1B8E];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x11DE; continue; }
    _data[0x9515] = _data[0x9515] + 1;
    r8[al] = _data[0x9515];
    if ( r8[al] < 4 ) // jb 
      return;
    sub_1C33();
    return;
  case 0x11DE:
    r16[ax] = _data16get(0x953E);
    if ( _short(r16[ax]) <= _short(0) ) // jle 
      { _pc = 0x11F0; continue; }
    r16[ax] = _data16get(0x954C);
    if ( !(r8[al] & 0x80) ) // jz 
      { _pc = 0x11F0; continue; }
    sub_1D1E();
  case 0x11F0:
    r16[ax] = _data16get(0x954C);
    r8[bl] = _data[0x951A];
    if ( !(r8[al] & 0x40) ) // jz 
      { _pc = 0x1235; continue; }
    if ( r8[bl] != 0 ) // jnz 
      { _pc = 0x1224; continue; }
    r16[ax] = _data16get(0x9536);
    if ( r16[ax] <= 0 ) // jbe 
      { _pc = 0x1222; continue; }
    _data[0x951A] = 1;
    si = 0x0DC3;
    _data[ADR(ds, si)] &= 0x0DF;
    sub_1CD9();
    sub_B58();
    _data16set(0x9538, _data16get(0x9538) -1);
    r8[al] = 1;
    sub_3840();
  case 0x1222:
    _pc = 0x1233;
      continue;
  case 0x1224:
    if ( r8[bl] != 2 ) // jnz 
      { _pc = 0x1233; continue; }
    _data[0x951A] = 3;
    r8[al] = 2;
    sub_3840();
  case 0x1233:
    _pc = 0x124B;
      continue;
  case 0x1235:
    if ( r8[bl] != 1 ) // jnz 
      { _pc = 0x1241; continue; }
    _data[0x951A] = 2;
    _pc = 0x124B;
      continue;
  case 0x1241:
    if ( r8[bl] != 3 ) // jnz 
      { _pc = 0x124B; continue; }
    _data[0x951A] = 0;
  case 0x124B:
    r16[ax] = _data16get(0x954C);
    r8[bl] = _data[0x951B];
    if ( !(r8[al] & 0x20) ) // jz 
      { _pc = 0x1290; continue; }
    if ( r8[bl] != 0 ) // jnz 
      { _pc = 0x127F; continue; }
    r16[ax] = _data16get(0x9536);
    if ( r16[ax] <= 0 ) // jbe 
      { _pc = 0x127D; continue; }
    _data[0x951B] = 1;
    si = 0x0DC3;
    _data[ADR(ds, si)] |= 0x20;
    sub_1CD9();
    sub_B58();
    _data16set(0x9538, _data16get(0x9538) -1);
    r8[al] = 1;
    sub_3840();
  case 0x127D:
    _pc = 0x128E;
      continue;
  case 0x127F:
    if ( r8[bl] != 2 ) // jnz 
      { _pc = 0x128E; continue; }
    _data[0x951B] = 3;
    r8[al] = 2;
    sub_3840();
  case 0x128E:
    return;
  case 0x1290:
    if ( r8[bl] != 1 ) // jnz 
      { _pc = 0x129C; continue; }
    _data[0x951B] = 2;
    return;
  case 0x129C:
    if ( r8[bl] != 3 ) // jnz 
      return;
    _data[0x951B] = 0;
    _pc = -1;
  }
}
function sub_12A7()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x12A7);
    r16[ax] = _data16get(0x952A);
    r16[ax] -= 3;
    if ( _short(r16[ax]) < 0 ) // js 
      { _pc = 0x12B4; continue; }
    _data16set(0x952A, r16[ax]);
    _pc = 0x12B7;
      continue;
  case 0x12B4:
    sub_1C33();
  case 0x12B7:
    sub_1BB9();
    sub_1B57();
    si = 0x1B8A;
    r16[bx] = 0x0D49;
    _data[ADR(ds, si + 4)] = 0x0A;
    sub_2121();
    _pc = -1;
  }
}
function sub_12CB()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x12CB);
    r16[ax] = _data16get(0x952A);
    r16[ax]--;
    if ( _short(r16[ax]) < 0 ) // js 
      { _pc = 0x12D4; continue; }
    _data16set(0x952A, r16[ax]);
  case 0x12D4:
    sub_1BB9();
    sub_1B57();
    _data[0x9514] = _data[0x9514] + 1;
    r8[al] = _data[0x9514];
    if ( r8[al] < 0x28 ) // jb 
      return;
    _data[0x9513] = 1;
    _pc = -1;
  }
}
function sub_12EB()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x12EB);
    sub_10A0();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x12F5; continue; }
    return;
  case 0x12F5:
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - 0x10);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    r8[al] = _data[ADR(ds, si + 4)];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x1312; continue; }
    r8[al] = _data[ADR(ds, si + 3)];
    if ( r8s[al] <= _char(0x9C) ) // jle 
      { _pc = 0x1310; continue; }
    _data[ADR(ds, si + 3)] -= 8;
  case 0x1310:
    _pc = 0x1321;
      continue;
  case 0x1312:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x1321; continue; }
    r8[al] = _data[ADR(ds, si + 3)];
    if ( r8s[al] >= _char(0x64) ) // jge 
      { _pc = 0x1321; continue; }
    _data[ADR(ds, si + 3)] += 8;
  case 0x1321:
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _push(r16[ax]);
    sub_7FD();
    si = _pop();
    if ( r8s[al] < _datas[ADR(ds, si + 3)] ) // jl 
      { _pc = 0x1338; continue; }
    sub_2092();
    return;
  case 0x1338:
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    _data[ADR(ds, si + 0x14)] = r8[cl];
    _push(r16[cx]);
    sub_AD5();
    si = _pop();
    if ( r16[ax] == 0 ) // jz 
      return;
    _push(si);
    r8[al] = _data[ADR(ds, si + 0x14)];
    r8[ah] = 0;
    _push(r16[bx]);
    _push(r16[ax]);
    sub_1C0A();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0x1382; continue; }
    r16[bx] = _pop();
    _push(r16[bx]);
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] -= _data[OFS(r16[bx] + 3)];
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x1367; continue; }
    r8[al] = - r8[al];
  case 0x1367:
    if ( r8[al] >= 0x10 ) // jnb 
      { _pc = 0x1382; continue; }
    _data[ADR(ds, si + 0x15)]--;
    if ( _datas[ADR(ds, si + 0x15)] >= 0 ) // jns 
      { _pc = 0x137A; continue; }
    sub_20DB();
    r8[al] = 6;
    sub_3840();
    _pc = 0x137D;
      continue;
  case 0x137A:
    sub_2662();
  case 0x137D:
    si = _pop();
    _push(si);
    sub_2047();
  case 0x1382:
    si = _pop();
    _pc = -1;
  }
}
function sub_1384()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1384);
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x138E; continue; }
    _data[ADR(ds, si)] = 0;
  case 0x138E:
    sub_1CD9();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x20 ) // jnz 
      { _pc = 0x139C; continue; }
    r8[al] = _data[0x951A];
    _pc = 0x139F;
      continue;
  case 0x139C:
    r8[al] = _data[0x951B];
  case 0x139F:
    if ( r8[al] != 3 ) // jnz 
      return;
    _data[ADR(ds, si + 0x12)] = 0x19;
    _pc = -1;
  }
}
function sub_13A8()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x13A8);
    sub_10A0();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x13B2; continue; }
    return;
  case 0x13B2:
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - 6);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _push(r16[ax]);
    sub_7FD();
    si = _pop();
    r8[al] += 4;
    _data[ADR(ds, si + 3)] = r8[al];
    _data[ADR(ds, si + 0x14)] = r8[cl];
    _data[ADR(ds, si + 4)] = r8[bl];
    r16[bx] = 0x0DDA;
    sub_2121();
    r8[al] = _data[ADR(ds, si + 4)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x13F5; continue; }
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    _data[ADR(ds, si + 0x15)]--;
    if ( _datas[ADR(ds, si + 0x15)] >= 0 ) // jns 
      { _pc = 0x13F5; continue; }
    sub_20F0();
    _data[ADR(ds, si)] = 0;
    return;
  case 0x13F5:
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r8[cl] = _data[ADR(ds, si + 0x14)];
    r8[ch] = 0;
    _push(r16[cx]);
    sub_AD5();
    si = _pop();
    if ( r16[ax] == 0 ) // jz 
      return;
    _push(si);
    r8[al] = _data[ADR(ds, si + 0x14)];
    r8[ah] = 0;
    _push(r16[bx]);
    _push(r16[ax]);
    sub_1C0A();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0x1427; continue; }
    sub_20DB();
    r8[al] = 6;
    sub_3840();
    si = _pop();
    _push(si);
    _data[ADR(ds, si)] = 0;
  case 0x1427:
    si = _pop();
    _pc = -1;
  }
}
function sub_1429()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1429);
    sub_10C6();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1433; continue; }
    return;
  case 0x1433:
    r8[al] = _data[ADR(ds, si + 1)];
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x1440; continue; }
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 5);
    _pc = 0x146A;
      continue;
  case 0x1440:
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x144A; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 5);
    _pc = 0x146A;
      continue;
  case 0x144A:
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x1458; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 3);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 2);
    _pc = 0x146A;
      continue;
  case 0x1458:
    if ( r8[al] != 3 ) // jnz 
      { _pc = 0x1466; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 3);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 2);
    _pc = 0x146A;
      continue;
  case 0x1466:
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 5);
  case 0x146A:
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    r16[ax] = _data16get(ADR(ds, si + 5));
    if ( _short(r16[ax]) >= _short(0x0C) ) // jge 
      { _pc = 0x147B; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x147B:
    if ( _short(r16[ax]) <= _short(0x0F4) ) // jle 
      { _pc = 0x1484; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1484:
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _push(r16[ax]);
    sub_7FD();
    si = _pop();
    r8[al] += 8;
    _data[ADR(ds, si + 3)] = r8[al];
    _data[ADR(ds, si + 0x14)] = r8[cl];
    _data[ADR(ds, si + 4)] = r8[bl];
    r8[bl] = _data[ADR(ds, si + 1)];
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] + 0x10FF));
    sub_2121();
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x14B2; continue; }
    return;
  case 0x14B2:
    r16[ax] = _data16get(ADR(ds, si + 5));
    r16[ax] -= _data16get(0x1B8F);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x14BD; continue; }
    r16[ax] = - r16[ax];
  case 0x14BD:
    if ( r16[ax] >= 0x10 ) // jnb 
      return;
    r16[ax] = _data16get(ADR(ds, si + 7));
    r16[ax] -= _data16get(0x1B91);
    r16[ax] -= 8;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x14D0; continue; }
    r16[ax] = - r16[ax];
  case 0x14D0:
    if ( r16[ax] >= 0x10 ) // jnb 
      return;
    r8[al] = 5;
    sub_3840();
    _data16set(0x9544, _data16get(0x9544) - 0x64);
    _data[0x12A0] = 1;
    sub_20F0();
    _data[0x12A0] = 5;
    _data[ADR(ds, si)] = 0;
    _pc = -1;
  }
}
function sub_14F0()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x14F0);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 1);
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _push(r16[ax]);
    sub_7FD();
    si = _pop();
    _data[ADR(ds, si + 3)] = r8[al];
    _data[ADR(ds, si + 0x14)] = r8[cl];
    _data[ADR(ds, si + 4)] = r8[bl];
    r8[bl] = _data[ADR(ds, si + 1)];
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] + 0x0FE1));
    sub_2121();
    r8[al] = _data[0x1B9C];
    if ( r8[al] == 0x11 ) // jz 
      { _pc = 0x1548; continue; }
    r16[ax] = _data16get(ADR(ds, si + 5));
    r16[ax] -= _data16get(0x1B8F);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x152A; continue; }
    r16[ax] = - r16[ax];
  case 0x152A:
    if ( r16[ax] >= 0x1A ) // jnb 
      { _pc = 0x1548; continue; }
    r16[ax] = _data16get(ADR(ds, si + 7));
    r16[ax] -= _data16get(0x1B91);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x153A; continue; }
    r16[ax] = - r16[ax];
  case 0x153A:
    if ( r16[ax] >= 0x12 ) // jnb 
      { _pc = 0x1548; continue; }
    _data16set(0x9544, _data16get(0x9544) - 0x0C);
    _data[ADR(ds, si + 0x15)] = 0x0FF;
  case 0x1548:
    di = 0x1BA1;
  case 0x154B:
    r8[al] = _data[ADR(ds, si + 0x15)];
    if ( r8s[al] >= _char(0) ) // jge 
      { _pc = 0x1561; continue; }
    r8[al] = 7;
    sub_3840();
    sub_20F0();
    _data[ADR(ds, si)] = 0;
    sub_2676();
    return;
  case 0x1561:
    r8[al] = _data[di];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0x15C0; continue; }
    if ( !(r8[al] & 0x40) ) // jz 
      { _pc = 0x15BB; continue; }
    _push(di);
    r16[ax] = _data16get(OFS(di + 5));
    r16[ax] -= _data16get(ADR(ds, si + 5));
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1576; continue; }
    r16[ax] = - r16[ax];
  case 0x1576:
    if ( r16[ax] >= 0x14 ) // jnb 
      { _pc = 0x15BA; continue; }
    r16[ax] = _data16get(OFS(di + 7));
    r16[ax] -= _data16get(ADR(ds, si + 7));
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1585; continue; }
    r16[ax] = - r16[ax];
  case 0x1585:
    if ( r16[ax] >= 0x10 ) // jnb 
      { _pc = 0x15BA; continue; }
    r8[al] = _data[OFS(di + 0x12)];
    if ( r8[al] != 0x19 ) // jnz 
      { _pc = 0x159A; continue; }
    _data[ADR(ds, si + 0x15)] = 0x0FF;
    _data[di] = 0;
    _pc = 0x15BA;
      continue;
  case 0x159A:
    r8[al] = _data[OFS(di + 3)];
    r8[al] -= _data[ADR(ds, si + 3)];
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x15A4; continue; }
    r8[al] = - r8[al];
  case 0x15A4:
    if ( r8[al] >= 0x10 ) // jnb 
      { _pc = 0x15BA; continue; }
    _data[ADR(ds, si + 0x15)]--;
    _push(si);
    si = di;
    sub_2092();
    r8[al] = 3;
    sub_3840();
    sub_2662();
    si = _pop();
  case 0x15BA:
    di = _pop();
  case 0x15BB:
    di += 0x17;
    _pc = 0x154B;
      continue;
  case 0x15C0:
    r8[al] = _data[0x1B9C];
    if ( r8[al] == 0x11 ) // jz 
      { _pc = 0x15F8; continue; }
    r16[ax] = _data16get(0x1B91);
    if ( r16[ax] <= _data16get(ADR(ds, si + 7)) ) // jbe 
      { _pc = 0x15F8; continue; }
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x15D9; continue; }
    r16[ax] = - r16[ax];
  case 0x15D9:
    if ( r16[ax] >= 0x20 ) // jnb 
      { _pc = 0x15F8; continue; }
    _data[ADR(ds, si + 0x16)]--;
    if ( _datas[ADR(ds, si + 0x16)] >= 0 ) // jns 
      { _pc = 0x15EE; continue; }
    _data[ADR(ds, si + 0x16)] = 7;
    _data[0x9518] = 1;
    _pc = 0x15F3;
      continue;
  case 0x15EE:
    _data[0x9518] = 0;
  case 0x15F3:
    _push(si);
    sub_1DEF();
    si = _pop();
  case 0x15F8:
    sub_10C6();
    _pc = -1;
  }
}
function sub_15FC()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x15FC);
    sub_10C6();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1606; continue; }
    return;
  case 0x1606:
    r8[al] = _data[ADR(ds, si + 1)];
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x1613; continue; }
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 8);
    _pc = 0x163D;
      continue;
  case 0x1613:
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x161D; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 8);
    _pc = 0x163D;
      continue;
  case 0x161D:
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x162B; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 6);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
    _pc = 0x163D;
      continue;
  case 0x162B:
    if ( r8[al] != 3 ) // jnz 
      { _pc = 0x1639; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 6);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
    _pc = 0x163D;
      continue;
  case 0x1639:
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 8);
  case 0x163D:
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    r16[ax] = _data16get(ADR(ds, si + 5));
    if ( _short(r16[ax]) >= _short(4) ) // jge 
      { _pc = 0x164E; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x164E:
    if ( _short(r16[ax]) <= _short(0x0FC) ) // jle 
      { _pc = 0x1657; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1657:
    r8[al] = _data[ADR(ds, si + 4)];
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x166B; continue; }
    r8[al] = _data[ADR(ds, si + 3)];
    if ( r8s[al] >= _char(0x64) ) // jge 
      { _pc = 0x1669; continue; }
    _data[ADR(ds, si + 3)] += 4;
  case 0x1669:
    _pc = 0x167A;
      continue;
  case 0x166B:
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x167A; continue; }
    r8[al] = _data[ADR(ds, si + 3)];
    if ( r8s[al] <= _char(0x9C) ) // jle 
      { _pc = 0x167A; continue; }
    _data[ADR(ds, si + 3)] -= 4;
  case 0x167A:
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _push(r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _push(r16[ax]);
    sub_7FD();
    si = _pop();
    if ( r8s[al] < _datas[ADR(ds, si + 3)] ) // jl 
      { _pc = 0x1691; continue; }
    sub_2092();
    return;
  case 0x1691:
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x1699; continue; }
    return;
  case 0x1699:
    r16[ax] = _data16get(ADR(ds, si + 5));
    r16[ax] -= _data16get(0x1B8F);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x16A4; continue; }
    r16[ax] = - r16[ax];
  case 0x16A4:
    if ( r16[ax] >= 0x0C ) // jnb 
      return;
    r16[ax] = _data16get(ADR(ds, si + 7));
    r16[ax] -= _data16get(0x1B91);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x16B4; continue; }
    r16[ax] = - r16[ax];
  case 0x16B4:
    if ( r16[ax] >= 8 ) // jnb 
      return;
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] -= _data[0x1B8D];
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x16C4; continue; }
    r8[al] = - r8[al];
  case 0x16C4:
    if ( r8[al] >= 0x10 ) // jnb 
      return;
    _data16set(0x9544, _data16get(0x9544) - 1);
    sub_2092();
    r8[al] = 4;
    sub_3840();
    _pc = -1;
  }
}
function sub_16D6()
{
  STAT(0x16D6);
  _data[ADR(ds, si + 4)]--;
  if ( _datas[ADR(ds, si + 4)] >= 0 ) // jns 
    return;
  _data[ADR(ds, si)] = 0;
}
function sub_16DF()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x16DF);
    r8[al] = _data[ADR(ds, si + 4)];
    _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
    if ( r8[al] < 4 ) // jb 
      { _pc = 0x16ED; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x16ED:
    r8[al] <<= 1;
    r8[bl] = r8[al];
    r8[bh] = 0;
    r16[ax] = _data16get(OFS(r16[bx] + 0x143E));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
    sub_10C6();
    _pc = -1;
  }
}
function sub_16FE()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x16FE);
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[al] = _data[ADR(ds, si + 0x16)];
    r8[al] >>= 1;
    r8[al] >>= 1;
    r8[al] &= 7;
    if ( r8s[al] < _char(5) ) // jl 
      { _pc = 0x1712; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1712:
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x12B5;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_171F()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x171F);
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[al] = _data[ADR(ds, si + 0x16)];
    r8[al] >>= 1;
    r8[al] >>= 1;
    r8[al] &= 7;
    if ( r8s[al] < _char(6) ) // jl 
      { _pc = 0x1733; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1733:
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x12F5;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_1740()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1740);
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[al] = _data[ADR(ds, si + 0x16)];
    r8[al] &= 7;
    if ( r8s[al] < _char(4) ) // jl 
      { _pc = 0x1762; continue; }
    r8[al] = _data[ADR(ds, si)];
    if ( !(r8[al] & 0x20) ) // jz 
      { _pc = 0x1759; continue; }
    _data[0x9517] &= 0x7F;
    _pc = 0x175E;
      continue;
  case 0x1759:
    _data[0x9517] &= 0x0FE;
  case 0x175E:
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1762:
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x133D;
    sub_2121();
    _pc = -1;
  }
}
function sub_176C()
{
  STAT(0x176C);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  r8[al] >>= 1;
  r8[al] &= 3;
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x0E2B;
  sub_2121();
  sub_10C6();
}
function sub_1783()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1783);
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[al] = _data[ADR(ds, si + 0x16)];
    r8[al] >>= 1;
    r8[al] &= 7;
    if ( r8[al] < 6 ) // jb 
      { _pc = 0x1797; continue; }
    r8[al] = 0;
    _data[ADR(ds, si + 0x16)] = 0;
  case 0x1797:
    r8[bl] = r8[al];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x0E4C)];
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x0E52;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_17AC()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x17AC);
    sub_215B();
    if ( r16[cx] == 0 ) // jz 
      { _pc = 0x17CC; continue; }
    _data[ADR(ds, si + 0x16)]--;
    if ( _datas[ADR(ds, si + 0x16)] >= 0 ) // jns 
      { _pc = 0x17C4; continue; }
    _data[ADR(ds, si + 0x16)] = 8;
    _data[0x9518] = 1;
    _pc = 0x17C9;
      continue;
  case 0x17C4:
    _data[0x9518] = 0;
  case 0x17C9:
    sub_1F0B();
  case 0x17CC:
    r16[bx] = 0x0E73;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_17D6()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x17D6);
    sub_215B();
    if ( r16[cx] == 0 ) // jz 
      { _pc = 0x17EA; continue; }
    _data[ADR(ds, si + 0x16)]--;
    if ( _datas[ADR(ds, si + 0x16)] >= 0 ) // jns 
      { _pc = 0x17EA; continue; }
    _data[ADR(ds, si + 0x16)] = 0x12;
    sub_2005();
  case 0x17EA:
    r16[bx] = 0x0E9C;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_17F4()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x17F4);
    sub_10C6();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x17FE; continue; }
    return;
  case 0x17FE:
    r8[al] = _data[ADR(ds, si + 1)];
    if ( r8[al] != 2 ) // jnz 
      { _pc = 0x180B; continue; }
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
    _pc = 0x1835;
      continue;
  case 0x180B:
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1815; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 4);
    _pc = 0x1835;
      continue;
  case 0x1815:
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x1823; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 4);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
    _pc = 0x1835;
      continue;
  case 0x1823:
    if ( r8[al] != 3 ) // jnz 
      { _pc = 0x1831; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 4);
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
    _pc = 0x1835;
      continue;
  case 0x1831:
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 4);
  case 0x1835:
    _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
    r16[ax] = _data16get(ADR(ds, si + 5));
    if ( _short(r16[ax]) >= _short(8) ) // jge 
      { _pc = 0x1846; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x1846:
    if ( _short(r16[ax]) <= _short(0x0F8) ) // jle 
      { _pc = 0x184F; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x184F:
    _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
    r8[bl] = _data[ADR(ds, si + 0x16)];
    if ( r8[bl] < 0x10 ) // jb 
      { _pc = 0x185E; continue; }
    sub_2099();
    return;
  case 0x185E:
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x1467)];
    _data[ADR(ds, si + 3)] += r8[al];
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x186F; continue; }
    return;
  case 0x186F:
    r16[ax] = _data16get(ADR(ds, si + 5));
    r16[ax] -= _data16get(0x1B8F);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x187A; continue; }
    r16[ax] = - r16[ax];
  case 0x187A:
    if ( r16[ax] >= 0x0E ) // jnb 
      return;
    r16[ax] = _data16get(ADR(ds, si + 7));
    r16[ax] -= _data16get(0x1B91);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x188A; continue; }
    r16[ax] = - r16[ax];
  case 0x188A:
    if ( r16[ax] >= 0x0A ) // jnb 
      return;
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] -= _data[0x1B8D];
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x189A; continue; }
    r8[al] = - r8[al];
  case 0x189A:
    if ( r8[al] >= 0x10 ) // jnb 
      return;
    _data16set(0x9544, _data16get(0x9544) - 0x0A);
    r8[al] = 5;
    sub_3840();
    _pc = -1;
  }
}
function sub_18A9()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x18A9);
    sub_215B();
    if ( r16[cx] == 0 ) // jz 
      { _pc = 0x18BD; continue; }
    _data[ADR(ds, si + 0x16)]--;
    if ( _datas[ADR(ds, si + 0x16)] >= 0 ) // jns 
      { _pc = 0x18BD; continue; }
    _data[ADR(ds, si + 0x16)] = 0x28;
    sub_1FBA();
  case 0x18BD:
    r16[bx] = 0x0EC5;
    sub_2121();
    sub_10C6();
    _pc = -1;
  }
}
function sub_18C7()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x18C7);
    r8[al] = _data[0x952E];
    r8[al] &= _data[0x952F];
    r8[al] &= _data[0x9530];
    r8[al] &= _data[0x9531];
    r8[al] &= _data[0x9532];
    r8[al] &= _data[0x9533];
    if ( r8[al] ) // jnz 
      { _pc = 0x18E4; continue; }
    sub_10C6();
    return;
  case 0x18E4:
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    r16[ax] -= 0x0C;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x18F1; continue; }
    r16[ax] = - r16[ax];
  case 0x18F1:
    r16[cx] = _data16get(0x1B91);
    r16[cx] -= 8;
    r16[cx] -= _data16get(ADR(ds, si + 7));
    if ( _short(r16[cx]) >= 0 ) // jns 
      { _pc = 0x18FF; continue; }
    r16[cx] = - r16[cx];
  case 0x18FF:
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bl] >>= 1;
    r16[ax] += r16[cx];
    if ( r16[ax] > 0x40 ) // ja 
      { _pc = 0x1915; continue; }
    if ( r8[bl] == 8 ) // jz 
      { _pc = 0x1913; continue; }
    _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
  case 0x1913:
    _pc = 0x191D;
      continue;
  case 0x1915:
    if ( r8[bl] == 0 ) // jz 
      { _pc = 0x191D; continue; }
    _data[ADR(ds, si + 4)]--;
  case 0x191D:
    _push(r16[bx]);
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x1483));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
    r16[bx] = _pop();
    if ( r8[bl] < 2 ) // jb 
      { _pc = 0x196B; continue; }
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    r16[ax] -= 0x0C;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1947; continue; }
    r16[ax] = - r16[ax];
    if ( r16[ax] > 0x18 ) // ja 
      { _pc = 0x1945; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) + 1);
  case 0x1945:
    _pc = 0x1952;
      continue;
  case 0x1947:
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x1952; continue; }
    if ( r16[ax] > 0x18 ) // ja 
      { _pc = 0x1952; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) -1);
  case 0x1952:
    if ( r8[bl] != 8 ) // jnz 
      { _pc = 0x196B; continue; }
    if ( r16[cx] > 8 ) // ja 
      { _pc = 0x196B; continue; }
    if ( r16[ax] > 8 ) // ja 
      { _pc = 0x196B; continue; }
    r8[al] = _data[0x1B9C];
    if ( r8[al] == 0x11 ) // jz 
      { _pc = 0x196B; continue; }
    sub_196F();
  case 0x196B:
    sub_10C6();
    _pc = -1;
  }
}
function sub_196F()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x196F);
    r8[al] = _data[0x1B8E];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1982; continue; }
    _data[0x951D] = 0x0F0;
    _data[0x94FF] = 1;
    return;
  case 0x1982:
    _push(si);
    _data[0x1B8E] = 0;
    si = 0x1B8A;
    r16[bx] = 0x0D49;
    sub_2121();
    si = _pop();
    _pc = -1;
  }
}
function sub_1993()
{
  STAT(0x1993);
  sub_1A04();
  r8[al] = _data[0x94FF];
  if ( r8[al] != 1 ) // jnz 
    return;
  r8[al] = _data[0x9501];
  r8[bl] = r8[al];
  r8[al] <<= 1;
  r8[bl] += r8[al];
  r8[bl] += _data[0x9502];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x1495));
  r8[bh] = r8[ah];
  r16[ax] &= 0x3FF;
  _data16set(0x950C, r16[ax]);
  r8[bh] &= 0x0C0;
  _data[0x951D] = r8[bh];
}
function sub_19C2()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x19C2);
    sub_1A04();
    r8[al] = _data[0x94FF];
    if ( r8[al] != 1 ) // jnz 
      return;
    r8[al] = _data[0x9501];
    r8[bl] = r8[al];
    r8[al] <<= 1;
    r8[bl] += r8[al];
    r8[bl] += _data[0x9502];
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x14C5));
    r8[bh] = r8[ah];
    r16[ax] &= 0x3FF;
    _data16set(0x950C, r16[ax]);
    r8[bh] &= 0x0C0;
    _data[0x951D] = r8[bh];
    _data[0x950E] = 1;
    r8[al] = _data[0x9502];
    r8[al] = r8[al] + 1;
    if ( r8[al] <= 2 ) // jbe 
      { _pc = 0x1A00; continue; }
    r8[al] = 0;
  case 0x1A00:
    _data[0x9502] = r8[al];
    _pc = -1;
  }
}
function sub_1A04()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1A04);
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    r16[ax] -= 0x0C;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1A11; continue; }
    r16[ax] = - r16[ax];
  case 0x1A11:
    r16[cx] = _data16get(0x1B91);
    r16[cx] -= _data16get(ADR(ds, si + 7));
    if ( _short(r16[cx]) >= 0 ) // jns 
      { _pc = 0x1A1C; continue; }
    r16[cx] = - r16[cx];
  case 0x1A1C:
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bl] >>= 1;
    r16[ax] += r16[cx];
    if ( r16[ax] > 0x40 ) // ja 
      { _pc = 0x1A32; continue; }
    if ( r8[bl] == 6 ) // jz 
      { _pc = 0x1A30; continue; }
    _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
  case 0x1A30:
    _pc = 0x1A3A;
      continue;
  case 0x1A32:
    if ( r8[bl] == 0 ) // jz 
      { _pc = 0x1A3A; continue; }
    _data[ADR(ds, si + 4)]--;
  case 0x1A3A:
    if ( r8[bl] != 6 ) // jnz 
      { _pc = 0x1A45; continue; }
    _data[ADR(ds, si + 2)] = 0;
    _pc = 0x1A56;
      continue;
  case 0x1A45:
    _push(r16[bx]);
    _data[ADR(ds, si + 2)] = 7;
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x1477));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
    r16[bx] = _pop();
  case 0x1A56:
    if ( r8[bl] < 1 ) // jb 
      { _pc = 0x1A9A; continue; }
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    r16[ax] -= 0x0C;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1A73; continue; }
    r16[ax] = - r16[ax];
    if ( r16[ax] > 0x18 ) // ja 
      { _pc = 0x1A71; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) + 1);
  case 0x1A71:
    _pc = 0x1A7E;
      continue;
  case 0x1A73:
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x1A7E; continue; }
    if ( r16[ax] > 0x18 ) // ja 
      { _pc = 0x1A7E; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) -1);
  case 0x1A7E:
    if ( r16[cx] > 8 ) // ja 
      { _pc = 0x1A9A; continue; }
    if ( r16[ax] > 8 ) // ja 
      { _pc = 0x1A9A; continue; }
    r8[al] = _data[0x1B9C];
    if ( r8[al] == 0x11 ) // jz 
      { _pc = 0x1A9A; continue; }
    r16[ax] = _data16get(0x1B8F);
    _data16set(0x950A, r16[ax]);
    _data[0x94FF] = 1;
  case 0x1A9A:
    sub_10C6();
    _pc = -1;
  }
}
function sub_1A9E()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1A9E);
    sub_10C6();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1AA8; continue; }
    return;
  case 0x1AA8:
    r16[bx] = _data16get(0x1B91);
    r16[bx] -= _data16get(ADR(ds, si + 7));
    if ( _short(r16[bx]) >= 0 ) // jns 
      { _pc = 0x1ABB; continue; }
    if ( _short(r16[bx]) >= _short(0x0FFF0) ) // jge 
      return;
    _data[ADR(ds, si + 2)] = 1;
    return;
  case 0x1ABB:
    if ( _short(r16[bx]) <= _short(0x20) ) // jle 
      { _pc = 0x1AC1; continue; }
    return;
  case 0x1AC1:
    r16[ax] = _data16get(0x1B8F);
    r16[ax] -= _data16get(ADR(ds, si + 5));
    r16[ax] -= 0x0C;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1AD9; continue; }
    r16[ax] = - r16[ax];
    if ( r16[ax] >= 0x18 ) // jnb 
      { _pc = 0x1AD7; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) + 1);
  case 0x1AD7:
    _pc = 0x1AE7;
      continue;
  case 0x1AD9:
    if ( r16[ax] >= 0x18 ) // jnb 
      { _pc = 0x1AE7; continue; }
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x1AE7; continue; }
    _data16set(0x1B8F, _data16get(0x1B8F) -1);
  case 0x1AE7:
    if ( r16[bx] <= 8 ) // jbe 
      { _pc = 0x1AED; continue; }
    return;
  case 0x1AED:
    if ( r16[ax] > 2 ) // ja 
      { _pc = 0x1AF8; continue; }
    _data16set(0x9538, _data16get(0x9538) + 1);
    return;
  case 0x1AF8:
    if ( r16[ax] >= 0x24 ) // jnb 
      return;
    _data16set(0x9542, 0);
    r8[al] = 6;
    sub_3840();
    _pc = -1;
  }
}
function sub_1B09()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1B09);
    sub_10C6();
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1B13; continue; }
    return;
  case 0x1B13:
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x1B1B; continue; }
    return;
  case 0x1B1B:
    r16[ax] = _data16get(ADR(ds, si + 5));
    r16[ax] -= _data16get(0x1B8F);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1B26; continue; }
    r16[ax] = - r16[ax];
  case 0x1B26:
    if ( r16[ax] >= 0x12 ) // jnb 
      return;
    r16[ax] = _data16get(ADR(ds, si + 7));
    r16[ax] -= _data16get(0x1B91);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x1B36; continue; }
    r16[ax] = - r16[ax];
  case 0x1B36:
    if ( r16[ax] >= 0x10 ) // jnb 
      return;
    _data[ADR(ds, si)] = 0;
    r8[al] = _data[ADR(ds, si + 1)];
    sub_2B28();
    r8[al] = 0x0A;
    sub_3840();
    _pc = -1;
  }
}
function sub_1B4A()
{
  STAT(0x1B4A);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - 2);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  sub_10A0();
}
function sub_1B57()
{
  STAT(0x1B57);
  r16[ax] = _data16get(0x1B8F);
  _push(r16[ax]);
  r16[ax] = _data16get(0x9528);
  r16[ax] += 0x70;
  r16[ax] &= 0x3FF;
  _data16set(0x1B91, r16[ax]);
  _push(r16[ax]);
  sub_7FD();
  _data[0x1B8D] = r8[al];
  _data[0x1B9E] = r8[cl];
  _data[0x1B8E] = r8[bl];
  si = 0x1B8A;
  r16[bx] = 0x0D49;
  sub_2121();
}
function sub_1B80()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1B80);
    r16[bx] = _data16get(0x952A);
    r16[ax] = _data16get(0x953A);
    if ( _short(r16[ax]) > _short(0) ) // jg 
      { _pc = 0x1B91; continue; }
    r16[ax] = 8;
    _pc = 0x1B94;
      continue;
  case 0x1B91:
    r16[ax] = _data16get(0x954C);
  case 0x1B94:
    if ( !(r8[al] & 4) ) // jz 
      { _pc = 0x1BA3; continue; }
    r16[bx] = r16[bx] + 1;
    if ( _short(r16[bx]) <= _short(0x40) ) // jle 
      { _pc = 0x1BA1; continue; }
    r16[bx] = 0x40;
  case 0x1BA1:
    _pc = 0x1BB4;
      continue;
  case 0x1BA3:
    if ( !(r8[al] & 8) ) // jz 
      { _pc = 0x1BB4; continue; }
    r16[bx] -= 2;
    if ( _short(r16[bx]) >= _data16gets(0x94FC) ) // jge 
      { _pc = 0x1BB4; continue; }
    r16[bx] = _data16get(0x94FC);
  case 0x1BB4:
    _data16set(0x952A, r16[bx]);
    _pc = -1;
  }
}
function sub_1BB9()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1BB9);
    r16[bx] = _data16get(0x952A);
    r16[bx] += 0x0F;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[ax] = r16[bx];
    r16[ax]--;
    r16[bx] >>= 1;
    r16[ax] += _data16get(0x950F);
    if ( r16[ax] <= 0x8B ) // jbe 
      { _pc = 0x1BDD; continue; }
    r16[ax] = 0;
    _data16set(0x953C, 0x0FFFF);
  case 0x1BDD:
    _data16set(0x950F, r16[ax]);
    r16[ax] = _data16get(0x9528);
    r16[ax] -= r16[bx];
    r16[ax] &= 0x3FF;
    _data16set(0x9528, r16[ax]);
    r16[ax] = _data16get(0x9528);
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] -= 3;
    r16[ax] &= 0x3F;
    if ( r16[ax] == _data16get(0x9507) ) // jz 
      return;
    _data16set(0x9507, r16[ax]);
    _push(r16[ax]);
    sub_8BA();
    _pc = -1;
  }
}
function sub_1C0A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1C0A);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[bx] = _stack16get(bp + arg_2);
    r16[cx] = _stack16get(bp + arg_0);
    si = 0x1B8A;
  case 0x1C16:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      { _pc = 0x1C2F; continue; }
    if ( !(r8[al] & 8) ) // jz 
      { _pc = 0x1C2A; continue; }
    if ( r8[cl] != _data[ADR(ds, si + 0x14)] ) // jnz 
      { _pc = 0x1C2A; continue; }
    if ( r8[bl] == _data[ADR(ds, si + 0x13)] ) // jz 
      { _pc = 0x1C2F; continue; }
  case 0x1C2A:
    si += 0x17;
    _pc = 0x1C16;
      continue;
  case 0x1C2F:
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_1C33()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1C33);
    r8[al] = _data[0x1B9C];
    if ( r8[al] != 0x11 ) // jnz 
      { _pc = 0x1C3B; continue; }
    return;
  case 0x1C3B:
    r8[al] = 0x0C;
    sub_3840();
    si = 0x1B8A;
    sub_20F0();
    _data[0x1B9C] = 0x11;
    _data[0x1B8C] = 0;
    _data[0x9514] = 0;
    _pc = -1;
  }
}
function sub_1C56()
{
  STAT(0x1C56);
  r16[ax] = - r16[ax];
  _data16set(0x9544, r16[ax]);
  _push(r16[ax]);
  r8[al] = 6;
  sub_3840();
  r16[ax] = _pop();
  r16[ax] = r16[bx];
  _push(r16[ax]);
  r8[al] = _data[0x1B9E];
  r8[ah] = 0;
  _push(r16[ax]);
  sub_1C0A();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    return;
  sub_20DB();
}
function sub_1C78()
{
  STAT(0x1C78);
  r16[ax] = _data16get(0x9437);
  _data16set(0x9439, r16[ax]);
  r16[ax] = _data16get(0x9435);
  _data16set(0x9437, r16[ax]);
  r16[ax] = _data16get(0x9433);
  _data16set(0x9435, r16[ax]);
  r16[ax] = _data16get(0x1B8F);
  _data16set(0x9433, r16[ax]);
  r16[ax] = _data16get(0x943F);
  _data16set(0x9441, r16[ax]);
  r16[ax] = _data16get(0x943D);
  _data16set(0x943F, r16[ax]);
  r16[ax] = _data16get(0x943B);
  _data16set(0x943D, r16[ax]);
  r16[ax] = _data16get(0x1B91);
  _data16set(0x943B, r16[ax]);
  r8[al] = _data[0x9445];
  _data[0x9446] = r8[al];
  r8[al] = _data[0x9444];
  _data[0x9445] = r8[al];
  r8[al] = _data[0x9443];
  _data[0x9444] = r8[al];
  r8[al] = _data[0x1B8E];
  _data[0x9443] = r8[al];
  r8[al] = _data[0x9449];
  _data[0x944A] = r8[al];
  r8[al] = _data[0x9448];
  _data[0x9449] = r8[al];
  r8[al] = _data[0x9447];
  _data[0x9448] = r8[al];
  r8[al] = _data[0x1B8D];
  _data[0x9447] = r8[al];
}
function sub_1CD9()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1CD9);
    r16[ax] = _data16get(0x9439);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r16[ax] = _data16get(0x9441);
    r16[ax] += 6;
    r16[ax] &= 0x3FF;
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0x9446];
    _data[ADR(ds, si + 4)] = r8[al];
    r8[bl] = r8[al];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x0DB9)];
    r8[al] = _data[0x944A];
    r8[al] += 6;
    _data[ADR(ds, si + 3)] = r8[al];
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x20 ) // jnz 
      { _pc = 0x1D10; continue; }
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 8);
    _data[ADR(ds, si + 3)] += r8[cl];
    _pc = 0x1D17;
      continue;
  case 0x1D10:
    _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 8);
    _data[ADR(ds, si + 3)] -= r8[cl];
  case 0x1D17:
    r16[bx] = 0x0DDA;
    sub_2121();
    _pc = -1;
  }
}
function sub_1D1E()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1D1E);
    si = 0x135E;
    _data[ADR(ds, si)] &= 0x0DF;
    r8[bl] = _data[0x1B8E];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x139D)];
    _data[ADR(ds, si + 4)] = r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x1375)];
    _cbw();
    r16[ax] += _data16get(0x1B8F);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r16[ax] = _data16get(0x1B91);
    r16[ax] -= 4;
    r16[ax] &= 0x3FF;
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0x1B8D];
    r8[al] += _data[OFS(r16[bx] + 0x1389)];
    _data[ADR(ds, si + 3)] = r8[al];
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x13A7)];
    _data[ADR(ds, si + 0x0A)] = r8[al];
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x13AA));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
    sub_B58();
    si = 0x0FF7;
    r16[ax] = _data16get(0x1363);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r16[ax] = _data16get(0x1365);
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0x1361];
    _data[ADR(ds, si + 3)] = r8[al];
    _data[0x9516] = _data[0x9516] + 1;
    r8[bl] = _data[0x9516];
    r16[bx] &= 0x0F;
    r8[al] = _data[OFS(r16[bx] + 0x0FE7)];
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x100E;
    sub_2121();
    sub_B58();
    si = 0x135E;
    _data[ADR(ds, si)] |= 0x20;
    r8[bl] = _data[0x1B8E];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x137F)];
    _cbw();
    r16[ax] += _data16get(0x1B8F);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r8[al] = _data[0x1B8D];
    r8[al] += _data[OFS(r16[bx] + 0x1393)];
    _data[ADR(ds, si + 3)] = r8[al];
    sub_B58();
    si = 0x0FF7;
    r16[ax] = _data16get(0x1363);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r16[ax] = _data16get(0x1365);
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0x1361];
    _data[ADR(ds, si + 3)] = r8[al];
    sub_B58();
    r16[ax] = _data16get(0x9511);
    r16[ax] += r16[bx];
    if ( r16[ax] <= 0x10 ) // jbe 
      { _pc = 0x1DEB; continue; }
    r16[ax] = 0;
    _data16set(0x9540, 0x0FFFF);
  case 0x1DEB:
    _data16set(0x9511, r16[ax]);
    _pc = -1;
  }
}
function sub_1DEF()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1DEF);
    _data[0x9516] = _data[0x9516] + 1;
    r8[bl] = _data[0x9516];
    r16[bx] &= 0x0F;
    r8[al] = _data[OFS(r16[bx] + 0x0FE7)];
    _data[0xFFB] = r8[al];
    r8[al] = _data[ADR(ds, si + 1)];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1E2E; continue; }
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13CD)];
    r16[ax] = 0x0FFFD;
    r16[bx] = 8;
    sub_1E7D();
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13D7)];
    r16[ax] = 3;
    r16[bx] = 8;
    sub_1E7D();
    return;
  case 0x1E2E:
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x1E46; continue; }
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13E1)];
    r16[ax] = 0;
    r16[bx] = 8;
    sub_1E7D();
    return;
  case 0x1E46:
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13EB)];
    r16[ax] = 0x0FFF9;
    r16[bx] = 8;
    sub_1E7D();
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13F5)];
    r16[ax] = 0;
    r16[bx] = 0x0B;
    sub_1E7D();
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[cl] = _data[OFS(r16[bx] + 0x13FF)];
    r16[ax] = 7;
    r16[bx] = 8;
    sub_1E7D();
    _pc = -1;
  }
}
function sub_1E7D()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1E7D);
    _push(si);
    di = 0x0FF7;
    r16[ax] += _data16get(ADR(ds, si + 5));
    _data16set(OFS(di + 5), r16[ax]);
    r16[bx] += _data16get(ADR(ds, si + 7));
    r16[bx] &= 0x3FF;
    _data16set(OFS(di + 7), r16[bx]);
    r8[cl] += _data[ADR(ds, si + 3)];
    _data[OFS(di + 3)] = r8[cl];
    si = di;
    r16[bx] = 0x1039;
    sub_2121();
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x1EB0; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x1EB0; continue; }
    sub_16D6();
  case 0x1EB0:
    si = _pop();
    r8[al] = _data[0x9518];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1EB9; continue; }
    return;
  case 0x1EB9:
    _push(si);
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    si = 0x13B0;
    r8[al] = _data[OFS(r16[bx] + 0x139D)];
    _data[ADR(ds, si + 4)] = r8[al];
    r16[ax] = _data16get(0xFFC);
    _data16set(ADR(ds, si + 5), r16[ax]);
    r16[ax] = _data16get(0xFFE);
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[0xFFA];
    _data[ADR(ds, si + 3)] = r8[al];
    _data[ADR(ds, si + 1)] = 2;
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x13A7)];
    _data[ADR(ds, si + 0x0A)] = r8[al];
    _data[ADR(ds, si + 9)] = 4;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x13C7));
    _data16set(ADR(ds, si + 0x0F), r16[ax]);
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x1F09; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x1F09; continue; }
    sub_15FC();
  case 0x1F09:
    si = _pop();
    _pc = -1;
  }
}
function sub_1F0B()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1F0B);
    _push(si);
    _data[0x9516] = _data[0x9516] + 1;
    r8[bl] = _data[0x9516];
    r16[bx] &= 0x0F;
    r8[al] = _data[OFS(r16[bx] + 0x0FE7)];
    _data[0xFFB] = r8[al];
    di = 0x0FF7;
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x1409)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 5));
    _data16set(OFS(di + 5), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x140E)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 7));
    r16[ax] &= 0x3FF;
    _data16set(OFS(di + 7), r16[ax]);
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] += 4;
    _data[OFS(di + 3)] = r8[al];
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] + 0x102F));
    si = di;
    sub_2121();
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x1F63; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x1F63; continue; }
    sub_16D6();
  case 0x1F63:
    si = _pop();
    r8[al] = _data[0x9518];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x1F6C; continue; }
    return;
  case 0x1F6C:
    _push(si);
    di = 0x13B0;
    r8[bl] = _data[ADR(ds, si + 4)];
    r8[bh] = 0;
    _data[OFS(di + 1)] = r8[bl];
    r16[ax] = _data16get(0xFFC);
    _data16set(OFS(di + 5), r16[ax]);
    r16[ax] = _data16get(0xFFE);
    _data16set(OFS(di + 7), r16[ax]);
    r8[al] = _data[0xFFA];
    _data[OFS(di + 3)] = r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x1413)];
    _data[OFS(di + 9)] = r8[al];
    r8[al] = _data[OFS(r16[bx] + 0x1418)];
    _data[OFS(di + 0x0A)] = r8[al];
    _data[OFS(di + 4)] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x141D));
    _data16set(OFS(di + 0x0F), r16[ax]);
    si = di;
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x1FB8; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x1FB8; continue; }
    sub_15FC();
  case 0x1FB8:
    si = _pop();
    _pc = -1;
  }
}
function sub_1FBA()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x1FBA);
    _push(si);
    di = 0x10E8;
    r8[bl] = _data[ADR(ds, si + 4)];
    _data[OFS(di + 1)] = r8[bl];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x10DE)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 5));
    _data16set(OFS(di + 5), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x10E3)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 7));
    r16[ax] &= 0x3FF;
    _data16set(OFS(di + 7), r16[ax]);
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] += 8;
    _data[OFS(di + 3)] = r8[al];
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] + 0x10FF));
    si = di;
    sub_2121();
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x2003; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x2003; continue; }
    sub_1429();
  case 0x2003:
    si = _pop();
    _pc = -1;
  }
}
function sub_2005()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2005);
    _push(si);
    di = 0x1446;
    r8[bl] = _data[ADR(ds, si + 4)];
    _data[OFS(di + 1)] = r8[bl];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x145D)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 5));
    _data16set(OFS(di + 5), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x1462)];
    _cbw();
    r16[ax] += _data16get(ADR(ds, si + 7));
    r16[ax] &= 0x3FF;
    _data16set(OFS(di + 7), r16[ax]);
    r8[al] = _data[ADR(ds, si + 3)];
    r8[al] += 8;
    _data[OFS(di + 3)] = r8[al];
    si = di;
    sub_B58();
    if ( si == 0 ) // jz 
      { _pc = 0x2045; continue; }
    r16[ax] = _pop();
    _push(r16[ax]);
    if ( r16[ax] <= si ) // jbe 
      { _pc = 0x2045; continue; }
    sub_17F4();
  case 0x2045:
    si = _pop();
    _pc = -1;
  }
}
function sub_2047()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2047);
    r8[al] = _data[ADR(ds, si)];
    r8[bl] = _data[0x9517];
    if ( !(r8[al] & 0x20) ) // jz 
      { _pc = 0x2072; continue; }
    if ( r8[bl] & 0x80 ) // jnz 
      { _pc = 0x206D; continue; }
    _data[0x9517] |= 0x80;
    _data[0x1326] |= 0x20;
    di = 0x1326;
    sub_20A0();
    r8[al] = 3;
    sub_3840();
    _pc = 0x2070;
      continue;
  case 0x206D:
    _data[ADR(ds, si)] = 0;
  case 0x2070:
    return;
  case 0x2072:
    if ( r8[bl] & 1 ) // jnz 
      { _pc = 0x208E; continue; }
    _data[0x9517] |= 1;
    _data[0x1326] &= 0x0DF;
    di = 0x1326;
    sub_20A0();
    r8[al] = 3;
    sub_3840();
    return;
  case 0x208E:
    _data[ADR(ds, si)] = 0;
    _pc = -1;
  }
}
function sub_2092()
{
  STAT(0x2092);
  di = 0x1427;
  sub_20A0();
}
function sub_2099()
{
  STAT(0x2099);
  di = 0x12DE;
  sub_20A0();
}
function sub_20A0()
{
  STAT(0x20A0);
  r8[al] = _data[di];
  _data[ADR(ds, si)] = r8[al];
  r8[al] = _data[OFS(di + 2)];
  _data[ADR(ds, si + 2)] = r8[al];
  r8[al] = _data[OFS(di + 0x16)];
  _data[ADR(ds, si + 0x16)] = r8[al];
  r8[al] = _data[OFS(di + 4)];
  _data[ADR(ds, si + 4)] = r8[al];
  r8[al] = _data[OFS(di + 9)];
  _data[ADR(ds, si + 9)] = r8[al];
  r8[al] = _data[OFS(di + 0x0A)];
  _data[ADR(ds, si + 0x0A)] = r8[al];
  r8[al] = _data[OFS(di + 0x0B)];
  _data[ADR(ds, si + 0x0B)] = r8[al];
  r8[al] = _data[OFS(di + 0x0C)];
  _data[ADR(ds, si + 0x0C)] = r8[al];
  r16[ax] = _data16get(OFS(di + 0x0F));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
  r8[al] = _data[OFS(di + 0x12)];
  _data[ADR(ds, si + 0x12)] = r8[al];
}
function sub_20DB()
{
  STAT(0x20DB);
  sub_2676();
  sub_20F0();
  _push(si);
  r8[al] = _data[ADR(ds, si + 0x13)];
  r8[ah] = 0;
  _push(r16[ax]);
  r8[al] = _data[ADR(ds, si + 0x14)];
  _push(r16[ax]);
  sub_9B5();
}
function sub_20F0()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x20F0);
    _push(si);
    r16[ax] = _data16get(ADR(ds, si + 5));
    _data16set(0x12A3, r16[ax]);
    r16[ax] = _data16get(ADR(ds, si + 7));
    _data16set(0x12A5, r16[ax]);
    r8[al] = _data[ADR(ds, si + 3)];
    _data[0x12A1] = r8[al];
    r8[al] = _data[ADR(ds, si)];
    if ( !(r8[al] & 0x10) ) // jz 
      { _pc = 0x2119; continue; }
    _data16set(0x12A3, _data16get(0x12A3) - 0x0C);
    _data16set(0x12A5, _data16get(0x12A5) - 8);
    _data16set(0x12A5, _data16get(0x12A5) & 0x3FF);
  case 0x2119:
    si = 0x129E;
    sub_B58();
    si = _pop();
    _pc = -1;
  }
}
function sub_2121()
{
  STAT(0x2121);
  r8[cl] = _data[r16[bx]];
  r8[ch] = 0;
  r16[bx] = r16[bx] + 1;
  r8[al] = _data[ADR(ds, si + 4)];
  r8[ah] = 0;
  di = r16[ax];
  r8[al] = _data[OFS(r16[bx] + di)];
  _data[ADR(ds, si + 9)] = r8[al];
  r16[bx] += r16[cx];
  r8[al] = _data[OFS(r16[bx] + di)];
  _data[ADR(ds, si + 0x0A)] = r8[al];
  r16[bx] += r16[cx];
  r8[al] = _data[OFS(r16[bx] + di)];
  _data[ADR(ds, si + 0x0B)] = r8[al];
  r16[bx] += r16[cx];
  r8[al] = _data[OFS(r16[bx] + di)];
  _data[ADR(ds, si + 0x0C)] = r8[al];
  r16[bx] += r16[cx];
  di <<= 1;
  di <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + di));
  _data16set(ADR(ds, si + 0x0D), r16[ax]);
  r16[bx] += 2;
  r16[ax] = _data16get(OFS(r16[bx] + di));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
}
function sub_215B()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x215B);
    r16[cx] = 1;
    r16[ax] = _data16get(0x1B91);
    r16[ax] -= _data16get(ADR(ds, si + 7));
    if ( _short(r16[ax]) <= _short(0x8C) ) // jle 
      { _pc = 0x2171; continue; }
    _data[ADR(ds, si + 4)] = 2;
    r16[cx] = 0;
    return;
  case 0x2171:
    if ( _short(r16[ax]) >= _short(0x0FFF0) ) // jge 
      { _pc = 0x21A0; continue; }
    r8[ah] = _data[ADR(ds, si + 4)];
    r8[al] = _data[ADR(ds, si)];
    if ( !(r8[al] & 0x20) ) // jz 
      { _pc = 0x218D; continue; }
    r8[ah] = r8[ah] + 1;
    if ( r8s[ah] <= _char(4) ) // jle 
      { _pc = 0x218B; continue; }
    _data[ADR(ds, si)] &= 0x0DF;
    r8[ah] = 4;
  case 0x218B:
    _pc = 0x2199;
      continue;
  case 0x218D:
    r8[ah]--;
    if ( r8s[ah] >= _char(0) ) // jge 
      { _pc = 0x2199; continue; }
    _data[ADR(ds, si)] |= 0x20;
    r8[ah] = 0;
  case 0x2199:
    _data[ADR(ds, si + 4)] = r8[ah];
    r16[cx] = 0;
    return;
  case 0x21A0:
    r16[bx] = _data16get(0x1B8F);
    r16[bx] -= _data16get(ADR(ds, si + 5));
    if ( _short(r16[bx]) >= 0 ) // jns 
      { _pc = 0x21C2; continue; }
    if ( _short(r16[bx]) <= _short(0x0FFE0) ) // jle 
      { _pc = 0x21B3; continue; }
    _data[ADR(ds, si + 4)] = 2;
    return;
  case 0x21B3:
    if ( _short(r16[ax]) <= _short(0x20) ) // jle 
      { _pc = 0x21BD; continue; }
    _data[ADR(ds, si + 4)] = 1;
    return;
  case 0x21BD:
    _data[ADR(ds, si + 4)] = 0;
    return;
  case 0x21C2:
    if ( _short(r16[bx]) >= _short(0x20) ) // jge 
      { _pc = 0x21CC; continue; }
    _data[ADR(ds, si + 4)] = 2;
    return;
  case 0x21CC:
    if ( _short(r16[ax]) <= _short(0x20) ) // jle 
      { _pc = 0x21D6; continue; }
    _data[ADR(ds, si + 4)] = 3;
    return;
  case 0x21D6:
    _data[ADR(ds, si + 4)] = 4;
    _pc = -1;
  }
}
function sub_21DC()
{
  STAT(0x21DC);
  r16[ax] = 0x403C;
  _push(r16[ax]);
  r16[ax] = 0x1E11;
  _push(r16[ax]);
  r16[ax] = 0x38;
  _push(r16[ax]);
  r16[ax] = 7;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
  sub_2200();
  sub_264A();
  sub_2A7F();
  sub_22B1();
}
function sub_2200()
{
  STAT(0x2200);
  sub_250B();
  sub_2553();
  sub_259B();
  sub_237C();
}
function sub_220D()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
  	//return;
    STAT(0x220D);
    _data[0x944C] = _data[0x944C] + 1;
    r8[al] = _data[0x944C];
    r8[al] &= 3;
    if ( r8[al] ) // jnz 
      { _pc = 0x2228; continue; }
    r16[ax] = 0;
    _push(r16[ax]);
    _push(r16[ax]);
    _push(r16[ax]);
    r8[al] = _data[0x94FE];
    _push(r16[ax]);
    sub_269E();
    sub_2714();
  case 0x2228:
    r16[ax] = _data16get(0x953C);
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x2246; continue; }
    if ( _short((r16[ax])) >= 0 ) // jns 
      { _pc = 0x2237; continue; }
    sub_252F();
    _pc = 0x2240;
      continue;
  case 0x2237:
    r16[cx] = r16[ax];
  case 0x2239:
    _push(r16[cx]);
    sub_2542();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2239; continue; }
  case 0x2240:
    _data16set(0x953C, 0);
  case 0x2246:
    r16[ax] = _data16get(0x9540);
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x2264; continue; }
    if ( _short((r16[ax])) >= 0 ) // jns 
      { _pc = 0x2255; continue; }
    sub_2577();
    _pc = 0x225E;
      continue;
  case 0x2255:
    r16[cx] = r16[ax];
  case 0x2257:
    _push(r16[cx]);
    sub_258A();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2257; continue; }
  case 0x225E:
    _data16set(0x9540, 0);
  case 0x2264:
    r16[ax] = _data16get(0x9544);
    //printf("hit=%d", _short(r16[ax]);) r16[ax] = 0;
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x228A; continue; }
    if ( _short((r16[ax])) >= 0 ) // jns 
      { _pc = 0x227B; continue; }
    r16[ax] = - r16[ax];
    r16[cx] = r16[ax];
  case 0x2272:
    _push(r16[cx]);
    sub_25BF(); // <--- problem
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2272; continue; }
    _pc = 0x2284;
      continue;
  case 0x227B:
    r16[cx] = r16[ax];
  case 0x227D:
    _push(r16[cx]);
    sub_25D2();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x227D; continue; }
  case 0x2284:
    _data16set(0x9544, 0);
  case 0x228A:
    r16[ax] = _data16get(0x9538);
    if ( r16[ax] == 0 ) // jz 
      return;
    if ( _short((r16[ax])) >= 0 ) // jns 
      { _pc = 0x22A1; continue; }
    r16[ax] = - r16[ax];
    r16[cx] = r16[ax];
  case 0x2298:
    _push(r16[cx]);
    sub_2464();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2298; continue; }
    _pc = 0x22AA;
      continue;
  case 0x22A1:
    r16[cx] = r16[ax];
  case 0x22A3:
    _push(r16[cx]);
    sub_239B();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x22A3; continue; }
  case 0x22AA:
    _data16set(0x9538, 0);
    _pc = -1;
  }
}
function sub_22B1()
{
  STAT(0x22B1);
  _data16set(0x9534, 3);
  sub_22E1();
  sub_22F9();
  sub_2311();
}
function sub_22C1()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x22C1);
    _data16set(0x9534, _data16get(0x9534) + 1);
    r16[ax] = _data16get(0x9534);
    if ( r16[ax] <= 3 ) // jbe 
      { _pc = 0x22D4; continue; }
    _data16set(0x9534, 3);
    return;
  case 0x22D4:
    if ( unknown_condition() ) // jz 
    {
      sub_2311();
  	return;
    }
    if ( r16[ax] == 2 ) // jz 
    {
      sub_22F9();
  	return;
    }
    if ( r16[ax] == 1 ) // jz 
    {
      sub_22E1();
  	return;
    }
    _pc = -1;
  }
}
function sub_22E1()
{
  STAT(0x22E1);
  r16[ax] = 0x43E6;
  _push(r16[ax]);
  r16[ax] = 0x1B90;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_22F9()
{
  STAT(0x22F9);
  r16[ax] = 0x43E6;
  _push(r16[ax]);
  r16[ax] = 0x1B93;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2311()
{
  STAT(0x2311);
  r16[ax] = 0x43E6;
  _push(r16[ax]);
  r16[ax] = 0x1B96;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2329()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2329);
    _data16set(0x9534, _data16get(0x9534) -1);
    r16[ax] = _data16get(0x9534);
    if ( r16[ax] == 2 ) // jz 
      { _pc = 0x2368; continue; }
    if ( r16[ax] == 1 ) // jz 
      { _pc = 0x2354; continue; }
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x2340; continue; }
    return;
  case 0x2340:
    r16[ax] = 0x1B90;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x2354:
    r16[ax] = 0x1B93;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x2368:
    r16[ax] = 0x1B96;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    _pc = -1;
  }
}
function sub_237C()
{
  STAT(0x237C);
  _data16set(0x9536, 6);
  _data16set(0x9538, 0);
  sub_23D4();
  sub_23EC();
  sub_2404();
  sub_241C();
  sub_2434();
  sub_244C();
}
function sub_239B()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x239B);
    _data16set(0x9536, _data16get(0x9536) + 1);
    r16[ax] = _data16get(0x9536);
    if ( r16[ax] <= 6 ) // jbe 
      { _pc = 0x23AE; continue; }
    _data16set(0x9536, 6);
    return;
  case 0x23AE:
    _push(r16[ax]);
    r8[al] = 8;
    sub_3840();
    r16[ax] = _pop();
    if ( r16[ax] == 1 ) // jz 
    {
      sub_23D4();
  	return;
    }
    if ( r16[ax] == 2 ) // jz 
    {
  	  sub_23EC();
  	  return;
    }
    if ( r16[ax] == 3 ) // jz 
    {
      sub_2404();
  	return;
    }
    if ( r16[ax] == 4 ) // jz 
    {
      sub_241C();
  	return;
    }
    if ( r16[ax] == 5 ) // jz 
    {
      sub_2434();
  	return;
    }
    if ( r16[ax] == 6 ) // jz 
    {
      sub_244C();
  	return;
    }
    _pc = -1;
  }
}
function sub_23D4()
{
  STAT(0x23D4);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1B99;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_23EC()
{
  STAT(0x23EC);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1B9B;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2404()
{
  STAT(0x2404);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1B9D;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_241C()
{
  STAT(0x241C);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1B9F;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2434()
{
  STAT(0x2434);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1BA1;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_244C()
{
  STAT(0x244C);
  r16[ax] = 0x43EE;
  _push(r16[ax]);
  r16[ax] = 0x1BA3;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2464()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2464);
    r16[ax] = _data16get(0x9536);
    _data16set(0x9536, _data16get(0x9536) -1);
    if ( _data16gets(0x9536) >= 0 ) // jns 
      { _pc = 0x2474; continue; }
    _data16set(0x9536, 0);
    return;
  case 0x2474:
    if ( r16[ax] == 1 ) // jz 
      { _pc = 0x2493; continue; }
    if ( r16[ax] == 2 ) // jz 
      { _pc = 0x24A7; continue; }
    if ( r16[ax] == 3 ) // jz 
      { _pc = 0x24BB; continue; }
    if ( r16[ax] == 4 ) // jz 
      { _pc = 0x24CF; continue; }
    if ( r16[ax] == 5 ) // jz 
      { _pc = 0x24E3; continue; }
    if ( r16[ax] == 6 ) // jz 
      { _pc = 0x24F7; continue; }
    return;
  case 0x2493:
    r16[ax] = 0x1B99;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x24A7:
    r16[ax] = 0x1B9B;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x24BB:
    r16[ax] = 0x1B9D;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x24CF:
    r16[ax] = 0x1B9F;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x24E3:
    r16[ax] = 0x1BA1;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    return;
  case 0x24F7:
    r16[ax] = 0x1BA3;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_2D9A();
    _pc = -1;
  }
}
function sub_250B()
{
  STAT(0x250B);
  _data16set(0x953A, 0x2C);
  _data16set(0x953C, 0);
  r16[ax] = 0x48F6;
  _push(r16[ax]);
  r16[ax] = 0x1B88;
  _push(r16[ax]);
  r16[ax] = 0x2C;
  _push(r16[ax]);
  r16[ax] = 7;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_252F()
{
  STAT(0x252F);
  r16[ax] = _data16get(0x953A);
  r16[ax]--;
  if ( _short(r16[ax]) >= 0 ) // jns 
  {
    sub_2536();
	return;
  }
}
function sub_2536()
{
  STAT(0x2536);
  _data16set(0x953A, r16[ax]);
  _push(r16[ax]);
  r16[ax] = 0x1B88;
  _push(r16[ax]);
  sub_25E3();
}
function sub_2542()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2542);
    r16[ax] = _data16get(0x953A);
    if ( r16[ax] < 0x2C ) // jb 
      { _pc = 0x254B; continue; }
    return;
  case 0x254B:
    sub_2536();
    _data16set(0x953A, _data16get(0x953A) + 1);
    _pc = -1;
  }
}
function sub_2553()
{
  STAT(0x2553);
  _data16set(0x953E, 0x30);
  _data16set(0x9540, 0);
  r16[ax] = 0x2CE6;
  _push(r16[ax]);
  r16[ax] = 0x1CC8;
  _push(r16[ax]);
  r16[ax] = 0x30;
  _push(r16[ax]);
  r16[ax] = 7;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2577()
{
  STAT(0x2577);
  r16[ax] = _data16get(0x953E);
  r16[ax]--;
  if ( _short(r16[ax]) >= 0 ) // jns 
    sub_257E();
}
function sub_257E()
{
  STAT(0x257E);
  _data16set(0x953E, r16[ax]);
  _push(r16[ax]);
  r16[ax] = 0x1CC8;
  _push(r16[ax]);
  sub_25E3();
}
function sub_258A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x258A);
    r16[ax] = _data16get(0x953E);
    if ( r16[ax] < 0x30 ) // jb 
      { _pc = 0x2593; continue; }
    return;
  case 0x2593:
    sub_257E();
    _data16set(0x953E, _data16get(0x953E) + 1);
    _pc = -1;
  }
}
function sub_259B()
{
  STAT(0x259B);
  _data16set(0x9542, 0x38);
  _data16set(0x9544, 0);
  r16[ax] = 0x4496;
  _push(r16[ax]);
  r16[ax] = 0x1E08;
  _push(r16[ax]);
  r16[ax] = 0x38;
  _push(r16[ax]);
  r16[ax] = 7;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_25BF()
{
  STAT(0x25BF);
  r16[ax] = _data16get(0x9542);
  r16[ax]--;
  if ( _short(r16[ax]) >= 0 ) // jns 
    sub_25C6();
}
function sub_25C6()
{
  STAT(0x25C6);
  _data16set(0x9542, r16[ax]);
  _push(r16[ax]);
  r16[ax] = 0x1E08;
  _push(r16[ax]);
  sub_25E3();
}
function sub_25D2()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x25D2);
    r16[ax] = _data16get(0x9542);
    if ( r16[ax] < 0x38 ) // jb 
      { _pc = 0x25DB; continue; }
    return;
  case 0x25DB:
    sub_25C6();
    _data16set(0x9542, _data16get(0x9542) + 1);
    _pc = -1;
  }
}
function sub_25E3()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x25E3);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[ax] = 0x0A000;
    es = r16[ax];
    r16[ax] = _stack16get(bp + arg_2);
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] += _stack16get(bp + arg_0);
    di = r16[ax];
    r16[dx] = 0x3CE;
    r16[ax] = 0x805;
    _out(r16[dx], r16[ax]);
    r16[cx] = _stack16get(bp + arg_2);
    r16[cx] &= 7;
    r8[ah] = 0x80;
    r8[ah] >>= r8[cl];
    r8[al] = 8;
    _out(r16[dx], r16[ax]);
    r8[bl] = r8[ah];
    r16[ax] = 0x1803;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F01;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x700;
    _out(r16[dx], r16[ax]);
    r16[cx] = 7;
  case 0x261E:
    r8[al] = _video8get(ADR(es,di));
    if ( r8[al] & r8[bl] ) // jnz 
      { _pc = 0x262D; continue; }
    _video8set(ADR(es,di), r8[bl]);
    _video8set(ADR(es,di+0x2000), r8[bl]);
  case 0x262D:
    di += 0x28;
    if ( --r16[cx] )
      { _pc = 0x261E; continue; }
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0FF08;
    _out(r16[dx], r16[ax]);
    r16[ax] = 3;
    _out(r16[dx], r16[ax]);
    r16[ax] = 1;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0;
    _out(r16[dx], r16[ax]);
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_264A()
{
  STAT(0x264A);
  r8[al] = 0;
  _data[0x94A9] = r8[al];
  _data[0x94AA] = r8[al];
  _data[0x94AB] = r8[al];
  _data[0x94AC] = r8[al];
  _data[0x94AD] = r8[al];
  _data[0x94AE] = r8[al];
  sub_2714();
}
function sub_2662()
{
  STAT(0x2662);
  r16[ax] = 0;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  r16[ax] = 1;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  sub_269E();
}
function sub_2676()
{
  STAT(0x2676);
  r16[ax] = 0;
  _push(r16[ax]);
  r16[ax] = 1;
  _push(r16[ax]);
  r16[ax] = 5;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  sub_269E();
}
function sub_268A()
{
  STAT(0x268A);
  r16[ax] = 2;
  _push(r16[ax]);
  r16[ax] = 5;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  sub_269E();
}
function sub_269E()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x269E);
   // unknown_command(); // arg_0		= byte ptr  4
   // unknown_command(); // arg_2		= byte ptr  6
   // unknown_command(); // arg_4		= byte ptr  8
   // unknown_command(); // arg_6		= byte ptr  0Ah
    _push(bp);
    bp = sp;
    r8[al] = _data[0x94AE];
    r8[al] += _stack8get(bp + arg_0);
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x26B1; continue; }
    r8[al] -= 0x0A;
    _data[0x94AD] = _data[0x94AD] + 1;
  case 0x26B1:
    _data[0x94AE] = r8[al];
    r8[al] = _data[0x94AD];
    r8[al] += _stack8get(bp + arg_2);
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x26C4; continue; }
    r8[al] -= 0x0A;
    _data[0x94AC] = _data[0x94AC] + 1;
  case 0x26C4:
    _data[0x94AD] = r8[al];
    r8[al] = _data[0x94AC];
    r8[al] += _stack8get(bp + arg_4);
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x26D7; continue; }
    r8[al] -= 0x0A;
    _data[0x94AB] = _data[0x94AB] + 1;
  case 0x26D7:
    _data[0x94AC] = r8[al];
    r8[al] = _data[0x94AB];
    r8[al] += _stack8get(bp + arg_6);
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x26EA; continue; }
    r8[al] -= 0x0A;
    _data[0x94AA] = _data[0x94AA] + 1;
  case 0x26EA:
    _data[0x94AB] = r8[al];
    r8[al] = _data[0x94AA];
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x2701; continue; }
    r8[al] -= 0x0A;
    _data[0x94A9] = _data[0x94A9] + 1;
    _push(r16[ax]);
    _push(si);
    sub_22C1();
    si = _pop();
    r16[ax] = _pop();
  case 0x2701:
    _data[0x94AA] = r8[al];
    r8[al] = _data[0x94A9];
    if ( r8[al] <= 9 ) // jbe 
      { _pc = 0x270D; continue; }
    r8[al] -= 0x0A;
  case 0x270D:
    _data[0x94A9] = r8[al];
    bp = _pop();
    _retn(8);
    _pc = -1;
  }
}
function sub_2714()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2714);
    _data[0x944D] = 1;
    si = 0x94A9;
    r16[cx] = 6;
    r16[dx] = 0;
  case 0x2722:
    _push(r16[cx]);
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x272D; continue; }
    _data[0x944D] = 0;
  case 0x272D:
    r8[cl] = _data[0x944D];
    if ( r8[cl] != 0 ) // jnz 
      { _pc = 0x275E; continue; }
    _push(r16[dx]);
    _push(si);
    r8[bh] = 0;
    r8[bl] = r8[al];
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x155F));
    _push(r16[ax]);
    r16[bx] = r16[dx];
    r16[ax] = _data16get(OFS(r16[bx] + 0x1573));
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 9;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    sub_2CEA();
    si = _pop();
    r16[dx] = _pop();
    r16[dx] += 2;
  case 0x275E:
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2722; continue; }
    _pc = -1;
  }
}
function sub_2762()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2762);
    r16[cx] = 0x12;
    r16[ax] = ds;
    es = r16[ax];
    di = 0x94AF;
    _cld();
    r16[ax] = 0;
    _rep_stosw();
    r16[cx] = 0x2A;
    di = 0x9455;
    r8[al] = 0x2E;
    r8[ah] = 0x2E;
    _rep_stosw();
    _data[0x9455] = 0x5F;
    r8[al] = 0;
    r16[cx] = 7;
    si = 0x94DA;
  case 0x278B:
    _data[ADR(ds, si)] = r8[al];
    r8[al] = r8[al] + 1;
    si = si + 1;
    if ( --r16[cx] )
      { _pc = 0x278B; continue; }
    di = 0x9455;
    r16[dx] = 0x1506;
    r16[cx] = 0x8C;
    sub_644();
    _pc = -1;
  }
}
function sub_279F()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x279F);
    sub_2809();
    r8[al] = _data[0x94E0];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x27AF; continue; }
    _data[0x9546] = 0;
    return;
  case 0x27AF:
    _data[0x9546] = 1;
    r8[bl] = r8[al];
    r8[bl] <<= 1;
    r8[bl] += r8[al];
    r8[bh] = 0;
    r16[bx] <<= 1;
    _push(r16[bx]);
    r16[bx] += 0x94A9;
    si = 0x94A9;
    r16[cx] = 6;
  case 0x27C9:
    _lodsb();
    _data[r16[bx]] = r8[al];
    r16[bx] = r16[bx] + 1;
    if ( --r16[cx] )
      { _pc = 0x27C9; continue; }
    r16[bx] = _pop();
    r16[bx] <<= 1;
    r16[bx] += 0x9455;
    _data16set(0x9451, r16[bx]);
    si = 0x9455;
    r16[cx] = 0x0C;
  case 0x27E0:
    _lodsb();
    _data[r16[bx]] = r8[al];
    r16[bx] = r16[bx] + 1;
    if ( --r16[cx] )
      { _pc = 0x27E0; continue; }
    si = 0x94DA;
  case 0x27E9:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x27F2; continue; }
    si = si + 1;
    _pc = 0x27E9;
      continue;
  case 0x27F2:
    r8[al] = _data[0x94E0];
    _data[ADR(ds, si)] = r8[al];
    _data[0x94E0] = 0;
    si -= 0x94DA;
    r16[ax] = si;
    _data[0x9450] = r8[al];
    sub_28DA();
    _pc = -1;
  }
}
function sub_2809()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2809);
    r8[al] = _data[0x94DA];
    _data[0x94D3] = r8[al];
    r8[al] = _data[0x94DB];
    _data[0x94D4] = r8[al];
    r8[al] = _data[0x94DC];
    _data[0x94D5] = r8[al];
    r8[al] = _data[0x94DD];
    _data[0x94D6] = r8[al];
    r8[al] = _data[0x94DE];
    _data[0x94D7] = r8[al];
    r8[al] = _data[0x94DF];
    _data[0x94D8] = r8[al];
    r8[al] = _data[0x94E0];
    _data[0x94D9] = r8[al];
    si = 0x94D3;
    di = 0x94DA;
    r16[cx] = 7;
  case 0x283C:
    _push(r16[cx]);
    _push(si);
  case 0x283E:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] != 0x0FF ) // jnz 
      { _pc = 0x2847; continue; }
    si = si + 1;
    _pc = 0x283E;
      continue;
  case 0x2847:
    if ( si == 0x94D9 ) // jz 
      { _pc = 0x2865; continue; }
    r16[bx] = si;
  case 0x284F:
    r16[bx] = r16[bx] + 1;
    r8[al] = _data[r16[bx]];
    if ( r8[al] == 0x0FF ) // jz 
      { _pc = 0x285F; continue; }
    sub_2872();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x285F; continue; }
    si = r16[bx];
  case 0x285F:
    if ( r16[bx] != 0x94D9 ) // jnz 
      { _pc = 0x284F; continue; }
  case 0x2865:
    r8[al] = _data[ADR(ds, si)];
    _data[ADR(ds, si)] = 0x0FF;
    _data[di] = r8[al];
    di = di + 1;
    si = _pop();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x283C; continue; }
    _pc = -1;
  }
}
function sub_2872()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2872);
    _push(si);
    _push(di);
    r8[al] = _data[ADR(ds, si)];
    r8[ah] = r8[al];
    r8[al] <<= 1;
    r8[al] += r8[ah];
    r8[al] <<= 1;
    r8[ah] = 0;
    r16[ax] += 0x94A9;
    si = r16[ax];
    r8[al] = _data[r16[bx]];
    r8[ah] = r8[al];
    r8[al] <<= 1;
    r8[al] += r8[ah];
    r8[al] <<= 1;
    r8[ah] = 0;
    r16[ax] += 0x94A9;
    di = r16[ax];
    r8[al] = _data[di];
    if ( r8[al] > _data[ADR(ds, si)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si)] ) // jb 
      { _pc = 0x28D0; continue; }
    r8[al] = _data[OFS(di + 1)];
    if ( r8[al] > _data[ADR(ds, si + 1)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si + 1)] ) // jb 
      { _pc = 0x28D0; continue; }
    r8[al] = _data[OFS(di + 2)];
    if ( r8[al] > _data[ADR(ds, si + 2)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si + 2)] ) // jb 
      { _pc = 0x28D0; continue; }
    r8[al] = _data[OFS(di + 3)];
    if ( r8[al] > _data[ADR(ds, si + 3)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si + 3)] ) // jb 
      { _pc = 0x28D0; continue; }
    r8[al] = _data[OFS(di + 4)];
    if ( r8[al] > _data[ADR(ds, si + 4)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si + 4)] ) // jb 
      { _pc = 0x28D0; continue; }
    r8[al] = _data[OFS(di + 5)];
    if ( r8[al] > _data[ADR(ds, si + 5)] ) // ja 
      { _pc = 0x28D5; continue; }
    if ( r8[al] < _data[ADR(ds, si + 5)] ) // jb 
    {
  	  _ASSERT(0);
     //oto $+2;
    }
  case 0x28D0:
    r8[al] = 0;
    di = _pop();
    si = _pop();
    return;
  case 0x28D5:
    r8[al] = 1;
    di = _pop();
    si = _pop();
    _pc = -1;
  }
}
function sub_28DA()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x28DA);
    si = 0x94DA;
    di = 0x1B1;
    r16[cx] = 6;
  case 0x28E3:
    _push(r16[cx]);
    di += 2;
    r16[ax] = _data16get(di);
    di += 2;
    _push(si);
    _push(di);
    sub_2959();
    di = _pop();
    si = _pop();
    di += 2;
    r16[ax] = _data16get(di);
    di += 2;
    _push(si);
    _push(di);
    sub_2907();
    di = _pop();
    si = _pop();
    si = si + 1;
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x28E3; continue; }
    _pc = -1;
  }
}
function sub_2907()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2907);
    _data16set(0x944E, r16[ax]);
    r8[al] = _data[ADR(ds, si)];
    r8[ah] = r8[al];
    r8[al] <<= 1;
    r8[al] += r8[ah];
    r8[ah] = 0;
    r16[ax] <<= 1;
    r16[ax] += 0x94A9;
    si = r16[ax];
    _data[0x944D] = 1;
    r16[cx] = 6;
    r16[dx] = 0;
  case 0x2926:
    _push(r16[cx]);
    _lodsb();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x2931; continue; }
    _data[0x944D] = 0;
  case 0x2931:
    r8[cl] = _data[0x944D];
    if ( r8[cl] == 0 ) // jz 
      { _pc = 0x293F; continue; }
    r16[ax] = 0x6F6C;
    _pc = 0x2949;
      continue;
  case 0x293F:
    r8[bh] = 0;
    r8[bl] = r8[al];
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] + 0x157F));
  case 0x2949:
    _push(r16[dx]);
    _push(si);
    _push(r16[ax]);
    _push(r16[dx]);
    sub_29AE();
    si = _pop();
    r16[dx] = _pop();
    r16[dx] += 6;
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2926; continue; }
    _pc = -1;
  }
}
function sub_2959()
{
  STAT(0x2959);
  _data16set(0x944E, r16[ax]);
  r8[al] = _data[ADR(ds, si)];
  r8[ah] = r8[al];
  r8[al] <<= 1;
  r8[al] += r8[ah];
  r8[ah] = 0;
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += 0x9455;
  si = r16[ax];
}
function sub_296F()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x296F);
    r16[cx] = 0x0C;
    r16[dx] = 0;
  case 0x2975:
    _push(r16[cx]);
    _lodsb();
    _push(si);
    _push(r16[dx]);
    if ( r8[al] != 0x20 ) // jnz 
      { _pc = 0x2982; continue; }
    r16[ax] = 0x6546;
    _pc = 0x29A0;
      continue;
  case 0x2982:
    if ( r8[al] != 0x2E ) // jnz 
      { _pc = 0x298B; continue; }
    r16[ax] = 0x6F6C;
    _pc = 0x29A0;
      continue;
  case 0x298B:
    if ( r8[al] != 0x5F ) // jnz 
      { _pc = 0x2994; continue; }
    r16[ax] = 0x764C;
    _pc = 0x29A0;
      continue;
  case 0x2994:
    r8[al] -= 0x41;
    r8[ah] = r8[al];
    r8[al] <<= 1;
    r8[al] += r8[ah];
    r8[al] <<= 1;
    r8[ah] = 0;
  case 0x29A0:
    _push(r16[ax]);
    _push(r16[dx]);
    sub_29AE();
    r16[dx] = _pop();
    r16[dx] += 6;
    si = _pop();
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x2975; continue; }
    _pc = -1;
  }
}
function sub_29AE()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x29AE);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[ax] = _data16get(0x94F0);
    es = r16[ax];
    di = _data16get(0x944E);
    di += _stack16get(bp + arg_0);
    r16[ax] = _data16get(0x94EA);
    _push(ds);
    ds = r16[ax];
    si = _stack16get(bp + arg_2);
    r16[cx] = 0x0B;
  case 0x29C9:
    _movsw();
    _movsw();
    _movsw();
    di += 0x9A;
    si += 0x9A;
    if ( --r16[cx] )
      { _pc = 0x29C9; continue; }
    ds = _pop();
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_29DB()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x29DB);
    _data16set(0x9453, 0);
  case 0x29E1:
    r16[ax] = _data16get(0x9453);
    if ( r16[ax] >= 0x0C ) // jnb 
      { _pc = 0x2A39; continue; }
    sub_541();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x2A39; continue; }
    if ( r8[al] != 8 ) // jnz 
      { _pc = 0x2A0D; continue; }
    r16[bx] = _data16get(0x9451);
    r16[bx] += _data16get(0x9453);
    _data[r16[bx]] = 0x2E;
    _data16set(0x9453, _data16get(0x9453) -1);
    if ( _data16gets(0x9453) >= 0 ) // jns 
      { _pc = 0x2A0B; continue; }
    _data16set(0x9453, 0);
  case 0x2A0B:
    _pc = 0x2A1B;
      continue;
  case 0x2A0D:
    r16[bx] = _data16get(0x9451);
    r16[bx] += _data16get(0x9453);
    _data[r16[bx]] = r8[al];
    _data16set(0x9453, _data16get(0x9453) + 1);
  case 0x2A1B:
    r16[bx] = _data16get(0x9453);
    if ( r16[bx] >= 0x0C ) // jnb 
      { _pc = 0x2A2B; continue; }
    r16[bx] += _data16get(0x9451);
    _data[r16[bx]] = 0x5F;
  case 0x2A2B:
    sub_2A64();
    sub_3498();
    sub_B8E();
    sub_3383();
    _pc = 0x29E1;
      continue;
  case 0x2A39:
    r16[bx] = _data16get(0x9453);
    if ( r16[bx] >= 0x0C ) // jnb 
      { _pc = 0x2A52; continue; }
    r16[bx] += _data16get(0x9451);
    r8[al] = _data[r16[bx]];
    if ( r8[al] != 0x5F ) // jnz 
      { _pc = 0x2A52; continue; }
    _data[r16[bx]] = 0x2E;
    sub_2A64();
  case 0x2A52:
    di = 0x9455;
    r16[dx] = 0x1506;
    r16[cx] = 0x8C;
    sub_674();
    _data[0x9546] = 0;
    _pc = -1;
  }
}
function sub_2A64()
{
  STAT(0x2A64);
  si = _data16get(0x9451);
  r8[bl] = _data[0x9450];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[bx] <<= 1;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x1B3));
  _data16set(0x944E, r16[ax]);
  sub_296F();
}
function sub_2A7F()
{
  STAT(0x2A7F);
  _data[0x952E] = 0;
  _data[0x952F] = 0;
  _data[0x9530] = 0;
  _data[0x9531] = 0;
  _data[0x9532] = 0;
  _data[0x9533] = 0;
  r16[ax] = 0x1178;
  _push(r16[ax]);
  r16[ax] = 0x1B82;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x1678;
  _push(r16[ax]);
  r16[ax] = 0x1CC2;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x1B78;
  _push(r16[ax]);
  r16[ax] = 0x1E02;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x2078;
  _push(r16[ax]);
  r16[ax] = 0x1B85;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x2578;
  _push(r16[ax]);
  r16[ax] = 0x1CC5;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x2A78;
  _push(r16[ax]);
  r16[ax] = 0x1E05;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 8;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2B28()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2B28);
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 1;
    _push(r16[ax]);
    r16[ax] = 5;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_269E();
    r16[ax] = _pop();
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x2B59; continue; }
    if ( r8[al] == 1 ) // jz 
      { _pc = 0x2B76; continue; }
    if ( r8[al] == 2 ) // jz 
      { _pc = 0x2B93; continue; }
    if ( r8[al] == 3 ) // jz 
      { _pc = 0x2BB0; continue; }
    if ( r8[al] == 4 ) // jz 
      { _pc = 0x2BCD; continue; }
    if ( r8[al] != 5 ) // jnz 
      return;
    _pc = 0x2BEA;
      continue;
    return;
  case 0x2B59:
    _data[0x952E] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1B82;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    return;
  case 0x2B76:
    _data[0x952F] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1CC2;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    return;
  case 0x2B93:
    _data[0x9530] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1E02;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    return;
  case 0x2BB0:
    _data[0x9531] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1B85;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    return;
  case 0x2BCD:
    _data[0x9532] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1CC5;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    return;
  case 0x2BEA:
    _data[0x9533] = 1;
    r16[ax] = 0x2F78;
    _push(r16[ax]);
    r16[ax] = 0x1E05;
    _push(r16[ax]);
    r16[ax] = 0x10;
    _push(r16[ax]);
    r16[ax] = 8;
    _push(r16[ax]);
    r16[ax] = 4;
    _push(r16[ax]);
    sub_2CEA();
    _pc = -1;
  }
}
function sub_2C07()
{
  STAT(0x2C07);
  r16[ax] = 0x0A0B;
  _push(r16[ax]);
  r16[ax] = 0x13;
  _push(r16[ax]);
  r16[ax] = 0x30;
  _push(r16[ax]);
  r16[ax] = 5;
  _push(r16[ax]);
  sub_2D9A();
  r16[ax] = 0x0AAC;
  _push(r16[ax]);
  r16[ax] = 0x11;
  _push(r16[ax]);
  r16[ax] = 0x28;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2D9A();
  r16[ax] = 0x5A5C;
  _push(r16[ax]);
  r16[ax] = 0x0B4D;
  _push(r16[ax]);
  r16[ax] = 0x78;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2C45()
{
  STAT(0x2C45);
  r16[ax] = 0x0AAC;
  _push(r16[ax]);
  r16[ax] = 0x10;
  _push(r16[ax]);
  r16[ax] = 0x28;
  _push(r16[ax]);
  r16[ax] = 5;
  _push(r16[ax]);
  sub_2D9A();
  r16[ax] = 0x0B4D;
  _push(r16[ax]);
  r16[ax] = 0x0E;
  _push(r16[ax]);
  r16[ax] = 0x20;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2D9A();
  r16[ax] = 0x7592;
  _push(r16[ax]);
  r16[ax] = 0x0C8F;
  _push(r16[ax]);
  r16[ax] = 0x28;
  _push(r16[ax]);
  r16[ax] = 0x0C;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  sub_2CEA();
  r16[ax] = 0x1AB8;
  _push(r16[ax]);
  r16[ax] = 0x0CE4;
  _push(r16[ax]);
  r16[ax] = 0x20;
  _push(r16[ax]);
  r16[ax] = 0x0D;
  _push(r16[ax]);
  r16[ax] = 4;
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2C9A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2C9A);
    _push(r16[ax]);
    r16[ax] = 0x0DCC;
    _push(r16[ax]);
    r16[ax] = 0x11;
    _push(r16[ax]);
    r16[ax] = 0x0F;
    _push(r16[ax]);
    r16[ax] = 2;
    _push(r16[ax]);
    sub_2D9A();
    r16[ax] = _pop();
    if ( r8[al] != 6 ) // jnz 
      { _pc = 0x2CBC; continue; }
    r8[al] = 0;
    sub_2CC7();
    r8[al] = 6;
    sub_2CC7();
    return;
  case 0x2CBC:
    if ( r8[al] != 7 ) // jnz 
    {
  	  sub_2CC7();
  	  return;
    }
    r8[al] = 1;
    sub_2CC7();
    r8[al] = 7;
    _pc = -1;
  }
}
function sub_2CC7()
{
  STAT(0x2CC7);
  r8[bl] = r8[al];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x151F));
  _push(r16[ax]);
  r16[ax] = _data16get(OFS(r16[bx] + 0x152F));
  _push(r16[ax]);
  r16[ax] = _data16get(OFS(r16[bx] + 0x153F));
  _push(r16[ax]);
  r16[ax] = _data16get(OFS(r16[bx] + 0x154F));
  _push(r16[ax]);
  r16[ax] = _data16get(OFS(r16[bx] + 0x150F));
  _push(r16[ax]);
  sub_2CEA();
}
function sub_2CEA()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2CEA);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    // arg_4		= word ptr  8
    // arg_6		= word ptr  0Ah
    // arg_8		= word ptr  0Ch
    _push(bp);
    bp = sp;
    r16[ax] = 0x0A000;
    es = r16[ax];
    di = _stack16get(bp + arg_6);
    r16[bx] = _stack16get(bp + arg_0);
    r16[bx] = _data16get(OFS(r16[bx] - 0x6B18));
    si = _stack16get(bp + arg_8);
    _push(ds);
    _push(r16[bx]);
    r16[dx] = 0x3CE;
    r16[ax] = 0x0A05;
    _out(r16[dx], r16[ax]);
    r16[ax] = 7;
    _out(r16[dx], r16[ax]);
    r16[cx] = _stack16get(bp + arg_4);
    r16[cx] >>= 1;
    r8[ah] = 0x80;
    r8[al] = 8;
    ds = _pop();
    r16[bx] = _stack16get(bp + arg_2);
  case 0x2D19:
    _push(r16[ax]);
    _push(r16[bx]);
    _push(r16[cx]);
    _push(di);
    _push(si);
  case 0x2D1E:
    r8[bh] = 0x22;
  case 0x2D20:
    r8[bl] = _data[ADR(ds, si)];
    si = si + 1;
    if ( r8[bh] != r8[bl] ) // jnz 
      { _pc = 0x2D3D; continue; }
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0x2D32; continue; }
    r8[ah] = 0x40;
    di = di + 1;
    if ( --r16[cx] )
      { _pc = 0x2D20; continue; }
    _pc = 0x2D76;
      continue;
  case 0x2D32:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0x2D39; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0x2D39:
    if ( --r16[cx] )
      { _pc = 0x2D20; continue; }
    _pc = 0x2D76;
      continue;
  case 0x2D3D:
    r8[bh] = r8[bl];
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    r8[bl] >>= 1;
    if ( r8[bl] == 2 ) // jz 
      { _pc = 0x2D55; continue; }
    _out(r16[dx], r16[ax]);
    _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bl]);
    _video8set(ADR(es,di+0x2000), _video8get(ADR(es,di+0x2000)) & r8[bl]);
  case 0x2D55:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0x2D5C; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0x2D5C:
    r8[bh] &= 0x0F;
    if ( r8[bh] == 2 ) // jz 
      { _pc = 0x2D6D; continue; }
    _out(r16[dx], r16[ax]);
    _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bh]);
    _video8set(ADR(es,di+0x2000), _video8get(ADR(es,di+0x2000)) & r8[bh]);
  case 0x2D6D:
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0x2D74; continue; }
    r8[ah] = 0x80;
    di = di + 1;
  case 0x2D74:
    if ( --r16[cx] )
      { _pc = 0x2D1E; continue; }
  case 0x2D76:
    si = _pop();
    si += 0x0A0;
    di = _pop();
    di += 0x28;
    di &= 0x7FFF;
    r16[cx] = _pop();
    r16[bx] = _pop();
    r16[ax] = _pop();
    r16[bx]--;
    if ( r16[bx] ) // jnz 
      { _pc = 0x2D19; continue; }
    ds = _pop();
    r16[ax] = 0x0FF08;
    _out(r16[dx], r16[ax]);
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F07;
    _out(r16[dx], r16[ax]);
    bp = _pop();
    _retn(0x0A);
    _pc = -1;
  }
}
function sub_2D9A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2D9A);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    // arg_4		= word ptr  8
    // arg_6		= word ptr  0Ah
    _push(bp);
    bp = sp;
    r16[ax] = 0x0A000;
    es = r16[ax];
    di = _stack16get(bp + arg_6);
    r16[dx] = 0x3CE;
    r16[ax] = _stack16get(bp + arg_0);
    r8[ah] = r8[al];
    r8[al] = 0;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F01;
    _out(r16[dx], r16[ax]);
    _cld();
    r16[bx] = _stack16get(bp + arg_2);
  case 0x2DB8:
    _push(di);
    r16[cx] = _stack16get(bp + arg_4);
    _rep_stosb();
    di = _pop();
    _push(di);
    di += 0x2000;
    r16[cx] = _stack16get(bp + arg_4);
    _rep_stosb();
    di = _pop();
    di += 0x28;
    r16[bx]--;
    if ( r16[bx] ) // jnz 
      { _pc = 0x2DB8; continue; }
    r16[ax] = 0;
    _out(r16[dx], r16[ax]);
    r8[al] = r8[al] + 1;
    _out(r16[dx], r16[ax]);
    bp = _pop();
    _retn(8);
    _pc = -1;
  }
}
function sub_2DDC()
{
  STAT(0x2DDC);
  r8[bl] = _data[0x94E4];
  r16[bx] &= 3;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x1A2A));
  _data16set(0x94E2, r16[ax]);
  _data[0x94E4] = _data[0x94E4] + 1;
  _data[0x9527] = 0x0FF;
}
function sub_2DF6()
{
  STAT(0x2DF6);
  r8[al] = 0;
  _data[0x94E5] = r8[al];
  _data[0x94E6] = r8[al];
  _data[0x94E7] = r8[al];
}
function sub_2E02()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2E02);
    _push(si);
    sub_1B80();
    sub_309D();
    si = _pop();
    r16[ax] = _data16get(0x952A);
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[bx] = _data16get(0x954C);
    if ( !(r8[bl] & 1) ) // jz 
      { _pc = 0x2E23; continue; }
    r16[ax] = - r16[ax];
    r16[ax] -= 3;
    _pc = 0x2E30;
      continue;
  case 0x2E23:
    if ( !(r8[bl] & 2) ) // jz 
      { _pc = 0x2E2D; continue; }
    r16[ax] += 3;
    _pc = 0x2E30;
      continue;
  case 0x2E2D:
    r16[ax] = 0;
  case 0x2E30:
    _data16set(0x9522, r16[ax]);
    r8[al] = _data[ADR(ds, si + 0x16)];
    r16[ax] &= 0x7F;
    if ( r8[al] <= 0x3F ) // jbe 
      { _pc = 0x2E48; continue; }
    r8[al] = - r8[al];
    r8[al] += 0x7F;
    sub_3084();
    r16[ax] = - r16[ax];
    _pc = 0x2E4B;
      continue;
  case 0x2E48:
    sub_3084();
  case 0x2E4B:
    _data16set(0x9520, r16[ax]);
    r16[ax] = _data16get(0x951E);
    r16[ax] += _data16get(0x9522);
    r16[ax] += _data16get(0x9520);
    if ( !r16[ax] ) // jz 
      { _pc = 0x2E6A; continue; }
  // dummy
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x2E63; continue; }
    r16[ax] = r16[ax] + 1;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x2E61; continue; }
    r16[ax] = r16[ax] + 1;
  case 0x2E61:
    _pc = 0x2E6A;
      continue;
  case 0x2E63:
    r16[ax]--;
    if ( _short(r16[ax]) <= _short(0) ) // jle 
      { _pc = 0x2E6A; continue; }
    r16[ax]--;
  case 0x2E6A:
    if ( _short(r16[ax]) <= _short(0x40) ) // jle 
      { _pc = 0x2E74; continue; }
    r16[ax] = 0x40;
    _pc = 0x2E7C;
      continue;
  case 0x2E74:
    if ( _short(r16[ax]) >= _short(0x0FFC0) ) // jge 
      { _pc = 0x2E7C; continue; }
    r16[ax] = 0x0FFC0;
  case 0x2E7C:
    _data16set(0x951E, r16[ax]);
    r16[ax] = _sar16(r16[ax]);
    r16[ax] = _sar16(r16[ax]);
  //  unknown_command(); // sar	ax, 1
  //  unknown_command(); // sar	ax, 1
    _data[ADR(ds, si + 0x16)] += r8[al];
    r8[al] = _data[ADR(ds, si + 0x16)];
    r16[ax] &= 0x7F;
    r16[bx] = r16[ax];
    r8[al] = _data[OFS(r16[bx] + 0x1675)];
    _cbw();
    r16[ax] <<= 1;
    r16[ax] += 0x80;
    _data16set(ADR(ds, si + 5), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x16F5)];
    _cbw();
    r16[ax] <<= 1;
    r16[ax] += 0x80;
    _push(r16[bx]);
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x2EBE; continue; }
    r16[bx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] += r16[bx];
    r16[ax] <<= 1;
    r16[ax] += 5;
    r8[bl] = 0x0C;
    _div(r8[bl]);
    r8[ah] = 0;
  case 0x2EBE:
    r16[bx] = _pop();
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x1775)];
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x1594;
    sub_2121();
    r8[al] = _data[0x94E6];
    _data[0x94E7] = r8[al];
    r8[al] = _data[0x94E5];
    _data[0x94E6] = r8[al];
    r8[al] = _data[0x1BA0];
    _data[0x94E5] = r8[al];
    r16[ax] = _data16get(0x954C);
    r8[bl] = _data[0x951A];
    if ( !(r8[al] & 0x40) ) // jz 
      { _pc = 0x2F02; continue; }
    if ( r8[bl] != 2 ) // jnz 
      { _pc = 0x2F00; continue; }
    _data[0x951A] = 3;
    r8[al] = 2;
    sub_3840();
    _data[0x951C] = 2;
  case 0x2F00:
    _pc = 0x2F18;
      continue;
  case 0x2F02:
    if ( r8[bl] != 1 ) // jnz 
      { _pc = 0x2F0E; continue; }
    _data[0x951A] = 2;
    _pc = 0x2F18;
      continue;
  case 0x2F0E:
    if ( r8[bl] != 3 ) // jnz 
      { _pc = 0x2F18; continue; }
    _data[0x951A] = 0;
  case 0x2F18:
    r16[ax] = _data16get(0x954C);
    r8[bl] = _data[0x951B];
    if ( !(r8[al] & 0x20) ) // jz 
      { _pc = 0x2F39; continue; }
    if ( r8[bl] != 2 ) // jnz 
      { _pc = 0x2F37; continue; }
    _data[0x951B] = 3;
    r8[al] = 2;
    sub_3840();
    _data[0x951C] = 2;
  case 0x2F37:
    return;
  case 0x2F39:
    if ( r8[bl] != 1 ) // jnz 
      { _pc = 0x2F45; continue; }
    _data[0x951B] = 2;
    return;
  case 0x2F45:
    if ( r8[bl] != 3 ) // jnz 
      return;
    _data[0x951B] = 0;
    _pc = -1;
  }
}
function sub_2F50()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x2F50);
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x20 ) // jnz 
      { _pc = 0x2F5E; continue; }
    r8[ah] = _data[0x951A];
    r8[al] = 0x0F8;
    _pc = 0x2F64;
      continue;
  case 0x2F5E:
    r8[ah] = _data[0x951B];
    r8[al] = 8;
  case 0x2F64:
    if ( r8[ah] == 3 ) // jz 
      { _pc = 0x2F6E; continue; }
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x2F90; continue; }
  case 0x2F6E:
    _data[ADR(ds, si)] = 0;
    si = 0x1BA1;
  case 0x2F74:
    r8[al] = _data[ADR(ds, si)];
    if ( r8[al] & 0x80 ) // jnz 
      return;
    if ( !(r8[al] & 1) ) // jz 
      { _pc = 0x2F8A; continue; }
    r8[al] = _data[ADR(ds, si + 0x12)];
    if ( r8[al] != 0x0F ) // jnz 
      { _pc = 0x2F8A; continue; }
    _push(si);
    sub_3059();
    si = _pop();
  case 0x2F8A:
    si += 0x17;
    _pc = 0x2F74;
      continue;
    return;
  case 0x2F90:
    r8[al] += _data[0x94E7];
    r16[ax] &= 0x7F;
    r16[bx] = r16[ax];
    r8[al] = _data[OFS(r16[bx] + 0x1675)];
    _cbw();
    r16[cx] = r16[ax];
  //  unknown_command(); // sar	cx, 1
    r16[cx] = _sar16(r16[cx]);
    r16[ax] += r16[cx];
    r16[ax] += 0x80;
    _data16set(ADR(ds, si + 5), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x16F5)];
    _cbw();
    r16[cx] = r16[ax];
    r16[cx] = _sar16(r16[cx]);
  //  unknown_command(); // sar	cx, 1
    r16[ax] += r16[cx];
    r16[ax] += 0x80;
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x2FD0; continue; }
    r16[bx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] += r16[bx];
    r16[ax] <<= 1;
    r16[ax] += 5;
    r8[bl] = 0x0C;
    _div(r8[bl]);
    r8[ah] = 0;
  case 0x2FD0:
    r8[bl] = _data[0x1BA0];
    r16[bx] &= 0x7F;
    _data16set(ADR(ds, si + 7), r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x1892)];
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = 0x1811;
    sub_2121();
    _pc = -1;
  }
}
function sub_2FE8()
{
  STAT(0x2FE8);
  r16[bx] = _data16get(0x9525);
  r16[bx] >>= 1;
  r16[bx] >>= 1;
  r16[bx] >>= 1;
  r16[bx] &= 0x1F;
  r8[al] = _data[OFS(r16[bx] + 0x1A0A)];
  _data[0x9549] = r8[al];
  r8[al] = _data[OFS(r16[bx] + 0x19EA)];
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x1929;
  sub_2121();
}
function sub_300A()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x300A);
    r16[ax] = _data16get(0x9547);
    r16[ax] -= _data16get(ADR(ds, si + 0x13));
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    if ( r16[ax] <= 0x2D ) // jbe 
      { _pc = 0x301F; continue; }
    _data[ADR(ds, si)] = 0;
    return;
  case 0x301F:
    _push(r16[ax]);
    sub_3130();
    r16[ax] = _pop();
    r16[ax] >>= 1;
    _data[ADR(ds, si + 4)] = r8[al];
    r16[bx] = r16[ax];
    r8[al] = _data[OFS(r16[bx] + 0x1A9A)];
    _data[ADR(ds, si + 2)] = r8[al];
    r16[bx] = 0x1AC9;
    sub_2121();
    r8[al] = _data[ADR(ds, si + 2)];
    if ( r8[al] == 2 ) // jz 
      { _pc = 0x3040; continue; }
    return;
  case 0x3040:
    r8[bl] = _data[0x1B8E];
    r8[bh] = 0;
    r8[al] = _data[OFS(r16[bx] + 0x17F5)];
    if ( r8[al] == _data[ADR(ds, si + 1)] ) // jz 
      { _pc = 0x3050; continue; }
    return;
  case 0x3050:
    r8[al] = 9;
    sub_3840();
    sub_3059();
    _pc = -1;
  }
}
function sub_3059()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3059);
    _data[ADR(ds, si)] = 0;
    r8[al] = _data[0x951D];
    if ( r8[al] != 0x40 ) // jnz 
      { _pc = 0x306A; continue; }
    _data16set(0x9540, _data16get(0x9540) + 6);
    return;
  case 0x306A:
    if ( r8[al] != 0x80 ) // jnz 
      { _pc = 0x3075; continue; }
    _data16set(0x953C, _data16get(0x953C) + 4);
    return;
  case 0x3075:
    if ( r8[al] != 0x0C0 ) // jnz 
      { _pc = 0x3080; continue; }
    _data16set(0x9544, _data16get(0x9544) + 8);
    return;
  case 0x3080:
    sub_268A();
    _pc = -1;
  }
}
function sub_3084()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3084);
    r8[al] -= 5;
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x308D; continue; }
    r16[ax] = 0;
    return;
  case 0x308D:
    if ( r8[al] <= 0x38 ) // jbe 
      { _pc = 0x3093; continue; }
    r8[al] = 0x38;
  case 0x3093:
    r8[al] >>= 1;
    r8[ah] = 0;
    r16[ax] = - r16[ax];
    r16[ax] -= 3;
    _pc = -1;
  }
}
function sub_309D()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x309D);
    r16[bx] = _data16get(0x952A);
    r16[bx] += 7;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] >>= 1;
    r16[bx] += 2;
    _data16set(0x9547, _data16get(0x9547) + r16[bx]);
    r16[ax] = _data16get(0x950F);
    r16[ax] += r16[bx];
    if ( r16[ax] <= 0x2E8 ) // jbe 
      { _pc = 0x30C4; continue; }
    r16[ax] = 0;
    _data16set(0x953C, 0x0FFFF);
  case 0x30C4:
    _data16set(0x950F, r16[ax]);
    r16[ax] = _data16get(0x9547);
    r16[ax] -= 0x380;
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x3124; continue; }
    r16[ax] = - r16[ax];
    if ( r16[ax] >= 0x100 ) // jnb 
      { _pc = 0x30ED; continue; }
    _data16set(0x9525, r16[ax]);
    r8[al] = _data[0x9524];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x30EB; continue; }
    si = 0x1912;
    sub_B58();
    _data[0x9524] = 1;
  case 0x30EB:
    _pc = 0x3122;
      continue;
  case 0x30ED:
    r16[ax] = _data16get(0x9547);
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    r16[ax] >>= 1;
    if ( r8[al] == _data[0x9527] ) // jz 
      { _pc = 0x3122; continue; }
    _data[0x9527] = r8[al];
    r8[bl] = r8[al];
    r8[bh] = 0;
    r16[bx] += _data16get(0x94E2);
    r8[al] = _data[r16[bx]];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x3122; continue; }
    si = 0x1AB2;
    _data[ADR(ds, si + 1)] = r8[al];
    r16[ax] = _data16get(0x9547);
    _data16set(ADR(ds, si + 0x13), r16[ax]);
    sub_B58();
  case 0x3122:
    return;
  case 0x3124:
    _data[0x94FF] = 0;
    r16[ax] = _data16get(0x950C);
    _data16set(0x9528, r16[ax]);
    _pc = -1;
  }
}

function sub_3130()
{
  STAT(0x3130);
  r8[bl] = r8[al];
  r8[bh] = 0;
  r8[cl] = _data[r16[bx] + 0x1A6A];
  r8[ch] = 0;
  r8[al] = _data[si + 1];
  if ( r8[al] == 1 ) // jz 
  {
    sub_315E();
	return;
  }
  if ( r8[al] == 2 ) // jz 
  {
    sub_3167();
	return;
  }
  if ( r8[al] == 3 ) // jz 
  {
    sub_3170();
	return;
  }
  if ( r8[al] == 4 ) // jz 
  {
	 sub_3178();
   return;
  }
  if ( r8[al] == 5 ) // jz 
  {
    sub_3181();
	return;
  }
  if ( r8[al] == 6 ) // jz 
  {
    sub_3188();
	return;
  }
  if ( r8[al] == 7 ) // jz 
  {
    sub_3191();
	return;
  }
  if ( r8[al] == 8 ) // jz 
  {
	sub_319B();
	return;
  }
}

function sub_3167()
{
	_push(r16[cx]);
	sub_315E();
	_pop(r16[cx]);
	sub_3170();
}

function sub_3178()
{
	_push(r16[cx]);
	sub_3170();
	_pop(r16[cx]);
	sub_3181();
}

function sub_3188()
{
	_push(r16[cx]);
	sub_3181();
	_pop(r16[cx]);
	sub_3191();
}

function sub_319B()
{
	_push(r16[cx]);
	sub_3191();
	_pop(r16[cx]);
	sub_315E();
}

function sub_315E()
{
  STAT(0x315E);
  r16[cx] = - r16[cx];
  r16[cx] += 0x6A;
  _data16set(ADR(ds, si + 7), r16[cx]);
}
function sub_3170()
{
  STAT(0x3170);
  r16[cx] += 0x80;
  _data16set(ADR(ds, si + 5), r16[cx]);
}
function sub_3181()
{
  STAT(0x3181);
  r16[cx] += 0x6A;
  _data16set(ADR(ds, si + 7), r16[cx]);
}
function sub_3191()
{
  STAT(0x3191);
  r16[cx] = - r16[cx];
  r16[cx] += 0x80;
  _data16set(ADR(ds, si + 5), r16[cx]);
}
function sub_31A4()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x31A4);
    r16[ax] = _data16get(0x94F8);
    es = r16[ax];
    di = 0x144;
    r16[bx] = _data16get(0x94F4);
    si = 0x340;
    sub_31E7();
    r16[ax] = ~ r16[ax];
    r16[ax] &= 0x0F;
    r8[ah] = r8[al];
    r8[al] = 1;
    r16[dx] = 0x3CE;
    _out(r16[dx], r16[ax]);
    sub_3209();
    r8[ah] = r8[al];
    r8[al] = 0;
    _out(r16[dx], r16[ax]);
    _push(ds);
    ds = r16[bx];
    _cld();
    r16[cx] = 0x0A0;
  case 0x31D2:
    _push(r16[cx]);
    r16[cx] = 0x20;
    _rep_movsb();
    di += 8;
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x31D2; continue; }
    ds = _pop();
    r16[ax] = 0;
    _out(r16[dx], r16[ax]);
    r8[al] = r8[al] + 1;
    _out(r16[dx], r16[ax]);
    _pc = -1;
  }
}
function sub_31E7()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x31E7);
    r8[al] = _data[0x951D];
    if ( r8[al] != 0x40 ) // jnz 
      { _pc = 0x31F3; continue; }
    r16[ax] = 2;
    return;
  case 0x31F3:
    if ( r8[al] != 0x80 ) // jnz 
      { _pc = 0x31FC; continue; }
    r16[ax] = 4;
    return;
  case 0x31FC:
    if ( r8[al] != 0x0C0 ) // jnz 
      { _pc = 0x3205; continue; }
    r16[ax] = 1;
    return;
  case 0x3205:
    r16[ax] = 3;
    _pc = -1;
  }
}
function sub_3209()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3209);
    r8[al] = _data[0x951C];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x3215; continue; }
    r16[ax] = 0;
    return;
  case 0x3215:
    if ( r8[al] != 1 ) // jnz 
      { _pc = 0x3223; continue; }
    r16[ax] = 7;
    _data[0x951C] = 0;
    return;
  case 0x3223:
    r16[ax] = 0x0F;
    _data[0x951C] = 1;
    _pc = -1;
  }
}
function sub_3291()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3291);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
    r16[ax] = _stack16get(bp + arg_0);
    es = r16[ax];
    di = 0x144;
    r16[bx] = _stack16get(bp + arg_2);
    si = 0x144;
    r16[dx] = 0x3CE;
    r16[ax] = 0x105;
    _out(r16[dx], r16[ax]);
    _push(ds);
    ds = r16[bx];
    _cld();
    r16[cx] = 0x0A0;
  case 0x32B0:
    _push(r16[cx]);
    r16[cx] = 0x20;
    _rep_movsb();
    si += 8;
    di += 8;
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x32B0; continue; }
    ds = _pop();
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_32FE()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x32FE);
    r16[dx] = 0x3CE;
    r16[ax] = 0x105;
    _out(r16[dx], r16[ax]);
    r16[ax] = _data16get(0x94F8);
    es = r16[ax];
    di = 0x144;
    r16[ax] = _data16get(0x9528);
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    si = r16[ax];
    _push(ds);
    r16[ax] = 0x0A800;
    ds = r16[ax];
    _cld();
    r16[cx] = 0x0A0;
  case 0x3326:
    _push(r16[cx]);
    r16[cx] = 0x20;
    _rep_movsb();
    si &= 0x7FFF;
    di += 8;
    r16[cx] = _pop();
    if ( --r16[cx] )
      { _pc = 0x3326; continue; }
    ds = _pop();
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    _pc = -1;
  }
}
function sub_333C()
{
  STAT(0x333C);
  r16[ax] = 0x0D;
  _int(0x10);
  r16[ax] = 0x0A000;
  _data16set(0x94FA, r16[ax]);
  r16[ax] += 0x200;
  _data16set(0x94F8, r16[ax]);
  r16[ax] = 0;
  sub_33B3();
  r16[ax] = _data16get(0x94F8);
  r16[bx] = _data16get(0x94FA);
  _data16set(0x94F8, r16[bx]);
  _data16set(0x94FA, r16[ax]);
  sub_33D7();
  r16[bx] = _data16get(0x94FA);
  r16[bx] <<= 1;
  r16[bx] <<= 1;
  r16[bx] <<= 1;
  r16[bx] <<= 1;
  _cli();
  r16[dx] = 0x3D4;
  r8[ah] = r8[bh];
  r8[al] = 0x0C;
  _out(r16[dx], r16[ax]);
  r8[ah] = r8[bl];
  r8[al] = r8[al] + 1;
  _out(r16[dx], r16[ax]);
  _sti();
  sub_33D7();
}
function sub_3383() // swap pages
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3383);
    r16[ax] = _data16get(0x94F8);
    r16[bx] = _data16get(0x94FA);
    _data16set(0x94F8, r16[bx]);
    _data16set(0x94FA, r16[ax]);
    r16[bx] = _data16get(0x94FA);
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    r16[bx] <<= 1;
    _cli();
    r16[dx] = 0x3D4;
    r8[ah] = r8[bh];
    r8[al] = 0x0C;
    _out(r16[dx], r16[ax]);
    _sti();
    /*
    V-Sync wait
    r16[dx] = 0x3DA;
  case 0x33AA:
    r8[al] = _in(r16[dx]);
    r8[al] &= 8;
    if ( r8[al] ) // jnz 
      { _pc = 0x33AA; continue; }
  	*/
    sub_33D7();
    _pc = -1;
  }
}
function sub_33B3()
{
  STAT(0x33B3);
  _push(r16[ax]);
  r16[ax] = _data16get(0x94F8);
  es = r16[ax];
  di = 0;
  r16[dx] = 0x3CE;
  r16[ax] = _pop();
  r8[ah] = r8[al];
  r8[al] = 0;
  _out(r16[dx], r16[ax]);
  r16[ax] = 0x0F01;
  _out(r16[dx], r16[ax]);
  _cld();
  r16[cx] = 0x0FA0;
  _rep_stosw();
  r16[ax] = 0;
  _out(r16[dx], r16[ax]);
  r8[al] = r8[al] + 1;
  _out(r16[dx], r16[ax]);
}
function sub_33D7()
{
  return; // v-sync
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x33D7);
    r16[dx] = 0x3DA;
  case 0x33DA:
    r8[al] = _in(r16[dx]);
    r8[al] &= 8;
    if ( !r8[al] ) // jz 
      { _pc = 0x33DA; continue; }
  case 0x33DF:
    r8[al] = _in(r16[dx]);
    r8[al] &= 8;
    if ( r8[al] ) // jnz 
      { _pc = 0x33DF; continue; }
    _pc = -1;
  }
}
function sub_33E5()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x33E5);
    r16[ax] = _data16get(0x94F8);
    es = r16[ax];
    di = 0;
    r16[dx] = 0x3CE;
    r16[ax] = 0x805;
    _out(r16[dx], r16[ax]);
    r16[ax] = 7;
    _out(r16[dx], r16[ax]);
    r8[dl] = 0x0C4;
    r16[ax] = 0x802;
    _push(ds);
    ds = r16[bx];
  case 0x3400:
    _out(r16[dx], r16[ax]);
    _push(r16[ax]);
    _push(di);
    r16[cx] = 0x1F40;
  case 0x3406:
    _lodsb();
    _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[al]);
    di = di + 1;
    if ( --r16[cx] )
      { _pc = 0x3406; continue; }
    di = _pop();
    r16[ax] = _pop();
    r8[ah] >>= 1;
    if ( r8[ah] ) // jnz 
      { _pc = 0x3400; continue; }
    ds = _pop();
    r16[ax] = 0x0F02;
    _out(r16[dx], r16[ax]);
    r8[dl] = 0x0CE;
    r16[ax] = 5;
    _out(r16[dx], r16[ax]);
    r16[ax] = 0x0F07;
    _out(r16[dx], r16[ax]);
    _pc = -1;
  }
}
function sub_3423()
{
  STAT(0x3423);
  r16[ax] = 0;
  sub_33B3();
  sub_3439();
  sub_3383();
  r16[ax] = 0;
  sub_33B3();
  sub_3439();
}
function sub_3439()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3439);
    r16[ax] = _data16get(0x94F8);
    es = r16[ax];
    di = 0x11C;
    r16[ax] = 0x0FFFF;
    r16[cx] = 0x10;
    _rep_stosw();
    di = 0x1A44;
    r16[cx] = 0x10;
    _rep_stosw();
    di = 0x11B;
    r8[al] = 1;
    r16[cx] = 0x0A2;
  case 0x3459:
    _video8set(ADR(es,di), r8[al]);
    di += 0x28;
    if ( --r16[cx] )
      { _pc = 0x3459; continue; }
    di = 0x13C;
    r8[al] = 0x80;
    r16[cx] = 0x0A2;
  case 0x3469:
    _video8set(ADR(es,di), r8[al]);
    di += 0x28;
    if ( --r16[cx] )
      { _pc = 0x3469; continue; }
    _pc = -1;
  }
}
function sub_3472()
{
  STAT(0x3472);
  si = 0;
  r16[bx] = _data16get(0x94F2);
  sub_33E5();
  sub_3383();
  si = 0;
  r16[bx] = _data16get(0x94F2);
  sub_33E5();
  r16[ax] = _data16get(0x94F8);
  _push(r16[ax]);
  r16[ax] = 0x0A000;
  r16[ax] += 0x400;
  _push(r16[ax]);
  sub_3291();
}
function sub_3498()
{
  STAT(0x3498);
  r16[ax] = 0x0A000;
  r16[ax] += 0x400;
  _push(r16[ax]);
  r16[ax] = _data16get(0x94F8);
  _push(r16[ax]);
  sub_3291();
}
function sub_34A8()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x34A8);
    di = 0;
    r16[ax] = _data16get(0x94F4);
    es = r16[ax];
    r16[ax] = 0;
    r16[cx] = 0x1000;
    _cld();
    _rep_stosw();
    r16[ax] = 0x4F;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r16[ax] = 0x0B0;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x4F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 0x0B0;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 0x4F;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r16[ax] = 0x0B0;
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 0x0B0;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r16[ax] = 0x4F;
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = _data16get(0x9547);
    r16[ax] &= 0x3F;
    _data16set(0x954E, r16[ax]);
    r16[bx] = r16[ax];
    r16[ax] += 0x40;
    _push(r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x1FDC)];
    r8[ah] = 0;
    _push(r16[ax]);
    sub_35BC();
    r16[ax] = _data16get(0x954E);
    if ( r16[ax] <= 0x0C ) // jbe 
      { _pc = 0x3527; continue; }
    return;
  case 0x3527:
    r16[bx] = _data16get(0x954E);
    r8[al] = _data[OFS(r16[bx] + 0x201C)];
    r8[ah] = 0;
    r16[ax] += 0x80;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x2029)];
    r8[ah] = 0;
    r16[ax] = - r16[ax];
    r16[ax] += 0x7F;
    _push(r16[ax]);
    sub_36D4();
    r16[bx] = _data16get(0x954E);
    r8[al] = _data[OFS(r16[bx] + 0x201C)];
    r8[ah] = 0;
    r16[ax] = - r16[ax];
    r16[ax] += 0x7F;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x2029)];
    r8[ah] = 0;
    r16[ax] = - r16[ax];
    r16[ax] += 0x7F;
    _push(r16[ax]);
    sub_36D4();
    r16[bx] = _data16get(0x954E);
    r8[al] = _data[OFS(r16[bx] + 0x201C)];
    r8[ah] = 0;
    r16[ax] += 0x80;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x2029)];
    r8[ah] = 0;
    r16[ax] += 0x80;
    _push(r16[ax]);
    sub_36D4();
    r16[bx] = _data16get(0x954E);
    r8[al] = _data[OFS(r16[bx] + 0x201C)];
    r8[ah] = 0;
    r16[ax] = - r16[ax];
    r16[ax] += 0x7F;
    _push(r16[ax]);
    r16[ax] = 0x0FF;
    _push(r16[ax]);
    r16[ax] = 0;
    _push(r16[ax]);
    r8[al] = _data[OFS(r16[bx] + 0x2029)];
    r8[ah] = 0;
    r16[ax] += 0x80;
    _push(r16[ax]);
    sub_36D4();
    _pc = -1;
  }
}
function sub_35BC()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x35BC);
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    _push(bp);
    bp = sp;
  case 0x35BF:
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_2);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x80;
    r16[ax] += _stack16get(bp + arg_0);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_0);
    _push(r16[ax]);
    r16[ax] = 0x7F;
    r16[ax] -= _stack16get(bp + arg_2);
    _push(r16[ax]);
    sub_36D4();
    r16[ax] = _stack16get(bp + arg_2);
    r16[ax] >>= 1;
    if ( r8[al] <= _data[0x9549] ) // jbe 
      { _pc = 0x36D0; continue; }
    _stack16set(OFS(bp + arg_2), r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    r16[ax] >>= 1;
    _stack16set(OFS(bp + arg_0), r16[ax]);
    _pc = 0x35BF;
      continue;
  case 0x36D0:
    bp = _pop();
    _retn(4);
    _pc = -1;
  }
}
function sub_36D4()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x36D4);
    // var_A		= word ptr -0Ah
    // var_6		= word ptr -6
    // var_4		= word ptr -4
    // var_2		= word ptr -2
    // arg_0		= word ptr  4
    // arg_2		= word ptr  6
    // arg_4		= word ptr  8
    // arg_6		= word ptr  0Ah
    _push(bp);
    bp = sp;
    sp -= 0x0A;
    r16[ax] = _data16get(0x94F4);
    es = r16[ax];
    r16[ax] = _stack16get(bp + arg_4);
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x36FA; continue; }
    r16[bx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] += r16[bx];
    r16[ax] <<= 1;
    r16[ax] += 5;
    r8[bl] = 0x0C;
    _div(r8[bl]);
    r8[ah] = 0;
  case 0x36FA:
    _stack16set(OFS(bp + arg_4), r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    if ( r16[ax] == 0 ) // jz 
      { _pc = 0x3718; continue; }
    r16[bx] = r16[ax];
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] += r16[bx];
    r16[ax] <<= 1;
    r16[ax] += 5;
    r8[bl] = 0x0C;
    _div(r8[bl]);
    r8[ah] = 0;
  case 0x3718:
    _stack16set(OFS(bp + arg_0), r16[ax]);
    r16[ax] = _stack16get(bp + arg_6);
    r16[bx] = _stack16get(bp + arg_2);
    if ( r16[bx] >= r16[ax] ) // jnb 
      { _pc = 0x3737; continue; }
    _stack16set(OFS(bp + arg_6), r16[bx]);
    _stack16set(OFS(bp + arg_2), r16[ax]);
    r16[ax] = _stack16get(bp + arg_4);
    r16[bx] = _stack16get(bp + arg_0);
    _stack16set(OFS(bp + arg_4), r16[bx]);
    _stack16set(OFS(bp + arg_0), r16[ax]);
  case 0x3737:
    r16[ax] = _stack16get(bp + arg_2);
    r16[ax] -= _stack16get(bp + arg_6);
    _stack16set(OFS(bp + var_2), r16[ax]);
    r16[ax] = _stack16get(bp + arg_0);
    r16[ax] -= _stack16get(bp + arg_4);
    if ( _short(r16[ax]) >= 0 ) // jns 
      { _pc = 0x3751; continue; }
    r16[ax] = - r16[ax];
    _stack16set(OFS(bp + var_A), 0x0FFE0);
    _pc = 0x3756;
      continue;
  case 0x3751:
    _stack16set(OFS(bp + var_A), 0x20);
  case 0x3756:
    _stack16set(OFS(bp + var_4), r16[ax]);
    r16[cx] = _stack16get(bp + var_2);
    if ( r16[cx] == 0 ) // jz 
      { _pc = 0x37DB; continue; }
    if ( r16[ax] != 0 ) // jnz 
      { _pc = 0x3769; continue; }
    _pc = 0x37ED;
      continue;
  case 0x3769:
    if ( r16[ax] >= _stack16get(bp + var_2) ) // jnb 
      { _pc = 0x37A4; continue; }
    r16[ax] = _stack16get(bp + var_2);
    r16[ax] >>= 1;
    _stack16set(OFS(bp + var_6), r16[ax]);
    sub_3801();
    r16[cx] = _stack16get(bp + var_2);
  case 0x377C:
    r8[al] >>= 1;
    if ( r8[al] ) // jnz 
      { _pc = 0x3783; continue; }
    r8[al] = 0x80;
    di = di + 1;
  case 0x3783:
    r16[bx] = _stack16get(bp + var_6);
    r16[bx] += _stack16get(bp + var_4);
    _stack16set(OFS(bp + var_6), r16[bx]);
    if ( r16[bx] <= _stack16get(bp + var_2) ) // jbe 
      { _pc = 0x379D; continue; }
    r16[bx] -= _stack16get(bp + var_2);
    _stack16set(OFS(bp + var_6), r16[bx]);
    r16[bx] = _stack16get(bp + var_A);
    di += _stack16get(bp + var_A);
  case 0x379D:
    _data[ADR(es,di)] |= r8[al];
    if ( --r16[cx] )
      { _pc = 0x377C; continue; }
    _pc = 0x37D5;
      continue;
  case 0x37A4:
    r16[ax] = _stack16get(bp + var_4);
    r16[ax] >>= 1;
    _stack16set(OFS(bp + var_6), r16[ax]);
    sub_3801();
    r16[cx] = _stack16get(bp + var_4);
  case 0x37B2:
    di += _stack16get(bp + var_A);
    r16[bx] = _stack16get(bp + var_6);
    r16[bx] += _stack16get(bp + var_2);
    _stack16set(OFS(bp + var_6), r16[bx]);
    if ( r16[bx] <= _stack16get(bp + var_4) ) // jbe 
      { _pc = 0x37D0; continue; }
    r16[bx] -= _stack16get(bp + var_4);
    _stack16set(OFS(bp + var_6), r16[bx]);
    r8[al] >>= 1;
    if ( r8[al] ) // jnz 
      { _pc = 0x37D0; continue; }
    r8[al] = 0x80;
    di = di + 1;
  case 0x37D0:
    _data[ADR(es,di)] |= r8[al];
    if ( --r16[cx] )
      { _pc = 0x37B2; continue; }
  case 0x37D5:
    sp = bp;
    bp = _pop();
    _retn(8);
    return;
  case 0x37DB:
    sub_3801();
    r16[cx] = _stack16get(bp + var_4);
    if ( r16[cx] == 0 )
      { _pc = 0x37D5; continue; }
    //unknown_command(); // jcxz	short loc_code_37D5
  case 0x37E3:
    di += _stack16get(bp + var_A);
    _data[ADR(es,di)] |= r8[al];
    if ( --r16[cx] )
      { _pc = 0x37E3; continue; }
    _pc = 0x37D5;
      continue;
  case 0x37ED:
    sub_3801();
    r16[cx] = _stack16get(bp + var_2);
  case 0x37F3:
    r8[al] >>= 1;
    if ( r8[al] ) // jnz 
      { _pc = 0x37FA; continue; }
    r8[al] = 0x80;
    di = di + 1;
  case 0x37FA:
    _data[ADR(es,di)] |= r8[al];
    if ( --r16[cx] )
      { _pc = 0x37F3; continue; }
    _pc = 0x37D5;
      continue;
    _pc = -1;
  }
}
function sub_3801()
{
  STAT(0x3801);
  r16[ax] = _stack16get(bp + 8);
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  di = r16[ax];
  r16[ax] = _stack16get(bp + 0x0A);
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  di += r16[ax];
  r16[cx] = _stack16get(bp + 0x0A);
  r16[cx] &= 7;
  r8[al] = 0x80;
  r8[al] >>= r8[cl];
  _data[ADR(es,di)] |= r8[al];
}
function sub_382A()
{
  STAT(0x382A);
  r8[al] = 0;
  _data[0x9550] = r8[al];
  _data[0x9551] = r8[al];
  _data[0x9552] = r8[al];
  _data[0x9506] = 1;
  _data[0x9505] = 0;
}
function sub_3840()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3840);
    r8[ah] = _data[0x955E];
    if ( r8[ah] == 0 ) // jz 
      { _pc = 0x384A; continue; }
    return;
  case 0x384A:
    r8[ah] = _data[0x9506];
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x3854; continue; }
    return;
  case 0x3854:
    r8[ah] = _data[0x9550];
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x3866; continue; }
    _push(r16[bx]);
    _data[0x9550] = r8[al];
    sub_3914();
    r16[bx] = _pop();
    return;
  case 0x3866:
    r8[ah] = _data[0x9551];
    if ( r8[ah] != 0 ) // jnz 
      { _pc = 0x3873; continue; }
    _data[0x9551] = r8[al];
    return;
  case 0x3873:
    if ( r8[al] <= _data[0x9552] ) // jbe 
      return;
    _data[0x9552] = r8[al];
    _pc = -1;
  }
}
function sub_387D()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x387D);
    r8[al] = _data[0x955E];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x389B; continue; }
    r8[al] = _data[0x9506];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x3890; continue; }
    sub_39DB();
    _pc = 0x389B;
      continue;
  case 0x3890:
    _data16set(0x955F, 0);
    _data[0x955E] = 0;
  case 0x389B:
    r8[al] = _data[0x9550];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x38A3; continue; }
    return;
  case 0x38A3:
    _data[0x9557]--;
    if ( _data[0x9557] ) // jnz 
      { _pc = 0x38D4; continue; }
    r8[al] = _data[0x9506];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x38B4; continue; }
    sub_39A3();
    return;
  case 0x38B4:
    r8[al] = _data[0x9551];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x38D0; continue; }
    _data[0x9550] = r8[al];
    r8[bl] = _data[0x9552];
    _data[0x9551] = r8[bl];
    _data[0x9552] = 0;
    sub_3914();
    return;
  case 0x38D0:
    sub_39A3();
    return;
  case 0x38D4:
    r16[ax] = _data16get(0x9558);
    r16[ax] += _data16get(0x955A);
    _data16set(0x9558, r16[ax]);
    r8[al] = _data[0x9553];
    if ( r8[al] == 0 ) // jz 
      { _pc = 0x38FD; continue; }
    r8[bl] = _data[0x9554];
    _data[0x9554] = _data[0x9554] + 1;
    r16[bx] &= 0x0F;
    r16[bx] <<= 1;
    r16[bx] += _data16get(0x9555);
    r16[ax] = _data16get(r16[bx]);
    _data16set(0x955C, r16[ax]);
    _pc = 0x3903;
      continue;
  case 0x38FD:
    _data16set(0x955C, 0);
  case 0x3903:
    r16[ax] = _data16get(0x9558);
    _data16set(0x955C, _data16get(0x955C) + r16[ax]);
    r16[ax] = _data16get(0x955C);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    _pc = -1;
  }
}
function sub_3914()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3914);
    r8[al]--;
    r8[bl] = r8[al];
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[bx] = _data16get(OFS(r16[bx] - 0x741C));
    r8[al] = _data[OFS(r16[bx] + 1)];
    _data[0x9557] = r8[al];
    if ( r16[bx] != 0x8C2C ) // jnz 
      { _pc = 0x3941; continue; }
    r16[ax] = _data16get(0x9536);
    r8[ah] = r8[al];
    r8[al] = 0;
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] = - r16[ax];
    r16[ax] += 0x1F40;
    _data16set(0x8C2E, r16[ax]);
    _pc = 0x3966;
      continue;
  case 0x3941:
    if ( r16[bx] != 0x8C32 ) // jnz 
      { _pc = 0x3966; continue; }
    r8[al] = _data[0x1BA0];
    r16[ax] &= 0x7F;
    if ( r16[ax] <= 0x3F ) // jbe 
      { _pc = 0x3957; continue; }
    r16[ax] -= 0x40;
    _pc = 0x395C;
      continue;
  case 0x3957:
    r16[ax] = - r16[ax];
    r16[ax] += 0x3F;
  case 0x395C:
    r16[ax] <<= 1;
    r16[ax] <<= 1;
    r16[ax] += 0x190;
    _data16set(0x8C34, r16[ax]);
  case 0x3966:
    r16[ax] = _data16get(OFS(r16[bx] + 2));
    _data16set(0x9558, r16[ax]);
    r16[ax] = _data16get(OFS(r16[bx] + 4));
    _data16set(0x955A, r16[ax]);
    r8[bl] = _data[r16[bx]];
    _data[0x9553] = r8[bl];
    if ( r8s[bl] <= _char(0) ) // jle 
      { _pc = 0x398F; continue; }
    r8[bl]--;
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] - 0x73A4));
    _data16set(0x9555, r16[ax]);
    _data[0x9554] = 0;
  case 0x398F:
    r8[al] = 0x0B6;
    _out(0x43, r8[al]);
    r16[ax] = _data16get(0x9558);
    _out(0x42, r8[al]);
    r8[al] = r8[ah];
    _out(0x42, r8[al]);
    r8[al] = _in(0x61);
    r8[al] |= 3;
    _out(0x61, r8[al]);
    _pc = -1;
  }
}
function sub_39A3()
{
  STAT(0x39A3);
  r8[al] = 0;
  _data[0x9550] = r8[al];
  _data[0x9551] = r8[al];
  _data[0x9552] = r8[al];
  _data[0x9557] = r8[al];
  r8[al] = _in(0x61);
  r8[al] &= 0x0FC;
  _out(0x61, r8[al]);
}
function sub_39B8()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x39B8);
    _data[0x9561] = 0;
    _data16set(0x955F, 0);
    _data[0x955E] = 1;
    r8[al] = _data[0x9546];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x39D4; continue; }
    r16[ax] = 0x8DEC;
    _pc = 0x39D7;
      continue;
  case 0x39D4:
    r16[ax] = 0x8D4C;
  case 0x39D7:
    _data16set(0x9562, r16[ax]);
    _pc = -1;
  }
}
function sub_39DB()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x39DB);
    _data[0x9561]--;
    if ( _datas[0x9561] < 0 ) // js 
      { _pc = 0x39E2; continue; }
    return;
  case 0x39E2:
    _data[0x9561] = 7;
    _data[0x8C57] = 0x0E;
    _data[0x8C56] = 4;
    r16[bx] = _data16get(0x955F);
    si = _data16get(0x9562);
    r8[al] = _data[OFS(r16[bx] + si)];
    if ( r8[al] != 0x0FF ) // jnz 
      { _pc = 0x3A05; continue; }
    _data[0x955E] = 0;
    return;
  case 0x3A05:
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x3A29; continue; }
    r8[al] = _data[0x9550];
    if ( r8[al] != 0 ) // jnz 
      { _pc = 0x3A25; continue; }
    _data[0x8C56] = 0;
    _data[0x8C57] = 6;
    r16[bx] &= 0x1F;
    r8[al] = _data[OFS(r16[bx] - 0x71A3)];
    r8[al] -= 0x0C;
    _pc = 0x3A27;
      continue;
  case 0x3A25:
    r8[al] = 0;
  case 0x3A27:
    _pc = 0x3A33;
      continue;
  case 0x3A29:
    if ( r8[al] != 0x0FE ) // jnz 
      { _pc = 0x3A31; continue; }
    r8[al] = 0;
    _pc = 0x3A33;
      continue;
  case 0x3A31:
    r8[al] += 0x0C;
  case 0x3A33:
    sub_3A3B();
    _data16set(0x955F, _data16get(0x955F) + 1);
    _pc = -1;
  }
}
function sub_3A3B()
{
  var _pc = 0;
  while (_pc != -1 && typeof(_pc) != "undefined" )
  switch (_pc)
  {
    case 0:
    STAT(0x3A3B);
    r8[al]--;
    if ( r8s[al] >= 0 ) // jns 
      { _pc = 0x3A40; continue; }
    return;
  case 0x3A40:
    r8[bl] = r8[al];
    r8[bh] = 0;
    r16[bx] <<= 1;
    r16[ax] = _data16get(OFS(r16[bx] - 0x731C));
    _data16set(0x8C58, r16[ax]);
    r8[al] = 0x0F;
    _data[0x9550] = r8[al];
    sub_3914();
    _pc = -1;
  }
}

