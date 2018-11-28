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
//--------新手法添加的参数（AxisMotor.c文件使用）start---------
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
//此变量为5个力度点的电流值 0：最大，1：较大，2：中：3：较小 4：最小
//unsigned int AxisMotorStrength[_3D_POSITION_POINT];
//机芯依据行程位置共取_3D_FULL_POINT+1个电流采样点，每个电流采样点有5个电流值
//第一个电流采样点为0 最后一个电流采样点为肩膀位置，中间还有9个点
st_n3D_Data   n3DMotorCurrent[_3D_FULL_POINT+1]; //肩膀位置以下电流采样点和肩膀位置电流采样点 
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
  unsigned short adc24;      //此处的电压值已经扩大了100倍
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= AXIS_SET_VOLTAGE/100) 
  {
    return setDuty;        //电压值偏低，返回预设值
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
  unsigned int scale = setVoltage / adc24; //计算与设定电压的比例值
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
3D 马达控制程序
stopLevel 在STATE_RUN_AXIS_REAL_POSITION时为实际位置
stopLevel 在STATE_RUN_AXIS_POSITION时为位置等级
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
    //   if(!SignalBoard_isOK())//读不到3D行程开关会停
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
    
    //  if(!SignalBoard_isOK())//100ms 行走电机行程开关会停
    //  {
    //    AxisMotor_Break();
    //    return(unsigned char)(TRUE);
    //    
    //  }
    /**********判断3D脉冲信号是否正常***********************/  
    if(AxisMotor_IsRun())
    { //3D马达是运行的
        if(oldPosition == curPosition)
        {
            if(_3D_PositionErrorCount > 5) //1.5秒
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
    {  //3D马达是停止的
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
                    if(_3D_PosStop_Time >= 200)  //3d电机在最大位置停留时间
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
      if(_3D_Press_Times > stopLevel) //stopLevel--上顶次数
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
    case STATE_RUN_AXIS_REAL_POSITION: //3D马达实际位置
        if(stopLevel >= AXIS_BEHIND_LIMIT)
        {
            bPowerFlag = FALSE;
            nRetVal = TRUE;
            AxisMotor_Break();
            break; 
        }
        stopPosition = stopLevel; //此处为实际位置值
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
        {   //数据溢出
            bPowerFlag = FALSE;
            nRetVal = TRUE ;
            AxisMotor_Break();
            break;
        }
        if(0 == stopLevel)
        {  //最小位置为后行程开关
            goto AXIS_BEHIND;
        }
        if(levelMax == stopLevel+1)
        {
            //最大位置为前行程开关
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
        {  //到达位置区域
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
    case STATE_RUN_AXIS_F_BEHIND:  //按摩头向后 按摩力道减小，碰到后行程开关才停  
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
    case STATE_RUN_AXIS_F_FORWARD:   //按摩头向前 按摩力道加大 碰到前行程开关才停
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
        /*********************轻柔呵护相关开始***********************/
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
        /*********************轻柔呵护相关结束***********************/
        
    case STATE_AXIS_IDLE:
        nRetVal = TRUE ;
        AxisMotor_Break();
        bPowerFlag = FALSE;
        break ;
    default://异常处理
        break ;
    }
    //电源部分的处理
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
这个程序用来计算3D马达向前伸的电流 一共 （_3D_FULL_POINT+1）* AXIS_BEHIND_LIMIT个点
参数 positionCount 记录为第几个电流采样点为0-10共11个点
*/

//bool bShouldDelay;
#define  BODY_TOUCHED     1
#define  BODY_NO_TOUCHED  0
//肩部位置检测信号    


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

//为了防止检测错误，同时便于后续计算，数据按从小到大排序
void AxisMotor_CurrentAdj(void)
{
  int i,j;
  //整理数据
  for(i=0;i <= _3D_FULL_POINT;i++)  //上下电流点
  {
    reArangeArray(&n3DMotorCurrent[i].current[2],AXIS_BEHIND_LIMIT-2);
    n3DMotorCurrent[i].current[1] = n3DMotorCurrent[i].current[2]; //0和1的电流值不稳定，直接取2的电流值
    n3DMotorCurrent[i].current[0] = n3DMotorCurrent[i].current[2];
  }
  
  //  电流已经按从小到大调整好
  unsigned int MaxCurrent,MinCurrent,currentSegments;
  
  for(i=0;i <= _3D_FULL_POINT;i++)  //上下电流点
  {
    MaxCurrent = n3DMotorCurrent[i].current[AXIS_BEHIND_LIMIT-1];
    MinCurrent = n3DMotorCurrent[i].current[0];
    currentSegments = (MaxCurrent - MinCurrent)/_3D_POSITION_POINT; //取出每一段的电流差值
    //最小（第一）电流位置
    n3DMotorCurrent[i]._3D_Position[0] = 0;
    //最大（第四）电流位置
    n3DMotorCurrent[i]._3D_Position[4] = AXIS_BEHIND_LIMIT;
    //取第二电流位置
    n3DMotorCurrent[i]._3D_Position[1] =  n3DMotorCurrent[i]._3D_Position[0];  //置初值
    for(j=n3DMotorCurrent[i]._3D_Position[0];j<AXIS_BEHIND_LIMIT;j++)
    {
      if(n3DMotorCurrent[i].current[j] >= (currentSegments + MinCurrent))
      {
        n3DMotorCurrent[i]._3D_Position[1] =  j;
        break;
      }
    }
    //取中间第三电流位置
    n3DMotorCurrent[i]._3D_Position[2] =  n3DMotorCurrent[i]._3D_Position[1];  //置初值
    for(j=n3DMotorCurrent[i]._3D_Position[1];j<AXIS_BEHIND_LIMIT;j++)
    {
      if(n3DMotorCurrent[i].current[j] >= (currentSegments*2 + MinCurrent))
      {
        n3DMotorCurrent[i]._3D_Position[2] =  j;
        break;
      }
    }
    
    //取第四电流位置
    n3DMotorCurrent[i]._3D_Position[3] =  n3DMotorCurrent[i]._3D_Position[2];  //置初值
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

