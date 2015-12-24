#include <stdint.h>
#include <string>
#include "gfx.h"
#include <algorithm>
#include <vector>

typedef int TTankBitmap[9][9];
	
TTankBitmap bmpTankAligned = 
 {{0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 3, 0, 0, 0, 0},
  {0, 0, 1, 0, 3, 0, 1, 0, 0},
  {0, 0, 1, 2, 3, 2, 1, 0, 0},
  {0, 0, 1, 2, 3, 2, 1, 0, 0},
  {0, 0, 1, 2, 2, 2, 1, 0, 0},
  {0, 0, 1, 2, 2, 2, 1, 0, 0},
  {0, 0, 1, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}};

TTankBitmap bmpTankDiagonal = 
 {{0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 2, 1, 0, 0, 0},
  {0, 0, 0, 2, 2, 2, 1, 0, 0},
  {0, 1, 2, 2, 3, 2, 2, 1, 0},
  {0, 0, 1, 2, 2, 3, 0, 0, 0},
  {0, 0, 0, 1, 2, 0, 3, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0}};

TTankBitmap bmpTankMaskAligned =  
 {{0, 0, 0, 2, 2, 2, 0, 0, 0},
  {0, 2, 2, 2, 3, 2, 2, 2, 0},
  {0, 2, 3, 1, 3, 1, 3, 2, 0},
  {0, 2, 3, 3, 3, 3, 3, 2, 0},
  {0, 2, 3, 3, 3, 3, 3, 2, 0},
  {0, 2, 3, 3, 3, 3, 3, 2, 0},
  {0, 2, 3, 3, 3, 3, 3, 2, 0},
  {0, 2, 3, 2, 2, 2, 3, 2, 0},
  {0, 2, 2, 2, 0, 2, 2, 2, 0}};

TTankBitmap bmpTankMaskDiagonal =
 {{0, 0, 0, 2, 2, 0, 0, 0, 0},
  {0, 0, 0, 1, 3, 2, 0, 0, 0},
  {0, 0, 2, 3, 3, 3, 2, 0, 0},
  {0, 2, 1, 3, 3, 3, 3, 2, 0},
  {2, 3, 3, 3, 3, 3, 3, 3, 2},
  {0, 2, 3, 3, 3, 3, 1, 2, 2},
  {0, 0, 2, 3, 3, 1, 3, 2, 0},
  {0, 0, 0, 2, 3, 2, 2, 2, 0},
  {0, 0, 0, 0, 2, 2, 0, 0, 0}};

class CTexture
{
	const int m_nWidth;
	const int m_nHeight;
	COLORREF* m_pBuffer;

public:
	enum {
		Width = 64,
		Height = 64
	};

public:
	CTexture() : m_nWidth(64), m_nHeight(64)
	{
		m_pBuffer = new COLORREF[m_nWidth*m_nHeight];
	}

	~CTexture()
	{
		delete m_pBuffer;
	}

	void Create(COLORREF clr1, COLORREF clr2)
	{
		for (int y=0; y<m_nHeight; y++)
			for (int x=0; x<m_nWidth; x++)
				m_pBuffer[y*m_nWidth + x] = GfxInterpolateColor( clr1, clr2, rand()%255 );
	}

	COLORREF PixelAt(POINT pt)
	{
		_ASSERT( pt.x >= 0 && pt.x < m_nWidth && pt.y >= 0 && pt.y < m_nHeight );
		return m_pBuffer[pt.y * m_nWidth + pt.x];
	}
};

class CWorld
{
public:
	enum {
		Ground = 0xf0,
		Dirt = 0xf1,
		Track = 0xf2,
		Stone = 0xf4,
		Water = 0xf5
	};

public:
	uint8_t m_map[1024][1024];
	int m_nWidth;
	int m_nHeight;

	CWorld()
	{
		memset(m_map, Ground, sizeof(m_map));
		m_nWidth = 1024;
		m_nHeight = 1024;
	}

