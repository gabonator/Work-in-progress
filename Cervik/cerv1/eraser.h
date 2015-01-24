

class CEraser
{
	struct TPoint
	{
		TPoint() {}
		TPoint(int _x, int _y, int _ttl) : x(_x), y(_y), ttl(_ttl) {}
		int x, y, ttl;
	};

public:

	CArray<TPoint> arrCache;

	CEraser()
	{
		arrCache.SetSize(0, 2000);
	}

	void Start(int x, int y)
	{
		CArray<TPoint> arrTemp;
		arrTemp.Copy(arrCache);
		arrCache.RemoveAll();
		
		Add(x, y, 800);
		Do(100);

		arrCache.Append(arrTemp);
	}

	void Add(int x, int y, int ttl)
	{
		GfxPutPixel(x, y, RGB(0, 0, 0));
		arrCache.Add( TPoint(x, y, ttl ) );
	}

	bool Erasable(COLORREF c)
	{
		return (c != RGB(0, 0, 0)) && (c != RGB(255, 255, 255));
	}

	void Do(int nPasses = 5)
	{
		for ( int t = 0; t < nPasses; t++ )
		{
			if ( arrCache.GetSize() == 0 )
				return;

			int nPrevCount = arrCache.GetSize();
			int i = rand() % nPrevCount;

			TPoint p = arrCache[i];
			if ( p.ttl > 0 )
			{
				if ( Erasable( GfxGetPixel( p.x - 1, p.y ) ) ) Add(p.x-1, p.y, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x + 1, p.y ) ) ) Add(p.x+1, p.y, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x, p.y - 1 ) ) ) Add(p.x, p.y-1, p.ttl-1);
				if ( Erasable( GfxGetPixel( p.x, p.y + 1 ) ) ) Add(p.x, p.y+1, p.ttl-1);
			}

			if ( arrCache.GetSize() == nPrevCount ) 
			{
				arrCache.RemoveAt( i );
			} else
			{
				TPoint pLast = arrCache.GetAt( arrCache.GetSize() - 1 );
				arrCache.SetSize(arrCache.GetSize()-1);
				arrCache.SetAt(i, pLast);
			}	
		}
	}
};