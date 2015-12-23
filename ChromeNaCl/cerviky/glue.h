
#include "stdafx.h"
#include "device.h"

CDevice* CDevice::m_pInstance = NULL;
CDevice g_dev;

#include "gfx.h"
#include "tools.h"
#include "cerv.h"
#include "player.h"
#include "game.h"

float CCerv::g_fSpeedMultiply = 0.6f;
CGame game;

DWORD *pPostBuffer = NULL;
int nPostWidth = 0;
int nPostHeight = 0;

void mainInit(int nWidth, int nHeight)
{
  g_dev.display.SetDisplay(nWidth, nHeight);
  game.Init();
}

void mainProc(uint32_t *pPixels, int nWidth, int nHeight)
{
  game.Do();
  
  // blit
	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
  int tx = min(nWidth, g_dev.display.Width());
  int ty = min(nHeight, g_dev.display.Height());
  int isrc = 0, idst = 0;

  for (int y=0; y<ty; y++)
  {
    for (int x=0; x<tx; x++, isrc++, idst++)
      pPixels[idst] = pBuf[isrc] | 0xff000000; 
    idst += nWidth - tx;
    isrc += g_dev.display.Width() - tx;
  }

  pPostBuffer = pPixels;
  nPostWidth = nWidth;
  nPostHeight = nHeight;

  game.m_Powerup.Render(NULL);
  game.m_Bullets.Render(NULL);

  pPostBuffer = NULL;
}

void mainKey(int nCode, int nState)
{
  nState ? g_dev.OnKeyDown(nCode) : g_dev.OnKeyUp(nCode);
}

void GfxPostDraw(RECT r, COLORREF clr)
{
  _ASSERT(pPostBuffer);
  if (!pPostBuffer)
    return;

  for (int y=r.top; y<r.bottom; y++)
  {
//    DWORD* pBase = pPostBuffer + y * pPostWidth;
    for (int x=r.left; x<r.right; x++)
      pPostBuffer[y*nPostWidth+x] = clr | 0xff000000;
  }
}
