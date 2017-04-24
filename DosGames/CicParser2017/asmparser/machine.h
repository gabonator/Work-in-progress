//#pragma once
//#include <vector>
//#include "instructions.h"

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
		bool interrupt;
	};

	typedef shared_ptr<CInstruction> SInstruction;
	vector<SInstruction> m_arrCode;
	vector<string> m_arrSource;

	int m_pc;
	CRegisters m_reg;
	CFlags m_flag;

	// Temp helpers;
	int m_nCmpOp1;
	int m_nCmpOp2;

	vector<int> m_arrCallStack;
	vector<int> m_arrStack;

	CDos m_dos;
	CEga EGA;

public:
	CMachine()
	{
		m_arrStack.resize(1024, 0);
		m_reg.sp = 512;

		FILE* f;
		fopen_s(&f, "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\data", "rb");
		fread(data, 0x955d, 1, f); 
		fclose(f);
	}

	/*
	int& stackAt(int nOffset)
	{
		_ASSERT(nOffset > 0
	}*/

	void Eval(vector<shared_ptr<CInstruction>>& arrCode, vector<string>& arrSource)
	{
		m_arrCode = arrCode;
		m_arrSource = arrSource;
		
		m_pc = -1;

		Call("start");
		for ( int i=0; i<1000; i++)
			Eval();
	}

	void Call(string label)
	{
		// return to next instruction
		m_arrCallStack.push_back(m_pc); // == -1 ? -1 : m_pc+1);
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);
		
		// skip function label
		m_pc++;
	}

	void Goto(string label)
	{
		m_pc = FindLabel(label);
		_ASSERT(m_pc != -1);

		// skip goto label
		m_pc++;
	}

	void Return()
	{
		m_pc = m_arrCallStack.back();
		m_arrCallStack.pop_back();
	}
	
	void Eval()
	{
		SInstruction sInstruction = m_arrCode[m_pc];
		printf("%s\n", m_arrSource[m_pc].c_str());
		m_pc++;

		sInstruction->Eval(*this);
	}

	int FindLabel(string label)
	{
		for (int i=0; (size_t)i<m_arrCode.size(); i++)
		{
			CILabel* pLabel = dynamic_cast<CILabel*>(m_arrCode[i].get());		
			if (pLabel && pLabel->m_label == label)
				return i;

			CIFunction* pFunction = dynamic_cast<CIFunction*>(m_arrCode[i].get());
			if (pFunction && pFunction->m_eBoundary == CIFunction::Begin && pFunction->m_strName == label)
				return i;
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
				return data[v.m_nValue] | (data[v.m_nValue+1] << 8);

			case CValue::byteptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue < sizeof(data));
				return data[v.m_nValue];

			case CValue::byteptrval: 
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return data[m_reg.ds*16 + GetValue(*v.m_value)];

			case CValue::wordptrval: 
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				return data[m_reg.ds*16 + GetValue(*v.m_value)] | (data[m_reg.ds*16 + GetValue(*v.m_value) + 1] << 8);

			case CValue::bp_plus: 
				return m_reg.bp + v.m_nValue;
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
				_ASSERT(v.m_nValue >= 0 && v.m_nValue+1 < sizeof(data));
				data[v.m_nValue] = nValue & 0xff;
				data[v.m_nValue+1] = nValue >> 8;
			return;

			case CValue::byteptr: 
				_ASSERT(v.m_nValue >= 0 && v.m_nValue < sizeof(data));
				data[v.m_nValue] = nValue;
			return;

			case CValue::byteptrval: 
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				data[m_reg.ds*16 + GetValue(*v.m_value)] = nValue;
			return;

			case CValue::wordptrval: 
				_ASSERT(m_reg.ds*16 + GetValue(*v.m_value) >= 0 && v.ds*16 + GetValue(*v.m_value) < sizeof(data));
				data[m_reg.ds*16 + GetValue(*v.m_value)] = nValue & 0xff;
				data[m_reg.ds*16 + GetValue(*v.m_value)+1] = nValue >> 8;
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
			if ( m_reg.a.r16.ax == 0 )
    		{
   				m_reg.a.r16.ax = 0x0000; // no mouse
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
	void VideoWrite(int nSegment, int nOffset, int nValue)
	{
		unsigned int addr = nSegment * 16 + nOffset;

		_ASSERT( addr/16 >= 0xa000 && addr/16 < 0xf000 );
		addr -= 0xa000*16;
		EGA.Write(addr, nValue & 0xff);
	}

	int VideoRead(int nSegment, int nOffset, int nValue)
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
			static int counter = 0;
			counter ^= 8;
			return counter;
		}

		_ASSERT(0);
		return 0;
	}
};
