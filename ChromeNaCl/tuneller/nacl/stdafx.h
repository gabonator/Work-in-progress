#pragma once
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <cassert>
#include <sys/time.h>

typedef uint32_t DWORD;
typedef int32_t LONG;
typedef DWORD COLORREF;
typedef void* PVOID;
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

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16)|0xff000000)
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
#define _ASSERT_VALID(exp) if (!(exp)) {assert(!!!#exp);}

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

#define _T
#define ZeroMemory(p, len) std::memset(p, 0, len)

struct RECT { int left; int top; int right; int bottom; };
struct POINT { int x; int y; };
struct SIZE { int cx; int cy; };

unsigned long GetTickCount()
{
  // pp::Module::Get()->core()->GetTimeTicks()
  static unsigned long lFirst = 0;

  struct timeval tv;
  if(gettimeofday(&tv, NULL) != 0)
    return 0;

  unsigned long lMs = tv.tv_usec / 1000;
  lMs += tv.tv_sec * 1000;
  if (lFirst == 0)
    lFirst = lMs;
  lMs -= lFirst;

  return lMs;
}