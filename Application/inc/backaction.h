//按摩椅运行状态描述

#ifndef __backaction_H__
#define __backaction_H__

#include "MassageStatus.h"
#include "AxisMotor.h"



#define KEY_HOLD_ENGINEERING_TIME   50 //单位0.1秒 

#define IDLE_INDICATE_TIME     20
#define WAIT_INDICATE_TIME     10  
#define SETTLE_INDICATE_TIME   3
#define RUN_INDICATE_TIME      5
#define PROBLEM_INDICATE_TIME  1

//背部按摩机构运行模式描述
//背背运行主模式
#define BACK_MAIN_MODE_IDLE			0 //与CHAIR_STATE_IDLE对应
#define BACK_MAIN_MODE_SETTLE		        1 //与CHAIR_STATE_SETTLE对应 
#define BACK_MAIN_MODE_AUTO			2	
#define BACK_MAIN_MODE_MANUAL		        3
#define BACK_MAIN_MODE_3D                       4
#define BACK_MAIN_MODE_DEMO                     5
//背背运行子模式
#define BACK_SUB_MODE_AUTO_0			0//0 //疲劳恢复
#define BACK_SUB_MODE_AUTO_1			1 //舒适按摩
#define BACK_SUB_MODE_AUTO_2			2 //轻松按摩
#define BACK_SUB_MODE_AUTO_3			3 //酸痛改善
#define BACK_SUB_MODE_AUTO_4			4 //颈肩自动
#define BACK_SUB_MODE_AUTO_5			5 //背腰自动



#define BACK_SUB_MODE_AUTO_6			7//6//20   			examine 
#define BACK_SUB_MODE_AUTO_7			8//7//21   			hip-up
#define BACK_SUB_MODE_AUTO_8			9//8//22  				golfer
#define BACK_SUB_MODE_AUTO_9		        6//9//23  			 care
#define BACK_SUB_MODE_AUTO_10			10//24     			growth


//quick
#define BACK_SUB_MODE_AUTO_QUICK_FULL		11
#define BACK_SUB_MODE_AUTO_QUICK_SHOULDER	12
#define BACK_SUB_MODE_AUTO_QUICK_WAIST		13
#define BACK_SUB_MODE_AUTO_QUICK_LEG		14







#define BACK_SUB_MODE_SOFT_KNOCK		16
#define BACK_SUB_MODE_MUSIC			17
//#define BACK_SUB_MODE_BODY_DETECT_0		13
//#define BACK_SUB_MODE_BODY_DETECT_1		14
//#define BACK_SUB_MODE_BODY_DETECT_2		15
#define BACK_SUB_MODE_RUBBING			18//16
#define BACK_SUB_MODE_NO_ACTION			27//6
#define BACK_SUB_MODE_KNEAD			28//7
#define BACK_SUB_MODE_KNOCK			29//8
#define BACK_SUB_MODE_PRESS			30//9
#define BACK_SUB_MODE_WAVELET			31//10


//-----------------------------------------------------------------
#define BACK_SUB_MODE_3D1                15//
#define BACK_SUB_MODE_3D2                16//        
#define BACK_SUB_MODE_3D3                17//       
#define BACK_SUB_MODE_DEMO               35//      21  
#define BACK_SUB_MODE_FULL_AIRBAG        36//       20  


