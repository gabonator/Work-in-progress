#include "goose_code.h"

WORD word_code_D93 = 0;
BYTE byte_code_D95 = 0;
BYTE byte_code_D96 = 0;

#if 0
#include "code.js"

#else
function start()
{
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
    goto loc_code_67;
  r16[dx] = 7;
  r8[ah] = 9;
  _int(0x21);
  r16[ax] = 0x4C00;
  _int(0x21);
  goto loc_code_6E;
loc_code_67:
  r16[dx] = 0x2A;
  r8[ah] = 9;
  _int(0x21);
loc_code_6E:
  sub_600();
  sub_333C();
  sub_2762();
  sub_5EC();
  sub_442();
  sub_588();
  sub_591();
  sub_382A();
  _data[0x9501] = 0;
loc_code_8B:
  sub_A9();
  sub_CF();
  sub_FD();
  goto loc_code_8B;
}
function sub_A9()
{
  STAT(0xA9);
  sub_103();
  _data[0x9500] = 0;
  _data[0x94FE] = 1;
  _data[0x94FC] = 0x10;
  _data[0x94FF] = 0;
  _data[0x9502] = 0;
  sub_DA7();
  sub_3423();
  sub_21DC();
}
function sub_CF()
{
  STAT(0xCF);
sub_code_CF:
  sub_1C0();
  sub_FDA();
  r8[al] = _data[0x94FF];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_E4;
  sub_32FE();
  sub_B8E();
  goto loc_code_ED;
loc_code_E4:
  sub_34A8();
  sub_31A4();
  sub_B8E();
loc_code_ED:
  // TODO: hit testing 
  /////////
  sub_220D(); // <--- problem!
  sub_3383();
  r8[al] = _data[0x9500];
  if ( r8[al] != 0 ) // jnz 
    return;
  goto sub_code_CF;
}
function sub_FD()
{
  STAT(0xFD);
  _data[0x6] = 1;
}
function sub_103()
{
  STAT(0x103);
  r8[al] = _data[0x6];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_115;
  _data16set(0x8E7E, 0x0DA);
  sub_279F();
  goto loc_code_11E;
loc_code_115:
  _data16set(0x8E7E, 0x0E9);
  sub_28DA();
loc_code_11E:
  sub_39B8();
  sub_3472();
  _data[0x9503] = 1;
  _data16set(0x8E80, 0);
  sub_D98();
loc_code_132:
  //printf("0x132");
  sub_1C0();
  sub_FDA();
  sub_3498();
  sub_B8E();
  sub_3383();
  r16[ax] = _data16get(0x954C);
  if ( r16[ax] & 0x80 ) // jnz 
    goto loc_code_197;
  _data16set(0x8E80, _data16get(0x8E80) + 1);
  r16[bx] = _data16get(0x8E80);
  if ( r16[bx] & 7 ) // jnz 
    goto loc_code_195;
  r16[bx] >>= 1;
  r16[bx] >>= 1;
  r16[bx] >>= 1;
  r16[bx] += _data16get(0x8E7E);
  r8[al] = _data[r16[bx]];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_195;
  if ( r8[al] == 0x0FF ) // jz 
    goto loc_code_197;
  if ( r8[al] != 0x0FE ) // jnz 
    goto loc_code_180;
  r8[al] = _data[0x9546];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_17B;
  sub_29DB();
  goto loc_code_17E;
loc_code_17B:
  sub_1AD();
loc_code_17E:
  goto loc_code_195;
loc_code_180:
  if ( r8[al] & 0x80 ) // jnz 
    goto loc_code_189;
  sub_19D();
  goto loc_code_195;
loc_code_189:
  r8[al] &= 0x3F;
  _push(r16[ax]);
  sub_19D();
  r16[ax] = _pop();
  r8[al] = r8[al] + 1;
  sub_19D();
loc_code_195:
  goto loc_code_132;
loc_code_197:
  _data[0x9503] = 0;
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
  STAT(0x1AD);
  r16[cx] = 0x1F40;
loc_code_1B0:
  _push(r16[cx]);
  sub_1C0();
  r16[cx] = _pop();
  r16[ax] = _data16get(0x954C);
  if ( !(r8[al] & 0x80) ) // jz 
    goto loc_code_1BD;
  return;
loc_code_1BD:
  if ( --r16[cx] )
    goto loc_code_1B0;
}
function sub_1C0()
{
  STAT(0x1C0);
  r16[bx] = 0x8E8A;
  si = 0x3D;
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_1D5;
  si = 0x3E;
loc_code_1CF:
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_1CF;
loc_code_1D5:
  si = 0x3B;
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_1E1;
  sub_33B();
loc_code_1E1:
  r16[bx] = 0x8E8A;
  si = _data16get(0x8F0D);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_1F6;
  _data16set(0x954C, 1);
  goto loc_code_20E;
loc_code_1F6:
  si = _data16get(0x8F0F);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_208;
  _data16set(0x954C, 2);
  goto loc_code_20E;
loc_code_208:
  _data16set(0x954C, 0);
loc_code_20E:
  si = _data16get(0x8F11);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_21F;
  _data16set(0x954C, _data16get(0x954C) | 4);
  goto loc_code_22E;
loc_code_21F:
  si = _data16get(0x8F13);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_22E;
  _data16set(0x954C, _data16get(0x954C) | 8);
loc_code_22E:
  si = _data16get(0x8F15);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_23E;
  _data16set(0x954C, _data16get(0x954C) | 0x80);
loc_code_23E:
  si = _data16get(0x8F17);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_24D;
  _data16set(0x954C, _data16get(0x954C) | 0x40);
loc_code_24D:
  si = _data16get(0x8F19);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_25C;
  _data16set(0x954C, _data16get(0x954C) | 0x20);
loc_code_25C:
  si = _data16get(0x8F1B);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_28C;
  sub_2C45();
  r16[bx] = 0x8E8A;
loc_code_26C:
  tick();
  r8[al] = _data[OFS(r16[bx] + 0x15)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_27C;
  r8[al] = _data[OFS(r16[bx] + 0x31)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_27C;
  goto loc_code_26C;
loc_code_27C:
  r16[bx] = 0x8E8A;
  r8[al] = _data[OFS(r16[bx] + 0x15)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_289;
  goto loc_code_96;
loc_code_289:
  sub_529();
loc_code_28C:
  r16[bx] = 0x8E8A;
  si = 0x3C;
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_2C5;
  r8[al] = _data[0x9505];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_2B0;
  r8[al] = 0x0E;
  sub_3840();
  _data[0x9505] = 1;
  _data[0x9506] = 0;
  goto loc_code_2C3;
loc_code_2B0:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_2C3;
  _data[0x9505] = 3;
  _data[0x9506] = 1;
  r8[al] = 0x0D;
  sub_3840();
loc_code_2C3:
  goto loc_code_2DC;
loc_code_2C5:
  r8[al] = _data[0x9505];
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_2D3;
  _data[0x9505] = 2;
  goto loc_code_2DC;
loc_code_2D3:
  if ( r8[al] != 3 ) // jnz 
    goto loc_code_2DC;
  _data[0x9505] = 0;
loc_code_2DC:
  r8[al] = _data[0x8F0A];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_2E4;
  return;
loc_code_2E4:
  r16[ax] = 3;
  _int(0x33);
  if ( !(r16[bx] & 1) ) // jz 
    goto loc_code_2F5;
  _data16set(0x954C, _data16get(0x954C) | 0x80);
loc_code_2F5:
  if ( !(r16[bx] & 2) ) // jz 
    goto loc_code_300;
  _data16set(0x954C, _data16get(0x954C) | 0x20);
loc_code_300:
  r16[ax] = _data16get(0x954C);
  r16[ax] &= 0x0F;
  if ( !r16[ax] ) // jz 
    goto loc_code_309;
  return;
loc_code_309:
  r16[ax] = 0x0B;
  _int(0x33);
  if ( (short)r16[cx] >= (short)0x0FFFB ) // jge 
    goto loc_code_31A;
  _data16set(0x954C, _data16get(0x954C) | 1);
  goto loc_code_324;
loc_code_31A:
  if ( (short)r16[cx] <= (short)5 ) // jle 
    goto loc_code_324;
  _data16set(0x954C, _data16get(0x954C) | 2);
loc_code_324:
  if ( (short)r16[dx] >= (short)0x0FFF6 ) // jge 
    goto loc_code_330;
  _data16set(0x954C, _data16get(0x954C) | 4);
  return;
loc_code_330:
  if ( (short)r16[dx] <= (short)0x0A ) // jle 
    return;
  _data16set(0x954C, _data16get(0x954C) | 8);
  return;
loc_code_96:
  // Exit game
  _ASSERT(0);
}
function sub_33B()
{
  STAT(0x33B);
  sub_2C07();
  r8[al] = 4;
  sub_2C9A();
  sub_4F3();
  _data16set(0x8F15, r16[ax]);
  r8[al] = 0;
  sub_2C9A();
loc_code_34E:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_34E;
  _data16set(0x8F0D, r16[ax]);
  r8[al] = 1;
  sub_2C9A();
loc_code_35F:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_35F;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_35F;
  _data16set(0x8F0F, r16[ax]);
  r8[al] = 2;
  sub_2C9A();
loc_code_376:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_376;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_376;
  if ( r16[ax] == _data16get(0x8F0F) ) // jz 
    goto loc_code_376;
  _data16set(0x8F11, r16[ax]);
  r8[al] = 3;
  sub_2C9A();
loc_code_393:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_393;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_393;
  if ( r16[ax] == _data16get(0x8F0F) ) // jz 
    goto loc_code_393;
  if ( r16[ax] == _data16get(0x8F11) ) // jz 
    goto loc_code_393;
  _data16set(0x8F13, r16[ax]);
  r8[al] = 6;
  sub_2C9A();
loc_code_3B6:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_3B6;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_3B6;
  if ( r16[ax] == _data16get(0x8F0F) ) // jz 
    goto loc_code_3B6;
  if ( r16[ax] == _data16get(0x8F11) ) // jz 
    goto loc_code_3B6;
  if ( r16[ax] == _data16get(0x8F13) ) // jz 
    goto loc_code_3B6;
  _data16set(0x8F17, r16[ax]);
  r8[al] = 7;
  sub_2C9A();
loc_code_3DF:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_3DF;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_3DF;
  if ( r16[ax] == _data16get(0x8F0F) ) // jz 
    goto loc_code_3DF;
  if ( r16[ax] == _data16get(0x8F11) ) // jz 
    goto loc_code_3DF;
  if ( r16[ax] == _data16get(0x8F13) ) // jz 
    goto loc_code_3DF;
  if ( r16[ax] == _data16get(0x8F17) ) // jz 
    goto loc_code_3DF;
  _data16set(0x8F19, r16[ax]);
  r8[al] = 5;
  sub_2C9A();
loc_code_40E:
  sub_4F3();
  if ( r16[ax] == _data16get(0x8F15) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F0D) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F0F) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F11) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F13) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F17) ) // jz 
    goto loc_code_40E;
  if ( r16[ax] == _data16get(0x8F19) ) // jz 
    goto loc_code_40E;
  _data16set(0x8F1B, r16[ax]);
  sub_529();
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
  STAT(0x4F3);
  _cld();
loc_code_4F4:
  si = 0x8E8A;
loc_code_4F7:
  tick();
  _lodsb();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_520;
  r16[ax] = si;
  r16[ax] -= 0x8E8B;
  if ( r16[ax] == 0x3B ) // jz 
    goto loc_code_520;
  if ( r16[ax] == 0x3C ) // jz 
    goto loc_code_520;
  if ( r16[ax] == 0x3D ) // jz 
    goto loc_code_520;
  if ( r16[ax] == 0x3E ) // jz 
    goto loc_code_520;
  if ( r16[ax] == 0x2A ) // jz 
    goto loc_code_520;
  if ( r16[ax] == 0x36 ) // jz 
    goto loc_code_520;
  return;
loc_code_520:
  if ( si != 0x8F0A ) // jnz 
    goto loc_code_4F7;
  goto loc_code_4F4;
}
function sub_529()
{
  STAT(0x529);
sub_code_529:
  si = 0x8E8A;
  r8[ah] = 0;
loc_code_52E:
  tick();
  _lodsb();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_535;
  r8[ah] = r8[ah] + 1;
loc_code_535:
  if ( si != 0x8F0A ) // jnz 
    goto loc_code_52E;
  if ( r8[ah] != 0 ) // jnz 
    goto sub_code_529;
}
function sub_541()
{
  STAT(0x541);
  r16[cx] = 0x4E20;
loc_code_544:
  si = 0x8E8A;
  r8[ah] = 0;
  _cld();
loc_code_54A:
  _lodsb();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_557;
  r8[ah] = 1;
  if ( si != _data16get(0x8F0B) ) // jnz 
    goto loc_code_55F;
loc_code_557:
  if ( si == 0x8F0A ) // jz 
    goto loc_code_55F;
  goto loc_code_54A;
loc_code_55F:
  if ( si == _data16get(0x8F0B) ) // jz 
    goto loc_code_578;
  _data16set(0x8F0B, si);
  si -= 0x8E8B;
  r8[al] = _data[ADR(ds, si + 0x5A)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_576;
  if ( (char)(r8[al]-0) >= 0 ) // jns 
    return;
  r8[al] = 0;
  return;
loc_code_576:
  goto loc_code_583;
loc_code_578:
  if ( r8[ah] != 0 ) // jnz 
    goto loc_code_583;
  _data16set(0x8F0B, 0);
loc_code_583:
  if ( --r16[cx] )
    goto loc_code_544;
  r8[al] = 0;
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
  STAT(0x64D);
  _push(di);
  _push(r16[cx]);
  r16[ax] = 0x3D00;
  _int(0x21);
  r16[cx] = _pop();
  r16[dx] = _pop();
  if ( !cf ) // jnb 
    goto loc_code_659;
  return;
loc_code_659:
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
}
function sub_674()
{
  STAT(0x674);
  _push(di);
  _push(r16[cx]);
  r16[cx] = 0;
  r16[ax] = 0x3C00;
  _int(0x21);
  r16[cx] = _pop();
  r16[dx] = _pop();
  if ( !cf ) // jnb 
    goto loc_code_683;
  return;
loc_code_683:
  _data16set(0x8F1E, r16[ax]);
  r16[bx] = r16[ax];
  r16[ax] = 0x4000;
  _int(0x21);
  if ( !cf ) // jnb 
    goto loc_code_690;
  return;
loc_code_690:
  r16[ax] = 0x3E00;
  r16[bx] = _data16get(0x8F1E);
  _int(0x21);
}
function sub_69A()
{
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
loc_code_6C2:
  _lodsb();
  if ( r8[al] == 0x0FF ) // jz 
    goto loc_code_6EB;
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
  goto loc_code_6C2;
loc_code_6EB:
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
loc_code_708:
  r8[bl]--;
  if ( (char) r8[bl] >= 0 ) // jns 
    goto loc_code_72C;
  _lodsb();
  r8[dl] = r8[al];
  r8[dl] &= 0x3F;
  r8[al] &= 0x0C0;
  if ( r8[al] ) // jnz 
    goto loc_code_71A;
  r8[bl] = 0;
  goto loc_code_72C;
loc_code_71A:
  if ( r8[al] != 0x40 ) // jnz 
    goto loc_code_722;
  r8[bl] = 1;
  goto loc_code_72C;
loc_code_722:
  if ( r8[al] != 0x80 ) // jnz 
    goto loc_code_72A;
  r8[bl] = 2;
  goto loc_code_72C;
loc_code_72A:
  r8[bl] = 3;
loc_code_72C:
  _data[di] = r8[dl];
  di = di + 1;
  if ( --r16[cx] )
    goto loc_code_708;
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
loc_code_759:
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
loc_code_786:
  _push(r16[cx]);
  sub_7AF();
  si = 0x274;
  sub_BC5();
  _data16set(0x279, _data16get(0x279) + 0x18);
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_786;
  _data[0x27D] = 8;
  sub_7AF();
  si = 0x274;
  sub_BC5();
  _data16set(0x8F23, _data16get(0x8F23) - 0x10);
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_759;
}
function sub_7AF()
{
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
    goto loc_code_7EC;
  _data16set(0x281, 2);
  goto loc_code_7F2;
loc_code_7EC:
  _data16set(0x281, 4);
loc_code_7F2:
  r16[bx] <<= 1;
  r16[bx] = _data16get(OFS(r16[bx] + 0x5EF));
  _data16set(0x283, r16[bx]);
}
function sub_7FD()
{
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
    goto loc_code_881;
  r8[cl] |= 0x0E0;
loc_code_881:
  r16[dx] = _stack16get(bp + var_2);
  _cld();
loc_code_885:
  if ( r16[dx] == 0 ) // jz 
    goto loc_code_896;
  _lodsb();
  r8[bh] = 0;
  r8[bl] = r8[al];
  r8[cl] += _data[OFS(r16[bx] + 0x571)];
  r16[dx]--;
  goto loc_code_885;
loc_code_896:
  r8[al] = r8[cl];
  _cbw();
  r16[cx] = _pop();
  r16[bx] = _pop();
  if ( r8[cl] & 0x80 ) // jnz 
    goto loc_code_8A6;
  r8[bl] = _data[OFS(r16[bx] + 0x59B)];
  goto loc_code_8AA;
loc_code_8A6:
  r8[bl] = _data[OFS(r16[bx] + 0x5C5)];
loc_code_8AA:
  r8[bh] = 0;
  r16[cx] = _stack16get(bp + var_6);
  r16[cx] = - r16[cx];
  r16[cx] += 0x3F;
  sp = bp;
  bp = _pop();
  _retn(4);
}
function sub_8BA()
{
  STAT(0x8BA);
  // arg_0		= word ptr  4
  _push(bp);
  bp = sp;
  r16[bx] = _stack16get(bp + arg_0);
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] - 0x6DD7));
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_946;
  _push(r16[ax]);
  r8[ah] >>= 1;
  r8[ah] >>= 1;
  r8[bl] = r8[ah];
  r8[bh] = 0;
  r16[bx] <<= 1;
  si = _data16get(OFS(r16[bx] + 0x28B));
  if ( r8[ah] < 0x0F ) // jb 
    goto loc_code_902;
  if ( r8[ah] > 0x14 ) // ja 
    goto loc_code_902;
  r8[ah] -= 0x0F;
  _data[ADR(ds, si + 1)] = r8[ah];
  r8[bl] = r8[ah];
  r8[bh] = 0;
  r8[al] = _data[OFS(r16[bx] - 0x6AD2)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_8F9;
  r16[ax] = _pop();
  goto loc_code_946;
loc_code_8F9:
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x32E));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
loc_code_902:
  _data[ADR(ds, si + 0x13)] = 0x0A;
  r16[ax] = _stack16get(bp + arg_0);
  _data[ADR(ds, si + 0x14)] = r8[al];
  r16[ax] = _pop();
  r16[cx] = 0x0A;
