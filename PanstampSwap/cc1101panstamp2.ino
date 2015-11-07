#define CC1101_GDO 2

#include "cc1101.h"
#include "panstamp.h"
#include "logger.h"
#include "swap.h"

#define MODEM

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
  // send register   
  // swap.getRegister(regTxInterval.id)->updateData()->sendSwapStatus();
  // send register ack 
  // bool bSuccess = swap.getRegister(regSensor.id)->updateData()->sendSwapStatusAck()->receivedAck();

  // update register data
  // swap.getRegister(regTxInterval.id)->updateData()

  // get register data
  // swap.getRegister(regTxInterval.id)->value.length ->value.data

  // inquiry

  // transmit

  // TX max 18 chars
  // TX:11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11
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

    Serial.print("TX: ");
    LOGGER::dumpPacket(packet);

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

    Serial.print("EM: ");
    LOGGER::dumpPacket(packet);

    SWAP::onPacketReceived(&packet);
  }
}

void setup()
{
  Serial.begin(9600); 
  Serial.print("INFO: Booting modem\n");

  panstamp.init(0,0);
  panstamp.radio.setCCregs();
  swap.init();
  panstamp.radio.disableAddressCheck();
  swap.enterSystemState(SYSTATE_RXON);
  procLogger.setEnabled(true);
  
  Serial.print("INFO: Ready\n");
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

extern REGISTER regProductCode;
extern REGISTER regTxInterval;
extern REGISTER regVoltSupply;
extern REGISTER regSensor;

void setup()
{
  int i;
  Serial.begin(9600); 
  Serial.print("booting DHT22 slave TXer...\n");
  // Init SWAP stack
  panstamp.init(0,0);
  Serial.print("post panstamp init\n");
  swap.init();
  Serial.print("post swap init, address=");
  Serial.print(panstamp.radio.devAddress, HEX);  
  Serial.print("\n");
  
  pinMode(LED, OUTPUT);

  // Transmit product code
  //regProductCode.getData()->sendSwapStatus();
  swap.getRegister(regProductCode.id)->updateData()->sendSwapStatus();

  // Enter SYNC state
  swap.enterSystemState(SYSTATE_SYNC);

  Serial.print("blink begin\n");

  // During 3 seconds, listen the network for possible commands whilst the LED blinks
  for(i=0 ; i<6 ; i++)
  {
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(400);
  }
  Serial.print("blink end\n");

  // Transmit periodic Tx interval
  swap.getRegister(regTxInterval.id)->updateData()->sendSwapStatus();
  // Transmit power voltage
  swap.getRegister(regVoltSupply.id)->updateData()->sendSwapStatus();
   // Switch to Rx OFF state
  swap.enterSystemState(SYSTATE_RXOFF);
  Serial.print("setup end\n");
}

/**
 * loop
 *
 * Arduino main loop
 */
void loop()
{
  Serial.print("main loop\n");
  
  // Transmit sensor data
  bool bSuccess = swap.getRegister(regSensor.id)
    ->updateData()
    ->sendSwapStatusAck()
    ->receivedAck();

  Serial.print(bSuccess ? "Send Ok!\n" : "Send error!\n");
  
  // Sleep
  swap.goToSleep();
}
#endif

