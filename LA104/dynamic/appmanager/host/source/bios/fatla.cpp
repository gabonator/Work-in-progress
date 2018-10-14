#include "Bios.h"
#include "fatla/FAT12.h"

/*
      EOk,
      EDiskError,
      EIntError,
      ENoFile,
      ENoPath,
      EDiskFull

u8   ReadFileSec(u8 *Buffer, u16 *Cluster);
u8   ReadDiskData(u8 *pBuffer, u32 ReadAddr, u16 Lenght);
u8   NextCluster(u16 *Cluster);
u8   ProgFileSec(u8 *Buffer, u16 *Cluster);
u8   ProgDiskPage(u8 *Buffer, u32 ProgAddr);
u8   SeekBlank(u8 *Buffer, u16 *Cluster);
u8   SetCluster(u8 *Buffer, u16 *Cluster);
u8   OpenFileRd(u8 *Buffer, u8 *FileName, u16 *Cluster, u32 *pDirAddr);
u8   OpenFileWr(u8 *Buffer, u8 *FileName, u16 *Cluster, u32 *pDirAddr);
u8   CloseFile(u8 *Buffer, u32 Lenght, u16 *Cluster, u32 *pDirAddr);
void ExtFlash_PageWrite(u8 *pBuffer, u32 WriteAddr, u8 Mode);
int  Init_Fat_Value(void);

*/

namespace BIOS
{
  namespace FAT 
  {
    uint8_t gSharedBuffer[SectorSize];
    u16 pCluster[3];
    u32 pDirAddr[1];

    PVOID GetSharedBuffer()
    {
      return gSharedBuffer;
    }

    EResult BIOS::FAT::Init()
    {
      return BIOS::FAT::EOk;
    }

    EResult Open(const char* strName, ui8 nIoMode)
    {
//    USB_Connect(DISABLE);
      if ( nIoMode == BIOS::DSK::IoWrite )
      {
        if (OpenFileWr(gSharedBuffer, strName, pCluster, pDirAddr) == OK) 
          return EOk;
      }
      if ( nIoMode == BIOS::DSK::IoRead )
      {
        if (OpenFileRd(gSharedBuffer, strName, pCluster, pDirAddr) == OK) 
          return EOk;
      }
      return EDiskError;
    }

    EResult BIOS::FAT::Read(ui8* pSectorData)
    {
      if (ReadFileSec(pSectorData, pCluster) == OK)
        return EOk;
      return EDiskError;
    }

    EResult BIOS::FAT::Write(ui8* pSectorData)
    {
      if (ProgFileSec(pSectorData, pCluster) == OK)
        return EOk;
      return EDiskError;
    }

    EResult BIOS::FAT::Close(int nSize /*= -1*/)
    {
      if (CloseFile(gSharedBuffer, nSize, pCluster, pDirAddr) == OK)
        return EOk; 
      return EDiskError;
    }

    BIOS::FAT::EResult BIOS::FAT::OpenDir(char* strPath)
    {
    	FRESULT r = f_opendir(&g_directory, (char*)strPath);
    	return Result(r);
    }

    BIOS::FAT::EResult BIOS::FAT::FindNext(TFindFile* pFile)
    {
    	FILINFO* pFileInfo = (FILINFO*)pFile;

    	FRESULT r = f_readdir(&g_directory, pFileInfo);
    	if ( pFileInfo->fname[0] == 0)
    		return BIOS::FAT::ENoFile;

    	return Result(r);	
    } 

    ui32 BIOS::FAT::GetFileSize()
    {
    	return g_file.fsize;
    }

    BIOS::FAT::EResult BIOS::FAT::Seek(ui32 lOffset)
    {
    	FRESULT r = f_lseek(&g_file, lOffset);
    	return Result(r);
    }

  }
}