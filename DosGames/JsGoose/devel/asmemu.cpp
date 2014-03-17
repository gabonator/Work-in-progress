// asmemu.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "trex.h"
#include <string>
#include <vector>
#include <algorithm>
//#undef _ASSERT
//#define _ASSERT(x) if (!(x)) { printf("prev(%s) - test(%s)\n", _strPrevLine.c_str(), strLine.c_str() ); }
#define ReportUnknownCondition() printf("Unknown condition - line %d\n%s\n%s\n", nLine, _strPrevLine.c_str(), strLine.c_str());
using namespace std;


// strings

string format(const char* fmt, ...)
{
    char dest[1024];
    va_list argptr;
    va_start(argptr, fmt);
    vsprintf(dest, fmt, argptr);
    va_end(argptr);
	return string(dest);
}

// regexp
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

bool replacefirst(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
bool replace(std::string& str, const std::string& from, const std::string& to) {
	while ( replacefirst( str, from, to ) );
	return true;
}

// javascript
const bool js = true;
const bool jsta = true;
const bool jsf = false;
const bool jslk = false;

bool jsop16(string s)
{
	if ( s == "ax" || s== "bx" || s == "cx" || s == "dx" )
		return true;
	return false;
}
string jsgetaddr(string s)
{
	vector<string> args;
	if ( match("_data\\[(.*)$", s, &args ) )
	{
		string sub = args[1];
		if (sub.at( sub.length() -1 ) == ']' )
			sub = sub.substr(0, sub.length() -1 );
		else
			_ASSERT(0);
		return sub;
	}
	return "";
}

string jsget(string s)
{
	if (!js)
		return s;
	//if ( s == "ax" || s== "bx" || s == "cx" || s == "dx" )
//		return string("get_") + s + "()";
	if ( s.substr(0,9) == "*(WORD*)&" )
	{
		if ( s.find("bp") != string::npos )
		{
			string adr = jsgetaddr(s).c_str();
			if ( adr.find("OFS") != string::npos )
			{
				replace(adr, "OFS", "");
				return format("_stack16get%s", adr.c_str());
			}
			return format("_stack16get(%s)", adr.c_str());
		}
		return format("_data16get(%s)", jsgetaddr(s).c_str());
	}
	return s;
}

string jsassign(string target, string src1)
{
	if ( match("^[abcd][hl]$", src1) || match("^r8\\[[abcd][hl]\\]$", src1))
	{
		replace(target, "*(WORD*)&", "");
	}

	if ( target.substr(0,9) == "*(WORD*)&" )
	{
		if ( target.find("bp") != string::npos )
			return format("_stack16set(%s, %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str() );
		return format("_data16set(%s, %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str() );
	}
	//if ( jsop16(target) )
	//	return format("set_%s(%s);", target.c_str(), jsget( src1 ).c_str() );
	return target + " = " + jsget( src1 ) + ";";
}

string jsassign(string target, string src1, string src2)
{
	if ( target.substr(0,9) == "*(WORD*)&" )
	{
		if ( src1.find("bp") != string::npos || src2.find("bp") != string::npos)
			return format("_stack16set(%s, %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str() );
		return format("_data16set(%s, %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str() );
	}
	//if ( jsop16(target) )
//		return format("set_%s(%s %s);", target.c_str(), jsget( src1 ).c_str(), jsget(src2).c_str() );
	if ( target == src1 && src2 == "+1")
		return target + "++;";
	if ( target == src1 && src2 == "-1")
		return target + "--;";
	return target + " = " + jsget( src1 ) + " " + jsget(src2) + ";";
}

string jsassign(string target, string src1, string src2, string src3)
{
	if ( target == src1 )
	{
		if ( match("^[abcd][hl]$", target) || match("^r8\\[[abcd][hl]\\]$", target))
		{
			if ( src3.find( "*(WORD*)&" ) != string::npos )
				replace(src3, "*(WORD*)&", "");
			if ( src3.find("_data16get(") != string::npos )
			{
				replace(src3, "_data16get(", "_data[");
				_ASSERT( src3.substr(src3.length()-1, 1) == ")" );
				src3 = src3.substr(0, src3.length()-1) + "]";
			}
		}
	}

	if ( target.substr(0,9) == "*(WORD*)&" )
	{
		if ( src1.find("bp") != string::npos || src2.find("bp") != string::npos || src3.find("bp") != string::npos)
			return format("_stack16set(%s, %s %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str()  );

		return format("_data16set(%s, %s %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str()  );
	}
	//if ( jsop16(target) )
//		return format("set_%s(%s %s %s);", target.c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str() );

	if ( target == src1 && src2 == "&")
		return target + " &= " + jsget(src3) + ";";
	if ( target == src1 && src2 == "|")
		return target + " |= " + jsget(src3) + ";";
	if ( target == src1 && src2 == "+")
		return target + " += " + jsget(src3) + ";";
	if ( target == src1 && src2 == "-")
		return target + " -= " + jsget(src3) + ";";
	if ( target == src1 && src2 == "<<")
		return target + " <<= " + jsget(src3) + ";";
	if ( target == src1 && src2 == ">>")
		return target + " >>= " + jsget(src3) + ";";

	return target + " = " + jsget( src1 ) + " " + jsget(src2) + " " + jsget(src3) + ";";
}

string jsassign(string target, string src1, string src2, string src3, string src4)
{
	if ( target.substr(0,9) == "*(WORD*)&" )
	{
		if ( src1.find("bp") != string::npos || src2.find("bp") != string::npos || src3.find("bp") != string::npos)
			return format("_stack16set(%s, %s %s %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str(), jsget(src4).c_str());
		return format("_data16set(%s, %s %s %s %s);", jsgetaddr(target).c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str(), jsget(src4).c_str());
	}
	//if ( jsop16(target) )
//		return format("set_%s(%s %s %s %s);", target.c_str(), jsget( src1 ).c_str(), jsget(src2).c_str(), jsget(src3).c_str(), jsget(src4).c_str() );
	return target + " = " + jsget( src1 ) + " " + jsget(src2) + " " + jsget(src3) + " " + jsget(src4) + ";";
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

string _value(string key)
{
	vector<string> matches;
	string out = key;

	if ( key == "ax" || key == "bx" || key == "cx" || key == "dx" )
		return string("r16[")+key+"]";
	if ( key == "ah" || key == "bh" || key == "ch" || key == "dh" ||
		 key == "al" || key == "bl" || key == "cl" || key == "dl" )
		return string("r8[")+key+"]";

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
		out = string("_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(_value(matches[2]))) + "]";
	else if ( match("^word_data_(.*)\\+(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(_value(matches[2]))) + "]";
	else if ( match("^byte_data_(.*)$", key.c_str(), &matches) )
		out = string("_data[0x") + _value(matches[1]) + string("]");
	else if ( match("^word_data_(.*)$", key.c_str(), &matches) )
		out = string("*(WORD*)&_data[0x") + _value(matches[1]) + string("]");
	else if ( match("^es:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[ADR(es,") + _value(matches[1]) + string(")]");
	else if ( match("^ds:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
		out = string("*(WORD*)&_data[ADR(ds,") + _value(matches[1]) + string(")]");

	else if ( match("^(cs|ds|es):(.*)$", key.c_str(), &matches) )
	{
		out = _value(matches[2]);
		if (out.find('[') != string::npos )
		{
			replacefirst(out, "[", format("[ADR(%s, ", matches[1].c_str()));
			_ASSERT( out.substr(out.length()-1,1) == "]" );
			out = out.substr(0, out.length()-1) + ")]";
		}
		else
			out = format("*(WORD*)&_data[ADR(%s,%s)]", matches[1].c_str(), out.c_str());
	}

	else if ( match("^\\[(.*)\\+(.*)\\+(.*)\\]$", key.c_str(), &matches) )
	{
		if ( matches[1] == "si" )
			out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + string(" + ") + _value(matches[2]) + string(" + ") + _value(matches[3]) + (")]");
		else
			out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" + ") + _value(matches[2]) + string(" + ") + _value(matches[3]) + (")]");
	}
	else if ( match("^\\[(.*)\\+(.*)\\]$", key.c_str(), &matches) )
	{
		if ( matches[1] == "si" )
			out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + string(" + ") + _value(matches[2]) + (")]");
		else
			out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" + ") + _value(matches[2]) + (")]");
	}
	else if ( match("^\\[(.*)\\-(.*)\\]$", key.c_str(), &matches) )
	{
		if ( matches[1] == "si" )
			out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + (")]");
		else
			out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" - ") + _value(matches[2]) + (")]");
	}
	else if ( match("^\\[(.*)\\]$", key.c_str(), &matches) )
	{
		if ( matches[1] == "si" )
			out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + (")]");
		else
			out = string("*(WORD*)&_data[") + _value(matches[1]) + ("]");
	}
	else if ( match("^word ptr (.*)$", key.c_str(), &matches) )
	{
		out = _value(matches[1]);
		if ( out.find("*(WORD*)") == -1 )
			out = string("*(WORD*)&") + out;
		//out = string("*(WORD*)(") + value(matches[1]) + string(")");
	}
	else if ( match("^byte ptr (.*)$", key.c_str(), &matches) )
	{
		out = _value(matches[1]);
		replace(out, "*(WORD*)&", "");
	}	
	if ( match("^offset\\s(.*)$", key.c_str(), &matches) )
		out = string("&") + _value(matches[1]); 
	
	return out;
}

string lvalue(string s)
{
	return _value(s);
}

string rvalue(string s)
{
	return jsget(_value(s));
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
	while ( match("pop", strPrev ) )
		strPrev = src[--nLine];

	if ( match("^(int)[\\s]+(.*)$", strPrev, &args) )
	{
		if ( args[2] == "21h" )
		{
			// suppose file io
			if ( jump == "jnb" )
				condition = "!cf";
			if ( jump == "jb" )
				condition = "cf";
		}
	}

	if ( match("(jz|jnz|jb|ja|jnb|jbe|jge|jle|jl|jns|js|jg)", strPrev) )
	{
		// previous line is conditional jump, use the same condition
		code.push_back("// dummy");
		return getCondition( jump, nLine-1 );
	}

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
		if ( args[2] == "[si+2]")
		{
			int f = 9;
		}
		args[1] = rvalue(args[1]);
		args[2] = rvalue(args[2]);
		string signedtype = "short";
		if ( match("^[abcd][hl]$", args[1]) || match("^r8\\[[abcd][hl]\\]$", args[1]) )
		{
			if ( args[2].find( "*(WORD*)&" ) != string::npos )
				replace(args[2], "*(WORD*)&", "");
			if ( args[2].find("_data16get(") != string::npos )
			{
				replace(args[2], "_data16get(", "_data[");
				_ASSERT( args[2].substr(args[2].length()-1, 1) == ")" );
				args[2] = args[2].substr(0, args[2].length()-1) + "]";
			}

			//replace(args[2], "*(WORD*)&", "");
			signedtype = "char";
		}
		if ( match("^[abcd][hl]$", args[2]) || match("^r8\\[[abcd][hl]\\]$", args[2]) )
		{
			replace(args[1], "*(WORD*)&", "");
			signedtype = "char";
		}

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
		// signed
		if ( jump == "jle" ) // <=
			condition = format("(%s)%s <= (%s)%s", signedtype.c_str(), args[1].c_str(), signedtype.c_str(), args[2].c_str());
		if ( jump == "jge" ) // >=
			condition = format("(%s)%s >= (%s)%s", signedtype.c_str(), args[1].c_str(), signedtype.c_str(), args[2].c_str());
		if ( jump == "jg" ) // >
			condition = format("(%s)%s > (%s)%s", signedtype.c_str(), args[1].c_str(), signedtype.c_str(), args[2].c_str());
		if ( jump == "jns" ) // >= 0
			condition = format("(%s)(%s-%s) >= 0", signedtype.c_str(), args[1].c_str(), args[2].c_str());
		if ( jump == "js" ) // < 0
			condition = format("(%s)(%s-%s) < 0", signedtype.c_str(), args[1].c_str(), args[2].c_str());
		if ( jump == "jl" ) // <
			condition = format("(%s)%s < (%s)%s", signedtype.c_str(), args[1].c_str(), signedtype.c_str(), args[2].c_str());
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
	if ( match("^(or|and|sub|add|xor|shl|shr)[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		if ( jump == "jz" )
			condition = format("!%s", rvalue(args[2]).c_str());
		if ( jump == "jnz" )
			condition = format("%s", rvalue(args[2]).c_str());
		if ( jump == "js" || jump == "jns" )
		{
			string signedtype = "";
			if ( match("^[abcd][hl]$", args[2])  )
				signedtype = "(char)";
			if ( match("^[abcd]x$", args[2])  )
				signedtype = "(short)";

			if ( jump == "js" )
				condition = format("%s %s < 0", signedtype.c_str(), rvalue(args[2]).c_str());
			else if ( jump == "jns" )
				condition = format("%s %s >= 0", signedtype.c_str(), rvalue(args[2]).c_str());
		}
		//if ( !condition.empty() )
		//	code.pop_back();
	}
	if ( match("^(inc|dec)[\\s]+(.*)$", strPrev, &args) )
	{
		if ( jump == "jz" )
			condition = format("!%s", rvalue(args[2]).c_str());
		if ( jump == "jnz" )
			condition = format("%s", rvalue(args[2]).c_str());
		if ( jump == "js" || jump == "jns" )
		{
			string signedtype = "";
			if ( match("^[abcd][hl]$", args[2])  )
				signedtype = "(char)";
			if ( match("^[abcd]x$", args[2])  )
				signedtype = "(short)";

			if ( jump == "js" )
				condition = format("%s %s < 0", signedtype.c_str(), rvalue(args[2]).c_str());
			else if ( jump == "jns" )
				condition = format("%s %s >= 0", signedtype.c_str(), rvalue(args[2]).c_str());
		}

		//if ( !condition.empty() )
		//	code.pop_back();
	}
	if ( match("^test[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		args[1] = rvalue(args[1]);
		args[2] = rvalue(args[2]);

		if ( jump == "jz" )
			condition = format("!(%s & %s)", args[1].c_str(), args[2].c_str());
		if ( jump == "jnz" )
			condition = format("%s & %s", args[1].c_str(), args[2].c_str());
		if ( !condition.empty() )
			code.pop_back();
	}

	if ( match("^sub[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		args[1] = rvalue(args[1]);
		args[2] = rvalue(args[2]);

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
	if ( match("^(shr)[\\s]+(.*), (.*)$", strPrev, &args) )
	{
		args[2] = rvalue(args[2]);
		args[3] = rvalue(args[3]);

		string ins_cf = "";
		if ( args[1] == "shr" )
			ins_cf = format("  cf = %s & 1; // cf-insertion", args[2].c_str());

		if ( jump == "jnb" || jump == "jb" )
			code.insert(code.end() - 1, ins_cf);

		if ( jump == "jnb" )
			condition = "!cf";
		if ( jump == "jb" )
			condition = "cf";
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

bool parseIf(string strLine, string& strCond, string& strComment)
{	
	vector<string> matches;
	string strTemp = strLine;
	replace(strTemp, "*(WORD*)", "__WORD");
	if ( match( "if\\s\\((.*)\\)$", strTemp, &matches) )
	{
		strCond = trim(matches[1]);
		replace(strCond, "__WORD", "*(WORD*)");
		strComment = "";
		return true;
	}

	if ( match( "if\\s\\((.*)\\)\\s+\\/\\/(.*)$", strTemp, &matches) )
	{
		strCond = trim(matches[1]);
		replace(strCond, "__WORD", "*(WORD*)");
		strComment = trim(matches[2]);
	} else 
		return false;
	return true;
}

bool parseGoto(string strLine, string& strGoto)
{
	vector<string> matches;
	if ( match("goto\\s(.*)\\;", strLine, &matches) )
	{
		strGoto = trim(matches[1]);
		return true;
	}
	return false;
}

bool parseLabel(string strLine, string& strLabel)
{
	vector<string> matches;
	if ( match("^(.*)\\:$", strLine, &matches) )
	{
		strLabel = trim(matches[1]);
		return true;
	}
	return false;
}

void jslooper(vector<string>& lines)
{
	vector<string> labels, gotos;
	for (int i=0; i<lines.size(); i++)
	{
		string& line = lines[i];
		string strLabel, strGoto;

		if ( parseLabel( line, strLabel ) )
		{
			if ( find(labels.begin(), labels.end(), strLabel)==labels.end() )
				labels.push_back( strLabel );
		}
		if ( parseGoto(line, strGoto) )
		{
			if ( std::find(gotos.begin(), gotos.end(), strGoto)==gotos.end() )
				gotos.push_back( strGoto );
		}
	}
	if ( !gotos.empty() )
		for ( int i=0; i<labels.size(); i++)
		{
			if ( std::find(gotos.begin(), gotos.end(), labels[i])!=gotos.end() )
			{
				labels.erase(labels.begin()+i--);
			}
		}

	if ( labels.size() != 0 )
	{
		// some unreferenced labels
		for (int i=0; i<lines.size(); i++)
		{
			string& line = lines[i];
			string strLabel, strGoto;
			if ( parseLabel( line, strLabel ) )
			{
				if ( std::find(labels.begin(), labels.end(), strLabel)!=labels.end() )
				{
					lines.erase(lines.begin()+i--);
				}
			}
		}
	}
	if ( gotos.size() == 0 )
		return;

	/*
	int wPos = 0;
	while ( wPos != -1 )
	switch ( wPos )
	{
	  case 0:
	  .....
	}
	*/
	for (int i=0; i<lines.size(); i++)
	{
		string& line = lines[i];
		string strLabel, strGoto;
		if ( parseLabel( line, strLabel ) )
		{
			replace(strLabel, "loc_code_", "");
			line = string("  case 0x") + strLabel + ":";
		} else
		if ( parseGoto(line, strGoto) )
		{
			replace(strGoto, "loc_code_", "");
			if ( lines[i-1].find( "if" ) == string::npos )
			{
				line = format("    wPos = 0x%s;", strGoto.c_str());
				lines.insert(lines.begin()+i+1, "    continue;");
			}
			else
				line = format("      { wPos = 0x%s; continue; }", strGoto.c_str());
		} else
		{
			if ( line != "$" )
				line = string("  ") + line;
		}
	}
	lines.push_back("    wPos = -1;");
	lines.insert(lines.begin()+0, (jsta && jsf) ? "  var wPos = 0;" : "  int wPos = 0;" );
	lines.insert(lines.begin()+1, "  while (wPos != -1 && typeof(wPos) != \"undefined\" )");
	lines.insert(lines.begin()+2, "  switch (wPos)");
	lines.insert(lines.begin()+3, "  {");
	lines.insert(lines.begin()+4, "    case 0:");
	lines.push_back("  }");
	//lines.push_back("  return wPos;");
}

void jsloopkiller(vector<string>& code)
{
	vector<string> result;
	vector<string> function;
	string funcheader;
	src.reserve(20000);
	function.reserve(1000);

	bool bInProc = false;
	printf("Loopkiller...\n");

	for (int i=0; i<(int)code.size()-4; i++)
	{
		vector<string> matches;
		string& line = code[i];
		if ( match( "(function|void|WORD|BYTE)\\s*(.*)\\(\\)\\s*\\{\\}", line, &matches ) )
		{
			result.push_back( line );
			continue;
		}

		if ( match( "(function|void|WORD|BYTE)\\s*(.*)\\(\\)", line, &matches ) )
		{
			function.clear();
			funcheader = line;
			bInProc = true;
			continue;
		}

		if ( line == "}" )
		{
			result.push_back( funcheader );
			result.push_back( "{" );
			jslooper( function );
			result.insert(result.end(), function.begin(), function.end());
			bInProc = false;
		}

		if ( bInProc && line != "{" && line != "") 
			function.push_back( line );

		if ( !bInProc )
			result.push_back( line );

	}

	code = result;
}
int main(int argc, char* argv[])
{
	src.reserve(20000);
	code.reserve(20000);
	const char* f_src = "C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\goose_code.asm";
	const char* f_code = "C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\goose_code.cpp";
	const char* f_header = "C:\\Data\\Devel\\Github\\Work-in-progress\\AlleyCat\\Games\\goose\\goose_code.h";

#define LOOPKILLER
#ifdef LOOPKILLER
	const char* f_cpp = "C:\\Data\\Devel\\VC\\catdec\\catdec\\goose\\goose_code.cpp";
	const char* f_js = "C:\\Data\\Devel\\VC\\catdec\\catdec\\goose\\goose_code.js";

	FILE* _f = fopen(f_cpp, "r");
	char _line[1024] = {0};
	printf("Reading file...\n");
	while (!feof(_f))
	{
		fgets(_line, 1023, _f);
		if ( _line[0] )
			_line[strlen(_line)-1] = 0;
		/*
		string strLine(_line);
		strLine = trim(strLine);
		if (strLine.length() == 0)
			continue;
			*/
		code.push_back(string(_line));
	}
	fclose(_f);
	printf("Killing loops\n");
	jsloopkiller(code);
	printf("Writing...\n");
	_f = fopen(f_js, "w");
	for (int i=0; i<(int)code.size(); i++)
	{
		vector<string> matches;
		string& line = code[i];
		if ( line == "$" )
			continue;
		fprintf(_f, "%s\n", line.c_str());
	}
	fclose(_f);
	return 0;
#endif

	// "C:\\Data\\Work\\alley\\1\\cat_code.asm"
	// "C:\\Data\\Work\\alley\\2\\cat_code.cpp" 

	FILE* f = fopen(f_src, "r");
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

			//if (js )
				//procType = "Function";

			curFunction = matches[1];
			
			code.push_back(format("%s %s()", procType.c_str(), matches[1].c_str()));
			code.push_back("{");

			string fid = matches[1].c_str();
			replace(fid, "sub_", "0x");
			code.push_back(format("  STAT(%s);", fid.c_str()));

			if ( matches[1] == "sub_1A569" || matches[1] == "sub_1A86D" || matches[1] == "sub_1CDEF" || matches[1] == "sub_1D05B")
			{
				code.push_back(format("%s:", safelabel.c_str()));
			}

			if ( matches[1] == "sub_3E2" || matches[1] == "sub_394" || matches[1] == "sub_349" || matches[1] == "sub_2FE" || 
				matches[1] == "sub_3339" || matches[1] == "sub_363D" || matches[1] == "sub_5BBF" || matches[1] == "sub_5E2B" ||
				matches[1] == "sub_CF" || matches[1] == "sub_529" )
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
			if ( matches[1] == "loc_code_28C" )
			{
				int f = 9;
			}
			code.push_back( format("%s:", matches[1].c_str()) );
			continue;
		} 

		if ( match("^retn$", line, &matches) )
		{
			code.push_back( "  return;" );
			continue;
		} 

		if ( match("^retn\\s*(.*)$", line, &matches) )
		{
			code.push_back( format("  _retn(%s);", matches[1].c_str()) );

			code.push_back( "  return;" );
			continue;
		} 

		// single arg instruction
		if ( match("^(push|pop|int|div)[\\s]+(.*)$", line, &matches) )
		{
			if ( js && matches[1] == "pop" )
				code.push_back( string("  ") + jsassign(_value(matches[2]), "_pop()"));
			else
				code.push_back( format("  _%s(%s);", matches[1].c_str(), rvalue(matches[2]).c_str()) );
			continue;
		}

		// zero arg instruction
		if ( match("^(cli|sti|std|stc|ctc|cld|aaa|cbw|lodsw|lodsb|stosw|movsw|movsb|clc|sahf|lahf|popf|pushf)$", line, &matches) )
		{
			code.push_back( format("  _%s();", matches[1].c_str() ) );
			continue;
		}

		if ( match("^(out|in|xchg|rcr|rcl)[\\s]+(.*),\\s*(.*)$", line, &matches) )
		{
			if ( matches[1] == "in" )
			{
				code.push_back( format("  %s = _in(%s);", rvalue(matches[2]).c_str(), rvalue(matches[3]).c_str() ) );
				continue;
			} 
			if ( matches[1] == "rcr" || matches[1] == "rcl" )
			{
				string strCarry = updateCarry(i-1);
				if ( strCarry.empty() )
					code.push_back("  fix_code(); // fix carry flag");
				else
					code.insert(code.end()-1, strCarry);
			}

			code.push_back( format("  _%s(%s, %s);", matches[1].c_str(), rvalue(matches[2]).c_str(), rvalue(matches[3]).c_str() ) );
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
			string target = _value(matches[1]);
			string source = _value(matches[2]);
			if (matches[2] == "[bx+244h]" )
			{
				int f = 9;
			}
			if ( match("^[abcd][hl]$", target) || match("^r8\\[[abcd][hl]\\]$", target))
				replace(source, "*(WORD*)&", "");
			if ( match("^[abcd][hl]$", source) || match("^r8\\[[abcd][hl]\\]$", target))
				replace(target, "*(WORD*)&", "");
			if ( js )
				code.push_back( string("  ") + jsassign(target, source));
			else
				code.push_back( format("  %s = %s;", target.c_str(), source.c_str()));
			continue;
		}

		// ALU
		if ( match("^dec[\\s]+(.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "-1"));
			else
				code.push_back( format("  %s--;", safeop(rvalue(matches[1])).c_str() ) );
			continue;
		}

		if ( match("^inc[\\s]+(.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "+ 1"));
			else
				code.push_back( format("  %s++;", safeop(rvalue(matches[1])).c_str() ) );
			continue;
		}

		if ( match("^sub\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{

			if ( matches[1] == matches[2] )
			{
				if ( js )
					code.push_back( string("  ") + jsassign( matches[1], "0" ));
				else
					code.push_back( format("  %s = 0;", matches[1].c_str()));
			}
			else
			{
				if ( js )
					code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "-", rvalue(matches[2])));
				else
					code.push_back( format("  %s -= %s;", rvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			}
			continue;
		} 

		if ( match("^add\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{
			if ( matches[2] == "[bx+571h]" )
				int f = 9;
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "+", rvalue(matches[2])));
			else
				code.push_back( format("  %s += %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}

		if ( match("^adc\\s+([^,]+),\\s*([^,]+)", line, &matches) )
		{
			code.push_back("  unknown_condition(); // verify cf");
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "+", rvalue(matches[2]), "+ cf"));
			else
				code.push_back(format("  %s += %s + cf;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		} 
		if ( match("^xor\\s+(.*),\\s*(.*)", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "^", rvalue(matches[2])));
			else
				code.push_back( format("  %s ^= %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}
		if ( match("^and[\\s]+(.*),\\s*(.*)", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "&", rvalue(matches[2])));
			else
				code.push_back( format("  %s &= %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}
		if ( match("^or[\\s]+(.*),\\s*(.*)", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "|", rvalue(matches[2])));
			else
				code.push_back( format("  %s |= %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}
		if ( match("^shl[\\s]+(.*), (.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), "<<", rvalue(matches[2])));
			else
				code.push_back( format("  %s <<= %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}
		if ( match("^shr[\\s]+(.*), (.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), rvalue(matches[1]), ">>", rvalue(matches[2])));
			else
				code.push_back( format("  %s >>= %s;", lvalue(matches[1]).c_str(), rvalue(matches[2]).c_str()));
			continue;
		}
		if ( match("^not[\\s]+(.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), "~", rvalue(matches[1])));
			else
				code.push_back( format("  %s = ~%s;", lvalue(matches[1]).c_str(), rvalue(matches[1]).c_str()));
			continue;
		}
		if ( match("^neg[\\s]+(.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign(lvalue(matches[1]), "-", rvalue(matches[1])));
			else
				code.push_back( format("  %s = -%s;", lvalue(matches[1]).c_str(), rvalue(matches[1]).c_str()));
			continue;
		}
		if ( match("^mul[\\s]+(.*)$", line, &matches) )
		{
			if ( js )
				code.push_back( string("  ") + jsassign("ax", matches[1], "*", "al"));
			else
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
				code.push_back( format("  goto %s;", rvalue(matches[2]).c_str()));
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
			if ( !target.empty() )
			{
				replace(target, "_code_", "_");
				code.push_back( format("  %s();", target.c_str()));
				continue;
			}
		}

		// loops
		if ( match("^loop[\\s]+(.*)$", line, &matches) )
		{
			code.push_back( format("  if ( --%s )", _value("cx").c_str() ) );
			code.push_back( format("    goto %s;", rvalue(matches[1]).c_str()));
			continue;
		}
		if ( match("^loope[\\s]+(.*)$", line, &matches) )
		{
			//string strPrev = src[i-1];
			string condition = getCondition("jz", i-1);
			if ( condition.empty() )
				condition = "unknown_condition()";

			code.push_back( format("  if ( --%s && (%s) )", _value("cx").c_str(), condition.c_str()));
			code.push_back( format("    goto %s;", rvalue(matches[1]).c_str()));
			continue;
		} 
		if ( match("^loopne[\\s]+(.*)$", line, &matches) )
		{
//			string strPrev = src[i-1];
			string condition = getCondition("jnz", i-1);
			if ( condition.empty() )
				condition = "unknown_condition()";

			code.push_back( format("  if ( --%s && (%s) )", _value("cx").c_str(), condition.c_str()));
			code.push_back( format("    goto %s;", rvalue(matches[1]).c_str()));
			continue;
		} 

		// conditional jump
		if ( line.substr(0, 3) == "jge" )
		{
			int f = 9;
		}
		string tmp = line;
		replace(tmp, "short ", "");
		replace(tmp, "short\t", "");
		bool bCondit = match("^(jbe|jz|jnz|ja|jb|jnb|jle|jg|jge|jns|jl|js|jge)\\s+(.*)$", tmp, &matches);
		if ( !bCondit )
			bCondit = match("^(jge)\\s+(.*)$", tmp, &matches);
		if ( bCondit )
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
			if ( match("^locret", matches[2]) )
				code.push_back("    return;");
			else
				code.push_back( format("    goto %s;", rvalue(matches[2]).c_str()));
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
		if ( match("=\\sword\\sptr", line) )
		{
			code.push_back( format("  // %s", line.c_str()));
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

	/*
	int nLines[] = {571, 4716, 4764, 0};
	for (int i=0; nLines[i]; i++)
	{
		string& line = code[nLines[i]-3];
		_ASSERT( line.find("_data") != string::npos );
		replace( line, "_data[", "_video[0*");
	}*/
	printf("Optimizing...\n");
	code.insert(code.begin(), "#include \"cat_code.h\"");
	code.insert(code.begin()+1, "");
	bool bAllowed = false;
	string curFunc;
	bool bFilter = false;
	const char *filter[] = {
"start", "sub_700", "sub_70D", "sub_8E5", "sub_1124", "sub_1145", "sub_11E3", "sub_13AA",
"sub_13E8", "sub_1419", "sub_1830", "sub_1D31", "sub_1E40", "sub_2330", "sub_2690", "sub_26B3",
"sub_26DA", "sub_26E1", "sub_26E8", "sub_26F2", "sub_26FC", "sub_2739", "sub_2A30", "sub_2A68",
"sub_2B24", "sub_2B9E", "sub_2C3D", "sub_2C84", "sub_2CB0", "sub_2D35", "sub_2D9D", "sub_2DCA",
"sub_2DFD", "sub_5450", "sub_5C60", "sub_5CB0", "sub_5CB0_helper_loc_code_5D54", "sub_5CB0_loop",
"sub_5DD4", "sub_5E3B", "sub_5EE5", "sub_1B7A", "sub_1020", "sub_F87", "sub_2D70",
"sub_FC9", "sub_20F5", "sub_1608", "sub_22F7", "sub_1069", "sub_2E10", NULL };
	const char *dummy[] = {
"sub_5AC2", "sub_59CB", "sub_2051", "sub_20E1", "sub_209B", "sub_1799", "sub_3C43", "sub_30FA", 
"sub_590E", "sub_16C6", "sub_1657", "sub_17AD", "sub_2136", "sub_2E29", "sub_1922", "sub_10DD", 
"sub_1166", "sub_5FCD", "sub_5FB1", "sub_5FE5", "sub_5F97", "sub_34A0", "sub_597F", "sub_1D6E", 
"sub_5C9E", "sub_53B0", "sub_5B21", "sub_2E10", 
"sub_3445", "sub_58F8", "sub_59A3", "sub_591F", "sub_347F", NULL };

	bool bVideoProc = false;

	for (int i=0; i<(int)code.size()-4; i++)
	{
		string& line = code[i];
		vector<string> matches;		
		if ( match( "(void|WORD|BYTE)\\s*(.*)\\(\\)", code[i+0], &matches ) )
		{
			curFunc = matches[2];
			if (curFunc == "sub_4A0" || curFunc == "sub_29E1" || curFunc == "sub_2CCC" ||
				curFunc == "sub_2D35" || curFunc == "sub_3339")
				bVideoProc = true;	
			else bVideoProc = false;


			if ( !bFilter )
				bAllowed = true;
			else
				for ( int j=0; filter[j]; j++)
					if ( curFunc == filter[j] )
						bAllowed = true;

			if (/*jsta && jsf*/ js)
				line = format("function %s()", curFunc.c_str());
		}
		if ( jsta )
		{
			/*
			for (int i=1; i<line.length(); i++)
			{
				if (line[i] == 'h' || line[i] == 'l') && (line[i-1)

			}
			*/
			/*
			//replace(line, "return;", "return -1;");
			replace(line, "include", "{INCLUDE}");
			replace(line, "clc", "{c-l-c}");
			replace(line, "cld", "{c-l-d}");
			replace(line, "cli", "{c-l-i}");
			replace(line, "xchg", "{x-c-h-g}");

			replace(line, "ah", "{a-h}"); replace(line, "al", "{a-l}"); replace(line, "ax", "{a-x}");
			replace(line, "bh", "{b-h}"); replace(line, "bl", "{b-l}"); replace(line, "bx", "{b-x}");
			replace(line, "ch", "{c-h}"); replace(line, "cl", "{c-l}"); replace(line, "cx", "{c-x}");
			replace(line, "dh", "{d-h}"); replace(line, "dl", "{d-l}"); replace(line, "dx", "{d-x}");

			replace(line, "{a-h}", "r8[ah]"); replace(line, "{a-l}", "r8[al]"); replace(line, "{a-x}", "r16[ax]");
			replace(line, "{b-h}", "r8[bh]"); replace(line, "{b-l}", "r8[bl]"); replace(line, "{b-x}", "r16[bx]");
			replace(line, "{c-h}", "r8[ch]"); replace(line, "{c-l}", "r8[cl]"); replace(line, "{c-x}", "r16[cx]");
			replace(line, "{d-h}", "r8[dh]"); replace(line, "{d-l}", "r8[dl]"); replace(line, "{d-x}", "r16[dx]");

			replace(line, "{c-l-c}", "clc");
			replace(line, "{c-l-d}", "cld");
			replace(line, "{c-l-i}", "cli");
			replace(line, "{x-c-h-g}", "xchg");
			replace(line, "{INCLUDE}", "include");
			*/

			/*
			int p = 0;
			while ( (p = line.find("*(WORD*)&_data[")) != string::npos ) 
			{
				line.replace(p, 15, "");
				

			*(WORD*)&_data
			}*/
		}
		/*
		if ( curFunc == "sub_2D35" )
		{
			replace(line, "_data[es*16+di]", "_video[di]");
		}*/
		if ( !bAllowed )
		{
			if ( !line.empty() && line[0] == '#' )
				continue;
			line = "$";
			//code.erase(code.begin()+i--);
			continue;
		}

		replace(line, "ds*16+", "");
		replace(line, "_data[es*16+0x0FFFE]", "0xff");
		if ( bVideoProc )
			replace(line, "_data[es*16+", "_video[");
		//replace(line, "if ( sub_13D8() )", ""

		if ( line.find( "loc_code_5DCA:" ) != string::npos )
		{
			code.insert(code.begin()+i+1, "  tick();"); 
			code.insert(code.begin()+i+1, "  Sleep(5);"); 
			i+=2;
		}
		if ( line.find( "sub_13D8") != string::npos )
		{
			if ( line.find("if") != string::npos )
			{
				code[i+0] = "$";
				code[i+1] = "$";
				//code.erase(code.begin()+i);
				//code.erase(code.begin()+i+1);
				i--;
			} else
				line = "zf = 0;";
		}
		if ( line.find("loc_code_1554") != string::npos )
		{
			line = "//" + line;
		}
		/*
		if ( line.find("sub_5CB0();") != string::npos )
		{
			code.insert(code.begin() + ++i, "}");
			bAllowed = false;
		}*/
		if ( code[i+0] == "}" )
		{
			bAllowed = false;
		}
		continue;

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

		//continue;
		if ( match( "if",    code[i+0] ) && 
			 match( "goto",  code[i+1] ) &&
			 match( "goto",  code[i+2] ) &&
			 match( "loc_",  code[i+3] ) )
		{
			string strCond, strComment, strJumpTrue, strJumpFalse, strLabel;
			//string strTemp = code[i+0];
			//replace(strTemp, "*(WORD*)", "__WORD");
			if ( !parseIf(code[i+0], strCond, strComment ) )
				continue;
			/*
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;
				*/
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
			if ( !strComment.empty() )
				strComment = string("// !") + strComment;

			code[i+0] = format("  if ( %s ) %s", strCond.c_str(), strComment.c_str());
			code[i+1] = format("    goto %s;", strJumpFalse.c_str());
			code[i+2] = "";
		}

		if ( match( "if",    code[i+0] ) && 
			 match( "goto",  code[i+1] ) &&
			 match( "loc_",  code[i+3] ) )
		{
			string strCond, strComment, strJumpTrue, strCode, strLabel;
			//string strTemp = code[i+0];
			//replace(strTemp, "*(WORD*)", "__WORD");
			if ( !parseIf(code[i+0], strCond, strComment ) )
				continue;
/*
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;*/
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
			if ( !strComment.empty() )
				strComment = string("// !") + strComment;

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
			if ( !parseIf(code[i+0], strCond, strComment ) )
				continue;
/*
			string strTemp = code[i+0];
			replace(strTemp, "*(WORD*)", "__WORD");
			if ( match( "if\\s\\((.*)\\)(.*)$", strTemp, &matches) )
			{
				strCond = matches[1];
				replace(strCond, "__WORD", "*(WORD*)");
				strComment = matches[2];
			} else
				continue;*/
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
			if ( !strComment.empty() )
				strComment = string("// !") + strComment;

			code[i+0] = format("  if ( %s ) %s", strCond.c_str(), strComment.c_str());
			code[i+1] = "  {";
			code[i+2] = format("  %s", strCode1.c_str());
			code[i+3] = format("  %s", strCode2.c_str());
			string tmp = code[i+4];
			code[i+4] = "  }";
			code.insert(code.begin()+i+5, tmp);
		}

	}
	if ( bFilter )
	for (int j=0; dummy[j]; j++)
		code.push_back( format(jsta ? "function %s() {} " : "void %s() {}", dummy[j]));

	// Looper
	if ( jslk )
	{
		jsloopkiller(code);
	}

	printf("Writing...\n");
	FILE* fo = fopen(f_code, "w");
	FILE* fh = f_header ? fopen(f_header, "w") : NULL;
	for (int i=0; i<(int)code.size(); i++)
	{
		vector<string> matches;
		string& line = code[i];
		if ( line == "$" )
			continue;
		if ( fh )
		if ( match("^(void|BYTE|WORD)\\s(.*)\\(\\)$", line, &matches) )
			fprintf(fh, "%s %s();\n", matches[1].c_str(), matches[2].c_str());
		fprintf(fo, "%s\n", line.c_str());
	}
	fclose(fo);
	if ( fh )
		fclose(fh);

	return 0;
}


// http://www.csc.depauw.edu/~bhoward/asmtut/asmtut7.html