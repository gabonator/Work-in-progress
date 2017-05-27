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
	string m_strDst;
	string m_strSrc;
	string m_strInsertion;

public:
	CCAssignment(shared_ptr<CIAssignment> pAssignment)
	{
		CValue& vTo = pAssignment->m_valueTo;
		CValue& vFrom = pAssignment->m_valueFrom;

		m_strDst = vTo.SetC(&pAssignment->m_analysis);

		if ( vFrom.m_eType == CValue::es_ptr && vFrom.GetRegisterLength() == CValue::r8 )
		{
			if ( pAssignment->m_analysis.m_es.GetValue() == 0xF000 && vFrom.m_nValue == 0xFFFE)
			{
				// F000:FFFE - BIOS - IBM computer type code
				m_strSrc = "0xff";
				return;
			}
		}
		m_strSrc = vFrom.GetC(&pAssignment->m_analysis);
	}

	CCAssignment(shared_ptr<CIAlu> pAlu)
	{
		string op1 = pAlu->m_op1.ToC();
		string op2 = pAlu->m_op2.m_eType == CValue::invalid ? "???" : pAlu->m_op2.ToC();
		switch (pAlu->m_eType)
		{
		case CIAlu::Increment: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = op1 + " + 1";
			break;
		case CIAlu::Decrement: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = op1 + " - 1";
			break;
		case CIAlu::Add: 
			if (pAlu->m_bExportInsertion)
			{
				_ASSERT(pAlu->m_op1.GetRegisterLength() == pAlu->m_op2.GetRegisterLength());
				if (pAlu->m_op1.GetRegisterLength() == CValue::r8)
					m_strInsertion = "flags.carry = (" + op1 + " + " + op2 + ") >= 0x100";
				else if (pAlu->m_op1.GetRegisterLength() == CValue::r8)
					m_strInsertion = "flags.carry = (" + op1 + " + " + op2 + ") >= 0x10000";
				else
					_ASSERT(0);
			}

			m_strDst = op1; 
			m_strSrc = op1 + " + " + op2;
			break;
		case CIAlu::AddWithCarry: 
			_ASSERT(!pAlu->m_bExportInsertion);
			// TODO CARRY!!! ODKIAL??
			m_strDst = op1; 
			m_strSrc = op1 + " + " + op2 + " + flags.carry; _ASSERT(0 /* add with carry */)";
			break;
		case CIAlu::Sub: 
			if (pAlu->m_bExportInsertion)
			{
				m_strInsertion = "flags.carry = " + op1 + " < " + op2;
			}

			m_strDst = op1; 
			if ( op1 == op2 )
				m_strSrc = "0";
			else
				m_strSrc = op1 + " - " + op2;
			break;
		case CIAlu::Xor: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = op1 + " ^ " + op2;
			break;
		case CIAlu::And: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = op1 + " & " + op2;
			break;
		case CIAlu::Or: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = op1 + " | " + op2;
			break;
		case CIAlu::Not: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = "(~" + op1 + ")";
			break;
		case CIAlu::Neg: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = op1; 
			m_strSrc = "-" + op1;
			break;
		case CIAlu::Shl: 
			if (pAlu->m_bExportInsertion)
			{
				_ASSERT(op2 == "1");
				if (pAlu->m_op1.GetRegisterLength() == CValue::r8)
					m_strInsertion = "flags.carry = !!(" + op1 + " & 0x80)";
				else if (pAlu->m_op1.GetRegisterLength() == CValue::r16)
					m_strInsertion = "flags.carry = !!(" + op1 + " & 0x8000)";
				else
					_ASSERT(0);
			}
			m_strDst = op1; 
			m_strSrc = op1 + " << " + op2;
			break;
		case CIAlu::Shr: 
			if (pAlu->m_bExportInsertion)
			{
				_ASSERT(op2 == "1");
				m_strInsertion = "flags.carry = " + op1 + " & 1";
			}
			m_strDst = op1; 
			m_strSrc = op1 + " >> " + op2;
			break;
		case CIAlu::Mul: 
			_ASSERT(!pAlu->m_bExportInsertion);
			m_strDst = CValue("ax").ToC(); 
			m_strSrc = op1 + " * " + CValue("al").ToC();
			break;
		default:
			_ASSERT(0);
		}
	}

	virtual string ToString() override
	{
		string strInsertion = m_strInsertion.empty() ? "" : m_strInsertion + ";\n";
		vector<string> arrMatches;
		string strTest = m_strSrc;
		CUtils::replace(strTest, m_strDst, "###");
		if (CUtils::match("### (\\+|\\-|>>|<<|&|\\|) ([^\\s]+)", strTest, arrMatches))
		{
			// only when finalizing, couldnt join
			/*
			if ( arrMatches[0] == "+" && arrMatches[1] == "1" )
				return m_strDst + "++";
			if ( arrMatches[0] == "-" && arrMatches[1] == "1" )
				return m_strDst + "--";
				*/
			return strInsertion + m_strDst + " " + arrMatches[0] + "= " + arrMatches[1] + ";";
		}

		if (m_strDst.find("($value)") != string::npos)
		{
			string strTemp = m_strDst;
			CUtils::replaceOnce(strTemp, "($value)", m_strSrc);
			return strInsertion + strTemp + ";";
		}

		return strInsertion + m_strDst + " = " + m_strSrc + ";";
	}

	virtual bool TryJoin(shared_ptr<CCInstruction> pInstruction) override
	{
		shared_ptr<CCAssignment> pPrev = dynamic_pointer_cast<CCAssignment>(pInstruction);
		if (!pPrev)
			return false;

		if ( !pPrev->m_strInsertion.empty() || !m_strInsertion.empty())
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
				CUtils::replaceOnce(m_strSrc, m_strDst, "(" + pPrev->m_strSrc + ")");
			else
				CUtils::replaceOnce(m_strSrc, m_strDst, pPrev->m_strSrc);
			return true;
		}
		return false;
	}
};

