#include "EFM32_def.h"
#include "EFM32_types.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "MassageStatus.h"
#include "ZeroMotor.h"
#include "LED_RGB.h"        

bool bFlag10ms;
unsigned int w_LEDSteps;  //用於記錄當前的顯示步驟
unsigned int w_LEDTimer;  //用於記錄當前步骤的运行时间 单位0.1秒
unsigned int w_LEDCtrlTimer;  //控制LED的渐亮或渐暗的定时器
unsigned int w_LEDCtrlTimer1;
unsigned char by_Red_PWM,by_Green_PWM,by_Blue_PWM;
bool b_LED_Init;
extern BITS GlobalFlags3 ;
#define bLedFlag 		        GlobalFlags3.bD2
//extern st_LEDCtrlStruct1 BlueCtrlStruct,RedCtrlStruct,GreenCtrlStruct;

  const st_LEDCtrlStruct LED_Settle[] = 
  {
    {0,0,0,LED_DARK,LED_DARK,LED_DARK,10},
    {80,0,0,LED_SLOWLY_LIGHT,LED_DARK,LED_DARK,2},     //红色
    {100,0,0,LED_SLOWLY_DARK,LED_SLOWLY_LIGHT,LED_DARK,50}, //红色渐暗绿色渐亮
    {0,100,0,LED_DARK,LED_SLOWLY_DARK,LED_SLOWLY_LIGHT,50}, //绿色渐暗蓝色渐亮
    {0,0,100,LED_SLOWLY_LIGHT,LED_DARK,LED_SLOWLY_DARK,50}, ////红色渐亮蓝色渐暗
  };

  const st_LEDCtrlStruct LED_Enginrering[] = 
  {
    {0,0,0,0,0,0,LED_DARK,LED_DARK,LED_DARK,10},
  };
  
  const st_LEDCtrlStruct LED_WaitCommand[] = 
  {
     {0,0,0,0,0,0,LED_DARK,LED_DARK,LED_DARK,10},
  };
  const st_LEDCtrlStruct LED_Running[] = 
  {
      /****************************7色呼吸****************************/
      {0,0,0,100,0,0,LED_SLOWLY_LIGHT,LED_DARK,LED_DARK,20},//红
      {100,0,0,0,0,0,LED_SLOWLY_DARK,LED_DARK,LED_DARK,20},
      {0,0,0,100,60,0,LED_SLOWLY_LIGHT,LED_SLOWLY_LIGHT,LED_DARK,20},//橙
      {100,60,0,0,0,0,LED_SLOWLY_DARK,LED_SLOWLY_DARK,LED_DARK,20},
      {0,0,0,100,100,0,LED_SLOWLY_LIGHT,LED_SLOWLY_LIGHT,LED_DARK,20},//黄
      {100,100,0,0,0,0,LED_SLOWLY_DARK,LED_SLOWLY_DARK,LED_DARK,20},
      {0,0,0,0,100,0,LED_DARK,LED_SLOWLY_LIGHT,LED_DARK,20},//绿
      {0,100,0,0,0,0,LED_DARK,LED_SLOWLY_DARK,LED_DARK,20},
      {0,0,0,0,0,100,LED_DARK,LED_DARK,LED_SLOWLY_LIGHT,20},   //蓝
      {0,0,100,0,0,0,LED_DARK,LED_DARK,LED_SLOWLY_DARK,20},
      {0,0,0,0,100,100,LED_DARK,LED_SLOWLY_LIGHT,LED_SLOWLY_LIGHT,20},//靛
      {0,100,100,0,0,0,LED_DARK,LED_SLOWLY_DARK,LED_SLOWLY_DARK,20},
      {0,0,0,100,0,100,LED_SLOWLY_LIGHT,LED_SLOWLY_LIGHT,LED_SLOWLY_LIGHT,20},//紫
      {100,0,100,0,0,0,LED_SLOWLY_DARK,LED_DARK,LED_SLOWLY_DARK,20},    

//      /**************************7色连续跳转***************************/
//      {200,0,0,200,0,0,LED_LIGHT,LED_DARK,LED_DARK,10},     //红
//      {200,70,0,200,70,0,LED_LIGHT,LED_LIGHT,LED_DARK,10},  //橙
//      {200,200,0,200,200,0,LED_LIGHT,LED_LIGHT,LED_DARK,10},    //黄
//      {0,200,0,0,200,0,LED_DARK,LED_LIGHT,LED_DARK,10},     //绿
//      {0,0,200,0,0,200,LED_DARK,LED_DARK,LED_LIGHT,10},     //蓝
//      {0,200,200,0,200,200,LED_DARK,LED_LIGHT,LED_LIGHT,10},//靛
//      {200,0,200,200,0,200,LED_LIGHT,LED_DARK,LED_LIGHT,10},    //紫
//      
//      /**************************6色无缝转换***************************/
//      {200,0,0,0,200,0,LED_SLOWLY_DARK,LED_SLOWLY_LIGHT,LED_DARK,18},//绿
//      {0,200,0,0,0,200,LED_DARK,LED_SLOWLY_DARK,LED_SLOWLY_LIGHT,17},//蓝
//      {0,0,200,0,200,200,LED_DARK,LED_SLOWLY_LIGHT,LED_LIGHT,18},    //靛
//      {0,200,200,200,0,200,LED_SLOWLY_LIGHT,LED_SLOWLY_DARK,LED_LIGHT,18},//紫
//      {200,0,200,200,200,0,LED_LIGHT,LED_SLOWLY_LIGHT,LED_SLOWLY_DARK,18},//黄
//      {200,200,0,200,0,0,LED_SLOWLY_LIGHT,LED_SLOWLY_DARK,LED_DARK,18},  //红

};
  const st_LEDCtrlStruct LED_Problem[] = 
  {
    {0,0,0,0,0,0,LED_DARK,LED_DARK,LED_DARK,2},
    {100,0,0,100,0,0,LED_LIGHT,LED_DARK,LED_DARK,2},
  };

  const st_LEDCtrlStruct LED_Idle[] = 
  {
    {0,0,0,0,0,0,LED_DARK,LED_DARK,LED_DARK,10},
  };
