void VideoUpdate();

class CTimer8254
{
	int nReset0;
	int nReset1;
	int nReset2;
	int nSpkrFrequency;

	WORD wLatch0;

public:
	CTimer8254()
	{
		nReset0 = 0;
		nReset1 = 0;
		nReset2 = 0;
		nSpkrFrequency = 0;
	}

	WORD Read18Hz()
	{
		return (WORD)((FLOAT)GetTickCount()*65543.0f/(1000.0f*60.0f*60.0f));
	}

	void WriteCtl(BYTE arg) // 43h
	{
		int nChannel = arg >> 6;
		int nAccess = (arg >> 4) & 3; // 0 = citame, 2 = ideme zapisovat
		int nMode = (arg >> 1) & 7; // 0 = irq on count, 3 = sq wave
		int nFormat = arg & 1; // 0 = 16 bit, 1 = bcd 4 digit

		switch ( nChannel )
		{
			case 0: 

				_ASSERT(arg==0);  // nAccess = 0 -> Latch for reading
				wLatch0 = -Read18Hz(); 
				wLatch0 = -(WORD)(GetTickCount()/5);
				//wLatch0 = 0;
				//nReset0 = 1; 
				break;
			case 1: nReset1 = 1; break;
			case 2: 
				nReset2 = 1; 
				break;
			default:
				_ASSERT(0);
		}
	}
	BYTE ReadCounter0() // 40h
	{
		BYTE b = wLatch0 >> 8;
		wLatch0 <<= 8;
		return b;
	}
	BYTE ReadCounter1() // 41h
	{
		_ASSERT(0);
		return 0;
	}
	BYTE ReadCounter2() // 42h
	{
		_ASSERT(0);
		return 0;
	}

	void WriteCounter0(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter1(BYTE arg)
	{
		_ASSERT(0);
	}
	void WriteCounter2(BYTE arg)
	{
		static int nFreqLow;
		static int nFreqHigh;

		switch ( nReset2++ )
		{
		case 1: nFreqLow = arg; break;
		case 2: nFreqHigh = arg; 
			{
				int nFreqDiv = nFreqHigh*256 + nFreqLow;
				INT nSpkrFrequency = 1193180/nFreqDiv;
				///printf("Tone %d Hz\n", nSpkrFrequency);
				//Beep(nSpkrFrequency*2, 100);
			}
			break;
		default:
			_ASSERT(0);
		}
	}

	int GetFrequency()
	{
		return nSpkrFrequency;
	}
	BOOL Out(WORD port, BYTE val)
	{
		switch ( port )
		{
			case 0x43: WriteCtl(val); return TRUE;
			case 0x40: WriteCounter0(val); return TRUE;
			case 0x41: WriteCounter1(val); return TRUE;
			case 0x42: WriteCounter2(val); return TRUE;
		}
		return FALSE;
	}

	BYTE In(WORD port)
	{
		switch ( port )
		{
			case 0x40: return ReadCounter0();
			case 0x41: return ReadCounter1();
			case 0x42: return ReadCounter2();
		}
		_ASSERT(0);
		return 0;
	}
};

// i8254
class CTimer
{
	int _p42;
	int _buffer42;
	int _buffer;
	int _t0;

public:
	CTimer()
	{
		_p42 = 0;
		_buffer42 = 0;
		_buffer = 0;
		_t0 = 0;
	}

	void Out(int nPort, int nValue)
	{
		_ASSERT(nPort >= 0x40 && nPort <= 0x43);

		if ( nPort == 0x43 )
		{
			if ( nValue == 0xB6 ) // play tone
			{
				_p42 = 0;
				_buffer42 = 0;
				return;
			} 
			if (nValue == 0x00)
			{
				_buffer = (-tick()*6) &0xffff; //(-this.tick()*1000) & 0xffff;
				return;
			}
		}

		if ( nPort == 0x42 )
		{
			if ( _p42 == 0 )
			{
				_buffer42 = nValue;
				_p42++;
			} else if ( _p42 == 1 )
			{
				_buffer42 = (nValue<<8) | _buffer42;
				//_tone(_buffer42, 1000);
			}    
		}

	}