class CCZeroArgOp : public CCInstruction
{
	string m_strOperation;

public:
	static string RegToC(CStaticAnalysis::CPossibleValue& pv)
	{
		switch(pv.GetValue())
		{
			case -1: 
				return "MemAuto";
			case 0xb800: 
				return "MemB800";
			case 0xa000: 
				return "MemA000";
			case 0x0000: 
				return "MemData";
			default:
				_ASSERT(0);
		}
		return "MemAuto";
	}

	static string DirToC(CStaticAnalysis::CPossibleValue& pv)
	{
		switch(pv.GetValue())
		{
			case -1: 
				return "DirAuto";
			case 0: 
				return "DirForward";
			case 1: 
				return "DirBackward";
			default:
				_ASSERT(0);
		}
		return "DirAuto";
	}

	static string GetTemplate(CStaticAnalysis& anal, CIZeroArgOp::EType op)
	{
		string _ds = RegToC(anal.m_ds);
		string _es = RegToC(anal.m_es);
		string _dir = DirToC(anal.m_direction);

		switch (op)
		{
		case CIZeroArgOp::lodsb: return "<" + _ds + ", " + _dir + ">"; break;
		case CIZeroArgOp::stosb: return "<" + _es + ", " + _dir + ">"; break;
		case CIZeroArgOp::lodsw: return "<" + _ds + ", " + _dir + ">"; break;
		case CIZeroArgOp::stosw: return "<" + _es + ", " + _dir + ">"; break;
		case CIZeroArgOp::movsb: return "<" + _es + ", " + _ds + ", " + _dir + ">"; break;
		case CIZeroArgOp::movsw: return "<" + _es + ", " + _ds + ", " + _dir + ">"; break;
		//case CIString::scasb: return ""; break;
		//case CIString::scasw: return ""; break;
		default:
			_ASSERT(0);
		}
		return "";
	}

