#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "power.h"

void Power_Initial_IO(void)
{
  GPIO_PinModeSet(POWER_GENERAL_PORT, POWER_GENERAL_BIT, POWER_GENERAL_MODE, GENERAL_POWER_OFF); 
  GPIO_PinModeSet(POWER_3V3_PORT, POWER_3V3_BIT, POWER_3V3_MODE, GENERAL_3V3_ON); 
  GPIO_PinModeSet(POWER_5V_PORT, POWER_5V_BIT, POWER_5V_MODE, GENERAL_5V_ON); 
}

unsigned int Power_Get(void)
{
  return(GPIO_PinOutGet(POWER_GENERAL_PORT,POWER_GENERAL_BIT));
}

void Power_3V3_On(void)
{
  GPIO_PinOutSet(POWER_3V3_PORT,POWER_3V3_BIT);
}
void Power_3V3_Off(void)
{
  GPIO_PinOutClear(POWER_3V3_PORT,POWER_3V3_BIT);
}    
void Power_On(void)
{
  GPIO_PinOutSet(POWER_GENERAL_PORT,POWER_GENERAL_BIT);
}
void Power_Off(void)
{
  GPIO_PinOutClear(POWER_GENERAL_PORT,POWER_GENERAL_BIT);
}    
void Power_5V_On(void)
{
  GPIO_PinOutSet(POWER_5V_PORT,POWER_5V_BIT);
}
void Power_5V_Off(void)
{
  GPIO_PinOutClear(POWER_5V_PORT,POWER_5V_BIT);
}

/*将5V屏蔽的原因是，在睡眠模式与语音板通信的485芯片还需要供5V电，
因此睡眠模式不能关闭5V */
void Power_All_Off(void)
{
  Power_Off();
  Power_3V3_Off();
  Power_5V_Off();
  VoiceUart_PowerOff();
}

void Power_All_On(void)
{
    Power_On();
    Power_3V3_On();
    Power_5V_On();
}
