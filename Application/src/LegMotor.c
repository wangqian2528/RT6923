#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "input.h"
#include "beep.h"
//#include "power.h"
#include "MassageStatus.h"
#include "ADC_Scan.h"
#include "LegMotor.h"
#include "signalUart_new.h"


static UINT32 w_Position;
static bool bLegMotorFlag;

static unsigned int motorStatus = MOTOR_STOP_BREAK;
static volatile unsigned int motorBreakTime;
unsigned  int w_legtest=0;
void LegMotor_Reset(void)
{
  GPIO_PinOutClear(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT);
}
void LegMotor_Reset_Cancel(void)
{
  GPIO_PinOutSet(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT);
}

void LegMotor_Initial_IO(void)
{
    GPIO_PinModeSet(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT, LEG_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(LEG_MOTOR_ENBL_PORT, LEG_MOTOR_ENBL_BIT, LEG_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT, LEG_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(LEG_MOTOR_DECAY_PORT, LEG_MOTOR_DECAY_BIT, LEG_MOTOR_DECAY_MODE, 0);
    GPIO_PinModeSet(LEG_MOTOR_FAULT_PORT, LEG_MOTOR_FAULT_BIT, LEG_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = LEG_MOTOR_Timer_CCInit;//��ʱ��ͨ����ʼ���ṹ��
    /* Configure CC channel 0 */
    TIMER_InitCC(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL, &timerCCInit);
    
    /* Set Top Value */
    TIMER_TopSet(LEG_MOTOR_TIMER, LEG_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL, 65);
    
    TIMER_Init_TypeDef timerInit = LEG_MOTOR_Timer_Init;
    
    /* Configure timer */
    TIMER_Init(LEG_MOTOR_TIMER, &timerInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    LEG_MOTOR_TIMER->ROUTE |= (LEG_MOTOR_ROUTE_EN | LEG_MOTOR_ROUTE_LOCATION); 
}

unsigned int LegPower_Get(void)
{
  unsigned long  ulDuty;
  ulDuty = TIMER_CompareBufGet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL);
  if(ulDuty > 0) return 1;
  else return 0;
}
void LegPower_Off(void)
{
   LegMotor_Set_Pwm_Data(0);    //�ر�����Դ
}
void LegMotor_Up(void)
{
  //Power_On();
  GPIO_PinOutSet(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT);
 // GPIO_PinOutClear(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT);
  GPIO_PinOutSet(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT);
  GPIO_PinOutClear(LEG_MOTOR_DECAY_PORT, LEG_MOTOR_DECAY_BIT);
}
void LegMotor_Down(void)
{
  //Power_On();
  GPIO_PinOutSet(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT);
 // GPIO_PinOutSet(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT);
  GPIO_PinOutClear(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT);
  
  GPIO_PinOutClear(LEG_MOTOR_DECAY_PORT, LEG_MOTOR_DECAY_BIT);
}
void LegMotor_Break(void)
{
  LegMotor_Set_Pwm_Data(0);    //�ر�����Դ
  if(motorStatus == MOTOR_RUN)
  {
   GPIO_PinOutSet(LEG_MOTOR_DECAY_PORT, LEG_MOTOR_DECAY_BIT); //ʹ���˿ڴ��ڸ��裬��ʱ������ڹ��Ի���
   motorStatus = MOTOR_STOP_HZ;
   motorBreakTime = 0;
  }
  if(motorStatus == MOTOR_STOP_HZ)
  {
    if(motorBreakTime < MOTOR_STOP_HZ_TIME) return;
  }
  GPIO_PinOutClear(LEG_MOTOR_DECAY_PORT, LEG_MOTOR_DECAY_BIT);  //��·�����������ɲ��״̬
  motorStatus = MOTOR_STOP_BREAK;
  
    //--------------------------------------------------------------
    GPIO_PinOutClear(LEG_MOTOR_RESET_PORT, LEG_MOTOR_RESET_BIT);
  //----------------------------------------------------------------
  
}

int LegMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(LEG_MOTOR_FAULT_PORT, LEG_MOTOR_FAULT_BIT))
    return LEG_MOTOR_NORMAL;
  return LEG_MOTOR_FAIL;
}

//����С�ȵ綯�׵Ĵ�λ�� ��ߣ���ͻ��м�
unsigned int LegMotor_Get_Location(void)
{
  if(Input_GetLegUpSwitch() == REACH_LEG_LIMIT)   return LEG_MOTOR_AT_TOP;
  if(Input_GetLegDownSwitch() == REACH_LEG_LIMIT)   return LEG_MOTOR_AT_BOTTOM;
  return LEG_MOTOR_AT_MID;
}

//����С�ȵ綯�׵ľ���λ�ã���ʱ������¼��С�ȵ綯��λ����ʹ�ʱ��Ϊ0����λ10ms
unsigned int LegMotor_Get_Position(void)
{
  return w_Position;
}

unsigned int LegMotor_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //�˴��ĵ�ѹֵ�Ѿ�������100��
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= LEG_SET_VOLTAGE/100) 
  {
    return setDuty;        //��ѹֵƫ�ͣ�����Ԥ��ֵ
  }
  unsigned int scale = LEG_SET_VOLTAGE / adc24; //�������趨��ѹ�ı���ֵ
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void LegMotor_Set_Pwm_Data(unsigned long ulDuty)
{
  
  //TIMER_CompareBufSet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL, 120);
  
  
  if(ulDuty == 0)
  {
    TIMER_CompareBufSet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL, ulDuty);
    return;
  }
  if(LegMotor_Get_Fault() == LEG_MOTOR_FAIL) 
  {
    LegMotor_Reset();
    __no_operation();
    __no_operation();
    LegMotor_Reset_Cancel();
  } 
  ulDuty =LegMotor_VoltageAdj(ulDuty);
  TIMER_CompareBufSet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL, ulDuty);
  
  
  
}

