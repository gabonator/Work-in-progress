class CAnalysis
{
public:
	vector<shared_ptr<CInstruction>> m_arrCode;
	vector<string> m_arrSource;

	set<CLabel> m_unique;
	list<pair<CLabel, CStaticAnalysis>> m_queue;

	CAnalysis(vector<shared_ptr<CInstruction>>& arrCode, vector<string>& arrSource) : 
		m_arrCode(arrCode), m_arrSource(arrSource)
	{
	}

	void Process()
	{
		CStaticAnalysis current;
		
		//m_queue.push_back(make_pair<CLabel, CForwardAnalysis>(CLabel("sub_1124"), current));
		//m_queue.push_back(make_pair<CLabel, CForwardAnalysis>(CLabel("sub_1166"), current));
		m_queue.push_back(make_pair<CLabel, CStaticAnalysis>(CLabel("start"), current));

		while (!m_queue.empty())
		{
			pair<CLabel, CStaticAnalysis> p = m_queue.front();
			m_queue.pop_front();
			m_unique.insert(p.first);
			TraceFunction(p.first, p.second);
		}

		// TODO: mali by sme testovat ci viacnasobny entry do funkcie ma vzdy rovnake registre, kolizie nahradit dirty

		//TraceFunction("sub_1166", current)
	}

	void TraceFunction(CLabel name, CStaticAnalysis state)
	{
		vector<shared_ptr<CInstruction>> arrCode = GetSubCode(m_arrCode, name);
		for (int i=0; i<(int)arrCode.size(); i++)
		{
			// zaujimaju nas operacia priradenia, push, pop, cld, std
			shared_ptr<CInstruction> pInstruction = arrCode[i];
			shared_ptr<CIAssignment> pAssign = dynamic_pointer_cast<CIAssignment>(pInstruction);

			pInstruction->m_analysis = state;

			if ( pAssign )
			{
				if ( pAssign->m_valueTo.m_eType == CValue::ax )
				{
					if (pAssign->m_valueFrom.m_eType == CValue::constant)
					{
						state.m_ax.SetValue(pAssign->m_valueFrom.m_nValue);
						continue;
					}
					if (pAssign->m_valueFrom.m_eType == CValue::segment)
					{
						_ASSERT(pAssign->m_valueFrom.m_eSegment == CValue::dseg);
						state.m_ax.SetValue(0);
						continue;
					}
					
					state.m_ax.SetDirty();
					continue;
				}
				if ( pAssign->m_valueTo.m_eType == CValue::ah ||  pAssign->m_valueTo.m_eType == CValue::al )
				{
					state.m_ax.SetDirty();
					continue;
				}
				if ( pAssign->m_valueTo.m_eType == CValue::es )
				{
					_ASSERT(pAssign->m_valueFrom.m_eType == CValue::ax);
					state.m_es = state.m_ax;
					continue;
				}
				if ( pAssign->m_valueTo.m_eType == CValue::ds )
				{
					_ASSERT(pAssign->m_valueFrom.m_eType == CValue::ax);
					state.m_ds = state.m_ax;
					continue;
				}
				continue;
			}

			shared_ptr<CIAlu> pAlu = dynamic_pointer_cast<CIAlu>(pInstruction);
			if (pAlu)
			{
				if ( pAlu->m_op1.m_eType == CValue::ah || pAlu->m_op1.m_eType == CValue::al || pAlu->m_op1.m_eType == CValue::ax )
					state.m_ax.SetDirty();
				continue;
			}

			shared_ptr<CIZeroArgOp> pZeroArg = dynamic_pointer_cast<CIZeroArgOp>(pInstruction);
			if (pZeroArg)
			{
				if ( pZeroArg->m_eType == CIZeroArgOp::cld )
					state.m_direction.SetValue(0);
				if ( pZeroArg->m_eType == CIZeroArgOp::_std )
					state.m_direction.SetValue(1);
				if ( pZeroArg->m_eType == CIZeroArgOp::sahf )
					state.m_direction.SetDirty();
				continue;
			}

			shared_ptr<CISingleArgOp> pSingleArg = dynamic_pointer_cast<CISingleArgOp>(pInstruction);
			if ( pSingleArg )
			{
				if (pSingleArg->m_eType == CISingleArgOp::push)
				{
					if ( pSingleArg->m_rvalue.m_eType == CValue::ax )
						state.m_stack = state.m_ax;
					else if ( pSingleArg->m_rvalue.m_eType == CValue::ds )
						state.m_stack = state.m_ds;
					else
						state.m_stack.SetDirty();
					continue;
				}
				if (pSingleArg->m_eType == CISingleArgOp::pop)
				{
					if ( pSingleArg->m_rvalue.m_eType == CValue::ax )
						state.m_ax = state.m_stack;
					else if ( pSingleArg->m_rvalue.m_eType == CValue::ds )
						state.m_ds = state.m_stack;
					else if ( pSingleArg->m_rvalue.m_eType == CValue::es )
						state.m_es = state.m_stack;
					continue;
				}
				continue;
			}

			shared_ptr<CICall> pCall = dynamic_pointer_cast<CICall>(pInstruction);
			if ( pCall )
			{
				// TODO: ak uz je, tak assertnut identitu!!!
				if ( m_unique.find(pCall->m_label) == m_unique.end() )
					m_queue.push_back(make_pair<CLabel, CStaticAnalysis>(pCall->m_label, state));

				continue;
			}

			// skip jumps, conditions, etc...
			shared_ptr<CIString> pString = dynamic_pointer_cast<CIString>(pInstruction);
			if (pString)
			{
				//printf("string op: %s ds=%x es=%x dir=%d\n", name.c_str(), state.m_ds.GetValue(), state.m_es.GetValue(), state.m_direction.GetValue());
			}

		}
	}

	// TODO: Duplicity
	int FindLabel(const vector<shared_ptr<CInstruction>>& arrCode, string label)
	{
		for (int i=0; (size_t)i<arrCode.size(); i++)
		{
			shared_ptr<CIFunction> pFunction = dynamic_pointer_cast<CIFunction>(arrCode[i]);
			if (pFunction && pFunction->m_eBoundary == CIFunction::Begin && pFunction->m_strName == label)
			{
				return i;
			}
		}
		_ASSERT(0);
		return -1;
	}

	vector<shared_ptr<CInstruction>> GetSubCode(const vector<shared_ptr<CInstruction>>& arrCode, CLabel label)
	{
		vector<shared_ptr<CInstruction>> aux;

		if ( label.find("nullsub") != string::npos)
			return move(aux);

		int nBegin = FindLabel(arrCode, label);
		_ASSERT(nBegin >= 0);
		for (int i=nBegin+1; i<(int)arrCode.size() && !dynamic_pointer_cast<CIFunction>(arrCode[i]); i++)
			aux.push_back(arrCode[i]);

		return move(aux);
	}

};

