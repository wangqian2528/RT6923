//��Ħ������״̬����

#ifndef __backaction_H__
#define __backaction_H__

#include "MassageStatus.h"
#include "AxisMotor.h"



#define KEY_HOLD_ENGINEERING_TIME   50 //��λ0.1�� 

#define IDLE_INDICATE_TIME     20
#define WAIT_INDICATE_TIME     10  
#define SETTLE_INDICATE_TIME   3
#define RUN_INDICATE_TIME      5
#define PROBLEM_INDICATE_TIME  1

//������Ħ��������ģʽ����
//����������ģʽ
#define BACK_MAIN_MODE_IDLE			0 //��CHAIR_STATE_IDLE��Ӧ
#define BACK_MAIN_MODE_SETTLE		        1 //��CHAIR_STATE_SETTLE��Ӧ 
#define BACK_MAIN_MODE_AUTO			2	
#define BACK_MAIN_MODE_MANUAL		        3
#define BACK_MAIN_MODE_3D                       4
#define BACK_MAIN_MODE_DEMO                     5
//����������ģʽ
#define BACK_SUB_MODE_AUTO_0			0//0 //ƣ�ͻָ�
#define BACK_SUB_MODE_AUTO_1			1 //���ʰ�Ħ
#define BACK_SUB_MODE_AUTO_2			2 //���ɰ�Ħ
#define BACK_SUB_MODE_AUTO_3			3 //��ʹ����
#define BACK_SUB_MODE_AUTO_4			4 //�����Զ�
#define BACK_SUB_MODE_AUTO_5			5 //�����Զ�



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
#define SHOULDER_POSITION                  500    //��������
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

//---------����������--------------------------------------------------------
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

//�����г̿��ص�λ�ź�
//RT8600Ϊ���г�
#define POSITION_T1				330
#define POSITION_T2				280
#define POSITION_T3				240
#define POSITION_T4				200
#define POSITION_T5				160
#define POSITION_T6				120
#define POSITION_T7				80
#define POSITION_T8				40

#define REACH_LIMIT 				1
//�г̲���
#define BODY_TOUCHED 1                          //8600s�޸�ΪͨѶ��ʽ����Ϊ�߼�1���󱳹��������ʱ��ֵ
#define BODY_NO_TOUCHED 0                          //8600s�޸�ΪͨѶ��ʽ����Ϊ�߼�1���󱳹��������ʱ��ֵ
#define LIMIT_POSITION				254//280//250//280//8600 100  //���λ�õ���͵�
#define TOP_POSITION 				360//397//8600 215  //���λ�õ���ߵ�
#define RESET_POSITION				(TOP_POSITION - 30)
#define WAIST_POSITION 				118//130
#define BUTTOCKS_POSITION 			82//90//50
#define LIMIT_PRECISION             32//35  //lgt

//#define TOP_POSITION 				405  //���λ�õ���ߵ�
#define LOW_DIFF				0
#define HIGH_DIFF				0
#define HALF_PARTIAL_DIFF			25
#define PARTIAL_DIFF				65
//��粿��λ��صĳ���
#define DEFAULT_SHOULDER_POSITION	370//330
#define DEFAULT_SHOULDER_POSITION_RELAX	305
#define DEFAULT_NECK_LENGTH		30 
#define DEFAULT_EAR_POSITION		60
#define Med_NECK_LENGTH			15  
#define MAX_SHOULDER_ADJUST_TIME	100 //�粿΢��ʱ�䣬��λ��100ms
#define SHOULDER_ADJUST_STEP		30
#define MAX_SHOULDER_ADJUST_DIFF	52 //�粿���΢�����룺5*SHOULDER_ADJUST_STEP + 2(������ʾ�͹���)

//----------------------------------------------------------------------
#define S_NECK_POSITION         360
//�粿320 340
//#define S_SHOULDER_POSITION     320
//����200 320
//#define S_BACK_POSITION         200
//����100 200
//#define S_WAIST_POSITION        120



//�粿320 340

#define S_SHOULDER_HIGH_POSITION    320// 340

#define S_SHOULDER_POSITION     320

