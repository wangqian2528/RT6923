#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "EFM32_def.h"
#include "ADC_Scan.h"
#include "input.h"
#include "signalUart_new.h"
#include "AxisMotor.h"
#include "UartLeg.h"
//--------���ַ���ӵĲ�����AxisMotor.c�ļ�ʹ�ã�start---------
#define _3dposmax   38
#define _3dposmin  2
unsigned char _3D_step = 0;
//bool _3D_walkflag;
//unsigned short _3D_POS;
extern bool _3D_StopFlag;
bool _3D_MaxOk=0;
unsigned char _3D_Press_Times;
bool _3D_Min_Ok;
bool _3D_Max_Ok,_3D_PosStop_TimeFlag;
unsigned char _3d_step=0;
extern unsigned char _3D_PosStop_Time;
extern unsigned char downWalkRun,upWalkRun;
extern bool Knead_Min_Ok;
extern bool Knead_Max_Ok;
//-----------------------end--------------------------


//unsigned char AxisMotorPosition[]={2,10,20,30,_3D_MAX_POSITION};
//�˱���Ϊ5�����ȵ�ĵ���ֵ 0�����1���ϴ�2���У�3����С 4����С
//unsigned int AxisMotorStrength[_3D_POSITION_POINT];
//��о�����г�λ�ù�ȡ_3D_FULL_POINT+1�����������㣬ÿ��������������5������ֵ
//��һ������������Ϊ0 ���һ������������Ϊ���λ�ã��м仹��9����
st_n3D_Data   n3DMotorCurrent[_3D_FULL_POINT+1]; //���λ�����µ���������ͼ��λ�õ��������� 
st_n3D_Data*  p3DMotorCurrent = n3DMotorCurrent; 
unsigned int positionCount;
bool bGetAxisPositionEnable;
bool bUpdataPosition = true;
bool bDisableCheckCurrent,bEnableCheckCurrent,b3D_PositionError;
volatile unsigned char nAxisLoss;
volatile unsigned int _3D_PositionErrorCount;
unsigned long AxisMotor_Get_Pwm_Data(void);
//unsigned short MaxCurrent;

//static char by_currentTimer_Flag;
void Axis_Initial_IO(void)
{
    GPIO_PinModeSet(AXIS_MOTOR_RESET_PORT, AXIS_MOTOR_RESET_BIT, AXIS_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(AXIS_MOTOR_ENBL_PORT, AXIS_MOTOR_ENBL_BIT, AXIS_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT, AXIS_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(AXIS_MOTOR_DECAY_PORT, AXIS_MOTOR_DECAY_BIT, AXIS_MOTOR_DECAY_MODE, 0);
    GPIO_PinModeSet(AXIS_MOTOR_FAULT_PORT, AXIS_MOTOR_FAULT_BIT, AXIS_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = AXIS_MOTOR_Timer_CCInit;
    /* Configure CC channel 0 */
    TIMER_InitCC(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, &timerCCInit);
    
    /* Set Top Value */
    TIMER_TopSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_DEFAULT_TOP);
    
    TIMER_CompareBufSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, 0);
    
    TIMER_Init_TypeDef timerInit = AXIS_MOTOR_Timer_Init;
    /* Configure timer */
    TIMER_Init(AXIS_MOTOR_TIMER, &timerInit);
    
    /* Route CC0 to location 3 (PD1) and enable pin */  
    AXIS_MOTOR_TIMER->ROUTE |= (AXIS_MOTOR_ROUTE_EN | AXIS_MOTOR_ROUTE_LOCATION); 
    
}

unsigned int AxisMotor_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //�˴��ĵ�ѹֵ�Ѿ�������100��
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= AXIS_SET_VOLTAGE/100) 
  {
    return setDuty;        //��ѹֵƫ�ͣ�����Ԥ��ֵ
  }
  unsigned int setVoltage;
  if(GPIO_PinOutGet(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT))
  {
    setVoltage = AXIS_SET_VOLTAGE;  
  }
  else
  {
    setVoltage = AXIS_SET_VOLTAGE;  
  } 
  unsigned int scale = setVoltage / adc24; //�������趨��ѹ�ı���ֵ
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void AxisMotor_SetSpeed(unsigned int setSpeed)
{
    if(setSpeed == 0)
    {
        TIMER_CompareBufSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, 0);
        return;
    }
    unsigned int curSpeed = UartLeg_Get3D_Speed();//LEUART0_Get3D_Speed();
    unsigned int curPWM = AxisMotor_Get_Pwm_Data();
    unsigned int setPWM;
    if(curPWM == 0)
    {
        switch(setSpeed)
        {
        default: 
        case _3D_SPEED_1: setPWM = _3D_SPEED_1_PWM;break;
        case _3D_SPEED_2: setPWM = _3D_SPEED_2_PWM;break;
        case _3D_SPEED_3: setPWM = _3D_SPEED_3_PWM;break;
        case _3D_SPEED_4: setPWM = _3D_SPEED_4_PWM;break;
        case _3D_SPEED_5: setPWM = _3D_SPEED_5_PWM;break;
        case _3D_SPEED_6: setPWM = _3D_SPEED_6_PWM;break;
        case _3D_SPEED_7: setPWM = _3D_SPEED_7_PWM;break;
        case _3D_SPEED_8: setPWM = _3D_SPEED_8_PWM;break;
        case _3D_SPEED_9: setPWM = _3D_SPEED_8_PWM;break;
        case _3D_SPEED_10: setPWM = _3D_SPEED_8_PWM;break;
        }
    }
    else
    {
        if(curSpeed < setSpeed)
        {
            if(curPWM > _3D_MIN_PWM)
            {
                curPWM--;
            }
        }
        if(curSpeed > setSpeed)
        {
            if(curPWM > _3D_MIN_PWM)
                curPWM++;
        }
        setPWM = curPWM;
    }
    AxisMotor_Set_Pwm_Data(setPWM);
}