	CCZeroArgOp(shared_ptr<CIZeroArgOp> pInstruction)
	{
		//cli, sti, _std, stc, ctc, cld, aaa, cbw, lodsw, lodsb, stosw, stosb, movsw, movsb, clc, sahf, lahf, popf, pushf, xlat,


		switch (pInstruction->m_eType)
		{
		case CIZeroArgOp::cli: m_strOperation = "flags.interrupt = false"; break;
		case CIZeroArgOp::sti: m_strOperation = "flags.interrupt = true"; break;
		case CIZeroArgOp::cld: m_strOperation = "flags.direction = false"; break;
		case CIZeroArgOp::_std: m_strOperation = "flags.direction = true"; break;
		case CIZeroArgOp::clc: m_strOperation = "flags.carry = false"; break;
		case CIZeroArgOp::stc: m_strOperation = "flags.carry = true"; break;
		case CIZeroArgOp::lahf: m_strOperation = "_ah = flags.toByte()"; break;
		case CIZeroArgOp::sahf: m_strOperation = "flags.fromByte(_ah)"; break;

		case CIZeroArgOp::lodsb: m_strOperation = "_lodsb"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;
		case CIZeroArgOp::stosb: m_strOperation = "_stosb"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;
		case CIZeroArgOp::lodsw: m_strOperation = "_lodsw"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;
		case CIZeroArgOp::stosw: m_strOperation = "_stosw"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;
		case CIZeroArgOp::movsb: m_strOperation = "_movsb"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;
		case CIZeroArgOp::movsw: m_strOperation = "_movsw"+GetTemplate(pInstruction->m_analysis, pInstruction->m_eType)+"()"; break;

		case CIZeroArgOp::pushf: m_strOperation = "_pushf()"; break;
		case CIZeroArgOp::popf: m_strOperation = "_popf()"; break;
		case CIZeroArgOp::aaa: m_strOperation = "_ASSERT(0 /* check carry */); _aaa()"; break;
		default:
				_ASSERT(0);
		}
	}

	virtual string ToString() override
	{
		return m_strOperation + ";";
	}
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

class CCTwoArgOp : public CCInstruction
{
	string m_strOperation;
	string m_strArgument1;
	string m_strArgument2;

public:
	CCTwoArgOp(shared_ptr<CITwoArgOp> pInstruction)
	{
		m_strArgument1 = pInstruction->m_rvalue1.ToC();
		m_strArgument2 = pInstruction->m_rvalue2.ToC();
		switch (pInstruction->m_eType)
		{
		case CITwoArgOp::in: m_strOperation = "_in($arg1, $arg2)"; break;
		case CITwoArgOp::out: m_strOperation = "_out($arg1, $arg2)"; break;
		case CITwoArgOp::xchg: m_strOperation = "_xchg($arg1, $arg2)"; break;
		case CITwoArgOp::rcr: m_strOperation = "_ASSERT(0 /* check carry */); _rcr($arg1, $arg2)"; break;
		case CITwoArgOp::rcl: m_strOperation = "_ASSERT(0 /* check carry */); _rcl($arg1, $arg2)"; break;
		case CITwoArgOp::rol: m_strOperation = "_rol($arg1, $arg2)"; break;
		case CITwoArgOp::les: m_strOperation = "_les($arg1, $arg2)"; break;
		case CITwoArgOp::lea: m_strOperation = "_lea($arg1, $arg2)"; break;
		case CITwoArgOp::sbb: m_strOperation = "_sbb($arg1, $arg2)"; break;
			default:
				_ASSERT(0);
		}
	}

	virtual string ToString() override
	{
		string strAux = m_strOperation;
		CUtils::replace(strAux, "$arg1", m_strArgument1);
		CUtils::replace(strAux, "$arg2", m_strArgument2);
		return strAux + ";";
	}
};

class CCConditionalJump : public CCInstruction
{
public:
	enum ELabelType {
		Label,
		Return,
		ReturnStack,
		Break,
		Continue
	};

	enum EConditionType {
		Regular,
		ZeroFlag,
		ZeroCarryFlag,
		CarryFlag
	};

	string m_strOperand1;
	string m_strOperand2;
	string m_strCondition;
	CLabel m_strLabel;
	ELabelType m_eLabelType;
	string m_strSigned;

public:
	CCConditionalJump(shared_ptr<CIJump> pJump) : m_strLabel("")
	{
		m_strCondition = "true";
		m_strLabel = pJump->m_label;
		m_eLabelType = Label;
	}

