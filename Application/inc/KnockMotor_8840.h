#ifndef __KNOCK_MOTOR_H__
#define __KNOCK_MOTOR_H__


#include "Period.h"

#define KNOCK_MOTOR_ENBL_PORT   gpioPortD//A   //new 
#define KNOCK_MOTOR_ENBL_BIT    1//8
#define KNOCK_MOTOR_ENBL_MODE   gpioModePushPull

#define KNOCK_MOTOR_FAULT_PORT   gpioPortA//B  //new 
#define KNOCK_MOTOR_FAULT_BIT    12//2
#define KNOCK_MOTOR_FAULT_MODE   gpioModeInputPullFilter


#define KNOCK_MOTOR_PHASE_PORT   1//gpioPortA//B //new
#define KNOCK_MOTOR_PHASE_BIT    1//13//4
#define KNOCK_MOTOR_PHASE_MODE   1//gpioModePushPull


#define KNOCK_MOTOR_DECAY_PORT   1//gpioPortD //new
#define KNOCK_MOTOR_DECAY_BIT    1//1
#define KNOCK_MOTOR_DECAY_MODE   1//gpioModePushPull

//#define KNOCK_MOTOR_CURRENT_PORT   gpioPortB
//#define KNOCK_MOTOR_CURRENT_BIT    12
//#define KNOCK_MOTOR_CURRENT_MODE   gpioModePushPull

#define KNOCK_MOTOR_RESET_PORT   gpioPortA//B
#define KNOCK_MOTOR_RESET_BIT    13
#define KNOCK_MOTOR_RESET_MODE   gpioModePushPull

#define KNOCK_MOTOR_TIMER           TIMER0//2
#define KNOCK_MOTOR_TIMER_CHANNEL   0
#define KNOCK_MOTOR_ROUTE_EN        TIMER_ROUTE_CC0PEN
#define KNOCK_MOTOR_ROUTE_LOCATION  TIMER_ROUTE_LOCATION_LOC3//0

#define KNOCK_MOTOR_PRESCALE        timerPrescale8//4
#define KNOCK_MOTOR_DEFAULT_TOP     TOP_PERIOD//131

#define KNOCK_MOTOR_CMU_TIMER       cmuClock_TIMER1

#define KNOCK_MOTOR_Timer_CCInit     \
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

#define KNOCK_MOTOR_Timer_Init      \
{                                   \
    true,                           \
    true,                           \
    KNOCK_MOTOR_PRESCALE,            \
    timerClkSelHFPerClk,            \
    timerInputActionNone,           \
    timerInputActionNone,           \
    timerModeUp,                    \
    false,                          \
    false,                          \
    false,                          \
    false,                          \
}


#define KNOCK_MOTOR_PWM_CLOSE      0
#define KNOCK_MOTOR_PWM_OPEN       1

#define KNOCK_MOTOR_PWM_20KHZ      20000

#define KNOCK_MOTOR_POLAR_NEGATIVE  0
#define KNOCK_MOTOR_POLAR_POSITIVE  1

#define KNOCK_SPEED0_PWM 	0       //0%
#define KNOCK_SPEED1_PWM 	70//300
#define KNOCK_SPEED2_PWM 	82//350
#define KNOCK_SPEED3_PWM 	94//400
#define KNOCK_SPEED4_PWM 	106//450
#define KNOCK_SPEED5_PWM 	118//500
#define KNOCK_SPEED6_PWM 	(TOP_PERIOD+1)   //132//550132//550
#define KNOCK_SET_VOLTAGE       250000 
enum
{
  KNOCK_MOTOR_CURRENT_HIGH,
  KNOCK_MOTOR_CURRENT_LOW
};

enum{
  KNOCK_MOTOR_NORMAL,
  KNOCK_MOTOR_FAIL
};

void KnockMotor_Initial_IO(void);
void KnockMotor_Set_Pwm_Data(unsigned long ulDuty);
void KnockMotor_ClockRun(void);
void KnockMotor_UnClockRun(void);
void KnockMotor_Break(void);
void KnockMotor_Reset(void);
int KnockMotor_Get_Fault(void);
void KnockMotor_SetCurrent(unsigned int current);
unsigned int KnockMotor_GetCurrent(void);
void KnockMotor_AdcCurrent(void);
void KnockMotor_DecCurrent(void);
void KnockSpeed_Up();
#endif
