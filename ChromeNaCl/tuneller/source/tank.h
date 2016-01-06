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

public:
//	CNetGame* m_pNetGame;
	CWorld* m_pWorld;
	POINT m_ptPosition;
	POINT m_ptHome;
	int m_nDirection;	
	int m_nId;
	int m_nNetworkKey;
	float m_fEnergy;
	int m_nDirt;
	
	int m_nKilled;
	int m_nDied;

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

	void Transform(TTankBitmap& result, const TTankBitmap& sourceStraight, const TTankBitmap& sourceDiagonal, int nDirection)
	{
		switch (nDirection)
		{
		case Up:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			break;

		case Down:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_FlipVertical(result);
			break;

		case Right:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_Rotate90(result);
			break;

		case Left:
			memcpy(result, sourceStraight, sizeof(TTankBitmap));
			_FlipVertical(result);
			_Rotate90(result);
			break;

		case DownRight:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			break;

		case UpRight:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_FlipVertical(result);
			break;

		case UpLeft:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_Rotate90(result);
			_FlipVertical(result);
			break;

		case DownLeft:
			memcpy(result, sourceDiagonal, sizeof(TTankBitmap));
			_Rotate90(result);
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

	void _FlipVertical(TTankBitmap& bitmap)
	{
		for (int y=0; y<9/2; y++)
			for( int x=0; x<9; x++)
			{
				std::swap(bitmap[y][x], bitmap[9-1-y][x]);
			}
	}

	void _Rotate90(TTankBitmap& bitmap)
	{
		int n = 9;
		for(int y=0; y<n/2; y++)
			for(int x=0; x<(n+1)/2; x++)
				_cyclic_roll(bitmap[y][x], bitmap[n-1-x][y], bitmap[n-1-y][n-1-x], bitmap[x][n-1-y]);
	}

	void _cyclic_roll(int &a, int &b, int &c, int &d)
	{
		int temp = a;
		a = b;
		b = c;
		c = d;
		d = temp;
	}

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

	POINT GetDeltaByDirection(int nDir)
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
    m_fEnergy = (float)nEnergy;
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
};