	CCConditionalJump(shared_ptr<CILoop> pLoop, shared_ptr<CInstruction> pCondition) : m_strLabel("")
	{
		string strExtraCondition;

		switch (pLoop->m_eType)
		{
		case CILoop::Loop:
			m_strCondition = "--_cx";
			break;

		case CILoop::WhileNotEqual:
			strExtraCondition = make_shared<CCConditionalJump>( make_shared<CIConditionalJump>(CIConditionalJump::jnz, CLabel("")), pCondition )->GetCondition();
			m_strCondition = "--_cx && " + strExtraCondition;
			break;

		case CILoop::WhileEqual:
			strExtraCondition = make_shared<CCConditionalJump>( make_shared<CIConditionalJump>(CIConditionalJump::jz, CLabel("")), pCondition )->GetCondition();
			m_strCondition = "--_cx && " + strExtraCondition;
			break;

		default:
			_ASSERT(0);
		}

		m_strLabel = pLoop->m_label;
		m_eLabelType = Label;
	}

	string SignedType(CValue& op)
	{
		if (op.GetRegisterLength() == CValue::r8)
			return "char";

		if (op.GetRegisterLength() == CValue::r16)
			return "short";

		_ASSERT(0);
		return "?";
	}

	explicit CCConditionalJump(shared_ptr<CIConditionalJump> pCondition, shared_ptr<CInstruction> pInstruction) : m_strLabel("")
	{
		if ( dynamic_pointer_cast<CIZeroArgOp>(pInstruction) && dynamic_pointer_cast<CIZeroArgOp>(pInstruction)->m_eType == CIZeroArgOp::FakeZeroTest )
			From(pCondition, CCConditionalJump::ZeroFlag);
		else if ( dynamic_pointer_cast<CIZeroArgOp>(pInstruction) && dynamic_pointer_cast<CIZeroArgOp>(pInstruction)->m_eType == CIZeroArgOp::FakeZeroCarryTest )
			From(pCondition, CCConditionalJump::ZeroCarryFlag);
		else if ( dynamic_pointer_cast<CIZeroArgOp>(pInstruction) && dynamic_pointer_cast<CIZeroArgOp>(pInstruction)->m_eType == CIZeroArgOp::FakeCarryTest )
			From(pCondition, CCConditionalJump::CarryFlag);
		else if ( dynamic_pointer_cast<CICompare>(pInstruction) )
			From(pCondition, dynamic_pointer_cast<CICompare>(pInstruction));
		else if ( dynamic_pointer_cast<CITest>(pInstruction) )
			From(pCondition, dynamic_pointer_cast<CITest>(pInstruction));
		else if ( dynamic_pointer_cast<CIAlu>(pInstruction) )
			From(pCondition, dynamic_pointer_cast<CIAlu>(pInstruction));
		else 
			_ASSERT(0);
	}

	void From(shared_ptr<CIConditionalJump> pCondition, shared_ptr<CICompare> pCompare)
	{
		_ASSERT(pCompare);

		m_strOperand1 = pCompare->m_op1.ToC();
		m_strOperand2 = pCompare->m_op2.ToC();
		m_strLabel = pCondition->m_label;
		m_eLabelType = Label;

		m_strSigned = "?";
		if (pCompare->m_op1.GetRegisterLength() == pCompare->m_op2.GetRegisterLength())
		{
			m_strSigned = SignedType(pCompare->m_op1);
		}

		// http://marin.jb.free.fr/jumps/
		switch ( pCondition->m_eType )
		{
		case CIConditionalJump::jz: m_strCondition = "$a == $b"; break;
		case CIConditionalJump::jnz: m_strCondition = "$a != $b"; break;
		case CIConditionalJump::jb: m_strCondition = "$a < $b"; break;
		case CIConditionalJump::jnb: m_strCondition = "$a >= $b"; break;
		case CIConditionalJump::jg: m_strCondition = "($type)$a > ($type)$b"; break;
		case CIConditionalJump::jge: m_strCondition = "($type)$a >= ($type)$b"; break;
		case CIConditionalJump::jle: m_strCondition = "($type)$a <= ($type)$b"; break;

		case CIConditionalJump::jbe: m_strCondition = "$a <= $b"; break;
		case CIConditionalJump::ja: m_strCondition = "$a > $b"; break;
		default:
			_ASSERT(0);
		}
	}
	
