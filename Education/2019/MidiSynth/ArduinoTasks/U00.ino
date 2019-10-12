void setup() 
{
  pinMode(12, OUTPUT);
}

void loop() 
{  
  digitalWrite(12, HIGH);
  delay(1); 
  digitalWrite(12, LOW);
  delay(1);

  // 1+1ms = 0.002s
  // 1/0.002s = 500 Hz
}