#define LED_SETTLE_LENGTH         sizeof(LED_Settle)/sizeof(st_LEDCtrlStruct)
#define LED_WAIT_COMMAND_LENGTH   sizeof(LED_WaitCommand)/sizeof(st_LEDCtrlStruct)
#define LED_RUNNING_LENGTH        sizeof(LED_Running)/sizeof(st_LEDCtrlStruct)
#define LED_PROBLEM_LENGTH        sizeof(LED_Problem)/sizeof(st_LEDCtrlStruct)
#define LED_IDLE_LENGTH           sizeof(LED_Idle)/sizeof(st_LEDCtrlStruct)

void LED_RGB_Initial_IO(void)
{
    GPIO_PinModeSet(LED_RED_PORT, LED_RED_BIT, LED_RED_MODE, 0);
    GPIO_PinModeSet(LED_GREEN_PORT, LED_GREEN_BIT, LED_GREEN_MODE, 0);
    GPIO_PinModeSet(LED_BLUE_PORT, LED_BLUE_BIT, LED_BLUE_MODE, 0);
    
//    TIMER_Init_TypeDef tTimer2Init = { 
//        .enable = false, /* 初始化结束不使能 */ 
//        .debugRun = false, /* 调试 Halt 时停止计数 */ 
//        .prescale = timerPrescale1, /* 1024 分频 */ 
//        .clkSel = timerClkSelHFPerClk, /* 时钟源选择高频外设时钟 */ 
//        .count2x = false, /* 不使用 2 倍计数模式，GG/TG 才有 */
//        .ati = false, 
//        .fallAction = timerInputActionNone, /* 配置下降沿行为 */ 
//        .riseAction = timerInputActionNone, /* 配置上升沿行为 */ 
//        .mode = timerModeUp, /* 配置计数模式 */ 
//        .dmaClrAct = false, 
//        .quadModeX4 = false, /* 在正交编码中是否使用 X4 模式 */ 
//        .oneShot = false, /* 是否使用单次模式 */ 
//        .sync = false, /* 定时器由其它定时器控制 */ 
//    }; 
//    TIMER_Init(TIMER2, &tTimer2Init); /* 初始化 TIMER1 计数器 */ 
//    TIMER_TopSet(TIMER2, 1400); //350，0.0125ms一个中断
//    TIMER_IntEnable(TIMER2, TIMER_IF_OF); /* 使能 TIMER1 溢出中断 */ 
//    NVIC_EnableIRQ(TIMER2_IRQn); /* 使能 TIMER1 中断 */ 
//    TIMER2->CMD = TIMER_CMD_START; /* 启动计数器 */ 
      TIMER_InitCC_TypeDef timerCCInit = LED_RGB_Timer_CCInit;
      /* Configure CC channel 0 */
      TIMER_InitCC(LED_RGB_TIMER, LED_RGB_RED_CHANNEL, &timerCCInit);
      TIMER_InitCC(LED_RGB_TIMER, LED_RGB_GREEN_CHANNEL, &timerCCInit);
      TIMER_InitCC(LED_RGB_TIMER, LED_RGB_BLUE_CHANNEL, &timerCCInit);
      
      /* Set Top Value */
      TIMER_TopSet(LED_RGB_TIMER, LED_RGB_DEFAULT_TOP);
      
      TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_RED_CHANNEL, 0);
      TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_GREEN_CHANNEL, 0);
      TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_BLUE_CHANNEL, 0);
      
      
      LED_RGB_Set_Route();
      /* Route CC0 to location 3 (PD1) and enable pin */  
      //    LED_RGB_TIMER->ROUTE |= (LED_RGB_RED_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
      //    LED_RGB_TIMER->ROUTE |= (LED_RGB_GREEN_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
      //    LED_RGB_TIMER->ROUTE |= (LED_RGB_BLUE_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
      b_LED_Init = 1;
}

