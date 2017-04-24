class CEga
{
	enum {
		MemSize = 0x10000*2
	};

public:
	DWORD memory[MemSize];
	int nWriteMode;
	int nReadMode;
	union TLatch
	{
		DWORD u32Data;
		BYTE u8Data[4];
	};
	TLatch uLatch;
	//
	WORD cfgAddr;
	BYTE cfgReadMapSelect;
	BYTE cfgBitMask;
	BYTE cfgEnableSetReset;
	BYTE cfgSetReset;
	BYTE cfgDontCare;
	BYTE cfgCompare;
	BYTE cfgMapMask;
	BYTE cfgDataRotate;
	BYTE cfgRasterOp;

	DWORD arrFillTable[16];
	DWORD arrExpandTable[256];

	// temp
	DWORD full_map_mask;
	DWORD full_not_map_mask;
	DWORD full_bit_mask;
	DWORD full_set_reset;
	DWORD full_enable_and_set_reset;
	DWORD full_enable_set_reset;
	DWORD full_not_enable_set_reset;

public:
	CEga()
	{
		nWriteMode = 0;
		nReadMode = 0;
		cfgAddr = 0;

		cfgReadMapSelect = 0; // 3CF.4
		cfgBitMask = 0xff;
		cfgEnableSetReset = 0xff;
		cfgSetReset = 0xff;
		cfgDontCare = 15; // 3CF.7
		cfgCompare = 0;
		cfgMapMask = 15;
		cfgDataRotate = 0;
		cfgRasterOp = 0; // 3CF.3

		for ( int i=0; i<16; i++)
		{
			arrFillTable[i]=
				((i & 1) ? 0x000000ff : 0) |
				((i & 2) ? 0x0000ff00 : 0) |
				((i & 4) ? 0x00ff0000 : 0) |
				((i & 8) ? 0xff000000 : 0) ;
		}
		for ( int i=0; i<256; i++ )
		{
			arrExpandTable[i] = i | (i << 8)| (i <<16) | (i << 24);
		}
		full_not_enable_set_reset	= 0xffffffff;
		full_enable_set_reset		= 0xffffffff;
		full_set_reset				= 0xffffffff;
		full_map_mask				= 0xffffffff;
		full_not_map_mask			= ~full_map_mask;
		full_bit_mask				= 0xffffffff;
	}

	void SetAddrHi(BYTE b)
	{
		cfgAddr &= 0x00ff;
		cfgAddr |= ((WORD)b)<<8;
	}
	void SetAddrLo(BYTE b)
	{
		cfgAddr &= 0xff00;
		cfgAddr |= b;
	}

	void SetMapMask(BYTE b) // 3c5.2
	{
		cfgMapMask = b;
		full_map_mask = arrFillTable[b & 15];
		full_not_map_mask = ~full_map_mask;
	}

	void SetSR(BYTE b)
	{
		cfgSetReset = b & 0x0f;
		full_set_reset = arrFillTable[b & 0x0f];
		full_enable_and_set_reset = full_set_reset & full_enable_set_reset;
	}
	void SetEnableSR(BYTE b)
	{
		cfgEnableSetReset = b & 0x0f;
		full_enable_set_reset = arrFillTable[b & 0x0f];
		full_not_enable_set_reset = ~full_enable_set_reset;
		full_enable_and_set_reset = full_set_reset & full_enable_set_reset;
	}
	void SetCompare(BYTE b)
	{
		cfgCompare = b & 0xf;
	}
	void SetMode(BYTE b)
	{
		nWriteMode = b & 3;
		nReadMode = (b >> 3) & 1;
	}
	void SetDontCare(BYTE b)
	{
		cfgDontCare = b & 0xf;
	}
	void SetBitMask(BYTE b)
	{
		cfgBitMask = b;
		full_bit_mask = arrExpandTable[b];
	}
	void SetRotate(BYTE b)
	{
		cfgDataRotate = b & 7;
		cfgRasterOp = (b >> 3)&3;	

		//cfgBitMask = b;
		//full_bit_mask = arrExpandTable[b];
	}
#if 0
	BYTE Read(int addr)
	{
		if ( nReadMode == 1 )
			return 0xff;
		_ASSERT( addr >=0 && addr < 0x1ffff );
		return memory[addr];
	}
	void Write( int addr, BYTE value )
	{
		_ASSERT( addr >=0 && addr < 0x1ffff );
		memory[addr] = value;
	}

#else
	void Write(DWORD dwAddr, BYTE bWrite)
	{
		if ( dwAddr == 171 )
		{
			int f = 9;
		}
		/*
		int nPlane = 0;
		_ASSERT( nPlane < 4 );
		if ( cfgMapMask & 1 ) uLatch.u8Data[0] = bWrite;
		if ( cfgMapMask & 2 ) uLatch.u8Data[1] = bWrite;
		if ( cfgMapMask & 4 ) uLatch.u8Data[2] = bWrite;
		if ( cfgMapMask & 8 ) uLatch.u8Data[3] = bWrite;
		StoreLatch(dwAddr);
		*/
		
		/*
		if ( nWriteMode == 1 && nReadMode == 0 )
		{
			//uLatch.u32Data |= 0xaaaa00aa;
			uLatch.u32Data |= 0xff;
			StoreLatch(dwAddr);
			return;
		}*/

		DWORD data = ModeOperation(bWrite);

		TLatch pixels;
		pixels.u32Data = uLatch.u32Data;
		//pixels.u32Data = ReadLatch(dwAddr); //((DWORD*)&memory[dwAddr])[dwAddr];

		pixels.u32Data &= full_not_map_mask;
		pixels.u32Data |= (data & full_map_mask);

		uLatch.u32Data = pixels.u32Data;
		StoreLatch(dwAddr);
	}

	BYTE Read(DWORD dwAddr)
	{
		/*
		if ( nWriteMode == 1 && nReadMode == 0 )
		{
			LoadLatch(dwAddr);
			return 0;
		}*/

		_ASSERT( dwAddr < sizeof(memory) );
		LoadLatch(dwAddr); //((DWORD*)&memory[dwAddr])[dwAddr]; 
		if ( nReadMode == 0 )
			return uLatch.u8Data[cfgReadMapSelect];
		if ( nReadMode == 1 )
		{
			TLatch temp;
			temp.u32Data = (uLatch.u32Data & arrFillTable[cfgDontCare]) ^ 
				arrFillTable[cfgCompare & cfgDontCare]; 
			return ~(temp.u8Data[0] | temp.u8Data[1] | temp.u8Data[2] | temp.u8Data[3]);
		}
		_ASSERT(0);
		return 0;
	}
	void LoadLatch(DWORD dwAddr)
	{
		//TLatch l;
		_ASSERT( dwAddr < MemSize );
		uLatch.u32Data = memory[dwAddr];
		/*
		l.u8Data[0] = memory[dwAddr];
		l.u8Data[1] = memory[dwAddr+0x2000];
		l.u8Data[2] = memory[dwAddr+0x4000];
		l.u8Data[3] = memory[dwAddr+0x6000];
		*/
		//7return uLatch.u32Data;
	}
	void StoreLatch(DWORD dwAddr)
	{
		//TLatch l;
		_ASSERT( dwAddr < MemSize );
		memory[dwAddr] = uLatch.u32Data;
/*
		TLatch l;
		l.u32Data = dwData;
		memory[dwAddr] = l.u8Data[0];
		memory[dwAddr+0x2000] = l.u8Data[1];
		memory[dwAddr+0x4000] = l.u8Data[2];
		memory[dwAddr+0x6000] = l.u8Data[3];
*/
	}
#endif
	DWORD ModeOperation(BYTE val) 
	{
		DWORD full;
		switch (nWriteMode) {
		case 0x00:
			// Write Mode 0: In this mode, the host data is first rotated as per the Rotate Count field, then the Enable Set/Reset mechanism selects data from this or the Set/Reset field. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val = ((val >> cfgDataRotate) | (val << (8-cfgDataRotate)));
			full = arrExpandTable[val];
			full = (full & full_not_enable_set_reset) | full_enable_and_set_reset;
			full = RasterOp(full,full_bit_mask);
			break;
		case 0x01:
			// Write Mode 1: In this mode, data is transferred directly from the 32 bit latch register to display memory, affected only by the Memory Plane Write Enable field. The host data is not used in this mode.
			full = uLatch.u32Data;
			break;
		case 0x02:
			//Write Mode 2: In this mode, the bits 3-0 of the host data are replicated across all 8 bits of their respective planes. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			full = RasterOp(arrFillTable[val&0xF], full_bit_mask);
			break;
		case 0x03:
			// Write Mode 3: In this mode, the data in the Set/Reset field is used as if the Enable Set/Reset field were set to 1111b. Then the host data is first rotated as per the Rotate Count field, then logical ANDed with the value of the Bit Mask field. The resulting value is used on the data obtained from the Set/Reset field in the same way that the Bit Mask field would ordinarily be used. to select which bits come from the expansion of the Set/Reset field and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val=((val >> cfgDataRotate) | (val << (8-cfgDataRotate)));
			full=RasterOp(full_set_reset, arrExpandTable[val] & full_bit_mask);
			break;
		default:
			_ASSERT(0);
			break;
		}
		return full;
	}

	DWORD RasterOp(DWORD input, DWORD mask) 
	{
		switch (cfgRasterOp) {
		case 0x00: /* None */
			return (input & mask) | (uLatch.u32Data & ~mask);
		case 0x01: /* AND */
			return (input | ~mask) & uLatch.u32Data;
		case 0x02: /* OR */
			return (input & mask) | uLatch.u32Data;
		case 0x03: /* XOR */
			return (input & mask) ^ uLatch.u32Data;
		};
		return 0;
	}
};




