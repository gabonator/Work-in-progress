string CValue::ToC()
{
	stringstream ss;

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

	case constant:
		{
			char str[32] = "?";
			if ( m_eRegLength == CValue::r8 )
				sprintf_s(str, 31, "0x%02x", m_nValue);
			else
			if ( m_eRegLength == CValue::r16 )
				sprintf_s(str, 31, "0x%04x", m_nValue);
			else
				sprintf_s(str, 31, "%d", m_nValue); // TODO
			return str;
		}

	case CValue::wordptr:
		{
			ss << "*(WORD*)&memory[0x" << hex << uppercase << m_nValue << "]";
			return ss.str();
		}

	case CValue::wordptrasbyte:
	case CValue::byteptr:
		{
			ss << "memory[0x" << hex << uppercase << m_nValue << "]";
			return ss.str();
		}
	default:
		_ASSERT(0);
	}
	return "?";
}
