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

class CPowerup
{
	class TPowerup
	{
	public:
		CPlayer::EExtra m_Type;
		RECT m_rcPosition;
		LONG m_lValidUntil;
	};

	CArray<TPowerup> m_arrPowerups;

public:
	CPowerup()
	{
	}

	static LPCTSTR GetName(CPlayer::EExtra eExtra)
	{
		switch ( eExtra )
		{
		case CPlayer::EENone: 
			return _T("???");
		case CPlayer::EEWalkThrough:
			return _T("WHI");
		case CPlayer::EEFlower:
			return _T("|||");
		case CPlayer::EESwapper:
			return _T("<->");
		case CPlayer::EEBuldozeer:	
			return _T("###");
		case CPlayer::EESlowMo:	
			return _T("---");
		case CPlayer::EETurbo:	
			return _T("+++");
		case CPlayer::EEEraser:	
			return _T(" * ");
		case CPlayer::EEShooter:	
			return _T(" ! ");
		case CPlayer::EEDouble:
			return _T("x2 ");
			/*
	EEShooter = 3,			// vystreli a spravi dieru, 3x
	EERespawn = 7,			// objavi sa niekde inde na mape
	EEShield = 8,			// vie sa prerazit cez 40 pixelov, automaticky aktivovane
	EECrosser = 9,			// moze prechadzat sam cez seba		
	*/
		}
		return _T("???");
	}

	static void Render(HDC hdc, CPlayer::EExtra eType, RECT r)
	{
		static HBRUSH brush = NULL;
		if ( brush == NULL )
			brush = CreateSolidBrush(RGB(255, 255, 0) );

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));

		FillRect(hdc, &r, brush);
		DrawText(hdc, GetName(eType), -1, 
			&r, DT_CENTER | DT_SINGLELINE | DT_VCENTER );
	}

	void Render(HDC hdc)
	{
		for ( int i=0; i<m_arrPowerups.GetSize(); i++)
			Render(hdc, m_arrPowerups[i].m_Type, m_arrPowerups[i].m_rcPosition);
	}

	void Do()
	{
		if ( rand() % 200 == 0 )
		{
			if ( m_arrPowerups.GetSize() < 10 )
				AddRandom();
		}

		LONG lTick = GetTickCount();
		for ( int i=0; i<m_arrPowerups.GetSize(); i++)
			if ( lTick > m_arrPowerups[i].m_lValidUntil )
				m_arrPowerups.RemoveAt(i--);
	}

	void AddRandom()
	{
		CPlayer::EExtra eType = CPlayer::EENone;
		switch (rand()%9)
		{
		case 0: eType = CPlayer::EEWalkThrough; break;
		case 1: eType = CPlayer::EEFlower; break;
		case 2: eType = CPlayer::EESwapper; break;
		case 3: eType = CPlayer::EEBuldozeer; break;
		case 4: eType = CPlayer::EESlowMo; break;
		case 5: eType = CPlayer::EETurbo; break;
		case 6: eType = CPlayer::EEEraser; break;
		case 7: eType = CPlayer::EEShooter; break;
		case 8: eType = CPlayer::EEDouble; break;
		}

		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		int nWidth = 30;
		int nHeight = 30;

		TPowerup powerup;
		powerup.m_Type = eType;
		powerup.m_rcPosition.left = nLeft + (rand()%(nRight-nLeft-nWidth));
		powerup.m_rcPosition.top = nTop + (rand()%(nBottom-nTop-nHeight));
		powerup.m_rcPosition.right = powerup.m_rcPosition.left + nWidth;
		powerup.m_rcPosition.bottom = powerup.m_rcPosition.top + nHeight;
		powerup.m_lValidUntil = GetTickCount() + 20000;

		m_arrPowerups.Add(powerup);
	}

	CPlayer::EExtra GetCollision(int x, int y)
	{
		for ( int i=0; i<m_arrPowerups.GetSize(); i++)
		{
			RECT rect = m_arrPowerups[i].m_rcPosition;
			if ( x < rect.left || x > rect.right || y < rect.top || y > rect.bottom )
				continue;

			CPlayer::EExtra eType = m_arrPowerups[i].m_Type;
			m_arrPowerups.RemoveAt(i);
			return eType;
		}
		return CPlayer::EENone;
	}

};

