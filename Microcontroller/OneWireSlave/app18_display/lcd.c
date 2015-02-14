#include "lcd.h"


void Shiftreg_Init(void)
{
  TRISB = 0b00001001;
  PORTB = 0xff;
}

void Shiftreg_Send(char n)
{
  PORTB = n;
}

void Shiftreg_Update(void)
{
}

void __LCD_SEND(unsigned char i, unsigned char rs)
{
	unsigned char send;

	DelayUs(30); // 20 ok, 10 error
 
	send = i & 0b11110000;

	if (rs)
		send |= 1<<2;

	Shiftreg_Send( send | (1<<1) );
	Shiftreg_Update();
	Shiftreg_Send( send );
	Shiftreg_Update();

	send = i << 4;

	if (rs)
		send |= 1<<2;

	Shiftreg_Send( send | (1<<1) );
	Shiftreg_Update();
	Shiftreg_Send( send );
	Shiftreg_Update();
}

void LCD_INIT(void)
{
  Shiftreg_Init();
	DelayMs(15);
	__LCD_SEND(0b00110011,0);
	__LCD_SEND(0b00110011,0); // 2x 8bit resets
	__LCD_SEND(0b00110010,0); // 8bit reset then 4bit reset
	__LCD_SEND(0b00101100,0); // Function Set - 4bit, 2 lines
	__LCD_SEND(0b00000110,0); // Mode Set - incr. w/crsr shift
	__LCD_SEND(0b00001100,0); // Display on, cursor & blink off
//	LCD_SENDINS(0b00001111,0); // Display on, cursor & blink off
	__LCD_SEND(0b00000001,0); // Display Clear
	__LCD_SEND(0b00000010,0); // Cursor Home
	__LCD_SEND(0x0f,0); 	//blinking cursor
	//__LCD_SEND(0x0e,0); 	//blinking cursor
	DelayMs(15);
}

void LCD_SETCURSOR(unsigned char c)
{
	__LCD_SEND(c,0); 	//blinking cursor
}

void LCD_PRINT(const char * s)
{
	while(*s)
		__LCD_SEND(*s++,1);
}

void LCD_CLEAR(void)
{
	__LCD_SEND(1,0);
}
void LCD_GOTO(unsigned char pos)
{
	__LCD_SEND(0x80|pos,0);
}
void LCD_CUSTOM(unsigned char pos)
{
	pos <<= 3;
	__LCD_SEND(0x40|pos,0);
}
void LCD_PUTCH(unsigned char ch)
{
	__LCD_SEND(ch,1);
}

void LCD_PRINTNUM(unsigned int i)
{
	char ch;
#define mPL(z)	ch = '0'; while (i>=z) { i-=z; ch++; }  LCD_PUTCH(ch);
	mPL(10000)
	mPL(1000)
	mPL(100)
	mPL(10)
	mPL(1)
}

void LCD_PUTHEX(unsigned char i)
{
	LCD_PUTCH("0123456789abcdef"[i>>4]);
	LCD_PUTCH("0123456789abcdef"[i&15]);
}