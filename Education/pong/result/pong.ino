void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("adc=");
  Serial.print( analogRead(A0) ); // 0..1023
  Serial.print(";\n");
}