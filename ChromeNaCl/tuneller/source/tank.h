struct R0 { static void Rotate(int& x, int& y) {} };
struct R90 { static void Rotate(int& x, int& y) {int t = y; y = 8-x; x = t;} };
struct R180 { static void Rotate(int& x, int& y) {x = 8-x; y = 8-y;} };
struct R270 { static void Rotate(int& x, int& y) {int t = x; x = 8-y; y = t;} };

template <class C>
void Rotate(TTankBitmap& dest, const TTankBitmap& source)
{
	for ( int y=0; y<9; y++)
		for ( int x=0; x<9; x++)
		{
			int _x = x, _y = y;
			C::Rotate(_x, _y);
			dest[y][x] = source[_y][_x];
		}
}

class CTank
{
	enum {
		HomeSize = 40,
		EntranceSize = 4
	};

	enum {
		Up = 8,
		Down = 2,
		Right = 6,
		Left = 4,
		UpLeft = 7,
		UpRight = 9,
		DownLeft = 1,
		DownRight = 3
	};

	struct TTankPoint
	{
		int nX;
		int nY;
		int nDir;
		int nFrames;
	};

public:
//	CNetGame* m_pNetGame;
	CWorld* m_pWorld;
	POINT m_ptPosition;
	POINT m_ptHome;
	int m_nDirection;	
	int m_nId;
	
	int m_nNetworkKey;
	int m_nNetworkTsStart;
	int m_nNetworkTsStop;

	float m_fEnergy;
	int m_nDirt;
	
	int m_nKilled;
	int m_nDied;
	int m_nKilledBy;

	std::vector<TTankPoint> m_arrPointQueue;

	CTank()
	{
		m_nId = -1;
		m_nKilledBy = -1;
	}

	void Create(CWorld* pWorld/*, CNetGame* pNetGame*/)
 	{
		m_nNetworkKey = 0;
		m_nId = 0;
		m_pWorld = pWorld;
		//m_pNetGame = pNetGame;

		m_ptHome.x = rand() % m_pWorld->m_nHeight;
		m_ptHome.y = rand() % m_pWorld->m_nWidth;
		m_ptPosition = m_ptHome;
		m_nDirection = 8;
		m_fEnergy = 1000;
		m_nDirt = 0;
		
		m_nKilled = 0;
		m_nDied = 0;
	}

	void DrawHome()
	{
		POINT pt;
		RECT rc;
		
		rc.top = m_ptHome.y - HomeSize/2;
		rc.bottom = m_ptHome.y + HomeSize/2;
		rc.left = m_ptHome.x - HomeSize/2;
		rc.right = m_ptHome.x + HomeSize/2;

		for (pt.y=rc.top; pt.y <= rc.bottom; pt.y++)
			for (pt.x=rc.left; pt.x <= rc.right; pt.x++)
			{
				m_pWorld->SetPixel(pt, CWorld::Track);
				if ( pt.x == rc.left || pt.x == rc.right )
					m_pWorld->SetPixel(pt, GetColor(2));
				if ( (pt.y == rc.top || pt.y == rc.bottom) && abs(pt.x - m_ptHome.x) > EntranceSize)
					m_pWorld->SetPixel(pt, GetColor(2));
			}
	}

	void RemoveHome()
	{
		POINT pt;
		RECT rc;
		
		rc.top = m_ptHome.y - HomeSize/2;
		rc.bottom = m_ptHome.y + HomeSize/2;
		rc.left = m_ptHome.x - HomeSize/2;
		rc.right = m_ptHome.x + HomeSize/2;

		for (pt.y=rc.top; pt.y <= rc.bottom; pt.y++)
			for (pt.x=rc.left; pt.x <= rc.right; pt.x++)
			{
				if ( pt.x == rc.left || pt.x == rc.right )
					m_pWorld->SetPixel(pt, CWorld::Dirt);
				if ( (pt.y == rc.top || pt.y == rc.bottom) && abs(pt.x - m_ptHome.x) > EntranceSize )
					m_pWorld->SetPixel(pt, CWorld::Dirt);
			}
	}

