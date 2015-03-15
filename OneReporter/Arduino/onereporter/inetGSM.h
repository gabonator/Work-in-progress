#ifndef _INETGSM_H_
#define _INETGSM_H_

#define BUFFERSIZE 1

#include "SIM900.h"

class InetGSM
{
  private:
    char _buffer[BUFFERSIZE];
    
  public:
    int httpGET(const char* server, int port, const char* path, char* result, int resultlength);
    int httpPOST(const char* server, int port, const char* path, const char* parameters, char* result, int resultlength);

		int httpOpen(const char* server, int port);
		int httpClose();

    int attachGPRS(char* domain, char* dom1, char* dom2);
    int dettachGPRS();
    int connectTCP(const char* server, int port);
    int disconnectTCP();
    int connectTCPServer(int port);
    boolean connectedClient();

  boolean ReadNonEmptyLine(char* strOut, int nMaxLen, int nMaxTimeout);
  boolean ReadLine(char* strOut, int nMaxLen, int nMaxTimeout);

};

#endif
