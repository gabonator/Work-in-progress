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
			return make_shared<CILabel>(arrMatches[0]);
			//return make_shared<CINop>();
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

		if ( CUtils::match("^retf$", strLine, arrMatches) )
		{
			// TODO:
			//https://courses.engr.illinois.edu/ece390/archive/spr2002/books/labmanual/inst-ref-ret.html
			return make_shared<CIReturn>();
		}

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

		if ( CUtils::match("^(cli|sti|std|stc|ctc|cld|aaa|cbw|lodsw|lodsb|stosb|stosw|movsw|movsb|clc|sahf|lahf|popf|pushf|xlat)$", strLine, arrMatches) )
		{
			return make_shared<CIZeroArgOp>(CIZeroArgOp::GetType(arrMatches[0]));
		}

		if ( CUtils::match("^(out|in|xchg|rcr|rcl|rol|les|lea|sbb)[\\s]+(.*),\\s*(.*)$", strLine, arrMatches) )
		{
			if ( arrMatches[0] == "lea" )
				return make_shared<CITwoArgOp>(CITwoArgOp::GetType(arrMatches[0]), CValue(arrMatches[1]), CValue(arrMatches[2], CValue::r16));
			else if ( arrMatches[0] == "xchg" )
			{
				CValue op1, op2;
				CValue::SameOperands(op1, op2, arrMatches[1], arrMatches[2]);
				return make_shared<CITwoArgOp>(CITwoArgOp::GetType(arrMatches[0]), op1, op2);
			}
			else
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

		if ( CUtils::match("^(rep|repne)\\s+(stosb|lodsb|stosw|lodsw|movsw|movsb|scasw|scasb)$", strLine, arrMatches) )
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
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::AddWithCarry, op1, op2);
		}

		if ( CUtils::match("^xor\\s+(.*),\\s*(.*)", strLine, arrMatches) )
		{
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);
			return make_shared<CIAlu>(CIAlu::Xor, op1, op2);
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

		if ( CUtils::match("^jmp\\s+cs:(off_code_\\w+)\\[(.*)\\]$", strLine, arrMatches) )
		{
			return make_shared<CISwitch>(arrMatches[0], CValue(arrMatches[1]));
		}

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
		
		//WTF: call dword ptr cs:[bp+7FBh]
		if ( CUtils::match("^call dword ptr cs:(off_code_\\w+)\\[(.*)\\]$", strLine, arrMatches) )
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
			CValue op1, op2;
			CValue::SameOperands(op1, op2, arrMatches[0], arrMatches[1]);

			return make_shared<CITest>(op1, op2);
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

		if ( strLine == "align 4" )
		{
			return make_shared<CINop>(strLine);
		}

		if ( strLine == "align 8" )
		{
			return make_shared<CINop>(strLine);
		}

		if ( strLine == "align 10h" )
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

		if ( strLine == "code  ends" || strLine == "end start")
		{
			return make_shared<CINop>(strLine);
		}

		return nullptr;
	}
};
