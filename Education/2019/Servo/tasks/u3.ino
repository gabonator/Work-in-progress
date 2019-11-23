void setup() 
{
  Serial.begin(9600);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);
}

int povodna = 0;

void loop() 
{
  int hodnota = analogRead(A3);
  int vysledok = hodnota*11/1024;

  if (vysledok != povodna)
  {
    Serial.print(vysledok);
    Serial.print("\n");    
    povodna = vysledok;
  }

  delay(100);
}
