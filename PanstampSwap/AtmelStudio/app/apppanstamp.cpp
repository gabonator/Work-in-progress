#include "apppanstamp.h"
#include "../swap/swap.h"

/*static*/ CAppPanstamp CAppPanstamp::m_appPanstamp;

extern REGISTER regProductCode;
extern REGISTER regHwVersion;
extern REGISTER regFwVersion;

const int FREQUENCY = CFREQ_868;

enum PRODUCT {
	SWAP_MANUFACT_ID = 0x00000001UL,
	SWAP_PRODUCT_ID  = 0x0000000AUL,
	HARDWARE_VERSION = 0x00000200UL,
	FIRMWARE_VERSION = 0x00000101UL,
};

void CAppPanstamp::SetupIds()
{
	uint8_t arrProductCode[8] = {
		(uint8_t)((uint32_t)SWAP_MANUFACT_ID >> 24),
		(uint8_t)((uint32_t)SWAP_MANUFACT_ID >> 16) ,
		(uint8_t)((uint32_t)SWAP_MANUFACT_ID >> 8),
		(uint8_t)(SWAP_MANUFACT_ID),
		(uint8_t)((uint32_t)SWAP_PRODUCT_ID >> 24),
		(uint8_t)((uint32_t)SWAP_PRODUCT_ID >> 16),
		(uint8_t)((uint32_t)SWAP_PRODUCT_ID >> 8),
		(uint8_t)(SWAP_PRODUCT_ID)
	};

	regProductCode.setData(arrProductCode);


	uint8_t arrHwVersion[4] = {
		(uint8_t)((uint32_t)HARDWARE_VERSION >> 24),
		(uint8_t)((uint32_t)HARDWARE_VERSION >> 16),
		(uint8_t)((uint32_t)HARDWARE_VERSION >> 8),
		(uint8_t)(HARDWARE_VERSION)
	};

	regHwVersion.setData(arrHwVersion);

	uint8_t arrFwVersion[4] = {
		(uint8_t)((uint32_t)FIRMWARE_VERSION >> 24),
		(uint8_t)((uint32_t)FIRMWARE_VERSION >> 16),
		(uint8_t)((uint32_t)FIRMWARE_VERSION >> 8),
		(uint8_t)(FIRMWARE_VERSION)
	};

	regFwVersion.setData(arrFwVersion);
};


void CAppPanstamp::radioISR(void)
{
	if (panstamp.radio.rfState == RFSTATE_RX)
	{
		static CCPACKET ccPacket;

		// Any packet waiting to be read?
		if (panstamp.radio.receiveData(&ccPacket) > 0)
		{
			// Is CRC OK?
			//if (ccPacket.crc_ok)
			{
				if (panstamp.m_ccPacketReceived != nullptr)
				panstamp.m_ccPacketReceived(&ccPacket);
			}
		}
	}
}

void CAppPanstamp::attachInterrupt(void (*funct)(CCPACKET*))
{
	m_ccPacketReceived = funct;
}

/*virtual*/ void CAppPanstamp::Init()
{
}

uint8_t CAppPanstamp::getDefaultAddress()
{
	return rand();
}

bool CAppPanstamp::InitRadio()
{
	SetupIds();

	HAL::IO::Configure(HAL::IO::D4, HAL::IO::InputPullUp);

	if (!radio.init(FREQUENCY, 0))
		return false;

	if (!swap.init())
		return false;

	// Attach callback function for GDO0 (INT0)
	HAL::INT::Attach(HAL::IO::D4, radioISR);

	HAL_TIME_DelayUs(50);

	// Enter RX state
	radio.setRxState();

	return true;
}

/*virtual*/ void CAppPanstamp::Loop()
{
}

void CAppPanstamp::randomDelay(int nMsMin, int nMsMax)
{
	// TODO!
	uint16_t postpone = 100 + (rand() & 511);

	// wait 100 .. 600ms to prevent traffic conflicts
	for (; postpone--; )
		HAL_TIME_DelayMs(1);
}
#if 0


#include "panstamp.h"
#include "../hal.h"

//HAL::IO::Read(HAL::IO::D4)
#define enableIRQ_GDO0()          HAL::INT::Attach(HAL::IO::D4, radioISR); // ::attachInterrupt(0, radioISR, FALLING);
#define disableIRQ_GDO0()         HAL::INT::Attach(HAL::IO::D4, nullptr); //::detachInterrupt(0);

CPanstamp panstamp;

/**
* radioISR
*
* Radio interrupt routine
*/
void radioISR(void)
{
	// Disable interrupt
	//disableIRQ_GDO0();
	if (panstamp.radio.rfState == RFSTATE_RX)
	{
		static CCPACKET ccPacket;

		// Any packet waiting to be read?
		if (panstamp.radio.receiveData(&ccPacket) > 0)
		{
			// Is CRC OK?
			//if (ccPacket.crc_ok)
			{
				if (panstamp.ccPacketReceived != nullptr)
				panstamp.ccPacketReceived(&ccPacket);
			}
		}
	}
	// Enable interrupt
	//enableIRQ_GDO0();
}

void CPanstamp::reset()
{
	//wdt_disable();
	//wdt_enable(WDTO_15MS);
	//while (1) {}
	//Serial.begin(9600);
	//while (1)
	//    Serial.print("Reboot!\n");
}

void CPanstamp::goToWirelessBoot()
{
	
}

void CPanstamp::attachInterrupt(void (*funct)(CCPACKET*))
{
	ccPacketReceived = funct;
}


//attachInterrupt(0, cc1101signalsInterrupt, FALLING);

bool CPanstamp::init(uint8_t freq, uint8_t mode)
{
	// TODO: srand!
	//srand(analogRead(0) ^ OSCCAL);
	// Calibrate internal RC oscillator
	//  rcOscCalibrate();

	// Setup CC1101
	if ( !radio.init(freq, mode) )
		return false;

	HAL_TIME_DelayUs(50);

	// Enter RX state
	radio.setRxState();

	// Attach callback function for GDO0 (INT0)
	HAL::IO::Configure(HAL::IO::D4, HAL::IO::InputPullUp);
	enableIRQ_GDO0();

	// Default values
	//  state = RXON;
	return true;
}

void CPanstamp::sleepSec(int n)
{
	if ( n < 0 || n > 180 )
		n = 5;

	//Serial.print("Sleeping for ");
	//Serial.print(n);
	//Serial.print(" seconds...\n");

	while (n--)
		HAL_TIME_DelayMs(1000);
}

uint16_t CPanstamp::getRand(void)
{
	// todo: init, or custom PRNG
	return rand();
}



#endif