void setup() 
{
  pinMode(12, OUTPUT);
}

/*
 *  A4
 *  f = 444Hz
 *  T = 1/444 = 0.002252252252252 s
 *  T = 2.252252252252252 ms
 *  T = 2252.252252252252252 us
 *  Ton = Toff = T/2 = 1126
 */

void loop() 
{  
  digitalWrite(12, HIGH);
  delayMicroseconds(1126);
  digitalWrite(12, LOW);
  delayMicroseconds(1126);
}