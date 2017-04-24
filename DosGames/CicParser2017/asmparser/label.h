class CLabel : public string
{
public:
	CLabel(const string& str) : string(str)
	{
		CUtils::replace(*this, "short ", "");
		CUtils::replace(*this, "_code_", "_");
	}
};
