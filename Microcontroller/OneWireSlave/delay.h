#ifndef __DELAY_H__
#define __DELAY_H__

// @ 8MHz
#define	DelayUs(x)       \
  {                      \
    unsigned char _dcnt; \
    _dcnt = (x*5/8)|1;   \
    while(--_dcnt)       \
      continue;          \
  }

void DelayMs(unsigned char);
void isrDelayMs(unsigned char);

#endif