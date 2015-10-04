#include <arduino.h>

// Itead studio 2.4 TFT Touch shield for arduino (Arduino Uno)
// http://wiki.iteadstudio.com/2.4_TFT_LCD_Touch_shield
// ftp://imall.iteadstudio.com/IM120417012_Arduino_2.4eTFT_shield/DS_S6D1121.pdf

class CCalibration
{
  // Carlos E. Vidales
  // http://www.embedded.com/design/system-integration/4023968/How-To-Calibrate-Touch-Screens
  // input range 0..1024
  
public:
  typedef long INT32;
  
  struct Point 
  {
    Point() {}
    Point(INT32 _x, INT32 _y) : x(_x), y(_y) {}
    INT32 x, y;
  };
  
  struct Matrix
  {
    INT32 An, Bn, Cn, Dn, En, Fn, Divider;
  };

  static bool setCalibrationMatrix( Point * displayPtr, Point * screenPtr, Matrix * matrixPtr)
  {
      matrixPtr->Divider = ((screenPtr[0].x - screenPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                           ((screenPtr[1].x - screenPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;
  
      if( matrixPtr->Divider == 0 )
        return false;
        
      matrixPtr->An = ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].y - screenPtr[2].y)) - 
                      ((displayPtr[1].x - displayPtr[2].x) * (screenPtr[0].y - screenPtr[2].y)) ;

      matrixPtr->Bn = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].x - displayPtr[2].x)) - 
                      ((displayPtr[0].x - displayPtr[2].x) * (screenPtr[1].x - screenPtr[2].x)) ;

      matrixPtr->Cn = (screenPtr[2].x * displayPtr[1].x - screenPtr[1].x * displayPtr[2].x) * screenPtr[0].y +
                      (screenPtr[0].x * displayPtr[2].x - screenPtr[2].x * displayPtr[0].x) * screenPtr[1].y +
                      (screenPtr[1].x * displayPtr[0].x - screenPtr[0].x * displayPtr[1].x) * screenPtr[2].y ;

      matrixPtr->Dn = ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].y - screenPtr[2].y)) - 
                      ((displayPtr[1].y - displayPtr[2].y) * (screenPtr[0].y - screenPtr[2].y)) ;
  
      matrixPtr->En = ((screenPtr[0].x - screenPtr[2].x) * (displayPtr[1].y - displayPtr[2].y)) - 
                      ((displayPtr[0].y - displayPtr[2].y) * (screenPtr[1].x - screenPtr[2].x)) ;

      matrixPtr->Fn = (screenPtr[2].x * displayPtr[1].y - screenPtr[1].x * displayPtr[2].y) * screenPtr[0].y +
                      (screenPtr[0].x * displayPtr[2].y - screenPtr[2].x * displayPtr[0].y) * screenPtr[1].y +
                      (screenPtr[1].x * displayPtr[0].y - screenPtr[0].x * displayPtr[1].y) * screenPtr[2].y ;
                      
      return true;     
  }
  
  static bool getDisplayPoint( Point * displayPtr, Point * screenPtr, Matrix * matrixPtr )
  {
    if( matrixPtr->Divider == 0 )
      return false;
    
    displayPtr->x = ( (matrixPtr->An * screenPtr->x) + 
                      (matrixPtr->Bn * screenPtr->y) + 
                       matrixPtr->Cn 
                    ) / matrixPtr->Divider ;
    
    displayPtr->y = ( (matrixPtr->Dn * screenPtr->x) + 
                      (matrixPtr->En * screenPtr->y) + 
                       matrixPtr->Fn 
                    ) / matrixPtr->Divider ;
    return true;
  }
};

class CTouch
{
  const int pinCLK = 15;
  const int pinCS = 20;
  const int pinDIN = 14;
  const int pinDOUT = 8;
  const int pinIRQ = 9;
  const int PRECISION = 4;
  
private:
  unsigned long m_ulRawX;
  unsigned long m_ulRawY;

  CCalibration::Matrix m_mCalibration;

public:
  CTouch()
  {
    // portrait
    m_mCalibration.An = 127800; m_mCalibration.Bn = 450; m_mCalibration.Cn = -125675850;
    m_mCalibration.Dn = -3640; m_mCalibration.En = 178100; m_mCalibration.Fn = -173510310;
    m_mCalibration.Divider = -486385;  
 
    // landscape
    m_mCalibration.Dn = 127800; m_mCalibration.En = 450; m_mCalibration.Fn = -125675850;
    m_mCalibration.An = -3640; m_mCalibration.Bn = 178100; m_mCalibration.Cn = -173510310;
    m_mCalibration.Divider = -486385;  

    // upside down
    m_mCalibration.Dn *= -1;
    m_mCalibration.En *= -1;
    m_mCalibration.Fn *= -1;
    m_mCalibration.Fn += 240 * m_mCalibration.Divider;
  }
  
  void Init()
  {
    pinMode(pinCLK,  OUTPUT);
    pinMode(pinCS,   OUTPUT);
    pinMode(pinDIN,  OUTPUT);
    pinMode(pinDOUT, INPUT);
    pinMode(pinIRQ,  INPUT);

    digitalWrite(pinCS,  HIGH);
    digitalWrite(pinCLK, HIGH);
    digitalWrite(pinDIN, HIGH);
    digitalWrite(pinCLK, HIGH);
  }

  void Flush()
  {
    while (Available())
    {
      _Read();      
    }
  }
  
  bool Available()
  {
    return !digitalRead(pinIRQ);
  }

