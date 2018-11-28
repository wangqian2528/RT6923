#include "EFM32_def.h"
#include "EFM32_types.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "input.h"
#include "memory.h"
#include "MassageStatus.h"
#include "valve.h"
#include  "ADC_Scan.h"
#include "BackPad.h"
//�����綯��λ�� ��ߣ�0 ��ͣ����λ��
#include "signalUart_new.h"


#define BACK_PROTECT_PORT     gpioPortD
#define BACK_PROTECT_BIT      10

#ifndef BACK_PLUSE_COUNTER




UINT32 w_Position;
static bool bBackMotorFlag;

static unsigned int motorStatus = MOTOR_STOP_BREAK;
static volatile unsigned int motorBreakTime;

//void BackMotor_Initial_IO(void)
//{
//  GPIO_PinModeSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT, BACK_MOTOR_RESET_MODE, 1);
//  GPIO_PinModeSet(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT, BACK_MOTOR_ENBL_MODE, 0);
//  GPIO_PinModeSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT, BACK_MOTOR_PHASE_MODE, 0);
//  GPIO_PinModeSet(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT, BACK_MOTOR_DECAY_MODE, 0);
//  GPIO_PinModeSet(BACK_MOTOR_FAULT_PORT, BACK_MOTOR_FAULT_BIT, BACK_MOTOR_FAULT_MODE, 1);
//  /*
//  GPIO_PinModeSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT, BACK_MOTOR_RESET_MODE, 1);
//  GPIO_PinModeSet(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT, BACK_MOTOR_ENBL_MODE, 1);
//  GPIO_PinModeSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT, BACK_MOTOR_PHASE_MODE, 1);
//  GPIO_PinModeSet(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT, BACK_MOTOR_DECAY_MODE, 0);
//  GPIO_PinModeSet(BACK_MOTOR_FAULT_PORT, BACK_MOTOR_FAULT_BIT, BACK_MOTOR_FAULT_MODE, 1);
//  
//  Power_On();
//  while(1);
//  */
//  TIMER_InitCC_TypeDef timerCCInit = BACK_MOTOR_Timer_CCInit;
//  TIMER_InitCC(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, &timerCCInit);
//  BACK_MOTOR_TIMER->ROUTE |= (BACK_MOTOR_ROUTE_EN | BACK_MOTOR_ROUTE_LOCATION); 
//  TIMER_TopSet(BACK_MOTOR_TIMER, BACK_MOTOR_DEFAULT_TOP);
//  TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL,65);// 0);
//  TIMER_Init_TypeDef timerInit = BACK_MOTOR_Timer_Init;
//  TIMER_Init(BACK_MOTOR_TIMER, &timerInit);
//  
//}
/*
int BackMotor_GetPower(void)
{
  if(GPIO_PinOutGet(BACK_MOTOR_ENBL_PORT,BACK_MOTOR_ENBL_BIT))
  {
   return BACK_MOTOR_POWER_ON; 
  }
  return BACK_MOTOR_POWER_OFF; 
}
*/
int BackMotor_GetDirection(void)
{
  if(GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT,BACK_MOTOR_PHASE_BIT))
  {
   return BACK_MOTOR_GO_UP; 
  }
  return BACK_MOTOR_GO_DOWN; 
}

void BackPower_Off(void)
{
  TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, 0);
  //BackMotor_Set_Pwm_Data(0);
}

unsigned int BackMotor_VoltageAdj(void)
{
  unsigned short adc24;      //�˴��ĵ�ѹֵ�Ѿ�������100��
  unsigned int setDuty = BACK_MOTOR_DEFAULT_TOP;
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= BACK_SET_VOLTAGE/100) 
  {
    return setDuty;        //��ѹֵƫ�ͣ�����Ԥ��ֵ
  }
  unsigned int scale = BACK_SET_VOLTAGE / adc24; //�������趨��ѹ�ı���ֵ
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void BackPower_On(void)
{
  unsigned long  ulDuty;
  ulDuty = BackMotor_VoltageAdj();
  if(BackMotor_Get_Fault() == BACK_MOTOR_FAIL) 
   {
      BackMotor_Reset();
     __no_operation();
     __no_operation();
     BackMotor_Reset_Cancel();
   }
  TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, ulDuty);
}
/*
static void BackPower_On(void)
{
  BackMotor_Set_Pwm_Data(BACK_MOTOR_DEFAULT_TOP);
}
static void BackPower_Off(void)
{
  BackMotor_Set_Pwm_Data(0);
}
*/