void AxisMotor_Set_Pwm_Data(unsigned long ulDuty)
{
  
  if(ulDuty == 0)
  {
    TIMER_CompareBufSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, ulDuty);
    return;
  }
  ulDuty = AxisMotor_VoltageAdj(ulDuty);
  if(AxisMotor_Get_Fault() == AXIS_MOTOR_FAIL)
  {
    AxisMotor_Reset();
    __no_operation();
    __no_operation();
    AxisMotor_Reset_Cancel();
  }
  TIMER_CompareBufSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, ulDuty);
}

unsigned long AxisMotor_Get_Pwm_Data(void)
{
  return(TIMER_CompareBufGet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL));
}

bool AxisMotor_IsRun(void)
{
  unsigned long  ulDuty;
  ulDuty = TIMER_CompareBufGet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL);
  if(ulDuty > 0) return 1;
  else return 0;
}

void AxisMotor_ClockRun(void)
{
  GPIO_PinOutSet(AXIS_MOTOR_RESET_PORT, AXIS_MOTOR_RESET_BIT);
  GPIO_PinOutClear(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT);
  GPIO_PinOutClear(AXIS_MOTOR_DECAY_PORT, AXIS_MOTOR_DECAY_BIT);
}
void AxisMotor_UnClockRun(void)
{
  GPIO_PinOutSet(AXIS_MOTOR_RESET_PORT, AXIS_MOTOR_RESET_BIT);
  GPIO_PinOutSet(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT);
  GPIO_PinOutClear(AXIS_MOTOR_DECAY_PORT, AXIS_MOTOR_DECAY_BIT);
}
void AxisMotor_Break(void)
{
  AxisMotor_Set_Pwm_Data(0);
  GPIO_PinOutSet(AXIS_MOTOR_DECAY_PORT, AXIS_MOTOR_DECAY_BIT);
}
static void AxisPower_Off(void)
{
  AxisMotor_Set_Pwm_Data(0);
}
/*
3D �����Ƴ���
stopLevel ��STATE_RUN_AXIS_REAL_POSITIONʱΪʵ��λ��
stopLevel ��STATE_RUN_AXIS_POSITIONʱΪλ�õȼ�
*/
#define AT_MIDDLE_SWITCH  0
#define AT_FRONT_SWITCH   1
#define AT_BACK_SWITCH   2