  void GetRaw(unsigned long* x, unsigned long* y)
  {
    _Read();
    *x = m_ulRawX;
    *y = m_ulRawY;
  }

  bool Get(int& x, int& y)
  {
    if ( !_Read() )
      return false;
      
    CCalibration::Point ptTouch(m_ulRawX, m_ulRawY);
    CCalibration::Point ptScreen;
    CCalibration::getDisplayPoint(&ptScreen, &ptTouch, &m_mCalibration);
    x = ptScreen.x;
    y = ptScreen.y;

    return true;
  }
  
private:
  void _WriteData(unsigned char data)
  {
    digitalWrite(pinCLK, LOW);
  
    for(unsigned char i = 0; i < 8; i++)
    {
      digitalWrite(pinDIN, (data & 0x80) ? HIGH : LOW);
      data <<= 1; 
      digitalWrite(pinCLK, LOW);          
      i++;  // nop
      digitalWrite(pinCLK, HIGH);
      i--;  // nop
    }
  }

  unsigned int _ReadData()
  {
    unsigned char nop;
    unsigned int data = 0;
    
    for (unsigned char i = 0; i < 12; i++)
    {
      digitalWrite(pinCLK, HIGH);               
      i++;  // nop
      digitalWrite(pinCLK, LOW);
      i--;  // nop

      data <<= 1;
      if (digitalRead(pinDOUT))
        data++;
    }
    return data;
  }
    
  bool _Read()
  {
    m_ulRawX = 0;
    m_ulRawY = 0;
  
    digitalWrite(pinCS, LOW);                    
  
    for (unsigned int i=0; i<(1<<PRECISION); i++)
    {
      _WriteData(0x90);        
      digitalWrite(pinCLK,HIGH);
      digitalWrite(pinCLK,LOW); 
      m_ulRawY += _ReadData();
  
      _WriteData(0xD0);      
      digitalWrite(pinCLK,HIGH);
      digitalWrite(pinCLK,LOW);
      m_ulRawX += _ReadData();

      if (!Available())
        return false;
        
    }
    m_ulRawX >>= PRECISION+2;
    m_ulRawY >>= PRECISION+2;
    
    digitalWrite(pinCS, HIGH);
    return true;
  }
};

class CLcd
{
  const int pinRS = 19;
  const int pinWR = 18;
  const int pinCS = 17;
  const int pinRST = 16;
  
public:
  static const int Width = 320;
  static const int Height = 240;
  
public:
  void Init()
  {
    pinMode(pinRS, OUTPUT);
    pinMode(pinWR, OUTPUT);
    pinMode(pinCS, OUTPUT);
    pinMode(pinRST, OUTPUT);
    DDRD = 0xFF;  
    digitalWrite(pinRST, HIGH);
    delay(3); 
    digitalWrite(pinRST, LOW);
    delay(3);  
    digitalWrite(pinRST, HIGH);
    digitalWrite(pinCS, HIGH);
    digitalWrite(pinWR, HIGH);
    delay(30);

    // http://asf.atmel.com/docs/3.7.2/sam.components.display.ili9325.unit_tests.sam3s_ek/html/ili9325_8c_source.html#l00696
    unsigned short configuration[] = {
      0x0011,0x2004,  0x0013,0xCC00,  0x0015,0x2600,  0x0014,0x252A,
      0x0012,0x0033,  0x0013,0xCC04,  0x0013,0xCC06,  0x0013,0xCC4F,
      0x0013,0x674F,  0x0011,0x2003,  0x0030,0x2609,  0x0031,0x242C,
      0x0032,0x1F23,  0x0033,0x2425,  0x0034,0x2226,  0x0035,0x2523,
      0x0036,0x1C1A,  0x0037,0x131D,  0x0038,0x0B11,  0x0039,0x1210,
      0x003A,0x1315,  0x003B,0x3619,  0x003C,0x0D00,  0x003D,0x000D,
      0x0016,0x0007,  0x0002,0x0013,  0x0003,0x0003,  0x0001,0x0127,
      0x0008,0x0303,  0x000A,0x000B,  0x000B,0x0003,  0x000C,0x0000,
      0x0041,0x0000,  0x0050,0x0000,  0x0060,0x0005,  0x0070,0x000B,
      0x0071,0x0000,  0x0078,0x0000,  0x007A,0x0000,  0x0079,0x0007,
      0x0007,0x0051,  0x0007,0x0053,  0x0079,0x0000,
      // landscape
      0x0003,0x000a,
      // scroll
      0x0007,0x1051,  0x0007,0x1053,
      0x0042,0x013f,  0x0043,0x0000,
      0x0041,0x0000
    };

    for (int i = 0; i < sizeof(configuration)/sizeof(configuration[0]); i += 2)
    {
      _WriteCmd(configuration[i]);
      _WriteData(configuration[i+1]);
    }

    // Write RAM
    _WriteCmd(0x0022);  
  }

  void Attach()
  {
    DDRD = 0xFF;  
  }

  void SetRegion(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1)
  {
    x1--;
    y1 = Height-y1;
    y0 = Height-1-y0;
    
    _Write(0x0046, (y1 << 8) | y1);
    _Write(0x0047, x1);
    _Write(0x0048, x0);
    
    _Write(0x0020, y0);
    _Write(0x0021, x0);
    _WriteCmd(0x0022);
  }

  void Bar(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int c)
  {
    SetRegion(x0, y0, x1, y1);
    unsigned int nPixels = (x1-x0)*(y1-y0);
    while (nPixels--)
      PutPixel(c);
  }
  
