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

#include "api.h"
#include "world.h"
#include "particle.h"
#include "bullet.h"
#include "bitmaps.h"
#include "tank.h"
#include "debug/debug.h"
#include "entity.h"
#include "gamecommon.h"
#include "powerups.h"
#include "netgame.h"

extern std::vector<std::pair<std::string, std::string> > g_arrMainArgs;

class CGame : public CNetGame
{
public:
	void Init()
	{
		m_ptViewPoint.x = rand() % m_world.m_nWidth;
		m_ptViewPoint.y = rand() % m_world.m_nHeight;
		m_nPixelScaling = 3;

		m_world.Create(0);
		CNetGame::Init();

		//NetCreateTank(0, m_ptViewPoint.x, m_ptViewPoint.y, m_ptViewPoint.x, m_ptViewPoint.y, 8);

	}

	void CheckExtras()
	{
		static bool bExtrasCreated = false;
		if ( bExtrasCreated )
			return;

		if ( GetTanks().size() == 0 )
			return;

		bExtrasCreated = true;

		POINT pt = GetTanks()[0].m_ptPosition;

		m_arrEntities.push_back(std::shared_ptr<CEntity>(new CDrone(this)));
		CDrone* p = (CDrone*)m_arrEntities[0].get();
		p->m_ptPosition.x = pt.x + 50;
		p->m_ptPosition.y = pt.y + 50;

		m_arrEntities.push_back(std::shared_ptr<CEntity>(new CSideShot(this)));
		CSideShot* ps = (CSideShot*)m_arrEntities[1].get();
		ps->m_ptPosition.x = pt.x + 30;
		ps->m_ptPosition.y = pt.y + 30;

	}
	void Do()
	{
		CheckExtras();
		CNetGame::Do();

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

				std::vector<CBullet> arrExtraBullets;
				for (int i=0; i<(int)m_arrEntities.size(); i++)
					m_arrEntities[i]->OnTankFires(m_arrTanks[0], arrExtraBullets);

				for (int i=0; i<(int)arrExtraBullets.size(); i++)
				{
					CBullet& bullet = arrExtraBullets[i];
					NetFire(bullet.GetPosition(), bullet.GetVector());
					m_arrBullets.push_back( bullet );
				}
			}

		static LONG lLastTick = 0;
		long lTick = GetTickCount();
		int nFps = 40;
		long lInterval = 1000 / nFps;

		if ( lLastTick == 0 )
			lLastTick = lTick;

		int nFramesPassed = (lTick - lLastTick) / lInterval;
		for ( int i = 0; i < nFramesPassed; i++ )
			SimulateStep(ptVector);
		lLastTick += nFramesPassed * lInterval;

		Blit();
	}

	void SimulateStep(POINT ptVector)
	{
		for (int i=0; i<(int)m_arrEntities.size(); i++)
			m_arrEntities[i]->Draw(false);

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
				CheckHit( m_arrParticles[i] );
				//m_arrParticles[i].Show( false );
				m_arrParticles.erase( m_arrParticles.begin() + i-- );
			}
		}
		for ( int i=0; i < (int) m_arrTanks.size(); i++ )
		{
			CTank& t = m_arrTanks[i];
			t.Do();

			if ( t.GetEnergy() < 0 )
			{
				CApi::SendMessage( (char*)"Umrel si!" );
				t.AddDied();
				NetDies();

				t.Draw(false);
				POINT ptVector = {0, 0};
				CBullet bullet(&m_world, t.m_nId, t.m_ptPosition, ptVector, 50, 40);
				Explode(bullet);
				t.GoHome();
				t.Draw(true);
			}

			if ( i == 0 )
			{
				// user tank
				int nDirection = t.GetDirectionByDelta(ptVector.x, ptVector.y);
				bool bMoved = t.Move( nDirection );   // TODO: sometime it is blocked by exploding particles! -> excessive net traffic
				NetMovement(bMoved ? nDirection : 5);

				m_world.FixPosition(t.m_ptPosition);
				m_ptViewPoint = t.m_ptPosition;					
			} else
			{
				// remote tank
				if ( t.m_nNetworkKey == 0 )
					t.Draw(true);
				else
				{
					t.Move( t.m_nNetworkKey );
					m_world.FixPosition( t.m_ptPosition );
				}
			}
		}

		for (int i=0; i<(int)m_arrEntities.size(); i++)
		{
			m_arrEntities[i]->Do();
			m_arrEntities[i]->Draw(true);
		}

	}

	void CheckHit(CParticle& particle)
	{
		for ( int i=0; i < (int) m_arrTanks.size(); i++ )
		{
			if ( m_arrTanks[i].HitTest(particle.GetPosition()) )
			{
				if ( particle.IsFriendly( m_arrTanks[i].m_nId ) )
					m_arrTanks[i].Charge(-1); 
				else
				{
					bool bWasAlive = m_arrTanks[i].GetEnergy() >= 0;
					m_arrTanks[i].Charge(-7);
					bool bIsAlive = m_arrTanks[i].GetEnergy() >= 0;
					
					if ( bWasAlive && !bIsAlive )
					{
						GetTankById( particle.GetOwnerId() ).AddKilled();
						CApi::SendMessage( (char*)"Nejaky tank umrel!" );
					}

				}
			}
		}
	}

	virtual void Explode(CBullet& bullet)
	{
		for (int i=0; i<bullet.GetParticles(); i++)
		{
			int nPower = bullet.GetParticlePower();
			float fSpeed = 1.0f;
			if ( nPower > 20 )
			{
				nPower = (nPower / 2) + rand() % (nPower / 2);  // 50% .. 100%
				fSpeed = 0.2f + (rand() % 1000) * 0.8f / 1000.0f;
			}

			m_arrParticles.push_back( CParticle(&m_world, bullet.GetOwnerId(), bullet.IsFriendly(), 
				bullet.GetPosition(), nPower, fSpeed) );
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

		char *strNetMode = (char*)"?";
		switch(m_pNet->GetState())
		{
			case CNet::Connecting: strNetMode = (char*)"Connecting"; break;
			case CNet::Open: strNetMode = (char*)"Open"; break;
			case CNet::Closed: strNetMode = (char*)"Closed"; break;
			case CNet::Error: strNetMode = (char*)"Error"; break;
			default: break;
		}

		const char *msg = TsValid() ? (((GetTs() % 1000) < 250) ? "###" : ":::") : "---"; 
		CDebug::Print(0, 0, "%s (%s) [%d, %d] %s", m_pNet->GetServerUrl().c_str(), strNetMode, m_ptViewPoint.x, m_ptViewPoint.y, msg);
		for ( int i = 0; i < (int)m_arrTanks.size(); i++ )
		{
			CTank& t = m_arrTanks[i];
			CDebug::Print(0, 14 + i*14, "Tank %d: Energy = %3d%% Kills =%2d, Deaths =%2d", 
				t.m_nId, t.GetEnergy()/10, t.GetKilled(), t.GetDied());
		}

/*
		if ( (GetTs() % 1000) < 250 )
		{
			CDebug::Bar(20, 20, 200, 200, RGB(255, 0, 0));
		}
*/

	}
};
