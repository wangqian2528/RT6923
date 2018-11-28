#include "EFM32_def.h"
#include "EFM32_types.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "input.h"
#include "ADC_Scan.h"
#include "WalkMotor.h"
#include "signalUart_new.h"

#include "Valve.h"//
#include "backaction.h"

//------新程序增加参数（walkMotor.c文件使用）start-------------
unsigned char Walk_Motor_State;
extern unsigned char upWalkRun;
extern unsigned char downWalkRun;
unsigned char WalkTimeFlag;
unsigned int WalkTime;
extern unsigned int bkneadTime;
//extern bool _3D_walkflag;
bool _3D_StopFlag;
extern bool _3D_MaxOk;
bool Walk_StopFlag;
//extern bool downWalkRunOver;
bool pwm_time_flag;
unsigned char pwm_time; 
extern unsigned char KneadState;
int Walk_PWM;
unsigned short RealTime_Position;
extern bool Walk_CheckPoint;
bool checkover1,checkover2;
bool downflag,upflag,downflag2,upflag2;
//----------------------end----------------------


#define TOP_POSITION 	360//397//8600 215  //肩膀位置的最高点
volatile unsigned char nWalkLoss;
//static bool bFalg; 
extern bool bRestSleepStatus;
extern unsigned char nBackSubRunMode ;


extern unsigned char bWalkSlowFlag ;
extern bool bWalkPWMFlag ;



void WalkMotor_Initial_IO(void)
{
    GPIO_PinModeSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT, WALK_MOTOR_RESET_MODE, 0);
    GPIO_PinModeSet(WALK_MOTOR_ENBL_PORT, WALK_MOTOR_ENBL_BIT, WALK_MOTOR_ENBL_MODE, 0);
    GPIO_PinModeSet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT, WALK_MOTOR_PHASE_MODE, 0);
    GPIO_PinModeSet(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT, WALK_MOTOR_DECAY_MODE, 0);
    GPIO_PinModeSet(WALK_MOTOR_FAULT_PORT, WALK_MOTOR_FAULT_BIT, WALK_MOTOR_FAULT_MODE, 1);
    
    TIMER_InitCC_TypeDef timerCCInit = WALK_MOTOR_Timer_CCInit;
    TIMER_InitCC(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, &timerCCInit);
    WALK_MOTOR_TIMER->ROUTE |= (WALK_MOTOR_ROUTE_EN | WALK_MOTOR_ROUTE_LOCATION); 
    TIMER_TopSet(WALK_MOTOR_TIMER, WALK_MOTOR_DEFAULT_TOP);
    TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, 0);
    TIMER_Init_TypeDef timerInit = WALK_MOTOR_Timer_Init;
    TIMER_Init(WALK_MOTOR_TIMER, &timerInit);
}

void WalkMotor_10ms_Int(void)
{
//    bFalg = true; 
}
unsigned int WalkMotor_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //此处的电压值已经扩大了100倍
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= WALK_SET_VOLTAGE/100) 
  {
    return setDuty;        //电压值偏低，返回预设值
  }
  unsigned int scale = WALK_SET_VOLTAGE / adc24; //计算与设定电压的比例值
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;
  if(yushu > 50) setDuty++;
  return setDuty; 
}

void WalkMotor_Set_Pwm_Data(unsigned long ulDuty)
{
    if(ulDuty == 0)
    {
        TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, ulDuty);
        return;
    }
    if(WalkMotor_Get_Fault() == WALK_MOTOR_FAIL)
    {
      WalkMotor_Reset();
      __no_operation();
      __no_operation();
      WalkMotor_Reset_Cancel();
    }
   WalkMotor_VoltageAdj(ulDuty);
    TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, ulDuty);
}
//0710
static void WalkPower_On(void)
{
    // WalkMotor_Set_Pwm_Data(WALK_MOTOR_DEFAULT_TOP);
    if(KneadState==KNEAD_MED_MED 
       || KneadState==KNEAD_MAX_MED
           || KneadState==KNEAD_MAX_MAX 
               || KneadState==KNEAD_RUN_WALK
                   || Walk_Motor_State == _3D_WALK
                       || Walk_Motor_State == PWM_WALK
                           || Walk_Motor_State==STATE_RUN_PWM_ABS
                               || Walk_Motor_State == UP_DOWN_WALK
                                   || Walk_Motor_State == STATE_RUN_STOP_WALK_KNEAD_3)
    {
        WalkMotor_Set_Pwm_Data(Walk_PWM);
    }
    
    switch(bWalkSlowFlag)
    {
    default:
        WalkMotor_Set_Pwm_Data(0);//50//60
        break;
    case 0:
        if(bWalkPWMFlag==FALSE)
        {
            WalkMotor_Set_Pwm_Data(130);
        }
        else
        {
            WalkMotor_Set_Pwm_Data(95);//89//87//85
        }
        break;
    case 1:
        WalkMotor_Set_Pwm_Data(56);//50//56//60//50//60
        break;
    case 2:
        WalkMotor_Set_Pwm_Data(42);//40//45//50//50//60
        break;
    case 3:
        WalkMotor_Set_Pwm_Data(33);//30//38//50//60
        break;
    case 4:
        WalkMotor_Set_Pwm_Data(40);//36//50//60
        break;   
    case 5:
        WalkMotor_Set_Pwm_Data(110);//105
        break;    
    }
}
 void WalkPower_Off(void)
{
    WalkMotor_Set_Pwm_Data(0);
}
unsigned int WalkRelay_Get(void)
{
    return(GPIO_PinOutGet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT));
}

