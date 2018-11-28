#ifndef __AXIS_MOTOR_H__
#define __AXIS_MOTOR_H__
#include <stdbool.h>

#define AXIS_MOTOR_ENBL_PORT   gpioPortD  
#define AXIS_MOTOR_ENBL_BIT    3
#define AXIS_MOTOR_ENBL_MODE   gpioModePushPull

#define AXIS_MOTOR_FAULT_PORT   gpioPortB  
#define AXIS_MOTOR_FAULT_BIT    14
#define AXIS_MOTOR_FAULT_MODE   gpioModeInputPullFilter

#define AXIS_MOTOR_PHASE_PORT   gpioPortB
#define AXIS_MOTOR_PHASE_BIT    12
#define AXIS_MOTOR_PHASE_MODE   gpioModePushPull

#define AXIS_MOTOR_DECAY_PORT   gpioPortB
#define AXIS_MOTOR_DECAY_BIT    13
#define AXIS_MOTOR_DECAY_MODE   gpioModePushPull

#define AXIS_MOTOR_RESET_PORT   gpioPortA
#define AXIS_MOTOR_RESET_BIT    11
#define AXIS_MOTOR_RESET_MODE   gpioModePushPull

#define AXIS_MOTOR_TIMER           TIMER0
#define AXIS_MOTOR_TIMER_CHANNEL   2
#define AXIS_MOTOR_ROUTE_EN        TIMER_ROUTE_CC2PEN
#define AXIS_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC3//0

#define AXIS_MOTOR_PRESCALE        timerPrescale8
#define AXIS_MOTOR_DEFAULT_TOP     131

#define AXIS_SPEED_STOP     0
#define AXIS_SPEED_SLOW     65
#define AXIS_SPEED_MID      95
#define AXIS_SPEED_FAST     AXIS_MOTOR_DEFAULT_TOP

#define _3D_MIN_PWM  30
#define _3D_MAX_PWM  AXIS_MOTOR_DEFAULT_TOP

//#define AXIS_BEHIND_LIMIT   45
#define REACH_AXIS_FRONT_LIMIT  0// 有74HC14为 1

//#define BODY_DETECT_3D_POSITION  30


#define AXIS_STRONGEST 4  
#define AXIS_STRONGER  3
#define AXIS_MIDDLE    2
#define AXIS_WEAKER    1
#define AXIS_WEAKEST   0

#define _3D_5 AXIS_STRONGEST
#define _3D_4 AXIS_STRONGER
#define _3D_3 AXIS_MIDDLE
#define _3D_2 AXIS_WEAKER
#define _3D_1 AXIS_WEAKEST

//这个参数的单位是10ms,是指脉冲宽度

#define _3D_SPEED_1 16
#define _3D_SPEED_2 15
#define _3D_SPEED_3 14
#define _3D_SPEED_4 13
#define _3D_SPEED_5 12
#define _3D_SPEED_6 11
#define _3D_SPEED_7 10
#define _3D_SPEED_8 9
#define _3D_SPEED_9 8
#define _3D_SPEED_10 7

#define _3D_SPEED_1_PWM  40
#define _3D_SPEED_2_PWM  49
#define _3D_SPEED_3_PWM  58
#define _3D_SPEED_4_PWM  67
#define _3D_SPEED_5_PWM  76
#define _3D_SPEED_6_PWM  85
#define _3D_SPEED_7_PWM  94

#define _3D_SPEED_8_PWM  103
#define _3D_SPEED_9_PWM  114
#define _3D_SPEED_10_PWM  130


#define AXIS_MOTOR_Timer_CCInit     \
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

