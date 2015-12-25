#pragma once
#include <string>
//#include "stdafx.h"

class CNet 
{
public:
	typedef void (*THandler)(std::string);

public:
	virtual void Do() = 0;
	virtual void Send(std::string str) = 0;
	virtual void SetReceiveHandler(THandler handler) = 0;
};
