void setup() 
{
  pinMode(12, OUTPUT);
}

void loop() 
{  
  digitalWrite(12, HIGH);
  delay(1000); // 1000ms = 1s
  digitalWrite(12, LOW);
  delay(1000);
}