#include "std.h"

namespace std
{
	string& string::operator=(const string& other)
	{
		data = other.data;
		return *this;
	}

	string& string::operator+=(const string& other)
	{
		append(other);
		return *this;
	}

	const string operator+(const string& me, const string& other)
	{
		string newString(me);
		newString.append(other);
		return newString;
	}

	const string operator+(const string& me, const char ch)
	{
		string newString(me);
		char buf[2];
		buf[0] = ch;
		buf[1] = '\0';
		newString.append(buf);
		return newString;
	}

	const string operator+(const string& me, int n)
	{
		char buf[255];
		sprintf(buf, "%d", n);
		string newString(me);
		newString.append(buf);
		return newString;
	}

	ostringstream& operator<<(ostringstream& os, const string& s)
	{
		os.buffer = os.buffer + s.c_str();
		return os;
	}
}