loc_code_910:
  cf = r16[ax] & 1; // cf-insertion
  r16[ax] >>= 1;
  if ( !cf ) // jnb 
    goto loc_code_941;
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
    goto loc_code_932;
  _push(si);
  sub_B58();
  si = _pop();
  goto loc_code_93F;
loc_code_932:
  _push(si);
  sub_B58();
  if ( si == 0 ) // jz 
    goto loc_code_93E;
  sub_A1B();
loc_code_93E:
  si = _pop();
loc_code_93F:
  r16[cx] = _pop();
  r16[ax] = _pop();
loc_code_941:
  _data[ADR(ds, si + 0x13)]--;
  if ( --r16[cx] )
    goto loc_code_910;
loc_code_946:
  bp = _pop();
  _retn(2);
}
function sub_94A()
{
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
loc_code_966:
  if ( r8[dl] == 0 ) // jz 
    goto loc_code_978;
  _lodsb();
  r8[bh] = 0;
  r8[bl] = r8[al];
  r8[cl] += _data[OFS(r16[bx] + 0x571)];
  r8[dl]--;
  goto loc_code_966;
loc_code_978:
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
    goto loc_code_9D9;
  r16[bx] += 0x80;
  goto loc_code_9E1;
loc_code_9D9:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_9E1;
  r16[bx] += 0x100;
loc_code_9E1:
  _data16set(OFS(r16[bx] - 0x6D57), _data16get(OFS(r16[bx] - 0x6D57)) & r16[cx]);
  bp = _pop();
  _retn(6);
}
function sub_9E9()
{
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
    goto loc_code_A07;
  r16[bx] += 0x80;
  goto loc_code_A0F;
loc_code_A07:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_A0F;
  r16[bx] += 0x100;
loc_code_A0F:
  r16[cx] = ~ r16[cx];
  r16[ax] = _data16get(OFS(r16[bx] - 0x6D57));
  r16[ax] &= r16[cx];
  bp = _pop();
  _retn(4);
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
  STAT(0xA51);
  r8[bl] = _data[0x1B9E];
  r8[bh] = 0;
  r16[bx] <<= 1;
  si = r16[bx];
  r8[al] = _data[0x9502];
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_A68;
  si += 0x80;
  goto loc_code_A70;
loc_code_A68:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_A70;
  si += 0x100;
loc_code_A70:
  _ASSERT( ds == 0 );
  r16[ax] = _data16get(ADR(ds, si));
  r16[ax] &= _data16get(OFS(r16[bx] - 0x6DD7));
  //////////// CHEAT MODE ON
  //r16[ax] = 0;
  ////////////
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_AD1;
  r8[bl] = r8[ah];
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bh] = 0;
  r8[cl] = _data[OFS(r16[bx] + 0x2B5)];
  if ( r8[cl] == 0 ) // jz 
    goto loc_code_AD1;
  _data[0x9429] = r8[cl];
  _data16set(0x942C, 0x0A);
  r16[bx] <<= 1;
  r16[dx] = _data16get(OFS(r16[bx] + 0x2CA));
  r16[bx] = _data16get(OFS(r16[bx] + 0x2F4));
  r16[cx] = 0x0A;
loc_code_AA5:
  cf = r16[ax] & 1; // cf-insertion
  r16[ax] >>= 1;
  if ( !cf ) // jnb 
    goto loc_code_AC8;
  _push(r16[bx]);
  r16[bx] -= r16[dx];
  if ( (short)r16[bx] > (short)_data16get(0x1B8F) ) // jg 
    goto loc_code_AC7;
  r16[bx] += r16[dx];
  r16[bx] += r16[dx];
  if ( (short)r16[bx] < (short)_data16get(0x1B8F) ) // jl 
    goto loc_code_AC7;
  r16[ax] = _pop();
  r8[al] = _data[0x9429];
  r8[ah] = 0;
  r16[bx] = _data16get(0x942C);
  return;
loc_code_AC7:
  r16[bx] = _pop();
loc_code_AC8:
  r16[bx] -= 0x18;
  _data16set(0x942C, _data16get(0x942C) -1);
  if ( --r16[cx] )
    goto loc_code_AA5;
loc_code_AD1:
  r16[ax] = 0;
}
function sub_AD5()
{
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
    goto loc_code_AEC;
  si += 0x80;
  goto loc_code_AF4;
loc_code_AEC:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_AF4;
  si += 0x100;
loc_code_AF4:
  r16[ax] = _data16get(ADR(ds, si));
  r16[ax] &= _data16get(OFS(r16[bx] - 0x6DD7));
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_B51;
  r8[bl] = r8[ah];
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bh] = 0;
  r8[cl] = _data[OFS(r16[bx] + 0x2B5)];
  if ( r8[cl] == 0 ) // jz 
    goto loc_code_B51;
  _data16set(0x942C, 0x0A);
  r16[bx] <<= 1;
  r16[dx] = _data16get(OFS(r16[bx] + 0x2CA));
  r16[dx] -= 0x0E;
  r16[bx] = _data16get(OFS(r16[bx] + 0x2F4));
  r16[cx] = 0x0A;
loc_code_B28:
  cf = r16[ax] & 1; // cf-insertion
  r16[ax] >>= 1;
  if ( !cf ) // jnb 
    goto loc_code_B48;
  _push(r16[bx]);
  r16[bx] -= r16[dx];
  if ( (short)r16[bx] > (short)_stack16get(bp + arg_2) ) // jg 
    goto loc_code_B47;
  r16[bx] += r16[dx];
  r16[bx] += r16[dx];
  if ( (short)r16[bx] < (short)_stack16get(bp + arg_2) ) // jl 
    goto loc_code_B47;
  r16[ax] = _pop();
  r16[ax] = 1;
  r16[bx] = _data16get(0x942C);
  goto loc_code_B54;
loc_code_B47:
  r16[bx] = _pop();
loc_code_B48:
  r16[bx] -= 0x18;
  _data16set(0x942C, _data16get(0x942C) -1);
  if ( --r16[cx] )
    goto loc_code_B28;
loc_code_B51:
  r16[ax] = 0;
loc_code_B54:
  bp = _pop();
  _retn(4);
}
function sub_B58()
{
  STAT(0xB58);
  r16[ax] = seg_dseg;
  es = r16[ax];
  di = 0x1B8A;
loc_code_B60:
  r8[al] = _data[di];
  if ( r8[al] & 0x80 ) // jnz 
    goto loc_code_B78;
  if ( r8[al] & 1 ) // jnz 
    goto loc_code_B73;
  _push(di);
  r16[cx] = 0x17;
  _cld();
  _rep_movsb();
  si = _pop();
  return;
loc_code_B73:
  di += 0x17;
  goto loc_code_B60;
loc_code_B78:
  si = 0;
}
function sub_B7C()
{
  STAT(0xB7C);
  si = 0x1B8A;
loc_code_B7F:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    return;
  _data[ADR(ds, si)] = 0;
  si += 0x17;
  goto loc_code_B7F;
}
function sub_B8E()
{
  STAT(0xB8E);
  r16[ax] = _data16get(0x94F8);
  _data16set(0x942E, r16[ax]);
  word_code_D93 = 0x28;
  _data16set(0x9430, 1);
  r16[cx] = 7;
loc_code_BA4:
  si = 0x1B8A;
loc_code_BA7:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    goto loc_code_BC2;
  if ( !(r8[al] & 1) ) // jz 
    goto loc_code_BBD;
  if ( r8[cl] != _data[ADR(ds, si + 2)] ) // jnz 
    goto loc_code_BBD;
  _push(r16[cx]);
  _push(si);
  sub_BDC();
  si = _pop();
  r16[cx] = _pop();
loc_code_BBD:
  si += 0x17;
  goto loc_code_BA7;
loc_code_BC2:
  if ( --r16[cx] )
    goto loc_code_BA4;
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
  STAT(0xC24);
  // arg_0		= word ptr  4
  // arg_2		= word ptr  6
  // arg_4		= word ptr  8
  // arg_6		= word ptr  0Ah
  _push(bp);
  bp = sp;
  r16[ax] = _data16get(0x9430);
  if ( r16[ax] != 0 ) // jnz 
    goto loc_code_C32;
  goto loc_code_CBC;
loc_code_C32:
  r16[ax] = _stack16get(bp + arg_4);
  r16[ax] -= _data16get(0x9528);
  r16[ax] &= 0x3FF;
  if ( !(r16[ax] & 0x200) ) // jz 
    goto loc_code_C44;
  r16[ax] |= 0x0FC00;
loc_code_C44:
  _stack16set(OFS(bp + arg_4), r16[ax]);
  if ( (short)r16[ax] >= (short)0 ) // jge 
    goto loc_code_C77;
  _stack16set(OFS(bp + arg_0), _stack16get(bp + arg_0) + r16[ax]);
  if ( (short) _stack16get(bp + arg_0) >= 0 ) // jns 
    goto loc_code_C54;
  goto loc_code_D8F;
loc_code_C54:
  if ( _stack16get(bp + arg_0) != 0 ) // jnz 
    goto loc_code_C59;
  goto loc_code_D8F;
loc_code_C59:
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
  goto loc_code_C8F;
loc_code_C77:
  r16[ax] += _stack16get(bp + arg_0);
  r16[ax] -= 0x0A0;
  if ( (short) r16[ax] < 0 ) // js 
    goto loc_code_C8F;
  r16[ax] = - r16[ax];
  r16[ax] += _stack16get(bp + arg_0);
  if ( (short)r16[ax] > (short)0 ) // jg 
    goto loc_code_C8C;
  goto loc_code_D8F;
loc_code_C8C:
  _stack16set(OFS(bp + arg_0), r16[ax]);
loc_code_C8F:
  r16[ax] = 0x20;
  _stack16set(OFS(bp + arg_6), _stack16get(bp + arg_6) + r16[ax]);
  r16[ax] = 8;
  _stack16set(OFS(bp + arg_4), _stack16get(bp + arg_4) + r16[ax]);
  r16[ax] = _stack16get(bp + arg_6);
  if ( (short)r16[ax] >= (short)0x20 ) // jge 
    goto loc_code_CAB;
  r16[ax] = 0x20;
  _stack16set(OFS(bp + arg_6), r16[ax]);
  goto loc_code_CBC;
loc_code_CAB:
  r16[ax] += _stack16get(bp + arg_2);
  if ( (short)r16[ax] <= (short)0x120 ) // jle 
    goto loc_code_CBC;
  r16[ax] = 0x120;
  r16[ax] -= _stack16get(bp + arg_2);
  _stack16set(OFS(bp + arg_6), r16[ax]);
loc_code_CBC:
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
    goto loc_code_CE4;
  di = r16[bx];
  goto loc_code_CE7;
loc_code_CE4:
  di = 0;
loc_code_CE7:
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
loc_code_D13:
  _ASSERT( r16[bx] < 200 && r16[cx] < 200 );
  _push(r16[ax]);
  _push(r16[bx]);
  _push(r16[cx]);
  _push(di);
  _push(si);
loc_code_D18:
  r8[bh] = byte_code_D96;
loc_code_D1D:
  r8[bl] = _data[ADR(ds, si)];
  si = si + 1;
  if ( r8[bh] != r8[bl] ) // jnz 
    goto loc_code_D3A;
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_D2F;
  r8[ah] = 0x40;
  di = di + 1;
  if ( --r16[cx] )
    goto loc_code_D1D;
  goto loc_code_D6D;
loc_code_D2F:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_D36;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_D36:
  if ( --r16[cx] )
    goto loc_code_D1D;
  goto loc_code_D6D;
loc_code_D3A:
  r8[bh] = r8[bl];
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  if ( r8[bl] == byte_code_D95 ) // jz 
    goto loc_code_D4F;
  _out(r16[dx], r16[ax]);
  _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bl]);
loc_code_D4F:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_D56;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_D56:
  r8[bh] &= 0x0F;
  if ( r8[bh] == byte_code_D95 ) // jz 
    goto loc_code_D64;
  _out(r16[dx], r16[ax]);
  _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bh]);
loc_code_D64:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_D6B;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_D6B:
  if ( --r16[cx] )
    goto loc_code_D18;
loc_code_D6D:
  si = _pop();
  si += 0x0A0;
  di = _pop();
  di += word_code_D93;
  di &= 0x7FFF;
  r16[cx] = _pop();
  r16[bx] = _pop();
  r16[ax] = _pop();
  r16[bx]--;
  if ( r16[bx] ) // jnz 
    goto loc_code_D13;
  ds = _pop();
  r16[ax] = 0x0FF08;
  _out(r16[dx], r16[ax]);
  r16[ax] = 5;
  _out(r16[dx], r16[ax]);
  r16[ax] = 0x0F07;
  _out(r16[dx], r16[ax]);
loc_code_D8F:
  bp = _pop();
  _retn(8);
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
  STAT(0xDC0);
  _data[0x94FE] = _data[0x94FE] + 1;
  r8[al] = _data[0x94FE];
  if ( r8[al] < 6 ) // jb 
    goto loc_code_DD3;
  _data16set(0x94FC, 0x30);
  goto loc_code_DE5;
loc_code_DD3:
  if ( r8[al] < 3 ) // jb 
    goto loc_code_DDF;
  _data16set(0x94FC, 0x20);
  goto loc_code_DE5;
loc_code_DDF:
  _data16set(0x94FC, 0x10);
loc_code_DE5:
  _data[0x9501] = _data[0x9501] + 1;
  r8[al] = _data[0x9501];
  if ( r8[al] <= 7 ) // jbe 
    goto loc_code_DF5;
  _data[0x9501] = 1;
