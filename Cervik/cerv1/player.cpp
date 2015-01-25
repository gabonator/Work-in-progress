#include "stdafx.h"
#include "player.h"
#include "tools.h"

CPlayer::CPlayer(int nId)
{
	m_nId = nId;

	m_nExtraAvailable = EENone;
	m_nExtraActivated = EENone;

	m_nExtraValidUntil = 0;
	m_nExtraCount = 0;
	m_fExtraCounter = 0;

	m_nLastKey = 0;
	m_nCurrentKey = 0;

	Randomize();

	m_nKeyLeft = 0;
	m_nKeyRight = 0;
	m_nKeyAction = 0;

	//
	m_nScore = 0;
	m_nTotalScore = 0;
	m_bAlive = false;

	switch ( nId )
	{
	case 0:
		m_nKeyLeft = VK_LEFT;
		m_nKeyRight = VK_RIGHT;
		m_nKeyAction = VK_UP;
		m_nExtraAvailable = EEWalkThrough;
		break;
	case 1:
		m_nKeyLeft = 'Z';
		m_nKeyRight = 'X';
		m_nKeyAction = 'S';
		m_nExtraAvailable = EEFlower;
		break;
	case 2:
		m_nKeyLeft = 'N';
		m_nKeyRight = 'M';
		m_nKeyAction = 'J';
		m_nExtraAvailable = EESwapper;
		break;
	case 3:
		m_nKeyLeft = 'Q';
		m_nKeyRight = 'W';
		m_nKeyAction = '2';
		m_nExtraAvailable = EESlowMo;
		break;
	}

	m_cColor = RGB(255, 255, 255);

	switch ( nId )
	{
		case 0: m_cColor = RGB(255, 0, 0); break;
		case 1: m_cColor = RGB(0, 255, 0); break;
		case 2: m_cColor = RGB(0, 255, 255); break;
		case 3: m_cColor = RGB(255, 255, 0); break;
		case 4: m_cColor = RGB(255, 0, 255); break;
	}

	m_nExtraActivated = EENone;
	m_nExtraAvailable = EENone;

	m_nExtraNewDuration = 0;
	m_nExtraNewCount = 0;

}

bool CPlayer::IsMyColor(COLORREF c)
{
	if ( c == 0 || c == RGB(255, 255, 255) )
		return false;
	int r = GetRValue(c);
	int g = GetGValue(c);
	int b = GetBValue(c);

	int myr = GetRValue( m_cColor );
	int myg = GetGValue( m_cColor );
	int myb = GetBValue( m_cColor );

	int l = max(max(r, g), b);
	r = r * 255 / l;
	g = g * 255 / l;
	b = b * 255 / l;

	if ( abs(r-myr)<10 && abs(g-myg)<10 && abs(b-myb) < 10 )
		return true;
	
	return false;
}

bool CPlayer::IsAlive()
{
	return m_bAlive;
}

void CPlayer::Randomize()
{
	m_fSteering = 4.0f;
	m_fSpeed = CTools::RandRange(0.8f, 1.3f); //*0.5f;
	m_fSteering = m_fSpeed * CTools::RandRange(2.0f, 5.0f);
}