	static void Transform(TTankBitmap& result, const TTankBitmap& sourceStraight, const TTankBitmap& sourceDiagonal, int nDirection)
	{
		switch (nDirection)
		{
		case Up:
			Rotate<R0>(result, sourceStraight);
			break;

		case Down:
			Rotate<R180>(result, sourceStraight );
			break;

		case Right:
			Rotate<R90>(result, sourceStraight );
			break;

		case Left:
			Rotate<R270>(result, sourceStraight );
			break;

		case DownRight:
			Rotate<R0>(result, sourceDiagonal );
			break;

		case UpRight:
			Rotate<R270>(result, sourceDiagonal );
			break;

		case UpLeft:
			Rotate<R180>(result, sourceDiagonal );
			break;

		case DownLeft:
			Rotate<R90>(result, sourceDiagonal );
			break;

		default:
			memset(result, 0, sizeof(TTankBitmap));
		}
	}

	void Draw(bool bDrawOrErase)
	{
		TTankBitmap bitmap, mask;

		Transform(bitmap, bmpTankAligned, bmpTankDiagonal, m_nDirection);
		Transform(mask, bmpTankMaskAligned, bmpTankMaskDiagonal, m_nDirection);
				
		if ( bDrawOrErase )
		{
			for (int y=0; y<9; y++)
				for (int x=0; x<9; x++)
				{
					POINT pt = m_ptPosition;
					pt.x += x - 4;
					pt.y += y - 4;
					int nPixel = mask[y][x];

					if (m_pWorld->IsWater(m_pWorld->GetPixel(pt)))
						continue;

					if ( nPixel == 2 || nPixel == 1 ) 
					{
						if ( m_pWorld->IsGround(m_pWorld->GetPixel(pt)) )
							m_pWorld->SetPixel(pt, CWorld::Dirt);
					}
					if ( nPixel == 3 ) 
						m_pWorld->SetPixel(pt, CWorld::Track);
				}
		}

		for (int y=0; y<9; y++)
			for (int x=0; x<9; x++)
			{
				POINT pt = m_ptPosition;
				pt.x += x - 4;
				pt.y += y - 4;
				int nPixel = bitmap[y][x];

				if (m_pWorld->IsWater(m_pWorld->GetPixel(pt)))
					continue;

				if ( !bDrawOrErase )
				{
					if ( nPixel != 0 )
						m_pWorld->SetPixel(pt, CWorld::Track);
				} else 
				{
					if ( nPixel != 0 )
						m_pWorld->SetPixel(pt, GetColor(nPixel));
				}
			}
	}

	uint8_t GetColor(uint8_t c)
	{
		uint8_t arrPalette[][4] = {
			{0, 2, 10, 15}, {0, 1,  9, 14}, {0, 4, 12, 14},	{0, 5, 13, 15},	{0, 6, 14, 15},	{0, 8,  7, 15}};
		int nIndex = m_nId % COUNT(arrPalette);
		_ASSERT(c < 4);
		return arrPalette[nIndex][c];
	}

	bool CheckObstacle(POINT pt_, int nDirection, int& nDirt)
	{
		nDirt = 0;

		TTankBitmap bitmap;
		Transform(bitmap, bmpTankAligned, bmpTankDiagonal, nDirection);
				
		for (int y=0; y<9; y++)
			for (int x=0; x<9; x++)
			{
				POINT pt = pt_;
				pt.x += x - 4;
				pt.y += y - 4;
				int nPixel = bitmap[y][x];
				m_pWorld->FixPosition(pt);
				int nMapPixel = m_pWorld->GetPixel(pt);
				
				// (nMapPixel != CWorld::Ground && nMapPixel != CWorld::Track && nMapPixel != CWorld::Dirt )
				if ( nPixel == 0 )
					continue;
				
				if ( m_pWorld->IsGround( nMapPixel ) || m_pWorld->IsDirt( nMapPixel ) )
					nDirt++;

				if ( !m_pWorld->CanWalk(nMapPixel) ) 
				{
					return false;
				}
			}

		return true;
	}

