class CValue : public CSerializable
{
public:
	enum EType {
		ah, al, ax,
		bh, bl, bx,
		ch, cl, cx,
		dh, dl, dx,
		ds, es, si, di, cs, bp, sp,
		ss,
		
		constant,
		
		wordptr, byteptr, wordptrasbyte,
		byteptrval, wordptrval,
		
		si_plus,
		bx_plus,
		bx_plus_si,
		bp_plus,
		di_plus,

		codeword,
		codebyte,

		es_ptr_di,
		bx_plus_di,
		es_ptr_di_plus,
		stack_bp_plus,

		byteptrasword,

		byteptrseg,
		wordptrseg,
		segment,
		wordptr_es,
		dwordptrseg,
		dwordptrasword,

		es_ptr,
		bx_plus_si_plus,
		ds_ptr_bp_plus,

		invalid
	};

	enum ERegLength 
	{
		r8, r16, r32, unknown
	};

	enum ESegment {
		invalidsegment,
		dseg,
		seg002,
		seg003
	};

public:
	EType m_eType;
	ERegLength m_eRegLength;

	shared_ptr<CValue> m_value;
	int m_nValue;	
	ESegment m_eSegment;

public:
	CValue()
	{
		m_eRegLength = unknown;
		m_eType = invalid;
		m_eSegment = invalidsegment;
	}

	CValue(const std::string& str, ERegLength eRegLength = unknown)
	{
		m_nValue = 0;
		Parse(str, eRegLength);
	}

