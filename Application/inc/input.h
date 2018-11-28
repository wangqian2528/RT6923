
#ifndef __INPUT_H__
#define __INPUT_H__


//#define INPUT_KNEAD_MAX_PORT   gpioPortC
//#define INPUT_KNEAD_MAX_BIT    13
//#define INPUT_KNEAD_MAX_MODE   gpioModeInputPullFilter
//
//#define INPUT_KNEAD_MID_PORT   gpioPortC
//#define INPUT_KNEAD_MID_BIT    12
//#define INPUT_KNEAD_MID_MODE   gpioModeInputPullFilter
//
//#define INPUT_KNEAD_MIN_PORT   gpioPortC
//#define INPUT_KNEAD_MIN_BIT    7
//#define INPUT_KNEAD_MIN_MODE   gpioModeInputPullFilter

//#define INPUT_SHOULDER_PULSE_PORT   gpioPortC
//#define INPUT_SHOULDER_PULSE_BIT    6
//#define INPUT_SHOULDER_PULSE_MODE   gpioModeInputPullFilter

/**************************以下小腿伸缩相关*********************************/
//#define INPUT_LEGFLEXUP_SWITCH_PORT       gpioPortD
//#define INPUT_LEGFLEXUP_SWITCH_BIT        0
//#define INPUT_LEGFLEXUP_SWITCH_MODE       gpioModeInputPullFilter
//    
//#define INPUT_LEGFLEXGROUND_SWITCH_PORT       gpioPortD
//#define INPUT_LEGFLEXGROUND_SWITCH_BIT        8
//#define INPUT_LEGFLEXGROUND_SWITCH_MODE       gpioModeInputPullFilter
//    
//#define INPUT_LEGFLEXLINE_SWITCH_PORT       gpioPortC
//#define INPUT_LEGFLEXLINE_SWITCH_BIT        13
//#define INPUT_LEGFLEXLINE_SWITCH_MODE       gpioModeInputPullFilter
//    
//#define INPUT_LEGFLEXDOWN_SWITCH_PORT       1//gpioPortB
//#define INPUT_LEGFLEXDOWN_SWITCH_BIT        14
//#define INPUT_LEGFLEXDOWN_SWITCH_MODE       gpioModeInputPullFilter
//    
//#define INPUT_LEGFLEXMTO_SWITCH_PORT       gpioPortE
//#define INPUT_LEGFLEXMTO_SWITCH_BIT        2
//#define INPUT_LEGFLEXMTO_SWITCH_MODE       gpioModeInputPullFilter
//
//#define INPUT_LEGFLEXMTPM_SWITCH_PORT       gpioPortE
//#define INPUT_LEGFLEXMTPM_SWITCH_BIT        3
//#define INPUT_LEGFLEXMTPM_SWITCH_MODE       gpioModeInputPullFilter
/**************************以上小腿伸缩相关*********************************/

#define INPUT_WALK_PULSE_PORT   gpioPortF//E
#define INPUT_WALK_PULSE_BIT    9//8//3//14
#define INPUT_WALK_PULSE_MODE   gpioModeInputPullFilter

#define INPUT_BACK_PULSE_PORT   gpioPortD//F
#define INPUT_BACK_PULSE_BIT    9
#define INPUT_BACK_PULSE_MODE   gpioModeInputPullFilter



//#define INPUT_AXIS_SW_PORT   gpioPortF
//#define INPUT_AXIS_SW_BIT    4
//#define INPUT_AXIS_SW_MODE   gpioModeInputPullFilter

//#define INPUT_LEG_FOOT_PORT   gpioPortB
//#define INPUT_LEG_FOOT_BIT    3
//#define INPUT_LEG_FOOT_MODE   gpioModeInput

#define KNEAD_WIDTH_UNKNOWN		0
#define KNEAD_WIDTH_MIN			1
#define KNEAD_WIDTH_MED			2
#define KNEAD_WIDTH_MAX			3

