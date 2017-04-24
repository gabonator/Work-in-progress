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
	case CIZeroArgOp::lodsb: CIString::EvalLodsb(m); return;
	case CIZeroArgOp::lodsw: CIString::EvalLodsw(m); return;
	//case CIZeroArgOp::stosb: CIString::EvalStosb(m); return;
	case CIZeroArgOp::stosw: CIString::EvalStosw(m); return;
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

void CIString::EvalLodsb(CMachine& m)
{
	int es = m.m_reg.es;
	_ASSERT(m.m_flag.df == false);
	_ASSERT(m.m_reg.ds < 0xa000);
	m.m_reg.a.r8.al = data[m.m_reg.ds*16 + m.m_reg.si];
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
	switch (m_eType)
	{
	case CILoop::Loop:
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
