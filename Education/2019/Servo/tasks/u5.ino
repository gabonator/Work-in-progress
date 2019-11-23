void setup() 
{
  Serial.begin(9600);

  pinMode(A1, OUTPUT);
  digitalWrite(A1, LOW);
  pinMode(A3, INPUT);
  pinMode(A5, OUTPUT);
  digitalWrite(A5, HIGH);

  pinMode(A0, OUTPUT);
}

void loop() 
{
  int hodnota = analogRead(A3);
  
  digitalWrite(A0, HIGH);
  delayMicroseconds(1000 + hodnota);
  digitalWrite(A0, LOW);
  delay(20);
}
