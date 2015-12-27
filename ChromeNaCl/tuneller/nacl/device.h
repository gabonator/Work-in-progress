#pragma once 
//#include <Source/Main/Application.h>

class CFrameBuffer {
private:

	PVOID m_pBuffer;
	LONG m_lWidth;
	LONG m_lHeight;

	LONG m_lWindowWidth;
	LONG m_lWindowHeight;

public:
	CFrameBuffer()
	{
		m_lWidth = 1024;
		m_lHeight = 1024;

		m_lWindowWidth = m_lWidth;
		m_lWindowHeight = m_lHeight;
    // init buf
    m_pBuffer = (DWORD*)malloc(m_lWidth*m_lHeight*4);
	}

	PVOID GetBuffer()
	{
		return m_pBuffer;
	}

	~CFrameBuffer()
	{
    free(m_pBuffer);
	}

	LONG Width()
	{
		return m_lWidth;
	}

	LONG Height()
	{
		return m_lHeight;
	}

	LONG WindowWidth()
	{
		return m_lWindowWidth;
	}

	LONG WindowHeight()
	{
		return m_lWindowHeight;
	}

	void SetDisplay(int w, int h)
	{
		m_lWindowWidth = min(m_lWidth, w);
		m_lWindowHeight = min(m_lHeight, h);
	}

  void Blit()
  {
  }
};

class CDevice {
public:
	static CDevice* m_pInstance;
	CFrameBuffer display;
	int keys;
	int keybuf[1000];
	int mousex, mousey, moused;

public:
	CDevice()
	{
		m_pInstance = this;
		keys = 0;
		memset(keybuf, 0, sizeof(keybuf));
		mousex = -1;
		mousey = -1;
		moused = 0;
	}
	~CDevice()
	{
	}
	void operator ()()
	{
	}
	void Blit( )
	{
		display.Blit();
	}
	void OnKeyDown(int k)
	{
		_ASSERT( k >= 0 && k < 1000 );
		keybuf[k] = 1;
		//keys |= k;
	}
	void OnKeyUp(int k)
	{
		_ASSERT( k >= 0 && k < 1000 );
		keybuf[k] = 0;
		//keys |= k;
	}
	void OnMouseMove(int x, int y)
	{
		mousex = x;
		mousey = y;
	}
	void OnMouseDown()
	{
		moused = 1;
	}
	void OnMouseUp()
	{
		//moused = 0;
	}
	int* GetKeys()
	{
		return keybuf;
	}
};