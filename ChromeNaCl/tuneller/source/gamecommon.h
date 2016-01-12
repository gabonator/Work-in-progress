
class CGameCommon
{
	friend class CDrone;
	friend class CSideShot;

protected:
	CWorld m_world;
	std::vector<CTank> m_arrTanks;
	std::vector<CBullet> m_arrBullets;
	std::vector<CParticle> m_arrParticles;
	std::vector<std::shared_ptr<CEntity> > m_arrEntities;

	POINT m_ptViewPoint;
	int m_nPixelScaling;

public:
	CTank& GetTankById(int nId)
	{
		for (int i = 0; i < (int)m_arrTanks.size(); i++ )
			if ( m_arrTanks[i].m_nId == nId )
				return m_arrTanks[i];

		static CTank dummyTank;
		return dummyTank;
	}

	CWorld& GetWorld()
	{
		return m_world;
	}

	std::vector<CTank>& GetTanks()
	{ 
		return m_arrTanks;
	}

	std::vector<CBullet>& GetBullets()
	{ 
		return m_arrBullets;
	}
};
