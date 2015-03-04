#include "websocket.h"

void Main()
{
	CWebSockets m_ws;
	m_ws.SetListener( Listener );
	m_ws.Setup( 38950 ); // the port we are listening on
	m_ws.Start();

	while ( MainLoopRunning() )
	{
		Sleep(5000);
		m_ws.Send( "Hello!");
	}

	m_ws.Stop();
}

static void Listener( DWORD dwId, CWebSockets::EEvent evt, unsigned char* buf )
{
	if ( !buf )
		return;

	printf("Incommnig data: '%s'\n", buf);
}

bool MainLoopRunning()
{
  return true;
}