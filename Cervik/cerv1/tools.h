#include "stdafx.h"

class CTools
{
public:
	static bool TestMask(int x, int y)
	{
		static const int mask[] = {
		 0, 1, 2, 1, 0,
		 1, 4, 8, 4, 1,
		 2, 8, 8, 8, 2,
		 1, 4, 8, 4, 1,
		 0, 1, 2, 1, 0};
		 if ( x < -2 || y < -2 || x > 2 || y > 2 )
			 return false;
		 int i = (y+2)*5 + (x+2);
		 _ASSERT( i >= 0 && i < COUNT(mask) );
		 return mask[i] ? true : false;
	}

	static COLORREF InterpolateColor( COLORREF clrA, COLORREF clrB, int nLevel )
	{
		int br = GetRValue(clrB)*nLevel;
		int bg = GetGValue(clrB)*nLevel;
		int bb = GetBValue(clrB)*nLevel;
		nLevel = 255-nLevel;
		int ar = GetRValue(clrA)*nLevel;
		int ag = GetGValue(clrA)*nLevel;
		int ab = GetBValue(clrA)*nLevel;
		ar = (ar+br) / 256;
		ag = (ag+bg) / 256;
		ab = (ab+bb) / 256;
		return RGB(ar, ag, ab);
	}
	static void GetMapArea(int& nLeft, int& nTop, int& nRight, int& nBottom)
	{
		nLeft = 20;
		nTop = 20;
		nRight = 900;
		nBottom = 550;
	}
	static float RandRange(float fLow, float fHigh)
	{
		int nLevel = rand()%1000;
		return fLow + (fHigh-fLow)*nLevel/1000;
	}
};
