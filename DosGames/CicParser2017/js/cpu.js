
var memory = new Uint8Array(0x10000);
var video = new Uint8Array(0x12000);

var r0 = new ArrayBuffer(8);
var r16 = new Uint16Array(r0, 0, 4);
var r8 = new Uint8Array(r0, 0, 8);
// index -> r16
var ax = 0, bx = 1, cx = 2, dx = 3;
// index -> r8
var al = 0, ah = 1, bl = 2, bh = 3, cl = 4, ch = 5, dl = 6, dh = 7;

var _ds = 0, _es = 0, _di = 0, _cs = 0;
stack = [];

var SEG_DATA = 0;

var flags = {carry:0, zero:0, interrupt:0, direction:0, toByte:function(){return this.carry + 2*this.zero}, fromByte:function(v){this.carry=v&1; this.zero=v>>1;}};

var _counter = 0;

function _ASSERT(cond)
{
  if (!cond)
    throw "Assertion failed";
}

function ofs(o)
{
  return o & 0xffff;
}

function adr(seg, ofs)
{
  return seg * 16 + (ofs & 0xffff);
}

function _esAssume(v)
{
  return v;
}

function _push(v) 
{
  stack.push(v);
}

function _pop()
{
  return stack.pop();
}

function _rep_stosb_MemData_DirAuto()
{
  if (flags.direction == 0)
    _rep_stosb_MemData_DirForward();
  else
    _rep_stosb_MemData_DirBackward();
}

function _rep_stosb_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
    memory[_di++] = r8[al]; 
  _ASSERT(_di <= 0xffff);
}

function _rep_stosw_MemB800_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    _videoWrite16(_es, _di, r16[ax]);
    _di += 2;
  }
  _ASSERT(_di <= 0xffff);
}

function _rep_stosw_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    _memoryWrite16(_di, r16[ax]);
    _di += 2;
  }
  _ASSERT(_di <= 0xffff);
}

function _stosw_MemData_DirForward()
{
  _memoryWrite16(_di, r16[ax]);
  _di += 2;
  _ASSERT(_di <= 0xffff);
}

