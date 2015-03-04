#include "websocket.h"

class CExample 
{
	static CExample m_Instance;
	CWebSockets m_ws;

public:
	CExample()
	{
		m_ws.Setup( 38950 ); // the port we are listening on
		m_ws.SetListener( Listener );
		m_ws.Start();
	}

	~CExample()
	{
		m_ws.Stop();
	}

	static void Listener( DWORD dwId, CWebSockets::EEvent evt, unsigned char* buf )
	{
		switch ( evt )
		{
		case CWebSockets::EConnect:
			// client dwId just connected
			break;
		case CWebSockets::EDisconnect:
			// client dwId was disconnected
			break;
		case CWebSockets::EResponse:
			// handshaking failed, probably just web browser GET request
			m_Instance.ReplyHtml( _T("<html>Hello!</html>"), dwId );
			break;
		case CWebSockets::EReceive:
			// client dwId is sending data (buf is null terminated string)
			m_Instance.Receive(CString(buf));
		default:
			break;
		}
	}

	void Receive(CString strData)
	{
		// handle received data
	}

	void Send(CString strData)
	{
		// send to all clients
		m_ws.Send( ToAscii(strData) );
	}

private:
	void ReplyHtml(CString strData, DWORD dwId)
	{
		CString strResponse;
			
		strResponse.Format( 
			_T("HTTP/1.1 200 OK\n")
			_T("Content-Type: text/html\n")
			_T("Content-Length: %d\n")
			_T("Connection: close\n\n%s"),
			strData.GetLength(), strData);

		m_ws.Send( ToAscii(strResponse), dwId );
	}

	char* ToAscii(CString& str)
	{
		static char strAscii[4096];
		int i;
		for ( i=0; str[i]; i++ )
			strAscii[i] = (char)str[i];
		strAscii[i] = 0;
		return strAscii;
	}
};

CExample CExample::m_Instance;
