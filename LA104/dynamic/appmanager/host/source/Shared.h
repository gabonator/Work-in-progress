uint32_t GetProcAddress(char* symbol)
{
  if (strncmp(symbol, "_ZN4BIOS", 8) != 0)
    return 0;
  symbol += 9;

  if (strcmp(symbol, "DBG5PrintEPKcz") == 0)
    return (uint32_t)BIOS::DBG::Print;
  if (strcmp(symbol, "FAT11GetFileSizeEv") == 0)
    return (uint32_t)BIOS::FAT::GetFileSize;
  if (strcmp(symbol, "FAT15GetSharedBufferEv") == 0)
    return (uint32_t)BIOS::FAT::GetSharedBuffer; 
  if (strcmp(symbol, "FAT4InitEv") == 0)
    return (uint32_t)BIOS::FAT::Init; 
  if (strcmp(symbol, "FAT4OpenEPKch") == 0)
    return (uint32_t)BIOS::FAT::Open; 
  if (strcmp(symbol, "FAT4ReadEPh") == 0)
    return (uint32_t)BIOS::FAT::Read; 
  if (strcmp(symbol, "FAT4SeekEm") == 0)
    return (uint32_t)BIOS::FAT::Seek; 
  if (strcmp(symbol, "FAT5CloseEi") == 0)
    return (uint32_t)static_cast<BIOS::FAT::EResult(*)(int)>(BIOS::FAT::Close); 
  if (strcmp(symbol, "FAT5CloseEv") == 0)
    return (uint32_t)static_cast<BIOS::FAT::EResult(*)(void)>(BIOS::FAT::Close); 
/*
  if (strcmp(symbol, "FAT5WriteEPh") == 0)
    return (uint32_t)BIOS::FAT::Write; 
  if (strcmp(symbol, "FAT7OpenDirEPc") == 0)
    return (uint32_t)BIOS::FAT::OpenDir; 
  if (strcmp(symbol, "FAT8FindNextEPNS0_9TFindFileE") == 0)
    return (uint32_t)BIOS::FAT::FindNext; 
  if (strcmp(symbol, "LCD10BufferPushEt") == 0)
    return (uint32_t)BIOS::LCD::BufferPush; 
  if (strcmp(symbol, "LCD11BufferBeginERK5CRecth") == 0)
    return (uint32_t)BIOS::LCD::BufferBegin; 
  if (strcmp(symbol, "LCD3BarERK5CRectt") == 0)
    return (uint32_t)BIOS::LCD::Bar; 
  if (strcmp(symbol, "LCD3BarEiiiit") == 0)
    return (uint32_t)BIOS::LCD::Bar; 
  if (strcmp(symbol, "LCD5ClearEt") == 0)
    return (uint32_t)BIOS::LCD::Clear; 
  if (strcmp(symbol, "LCD5PrintEiittPKc") == 0)
    return (uint32_t)BIOS::LCD::Print; 
  if (strcmp(symbol, "LCD5PrintEiittPc") == 0)
    return (uint32_t)BIOS::LCD::Print; 
  if (strcmp(symbol, "LCD6ShadowEiiiij") == 0)
    return (uint32_t)BIOS::LCD::Shadow; 
  if (strcmp(symbol, "LCD7PatternEiiiiPKti") == 0)
    return (uint32_t)BIOS::LCD::Pattern; 
  if (strcmp(symbol, "LCD8PutPixelERK6CPointt") == 0)
    return (uint32_t)BIOS::LCD::PutPixel; 
  if (strcmp(symbol, "LCD8PutPixelEiit") == 0)
    return (uint32_t)BIOS::LCD::PutPixel; 
  if (strcmp(symbol, "LCD9BufferEndEv") == 0)
    return (uint32_t)BIOS::LCD::BufferEnd; 
  if (strcmp(symbol, "LCD9RoundRectERK5CRectt") == 0)
    return (uint32_t)BIOS::LCD::RoundRect; 
  if (strcmp(symbol, "LCD9RoundRectEiiiit") == 0)
    return (uint32_t)BIOS::LCD::RoundRect; 
  if (strcmp(symbol, "SYS4BeepEi") == 0)
    return (uint32_t)BIOS::SYS::Beep; 
  if (strcmp(symbol, "SYS7DelayMsEi") == 0)
    return (uint32_t)BIOS::SYS::DelayMs; 
  if (strcmp(symbol, "SYS7ExecuteEm") == 0)
    return (uint32_t)BIOS::SYS::Execute; 
  if (strcmp(symbol, "SYS7GetTickEv") == 0)
    return (uint32_t)BIOS::SYS::GetTick; 
  if (strcmp(symbol, "MEMORY11LinearStartEv") == 0)
    return (uint32_t)BIOS::MEMORY::LinearStart; 
  if (strcmp(symbol, "MEMORY12LinearFinishEv") == 0)
    return (uint32_t)BIOS::MEMORY::LinearFinish; 
  if (strcmp(symbol, "MEMORY::LinearProgramEmPhi") == 0)
    return (uint32_t)BIOS::MEMORY::LinearProgram; 
  if (strcmp(symbol, "MEMORY::GetSharedBufferEv") == 0)
    return (uint32_t)BIOS::MEMORY::GetSharedBuffer; 
*/
  return 0;
}
/*
000008bc T _ZN4BIOS3DBG5PrintEPKcz
000008f0 T _ZN4BIOS3FAT11GetFileSizeEv
000008d0 T _ZN4BIOS3FAT15GetSharedBufferEv
000008d4 T _ZN4BIOS3FAT4InitEv
000008d8 T _ZN4BIOS3FAT4OpenEPKch
000008dc T _ZN4BIOS3FAT4ReadEPh
000008e4 T _ZN4BIOS3FAT4SeekEm
000008e8 T _ZN4BIOS3FAT5CloseEi
000008ec T _ZN4BIOS3FAT5CloseEv
000008e0 T _ZN4BIOS3FAT5WriteEPh
000008f4 T _ZN4BIOS3FAT7OpenDirEPc
000008f8 T _ZN4BIOS3FAT8FindNextEPNS0_9TFindFileE
000008b6 T _ZN4BIOS3LCD10BufferPushEt
000008b4 T _ZN4BIOS3LCD11BufferBeginERK5CRecth
000008ac T _ZN4BIOS3LCD3BarERK5CRectt
000008aa T _ZN4BIOS3LCD3BarEiiiit
0000089c T _ZN4BIOS3LCD5ClearEt
000008a2 T _ZN4BIOS3LCD5PrintEiittPKc
0000089e T _ZN4BIOS3LCD5PrintEiittPc
000008b2 T _ZN4BIOS3LCD6ShadowEiiiij
000008ba T _ZN4BIOS3LCD7PatternEiiiiPKti
000008a8 T _ZN4BIOS3LCD8PutPixelERK6CPointt
000008a6 T _ZN4BIOS3LCD8PutPixelEiit
000008b8 T _ZN4BIOS3LCD9BufferEndEv
000008b0 T _ZN4BIOS3LCD9RoundRectERK5CRectt
000008ae T _ZN4BIOS3LCD9RoundRectEiiiit
00000898 T _ZN4BIOS3SYS4BeepEi
0000089a T _ZN4BIOS3SYS7DelayMsEi
00000894 T _ZN4BIOS3SYS7ExecuteEm
00000890 T _ZN4BIOS3SYS7GetTickEv
000008c6 T _ZN4BIOS6MEMORY11LinearStartEv
000008c8 T _ZN4BIOS6MEMORY12LinearFinishEv
000008cc T _ZN4BIOS6MEMORY13LinearProgramEmPhi
000008c2 T _ZN4BIOS6MEMORY15GetSharedBufferEv
*/