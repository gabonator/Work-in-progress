class CCExport
{
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

	void Convert(vector<shared_ptr<CInstruction>>& arrInput, vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		shared_ptr<CCInstruction> pPrev;

		for (int i=0; i<(int)arrInput.size(); i++)
		{
			shared_ptr<CInstruction> pInInstruction = arrInput[i];
			shared_ptr<CCInstruction> pOutInstruction;

			if ( dynamic_pointer_cast<CINop>(pInInstruction) )
				continue;

			if ( dynamic_pointer_cast<CICompare>(pInInstruction) ||
			     dynamic_pointer_cast<CITest>(pInInstruction) )
				continue;

			if ( dynamic_pointer_cast<CIData>(pInInstruction) && dynamic_pointer_cast<CIData>(pInInstruction)->m_eType == CIData::Function )
			{
				// TODO: probably switch, check previous instruction
				continue;
			}

			shared_ptr<CIReturn> pReturn = dynamic_pointer_cast<CIReturn>(pInInstruction);
			if (pReturn && i == arrInput.size()-1 && pReturn->m_nReduceStack == 0)
				continue;

			if (pReturn)
				pOutInstruction = make_shared<CCReturn>( pReturn );

			shared_ptr<CIAssignment> pAssignment = dynamic_pointer_cast<CIAssignment>(pInInstruction);
			if (pAssignment)
				pOutInstruction = make_shared<CCAssignment>( pAssignment->m_valueTo, pAssignment->m_valueFrom);

			shared_ptr<CIAlu> pAlu = dynamic_pointer_cast<CIAlu>(pInInstruction);
			if (pAlu)
				pOutInstruction = make_shared<CCAssignment>( pAlu );

			shared_ptr<CISingleArgOp> pSingleArgOp = dynamic_pointer_cast<CISingleArgOp>(pInInstruction);
			if (pSingleArgOp)
				pOutInstruction = make_shared<CCSingleArgOp>( pSingleArgOp );

			shared_ptr<CITwoArgOp> pTwoArgOp = dynamic_pointer_cast<CITwoArgOp>(pInInstruction);
			if (pTwoArgOp)
				pOutInstruction = make_shared<CCTwoArgOp>( pTwoArgOp );

			shared_ptr<CIConditionalJump> pConditionalJump = dynamic_pointer_cast<CIConditionalJump>(pInInstruction);
			if (pConditionalJump)
			{
				shared_ptr<CInstruction> pInstruction = arrInput[i-1];
				if ( dynamic_pointer_cast<CICompare>(pInstruction) )
					pOutInstruction = make_shared<CCConditionalJump>( pConditionalJump, dynamic_pointer_cast<CICompare>(pInstruction) );
				else if ( dynamic_pointer_cast<CITest>(pInstruction) )
					pOutInstruction = make_shared<CCConditionalJump>( pConditionalJump, dynamic_pointer_cast<CITest>(pInstruction) );
				else if ( dynamic_pointer_cast<CIAlu>(pInstruction) )
					pOutInstruction = make_shared<CCConditionalJump>( pConditionalJump, dynamic_pointer_cast<CIAlu>(pInstruction) );
				else
					_ASSERT(0);
			}

			shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(pInInstruction);
			if (pJump)
				pOutInstruction = make_shared<CCConditionalJump>( pJump );

			shared_ptr<CILabel> pLabel = dynamic_pointer_cast<CILabel>(pInInstruction);
			if (pLabel)
				pOutInstruction = make_shared<CCLabel>( pLabel );

			shared_ptr<CICall> pCall = dynamic_pointer_cast<CICall>(pInInstruction);
			if (pCall)
				pOutInstruction = make_shared<CCCall>( pCall );

			shared_ptr<CILoop> pLoop = dynamic_pointer_cast<CILoop>(pInInstruction);
			if (pLoop)
				pOutInstruction = make_shared<CCConditionalJump>( pLoop );

			if (!pOutInstruction)
				_ASSERT(0);

			if (pOutInstruction->TryJoin(pPrev))
				arrOutput.pop_back();

			//printf("%s\n", pOutInstruction->ToString().c_str());
			pPrev = pOutInstruction;
			arrOutput.push_back( pOutInstruction);
		}
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

	void DumpProgram(vector<shared_ptr<CCInstruction>>& arrOutput)
	{
		int nIndent = 0;
		for (int i=0; i<(int)arrOutput.size(); i++)
		{	
			if ( arrOutput[i]->ToString().find("}") != string::npos )
				nIndent--;

			for (int j=0; j<nIndent; j++)
				printf("  ");

			printf("%s\n", arrOutput[i]->ToString().c_str());

			if ( arrOutput[i]->ToString().find("{") != string::npos )
				nIndent++;
		}
	}

	void Optimize(vector<shared_ptr<CInstruction>>& arrInput)
	{
		vector<shared_ptr<CCInstruction>> arrOutput;
		Convert(arrInput, arrOutput);
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
};
