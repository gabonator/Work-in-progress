// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#define _AFXDLL

//#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <crtdbg.h>
#include <afxtempl.h>
#include <math.h>
#include <list>

#define COUNT(a) (sizeof(a)/sizeof(a[0]))
typedef void* PVOID;
#define _ASSERT_VALID(exp) {if(!(exp)) {_ASSERT(!!!#exp);}};


// TODO: reference additional headers your program requires here
