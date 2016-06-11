#pragma once

// files in this folder are migrated from ASF, compiler.h builds environment for these files

#include <avr/io.h>
#include <avr/builtins.h>
#include <avr/interrupt.h>
#include <stddef.h>

#define XMEGA_AU 1

#ifdef __GNUC__
#  define barrier()        asm volatile("" ::: "memory")
#else
#  define barrier()        asm ("")
#endif

#define  MSB(u16)          (((uint8_t* )&u16)[1])
#define  LSB(u16)          (((uint8_t* )&u16)[0])

typedef uint16_t   le16_t;
typedef uint16_t   be16_t;
typedef uint32_t   le32_t;
typedef uint32_t   be32_t;
typedef uint16_t   iram_size_t;


#ifndef __cplusplus
typedef uint8_t bool;
#endif
#define false 0
#define true 1

#define XMEGA 1

#define COMPILER_ALIGNED(a)    __attribute__((__aligned__(a)))

#define COMPILER_WORD_ALIGNED    __attribute__((__aligned__(2)))
#include "compiler/mrepeat.h"

#define  LE32(x)        (x)
#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)

#define  LE16(x)        (x)
#define  le16_to_cpu(x) (x)
#define  cpu_to_le16(x) (x)
#define  LE16_TO_CPU(x) (x)
#define  CPU_TO_LE16(x) (x)


typedef uint8_t irqflags_t;

#define COMPILER_PRAGMA(arg)            _Pragma(#arg)
#define COMPILER_PACK_RESET(alignment)
#define COMPILER_PACK_SET(alignment)

#ifndef NULL
#define NULL 0
#endif

#define Max(a, b)           (((a) > (b)) ?  (a) : (b))
#define max(a, b)           Max(a, b)
#define UNUSED(v)          (void)(v)

#  define cpu_irq_enable() sei()
#  define cpu_irq_disable() cli()


# define nvm_get_production_signature_row_offset(regname) offsetof( NVM_PROD_SIGNATURES_t, regname)

typedef uint8_t irqflags_t;

static inline irqflags_t cpu_irq_save(void)
{
	irqflags_t flags = SREG;
	cpu_irq_disable();
	return flags;
}

static inline void cpu_irq_restore(irqflags_t flags)
{
	barrier();
	SREG = flags;
}

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t nvm_read_byte(uint8_t nvm_cmd, uint16_t address);

#ifdef __cplusplus
}
#endif

static inline uint8_t nvm_read_production_signature_row(uint8_t address)
{
	return nvm_read_byte(NVM_CMD_READ_CALIB_ROW_gc, address);
}
#define USBCLK_SRC_RCOSC    0


#define UDD_NO_SLEEP_MGR

#ifdef __cplusplus
extern "C" {
	#endif

void sysclk_disable_usb(void);
void sysclk_enable_usb(uint8_t frequency);
void ccp_write_io(void *addr, uint8_t value);
void ReportError(const char* strFile, int nLine, const char* strFunction, const char* strExp);

#ifdef __cplusplus
}
#endif

#ifndef Assert
#define Assert(expr) { if (!(expr)) { ReportError( __FILE__, __LINE__, __FUNCTION__, #expr); while (1); } }
#endif

