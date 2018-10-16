#include "STM32F10x.h"
#include "source/bios/Bios.h"
#include "source/Manager.h"

extern "C" void Hardware_Init();


int main()
{
  Hardware_Init();

  CWndUserManager manager;
  manager.Create(nullptr, 0);
  manager.SetFocus();
  manager.OnMessage(nullptr, ToWord('L', 'E'), 0);
  while (1)
  {
    manager.WindowMessage(CWnd::WmTick, 0);
    manager.WindowMessage(CWnd::WmPaint, 0);
  }
  return 0;
}