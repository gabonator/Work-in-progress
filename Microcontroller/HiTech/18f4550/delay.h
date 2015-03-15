/*
 *	Delay functions for HI-TECH C on the PIC18
 *
 *	Functions available:
 *		DelayUs(x)	Delay specified number of microseconds
 *		DelayMs(x)	Delay specified number of milliseconds
 *
 *	Note that there are range limits: 
 *	- on small values of x (i.e. x<10), the delay becomes less
 *	accurate. DelayUs is accurate with xtal frequencies in the
 * 	range of 4-16MHZ, where x must not exceed 255. 
 *	For xtal frequencies > 16MHz the valid range for DelayUs
 *	is even smaller - hence affecting DelayMs.
 *	To use DelayUs it is only necessary to include this file.
 *	To use DelayMs you must include delay.c in your project.
 *
 *	Set the crystal frequency in the CPP predefined symbols list
 *	on the PICC-18 commmand line, e.g.
 *	picc18 -DXTAL_FREQ=4MHZ
 *
 *	or
 *	picc18 -DXTAL_FREQ=100KHZ
 *	
 *	Note that this is the crystal frequency, the CPU clock is
 *	divided by 4.
 *
 *	MAKE SURE this code is compiled with full optimization!!!
*/

#define	MHZ	*1

#ifndef	XTAL_FREQ
#define	XTAL_FREQ	4MHZ		/* Crystal frequency in MHz */
#endif

#if	XTAL_FREQ < 8MHZ
#define	uS_CNT 	238			/* 4x to make 1 mSec */
#endif

#if	XTAL_FREQ == 8MHZ
#define uS_CNT  244
#endif

#if	XTAL_FREQ > 8MHZ
#define uS_CNT  246
#endif

#define FREQ_MULT	(XTAL_FREQ)/(4MHZ)

#define	DelayUs(x)	{ unsigned char _dcnt; \
			  if(x>=4) _dcnt=(x*(FREQ_MULT)/2); \
			  else _dcnt=1; \
			  while(--_dcnt > 0) \
				{\
				asm("nop");\
				asm("nop");\
				continue; }\
		} 

extern void DelayMs(unsigned char);


