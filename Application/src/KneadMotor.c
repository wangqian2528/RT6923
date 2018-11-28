#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "efm32_def.h"
#include "MassageStatus.h"
#include "input.h"
#include "em_dac.h"
#include "ADC_Scan.h"
#include "KneadMotor.h"
//unsigned int w_KneadCurrent = 8;
static unsigned int motorStatus = MOTOR_STOP_BREAK;
static unsigned int err=0;
//static unsigned int kneadduty;
bool breset;
static volatile unsigned int motorBreakTime;
static volatile unsigned int kneadCounter;
//static unsigned int kneadSpeed;
static void KneadMotor_Set_Pwm_Data(unsigned long ulDuty);
void KneadMotor_Initial_IO(void)
{
  GPIO_PinModeSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT, KNEAD_MOTOR_RESET_MODE,0);
  GPIO_PinModeSet(KNEAD_MOTOR_ENBL_PORT, KNEAD_MOTOR_ENBL_BIT, KNEAD_MOTOR_ENBL_MODE, 0);
  GPIO_PinModeSet(KNEAD_MOTOR_PHASE_PORT, KNEAD_MOTOR_PHASE_BIT, KNEAD_MOTOR_PHASE_MODE, 0);
  GPIO_PinModeSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT, KNEAD_MOTOR_DECAY_MODE, 0);
  GPIO_PinModeSet(KNEAD_MOTOR_FAULT_PORT, KNEAD_MOTOR_FAULT_BIT, KNEAD_MOTOR_FAULT_MODE, 1);
 // GPIO_PinModeSet(KNEAD_MOTOR_CURRENT_PORT, KNEAD_MOTOR_CURRENT_BIT, KNEAD_MOTOR_CURRENT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = KNEAD_MOTOR_Timer_CCInit;
    /* Configure CC channel 0 */
    TIMER_InitCC(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, &timerCCInit);

    /* Set Top Value */
    TIMER_TopSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, 65);

    TIMER_Init_TypeDef timerInit = KNEAD_MOTOR_Timer_Init;
 
    /* Configure timer */
    TIMER_Init(KNEAD_MOTOR_TIMER, &timerInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    KNEAD_MOTOR_TIMER->ROUTE |= (KNEAD_MOTOR_ROUTE_EN | KNEAD_MOTOR_ROUTE_LOCATION); 
}

void KneadMotor_Reset(void)
{
  GPIO_PinOutClear(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
}

void KneadMotor_Reset_Cancel(void)
{
  GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
}
void KneadMotorBrake_On(void)
{
  KneadMotor_Set_Pwm_Data(0);
  GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
}
void KneadMotorBrake_Off(void)
{
  KneadMotor_Set_Pwm_Data(0);
  GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
}
void KneadMotor_10ms_Int(void)
{
   kneadCounter++;
}
//�������Դ��ѹ����Ԥ��ֵʱ���趨ռ�ձȰ�������С�������趨ռ�ձȲ���
unsigned int KneadMotor_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //�˴��ĵ�ѹֵ�Ѿ�������100��
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= KNEAD_SET_VOLTAGE) 
  {
    return setDuty;        //��ѹֵƫ�ͣ�����Ԥ��ֵ
  }
  unsigned int scale = KNEAD_SET_VOLTAGE * 100 / adc24; //�������趨��ѹ�ı���ֵ,�ٷ�֮scale
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;   //setDuty���԰ٷ�֮scale
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void KneadMotor_Set_Pwm_Data(unsigned long ulDuty)
{
  if(ulDuty == 0)
  {
    TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, ulDuty);
    return;
  }
  if(KneadMotor_Get_Fault() == KNEAD_MOTOR_FAIL) 
  {err++;
    KneadMotor_Reset();
    __no_operation();
    __no_operation();
    KneadMotor_Reset_Cancel();
  } 
  ulDuty = KneadMotor_VoltageAdj(ulDuty);
  
  //kneadduty=ulDuty;
  breset=GPIO_PinInGet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);


  TIMER_CompareBufSet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL, ulDuty);
  motorStatus = MOTOR_RUN;
}
bool KneadMotor_IsRun(void)
{
  unsigned long  ulDuty;
  ulDuty = TIMER_CompareBufGet(KNEAD_MOTOR_TIMER, KNEAD_MOTOR_TIMER_CHANNEL);
  if(ulDuty > 0) return 1;
  else return 0;
}

