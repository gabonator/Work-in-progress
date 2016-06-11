#include "leds.h"
#include <avr/io.h>

/*virtual*/ void CAppLeds::Init()
{
	HAL::IO::Configure(HAL::IO::A0, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A1, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A2, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A3, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A4, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A5, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A6, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A7, HAL::IO::InputPullUp);
	
	Show(0);
}

/*virtual*/ void CAppLeds::Loop()
{
}

void CAppLeds::Show(uint8_t n)
{
	HAL::IO::Write(HAL::IO::A, ~n);
}

uint8_t CAppLeds::GetButtons()
{
	uint8_t nPortA = ~HAL::IO::Read(HAL::IO::A);
	uint8_t nButtons = 0;

	if ( nPortA & 16 )
		nButtons |= 8;
	if ( nPortA & 32 )
		nButtons |= 4;
	if ( nPortA & 64 )
		nButtons |= 2;
	if ( nPortA & 128 )
		nButtons |= 1;
		
	return nButtons;
}
