#include "serial.h"
#include "../hal.h"

CSerial CSerial::m_Instance;

  void CSerial::print(char ch)
  {	  
	  if ( HAL::COM::Ready() )
		HAL::COM::Put(ch);
  }
  
  void CSerial::print(int num, EFormat eFormat)
  {
		uint8_t i = 0;
	  char strNum[8] = {};
		  
	if ( num <= 0 )
	{
		print('0');
		return;
	}
	
	if (eFormat == CSerial::DEC)  
	{
		while (num > 0)
		{
			strNum[i++] = '0' + (num % 10);
			num /= 10;
		}		
		while (i--)
			print(strNum[i]);
	}
	if (eFormat == CSerial::HEX)
	{
		while (num > 0)
		{
			strNum[i++] = "0123456789abcdef"[num % 16];
			num /= 16;
		}
		while (i--)
			print(strNum[i]);
	}
  }
  
  void CSerial::print(char* msg)
  {	  
	  while ( *msg )
		print(*msg++);	  
  }
  
  void CSerial::print(const char* msg)
  {
	  while ( *msg )
		print(*msg++);
  }
  
  uint8_t CSerial::available()
  {
	  return HAL::COM::Ready() && HAL::COM::Available();	  
  }
  
  uint8_t CSerial::read()
  {
	  return HAL::COM::Get();
  }