  void PutPixel(unsigned int x, unsigned int y, unsigned int c)
  {
    _Write(0x0020, Height-1-y);
    _Write(0x0021, x);
    _WriteCmd(0x0022);
    _WriteData(c);
  }
  
  void PutPixel(unsigned int c)
  {
    _WriteData(c);
  }

  void GetPixel(unsigned int c)
  {
    _WriteData(c);
  }

  void Clear(unsigned int c)
  {
    SetRegion(0, 0, Width, Height);
    for (int y=0; y<Height; y++)
      for (int x=0; x<Width; x++)
        PutPixel(c);    
  }
    
  unsigned int GetColor(unsigned long lRRGGBB)
  {
    unsigned char b = (unsigned char)lRRGGBB;
    lRRGGBB >>= 8;
    unsigned char g = (unsigned char)lRRGGBB;
    lRRGGBB >>= 8;
    unsigned char r = (unsigned char)lRRGGBB;
    r >>= 3;
    g >>= 2;
    b >>= 3;
    
    unsigned int aux = (unsigned int)b | ((unsigned int)g << 5) | ((unsigned int)r << 11);
    return aux;
  }
  
  unsigned long Interpolate(unsigned long c0, unsigned long c1, short level)
  {
    if ( level <= 0 )
      return c0;
    if ( level >= 255 )
      return c1;
      
    unsigned int b0 = c0 & 0xff;
    c0 >>= 8;
    unsigned int g0 = c0 & 0xff;
    c0 >>= 8;
    unsigned int r0 = c0 & 0xff;
    
    unsigned int b1 = c1 & 0xff;
    c1 >>= 8;
    unsigned int g1 = c1 & 0xff;
    c1 >>= 8;
    unsigned int r1 = c1 & 0xff;

    r0 += ((r1 - r0) * level) >> 8;
    g0 += ((g1 - g0) * level) >> 8;
    b0 += ((b1 - b0) * level) >> 8;

    return (unsigned long)b0 | ((unsigned long)g0 << 8) | ((unsigned long)r0 << 16);
  }

private:
public:
  void _WriteCmdSlow(unsigned int c)
  {
    digitalWrite(pinRS, LOW);
    digitalWrite(pinCS, LOW);
    PORTD = c>>8; 
    digitalWrite(pinWR, LOW);
    digitalWrite(pinWR, HIGH);
    PORTD = c;
    digitalWrite(pinWR, LOW);
    digitalWrite(pinWR, HIGH);
    digitalWrite(pinCS, HIGH);
  }

  void _WriteDataSlow(unsigned int c)
  {
    digitalWrite(pinRS, HIGH);
    digitalWrite(pinCS, LOW);
    PORTD = c>>8;
    digitalWrite(pinWR, LOW);
    digitalWrite(pinWR, HIGH);
    PORTD = c;
    digitalWrite(pinWR, LOW);
    digitalWrite(pinWR, HIGH);
    digitalWrite(pinCS, HIGH);
  }

  void _WriteData(unsigned int c)
  {
    PORTC |= 1<<5; //digitalWrite(pinRS, HIGH);
    PORTC &= ~1<<3; //digitalWrite(pinCS, LOW);
    PORTD = c>>8;
    PORTC &= ~1<<4; //digitalWrite(pinWR, LOW);
    PORTC |= 1<<4; //digitalWrite(pinWR, HIGH);
    PORTD = c;
    PORTC &= ~1<<4; //digitalWrite(pinWR, LOW);
    PORTC |= 1<<4; //digitalWrite(pinWR, HIGH);
    PORTC |= 1<<3; //digitalWrite(pinCS, HIGH);
  }

  void _WriteCmd(unsigned int c)
  {
    digitalWrite(pinRS, LOW);
    //PORTC &= ~1<<5; //digitalWrite(pinRS, LOW);
    PORTC &= ~1<<3; //digitalWrite(pinCS, LOW);
    PORTD = c>>8;
    PORTC &= ~1<<4; //digitalWrite(pinWR, LOW);
    PORTC |= 1<<4; //digitalWrite(pinWR, HIGH);
    PORTD = c;
    PORTC &= ~1<<4; //digitalWrite(pinWR, LOW);
    PORTC |= 1<<4; //digitalWrite(pinWR, HIGH);
    PORTC |= 1<<3; //digitalWrite(pinCS, HIGH);
  }

  void _Write(unsigned int cmd, unsigned int data)
  {
    _WriteCmd(cmd);
    _WriteData(data);
  }
};

class CCalibrationProcess
{
public:
  CLcd m_Lcd;
  CTouch m_Touch;
  CCalibration::Matrix m_Matrix;

  void Init()
  {
    m_Lcd.Init();
    m_Touch.Init();
  }

  void Test()
  {
    m_Touch.Init();
    Serial.begin(9600);
    while (1)
    {
      if ( !m_Touch.Available() ) 
        continue;
        
      unsigned long lX, lY;
      m_Touch.GetRaw(&lX, &lY);
      Serial.print((" x0=")); Serial.print(lX);
      Serial.print((" y0=")); Serial.print(lY);
      Serial.print(("\n"));
      delay(100);
    }
  }
  
