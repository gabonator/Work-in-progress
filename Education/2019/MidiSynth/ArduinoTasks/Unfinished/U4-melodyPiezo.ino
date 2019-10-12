void setup()
{
}

int C=0, Cis=1, D=2, Dis=3, E=4, F=5, Fis=6, G=7, Gis=8, A=9, Ais=10, B=11, None=12;
int BPM = 120;

// 120 beatov za minutu, kolko milisekund trva jeden beat?
int Beat = 60000L / BPM;
int Whole = ?;
int Half = ?;
int Quarter = Beat;
int Eigth = ?;
int Sixteenth = ?;
int Thirtysecond = ?;
int WholeDot = ?;
int HalfDot = ?;
int QuarterDot = ?;
int EigthDot = ?;
int SixteenthDot = ?;
int ThirtysecondDot = ?;

int Frequency(int note)
{
  return ?;
}

void Play(int note, int octave, int length)
{
  int pitch = ?;

  tone(12, Frequency(pitch));
  delay(length);
  noTone(12);
  delay(10);
}

void loop() 
{  
  Play(G, 2, Quarter);
  Play(Ais, 2, EigthDot);
  Play(G, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(G, 2, Sixteenth);
  Play(C, 3, Eigth);
  Play(G, 2, Eigth);
  Play(F, 2, Eigth);
  Play(G, 2, Quarter);
  Play(D, 3, EigthDot);
  Play(G, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(G, 2, Sixteenth);
  Play(Dis, 3, Eigth);
  Play(D, 3, Eigth);
  Play(Ais, 2, Eigth);
  Play(G, 2, Eigth);
  Play(D, 3, Eigth);
  Play(G, 3, Eigth);
  Play(G, 2, Sixteenth);
  Play(F, 2, Sixteenth);
  Play(None, 0, Sixteenth);
  Play(F, 2, Sixteenth);
  Play(D, 2, Eigth);
  Play(A, 2, Eigth);
  Play(G, 2, Half);
  delay(5000);
}