#define AXIS_MOTOR_Timer_Init       \
{                                   \
    true,                           \
    true,                           \
    AXIS_MOTOR_PRESCALE,            \
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

#define AXIS_BEHIND_LIMIT 40
#define _3D_MAX_POSITION  38
#define _3D_MORE_MED_POSITION  30
#define _3D_MED_POSITION  20
#define _3D_MORE_MIN_POSITION  10
#define _3D_MIN_POSITION  2
#define _3D_POSITION_POINT  5

typedef struct
{
    unsigned int position;                        //电流取样点行走位置
    unsigned int current[AXIS_BEHIND_LIMIT];      //电流取样点上的5个3D位置电流值
    unsigned int _3D_Position[5];                  //电流取样点上的5个3D位置的计数值
}st_n3D_Data;

extern st_n3D_Data*  p3DMotorCurrent; 

enum
{
  AXIS_MOTOR_CURRENT_HIGH,
  AXIS_MOTOR_CURRENT_LOW
};
enum
{
  AXIS_MOTOR_NORMAL,
  AXIS_MOTOR_FAIL
};


enum
{
  AXIS_MOTOR_GO_BACK,
  AXIS_MOTOR_GO_FORWARD 
};
enum
{
   STATE_RUN_AXIS_REAL_POSITION,
   STATE_RUN_AXIS_POSITION,
   STATE_RUN_AXIS_BEHIND,
   STATE_RUN_AXIS_FORWARD,
   STATE_RUN_AXIS_RESET,
   STATE_AXIS_IDLE,
   STATE_RUN_AXIS_F_BEHIND,
   STATE_RUN_AXIS_F_FORWARD,
   STATE_RUN_AXIS_WALK,
   STATE_RUN_AXIS_TOGGLE,
   STATE_RUN_AXIS_3D_KNEAD,
   STATE_RUN_AXIS_KNEAD_HALF,
   STATE_RUN_HALF_CIRCLE_3,
   STATE_RUN_AXIS_CIRCLE
};

#define _3D_MOTOR_WALK_MAX_POSITION 330


#define _3D_FULL_POINT  20     //3d 电流在上下方向上的电流采样点数

#define AXIS_MOTOR_PWM_CLOSE      0
#define AXIS_MOTOR_PWM_OPEN       1

#define AXIS_MOTOR_PWM_20KHZ      20000

#define AXIS_MOTOR_POLAR_NEGATIVE  0
#define AXIS_MOTOR_POLAR_POSITIVE  1

#define AXIS_SET_VOLTAGE    250000 //扩大10000倍
//#define AXIS_SET_LOW_VOLTAGE    90000 //扩大10000倍
#define  AXIS_CURRENT_VALID   1
#define  AXIS_CURRENT_INVALID 0
void Axis_Initial_IO(void);
bool AxisMotor_IsRun(void);
void AxisMotor_ClockRun(void);
void AxisMotor_UnClockRun(void);
void AxisMotor_Break(void);
void AxisMotor_Reset(void);
void AxisMotor_Reset_Cancel(void);
int AxisMotor_Get_Fault(void);
unsigned char AxisMotor_Control(unsigned char nFinalAxisMotorState,unsigned short stopLevel,unsigned int speed);
//unsigned char AxisMotor_Control(unsigned char nFinalAxisMotorState,unsigned short stopLevel,unsigned int PWM);
//unsigned char AxisMotor_Control(unsigned char nFinalAxisMotorState,unsigned short stopLevel);
unsigned int AxisRelay_Get(void);
void Axis_5ms_Int(void);
void AxisMotor_UpdataPosition(void);
//void AxisMotor_CurrentAdj(void);
void AxisMotor_GetCurrent(unsigned int positionCount,unsigned int walkPosition);
unsigned int AxisMotor_Get3DPosition(unsigned int strength);
unsigned int AxisMotor_GetDirection(void);
unsigned int _3D_GetWalkCount(unsigned int walkPosition);
unsigned int _3D_Get_3D_Level(unsigned int walkCount,unsigned int strength);
unsigned int _3D_calculate_3D_count(unsigned int walkPosition,unsigned int strength);
unsigned int _3D_Get_3D_count(unsigned int walkCount,unsigned int strength);
void AxisMotor_StorageCurrent(unsigned int positionCount,unsigned int walkPosition);
void AxisMotor_CurrentAdj(void);
void AxisMotor_10msInt(void);
void AxisMotor_100msInt(void);
void AxisMotor_StorageCurrentClear();

void AxisMotor_Set_Pwm_Data(unsigned long ulDuty);

#endif
