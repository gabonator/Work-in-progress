// asmparser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <regex>
#include <vector>
#include <map>
#include <typeinfo>
#include <sstream>
#include <iomanip>
#include <functional>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;

#define CheckEnum2(s, e) if (str==s) return e;
#define CheckEnum(e) if (str==#e) return e;

//typedef uint32_t DWORD;
//typedef uint16_t WORD;
//typedef uint8_t BYTE;

unsigned char data[1024*1024];
unsigned char video[1024*1024];

#include "utils.h"

std::map<string, regex> CUtils::m_mapCache;

#include "serializer.h"

#include "value.h"
#include "label.h"

class CMachine;

#include "instructions.h"
#include "matchers.h"

// Matchers
#include "parser.h"
#include "dos.h"
#include "ega.h"
#include "machine.h"
#include "dos.cpp"
#include "emulator.cpp"

// Export to C
#include "cvalue.h"
#include "cinstructions.h"
#include "cexport.h"

// Emulator
#include "video.h"

CVideo videoOutput;

void VideoUpdate()
{
	videoOutput.Tick();
}

int main(int argc, char* argv[])
{
	CSourceParser sp;
	//sp.Parse("C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\devel\\goose_code.asm");
	//sp.Save("cache");
	//return 0;
	sp.Load("cache");

	CMachine m;
	m.m_arrCode = sp.m_arrCode;
	m.m_arrSource = sp.m_arrSource;

	vector<shared_ptr<CInstruction>> arrCode = m.GetSubCode(CLabel("start"));
	CCExport e;
	e.Optimize(arrCode);
	return 0;

	videoOutput.Init();
	m.Eval(sp.m_arrCode, sp.m_arrSource);
	return 0;
}