  void Do()
  {    
    CCalibration::Point arrScreen[3] = {{30, 30}, {m_Lcd.Width/2, m_Lcd.Height - 30}, {m_Lcd.Width-30, 30}};
    CCalibration::Point arrTouch[3];

    for ( int i = 0; i < 3; i++ )
    {
      DrawCrosshair(arrScreen[i].x, arrScreen[i].y, 15);
      while (m_Touch.Available())
        delay(100);
      while (!m_Touch.Available())
        delay(100);
      ClearCrosshair(arrScreen[i].x, arrScreen[i].y, 15);

      unsigned long lX, lY;
      m_Touch.GetRaw(&lX, &lY);
      arrTouch[i].x = lX;
      arrTouch[i].y = lY;
    }

    CCalibration::setCalibrationMatrix(arrScreen, arrTouch, &m_Matrix);

    Serial.begin(9600);
    delay(100);
    Serial.print(("Points:\n"));
    Serial.print(("x0=")); Serial.print(arrTouch[0].x);
    Serial.print(("y0=")); Serial.print(arrTouch[0].y);
    Serial.print(("\nx1=")); Serial.print(arrTouch[1].x);
    Serial.print(("y1=")); Serial.print(arrTouch[1].y);
    Serial.print(("\nx2=")); Serial.print(arrTouch[2].x);
    Serial.print(("y2=")); Serial.print(arrTouch[2].y);
    Serial.print(("\n\n"));

    Serial.print(("Calibration matrix:\n"));
    Serial.print(("A=")); Serial.print(m_Matrix.An);
    Serial.print((", B=")); Serial.print(m_Matrix.Bn);
    Serial.print((", C=")); Serial.print(m_Matrix.Cn);
    Serial.print(("\nD=")); Serial.print(m_Matrix.Dn);
    Serial.print((", E=")); Serial.print(m_Matrix.En);
    Serial.print((", F=")); Serial.print(m_Matrix.Fn);
    Serial.print(("\nDivider=")); Serial.print(m_Matrix.Divider);
    Serial.print(("\n\n"));
    Serial.end();

    delay(200);
    m_Lcd.Attach();
    m_Lcd.Init();
}

private:
  void DrawCrosshair(int x, int y, int l)
  {
    m_Lcd.Bar(x-l, y-1, x+l, y+1, 0xffff);
    m_Lcd.Bar(x-1, y-l, x+1, y+l, 0xffff);
  }
  
  void ClearCrosshair(int x, int y, int l)
  {
    m_Lcd.Bar(x-l, y-l, x+l, y+l, 0x0000);
  }
};

class CDraw
{
  CLcd m_lcd;

public:
  const int FontHeight2x = 24;
  const int FontHeight = 12;
  const int FontWidth2x = 16;
  const int FontWidth = 8;

public:
  int m_nWidth;
  unsigned long m_rgbBack;
  unsigned long m_rgbFront;
  unsigned short m_clrBack;
  unsigned short m_clrFront;

  CDraw()
  {
    m_nWidth = 3;
    SetBkgColor(0x000000);
    SetColor(0xffffff);
  }

  void SetBkgColor(unsigned long lRgb)
  {
    m_rgbBack = lRgb;
    m_clrBack = m_lcd.GetColor(lRgb);
  }
  
  void SetColor(unsigned long lRgb)
  {
    m_rgbFront = lRgb;
    m_clrFront = m_lcd.GetColor(lRgb);
  }

  void line(int x0, int y0, int x1, int y1)
  { 
   int dx = abs(x1-x0);
   int sx = x0 < x1 ? 1 : -1; 
   int dy = abs(y1-y0);
   int sy = y0 < y1 ? 1 : -1; 
   
   int err = dx-dy, e2, x2, y2;                          /* error value e_xy */
   int ed = (dx+dy == 0) ? 1 : sqrt((float)dx*dx+(float)dy*dy);

   unsigned short c = m_lcd.GetColor(m_rgbFront);
   
   for (int wd = (m_nWidth+1)/2; ; ) {                                   /* pixel loop */
      m_lcd.PutPixel(x0, y0, c);
      e2 = err; x2 = x0;
      if (2*e2 >= -dx) {                                           /* x step */
         for (e2 += dy, y2 = y0; e2 < ed*wd && (y1 != y2 || dx > dy); e2 += dx)
            m_lcd.PutPixel(x0, y2 += sy, c);
         if (x0 == x1) break;
         e2 = err; err -= dy; x0 += sx; 
      } 
      if (2*e2 <= dy) {                                            /* y step */
         for (e2 = dx-e2; e2 < ed*wd && (x1 != x2 || dx < dy); e2 += dy)
            m_lcd.PutPixel(x2 += sx, y0, c);
         if (y0 == y1) break;
         err += dx; y0 += sy; 
      }
   }
  }

  void DrawText(int x, int y, char* strText, bool bDouble = false)
  {
    while (*strText)
    {
      bDouble ? DrawDoubleChar(x, y, *strText++) : DrawChar(x, y, *strText++);
      x += bDouble ? 16 : 8;
    }
  }

  void DrawChar(int x, int y, char c)
  {
    const unsigned char* PROGMEM data = GetSymbol(c);
    if ( !c )
      return;

    m_lcd.SetRegion(x, y, x+FontWidth, y+FontHeight);
    for (unsigned char _y=0; _y<FontHeight; _y++)
    {
      unsigned char r = pgm_read_byte_near(data + _y);
      for (unsigned char _x=0; _x<FontWidth; _x++)
        m_lcd.PutPixel((r & (128>>_x)) ? m_clrFront : m_clrBack);
    }
  }

