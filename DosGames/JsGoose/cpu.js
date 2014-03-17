var _datab = new ArrayBuffer(0x40000);
var _data = new Uint8Array(_datab, 0, 0x40000);
var _datas = new Int8Array(_datab, 0, 0x40000);

//var _video = new Uint8Array(0x12000);

var _stackb = new ArrayBuffer(0x800*2);
var _stack = new Uint16Array(_stackb, 0, 0x800);
var _stacks = new Int16Array(_stackb, 0, 0x800);

var r0 = new ArrayBuffer(10);
var r16 = new Uint16Array(r0, 0, 5);
var r16s = new Int16Array(r0, 0, 5);
var r8 = new Uint8Array(r0, 0, 10);
var r8s = new Int8Array(r0, 0, 10);

// index -> r16
var ax = 0, bx = 1, cx = 2, dx = 3, tx = 4;
// index -> r8
var al = 0, ah = 1, bl = 2, bh = 3, cl = 4, ch = 5, dl = 6, dh = 7, tl = 8, th = 9;
// other registers
var ds = 0, es = 0, di = 0, cs = 0;
var df = 0, zf = 0, cf = 0, af = 0;
var bp = 0, sp = 1024;
var seg_data = 0;

function _int(i)
{
//  console.log("int "+i.toString(16)+ " ah="+r8[ah].toString(16)+" al="+r8[al].toString(16)+" bx="+r16[bx].toString(16));
  switch(i)
  {
    case 0x11: r16[ax] = 0xb91e; return;
    case 0x10: 
      switch ( r8[ah] )
      {
        case 0x00: /* set video */ return;
      }
      break;
    case 0x1a:
      if ( r8[ah] == 0 ) 
      {
        r16[dx] = timer.tick();
        r16[cx] = 0;
        return;
      }
    case 0x12:
  	  // free mem ->ax
	    r16[ax] = 0x1000;
		  return;
    case 0x21:
			if ( r8[ah] == 0x3d )
      {
			  r16[ax] = DOS.open(ds*16 + r16[dx]);
        cf = r16[ax] == 0;
        return;
      }
			if ( r8[ah] == 0x3f )
      {
			  cf = DOS.read(r16[ax], ds*16 + r16[dx], r16[cx]);
        return;
      }
			if ( r8[ah] == 0x3e )
      {
        cf = DOS.close(r16[ax]);
      }
      return;
    case 0x33:
     	if ( r16[ax] == 0 )
    	{
   			r16[ax] = 0x0000; // no mouse
   			return;
    	}
  }
  console.log("Unhandled interrupt " + i.toString(16) + " ah=" + r8[ah].toString(16));
}
function _data16set(i, v)
{
  _data[i] = v & 0xff;
  _data[i+1] = v >> 8;
}
function _data16get(i, v)
{
  return _data[i] | (_data[i+1]<<8)
}
function _data16gets(i, v)
{
  r16[tx] = _data[i] | (_data[i+1]<<8);
  return r16s[tx];
}

function _cli() {}
function _sti() {}
function _cld() { df = 0; }
function _std() { df = 1; }
function _clc() { cf = 0; }
function _stc() { cf = 1; }
function _lahf() { r8[ah] = cf; }
function _sahf() { cf = r8[ah]; }

function _aaa()
{
	if ((r8[al] & 0x0F) > 9 || (r8[af] = 1))
	{
		r8[al] = (r8[al] + 6) & 0x0f;
		r8[ah] ++;
		af = 1;
		cf = 1;
	} else {
		cf = 0;
		af = 0;
	}
}

function _rep_stosw()
{
	while ( r16[cx]-- ) 
		_stosw();
}

function _stosw() 
{
  if ( es >= 0xa000 )
  {
		_video8set(es*16+di++, r8[al]);
		_video8set(es*16+di++, r8[ah]);
    return;
  }
  _data16set(es*16+di, r16[ax]);
  di+=2;
}

