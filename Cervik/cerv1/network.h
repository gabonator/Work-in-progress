#include "websocket.h"

class CGameCommon : public CGameCommon_
{
	CWebSockets m_ws;
	CMap<DWORD, DWORD, int, int> m_mapConnections;

	static void Listener( DWORD dwId, CWebSockets::EEvent evt, unsigned char* buf )
	{
		_ASSERT(m_pThis);
		((CGameCommon*)m_pThis)->_Listener(dwId, evt, buf);
	}

	void _Listener( DWORD dwId, CWebSockets::EEvent evt, unsigned char* buf )
	{
		/*
		CString strMsg;
		strMsg.Format( _T("Received %08x : '%S'\n"), dwId, buf );
		OutputDebugString(strMsg);
		*/
		if ( buf && strlen((char*)buf) == 2)
		{
			int *pKeys = g_dev.GetKeys();
			pKeys[buf[0]] = buf[1]-'0';
		}

		if ( evt == CWebSockets::EResponse )
		{
			OutputDebugString( _T("Returning index.html\n") );
			CFile f;
			f.Open(_T("index.html"), CFile::modeRead);
			if ( f.m_hFile == NULL || f.m_hFile == INVALID_HANDLE_VALUE )
				_ASSERT(0);
			else 
			{
				LONG lLength = (LONG)f.GetLength();
				char *pData = new char[lLength+1];
				f.Read(pData, lLength);
				pData[lLength] = 0;
				f.Close();

				CString strData(pData);
				delete pData;

				CString strResponse;
			
				strResponse.Format( 
					_T("HTTP/1.1 200 OK\n")
					_T("Content-Type: text/html\n")
					_T("Content-Length: %d\n")
					_T("Connection: close\n\n%s"),
					strData.GetLength(), strData);

				m_ws.Send( ToAscii(strResponse), dwId );
			}
		}

		if ( evt == CWebSockets::EDisconnect )
		{
			int nPlayerId = 0;
			if ( m_mapConnections.Lookup(dwId, nPlayerId) )
			{
				CPlayer* pPlayer = arrPlayer[nPlayerId];
				pPlayer->m_bRobot = true;
			}
			m_mapConnections.RemoveKey( dwId );
		}

		if ( evt == CWebSockets::EConnect )
		{
			// assign new player
			int nPlayerId = m_mapConnections.GetSize()+1;
			_ASSERT( nPlayerId < arrPlayer.GetSize() );
			m_mapConnections.SetAt(dwId, nPlayerId);
			CPlayer* pPlayer = arrPlayer[nPlayerId];
			ActivateRobot(pPlayer, false);
			//pPlayer->m_bRobot = false;

			CString str;
			str.Format( _T("document.body.style.background = '#%02x%02x%02x'; chLeft = '%c'; chRight = '%c'; chAction = '%c';\n"),
				GetRValue(pPlayer->m_cColor), GetGValue(pPlayer->m_cColor), GetBValue(pPlayer->m_cColor),
				pPlayer->m_nKeyLeft, pPlayer->m_nKeyRight, pPlayer->m_nKeyAction);

			m_ws.Send( ToAscii(str), dwId );
		}
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

public:
	CGameCommon()
	{
		m_ws.Setup( "127.0.0.1", 38950 );
		m_ws.SetListener( Listener );
		m_ws.Start();
	}

	~CGameCommon()
	{
		m_ws.Stop();
	}
};