//void BackMotor_Up(void)
//{
//  GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
////  GPIO_PinOutSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
//  GPIO_PinOutClear(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
//  GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);
//}
//void BackMotor_Down(void)
//{
//  GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
// // GPIO_PinOutClear(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
//   GPIO_PinOutSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
//  
//  GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);//DECAY =1 ����ֹͣ//Ϊ�ߵ�ƽʱ��250V ��������ѹ���½���15V
//}
void BackMotor_Break(void)
{
  BackPower_Off();    //�ر�����Դ
  if(motorStatus == MOTOR_RUN)
  {
  //tt GPIO_PinOutSet(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT); //ʹ���˿ڴ��ڸ��裬��ʱ������ڹ��Ի���
   motorStatus = MOTOR_STOP_HZ;
   motorBreakTime = 0;
  }
  if(motorStatus == MOTOR_STOP_HZ)
  {
    if(motorBreakTime < MOTOR_STOP_HZ_TIME) return;
  }
 //tt GPIO_PinOutSet(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);
  //GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);  //��·�����������ɲ��״̬
  motorStatus = MOTOR_STOP_BREAK;
  
    //-------------------------------------------------------------------//������λ
   GPIO_PinOutClear(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
  //-------------------------------------------------------------------
  
  
  
}

void BackMotor_Reset(void)
{
  GPIO_PinOutClear(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
}
void BackMotor_Reset_Cancel(void)
{
  GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
}
int BackMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(BACK_MOTOR_FAULT_PORT, BACK_MOTOR_FAULT_BIT))
    return BACK_MOTOR_NORMAL;
  return BACK_MOTOR_FAIL;
}
//���ؿ����綯�׵Ĵ�λ�� ��ߣ���ͻ��м�
unsigned int BackMotor_Get_Location(void)
{
  if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)   return BACK_MOTOR_AT_TOP;
  if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)   return BACK_MOTOR_AT_BOTTOM;
  return BACK_MOTOR_AT_MID;
}
//���ؿ����綯�׵ľ���λ�ã���ʱ������¼�������綯��λ����ߴ�ʱ��Ϊ0����λ10ms
unsigned int BackMotor_Get_Position(void)
{
  return w_Position;
}

int BackMotor_GetPower(void)
{
  if(TIMER_CompareBufGet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL))
  {
   return BACK_MOTOR_POWER_ON; 
  }
  return BACK_MOTOR_POWER_OFF; 
}

void BackMotor_10ms_int(void)
{
  bBackMotorFlag = TRUE;
}

void BackMotor_Proce(void)
{
    if(!bBackMotorFlag) return;
    
    if(REACH_BACK_LIMIT == Input_GetBackDownSwitch())
    {
        w_Position = BACK_MOTOR_MAX_POSITION; 
        return;
    }
    if(REACH_BACK_LIMIT == Input_GetBackUpSwitch())
    {
        w_Position = 0; 
        return;
    }
    
    bBackMotorFlag = FALSE;
    
    if(!TIMER_CompareBufGet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL)) return;
    
    if(!GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT))
    {
        if(w_Position > 0) w_Position--;  
    }
    else
    {
        if(w_Position < BACK_MOTOR_MAX_POSITION) w_Position++;  
    }
}
void currentBackPadMotorState_reset()
{
  //currentBackPadMotorState = STATE_BACK_IDLE;
}
//BackPad motor control function
//unsigned char BackMotor_Control(unsigned char nFinalBackPadMotorState)
//{
//  static unsigned int position = 0;
//  unsigned char nRetVal ;
//  bool bPowerFlag;
//  nRetVal = FALSE ;
//  
//  bool enable = ReadEEByte(USER_DATA_BASE + SLIDE_MOTOR_ENABLE_ADDRESS);
//    if(enable) 
//      if(Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT)
//        if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)
//    {
//        BackMotor_Break();
//        return TRUE;
//    }
//  
//
//    
//    
//  
//  switch(nFinalBackPadMotorState)
//  {
//  case STATE_RUN_BACK_DOWN:  //back motor go down
//    if(REACH_BACK_LIMIT == Input_GetBackDownSwitch() || position == 1)
//    {
//      position = 1;
//      bPowerFlag = FALSE;
//      nRetVal = TRUE ;
//      BackMotor_Break();
//      break;
//    }
//    position = 0;
//    BackMotor_Down();
//    bPowerFlag = TRUE;
//    break ;
//  case STATE_RUN_BACK_UP:  //back motor go up
//    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT || position == 2)
//    {
//      position = 2;
//      bPowerFlag = FALSE;
//      nRetVal = TRUE ;
//      BackMotor_Break();
//      break;
//    }
//    position = 0;
//    BackMotor_Up();
//    bPowerFlag = TRUE;
//    break ;
//  case STATE_BACK_IDLE:
//    nRetVal = TRUE ;
//    BackMotor_Break();
//    bPowerFlag = FALSE;
//    break ;
//  default://�쳣����
//    break ;
//  }
//  //��Դ���ֵĴ���
//  if(bPowerFlag == TRUE)
//  {
//    BackPower_On();
//  }
//  else
//  {
//    BackPower_Off();
//  }
//  return nRetVal ;
//}


