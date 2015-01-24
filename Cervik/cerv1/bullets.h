class CBullets
{
	class CBullet
	{
	public:
		float m_fX;
		float m_fY;
		float m_fAngle;
		float m_fSpeed;

	public:
		CBullet(int x, int y, float fAngle, float fSpeed)
		{
			m_fX = (float)x;
			m_fY = (float)y;
			m_fAngle = fAngle;
			m_fSpeed = fSpeed;
		}
		
		bool Advance()
		{
			float fAdvance = m_fSpeed;
			float fAngle = m_fAngle / 180.0f * 3.1415926535f;
			float fDx = cos(fAngle);
			float fDy = sin(fAngle);

			int nLeft, nTop, nRight, nBottom;
			CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

			while (fAdvance > 0)
			{
				fAdvance -= 1.0f;
				m_fX += fDx;
				m_fY += fDy;
		
				if ( m_fX <= nLeft || m_fX >= nRight || m_fY <= nTop || m_fY >= nBottom )
					return false;
				
				//TODO!
				//m_Powerup.GetCollision( (int)pCerv->m_Attrs.m_fX, (int)pCerv->m_Attrs.m_fY );

				COLORREF clr = GfxGetPixel( (int)m_fX, (int)m_fY);
				if ( !CCerv::CanWalk ( clr ) )
				//if ( clr != RGB(0, 0, 0) && clr != RGB(64, 64, 64) )
					return false;
			}
			return true;
		}
	};

	CArray<CBullet*> m_arrBullets;

public:
	void Shoot(CCerv* pCerv)
	{
		int x, y;
		pCerv->GetCoordsInFront( x, y, 7.0f );

		m_arrBullets.Add( new CBullet(x, y, pCerv->m_Attrs.m_fAngle, 5.0) );
	}

	void Do()
	{
		for ( int i=0; i<m_arrBullets.GetSize(); i++)
		{
			CBullet* pBullet = m_arrBullets[i];
			if ( !pBullet->Advance() )
			{
				Action((int)pBullet->m_fX, (int)pBullet->m_fY);
				delete pBullet;
				m_arrBullets.RemoveAt(i--);
			}
		}
	}

	void Action(int bx, int by)
	{
		int r = 50;
		int rr = r*r;

		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		for (int y=-r; y<=r; y++)
			for (int x=-r; x<=r; x++)
			{
				int l = x*x + y*y;
				if ( l > rr )
					continue;

				int _x = bx + x;
				int _y = by + y;

				if ( _x >= nRight || _x <= nLeft || _y >= nBottom || _y <= nTop )
					continue;

				GfxPutPixel(_x, _y, RGB(64, 64, 64));
			}
	}

	void Render(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush( RGB(255, 0, 0) );

		for ( int i=0; i<m_arrBullets.GetSize(); i++)
		{
			CBullet* pBullet = m_arrBullets[i];
			RECT rc;
			rc.left = (int)pBullet->m_fX - 2;
			rc.top = (int)pBullet->m_fY - 2;
			rc.right = (int)pBullet->m_fX + 2;
			rc.bottom = (int)pBullet->m_fY + 2;

			FillRect(hdc, &rc, brush);
		}
	}
};
