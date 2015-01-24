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
			return _T("HCl");
		case CPlayer::EEShooter:	
			return _T(" ! ");
		case CPlayer::EEDouble:
			return _T("x2 ");
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