//========================================================================

#else
unsigned int w_pistiong2,fatul;
//�����綯��λ�� ��ߣ�0 ��ͣ����λ��
extern BITS GlobalFlags5 ;
#define bGetNextActionStep 			GlobalFlags5.bD5
static UINT32 w_Position;
static bool bBackMotorFlag;
extern unsigned char nReworkShoulderPosition;//zlw
//extern unsigned int nCurActionStep;
//static unsigned int motorStatus = MOTOR_STOP_BREAK;
static volatile unsigned int motorBreakTime;
bool slow_break_10MS_Int = false;
bool speedUp_10MS_Int = false;
bool breakDown_10MS_Int = false; 
bool set_Pwm_10MS_Int = false;
bool isRocking = false;
int speed = 0;
int currentSpeed = BACK_MOTOR_DEFAULT_TOP;
unsigned char currentBackPadMotorState = STATE_BACK_IDLE;

void BackMotor_Initial_IO(void)
{
  GPIO_PinModeSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT, BACK_MOTOR_RESET_MODE, 0);
  GPIO_PinModeSet(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT, BACK_MOTOR_ENBL_MODE, 0);
  GPIO_PinModeSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT, BACK_MOTOR_PHASE_MODE, 0);
  GPIO_PinModeSet(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT, BACK_MOTOR_DECAY_MODE, 0);
  GPIO_PinModeSet(BACK_MOTOR_FAULT_PORT, BACK_MOTOR_FAULT_BIT, BACK_MOTOR_FAULT_MODE, 1);
  //Configure TIMER1 CC0 LOC1 PE10
  TIMER_InitCC_TypeDef timerCCInit = BACK_MOTOR_Timer_CCInit;

  TIMER_InitCC(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, &timerCCInit);
 
  
  GPIO_PinModeSet(BACK_PROTECT_PORT, BACK_PROTECT_BIT, gpioModeInputPullFilter, 1);
  
  
  
 TIMER_TopSet(BACK_MOTOR_TIMER, BACK_MOTOR_DEFAULT_TOP);
  
  TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, 0);

  
  BACK_MOTOR_TIMER->ROUTE |= (BACK_MOTOR_ROUTE_EN /*|LEG_MOTOR_ROUTE_EN*/ |/*SLIDE_MOTOR_ROUTE_EN | */BACK_MOTOR_ROUTE_LOCATION); //��ʱ���������������
  
   //init TIMER1
  TIMER_Init_TypeDef timerInit = BACK_MOTOR_Timer_Init;

  TIMER_Init(BACK_MOTOR_TIMER, &timerInit);  
}

int BackMotor_GetPower(void)
{
  if(TIMER_CompareBufGet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL) > 0)
  {
    return BACK_MOTOR_POWER_ON;
  }
  return BACK_MOTOR_POWER_OFF;
  /*
  if(GPIO_PinOutGet(BACK_MOTOR_ENBL_PORT,BACK_MOTOR_ENBL_BIT))
  {
   return BACK_MOTOR_POWER_ON; 
  }
  return BACK_MOTOR_POWER_OFF; 
  */
}
int BackMotor_GetDirection(void)
{
  if(GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT,BACK_MOTOR_PHASE_BIT))
  {
   return BACK_MOTOR_GO_UP; 
  }
  return BACK_MOTOR_GO_DOWN; 
}

