#define F_CPU 4000000
#include <avr/io.h>
#include "hal.h"
#include <avr/interrupt.h>

// internal {{{
HAL::INT::THandlerFunction hPortCIsrHandler = nullptr;
ISR(PORTA_INT0_vect)
{
//	while ( 1 );
	if ( hPortCIsrHandler )
		hPortCIsrHandler();

	PORTA.INTFLAGS = 0xff; 
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

	pPort->INTCTRL = PORT_INT0LVL0_bm;
	pPort->INT0MASK = nPortMask;
	pPort->INTFLAGS = PORT_INT0IF_bm;
	regCtrl |= PORT_ISC_FALLING_gc;
	PMIC.CTRL = PMIC_LOLVLEN_bm;
	
	hPortCIsrHandler = pHandler;
		
	pPort->INTFLAGS = 0xff; //PIN1_bm; -> clear
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