loc_code_DF5:
  sub_9A4();
  sub_69A();
  _data[0x9519] = 0;
  sub_E3D();
  sub_2A7F();
}
function sub_E07()
{
  STAT(0xE07);
  r16[ax] = _data16get(0x9534);
  if ( r16[ax] != 0 ) // jnz 
    goto loc_code_E15;
  _data[0x9500] = 1;
  return;
loc_code_E15:
  sub_2329();
  r8[al] = _data[0x9502];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_E27;
  _data[0x9502] = 0;
  sub_69A();
loc_code_E27:
  sub_2200();
  _data[0x9519] = 1;
  _data[0x951A] = 0;
  _data[0x951B] = 0;
  sub_E3D();
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
  STAT(0xE84);
  r8[al] = _data[0x950E];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_E93;
  _data[0x950E] = 0;
  sub_69A();
loc_code_E93:
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
loc_code_EC2:
  _push(r16[cx]);
  _push(r16[ax]);
  _push(r16[ax]);
  sub_8BA();
  r16[ax] = _pop();
  r16[cx] = _pop();
  r16[ax] = r16[ax] + 1;
  r16[ax] &= 0x3F;
  if ( --r16[cx] )
    goto loc_code_EC2;
  r8[al] = _data[0x9432];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_EEA;
  si = 0x1B8A;
  r16[bx] = 0x0D49;
  _data[ADR(ds, si + 4)] = 0x0A;
  sub_2121();
  _data[0x1B9C] = 0x23;
  return;
loc_code_EEA:
  r8[al] = _data[0x9519];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_F08;
  _data[0x9519] = 0;
  si = 0x0DA2;
  r16[ax] = _data16get(0x1B91);
  _data16set(ADR(ds, si + 7), r16[ax]);
  r8[al] = _data[0x1B8D];
  _data[ADR(ds, si + 3)] = r8[al];
  sub_B58();
loc_code_F08:
  sub_F9D();
  r8[al] = _data[0x951A];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_F23;
  _data[0x951A] = 1;
  si = 0x0DC3;
  _data[ADR(ds, si)] &= 0x0DF;
  sub_1CD9();
  sub_B58();
loc_code_F23:
  r8[al] = _data[0x951B];
  if ( r8[al] == 0 ) // jz 
    return;
  _data[0x951B] = 1;
  si = 0x0DC3;
  _data[ADR(ds, si)] |= 0x20;
  sub_1CD9();
  sub_B58();
}
function sub_F3C()
{
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
    goto loc_code_F84;
  _data[0x951A] = 1;
  si = 0x0D1B;
  _data[ADR(ds, si)] &= 0x0DF;
  sub_2F50();
  sub_B58();
loc_code_F84:
  r8[al] = _data[0x951B];
  if ( r8[al] == 0 ) // jz 
    return;
  _data[0x951B] = 1;
  si = 0x0D1B;
  _data[ADR(ds, si)] |= 0x20;
  sub_2F50();
  sub_B58();
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
sub_code_FDA:
  STAT(0xFDA);
  r8[al] = _data[0x94FF];
  _data[0x9509] = r8[al];
  si = 0x1B8A;
loc_code_FE3:
  r8[al] = _data[0x9513];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_FF5;
  sub_E07();
  r8[al] = _data[0x9500];
  if ( r8[al] == 0 ) // jz 
    goto sub_code_FDA;
  return;
loc_code_FF5:
  r8[al] = _data[0x94FF];
  if ( r8[al] == _data[0x9509] ) // jz 
    goto loc_code_1036;
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_100E;
  r8[al] = 0x0B;
  sub_3840();
  sub_F3C();
  goto sub_code_FDA;
  goto loc_code_1036;
loc_code_100E:
  r8[al] = 0x0B;
  sub_3840();
  r8[al] = _data[0x951D];
  if ( r8[al] != 0x0F0 ) // jnz 
    goto loc_code_101F;
  sub_DC0();
  goto loc_code_1034;
loc_code_101F:
  r8[al] = _data[0x1BA0];
  r8[al] &= 0x7F;
  if ( r8[al] <= 0x28 ) // jbe 
    goto loc_code_1031;
  if ( r8[al] >= 0x58 ) // jnb 
    goto loc_code_1031;
  _data[0x9432] = 1;
loc_code_1031:
  sub_E84();
loc_code_1034:
  goto sub_code_FDA;
loc_code_1036:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    return;
  if ( !(r8[al] & 2) ) // jz 
    goto loc_code_1054;
  _push(si);
  r8[bl] = _data[ADR(ds, si + 0x12)];
  if ( r8[bl] == 0 ) // jz 
    goto loc_code_1053;
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
  default:
	  _ASSERT(0);
  }

loc_code_1053:
  si = _pop();
loc_code_1054:
  si += 0x17;
  goto loc_code_FE3;
}
function sub_10A0()
{
  STAT(0x10A0);
  r8[al] = _data[ADR(ds, si + 0x0A)];
  r8[al] -= _data[ADR(ds, si + 3)];
  r8[al] -= _data[ADR(ds, si + 0x0C)];
  _cbw();
  r16[ax] += _data16get(ADR(ds, si + 7));
  r16[ax] &= 0x3FF;
  r16[bx] = _data16get(0x9528);
  if ( r16[ax] >= r16[bx] ) // jnb 
    goto loc_code_10BB;
  r16[ax] += 0x400;
loc_code_10BB:
  r16[ax] -= r16[bx];
  if ( r16[ax] <= 0x200 ) // jbe 
    return;
  _data[ADR(ds, si)] = 0;
}
function sub_10C6()
{
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
    goto loc_code_10E8;
  r16[ax] += 0x400;
loc_code_10E8:
  r16[ax] -= r16[bx];
  if ( r16[ax] >= 0x200 ) // jnb 
    return;
  _data[ADR(ds, si)] = 0;
}
function sub_10F3()
{
  STAT(0x10F3);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  if ( r8[al] <= 8 ) // jbe 
    goto loc_code_10FF;
  r8[al] = 8;
loc_code_10FF:
  r8[ah] = 0;
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - r16[ax]);
  sub_10A0();
}
function sub_1108()
{
  STAT(0x1108);
  sub_1B80();
  sub_1BB9();
  r16[bx] = _data16get(0x954C);
  r16[ax] = _data16get(0x952C);
  if ( !(r8[bl] & 1) ) // jz 
    goto loc_code_1131;
  r16[ax] -= 1;
  if ( (short) r16[ax] < 0 ) // js 
    goto loc_code_1127;
  if ( (short)r16[ax] <= (short)4 ) // jle 
    goto loc_code_1127;
  r16[ax] = 4;
loc_code_1127:
  if ( (short)r16[ax] >= (short)0x0FFE8 ) // jge 
    goto loc_code_112F;
  r16[ax] = 0x0FFE8;
loc_code_112F:
  goto loc_code_1158;
loc_code_1131:
  if ( !(r8[bl] & 2) ) // jz 
    goto loc_code_114D;
  r16[ax] += 1;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1143;
  if ( (short)r16[ax] >= (short)0x0FFFC ) // jge 
    goto loc_code_1143;
  r16[ax] = 0x0FFFC;
loc_code_1143:
  if ( (short)r16[ax] <= (short)0x18 ) // jle 
    goto loc_code_114B;
  r16[ax] = 0x18;
loc_code_114B:
  goto loc_code_1158;
loc_code_114D:
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_1158;
  if ( (short)r16[ax] <= (short)0 ) // jle 
    goto loc_code_1157;
  r16[ax]--;
  goto loc_code_1158;
loc_code_1157:
  r16[ax] = r16[ax] + 1;
loc_code_1158:
  _data16set(0x952C, r16[ax]);
  r16[ax] += 3;
  r16[ax] = _sar16(r16[ax]);
  r16[ax] = _sar16(r16[ax]);
  //unknown_command(); // sar	ax, 1
  //unknown_command(); // sar	ax, 1
  r16[ax] += _data16get(0x1B8F);
  if ( (short)r16[ax] >= (short)0x14 ) // jge 
    goto loc_code_1174;
  r16[ax] = 0x14;
  _data16set(0x952C, 0);
loc_code_1174:
  if ( (short)r16[ax] <= (short)0x0EC ) // jle 
    goto loc_code_1182;
  r16[ax] = 0x0EC;
  _data16set(0x952C, 0);
loc_code_1182:
  _data16set(0x1B8F, r16[ax]);
  r8[al] = _data[0x1B8E];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_118F;
  sub_1B57();
loc_code_118F:
  sub_1C78();
  sub_A51();
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_119F;
  sub_1C56();
  goto loc_code_11BC;
loc_code_119F:
  _data[0x1B9E] = _data[0x1B9E] + 1;
  _data[0x1B9E] &= 0x3F;
  sub_A51();
//  r16[ax] = 0;					// CLEAR HIT TEST ----- TODO!
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_11B3;
  // hit - test
  sub_1C56();
loc_code_11B3:
  _data[0x1B9E]--;
  _data[0x1B9E] &= 0x3F;
loc_code_11BC:
  r16[ax] = _data16get(0x9542);
  if ( (short)r16[ax] > (short)0 ) // jg 
    goto loc_code_11C8;
  sub_1C33();
  return;
loc_code_11C8:
  r8[al] = _data[0x1B8E];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_11DE;
  _data[0x9515] = _data[0x9515] + 1;
  r8[al] = _data[0x9515];
  if ( r8[al] < 4 ) // jb 
    return;
  sub_1C33();
  return;
loc_code_11DE:
  r16[ax] = _data16get(0x953E);
  if ( (short)r16[ax] <= (short)0 ) // jle 
    goto loc_code_11F0;
  r16[ax] = _data16get(0x954C);
  if ( !(r8[al] & 0x80) ) // jz 
    goto loc_code_11F0;
  sub_1D1E();
loc_code_11F0:
  r16[ax] = _data16get(0x954C);
  r8[bl] = _data[0x951A];
  if ( !(r8[al] & 0x40) ) // jz 
    goto loc_code_1235;
  if ( r8[bl] != 0 ) // jnz 
    goto loc_code_1224;
  r16[ax] = _data16get(0x9536);
  if ( r16[ax] <= 0 ) // jbe 
    goto loc_code_1222;
  _data[0x951A] = 1;
  si = 0x0DC3;
  _data[ADR(ds, si)] &= 0x0DF;
  sub_1CD9();
  sub_B58();
  _data16set(0x9538, _data16get(0x9538) -1);
  r8[al] = 1;
  sub_3840();
loc_code_1222:
  goto loc_code_1233;
loc_code_1224:
  if ( r8[bl] != 2 ) // jnz 
    goto loc_code_1233;
  _data[0x951A] = 3;
  r8[al] = 2;
  sub_3840();
loc_code_1233:
  goto loc_code_124B;
loc_code_1235:
  if ( r8[bl] != 1 ) // jnz 
    goto loc_code_1241;
  _data[0x951A] = 2;
  goto loc_code_124B;
loc_code_1241:
  if ( r8[bl] != 3 ) // jnz 
    goto loc_code_124B;
  _data[0x951A] = 0;
loc_code_124B:
  r16[ax] = _data16get(0x954C);
  r8[bl] = _data[0x951B];
  if ( !(r8[al] & 0x20) ) // jz 
    goto loc_code_1290;
  if ( r8[bl] != 0 ) // jnz 
    goto loc_code_127F;
  r16[ax] = _data16get(0x9536);
  if ( r16[ax] <= 0 ) // jbe 
    goto loc_code_127D;
  _data[0x951B] = 1;
  si = 0x0DC3;
  _data[ADR(ds, si)] |= 0x20;
  sub_1CD9();
  sub_B58();
  _data16set(0x9538, _data16get(0x9538) -1);
  r8[al] = 1;
  sub_3840();
loc_code_127D:
  goto loc_code_128E;
loc_code_127F:
  if ( r8[bl] != 2 ) // jnz 
    goto loc_code_128E;
  _data[0x951B] = 3;
  r8[al] = 2;
  sub_3840();
loc_code_128E:
  return;
loc_code_1290:
  if ( r8[bl] != 1 ) // jnz 
    goto loc_code_129C;
  _data[0x951B] = 2;
  return;
loc_code_129C:
  if ( r8[bl] != 3 ) // jnz 
    return;
  _data[0x951B] = 0;
}
function sub_12A7()
{
  STAT(0x12A7);
  r16[ax] = _data16get(0x952A);
  r16[ax] -= 3;
  if ( (short) r16[ax] < 0 ) // js 
    goto loc_code_12B4;
  _data16set(0x952A, r16[ax]);
  goto loc_code_12B7;
loc_code_12B4:
  sub_1C33();
loc_code_12B7:
  sub_1BB9();
  sub_1B57();
  si = 0x1B8A;
  r16[bx] = 0x0D49;
  _data[ADR(ds, si + 4)] = 0x0A;
  sub_2121();
}
function sub_12CB()
{
  STAT(0x12CB);
  r16[ax] = _data16get(0x952A);
  r16[ax]--;
  if ( (short) r16[ax] < 0 ) // js 
    goto loc_code_12D4;
  _data16set(0x952A, r16[ax]);
loc_code_12D4:
  sub_1BB9();
  sub_1B57();
  _data[0x9514] = _data[0x9514] + 1;
  r8[al] = _data[0x9514];
  if ( r8[al] < 0x28 ) // jb 
    return;
  _data[0x9513] = 1;
}
function sub_12EB()
{
  STAT(0x12EB);
  sub_10A0();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_12F5;
  return;
loc_code_12F5:
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) - 0x10);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  r8[al] = _data[ADR(ds, si + 4)];
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_1312;
  r8[al] = _data[ADR(ds, si + 3)];
  if ( (char)r8[al] <= (char)0x9C ) // jle 
    goto loc_code_1310;
  _data[ADR(ds, si + 3)] -= 8;
loc_code_1310:
  goto loc_code_1321;
loc_code_1312:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_1321;
  r8[al] = _data[ADR(ds, si + 3)];
  if ( (char)r8[al] >= (char)0x64 ) // jge 
    goto loc_code_1321;
  _data[ADR(ds, si + 3)] += 8;
loc_code_1321:
  _push(si);
  r16[ax] = _data16get(ADR(ds, si + 5));
  _push(r16[ax]);
  r16[ax] = _data16get(ADR(ds, si + 7));
  _push(r16[ax]);
  sub_7FD();
  si = _pop();
  if ( (char)r8[al] < (char)_data[ADR(ds, si + 3)] ) // jl 
    goto loc_code_1338;
  sub_2092();
  return;
loc_code_1338:
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
    goto loc_code_1382;
  r16[bx] = _pop();
  _push(r16[bx]);
  r8[al] = _data[ADR(ds, si + 3)];
  r8[al] -= _data[OFS(r16[bx] + 3)];
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_1367;
  r8[al] = - r8[al];
loc_code_1367:
  if ( r8[al] >= 0x10 ) // jnb 
    goto loc_code_1382;
  _data[ADR(ds, si + 0x15)]--;
  if ( (char)_data[ADR(ds, si + 0x15)] >= 0 ) // jns 
    goto loc_code_137A;
  sub_20DB();
  r8[al] = 6;
  sub_3840();
  goto loc_code_137D;
loc_code_137A:
  sub_2662();
loc_code_137D:
  si = _pop();
  _push(si);
  sub_2047();
loc_code_1382:
  si = _pop();
}
function sub_1384()
{
  STAT(0x1384);
  r8[al] = _data[0x1B9C];
  if ( r8[al] != 0x11 ) // jnz 
    goto loc_code_138E;
  _data[ADR(ds, si)] = 0;
loc_code_138E:
  sub_1CD9();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x20 ) // jnz 
    goto loc_code_139C;
  r8[al] = _data[0x951A];
  goto loc_code_139F;
loc_code_139C:
  r8[al] = _data[0x951B];
