//#define F_CPU 4000000
#include <avr/io.h>
#include "hal.h"
#include <avr/interrupt.h>
#include <util/atomic.h>

#include "hal/clock/clock.h"
#include "hal/usb/udc/udc.h"
#include "hal/usb/udc/udi.h"
#include "hal/usb/class/cdc/device/udi_cdc.h"

// internal {{{
HAL::INT::THandlerFunction hPortCIsrHandler = nullptr;

ISR(PORTD_INT0_vect)
{
	Serial.print('*');
	if ( hPortCIsrHandler )
		hPortCIsrHandler();

	PORTD.INTFLAGS = 0xff; 
}

volatile uint32_t g_nTickCount = 0;

ISR(TCC0_OVF_vect)
{
	// nebolo skalibrovane!!!
	g_nTickCount += 5; // 5ms per ISR
}

static bool usb_flag_autorize_cdc_transfer = false;

uint8_t usb_callback_cdc_enable(void)
{
	usb_flag_autorize_cdc_transfer = true;
	return true;
}

void usb_callback_cdc_disable(void)
{
	usb_flag_autorize_cdc_transfer = false;
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
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV128_gc; //SPI_PRESCALER_DIV64_gc;
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

	regCtrl &= ~PORT_OPC_gm;
	regCtrl = eMode & PullUp ? (PORT_OPC_PULLUP_gc /*| PORT_INT0IF_bm*/ ): PORT_OPC_TOTEM_gc;
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

 // iba PORTD !!

	byte nPortIndex = ePin / 8;
	byte nPortPin = ePin % 8;
	byte nPortMask = 1 << nPortPin;

	PORT_t* pPort = arrPorts[nPortIndex];
	register8_t& regCtrl = (&pPort->PIN0CTRL)[nPortPin];

	Assert( pPort == &PORTD );

	if ( pHandler )	
	{
		Assert( !hPortCIsrHandler );
		pPort->INTCTRL = PORT_INT0LVL0_bm;
		pPort->INT0MASK |= nPortMask;
		pPort->INTFLAGS = PORT_INT0IF_bm;
		regCtrl |= PORT_ISC_FALLING_gc;
		PMIC.CTRL |= PMIC_LOLVLEN_bm;
		
//TODO
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
	enum {
		PMIC_LVL_LOW    = 0x01,
		PMIC_LVL_MEDIUM = 0x02,
		PMIC_LVL_HIGH   = 0x04,
	};

	enum {
		SYSCLK_PORT_GEN,
		SYSCLK_PORT_A,
		SYSCLK_PORT_B,
		SYSCLK_PORT_C,
		SYSCLK_PORT_D,
		SYSCLK_PORT_E,
		SYSCLK_PORT_F
	};

	enum
	{
		SYSCLK_TC0 = PR_TC0_bm,
		SYSCLK_HIRES = PR_HIRES_bm,
		TC_WG_NORMAL = TC_WGMODE_NORMAL_gc,
		TC_INT_LVL_LO = 0x01
	};


	PMIC.CTRL = PMIC_LVL_LOW | PMIC_LVL_MEDIUM | PMIC_LVL_HIGH;

	//irqflags_t flags = cpu_irq_save();

	*((uint8_t *)&PR.PRGEN + SYSCLK_PORT_C) &= ~SYSCLK_TC0;
	*((uint8_t *)&PR.PRGEN + SYSCLK_PORT_C) &= ~SYSCLK_HIRES;

	//cpu_irq_restore(flags);

	TCC0.CTRLB = (TCC0.CTRLB & ~TC0_WGMODE_gm) | TC_WG_NORMAL;
	// TODO: vyratat 5ms interval
	TCC0.PER = 60000; // 12*1000*5 //1ms -> 5ms?

	TCC0.INTCTRLA = TCC0.INTCTRLA & ~TC0_OVFINTLVL_gm;
	TCC0.INTCTRLA = TCC0.INTCTRLA | (TC_INT_LVL_LO << TC0_OVFINTLVL_gp);

	sei();
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

/*static*/ void HAL::COM::Init()
{
	enum {
		PMIC_LVL_LOW    = 0x01,
		PMIC_LVL_MEDIUM = 0x02,
		PMIC_LVL_HIGH   = 0x04,
	};
	
	sysclk_init();
	PMIC.CTRL = PMIC_LVL_LOW | PMIC_LVL_MEDIUM | PMIC_LVL_HIGH;
	sei();	
	udc_start();
}

/*static*/ uint8_t HAL::COM::Ready()
{
	return usb_flag_autorize_cdc_transfer;
}

/*static*/ uint8_t HAL::COM::Available()
{
	return udi_cdc_multi_is_rx_ready(0);
}

/*static*/ uint8_t HAL::COM::Get()
{
	return udi_cdc_getc();
}

/*static*/ void HAL::COM::Put(uint8_t ch)
{
	udi_cdc_putc(ch);	
}