/*wby*/
#define WALK_LOCATE_NeckMax                54
#define WALK_LOCATE_Shoulder_NeckMax_1_3   55 
#define WALK_LOCATE_Shoulder_NeckMax_2_3   56 
#define TOPMAX_POSITION                    57
#define SHOULDER_ADD_PULSE                 58
#define SHOULDER_DEC_PULSE                 59
#define PWM_ABSALUTE                       60
#define SHOULDER_DEC_5                     61
#define SHOULDER_DEC_10                    62
#define WALK_SHOULDER_WAIST_1_20           63
#define WALK_SHOULDER_WAIST_3_20           64
#define WALK_SHOULDER_WAIST_5_20           65
#define WALK_SHOULDER_WAIST_7_20           66
#define WALK_SHOULDER_WAIST_9_20           67
#define WALK_SHOULDER_WAIST_11_20          68
#define WALK_SHOULDER_WAIST_13_20          69
#define WALK_SHOULDER_WAIST_15_20          70
#define WALK_SHOULDER_WAIST_17_20          71
#define WALK_SHOULDER_WAIST_19_20          72
#define WALK_LOCATE_3D_PRESS               73
#define LONG_WALK_KNEAD                    74
#define STOP_WALK_KNEAD                    75
#define STATE_RUN_LOCATE_POSITION          76
#define WALK_PWM                           77
#define PRESS_WALK                         78
#define RUN_UP_DOWN                        79
#define WALK_ADD_PULSE                     80
#define WALK_DEC_PULSE                     81
#define SHOULDER_POSITION                  500    //非脉冲数
#define SHOULDPOS_15                       501
#define SHOULDPOS_70                       502


/*wby*/
#define KNEAD_WALK_MED_MIN              12
#define ADD_UNCLOCKRUN                  13
#define DEC_CLCOKRUN                    14
#define KNEAD_MAX_MED                   15
#define KNEAD_MED_MED                   16
#define KNEAD_MAX_MAX                   17
#define KNEAD_MED_STOP_MED              18
#define KNEAD_RUN_WALK                  19
#define KNEAD_TO_SIDE                   20
#define KNEAD_MAX_MIN                   21
#define KNEAD_RUBBING                   22
#define KNEAD_FITFUL                    23
#define KNEAD_TOGGLE                    24
#define KNEAD_RUN_MULTY                 25
#define KNEAD_RUN_HALF                  26
#define KNEAD_RUN_MAX_MIN               27

//---------云养程序区--------------------------------------------------------
#define BACK_SUB_MODE_NETCLOUD_1               22//fww
#define BACK_SUB_MODE_NETCLOUD_2               23
#define BACK_SUB_MODE_NETCLOUD_3               24
#define BACK_SUB_MODE_NETCLOUD_4               25
#define BACK_SUB_MODE_DIY                      26
//------------------------------------------------------------------------


/*****************************************/
#define SETZERO_LEG_TMIE1			400
#define SETZERO_LEG_TMIE2			1000
#define SETZERO_BACK_TMIE1			400
#define SETZERO_BACK_TMIE2			1000
#define MAXMOTORREMOVETIME		        1600

//行走行程开关到位信号
//RT8600为长行程
#define POSITION_T1				330
#define POSITION_T2				280
#define POSITION_T3				240
#define POSITION_T4				200
#define POSITION_T5				160
#define POSITION_T6				120
#define POSITION_T7				80
#define POSITION_T8				40

#define REACH_LIMIT 				1
//行程参数
#define BODY_TOUCHED 1                          //8600s修改为通讯方式，改为逻辑1，后背光耦开关碰到时的值
#define BODY_NO_TOUCHED 0                          //8600s修改为通讯方式，改为逻辑1，后背光耦开关碰到时的值
#define LIMIT_POSITION				254//280//250//280//8600 100  //肩膀位置的最低点
#define TOP_POSITION 				360//397//8600 215  //肩膀位置的最高点
#define RESET_POSITION				(TOP_POSITION - 30)
#define WAIST_POSITION 				118//130
#define BUTTOCKS_POSITION 			82//90//50
#define LIMIT_PRECISION             32//35  //lgt

//#define TOP_POSITION 				405  //肩膀位置的最高点
#define LOW_DIFF				0
#define HIGH_DIFF				0
#define HALF_PARTIAL_DIFF			25
#define PARTIAL_DIFF				65
//与肩部定位相关的常数
#define DEFAULT_SHOULDER_POSITION	370//330
#define DEFAULT_SHOULDER_POSITION_RELAX	305
#define DEFAULT_NECK_LENGTH		30 
#define DEFAULT_EAR_POSITION		60
#define Med_NECK_LENGTH			15  
#define MAX_SHOULDER_ADJUST_TIME	100 //肩部微调时间，单位：100ms
#define SHOULDER_ADJUST_STEP		30
#define MAX_SHOULDER_ADJUST_DIFF	52 //肩部最大微调距离：5*SHOULDER_ADJUST_STEP + 2(考虑显示和惯性)

