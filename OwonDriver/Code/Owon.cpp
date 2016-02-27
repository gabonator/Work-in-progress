#define _CRT_SECURE_NO_WARNINGS
#define _AFXDLL
#include <afxtempl.h>
#include <windows.h>

#include "lib/libusb.h"
#pragma comment(lib, "lib/libusb.lib")

void Message( char *msg )
{
	printf(msg);
	printf("\n");
}

void Message( char *msg, int n )
{
	printf(msg, n);
	printf("\n");
}

void Message( char *msg, int n, int i )
{
	printf(msg, n, i);
	printf("\n");
}

void Message( char *msg, int n, char *str )
{
	printf(msg, n, str);
	printf("\n");
}

class CUSB {
public:
	enum {
		DefaultTimeout = 500 // 500 ms
	};

protected:
	HANDLE m_hDevice;

public:
	CUSB()
	{
		m_hDevice = NULL;
	}

	HANDLE Find()
	{
		usb_init();

		int nBuses = usb_find_busses();
		int nDevs = usb_find_devices();
		struct usb_bus* pBus = usb_busses;
		struct usb_dev_handle* hDevice = NULL;

		for (; pBus; pBus = pBus->next) 
		{
			struct usb_device *pDev;
			for ( pDev = pBus->devices; pDev; pDev = pDev->next )
				if ( MatchDevice( &pDev->descriptor ) )
					return (HANDLE)pDev;
		}
		return (NULL);		// No Owon found

	}

	BOOL Open( HANDLE hDev )
	{
		//usb_dev_handle *usb_open(struct usb_device *dev);
		m_hDevice = (HANDLE) usb_open( (struct usb_device*) hDev );
		return m_hDevice ? TRUE : FALSE;
	}

	virtual BOOL MatchDevice( usb_device_descriptor* pDesc ) = 0;

	BOOL SetConfiguration( int nConf )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_set_configuration( (usb_dev_handle *)m_hDevice, nConf );
		if (nResult < 0) 
			Message("CUSB::Error (%d) %s ", -nResult, strerror(-nResult));
		_ASSERT( nResult >= 0);
		return nResult >= 0;
	}

	BOOL ClaimInterface( int nInterface )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_claim_interface( (usb_dev_handle *)m_hDevice, nInterface );
		if (nResult < 0) 
			Message("CUSB::Error (%d) %s ", -nResult, strerror(-nResult));
		_ASSERT( nResult >= 0);
		return nResult >= 0;
	}

	BOOL ReleaseInterface( int nInterface )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_release_interface( (usb_dev_handle *)m_hDevice, nInterface );
		if (nResult < 0) 
			Message("CUSB::Error (%d) %s ", -nResult, strerror(-nResult));
		_ASSERT( nResult >= 0);
		return nResult >= 0;
	}

	BOOL ClearHalt( int nEndpoint )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_clear_halt( (usb_dev_handle *)m_hDevice, nEndpoint );
		if (nResult < 0) 
			Message("CUSB::Error (%d) %s ", -nResult, strerror(-nResult));
		_ASSERT( nResult >= 0);
		return nResult >= 0;
	}

	BOOL GetDescriptor( unsigned char bType, unsigned char bIndex, LPVOID pBuffer, int nSize )
	{
		_ASSERT( m_hDevice );
	  	int nResult = usb_get_descriptor( (usb_dev_handle *)m_hDevice, 
			bType, bIndex, pBuffer, nSize);
		_ASSERT( nResult == nSize );
		return nResult == nSize;
	}

	BOOL Write( int nEndpoint, LPVOID pBuffer, int nSize )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_bulk_write( (usb_dev_handle *)m_hDevice, nEndpoint, 
			(CHAR*)pBuffer, nSize, DefaultTimeout );
		_ASSERT ( nResult == nSize );
		return ( nResult == nSize );
	}

	BOOL Read( int nEndpoint, LPVOID pBuffer, int nSize )
	{
		_ASSERT( m_hDevice );
		int nResult = usb_bulk_read( (usb_dev_handle *)m_hDevice, nEndpoint, 
			(CHAR*)pBuffer, nSize, DefaultTimeout );

		if (nResult < 0) 
			Message("CUSB::Error (%d) %s ", -nResult, strerror(-nResult));

		_ASSERT ( nResult == nSize );
		return ( nResult == nSize );
	}

	void Reset()
	{
		_ASSERT( m_hDevice );
		usb_reset( (usb_dev_handle *)m_hDevice );
	}

	void Close()
	{
		_ASSERT( m_hDevice );
		usb_close( (usb_dev_handle *)m_hDevice );
		m_hDevice = NULL;
	}
};

