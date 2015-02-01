#include "stdafx.h"
#include "bass.h"
#pragma comment(lib, "bass.lib")

#define KEYS 20
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define MAXVOL (0.22*32768)
#define DECAY (MAXVOL/4000)

class CPlayer 
{
	HFX fx[9];
	INPUT_RECORD keyin;
	DWORD r,buflen;
	BASS_INFO info;
	HSTREAM stream; // the stream
	float vol[KEYS];
	float pos[KEYS]; // keys' volume and pos
	static CPlayer* m_this;

	//
	float m_fPosition;
	float m_fTempo;
	bool m_bPlaying;

public:
	CPlayer()
	{
		return; // multi thread crash

		m_this = this;
		ZeroMemory(fx, sizeof(fx));
		ZeroMemory(vol, sizeof(vol));
		ZeroMemory(pos, sizeof(pos));

		m_fPosition = 0.0f;
		m_fTempo = 120.0f;
		m_bPlaying = false;

		// check the correct BASS was loaded
		if (HIWORD(BASS_GetVersion())!=BASSVERSION) 
		{
			printf("An incorrect version of BASS.DLL was loaded");
			return;
		}

		BASS_SetConfig(BASS_CONFIG_VISTA_TRUEPOS,0); // allows lower latency on Vista and newer
		BASS_SetConfig(BASS_CONFIG_UPDATEPERIOD,10); // 10ms update period

		// initialize default output device (and measure latency)
		if (!BASS_Init(-1,44100,BASS_DEVICE_LATENCY,0,NULL))
		{
			printf("Can't initialize device");
			return;
		}			

		BASS_GetInfo(&info);
		BASS_SetConfig(BASS_CONFIG_BUFFER,10+info.minbuf+1); // default buffer size = update period + 'minbuf' + 1ms extra margin
		buflen=BASS_GetConfig(BASS_CONFIG_BUFFER);
		if (!info.freq) info.freq=44100; // if the device's output rate is unknown default to 44100 Hz	
		stream=BASS_StreamCreate(info.freq,2,0,(STREAMPROC*)CPlayer::_WriteStream,0); // create a stream (stereo for effects)
		BASS_ChannelPlay(stream,FALSE); // start it
		//BASS_ChannelSetFX(stream, BASS_FX_DX8_CHORUS, 0);
		//
	}

	~CPlayer()
	{
		BASS_Free();
	}

	int getNote(char ch)
	{
		char* notes  = "c?d?ef?g?a?h"; //"cdefgah";
		char* octave = "111111100000"; //"cdefgah";
		for (int i=0; notes[i]; i++)
			if ( ch == notes[i] )
				return i + (octave[i] - '0')*12;
		return -1;
	}

	void Start()
	{
		m_bPlaying = true;
		m_fPosition = 0;
	}

	void Stop()
	{
		m_bPlaying = false;
	}

	void SetTempo(float fTempo)
	{
		m_fTempo = fTempo;
	}

	float GetTempo()
	{
		return m_fTempo;
	}

	LONG GetPassedTime()
	{
		static DWORD dwLastTime = 0;
		DWORD dwTick = GetTickCount();
		if ( dwLastTime == 0 )
			dwLastTime = dwTick;
		LONG lPassed = (LONG)(dwTick - dwLastTime);
		dwLastTime = dwTick;
		return lPassed;
	}

	void operator()()
	{
		char* melody = "c-g-c-g-c-g-cchag-d-g-d-g-d-ggahc-g-c-g-c-g-ccdef-c-f-c-f-c-ffedc-g-c-g-c-g-cchag-d-g-d-g-d-ggah";
		int nLen = strlen(melody);
		char ch = 0;

		LONG lPassed = GetPassedTime();

		if ( m_bPlaying )
		{
			float fPassedSeconds = lPassed / 1000.0f;
			float fNotesPerSecond = m_fTempo / 60.0f;
			m_fPosition += fPassedSeconds * fNotesPerSecond;

			int nPos = ((int)m_fPosition) % nLen;
			ch = melody[nPos];
		}

		int note1 = getNote(ch);

		// not time-fixed
		for (int key=0;key<KEYS;key++)
		{
			if ( (note1 == key) && vol[key]<MAXVOL) {
				pos[key]=0;
				vol[key]=(float)(MAXVOL+DECAY/2); // start key (setting "vol" slightly higher than MAXVOL to cover any rounding-down)
			} else if (!(note1 == key) && vol[key])
				vol[key]-=(float)DECAY; // trigger key fadeout
		}		
	}

	static DWORD CALLBACK _WriteStream(HSTREAM handle, short *buffer, DWORD length, void *user)
	{
		_ASSERT(m_this);
		if ( m_this )
			return m_this->WriteStream(handle, buffer, length, user);
		return 0;
	}

	float shape(float a)
	{
		float f = sin(a);
		return f > 0 ? 1.0f : -1.0f;
	}

	DWORD CALLBACK WriteStream(HSTREAM handle, short *buffer, DWORD length, void *user)
	{
		int k,c,s;
		float omega;
		memset(buffer,0,length);
		for (k=0;k<KEYS;k++) {
			if (!vol[k]) continue;
			omega=(float)(2*M_PI*pow(2.0,(k+3)/12.0-1.0)*440.0/info.freq);
			for (c=0;c<(int)(length/sizeof(short));c+=2) {
				s=buffer[c]+(int)(shape(pos[k])*vol[k]);
				if (s>32767) s=32767;
				else if (s<-32768) s=-32768;
				buffer[c+1]=buffer[c]=s; // left and right channels are the same
				pos[k]+=omega;
				if (vol[k]<MAXVOL) {
					vol[k]-=(float)DECAY;
					if (vol[k]<=0) { // faded-out
						vol[k]=0;
						break;
					}
				}
			}
			pos[k]=fmod(pos[k],(float)(2*M_PI));
		}
		return length;
	}

};

/*static*/ CPlayer* CPlayer::m_this = NULL;

void PlayerDo();
void PlayerFaster();
void PlayerStart();
void PlayerStop();

CPlayer& GetPlayer()
{
	static CPlayer player;
	return player;
}

void PlayerDo()
{
	GetPlayer()();
}

void PlayerStart()
{
	GetPlayer().SetTempo( 160.0f );
	GetPlayer().Start();
}

void PlayerStop()
{
	GetPlayer().Stop();
}

void PlayerFaster()
{
	GetPlayer().SetTempo( GetPlayer().GetTempo() + 80 );
}
