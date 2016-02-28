#include "hal.h"
#include "swap/panstamp.h"
#include "swap/swap.h"
#include "swap/commonregs.h"
#include "swap/logger.h"
#include <string.h>

CSerial CSerial::m_Instance;

  void CSerial::print(char ch)
  {	  
	  if ( HAL::COM::Ready() )
		HAL::COM::Put(ch);
  }
  
  void CSerial::print(int num, EFormat eFormat)
  {
		uint8_t i = 0;
	  char strNum[8] = {};
		  
	if ( num <= 0 )
	{
		print('0');
		return;
	}
	
	if (eFormat == CSerial::DEC)  
	{
		while (num > 0)
		{
			strNum[i++] = '0' + (num % 10);
			num /= 10;
		}		
		while (i--)
			print(strNum[i]);
	}
	if (eFormat == CSerial::HEX)
	{
		while (num > 0)
		{
			strNum[i++] = "0123456789abcdef"[num % 16];
			num /= 16;
		}
		while (i--)
			print(strNum[i]);
	}
  }
  
  void CSerial::print(char* msg)
  {	  
	  while ( *msg )
		print(*msg++);	  
  }
  
  void CSerial::print(const char* msg)
  {
	  while ( *msg )
		print(*msg++);
  }
  
  uint8_t CSerial::available()
  {
	  return HAL::COM::Ready() && HAL::COM::Available();	  
  }
  
  uint8_t CSerial::read()
  {
	  return HAL::COM::Get();
  }

//#include "swap/cc1101.h"

#include <avr/interrupt.h>

void myIsr()
{
	HAL::IO::Write(HAL::IO::A2, !HAL::IO::Read(HAL::IO::A2));
}

extern LOGGER procLogger;

uint8_t hex(char c)
{
  if (c >= '0' && c <= '9' )
    return c - '0';
  if (c >= 'a' && c <= 'f' )
    return c - 'a' + 10;
  if (c >= 'A' && c <= 'F' )
    return c - 'A' + 10;
  return 0;
}

void eval(char* strCommand)
{
  Serial.print("INFO: command '");
  Serial.print(strCommand);
  Serial.print("'\r\n");

  CCPACKET packet;

  if ( strncmp(strCommand, "TX:", 3) == 0 )
  {
    packet.length = 0;
    for (uint8_t i=3; i<strlen(strCommand); i+=3)
    {
      char digit0 = strCommand[i];
      char digit1 = strCommand[i+1];
      unsigned char data = (hex(digit0) << 4) | hex(digit1);
      packet.data[packet.length++] = data;
    }

    SWPACKET swPacket(&packet);
    if ( swPacket.destAddr == swap.devAddress /*0xff && swPacket.srcAddr == 0xff*/ )
    {
      PROCESSOR* p = swap.processor;
      while (p)
      {
        if ( !p->packetHandler(&swPacket) )
        {
          Serial.print("INFO: Packet propagation cancelled\r\n");
          swPacket.function = -1;
          break;
        }

        p = p->pNext;
      }

      REGISTER* reg = NULL;
      switch(swPacket.function)
      {
        case SWAPFUNCT_CMD:
          // Valid register?
          if ((reg = swap.getRegister(swPacket.regId)) == NULL)
            break;
    
          // Filter incorrect data lengths
          if (swPacket.value.length == reg->length)
          {
            reg = reg->setData(swPacket.value.data);
            if (reg)
            {
              Serial.print("ME: ");
              LOGGER::dumpPacket(reg->save()->getStatusPacket()->prepare()->getPacket(), false);
            }
          } else
          {
            Serial.print("ME: ");            
            LOGGER::dumpPacket(reg->getStatusPacket()->prepare()->getPacket(), false);
          }
          break;
    
        case SWAPFUNCT_QRY:
          // Valid register?
          if ((reg = swap.getRegister(swPacket.regId)) == NULL)
            break;
          
          // handle write protection reg->access == Public, Readonly
          reg = reg->updateData();
          if (reg)
          {
            Serial.print("ME: ");            
            LOGGER::dumpPacket(reg->getStatusPacket()->prepare()->getPacket(), false);
          }
          break;
      }  
    } else 
    {
      // TODO: should be replaced with swPacket._send();
      Serial.print("TX: ");
      LOGGER::dumpPacket(packet, false);

      uint8_t i = SWAP_NB_TX_TRIES;
      uint8_t res;
      while(!(res = panstamp.radio.sendData(packet)) && i>1)
      {
        i--;
		for ( uint8_t t = SWAP_TX_DELAY; t--; )
			HAL_TIME_DelayMs(1);                           // Delay before sending
      }
      
      if (!res)
        Serial.print("INFO: TX error\r\n");    
    }
  }
}

extern int nIsrCalls;
unsigned long nLastCall = 0;

void RunModem()
{
  Serial.print("INFO: Built " __DATE__ " " __TIME__ "\r\n");
  Serial.print("INFO: Booting A...\r\n");
 
  //while (!panstamp.init(CFREQ_433,0))
  while (!panstamp.init(CFREQ_868,0))
  {
	  Serial.print("radio init failed!\r\n");	  	  
  }
  panstamp.radio.setCCregs();

  procLogger.setEnabled(true);

  while (!swap.init() )
  {
	  Serial.print("swap init failed!\r\n");
  }
  
  panstamp.radio.disableAddressCheck();

  swap.enterSystemState(SYSTATE_RXON);

	//while ( 1 ) PORTA.OUT = (~(HAL::TIME::GetTick() / 1000)) | 4;		

  
  Serial.print("INFO: Ready\r\n");

  Serial.print("INFO: network address/sync word=");
  Serial.print(panstamp.radio.syncWord[0], CSerial::HEX);
  Serial.print(panstamp.radio.syncWord[1], CSerial::HEX);
  Serial.print("\r\n");

  Serial.print("INFO: modem address=");
  Serial.print(panstamp.radio.devAddress, CSerial::HEX);  
  Serial.print("\r\n");
	
	char strCommand[80];
    uint8_t iCommand = 0;


	while (1)
	{
      PORTA.OUT = (HAL::TIME::GetTick() / 1000);

	  swap.tick();
  
	  while (Serial.available())
	  {
		char ch = Serial.read();
		//Serial.print(ch,CSerial::HEX);
		if ( ch == '\n' || ch == '\r' )
		{
		  if ( iCommand != -1 && iCommand > 0 )
		  {
			strCommand[iCommand] = 0;
			eval(strCommand);
		  }
		  iCommand = 0;
		} else
		if ( iCommand != -1 )
		{
		  if ( iCommand < sizeof(strCommand)-2 )
			strCommand[iCommand++] = ch;
		  else
			iCommand = -1;
		}
	  }
	
  }
}

int main(void)
{
	HAL::TIME::Init();
	HAL::COM::Init();

	HAL::IO::Configure(HAL::IO::A0, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A1, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A2, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A3, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A4, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A5, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A6, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A7, HAL::IO::InputPullUp);

	HAL::IO::Write(HAL::IO::A, 0xff);

	while ( !HAL::COM::Ready() || !HAL::COM::Available());

//	HAL_TIME_DelayMs(5000);
	
	RunModem();
	
    while (1) 
    {
		if ( HAL::COM::Ready() && HAL::COM::Available() )
		{
			char ch = HAL::COM::Get();
			PORTA.OUT = ~ch;
			HAL::COM::Put( ch );
		}
			
        PORTA.OUT = ~(HAL::TIME::GetTick() / 1000);
    }
}