class COwonUSB : CUSB {
public:
	enum {
		WriteEndpoint = 0x03,
		ReadEndpoint = 0x81,
		DefaultConfiguration = 0x01,
		DefaultInterface = 0x00,
		DtDevice = USB_DT_DEVICE,
		UsbVendor = 0x5345,
		UsbProduct = 0x1234
	};

private:
	LPVOID m_pData;
	LONG m_lDataLength;

public:
	COwonUSB() : CUSB()
	{
		m_pData = NULL;
	}

	~COwonUSB()
	{
		Free();
	}

	void Free()
	{
		if (m_pData)
			free (m_pData);
		m_pData = NULL;
	}

	virtual BOOL MatchDevice( usb_device_descriptor* pDesc )
	{
		_ASSERT( pDesc );
		if ( pDesc->idVendor == UsbVendor && 
			 pDesc->idProduct == UsbProduct )
		{
			return TRUE;
		}

		return FALSE;
	}

	BOOL Open()
	{
		HANDLE hDevice = CUSB::Find();
		if ( !hDevice )
			return FALSE;

		return CUSB::Open(hDevice);
	}

	BOOL Init()
	{
		CHAR pDescriptor[0x12];

		if ( !CUSB::SetConfiguration( DefaultConfiguration ) )
			return FALSE;

		if ( !CUSB::ClaimInterface( DefaultInterface ) )
			return FALSE;

		if ( !CUSB::ClearHalt( ReadEndpoint ) )
			return FALSE;

		if ( !CUSB::GetDescriptor( DtDevice, 0x00, pDescriptor, sizeof(pDescriptor) ) )
			return FALSE;
		return TRUE;
	}

	BOOL Write( char *buf )
	{
		return CUSB::Write( WriteEndpoint, buf, (int)strlen(buf) );
	}
	
	BOOL Read( LPVOID buf, int nSize )
	{
		return CUSB::Read( ReadEndpoint, buf, nSize );
	}

	BOOL Download()
	{
		struct {
			DWORD dwBufferSize;
			DWORD dwUnknown1;
			DWORD dwUnknown2;
		} sReadBlock;

		_ASSERT( m_pData == NULL );

		ClearHalt( WriteEndpoint );
		if ( !Write( "START" ) )
		{
			Message("send StartDataCmd failed");
			return FALSE;
		}

		ClearHalt( ReadEndpoint );
		if ( !Read( &sReadBlock, sizeof(sReadBlock) ) )
		{
			Message("read after START failed");
			return FALSE;
		}

		Message( "Block of size %d found", sReadBlock.dwBufferSize );
		Message( "unk1 = %x, unk2 = %x", sReadBlock.dwUnknown1, sReadBlock.dwUnknown2 );

		m_pData = malloc( sReadBlock.dwBufferSize );
		if ( !m_pData )
		{
			Message( "Allocation failed" );
			return FALSE;
		}

		if ( !Read( m_pData, sReadBlock.dwBufferSize ) )
		{
			Message( "Reading of %d bytes failed", sReadBlock.dwBufferSize );
			return FALSE;
		}

		m_lDataLength = sReadBlock.dwBufferSize;
		return TRUE;
	}

	void Close()
	{
		//CUSB::Reset();
		CUSB::Close();
	}

	void Reset()
	{
		CUSB::Reset();
	}

	void Release()
	{
		CUSB::ReleaseInterface( DefaultInterface );
	}

public:
	BYTE* GetData()
	{
		return (BYTE*)m_pData;
	}