	void From(shared_ptr<CIConditionalJump> pCondition, shared_ptr<CITest> pTest)
	{
		m_strOperand1 = pTest->m_op1.ToC();
		m_strOperand2 = pTest->m_op2.ToC();
		m_strLabel = pCondition->m_label;
		m_eLabelType = Label;

		switch ( pCondition->m_eType )
		{
		case CIConditionalJump::jz: m_strCondition = "!($a & $b)"; break;
		case CIConditionalJump::jnz: m_strCondition = "$a & $b"; break;
		default:
			_ASSERT(0);
		}
	}

	void From(shared_ptr<CIConditionalJump> pCondition, shared_ptr<CIAlu> pAlu)
	{
		m_strOperand1 = pAlu->m_op1.ToC();
		m_strLabel = pCondition->m_label;
		m_eLabelType = Label;
		m_strSigned = SignedType(pAlu->m_op1);
		switch (pAlu->m_eType)
		{
		case CIAlu::Increment:
			switch ( pCondition->m_eType )
			{
			case CIConditionalJump::jz: m_strCondition = "$a == 0"; break;
			case CIConditionalJump::jnz: m_strCondition = "$a != 0"; break;
			case CIConditionalJump::jb: m_strCondition = "($type)$a < 0"; break; // TODO: verify?
			default:
				_ASSERT(0);
			}
			break;

		case CIAlu::Decrement: // TODO: should change carry??
			switch ( pCondition->m_eType )
			{
			case CIConditionalJump::jz: m_strCondition = "$a == 0"; break;
			case CIConditionalJump::jnz: m_strCondition = "$a != 0"; break;
			default:
				_ASSERT(0);
			}
			break;

		case CIAlu::And:
		case CIAlu::Or:
		case CIAlu::Sub:
		case CIAlu::Add:
		case CIAlu::Xor:
			switch ( pCondition->m_eType )
			{
			case CIConditionalJump::jz: m_strCondition = "$a == 0"; break;
			case CIConditionalJump::jnz: m_strCondition = "$a != 0"; break;
			case CIConditionalJump::ja: 
				pAlu->m_bExportInsertion = true;
				m_strCondition = "!flags.carry && ($a != 0)"; break;
			case CIConditionalJump::jb: 
				pAlu->m_bExportInsertion = true;
				m_strCondition = "flags.carry"; break;
			case CIConditionalJump::jnb: 
				pAlu->m_bExportInsertion = true;
				m_strCondition = "!flags.carry"; break;
			default:
				_ASSERT(0);
			}
			break;
		
		case CIAlu::Shl:
		case CIAlu::Shr:
			switch ( pCondition->m_eType )
			{
			case CIConditionalJump::jz: m_strCondition = "$a == 0"; break;
			case CIConditionalJump::jnz: m_strCondition = "$a != 0"; break;
			case CIConditionalJump::jb: 
				pAlu->m_bExportInsertion = true;
				m_strCondition = "flags.carry"; break;
			case CIConditionalJump::jnb: 
				pAlu->m_bExportInsertion = true;
				m_strCondition = "!flags.carry"; break;
			default:
				_ASSERT(0);
			}
			break;

		default:
			_ASSERT(0);
		}
	}

