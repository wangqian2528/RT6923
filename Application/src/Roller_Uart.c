#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "Roller_Uart.h"
#include "ADC_Scan.h"


/**********************************新增变量开始**********************************/
unsigned int nRollercnt;
unsigned int displayPWM;
/**********************************新增变量结束**********************************/
//static unsigned char nRollerSpeed;
//static unsigned char nRollerMode;
//
//void Roller_SetSpeed(unsigned char rollerSpeed)
//{
//   nRollerSpeed = rollerSpeed;
//   
//}
//unsigned char Roller_GetSpeed(void)
//{
//    return nRollerSpeed;
//}
//
//void Roller_SetMode(unsigned int mode)
//{
//    nRollerMode = mode;
//}
//unsigned char Roller_GetMode(void)
//{
//    return(nRollerMode);
//}
//void RollerMotor_Control(unsigned int speed,unsigned int phase)
//{
//  Roller_SetSpeed(speed);
//  if(phase)
//  {
//    Roller_SetMode(ROLLER_MODE_CON_IN);
//  }
//  else
//  {
//   Roller_SetMode(ROLLER_MODE_CON_OUT);
//  }
//}
//void RollerMotor_Controlstrtch(unsigned int speed,unsigned int phase)
//{
//  Roller_SetSpeed(speed);
//    Roller_SetMode(phase);
//
//}


void Roller_Initial_IO(void)
{
    GPIO_PinModeSet(ROLLER_MOTOR_RESET_PORT, ROLLER_MOTOR_RESET_BIT, ROLLER_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(ROLLER_MOTOR_ENBL_PORT, ROLLER_MOTOR_ENBL_BIT, ROLLER_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(ROLLER_MOTOR_PHASE_PORT, ROLLER_MOTOR_PHASE_BIT, ROLLER_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(ROLLER_MOTOR_DECAY_PORT, ROLLER_MOTOR_DECAY_BIT, ROLLER_MOTOR_DECAY_MODE, 0);
    GPIO_PinModeSet(ROLLER_MOTOR_FAULT_PORT, ROLLER_MOTOR_FAULT_BIT, ROLLER_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = ROLLER_MOTOR_Timer_CCInit;
    /* Configure CC channel 0 */
    TIMER_InitCC(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL, &timerCCInit);
    
    /* Set Top Value */
    TIMER_TopSet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL, 0);
    
    TIMER_Init_TypeDef timerInit = ROLLER_MOTOR_Timer_Init;
    /* Configure timer */
    TIMER_Init(ROLLER_MOTOR_TIMER, &timerInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    ROLLER_MOTOR_TIMER->ROUTE |= (ROLLER_MOTOR_ROUTE_EN | ROLLER_MOTOR_ROUTE_LOCATION); 
}

unsigned int RollerMotor_VoltageAdj(unsigned int setDuty)
{
    unsigned short adc24;      //此处的电压值已经扩大了100倍
    ADC_Get_Voltage(ADC_V24,&adc24);     
    if(adc24 <= ROLLER_SET_VOLTAGE/100) 
    {
        return setDuty;        //电压值偏低，返回预设值
    }
    unsigned int scale = ROLLER_SET_VOLTAGE / adc24; //计算与设定电压的比例值
    setDuty *= scale;
    unsigned int yushu = setDuty  % 100;
    setDuty /= 100;
    if(yushu > 50) setDuty++;
    return setDuty; 
}

void RollerMotor_Reset(void)
{
    GPIO_PinOutClear(ROLLER_MOTOR_RESET_PORT, ROLLER_MOTOR_RESET_BIT);
    RollerMotor_Set_Pwm_Data(0);
}

void RollerMotor_Reset_Cancel(void)
{
    GPIO_PinOutSet(ROLLER_MOTOR_RESET_PORT, ROLLER_MOTOR_RESET_BIT);
}

int RollerMotor_Get_Fault(void)
{
    if(GPIO_PinInGet(ROLLER_MOTOR_FAULT_PORT, ROLLER_MOTOR_FAULT_BIT))
        return ROLLER_MOTOR_NORMAL;
    return ROLLER_MOTOR_FAIL;
}
unsigned long ulDuty1;
void RollerMotor_Set_Pwm_Data(unsigned long ulDuty)
{
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL, ulDuty);
        return;
    }
    ulDuty = RollerMotor_VoltageAdj(ulDuty);
    ulDuty1=ulDuty;
    if(RollerMotor_Get_Fault() == ROLLER_MOTOR_FAIL)
    {
        RollerMotor_Reset();
        __NOP;
        __NOP;
        RollerMotor_Reset_Cancel();
    }
    TIMER_CompareBufSet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL, ulDuty);
}

unsigned long RollerMotor_Get_Pwm_Data(void)
{
    return(TIMER_CompareBufGet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL));
}