//----------------------------------------------------------------------
#define S_NECK_POSITION         360
//肩部320 340
//#define S_SHOULDER_POSITION     320
//背部200 320
//#define S_BACK_POSITION         200
//腰部100 200
//#define S_WAIST_POSITION        120



//肩部320 340

#define S_SHOULDER_HIGH_POSITION    320// 340

#define S_SHOULDER_POSITION     320

#define S_SHOULDER_MIDDLE_POSITION     290
//背部200 320
#define S_BACK_HIGH_POSITION         240

#define S_BACK_MIDDLE_HIGH_POSITION         220

#define S_BACK_POSITION         200
#define S_BACK_MIDDLE_POSITION         200
#define S_BACK_MIDDLE_LOW_POSITION         180

#define S_BACK_LOW_POSITION     165


//腰部100 200
#define S_WAIST_HIGH_POSITION        150
#define S_WAIST_POSITION        120
#define S_WAIST_MIDDLE_POSITION        120
#define S_WAIST_LOW_POSITION        90

#define HIP_H	        60	// BF 16.12.22 官叼橇罚靛 救付 菩畔 HIP_H 备埃
#define HIP_MIDDLE	30	// 20170216
#define HIP_L	         0	// BF 16.12.22 官叼橇罚靛 救付 菩畔 HIP_L 备埃

//--------------------------------------------------------------------------------

#define DEFAULT_BALANCE_POSITION_MAX	290
#define DEFAULT_BALANCE_POSITION_MIN	100








//肩膀位置必须介于最低点和最高点之
//行走电机上电/断电常数
//行走电机上电/断电常数
#ifdef WALK_POWER_LOW
#define WALK_MOTOR_POWER_ON		0
#define WALK_MOTOR_POWER_OFF		1
#endif
#ifdef WALK_POWER_HIGH
#define WALK_MOTOR_POWER_ON		1
#define WALK_MOTOR_POWER_OFF		0
#endif
//行走电机时间描述常数
#define MAX_PARK_TIME			0xff //定点方式时，WalkMotorControl()函数不返回值，确保SOFT_KNOCK正常
//行走电机定位特点
#define LOCATE_POINT			0
#define LOCATE_FULL_BACK		1
#define LOCATE_UPPER_BACK		2
#define LOCATE_LOWER_BACK		3
#define LOCATE_SHOULDER			4
#define LOCATE_BACK			5
#define LOCATE_WAIST			6
#define LOCATE_PARTIAL			7
#define LOCATE_NONE			8
//行走电机定位方式
#define WALK_LOCATE_ABSULATE			0
#define WALK_LOCATE_SHOULDER			3  //肩膀位置
#define WALK_LOCATE_TOP				2
#define WALK_LOCATE_SHOULDER_OR_ABSULATE	1
#define WALK_LOCATE_PARK			4
//#define WALK_LOCATE_NeckSwitch			5
#define WALK_LOCATE_NeckMed			6  //脖子中间位置
#define WALK_LOCATE_PressNeck			7  //脖子靠近肩膀位置

#define WALK_LOCATE_WAIST             8
#define WALK_SHOULDER_WAIST_1_10      9  //肩膀向腰的位置移动1/10的距离
#define WALK_SHOULDER_WAIST_2_10      10 //肩膀向腰的位置移动2/10的距离
#define WALK_SHOULDER_WAIST_3_10      11 //肩膀向腰的位置移动3/10的距离
#define WALK_SHOULDER_WAIST_4_10      12 //肩膀向腰的位置移动4/10的距离
#define WALK_SHOULDER_WAIST_5_10      13 //肩膀向腰的位置移动5/10的距离
#define WALK_SHOULDER_WAIST_6_10      14 //肩膀向腰的位置移动6/10的距离
#define WALK_SHOULDER_WAIST_7_10      15 //肩膀向腰的位置移动7/10的距离
#define WALK_SHOULDER_WAIST_8_10      16 //肩膀向腰的位置移动8/10的距离
#define WALK_SHOULDER_WAIST_9_10      17 //肩膀向腰的位置移动9/10的距离