function _rep_movsw_MemB800_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    video[_di++] = memory[_si++];
    video[_di++] = memory[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsb_MemB800_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    video[_di++] = memory[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsb_MemData_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    memory[_di++] = memory[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsb_MemB800_MemB800_DirAuto()
{
  if (flags.direction==0)
    _rep_movsb_MemB800_MemB800_DirForward();
  else
    _rep_movsb_MemB800_MemB800_DirBackward();
}

function _rep_movsb_MemB800_MemB800_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    video[_di++] = video[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsb_MemB800_MemB800_DirBackward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    video[_di--] = video[_si--];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsw_MemData_MemB800_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    memory[_di++] = video[_si++];
    memory[_di++] = video[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsw_MemData_MemData_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    memory[_di++] = memory[_si++];
    memory[_di++] = memory[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _rep_movsb_MemData_MemB800_DirForward()
{
  for ( ; r16[cx] > 0; r16[cx]-- ) 
  {
    memory[_di++] = video[_si++];
  }
  _ASSERT(_di <= 0xffff);
  _ASSERT(_si <= 0xffff);
}

function _lodsb_MemData_DirAuto() 
{
  if (flags.dir == 0)
    _lodsb_MemData_DirForward();
  else
    _lodsb_MemData_DirBackward();
}

function _lodsb_MemData_DirForward() 
{
  r8[al] = memory[_si++]; 
}

function _lodsb_MemData_DirBackward() 
{
  r8[al] = memory[_si--]; 
  _ASSERT(_si >= 0);
}

function _lodsw_MemData_DirForward() 
{
  r8[al] = memory[_si++]; 
  r8[ah] = memory[_si++]; 
}

function _stosw_MemB800_DirForward()
{
  video[_di++] = r8[al]; 
  video[_di++] = r8[ah]; 
  _ASSERT(_di <= 0xffff);
}

function _interrupt(i)
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
        r16[dx] = timer.Read18Hz();
        r16[cx] = 0;
        return;
      }
      if ( r8[ah] == 1 ) 
      {
        _ASSERT(0);
        return;
      }
  }
  console.log("Unhandled interrupt " + i.toString(16) + " ah=" + r8[ah].toString(16));
}

function _memoryWrite16(i, v)
{
  memory[i] = v & 0xff;
  memory[i+1] = v >> 8;
}
function _memoryRead16(i, v)
{
  return memory[i] | (memory[i+1]<<8);
}
function _videoWrite16(seg, ofs, v)
{
  video[ofs] = v & 0xff;
  video[ofs+1] = v >> 8;
}
function _videoRead16(seg, ofs, v)
{
  return video[ofs] | (video[ofs+1]<<8);
}

function _videoWrite8(seg, ofs, v)
{
  video[ofs] = v;
}

function _out(port, val)
{
  timer.Out(port, val);
}

function _in(port)
{
  if (port == 0x3da)
  {
    _counter ^= 8;
    return _counter;
  }
  if ( port >= 0x40 && port <= 0x43 )
  {
    return timer.In(port);
  }
//  console.log("in("+port.toString(16)+")");
//_ASSERT(0);
  return 0;
}

function _rcr16(arg, l)
{
  var ncf = arg & 1 ? 1 : 0;
  arg >>= 1;
  if (flags.carry)
    arg |= 0x8000;
  flags.carry = ncf;
  return arg;
}

function _rcr8(arg, l)
{
  var ncf = arg & 1 ? 1 : 0;
  arg >>= 1;
  if (flags.carry)
    arg |= 0x80;
  flags.carry = ncf;
  return arg;
}

function _rcl8(arg, l)
{
  var ncf = arg & 0x80 ? 1 : 0;
  arg <<= 1;
  if (flags.carry)
    arg |= 1;
  flags.carry = ncf;
  return arg;
}

function* _DeadLoop()
{
  yield 0;
}

function _Sleep(cycles)
{
}

function _carry8(b)
{
  flags.carry = b>0xff || b<0;
  return b;
}

function _aaa()
{
  if ((r8[al] & 0x0F) > 9 /*|| (_ah == 1)*/)
  {
    r8[al] = (r8[al] + 6) & 0x0f;
    r8[ah] ++;
    flags.carry = 1;
  } else {
    flags.carry = 0;
  }
  r8[al] &= 0x0f;
}

function nullsub_1()
{
}

function nullsub_2()
{
}

function _pushf() 
{
  _push(flags.toByte());
}

function _popf()
{
  flags.fromByte(_pop());
}

var cga = {
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

var timer = {
  nReset0:0,
  nReset1:0,
  nReset2:0,
  nSpkrFrequency:0,
  wLatch0:0,

  nFreqLow:0,
  nFreqHigh:0,
  t0:0,

  Read18Hz: function()
  {
    var t = (new Date()).getTime();
    if ( this.t0 == 0 )
      this.t0 = t;
    t -= this.t0;
    t = Math.floor(t*18.2/1000.0);
    return t & 0xffff;
  },
  WriteCtl: function(arg) // 43h
  {
    var nChannel = arg >> 6;
    var nAccess = (arg >> 4) & 3; // 0 = citame, 2 = ideme zapisovat
    var nMode = (arg >> 1) & 7; // 0 = irq on count, 3 = sq wave
    var nFormat = arg & 1; // 0 = 16 bit, 1 = bcd 4 digit

    switch ( nChannel )
    {
      case 0: 
        _ASSERT(arg==0);  // nAccess = 0 -> Latch for reading
        this.wLatch0 = 0xffff-this.Read18Hz(); 
      break;
      case 1: 
        this.nReset1 = 1; 
      break;
      case 2: 
        this.nReset2 = 1; 
      break;
      default:
        _ASSERT(0);
    }
  },
  ReadCounter0: function() // 40h
  {
    var b = (this.wLatch0 >> 8) & 0xff;
    this.wLatch0 = (this.wLatch0 & 0xff) << 8;
    return b;
  },
  ReadCounter1: function() // 41h
  {
    _ASSERT(0);
    return 0;
  },
  ReadCounter2: function() // 42h
  {
    _ASSERT(0);
    return 0;
  },
  WriteCounter0: function(arg)
  {
    _ASSERT(0);
  },
  WriteCounter1: function(arg)
  {
    _ASSERT(0);
  },
  WriteCounter2: function(arg)
  {
    switch ( this.nReset2++ )
    {
      case 1: this.nFreqLow = arg; break;
      case 2: this.nFreqHigh = arg; 
      {
        var nFreqDiv = this.nFreqHigh*256 + this.nFreqLow;
        var nSpkrFrequency = 1193180/nFreqDiv;
        ///printf("Tone %d Hz\n", nSpkrFrequency);
        //Beep(nSpkrFrequency*2, 100);
      }
      break;
      default:
        _ASSERT(0);
    }
  },
  GetFrequency: function()
  {
    return nSpkrFrequency;
  },
  Out: function(port, val)
  {
    switch ( port )
    {
      case 0x43: this.WriteCtl(val); return true;
      case 0x40: this.WriteCounter0(val); return true;
      case 0x41: this.WriteCounter1(val); return true;
      case 0x42: this.WriteCounter2(val); return true;
    }
    return false;
  },
  In: function(port)
  {
    switch ( port )
    {
      case 0x40: return this.ReadCounter0();
      case 0x41: return this.ReadCounter1();
      case 0x42: return this.ReadCounter2();
    }
    _ASSERT(0);
    return 0;
  }
};

