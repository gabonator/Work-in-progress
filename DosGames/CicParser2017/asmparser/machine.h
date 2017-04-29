//#pragma once
//#include <vector>
//#include "instructions.h"

CEga EGA;
void VideoUpdate();

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
	};

	typedef shared_ptr<CInstruction> SInstruction;
	vector<SInstruction> m_arrCode;
	vector<string> m_arrSource;

	int m_pc;
	CRegisters m_reg;
	CFlags m_flag;

	// Temp helpers;
	CValue::ERegLength m_eCmpLen;
	int m_nCmpOp1;
	int m_nCmpOp2;

	vector<string> m_arrCallStackNames;
	vector<int> m_arrCallStack;
	vector<int> m_arrStack;
	map<string, int> m_mapLabels;

	CDos m_dos;

public:
	CMachine()
	{
		m_arrStack.resize(32, 0);
		m_reg.sp = 16*2;
		m_reg.bp = 0;

		FILE* f;
		fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\data", "rb");
		fread(data, 0x955d, 1, f); 
		fclose(f);
	}

	void Eval(vector<shared_ptr<CInstruction>>& arrCode, vector<string>& arrSource)
	{
		m_arrCode = arrCode;
		m_arrSource = arrSource;
		
		m_pc = -1;

		Call("start");
		for ( int i=0; i<53251000; i++)
		{
			if (i % 100 == 0)
			{
				VideoUpdate();
			}

			Eval();

		}
	}

	void Call(string label)
	{
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
		//static bool blog = false;
		////if ( m_arrSource[m_pc].find("D3A") != string::npos)
		////if ( m_arrSource[m_pc].find("CE7") != string::npos)
		////if ( m_arrSource[m_pc].find("C24") != string::npos)
		//	// 9430 je nula! a ma byt jedna, lebo dostal sa na 759 -> sub_BC5
		////if ( m_arrSource[m_pc].find("9430") != string::npos)
		//// sub_69a -> 759, sub_69a sa vola na konci titulkov
		////if ( m_arrSource[m_pc].find("69A") != string::npos)
		//if ( m_arrSource[m_pc].find("2762") != string::npos) // toto by malo byt intro scroll
		//{
		//	int f = 9;
		//	//blog = true;
		//}
		//if ( m_arrSource[m_pc].find("_3291") != string::npos)
		//{
		//	//blog = true;
		//	int f = 9;
		//}
		//if ( m_arrSource[m_pc].find("_B7C") != string::npos)
		//{
		//	////blog = true;
		//	int f = 9;
		//}
		//if ( m_arrSource[m_pc].find("9430") != string::npos)
		//{
		//	printf("%s\n", m_arrSource[m_pc].c_str());
		//	int f=9;
		//}
		//	if ( m_arrSource[m_pc] == "call sub_code_C24")
		//	{
		//	//	m_pc++;
		//		//blog = true;
		//		int f = 9;
		//	}
		//	
		//	if ( m_arrSource[m_pc].find( "retn" ) != string::npos)
		//	{
		//		for (int i=m_pc; i>0; i--)
		//			if (dynamic_cast<CIFunction*>(m_arrCode[i].get()))
		//			{
		//				//printf("ret from %s\n", dynamic_cast<CIFunction*>(m_arrCode[i].get())->m_strName.c_str());
		//				break;
		//			}
		//		VideoUpdate();
		//		int f = 9;
		//	}

		const string& strDebug0 = m_arrSource[m_pc > 0 ? m_pc-1 : 0];
		const string& strDebug1 = m_arrSource[m_pc];

		SInstruction sInstruction = m_arrCode[m_pc];
		//if (blog )
		//{
		//printf("ax:%04x bx:%04x cx:%04x dx:%04x si:%04x di:%04x\t",
		//	m_reg.a.r16.ax, m_reg.b.r16.bx, m_reg.c.r16.cx, m_reg.d.r16.dx, m_reg.si, m_reg.di);
		//printf("%s\n", m_arrSource[m_pc].c_str());

		//if ( m_arrSource[m_pc].find("_2959") != string::npos)
		//{
		//	int f = 9;
		//}

		//}
		////printf("%d: %s\n", m_pc, m_arrSource[m_pc].c_str());

		m_pc++;

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

	vector<shared_ptr<CInstruction>> GetSubCode(CLabel label)
	{
		vector<shared_ptr<CInstruction>> aux;

		int nBegin = FindLabel(label);
		_ASSERT(nBegin >= 0);
		for (int i=nBegin+1; i<(int)m_arrCode.size() && !dynamic_pointer_cast<CIFunction>(m_arrCode[i]); i++)
			aux.push_back(m_arrCode[i]);

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

			case CValue::wordptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				return MappedRead(v.m_nValue) | (MappedRead(v.m_nValue+1) << 8);

			case CValue::byteptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue < sizeof(data));
				return MappedRead(v.m_nValue);

			case CValue::byteptrval: 
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return MappedRead(m_reg.ds, GetValue(*v.m_value));

			case CValue::wordptrval: 
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return MappedRead(m_reg.ds, GetValue(*v.m_value) & 0xffff) | (MappedRead(m_reg.ds, (GetValue(*v.m_value) + 1) & 0xffff) << 8);

			case CValue::bp_plus: 
				return m_reg.bp + v.m_nValue;

			case CValue::es_ptr_di:
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				return MappedRead(m_reg.es, m_reg.di);

			case CValue::bx_plus_si:
				//_ASSERT(v.GetRegisterLength() == CValue::r8);
				return m_reg.b.r16.bx + m_reg.si;

			case CValue::wordptrasbyte:
				return MappedRead(v.m_nValue);

			case CValue::bx_plus:
				return m_reg.b.r16.bx + v.m_nValue;

			case CValue::si_plus:
				return m_reg.si + v.m_nValue;

			case CValue::stack_bp_plus:
				return StackRead(m_reg.bp + v.m_nValue);

			case CValue::bx_plus_di:
				return m_reg.b.r16.bx + m_reg.di;

			case CValue::codeword:
			{
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
				stringstream ss;
				ss << "byte_code_" << std::hex << std::uppercase << v.m_nValue; 
				CLabel label(ss.str());
				int nIndex = FindLabel(label);
				_ASSERT(nIndex >= 0);
				CIData* pData = dynamic_cast<CIData*>(m_arrCode[nIndex].get());
				_ASSERT(pData->m_strVariableName == label);
				return pData->m_nValue;
			}

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

			case CValue::wordptr: 
				// TODO: toto vsetko musi ist cez mapped, robi sa tam s grafikou!
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				MappedWrite(v.m_nValue, nValue & 0xff);
				MappedWrite(v.m_nValue+1, nValue >> 8);
			return;

			case CValue::byteptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue < sizeof(data));
				MappedWrite(v.m_nValue, nValue);
			return;

			case CValue::byteptrval: 
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				MappedWrite(m_reg.ds, GetValue(*v.m_value), nValue);
			return;

			case CValue::wordptrval: 
				//_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				MappedWrite(m_reg.ds, GetValue(*v.m_value) & 0xffff, nValue & 0xff);
				MappedWrite(m_reg.ds, (GetValue(*v.m_value)+1) & 0xffff, nValue >> 8);
			return;

			case CValue::es_ptr_di:
				_ASSERT(v.GetRegisterLength() == CValue::r8);
				MappedWrite(m_reg.es, m_reg.di, nValue & 0xff);
			return;

			case CValue::codeword:
			{
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
				MappedWrite(v.m_nValue, nValue & 0xff);
			return;

			case CValue::stack_bp_plus:
				StackWrite(m_reg.bp + v.m_nValue, nValue);
			return;

		}
		_ASSERT(0);
	}

	void Interrupt(int i)
	{
		switch (i)
		{
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
				printf("Setting video mode %d\n", m_reg.a.r8.al);
				return;
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
		_ASSERT(nSegment >= 0 && nSegment < 0xf000);
		_ASSERT(nOffset >= 0 && nOffset <= 0xfff5);

		if (nSegment >= 0xa000)
			return VideoRead(nSegment, nOffset);
		_ASSERT(nSegment * 16 + nOffset < sizeof(data));
		return data[nSegment * 16 + nOffset];
	}

	void MappedWrite(int nOffset, int nValue)
	{
		if ( nOffset == 0x9430 )
		{
			int f = 9;
		}
		_ASSERT(m_reg.ds == 0);
		MappedWrite(m_reg.ds, nOffset, nValue);
	}

	void MappedWrite(int nSegment, int nOffset, int nValue)
	{
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
		addr -= 0xa000*16;
		EGA.Write(addr, nValue & 0xff);
	}

	int VideoRead(int nSegment, int nOffset)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		addr -= 0xa000*16;
		return EGA.Read(addr);
	}

	void PortWrite16(int port, int data)
	{
		if ( port == 0x3c4 )
		{
			if ( (data & 0x00ff) == 0x02 )
			{
				/*
				01 = plane 0, 02 = plane 1, 04 = plane 2, 08 = plane 3
				0f = default
				*/
				//printf("Write mask = %02x\n", data>>8 );
				EGA.SetMapMask( data>>8); // 3c5.2
				return;
			}
		}	
		if ( port == 0x3d4 )
		{
			if ( (data & 0x00ff) == 0x0c )
			{
				EGA.SetAddrHi( data >>8 );
				return;
			}
			if ( (data & 0x00ff) == 0x0d )
			{
				EGA.SetAddrLo( data >> 8);
				return;
			}
		}
		if ( port == 0x3ce )
		{
			switch ( data & 0xff )
			{
			case 0x00: EGA.SetSR( data >> 8 ); return;
			case 0x01: EGA.SetEnableSR( data >> 8 ); return;
			case 0x02: EGA.SetCompare( data >> 8 ); return;
			case 0x05: EGA.SetMode( data >> 8 ); return;
			case 0x07: EGA.SetDontCare( data >> 8 ); return;
			case 0x08: EGA.SetBitMask( data >> 8 ); return;
			case 0x03: EGA.SetRotate( data >> 8 ); return;
			default:
				_ASSERT(0);
			}
		}
	}

	void PortWrite8(int nPort, int nValue)
	{
		if ( nPort >= 0x40 && nPort <= 0x43)
		{
			// i8254 timer
			return;
		}
		_ASSERT(0);
	}
	
	int PortRead(int nPort)
	{
		if ( nPort == 0x3da )
		{
			// TODO: wait retrace
			//return ( GetTickCount()%20 < 10 ) ? 0 : 8;
			static int counter = 0;
			counter ^= 8;
			return counter;
		}

		_ASSERT(0);
		return 0;
	}
};