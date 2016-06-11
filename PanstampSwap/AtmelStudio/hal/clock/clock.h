#include "../compiler.h"
#include "../conf/conf_clock.h"
#include "ccp.h"
//#include <avr/io.h>
#include <stddef.h>


#define SYSCLK_PSADIV_1      CLK_PSADIV_1_gc      //!< Do not prescale
#define SYSCLK_PSADIV_2      CLK_PSADIV_2_gc      //!< Prescale CLKper4 by 2
#define SYSCLK_PSADIV_4      CLK_PSADIV_4_gc      //!< Prescale CLKper4 by 4
#define SYSCLK_PSADIV_8      CLK_PSADIV_8_gc      //!< Prescale CLKper4 by 8
#define SYSCLK_PSADIV_16     CLK_PSADIV_16_gc     //!< Prescale CLKper4 by 16
#define SYSCLK_PSADIV_32     CLK_PSADIV_32_gc     //!< Prescale CLKper4 by 32
#define SYSCLK_PSADIV_64     CLK_PSADIV_64_gc     //!< Prescale CLKper4 by 64
#define SYSCLK_PSADIV_128    CLK_PSADIV_128_gc    //!< Prescale CLKper4 by 128
#define SYSCLK_PSADIV_256    CLK_PSADIV_256_gc    //!< Prescale CLKper4 by 256
#define SYSCLK_PSADIV_512    CLK_PSADIV_512_gc    //!< Prescale CLKper4 by 512
#define SYSCLK_PSBCDIV_1_1   CLK_PSBCDIV_1_1_gc
#define SYSCLK_PSBCDIV_1_2   CLK_PSBCDIV_1_2_gc
#define SYSCLK_PSBCDIV_4_1   CLK_PSBCDIV_4_1_gc
#define SYSCLK_PSBCDIV_2_2   CLK_PSBCDIV_2_2_gc

#define OSC_ID_USBSOF         0xff

#define SYSCLK_SRC_RC2MHZ    CLK_SCLKSEL_RC2M_gc
//! Internal 32 MHz RC oscillator
#define SYSCLK_SRC_RC32MHZ   CLK_SCLKSEL_RC32M_gc
//! Internal 32 KHz RC oscillator
#define SYSCLK_SRC_RC32KHZ   CLK_SCLKSEL_RC32K_gc
//! External oscillator
#define SYSCLK_SRC_XOSC      CLK_SCLKSEL_XOSC_gc
//! Phase-Locked Loop
#define SYSCLK_SRC_PLL       CLK_SCLKSEL_PLL_gc

#define OSC_ID_RC2MHZ         OSC_RC2MEN_bm
//! 32 MHz Internal RC Oscillator
#define OSC_ID_RC32MHZ        OSC_RC32MEN_bm
//! 32 KHz Internal RC Oscillator
#define OSC_ID_RC32KHZ        OSC_RC32KEN_bm
//! External Oscillator
#define OSC_ID_XOSC           OSC_XOSCEN_bm

enum sysclk_port_id {
	SYSCLK_PORT_GEN,   //!< Devices not associated with a specific port.
	SYSCLK_PORT_A,     //!< Devices on PORTA
	SYSCLK_PORT_B,     //!< Devices on PORTB
	SYSCLK_PORT_C,     //!< Devices on PORTC
	SYSCLK_PORT_D,     //!< Devices on PORTD
	SYSCLK_PORT_E,     //!< Devices on PORTE
	SYSCLK_PORT_F,     //!< Devices on PORTF
};


static inline void sysclk_set_prescalers(uint8_t psadiv, uint8_t psbcdiv)
{
	ccp_write_io((uint8_t *)&CLK.PSCTRL, psadiv | psbcdiv);
}

