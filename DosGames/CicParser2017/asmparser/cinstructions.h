class CCInstruction
{
public:
	virtual ~CCInstruction() {}
	virtual string ToString() = 0;
	virtual bool TryJoin(shared_ptr<CCInstruction>) 
	{ 
		return false;
	};
};

class CCAssignment : public CCInstruction
{
public:
	CCAssignment(CValue& vTo, CValue& vFrom)
	{
		m_strDst = vTo.ToC();
		m_strSrc = vFrom.ToC();
	}

	CCAssignment(shared_ptr<CIAlu> pAlu)
	{
		string op1 = pAlu->m_op1.ToC();
		string op2 = pAlu->m_op2.ToC();
		switch (pAlu->m_eType)
		{
		case CIAlu::Increment: 
			m_strDst = op1; 
			m_strSrc = op1 + " + 1";
			break;
		case CIAlu::Decrement: 
			m_strDst = op1; 
			m_strSrc = op1 + " - 1";
			break;
		case CIAlu::Add: 
			m_strDst = op1; 
			m_strSrc = op1 + " + " + op2;
			break;
		case CIAlu::Sub: 
			m_strDst = op1; 
			m_strSrc = op1 + " - " + op2;
			break;
		case CIAlu::Xor: 
			m_strDst = op1; 
			m_strSrc = op1 + " ^ " + op2;
			break;
		case CIAlu::And: 
			m_strDst = op1; 
			m_strSrc = op1 + " & " + op2;
			break;
		case CIAlu::Or: 
			m_strDst = op1; 
			m_strSrc = op1 + " | " + op2;
			break;
		case CIAlu::Not: 
			m_strDst = op1; 
			m_strSrc = "!" + op1;
			break;
		case CIAlu::Neg: 
			m_strDst = op1; 
			m_strSrc = "-" + op1;
			break;
		case CIAlu::Shl: 
			m_strDst = op1; 
			m_strSrc = op1 + " << " + op2;
			break;
		case CIAlu::Shr: 
			m_strDst = op1; 
			m_strSrc = op1 + " >> " + op2;
			break;
		default:
			_ASSERT(0);
		}
	}

	virtual string ToString() override
	{
		vector<string> arrMatches;
		string strTest = m_strSrc;
		CUtils::replace(strTest, m_strDst, "###");
		if (CUtils::match("### (\\+|\\-|>>|<<|&) ([^\\s]+)", strTest, arrMatches))
		{
			// only when finalizing, couldnt join
			/*
			if ( arrMatches[0] == "+" && arrMatches[1] == "1" )
				return m_strDst + "++";
			if ( arrMatches[0] == "-" && arrMatches[1] == "1" )
				return m_strDst + "--";
				*/
			return m_strDst + " " + arrMatches[0] + "= " + arrMatches[1] + ";";
		}

		return m_strDst + " = " + m_strSrc + ";";
	}

	virtual bool TryJoin(shared_ptr<CCInstruction> pInstruction) override
	{
		shared_ptr<CCAssignment> pPrev = dynamic_pointer_cast<CCAssignment>(pInstruction);
		if (!pPrev)
			return false;

		if ( m_strDst == pPrev->m_strDst )
		{
			if ( CUtils::match(".* >> (\\d+)$", m_strSrc) && CUtils::match(".* >> (\\d+)$", pPrev->m_strSrc))
			{
				vector<string> arrPrevMatches;
				CUtils::match("(.*) >> (\\d+)$", pPrev->m_strSrc, arrPrevMatches);
			
				vector<string> arrCurMatches;
				CUtils::match("(.*) >> (\\d+)$", m_strSrc, arrCurMatches);

				int nTotal = CUtils::ParseLiteral(arrPrevMatches[1]) + CUtils::ParseLiteral(arrCurMatches[1]);
				stringstream ss;
				ss << arrPrevMatches[0] << " >> " << std::dec << nTotal;
				m_strSrc = ss.str();

				return true;
			}

			if ( pPrev->m_strSrc.find(" ") != string::npos )
				CUtils::replace(m_strSrc, m_strDst, "(" + pPrev->m_strSrc + ")");
			else
				CUtils::replace(m_strSrc, m_strDst, pPrev->m_strSrc);
			return true;
		}
		return false;
	}


	string m_strDst;
	string m_strSrc;
};

class CCSingleArgOp : public CCInstruction
{
	string m_strOperation;
	string m_strArgument;

public:
	CCSingleArgOp(shared_ptr<CISingleArgOp> pInstruction)
	{
		m_strArgument = pInstruction->m_rvalue.ToC();
		switch (pInstruction->m_eType)
		{
			case CISingleArgOp::push: m_strOperation = "_push($arg)"; break;
			case CISingleArgOp::pop: m_strOperation = "$arg = _pop()"; break;
			case CISingleArgOp::interrupt: m_strOperation = "_interrupt($arg)"; break;
			case CISingleArgOp::div: m_strOperation = "_div($arg)"; break;
			default:
				_ASSERT(0);
		}
	}