unsigned int WalkMotor_GetDirection(void)
{
    if(!GPIO_PinOutGet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT) == 0)
    {
      return WALK_MOTOR_GO_UP;
    }
    return WALK_MOTOR_GO_DOWN;
}

unsigned int WalkPower_Get(void)
{
    unsigned long  ulDuty;
    ulDuty = TIMER_CompareBufGet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL);
    if(ulDuty > 0) return WALK_MOTOR_POWER_ON;
    else return WALK_MOTOR_POWER_OFF;
}

static void WalkMotor_Up(void)
{
    GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
  //  GPIO_PinOutClear(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    
    GPIO_PinOutSet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
}
static void WalkMotor_Down(void)
{
    GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
   // GPIO_PinOutSet(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    GPIO_PinOutClear(WALK_MOTOR_PHASE_PORT, WALK_MOTOR_PHASE_BIT);
    
    GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
}
static void WalkMotor_Break(void)
{
    GPIO_PinOutSet(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);//GPIO_PinOutClear(WALK_MOTOR_DECAY_PORT, WALK_MOTOR_DECAY_BIT);
    WalkMotor_Set_Pwm_Data(0);
}
static void WalkMotor_Reset(void)
{
    GPIO_PinOutClear(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
}
static void WalkMotor_Reset_Cancel(void)
{
    GPIO_PinOutSet(WALK_MOTOR_RESET_PORT, WALK_MOTOR_RESET_BIT);
}

int WalkMotor_Get_Fault(void)
{
    if(GPIO_PinInGet(WALK_MOTOR_FAULT_PORT, WALK_MOTOR_FAULT_BIT))
        return WALK_MOTOR_NORMAL;
    return WALK_MOTOR_FAIL;
}

////BackPad motor control function
//unsigned char WalkMotor_Control(unsigned char nFinalWalkMotorState,unsigned short stopPosition)
//{
//    unsigned char RetVal ;
//    bool bPowerFlag;
//    RetVal = FALSE ;
//    static bool init_flag = FALSE; 
//    unsigned short curPosition = Input_GetWalkMotorPosition();
//    nWalkLoss = 0;
//
//     static unsigned char walkStep = 0;
//   
//
//    if(!SignalBoard_isOK())//100ms 读不到行程开关位置电机停止运行
//    {
//     WalkMotor_Break();
//     WalkPower_Off();
//     return(unsigned char)(TRUE);
//      
//    }
//    
//  //   #ifdef SELECT_3D
//  //  if(!UartLeg_Get3DMessage_RXStatus())
//  //  {
//   //  WalkMotor_Break();
//   //  WalkPower_Off();
//    // return(unsigned char)(TRUE);
//      
//  //  }
//   //   #endif
//    
//    
////#ifdef SELECT_3D
//  if(!SignalBoard_isOK())
//   {
//     WalkMotor_Break();
//     WalkPower_Off();
//     return(unsigned char)(TRUE);
//   }
////#endif
//    switch(nFinalWalkMotorState)
//    {
//      case WALK_UP_PULSE:
//      if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//      {
//        Input_SetWalkMotorPosition(TOP_POSITION);
//        bPowerFlag= FALSE;
//        WalkMotor_Break();
//        init_flag = FALSE;
//        RetVal = TRUE ;
//        break;
//      }
//      if(!init_flag)
//      {
//        RealTime_Position = curPosition;
//        init_flag = TRUE;//保证在到达位置前只获取一次位置
//      }
//      if((curPosition >= RealTime_Position+stopPosition))
//      {
//         init_flag = FALSE;
//         bPowerFlag= FALSE;
//         WalkMotor_Break();
//         RetVal = TRUE ;
//      }
//      else
//      {
//          WalkMotor_Up();
//          bPowerFlag= TRUE;
//      }
//      break;
//      
//     case WALK_DOWN_PULSE:
//      if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//      {
//        Input_SetWalkMotorPosition(0);
//        bPowerFlag= FALSE;
//        WalkMotor_Break();
//        init_flag = FALSE;
//        RetVal = TRUE ;
//        break;
//      }
//      if(!init_flag)
//      {
//        RealTime_Position = curPosition;
//        init_flag = TRUE;//保证在到达位置前只获取一次位置
//      }
//      if((curPosition <= RealTime_Position-stopPosition) && (curPosition > RealTime_Position-stopPosition-3))
//      {
//         init_flag = FALSE;
//         bPowerFlag= FALSE;
//         WalkMotor_Break();
//         RetVal = TRUE ;
//      }
//      else
//      {
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//      }
//      break;  
//    case UP_DOWN_WALK:
//      RetVal = TRUE ;
//      Walk_PWM = 90; 
//      if(downWalkRun)
//      {
//        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            break;
//          }  
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//      }
//      else
//      {
//        bPowerFlag= FALSE;
//        WalkMotor_Break(); 
//      }
//      if(upWalkRun)
//      {
//         if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//            {
//              Input_SetWalkMotorPosition(TOP_POSITION);
//              bPowerFlag= FALSE;
//              WalkMotor_Break();      
//              break;
//            }
//            WalkMotor_Up();
//            bPowerFlag= TRUE;  
//            break;
//      }
//      else
//      {
//        bPowerFlag= FALSE;
//        WalkMotor_Break();
//      }
//      break;
//        
//    case PWM_WALK:
//      switch(walkStep)
//      {
//        case 0:
//        if(downWalkRun)
//        {
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            walkStep = 1;
//            pwm_time_flag = 0;
//            pwm_time = 0;
//            RetVal = TRUE ;
//            downWalkRun = FALSE;
//            break;
//          }
//          Walk_PWM = 110; 
//          upWalkRun = 0;
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//      }
//      else
//      {  
//        WalkMotor_Break();
//        walkStep = 1;
//        bPowerFlag= FALSE;
//      } 
//      break;
//      case 1:
//         Walk_PWM = 120; 
//         if(upWalkRun)
//         {
//            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//            {
//              Input_SetWalkMotorPosition(TOP_POSITION);
//              bPowerFlag= FALSE;
//              RetVal = TRUE ;
//              WalkMotor_Break();      
//              upWalkRun = FALSE;
//              pwm_time_flag = 0;
//              pwm_time = 0;
//              walkStep = 0;
//              break;
//            }
//            Walk_PWM = 120;    
//            WalkMotor_Up();
//            bPowerFlag= TRUE;  
//            break;
//          }
//          else 
//          {
//            WalkMotor_Break();
//            walkStep = 0;
//            bPowerFlag= FALSE;
//            RetVal = TRUE ;
//         }
//         break;
//      }
//      break;
//       case _3D_WALK:             //add by wby 20161223
//      if(!_3D_MaxOk)
//      {
//        bPowerFlag= FALSE;
//        WalkMotor_Break();
//        break;
//      }
//      Walk_PWM = 110;
//      if(curPosition < stopPosition-3)
//      {
//          if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//          {
//              Input_SetWalkMotorPosition(TOP_POSITION);
//              bPowerFlag = FALSE;
//              RetVal = TRUE ;
//              WalkMotor_Break();
//              _3D_StopFlag = 1;
//              break;
//          }
//          WalkMotor_Up();
//          bPowerFlag= TRUE;
//          _3D_StopFlag = 0;
//          break;
//      }
//       if(curPosition > stopPosition+3)
//       {
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//            {
//                Input_SetWalkMotorPosition(0);
//                bPowerFlag = FALSE;
//                RetVal = TRUE ;
//                WalkMotor_Break();
//                _3D_StopFlag = 1;
//                break;
//            }
//            WalkMotor_Down();
//            bPowerFlag = TRUE;
//            _3D_StopFlag = 0;
//            break;
//       }
//        bPowerFlag= FALSE;
//        RetVal = TRUE ;
//        WalkMotor_Break();
//        _3D_StopFlag = 1;
//        break;
//     
//    case STATE_RUN_STOP_WALK_KNEAD:           //add by wby 20161223
//      Walk_PWM = 120;
//      switch(walkStep)
//      {
//        case 0:
//        if(downWalkRun)
//        {
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            walkStep = 1;
//            downWalkRun = FALSE;
//            break;
//          }  
//          upWalkRun = 0;
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//        }
//        else
//        {    
//         bPowerFlag= FALSE;
//            WalkMotor_Break();
//            walkStep = 1;
//        }
//        break;
//        
//    case 1:
//      if(upWalkRun)
//      {
//        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//        {
//          Input_SetWalkMotorPosition(TOP_POSITION);
//          bPowerFlag= FALSE;
//         // RetVal = TRUE ;
//          WalkMotor_Break();      
//          upWalkRun = FALSE;
//          WalkTimeFlag = FALSE;
//          WalkTime = FALSE;
//         //Walk_StopFlag = 1;
//          walkStep = 0;
//          break;
//        }
//        WalkMotor_Up();
//        bPowerFlag= TRUE;  
//        break;
//      }
//      else 
//      {
//       bPowerFlag= FALSE;
//            WalkMotor_Break(); 
//            walkStep = 0;
//             RetVal = TRUE ;
//      }
//      break;
//    }      
//    break;
//    case STATE_RUN_LONG_WALK_KNEAD:   //上下PWM差来实现总体行走            //add by wby 20161223
//       if(curPosition > stopPosition-3 && curPosition < stopPosition+3)
//       {
//          walkStep = 0;
//          bPowerFlag= FALSE;
//          WalkMotor_Break();
//          RetVal = TRUE ;
//          downWalkRun = 0;
//          upWalkRun = 0;
//          Walk_StopFlag = 1;
//          break;
//       }
//      Walk_StopFlag = 0;
//      switch(walkStep)
//      {
//        case 0:
//        if(downWalkRun)
//        {
//          if(curPosition > stopPosition+3)
//          {
//              Walk_PWM=131;
//          }
//          else if(curPosition < stopPosition-3)
//          {
//              Walk_PWM=100;
//          }
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            walkStep = 1;
//            downWalkRun = FALSE;
//            break;
//          }  
//          //upWalkRun = 0;
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//        }
//        else
//        {
//           WalkMotor_Break();
//           walkStep = 1;
//           bPowerFlag= FALSE;
//        }
//        break;
//        
//    case 1:
//      if(upWalkRun)
//      {
//        if(curPosition > stopPosition+3)
//        {
//            Walk_PWM=100;
//        }
//        else if(curPosition < stopPosition-3)
//        {
//           Walk_PWM=131;
//        } 
//        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//        {
//          Input_SetWalkMotorPosition(TOP_POSITION);
//          bPowerFlag= FALSE;
//          WalkMotor_Break();      
//          upWalkRun = FALSE;
//          WalkTimeFlag = FALSE;
//          WalkTime = FALSE;
//          walkStep = 0;
//          break;
//        }
//        WalkMotor_Up();
//        bPowerFlag= TRUE;  
//        break;
//      }
//      else 
//      {
//         WalkMotor_Break();
//         bPowerFlag= FALSE;
//         walkStep = 0;        
//      }
//      break;
//    }      
//    break;   
//    case STATE_RUN_PWM_ABS:        //PWM差值积累形成总体上下行走--- 110~90的差值                          //add by wby 20161223   
//      //Walk_CheckPoint：保证中中揉时，在上行时检测行程位置
//      if(Walk_CheckPoint && curPosition > stopPosition-3 && curPosition < stopPosition+3)
//      {
//        walkStep = 0;
//        bPowerFlag= FALSE;
//        WalkMotor_Break();
//        RetVal = TRUE ;
//        downWalkRun = 0;
//        upWalkRun = 0;
//        Walk_StopFlag = 1;
//        downflag=0;
//        upflag=0;
//        downflag2=0;
//        upflag2=0;
//        checkover1 = 0;
//        checkover2 = 0;
//        break;
//      }
//      Walk_StopFlag = 0;
//      switch(walkStep)
//      {
//        case 0:
//        if(downWalkRun)
//        {
//            if(curPosition > stopPosition && !checkover1)
//            {           
//              downflag=1;
//              upflag = 0;
//              checkover1=1;
//            }
//            else if(curPosition < stopPosition && !checkover1)
//            {
//              upflag=1;
//              downflag = 0;
//              checkover1=1;
//            }
//           if(downflag) 
//           {
//             Walk_PWM=110;
//           }
//           if(upflag)
//           {
//             Walk_PWM = 90;
//           }
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            downWalkRun = FALSE;
//            walkStep = 1;
//            break;
//          }  
//          upWalkRun = 0;
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//        }
//        else
//        {
//           WalkMotor_Break();
//           walkStep = 1;
//           bPowerFlag= FALSE;
//        }
//        break; 
//    case 1:
//      if(upWalkRun)
//      {
//        if(curPosition > stopPosition && !checkover2)
//        {
//          checkover2 = 1;
//          downflag2 = 1;
//          upflag2 = 0;
//        }
//        else if(curPosition > stopPosition && !checkover2)
//        {
//          checkover2 = 1;
//          upflag2=1;
//          downflag2 = 0;
//        }
//        if(downflag2)
//        {
//          Walk_PWM=90;
//        }
//        else if(upflag2)
//        {
//          Walk_PWM=110;
//        }
//        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//        {
//          Input_SetWalkMotorPosition(TOP_POSITION);
//          bPowerFlag= FALSE;
//          WalkMotor_Break();      
//          upWalkRun = FALSE;
//          WalkTimeFlag = FALSE;
//          WalkTime = FALSE;
//          walkStep = 0;
//          break;
//        }
//        downWalkRun = 0;
//        WalkMotor_Up();
//        bPowerFlag= TRUE;  
//        
//        break;
//      }
//      else 
//      {
//         WalkMotor_Break();
//         bPowerFlag= FALSE;
//         walkStep = 0;        
//      }
//      break;
//    }      
//    break;
//    case STATE_RUN_WALK_LOCATE:
//      RetVal = TRUE;
//      switch(walkStep)
//      {
//        case 0:
//        if(downWalkRun)
//        {
//          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//          {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag= FALSE;
//            WalkMotor_Break();
//            downWalkRun = FALSE;
//            walkStep = 1;
//            break;
//          }  
//          upWalkRun = 0;
//          WalkMotor_Down();
//          bPowerFlag= TRUE;
//          break;
//        }
//        else
//        {
//           WalkMotor_Break();
//           walkStep = 1;
//           bPowerFlag= FALSE;
//        }
//        break;
//        
//    case 1:
//      if(upWalkRun)
//      {
//        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//        {
//          Input_SetWalkMotorPosition(TOP_POSITION);
//          bPowerFlag= FALSE;
//          WalkMotor_Break();      
//          upWalkRun = FALSE;
//          WalkTimeFlag = FALSE;
//          WalkTime = FALSE;
//          walkStep = 0;
//          break;
//        }
//        WalkMotor_Up();
//        bPowerFlag= TRUE;  
//        break;
//      }
//      else 
//      {
//         WalkMotor_Break();
//        // RetVal = TRUE ;
//         bPowerFlag= FALSE;
//         walkStep = 0;        
//      }
//      break;
//    }      
//    break;
//    case STATE_RUN_WALK_POSITION:  
//        if(stopPosition > (curPosition + 3))
//        {
//            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//            {
//                Input_SetWalkMotorPosition(TOP_POSITION);
//                bPowerFlag = FALSE;
//                RetVal = TRUE ;
//                WalkMotor_Break();
//                break;
//            }
//            WalkMotor_Up();
//            bPowerFlag = TRUE;
//            break;
//        }
//        if((stopPosition + 3) < curPosition)
//        {
//            if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//            {
//                Input_SetWalkMotorPosition(0);
//                bPowerFlag = FALSE;
//                RetVal = TRUE ;
//                WalkMotor_Break();
//                break;
//            }
//            WalkMotor_Down();
//            bPowerFlag = TRUE;
//            break;
//        }
//        bPowerFlag = FALSE;
//        RetVal = TRUE ;
//        WalkMotor_Break();
//        break;
//    case STATE_RUN_WALK_DOWN:  //back motor go down
//        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
//        {
//            Input_SetWalkMotorPosition(0);
//            bPowerFlag = FALSE;
//            RetVal = TRUE ;
//            WalkMotor_Break();
//            break;
//        }
//        WalkMotor_Down();
//        bPowerFlag = TRUE;
//        break ;
//    case STATE_RUN_WALK_UP:  //back motor go up
//        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
//        {
//            Input_SetWalkMotorPosition(TOP_POSITION);
//            bPowerFlag = FALSE;
//            RetVal = TRUE ;
//            WalkMotor_Break();
//            break;
//        }
//        WalkMotor_Up();
//        bPowerFlag = TRUE;
//        break ;
//    case STATE_WALK_IDLE:
//        RetVal = TRUE ;
//        WalkMotor_Break();
//        bPowerFlag = FALSE;
//        break ;
//    default://异常处理
//        break ;
//    }
//    //电源部分的处理
//    if(bPowerFlag == TRUE)
//    {
//        WalkPower_On();
//    }
//    else
//    {
//        WalkPower_Off();
//    }
//    return RetVal ;
//}
bool downflag,upflag,downflag2,upflag2;
unsigned char WalkMotor_Control(unsigned char nFinalWalkMotorState,unsigned short stopPosition)
{
    unsigned char RetVal ;
    bool PowerFlag;
    RetVal = FALSE ;
    
    static bool init_flag = FALSE;
    static unsigned short curPosition;
    curPosition= Input_GetWalkMotorPosition();
    nWalkLoss = 0;
    static unsigned char walkStep = 0;
    Walk_Motor_State = nFinalWalkMotorState; 
    //   if(!LEUART0_isOK())
    //   {
    //     WalkMotor_Break();
    //     WalkPower_Off();
    //     return(unsigned char)(TRUE);
    //   }
    
    switch(nFinalWalkMotorState)
    {
    case WALK_UP_PULSE:
        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(TOP_POSITION);
            PowerFlag= FALSE;
            WalkMotor_Break();
            init_flag = FALSE;
            RetVal = TRUE ;
            break;
        }
        if(!init_flag)
        {
            RealTime_Position = curPosition;
            init_flag = TRUE;//保证在到达位置前只获取一次位置
        }
        if((curPosition >= RealTime_Position+stopPosition))
        {
            init_flag = FALSE;
            PowerFlag = FALSE;
            WalkMotor_Break();
            RetVal = TRUE ;
        }
        else
        {
            WalkMotor_Up();
            PowerFlag= TRUE;
        }
        break;
        
    case WALK_DOWN_PULSE:
        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(0);
            PowerFlag= FALSE;
            WalkMotor_Break();
            init_flag = FALSE;
            RetVal = TRUE ;
            break;
        }
        if(!init_flag)
        {
            RealTime_Position = curPosition;
            init_flag = TRUE;//保证在到达位置前只获取一次位置
        }
        if((curPosition <= RealTime_Position-stopPosition) && (curPosition > RealTime_Position-stopPosition-3))
        {
            init_flag = FALSE;
            PowerFlag= FALSE;
            WalkMotor_Break();
            RetVal = TRUE ;
        }
        else
        {
            WalkMotor_Down();
            PowerFlag= TRUE;
        }
        break;  
    case UP_DOWN_WALK:
        RetVal = TRUE ;
        Walk_PWM = 90; 
        if(downWalkRun)
        {
            if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(0);
                PowerFlag= FALSE;
                WalkMotor_Break();
                break;
            }  
            WalkMotor_Down();
            PowerFlag= TRUE;
            break;
        }
        else
        {
            PowerFlag= FALSE;
            WalkMotor_Break(); 
        }
        if(upWalkRun)
        {
            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(TOP_POSITION);
                PowerFlag= FALSE;
                WalkMotor_Break();      
                break;
            }
            WalkMotor_Up();
            PowerFlag= TRUE;  
            break;
        }
        else
        {
            PowerFlag= FALSE;
            WalkMotor_Break();
        }
        break;
        
    case PWM_WALK:
        switch(walkStep)
        {
        case 0:
            if(downWalkRun)
            {
                if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(0);
                    PowerFlag= FALSE;
                    WalkMotor_Break();
                    walkStep = 1;
                    pwm_time_flag = 0;
                    pwm_time = 0;
                    RetVal = TRUE ;
                    downWalkRun = FALSE;
                    break;
                }
                Walk_PWM = 110; 
                upWalkRun = 0;
                WalkMotor_Down();
                PowerFlag= TRUE;
                break;
            }
            else
            {  
                WalkMotor_Break();
                walkStep = 1;
                PowerFlag= FALSE;
            } 
            break;
        case 1:
            Walk_PWM = 120; 
            if(upWalkRun)
            {
                if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(TOP_POSITION);
                    PowerFlag= FALSE;
                    RetVal = TRUE ;
                    WalkMotor_Break();      
                    upWalkRun = FALSE;
                    pwm_time_flag = 0;
                    pwm_time = 0;
                    walkStep = 0;
                    break;
                }
                Walk_PWM = 120;    
                WalkMotor_Up();
                PowerFlag= TRUE;  
                break;
            }
            else 
            {
                WalkMotor_Break();
                walkStep = 0;
                PowerFlag= FALSE;
                RetVal = TRUE ;
            }
            break;
        default:
            walkStep = 0; 
            break;
        }
        break;
        
    case STATE_RUN_WALK_POSITION:  
        if(stopPosition > (curPosition + 3))
        {
            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(TOP_POSITION);
                PowerFlag= FALSE;
                RetVal = TRUE ;
                WalkMotor_Break();
                break;
            }
            WalkMotor_Up();
            PowerFlag= TRUE;
            break;
        }
        if((stopPosition + 3) < curPosition)
        {
            if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(0);
                PowerFlag= FALSE;
                RetVal = TRUE ;
                WalkMotor_Break();
                break;
            }
            WalkMotor_Down();
            PowerFlag= TRUE;
            break;
        }
        PowerFlag= FALSE;
        RetVal = TRUE ; 
        //WalkMtor_SlowBreak();
        WalkMotor_Break();
        break;
    case STATE_RUN_WALK_DOWN:  //back motor go down
        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(0);
            PowerFlag= FALSE;
            RetVal = TRUE ;
            WalkMotor_Break();
            break;
        }
        WalkMotor_Down();
        PowerFlag= TRUE;
        break ;
    case STATE_RUN_WALK_UP:  //back motor go up
        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        {
            Input_SetWalkMotorPosition(TOP_POSITION);
            PowerFlag= FALSE;
            RetVal = TRUE ;
            WalkMotor_Break();
            break;
        }
        WalkMotor_Up();
        PowerFlag= TRUE;
        break ;
    case _3D_WALK:             //add by wby 20161223
      if(!_3D_MaxOk)
      {
        PowerFlag= FALSE;
        WalkMotor_Break();
        break;
      }
      Walk_PWM = 110;
      if(curPosition < stopPosition-3)
      {
          if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
          {
              Input_SetWalkMotorPosition(TOP_POSITION);
              PowerFlag = FALSE;
              RetVal = TRUE ;
              WalkMotor_Break();
              _3D_StopFlag = 1;
              break;
          }
          WalkMotor_Up();
          PowerFlag= TRUE;
          _3D_StopFlag = 0;
          break;
      }
       if(curPosition > stopPosition+3)
       {
          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(0);
                PowerFlag = FALSE;
                RetVal = TRUE ;
                WalkMotor_Break();
                _3D_StopFlag = 1;
                break;
            }
            WalkMotor_Down();
            PowerFlag = TRUE;
            _3D_StopFlag = 0;
            break;
       }
        PowerFlag= FALSE;
        RetVal = TRUE ;
        WalkMotor_Break();
        _3D_StopFlag = 1;
        break;
        
    case STATE_RUN_STOP_WALK_KNEAD:           //add by wby 20161223
      Walk_PWM = 120;
      switch(walkStep)
      {
      case 0:
          if(downWalkRun)
          {
              if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
              {
                  Input_SetWalkMotorPosition(0);
                  PowerFlag= FALSE;
                  WalkMotor_Break();
                  walkStep = 1;
                  downWalkRun = FALSE;
                  break;
              }  
              upWalkRun = 0;
              WalkMotor_Down();
              PowerFlag= TRUE;
              break;
          }
          else
          {    
              PowerFlag= FALSE;
              WalkMotor_Break();
              walkStep = 1;
          }
          break;
          
      case 1:
          if(upWalkRun)
          {
              if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
              {
                  Input_SetWalkMotorPosition(TOP_POSITION);
                  PowerFlag= FALSE;
                  // RetVal = TRUE ;
                  WalkMotor_Break();      
                  upWalkRun = FALSE;
                  WalkTimeFlag = FALSE;
                  WalkTime = FALSE;
                  //Walk_StopFlag = 1;
                  walkStep = 0;
                  break;
              }
              WalkMotor_Up();
              PowerFlag= TRUE;  
              break;
          }
          else 
          {
              PowerFlag= FALSE;
              WalkMotor_Break(); 
              walkStep = 0;
              RetVal = TRUE ;
          }
          break;
      default:
          walkStep = 0; 
          break; 
      }      
    break;
    case STATE_RUN_LONG_WALK_KNEAD:   //上下PWM差来实现总体行走            //add by wby 20161223
        if(curPosition > stopPosition-3 && curPosition < stopPosition+3)
        {
            walkStep = 0;
            PowerFlag= FALSE;
            WalkMotor_Break();
            RetVal = TRUE ;
            downWalkRun = 0;
            upWalkRun = 0;
            Walk_StopFlag = 1;
            break;
        }
        Walk_StopFlag = 0;
        switch(walkStep)
        {
        case 0:
            if(downWalkRun)
            {
                if(curPosition > stopPosition+3)
                {
                    Walk_PWM=131;
                }
                else if(curPosition < stopPosition-3)
                {
                    Walk_PWM=100;
                }
                if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(0);
                    PowerFlag= FALSE;
                    WalkMotor_Break();
                    walkStep = 1;
                    downWalkRun = FALSE;
                    break;
                }  
                //upWalkRun = 0;
                WalkMotor_Down();
                PowerFlag= TRUE;
                break;
            }
            else
            {
                WalkMotor_Break();
                walkStep = 1;
                PowerFlag= FALSE;
            }
            break;
            
        case 1:
            if(upWalkRun)
            {
                if(curPosition > stopPosition+3)
                {
                    Walk_PWM=100;
                }
                else if(curPosition < stopPosition-3)
                {
                    Walk_PWM=131;
                } 
                if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(TOP_POSITION);
                    PowerFlag= FALSE;
                    WalkMotor_Break();      
                    upWalkRun = FALSE;
                    WalkTimeFlag = FALSE;
                    WalkTime = FALSE;
                    walkStep = 0;
                    break;
                }
                WalkMotor_Up();
                PowerFlag= TRUE;  
                break;
            }
            else 
            {
                WalkMotor_Break();
                PowerFlag= FALSE;
                walkStep = 0;        
            }
            break;
        default:
            walkStep = 0; 
            break;
        }      
        break;   
    case STATE_RUN_PWM_ABS:        //PWM差值积累形成总体上下行走--- 110~90的差值                          //add by wby 20161223   
      if(/*(Walk_CheckPoint) && */(curPosition > (stopPosition-3) )&& (curPosition < (stopPosition+3)  )   )
      {
        walkStep = 0;
        PowerFlag= FALSE;
        WalkMotor_Break();
        RetVal = TRUE ;
        downWalkRun = 0;
        upWalkRun = 0;
        Walk_StopFlag = 1;
        downflag=0;
        upflag=0;
        downflag2=0;
        upflag2=0;
        checkover1 = 0;
        checkover2 = 0;
        break;
      }
      Walk_StopFlag = 0;

             
      switch(walkStep)
      {
        case 0:
        if(downWalkRun)
        {
            if(curPosition > stopPosition )//&& !checkover2)
            {
                checkover2 = 1;
                downflag=1;
                upflag = 0;
            }
            else if(curPosition < stopPosition )//&& !checkover2)
            {
                checkover2 = 1;
                downflag=0;
                upflag = 1;
            }
            
            if(downflag) 
           {
             Walk_PWM=90;
           }
           else if(upflag)
           {
             Walk_PWM = 70;
           }
          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
          {
            Input_SetWalkMotorPosition(0);
            PowerFlag= FALSE;
            WalkMotor_Break();
            downWalkRun = FALSE;
            walkStep = 1;
            break;
          }  
          upWalkRun = 0;
          WalkMotor_Down();
          PowerFlag= TRUE;
          break;
        }
        else
        {
           WalkMotor_Break();
           walkStep = 1;
           PowerFlag= FALSE;
        }
        break; 
    case 1:
      if(upWalkRun)
      {
        if(curPosition > stopPosition )//&& !checkover2)
        {
          checkover2 = 1;
          downflag2 = 1;
          upflag2 = 0;
        }
        else if(curPosition < stopPosition )//&& !checkover2)
        {
          checkover2 = 1;
          upflag2=1;
          downflag2 = 0;
        }
        if(downflag2)
        {
          Walk_PWM=70;
        }
        else if(upflag2)
        {
          Walk_PWM=90;
        }
        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        {
          Input_SetWalkMotorPosition(TOP_POSITION);
          PowerFlag= FALSE;
          WalkMotor_Break();      
          upWalkRun = FALSE;
          WalkTimeFlag = FALSE;
          WalkTime = FALSE;
          walkStep = 0;
          break;
        }
        downWalkRun = 0;
        WalkMotor_Up();
        PowerFlag= TRUE;  
        
        break;
      }
      else 
      {
         WalkMotor_Break();
         PowerFlag= FALSE;
         walkStep = 0;        
      }
      break;
      default:                   //cyw
          walkStep = 0; 
          break; 
    }      
    break;
    case STATE_RUN_WALK_LOCATE:
      RetVal = TRUE;
      switch(walkStep)
      {
        case 0:
        if(downWalkRun)
        {
          if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
          {
            Input_SetWalkMotorPosition(0);
            PowerFlag= FALSE;
            WalkMotor_Break();
            downWalkRun = FALSE;
            walkStep = 1;
            break;
          }  
          upWalkRun = 0;
          WalkMotor_Down();
          PowerFlag= TRUE;
          break;
        }
        else
        {
           WalkMotor_Break();
           walkStep = 1;
           PowerFlag= FALSE;
        }
        break;
        
    case 1:
      if(upWalkRun)
      {
        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        {
          Input_SetWalkMotorPosition(TOP_POSITION);
          PowerFlag= FALSE;
          WalkMotor_Break();      
          upWalkRun = FALSE;
          WalkTimeFlag = FALSE;
          WalkTime = FALSE;
          walkStep = 0;
          break;
        }
        WalkMotor_Up();
        PowerFlag= TRUE;  
        break;
      }
      else 
      {
         WalkMotor_Break();
        // RetVal = TRUE ;
         PowerFlag= FALSE;
         walkStep = 0;        
      }
      break;
      default:
          walkStep = 0; 
          break;  
    }      
    break;
        /**************************轻柔呵护相关开始*********************/
    case STATE_RUN_STOP_WALK_KNEAD_3:           
        //Walk_PWM = 120; ///测试改为80 原120
        switch(walkStep)
        {
        case 0:
            Walk_PWM = 105;
            if(downWalkRun)
            {
                //2 120
                if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(0);
                    PowerFlag= FALSE;
                    // RetVal = TRUE ;
                    WalkMotor_Break();      
                    downWalkRun = FALSE;
                    WalkTimeFlag = FALSE;
                    WalkTime = FALSE;
                    //Walk_StopFlag = 1;
                    walkStep = 1;
                    break;
                }
                WalkMotor_Down();
                PowerFlag= TRUE;  
                break;
            }
            else 
            {
                PowerFlag= FALSE;
                WalkMotor_Break(); 
                walkStep = 1;
                RetVal = TRUE;
            }
            break;
            
        case 1: 
            Walk_PWM = 120;
            if(upWalkRun)
            { 
                if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
                {
                    Input_SetWalkMotorPosition(TOP_POSITION);
                    PowerFlag= FALSE;
                    WalkMotor_Break();
                    walkStep = 0;
                    upWalkRun = FALSE;
                    break;
                }  
                //upWalkRun = 0;
                WalkMotor_Up();
                PowerFlag= TRUE;
                break;
            }
            else
            {    
                PowerFlag= FALSE;
                WalkMotor_Break();
                walkStep = 0;
                RetVal = TRUE;
            }
            break;
        default:                //cyw
            walkStep = 0;
            break;
        }      
        break;
        /**************************轻柔呵护相关结束*********************/
    case STATE_WALK_IDLE:
        RetVal = TRUE ;
        WalkMotor_Break();
        PowerFlag= FALSE;
        break ;
    default://异常处理
        break ;
    }
    //电源部分的处理
    if(PowerFlag== TRUE)
    {
        WalkPower_On();
    }
    else
    {
        WalkPower_Off();
    }
    return RetVal ;
}

void WalkMotor_10msInt(void)
{
  nWalkLoss++;
  if(nWalkLoss > 2)
  {

  TIMER_CompareBufSet(WALK_MOTOR_TIMER, WALK_MOTOR_TIMER_CHANNEL, 0);
  }
  
  
}