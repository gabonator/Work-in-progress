
void GfxPutPixel(int x, int y, COLORREF c)
{
	if ( x < 0 || y < 0 || x >= g_dev.display.Width() || y >= g_dev.display.Height() )
		return;

	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
	pBuf[y*g_dev.display.Width()+x] = c;
}

COLORREF GfxGetPixel(int x, int y)
{
	if ( x < 0 || y < 0 || x >= g_dev.display.Width() || y >= g_dev.display.Height() )
		return 0;

	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
	return pBuf[y*g_dev.display.Width()+x];
}

void GfxLine(int x0, int y0, int x1, int y1, COLORREF c)
{
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;)
  {
    GfxPutPixel(x0, y0, c);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

void GfxClear(COLORREF c)
{
	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
	for (int i=0; i<g_dev.display.Width()*g_dev.display.Height(); i++, pBuf++)
		*pBuf = c;
}
