//#include "instructions.h"

void CIAssignment::Eval(CMachine& m)
{
	int nValue = m.GetValue(m_valueFrom);
	m.SetValue(m_valueTo, nValue);
}

void CIAlu::Eval(CMachine& m)
{
	switch (m_eType)
	{
	case CIAlu::Add:
	case CIAlu::Sub:
	case CIAlu::Xor:
	case CIAlu::And:
	case CIAlu::Or:
	case CIAlu::AddWithCarry:
		if ( m_op2.m_eType != CValue::constant )
			_ASSERT(m_op1.GetRegisterLength() == m_op2.GetRegisterLength());
	}
	
	switch (m_eType)
	{
	case CIAlu::Increment: m.SetValue(m_op1, m.GetValue(m_op1)+1); return;
	case CIAlu::Decrement: m.SetValue(m_op1, m.GetValue(m_op1)-1); return;
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
	case CIAlu::Shl: 
		m.SetValue(m_op1, m.GetValue(m_op1) << m.GetValue(m_op2)); 
		return;
	case CIAlu::Shr: 
		m.SetValue(m_op1, m.GetValue(m_op1) >> m.GetValue(m_op2)); 
		return;
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
		m.StackWrite(m.m_reg.sp, m.GetValue(m_rvalue));
		/*
		_ASSERT(m.m_reg.sp/2 > 0 && m.m_reg.sp/2 < (int)m.m_arrStack.size());
		_ASSERT((m.m_reg.sp & 1) == 0);
		m.m_arrStack[m.m_reg.sp/2] = m.GetValue(m_rvalue);
		*/
		m.m_reg.sp -= 2;
		break;

	case CISingleArgOp::pop:
		_ASSERT(m_rvalue.GetRegisterLength() == CValue::r16);
		m.m_reg.sp += 2;
		/*
		_ASSERT(m.m_reg.sp/2 > 0 && m.m_reg.sp/2 < (int)m.m_arrStack.size());
		m.SetValue(m_rvalue, m.m_arrStack[m.m_reg.sp/2]);
		*/
		m.SetValue(m_rvalue, m.StackRead(m.m_reg.sp));
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

	if (m_op2.m_eType != CValue::constant)
	{
		_ASSERT(m_op1.GetRegisterLength() == m_op2.GetRegisterLength());
	}

	m.m_eCmpLen = m_op1.GetRegisterLength();
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
	case jnb: /*return SatisfiesCondition2(m, eType); //*/ return !m.m_flag.cf; // TODO!!!
	case jb: /*return SatisfiesCondition2(m, eType); //*/ return m.m_flag.cf; // TODO!!!!
	//case ja:
	//case jb:
	//case jnb:
	case jle:return SatisfiesCondition2(m, eType);
	case jg:return SatisfiesCondition2(m, eType);
	//case jge:
	case jge: return SatisfiesCondition2(m, eType); //return m.m_flag.sf == 0;
	//case jns:
	//case jl:
	case js: return SatisfiesCondition2(m, eType);
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
	case jb: return m.m_nCmpOp1 <= m.m_nCmpOp2;
	//case ja:
	//case jb:
	//case jnb:
	case jle:
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)m.m_nCmpOp1 <= (char)m.m_nCmpOp2 ? true : false;
		case CValue::r16: return (short)m.m_nCmpOp1 <= (short)m.m_nCmpOp2 ? true : false;
		default: break;
		}		
	case jg:
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)m.m_nCmpOp1 > (char)m.m_nCmpOp2 ? true : false;
		case CValue::r16: return (short)m.m_nCmpOp1 > (short)m.m_nCmpOp2 ? true : false;
		default: break;
		}		
	case jge:
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)m.m_nCmpOp1 >= (char)m.m_nCmpOp2 ? true : false;
		case CValue::r16: return (short)m.m_nCmpOp1 >= (short)m.m_nCmpOp2 ? true : false;
		default: break;
		}		
	//case jns:
	//case jl:
	case js:
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)(m.m_nCmpOp1-m.m_nCmpOp2) < 0 ? true : false;
		case CValue::r16: return (short)(m.m_nCmpOp1-m.m_nCmpOp2) < 0 ? true : false;
		default: break;
		}
	//case jcxz:
	default:
		_ASSERT(0);
	}
	_ASSERT(0);
	return false;
}

