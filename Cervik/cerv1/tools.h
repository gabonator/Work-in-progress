#include "stdafx.h"

class CTools
{
public:
	static int TestMask(int x, int y);
	static COLORREF InterpolateColor( COLORREF clrA, COLORREF clrB, int nLevel );
	static void GetMapArea(int& nLeft, int& nTop, int& nRight, int& nBottom);
	static float RandRange(float fLow, float fHigh);
};