#define S_SHOULDER_MIDDLE_POSITION     290
//����200 320
#define S_BACK_HIGH_POSITION         240

#define S_BACK_MIDDLE_HIGH_POSITION         220

#define S_BACK_POSITION         200
#define S_BACK_MIDDLE_POSITION         200
#define S_BACK_MIDDLE_LOW_POSITION         180

#define S_BACK_LOW_POSITION     165


//����100 200
#define S_WAIST_HIGH_POSITION        150
#define S_WAIST_POSITION        120
#define S_WAIST_MIDDLE_POSITION        120
#define S_WAIST_LOW_POSITION        90

#define HIP_H	        60	// BF 16.12.22 �ٵ������� �ȸ� ���� HIP_H ����
#define HIP_MIDDLE	30	// 20170216
#define HIP_L	         0	// BF 16.12.22 �ٵ������� �ȸ� ���� HIP_L ����

//--------------------------------------------------------------------------------

#define DEFAULT_BALANCE_POSITION_MAX	290
#define DEFAULT_BALANCE_POSITION_MIN	100








//���λ�ñ��������͵����ߵ�֮
//���ߵ���ϵ�/�ϵ糣��
//���ߵ���ϵ�/�ϵ糣��
#ifdef WALK_POWER_LOW
#define WALK_MOTOR_POWER_ON		0
#define WALK_MOTOR_POWER_OFF		1
#endif
#ifdef WALK_POWER_HIGH
#define WALK_MOTOR_POWER_ON		1
#define WALK_MOTOR_POWER_OFF		0
#endif
//���ߵ��ʱ����������
#define MAX_PARK_TIME			0xff //���㷽ʽʱ��WalkMotorControl()����������ֵ��ȷ��SOFT_KNOCK����
//���ߵ����λ�ص�
#define LOCATE_POINT			0
#define LOCATE_FULL_BACK		1
#define LOCATE_UPPER_BACK		2
#define LOCATE_LOWER_BACK		3
#define LOCATE_SHOULDER			4
#define LOCATE_BACK			5
#define LOCATE_WAIST			6
#define LOCATE_PARTIAL			7
#define LOCATE_NONE			8
//���ߵ����λ��ʽ
#define WALK_LOCATE_ABSULATE			0
#define WALK_LOCATE_SHOULDER			3  //���λ��
#define WALK_LOCATE_TOP				2
#define WALK_LOCATE_SHOULDER_OR_ABSULATE	1
#define WALK_LOCATE_PARK			4
//#define WALK_LOCATE_NeckSwitch			5
#define WALK_LOCATE_NeckMed			6  //�����м�λ��
#define WALK_LOCATE_PressNeck			7  //���ӿ������λ��

#define WALK_LOCATE_WAIST             8
#define WALK_SHOULDER_WAIST_1_10      9  //���������λ���ƶ�1/10�ľ���
#define WALK_SHOULDER_WAIST_2_10      10 //���������λ���ƶ�2/10�ľ���
#define WALK_SHOULDER_WAIST_3_10      11 //���������λ���ƶ�3/10�ľ���
#define WALK_SHOULDER_WAIST_4_10      12 //���������λ���ƶ�4/10�ľ���
#define WALK_SHOULDER_WAIST_5_10      13 //���������λ���ƶ�5/10�ľ���
#define WALK_SHOULDER_WAIST_6_10      14 //���������λ���ƶ�6/10�ľ���
#define WALK_SHOULDER_WAIST_7_10      15 //���������λ���ƶ�7/10�ľ���
#define WALK_SHOULDER_WAIST_8_10      16 //���������λ���ƶ�8/10�ľ���
#define WALK_SHOULDER_WAIST_9_10      17 //���������λ���ƶ�9/10�ľ���

#define WALK_LOCATE_Ear			18  //ear 
#define WALK_SHOULDER_WAIST_1_9      19 //���������λ���ƶ�2/10�ľ���
/////////////////////////////////////////////////////////////////////////


//--------------------------------------����GROWTH ,CARE�Զ�����

