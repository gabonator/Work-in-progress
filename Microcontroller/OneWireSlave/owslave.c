#include "1wire.h"

__CONFIG(BORDIS & UNPROTECT & MCLRDIS & PWRTEN & WDTEN & INTIO);

void Read_SN(void);

byte SN[8]; // serial number
byte ow_status; // 0 - waiting for reset, ROM_CMD - waiting for rom command, FUNCTION_CMD - waiting for function command
byte ow_buffer; // buffer for data received on 1-wire line
byte timeout; 

#define INIT_SEQ		  	( ow_status=0, ow_error=0, ow_buffer=0, timeout=200 )

#define ERR1() {DBG(0,1); __delay_ms(200); DBG(0,0);}

#define SCRATCHPAD_LEN 7
volatile byte scratchpad[SCRATCHPAD_LEN];
volatile byte scratchpad_valid = 0;
volatile byte scratchpad_request = 0;

void ERROR(unsigned char i)
{
  DBG(0, 0);
  DelayMs(200);  
  DelayMs(200);
  while (i--)
  {
    DBG(0, 1);
    DelayMs(200);
    DBG(0, 0);
    DelayMs(200);
  }
  DelayMs(200);  
  DelayMs(200);
}

void interrupt ISR(void)
{
	byte i;
	byte current_byte;
	
	if ( ow_status == ROM_CMD )
  { 
    // ROM command
		ow_buffer = OW_read_byte();
		if(ow_error)
			goto RST; // nedava zmysel

		if ( ow_buffer == 0xF0 ) // search rom
    {
      i = 7;
			do {
        SEARCH_SEND_BYTE( SN[i] );
      } while (i--);
 			INIT_SEQ; 
    } else
    if ( ow_buffer == 0x55 ) // match rom
    {
      i = 7;
			do {
        SEARCH_MATCH_BYTE( SN[i] );
      } while (i--);
      if ( i==(byte)-1 )
      {
  			INIT_SEQ; 
        ow_status = FUNCTION_CMD;
        // OK
      } else
      {
        // FAIL
   			INIT_SEQ; 
      }
    } else
    if ( ow_buffer == 0x33 ) // send rom
    {                
      // TODO: check timing!
      i = 7;
      do {
        while(OW);
			  OW_write_byte(SN[i]);
      } while (i--);

      INIT_SEQ;
    } else
    if ( ow_buffer == 0xCC ) // skip rom
    {
			INIT_SEQ;
			ow_status = FUNCTION_CMD;
	    }
		INTF = 0;
		return;
	}

  if ( ow_status == FUNCTION_CMD )
  { 
    // Function command
		ow_buffer = OW_read_byte();
 
		if(ow_error)
			goto RST;  // TODO: Z nejakeho dovodu sa dostane sem aj ked vobec neposiela master data!

    if ( ow_buffer == 0xBE /*&& scratchpad_valid*/ ) // read scratchpad
    {
      i = SCRATCHPAD_LEN-1;
		  do
      {
        while(OW);
        OW_write_byte(scratchpad[i]);
      } while (i--);
    } 

    if ( ow_buffer == 0x44 ) // start conversion
    {
		  scratchpad_valid = 0;
      scratchpad_request = 1;
    }

		INIT_SEQ;
		INTF = 0;
		return;
	}

RST:
	if ( OW_reset_pulse() )
  {
    // if reset detected 
		__delay_us(30);
		OW_presence_pulse(); // generate presence pulse
		INIT_SEQ;
		ow_status = ROM_CMD; // and wait for rom command
	} else
  {
		INIT_SEQ; // else reset all settings
  }

	INTF = 0;
	return;
}

void main(void) 
{
  OSCCON = 0b01110001;
	TRISIO = 0xFF; //all inputs
//	TRISA = 0xFF; //all inputs
//	TRISB = 0xFF; 
  //DBG
  TRISIO4 = 0;
  TRISIO5 = 0;
  DBG(0,1);
  X__delay_ms(250);
  DBG(0, 0);
  X__delay_ms(250);
  DBG(0,1);
  X__delay_ms(250);
  DBG(0, 0);
  X__delay_ms(250);

//  WPU0 = 1;

#ifdef LEDMOD
	TRIS_LED1 = OUTPUT; TRIS_LED2 = OUTPUT;	// output for leds
#endif
  // WDT
	PSA = 1; //prescaler assigned to WDT
	PS0 = 1; PS1 = 1; PS2 = 1; //prescale = 128, WDT period = 2.3 s
	Read_SN(); // read serial number from eeprom

//  IOC0 = 1;
  ANSEL = 0; // all digital pins
  CMCON0 = 0b00000111;

	INTEDG = 0; //external interrupt on falling edge
	INTE = 1; //enable external interrupts
	GIE = 1; //enable global interrupts

	INIT_SEQ;

	while (TRUE) 
  {
    if ( scratchpad_request )
    {
      GIE = 0;
      DBG(1, 0);
      X__delay_ms(200);
      DBG(0, 0);

      if ( scratchpad[0] == 0xab )
        scratchpad[6]++;
      else
        scratchpad[6] = 0x56;
      scratchpad[0] = 0xab;
      scratchpad[1] = 0xcd;
      scratchpad[2] = 0xef;
      scratchpad[3] = 0x00;
      scratchpad[4] = 0x12;
      scratchpad[5] = 0x34;
      scratchpad_valid = 1;
      scratchpad_request = 0;
      GIE = 1;
    }

		if ( timeout ) 
    { // go to sleep after 1 second of inactivity
			CLRWDT();
			X__delay_ms(10); //0.1 s * 200 = 2 s
			timeout--;
			continue;
		}

    DBG(1, 1);
		CLRWDT();
		SLEEP();
		NOP();
    DBG(0, 0); 
	}
}

void Read_SN(void) 
{
	byte address = 0;

  SN[7] = 0xBF;
  SN[6] = 0x54;
  SN[5] = 0x59;
  SN[4] = 0x4D;
  SN[3] = 0x45;
  SN[2] = 0x4B;
  SN[1] = 0x00;
  SN[0] = 0x94;

//	SN[7] = CalcCRC(7, SN);

  scratchpad[0] = 0x12;
  scratchpad[1] = 0x34;
  scratchpad[2] = 0x56;
  scratchpad[3] = 0x78;
  scratchpad[4] = 0x9a;
  scratchpad[5] = 0xbc;
}