  void DrawDoubleChar(int x, int y, char c)
  {
    const unsigned char* PROGMEM data = GetSymbol(c);
    if ( !c )
      return;

    m_lcd.SetRegion(x, y, x+FontWidth*2, y+FontHeight*2);
    for (unsigned char _y=0; _y<FontHeight*2; _y++)
    {
      unsigned char r = pgm_read_byte_near(data + _y/2);
      for (unsigned char _x=0; _x<FontWidth*2; _x++)
        m_lcd.PutPixel((r & (128>>(_x/2))) ? m_clrFront : m_clrBack);
    }
  }
  
  const unsigned char* PROGMEM GetSymbol(char ch)
  {
    // UTFT library
    static const unsigned char SmallFont[1144] PROGMEM={         
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // <Space>
      0x00,0x00,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x20,0x00,0x00, // !
      0x00,0x28,0x50,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // "
      0x00,0x00,0x28,0x28,0xFC,0x28,0x50,0xFC,0x50,0x50,0x00,0x00, // #
      0x00,0x20,0x78,0xA8,0xA0,0x60,0x30,0x28,0xA8,0xF0,0x20,0x00, // $
      0x00,0x00,0x48,0xA8,0xB0,0x50,0x28,0x34,0x54,0x48,0x00,0x00, // %
      0x00,0x00,0x20,0x50,0x50,0x78,0xA8,0xA8,0x90,0x6C,0x00,0x00, // &
      0x00,0x40,0x40,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
      0x00,0x04,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x04,0x00, // (
      0x00,0x40,0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x40,0x00, // )
      0x00,0x00,0x00,0x20,0xA8,0x70,0x70,0xA8,0x20,0x00,0x00,0x00, // *
      0x00,0x00,0x20,0x20,0x20,0xF8,0x20,0x20,0x20,0x00,0x00,0x00, // +
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x80, // ,
      0x00,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00, // -
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00, // .
      0x00,0x08,0x10,0x10,0x10,0x20,0x20,0x40,0x40,0x40,0x80,0x00, // /
      0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // 0
      0x00,0x00,0x20,0x60,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // 1
      0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x40,0x80,0xF8,0x00,0x00, // 2
      0x00,0x00,0x70,0x88,0x08,0x30,0x08,0x08,0x88,0x70,0x00,0x00, // 3
      0x00,0x00,0x10,0x30,0x50,0x50,0x90,0x78,0x10,0x18,0x00,0x00, // 4
      0x00,0x00,0xF8,0x80,0x80,0xF0,0x08,0x08,0x88,0x70,0x00,0x00, // 5
      0x00,0x00,0x70,0x90,0x80,0xF0,0x88,0x88,0x88,0x70,0x00,0x00, // 6
      0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x20,0x20,0x20,0x00,0x00, // 7
      0x00,0x00,0x70,0x88,0x88,0x70,0x88,0x88,0x88,0x70,0x00,0x00, // 8
      0x00,0x00,0x70,0x88,0x88,0x88,0x78,0x08,0x48,0x70,0x00,0x00, // 9
      0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x20,0x00,0x00, // :
      0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x20,0x20,0x00, // ;
      0x00,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x00,0x00, // <
      0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0xF8,0x00,0x00,0x00,0x00, // =
      0x00,0x40,0x20,0x10,0x08,0x04,0x08,0x10,0x20,0x40,0x00,0x00, // >
      0x00,0x00,0x70,0x88,0x88,0x10,0x20,0x20,0x00,0x20,0x00,0x00, // ?
      0x00,0x00,0x70,0x88,0x98,0xA8,0xA8,0xB8,0x80,0x78,0x00,0x00, // @
      0x00,0x00,0x20,0x20,0x30,0x50,0x50,0x78,0x48,0xCC,0x00,0x00, // A
      0x00,0x00,0xF0,0x48,0x48,0x70,0x48,0x48,0x48,0xF0,0x00,0x00, // B
      0x00,0x00,0x78,0x88,0x80,0x80,0x80,0x80,0x88,0x70,0x00,0x00, // C
      0x00,0x00,0xF0,0x48,0x48,0x48,0x48,0x48,0x48,0xF0,0x00,0x00, // D
      0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x48,0xF8,0x00,0x00, // E
      0x00,0x00,0xF8,0x48,0x50,0x70,0x50,0x40,0x40,0xE0,0x00,0x00, // F
      0x00,0x00,0x38,0x48,0x80,0x80,0x9C,0x88,0x48,0x30,0x00,0x00, // G
      0x00,0x00,0xCC,0x48,0x48,0x78,0x48,0x48,0x48,0xCC,0x00,0x00, // H
      0x00,0x00,0xF8,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // I
      0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x90,0xE0,0x00, // J
      0x00,0x00,0xEC,0x48,0x50,0x60,0x50,0x50,0x48,0xEC,0x00,0x00, // K
      0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x44,0xFC,0x00,0x00, // L
      0x00,0x00,0xD8,0xD8,0xD8,0xD8,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // M
      0x00,0x00,0xDC,0x48,0x68,0x68,0x58,0x58,0x48,0xE8,0x00,0x00, // N
      0x00,0x00,0x70,0x88,0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00, // O
      0x00,0x00,0xF0,0x48,0x48,0x70,0x40,0x40,0x40,0xE0,0x00,0x00, // P
      0x00,0x00,0x70,0x88,0x88,0x88,0x88,0xE8,0x98,0x70,0x18,0x00, // Q
      0x00,0x00,0xF0,0x48,0x48,0x70,0x50,0x48,0x48,0xEC,0x00,0x00, // R
      0x00,0x00,0x78,0x88,0x80,0x60,0x10,0x08,0x88,0xF0,0x00,0x00, // S
      0x00,0x00,0xF8,0xA8,0x20,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // T
      0x00,0x00,0xCC,0x48,0x48,0x48,0x48,0x48,0x48,0x30,0x00,0x00, // U
      0x00,0x00,0xCC,0x48,0x48,0x50,0x50,0x30,0x20,0x20,0x00,0x00, // V
      0x00,0x00,0xA8,0xA8,0xA8,0x70,0x50,0x50,0x50,0x50,0x00,0x00, // W
      0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x50,0x50,0xD8,0x00,0x00, // X
      0x00,0x00,0xD8,0x50,0x50,0x20,0x20,0x20,0x20,0x70,0x00,0x00, // Y
      0x00,0x00,0xF8,0x90,0x10,0x20,0x20,0x40,0x48,0xF8,0x00,0x00, // Z
      0x00,0x38,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x38,0x00, // [
      0x00,0x40,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x00,0x00, // <Backslash>
      0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x70,0x00, // ]
      0x00,0x20,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ^
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC, // _
      0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // '
      0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x38,0x48,0x3C,0x00,0x00, // a
      0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0x70,0x00,0x00, // b
      0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x40,0x40,0x38,0x00,0x00, // c
      0x00,0x00,0x18,0x08,0x08,0x38,0x48,0x48,0x48,0x3C,0x00,0x00, // d
      0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x78,0x40,0x38,0x00,0x00, // e
      0x00,0x00,0x1C,0x20,0x20,0x78,0x20,0x20,0x20,0x78,0x00,0x00, // f
      0x00,0x00,0x00,0x00,0x00,0x3C,0x48,0x30,0x40,0x78,0x44,0x38, // g
      0x00,0x00,0xC0,0x40,0x40,0x70,0x48,0x48,0x48,0xEC,0x00,0x00, // h
      0x00,0x00,0x20,0x00,0x00,0x60,0x20,0x20,0x20,0x70,0x00,0x00, // i
      0x00,0x00,0x10,0x00,0x00,0x30,0x10,0x10,0x10,0x10,0x10,0xE0, // j
      0x00,0x00,0xC0,0x40,0x40,0x5C,0x50,0x70,0x48,0xEC,0x00,0x00, // k
      0x00,0x00,0xE0,0x20,0x20,0x20,0x20,0x20,0x20,0xF8,0x00,0x00, // l
      0x00,0x00,0x00,0x00,0x00,0xF0,0xA8,0xA8,0xA8,0xA8,0x00,0x00, // m
      0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0xEC,0x00,0x00, // n
      0x00,0x00,0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x30,0x00,0x00, // o
      0x00,0x00,0x00,0x00,0x00,0xF0,0x48,0x48,0x48,0x70,0x40,0xE0, // p
      0x00,0x00,0x00,0x00,0x00,0x38,0x48,0x48,0x48,0x38,0x08,0x1C, // q
      0x00,0x00,0x00,0x00,0x00,0xD8,0x60,0x40,0x40,0xE0,0x00,0x00, // r
      0x00,0x00,0x00,0x00,0x00,0x78,0x40,0x30,0x08,0x78,0x00,0x00, // s
      0x00,0x00,0x00,0x20,0x20,0x70,0x20,0x20,0x20,0x18,0x00,0x00, // t
      0x00,0x00,0x00,0x00,0x00,0xD8,0x48,0x48,0x48,0x3C,0x00,0x00, // u
      0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x00,0x00, // v
      0x00,0x00,0x00,0x00,0x00,0xA8,0xA8,0x70,0x50,0x50,0x00,0x00, // w
      0x00,0x00,0x00,0x00,0x00,0xD8,0x50,0x20,0x50,0xD8,0x00,0x00, // x
      0x00,0x00,0x00,0x00,0x00,0xEC,0x48,0x50,0x30,0x20,0x20,0xC0, // y
      0x00,0x00,0x00,0x00,0x00,0x78,0x10,0x20,0x20,0x78,0x00,0x00, // z
      0x00,0x18,0x10,0x10,0x10,0x20,0x10,0x10,0x10,0x10,0x18,0x00, // {
      0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, // |
      0x00,0x60,0x20,0x20,0x20,0x10,0x20,0x20,0x20,0x20,0x60,0x00, // }
      0x40,0xA4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ~
    };
    
    unsigned int nOfs = (ch-' ')*12;
    if ( nOfs >= sizeof(SmallFont) )
      return NULL;

    return SmallFont + nOfs;
  }  
  
};

