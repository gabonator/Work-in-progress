void setup() 
{
  pinMode(12, OUTPUT);
}

/*
 *  A4
 *  f = 440Hz
 *  T = ? s
 *  T = ? ms
 *  T = ? us
 *  Ton = Toff = ? us
 */

void loop() 
{  
  digitalWrite(12, HIGH);
  delayMicroseconds(?);
  digitalWrite(12, LOW);
  delayMicroseconds(?);
}