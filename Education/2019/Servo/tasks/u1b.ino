void setup() 
{
  Serial.begin(9600);
  Serial.print("2/2=");
  Serial.println(2/2);

  Serial.print("3/2=");
  Serial.println((float)3/2);
  
  Serial.print("4/2=");
  Serial.println(4/2);
  
  Serial.print("100*100=");
  Serial.println(100*100);

  Serial.print("300*300=");
  Serial.println(300*300);

  Serial.print("(long)300*300=");
  Serial.println((long)300*300);

  Serial.print("300L*300=");
  Serial.println(300L*300);

  Serial.print("1000*1000=");
  Serial.println(1000*1000);

  Serial.print("(long)1000*1000=");
  Serial.println((long)1000*1000);
  
  Serial.print("1000L*1000=");
  Serial.println(1000L*1000);

  Serial.print("500/1000*5=");
  Serial.println((float)500/1000*5);

  Serial.print("500.0f/1000*5=");
  Serial.println(500.0f/1000*5);

  Serial.print("(float)500*5/1000=");
  Serial.println((float)500*5/1000);

  Serial.print("500.0f*5/1000=");
  Serial.println(500.0f*5/1000);
}

void loop()
{
}
