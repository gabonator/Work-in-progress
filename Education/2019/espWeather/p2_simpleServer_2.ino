#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

char* ssid = "******";
char* password = "******";
 
ESP8266WebServer server(80);

char* html = R""(
<HTML>
  <HEAD>
      <TITLE>My first web page</TITLE>
  </HEAD>
<BODY>
  <CENTER>
      <B>Hello World.... </B>
  </CENTER> 
</BODY>
</HTML>
)"";
  
void handleRoot() 
{
 server.send(200, "text/html", html);
}

void setup(void)
{
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
 
  Serial.print("\n");
  Serial.print("Connected to ");
  Serial.print(ssid);
  Serial.print("\n");
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
 
  server.on("/", handleRoot);
  server.begin();
}

void loop(void)
{
  server.handleClient();
}