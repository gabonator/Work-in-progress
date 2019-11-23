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
  Serial.print("\n");

  delay(100);
}