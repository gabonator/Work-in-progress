void setup() 
{
  Serial.begin(9600);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
}

void loop() 
{
  int hodnota = analogRead(A3);
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
