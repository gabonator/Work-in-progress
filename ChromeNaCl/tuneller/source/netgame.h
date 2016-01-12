int s_nRepliedTime = 0;
int s_nRepliedAt = 0;
int s_nRequestedAt = 0;
int s_nRequestedSequence = 0;
int s_nRepliedSequence = 0;

class CNetTimer 
{
private:
	struct TResponse 
	{
		TResponse() : lRequestedTimestamp(0), lRepliedTimestamp(0), lServerTimestamp(0)
		{
		}
		long lRequestedTimestamp;
		long lRepliedTimestamp;
		long lServerTimestamp;
		// calculated
		long lTrip;
		long lConstant;
	};

	std::vector<TResponse> m_arrResponses;
	int m_nFrame;
	int m_nSkipFrames;
	long m_lFirstConnectionTime;

	long m_lConstant;
	bool m_bConstantValid;
public:
	// imports
	virtual void NetRequestTime(int nSequence) = 0;
	virtual CNet::EConnectionState GetNetworkState() = 0;

	// exports
	virtual void NetOnReplyTime(int nSequence, int nTs)
	{
		_ASSERT( nSequence >= 0 && nSequence < 20 );
		m_arrResponses[nSequence].lRepliedTimestamp = GetTickCount();
		m_arrResponses[nSequence].lServerTimestamp = nTs;
		m_arrResponses[nSequence].lTrip = m_arrResponses[nSequence].lRepliedTimestamp - m_arrResponses[nSequence].lRequestedTimestamp;
		m_arrResponses[nSequence].lConstant = m_arrResponses[nSequence].lServerTimestamp - m_arrResponses[nSequence].lRequestedTimestamp;
	}

public:
	CNetTimer()
	{
		m_nFrame = 0;
		m_nSkipFrames = 0;
		m_lFirstConnectionTime = 0;
		m_arrResponses.resize(20);	

		m_lConstant = 0;
		m_bConstantValid = 0;
	}

	void Do()
	{
		if ( m_bConstantValid )
			return;

		if ( GetNetworkState() != CNet::Open )
			return;

		if ( m_lFirstConnectionTime == 0 )
			m_lFirstConnectionTime = GetTickCount();

		// wait at least 1000 ms since game start, for everything to settle down
		if ( (long)GetTickCount() < m_lFirstConnectionTime + 1000 )
			return;
		
		if ( m_nSkipFrames > 0 )
		{
			m_nSkipFrames--;
			return;
		}

		if ( m_nFrame < 20 )
		{
			NetRequestTime(m_nFrame);
			m_arrResponses[m_nFrame].lRequestedTimestamp = GetTickCount();
			m_nFrame++;
			m_nSkipFrames = 5;
			return;
		} 

		if ( m_nFrame == 20 )
		{
			// qsort by trip and choose average of first 5 constants
			long lConstantSum = 0;
			int nConstants = 0;

			for ( int i=0; i<10; i++ )
			{
				lConstantSum += m_arrResponses[i].lConstant;
				nConstants ++;
			}

			m_lConstant = lConstantSum / nConstants;
			m_bConstantValid = true;
			m_nFrame++;
		}
	}

public:
	long GetTs()
	{
		return GetTickCount() + m_lConstant;
	}

	bool TsValid()
	{
		return m_bConstantValid;
	}
};

class CNetGame : public CGameCommon, public CNetTimer
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

protected:
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
			NetMoveTank(nTankId, nTankX, nTankY, nDir, nEnergy, nTankTs);
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
		if ( message.substr(0, 9) == "replyTime" )
		{
			int nN = 0, nTs = 0;
			_ASSERT_VALID( sscanf(message.c_str(), "replyTime({n:%d, ts:%d})", &nN, &nTs) == 2 );
			NetOnReplyTime(nN, nTs);
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
		int nTs = GetTs();
		char msg[128];
		sprintf(msg, "notifyMove({id:%d, ts:%d, x:%d, y:%d, dir:%d, e:%d});\n", nId, nTs, nX, nY, nDir, nEnergy);
		Send(msg);
	}

	void NotifyTankInfo(int nId, int nHomeX, int nHomeY, int nX, int nY, int nDir)
	{
		int nTs = GetTs();
		char msg[128];
		sprintf(msg, "notifyInfo({id:%d, ts:%d, hx:%d, hy:%d, x:%d, y:%d, dir:%d});\n", 
			nId, nTs, nHomeX, nHomeY, nX, nY, nDir);
		Send(msg);
	}

	void NotifyTankFires(int nId, POINT ptStart, POINT ptVector)
	{
		int nTs = GetTs();
		char msg[128];
		sprintf(msg, "notifyFire({id:%d, ts:%d, x:%d, y:%d, vx:%d, vy:%d});\n", 
			nId, nTs, ptStart.x, ptStart.y, ptVector.x, ptVector.y);
		Send(msg);
	}

	void NetRequestTime(int nSequence)
	{
		char msg[128];
		sprintf(msg, "requestTime({n:%d});\n", nSequence);
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

	virtual void NetMoveTank(int nId, int nX, int nY, int nDir, int nEnergy, int nTs)
	{
		for (int i=0; i<(int)m_arrTanks.size(); i++)
		{
			CTank& t = m_arrTanks[i];
			if ( t.m_nId == nId )
			{
				t.Draw(false);
				// Apply moved since!
				// simuluj pohyb, ale pozor, co ak nas caka dalsia sprava a pocas simulacie uz zmenil smer?
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
		CNetTimer::Do();

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

	virtual CNet::EConnectionState GetNetworkState()
	{
		return m_pNet ? m_pNet->GetState() : CNet::Error;
	}

public:
	// imports
	virtual void Explode(CBullet& bullet) = 0;
//	virtual void NetOnReplyTime(int nSequence, int nTs) = 0;
};
