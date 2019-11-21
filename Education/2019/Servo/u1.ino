void setup() 
{
  Serial.begin(9600);
  Serial.print("2/2=");
  Serial.println(2/2);

  Serial.print("3/2=");
  Serial.println(3/2);
  
  Serial.print("4/2=");
  Serial.println(4/2);
  
  Serial.print("100*100=");
  Serial.println(100*100);

  Serial.print("300*300=");
  Serial.println(300*300);

  Serial.print("1000*1000=");
  Serial.println(1000*1000);
  
  Serial.print("500/1000*5=");
  Serial.println(500/1000*5);

  Serial.print("500*5/1000=");
  Serial.println(500*5/1000);

  pinMode(A0, OUTPUT);
  digitalWrite(A0, LOW);
  
  pinMode(A4, OUTPUT);
  digitalWrite(A4, HIGH);
}

void loop() 
{
  int hodnota = analogRead(A2);
  Serial.print("Namerali sme = ");
  Serial.print(hodnota);
  Serial.print(" napatie = ");
  
  //float napatie = (float)hodnota / 1023 * 5;
  //float napatie = hodnota / 1023.0f * 5.0f;
  float napatie = hodnota * 5.0f / 1023.0f;

  Serial.print(napatie);
  Serial.print(" V");
  Serial.print("\n");

  delay(100);
}
