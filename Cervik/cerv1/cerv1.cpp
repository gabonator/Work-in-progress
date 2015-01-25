// cerv1.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "cerv1.h"
#include "Device.h"

CDevice* CDevice::m_pInstance = NULL;


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

CDevice g_dev;
HWND g_hwnd = NULL;
BOOL g_running = FALSE;
HANDLE g_hDrawThread = NULL;
HANDLE g_hAppThread = NULL;


#include "gfx.h"
#include "tools.h"
#include "cerv.h"
#include "player.h"
#include "game.h"

float CCerv::g_fSpeedMultiply = 1.0f;
CGame game;
bool bFullscreen = false;

void SetFullscreen( HWND hwnd, bool enable )
{
	long style = enable ? WS_POPUP : WS_OVERLAPPEDWINDOW;
	static DWORD dwStyle = 0;
	static HMENU hMenu = NULL;
	static RECT windowRect = {};
	static bool needRect = true;

	if (needRect)
	{
		dwStyle = ::GetWindowLong(hwnd, GWL_STYLE);
		GetWindowRect(hwnd,&windowRect);
		hMenu = ::GetMenu(hwnd);
		needRect = false;
	}

	SetWindowLong(hwnd,GWL_STYLE,style);

	if ( enable )
	{
		::LockWindowUpdate(hwnd); 
		::SetMenu(hwnd, NULL);
		::LockWindowUpdate(NULL); 

		SetWindowPos(hwnd, HWND_TOPMOST,
			0,0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN),
			SWP_SHOWWINDOW);

		g_dev.display.SetDisplay(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}
	else
	{
		::LockWindowUpdate(hwnd); // prevent intermediate redrawing
		::SetMenu(hwnd, hMenu);
		//::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~dwRemove);
		//HDC hDC = ::GetWindowDC(NULL);
		::LockWindowUpdate(NULL); // allow redrawing

		SetWindowPos(hwnd, 0,
			windowRect.left,windowRect.top,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			SWP_SHOWWINDOW);

		g_dev.display.SetDisplay(windowRect.right - windowRect.left-16, windowRect.bottom - windowRect.top-62);

	}

	/*
DWORD dwRemove = WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
// This should be kept for reverse operation
DWORD dwStyle = ::GetWindowLong(m_hWnd, GWL_STYLE);
HMENU hMenu = ::GetMenu(m_hWnd);
WINDOWPLACEMENT wp = {sizeof WINDOWPLACEMENT};
::GetWindowPlacement(m_hWnd, &wp);
 
// Hide the menu bar, change styles and position and redraw
::LockWindowUpdate(m_hWnd); // prevent intermediate redrawing
::SetMenu(m_hWnd, NULL);
::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle & ~dwRemove);
HDC hDC = ::GetWindowDC(NULL);
::LockWindowUpdate(NULL); // allow redrawing
::SetWindowPos(m_hWnd, NULL, 0, 0, GetDeviceCaps(hDC, HORZRES), GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);
	*/
	bFullscreen = enable;
}

void Swap(DWORD& a, DWORD& b)
{
	DWORD c = a;
	a = b;
	b = c;
}

void SwapAvg(DWORD& a, DWORD& b)
{
	DWORD c;
	c = RGB(
			(GetRValue(a)+GetRValue(b))>>1, 
			(GetGValue(a)+GetGValue(b))>>1,
			(GetBValue(a)+GetBValue(b))>>1);
	a = c;
	b = c;
}

void SwapOr(DWORD& a, DWORD& b)
{
	DWORD c = a | b;
	a = c;
	b = c;
}

void Blur1(CFrameBuffer& b, RECT r)
{
	int bx = b.WindowWidth()/2;
	int by = b.WindowHeight()/2;

	DWORD* pBuffer = (DWORD*)b.GetBuffer();
	LONG w = b.Width();

	static int noise[2048] = {0};
	if ( noise[0] == 0 )
	{
		for ( int i=0; i<2048; i++)
		{
			int dx=(rand()&15)-7;
			int dy=(rand()%15)-7;
			noise[i] = dy*w + dx;
		}
		noise[0] |= 1;
	}

	int rw = r.right - r.left;
	int rh = r.bottom - r.top;
	pBuffer += r.left + r.top * w;
	int gap = w-rw;

	int ri = 0;
	DWORD* pBuffer_ = pBuffer;
	for (int y=rh; y; y--)
	{
		for ( int x=rw; x; x--, pBuffer_++)
		{		
			Swap(*pBuffer_, pBuffer_[noise[ri++]]);
			ri &= 2047;
		}
		pBuffer_ += gap;
	}

	pBuffer_ = pBuffer;
	for (int y=rh; y; y--)
	{
		for ( int x=rw; x; x--, pBuffer_++)
		{			
			SwapAvg(*pBuffer_, pBuffer_[noise[ri++]]);
			ri &= 2047;
		}
		pBuffer_ += gap;
	}
}