#define WALK_LOCATE_UNDER_SHOULDER  20  //������  ,���� �����Զ�����
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

//��������������
#define KNEAD_STOP			0 //��Ħ��ͣ�������λ��
#define KNEAD_STOP_AT_MIN		1 //��Ħ��ͣ����խ��λ��
#define KNEAD_STOP_AT_MED		2 //��Ħ��ͣ�����е�λ��
#define KNEAD_STOP_AT_MAX		3 //��Ħ��ͣ���ڿ��λ��
#define KNEAD_RUN			4 //��Ħ��˳ʱ�ӷ�������
#define KNEAD_RUN_STOP		 	5 //��Ħ��CLOCK����nȦ��ͣ�������λ��
#define KNEAD_RUN_STOP_AT_MIN 	        6 //��Ħ��CLOCK����nȦ��ͣ����խ��λ��
#define KNEAD_RUN_STOP_AT_MED 	        7 //��Ħ��CLOCK����nȦ��ͣ�����е�λ��
#define KNEAD_RUN_STOP_AT_MAX 	        8 //��Ħ��CLOCK����nȦ��ͣ���ڿ��λ��
#define KNEAD_RUN_RUBBING 	        9 //
#define KNEAD_RUN_MEDRUBBING 	        10 //
#define KNEAD_RUN_MAXRUBBING 	        11 //
#define KNEAD_ANTIRUN	                12
#define KNEAD_WALK_MED_MED_3D_3         13

#define KNEAD_STOP_AT_POSITION_TIME              12
#define KNEAD_STOP_AT_FORWARD_REWIND            13








//����ۿ�ȶ���
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
//�����ٶ�PWM��������
//�ô�����������
#define KNOCK_STOP		0 //ֹͣ
#define KNOCK_RUN_WIDTH		1 //����խ��λ��ɺ�����
#define KNOCK_RUN		2 //�������խ��λ����������������
#define KNOCK_RUN_STOP		3 //����խ��λ��ɺ�������ʱ�������ֹͣ
#define KNOCK_RUN_MUSIC		4 //���ֻ���ģʽ�������խ��λ�޹أ�

//3D�����������
#define AXIS_1		0 //3D��Ħͷ��� ������С
#define AXIS_2		1 //3D��Ħͷ�Ͽ��� ���Ƚ�С
#define AXIS_3		2 //3D��Ħͷ���м�λ�� ��������
#define AXIS_4		3 //3D��Ħͷ�Ͽ�ǰ ���Ƚϴ�
#define AXIS_5		4 //3D��Ħͷ�ǰ �������
#define AXIS_AUTO	5 //���ݵ����Զ�������Ħͷλ��

#define KNOCK_RUN_WIDTH		1 //����խ��λ��ɺ�����
#define KNOCK_RUN		2 //�������խ��λ����������������
#define KNOCK_RUN_STOP		3 //����խ��λ��ɺ�������ʱ�������ֹͣ
#define KNOCK_RUN_MUSIC		4 //���ֻ���ģʽ�������խ��λ�޹أ�
#define KNOCK_PWM               5

#define _3D_MANUAL      0   //�����û��趨3D���ȶ���
#define _3D_PROGRAM     1   //�����趨��3Dλ�ö���
#define _3D_CURRENT     2   //���ݵ������λ�ö���
#define _3D_PARK        3   //3D���ͣ���ڵ�ǰλ��

#define _3D_RUN_PRESSURE    1 //3Dָѹ  3D��оǰ���˶� ����ֹͣ �û�ֹͣ �ɵ��ڿ���խ �ɽ��оֲ�����ȫ��Ħ 
#define _3D_AUTO_WALK       6
#define _3D_SIDE_TOGGLE     7
#define _3D_KNEAD           8
#define _3D_KNEAD_HALF      9
#define _3D_WORK_CIRCLE     10
#define _3D_KNEAD_NECK_3    11


#define _3D_WEAK_TIME       20  //3d ָѹʱͣ��������ʱ��
#define _3D_STRONG_TIME     40  //3d ָѹʱͣ����ǰ���ʱ��

