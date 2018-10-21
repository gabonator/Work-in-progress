#include "Bios.h"

#include <stm32f10x_tim.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

namespace PIN
{
  enum {
    // nPort
    PortA = 0,
    PortB = 1,
    PortC = 2,
    PortD = 3,

    // nReg
    RegCrl = 0,
    RegCrh = 1,
    RegIdr = 2,
    RegOdr = 3,
    RegBsrr = 4,
    RegBrr = 5,
    RegLckr = 6,
    
    // nState
    StateInput = 0,           // ..00
    StateOutput10Mhz = 1,     // ..01
    StateOutput2Mhz = 2,      // ..10
    StateOutput50Mhz = 3,     // ..11

    StateInputAnalog = 0<<2,
    StateInputFloating = 1<<2,
    StateInputPull = 2<<2,

    StateOutputPushPull = 0<<2,
    StateOutputOpenDrain = 1<<2,
    StateOutputFunctionPushPull = 2<<2,
    StateOutputFunctionOpenDrain = 3<<2,
    
    // macros for easy use
    StateSimpleInput = StateInput | StateInputFloating,
    StateSimpleOutput = StateOutput2Mhz | StateOutputPushPull
  };

  /*
  #define PERIPH_BASE           ((u32)0x40000000)
  #define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
  #define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
  #define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
  #define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
  #define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
  #define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
  #define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
  #define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)
  */
  const static uint32_t arrGpioBase[] = {GPIOA_BASE, GPIOB_BASE, GPIOC_BASE, GPIOD_BASE, GPIOE_BASE, GPIOF_BASE, GPIOG_BASE};

  uint32_t* GetRegister(int nPort, int nReg)
  {
    uint32_t dwAddr = arrGpioBase[nPort];

    dwAddr |= nReg*4; 
    return (uint32_t*)dwAddr;
  }

  void SetState(int nPort, int nPin, int nState)
  {
    uint32_t dwAddr;

    if ( nPin < 8 )
      dwAddr = arrGpioBase[nPort] + 0;	// CRL
    else
    {
      dwAddr = arrGpioBase[nPort] + 4;	// CRH
      nPin &= 7;
    }

    uint32_t dwMask = ~(0xf << (nPin*4));
    uint32_t dwBits = nState << (nPin*4);

    uint32_t* pCR = ((uint32_t*)dwAddr);
    *pCR = (*pCR & dwMask) | dwBits;
  }

  void SetPin(int nPort, int nPin, bool bValue)
  {
    uint32_t dwAddr = arrGpioBase[nPort];
    if ( bValue )
    {
      uint32_t* pBSRR = &((uint32_t*)dwAddr)[4];
      *pBSRR = 1<<nPin;
    } else
    {
      uint32_t* pBRR = &((uint32_t*)dwAddr)[5];
      *pBRR = 1<<nPin;
    }
  }

  bool GetPin(int nPort, int nPin)
  {
    uint32_t dwAddr = arrGpioBase[nPort];
    uint32_t dwIDR = ((uint32_t*)dwAddr)[2];
    return (dwIDR & (1<<nPin)) ? 1 : 0;
  }
}

namespace PWM
{
  void RCCInit(void)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // TIM4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  } 

  void TimerInit(uint16_t period) 
  {
    TIM_TimeBaseInitTypeDef timerInitStructure;

    // TIM2
    timerInitStructure.TIM_Prescaler = 72;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = period;
    timerInitStructure.TIM_ClockDivision = 0;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE); 

