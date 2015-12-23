#include "stdafx.h"

void mainPlaySound(float freq, float vol);

#define KEYS 20
#define MAXVOL (0.22*32768)
#define DECAY (MAXVOL/1000)

class CPlayer 
{
	float vol[KEYS];
	float pos[KEYS];
	static CPlayer* m_this;

	//
	float m_fPosition;
	float m_fTempo;
	float m_fFreqMultiply;
	float m_fFreqMultiplyStep;
	bool m_bPlaying;


public:
	CPlayer()
	{
		m_this = this;
		ZeroMemory(vol, sizeof(vol));
		ZeroMemory(pos, sizeof(pos));

		m_fPosition = 0.0f;
		m_fTempo = 120.0f;
		m_bPlaying = false;
		m_fFreqMultiply = 1.0f;
		m_fFreqMultiplyStep = 0.0f;
	}

	~CPlayer()
	{   
	}

	int getNote(char ch)
	{
		const char* notes  = "c?d?ef?g?a?h"; //"cdefgah";
		const char* octave = "111111100000"; //"cdefgah";
		for (int i=0; notes[i]; i++)
			if ( ch == notes[i] )
				return i + (octave[i] - '0')*12;
		return -1;
	}

	void Start()
	{
		m_bPlaying = true;
		m_fPosition = 0;
		m_fFreqMultiply = 0;
		Resume();
	}
	
	void Pause()
	{
		m_fFreqMultiplyStep = -1.0;
	}

	void Resume()
	{
		m_fFreqMultiplyStep = 1.0;
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
		const char* melody = "c-g-c-g-c-g-cchag-d-g-d-g-d-ggahc-g-c-g-c-g-ccdef-c-f-c-f-c-ffedc-g-c-g-c-g-cchag-d-g-d-g-d-ggah";
		int nLen = strlen(melody);
		char ch = 0;

		LONG lPassed = GetPassedTime();

		if ( m_bPlaying )
		{
			float fPassedSeconds = lPassed / 1000.0f;

			if ( m_fFreqMultiplyStep != 0 )
			{
				m_fFreqMultiply += m_fFreqMultiplyStep * fPassedSeconds / 0.6f; // 0.6s intro
				if ( m_fFreqMultiply > 1.0f )
					m_fFreqMultiply = 1.0f;
				if ( m_fFreqMultiply < 0.0f )
					m_fFreqMultiply = 0.0f;
			}

			float fNotesPerSecond = m_fTempo / 60.0f;

			if ( m_fFreqMultiply == 1.0f )
				m_fPosition += fPassedSeconds * fNotesPerSecond;

			int nPos = ((int)m_fPosition);

			if ( m_fFreqMultiply < 1.0f && melody[nPos%nLen] == '-' )
			{
				m_fPosition++;
				nPos++;
			}

			if ( m_fFreqMultiply < 1.0f || m_fPosition - nPos <= 0.80 ) // 20% legato
			{
				nPos %= nLen;
				ch = melody[nPos];
			}
		}

		int note1 = getNote(ch);

    if ( note1 != -1 )
    {
      float freq = pow(2.0,(note1+3)/12.0-1.0)*440.0;
      mainPlaySound(freq, 0.5f);
    } else
    {
      mainPlaySound(0.0f, 0.0f);
    }
/*
		// not time-fixed
		for (int key=0;key<KEYS;key++)
		{
			if ( (note1 == key) && vol[key]<MAXVOL) {
				pos[key]=0;
				vol[key]=(float)(MAXVOL+DECAY/2); // start key (setting "vol" slightly higher than MAXVOL to cover any rounding-down)
			} else if (!(note1 == key) && vol[key])
				vol[key]-=(float)DECAY; // trigger key fadeout
		}		
*/
	}
/*
	DWORD CALLBACK WriteStream(HSTREAM handle, short *buffer, DWORD length, void *user)
	{
		int k,c,s;
		float omega;
		memset(buffer,0,length);
		for (k=0;k<KEYS;k++) {
			if (!vol[k]) continue;
			omega=(float)(2*M_PI*pow(2.0,(k+3)/12.0-1.0)*440.0/info.freq)*m_fFreqMultiply;
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
*/
};

CPlayer* CPlayer::m_this = NULL;

void PlayerDo();
void PlayerFaster();
void PlayerStart();
void PlayerStop();
void PlayerPause();
void PlayerResume();

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

void PlayerPause()
{
	GetPlayer().Pause();
}

void PlayerResume()
{
	GetPlayer().Resume();
}