	void SetPixel(POINT pt, uint8_t pixel)
	{
		FixPosition(pt);
		m_map[pt.y][pt.x] = pixel;
	}

	uint8_t GetPixel(POINT pt)
	{
		FixPosition(pt);
		return m_map[pt.y][pt.x];
	}

	void FixPosition(POINT& pt)
	{
		pt.x = (pt.x + m_nWidth) % m_nWidth;
		pt.y = (pt.y + m_nHeight) % m_nHeight;
	}
};

class CBullet
{
	POINT m_ptPosition;
	POINT m_ptVector;
	CWorld* m_pWorld;
	bool m_bShouldExplode;
	int m_nLive;

public:
	CBullet()
	{
	}

	CBullet(CWorld* pWorld, POINT ptOrigin, POINT ptVector)
	{
		m_pWorld = pWorld;
		m_ptPosition = ptOrigin;
		m_ptVector = ptVector;
		m_bShouldExplode = false;
		m_nLive = 0;
		m_bShouldExplode = CheckCollision();
	}

	bool CheckCollision()
	{
		if ( m_nLive == 0 )
			return false;

		POINT ptTest = m_ptPosition;
		if ( m_pWorld->GetPixel( ptTest ) != CWorld::Track )
 			return true;

		if ( m_nLive == 1 )
			return false;

		// tail
		ptTest.x -= m_ptVector.x;
		ptTest.y -= m_ptVector.y;
		if ( m_pWorld->GetPixel( ptTest ) != CWorld::Track )
			return true;
		return false;
	}

	void Do()
	{
		if ( m_bShouldExplode )
			return;

		Show(false);

		for (int i=0; i<2; i++)
		{
			m_nLive++;

			POINT ptSafePosition = m_ptPosition;
			m_ptPosition.x += m_ptVector.x;
			m_ptPosition.y += m_ptVector.y;
			m_pWorld->FixPosition(m_ptPosition);

			if ( CheckCollision() )
			{
				m_ptPosition = ptSafePosition;
				m_bShouldExplode = true;
				return;
			}
		}
		Show(true);
	}

	void Show(bool bShowOrClear)
	{
		POINT ptTail = m_ptPosition;
		POINT ptFront = m_ptPosition;
		ptTail.x -= m_ptVector.x;
		ptTail.y -= m_ptVector.y;

		m_pWorld->SetPixel(ptFront, bShowOrClear ? 12 : CWorld::Track);
		m_pWorld->SetPixel(ptTail, bShowOrClear ? 4 : CWorld::Track);
	}

	POINT GetPosition()
	{
		return m_ptPosition;
	}

	bool ShouldExplode()
	{
		return m_bShouldExplode;
	}
};

class CParticle
{
	CWorld* m_pWorld;
	float m_fX;
	float m_fY;

	float m_fDx;
	float m_fDy;

	int m_nCount;
	bool m_bCollision;

public:
	CParticle()
	{
	}

	CParticle(CWorld* pWorld, POINT ptCenter)
	{
		m_pWorld = pWorld;
		m_fX = (float)ptCenter.x;
		m_fY = (float)ptCenter.y;

		float fAngle = (rand()%360) * 3.141596f / 180.0f;
//		float fSpeed = ((rand()%80) +20) /100*0.5f;
		m_fDx = cos(fAngle);
		m_fDy = sin(fAngle);
		m_nCount = 4;
		m_bCollision = false; //CheckCollision();
	}

	void Do()
	{
		if ( m_bCollision )
			return;

		_ASSERT( m_nCount > 0 );
		//_ASSERT(!CheckCollision());
		Show(false);

		m_fX += m_fDx;
		m_fY += m_fDy;

		m_bCollision = CheckCollision();
		if ( m_bCollision )
			return;

		m_nCount--;
		if ( m_nCount > 0 )
			Show(true);
	}

