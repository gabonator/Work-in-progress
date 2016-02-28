#include "dummysender.h"
#include "../swap/swap.h"

const bool updateUserValue(REGISTER* pRegister);

char strIdentify[] = "l.valky.eu/e";
REGISTER regIdentify((byte*)strIdentify, sizeof(strIdentify)-1, NULL, NULL, REGISTER::ReadOnly);

byte arrUser[4] = {'0', '0', '0', '0'};
REGISTER regUser(arrUser, sizeof(arrUser), &updateUserValue, NULL, REGISTER::Public);

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
  m_nLastSend = 0;
}

void CAppSender::OnSecond()
{
	regUser.updateData()->getStatusPacket()->prepare()->send();
}

/*virtual*/ void CAppSender::Init() 
{
}

/*virtual*/ void CAppSender::Loop()
{
  uint32_t nTick = HAL::TIME::GetTick();

  if ( m_nLastSend == 0 )
    m_nLastSend = nTick;

  if ( nTick - m_nLastSend > Interval )
  {
    m_nLastSend = nTick;
    OnSecond();
  }
}
