class CDrone : public CEntity
{
public:// temporary!
	POINT m_ptPosition;
	CGameCommon* m_pGame;

	int m_nOwner;

public:
	CDrone( CGameCommon* pGame ) : CEntity( &pGame->GetWorld() )
	{
		m_pGame = pGame;
		m_ptPosition.x = rand() % m_pWorld->m_nWidth;
		m_ptPosition.y = rand() % m_pWorld->m_nHeight;
		m_nOwner = -1;
	}

	virtual void Draw(bool bDrawOrErase)
	{
		CEntity::Draw( bDrawOrErase, bmpEntityDrone, m_ptPosition );
	}

	virtual void Do()
	{
		if ( m_nOwner == -1 )
		{
			for (int i = 0; i < (int)m_pGame->m_arrTanks.size(); i++ )
			{
				CTank& t = m_pGame->m_arrTanks[i];
				POINT ptLockPoint = GetLockPoint(t);
				POINT ptDistance = m_pWorld->GetOffset(ptLockPoint, m_ptPosition);
				if ( LengthSq(ptDistance) < 2*2 )
					m_nOwner = t.m_nId;
			}
			return;
		}

		CTank& t = m_pGame->GetTankById(m_nOwner);
		if ( !t.IsValid() )
		{
			m_nOwner = -1;
			return;
		}
		
		POINT ptLockPoint = GetLockPoint(t);
		POINT ptOffset = m_pWorld->GetOffset(ptLockPoint, m_ptPosition);
		if ( LengthSq(ptOffset) > 20*20 )
		{
			m_nOwner = -1;
			return;
		}

		Normalize(ptOffset);
		m_ptPosition.x -= ptOffset.x;
		m_ptPosition.y -= ptOffset.y;
	}

	POINT GetLockPoint(CTank& t)
	{
		POINT ptDelta = t.GetDeltaByDirection(t.m_nDirection);
		if ( t.m_nDirection & 1 ) 
		{
			ptDelta.x *= -5;
			ptDelta.y *= -5;
		} else {
			ptDelta.x *= -7;
			ptDelta.y *= -7;
		}
		ptDelta.x += t.m_ptPosition.x;
		ptDelta.y += t.m_ptPosition.y;
		return ptDelta;
	}

//
	virtual void OnTankFires(CTank& t, std::vector<CBullet>& arrBullets)
	{
		if ( m_nOwner == -1 || m_nOwner != t.m_nId )
			return;
		//NetFire(m_ptPosii, bullet.GetVector());
		CBullet bullet = GetBullet(t);
		//m_pGame->NetFire(bullet.GetPosition(), bullet.GetVector());
		arrBullets.push_back( bullet );
	}

	CBullet GetBullet(CTank& t)
	{
		POINT ptVector = t.GetDeltaByDirection(t.m_nDirection);
		ptVector.x *= -1;
		ptVector.y *= -1;

		return CBullet(m_pWorld, t.m_nId, m_ptPosition, ptVector);
	}
};

class CSideShot : public CEntity
{
public:// temporary!
	POINT m_ptPosition;
	CGameCommon* m_pGame;

	int m_nOwner;
	int m_nDirection;
	int m_nOpen;

public:
	CSideShot( CGameCommon* pGame ) : CEntity( &pGame->GetWorld() )
	{
		m_pGame = pGame;
		m_pWorld = &pGame->GetWorld();
		m_ptPosition.x = rand() % m_pWorld->m_nWidth;
		m_ptPosition.y = rand() % m_pWorld->m_nHeight;
		m_nOwner = -1;
		m_nDirection = 8;
		m_nOpen = 0;
	}

	virtual void Draw(bool bDrawOrErase)
	{		
		POINT ptVect = CTank::GetDeltaByDirection(m_nDirection);

		POINT ptDrawA = m_ptPosition;
		ptDrawA.x += -ptVect.y * m_nOpen;
		ptDrawA.y += ptVect.x * m_nOpen;

		POINT ptDrawB = m_ptPosition;
		ptDrawB.x += ptVect.y * m_nOpen;
		ptDrawB.y += -ptVect.x * m_nOpen;

		TTankBitmap bitmap;
		CTank::Transform(bitmap, bmpEntitySideshotRAligned, bmpEntitySideshotDiagonal, m_nDirection);
		CEntity::Draw(bDrawOrErase, bitmap, ptDrawA);

		CTank::Transform(bitmap, bmpEntitySideshotLAligned, bmpEntitySideshotDiagonal, m_nDirection);
		CEntity::Draw(bDrawOrErase, bitmap, ptDrawB);
	}

	virtual void Do()
	{
		if ( m_nOpen > 0 )
			m_nOpen--;

		if ( m_nOwner == -1 )
		{
			m_nOpen = 0;
			for (int i = 0; i < (int)m_pGame->m_arrTanks.size(); i++ )
			{
				CTank& t = m_pGame->m_arrTanks[i];
				POINT ptDistance = m_pWorld->GetOffset(t.m_ptPosition, m_ptPosition);
				int nLength = LengthSq(ptDistance);
				if ( nLength > 10*10 )
					continue;
				nLength = (int)sqrt((float)nLength);

				if ( nLength < 2 )
				{
					m_nOwner = t.m_nId;
				}

				int nThisOpen = 5 - nLength/2;
				m_nOpen = max(m_nOpen, nThisOpen);
			}

			return;
		}

		CTank& t = m_pGame->GetTankById(m_nOwner);
		if ( !t.IsValid() )
		{
			m_nOwner = -1;
			return;
		}
		
		POINT ptOffset = m_pWorld->GetOffset(t.m_ptPosition, m_ptPosition);
		if ( LengthSq(ptOffset) > 20*20 )
		{
			m_nOwner = -1;
			return;
		}

		m_nDirection = t.m_nDirection;
		m_nOpen = (int)(6.0f + sin(GetTickCount()*0.01f)*1.5f);

		Normalize(ptOffset);
		m_ptPosition.x -= ptOffset.x;
		m_ptPosition.y -= ptOffset.y;
	}

	virtual void OnTankFires(CTank& t, std::vector<CBullet>& arrBullets)
	{
		if ( m_nOwner == -1 || m_nOwner != t.m_nId )
			return;

		arrBullets.push_back( GetBullet(t, -1) );
		arrBullets.push_back( GetBullet(t, +1) );
	}

	CBullet GetBullet(CTank& t, int nDir)
	{
		POINT ptDir = CTank::GetDeltaByDirection(m_nDirection);
		POINT ptVect;
		ptVect.x = -ptDir.y * nDir;
		ptVect.y = ptDir.x * nDir;
		
		POINT ptPosition;
		ptPosition.x = t.m_ptPosition.x + ptVect.x * 5;
		ptPosition.y = t.m_ptPosition.y + ptVect.y * 5;
		return CBullet(m_pWorld, t.m_nId, ptPosition, ptVect);
	}
};
