class CGameAi : public CGameCommon
{
private:
	float TestDir( CCerv* pCerv, float fAngle, float fMax )
	{
		int bx, by;
		pCerv->GetCoordsInFront(bx, by, 5.0f);
		float a = (pCerv->m_Attrs.m_fAngle + fAngle) / 180.0f * 3.141592f;
		float vx = cos(a);
		float vy = sin(a);

		float f;
		int nLeft, nTop, nRight, nBottom;
		CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

		const LONG H = g_dev.display.Width();
		LONG lOffsets[] = {  
			-H-3, -H, -H+3,
			-3, 0, +3,
			+H-3, +H, +H+3};

		DWORD *pBuf_ = (DWORD*)g_dev.display.GetBuffer();
		
		for ( f=5.0; f<fMax; f+=1.0f)
		{
			float x = bx + vx*f;
			float y = by + vy*f;
			if ( x <= nLeft+3 || x >= nRight-3 || y <= nTop+3 || y >= nBottom-3 )
				return f;

			DWORD* pBuf = pBuf_ + (LONG)x + (LONG)y*H;

			for ( int q=0; q<9; q++)
				if ( !pCerv->CanWalk( *(pBuf+lOffsets[q]) ) )
					return f;
		}
		return f;
	}

public:
	virtual void Robot(CCerv* pCerv, CPlayer* pPlayer)
	{
		pPlayer->m_nCurrentKey = CCerv::goNone;

		float fForward = TestDir(pCerv, 0.0f, 500.0f);

		if ( fForward >= 500.0f )
			return;

		if ( fForward >= 200.0f )
		{
			static float fFavor = 0.0;

			float fTestAngle = (float)((rand()%240)-120);

			float fFavorRange = TestDir(pCerv, pCerv->m_Attrs.m_fAngle + fFavor, 500.0f);
			float fTestRange = TestDir(pCerv, pCerv->m_Attrs.m_fAngle + fTestAngle, 500.0f);
		
			if ( fFavorRange > fTestRange )
			{
				if ( fFavorRange < 0 )
					pPlayer->m_nCurrentKey = CCerv::goLeft;
				else
					pPlayer->m_nCurrentKey = CCerv::goRight;
				return;
			}

			if ( fTestRange > fForward )
			{
				fFavor = fTestAngle;
				if ( fTestAngle < 0 )
					pPlayer->m_nCurrentKey = CCerv::goLeft;
				else
					pPlayer->m_nCurrentKey = CCerv::goRight;
				return;
			}
		}

		float fBestDist = 0.0f;
		float fBestAngle = 0;
		for (float fTest = -20.0f; fTest <= 20.0f; fTest += 2.0f )
		{
			float fDist = TestDir(pCerv, pCerv->m_Attrs.m_fSteering*fTest, 100.0f);
			if ( fDist > fBestDist )
			{
				fBestDist = fDist;
				fBestAngle = fTest;
			}
		}

		if ( fBestDist < 50.0f )
		{
			if ( pCerv->m_Attrs.m_nId & 1 )
				pPlayer->m_nCurrentKey = CCerv::goLeft;
			else
				pPlayer->m_nCurrentKey = CCerv::goRight;
		}

		if ( fBestAngle < 0 )
			pPlayer->m_nCurrentKey = CCerv::goLeft;
		else
			pPlayer->m_nCurrentKey = CCerv::goRight;
	}
};

