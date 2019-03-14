#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHTesp.h>

char* ssid = "*******";
char* password = "*******";
 
ESP8266WebServer server(80);
  
void handleRoot() 
{
  String html = R""(
<HTML>
  <HEAD>
      <TITLE>My first web page</TITLE>
  </HEAD>
<BODY>
  <CENTER>
      <a href="/teplota">Klikni sem ked chces vediet teplotu</a>
  </CENTER> 
</BODY>
</HTML>
)"";

  server.send(200, "text/html", html);
}

void handleMeranie() 
{
  DHTesp dht;
  dht.setup(D4, DHTesp::DHT22);
  
  String html = "meranie(" + String(dht.getTemperature()) + ", ";
  html = html + String(dht.getHumidity()) + ");";
  server.send(200, "application/javascript", html);
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
  server.on("/meranie", handleMeranie);
  server.begin();
}

void loop(void)
{
  server.handleClient();
}