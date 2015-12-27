#pragma once

COLORREF GfxInterpolateColor( COLORREF clrA, COLORREF clrB, int nLevel )
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
