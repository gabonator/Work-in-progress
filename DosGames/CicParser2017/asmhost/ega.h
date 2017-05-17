class CVideoAdapter
{
public:
	virtual bool PortWrite16(int port, int data) = 0;
	virtual bool Interrupt(int ah, int al, int bh, int bl) = 0;
	virtual void Write(DWORD dwAddr, BYTE bWrite) = 0;
	virtual BYTE Read(DWORD dwAddr) = 0;
	virtual DWORD GetPixel(int x, int y) = 0;
};

class CTextMode : public CVideoAdapter
{
public:
	virtual bool Interrupt(int ah, int al, int bh, int bl) override
	{
		if (ah == 0x02)
		{
			// gotoxy dl, dh
			return true;
		}
		if (ah == 0x0e)
		{
			printf("%c", al);
			return true;
		}
		return false;

	}
};

class CCga : public CTextMode
{
	enum {
		MemSize = 0x10000*2
	};

public:
	BYTE memory[MemSize];

	DWORD _cgaPalette[4];
	DWORD _cgaBackground;

	CCga()
	{
		_cgaPalette[0] = 0x000000;
		_cgaPalette[1] = 0x808080;
		_cgaPalette[2] = 0xb0b0b0;
		_cgaPalette[3] = 0xffffff;
	}

	virtual bool PortWrite16(int port, int data) override
	{
		return false;
	}

	virtual bool Interrupt(int ah, int al, int bh, int bl) override
	{
		if ( CTextMode::Interrupt( ah, al, bh, bl ) )
			return true;

		if ( ah == 0x0b )
		{
			if ( bh == 0x00 )
			{
				_cgaBackground = bl;
				return true;
			}
			if ( bh == 0x01 )
			{
				if (bl == 0x00)
				{
					_cgaPalette[0] = 0x000000;
					_cgaPalette[1] = 0x00b000;
					_cgaPalette[2] = 0xb00000;
					_cgaPalette[3] = 0xb0b000;
					return true;
				}
				if (bl == 0x01)
				{
					_cgaPalette[0] = 0x000000;
					_cgaPalette[1] = 0x00ffff;
					_cgaPalette[2] = 0xff00ff;
					_cgaPalette[3] = 0xffffff;
					return true;
				}
			}
		}
		return false;
	}

	virtual void Write(DWORD dwAddr, BYTE bWrite) override
	{
		_ASSERT(dwAddr >= 0xb800*16);
		dwAddr -= 0xb800 * 16;
		_ASSERT(dwAddr < MemSize);
		memory[dwAddr] = bWrite;
	}

	virtual BYTE Read(DWORD dwAddr) override
	{
		_ASSERT(dwAddr >= 0xb800*16);
		dwAddr -= 0xb800 * 16;
		_ASSERT(dwAddr < MemSize);
		return memory[dwAddr];
	}


	DWORD GetPixel(int x, int y) override
	{
		if ((y&1) == 0)
		{
			y /= 2;
			BYTE pix4 = memory[y*80+x/4];
			pix4 <<= (x&3)*2;
			return _cgaPalette[pix4 >> 6];
		} else
		{
			y /= 2;
			BYTE pix4 = memory[0x2000+y*80+x/4];
			pix4 <<= (x&3)*2;
			return _cgaPalette[pix4 >> 6];
		}
		return 0;
	}


};

class CEga : public CVideoAdapter
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

	virtual bool Interrupt(int ah, int al, int bh, int bl) override
	{
		return false;
	}

	virtual bool PortWrite16(int port, int data) override
	{
		if ( port == 0x3c4 )
		{
			if ( (data & 0x00ff) == 0x02 )
			{
				/*
				01 = plane 0, 02 = plane 1, 04 = plane 2, 08 = plane 3
				0f = default
				*/
				//printf("Write mask = %02x\n", data>>8 );
				SetMapMask( data>>8); // 3c5.2
				return true;
			}
		}	
		if ( port == 0x3d4 )
		{
			if ( (data & 0x00ff) == 0x0c )
			{
				SetAddrHi( data >>8 );
				return true;
			}
			if ( (data & 0x00ff) == 0x0d )
			{
				SetAddrLo( data >> 8);
				return true;
			}
		}
		if ( port == 0x3ce )
		{
			switch ( data & 0xff )
			{
			case 0x00: SetSR( data >> 8 ); return true;
			case 0x01: SetEnableSR( data >> 8 ); return true;
			case 0x02: SetCompare( data >> 8 ); return true;
			case 0x05: SetMode( data >> 8 ); return true;
			case 0x07: SetDontCare( data >> 8 ); return true;
			case 0x08: SetBitMask( data >> 8 ); return true;
			case 0x03: SetRotate( data >> 8 ); return true;
			default:
				_ASSERT(0);
			}
		}
		return false;
	}
	
	virtual DWORD GetPixel(int x, int y) override
	{
		static const DWORD pal[] = {
			0x000000, 0x0000b0, 0x00b000, 0x00b0b0, 0xb00000, 0xb000b0, 0xb0b000, 0xb0b0b0,
			0x808080, 0x0000ff, 0x00ff00, 0x00ffff, 0xff0000, 0xff00ff, 0xffff00, 0xffffff};
			/*

		static bool bloaded = false;
		static unsigned char buf[32000];
		if (!bloaded)
		{
			char strFull[128] = "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\podz1.x";
			FILE* f = fopen(strFull, "rb");
			fread(buf,	32000, 1, f);
			fclose(f);
			bloaded = true;
		}
		
		unsigned char* pl = buf + y * 320/2;
		unsigned char pix = pl[x/2];
		if ( x & 1)
			pix <<= 4;
		return pal[pix >> 4];
		*/

		BYTE* _video = (BYTE*)memory;
		DWORD off = (LONG)y * 40L + ((LONG)x / 8L);
		DWORD mem_addr = off;
		int mask = 0x80 >> (x % 8);

		BYTE b = 0;
		if ( _video[cfgAddr*4 + off*4 + 0] & mask ) b |= 1;
		if ( _video[cfgAddr*4 + off*4 + 1] & mask ) b |= 2;
		if ( _video[cfgAddr*4 + off*4 + 2] & mask ) b |= 4;
		if ( _video[cfgAddr*4 + off*4 + 3] & mask ) b |= 8;
		return pal[b];
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
	virtual void Write(DWORD dwAddr, BYTE bWrite) override
	{
		dwAddr -= 0xa000 * 16;

		DWORD data = ModeOperation(bWrite);

		TLatch pixels;
		pixels.u32Data = uLatch.u32Data;
		//pixels.u32Data = ReadLatch(dwAddr); //((DWORD*)&memory[dwAddr])[dwAddr];

		pixels.u32Data &= full_not_map_mask;
		pixels.u32Data |= (data & full_map_mask);

		uLatch.u32Data = pixels.u32Data;
		StoreLatch(dwAddr);
	}

	virtual BYTE Read(DWORD dwAddr) override
	{
		dwAddr -= 0xa000 * 16;

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