void LED_RGB_Set_Route(void)
{
  TIMER_Init_TypeDef timerInit = LED_RGB_Timer_Init;
  TIMER_Init(LED_RGB_TIMER, &timerInit);
  LED_RGB_TIMER->ROUTE = (LED_RGB_RED_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
  LED_RGB_TIMER->ROUTE |= (LED_RGB_GREEN_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
  LED_RGB_TIMER->ROUTE |= (LED_RGB_BLUE_ROUTE_EN | LED_RGB_ROUTE_LOCATION); 
}

void LED_RGB_Red_Set(void)
{
 GPIO_PinOutSet(LED_RED_PORT, LED_RED_BIT); 
}
void LED_RGB_Red_Clear(void)
{
 GPIO_PinOutClear(LED_RED_PORT, LED_RED_BIT); 
}
void LED_RGB_Red_Toggle(void)
{
  GPIO_PinOutToggle(LED_RED_PORT, LED_RED_BIT); 
}

void LED_RGB_Green_Set(void)
{
 GPIO_PinOutSet(LED_GREEN_PORT, LED_GREEN_BIT); 
}
void LED_RGB_Green_Clear(void)
{
 GPIO_PinOutClear(LED_GREEN_PORT, LED_GREEN_BIT); 
}
void LED_RGB_Green_Toggle(void)
{
 GPIO_PinOutToggle(LED_GREEN_PORT, LED_GREEN_BIT); 
}

void LED_RGB_Blue_Set(void)
{
 GPIO_PinOutSet(LED_BLUE_PORT, LED_BLUE_BIT); 
}
void LED_RGB_Blue_Clear(void)
{
  GPIO_PinOutClear(LED_BLUE_PORT, LED_BLUE_BIT); 
}
void LED_RGB_Blue_Toggle(void)
{
  GPIO_PinOutToggle(LED_BLUE_PORT, LED_BLUE_BIT); 
}

void LED_RGB_Set_Red_Data(unsigned long ulDuty)
{
  TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_RED_CHANNEL, ulDuty);
}
void LED_RGB_Set_Green_Data(unsigned long ulDuty)
{
  TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_GREEN_CHANNEL, ulDuty);
}

void LED_RGB_Set_Blue_Data(unsigned long ulDuty)
{
  TIMER_CompareBufSet(LED_RGB_TIMER, LED_RGB_BLUE_CHANNEL, ulDuty);
}
unsigned char LED_count=0;
void LED_RGB_10ms_Int(void)
{
  bFlag10ms = TRUE;
  LED_count++;
  
  if(LED_count == 2)
  {
      
      w_LEDCtrlTimer++;
      w_LEDCtrlTimer1--;
      LED_count = 0;
  }
}
//void LED_RGB_5ms_Int(void)
//{
//   w_LEDCtrlTimer++;
//}
void LED_RGB_100ms_Int(void)
{
  w_LEDTimer++;
}

BYTE  LED_RGB_Set_Pwm(BYTE CtrlMode,BYTE PWM_init,BYTE PWM_Target)  
{
    BYTE pwm;
    unsigned int w_PWM;
    switch(CtrlMode)
    {
    case LED_LIGHT: pwm = PWM_init; break; 
    case LED_DARK:  pwm = PWM_init; break; 
    case LED_SLOWLY_LIGHT: 
        w_PWM = w_LEDCtrlTimer+PWM_init;// >> 2; 
        if(w_PWM > PWM_Target) w_PWM = PWM_Target;
        pwm = (unsigned char)w_PWM;   
        break; 
    case LED_SLOWLY_DARK: 
        w_PWM = w_LEDCtrlTimer;// >> 2; 
        if(w_PWM > PWM_init-PWM_Target)
        {
            w_PWM = PWM_Target;
        }
        else 
        {
            w_PWM = PWM_init-w_LEDCtrlTimer;// >> 2; 
        }
        pwm = (unsigned char)w_PWM;   
        break; 
    default:  break;  
    } 
    return pwm;
} 
  
