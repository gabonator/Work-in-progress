class CStaticAnalysis : public CSerializable
{
public:
	class CPossibleValue : public CSerializable
	{
	public:
		CPossibleValue() : bKnown(false), bAmbiguity(false), bDirty(true), nValue(-1)
		{
		}

		int GetValue()
		{
			if (!bKnown || bAmbiguity || bDirty)
			{
				return -1;
			}
			return nValue;
		}

		void SetValue(int n)
		{
			bKnown = true;
			bDirty = false;
			nValue = n;
			/*
			if (bAmbiguity || (bKnown && bDirty))
				return;

			if (!bKnown)
			{
				nValue = n;
				bKnown = true;
				bDirty = false;
				return;
			}
			
			if ( nValue != n )
			{
				bAmbiguity = true;
			}*/
		}

		void SetDirty()
		{
			bKnown = false;
			bDirty = true;
		}

		virtual void Serialize(CSerializer& s)
		{
			s << bKnown << bAmbiguity << bDirty << nValue;
		}

		bool bKnown;
		bool bAmbiguity;
		bool bDirty;
		int nValue;
	};

public:
	CStaticAnalysis() : m_nVisits(0)
	{
	}

	virtual void Serialize(CSerializer& s)
	{
		s << m_ax << m_es << m_ds << m_direction;
	}

	CPossibleValue m_ax, m_es, m_ds, m_direction, m_stack;
	int m_nVisits;
};
