
class CSourceParser
{
public:
	typedef shared_ptr<CInstructionMatcher> SInstructionMatcher;
	vector<SInstructionMatcher> m_arrMatchers;

	vector<shared_ptr<CInstruction>> m_arrCode;
	vector<string> m_arrSource;

	CSourceParser()
	{
		m_arrMatchers.push_back(std::make_shared<CIMFunction>());
		m_arrMatchers.push_back(std::make_shared<CIMLabel>());
		m_arrMatchers.push_back(std::make_shared<CIMReturn>());
		m_arrMatchers.push_back(std::make_shared<CIMFixedArgOp>());
		m_arrMatchers.push_back(std::make_shared<CIMStringOp>());
		m_arrMatchers.push_back(std::make_shared<CIMAssignment>());
		m_arrMatchers.push_back(std::make_shared<CIMAlu>());
		m_arrMatchers.push_back(std::make_shared<CIMFlow>());
		m_arrMatchers.push_back(std::make_shared<CIMCompare>());
		m_arrMatchers.push_back(std::make_shared<CIMData>());
		m_arrMatchers.push_back(std::make_shared<CIMNop>());

		m_arrCode.reserve(20000);
		m_arrSource.reserve(20000);
	}

	void MatchLine(const string& strLine)
	{
		for (vector<SInstructionMatcher>::iterator i = m_arrMatchers.begin(); i != m_arrMatchers.end(); i++)
		{
			shared_ptr<CInstruction> sInstruction = (*i)->Match(strLine);
			if ( sInstruction ) 
			{
				m_arrCode.push_back(sInstruction);
				m_arrSource.push_back(strLine);
				//printf("%s -> %s\n", strLine.c_str(), typeid(*sInstruction).name());
				return;
			}
		}

		printf("%s\n", strLine.c_str());
		_ASSERT(0);
	}

	void Save(char* strFileName)
	{
		std::ofstream f;
		f.open(strFileName, ios::binary);
		_ASSERT(f);

		int nSize = (int)m_arrCode.size();

		CSerializer serializer(f);
		serializer << nSize;

		for (int i=0; i<nSize; i++)
		{
			serializer << m_arrSource[i];
			serializer << string(typeid(*m_arrCode[i]).name());		
			m_arrCode[i]->Serialize(serializer);
		}
		f.close();
	}

	void Load(char* strFileName)
	{
		std::ifstream f;
		f.open(strFileName, ios::binary);
		_ASSERT(f);

		int nLength = 0;

		CSerializer serializer(f);
		serializer << nLength;

		m_arrCode.resize(nLength);
		m_arrSource.resize(nLength);

		for (int i=0; i<nLength; i++)
		{
			string strSourceLine;
			string strClassName;

			serializer << strSourceLine;
			serializer << strClassName;

			CInstruction* pInstruction = CInstruction::FromName(strClassName);
			_ASSERT(pInstruction);
			pInstruction->Serialize(serializer);

			m_arrCode[i] = shared_ptr<CInstruction>(pInstruction);
			m_arrSource[i] = strSourceLine;
		}
		/*
		for (int i=0; (size_t)i<m_arrCode.size(); i++)
		{
			serializer << string(typeid(*m_arrCode[i]).name());		
			m_arrCode[i]->Serialize(serializer);
		}*/
		f.close();
	}

	void Parse(char* strFileName)
	{
		FILE* f = nullptr;
		fopen_s(&f, strFileName, "r");
		int i = 0;
		while (!feof(f))
		{
			printf("\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08%d", i++);

			// TODO:
			//if ( i > 2500 )
			//	break;

			char strLine[1024];
			fgets(strLine, 1023, f);
			if ( strLine[0] )
				strLine[strlen(strLine)-1] = 0;
			
			string _strLine = Trim(strLine);

			if ( _strLine.length() == 0 )
				continue;

			MatchLine(_strLine);
		}
		fclose(f);
	}

	string Trim(string strLine)
	{
		const char *b = strLine.c_str();
		const char *e = b + strlen(b);
		const char *cmt = strstr(b, ";");
		
		if ( cmt )
			e = cmt;

		while (b[0] == '\t' || b[0] == ' ')
			b++;
		while (e-b > 0 && (e[-1] == ' ' || e[-1] == '\t'))
			e--;

		for (char* i = (char*)b; i<e; i++)
			if ( *i == 9 )
				*i = ' ';

		return string(b, e);
	}

};
