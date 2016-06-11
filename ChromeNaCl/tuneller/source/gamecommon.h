class CGameCommon;

class CNetCommand
{
public:
	static CGameCommon* s_pGame;

	virtual CNetCommand* FromString(std::string strCommand) = 0;
	virtual void Do() = 0;
	virtual std::string ToString() = 0;

	void Send();
	//{
//		s_pGame->Send( ToString() );
//	}
};

class CGameCommon
{
	friend class CDrone;
	friend class CSideShot;
	friend class CNetCommandNotifyMove;
	friend class CNetCommandKilled;
	friend class CNetCommandNotifyKilled;

protected:
	CWorld m_world;
	std::vector<CTank> m_arrTanks;
	std::vector<CBullet> m_arrBullets;
	std::vector<CParticle> m_arrParticles;
	std::vector<std::shared_ptr<CEntity> > m_arrEntities;
	std::list<std::shared_ptr<CNetCommand> > m_lstCommands;

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

	// interface for net* functions
	virtual void Send(std::string str) = 0;
	virtual void NetCreateWorld(int nSeed) = 0;
	virtual void NetCreateTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetMoveTank(int nId, int nX, int nY, int nDir, int nEnergy, int nTankTs, int nStopTs) = 0;
	virtual void NetInfoTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetFireTank(int nId, int nFireX, int nFireY, int nVectorX, int nVectorY) = 0;
	virtual void NetKillTank(int nId) = 0;
	virtual void NetRequestInfo() = 0;
	virtual long GetTs() = 0;
	virtual void NetOnReplyTime(int nSequence, int nTs) = 0;
	virtual void Explode(CBullet& bullet) = 0;
};
