/*
byte GetAdc8(void)
{
  TRISIO0 = 1;
  ANSEL = 0b00100001;
  // ADCON0
  ADFM = 0; // 0-left justified, 1-right
  CHS1 = 0; // CHS 00-AN0, GPIO0
  CHS2 = 0;
  ADON = 1;

  // Wait for ADC startup
  DelayUs(20);
  GODONE = 1;
  while (GODONE);
  ADON = 0;
    
  return ADRESH;
}

unsigned int GetAdc16(void)
{
  TRISIO1 = 1;
  ANSEL = 0b00100001;
  // ADCON0
  ADFM = 1; // 0-left justified, 1-right
//  CHS1 = 0; CHS2 = 0; // CHS 00-AN0, GPIO0
  CHS1 = 0; CHS0 = 1; // CHS 01-AN1, GPIO1
  
  ADON = 1;

  // Wait for ADC startup
  DelayUs(20);
  GODONE = 1;
  while (GODONE);
  ADON = 0;
    
  return (((unsigned int)ADRESH) << 8) | ADRESL;
}
*/

void ADC_Init(void)
{
  // AN0 - GPIO0 (7)
  // AN1 - GPIO1 (6)
  // AN2 - GPIO2 (2)
  // AN3 - GPIO4 (3)
 
  TRISIO1 = 1;
  ANSEL = 0b00101000;
  // . adcs2 adcs1 adcs0 - ans3 ans2 ans1 ans0
  // ADCS = 010, ANS = 1000

  ADFM = 1; // 0-left justified, 1-right
//  CHS1 = 0; CHS2 = 0; // CHS 00-AN0, GPIO0
//  CHS1 = 0; CHS0 = 1; // CHS 01-AN1, GPIO1
  CHS1 = 1; CHS0 = 1; // CHS 11-AN2, GPIO4
  
  ADON = 1;
}


unsigned int ADC_Get16(void)
{
  // 4us
  GODONE = 1;
  while (GODONE);

  return (((unsigned int)ADRESH) << 8) | ADRESL;
}