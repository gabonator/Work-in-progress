void CDos::Interrupt()
{
	static FILE* ff[8] = {0};

	switch (_ah)
	{
	case 0x09:
		printf("DOS - print DS:%04x\n", _dx);
		return;

	case 0x4c:			
		printf("DOS - process exit code %d\n", _al);
		return;
/*
	case 0x3d:			
		// open file DS:DX - filename
		{
			_ASSERT(_al == 0);

			int j;
			for ( j=0; j<8; j++)
				if (ff[j] == 0)
					break;

			char* strName = (char*)&memory[_ds*16 + _dx];
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
			_ASSERT( (_bx & 0xf000) == 0xf000);
			FILE*f = ff[_bx ^ 0xf000];
			int ofs = _ds*16+_dx;
			int len = _cx;
			_ASSERT(ofs >= 0 && ofs + len < sizeof(memory));
			unsigned char* ptr = &memory[ofs];
			size_t nRead = fread(ptr, 1, len, f);
			_ASSERT(nRead == len);
			//_ASSERT( 0x5a5c < ofs || 0x5a5c > ofs+len); 
			_flags.carry = 0;
			printf("Read %x bytes into %04x:%04x\n", len, _ds, _dx);
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
		*/
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