	int In(int nPort)
	{
		_ASSERT(nPort >= 0x40 && nPort <= 0x43);

		int b = _buffer >> 8;
		_buffer <<= 8;
		return b & 0xff;
	}

	int tick()
	{
		int t = GetTickCount();
		if ( _t0 == 0 )
			_t0 = t;
		t -= _t0;
		t = (int)(t*18.2f/1000.0f);
		return t;
	}

};

class CMachine
{
public:
	class CRegisters {
	public:
		union {
			struct {
				unsigned char al;
				unsigned char ah;
			} r8;
			struct {
				unsigned short ax;
			} r16;
		} a;
		union {
			struct {
				unsigned char bl;
				unsigned char bh;
			} r8;
			struct {
				unsigned short bx;
			} r16;
		} b;
		union {
			struct {
				unsigned char cl;
				unsigned char ch;
			} r8;
			struct {
				unsigned short cx;
			} r16;
		} c;
		union {
			struct {
				unsigned char dl;
				unsigned char dh;
			} r8;
			struct {
				unsigned short dx;
			} r16;
		} d;
		unsigned short cs;
		unsigned short ds;
		unsigned short es;

		unsigned short si;
		unsigned short di;

		unsigned short bp;
		unsigned short sp;
	};

	class CFlags
	{
	public:
		bool cf; // carry
		bool zf; // zero
		bool df; // dir
		bool signum;
		bool interrupt;

		BYTE ToByte()
		{
			return cf + 2*zf;
		}

		void FromByte(BYTE b)
		{
			cf = b & 1;
			zf = !!(b & 2);
		}
	};

	typedef shared_ptr<CInstruction> SInstruction;
	vector<SInstruction> m_arrCode;
	vector<string> m_arrSource;

	int m_pc;
	CRegisters m_reg;
	CFlags m_flag;
	CTimer8254 m_Timer;

	// Temp helpers;
	CValue::ERegLength m_eCmpLen;
	int m_nCmpOp1;
	int m_nCmpOp2;

	vector<string> m_arrCallStackNames;
	vector<int> m_arrCallStack;
	vector<int> m_arrStack;
	map<string, int> m_mapLabels;

	CDos m_dos;
	shared_ptr<CVideoAdapter> m_pVideo;

public:
	CMachine()
	{
		memset(&m_reg, 0, sizeof(m_reg));
		memset(data, 0xff, sizeof(data));
		m_arrStack.resize(32*2, 0);

		m_reg.sp = 16*2*2;
		m_reg.bp = 0;
	}

	void Eval(vector<shared_ptr<CInstruction>>& arrCode, vector<string>& arrSource)
	{
		m_arrCode = arrCode;
		m_arrSource = arrSource;
		
		m_pc = -1;

		Call("start");
		for ( int i=0; i<53251000; i++)
		{
			if (i % 50 == 0)
			{
				//data[0x693]++;
				//data[0x6BC+5] = 1;
				//data[0x6BC+7] = 1;

				VideoUpdate();
			}

			Eval();

		}
	}

