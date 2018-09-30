#include "stm32f10x.h"
#include "USB_bot.h"
#include "usb_core.h"

u32 SystemCoreClock   = 72000000; // 72MHz System Clock Frequency

void USB_Istr(void)
{
}

void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
}

void SetEPTxCount(uint8_t bEpNum, uint16_t wCount)
{
}

void SetEPTxStatus(uint8_t bEpNum, uint16_t wState)
{
}

Bulk_Only_CSW CSW;
u8 Bot_State;

void SetEPRxStatus(uint8_t bEpNum, uint16_t wState)
{
}

void Set_CSW (u8 CSW_Status, u8 Send_Permission)
{
}
u8 Bulk_Buff[BULK_MAX_PACKET_SIZE];  // Data_ data buffer
u16 Data_Len;

RESULT PowerOff()
{
  return 0;
}

void USB_Init(void)
{
}
