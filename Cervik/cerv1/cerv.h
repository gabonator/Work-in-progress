#include "player.h"

class CCerv
{
public:
	class CAttrs
	{
	public:
		float m_fX, m_fY;
		float m_fAngle;
		float m_fSpeed;
		float m_fSteering;
		float m_fImmortal;
		bool m_bColliding;
		COLORREF m_color;
		int m_nId;
	} m_Attrs;

	class COrigin 
	{
	public:
		float m_fX;
		float m_fY;
		float m_fAngle;
	} m_Origin;

	int m_nPrevX, m_nPrevY;
	float m_fCrash;
	COLORREF m_clrHitColor;
	float m_fAdvanceRemain;

	static float g_fSpeedMultiply;

	enum EAction 
	{
		goNone = 0,
		goLeft = 1,
		goRight = 2,
		goAction = 4
	};

	CCerv(CPlayer* pPlayer)
	{
		m_Attrs.m_nId = pPlayer->m_nId;

		m_Attrs.m_fX = g_dev.display.Width()/2.0f;
		m_Attrs.m_fY = g_dev.display.Height()/2.0f;
		m_Attrs.m_fAngle = 0.0f;
		m_Attrs.m_fSpeed = pPlayer->m_fSpeed;
		m_Attrs.m_fSteering = pPlayer->m_fSteering;
		m_Attrs.m_color = RGB(255, 0, 255);
		m_Attrs.m_fImmortal = 0.0f;
		m_Attrs.m_bColliding = false;
		m_nPrevX = -1;
		m_nPrevY = -1;
		m_fCrash = 0;
		m_Attrs.m_color = pPlayer->m_cColor;
		m_clrHitColor = 0;
		m_fAdvanceRemain = 0;
		/*
		if ( m_Attrs.m_nId == 1 )
		{
			m_Attrs.m_fX = CFrameBuffer::Width/2;
			m_Attrs.m_fY = 50;
			m_Attrs.m_fAngle = 180;
			m_Attrs.m_color = RGB(0, 255, 0);
		}*/
	}

	void SetPosition(float x, float y, float a)
	{
		m_Attrs.m_fX = x;
		m_Attrs.m_fY = y;
		m_Attrs.m_fAngle = a;
		m_Origin.m_fX = m_Attrs.m_fX;
		m_Origin.m_fY = m_Attrs.m_fY;
		m_Origin.m_fAngle = m_Attrs.m_fAngle;
	}

	CCerv(CCerv* pParent)
	{
		m_Attrs = pParent->m_Attrs;
		m_nPrevX = -1;
		m_nPrevY = -1;
		m_fCrash = 0;

		m_Origin.m_fX = m_Attrs.m_fX;
		m_Origin.m_fY = m_Attrs.m_fY;
		m_Origin.m_fAngle = m_Attrs.m_fAngle;

		m_clrHitColor = 0;
		m_fAdvanceRemain = 0;
	}
	
	static bool CanWalk(COLORREF c)
	{
		if ( c == 0 )
			return true;
		if ( c == RGB(255, 255, 255) )
			return false;
		int r = GetRValue(c);
		int g = GetGValue(c);
		int b = GetBValue(c);
		if ( r == g && g == b )
			return true;
		return false;
	}