unsigned char AxisMotor_Control(unsigned char nFinalAxisMotorState,unsigned short stopLevel,unsigned int speed)
{
    static unsigned int justPosition = AT_MIDDLE_SWITCH;
    unsigned int setPWM;
    unsigned char nRetVal ;
    bool bPowerFlag = false;
    nRetVal = FALSE;
    unsigned short curPosition = Input_GetAxisMotorPosition();
    //static unsigned short oldPosition;
    static unsigned short oldPosition;
    unsigned short stopPosition;
    int levelMax = _3D_POSITION_POINT;
    
    nAxisLoss = 0;
    
    //   #ifdef SELECT_3D
    //   if(!SignalBoard_isOK())//������3D�г̿��ػ�ͣ
    //  {
    //     AxisMotor_Break();
    //     return(unsigned char)(TRUE);
    //  }
    //  #endif
    //  
    //  if(!UartLeg_Get3DMessage_RXStatus())
    //  {
    //    AxisMotor_Break();
    //    return(unsigned char)(TRUE);
    //    
    //  }
    //  
    
    //  if(!SignalBoard_isOK())//100ms ���ߵ���г̿��ػ�ͣ
    //  {
    //    AxisMotor_Break();
    //    return(unsigned char)(TRUE);
    //    
    //  }
    /**********�ж�3D�����ź��Ƿ�����***********************/  
    if(AxisMotor_IsRun())
    { //3D��������е�
        if(oldPosition == curPosition)
        {
            if(_3D_PositionErrorCount > 5) //1.5��
            {
                AxisMotor_Break();
                return(unsigned char)(TRUE);
            }
        }
        else
        {
            b3D_PositionError = false; 
            _3D_PositionErrorCount = 0;
        }
    }
    else
    {  //3D�����ֹͣ��
        b3D_PositionError = false; 
        _3D_PositionErrorCount = 0;
    }
    oldPosition = curPosition;
    /********************************************/   
    
    /*
    if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
    {
    nFinalAxisMotorState = STATE_RUN_AXIS_FORWARD;
}
    */
    switch(nFinalAxisMotorState)
    {
    case STATE_RUN_AXIS_KNEAD_HALF:
        speed = _3D_SPEED_8;
        switch(_3D_step)
        {
        case 0:
            if(Knead_Min_Ok)
            {
                if(Input_Get3DFrontSwitch()) 
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break();
                    _3D_step = 1;
                    _3D_Max_Ok = TRUE;
                    break;
                }  
                if(curPosition > 36)
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break(); 
                    _3D_step = 1;
                    _3D_Max_Ok = TRUE;
                    break;
                }
                AxisMotor_ClockRun();
                bPowerFlag = TRUE;
            } 
            break;
        case 1:
            if(Knead_Max_Ok)
            {
                if(Input_Get3DBackSwitch()) 
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break();
                    _3D_step = 0;
                    _3D_Min_Ok = FALSE; 
                    Knead_Max_Ok = FALSE;
                    break;
                }
                if(curPosition < 4)
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break(); 
                    _3D_step = 0;
                    _3D_Min_Ok = TRUE;
                    Knead_Max_Ok = FALSE;
                    nRetVal = TRUE;
                    break;
                }
                AxisMotor_UnClockRun();
                bPowerFlag = TRUE;
            }
            break;
        }
        break;
    case STATE_RUN_AXIS_3D_KNEAD:
        speed = _3D_SPEED_8;
        switch(_3D_step)
        {
        case 1:
            if(upWalkRun)
            { 
                if(curPosition < 5)
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break(); 
                    _3D_step = 0;
                    nRetVal = 1;
                    break;
                }
                AxisMotor_ClockRun();
                bPowerFlag = TRUE;
            }
            else
            {
                bPowerFlag = FALSE;            
                AxisMotor_Break(); 
                _3D_step = 0;
                // nRetVal = 1;     //20170630
            }
            break;
        case 0:
            if(downWalkRun)
            { 
                if(curPosition > 36)
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break(); 
                    _3D_step = 1;
                    //nRetVal = 1;   //20170630
                    break;
                }
                AxisMotor_UnClockRun();
                bPowerFlag = TRUE;
            }
            else
            {
                bPowerFlag = FALSE;            
                AxisMotor_Break(); 
                //nRetVal = 1;     //20170630
                _3D_step = 1;
            }
            break;
        }  
        break;
    case STATE_RUN_AXIS_TOGGLE:
        speed = _3D_SPEED_6;
        nRetVal = TRUE;
        switch(_3d_step)
        {
        case 0:
            if(!Knead_Min_Ok)  //
            {
                if(Input_Get3DBackSwitch()) //3D Motor go back
                {
                    _3D_Min_Ok = 1;             
                    
                    AxisMotor_Break(); 
                    __NOP();
                    _3d_step = 1;
                    bPowerFlag = FALSE; //nRetVal = TRUE;
                    break;
                }
                //          if(Input_Get3DFrontSwitch()) //3D Motor go back
                //       {
                //          //  _3D_Min_Ok = 1;             
                //            bPowerFlag = FALSE; //nRetVal = TRUE;
                //            AxisMotor_Break(); 
                //          //  _3d_step = 1;
                //            break;
                //       }
                if(curPosition < 5)
                {
                    bPowerFlag = FALSE;            
                    AxisMotor_Break(); 
                    _3D_Min_Ok = 1;
                    _3d_step = 1;
                    break;
                }
                AxisMotor_UnClockRun();
                bPowerFlag = TRUE;
                _3D_Min_Ok = 0;
            }    
            break;
        case 1:
            if(Knead_Min_Ok)//wait for Knead_motor knead stop at min
            {
                if(Input_Get3DFrontSwitch()) 
                {
                    if(_3D_Max_Ok)
                    {
                        _3d_step = 0;
                        break;
                    }    
                    _3D_PosStop_TimeFlag = 1;
                    AxisMotor_Break(); 
                    bPowerFlag = FALSE; 
                    if(_3D_PosStop_Time >= 200)  //3d��������λ��ͣ��ʱ��
                    {
                        _3D_PosStop_TimeFlag = 0;
                        _3D_PosStop_Time = 0;
                        _3D_Max_Ok = 1;
                        _3d_step = 0;  
                        nRetVal = TRUE;
                    }
                    break;
                }
                if(curPosition > 36)
                {
                    if(_3D_Max_Ok)
                    {
                        _3d_step = 0;
                        break;
                    }
                    _3D_PosStop_TimeFlag = 1;
                    AxisMotor_Break(); 
                    bPowerFlag = FALSE;                      
                    if(_3D_PosStop_Time >= 200)
                    {
                        _3D_PosStop_TimeFlag = 0;
                        _3D_PosStop_Time = 0;
                        _3D_Max_Ok = 1;
                        _3d_step = 0;
                        nRetVal = TRUE;
                    }
                    break;
                }
                AxisMotor_ClockRun();
                bPowerFlag = TRUE;  
                _3D_Max_Ok = 0;
                break; 
            } 
        }
        break;   
    case STATE_RUN_AXIS_WALK:
    switch(_3D_step)
    {
    case 0:  
     if(curPosition >=36)
      { 
          bPowerFlag = FALSE;        
          AxisMotor_Break();
          _3D_step = 1;
          _3D_MaxOk = 1;
          break;
      }
      AxisMotor_ClockRun();//AxisMotor_UnClockRun();
      bPowerFlag = TRUE;   
      _3D_MaxOk = 0;
      break;
    case 1:            
         if(curPosition<=5)
         {  
              bPowerFlag = FALSE;            
              AxisMotor_Break();
              _3D_step = 2;
              break;
         }
         if(curPosition < 7) speed = _3D_SPEED_2;
          AxisMotor_UnClockRun();//AxisMotor_ClockRun();
          bPowerFlag = TRUE;      
          break;
    case 2:             
         if(curPosition >=36)
          {
              bPowerFlag = FALSE;
              AxisMotor_Break();
              if(_3D_StopFlag)
              {
                _3D_step = 3;
              }
              else
              {
                _3D_step = 1;
              }            
              _3D_MaxOk = 1;
              break;
          }
          AxisMotor_ClockRun();//AxisMotor_UnClockRun();
          bPowerFlag = TRUE;       
          break;
    case 3:
      _3D_step = 1;
      _3D_Press_Times++;
      if(_3D_Press_Times > stopLevel) //stopLevel--�϶�����
      {
        _3D_step=0;
        nRetVal = TRUE ;
        bPowerFlag = FALSE;
        AxisMotor_Break();
        _3D_step = 0;
        _3D_StopFlag = 0;
        _3D_MaxOk = 0;
        _3D_Press_Times = 0;
      }
     break;  
    default:
        _3D_step=0;
        break;  
  }
  break;
    case STATE_RUN_AXIS_REAL_POSITION: //3D���ʵ��λ��
        if(stopLevel >= AXIS_BEHIND_LIMIT)
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            break; 
        }
        stopPosition = stopLevel; //�˴�Ϊʵ��λ��ֵ
        if((curPosition <= stopPosition + 1) && (curPosition >= stopPosition - 1 ))
        { 
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            AxisMotor_Break();
            break;
        }
        if(curPosition < stopPosition ) 
        {
            goto AXIS_FORWARD;
        }
        goto AXIS_BEHIND ;
        break;    
    case STATE_RUN_AXIS_POSITION:
        if(stopLevel >= levelMax)
        {   //�������
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            AxisMotor_Break();
            break;
        }
        if(0 == stopLevel)
        {  //��Сλ��Ϊ���г̿���
            goto AXIS_BEHIND;
        }
        if(levelMax == stopLevel+1)
        {
            //���λ��Ϊǰ�г̿���
            goto AXIS_FORWARD;
        }
        
        switch(stopLevel)
        {
        default: 
        case 0: stopPosition = _3D_MIN_POSITION; break;
        case 1: stopPosition = _3D_MORE_MIN_POSITION; break;
        case 2: stopPosition = _3D_MED_POSITION; break;
        case 3: stopPosition = _3D_MORE_MED_POSITION; break;
        case 4: stopPosition = _3D_MAX_POSITION; break;
        }
        if((curPosition <= stopPosition + 2) && (curPosition >= stopPosition - 2 ))
        {  //����λ������
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            AxisMotor_Break();
            break;
        }
        if(curPosition < stopPosition ) 
        {
            goto AXIS_FORWARD;
        }
        goto AXIS_BEHIND ;
        break;
        /*
    case STATE_RUN_AXIS_RESET:    
        speed = _3D_SPEED_2;
        bDisableCheckCurrent = TRUE;
        AxisMotor_ClockRun();
        bPowerFlag = TRUE;
        break;
        */
    case STATE_RUN_AXIS_F_BEHIND:  //��Ħͷ��� ��Ħ������С���������г̿��ز�ͣ  
        if(Input_Get3DBackSwitch() || justPosition == AT_BACK_SWITCH) 
        {
            justPosition = AT_BACK_SWITCH;
        }  
        if(justPosition == AT_FRONT_SWITCH)
        {
            justPosition = AT_MIDDLE_SWITCH;
        }
        if(curPosition < 5) speed = _3D_SPEED_2;
        bDisableCheckCurrent = TRUE;
        //AxisMotor_ClockRun();
        AxisMotor_UnClockRun();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_AXIS_BEHIND:  
    AXIS_BEHIND:     
        if(Input_Get3DBackSwitch() || justPosition == AT_BACK_SWITCH) 
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            justPosition = AT_BACK_SWITCH;
            break;
        }  
        if(justPosition == AT_FRONT_SWITCH)
        {
            justPosition = AT_MIDDLE_SWITCH;
        }
        if(b3D_PositionError)
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            break;
        }
        if(curPosition < 5) speed = _3D_SPEED_2;
        bDisableCheckCurrent = TRUE;
        // AxisMotor_ClockRun();
        AxisMotor_UnClockRun();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_AXIS_F_FORWARD:   //��Ħͷ��ǰ ��Ħ�����Ӵ� ����ǰ�г̿��ز�ͣ
        if(Input_Get3DFrontSwitch() || justPosition == AT_FRONT_SWITCH) 
        {
            justPosition = AT_FRONT_SWITCH;
        }  
        if(justPosition == AT_BACK_SWITCH)
        {
            justPosition = AT_MIDDLE_SWITCH;
        }
        if(curPosition > 35) speed = _3D_SPEED_5;
        // AxisMotor_UnClockRun();
        AxisMotor_ClockRun();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_AXIS_FORWARD:     
    AXIS_FORWARD:     
        if(Input_Get3DFrontSwitch() )//|| justPosition == AT_FRONT_SWITCH) 
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            justPosition = AT_FRONT_SWITCH;
            break;
        }  
        if(justPosition == AT_BACK_SWITCH)
        {
            justPosition = AT_MIDDLE_SWITCH;
        }
        if(b3D_PositionError)
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            break;
        }
        if(curPosition > 35) speed = _3D_SPEED_5;
        ///AxisMotor_UnClockRun();
        AxisMotor_ClockRun();
        bPowerFlag = TRUE;
        break ;
    case STATE_RUN_AXIS_CIRCLE:
        switch(_3D_step)
        {
        case 0:  
            nRetVal = FALSE;
            if(Input_Get3DFrontSwitch())//(curPosition >=36)
            { 
                bPowerFlag = FALSE;        
                AxisMotor_Break();
                _3D_step = 1;
                break;
            }
            AxisMotor_ClockRun();
            bPowerFlag = TRUE;   
            break;
        case 1:   
            nRetVal = FALSE;
            if(Input_Get3DBackSwitch())//(curPosition<=5)
            {  
                bPowerFlag = FALSE;            
                AxisMotor_Break();
                _3D_step = 2;
                break;
            }
            AxisMotor_UnClockRun();
            bPowerFlag = TRUE; 
            break;
        case 2:
            nRetVal = TRUE ;
            _3D_step = 0;
            break;
        }
        break;
        /*********************����ǻ���ؿ�ʼ***********************/
    case STATE_RUN_HALF_CIRCLE_3:
        //speed = _3D_SPEED_6;
        //nRetVal = TRUE;
        switch(_3D_step)
        {
        default:           //cyw
        case 0:
            //if(Knead_Min_Ok)
            //{
            if(curPosition < 5)
            {
                bPowerFlag = FALSE;            
                AxisMotor_Break(); 
                _3D_PosStop_TimeFlag = 1;
                if(Knead_Max_Ok)
                { 
                    //_3D_Min_Ok = 1;
                    _3D_PosStop_TimeFlag = 0;
                    _3D_PosStop_Time = 0;
                    _3D_step = 1;
                    nRetVal = TRUE;
                    break;
                }
            }
            if(Knead_Max_Ok)
            {
                bPowerFlag = FALSE;            
                AxisMotor_Break(); 
                //_3D_Min_Ok = 1;
                _3D_PosStop_TimeFlag = 0;
                _3D_PosStop_Time = 0;
                _3D_step = 1; 
                nRetVal = TRUE;
                break;
            }
            if(Input_Get3DBackSwitch())//3D Motor go back
            {
                //_3D_Min_Ok = 1;             
                bPowerFlag = FALSE; //nRetVal = TRUE;
                AxisMotor_Break(); 
                //_3D_step = 1;
                _3D_PosStop_TimeFlag = 1;
                if(_3D_PosStop_Time >= 50)
                {  
                    if(Knead_Max_Ok)
                    {
                        _3D_PosStop_TimeFlag = 0;
                        _3D_PosStop_Time = 0;
                        _3D_step = 1;
                        nRetVal = TRUE;
                        break;
                    }
                    //_3D_Min_Ok = 1; 
                } 
            }
            if(_3D_PosStop_TimeFlag == 0)
            {
                speed = _3D_SPEED_4;
                //AxisMotor_ClockRun();
                AxisMotor_UnClockRun();
                bPowerFlag = TRUE;
            }
            //_3D_Min_Ok = 0;
            // } //   
            break;
        case 1:
            //if(Knead_Max_Ok)//wait for Knead_motor knead stop at max
            //{
            if(curPosition > 36)
            { 
                AxisMotor_Break();
                bPowerFlag = FALSE; 
                _3D_PosStop_TimeFlag = 1; 
                if(_3D_PosStop_Time >= 50)
                {
                    if(Knead_Min_Ok)
                    { 
                        _3D_PosStop_TimeFlag = 0;
                        _3D_PosStop_Time = 0;
                        _3D_step = 0;
                        nRetVal = TRUE;
                        
                        break;
                    }
                    //_3D_Max_Ok = 1;
                }
            }
            if(Knead_Min_Ok)
            { 
                //_3D_PosStop_TimeFlag = 1;
                AxisMotor_Break(); 
                bPowerFlag = FALSE;
                _3D_PosStop_TimeFlag = 0;
                _3D_PosStop_Time = 0;
                _3D_step = 0;
                break; 
            }
            if(Input_Get3DFrontSwitch()) 
            {
                AxisMotor_Break();
                bPowerFlag = FALSE;
                _3D_PosStop_TimeFlag = 1;
                //_3d_step = 0;
                if(_3D_PosStop_Time >= 50)
                {
                    //_3D_Max_Ok = 1;
                    if(Knead_Min_Ok)
                    {
                        _3D_PosStop_TimeFlag = 0;
                        _3D_PosStop_Time = 0;
                        _3D_step = 0;
                        nRetVal = TRUE;
                        break;
                    }
                }
            }
            if(_3D_PosStop_TimeFlag == 0)
            {
                speed = _3D_SPEED_4;
                //AxisMotor_UnClockRun();
                AxisMotor_ClockRun();
                bPowerFlag = TRUE;  
                //_3D_Max_Ok = 0;
            }
            break;
        }
        break;
        /*********************����ǻ���ؽ���***********************/
        
    case STATE_AXIS_IDLE:
        nRetVal = TRUE ;
        AxisMotor_Break();
        bPowerFlag = FALSE;
        break ;
    default://�쳣����
        break ;
    }
    //��Դ���ֵĴ���
    if(bPowerFlag == TRUE)
    {
        //AxisMotor_SetSpeed(speed);
        
        switch(speed)
        {
        default: 
        case _3D_SPEED_1: setPWM = _3D_SPEED_1_PWM;break;
        case _3D_SPEED_2: setPWM = _3D_SPEED_2_PWM;break;
        case _3D_SPEED_3: setPWM = _3D_SPEED_3_PWM;break;
        case _3D_SPEED_4: setPWM = _3D_SPEED_4_PWM;break;
        case _3D_SPEED_5: setPWM = _3D_SPEED_5_PWM;break;
        case _3D_SPEED_6: setPWM = _3D_SPEED_6_PWM;break;
        case _3D_SPEED_7: setPWM = _3D_SPEED_7_PWM;break;
        case _3D_SPEED_8: setPWM = _3D_SPEED_8_PWM;break;
        case _3D_SPEED_9: setPWM = _3D_SPEED_8_PWM;break;
        case _3D_SPEED_10: setPWM = _3D_SPEED_8_PWM;break;
        }
        AxisMotor_Set_Pwm_Data(setPWM);
        bDisableCheckCurrent = FALSE;  
    }
    else
    {
        bDisableCheckCurrent = TRUE;  
        bEnableCheckCurrent = FALSE;
        AxisPower_Off();
    }
    return nRetVal ;
}
void AxisMotor_Reset(void)
{
  GPIO_PinOutClear(AXIS_MOTOR_RESET_PORT, AXIS_MOTOR_RESET_BIT);
}
void AxisMotor_Reset_Cancel(void)
{
  GPIO_PinOutSet(AXIS_MOTOR_RESET_PORT, AXIS_MOTOR_RESET_BIT);
}