	LONG GetLength()
	{
		return m_lDataLength;
	}
};

void writeVectorData(char *buf, int count);

int main(int argc, char *argv[]) 
{
	// graph generator test from binary image
	FILE* f = fopen("C:\\Data\\Devel\\Github\\Work-in-progress\\OwonDriver\\Owon\\Owon\\output_2v.bin", "r");
	fseek(f, 0, SEEK_END);
	LONG size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buffer = new char[size];
	fread(buffer, 1, size, f);
	fclose(f);
	writeVectorData(buffer, size);
	delete buffer;
	return 0;

	COwonUSB Owon;

	if ( !Owon.Open() )
	{
		Message("Owon device not found");
		return 1;
	}

	//while (!kbhit())
	{
		{
			Message("Port opened");
			BOOL bInit = Owon.Init();
			Message(bInit ? "Init succeed" : "Init failed");
			_ASSERT( bInit );
			if ( bInit )
			{
				BOOL bDown = Owon.Download();
				_ASSERT(bDown);
				if (!bDown)
				{
					Owon.Reset();
					Owon.Close();
					Owon.Open();
					Owon.Init();
				}
				
				if (!bDown)
					bDown = Owon.Download();

				if (bDown)
					writeVectorData( (char*)Owon.GetData(), Owon.GetLength());
			} else
			{
				//Owon.Reset();
			}
			Message("Closing...");
			Owon.Free();
			Owon.Release();
		} 
		Message("");
		Sleep(1000);
	}
	Owon.Close();

//	Message("Press any key");
//	getchar();
}

