
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

void gameProc(uint32_t* data, int width, int height)
{
  static bool bStarted = false;
  if (!bStarted)
  {
    bStarted = true;
    g_dev.display.SetDisplay(width, height);
    game.Init();
  }
  game.Do();

	DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();
  int tx = min(width, g_dev.display.Width());
  int ty = min(height, g_dev.display.Height());
  int isrc = 0, idst = 0;
  for (int y=0; y<ty; y++)
  {
    for (int x=0; x<tx; x++, isrc++, idst++)
      data[idst] = pBuf[isrc] | 0xff000000; 
    idst += width - tx;
    isrc += g_dev.display.Width() - tx;
  }

}