	void Call(string label)
	{
		//if ( label == "sub_69A" )
		//{
		//	/*
		//	loc_code_708:				; CODE XREF: sub_code_69A+95j
		//dec	bl
		//jns	short loc_code_72C
		//lodsb

		//	*/
		//	int f = 9;
		//}
		//if ( label == "sub_7AF" )
		//{
		//	// toto nam nastavuje vysku na 1px
		//	// mov	byte_data_27E, al
		//	int f = 9;
		//	// r8[al] = _data[r16[bx]]; mem at 34469 ma byt 1

		//}
		//if ( label == "sub_BDC" )
		//{
		//	// kresli sprite cez map c24, chceme vediet preco je vyska q=1 px
		//	
		//	int w = data[m_reg.ds * 16 + m_reg.si +	9];
		//	int h = data[m_reg.ds * 16 + m_reg.si +	10];
		//	int f = 9;
		//}
		//if ( label == "sub_C24" )
		//{
		//	int q = StackRead(m_reg.sp+2);
		//	int x = StackRead(m_reg.sp+4);
		//	int y = StackRead(m_reg.sp+6);
		//	int z = StackRead(m_reg.sp+8);
		//	printf("sprite %d x %x\n", x, q);
		//	//if ( q > 10)
		//	if ( q == 1)
		//		StackWrite(m_reg.sp+2, 5);
		//}
		if ( label == "sub_103" )
			return;
		////if ( label == "sub_2D35" )
		////{
		////	int f = 9;
		//////	return;
		////}

		////if ( label == "sub_2D9D" )
		////{
		////	/*
		////	int xx0 = data[m_reg.ds*16+0x2ae0];
		////	int xx1 = data[m_reg.ds*16+0x2ae1];
		////	int xx2 = data[m_reg.ds*16+0x2ae2];

		////	int _cl = m_reg.c.r8.cl;
		////	int _ch = m_reg.c.r8.ch;

		////	m_reg.c.r8.cl = rand();*/
		////	if ( m_reg.c.r16.cx == 0x0b03 || m_reg.c.r16.cx == 0x0c0a )
		////	{
		////printf("STACK: ");
		////for (int i=0; i<(int)m_arrCallStackNames.size(); i++)
		////	printf("%s ", m_arrCallStackNames[i].c_str());
		////printf(": ");

		////		printf("%dx%d\t", m_reg.c.r8.ch, m_reg.c.r8.cl);
		////		printf("%04x:%04x <- %04x:%04x\n", 
		////			m_reg.es, m_reg.di, m_reg.ds, m_reg.si);
		////		//return;
		////	}
		////	//int f = 9;
		////}

		//	return;
		// return to next instruction
		m_arrCallStackNames.push_back(label);
		m_arrCallStack.push_back(m_pc); // == -1 ? -1 : m_pc+1);
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);
		
		// skip function label
		m_pc++;
		/*
		printf("STACK: ");
		for (int i=0; i<(int)m_arrCallStackNames.size(); i++)
			printf("%s ", m_arrCallStackNames[i].c_str());
		printf("\n");
		*/
	}

	void Goto(string label)
	{
		//if ( m_arrCallStackNames.back() != "sub_33E5")
//			printf("GOTO: %s\n", label.c_str());
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);

