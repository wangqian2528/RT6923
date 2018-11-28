#ifndef __BACKPAD_H__
#define __BACKPAD_H__
 #define BACK_PLUSE_COUNTER

  #ifndef BACK_PLUSE_COUNTER
//
//#define BACK_MOTOR_ENBL_PORT   gpioPortE
//#define BACK_MOTOR_ENBL_BIT    15//7
//#define BACK_MOTOR_ENBL_MODE   gpioModePushPull
//
//#define BACK_MOTOR_PHASE_PORT   gpioPortE
//#define BACK_MOTOR_PHASE_BIT   10// 12
//#define BACK_MOTOR_PHASE_MODE   gpioModePushPull
//
//#define BACK_MOTOR_DECAY_PORT   gpioPortE//E
//#define BACK_MOTOR_DECAY_BIT    11//13
//#define BACK_MOTOR_DECAY_MODE   gpioModePushPull
//
//#define BACK_MOTOR_FAULT_PORT   gpioPortE//D
//#define BACK_MOTOR_FAULT_BIT    12//12
//#define BACK_MOTOR_FAULT_MODE   gpioModeInputPullFilter
//
//#define BACK_MOTOR_RESET_PORT   gpioPortE//D
//#define BACK_MOTOR_RESET_BIT    13//9
//#define BACK_MOTOR_RESET_MODE   gpioModePushPull
//
//#define BACK_MOTOR_AT_MID     0
//#define BACK_MOTOR_AT_BOTTOM  1
//#define BACK_MOTOR_AT_TOP     2
////靠背电动缸最大运行时间ms
//#define BACK_MOTOR_MAX_POSITION 1600
//
//#define BACK_MOTOR_MAX_LOCATION 674//1077
//#define TOP_POSITION 		399//最高点
//
////靠背电动缸最大计数位置
//#define BACK_MOTOR_MAX_POSITION_PULSE	674//BACK_MOTOR_MAX_POSITION_PULSE
//
//#define STATE_RUN_BACK_DOWN   0
//#define STATE_RUN_BACK_UP     1
//#define STATE_BACK_IDLE   2
//
//#define BACK_MOTOR_TIMER           TIMER3
//#define BACK_MOTOR_TIMER_CHANNEL   1
//#define BACK_MOTOR_ROUTE_EN        TIMER_ROUTE_CC1PEN
//#define BACK_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC0
//
//
//#define BACK_MOTOR_PRESCALE        timerPrescale4
//#define BACK_MOTOR_DEFAULT_TOP     131
//
//#define BACK_MOTOR_Timer_CCInit     \
//{                                   \
//    timerEventEveryEdge,            \
//    timerEdgeBoth,                  \
//    timerPRSSELCh0,                 \
//    timerOutputActionNone,          \
//    timerOutputActionNone,          \
//    timerOutputActionToggle,        \
//    timerCCModePWM,                 \
//    false,                          \
//    false,                          \
//    false,                          \
//    false,                          \
//} 
//
//#define BACK_MOTOR_Timer_Init      \
//{                                   \
//    true,                           \
//    true,                           \
//    BACK_MOTOR_PRESCALE,            \
//    timerClkSelHFPerClk,            \
//    false,                          \
//    false,                          \
//    timerInputActionNone,           \
//    timerInputActionNone,           \
//    timerModeUp,                    \
//    false,                          \
//    false,                          \
//    false,                          \
//    false,                          \
//}
//
//enum
//{
//  BACK_MOTOR_POWER_ON, 
//  BACK_MOTOR_POWER_OFF 
//};
//enum
//{
//  BACK_MOTOR_GO_UP, 
//  BACK_MOTOR_GO_DOWN 
//};
//
//enum
//{
// BACK_MOTOR_CURRENT_HIGH,
// BACK_MOTOR_CURRENT_LOW
//};
//
//enum
//{
// BACK_MOTOR_NORMAL,
// BACK_MOTOR_FAIL
//};
////int BackPower_On(void);
//void BackPower_Off(void);
//
//#define BACK_SET_VOLTAGE    260000 //25V
//
//void BackMotor_Initial_IO(void);
//void BackMotor_Up(void);
//void BackMotor_Down(void);
//void BackMotor_Break(void);
//void BackMotor_Reset(void);
//void BackMotor_Reset_Cancel(void);
//int BackMotor_Get_Fault(void);
//void BackMotor_10ms_int(void);
//void BackMotor_Proce(void);
//unsigned int BackMotor_Get_Position(void);
//unsigned char BackMotor_Control(unsigned char nFinalBackPadMotorState);
//int BackMotor_GetDirection(void);
//int BackMotor_GetPower(void);
//void currentBackPadMotorState_reset(void);



//==============================================================
   #else   //定义靠背脉冲计数



#define BACK_MOTOR_ENBL_PORT   gpioPortE
#define BACK_MOTOR_ENBL_BIT    15//7
#define BACK_MOTOR_ENBL_MODE   gpioModePushPull

#define BACK_MOTOR_PHASE_PORT   gpioPortE
#define BACK_MOTOR_PHASE_BIT   10// 12
#define BACK_MOTOR_PHASE_MODE   gpioModePushPull

