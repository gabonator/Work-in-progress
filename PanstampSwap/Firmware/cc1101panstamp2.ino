#define CC1101_GDO 2

#include "cc1101.h"
#include "panstamp.h"
#include "logger.h"
#include "swap.h"

#define TXER
//#define MODEM

#ifdef MODEM
char strCommand[80];
uint8_t iCommand = 0;

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
  Serial.print("'\n");

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
    if ( swPacket.destAddr == 0xff && swPacket.srcAddr == 0xff )
    {
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
      Serial.print("TX: ");
      LOGGER::dumpPacket(packet, false);

      uint8_t i = SWAP_NB_TX_TRIES;
      uint8_t res;
      while(!(res = panstamp.radio.sendData(packet)) && i>1)
      {
        i--;
        delay(SWAP_TX_DELAY);
      }
      
      if (!res)
        Serial.print("INFO: TX error\n");    
    }
  }
/*
  if ( strncmp(strCommand, "EM:", 3) == 0 )
  {
    packet.length = 0;
    for (uint8_t i=3; i<strlen(strCommand); i+=3)
    {
      char digit0 = strCommand[i];
      char digit1 = strCommand[i+1];
      unsigned char data = (hex(digit0) << 4) | hex(digit1);
      packet.data[packet.length++] = data;
    }

    packet.rssi = 0;
    packet.lqi = 0;
    packet.crc_ok = 1;
    //EM:9F,01,00,AB,01,9F,00
    //TX:ff,ff,00,aa,01,aa,00
    
    SWAP::onPacketReceived(&packet);
  }
*/
}

void setup()
{
  Serial.begin(9600); 
  Serial.print("INFO: Booting modem\n");

  panstamp.init(CFREQ_433,0);
  panstamp.radio.setCCregs();
  swap.init();
  panstamp.radio.disableAddressCheck();
  swap.enterSystemState(SYSTATE_RXON);
  procLogger.setEnabled(true);
  
  Serial.print("INFO: Ready\n");

  Serial.print("INFO: modem address=");
  Serial.print(panstamp.radio.devAddress, HEX);  
  Serial.print("\n");
}

void loop()
{
  while (Serial.available())
  {
    char ch = Serial.read();
    if ( ch == '\n' )
    {
      if ( iCommand != -1 )
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
#endif

#ifdef TXER
#define LED 3


extern LOGGER procLogger;
extern REGISTER regProductCode;
extern REGISTER regTxInterval;
extern REGISTER regVoltSupply;
extern REGISTER regSensor;

extern REGISTER regTargetAddr;
extern REGISTER regMediateAddr;

void setup()
{
  Serial.begin(9600); 
  Serial.print("\nBooting DHT22 slave TXer\n");

  // Init SWAP stack
  Serial.print("Initializing panstamp...");
  panstamp.init(CFREQ_433, 0);
  Serial.print(" Ok.\n");
  Serial.print("Initializing SWAP...");
  swap.init();
  Serial.print(" Ok.\n");

  Serial.print("Panstamp network=");
  Serial.print(panstamp.radio.syncWord[1], HEX);  
  Serial.print(panstamp.radio.syncWord[0], HEX);  
  Serial.print(", address=");
  Serial.print(panstamp.radio.devAddress, HEX);  
  Serial.print("\n");
  
  // Transmit product code
  //regProductCode.getData()->sendSwapStatus();
  //procLogger.setEnabled(true);

  swap.getRegister(regProductCode.id)
    ->updateData()
    ->getStatusPacket()
    ->prepare()
    ->_send();

  // Enter SYNC state
  swap.enterSystemState(SYSTATE_SYNC);
/*
  Serial.print("Listening...");
  // During 3 seconds, listen the network for possible commands whilst the LED blinks
  for(int i=0 ; i<6 ; i++)
  {
    delay(500);
  }
  Serial.print(" Done.\n");
*/

  // Transmit periodic Tx interval
  swap.getRegister(regTxInterval.id)->updateData()->getStatusPacket()->prepare()->_send();
  // Transmit power voltage
  swap.getRegister(regVoltSupply.id)->updateData()->getStatusPacket()->prepare()->_send();
  // Switch to Rx OFF state
  swap.enterSystemState(SYSTATE_RXOFF); // RX on?
  Serial.print("setup end\n");
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  Serial.print("Sending... ");
  
  // Transmit sensor data
  bool bSuccess = swap.getRegister(regSensor.id)
    ->updateData()
    ->sendSwapStatusAck(regTargetAddr.value[0])
    ->receivedAck();

  Serial.print(bSuccess ? "Ok.\n" : "Error!\n");
    
  // Sleep
  swap.goToSleep();
}
#endif