	POINT GetPosition()
	{
		POINT pt;
		pt.x = (int)m_fX;
		pt.y = (int)m_fY;
		return pt;
	}

	bool CheckCollision()
	{
		int nPixel = m_pWorld->GetPixel(GetPosition());

		if ( nPixel == CWorld::Dirt || nPixel == CWorld::Track || nPixel == CWorld::Ground )
			return false;

		return true;
	}

	void Show(bool bShowOrClear)
	{
		m_pWorld->SetPixel(GetPosition(), bShowOrClear ? 12 : CWorld::Track);
	}

	bool ShouldDie()
	{
		return m_nCount <= 0 || m_bCollision;
	}
};

class CTank
{
	enum {
		HomeSize = 40,
		EntranceSize = 4
	};

	enum {
		Up = 8,
		Down = 2,
		Right = 6,
		Left = 4,
		UpLeft = 7,
		UpRight = 9,
		DownLeft = 1,
		DownRight = 3
	};

public:
	CWorld* m_pWorld;
	POINT m_ptPosition;
	int m_nDirection;

	void Create(CWorld* pWorld)
 	{
		m_pWorld = pWorld;
		m_ptPosition.x = m_pWorld->m_nHeight / 2;
		m_ptPosition.y = m_pWorld->m_nWidth / 2;
		m_nDirection = 8;
	}

	void DrawHome()
	{
		POINT pt;
		RECT rc;
		
		rc.top = m_ptPosition.y - HomeSize/2;
		rc.bottom = m_ptPosition.y + HomeSize/2;
		rc.left = m_ptPosition.x - HomeSize/2;
		rc.right = m_ptPosition.x + HomeSize/2;

		for (pt.y=rc.top; pt.y <= rc.bottom; pt.y++)
			for (pt.x=rc.left; pt.x <= rc.right; pt.x++)
			{
				m_pWorld->SetPixel(pt, CWorld::Track);
				if ( pt.x == rc.left || pt.x == rc.right )
					m_pWorld->SetPixel(pt, 1);
				if ( (pt.y == rc.top || pt.y == rc.bottom) && abs(pt.x - m_ptPosition.x) > EntranceSize)
					m_pWorld->SetPixel(pt, 1);
			}
	}

	void Transform(TTankBitmap& result, const TTankBitmap& sourceStraight, const TTankBitmap& sourceDiagonal, int nDirection)
	{
		switch (nDirection)
		{
		case Up:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			break;

		case Down:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_FlipVertical(result);
			break;

		case Right:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_Rotate90(result);
			break;

		case Left:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_FlipVertical(result);
			_Rotate90(result);
			break;

		case DownRight:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			break;

		case UpRight:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_FlipVertical(result);
			break;

		case UpLeft:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_Rotate90(result);
			_FlipVertical(result);
			break;

		case DownLeft:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_Rotate90(result);
			break;

		default:
			memset(result, 0, sizeof(TTankBitmap));
		}
	}

	void Draw(bool bDrawOrErase)
	{
		TTankBitmap bitmap, mask;

		Transform(bitmap, bmpTankAligned, bmpTankDiagonal, m_nDirection);
		Transform(mask, bmpTankMaskAligned, bmpTankMaskDiagonal, m_nDirection);
				
		if ( bDrawOrErase )
		{
			for (int y=0; y<9; y++)
				for (int x=0; x<9; x++)
				{
					POINT pt = m_ptPosition;
					pt.x += x - 4;
					pt.y += y - 4;
					int nPixel = mask[y][x];
					if ( nPixel == 2 || nPixel == 1 ) 
					{
						if ( m_pWorld->GetPixel(pt) == CWorld::Ground )
							m_pWorld->SetPixel(pt, CWorld::Dirt);
					}
					if ( nPixel == 3 ) 
						m_pWorld->SetPixel(pt, CWorld::Track);
				}
		}

		for (int y=0; y<9; y++)
			for (int x=0; x<9; x++)
			{
				POINT pt = m_ptPosition;
				pt.x += x - 4;
				pt.y += y - 4;
				int nPixel = bitmap[y][x];

				if ( !bDrawOrErase )
				{
					if ( nPixel != 0 )
						m_pWorld->SetPixel(pt, CWorld::Track);
				} else 
				{
					if ( nPixel != 0 )
						m_pWorld->SetPixel(pt, nPixel);
				}
			}
	}