#define BACK_MOTOR_DECAY_PORT   gpioPortE//E
#define BACK_MOTOR_DECAY_BIT    11//13
#define BACK_MOTOR_DECAY_MODE   gpioModePushPull

#define BACK_MOTOR_FAULT_PORT   gpioPortE//D
#define BACK_MOTOR_FAULT_BIT    12//12
#define BACK_MOTOR_FAULT_MODE   gpioModeInputPullFilter

#define BACK_MOTOR_RESET_PORT   gpioPortE//D
#define BACK_MOTOR_RESET_BIT    13//9
#define BACK_MOTOR_RESET_MODE   gpioModePushPull





#define BACK_MOTOR_AT_MID		0
#define BACK_MOTOR_AT_BOTTOM		1
#define BACK_MOTOR_AT_TOP		2
//靠背电动缸最大运行时间ms
#define BACK_MOTOR_MAX_POSITION		1550//1600

//靠背电动缸最大计数位置
#define BACK_MOTOR_MAX_POSITION_PULSE	660//640//674//BACK_MOTOR_MAX_POSITION_PULSE

#define BACK_MIN_SPEED		3
//停止0，刹车1，加速2，缓刹车3，缓加速4
#define BACK_SPEED_STATE_STOP		0
#define BACK_SPEED_STATE_BREAK		1
#define BACK_SPEED_STATE_UP		2
#define BACK_SPEED_STATE_SLOW_BREAK	3
#define BACK_SPEED_STATE_SLOW_UP	4

#define STATE_RUN_BACK_DOWN	0
#define STATE_RUN_BACK_UP	1
#define STATE_BACK_IDLE	2

//#define BACK_MOTOR_TIMER		TIMER0
//#define BACK_MOTOR_TIMER_CHANNEL	1
//#define BACK_MOTOR_ROUTE_EN		TIMER_ROUTE_CC1PEN
//#define BACK_MOTOR_ROUTE_LOCATION	TIMER_ROUTE_LOCATION_LOC2


/*
#define BACK_MOTOR_TIMER           TIMER1//0
#define BACK_MOTOR_TIMER_CHANNEL   0//1
#define BACK_MOTOR_ROUTE_EN        TIMER_ROUTE_CC0PEN
#define BACK_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC2

*/
#define BACK_MOTOR_TIMER           TIMER3
#define BACK_MOTOR_TIMER_CHANNEL   1
#define BACK_MOTOR_ROUTE_EN        TIMER_ROUTE_CC1PEN
#define BACK_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC0


#define BACK_MOTOR_PRESCALE		timerPrescale4//在250V,马达为25V 



#define BACK_MOTOR_DEFAULT_TOP     131//在250V,马达为25V 

//Tosc=(1/28MHZ)=0.035us  ,    周期=131*0.035*4分频=18us,
//Tcy=2Tosc=0.035*2us

//#define BACK_MOTOR_DEFAULT_TOP    100// 100 在250V,马达为25V 
#define BACK_SET_VOLTAGE    250000//250000 // 25V  在250V,马达为25V 

#define BACK_MOTOR_Timer_CCInit     \
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

#define BACK_MOTOR_Timer_Init      \
{                                   \
    true,                           \
    true,                           \
    BACK_MOTOR_PRESCALE,            \
    timerClkSelHFPerClk,            \
    false,                          \
    false,                          \
    timerInputActionNone,           \
    timerInputActionNone,           \
    timerModeUp,                    \
    false,                          \
    false,                          \
    false,                          \
    false,                          \
}

enum
{
	BACK_MOTOR_POWER_ON, 
	BACK_MOTOR_POWER_OFF 
};
enum
{
	BACK_MOTOR_GO_UP, 
	BACK_MOTOR_GO_DOWN 
};

enum
{
	BACK_MOTOR_CURRENT_HIGH,
	BACK_MOTOR_CURRENT_LOW
};

enum
{
	BACK_MOTOR_NORMAL,
	BACK_MOTOR_FAIL
};
int BackPower_On(void);
void BackPower_Off(void);
unsigned int BackRelay_Get(void);
//unsigned int BackPower_Get(void);
void BackMotor_Initial_IO(void);
void BackMotor_Up(void);
void BackMotor_Down(void);
void BackMotor_Break(void);
void BackMotor_Reset(void);
void BackMotor_Reset_Cancel(void);
int BackMotor_Get_Fault(void);
void BackMotor_10ms_int(void);
void BackMotor_Proce(void);
unsigned int BackMotor_Get_Location(void);
unsigned int BackMotor_Get_Position(void);
unsigned char BackMotor_Control(unsigned char nFinalBackPadMotorState);

int BackMotor_GetPower(void);
int BackMotor_GetDirection(void);
void BackMotor_10ms_int(void);
void setBackPadRockingEnable(bool flag);
void BackMotor_Set_Route(void);
void BackMotor_Set_PWM(unsigned long ulDuty);
unsigned int BackMotor_VoltageAdj(unsigned int setDuty);
unsigned int BackPower_Get(void);

extern UINT32 w_Position;




  #endif










#endif
