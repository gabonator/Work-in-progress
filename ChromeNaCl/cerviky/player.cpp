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
	case 0:	m_nKeyLeft = VK_LEFT;	m_nKeyRight = VK_RIGHT;		m_nKeyAction = VK_UP;	break;
	case 1: m_nKeyLeft = 'Z';		m_nKeyRight = 'X';			m_nKeyAction = 'S';		break;
	case 2:	m_nKeyLeft = 'N';		m_nKeyRight = 'M';			m_nKeyAction = 'J';		break;
	case 3:	m_nKeyLeft = 'Q';		m_nKeyRight = 'W';			m_nKeyAction = '2';		break;

	case 4:	m_nKeyLeft = 'R';		m_nKeyRight = 'T';			m_nKeyAction = '5';		break;
	case 5:	m_nKeyLeft = 'Y';		m_nKeyRight = 'U';			m_nKeyAction = '7';		break;
	case 6:	m_nKeyLeft = 'I';		m_nKeyRight = 'O';			m_nKeyAction = '9';		break;

	case 7:	m_nKeyLeft = 'D';		m_nKeyRight = 'F';			m_nKeyAction = 'G';		break;
	case 8:	m_nKeyLeft = 'H';		m_nKeyRight = 'J';			m_nKeyAction = 'K';		break;
	case 9:	m_nKeyLeft = VK_F1;		m_nKeyRight = VK_F2;		m_nKeyAction = VK_F3;	break;
	case 10:m_nKeyLeft = VK_F4;		m_nKeyRight = VK_F5;		m_nKeyAction = VK_F5;	break;
	}

	m_cColor = RGB(255, 255, 255);

	switch ( nId )
	{
		case 0: m_cColor = RGB(255, 0, 0); break;
		case 1: m_cColor = RGB(0, 255, 0); break;
		case 2: m_cColor = RGB(0, 255, 255); break;
		case 3: m_cColor = RGB(255, 255, 0); break;
		case 4: m_cColor = RGB(255, 0, 255); break;
		case 5: m_cColor = RGB(0, 0, 255); break;

		case 6: m_cColor = RGB(255, 0, 0); break;
		case 7: m_cColor = RGB(128, 255, 0); break;
		case 8: m_cColor = RGB(128, 255, 255); break;
		case 9: m_cColor = RGB(255, 255, 128); break;
		case 10: m_cColor = RGB(255, 128, 255); break;
		case 11: m_cColor = RGB(128, 0, 255); break;

		case 12: m_cColor = RGB(255, 0, 128); break;
		case 13: m_cColor = RGB(0, 255, 128); break;
		case 14: m_cColor = RGB(0, 128, 255); break;
	}
		
	m_nExtraActivated = EENone;
	m_nExtraAvailable = EENone;

	m_nExtraNewDuration = 0;
	m_nExtraNewCount = 0;

	m_bRobot = true; //nId > 0;
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

	int l = max(b, max(r, g));
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
	m_fSteering = CTools::RandRange(2.0f, 5.0f) * m_fSpeed;
}
