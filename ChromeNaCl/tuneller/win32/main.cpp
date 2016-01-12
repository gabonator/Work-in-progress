#include "stdafx.h"
#include "main.h"
#include "device.h"

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

// network {{{
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include "easywsclient.h"

using easywsclient::WebSocket;
WebSocket::pointer ws;
#include "../source/net.h"


std::vector<std::pair<std::string, std::string> > g_arrMainArgs;

class CNetWs : public CNet
{
public:
	THandler m_handler;
	PVOID m_handlerData;
	WebSocket::pointer m_ws;
	HANDLE m_hThread;
	bool m_bRunning;

public:
	std::string GetServerUrl()
	{
		return "ws://localhost:1337/tuneller";
		//return "ws://91.230.44.236:1337/test";
	}
	CNetWs()
	{
		g_arrMainArgs.push_back(std::pair<std::string, std::string>("kluc", "hodnota"));
		g_arrMainArgs.push_back(std::pair<std::string, std::string>("A", "B"));
		WSADATA wsaData;

		INT rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (rc) 
		{
			printf("WSAStartup Failed.\n");
			_ASSERT(0);
		}

		m_handler = NULL;
		m_handlerData = NULL;
		m_ws = WebSocket::from_url(GetServerUrl());
		//_ASSERT(m_ws);

		m_bRunning = false;
/*
		if ( m_ws )
		{
			m_hThread = CreateThread( NULL, NULL, &_ThreadProc, this, NULL, NULL );
		}
*/
	}

	~CNetWs()
	{
		if ( m_bRunning )
		{
			m_bRunning = false;
			Sleep(100);
			CloseHandle(m_hThread);
		}
		if ( m_ws )
			m_ws->close();
		WSACleanup();
		delete m_ws;
	}

	static DWORD WINAPI _ThreadProc(HANDLE handle) 
	{	
		CNetWs* pThis = static_cast<CNetWs*>(handle);
		return pThis->ThreadProc();
	}

	DWORD ThreadProc()
	{
		//TODO: Not acceptable!!! Round trip 16ms on localhost!!!
		m_bRunning = true;
		while (m_bRunning)
		{
			m_ws->poll(1);
			m_ws->dispatch([&](const std::string & message) 
			{
				if ( m_handler)
					m_handler(message, m_handlerData);
			});
		}
		return 1;
	}

	virtual void Do()
	{
		if (!m_ws)
			return;

		m_ws->poll();
		m_ws->dispatch([&](const std::string & message) 
		{
			if ( m_handler)
				m_handler(message, m_handlerData);
		});
	}

	virtual void SetReceiveHandler(THandler handler, PVOID handlerData) 
	{
		m_handler = handler;
		m_handlerData = handlerData;
	}

	virtual void Send(std::string msg)
	{
		if (!m_ws)
			return;
		m_ws->send(msg);
	}

	virtual EConnectionState GetState()
	{
		return m_ws ? CNet::Open : CNet::Closed;
	}
};
        
// }}} network

#include "../source/game.h"

CNetWs net;
CGame game;

int nFps = 0;
void DoFrame()
{
	static long lTime = 0;
	static int nFrames = 0;

	long lCurrent = GetTickCount();
	if ( lCurrent >= lTime+1000)
	{
		lTime = lCurrent;
		nFps = nFrames;
		nFrames = 0;

		CHAR msg[128] = {0};
		sprintf(msg, "fps: %d\n", nFps);
		OutputDebugStringA(msg);

	}
	nFrames++;
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

	bool bRunning = true;

	RECT rcClient;
	GetClientRect(g_hwnd, &rcClient);
	g_dev.display.SetDisplay(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

	srand((unsigned int)time(NULL));
	game.SetNetwork(&net);
	game.Init();
	HDC hdc = GetDC( g_hwnd );

	while ( bRunning )
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{	
			if (msg.message == WM_QUIT || 
				msg.message == WM_DESTROY || 
				msg.message == WM_CLOSE)
			{
				bRunning = false;
				break;
			}

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		
		DoFrame();
		net.Do();
		game.Do();
		g_dev.Blit( hdc );
		net.Do();
		Sleep(8);
		net.Do();
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
      CW_USEDEFAULT, 
	  0, 
	  800, 
	  800, 
	  NULL, NULL, hInstance, NULL);

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
		if (wParam == VK_ESCAPE)
		{
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
//		SetFullscreen(hWnd, false);
		//g_running = TRUE;
		//g_hDrawThread = CreateThread( NULL, NULL, &ThreadProcDraw, NULL, NULL, NULL );
		//SetThreadPriority( g_hDrawThread, THREAD_PRIORITY_ABOVE_NORMAL );
		//SetThreadPriority( g_hDrawThread, THREAD_PRIORITY_HIGHEST );
		//hAppThread = CreateThread( NULL, NULL, &ThreadProcApp, NULL, NULL, NULL );
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//g_dev.Blit( hdc );
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
