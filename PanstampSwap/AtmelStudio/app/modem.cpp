#include <string.h>
#include <avr/io.h>

#include "modem.h"
#include "../common.h"
#include "../utils/utils.h"
#include "../swap/commonregs.h"
#include "../swap/swap.h"
#include "../swap/logger.h"

extern LOGGER procLogger;

CModem::CModem()
{
	nLastCall = 0;
	iCommand = 0;
}

void CModem::eval(char* strCommand)
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
			unsigned char data = (CUtils::nibble(digit0) << 4) | CUtils::nibble(digit1);
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

void CModem::Init()
{
	Serial.print("INFO: Built " __DATE__ " " __TIME__ "\r\n");
	Serial.print("INFO: Booting modem...\r\n");

	procLogger.setEnabled(true);

	while (!panstamp.InitRadio())
	{
		Serial.print("radio init failed!\r\n");
	}

	radio.disableAddressCheck();

	swap.enterSystemState(SYSTATE_RXON);

	Serial.print("INFO: Ready\r\n");
	Serial.print("INFO: network address/sync word=");
	Serial.print(panstamp.radio.syncWord[0], CSerial::HEX);
	Serial.print(",");
	Serial.print(panstamp.radio.syncWord[1], CSerial::HEX);
	Serial.print("\r\n");

	Serial.print("INFO: modem address=");
	Serial.print(panstamp.radio.devAddress, CSerial::HEX);
	Serial.print("\r\n");
}

void CModem::Loop()
{
	PORTA.OUT = (HAL::TIME::GetTick() / 1000);

	swap.tick();
		
	while (Serial.available())
	{
		char ch = Serial.read();
		
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
			if ( iCommand < (int) sizeof(strCommand)-2 )
				strCommand[iCommand++] = ch;
			else
				iCommand = -1;
		}
	}
}