	void From(shared_ptr<CIConditionalJump> pCondition, EConditionType eCondition)
	{
		m_strLabel = pCondition->m_label;
		m_eLabelType = Label;

		switch ( pCondition->m_eType )
		{
		case CIConditionalJump::jz: 
			_ASSERT(eCondition == ZeroFlag);
			m_strCondition = "flags.zero"; 
			break;
			
		case CIConditionalJump::jnz: 
			_ASSERT(eCondition == ZeroFlag);
			m_strCondition = "!flags.zero"; 
			break;

		case CIConditionalJump::jnb: 
			_ASSERT(eCondition == CarryFlag || eCondition == ZeroCarryFlag);
			m_strCondition = "!flags.carry"; 
			break;

		case CIConditionalJump::jb: 
			_ASSERT(eCondition == CarryFlag);
			m_strCondition = "flags.carry"; 
			break;

		default:
			_ASSERT(0);
		}
	}
	
	string GetNegated()
	{
		// TODO: lazy negation!
		vector<string> arrMatches;
		if (CUtils::match("^!\\((.*)\\)$", GetCondition(), arrMatches))
			return arrMatches[0];

		if (CUtils::match("^(.*) == (.*)$", GetCondition(), arrMatches))
			return arrMatches[0] + " != " + arrMatches[1];

		if (CUtils::match("^(.*) != (.*)$", GetCondition(), arrMatches))
			return arrMatches[0] + " == " + arrMatches[1];

		return "!(" + GetCondition() + ")";
	}

	string GetCondition()
	{
		string strAux = m_strCondition;
		CUtils::replace(strAux, "$a", m_strOperand1);
		CUtils::replace(strAux, "$b", m_strOperand2);
		CUtils::replace(strAux, "$type", m_strSigned);
		
		return strAux;
	}

	string Target()
	{
		switch (m_eLabelType)
		{
		case Label: return "goto " + m_strLabel;
		case Return: return "return";
		case Break: return "break";
		case Continue: return "continue";
		}
		_ASSERT(0);
		return "?";
	}

	virtual string ToString() override
	{
		string strAux = GetCondition();

		if ( strAux == "true" )
			return Target() + ";";

		return "if (" + strAux + ")\n  " + Target() + ";";
	}

	CLabel GetLabel()
	{
		_ASSERT(m_eLabelType == Label);
		return m_strLabel;
	}

	void SetLabel(CLabel label)
	{
		m_strLabel = label;
	}

	bool Unconditional()
	{
		return m_strCondition == "true";
	}

	void SetLabelReturn()
	{
		m_eLabelType = Return;
	}

	bool GetLabelReturn()
	{
		return m_eLabelType == Return;
	}

	void SetLabelContinue()
	{
		m_eLabelType = Continue;
	}

	bool GetLabelContinue()
	{
		return m_eLabelType == Continue;
	}

	void SetLabelBreak()
	{
		m_eLabelType = Break;
	}

	bool GetLabelBreak()
	{
		return m_eLabelType == Break;
	}

