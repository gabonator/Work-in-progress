class CWorld
{
public:
	enum {
		SpecialBegin = 0x80,
		SpecialEnd = 0xB1,

		BaseWater = 0x80,  // 0x80-0x8f
		BaseGround = 0x90, // 0x90-0x9f
		BaseStone = 0xA0,  // 0xA0-0xAf

		Ground = 0x98,
		Dirt = 0xB0,
		Track = 0xB1
	};

public:
	uint8_t* m_pMap;
	int m_nWidth;
	int m_nHeight;

	CWorld()
	{
		m_nWidth = 1024*1;
		m_nHeight = 1024*1;
		m_pMap = (uint8_t*)malloc(m_nWidth * m_nHeight);
		memset(m_pMap, Ground, m_nWidth * m_nHeight);
	}

	~CWorld()
	{
		free(m_pMap);
	}

	void Create(int nSeed)
	{
		if ( nSeed == 0 )
			nSeed = GetTickCount()|1;
		CWorldGenerator::Generate(m_pMap, m_nWidth, m_nHeight, BaseWater, nSeed); // + 0x20
	}

	void SetPixel(POINT pt, uint8_t pixel)
	{
		FixPosition(pt);
		m_pMap[pt.y * m_nWidth + pt.x] = pixel;
	}

	uint8_t GetPixel(POINT pt)
	{
		FixPosition(pt);
		return m_pMap[pt.y * m_nWidth + pt.x];
	}

	static COLORREF GetColor(uint8_t pixel)
	{
		static const COLORREF clrPalette[16] = {
			RGB(0x00, 0x00, 0x00), RGB(0x00, 0x00, 0xb0), RGB(0x00, 0xb0, 0x00), RGB(0x00, 0xb0, 0xb0),
		    RGB(0xb0, 0x00, 0x00), RGB(0xb0, 0x40, 0xb0), RGB(0xb0, 0xb0, 0x00), RGB(0xb0, 0xb0, 0xb0),
		    RGB(0x80, 0x80, 0x80), RGB(0x00, 0x00, 0xff), RGB(0x00, 0xff, 0x00), RGB(0x00, 0xff, 0xff),
		    RGB(0xff, 0x00, 0x00), RGB(0xff, 0x00, 0xff), RGB(0xff, 0xff, 0x00), RGB(0xff, 0xff, 0xff)};

		if ( pixel < SpecialBegin || pixel > SpecialEnd )
		{
			_ASSERT( pixel <= 15 );
			return clrPalette[pixel];
		}
		_ASSERT(pixel - SpecialBegin < 0x32);
		return CWorldGenerator::GetPalette()[pixel - SpecialBegin];
	}

	static COLORREF Noise(COLORREF clr, int x, int y)
	{
		static bool bFirst = true;
		static int arrNoise[32*32*4] = {0};
		if ( bFirst )
		{
			bFirst = false;
			for (int i=0; i<COUNT(arrNoise); i++)
				arrNoise[i] = rand() % 64;
		}
	
	    int i = ((x&31) + (y&31)*32)*4;
		_ASSERT( i < COUNT(arrNoise) );
		//clr &= 0xf0f0f0;
		clr += (arrNoise[i] << 16);
		clr += (arrNoise[i+1] << 8);
		clr += (arrNoise[i+2] << 0);
		return clr;
	}

	bool CanWalk(uint8_t p)
	{
		return IsGround(p) || IsWater(p) || IsDirt(p) || IsTrack(p);
	}

	bool CanFly(uint8_t p)
	{
		return IsGround(p) || IsDirt(p) || IsTrack(p);
	}

	bool IsGround(uint8_t p) { return (p&0xf0) == BaseGround; }
	bool IsWater(uint8_t p) { return (p&0xf0) == BaseWater; }
	bool IsStone(uint8_t p) { return (p&0xf0) == BaseStone; }
	bool IsDirt(uint8_t p) { return p == Dirt; }
	bool IsTrack(uint8_t p) { return p == Track; }

	void FixPosition(POINT& pt)
	{
		pt.x = (pt.x + m_nWidth) % m_nWidth;
		pt.y = (pt.y + m_nHeight) % m_nHeight;
		_ASSERT(pt.x >= 0 && pt.y >= 0);
	}

	uint8_t* GetPixels()
	{
		return m_pMap;
	}
};