class CEraser
{
	struct TPoint
	{
		TPoint() {}
		TPoint(int _x, int _y, int _ttl) : x(_x), y(_y), ttl(_ttl) {}
		int x, y, ttl;
	};

public:

	CArray<TPoint> arrCache;

	CEraser()
	{
		arrCache.SetSize(0, 2000);
	}

	void Start(int x, int y)
	{
		CArray<TPoint> arrTemp;
		arrTemp.Copy(arrCache);
		arrCache.RemoveAll();
		
		Add(x, y, 800);
		Do(100);

		arrCache.Append(arrTemp);
	}

	void Add(int x, int y, int ttl)
	{
		GfxPutPixel(x, y, RGB(0, 0, 0));
		arrCache.Add( TPoint(x, y, ttl ) );
	}

	bool Erasable(COLORREF c)
	{
		return (c != RGB(0, 0, 0)) && (c != RGB(255, 255, 255));
	}

	void Do(int nPasses = 5)
	{
		for ( int t = 0; t < nPasses; t++ )
		{
			if ( arrCache.GetSize() == 0 )
				return;

			int nPrevCount = arrCache.GetSize();
			int i = rand() % nPrevCount;

			TPoint p = arrCache[i];
			if ( p.ttl > 0 )
			{
				if ( Erasable( GfxGetPixel( p.x - 1, p.y ) ) ) Add(p.x-1, p.y, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x + 1, p.y ) ) ) Add(p.x+1, p.y, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x, p.y - 1 ) ) ) Add(p.x, p.y-1, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x, p.y + 1 ) ) ) Add(p.x, p.y+1, p.ttl-1);
			}

			if ( arrCache.GetSize() == nPrevCount ) 
			{
				arrCache.RemoveAt( i );
			} else
			{
				TPoint pLast = arrCache.GetAt( arrCache.GetSize() - 1 );
				arrCache.SetSize(arrCache.GetSize()-1);
				arrCache.SetAt(i, pLast);
			}	
		}
	}
};

class CGame 
{
public:
	CArray<CCerv*> arrCerv;
	CArray<CPlayer*> arrPlayer;
	CEraser m_Eraser;
	CPowerup m_Powerup;
	CBullets m_Bullets;

	CGame()
	{
	}

	~CGame()
	{
		Reset();
	}

	void Reset()
	{
		for ( int i = 0; i < arrCerv.GetSize(); i++ )
			delete arrCerv[i];
		arrCerv.RemoveAll();

		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
			delete arrPlayer[i];
		arrPlayer.RemoveAll();
	}

	void Init()
	{
		arrPlayer.Add( new CPlayer(0) );
		arrPlayer.Add( new CPlayer(1) );
		arrPlayer.Add( new CPlayer(2) );
		NextRound();
	}

	void RemoveCervs()
	{
		for ( int i = 0; i < arrCerv.GetSize(); i++ )
			delete arrCerv[i];
		arrCerv.RemoveAll();
	}

	void NextRound()
	{
		CCerv::g_fSpeedMultiply = 1.0f;
		RemoveCervs();
		//Reset();
		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
		{
			arrCerv.Add( new CCerv( arrPlayer[i] ) ); //arrPlayer[i]->m_nId ) );
			arrPlayer[i]->m_bAlive = true;
		}

		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );
		int nCenterX = (nLeft + nRight)/2, nCenterY = (nTop + nBottom)/2;
		int nRadius = (nBottom - nTop)/6;
		float fHeading = 0;
		float fRotation = (float)(rand()%360);

		if (rand()%2 == 0)
		{
			fHeading = 180;
			nRadius *= 2;
		}

