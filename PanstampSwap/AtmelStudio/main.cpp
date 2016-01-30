#include "hal.h"
#include "cc1101.h"
#include <avr/interrupt.h>
#include <avr/interrupt.h>

void myIsr()
{
	HAL::IO::Write(HAL::IO::A2, !HAL::IO::Read(HAL::IO::A2));
}

int main(void)
{
	HAL::IO::Configure(HAL::IO::A0, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A1, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A2, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A3, HAL::IO::Output);
	HAL::IO::Configure(HAL::IO::A4, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A5, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A6, HAL::IO::InputPullUp);
	HAL::IO::Configure(HAL::IO::A7, HAL::IO::InputPullUp);
		
	HAL::INT::Attach(HAL::IO::A4, myIsr);
	HAL::INT::Enable();

	HAL::IO::Write(HAL::IO::A, 0xff ^ 1);	
	HAL_TIME_DelayMs(100);
	
	CC1101 test;
	while ( !test.init() )
	{
		HAL::IO::Write(HAL::IO::A3, 1);
		HAL_TIME_DelayMs(250);
		HAL::IO::Write(HAL::IO::A3, 0);
		HAL_TIME_DelayMs(250);
	}
	
	HAL::IO::Write(HAL::IO::A, 0xff);
	
    while (1) 
    {
		HAL::IO::Write(HAL::IO::A3, 0);
			
		HAL_TIME_DelayMs(1);
			HAL::IO::Write(HAL::IO::A3, 1);
		HAL_TIME_DelayMs(499);
		
		//HAL::IO::Write(HAL::IO::A, HAL::IO::Read(HAL::IO::A) >> 4);
    }
}

