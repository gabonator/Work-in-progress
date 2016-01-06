#pragma once
#include <string>
//#include "stdafx.h"

class CNet 
{
public:
  enum EConnectionState
  { 
    Connecting = 0,
    Open = 1,
    Closed = 2,
    Error = 3
  };
 
public:
	typedef void (*THandler)(std::string, PVOID data);

public:
	virtual EConnectionState GetState() = 0;
	virtual void Do() = 0;
	virtual void Send(std::string str) = 0;
	virtual void SetReceiveHandler(THandler handler, PVOID data) = 0;
	virtual std::string GetServerUrl() = 0;
};
