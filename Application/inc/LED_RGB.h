#ifndef __LED_RGB_H__
#define __LED_RGB_H__
/*
#define LED_RED_PORT   gpioPortC
#define LED_RED_BIT    13
#define LED_RED_MODE   gpioModePushPull

#define LED_GREEN_PORT   gpioPortC
#define LED_GREEN_BIT    14
#define LED_GREEN_MODE   gpioModePushPull

#define LED_BLUE_PORT   gpioPortC
#define LED_BLUE_BIT    15
#define LED_BLUE_MODE   gpioModePushPull
*/
#define LED_RED_PORT   gpioPortC
#define LED_RED_BIT    8//0
#define LED_RED_MODE   gpioModePushPull

#define LED_GREEN_PORT   gpioPortC//E
#define LED_GREEN_BIT    9//1
#define LED_GREEN_MODE   gpioModePushPull

#define LED_BLUE_PORT   gpioPortC//E
#define LED_BLUE_BIT    10//2
#define LED_BLUE_MODE   gpioModePushPull

#define LED_RGB_TIMER           TIMER2//3

#define LED_RGB_RED_CHANNEL     1   
#define LED_RGB_GREEN_CHANNEL   0   
#define LED_RGB_BLUE_CHANNEL    2

#define LED_RGB_RED_ROUTE_EN        TIMER_ROUTE_CC0PEN
#define LED_RGB_GREEN_ROUTE_EN      TIMER_ROUTE_CC1PEN
#define LED_RGB_BLUE_ROUTE_EN       TIMER_ROUTE_CC2PEN

#define LED_RGB_ROUTE_LOCATION    TIMER_ROUTE_LOCATION_LOC2

#define LED_RGB_PRESCALE        timerPrescale256

#define LED_RGB_DEFAULT_TOP     100

#define LED_RGB_Timer_CCInit     \
{                                   \
    timerEventEveryEdge,            \
    timerEdgeBoth,                  \
    timerPRSSELCh0,                 \
    timerOutputActionNone,          \
    timerOutputActionNone,          \
    timerOutputActionToggle,        \
    timerCCModePWM,                 \
    false,                          \
    false,                          \
    false,                          \
    false,                          \
} 

#define LED_RGB_Timer_Init       \
{                                   \
    true,                           \
    true,                           \
    LED_RGB_PRESCALE,            \
    timerClkSelHFPerClk,            \
    timerInputActionNone,           \
    timerInputActionNone,           \
    timerModeUp,                    \
    false,                          \
    false,                          \
    false,                          \
    false,                          \
}

#define LED_LIGHT         0
#define LED_DARK          1
#define LED_SLOWLY_LIGHT  2
#define LED_SLOWLY_DARK   3

typedef struct LEDCtrlStruct
{
  unsigned char nRedInit ;  //红色LED初始值
  unsigned char nGreenInit ;//绿色LED初始值
  unsigned char nBlueInit ; //蓝色LED初始值
  unsigned char nRedTarget;
  unsigned char nGreenTarget ;
  unsigned char nBlueTarget ;
  unsigned nRedCtrl:   2   ;//LED控制方式 00：灭 01：亮 02：渐灭 03：渐亮 
  unsigned nGreenCtrl: 2   ;
  unsigned nBlueCtrl:  2   ;
  unsigned char nTime ;     //当前状态保持时间,单位0.1秒
} st_LEDCtrlStruct ;

typedef struct LEDCtrlStruct1
{
    unsigned char LEDHighTime_Init ;
    unsigned char LEDLowTime_Init ;
    unsigned char LEDHighTime_Target;
    unsigned char LEDLowTime_Target;
    unsigned char LEDHighTime;
    unsigned char LEDLowTime;
    unsigned char LEDCycount;
    unsigned char LEDCtrlMode;
//    unsigned int RedHighTime_Init;
//    unsigned int RedLowTime_Init;
//    unsigned int RedHighTime_Target;
//    unsigned int RedLowTime_Target;
//    unsigned int RedHighTime;
//    unsigned int RedLowTime;
//    unsigned int RedCycount;
//    unsigned int RedCtrlMode;
//    unsigned int GreenHighTime_Init;
//    unsigned int GreenLowTime_Init;
//    unsigned int GreenHighTime_Target;
//    unsigned int GreenLowTime_Target;
//    unsigned int GreenHighTime;
//    unsigned int GreenLowTime;
//    unsigned int GreenCycount;
//    unsigned int GreenCtrlMode;
}st_LEDCtrlStruct1;

void LED_RGB_Initial_IO(void);
void LED_RGB_Red_Set(void);
void LED_RGB_Red_Clear(void);
void LED_RGB_Red_Toggle(void);
void LED_RGB_Green_Set(void);
void LED_RGB_Green_Clear(void);
void LED_RGB_Green_Toggle(void);
void LED_RGB_Blue_Set(void);
void LED_RGB_Blue_Clear(void);
void LED_RGB_Blue_Toggle(void);

void LED_RGB_Set_Red_Data(unsigned long ulDuty);
void LED_RGB_Set_Green_Data(unsigned long ulDuty);
void LED_RGB_Set_Blue_Data(unsigned long ulDuty);

void LED_RGB_10ms_Int(void);
void LED_RGB_5ms_Int(void);
void LED_RGB_100ms_Int(void);

void LED_RGB_Proce(unsigned char nChairRunState);
void LED_RGB_Set_All(unsigned int w_Data);
void LED_RGB_Set_Route(void);

#endif /*__LED_RGB_H__*/