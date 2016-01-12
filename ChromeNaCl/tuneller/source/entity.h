class CEntity
{
protected:
	CWorld* m_pWorld;

public:
	CEntity(CWorld* pWorld) : m_pWorld(pWorld)
	{
	}

	virtual void Draw(bool bShowOrHide) {_ASSERT(0);}
	virtual void Do() {_ASSERT(0);}
	virtual void OnTankFires(CTank& t, std::vector<CBullet>& arrBullets) { _ASSERT(0); }

protected:
	void Draw(bool bDrawOrErase, TTankBitmap& bitmap, POINT ptBase)
	{
		for (int y=0; y<9; y++)
			for (int x=0; x<9; x++)
			{
				POINT pt = ptBase;
				pt.x += x - 4;
				pt.y += y - 4;
				int nPixel = bitmap[y][x];

				if ( nPixel == 0 )
					continue;
				if ( m_pWorld->IsWater(m_pWorld->GetPixel(pt)) )
					continue;

				if ( bDrawOrErase )
					m_pWorld->SetPixel(pt, nPixel);
				else
					m_pWorld->SetPixel(pt, CWorld::Track);
			}
	}

	void Normalize(POINT& pt)
	{
		if ( pt.x != 0 ) 
			pt.x /= abs(pt.x);
		if ( pt.y != 0 ) 
			pt.y /= abs(pt.y);
	}

	int DistanceSq(POINT ptA, POINT ptB)
	{
		POINT ptV;
		ptV.x = ptB.x - ptA.x;
		ptV.y = ptB.y - ptA.y;
		return LengthSq(ptV);
	}

	int LengthSq(POINT ptVector)
	{
		return ptVector.x * ptVector.x + ptVector.y * ptVector.y;				
	}

};
