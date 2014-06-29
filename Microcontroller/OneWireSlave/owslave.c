#include "owslave.h"
#include "owutils.h"

byte ow_status; // 0 - waiting for reset, ROM_CMD - waiting for rom command, FUNCTION_CMD - waiting for function command
byte ow_buffer; // buffer for data received on 1-wire line
byte timeout; 

volatile byte OW_scratchpad[OW_SCRATCHPAD_LEN];
volatile byte OW_scratchpad_valid = 0;
volatile byte OW_scratchpad_request = 0;
volatile byte OW_serial[8];

#define INIT_SEQ() { ow_status=0; ow_error=0; ow_buffer=0; timeout=200; }

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
        SEARCH_SEND_BYTE( OW_serial[i] );
      } while (i--);
 			INIT_SEQ();
    } else
    if ( ow_buffer == 0x55 ) // match rom
    {
      i = 7;
			do {
        SEARCH_MATCH_BYTE( OW_serial[i] );
      } while (i--);
      if ( i==(byte)-1 )
      {
  			INIT_SEQ();
        ow_status = FUNCTION_CMD;
        // OK
      } else
      {
        // FAIL
   			INIT_SEQ();
      }
    } else
    if ( ow_buffer == 0x33 ) // send rom
    {                
      i = 7;
      do {
        while(OW);
			  OW_write_byte(OW_serial[i]);
      } while (i--);

      INIT_SEQ();
    } else
    if ( ow_buffer == 0xCC ) // skip rom
    {
			INIT_SEQ();
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
			goto RST;

		// WTF? Not enough time to test scratchpad_valid value?
    if ( ow_buffer == 0xBE /*&& scratchpad_valid*/ ) // read scratchpad
    {
      i = OW_SCRATCHPAD_LEN-1;
		  do
      {
        while(OW);    
        OW_write_byte(OW_scratchpad[i]);
      } while (i--);
    } 

    if ( ow_buffer == 0x44 ) // start conversion
    {
		  OW_scratchpad_valid = 0;
      OW_scratchpad_request = 1;
    }

		INIT_SEQ();
		INTF = 0;
		return;
	}

RST:
	if ( OW_reset_pulse() )
  {
    // if reset detected 
		__delay_us(30);
		OW_presence_pulse(); // generate presence pulse
		INIT_SEQ();
		ow_status = ROM_CMD; // and wait for rom command
	} else
  {
		INIT_SEQ(); // else reset all settings
  }

	INTF = 0;
	return;
}

void OW_setup()
{
  OSCCON = 0b01110001;  /// 8 MHz

  // WDT
	PSA = 1; //prescaler assigned to WDT
	PS0 = 1; PS1 = 1; PS2 = 1; //prescale = 128, WDT period = 2.3 s

	// Disable ADC, enable using GPOI2 as INT
  ANSEL = 0; // all digital pins
  CMCON0 = 0b00000111;
 
  // clear watchdog
	CLRWDT();

  // configure GPIO change interrupt
	INTEDG = 0; //external interrupt on falling edge
  INTE = 1;
}

void OW_start(void)
{
  // init state machine
  INIT_SEQ();
  // enable interrupts
	GIE = 1; 
}

void OW_stop(void)
{
  // disable interrupts
	GIE = 0; 
}

void OW_loop()
{
  if ( timeout ) 
  { 
    byte i;

    timeout--;
    CLRWDT();

    // wait 10 ms or until a request was made
    for (i=40; i-- && !OW_scratchpad_request; )
    {
      DelayUs(250);
    }
    return;
  }
  DBG(1,1);
  // go to sleep after 2 second of inactivity
  CLRWDT();
  SLEEP();
  NOP();
  DBG(0,0);
}
