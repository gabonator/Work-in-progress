#include "Bios.h"

extern "C" volatile uint32_t gCounter;

void BIOS::SYS::DelayMs(int intervalMs)
{
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