loc_code_139F:
  if ( r8[al] != 3 ) // jnz 
    return;
  _data[ADR(ds, si + 0x12)] = 0x19;
}
function sub_13A8()
{
  STAT(0x13A8);
  sub_10A0();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_13B2;
  return;
loc_code_13B2:
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
    goto loc_code_13F5;
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  _data[ADR(ds, si + 0x15)]--;
  if ( (char)_data[ADR(ds, si + 0x15)] >= 0 ) // jns 
    goto loc_code_13F5;
  sub_20F0();
  _data[ADR(ds, si)] = 0;
  return;
loc_code_13F5:
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
    goto loc_code_1427;
  sub_20DB();
  r8[al] = 6;
  sub_3840();
  si = _pop();
  _push(si);
  _data[ADR(ds, si)] = 0;
loc_code_1427:
  si = _pop();
}
function sub_1429()
{
  STAT(0x1429);
  sub_10C6();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1433;
  return;
loc_code_1433:
  r8[al] = _data[ADR(ds, si + 1)];
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_1440;
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 5);
  goto loc_code_146A;
loc_code_1440:
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_144A;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 5);
  goto loc_code_146A;
loc_code_144A:
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_1458;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 3);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 2);
  goto loc_code_146A;
loc_code_1458:
  if ( r8[al] != 3 ) // jnz 
    goto loc_code_1466;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 3);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 2);
  goto loc_code_146A;
loc_code_1466:
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 5);
loc_code_146A:
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  r16[ax] = _data16get(ADR(ds, si + 5));
  if ( (short)r16[ax] >= (short)0x0C ) // jge 
    goto loc_code_147B;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_147B:
  if ( (short)r16[ax] <= (short)0x0F4 ) // jle 
    goto loc_code_1484;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1484:
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
    goto loc_code_14B2;
  return;
loc_code_14B2:
  r16[ax] = _data16get(ADR(ds, si + 5));
  r16[ax] -= _data16get(0x1B8F);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_14BD;
  r16[ax] = - r16[ax];
loc_code_14BD:
  if ( r16[ax] >= 0x10 ) // jnb 
    return;
  r16[ax] = _data16get(ADR(ds, si + 7));
  r16[ax] -= _data16get(0x1B91);
  r16[ax] -= 8;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_14D0;
  r16[ax] = - r16[ax];
loc_code_14D0:
  if ( r16[ax] >= 0x10 ) // jnb 
    return;
  r8[al] = 5;
  sub_3840();
  _data16set(0x9544, _data16get(0x9544) - 0x64);
  _data[0x12A0] = 1;
  sub_20F0();
  _data[0x12A0] = 5;
  _data[ADR(ds, si)] = 0;
}
function sub_14F0()
{
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
    goto loc_code_1548;
  r16[ax] = _data16get(ADR(ds, si + 5));
  r16[ax] -= _data16get(0x1B8F);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_152A;
  r16[ax] = - r16[ax];
loc_code_152A:
  if ( r16[ax] >= 0x1A ) // jnb 
    goto loc_code_1548;
  r16[ax] = _data16get(ADR(ds, si + 7));
  r16[ax] -= _data16get(0x1B91);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_153A;
  r16[ax] = - r16[ax];
loc_code_153A:
  if ( r16[ax] >= 0x12 ) // jnb 
    goto loc_code_1548;
  _data16set(0x9544, _data16get(0x9544) - 0x0C);
  _data[ADR(ds, si + 0x15)] = 0x0FF;
loc_code_1548:
  di = 0x1BA1;
loc_code_154B:
  r8[al] = _data[ADR(ds, si + 0x15)];
  if ( (char)r8[al] >= (char)0 ) // jge 
    goto loc_code_1561;
  r8[al] = 7;
  sub_3840();
  sub_20F0();
  _data[ADR(ds, si)] = 0;
  sub_2676();
  return;
loc_code_1561:
  r8[al] = _data[di];
  if ( r8[al] & 0x80 ) // jnz 
    goto loc_code_15C0;
  if ( !(r8[al] & 0x40) ) // jz 
    goto loc_code_15BB;
  _push(di);
  r16[ax] = _data16get(OFS(di + 5));
  r16[ax] -= _data16get(ADR(ds, si + 5));
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1576;
  r16[ax] = - r16[ax];
loc_code_1576:
  if ( r16[ax] >= 0x14 ) // jnb 
    goto loc_code_15BA;
  r16[ax] = _data16get(OFS(di + 7));
  r16[ax] -= _data16get(ADR(ds, si + 7));
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1585;
  r16[ax] = - r16[ax];
loc_code_1585:
  if ( r16[ax] >= 0x10 ) // jnb 
    goto loc_code_15BA;
  r8[al] = _data[OFS(di + 0x12)];
  if ( r8[al] != 0x19 ) // jnz 
    goto loc_code_159A;
  _data[ADR(ds, si + 0x15)] = 0x0FF;
  _data[di] = 0;
  goto loc_code_15BA;
loc_code_159A:
  r8[al] = _data[OFS(di + 3)];
  r8[al] -= _data[ADR(ds, si + 3)];
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_15A4;
  r8[al] = - r8[al];
loc_code_15A4:
  if ( r8[al] >= 0x10 ) // jnb 
    goto loc_code_15BA;
  _data[ADR(ds, si + 0x15)]--;
  _push(si);
  si = di;
  sub_2092();
  r8[al] = 3;
  sub_3840();
  sub_2662();
  si = _pop();
loc_code_15BA:
  di = _pop();
loc_code_15BB:
  di += 0x17;
  goto loc_code_154B;
loc_code_15C0:
  r8[al] = _data[0x1B9C];
  if ( r8[al] == 0x11 ) // jz 
    goto loc_code_15F8;
  r16[ax] = _data16get(0x1B91);
  if ( r16[ax] <= _data16get(ADR(ds, si + 7)) ) // jbe 
    goto loc_code_15F8;
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_15D9;
  r16[ax] = - r16[ax];
loc_code_15D9:
  if ( r16[ax] >= 0x20 ) // jnb 
    goto loc_code_15F8;
  _data[ADR(ds, si + 0x16)]--;
  if ( (char)_data[ADR(ds, si + 0x16)] >= 0 ) // jns 
    goto loc_code_15EE;
  _data[ADR(ds, si + 0x16)] = 7;
  _data[0x9518] = 1;
  goto loc_code_15F3;
loc_code_15EE:
  _data[0x9518] = 0;
loc_code_15F3:
  _push(si);
  sub_1DEF();
  si = _pop();
loc_code_15F8:
  sub_10C6();
}
function sub_15FC()
{
  STAT(0x15FC);
  sub_10C6();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1606;
  return;
loc_code_1606:
  r8[al] = _data[ADR(ds, si + 1)];
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_1613;
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 8);
  goto loc_code_163D;
loc_code_1613:
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_161D;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 8);
  goto loc_code_163D;
loc_code_161D:
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_162B;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 6);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
  goto loc_code_163D;
loc_code_162B:
  if ( r8[al] != 3 ) // jnz 
    goto loc_code_1639;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 6);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 4);
  goto loc_code_163D;
loc_code_1639:
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 8);
loc_code_163D:
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  r16[ax] = _data16get(ADR(ds, si + 5));
  if ( (short)r16[ax] >= (short)4 ) // jge 
    goto loc_code_164E;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_164E:
  if ( (short)r16[ax] <= (short)0x0FC ) // jle 
    goto loc_code_1657;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1657:
  r8[al] = _data[ADR(ds, si + 4)];
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_166B;
  r8[al] = _data[ADR(ds, si + 3)];
  if ( (char)r8[al] >= (char)0x64 ) // jge 
    goto loc_code_1669;
  _data[ADR(ds, si + 3)] += 4;
loc_code_1669:
  goto loc_code_167A;
loc_code_166B:
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_167A;
  r8[al] = _data[ADR(ds, si + 3)];
  if ( (char)r8[al] <= (char)0x9C ) // jle 
    goto loc_code_167A;
  _data[ADR(ds, si + 3)] -= 4;
loc_code_167A:
  _push(si);
  r16[ax] = _data16get(ADR(ds, si + 5));
  _push(r16[ax]);
  r16[ax] = _data16get(ADR(ds, si + 7));
  _push(r16[ax]);
  sub_7FD();
  si = _pop();
  if ( (char)r8[al] < (char)_data[ADR(ds, si + 3)] ) // jl 
    goto loc_code_1691;
  sub_2092();
  return;
loc_code_1691:
  r8[al] = _data[0x1B9C];
  if ( r8[al] != 0x11 ) // jnz 
    goto loc_code_1699;
  return;
loc_code_1699:
  r16[ax] = _data16get(ADR(ds, si + 5));
  r16[ax] -= _data16get(0x1B8F);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_16A4;
  r16[ax] = - r16[ax];
loc_code_16A4:
  if ( r16[ax] >= 0x0C ) // jnb 
    return;
  r16[ax] = _data16get(ADR(ds, si + 7));
  r16[ax] -= _data16get(0x1B91);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_16B4;
  r16[ax] = - r16[ax];
loc_code_16B4:
  if ( r16[ax] >= 8 ) // jnb 
    return;
  r8[al] = _data[ADR(ds, si + 3)];
  r8[al] -= _data[0x1B8D];
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_16C4;
  r8[al] = - r8[al];
loc_code_16C4:
  if ( r8[al] >= 0x10 ) // jnb 
    return;
  _data16set(0x9544, _data16get(0x9544) - 1);
  sub_2092();
  r8[al] = 4;
  sub_3840();
}
function sub_16D6()
{
  STAT(0x16D6);
  _data[ADR(ds, si + 4)]--;
  if ( (char)_data[ADR(ds, si + 4)] >= 0 ) // jns 
    return;
  _data[ADR(ds, si)] = 0;
}
function sub_16DF()
{
  STAT(0x16DF);
  r8[al] = _data[ADR(ds, si + 4)];
  _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
  if ( r8[al] < 4 ) // jb 
    goto loc_code_16ED;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_16ED:
  r8[al] <<= 1;
  r8[bl] = r8[al];
  r8[bh] = 0;
  r16[ax] = _data16get(OFS(r16[bx] + 0x143E));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
  sub_10C6();
}
function sub_16FE()
{
  STAT(0x16FE);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  r8[al] >>= 1;
  r8[al] >>= 1;
  r8[al] &= 7;
  if ( (char)r8[al] < (char)5 ) // jl 
    goto loc_code_1712;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1712:
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x12B5;
  sub_2121();
  sub_10C6();
}
function sub_171F()
{
  STAT(0x171F);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  r8[al] >>= 1;
  r8[al] >>= 1;
  r8[al] &= 7;
  if ( (char)r8[al] < (char)6 ) // jl 
    goto loc_code_1733;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1733:
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x12F5;
  sub_2121();
  sub_10C6();
}
function sub_1740()
{
  STAT(0x1740);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  r8[al] &= 7;
  if ( (char)r8[al] < (char)4 ) // jl 
    goto loc_code_1762;
  r8[al] = _data[ADR(ds, si)];
  if ( !(r8[al] & 0x20) ) // jz 
    goto loc_code_1759;
  _data[0x9517] &= 0x7F;
  goto loc_code_175E;
loc_code_1759:
  _data[0x9517] &= 0x0FE;
loc_code_175E:
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1762:
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x133D;
  sub_2121();
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
  STAT(0x1783);
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[al] = _data[ADR(ds, si + 0x16)];
  r8[al] >>= 1;
  r8[al] &= 7;
  if ( r8[al] < 6 ) // jb 
    goto loc_code_1797;
  r8[al] = 0;
  _data[ADR(ds, si + 0x16)] = 0;
loc_code_1797:
  r8[bl] = r8[al];
  r8[bh] = 0;
  r8[al] = _data[OFS(r16[bx] + 0x0E4C)];
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x0E52;
  sub_2121();
  sub_10C6();
}
function sub_17AC()
{
  STAT(0x17AC);
  sub_215B();
  if ( r16[cx] == 0 ) // jz 
    goto loc_code_17CC;
  _data[ADR(ds, si + 0x16)]--;
  if ( (char)_data[ADR(ds, si + 0x16)] >= 0 ) // jns 
    goto loc_code_17C4;
  _data[ADR(ds, si + 0x16)] = 8;
  _data[0x9518] = 1;
  goto loc_code_17C9;
loc_code_17C4:
  _data[0x9518] = 0;
loc_code_17C9:
  sub_1F0B();
loc_code_17CC:
  r16[bx] = 0x0E73;
  sub_2121();
  sub_10C6();
}
function sub_17D6()
{
  STAT(0x17D6);
  sub_215B();
  if ( r16[cx] == 0 ) // jz 
    goto loc_code_17EA;
  _data[ADR(ds, si + 0x16)]--;
  if ( (char)_data[ADR(ds, si + 0x16)] >= 0 ) // jns 
    goto loc_code_17EA;
  _data[ADR(ds, si + 0x16)] = 0x12;
  sub_2005();
loc_code_17EA:
  r16[bx] = 0x0E9C;
  sub_2121();
  sub_10C6();
}
function sub_17F4()
{
  STAT(0x17F4);
  sub_10C6();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_17FE;
  return;
loc_code_17FE:
  r8[al] = _data[ADR(ds, si + 1)];
  if ( r8[al] != 2 ) // jnz 
    goto loc_code_180B;
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
  goto loc_code_1835;
loc_code_180B:
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1815;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 4);
  goto loc_code_1835;
loc_code_1815:
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_1823;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 4);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
  goto loc_code_1835;
loc_code_1823:
  if ( r8[al] != 3 ) // jnz 
    goto loc_code_1831;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 4);
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) + 3);
  goto loc_code_1835;
loc_code_1831:
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 4);
loc_code_1835:
  _data16set(ADR(ds, si + 7), _data16get(ADR(ds, si + 7)) & 0x3FF);
  r16[ax] = _data16get(ADR(ds, si + 5));
  if ( (short)r16[ax] >= (short)8 ) // jge 
    goto loc_code_1846;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_1846:
  if ( (short)r16[ax] <= (short)0x0F8 ) // jle 
    goto loc_code_184F;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_184F:
  _data[ADR(ds, si + 0x16)] = _data[ADR(ds, si + 0x16)] + 1;
  r8[bl] = _data[ADR(ds, si + 0x16)];
  if ( r8[bl] < 0x10 ) // jb 
    goto loc_code_185E;
  sub_2099();
  return;
loc_code_185E:
  r8[bh] = 0;
  r8[al] = _data[OFS(r16[bx] + 0x1467)];
  _data8set(ADR(ds, si + 3), _data8get(ADR(ds, si + 3)) + r8[al]);
  r8[al] = _data[0x1B9C];
  if ( r8[al] != 0x11 ) // jnz 
    goto loc_code_186F;
  return;
loc_code_186F:
  r16[ax] = _data16get(ADR(ds, si + 5));
  r16[ax] -= _data16get(0x1B8F);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_187A;
  r16[ax] = - r16[ax];
loc_code_187A:
  if ( r16[ax] >= 0x0E ) // jnb 
    return;
  r16[ax] = _data16get(ADR(ds, si + 7));
  r16[ax] -= _data16get(0x1B91);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_188A;
  r16[ax] = - r16[ax];
loc_code_188A:
  if ( r16[ax] >= 0x0A ) // jnb 
    return;
  r8[al] = _data[ADR(ds, si + 3)];
  r8[al] -= _data[0x1B8D];
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_189A;
  r8[al] = - r8[al];
