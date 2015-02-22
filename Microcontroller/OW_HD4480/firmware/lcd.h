#include <pic.h>
#include "delay.h"

void __LCD_SEND(unsigned char i, unsigned char rs);

#define LCD_CURSOR_UNDERLINE 0x0e
#define LCD_CURSOR_BLOCK 0x0f
#define LCD_CURSOR_HIDDEN 0x0c

void LCD_INIT(void);
void LCD_PRINT(const char * s);
void LCD_CLEAR(void);
void LCD_GOTO(unsigned char pos);
void LCD_CUSTOM(unsigned char pos);
void LCD_PUTCH(unsigned char ch);
void LCD_PRINTNUM(unsigned int i);
void LCD_PUTHEX(unsigned char i);
void LCD_SETCURSOR(unsigned char c);