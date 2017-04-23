// asmparser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <regex>
#include <vector>
#include <map>
#include <typeinfo>
#include <sstream>
#include <iomanip>
#include <functional>
#include <ctype.h>

using namespace std;

#define CheckEnum2(s, e) if (str==s) return e;
#define CheckEnum(e) if (str==#e) return e;

unsigned char data[1024*1024];
unsigned char video[1024*1024];

class CUtils
{
	static std::map<string, regex> m_mapCache;

public:
	static bool match(const string& strRegex, const string& strInput, vector<string>& arrMatches)
	{
		auto i = m_mapCache.find(strRegex);
		if ( i == m_mapCache.end() )
		{
			regex newRegex(strRegex, std::regex_constants::ECMAScript);
			m_mapCache.insert(make_pair<string, regex>(strRegex, newRegex));

			return match(newRegex, strInput, arrMatches);
		}

		return match(i->second, strInput, arrMatches);
	}

	static bool match(const regex& regexMatch, const string& strInput, vector<string>& arrMatches)
	{
		_ASSERT(arrMatches.empty());

		cmatch results;
		if ( !regex_match(strInput.c_str(), results, regexMatch) )
			return false;

		for (auto it = ++results.begin(); it != results.end(); it++)
			arrMatches.push_back(it->str().c_str()); // string(it->first, it->second).c_str());

		return true;
	}

	static bool match(const string& strRegex, const string& strInput)
	{
		auto i = m_mapCache.find(strRegex);
		if ( i == m_mapCache.end() )
		{
			regex newRegex(strRegex, std::regex_constants::ECMAScript);
			m_mapCache.insert(make_pair<string, regex>(strRegex, newRegex));

			return match(newRegex, strInput);
		}

		return match(i->second, strInput);
	}

	static bool match(const regex& regexMatch, const string& strInput)
	{
		return regex_match(strInput.c_str(), regexMatch);
	}

	static bool replacefirst(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);
		if(start_pos == std::string::npos)	
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	static bool replace(std::string& str, const std::string& from, const std::string& to) 
	{
		while ( replacefirst( str, from, to ) );
		return true;
	}

	static bool ParseLiteral(const string& _str, int& nValue)
	{
		string str = Trim(_str);
		if ( match("^\\d+$", str.c_str()) )
		{
			nValue = atoi(str.c_str());
			return true;
		}

		vector<string> matches;

		if ( match("^([0-9A-F]+)h$", str.c_str(), matches) )
		{
			std::stringstream converter(matches[0]);
			converter >> std::hex >> nValue;
			return true;
		}
		
		if ( match("^0x([0-9A-F]+)$", str.c_str(), matches) )
		{
			std::stringstream converter(matches[0]);
			converter >> std::hex >> nValue;
			return true;
		}

		return false;
	}

	static int ParseLiteral(const string& str)
	{
		int nAux;

		bool bOk = ParseLiteral(str, nAux);
		_ASSERT(bOk);

		return nAux;
	}

	static std::string Trim(std::string str)
	{
		size_t first = str.find_first_not_of(' ');
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}
};

std::map<string, regex> CUtils::m_mapCache;

class CValue
{
public:
	enum EType {
		ah, al, ax,
		bh, bl, bx,
		ch, cl, cx,
		dh, dl, dx,
		ds, es, si, di, cs, bp, sp,
		
		constant,
		
		wordptr, byteptr, wordptrasbyte,
		byteptrval, wordptrval,
		
		si_plus,
		bx_plus,
		bx_plus_si,
		bp_plus,
		di_plus,

		codeword,
		codebyte,

		es_ptr_di,
		bx_plus_di,
		es_ptr_di_plus,

		invalid
	};

	enum ERegLength 
	{
		r8, r16, unknown
	};

public:
	EType m_eType;
	ERegLength m_eRegLength;

	shared_ptr<CValue> m_value;
	int m_nValue;	

public:
	CValue()
	{
		m_eRegLength = unknown;
		m_eType = invalid;
	}

	CValue(const std::string& str, ERegLength eRegLength = unknown)
	{
		m_nValue = 0;
		Parse(str, eRegLength);
	}