loc_code_189A:
  if ( r8[al] >= 0x10 ) // jnb 
    return;
  _data16set(0x9544, _data16get(0x9544) - 0x0A);
  r8[al] = 5;
  sub_3840();
}
function sub_18A9()
{
  STAT(0x18A9);
  sub_215B();
  if ( r16[cx] == 0 ) // jz 
    goto loc_code_18BD;
  _data[ADR(ds, si + 0x16)]--;
  if ( (char)_data[ADR(ds, si + 0x16)] >= 0 ) // jns 
    goto loc_code_18BD;
  _data[ADR(ds, si + 0x16)] = 0x28;
  sub_1FBA();
loc_code_18BD:
  r16[bx] = 0x0EC5;
  sub_2121();
  sub_10C6();
}
function sub_18C7()
{
  STAT(0x18C7);
  r8[al] = _data[0x952E];
  r8[al] &= _data[0x952F];
  r8[al] &= _data[0x9530];
  r8[al] &= _data[0x9531];
  r8[al] &= _data[0x9532];
  r8[al] &= _data[0x9533];
  if ( r8[al] ) // jnz 
    goto loc_code_18E4;
  sub_10C6();
  return;
loc_code_18E4:
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  r16[ax] -= 0x0C;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_18F1;
  r16[ax] = - r16[ax];
loc_code_18F1:
  r16[cx] = _data16get(0x1B91);
  r16[cx] -= 8;
  r16[cx] -= _data16get(ADR(ds, si + 7));
  if ( (short) r16[cx] >= 0 ) // jns 
    goto loc_code_18FF;
  r16[cx] = - r16[cx];
loc_code_18FF:
  r8[bl] = _data[ADR(ds, si + 4)];
  r8[bl] >>= 1;
  r16[ax] += r16[cx];
  if ( r16[ax] > 0x40 ) // ja 
    goto loc_code_1915;
  if ( r8[bl] == 8 ) // jz 
    goto loc_code_1913;
  _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
loc_code_1913:
  goto loc_code_191D;
loc_code_1915:
  if ( r8[bl] == 0 ) // jz 
    goto loc_code_191D;
  _data[ADR(ds, si + 4)]--;
loc_code_191D:
  _push(r16[bx]);
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x1483));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
  r16[bx] = _pop();
  if ( r8[bl] < 2 ) // jb 
    goto loc_code_196B;
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  r16[ax] -= 0x0C;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1947;
  r16[ax] = - r16[ax];
  if ( r16[ax] > 0x18 ) // ja 
    goto loc_code_1945;
  _data16set(0x1B8F, _data16get(0x1B8F) + 1);
loc_code_1945:
  goto loc_code_1952;
loc_code_1947:
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_1952;
  if ( r16[ax] > 0x18 ) // ja 
    goto loc_code_1952;
  _data16set(0x1B8F, _data16get(0x1B8F) -1);
loc_code_1952:
  if ( r8[bl] != 8 ) // jnz 
    goto loc_code_196B;
  if ( r16[cx] > 8 ) // ja 
    goto loc_code_196B;
  if ( r16[ax] > 8 ) // ja 
    goto loc_code_196B;
  r8[al] = _data[0x1B9C];
  if ( r8[al] == 0x11 ) // jz 
    goto loc_code_196B;
  sub_196F();
loc_code_196B:
  sub_10C6();
}
function sub_196F()
{
  STAT(0x196F);
  r8[al] = _data[0x1B8E];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1982;
  _data[0x951D] = 0x0F0;
  _data[0x94FF] = 1;
  return;
loc_code_1982:
  _push(si);
  _data[0x1B8E] = 0;
  si = 0x1B8A;
  r16[bx] = 0x0D49;
  sub_2121();
  si = _pop();
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
    goto loc_code_1A00;
  r8[al] = 0;
loc_code_1A00:
  _data[0x9502] = r8[al];
}
function sub_1A04()
{
  STAT(0x1A04);
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  r16[ax] -= 0x0C;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1A11;
  r16[ax] = - r16[ax];
loc_code_1A11:
  r16[cx] = _data16get(0x1B91);
  r16[cx] -= _data16get(ADR(ds, si + 7));
  if ( (short) r16[cx] >= 0 ) // jns 
    goto loc_code_1A1C;
  r16[cx] = - r16[cx];
loc_code_1A1C:
  r8[bl] = _data[ADR(ds, si + 4)];
  r8[bl] >>= 1;
  r16[ax] += r16[cx];
  if ( r16[ax] > 0x40 ) // ja 
    goto loc_code_1A32;
  if ( r8[bl] == 6 ) // jz 
    goto loc_code_1A30;
  _data[ADR(ds, si + 4)] = _data[ADR(ds, si + 4)] + 1;
loc_code_1A30:
  goto loc_code_1A3A;
loc_code_1A32:
  if ( r8[bl] == 0 ) // jz 
    goto loc_code_1A3A;
  _data[ADR(ds, si + 4)]--;
loc_code_1A3A:
  if ( r8[bl] != 6 ) // jnz 
    goto loc_code_1A45;
  _data[ADR(ds, si + 2)] = 0;
  goto loc_code_1A56;
loc_code_1A45:
  _push(r16[bx]);
  _data[ADR(ds, si + 2)] = 7;
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x1477));
  _data16set(ADR(ds, si + 0x0F), r16[ax]);
  r16[bx] = _pop();
loc_code_1A56:
  if ( r8[bl] < 1 ) // jb 
    goto loc_code_1A9A;
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  r16[ax] -= 0x0C;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1A73;
  r16[ax] = - r16[ax];
  if ( r16[ax] > 0x18 ) // ja 
    goto loc_code_1A71;
  _data16set(0x1B8F, _data16get(0x1B8F) + 1);
loc_code_1A71:
  goto loc_code_1A7E;
loc_code_1A73:
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_1A7E;
  if ( r16[ax] > 0x18 ) // ja 
    goto loc_code_1A7E;
  _data16set(0x1B8F, _data16get(0x1B8F) -1);
loc_code_1A7E:
  if ( r16[cx] > 8 ) // ja 
    goto loc_code_1A9A;
  if ( r16[ax] > 8 ) // ja 
    goto loc_code_1A9A;
  r8[al] = _data[0x1B9C];
  if ( r8[al] == 0x11 ) // jz 
    goto loc_code_1A9A;
  r16[ax] = _data16get(0x1B8F);
  _data16set(0x950A, r16[ax]);
  _data[0x94FF] = 1;
loc_code_1A9A:
  sub_10C6();
}
function sub_1A9E()
{
  STAT(0x1A9E);
  sub_10C6();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1AA8;
  return;
loc_code_1AA8:
  r16[bx] = _data16get(0x1B91);
  r16[bx] -= _data16get(ADR(ds, si + 7));
  if ( (short) r16[bx] >= 0 ) // jns 
    goto loc_code_1ABB;
  if ( (short)r16[bx] >= (short)0x0FFF0 ) // jge 
    return;
  _data[ADR(ds, si + 2)] = 1;
  return;
loc_code_1ABB:
  if ( (short)r16[bx] <= (short)0x20 ) // jle 
    goto loc_code_1AC1;
  return;
loc_code_1AC1:
  r16[ax] = _data16get(0x1B8F);
  r16[ax] -= _data16get(ADR(ds, si + 5));
  r16[ax] -= 0x0C;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1AD9;
  r16[ax] = - r16[ax];
  if ( r16[ax] >= 0x18 ) // jnb 
    goto loc_code_1AD7;
  _data16set(0x1B8F, _data16get(0x1B8F) + 1);
loc_code_1AD7:
  goto loc_code_1AE7;
loc_code_1AD9:
  if ( r16[ax] >= 0x18 ) // jnb 
    goto loc_code_1AE7;
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_1AE7;
  _data16set(0x1B8F, _data16get(0x1B8F) -1);
loc_code_1AE7:
  if ( r16[bx] <= 8 ) // jbe 
    goto loc_code_1AED;
  return;
loc_code_1AED:
  if ( r16[ax] > 2 ) // ja 
    goto loc_code_1AF8;
  _data16set(0x9538, _data16get(0x9538) + 1);
  return;
loc_code_1AF8:
  if ( r16[ax] >= 0x24 ) // jnb 
    return;
  _data16set(0x9542, 0);
  r8[al] = 6;
  sub_3840();
}
function sub_1B09()
{
  STAT(0x1B09);
  sub_10C6();
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1B13;
  return;
loc_code_1B13:
  r8[al] = _data[0x1B9C];
  if ( r8[al] != 0x11 ) // jnz 
    goto loc_code_1B1B;
  return;
loc_code_1B1B:
  r16[ax] = _data16get(ADR(ds, si + 5));
  r16[ax] -= _data16get(0x1B8F);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1B26;
  r16[ax] = - r16[ax];
loc_code_1B26:
  if ( r16[ax] >= 0x12 ) // jnb 
    return;
  r16[ax] = _data16get(ADR(ds, si + 7));
  r16[ax] -= _data16get(0x1B91);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_1B36;
  r16[ax] = - r16[ax];
loc_code_1B36:
  if ( r16[ax] >= 0x10 ) // jnb 
    return;
  _data[ADR(ds, si)] = 0;
  r8[al] = _data[ADR(ds, si + 1)];
  sub_2B28();
  r8[al] = 0x0A;
  sub_3840();
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
  STAT(0x1B80);
  r16[bx] = _data16get(0x952A);
  r16[ax] = _data16get(0x953A);
  if ( (short)r16[ax] > (short)0 ) // jg 
    goto loc_code_1B91;
  r16[ax] = 8;
  goto loc_code_1B94;
loc_code_1B91:
  r16[ax] = _data16get(0x954C);
loc_code_1B94:
  if ( !(r8[al] & 4) ) // jz 
    goto loc_code_1BA3;
  r16[bx] = r16[bx] + 1;
  if ( (short)r16[bx] <= (short)0x40 ) // jle 
    goto loc_code_1BA1;
  r16[bx] = 0x40;
loc_code_1BA1:
  goto loc_code_1BB4;
loc_code_1BA3:
  if ( !(r8[al] & 8) ) // jz 
    goto loc_code_1BB4;
  r16[bx] -= 2;
  if ( (short)r16[bx] >= (short)_data16get(0x94FC) ) // jge 
    goto loc_code_1BB4;
  r16[bx] = _data16get(0x94FC);
loc_code_1BB4:
  _data16set(0x952A, r16[bx]);
}
function sub_1BB9()
{
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
    goto loc_code_1BDD;
  r16[ax] = 0;
  _data16set(0x953C, 0x0FFFF);
loc_code_1BDD:
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
}
function sub_1C0A()
{
  STAT(0x1C0A);
  // arg_0		= word ptr  4
  // arg_2		= word ptr  6
  _push(bp);
  bp = sp;
  r16[bx] = _stack16get(bp + arg_2);
  r16[cx] = _stack16get(bp + arg_0);
  si = 0x1B8A;
loc_code_1C16:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    goto loc_code_1C2F;
  if ( !(r8[al] & 8) ) // jz 
    goto loc_code_1C2A;
  if ( r8[cl] != _data[ADR(ds, si + 0x14)] ) // jnz 
    goto loc_code_1C2A;
  if ( r8[bl] == _data[ADR(ds, si + 0x13)] ) // jz 
    goto loc_code_1C2F;
loc_code_1C2A:
  si += 0x17;
  goto loc_code_1C16;
loc_code_1C2F:
  bp = _pop();
  _retn(4);
}
function sub_1C33()
{
  STAT(0x1C33);
  r8[al] = _data[0x1B9C];
  if ( r8[al] != 0x11 ) // jnz 
    goto loc_code_1C3B;
  return;
loc_code_1C3B:
  r8[al] = 0x0C;
  sub_3840();
  si = 0x1B8A;
  sub_20F0();
  _data[0x1B9C] = 0x11;
  _data[0x1B8C] = 0;
  _data[0x9514] = 0;
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
    goto loc_code_1D10;
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) - 8);
  _data8set(ADR(ds, si + 3), _data8get(ADR(ds, si + 3)) + r8[cl]);
  goto loc_code_1D17;
loc_code_1D10:
  _data16set(ADR(ds, si + 5), _data16get(ADR(ds, si + 5)) + 8);
  _data8set(ADR(ds, si + 3), _data8get(ADR(ds, si + 3)) - r8[cl]);
