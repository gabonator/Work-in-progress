class CUtils
{
	static std::map<string, regex> m_mapCache;

public:
	static bool match(const string& strRegex, const string& strInput, vector<string>& arrMatches)
	{
		auto i = m_mapCache.find(strRegex);
		if ( i == m_mapCache.end() )
		{
			regex newRegex(strRegex, std::regex_constants::ECMAScript);
			m_mapCache.insert(make_pair<string, regex>(strRegex, newRegex));

			return match(newRegex, strInput, arrMatches);
		}

		return match(i->second, strInput, arrMatches);
	}

	static bool match(const regex& regexMatch, const string& strInput, vector<string>& arrMatches)
	{
		_ASSERT(arrMatches.empty());

		cmatch results;
		if ( !regex_match(strInput.c_str(), results, regexMatch) )
			return false;

		for (auto it = ++results.begin(); it != results.end(); it++)
			arrMatches.push_back(it->str().c_str()); // string(it->first, it->second).c_str());

		return true;
	}

	static bool match(const string& strRegex, const string& strInput)
	{
		auto i = m_mapCache.find(strRegex);
		if ( i == m_mapCache.end() )
		{
			regex newRegex(strRegex, std::regex_constants::ECMAScript);
			m_mapCache.insert(make_pair<string, regex>(strRegex, newRegex));

			return match(newRegex, strInput);
		}

		return match(i->second, strInput);
	}

	static bool match(const regex& regexMatch, const string& strInput)
	{
		return regex_match(strInput.c_str(), regexMatch);
	}
	/*
	static bool replacefirst(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);
		if(start_pos == std::string::npos)	
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	static bool replace(std::string& str, const std::string& from, const std::string& to) 
	{
		while ( replacefirst( str, from, to ) );
		return true;
	}*/

	static bool replace(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);
		if(start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	static bool ParseLiteral(const string& _str, int& nValue)
	{
		string str = Trim(_str);
		if ( match("^\\d+$", str.c_str()) )
		{
			nValue = atoi(str.c_str());
			return true;
		}

		vector<string> matches;

		if ( match("^([0-9A-F]+)h$", str.c_str(), matches) )
		{
			std::stringstream converter(matches[0]);
			converter >> std::hex >> nValue;
			return true;
		}
		
		if ( match("^0x([0-9A-F]+)$", str.c_str(), matches) )
		{
			std::stringstream converter(matches[0]);
			converter >> std::hex >> nValue;
			return true;
		}

		return false;
	}

	static int ParseLiteral(const string& str)
	{
		int nAux;

		bool bOk = ParseLiteral(str, nAux);
		_ASSERT(bOk);

		return nAux;
	}

	static std::string Trim(std::string str)
	{
		size_t first = str.find_first_not_of(' ');
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}
};