CLcd lcd;
CTouch touch;
CDraw draw;

void chess()
{
  unsigned short clr1 = lcd.GetColor(0x0060b0);
  unsigned short clr2 = lcd.GetColor(0x808080);
  
  lcd.SetRegion(0, 0, lcd.Width, lcd.Height);
  for (int y=0; y<lcd.Height; y++)
    for (int x=0; x<lcd.Width; x++)
    {
      if ( ((x >> 4) + (y>>4))&1)
        lcd.PutPixel(clr1);
      else
        lcd.PutPixel(clr2);
    }  
}

void spheres()
{
  static int nOffset = 0;
  lcd.SetRegion(0, 0, lcd.Width, lcd.Height);
  for (int y=0; y<lcd.Height; y++)
    for (int x=0; x<lcd.Width; x++)
    {
      int nDistX = (x-lcd.Width/2);
      int nDistY = (y-lcd.Height/2);
      int nDist = nDistX*nDistX + nDistY*nDistY;
      nDist >>= 2;
      nDist += nOffset;
      lcd.PutPixel(nDist);
    }
  nOffset += 200;
}

static const unsigned long arrRainbowColors[] = 
   {0xff0000, 0xffff00, 0xffffff, 0x00ffff, 0x0000ff, 0x000000};

unsigned short multigrad(const unsigned long* arrColors, const int nColors, unsigned long lPhase)
{  
  unsigned int nColor = (lPhase >> 8) % nColors;
  unsigned int nMid = lPhase & 0xff;
  
  unsigned long lRGB = lcd.Interpolate(arrColors[nColor], arrColors[(nColor+1)%nColors], nMid);  
  return lcd.GetColor(lRGB);
}