static inline void osc_user_calibration(uint8_t id, uint16_t calib)
{
	switch (id) {
		case OSC_ID_RC2MHZ:
		#if !XMEGA_E
		DFLLRC2M.CALA=LSB(calib);
		DFLLRC2M.CALB=MSB(calib);
		#endif
		break;

		case OSC_ID_RC32MHZ:
		DFLLRC32M.CALA=LSB(calib);
		DFLLRC32M.CALB=MSB(calib);
		break;

		#if XMEGA_E
		case OSC_ID_RC8MHZ:
		OSC.RC8MCAL=LSB(calib);
		break;
		#endif

		default:
			Assert(false);
		break;
	}
}

static inline void osc_enable_internal(uint8_t id)
{
	irqflags_t flags;

	Assert(id != OSC_ID_USBSOF);

	flags = cpu_irq_save();
	OSC.CTRL |= id;
	cpu_irq_restore(flags);
}

static inline void osc_enable_external(uint8_t id)
{
	Assert(0);
}

static inline void osc_enable(uint8_t id)
{
	if (id != OSC_ID_XOSC) {
		osc_enable_internal(id);
		} else {
		osc_enable_external(id);
	}
}

static inline void osc_disable(uint8_t id)
{
	irqflags_t flags;

	Assert(id != OSC_ID_USBSOF);

	flags = cpu_irq_save();
	OSC.CTRL &= ~id;
	cpu_irq_restore(flags);
}

static inline void osc_enable_autocalibration(uint8_t id, uint8_t ref_id)
{
	irqflags_t flags;

	flags = cpu_irq_save();
	switch (id) {
	case OSC_ID_RC2MHZ:
#if !XMEGA_E
		Assert((ref_id == OSC_ID_RC32KHZ) || (ref_id == OSC_ID_XOSC));
		if (ref_id == OSC_ID_XOSC) {
			osc_enable(OSC_ID_RC32KHZ);
			OSC.DFLLCTRL |= OSC_RC2MCREF_bm;
		} else {
			OSC.DFLLCTRL &= ~(OSC_RC2MCREF_bm);
		}
		DFLLRC2M.CTRL |= DFLL_ENABLE_bm;
#endif
		break;

	case OSC_ID_RC32MHZ:
#if XMEGA_AU || XMEGA_B || XMEGA_C || XMEGA_E
		Assert((ref_id == OSC_ID_RC32KHZ)
				|| (ref_id == OSC_ID_XOSC)
# if !XMEGA_E
				|| (ref_id == OSC_ID_USBSOF)
#endif
				);

		OSC.DFLLCTRL &= ~(OSC_RC32MCREF_gm);

		if (ref_id == OSC_ID_XOSC) {
			osc_enable(OSC_ID_RC32KHZ);
			OSC.DFLLCTRL |= OSC_RC32MCREF_XOSC32K_gc;
		}
		else if (ref_id == OSC_ID_RC32KHZ) {
			OSC.DFLLCTRL |= OSC_RC32MCREF_RC32K_gc;
		}
# if !XMEGA_E
		else if (ref_id == OSC_ID_USBSOF) {
			/*
			 * Calibrate 32MRC at 48MHz using USB SOF
			 * 48MHz / 1kHz = 0xBB80
			 */
			DFLLRC32M.COMP1 = 0x80;
			DFLLRC32M.COMP2 = 0xBB;
			OSC.DFLLCTRL |= OSC_RC32MCREF_USBSOF_gc;
		}
# endif
#else
		Assert((ref_id == OSC_ID_RC32KHZ) ||
				(ref_id == OSC_ID_XOSC));

# if defined(OSC_RC32MCREF_gm)
		OSC.DFLLCTRL &= ~(OSC_RC32MCREF_gm);
# endif

		if (ref_id == OSC_ID_XOSC) {
			osc_enable(OSC_ID_RC32KHZ);
# if defined(OSC_RC32MCREF_gm)
			OSC.DFLLCTRL |= OSC_RC32MCREF_XOSC32K_gc;
# else
			OSC.DFLLCTRL |= OSC_RC32MCREF_bm;
# endif
		}
		else if (ref_id == OSC_ID_RC32KHZ) {
# if defined(OSC_RC32MCREF_gm)
			OSC.DFLLCTRL |= OSC_RC32MCREF_RC32K_gc;
# else
			OSC.DFLLCTRL &= ~(OSC_RC32MCREF_bm);
# endif
		}
#endif

		DFLLRC32M.CTRL |= DFLL_ENABLE_bm;
		break;

	default:
		Assert(false);
		break;
	}
	cpu_irq_restore(flags);
}

