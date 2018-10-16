#include "Bios.h"

extern "C" volatile uint32_t gCounter;
extern "C" volatile uint32_t Dly_mS;

extern "C" 
void Delay_mS(uint32_t mS)
{
    Dly_mS = mS;
    while(Dly_mS)
    {};
}


void BIOS::SYS::DelayMs(int intervalMs)
{
  Delay_mS(intervalMs);
  // TODO: implement
}

uint32_t BIOS::SYS::GetTick()
{
  return gCounter;
}

int BIOS::SYS::Execute(uint32_t addr)
{
  return 0;
}

void BIOS::SYS::Beep(int intervalMs)
{
}
