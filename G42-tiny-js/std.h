#ifndef GABO_STD
#define GABO_STD

#ifndef _AFXDLL
#define _AFXDLL
#endif
#include <afxtempl.h>
#include <math.h>

namespace std
{
	class string
	{
	private:
		CString data;

	public:
		typedef size_t size_type;

	public:
		enum {
			npos = -1
		};

	public:
		string() : data("") { }
		string(const char ch) { char buf[2]; buf[0] = ch; buf[1] = '\0'; data = buf; }
		string(const char* str) : data(str) {}
		string(const string& other) : data(other.data) {}

		string( const string& str, size_t pos, size_t n = npos) 
		{
			_ASSERT(0);
		}

		string& operator=(const string& other);

		string& operator+=(const string& other);

		char operator[](int index) const { return data[index]; }

		bool operator==(const string& other) const { return data == other.data; }

		bool operator!=(const string& other) const { return data != other.data; }
		bool operator<(const string& other) const { return data < other.data; }
		bool operator>(const string& other) const { return data > other.data; }
		bool operator<=(const string& other) const { return data <= other.data; }
		bool operator>=(const string& other) const { return data >= other.data; }

		string append(const string& other) { data += other.data; return *this;}
		string append(int nCount, char ch ) { data += CString(ch, nCount); return *this;}

		void clear() { data.Empty(); }

		const char* string::c_str() const  { return (LPCTSTR) data; }

		size_t find(const string& findMe, size_type startIndex = 0) const
		{
			return data.Find( findMe.data, startIndex );
			//return data.find(findMe.c_str(), startIndex);
		}
		size_t rfind( const string& findMe) const
		{
			int nPos = 0, nNewPos = 0;

			do {
				nPos = nNewPos;
				nNewPos = data.Find( findMe.data, nPos );
			} while (nNewPos > 0);
			return nPos;
		}
		char* begin()
		{
			return data.GetBuffer();
		}
		char* end()
		{
			return data.GetBuffer() + data.GetLength();
		}
		int find_first_not_of(char *p)
		{
			const char* pData = c_str();
			int i;
			for (i=0; pData[i]; i++)
			{
				bool match = false;
				for (int j=0; p[j]; j++)
					if (pData[i] == p[j])
					{
						match = true;
						break;
					}
				if (!match)
					break;
			}
			return i;
		}
		int find_last_not_of(char *p)
		{
			const char* pData = c_str();
			int l = data.GetLength();
			int i;
			for (i=l-1; i>0; i++)
			{
				bool match = false;
				for (int j=0; p[j]; j++)
					if (pData[i] == p[j])
					{
						match = true;
						break;
					}
				if (!match)
					break;
			}
			return i;
		}

		size_t length() const { return data.GetLength(); }
		size_t size() const { return data.GetLength(); }

		string substr(int startIndex, int length = npos) const
		{
			//return data.substr(startIndex, length).c_str();
			return string(data.Mid(startIndex, length));

		}
		bool empty() const
		{
			return data.IsEmpty(); 
		}

		char at(int nPos)
		{
			// range check
			return data[nPos];
		}
		void resize(int a)
		{
			_ASSERT(a <= data.GetLength());
			data = data.Left(a);
		}
	};

	const string operator+(const string& me, const string& other);
	const string operator+(const string& me, const char ch);
	const string operator+(const string& me, int n);

	class ostringstream
	{
		friend ostringstream& operator<<(ostringstream& os, const string& s);

	private:
		string buffer;

	public:
		ostringstream() : buffer("") {}

		const char* str() const
		{
			return buffer.c_str();
		}
	};

	ostringstream& operator<<(ostringstream& os, const string& s);
}