void LegMotor_10ms_int(void)
{
  bLegMotorFlag = TRUE;
}
unsigned int wghtest;
void LegMotor_Proce(void)
{
    if(!bLegMotorFlag) return;
    bLegMotorFlag = FALSE;
    
    if(Input_GetLegUpSwitch() == REACH_LEG_LIMIT)
    {
        w_Position = LEG_MOTOR_MAX_POSITION;
    }  
    if(Input_GetLegDownSwitch() == REACH_LEG_LIMIT)
    {
        w_Position = 0;
        w_legtest=0;
    }  
    
    if(!TIMER_CompareBufGet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL)) return;
    
    if(!GPIO_PinOutGet(LEG_MOTOR_PHASE_PORT, LEG_MOTOR_PHASE_BIT))
    {
        if(w_Position > 0) w_Position--;  
	
	w_legtest--;
    }
    else
    {
        if(w_Position < LEG_MOTOR_MAX_POSITION) w_Position++;  
	w_legtest++;
    }
    wghtest = w_Position;
}

//LegPad motor control function
//���������з���0�������г̿��ػ�����ԭ��ֹͣ����1
unsigned char LegMotor_Control(unsigned char nFinalLegPadMotorState)
{
  static unsigned int position = 0;
  unsigned char nRetVal ;
  bool bPowerFlag;
  nRetVal = LEG_RUN;
  
      if(!SignalBoard_isOK())//100ms �������г̿���λ�õ��ֹͣ����
    {
      LegMotor_Break();
      LegPower_Off();
     return(unsigned char)(TRUE);
      
    }
  
  
  
  switch(nFinalLegPadMotorState)
  {
  case STATE_RUN_LEG_DOWN:
    if(Input_GetLegDownSwitch() == REACH_LEG_LIMIT || position == 1) 
    {
       position = 1;
       bPowerFlag = FALSE;
       nRetVal = LEG_STOP_AT_DOWN;
       w_Position = 0;
       LegMotor_Break();
       break;
    }
    /*
    if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON)
    { //����������,С�Ȼ�û���ջص�ʱ������������
      if(Input_GetFlexInSwitch() != REACH_FLEX_LIMIT)
      {
       bPowerFlag = FALSE;
       LegMotor_Break();
       nRetVal = LEG_STOP_AT_GROUND;
       break;
      }
    }
    */
    /*
    if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON)
    { //С��15��
      bPowerFlag = FALSE;
      LegMotor_Break();
      nRetVal = LEG_STOP_AT_ANGLE ;
      break;
    }
    */
    position = 0;
    bPowerFlag = TRUE;
    LegMotor_Down();
    break ;
  case STATE_RUN_LEG_UP:  //����
   if(Input_GetLegUpSwitch() == REACH_LEG_LIMIT || position == 2)
    {
      position = 2;
      bPowerFlag = FALSE;
      LegMotor_Break();
      nRetVal = LEG_STOP_AT_UP;
      w_Position = LEG_MOTOR_MAX_POSITION;
      break;
    }
   position = 0;
    LegMotor_Up();
    bPowerFlag = TRUE;
    break ;
  case STATE_LEG_IDLE:
    bPowerFlag = FALSE;
    LegMotor_Break();
    nRetVal = LEG_STOP_IDLE; ;
    break ;
  default://�쳣����
    break ;
  }
  //��Դ���ֵĴ���
  if(bPowerFlag == TRUE)
  {
      __no_operation();
      __no_operation();
      __no_operation();
      __no_operation();
       __no_operation();
      __no_operation();
      __no_operation();
    LegMotor_Set_Pwm_Data(LEG_MOTOR_DEFAULT_TOP);
  }
  else
  {
    LegMotor_Set_Pwm_Data(0);
  }
  return nRetVal ;
}

int LegMotor_GetDirection(void)
{
  if(GPIO_PinOutGet(LEG_MOTOR_PHASE_PORT,LEG_MOTOR_PHASE_BIT))
  {
   return LEG_MOTOR_GO_DOWN; 
  }
  return LEG_MOTOR_GO_UP; 
}

int LegMotor_GetPower(void)
{
  if(TIMER_CompareBufGet(LEG_MOTOR_TIMER, LEG_MOTOR_TIMER_CHANNEL))
  {
   return LEG_MOTOR_POWER_ON; 
  }
  return LEG_MOTOR_POWER_OFF; 
}