	bool CheckObstacle(POINT pt_, int nDirection)
	{
		TTankBitmap bitmap;
		Transform(bitmap, bmpTankAligned, bmpTankDiagonal, nDirection);
				
		for (int y=0; y<9; y++)
			for (int x=0; x<9; x++)
			{
				POINT pt = pt_;
				pt.x += x - 4;
				pt.y += y - 4;
				int nPixel = bitmap[y][x];
				int nMapPixel = m_pWorld->GetPixel(pt);
				if ( nPixel != 0 && (nMapPixel != CWorld::Ground && nMapPixel != CWorld::Track && nMapPixel != CWorld::Dirt ) ) 
				{
					return false;
				}
			}

		return true;
	}

	void _FlipVertical(TTankBitmap& bitmap)
	{
		for (int y=0; y<9/2; y++)
			for( int x=0; x<9; x++)
			{
				std::swap(bitmap[y][x], bitmap[9-1-y][x]);
			}
	}

	void _Rotate90(TTankBitmap& bitmap)
	{
		int n = 9;
		for(int y=0; y<n/2; y++)
			for(int x=0; x<(n+1)/2; x++)
				_cyclic_roll(bitmap[y][x], bitmap[n-1-x][y], bitmap[n-1-y][n-1-x], bitmap[x][n-1-y]);
	}

	void _cyclic_roll(int &a, int &b, int &c, int &d)
	{
		int temp = a;
		a = b;
		b = c;
		c = d;
		d = temp;
	}

	void Move(int nDir)
	{
		if ( nDir == 5 )
		{
			Draw(true);
			return;
		}

		Draw(false);

		POINT vDirection = GetDeltaByDirection(nDir);

		POINT ptForward = m_ptPosition;
		ptForward.x += vDirection.x;
		ptForward.y += vDirection.y;

		if ( CheckObstacle(ptForward, nDir) )
		{
			m_ptPosition = ptForward;
			m_nDirection = nDir;
		}

		Draw(true);
	}

	POINT GetDeltaByDirection(int nDir)
	{
		POINT arrPos[10] = {{0, 0}, 
		{-1, +1}, {0, +1}, {+1, +1},
		{-1, 0}, {0, 0}, {+1, 0},
		{-1, -1}, {0, -1}, {+1, -1}};

		_ASSERT(nDir >= 0 && nDir < COUNT(arrPos));
		return arrPos[nDir];
	}

	int GetDirectionByDelta(int nDx, int nDy)
	{
		return (nDx+2) + (nDy+1)*3;
	}

	bool CanShoot()
	{
		static long lLastShoot = 0;
		long lTick = GetTickCount();

		if ( lTick - lLastShoot > 200 )
		{
			lLastShoot = lTick;
			return true;
		}
		return false;
	}

	CBullet GetBullet()
	{
		POINT ptOrigin = m_ptPosition;
		POINT ptVector = GetDeltaByDirection(m_nDirection);

		if ( (m_nDirection & 1) == 1 ) // diagonal firing
		{
			ptOrigin.x += ptVector.x * 2;
			ptOrigin.y += ptVector.y * 2;
		} else
		{
			ptOrigin.x += ptVector.x * 3;
			ptOrigin.y += ptVector.y * 3;
		}

		return CBullet(m_pWorld, ptOrigin, ptVector);
	}
};