	void Parse(const std::string& str, ERegLength eRegLength = unknown)
	{
		m_eRegLength = unknown;
		std::string value = CUtils::Trim(str);
		
		m_eType = RegisterType8(value);
		
		if (m_eType != invalid)
		{
			m_eRegLength = r8;
			return;
		}

		m_eType = RegisterType16(value);
		
		if (m_eType != invalid)
		{
			m_eRegLength = r16;
			return;
		}

		if (CUtils::ParseLiteral(str, m_nValue))
		{
			if ( CUtils::match("^[0-9A-F]{2}h$", value.c_str()) )
				m_eRegLength = r8;
			if ( CUtils::match("^0[0-9A-F]{2}h$", value.c_str()) )
				m_eRegLength = r8;
			if ( CUtils::match("^0[0-9A-F]{4}h$", value.c_str()) )
				m_eRegLength = r16;
			
			m_eType = constant;
			return;
		}

		if ( str == "seg dseg" )
		{
			m_nValue = 0;
			m_eType = constant;
			return;
		}

		vector<string> matches;
		if ( CUtils::match("^word_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptr; // urcite ptr?
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^byte ptr \\[(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = byteptrval;
			m_eRegLength = r16;
			m_value = make_shared<CValue>(matches[0]);
			// TODO: HOPLA TOTO JE PTR
			// iba castujeme na byte, nepotrebujeme
			//Parse(matches[0]);
			//m_eRegLength = r8;
			return;
		}

		if ( CUtils::match("^word ptr \\[(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = wordptrval;
			m_eRegLength = r16;
			m_value = make_shared<CValue>(matches[0]);
			return;
		}

		if ( CUtils::match("^byte ptr word_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptrasbyte;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^byte_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = byteptr;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^\\[(.*)\\]$", value.c_str(), matches) )
		{
			_ASSERT(eRegLength != unknown);
			if ( eRegLength == r8 )
			{
				m_value = make_shared<CValue>(matches[0]);
				m_eType = byteptrval;
				return;
			}
			if ( eRegLength == r16 )
			{
				m_value = make_shared<CValue>(matches[0]);
				m_eType = wordptrval;
				return;
			}
		}

		if ( CUtils::match("^si\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = si_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( value == "bx+di" )
		{
			m_eType = bx_plus_di;
			return;
		}

		if ( CUtils::match("^bx\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = bx_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bx\\-(.*)$", value.c_str(), matches) )
		{
			m_eType = bx_plus;
			m_nValue = -CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^di\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = di_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^si\\-(.*)$", value.c_str(), matches) )
		{
			m_eType = si_plus;
			m_nValue = -CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+arg_(.*)$", value.c_str(), matches) )
		{
			m_eType = bp_plus;
			m_nValue = CUtils::ParseLiteral("0x"+matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+var_(.*)$", value.c_str(), matches) )
		{
			m_eType = bp_plus;
			m_nValue = -CUtils::ParseLiteral("0x"+matches[0]);
			return;
		}

		if ( CUtils::match("^cs:word_code_(.*)$", value.c_str(), matches) )
		{
			m_eType = codeword;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^cs:byte_code_(.*)$", value.c_str(), matches) )
		{
			m_eType = codebyte;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( value == "es:[di]" )
		{
			m_eType = es_ptr_di;
			return;
		}

		if ( CUtils::match("^es:\\[di\\+(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = es_ptr_di_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = bp_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		printf("%s\n", str.c_str());
		int f = 9;
		//Fix(*this);
	}

	static void SameOperands(CValue& op1, CValue& op2, string str1, string str2)
	{
		if (str1.length() == 2)
		{
			op1.Parse(str1);
			op2.Parse(str2, op1.GetRegisterLength());
		} else
		{
			op2.Parse(str2);
			op1.Parse(str1, op2.GetRegisterLength());
		}
	}

	static EType RegisterType8(std::string str)
	{
		CheckEnum(ah);		CheckEnum(al);
		CheckEnum(bh);		CheckEnum(bl);
		CheckEnum(ch);		CheckEnum(cl);
		CheckEnum(dh);		CheckEnum(dl);
		return invalid;
	}

	static EType RegisterType16(std::string str)
	{
		CheckEnum(ax);		CheckEnum(bx);		CheckEnum(cx);		CheckEnum(dx);
		CheckEnum(ds);		CheckEnum(es);		CheckEnum(si);		CheckEnum(di);
		CheckEnum(cs);		CheckEnum(bp);		CheckEnum(sp);
		CheckEnum2("bx+si", bx_plus_si);
		return invalid;
	}

	ERegLength GetRegisterLength()
	{
		return m_eRegLength;
	}

	/*
	void Fix(string& key)
	{
		vector<string> matches;
		string out = key;

		if ( key == "ax" || key == "bx" || key == "cx" || key == "dx" )
			return string("r16[")+key+"]";
		if ( key == "ah" || key == "bh" || key == "ch" || key == "dh" ||
			 key == "al" || key == "bl" || key == "cl" || key == "dl" )
			return string("r8[")+key+"]";

		// decimal
		if ( CUtils::match("^([0-9]*)$", key.c_str(), &matches) )
			return out;
		// hex
		if ( CUtils::match("^([0-9A-F]+)h$", key.c_str(), &matches) )
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
	}*/
};

class CLabel : public string
{
public:
	CLabel(const string& str) : string(str)
	{
		CUtils::replace(*this, "short ", "");
		CUtils::replace(*this, "_code_", "_");
	}
};

class CMachine;

class CInstruction
{
public:
	virtual ~CInstruction() {}
	virtual void Eval(CMachine& m) { _ASSERT(0); }
};

class CIFunction : public CInstruction
{
public:
	enum EBoundary {
		Begin,
		End
	};

	string m_strName;
	EBoundary m_eBoundary;

public:
	CIFunction(EBoundary eBoundary, string strName) : 
	  m_eBoundary(eBoundary), m_strName(strName)
	{
	}

	CIFunction(EBoundary eBoundary) : 
	  m_eBoundary(eBoundary)
	{
	}
};

class CINop : public CInstruction
{
public:
	string m_strComment;

public:
	CINop()
	{
	}

	CINop(const string& strComment) : m_strComment(strComment)	
	{
	}

	virtual void Eval(CMachine& m) {}
};

class CILabel : public CInstruction
{
public:
	CLabel m_label;

public:
	CILabel(string strName) : m_label(strName)
	{
	}

	virtual void Eval(CMachine& m) {}
};

class CIReturn : public CInstruction
{
public:
	int m_nReduceStack;

public:
	CIReturn(int nReduceStack = 0) : m_nReduceStack(nReduceStack)
	{
	}

	virtual void Eval(CMachine& m);
};

class CIZeroArgOp : public CInstruction
{
public:
	enum EType {
		cli, sti, _std, stc, ctc, cld, aaa, cbw, lodsw, lodsb, stosw, movsw, movsb, clc, sahf, lahf, popf, pushf,
		invalid
	};

public:
	EType m_eType;

public:
	CIZeroArgOp(EType eType) : m_eType(eType)
	{
	}

	static EType GetType(string str)
	{
		CheckEnum(cli);		CheckEnum(sti);		CheckEnum2("std", _std);	CheckEnum(stc);
		CheckEnum(ctc);		CheckEnum(cld);		CheckEnum(aaa);		CheckEnum(cbw);
		CheckEnum(lodsw);	CheckEnum(lodsb);	CheckEnum(stosw);	CheckEnum(movsw);
		CheckEnum(movsb);	CheckEnum(clc);		CheckEnum(sahf);	CheckEnum(lahf);
		CheckEnum(popf);	CheckEnum(pushf);
		_ASSERT(0);
		return invalid;
	}
	virtual void Eval(CMachine& m);
};

class CISingleArgOp : public CInstruction
{
public:
	enum EType {
		push,
		pop,
		interrupt,
		div,
		invalid
	};

public:
	EType m_eType;
	CValue m_rvalue;

public:
	CISingleArgOp(EType eType, const CValue& rvalue) : 
	  m_eType(eType), m_rvalue(rvalue)
	{
	}

	static EType GetType(string str)
	{
		CheckEnum(push);	CheckEnum(pop);	CheckEnum(div);
		CheckEnum2("int", interrupt);
		_ASSERT(0);
		return invalid;
	}
	virtual void Eval(CMachine& m);
};

class CITwoArgOp : public CInstruction
{
public:
	enum EType {
		out, in, xchg, rcr, rcl, invalid
	};

public:
	EType m_eType;
	CValue m_rvalue1;
	CValue m_rvalue2;

public:
	CITwoArgOp(EType eType, const CValue& rvalue1, const CValue& rvalue2) : 
	  m_eType(eType), m_rvalue1(rvalue1), m_rvalue2(rvalue2)
	{
	}

	static EType GetType(string str)
	{
		CheckEnum(out);	CheckEnum(in); CheckEnum(xchg); CheckEnum(rcr); CheckEnum(rcl);
		_ASSERT(0);
		return invalid;
	}

	virtual void Eval(CMachine& m);
};

class CIString : public CInstruction
{
public:
	enum ERule
	{
		rep,
		repne,
		invalidrule
	};

	enum EOperation
	{
		stosb, lodsb, stosw, lodsw, movsw, movsb,
		invalidop
	};

public:
	ERule m_rule;
	EOperation m_operation;

public:
	CIString(ERule eRule, EOperation eOperation) : 
	  m_rule(eRule), m_operation(eOperation)
	{
	}

	static ERule GetRule(string str)
	{
		CheckEnum(rep);	CheckEnum(repne);
		_ASSERT(0);
		return invalidrule;
	}

	static EOperation GetOperation(string str)
	{
		CheckEnum(stosb);	CheckEnum(lodsb);
		CheckEnum(stosw);	CheckEnum(lodsw);
		CheckEnum(movsw);	CheckEnum(movsb);
		_ASSERT(0);
		return invalidop;
	}

	virtual void Eval(CMachine& m);
	static void EvalStosb(CMachine& m);
	static void EvalStosw(CMachine& m);
};

class CIAssignment : public CInstruction
{
public:
	CValue m_valueFrom;
	CValue m_valueTo;

public:
	CIAssignment(const CValue& valueTo, const CValue& valueFrom) : 
	  m_valueFrom(valueFrom), m_valueTo(valueTo)
	{
	}

	virtual void Eval(CMachine& m);
};

class CIAlu : public CInstruction
{
public:
	enum EType
	{
		Increment,
		Decrement,
		Add,
		Sub,
		Xor,
		And,
		Or,
		Not,
		Neg,
		AddWithCarry,
		Shl,
		Shr,
		Sar,
		Mul
	};

public:
	CValue m_op1;
	CValue m_op2;
	EType m_eType;

public:
	CIAlu(EType eType, const CValue& op1) : 
	  m_eType(eType), m_op1(op1)
	{
	}

	CIAlu(EType eType, const CValue& op1, const CValue& op2) : 
	  m_eType(eType), m_op1(op1), m_op2(op2)
	{
	}

	virtual void Eval(CMachine& m);
};

class CIJump : public CInstruction
{
public:
	CLabel m_label;

public:
	CIJump(const CLabel& label) : 
	  m_label(label)
	{
	}
};

class CIConditionalJump : public CInstruction
{
public:
	enum EType {
		jbe, jz, jnz, ja, jb, jnb, jle, jg, jge, jns, jl, js, jcxz,
		invalid
	};

public:
	EType m_eType;
	CLabel m_label;

public:
	CIConditionalJump(EType eType, const CLabel& label) : 
	  m_eType(eType), m_label(label)
	{
	}

  	static EType GetType(string str)
	{
		CheckEnum(jbe);	CheckEnum(jz); CheckEnum(jnz); CheckEnum(ja); CheckEnum(jb);
		CheckEnum(jnb);	CheckEnum(jle); CheckEnum(jg); CheckEnum(jge); CheckEnum(jns);
		CheckEnum(jl);	CheckEnum(js); CheckEnum(jcxz);
		_ASSERT(0);
		return invalid;
	}

	virtual void Eval(CMachine& m);

	static bool SatisfiesCondition1(CMachine& m, CIConditionalJump::EType eType);
	static bool SatisfiesCondition2(CMachine& m, CIConditionalJump::EType eType);
};

class CICall : public CInstruction
{
public:
	CLabel m_label;

public:
	CICall(const CLabel& label) : 
	  m_label(label)
	{
	}

	virtual void Eval(CMachine& m);
};

class CISwitch : public CInstruction
{
public:
	CLabel m_label;
	CValue m_reg;

public:
	CISwitch(const CLabel& label, const CValue& reg) : 
	  m_label(label), m_reg(reg)
	{
	}
};

class CILoop : public CInstruction
{
public:
	enum EType {
		Loop, WhileEqual, WhileNotEqual
	};

public:
	EType m_eType;
	CLabel m_label;

public:
	CILoop(EType eType, const CLabel& label) : 
	  m_eType(eType), m_label(label)
	{
	}
};

class CICompare : public CInstruction
{
public:
	CValue m_op1;
	CValue m_op2;

public:
	CICompare(const CValue& op1, const CValue& op2) : 
	  m_op1(op1), m_op2(op2)
	{
	}

	virtual void Eval(CMachine& m);
};

class CITest : public CInstruction
{
public:
	CValue m_op1;
	CValue m_op2;

public:
	CITest(const CValue& op1, const CValue& op2) : 
	  m_op1(op1), m_op2(op2)
	{
	}
};

class CIData : public CInstruction
{
public:
	enum EType {
		WordPtr, Word, Byte,
		Function
	};

public:
	EType m_eType;
	string m_strVariableName;
	unsigned int m_nValue;
	string m_strFunction;

public:
	CIData(EType eType, const string& strValue) : 
	  m_eType(eType), m_strVariableName(strValue)
	{
	}

	CIData(EType eType, const string& strVariableName, int nValue) : 
	  m_eType(eType), m_strVariableName(strVariableName), m_nValue(nValue)
	{
	}

	CIData(EType eType, const string& strVariableName, const string& strFunction) : 
	  m_eType(eType), m_strVariableName(strVariableName), m_strFunction(strFunction)
	{
		_ASSERT(m_eType == Function);
	}
};


// Matchers
class CInstructionMatcher
{
public:
	virtual shared_ptr<CInstruction> Match(string strLine) = 0;
};

class CIMFunction : public CInstructionMatcher
{
public:
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^([\\w]*)[\\s]*proc\\s(near|far)", strLine, arrMatches) )
		{
			string strFunctionName = arrMatches[0];
			CUtils::replace(strFunctionName, "_code_", "_");

			return make_shared<CIFunction>(CIFunction::Begin, strFunctionName);
		}

		if ( CUtils::match("^([\\w]*)[\\s]*endp$", strLine, arrMatches) )
		{
			return make_shared<CIFunction>(CIFunction::End);
		}

		return nullptr;
	}
};

class CIMLabel : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^(locret[\\w]*):$", strLine, arrMatches) )
		{
			return make_shared<CINop>();
		}

		if ( CUtils::match("^(loc[\\w]*):$", strLine, arrMatches) )
		{
			return make_shared<CILabel>(arrMatches[0]);
		}

		return nullptr;
	}
};

class CIMReturn : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^retn$", strLine, arrMatches) )
		{
			return make_shared<CIReturn>();
		}

		if ( CUtils::match("^iret$", strLine, arrMatches) )
		{
			return make_shared<CIReturn>();
		}

		if ( CUtils::match("^retn\\s*(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIReturn>(CUtils::ParseLiteral(arrMatches[0]));
		}

		return nullptr;
	}
};

class CIMFixedArgOp : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^(push|pop|int|div)[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CISingleArgOp>(CISingleArgOp::GetType(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^(cli|sti|std|stc|ctc|cld|aaa|cbw|lodsw|lodsb|stosw|movsw|movsb|clc|sahf|lahf|popf|pushf)$", strLine, arrMatches) )
		{
			return make_shared<CIZeroArgOp>(CIZeroArgOp::GetType(arrMatches[0]));
		}

		if ( CUtils::match("^(out|in|xchg|rcr|rcl)[\\s]+(.*),\\s*(.*)$", strLine, arrMatches) )
		{
			return make_shared<CITwoArgOp>(CITwoArgOp::GetType(arrMatches[0]), CValue(arrMatches[1]), CValue(arrMatches[2]));
		}

		return nullptr;
	}
};

class CIMStringOp : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^(rep|repne)\\s+(stosb|lodsb|stosw|lodsw|movsw|movsb)$", strLine, arrMatches) )
		{
			return make_shared<CIString>(CIString::GetRule(arrMatches[0]), CIString::GetOperation(arrMatches[1]));
		}

		return nullptr;
	}
};

class CIMAssignment : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^mov[\\s]+(.*),[\\s]*(.*)$", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAssignment>(op1, op2);
		}

		return nullptr;
	}
};

class CIMAlu : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^dec[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Decrement, CValue(arrMatches[0]));
		}

		if ( CUtils::match("^inc[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Increment, CValue(arrMatches[0]));
		}

		if ( CUtils::match("^add\\s+([^,]+),\\s*([^,]+)", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::Add, op1, op2);
		}

		if ( CUtils::match("^sub\\s+([^,]+),\\s*([^,]+)", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::Sub, op1, op2);
		}

		if ( CUtils::match("^adc\\s+([^,]+),\\s*([^,]+)", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::AddWithCarry, CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^xor\\s+(.*),\\s*(.*)", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Xor, CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^and[\\s]+(.*),\\s*(.*)", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::And, op1, op2);
		}

		if ( CUtils::match("^or[\\s]+(.*),\\s*(.*)", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::Or, op1, op2);
		}

		if ( CUtils::match("^shl[\\s]+(.*), (.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Shl, CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^shr[\\s]+(.*), (.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Shr, CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^sar[\\s]+(.*), (.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Sar, CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		if ( CUtils::match("^not[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Not, CValue(arrMatches[0]));
		}

		if ( CUtils::match("^neg[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Neg, CValue(arrMatches[0]));
		}

		if ( CUtils::match("^mul[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIAlu>(CIAlu::Mul, CValue(arrMatches[0]));
		}

		return nullptr;
	}
};

class CIMFlow : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^jmp(\\sshort)?\\s+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIJump>(CLabel(arrMatches.back()));
		}

		if ( CUtils::match("^(jbe|jz|jnz|ja|jb|jnb|jle|jg|jge|jns|jl|js|jge|jcxz)\\s+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIConditionalJump>(CIConditionalJump::GetType(arrMatches[0]), CLabel(arrMatches[1]));
		}

		if ( CUtils::match("^call\\s+(\\w+)$", strLine, arrMatches) )
		{
			return make_shared<CICall>(CLabel(arrMatches[0]));
		}

		if ( CUtils::match("^call\\s+near\\s+(\\w+)$", strLine, arrMatches) )
		{
			return make_shared<CICall>(CLabel(arrMatches[0]));
		}

		if ( CUtils::match("^call\\s+near\\s+ptr\\s+(\\w+)$", strLine, arrMatches) )
		{
			return make_shared<CICall>(CLabel(arrMatches[0]));
		}

		if ( CUtils::match("^call\\s+cs:(off_code_\\w+)\\[(.*)\\]$", strLine, arrMatches) )
		{
			return make_shared<CISwitch>(arrMatches[0], CValue(arrMatches[1]));
		}

		if ( CUtils::match("^loop[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CILoop>(CILoop::Loop, CLabel(arrMatches[0]));
		}

		if ( CUtils::match("^loope[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CILoop>(CILoop::WhileEqual, CLabel(arrMatches[0]));
		}

		if ( CUtils::match("^loopne[\\s]+(.*)$", strLine, arrMatches) )
		{
			return make_shared<CILoop>(CILoop::WhileNotEqual, CLabel(arrMatches[0]));
		}


		return nullptr;
	}
};

class CIMCompare : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("^cmp\\s+(.*),\\s*(.*)$", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);

			return make_shared<CICompare>(op1, op2);
		}

		if ( CUtils::match("^test[\\s]+(.*), (.*)$", strLine, arrMatches) )
		{
			return make_shared<CITest>(CValue(arrMatches[0]), CValue(arrMatches[1]));
		}

		return nullptr;
	}
};

class CIMData : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( CUtils::match("=\\sword\\sptr", strLine, arrMatches) )
		{
			return make_shared<CIData>(CIData::WordPtr, strLine);
		}

		if ( CUtils::match("^(.*_code_.*)\\sdw offset (.*)$", strLine, arrMatches) )
		{
			return make_shared<CIData>(CIData::Function, arrMatches[0], arrMatches[1]);
		}

		if ( CUtils::match("^\\s*dw offset (.*)$", strLine, arrMatches) )
		{
			return make_shared<CIData>(CIData::Function, "", arrMatches[0]);
		}

		if ( CUtils::match("^(.*_code_.*)\\sdw(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIData>(CIData::Word, arrMatches[0], CUtils::ParseLiteral(arrMatches[1]));
		}

		if ( CUtils::match("^(.*_code_.*)\\sdb(.*)$", strLine, arrMatches) )
		{
			return make_shared<CIData>(CIData::Byte, arrMatches[0], CUtils::ParseLiteral(arrMatches[1]));
		}

		return nullptr;
	}
};

class CIMNop : public CInstructionMatcher
{
	virtual shared_ptr<CInstruction> Match(string strLine) override
	{
		vector<string> arrMatches;

		if ( strLine == "nop" )
		{
			return make_shared<CINop>();
		}

		if ( strLine == "public start" )
		{
			return make_shared<CINop>(strLine);
		}

		if ( CUtils::match("^seg.*\\s+(end|ends)$", strLine) )
		{
			return make_shared<CINop>(strLine);
		}

		if ( strLine == "align 2" )
		{
			return make_shared<CINop>(strLine);
		}

		if ( CUtils::match("^assume .*", strLine, arrMatches) )
		{
			return make_shared<CINop>(strLine);
		}

		if ( CUtils::match("^(var|arg)_.* = (byte|word) ptr .*", strLine, arrMatches) )
		{
			return make_shared<CINop>(strLine);
		}

		return nullptr;
	}
};

class CSourceParser
{
public:
	typedef shared_ptr<CInstructionMatcher> SInstructionMatcher;
	vector<SInstructionMatcher> m_arrMatchers;

	vector<shared_ptr<CInstruction>> m_arrCode;
	vector<string> m_arrSource;

	CSourceParser()
	{
		m_arrMatchers.push_back(std::make_shared<CIMFunction>());
		m_arrMatchers.push_back(std::make_shared<CIMLabel>());
		m_arrMatchers.push_back(std::make_shared<CIMReturn>());
		m_arrMatchers.push_back(std::make_shared<CIMFixedArgOp>());
		m_arrMatchers.push_back(std::make_shared<CIMStringOp>());
		m_arrMatchers.push_back(std::make_shared<CIMAssignment>());
		m_arrMatchers.push_back(std::make_shared<CIMAlu>());
		m_arrMatchers.push_back(std::make_shared<CIMFlow>());
		m_arrMatchers.push_back(std::make_shared<CIMCompare>());
		m_arrMatchers.push_back(std::make_shared<CIMData>());
		m_arrMatchers.push_back(std::make_shared<CIMNop>());

		m_arrCode.reserve(20000);
		m_arrSource.reserve(20000);
	}

	void MatchLine(const string& strLine)
	{
		for (vector<SInstructionMatcher>::iterator i = m_arrMatchers.begin(); i != m_arrMatchers.end(); i++)
		{
			shared_ptr<CInstruction> sInstruction = (*i)->Match(strLine);
			if ( sInstruction ) 
			{
				m_arrCode.push_back(sInstruction);
				m_arrSource.push_back(strLine);
				//printf("%s -> %s\n", strLine.c_str(), typeid(*sInstruction).name());
				return;
			}
		}

		printf("%s\n", strLine.c_str());
		_ASSERT(0);
	}

	void Parse(char* strFileName)
	{
		FILE* f = nullptr;
		fopen_s(&f, strFileName, "r");
		int i = 0;
		while (!feof(f))
		{
			printf("\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08%d", i++);

			// TODO:
			//if ( i > 2500 )
			//	break;

			char strLine[1024];
			fgets(strLine, 1023, f);
			if ( strLine[0] )
				strLine[strlen(strLine)-1] = 0;
			
			string _strLine = Trim(strLine);

			if ( _strLine.length() == 0 )
				continue;

			MatchLine(_strLine);
		}
	}

	string Trim(string strLine)
	{
		const char *b = strLine.c_str();
		const char *e = b + strlen(b);
		const char *cmt = strstr(b, ";");
		
		if ( cmt )
			e = cmt;

		while (b[0] == '\t' || b[0] == ' ')
			b++;
		while (e-b > 0 && (e[-1] == ' ' || e[-1] == '\t'))
			e--;

		for (char* i = (char*)b; i<e; i++)
			if ( *i == 9 )
				*i = ' ';

		return string(b, e);
	}

};

class CDos
{
public:
	void Interrupt(CMachine& m);
};

class CMachine
{
public:
	class CRegisters {
	public:
		union {
			struct {
				unsigned char al;
				unsigned char ah;
			} r8;
			struct {
				unsigned short ax;
			} r16;
		} a;
		union {
			struct {
				unsigned char bl;
				unsigned char bh;
			} r8;
			struct {
				unsigned short bx;
			} r16;
		} b;
		union {
			struct {
				unsigned char cl;
				unsigned char ch;
			} r8;
			struct {
				unsigned short cx;
			} r16;
		} c;
		union {
			struct {
				unsigned char dl;
				unsigned char dh;
			} r8;
			struct {
				unsigned short dx;
			} r16;
		} d;
		unsigned short cs;
		unsigned short ds;
		unsigned short es;

		unsigned short si;
		unsigned short di;

		unsigned short bp;
		unsigned short sp;
	};

	class CFlags
	{
	public:
		bool cf; // carry
		bool zf; // zero
		bool df; // dir
		bool interrupt;
	};

	typedef shared_ptr<CInstruction> SInstruction;
	vector<SInstruction> m_arrCode;
	vector<string> m_arrSource;

	int m_pc;
	CRegisters m_reg;
	CFlags m_flag;

	// Temp helpers;
	int m_nCmpOp1;
	int m_nCmpOp2;

	vector<int> m_arrCallStack;
	vector<int> m_arrStack;

	CDos m_dos;

public:
	CMachine()
	{
		m_arrStack.resize(1024, 0);
		m_reg.sp = 512;

		FILE* f;
		fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\data", "rb");
		fread(data, 0x955d, 1, f); 
		fclose(f);
	}

	/*
	int& stackAt(int nOffset)
	{
		_ASSERT(nOffset > 0
	}*/

	void Eval(vector<shared_ptr<CInstruction>>& arrCode, vector<string>& arrSource)
	{
		m_arrCode = arrCode;
		m_arrSource = arrSource;
		
		m_pc = -1;

		Call("start");
		for ( int i=0; i<1000; i++)
			Eval();
	}

	void Call(string label)
	{
		// return to next instruction
		m_arrCallStack.push_back(m_pc); // == -1 ? -1 : m_pc+1);
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);
		
		// skip function label
		m_pc++;
	}

	void Goto(string label)
	{
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);

		// skip goto label
		m_pc++;
	}

	void Return()
	{
		m_pc = m_arrCallStack.back();
		m_arrCallStack.pop_back();
	}
	
	void Eval()
	{
		SInstruction sInstruction = m_arrCode[m_pc];
		printf("%s\n", m_arrSource[m_pc].c_str());
		m_pc++;

		sInstruction->Eval(*this);
	}

	int FindLabel(string label)
	{
		for (int i=0; (size_t)i<m_arrCode.size(); i++)
		{
			CILabel* pLabel = dynamic_cast<CILabel*>(m_arrCode[i].get());		
			if (pLabel && pLabel->m_label == label)
				return i;

			CIFunction* pFunction = dynamic_cast<CIFunction*>(m_arrCode[i].get());
			if (pFunction && pFunction->m_eBoundary == CIFunction::Begin && pFunction->m_strName == label)
				return i;
		}
		_ASSERT(0);
		return -1;
	}

	int GetValue(CValue& v)
	{
		switch (v.m_eType)
		{
			case CValue::constant: return v.m_nValue;
			case CValue::ax: return m_reg.a.r16.ax;
			case CValue::ah: return m_reg.a.r8.ah;
			case CValue::al: return m_reg.a.r8.al;
			case CValue::bx: return m_reg.b.r16.bx;
			case CValue::bh: return m_reg.b.r8.bh;
			case CValue::bl: return m_reg.b.r8.bl;
			case CValue::cx: return m_reg.c.r16.cx;
			case CValue::ch: return m_reg.c.r8.ch;
			case CValue::cl: return m_reg.c.r8.cl;
			case CValue::dx: return m_reg.d.r16.dx;
			case CValue::dh: return m_reg.d.r8.dh;
			case CValue::dl: return m_reg.d.r8.dl;
			case CValue::cs: return m_reg.cs;
			case CValue::ds: return m_reg.ds;
			case CValue::es: return m_reg.es;

			case CValue::si: return m_reg.si;
			case CValue::di: return m_reg.di;

			case CValue::bp: return m_reg.bp;
			case CValue::sp: return m_reg.sp;

			case CValue::wordptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				return data[v.m_nValue] | (data[v.m_nValue+1] << 8);
		}
		_ASSERT(0);
		return 0;
	}

	void SetValue(CValue& v, int nValue)
	{
		switch (v.m_eType)
		{
			case CValue::constant: _ASSERT(0); return;
			case CValue::ax: m_reg.a.r16.ax = (unsigned short)nValue; return;
			case CValue::ah: m_reg.a.r8.ah = (unsigned char)nValue; return;
			case CValue::al: m_reg.a.r8.al = (unsigned char)nValue; return;
			case CValue::bx: m_reg.b.r16.bx = (unsigned short)nValue; return;
			case CValue::bh: m_reg.b.r8.bh = (unsigned char)nValue; return;
			case CValue::bl: m_reg.b.r8.bl = (unsigned char)nValue; return;
			case CValue::cx: m_reg.c.r16.cx = (unsigned short)nValue; return;
			case CValue::ch: m_reg.c.r8.ch = (unsigned char)nValue; return;
			case CValue::cl: m_reg.c.r8.cl = (unsigned char)nValue; return;
			case CValue::dx: m_reg.d.r16.dx = (unsigned short)nValue; return;
			case CValue::dh: m_reg.d.r8.dh = (unsigned char)nValue; return;
			case CValue::dl: m_reg.d.r8.dl = (unsigned char)nValue; return;

			case CValue::cs: m_reg.cs = (unsigned short)nValue; return;
			case CValue::ds: m_reg.ds = (unsigned short)nValue; return;
			case CValue::es: m_reg.es = (unsigned short)nValue; return;

			case CValue::si: m_reg.si = (unsigned short)nValue; return;
			case CValue::di: m_reg.di = (unsigned short)nValue; return;

			case CValue::bp: m_reg.bp = (unsigned short)nValue; return;
			case CValue::sp: m_reg.sp = (unsigned short)nValue; return;

			case CValue::wordptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				data[v.m_nValue] = nValue & 0xff;
				data[v.m_nValue+1] = nValue >> 8;
			return;
		}
		_ASSERT(0);
	}

	void Interrupt(int i)
	{
		switch (i)
		{
		case 0x12:
			// free mem -> ax
			m_reg.a.r16.ax = 0x1000;
			return;

		case 0x21:
			m_dos.Interrupt(*this);
			return;

		case 0x10:
			switch (m_reg.a.r8.ah)
			{
			case 0x00:
				printf("Setting video mode %d\n", m_reg.a.r8.al);
				return;
			}
		}

		_ASSERT(0);
	}

	void VideoWrite(int nSegment, int nOffset, unsigned char nValue)
	{
		// TODO:
	}
};

void CDos::Interrupt(CMachine& m)
{
	static FILE* ff[8] = {0};

	switch (m.m_reg.a.r8.ah)
	{
	case 0x09:
		printf("DOS - print DS:%04x\n", m.m_reg.d.r16.dx);
		return;

	case 0x4c:			
		printf("DOS - process exit code %d\n", m.m_reg.a.r8.al);
		return;

	case 0x3d:			
		// open file DS:DX - filename
		{
			_ASSERT(m.m_reg.a.r8.al == 0);

			int j;
			for ( j=0; j<8; j++)
				if (ff[j] == 0)
					break;

			char* strName = (char*)&data[m.m_reg.ds*16 + m.m_reg.d.r16.dx];
			char strFull[128] = "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\";
			printf("Open file '%s'\n", strName);
			strcat_s(strFull, 127, strName);
			fopen_s(&ff[j], strFull, "rb");
			m.m_flag.cf = ( ff[j] != nullptr && ff[j] != (FILE*)-1 ) ? false : true;
			m.m_reg.a.r16.ax = j ^ 0xf000;
		}
		return;

	case 0x3f:
		{
			_ASSERT( (m.m_reg.b.r16.bx & 0xf000) == 0xf000);
			FILE*f = ff[m.m_reg.b.r16.bx ^ 0xf000];
			int ofs = m.m_reg.ds*16+m.m_reg.d.r16.dx;
			int len = m.m_reg.c.r16.cx;
			_ASSERT(ofs >= 0 && ofs + len < sizeof(data));
			unsigned char* ptr = &data[ofs];
			fread(ptr, len, 1, f);
			//_ASSERT( 0x5a5c < ofs || 0x5a5c > ofs+len); 
			m.m_flag.cf = 0;
			printf("Read %x bytes into %04x:%04x\n", len, m.m_reg.ds, m.m_reg.d.r16.dx);
		}
		return;
	case 0x3e:
		{
			_ASSERT( (m.m_reg.b.r16.bx & 0xf000) == 0xf000);
			int nSlot = m.m_reg.b.r16.bx ^ 0xf000;
			_ASSERT(nSlot >= 0 && nSlot < sizeof(ff)/sizeof(ff[0]));
			FILE*f = ff[nSlot];
			fclose(f);
			ff[m.m_reg.b.r16.bx ^ 0xf000] = nullptr;
			m.m_flag.cf = 0;
		}
		return;
	}
	_ASSERT(0);
}
// Emulator

void CIAssignment::Eval(CMachine& m)
{
	int nValue = m.GetValue(m_valueFrom);
	m.SetValue(m_valueTo, nValue);
}

void CIAlu::Eval(CMachine& m)
{
	switch (m_eType)
	{
	case CIAlu::Increment: m.SetValue(m_op1, m.GetValue(m_op1)+1); return;
	case CIAlu::Decrement: m.SetValue(m_op1, m.GetValue(m_op2)-1); return;
	case CIAlu::Add: m.SetValue(m_op1, m.GetValue(m_op1) + m.GetValue(m_op2)); return;
	case CIAlu::Sub: m.SetValue(m_op1, m.GetValue(m_op1) - m.GetValue(m_op2)); return;
	case CIAlu::Xor: m.SetValue(m_op1, m.GetValue(m_op1) ^ m.GetValue(m_op2)); return;
	case CIAlu::And: m.SetValue(m_op1, m.GetValue(m_op1) & m.GetValue(m_op2)); 
		// TODO: vsetky by mali
		m.m_flag.zf = m.GetValue(m_op1) == 0;
		return;
	case CIAlu::Or: m.SetValue(m_op1, m.GetValue(m_op1) | m.GetValue(m_op2)); return;
	case CIAlu::Not: m.SetValue(m_op1, ~m.GetValue(m_op1)); return;
	case CIAlu::Neg: m.SetValue(m_op1, -m.GetValue(m_op1)); return;
	case CIAlu::AddWithCarry: m.SetValue(m_op1, m.GetValue(m_op1) + m.GetValue(m_op2) + m.m_flag.cf); return;
	case CIAlu::Shl: m.SetValue(m_op1, m.GetValue(m_op1) << m.GetValue(m_op2)); return;
	case CIAlu::Shr: m.SetValue(m_op1, m.GetValue(m_op1) >> m.GetValue(m_op2)); return;
	//	case CIAlu::Sar,
	case CIAlu::Mul: m.m_reg.a.r16.ax = m.GetValue(m_op1) * m.m_reg.a.r8.al; return;
	default:
		_ASSERT(0);
	}
}

void CISingleArgOp::Eval(CMachine& m)
{
	switch (m_eType)
	{
	case CISingleArgOp::push:
		_ASSERT(m_rvalue.GetRegisterLength() == CValue::r16);
		_ASSERT(m.m_reg.sp/2 > 0 && m.m_reg.sp/2 < (int)m.m_arrStack.size());
		m.m_arrStack[m.m_reg.sp/2] = m.GetValue(m_rvalue);
		m.m_reg.sp -= 2;
		break;

	case CISingleArgOp::pop:
		_ASSERT(m_rvalue.GetRegisterLength() == CValue::r16);
		m.m_reg.sp += 2;
		_ASSERT(m.m_reg.sp/2 > 0 && m.m_reg.sp/2 < (int)m.m_arrStack.size());
		m.SetValue(m_rvalue, m.m_arrStack[m.m_reg.sp/2]);
		break;

	case CISingleArgOp::interrupt:
		m.Interrupt(m.GetValue(m_rvalue));
		return;
	//case CISingleArgOp::div:
	//case CISingleArgOp::invalid:
	default:
		_ASSERT(0);
	}
}

void CICompare::Eval(CMachine& m)
{
	// https://www.aldeid.com/wiki/X86-assembly/Instructions/cmp
	int nOp1 = m.GetValue(m_op1);
	int nOp2 = m.GetValue(m_op2);
	m.m_flag.zf = (nOp1 == nOp2) ? 1 : 0;
	m.m_flag.cf = (nOp1 < nOp2) ? 1 : 0;

	m.m_nCmpOp1 = nOp1;
	m.m_nCmpOp2 = nOp2;
}

bool CIConditionalJump::SatisfiesCondition1(CMachine& m, CIConditionalJump::EType eType)
{
	// http://faydoc.tripod.com/cpu/jnb.htm
	switch (eType)
	{
	case jbe: return m.m_flag.cf || m.m_flag.zf;
	case jz: return m.m_flag.zf;
	case jnz: return !m.m_flag.zf;
	case jnb: return !m.m_flag.cf;
	//case ja:
	//case jb:
	//case jnb:
	//case jle:
	//case jg:
	//case jge:
	//case jns:
	//case jl:
	//case js:
	//case jcxz:
	default:
		_ASSERT(0);
	}
	return false;
}

bool CIConditionalJump::SatisfiesCondition2(CMachine& m, CIConditionalJump::EType eType)
{
	switch (eType)
	{
	case jbe: return m.m_nCmpOp1 <= m.m_nCmpOp2;
	case jz: return m.m_nCmpOp1 == m.m_nCmpOp2;
	case jnz: return m.m_nCmpOp1 != m.m_nCmpOp2;
	case jnb: return m.m_nCmpOp1 > m.m_nCmpOp2;
	//case ja:
	//case jb:
	//case jnb:
	//case jle:
	//case jg:
	//case jge:
	//case jns:
	//case jl:
	//case js:
	//case jcxz:
	default:
		_ASSERT(0);
	}
	return false;
}

void CIConditionalJump::Eval(CMachine& m)
{	
	if (!dynamic_cast<CICompare*>(m.m_arrCode[m.m_pc-2].get()))
	{
		// read file uses CF as return value!
		if (SatisfiesCondition1(m, m_eType))
			m.Goto(m_label);
		return;
	} else 
	if (!dynamic_cast<CIAlu*>(m.m_arrCode[m.m_pc-2].get()))
	{
		// TODO!!!
		if (SatisfiesCondition1(m, m_eType))
			m.Goto(m_label);
		return;
	}

	bool bTest1 = SatisfiesCondition1(m, m_eType);
	bool bTest2 = SatisfiesCondition2(m, m_eType);
	_ASSERT(bTest1 == bTest2);

	if ( bTest1 )
	{
		m.Goto(m_label);
	}
}

void CICall::Eval(CMachine& m)
{
	m.Call(m_label);
}

void CIReturn::Eval(CMachine& m)
{
	m.m_reg.sp += m_nReduceStack;
	m.Return();
}

void CITwoArgOp::Eval(CMachine& m)
{
	if (m_eType == CITwoArgOp::out)
	{
		printf("out[%x] = %x\n", m.GetValue(m_rvalue1), m.GetValue(m_rvalue2));
		return;
	}
	if (m_eType == CITwoArgOp::in)
	{
		if ( m.GetValue(m_rvalue2) == 0x3da )
		{
			// TODO: wait retrace
			static int counter = 0;
			counter ^= 8;
			m.SetValue(m_rvalue1, counter);
		}
		printf("in[%x] = %x\n", m.GetValue(m_rvalue2), m.GetValue(m_rvalue1));
		return;

	}
	_ASSERT(0);
}

void CIZeroArgOp::Eval(CMachine& m)
{
	switch (m_eType)
	{
	case CIZeroArgOp::cld: m.m_flag.df = false; return;
	case CIZeroArgOp::_std: m.m_flag.df = true; return;
	case CIZeroArgOp::clc: m.m_flag.cf = false; return;
	case CIZeroArgOp::stc: m.m_flag.cf = true; return;
	case CIZeroArgOp::cli: m.m_flag.interrupt = false; return;
	case CIZeroArgOp::sti: m.m_flag.interrupt = true; return;
	}
	_ASSERT(0);
}

void CIString::Eval(CMachine& m)
{
	switch (m_rule)
	{
	case CIString::rep:
		switch (m_operation)
		{
		case CIString::stosb:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalStosb(m);
			return;
		case CIString::lodsb:
			break;
		case CIString::stosw:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalStosw(m);
			return;
		case CIString::lodsw: 
			break;
		case CIString::movsw:
			break;
		case CIString::movsb:
			break;
		}

		break;
	case CIString::repne:
		break;
	}
	_ASSERT(0);
}

void CIString::EvalStosb(CMachine& m)
{
	int es = m.m_reg.es;
	_ASSERT(m.m_flag.df == false);

	if ( ( es == 0xa000 ) || (es == 0xb800) )
		m.VideoWrite(es, m.m_reg.di++, m.m_reg.a.r8.al);
	else
		data[es*16+m.m_reg.di++] = m.m_reg.a.r8.al; 

	_ASSERT( m.m_reg.di < 0xfff5 );
}

void CIString::EvalStosw(CMachine& m)
{
	int es = m.m_reg.es;
	_ASSERT(m.m_flag.df == false);

	if ( ( es == 0xa000 ) || (es == 0xb800) )
	{
		m.VideoWrite(es, m.m_reg.di++, m.m_reg.a.r8.ah);
		m.VideoWrite(es, m.m_reg.di++, m.m_reg.a.r8.al);
	}
	else
	{
		data[es*16+m.m_reg.di++] = m.m_reg.a.r8.ah;
		data[es*16+m.m_reg.di++] = m.m_reg.a.r8.al;
	}
	_ASSERT( m.m_reg.di < 0xfff5 );
}

int main(int argc, char* argv[])
{
	CSourceParser sp;
	sp.Parse("C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\devel\\goose_code.asm");
	
	CMachine m;
	m.Eval(sp.m_arrCode, sp.m_arrSource);
	return 0;
}