#define WALK_LOCATE_Ear			18  //ear 
#define WALK_SHOULDER_WAIST_1_9      19 //肩膀向腰的位置移动2/10的距离
/////////////////////////////////////////////////////////////////////////


//--------------------------------------用于GROWTH ,CARE自动程序

#define WALK_LOCATE_UNDER_SHOULDER  20  //新增加  ,用于 三个自动程序
#define WALK_LOCATE_ABSULATE_SLOW	     21
#define WALK_LOCATE_SHOULDER_SLOW            22
#define WALK_LOCATE_NeckMed_SLOW             23
#define WALK_LOCATE_SHOULDER_SLOW_SLOW       24
#define WALK_LOCATE_NeckMed_SLOW_FAST        25
#define WALK_LOCATE_ABSULATE_SLOW_FAST       26
#define WALK_LOCATE_SHOULDER_SLOW_FAST       27
#define WALK_LOCATE_NeckMed_SLOW_SLOW        28
#define WALK_LOCATE_ABSULATE_SLOW_SLOW       29
#define WALK_LOCATE_ABSULATE_SLOW_SLOW_FAST  30
#define WALK_LOCATE_SHOULDER_SLOW_SLOW_FAST  31
#define WALK_LOCATE_ABSULATE_SLOWFAST	     32
#define WALK_LOCATE_SHOULDER_SLOWFAST        33


#define WALK_LOCATE_NECK_POSITION               34
#define WALK_LOCATE_SHOULDER_POSITION           35
#define WALK_LOCATE_BELLOW_SHOULDER		36
#define WALK_LOCATE_BACK_POSITION               37
#define WALK_LOCATE_WAIST_POSITION              38

//--------------------------------------------------------------------------

#define WALK_LOCATE_BACK_MIDDLE_HIGH_POSITION         45
#define WALK_LOCATE_BACK_MIDDLE_POSITION              46
#define WALK_LOCATE_BACK_MIDDLE_LOW_POSITION          47 
#define WALK_LOCATE_BACK_LOW_POSITION                 48

#define WALK_LOCATE_WAIST_HIGH_POSITION                49
#define WALK_LOCATE_WAIST_MIDDLE_POSITION              50
#define WALK_LOCATE_WAIST_LOW_POSITION                 51

#define WALK_LOCATE_SHOULDER_MIDDLE_POSITION           52
#define WALK_LOCATE_BACK_HIGH_POSITION                 53
#define WALK_LOCATE_SHOULDER_HIGH_POSITION             54

#define STOP_WALK_KNEAD_3                              82

//--------------------------------------------------------------------

//揉捏电机描述常数
#define KNEAD_STOP			0 //按摩臂停留在随机位置
#define KNEAD_STOP_AT_MIN		1 //按摩臂停留在窄的位置
#define KNEAD_STOP_AT_MED		2 //按摩臂停留在中的位置
#define KNEAD_STOP_AT_MAX		3 //按摩臂停留在宽的位置
#define KNEAD_RUN			4 //按摩臂顺时钟方向揉捏
#define KNEAD_RUN_STOP		 	5 //按摩臂CLOCK方向n圈后停留在随机位置
#define KNEAD_RUN_STOP_AT_MIN 	        6 //按摩臂CLOCK方向n圈后停留在窄的位置
#define KNEAD_RUN_STOP_AT_MED 	        7 //按摩臂CLOCK方向n圈后停留在中的位置
#define KNEAD_RUN_STOP_AT_MAX 	        8 //按摩臂CLOCK方向n圈后停留在宽的位置
#define KNEAD_RUN_RUBBING 	        9 //
#define KNEAD_RUN_MEDRUBBING 	        10 //
#define KNEAD_RUN_MAXRUBBING 	        11 //
#define KNEAD_ANTIRUN	                12
#define KNEAD_WALK_MED_MED_3D_3         13

#define KNEAD_STOP_AT_POSITION_TIME              12
#define KNEAD_STOP_AT_FORWARD_REWIND            13