	bool GetLabelLabel()
	{
		return m_eLabelType == Label;
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

	CCLabel(CLabel label) : m_strLabel(label)
	{
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
	//CLabel m_strFunction;
	string m_strCall;

public:
	CCCall(shared_ptr<CICall> pCall)
	{
		m_strCall = pCall->m_label + "()";
	}

	CCCall(string strFunction) : m_strCall(strFunction)
	{
	}

	virtual string ToString() override
	{
		return m_strCall + ";";
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

class CCWhileContinueBreak : public CCInstruction
{
public:
	enum EType {
		While,
		Continue,
		Break,
		Final
	};

	shared_ptr<CCConditionalJump> m_pCondition;
	EType m_eType;

public:
	CCWhileContinueBreak(EType eType)
	{
		m_eType = eType;
	}

	virtual string ToString() override
	{
		switch (m_eType)
		{
		case While: return "while (true) {";
		case Continue: return "continue;";
		case Break: return "break;";
		case Final: return "}";
		}
		_ASSERT(0);
		return "";
	}
};

class CCReturn : public CCInstruction
{
public:
	int m_nReduceStack;

public:
	CCReturn(shared_ptr<CIReturn> pReturn)
	{
		m_nReduceStack = pReturn->m_nReduceStack;;
	}

	virtual string ToString() override
	{
		_ASSERT(m_nReduceStack == 0);
		return "return;";
	}
};

class CCCompare : public CCInstruction
{
public:
	enum EType
	{
		ZeroFlag,
		ZeroCarryFlag,
	};

	string m_strCode;

public:
	CCCompare(shared_ptr<CICompare> pInstruction, EType eType)
	{
		string strArgument1 = pInstruction->m_op1.ToC();
		string strArgument2 = pInstruction->m_op2.ToC();

		switch (eType)
		{
		case CCCompare::ZeroCarryFlag: 
			// TODO: Check
			m_strCode = "flags.zero = $arg1 == $arg2; flags.carry = $arg1 < $arg2"; 
			break;

		case CCCompare::ZeroFlag: 
			if (strArgument1 == strArgument2)
				m_strCode = "flags.zero = true";
			else
				m_strCode = "flags.zero = $arg1 == $arg2"; 
			break;

		default:
			_ASSERT(0);
		}

		CUtils::replace(m_strCode, "$arg1", strArgument1);
		CUtils::replace(m_strCode, "$arg2", strArgument2);
	}

	virtual string ToString() override
	{
		return m_strCode + ";";
	}
};

class CCStringOp : public CCInstruction
{
public:
	string m_strRepeat;
	string m_strOperation;
	string m_strTemplate;

public:
	CCStringOp(shared_ptr<CIString> pInstruction)
	{
		switch (pInstruction->m_rule)		
		{
		case CIString::rep: m_strRepeat = "rep"; break;
		case CIString::repne: m_strRepeat = "repne"; break;
		default:
			_ASSERT(0);
		}

		switch (pInstruction->m_operation)		
		{
		case CIString::lodsb: m_strOperation = "lodsb"; break;
		case CIString::stosb: m_strOperation = "stosb"; break;
		case CIString::lodsw: m_strOperation = "lodsw"; break;
		case CIString::stosw: m_strOperation = "stosw"; break;
		case CIString::movsb: m_strOperation = "movsb"; break;
		case CIString::movsw: m_strOperation = "movsw"; break;
		case CIString::scasb: m_strOperation = "scasb"; break;
		case CIString::scasw: m_strOperation = "scasw"; break;
		default:
			_ASSERT(0);
		}

		switch (pInstruction->m_operation)		
		{
		case CIString::lodsb: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::lodsb); break;
		case CIString::stosb: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::stosb); break;
		case CIString::lodsw: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::lodsw); break;
		case CIString::stosw: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::stosw); break;
		case CIString::movsb: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::movsb); break;
		case CIString::movsw: m_strTemplate = CCZeroArgOp::GetTemplate(pInstruction->m_analysis, CIZeroArgOp::movsw); break;
		case CIString::scasb: m_strTemplate = ""; break;
		case CIString::scasw: m_strTemplate = ""; break;
		default:
			_ASSERT(0);
		}
	}
	
	virtual string ToString() override
	{
		return "_" + m_strRepeat + "_" + m_strOperation + m_strTemplate + "();";
	}
};

class CCSwitch : public CCInstruction
{
public:
	string m_strSelector;
	vector<CLabel> m_arrLabels;

public:
	CCSwitch(shared_ptr<CISwitch> pSwitch, vector<shared_ptr<CInstruction>> arrInstructions)
	{
		m_strSelector = pSwitch->m_reg.ToC();

		for (int i=0; i<(int)arrInstructions.size(); i++)
		{
			shared_ptr<CIData> pData = dynamic_pointer_cast<CIData>(arrInstructions[i]);
			_ASSERT(pData && pData->m_eType == CIData::Function);
			m_arrLabels.push_back(pData->m_strFunction);
		}
	}

	virtual string ToString() override
	{
		// TODO: how to optimize without gotos?
		stringstream ss;
		ss << "switch (" << m_strSelector << ")" << endl;
		ss << "{" << endl;
		for (int i=0; i<(int)m_arrLabels.size(); i++)
			ss << "  case " << i*2 << ": goto " << m_arrLabels[i] << ";" << endl;
		ss << "  default:" << endl;
		ss << "    _ASSERT(0);" << endl;
		ss << "}" << endl;

		return ss.str();
	}
};
