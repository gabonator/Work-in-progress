void setup() 
{
  Serial.begin(9600);

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
  Serial.print("\n");

  delay(100);
}