#include "efm32.h"
#include "EFM32_def.h"
#include "Flex_Uart.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "input.h"
#include "Timer.h"
#include "LegMotor.h"
#include "BackPad.h"
#include "em_chip.h"
#include "em_cmu.h"

//extern BITS GlobalFlags3;
//#define FlexMotorEnable		GlobalFlags3.bD4
static bool bFalg ;
static bool b10msFlexinFalg,b100msFalg;
static unsigned int nFlexMotorRunStateOld = STATE_FLEX_IDLE ;
static unsigned int Flex_In_Delay,nFlex_In_TimeStop,nFlex_StretchIn_TimeStop;
static volatile unsigned int w_Timer;
BYTE w_Timer_OutTime;
extern bool bHaveMan;
static volatile unsigned char FlexMotorEn = 0;
unsigned int Flex_In_Fault;
static unsigned int w_FlexAdjStep;

void FlexMotor_Initial_IO(void)
{
    GPIO_PinModeSet(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT, FLEX_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(FLEX_MOTOR_ENBL_PORT, FLEX_MOTOR_ENBL_BIT, FLEX_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(FLEX_MOTOR_PHASE_PORT, FLEX_MOTOR_PHASE_BIT, FLEX_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(FLEX_MOTOR_DECAY_PORT, FLEX_MOTOR_DECAY_BIT, FLEX_MOTOR_DECAY_MODE, 0);
    //GPIO_PinModeSet(FLEX_MOTOR_CURRENT_PORT, FLEX_MOTOR_CURRENT_BIT, FLEX_MOTOR_CURRENT_MODE, 1);//端口不明确
    GPIO_PinModeSet(FLEX_MOTOR_FAULT_PORT, FLEX_MOTOR_FAULT_BIT, FLEX_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = FLEX_MOTOR_Timer_CCInit;
    TIMER_InitCC(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL, &timerCCInit);
    TIMER_TopSet(FLEX_MOTOR_TIMER, FLEX_MOTOR_DEFAULT_TOP);
    TIMER_CompareBufSet(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL, 0);
    TIMER_Init_TypeDef timerInit = FLEX_MOTOR_Timer_Init;
    TIMER_Init(FLEX_MOTOR_TIMER, &timerInit);
    FLEX_MOTOR_TIMER->ROUTE |= (FLEX_MOTOR_ROUTE_EN | FLEX_MOTOR_ROUTE_LOCATION); 
    
//    TIMER_InitCC_TypeDef timerCCcurInit = FLEX_MOTOR_CUR_Timer_CCInit;
//    TIMER_InitCC(FLEX_MOTOR_CUR_TIMER, FLEX_MOTOR_CUR_TIMER_CHANNEL, &timerCCcurInit);  //不明确的定时器
//    TIMER_TopSet(FLEX_MOTOR_CUR_TIMER, FLEX_MOTOR_CUR_DEFAULT_TOP);
//    TIMER_CompareBufSet(FLEX_MOTOR_CUR_TIMER, FLEX_MOTOR_CUR_TIMER_CHANNEL, FLEX_CURRENT_4A);
//    TIMER_Init_TypeDef timercurInit = FLEX_MOTOR_CUR_Timer_Init;
//    TIMER_Init(FLEX_MOTOR_CUR_TIMER, &timercurInit);
//    FLEX_MOTOR_CUR_TIMER->ROUTE |= (FLEX_MOTOR_CUR_ROUTE_EN | FLEX_MOTOR_CUR_ROUTE_LOCATION); 
}

/****************************电机控制函数开始********************************/
void FlexMotor_Out(void)
{
    GPIO_PinOutSet(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT);
    GPIO_PinOutClear(FLEX_MOTOR_PHASE_PORT, FLEX_MOTOR_PHASE_BIT);  
    GPIO_PinOutClear(FLEX_MOTOR_DECAY_PORT, FLEX_MOTOR_DECAY_BIT);
}

void FlexMotor_In(void)
{
    GPIO_PinOutSet(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT);
    GPIO_PinOutSet(FLEX_MOTOR_PHASE_PORT, FLEX_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(FLEX_MOTOR_DECAY_PORT, FLEX_MOTOR_DECAY_BIT);  
}

void FlexMotor_Break(void)
{
    GPIO_PinOutClear(FLEX_MOTOR_DECAY_PORT, FLEX_MOTOR_DECAY_BIT);
    FlexkMotor_Set_Pwm_Data(0);
}
/****************************电机控制函数结束********************************/

/*************************电机电源相关函数开始*******************************/
void FlexMotor_Reset(void)
{
    GPIO_PinOutClear(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT);
}

void FlexMotor_Reset_Cancel(void)
{
    GPIO_PinOutSet(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT);
}

int FlexMotor_Get_Fault(void)
{
    if(GPIO_PinInGet(FLEX_MOTOR_FAULT_PORT, FLEX_MOTOR_FAULT_BIT))
    {
        return FLEX_MOTOR_NORMAL;
    }
    return FLEX_MOTOR_FAIL;
}

void FlexMotor_10ms_Int(void)
{
    bFalg = true; 
    b100msFalg = true; 
    b10msFlexinFalg = true;
}

void FlexkMotor_Set_Pwm_Data(unsigned long ulDuty)
{
    unsigned int duty ;
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL, ulDuty);
        GPIO_PinOutClear(FLEX_MOTOR_RESET_PORT, FLEX_MOTOR_RESET_BIT); 
        return;
    }
    if(FlexMotor_Get_Fault() == FLEX_MOTOR_FAIL) 
    {
        FlexMotor_Reset();
        FlexMotor_Reset_Cancel();
    }
    
    duty = TIMER_CompareBufGet(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL);
    if(!bFalg) return;
    bFalg = false;
    if(duty < ulDuty)
    {
        if(duty < FLEX_MOTOR_DEFAULT_TOP/2)
            duty = FLEX_MOTOR_DEFAULT_TOP/2;
        else duty++;
    }
    TIMER_CompareBufSet(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL, duty);
}

int FlexPower_On(unsigned char speed)
{
    FlexkMotor_Set_Pwm_Data(speed);
    return 0;
}

void FlexPower_Off(void)
{
    FlexkMotor_Set_Pwm_Data(0);
}

unsigned int FlexPower_Get(void)
{
    unsigned long  ulDuty;
    ulDuty = TIMER_CompareBufGet(FLEX_MOTOR_TIMER, FLEX_MOTOR_TIMER_CHANNEL);
    if(ulDuty > 0) return FLEX_POWER_ON;
    else return FLEX_POWER_OFF;
}

unsigned char Flex_GetDirection(void)
{
    if(GPIO_PinOutGet(FLEX_MOTOR_PHASE_PORT , FLEX_MOTOR_PHASE_BIT))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}
/*************************电机电源相关函数结束*******************************/


void FlexMotor_100ms_Int(void)
{
    w_Timer++;
}

void nSet_StretchStopTime(unsigned int time)
{
  nFlex_StretchIn_TimeStop = time;
}

unsigned char FlexMotor_Control(unsigned char nFinalFlexPadMotorState,unsigned char speed,unsigned char current)
{
    static unsigned int position = 0;
    unsigned char nRetVal ;
    bool bPowerFlag;
    nRetVal = FLEX_RUN;

    if(nFlexMotorRunStateOld  != nFinalFlexPadMotorState)
    {
        nFlexMotorRunStateOld = nFinalFlexPadMotorState ;
        position = 0 ;
    }
    switch(nFinalFlexPadMotorState)
    {
    case STATE_RUN_FLEX_IN:
        if(Input_GetFlexInSwitch() == REACH_FLEX_LIMIT || position == 1)
        {
            position = 1;
            bPowerFlag = FALSE;
            nRetVal = FLEX_STOP_AT_IN ;
            FlexMotor_Break();
            break;
        }
        if((Input_GetFlexFootSwitch() == FOOT_SWITCH_ON)&&(b10msFlexinFalg == true) )//向里找到脚，在向脚心移动1秒，停
        {
            Flex_In_Delay++;   
            b10msFlexinFalg = false;
        }
        if((Input_GetFlexFootSwitch() == FOOT_SWITCH_ON)&&(Flex_In_Delay >= 100) )
        { 
            __NOP();
            Flex_In_Delay = 0;
            bPowerFlag = FALSE;
            nRetVal = FLEX_STOP_AT_FOOT ;
            FlexMotor_Break();
            break;
        }
        if(nFlex_In_TimeStop  < 2000)
        {
            
            if(b100msFalg == true)
            {
                b100msFalg = false;
                nFlex_In_TimeStop++;
            }
            if(nFlex_In_TimeStop >=2000)
            {
                Flex_In_Delay = 0;
                bPowerFlag = FALSE;
                nRetVal = FLEX_STOP_AT_FOOT ;
                FlexMotor_Break();
                break;
            }
        }
        __NOP();
        position = 0;
        bPowerFlag = TRUE;
        FlexMotor_In();
        break ;
        
    case STATE_RUN_FLEX_RESET: 
        if(Input_GetFlexInSwitch() == REACH_FLEX_LIMIT || position == 1)
        {
            __no_operation();
            position = 1;
            bPowerFlag = FALSE;
            nRetVal = FLEX_STOP_AT_IN ;
            FlexMotor_Break();
            break;
        }
        __no_operation();
        position = 0;
        bPowerFlag = TRUE;
        FlexMotor_In();
        break ;
        
    case STATE_RUN_FLEX_STRETCH_RESET:   
        if(Input_GetFlexInSwitch() == REACH_FLEX_LIMIT || position == 1)
        {
            position = 1;
            bPowerFlag = FALSE;
            nRetVal = FLEX_STOP_AT_IN ;
            FlexMotor_Break();
            break;
        }
        if(nFlex_StretchIn_TimeStop  < 1300)
        {
            if(b100msFalg == true)
            {
                b100msFalg = false;
                nFlex_StretchIn_TimeStop++;
            }
            if(nFlex_StretchIn_TimeStop >=1300)
            {
                Flex_In_Delay = 0;
                bPowerFlag = FALSE;
                nRetVal = FLEX_STOP_AT_FOOT ;
                FlexMotor_Break();
                break;
            }
        }
        position = 0;
        bPowerFlag = TRUE;
        FlexMotor_In();
        break ; 
        
    case STATE_RUN_FLEX_OUT: 
        if(Input_GetFlexOutSwitch() == REACH_FLEX_LIMIT || position == 2)
        {
            position = 2;
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_OUT ;
            break;
        }
        if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON)//小于15度
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_ANGLE ;
            break;
        }
        if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON)//碰到地面了
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_GROUND;
            break;
        }
        if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON)//碰到脚
        {  
            nRetVal = FLEX_STOP_AT_FOOT ;
        } 
        if((Input_GetFlexFootSwitch() == FOOT_SWITCH_OFF)&&((w_Timer > w_Timer_OutTime)))//碰不到脚了
        {  
            bPowerFlag = FALSE;
            nRetVal = FLEX_STOP_AT_FOOT_LEAVE ;
            FlexMotor_Break();
            break;
        }
        nFlex_In_TimeStop = 0;
        position = 0;
        FlexMotor_Out();
        bPowerFlag = TRUE;nFlex_In_TimeStop = 0;
        break ;
        
    case STATE_RUN_FLEX_STRETCH_OUT:  //向外运行，如果原来有脚向外运行到找不到脚停止，如果原来没脚向外运行2秒停止
        if(Input_GetFlexOutSwitch() == REACH_FLEX_LIMIT || position == 2)
        {
            __NOP();
            position = 2;
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_OUT ;
            break;
        }
        if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON)//小于15度
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_ANGLE ;
            break;
        }
        if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON)//碰到地面了
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_GROUND;
            break;
        }
        if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON)//碰到脚了
        {  
            nRetVal = FLEX_STOP_AT_FOOT ;
        } 
        if(bHaveMan == TRUE)
        {
            if((Input_GetFlexFootSwitch() == FOOT_SWITCH_OFF))//碰不到脚了
            {  
                bPowerFlag = FALSE;
                nRetVal = FLEX_STOP_AT_FOOT_LEAVE ;
                FlexMotor_Break();
                break;
            }
        }
        else
        {
            if(w_Timer > 20)
            { 
                bPowerFlag = FALSE;
                nRetVal = 0x04 ;
                FlexMotor_Break();
                bPowerFlag = false;
                break;
            }
        }
        nFlex_In_TimeStop = 0;
        position = 0;
        FlexMotor_Out();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_FLEX_MANUAL_OUT:  //小腿手动伸出
        if(Input_GetFlexOutSwitch() == REACH_FLEX_LIMIT || position == 2)
        {
            nRetVal = FLEX_STOP_AT_OUT ;
            position = 2;
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nFlex_In_TimeStop = 0;
            break;
        }
        if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON)//碰到地面了
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_GROUND;
            break;
        }
        if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON)//小于15度
        { 
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_ANGLE ;
            break;
        }
        Timer_Counter_Clear(FLEX_TIME_CHANNEL) ;
        position = 0;
        FlexMotor_Out();
        bPowerFlag = TRUE;
        break ;  
    case STATE_RUN_FLEX_TEST_OUT:  //小腿伸出直到碰到行程开关，测试用
        if(Input_GetFlexOutSwitch() == REACH_FLEX_LIMIT || position == 2)
        {
            position = 2;
            bPowerFlag = FALSE;
            FlexMotor_Break();
            nRetVal = FLEX_STOP_AT_OUT ;
            break;
        }
        position = 0;
        FlexMotor_Out();
        bPowerFlag = TRUE;
        break ;    
    case STATE_FLEX_IDLE:
        Timer_Counter_Clear(FLEX_TIME_CHANNEL) ;
        position = 0;
        bPowerFlag = FALSE;
        FlexMotor_Break();
        nRetVal = FLEX_STOP_AT_IDLE;nFlex_In_TimeStop = 0;
        break ;
    default://异常处理
        break ;
    }
    //电源部分的处理
    if(bPowerFlag == TRUE)
    {
        FlexPower_On(speed);
    }
    else
    {
        FlexPower_Off();
    }
    return nRetVal ;
}

