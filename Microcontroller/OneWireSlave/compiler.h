#include <pic.h>
#include "delay.h"
#define __delay_us(x) DelayUs(x)
#define __delay_ms(x) isrDelayMs(x)
#define X__delay_ms(x) DelayMs(x)
#define OPTIMIZE(x)
#define DBG(a, b) { GPIO5 = a; GPIO4 = b; }
