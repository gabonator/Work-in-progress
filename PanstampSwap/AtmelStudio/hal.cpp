//#define F_CPU 4000000
#include <avr/io.h>
#include "hal.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

// internal {{{
HAL::INT::THandlerFunction hPortCIsrHandler = nullptr;

ISR(PORTA_INT0_vect)
{
//	while ( 1 );
	if ( hPortCIsrHandler )
		hPortCIsrHandler();

	PORTA.INTFLAGS = 0xff; 
}

volatile uint32_t g_nTickCount = 0;

ISR(TCC1_COMPA_vect)
{
	++g_nTickCount;
}
ISR(TCC1_OVF_vect)
{
	++g_nTickCount;
}
// }}} internal

/*static*/ void HAL::SPI::Init()
{
	// SS -> C4
	IO::Configure(IO::C4, IO::Output);
	
	// MOSI -> C5
	IO::Configure(IO::C5, IO::Output);

	// MISO -> C6
	IO::Configure(IO::C6, IO::Input);

	// CLK -> C7
	IO::Configure(IO::C7, IO::Output);

	// Master, enabled, mode0, CLK/64 TODO: switch to CLK/4!!!
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV64_gc;
}

/*static*/ byte HAL::SPI::Send(byte data)
{
	enum {
		SPI_STATUS_COMPLETED_bm = 0x80
	};

	SPIC.DATA = data;

	while (!(SPIC.STATUS & SPI_STATUS_COMPLETED_bm));

	return SPIC.DATA;
}

/*static*/ void HAL::IO::Configure(EPin ePin, EMode eMode)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};

	byte nPortIndex = ePin / 8;
	byte nPortPin = ePin % 8;
	byte nPortMask = 1 << nPortPin;

	PORT_t* pPort = arrPorts[nPortIndex];
	register8_t& regCtrl = (&pPort->PIN0CTRL)[nPortPin];
	register8_t& regDirSet = pPort->DIRSET;
	register8_t& regDirClr = pPort->DIRCLR;

	regCtrl = eMode & PullUp ? (PORT_OPC_PULLUP_gc | PORT_INT0IF_bm ): PORT_OPC_TOTEM_gc;
	if ( eMode & Output )
		regDirSet = nPortMask;
	else
		regDirClr = nPortMask;
}

/*static*/ void HAL::IO::Write(EPin ePin, byte bValue)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};

	byte nPortIndex = ePin / 8;
	byte nPortPin = ePin % 8;
	byte nPortMask = 1 << nPortPin;

	PORT_t* pPort = arrPorts[nPortIndex];
	
	if ( bValue )
		pPort->OUTSET = nPortMask;
	else
		pPort->OUTCLR = nPortMask;
}

/*static*/ byte HAL::IO::Read(EPin ePin)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};

	byte nPortIndex = ePin / 8;
	byte nPortPin = ePin % 8;

	PORT_t* pPort = arrPorts[nPortIndex];
	
	return (pPort->IN >> nPortPin) & 1;
}

/*static*/ void HAL::IO::Write(EPort ePort, byte bValue)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};

	arrPorts[ePort]->OUT = bValue;
}

/*static*/ byte HAL::IO::Read(EPort ePort)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};
		
	return arrPorts[ePort]->IN;
}

/*static*/ void HAL::INT::Attach(IO::EPin ePin, HAL::INT::THandlerFunction pHandler)
{
	static PORT_t* const arrPorts[] = {&PORTA, &PORTB, &PORTC, &PORTD};

	byte nPortIndex = ePin / 8;
	byte nPortPin = ePin % 8;
	byte nPortMask = 1 << nPortPin;

	PORT_t* pPort = arrPorts[nPortIndex];
	register8_t regCtrl = (&pPort->PIN0CTRL)[nPortPin];

	if ( pHandler )	
	{
		pPort->INTCTRL = PORT_INT0LVL0_bm;
		pPort->INT0MASK |= nPortMask;
		pPort->INTFLAGS = PORT_INT0IF_bm;
		regCtrl |= PORT_ISC_FALLING_gc;
		PMIC.CTRL = PMIC_LOLVLEN_bm;
		
		pPort->INTFLAGS = 0xff; //PIN1_bm; -> clear
	} else {
		pPort->INT0MASK &= ~nPortMask;
	}
	
	hPortCIsrHandler = pHandler;	
}

/*static*/ void HAL::INT::Enable()
{	
	sei();
}

/*static*/ void HAL::INT::Disable()
{
	cli();
}

#if 0
/*static*/ void HAL::TIME::DelayMs(int nMs)
{
	_delay_ms(nMs);
}

/*static*/ void HAL::TIME::DelayUs(int nUs)
{
	_delay_us(nUs);
}

#endif

/*static*/ void HAL::TIME::Init()
{
	// https://github.com/zkemble/millis/blob/master/millis/millis.c
/*
	#define PRESCALER 1
	#define TCCR1A TCC1_CTRLA
	#define TCCR1B TCC1_CTRLB
	#define TIMSK1 TCC1_INTCTRLB 
	#define _BIT_OCIE TC_CCAINTLVL_LO_gc
	#define OCR1A TCC1_CCA
	#define _WGM12 TC_WGMODE_FRQ_gc
	#define _CS10 TC1_CCAEN_bm 
	
	// PMIC_LOLVLEN_bm
	//PMIC_
	TCCR1A = 0;
	TCCR1B = _WGM12 | _CS10;
	TIMSK1 = _BIT_OCIE;
	OCR1A = (F_CPU / PRESCALER) / 1000;
	
	PMIC.CTRL |= PMIC_LOLVEN_bm;
	*/

//http://www.avrfreaks.net/forum/simple-xmega-timer
	//tc_enable(&TCC0);
	enum {
		SYSCLK_PORT_C = 3,
		  TC_CLKSEL_DIV1_gc = (0x01) 
		};
		 
	*((uint8_t *)&PR.PRGEN + 3) &= ~PR_TC1_bm;
	*((uint8_t *)&PR.PRGEN + 3) &= ~PR_HIRES_bm;
		
	//sysclk_enable_module(SYSCLK_PORT_C, PR_TC1_bm);
	//sysclk_enable_module(SYSCLK_PORT_C, PR_HIRES_bm);
	
	//tc_set_overflow_interrupt_callback(&TCC0, ticktimer_callback);
	//tc_set_wgm(&TCC0, TC_WG_NORMAL);
	TCC0.CTRLB = (TCC0.CTRLB & ~TC0_WGMODE_gm) | TC_WGMODE_NORMAL_gc;
	//tc_write_period(&TCC0, 1000);
	TCC0.PER = 1000;
	//tc_set_overflow_interrupt_level(&TCC0, TC_INT_LVL_LO);
	TCC0.INTCTRLA = TCC0.INTCTRLA & ~TC0_OVFINTLVL_gm;
	TCC0.INTCTRLA = TCC0.INTCTRLA | TC0_OVFINTLVL0_bm; //(TC_INT_LVL_LO << TC0_OVFINTLVL_gp);	
	//tc_write_clock_source(&TCC0, TC_CLKSEL_DIV1_gc);
	TCC0.CTRLA = (TCC0.CTRLA & ~TC0_CLKSEL_gm) | TC_CLKSEL_DIV1_gc;
}

/*static*/ uint32_t HAL::TIME::GetTick()
{
	uint32_t ms;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		ms = g_nTickCount;
	}
	return ms;	
}