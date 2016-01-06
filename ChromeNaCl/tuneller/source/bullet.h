class CBullet
{
	POINT m_ptPosition;
	POINT m_ptVector;
	CWorld* m_pWorld;
	bool m_bShouldExplode;
	int m_nLive;

	//
	int m_nOwnerId;
	int m_nParticles;
	int m_nParticlePower;

public:
	CBullet()
	{
	}

	CBullet(CWorld* pWorld, int nOwnerId, POINT ptOrigin, POINT ptVector, int nParticles = 10, int nParticlePower = 4 )
	{
		m_pWorld = pWorld;
		m_nOwnerId = nOwnerId;
		m_ptPosition = ptOrigin;
		m_ptVector = ptVector;
		m_bShouldExplode = false;
		m_nLive = 0;
		m_bShouldExplode = CheckCollision();
		//
		m_nParticles = nParticles;
		m_nParticlePower = nParticlePower;
	}

	bool CheckCollision()
	{
		if ( m_nLive == 0 )
			return false;

		POINT ptTest = m_ptPosition;
		int nPixel = m_pWorld->GetPixel( ptTest );
		if ( nPixel != CWorld::Track )
		{
			// when digging, explode in advance, not under tank
			if ( m_nLive == 1 && nPixel == CWorld::Dirt )
				return false;
			return true;
		}

		if ( m_nLive == 1 )
			return false;

		// tail
		ptTest.x -= m_ptVector.x;
		ptTest.y -= m_ptVector.y;
		if ( m_pWorld->GetPixel( ptTest ) != CWorld::Track )
			return true;
		return false;
	}

	void Do()
	{
		if ( m_bShouldExplode )
			return;

		Show(false);

		for (int i=0; i<2; i++)
		{
			m_nLive++;

			POINT ptSafePosition = m_ptPosition;
			m_ptPosition.x += m_ptVector.x;
			m_ptPosition.y += m_ptVector.y;
			m_pWorld->FixPosition(m_ptPosition);

			if ( CheckCollision() )
			{
				m_ptPosition = ptSafePosition;
				m_bShouldExplode = true;
				return;
			}
		}
		Show(true);
	}

	void Show(bool bShowOrClear)
	{
		POINT ptTail = m_ptPosition;
		POINT ptFront = m_ptPosition;
		ptTail.x -= m_ptVector.x;
		ptTail.y -= m_ptVector.y;

		m_pWorld->SetPixel(ptFront, bShowOrClear ? 12 : CWorld::Track);
		m_pWorld->SetPixel(ptTail, bShowOrClear ? 4 : CWorld::Track);
	}

	POINT GetPosition()
	{
		return m_ptPosition;
	}

	POINT GetVector()
	{
		return m_ptVector;
	}

	bool ShouldExplode()
	{
		return m_bShouldExplode;
	}

	//
	int GetParticles()
	{
		return m_nParticles;
	}

	int GetParticlePower()
	{
		return m_nParticlePower;
	}

	int GetOwnerId()
	{
		return m_nOwnerId;
	}

	bool IsFriendly()
	{
		return m_nLive < 5;
	}
};
