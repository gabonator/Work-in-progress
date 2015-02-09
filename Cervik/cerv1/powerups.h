class CPowerup
{
public:
	class TPowerup
	{
	public:
		CPlayer::EExtra m_Type;
		RECT m_rcPosition;
		DWORD m_lValidUntil;
		DWORD m_lValidSince;
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
			return _T("HCl");
		case CPlayer::EEShooter:	
			return _T(" ! ");
		case CPlayer::EEDouble:
			return _T("x2 ");
		case CPlayer::EEThroughWall:
			return _T("<^>");
			/*
	EEShooter = 3,			// vystreli a spravi dieru, 3x
	EERespawn = 7,			// objavi sa niekde inde na mape
	EEShield = 8,			// vie sa prerazit cez 40 pixelov, automaticky aktivovane
	EECrosser = 9,			// moze prechadzat sam cez seba		


	EEMirror = ? obrati sa cela obrazovka
	EEMirrorControls = vsetkym sa obrati riadenie left/right
	*/
		}
		return _T("???");
	}

	static void Render(HDC hdc, const TPowerup& powerup)
	{
		CPlayer::EExtra eType = powerup.m_Type;
		RECT r = powerup.m_rcPosition;

		static HBRUSH brush = NULL;
		if ( brush == NULL )
			brush = CreateSolidBrush(RGB(255, 255, 0) );

		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0, 0, 0));

		float fTransition = GetTransition(powerup);
		
		if ( fTransition <= 0 )
			return;

		if ( fTransition != 1.0f )
			fTransition = sin(fTransition*3.141592f*0.7f)/sin(3.141592f*0.7f);

		POINT center;
		center.x = (r.left + r.right)/2;
		center.y = (r.top + r.bottom)/2;

		SIZE sz;
		sz.cx = r.right - r.left;
		sz.cy = r.bottom - r.top;

		RECT r1;
		r1.right = (int)(sz.cx/2*fTransition);
		r1.bottom = (int)(sz.cy/2*fTransition);
		r1.left = -r1.right;
		r1.top = -r1.bottom;

		r1.left += center.x;
		r1.right += center.x;
		r1.top += center.y;
		r1.bottom += center.y;

		FillRect(hdc, &r1, brush);
		DrawText(hdc, GetName(eType), -1, 
			&r, DT_CENTER | DT_SINGLELINE | DT_VCENTER );
	}

	void Render(HDC hdc)
	{
		for ( int i=0; i<m_arrPowerups.GetSize(); i++)
			Render(hdc, m_arrPowerups[i]);
	}

	void Do()
	{
		if ( rand() % 200 == 0 )
		{
			if ( m_arrPowerups.GetSize() < 10 )
				AddRandom();
		}

		DWORD lTick = GetTickCount();
		for ( int i=0; i<m_arrPowerups.GetSize(); i++)
			if ( lTick > m_arrPowerups[i].m_lValidUntil )
				m_arrPowerups.RemoveAt(i--);
	}

	void AddRandom()
	{
		CPlayer::EExtra eType = CPlayer::EENone;
		switch (rand()%10)
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
		case 9: eType = CPlayer::EEThroughWall; break;
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
		powerup.m_lValidSince = GetTickCount();
		powerup.m_lValidUntil = powerup.m_lValidSince + 20000;

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

	static float GetTransition(const TPowerup& powerup)
	{
		if ( powerup.m_lValidSince == powerup.m_lValidUntil )
			return 1.0f;

		const float fTime0 = 0.5f;
		const float fTime1 = 3.0f;

		DWORD lTick = GetTickCount();
		float fSince = (lTick - powerup.m_lValidSince) / 1000.0f;
		float fTo = (powerup.m_lValidUntil - lTick) / 1000.0f;

		float fResult = 1.0f;

		if ( fTo < 0 )
			return 0.0f;
		if ( fTo < fTime1 )
			fResult = fTo / fTime1;
		else if ( fSince < fTime0 )
			fResult = fSince / fTime0;
		if ( fResult < 0.0f )
			fResult = 0.0f;

		return fResult;
	}

};
