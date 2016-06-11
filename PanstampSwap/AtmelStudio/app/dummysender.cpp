#include "dummysender.h"
#include "leds.h"
#include "../panstamp/panstamp.h"
#include "../swap/nvolat.h"
#include "../swap/register.h"

extern REGISTER regTxInterval;

const bool updateUserValue(REGISTER* pRegister);
const bool setLedValue(REGISTER* pRegister, uint8_t *v);

char strIdentify[] = "l.valky.eu/e";
REGISTER regIdentify((byte*)strIdentify, sizeof(strIdentify)-1, NULL, NULL, REGISTER::ReadOnly);

byte arrUser[4] = {'0', '0', '0', '0'};
REGISTER regUser(arrUser, sizeof(arrUser), &updateUserValue, NULL, REGISTER::Public);

byte dtTargetAddr[1] = {0};
REGISTER regTargetAddr(dtTargetAddr, sizeof(dtTargetAddr), NULL, NULL, REGISTER::Private, SWDTYPE_INTEGER, NVOLAT_FIRST_CUSTOM+0);

byte dtMediateAddr[1] = {0};
REGISTER regMediateAddr(dtMediateAddr, sizeof(dtMediateAddr), NULL, NULL, REGISTER::Private, SWDTYPE_INTEGER, NVOLAT_FIRST_CUSTOM+1);

byte arrButtons[1] = {};
REGISTER regButtons(arrButtons, sizeof(arrButtons), NULL, NULL, REGISTER::Public);

byte arrLeds[1] = {};
REGISTER regLeds(arrLeds, sizeof(arrLeds), NULL, &setLedValue, REGISTER::Public);

byte dtSendLedAddr[1] = {0};
REGISTER regSendLedAddr(dtSendLedAddr, sizeof(dtSendLedAddr), NULL, NULL, REGISTER::Private, SWDTYPE_INTEGER, NVOLAT_FIRST_CUSTOM+2);

const bool setLedValue(REGISTER* pRegister, uint8_t *v)
{
	CAppLeds::Show(v[0]);
	return true;
}

const bool updateUserValue(REGISTER* pRegister)
{
  if ( pRegister->value[0]++ >= '9' )
  {
    pRegister->value[0] = '0';

    if ( pRegister->value[1]++ >= '9' )
    {
      pRegister->value[1] = '0';

      if ( pRegister->value[2]++ >= '9' )
      {
        pRegister->value[2] = '0';

        if ( pRegister->value[3]++ >= '9' )
        {
          pRegister->value[3] = '0';
        }
      }
    }
  }

  return true;
}

CAppSender::CAppSender()                                                 
{
  m_nLastSecond = 0;
  m_nLastSend = 0;
  m_nInhibit = 0;
}

void CAppSender::OnSecond()
{
	HAL::IO::Write(HAL::IO::A, HAL::IO::Read(HAL::IO::A) ^ 1);
	HAL_TIME_DelayMs(1);	
	HAL::IO::Write(HAL::IO::A, HAL::IO::Read(HAL::IO::A) ^ 1);
}

void CAppSender::OnTimer()
{
	//static uint8_t nSendCount = 0;
	//CAppLeds::Show(nSendCount++);
	
	regUser.
		updateData()->
		getStatusPacket()->
		setDestAddr(regTargetAddr.value[0])->
		//mediate(regMediateAddr.value[0])->
		prepare()->
		sendAck();
		
}

/*virtual*/ void CAppSender::Init() 
{
}

/*virtual*/ void CAppSender::Loop()
{
	static uint8_t nLastButtons = 0;
	
	uint32_t nTick = HAL::TIME::GetTick();
	if ( nTick > m_nInhibit )
	{
		uint8_t nCurButtons = CAppLeds::GetButtons();
		if ( nCurButtons != nLastButtons )
		{
			nLastButtons = nCurButtons;
			if ( regSendLedAddr.value[0] != SWAP_BCAST_ADDR )
			{
				regLeds.value[0] = nCurButtons;
				
				bool bSendOk = regLeds.
					getCommandPacket()->
					setDestAddr(regSendLedAddr.value[0])->
					prepare()->
					sendAck();
					
				if (!bSendOk)
					Serial.print("Send failed!\r\n");
			} else 
			{
				regButtons.value[0] = nCurButtons;

				bool bSendOk = regButtons.
					getStatusPacket()->
					setDestAddr(regTargetAddr.value[0])->
					//mediate(regMediateAddr.value[0])->
					prepare()->
					sendAck();

				if (!bSendOk)
					Serial.print("Send failed!\r\n");
			}

			m_nInhibit = nTick + 50; // 50 ms debounce			
		}
	}
	
	// second
	if ( m_nLastSecond == 0 )	
		m_nLastSecond = nTick;

	if ( nTick - m_nLastSecond > 1000 )
	{
		m_nLastSecond = nTick;
		OnSecond();
	}
		
	// send interval
	if ( panstamp.m_swap.txInterval == 0 )
		return;

	if ( m_nLastSend == 0 )
		m_nLastSend = nTick;

	if ( nTick - m_nLastSend > panstamp.m_swap.txInterval*1000 )
	{
		m_nLastSend = nTick;
		OnTimer();
	}
}