	void DrawCerv()
	{
		int nX = (int)m_Attrs.m_fX;
		int nY = (int)m_Attrs.m_fY;
		int nOfsX = nX-m_nPrevX, nOfsY = nY-m_nPrevY;

		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		if ( nX-2 < nLeft || nX+2 >= nRight || nY-2 < nTop || nY+2 >= nBottom )
			m_Attrs.m_bColliding = true;
		
		int nMask = 0;
		for ( int y = -2; y <= 2; y++ )
			for ( int x = -2; x <= 2; x++ )
				if ( (nMask = CTools::TestMask(x, y)) != 0 )
				{
					if ( m_nPrevX != -1 && m_nPrevY != -1 )
					{
						if ( !CTools::TestMask(x+nOfsX, y+nOfsY) )
						{
							COLORREF clr = GfxGetPixel(nX+x + nOfsX, nY+y + nOfsY);
							if ( !CanWalk(clr) )// != RGB(0, 0, 0) && clr != RGB(64, 64, 64) )
							{
								m_clrHitColor = clr;
								// collision
								if ( m_Attrs.m_fImmortal == 0 )
									m_fCrash += 1.0f;
									//m_Attrs.m_bColliding = true;
								//GfxPutPixel(nX+x + nOfsX, nY+y + nOfsY, RGB(0, 0, 255));
								continue;
							}
						}
					}

					COLORREF cCurrent = GfxGetPixel(nX+x, nY+y);
					// collision test
					//if ( cCurrent == RGB(0, 0, 255) )
//						continue;

					if ( m_Attrs.m_fImmortal > 0 )
					{
						GfxPutPixel(nX+x, nY+y, RGB(255, 255, 255));
						continue;
					}

					COLORREF clrAntialias = CTools::InterpolateColor( cCurrent, m_Attrs.m_color, nMask*20 );
					GfxPutPixel(nX+x, nY+y, clrAntialias);
				}
				
		m_nPrevX = nX;
		m_nPrevY = nY;

		if ( m_fCrash > 10.0f )
			m_Attrs.m_bColliding = true;
		if ( m_fCrash > 0 )
			m_fCrash -= 0.1f;
	}

	void AdvanceCerv(float fSteps)
	{
		m_fAdvanceRemain += fSteps;
		while (m_fAdvanceRemain >= 1.0)
		{
			AdvanceBy( 1.0f );
			m_fAdvanceRemain -= 1.0f;
			DrawCerv();
		}
#if 0
		float fDistance = /*m_Attrs.m_fSpeed * */ fSteps;
		DrawCerv();
		while (fDistance >= 1.0)
		{
			AdvanceBy( 1.0f );
			fDistance -= 1.0f;
			DrawCerv();
		}
		AdvanceBy(fDistance);
#endif
	}

	void AdvanceBy(float fDistance)
	{
		_ASSERT(m_Attrs.m_fSpeed >= 0);

		float fAngle = m_Attrs.m_fAngle / 180.0f * 3.1415926535f;
		m_Attrs.m_fX += cos(fAngle)*fDistance;
		m_Attrs.m_fY += sin(fAngle)*fDistance;
		if ( m_Attrs.m_fImmortal > 0 )
		{
			m_Attrs.m_fImmortal -= fDistance;
			if ( m_Attrs.m_fImmortal < 0 )
				m_Attrs.m_fImmortal = 0;
		}
	}

	void Command(EAction eAction)
	{
		if ( eAction & goLeft )
			m_Attrs.m_fAngle -= m_Attrs.m_fSteering;
		if ( eAction & goRight )
			m_Attrs.m_fAngle += m_Attrs.m_fSteering;
	}

	void SwapEnds()
	{
		float fTempX = m_Attrs.m_fX;
		float fTempY = m_Attrs.m_fY;
		float fTempA = m_Attrs.m_fAngle;

		m_Attrs.m_fX = m_Origin.m_fX;
		m_Attrs.m_fY = m_Origin.m_fY;
		m_Attrs.m_fAngle = m_Origin.m_fAngle + 180.0f;

		m_Origin.m_fX = fTempX;
		m_Origin.m_fY = fTempY;
		m_Origin.m_fAngle = fTempA-180.0f;
		m_nPrevX = -1;
		m_nPrevY = -1;
	}

	void EraseAround(int nRadius)
	{
		int nX, nY;
		GetCoordsInFront(nX, nY, (float)nRadius);
		int nL = nRadius*nRadius;

		for ( int y= -nRadius; y <= nRadius; y++ )
			for ( int x= -nRadius; x <= nRadius; x++ )
			{
				if ( x*x+y*y > nL )
					continue;
				GfxPutPixel(nX+x, nY+y, RGB(64, 64, 64));
			}
	}

	void GetCoordsInFront(int& x, int& y, float fDistance = 5.0f)
	{
		float fAngle = m_Attrs.m_fAngle / 180.0f * 3.1415926535f;
		x = (int)(m_Attrs.m_fX + cos(fAngle)*fDistance);
		y = (int)(m_Attrs.m_fY + sin(fAngle)*fDistance);
	}
};