int AxisMotor_Get_Fault(void)
{
  if(GPIO_PinInGet(AXIS_MOTOR_FAULT_PORT, AXIS_MOTOR_FAULT_BIT))
    return AXIS_MOTOR_NORMAL;
  return AXIS_MOTOR_FAIL;
}

unsigned int AxisRelay_Get(void)
{
  return(GPIO_PinOutGet(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT));
}

unsigned int AxisMotor_GetDirection(void)
{
  if(GPIO_PinOutGet(AXIS_MOTOR_PHASE_PORT, AXIS_MOTOR_PHASE_BIT))
  {
    return AXIS_MOTOR_GO_FORWARD;
  }
  else
  {
    return AXIS_MOTOR_GO_BACK;
  } 
}

void Axis_5ms_Int(void)
{
  static unsigned int timer5ms = 0;
  if(bDisableCheckCurrent)  
  {
    timer5ms = 0;
    return;
  }
  timer5ms++;
  if(timer5ms >= 4)
  {
    bEnableCheckCurrent = true;
  }
}

void AxisMotor_UpdataPosition(void)
{
  bUpdataPosition = true; 
}
unsigned short AxisMotor_CurrentFiter(unsigned short current)
{
  
  static unsigned short axisCurrent[8]={0,0,0,0,0,0,0,0};
  unsigned int  w_SUM;
  unsigned int aveaxisCurrent;
  
  
  //current = TaxisCurrent[0+wghc];
  
  w_SUM = axisCurrent[7] + axisCurrent[6] + axisCurrent[5] + axisCurrent[4]+
    axisCurrent[3] + axisCurrent[2]+ axisCurrent[1] + axisCurrent[0];
  aveaxisCurrent = w_SUM / 8; 
  
  axisCurrent[0] =( 7*aveaxisCurrent + current )>>3;
  axisCurrent[7] = axisCurrent[6];
  axisCurrent[6] = axisCurrent[5];
  axisCurrent[5] = axisCurrent[4];
  axisCurrent[4] = axisCurrent[3];
  axisCurrent[3] = axisCurrent[2];
  axisCurrent[2] = axisCurrent[1];
  axisCurrent[1] = axisCurrent[0];
  //axisCurrent[0] = lastaxisCurrent;
  
  return(axisCurrent[0]);
}

