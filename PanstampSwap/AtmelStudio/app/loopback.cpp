#include "loopback.h"
#include <avr/io.h>

/*virtual*/ void CAppLoopback::Init()
{
	// requires leds app
}

/*virtual*/ void CAppLoopback::Loop() 
{
	if ( HAL::COM::Ready() && HAL::COM::Available() )
	{
		char ch = HAL::COM::Get();
		PORTA.OUT = ~ch;
		HAL::COM::Put( ch );
	}
			
	PORTA.OUT = ~(HAL::TIME::GetTick() / 1000);
}