//揉捏臂宽度定义
/*
#define KNEAD_WIDTH_UNKNOWN		0
#define KNEAD_WIDTH_MIN			1
#define KNEAD_WIDTH_MED			2
#define KNEAD_WIDTH_MAX			3
*/
#define DISPLAY_WIDTH_OFF		0
#define DISPLAY_WIDTH_MIN		1
#define DISPLAY_WIDTH_MED		2
#define DISPLAY_WIDTH_MAX		3
//揉捏速度PWM常数定义
//敲打电机描述常数
#define KNOCK_STOP		0 //停止
#define KNOCK_RUN_WIDTH		1 //宽中窄定位完成后启动
#define KNOCK_RUN		2 //无需宽中窄定位，无条件立即启动
#define KNOCK_RUN_STOP		3 //宽中窄定位完成后启动短时间后马上停止
#define KNOCK_RUN_MUSIC		4 //音乐互动模式（与宽中窄定位无关）

//3D电机描述常数
#define AXIS_1		0 //3D按摩头最靠后 力度最小
#define AXIS_2		1 //3D按摩头较靠后 力度较小
#define AXIS_3		2 //3D按摩头在中间位置 力度适中
#define AXIS_4		3 //3D按摩头较靠前 力度较大
#define AXIS_5		4 //3D按摩头最靠前 力度最大
#define AXIS_AUTO	5 //依据电流自动调整按摩头位置

#define KNOCK_RUN_WIDTH		1 //宽中窄定位完成后启动
#define KNOCK_RUN		2 //无需宽中窄定位，无条件立即启动
#define KNOCK_RUN_STOP		3 //宽中窄定位完成后启动短时间后马上停止
#define KNOCK_RUN_MUSIC		4 //音乐互动模式（与宽中窄定位无关）
#define KNOCK_PWM               5

#define _3D_MANUAL      0   //依据用户设定3D力度动作
#define _3D_PROGRAM     1   //依据设定的3D位置动作
#define _3D_CURRENT     2   //依据电流检测位置动作
#define _3D_PARK        3   //3D马达停留在当前位置

#define _3D_RUN_PRESSURE    1 //3D指压  3D机芯前后运动 揉捏停止 敲击停止 可调节宽中窄 可进行局部定点全身按摩 
#define _3D_AUTO_WALK       6
#define _3D_SIDE_TOGGLE     7
#define _3D_KNEAD           8
#define _3D_KNEAD_HALF      9
#define _3D_WORK_CIRCLE     10
#define _3D_KNEAD_NECK_3    11


#define _3D_WEAK_TIME       20  //3d 指压时停在最后面的时间
#define _3D_STRONG_TIME     40  //3d 指压时停在最前面的时间

//敲打速度PWM常数定义(指压敲打)
//#define MANUAL_SPEED0_PWM 	0 //0%
//#define MANUAL_SPEED1_PWM 	300
//#define MANUAL_SPEED2_PWM 	325
//#define MANUAL_SPEED3_PWM 	350
//#define MANUAL_SPEED4_PWM 	375
//#define MANUAL_SPEED5_PWM 	400
//#define MANUAL_SPEED6_PWM 	425 
//#define MANUAL_SPEED7_PWM 	450
//#define MANUAL_SPEED8_PWM 	475
//#define MANUAL_SPEED9_PWM 	500
//#define MANUAL_SPEED10_PWM 	550

//与音乐互动相关
#define MAX_MUSIC_KNOCK_PWM	KNOCK_SPEED6_PWM	
#define MIN_MUSIC_KNOCK_PWM	KNOCK_SPEED1_PWM
#define MUSIC_KNOCK_AD_RATIO 3
//整机揉捏敲打速度常数定义
#define SPEED_0		0
#define SPEED_1		1
#define SPEED_2		2
#define SPEED_3		3
#define SPEED_4		4
#define SPEED_5		5
#define SPEED_6		6
#define SPEED_7		7

//靠背电动缸上电/断电常数
#define BACKPAD_MOTOR_POWER_ON		1
#define BACKPAD_MOTOR_POWER_OFF		0
//小腿电动缸上电/断电常数
#define LEGPAD_MOTOR_POWER_ON		1
#define LEGPAD_MOTOR_POWER_OFF		0