bool CIConditionalJump::EvalByPrevInstruction(CMachine& m, shared_ptr<CInstruction> pInstruction)
{
	bool bTest = false;

	if (dynamic_cast<CITest*>(pInstruction.get()))
	{
		_ASSERT(m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jnz);
		bTest = SatisfiesCondition1(m, m_eType);
	} else
	if (dynamic_cast<CICompare*>(pInstruction.get()))
	{
		bool bTest1 = SatisfiesCondition1(m, m_eType);
		bool bTest2 = SatisfiesCondition2(m, m_eType);
		if (bTest1 != bTest2 ) printf("CIConditionalJump error\n");
		//_ASSERT(bTest1 == bTest2);
		bTest = bTest2;
	}
	else if (dynamic_cast<CIAlu*>(pInstruction.get()))
	{
		CIAlu* pAlu = dynamic_cast<CIAlu*>(pInstruction.get());
		switch (pAlu->m_eType)
		{
		case CIAlu::And:
			m.m_flag.zf = m.GetValue(pAlu->m_op1) == 0;
			_ASSERT(m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jnz);
			bTest = SatisfiesCondition1(m, m_eType);
			break;

		case CIAlu::Shr:
			m.m_flag.zf = m.GetValue(pAlu->m_op1) == 0;
			_ASSERT(m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jnz);
			bTest = SatisfiesCondition1(m, m_eType);
			break;

		case CIAlu::Decrement:
			_ASSERT(m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnz);
			if ( m_eType == CIConditionalJump::js )
				bTest = m.GetValue(pAlu->m_op1) < 0;

			if ( m_eType == CIConditionalJump::jns )
				bTest = m.GetValue(pAlu->m_op1) >= 0;

			if ( m_eType == CIConditionalJump::jnz )
				bTest = m.GetValue(pAlu->m_op1) > 0;
			break;

		case CIAlu::Sub:
		case CIAlu::Add:
			_ASSERT(m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnz);
			_ASSERT(pAlu->m_op1.GetRegisterLength() == CValue::r16);

			if ( m_eType == CIConditionalJump::js )
				bTest = ((signed short)m.GetValue(pAlu->m_op1)) < 0;

			if ( m_eType == CIConditionalJump::jns )
				bTest = ((signed short)m.GetValue(pAlu->m_op1)) >= 0;

			if ( m_eType == CIConditionalJump::jnz )
				bTest = ((signed short)m.GetValue(pAlu->m_op1)) != 0;
			break;

		default:
			_ASSERT(0);
			return false;
		}
	} else
	{
		return false;
	}

	if ( bTest )
	{
		m.Goto(m_label);
	}
	return true;
}

