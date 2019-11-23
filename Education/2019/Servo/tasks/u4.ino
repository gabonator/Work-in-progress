void setup() 
{
  Serial.begin(9600);
  pinMode(A0, OUTPUT);
}

void loop() 
{
  digitalWrite(A0, HIGH);
  delayMicroseconds(1500);
  digitalWrite(A0, LOW);
  delay(20);
}