		// skip goto label
		m_pc++;
	}

	void Return()
	{
		m_pc = m_arrCallStack.back();
		m_arrCallStack.pop_back();
		m_arrCallStackNames.pop_back();
	}
	
	void Eval()
	{
		const string& strDebug0 = m_arrSource[m_pc > 0 ? m_pc-1 : 0];
		const string& strDebug1 = m_arrSource[m_pc];

		SInstruction sInstruction = m_arrCode[m_pc];

		m_pc++;
		/*
		if ( m_arrCallStackNames.back() == "sub_DA7" )
		{
		printf("ax:%04x bx:%04x cx:%04x dx:%04x si:%04x di:%04x\t",
			m_reg.a.r16.ax, m_reg.b.r16.bx, m_reg.c.r16.cx, m_reg.d.r16.dx, m_reg.si, m_reg.di);
		printf("%s\n", m_arrSource[m_pc].c_str());
		}*/

		sInstruction->Eval(*this);
	}

	vector<int> FindReferences(CLabel label)
	{
		vector<int> aux;

		for (int i=0; (size_t)i<m_arrCode.size(); i++)
		{
			shared_ptr<CIJump> pJump = dynamic_pointer_cast<CIJump>(m_arrCode[i]);
			if (pJump && pJump->m_label == label)
				aux.push_back(i);

			shared_ptr<CIConditionalJump> pConditional = dynamic_pointer_cast<CIConditionalJump>(m_arrCode[i]);
			if (pConditional && pConditional->m_label == label)
				aux.push_back(i);
		}

		return move(aux);
	}

	int FindLabel(string label)
	{
		auto i = m_mapLabels.find(label);
		if (i != m_mapLabels.end())
		{
			return i->second;
		}

		for (int i=0; (size_t)i<m_arrCode.size(); i++)
		{
			CILabel* pLabel = dynamic_cast<CILabel*>(m_arrCode[i].get());		
			if (pLabel && pLabel->m_label == label)
			{
				m_mapLabels.insert(make_pair<string, int>(label, i));
				return i;
			}

			CIFunction* pFunction = dynamic_cast<CIFunction*>(m_arrCode[i].get());
			if (pFunction && pFunction->m_eBoundary == CIFunction::Begin && pFunction->m_strName == label)
			{
				m_mapLabels.insert(make_pair<string, int>(label, i));
				return i;
			}

			CIData* pData = dynamic_cast<CIData*>(m_arrCode[i].get());		
			if ( pData)
			{
				int f = 9;
			}
			if (pData && pData->m_strVariableName == label)
			{
				m_mapLabels.insert(make_pair<string, int>(label, i));
				return i;
			}

		}
		_ASSERT(0);
		return -1;
	}

	int GetValue(CValue& v)
	{
		switch (v.m_eType)
		{
			case CValue::constant: return v.m_nValue;
			case CValue::ax: return m_reg.a.r16.ax;
			case CValue::ah: return m_reg.a.r8.ah;
			case CValue::al: return m_reg.a.r8.al;
			case CValue::bx: return m_reg.b.r16.bx;
			case CValue::bh: return m_reg.b.r8.bh;
			case CValue::bl: return m_reg.b.r8.bl;
			case CValue::cx: return m_reg.c.r16.cx;
			case CValue::ch: return m_reg.c.r8.ch;
			case CValue::cl: return m_reg.c.r8.cl;
			case CValue::dx: return m_reg.d.r16.dx;
			case CValue::dh: return m_reg.d.r8.dh;
			case CValue::dl: return m_reg.d.r8.dl;
			case CValue::cs: return m_reg.cs;
			case CValue::ds: return m_reg.ds;
			case CValue::es: return m_reg.es;

			case CValue::si: return m_reg.si;
			case CValue::di: return m_reg.di;

			case CValue::bp: return m_reg.bp;
			case CValue::sp: return m_reg.sp;

			case CValue::byteptrasword: 
			case CValue::wordptr: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				return MappedRead(v.m_nValue) | (MappedRead(v.m_nValue+1) << 8);

			case CValue::byteptr: 
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				return MappedRead(v.m_nValue);

			case CValue::byteptrval: 
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return MappedRead(m_reg.ds, GetValue(*v.m_value) & 0xffff);

			case CValue::wordptrval: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return MappedRead(m_reg.ds, GetValue(*v.m_value) & 0xffff) | (MappedRead(m_reg.ds, (GetValue(*v.m_value) + 1) & 0xffff) << 8);

			case CValue::bp_plus: 
//				_ASSERT(v.GetRegisterLength() == CValue::r16);
				return m_reg.bp + v.m_nValue;

			case CValue::di_plus: 
//				_ASSERT(v.GetRegisterLength() == CValue::r16);
				return m_reg.di + v.m_nValue;

			case CValue::es_ptr_di:
				if (v.GetRegisterLength() == CValue::r8)
				{
					return MappedRead(m_reg.es, m_reg.di);
				} else
				if (v.GetRegisterLength() == CValue::r16)
				{
					return MappedRead(m_reg.es, m_reg.di) | (MappedRead(m_reg.es, m_reg.di+1) << 8);
				}
				break;

			case CValue::es_ptr:
				if (v.GetRegisterLength() == CValue::r8)
					return MappedRead(m_reg.es, v.m_nValue);
				else
				if (v.GetRegisterLength() == CValue::r16)
					return MappedRead(m_reg.es, v.m_nValue) | (MappedRead(m_reg.es, v.m_nValue+1) << 8);
				else
					_ASSERT(0);

			case CValue::bx_plus_si:
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				//_ASSERT(v.GetRegisterLength() == CValue::r8);
				return m_reg.b.r16.bx + m_reg.si;

			case CValue::bx_plus_si_plus: // PTR?
				// TODO: ptr, 16
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				return MappedRead(m_reg.b.r16.bx + m_reg.si + v.m_nValue);

			case CValue::wordptrasbyte:
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				return MappedRead(v.m_nValue);

			case CValue::bx_plus:
				//_ASSERT(v.GetRegisterLength() == CValue::r16);
				return m_reg.b.r16.bx + v.m_nValue;

			case CValue::si_plus:
				//_ASSERT(v.GetRegisterLength() == CValue::r16);
				return m_reg.si + v.m_nValue;

			case CValue::stack_bp_plus:
				if (v.GetRegisterLength() == CValue::r16)
					return StackRead(m_reg.bp + v.m_nValue);
				else
				if (v.GetRegisterLength() == CValue::r8)
					return StackRead(m_reg.bp + v.m_nValue);
				else
					_ASSERT(0);
				//_ASSERT(v.GetRegisterLength() == CValue::r16);
				//return StackRead(m_reg.bp + v.m_nValue);

			case CValue::bx_plus_di:
				//_ASSERT(v.GetRegisterLength() == CValue::r16);
				return m_reg.b.r16.bx + m_reg.di;

			case CValue::codeword:
			{
				_ASSERT(v.GetRegisterLength() == CValue::r16);

				stringstream ss;
				ss << "word_code_" << std::hex << std::uppercase << v.m_nValue; 
				CLabel label(ss.str());
				int nIndex = FindLabel(label);
				_ASSERT(nIndex >= 0);
				CIData* pData = dynamic_cast<CIData*>(m_arrCode[nIndex].get());
				_ASSERT(pData->m_strVariableName == label);
				return pData->m_nValue;
			}

			case CValue::codebyte:
			{
				_ASSERT(v.GetRegisterLength() == CValue::r8);

				stringstream ss;
				ss << "byte_code_" << std::hex << std::uppercase << v.m_nValue; 
				CLabel label(ss.str());
				int nIndex = FindLabel(label);
				_ASSERT(nIndex >= 0);
				CIData* pData = dynamic_cast<CIData*>(m_arrCode[nIndex].get());
				_ASSERT(pData->m_strVariableName == label);
				return pData->m_nValue;
			}

			case CValue::segment: 
				if ( v.m_eSegment == CValue::dseg )
					return 0;		
				break;

			case CValue::wordptr_es: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return MappedRead(m_reg.es, v.m_nValue & 0xffff) | (MappedRead(m_reg.es, (v.m_nValue + 1) & 0xffff) << 8);

			case CValue::es_ptr_di_plus:
				if (v.GetRegisterLength() == CValue::r8)
				{
					return MappedRead(m_reg.es, m_reg.di + v.m_nValue);
				}
				else
				if (v.GetRegisterLength() == CValue::r16)
				{
					return MappedRead(m_reg.es, m_reg.di + v.m_nValue) |
						(MappedRead(m_reg.es, m_reg.di + v.m_nValue + 1) << 8);
				}
				break;
		}
		_ASSERT(0);
		return 0;
	}

	void SetValue(CValue& v, int nValue)
	{
		switch (v.m_eType)
		{
			case CValue::constant: _ASSERT(0); return;
			case CValue::ax: m_reg.a.r16.ax = (unsigned short)nValue; return;
			case CValue::ah: m_reg.a.r8.ah = (unsigned char)nValue; return;
			case CValue::al: m_reg.a.r8.al = (unsigned char)nValue; return;
			case CValue::bx: m_reg.b.r16.bx = (unsigned short)nValue; return;
			case CValue::bh: m_reg.b.r8.bh = (unsigned char)nValue; return;
			case CValue::bl: m_reg.b.r8.bl = (unsigned char)nValue; return;
			case CValue::cx: m_reg.c.r16.cx = (unsigned short)nValue; return;
			case CValue::ch: m_reg.c.r8.ch = (unsigned char)nValue; return;
			case CValue::cl: m_reg.c.r8.cl = (unsigned char)nValue; return;
			case CValue::dx: m_reg.d.r16.dx = (unsigned short)nValue; return;
			case CValue::dh: m_reg.d.r8.dh = (unsigned char)nValue; return;
			case CValue::dl: m_reg.d.r8.dl = (unsigned char)nValue; return;

			case CValue::cs: m_reg.cs = (unsigned short)nValue; return;
			case CValue::ds: m_reg.ds = (unsigned short)nValue; return;
			case CValue::es: m_reg.es = (unsigned short)nValue; return;

			case CValue::si: m_reg.si = (unsigned short)nValue; return;
			case CValue::di: m_reg.di = (unsigned short)nValue; return;

			case CValue::bp: m_reg.bp = (unsigned short)nValue; return;
			case CValue::sp: m_reg.sp = (unsigned short)nValue; return;

			case CValue::byteptrasword: 
			case CValue::wordptr: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				// TODO: toto vsetko musi ist cez mapped, robi sa tam s grafikou!
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				MappedWrite(v.m_nValue, nValue & 0xff);
				MappedWrite(v.m_nValue+1, nValue >> 8);
			return;

			case CValue::byteptr: 
				_ASSERT(v.GetRegisterLength() == CValue::r8);

				_ASSERT(v.m_nValue >= 0 && v.m_nValue < sizeof(data));
				MappedWrite(v.m_nValue, nValue);
			return;

			case CValue::byteptrval: 
				_ASSERT(v.GetRegisterLength() == CValue::r8);

				_ASSERT(v.m_value);
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				MappedWrite(m_reg.ds, GetValue(*v.m_value), nValue);
			return;

			case CValue::wordptrval: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);

				_ASSERT(v.m_value);
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				MappedWrite(m_reg.ds, GetValue(*v.m_value) & 0xffff, nValue & 0xff);
				MappedWrite(m_reg.ds, (GetValue(*v.m_value)+1) & 0xffff, nValue >> 8);
			return;

			case CValue::es_ptr_di:
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				MappedWrite(m_reg.es, m_reg.di, nValue & 0xff);
			return;

			case CValue::ds_ptr_bp_plus:
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				MappedWrite(m_reg.ds, m_reg.bp + v.m_nValue, nValue & 0xff);
				MappedWrite(m_reg.ds, m_reg.bp + v.m_nValue + 1, nValue >> 8);
			return;

			case CValue::codeword:
			{
				_ASSERT(v.GetRegisterLength() == CValue::r16);

				stringstream ss;
				ss << "word_code_" << std::hex << std::uppercase << v.m_nValue; 
				CLabel label(ss.str());
				int nIndex = FindLabel(label);
				_ASSERT(nIndex >= 0);
				CIData* pData = dynamic_cast<CIData*>(m_arrCode[nIndex].get());
				_ASSERT(pData->m_strVariableName == label);
				pData->m_nValue = nValue;
			}
			return;

			case CValue::codebyte:
			{
				_ASSERT(v.GetRegisterLength() == CValue::r8);

				stringstream ss;
				ss << "byte_code_" << std::hex << std::uppercase << v.m_nValue; 
				CLabel label(ss.str());
				int nIndex = FindLabel(label);
				_ASSERT(nIndex >= 0);
				CIData* pData = dynamic_cast<CIData*>(m_arrCode[nIndex].get());
				_ASSERT(pData->m_strVariableName == label);
				pData->m_nValue = nValue;
			}
			return;

			case CValue::wordptrasbyte:
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				MappedWrite(v.m_nValue, nValue & 0xff);
			return;

			case CValue::stack_bp_plus:
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				StackWrite(m_reg.bp + v.m_nValue, nValue);
			return;

			case CValue::es_ptr:
				if (v.GetRegisterLength() == CValue::r16)
				{
					MappedWrite(m_reg.es, v.m_nValue, nValue & 0xff);
					MappedWrite(m_reg.es, v.m_nValue+1, (nValue>>8) & 0xff);
				} else
				if (v.GetRegisterLength() == CValue::r8)
				{
					MappedWrite(m_reg.es, v.m_nValue, nValue & 0xff);
				} else
					_ASSERT(0);

			return;
			
			case CValue::es_ptr_di_plus:
				if (v.GetRegisterLength() == CValue::r8)
				{
					MappedWrite(m_reg.es, m_reg.di + v.m_nValue, nValue);
				}
				else
				if (v.GetRegisterLength() == CValue::r16)
				{
					MappedWrite(m_reg.es, m_reg.di + v.m_nValue, nValue & 0xff);
					MappedWrite(m_reg.es, m_reg.di + v.m_nValue + 1, nValue >> 8);
				} else
					_ASSERT(0);
			return;

			case CValue::wordptr_es: 
				_ASSERT(v.GetRegisterLength() == CValue::r16);
				MappedWrite(m_reg.es, v.m_nValue, nValue & 0xff);
				MappedWrite(m_reg.es, v.m_nValue+1, nValue >> 8);
			return;
		}
		_ASSERT(0);
	}

	void Interrupt(int i)
	{
		switch (i)
		{
		case 0x11:
			// equipment detection
			m_reg.a.r16.ax = 0xb91e;
			return;

		case 0x12:
			// free mem -> ax
			m_reg.a.r16.ax = 0x1000;
			return;

		case 0x21:
			m_dos.Interrupt(*this);
			return;

		case 0x10:
			switch (m_reg.a.r8.ah)
			{
			case 0x00:
				printf("Setting video mode 0x%02x - ", m_reg.a.r8.al);
				switch (m_reg.a.r8.al)
				{
				case 4: 
					printf("320x200 2bpp, CGA Adapter\n");
					m_pVideo.reset(new CCga());
					return;
				case 13: 
					printf("320x200 4bpp, EGA Adapter\n");
					m_pVideo.reset(new CEga());
					return;
				}
				_ASSERT(0);
				printf("Unknown adapter\n");
				return;
			default:
				_ASSERT( m_pVideo );
				if ( m_pVideo->Interrupt(m_reg.a.r8.ah, m_reg.a.r8.al, m_reg.b.r8.bh, m_reg.b.r8.bl ) )
					return;
			}
			break;

		case 0x1a:	
			{
				static DWORD dwTimeBase = 0;
				DWORD dwTime = (WORD)(GetTickCount()*18.2f/1000.0f);

				switch (m_reg.a.r8.ah)
				{
				case 0x00:
					//http://vitaly_filatov.tripod.com/ng/asm/asm_029.1.html
					if ( dwTimeBase == 0 )
						dwTimeBase = dwTime;
					dwTime -= dwTimeBase;
					m_reg.c.r16.cx = dwTime >> 16;
					m_reg.d.r16.dx = dwTime & 0xffff;
					return;

				case 0x01:
					if (m_reg.c.r16.cx == 0 && m_reg.d.r16.dx == 0)
					{
						dwTimeBase = dwTime;
						return;
					}
					break;
				}
			break;
			}

		case 0x33:
			if ( m_reg.a.r8.ah == 0 )
    		{
				m_reg.a.r16.ax = 0xffff;
				m_reg.b.r16.bx = 0x0002;

   				//m_reg.a.r16.ax = 0x0000; // no mouse
   				return;
    		}
		}

		_ASSERT(0);
	}

	/*
	void VideoWrite16(int nSegment, int nOffset, int nValue)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		addr -= 0xa000*16;
		EGA.Write(addr, nValue & 0xff);
		EGA.Write(addr+1, nValue >> 8);
	}

	int VideoRead16(int nSegment, int nOffset, int nValue)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		addr -= 0xa000*16;
		return EGA.Read(addr) | (EGA.Read(addr+1)<<8);
	}
	*/
	int StackRead(int nOffset)
	{
		_ASSERT(nOffset/2 >= 0 && nOffset/2 < (int)m_arrStack.size());
		_ASSERT((nOffset&1) == 0);
		return m_arrStack[nOffset/2];
	}

	void StackWrite(int nOffset, int nData)
	{
		_ASSERT(nOffset/2 >= 0 && nOffset/2 < (int)m_arrStack.size());
		_ASSERT((nOffset&1) == 0);
		m_arrStack[nOffset/2] = nData;
	}

	int MappedRead(int nOffset)
	{
		_ASSERT(m_reg.ds == 0);
		return MappedRead(m_reg.ds, nOffset);
	}

	int MappedRead(int nSegment, int nOffset)
	{
		_ASSERT(nSegment != 0xcccc);
		if (nSegment == 0xf000 && nOffset == 0xfffe )
			return 0xff; // BIOS - IBM computer type code

		_ASSERT(nSegment >= 0 && nSegment < 0xf000);
		_ASSERT(nOffset >= 0 && nOffset <= 0xffff);

		if (nSegment >= 0xa000)
			return VideoRead(nSegment, nOffset);
		_ASSERT(nSegment * 16 + nOffset < sizeof(data));
		_ASSERT(*(WORD*)&data[nSegment * 16 + nOffset] != 0x6a6a);
		//_ASSERT(*(WORD*)&data[nSegment * 16 + nOffset] != 0xcccc);
		return data[nSegment * 16 + nOffset];
	}

	void MappedWrite(int nOffset, int nValue)
	{
		_ASSERT(m_reg.ds == 0);
		MappedWrite(m_reg.ds, nOffset, nValue);
	}

	void MappedWrite(int nSegment, int nOffset, int nValue)
	{
		_ASSERT(nSegment != 0xcccc);
		if (nSegment >= 0xa000)
		{
			VideoWrite(nSegment, nOffset, nValue);
			return;
		}
		_ASSERT(nSegment * 16 + nOffset < sizeof(data));
		data[nSegment * 16 + nOffset] = (BYTE)nValue;

		if ( nSegment * 16 + nOffset >= 0x31670 + 0x0800 &&
			 nSegment * 16 + nOffset <= 0x31670 + 0x0d00 )
		{
			int f = 9;
			data[nSegment * 16 + nOffset] = 0xff;
		}
	}

	void VideoWrite(int nSegment, int nOffset, int nValue)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		//addr -= 0xa000*16;
		_ASSERT(m_pVideo);
		m_pVideo->Write(addr, nValue & 0xff);
	}

	int VideoRead(int nSegment, int nOffset)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		//addr -= 0xa000*16;
		_ASSERT(m_pVideo);
		return m_pVideo->Read(addr);
	}

	void PortWrite16(int port, int data)
	{
		_ASSERT(m_pVideo);
		if ( m_pVideo && m_pVideo->PortWrite16(port, data) )
			return;
		printf("Unknown port write port[%x] = %x\n", port, data);
		//_ASSERT(0);
	}

	void PortWrite8(int nPort, int nValue)
	{
		if ( nPort >= 0x40 && nPort <= 0x43)
		{
			m_Timer.Out(nPort, nValue);
			// i8254 timer
			return;
		}
		if ( nPort == 0x61)
		{
			// TODO: sound
			return;
		}
		if ( nPort == 0x3d8 || nPort == 0x3d9 )
		{
			// TODO;
			return;
		}
		if ( nPort == 0x201)
		{
			// TODO: joystick
			return;
		}
		_ASSERT(0);
	}
	
	int PortRead(int nPort)
	{
		if ( nPort >= 0x40 && nPort <= 0x43 )
		{
			return m_Timer.In(nPort);
			// TODO: timer
			return 0;
		}

		if ( nPort == 0x61 )
		{
			// TODO: sound
			return 0;
		}

		if ( nPort == 0x3da )
		{
			// TODO: wait retrace
			//return ( GetTickCount()%20 < 10 ) ? 0 : 8;
			static int counter = 0;
			counter ^= 8;
			return counter;
		}

		if ( nPort == 0x201 )
		{
			// TODO: joystick
			return 0;
		}

		_ASSERT(0);
		return 0;
	}
};
