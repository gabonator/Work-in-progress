// Synology surveillance station license key generator
//
// update address of GenerateKey symbol in libsynoss_1.so:
//   nm -D /var/packages/SurveillanceStation/target/lib/libsynoss_1.so | grep GenerateKey
//
// install gcc on synology machine:
//   ipkg install crosstool-native optware-devel
//
// compile on synology machine by calling:
//   g++ synogen.cpp -ldl -o synogen
// 
// Do not misuse this tool, use it only for testing purposes and then delete the 
// key from your machine.
//
// How does this tool work? After entering license key in Key manager, disk station calls 
// function VerifyKey from libsynoss_1.so to validate new key. Every key is composed from 
// 4 bits determining how many cameras will be activated (1, 4, 8), unique 32 bit key and 
// remaining part of the sequence is just SHA1 hash of the previous part. Binary value of
// this block is encoded into human readable form using this alphabet: 'BCDFGHJKMPQRTVWXY2346789'
// Unique 32 bit number is in range <15000000, 20000000> for normal license or in range
// <20000000, 20100000> for trial key. Every license is also sent with your diskstation
// serial number to synology servers (synosurveillance.synology.com) to verify whether someone 
// is not already using this key.
//
// Some engineer at synology forgot to remove function GenerateKey from the libsynoss_1.so library 
// which takes two numbers (camera count and unique id) and generates the string with license key.
// This is pretty funny fail from synology side, so instead of reverse engineering all the
// bit manipulation done in VerifyKey function, we just call GenerateKey(8, random number, strCode)
// to get valid activation code. The GenerateKey function is not exported and cannot be loaded 
// using dlsym, but due to benefits of ELF shared objects and wrong linker configuration
// we can determine the function's offset by calling nm -D command. This code was tested on
// PowerPc based diskstations, but I have found function with the same name also on x86 synology 
// machine.

#include <iostream>
#include <string>
#include <dlfcn.h>
#include <link.h>

const int nGenerateKeyRelativeAddr = 0x537dc;

int main()
{
  std::cout << "Synology license key generator by valky.eu" << std::endl;

  std::string arr[] = {
  "libpq.so.5",
  "libstdc++.so.5",
  "libsynosdk.so.4",
  "libcrypt.so.1",
  "libicui18n.so.22",
  "libicuuc.so.22",
  "libicudata.so.22",
  "libxml2.so.2",
  "libm.so.6",
  "libdl.so.2",
  "libpam.so.0",
  "libpthread.so.0",
  "librt.so.1",
  "libjson.so",

  "libsynobandwidth.so",
  "libsynowimax.so",
  "libcurl.so.4",

  "libdsm.so.4",
  "libsynoutils.so.1",
  "libsynoddnsclient.so",
  "libsynowimax.so",
  "libbackup.so",
  "libsynoacl.so",
  "libcurl.so.4",
  "libsynoldap.so.4",
  "libcrypto.so.1.0.0",
  "libssl.so.1.0.0",
  "libsynosmtp.so",
  "libjpeg.so.62",
  "libfindhost.so.1",
  "libncurses.so.5",
  "libsqlite3.so.0",
  "libsynodb.so",
  "/var/packages/SurveillanceStation/target/lib/libsynoss_1.so"
  };


  typedef void (*TGenerateKey)(int, int, std::string &);
  TGenerateKey GenerateKey;

  void* handle;

  for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
  {
    std::cout << "Loading library=" << arr[i] << "...";

    handle = dlopen (arr[i].c_str(), RTLD_NOW | RTLD_GLOBAL);

    if (!handle) 
    {
      std::cout << " Error" << std::endl;
      fputs (dlerror(), stderr);
      return 1;
    }
    std::cout << " Ok." << std::endl;
  }

  struct link_map *lm = (struct link_map*) handle;
  GenerateKey = (TGenerateKey)(lm->l_addr + nGenerateKeyRelativeAddr);

  for (int i=0; i<100; i++)
  {
    int nCameras = 8;
    int nKeyMin = 15000000;
    int nKeyMax = 20000000;
    int nKeyMaxTrial = 20100000;
    int nKey = nKeyMin + (rand() & 0xffff);

    std::string str;
    (*GenerateKey)(nKey, nCameras, str);
    std::cout << " Key = " << str << std::endl;
  }

  return 0;
}
 