loc_code_1D17:
  r16[bx] = 0x0DDA;
  sub_2121();
}
function sub_1D1E()
{
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
    goto loc_code_1DEB;
  r16[ax] = 0;
  _data16set(0x9540, 0x0FFFF);
loc_code_1DEB:
  _data16set(0x9511, r16[ax]);
}
function sub_1DEF()
{
  STAT(0x1DEF);
  _data[0x9516] = _data[0x9516] + 1;
  r8[bl] = _data[0x9516];
  r16[bx] &= 0x0F;
  r8[al] = _data[OFS(r16[bx] + 0x0FE7)];
  _data[0xFFB] = r8[al];
  r8[al] = _data[ADR(ds, si + 1)];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1E2E;
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
loc_code_1E2E:
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_1E46;
  r8[bl] = _data[ADR(ds, si + 4)];
  r8[bh] = 0;
  r8[cl] = _data[OFS(r16[bx] + 0x13E1)];
  r16[ax] = 0;
  r16[bx] = 8;
  sub_1E7D();
  return;
loc_code_1E46:
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
}
function sub_1E7D()
{
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
    goto loc_code_1EB0;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_1EB0;
  sub_16D6();
loc_code_1EB0:
  si = _pop();
  r8[al] = _data[0x9518];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1EB9;
  return;
loc_code_1EB9:
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
    goto loc_code_1F09;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_1F09;
  sub_15FC();
loc_code_1F09:
  si = _pop();
}
function sub_1F0B()
{
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
    goto loc_code_1F63;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_1F63;
  sub_16D6();
loc_code_1F63:
  si = _pop();
  r8[al] = _data[0x9518];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_1F6C;
  return;
loc_code_1F6C:
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
    goto loc_code_1FB8;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_1FB8;
  sub_15FC();
loc_code_1FB8:
  si = _pop();
}
function sub_1FBA()
{
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
    goto loc_code_2003;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_2003;
  sub_1429();
loc_code_2003:
  si = _pop();
}
function sub_2005()
{
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
    goto loc_code_2045;
  r16[ax] = _pop();
  _push(r16[ax]);
  if ( r16[ax] <= si ) // jbe 
    goto loc_code_2045;
  sub_17F4();
loc_code_2045:
  si = _pop();
}
function sub_2047()
{
  STAT(0x2047);
  r8[al] = _data[ADR(ds, si)];
  r8[bl] = _data[0x9517];
  if ( !(r8[al] & 0x20) ) // jz 
    goto loc_code_2072;
  if ( r8[bl] & 0x80 ) // jnz 
    goto loc_code_206D;
  _data[0x9517] |= 0x80;
  _data[0x1326] |= 0x20;
  di = 0x1326;
  sub_20A0();
  r8[al] = 3;
  sub_3840();
  goto loc_code_2070;
loc_code_206D:
  _data[ADR(ds, si)] = 0;
loc_code_2070:
  return;
loc_code_2072:
  if ( r8[bl] & 1 ) // jnz 
    goto loc_code_208E;
  _data[0x9517] |= 1;
  _data[0x1326] &= 0x0DF;
  di = 0x1326;
  sub_20A0();
  r8[al] = 3;
  sub_3840();
  return;
loc_code_208E:
  _data[ADR(ds, si)] = 0;
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
    goto loc_code_2119;
  _data16set(0x12A3, _data16get(0x12A3) - 0x0C);
  _data16set(0x12A5, _data16get(0x12A5) - 8);
  _data16set(0x12A5, _data16get(0x12A5) & 0x3FF);
loc_code_2119:
  si = 0x129E;
  sub_B58();
  si = _pop();
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
  STAT(0x215B);
  r16[cx] = 1;
  r16[ax] = _data16get(0x1B91);
  r16[ax] -= _data16get(ADR(ds, si + 7));
  if ( (short)r16[ax] <= (short)0x8C ) // jle 
    goto loc_code_2171;
  _data[ADR(ds, si + 4)] = 2;
  r16[cx] = 0;
  return;
loc_code_2171:
  if ( (short)r16[ax] >= (short)0x0FFF0 ) // jge 
    goto loc_code_21A0;
  r8[ah] = _data[ADR(ds, si + 4)];
  r8[al] = _data[ADR(ds, si)];
  if ( !(r8[al] & 0x20) ) // jz 
    goto loc_code_218D;
  r8[ah] = r8[ah] + 1;
  if ( (char)r8[ah] <= (char)4 ) // jle 
    goto loc_code_218B;
  _data[ADR(ds, si)] &= 0x0DF;
  r8[ah] = 4;
loc_code_218B:
  goto loc_code_2199;
loc_code_218D:
  r8[ah]--;
  if ( (char)r8[ah] >= (char)0 ) // jge 
    goto loc_code_2199;
  _data[ADR(ds, si)] |= 0x20;
  r8[ah] = 0;
loc_code_2199:
  _data[ADR(ds, si + 4)] = r8[ah];
  r16[cx] = 0;
  return;
loc_code_21A0:
  r16[bx] = _data16get(0x1B8F);
  r16[bx] -= _data16get(ADR(ds, si + 5));
  if ( (short) r16[bx] >= 0 ) // jns 
    goto loc_code_21C2;
  if ( (short)r16[bx] <= (short)0x0FFE0 ) // jle 
    goto loc_code_21B3;
  _data[ADR(ds, si + 4)] = 2;
  return;
loc_code_21B3:
  if ( (short)r16[ax] <= (short)0x20 ) // jle 
    goto loc_code_21BD;
  _data[ADR(ds, si + 4)] = 1;
  return;
loc_code_21BD:
  _data[ADR(ds, si + 4)] = 0;
  return;
loc_code_21C2:
  if ( (short)r16[bx] >= (short)0x20 ) // jge 
    goto loc_code_21CC;
  _data[ADR(ds, si + 4)] = 2;
  return;
loc_code_21CC:
  if ( (short)r16[ax] <= (short)0x20 ) // jle 
    goto loc_code_21D6;
  _data[ADR(ds, si + 4)] = 3;
  return;
loc_code_21D6:
  _data[ADR(ds, si + 4)] = 4;
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
	//return;
  STAT(0x220D);
  _data[0x944C] = _data[0x944C] + 1;
  r8[al] = _data[0x944C];
  r8[al] &= 3;
  if ( r8[al] ) // jnz 
    goto loc_code_2228;
  r16[ax] = 0;
  _push(r16[ax]);
  _push(r16[ax]);
  _push(r16[ax]);
  r8[al] = _data[0x94FE];
  _push(r16[ax]);
  sub_269E();
  sub_2714();
loc_code_2228:
  r16[ax] = _data16get(0x953C);
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_2246;
  if ( (short)(r16[ax]-0) >= 0 ) // jns 
    goto loc_code_2237;
  sub_252F();
  goto loc_code_2240;
loc_code_2237:
  r16[cx] = r16[ax];
loc_code_2239:
  _push(r16[cx]);
  sub_2542();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2239;
loc_code_2240:
  _data16set(0x953C, 0);
loc_code_2246:
  r16[ax] = _data16get(0x9540);
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_2264;
  if ( (short)(r16[ax]-0) >= 0 ) // jns 
    goto loc_code_2255;
  sub_2577();
  goto loc_code_225E;
loc_code_2255:
  r16[cx] = r16[ax];
loc_code_2257:
  _push(r16[cx]);
  sub_258A();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2257;
loc_code_225E:
  _data16set(0x9540, 0);
loc_code_2264:
  r16[ax] = _data16get(0x9544);
  //printf("hit=%d", (short)r16[ax]); r16[ax] = 0;
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_228A;
  if ( (short)(r16[ax]-0) >= 0 ) // jns 
    goto loc_code_227B;
  r16[ax] = - r16[ax];
  r16[cx] = r16[ax];
loc_code_2272:
  _push(r16[cx]);
  sub_25BF(); // <--- problem
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2272;
  goto loc_code_2284;
loc_code_227B:
  r16[cx] = r16[ax];
loc_code_227D:
  _push(r16[cx]);
  sub_25D2();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_227D;
loc_code_2284:
  _data16set(0x9544, 0);
loc_code_228A:
  r16[ax] = _data16get(0x9538);
  if ( r16[ax] == 0 ) // jz 
    return;
  if ( (short)(r16[ax]-0) >= 0 ) // jns 
    goto loc_code_22A1;
  r16[ax] = - r16[ax];
  r16[cx] = r16[ax];
loc_code_2298:
  _push(r16[cx]);
  sub_2464();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2298;
  goto loc_code_22AA;
loc_code_22A1:
  r16[cx] = r16[ax];
loc_code_22A3:
  _push(r16[cx]);
  sub_239B();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_22A3;
loc_code_22AA:
  _data16set(0x9538, 0);
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
  STAT(0x22C1);
  _data16set(0x9534, _data16get(0x9534) + 1);
  r16[ax] = _data16get(0x9534);
  if ( r16[ax] <= 3 ) // jbe 
    goto loc_code_22D4;
  _data16set(0x9534, 3);
  return;
loc_code_22D4:
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
  STAT(0x2329);
  _data16set(0x9534, _data16get(0x9534) -1);
  r16[ax] = _data16get(0x9534);
  if ( r16[ax] == 2 ) // jz 
    goto loc_code_2368;
  if ( r16[ax] == 1 ) // jz 
    goto loc_code_2354;
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_2340;
  return;
loc_code_2340:
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
loc_code_2354:
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
loc_code_2368:
  r16[ax] = 0x1B96;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  sub_2D9A();
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
  STAT(0x239B);
  _data16set(0x9536, _data16get(0x9536) + 1);
  r16[ax] = _data16get(0x9536);
  if ( r16[ax] <= 6 ) // jbe 
    goto loc_code_23AE;
  _data16set(0x9536, 6);
  return;
loc_code_23AE:
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
  STAT(0x2464);
  r16[ax] = _data16get(0x9536);
  _data16set(0x9536, _data16get(0x9536) -1);
  if ( (short)_data16get(0x9536) >= 0 ) // jns 
    goto loc_code_2474;
  _data16set(0x9536, 0);
  return;
loc_code_2474:
  if ( r16[ax] == 1 ) // jz 
    goto loc_code_2493;
  if ( r16[ax] == 2 ) // jz 
    goto loc_code_24A7;
  if ( r16[ax] == 3 ) // jz 
    goto loc_code_24BB;
  if ( r16[ax] == 4 ) // jz 
    goto loc_code_24CF;
  if ( r16[ax] == 5 ) // jz 
    goto loc_code_24E3;
  if ( r16[ax] == 6 ) // jz 
    goto loc_code_24F7;
  return;
loc_code_2493:
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
loc_code_24A7:
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
loc_code_24BB:
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
loc_code_24CF:
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
loc_code_24E3:
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
loc_code_24F7:
  r16[ax] = 0x1BA3;
  _push(r16[ax]);
  r16[ax] = 2;
  _push(r16[ax]);
  r16[ax] = 0x0F;
  _push(r16[ax]);
  r16[ax] = 0;
  _push(r16[ax]);
  sub_2D9A();
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
  if ( (short) r16[ax] >= 0 ) // jns 
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
  STAT(0x2542);
  r16[ax] = _data16get(0x953A);
  if ( r16[ax] < 0x2C ) // jb 
    goto loc_code_254B;
  return;
loc_code_254B:
  sub_2536();
  _data16set(0x953A, _data16get(0x953A) + 1);
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
  if ( (short) r16[ax] >= 0 ) // jns 
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
  STAT(0x258A);
  r16[ax] = _data16get(0x953E);
  if ( r16[ax] < 0x30 ) // jb 
    goto loc_code_2593;
  return;
loc_code_2593:
  sub_257E();
  _data16set(0x953E, _data16get(0x953E) + 1);
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
  if ( (short) r16[ax] >= 0 ) // jns 
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
  STAT(0x25D2);
  r16[ax] = _data16get(0x9542);
  if ( r16[ax] < 0x38 ) // jb 
    goto loc_code_25DB;
  return;
loc_code_25DB:
  sub_25C6();
  _data16set(0x9542, _data16get(0x9542) + 1);
}
function sub_25E3()
{
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
loc_code_261E:
  r8[al] = _video8get(ADR(es,di));
  if ( r8[al] & r8[bl] ) // jnz 
    goto loc_code_262D;
  _video8set(ADR(es,di), r8[bl]);
  _video8set(ADR(es,di+0x2000), r8[bl]);
loc_code_262D:
  di += 0x28;
  if ( --r16[cx] )
    goto loc_code_261E;
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
    goto loc_code_26B1;
  r8[al] -= 0x0A;
  _data[0x94AD] = _data[0x94AD] + 1;
loc_code_26B1:
  _data[0x94AE] = r8[al];
  r8[al] = _data[0x94AD];
  r8[al] += _stack8get(bp + arg_2);
  if ( r8[al] <= 9 ) // jbe 
    goto loc_code_26C4;
  r8[al] -= 0x0A;
  _data[0x94AC] = _data[0x94AC] + 1;
loc_code_26C4:
  _data[0x94AD] = r8[al];
  r8[al] = _data[0x94AC];
  r8[al] += _stack8get(bp + arg_4);
  if ( r8[al] <= 9 ) // jbe 
    goto loc_code_26D7;
  r8[al] -= 0x0A;
  _data[0x94AB] = _data[0x94AB] + 1;
loc_code_26D7:
  _data[0x94AC] = r8[al];
  r8[al] = _data[0x94AB];
  r8[al] += _stack8get(bp + arg_6);
  if ( r8[al] <= 9 ) // jbe 
    goto loc_code_26EA;
  r8[al] -= 0x0A;
  _data[0x94AA] = _data[0x94AA] + 1;
loc_code_26EA:
  _data[0x94AB] = r8[al];
  r8[al] = _data[0x94AA];
  if ( r8[al] <= 9 ) // jbe 
    goto loc_code_2701;
  r8[al] -= 0x0A;
  _data[0x94A9] = _data[0x94A9] + 1;
  _push(r16[ax]);
  _push(si);
  sub_22C1();
  si = _pop();
  r16[ax] = _pop();
loc_code_2701:
  _data[0x94AA] = r8[al];
  r8[al] = _data[0x94A9];
  if ( r8[al] <= 9 ) // jbe 
    goto loc_code_270D;
  r8[al] -= 0x0A;
loc_code_270D:
  _data[0x94A9] = r8[al];
  bp = _pop();
  _retn(8);
}
function sub_2714()
{
  STAT(0x2714);
  _data[0x944D] = 1;
  si = 0x94A9;
  r16[cx] = 6;
  r16[dx] = 0;
loc_code_2722:
  _push(r16[cx]);
  _lodsb();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_272D;
  _data[0x944D] = 0;
loc_code_272D:
  r8[cl] = _data[0x944D];
  if ( r8[cl] != 0 ) // jnz 
    goto loc_code_275E;
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
loc_code_275E:
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2722;
}
function sub_2762()
{
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
loc_code_278B:
  _data[ADR(ds, si)] = r8[al];
  r8[al] = r8[al] + 1;
  si = si + 1;
  if ( --r16[cx] )
    goto loc_code_278B;
  di = 0x9455;
  r16[dx] = 0x1506;
  r16[cx] = 0x8C;
  sub_644();
}
function sub_279F()
{
  STAT(0x279F);
  sub_2809();
  r8[al] = _data[0x94E0];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_27AF;
  _data[0x9546] = 0;
  return;
loc_code_27AF:
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
loc_code_27C9:
  _lodsb();
  _data[r16[bx]] = r8[al];
  r16[bx] = r16[bx] + 1;
  if ( --r16[cx] )
    goto loc_code_27C9;
  r16[bx] = _pop();
  r16[bx] <<= 1;
  r16[bx] += 0x9455;
  _data16set(0x9451, r16[bx]);
  si = 0x9455;
  r16[cx] = 0x0C;
loc_code_27E0:
  _lodsb();
  _data[r16[bx]] = r8[al];
  r16[bx] = r16[bx] + 1;
  if ( --r16[cx] )
    goto loc_code_27E0;
  si = 0x94DA;
loc_code_27E9:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_27F2;
  si = si + 1;
  goto loc_code_27E9;
loc_code_27F2:
  r8[al] = _data[0x94E0];
  _data[ADR(ds, si)] = r8[al];
  _data[0x94E0] = 0;
  si -= 0x94DA;
  r16[ax] = si;
  _data[0x9450] = r8[al];
  sub_28DA();
}
function sub_2809()
{
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
loc_code_283C:
  _push(r16[cx]);
  _push(si);
loc_code_283E:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] != 0x0FF ) // jnz 
    goto loc_code_2847;
  si = si + 1;
  goto loc_code_283E;
loc_code_2847:
  if ( si == 0x94D9 ) // jz 
    goto loc_code_2865;
  r16[bx] = si;
loc_code_284F:
  r16[bx] = r16[bx] + 1;
  r8[al] = _data[r16[bx]];
  if ( r8[al] == 0x0FF ) // jz 
    goto loc_code_285F;
  sub_2872();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_285F;
  si = r16[bx];
loc_code_285F:
  if ( r16[bx] != 0x94D9 ) // jnz 
    goto loc_code_284F;
loc_code_2865:
  r8[al] = _data[ADR(ds, si)];
  _data[ADR(ds, si)] = 0x0FF;
  _data[di] = r8[al];
  di = di + 1;
  si = _pop();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_283C;
}
function sub_2872()
{
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
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si)] ) // jb 
    goto loc_code_28D0;
  r8[al] = _data[OFS(di + 1)];
  if ( r8[al] > _data[ADR(ds, si + 1)] ) // ja 
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si + 1)] ) // jb 
    goto loc_code_28D0;
  r8[al] = _data[OFS(di + 2)];
  if ( r8[al] > _data[ADR(ds, si + 2)] ) // ja 
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si + 2)] ) // jb 
    goto loc_code_28D0;
  r8[al] = _data[OFS(di + 3)];
  if ( r8[al] > _data[ADR(ds, si + 3)] ) // ja 
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si + 3)] ) // jb 
    goto loc_code_28D0;
  r8[al] = _data[OFS(di + 4)];
  if ( r8[al] > _data[ADR(ds, si + 4)] ) // ja 
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si + 4)] ) // jb 
    goto loc_code_28D0;
  r8[al] = _data[OFS(di + 5)];
  if ( r8[al] > _data[ADR(ds, si + 5)] ) // ja 
    goto loc_code_28D5;
  if ( r8[al] < _data[ADR(ds, si + 5)] ) // jb 
  {
	  _ASSERT(0);
   //oto $+2;
  }
loc_code_28D0:
  r8[al] = 0;
  di = _pop();
  si = _pop();
  return;
loc_code_28D5:
  r8[al] = 1;
  di = _pop();
  si = _pop();
}
function sub_28DA()
{
  STAT(0x28DA);
  si = 0x94DA;
  di = 0x1B1;
  r16[cx] = 6;
loc_code_28E3:
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
    goto loc_code_28E3;
}
function sub_2907()
{
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
loc_code_2926:
  _push(r16[cx]);
  _lodsb();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_2931;
  _data[0x944D] = 0;
loc_code_2931:
  r8[cl] = _data[0x944D];
  if ( r8[cl] == 0 ) // jz 
    goto loc_code_293F;
  r16[ax] = 0x6F6C;
  goto loc_code_2949;
loc_code_293F:
  r8[bh] = 0;
  r8[bl] = r8[al];
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] + 0x157F));
loc_code_2949:
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
    goto loc_code_2926;
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
  STAT(0x296F);
  r16[cx] = 0x0C;
  r16[dx] = 0;
loc_code_2975:
  _push(r16[cx]);
  _lodsb();
  _push(si);
  _push(r16[dx]);
  if ( r8[al] != 0x20 ) // jnz 
    goto loc_code_2982;
  r16[ax] = 0x6546;
  goto loc_code_29A0;
loc_code_2982:
  if ( r8[al] != 0x2E ) // jnz 
    goto loc_code_298B;
  r16[ax] = 0x6F6C;
  goto loc_code_29A0;
loc_code_298B:
  if ( r8[al] != 0x5F ) // jnz 
    goto loc_code_2994;
  r16[ax] = 0x764C;
  goto loc_code_29A0;
loc_code_2994:
  r8[al] -= 0x41;
  r8[ah] = r8[al];
  r8[al] <<= 1;
  r8[al] += r8[ah];
  r8[al] <<= 1;
  r8[ah] = 0;
