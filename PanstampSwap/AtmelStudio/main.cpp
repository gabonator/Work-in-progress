#include "hal.h"

#include "app/modem.h"
#include "app/dummysender.h"
#include "app/leds.h"
#include "app/apppanstamp.h"
#include "app/loopback.h"

int main(void)
{
	HAL::TIME::Init();
	HAL::COM::Init();
	
	while ( !HAL::COM::Ready() || !HAL::COM::Available());

	//panstamp.Init();

	CAppLeds leds;
	CModem app;
	//CAppSender sender;
	//CAppLoopback loopback;
	
	//loopback.Init();
	leds.Init();
	app.Init();
	//sender.Init();
	while (1)
	{
		//loopback.Loop();
		app.Loop();
		//sender.Loop();
	}
}