//继电器+Mosfet+Brake电路电机状态定义(无继电器只取前面5种状态)
#define STATE_IDLE				0
#define STATE_RUN_CLOCK				1
#define STATE_STOP_CLOCK_HV			2
#define STATE_STOP_CLOCK_BRAKE		        3
#define STATE_STOP_CLOCK_ZV			4
#define STATE_RUN_ANTICLOCK			5
#define STATE_STOP_ANTICLOCK_HV		        6
#define STATE_STOP_ANTICLOCK_BRAKE	        7
#define STATE_STOP_ANTICLOCK_ZV		        8
#define STATE_RUN_UNCLOCK			9
//继电器+Mosfet电机状态时间
#define PRE_BRAKE_TIME				30//5  //20 //Unit:10ms 断电到刹车前的时间
#define BRAKE_TIME				35 //10 //Unit:10ms 刹车时间
#define POST_BRAKE_TIME				30//5  //2  //Unit:10ms 刹车之后的延时时间
#define RELAY_STABLE_TIME 			25 //15 //Unit:10ms 继电器换向后的稳定时间
//继电器+Mosfet电机方向定义
#define BRAKE_OFF				0
#define BRAKE_ON				1
#define DIRECTION_RELAY_CLOCK			0
#define DIRECTION_RELAY_ANTICLOCK		1

//记忆功能常数定义
#define MEMORY_SET_OFF		0
#define MEMORY_SET_START	1		
#define MEMORY_SET_FINISH	2

#define MEMORY_SET_START_TIME	40 //50 //UNIT:100MS		
#define MEMORY_SET_FINISH_TIME	60 //20 //UNIT:100MS


typedef struct Walk_Knead_Knock_Motor_Struct_Auto
{
  //1st byte
  unsigned char nSubFunction ;
  unsigned char nWalkMotorLocateMethod ;
  //2nd byte
  unsigned short nWalkMotorLocateParam;  //长行程
  //3rd byte
  unsigned nKneadMotorState:8 ;
  unsigned nKneadMotorCycles:5 ;
  //4th byte(KNOCK_STOP,KNOCK_RUN_WIDTH,KNOCK_RUN,KNOCK_RUN_STOP,KNOCK_RUN_MUSIC)	
  //Only 4 states for auto mode
  unsigned nKnockMotorState:3 ;
  unsigned nKnockMotorRunTime:6 ;//敲打持续的时间
  //5th byte
  unsigned nKnockMotorStopTime:5 ;//敲打停顿的时间
  //unsigned nAxisMotorPosition ;//敲打停顿的时间
  unsigned nKneadKnockSpeed:3 ;
  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;
} WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO ;