void KneadMotor_ClockRun(void)
{
  GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
  GPIO_PinOutSet(KNEAD_MOTOR_PHASE_PORT, KNEAD_MOTOR_PHASE_BIT);
  //GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
  GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
}
void KneadMotor_UnClockRun(void)
{
  GPIO_PinOutSet(KNEAD_MOTOR_RESET_PORT, KNEAD_MOTOR_RESET_BIT);
  GPIO_PinOutClear(KNEAD_MOTOR_PHASE_PORT, KNEAD_MOTOR_PHASE_BIT);
  //GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
  GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);
}
void KneadMotor_Break(void)
{
  KneadMotor_Set_Pwm_Data(0);    //�ر�����Դ
  if(motorStatus == MOTOR_RUN)
  {
   GPIO_PinOutSet(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT); //ʹ���˿ڴ��ڸ��裬��ʱ������ڹ��Ի���
   motorStatus = MOTOR_STOP_HZ;
   motorBreakTime = 0;
  }
  if(motorStatus == MOTOR_STOP_HZ)
  {
    if(motorBreakTime < MOTOR_STOP_HZ_TIME) return;
  }
  GPIO_PinOutClear(KNEAD_MOTOR_DECAY_PORT, KNEAD_MOTOR_DECAY_BIT);  //��·�����������ɲ��״̬
  motorStatus = MOTOR_STOP_BREAK;
}

int KneadMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(KNEAD_MOTOR_FAULT_PORT, KNEAD_MOTOR_FAULT_BIT))
    return KNEAD_MOTOR_NORMAL;
  return KNEAD_MOTOR_FAIL;
}

void KneadMotorUpdateSpeed(unsigned int speed)
{
  switch(speed)
  {
  default:  
  case 0: KneadMotor_Set_Pwm_Data(KNEAD_SPEED0_PWM); break;
  case 1: KneadMotor_Set_Pwm_Data(KNEAD_SPEED1_PWM); break;
  case 2: KneadMotor_Set_Pwm_Data(KNEAD_SPEED2_PWM); break;
  case 3: KneadMotor_Set_Pwm_Data(KNEAD_SPEED3_PWM); break;
  case 4: KneadMotor_Set_Pwm_Data(KNEAD_SPEED4_PWM); break;
  case 5: KneadMotor_Set_Pwm_Data(KNEAD_SPEED5_PWM); break;
  case 6: KneadMotor_Set_Pwm_Data(KNEAD_SPEED6_PWM); break;
  }
}
//Knead motor control function
unsigned int KneadMotor_Control(unsigned int nMotorState,unsigned int PWM)
{
//  static unsigned int kneadPosition =  KNEAD_WIDTH_UNKNOWN; 
  unsigned int nRetVal ;
  bool bPowerFlag;
  nRetVal = FALSE ;
  switch(nMotorState)
  {
  case STATE_KNEAD_STOP_AT_MIN:
      //if(KNEAD_WIDTH_MIN == Input_GetKneadPosition())
      if(Input_GetKneadMin() == 0)
      {
       //   kneadPosition = KNEAD_WIDTH_MIN;
          nRetVal = TRUE ;
          KneadMotor_Break();
          bPowerFlag = FALSE;
          break ;  
      }
      PWM = KNEAD_SPEED2_PWM;
      KneadMotor_ClockRun();
      bPowerFlag = TRUE;
      break;
  case STATE_KNEAD_STOP_AT_MED:
      //if(KNEAD_WIDTH_MED == Input_GetKneadPosition())
      if(Input_GetKneadMid() == 0)
      {
       //   kneadPosition = KNEAD_WIDTH_MED;
          KneadMotor_Break();
          nRetVal = TRUE ;
          bPowerFlag = FALSE;
          break ;  
      }
      PWM = KNEAD_SPEED2_PWM;
      KneadMotor_ClockRun();
      bPowerFlag = TRUE;
      break;
  case STATE_KNEAD_STOP_AT_MAX:  
      //if(KNEAD_WIDTH_MAX == Input_GetKneadPosition())
      if(Input_GetKneadMax() == 0)
      {
      //    kneadPosition = KNEAD_WIDTH_MAX;
          nRetVal = TRUE ;
          KneadMotor_Break();
          bPowerFlag = FALSE;
          break ;  
      }
      PWM = KNEAD_SPEED2_PWM;
      KneadMotor_ClockRun();
      bPowerFlag = TRUE;
      break;
  case STATE_KNEAD_CLOCK_RUN:    //˳ʱ����ת
    nRetVal = FALSE ;
    KneadMotor_ClockRun();
    bPowerFlag = TRUE;
    break;
  case STATE_KNEAD_UNCLOCK_RUN:  //��ʱ����ת
    nRetVal = FALSE ;
    KneadMotor_UnClockRun();
    bPowerFlag = TRUE;
    break;
  default:
  case STATE_KNEAD_IDLE:
    nRetVal = TRUE ;
    KneadMotor_Break();
    bPowerFlag = FALSE;
    break ;  
  } 
  //��Դ���ֵĴ���
  if(bPowerFlag == TRUE)
  {
    KneadMotor_Set_Pwm_Data(PWM);
  }
  else
  {
    KneadMotor_Set_Pwm_Data(0);
  }
  return nRetVal ;
}

