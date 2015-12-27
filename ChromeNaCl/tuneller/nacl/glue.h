#include "stdafx.h"
#include "device.h"

CDevice* CDevice::m_pInstance = NULL;
CDevice g_dev;

#include "../source/game.h"
#include "websocket.h"

CNaclWebsocket network;
CGame game;

void mainInit(int nWidth, int nHeight)
{
  g_dev.display.SetDisplay(nWidth, nHeight);
  network.Create();
  game.SetNetwork(&network);
  game.Init();
}

void mainProc(uint32_t *pPixels, int nWidth, int nHeight)
{
  network.Do();
  game.Do();
  
  // blit
	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
  int tx = min(nWidth, g_dev.display.Width());
  int ty = min(nHeight, g_dev.display.Height());
  int isrc = 0, idst = 0;

  for (int y=0; y<ty; y++)
  {
//    memcpy(pPixels + idst, pBuf + isrc, tx*4);
    for (int x=0; x<tx; x++, isrc++, idst++)
      pPixels[idst] = pBuf[isrc]; 
    idst += nWidth - tx;
    isrc += g_dev.display.Width() - tx;
  }
}

void mainKey(int nCode, int nState)
{
  nState ? g_dev.OnKeyDown(nCode) : g_dev.OnKeyUp(nCode);
}

