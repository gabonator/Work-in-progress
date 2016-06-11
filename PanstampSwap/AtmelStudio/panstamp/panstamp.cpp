#include "../panstamp/panstamp.h"
#include "../swap/swap.h"
#include "../swap/register.h"

/*static*/ CPanstamp CPanstamp::m_Panstamp;

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

void CPanstamp::SetupIds()
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


void CPanstamp::radioISR(void)
{
	CPanstamp *pThis = &panstamp;
	
	Serial.print('{');
	Serial.print(HAL::IO::Read(HAL::IO::D4) ? '1' : '0');

	if (pThis->m_radio.rfState == RFSTATE_RX)
	{
		static CCPACKET ccPacket;

		// Any packet waiting to be read?
		if (pThis->m_radio.receiveData(&ccPacket) > 0)
		{
			// Is CRC OK?
			//if (ccPacket.crc_ok)
			{
				if (pThis->m_ccPacketReceived != nullptr)
					pThis->m_ccPacketReceived(&ccPacket);
			}
		}
	}
	Serial.print(HAL::IO::Read(HAL::IO::D4) ? '1' : '0');
	Serial.print('}');	
}

void CPanstamp::attachInterrupt(void (*funct)(CCPACKET*))
{
	m_ccPacketReceived = funct;
}

/*virtual*/ void CPanstamp::Init()
{
}

uint16_t CPanstamp::getDefaultAddress()
{
	return HAL::SEC::GetRand();
}

bool CPanstamp::InitRadio()
{
	SetupIds();

	HAL::IO::Configure(HAL::IO::D4, HAL::IO::InputPullUp);

	if (!m_radio.init(FREQUENCY, 0))
		return false;

	if (!m_swap.init())
		return false;

	// Attach callback function for GDO0 (INT0)
	HAL::INT::Attach(HAL::IO::D4, radioISR);

	HAL_TIME_DelayUs(50);

	// Enter RX state
	m_radio.setRxState();

	return true;
}

/*virtual*/ void CPanstamp::Loop()
{
}

void CPanstamp::randomDelay(int nMsMin, int nMsMax)
{
	// TODO!
	uint16_t postpone = 100 + (HAL::SEC::GetRand() & 511);

	// wait 100 .. 600ms to prevent traffic conflicts
	for (; postpone--; )
		HAL_TIME_DelayMs(1);
}

uint8_t CPanstamp::sendPacket(CCPACKET& packet)
{		
	uint8_t i = SWAP_NB_TX_TRIES;
	uint8_t res;
	HAL::INT::Disable();

	while(!(res = m_radio.sendData(packet)) && i>1)
	{
		i--;
		HAL::INT::Enable();

		for ( uint8_t t = SWAP_TX_DELAY; t--; )
			HAL_TIME_DelayMs(1);                           // Delay before sending
		
		HAL::INT::Disable();
	}
		
	if ( !res )
	{
		panstamp.m_radio.setRxState();			
	}

	HAL::INT::Enable();
		
	return res;
}

void CPanstamp::setAddressCheck(bool bEnable)
{
	if ( bEnable )
		m_radio.writeReg(CC1101_PKTCTRL1, 0x06);
	else
		m_radio.writeReg(CC1101_PKTCTRL1, 0x04);
}