//达到极限位置的信号电平
#define REACH_WALK_LIMIT   1// 0   //hull
#define REACH_BACK_LIMIT    1   //limit switch
#define REACH_LEG_LIMIT     1   //limit switch
#define REACH_SLIDE_LIMIT   1   //limit switch
#define REACH_AXIS_LIMIT    1   //limit switch
#define REACH_FLEX_LIMIT    0   //hull

#define WALK_MOTOR_AT_MID     0
#define WALK_MOTOR_AT_BOTTOM  1
#define WALK_MOTOR_AT_TOP     2

#define LEGGROUND_SWITCH_ON	0 		
#define LEGGROUND_SWITCH_OFF	1//小腿伸缩触地开关	

#define LEGANGLE_SWITCH_ON	1 
#define LEGANGLE_SWITCH_OFF	0//小腿伸缩角度开关

#define FOOT_SWITCH_ON		0 
#define FOOT_SWITCH_OFF		1//小腿伸缩脚底开关

#define FLEX_AT_IN              0         
#define FLEX_AT_OUT             0//小腿伸缩限位开关               

#define ARM_IN_LIMIT       1
#define ARM_OUT_LIMIT      2
#define ARM_IN_RUN         4
#define ARM_OUT_RUN        8
#define ARM_IN_PROTECT     0x10

void Input_Initial_IO(void);
void Input_5ms_Int(void);
void Input_Proce(void);
unsigned int Input_GetBackUpSwitch(void);
unsigned int Input_GetBackDownSwitch(void);
unsigned int Input_GetLegUpSwitch(void);
unsigned int Input_GetLegDownSwitch(void);
unsigned int Input_GetWalkUpSwitch(void);
unsigned int Input_GetWalkDownSwitch(void);

unsigned int Input_GetKneadPosition(void);
unsigned int Input_GetKneadMax(void);
unsigned int Input_GetKneadMid(void);
unsigned int Input_GetKneadMin(void);
unsigned int Input_GetMp3Status(void);
unsigned int Input_PowerCheck(void);
//bool Input_GetWalkChange(void);
//void Input_ClearWalkChange(void);
void Input_SetWalkMotorPosition(unsigned short locate);
unsigned short Input_GetWalkMotorPosition(void);
//void Input_SetAxisMotorPosition(unsigned short locate);
unsigned short Input_GetAxisMotorPosition(void);
//void Input_SetCounterWalkMotorPosition(unsigned short locate); 
//unsigned short Input_GetCounterWalkMotorPosition(void);
void Input_SetCounterAxisMotorPosition(unsigned short locate); 
unsigned short Input_GetCounterAxisMotorPosition(void);
unsigned int Input_GetWalkPosition(void);
unsigned int Input_GetSlideForwardSwitch(void);
unsigned int Input_GetSlideBackwardSwitch(void);
//unsigned int Input_GetAxisSW(void);
unsigned int Input_GetReady(void);
bool Input_Get3DFrontSwitch(void);
bool Input_Get3DBackSwitch(void);

unsigned char Input_GetBalance(void);
void KneadMotor_CalculateSpeed(unsigned int kneadPosition);


unsigned int Input_GetBackPosition(void);
void Input_SetBackMotorPosition(unsigned int Position);

unsigned int Input_GetVout(void);

void Input_Back_Pulse1MS(void);
uint8_t Input_Get_Mim_Max();

 extern volatile unsigned int nCurBackLocate;
 
unsigned int Input_GetFlexInSwitch(void);
unsigned int Input_GetFlexOutSwitch(void);
unsigned int Input_GetFlexGroundSwitch(void);
unsigned int Input_GetFlexAngleSwitch(void);
unsigned int Input_GetFlexFootSwitch(void);

void BackMotor_Set_Location(unsigned short locate);
#endif /*__INPUT_H__*/