/*
���������������3D�����ǰ��ĵ��� һ�� ��_3D_FULL_POINT+1��* AXIS_BEHIND_LIMIT����
���� positionCount ��¼Ϊ�ڼ�������������Ϊ0-10��11����
*/

//bool bShouldDelay;
#define  BODY_TOUCHED     1
#define  BODY_NO_TOUCHED  0
//�粿λ�ü���ź�    


unsigned char ncurrentcnt;

unsigned short curPositiontest,prepositionCount;
unsigned char ncurrentcou =0;
unsigned short voltagetemp;
void AxisMotor_StorageCurrent(unsigned int positionCount,unsigned int walkPosition)
{
  /*
  unsigned short voltage;
  unsigned short curPosition = Input_GetAxisMotorPosition();
  curPositiontest =walkPosition;
  //  if(!bEnableCheckCurrent) return;
  //  if(!ADC_GetUpdata()) return;
  //if(positionCount > _3D_FULL_POINT)//10
  //{
  //  return;
  //}
  //if(curPosition >= AXIS_BEHIND_LIMIT) return;//40
  if(by_currentTimer_Flag == FALSE) return;
  if( by_currentTimer_Flag == TRUE)//100ms
  {
  by_currentTimer_Flag = FALSE;
  if(ncurrentcou <50)
  {
  ncurrentcou++;
  if(prepositionCount == positionCount)
  {
  ncurrentcnt ++;
}
      else
  {
  ncurrentcnt = 0;
}
}
}
  ADC_Get_Voltage(ADC_Vaxis,&voltage); 
  voltagetemp = AxisMotor_CurrentFiter(voltage);
  n3DMotorCurrent[positionCount].current[ncurrentcnt] = voltagetemp;//ncurrentcou //
  n3DMotorCurrent[positionCount].position = walkPosition;
  
  if(  (voltagetemp <600)&&(walkPosition >=280) &&(ncurrentcou >15) ) //1s
  {
  bShouldDelay =1; 
}
  if  (voltagetemp >=600)
  {
  ncurrentcou =0;
  bShouldDelay =0;
}
  
  prepositionCount = positionCount;
}
  void AxisMotor_StorageCurrentClear()
  {
  unsigned char i,j;
  for(i=0;i<21;i++)
  {
  n3DMotorCurrent[i].position = 0;
  for(j=0;j<40;j++)
  {
  n3DMotorCurrent[i].current[j] = 0;//AxisMotor_CurrentFiter(voltage);
}
}
  ncurrentcnt =0;
  prepositionCount = 0;
  bShouldDelay = 0;*/
}