int BackPower_On(void)
{
    int val = 0;
    //Power_On();
    if(GPIO_PinOutGet(BACK_MOTOR_ENBL_PORT,BACK_MOTOR_ENBL_BIT))
    { //�˿��Ѿ�high
        if(BackMotor_Get_Fault() == BACK_MOTOR_FAIL)
        {
            BackMotor_Reset();
            __no_operation();
            __no_operation();
            BackMotor_Reset_Cancel();
            __no_operation();
            if(BackMotor_Get_Fault() != BACK_MOTOR_FAIL) val = 0;
        }
    }
    else
    {
        GPIO_PinOutSet(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT);
        //motorStatus = MOTOR_RUN;
        val =  1;
    }
    return val;
}
void BackPower_Off(void)
{
  GPIO_PinOutClear(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT);
  TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, 0);
}

  
void BackMotor_Up(void)
{
  GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
   GPIO_PinOutClear(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
   GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);//����ֹͣ  250V ,������ѹ�����½�   ,���Ϊ25V
}
void BackMotor_Down(void)
{
    GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
    GPIO_PinOutSet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT, BACK_MOTOR_DECAY_BIT);
}
void BackMotor_Break(void)
{
    if(!breakDown_10MS_Int)return;
    breakDown_10MS_Int = false;
    //�˵�ɲ������137.5
    if(currentSpeed > BACK_MIN_SPEED)
    {
        //�˵㼱ɲ��
        if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT ||Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
        {
            currentSpeed -= 3+currentSpeed/40+currentSpeed/20;
            GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT,BACK_MOTOR_DECAY_BIT);
        }
        else//�м�һ��ɲ��
        {
            if(GetbRockEnable())
            {
               GPIO_PinOutSet(BACK_MOTOR_DECAY_PORT,BACK_MOTOR_DECAY_BIT);
            }
            else
            {
               GPIO_PinOutClear(BACK_MOTOR_DECAY_PORT,BACK_MOTOR_DECAY_BIT);
            }
            currentSpeed =0;//-= 1+currentSpeed/100+currentSpeed/70;
        }
    }
    if(currentSpeed <= BACK_MIN_SPEED)currentSpeed = 0;    
}

void BackMotor_Reset(void)
{
  GPIO_PinOutClear(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
}
void BackMotor_Reset_Cancel(void)
{
  GPIO_PinOutSet(BACK_MOTOR_RESET_PORT, BACK_MOTOR_RESET_BIT);
}
int BackMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(BACK_MOTOR_FAULT_PORT, BACK_MOTOR_FAULT_BIT))
    return BACK_MOTOR_NORMAL;
  return BACK_MOTOR_FAIL;
}
////131223
unsigned int BackMotor_VoltageAdj(unsigned int setDuty)
{
  
  
  
  unsigned short adc24;      //�˴��ĵ�ѹֵ�Ѿ�������100��
  ADC_Get_Voltage(ADC_V24,&adc24);
  if(adc24 <= BACK_SET_VOLTAGE/100)
  {
    return setDuty;        //��ѹֵƫ�ͣ�����Ԥ��ֵ
  }
  unsigned int scale = BACK_SET_VOLTAGE / adc24; //�������趨��ѹ�ı���ֵ
  setDuty *= scale;
  unsigned int yushu = setDuty % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty;
  
  /*
     unsigned short adc24;
  ADC_Get_Voltage(ADC_V24,&adc24);  
                                                                                                                
  unsigned int duty = setDuty;
  if(adc24 <= BACK_SET_VOLTAGE/100) 
  {
    return duty; 
  }
  unsigned int yushu = BACK_SET_VOLTAGE % adc24;
  duty = BACK_SET_VOLTAGE / adc24;
  if(yushu > adc24/2) duty++;
  return duty;  
  */
  
}
void Back_Motor_PwmSet_Fault_Process(unsigned long ulDuty)
{
    //unsigned long  ulDuty;
    ulDuty = BackMotor_VoltageAdj(ulDuty); //ZERO_MOTOR_DEFAULT_TOP
    unsigned int duty ;
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, ulDuty);
        return;
    }
    duty = TIMER_CompareBufGet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL);
    if(ulDuty == duty)
    {
        if(BackMotor_Get_Fault() == BACK_MOTOR_FAIL)
        {
            BackMotor_Reset();
            __no_operation();
            __no_operation();
            fatul++;
            BackMotor_Reset_Cancel();
            return;
        }
        return;
    }
    if(!set_Pwm_10MS_Int) return;
    set_Pwm_10MS_Int = false;
    duty = ulDuty;
    TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, duty);
}

