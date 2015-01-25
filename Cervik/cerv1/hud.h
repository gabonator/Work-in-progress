class CGameHud : public CGameAi
{
public:
	virtual void Blit(HDC hdc)
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
		
		CString strInfo;
		strInfo.Format( _T("FPS: %d   "), nFps );

		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		RECT r;
		r.left = nRight+8; r.top = nBottom-16; r.right = r.left + 60; r.bottom = nBottom;

		//SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(255, 255, 255));
		DrawText(hdc, strInfo, -1, &r, 0);
		DrawScores(hdc);

		if ( m_bGamePaused )
		{
			RECT r;
			r.left = (nLeft + nRight)/2-100; r.top = (nTop+nBottom)/2; 
			r.right = r.left + 200; r.bottom = r.top + 16;
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, _T("Game paused, press space"), -1, &r, 0);	
		}
	}

private:
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
				CPowerup::TPowerup powerup;
				powerup.m_lValidSince = 0;
				powerup.m_lValidUntil = 0;
				powerup.m_rcPosition = rp;
				powerup.m_Type = pPlayer->m_nExtraActivated;

				CPowerup::Render(hdc, powerup);
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
				CPowerup::TPowerup powerup;
				powerup.m_lValidSince = 0;
				powerup.m_lValidUntil = 0;
				powerup.m_rcPosition = rp;
				powerup.m_Type = pPlayer->m_nExtraAvailable;

				CPowerup::Render(hdc, powerup);
				
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
