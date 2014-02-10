// asmemu.cpp : Defines the entry point for the console application.
//
#include <Windows.h>
#include "trex.h"
#include <string>
#include <vector>

//#undef _ASSERT
//#define _ASSERT(x) if (!(x)) { printf("prev(%s) - test(%s)\n", _strPrevLine.c_str(), strLine.c_str() ); }
#define ReportUnknownCondition() printf("Unknown condition - line %d\n%s\n%s\n", nLine, _strPrevLine.c_str(), strLine.c_str());
using namespace std;

bool match(string pattern, string test, vector<std::string>* pArrMatches = NULL)
{
	const TRexChar *err = NULL;
	TRex *rex = trex_compile(pattern.c_str(), &err);
	if ( !rex )
		return false;
	const TRexChar *begin,*end;
	if ( !trex_search(rex,test.c_str(),&begin,&end) )
		return false;
	int n = trex_getsubexpcount(rex);
	if ( n == 0 )
		return false;
	if ( !pArrMatches )
		return true;

	pArrMatches->clear();
	for (int i = 0; i < n; i++)
	{
		TRexMatch match;
		trex_getsubexp(rex,i,&match);
		pArrMatches->push_back(string(match.begin, match.begin+match.len));
	}
	return true;
}

string trim(string strLine)
{
	const char *b = strLine.c_str();
	const char *e = b + strlen(b);
	const char *cmt = strstr(b, ";");
	if ( cmt != NULL )
		e = cmt;

	while (b[0] == '\t' || b[0] == ' ')
		b++;
	while (e-b > 0 && (e[-1] == ' ' || e[-1] == '\t'))
		e--;
/*	
	vector<string> matches;
	if ( match("^[\\s]*([^\\s].*)[\\s]*;", strLine, &matches) )
		return matches[1];
	if ( match("^[\\s]*([^\\s].*)[\\s]*$", strLine, &matches) )
		return matches[1];
	return string();
	*/
	return string(b, e);
}
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

LONG toNumber(string s)
{
	_ASSERT( s.substr(0, 2) == "0x" );
	char *endp = NULL;
	LONG l = strtol(s.c_str(), &endp, 16);
	_ASSERT( endp == s.c_str() + s.length() );
	return l;
}

string toString(LONG l)
{
	char str[32];
	sprintf(str, "0x%X", l);
	return string(str);
}