//���ؿ����綯�׵Ĵ�λ�� ��ߣ���ͻ��м�
unsigned int BackMotor_Get_Location(void)
{
  if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)   return BACK_MOTOR_AT_TOP;
  if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)   return BACK_MOTOR_AT_BOTTOM;
  return BACK_MOTOR_AT_MID;
}
//���ؿ����綯�׵ľ���λ�ã���ʱ������¼�������綯��λ����ߴ�ʱ��Ϊ0����λ10ms
unsigned int BackMotor_Get_Position(void)
{
  return w_Position;
}

void BackMotor_10ms_int(void)
{
  bBackMotorFlag = TRUE;
  speedUp_10MS_Int = TRUE;
  breakDown_10MS_Int = TRUE;
  set_Pwm_10MS_Int = TRUE;
  slow_break_10MS_Int = TRUE;
}
void speedUp(void)
{
  if(!speedUp_10MS_Int) return;
  speedUp_10MS_Int = false;
  //������Ҫ����С���ȣ���ѹռ�ձȣ�
  if(currentSpeed < BACK_MIN_SPEED)currentSpeed = BACK_MIN_SPEED;
  if(isRocking){
    if(currentSpeed < BACK_MOTOR_DEFAULT_TOP - 10/* - 20*/){
      currentSpeed++;
    }
  }else{
    if(currentSpeed < BACK_MOTOR_DEFAULT_TOP){
      currentSpeed+=2;
    }
  }
}
void ZeroMotor_SlowBreak(void)
{
  if(!slow_break_10MS_Int)return;
  slow_break_10MS_Int = false;
  if(currentSpeed > 0)currentSpeed--;
  if(currentSpeed < BACK_MIN_SPEED)currentSpeed = 0;
}
void BackMotor_Proce(void)
{
    if(!bBackMotorFlag) return;
    bBackMotorFlag = FALSE;
    
    //if(!GPIO_PinOutGet(BACK_MOTOR_ENBL_PORT, BACK_MOTOR_ENBL_BIT)) return;
    
    if(TIMER_CompareBufGet(BACK_MOTOR_TIMER,BACK_MOTOR_TIMER_CHANNEL) <= BACK_MIN_SPEED) return;
    
    if(!GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT))
        // if(GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT))//������ϣ������С
    {
        if(w_Position > 0) w_Position--;  
        w_pistiong2--;
        
    }
    else
    {
        if(w_Position < BACK_MOTOR_MAX_POSITION) w_Position++;  
        w_pistiong2++;
        
        
    }
}

