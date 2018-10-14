#include <stdint.h>

volatile uint32_t gCounter = 0;

void SysTick_Handler(void)
{
  // TODO: check timer init
  gCounter++;
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
// TODO: implement usb conn
//    USB_Istr();
}