/*********************************/
typedef struct Walk_Knead_Knock_Motor_Struct_Manual
{
  //子功能索引(用于显示)
  //KNEAD,KNOCK,PRESS,WAVELET,PREPARE
  unsigned char nSubFunction ;
  //行走电机定位方式
  //0:WALK_LOCATE_ABSULATE:由绝对坐标决定
  //1:WALK_LOCATE_SHOULDER:由肩部位置决定
  //2:WALK_LOCATE_TOP:由上端行程开关决定
  //3:WALK_LOCATE_SHOULDER_OR_ABSULATE:由肩部位置和绝对坐标中的较小者决定
  //4:WALK_LOCATE_PARK:停留在当前位置
  unsigned char nWalkMotorLocateMethod ;
  //行走电机定位的绝对坐标或在PARK时的停顿时间
  unsigned short nWalkMotorLocateParam ; //长行程
  //揉捏电机描述(包含了结束条件)
  //KNEAD_STOP			0 //按摩臂停留在随机位置
  //KNEAD_STOP_AT_MIN		1 //按摩臂停留在窄的位置
  //KNEAD_STOP_AT_MED		2 //按摩臂停留在中的位置
  //KNEAD_STOP_AT_MAX		3 //按摩臂停留在宽的位置
  //KNEAD_RUN			4 //按摩臂顺时钟方向揉捏
  //KNEAD_RUN_STOP		5 //按摩臂n圈后停留在随机位置
  //KNEAD_RUN_STOP_AT_MIN       6 //按摩臂n圈后停留在窄的位置
  //KNEAD_RUN_STOP_AT_MED       7 //按摩臂n圈后停留在中的位置
  //KNEAD_RUN_STOP_AT_MAX       8 //按摩臂n圈后停留在宽的位置	
  unsigned char nKneadMotorState ;
  //揉捏圈数
  unsigned char nKneadMotorCycles ;
  //揉捏方向 RT8600
  // unsigned char nKneadMotorPhase ;  
  //敲打电机要达到的状态
  //KNOCK_STOP/KNOCK_RUN_WIDTH/KNOCK_RUN/KNOCK_RUN_STOP
  unsigned char nKnockMotorState ;
  unsigned char nKnockMotorRunTime ;//敲打持续的时间
  unsigned char nKnockMotorStopTime ;//敲打停顿的时间
  //揉捏与敲打的速度	
  //SPEED_0,SPEED_2,SPEED_3,SPEED_4
  unsigned char nKneadKnockSpeed ;
  unsigned char _3D_Position;
  unsigned char _3D_Speed;
  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;
} WALK_KNEAD_KNOCK_MOTOR_STRUCT_MANUAL ;



//===================DIY 定义区

typedef struct Walk_Knead_Knock_Motor_Struct_DIY_Manual
{
  //子功能索引(用于显示)
  //KNEAD,KNOCK,PRESS,WAVELET,PREPARE
  unsigned char nSubFunction ;
  //行走电机定位方式
  //0:WALK_LOCATE_ABSULATE:由绝对坐标决定
  //1:WALK_LOCATE_SHOULDER:由肩部位置决定
  //2:WALK_LOCATE_TOP:由上端行程开关决定
  //3:WALK_LOCATE_SHOULDER_OR_ABSULATE:由肩部位置和绝对坐标中的较小者决定
  //4:WALK_LOCATE_PARK:停留在当前位置
  unsigned char nWalkMotorLocateMethod ;
  //行走电机定位的绝对坐标或在PARK时的停顿时间
  unsigned short nWalkMotorLocateParam ; //长行程
  //揉捏电机描述(包含了结束条件)
  //KNEAD_STOP			0 //按摩臂停留在随机位置
  //KNEAD_STOP_AT_MIN		1 //按摩臂停留在窄的位置
  //KNEAD_STOP_AT_MED		2 //按摩臂停留在中的位置
  //KNEAD_STOP_AT_MAX		3 //按摩臂停留在宽的位置
  //KNEAD_RUN			4 //按摩臂顺时钟方向揉捏
  //KNEAD_RUN_STOP		5 //按摩臂n圈后停留在随机位置
  //KNEAD_RUN_STOP_AT_MIN       6 //按摩臂n圈后停留在窄的位置
  //KNEAD_RUN_STOP_AT_MED       7 //按摩臂n圈后停留在中的位置
  //KNEAD_RUN_STOP_AT_MAX       8 //按摩臂n圈后停留在宽的位置	
  unsigned char nKneadMotorState ;
  //揉捏圈数
  unsigned char nKneadMotorCycles ;
  //揉捏方向 RT8600
  // unsigned char nKneadMotorPhase ;  
  //敲打电机要达到的状态
  //KNOCK_STOP/KNOCK_RUN_WIDTH/KNOCK_RUN/KNOCK_RUN_STOP
  unsigned char nKnockMotorState ;
  unsigned char nKnockMotorRunTime ;//敲打持续的时间
  unsigned char nKnockMotorStopTime ;//敲打停顿的时间
  //揉捏与敲打的速度	
  //SPEED_0,SPEED_2,SPEED_3,SPEED_4
  unsigned char nKneadKnockSpeed ;
  unsigned char _3D_Position;
  unsigned char _3D_Speed;
  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;
} WALK_KNEAD_KNOCK_MOTOR_STRUCT__DIY_MANUAL ;











#endif




/*************************************************************/