	/*
	static void _FlipVertical(TTankBitmap& bitmap)
	{
		for (int y=0; y<9/2; y++)
			for( int x=0; x<9; x++)
			{
				std::swap(bitmap[y][x], bitmap[9-1-y][x]);
			}
	}

	static void _Rotate90(TTankBitmap& bitmap)
	{
		int n = 9;
		for(int y=0; y<n/2; y++)
			for(int x=0; x<(n+1)/2; x++)
				_cyclic_roll(bitmap[y][x], bitmap[n-1-x][y], bitmap[n-1-y][n-1-x], bitmap[x][n-1-y]);
	}

	static void _cyclic_roll(int &a, int &b, int &c, int &d)
	{
		int temp = a;
		a = b;
		b = c;
		c = d;
		d = temp;
	}*/

	bool Move(int nDir)
	{
		m_nDirt = max(m_nDirt-2, 0);
		if ( m_nDirt > 0 )
		{
			Draw(true);
			nDir = 5;
			return true; // otherwise it would send too many net messages
		}

		if ( nDir == 5 )
		{
			Draw(true);
			return false;
		}

		Draw(false);

		int nDirt = 0;

		if ( nDir != m_nDirection && CheckObstacle( m_ptPosition, nDir, nDirt ) )
		{
			m_nDirt += nDirt;
			m_nDirection = nDir;
		} else 
		{
			POINT vDirection = GetDeltaByDirection(nDir);

			POINT ptForward = m_ptPosition;
			ptForward.x += vDirection.x;
			ptForward.y += vDirection.y;

			if ( CheckObstacle(ptForward, nDir, nDirt) )
			{
				m_nDirt += nDirt;
				m_ptPosition = ptForward;
				m_nDirection = nDir;
			} else 
			{
				Draw(true);
				return false; // no movement
			}
		}

		Draw(true);
		return true; // tank moves
	}

	static POINT GetDeltaByDirection(int nDir)
	{
		POINT arrPos[10] = {{0, 0}, 
		{-1, +1}, {0, +1}, {+1, +1},
		{-1, 0}, {0, 0}, {+1, 0},
		{-1, -1}, {0, -1}, {+1, -1}};

		_ASSERT(nDir >= 0 && nDir < COUNT(arrPos));
		return arrPos[nDir];
	}

	int GetDirectionByDelta(int nDx, int nDy)
	{
		return (nDx+2) + (nDy+1)*3;
	}

	bool CanShoot()
	{
		static long lLastShoot = 0;
		long lTick = GetTickCount();

		if ( lTick - lLastShoot > 150 )
		{
			lLastShoot = lTick;
			return true;
		}
		return false;
	}

	CBullet GetBullet()
	{
		POINT ptOrigin = m_ptPosition;
		POINT ptVector = GetDeltaByDirection(m_nDirection);

		if ( (m_nDirection & 1) == 1 ) // diagonal firing
		{
			ptOrigin.x += ptVector.x * 2;
			ptOrigin.y += ptVector.y * 2;
		} else
		{
			ptOrigin.x += ptVector.x * 3;
			ptOrigin.y += ptVector.y * 3;
		}

		return CBullet(m_pWorld, m_nId, ptOrigin, ptVector);
	}