class CGame 
{
	CWorld m_world;
	CTank m_tank;
	std::vector<CBullet> m_arrBullets;
	std::vector<CParticle> m_arrParticles;

	CTexture m_texGround;
	CTexture m_texDirt;
	CTexture m_texTrack;
	CTexture m_texStone;
	CTexture m_texWater;

	COLORREF m_palette[256];

	POINT m_ptViewPoint;
	int m_nPixelScaling;

public:
	void Init()
	{
		m_texGround.Create(0x005080, 0x0030a0);
		m_texTrack.Create(0x202020, 0x404040);
		m_texDirt.Create(0x404040, 0x606080);
		m_texStone.Create(0xb0b0b0, 0xc0c0c0);
		m_texWater.Create(0xff0000, 0xb00000);

		m_ptViewPoint.x = 300;
		m_ptViewPoint.y = 300;
		m_nPixelScaling = 3;

		for (int i=0; i<256; i++)
			m_palette[i] = RGB(255, 0, 255);

		m_palette[1] = RGB(0, 0, 0xff);
		m_palette[2] = RGB(0, 0, 0xb0);
		m_palette[3] = RGB(0xff, 0xff, 0xff);
		m_palette[12] = RGB(0xff, 0, 0);
		m_palette[4] = RGB(0xb0, 0, 0);

		m_tank.Create(&m_world);
		m_tank.DrawHome();
		m_tank.Draw(true);
	}

	void Do()
	{
		POINT ptVector = {0, 0};
		if ( g_dev.GetKeys()[VK_LEFT] )
			ptVector.x--;
		if ( g_dev.GetKeys()[VK_RIGHT] )
			ptVector.x++;
		if ( g_dev.GetKeys()[VK_UP] )
			ptVector.y++;
		if ( g_dev.GetKeys()[VK_DOWN] )
			ptVector.y--;

		if ( g_dev.GetKeys()[VK_SPACE] )
			if ( m_tank.CanShoot() )
				m_arrBullets.push_back( m_tank.GetBullet() );

		for (int i=0; i<(int)m_arrBullets.size(); i++)
		{
			m_arrBullets[i].Do();
			
			if ( m_arrBullets[i].ShouldExplode() )
			{
				Explode(m_arrBullets[i]);
				m_arrBullets.erase( m_arrBullets.begin() + i-- );
			}
		}

		for (int i=0; i<(int)m_arrParticles.size(); i++)
		{
			m_arrParticles[i].Do();
			if ( m_arrParticles[i].ShouldDie() )
			{
				//m_arrParticles[i].Show( false );
				m_arrParticles.erase( m_arrParticles.begin() + i-- );
			}
		}

		m_tank.Move( m_tank.GetDirectionByDelta(ptVector.x, ptVector.y) );
//		m_tank.Draw(true);

		m_ptViewPoint = m_tank.m_ptPosition;

		m_ptViewPoint.x = (m_ptViewPoint.x + m_world.m_nWidth) % m_world.m_nWidth;
		m_ptViewPoint.y = (m_ptViewPoint.y + m_world.m_nHeight) % m_world.m_nHeight;

		Blit();
	}

	void Explode(CBullet& bullet)
	{
		for (int i=0; i<10; i++)
		{
			m_arrParticles.push_back( CParticle(&m_world, bullet.GetPosition()) );
		}
	}

