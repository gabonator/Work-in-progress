int s_nRepliedTime = 0;
int s_nRepliedAt = 0;
int s_nRequestedAt = 0;
int s_nRequestedSequence = 0;
int s_nRepliedSequence = 0;

void CNetCommand::Send()
{
	s_pGame->Send( ToString() );
}

#include "netcommands.h"

class CNetTimer : public CGameCommon
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
		TResponse& response = m_arrResponses[nSequence];
		_ASSERT( nSequence >= 0 && nSequence < 20 );
		response.lRepliedTimestamp = GetTickCount();
		response.lServerTimestamp = nTs;
		response.lTrip = response.lRepliedTimestamp - response.lRequestedTimestamp;
		response.lConstant = response.lServerTimestamp - response.lRequestedTimestamp;
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
			long long lConstantSum = 0;
			int nConstants = 0;

			char strDebug[512] = "Round trip times: ";
			for ( int i=0; i<20; i++ )
			{
				char strSingle[32];
				sprintf(strSingle, "%d, ", m_arrResponses[i].lTrip);
				strcat(strDebug, strSingle);

				lConstantSum += m_arrResponses[i].lConstant;
				nConstants ++;
			}
		
			OutputDebugStringA(strDebug);

			m_lConstant = (long)(lConstantSum / nConstants);
			m_bConstantValid = true;
			m_nFrame++;
		}
	}

public:
	virtual long GetTs()
	{
		return GetTickCount() + m_lConstant;
	}

	virtual long GetTsOffset()
	{
		return m_lConstant;
	}

	bool TsValid()
	{
		return m_bConstantValid;
	}
};

class CNetGame : public CNetTimer
{
protected:
	CNet* m_pNet;
	long m_nTimeOffset;
	std::list<std::string> m_lstRawCommands;  // THREAD SAFE!

public:
	CNetGame()
	{
		m_nTimeOffset = 0;
		m_pNet = NULL;
		m_nStartRequestState = EStartRequestFailed;

		CNetCommand::s_pGame = this;
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
		m_lstRawCommands.push_back(message);
	}

	void ProcessMessages()
	{
		while ( m_lstRawCommands.size() )
		{
			m_lstCommands.push_back(CNetCommandFactory::FromString(m_lstRawCommands.front()));
			m_lstRawCommands.pop_front();
		}

		while ( m_lstCommands.size() )
		{
			std::shared_ptr<CNetCommand> sNetCommand = m_lstCommands.front();
			m_lstCommands.pop_front();

			sNetCommand->Do();
		}
	}

	bool IsConnected()
	{
		return m_pNet ? true : false;
	}

	virtual void Send(std::string str)
	{
		if (!m_pNet)
			return;

		m_pNet->Send(str);
	}

	// requests

	void StartRequest()
	{
		m_nStartRequestTime = GetTickCount();
		CNetGame::StartRequestSet(EStartRequestPending);
		CNetCommandStart().Send();
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

	// game notifications
	void NotifyTankMoves(int nId, int nX, int nY, int nDir, int nEnergy)
	{
		CNetCommandNotifyMove(nId, nX, nY, nDir, nEnergy).Send();
	}

	void NotifyTankInfo(int nId, int nHomeX, int nHomeY, int nX, int nY, int nDir)
	{
		CNetCommandNotifyInfo(nId, nHomeX, nHomeY, nX, nY, nDir).Send();
	}

	void NotifyTankFires(int nId, POINT ptStart, POINT ptVector)
	{
		CNetCommandNotifyFire(nId, ptStart.x, ptStart.y, ptVector.x, ptVector.y).Send();
	}

	void NetRequestTime(int nSequence)
	{
		CNetCommandTime(nSequence).Send();
	}

	void NotifyTankDies(int nId, POINT ptWhere, int nIdBy)
	{
		CNetCommandNotifyKilled(nId, ptWhere.x, ptWhere.y, nIdBy).Send();
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

	virtual void NetMoveTank(int nId, int nX, int nY, int nDir, int nEnergy, int nTs, int nStopTs)
	{
		int nFrameInterval = 1000 / 40;
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
				t.AddPointQueue(nX, nY, nDir, (nStopTs - nTs) / nFrameInterval );
				
				t.m_nNetworkKey = nDir;
				//t.m_nNetworkTsStart = nTs;
				//t.m_nNetworkTsStop = nStopTs;
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
		ProcessMessages();
		CNetTimer::Do();

		if ( CNetGame::StartRequestState() == EStartRequestConnected )
		{
			CNetGame::StartRequest();
		}
		if ( CNetGame::StartRequestState() == EStartRequestFailed )
		{
			CNetGame::StartRequestSet(EStartRequestReset);
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
		NotifyTankDies(t.m_nId, t.m_ptPosition, t.m_nKilledBy);
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