unsigned short rainbow()
{
  return multigrad(arrRainbowColors, (sizeof(arrRainbowColors)/sizeof(arrRainbowColors[0])), millis() >> 2);
}

void worm()
{
  float omega = millis() * 2.0f * PI * 0.001f;
  const float fFreqX = 1.5f;
  const float fFreqY = 1.0f;
  const int nDimension = min(lcd.Width, lcd.Height) / 3;
  
  int nX = lcd.Width/2 + cos(omega * fFreqX) * nDimension;
  int nY = lcd.Height/2 + sin(omega * fFreqY) * nDimension;

  unsigned long nColor = millis();
  nColor &= 511;
  if (nColor >= 256)
    nColor = 256 - (nColor - 256);

  nColor = nColor & 0xff;
  nColor = nColor | (nColor<<8) | (nColor<<16);
  lcd.Bar(nX-5, nY-5, nX+5, nY+5, lcd.GetColor(nColor));
}

void gradient()
{
  lcd.SetRegion(0, 0, lcd.Width, lcd.Height);
  unsigned long lTopLeft = 0xff0000;
  unsigned long lTopRight = 0x00ff00;
  unsigned long lBottomLeft = 0x0000ff;
  unsigned long lBottomRight = 0xb0b0b0;

  for (int y=0; y<lcd.Height; y++)
    for (int x=0; x<lcd.Width; x++)
    {
      unsigned long nLeft = (unsigned long)x*256/lcd.Width;
      unsigned long nTop = (unsigned long)y*256/lcd.Height;
      
      unsigned long nInterpolateTop = lcd.Interpolate(lTopLeft, lTopRight, nLeft);
      unsigned long nInterpolateBottom = lcd.Interpolate(lBottomLeft, lBottomRight, nLeft);
      unsigned long nInterpolate = lcd.Interpolate(nInterpolateTop, nInterpolateBottom, nTop);

      lcd.PutPixel(lcd.GetColor(nInterpolate));
    }
}

void sierpinski()
{
  static const int arrX[3] = {20, lcd.Width/2, lcd.Width-20};
  static const int arrY[3] = {lcd.Height-20, 20, lcd.Height-20};
  
  static int x = arrX[0];
  static int y = arrY[0];

  int nRandom = rand() % 3;
  int nNewX = arrX[nRandom];
  int nNewY = arrY[nRandom];

  x = (x + nNewX) / 2;
  y = (y + nNewY) / 2;
  
  lcd.PutPixel(x, y, rainbow());
}

bool Paint()
{
  static int nLastX = -1, nLastY = -1;
  static int nNewX = -1, nNewY = -1;
  static long nPressed = 0;
  
  if ( touch.Available() )
  {
    if ( nNewX == -1 )
      nPressed = millis();
    else
    {
      long lPassed = millis() - nPressed;
      if ( lPassed > 5000 )
      {
        nPressed = millis();
        return true;
      }
    }
  } else
  {
    nLastX = -1;
    nNewX = -1;
    return false;
  }

  if ( nLastX != -1 && nNewX != -1 )
  {
    draw.line(nLastX, nLastY, nNewX, nNewY);
  }

  nLastX = nNewX;
  nLastY = nNewY;

  if (!touch.Get(nNewX, nNewY))
  {
    nNewX = -1;
    nLastX = -1;
  }
  return false;
}
  
void Ball(int x0, int y0, int x1, int y1)
{
  unsigned long lBack = 0x0060b0;

  const int r = 20;
  const int g = 150;
  const int b = 10;
  const int w = x1-x0;
  const int h = y1-y0;  
  const int cx = (w*128)>>8;  // center   
  const int cy = (w*128)>>8;    
  const int gx = (w*133)>>8;  // glow
  const int gy = (h*159)>>8;
  const int sx = (w*179)>>8;  // shadow
  const int sy = (h*205)>>8;
  const int lc = (60*w)>>7;   
  const int lg = (70*w)>>7;
  const int ls = (50*w)>>7;
    
  const long aMat[9] =
    {r, 240-r, -60,
    g, 240-g, -60,
    b, 240-b, -60};
  
  lcd.SetRegion(x0, y0, x1, y1);
  
  for (long y=0; y<h; y++)
    for (long x=0; x<w; x++)
    {
      unsigned long a = (x-cx)*(x-cx) + (y-cy)*(y-cy);      
      a = sqrt( a *256*256/lc/lc );      
      a = min(max(0, a), 255);      
      a = (255-a)*5;
      a = min(max(0, a), 255);      
      long c = (x-gx)*(x-gx) + (y-gy)*(y-gy);
      c = sqrt( c *256*256/lg/lg );
      c = c*c/256;
      c = min(c, 255);      
      long s = (x-sx)*(x-sx) + (y-sy)*(y-sy);
      s = 255-sqrt( s *256*156/ls/ls);
      s = min(max(0, s), 255);
      long r = aMat[0*3+0] + ((aMat[0*3+1]*c)>>8) + ((aMat[0*3+2]*s)>>8);
      long g = aMat[1*3+0] + ((aMat[1*3+1]*c)>>8) + ((aMat[1*3+2]*s)>>8);
      long b = aMat[2*3+0] + ((aMat[2*3+1]*c)>>8) + ((aMat[2*3+2]*s)>>8);      
      r = min(max(0, r), 255);
      g = min(max(0, g), 255);
      b = min(max(0, b), 255);
      //a = 255;      
      unsigned long rgb = (unsigned long)b | ((unsigned long)g << 8) | ((unsigned long)r << 16);
      lcd.PutPixel(lcd.GetColor(lcd.Interpolate(lBack, rgb, a)));
    }  
}