//�ô��ٶ�PWM��������(ָѹ�ô�)
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

//�����ֻ������
#define MAX_MUSIC_KNOCK_PWM	KNOCK_SPEED6_PWM	
#define MIN_MUSIC_KNOCK_PWM	KNOCK_SPEED1_PWM
#define MUSIC_KNOCK_AD_RATIO 3
//���������ô��ٶȳ�������
#define SPEED_0		0
#define SPEED_1		1
#define SPEED_2		2
#define SPEED_3		3
#define SPEED_4		4
#define SPEED_5		5
#define SPEED_6		6
#define SPEED_7		7

//�����綯���ϵ�/�ϵ糣��
#define BACKPAD_MOTOR_POWER_ON		1
#define BACKPAD_MOTOR_POWER_OFF		0
//С�ȵ綯���ϵ�/�ϵ糣��
#define LEGPAD_MOTOR_POWER_ON		1
#define LEGPAD_MOTOR_POWER_OFF		0

//�̵���+Mosfet+Brake��·���״̬����(�޼̵���ֻȡǰ��5��״̬)
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
//�̵���+Mosfet���״̬ʱ��
#define PRE_BRAKE_TIME				30//5  //20 //Unit:10ms �ϵ絽ɲ��ǰ��ʱ��
#define BRAKE_TIME				35 //10 //Unit:10ms ɲ��ʱ��
#define POST_BRAKE_TIME				30//5  //2  //Unit:10ms ɲ��֮�����ʱʱ��
#define RELAY_STABLE_TIME 			25 //15 //Unit:10ms �̵����������ȶ�ʱ��
//�̵���+Mosfet���������
#define BRAKE_OFF				0
#define BRAKE_ON				1
#define DIRECTION_RELAY_CLOCK			0
#define DIRECTION_RELAY_ANTICLOCK		1

//���书�ܳ�������
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
  unsigned short nWalkMotorLocateParam;  //���г�
  //3rd byte
  unsigned nKneadMotorState:8 ;
  unsigned nKneadMotorCycles:5 ;
  //4th byte(KNOCK_STOP,KNOCK_RUN_WIDTH,KNOCK_RUN,KNOCK_RUN_STOP,KNOCK_RUN_MUSIC)	
  //Only 4 states for auto mode
  unsigned nKnockMotorState:3 ;
  unsigned nKnockMotorRunTime:6 ;//�ô������ʱ��
  //5th byte
  unsigned nKnockMotorStopTime:5 ;//�ô�ͣ�ٵ�ʱ��
  //unsigned nAxisMotorPosition ;//�ô�ͣ�ٵ�ʱ��
  unsigned nKneadKnockSpeed:3 ;
  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;
} WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO ;

