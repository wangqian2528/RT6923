#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_dac.h"
//#include "DAC.h"
#include "ADC_Scan.h"
#include "KnockMotor_8840.h"
unsigned int w_KnockCurrent = 4;
bool bKnockslow_10MS_Int = false;
int KnockcurrentSpeed =0;
void KnockMotor_Initial_IO(void)
{
  GPIO_PinModeSet(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT, KNOCK_MOTOR_RESET_MODE, 0);
  GPIO_PinModeSet(KNOCK_MOTOR_ENBL_PORT, KNOCK_MOTOR_ENBL_BIT, KNOCK_MOTOR_ENBL_MODE, 1);
//  GPIO_PinModeSet(KNOCK_MOTOR_PHASE_PORT, KNOCK_MOTOR_PHASE_BIT, KNOCK_MOTOR_PHASE_MODE, 0);
//  GPIO_PinModeSet(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT, KNOCK_MOTOR_DECAY_MODE, 1);
  GPIO_PinModeSet(KNOCK_MOTOR_FAULT_PORT, KNOCK_MOTOR_FAULT_BIT, KNOCK_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = KNOCK_MOTOR_Timer_CCInit;
    /* Configure CC channel 0 */
    TIMER_InitCC(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, &timerCCInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    KNOCK_MOTOR_TIMER->ROUTE |= (KNOCK_MOTOR_ROUTE_EN | KNOCK_MOTOR_ROUTE_LOCATION); 

    /* Set Top Value */
    TIMER_TopSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, 0);

    TIMER_Init_TypeDef timerInit = KNOCK_MOTOR_Timer_Init;
    
    /* Configure timer */
    TIMER_Init(KNOCK_MOTOR_TIMER, &timerInit);
}

void KnockMotor_Reset(void)
{
 // GPIO_PinOutClear(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
  GPIO_PinOutSet(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
}
void KnockMotor_Reset_Cancel(void)
{
 // GPIO_PinOutSet(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
  GPIO_PinOutClear(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
}

unsigned int KnockMotor_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //此处的电压值已经扩大了100倍
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= KNOCK_SET_VOLTAGE/100) 
  {
    return setDuty;        //电压值偏低，返回预设值
  }
  unsigned int scale = KNOCK_SET_VOLTAGE / adc24; //计算与设定电压的比例值
  setDuty *= scale;
  
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  
  return setDuty; 
}


void KnockMotor_Set_Pwm_Data(unsigned long ulDuty)
{
  if(ulDuty == 0)
  {
    TIMER_CompareBufSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, ulDuty);
    return;
  }
  
  ulDuty = KnockMotor_VoltageAdj(ulDuty);
  
  if(KnockMotor_Get_Fault() == KNOCK_MOTOR_FAIL) 
  {
    KnockMotor_Reset();
    __no_operation();
    __no_operation();
    KnockMotor_Reset_Cancel();
  }
  TIMER_CompareBufSet(KNOCK_MOTOR_TIMER, KNOCK_MOTOR_TIMER_CHANNEL, ulDuty);
}

void KnockMotor_ClockRun(void)
{
 // GPIO_PinOutSet(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
//  GPIO_PinOutSet(KNOCK_MOTOR_PHASE_PORT, KNOCK_MOTOR_PHASE_BIT);
 // GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
}
void KnockMotor_UnClockRun(void)
{
 // GPIO_PinOutSet(KNOCK_MOTOR_RESET_PORT, KNOCK_MOTOR_RESET_BIT);
 // GPIO_PinOutSet(KNOCK_MOTOR_PHASE_PORT, KNOCK_MOTOR_PHASE_BIT);
  //GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
}//
void KnockMotor_Break(void)
{
  KnockMotor_Set_Pwm_Data(0);
//  GPIO_PinOutClear(KNOCK_MOTOR_DECAY_PORT, KNOCK_MOTOR_DECAY_BIT);
    KnockcurrentSpeed = 0;
}

int KnockMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(KNOCK_MOTOR_FAULT_PORT, KNOCK_MOTOR_FAULT_BIT))
    return KNOCK_MOTOR_NORMAL;
  return KNOCK_MOTOR_FAIL;
}

void KnockSpeed_Up()
{
  
  //nWalkTopSpeed =  GetWalkTopSpeed();
   // currentSpeed = WALK_MOTOR_DEFAULT_TOP;
  //WalkMotor_Set_Pwm_Data(WALK_MOTOR_DEFAULT_TOP);
  if(!bKnockslow_10MS_Int) return;
  bKnockslow_10MS_Int = false;
  //启动需要的最小力度（电压占空比）
  if(KnockcurrentSpeed < 3)KnockcurrentSpeed = 3;

  if(KnockcurrentSpeed < 90)//nWalkTopSpeed)
  {
    KnockcurrentSpeed+=1;
  }
  else
  {
    KnockcurrentSpeed = 90;//nWalkTopSpeed;
  }
  KnockMotor_Set_Pwm_Data(KnockcurrentSpeed);

}

void KnockMotor_10msInt(void)
{
  bKnockslow_10MS_Int = true;
 /* nWalkLoss++;
  if(nWalkLoss > 2)
  {
    //Power_All_Off();
    TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, 0);
  }*/
}



/*
void KnockMotor_SetCurrent(unsigned int current)
{
  if(current > DAC_CURRENT_MAX_LEVEL)  current = DAC_CURRENT_MAX_LEVEL;
  switch(current)
  {
  case 0: DAC_Set_Data(DAC0, 1,DAC_CURRENT_1A); break;
  case 1: DAC_Set_Data(DAC0, 1,DAC_CURRENT_1_5A); break;
  case 2: DAC_Set_Data(DAC0, 1,DAC_CURRENT_2A); break;
  case 3: DAC_Set_Data(DAC0, 1,DAC_CURRENT_2_5A); break;
  case 4: DAC_Set_Data(DAC0, 1,DAC_CURRENT_3A); break;
  case 5: DAC_Set_Data(DAC0, 1,DAC_CURRENT_3_5A); break;
  case 6: DAC_Set_Data(DAC0, 1,DAC_CURRENT_4A); break;
  case 7: DAC_Set_Data(DAC0, 1,DAC_CURRENT_4_5A); break;
  case 8: DAC_Set_Data(DAC0, 1,DAC_CURRENT_5A); break;
  case 9: DAC_Set_Data(DAC0, 1,DAC_CURRENT_5_5A); break;
  }
  w_KnockCurrent = current;
}

unsigned int KnockMotor_GetCurrent(void)
{
  return(w_KnockCurrent);
}

void KnockMotor_AdcCurrent(void)
{
  if(w_KnockCurrent < DAC_CURRENT_MAX_LEVEL)
  {
    w_KnockCurrent++;
    KnockMotor_SetCurrent(w_KnockCurrent);
  }
}

void KnockMotor_DecCurrent(void)
{
  if(w_KnockCurrent > 0)
  {
    w_KnockCurrent--;
    KnockMotor_SetCurrent(w_KnockCurrent);
  }
}
*/