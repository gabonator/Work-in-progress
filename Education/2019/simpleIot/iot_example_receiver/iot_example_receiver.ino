#include "ESP8266WiFi.h"

const char* ssid = "fbox";
const char* password = "********";

void setup() 
{  
  Serial.begin(115200);
  
  Serial.print("\n");
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("\n");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\n");
  Serial.print("WiFi connected\n");

  pinMode(D5, OUTPUT);
  digitalWrite(D5, 0);
  tone(D7, 2000);
  delay(100);
  noTone(D7);
}

void loop() 
{
  // https://dweet.io/follow/creativepoint_ba1
  // https://dweet.io/dweet/for/creativepoint_ba1?counter=10123
  // https://dweet.io/get/latest/dweet/for/creativepoint_ba1

  Serial.print("Connecting...\n");
  
  WiFiClient client;
  if (!client.connect("dweet.io", 80)) 
  {
    Serial.println("connection failed");
    return;
  }

  client.print("GET /get/latest/dweet/for/creativepoint_ba1 HTTP/1.1\r\n");
  client.print("Host: dweet.io\r\n");
  client.print("Connection: close\r\n");
  client.print("\r\n");
  
  delay(1000);

  for (int i=0; i<10; i++)
  {
    String line = client.readStringUntil('\r');  
    client.readStringUntil('\n');  
    Serial.print("Header: '");
    Serial.print(line);
    Serial.print("'\n");
    if (line.length() == 0)
      break;
  }
  String line = client.readStringUntil('}');  
  Serial.print("Response: '");
  Serial.print(line);
  Serial.print("'\n");

  // {"this":"succeeded","by":"getting","the":"dweets",
  // "with":[{"thing":"gabonator_1","created":"2019-05-26T09:41:57.694Z",
  // "content":{"counter":430,"humidity":62.7,"temperature":19.8}}]}

  float humidity = 0;
  int pos = line.indexOf("humidity");
  if (pos > 0)
  {
    int begin = pos + 8 + 1 + 1;
    int end = line.indexOf(',', begin);
    if (end > 0)
    {
      String strHumidity = line.substring(begin, end);
      humidity = strHumidity.toFloat();

      Serial.print("token='");
      Serial.print(strHumidity);
      Serial.print("' humidity=");
      Serial.print(humidity);
      Serial.print("\n");
    }    
  }

  if (humidity > 90)
    tone(D7, 1000);
  else
    noTone(D7);

  // Repeat every 5 seconds
  delay(3000); 
}

