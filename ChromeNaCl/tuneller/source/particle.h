class CParticle
{
	CWorld* m_pWorld;
	float m_fX;
	float m_fY;

	float m_fDx;
	float m_fDy;

	int m_nCount;
	bool m_bCollision;

public:
	CParticle()
	{
	}

	CParticle(CWorld* pWorld, POINT ptCenter, int nPower = 4, float fSpeed = 1.0f)
	{
		m_pWorld = pWorld;
		m_fX = (float)ptCenter.x;
		m_fY = (float)ptCenter.y;

		float fAngle = (rand()%360) * 3.141596f / 180.0f;
//		float fSpeed = ((rand()%80) +20) /100*0.5f;
		m_fDx = cos(fAngle) * fSpeed;
		m_fDy = sin(fAngle) * fSpeed;
		m_nCount = nPower;
		m_bCollision = false; //CheckCollision();
	}

	void Do()
	{
		if ( m_bCollision )
			return;

		_ASSERT( m_nCount > 0 );
		//_ASSERT(!CheckCollision());
		Show(false);

		m_fX += m_fDx;
		m_fY += m_fDy;

		m_bCollision = CheckCollision();
		if ( m_bCollision )
			return;

		m_nCount--;
		if ( m_nCount > 0 )
			Show(true);
	}

	POINT GetPosition()
	{
		POINT pt;
		pt.x = (int)m_fX;
		pt.y = (int)m_fY;
		return pt;
	}

	bool CheckCollision()
	{
		int nPixel = m_pWorld->GetPixel(GetPosition());

		// TODO: consider this approach: 1. hide all particles, 2. move all particles/check for collision, 3. show all particles
		if ( nPixel == 12 || m_pWorld->CanFly(nPixel) )
			return false;

		return true;
	}

	void Show(bool bShowOrClear)
	{
		m_pWorld->SetPixel(GetPosition(), bShowOrClear ? 12 : CWorld::Track);
	}

	bool ShouldDie()
	{
		return m_nCount <= 0 || m_bCollision;
	}
};
