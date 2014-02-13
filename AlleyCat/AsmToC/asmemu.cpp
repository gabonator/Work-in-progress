// asmemu.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
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

string format(const char* fmt, ...)
{
    char dest[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsprintf(dest, fmt, argptr);
    va_end(argptr);
	return string(dest);
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
		out = string("seg_")+matches[1];
	else if ( match("^byte_data_(.*)\\+(.*)$", key.c_str(), &matches) )
		out = string("_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(value(matches[2]))) + "]";
		//out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^word_data_(.*)\\+(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(value(matches[2]))) + "]";
		//out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^byte_data_(.*)$", key.c_str(), &matches) )
		out = string("_data[0x") + value(matches[1]) + string("]");
	//else if ( match("^byte_(.*)$", key.c_str(), &matches) )
	//	out = string("_data[0x") + value(matches[1]) + string("]");
	else if ( match("^word_data_(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[0x") + value(matches[1]) + string("]");
	//else if ( match("^word_(.*)$", key.c_str(), &matches) )
	///	out = string("/*code*/0x") + value(matches[1]) + string("]");
	else if ( match("^es:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[es*16+") + value(matches[1]) + string("]");
	else if ( match("^ds:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[ds*16+") + value(matches[1]) + string("]");

	else if ( match("^(cs|ds|es):(.*)$", key.c_str(), &matches) )
	{
		out = value(matches[2]);
		if (out.find('[') != string::npos )
			replace(out, "[", format("[%s*16+", matches[1].c_str()));
		else
			out = format("*(WORD*)&_data[%s*16+%s]", matches[1].c_str(), out.c_str());
	}/*
	else if ( match("^ds:(.*)$", key.c_str(), &matches) )
	{
		out = value(matches[1]);
		if (out.find('[') != string::npos )
			replace(out, "[", "[ds*16+");
		else
			out = string("*(WORD*)&_data[ds*16+") + value(matches[1]) + string("]");
	}
	else if ( match("^es:(.*)$", key.c_str(), &matches) )
	{
		out = value(matches[1]);
		replace(out, "[", "[es*16+");
		//out = string("*(WORD*)&_data[es*16+") + value(matches[1]) + string("]");
	}*/

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

vector<string> src;
vector<string> code;

void insert(int i, string line)
{
	code.insert(code.begin()+i, line);
}


string safeop(string arg)
{
	if ( arg.find( '*' ) == -1 )
		return arg;
	return format("(%s)", arg.c_str());
}

string updateCarry( int nLine )
{
	vector<string> matches;
	string line = src[nLine];
	if ( match("^shl[\\s]+(.*), (.*)$", line, &matches) )
		return format("  cf = %s & 128 ? 1 : 0;", matches[1].c_str());
	if ( match("^shr[\\s]+(.*), (.*)$", line, &matches) )
		return format("  cf = %s & 1 ? 1 : 0;", matches[1].c_str());
	if ( line == "sahf" )
		return "//";
	return "";
}

string getCondition( string jump, int nLine )
{
	string strPrev = src[nLine];
	string condition;
	vector<string> args;
	if ( match("^loope", strPrev) ) // loope does not change flags
	{
		code.push_back("// dummy"); // will be removed
		strPrev = src[--nLine];
	}

	if ( match("^call[\\s]+(.*)$", strPrev, &args) )
	{
		string funcName = args[1];
		replace(funcName, "_code_", "_");

		if ( funcName == "sub_13D8" )
		{
			if ( jump == "jz" )
			{
				condition = format("!%s()", funcName.c_str());
				code.pop_back();
			}
			if ( jump == "jnz" )
			{
				condition = format("%s()", funcName.c_str());
				code.pop_back();
			}
		}
		if ( funcName == "sub_13D8" || funcName == "sub_1B7A" || funcName == "sub_20F5" || 
			 funcName == "sub_1608" || funcName == "sub_22F7" )
		{
			if ( jump == "jnb" )
				condition = "!cf";
			if ( jump == "jb" )
				condition = "cf";
		}
		if ( funcName == "sub_658" )
		{
			if ( jump == "jz" )
				condition = "zf";
			if ( jump == "jnz" )
				condition = "!zf";
		}

	}

	if ( match("^cmp\\s+(.*),\\s*(.*)$", strPrev, &args) )
	{
		args[1] = value(args[1]);
		args[2] = value(args[2]);
		if ( match("^[abcd][hl]$", args[1]) )
			replace(args[2], "*(WORD*)&", "");
		if ( match("^[abcd][hl]$", args[2]) )
			replace(args[1], "*(WORD*)&", "");

		if ( jump == "jz" )
			condition = format("%s == %s", args[1].c_str(), args[2].c_str());
		if ( jump == "jnz" )
			condition = format("%s != %s", args[1].c_str(), args[2].c_str());
		if ( jump == "jb" )
			condition = format("%s < %s", args[1].c_str(), args[2].c_str());
		if ( jump == "ja" )
			condition = format("%s > %s", args[1].c_str(), args[2].c_str());
		if ( jump == "jnb" )
			condition = format("%s >= %s", args[1].c_str(), args[2].c_str());
		if ( jump == "jbe" )
			condition = format("%s <= %s", args[1].c_str(), args[2].c_str());
/*

		bool b16 = cmp16bit(args[1]) || cmp16bit(args[2]);
		string prefix = b16 ? "(short)" : "(char)";

		string arg2 = args[2];
		if ( arg2 != "0" )
			arg2 = string(" - ") + arg2;
		else
			arg2 = "";
		if ( jump == "jz" )
			condition = format("(%s%s) == 0", args[1].c_str(), arg2.c_str());
		if ( jump == "jnz" )
			condition = format("(%s%s) != 0", args[1].c_str(), arg2.c_str());
		if ( jump == "jb" )
			condition = format("%s(%s%s) < 0", prefix.c_str(), args[1].c_str(), arg2.c_str());
		if ( jump == "ja" )
			condition = format("%s(%s%s) > 0", prefix.c_str(), args[1].c_str(), arg2.c_str());
		if ( jump == "jnb" )
			condition = format("%s(%s%s) >= 0", prefix.c_str(), args[1].c_str(), arg2.c_str());
		if ( jump == "jbe" )
			condition = format("%s(%s%s) <= 0", prefix.c_str(), args[1].c_str(), arg2.c_str());
*/
		if ( !condition.empty() )
			code.pop_back();
	} 
	if ( match("^(or|and|sub|add|xor)[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		if ( jump == "jz" )
			condition = format("!%s", value(args[2]).c_str());
		if ( jump == "jnz" )
			condition = format("%s", value(args[2]).c_str());
		//if ( !condition.empty() )
		//	code.pop_back();
	}
	if ( match("^(inc|dec)[\\s]+(.*)$", strPrev, &args) )
	{
		if ( jump == "jz" )
			condition = format("!%s", value(args[2]).c_str());
		if ( jump == "jnz" )
			condition = format("%s", value(args[2]).c_str());
		//if ( !condition.empty() )
		//	code.pop_back();
	}
	if ( match("^test[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		args[1] = value(args[1]);
		args[2] = value(args[2]);

		if ( jump == "jz" )
			condition = format("!(%s & %s)", args[1].c_str(), args[2].c_str());
		if ( jump == "jnz" )
			condition = format("%s & %s", args[1].c_str(), args[2].c_str());
		if ( !condition.empty() )
			code.pop_back();
	}

	if ( match("^sub[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		args[1] = value(args[1]);
		args[2] = value(args[2]);

		string ins_cf = format("  cf = (%s < %s); // cf-insertion", args[1].c_str(), args[2].c_str());
		string ins_zf = format("  zf = (%s == %s); // zf-insertion", args[1].c_str(), args[2].c_str());

		if ( jump == "jz" || jump == "jnz" || jump == "ja" || jump == "jbe" )
			code.insert(code.end() - 1, ins_zf);
		if ( jump == "jb" || jump == "jnb" || jump == "ja" || jump == "jbe" )
			code.insert(code.end() - 1, ins_cf);

		if ( jump == "jz" )
			condition = "zf";
		if ( jump == "jnz" )
			condition = "!zf";
		if ( jump == "jnb" )
			condition = "!cf";
		if ( jump == "jb" )
			condition = "cf";
		if ( jump == "ja" )
			condition = "!cf && !zf";
		if ( jump == "jbe" )
			condition = "cf && zf";
	}
	return condition;
}

string inverseCondition(string strCond)
{
	vector<string> matches;
	if ( match( "^\\s*(.*)\\s==\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s != %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*(.*)\\s!=\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s == %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*(.*)\\s<\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s >= %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*(.*)\\s>=\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s < %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*(.*)\\s>\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s <= %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*(.*)\\s<=\\s(.*)\\s*$", strCond, &matches) )
		strCond = format("%s > %s", matches[1].c_str(), matches[2].c_str());
	else if ( match( "^\\s*([a-z][a-z])\\s*$", strCond, &matches ) )
		strCond = format("!%s", matches[1].c_str());
	else if ( match( "^\\s*\\!([a-z][a-z])\\s*$", strCond, &matches ) )
		strCond = format("%s", matches[1].c_str());
	else
		strCond = format("!(%s)", strCond.c_str());

	return strCond;
}

int main(int argc, char* argv[])
{
	src.reserve(20000);
	code.reserve(20000);

	FILE* f = fopen("C:\\Data\\Work\\alley\\1\\cat_code.asm", "r");
	char line[1024] = {0};
	printf("Reading file...\n");
	while (!feof(f))
	{
		fgets(line, 1023, f);
		if ( line[0] )
			line[strlen(line)-1] = 0;
		string strLine(line);
		strLine = trim(strLine);
		if (strLine.length() == 0)
			continue;
		src.push_back(strLine);
	}
	fclose(f);

	printf("Processing...\n");
	bool outproc = false, inproc = false;
	string curFunction;
	for (int i=0; i<(int)src.size(); i++)
	{
		string& line = src[i];
		vector<string> matches;

		// function begin end
		if ( match("^([\\w]*)[\\s]*proc\\s(near|far)", line, &matches) )
		{
			string safelabel = matches[1];
			replace(matches[1], "_code_", "_");
			if ( outproc )
			{
				outproc = false;
				code.push_back("*/");
			}
			inproc = true;

			string procType = "void";
			if ( matches[1] == "sub_13D8" )
				procType = "BYTE";

			curFunction = matches[1];
			
			code.push_back(format("%s %s()", procType.c_str(), matches[1].c_str()));
			code.push_back("{");

			if ( matches[1] == "sub_1A569" || matches[1] == "sub_1A86D" || matches[1] == "sub_1CDEF" || matches[1] == "sub_1D05B")
			{
				code.push_back(format("%s:", safelabel.c_str()));
			}

			if ( matches[1] == "sub_3E2" || matches[1] == "sub_394" || matches[1] == "sub_349" || matches[1] == "sub_2FE" || 
				matches[1] == "sub_3339" || matches[1] == "sub_363D" || matches[1] == "sub_5BBF" || matches[1] == "sub_5E2B")
				code.push_back(format("%s:", safelabel.c_str()));
			continue;
		} 

		if ( match("^([\\w]*)[\\s]*endp$", line, &matches) )
		{
			inproc = false;
			if ( code.back() == "  return;" )
				code.pop_back();
			if ( curFunction == "sub_13D8" )
				code.push_back("  return al;");
			curFunction.clear();
			code.push_back( "}" );
			code.push_back( "" );
			continue;
		}
		
		// comment out unreferenced code
		if ( !inproc )
		{
			if (!outproc)
				code.push_back("/*");
			outproc = true;
		}

		// jump label
		if ( match("^(locret[\\w]*):$", line, &matches) )
		{
			//skip
			continue;
		} 
		if ( match("^(loc[\\w]*):$", line, &matches) )
		{
			code.push_back( format("%s:", matches[1].c_str()) );
			continue;
		} 

		if ( match("^retn$", line, &matches) )
		{
			code.push_back( "  return;" );
			continue;
		} 

		// single arg instruction
		if ( match("^(push|pop|int)[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  _%s(%s);", matches[1].c_str(), value(matches[2]).c_str()) );
			continue;
		}

		// zero arg instruction
		if ( match("^(cli|sti|std|stc|ctc|cld|aaa|lodsw|lodsb|stosw|clc|sahf|lahf|popf|pushf)$", line, &matches) )
		{
			code.push_back( format("  _%s();", matches[1].c_str() ) );
			continue;
		}

		if ( match("^(out|in|xchg|rcr|rcl)[\\s]+(.*),\\s*(.*)$", line, &matches) )
		{
			if ( matches[1] == "rcr" || matches[1] == "rcl" )
			{
				string strCarry = updateCarry(i-1);
				if ( strCarry.empty() )
					code.push_back("  fix_code(); // fix carry flag");
				else
					code.insert(code.end()-1, strCarry);
			}

			code.push_back( format("  _%s(%s, %s);", matches[1].c_str(), value(matches[2]).c_str(), value(matches[3]).c_str() ) );
			continue;
		}

		if ( match("^(rep|repne)\\s+(stosb|lodsb|stosw|lodsw|movsw|movsb)$", line, &matches) )
		{
			code.push_back( format("  _%s_%s();", matches[1].c_str(), matches[2].c_str()));
			continue;
		}

		// assignment
		if ( match("^mov[\\s]+(.*),[\\s]*(.*)$", line, &matches) )
		{
			string target = value(matches[1]);
			string source = value(matches[2]);
			if ( match("^[abcd][hl]$", target) )
				replace(source, "*(WORD*)&", "");
			if ( match("^[abcd][hl]$", source) )
				replace(target, "*(WORD*)&", "");
			code.push_back( format("  %s = %s;", target.c_str(), source.c_str()));
			continue;
		}

		// ALU
		if ( match("^dec[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  %s--;", safeop(value(matches[1])).c_str() ) );
			continue;
		}

		if ( match("^inc[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  %s++;", safeop(value(matches[1])).c_str() ) );
			continue;
		}

		if ( match("^sub\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{
			if ( matches[1] == matches[2] )
				code.push_back( format("  %s = 0;", matches[1].c_str()));
			else
				code.push_back( format("  %s -= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		} 

		if ( match("^add\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{
			code.push_back( format("  %s += %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}

		if ( match("^adc\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{
			code.push_back("  unknown_condition(); // verify cf");
			code.push_back(format("  %s += %s + cf;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		} 
		if ( match("^xor\\s+(.*),\\s*(.*)", line, &matches) )
		{
			code.push_back( format("  %s ^= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}
		if ( match("^and[\\s]+(.*), (.*)", line, &matches) )
		{
			code.push_back( format("  %s &= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}
		if ( match("^or[\\s]+(.*), (.*)", line, &matches) )
		{
			code.push_back( format("  %s |= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}
		if ( match("^shl[\\s]+(.*), (.*)$", line, &matches) )
		{
			code.push_back( format("  %s <<= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}
		if ( match("^shr[\\s]+(.*), (.*)$", line, &matches) )
		{
			code.push_back( format("  %s >>= %s;", value(matches[1]).c_str(), value(matches[2]).c_str()));
			continue;
		}
		if ( match("^not[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  %s = ~%s;", value(matches[1]).c_str(), value(matches[1]).c_str()));
			continue;
		}
		if ( match("^mul[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  ax = (WORD)%s * (WORD)al;\n", matches[1].c_str()));
			continue;
		}

		// unconditional jump/calls
		if ( match("jmp(\\sshort)?\\s+(.*)$", line, &matches) )
		{
			if (line.find("locret_") != string::npos)
				code.push_back( "  return;" );
			if (line.find("off") != string::npos)
				code.push_back( format("  unknown_command(); // %s;", line.c_str()) );
			else
				code.push_back( format("  goto %s;", value(matches[2]).c_str()));
			continue;
		}
		if ( match("^call", line, &matches) )
		{
			// workaround for: ^call.*\s(\w+)$
			string target;
			if ( match("^call\\s+(\\w+)$", line, &matches) )
				target = matches[1];
			if ( match("^call\\s+near\\s+(\\w+)$", line, &matches) )
				target = matches[1];
			if ( match("^call\\s+near\\s+ptr\\s+(\\w+)$", line, &matches) )
				target = matches[1];
			_ASSERT( !target.empty() );
			replace(target, "_code_", "_");
			code.push_back( format("  %s();", target.c_str()));
			continue;
		}

		// loops
		if ( match("^loop[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( "  if ( --cx )" );
			code.push_back( format("    goto %s;", value(matches[1]).c_str()));
			continue;
		}
		if ( match("^loope[\\s]+(.*)$", line, &matches) )
		{
			//string strPrev = src[i-1];
			string condition = getCondition("jz", i-1);
			if ( condition.empty() )
				condition = "unknown_condition()";

			code.push_back( format("  if ( --cx && (%s) )", condition.c_str()));
			code.push_back( format("    goto %s;", value(matches[1]).c_str()));
			continue;
		} 
		if ( match("^loopne[\\s]+(.*)$", line, &matches) )
		{
//			string strPrev = src[i-1];
			string condition = getCondition("jnz", i-1);
			if ( condition.empty() )
				condition = "unknown_condition()";

			code.push_back( format("  if ( --cx && (%s) )", condition.c_str()));
			code.push_back( format("    goto %s;", value(matches[1]).c_str()));
			continue;
		} 

		// conditional jump
		if ( match("^(jbe|jz|jnz|ja|jb|jnb)\\s+(short\\s)?(.*)$", line, &matches) )
		{
			string jump = matches[1];
			string condition = getCondition(jump, i-1);

			string help;
			if ( condition.empty() )
			{
				condition = "unknown_condition()";
				if ( jump == "jnb" )
					help = "cf=0";
				if ( jump == "jb" )
					help = "cf=1";
				if ( jump == "ja" )
					help = "cf=0 & zf=0";
				if ( jump == "jbe" )
					help = "cf=1 & zf=1";
			}
			code.push_back(format("  if ( %s ) // %s %s", condition.c_str(), matches[1].c_str(), help.c_str()));
			if ( match("^locret", matches[3]) )
				code.push_back("    return;");
			else
				code.push_back( format("    goto %s;", value(matches[3]).c_str()));
			continue;
		}
		if ( match("^cmp\\s+(.*),\\s*(.*)$", line, &matches) )
		{
			if ( matches[1] == matches[2] )
				code.push_back( "  fix_code(); // zf=1");
			else
				code.push_back( format("  fix_code(); // %s", line.c_str()));
			continue;
		}
		if ( match("^(.*_code_.*)\\s(dw|db)(.*)$", line, &matches) )
		{
			if ( outproc )
			{
				outproc = false;
				inproc = true; // todo!
				code.push_back("*/");
			}

			string strType = "UNKNOWN";
			if (matches[2] == "db")
				strType = "BYTE";
			if (matches[2] == "dw")
				strType = "WORD";

			code.push_back( format("%s %s = %s;", strType.c_str(), matches[1].c_str(), matches[3].c_str()) );
			continue;
		} 

		// discard
		if ( line == "nop" || match("^assume", line) )
			continue;

		// unidentified command
		code.push_back( string("  unknown_command(); // ") + line );
	}
	if ( outproc )
	{
		outproc = false;
		code.push_back("*/");
	}

	int nLines[] = {571, 4716, 4764, 0};
	for (int i=0; nLines[i]; i++)
	{
		string& line = code[nLines[i]-3];
		_ASSERT( line.find("_data") != string::npos );
		replace( line, "_data[", "_video[0*");
	}
	printf("Optimizing...\n");
	code.insert(code.begin(), "#include \"cat_code.h\"");
	code.insert(code.begin()+1, "");
	for (int i=0; i<(int)code.size()-4; i++)
	{
		vector<string> matches;
		if ( match( "\\s*loc_", code[i+0] ) && 
			 match( "\\s*if",   code[i+1] ) &&
			 match( "\\s*goto",  code[i+2] ) )
		{
			string strLabel, strLoop;
			if ( match( "^(.+):$", code[i+0], &matches) )
				strLabel = matches[1];
			if ( match( "goto\\s(.*);", code[i+2], &matches) )
				strLoop = matches[1];
			if ( code[i+1].find("()") != string::npos || 
				 code[i+1].find("++") != string::npos ||
				 code[i+1].find("--") != string::npos)
				continue;
			if ( strLabel != strLoop )
				continue;
			code.insert(code.begin()+i+1, "  tick();");
			i++;
		}

		continue;
		if ( match( "if",    code[i+0] ) && 
			 match( "goto",  code[i+1] ) &&
			 match( "goto",  code[i+2] ) &&
			 match( "loc_",  code[i+3] ) )
		{
			string strCond, strComment, strJumpTrue, strJumpFalse, strLabel;
			string strTemp = code[i+0];
			replace(strTemp, "*(WORD*)", "__WORD");
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;
			if ( match( "goto\\s(.*);", code[i+1], &matches) )
				strJumpTrue = matches[1];
			else 
				continue;
			if ( match( "goto\\s(.*);", code[i+2], &matches) )
				strJumpFalse = matches[1];
			else 
				continue;
			if ( match( "^(.+):$", code[i+3], &matches) )
				strLabel = matches[1];
			else 
				continue;
			if ( strLabel != strJumpTrue )
				continue;

			// negate condition
			strCond = inverseCondition(strCond);

			code[i+0] = format("  if ( %s ) %s", strCond.c_str(), strComment.c_str());
			code[i+1] = format("    goto %s;", strJumpFalse.c_str());
			code[i+2] = "";
		}

		if ( match( "if",    code[i+0] ) && 
			 match( "goto",  code[i+1] ) &&
			 match( "loc_",  code[i+3] ) )
		{
			string strCond, strComment, strJumpTrue, strCode, strLabel;
			string strTemp = code[i+0];
			replace(strTemp, "*(WORD*)", "__WORD");
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;
			if ( match( "goto\\s(.*);", code[i+1], &matches) )
				strJumpTrue = matches[1];
			else 
				continue;
			strCode = code[i+2];
			if ( match( "^(.+):$", code[i+3], &matches) )
				strLabel = matches[1];
			else 
				continue;
			if ( strLabel != strJumpTrue )
				continue;

			strCond = inverseCondition(strCond);

			code[i+0] = format("  if ( %s ) %s", strCond.c_str(), strComment.c_str());
			code[i+1] = format("  %s", strCode.c_str());
			code[i+2] = "";

		}

		if ( match( "if",    code[i+0] ) && 
			 match( "goto",  code[i+1] ) &&
			 !match( "goto",  code[i+2] ) &&
			 !match( "loc_",  code[i+2] ) &&
			 !match( "goto",  code[i+3] ) &&
			 !match( "loc_",  code[i+3] ) &&
			 match( "loc_",  code[i+4] ) )
		{
			string strCond, strComment, strJumpTrue, strCode1, strCode2, strLabel;
			string strTemp = code[i+0];
			replace(strTemp, "*(WORD*)", "__WORD");
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;
			if ( match( "goto\\s(.*);", code[i+1], &matches) )
				strJumpTrue = matches[1];
			else 
				continue;
			strCode1 = code[i+2];
			strCode2 = code[i+3];
			if ( match( "^(.+):$", code[i+4], &matches) )
				strLabel = matches[1];
			else 
				continue;
			if ( strLabel != strJumpTrue )
				continue;

			strCond = inverseCondition(strCond);

			code[i+0] = format("  if ( %s ) %s", strCond.c_str(), strComment.c_str());
			code[i+1] = "  {";
			code[i+2] = format("  %s", strCode1.c_str());
			code[i+3] = format("  %s", strCode2.c_str());
			string tmp = code[i+4];
			code[i+4] = "  }";
			code.insert(code.begin()+i+5, tmp);
		}

	}

	printf("Writing...\n");
	FILE* fo = fopen("C:\\Data\\Work\\alley\\2\\cat_code.cpp", "w");
	FILE* fh = fopen("C:\\Data\\Work\\alley\\2\\cat_code.h", "w");
	for (int i=0; i<(int)code.size(); i++)
	{
		vector<string> matches;
		string& line = code[i];
		if ( match("^(void|BYTE|WORD)\\s(.*)\\(\\)$", line, &matches) )
			fprintf(fh, "%s %s();\n", matches[1].c_str(), matches[2].c_str());
		fprintf(fo, "%s\n", line.c_str());
	}
	fclose(fo);
	fclose(fh);

	return 0;
}


// http://www.csc.depauw.edu/~bhoward/asmtut/asmtut7.html