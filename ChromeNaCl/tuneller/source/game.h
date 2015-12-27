#include <stdint.h>
#include <string>
#include "gfx.h"
#include <algorithm>
#include <vector>
#include "noise.h"
#include "net.h"

// BGR for pixel buffer
#ifdef RGB
#undef RGB
#endif
#define RGB(r, g, b) ((b)|((g)<<8)|((r)<<16)|0xff000000)

class CNetGame
{
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
			int nTankId, nTankTs, nTankX, nTankY, nDir;
			_ASSERT_VALID( sscanf(message.c_str(), "notifyMove({id:%d, ts:%d, x:%d, y:%d, dir:%d})", &nTankId, &nTankTs, &nTankX, &nTankY, &nDir) == 5);
			NetMoveTank(nTankId, nTankX, nTankY, nDir);
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

	// game calls
	virtual void NetCreateWorld(int nSeed) = 0;
	virtual void NetCreateTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetMoveTank(int nId, int nX, int nY, int nDir) = 0;
	virtual void NetInfoTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir) = 0;
	virtual void NetFireTank(int nId, int nFireX, int nFireY, int nVectorX, int nVectorY) = 0;
	virtual void NetRequestInfo() = 0;

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
	void NotifyTankMoves(int nId, int nX, int nY, int nDir)
	{
		int nTs = 0;
		char msg[64];
		sprintf(msg, "notifyMove({id:%d, ts:%d, x:%d, y:%d, dir:%d});\n", nId, nTs, nX, nY, nDir);
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
};

#include "world.h"
#include "particle.h"
#include "bullet.h"
#include "bitmaps.h"
#include "tank.h"

class CGame : public CNetGame
{
	CWorld m_world;
	std::vector<CTank> m_arrTanks;
	std::vector<CBullet> m_arrBullets;
	std::vector<CParticle> m_arrParticles;

	POINT m_ptViewPoint;
	int m_nPixelScaling;

public:
	void Init()
	{
		m_ptViewPoint.x = rand() % m_world.m_nWidth;
		m_ptViewPoint.y = rand() % m_world.m_nHeight;
		m_nPixelScaling = 3;

		NetCreateWorld(0);
	}

	virtual void NetCreateWorld(int nSeed)
	{
		m_world.Create(nSeed);
	}

	virtual void NetCreateTank(int nId, int nX, int nY, int nHomeX, int nHomeY, int nDir)
	{
		CTank tank;
		tank.Create(&m_world, this);
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

	virtual void NetMoveTank(int nId, int nX, int nY, int nDir)
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
				t.Draw(true);
				return;
			}
		}
		_ASSERT(0);
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

		m_arrBullets.push_back( CBullet(&m_world, ptPosition, ptVector) );
	}

	//
	void NetMovement(int nDir)
	{
		CTank& t = m_arrTanks[0];

		static int nPrevDir = -1;
		if ( nPrevDir == -1 )
		{
			// will be 5 (stay)
			nPrevDir = nDir;
			return;
		}

		if (nDir != nPrevDir)
			nPrevDir = nDir;
		else
			return;

		NotifyTankMoves(t.m_nId, t.m_ptPosition.x, t.m_ptPosition.y, nDir);
	}

	void NetFire(POINT ptStart, POINT ptVector)
	{
		CTank& t = m_arrTanks[0];
		NotifyTankFires(t.m_nId, ptStart, ptVector);
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
		
		POINT ptVector = {0, 0};
		if ( g_dev.GetKeys()[VK_LEFT] )
			ptVector.x--;
		if ( g_dev.GetKeys()[VK_RIGHT] )
			ptVector.x++;
		if ( g_dev.GetKeys()[VK_UP] )
			ptVector.y++;
		if ( g_dev.GetKeys()[VK_DOWN] )
			ptVector.y--;

		if ( g_dev.GetKeys()[VK_SPACE] )
			if ( m_arrTanks.size() > 0 && m_arrTanks[0].CanShoot() )
			{
				CBullet bullet = m_arrTanks[0].GetBullet();
				NetFire(bullet.GetPosition(), bullet.GetVector());
				m_arrBullets.push_back( bullet );
			}

		for (int i=0; i<(int)m_arrBullets.size(); i++)
		{
			m_arrBullets[i].Do();
			
			if ( m_arrBullets[i].ShouldExplode() )
			{
				Explode(m_arrBullets[i]);
				m_arrBullets.erase( m_arrBullets.begin() + i-- );
			}
		}

		for (int i=0; i<(int)m_arrParticles.size(); i++)
		{
			m_arrParticles[i].Do();
			if ( m_arrParticles[i].ShouldDie() )
			{
				//m_arrParticles[i].Show( false );
				m_arrParticles.erase( m_arrParticles.begin() + i-- );
			}
		}
		for ( int i=0; i < (int) m_arrTanks.size(); i++ )
		{
			CTank& t = m_arrTanks[i];
			if ( i == 0 )
			{
				NetMovement(t.GetDirectionByDelta(ptVector.x, ptVector.y));
				t.Move( t.GetDirectionByDelta(ptVector.x, ptVector.y) );
				m_world.FixPosition(t.m_ptPosition);
				m_ptViewPoint = t.m_ptPosition;					
			} else
			{
				if ( t.m_nNetworkKey == 0 )
					t.Draw(true);
				else
				{
					t.Move( t.m_nNetworkKey );
					m_world.FixPosition( t.m_ptPosition );
				}
			}
		}

		Blit();
	}

	void Explode(CBullet& bullet)
	{
		for (int i=0; i<10; i++)
		{
			m_arrParticles.push_back( CParticle(&m_world, bullet.GetPosition()) );
		}
	}

	void Blit()
	{
		DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();

		POINT ptBase;
		ptBase.x = m_ptViewPoint.x - g_dev.display.WindowWidth() / m_nPixelScaling / 2;
		ptBase.y = m_ptViewPoint.y - g_dev.display.WindowHeight() / m_nPixelScaling / 2;
		m_world.FixPosition(ptBase);

		long i = 0;

		uint8_t* pMap = m_world.GetPixels();
		POINT ptCurrent;
		int _windowWidth = g_dev.display.WindowWidth();
		int _windowHeight = g_dev.display.WindowHeight();
		int _displayWidth = g_dev.display.Width();
		int _worldWidth = m_world.m_nWidth;
		int _i = 0;

		for (int y = 0, dy = 0; y < _windowHeight; y++)
		{
			_i += _displayWidth;
			i = _i;

			if ( (y % m_nPixelScaling) != 0 )
			{	
				for (int x = 0; x < _windowWidth; x++, i++)
					pBuf[i] = pBuf[i - _displayWidth];
				continue;
			}

			ptCurrent.x = ptBase.x;
			ptCurrent.y = ptBase.y + dy++;
			if (ptBase.y + dy >= m_world.m_nHeight)
				dy -= m_world.m_nHeight;

			int nOffsetBase = ptCurrent.y * _worldWidth;

			for (int x = 0; x < _windowWidth; x+=m_nPixelScaling, ptCurrent.x++)
			{
				if (ptCurrent.x >= _worldWidth)
					ptCurrent.x = 0;

				int nPixel = pMap[nOffsetBase + ptCurrent.x];

				COLORREF clr = CWorld::GetColor(nPixel); 

				for ( int q = 0; q < m_nPixelScaling; q++ )
					pBuf[i++] = clr;
			}
		}
	}
};