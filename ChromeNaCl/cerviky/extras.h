class CGameExtras : public CGameAi
{
public:
	virtual void ExtraAccept(CPlayer* pPlayer, CPlayer::EExtra eType)
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
			case CPlayer::EEThroughWall:
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
			case CPlayer::EEDisease:
				pPlayer->m_nExtraNewCount = 1;
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
      default:;
		}
	}

	virtual void ExtraDo(CPlayer* pPlayer)
	{
		if ( pPlayer->m_nExtraActivated == CPlayer::EENone )
			return;

		if ( pPlayer->m_nExtraValidUntil && (int)GetTickCount() > pPlayer->m_nExtraValidUntil )
		{
			switch ( pPlayer->m_nExtraActivated )
			{
				case CPlayer::EESlowMo:
					if ( pPlayer->m_fExtraCounter < 1.0f )
					{
						PlayerResume();
						pPlayer->m_fExtraCounter += 0.01f;
					}

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
        default:;
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

			case CPlayer::EEThroughWall:
				{				
					int nLeft, nTop, nRight, nBottom;
					CTools::GetMapArea( nLeft, nTop, nRight, nBottom );

					for ( int i = 0; i < arrCerv.GetSize(); i++ )
					{
						CCerv* pCerv = arrCerv[i];
						if ( pCerv->m_Attrs.m_nId != pPlayer->m_nId )
							continue;

						int x, y;
						pCerv->GetCoordsInFront(x, y);
						if ( x > nRight - 2 )
							pCerv->m_Attrs.m_fX = (float)nLeft + 3;
						if ( x < nLeft + 2 )
							pCerv->m_Attrs.m_fX = (float)nRight - 3;
						if ( y > nBottom - 2 )
							pCerv->m_Attrs.m_fY = (float)nTop + 3;
						if ( y < nTop + 2 )
							pCerv->m_Attrs.m_fY = (float)nBottom - 3;
					}
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
					if ( !pCerv->CanWalk( GfxGetPixel( x, y ) ) )
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

	virtual void ExtraActivate(CPlayer* pPlayer)
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
				PlayerPause();
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

			case CPlayer::EEThroughWall:	
				pPlayer->m_nExtraActivated = pPlayer->m_nExtraAvailable;
				pPlayer->m_nExtraValidUntil = 0;
				break;

			case CPlayer::EEShooter:
				/*pPlayer->m_nExtraCount = pPlayer->m_nExtraNewCount*/;
				m_Bullets.Shoot( pCerv, CPlayer::EEShooter );
				break;

			case CPlayer::EEDisease:
				/*pPlayer->m_nExtraCount = pPlayer->m_nExtraNewCount*/;
				m_Bullets.Shoot( pCerv, CPlayer::EEDisease );
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

	virtual void ExtraCleanup(CPlayer* pPlayer)
	{
		switch ( pPlayer->m_nExtraActivated )
		{
			case CPlayer::EESlowMo:
			case CPlayer::EETurbo:
				ResetSpeeds();
      default:;
		}
	}

};