loc_code_29A0:
  _push(r16[ax]);
  _push(r16[dx]);
  sub_29AE();
  r16[dx] = _pop();
  r16[dx] += 6;
  si = _pop();
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_2975;
}
function sub_29AE()
{
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
loc_code_29C9:
  _movsw();
  _movsw();
  _movsw();
  di += 0x9A;
  si += 0x9A;
  if ( --r16[cx] )
    goto loc_code_29C9;
  ds = _pop();
  bp = _pop();
  _retn(4);
}
function sub_29DB()
{
  STAT(0x29DB);
  _data16set(0x9453, 0);
loc_code_29E1:
  r16[ax] = _data16get(0x9453);
  if ( r16[ax] >= 0x0C ) // jnb 
    goto loc_code_2A39;
  sub_541();
  if ( r8[al] == 0 ) // jz 
    goto loc_code_2A39;
  if ( r8[al] != 8 ) // jnz 
    goto loc_code_2A0D;
  r16[bx] = _data16get(0x9451);
  r16[bx] += _data16get(0x9453);
  _data[r16[bx]] = 0x2E;
  _data16set(0x9453, _data16get(0x9453) -1);
  if ( (short)_data16get(0x9453) >= 0 ) // jns 
    goto loc_code_2A0B;
  _data16set(0x9453, 0);
loc_code_2A0B:
  goto loc_code_2A1B;
loc_code_2A0D:
  r16[bx] = _data16get(0x9451);
  r16[bx] += _data16get(0x9453);
  _data[r16[bx]] = r8[al];
  _data16set(0x9453, _data16get(0x9453) + 1);
loc_code_2A1B:
  r16[bx] = _data16get(0x9453);
  if ( r16[bx] >= 0x0C ) // jnb 
    goto loc_code_2A2B;
  r16[bx] += _data16get(0x9451);
  _data[r16[bx]] = 0x5F;
loc_code_2A2B:
  sub_2A64();
  sub_3498();
  sub_B8E();
  sub_3383();
  goto loc_code_29E1;
loc_code_2A39:
  r16[bx] = _data16get(0x9453);
  if ( r16[bx] >= 0x0C ) // jnb 
    goto loc_code_2A52;
  r16[bx] += _data16get(0x9451);
  r8[al] = _data[r16[bx]];
  if ( r8[al] != 0x5F ) // jnz 
    goto loc_code_2A52;
  _data[r16[bx]] = 0x2E;
  sub_2A64();
loc_code_2A52:
  di = 0x9455;
  r16[dx] = 0x1506;
  r16[cx] = 0x8C;
  sub_674();
  _data[0x9546] = 0;
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
    goto loc_code_2B59;
  if ( r8[al] == 1 ) // jz 
    goto loc_code_2B76;
  if ( r8[al] == 2 ) // jz 
    goto loc_code_2B93;
  if ( r8[al] == 3 ) // jz 
    goto loc_code_2BB0;
  if ( r8[al] == 4 ) // jz 
    goto loc_code_2BCD;
  if ( r8[al] != 5 ) // jnz 
    return;
  goto loc_code_2BEA;
  return;
loc_code_2B59:
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
loc_code_2B76:
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
loc_code_2B93:
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
loc_code_2BB0:
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
loc_code_2BCD:
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
loc_code_2BEA:
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
    goto loc_code_2CBC;
  r8[al] = 0;
  sub_2CC7();
  r8[al] = 6;
  sub_2CC7();
  return;
loc_code_2CBC:
  if ( r8[al] != 7 ) // jnz 
  {
	  sub_2CC7();
	  return;
  }
  r8[al] = 1;
  sub_2CC7();
  r8[al] = 7;
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
loc_code_2D19:
  _push(r16[ax]);
  _push(r16[bx]);
  _push(r16[cx]);
  _push(di);
  _push(si);
loc_code_2D1E:
  r8[bh] = 0x22;
loc_code_2D20:
  r8[bl] = _data[ADR(ds, si)];
  si = si + 1;
  if ( r8[bh] != r8[bl] ) // jnz 
    goto loc_code_2D3D;
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_2D32;
  r8[ah] = 0x40;
  di = di + 1;
  if ( --r16[cx] )
    goto loc_code_2D20;
  goto loc_code_2D76;
loc_code_2D32:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_2D39;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_2D39:
  if ( --r16[cx] )
    goto loc_code_2D20;
  goto loc_code_2D76;
loc_code_2D3D:
  r8[bh] = r8[bl];
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  r8[bl] >>= 1;
  if ( r8[bl] == 2 ) // jz 
    goto loc_code_2D55;
  _out(r16[dx], r16[ax]);
  _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bl]);
  _video8set(ADR(es,di+0x2000), _video8get(ADR(es,di+0x2000)) & r8[bl]);
loc_code_2D55:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_2D5C;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_2D5C:
  r8[bh] &= 0x0F;
  if ( r8[bh] == 2 ) // jz 
    goto loc_code_2D6D;
  _out(r16[dx], r16[ax]);
  _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[bh]);
  _video8set(ADR(es,di+0x2000), _video8get(ADR(es,di+0x2000)) & r8[bh]);
loc_code_2D6D:
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_2D74;
  r8[ah] = 0x80;
  di = di + 1;
loc_code_2D74:
  if ( --r16[cx] )
    goto loc_code_2D1E;
loc_code_2D76:
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
    goto loc_code_2D19;
  ds = _pop();
  r16[ax] = 0x0FF08;
  _out(r16[dx], r16[ax]);
  r16[ax] = 5;
  _out(r16[dx], r16[ax]);
  r16[ax] = 0x0F07;
  _out(r16[dx], r16[ax]);
  bp = _pop();
  _retn(0x0A);
}
function sub_2D9A()
{
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
loc_code_2DB8:
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
    goto loc_code_2DB8;
  r16[ax] = 0;
  _out(r16[dx], r16[ax]);
  r8[al] = r8[al] + 1;
  _out(r16[dx], r16[ax]);
  bp = _pop();
  _retn(8);
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
    goto loc_code_2E23;
  r16[ax] = - r16[ax];
  r16[ax] -= 3;
  goto loc_code_2E30;
loc_code_2E23:
  if ( !(r8[bl] & 2) ) // jz 
    goto loc_code_2E2D;
  r16[ax] += 3;
  goto loc_code_2E30;
loc_code_2E2D:
  r16[ax] = 0;
loc_code_2E30:
  _data16set(0x9522, r16[ax]);
  r8[al] = _data[ADR(ds, si + 0x16)];
  r16[ax] &= 0x7F;
  if ( r8[al] <= 0x3F ) // jbe 
    goto loc_code_2E48;
  r8[al] = - r8[al];
  r8[al] += 0x7F;
  sub_3084();
  r16[ax] = - r16[ax];
  goto loc_code_2E4B;
loc_code_2E48:
  sub_3084();
loc_code_2E4B:
  _data16set(0x9520, r16[ax]);
  r16[ax] = _data16get(0x951E);
  r16[ax] += _data16get(0x9522);
  r16[ax] += _data16get(0x9520);
  if ( !r16[ax] ) // jz 
    goto loc_code_2E6A;
// dummy
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_2E63;
  r16[ax] = r16[ax] + 1;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_2E61;
  r16[ax] = r16[ax] + 1;
loc_code_2E61:
  goto loc_code_2E6A;
loc_code_2E63:
  r16[ax]--;
  if ( (short)r16[ax] <= (short)0 ) // jle 
    goto loc_code_2E6A;
  r16[ax]--;
loc_code_2E6A:
  if ( (short)r16[ax] <= (short)0x40 ) // jle 
    goto loc_code_2E74;
  r16[ax] = 0x40;
  goto loc_code_2E7C;
loc_code_2E74:
  if ( (short)r16[ax] >= (short)0x0FFC0 ) // jge 
    goto loc_code_2E7C;
  r16[ax] = 0x0FFC0;
loc_code_2E7C:
  _data16set(0x951E, r16[ax]);
  r16[ax] = _sar16(r16[ax]);
  r16[ax] = _sar16(r16[ax]);
//  unknown_command(); // sar	ax, 1
//  unknown_command(); // sar	ax, 1
  _data8set(ADR(ds, si + 0x16), _data8get(ADR(ds, si + 0x16)) + r8[al]);
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
    goto loc_code_2EBE;
  r16[bx] = r16[ax];
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += r16[bx];
  r16[ax] <<= 1;
  r16[ax] += 5;
  r8[bl] = 0x0C;
  _div(r8[bl]);
  r8[ah] = 0;
loc_code_2EBE:
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
    goto loc_code_2F02;
  if ( r8[bl] != 2 ) // jnz 
    goto loc_code_2F00;
  _data[0x951A] = 3;
  r8[al] = 2;
  sub_3840();
  _data[0x951C] = 2;
loc_code_2F00:
  goto loc_code_2F18;
loc_code_2F02:
  if ( r8[bl] != 1 ) // jnz 
    goto loc_code_2F0E;
  _data[0x951A] = 2;
  goto loc_code_2F18;
loc_code_2F0E:
  if ( r8[bl] != 3 ) // jnz 
    goto loc_code_2F18;
  _data[0x951A] = 0;
loc_code_2F18:
  r16[ax] = _data16get(0x954C);
  r8[bl] = _data[0x951B];
  if ( !(r8[al] & 0x20) ) // jz 
    goto loc_code_2F39;
  if ( r8[bl] != 2 ) // jnz 
    goto loc_code_2F37;
  _data[0x951B] = 3;
  r8[al] = 2;
  sub_3840();
  _data[0x951C] = 2;
loc_code_2F37:
  return;
loc_code_2F39:
  if ( r8[bl] != 1 ) // jnz 
    goto loc_code_2F45;
  _data[0x951B] = 2;
  return;
loc_code_2F45:
  if ( r8[bl] != 3 ) // jnz 
    return;
  _data[0x951B] = 0;
}
function sub_2F50()
{
  STAT(0x2F50);
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x20 ) // jnz 
    goto loc_code_2F5E;
  r8[ah] = _data[0x951A];
  r8[al] = 0x0F8;
  goto loc_code_2F64;
loc_code_2F5E:
  r8[ah] = _data[0x951B];
  r8[al] = 8;
loc_code_2F64:
  if ( r8[ah] == 3 ) // jz 
    goto loc_code_2F6E;
  if ( r8[ah] != 0 ) // jnz 
    goto loc_code_2F90;
loc_code_2F6E:
  _data[ADR(ds, si)] = 0;
  si = 0x1BA1;
loc_code_2F74:
  r8[al] = _data[ADR(ds, si)];
  if ( r8[al] & 0x80 ) // jnz 
    return;
  if ( !(r8[al] & 1) ) // jz 
    goto loc_code_2F8A;
  r8[al] = _data[ADR(ds, si + 0x12)];
  if ( r8[al] != 0x0F ) // jnz 
    goto loc_code_2F8A;
  _push(si);
  sub_3059();
  si = _pop();
loc_code_2F8A:
  si += 0x17;
  goto loc_code_2F74;
  return;
loc_code_2F90:
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
    goto loc_code_2FD0;
  r16[bx] = r16[ax];
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += r16[bx];
  r16[ax] <<= 1;
  r16[ax] += 5;
  r8[bl] = 0x0C;
  _div(r8[bl]);
  r8[ah] = 0;
loc_code_2FD0:
  r8[bl] = _data[0x1BA0];
  r16[bx] &= 0x7F;
  _data16set(ADR(ds, si + 7), r16[ax]);
  r8[al] = _data[OFS(r16[bx] + 0x1892)];
  _data[ADR(ds, si + 4)] = r8[al];
  r16[bx] = 0x1811;
  sub_2121();
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
  STAT(0x300A);
  r16[ax] = _data16get(0x9547);
  r16[ax] -= _data16get(ADR(ds, si + 0x13));
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  if ( r16[ax] <= 0x2D ) // jbe 
    goto loc_code_301F;
  _data[ADR(ds, si)] = 0;
  return;
loc_code_301F:
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
    goto loc_code_3040;
  return;
loc_code_3040:
  r8[bl] = _data[0x1B8E];
  r8[bh] = 0;
  r8[al] = _data[OFS(r16[bx] + 0x17F5)];
  if ( r8[al] == _data[ADR(ds, si + 1)] ) // jz 
    goto loc_code_3050;
  return;
loc_code_3050:
  r8[al] = 9;
  sub_3840();
  sub_3059();
}
function sub_3059()
{
  STAT(0x3059);
  _data[ADR(ds, si)] = 0;
  r8[al] = _data[0x951D];
  if ( r8[al] != 0x40 ) // jnz 
    goto loc_code_306A;
  _data16set(0x9540, _data16get(0x9540) + 6);
  return;
loc_code_306A:
  if ( r8[al] != 0x80 ) // jnz 
    goto loc_code_3075;
  _data16set(0x953C, _data16get(0x953C) + 4);
  return;
loc_code_3075:
  if ( r8[al] != 0x0C0 ) // jnz 
    goto loc_code_3080;
  _data16set(0x9544, _data16get(0x9544) + 8);
  return;
loc_code_3080:
  sub_268A();
}
function sub_3084()
{
  STAT(0x3084);
  r8[al] -= 5;
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_308D;
  r16[ax] = 0;
  return;
loc_code_308D:
  if ( r8[al] <= 0x38 ) // jbe 
    goto loc_code_3093;
  r8[al] = 0x38;
loc_code_3093:
  r8[al] >>= 1;
  r8[ah] = 0;
  r16[ax] = - r16[ax];
  r16[ax] -= 3;
}
function sub_309D()
{
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
    goto loc_code_30C4;
  r16[ax] = 0;
  _data16set(0x953C, 0x0FFFF);
loc_code_30C4:
  _data16set(0x950F, r16[ax]);
  r16[ax] = _data16get(0x9547);
  r16[ax] -= 0x380;
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_3124;
  r16[ax] = - r16[ax];
  if ( r16[ax] >= 0x100 ) // jnb 
    goto loc_code_30ED;
  _data16set(0x9525, r16[ax]);
  r8[al] = _data[0x9524];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_30EB;
  si = 0x1912;
  sub_B58();
  _data[0x9524] = 1;
loc_code_30EB:
  goto loc_code_3122;
loc_code_30ED:
  r16[ax] = _data16get(0x9547);
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  r16[ax] >>= 1;
  if ( r8[al] == _data[0x9527] ) // jz 
    goto loc_code_3122;
  _data[0x9527] = r8[al];
  r8[bl] = r8[al];
  r8[bh] = 0;
  r16[bx] += _data16get(0x94E2);
  r8[al] = _data[r16[bx]];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_3122;
  si = 0x1AB2;
  _data[ADR(ds, si + 1)] = r8[al];
  r16[ax] = _data16get(0x9547);
  _data16set(ADR(ds, si + 0x13), r16[ax]);
  sub_B58();
loc_code_3122:
  return;
loc_code_3124:
  _data[0x94FF] = 0;
  r16[ax] = _data16get(0x950C);
  _data16set(0x9528, r16[ax]);
}

