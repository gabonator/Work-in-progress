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
  Serial.print(" vysledok = ");

  // mapujeme interval 0..1024 na interval 0..11
  // vysledok analogRead je hodnota 0..1023, takze vysledok
  // 11 nikdy nedostaneme
  int vysledok = hodnota*11/1024;

  Serial.print(vysledok);
  Serial.print("\n");

  delay(100);
}