namespace std
{
	template <typename T> class vector
	{
	private:
		CArray<T> data;

	public:
		typedef size_t size_type;
		typedef T* iterator;
		typedef const T* const_iterator;
		//typedef T* reverse_iterator;
		struct reverse_iterator 
		{
			typedef T* type;
			type m;

			reverse_iterator(type p)
			{
				m = p;
			}

			type operator ++(int)
			{
				return --m;
			}

			type operator ++()
			{
				return m--;
			}
			type operator +(int n)
			{
				return m-n;
			}
			bool operator != (const reverse_iterator& p)
			{
				return m != p.m;
			}
			T* operator->() const
			{
				return m;
			}

		};

	public:
		vector()
		{
		}

		vector( const vector<T>& other)
		{
			data.Copy( other.data );
		}
		vector(int nLength, T val)
		{
			data.SetSize(nLength);
			for (int i=0; i<nLength; i++) data[i] = val;
		}
		size_type size() const { return data.GetSize(); }
		void clear() { data.RemoveAll(); }
		T& back() { return data[size() - 1]; }
		const T& back() const { return data[data.size() - 1]; }
		void push_back(const T& element) { data.Add(element); }
		void pop_back() { data.RemoveAt(size()-1); }
		T& operator[](size_type index) { return data[index]; }
		const T& operator[](size_type index) const { return data[index]; }
		iterator begin() { return size() > 0 ? &data[0] : NULL; }
		iterator end() { return size() > 0 ? &data[0] + size() : NULL; }
		const_iterator begin() const { return size() > 0 ? &data[0] : NULL; }
		const_iterator end() const { return size() > 0 ? &data[0] + size() : NULL; }

		bool empty() { return data.IsEmpty() ? true : false; }
		T& front() { return data[0]; }
		void swap(vector<T>& sw)
		{
			vector<T> tmp;
			tmp.data.Copy( sw.data );  // TMP <- SW
			sw.data.Copy( data );		// SW <- this
			data.Copy( tmp.data );			// this <- TMP
		}
		reverse_iterator rbegin()
		{
			return size() > 0 ? &data[size()-1] : NULL;
		}
		reverse_iterator rend()
		{
			return size() > 0 ? &data[0] : NULL;
		}
		T* insert( iterator at, const T& itm)
		{
			if (!at)
			{
				data.Add( itm );
				return data.GetData() + data.GetSize()-1;
			}
			else
			{
				int nIndex = at - begin();
				data.InsertAt( nIndex, itm);
				return data.GetData() + nIndex;
			}
			//_ASSERT(0);
			//data.InsertAt( at, *itm );
		}
		void erase(iterator it)
		{
			_ASSERT(it);
			data.RemoveAt( it - begin());
		}
	};

	template <typename T> class set
	{
	public:
		typedef T* iterator;
		void insert(const T&t)
		{
			_ASSERT(0);
		}
		int size()
		{
			_ASSERT(0);
			return 0;
		}
		iterator begin()
		{
			_ASSERT(0);
			return 0;
		}
		iterator end()
		{
			_ASSERT(0);
			return 0;
		}
	};
	
	template <class iterator, class T>
	iterator find (iterator begin, iterator end, const T& x)
	{
		_ASSERT(0);
		return end;
	}

	template <class T> struct sortfunc
	{
		typedef T item;
		static int compare(const void* pa, const void* pb)
		{
			// ascending order
			const T& a = *((T*)pa);
			const T& b = *((T*)pb);
			return a-b;
		}
	};
	
	template <class T>
	void sort( T* begin, T* end)
	{		
		qsort(begin, end-begin, sizeof(int), sortfunc<T>::compare);
	}

	template <class ForwardIterator, class T>
	ForwardIterator lower_bound ( ForwardIterator first, ForwardIterator last, const T& value )
	{
		ForwardIterator it;
		/*iterator_traits<ForwardIterator>::difference_type*/int count, step;
		count = last-first;
		while (count>0)
		{
			it = first; 
			step=count/2; 
			it += step;
			if (*it<value)                   // or: if (comp(*it,value)), for the comp version
			{ 
				first=++it; 
				count-=step+1;  
			} else 
				count=step;
		}
		return first;
	}

	template <class ForwardIterator, class T, class FCompare>
	ForwardIterator lower_bound ( ForwardIterator first, ForwardIterator last, const T& value, FCompare f )
	{
		ForwardIterator it;
		/*iterator_traits<ForwardIterator>::difference_type*/int count, step;
		count = last-first;
		while (count>0)
		{
			it = first; 
			step=count/2; 
			it += step;
			if ( f(*it, value) )                   // or: if (comp(*it,value)), for the comp version
			{ 
				first=++it; 
				count-=step+1;  
			} else 
				count=step;
		}
		return first;
	}

	template<class T>
	class auto_ptr
	{
	public:
		T* p;
		auto_ptr(T* n)
		{
			p = n;
		}
		~auto_ptr()
		{
			if (p)
				delete p;
		}
		T* operator->() const
		{
			return p;
		}
		T* release()
		{
			T* tmp = p;
			p = NULL;
			return tmp;
		}
	};

	template <class iterator, class Func>
	void transform( iterator begin, iterator end, iterator x, Func* f )
	{
		_ASSERT(0);
	}

	/*
	template <class T1, class T2>
	bool typeidequal( T1& p1, T2& p2 )
	{
		bool b1=( p1.findChild("__proto__") == p2.findChild("__proto__") );
		bool b2= typeid(p1) == typeid(p2);
		_ASSERT( b1==b2 );
		return b1;
	}*/

}
#endif