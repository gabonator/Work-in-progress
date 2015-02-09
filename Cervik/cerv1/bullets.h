class CBullets
{
	class CBullet
	{
	public:
		float m_fX;
		float m_fY;
		float m_fAngle;
		float m_fSpeed;
		CPlayer::EExtra m_eType;
		COLORREF m_clrHit;

	public:
		CBullet(int x, int y, float fAngle, float fSpeed, CPlayer::EExtra eType)
		{
			m_fX = (float)x;
			m_fY = (float)y;
			m_fAngle = fAngle;
			m_fSpeed = fSpeed;
			m_eType = eType;
			m_clrHit = RGB(0, 0, 0);
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
				{
					m_clrHit = clr;
					return false;
				}
			}
			return true;
		}
	};

	CArray<CBullet*> m_arrBullets;

public:
	void Shoot(CCerv* pCerv, CPlayer::EExtra eType)
	{
		int x, y;
		pCerv->GetCoordsInFront( x, y, 7.0f );

		m_arrBullets.Add( new CBullet(x, y, pCerv->m_Attrs.m_fAngle, 5.0, eType) );
	}

	void Do()
	{
		for ( int i=0; i<m_arrBullets.GetSize(); i++)
		{
			CBullet* pBullet = m_arrBullets[i];
			if ( !pBullet->Advance() )
			{
				Action(pBullet);
				delete pBullet;
				m_arrBullets.RemoveAt(i--);
			}
		}
	}

	void Action(CBullet* pBullet)
	{
		switch (pBullet->m_eType)
		{
		case CPlayer::EEShooter: 
			ActionExplode(pBullet); 
			break;

		case CPlayer::EEDisease:
			ActionDisease(pBullet);
			break;

		default:
			_ASSERT(0);
		}
	}

	void ActionExplode(CBullet* pBullet)
	{
		int bx = (int)pBullet->m_fX;
		int by = (int)pBullet->m_fY;
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

	void ActionDisease(CBullet* pBullet)
	{
		/*
		for ( int i = 0; i < CGameCommon_::m_pThis->arrPlayer.GetSize(); i++ )
			if ( CGameCommon_::m_pThis->arrPlayer[i]->IsMyColor( pBullet->m_clrHit ) )
			{
				((CGameExtras*)CGameCommon_::m_pThis)->ExtraAccept(arrPlayer[i], CPlayer::EESwapControls);
			}
		*/
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