string value(string key)
{
	vector<string> matches;
	string out = key;
	// decimal
	if ( match("^([0-9]*)$", key.c_str(), &matches) )
		return out;
	// hex
	if ( match("^([0-9A-F]+)h$", key.c_str(), &matches) )
	{
		out = string("0x") + matches[1];
		return out;
	}
	//byte ptr ds:44D0h
	if ( match("^cs:(.*)$", key.c_str(), &matches) )
		return matches[1];
	else if ( match("^seg\\s(.*)$", key.c_str(), &matches) )
		out = "0";
	else if ( match("^byte_data_(.*)\\+(.*)$", key.c_str(), &matches) )
		out = string("_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(value(matches[2]))) + "]";
		//out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^word_data_(.*)\\+(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(value(matches[2]))) + "]";
		//out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^byte_data_(.*)$", key.c_str(), &matches) )
		out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^byte_(.*)$", key.c_str(), &matches) )
		out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^word_data_(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[0x") + value(matches[1]) + string("]");
	else if ( match("^word_(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[0x") + value(matches[1]) + string("]");
	else if ( match("^es:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[es+") + value(matches[1]) + string("]");
	else if ( match("^ds:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[ds+") + value(matches[1]) + string("]");

	else if ( match("^cs:(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[cs+") + value(matches[1]) + string("]");
	else if ( match("^ds:(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[ds+") + value(matches[1]) + string("]");
	else if ( match("^es:(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[es+") + value(matches[1]) + string("]");

	else if ( match("^\\[(.*)\\+(.*)\\+(.*)\\]$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + matches[1] + string(" + ") + value(matches[2]) + string(" + ") + value(matches[3]) + ("]");
	else if ( match("^\\[(.*)\\+(.*)\\]$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + matches[1] + string(" + ") + value(matches[2]) + ("]");
	else if ( match("^\\[(.*)\\]$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + matches[1] + ("]");
	else if ( match("^word ptr (.*)$", key.c_str(), &matches) )
	{
		out = value(matches[1]);
		if ( out.find("*(WORD*)") == -1 )
			out = string("*(WORD*)&") + out;
		//out = string("*(WORD*)(") + value(matches[1]) + string(")");
	}
	else if ( match("^byte ptr (.*)$", key.c_str(), &matches) )
	{
		out = value(matches[1]);
		replace(out, "*(WORD*)&", "");
	}	
	if ( match("^offset\\s(.*)$", key.c_str(), &matches) )
		out = string("&") + value(matches[1]); 

	
	return out;
}

bool cmp16bit(string exp)
{
	if ( exp.find("*(WORD*)&") != -1 )
		return true;
	if ( exp.find("ax") != -1 )
		return true;
	if ( exp.find("bx") != -1 )
		return true;
	if ( exp.find("cx") != -1 )
		return true;
	if ( exp.find("dx") != -1 )
		return true;	
	return false;
}

int main(int argc, char* argv[])
{
	FILE* f = fopen("C:\\Data\\Work\\alley\\1\\cat_code.asm", "r");
	FILE* fo = fopen("C:\\Data\\Work\\alley\\1\\cat_code.cpp", "w");
	FILE* fh = fopen("C:\\Data\\Work\\alley\\1\\cat_code.h", "w");
	char line[1024] = {0};

	fprintf(fh, "#include \"asm.h\"\n");
	fprintf(fh, "\n");

	fprintf(fo, "#include \"cat_code.h\"\n");
	fprintf(fo, "\n");
	vector<string> matches;

	string lastcmp;
	string strPrevLine;
	string lastcmp2;
	bool inproc = false;
	bool outproc = false;
	int nLine = 0;
	while (!feof(f))
	{
		fgets(line, 1023, f);
		nLine++;
		if ( line[0] )
			line[strlen(line)-1] = 0;
		string strLine(line);

		//int nComment = strLine.find(";");
		//if ( nComment != -1 )
//			strLine = strLine.substr(0, nComment );
		strLine = trim(strLine);
		if (strLine.length() == 0)
			continue;

		//printf("%s\n", strLine.c_str());

		string _strPrevLine = strPrevLine;
		strPrevLine = strLine;
		string _lastcmp = lastcmp;
		lastcmp2 = lastcmp;
		lastcmp.clear();

		//inproc = true; strLine = "mov	es:24h,	bx";

		if ( match("^([\\w]*)[\\s]*proc near", strLine, &matches) )
		{
			replace(matches[1], "_code_", "_");
			if ( outproc )
			{
				outproc = false;
				fprintf(fo, "*/\n");
			}
			inproc = true;

			string procType = "void";
			if ( matches[1] == "sub_13D8" )
				procType = "BYTE";

			fprintf(fh, "%s %s();\n", procType.c_str(), matches[1].c_str());
			fprintf(fo, "%s %s()\n", procType.c_str(), matches[1].c_str());
			fprintf(fo, "{\n");

			if ( matches[1] == "sub_1A569" || matches[1] == "sub_1A86D" || matches[1] == "sub_1CDEF" || matches[1] == "sub_1D05B")
				fprintf(fo, "%s:\n", matches[1].c_str());

			if ( matches[1] == "sub_3E2" || matches[1] == "sub_394" || matches[1] == "sub_349" || matches[1] == "sub_2FE" || 
				matches[1] == "sub_3339" || matches[1] == "sub_363D" || matches[1] == "sub_5BBF")
				fprintf(fo, "%s:\n", matches[1].c_str());
			continue;
		} else
		if ( match("^([\\w]*)[\\s]*proc far", strLine, &matches) )
		{
			replace(matches[1], "_code_", "_");
			if ( outproc )
			{
				outproc = false;
				fprintf(fo, "*/\n");
			}
			inproc = true;
			fprintf(fh, "void %s();\n", matches[1].c_str());
			fprintf(fo, "void %s()\n", matches[1].c_str());
			fprintf(fo, "{\n");
			continue;
		} else
		if ( match("^([\\w]*)[\\s]*endp", strLine, &matches) )
		{
			inproc = false;
			fprintf(fo, "} //%s\n", matches[1].c_str());
			fprintf(fo, "\n");
			continue;
		}

		if ( !inproc )
		{
			if (!outproc)
				fprintf(fo, "/*\n");
			outproc = true;
		}
		if ( match("^(loc[\\w]*):", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			fprintf(fo, "%s:\n", matches[1].c_str());

			/*
			fprintf(fo, "  %s();\n", matches[1].c_str());
			fprintf(fo, "}\n");
			fprintf(fo, "\n");
			fprintf(fo, "void %s()\n", matches[1].c_str());
			fprintf(fo, "{\n");
			*/
		} else
		if ( match("^[\\s]*push[\\s]+([\\w]+)", strLine, &matches) )
		{
			fprintf(fo, "  _push(%s);\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*pop[\\s]+([\\w]+)", strLine, &matches) )
		{
			//lastcmp = matches[1];
			fprintf(fo, "  _pop(%s);\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*mul[\\s]+([\\w]+)", strLine, &matches) )
		{
			fprintf(fo, "  ax = (WORD)%s * (WORD)al;\n", matches[1].c_str());
		} else
		if ( match("^mov[\\s]+(.*),[\\s]*(.*)$", strLine, &matches) )
		{
			string target = value(matches[1]);
			string source = value(matches[2]);
			if ( match("^[abcd][hl]$", target) )
				replace(source, "*(WORD*)&", "");
			if ( match("^[abcd][hl]$", source) )
				replace(target, "*(WORD*)&", "");
			//lastcmp = _lastcmp;
			fprintf(fo, "  %s = %s;\n", target.c_str(), source.c_str());

			//printf("%s   ->   %s = %s;\n", strLine.c_str(), target.c_str(), source.c_str());
		} else
		if ( match("^call[\\s]+near[\\s]+ptr+(.*)$", strLine, &matches) )
		{
			replace(matches[1], "_code_", "_");
			fprintf(fo, "  %s();\n", matches[1].c_str());
		} else
		if ( match("^call[\\s]+(.*)$", strLine, &matches) )
		{
			replace(matches[1], "_code_", "_");
			if ( matches[1] == "sub_13D8" )
				lastcmp =  matches[1] + "()";
			fprintf(fo, "  %s();\n", matches[1].c_str());
		} else
		if ( match("^int[\\s]+([\\w]+)", strLine, &matches) )
		{
			fprintf(fo, "  _int(%s);\n", value(matches[1]).c_str());
		} else
		if ( match("^[\\s]*jmp[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			fprintf(fo, "  goto %s;\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jmp[\\s]+([\\w]*)$", strLine, &matches) )
		{
			fprintf(fo, "  goto %s;\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*loop[\\s]+([\\w]*)$", strLine, &matches) )
		{
			fprintf(fo, "  if ( --cx )\n    goto %s;\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*loope[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			_ASSERT( !_lastcmp.empty() );
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			fprintf(fo, "  if ( --cx && (%s) == 0 )\n    goto %s;\n", _lastcmp.c_str(), matches[1].c_str());
		} else
		if ( match("^[\\s]*loopne[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			_ASSERT( !_lastcmp.empty() );
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			fprintf(fo, "  if ( --cx && (%s) != 0 )\n    goto %s;\n", _lastcmp.c_str(), matches[1].c_str());
		} else //		cmp	byte_data_6A8A,	0
		if ( match("^cmp[\\s]+([^,]+), ([^,]+)$", strLine, &matches) )
		{
			string arg1 = value(matches[1]);
			string arg2 = value(matches[2]);

			if ( match("^[abcd][hl]$", arg1) )
				replace(arg2, "*(WORD*)&", "");
			if ( match("^[abcd][hl]$", arg2) )
				replace(arg1, "*(WORD*)&", "");

			if ( arg1 == arg2 )
				fprintf(fo, "  zf = 1;\n");
			else {

				if ( arg2 == "0" )
					lastcmp = arg1;
				else
					lastcmp = arg1.c_str() + string(" - ") + arg2.c_str();
			}
			//fprintf(fo, "  _cmpval = %s - %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^test[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = value(matches[1]) + " & " + value(matches[2]).c_str();
//			fprintf(fo, "  _cmpval = %s & %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^dec[\\s]+(.*)$", strLine, &matches) )
		{
			string arg = value(matches[1]);
			lastcmp = arg;
			if ( arg.find( '*' ) == -1 )
				fprintf(fo, "  %s--;\n", arg.c_str());
			else
				fprintf(fo, "  (%s)--;\n", arg.c_str());
		} else
		if ( match("^inc[\\s]+(.*)$", strLine, &matches) )
		{
			string arg = value(matches[1]);
			lastcmp = arg;
			if ( arg.find( '*' ) == -1 )
				fprintf(fo, "  %s++;\n", arg.c_str());
			else
				fprintf(fo, "  (%s)++;\n", arg.c_str());
		} else
		if ( match("^sub[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = value(matches[1]);
			if ( matches[1] == matches[2] )
				fprintf(fo, "  %s = 0;\n", matches[1].c_str());
			else
				fprintf(fo, "  %s -= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^add[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  %s += %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^adc[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  %s += %s + cf;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*xor[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = matches[1];
			fprintf(fo, "  %s ^= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*ja[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
//			_ASSERT( !_lastcmp.empty() );
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) 
			{
				// CF == 0 ZF == 0    x > y
				fprintf(fo, "  unknown_condition(); // skontroluj ja");
				fprintf(fo, "  if ( !cf )\n");
			} else
			{
				if ( cmp16bit( _lastcmp ) )
					fprintf(fo, "  if ( (short)(%s) > 0 )\n", _lastcmp.c_str());
				else
					fprintf(fo, "  if ( (char)(%s) > 0 )\n", _lastcmp.c_str());
			}
			fprintf(fo, "    goto %s; // ja\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jb[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) 
			{
				// CF == 1   x < y
				fprintf(fo, "  unknown_condition(); // skontroluj jb");
				fprintf(fo, "  if ( cf )\n");
			} else
			{
				if ( cmp16bit( _lastcmp ) )
					fprintf(fo, "  if ( (short)(%s) < 0 )\n", value(_lastcmp).c_str());
				else
					fprintf(fo, "  if ( (char)(%s) < 0 )\n", value(_lastcmp).c_str());
			}
			fprintf(fo, "    goto %s; // jb\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jnb[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			if ( cmp16bit( _lastcmp ) )
				fprintf(fo, "  if ( (short)(%s) >= 0 )\n", value(_lastcmp).c_str());
			else
				fprintf(fo, "  if ( (char)(%s) >= 0 )\n", value(_lastcmp).c_str());
			fprintf(fo, "    goto %s; // jnb\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jbe[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			if ( cmp16bit( _lastcmp ) )
				fprintf(fo, "  if ( (short)(%s) <= 0 )\n", value(_lastcmp).c_str());
			else
				fprintf(fo, "  if ( (char)(%s) <= 0 )\n", value(_lastcmp).c_str());
			fprintf(fo, "    goto %s; // jbe\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jz[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			fprintf(fo, "  if ( (%s) == 0 )\n", _lastcmp.c_str());
			fprintf(fo, "    goto %s;\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*jnz[\\s]+short[\\s]+([\\w]*)$", strLine, &matches) )
		{
			lastcmp = _lastcmp;
			if ( _lastcmp.empty() ) ReportUnknownCondition();
			if ( _lastcmp.empty() ) _lastcmp = "unknown_condition()";
			fprintf(fo, "  if ( (%s) != 0 )\n", _lastcmp.c_str());
			fprintf(fo, "    goto %s;\n", matches[1].c_str());
		} else
		if ( match("^[\\s]*shr[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = ""; //value(matches[1]);
			fprintf(fo, "  %s >>= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*shl[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = ""; //value(matches[1]);
			fprintf(fo, "  %s <<= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*and[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = matches[1];
			fprintf(fo, "  %s &= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*or[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			lastcmp = matches[1];
			fprintf(fo, "  %s |= %s;\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^not[\\s]+(.*)$", strLine, &matches) )
		{
			fprintf(fo, "  %s = ~%s;\n", value(matches[1]).c_str(), value(matches[1]).c_str());
		} else
		if ( match("^[\\s]*out[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  _out(%s, %s);\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*in[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  _in(%s, %s);\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*xchg[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  _xchg(%s, %s);\n", matches[1].c_str(), matches[2].c_str());
		} else
		if ( match("^[\\s]*retn", strLine, &matches) )
		{/*
			if ( !lastcmp2.empty() )
			{
				fprintf(fo, "  _cmp = %s\n", lastcmp2.c_str());
				lastcmp = "_cmp";
			}*/
			fprintf(fo, "  return;\n");
		} else
		if ( match("^[\\s]*retf", strLine, &matches) )
		{
			fprintf(fo, "  return;\n");
		} else
		if ( match("^[\\s]*nop", strLine, &matches) )
		{
		} else
		if ( match("^[\\s]*cli", strLine, &matches) )
		{
			fprintf(fo, "  _cli();\n");
		} else
		if ( match("^[\\s]*sti", strLine, &matches) )
		{
			fprintf(fo, "  _sti();\n");
		} else
		if ( match("^[\\s]*std", strLine, &matches) )
		{
			fprintf(fo, "  _std();\n");
		} else
		if ( match("^[\\s]*stc", strLine, &matches) )
		{
			fprintf(fo, "  _stc();\n");
		} else
		if ( match("^[\\s]*ctc", strLine, &matches) )
		{
			fprintf(fo, "  _ctc();\n");
		} else
		if ( match("^[\\s]*cld", strLine, &matches) )
		{
			fprintf(fo, "  _cld();\n");
		} else
		if ( match("^rep[\\s]+(\\w+)$", strLine, &matches) )
		{
			fprintf(fo, "  _rep_%s();\n", matches[1].c_str());
		} else
		if ( match("^repne[\\s]+(\\w+)$", strLine, &matches) )
		{
			fprintf(fo, "  _repne_%s();\n", matches[1].c_str());
		} else
		//if ( match("^pushf$", strLine, &matches) )
		//{
		//	fprintf(fo, "  _pushf();\n");
		//} else
		if ( strLine == "aaa" || strLine == "lodsw" || 
			strLine == "lodsb" || 
			strLine == "stosw" || strLine == "clc" ||
			strLine == "sahf" || strLine == "lahf" ||
			strLine == "popf" || strLine == "pushf" )
		{
			fprintf(fo, "  _%s();\n", strLine.c_str());
		} else
		if ( match("^[\\s]*rcr[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  _rcr(%s, %s);\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^[\\s]*rcl[\\s]+([^,]+), ([^,]+)", strLine, &matches) )
		{
			fprintf(fo, "  _rcl(%s, %s);\n", value(matches[1]).c_str(), value(matches[2]).c_str());
		} else
		if ( match("^(word_code_.*)\\sdw(.*)$", strLine, &matches) )
		{
			fprintf(fo, "WORD %s = %s;\n", matches[1].c_str(), value(matches[2]).c_str());
			fprintf(fh, "extern WORD %s;\n", matches[1].c_str());
		} else
		if ( match("^(byte_code_.*)\\sdb(.*)$", strLine, &matches) )
		{
			fprintf(fo, "BYTE %s = %s;\n", matches[1].c_str(), value(matches[2]).c_str());
			fprintf(fh, "extern BYTE %s;\n", matches[1].c_str());
		} else
		{
			bool bIgnore = false;
			if ( match("^assume", strLine) )
				bIgnore = true;
			if ( bIgnore )
				fprintf(fo, "//%s\n", line);
			else
				fprintf(fo, "unknown_command(); //%s\n", line);

		}
		//7break;
	}

	if ( outproc )
	{
		outproc = false;
		fprintf(fo, "*/\n");
	}

	fclose(f);
	fclose(fo);
	fclose(fh);
	return 0;
}


// http://www.csc.depauw.edu/~bhoward/asmtut/asmtut7.html