var EGA = {
  palette :
    [0x000000, 0x0000b0, 0x00b000, 0x00b0b0, 0xb00000, 0xb000b0, 0xb0b000, 0xb0b0b0,
	   0x808080, 0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff],
  memory : null,
  getPixel : function(x, y)
  {
  	var off = y * 40 + (x >> 3);
    var mask = 0x80 >> (x & 7);
  	var b = 0;
  	var addr = this.cfgAddr + off;
  	var latch = this.memory[addr];
  	if ( latch & mask ) b |= 1;
		latch >>= 8;
  	if ( latch & mask ) b |= 2;
		latch >>= 8;
  	if ( latch & mask ) b |= 4;
		latch >>= 8;
  	if ( latch & mask ) b |= 8;
		latch >>= 8;
  	return this.palette[b];
  },
  write : function(addr, val)
  {
		var data = this.ModeOperation(val);
		var pixels = this.aLatch32[0];
		pixels &= this.full_not_map_mask;
		pixels |= (data & this.full_map_mask);
		this.aLatch32[0] = pixels;
		this.StoreLatch(addr);
  },
  read : function(addr)
  {
		this.LoadLatch(addr);
		if ( this.nReadMode == 0 )
			return this.aLatch8[this.cfgReadMapSelect];
		if ( this.nReadMode == 1 )
		{
			this.aLatch32[1] = (this.aLatch32[0] & this.arrFillTable[this.cfgDontCare]) ^ 
				this.arrFillTable[this.cfgCompare & this.cfgDontCare]; 
			return ~(this.aLatch8[4] | this.aLatch8[5] | this.aLatch8[6] | this.aLatch8[7]);
		}
		return 0;
  },
  init : function()
  {
    this.memory = new Uint32Array(0x10000*2);
    this.aLatchb = new ArrayBuffer(8);
    this.aLatch32 = new Uint32Array(this.aLatchb, 0, 2);
    this.aLatch8 = new Uint8Array(this.aLatchb, 0, 8);

		for ( var i=0; i<16; i++)
		{
			this.arrFillTable[i]=
				((i & 1) ? 0x000000ff : 0) |
				((i & 2) ? 0x0000ff00 : 0) |
				((i & 4) ? 0x00ff0000 : 0) |
				((i & 8) ? 0xff000000 : 0) ;
		}
		for ( var i=0; i<256; i++ )
		{
			this.arrExpandTable[i] = i | (i << 8)| (i <<16) | (i << 24);
		}
  },

  // Emulation
	nWriteMode : 0,
	nReadMode : 0,
	aLatchb : null,
  aLatch8 : null,
  aLatch32 : null,

	cfgAddr : 0,
	cfgReadMapSelect : 0,
	cfgBitMask : 0xff,
	cfgEnableSetReset : 0xff,
	cfgSetReset : 0xff,
	cfgDontCare : 15,
	cfgCompare : 0,
	cfgMapMask : 15,
	cfgDataRotate : 0,
	cfgRasterOp : 0,
	arrFillTable : [],
	arrExpandTable : [],

	// temp
	full_map_mask : 0xffffffff,
	full_not_map_mask : 0,
	full_bit_mask : 0xffffffff,
	full_set_reset : 0xffffffff,
	full_enable_and_set_reset : 0,
	full_enable_set_reset : 0xffffffff,
	full_not_enable_set_reset : 0xffffffff,

	SetAddrHi : function(b)
	{
		this.cfgAddr &= 0x00ff;
		this.cfgAddr |= b<<8;
	},
	SetAddrLo : function(b)
	{
		this.cfgAddr &= 0xff00;
		this.cfgAddr |= b;
	},
	SetMapMask : function(b) // 3c5.2
	{
		this.cfgMapMask = b;
		this.full_map_mask = this.arrFillTable[b & 15];
		this.full_not_map_mask = ~this.full_map_mask;
	},
	SetSR : function(b)
	{
		this.cfgSetReset = b & 0x0f;
		this.full_set_reset = this.arrFillTable[b & 0x0f];
		this.full_enable_and_set_reset = this.full_set_reset & this.full_enable_set_reset;
	},
	SetEnableSR : function(b)
	{
		this.cfgEnableSetReset = b & 0x0f;
		this.full_enable_set_reset = this.arrFillTable[b & 0x0f];
		this.full_not_enable_set_reset = ~this.full_enable_set_reset;
		this.full_enable_and_set_reset = this.full_set_reset & this.full_enable_set_reset;
	},
	SetCompare : function(b)
	{
		this.cfgCompare = b & 0xf;
	},
	SetMode : function(b)
	{
		this.nWriteMode = b & 3;
		this.nReadMode = (b >> 3) & 1;
	},
	SetDontCare : function(b)
	{
		this.cfgDontCare = b & 0xf;
	},
	SetBitMask : function(b)
	{
		this.cfgBitMask = b;
		this.full_bit_mask = this.arrExpandTable[b];
	},
	SetRotate : function(b)
	{
		this.cfgDataRotate = b & 7;
		this.cfgRasterOp = (b >> 3)&3;	
	},

	LoadLatch : function (dwAddr)
	{
    this.aLatch32[0] = this.memory[dwAddr];
	},
	StoreLatch : function(dwAddr, val)
	{
    this.memory[dwAddr] = this.aLatch32[0];
	},
	ModeOperation : function(val) 
	{
		var full;
		switch (this.nWriteMode) {
		case 0x00:
			// Write Mode 0: In this mode, the host data is first rotated as per the Rotate Count field, then the Enable Set/Reset mechanism selects data from this or the Set/Reset field. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val = ((val >> this.cfgDataRotate) | (val << (8-this.cfgDataRotate))) & 0xff;
			full = this.arrExpandTable[val];
			full = (full & this.full_not_enable_set_reset) | this.full_enable_and_set_reset;
			full = this.RasterOp(full, this.full_bit_mask);
			break;
		case 0x01:
			// Write Mode 1: In this mode, data is transferred directly from the 32 bit latch register to display memory, affected only by the Memory Plane Write Enable field. The host data is not used in this mode.
			full = this.aLatch32[0];
			break;
		case 0x02:
			//Write Mode 2: In this mode, the bits 3-0 of the host data are replicated across all 8 bits of their respective planes. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			full = this.RasterOp(this.arrFillTable[val&0xF], this.full_bit_mask);
			break;
		case 0x03:
			// Write Mode 3: In this mode, the data in the Set/Reset field is used as if the Enable Set/Reset field were set to 1111b. Then the host data is first rotated as per the Rotate Count field, then logical ANDed with the value of the Bit Mask field. The resulting value is used on the data obtained from the Set/Reset field in the same way that the Bit Mask field would ordinarily be used. to select which bits come from the expansion of the Set/Reset field and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val = ((val >> this.cfgDataRotate) | (val << (8-this.cfgDataRotate))) & 0xff;
			full = this.RasterOp(this.full_set_reset, this.arrExpandTable[val] & this.full_bit_mask);
			break;
		}
		return full;
	},
	RasterOp : function(input, mask) 
	{
		switch (this.cfgRasterOp) {
		case 0x00: // None
			return (input & mask) | (this.aLatch32[0] & ~mask);
		case 0x01: // AND
			return (input | ~mask) & this.aLatch32[0];
		case 0x02: // OR
			return (input & mask) | this.aLatch32[0];
		case 0x03: // XOR
			return (input & mask) ^ this.aLatch32[0];
		};
		return 0;
	}
};