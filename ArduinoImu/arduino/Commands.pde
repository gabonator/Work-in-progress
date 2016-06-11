
#define IsCommand( cmd, find, callback ) \
	if ( strncmp( cmd, find, strlen(find) ) == 0 ) \
	{	\
		cmd += strlen(find)+1; \
		cmd ## callback( &cmd );	\
		return; \
	}

#define GetInteger( var ) \
	_GetInteger( cmd, &var )

#define COMMAND( name ) \
		void cmd ## name(char **cmd)
	
#define OutputString(str) \
		Serial.print(str)

int g_nLastAddr = 0;

void OutputNumHex(int val) 
{
	if ( val > 0xff || val < 0 )
	{
		OutputString("OnError('Value outside range');\r\n");
	}
	char out[5] = "0x00";
	const char hex[] = "0123456789abcdef";
	out[2] = hex[val >> 4];
	out[3] = hex[val & 0xf];
	OutputString(out);
}


int getHex(char c)
{
//	if ( c >= '0' && c <= '9' ) 
//		return c - '0';
	if ( c >= 'a' && c <= 'f' ) 
		return c - 'a' + 10;
	if ( c >= 'A' && c <= 'F' ) 
		return c - 'A' + 10;
	return c & 0x0f;
}

int isHex(char c)
{
	if ( c >= 'a' && c <= 'f' ) 
		return 1;
	if ( c >= 'A' && c <= 'F' ) 
		return 1;
	if ( c >= '0' && c <= '9' ) 
		return 1;
	return 0;
}

int isDec(char c)
{
	if ( c >= '0' && c <= '9' ) 
		return 1;
	return 0;
}

int _GetInteger( char **buf, int* out )
{
	int nVal = 0;
	while ( **buf == ' ' )
		(*buf)++;
	if ( **buf == ')' )
		return 0;

  if ( (*buf)[0] == '0' && (*buf)[1] == 'x' )
	{
		(*buf) += 2;
		// hex
		while ( isHex( **buf ) )
		{
			nVal <<= 4;
			nVal |= getHex( **buf );
			(*buf)++;
		}
	} else
	{
		// dec
		while ( isDec( **buf ) )
		{
			nVal *= 10;
			nVal += getHex( **buf );
			(*buf)++;
		}
	}

	while ( **buf == ' ' )
		(*buf)++;

	if ( **buf == ',' )
		(*buf)++;
	*out = nVal;
	return 1;
}

COMMAND( WireSetAddress )
{
  GetInteger( g_nLastAddr );
}

COMMAND( WireBeginTransmission )
{
	int nAddr;
  GetInteger( nAddr );
  g_nLastAddr = nAddr;
  Wire.beginTransmission(nAddr);
}

COMMAND( WireEndTransmission )
{
  Wire.endTransmission();
}

COMMAND( WireWrite )
{
  int nData;
	Wire.beginTransmission( g_nLastAddr );
  while ( GetInteger( nData ) )
    Wire.write( (byte) nData );
	Wire.endTransmission();
}

COMMAND( WireRead )
{
  int nCount;
	byte buf[256];
  GetInteger( nCount );
	if ( nCount >= 256 )
  {
    OutputString("Error('requested buffer too long');\r\n");
		return;
  }

	Wire.beginTransmission( g_nLastAddr );
	Wire.requestFrom( g_nLastAddr, nCount );
  for ( int i = 0; i < nCount; i ++ )
		buf[i] = Wire.read();
	Wire.endTransmission();

  OutputString("Wire.onData(");
  for ( int i = 0; i < nCount; i ++ )
	{
		if (i > 0)
			OutputString(", ");
		OutputNumHex( buf[i] );
	}
  OutputString(");\r\n");
}

COMMAND( Delay )
{
  int nDelay;
  GetInteger( nDelay );
	delay( nDelay );
}

COMMAND( About )
{
	OutputString("Arduino interpreter 1.0\r\n");
}

void ProcessCommand(char* cmd)
{
/*
	IsCommand( cmd, "Wire.beginTransmission", WireBeginTransmission);
	IsCommand( cmd, "Wire.write", WireWrite);
	IsCommand( cmd, "Wire.read", WireRead);
	IsCommand( cmd, "Wire.endTransmission", WireEndTransmission);
*/
	IsCommand( cmd, "Wire.select", WireSetAddress);
	IsCommand( cmd, "Wire.read", WireRead);
	IsCommand( cmd, "Wire.write", WireWrite);
//	IsCommand( cmd, "Wire.transfer", WireTrans);

	IsCommand( cmd, "Delay", Delay);
	IsCommand( cmd, "About", About);
	OutputString("!Unknown command [");
	OutputString(cmd);
	OutputString("]\r\n");
}

// > Wire.beginTransmission(0x12);
// > Wire.write(0x11, 0x12, 0x22, 0x12);
// > Wire.read(3);
// < Wire.OnData(0x90, 0x12, 0x11);
// > Wire.endTransmission();

