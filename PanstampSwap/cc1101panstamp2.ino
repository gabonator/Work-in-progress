#define CC1101_GDO 2

#include "cc1101.h"
#include "panstamp.h"
//#define cc1101 radio


//#include "regtable.h"
#include "swap.h"

//#define RXER
//#define TXER   /// slave com3
#define RXER2    /// master com60



#ifdef RXER2
const unsigned char addr = 0xB5;
boolean packetAvailable = false;

void onPacket(SWPACKET *swPacket)
{
    REGISTER *reg;
    
    if ( swPacket->addrType == SWAPADDR_SIMPLE )
      Serial.print("SIMPLE packet");
    else 
    if ( swPacket->addrType == SWAPADDR_EXTENDED )
      Serial.print("EXTENDED packet");
    else 
      Serial.print("UNKNOWN packet");
      
    Serial.print(", function=");
    Serial.print(swPacket->function);
    Serial.print(", destAddr=");
    Serial.print(swPacket->destAddr);
    Serial.print(", regAddr=");
    Serial.print(swPacket->regAddr);
    Serial.print(", regId=");
    Serial.print(swPacket->regId);
//    Serial.print(", SWDATA:type=");
    //Serial.print(swPacket.value.type);
    //Serial.print(", payload.len=");
    //Serial.print(swPacket.value.length);
    Serial.print(", payload=");
    for (unsigned char i=0; i<swPacket->value.length; i++)
    {
      Serial.print(swPacket->value.data[i], HEX);
      Serial.print(' ');
    }
     Serial.print("\n");
}

void setup()
{
  Serial.begin(9600); 
  Serial.print("booting RXer2...\n");
  // Init SWAP stack
  panstamp.init(0,0);
  Serial.print("post panstamp init\n");
  swap.init();
  swap.attachInterrupt(STATUS, onPacket);

  Serial.print("master address=");
  Serial.print(panstamp.radio.devAddress, HEX);  
  Serial.print("\n");

}

void loop()
{
}
#endif

#ifdef RXER
const unsigned char addr = 0xB5;
boolean packetAvailable = false;

void onPacket(CCPACKET *packet)
{
  if ( 0 ) 
  {
    Serial.print("RX: ");
    for(int j=0; j<packet->length; j++)
    {
      Serial.print(packet->data[j],HEX);
      Serial.print(" ");
    }
  
    Serial.print("crc ");
    Serial.print(packet->crc_ok);
    Serial.print("\n");   
  } else
  {
    Serial.print(packet->rssi);
    Serial.print("/");
    Serial.print(packet->lqi);
    Serial.print(" ");

    if (packet->length <= SWAP_DATA_HEAD_LEN)
    {
      Serial.print("Packet too small\n");
      return;
    }
  
    SWPACKET swPacket = SWPACKET(packet);
    REGISTER *reg;
    
    if ( swPacket.addrType == SWAPADDR_SIMPLE )
      Serial.print("SIMPLE packet");
    else 
    if ( swPacket.addrType == SWAPADDR_EXTENDED )
      Serial.print("EXTENDED packet");
    else 
      Serial.print("UNKNOWN packet");
      
    Serial.print(", function=");
    Serial.print(swPacket.function);
    Serial.print(", destAddr=");
    Serial.print(swPacket.destAddr);
    Serial.print(", regAddr=");
    Serial.print(swPacket.regAddr);
    Serial.print(", regId=");
    Serial.print(swPacket.regId);
//    Serial.print(", SWDATA:type=");
    //Serial.print(swPacket.value.type);
    //Serial.print(", payload.len=");
    //Serial.print(swPacket.value.length);
    Serial.print(", payload=");
    for (unsigned char i=0; i<swPacket.value.length; i++)
    {
      Serial.print(swPacket.value.data[i], HEX);
      Serial.print(' ');
    }
     Serial.print("\n");
  }
}

void setup()
{
  int i;
  Serial.begin(9600); 
  Serial.print("booting RXer...\n");
  panstamp.init(0,0);
  panstamp.radio.devAddress = addr; // nemalo by byt potrebne
  panstamp.radio.setCCregs();

  Serial.print("address=");
  Serial.print(panstamp.radio.devAddress, HEX);  
  Serial.print("\n");

  panstamp.attachInterrupt(onPacket);

  Serial.print("setup end\n");
}

void loop()
{
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
