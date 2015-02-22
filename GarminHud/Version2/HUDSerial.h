#if !defined(HUDSERIAL_H__INCLUDED_)
#define HUDSERIAL_H__INCLUDED_

#include "HUDInterface.h"

class HUDSerial :
	public HUDInterface
{
protected:
	HANDLE m_hCommPort;
	virtual int SendPacket(const unsigned char* pBuf, int nLen);
public:
	HUDSerial() : HUDInterface(), m_hCommPort(INVALID_HANDLE_VALUE) {};
	bool Init(const char * port, int baud);
	virtual ~HUDSerial();
};

#endif