void reArangeArray(unsigned int* array,int length)
{
  unsigned int temp,temp1;
  for(int i = 0; i < length;i++){
    temp = array[i];
    for(int j = i + 1; j < length;j++){
      if(array[j] < temp){
        temp1 = array[j];
        array[j] = temp;
        temp = temp1;
      }
    }
    array[i] = temp;
  }
}

//Ϊ�˷�ֹ������ͬʱ���ں������㣬���ݰ���С��������
void AxisMotor_CurrentAdj(void)
{
  int i,j;
  //��������
  for(i=0;i <= _3D_FULL_POINT;i++)  //���µ�����
  {
    reArangeArray(&n3DMotorCurrent[i].current[2],AXIS_BEHIND_LIMIT-2);
    n3DMotorCurrent[i].current[1] = n3DMotorCurrent[i].current[2]; //0��1�ĵ���ֵ���ȶ���ֱ��ȡ2�ĵ���ֵ
    n3DMotorCurrent[i].current[0] = n3DMotorCurrent[i].current[2];
  }
  
  //  �����Ѿ�����С���������
  unsigned int MaxCurrent,MinCurrent,currentSegments;
  
  for(i=0;i <= _3D_FULL_POINT;i++)  //���µ�����
  {
    MaxCurrent = n3DMotorCurrent[i].current[AXIS_BEHIND_LIMIT-1];
    MinCurrent = n3DMotorCurrent[i].current[0];
    currentSegments = (MaxCurrent - MinCurrent)/_3D_POSITION_POINT; //ȡ��ÿһ�εĵ�����ֵ
    //��С����һ������λ��
    n3DMotorCurrent[i]._3D_Position[0] = 0;
    //��󣨵��ģ�����λ��
    n3DMotorCurrent[i]._3D_Position[4] = AXIS_BEHIND_LIMIT;
    //ȡ�ڶ�����λ��
    n3DMotorCurrent[i]._3D_Position[1] =  n3DMotorCurrent[i]._3D_Position[0];  //�ó�ֵ
    for(j=n3DMotorCurrent[i]._3D_Position[0];j<AXIS_BEHIND_LIMIT;j++)
    {
      if(n3DMotorCurrent[i].current[j] >= (currentSegments + MinCurrent))
      {
        n3DMotorCurrent[i]._3D_Position[1] =  j;
        break;
      }
    }
    //ȡ�м��������λ��
    n3DMotorCurrent[i]._3D_Position[2] =  n3DMotorCurrent[i]._3D_Position[1];  //�ó�ֵ
    for(j=n3DMotorCurrent[i]._3D_Position[1];j<AXIS_BEHIND_LIMIT;j++)
    {
      if(n3DMotorCurrent[i].current[j] >= (currentSegments*2 + MinCurrent))
      {
        n3DMotorCurrent[i]._3D_Position[2] =  j;
        break;
      }
    }
    
    //ȡ���ĵ���λ��
    n3DMotorCurrent[i]._3D_Position[3] =  n3DMotorCurrent[i]._3D_Position[2];  //�ó�ֵ
    for(j=n3DMotorCurrent[i]._3D_Position[2];j<AXIS_BEHIND_LIMIT;j++)
    {
      if(n3DMotorCurrent[i].current[j] >= (currentSegments*3 + MinCurrent))
      {
        n3DMotorCurrent[i]._3D_Position[3] =  j;
        break;
      }
    }      
  }
}          