	// energy
	bool HitTest(POINT pt)
	{
		POINT ptOffset = m_pWorld->GetOffset(m_ptPosition, pt);
		ptOffset.x += 4;
		ptOffset.y += 4;

		if ( ptOffset.x < 0 || ptOffset.x > 9 || ptOffset.y < 0 || ptOffset.y > 9 )
			return false;

		TTankBitmap bitmap;
		Transform(bitmap, bmpTankAligned, bmpTankDiagonal, m_nDirection);
		
		return ( bitmap[ptOffset.y][ptOffset.x] != 0 );
	}

	void Charge(int nEnergy)
	{
		m_fEnergy += (float)nEnergy;
	}

	int GetEnergy()
	{
		return (int)m_fEnergy;
	}

	void SetEnergy(int nEnergy)
	{
		m_fEnergy = (float)nEnergy + 0.9f;
	}

	void GoHome()
	{
		m_fEnergy = 1000.0f;
		m_ptPosition = m_ptHome;
	}

	void Do()
	{
		POINT ptOffset = m_pWorld->GetOffset(m_ptPosition, m_ptHome);
		if ( abs(ptOffset.x) < HomeSize/2 && abs(ptOffset.y) < HomeSize/2 )
		{
			m_fEnergy += 1.0f;
			if ( m_fEnergy > 1000.0f )
				m_fEnergy = 1000.0f;
		}
		else
			m_fEnergy -= 0.1f;
	}

	void AddKilled()
	{
		m_nKilled++;
	}

	void AddDied()
	{
		m_nDied++;
	}

	int GetKilled()
	{
		return m_nKilled;
	}

	int GetDied()
	{
		return m_nDied;
	}

	bool IsValid()
	{
		return m_nId != -1;
	}

	void AddPointQueue(int nX, int nY, int nDir, int nFrames)
	{
		TTankPoint point;
		point.nX = nX;
		point.nY = nY;
		point.nDir = nDir;
		point.nFrames = nFrames;
		_ASSERT( nFrames < 50 );
		m_arrPointQueue.push_back(point);
	}

	bool FlushPointQueue()
	{
		if ( !m_arrPointQueue.size() )
			return false;

		for ( int i = 0; i < (int)m_arrPointQueue.size(); i++)
		{		
			TTankPoint& point = m_arrPointQueue[i];
			Draw(false);			

			// finish movement from m_ptPosition to point
			POINT ptTemp;
			ptTemp.x = point.nX;
			ptTemp.y = point.nY;

			POINT ptDiff = m_pWorld->GetOffset( m_ptPosition, ptTemp );

			// can be ptDiff divided by current movement vector?
			POINT ptMovement = GetDeltaByDirection(m_nDirection);
			int nMaxVector = max(abs(ptMovement.x), abs(ptMovement.y));
			if ( ptDiff.x != 0 || ptDiff.y != 0 )
			{
				CDebug::Print("Missing move %d, %d by vector %d, %d -> ", ptDiff.x, ptDiff.y, ptMovement.x, ptMovement.y);
				if ( nMaxVector > 0 )
				{
					int nMoves = abs(ptDiff.x) > abs(ptDiff.y) ? ptDiff.x / nMaxVector : ptDiff.y / nMaxVector;
					if ( nMoves * ptMovement.x == ptDiff.x && nMoves * ptMovement.y == ptDiff.y )
					{
						CDebug::Print("Fixing by %d moves!!!\n", nMoves);
						// finish junction
						for ( int j = 0; j < nMoves; j++ )
							Move( point.nDir );
					} else
					{
						CDebug::Print("Unable to fix :(\n", nMoves);
					}
				}
			}
			
			m_ptPosition.x = point.nX;
			m_ptPosition.y = point.nY;
			Draw(true);
			CDebug::Print("Flusing queue %d/%d -> %d frames\n", i, m_arrPointQueue.size(), point.nFrames);
			for ( int j = 0; j < point.nFrames; j++)
			{
				Move( point.nDir );
				m_pWorld->FixPosition( m_ptPosition );
			}
		}
		m_arrPointQueue.clear(); // last command should remain in queue, so we know what direction is he heading
		return true;
	}
};
