
#include "eraser.h"
#include "powerups.h"
#include "bullets.h"

class CGameCommon
{
public:
	CArray<CCerv*> arrCerv;
	CArray<CPlayer*> arrPlayer;
	CEraser m_Eraser;
	CPowerup m_Powerup;
	CBullets m_Bullets;
	bool m_bGamePaused;

	CGameCommon()
	{
		m_bGamePaused = false;
	}

	~CGameCommon()
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
		arrPlayer.Add( new CPlayer(3) );
		arrPlayer.Add( new CPlayer(4) );
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
			arrPlayer[i]->Randomize();
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
		if ( m_bGamePaused )
		{
			GamePaused();
			return;
		}

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

			pCerv->AdvanceCerv(1.0f * CCerv::g_fSpeedMultiply * pCerv->m_Attrs.m_fSpeed);

			if ( pCerv->m_Attrs.m_bColliding )
			{
				pCerv->DrawCerv();
				CervKilled(pPlayer, pCerv);

				delete pCerv;
				arrCerv.RemoveAt(i);
				i--;
				continue;
			}

			if ( pPlayer->m_nKeyLeft != VK_LEFT )
				Robot(pCerv, pPlayer);

			pCerv->Command( (CCerv::EAction)pPlayer->m_nCurrentKey );

			CPlayer::EExtra eType = m_Powerup.GetCollision( (int)pCerv->m_Attrs.m_fX, (int)pCerv->m_Attrs.m_fY );
			if ( eType != CPlayer::EENone )
				ExtraAccept(pPlayer, eType);
		}
		
		if ( arrCerv.GetSize() <= 1 )
		{
			m_bGamePaused = true;
			//GamePaused();
		}
		
		m_Powerup.Do();
		m_Bullets.Do();
		FxFade();
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

		// Pridaj bod tomu do ktoreho narazil
		int nMatch = -1;
		for ( int i = 0; i < arrPlayer.GetSize(); i++ )
			if ( arrPlayer[i]->IsMyColor( pCerv->m_clrHitColor ) )
			{
				nMatch = i;
				arrPlayer[i]->m_nScore++;
			}

		CString strInfo;
		if ( nMatch == -1 )
			strInfo.Format( _T("CervKilled (id=%d, color=%06x) color match %06x, UNKNOWN ID\n"),
				pCerv->m_Attrs.m_nId, pCerv->m_Attrs.m_color, pCerv->m_clrHitColor);
		else
			strInfo.Format( _T("CervKilled (id=%d, color=%06x) color match %06x -> %06x, id=%d\n"), 
				pCerv->m_Attrs.m_nId, pCerv->m_Attrs.m_color,
				pCerv->m_clrHitColor, arrPlayer[nMatch]->m_cColor, nMatch );
		
		OutputDebugString(strInfo);
		ExtraCleanup(pPlayer);

		pPlayer->m_bAlive = false;
		CCerv::g_fSpeedMultiply += 0.2f;
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

	virtual void FxFade()
	{
		DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();

		LONG lPoints = g_dev.display.Width() * g_dev.display.Height();
		while (lPoints--)
		{
			COLORREF c = *pBuf;

			if ( c == 0 || c == RGB(255, 255, 255) )
				goto skip;

			if ( GetRValue(c) != GetGValue(c) || GetGValue(c) != GetBValue(c) )
				goto skip;

			*pBuf = c - 0x020202;
skip:
			pBuf++;
		}
	}

	int RandomNumber(int nLow, int nHigh)
	{
		return nLow + rand() % (nHigh-nLow+1);
	}

	void GamePaused()
	{
		static bool bPrevSpace = false;
		bool bCurSpace = (bool)g_dev.GetKeys()[VK_SPACE];

		if ( !m_bGamePaused )
		{
			bPrevSpace = bCurSpace;
			return;
		}
		if ( !bPrevSpace && bCurSpace )
		{
			m_bGamePaused = false;
			RoundFinished();
			NextRound();
		}
		bPrevSpace = bCurSpace;
	}

	virtual void ExtraAccept(CPlayer* pPlayer, CPlayer::EExtra eType) = 0;
	virtual void ExtraDo(CPlayer* pPlayer) = 0;
	virtual void ExtraActivate(CPlayer* pPlayer) = 0;
	virtual void ExtraCleanup(CPlayer* pPlayer) = 0;
//	virtual void FxFade() = 0;
	virtual void Robot(CCerv* pCerv, CPlayer* pPlayer) = 0;
	virtual void Blit(HDC hdc) {}
};

#include "ai.h"
#include "hud.h"
#include "extras.h"


class CGame : public CGameExtras
{
};