void Blur(CFrameBuffer& b, RECT r)
{
	int bx = b.WindowWidth()/2;
	int by = b.WindowHeight()/2;

	DWORD* pBuffer = (DWORD*)b.GetBuffer();
	LONG w = b.Width();

	int rw = r.right - r.left;
	int rh = r.bottom - r.top;
	pBuffer += r.left + r.top * w;
	int gap = w-rw;

	int ri = 0;
	DWORD* pBuffer_ = pBuffer;
	for (int y=rh; y; y--)
	{
		for ( int x=rw; x; x--, pBuffer_++)
			*pBuffer_ = pBuffer_[-(x&7) -((y+1)&7)*w];		//SwapOr(*pBuffer_, pBuffer_[-(x&7) -(y&7)*w]);
		pBuffer_ += gap;
	}
}

DWORD WINAPI ThreadProcDraw(HANDLE handle) 
{
	OutputDebugString( _T("Main thread started!\n") );
	while ( !g_hwnd )
		Sleep( 10 );
	
	CFrameBuffer tempBuffer;

	ShowWindow( g_hwnd, SW_SHOW );
	HDC hdc = GetDC( g_hwnd );
	game.Init();

	while (g_running) 
	{
		RECT blurRect1, blurRect2;
		int brLeft, brTop, brRight, brBottom;
		CTools::GetMapArea(brLeft, brTop, brRight, brBottom);

		blurRect1.left = brLeft+1;
		blurRect1.top = brBottom-50;
		blurRect1.right = brRight-1;
		blurRect1.bottom = brBottom-1;

		blurRect2.left = brLeft+1;
		blurRect2.top = brTop+1;
		blurRect2.right = brRight-1;
		blurRect2.bottom = brTop+100;

		game.Do();
		g_dev.Blit( tempBuffer.GetDc() );
		game.Blit( tempBuffer.GetDc() );
		Blur(tempBuffer, blurRect1);
		Blur(tempBuffer, blurRect2);
		tempBuffer.Blit(hdc);
		Sleep( 10 );
	}
	OutputDebugString( _T("Main thread ended!\n") );
	return 0;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CERV1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CERV1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CERV1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CERV1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1024+10, 640, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   g_hwnd = hWnd;

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CHAR:
		if (wParam == 'f')
		{
			SetFullscreen( g_hwnd, !bFullscreen );
			//SetMenu(g_hwnd, bFullscreen ? NULL : AKEINTRESOURCE(IDC_CERV1));
		}
		
		if (wParam == VK_ESCAPE)
		{
			g_running = FALSE;
			Sleep(10);
			OutputDebugString( _T("Quit!\n") );
	
			PostQuitMessage(0);
		}
		break;

	case WM_KEYDOWN:
		g_dev.OnKeyDown( (int)wParam );
		break;

	case WM_KEYUP:
		g_dev.OnKeyUp( (int)wParam );
		break;

	case WM_CREATE:
	{
		SetFullscreen(hWnd, false);
		g_running = TRUE;
		g_hDrawThread = CreateThread( NULL, NULL, &ThreadProcDraw, NULL, NULL, NULL );
		//SetThreadPriority( g_hDrawThread, THREAD_PRIORITY_ABOVE_NORMAL );
		//SetThreadPriority( g_hDrawThread, THREAD_PRIORITY_HIGHEST );
		//hAppThread = CreateThread( NULL, NULL, &ThreadProcApp, NULL, NULL, NULL );
		break;
	}
	case WM_CLOSE:
		g_running = FALSE;
		Sleep(10);
		OutputDebugString( _T("Window destroyed!\n") );
		DestroyWindow(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		g_dev.Blit( hdc );
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
