void setup()
{
  pinMode(12, OUTPUT);
}

/*
 *  C dur = C E G
 *  
 *  C6 = 1046 Hz
 *  E6 = 1318 Hz
 *  G6 = 1567 Hz
 */

void loop() 
{  
  tone(12, 1046);
  delay(200);
  tone(12, 1318);
  delay(200);
  tone(12, 1567);
  delay(200);
  noTone(12);
  delay(5000);
}