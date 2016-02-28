#pragma once
#include "../common.h"
#include "../swap/cc1101.h"
#include "../swap/swap.h"

#define panstamp CPanstamp::m_Panstamp

class CPanstamp
{
public:
	static CPanstamp m_Panstamp;
	CC1101 m_radio;
	SWAP m_swap;

private:
	void (*m_ccPacketReceived)(CCPACKET *packet);

public:
	virtual void Init();
	virtual void Loop();

	void SetupIds();
	uint8_t getDefaultAddress();
	bool InitRadio();
	void randomDelay(int nMsMin, int nMsMax);
	void setAddressCheck(bool bEnable);
	uint8_t sendPacket(CCPACKET& packet);
		
// obsolete:
	void reset() {}
	void goToWirelessBoot() {}
	
public:
	static void radioISR(void);
	void attachInterrupt(void (*funct)(CCPACKET*));
};