function _lodsw() 
{
  _ASSERT( ds < 0xa000 );
	r16[ax] = _data16get(ds*16+si);
	si+=2;
}

function _rep_stosb()
{
  if ( es >= 0xa000 )
  {
	  while ( r16[cx]-- ) 
      _video8set(es*16+di, r8[al]);

    return;
  }
	while ( r16[cx]-- ) 
		_stosb();
}

function _stosb() 
{
  _ASSERT( es < 0xa000 );
  _data[es*16+di] = r8[al]; 
  di++;
}

function _lodsb() 
{
  _ASSERT( ds < 0xa000 );
	r8[al] = _data[ds*16+si]; 
	si++;
}

function _out(port, val)
{
  if ( port >= 0x40 && port <= 0x43 )
    timer.out(port, val);
  if ( port == 0x61 )
  {
    if ((val & 3) == 0)
      GTone.Stop();
  }

	if ( port == 0x3c4 )
	{
		if ( (val & 0x00ff) == 0x02 )
		{
			EGA.SetMapMask( val>>8); // 3c5.2
			return;
		}
	}	
	if ( port == 0x3d4 )
	{
		if ( (val & 0x00ff) == 0x0c )
		{
			EGA.SetAddrHi( val >>8 );
			return;
		}
		if ( (val & 0x00ff) == 0x0d )
		{
			EGA.SetAddrLo( val >> 8);
			return;
		}
	}
	if ( port == 0x3ce )
	{
//console.log("EGA: " + val.toString(16));
		switch ( val & 0xff )
		{
		case 0x00: EGA.SetSR( val >> 8 ); return;
		case 0x01: EGA.SetEnableSR( val >> 8 ); return;
		case 0x02: EGA.SetCompare( val >> 8 ); return;
		case 0x05: EGA.SetMode( val >> 8 ); return;
		case 0x07: EGA.SetDontCare( val >> 8 ); return;
		case 0x08: EGA.SetBitMask( val >> 8 ); return;
		case 0x03: EGA.SetRotate( val >> 8 ); return;
		}
	}

  console.log("todo out("+port.toString(16)+","+val.toString(16)+")");
}

function _in(port,x)
{
  if ( typeof(x) != "undefined" )
    alert("wrong io");
  if ( port >= 0x40 && port <= 0x43 )
    return timer.inp(port);
//  console.log("todo in("+port.toString(16)+")");
  return 0;
}

function _rcr16(arg, l)
{
	var ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	if ( cf )
		arg |= 0x8000;
	cf = ncf;
  return arg;
}

function _rcr8(arg, l)
{
	var ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	if ( cf )
		arg |= 128;
	cf = ncf;
  return arg;
}

function _rcl16(arg, l)
{
	var ncf = arg & 0x8000 ? 1 : 0;
	arg <<= 1;
	if ( cf )
		arg |= 1;
	cf = ncf;
  return arg;
}

function _rep_movsw()
{
	// [DS:SI] => [ES:DI]
	var pfrom = _data;
  var pto = _data;
  _ASSERT( es < 0xa000 && ds < 0xa000 );
	while (r16[cx]--) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
	}
  r16[cx] = 0;
}

function _movsw()
{
	var pfrom = _data;
  var pto = _data;

  _ASSERT( es < 0xa000 && ds < 0xa000 );

  pto[es*16 + di] = pfrom[ds*16 + si];
  si++;
  di++;
  pto[es*16 + di] = pfrom[ds*16 + si];
  si++;
  di++;
}

