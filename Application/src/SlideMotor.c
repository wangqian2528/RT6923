#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "input.h"
#include "MassageStatus.h"
#include "memory.h"
#include "LED_RGB.h"
#include "ADC_Scan.h"
#include "SlideMotor.h"
#include "signalUart_new.h"
static unsigned int motorStatus = MOTOR_STOP_BREAK;
static volatile unsigned int motorBreakTime;

bool bFlag;

void SlideMotor_Initial_IO(void)
{
    GPIO_PinModeSet(SLIDE_MOTOR_RESET_PORT, SLIDE_MOTOR_RESET_BIT, SLIDE_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(SLIDE_MOTOR_ENBL_PORT, SLIDE_MOTOR_ENBL_BIT, SLIDE_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT, SLIDE_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(SLIDE_MOTOR_DECAY_PORT, SLIDE_MOTOR_DECAY_BIT, SLIDE_MOTOR_DECAY_MODE, 0);
    GPIO_PinModeSet(SLIDE_MOTOR_FAULT_PORT, SLIDE_MOTOR_FAULT_BIT, SLIDE_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = SLIDE_MOTOR_Timer_CCInit;
    /* Configure CC channel 0 */
    TIMER_InitCC(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL, &timerCCInit);

    /* Set Top Value */
    TIMER_TopSet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL, 0);

    TIMER_Init_TypeDef timerInit = SLIDE_MOTOR_Timer_Init;
 
    /* Configure timer */
    TIMER_Init(SLIDE_MOTOR_TIMER, &timerInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    SLIDE_MOTOR_TIMER->ROUTE |= (SLIDE_MOTOR_ROUTE_EN | SLIDE_MOTOR_ROUTE_LOCATION); 
}

unsigned int SlideMotor_VoltageAdj(void)
{
  unsigned short adc24;      //此处的电压值已经扩大了100倍
  unsigned int setDuty = SLIDE_MOTOR_DEFAULT_TOP;
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= SLIDE_SET_VOLTAGE/100) 
  {
    return setDuty;        //电压值偏低，返回预设值
  }
  unsigned int scale = SLIDE_SET_VOLTAGE / adc24; //计算与设定电压的比例值
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void SlideMotor_Set_PWM(unsigned long ulDuty)
{
  TIMER_CompareBufSet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL, ulDuty);
}
/*
void SlideMotor_Set_Pwm_Data(unsigned long ulDuty)
{
    unsigned int duty ;
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL, ulDuty);
        return;
    }
    duty = TIMER_CompareBufGet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL);
    if(ulDuty == duty)
    {
        if(SlideMotor_Get_Fault() == SLIDE_MOTOR_NORMAL) return;
        SlideMotor_Reset();
        __no_operation();
        __no_operation();
        SlideMotor_Reset_Cancel();
        return; 
    }
    if(!bFlag) return;
    bFlag = false;
    if(duty < ulDuty)
    {
        if(duty < SLIDE_MOTOR_DEFAULT_TOP/2)
        {
            duty = SLIDE_MOTOR_DEFAULT_TOP/2;
        }
        else duty++;
    }
    TIMER_CompareBufSet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL, duty);
}
*/
void SlideMotor_10ms_Int(void)
{
    motorBreakTime++; 
    bFlag = true; 
}

void SlideMotor_Break(void)
{
    SlideMotor_Set_PWM(0);   //关闭马达电源
    if(motorStatus == MOTOR_RUN)
    {
        GPIO_PinOutSet(SLIDE_MOTOR_DECAY_PORT, SLIDE_MOTOR_DECAY_BIT); //使马达端口处于高阻，此时马达属于惯性滑行
        motorStatus = MOTOR_STOP_HZ;
        motorBreakTime = 0;
    }
    if(motorStatus == MOTOR_STOP_HZ)
    {
        if(motorBreakTime < MOTOR_STOP_HZ_TIME) return;
    }
    GPIO_PinOutClear(SLIDE_MOTOR_DECAY_PORT, SLIDE_MOTOR_DECAY_BIT);  //短路马达，保持马达在刹车状态
    motorStatus = MOTOR_STOP_BREAK;
}

int SlideMotorPower_On(void)
{
   unsigned long  ulDuty;
   ulDuty = SlideMotor_VoltageAdj();
   if(SlideMotor_Get_Fault() == SLIDE_MOTOR_FAIL)
    {
      SlideMotor_Reset();
      __no_operation();
      __no_operation();
      SlideMotor_Reset_Cancel();
    }
   SlideMotor_Set_PWM(ulDuty);
   motorStatus = MOTOR_RUN;
   return 1;
}

void SlideMotorPower_Off(void)
{
    SlideMotor_Set_PWM(0);
}

/*
int SlideMotor_GetPower(void)
{
    if(LED_RGB_TIMER->ROUTE == (SLIDE_MOTOR_ROUTE_EN | SLIDE_MOTOR_ROUTE_LOCATION)) 
    {
        unsigned long  ulDuty;
        ulDuty = TIMER_CompareBufGet(LED_RGB_TIMER, SLIDE_MOTOR_CHANNEL); 
        if(ulDuty > 0) return SLIDE_MOTOR_POWER_ON;
        else return SLIDE_MOTOR_POWER_OFF; 
    }
    
    if(GPIO_PinOutGet(SLIDE_MOTOR_ENBL_PORT,SLIDE_MOTOR_ENBL_BIT))
    {
        return SLIDE_MOTOR_POWER_ON; 
    }
    return SLIDE_MOTOR_POWER_OFF; 
}
*/
void SlideMotor_Reset(void)
{
    GPIO_PinOutClear(SLIDE_MOTOR_RESET_PORT, SLIDE_MOTOR_RESET_BIT);
}
void SlideMotor_Reset_Cancel(void)
{
    GPIO_PinOutSet(SLIDE_MOTOR_RESET_PORT, SLIDE_MOTOR_RESET_BIT);
}

void SlideMotor_Forward(void)
{
    GPIO_PinOutSet(SLIDE_MOTOR_RESET_PORT, SLIDE_MOTOR_RESET_BIT);
 //----------- //  GPIO_PinOutClear(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
  //   GPIO_PinOutClear(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
    GPIO_PinOutSet(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(SLIDE_MOTOR_DECAY_PORT, SLIDE_MOTOR_DECAY_BIT);
}
void SlideMotor_Backward(void)
{
    GPIO_PinOutSet(SLIDE_MOTOR_RESET_PORT, SLIDE_MOTOR_RESET_BIT);
   //  GPIO_PinOutSet(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
    
 //-------------- //  GPIO_PinOutSet(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(SLIDE_MOTOR_PHASE_PORT, SLIDE_MOTOR_PHASE_BIT);
    
    GPIO_PinOutClear(SLIDE_MOTOR_DECAY_PORT, SLIDE_MOTOR_DECAY_BIT);
}

unsigned int SlideMotor_Get_Fault(void)
{
    if(GPIO_PinInGet(SLIDE_MOTOR_FAULT_PORT, SLIDE_MOTOR_FAULT_BIT))
    {
        return SLIDE_MOTOR_NORMAL;
    }
    return SLIDE_MOTOR_FAIL;
}

//返回靠背电动缸的大位置 最高，最低或中间
unsigned int SlideMotor_Get_Location(void)
{
    if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)   return SLIDE_MOTOR_AT_FORWARD;
    if(Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT)   return SLIDE_MOTOR_AT_BACKWARD;
    return SLIDE_MOTOR_AT_MID;
}

unsigned int SlideMotor_GetDirection(void)
{
    if(GPIO_PinOutGet(SLIDE_MOTOR_PHASE_PORT,SLIDE_MOTOR_PHASE_BIT))
    {
        return SLIDE_MOTOR_GO_BACKWARD; 
    }
    return SLIDE_MOTOR_GO_FORWARD; 
}

int SlideMotor_GetPower(void)
{
  if(TIMER_CompareBufGet(SLIDE_MOTOR_TIMER, SLIDE_MOTOR_TIMER_CHANNEL))
  {
   return SLIDE_MOTOR_POWER_ON; 
  }
  return SLIDE_MOTOR_POWER_OFF; 
}

unsigned char SlideMotorControl(unsigned char nFinalSlideMotorState)
{
    //static unsigned int position = 0;
    unsigned char nRetVal;
    bool bPowerFlag;
    nRetVal = FALSE;
    
    bool enable = ReadEEByte(USER_DATA_BASE + SLIDE_MOTOR_ENABLE_ADDRESS);
    if(!enable) 
    {
        SlideMotor_Break();
        return TRUE;
    }
    
    //     if(!SignalBoard_isOK())//100ms 读不到行程开关位置电机停止运行
    //    {
    //     SlideMotor_Break();
    //      SlideMotorPower_Off();
    //     return(unsigned char)(TRUE);
    //      
    //    }   
    if((Input_GetBackDownSwitch() == REACH_BACK_LIMIT)&&(Input_GetBackUpSwitch() == REACH_BACK_LIMIT))
    {
         SlideMotor_Break();
         SlideMotorPower_Off();
         return(unsigned char)(TRUE);
    }
    
    switch(nFinalSlideMotorState)
    {
    case STATE_RUN_SLIDE_BACKWARD:
        if(Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT ) //|| position == 1
        {
            //position = 1;
            nRetVal = TRUE ;
            SlideMotor_Break();
            bPowerFlag = FALSE;
            break;
        }
        //position = 0;
        SlideMotor_Backward();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_SLIDE_FORWARD:
        if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)// || position == 2
        {
            //position = 2;
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            SlideMotor_Break();
            break;
        }
        //position = 0;
        SlideMotor_Forward();
        bPowerFlag = TRUE;
        break ;
    case STATE_SLIDE_IDLE:
        nRetVal = TRUE ;
        SlideMotor_Break();
        bPowerFlag = FALSE;
        break ;
    default://异常处理
        break ;
    }
    
    //电源部分的处理
    if(bPowerFlag == TRUE)
    {
        SlideMotorPower_On();
    }
    else
    {
        SlideMotorPower_Off();
    }
    
    
    return nRetVal ;
}
