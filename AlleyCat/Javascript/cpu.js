var _data = new Uint8Array(0x10000);
var _video = new Uint8Array(0x12000);

var ds = 0, es = 0, di = 0, cs = 0;
var ah = 0, al = 0, bh = 0, bl = 0, ch = 0, cl = 0, dh = 0, dl = 0;
var df = 0, zf = 0, cf = 0;
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
function set_ax(v)
{
  ah = v >> 8;
  al = v & 0xff;
}
function set_bx(v)
{
  bh = v >> 8;
  bl = v & 0xff;
}
function set_cx(v)
{
  ch = v >> 8;
  cl = v & 0xff;
}
function set_dx(v)
{
  dh = v >> 8;
  dl = v & 0xff;
}
function get_ax() 
{
  return (ah<<8)|al;
}
function get_bx() 
{
  return (bh<<8)|bl;
}
function get_cx() 
{
  return (ch<<8)|cl;
}
function get_dx() 
{
  return (dh<<8)|dl;
}
function _int(i)
{
  switch(i)
  {
    case 0x11: set_ax(0xb91e); return;
    case 0x10: 
      if ( ah == 0x00 ) /* set video */ return;
      if ( ah == 0x0b ) /* backgrond, palette */ return;
      break;
    case 0x1a:
      if ( ah == 0 ) 
      {
        var t = (new Date()).getTime();
//        t = Math.floor(t*65543.0/(1000.0*60.0*60.0));
        t %= 1000*60*60;
        t = Math.floor(t*18.2/1000.0);
        set_cx(0);
        set_dx(t&0xffff);
//console.log("Set time: "+get_dx().toString(16) + " " +getCallStack());
//printStackTrace();
        return;
      }
  }
  alert("Unhandled interrupt " + i.toString(16) + " ah=" + ah.toString(16));
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

function _rep_stosw()
{
	while ( get_cx() ) 
  {
    set_cx( get_cx() - 1 );
		_stosw();
  }
}

function _stosw() 
{
  if ( es == 0xb800 )
  {
    _video16set(di, get_ax());
    di+=2;
  } else
  {
    _data16set(es*16+di, get_ax());
    di+=2;
  }
}

function _lodsw() 
{
	if ( ds*16+si >= 0xb800 )
		set_ax(_video16get(ds*16+si - 0xb800)); 
	else
		set_ax(_data16get(ds*16+si)); 
	si+=2;
}

function _rep_stosb()
{
	while ( get_cx() ) 
  {
    set_cx( get_cx() - 1 );
		_stosb();
  }
}

function _stosb() 
{
  if ( es == 0xb800 )
  {
    _video[di] = al; 
    di++;
  } else
  {
    _data[es*16+di] = al; 
    di++;
  }
}

function _lodsb() 
{
	al = _data[ds*16+si]; 
	si++;
}

function _out(port, val)
{
  console.log("todo out("+port.toString(16)+","+val.toString(16)+")");
}

function _in(port)
{
  console.log("todo in("+port.toString(16)+")");
  return 0;
}

function decrement_cx()
{
  var cx = get_cx()-1;
  set_cx(cx);
  return cx;
}

function _rcr( arg, l)
{
	var ncf = arg & 1 ? 1 : 0;
	arg >>= 1;
	if ( cf )
		arg |= 128;
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

	while (get_cx() != 0) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			pto[es*16 + di] = pfrom[ds*16 + si];
			si++;
			di++;
			set_cx(get_cx()-1);
	}

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

	while (get_cx() != 0) {
			pto[es*16 + di] = pfrom[ds*16 + si];
			si+=dir;
			di+=dir;
			set_cx(get_cx()-1);
	}
	if ( pfrom == _video )
		ds = 0xb800;
	if ( pto == _video )
		es = 0xb800;
}