void sub_3167();
void sub_3178();
void sub_3188();
void sub_319B();

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
loc_code_31D2:
  _push(r16[cx]);
  r16[cx] = 0x20;
  _rep_movsb();
  di += 8;
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_31D2;
  ds = _pop();
  r16[ax] = 0;
  _out(r16[dx], r16[ax]);
  r8[al] = r8[al] + 1;
  _out(r16[dx], r16[ax]);
}
function sub_31E7()
{
  STAT(0x31E7);
  r8[al] = _data[0x951D];
  if ( r8[al] != 0x40 ) // jnz 
    goto loc_code_31F3;
  r16[ax] = 2;
  return;
loc_code_31F3:
  if ( r8[al] != 0x80 ) // jnz 
    goto loc_code_31FC;
  r16[ax] = 4;
  return;
loc_code_31FC:
  if ( r8[al] != 0x0C0 ) // jnz 
    goto loc_code_3205;
  r16[ax] = 1;
  return;
loc_code_3205:
  r16[ax] = 3;
}
function sub_3209()
{
  STAT(0x3209);
  r8[al] = _data[0x951C];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_3215;
  r16[ax] = 0;
  return;
loc_code_3215:
  if ( r8[al] != 1 ) // jnz 
    goto loc_code_3223;
  r16[ax] = 7;
  _data[0x951C] = 0;
  return;
loc_code_3223:
  r16[ax] = 0x0F;
  _data[0x951C] = 1;
}
function sub_3291()
{
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
loc_code_32B0:
  _push(r16[cx]);
  r16[cx] = 0x20;
  _rep_movsb();
  si += 8;
  di += 8;
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_32B0;
  ds = _pop();
  r16[ax] = 5;
  _out(r16[dx], r16[ax]);
  bp = _pop();
  _retn(4);
}
function sub_32FE()
{
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
loc_code_3326:
  _push(r16[cx]);
  r16[cx] = 0x20;
  _rep_movsb();
  si &= 0x7FFF;
  di += 8;
  r16[cx] = _pop();
  if ( --r16[cx] )
    goto loc_code_3326;
  ds = _pop();
  r16[ax] = 5;
  _out(r16[dx], r16[ax]);
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
loc_code_33AA:
  r8[al] = _in(r16[dx]);
  r8[al] &= 8;
  if ( r8[al] ) // jnz 
    goto loc_code_33AA;
	*/
  sub_33D7();
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
  STAT(0x33D7);
  r16[dx] = 0x3DA;
loc_code_33DA:
  r8[al] = _in(r16[dx]);
  r8[al] &= 8;
  if ( !r8[al] ) // jz 
    goto loc_code_33DA;
loc_code_33DF:
  r8[al] = _in(r16[dx]);
  r8[al] &= 8;
  if ( r8[al] ) // jnz 
    goto loc_code_33DF;
}
function sub_33E5()
{
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
loc_code_3400:
  _out(r16[dx], r16[ax]);
  _push(r16[ax]);
  _push(di);
  r16[cx] = 0x1F40;
loc_code_3406:
  _lodsb();
  _video8set(ADR(es,di), _video8get(ADR(es,di)) & r8[al]);
  di = di + 1;
  if ( --r16[cx] )
    goto loc_code_3406;
  di = _pop();
  r16[ax] = _pop();
  r8[ah] >>= 1;
  if ( r8[ah] ) // jnz 
    goto loc_code_3400;
  ds = _pop();
  r16[ax] = 0x0F02;
  _out(r16[dx], r16[ax]);
  r8[dl] = 0x0CE;
  r16[ax] = 5;
  _out(r16[dx], r16[ax]);
  r16[ax] = 0x0F07;
  _out(r16[dx], r16[ax]);
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
loc_code_3459:
  _video8set(ADR(es,di), r8[al]);
  di += 0x28;
  if ( --r16[cx] )
    goto loc_code_3459;
  di = 0x13C;
  r8[al] = 0x80;
  r16[cx] = 0x0A2;
loc_code_3469:
  _video8set(ADR(es,di), r8[al]);
  di += 0x28;
  if ( --r16[cx] )
    goto loc_code_3469;
}
function sub_3472()
{
  STAT(0x3472);
  si = 0;
  r16[bx] = _data16get(0x94F2);
  sub_33E5();
  sub_3383(); // prvy
  si = 0;
  r16[bx] = _data16get(0x94F2);
  sub_33E5(); // druhy
  r16[ax] = _data16get(0x94F8);
  _push(r16[ax]);
  r16[ax] = 0x0A000;
  r16[ax] += 0x400;
  _push(r16[ax]);
  sub_3291(); // treti
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
    goto loc_code_3527;
  return;
loc_code_3527:
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
}
function sub_35BC()
{
  STAT(0x35BC);
  // arg_0		= word ptr  4
  // arg_2		= word ptr  6
  _push(bp);
  bp = sp;
loc_code_35BF:
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
    goto loc_code_36D0;
  _stack16set(OFS(bp + arg_2), r16[ax]);
  r16[ax] = _stack16get(bp + arg_0);
  r16[ax] >>= 1;
  _stack16set(OFS(bp + arg_0), r16[ax]);
  goto loc_code_35BF;
loc_code_36D0:
  bp = _pop();
  _retn(4);
}
function sub_36D4()
{
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
    goto loc_code_36FA;
  r16[bx] = r16[ax];
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += r16[bx];
  r16[ax] <<= 1;
  r16[ax] += 5;
  r8[bl] = 0x0C;
  _div(r8[bl]);
  r8[ah] = 0;
loc_code_36FA:
  _stack16set(OFS(bp + arg_4), r16[ax]);
  r16[ax] = _stack16get(bp + arg_0);
  if ( r16[ax] == 0 ) // jz 
    goto loc_code_3718;
  r16[bx] = r16[ax];
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += r16[bx];
  r16[ax] <<= 1;
  r16[ax] += 5;
  r8[bl] = 0x0C;
  _div(r8[bl]);
  r8[ah] = 0;
loc_code_3718:
  _stack16set(OFS(bp + arg_0), r16[ax]);
  r16[ax] = _stack16get(bp + arg_6);
  r16[bx] = _stack16get(bp + arg_2);
  if ( r16[bx] >= r16[ax] ) // jnb 
    goto loc_code_3737;
  _stack16set(OFS(bp + arg_6), r16[bx]);
  _stack16set(OFS(bp + arg_2), r16[ax]);
  r16[ax] = _stack16get(bp + arg_4);
  r16[bx] = _stack16get(bp + arg_0);
  _stack16set(OFS(bp + arg_4), r16[bx]);
  _stack16set(OFS(bp + arg_0), r16[ax]);
loc_code_3737:
  r16[ax] = _stack16get(bp + arg_2);
  r16[ax] -= _stack16get(bp + arg_6);
  _stack16set(OFS(bp + var_2), r16[ax]);
  r16[ax] = _stack16get(bp + arg_0);
  r16[ax] -= _stack16get(bp + arg_4);
  if ( (short) r16[ax] >= 0 ) // jns 
    goto loc_code_3751;
  r16[ax] = - r16[ax];
  _stack16set(OFS(bp + var_A), 0x0FFE0);
  goto loc_code_3756;
loc_code_3751:
  _stack16set(OFS(bp + var_A), 0x20);
loc_code_3756:
  _stack16set(OFS(bp + var_4), r16[ax]);
  r16[cx] = _stack16get(bp + var_2);
  if ( r16[cx] == 0 ) // jz 
    goto loc_code_37DB;
  if ( r16[ax] != 0 ) // jnz 
    goto loc_code_3769;
  goto loc_code_37ED;
loc_code_3769:
  if ( r16[ax] >= _stack16get(bp + var_2) ) // jnb 
    goto loc_code_37A4;
  r16[ax] = _stack16get(bp + var_2);
  r16[ax] >>= 1;
  _stack16set(OFS(bp + var_6), r16[ax]);
  sub_3801();
  r16[cx] = _stack16get(bp + var_2);
loc_code_377C:
  r8[al] >>= 1;
  if ( r8[al] ) // jnz 
    goto loc_code_3783;
  r8[al] = 0x80;
  di = di + 1;
loc_code_3783:
  r16[bx] = _stack16get(bp + var_6);
  r16[bx] += _stack16get(bp + var_4);
  _stack16set(OFS(bp + var_6), r16[bx]);
  if ( r16[bx] <= _stack16get(bp + var_2) ) // jbe 
    goto loc_code_379D;
  r16[bx] -= _stack16get(bp + var_2);
  _stack16set(OFS(bp + var_6), r16[bx]);
  r16[bx] = _stack16get(bp + var_A);
  di += _stack16get(bp + var_A);
loc_code_379D:
  _data8set(ADR(es,di), _data8get(ADR(es,di)) | r8[al]);
  if ( --r16[cx] )
    goto loc_code_377C;
  goto loc_code_37D5;
loc_code_37A4:
  r16[ax] = _stack16get(bp + var_4);
  r16[ax] >>= 1;
  _stack16set(OFS(bp + var_6), r16[ax]);
  sub_3801();
  r16[cx] = _stack16get(bp + var_4);
loc_code_37B2:
  di += _stack16get(bp + var_A);
  r16[bx] = _stack16get(bp + var_6);
  r16[bx] += _stack16get(bp + var_2);
  _stack16set(OFS(bp + var_6), r16[bx]);
  if ( r16[bx] <= _stack16get(bp + var_4) ) // jbe 
    goto loc_code_37D0;
  r16[bx] -= _stack16get(bp + var_4);
  _stack16set(OFS(bp + var_6), r16[bx]);
  r8[al] >>= 1;
  if ( r8[al] ) // jnz 
    goto loc_code_37D0;
  r8[al] = 0x80;
  di = di + 1;
loc_code_37D0:
  _data8set(ADR(es,di), _data8get(ADR(es,di)) | r8[al]);
  if ( --r16[cx] )
    goto loc_code_37B2;
loc_code_37D5:
  sp = bp;
  bp = _pop();
  _retn(8);
  return;
loc_code_37DB:
  sub_3801();
  r16[cx] = _stack16get(bp + var_4);
  if ( r16[cx] == 0 )
	  goto loc_code_37D5;
  //unknown_command(); // jcxz	short loc_code_37D5
loc_code_37E3:
  di += _stack16get(bp + var_A);
  _data8set(ADR(es,di), _data8get(ADR(es,di)) | r8[al]);
  if ( --r16[cx] )
    goto loc_code_37E3;
  goto loc_code_37D5;
loc_code_37ED:
  sub_3801();
  r16[cx] = _stack16get(bp + var_2);
loc_code_37F3:
  r8[al] >>= 1;
  if ( r8[al] ) // jnz 
    goto loc_code_37FA;
  r8[al] = 0x80;
  di = di + 1;
loc_code_37FA:
  _data8set(ADR(es,di), _data8get(ADR(es,di)) | r8[al]);
  if ( --r16[cx] )
    goto loc_code_37F3;
  goto loc_code_37D5;
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
  _data8set(ADR(es,di), _data8get(ADR(es,di)) | r8[al]);
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
  STAT(0x3840);
  r8[ah] = _data[0x955E];
  if ( r8[ah] == 0 ) // jz 
    goto loc_code_384A;
  return;
loc_code_384A:
  r8[ah] = _data[0x9506];
  if ( r8[ah] != 0 ) // jnz 
    goto loc_code_3854;
  return;
loc_code_3854:
  r8[ah] = _data[0x9550];
  if ( r8[ah] != 0 ) // jnz 
    goto loc_code_3866;
  _push(r16[bx]);
  _data[0x9550] = r8[al];
  sub_3914();
  r16[bx] = _pop();
  return;
loc_code_3866:
  r8[ah] = _data[0x9551];
  if ( r8[ah] != 0 ) // jnz 
    goto loc_code_3873;
  _data[0x9551] = r8[al];
  return;
loc_code_3873:
  if ( r8[al] <= _data[0x9552] ) // jbe 
    return;
  _data[0x9552] = r8[al];
}
function sub_387D()
{
  STAT(0x387D);
  r8[al] = _data[0x955E];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_389B;
  r8[al] = _data[0x9506];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_3890;
  sub_39DB();
  goto loc_code_389B;
loc_code_3890:
  _data16set(0x955F, 0);
  _data[0x955E] = 0;
loc_code_389B:
  r8[al] = _data[0x9550];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_38A3;
  return;
loc_code_38A3:
  _data[0x9557]--;
  if ( _data[0x9557] ) // jnz 
    goto loc_code_38D4;
  r8[al] = _data[0x9506];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_38B4;
  sub_39A3();
  return;
loc_code_38B4:
  r8[al] = _data[0x9551];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_38D0;
  _data[0x9550] = r8[al];
  r8[bl] = _data[0x9552];
  _data[0x9551] = r8[bl];
  _data[0x9552] = 0;
  sub_3914();
  return;
loc_code_38D0:
  sub_39A3();
  return;
loc_code_38D4:
  r16[ax] = _data16get(0x9558);
  r16[ax] += _data16get(0x955A);
  _data16set(0x9558, r16[ax]);
  r8[al] = _data[0x9553];
  if ( r8[al] == 0 ) // jz 
    goto loc_code_38FD;
  r8[bl] = _data[0x9554];
  _data[0x9554] = _data[0x9554] + 1;
  r16[bx] &= 0x0F;
  r16[bx] <<= 1;
  r16[bx] += _data16get(0x9555);
  r16[ax] = _data16get(r16[bx]);
  _data16set(0x955C, r16[ax]);
  goto loc_code_3903;
loc_code_38FD:
  _data16set(0x955C, 0);
loc_code_3903:
  r16[ax] = _data16get(0x9558);
  _data16set(0x955C, _data16get(0x955C) + r16[ax]);
  r16[ax] = _data16get(0x955C);
  _out(0x42, r8[al]);
  r8[al] = r8[ah];
  _out(0x42, r8[al]);
}
function sub_3914()
{
  STAT(0x3914);
  r8[al]--;
  r8[bl] = r8[al];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[bx] = _data16get(OFS(r16[bx] - 0x741C));
  r8[al] = _data[OFS(r16[bx] + 1)];
  _data[0x9557] = r8[al];
  if ( r16[bx] != 0x8C2C ) // jnz 
    goto loc_code_3941;
  r16[ax] = _data16get(0x9536);
  r8[ah] = r8[al];
  r8[al] = 0;
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] = - r16[ax];
  r16[ax] += 0x1F40;
  _data16set(0x8C2E, r16[ax]);
  goto loc_code_3966;
loc_code_3941:
  if ( r16[bx] != 0x8C32 ) // jnz 
    goto loc_code_3966;
  r8[al] = _data[0x1BA0];
  r16[ax] &= 0x7F;
  if ( r16[ax] <= 0x3F ) // jbe 
    goto loc_code_3957;
  r16[ax] -= 0x40;
  goto loc_code_395C;
loc_code_3957:
  r16[ax] = - r16[ax];
  r16[ax] += 0x3F;
loc_code_395C:
  r16[ax] <<= 1;
  r16[ax] <<= 1;
  r16[ax] += 0x190;
  _data16set(0x8C34, r16[ax]);
loc_code_3966:
  r16[ax] = _data16get(OFS(r16[bx] + 2));
  _data16set(0x9558, r16[ax]);
  r16[ax] = _data16get(OFS(r16[bx] + 4));
  _data16set(0x955A, r16[ax]);
  r8[bl] = _data[r16[bx]];
  _data[0x9553] = r8[bl];
  if ( (char)r8[bl] <= (char)0 ) // jle 
    goto loc_code_398F;
  r8[bl]--;
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] - 0x73A4));
  _data16set(0x9555, r16[ax]);
  _data[0x9554] = 0;
loc_code_398F:
  r8[al] = 0x0B6;
  _out(0x43, r8[al]);
  r16[ax] = _data16get(0x9558);
  _out(0x42, r8[al]);
  r8[al] = r8[ah];
  _out(0x42, r8[al]);
  r8[al] = _in(0x61);
  r8[al] |= 3;
  _out(0x61, r8[al]);
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
  STAT(0x39B8);
  _data[0x9561] = 0;
  _data16set(0x955F, 0);
  _data[0x955E] = 1;
  r8[al] = _data[0x9546];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_39D4;
  r16[ax] = 0x8DEC;
  goto loc_code_39D7;
loc_code_39D4:
  r16[ax] = 0x8D4C;
loc_code_39D7:
  _data16set(0x9562, r16[ax]);
}
function sub_39DB()
{
  STAT(0x39DB);
  _data[0x9561]--;
  if ( (char)_data[0x9561] < 0 ) // js 
    goto loc_code_39E2;
  return;
loc_code_39E2:
  _data[0x9561] = 7;
  _data[0x8C57] = 0x0E;
  _data[0x8C56] = 4;
  r16[bx] = _data16get(0x955F);
  si = _data16get(0x9562);
  r8[al] = _data[OFS(r16[bx] + si)];
  if ( r8[al] != 0x0FF ) // jnz 
    goto loc_code_3A05;
  _data[0x955E] = 0;
  return;
loc_code_3A05:
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_3A29;
  r8[al] = _data[0x9550];
  if ( r8[al] != 0 ) // jnz 
    goto loc_code_3A25;
  _data[0x8C56] = 0;
  _data[0x8C57] = 6;
  r16[bx] &= 0x1F;
  r8[al] = _data[OFS(r16[bx] - 0x71A3)];
  r8[al] -= 0x0C;
  goto loc_code_3A27;
loc_code_3A25:
  r8[al] = 0;
loc_code_3A27:
  goto loc_code_3A33;
loc_code_3A29:
  if ( r8[al] != 0x0FE ) // jnz 
    goto loc_code_3A31;
  r8[al] = 0;
  goto loc_code_3A33;
loc_code_3A31:
  r8[al] += 0x0C;
loc_code_3A33:
  sub_3A3B();
  _data16set(0x955F, _data16get(0x955F) + 1);
}
function sub_3A3B()
{
  STAT(0x3A3B);
  r8[al]--;
  if ( (char) r8[al] >= 0 ) // jns 
    goto loc_code_3A40;
  return;
loc_code_3A40:
  r8[bl] = r8[al];
  r8[bh] = 0;
  r16[bx] <<= 1;
  r16[ax] = _data16get(OFS(r16[bx] - 0x731C));
  _data16set(0x8C58, r16[ax]);
  r8[al] = 0x0F;
  _data[0x9550] = r8[al];
  sub_3914();
}
/*
  unknown_command(); // seg000		ends
  unknown_command(); // seg000		end
*/
#endif