void  _3D_Set_3D_data(void)
{
  int i;
  for(i=0;i <= _3D_FULL_POINT;i++)  
  {
    n3DMotorCurrent[i].position = i*30;
    n3DMotorCurrent[i]._3D_Position[0] = 0;
    n3DMotorCurrent[i]._3D_Position[1] = 10;
    n3DMotorCurrent[i]._3D_Position[2] = 15;
    n3DMotorCurrent[i]._3D_Position[2] = 25;
    n3DMotorCurrent[i]._3D_Position[2] = 40;
  }
}

unsigned int _3D_Get_3D_count(unsigned int walkCount,unsigned int strength)
{
  return(n3DMotorCurrent[walkCount]._3D_Position[strength]);
}

unsigned int _3D_GetWalkCount(unsigned int walkPosition)
{
  int i;
  for(i=0; i<= _3D_FULL_POINT; i++)
  {
    if(n3DMotorCurrent[i].position >= walkPosition)
    {
      return i;
    }
  }
  return 0;
}

void AxisMotor_100msInt(void)
{
  _3D_PositionErrorCount++; 
  //by_currentTimer_Flag = TRUE;
}
void AxisMotor_10msInt(void)
{
  nAxisLoss++;
  if(nAxisLoss > 2)
  {
    TIMER_CompareBufSet(AXIS_MOTOR_TIMER, AXIS_MOTOR_TIMER_CHANNEL, 0);
  }
}