	void Blit()
	{
		DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();

		POINT ptMid;
		ptMid.x = g_dev.display.WindowWidth()/2;
		ptMid.y = g_dev.display.WindowHeight()/2;
//		int nGap = g_dev.display.Width() - g_dev.display.WindowWidth();
		//CTexture* pTexture = m_arrTextures[0];

//		COLORREF palette[16] = {0, RGB(0, 0xff, 0), RGB(0, 0xb0, 0), RGB(0xff, 0xff, 0x00)};

		POINT ptBase;
		ptBase.x = m_ptViewPoint.x - g_dev.display.WindowWidth() / m_nPixelScaling / 2;
		ptBase.y = m_ptViewPoint.y - g_dev.display.WindowHeight() / m_nPixelScaling / 2;
		long i = 0;
//			int dx = 0;
		int dy = 0;

		for (int y = 0; y < g_dev.display.WindowHeight(); y++, dy++)
		{
			i = y * g_dev.display.Width();

			if ( (y % m_nPixelScaling) != 0 )
			{	
				for (int x = 0; x < g_dev.display.WindowWidth(); x++, i++)
					pBuf[i] = pBuf[i - g_dev.display.Width()];
				continue;
			}
			for (int x = 0, dx = 0; x < g_dev.display.WindowWidth(); x+=m_nPixelScaling)
			{
				POINT ptCurrent, ptSubPixel;
				ptCurrent.x = ptBase.x + dx++;
				ptCurrent.y = ptBase.y + y/m_nPixelScaling;
				int nPixel = m_world.GetPixel(ptCurrent);

				ptSubPixel.x = ptCurrent.x & (CTexture::Width-1);
				ptSubPixel.y = ptCurrent.y & (CTexture::Height-1);

				COLORREF clr = RGB(255, 0, 255);
				CTexture* pTexture = NULL;
				if ( (nPixel & 0xf0) == 0xf0 )
				{
					if ( nPixel == CWorld::Dirt )
						pTexture = &m_texDirt;
					if ( nPixel == CWorld::Track )
						pTexture = &m_texTrack;
					if ( nPixel == CWorld::Ground )
						pTexture = &m_texGround;
					if ( nPixel == CWorld::Water )
						pTexture = &m_texWater;
					if ( nPixel == CWorld::Stone )
						pTexture = &m_texStone;
				}

				clr = RGB2BGR(pTexture ? pTexture->PixelAt(ptSubPixel) : m_palette[nPixel]);
				for ( int q = 0; q < m_nPixelScaling; q++ )
					pBuf[i++] = clr;
			}
		}

/*
		int nZero = 500;
		int nZeroMul = nZero*m_nPixelScaling;
		long i = 0;
		for (int y = 0; y < g_dev.display.WindowHeight(); y++, i += nGap)
		{
			for (int x = 0; x < g_dev.display.WindowWidth(); x++, i++)
			{
				POINT ptRealPixel;
				ptRealPixel.x = m_ptViewPoint.x + (x - ptMid.x + nZeroMul) / m_nPixelScaling - nZero;
				ptRealPixel.y = m_ptViewPoint.y + (y - ptMid.y + nZeroMul) / m_nPixelScaling - nZero;
				ptRealPixel.x = (ptRealPixel.x + m_world.m_nWidth) % m_world.m_nWidth;
				ptRealPixel.y = (ptRealPixel.y + m_world.m_nHeight) % m_world.m_nHeight;

				POINT ptSubPixel;
				ptSubPixel.x = ptRealPixel.x % CTexture::Width;
				ptSubPixel.y = ptRealPixel.y % CTexture::Height;

				int nPixel = m_world.m_map[ptRealPixel.y][ptRealPixel.x];

				CTexture* pTexture = NULL;
				if ( nPixel == CWorld::Dirt )
					pTexture = &m_texDirt;
				if ( nPixel == CWorld::Track )
					pTexture = &m_texTrack;
				if ( nPixel == CWorld::Ground )
					pTexture = &m_texGround;
				if ( nPixel == CWorld::Water )
					pTexture = &m_texWater;
				if ( nPixel == CWorld::Stone )
					pTexture = &m_texStone;

				pBuf[i] = RGB2BGR(pTexture ? pTexture->PixelAt(ptSubPixel) : m_palette[nPixel]);
			}
		}
		*/
	}

	uint32_t RGB2BGR(COLORREF c)
	{
		return (c&0x00ff00) | ((c&0xff)<<16) | (c>>16);
	}
};