/*
void KneadMotor_SetCurrent(int current)
{
  if(current > DAC_CURRENT_MAX_LEVEL)  current = DAC_CURRENT_MAX_LEVEL;
  switch(current)
  {
  case 0: DAC_Set_Data(DAC0, 0,DAC_CURRENT_1A); break;
  case 1: DAC_Set_Data(DAC0, 0,DAC_CURRENT_1_5A); break;
  case 2: DAC_Set_Data(DAC0, 0,DAC_CURRENT_2A); break;
  case 3: DAC_Set_Data(DAC0, 0,DAC_CURRENT_2_5A); break;
  case 4: DAC_Set_Data(DAC0, 0,DAC_CURRENT_3A); break;
  case 5: DAC_Set_Data(DAC0, 0,DAC_CURRENT_3_5A); break;
  case 6: DAC_Set_Data(DAC0, 0,DAC_CURRENT_4A); break;
  case 7: DAC_Set_Data(DAC0, 0,DAC_CURRENT_4_5A); break;
  case 8: DAC_Set_Data(DAC0, 0,DAC_CURRENT_5A); break;
  case 9: DAC_Set_Data(DAC0, 0,DAC_CURRENT_5_5A); break;
  }
  w_KneadCurrent = current;
}

unsigned int KneadMotor_GetCurrent(void)
{
  return(w_KneadCurrent);
}
void KneadMotor_AdcCurrent(void)
{
  if(w_KneadCurrent < DAC_CURRENT_MAX_LEVEL)
  {
    w_KneadCurrent++;
    KneadMotor_SetCurrent(w_KneadCurrent);
  }
}

void KneadMotor_DecCurrent(void)
{
  if(w_KneadCurrent > 0)
  {
    w_KneadCurrent--;
    KneadMotor_SetCurrent(w_KneadCurrent);
  }
}
*/

#define KNEAD_WIDTH_UNKNOWN		0
#define KNEAD_WIDTH_MIN			1
#define KNEAD_WIDTH_MED			2
#define KNEAD_WIDTH_MAX			3


void KneadMotor_CalculateSpeed(unsigned int kneadPosition)
{
  return;
  static bool bAlreadyDone = false;     //����ͷͣ�������ֻ�ܴ���һ�α�־λ
  static unsigned int bSpeedInvalid = false; //�ٶȸո����������ܼ����־λ
  if(!KneadMotor_IsRun())
  {
     //kneadSpeed = 0;
     bSpeedInvalid = true;
     return;
  }
  if(kneadPosition == KNEAD_WIDTH_MAX)
  {
    if(bAlreadyDone) return;
    bAlreadyDone = true; 
    if(bSpeedInvalid)
    {
      //kneadSpeed = 0;
      bSpeedInvalid = false;
    }
    else
    {
      //kneadSpeed = kneadCounter;  
     // printf("%d\n\r",kneadSpeed);
    }
    kneadCounter = 0;
  }
  else
  {
    bAlreadyDone = false;  //��������λ��
  }
}
