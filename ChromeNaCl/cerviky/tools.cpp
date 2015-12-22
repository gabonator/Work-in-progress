#include "stdafx.h"
#include "tools.h"
#include "Device.h"
extern CDevice g_dev;

	/*static*/ int CTools::TestMask(int x, int y)
	{
		static const int mask[] = {
		 0, 1, 4, 3, 0,
		 3, 6, 8, 6, 3,
		 4, 8, 8, 8, 4,
		 3, 6, 8, 6, 3,
		 0, 3, 4, 3, 0};
		 if ( x < -2 || y < -2 || x > 2 || y > 2 )
			 return false;
		 int i = (y+2)*5 + (x+2);
		 _ASSERT( i >= 0 && i < COUNT(mask) );
		 return mask[i]; // ? true : false;
	}

	/*static*/ COLORREF CTools::InterpolateColor( COLORREF clrA, COLORREF clrB, int nLevel )
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

	/*static*/ void CTools::GetMapArea(int& nLeft, int& nTop, int& nRight, int& nBottom)
	{
		nLeft = 10;
		nTop = 10;
		nRight = g_dev.display.WindowWidth() - 10;
		nBottom = g_dev.display.WindowHeight() - 10;
	}

	/*static*/ float CTools::RandRange(float fLow, float fHigh)
	{
		int nLevel = rand()%1000;
		return fLow + (fHigh-fLow)*nLevel/1000;
	}
