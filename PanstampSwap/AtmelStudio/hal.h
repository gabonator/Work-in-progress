#pragma once
#include "common.h"

#define F_CPU 12000000
#include <util/delay.h>

// Delay functions require compile time known argument, backward compatibility and nicer interface would result in less precise timing
#define HAL_TIME_DelayMs _delay_ms
#define HAL_TIME_DelayUs _delay_us

class HAL
{
public:
	class SPI
	{
	public:
		static void Init();
		static uint8_t Send(byte data);
	};

	class IO
	{
	public:
		enum EPin {
			A0, A1, A2, A3, A4, A5, A6, A7,
			B0, B1, B2, B3, B4, B5, B6, B7,
			C0, C1, C2, C3, C4, C5, C6, C7,
			D0, D1, D2, D3, D4, D5, D6, D7
		};

		enum EMode {
			Input = 1,
			Output = 2,
			PullUp = 4,
			InputPullUp = Input | PullUp
		};

		enum EPort {
			A, B, C, D
		};

	public:
		static void Configure(EPin ePin, EMode eMode);
		static void Write(EPin ePin, byte bValue);
		static byte Read(EPin ePin);

		static void Write(EPort ePort, byte bValue);
		static byte Read(EPort ePin);
	};

	class TIME
	{
	public:
		static void Init();
		static void DelayMs(int nMs);
		static void DelayUs(int nUs);
		static uint32_t GetTick();
	};
	
	class INT
	{
	public:
		typedef void (*THandlerFunction)();
		
	public:	
		static void Attach(IO::EPin ePin, THandlerFunction pHandler);
		static void Enable();
		static void Disable();
	};
	
	class COM
	{
	public:
		static void Init();
		static uint8_t Ready();
		static uint8_t Available();
		static uint8_t Get();
		static void Put(uint8_t ch);			
	};
};
