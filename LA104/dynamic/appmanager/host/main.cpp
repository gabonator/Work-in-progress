#include "STM32F10x.h"
#include "source/bios/Bios.h"
#include "source/Manager.h"

/*
TODO: implement live usb conn
extern "C" {
ui32  __Bios(ui8 Item, ui32 Var);
}

void DiskConfig(void)
{
    USB_Init();
    Disk_Init();
    Init_Fat_Value();
}

void Hardware_Init(void)
{
    __Bios(PWRCTRL, INIT);        // 
    __Bios(KEYnDEV, INIT);        // 
    __Bios(NIVCPTR, 0x8000);      // 
//  __Bios(SYSTICK, 1000);        // 
    SysTick_Config(SystemCoreClock / 1000);
    __Bios(BUZZDEV, INIT);        // 
    __Bios(BUZZDEV, 50);
    //Beep_mS(200);
    __Bios(FLSHDEV, INIT);        // SPI
    __Bios(USBDEV, INIT);         // USB
    DiskConfig();                 // 
    __Bios(IN_PORT, INIT);        // DAC
//  __Bios(IN_PORT, 3000);        // 3V
    __Bios(IN_PORT, gItemParam[THRESHOLD]*100);

}
*/

int main()
{
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