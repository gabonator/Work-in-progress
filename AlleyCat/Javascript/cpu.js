
var _data = new Uint8Array(0x10000);
var _video = new Uint8Array(0x12000);

var r0 = new ArrayBuffer(8);
var r16 = new Uint16Array(r0, 0, 4);
var r8 = new Uint8Array(r0, 0, 8);
// index -> r16
var ax = 0, bx = 1, cx = 2, dx = 3;
// index -> r8
var al = 0, ah = 1, bl = 2, bh = 3, cl = 4, ch = 5, dl = 6, dh = 7;

var ds = 0, es = 0, di = 0, cs = 0;
var df = 0, zf = 0, cf = 0, af = 0;
var seg_data = 0;
stack = [];

function _push(v) 
{
  stack.push(v);
}
function _pop()
{
  return stack.pop();
}

function _int(i)
{
//  console.log("int "+i.toString(16)+ " ah="+r8[ah].toString(16)+" al="+r8[al].toString(16)+" bx="+r16[bx].toString(16));
  switch(i)
  {
    case 0x11: r16[ax] = 0xb91e; return;
    case 0x10: 
      switch ( r8[ah] )
      {
        case 0x00: cga.setmode(r8[al]); /* set video */ return;
        case 0x0b: /* backgrond, palette */ return;
        case 0x0e: cga.putchar(String.fromCharCode(r8[al])); return;
        case 0x02: cga.gotoxy(r8[dl], r8[dh]); return;
      }
      break;
    case 0x1a:
      if ( r8[ah] == 0 ) 
      {
        r16[dx] = timer.tick();
        r16[cx] = 0;
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
function _video16set(i, v)
{
  _video[i] = v & 0xff;
  _video[i+1] = v >> 8;
}
function _video16get(i, v)
{
  return _video[i] | (_video[i+1]<<8)
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
  if ( es == 0xb800 )
  {
    _video16set(di, r16[ax]);
    di+=2;
  } else
  {
    _data16set(es*16+di, r16[ax]);
    di+=2;
  }
}

function _lodsw() 
{
	if ( ds*16+si >= 0xb800 )
		r16[ax] = _video16get(ds*16+si - 0xb800); 
	else
		r16[ax] = _data16get(ds*16+si);
	si+=2;
}

function _rep_stosb()
{
	while ( r16[cx]-- ) 
		_stosb();
}

function _stosb() 
{
  if ( es == 0xb800 )
  {
    _video[di] = a8[al]; 
    di++;
  } else
  {
    _data[es*16+di] = r8[al]; 
    di++;
  }
}

function _lodsb() 
{
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
//  console.log("todo out("+port.toString(16)+","+val.toString(16)+")");
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
	if (ds == 0xb800)
	{
		pfrom = _video;
		ds = 0;
	}
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}

	while (r16[cx]--) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
	}
  r16[cx] = 0;

	if ( pfrom == _video )
		ds = 0xb800;
	if ( pto == _video )
		es = 0xb800;
}
function _rep_movsb()
{
	var dir = df == 0 ? 1 : -1;
	var pfrom = _data;
	var pto = _data;
	if (ds == 0xb800)
	{
		pfrom = _video;
		ds = 0;
	}
	if (es == 0xb800)
	{
		pto = _video;
		es = 0;
	}

	while (r16[cx]--) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si+=dir;
			di+=dir;
	}
  r16[cx] = 0;
	if ( pfrom == _video )
		ds = 0xb800;
	if ( pto == _video )
		es = 0xb800;
}

function unknown_condition()
{
  alert("fixme!");
}
function fix_code()
{
  alert("fixme!");
}

cga = {
  setmode : function(mode)
  {
    document.getElementById("terminal").value = "";
    console.log("Set mode = "+mode);
  },
  putchar : function(ch)
  {
    document.getElementById("terminal").value = document.getElementById("terminal").value + ch;
  },
  gotoxy : function(x, y)
  {
    this.putchar("\n");
  }
};

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

var GTone = {
  Play: function(freq, dur)
  {
		if ( typeof(this.ac) == "undefined" )
		{
			if ( window.AudioContext )
				this.ac = new AudioContext();
			else if ( window.webkitAudioContext )
				this.ac = new webkitAudioContext();
		 	var osc = this.ac.createOscillator();
			this.hasNote = osc.noteOn ? true : false;
  
			if ( this.ac.createGainNode )
      {
			  this.endp = this.ac.createGainNode();
        this.endp.gain.value = 0.3;
        this.endp.connect(this.ac.destination);
      } else {
        this.endp = this.ac.destination;
      }
    }
    this.Stop();

	 	this.osc = this.ac.createOscillator();
		this.osc.type = "square";
		this.osc.frequency.value = freq;
		this.osc.connect(this.endp);
		this.hasNote ? this.osc.noteOn(0) : this.osc.start(0);

    var _this = this;
		this.timeout = setTimeout( function() { _this.Stop(); }, dur );
  },
  Stop: function()
  {
    if ( this.timeout )
      clearTimeout( this.timeout );
    if ( this.osc )
    {
      this.hasNote ? this.osc.noteOff(0) : this.osc.stop(0);
      this.osc.disconnect();
    }
  }
};

function _tone(div, duration)
{
  GTone.Play(1193180 / div, duration);
}