/*********************************/
typedef struct Walk_Knead_Knock_Motor_Struct_Manual
{
  //�ӹ�������(������ʾ)
  //KNEAD,KNOCK,PRESS,WAVELET,PREPARE
  unsigned char nSubFunction ;
  //���ߵ����λ��ʽ
  //0:WALK_LOCATE_ABSULATE:�ɾ����������
  //1:WALK_LOCATE_SHOULDER:�ɼ粿λ�þ���
  //2:WALK_LOCATE_TOP:���϶��г̿��ؾ���
  //3:WALK_LOCATE_SHOULDER_OR_ABSULATE:�ɼ粿λ�ú;��������еĽ�С�߾���
  //4:WALK_LOCATE_PARK:ͣ���ڵ�ǰλ��
  unsigned char nWalkMotorLocateMethod ;
  //���ߵ����λ�ľ����������PARKʱ��ͣ��ʱ��
  unsigned short nWalkMotorLocateParam ; //���г�
  //����������(�����˽�������)
  //KNEAD_STOP			0 //��Ħ��ͣ�������λ��
  //KNEAD_STOP_AT_MIN		1 //��Ħ��ͣ����խ��λ��
  //KNEAD_STOP_AT_MED		2 //��Ħ��ͣ�����е�λ��
  //KNEAD_STOP_AT_MAX		3 //��Ħ��ͣ���ڿ��λ��
  //KNEAD_RUN			4 //��Ħ��˳ʱ�ӷ�������
  //KNEAD_RUN_STOP		5 //��Ħ��nȦ��ͣ�������λ��
  //KNEAD_RUN_STOP_AT_MIN       6 //��Ħ��nȦ��ͣ����խ��λ��
  //KNEAD_RUN_STOP_AT_MED       7 //��Ħ��nȦ��ͣ�����е�λ��
  //KNEAD_RUN_STOP_AT_MAX       8 //��Ħ��nȦ��ͣ���ڿ��λ��	
  unsigned char nKneadMotorState ;
  //����Ȧ��
  unsigned char nKneadMotorCycles ;
  //������ RT8600
  // unsigned char nKneadMotorPhase ;  
  //�ô���Ҫ�ﵽ��״̬
  //KNOCK_STOP/KNOCK_RUN_WIDTH/KNOCK_RUN/KNOCK_RUN_STOP
  unsigned char nKnockMotorState ;
  unsigned char nKnockMotorRunTime ;//�ô������ʱ��
  unsigned char nKnockMotorStopTime ;//�ô�ͣ�ٵ�ʱ��
  //�������ô���ٶ�	
  //SPEED_0,SPEED_2,SPEED_3,SPEED_4
  unsigned char nKneadKnockSpeed ;
  unsigned char _3D_Position;
  unsigned char _3D_Speed;
  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;
} WALK_KNEAD_KNOCK_MOTOR_STRUCT_MANUAL ;



//===================DIY ������

typedef struct Walk_Knead_Knock_Motor_Struct_DIY_Manual
{
  //�ӹ�������(������ʾ)
  //KNEAD,KNOCK,PRESS,WAVELET,PREPARE
  unsigned char nSubFunction ;
  //���ߵ����λ��ʽ
  //0:WALK_LOCATE_ABSULATE:�ɾ����������
  //1:WALK_LOCATE_SHOULDER:�ɼ粿λ�þ���
  //2:WALK_LOCATE_TOP:���϶��г̿��ؾ���
  //3:WALK_LOCATE_SHOULDER_OR_ABSULATE:�ɼ粿λ�ú;��������еĽ�С�߾���
  //4:WALK_LOCATE_PARK:ͣ���ڵ�ǰλ��
  unsigned char nWalkMotorLocateMethod ;
  //���ߵ����λ�ľ����������PARKʱ��ͣ��ʱ��
  unsigned short nWalkMotorLocateParam ; //���г�
  //����������(�����˽�������)
  //KNEAD_STOP			0 //��Ħ��ͣ�������λ��
  //KNEAD_STOP_AT_MIN		1 //��Ħ��ͣ����խ��λ��
  //KNEAD_STOP_AT_MED		2 //��Ħ��ͣ�����е�λ��
  //KNEAD_STOP_AT_MAX		3 //��Ħ��ͣ���ڿ��λ��
  //KNEAD_RUN			4 //��Ħ��˳ʱ�ӷ�������
  //KNEAD_RUN_STOP		5 //��Ħ��nȦ��ͣ�������λ��
  //KNEAD_RUN_STOP_AT_MIN       6 //��Ħ��nȦ��ͣ����խ��λ��
  //KNEAD_RUN_STOP_AT_MED       7 //��Ħ��nȦ��ͣ�����е�λ��
  //KNEAD_RUN_STOP_AT_MAX       8 //��Ħ��nȦ��ͣ���ڿ��λ��	
  unsigned char nKneadMotorState ;
  //����Ȧ��
  unsigned char nKneadMotorCycles ;
  //������ RT8600
  // unsigned char nKneadMotorPhase ;  
  //�ô���Ҫ�ﵽ��״̬
  //KNOCK_STOP/KNOCK_RUN_WIDTH/KNOCK_RUN/KNOCK_RUN_STOP
  unsigned char nKnockMotorState ;
  unsigned char nKnockMotorRunTime ;//�ô������ʱ��
  unsigned char nKnockMotorStopTime ;//�ô�ͣ�ٵ�ʱ��
  //�������ô���ٶ�	
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
