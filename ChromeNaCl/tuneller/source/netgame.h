class CNetGame : public CGameCommon
{
protected:
	CNet* m_pNet;
	long m_nTimeOffset;

public:
	CNetGame()
	{
		m_nTimeOffset = 0;
		m_pNet = NULL;
		m_nStartRequestState = EStartRequestFailed;
	}

	void SetNetwork(CNet* pNet)
	{
		m_pNet = pNet;
		m_pNet->SetReceiveHandler(_ReceiveHandler, (PVOID)this);

		// connection safety timeout?
		m_nStartRequestState = m_pNet ? EStartRequestConnecting : EStartRequestFailed;
	}

private:
	static void _ReceiveHandler(std::string message, PVOID data)
	{
		CNetGame* pThis = static_cast<CNetGame*>(data);
		pThis->ReceiveHandler(message);
	}

	void ReceiveHandler(std::string message)
	{
		if ( message.substr(0, 10) == "replyStart" )
		{
			_ASSERT_VALID(StartRequestHandler(message));
		}
		if ( message.substr(0, 11) == "requestInfo" )
		{
			NetRequestInfo();
		}
		if ( message.substr(0, 10) == "notifyMove" )
		{
			int nTankId, nTankTs, nTankX, nTankY, nDir, nEnergy;
			_ASSERT_VALID( sscanf(message.c_str(), "notifyMove({id:%d, ts:%d, x:%d, y:%d, dir:%d, e:%d})", &nTankId, &nTankTs, &nTankX, &nTankY, &nDir, &nEnergy) == 6);
			NetMoveTank(nTankId, nTankX, nTankY, nDir, nEnergy);
		}
		if ( message.substr(0, 10) == "notifyInfo" )
		{
			int nTankId, nTankTs, nTankX, nTankY, nTankHomeX, nTankHomeY, nDir;
			_ASSERT_VALID( sscanf(message.c_str(), "notifyInfo({id:%d, ts:%d, hx:%d, hy:%d, x:%d, y:%d, dir:%d})", 
				&nTankId, &nTankTs, &nTankHomeX, &nTankHomeY, &nTankX, &nTankY, &nDir) == 7 );
			NetInfoTank(nTankId, nTankX, nTankY, nTankHomeX, nTankHomeY, nDir);
		}
		if ( message.substr(0, 10) == "notifyFire" )
		{
			int nTankId, nFireTs, nFireX, nFireY, nFireVectorX, nFireVectorY;
			_ASSERT_VALID( sscanf(message.c_str(), "notifyFire({id:%d, ts:%d, x:%d, y:%d, vx:%d, vy:%d})", 
				&nTankId, &nFireTs, &nFireX, &nFireY, &nFireVectorX, &nFireVectorY) == 6);
			NetFireTank(nTankId, nFireX, nFireY, nFireVectorX, nFireVectorY);
		}
		if ( message.substr(0, 10) == "notifyDead" )
		{
			int nTankId;
			_ASSERT_VALID( sscanf(message.c_str(), "notifyDead({id:%d})", 
				&nTankId) == 1);
			NetKillTank(nTankId);
		}
	}
		
	bool IsConnected()
	{
		return m_pNet ? true : false;
	}

	void Send(std::string str)
	{
		if (!m_pNet)
			return;

		m_pNet->Send(str);
	}

	// requests
	int m_nStartRequestState;
	long m_nStartRequestTime;

	enum {
		EStartRequestReset = 0,
		EStartRequestConnecting = 4,
		EStartRequestConnected = 5,
		EStartRequestPending = 1,
		EStartRequestSuccess = 2,
		EStartRequestFailed = 3
	};

	void StartRequest()
	{
		m_nStartRequestTime = GetTickCount();
		CNetGame::StartRequestSet(CNetGame::EStartRequestPending);
		CNetGame::Send("requestStart();");
	}
	
	void StartRequestSet(int nNewState)
	{
		m_nStartRequestState = nNewState;
	}

	int StartRequestState()
	{
		if ( m_nStartRequestState == EStartRequestConnecting )
		{
			if ( m_pNet->GetState() == CNet::Open ) 
				m_nStartRequestState = EStartRequestConnected;
			if ( m_pNet->GetState() == CNet::Closed || m_pNet->GetState() == CNet::Error )
				m_nStartRequestState = EStartRequestFailed;     
		}

		if ( m_nStartRequestState == EStartRequestPending )
		{
			// Timeout?
			if ( GetTickCount() - m_nStartRequestTime > 3000 )
				m_nStartRequestState = EStartRequestFailed;
		}
		return m_nStartRequestState;
	}
	
	bool StartRequestHandler(std::string message)
	{
		_ASSERT ( m_nStartRequestState == EStartRequestPending );
		
		int nId, nTs, nWorldSeed, nX, nY;
		_ASSERT_VALID( sscanf(message.c_str(), "replyStart({id:%d, ts:%d, world:%d, x:%d, y:%d})", &nId, &nTs, &nWorldSeed, &nX, &nY) == 5);

		m_nTimeOffset = nTs-GetTickCount(); // TODO: compensate ping times

		NetCreateWorld(nWorldSeed);
		NetCreateTank(nId, nX, nY, nX, nY, 8);
		NetRequestInfo();

		m_nStartRequestState = EStartRequestSuccess;
		return true;
	}

	// game notifications
	void NotifyTankMoves(int nId, int nX, int nY, int nDir, int nEnergy)
	{
		int nTs = 0;
		char msg[64];
		sprintf(msg, "notifyMove({id:%d, ts:%d, x:%d, y:%d, dir:%d, e:%d});\n", nId, nTs, nX, nY, nDir, nEnergy);
		Send(msg);
	}

	void NotifyTankInfo(int nId, int nHomeX, int nHomeY, int nX, int nY, int nDir)
	{
		int nTs = 0;
		char msg[64];
		sprintf(msg, "notifyInfo({id:%d, ts:%d, hx:%d, hy:%d, x:%d, y:%d, dir:%d});\n", 
			nId, nTs, nHomeX, nHomeY, nX, nY, nDir);
		Send(msg);
	}

	void NotifyTankFires(int nId, POINT ptStart, POINT ptVector)
	{
		int nTs = 0;
		char msg[64];
		sprintf(msg, "notifyFire({id:%d, ts:%d, x:%d, y:%d, vx:%d, vy:%d});\n", 
			nId, nTs, ptStart.x, ptStart.y, ptVector.x, ptVector.y);
		Send(msg);
	}

	void NotifyTankDies(int nId, POINT ptWhere)
	{
		// TODO:
	}

	/*
	// game calls
	virtual void NetCreateWorld(int nSeed) = 0;
	virtual void NetCreateTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetMoveTank(int nId, int nX, int nY, int nDir) = 0;
	virtual void NetInfoTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetFireTank(int nId, int nFireX, int nFireY, int nVectorX, int nVectorY) = 0;
	virtual void NetKillTank(int nId) = 0;
	virtual void NetRequestInfo() = 0;
	*/

	// Game stubs
	virtual void NetCreateWorld(int nSeed)
	{
		m_world.Create(nSeed);
	}

	virtual void NetCreateTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir)
	{
		CTank tank;
		tank.Create(&m_world);
		tank.m_nId = nId;
		tank.m_ptPosition.x = nX;
		tank.m_ptPosition.y = nY;
		tank.m_ptHome.x = nHomeX;
		tank.m_ptHome.y = nHomeY;
		tank.m_nDirection = nDir;
		m_world.FixPosition(tank.m_ptPosition);
		m_world.FixPosition(tank.m_ptHome);
		tank.DrawHome();
		tank.Draw(true);
		m_arrTanks.push_back(tank);
	}

	virtual void NetRequestInfo() 
	{
		_ASSERT( m_arrTanks.size() > 0 );
		//NetMovement(5);
		CTank& t = m_arrTanks[0];
		NotifyTankInfo(t.m_nId, t.m_ptHome.x, t.m_ptHome.y, t.m_ptPosition.x, t.m_ptPosition.y, t.m_nDirection);
		//NotifyTankMoves(t.m_nId, t.m_ptPosition.x, t.m_ptPosition.y, 5);
		//CTank& t = m_arrTanks[0];
		//CNetGame::NotifyTankMoves(t.m_nId, t.m_ptPosition.x, t.m_ptPosition.y, 5);
	}

	virtual void NetMoveTank(int nId, int nX, int nY, int nDir, int nEnergy)
	{
		for (int i=0; i<(int)m_arrTanks.size(); i++)
		{
			CTank& t = m_arrTanks[i];
			if ( t.m_nId == nId )
			{
				t.Draw(false);
				t.m_ptPosition.x = nX;
				t.m_ptPosition.y = nY;
				t.m_nNetworkKey = nDir;
        t.SetEnergy( nEnergy );
				t.Draw(true);
				return;
			}
		}
		_ASSERT(0);
	}

	virtual void NetKillTank(int nId)
	{
		for (int i=0; i<(int)m_arrTanks.size(); i++)
		{
			CTank& t = m_arrTanks[i];
			if ( t.m_nId == nId )
			{
				t.RemoveHome();
				t.Draw(false);
			
				POINT ptVector = {0, 0};
				CBullet bullet(&m_world, t.m_nId, t.m_ptPosition, ptVector, 50, 40);
				Explode(bullet);

				m_arrTanks.erase(m_arrTanks.begin() + i);
				return;
			}
		}
		_ASSERT(0); // !!! should not happen, but it did!
	}

	virtual void NetInfoTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir)
	{
		for (int i=0; i<(int)m_arrTanks.size(); i++)
		{
			CTank& t = m_arrTanks[i];
			if ( t.m_nId == nId )
				return;
		}

		// new tank, create!
		NetCreateTank(nId, nX, nY, nHomeX, nHomeY, nDir);
	}

	void NetFireTank(int nId, int nFireX, int nFireY, int nVectorX, int nVectorY)
	{
		POINT ptPosition;
		ptPosition.x = nFireX;
		ptPosition.y = nFireY;

		POINT ptVector;
		ptVector.x = nVectorX;
		ptVector.y = nVectorY;

		m_arrBullets.push_back( CBullet(&m_world, nId, ptPosition, ptVector) );
	}