    // TIM4
    TIM_TimeBaseInit(TIM4, &timerInitStructure);
    TIM_Cmd(TIM4, ENABLE); 
  }

  void GPIOInit(void)
  {
    // TIM2
    {
      GPIO_InitTypeDef gpioStructure; 
      gpioStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
      gpioStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
      gpioStructure.GPIO_Speed = GPIO_Speed_50MHz ; 
      GPIO_Init(GPIOB, &gpioStructure); 
    }
    // TIM4
    {
      GPIO_InitTypeDef gpioStructure; 
      gpioStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
      gpioStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(GPIOB, &gpioStructure); 
    }
  }

  void PWMInit(void)
  { 
    TIM_OCInitTypeDef outputChannelInit;
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 1;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

    // TIM2
    TIM_OC3Init(TIM2, &outputChannelInit);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM2, &outputChannelInit);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);

    // TIM4
    TIM_OC3Init(TIM4, &outputChannelInit);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_OC4Init(TIM4, &outputChannelInit);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  }

  void EnablePwm(void)
  {
    RCCInit();
    TimerInit(BIOS::GPIO::AnalogRange);
    GPIOInit();
    PWMInit();
  }

  void DisablePwm(void)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, DISABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);
    TIM_Cmd(TIM2, DISABLE); 
    TIM_Cmd(TIM4, DISABLE); 

    GPIO_InitTypeDef gpioStructure; 
    gpioStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
    gpioStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
    gpioStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpioStructure); 

    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Disable);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, DISABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, DISABLE);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Disable);
  }
}

namespace BIOS
{
  namespace GPIO
  {
    /*
      P1: PB15, PB10  remap   TIM2_CH3
      P2: PB14, PB11  remap   TIM2_CH4
      P3: PB13, PB8   default TIM4_CH3
      P4: PB12, PB9   default TIM4_CH4
    */
    static const uint8_t arrPinAdrAPort[4] = {PIN::PortB, PIN::PortB, PIN::PortB, PIN::PortB};
    static const uint8_t arrPinAdrAPin[4] = {15, 14, 13, 12};
    static const uint8_t arrPinAdrBPort[4] = {PIN::PortB, PIN::PortB, PIN::PortB, PIN::PortB};
    static const uint8_t arrPinAdrBPin[4] = {10, 11, 8, 9};

    bool bModePwm = false;

    void DigitalWrite(EPin pin, bool value)
    {
      PIN::SetPin(arrPinAdrBPort[pin], arrPinAdrBPin[pin], value);
    }

    bool DigitalRead(EPin pin)
    {
      return PIN::GetPin(arrPinAdrBPort[pin], arrPinAdrBPin[pin]);
    }

    void AnalogWrite(EPin pin, int value)
    {
      value = max(0, min(value, AnalogRange));

      switch (pin)
      {
        case P1: TIM_SetCompare3 (TIM2, value); break;
        case P2: TIM_SetCompare4 (TIM2, value); break;
        case P3: TIM_SetCompare3 (TIM4, value); break;
        case P4: TIM_SetCompare4 (TIM4, value); break;
      }
    }

    int AnalogRead(EPin pin)
    {
      return 0;
    }

    void PinMode(EPin pin, EMode mode)
    {
      if (mode == Pwm)
      {
        if (!bModePwm)
        {
          bModePwm = true;
          PWM::EnablePwm();
        }
      } else
      {
        if (bModePwm)
        {
          bModePwm = false;
          PWM::DisablePwm();
        }
      }

      PIN::SetState(arrPinAdrAPort[pin], arrPinAdrAPin[pin], PIN::StateSimpleInput);

      switch ((int)mode)
      {
        case Input:
          PIN::SetState(arrPinAdrBPort[pin], arrPinAdrBPin[pin], PIN::StateSimpleInput);
          break;
        case Input | PullUp:
          PIN::SetState(arrPinAdrBPort[pin], arrPinAdrBPin[pin], PIN::StateInput | PIN::StateInputPull);
          break;
        case Input | PullDown:
          _ASSERT(0);
          break;
        case Output:
          PIN::SetState(arrPinAdrBPort[pin], arrPinAdrBPin[pin], PIN::StateSimpleOutput);
          break;
        case Pwm:
          AnalogWrite(pin, 0);
          break;
        default:
          _ASSERT(0);
      }
    }
  }
}
