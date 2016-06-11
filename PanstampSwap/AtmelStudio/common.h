#include <stdint.h>
#include <stdlib.h>

#define XMEGA 1

typedef uint8_t byte;

#define nullptr 0

#include "hal/hal.h"
#include "utils/serial.h"

#define Assert(expr) { if (!(expr)) { ReportError( __FILE__, __LINE__, __FUNCTION__, #expr); while (1); } }
extern "C" void ReportError(const char* strFile, int nLine, const char* strFunction, const char* strExp);
