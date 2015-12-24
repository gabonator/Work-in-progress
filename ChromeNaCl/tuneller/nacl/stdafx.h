#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <cassert>

typedef uint32_t DWORD;
typedef int32_t LONG;
typedef DWORD COLORREF;
typedef void* LPVOID;
//#define NULL 0

const int VK_LEFT = 37;
const int VK_RIGHT = 39;
const int VK_UP = 38;
const int VK_DOWN = 40;
const int VK_F1 = 49;
const int VK_F2 = 50;
const int VK_F3 = 51;
const int VK_F4 = 52;
const int VK_F5 = 53;
const int VK_SPACE = 32;

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))
#define GetRValue(x) ((x)&0xff)
#define GetGValue(x) (((x)>>8)&0xff)
#define GetBValue(x) (((x)>>16)&0xff)

template<class T> const T max(T a, T b)
{
  return a < b ? b : a;
}

template<class T> const T min(T a, T b)
{
  return a > b ? b : a;
}

template<class T> const T abs(T a)
{
  return a >= 0 ? a : -a;
}

#define COUNT(a) (sizeof(a)/sizeof(a[0]))
#define _ASSERT assert


template <class T>
class CArray : public std::vector<T>
{
public:
  void SetSize(int nCount, int nGrow = -1)
  {
//    nGrow > -1 ? 
//      std::vector<T>::resize(nCount, nGrow) :
      std::vector<T>::resize(nCount);
  }
  void Copy(CArray<T>& arrOther)
  {
    std::vector<T>::operator =(arrOther);
  }
  void RemoveAll()
  {
    std::vector<T>::clear();
  } 
  void Append(CArray<T>& arrOther)
  {
    std::vector<T>::insert(std::vector<T>::end(), arrOther.begin(), arrOther.end());
  }
  void Add(const T& element)
  {
    std::vector<T>::push_back(element);
  }
  int GetSize()
  {
    return std::vector<T>::size();
  }
  void RemoveAt(int index)
  {
    std::vector<T>::erase(std::vector<T>::begin() + index);
  }
  T& GetAt(int index)
  { 
    return std::vector<T>::operator[](index);
  }
  void SetAt(int index, const T& element)
  { 
    std::vector<T>::operator[](index) = element;
  }
};

#define GetTickCount() (clock()/64/16)
#define _T
#define ZeroMemory(p, len) std::memset(p, 0, len)

struct RECT { int left; int top; int right; int bottom; };
struct POINT { int x; int y; };
struct SIZE { int cx; int cy; };

typedef const char* LPCTSTR;
typedef LPVOID HDC;
typedef LPVOID HBRUSH;