void FlexMotorFollowingFood(void)
{
    BYTE FlexMotor_ReturnVal;
    if(FlexMotorEn == 0)
    {
        Flex_In_Delay = 0;
        Flex_In_Fault = 0;
        nFlex_In_TimeStop = 0;
        return;
    }
    if(LegPower_Get())
    {
        Flex_In_Delay = 0;
        Flex_In_Fault = 0;
        FlexMotor_Break();
        return; 
    }
    if(BackMotor_GetPower() == 0)
    {
        Flex_In_Delay = 0;
        Flex_In_Fault = 0;
        FlexMotor_Break();
        return; 
    }
    if((FlexMotor_Get_Fault()==FLEX_MOTOR_FAIL) ||(Flex_In_Fault>=120)) 
    {
        FlexMotorEn = 0;                   
        FlexMotor_Break();                     
        return;
    }
    
    switch(w_FlexAdjStep)
    {
    case 0:
        if(  Input_GetFlexInSwitch() == REACH_FLEX_LIMIT  )
        {
            w_Timer_OutTime = 60;
        }
        else
        {
            w_Timer_OutTime = 20;
        }
        w_Timer = 0;
        w_FlexAdjStep = 1;
        Flex_In_Fault = 0;
        break;
    case 1://先向外走
        FlexMotor_ReturnVal = FlexMotor_Control(STATE_RUN_FLEX_OUT,FLEX_SPEED_MID,FLEX_CURRENT_3A);
        if (  (  (FlexMotor_ReturnVal&FLEX_STOP_AT_OUT) == FLEX_STOP_AT_OUT)
            ||(  (FlexMotor_ReturnVal&FLEX_STOP_AT_ANGLE) == FLEX_STOP_AT_ANGLE)
                ||(  (FlexMotor_ReturnVal&FLEX_STOP_AT_GROUND) == FLEX_STOP_AT_GROUND)
                    ||(  (FlexMotor_ReturnVal&FLEX_STOP_AT_FOOT_LEAVE) == FLEX_STOP_AT_FOOT_LEAVE))
        {
            w_FlexAdjStep++;
            w_Timer = 0;
        }
        if ( (FlexMotor_ReturnVal&FLEX_STOP_AT_FOOT) == FLEX_STOP_AT_FOOT)
        {
            w_Timer_OutTime = 20;
            w_Timer = 0;
        }  
        Flex_In_Delay = 0;
        Flex_In_Fault = 0;
        break;
    case 2://再向里走
        if(FlexMotor_Control(STATE_RUN_FLEX_IN,FLEX_SPEED_MID,FLEX_CURRENT_3A))
        {
            FlexMotorSetDisable();
        }
        break;
    }
}

unsigned char FlexMotorGetEnable(void)
{
    return(FlexMotorEn);
}
void FlexMotorSetEnable(void)
{
    FlexMotorEn = 1;
    w_FlexAdjStep = 0; 
}
void FlexMotorSetDisable(void)
{
    FlexMotorEn = 0;
    w_FlexAdjStep = 0; 
}

void nSet_StretchTime( BYTE time)
{
    w_Timer = time;
}