void writeVectorData(char *buf, int count) 
{
	if ( buf[0] != 'S' || buf[1] != 'P' || buf[2] != 'B' || buf[3] != 'V' )
	{
		_ASSERT(!!!"Not a PDS5022S oscilloscope");
		return;
	}

#pragma pack(push)
#pragma pack(1)
	struct TVectogramBinaryHeader 
	{
		CHAR strChannelName[3];
		LONG blockLength;
		LONG sampleCount1;
		LONG sampleCount2;
		LONG unk3;
		LONG timebase;
		LONG unk4;
		LONG vertSensCode;
		LONG unk5;
		LONG unk6;
		LONG unk7;
		LONG unk8;
		LONG unk9;
	};
#pragma pack(pop)

	struct TVectogram
	{
		CHAR strChannelName[4];
		INT nSamples;
		FLOAT fTimebase;
		FLOAT fVertical;

		INT nDataOffset;
		//
		char* strColor;
		char* strTime;
		char* strAmplitude;
	};

	
#define NS *1E-9
#define US *1E-6
#define MS *1E-3
#define S
#define mV *1E-3

	static double arrSensitivity[] = {
		0, 5 mV, 10 mV, 20 mV, 50 mV, 100 mV, 200 mV, 500 mV, 1000 mV, 5000 mV
	};

	static double arrTimebase[] = {
		              5 NS, 10 NS, 25 NS, 50 NS, 100 NS, 250 NS, 500 NS,  // 00..06
		1 US, 2.5 US, 5 US, 10 US, 25 US, 50 US, 100 US, 250 US, 500 US,  // 07..0f
		1 MS, 2.5 MS, 5 MS, 10 MS, 25 MS, 50 MS, 100 MS, 250 MS, 500 MS,  // 10..18
		1  S, 2.5  S, 5  S, 10  S, 25 S,  50  S, 100  S};
	
	static char* arrSensitivityName[] = {
		"0", "5 mV", "10 mV", "20 mV", "50 mV", "100 mV", "200 mV", "500 mV", "1000 mV", "5000 mV"
	};

	static char* arrTimebaseName[] = {
		                  "5 nS", "10 nS", "25 nS", "50 nS", "100 nS", "250 nS", "500 nS",  // 00..06
		"1 uS", "2.5 uS", "5 uS", "10 uS", "25 uS", "50 uS", "100 uS", "250 uS", "500 uS",  // 07..0f
		"1 mS", "2.5 mS", "5 mS", "10 mS", "25 mS", "50 mS", "100 mS", "250 mS", "500 mS",  // 10..18
		"1  S", "2.5 S",  "5 S",  "10 S",  "25 S",  "50 S",  "100 S"};

#undef NS
#undef US
#undef MS
#undef S
#undef mV

	CArray<TVectogram> arrVectograms;

	int nNextHeaderOffset = 10;
	while ( nNextHeaderOffset < count )
	{
		TVectogramBinaryHeader header;
		memcpy(&header, buf+nNextHeaderOffset, sizeof(TVectogramBinaryHeader));

		_ASSERT( header.sampleCount1 == header.sampleCount2 );
		_ASSERT( header.blockLength >= header.sampleCount1*2 );

		TVectogram vectogram;
		memcpy(vectogram.strChannelName, header.strChannelName, 4);
		vectogram.strChannelName[3] = 0;

		vectogram.nSamples = header.sampleCount1;

		vectogram.strColor = "red";
		switch (vectogram.strChannelName[2])
		{
		case '1': vectogram.strColor = "red"; break;
		case '2': vectogram.strColor = "yellow"; break;
		case 'A': vectogram.strColor = "cyan"; break;
		case 'B': vectogram.strColor = "green"; break;
		case 'C': vectogram.strColor = "purble"; break;
		case 'D': vectogram.strColor = "blue"; break;
		}

		_ASSERT(header.timebase >= 0 && header.timebase < sizeof(arrTimebase)/sizeof(arrTimebase[0]));
		vectogram.fTimebase = (float)arrTimebase[header.timebase];
		vectogram.strTime = arrTimebaseName[header.timebase];

		_ASSERT(header.vertSensCode >= 0 && header.vertSensCode < sizeof(arrSensitivity)/sizeof(arrSensitivity[0]));
		vectogram.fVertical = (float)arrSensitivity[header.vertSensCode];
		vectogram.strAmplitude = arrSensitivityName[header.vertSensCode];

		vectogram.nDataOffset = nNextHeaderOffset + sizeof(TVectogramBinaryHeader);
		arrVectograms.Add(vectogram);

		nNextHeaderOffset += header.blockLength + 3;
	}

	int i,j;

	FILE *fpout;
	const char svgheaderwhite[] = 
"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">\n"
"<svg width=\"640\" height=\"480\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" onload=\"init(evt)\" onmousemove=\"msMove(evt)\">\n"
"<g transform=\"translate(0,0) scale(1,1)\" stroke-width=\"1\">\n"
"  <path stroke=\"black\" fill=\"none\" stroke-width=\"2\" d=\"M0,0 H640 V480 H0 V0\"/>\n"
"  <g transform=\"translate(320,240) scale(64,60)\">\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,-3 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,-2 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,-1 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.02\" d=\"M-5,0 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,1 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,2 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-5,3 H5\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-4,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-3,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-2,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M-1,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.02\" d=\"M0,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M1,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M2,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M3,-4 V4\"/>\n"
"    <path stroke=\"black\" stroke-width=\"0.01\" d=\"M4,-4 V4\"/>\n"
"  </g>\n"
"  <text font-family=\"Arial\" font-weight=\"bold\" x=\"2\" y=\"22\" fill=\"black\" font-size=\"20\" text-anchor=\"start\">%s</text>\n";

	const char svgheaderblack[] = 
"<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">\n"
"<svg width=\"640\" height=\"480\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" onload=\"init(evt)\" onmousemove=\"msMove(evt)\">\n"
"<g transform=\"translate(0,0) scale(1,1)\" stroke-width=\"1\">\n"
"  <path stroke=\"white\" fill=\"black\" stroke-width=\"2\" d=\"M0,0 H640 V480 H0 V0\"/>\n"
"  <g transform=\"translate(320,240) scale(64,60)\">\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,-3 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,-2 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,-1 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.02\" d=\"M-5,0 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,1 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,2 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-5,3 H5\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-4,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-3,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-2,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M-1,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.02\" d=\"M0,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M1,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M2,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M3,-4 V4\"/>\n"
"    <path stroke=\"white\" stroke-width=\"0.01\" d=\"M4,-4 V4\"/>\n"
"  </g>\n"
"  <text font-family=\"Arial\" font-weight=\"bold\" x=\"2\" y=\"22\" fill=\"white\" font-size=\"20\" text-anchor=\"start\">%s</text>\n";

	const char scriptheader[] = 
"<script type=\"text/ecmascript\"><![CDATA[\n"
"function init(evt) { if ( window.svgDocument == null ) svgDocument = evt.target.ownerDocument; }\n"
"function fmtT(val, div) {\n"
"  if (div > 100) return Math.floor((val-320)*div/64) + \" ms\";\n"
"  if (div > 0.025) return Math.floor((val-320)*div*1000/64)/1000 + \" ms\";\n" 
"  return Math.floor((val-320)*div*1000*1000/64)/1000 + \" us\";\n"
"}\n"
"function fmtU(val, div, shift) { shift *= -60/25; return Math.floor((240-val+shift)*div/60) + \" mV\"; }\n"
"function msMove (evt)\n"
"{\n"
"	var x = evt.clientX;\n"
"	var y = evt.clientY;\n"
"	if (x < 0 || y < 0 || x >= 640 || y >= 480)\n"
"		return;\n";

	const char scriptfooter[] = 
"}\n"
"]]></script>\n";
		
	const char svgfooter[] = "</g></svg>\n";
	char* channelcolor = NULL;
	char* extraInfo = NULL;

	if ((fpout = fopen("C:\\Data\\Devel\\Github\\Work-in-progress\\OwonDriver\\Owon\\Owon\\__out.svg","w")) == NULL) {
	  printf("..Failed to open file !\n");
	  return;
	}

    fprintf(fpout, svgheaderblack, "OWON PDS 5022S");

	for (i=0; i<arrVectograms.GetSize(); i++)
	{
		int nBaseOffset = arrVectograms[i].nDataOffset;
		int nCount = arrVectograms[i].nSamples;

		fprintf( fpout, "<path stroke=\"%s\" transform=\"translate(0,420) scale(%g,%g)\" fill=\"none\" stroke-width=\"3\" d=\"", 
			"red", 640.0 / nCount, -7.0f/3.0f );

		for(j=0;j < (int) nCount;j++) 
		{
			signed short nSample = ((unsigned char*)buf)[nBaseOffset+j*2+1]*256 + ((unsigned char*)buf)[nBaseOffset+j*2];
			nSample = 0;
			if (j==0)
				fprintf(fpout, "M%d,%d ", j, nSample);
			else
				fprintf(fpout, "L%d,%d ", j, nSample);
			
			if (j%100==49)
				fprintf(fpout, "\n");
		}
		fprintf(fpout, "\"/>\n");

		fprintf(fpout, "<text id=\"%s\" font-family=\"Arial\" x=\"638\" y=\"%d\" fill=\"%s\" font-size=\"20\" text-anchor=\"end\">%s: %s/div %s/div</text>",
			arrVectograms[i].strChannelName, 478 - (arrVectograms.GetSize() - i - 1)*30, arrVectograms[i].strColor, 
			arrVectograms[i].strChannelName, arrVectograms[i].strAmplitude, arrVectograms[i].strTime );
	}

	fprintf(fpout, scriptheader);
	for (i=0; i<arrVectograms.GetSize(); i++)
	{
		fprintf(fpout, "	svgDocument.getElementById(\"%s\").firstChild.data = fmtU(y, %.2f, %d) + \" \" + fmtT(x, %.2f);\n",
			arrVectograms[i].strChannelName, arrVectograms[i].fVertical*1000.0f, 0, arrVectograms[i].fTimebase * 1000.0f);
	}
	fprintf(fpout, scriptfooter);

	fprintf(fpout, svgfooter);

	printf("..Successfully written trace data to \'%s\'!\n", "x");
	if(!fclose(fpout))
		printf("..Successfully closed text file \'%s\'!\n", "x");
    
}

