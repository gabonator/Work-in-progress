namespace CDebugFont {
#include "font.h"
}

//DWORD *pBuf = (DWORD*)g_dev.display.GetBuffer();

#define PIXEL(x, y) ((DWORD*)g_dev.display.GetBuffer())[(y)*g_dev.display.Width()+x]

class CDebug
{
public:
	static void Print(const char* strFormat, ...)
	{
		static char buff[1024];	// TODO: possible buffer overflow

		va_list argList;
		va_start(argList, strFormat);
		vsprintf(buff, strFormat, argList);
		va_end(argList);

		OutputDebugStringA(buff);	
	}

	static void Print(int x, int y, const char* strFormat, ...)
	{
		static char buff[1024];	// TODO: possible buffer overflow

		va_list argList;
		va_start(argList, strFormat);
		vsprintf(buff, strFormat, argList);
		va_end(argList);

		//OutputDebugStringA(buff);
		/*
		x++; y++;
		_Print(x-1, y-1, buff, 0);
		_Print(x-1, y, buff, 0);
		_Print(x, y-1, buff, 0);
		_Print(x, y+1, buff, 0);
		_Print(x+1, y+1, buff, 0);
*/
		_Print(x, y, buff, RGB(0xff, 0xff, 0xff));
	}

	static void Bar(int x1, int y1, int x2, int y2, COLORREF clr)
	{
		clr |= 0xff000000;
		for (int y=y1; y<y2; y++)
			for (int x=x1; x<x2; x++)
			{
				PIXEL(x, y) = clr;
			}
	}

private:
	static void _Print(int x, int y, char* text, COLORREF clr)
	{
	    clr |= 0xff000000;
		while (*text)
			x += _DrawChar(x, y, clr, *text++);
	}

	static int _DrawChar(int x, int y, COLORREF clr, char ch)
	{
		const unsigned char *pFont = CDebugFont::GetFont(ch);

		for (int _y=0; _y<14; _y++)
		{
			unsigned char col = ~*pFont++;
	
			for (int _x=0; _x<8; _x++, col <<= 1)
				if ( col & 128 )
					PIXEL(x+_x, y+_y) = clr; //clrFore;
//				else
//					PIXEL(x+_x, y+_y) &= 0x7f7f7f; //clrFore;
		}

		return 8;
	}

};

#undef PIXEL
