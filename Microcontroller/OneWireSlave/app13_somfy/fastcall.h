#ifndef __FASTCALL__
#define __FASTCALL__

//void User_FastIsr(void);
extern unsigned char nPrevWind;
extern unsigned int nWindCounter;
//extern unsigned char nInhibitOw;

//#define SLOWCALL() { INTE = 0; nInhibitOw = 100; }

#define FASTCALL() { if ( GPIO5 != nPrevWind ) { nPrevWind ^= 1; nWindCounter++; } }
//#define FASTCALL() { User_FastIsr(); }

#endif