void LED_RGB_Proce(unsigned char nChairRunState)
{
    if(!bFlag10ms) return;
    bFlag10ms = FALSE;
    if(bLedFlag == 0)
    {
         TIMER_IntDisable(TIMER2,TIMER_IF_OF);
         LED_RGB_Set_Red_Data(0);
         LED_RGB_Set_Green_Data(0);
         LED_RGB_Set_Blue_Data(0); 
         return;
    }
    const st_LEDCtrlStruct* pst_LED; 
    unsigned int length;
    static BYTE OldState = CHAIR_STATE_IDLE;
    //  static bool bRoute = false;
    /*
    if(LED_RGB_TIMER->ROUTE == (ZERO_MOTOR_ROUTE_EN | ZERO_MOTOR_ROUTE_LOCATION)) 
    //if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
    {
    LED_RGB_Red_Set();
    LED_RGB_Green_Set();
    LED_RGB_Blue_Set();
    bRoute = false;
    return; 
}
    */
    /*
    if(!bRoute)
    {
    bRoute = true;
    LED_RGB_Set_Route();
}
    */
    if(OldState != nChairRunState)
    {
        b_LED_Init = TRUE;  //按摩椅状态切换时，需要初始化按摩椅控制程序
        OldState = nChairRunState;
    }
    switch(nChairRunState)
    {
    case CHAIR_STATE_IDLE: 
        pst_LED = LED_Idle;
        length = LED_IDLE_LENGTH;
        break;
    case CHAIR_STATE_SETTLE: 
        pst_LED = LED_Settle;
        length = LED_SETTLE_LENGTH;
        break;
    case CHAIR_STATE_WAIT_COMMAND: 
        pst_LED = LED_WaitCommand;
        length = LED_WAIT_COMMAND_LENGTH;
        break;
    case CHAIR_STATE_RUN:
    default:
        pst_LED = LED_Running;
        length = LED_RUNNING_LENGTH;
        break;
    case CHAIR_STATE_WAIT_MEMORY: 
        break;
    case CHAIR_STATE_PROBLEM: 
        pst_LED = LED_Problem;
        length = LED_PROBLEM_LENGTH;
        break;
    case CHAIR_STATE_ENGINEERING:
        pst_LED = LED_Enginrering;
        length = LED_PROBLEM_LENGTH;
        break;
    }
    if(b_LED_Init)  //LED显示数据被初始化，显示从表头开始
    {
        w_LEDTimer = 0;
        w_LEDCtrlTimer = 0;
        w_LEDCtrlTimer1 = 100;
        w_LEDSteps = 0;
        by_Red_PWM = (pst_LED + w_LEDSteps)->nRedInit;
        by_Blue_PWM = (pst_LED + w_LEDSteps)->nBlueInit;
        by_Green_PWM = (pst_LED + w_LEDSteps)->nGreenInit;
        b_LED_Init = FALSE;
        LED_RGB_Set_Red_Data(by_Red_PWM);
        LED_RGB_Set_Green_Data(by_Green_PWM);
        LED_RGB_Set_Blue_Data(by_Blue_PWM);
        return;
    }
    
    by_Red_PWM = LED_RGB_Set_Pwm((pst_LED + w_LEDSteps)->nRedCtrl,(pst_LED + w_LEDSteps)->nRedInit,(pst_LED + w_LEDSteps)->nRedTarget);
    by_Green_PWM = LED_RGB_Set_Pwm((pst_LED + w_LEDSteps)->nGreenCtrl,(pst_LED + w_LEDSteps)->nGreenInit,(pst_LED + w_LEDSteps)->nGreenTarget);
    by_Blue_PWM = LED_RGB_Set_Pwm((pst_LED + w_LEDSteps)->nBlueCtrl,(pst_LED + w_LEDSteps)->nBlueInit,(pst_LED + w_LEDSteps)->nBlueTarget);
    
    if(w_LEDTimer >= (pst_LED + w_LEDSteps)->nTime)
    {
        w_LEDSteps++;
        if(w_LEDSteps >= length) 
        {
            b_LED_Init = TRUE; 
        }
        else
        {
            w_LEDTimer = 0;
            w_LEDCtrlTimer = 0;
            w_LEDCtrlTimer1 = 100;
            by_Red_PWM = (pst_LED + w_LEDSteps)->nRedInit;
            by_Blue_PWM = (pst_LED + w_LEDSteps)->nBlueInit;
            by_Green_PWM = (pst_LED + w_LEDSteps)->nGreenInit;
        }
    }
    LED_RGB_Set_Red_Data(by_Red_PWM);
    LED_RGB_Set_Green_Data(by_Green_PWM);
    LED_RGB_Set_Blue_Data(by_Blue_PWM);
}

