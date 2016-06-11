#include "hal/hal.h"

#include "app/modem.h"
#include "app/client.h"
#include "app/dummysender.h"
#include "app/leds.h"
#include "app/loopback.h"

int main(void)
{
	HAL::TIME::Init();
	HAL::COM::Init();

	CAppLeds leds;
	CModem modem;
	CClient client;
	CAppSender sender;	
	CAppLoopback loopback;

//	while ( !HAL::COM::Ready() || !HAL::COM::Available());

#define MODEM
#ifdef MODEM	
	//while ( !HAL::COM::Ready() || !HAL::COM::Available());

	leds.Init();
	leds.Show(0xff);
	modem.Init();
	sender.Init();
	leds.Show(0x00);
	
	while (1)
	{
		//loopback.Loop();
		modem.Loop();
		sender.Loop();
	}
#else
	leds.Init();
	leds.Show(0xff);
	client.Init();
	sender.Init();
	leds.Show(0x00);
	while (1)
	{
		//loopback.Loop();
		client.Loop();
		sender.Loop();
	}
#endif
}