		for ( int i = 0; i < arrCerv.GetSize(); i++ )
		{
			CCerv* pCerv = arrCerv[i];
			float a = 360 * i / arrCerv.GetSize() + fRotation;

			float fAngle = a*3.141592f/180.0f;

			float x = nCenterX + nRadius * cos(fAngle);
			float y = nCenterY + nRadius * sin(fAngle);

			pCerv->SetPosition(x, y, a + fHeading);
		}

		ResetMap();
	}

	void ResetMap()
	{
		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		GfxClear(RGB(0, 0, 0));
		GfxLine( nLeft, nTop, nRight, nTop, RGB(255, 255, 255) );
		GfxLine( nRight, nTop, nRight, nBottom, RGB(255, 255, 255) );
		GfxLine( nRight, nBottom, nLeft, nBottom, RGB(255, 255, 255) );
		GfxLine( nLeft, nBottom, nLeft, nTop, RGB(255, 255, 255) );
	}

	void Do()
	{
		int *pKeys = g_dev.GetKeys();
		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
		{
			CPlayer* pPlayer = arrPlayer[i];
			pPlayer->m_nCurrentKey = 0;

			if ( pKeys[pPlayer->m_nKeyLeft] )
				pPlayer->m_nCurrentKey |= CCerv::goLeft;
			if ( pKeys[pPlayer->m_nKeyRight] )
				pPlayer->m_nCurrentKey |= CCerv::goRight;
			if ( pKeys[pPlayer->m_nKeyAction] )
				pPlayer->m_nCurrentKey |= CCerv::goAction;

			bool bAction = ( (pPlayer->m_nCurrentKey & CCerv::goAction) && 
				 !(pPlayer->m_nLastKey & CCerv::goAction) );
			pPlayer->m_nLastKey = pPlayer->m_nCurrentKey;

			if ( bAction )
				ExtraActivate(pPlayer);

			if ( pPlayer->m_nExtraActivated != CPlayer::EENone )
			{
				ExtraDo(pPlayer);
			}
		}

		m_Eraser.Do();

		for ( int i = 0; i < arrCerv.GetSize(); i++ )
		{
			CCerv* pCerv = arrCerv[i];
			CPlayer* pPlayer = arrPlayer[pCerv->m_Attrs.m_nId];

			//pCerv->DrawCerv();
			pCerv->AdvanceCerv(2.0f * CCerv::g_fSpeedMultiply * pCerv->m_Attrs.m_fSpeed);
			//pCerv->DrawCerv();
			//pCerv->AdvanceCerv();

			if ( pCerv->m_Attrs.m_bColliding )
			{
				pCerv->DrawCerv();
				CervKilled(pPlayer, pCerv);

				delete pCerv;
				arrCerv.RemoveAt(i);
				i--;
				continue;
			}

			pCerv->Command( (CCerv::EAction)pPlayer->m_nCurrentKey );

			CPlayer::EExtra eType = m_Powerup.GetCollision( (int)pCerv->m_Attrs.m_fX, (int)pCerv->m_Attrs.m_fY );
			if ( eType != CPlayer::EENone )
				ExtraAccept(pPlayer, eType);
		}
		
		if ( arrCerv.GetSize() == 0 )
		{
			RoundFinished();
			NextRound();
		}
		
		m_Powerup.Do();
		m_Bullets.Do();
		Fade();
	}

	void RoundFinished()
	{
		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
		{
			CPlayer* pPlayer = arrPlayer[i];
			pPlayer->m_nTotalScore += pPlayer->m_nScore;
			pPlayer->m_nScore = 0;
		}
	}

	void CervKilled(CPlayer* pPlayer, CCerv* pCerv)
	{
		for ( int i = 0; i < arrCerv.GetSize(); i++ )
			if ( arrCerv[i] != pCerv && arrCerv[i]->m_Attrs.m_nId == pPlayer->m_nId )
				return;

		// zomrel mu posledny cerv, kazdemu daj 1 bod
		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
			if ( arrPlayer[i]->IsAlive() && arrPlayer[i]->m_nId != pPlayer->m_nId )
				arrPlayer[i]->m_nScore++;

		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
			if ( arrPlayer[i]->IsAlive() && arrPlayer[i]->IsMyColor( pCerv->m_clrHitColor ) )
				arrPlayer[i]->m_nScore++;

		pPlayer->m_bAlive = false;
		CCerv::g_fSpeedMultiply += 0.2f;
	}

	void Fade()
	{
		//return;
		COLORREF c0 = RGB(64, 64, 64);
		COLORREF c1 = RGB(32, 32, 32);
		COLORREF c2 = RGB(16, 16, 16);
		COLORREF c3 = RGB(0, 0, 0);

		DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
//	return pBuf[y*CFrameBuffer::Width+x];

		for (int y=0; y< CFrameBuffer::Height; y++)
			for (int x=0; x< CFrameBuffer::Width; x++, pBuf++)
			{
				COLORREF c = *pBuf;
				if ( c != 0 && c != RGB(255, 255, 255) && GetRValue(c) == GetGValue(c) && GetGValue(c) == GetBValue(c) )
				{
					if ( GetRValue(c) >= 0x02 )
						c -= 0x020202;
					else 
						c = 0;
					*pBuf = c;
				}
			}
	}

	void ResetSpeeds()
	{
		for ( int i = 0; i < arrCerv.GetSize(); i++ )
		{
			CCerv* pCerv = arrCerv[i];
			CPlayer* pPlayer = arrPlayer[pCerv->m_Attrs.m_nId];
			pCerv->m_Attrs.m_fSpeed = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSpeed;
			pCerv->m_Attrs.m_fSteering = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSteering;
		}
	}

	int RandomNumber(int nLow, int nHigh)
	{
		return nLow + rand() % (nHigh-nLow+1);
	}

	void ExtraAccept(CPlayer* pPlayer, CPlayer::EExtra eType)
	{
		if ( eType == CPlayer::EEDouble )
		{
			if ( pPlayer->m_nExtraNewDuration > 0 )
				pPlayer->m_nExtraNewDuration *= 2;
			if ( pPlayer->m_nExtraNewCount > 0 )
				pPlayer->m_nExtraNewCount *= 2;
			return;
		}

		if ( eType == CPlayer::EEEraser && pPlayer->m_nExtraActivated == CPlayer::EEEraser )
		{
			pPlayer->m_nExtraAvailable = eType;
			pPlayer->m_nExtraNewCount = 1;
			return;
		}

		pPlayer->m_nExtraAvailable = eType;
		pPlayer->m_nExtraNewDuration = 0;
		pPlayer->m_nExtraNewCount = 0;

		switch ( eType )
		{
			case CPlayer::EEEraser:
				ExtraActivate(pPlayer);
				pPlayer->m_nExtraAvailable = CPlayer::EENone;
			break;
			case CPlayer::EEWalkThrough:
				pPlayer->m_nExtraNewDuration = 1000*RandomNumber(3, 15);
			break;
			case CPlayer::EEFlower:
				pPlayer->m_nExtraNewCount = 1;
			break;
			case CPlayer::EEShooter:
				pPlayer->m_nExtraNewCount = 5;
			break;
			case CPlayer::EEBuldozeer:
				pPlayer->m_nExtraNewDuration = 1000*RandomNumber(3, 15);
			break;
			case CPlayer::EESwapper:
				pPlayer->m_nExtraNewCount = -1;
			break;
			case CPlayer::EESlowMo:
				pPlayer->m_nExtraNewDuration = 5000;
				break;
			case CPlayer::EETurbo:
				pPlayer->m_nExtraNewDuration = 1000*RandomNumber(3, 15);
				break;
		}
	}

	void ExtraDo(CPlayer* pPlayer)
	{
		if ( pPlayer->m_nExtraActivated == CPlayer::EENone )
			return;

		if ( pPlayer->m_nExtraValidUntil && (int)GetTickCount() > pPlayer->m_nExtraValidUntil )
		{
			switch ( pPlayer->m_nExtraActivated )
			{
				case CPlayer::EESlowMo:
					if ( pPlayer->m_fExtraCounter < 1.0f )
						pPlayer->m_fExtraCounter += 0.01f;

					if ( pPlayer->m_fExtraCounter > 1.0f )
					{
						pPlayer->m_fExtraCounter = 1.0f;
						ResetSpeeds();
						break;
					}

					for ( int i = 0; i < arrCerv.GetSize(); i++ )
					{
						CCerv* pCerv = arrCerv[i];
						if ( pCerv->m_Attrs.m_nId != pPlayer->m_nId )
						{
							pCerv->m_Attrs.m_fSpeed = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSpeed * pPlayer->m_fExtraCounter;
							pCerv->m_Attrs.m_fSteering = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSteering * pPlayer->m_fExtraCounter;
						}
					}

					return;

				case CPlayer::EETurbo:
					if ( pPlayer->m_fExtraCounter > 1.0f )
						pPlayer->m_fExtraCounter -= 0.04f;
					if ( pPlayer->m_fExtraCounter < 1.0f )
					{
						pPlayer->m_fExtraCounter = 1.0;
						ResetSpeeds();
						break;
					}

					for ( int i = 0; i < arrCerv.GetSize(); i++ )
					{
						CCerv* pCerv = arrCerv[i];
						if ( pCerv->m_Attrs.m_nId == pPlayer->m_nId )
						{
							pCerv->m_Attrs.m_fSpeed = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSpeed * pPlayer->m_fExtraCounter;
							pCerv->m_Attrs.m_fSteering = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSteering * pPlayer->m_fExtraCounter;
						}
					}
					return;
			}

			pPlayer->m_nExtraActivated = CPlayer::EENone;
			pPlayer->m_nExtraValidUntil = 0;

			return;
		}

		switch ( pPlayer->m_nExtraActivated )
		{
			case CPlayer::EEBuldozeer:
				pPlayer->m_fExtraCounter += pPlayer->m_fSpeed;

				if ( pPlayer->m_fExtraCounter < 10.0f )
					break;
				pPlayer->m_fExtraCounter -= 10.0f;

				for ( int i = 0; i < arrCerv.GetSize(); i++ )
				{
					CCerv* pCerv = arrCerv[i];
					if ( pCerv->m_Attrs.m_nId == pPlayer->m_nId )
						pCerv->EraseAround(25);
				}
				break;

			case CPlayer::EESlowMo:
				if ( pPlayer->m_fExtraCounter > 0.0f )
					pPlayer->m_fExtraCounter -= 0.01f;
				if ( pPlayer->m_fExtraCounter < 0.0f )
					pPlayer->m_fExtraCounter = 0.0f;

				for ( int i = 0; i < arrCerv.GetSize(); i++ )
				{
					CCerv* pCerv = arrCerv[i];
					if ( pCerv->m_Attrs.m_nId != pPlayer->m_nId )
					{
						pCerv->m_Attrs.m_fSpeed = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSpeed * pPlayer->m_fExtraCounter;
						pCerv->m_Attrs.m_fSteering = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSteering * pPlayer->m_fExtraCounter;
					}
				}
				break;

			case CPlayer::EETurbo:
				if ( pPlayer->m_fExtraCounter < 2.0f )
					pPlayer->m_fExtraCounter += 0.04f;
				if ( pPlayer->m_fExtraCounter > 2.0f )
					pPlayer->m_fExtraCounter = 2.0f;

				for ( int i = 0; i < arrCerv.GetSize(); i++ )
				{
					CCerv* pCerv = arrCerv[i];
					if ( pCerv->m_Attrs.m_nId == pPlayer->m_nId )
					{
						pCerv->m_Attrs.m_fSpeed = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSpeed * pPlayer->m_fExtraCounter;
						pCerv->m_Attrs.m_fSteering = arrPlayer[pCerv->m_Attrs.m_nId]->m_fSteering * pPlayer->m_fExtraCounter;
					}
				}
				break;

			case CPlayer::EEWalkThrough:
				for ( int i = 0; i < arrCerv.GetSize(); i++ )
				{
					CCerv* pCerv = arrCerv[i];
					if ( pCerv->m_Attrs.m_nId == pPlayer->m_nId )
						pCerv->m_Attrs.m_fImmortal = 10.0f;
				}
				break;

			case CPlayer::EEEraser:
				for ( int i = 0; i < arrCerv.GetSize(); i++ )
				{
					CCerv* pCerv = arrCerv[i];
					if ( pCerv->m_Attrs.m_nId != pPlayer->m_nId )
						continue;

					int x, y;
					pCerv->GetCoordsInFront(x, y);
					if ( GfxGetPixel( x, y ) != RGB(0, 0, 0) && GfxGetPixel( x, y ) != RGB(64, 64, 64) )
					{
						pPlayer->m_nExtraActivated = CPlayer::EENone;
						//pCerv->m_Attrs.m_fImmortal = 15.0f;
						m_Eraser.Start(x, y);
						if ( pPlayer->m_nExtraAvailable == CPlayer::EEEraser )
						{
							pPlayer->m_nExtraActivated = CPlayer::EEEraser;
							pPlayer->m_nExtraNewCount--;
							if ( pPlayer->m_nExtraNewCount == 0 )
								pPlayer->m_nExtraAvailable = CPlayer::EENone;							
						}
					}
				}
				break;

			default:
				break;
		}

	}

	void ExtraActivate(CPlayer* pPlayer)
	{
		int nCervCount = arrCerv.GetSize();
		for ( int i = 0; i < nCervCount; i++ )
		{
			CCerv* pCerv = arrCerv[i];
			if ( pCerv->m_Attrs.m_nId != pPlayer->m_nId )
				continue;

			switch ( pPlayer->m_nExtraAvailable )
			{
			case CPlayer::EENone:
				break;

			case CPlayer::EEWalkThrough:
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = GetTickCount() + pPlayer->m_nExtraNewDuration;
				pPlayer->m_nExtraAvailable = CPlayer::EENone;
				break;

			case CPlayer::EEFlower:
				{
					pPlayer->m_nExtraCount = pPlayer->m_nExtraNewCount;
					CCerv* pLeftCerv = new CCerv(pCerv);
					CCerv* pRightCerv = new CCerv(pCerv);
					pCerv->m_Attrs.m_fImmortal = 15;
					pLeftCerv->m_Attrs.m_fAngle -= 30;
					pLeftCerv->m_Attrs.m_fImmortal = 15;
					pRightCerv->m_Attrs.m_fAngle += 30;
					pRightCerv->m_Attrs.m_fImmortal = 15;
					arrCerv.Add( pLeftCerv );
					arrCerv.Add( pRightCerv );
				}
				break;

			case CPlayer::EESwapper:
				pPlayer->m_nExtraCount = pPlayer->m_nExtraNewCount;
				pCerv->SwapEnds();
				break;

			case CPlayer::EEBuldozeer:	
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = GetTickCount() + pPlayer->m_nExtraNewDuration;
				pPlayer->m_nExtraAvailable = CPlayer::EENone;
				pPlayer->m_fExtraCounter = 0;
				break;

			case CPlayer::EESlowMo:	
				ResetSpeeds();
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = GetTickCount() + pPlayer->m_nExtraNewDuration;
				pPlayer->m_nExtraAvailable = CPlayer::EENone;
				pPlayer->m_fExtraCounter = 1.0;
				break;

			case CPlayer::EETurbo:	
				ResetSpeeds();
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = GetTickCount() + pPlayer->m_nExtraNewDuration;
				pPlayer->m_fExtraCounter = 1.0;
				pPlayer->m_nExtraAvailable = CPlayer::EENone;
				break;

			case CPlayer::EEEraser:	
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = 0;
				break;

			case CPlayer::EEShooter:
				/*pPlayer->m_nExtraCount = pPlayer->m_nExtraNewCount*/;
				m_Bullets.Shoot( pCerv );
				break;

			default:
				break;
				/*
		EEShooter = 3,			// vystreli a spravi dieru, 3x
		EERespawn = 7,			// objavi sa niekde inde na mape
		EEShield = 8,			// vie sa prerazit cez 40 pixelov, automaticky aktivovane
		EECrosser = 9,			// moze prechadzat sam cez seba
		
		*/
			}
			if ( pPlayer->m_nExtraNewCount > 0 )
			{
				pPlayer->m_nExtraNewCount--;
				if ( pPlayer->m_nExtraNewCount == 0 )
					pPlayer->m_nExtraAvailable = CPlayer::EENone;
			}
		}

	}

	void Blit(HDC hdc)
	{
		static int nFrames = 0;
		nFrames++;

		static int nFps = 0;

		static LONG lLastTick = 0;
		LONG lTick = GetTickCount();
		if ( lLastTick == 0 )
			lLastTick = lTick;
		if ( lTick > lLastTick + 1000 )
		{
			nFps = nFrames;
			nFrames = 0;
			lLastTick = lTick; //+= 1000;
		}

		m_Powerup.Render(hdc);
		m_Bullets.Render(hdc);
		
		/*
		CString strInfo;
		strInfo.Format( _T("FPS: %d   "), nFps );
		RECT r;
		r.left = 0; r.top = 20; r.right = 256; r.bottom = 40;

		//SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		DrawText(hdc, strInfo, -1, &r, 0);
		*/
		DrawScores(hdc);
	}

	void DrawScores(HDC hdc)
	{
		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );
		SetBkMode(hdc, TRANSPARENT);

		for (int i=0; i<arrPlayer.GetSize(); i++)
		{
			COLORREF cPlayer = arrPlayer[i]->m_cColor;
			cPlayer = RGB(GetBValue(cPlayer), GetGValue(cPlayer), GetRValue(cPlayer));

			RECT r;
			r.left = nRight+8; r.top = 20+i*100; r.right = r.left + 100; r.bottom = r.top + 80;

			CPlayer* pPlayer = arrPlayer[i];
			SetTextColor(hdc, cPlayer);

			CString strInfo;
			strInfo.Format( _T("Player %d"), i+1 );
			DrawText(hdc, strInfo, -1, &r, 0);
			
			r.top += 16;
			strInfo.Format( _T("Score %03d + %d"), pPlayer->m_nTotalScore, pPlayer->m_nScore );
			DrawText(hdc, strInfo, -1, &r, 0);

			r.top += 16;

			RECT rp = r;
			rp.right = rp.left + 32;
			rp.bottom = rp.top + 32;

			if ( pPlayer->m_nExtraActivated )
			{
				CPowerup::Render(hdc, pPlayer->m_nExtraActivated, rp);
				SetTextColor(hdc, cPlayer);

				RECT rpt = rp;
				rpt.top = rpt.bottom;
				rpt.bottom = rpt.top + 16;

				if ( pPlayer->m_nExtraValidUntil != 0 )
				{
					int nRemain = pPlayer->m_nExtraValidUntil - GetTickCount();					
					strInfo.Format( _T("%ds"), nRemain / 1000 );
					DrawText(hdc, strInfo, -1, &rpt, 0);
				}
			}

			rp.left += 40;
			rp.right += 40;
			if ( pPlayer->m_nExtraAvailable )
			{
				CPowerup::Render(hdc, pPlayer->m_nExtraAvailable, rp);
				
				SetTextColor(hdc, cPlayer);
				RECT rpt = rp;
				rpt.top = rpt.bottom;
				rpt.bottom = rpt.top + 16;

				if ( pPlayer->m_nExtraNewDuration != 0 )
				{
					strInfo.Format( _T("%ds"), pPlayer->m_nExtraNewDuration / 1000 );
					DrawText(hdc, strInfo, -1, &rpt, 0);
				} else
				if ( pPlayer->m_nExtraNewCount != 0 )
				{
					if ( pPlayer->m_nExtraNewCount == -1 )
						strInfo = _T("oo x");
					else
						strInfo.Format( _T("%dx"), pPlayer->m_nExtraNewCount );
					DrawText(hdc, strInfo, -1, &rpt, 0);
				}
			}
		}
	}
};
