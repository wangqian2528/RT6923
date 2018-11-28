#ifndef __SLIDE_MOTOR_H__
#define __SLIDE_MOTOR_H__

#define SLIDE_MOTOR_FAULT_PORT   gpioPortE//A
#define SLIDE_MOTOR_FAULT_BIT    8//1
#define SLIDE_MOTOR_FAULT_MODE   gpioModeInputPullFilter

#define SLIDE_MOTOR_ENBL_PORT   gpioPortE//F
#define SLIDE_MOTOR_ENBL_BIT    14//8
#define SLIDE_MOTOR_ENBL_MODE   gpioModePushPull

#define SLIDE_MOTOR_PHASE_PORT   gpioPortD//A
#define SLIDE_MOTOR_PHASE_BIT    11//15
#define SLIDE_MOTOR_PHASE_MODE   gpioModePushPull

#define SLIDE_MOTOR_DECAY_PORT   gpioPortD//E//A
#define SLIDE_MOTOR_DECAY_BIT   12// 11//0
#define SLIDE_MOTOR_DECAY_MODE   gpioModePushPull

#define SLIDE_MOTOR_RESET_PORT   gpioPortE//A
#define SLIDE_MOTOR_RESET_BIT    9//2
#define SLIDE_MOTOR_RESET_MODE   gpioModePushPull

#define  SLIDE_MOTOR_AT_FORWARD   0
#define  SLIDE_MOTOR_AT_BACKWARD  1
#define  SLIDE_MOTOR_AT_MID       2
//前滑电动缸最大运行时间ms
#define SLIDE_MOTOR_MAX_POSITION 1600

#define STATE_RUN_SLIDE_BACKWARD   0   
#define STATE_RUN_SLIDE_FORWARD    1 
#define STATE_SLIDE_IDLE           2 

#define SLIDE_MOTOR_TIMER           TIMER3//0
#define SLIDE_MOTOR_TIMER_CHANNEL   0//2
#define SLIDE_MOTOR_ROUTE_EN        TIMER_ROUTE_CC0PEN
#define SLIDE_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC0//2

#define SLIDE_MOTOR_PRESCALE        timerPrescale4
#define SLIDE_MOTOR_DEFAULT_TOP     131

#define SLIDE_MOTOR_Timer_CCInit     \
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

#define SLIDE_MOTOR_Timer_Init       \
{                                   \
    true,                           \
    true,                           \
    SLIDE_MOTOR_PRESCALE,           \
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

#define SLIDE_SET_VOLTAGE    250000 //25V

enum
{
  SLIDE_MOTOR_POWER_ON, 
  SLIDE_MOTOR_POWER_OFF 
};

enum
{
  SLIDE_MOTOR_GO_FORWARD, 
  SLIDE_MOTOR_GO_BACKWARD 
};

enum
{
 SLIDE_MOTOR_CURRENT_HIGH,
 SLIDE_MOTOR_CURRENT_LOW
};

enum
{
 SLIDE_MOTOR_NORMAL,
 SLIDE_MOTOR_FAIL
};

void SlideMotor_Initial_IO(void);
void SlideMotor_Reset(void);
void SlideMotor_Reset_Cancel(void);
int SlideMotorPower_On(void);
void SlideMotorPower_Off(void);
void SlideMotor_Forward(void);
void SlideMotor_Backward(void);
void SlideMotor_Break(void);
unsigned int SlideMotor_Get_Fault(void);
unsigned int SlideMotor_Get_Location(void);
unsigned char SlideMotorControl(unsigned char nFinalZeroPadMotorState);

int SlideMotor_GetPower(void);
unsigned int SlideMotor_GetDirection(void);
void SlideMotor_10ms_Int(void);

void SlideMotor_Set_Route(void);
void SlideMotor_Set_PWM(unsigned long ulDuty);

#endif