bool RollerMotor_IsRun(void)
{
    unsigned long  ulDuty;
    ulDuty = TIMER_CompareBufGet(ROLLER_MOTOR_TIMER, ROLLER_MOTOR_TIMER_CHANNEL);
    if(ulDuty > 0) return 1;
    else return 0;
}

void RollerMotor_ClockRun(void)
{
    GPIO_PinOutSet(ROLLER_MOTOR_RESET_PORT, ROLLER_MOTOR_RESET_BIT);
    GPIO_PinOutClear(ROLLER_MOTOR_PHASE_PORT, ROLLER_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(ROLLER_MOTOR_DECAY_PORT, ROLLER_MOTOR_DECAY_BIT);
}
void RollerMotor_UnClockRun(void)
{
    GPIO_PinOutSet(ROLLER_MOTOR_RESET_PORT, ROLLER_MOTOR_RESET_BIT);
    GPIO_PinOutSet(ROLLER_MOTOR_PHASE_PORT, ROLLER_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(ROLLER_MOTOR_DECAY_PORT, ROLLER_MOTOR_DECAY_BIT);
}
void RollerMotor_Break(void)
{
    RollerMotor_Set_Pwm_Data(0);
    GPIO_PinOutClear(ROLLER_MOTOR_DECAY_PORT, ROLLER_MOTOR_DECAY_BIT);
}

void RollerMotor_Control(unsigned int ulDuty,unsigned int phase)
{
    switch(phase)
    {
    default:
    case 0://连续正传
        RollerMotor_ClockRun();
        break;
    case 1://连续反转
        RollerMotor_UnClockRun();
        break;
    case 2:// 正向转1s，停1s
        if(nRollercnt < 100 )//前1s正转
        {
            //ulDuty = 0;
        }
        else if(nRollercnt < 200 )//1s~2s停止
        {
            ulDuty = 0;
        }
        else
        {
            nRollercnt=0;
        }
        RollerMotor_ClockRun();
        break;
        
    case 3://反向转1s，停1s
        if(nRollercnt < 100 )//前1s运行
        {
            //ulDuty = 0;
        }
        else if(nRollercnt < 200 )//1s~2s停
        {
            ulDuty = 0;
        }
        else
        {
            nRollercnt=0;
        }
        RollerMotor_UnClockRun();
        break;
        
    case 4:// 正向转3s停3s
        if(nRollercnt < 300 )//前3s运行
        {
            //ulDuty = 0;
        }
        else if(nRollercnt < 600 )//3s~6s停止
        {
            ulDuty = 0;
        }
        else
        {
            nRollercnt=0;
        }
        RollerMotor_ClockRun();
        break;       
        
        
    case 5:// 反向转3s停3s
        if(nRollercnt < 300 )
        {
            //ulDuty = 0;
        }
        else if(nRollercnt < 600 )
        {
            ulDuty = 0;
        }
        else
        {
            nRollercnt=0;
        }
        RollerMotor_UnClockRun();
        
        break;
        
        
        
    case 6://正向转1s，反向转1s
        
        if(nRollercnt < 100 )
        {
            RollerMotor_ClockRun();
        }
        else if(nRollercnt < 200 )
        {
            RollerMotor_UnClockRun();
        }
        else
        {
            nRollercnt=0;
        }
        break;
        
    case 7://正向转3s，反向转3s
        if(nRollercnt < 300 )
        {
            RollerMotor_ClockRun();
        }
        else if(nRollercnt < 600 )
        {
            RollerMotor_UnClockRun();
        }
        else
        {
            nRollercnt=0;
        }
        
        break; 
    }
    
    RollerMotor_Set_Pwm_Data(ulDuty);
    displayPWM = ulDuty;
}

void RollerMotor_10msInt(void)
{
    nRollercnt++;
}