public:
	// main calls
	void Init()
	{
	}

	void Do()
	{
		if ( CNetGame::StartRequestState() == CNetGame::EStartRequestConnected )
		{
			CNetGame::StartRequest();
		}
		if ( CNetGame::StartRequestState() == CNetGame::EStartRequestFailed )
		{
			CNetGame::StartRequestSet(CNetGame::EStartRequestReset);
			NetCreateTank(0, m_ptViewPoint.x, m_ptViewPoint.y, m_ptViewPoint.x, m_ptViewPoint.y, 8);
		}
	}

public:
	// exports
	void NetFire(POINT ptStart, POINT ptVector)
	{
		CTank& t = m_arrTanks[0];
		NotifyTankFires(t.m_nId, ptStart, ptVector);
	}

	void NetDies()
	{
		CTank& t = m_arrTanks[0];		
		NotifyTankDies(t.m_nId, t.m_ptPosition);
	}

	void NetMovement(int nDir)
	{
		CTank& t = m_arrTanks[0];

		static int nPrevDir = -1;
		static int nCounter = 0;
		if ( nPrevDir == -1 )
		{
			// will be 5 (stay)
			nPrevDir = nDir;
			return;
		}

		if (nDir != nPrevDir)
		{
			nPrevDir = nDir;
			nCounter = 0;
		}
		else
		{
			if ( nDir == 5 )
				return;

			nCounter++;
			if ( nCounter < 20 )
				return;
			else
				nCounter = 0;
		}

		NotifyTankMoves(t.m_nId, t.m_ptPosition.x, t.m_ptPosition.y, nDir, t.GetEnergy());
	}

public:
	// imports
	virtual void Explode(CBullet& bullet) = 0;
};
