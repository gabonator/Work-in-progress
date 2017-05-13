//#include "instructions.h"

void CIAssignment::Eval(CMachine& m)
{
	if (m_valueFrom.m_eType != CValue::constant && m_valueFrom.m_eType != CValue::segment)
	{
		_ASSERT(m_valueFrom.GetRegisterLength() != CValue::invalid);
		_ASSERT(m_valueFrom.GetRegisterLength() == m_valueTo.GetRegisterLength());
	}
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
		if (m_op1.GetRegisterLength() == CValue::r8)
			m.m_flag.cf = m.GetValue(m_op1) & 0x80 ? true : false;
		else
		if (m_op1.GetRegisterLength() == CValue::r16)
			m.m_flag.cf = m.GetValue(m_op1) & 0x8000 ? true : false;
		else
			_ASSERT(0);

		m.SetValue(m_op1, m.GetValue(m_op1) << m.GetValue(m_op2)); 
		return;
	case CIAlu::Shr: 
		m.m_flag.cf = m.GetValue(m_op1) & 1 ? true : false;
		m.SetValue(m_op1, m.GetValue(m_op1) >> m.GetValue(m_op2)); 
		return;
	case CIAlu::Sar: 
		_ASSERT(m.GetValue(m_op2) == 1);
		if ( m.GetValue(m_op1) & 0x80 )
			m.SetValue(m_op1, m.GetValue(m_op1) >> m.GetValue(m_op2) | 0x80); 
		else
			m.SetValue(m_op1, m.GetValue(m_op1) >> m.GetValue(m_op2)); 
		return;
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

	case CISingleArgOp::div:
		{
			int divisor = m.GetValue(m_rvalue);
			int low = m.m_reg.a.r16.ax / divisor;
			int high = m.m_reg.a.r16.ax % divisor;
			m.m_reg.a.r8.al = low;
			m.m_reg.a.r8.ah = high;
		}
		return;
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
	case ja: return !m.m_flag.cf && !m.m_flag.zf; //?
	//case jb:
	//case jnb:
	case jle:return SatisfiesCondition2(m, eType);
	case jg:return SatisfiesCondition2(m, eType);
	//case jge:
	case jge: return SatisfiesCondition2(m, eType); //return m.m_flag.sf == 0;
	//case jns:
	case jl: return SatisfiesCondition2(m, eType);
	case jns:
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
	case jnb: return m.m_nCmpOp1 >= m.m_nCmpOp2;
	case jb: return m.m_nCmpOp1 < m.m_nCmpOp2;
	case ja: return m.m_nCmpOp1 > m.m_nCmpOp2;
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
	case jl:
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)m.m_nCmpOp1 < (char)m.m_nCmpOp2 ? true : false;
		case CValue::r16: return (short)m.m_nCmpOp1 < (short)m.m_nCmpOp2 ? true : false;
		default: break;
		}
	case jns: 
		switch (m.m_eCmpLen)
		{
		case CValue::r8: return (char)(m.m_nCmpOp1-m.m_nCmpOp2) >= 0 ? true : false;
		case CValue::r16: return (short)(m.m_nCmpOp1-m.m_nCmpOp2) >= 0 ? true : false;
		default: break;
		}
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
		if (bTest1 != bTest2 ) 
			printf("CIConditionalJump error\n");
		//_ASSERT(bTest1 == bTest2);
		bTest = bTest2;
	}
	else if (dynamic_cast<CIAlu*>(pInstruction.get()))
	{
		CIAlu* pAlu = dynamic_cast<CIAlu*>(pInstruction.get());
		switch (pAlu->m_eType)
		{
		case CIAlu::Or:
		case CIAlu::And:
			m.m_flag.zf = m.GetValue(pAlu->m_op1) == 0;
			_ASSERT(m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jnz);
			bTest = SatisfiesCondition1(m, m_eType);
			break;

		case CIAlu::Shr:
			m.m_flag.zf = m.GetValue(pAlu->m_op1) == 0;
			_ASSERT(m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jnz ||
				m_eType == CIConditionalJump::jb || m_eType == CIConditionalJump::jnb);
			bTest = SatisfiesCondition1(m, m_eType);
			break;

		case CIAlu::Decrement:
		case CIAlu::Sub:
		case CIAlu::Add:
			_ASSERT(m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnz
				 || m_eType == CIConditionalJump::jz || m_eType == CIConditionalJump::jb || m_eType == CIConditionalJump::jnb);
			_ASSERT(pAlu->m_op1.GetRegisterLength() == CValue::r16 || pAlu->m_op1.GetRegisterLength() == CValue::r8);
			
			if ( pAlu->m_op1.GetRegisterLength() == CValue::r16 )
			{
				if ( m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jb )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) < 0;

				if ( m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnb )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) >= 0;

				if ( m_eType == CIConditionalJump::jnz )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) != 0;

				if ( m_eType == CIConditionalJump::jz )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) == 0;
			} else 
			if ( pAlu->m_op1.GetRegisterLength() == CValue::r8 )
			{
				if ( m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jb )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) < 0;

				if ( m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnb )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) >= 0;

				if ( m_eType == CIConditionalJump::jnz )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) != 0;

				if ( m_eType == CIConditionalJump::jz )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) == 0;
			} else
			{
				_ASSERT(0);
			}
			break;
			/*
			_ASSERT(m_eType == CIConditionalJump::js || m_eType == CIConditionalJump::jns || m_eType == CIConditionalJump::jnz ||
				m_eType == CIConditionalJump::jb || m_eType == CIConditionalJump::jz);

			if ( m_eType == CIConditionalJump::jz )
				bTest = m.GetValue(pAlu->m_op1) == 0;

			if ( m_eType == CIConditionalJump::jnz )
				bTest = m.GetValue(pAlu->m_op1) != 0;

			if (pAlu->m_op1.GetRegisterLength() == CValue::r16)
			{
				// TODO "jb" a "js"
				if ( m_eType == CIConditionalJump::js )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) < 0;

				if ( m_eType == CIConditionalJump::jns )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) >= 0;

				if ( m_eType == CIConditionalJump::jb )
					bTest = ((signed short)m.GetValue(pAlu->m_op1)) < 0;
			} else
			if (pAlu->m_op1.GetRegisterLength() == CValue::r8)
			{
				if ( m_eType == CIConditionalJump::js )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) < 0;

				if ( m_eType == CIConditionalJump::jns )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) >= 0;

				if ( m_eType == CIConditionalJump::jb )
					bTest = ((signed char)m.GetValue(pAlu->m_op1)) < 0;
			} else
			{
				_ASSERT(0);
			}
			break;
			*/
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
	if (m_eType == jcxz)
	{
		if (m.m_reg.c.r16.cx == 0)
			m.Goto(m_label);
		return;
	}

	if ( EvalByPrevInstruction(m, m.m_arrCode[m.m_pc-2]) )
		return;

	for (int nTraceBack=m.m_pc-2; nTraceBack>m.m_pc-10; nTraceBack--)
	{
		shared_ptr<CInstruction> pInstruction = dynamic_pointer_cast<CInstruction>(m.m_arrCode[nTraceBack]);

		shared_ptr<CIConditionalJump> pConditional = dynamic_pointer_cast<CIConditionalJump>(pInstruction);
		if ( pConditional )
			continue;

		shared_ptr<CISingleArgOp> pSingleArgOp = dynamic_pointer_cast<CISingleArgOp>(m.m_arrCode[nTraceBack]);
		if (pSingleArgOp && pSingleArgOp->m_eType == CISingleArgOp::pop)
			continue;
		
		shared_ptr<CILoop> pLoop = dynamic_pointer_cast<CILoop>(m.m_arrCode[nTraceBack]);
		if ( pLoop )
			continue;

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

		if ( dynamic_pointer_cast<CICompare>(pInstruction) )
		{
			if ( EvalByPrevInstruction(m, pInstruction) )
				return;
			_ASSERT(0);
		}

		shared_ptr<CILabel> pLabel = dynamic_pointer_cast<CILabel>(m.m_arrCode[nTraceBack]);
		shared_ptr<CIJump> pPrevJump = dynamic_pointer_cast<CIJump>(m.m_arrCode[nTraceBack-1]);
		if ( pLabel && pPrevJump )
		{
			vector<int> arrRefs = m.FindReferences(pLabel->m_label);
			_ASSERT(arrRefs.size() == 1);

			if ( EvalByPrevInstruction(m, m.m_arrCode[arrRefs[0]-1]) )
				return;
		}

		shared_ptr<CICall> pCall = dynamic_pointer_cast<CICall>(m.m_arrCode[nTraceBack]);
		if ( pCall )
		{
			// TODO: trace stc/clc instructions recursively!
			if ( pCall->m_label == "sub_22F7" || pCall->m_label == "sub_265E" )
			{
				if ( SatisfiesCondition1(m, m_eType) )
					m.Goto(m_label);
				return;
			}

			int nLabel = m.FindLabel(pCall->m_label);
			int nEndPos = -1;

			for (int iTest = nLabel; iTest < nLabel + 100; iTest++)
			{
				shared_ptr<CIFunction> pReturn = dynamic_pointer_cast<CIFunction>(m.m_arrCode[iTest]);
				if ( pReturn && pReturn->m_eBoundary == CIFunction::End )
				{
					nEndPos = iTest-1;
					break;
				}
			}

			_ASSERT(nEndPos != -1);
			// TODO: unsafe !


			for (int iTest = nEndPos; iTest > nEndPos - 5; iTest--)
			{
				shared_ptr<CInstruction> pTestInstruction = dynamic_pointer_cast<CInstruction>(m.m_arrCode[iTest]);

				bool bOk = EvalByPrevInstruction(m, m.m_arrCode[iTest]);
				if (bOk)
					return;
				/*
				shared_ptr<CIFunction> pReturn = dynamic_pointer_cast<CIFunction>(pTestInstruction);
				if ( pReturn && pReturn->m_eBoundary == CIFunction::End )
				{
					shared_ptr<CIReturn> pLastReturn = dynamic_pointer_cast<CIReturn>(m.m_arrCode[iTest-1]);
					_ASSERT(pLastReturn);
					bool bOk = EvalByPrevInstruction(m, m.m_arrCode[iTest-2]);
					_ASSERT(bOk);
					return;
				}*/
				/*
				shared_ptr<CIConditionalJump> pConditional = dynamic_pointer_cast<CIConditionalJump>(pTestInstruction);
				//shared_ptr<CILabel> pLabel = dynamic_pointer_cast<CILabel>(pTestInstruction);
				shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(pTestInstruction);
				_ASSERT(!pConditional);
				//_ASSERT(!pLabel);
				_ASSERT(!pJump);
				*/
				shared_ptr<CIZeroArgOp> pZeroArg = dynamic_pointer_cast<CIZeroArgOp>(pTestInstruction);
				if ( pZeroArg && (pZeroArg->m_eType == CIZeroArgOp::clc || pZeroArg->m_eType == CIZeroArgOp::stc))
				{	
					// TODO: verify stc/ctc flow
					if ( SatisfiesCondition1(m, m_eType) )
						m.Goto(m_label);
					return;
				}
			}
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
		return;
	}

	if (m_eType == CITwoArgOp::rcr)
	{
		_ASSERT( m.GetValue(m_rvalue2) == 1 );
		int nValue = m.GetValue(m_rvalue1); 
		bool ncf = nValue & 1;
		nValue >>= 1;
		if ( m.m_flag.cf )
			nValue |= 0x8000;
		m.m_flag.cf = ncf;
		m.SetValue(m_rvalue1, nValue);
		return;
	}

	if (m_eType == CITwoArgOp::rcl)
	{
		_ASSERT( m.GetValue(m_rvalue2) == 1 );
		int nValue = m.GetValue(m_rvalue1); 
		bool ncf = !!(nValue & 128);
		nValue <<= 1;
		if ( m.m_flag.cf )
			nValue |= 1;
		m.m_flag.cf = ncf;
		m.SetValue(m_rvalue1, nValue);
		return;
	}

	if (m_eType == CITwoArgOp::xchg)
	{
		_ASSERT( m_rvalue1.GetRegisterLength() != CValue::invalid );
		_ASSERT( m_rvalue1.GetRegisterLength() == m_rvalue2.GetRegisterLength() );
		CValue temp = m_rvalue1;
		m_rvalue1 = m_rvalue2;
		m_rvalue2 = temp;
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
	case CIZeroArgOp::lahf: m.m_reg.a.r8.ah = m.m_flag.ToByte(); return;
	case CIZeroArgOp::sahf: m.m_flag.FromByte(m.m_reg.a.r8.ah); return;
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
			m.m_reg.c.r16.cx = 0;
			return;
		case CIString::lodsb:
			_ASSERT(0);
			break;
		case CIString::stosw:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalStosw(m);
			m.m_reg.c.r16.cx = 0;
			return;
		case CIString::lodsw: 
			_ASSERT(0);
			break;
		case CIString::movsw:
			_ASSERT(m.m_reg.c.r16.cx);
			_ASSERT(m.m_flag.df == false);
			while (m.m_reg.c.r16.cx--) 
				EvalMovsw(m);
			m.m_reg.c.r16.cx = 0;
			return;
		case CIString::movsb:
			_ASSERT(m.m_reg.c.r16.cx);
			while (m.m_reg.c.r16.cx--) 
				EvalMovsb(m);
			m.m_reg.c.r16.cx = 0;
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
	if (m.m_flag.df)
		m.MappedWrite(m.m_reg.es, m.m_reg.di--, m.MappedRead(m.m_reg.ds, m.m_reg.si--));
	else
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
	m.m_reg.a.r8.al = m.MappedRead(m.m_reg.ds, m.m_reg.si++);// ds:si
}

void CIString::EvalLodsw(CMachine& m)
{
	m.m_reg.a.r8.al = m.MappedRead(m.m_reg.ds, m.m_reg.si++);
	m.m_reg.a.r8.ah = m.MappedRead(m.m_reg.ds, m.m_reg.si++);
}

void CIString::EvalStosb(CMachine& m)
{
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.m_reg.a.r8.al);
}

void CIString::EvalStosw(CMachine& m)
{
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.m_reg.a.r8.al);
	m.MappedWrite(m.m_reg.es, m.m_reg.di++, m.m_reg.a.r8.ah);
}

void CILoop::Eval(CMachine& m)
{ 
	switch (m_eType)
	{
	case CILoop::Loop:
		if ( !m.m_reg.c.r16.cx )
			return;
		if ( --m.m_reg.c.r16.cx )
			m.Goto(m_label);
		return;

	case CILoop::WhileEqual:
		{
			if ( !m.m_reg.c.r16.cx )
				return;

			_ASSERT(dynamic_pointer_cast<CICompare>(m.m_arrCode[m.m_pc-2]));
			bool bConditionEqual = m.m_nCmpOp1 == m.m_nCmpOp2;

			if ( --m.m_reg.c.r16.cx && bConditionEqual )
				m.Goto(m_label);

		}
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
