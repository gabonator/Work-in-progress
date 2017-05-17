class CLabel : public string
{
public:
	CLabel(const string& str) : string(str)
	{
		if ( empty() )
			return;

		CUtils::replace(*this, "short ", "");

		// strip _code_ only in function names, not in variables
		if ( find("byte_") == string::npos && find("word_") == string::npos )
			CUtils::replace(*this, "_code_", "_");
	}
};
