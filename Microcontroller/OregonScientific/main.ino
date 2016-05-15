#include "oregon.h"

void InitOregon()
{
  while (!Receiver.Init())
  {
    Serial.print("Cannot initialize receiver!\n");
    delay(1000);
  }
}

void DoOregon()
{
  if ( Oregon.WaitHeader() )
  {
    if ( Oregon.GetHeader() )
    {
      byte pBuffer[COregon::PacketLength] = {0};
      byte received = Oregon.ReceivePacket(pBuffer);
      if ( received )
      {
        const char hex[] = "0123456789abcdef";
        Serial.print("Received buffer: ");
        for( int i=0; i < received; i++)
        {     
          Serial.print(hex[pBuffer[i] >> 4]);
          Serial.print(hex[pBuffer[i] & 15]);
        }
        Serial.print("\n");
      } else
        Serial.print("Receive error\n");
    }
  }  
}
