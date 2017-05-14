class CCExport
{
	vector<shared_ptr<CInstruction>> m_arrSource;

public:
	int CountRefs(vector<shared_ptr<CCInstruction>>& arrOutput, CLabel label)
	{
		int nCount = 0;

		for (int i=0; i<(int)arrOutput.size(); i++)
		{
			shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i]);
			if ( pJump && pJump->GetLabel() == label )
				nCount++;
		}

		return nCount;
	}

	vector<int> FindReferences(const vector<shared_ptr<CInstruction>>& arrCode, CLabel label)
	{
		vector<int> aux;

		for (int i=0; (size_t)i<arrCode.size(); i++)
		{
			shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(arrCode[i]);
			if (pJump && pJump->m_label == label)
				aux.push_back(i);

			shared_ptr<CIConditionalJump> pConditional = dynamic_pointer_cast<CIConditionalJump>(arrCode[i]);
			if (pConditional && pConditional->m_label == label)
				aux.push_back(i);
		}

		return move(aux);
	}

	vector<shared_ptr<CInstruction>> GetDataStarting(CLabel label)
	{
		vector<shared_ptr<CInstruction>> aux;
		bool bFound = false;

		for (int i=0; (size_t)i<m_arrSource.size(); i++)
		{
			shared_ptr<CIData> pData = dynamic_pointer_cast<CIData>(m_arrSource[i]);
			if (pData)
			{
				if (!bFound)
					bFound = true;
			} else
			{
				if (bFound)
					return aux;
			}

			if (bFound)
				aux.push_back(pData);
		}

		_ASSERT(0);
		return aux;
	}

	shared_ptr<CCInstruction> Convert(string strFunction, shared_ptr<CInstruction> pInInstruction, shared_ptr<CInstruction> pPrevious)
	{
		shared_ptr<CCInstruction> pOutInstruction;

		if ( dynamic_pointer_cast<CINop>(pInInstruction) )
			return nullptr;

		shared_ptr<CICompare> pCompare = dynamic_pointer_cast<CICompare>(pInInstruction);
		if ( pCompare )
		{
			// TODO: Automatic
			if (strFunction=="")
			{
				pOutInstruction = make_shared<CCCompare>(pCompare, CCCompare::ZeroCarryFlag);
			} else
			if (strFunction=="sub_658")
			{
				pOutInstruction = make_shared<CCCompare>(pCompare, CCCompare::ZeroFlag);
			} else
			if (strFunction=="sub_34A0")
			{
				pOutInstruction = make_shared<CCCompare>(pCompare, CCCompare::ZeroCarryFlag);
			} else
				return nullptr;
		}
		if (dynamic_pointer_cast<CITest>(pInInstruction) )
		{
			return nullptr;
		}

		if ( dynamic_pointer_cast<CIData>(pInInstruction) && dynamic_pointer_cast<CIData>(pInInstruction)->m_eType == CIData::Function )
		{
			return nullptr;
		}

		shared_ptr<CIReturn> pReturn = dynamic_pointer_cast<CIReturn>(pInInstruction);
		/*
		if (pReturn && i == arrInput.size()-1 && pReturn->m_nReduceStack == 0)
			return nullptr;
			*/

		if (pReturn)
			pOutInstruction = make_shared<CCReturn>( pReturn );

		shared_ptr<CIAssignment> pAssignment = dynamic_pointer_cast<CIAssignment>(pInInstruction);
		if (pAssignment)
			pOutInstruction = make_shared<CCAssignment>( pAssignment->m_valueTo, pAssignment->m_valueFrom);

		shared_ptr<CIAlu> pAlu = dynamic_pointer_cast<CIAlu>(pInInstruction);
		if (pAlu)
			pOutInstruction = make_shared<CCAssignment>( pAlu );

		shared_ptr<CIZeroArgOp> pZeroArgOp = dynamic_pointer_cast<CIZeroArgOp>(pInInstruction);
		if (pZeroArgOp)
			pOutInstruction = make_shared<CCZeroArgOp>( pZeroArgOp );

		shared_ptr<CISingleArgOp> pSingleArgOp = dynamic_pointer_cast<CISingleArgOp>(pInInstruction);
		if (pSingleArgOp)
			pOutInstruction = make_shared<CCSingleArgOp>( pSingleArgOp );

		shared_ptr<CITwoArgOp> pTwoArgOp = dynamic_pointer_cast<CITwoArgOp>(pInInstruction);
		if (pTwoArgOp)
			pOutInstruction = make_shared<CCTwoArgOp>( pTwoArgOp );

		shared_ptr<CIString> pStringOp = dynamic_pointer_cast<CIString>(pInInstruction);
		if (pStringOp)
			pOutInstruction = make_shared<CCStringOp>(pStringOp);

		shared_ptr<CIConditionalJump> pConditionalJump = dynamic_pointer_cast<CIConditionalJump>(pInInstruction);
		if (pConditionalJump)
			pOutInstruction = make_shared<CCConditionalJump>( pConditionalJump, pPrevious );

		shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(pInInstruction);
		if (pJump)
			pOutInstruction = make_shared<CCConditionalJump>( pJump );

		shared_ptr<CILabel> pLabel = dynamic_pointer_cast<CILabel>(pInInstruction);
		if (pLabel)
			pOutInstruction = make_shared<CCLabel>( pLabel );

		shared_ptr<CICall> pCall = dynamic_pointer_cast<CICall>(pInInstruction);
		if (pCall)
			pOutInstruction = make_shared<CCCall>( pCall );

		shared_ptr<CISwitch> pSwitch = dynamic_pointer_cast<CISwitch>(pInInstruction);
		if (pSwitch)
		{
			vector<shared_ptr<CInstruction>> arrOptions = GetDataStarting(pSwitch->m_label);
			pOutInstruction = make_shared<CCSwitch>( pSwitch, arrOptions );
		}

		shared_ptr<CILoop> pLoop = dynamic_pointer_cast<CILoop>(pInInstruction);
		if (pLoop)
		{
			if ( pLoop->m_eType != CILoop::Loop )
			{
				_ASSERT(pPrevious);
			}

			pOutInstruction = make_shared<CCConditionalJump>( pLoop, pPrevious );
		}
			
		_ASSERT(pOutInstruction);
		return pOutInstruction;
	}

	shared_ptr<CInstruction> TracebackCondition(CIConditionalJump::EType eType, vector<shared_ptr<CInstruction>>& arrInput, int nLine)
	{
		for (int nTraceBack=nLine; nTraceBack>=max(0, nLine-10); nTraceBack--)
		{
			shared_ptr<CInstruction> pPrev = nTraceBack > 0 ? arrInput[nTraceBack-1] : nullptr;
			shared_ptr<CInstruction> pInstruction = arrInput[nTraceBack];

			if (dynamic_pointer_cast<CITest>(pInstruction) || dynamic_pointer_cast<CICompare>(pInstruction) ||
				dynamic_pointer_cast<CIAlu>(pInstruction) )
			{
				return pInstruction;
			}
			if (dynamic_pointer_cast<CIConditionalJump>(pInstruction) || dynamic_pointer_cast<CILoop>(pInstruction) )
			{
				continue;
			}
			if (dynamic_pointer_cast<CISingleArgOp>(pInstruction) && dynamic_pointer_cast<CISingleArgOp>(pInstruction)->m_eType == CISingleArgOp::pop)
			{
				continue;
			}
			if (dynamic_pointer_cast<CISingleArgOp>(pInstruction) && dynamic_pointer_cast<CISingleArgOp>(pInstruction)->m_eType == CISingleArgOp::interrupt)
			{
				return pInstruction;
			}
			if ( dynamic_pointer_cast<CILabel>(pInstruction) && dynamic_pointer_cast<CIJump>(pPrev) )
			{
				vector<int> arrRefs = FindReferences(arrInput, dynamic_pointer_cast<CILabel>(pInstruction)->m_label);
				_ASSERT(arrRefs.size() == 1);

				return TracebackCondition(eType, arrInput, arrRefs[0]);
			}
			if (dynamic_pointer_cast<CICall>(pInstruction))
			{
				// Toto musime manualne!!!
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_13D8" ) // alu op -> AL
				{
					return make_shared<CIAlu>(CIAlu::And, CValue("al"), CValue("8", CValue::r8));
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_658" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeZeroTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_34A0" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeZeroCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_1B7A" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_20F5" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_FC9" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_1608" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_22F7" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_1657" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_2E29" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_3C43" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_1B05" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_1B4C" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_265E" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_2567" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_33BA" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_21E0" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_3E52" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_3E6E" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_4065" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_42DB" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_42FC" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_431C" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_4557" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_4786" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_44E7" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_473E" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_47B0" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_502D" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_4DD0" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_5FE5" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_600F" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				if ( dynamic_pointer_cast<CICall>(pInstruction)->m_label == "sub_62A6" ) // need to use FLAGS!!!
				{
					//TODO: totally fake instruction just to let know that we need to use flag test
					return make_shared<CIZeroArgOp>( CIZeroArgOp::FakeCarryTest );
				} else
				{
					//vector<shared_ptr<CInstruction>> arrSub = GetSubCode(arrSource, pFunction->m_strName)
					//dynamic_pointer_cast<CICall>(pInstruction)->m_label

					_ASSERT(0);
				}
				return pInstruction;
			}
		}
		_ASSERT(0);
		return nullptr;
	}

	void Convert(CLabel strFunction, vector<shared_ptr<CInstruction>>& arrInput, vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		shared_ptr<CCInstruction> pPrev;

		for (int i=0; i<(int)arrInput.size(); i++)
		{
			shared_ptr<CInstruction> pInInstruction = arrInput[i];
			shared_ptr<CInstruction> pCondition;
			
			if (dynamic_pointer_cast<CIConditionalJump>(pInInstruction))
			{
				pCondition = TracebackCondition(dynamic_pointer_cast<CIConditionalJump>(pInInstruction)->m_eType, arrInput, i-1);
			}
			if (dynamic_pointer_cast<CILoop>(pInInstruction) && dynamic_pointer_cast<CILoop>(pInInstruction)->m_eType == CILoop::WhileEqual)
			{
				pCondition = TracebackCondition(CIConditionalJump::jz, arrInput, i-1);
			}
			if (dynamic_pointer_cast<CILoop>(pInInstruction) && dynamic_pointer_cast<CILoop>(pInInstruction)->m_eType == CILoop::WhileNotEqual)
			{
				pCondition = TracebackCondition(CIConditionalJump::jnz, arrInput, i-1);
			}

			shared_ptr<CCInstruction> pOutInstruction = Convert(strFunction, pInInstruction, pCondition);

			if (!pOutInstruction)
				continue;

			if (pOutInstruction->TryJoin(pPrev))
				arrOutput.pop_back();

			//printf("%s\n", pOutInstruction->ToString().c_str());
			pPrev = pOutInstruction;
			arrOutput.push_back(pOutInstruction);
		}

		if ( !arrOutput.empty() && arrOutput.back()->ToString() == "return;" )
			arrOutput.pop_back();
	}

	void OptimizeLoops(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		int nLastLabel = -1;
		shared_ptr<CCLabel> pLastLabel;

		bool bShouldRun = true;
		while (bShouldRun)
		{
			bShouldRun = false;

			// inner loop remover, should run multiple times
			for (int i=0; i<(int)arrOutput.size(); i++)
			{
				shared_ptr<CCLabel> pLabel = dynamic_pointer_cast<CCLabel>(arrOutput[i]);
				if (pLabel)
				{
					pLastLabel = pLabel;
					nLastLabel = i;
				}

				if ( !pLastLabel )
					continue;

				shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i]);
				if (pJump)
				{
					if (pJump->GetLabelReturn())
						continue;

					if ( pJump->GetLabelBreak() || pJump->GetLabelContinue() || pJump->GetLabelReturn() )
						continue;

					if ( pJump->GetLabel() == pLastLabel->GetLabel() )
					{
						if (CountRefs(arrOutput, pLastLabel->GetLabel()) == 1)
						{
							// only one loop uses this label
							arrOutput[nLastLabel] = make_shared<CCLoop>(pLastLabel);
							arrOutput[i] = make_shared<CCLoop>(pJump);
							bShouldRun = true;
						}
					} else
					{
						// different label in inner loop
						pLastLabel = nullptr;
					}
				}
			}
		}
	}

	void OptimizeConditions(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		// inner loop remover, should run multiple times
		for (int i=0; i<(int)arrOutput.size(); i++)
		{
			shared_ptr<CCConditionalJump>& pCondition = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i]);
		
			if ( pCondition && pCondition->GetLabelLabel() )
			{
				for (int j=i+1; j<(int)arrOutput.size()-1; j++)
				{
					shared_ptr<CCInstruction> pCurrent = arrOutput[j];
					shared_ptr<CCInstruction> pNext = arrOutput[j+1];

					// nesmie byt instrukcia obmedzujuca flow, okrem. GOTO + LABEL
					shared_ptr<CCConditionalJump> pTryJump = dynamic_pointer_cast<CCConditionalJump>(pCurrent);
					shared_ptr<CCLabel> pTryNextLabel = dynamic_pointer_cast<CCLabel>(pNext);

					if ( pTryJump && pTryNextLabel )
					{
						if ( pTryNextLabel->GetLabel() == pCondition->GetLabel() )
						{
							// we have found else point
							for (int k=j+2; k<(int)arrOutput.size(); k++)
							{
								if ( dynamic_pointer_cast<CCConditionalJump>(arrOutput[k]) )
								{
									// unwanted jump inside
									break;
								}

								shared_ptr<CCLabel> pFinishLabel = dynamic_pointer_cast<CCLabel>(arrOutput[k]);
								if ( pFinishLabel && pFinishLabel->GetLabel() == pTryJump->GetLabel() )
								{
									// pCondition -> negate condition
									// pTryJump + pTryNextLabel -> join as else
									// pFinishLabel -> final, scope end

									arrOutput[i] = make_shared<CCIfThenElse>(pCondition); // pCondition - negate condition "if"
									arrOutput[j] = make_shared<CCIfThenElse>(CCIfThenElse::Else); // pTryJump "} else"
									arrOutput[j+1] = make_shared<CCIfThenElse>(CCIfThenElse::Skip); // pTryNextLabel "{"
									arrOutput[k] = make_shared<CCIfThenElse>(CCIfThenElse::Final); // pFinishLabel "}"
									i = k+1;
									break;
								}

								if ( pFinishLabel )
								{
									// unwanted label inside
									break;
								}
							}
						}

					}

					if ( pTryNextLabel && pTryNextLabel->GetLabel() == pCondition->GetLabel())
					{
						if ( GetReferencesToLabel(arrOutput, pCondition->GetLabel()) == 1 )
						{
							arrOutput[i] = make_shared<CCIfThenElse>(pCondition);
							arrOutput[j+1] = make_shared<CCIfThenElse>(CCIfThenElse::Final);
						}
						i = j+1;
						break;
					}

					if ( dynamic_pointer_cast<CCConditionalJump>(pCurrent) ||
						 dynamic_pointer_cast<CCLabel>(pCurrent) )
					{
						if ( dynamic_pointer_cast<CCConditionalJump>(pCurrent) && (
							 dynamic_pointer_cast<CCConditionalJump>(pCurrent)->GetLabelReturn() ||
							 dynamic_pointer_cast<CCConditionalJump>(pCurrent)->GetLabelContinue() ||
							 dynamic_pointer_cast<CCConditionalJump>(pCurrent)->GetLabelBreak() ) )
						{
							 continue;
						}
						// flow control inside
						break;
					}
				}
			}
		}
	}

	void OptimizeExits(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		// inner loop remover, should run multiple times
		for (int i=0; i<(int)arrOutput.size(); i++)
		{
			shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i]);
			if (pJump)
			{
				int nTarget = GetLabelRow(arrOutput, pJump->GetLabel());
				// if return
				// TODO: mali by sme zrusit vyhadzovanie returnu na konci funkcie
				if ( nTarget+1 == arrOutput.size() )
				{
					// there will be no reference to label
					if ( GetReferencesToLabel(arrOutput, pJump->GetLabel()) == 1 )
					{
						pJump->SetLabelReturn();
						arrOutput.erase(arrOutput.begin() + nTarget);
					}
				}
			}
		}
	}

	int GetReferencesToLabel(vector<shared_ptr<CCInstruction>>& arrOutput, CLabel label)
	{
		int nCount = 0;

		for (int i=0; i<(int)arrOutput.size(); i++)
		{
			shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i]);
			if (pJump && pJump->GetLabelLabel() && pJump->GetLabel() == label)
			{
				nCount++;
			}
		}
		return nCount;
	}

	int GetLabelRow(vector<shared_ptr<CCInstruction>>& arrOutput, CLabel label)
	{
		// inner loop remover, should run multiple times
		for (int i=0; i<(int)arrOutput.size(); i++)
		{
			shared_ptr<CCLabel> pLabel = dynamic_pointer_cast<CCLabel>(arrOutput[i]);
			if (pLabel && pLabel->GetLabel() == label)
			{
				return i;
			}
		}
		// TODO asi skok na start
		return 0;
		_ASSERT(0);
		return -1;
	}

	void OptimizeRedirects(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		for (int i=0; i<(int)arrOutput.size()-1; i++)
		{
			shared_ptr<CCLabel> pLabel = dynamic_pointer_cast<CCLabel>(arrOutput[i]);
			shared_ptr<CCConditionalJump> pNextJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[i+1]);
			if ( pLabel && pNextJump && pNextJump->Unconditional() )
			{
				// rename all jumps to pLabel to pNextJump->Target
				// delete label pLabel,
				for (int j=0; j<(int)arrOutput.size(); j++)
				{
					shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[j]);
					if ( pJump && pJump->GetLabel() == pLabel->GetLabel() )
						pJump->SetLabel(pNextJump->GetLabel());
				}
				arrOutput.erase(arrOutput.begin()+i);
			}
		}
	}

	shared_ptr<CCInstruction> CopyInstruction(shared_ptr<CCInstruction> instruction)
	{
		if (dynamic_pointer_cast<CCAssignment>(instruction))
			return make_shared<CCAssignment>(*dynamic_pointer_cast<CCAssignment>(instruction));
		if (dynamic_pointer_cast<CCSingleArgOp>(instruction))
			return make_shared<CCSingleArgOp>(*dynamic_pointer_cast<CCSingleArgOp>(instruction));
		if (dynamic_pointer_cast<CCConditionalJump>(instruction))
			return make_shared<CCConditionalJump>(*dynamic_pointer_cast<CCConditionalJump>(instruction));
		if (dynamic_pointer_cast<CCLabel>(instruction))
			return make_shared<CCLabel>(*dynamic_pointer_cast<CCLabel>(instruction));
		if (dynamic_pointer_cast<CCCall>(instruction))
			return make_shared<CCCall>(*dynamic_pointer_cast<CCCall>(instruction));
		if (dynamic_pointer_cast<CCIfThenElse>(instruction))
			return make_shared<CCIfThenElse>(*dynamic_pointer_cast<CCIfThenElse>(instruction));
		if (dynamic_pointer_cast<CCWhileContinueBreak>(instruction))
			return make_shared<CCWhileContinueBreak>(*dynamic_pointer_cast<CCWhileContinueBreak>(instruction));
			
		_ASSERT(0);

		return nullptr;
	}

	vector<shared_ptr<CCInstruction>> CopyProgram(vector<shared_ptr<CCInstruction>>::iterator begin, vector<shared_ptr<CCInstruction>>::iterator end)
	{
		vector<shared_ptr<CCInstruction>> aux;
		for (vector<shared_ptr<CCInstruction>>::iterator it = begin; it != end; it++)
			aux.push_back(CopyInstruction(*it));
		return move(aux);
	}

	void OptimizeLoops2(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		for (int i=0; i<(int)arrOutput.size()-1; i++)
		{
			shared_ptr<CCLabel> pStartLabel = dynamic_pointer_cast<CCLabel>(arrOutput[i]);
			if ( pStartLabel )
			{
				for (int j=arrOutput.size()-2; j>i; j--)
				{
					shared_ptr<CCConditionalJump> pTryJump = dynamic_pointer_cast<CCConditionalJump>(arrOutput[j]);
					shared_ptr<CCLabel> pExitLabel = dynamic_pointer_cast<CCLabel>(arrOutput[j+1]);
					if ( pTryJump && pExitLabel && pTryJump->Unconditional() && pTryJump->GetLabel() == pStartLabel->GetLabel())
					{
						// mozno komplexny while medzi pLabel a pTryJump
						vector<shared_ptr<CCInstruction>> arrCopy = CopyProgram(arrOutput.begin() + i, arrOutput.begin()+j+1);

						arrCopy.front() = make_shared<CCWhileContinueBreak>(CCWhileContinueBreak::While);
						arrCopy.back() = make_shared<CCWhileContinueBreak>(CCWhileContinueBreak::Final);

						for (int k=0; k<(int)arrCopy.size(); k++)
						{
							shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrCopy[k]);
							if (pJump && pJump->GetLabel() == pStartLabel->GetLabel())
								pJump->SetLabelContinue();
							else if (pJump && pJump->GetLabel() == pExitLabel->GetLabel())
								pJump->SetLabelBreak();
						}
						OptimizeConditions(arrCopy);
						OptimizeLoops(arrCopy);

						// Verify program
						bool bNoLabel = true;
						for (int k=0; k<(int)arrCopy.size(); k++)
						{
							shared_ptr<CCConditionalJump> pJump = dynamic_pointer_cast<CCConditionalJump>(arrCopy[k]);
							if (pJump && pJump->GetLabelLabel() )
								bNoLabel = false;

							shared_ptr<CCLabel> pLabel = dynamic_pointer_cast<CCLabel>(arrCopy[k]);
							if (pLabel)
								bNoLabel = false;
						}

						if (bNoLabel)
						{
							arrOutput.erase(arrOutput.begin() + i, arrOutput.begin()+j + 2);
							arrOutput.insert(arrOutput.begin() + i, arrCopy.begin(), arrCopy.end());
							i = 0;
							break;
						}
					}
						 
				}
			}
		}
	}

	void DumpProgram(vector<shared_ptr<CCInstruction>>& arrOutput, int nBaseIndent = 0)
	{
		int nIndent = 0;
		for (int i=0; i<(int)arrOutput.size(); i++)
		{	
			if ( !dynamic_pointer_cast<CCSwitch>(arrOutput[i]) )
			{
				if ( arrOutput[i]->ToString().find("}") != string::npos )
					nIndent--;
			}

			string strPad;
			if ( !dynamic_pointer_cast<CCLabel>(arrOutput[i]) )
				for (int j=0; j<nBaseIndent + nIndent; j++)
					strPad += "  ";

			string all(arrOutput[i]->ToString());
			CUtils::replace(all, "\r", "\n"); 
			istringstream is(all);
			string line;
			while (getline(is, line, '\n'))
				printf("%s%s\n", strPad.c_str(), line.c_str());

			if ( arrOutput[i]->ToString().find("{") != string::npos )
				nIndent++;
		}
	}

	void Optimize(CLabel name, vector<shared_ptr<CInstruction>>& arrInput)
	{
		vector<shared_ptr<CCInstruction>> arrOutput;
		Convert(name, arrInput, arrOutput);
		/*
		//arrOutput.insert(arrOutput.begin(), make_shared<CCLabel>(CLabel("sub_CF")));
		OptimizeRedirects(arrOutput);		
		OptimizeLoops(arrOutput);
		OptimizeConditions(arrOutput);
		//OptimizeLoops(arrOutput);
		OptimizeExits(arrOutput);
		OptimizeLoops2(arrOutput);
		OptimizeLoops(arrOutput);
		OptimizeConditions(arrOutput);
		OptimizeLoops(arrOutput);
		OptimizeConditions(arrOutput);
		OptimizeLoops(arrOutput);
		OptimizeConditions(arrOutput);
		*/
		DumpProgram(arrOutput);	
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

		int nBegin = FindLabel(arrCode, label);
		_ASSERT(nBegin >= 0);
		for (int i=nBegin+1; i<(int)arrCode.size() && !dynamic_pointer_cast<CIFunction>(arrCode[i]); i++)
			aux.push_back(arrCode[i]);

		return move(aux);
	}

	void Process(const vector<shared_ptr<CInstruction>>& arrSource)
	{
		m_arrSource = arrSource;

		bool bInFunc = false;
		for (int i=0; i<(int)arrSource.size(); i++)
		{
			shared_ptr<CInstruction> pInstruction = arrSource[i];
			shared_ptr<CINop> pNop = dynamic_pointer_cast<CINop>(pInstruction);

			if ( pNop )
				continue;

			shared_ptr<CIFunction> pFunction = dynamic_pointer_cast<CIFunction>(pInstruction);
			if (bInFunc)
			{
				shared_ptr<CIReturn> pReturn = dynamic_pointer_cast<CIReturn>(pInstruction);
				if ( pReturn )
				{
					_ASSERT(pReturn->m_nReduceStack == 0);
					bInFunc = false;
					continue;
				}

				_ASSERT(pFunction && pFunction->m_eBoundary == CIFunction::End);
				bInFunc = false;
				continue;
			}

			if (!pFunction || pFunction->m_eBoundary != CIFunction::Begin)
			{
				// lost code!
				printf("// %s\n", typeid(*pInstruction).name()); //Convert("", pInstruction, nullptr)->ToString().c_str());
				continue;
			}

			_ASSERT(pFunction && pFunction->m_eBoundary == CIFunction::Begin);
			bInFunc = true;

			vector<shared_ptr<CInstruction>> arrFunction = GetSubCode(arrSource, pFunction->m_strName);

			vector<shared_ptr<CCInstruction>> arrCFunction;
			Convert(pFunction->m_strName, arrFunction, arrCFunction);

			printf("void %s()\n{\n", pFunction->m_strName.c_str());
			DumpProgram(arrCFunction, 1);	
			printf("}\n\n");

			i += arrFunction.size();
		}
	}
};
