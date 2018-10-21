
uint32_t GetProcAddress(char* symbol)
{
  if (strncmp(symbol, "_ZN4BIOS", 8) != 0)
    return 0;
  symbol += 9;

  if (strcmp(symbol, "DBG5PrintEPKcz") == 0)
    return (uint32_t)static_cast<void(*)(char const*, ...)>(BIOS::DBG::Print); 
  if (strcmp(symbol, "FAT11GetFileSizeEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::FAT::GetFileSize); 
  if (strcmp(symbol, "FAT15GetSharedBufferEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::FAT::GetSharedBuffer); 
  if (strcmp(symbol, "FAT4InitEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::FAT::Init); 
  if (strcmp(symbol, "FAT4OpenEPKch") == 0)
    return (uint32_t)static_cast<void(*)(char const*, unsigned char)>(BIOS::FAT::Open); 
  if (strcmp(symbol, "FAT4ReadEPh") == 0)
    return (uint32_t)static_cast<void(*)(unsigned char*)>(BIOS::FAT::Read); 
  if (strcmp(symbol, "FAT4SeekEm") == 0)
    return (uint32_t)static_cast<void(*)(unsigned long)>(BIOS::FAT::Seek); 
  if (strcmp(symbol, "FAT5CloseEi") == 0)
    return (uint32_t)static_cast<void(*)(int)>(BIOS::FAT::Close); 
  if (strcmp(symbol, "FAT5CloseEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::FAT::Close); 
  if (strcmp(symbol, "FAT5WriteEPh") == 0)
    return (uint32_t)static_cast<void(*)(unsigned char*)>(BIOS::FAT::Write); 
  if (strcmp(symbol, "FAT7OpenDirEPc") == 0)
    return (uint32_t)static_cast<void(*)(char*)>(BIOS::FAT::OpenDir); 
  if (strcmp(symbol, "FAT8FindNextEPNS0_9TFindFileE") == 0)
    return (uint32_t)static_cast<void(*)(BIOS::FAT::TFindFile*)>(BIOS::FAT::FindNext); 
  if (strcmp(symbol, "LCD10BufferPushEt") == 0)
    return (uint32_t)static_cast<void(*)(unsigned short)>(BIOS::LCD::BufferPush); 
  if (strcmp(symbol, "LCD11BufferBeginERK5CRecth") == 0)
    return (uint32_t)static_cast<void(*)(CRect const&, unsigned char)>(BIOS::LCD::BufferBegin); 
  if (strcmp(symbol, "LCD3BarERK5CRectt") == 0)
    return (uint32_t)static_cast<void(*)(CRect const&, unsigned short)>(BIOS::LCD::Bar); 
  if (strcmp(symbol, "LCD3BarEiiiit") == 0)
    return (uint32_t)static_cast<void(*)(int, int, int, int, unsigned short)>(BIOS::LCD::Bar); 
  if (strcmp(symbol, "LCD5ClearEt") == 0)
    return (uint32_t)static_cast<void(*)(unsigned short)>(BIOS::LCD::Clear); 
  if (strcmp(symbol, "LCD5PrintEiittPKc") == 0)
    return (uint32_t)static_cast<void(*)(int, int, unsigned short, unsigned short, char const*)>(BIOS::LCD::Print); 
  if (strcmp(symbol, "LCD5PrintEiittPc") == 0)
    return (uint32_t)static_cast<void(*)(int, int, unsigned short, unsigned short, char*)>(BIOS::LCD::Print); 
  if (strcmp(symbol, "LCD6ShadowEiiiij") == 0)
    return (uint32_t)static_cast<void(*)(int, int, int, int, unsigned int)>(BIOS::LCD::Shadow); 
  if (strcmp(symbol, "LCD7PatternEiiiiPKti") == 0)
    return (uint32_t)static_cast<void(*)(int, int, int, int, unsigned short const*, int)>(BIOS::LCD::Pattern); 
  if (strcmp(symbol, "LCD8PutPixelERK6CPointt") == 0)
    return (uint32_t)static_cast<void(*)(CPoint const&, unsigned short)>(BIOS::LCD::PutPixel); 
  if (strcmp(symbol, "LCD8PutPixelEiit") == 0)
    return (uint32_t)static_cast<void(*)(int, int, unsigned short)>(BIOS::LCD::PutPixel); 
  if (strcmp(symbol, "LCD9BufferEndEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::LCD::BufferEnd); 
  if (strcmp(symbol, "LCD9RoundRectERK5CRectt") == 0)
    return (uint32_t)static_cast<void(*)(CRect const&, unsigned short)>(BIOS::LCD::RoundRect); 
  if (strcmp(symbol, "LCD9RoundRectEiiiit") == 0)
    return (uint32_t)static_cast<void(*)(int, int, int, int, unsigned short)>(BIOS::LCD::RoundRect); 
  if (strcmp(symbol, "SYS4BeepEi") == 0)
    return (uint32_t)static_cast<void(*)(int)>(BIOS::SYS::Beep); 
  if (strcmp(symbol, "SYS7DelayMsEi") == 0)
    return (uint32_t)static_cast<void(*)(int)>(BIOS::SYS::DelayMs); 
  if (strcmp(symbol, "SYS7ExecuteEm") == 0)
    return (uint32_t)static_cast<void(*)(unsigned long)>(BIOS::SYS::Execute); 
  if (strcmp(symbol, "SYS7GetTickEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::SYS::GetTick); 
  if (strcmp(symbol, "MEMORY11LinearStartEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::MEMORY::LinearStart); 
  if (strcmp(symbol, "MEMORY12LinearFinishEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::MEMORY::LinearFinish); 
  if (strcmp(symbol, "MEMORY13LinearProgramEmPhi") == 0)
    return (uint32_t)static_cast<void(*)(unsigned long, unsigned char*, int)>(BIOS::MEMORY::LinearProgram); 
  if (strcmp(symbol, "MEMORY15GetSharedBufferEv") == 0)
    return (uint32_t)static_cast<void(*)()>(BIOS::MEMORY::GetSharedBuffer); 
  return 0;
}

