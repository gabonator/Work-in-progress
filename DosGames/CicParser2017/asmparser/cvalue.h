string CValue::ToC()
{
	stringstream ss;
	char str[32] = "?";

	switch (m_eType)
	{
	case ah: return "_ah";
	case al: return "_al";
	case ax: return "_ax";
	case bh: return "_bh";
	case bl: return "_bl";
	case bx: return "_bx";
	case ch: return "_ch";
	case cl: return "_cl";
	case cx: return "_cx";
	case dh: return "_dh";
	case dl: return "_dl";
	case dx: return "_dx";

	case cs: return "_cs";
	case ds: return "_ds";
	case es: return "_es";
	case si: return "_si";
	case di: return "_di";
	case bp: return "_bp";

	case constant:
		if ( m_eRegLength == CValue::r8 )
			sprintf_s(str, 31, "0x%02x", m_nValue);
		else
		if ( m_eRegLength == CValue::r16 )
			sprintf_s(str, 31, "0x%04x", m_nValue);
		else
			sprintf_s(str, 31, "%d", m_nValue); // TODO
		return str;

	case CValue::byteptrasword:
	case CValue::wordptr:
		ss << "*(WORD*)&memory[0x" << hex << uppercase << m_nValue << "]";
		return ss.str();

	case CValue::wordptrasbyte:
	case CValue::byteptr:
		ss << "memory[0x" << hex << uppercase << m_nValue << "]";
		return ss.str();

	case CValue::byteptrval:
		return "memory[ofs(" + m_value->ToC() + ")]";

	case CValue::bx_plus_si:
		return "_bx + _si";

	case CValue::bx_plus:
		ss << "_bx + " << m_nValue;
		return ss.str();

	case CValue::segment:
		_ASSERT(m_eSegment == dseg);
		return "SEG_DATA";

	case CValue::wordptrval:
		ss << "*(WORD*)&memory[ofs(" << m_value->ToC() << ")]";
		return ss.str();

	case CValue::es_ptr_di:
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[adr(_es, _di)]";
		else if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)memory[adr(_es, _di)]";
		else
			_ASSERT(0);
		return ss.str();

	case CValue::es_ptr_di_plus:
		_ASSERT(m_nValue >= 0);
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[_es*16 + ofs(_di + " << m_nValue << ")]";
		else
		if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)memory[_es*16 + ofs(_di + " << m_nValue << ")]";
		else
			_ASSERT(0);
		return ss.str();

	case CValue::es_ptr:
		_ASSERT(m_nValue >= 0);
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[_es*16 + " << m_nValue << "]";
		else
		if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)memory[_es*16 + " << m_nValue << "]";
		else
			_ASSERT(0);
		return ss.str();

	case CValue::si_plus:
		_ASSERT(m_nValue >= 0);
		ss << "_si + " << m_nValue;
		return ss.str();

	case CValue::codebyte:
		ss << "byte_code_" << std::hex << std::uppercase << m_nValue; 
		return ss.str();

	case CValue::codeword:
		ss << "word_code_" << std::hex << std::uppercase << m_nValue; 
		return ss.str();

	case CValue::wordptr_es:
		// TODO: what if value = 0xffff ?
		ss << "*(WORD*)&memory[adr(_es, " << m_nValue << ")]";
		return ss.str();

	case CValue::bx_plus_si_plus:
		_ASSERT(m_eRegLength == r16);
		ss << "*(WORD*)&memory[ofs(_bx + _si + " << m_nValue << ")]";
		return ss.str();

	case CValue::bx_plus_di:
		//_ASSERT(m_eRegLength == r16);
		ss << "_bx + _di";
		return ss.str();

	case CValue::ds_ptr_bp_plus:
		_ASSERT(m_eRegLength == r16);
		ss << "*(WORD*)&memory[adr(_ds, _bp + " << m_nValue << ")]";
		return ss.str();

	case CValue::di_plus:
		//_ASSERT(m_eRegLength == r16);
		ss << "_di + " << m_nValue;
		return ss.str();

	default:
		_ASSERT(0);
	}
	return "?";
}
