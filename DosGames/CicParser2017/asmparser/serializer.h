class _enum
{
	int* p;

public:
	template<typename T>
	_enum(T& e)
	{
		_STATIC_ASSERT (sizeof(T) == sizeof(int));
		_ASSERT(sizeof(T) == sizeof(int));
		p = (int*)&e;
	}

	operator int& ()
	{
		return *p;
	}
};

class CSerializer;

class CSerializable
{
public:
	virtual ~CSerializable() {}
	virtual void Serialize(CSerializer& s) { _ASSERT(0); }
};

template<typename T>
class _shared : public CSerializable
{
	shared_ptr<T>& m_sharedptr;

public:
	_shared<T>(shared_ptr<T>& sptr) : m_sharedptr(sptr)
	{
	}

	virtual void Serialize(CSerializer& s) 
	{ 
		if ( s.IsWriting() )
		{
			int nValid = !!m_sharedptr.get();
			s << nValid;
			if (m_sharedptr)
				m_sharedptr->Serialize(s);
		}

		if ( s.IsReading() )
		{
			int nValid = 0;
			s << nValid;
			if ( nValid )
			{
				m_sharedptr.reset(new T());
				m_sharedptr->Serialize(s);
			}
		}
	}
};

class CSerializer
{
	std::ofstream* pOutput;
	std::ifstream* pInput;

public:
	CSerializer(std::ofstream& stream)
	{
		pInput = nullptr;
		pOutput = &stream;
	}

	CSerializer(std::ifstream& stream)
	{
		pInput = &stream;
		pOutput = nullptr;
	}

	bool IsReading()
	{
		return !!pInput;
	}

	bool IsWriting()
	{
		return !!pOutput;
	}

	CSerializer& operator <<(string& str)
	{
		const int nMaxLength = 48;
		char buf[nMaxLength];

		if (pOutput)
		{
			memset(buf, 0, nMaxLength);
			_ASSERT(str.length() < nMaxLength-1);
			memcpy(buf, str.c_str(), str.length());

			pOutput->write(buf, nMaxLength);
		}
		if (pInput)
		{
			pInput->read(buf, nMaxLength);

			buf[nMaxLength-1] = 0;
			str = string(buf, strlen(buf));
		}
		return *this;
	}
	
	CSerializer& operator <<(int& n)
	{
		if (pOutput)
			pOutput->write(reinterpret_cast<const char*>(&n), sizeof(n));
		if (pInput)
			pInput->read(reinterpret_cast<char*>(&n), sizeof(n));
		return *this;
	}

	CSerializer& operator <<(bool& n)
	{
		if (pOutput)
			pOutput->write(reinterpret_cast<const char*>(&n), sizeof(n));
		if (pInput)
			pInput->read(reinterpret_cast<char*>(&n), sizeof(n));
		return *this;
	}

	CSerializer& operator <<(unsigned int& n)
	{
		if (pOutput)
			pOutput->write(reinterpret_cast<const char*>(&n), sizeof(n));
		if (pInput)
			pInput->read(reinterpret_cast<char*>(&n), sizeof(n));
		return *this;
	}

	CSerializer& operator <<(CSerializable& src)
	{
		src.Serialize(*this);
		return *this;
	}
};

