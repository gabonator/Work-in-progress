#pragma once
#include "app.h"
#include "../swap/cc1101.h"
//#include "../swap/swap.h"

#define panstamp CAppPanstamp::m_appPanstamp

class CAppPanstamp : public CApp
{
public:
	static CAppPanstamp m_appPanstamp;
	CC1101 m_radio;

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
	uint8_t  sendPacket(CCPACKET& packet);
		
// obsolete:
	void reset() {}
	void goToWirelessBoot() {}
	
public:
	static void radioISR(void);
	void attachInterrupt(void (*funct)(CCPACKET*));
};