	virtual string ToString() override
	{
		string strAux = m_strOperation;
		CUtils::replace(strAux, "$arg", m_strArgument);
		return strAux + ";";
	}
};

class CCConditionalJump : public CCInstruction
{
	string m_strOperand1;
	string m_strOperand2;
	string m_strCondition;
	CLabel m_strLabel;

public:
	CCConditionalJump(shared_ptr<CIJump> pJump) : m_strLabel("")
	{
		m_strCondition = "true";
		m_strLabel = pJump->m_label;
	}

	CCConditionalJump(shared_ptr<CIConditionalJump> pCondition, shared_ptr<CICompare> pCompare) : m_strLabel("")
	{
		/*
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

		*/

		m_strOperand1 = pCompare->m_op1.ToC();
		m_strOperand2 = pCompare->m_op2.ToC();
		m_strLabel = pCondition->m_label;
		switch ( pCondition->m_eType )
		{
		case CIConditionalJump::jz: m_strCondition = "$a == $b"; break;
		case CIConditionalJump::jnz: m_strCondition = "$a != $b"; break;
		case CIConditionalJump::jb: m_strCondition = "$a < $b"; break;
		case CIConditionalJump::jnb: m_strCondition = "$a >= $b"; break;
		case CIConditionalJump::jg: m_strCondition = "($type)$a > ($type)$b"; break;

				
			/*
		case CIConditionalJump::jbe:
		case CIConditionalJump::ja:
		case CIConditionalJump::jnb:
		case CIConditionalJump::jle:
		case CIConditionalJump::jg:
		case CIConditionalJump::jge:
		case CIConditionalJump::jns:
		case CIConditionalJump::jl:
		case CIConditionalJump::js:
		case CIConditionalJump::jcxz:
		*/
		default:
			_ASSERT(0);
		}
	}
	
	string GetNegated()
	{
		// TODO: lazy negation!
		return "!(" + GetCondition() + ")";
	}

	string GetCondition()
	{
		string strAux = m_strCondition;
		CUtils::replace(strAux, "$a", m_strOperand1);
		CUtils::replace(strAux, "$b", m_strOperand2);
		return strAux;
	}

	virtual string ToString() override
	{
		string strAux = GetCondition();

		if ( strAux == "true" )
			return "goto " + m_strLabel + ";";

		return "if (" + strAux + ") goto " + m_strLabel + ";";
	}

	CLabel GetLabel()
	{
		return m_strLabel;
	}
};

class CCLabel : public CCInstruction
{
	CLabel m_strLabel;

public:
	CCLabel(shared_ptr<CILabel> pJump) : m_strLabel("")
	{
		m_strLabel = pJump->m_label;
	}

	virtual string ToString() override
	{
		return m_strLabel + ":";
	}

	CLabel GetLabel()
	{
		return m_strLabel;
	}
};

class CCCall : public CCInstruction
{
	CLabel m_strFunction;

public:
	CCCall(shared_ptr<CICall> pCall) : m_strFunction("")
	{
		m_strFunction = pCall->m_label;
	}

	virtual string ToString() override
	{
		return m_strFunction + "();";
	}
};

class CCLoop : public CCInstruction
{
	shared_ptr<CCInstruction> m_pOrigin;

public:
	CCLoop(shared_ptr<CCInstruction> pOrigin)
	{
		m_pOrigin = pOrigin;
	}

	virtual string ToString() override
	{
		if ( dynamic_pointer_cast<CCLabel>(m_pOrigin) )
			return "do {";

		shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(m_pOrigin);
		if ( pJump )
		{
			return "} while (" + pJump->GetCondition() + ");";
		}
			
		_ASSERT(0);
		return "";
	}
};

class CCIfThenElse : public CCInstruction
{
public:
	enum EType {
		If,
		Skip,
		Else,
		Final
	};

	shared_ptr<CCConditionalJump> m_pCondition;
	EType m_eType;


public:
	CCIfThenElse(shared_ptr<CCConditionalJump> pCondition)
	{
		m_pCondition = pCondition;
		m_eType = If;
	}

	CCIfThenElse(EType eType)
	{
		m_eType = eType;
	}

	virtual string ToString() override
	{
		switch (m_eType)
		{
		case If: return "if (" + m_pCondition->GetNegated() + " ) {";
		case Else: return "} else";
		case Skip: return "{";
		case Final: return "}";
		}
		_ASSERT(0);
		return "";
	}
};
