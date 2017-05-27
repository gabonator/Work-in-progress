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
		ss << "*(WORD*)&memory[adr(_ds, 0x" << hex << uppercase << m_nValue << ")]";
		return ss.str();

	case CValue::wordptrasbyte:
	case CValue::byteptr:
		// TODO: vsade pridat adr(_ds, ...)
		ss << "memory[adr(_ds, 0x" << hex << uppercase << m_nValue << ")]";
		return ss.str();

	case CValue::byteptrval:
		return "memory[adr(_ds, " + m_value->ToC() + ")]";

	case CValue::bx_plus_si:
		return "_bx + _si";

	case CValue::bx_plus:
		ss << "_bx + " << m_nValue;
		return ss.str();

	case CValue::segment:
		_ASSERT(m_eSegment == dseg);
		return "SEG_DATA";

	case CValue::wordptrval:
		ss << "*(WORD*)&memory[adr(_ds, " << m_value->ToC() << ")]";
		return ss.str();

	case CValue::es_ptr_di:
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[adr(_es, _di)]";
		else if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)&memory[adr(_es, _di)]";
		else
			_ASSERT(0);
		return ss.str();

	case CValue::es_ptr_di_plus:
		_ASSERT(m_nValue >= 0);
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[adr(_es, _di + " << m_nValue << ")]";
		else
		if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)&memory[adr(_es, _di + " << m_nValue << ")]";
		else
			_ASSERT(0);
		return ss.str();

	case CValue::es_ptr:
		_ASSERT(m_nValue >= 0);
		if ( m_eRegLength == CValue::r8 )
			ss << "memory[adr(_es, " << m_nValue << ")]";
		else
		if ( m_eRegLength == CValue::r16 )
			ss << "*(WORD*)&memory[adr(_es, " << m_nValue << ")]";
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
		ss << "_bx + _si + " << m_nValue;
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


string CValue::GetC(CStaticAnalysis* pAnalysis)
{
	stringstream videoOffset;

	switch (m_eType)
	{
	case CValue::byteptrasword:
	case CValue::wordptr:
	case CValue::byteptrval:
	case CValue::ds_ptr_bp_plus:
		//_ASSERT(pAnalysis->m_ds.GetValue() == 0x0000); // TODO: FIX IT!!!!!!!!!!
		return ToC();

	case CValue::es_ptr_di:
		videoOffset << "_di";
		break;

	case CValue::es_ptr_di_plus:
		videoOffset << "_di" << m_nValue;
		break;

	case CValue::es_ptr:
		videoOffset << m_nValue;
		break;

	case CValue::wordptr_es:
		videoOffset << m_nValue;
		break;
	}

	if (videoOffset.str().empty())
		return ToC();

	if (pAnalysis->m_es.GetValue() != 0xb800 && pAnalysis->m_es.GetValue() != 0xa000)
		return ToC();

	stringstream result;
	if (m_eRegLength == CValue::r8)
		result << "_videoRead8(_esAssume(0x" << std::hex << pAnalysis->m_es.GetValue() << "), " << videoOffset.str() << ")";
	else if (m_eRegLength == CValue::r16)
		result << "_videoRead16(_esAssume(0x" << std::hex << pAnalysis->m_es.GetValue() << "), " << videoOffset.str() << ")";
	else
		_ASSERT(0);

	return result.str();
}

string CValue::SetC(CStaticAnalysis* pAnalysis)
{
	stringstream videoOffset;

	switch (m_eType)
	{
	case CValue::byteptrasword:
	case CValue::wordptr:
	case CValue::byteptrval:
	case CValue::ds_ptr_bp_plus:
		// TODO: the same with _ds!
		//_ASSERT(pAnalysis->m_ds.GetValue() == 0x0000); //TODO: FIX IT!!!!! UNSURE ABOUT DS VALUE??? 
		return ToC();

	case CValue::es_ptr_di:
		videoOffset << "_di";
		break;

	case CValue::es_ptr_di_plus:
		videoOffset << "_di + 0x" << std::hex << m_nValue; // overflow?
		break;

	case CValue::es_ptr:
		videoOffset << "0x" << std::hex << m_nValue;
		break;

	case CValue::wordptr_es:
		videoOffset << "0x" << std::hex << m_nValue;
		break;
	}

	if (videoOffset.str().empty())
		return ToC();

	if (pAnalysis->m_es.GetValue() != 0xb800 && pAnalysis->m_es.GetValue() != 0xa000)
		return ToC();

	stringstream result;
	if (m_eRegLength == CValue::r8)
		result << "_videoWrite8(_esAssume(0x" << std::hex << pAnalysis->m_es.GetValue() << "), " << videoOffset.str() << ", ($value))";
	else if (m_eRegLength == CValue::r16)
		result << "_videoWrite16(_esAssume(0x" << std::hex << pAnalysis->m_es.GetValue() << "), " << videoOffset.str() << ", ($value))";
	else
		_ASSERT(0);

	return result.str();

}