void scrollInit()
{
  chess();
  draw.DrawText(lcd.Width - draw.FontWidth2x*11, lcd.Height/2 - draw.FontHeight2x/2 , "Scrolling!!", true);
  lcd._Write(0x0042,0x013f+96);  
}

void scrollDo()
{
  int x=(1+(sin(millis()/100.0f)))*120;
  lcd._Write(0x0041, x); 
}

void scrollEnd()
{
  lcd._Write(0x0041, 0);   
}

void mandelbrot()
{
  class complex
  {
  public:
    typedef float real;
    
    real r, i;
  public:
    complex(const real x, const real y) : r(x), i(y) {}
    complex operator *(const complex& b)
    {
      complex& a = *this;
      return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);      
    }
    real len2()
    {
      return abs(r)+abs(i);
    }
    complex& operator+(const complex add)
    {
      r += add.r;
      i += add.i;
      return *this;
    }
  };
  
  complex::real cxmin = -2.2;
  complex::real cxmax = 0.6;
  complex::real cymin = -1.2;
  complex::real cymax = 1.2;

  int w = lcd.Width;
  int h = lcd.Height;

  const int max_iterations = 30;
  unsigned long arrColors[] = {0x0000b0, 0xb00000, 0x00b0b0, 0xb000b0, 0xb0b000, 0xffffff};
  
  lcd.SetRegion(0, 0, lcd.Width, lcd.Height);  
  for (int y=0; y<h; y++)
    for (int x=0; x<w; x++)
    {
      complex c(cxmin + x*(cxmax-cxmin)/w, cymin + y*(cymax-cymin)/h);
      complex z(0, 0);
      unsigned int iterations;
 
      for (iterations = 0; iterations < max_iterations && z.len2() < 4.0; ++iterations) 
        z = z*z + c;

      if (iterations == max_iterations)
      {
        lcd.PutPixel(0);
        continue;
      }
      
      unsigned short clr = multigrad(arrRainbowColors, (sizeof(arrRainbowColors)/sizeof(arrRainbowColors[0])), iterations*30);
      lcd.PutPixel(clr);
    }
}

void setup()
{ 
  lcd.Init();  
  touch.Init();
  draw.DrawText(lcd.Width/2 - draw.FontWidth2x/2*14, lcd.Height/2 - draw.FontHeight2x/2 , "ILI9325D test!", true);
  draw.SetBkgColor(0x0060b0);

  draw.DrawText(100, lcd.Height-draw.FontHeight, "     Gradient!     ", false);
  gradient();
  draw.DrawText(100, lcd.Height-draw.FontHeight, "    Chess board    ", false);
  chess();
  draw.DrawText(100, lcd.Height-draw.FontHeight, "Nice smooth 3d ball", false);
  Ball(80, 40, 240, 200);
  draw.DrawText(0, 0, "touch the screen for drawing, or hold...", false);
}

void loop()
{
  /*
  CCalibrationProcess proc;
  proc.Init();
  proc.Do();
  */
  static unsigned int nCurrentApp = -1;
  bool bSwapApp = Paint();

  if ( bSwapApp || nCurrentApp == -1 )
  {
    if ( nCurrentApp == 5 )
      scrollEnd();
    
    if (++nCurrentApp > 6)
      nCurrentApp = 0;

    if ( nCurrentApp == 0 )
      draw.DrawText(100, lcd.Height-draw.FontHeight, "Sierpinski triangle", false);
    if ( nCurrentApp == 1 )
      draw.DrawText(100, lcd.Height-draw.FontHeight, "       Worm        ", false);
    if ( nCurrentApp == 2 )
    {
      chess();
      draw.DrawText(100, lcd.Height-draw.FontHeight, "      Drawing      ", false);
    }
    if ( nCurrentApp == 3 )
    {
      gradient();
      draw.DrawText(100, lcd.Height-draw.FontHeight, "      Drawing      ", false);
    }
    if ( nCurrentApp == 4 )
    {
      spheres();
      draw.DrawText(100, lcd.Height-draw.FontHeight, "      Drawing      ", false);
    }
    if ( nCurrentApp == 5 )
    {
      scrollInit();
    }
    if ( nCurrentApp == 6 )
    {
      draw.DrawText(100, lcd.Height-draw.FontHeight, "    Mandelbrot     ", false);
      mandelbrot();
      draw.DrawText(100, lcd.Height-draw.FontHeight, "    Mandelbrot     ", false);
    }
  }
  if ( nCurrentApp == 0 )
    sierpinski();
  if ( nCurrentApp == 1 )
    worm();
  if ( nCurrentApp == 5 )
    scrollDo();
}