//void LED_RGB_Proce(unsigned char nChairRunState)
//{
//    if(bLedFlag == 0)
//    {
//         TIMER_IntDisable(TIMER2,TIMER_IF_OF);
//         LED_RGB_Red_Clear();
//         LED_RGB_Green_Clear();
//         LED_RGB_Blue_Clear(); 
//         return;
//    }
//    else
//    {
//         TIMER_IntEnable(TIMER2,TIMER_IF_OF);
//    }
//    
//    //    if(!bFlag10ms) return;
//    //    bFlag10ms = FALSE;
//    const st_LEDCtrlStruct* pst_LED; 
//    unsigned int length;
//    static BYTE OldState = CHAIR_STATE_IDLE;
//    if(OldState != nChairRunState)
//    {
//        b_LED_Init = TRUE;  //按摩椅状态切换时，需要初始化按摩椅控制程序
//        OldState = nChairRunState;
//    }
//    switch(nChairRunState)
//    {
//    case CHAIR_STATE_IDLE: 
//        pst_LED = LED_Idle;
//        length = LED_IDLE_LENGTH;
//        break;
//    case CHAIR_STATE_SETTLE: 
//        pst_LED = LED_Settle;
//        length = LED_SETTLE_LENGTH;
//        break;
//    case CHAIR_STATE_WAIT_COMMAND: 
//        pst_LED = LED_WaitCommand;
//        length = LED_WAIT_COMMAND_LENGTH;
//        break;
//    case CHAIR_STATE_RUN:
//    default:
//        pst_LED = LED_Running;
//        length = LED_RUNNING_LENGTH;
//        break;
//    case CHAIR_STATE_WAIT_MEMORY: 
//        break;
//    case CHAIR_STATE_PROBLEM: 
//        pst_LED = LED_Problem;
//        length = LED_PROBLEM_LENGTH;
//        break;
//    case CHAIR_STATE_ENGINEERING:
//        pst_LED = LED_Enginrering;
//        length = LED_PROBLEM_LENGTH;
//        break;
//    }
//    if(b_LED_Init)  //LED显示数据被初始化，显示从表头开始
//    {
//        w_LEDTimer = 0;
//        w_LEDCtrlTimer = 0;
//        w_LEDCtrlTimer1 = 100;
//        w_LEDSteps = 0;
//        RedCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nRedInit;
//        RedCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nRedTarget;
//        RedCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nRedCtrl;
//        
//        BlueCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nBlueInit;
//        BlueCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nBlueTarget;
//        BlueCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nBlueCtrl;
//        
//        GreenCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nGreenInit;
//        GreenCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nGreenTarget;
//        GreenCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nGreenCtrl;
//        
//        b_LED_Init = FALSE;
//        return;
//    }
//    
//    if(w_LEDTimer >= (pst_LED + w_LEDSteps)->nTime)
//    {
//        w_LEDSteps++;
//        if(w_LEDSteps >= length) 
//        {
//            b_LED_Init = TRUE; 
//        }
//        else
//        {
//            w_LEDTimer = 0;
//            w_LEDCtrlTimer = 0;
//            w_LEDCtrlTimer1 = 100;
//            BlueCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nBlueInit;
//            BlueCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nBlueTarget;
//            BlueCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nBlueCtrl;
//            
//            RedCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nRedInit;
//            RedCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nRedTarget;
//            RedCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nRedCtrl;
//            
//            GreenCtrlStruct.LEDHighTime_Init = (pst_LED + w_LEDSteps)->nGreenInit;
//            GreenCtrlStruct.LEDHighTime_Target = (pst_LED + w_LEDSteps)->nGreenTarget;
//            GreenCtrlStruct.LEDCtrlMode = (pst_LED + w_LEDSteps)->nGreenCtrl;
//        }
//    }
//}

void LED_RGB_Set_All(unsigned int w_Data)
{
  unsigned int DispVal;
  if(w_Data)  DispVal = 100;
  else DispVal = 0;
  LED_RGB_Set_Red_Data(DispVal);
  LED_RGB_Set_Green_Data(DispVal);
  LED_RGB_Set_Blue_Data(DispVal);
}