static inline bool osc_is_ready(uint8_t id)
{
	Assert(id != OSC_ID_USBSOF);

	return OSC.STATUS & id;
}

static inline void osc_wait_ready(uint8_t id)
{
	while (!osc_is_ready(id)) {
		/* Do nothing */
	}
}

void sysclk_init(void)
{
	uint8_t *reg = (uint8_t *)&PR.PRGEN;
	uint8_t i;
#ifdef CONFIG_OSC_RC32_CAL
	uint16_t cal;
	/* avoid Cppcheck Warning */
	(void)(cal);
#endif
	bool need_rc2mhz = false;

	/* Turn off all peripheral clocks that can be turned off. */
	for (i = 0; i <= SYSCLK_PORT_F; i++) {
		// TODO: gabo: nemozeme vypnut !!! na porte C mame SPI!!
		if ( i != SYSCLK_PORT_C )
			*(reg++) = 0xff;
		else
			reg++;
	}


	/* Set up system clock prescalers if different from defaults */
	if ((CONFIG_SYSCLK_PSADIV != SYSCLK_PSADIV_1)
			|| (CONFIG_SYSCLK_PSBCDIV != SYSCLK_PSBCDIV_1_1)) {
		sysclk_set_prescalers(CONFIG_SYSCLK_PSADIV,
				CONFIG_SYSCLK_PSBCDIV);
	}
		
#if (CONFIG_OSC_RC32_CAL==48000000UL)
	MSB(cal) = nvm_read_production_signature_row(
			nvm_get_production_signature_row_offset(USBRCOSC));
	LSB(cal) = nvm_read_production_signature_row(
			nvm_get_production_signature_row_offset(USBRCOSCA));
	/*
	* If a device has an uncalibrated value in the
	* production signature row (early sample part), load a
	* sane default calibration value.
	*/
	if (cal == 0xFFFF) {
		cal = 0x2340;
	}
	osc_user_calibration(OSC_ID_RC32MHZ,cal);
#endif
	/*
	 * Switch to the selected initial system clock source, unless
	 * the default internal 2 MHz oscillator is selected.
	 */
	if (CONFIG_SYSCLK_SOURCE == SYSCLK_SRC_RC2MHZ) {
		need_rc2mhz = true;
	} else {
		switch (CONFIG_SYSCLK_SOURCE) {
		case SYSCLK_SRC_RC32MHZ:
			osc_enable(OSC_ID_RC32MHZ);
			osc_wait_ready(OSC_ID_RC32MHZ);
#ifdef CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC
			if (CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC
					!= OSC_ID_USBSOF) {
				osc_enable(CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
				osc_wait_ready(CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
			}
			osc_enable_autocalibration(OSC_ID_RC32MHZ,
					CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
#else
#error auto cal osc err
#endif
			break;

		case SYSCLK_SRC_RC32KHZ:
			osc_enable(OSC_ID_RC32KHZ);
			osc_wait_ready(OSC_ID_RC32KHZ);
			break;

		case SYSCLK_SRC_XOSC:
			osc_enable(OSC_ID_XOSC);
			osc_wait_ready(OSC_ID_XOSC);
			break;

#ifdef CONFIG_PLL0_SOURCE
		case SYSCLK_SRC_PLL:
			if (CONFIG_PLL0_SOURCE == PLL_SRC_RC2MHZ) {
				need_rc2mhz = true;
			}
			pll_enable_config_defaults(0);
			break;
#endif
#if XMEGA_E
		case SYSCLK_SRC_RC8MHZ:
			osc_enable(OSC_ID_RC8MHZ);
			osc_wait_ready(OSC_ID_RC8MHZ);
			break;
#endif
		default:
			//unhandled_case(CONFIG_SYSCLK_SOURCE);
			return;
		}

		ccp_write_io((uint8_t *)&CLK.CTRL, CONFIG_SYSCLK_SOURCE);
		Assert(CLK.CTRL == CONFIG_SYSCLK_SOURCE);
	}

	if (need_rc2mhz) {
#ifdef CONFIG_OSC_AUTOCAL_RC2MHZ_REF_OSC
		osc_enable(CONFIG_OSC_AUTOCAL_RC2MHZ_REF_OSC);
		osc_wait_ready(CONFIG_OSC_AUTOCAL_RC2MHZ_REF_OSC);
		osc_enable_autocalibration(OSC_ID_RC2MHZ,
				CONFIG_OSC_AUTOCAL_RC2MHZ_REF_OSC);
#endif
	} else {
		osc_disable(OSC_ID_RC2MHZ);
	}

#ifdef CONFIG_RTC_SOURCE
	sysclk_rtcsrc_enable(CONFIG_RTC_SOURCE);
#endif
}

#define SYSCLK_USB        PR_USB_bm     //!< USB Module

void sysclk_enable_module(enum sysclk_port_id port, uint8_t id)
{
	irqflags_t flags = cpu_irq_save();

	*((uint8_t *)&PR.PRGEN + port) &= ~id;

	cpu_irq_restore(flags);
}

void sysclk_enable_usb(uint8_t frequency)
{
	uint8_t prescaler;

	Assert((frequency == 6) || (frequency == 48));

	/*
	 * Enable or disable prescaler depending on if the USB frequency is 6
	 * MHz or 48 MHz. Only 6 MHz USB frequency requires prescaling.
	 */
	if (frequency == 6) {
		prescaler = CLK_USBPSDIV_8_gc;
	}
	else {
		prescaler = 0;
	}

	/*
	 * Switch to the system clock selected by the user.
	 */
	switch (CONFIG_USBCLK_SOURCE) {
	case USBCLK_SRC_RCOSC:
		if (!osc_is_ready(OSC_ID_RC32MHZ)) {
			osc_enable(OSC_ID_RC32MHZ);
			osc_wait_ready(OSC_ID_RC32MHZ);
#ifdef CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC
			if (CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC
					!= OSC_ID_USBSOF) {
				osc_enable(CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
				osc_wait_ready(CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
			}
			osc_enable_autocalibration(OSC_ID_RC32MHZ,
					CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC);
#endif
		}
		ccp_write_io((uint8_t *)&CLK.USBCTRL, (prescaler)
				| CLK_USBSRC_RC32M_gc
				| CLK_USBSEN_bm);
		break;

#ifdef CONFIG_PLL0_SOURCE
	case USBCLK_SRC_PLL:
		pll_enable_config_defaults(0);
		ccp_write_io((uint8_t *)&CLK.USBCTRL, (prescaler)
				| CLK_USBSRC_PLL_gc
				| CLK_USBSEN_bm);
		break;
#endif

	default:
		Assert(false);
		break;
	}

	sysclk_enable_module(SYSCLK_PORT_GEN, SYSCLK_USB);
}


void sysclk_disable_module(enum sysclk_port_id port, uint8_t id)
{
	irqflags_t flags = cpu_irq_save();

	*((uint8_t *)&PR.PRGEN + port) |= id;

	cpu_irq_restore(flags);
}

void sysclk_disable_usb(void)
{
	sysclk_disable_module(SYSCLK_PORT_GEN, SYSCLK_USB);
	ccp_write_io((uint8_t *)&CLK.USBCTRL, 0);
}
