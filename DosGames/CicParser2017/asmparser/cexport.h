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

			if ( dynamic_pointer_cast<CICompare>(pInInstruction) )
				continue;

			shared_ptr<CIReturn> pReturn = dynamic_pointer_cast<CIReturn>(pInInstruction);
			if (pReturn && i == arrInput.size()-1 && pReturn->m_nReduceStack == 0)
				continue;

			shared_ptr<CIAssignment> pAssignment = dynamic_pointer_cast<CIAssignment>(pInInstruction);
			if (pAssignment)
				pOutInstruction = make_shared<CCAssignment>( pAssignment->m_valueTo, pAssignment->m_valueFrom);

			shared_ptr<CIAlu> pAlu = dynamic_pointer_cast<CIAlu>(pInInstruction);
			if (pAlu)
				pOutInstruction = make_shared<CCAssignment>( pAlu );

			shared_ptr<CISingleArgOp> pSingleArgOp = dynamic_pointer_cast<CISingleArgOp>(pInInstruction);
			if (pSingleArgOp)
				pOutInstruction = make_shared<CCSingleArgOp>( pSingleArgOp );

			shared_ptr<CIConditionalJump> pConditionalJump = dynamic_pointer_cast<CIConditionalJump>(pInInstruction);
			if (pConditionalJump)
				pOutInstruction = make_shared<CCConditionalJump>( pConditionalJump, dynamic_pointer_cast<CICompare>(arrInput[i-1]) );

			shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(pInInstruction);
			if (pJump)
				pOutInstruction = make_shared<CCConditionalJump>( pJump );

			shared_ptr<CILabel> pLabel = dynamic_pointer_cast<CILabel>(pInInstruction);
			if (pLabel)
				pOutInstruction = make_shared<CCLabel>( pLabel );

			shared_ptr<CICall> pCall = dynamic_pointer_cast<CICall>(pInInstruction);
			if (pCall)
				pOutInstruction = make_shared<CCCall>( pCall );

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
		
			if ( pCondition )
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

					if ( dynamic_pointer_cast<CCConditionalJump>(pCurrent) ||
						 dynamic_pointer_cast<CCLabel>(pCurrent) )
					{
						// flow control inside
						break;
					}
				}
			}
		}
	}

	void Optimize(vector<shared_ptr<CInstruction>>& arrInput)
	{
		vector<shared_ptr<CCInstruction>> arrOutput;
		Convert(arrInput, arrOutput);
		OptimizeLoops(arrOutput);
		OptimizeConditions(arrOutput);
	
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
};