//BackMotor
unsigned char BackMotor_Control(unsigned char nFinalBackPadMotorState)
{
    //static unsigned int position = 0;
    unsigned char nRetVal ;
    // bool bPowerFlag;
    nRetVal = FALSE ;
    unsigned char speedState = BACK_SPEED_STATE_STOP;//ֹͣ0��ɲ��1������2����ɲ��3��������4

//    if(!SignalBoard_isOK())//100ms �������г̿���λ�õ��ֹͣ����//20180719���ε���ֹ��Ϊ100ms�������г̿��ط���1�����ҡ��ʱ������δ����λ����ǰ�����ƶ�������
//    {
//        BackMotor_Break();
//        BackPower_Off();
//        return(unsigned char)(TRUE);  
//    }
    
    //��ǰ�������ǰ����λ����Чʱ����������������У���ֹ��ǰ������ʱ�˶�������ɴ�ǽ������//20180718
    if((Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT)&&(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT))
    {
        BackMotor_Break();
        BackPower_Off();
        return TRUE;
    }
    
    //����
    if(currentBackPadMotorState != nFinalBackPadMotorState && currentBackPadMotorState != STATE_BACK_IDLE)
    {
        //ɲ��
        //��������
        if((currentBackPadMotorState == STATE_RUN_BACK_UP && Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
           ||(currentBackPadMotorState == STATE_RUN_BACK_DOWN && Input_GetBackDownSwitch() == REACH_BACK_LIMIT))
        {
            //����ʱ����ɲ��
            speedState = BACK_SPEED_STATE_BREAK;
        }
        else if(isRocking)
        {
            //ҡ��ʱ,��ɲ��
            speedState = BACK_SPEED_STATE_SLOW_BREAK;
        }
        else
        {
            //�ֶ�ʱ����ɲ��
            speedState = BACK_SPEED_STATE_BREAK;
        }
        if(currentSpeed <= 0)
        {
            currentBackPadMotorState = nFinalBackPadMotorState;
        }
    }
    else
    {
        currentBackPadMotorState = nFinalBackPadMotorState;
        switch(nFinalBackPadMotorState)
        {
        case STATE_RUN_BACK_DOWN:  
            if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT )//|| position == 1
            {
                //position = 1;
                //bPowerFlag = FALSE;
                nRetVal = TRUE ;
                w_Position = BACK_MOTOR_MAX_POSITION;
                BackMotor_Break();
                break;
            }
            //position = 0;
            //BackMotor_Set_Route();
            BackMotor_Down();
            speedState = BACK_SPEED_STATE_UP;
            //bPowerFlag = TRUE;
            break ;
            
        case STATE_RUN_BACK_UP:  //back motor go up
            if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT )//|| position == 2
            {
                //position = 2;
                //bPowerFlag = FALSE;
                nRetVal = TRUE ;
                w_Position = 0;
                BackMotor_Break();
                break;
            }
            //position = 0;
            //BackMotor_Set_Route();
            BackMotor_Up();
            speedState = BACK_SPEED_STATE_UP;
            //bPowerFlag = TRUE;
            break ;
            
        case STATE_BACK_IDLE:
            nRetVal = TRUE ;
            //BackMotor_Set_Route();
            BackMotor_Break();
            speedState = BACK_SPEED_STATE_BREAK;
            //bPowerFlag = FALSE;
            break ;
        default://�쳣����
            break ;
        }
    }
    switch(speedState)
    {
    case BACK_SPEED_STATE_STOP:
        currentSpeed = 0;
        break;
    case BACK_SPEED_STATE_BREAK:
        BackMotor_Break();
        break;
    case BACK_SPEED_STATE_UP:
        __NOP();
        speedUp();
        break;
    case BACK_SPEED_STATE_SLOW_BREAK:
        ZeroMotor_SlowBreak();
        break;
    case BACK_SPEED_STATE_SLOW_UP:
        //ҡ�μ����ж��ں�����
        speedUp();
        break;
    }
    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
    {
	Input_SetBackMotorPosition(0);
    }
    else if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
    {
        Input_SetBackMotorPosition(BACK_MOTOR_MAX_POSITION_PULSE);
    }
    //Խ�紦��
    if(currentSpeed > BACK_MOTOR_DEFAULT_TOP)
    {
        currentSpeed = BACK_MOTOR_DEFAULT_TOP;
    }
    if(currentSpeed < 0)
    {
        currentSpeed = 0;
    }
    Back_Motor_PwmSet_Fault_Process(currentSpeed);
    return nRetVal ;
}

void setBackPadRockingEnable(bool flag)
{
    isRocking = flag;
}

void BackMotor_Set_Route(void)
{
	if(BACK_MOTOR_TIMER->ROUTE != (BACK_MOTOR_ROUTE_EN | BACK_MOTOR_ROUTE_LOCATION))
	{
		TIMER_Init_TypeDef timerInit = BACK_MOTOR_Timer_Init;
		TIMER_Init(BACK_MOTOR_TIMER, &timerInit);
		BACK_MOTOR_TIMER->ROUTE = (BACK_MOTOR_ROUTE_EN | BACK_MOTOR_ROUTE_LOCATION); 
		//BackMotor_Set_PWM(0);
	}
}
void BackMotor_Set_PWM(unsigned long ulDuty)
{
	TIMER_CompareBufSet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL, ulDuty);
}

unsigned int BackPower_Get(void)
{
  unsigned int  ulDuty;
  ulDuty = TIMER_CompareBufGet(BACK_MOTOR_TIMER, BACK_MOTOR_TIMER_CHANNEL);
  if(ulDuty > 0) return 1;
  else return 0;
}






#endif






