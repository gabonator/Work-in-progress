
class CFrameBuffer {
public:
	enum {
		Width = 320,
		Height = 200
	};

private:

	LPVOID m_pBuffer;
	HDC m_pDC;
	HANDLE m_Old;
	HBITMAP m_ourbitmap;

public:
	CFrameBuffer()
	{
		HDC hDC;
		BITMAPINFO bitmapinfo;
		hDC=CreateCompatibleDC(NULL);
		bitmapinfo.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		bitmapinfo.bmiHeader.biWidth=Width;
		bitmapinfo.bmiHeader.biHeight=-Height; /* top-down */
		bitmapinfo.bmiHeader.biPlanes=1;
		bitmapinfo.bmiHeader.biBitCount=32;
		bitmapinfo.bmiHeader.biCompression=BI_RGB;
		bitmapinfo.bmiHeader.biSizeImage=0;
		bitmapinfo.bmiHeader.biClrUsed=256;
		bitmapinfo.bmiHeader.biClrImportant=256;
		m_pBuffer = NULL;
		m_ourbitmap=CreateDIBSection(hDC,&bitmapinfo,DIB_RGB_COLORS,&m_pBuffer,0,0);
		m_pDC=CreateCompatibleDC(NULL);
		m_Old=SelectObject(m_pDC,m_ourbitmap);
		DeleteDC(hDC);

		FillMemory(m_pBuffer, sizeof(DWORD)*Width*Height, 0xb0);
	}

	LPVOID GetBuffer()
	{
		return m_pBuffer;
	}

	void Blit(HDC hDC)
	{
		BitBlt(hDC,0,0,Width,Height,m_pDC,0,0,SRCCOPY);
	}

	~CFrameBuffer()
	{
		SelectObject(m_pDC,m_Old);
		DeleteDC(m_pDC);
		DeleteObject(m_ourbitmap);
	}
} m_Display;

class CVideo
{
public:
	HWND wnd;

public:
	CVideo()
	{
		wnd = NULL;
	}

	void Init()
	{
		const char* const myclass = "myclass" ;
		WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProcedure,
			0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
			LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW+1),
			0, myclass, LoadIcon(0,IDI_APPLICATION) } ;
		BOOL b = RegisterClassEx(&wndclass);
		_ASSERT(b);
		HWND window = CreateWindowEx( 0, myclass, "Screen",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			CFrameBuffer::Width+GetSystemMetrics(SM_CXFRAME)*2, CFrameBuffer::Height+ GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME)*2, 0, 0, GetModuleHandle(0), 0 ) ;
		_ASSERT(window);
		ShowWindow( window, SW_SHOWDEFAULT ) ;
		wnd = window;
	}

	static long __stdcall WindowProcedure( HWND window, unsigned int msg, WPARAM wp, LPARAM lp )
	{
		HDC hdc;
		PAINTSTRUCT ps;
		switch(msg)
		{
			case WM_DESTROY:
				printf( "\ndestroying window\n" );
				PostQuitMessage(0) ;
				return 0L;

			case WM_PAINT:
				hdc = BeginPaint(window, &ps);
				m_Display.Blit(hdc);
				EndPaint(window, &ps);
				break;
		}
		return DefWindowProc( window, msg, wp, lp ) ;
	}

	void Tick(shared_ptr<CVideoAdapter> pAdapter)
	{
		static LONG last = 0;
		LONG cur = GetTickCount();
		if (last == 0)
			last = cur;
		if ( cur - last < 100 )
			return;

		last = GetTickCount();
		InvalidateRect( wnd, NULL, FALSE );

		if (pAdapter)
		{
			DWORD* pBuffer = (DWORD*)m_Display.GetBuffer();
			for (int y=0; y<200; y++)
				for (int x=0; x<320; x++)
				{
					*pBuffer++ = pAdapter->GetPixel(x,y);
				}
		}

		MSG msg;
		while ( PeekMessage( &msg, wnd, 0, 0, 1 ) ) 
		{
			DispatchMessage(&msg);
		}
	}
};
