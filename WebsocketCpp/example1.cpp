#include "websocket.h"

class CExampleMinimal
{
public:
	CWebSockets m_ws;

	CExampleMinimal()
	{
		m_ws.Setup( 38950 ); // the port we are listening on
		m_ws.SetListener( Listener );
		m_ws.Start();
	}
	
	~CExampleMinimal()
	{
		m_ws.Stop();
	}

	static void Listener( DWORD dwId, CWebSockets::EEvent evt, unsigned char* buf )
	{
		if ( !buf )
			return;

		printf("Incommnig data: '%s'\n", buf);
		// process incomming data
	}

	void Send(char* strSend)
	{
		// send to all clients
		m_ws.Send(strSend);
	}
};
