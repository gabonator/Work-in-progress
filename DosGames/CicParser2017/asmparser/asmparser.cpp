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

unsigned char data[1024*1024/2];
//unsigned char video[1024*1024];

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
CMachine m;

void VideoUpdate()
{
	videoOutput.Tick(m.m_pVideo);
}

int main(int argc, char* argv[])
{
	CSourceParser sp;
//	sp.Parse("C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\devel\\goose_code.asm");
	//sp.Parse("C:\\Data\\Devel\\VC\\catdec_xen\\catdec\\goose_vx\\goose_code.asm");
	//sp.Parse("C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsXenon\\asm\\xenon2a.asm");
	//sp.Parse("C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\AlleyCat\\Source\\cat_code.asm");
	//sp.Save("cat.cache");
	sp.Load("cat.cache");

	sp.Save("goose.cache");
	sp.Load("goose.cache");


	m.m_arrCode = sp.m_arrCode;
	m.m_arrSource = sp.m_arrSource;

	FILE* f;
	//fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\data", "rb");
	//fread(data, 38244, 1, f); 

	fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\AlleyCat\\Converted\\datasegment", "rb");
	fread(data, 28976, 1, f);
	fclose(f);

	// TODO: optimize exit condition sub_CF
//	vector<shared_ptr<CInstruction>> arrCode = m.GetSubCode(CLabel("sub_103"));
	//vector<shared_ptr<CInstruction>> arrCode = m.GetSubCode(CLabel("sub_1AD"));
	//vector<shared_ptr<CInstruction>> arrCode = m.GetSubCode(CLabel("sub_1C0"));
	
	
	//vector<shared_ptr<CInstruction>> arrCode = m.GetSubCode(CLabel("start"));
	//CCExport e;
	//e.Optimize(arrCode);
	//e.DumpProgram(arrCode);
	//return 0;

	videoOutput.Init();
	m.Eval(sp.m_arrCode, sp.m_arrSource);
	return 0;
}

