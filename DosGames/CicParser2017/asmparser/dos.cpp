void CDos::Interrupt(CMachine& m)
{
	static FILE* ff[8] = {0};

	switch (m.m_reg.a.r8.ah)
	{
	case 0x09:
		printf("DOS - print DS:%04x\n", m.m_reg.d.r16.dx);
		return;

	case 0x4c:			
		printf("DOS - process exit code %d\n", m.m_reg.a.r8.al);
		return;

	case 0x3d:			
		// open file DS:DX - filename
		{
			_ASSERT(m.m_reg.a.r8.al == 0);

			int j;
			for ( j=0; j<8; j++)
				if (ff[j] == 0)
					break;

			char* strName = (char*)&data[m.m_reg.ds*16 + m.m_reg.d.r16.dx];
			char strFull[128] = "C:\\Data\\Devel\\Github\\Work-in-progress\\DosGames\\JsGoose\\bin\\";
			printf("Open file '%s'\n", strName);
			strcat_s(strFull, 127, strName);
			fopen_s(&ff[j], strFull, "rb");
			m.m_flag.cf = ( ff[j] != nullptr && ff[j] != (FILE*)-1 ) ? false : true;
			m.m_reg.a.r16.ax = j ^ 0xf000;
		}
		return;

	case 0x3f:
		{
			_ASSERT( (m.m_reg.b.r16.bx & 0xf000) == 0xf000);
			FILE*f = ff[m.m_reg.b.r16.bx ^ 0xf000];
			int ofs = m.m_reg.ds*16+m.m_reg.d.r16.dx;
			int len = m.m_reg.c.r16.cx;
			_ASSERT(ofs >= 0 && ofs + len < sizeof(data));
			unsigned char* ptr = &data[ofs];
			size_t nRead = fread(ptr, 1, len, f);
			_ASSERT(nRead == len);
			//_ASSERT( 0x5a5c < ofs || 0x5a5c > ofs+len); 
			m.m_flag.cf = 0;
			printf("Read %x bytes into %04x:%04x\n", len, m.m_reg.ds, m.m_reg.d.r16.dx);
		}
		return;
	case 0x3e:
		{
			_ASSERT( (m.m_reg.b.r16.bx & 0xf000) == 0xf000);
			int nSlot = m.m_reg.b.r16.bx ^ 0xf000;
			_ASSERT(nSlot >= 0 && nSlot < sizeof(ff)/sizeof(ff[0]));
			FILE*f = ff[nSlot];
			fclose(f);
			ff[m.m_reg.b.r16.bx ^ 0xf000] = nullptr;
			m.m_flag.cf = 0;
		}
		return;
	case 0x25:
		// TODO
		printf("DOS: Set interrupt vector - not implemented\n");
		return;
	case 0x35:
		// TODO
		printf("DOS: Get interrupt vector - not implemented\n");
		return;
	}
	_ASSERT(0);
}
