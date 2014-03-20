function optGetPixel(dwAddr, nSub)
{
	var mask = 0x80 >> (nSub & 6);
	dwAddr += nSub >> 3;
	var dwPix = EGA.memory[dwAddr];
	var b = 0;
	if ( dwPix & mask ) b |= 1;
	dwPix >>= 8;
	if ( dwPix & mask ) b |= 2;
	dwPix >>= 8;
	if ( dwPix & mask ) b |= 4;
	dwPix >>= 8;
	if ( dwPix & mask ) b |= 8;
	return b;
}

function optSetPixel(dwAddr, nSub, clr)
{
	var mask = 0x80 >> (nSub & 7);
	dwAddr += nSub >> 3;
	var dwPix = EGA.memory[dwAddr];
	var b = 0;
	dwPix &= (~mask)&0xff | (((~mask)&0xff)<<8) | (((~mask)&0xff)<<16) | (((~mask)&0xff)<<24);
	if ( clr & 1 ) dwPix |= mask;
	if ( clr & 2 ) dwPix |= mask<<8;
	if ( clr & 4 ) dwPix |= mask<<16;
	if ( clr & 8 ) dwPix |= mask<<24;
	EGA.memory[dwAddr] = dwPix;
}


function sub_C24()
{
  _push(bp);
  bp = sp;
  var _arg_0 = _stack16get(bp + arg_0);
  var _arg_2 = _stack16get(bp + arg_2);
  var _arg_4 = _stack16get(bp + arg_4);
  var _arg_6 = _stack16get(bp + arg_6);

  r16[ax] = _data16get(0x9430);
  if ( r16[ax] != 0 ) // jnz 
  {
	  r16[ax] = _arg_4;
	  r16[ax] -= _data16get(0x9528);
	  r16[ax] &= 0x3FF;
	  if ( (r16[ax] & 0x200) ) // jz 
		  r16[ax] |= 0x0FC00;

	  _arg_4 = r16[ax];
	  if ( (short)r16[ax] < (short)0 ) // jge 
	  {
		  // top-clipping
		  _arg_0 += r16[ax];
      r16[tx] = _arg_0;
		  if ( r16s[tx] < 0 || r16[tx] == 0 ) // jns 
      {
        bp = _pop();
        _retn(8);
      }

		  si += 160*(-r16[ax]);
		  r16[ax] = 0;
		  _arg_4 = r16[ax];
	  } else 
	  {
		  r16[ax] = r16[ax] + _arg_0 - 0xA0;
		  if ( r16s[ax] >= 0 ) // js 
		  {
			  r16[ax] = -r16[ax] + _arg_0;
			  if ( r16s[ax] <= 0 ) // jg 
        {
          bp = _pop();
          _retn(8);
          return;
        }
			  _arg_0 = r16[ax];
		  }
	  }
	  _arg_6 += 0x20;
	  _arg_4 += 8;
	  r16[ax] = _arg_6;
	  if ( r16s[ax] < 0x20 ) // jge 
	  {
		  r16[ax] = 0x20;
		  _arg_6 = r16[ax];
	  } else
    {
      r16[ax] += _arg_2;
	    if ( r16s[ax] > 0x120 ) // jle 
	    {
		    r16[ax] = 0x120;
		    r16[ax] -= _arg_2;
		    _arg_6 = r16[ax];
	    }
    }
  }

  _push(ds);
  _push(r16[bx]);
  r16[ax] = _arg_6;
  r16[bx] = _arg_4;
  _push(r16[cx]);
  r16[bx] <<= 3;
  r16[cx] = word_code_D93;
  if ( r16[cx] != 0x28 ) // jnz 
	  di = 0;
  else
	  di = r16[bx];
  di += r16[bx] <<= 2;
  r8[cl] = r8[al];
  r16[ax] >>= 3;
  di += r16[ax];
  r8[cl] &= 7;

  var nPixOfs = r8[cl];
  es = _data16get(0x942E);
  _pop();
  r16[cx] = _arg_2 >> 1;
  ds = _pop();
  r16[bx] = _arg_0;
  var nBPL = word_code_D93*8;
  var nBaseAdr = (es-0xa000)*16+di;

  for ( var y=0; y<r16[bx]; y++)
  {
	  var _si = si;
    var nBaseOfs = y*nBPL+nPixOfs;
	  for ( var x=0; x<r16[cx]; x++, nBaseOfs+=2)
	  {
		  var p = _data[ADR(ds, _si++)];
		  if ( (p>>4) != byte_code_D95 )
			  optSetPixel(nBaseAdr, nBaseOfs, p>>4 );
		  if ( (p&15) != byte_code_D95 )
			  optSetPixel(nBaseAdr, nBaseOfs+1, p&15 );
	  }
	  si += 0x0A0;
  }
  ds = _pop();
loc_code_D8F:
  bp = _pop();
  _retn(8);
}

function sub_3291()
{
  _push(bp);
  bp = sp;
  var dwTo = _stack16get(bp + arg_0) - 0xA000;
  var dwFrom = _stack16get(bp + arg_2) - 0xA000;
  _ASSERT( dwFrom >= 0 && dwTo >= 0 );
  dwTo <<= 4;
  dwFrom <<= 4;
  var dwOfs = 0x144;
  for ( var y = 0; y < 160; y++, dwOfs += 8)
    for ( var x = 0; x < 32; x++, dwOfs++ )
	    EGA.memory[dwTo + dwOfs] = EGA.memory[dwFrom + dwOfs];
  bp = _pop();
  _retn(4);
}
