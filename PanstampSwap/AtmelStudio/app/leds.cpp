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
	return HAL::IO::Read(HAL::IO::A) >> 4;
}