	void Parse(const std::string& str, ERegLength eRegLength = unknown)
	{
		m_eRegLength = unknown;
		m_eSegment = invalidsegment;
		std::string value = CUtils::Trim(str);
		
		m_eType = RegisterType8(value);
		
		if (m_eType != invalid)
		{
			m_eRegLength = r8;
			return;
		}

		m_eType = RegisterType16(value);
		
		if (m_eType != invalid)
		{
			m_eRegLength = r16;
			return;
		}

		if (CUtils::ParseLiteral(str, m_nValue))
		{
			if ( CUtils::match("^[0-9A-F]{2}h$", value.c_str()) )
				m_eRegLength = r8;
			if ( CUtils::match("^0[0-9A-F]{2}h$", value.c_str()) )
				m_eRegLength = r8;
			if ( CUtils::match("^0[0-9A-F]{4}h$", value.c_str()) )
				m_eRegLength = r16;
			
			m_eType = constant;
			return;
		}

		if (str == "seg dseg" || str == "seg data")
		{
			m_nValue = 0;
			m_eType = segment;
			m_eSegment = dseg;
			return;
		}

		if ( str == "seg seg003" )
		{
			m_nValue = 0;
			m_eType = segment;
			m_eSegment = seg003;
			return;
		}

		if ( str == "seg seg002" )
		{
			m_nValue = 0;
			m_eType = segment;
			m_eSegment = seg002;
			return;
		}

		vector<string> matches;
		if ( CUtils::match("^word_data_(.+)\\+(.+)h$", value.c_str(), matches) )
		{
			m_eType = wordptr; // urcite ptr?
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]) + CUtils::ParseLiteral("0x" + matches[1]);
			return;
		}

		if ( CUtils::match("^word_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptr; // urcite ptr?
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^byte ptr \\[(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = byteptrval;
			m_eRegLength = r16;
			m_value = make_shared<CValue>(matches[0]);
			// TODO: HOPLA TOTO JE PTR
			// iba castujeme na byte, nepotrebujeme
			//Parse(matches[0]);
			//m_eRegLength = r8;
			return;
		}

		if ( CUtils::match("^word ptr \\[(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = wordptrval;
			m_eRegLength = r16;
			m_value = make_shared<CValue>(matches[0]);
			return;
		}

		if ( CUtils::match("^word ptr (es):(.+)$", value.c_str(), matches) )
		{
			m_eType = wordptr_es;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral(matches[1]);
			//m_value = make_shared<CValue>(matches[1], CValue::r16);
			return;
		}

		if ( CUtils::match("^byte ptr word_data_(.+)\\+(.+)h$", value.c_str(), matches) )
		{
			m_eType = wordptrasbyte;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]) + CUtils::ParseLiteral("0x" + matches[1]);
			return;
		}

		if ( CUtils::match("^word ptr byte_data_(.+)\\+(.+)h$", value.c_str(), matches) )
		{
			m_eType = byteptrasword;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]) + CUtils::ParseLiteral("0x" + matches[1]);
			return;
		}

		if ( CUtils::match("^byte ptr word_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptrasbyte;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^word ptr dword_dseg_(.*)$", value.c_str(), matches) )
		{
			m_eType = dwordptrasword;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}


		if ( CUtils::match("^byte_data_(.*)$", value.c_str(), matches) )
		{
			m_eType = byteptr;
			m_eRegLength = r8;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^byte_dseg_(.*)$", value.c_str(), matches) )
		{
			m_eType = byteptrseg;
			m_eSegment = dseg;
			m_eRegLength = r8;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^byte_seg003_(.*)$", value.c_str(), matches) )
		{
			m_eType = byteptrseg;
			m_eSegment = seg003;
			m_eRegLength = r8;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^word_dseg_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptrseg;
			m_eSegment = dseg;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^word_seg003_(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptrseg;
			m_eSegment = seg003;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^dword_dseg_(.*)$", value.c_str(), matches) )
		{
			m_eType = dwordptrseg;
			m_eSegment = dseg;
			m_eRegLength = r32;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^ds:\\[bp\\+(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = ds_ptr_bp_plus;
			m_nValue = CUtils::ParseLiteral("0x"+matches[0]);
			m_eRegLength = r16;
			return;
		}

		if ( CUtils::match("^\\[bp\\+arg_(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = stack_bp_plus;
			m_nValue = CUtils::ParseLiteral("0x"+matches[0])+4;
			_ASSERT(eRegLength == r16 || eRegLength == r8);
			m_eRegLength = eRegLength;
			return;
		}

		if ( CUtils::match("^\\[bp\\+var_(.*)\\]$", value.c_str(), matches) )
		{
			m_eType = stack_bp_plus;
			m_nValue = -CUtils::ParseLiteral("0x"+matches[0]);
			m_eRegLength = r16;
			return;
		}

		if ( CUtils::match("^\\[(.*)\\]$", value.c_str(), matches) )
		{
			_ASSERT(eRegLength != unknown);
			if ( eRegLength == r8 )
			{
				m_value = make_shared<CValue>(matches[0]);
				m_eType = byteptrval;
				m_eRegLength = r8;
				return;
			}
			if ( eRegLength == r16 )
			{
				m_value = make_shared<CValue>(matches[0]);
				m_eType = wordptrval;
				m_eRegLength = r16;
				return;
			}
		}

		if ( CUtils::match("^si\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = si_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( value == "bx+di" )
		{
			m_eType = bx_plus_di;
			return;
		}

		if ( CUtils::match("^bx\\+si\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = bx_plus_si_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bx\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = bx_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bx\\-(.*)$", value.c_str(), matches) )
		{
			m_eType = bx_plus;
			m_nValue = -CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^di\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = di_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^si\\-(.*)$", value.c_str(), matches) )
		{
			m_eType = si_plus;
			m_nValue = -CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+arg_(.*)$", value.c_str(), matches) )
		{
			_ASSERT(0);
			m_eType = bp_plus;
			m_nValue = CUtils::ParseLiteral("0x"+matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+var_(.*)$", value.c_str(), matches) )
		{
			_ASSERT(0);
			m_eType = bp_plus;
			m_nValue = -CUtils::ParseLiteral("0x"+matches[0]);
			return;
		}

		if ( CUtils::match("^cs:word_code_(.*)$", value.c_str(), matches) )
		{
			m_eType = codeword;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^cs:byte_code_(.*)$", value.c_str(), matches) )
		{
			m_eType = codebyte;
			m_eRegLength = r8;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^offset loc_seg002_(.+)$", value.c_str(), matches) )
		{
			m_eType = constant;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( CUtils::match("^offset loc_code_(.+)$", value.c_str(), matches) )
		{
			m_eType = constant;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral("0x" + matches[0]);
			return;
		}

		if ( value == "es:[di]" )
		{
			m_eRegLength = r8;
			m_eType = es_ptr_di;
			return;
		}

		if ( CUtils::match("^es:\\[di\\+(.*)\\]$", value.c_str(), matches) )
		{
			m_eRegLength = eRegLength;
			m_eType = es_ptr_di_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^ds:(.*)$", value.c_str(), matches) )
		{
			_ASSERT(eRegLength == r16 || eRegLength == r8);
			if ( eRegLength == r16 )
			{
				m_eType = wordptr;
				m_eRegLength = r16;
			} else
			if ( eRegLength == r8 )
			{
				m_eType = byteptr;
				m_eRegLength = r8;
			} else
			{
				_ASSERT(0);
			}

			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^byte ptr ds:(.*)$", value.c_str(), matches) )
		{
			m_eType = byteptr;
			m_eRegLength = r8;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^word ptr ds:(.*)$", value.c_str(), matches) )
		{
			m_eType = wordptr;
			m_eRegLength = r16;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^bp\\+(.*)$", value.c_str(), matches) )
		{
			m_eType = bp_plus;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^es:word_data_(.+)\\+(.+)$", value.c_str(), matches) )
		{
			m_eRegLength = r16;
			m_eType = es_ptr;
			m_nValue = CUtils::ParseLiteral("0x"+matches[0]) + CUtils::ParseLiteral(matches[1]);
			return;
		}

		if ( CUtils::match("^es:(.+)$", value.c_str(), matches) )
		{
			_ASSERT(eRegLength == r8 || eRegLength == r16);
			m_eRegLength = eRegLength;
			m_eType = es_ptr;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		if ( CUtils::match("^byte ptr es:(.+)$", value.c_str(), matches) )
		{
			m_eRegLength = r8;
			m_eType = es_ptr;
			m_nValue = CUtils::ParseLiteral(matches[0]);
			return;
		}

		printf("%s\n", str.c_str());
		_ASSERT(0);
	}

	static void SameOperands(CValue& op1, CValue& op2, string str1, string str2)
	{
		if (str1.length() == 2)
		{
			op1.Parse(str1);
			op2.Parse(str2, op1.GetRegisterLength());
		} else
		{
			op2.Parse(str2);
			op1.Parse(str1, op2.GetRegisterLength());
		}
	}

	static EType RegisterType8(std::string str)
	{
		CheckEnum(ah);		CheckEnum(al);
		CheckEnum(bh);		CheckEnum(bl);
		CheckEnum(ch);		CheckEnum(cl);
		CheckEnum(dh);		CheckEnum(dl);
		return invalid;
	}

	static EType RegisterType16(std::string str)
	{
		CheckEnum(ax);		CheckEnum(bx);		CheckEnum(cx);		CheckEnum(dx);
		CheckEnum(ds);		CheckEnum(es);		CheckEnum(si);		CheckEnum(di);
		CheckEnum(cs);		CheckEnum(bp);		CheckEnum(sp);		CheckEnum(ss);
		CheckEnum2("bx+si", bx_plus_si);
		return invalid;
	}

	ERegLength GetRegisterLength()
	{
		return m_eRegLength;
	}

	/*
	void Fix(string& key)
	{
		vector<string> matches;
		string out = key;

		if ( key == "ax" || key == "bx" || key == "cx" || key == "dx" )
			return string("r16[")+key+"]";
		if ( key == "ah" || key == "bh" || key == "ch" || key == "dh" ||
			 key == "al" || key == "bl" || key == "cl" || key == "dl" )
			return string("r8[")+key+"]";

		// decimal
		if ( CUtils::match("^([0-9]*)$", key.c_str(), &matches) )
			return out;
		// hex
		if ( CUtils::match("^([0-9A-F]+)h$", key.c_str(), &matches) )
		{
			out = string("0x") + matches[1];
			return out;
		}
		//byte ptr ds:44D0h
		if ( match("^cs:(.*)$", key.c_str(), &matches) )
			return matches[1];
		else if ( match("^seg\\s(.*)$", key.c_str(), &matches) )
			out = string("seg_")+matches[1];
		else if ( match("^byte_data_(.*)\\+(.*)$", key.c_str(), &matches) )
			out = string("_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(_value(matches[2]))) + "]";
		else if ( match("^word_data_(.*)\\+(.*)$", key.c_str(), &matches) )
			out = string("*(WORD*)&_data[") + toString(toNumber(string("0x") + matches[1]) + toNumber(_value(matches[2]))) + "]";
		else if ( match("^byte_data_(.*)$", key.c_str(), &matches) )
			out = string("_data[0x") + _value(matches[1]) + string("]");
		else if ( match("^word_data_(.*)$", key.c_str(), &matches) )
			out = string("*(WORD*)&_data[0x") + _value(matches[1]) + string("]");
		else if ( match("^es:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
			out = string("*(WORD*)&_data[ADR(es,") + _value(matches[1]) + string(")]");
		else if ( match("^ds:\\[(.*)\\]", key.c_str(), &matches) ) // es:[di] ??
			out = string("*(WORD*)&_data[ADR(ds,") + _value(matches[1]) + string(")]");

		else if ( match("^(cs|ds|es):(.*)$", key.c_str(), &matches) )
		{
			out = _value(matches[2]);
			if (out.find('[') != string::npos )
			{
				replacefirst(out, "[", format("[ADR(%s, ", matches[1].c_str()));
				_ASSERT( out.substr(out.length()-1,1) == "]" );
				out = out.substr(0, out.length()-1) + ")]";
			}
			else
				out = format("*(WORD*)&_data[ADR(%s,%s)]", matches[1].c_str(), out.c_str());
		}

		else if ( match("^\\[(.*)\\+(.*)\\+(.*)\\]$", key.c_str(), &matches) )
		{
			if ( matches[1] == "si" )
				out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + string(" + ") + _value(matches[2]) + string(" + ") + _value(matches[3]) + (")]");
			else
				out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" + ") + _value(matches[2]) + string(" + ") + _value(matches[3]) + (")]");
		}
		else if ( match("^\\[(.*)\\+(.*)\\]$", key.c_str(), &matches) )
		{
			if ( matches[1] == "si" )
				out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + string(" + ") + _value(matches[2]) + (")]");
			else
				out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" + ") + _value(matches[2]) + (")]");
		}
		else if ( match("^\\[(.*)\\-(.*)\\]$", key.c_str(), &matches) )
		{
			if ( matches[1] == "si" )
				out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + (")]");
			else
				out = string("*(WORD*)&_data[OFS(") + _value(matches[1]) + string(" - ") + _value(matches[2]) + (")]");
		}
		else if ( match("^\\[(.*)\\]$", key.c_str(), &matches) )
		{
			if ( matches[1] == "si" )
				out = string("*(WORD*)&_data[ADR(ds, ") + _value(matches[1]) + (")]");
			else
				out = string("*(WORD*)&_data[") + _value(matches[1]) + ("]");
		}
		else if ( match("^word ptr (.*)$", key.c_str(), &matches) )
		{
			out = _value(matches[1]);
			if ( out.find("*(WORD*)") == -1 )
				out = string("*(WORD*)&") + out;
			//out = string("*(WORD*)(") + value(matches[1]) + string(")");
		}
		else if ( match("^byte ptr (.*)$", key.c_str(), &matches) )
		{
			out = _value(matches[1]);
			replace(out, "*(WORD*)&", "");
		}	
		if ( match("^offset\\s(.*)$", key.c_str(), &matches) )
			out = string("&") + _value(matches[1]); 
	
		return out;
	}*/

	virtual void Serialize(CSerializer& s)
	{
		s << _enum(m_eType) << _enum(m_eRegLength) << _shared<CValue>(m_value) << m_nValue << _enum(m_eSegment);
	}

	string ToC();
};