void CIConditionalJump::Eval(CMachine& m)
{	
	if ( EvalByPrevInstruction(m, m.m_arrCode[m.m_pc-2]) )
		return;

	for (int nTraceBack=m.m_pc-2; nTraceBack>m.m_pc-10; nTraceBack--)
	{
		CISingleArgOp* pSingleArgOp = dynamic_cast<CISingleArgOp*>(m.m_arrCode[nTraceBack].get());
		if (pSingleArgOp && pSingleArgOp->m_eType == CISingleArgOp::pop)
			continue;

		if (pSingleArgOp && pSingleArgOp->m_eType == CISingleArgOp::interrupt)
		{
			// uses CF to transfer state
			_ASSERT(m_eType == CIConditionalJump::jb || m_eType == CIConditionalJump::jnb);
			bool bTest = SatisfiesCondition1(m, m_eType);
			if ( bTest )
			{
				m.Goto(m_label);
			}
			return;
		}

		CILabel* pLabel = dynamic_cast<CILabel*>(m.m_arrCode[nTraceBack].get());
		CIJump* pPrevJump = dynamic_cast<CIJump*>(m.m_arrCode[nTraceBack-1].get());
		if ( pLabel && pPrevJump )
		{
			vector<int> arrRefs = m.FindReferences(pLabel->m_label);
			_ASSERT(arrRefs.size() == 1);

			if ( EvalByPrevInstruction(m, m.m_arrCode[arrRefs[0]-1]) )
				return;
		}

		_ASSERT(0);
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
		//printf("out[%x] = %x\n", m.GetValue(m_rvalue1), m.GetValue(m_rvalue2));
		if (m_rvalue2.GetRegisterLength() == CValue::r16)
			m.PortWrite16(m.GetValue(m_rvalue1), m.GetValue(m_rvalue2));
		else
		if (m_rvalue2.GetRegisterLength() == CValue::r8)
			m.PortWrite8(m.GetValue(m_rvalue1), m.GetValue(m_rvalue2));
		else
			_ASSERT(0);

		return;
	}
	if (m_eType == CITwoArgOp::in)
	{
		_ASSERT(m_rvalue1.GetRegisterLength() == CValue::r8);

		m.SetValue(m_rvalue1, m.PortRead(m.GetValue(m_rvalue2)));
		//printf("in[%x] = %x\n", m.GetValue(m_rvalue2), m.GetValue(m_rvalue1));
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
	case CIZeroArgOp::lodsb: CIString::EvalLodsb(m); return;
	case CIZeroArgOp::lodsw: CIString::EvalLodsw(m); return;
	//case CIZeroArgOp::stosb: CIString::EvalStosb(m); return;
	case CIZeroArgOp::stosw: CIString::EvalStosw(m); return;
	case CIZeroArgOp::movsb: CIString::EvalMovsb(m); return;
	case CIZeroArgOp::movsw: CIString::EvalMovsw(m); return;
	case CIZeroArgOp::cbw: 
		if (m.m_reg.a.r8.al & 0x80)
			m.m_reg.a.r8.ah = 0xff;
		else
			m.m_reg.a.r8.ah = 0x00;
		return;
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
			_ASSERT(0);
			break;
		case CIString::stosw:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalStosw(m);
			return;
		case CIString::lodsw: 
			_ASSERT(0);
			break;
		case CIString::movsw:
			_ASSERT(0);
			break;
		case CIString::movsb:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalMovsb(m);
			return;
		}

		break;
	case CIString::repne:
		break;
	}
	_ASSERT(0);
}

void CIString::EvalMovsb(CMachine& m)
{
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.MappedRead(m.m_reg.ds, m.m_reg.si++));
}

void CIString::EvalMovsw(CMachine& m)
{
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.MappedRead(m.m_reg.ds, m.m_reg.si++));
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.MappedRead(m.m_reg.ds, m.m_reg.si++));
}

void CIString::EvalLodsb(CMachine& m)
{
	_ASSERT(m.m_flag.df == false);
	_ASSERT(m.m_reg.ds < 0xa000);
	m.m_reg.a.r8.al = m.MappedRead(m.m_reg.ds, m.m_reg.si);
	m.m_reg.si++;
	_ASSERT(m.m_reg.si < 0xfff5);
}

void CIString::EvalLodsw(CMachine& m)
{
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

void CILoop::Eval(CMachine& m)
{ 
	if ( m_label == "loc_3406" )
	{
		int f = 9;
	}

	switch (m_eType)
	{
	case CILoop::Loop:
		if ( !m.m_reg.c.r16.cx )
			return;
		if ( --m.m_reg.c.r16.cx )
			m.Goto(m_label);
		return;
	}
	_ASSERT(0);
}

void CIFunction::Eval(CMachine& m)
{
	if (m_eBoundary == CIFunction::End)
	{
		m.Return();
		return;
	}
	_ASSERT(0);	
}

void CIJump::Eval(CMachine& m)
{
	m.Goto(m_label);
}

void CITest::Eval(CMachine& m)
{
	m.m_flag.zf = !(m.GetValue(m_op1) & m.GetValue(m_op2));
}

void CISwitch::Eval(CMachine& m)
{
	int nTable = m.FindLabel(m_label);
	int nRow = nTable + m.GetValue(m_reg) / 2;
	
	for (int i=nTable; i<=nRow; i++)
	{
		// TODO: could be db, dw... check contents between table start and target
		shared_ptr<CIData> pTest = dynamic_pointer_cast<CIData>(m.m_arrCode[i]);
		_ASSERT(pTest && pTest->m_eType == CIData::Function);
	}
	shared_ptr<CIData> pData = dynamic_pointer_cast<CIData>(m.m_arrCode[nRow]);
	_ASSERT(pData && pData->m_eType == CIData::Function);

	m.Call(CLabel(pData->m_strFunction));
}