#if 0
private:
	Bitu readHandler(PhysPt start) {
		vga.latch.d=((Bit32u*)vga.mem.linear)[start];
		switch (vga.config.read_mode) {
		case 0:
			return (vga.latch.b[vga.config.read_map_select]);
		case 1:
			VGA_Latch templatch;
			templatch.d=(vga.latch.d &	FillTable[vga.config.color_dont_care]) ^ FillTable[vga.config.color_compare & vga.config.color_dont_care];
			return (Bit8u)~(templatch.b[0] | templatch.b[1] | templatch.b[2] | templatch.b[3]);
		}
		return 0;
	}

	INLINE static Bit32u ModeOperation(Bit8u val) {
		Bit32u full;
		switch (vga.config.write_mode) {
		case 0x00:
			// Write Mode 0: In this mode, the host data is first rotated as per the Rotate Count field, then the Enable Set/Reset mechanism selects data from this or the Set/Reset field. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val=((val >> vga.config.data_rotate) | (val << (8-vga.config.data_rotate)));
			full=ExpandTable[val];
			full=(full & vga.config.full_not_enable_set_reset) | vga.config.full_enable_and_set_reset;
			full=RasterOp(full,vga.config.full_bit_mask);
			break;
		case 0x01:
			// Write Mode 1: In this mode, data is transferred directly from the 32 bit latch register to display memory, affected only by the Memory Plane Write Enable field. The host data is not used in this mode.
			full=vga.latch.d;
			break;
		case 0x02:
			//Write Mode 2: In this mode, the bits 3-0 of the host data are replicated across all 8 bits of their respective planes. Then the selected Logical Operation is performed on the resulting data and the data in the latch register. Then the Bit Mask field is used to select which bits come from the resulting data and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			full=RasterOp(FillTable[val&0xF],vga.config.full_bit_mask);
			break;
		case 0x03:
			// Write Mode 3: In this mode, the data in the Set/Reset field is used as if the Enable Set/Reset field were set to 1111b. Then the host data is first rotated as per the Rotate Count field, then logical ANDed with the value of the Bit Mask field. The resulting value is used on the data obtained from the Set/Reset field in the same way that the Bit Mask field would ordinarily be used. to select which bits come from the expansion of the Set/Reset field and which come from the latch register. Finally, only the bit planes enabled by the Memory Plane Write Enable field are written to memory.
			val=((val >> vga.config.data_rotate) | (val << (8-vga.config.data_rotate)));
			full=RasterOp(vga.config.full_set_reset,ExpandTable[val] & vga.config.full_bit_mask);
			break;
		default:
			LOG(LOG_VGAMISC,LOG_NORMAL)("VGA:Unsupported write mode %d",vga.config.write_mode);
			full=0;
			break;
		}
		return full;
	}


	void writeHandler(PhysPt start, Bit8u val) {
		Bit32u data=ModeOperation(val);
		/* Update video memory and the pixel buffer */
		VGA_Latch pixels;
		pixels.d=((Bit32u*)vga.mem.linear)[start];
		pixels.d&=vga.config.full_not_map_mask;
		pixels.d|=(data & vga.config.full_map_mask);
		((Bit32u*)vga.mem.linear)[start]=pixels.d;

		Bit8u * write_pixels=&vga.fastmem[start<<3];

		Bit32u colors0_3, colors4_7;
		VGA_Latch temp;
		temp.d=(pixels.d>>4) & 0x0f0f0f0f;
		colors0_3 =
			Expand16Table[0][temp.b[0]] |
			Expand16Table[1][temp.b[1]] |
			Expand16Table[2][temp.b[2]] |
			Expand16Table[3][temp.b[3]];
		*(Bit32u *)write_pixels=colors0_3;

		temp.d=pixels.d & 0x0f0f0f0f;
		colors4_7 =
			Expand16Table[0][temp.b[0]] |
			Expand16Table[1][temp.b[1]] |
			Expand16Table[2][temp.b[2]] |
			Expand16Table[3][temp.b[3]];
		*(Bit32u *)(write_pixels+4)=colors4_7;
	}
#endif