function _rep_movsb()
{
	var dir = df == 0 ? 1 : -1;

  if ( es >= 0xa000 && ds >= 0xa000 && dir == 1)
  {
    var bto = es*16;
    var bfrom = ds*16;
	  while (r16[cx]--)
	    _video8set(bto + di++, _video8get(bfrom + si++));
    r16[cx] = 0;
    return;
  }
  if ( es >= 0xa000 && dir == 1)
  {
    var bto = es*16;
    var bfrom = ds*16;
	  while (r16[cx]--)
	    _video8set(bto + di++, _data[bfrom + si++]);
    r16[cx] = 0;
    return;
  }
  _ASSERT( es < 0xa000 && ds < 0xa000 );

	var pfrom = _data;
	var pto = _data;
	while (r16[cx]--) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si+=dir;
			di+=dir;
	}
  r16[cx] = 0;
}

function unknown_condition()
{
  alert("fixme!");
}
function fix_code()
{
  alert("fixme!");
}

timer = {
  out : function(port, val)
  {
    if ( port == 0x43 )
    {
      if ( val == 0xB6 ) // play tone
      {
        this._p42 = 0;
        this._buffer42 = 0;
      } else if (val == 0x00)
      {
        this._buffer = (-this.tick()*6) &0xffff; //(-this.tick()*1000) & 0xffff;
      }
    }
    if ( port == 0x42 )
    {
      if ( this._p42 == 0 )
      {
        this._buffer42 = val;
        this._p42++;
      } else if ( this._p42 == 1 )
      {
        this._buffer42 = (val<<8) | this._buffer42;
        _tone(this._buffer42, 1000);
      }    
    }
  },
  inp : function(port)
  {
/*
		var b = this._buffer & 0xff;
		this._buffer >>= 8;
    return b;
*/
    // incorrect
		var b = this._buffer >> 8;
		this._buffer <<= 8;
		return b & 0xff;

  },
  tick : function()
  {
    var t = (new Date()).getTime();
    if ( this._t0 == 0 )
      this._t0 = t;
    t -= this._t0;
    t = Math.floor(t*18.2/1000.0);
    return t;
  },
  // private values
  _t0:0,
  _buffer:0,
  _p42:-1,
  _buffer42:0
};


function _tone(div, duration)
{
//  GTone.Play(1193180 / div, duration);
}

function STAT(x) {}
var seg_dseg = 0;

function ADR(seg,ofs) { return seg*16+(ofs&0xffff); }
function OFS(ofs) { return ofs&0xffff; }

function _ASSERT(p)
{
  if (!p) alert("Assert!");
}

// stack
function _stack16get(i)
{
  return _stack[i>>1];
}
function _stack8get(i)
{
  return _stack[i>>1] >> 8; //& 0xff;
}
function _stack16gets(i)
{
  return _stacks[i>>1];
}
function _stack16set(i, v)
{
  _stack[i>>1] = v;
}
function _push(i)
{
	_stack[sp>>1] = i;
	sp -= 2;
}
function _pop()
{
	sp += 2;
  return _stack[sp>>1];
}
function _retn(q)
{
	sp += q;
  _ASSERT( (sp>>1) >= 0 && (sp>>1) < 0x800 );
}

var var_A = -10, var_8 = -8, var_6 = -6, var_4 = -4, var_2 = -2;
var arg_0 = 4, arg_2 = 6, arg_4 = 8, arg_6 = 10, arg_8 = 12, arg_A = 14;

function _video8set(addr, val) { EGA.write( addr - 0xa000*16, val); }
function _video8get(addr, val) { return EGA.read( addr - 0xa000*16); }


function _cbw()
{
	if ( r8[al] & 0x80 )
		r8[ah] = 0xff;
	else 
		r8[ah] = 0x00;
}

function _short(x)
{
  r16[tx] = x;
  return r16s[tx];
}

function _char(x)
{
  r8[tl] = x;
  return r8s[tl];
}

function _div(dby)
{
  var res = Math.floor(r16[ax] / dby);
  var rem = r16[ax] % dby;
  r8[al] = res;
  r8[ah] = rem;
}
function _sar16(v) 
{ 
  r16[tx] = v;
  return r16s[tx] >> 1;
}
