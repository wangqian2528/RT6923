
#include "AIIinclude.h"


//#define _3D_MANUAL_TEST 1

//------------新总裁养生手法参数增加（main.c文件使用）start---------
bool bDemoStretch;
bool bkneadStopTimeFlag;
//extern bool TimeCountStart;
//int ProgTimeStorage[28];

//unsigned char nKneadDirection;
//bool stopcount;
//extern int ProgTime;
//int ProgStep;
unsigned int bkneadStopTime;
unsigned char nStretchVigor;//3档拉筋标志位
bool handrail_flag = 0;
//int shoulderstep;
//bool WalkStopCounterFlag;
//extern unsigned int WalkStopCounter;
#define NECKMAXPOS      40
#define NECKTOPPOS       30
//unsigned short Main_RealTimeWPos;
bool Walk_CheckPoint;
unsigned int bkneadTime;
unsigned char bkneadTimeFlag,KneadState;
unsigned char upWalkRun,downWalkRun;
//unsigned char checkcicle;
extern bool Walk_StopFlag;
unsigned char bkneadStep;
bool Knead_Min_Ok;
bool Knead_Max_Ok;
extern bool _3D_Min_Ok;
extern bool _3D_Max_Ok;
unsigned char KneadTimesCount,CycleCount;
unsigned char KnockSlow_Flag;
//unsigned char KnockSpeed;
//int piccount;
bool RockStartTimeFlag = false;

uint8_t  nZero_OK;        //零重力调整完成标准
uint8_t Command_Memory_Out;
uint8_t Main_SingleLineTime;
//----------------------end--------------------   -   

unsigned char nKneadTurn,nPreKneadTurn ;
/*****************************扶手相关变量开始*******************************/
#define MAX_OUTBUFFER_COUNT			20
__no_init unsigned char OutArmBuffer[MAX_OUTBUFFER_COUNT] ;
unsigned char outarmcmdcount =0;
unsigned char outarmcmd =0xff;
__no_init unsigned char nOutArmBufferCount;
bool bArmProtect ;
unsigned char nArmProtect;
/*****************************扶手相关变量结束*******************************/

__no_init unsigned char OutVoiceBuffer[MAX_OUTBUFFER_COUNT] ;

/********************************************************/
unsigned int nM_BackAngle;
unsigned int nM_LegAngle;
bool bHaveMan;//新移植
extern unsigned int Flex_In_Fault;//新移植
bool bTapping;
bool bTapping_old;

unsigned short nPartialTop,nPartialBottom,nPartPointMemory ;

/********************************************************/
unsigned char bLanguageFlag;//语言标志位
/******************************************************************/
__no_init BITS GlobalFlags0 ;
#define bKneadWidthMaxPulseLevel0 	GlobalFlags0.bD0
#define bKneadWidthMaxPulseLevel1 	GlobalFlags0.bD1
#define bKneadWidthMaxPulseLevel2 	GlobalFlags0.bD2
#define bKneadWidthMaxPulseLevel3 	GlobalFlags0.bD3
#define bHasKneadWidthMaxPulse	 	GlobalFlags0.bD4
#define bDisplayKneadWidthMax		GlobalFlags0.bD5
#define bDisplayKneadTrackMax		GlobalFlags0.bD6
#define bUpdateLocate 			GlobalFlags0.bD7

__no_init BITS GlobalFlags1 ;
#define bKneadWidthMedPulseLevel0 	GlobalFlags1.bD0
#define bKneadWidthMedPulseLevel1 	GlobalFlags1.bD1
#define bKneadWidthMedPulseLevel2	GlobalFlags1.bD2
#define bKneadWidthMedPulseLevel3 	GlobalFlags1.bD3
#define bHasKneadWidthMedPulse		GlobalFlags1.bD4
#define bDisplayKneadWidthMed		GlobalFlags1.bD5
#define bDisplayKneadTrackMed		GlobalFlags1.bD6
#define bLegPadLinkage 			GlobalFlags1.bD7   //小腿起落联动标志

__no_init BITS GlobalFlags2 ;
#define bKneadWidthMinPulseLevel0 	GlobalFlags2.bD0
#define bKneadWidthMinPulseLevel1 	GlobalFlags2.bD1
#define bKneadWidthMinPulseLevel2 	GlobalFlags2.bD2
#define bKneadWidthMinPulseLevel3 	GlobalFlags2.bD3
#define bHasKneadWidthMinPulse	 	GlobalFlags2.bD4
#define bDisplayKneadWidthMin		GlobalFlags2.bD5
#define bDisplayKneadTrackMin		GlobalFlags2.bD6
#define bWaveMotorFail 			GlobalFlags2.bD7

__no_init BITS GlobalFlags3 ;
#define bShoulderOK	                GlobalFlags3.bD0
#define bBlueToothStatus		GlobalFlags3.bD1
#define bLedFlag 		        GlobalFlags3.bD2
#define bKeyWaistHeat 			GlobalFlags3.bD3
//#define bSlowDisplayFlash		GlobalFlags3.bD4
//#define FlexMotorEnable		GlobalFlags3.bD4
//#define bKeySeatVibrate 		GlobalFlags3.bD5
#define bAngleNoChangeCMD 		GlobalFlags3.bD6
#define bAngleNoChangeProcess	 		GlobalFlags3.bD7

//位变量
__no_init BITS GlobalFlags4 ;
#define bAutoProgramOver 		GlobalFlags4.bD0
#define bTimer10MS 			GlobalFlags4.bD1
#define RockAtuoEnable 		GlobalFlags4.bD2
#define bWorkPower_Switch 		GlobalFlags4.bD3
//#define bKneadMotorPowerFlag 		GlobalFlags4.bD4
#define bTimer5MS 		GlobalFlags4.bD5
#define bBackLegPadSettle 		GlobalFlags4.bD6
#define bDisplayFlash 			GlobalFlags4.bD7

__no_init BITS GlobalFlags5 ;
#define bBackAutoModeInit 			GlobalFlags5.bD0
#define bBackManualModeInit 		        GlobalFlags5.bD1
#define bWalkMotorInProcess 		        GlobalFlags5.bD2 //行走电机程序执行标志
#define bKneadMotorInProcess 		        GlobalFlags5.bD3 //揉捏电机程序执行标志，例如顺时针揉捏3圈后停止
#define bKnockMotorInProcess 		        GlobalFlags5.bD4 //敲击电机程序执行标志
#define bGetNextActionStep 			GlobalFlags5.bD5
#define bKeyWalkUp 				GlobalFlags5.bD6
#define bKeyWalkDown 				GlobalFlags5.bD7

__no_init BITS GlobalFlags6 ;
#define b3D_MotorInProcess 			GlobalFlags6.bD0
#define bMassagePositionUpdate 			GlobalFlags6.bD1
#define bLegRollerEnable			GlobalFlags6.bD2
#define bSendBuzzerMode 			GlobalFlags6.bD3

#define bMain_Start_Manual_WalkNoNeed 			GlobalFlags6.bD4
#define bMasterSendPacket 			GlobalFlags6.bD5 
//#define bReconfigFlag 			GlobalFlags6.bD6
#define bKneadWidthChange			GlobalFlags6.bD7


__no_init BITS GlobalFlags7 ;
#define bKeyBackPadUp 				GlobalFlags7.bD0
#define bKeyBackPadDown 			GlobalFlags7.bD1
#define bOzonEnable 	                        GlobalFlags7.bD2
#define FlexAtuoEnable 	      			GlobalFlags7.bD3

#define bMassagePositionUpdateMemory            GlobalFlags7.bD4
#define bKeyArmPadIn             	        GlobalFlags7.bD5//新增扶手
#define bKeyArmPadOut 			        GlobalFlags7.bD6//新增扶手
//#define bGetAirBagNextStep 			GlobalFlags7.bD5
#define bManualReset                            GlobalFlags7.bD7
//#define bCurActionStepChange		        GlobalFlags7.bD6
//#define bWalkLocateChange			GlobalFlags7.bD7

__no_init BITS GlobalFlags8 ;
#define bKeyLegPadUp 				GlobalFlags8.bD0
#define bKeyLegPadDown 				GlobalFlags8.bD1  //小腿起落电动缸落标志，在按键处理里面设置
#define bKeyFlexOut 		                GlobalFlags8.bD2
#define bKeyFlexIn 	                        GlobalFlags8.bD3
//#define bZeroPadMotorPowerFlag		GlobalFlags8.bD4
//#define bWalkMotorLocateChange 		GlobalFlags8.bD5
//#define bReachWalkUpLimitFlag		        GlobalFlags8.bD6
//#define bReachWalkDownLimitFlag		GlobalFlags8.bD7

__no_init BITS GlobalFlags9 ;
//#define bProgramMemorySet			GlobalFlags9.bD0
//#define bBodyDetectSuccess			GlobalFlags9.bD1
//#define bKeyZeroUp			        GlobalFlags9.bD2
//#define bGetArmAirBagNextStep 		GlobalFlags9.bD3
//#define bZeroTransition			GlobalFlags9.bD4
//#define bZeroRestFlag				GlobalFlags9.bD5
//#define bZeroRunFlag				GlobalFlags9.bD6
//#define bGetBodyUpAirBagNextStep 	        GlobalFlags9.bD7

__no_init BITS GlobalFlags10 ;
//#define bZeroRunUpFlag			GlobalFlags10.bD0
//#define bZeroRunDownFlag			GlobalFlags10.bD1
//#define bMP3_AD_Enable			GlobalFlags10.bD2
//#define bKeyZeroDown    			GlobalFlags10.bD3
//#define bBackMotorUpFlag			GlobalFlags10.bD4
//#define bLegkMotorUpFlag			GlobalFlags10.bD5
#define bBlueToothMasterSendPacket		GlobalFlags10.bD6
#define bBlueToothSendBuzzerMode		GlobalFlags10.bD7
//MP3 变量
unsigned char CMDPRO ;//20161226 ZERO 
//--------------------------------------------------------------------------------------
//bool vReadSholuder2;
//uint8_t bRockEnable;
__no_init unsigned char nRockModeEnterEnable;
__no_init unsigned char WorkStep; //摇摆
__no_init unsigned char nChairRunState_Pre;
//-------------------------------------------------------------
//__no_init bool bLegRollerEnable;

unsigned char bWalkSlowFlag = 0;	
bool bWalkPWMFlag =FALSE;
//  static char count_t=0;
//-------------------------------------------------------

//unsigned int w_BackPosition,w_LegPosition;//全局变量

unsigned int w_BackPosition_2,w_LegPosition_2;
//----------------------------------------------
__no_init unsigned char nHotTime;//3档加热
__no_init unsigned char nHeatStreng;
__no_init unsigned short nHeatADCTemp;
__no_init unsigned int nHeatResister;
signed char by_cur_adc_temperatue;
#define nHeatStreng_tempetatue_1class      45
#define nHeatStreng_tempetatue_2class      51
#define nHeatStreng_tempetatue_3class      57
//-------------------------------------------------
/******************************************************************/
#define MAX_INBUFFER_COUNT			10
#define MAX_OUTBUFFER_COUNT			20
/******************************************************************/
#define MAX_WAIT_COMMAND_TIME		120 //120*0.5s=60s=1min

__no_init unsigned char nSettleMode;

__no_init unsigned char CalfSpeed;//小腿滚轮速度

__no_init  bool stretchMode;

/******************************************************************/
//__no_init StretchStruct st_Stretch;
StretchStruct st_Stretch,st_RestSleep,st_GrowthStretch;
/******************************************************************/
__no_init unsigned char nBuzzerMode;
/******************************************************************/
__no_init unsigned char nBackMainRunMode,nBackSubRunMode ;
__no_init unsigned char nCurSubFunction ;        
__no_init unsigned char nCurKneadKnockSpeed ; 
/******************************************************************/
__no_init unsigned int nCurActionStep,nCurActionStepreturn;
__no_init unsigned int nMaxActionStep ;
__no_init unsigned char nStartActionStep ;
/******************************************************************/
__no_init unsigned char nTargetMassagePosition;
__no_init unsigned short nShoulderPosition,nShoulderPositionTop,nShoulderPositionBottom;
__no_init unsigned int ShoulderSteps;
__no_init int BodyDetectStep;   
//BODY_DETECT_PREPARE:  未开始检测 
//BODY_DETECT_SHOULDER: 正在检测肩膀位置
//BODY_DETECT_3D:       正在检测3D力度 
//BODY_DETECT_OVER:     检测完成 

/******************************************************************/
//控制手控器需要知道的相关信息的变量
__no_init unsigned char nKeySeatVibrateStrength ;//振动力度，对应outbuf[3]3,4,5位
__no_init unsigned char nKeyBackLocate;//机芯按摩部位，对应outbuf[4]5,6位
__no_init unsigned int w_PresetTime;  //程序预设时间，对应outbuf[12]0,1位
__no_init unsigned char nKeyAirBagLocate ;    //气囊按摩区域,对应outbuf[12]2.3.4位
/******************************************************************/
       
unsigned short nLegAngle,nLegGround;
unsigned char nFlexStatus;
unsigned char nLegReady;

//unsigned int topPositionRefreshedFlag;
//int shoulderPos[3];

//与通信相关的变量
//两种类型的数据包，命令包和状态包，命令包需要应答，状态包无需应答
__no_init unsigned char OutBuffer[MAX_OUTBUFFER_COUNT] ;
__no_init unsigned char OutBufferBlueTooth[MAX_OUTBUFFER_COUNT] ;
__no_init unsigned char InBuffer[MAX_INBUFFER_COUNT] ;
__no_init unsigned char nInBufferCount ;
__no_init unsigned char nOutBufferCount ;
__no_init unsigned char nOutBufferBlueToothCount;
//__no_init unsigned char nSendCount ;
//__no_init unsigned char nCommandID ;
//__no_init unsigned char nSendPacketID ;

__no_init unsigned char OutLegBuffer[MAX_OUTBUFFER_COUNT];
__no_init unsigned char OutLegBuffer_3D[MAX_OUTBUFFER_COUNT];

__no_init unsigned char InLegBuffer[MAX_INBUFFER_COUNT];

bool bMasterSendLegPacket;
bool send_time_flag;
//__no_init unsigned char _3D_Mode_Step;
//unsigned int sysTimer;
//bool bLegKneadEnableonly;
bool bRollerEnable;//,bLegKneadEnable
__no_init unsigned char nRollerPWM;
bool bAUTO1AirEnable;
bool bFlexEnable;

unsigned char nFlexMode;
//#define FLEX_AUTO   1
//#define FLEX_MANUAL 0

unsigned char nFlexDirection;
#define FLEX_IN    0
#define FLEX_OUT   1
//unsigned char nLegAirBagMode;
//#define LEG_AIRBAG_MODE1  0x14
//#define LEG_AIRBAG_MODE2  0x15
//#define LEG_AIRBAG_MODE3  0x16

//unsigned char nLegAirBagStrength;
//#define LEG_AIRBAG_OFF     0x17
//#define LEG_AIRBAG_WEAK    0x18
//#define LEG_AIRBAG_MIDDLE  0x19
//#define LEG_AIRBAG_STRONG  0x1a

//bool bLegModulePower;
extern bool bLegAirBagOn;
//bool bLegHeat;
/******************************************************************/
__no_init unsigned char nKeyKneadWidth ;
__no_init unsigned char nKeyKneadKnockSpeed ;
__no_init unsigned char nMaunalSubMode;
/******************************************************************/
unsigned int password;
/******************************************************************/
unsigned int nPowerMotorHighTime;
unsigned int nPowerMotorLowTime;
unsigned int nPowerValveHighTime;
unsigned int nPowerValveLowTime;
unsigned int nPowerVCCHighTime;
unsigned int nPowerVCCLowTime;
unsigned char nVoicekey;
// nAxisStrength:总强度  
//unsigned char  nAxisStrength/*,nAxisStrengthBase,nAxisAuto,nAxisMode*/; 
/*
  nKeyAxisStrength 用户设定值  数值范围0-4
  nSetAxisStrength 程序设定值  数值范围0-4
  nFinalAxisStrength 实际值    数值范围0-4
  nFinalAxisStrength 计算方式：
*/
unsigned char  nKeyAxisStrength,nSetAxisStrength,nFinalAxisStrength,nAxisUpdateCounter; 
unsigned char  nDisplayAxisStrength; //添加肩部显示
//unsigned int nWidthOverTime;
//unsigned int nPowerOverTime;
//unsigned int nWalkOverTime;
//unsigned int nBackOverTime;
//unsigned int nLegOverTime;
//unsigned int nZeroOverTime;
//unsigned int nWaveOverTime;
//unsigned int nFlexOverTime;

/******************************************************************/
__no_init unsigned short nFinalWalkMotorLocate ;
/******************************************************************/
__no_init unsigned char nCurActionStepCounter;       //当前步骤时间计数器(适用于所有行走，揉捏，敲打电机)
__no_init unsigned char nCurKnockRunStopCounter;   
__no_init unsigned char nCur3D_MotorStopCounter;
__no_init unsigned char nCurShoulderAdjustCounter ;
__no_init unsigned char n3DMotorRunCounter;
/******************************************************************/
unsigned char nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
__no_init unsigned char nCurKneadMotorCycles ;

unsigned char nCurKneadMotorState,nPrevKneadMotorState,nFinalKneadMotorState ;
/******************************************************************/
__no_init unsigned char nWalkMotorControlParam1;
__no_init unsigned short nWalkMotorControlParam2 ;
__no_init unsigned char nKneadMotorControlParam1,nKneadMotorControlParam2 ;
__no_init unsigned char n3D_MotorControlState,n3D_MotorControlPosition,n3D_MotorControlSpeed,n3D_MotorControlStopTime;
__no_init unsigned char nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3 ;

unsigned char engineeringTime_10msFlag = 0; //工程模式使用

//unsigned short adcAudio_L_Base,adcAudio_R_Base;

/******************************************************************/
__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoDirector;
//__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO* pAutoDirector = &AutoDirector ;
__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT_MANUAL ManualDirector[4] ;

//--------------------------------------------------------------------------------------定义DIY 变量
__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT__DIY_MANUAL    DIY_ManualDirector[4] ;
unsigned char DIYProgramContent;//DIY键值

bool  bGetDIY_keyflag=0;

//-------------------------------------------------------------------------------------
unsigned int  GrowthStepMaxA;//= sizeof(AirBagModeLegFoot_GrowthA) / sizeof(struct AirBagStruct);  
unsigned int  GrowthStepMaxB;// = sizeof(AirBagModeLegFoot_GrowthB) / sizeof(struct AirBagStruct);
__no_init st_AirBag  st_AirBagModeLegFootSeat_Growth;
//---------------------------------------------
//2015/4/7 
// 新增3个自动程序
__no_init unsigned long n_Examinee_Steps;
__no_init unsigned long n_HipUp_Steps;
__no_init unsigned long n_Golfer_Steps;
__no_init unsigned long massage_step_tm_flag;
__no_init unsigned long massage_step_tm;  //by_Time30s;
__no_init unsigned long n_Examinee_Pointer;
__no_init unsigned long n_HipUp_Pointer;
__no_init unsigned long n_Golfer_Pointer;

__no_init unsigned long by_moni_cmd_tm;

__no_init unsigned long by_moni_cmd_tm_en;


__no_init unsigned long n_Wrick_Steps;
__no_init unsigned long n_Wrick_Pointer;

static uint8_t Zero_mark;
static bool bZero_ShowFlag;    
    
uint16_t CurTime;    

void Examinee_Mode_Massage_Pointer_Control_Start(void);
void HipUp_Mode_Massage_Pointer_Control_Start(void);
void Golf_Mode_Massage_Pointer_Control_Start(void);
void Examinee_Mode_Massage_Pointer_Control_Proc(void);
void HipUp_Mode_Massage_Pointer_Control_Proc(void);
void Golf_Mode_Massage_Pointer_Control_Proc(void);



void  open_auto_back_down2s(void);
void  close_auto_back_down(void);

uint8_t Zero_Grade(uint16_t wBackPosition);

void  Set_Moni_cmd_tm(unsigned long c);
// 时基0.1s
void  Set_Moni_cmd_tm(unsigned long c)
{

	by_moni_cmd_tm = c;
	return;
}


/////////////////////////////////////////////////////////////////////////

__no_init st_AirBag st_AirBagArmSholderBackWaist, st_AirBagModeLegFootSeat, st_AirBagLegFoot, st_AirBagArmSholder, st_AirBagBackWaist, st_AirBagSeat, st_AirBagArm;
__no_init st_AirBag st_AirBagLegFoot_Seat,st_AirBagLegFoot_ArmSholder,st_AirBagArmSholder_Seat,st_AirBagLegFoot_ArmSholder_Seat;
/******************************************************************/
#define AUTO_FUNCTION_0_STEPS	sizeof(AutoFunction0)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_1_STEPS	sizeof(AutoFunction1)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_2_STEPS	sizeof(AutoFunction2)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_3_STEPS	sizeof(AutoFunction3)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_4_STEPS	sizeof(AutoFunction4)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_5_STEPS	sizeof(AutoFunction5)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)

#define AUTO_FUNCTION_6_STEPS	sizeof(AutoFunction6)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_7_STEPS	sizeof(AutoFunction6)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_8_STEPS	sizeof(AutoFunction7)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_9_STEPS	sizeof(AutoFunction8)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)//CARE   
#define AUTO_FUNCTION_10_STEPS	sizeof(AutoFunction10)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)//GROWHT//

#define AUTO_FUNCTION_11_STEPS	sizeof(AutoFunctionFull)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_12_STEPS	sizeof(AutoFunctionShoulder)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_13_STEPS	sizeof(AutoFunctionWaist)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
//#define AUTO_FUNCTION_14_STEPS	sizeof(AutoFunctionLeg)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_14_STEPS	sizeof(DemoFunction)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)

#define AUTO_FUNCTION_15_STEPS  sizeof(_3DFunction0)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_16_STEPS  sizeof(_3DFunction1)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_17_STEPS  sizeof(_3DFunction2)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)

//#define AUTO_FUNCTION_10_MED_STEPS	sizeof(AutoFunction2_1)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
//#define AUTO_FUNCTION_11_SLOW_STEPS	sizeof(AutoFunction2_2)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)

//自动程序步骤总数
//const unsigned int BACK_AUTO_STEPS[] = 
unsigned int BACK_AUTO_STEPS[] =
{
	AUTO_FUNCTION_0_STEPS,
	AUTO_FUNCTION_1_STEPS,
	AUTO_FUNCTION_2_STEPS,
	AUTO_FUNCTION_3_STEPS,
	AUTO_FUNCTION_4_STEPS,
	AUTO_FUNCTION_5_STEPS,
	
        AUTO_FUNCTION_6_STEPS,
        AUTO_FUNCTION_7_STEPS,
        AUTO_FUNCTION_8_STEPS,
        AUTO_FUNCTION_9_STEPS,
	AUTO_FUNCTION_10_STEPS,
	
	
	AUTO_FUNCTION_11_STEPS,
        AUTO_FUNCTION_12_STEPS,
        AUTO_FUNCTION_13_STEPS,
	AUTO_FUNCTION_14_STEPS,
        
        AUTO_FUNCTION_15_STEPS,// 3D1
	AUTO_FUNCTION_16_STEPS,//3D2
        AUTO_FUNCTION_17_STEPS//3D3
	
      //  AUTO_FUNCTION_10_MED_STEPS,
      //  AUTO_FUNCTION_11_SLOW_STEPS,  
} ;
//自动程序循环运行开始的步骤
const unsigned char BACK_AUTO_START_STEP[] =
{
	0,
	0,
	0,
	0,
	0,
	0,
        0,
        0,
        0,
        0,
        0,
        0,
	0,
	0,
	0,
        0,
        0,
        0,
} ;
/******************************************************************/
__no_init unsigned char nStretchStep;
/******************************************************************/
__no_init unsigned short nPartialTop,nPartialBottom ;
/******************************************************************/
bool bAxisUpdate;
/******************************************************************/
__no_init unsigned char n3Dpointturn;
/******************************************************************/
bool bAxisUpdate_Manual_Waitting_Timef;
bool bAxisUpdate_Program_Waitting_Timef;

unsigned char nAxisUpdate_Manual_Waitting_Time_cnt;
unsigned char nAxisUpdate_Program_Waitting_Time_cnt;
/******************************************************************/
bool bRestSleepStatus;
bool bTimeoverRestSleepStatus;
__no_init unsigned char wgh;

void Main_Start_Manual(void);
////////////////////////////////////
void BodyDataRefresh(void);
void Main_Initial_Data(void);

void Main_Initial_IO(void)
{
    __disable_irq();
    System_Initial_IO();
    // __enable_irq(); //test
    // while(1);
    Power_Initial_IO();
    IndicateLED_Initial_IO();
    KneadMotor_Initial_IO();
    HAND_Initial_IO();
    Valve_Initial_IO();
    Axis_Initial_IO();
    SlideMotor_Initial_IO();
    LegMotor_Initial_IO();
    BackMotor_Initial_IO();
    WalkMotor_Initial_IO();
    Input_Initial_IO();
    KnockMotor_Initial_IO();
    MP3Control1_Initial_IO();
    WaistHeat_Initial_IO();
    LED_RGB_Initial_IO();
    UartLeg_Initial_IO();
    BlueToothUart_Initial_IO();
    DMA_Ctrl_Init();
    ADC_Data_Init();
    Roller_Initial_IO();
    FlexMotor_Initial_IO();
    //  LEUART0_Initial_IO();// 接收3D检测板485信号 ,去掉3D检测借口
    //  DMA_Ctrl_Init();
    SignalBoard_Initial_IO();//读取电机行程开关
    __enable_irq();
    
}

#define		ADSTRONG_ON  8
#define		ADSTRONG1  10
#define		ADSTRONG2  30
#define		ADSTRONG3  50
#define		ADSTRONG4  70
#define		ADSTRONG5  100
#define		ADSTRONG6  150
unsigned int nAvrADResult0 ;
unsigned int nMusicKnockPWM ;//用于音乐互动
void MusicSampling(void)
{
    unsigned int adcAudio_L,adcAudio_R;
    
    if(ADC_Get_Updata() < 0)
    {
     return; 
    }
    
    adcAudio_L = *(pADC + ADC_AUDIO_L);
    adcAudio_R = *(pADC + ADC_AUDIO_R);
    
    if(adcAudio_L >= adcAudio_R)
    {
        nAvrADResult0 = adcAudio_L - adcAudio_R  ;
    }
    else
    {
        nAvrADResult0 = adcAudio_R - adcAudio_L  ;
    } 
    
    if(nAvrADResult0 > ADSTRONG1)
    {
      VoiceUart_SetMusicStatus(1);  //有音乐
    }
    else
    {
      VoiceUart_SetMusicStatus(0); //无音乐
    } 
}
/*******************************************************************************/
void BackManualModeNoActionMemory(void)
{
    WaistHeat_Off();
    WalkMotor_Control(STATE_WALK_IDLE, 0);
    KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
    LegMotor_Control(STATE_LEG_IDLE);
    BackMotor_Control(STATE_BACK_IDLE);
    SlideMotorControl(STATE_SLIDE_IDLE);
    FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_SetDirection(FLEX_MOTOR_STOP);
    KnockMotor_Set_Pwm_Data(0);
    LED_RGB_Set_All(0);
    AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8);
    Valve_CloseAll();
    //LegKnead_SetPower(LEG_KNEAD_OFF);  
    /////////////////////////////////////////////////////////////////////////////////////
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION;
    nBackMainRunMode == BACK_MAIN_MODE_IDLE;
    
    nKeyKneadKnockSpeed = 0;//ReadEEByte(MEMORYA_ADDR_BASE + KNEADKNOCK_SPEED_ADDRESS);
    /////////////////////////////////////////
    
    nKeyAirBagLocate = AIRBAG_LOCATE_NONE;//ReadEEByte(MEMORYA_ADDR_BASE + AIRLOCATE_ADDRESS);//AIRBAG_LOCATE_AUTO 
    nKeyAxisStrength = 0;//ReadEEByte(MEMORYA_ADDR_BASE + AXIS_STRENGTH_ADDRESS);
    //bAxisUpdate = TRUE;
    //nAxisUpdateCounter = 0;
    
    //========================HOT===========================
    //if(  ReadEEByte(MEMORYA_ADDR_BASE + HOT_ADDRESS)==0x01 )
    //{
    bKeyWaistHeat = false ;
    
    //=====ROLLER========  
    bRollerEnable = false;//(  ReadEEByte(MEMORYA_ADDR_BASE + ROLLER_ENABLE_ADDRESS)==0x01 )? TRUE:FALSE;
    nRollerPWM = 0;//ReadEEByte(MEMORYA_ADDR_BASE + ROLLER_PWM_ADDRESS);
    Valve_SetRollerPWM(nRollerPWM);
    
    //=====LEGKNEAD========  
    //bLegKneadEnable = 0;//(  ReadEEByte(MEMORYA_ADDR_BASE + LEGKNEAD_ENABLE_ADDRESS)==0x01 )? TRUE:FALSE;
    //LegKneadSpeed = 0;//ReadEEByte(MEMORYA_ADDR_BASE + LEGKNEAD_PWM_ADDRESS);
    //if(  (bLegKneadEnable == true)&&(nKeyAirBagLocate == AIRBAG_LOCATE_LEG_FOOT)    )
    //{
    //      bLegKnead_Air_Link  = false;
    //bLegKneadEnableonly = FALSE;
    //}
    
}
/*******************************************************************************/
void Manual_Memory_Air_Postion(unsigned int nAddress)
{
  BYTE nAirBagStrength;
              switch(nKeyAirBagLocate)
              {
              case AIRBAG_LOCATE_NONE:
                
                break;
              case AIRBAG_LOCATE_LEG_FOOT:
                //bLegKneadEnableonly = FALSE;
                st_AirBagLegFoot.init = TRUE ;
                nAirBagStrength = ReadEEByte(nAddress + AIR_STRENGTH_ADDRESS);
                Valve_SetAirBagStrength(nAirBagStrength);
                nChairRunState = CHAIR_STATE_RUN ;
                break;                 
              case AIRBAG_LOCATE_BACK_WAIST:
                st_AirBagBackWaist.init = TRUE ;
                nAirBagStrength = ReadEEByte(nAddress + AIR_STRENGTH_ADDRESS);
                Valve_SetAirBagStrength(nAirBagStrength);
                nChairRunState = CHAIR_STATE_RUN ;
                break;
              case AIRBAG_LOCATE_ARM_SHOLDER:
                st_AirBagArmSholder.init = TRUE ;
                nAirBagStrength = ReadEEByte(nAddress + AIR_STRENGTH_ADDRESS);
                Valve_SetAirBagStrength(nAirBagStrength);
                nChairRunState = CHAIR_STATE_RUN ;
                break;               
              case AIRBAG_LOCATE_SEAT:
                st_AirBagSeat.init = TRUE ;
                nAirBagStrength = ReadEEByte(nAddress + AIR_STRENGTH_ADDRESS);
                Valve_SetAirBagStrength(nAirBagStrength);
                nChairRunState = CHAIR_STATE_RUN ;
                break;
              case AIRBAG_LOCATE_AUTO:
                nAirBagStrength = ReadEEByte(nAddress + AIR_STRENGTH_ADDRESS);
                Valve_SetAirBagStrength(nAirBagStrength);
                
                st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
                st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
                st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
                st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
                st_AirBagModeLegFootSeat.init = TRUE;
                st_AirBagArmSholderBackWaist.init = TRUE;
                bRollerEnable = TRUE;    
                nChairRunState = CHAIR_STATE_RUN ;
                break;                 
                //case AIRBAG_LOCATE_ARM:
                
                // break;
              default:
                
                break;           
                
              }
}
/*******************************************************************************/
void Manual_Memory_Walk_Postion(unsigned int nAddress)
{
 //nMaxActionStep = 4 ;
 // bMemory_walk = true;
  if(nKeyBackLocate == LOCATE_FULL_BACK)
  {
    ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
    ManualDirector[0].nWalkMotorLocateParam = 0 ;
    ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
    ManualDirector[1].nWalkMotorLocateParam = 0 ;
    ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
    ManualDirector[2].nWalkMotorLocateParam = 0 ;
    ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
    ManualDirector[3].nWalkMotorLocateParam = 0 ;
  }
  if(nKeyBackLocate == LOCATE_PARTIAL)//
  {nCurActionStep = 0;//first  run  to zero
    nPartialTop = (  ReadEEByte(nAddress + WALK_POSITION_TOP_H_ADDRESS)<<8  )+ReadEEByte(nAddress + WALK_POSITION_TOP_L_ADDRESS);
    nPartialBottom = (  ReadEEByte(nAddress + WALK_POSITION_BOTTOM_H_ADDRESS)<<8  )+ReadEEByte(nAddress + WALK_POSITION_BOTTOM_L_ADDRESS);
    /*if(bNoReach == true)
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ; 
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = 0 ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = 0 ; 
    }
    else
    {*/
    
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
    
      //ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      //ManualDirector[0].nWalkMotorLocateParam = nPartialBottom ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = nPartialTop ; 
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = nPartialBottom ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = nPartialTop ;  
   // }
      nMaxActionStep = 2;

  }
  if(nKeyBackLocate == LOCATE_POINT)
  {
    nPartialTop = (  ReadEEByte(nAddress + WALK_POSITION_TOP_H_ADDRESS)<<8  )+ReadEEByte(nAddress + WALK_POSITION_TOP_L_ADDRESS);
    //nPartialBottom = (  ReadEEByte(MEMORYA_ADDR_BASE + WALK_POSITION_BOTTOM_H_ADDRESS)<<8  )+ReadEEByte(MEMORYA_ADDR_BASE + WALK_POSITION_BOTTOM_L_ADDRESS);
    nCurActionStep = 0;//first  run  to zero
   /* if(bNoReach == true)
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ; 
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = 0 ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = 0 ; 
    }
    else
    { */  
    ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE;//WALK_LOCATE_TOP ;
    ManualDirector[0].nWalkMotorLocateParam = 0 ;
    ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
    ManualDirector[1].nWalkMotorLocateParam = nPartialTop ;

      
   // ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
   // ManualDirector[0].nWalkMotorLocateParam = MAX_PARK_TIME ;
  // ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
   // ManualDirector[1].nWalkMotorLocateParam = MAX_PARK_TIME ;  
      
    ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[2].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[3].nWalkMotorLocateParam = MAX_PARK_TIME ;
    nMaxActionStep = 5;
  //}
    
    
  }
  
  
            bWalkMotorInProcess = TRUE ;
            bUpdateLocate = TRUE ;
            nWalkMotorControlParam1 = ManualDirector[0].nWalkMotorLocateMethod ;
            nWalkMotorControlParam2 = ManualDirector[0].nWalkMotorLocateParam ;
            
           
  ///////////nPartPointMemory = Input_GetWalkMotorPosition();         
 
}
/*******************************************************************************/
void Memory_In(uint32_t Address)
{
    //uint8_t Save_data[32];
    unsigned int pw_Memory[10];
    PBYTE pMemory = (PBYTE)pw_Memory;
    if(
       (nBackMainRunMode == BACK_MAIN_MODE_AUTO)||
           (nBackMainRunMode == BACK_MAIN_MODE_3D)||
               (nBackMainRunMode == BACK_MAIN_MODE_DEMO)||
                   (nBackMainRunMode == BACK_MAIN_MODE_SETTLE)
                       )
    {
        nBuzzerMode = BUZZER_MODE_TWOTIME ;
        bSendBuzzerMode = TRUE ;
        return ;
    }
    
    memset(pw_Memory,0,sizeof(pw_Memory));
    
    // if((SOFT_MAIN_VER != ReadEEByte(USER_DATA_BASE + SOFT_MAIN_VER_ADDRESS)) || (SOFT_SECONDARY_VER != ReadEEByte(USER_DATA_BASE + SOFT_SECONDARY_VER_ADDRESS))) 
    // {  //首次使用需要初始化数据
    *(pMemory + BACK_MAIN_RUN_MODE_ADDRESS)      = nBackMainRunMode;//1;
    *(pMemory + MANSUB_MODE_ADDRESS)      = nMaunalSubMode;//1;
    *(pMemory + KNEAD_WIDTH_ADDRESS)      = nKeyKneadWidth;//3;   max:3  med:2
    *(pMemory + KNEADKNOCK_SPEED_ADDRESS) = nKeyKneadKnockSpeed;//2;          
    *(pMemory + AIRLOCATE_ADDRESS)        = nKeyAirBagLocate;//1;
    //
    *(pMemory + AIR_STRENGTH_ADDRESS)     = Valve_GetAirBagStrength();//nAirBagStrength;//2;          
    *(pMemory + AXIS_STRENGTH_ADDRESS)    = nKeyAxisStrength;//3;
    //================
    *(pMemory + HOT_ADDRESS)    =  (bKeyWaistHeat == TRUE)? 0X01:0;//nKeyAxisStrength;
    //=====ROLLER========  
    *(pMemory + ROLLER_ENABLE_ADDRESS) = (bRollerEnable == TRUE)? 1:0;
    *(pMemory + ROLLER_PWM_ADDRESS) = Valve_GetRollerLevel();//nRollerPWM;
    //=====LEGKNEAD========  
    //  *(pMemory + LEGKNEAD_ENABLE_ADDRESS) = (bLegKneadEnable == TRUE)? 1:0;
    //  *(pMemory + LEGKNEAD_PWM_ADDRESS) = LegKnead_GetSpeed();// LegKneadSpeed
    //===================
    nM_BackAngle = BackMotor_Get_Position();
    nM_LegAngle = LegMotor_Get_Position(); 
    
    *(pMemory + BACK_ANGLE_H_ADDRESS)= (BYTE)(nM_BackAngle>>8);
    *(pMemory + BACK_ANGLE_L_ADDRESS)= (BYTE)nM_BackAngle;
    *(pMemory + LEG_ANGLE_H_ADDRESS)= (BYTE)(nM_LegAngle>>8);
    *(pMemory + LEG_ANGLE_L_ADDRESS)= (BYTE)nM_LegAngle;
    //===================
    //LOCATE_FULL_BACK: 1
    //LOCATE_PARTIAL:   7
    //LOCATE_POINT:     0
    
    *(pMemory + WALK_MODE_ADDRESS)= nKeyBackLocate;//
    
    
    if(nKeyBackLocate == LOCATE_PARTIAL)
    {
        *(pMemory + WALK_POSITION_TOP_H_ADDRESS)= (BYTE)(nPartialTop>>8);
        *(pMemory + WALK_POSITION_TOP_L_ADDRESS)= (BYTE)(nPartialTop);
        *(pMemory + WALK_POSITION_BOTTOM_H_ADDRESS)= (BYTE)(nPartialBottom>>8);
        *(pMemory + WALK_POSITION_BOTTOM_L_ADDRESS)= (BYTE)(nPartialBottom);  
        
    }
    nPartPointMemory = Input_GetWalkMotorPosition();//wgh 20160801
    if(nKeyBackLocate == LOCATE_POINT)
    {
        *(pMemory + WALK_POSITION_TOP_H_ADDRESS)= (BYTE)(nPartPointMemory>>8);
        *(pMemory + WALK_POSITION_TOP_L_ADDRESS)= (BYTE)(nPartPointMemory);
        *(pMemory + WALK_POSITION_BOTTOM_H_ADDRESS)= (BYTE)(nPartPointMemory>>8);
        *(pMemory + WALK_POSITION_BOTTOM_L_ADDRESS)= (BYTE)(nPartPointMemory);   
    }
    
    //====================
    MEMORYA_Write_Memory(pw_Memory,32,Address);
    nBuzzerMode = BUZZER_MODE_ONETIME ;
    bSendBuzzerMode = TRUE ;
}
/*******************************************************************************/
void Memory_Out(uint32_t Address)
{
    ShoulderSteps = BODY_DETECT_PREPARE;
    bMain_Start_Manual_WalkNoNeed = true;
    nCurSubFunction = BACK_SUB_MODE_NO_ACTION;
    BackManualModeNoActionMemory();
    
    bBackManualModeInit = true;   // 手动初始化
    
    //  if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL) bMaunalSubMode_MemoryPro = true;
    //  else                                          bMaunalSubMode_MemoryPro = false;
    
    nBackMainRunMode = ReadEEByte(Address + BACK_MAIN_RUN_MODE_ADDRESS);//BACK_MAIN_MODE_MANUAL;
    //  nMaunalSubMode_MemoryPro = nMaunalSubMode;
    
    nMaunalSubMode = ReadEEByte(Address + MANSUB_MODE_ADDRESS);//nMaunalSubMode_KNEAD;
    if( nMaunalSubMode > nMaunalSubMode_MUSIC   ) nMaunalSubMode = nMaunalSubMode_KNEAD;
    nKeyKneadWidth = ReadEEByte(Address + KNEAD_WIDTH_ADDRESS);
    if(nKeyKneadWidth > 3)nKeyKneadWidth = KNEAD_WIDTH_MED ;
    nKeyKneadKnockSpeed = ReadEEByte(Address + KNEADKNOCK_SPEED_ADDRESS);
    //  if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)Main_Start_Manual();
    
    nKeyAirBagLocate = ReadEEByte(Address + AIRLOCATE_ADDRESS);//AIRBAG_LOCATE_AUTO ;
    Manual_Memory_Air_Postion(Address);
    nKeyAxisStrength = ReadEEByte(Address + AXIS_STRENGTH_ADDRESS);
    bAxisUpdate = TRUE;
    nAxisUpdateCounter = 0;
    //========================HOT===========================
    if(  ReadEEByte(Address + HOT_ADDRESS)==0x01 )
    {
        bKeyWaistHeat = TRUE ;
        WaistHeat_On();
        nChairRunState = CHAIR_STATE_RUN ;
    }
    else
    {
        bKeyWaistHeat = FALSE ;
    }
    //=====ROLLER========  
    bRollerEnable = (  ReadEEByte(Address + ROLLER_ENABLE_ADDRESS)==0x01 )? TRUE:FALSE;
    nRollerPWM = ReadEEByte(Address + ROLLER_PWM_ADDRESS);
    Valve_SetRollerPWM(nRollerPWM);
    
    //=====LEGKNEAD========  
    //bLegKneadEnable = (  ReadEEByte(Address + LEGKNEAD_ENABLE_ADDRESS)==0x01 )? TRUE:FALSE;
    //LegKneadSpeed = ReadEEByte(Address + LEGKNEAD_PWM_ADDRESS);
//    if(  (bLegKneadEnable == true)&&(nKeyAirBagLocate == AIRBAG_LOCATE_LEG_FOOT)    )
//    {
//        //    bLegKnead_Air_Link  = true;
//        bLegKneadEnableonly = FALSE;
//    }
    
    //====================back  leg ======================
    nM_BackAngle = (  ReadEEByte(Address + BACK_ANGLE_H_ADDRESS)<<8  )+ReadEEByte(Address + BACK_ANGLE_L_ADDRESS);
    nM_LegAngle = (  ReadEEByte(Address + LEG_ANGLE_H_ADDRESS)<<8  )+ReadEEByte(Address + LEG_ANGLE_L_ADDRESS);
    
    nTargetMassagePosition = MASSAGE_MEMORY_POSITION;
    bMassagePositionUpdate = TRUE;
    bMassagePositionUpdateMemory = TRUE;
    
    //++++++++++walk++++++++++++++++++++++++++++++++++++++++++
    
    nKeyBackLocate = ReadEEByte(Address + WALK_MODE_ADDRESS);
    Manual_Memory_Walk_Postion(Address);
    //===================total===========================
    //nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
    nChairRunState = CHAIR_STATE_RUN ;
    
    if(Data_Get_Time() == 0)
    {
        Data_Set_Start(1, w_PresetTime);
    }
    //MEMORYA_Write_Memory( 0, 1);
    nBuzzerMode = BUZZER_MODE_ONETIME ;
    bSendBuzzerMode = TRUE ;
    RockFunctionEnable(false);  
}
/*******************************************************************************/
//敲打音乐互动
unsigned int AD_KNOCK_PWM(unsigned int nADValue)
{
    unsigned int nRetPWM ;
    if(nADValue < ADSTRONG1)  nRetPWM = KNOCK_SPEED0_PWM;
    else if(nADValue < ADSTRONG2)  nRetPWM = KNOCK_SPEED1_PWM;
    else if(nADValue < ADSTRONG3)  nRetPWM = KNOCK_SPEED2_PWM;
    else if(nADValue < ADSTRONG4)  nRetPWM = KNOCK_SPEED3_PWM;
    else if(nADValue < ADSTRONG5)  nRetPWM = KNOCK_SPEED4_PWM;
    else if(nADValue < ADSTRONG6)  nRetPWM = KNOCK_SPEED5_PWM;
    else nRetPWM = KNOCK_SPEED6_PWM;
    return nRetPWM ;
}  
/*
n3D_position: 1-5 5个力度位置
n3D_MotorSpeed：运行速度
n3D_MotorStopTime：运行到位置后的停留时间
*/
void AxisUpdate_Waitting_100msInt(void)//3D启动10秒，不到位，认为到位
{
  
  if(bAxisUpdate_Manual_Waitting_Timef == TRUE)
  {
    nAxisUpdate_Manual_Waitting_Time_cnt++;
    if(nAxisUpdate_Manual_Waitting_Time_cnt >=100)
    {
      bAxisUpdate = FALSE;
      b3D_MotorInProcess = false;
    }
  }
  else
  {
    nAxisUpdate_Manual_Waitting_Time_cnt =0;
  }
  
  if(bAxisUpdate_Program_Waitting_Timef == TRUE)
  {
    nAxisUpdate_Program_Waitting_Time_cnt++;
    if(nAxisUpdate_Program_Waitting_Time_cnt >=100)
    {
      bAxisUpdate = FALSE;b3D_MotorInProcess = false;
    }
  }
  else
  {
    nAxisUpdate_Program_Waitting_Time_cnt =0;
  }
 
}

uint8_t _3D_Protect()
{
    if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
    {
        if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7))
            b3D_MotorInProcess = false; 
        
        bAxisUpdate = true; 
        nDisplayAxisStrength = 4;// wgh 20140421
        //      break;  
        return 1;
    }
    return 0;
}

/**********************************************************************************************************/
void _3DMotorControl(unsigned char state,unsigned char position,unsigned char speed,unsigned char stopTime)
{
    if(/*Problem_Get3DFault() || */Problem_GetWalkSwitchFault())
    {
        b3D_MotorInProcess = false; 
        AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
        return;
    }
    
    
    switch(state)
    {
    default: 
    case  _3D_MANUAL:  //手动控制 
        //3D启动10秒，不到位，认为到位
        bAxisUpdate_Program_Waitting_Timef = FALSE;
        nAxisUpdate_Program_Waitting_Time_cnt = 0;
        
        b3D_MotorInProcess = FALSE ; 
        if(_3D_Protect()) break;
        
//        if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
//        {
//            AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7);
//            bAxisUpdate = true; 
//            nDisplayAxisStrength = 4;// wgh 20140421
//            break;      
//        }
        
        if(bAxisUpdate)
        {
            nFinalAxisStrength = nKeyAxisStrength;  
            nDisplayAxisStrength = nFinalAxisStrength;
            if(nKeyAxisStrength ==0)
            {
                if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nFinalAxisStrength,_3D_SPEED_4) == TRUE)
                {
                    bAxisUpdate = FALSE;  
                }
            }
            else
            {
                if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nFinalAxisStrength,_3D_SPEED_8) == TRUE)
                {
                    bAxisUpdate = FALSE;  
                }
            }
            //3D启动10秒，不到位，认为到位
            //bAxisUpdate_Manual_Waitting_Timef = TRUE;
        }
        else
        {
            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
            //3D启动10秒，不到位，认为到位
            nAxisUpdate_Manual_Waitting_Time_cnt = 0;
            nAxisUpdate_Program_Waitting_Time_cnt = 0;
            bAxisUpdate_Manual_Waitting_Timef = FALSE;
            bAxisUpdate_Program_Waitting_Timef = FALSE;
        }
        break;
    case _3D_SIDE_TOGGLE:
        if(_3D_Protect()) break;
        //      if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
        //    {
        //      AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7);
        //      b3D_MotorInProcess = false;
        //      bAxisUpdate = true; 
        //      //nDisplayAxisStrength = 4;//
        //      break;      
        //    }
        if(AxisMotor_Control(STATE_RUN_AXIS_TOGGLE,position,speed))
        {
            b3D_MotorInProcess = false;
            bAxisUpdate = true; 
            __NOP();
        }
        break;
    case _3D_KNEAD:
        //    if(_3D_Protect()) break;
        //     if((Input_GetWalkMotorPosition()) > (_3D_MOTOR_WALK_MAX_POSITION))
        //    {
        //      AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7);
        //      b3D_MotorInProcess = false;
        //      bAxisUpdate = true; 
        //      //nDisplayAxisStrength = 4;//
        //      break;      
        //    }
        //     if(AxisMotor_Control(STATE_RUN_AXIS_3D_KNEAD,position,speed))
        //     {
        //        __NOP();
        //       b3D_MotorInProcess = false;
        //       bAxisUpdate = true; 
        //     }
        b3D_MotorInProcess = false;
        AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
        break;
        //++++++++++++++++++++++++++++++++++++++ 
        //机芯处于MANUAL 模式时，3D 前后工作
    case _3D_AUTO_WALK:
        if(_3D_Protect()) break;
        //    if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
        //    {
        //      AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7);
        //      b3D_MotorInProcess = false;
        //      bAxisUpdate = true; 
        //      //nDisplayAxisStrength = 4;//
        //      break;      
        //    }
        if(AxisMotor_Control(STATE_RUN_AXIS_WALK,position,speed))
        {
            __NOP();
            b3D_MotorInProcess = false;
            bAxisUpdate = true; 
            __NOP();
        }
        break;
    case  _3D_PROGRAM:
        if(_3D_Protect()) break;
        //    if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
        //    {
        //      AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7);
        //      b3D_MotorInProcess = false;
        //      bAxisUpdate = true; 
        //      nDisplayAxisStrength = 4;// wgh 20140421
        //      break;      
        //    }
        if(bAxisUpdate)
        {
            unsigned char strength = nSetAxisStrength;
            switch(nKeyAxisStrength)
            {
                
            case 0:  if(strength > 0) strength--;
            case 1:  if(strength > 0) strength--;
            case 2:  nFinalAxisStrength = strength; 
            nDisplayAxisStrength = nFinalAxisStrength;//20150421 wgh 添加肩部显示
            break;
            case 4:  if(strength < 4) strength++;
            case 3:  if(strength < 4) strength++;
            nFinalAxisStrength = strength; 
            nDisplayAxisStrength = nFinalAxisStrength;//20150421 wgh 添加肩部显示
            break;  
            }
            //bAxisUpdate_Program_Waitting_Timef = TRUE;
        }
        
        if(!b3D_MotorInProcess && !bAxisUpdate)
        {
            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
            nAxisUpdate_Manual_Waitting_Time_cnt = 0;
            nAxisUpdate_Program_Waitting_Time_cnt = 0;
            bAxisUpdate_Manual_Waitting_Timef = FALSE;
            bAxisUpdate_Program_Waitting_Timef = FALSE;
            break;
        }
        
        if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nFinalAxisStrength,speed))
        {
            bAxisUpdate = false;
            if(nCur3D_MotorStopCounter >= stopTime)
            {
                b3D_MotorInProcess = FALSE ; 
            }
        }
        else
        {
            nCur3D_MotorStopCounter = 0;
        }
        break;
    case _3D_WORK_CIRCLE:
        if(_3D_Protect()) break;
        if(AxisMotor_Control(STATE_RUN_AXIS_CIRCLE,position,_3D_SPEED_8))
        {
            bAxisUpdate = false;
            if(nCur3D_MotorStopCounter >= stopTime)
            {
                b3D_MotorInProcess = FALSE ; 
            }
        }
        break;
        /**********************轻柔呵护相关开始*******************/
    case _3D_KNEAD_NECK_3:
        if(AxisMotor_Control(STATE_RUN_HALF_CIRCLE_3,position,speed))
        {
            b3D_MotorInProcess = false;
            bAxisUpdate = true; 
        }
        break;
        /**********************轻柔呵护相关结束*******************/
    case _3D_PARK:
        nAxisUpdate_Manual_Waitting_Time_cnt = 0;
        nAxisUpdate_Program_Waitting_Time_cnt = 0;
        bAxisUpdate_Manual_Waitting_Timef = FALSE;
        bAxisUpdate_Program_Waitting_Timef = FALSE;
        b3D_MotorInProcess = false;
        AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
        break;
    }
    
    
    
}
/*******************************************************************************/
//捶击电机控制
void KnockMotorControl(unsigned char nKnockMotorState,unsigned char nKnockingMotorRunTime,unsigned char nKnockingMotorStopTime)
{
    static bool  bKnockMotorPowerFlag;
    static unsigned char nKnockMotorStateTest;
#ifdef  SELECT_3D
    
    if(nKnockMotorState==5) bKnockMotorInProcess = TRUE;
    if(nBackMainRunMode == BACK_MAIN_MODE_3D)
    {
        if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
        {
            KnockMotor_Set_Pwm_Data(KNOCK_SPEED0_PWM);
            KnockMotor_Break();
            bKnockMotorInProcess = FALSE ;
            bKnockMotorPowerFlag = FALSE ;
            nCurKnockRunStopCounter = 0 ;//叩击动作记数器
            return;      
        }
    }
#endif
    //static int step = 0;
    //敲打电机音乐互动（高频）
    if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) &&
       (nBackSubRunMode == BACK_SUB_MODE_MUSIC) &&
           (nKnockMotorState == KNOCK_RUN_MUSIC))
    {
        nMusicKnockPWM = AD_KNOCK_PWM(nAvrADResult0) ;
        KnockMotor_Set_Pwm_Data(nMusicKnockPWM);
        bKnockMotorInProcess = FALSE ;
    }
    else
    {
        if(bKnockMotorInProcess == TRUE)
        {
            switch(nKnockMotorState)
            {
            default:
                bKnockMotorInProcess = FALSE ;
                //                while(1)
                //                {
                //                    //WDOG_Feed();
                //                }
                break;
            case KNOCK_PWM:
                if(KnockSlow_Flag!=0)
                {
                    
                    nCurKneadKnockSpeed = 3;//nCurKneadKnockSpeed
                    __NOP();
                    if(nKnockMotorStateTest==5)  nCurKneadKnockSpeed = 3;
                }
                else
                {
                    nCurKneadKnockSpeed = 1;
                }
                bKnockMotorPowerFlag = TRUE;
                bKnockMotorInProcess = FALSE ;
                break;
            case KNOCK_STOP:
                bKnockMotorPowerFlag = FALSE ;
                if(nCurActionStepCounter >= nKnockingMotorRunTime)
                {
                    bKnockMotorInProcess = FALSE ;
                }
                break ;
            case KNOCK_RUN_WIDTH://定位完成后进行
                if(bKneadMotorInProcess == TRUE)
                {
                    bKnockMotorPowerFlag = FALSE ;
                    nCurActionStepCounter = 0 ;
                }
                else
                {
                    bKnockMotorPowerFlag = TRUE ;
                    if(nCurActionStepCounter >= nKnockingMotorRunTime)
                    {
                        bKnockMotorInProcess = FALSE ;
                    }
                }
                break ;
            case KNOCK_RUN:
                bKnockMotorPowerFlag = TRUE ;
                if(nCurActionStepCounter >= nKnockingMotorRunTime)
                {
                    bKnockMotorInProcess = FALSE ;
                }
                break ;
            case KNOCK_RUN_STOP:  //叩击
                if(bKneadMotorInProcess == TRUE)
                {
                    bKnockMotorPowerFlag = FALSE ;
                    nCurKnockRunStopCounter = 0 ;//叩击动作记数器
                }
                else
                {
                    if(nCurKnockRunStopCounter < nKnockingMotorRunTime)//nCurKnockRunStopCounter:单位:2ms; nKnockingMotorRunTime:单位:100ms;
                    {
                        bKnockMotorPowerFlag = TRUE ;
                    }
                    if((nCurKnockRunStopCounter >= nKnockingMotorRunTime) && (nCurKnockRunStopCounter < (nKnockingMotorRunTime + nKnockingMotorStopTime)))
                    {
                        bKnockMotorPowerFlag = FALSE ;
                        //行走电机完成动作时，该动作也结束
                        
                        
                        
                    }
                    if(nCurKnockRunStopCounter >= (nKnockingMotorRunTime + nKnockingMotorStopTime))
                    {
                        nCurKnockRunStopCounter = 0 ;
                        if(bWalkMotorInProcess == FALSE)
                        {
                            bKnockMotorInProcess = FALSE ;
                        }                        
                        
                    }
                }
                break ;
            case KNOCK_RUN_MUSIC:
                break ;
            }
        }
        if(bKnockMotorPowerFlag == TRUE)
        {
            switch(nCurKneadKnockSpeed)
            {
            case 1:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED1_PWM);
                break ;
            case 2:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED2_PWM);
                break ;
            case 3:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED3_PWM);
                break ;
            case 4:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED4_PWM);
                break ;
            case 5:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED5_PWM);
                break ;
            case 6:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED6_PWM);
                break ;
            default:
                KnockMotor_Set_Pwm_Data(KNOCK_SPEED1_PWM);
                break ;
            }
            KnockMotor_ClockRun();
        }
        else
        {
            KnockMotor_Set_Pwm_Data(KNOCK_SPEED0_PWM);
            KnockMotor_Break();
        }
    }
}
/*******************************************************************************/
void main_GetKneadPosition(void)
{            
    static unsigned char nLastKneadPosition = KNEAD_WIDTH_UNKNOWN ;
    unsigned char nNowKneadPosition = Input_GetKneadPosition();
    if(nNowKneadPosition != nLastKneadPosition) 
    {
        //nWidthOverTime = 0;
        if(nNowKneadPosition == KNEAD_WIDTH_MIN)
        {
            bHasKneadWidthMinPulse = TRUE ;
            bHasKneadWidthMedPulse = FALSE ;
            bHasKneadWidthMaxPulse = FALSE ;
            bDisplayKneadTrackMin = TRUE ;
            bDisplayKneadTrackMed = FALSE ;
            bDisplayKneadTrackMax = FALSE ;
            bDisplayKneadWidthMin = TRUE ;
            bDisplayKneadWidthMed = FALSE ;
            bDisplayKneadWidthMax = FALSE ;
            nLastKneadPosition = KNEAD_WIDTH_MIN ;
        }
        if(nNowKneadPosition == KNEAD_WIDTH_MED)
        {
            bHasKneadWidthMinPulse = FALSE ;
            bHasKneadWidthMedPulse = TRUE ;
            bHasKneadWidthMaxPulse = FALSE ;
            bDisplayKneadTrackMin = FALSE ;
            bDisplayKneadTrackMed = TRUE ;
            bDisplayKneadTrackMax = FALSE ;
            bDisplayKneadWidthMin = FALSE ;
            bDisplayKneadWidthMed = TRUE ;
            bDisplayKneadWidthMax = FALSE ;
            nLastKneadPosition = KNEAD_WIDTH_MED ;
        }
        if(nNowKneadPosition == KNEAD_WIDTH_MAX)
        {
            bHasKneadWidthMinPulse = FALSE ;
            bHasKneadWidthMedPulse = FALSE ;
            bHasKneadWidthMaxPulse = TRUE ;
            bDisplayKneadTrackMin = FALSE ;
            bDisplayKneadTrackMed = FALSE ;
            bDisplayKneadTrackMax = TRUE ;
            bDisplayKneadWidthMin = FALSE ;
            bDisplayKneadWidthMed = FALSE ;
            bDisplayKneadWidthMax = TRUE ;
            nLastKneadPosition = KNEAD_WIDTH_MAX ;
        }
    }
}

unsigned int widthstep =0;
/***********************************************************************************/
//void KneadMotorControl(unsigned char nKneadMotorState,unsigned char nKneadMotorCycles)
//{
//    unsigned int speed;
//    unsigned int step;
//          if(nBackMainRunMode == BACK_MAIN_MODE_3D)
//          {
//            if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
//            {
//              KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
//              nFinalKneadMotorState = STATE_IDLE ;
//              bKneadMotorInProcess = FALSE ;
//              return;      
//            }
//          }  
//    if(bKneadMotorInProcess == TRUE)
//    {
//        switch(nKneadMotorState)
//        {
//        default:
//        case KNEAD_STOP:
//            nFinalKneadMotorState = STATE_IDLE ;
//            bKneadMotorInProcess = FALSE ;
//            break ;
//            case KNEAD_FITFUL:  //揉捏方式1--断续揉捏
//          switch(bkneadStep)
//          {
//          case 0:
//           if(bHasKneadWidthMedPulse == TRUE)
//            {
//                bHasKneadWidthMedPulse = FALSE ;
//                if(Input_GetKneadMid() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 1;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//            }
//            break;
//          case 1:
//             nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//             nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//             bkneadTimeFlag = TRUE;
//             upWalkRun = TRUE;
//             if(bkneadTime >= 130)
//             {
//               upWalkRun = FALSE;
//               bkneadTimeFlag = FALSE;
//               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//               nFinalKneadMotorState = STATE_IDLE ;
//               bkneadStopTimeFlag = TRUE;
//               if(bkneadStopTime >= 6)
//               {
//                 bkneadTime = 0;
//                 bkneadStopTime = 0;
//                 bkneadStopTimeFlag = FALSE;
//                 bkneadStep = 2;
//               }
//             }
//             break;
//          case 2:
//            downWalkRun = TRUE;
//            if(bHasKneadWidthMedPulse == TRUE)
//            {
//                bHasKneadWidthMedPulse = FALSE ;
//                if(Input_GetKneadMid() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 3;
//                    downWalkRun = FALSE;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//            }
//            break;
//          case 3:
//            nCurKneadWidth = KNEAD_WIDTH_MED ;
//            nFinalKneadMotorState = STATE_IDLE ;
//            bkneadStopTimeFlag = TRUE;
//            if(bkneadStopTime >= 6)
//            {
//              bkneadStopTimeFlag = FALSE;
//              bkneadStopTime = 0;
//              bkneadStep = 1;
//              CycleCount++;
//              if(CycleCount >= nKneadMotorCycles)
//              {
//                CycleCount = 0;
//                bKneadMotorInProcess = FALSE ;
//                bkneadStep = 0;
//              }          
//            }
//            break; 
//          }
//          break;
//        case KNEAD_TOGGLE:  //揉捏方式2
//                switch(bkneadStep)
//                {
//                case 0:
//                 if(bHasKneadWidthMedPulse == TRUE)
//                  {
//                      bHasKneadWidthMedPulse = FALSE ;
//                      if(Input_GetKneadMid() == 0)
//                      {  
//                          nCurKneadWidth = KNEAD_WIDTH_MED ;
//                          nFinalKneadMotorState = STATE_IDLE ;
//                          bkneadStep = 1;
//                      }                    
//                  }
//                  else
//                  {
//                      nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                      nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//                  }
//                  break;
//                 case 1:
//                   upWalkRun = TRUE;
//                   bkneadTimeFlag = TRUE;
//                   nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                   nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//                   if(bkneadTime >= 130)
//                   {
//                     upWalkRun = FALSE;
//                     bkneadTimeFlag = FALSE;
//                     nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                     nFinalKneadMotorState = STATE_IDLE ;
//                     bkneadStopTimeFlag = TRUE;
//                     if(bkneadStopTime >= 6)
//                     {
//                       bkneadTime = 0;
//                       bkneadStopTime = 0;
//                       bkneadStopTimeFlag = FALSE;
//                       bkneadStep = 2;
//                     }
//                   }
//                  break;
//                case 2:
//                  downWalkRun = TRUE;
//                  if(bHasKneadWidthMedPulse == TRUE)
//                  {
//                      bHasKneadWidthMedPulse = FALSE ;
//                      if(Input_GetKneadMid() == 0)
//                      {  
//                          downWalkRun = FALSE;
//                          nCurKneadWidth = KNEAD_WIDTH_MED ;
//                          nFinalKneadMotorState = STATE_IDLE ;
//                          bkneadStep = 3;
//                       }                    
//                  }
//                  else
//                  {
//                      nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                      nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                  }
//                  break;
//              case 3:
//                bkneadStopTimeFlag = TRUE;
//                if(bkneadStopTime >= 6)
//                {
//                   bkneadStopTime = 0;
//                   bkneadStopTimeFlag = FALSE;
//                   bkneadStep = 1;
//                   CycleCount++;
//                   if(CycleCount >= nKneadMotorCycles)
//                   {
//                      bkneadStep = 0;
//                      CycleCount = 0;
//                      bKneadMotorInProcess = FALSE ;
//                   }
//                 }  
//                 break;
//                }
//                break;
//        case KNEAD_RUBBING:
//          switch(bkneadStep)
//          {
//          case 0:
//            KnockSlow_Flag = 1;
//            if(bHasKneadWidthMinPulse == TRUE)
//            {
//                bHasKneadWidthMinPulse = FALSE ;
//                if(Input_GetKneadMin() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 1;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//            }
//            break;
//            case 1:
//            if(bHasKneadWidthMedPulse == TRUE)
//            {
//                bHasKneadWidthMedPulse = FALSE ;
//                if(Input_GetKneadMid() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    bkneadStep = 2;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break;
//            case 2:
//            KnockSlow_Flag = 0;
//            if(bHasKneadWidthMaxPulse == TRUE)
//            {
//                bHasKneadWidthMaxPulse = FALSE ;
//                if(Input_GetKneadMax() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 3;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break;
//            case 3:
//            if(bHasKneadWidthMedPulse == TRUE)
//            {
//                bHasKneadWidthMedPulse = FALSE ;
//                if(Input_GetKneadMid() == 0)
//                {  
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    CycleCount++;
//                    if(CycleCount>nKneadMotorCycles)
//                    {
//                      bKneadMotorInProcess = FALSE ;
//                      CycleCount = 0;
//                    }
//                    
//                    bkneadStep = 0;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//            }
//            break;
//          }
//          break;
//  
//        case KNEAD_RUN_MAX_MIN:    
//           switch(bkneadStep)
//           {
//           case 0:
//            upWalkRun = TRUE;
//            downWalkRun = FALSE;
//            if(bHasKneadWidthMaxPulse == TRUE)
//            {
//                bHasKneadWidthMaxPulse = FALSE ;
//                if(Input_GetKneadMax() == 0)
//                {  
//                    upWalkRun = FALSE;
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                    bkneadStep = 1;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break;
//         case 1:
//            downWalkRun = TRUE;
//            if(bHasKneadWidthMinPulse == TRUE)
//            {
//                bHasKneadWidthMinPulse = FALSE ;
//                if(Input_GetKneadMin() == 0)
//                {  
//                    downWalkRun = FALSE;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;                  
//                    CycleCount++;
//                    if(CycleCount>=nKneadMotorCycles)
//                    {
//                      bKneadMotorInProcess = FALSE ;
//                      CycleCount = 0;
//                      nFinalKneadMotorState = STATE_IDLE ;
//                    }
//                    bkneadStep = 0;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break;
//         }
//         break;
//        case KNEAD_RUN_WALK:
//           if(Walk_StopFlag)
//             {
//               bKneadMotorInProcess = FALSE ;
//               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//               nFinalKneadMotorState = STATE_IDLE ;
//               bkneadTime = 0;
//               bkneadTimeFlag = 0;  
//               upWalkRun = 0;
//               downWalkRun = 0;
//               Walk_StopFlag = 0;
//               bkneadStep = 0;               
//               break;
//             }
//            switch(bkneadStep)
//            {
//              case 0: 
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                bkneadTimeFlag = TRUE;
//                upWalkRun = TRUE;  
//                downWalkRun = FALSE;
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                if(bkneadTime >= 170)
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    upWalkRun = FALSE;
//                    bkneadStopTimeFlag = TRUE;
//                    bkneadTimeFlag = FALSE;
//                    bkneadTime = 0;
//                    bkneadStep = 1;
//                }
//               break;
//              case 1:              
//              downWalkRun = TRUE;
//              if(bHasKneadWidthMedPulse == TRUE)
//              {
//                  bHasKneadWidthMedPulse = FALSE ;
//                  if(Input_GetKneadMid() == 0)
//                  {
//                      nCurKneadWidth = KNEAD_WIDTH_MED ;                    
//                      bkneadStep = 0;
//                      downWalkRun = FALSE;          
//                  }
//              }
//              else
//              {
//                  nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                  nFinalKneadMotorState = STATE_RUN_CLOCK ;                 
//              }
//           break;
//           }
//           
//          break;
//        case KNEAD_MAX_MIN://先定位到Min
//         switch(bkneadStep)
//         {
//         case 0:
//            downWalkRun = TRUE;
//            upWalkRun = FALSE;
//            if(bHasKneadWidthMaxPulse == TRUE)
//            {
//                bHasKneadWidthMaxPulse = FALSE ;
//                if(Input_GetKneadMax() == 0)
//                {  
//                    downWalkRun = FALSE;
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 1;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break;
//         case 1:
//            upWalkRun = TRUE;
//            if(bHasKneadWidthMinPulse == TRUE)
//            {
//                bHasKneadWidthMinPulse = FALSE ;
//                if(Input_GetKneadMin() == 0)
//                {  
//                    upWalkRun = FALSE;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    CycleCount++;
//                    if(CycleCount>=nKneadMotorCycles)
//                    {
//                      bKneadMotorInProcess = FALSE ;
//                      CycleCount = 0;
//                      nFinalKneadMotorState = STATE_IDLE ;
//                    }
//                    bkneadStep = 0;
//                }                    
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//            }
//            break;
//         }
//         break;
//        case KNEAD_MAX_MED:
//           if(Walk_StopFlag && (KneadTimesCount >= nKneadMotorCycles))
//           {
//             bKneadMotorInProcess = FALSE ;
//             nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//             nFinalKneadMotorState = STATE_IDLE ;
//             bkneadTime = 0;
//             bkneadTimeFlag = 0;
//             bkneadStopTime = 0;
//             bkneadStopTimeFlag = 0;
//             upWalkRun = 0;
//             downWalkRun = 0;
//             Walk_StopFlag = 0;
//             bkneadStep = 0; 
//             KneadTimesCount = 0;
//             break;
//           }
//         switch(bkneadStep)
//         {
//                      
//         case 0:
//               bkneadTimeFlag = TRUE;
//               nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//               upWalkRun = TRUE;
//               downWalkRun = FALSE;  
//               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//               if(bkneadTime >= 210)
//               {
//                 upWalkRun = FALSE ;
//                 bkneadTime = 0;
//                 bkneadTimeFlag = FALSE;
//                 nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                 nFinalKneadMotorState = STATE_IDLE ;                                        
//                 bkneadStep = 1;   
//                 Walk_CheckPoint = TRUE;  
//               }
//               break;
//         case 1:
//                downWalkRun = TRUE;
//                Walk_CheckPoint = FALSE;  
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMaxPulse = FALSE ;
//                    if(Input_GetKneadMax() == 0)
//                    {  
//                        downWalkRun = FALSE;
//                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bkneadStep = 0;
//                        KneadTimesCount++;                       
//                    }                    
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                    //downWalkRunOver = 0;
//                }
//                break;
//            }            
//            break;
//            case KNEAD_MAX_MAX:
//              if(Walk_StopFlag)
//              {
//               bKneadMotorInProcess = FALSE ;
//               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//               nFinalKneadMotorState = STATE_IDLE ;
//               bkneadTime = 0;
//               bkneadTimeFlag = 0;
//               bkneadStopTime = 0;
//               bkneadStopTimeFlag = 0;
//               upWalkRun = 0;
//               downWalkRun = 0;
//               Walk_StopFlag = 0;
//               bkneadStep = 0;
//               break;
//              }
//            switch(bkneadStep)
//              {
//              case 0:
//                  bkneadTimeFlag = TRUE;
//                  nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//                  downWalkRun = FALSE;
//                  upWalkRun = TRUE;
//                  bkneadStep = 0;
//                  nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                  if(bkneadTime >= 240)
//                  {
//                    bkneadTime = 0;
//                    bkneadTimeFlag = FALSE;
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_IDLE ;   
//                    bkneadStep = 1;
//                    upWalkRun = FALSE;                                    
//                  }
//                  break;                             
//              case 1:             
//                downWalkRun = TRUE;
//                upWalkRun = FALSE;
//                //downWalkRunOver = 0;
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMaxPulse = FALSE ;        
//                    if(Input_GetKneadMax() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bkneadStep = 0;
//                        downWalkRun = FALSE; 
//                    }
//                }
//                
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                }
//                break;
//              }            
//              break;
//           case KNEAD_MED_MED:
//             if(Walk_StopFlag)
//             {
//               bKneadMotorInProcess = FALSE ;
//               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//               nFinalKneadMotorState = STATE_IDLE ;
//               bkneadTime = 0;
//               bkneadTimeFlag = 0;
//               bkneadStopTime = 0;
//               bkneadStopTimeFlag = 0;
//               upWalkRun = 0;
//               downWalkRun = 0;
//               Walk_StopFlag = 0;
//               bkneadStep = 0;
//               nKneadMotorCycles = 0;
//               break;
//             }
//            switch(bkneadStep)
//            {
//              case 0:
//              downWalkRun = TRUE;
//              upWalkRun = FALSE;
//              Walk_CheckPoint = FALSE;                     //下行时不予检测
//              if(bHasKneadWidthMedPulse == TRUE)
//              {
//                  bHasKneadWidthMedPulse = FALSE ;
//                  if(Input_GetKneadMid() == 0)
//                  {
//                      nCurKneadWidth = KNEAD_WIDTH_MED ;
//                      nFinalKneadMotorState = STATE_IDLE ;
//                      bkneadStep = 1;
//                      downWalkRun = FALSE;
//                  }
//              }
//              else
//              {
//                  nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                  nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                  //downWalkRunOver = 0;
//              }
//           break;            
//              case 1: 
//                upWalkRun = TRUE;   
//                downWalkRun = FALSE;
//                bkneadTimeFlag = TRUE;
//                if(bkneadTime >= 170)
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_IDLE ; 
//                    upWalkRun = FALSE;
//                    bkneadTime = 0;
//                    bkneadStep = 0;
//                    bkneadTimeFlag = FALSE;
//                    Walk_CheckPoint = TRUE;            //到达揉捏最高点，可以检测行程
//                }
//                else
//                {
//                  nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                  nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//                }
//            break;
//          }
//          break;
//          case KNEAD_MED_STOP_MED:           
//            switch(bkneadStep)
//            {                       
//              case 0: 
//                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
//                bkneadTimeFlag = TRUE;
//                upWalkRun = TRUE;  
//                downWalkRun = 0;
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                if(bkneadTime >= 140)
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_IDLE ; 
//                    upWalkRun = FALSE;
//                    bkneadStopTimeFlag = TRUE;   
//                    if(bkneadStopTime >= nKneadMotorCycles)
//                    {
//                      bkneadTimeFlag = FALSE;
//                      bkneadTime = 0;
//                      bkneadStep = 1;
//                      bkneadStopTime = 0;
//                      bkneadStopTimeFlag = FALSE;
//                    }                    
//                  }
//            break;
//            case 1:            
//              downWalkRun = TRUE;
//              upWalkRun = 0;
//              if(bHasKneadWidthMedPulse == TRUE)
//              {
//                  bHasKneadWidthMedPulse = FALSE ;
//                  if(Input_GetKneadMid() == 0)
//                  {
//                      nCurKneadWidth = KNEAD_WIDTH_MED ;
//                      nFinalKneadMotorState = STATE_IDLE ;
//                      bKneadMotorInProcess = FALSE ;
//                      bkneadStep = 0;
//                      downWalkRun = 0;
//                      upWalkRun = 0;                         
//                  }
//              }
//              else
//              {
//                  nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                  nFinalKneadMotorState = STATE_RUN_CLOCK ;
//              }
//           break;
//          }
//          break;
//           case KNEAD_TO_SIDE:
//     
//          switch(bkneadStep)
//          {
//          case 0:
//            if(_3D_Min_Ok)
//            {           
//                if(bHasKneadWidthMinPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 1;
//                    Knead_Min_Ok = 1;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                }
//            }
//          break;
//          case 1:
//            if( _3D_Max_Ok)
//            {
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;               
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    bkneadStep = 0;
//                    Knead_Min_Ok = 0;
//                    bKneadMotorInProcess = FALSE ;
//                    Knead_Min_Ok = 0;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //还未到达最窄处，继续逆时针转动
//                }
//                break;
//            }
//          }
//          break;
//        case KNEAD_STOP_AT_MIN:
//            if(nCurKneadWidth == KNEAD_WIDTH_MIN)
//            {
//                nFinalKneadMotorState = STATE_IDLE ;
//                bKneadMotorInProcess = FALSE ;
//            }
//            else
//            {
//                if(bHasKneadWidthMinPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    if(Input_GetKneadMin() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                }
//            }
//            break ;
//        case KNEAD_STOP_AT_MED:
//            if(nCurKneadWidth == KNEAD_WIDTH_MED)
//            {
//                nFinalKneadMotorState = STATE_IDLE ;
//                bKneadMotorInProcess = FALSE ;
//            }
//            else
//            {
//                if(bHasKneadWidthMedPulse == TRUE)
//                {
//                    bHasKneadWidthMedPulse = FALSE ;
//                    if(Input_GetKneadMid() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MED ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                }
//            }
//            break ;
//        case KNEAD_STOP_AT_MAX:
//            if(nCurKneadWidth == KNEAD_WIDTH_MAX)
//            {
//                nFinalKneadMotorState = STATE_IDLE ;
//                bKneadMotorInProcess = FALSE ;
//            }
//            else
//            {
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMaxPulse = FALSE ;
//                    if(Input_GetKneadMax() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
//                }
//            }
//            break ;
//        case KNEAD_RUN:
//            nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//            nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            bKneadMotorInProcess = FALSE ;
//            break ;
//        case KNEAD_RUN_STOP:
//        case KNEAD_RUN_STOP_AT_MIN:
//            if(bHasKneadWidthMinPulse == TRUE)
//            {
//                bHasKneadWidthMinPulse = FALSE ;
//                nCurKneadMotorCycles++ ;
//                if(nCurKneadMotorCycles > nKneadMotorCycles)
//                {
//                    if(Input_GetKneadMin() == 0)  
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break ;
//        case KNEAD_RUN_STOP_AT_MED:
//            if(bHasKneadWidthMedPulse == TRUE)
//            {
//                bHasKneadWidthMedPulse = FALSE ;
//                nCurKneadMotorCycles++ ;
//                if(nCurKneadMotorCycles > nKneadMotorCycles)
//                {
//                    if(Input_GetKneadMid() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MED ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break ;
//        case KNEAD_RUN_STOP_AT_MAX:
//            if(bHasKneadWidthMaxPulse == TRUE)
//            {
//                bHasKneadWidthMaxPulse = FALSE ;
//                nCurKneadMotorCycles++ ;
//                if(nCurKneadMotorCycles > nKneadMotorCycles)
//                {
//                    if(Input_GetKneadMax() == 0)
//                    {
//                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        bKneadMotorInProcess = FALSE ;
//                    }
//                }
//            }
//            else
//            {
//                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                nFinalKneadMotorState = STATE_RUN_CLOCK ;
//            }
//            break ;
//            //顺时针：窄-中-宽-半圈空闲-窄     
//            //逆时针：宽-中-窄-半圈空闲-宽          
//            /*
//            搓背程序依据  nCurKneadMotorCycles的值控制揉捏电机    
//            */
////begin...MED..............................
//        case KNEAD_RUN_MEDRUBBING:
//            /*顺时针转动缩小，逆时针变大*************************/
//            step = nCurKneadMotorCycles % 4;
//            switch(step)
//            {
//            case 0: 
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMedPulse == TRUE)
//                {
//                    bHasKneadWidthMedPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    nCurKneadMotorCycles++ ;       //到达窄位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING); 
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //还未到达最窄处，继续逆时针转动
//                }
//                /*********************************************/
//                break; 
//            case 1:  //停在最窄处
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING,1)) 
//                {
//                    nCurKneadMotorCycles++ ;       //加1
//                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从最窄到最宽，进行顺时针运动
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;
//            case 2: 
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMinPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    nCurKneadMotorCycles++ ;       //到达宽位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING); 
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从窄到宽顺时针转动
//                }
//                /*********************************************/
//                break;  
//            case 3: //停顿 
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING,1)) 
//                {
//                    nCurKneadMotorCycles++ ;       //加1
//                    
//                    if(nCurKneadMotorCycles > nKneadMotorCycles)
//                    {
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        
//                        if(bWalkMotorInProcess == FALSE)
//                        {
//                            bKneadMotorInProcess = FALSE ;
//                        }
//                    }
//                    else
//                    {
//                        nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动 
//                    }
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;  
//            }
//            
//            break;                      
////end...MED.............................  
//        case KNEAD_RUN_RUBBING:
//            step = nCurKneadMotorCycles % 4;
//            switch(step)
//            {
//            case 0: 
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMinPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    nCurKneadMotorCycles++ ;       //到达窄位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING); 
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //还未到达最窄处，继续逆时针转动
//                }
//                /*********************************************/
//                break; 
//            case 1:  //停在最窄处
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING,1)) 
//                {
//                    nCurKneadMotorCycles++ ;       //加1
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;
//            case 2: 
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMaxPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                    nCurKneadMotorCycles++ ;       //到达宽位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING); 
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从窄到宽顺时针转动
//                }
//                /*********************************************/
//                break;  
//            case 3: 
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING,1)) 
//                {
//                    nCurKneadMotorCycles++ ;       //加1
//                    
//                    if(nCurKneadMotorCycles > nKneadMotorCycles)
//                    {
//                        nFinalKneadMotorState = STATE_IDLE ;
//                        
//                        if(bWalkMotorInProcess == FALSE)
//                        {
//                            bKneadMotorInProcess = FALSE ;
//                        }
//                    }
//                    else
//                    {
//                        nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从最窄到最宽，进行顺时针运动 
//                    }
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;  
//            }
//            
//            break;
//	   //--------------------------------------------------------------
//	     //////////////////////////////////////////////////////////////////////////////////////////////////////////////////           
//       case KNEAD_STOP_AT_POSITION_TIME:
//            
//            switch(widthstep)
//            {
//            case 0:
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMaxPulse == TRUE)
//                {
//                    bHasKneadWidthMaxPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
//                    //nCurKneadMotorCycles++ ;       //到达窄位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING);
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    widthstep++;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //还未到达最MAX处，继续*时针转动
//                }
//                /*********************************************/
//                break;
//            case 1:  //停在最窄处
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING, 30))
//                {
//                   // nCurKneadMotorCycles++ ;       //加1
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
//                    widthstep++;
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;
//           case 2:
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMedPulse == TRUE)
//                {
//                    bHasKneadWidthMedPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MED ;
//                    //nCurKneadMotorCycles++ ;       //到达窄位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING);
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    widthstep++;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //还未到达最MAX处，继续*时针转动
//                }
//                /*********************************************/
//                break;
//            case 3:  //停在最窄处
//                /**************判断刹车时间************************/
//                if(Timer_Counter(C_TIME_RUBBING, 30))
//                {
//                   // nCurKneadMotorCycles++ ;       //加1
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
//                    widthstep++;
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    if(bWalkMotorInProcess == FALSE)
//                    {
//                      bKneadMotorInProcess = FALSE ;
//                      
//                    }
//                }
//                /*********************************************/
//                break;
//           case 4:
//                /**************判断是否到达最窄处*************************/
//                if(bHasKneadWidthMinPulse == TRUE)
//                {
//                    bHasKneadWidthMinPulse = FALSE ;
//                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
//                    //nCurKneadMotorCycles++ ;       //到达窄位置加1
//                    Timer_Counter_Clear(C_TIME_RUBBING);
//                    nFinalKneadMotorState = STATE_IDLE ;
//                    widthstep++;
//                }
//                else
//                {
//                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //还未到达最MAX处，继续*时针转动
//                }
//                /*********************************************/
//                break;
//            case 5:  //停在最窄处
//                /**************判断刹车时间************************/
//              
//              
//                if(Timer_Counter(C_TIME_RUBBING, 30))
//                {
//                   // nCurKneadMotorCycles++ ;       //加1
//                   // nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
//                    widthstep++;
//                    //bKneadMotorInProcess = FALSE ;                     
//                    if(bWalkMotorInProcess == FALSE)
//                    {
//                      bKneadMotorInProcess = FALSE ;
//                    }
//                }
//                else
//                {
//                    nFinalKneadMotorState = STATE_IDLE ;
//                }
//                /*********************************************/
//                break;
//  
//                
//            default:  
//              widthstep = 0;
//              break;
//            }
//
//            break;          
//            
//            
//            
// ///////////////////////////////////////////////////////////////////////////////////////////////////////  
//	    
// case KNEAD_STOP_AT_FORWARD_REWIND:
//           switch(widthstep)
//            {
//            case 0:  
//              Timer_Counter_Clear(C_TIME_RUBBING);
//              nFinalKneadMotorState = STATE_IDLE ;
//              widthstep++;
//              break;
//            case 1:
//              nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//              nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
//              if(Timer_Counter(C_TIME_RUBBING, 30))
//              {
//                // nCurKneadMotorCycles++ ;       //加1
//                nFinalKneadMotorState = STATE_IDLE ;
//                Timer_Counter_Clear(C_TIME_RUBBING);
//                widthstep++;
//              }
//              break;
//            case 2:  
//              nFinalKneadMotorState = STATE_IDLE ;
//              if(Timer_Counter(C_TIME_RUBBING, 5))
//              {
//                // nCurKneadMotorCycles++ ;       //加1
//                
//                Timer_Counter_Clear(C_TIME_RUBBING);
//                widthstep++;
//              }
//              break;
//            case 3:
//              nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
//              nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从最窄到最宽，进行顺时针运动
//              
//              
//              if(Timer_Counter(C_TIME_RUBBING, 30))
//              {
//                // nCurKneadMotorCycles++ ;       //加1
//                nFinalKneadMotorState = STATE_IDLE ;
//                Timer_Counter_Clear(C_TIME_RUBBING);
//                widthstep++;
//              }
//              break;
//            case 4:  
//              nFinalKneadMotorState = STATE_IDLE ;
//              if(Timer_Counter(C_TIME_RUBBING, 5))
//              {
//                // nCurKneadMotorCycles++ ;       //加1
//                
//                Timer_Counter_Clear(C_TIME_RUBBING);
//                widthstep++;
//                //bKneadMotorInProcess = FALSE ;
//                
//                if(bWalkMotorInProcess == FALSE)
//                {
//                  bKneadMotorInProcess = FALSE ;
//                }
//                
//              }
//              break;
//             default:  
//              widthstep = 0;
//              break;
//            }
//
//            break;                    
//        }
//    }
//    //确定揉捏马达的速度
//     if((nKneadMotorState == KNEAD_STOP_AT_MIN) ||
//       (nKneadMotorState == KNEAD_STOP_AT_MED) ||
//           (nKneadMotorState == KNEAD_STOP_AT_MAX) ||
//               (nKneadMotorState == KNEAD_RUN_STOP) )
//    {
//        speed =  KNEAD_SPEED2_PWM;
//    }
//    else if(nKneadMotorState == KNEAD_TO_SIDE)
//    {
//      speed =  KNEAD_SPEED3_PWM;
//    }
//    else
//    {
//        switch(nCurKneadKnockSpeed)
//        {
//        default:  
//        case 1:speed = KNEAD_SPEED1_PWM;  break ;
//        case 2:speed = KNEAD_SPEED2_PWM;  break ;
//        case 3:speed = KNEAD_SPEED3_PWM;  break ;
//        case 4:speed = KNEAD_SPEED4_PWM;  break ;
//        case 5:speed = KNEAD_SPEED5_PWM;  break ;
//        case 6:speed = KNEAD_SPEED6_PWM;  break ;
//        case 7:speed = KNEAD_TEST_PWM;    break;  
//       
//        }
//    }
//    if(nFinalKneadMotorState == STATE_RUN_CLOCK)
//    {
//        KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,speed);
//    }
//    if(nFinalKneadMotorState == STATE_RUN_UNCLOCK)
//    {
//        KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN,speed);
//    }
//    if(nFinalKneadMotorState == STATE_IDLE)
//    {
//        KneadMotor_Control(STATE_KNEAD_IDLE,speed);
//    }
//}
void Knead_InProcess(uint8_t KneadWidth, uint8_t FinalKneadMotorState,uint8_t KneadMotorInProcess)// 解决软件优化问题
{
  
  nCurKneadWidth = KneadWidth ;
  nFinalKneadMotorState = FinalKneadMotorState ;
  if((KneadMotorInProcess==FALSE)|(KneadMotorInProcess==TRUE))
   bKneadMotorInProcess = KneadMotorInProcess ;
}

/***********************************************************************************************/
void KneadMotorControl(unsigned char nKneadMotorState,unsigned char nKneadMotorCycles)
{
    unsigned int speed;
    unsigned int step;
    KneadState = nKneadMotorState;
    if(nBackMainRunMode == BACK_MAIN_MODE_3D)
    {
        if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
        {
            KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
            nFinalKneadMotorState = STATE_IDLE ;
            bKneadMotorInProcess = FALSE ;
            return;      
        }
    }  
    if(bKneadMotorInProcess == TRUE)
    {
        switch(nKneadMotorState)
        {
        default:
        case KNEAD_STOP:
            nFinalKneadMotorState = STATE_IDLE ;
            bKneadMotorInProcess = FALSE ;
            break ;
        case KNEAD_RUN:
            nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            nFinalKneadMotorState = STATE_RUN_CLOCK ;
            nKneadTurn = 1;
            bKneadMotorInProcess = FALSE ;
            break ;
        case KNEAD_ANTIRUN:
            nKneadTurn = 2;
            nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
            bKneadMotorInProcess = FALSE ;//在自动程序数组同步其他电机的停止状态，只要其他电机都停止默认该电机也会停止
            break ;
        case KNEAD_FITFUL:  //揉捏方式1--断续揉捏
            switch(bkneadStep)
            {
            case 0:
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {  
                        bkneadStep = 1;
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                    nKneadTurn = 2;
                }
                break;
            case 1:
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                nKneadTurn = 2;
                bkneadTimeFlag = TRUE;
                upWalkRun = TRUE;
                if(bkneadTime >= 130)
                {
                    upWalkRun = FALSE;
                    bkneadTimeFlag = FALSE;
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_IDLE ;
                    bkneadStopTimeFlag = TRUE;
                    if(bkneadStopTime >= 6)
                    {
                        bkneadTime = 0;
                        bkneadStopTime = 0;
                        bkneadStopTimeFlag = FALSE;
                        bkneadStep = 2;
                    }
                }
                break;
            case 2:
                downWalkRun = TRUE;
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {  
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 3;
                        downWalkRun = FALSE;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                    nKneadTurn = 2;
                }
                break;
            case 3:
                nCurKneadWidth = KNEAD_WIDTH_MED ;
                nFinalKneadMotorState = STATE_IDLE ;
                bkneadStopTimeFlag = TRUE;
                if(bkneadStopTime >= 6)
                {
                    bkneadStopTimeFlag = FALSE;
                    bkneadStopTime = 0;
                    bkneadStep = 1;
                    CycleCount++;
                    if(CycleCount >= nKneadMotorCycles)
                    {
                        CycleCount = 0;
                        bKneadMotorInProcess = FALSE ;
                        bkneadStep = 0;
                    }          
                }
                break; 
            default:               //cyw
                bkneadStep = 0;
                break;
            }
            break;
        case KNEAD_TOGGLE:  //揉捏方式2
            switch(bkneadStep)
            {
            default:                   //cyw
            case 0:
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {  
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 1;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                    nKneadTurn = 2;
                }
                break;
            case 1:
                upWalkRun = TRUE;
                bkneadTimeFlag = TRUE;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                nKneadTurn = 2;
                if(bkneadTime >= 130)
                {
                    upWalkRun = FALSE;
                    bkneadTimeFlag = FALSE;
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_IDLE ;
                    bkneadStopTimeFlag = TRUE;
                    if(bkneadStopTime >= 6)
                    {
                        bkneadTime = 0;
                        bkneadStopTime = 0;
                        bkneadStopTimeFlag = FALSE;
                        bkneadStep = 2;
                    }
                }
                break;
            case 2:
                downWalkRun = TRUE;
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {  
                        downWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 3;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            case 3:
                bkneadStopTimeFlag = TRUE;
                if(bkneadStopTime >= 6)
                {
                    bkneadStopTime = 0;
                    bkneadStopTimeFlag = FALSE;
                    bkneadStep = 1;
                    CycleCount++;
                    if(CycleCount >= nKneadMotorCycles)
                    {
                        bkneadStep = 0;
                        CycleCount = 0;
                        bKneadMotorInProcess = FALSE ;
                    }
                }  
                break;
            }
            break;
        case KNEAD_RUBBING:
          switch(bkneadStep)
          {
          default:
          case 0:
            KnockSlow_Flag = 1;
            if(bHasKneadWidthMinPulse == TRUE)
            {
                bHasKneadWidthMinPulse = FALSE ;
                if(Input_GetKneadMin() == 0)
                {  
                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    nFinalKneadMotorState = STATE_IDLE ;
                    bkneadStep = 1;
                }                    
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
            }
            break;
            case 1:
            if(bHasKneadWidthMedPulse == TRUE)
            {
                bHasKneadWidthMedPulse = FALSE ;
                if(Input_GetKneadMid() == 0)
                {  
                    nCurKneadWidth = KNEAD_WIDTH_MED ;
                    bkneadStep = 2;
                }                    
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            }
            break;
            case 2:
            KnockSlow_Flag = 0;
            if(bHasKneadWidthMaxPulse == TRUE)
            {
                bHasKneadWidthMaxPulse = FALSE ;
                if(Input_GetKneadMax() == 0)
                {  
                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
                    nFinalKneadMotorState = STATE_IDLE ;
                    bkneadStep = 3;
                }                    
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            }
            break;
            case 3:
            if(bHasKneadWidthMedPulse == TRUE)
            {
                bHasKneadWidthMedPulse = FALSE ;
                if(Input_GetKneadMid() == 0)
                {  
                    nCurKneadWidth = KNEAD_WIDTH_MED ;
                    nFinalKneadMotorState = STATE_IDLE ;
                    CycleCount++;
                    if(CycleCount>nKneadMotorCycles)
                    {
                      bKneadMotorInProcess = FALSE ;
                      CycleCount = 0;
                    }
                    
                    bkneadStep = 0;
                }                    
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
            }
            break;
          }
          break;
            
        case KNEAD_RUN_MAX_MIN:    
            switch(bkneadStep)
            {
            default:                    //cyw
            case 0:
                upWalkRun = TRUE;
                downWalkRun = FALSE;
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;
                    if(Input_GetKneadMax() == 0)
                    {  
                        upWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        bkneadStep = 1;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            case 1:
                downWalkRun = TRUE;
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    if(Input_GetKneadMin() == 0)
                    {  
                        downWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MIN ;                  
                        CycleCount++;
                        if(CycleCount>=nKneadMotorCycles)
                        {
                            bKneadMotorInProcess = FALSE ;
                            CycleCount = 0;
                            nFinalKneadMotorState = STATE_IDLE ;
                        }
                        bkneadStep = 0;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            }
            break;
        case KNEAD_RUN_WALK:
            if(Walk_StopFlag)
            {
                bKneadMotorInProcess = FALSE ;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_IDLE ;
                bkneadTime = 0;
                bkneadTimeFlag = 0;  
                upWalkRun = 0;
                downWalkRun = 0;
                Walk_StopFlag = 0;
                bkneadStep = 0;               
                break;
            }
            switch(bkneadStep)
            {
            default:                 //cyw
            case 0: 
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
                nKneadTurn = 1;
                bkneadTimeFlag = TRUE;
                upWalkRun = TRUE;  
                downWalkRun = FALSE;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                if(bkneadTime >= 170)
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    upWalkRun = FALSE;
                    bkneadStopTimeFlag = TRUE;
                    bkneadTimeFlag = FALSE;
                    bkneadTime = 0;
                    bkneadStep = 1;
                }
                break;
            case 1:              
                downWalkRun = TRUE;
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MED ;                    
                        bkneadStep = 0;
                        downWalkRun = FALSE;          
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ; 
                    nKneadTurn = 1;
                }
                break;
            }
            
            break;
        case KNEAD_MAX_MIN://先定位到Min
            switch(bkneadStep)
            {
            default:              //cyw
            case 0:
                downWalkRun = TRUE;
                upWalkRun = FALSE;
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;
                    if(Input_GetKneadMax() == 0)
                    {  
                        downWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 1;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            case 1:
                upWalkRun = TRUE;
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    if(Input_GetKneadMin() == 0)
                    {  
                        upWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        CycleCount++;
                        if(CycleCount>=nKneadMotorCycles)
                        {
                            bKneadMotorInProcess = FALSE ;
                            CycleCount = 0;
                            nFinalKneadMotorState = STATE_IDLE ;
                        }
                        bkneadStep = 0;
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                    nKneadTurn = 2;
                }
                break;
            }
            break;
        case KNEAD_MAX_MED:
           if(Walk_StopFlag && (KneadTimesCount >= nKneadMotorCycles))
           {
             bKneadMotorInProcess = FALSE ;
             nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
             nFinalKneadMotorState = STATE_IDLE ;
             bkneadTime = 0;
             bkneadTimeFlag = 0;
             bkneadStopTime = 0;
             bkneadStopTimeFlag = 0;
             upWalkRun = 0;
             downWalkRun = 0;
             Walk_StopFlag = 0;
             bkneadStep = 0; 
             KneadTimesCount = 0;
             break;
           }
         switch(bkneadStep)
         {
           default:           //cyw
         case 0:
               bkneadTimeFlag = TRUE;
               nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
               upWalkRun = TRUE;
               downWalkRun = FALSE;  
               nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
               if(bkneadTime >= 210)
               {
                 upWalkRun = FALSE ;
                 bkneadTime = 0;
                 bkneadTimeFlag = FALSE;
                 nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                 nFinalKneadMotorState = STATE_IDLE ;                                        
                 bkneadStep = 1;   
                 Walk_CheckPoint = TRUE;  
               }
               break;
         case 1:
                downWalkRun = TRUE;
                Walk_CheckPoint = FALSE;  
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;
                    if(Input_GetKneadMax() == 0)
                    {  
                        downWalkRun = FALSE;
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 0;
                        KneadTimesCount++;                       
                    }                    
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    //downWalkRunOver = 0;
                }
                break;
            }            
            break;
        case KNEAD_MAX_MAX:
            if(Walk_StopFlag)
            {
                bKneadMotorInProcess = FALSE ;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_IDLE ;
                bkneadTime = 0;
                bkneadTimeFlag = 0;
                bkneadStopTime = 0;
                bkneadStopTimeFlag = 0;
                upWalkRun = 0;
                downWalkRun = 0;
                Walk_StopFlag = 0;
                bkneadStep = 0;
                break;
            }
            switch(bkneadStep)
            {
            default:               //cyw
            case 0:
                bkneadTimeFlag = TRUE;
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                nKneadTurn = 2;
                downWalkRun = FALSE;
                upWalkRun = TRUE;
                bkneadStep = 0;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                if(bkneadTime >= 240)
                {
                    bkneadTime = 0;
                    bkneadTimeFlag = FALSE;
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_IDLE ;   
                    bkneadStep = 1;
                    upWalkRun = FALSE;                                    
                }
                break;                             
            case 1:             
                downWalkRun = TRUE;
                upWalkRun = FALSE;
                //downWalkRunOver = 0;
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;        
                    if(Input_GetKneadMax() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 0;
                        downWalkRun = FALSE; 
                    }
                }
                
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            }            
            break;
        case KNEAD_MED_MED:
            if(Walk_StopFlag)
            {
                bKneadMotorInProcess = FALSE ;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_IDLE ;
                bkneadTime = 0;
                bkneadTimeFlag = 0;
                bkneadStopTime = 0;
                bkneadStopTimeFlag = 0;
                upWalkRun = 0;
                downWalkRun = 0;
                Walk_StopFlag = 0;
                bkneadStep = 0;
                nKneadMotorCycles = 0;
                break;
            }
            switch(bkneadStep)
            {
            default:            //cyw
            case 0:
                downWalkRun = TRUE;
                upWalkRun = FALSE;
                Walk_CheckPoint = FALSE;                     //下行时不予检测
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 1;
                        downWalkRun = FALSE;
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                    //downWalkRunOver = 0;
                }
                break;            
            case 1: 
                upWalkRun = TRUE;   
                downWalkRun = FALSE;
                bkneadTimeFlag = TRUE;
                if(bkneadTime >= 170)
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_IDLE ; 
                    upWalkRun = FALSE;
                    bkneadTime = 0;
                    bkneadStep = 0;
                    bkneadTimeFlag = FALSE;
                    Walk_CheckPoint = TRUE;            //到达揉捏最高点，可以检测行程
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                    nKneadTurn = 2;
                }
                break;
            }
            break;
        case KNEAD_MED_STOP_MED:           
            switch(bkneadStep)
            {
            default:
            case 0: 
                nFinalKneadMotorState = STATE_RUN_UNCLOCK ;
                nKneadTurn = 2;
                bkneadTimeFlag = TRUE;
                upWalkRun = TRUE;  
                downWalkRun = 0;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                if(bkneadTime >= 140)
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_IDLE ; 
                    upWalkRun = FALSE;
                    bkneadStopTimeFlag = TRUE;   
                    if(bkneadStopTime >= nKneadMotorCycles)
                    {
                        bkneadTimeFlag = FALSE;
                        bkneadTime = 0;
                        bkneadStep = 1;
                        bkneadStopTime = 0;
                        bkneadStopTimeFlag = FALSE;
                    }                    
                }
                break;
            case 1:            
                downWalkRun = TRUE;
                upWalkRun = 0;
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                        bkneadStep = 0;
                        downWalkRun = 0;
                        upWalkRun = 0;                         
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            }
            break;
        case KNEAD_TO_SIDE:
            if(_3D_Protect())//20180331 wgh
           {
              _3D_Min_Ok =1; 
           }
            switch(bkneadStep)
            {
            default:
            case 0:
                if(_3D_Min_Ok)
                {           
                    if(bHasKneadWidthMinPulse == TRUE)
                    {
                        bHasKneadWidthMinPulse = FALSE ;
                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 1;
                        Knead_Min_Ok = 1;
                    }
                    else
                    {
                        nFinalKneadMotorState = STATE_RUN_CLOCK ;
                        nKneadTurn = 1;
                        nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    }
                }
                else
                {
                    Knead_Min_Ok = 0;
                }
                break;
            case 1:
                if( _3D_Max_Ok)
                {
                    if(bHasKneadWidthMaxPulse == TRUE)
                    {
                        bHasKneadWidthMinPulse = FALSE ;
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;               
                        nFinalKneadMotorState = STATE_IDLE ;
                        bkneadStep = 0;
                        Knead_Min_Ok = 0;
                        bKneadMotorInProcess = FALSE ;
                        Knead_Min_Ok = 0;
                    }
                    else
                    {
                        nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                        nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //还未到达最窄处，继续逆时针转动
                        nKneadTurn = 2;
                        __NOP();
                    }
                    break;
                }
            }
            break;
        case KNEAD_STOP_AT_MIN:
            if(nCurKneadWidth == KNEAD_WIDTH_MIN)
            {
                Knead_InProcess(KNEAD_WIDTH_MIN,STATE_IDLE,FALSE);
                //                nFinalKneadMotorState = STATE_IDLE ;
                //                bKneadMotorInProcess = FALSE ;
                break;
            }
            
            if(bHasKneadWidthMinPulse == TRUE)
            {
                bHasKneadWidthMinPulse = FALSE ;
                if(Input_GetKneadMin() == 0)
                {
                    Knead_InProcess(KNEAD_WIDTH_MIN,STATE_IDLE,FALSE);
                    //                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    //                    nFinalKneadMotorState = STATE_IDLE ;
                    //                    bKneadMotorInProcess = FALSE ;
                }
            }
            else     Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
            //            {
            //                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            //                 __NOP();
            //                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            //            }
            
            break ;
        case KNEAD_STOP_AT_MED:
            if(nCurKneadWidth == KNEAD_WIDTH_MED)
            {
                Knead_InProcess(KNEAD_WIDTH_MED,STATE_IDLE,FALSE);
                //                nFinalKneadMotorState = STATE_IDLE ;
                //                bKneadMotorInProcess = FALSE ;
                break;
            }
            
            if(bHasKneadWidthMedPulse == TRUE)
            {
                bHasKneadWidthMedPulse = FALSE ;
                if(Input_GetKneadMid() == 0) Knead_InProcess(KNEAD_WIDTH_MED,STATE_IDLE,FALSE);
                //              {
                //                 bKneadMotorInProcess = FALSE ;
                //                  nCurKneadWidth = KNEAD_WIDTH_MED ; 
                //                  nFinalKneadMotorState = STATE_IDLE ;
                //                 
                //              }
            }
            else   Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
            //          {
            //              nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            //               __NOP();
            //              nFinalKneadMotorState = STATE_RUN_CLOCK ;
            //          }
            
            break ;
        case KNEAD_STOP_AT_MAX:
            if(nCurKneadWidth == KNEAD_WIDTH_MAX)
            {
                nFinalKneadMotorState = STATE_IDLE ;
                bKneadMotorInProcess = FALSE ;
                break;
            }
            
            if(bHasKneadWidthMaxPulse == TRUE)
            {
                bHasKneadWidthMaxPulse = FALSE ;
                if(Input_GetKneadMax() == 0) Knead_InProcess(KNEAD_WIDTH_MAX,STATE_IDLE,FALSE);
                //                    {
                //                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                //                        nFinalKneadMotorState = STATE_IDLE ;
                //                        bKneadMotorInProcess = FALSE ;
                //                    }
            }
            else  Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
            //                {
            //                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            //                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
            //                }
            break ;
            //            if(
            //               ((nCurKneadWidth == KNEAD_WIDTH_MAX)&&(nKneadMotorState==KNEAD_STOP_AT_MAX))|
            //               ((nCurKneadWidth == KNEAD_WIDTH_MIN)&&(nKneadMotorState==KNEAD_WIDTH_MIN))  |
            //               ((nCurKneadWidth == KNEAD_WIDTH_MED)&&(nKneadMotorState==KNEAD_WIDTH_MED))
            //               )
            //            {
            //                nFinalKneadMotorState = STATE_IDLE ;
            //                bKneadMotorInProcess = FALSE ;
            //            }
            //            else
            //            {
            //                if(bHasKneadWidthMaxPulse == TRUE)
            //                {
            //                    bHasKneadWidthMaxPulse = FALSE ;
            //                    
            //                    if((Input_GetKneadMax() == 0)&&(nKneadMotorState==KNEAD_STOP_AT_MAX))
            //                    {
            //                      Knead_InProcess(KNEAD_WIDTH_MAX,STATE_IDLE,FALSE);
            ////                        nCurKneadWidth = KNEAD_  WIDTH_MAX ;
            ////                        nFinalKneadMotorState = STATE_IDLE ;
            ////                        bKneadMotorInProcess = FALSE ;
            //                    }
            //                    else if((Input_GetKneadMin() == 0)&&(nKneadMotorState==KNEAD_WIDTH_MIN))
            //                    {
            //                      Knead_InProcess(KNEAD_WIDTH_MIN,STATE_IDLE,FALSE);
            ////                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
            ////                        nFinalKneadMotorState = STATE_IDLE ;
            ////                        bKneadMotorInProcess = FALSE ;
            //                    }
            //                    else if((Input_GetKneadMid() == 0)&&(nKneadMotorState==KNEAD_WIDTH_MED)) 
            //                    {
            //                     Knead_InProcess(KNEAD_WIDTH_MED,STATE_IDLE,FALSE);
            ////                        nCurKneadWidth = KNEAD_WIDTH_MED ; 
            ////                        nFinalKneadMotorState = STATE_IDLE ;
            ////                        bKneadMotorInProcess = FALSE ;
            //                    }
            //                }
            //                else
            //                {
            //                  Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
            ////                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            ////                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
            //                }
            //            }
            //            break ;
            //        case KNEAD_RUN:
            //            Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,FALSE);
            //            //            nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            //            //            nFinalKneadMotorState = STATE_RUN_CLOCK ;
            //            //            bKneadMotorInProcess = FALSE ;
            //            break ;
        case KNEAD_RUN_STOP:
        case KNEAD_RUN_STOP_AT_MIN:
            if(bHasKneadWidthMinPulse == TRUE)
            {
                bHasKneadWidthMinPulse = FALSE ;
                nCurKneadMotorCycles++ ;
                if(nCurKneadMotorCycles > nKneadMotorCycles)
                {
                    if(Input_GetKneadMin() == 0)  
                    {
                        Knead_InProcess(KNEAD_WIDTH_MIN,STATE_IDLE,FALSE);
                        //                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
                        //                        nFinalKneadMotorState = STATE_IDLE ;
                        //                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
                //                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                //                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            }
            break ;
        case KNEAD_RUN_STOP_AT_MED:
            if(bHasKneadWidthMedPulse == TRUE)
            {
                bHasKneadWidthMedPulse = FALSE ;
                nCurKneadMotorCycles++ ;
                if(nCurKneadMotorCycles > nKneadMotorCycles)
                {
                    if(Input_GetKneadMid() == 0)
                    {
                        Knead_InProcess(KNEAD_WIDTH_MED,STATE_IDLE,FALSE);
                        //                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        //                        nFinalKneadMotorState = STATE_IDLE ;
                        //                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
                //                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                //                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            }
            break ;
        case KNEAD_RUN_STOP_AT_MAX:
            if(bHasKneadWidthMaxPulse == TRUE)
            {
                bHasKneadWidthMaxPulse = FALSE ;
                nCurKneadMotorCycles++ ;
                if(nCurKneadMotorCycles > nKneadMotorCycles)
                {
                    if(Input_GetKneadMax() == 0)
                    {
                        Knead_InProcess(KNEAD_WIDTH_MAX,STATE_IDLE,FALSE);
                        //                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        //                        nFinalKneadMotorState = STATE_IDLE ;
                        //                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
                //                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                //                nFinalKneadMotorState = STATE_RUN_CLOCK ;
            }
            break ;
            //顺时针：窄-中-宽-半圈空闲-窄     
            //逆时针：宽-中-窄-半圈空闲-宽          
            /*
            搓背程序依据  nCurKneadMotorCycles的值控制揉捏电机    
            */
        case KNEAD_RUN_RUBBING:
            step = nCurKneadMotorCycles % 4;
            switch(step)
            {
            default:          //cyw
            case 0: 
                /**************判断是否到达最窄处*************************/
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    nCurKneadMotorCycles++ ;       //到达窄位置加1
                    Timer_Counter_Clear(C_TIME_RUBBING); 
                    nFinalKneadMotorState = STATE_IDLE ;
                    __NOP();
                }
                else
                {
                    Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
                    //                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    //                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //还未到达最窄处，继续逆时针转动
                }
                /*********************************************/
                break; 
            case 1:  //停在最窄处
                /**************判断刹车时间************************/
                if(Timer_Counter(C_TIME_RUBBING,1)) 
                {
                    nCurKneadMotorCycles++ ;       //加1
                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
                    nKneadTurn = 1;
                }
                else
                {
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                /*********************************************/
                break;
            case 2: 
                /**************判断是否到达最窄处*************************/
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;
                    nCurKneadWidth = KNEAD_WIDTH_MAX ;
                    nCurKneadMotorCycles++ ;       //到达宽位置加1
                    Timer_Counter_Clear(C_TIME_RUBBING); 
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从窄到宽顺时针转动
                    nKneadTurn = 1;
                }
                /*********************************************/
                break;  
            case 3: 
                /**************判断刹车时间************************/
                if(Timer_Counter(C_TIME_RUBBING,1)) 
                {
                    nCurKneadMotorCycles++ ;       //加1
                    
                    if(nCurKneadMotorCycles > nKneadMotorCycles)
                    {
                        nFinalKneadMotorState = STATE_IDLE ;
                        
                        if(bWalkMotorInProcess == FALSE)
                        {
                            bKneadMotorInProcess = FALSE ;
                        }
                    }
                    else
                    {
                        nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从最窄到最宽，进行顺时针运动 
                        nKneadTurn = 2;
                    }
                }
                else
                {
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                /*********************************************/
                break;  
            }
            
            break;
            /**********************轻柔呵护相关手法开始*****************/
        case KNEAD_WALK_MED_MED_3D_3: //先定位到MED
            //KneadFinish = FALSE;
            if((KneadTimesCount >= nKneadMotorCycles))
            {
                bKneadMotorInProcess = FALSE ;
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_IDLE ;
                bkneadTime = 0;
                bkneadTimeFlag = 0;
                bkneadStopTime = 0;
                //bkneadStopTimeFlag = 0;
                upWalkRun = 0;
                downWalkRun = 0;
                Walk_StopFlag = 0;
                bkneadStep = 0; 
                KneadTimesCount = 0;
                //KneadFinish = TRUE;
                break;
            }
            switch(bkneadStep)
            {
            default:
            case 0://由窄限位向宽限位揉捏
                //起始点 min stro
                Knead_Min_Ok = 1;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
                nKneadTurn = 1;
                nCurKneadWidth = KNEAD_WIDTH_MIN ;
                if(KneadTimesCount == 0)
                {
                    downWalkRun = TRUE;
                    upWalkRun = FALSE;
                }
                if(Input_GetKneadMid() == 0)
                { 
                    upWalkRun = TRUE ;
                    downWalkRun = FALSE;
                }
                if(Input_GetKneadMax() == 0)
                {     
                    nCurKneadWidth = KNEAD_WIDTH_MAX;
                    Knead_Min_Ok = 0;
                    Knead_Max_Ok = 1;
                    bkneadStep = 1;
                    upWalkRun = TRUE ;
                    downWalkRun = FALSE;   
                    break;
                }
                else if(nCurKneadWidth != KNEAD_WIDTH_MAX)
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            case 1:
                nCurKneadWidth = KNEAD_WIDTH_MAX ;
                bkneadTimeFlag = TRUE; 
                if(bkneadTime >= 85)
                {
                    bkneadTimeFlag = FALSE;
                    bkneadTime = 0;
                    
                    upWalkRun = FALSE; 
                    downWalkRun = TRUE;
                }
                if(Input_GetKneadMin() == 0)
                {
                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    downWalkRun = TRUE;
                    upWalkRun = FALSE;
                    Knead_Max_Ok = 0;
                    Knead_Min_Ok = 1;
                    bkneadStep = 0;
                    KneadTimesCount++;
                    break;
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                    nKneadTurn = 1;
                }
                break;
            }
            break;
            /**********************轻柔呵护相关手法结束*****************/
            //begin...MED..............................
        case KNEAD_RUN_MEDRUBBING:
            /*顺时针转动缩小，逆时针变大*************************/
            step = nCurKneadMotorCycles % 4;
            switch(step)
            {
            case 0: 
                /**************判断是否到达最窄处*************************/
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    nCurKneadWidth = KNEAD_WIDTH_MED ;
                    nCurKneadMotorCycles++ ;       //到达窄位置加1
                    Timer_Counter_Clear(C_TIME_RUBBING); 
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                else
                {
                    Knead_InProcess(KNEAD_WIDTH_UNKNOWN,STATE_RUN_CLOCK,0xff);
                    //                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    //                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //还未到达最窄处，继续逆时针转动
                }
                /*********************************************/
                break; 
            case 1:  //停在最窄处
                /**************判断刹车时间************************/
                if(Timer_Counter(C_TIME_RUBBING,1)) 
                {
                    nCurKneadMotorCycles++ ;       //加1
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从最窄到最宽，进行顺时针运动
                    nKneadTurn = 2;
                }
                else
                {
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                /*********************************************/
                break;
            case 2: 
                /**************判断是否到达最窄处*************************/
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    nCurKneadMotorCycles++ ;       //到达宽位置加1
                    Timer_Counter_Clear(C_TIME_RUBBING); 
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //从窄到宽顺时针转动
                    nKneadTurn = 2;
                    
                }
                /*********************************************/
                break;  
            case 3: //停顿 
                /**************判断刹车时间************************/
                if(Timer_Counter(C_TIME_RUBBING,1)) 
                {
                    nCurKneadMotorCycles++ ;       //加1
                    
                    if(nCurKneadMotorCycles > nKneadMotorCycles)
                    {
                        nFinalKneadMotorState = STATE_IDLE ;
                        
                        if(bWalkMotorInProcess == FALSE)
                        {
                            bKneadMotorInProcess = FALSE ;
                        }
                    }
                    else
                    {
                        nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动 
                        nKneadTurn = 1;
                    }
                }
                else
                {
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                /*********************************************/
                break;  
            }
            
            break;           
            
            //end...MED.............................             
        }
    }
    //确定揉捏马达的速度
    if((nKneadMotorState == KNEAD_STOP_AT_MIN) ||
       (nKneadMotorState == KNEAD_STOP_AT_MED) ||
           (nKneadMotorState == KNEAD_STOP_AT_MAX) ||
               (nKneadMotorState == KNEAD_RUN_STOP) )
    {
        speed =  KNEAD_SPEED2_PWM;
    }
    else if(nKneadMotorState == KNEAD_TO_SIDE)
    {
        speed =  KNEAD_SPEED3_PWM;
    }
    else
    {
        switch(nCurKneadKnockSpeed)
        {
        default:  
        case 1:speed = KNEAD_SPEED1_PWM;  break ;
        case 2:speed = KNEAD_SPEED2_PWM;  break ;
        case 3:speed = KNEAD_SPEED3_PWM;  break ;
        case 4:speed = KNEAD_SPEED4_PWM;  break ;
        case 5:speed = KNEAD_SPEED5_PWM;  break ;
        case 6:speed = KNEAD_SPEED6_PWM;  break ;
        case 7:speed = KNEAD_TEST_PWM;    break;  
        
        }
    }
    if(nFinalKneadMotorState == STATE_RUN_CLOCK)
    {
        KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,speed);
        nKneadTurn = 1;
    }
    if(nFinalKneadMotorState == STATE_RUN_UNCLOCK)
    {
        KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN,speed);
        nKneadTurn = 2;
    }
    if(nFinalKneadMotorState == STATE_IDLE)
    {
        KneadMotor_Control(STATE_KNEAD_IDLE,speed);
        nKneadTurn = 0;
    }
}
/***********************************************************************************************/
unsigned char WalkMotorControl(unsigned char nWalkMotorLocateMethod,unsigned short nWalkMotorLocateParam)
{
    //坐标更新，只有在更换动作时才执行一次
    unsigned short by_TopPosition = TOP_POSITION;
    if(bUpdateLocate == TRUE)
    {
        bUpdateLocate = FALSE ;
        //nWalkMotorLocateState = nWalkMotorLocateMethod;
        switch(nWalkMotorLocateMethod)
        {
        default:  
            bWalkMotorInProcess = FALSE ;
	    bWalkSlowFlag = 0;
            break;
        case WALK_SHOULDER_WAIST_1_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10);
            bWalkSlowFlag = 0;
            break ;
        case WALK_SHOULDER_WAIST_1_9:
            nFinalWalkMotorLocate = nShoulderPosition -3- ((nShoulderPosition - WAIST_POSITION)/10);
            bWalkSlowFlag = 0;
            break ;              
        case WALK_SHOULDER_WAIST_2_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*2);
            bWalkSlowFlag = 0;
            break ;  
        case WALK_SHOULDER_WAIST_3_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*3);
            bWalkSlowFlag = 0;
            break ;          
        case WALK_SHOULDER_WAIST_4_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*4);
            bWalkSlowFlag = 0;
            break ;               
        case WALK_SHOULDER_WAIST_5_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*5);
            bWalkSlowFlag = 0;
            break ;                    
        case WALK_SHOULDER_WAIST_6_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*6);
            bWalkSlowFlag = 0;
            break ;                       
        case WALK_SHOULDER_WAIST_7_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*7);
            bWalkSlowFlag = 0;
            break ;                       
        case WALK_SHOULDER_WAIST_8_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*8);
            //printf("8_10:%d\n\r",nFinalWalkMotorLocate);
            bWalkSlowFlag = 0;
            break ;                       
        case WALK_SHOULDER_WAIST_9_10:
            nFinalWalkMotorLocate = nShoulderPosition - ((nShoulderPosition - WAIST_POSITION)/10*9);
            //printf("9_10:%d\n\r",nFinalWalkMotorLocate);
            bWalkSlowFlag = 0;
            break ;                       
        case WALK_LOCATE_WAIST:
            nFinalWalkMotorLocate = WAIST_POSITION ;      
            //printf("W:%d\n\r",nFinalWalkMotorLocate);
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_ABSULATE:    //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ; 
            bWalkSlowFlag = 0;
            break ;
            //----------------------------------------------------    
	case WALK_LOCATE_ABSULATE_SLOW:  //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            bWalkSlowFlag = 2;      
            break ;
        case WALK_LOCATE_ABSULATE_SLOW_SLOW:  //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            bWalkSlowFlag = 3;
            break ;
        case WALK_LOCATE_ABSULATE_SLOW_SLOW_FAST:  //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            bWalkSlowFlag = 4;
            break ;
        case WALK_LOCATE_ABSULATE_SLOW_FAST:  //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            bWalkSlowFlag = 1;  
            break ;  
        case WALK_LOCATE_ABSULATE_SLOWFAST:  //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            bWalkSlowFlag = 5;
            break ;         
            //-------------------------------------------------------------  
        case WALK_LOCATE_SHOULDER:    //运行到肩膀位置
            nFinalWalkMotorLocate =  nShoulderPosition - 10;
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_SHOULDER_SLOW:       //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 2;
            break ;
        case WALK_LOCATE_SHOULDER_SLOW_FAST:       //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 1;
            break ;
        case WALK_LOCATE_SHOULDER_SLOW_SLOW:       //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 3;
            break ;
        case WALK_LOCATE_SHOULDER_SLOWFAST:       //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 5;
            break ;
        case WALK_LOCATE_SHOULDER_SLOW_SLOW_FAST:       //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 4;
            break ;    
            //----------------------------------------------------------    
        case WALK_LOCATE_TOP:  //运行到上端行程
#ifdef TOP_BY_LIMIT
            nFinalWalkMotorLocate = by_TopPosition ;
#else
            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
            {
                if(nShoulderPosition >= by_TopPosition - DEFAULT_NECK_LENGTH)
                {
                    nFinalWalkMotorLocate = by_TopPosition ;
                }
                else
                {
                    nFinalWalkMotorLocate = nShoulderPosition + DEFAULT_NECK_LENGTH ;
                }
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
#endif
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_SHOULDER_OR_ABSULATE:  //由肩部位置和绝对坐标中的较小者决定
            if(nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition ;
            }
            else
            {
                nFinalWalkMotorLocate = nWalkMotorLocateParam ;
            }
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_PARK: //停留在当前位置
            WalkMotor_Control(STATE_WALK_IDLE,0);
            nCurActionStepCounter = 0 ;
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_NeckMed: //脖子中间位置
            if(nShoulderPosition >= by_TopPosition - Med_NECK_LENGTH)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + Med_NECK_LENGTH ;
            }
            bWalkSlowFlag = 0;
            break;
        case WALK_LOCATE_NeckMed_SLOW: //脖子位置
            if(nShoulderPosition >= by_TopPosition - Med_NECK_LENGTH)
            {
		nFinalWalkMotorLocate = by_TopPosition ;
            }
            else
            {
		nFinalWalkMotorLocate = nShoulderPosition + Med_NECK_LENGTH ;
            }
            bWalkSlowFlag = 2;
            break;    
        case WALK_LOCATE_NeckMed_SLOW_SLOW: //脖子位置
            if(nShoulderPosition >= by_TopPosition - Med_NECK_LENGTH)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + Med_NECK_LENGTH ;
            }
            bWalkSlowFlag = 3;
            break;
        case WALK_LOCATE_NeckMed_SLOW_FAST: //脖子位置
            if(nShoulderPosition >= by_TopPosition - Med_NECK_LENGTH)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + Med_NECK_LENGTH ;
            }
            bWalkSlowFlag = 1;
            break;         
        case WALK_LOCATE_PressNeck: //脖子位置,靠近肩膀
            nFinalWalkMotorLocate = nShoulderPosition;	//10 ;
            bWalkSlowFlag = 0;
            break;  
            //颈部
        case WALK_LOCATE_NECK_POSITION:
            nFinalWalkMotorLocate = S_NECK_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 0;
            break ;
            //肩部
        case WALK_LOCATE_SHOULDER_POSITION:
            nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 0;
            break ;
            //背部
            /*  case WALK_LOCATE_BACK_POSITION:
            nFinalWalkMotorLocate = S_BACK_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
            nFinalWalkMotorLocate = by_TopPosition ;
        }
	    bWalkSlowFlag = 0;
            break ;*/
            //腰部
        case WALK_LOCATE_WAIST_POSITION:
            nFinalWalkMotorLocate = S_WAIST_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 0;
            break ;
        case WALK_LOCATE_BELLOW_SHOULDER:    //运行到肩膀以下
            if(nWalkMotorLocateParam < nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition - nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition / 2;
            }
            bWalkSlowFlag = 0;
            break ;    
            //-=----------------------------------------------------------------   
        case WALK_LOCATE_Ear:
            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
            {
                if(nShoulderPosition >= by_TopPosition - DEFAULT_NECK_LENGTH)
                {
                    nFinalWalkMotorLocate = by_TopPosition ;
                }
                else
                {
                    nFinalWalkMotorLocate = nShoulderPosition + DEFAULT_EAR_POSITION ;
                }
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 0;
            break;
            //==============================================================          
        case WALK_LOCATE_BACK_HIGH_POSITION:
            nFinalWalkMotorLocate = S_BACK_HIGH_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;           
        case WALK_LOCATE_BACK_POSITION:
        case WALK_LOCATE_BACK_MIDDLE_POSITION:
            nFinalWalkMotorLocate = S_BACK_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            bWalkSlowFlag = 0;
            break ;      
            //ADD WGH20170216
        case WALK_LOCATE_BACK_MIDDLE_HIGH_POSITION:
            nFinalWalkMotorLocate = S_BACK_MIDDLE_HIGH_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;
        case WALK_LOCATE_BACK_MIDDLE_LOW_POSITION:
            nFinalWalkMotorLocate = S_BACK_MIDDLE_LOW_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;
        case WALK_LOCATE_BACK_LOW_POSITION:
            nFinalWalkMotorLocate = S_BACK_LOW_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;    
        case WALK_LOCATE_SHOULDER_MIDDLE_POSITION:
            nFinalWalkMotorLocate = S_SHOULDER_MIDDLE_POSITION * nShoulderPosition / S_SHOULDER_POSITION + nWalkMotorLocateParam ;
            //防止越界
            if(nFinalWalkMotorLocate > by_TopPosition)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;   
        case WALK_ADD_PULSE:
        case WALK_DEC_PULSE:
            nFinalWalkMotorLocate = nWalkMotorLocateParam ; 
            break;
        case WALK_LOCATE_NeckMax:
            if(nShoulderPosition >= TOP_POSITION - NECKMAXPOS)
            {
                nFinalWalkMotorLocate =TOP_POSITION ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + NECKMAXPOS;
            }
            break;
        case WALK_LOCATE_Shoulder_NeckMax_1_3: 
            if(nShoulderPosition >= TOP_POSITION - NECKMAXPOS)
            {
                nFinalWalkMotorLocate = nShoulderPosition+(TOP_POSITION - (nShoulderPosition))/3;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + NECKMAXPOS/3;
            }
            break;
        case WALK_LOCATE_Shoulder_NeckMax_2_3: 
            if(nShoulderPosition >= TOP_POSITION - NECKMAXPOS)
            {
                nFinalWalkMotorLocate = nShoulderPosition+2*(TOP_POSITION - (nShoulderPosition))/3;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + 2*NECKMAXPOS/3;
            }
            break;
        case TOPMAX_POSITION:
            if(nShoulderPosition >= TOP_POSITION - NECKMAXPOS-NECKTOPPOS)
            {
                nFinalWalkMotorLocate =TOP_POSITION ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + NECKMAXPOS+NECKTOPPOS;
            }     
            break; 
        case SHOULDER_DEC_PULSE:
            nFinalWalkMotorLocate = nShoulderPosition-10-nWalkMotorLocateParam;
            break;
        case SHOULDER_ADD_PULSE:
            nFinalWalkMotorLocate = nShoulderPosition-10 + nWalkMotorLocateParam;
            break;
        case WALK_SHOULDER_WAIST_1_20:
            nFinalWalkMotorLocate =nShoulderPosition - 10 -((nShoulderPosition - 10 - WAIST_POSITION)/20);
            break;
        case WALK_SHOULDER_WAIST_3_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(3*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_5_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(5*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_7_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(7*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_9_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(9*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_11_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(11*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_13_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(13*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_15_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(15*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break;
        case WALK_SHOULDER_WAIST_17_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(17*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break; 
        case WALK_SHOULDER_WAIST_19_20:
            nFinalWalkMotorLocate = nShoulderPosition - 10 -(19*(nShoulderPosition - 10 - WAIST_POSITION)/20);
            break;
        case WALK_LOCATE_3D_PRESS:
            if(nWalkMotorLocateParam==SHOULDER_POSITION)
                nFinalWalkMotorLocate = nShoulderPosition-10;
            else
                nFinalWalkMotorLocate = nWalkMotorLocateParam;
            break;
        case STOP_WALK_KNEAD_3://轻柔呵护相关
        case STOP_WALK_KNEAD:
            nFinalWalkMotorLocate = nWalkMotorLocateParam;
            break;
        case LONG_WALK_KNEAD:
            if(nWalkMotorLocateParam==SHOULDPOS_70)
                nFinalWalkMotorLocate = nShoulderPosition - 70;
            else if(nWalkMotorLocateParam == SHOULDPOS_15)
                nFinalWalkMotorLocate = nShoulderPosition - 15;
            else
                nFinalWalkMotorLocate = nWalkMotorLocateParam;
            break;
        case PWM_ABSALUTE:
            if(nWalkMotorLocateParam == SHOULDPOS_15)
                nFinalWalkMotorLocate = nShoulderPosition-15;
            else if(nWalkMotorLocateParam == SHOULDPOS_70)
                nFinalWalkMotorLocate = nShoulderPosition-70;
            else nFinalWalkMotorLocate = nWalkMotorLocateParam;
            break; 
        }//end switch
        /*************************************************************************/   
        if(nFinalWalkMotorLocate > by_TopPosition)nFinalWalkMotorLocate = by_TopPosition;   //保证不超过最高位
    }//end if
    
    //以下判断 walk 行程（bWalkMotorInProcess）何时停止 
    switch(nWalkMotorLocateMethod)
    {
    case WALK_LOCATE_PARK:
        WalkMotor_Control(STATE_WALK_IDLE,0);
        if((nWalkMotorLocateParam != MAX_PARK_TIME) && 
           (nCurActionStepCounter >= nWalkMotorLocateParam))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case WALK_ADD_PULSE:
        if(WalkMotor_Control(WALK_UP_PULSE,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case WALK_DEC_PULSE:
        if(WalkMotor_Control(WALK_DOWN_PULSE,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case RUN_UP_DOWN:
        if(WalkMotor_Control(UP_DOWN_WALK,0))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case WALK_PWM:
        if(nWalkMotorLocateParam)
            __NOP();
        //nKneadDirection=0;
        else 
            //nKneadDirection = 1;
            if(WalkMotor_Control(PWM_WALK,0))
            {
                bWalkMotorInProcess = FALSE ;
            }
        break;
    case STOP_WALK_KNEAD:
        WalkMotor_Control(STATE_RUN_STOP_WALK_KNEAD,0);
        bWalkMotorInProcess = FALSE ;
        Walk_StopFlag = 1;
        break;
    case LONG_WALK_KNEAD:
        if(WalkMotor_Control(STATE_RUN_LONG_WALK_KNEAD,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case PWM_ABSALUTE:
        if(WalkMotor_Control(STATE_RUN_PWM_ABS,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case STATE_RUN_LOCATE_POSITION:
        if(WalkMotor_Control(STATE_RUN_WALK_LOCATE,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
    case WALK_LOCATE_3D_PRESS:
        if(WalkMotor_Control(_3D_WALK,nFinalWalkMotorLocate))
        {
            bWalkMotorInProcess = FALSE ;
        }
        break;
     /*******************轻柔呵护相关开始********************/
    case STOP_WALK_KNEAD_3:
         WalkMotor_Control(STATE_RUN_STOP_WALK_KNEAD_3,0);
         bWalkMotorInProcess = FALSE ;
         Walk_StopFlag = 1;
         break;    
     /*******************轻柔呵护相关结束********************/
    default:
        if(nFinalWalkMotorLocate == 0)  //行程最终位置为0
        {
            if(WalkMotor_Control(STATE_RUN_WALK_DOWN,0))
            {
                bWalkMotorInProcess = FALSE ;
            }
        }
        else if(nFinalWalkMotorLocate >= by_TopPosition) //行程最终位置为最高
        {
            if(WalkMotor_Control(STATE_RUN_WALK_UP,0))
            {
                bWalkMotorInProcess = FALSE ;
            }
        }
        else
        {        
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nFinalWalkMotorLocate))
            {
                bWalkMotorInProcess = FALSE ;
            }
        }
        break;
    }
    return 0;
}

/*******************************************************************************/
void startBodyDetect(void)
{
    //往上走
    nFinalWalkMotorLocate = TOP_POSITION;
    //肩部检测清空
    //bodyDetectSuccess = 0;
    //检测步骤清零
    //shoulderPositionScanStep = 0;
}
/*******************************************************************************/
void walkRefreshUp(unsigned char key)
{
  if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
    }
  if(nKeyBackLocate == LOCATE_FULL_BACK)		//全程
  {
    //nKeyBackLocate = LOCATE_FULL_BACK;
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;      
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[2].nWalkMotorLocateParam = 0 ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = 0 ;

    }
  }
  if(nKeyBackLocate == LOCATE_PARTIAL)
  {
    nKeyBackLocate = LOCATE_PARTIAL ;
    if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
    {
      nPartialTop = TOP_POSITION ;
      nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
    }
    else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
    {
      nPartialTop = PARTIAL_DIFF ;
      nPartialBottom = 0 ;
    }
    else
    {
      nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
      nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
    }
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = nPartialTop ; ;      
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = nPartialBottom ;
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = nPartialTop ; ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = nPartialBottom ;

    }
  }
  if(nKeyBackLocate == LOCATE_POINT)
  {
    nKeyBackLocate = LOCATE_POINT ;
    ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[0].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[1].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[2].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[3].nWalkMotorLocateParam = MAX_PARK_TIME ;
  }
  bBackManualModeInit = TRUE ;
}

void walkRefreshDown(unsigned char key)
{
  if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
    }
  if(nKeyBackLocate == LOCATE_FULL_BACK)		//全程
  {
   // nKeyBackLocate = LOCATE_FULL_BACK;
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = 0 ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[3].nWalkMotorLocateParam = 0 ;
    }
  }
  if(nKeyBackLocate == LOCATE_PARTIAL)
  {
   // nKeyBackLocate = LOCATE_PARTIAL ;
    if(Command_Memory_Out==0)
    {   
        if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
        {
          nPartialTop = TOP_POSITION ;
          nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
        }
        else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
        {
          nPartialTop = PARTIAL_DIFF ;
          nPartialBottom = 0 ;
        }
        else
        {
          nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
          nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
        }
    }
 
    
    
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = nPartialBottom ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[1].nWalkMotorLocateParam = nPartialTop ; ;
      ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[2].nWalkMotorLocateParam = nPartialBottom ;
      ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[3].nWalkMotorLocateParam = nPartialTop ; ;
    
  }
  if((nKeyBackLocate == LOCATE_POINT)&(Command_Memory_Out==0))
  {
    nKeyBackLocate = LOCATE_POINT ;
    ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[0].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[1].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[2].nWalkMotorLocateParam = MAX_PARK_TIME ;
    ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
    ManualDirector[3].nWalkMotorLocateParam = MAX_PARK_TIME ;
  }
  
  if((Command_Memory_Out==1)&(nKeyBackLocate == LOCATE_PARTIAL))nMaxActionStep=2;
  if((Command_Memory_Out==1)&(nKeyBackLocate == LOCATE_POINT))nMaxActionStep=5;
  bBackManualModeInit = TRUE ;
  
  
  Command_Memory_Out = 0;
}

//电机参数设置
//void refreshAutoDirector2(void)
//{
//    nCurSubFunction = AutoDirector.nSubFunction ;
//    nCurKneadKnockSpeed = AutoDirector.nKneadKnockSpeed ;
//    //设置行走电机
//    bWalkMotorInProcess = TRUE ;
//    bUpdateLocate = TRUE ;
//    nWalkMotorControlParam1 = AutoDirector.nWalkMotorLocateMethod ;
//    nWalkMotorControlParam2 = AutoDirector.nWalkMotorLocateParam ;
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = AutoDirector.nKneadMotorState ;
//    nKneadMotorControlParam2 = AutoDirector.nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = AutoDirector.nKnockMotorState ;
//    nKnockMotorControlParam2 = AutoDirector.nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = AutoDirector.nKnockMotorStopTime ;
//}
void refreshAutoDirector(void)
{
//    unsigned int position = Input_GetWalkMotorPosition();
//    nCurSubFunction = AutoDirector.nSubFunction ;
//    nCurKneadKnockSpeed = AutoDirector.nKneadKnockSpeed ;
//    //设置行走电机
//    if(nBackMainRunMode == BACK_MAIN_MODE_3D)
//    {
//        if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
//            nCurKneadKnockSpeed = 0;
//        
//        switch(nKeyBackLocate)//LOCATE_FULL_BACK:
//        {
//        case LOCATE_POINT:
//            bWalkMotorInProcess = TRUE ;
//            bUpdateLocate = TRUE ;
//            nWalkMotorControlParam1 = WALK_LOCATE_PARK ;//AutoDirector.nWalkMotorLocateMethod ;
//            nWalkMotorControlParam2 = 0;//MAX_PARK_TIME ;//AutoDirector.nWalkMotorLocateParam ; 
//            //WalkMotor_Control(STATE_WALK_IDLE,0);
//            //nCurActionStepCounter = 0 ;
//            break;
//        case LOCATE_PARTIAL:
//            if(bKeyWalkUp == TRUE)
//            {
//                bWalkMotorInProcess = TRUE ;
//                bUpdateLocate = TRUE ;
//                nWalkMotorControlParam1 = WALK_LOCATE_TOP;//WALK_LOCATE_ABSULATE ;
//                nWalkMotorControlParam2 = 0;//nPartialBottom ;
//                break;
//            }
//            if(bKeyWalkDown == TRUE)
//            {
//                bWalkMotorInProcess = TRUE ;
//                bUpdateLocate = TRUE ;
//                nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE;//WALK_LOCATE_ABSULATE ;
//                nWalkMotorControlParam2 = 0;//nPartialBottom ;
//                break;
//            }
//            /*
//            //
//            if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
//            {
//            nPartialTop = TOP_POSITION ;
//            nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
//        }
//            else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
//            {
//            nPartialTop = PARTIAL_DIFF ;
//            nPartialBottom = 0 ;
//        }
//            else
//            {
//            nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
//            nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
//        }*/
//            if(n3Dpointturn%2==0)
//            {
//                bWalkMotorInProcess = TRUE ;
//                bUpdateLocate = TRUE ;
//                nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
//                nWalkMotorControlParam2 = nPartialBottom ;
//            }
//            else
//            {
//                bWalkMotorInProcess = TRUE ;
//                bUpdateLocate = TRUE ;
//                nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
//                nWalkMotorControlParam2 = nPartialTop ;
//            }
//            break;
//        case LOCATE_FULL_BACK:
//            bWalkMotorInProcess = TRUE ;
//            bUpdateLocate = TRUE ;
//            nWalkMotorControlParam1 = AutoDirector.nWalkMotorLocateMethod ;
//            nWalkMotorControlParam2 = AutoDirector.nWalkMotorLocateParam ;
//            break;
//        }
//    }
//    else
//    {
//        bWalkMotorInProcess = TRUE ;
//        bUpdateLocate = TRUE ;
//        nWalkMotorControlParam1 = AutoDirector.nWalkMotorLocateMethod ;
//        nWalkMotorControlParam2 = AutoDirector.nWalkMotorLocateParam ;
//    }
//    
//    
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = AutoDirector.nKneadMotorState ;
//    nKneadMotorControlParam2 = AutoDirector.nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = AutoDirector.nKnockMotorState ;
//    nKnockMotorControlParam2 = AutoDirector.nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = AutoDirector.nKnockMotorStopTime ;
//    //设置3D马达力度 
//    
//    if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_POINT))
//    {
//        if(n3Dpointturn%2==0)
//        {
//            b3D_MotorInProcess = TRUE ;
//            n3D_MotorControlState = _3D_PROGRAM;//AutoDirector.n3D_MotorState ;
//            n3D_MotorControlPosition = AXIS_STRONGEST;//AutoDirector.n3D_MotorPosition ;
//            nSetAxisStrength = n3D_MotorControlPosition;
//            bAxisUpdate = true; 
//            n3D_MotorControlSpeed = _3D_SPEED_5;//AutoDirector.n3D_MotorSpeed ;
//            n3D_MotorControlStopTime = 20;//AutoDirector.n3D_MotorStopTime ;         
//            
//        }
//        else
//        {
//            b3D_MotorInProcess = TRUE ;
//            n3D_MotorControlState = _3D_PROGRAM;//AutoDirector.n3D_MotorState ;
//            n3D_MotorControlPosition = AXIS_WEAKEST;//AutoDirector.n3D_MotorPosition ;
//            nSetAxisStrength = n3D_MotorControlPosition;
//            bAxisUpdate = true; 
//            n3D_MotorControlSpeed = _3D_SPEED_5;//AutoDirector.n3D_MotorSpeed ;
//            n3D_MotorControlStopTime = 20;//AutoDirector.n3D_MotorStopTime ;    
//            
//        }
//        
//    }
//    else
//    {
//        b3D_MotorInProcess = TRUE ;
//        n3D_MotorControlState = AutoDirector.n3D_MotorState ;
//        n3D_MotorControlPosition = AutoDirector.n3D_MotorPosition ;
//        nSetAxisStrength = n3D_MotorControlPosition;
//        bAxisUpdate = true; 
//        n3D_MotorControlSpeed = AutoDirector.n3D_MotorSpeed ;
//        n3D_MotorControlStopTime = AutoDirector.n3D_MotorStopTime ;      
//    }
    nCurSubFunction = AutoDirector.nSubFunction ;
    nCurKneadKnockSpeed = AutoDirector.nKneadKnockSpeed ;
    //设置行走电机
    bWalkMotorInProcess = TRUE ;
    bUpdateLocate = TRUE ;
    nWalkMotorControlParam1 = AutoDirector.nWalkMotorLocateMethod ;
    nWalkMotorControlParam2 = AutoDirector.nWalkMotorLocateParam ;
    //设置揉捏电机
    bKneadMotorInProcess = TRUE ;
    nKneadMotorControlParam1 = AutoDirector.nKneadMotorState ;
    nKneadMotorControlParam2 = AutoDirector.nKneadMotorCycles ;
    //设置捶击电机
    bKnockMotorInProcess = TRUE ;
    nKnockMotorControlParam1 = AutoDirector.nKnockMotorState ;
    nKnockMotorControlParam2 = AutoDirector.nKnockMotorRunTime ;
    nKnockMotorControlParam3 = AutoDirector.nKnockMotorStopTime ;
    //设置3D马达力度 
    b3D_MotorInProcess = TRUE ;
    n3D_MotorControlState = AutoDirector.n3D_MotorState ;
    n3D_MotorControlPosition = AutoDirector.n3D_MotorPosition ;
    nSetAxisStrength = n3D_MotorControlPosition;
    bAxisUpdate = true; 
    n3D_MotorControlSpeed = AutoDirector.n3D_MotorSpeed ;
    n3D_MotorControlStopTime = AutoDirector.n3D_MotorStopTime ;
    
    /*********************Tapping OFF功能设置开始****************/
    if((bTapping ==1)&&((AutoDirector.nSubFunction == BACK_SUB_MODE_SOFT_KNOCK)||(AutoDirector.nSubFunction == BACK_SUB_MODE_KNOCK)))
    {
        if(AutoDirector.nWalkMotorLocateMethod == WALK_LOCATE_PARK)
        {
            bKnockMotorInProcess = TRUE ;
            nKnockMotorControlParam1 = 0 ;
            nKnockMotorControlParam2 = 0 ;
            nKnockMotorControlParam3 = 0 ;
            nCurSubFunction = BACK_SUB_MODE_PRESS;
            nCurKneadKnockSpeed = 0 ;
            
            b3D_MotorInProcess = TRUE;
            n3D_MotorControlState =_3D_WORK_CIRCLE;
            n3D_MotorControlPosition = 0 ;
            n3D_MotorControlSpeed =  _3D_SPEED_3;
            n3D_MotorControlStopTime = 0 ;
            
            bTapping_old = TRUE;
        }
        else
        {
            bKnockMotorInProcess = TRUE ;
            nKnockMotorControlParam1 = 0 ;
            nKnockMotorControlParam2 = 0 ;
            nKnockMotorControlParam3 = 0 ;
            nCurSubFunction = BACK_SUB_MODE_PRESS;
            nCurKneadKnockSpeed = 0 ;
            
            bTapping_old = TRUE;
        }
    }
    else if((bTapping ==1)&&(AutoDirector.nSubFunction == BACK_SUB_MODE_WAVELET))
    {
         bKnockMotorInProcess = TRUE ;
         nKnockMotorControlParam1 = 0 ;
         nKnockMotorControlParam2 = 0 ;
         nKnockMotorControlParam3 = 0 ;
         nCurSubFunction = BACK_SUB_MODE_KNEAD;
         
         bTapping_old = TRUE;
    }
    /*********************Tapping OFF功能设置结束****************/ 
}

//--------------------------------------------------------------------------
//3个自动程序区域
//------------------------------------------
// massage_step_tm           // 60 s 一次 by_Time30s                   // 30s 一次
// massage_step_tm_flag    // by_Time30s 到了后,被设置为1.
// by_moni_cmd_tm   		// 模拟命令的长度 2s  . 每100ms 减一次。 set_moni_cmd_tm中设置20.
// by_moni_cmd_tm_en 	// 模拟命令是否有效。
void focredFinisih(void)
{
    bWalkMotorInProcess = FALSE;
    bKneadMotorInProcess = FALSE;
    bKnockMotorInProcess = FALSE;
    b3D_MotorInProcess = FALSE ;
    
}
/******************************************************************************/
void Examinee_Mode_Massage_Pointer_Control_Start(void)
{
  n_Examinee_Pointer = 0;			
  n_Examinee_Steps = 1;
  // 60 秒一次.
  Clr_Massage_Step_Timer();
  massage_step_tm_flag = 1;////一分钟时间标志位	
  return;
}
/******************************************************************************/
void  open_auto_back_down2s(void)
{

  // 开2s
    Set_Moni_cmd_tm(20); 
    st_Stretch.active = FALSE;
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = TRUE ;
    //小腿联动设置
    bKeyLegPadDown = FALSE ;
    bKeyLegPadUp = TRUE ;
    bLegPadLinkage = TRUE ;
    return;
}
/******************************************************************************/
void  close_auto_back_down(void)
{
    st_Stretch.active = FALSE;
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    //小腿联动设置
    bKeyLegPadDown = FALSE ;
    bKeyLegPadUp = FALSE ;
    bLegPadLinkage = TRUE ;
    return;
}
/******************************************************************************/
//void Examinee_Mode_Massage_Pointer_Control_Proc(void)
//{
//   if((by_moni_cmd_tm == 1)&&(bShoulderOK == TRUE)&&
//      (nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&
//      (nBackSubRunMode == BACK_SUB_MODE_AUTO_6) 
//      )
//   {
//      by_moni_cmd_tm = 0;//// 模拟命令的长度 2s  . 每100ms 减一次。 set_moni_cmd_tm中设置20.
//      close_auto_back_down();
//   } 
//  if((0 != massage_step_tm_flag)&&(bShoulderOK == TRUE)&&
//  	(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&(nBackSubRunMode == BACK_SUB_MODE_AUTO_6) )
//  {
//	massage_step_tm_flag = 0;
//	Clr_Massage_Step_Timer();//第一次按开始键体型检测结速后开始运行数组，大致时间为第19分钟开始运行  step=0
//	switch(n_Examinee_Steps)
//	{
//
//		case 0:
//			//循环
//			n_Examinee_Steps =0;
//			n_Examinee_Pointer = 0;			
//			break;
//
//		case 1:
//			// 第1  分钟
//			n_Examinee_Pointer = 1;
//			n_Examinee_Steps =2;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;//nCurActionStep为当前步数 ，当程序运行到进入Main_BackProc，还要++一步
//			// 进入Main_BackProc ,还要++;
//			break;
//
//		case 2:
//			// 第2  分钟			
//			n_Examinee_Pointer = 18;			
//			n_Examinee_Steps =3;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//
//                    //nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
//                    //bMassagePositionUpdate = TRUE;
//			break;
//
//		case 3:
//			// 第3 ,4  分钟			
//			n_Examinee_Pointer = 40;			
//			n_Examinee_Steps =4;	
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//
//                    //nTargetMassagePosition = MASSAGE_MAX_POSITION;
//                    //bMassagePositionUpdate = TRUE;
//			
//			break;
//
//		case 4:
//
//			n_Examinee_Pointer = 0; //0表示不理财			
//			n_Examinee_Steps =5;		
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 5:
//			// 第5  分钟			
//			n_Examinee_Pointer = 64;			
//			n_Examinee_Steps =6;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//                    /*
//			{
//			Set_Moni_cmd_tm(20) ; //20 * 0.1 = 2s
//			// 自动倒
//	                  st_Stretch.active = FALSE;
//	                  bKeyBackPadUp = FALSE ;
//	                  bKeyBackPadDown = TRUE ;
//	                  //小腿联动设置
//	                  bKeyLegPadDown = FALSE ;
//	                  bKeyLegPadUp = TRUE ;
//	                  bLegPadLinkage = TRUE ;
//	                  bKeyFlexOut = FALSE ;
//	                  bKeyFlexIn = FALSE ;			
//			}
//                    */
//             
//			break;
//
//		case 6:
//			// 第6  分钟			
//			n_Examinee_Pointer = 82;			
//			n_Examinee_Steps =7;			
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//             //----------------------------------------
//             // 往后延时30s
//             //if(1 == by_moni_cmd_tm_en) open_auto_back_down2s();
//			
//			break;
//
//		case 7:
//			// 第7  分钟			
//			n_Examinee_Pointer = 100;			
//			n_Examinee_Steps =8;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 8:
//			// 第8  分钟			
//			n_Examinee_Pointer = 118;			
//			n_Examinee_Steps =9;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 9:
//			// 第9 ,10 分钟			
//			n_Examinee_Pointer = 130;			
//			n_Examinee_Steps =10;			
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 10:
//
//			n_Examinee_Pointer = 0;	//0表示不理财				
//			n_Examinee_Steps =11;			
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//						
//			break;
//
//		case 11:
//			// 第11 分钟
//			n_Examinee_Pointer = 158;			
//			n_Examinee_Steps =12;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//            //------------------------------------
//            //if(1 == by_moni_cmd_tm_en) open_auto_back_down2s();
//			
//			break;
//
//		case 12:
//			// 第12 ,13 分钟
//			n_Examinee_Pointer = 169;			
//			n_Examinee_Steps =13;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//		case 13:
//
//			n_Examinee_Pointer = 0;	//0表示不理财				
//			n_Examinee_Steps =14;
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//		case 14:
//			// 第14 ,15分钟
//			n_Examinee_Pointer = 193;			
//			n_Examinee_Steps =15;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//		case 15:
//
//			n_Examinee_Pointer = 0;	//0表示不理财				
//			n_Examinee_Steps =16;
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 16:
//			// 第16 分钟
//			n_Examinee_Pointer = 211;			
//			n_Examinee_Steps =17;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//
//			
//			break;
//
//		case 17:
//			// 第17 分钟
//			n_Examinee_Pointer = 222;	//0表示不理财				
//			n_Examinee_Steps =18;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//		case 18:
//			// 第18 ,19 分钟			
//			n_Examinee_Pointer = 232;			
//			n_Examinee_Steps =19;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//		case 19:
//
//			n_Examinee_Pointer = 0;		//0表示不理财			
//			n_Examinee_Steps =20;
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//
//			
//			break;
//
//		case 20:
//			// 第20 分钟			
//			n_Examinee_Pointer = 0;		//0表示不理财			
//			n_Examinee_Steps =21;
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			
//			break;
//
//			//-----------------------------------------------------
//			//   修正30分钟时模式不准。
//		case 21:
//			// 第1  分钟
//			n_Examinee_Pointer = 1;
//			n_Examinee_Steps =22;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;						
//			break;
//
//		case 22:
//			// 第2  分钟			
//			n_Examinee_Pointer = 18;			
//			n_Examinee_Steps =23;
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 23:
//			// 第3 ,4  分钟			
//			n_Examinee_Pointer = 40;			
//			n_Examinee_Steps =24;	
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 24:
//
//			n_Examinee_Pointer = 0; //0表示不理财			
//			n_Examinee_Steps =25;		
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 25:
//			// 第5  分钟			
//			n_Examinee_Pointer = 64;			
//			n_Examinee_Steps =26;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//
//			break;
//
//		case 26:
//			// 第6  分钟			
//			n_Examinee_Pointer = 82;			
//			n_Examinee_Steps =27;			
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 27:
//			// 第7  分钟			
//			n_Examinee_Pointer = 100;			
//			n_Examinee_Steps =28;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 28:
//			// 第8  分钟			
//			n_Examinee_Pointer = 118;			
//			n_Examinee_Steps =29;		
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 29:
//			// 第9 ,10 分钟			
//			n_Examinee_Pointer = 130;			
//			n_Examinee_Steps =30;			
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//			
//			break;
//
//		case 30:
//
//			n_Examinee_Pointer = 0;	//0表示不理财				
//			n_Examinee_Steps =31;			
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_Examinee_Pointer - 1;
//			// 进入Main_BackProc ,还要++;
//                    //------------------------------------
//                        
//			break;
//
//
//		default:	
//			n_Examinee_Pointer = 0;		//0表示不理财						
//			break;
//	}
//	
//    }
//    return;
//}

/*****************************************************************************/
////high up 
//void HipUp_Mode_Massage_Pointer_Control_Start(void)
//{
//
//	n_HipUp_Steps = 1;
//	n_HipUp_Pointer = 0;			
//	Clr_Massage_Step_Timer();
//	//	
//	massage_step_tm_flag = 1;
//	return;
//}
//
//
//// 第5 ，第10 分倒
//void HipUp_Mode_Massage_Pointer_Control_Proc(void)
//{
//  
//  
//     if((by_moni_cmd_tm == 1)&&(bShoulderOK == TRUE)&&
//  	(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) )
//   {
//		by_moni_cmd_tm = 0;
//		//
//		// 关
//                close_auto_back_down();
//
//   } 
//
//  
//  
//  //------------------------------------------------------
//  
//
//  if((0 != massage_step_tm_flag)&&(bShoulderOK == TRUE)&&
//  	(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) )
//  {
//	massage_step_tm_flag = 0;
//	Clr_Massage_Step_Timer();
//	//
//	switch(n_HipUp_Steps)
//	{
//
//		case 0:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =0;
//			break;
//
//		case 1:
//			n_HipUp_Pointer = 1;
//			n_HipUp_Steps =2;
//			// 第1  分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 2:
//			n_HipUp_Pointer = 11;			
//			n_HipUp_Steps =3;
//			// 第2, 3 分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 3:
//			n_HipUp_Pointer = 0;
//			n_HipUp_Steps =4;			
//			// 第3 钟
//			break;
//
//		case 4:
//			n_HipUp_Pointer = 39;	//		
//			n_HipUp_Steps =5;			
//			// 第4  分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 5:
//			n_HipUp_Pointer = 49;			
//			n_HipUp_Steps =6;		
//			// 第5 ,6 分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//                        
//			break;
//
//		case 6:
//			n_HipUp_Pointer = 0;
//			n_HipUp_Steps =7;			
//			// 第6  分钟
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;	
//            //--------------------------------------------------
//            //if(1 == by_moni_cmd_tm_en) open_auto_back_down2s();                        
//			
//			break;
//
//		case 7:			
//			n_HipUp_Pointer = 61;			
//			n_HipUp_Steps =8;			
//			// 第7 ,8  ,9分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 8:			
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =9;			
//			// 第8  分钟
//			break;
//
//		case 9:			
//			n_HipUp_Pointer =0;			
//			n_HipUp_Steps =10;			
//			// 第9  分钟
//			break;
//
//		case 10:
//			n_HipUp_Pointer = 85;	//		
//			n_HipUp_Steps =11;			
//			// 第10  11 12分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;		
//                        
//			break;
//
//		case 11:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =12;
//			// 第11  分钟
//            //--------------------------------------------------
//            //if(1 == by_moni_cmd_tm_en) open_auto_back_down2s();      
//			
//			break;
//
//		case 12:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =13;
//			// 第12  分钟
//			break;
//
//		case 13:
//			n_HipUp_Pointer = 113;	//		
//			n_HipUp_Steps =14;
//			// 第13  14  15 分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;						
//			break;
//
//		case 14:
//			n_HipUp_Pointer = 0;
//			n_HipUp_Steps =15;
//			// 第14,15  分钟
//
//			break;
//
//		case 15:
//			n_HipUp_Pointer = 0;	//		
//			n_HipUp_Steps =16;
//			// 第15  分钟
//
//			break;
//
//		case 16:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =17;
//			// 第16,17  分钟
//
//			break;
//
//		case 17:
//			n_HipUp_Pointer = 0;	//		
//			n_HipUp_Steps =18;
//			// 第17  分钟
//
//			break;
//
//		case 18:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =19;
//			// 第18  分钟
//
//			break;
//
//		case 19:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =20;
//			// 第19  分钟
//
//			break;
//
//		case 20:
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =21;
//			// 第20  分钟
//
//			break;
//
//           //-----------------------------------------------------------
//
//		case 21:
//			n_HipUp_Pointer = 1;
//			n_HipUp_Steps =22;
//			// 第1  分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 22:
//			n_HipUp_Pointer = 11;			
//			n_HipUp_Steps =23;
//			// 第2, 3 分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 23:
//			n_HipUp_Pointer = 0;
//			n_HipUp_Steps =24;			
//			// 第3 钟
//			break;
//
//		case 24:
//			n_HipUp_Pointer = 39;	//		
//			n_HipUp_Steps =25;			
//			// 第4  分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 25:
//			n_HipUp_Pointer = 49;			
//			n_HipUp_Steps =26;		
//			// 第5 ,6 分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			                        
//                        
//			break;
//
//		case 26:
//			n_HipUp_Pointer = 0;
//			n_HipUp_Steps =27;			
//			// 第6  分钟
//                    //
//			//focredFinisih(); 					
//			//nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 27:			
//			n_HipUp_Pointer = 61;			
//			n_HipUp_Steps =28;			
//			// 第7 ,8  ,9分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;			
//			break;
//
//		case 28:			
//			n_HipUp_Pointer = 0;			
//			n_HipUp_Steps =29;			
//			// 第8  分钟
//			break;
//
//		case 29:			
//			n_HipUp_Pointer =0;			
//			n_HipUp_Steps =30;			
//			// 第9  分钟
//			break;
//
//		case 30:
//			n_HipUp_Pointer = 85;	//		
//			n_HipUp_Steps =31;			
//			// 第10  11 12分钟
//                    //
//			focredFinisih(); 					
//			nCurActionStep = n_HipUp_Pointer - 1;
//			// 进入Main_BackProc ,还要++;		
//                    //--------------------------------------------------                        
//			break;
//
//		default:	
//			break;
//			
//
//	}
//	
//    }
//    return;
//
//}


void Golf_Mode_Massage_Pointer_Control_Start(void)
{

	n_Golfer_Pointer = 0;			
	n_Golfer_Steps = 1;
	Clr_Massage_Step_Timer();
	//	
	massage_step_tm_flag = 1;
	return;

}
/******************************************************************************/
//void Golf_Mode_Massage_Pointer_Control_Proc(void)
//{
// 
//    //
//  if((0 != massage_step_tm_flag)&&(bShoulderOK == TRUE)&&
//  	(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&(nBackSubRunMode == BACK_SUB_MODE_AUTO_8) )
//  {
//	massage_step_tm_flag = 0;
//	Clr_Massage_Step_Timer();
//	//
//        
//      //
//	switch(n_Golfer_Steps)
//	{
//
//		case 0:
//			n_Golfer_Steps =0;
//			n_Golfer_Pointer = 0;			
//			break;
//
//		case 1:
//			n_Golfer_Pointer = 1;
//			n_Golfer_Steps =2;
//			// 第1  分钟
//            //
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//
//			break;
//
//		case 2:
//			n_Golfer_Pointer = 16;			
//			n_Golfer_Steps =3;
//			// 第2  ,3 分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 3:
//			n_Golfer_Pointer = 0;//			
//			n_Golfer_Steps =4;	
//			// 3分钟
//			break;
//
//		case 4:
//			n_Golfer_Pointer = 40;			
//			n_Golfer_Steps =5;			
//			// 第4  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 5:
//			n_Golfer_Pointer = 57;			
//			n_Golfer_Steps =6;		
//
//			// 第5  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//
//			break;
//
//		case 6:
//			n_Golfer_Pointer = 71;			
//			n_Golfer_Steps =7;	
//			// 第6  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 7:
//			
//			n_Golfer_Pointer = 85;			
//			n_Golfer_Steps =8;		
//			// 第7  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 8:
//			
//			n_Golfer_Pointer = 95;			
//			n_Golfer_Steps =9;			
//			// 第8  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 9:
//			
//			n_Golfer_Pointer = 105;			
//			n_Golfer_Steps =10;			
//
//			// 第9 -15 分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 10:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =11;			
//			// 第10  分钟			
//			//
//			
//			break;
//
//		case 11:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =12;
//			// 第11 分钟			
//			//			
//			
//			break;
//
//		case 12:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =13;
//			// 第12 分钟			
//			//			
//			
//			break;
//
//		case 13:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =14;
//			// 第13 分钟			
//			//			
//			
//			break;
//
//		case 14:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =15;
//			// 第14 分钟			
//			//			
//
//			
//			break;
//
//		case 15:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =16;
//
//			// 第15 分钟			
//			//			
//
//			
//			break;
//
//		case 16:
//
//			n_Golfer_Pointer = 181;			
//			n_Golfer_Steps =17;
//			// 第16  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			
//			break;
//
//		case 17:
//
//			n_Golfer_Pointer = 196;			
//			n_Golfer_Steps =18;
//
//			// 第17  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			
//			break;
//
//		case 18:
//			n_Golfer_Pointer = 210;		//	
//			n_Golfer_Steps =19;
//			// 第18  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//
//			break;
//
//		case 19:
//			n_Golfer_Pointer = 222;			
//			n_Golfer_Steps =20;
//
//			// 第19  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 20:
//			n_Golfer_Pointer = 236;			
//			n_Golfer_Steps =21;
//			
//			break;
//
//		//---------------------------------------------------			
//		case 21:
//			n_Golfer_Pointer = 1;
//			n_Golfer_Steps =22;
//			// 第1  分钟
//            		//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			//
//			break;
//
//		case 22:
//			n_Golfer_Pointer = 16;			
//			n_Golfer_Steps =23;
//			// 第2  ,3 分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 23:
//			n_Golfer_Pointer = 0;//			
//			n_Golfer_Steps =24;	
//			// 3分钟
//			break;
//
//		case 24:
//			n_Golfer_Pointer = 40;			
//			n_Golfer_Steps =25;			
//			// 第4  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 25:
//			n_Golfer_Pointer = 57;			
//			n_Golfer_Steps =26;		
//
//			// 第5  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//
//			break;
//
//		case 26:
//			n_Golfer_Pointer = 71;			
//			n_Golfer_Steps =27;	
//			// 第6  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 27:
//			
//			n_Golfer_Pointer = 85;			
//			n_Golfer_Steps =28;		
//			// 第7  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 28:
//			
//			n_Golfer_Pointer = 95;			
//			n_Golfer_Steps =29;			
//			// 第8  分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 29:
//			
//			n_Golfer_Pointer = 105;			
//			n_Golfer_Steps =30;			
//
//			// 第9 -15 分钟			
//			//
//			focredFinisih(); 					
//			nCurActionStep = n_Golfer_Pointer - 1;
//			
//			break;
//
//		case 30:
//
//			n_Golfer_Pointer = 0;			
//			n_Golfer_Steps =31;			
//			// 第10  分钟			
//			//
//			
//			break;
//			
//
//		default:	
//			break;
//			
//
//	}
//	
//    }
//    return;
//}
//----------------------------------------------------------------------------


void Wrick_Mode_Massage_Pointer_Control_Start(void)
{

	n_Wrick_Pointer = 0;			
	n_Wrick_Steps = 1;
	Clr_Massage_Step_Timer();
	//	
	massage_step_tm_flag = 1;
	return;

}

/******************************************************************************/
//void Wrick_Mode_Massage_Pointer_Control_Proc(void)
//{
//  if((0 != massage_step_tm_flag)&&(bShoulderOK == TRUE == TRUE)&& \
//  	(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&(nBackSubRunMode == BACK_SUB_MODE_AUTO_9) )
//  {
//	massage_step_tm_flag = 0;
//	Clr_Massage_Step_Timer();
//	//
//        
//      //
//	switch(n_Wrick_Steps)
//	{
//
//		case 0:
//			n_Wrick_Steps =0;
//			n_Wrick_Pointer = 0;			
//			break;
//
//		case 1:
//			n_Wrick_Pointer = 1;
//			n_Wrick_Steps =2;
//			// 第1  分钟
//            //
//			focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;
//			
//			break;
//
//		case 2:
//			n_Wrick_Pointer = 0;//16	
//			n_Wrick_Steps =3;
//			
//			
//			break;
//
//		case 3:
//			n_Wrick_Pointer = 0;//			
//			n_Wrick_Steps =4;	
//                       
//			// 3分钟
//			break;
//
//		case 4:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =5;			
//			
//			break;
//
//		case 5:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =6;		
//
//			break;
//
//		case 6:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =7;	
//                        
//			/*focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;*/
//			break;
//
//		case 7:
//			
//			n_Wrick_Pointer =0;			
//			n_Wrick_Steps =8;		
//			// 第7  分钟			
//			
//			break;
//
//		case 8:
//			
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =9;			
//			
//			
//			break;
//
//		case 9:
//			
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =10;			
//
//			
//			
//			break;
//
//		case 10:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =11;			
//			/*//			
//			focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;
//			break;*/
//			break;
//
//		case 11:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =12;
//			// 第11 分钟			
//			
//
//		case 12:
//
//			n_Wrick_Pointer = 0;//75;			
//			n_Wrick_Steps =13;
//			// 第13 分钟			
//			//			
//			/*focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;
//			break;
//			break;*/
//
//		case 13:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =14;
//			
//
//		case 14:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =15;
//			
//			
//			break;
//
//		case 15:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =16;
//
//			
//			break;
//
//		case 16:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =17;
//			
//			
//			
//			break;
//
//		case 17:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =18;
//
//			
//			break;
//
//		case 18:
//			n_Wrick_Pointer = 0;		//	
//			n_Wrick_Steps =19;
//			//
//			
//
//			break;
//
//		case 19:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =20;
//
//			// 第19  分钟		
//                       /* focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;*/
//			
//                        
//			
//			break;
//
//		case 20:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =21;
//			
//			break;
//
//		//---------------------------------------------------			
//		case 21:
//			n_Wrick_Pointer = 0;
//			n_Wrick_Steps =22;
//			// 第1  分钟
//            		//
//			
//			//
//			break;
//
//		case 22:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =23;
//			
//			
//			break;
//
//		case 23:
//			n_Wrick_Pointer = 0;//			
//			n_Wrick_Steps =24;	
//			// 3分钟
//                        
//			break;
//
//		case 24:
//			n_Wrick_Pointer = 1;			
//			n_Wrick_Steps =25;			
//			// 第4  分钟			
//			focredFinisih(); 					
//			nCurActionStep = n_Wrick_Pointer - 1;
//			break;
//
//		case 25:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =26;		
//
//			
//
//			break;
//
//		case 26:
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =27;	
//			
//			
//			break;
//
//		case 27:
//			
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =28;		
//			
//			break;
//
//		case 28:
//			
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =29;			
//			
//			
//			break;
//
//		case 29:
//			
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =30;			
//
//				
//			
//			
//			break;
//
//		case 30:
//
//			n_Wrick_Pointer = 0;			
//			n_Wrick_Steps =31;			
//			// 第10  分钟			
//			//
//			
//			break;
//			
//
//		default:	
//			break;
//			
//
//	}
//	
//    }
//    return;
//
//}


//----------------------------------------------------------------------------
//
unsigned int wghrestsleep;
unsigned char RestSleepStep;
void Valve_RestSleepControlProce(void)
{
    // bool bStatus;
    // bool bBACKStatus;
    //int legFlag,BackFlag;//,SlideFlag;
    //unsigned int p_BackLocation;
    
    
    
    unsigned int Minutes;
    if(!st_RestSleep.active) 
    {
        unsigned int RunTime = Data_Get_TimeSecond();   
        //if(RunTime%60 != 0)  return; //0秒开始SLEEP
        Minutes = RunTime/60; //获取当前分钟数
        
        if((Minutes == 30) &&(RunTime%60 == 0))
        {
            st_RestSleep.step = 0;
            st_RestSleep.active = TRUE;
            st_RestSleep.init = TRUE; 
        }
        if((Minutes == 20)&&(RunTime%60 == 0))
        {
            st_RestSleep.step = 1;bBackAutoModeInit = TRUE;
            st_RestSleep.active = TRUE;
            st_RestSleep.init = TRUE; 
            
            
        }
        if((Minutes == 10) &&(RunTime%60 == 0))
        {
            st_RestSleep.step = 2;bBackAutoModeInit = TRUE;
            st_RestSleep.active = TRUE;
            st_RestSleep.init = TRUE; 
            
        }
        
    }
    
    if(st_RestSleep.active)
    {
        //nStretchStep = 0;
        //st_RestSleep.step = 0;
        //st_RestSleep.timer = 0;
        st_RestSleep.active = FALSE;
    }
    
    
    //RestSleepStep =0;
    wghrestsleep = Data_Get_TimeSecond();
    
    switch(st_RestSleep.step)//RestSleepStep
        
    {
    case 0:
        if(st_RestSleep.init == TRUE)
        {
            nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION; 
            bMassagePositionUpdate = TRUE; 
            st_RestSleep.init = FALSE; 
        }
        break;
    case 1:
        if(st_RestSleep.init == TRUE)
        {
            nTargetMassagePosition = MASSAGE_OPTIMAL_MED_POSITION; 
            bMassagePositionUpdate = TRUE;  
            st_RestSleep.init = FALSE; 
        }
        break;
        
    case 2:
        if(st_RestSleep.init == TRUE)
        {
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION; 
            bMassagePositionUpdate = TRUE; 
            st_RestSleep.init = FALSE; 
        }
        break;
        
    }
    
}


void Main_BackProce(void)
{    
    if(st_Stretch.active)
    {
        return;
    }
    switch(nBackMainRunMode)
    {
    case BACK_MAIN_MODE_DEMO:  
        if(bBackAutoModeInit == TRUE)
        {
            bBackAutoModeInit = FALSE;
            nMaxActionStep = BACK_AUTO_STEPS[14];
            nStartActionStep = BACK_AUTO_START_STEP[14];
            bGetNextActionStep = TRUE;
            nCurActionStep = 0;
            nStretchStep = 0;
        }
        else
        {
            if((bWalkMotorInProcess == FALSE) &&
               (bKneadMotorInProcess == FALSE) &&
                   (bKnockMotorInProcess == FALSE)&&
                       (b3D_MotorInProcess == FALSE))
            {
                nCurActionStep++ ; //自动程序步骤增加
                if(nCurActionStep >= nMaxActionStep)
                {
                    nCurActionStep = nStartActionStep ;
                }
                bGetNextActionStep = TRUE ;
            }
        }
        if(bGetNextActionStep == TRUE)
        {
            bGetNextActionStep = FALSE ;
            switch(nBackSubRunMode)
            {
            case BACK_SUB_MODE_AUTO_0:
                AutoDirector = AutoFunction0[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_AUTO_1:
                AutoDirector = AutoFunction1[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_AUTO_2:
                AutoDirector = AutoFunction2[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_AUTO_3:
                AutoDirector = AutoFunction3[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_AUTO_4:
                AutoDirector = AutoFunction4[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_AUTO_5:
                AutoDirector = AutoFunction5[nCurActionStep] ;
                break;
            case BACK_SUB_MODE_3D1:
                AutoDirector = _3DFunction0[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_3D2:
                AutoDirector = _3DFunction1[nCurActionStep] ;
                break ;
            case BACK_SUB_MODE_3D3:
                AutoDirector = _3DFunction2[nCurActionStep] ;
                break ;   
            case BACK_SUB_MODE_DEMO:
                AutoDirector = DemoFunction[nCurActionStep] ;
                break ;       
            }
            //每次更换动作需要更新的变量
            nCurActionStepCounter = 0 ;//当前动作时间计数（行走或敲击时间计数）
            nCurShoulderAdjustCounter = 0 ;
            if(!((nCurSubFunction == BACK_SUB_MODE_SOFT_KNOCK) && (AutoDirector.nSubFunction == BACK_SUB_MODE_SOFT_KNOCK)))
            {
                nCurKnockRunStopCounter = 0 ;//叩击动作记数器
            }
            nCurKneadMotorCycles = 0 ;//揉捏圈数计数（揉捏）
            refreshAutoDirector();
        }
        break;
    case BACK_MAIN_MODE_AUTO:
    case BACK_MAIN_MODE_3D:    
        if(bBackAutoModeInit == TRUE)
        {
            bBackAutoModeInit = FALSE;
            nStartActionStep = BACK_AUTO_START_STEP[nBackSubRunMode] ;
            bGetNextActionStep = TRUE ;
            nCurActionStep = 0 ;
            nStretchStep = 0;
            nCur3D_MotorStopCounter = 0;
            nMaxActionStep = BACK_AUTO_STEPS[nBackSubRunMode] ;   
        }
        else
        {
            if((bWalkMotorInProcess == FALSE) &&
               (bKneadMotorInProcess == FALSE) &&
                   (bKnockMotorInProcess == FALSE)&&
                       (b3D_MotorInProcess == FALSE))
            {
                nCurActionStep++ ; //自动程序步骤增加
                if((nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
                   &&((nCurActionStep==170)|(nCurActionStep==310)))
                    {
                        bDemoStretch = true;
                        st_Stretch.active = TRUE;
                        st_Stretch.init = TRUE; 
                        st_Stretch.times = 2;
                        nCurActionStepreturn = nCurActionStep+1;
                    }
                    if((nBackSubRunMode == BACK_SUB_MODE_AUTO_7)&&(nCurActionStep%85==84))//nCurActionSteptemp))
                    {
                        bDemoStretch = true;
                        st_Stretch.active = TRUE;
                        st_Stretch.init = TRUE; 
                        st_Stretch.times = 3;
                        nCurActionStepreturn = nCurActionStep+1;
                    } 
                if(nCurActionStep >= nMaxActionStep)
                {
                    nCurActionStep = nStartActionStep ;  
                    if((nBackSubRunMode == BACK_SUB_MODE_AUTO_6)  )
                    {
                          bDemoStretch = true;//20170521
                          st_Stretch.active = TRUE;
                          //stretchMode = 0;//STRETCH_GO_DOWN;
                          st_Stretch.init = TRUE; 
                          st_Stretch.times = 3;
                          nCurActionStepreturn = 0;
                    }
                    if((nBackSubRunMode == BACK_SUB_MODE_AUTO_7))
                    {
                          bDemoStretch = true;//20170521
                          st_Stretch.active = TRUE;
                          //stretchMode = 0;//STRETCH_GO_DOWN;
                          st_Stretch.init = TRUE; 
                          st_Stretch.times = 3;
                          nCurActionStepreturn = 0;
                    }     
                }
                bGetNextActionStep = TRUE ;
            }
            
            /*********************Tapping OFF功能设置开始****************/
            if((bTapping ==1)&&((AutoDirector.nSubFunction == BACK_SUB_MODE_SOFT_KNOCK)||(AutoDirector.nSubFunction == BACK_SUB_MODE_KNOCK)))
            {
                if(AutoDirector.nWalkMotorLocateMethod == WALK_LOCATE_PARK)
                {
                    //敲击电机停止
                    bKnockMotorInProcess = TRUE ;
                    nKnockMotorControlParam1 = 0 ;
                    nKnockMotorControlParam2 = 0 ;
                    nKnockMotorControlParam3 = 0 ;
                    nCurSubFunction = BACK_SUB_MODE_PRESS;
                    nCurKneadKnockSpeed = 0 ;
                    //3D电机为3D指压状态
                    b3D_MotorInProcess = TRUE;
                    n3D_MotorControlState =_3D_WORK_CIRCLE;
                    n3D_MotorControlPosition = 0 ;
                    n3D_MotorControlSpeed =  _3D_SPEED_8;
                    n3D_MotorControlStopTime = AutoDirector.nKnockMotorRunTime ;
                    
                    bTapping_old = TRUE;
                }
                else
                {
                    //敲击电机停止
                    bKnockMotorInProcess = TRUE ;
                    nKnockMotorControlParam1 = 0 ;
                    nKnockMotorControlParam2 = AutoDirector.nKnockMotorRunTime ;
                    nKnockMotorControlParam3 = 0 ;
                    nCurSubFunction = BACK_SUB_MODE_PRESS;
                    nCurKneadKnockSpeed = 0 ;
                    
                    bTapping_old = TRUE;
                }
            }   
            else if((bTapping ==1)&&(AutoDirector.nSubFunction == BACK_SUB_MODE_WAVELET))
            {
                //敲击电机停止，揉捏电机不变
                bKnockMotorInProcess = TRUE ;
                nKnockMotorControlParam1 = 0 ;
                nKnockMotorControlParam2 = 0 ;
                nKnockMotorControlParam3 = 0 ;
                nCurSubFunction = BACK_SUB_MODE_KNEAD;
                
                bTapping_old = TRUE;
            }
            
            if((bTapping ==0)&&(bTapping_old == TRUE))
            {
                bTapping_old = false;
                nCurSubFunction = AutoDirector.nSubFunction ;
                nCurKneadKnockSpeed = AutoDirector.nKneadKnockSpeed ;
                
                bKneadMotorInProcess = TRUE ;
                nKneadMotorControlParam1 = AutoDirector.nKneadMotorState ;
                nKneadMotorControlParam2 = AutoDirector.nKneadMotorCycles ;
                //设置捶击电机
                bKnockMotorInProcess = TRUE ;
                nKnockMotorControlParam1 = AutoDirector.nKnockMotorState ;
                nKnockMotorControlParam2 = AutoDirector.nKnockMotorRunTime ;
                nKnockMotorControlParam3 = AutoDirector.nKnockMotorStopTime ;
                //设置3D马达力度 
                b3D_MotorInProcess = TRUE ;
                n3D_MotorControlState = AutoDirector.n3D_MotorState ;
                n3D_MotorControlPosition = AutoDirector.n3D_MotorPosition ;
                nSetAxisStrength = n3D_MotorControlPosition;
                bAxisUpdate = true; 
                n3D_MotorControlSpeed = AutoDirector.n3D_MotorSpeed ;
                n3D_MotorControlStopTime = AutoDirector.n3D_MotorStopTime ; 
            }
            /*********************Tapping OFF功能设置结束****************/
        }
        
        if(bGetNextActionStep == TRUE)
        {
            bGetNextActionStep = FALSE ;
            
            n3Dpointturn ++;
            switch(nBackSubRunMode)
            {
            case BACK_SUB_MODE_AUTO_0:
                AutoDirector = AutoFunction0[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_1:
                AutoDirector = AutoFunction1[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_2:
                AutoDirector = AutoFunction2[nCurActionStep] ;bWalkSlowFlag = 0;
                //     if(!bRestSleepStatus) st_RestSleep.step = 0;
                //     if(st_RestSleep.step == 0){AutoDirector = AutoFunction2[nCurActionStep] ;}
                //      if(st_RestSleep.step == 1){AutoDirector = AutoFunction2_1[nCurActionStep] ;}
                //     if(st_RestSleep.step == 2){AutoDirector = AutoFunction2_2[nCurActionStep] ;}
                break ;
            case BACK_SUB_MODE_AUTO_3:
                AutoDirector = AutoFunction3[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_4:
                AutoDirector = AutoFunction4[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_5:
                AutoDirector = AutoFunction5[nCurActionStep] ;bWalkSlowFlag = 0;
                break;
            case BACK_SUB_MODE_AUTO_6:
                //#ifndef TEST_3ADD_PROG
                //	printf("b:%d\n\r",nCurActionStep);
                //#endif
                AutoDirector = AutoFunction6[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_7:
                //#ifndef TEST_3ADD_PROG						
                //	printf("b:%d\n\r",nCurActionStep);
                //#endif					
                AutoDirector = AutoFunction7[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_AUTO_8:
                //#ifndef TEST_3ADD_PROG
                //	printf("b:%d\n\r",nCurActionStep);
                //#endif					
                AutoDirector = AutoFunction8[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;		
                
                //		         case BACK_SUB_MODE_AUTO_9://care 
                //					//#ifdef TEST_3ADD_PROG
                //					//	printf("b:%d\n\r",nCurActionStep);
                //					//#endif					
                //                        AutoDirector = AutoFunction9[nCurActionStep] ;
                //                        bWalkPWMFlag = FALSE;
                //						bWalkSlowFlag = 0;
                //                        break ; 
                //			
                
//            case BACK_SUB_MODE_AUTO_10:  //growth
//                //#ifdef TEST_3ADD_PROG
//                //	printf("b:%d\n\r",nCurActionStep);
//                //#endif					
//                AutoDirector = AutoFunction10[nCurActionStep] ;
//                bWalkPWMFlag = TRUE;
//                break ;   	
//                
//                
//                //4个quick mode
//            case BACK_SUB_MODE_AUTO_QUICK_FULL:
//                //#ifdef TEST_3ADD_PROG
//                //	printf("b:%d\n\r",nCurActionStep);
//                //#endif					
//                AutoDirector = AutoFunctionFull[nCurActionStep] ;
//                bWalkPWMFlag = FALSE;
//                break ;                        
//            case BACK_SUB_MODE_AUTO_QUICK_SHOULDER:
//                //#ifdef TEST_3ADD_PROG
//                //	printf("b:%d\n\r",nCurActionStep);
//                //#endif					
//                AutoDirector = AutoFunctionShoulder[nCurActionStep] ;
//                bWalkPWMFlag = FALSE;
//                break ;                        
//            case BACK_SUB_MODE_AUTO_QUICK_WAIST:
//                //#ifdef TEST_3ADD_PROG
//                //	printf("b:%d\n\r",nCurActionStep);
//                //#endif					
//                AutoDirector = AutoFunctionWaist[nCurActionStep] ;
//                bWalkPWMFlag = FALSE;
//                break ;  
//            case BACK_SUB_MODE_AUTO_QUICK_LEG:
//                //#ifdef TEST_3ADD_PROG
//                //	printf("b:%d\n\r",nCurActionStep);
//                //#endif					
//                AutoDirector = AutoFunctionLeg[nCurActionStep] ;
//                bWalkPWMFlag = FALSE;
//                break ;     	
                
            case BACK_SUB_MODE_3D1:
                AutoDirector = _3DFunction0[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_3D2:
                AutoDirector = _3DFunction1[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;
            case BACK_SUB_MODE_3D3:
                AutoDirector = _3DFunction2[nCurActionStep] ;bWalkSlowFlag = 0;
                break ;                     
            }
            //每次更换动作需要更新的变量
            nCurActionStepCounter = 0 ;//当前动作时间计数（行走或敲击时间计数）
            nCurShoulderAdjustCounter = 0 ;
            if(!((nCurSubFunction == BACK_SUB_MODE_SOFT_KNOCK) && (AutoDirector.nSubFunction == BACK_SUB_MODE_SOFT_KNOCK)))
            {
                nCurKnockRunStopCounter = 0 ;//叩击动作记数器
            }
            nCurKneadMotorCycles = 0 ;//揉捏圈数计数（揉捏）
            refreshAutoDirector();
        }
        break ;
    case BACK_MAIN_MODE_MANUAL:
        if(bBackManualModeInit == TRUE)
        {
            bBackManualModeInit = FALSE ;
            bGetNextActionStep = TRUE ;
            //            nMaxActionStep = 2 ;
            nCurActionStep = 0 ;
            b3D_MotorInProcess = false;
            n3D_MotorControlState = _3D_MANUAL ;
            //RockFunctionEnable(false);
        }
        else
        {
            if((bWalkMotorInProcess == FALSE) &&
               (bKneadMotorInProcess == FALSE) &&
                   (bKnockMotorInProcess == FALSE) &&
                       (b3D_MotorInProcess == FALSE))
            {
                nCurActionStep++ ;
                if(nCurActionStep >= nMaxActionStep)
                {
                    nCurActionStep = nStartActionStep ;
                }
                bGetNextActionStep = TRUE ;
            }
        }
        if(bGetNextActionStep == TRUE)
        {
            bGetNextActionStep = FALSE ;
            //每次更换动作需要更新的变量
            nCurActionStepCounter = 0 ;//当前动作时间计数（行走或敲击时间计数）
            nCurKnockRunStopCounter = 0 ;//叩击动作记数器
            nCurKneadMotorCycles = 0 ;//揉捏圈数计数（揉捏）
            nCur3D_MotorStopCounter = 0;
            nCurSubFunction = ManualDirector[nCurActionStep].nSubFunction ;
            nCurKneadKnockSpeed = ManualDirector[nCurActionStep].nKneadKnockSpeed ;
            //设置行走电机
            bWalkMotorInProcess = TRUE ;
            bUpdateLocate = TRUE ;
            nWalkMotorControlParam1 = ManualDirector[nCurActionStep].nWalkMotorLocateMethod ;
            nWalkMotorControlParam2 = ManualDirector[nCurActionStep].nWalkMotorLocateParam ;
            //设置揉捏电机
            bKneadMotorInProcess = TRUE ;
            nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
            nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
            //设置捶击电机
            bKnockMotorInProcess = TRUE ;
            nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
            nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
            nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
            
            //设置3D马达
            b3D_MotorInProcess = TRUE;
            n3D_MotorControlState = ManualDirector[nCurActionStep].n3D_MotorState ;
            n3D_MotorControlPosition = ManualDirector[nCurActionStep].n3D_MotorPosition ;
            n3D_MotorControlSpeed = ManualDirector[nCurActionStep].n3D_MotorSpeed ;
            n3D_MotorControlStopTime = ManualDirector[nCurActionStep].n3D_MotorStopTime ;
        }
        break;
    }
}

//int Main_FlexPad_Proce(void)
//{
//    int retval = 0;
//    if(st_Stretch.active) return 0;
//    if(bMassagePositionUpdate) return 0;
//    
//    if(bKeyFlexOut == TRUE)
//    {
//      FlexMotorSetDisable();
//      if(Flex_ControlOut(FLEX_MOTOR_CURRENT_4A))
//      {
//        nBuzzerMode = BUZZER_MODE_FAST ;
//        bSendBuzzerMode = TRUE ;
//        bBlueToothSendBuzzerMode = TRUE;
//        retval = 1; 
//      }
//      else      
//      {
//        nBuzzerMode = BUZZER_MODE_SLOW ;
//        bSendBuzzerMode = TRUE ;
//        bBlueToothSendBuzzerMode = TRUE;
//      }
//    }
//    if(bKeyFlexIn == TRUE)
//    {
//      FlexMotorSetDisable();
//      if(Flex_ControlIn(FLEX_MOTOR_CURRENT_4A))
//      {
//        nBuzzerMode = BUZZER_MODE_FAST ;
//        bSendBuzzerMode = TRUE ;
//        bBlueToothSendBuzzerMode = TRUE;
//        retval = 1; 
//      }
//      else      
//      {
//        nBuzzerMode = BUZZER_MODE_SLOW ;
//        bSendBuzzerMode = TRUE ;
//        bBlueToothSendBuzzerMode = TRUE;
//      }
//    }
//    if((bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE) && FlexMotorGetEnable() == false)
//    {
//        //Flex_SetDirection(FLEX_MOTOR_STOP);
//        Flex_ControlStop();
//        retval = 0;
//    }
//    return retval;
//}

/*********************************************************************
功能说明：根据扶手状态控制蜂鸣器响声函数
参数：无
返回值：无
其他说明：无
*********************************************************************/
void Main_ArmPad_Proce(void)
{
    if(handrail_flag != 0)
    {
        return;
    }
    if(  bKeyArmPadOut == true )
    {
        if(  Input_GetArmStatus() == ARM_OUT_LIMIT  )//到达外限位，快速响
        {
            nBuzzerMode = BUZZER_MODE_FAST ;
            bSendBuzzerMode = TRUE ;
        }
        else
        {
            nBuzzerMode = BUZZER_MODE_SLOW ;
            bSendBuzzerMode = TRUE ;    
        }
    }
    if( bKeyArmPadIn == true )
    {  
        if(Input_GetArmStatus() == ARM_IN_PROTECT)
        {
            if(bArmProtect == TRUE)
            {
                bArmProtect = false;
                nArmProtect++;
            }
            if(nArmProtect < 5)
            {
                
                nBuzzerMode = BUZZER_MODE_FAST ;
                bSendBuzzerMode = TRUE ;
            }
            else if(nArmProtect < 15)
            {
                nBuzzerMode = BUZZER_MODE_SLOW ;
                bSendBuzzerMode = TRUE ; 
            }
            else
            {
                nArmProtect = 0;
            } 
        }
        else if( ( Input_GetArmStatus() == ARM_IN_LIMIT) ||(Input_GetArmStatus() == ARM_OUT_LIMIT) )
        {
            nBuzzerMode = BUZZER_MODE_FAST ;
            bSendBuzzerMode = TRUE ;
        }
        else
        {
            nBuzzerMode = BUZZER_MODE_SLOW ;
            bSendBuzzerMode = TRUE ; 
        }
    }
    
    if(( bKeyArmPadIn == FALSE )&&(bKeyArmPadOut == FALSE))
    {
        if(outarmcmd == H10_KEY_HANDRAIL_OUT_START)
        {
            outarmcmd = H10_KEY_HANDRAIL_OUT_STOP;
        }
        
        if(outarmcmd == H10_KEY_HANDRAIL_IN_START)
        {
            outarmcmd = H10_KEY_HANDRAIL_IN_STOP;
        }
    }
}
unsigned char arm_step=0;
unsigned int arm_100ms_time;
void Main_Arm_Start(void)
{
    //bool enable = ReadEEByte(USER_DATA_BASE + ARM_MOTOR_SWITCH_ADDRESS);
    if((handrail_flag == 0))//||(!enable)
    {
        return;
    }
    switch(arm_step)
    {
    case 0:
        if(  Input_GetArmStatus() == ARM_OUT_LIMIT  )
        {
            outarmcmd = H10_KEY_HANDRAIL_OUT_STOP;
            arm_step++;
            arm_100ms_time = 0;
        }
        else
        {
            outarmcmd = H10_KEY_HANDRAIL_OUT_START;
        } 
        break;
    default:
    case 1:
        if((Input_GetArmStatus() == ARM_IN_LIMIT)||(Input_GetArmStatus() == ARM_IN_PROTECT)||(arm_100ms_time == 20))
        {
            outarmcmd = H10_KEY_HANDRAIL_IN_STOP;
            arm_step = 0;
            handrail_flag = 0;
        }
        else
        {
            outarmcmd = H10_KEY_HANDRAIL_IN_START;
        }
        break;
    }
}

int Main_FlexPad_Proce(void)
{
    int retval = 0;
    if(st_Stretch.active) return 0;
    if(bMassagePositionUpdate) return 0;
    if(bKeyFlexOut == TRUE)
    {
        FlexMotorSetDisable();
        if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
        {
            nBuzzerMode = BUZZER_MODE_FAST ;
            bSendBuzzerMode = TRUE ;
            bBlueToothSendBuzzerMode = TRUE;
            retval = 1;
        }
        else
        {
            nBuzzerMode = BUZZER_MODE_SLOW ;
            bSendBuzzerMode = TRUE ;
            bBlueToothSendBuzzerMode = TRUE;
            retval = 0;
        }
    }
    if(bKeyFlexIn == TRUE)
    {
        FlexMotorSetDisable();
        if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
        {
            nBuzzerMode = BUZZER_MODE_FAST ;
            bSendBuzzerMode = TRUE ;
            bBlueToothSendBuzzerMode = TRUE;
            retval = 1;
        }
        else
        {
            nBuzzerMode = BUZZER_MODE_SLOW ;
            bSendBuzzerMode = TRUE ;
            bBlueToothSendBuzzerMode = TRUE;
            retval = 0;
        }
    }
    if((bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE))
    {
        if(FlexMotorGetEnable()) return 0;
        FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
        retval = 0;
    }
    return retval;
}

//小腿起落电动缸控制程序
void Main_LegPad_Proce(void)
{   
    LegMotor_Proce();
    if(st_Stretch.active) return;  //如果拉退程序有效，退出
	  if(st_GrowthStretch.active) return;
    if(bMassagePositionUpdate) return; //在强制设置按摩位置时也会进行小腿处理，故当强制设置按摩位置时不执行此函数内容
    if(bLegPadLinkage == FALSE) //小腿单独动，此时不考虑前滑电动缸的位置
    {
        if(bKeyLegPadUp == TRUE)
        {
            FlexMotorSetEnable();
            if(LegMotor_Control(STATE_RUN_LEG_UP) != LEG_RUN)
            {
                if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
                {
                   nBuzzerMode = BUZZER_MODE_FAST ;
                   bSendBuzzerMode = TRUE ;
                }
            }
            else
            {
                if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
                {
                   nBuzzerMode = BUZZER_MODE_SLOW ;
                   bSendBuzzerMode = TRUE ;	
                }
            }
        }
        
        if(bKeyLegPadDown == TRUE)
        {
            FlexMotorSetEnable();
            switch(LegMotor_Control(STATE_RUN_LEG_DOWN))
            {
            case LEG_RUN:
                {		 
                    nBuzzerMode = BUZZER_MODE_SLOW ;
                    bSendBuzzerMode = TRUE ;		   
                }
                break;
            case LEG_STOP_AT_DOWN:
                { 
                    nBuzzerMode = BUZZER_MODE_FAST ;
                    bSendBuzzerMode = TRUE ;	   
                }
                break;
            case  LEG_STOP_AT_GROUND:
                                
                break;
            case LEG_STOP_AT_ANGLE:
                break;
            }
        }
        
    }
    else  //靠背和小腿联动，前滑电动缸必须在最前位置
    {
        if(SlideMotor_Get_Location() == SLIDE_MOTOR_AT_FORWARD)
        {   
            if(bKeyLegPadUp == TRUE)
            {
                LegMotor_Control(STATE_RUN_LEG_UP);
                FlexMotorSetEnable();
            }
            if(bKeyLegPadDown == TRUE)
            {
                LegMotor_Control(STATE_RUN_LEG_DOWN);
                FlexMotorSetEnable();
            }
        }
    }
    
    if((bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE))
    {
        LegMotor_Control(STATE_LEG_IDLE) ;
    }
}
#define STRETCH_GO_DOWN 0
#define STRETCH_GO_OUT  1

StretchProgramStruct const stretchProgram_30[] =
{
  {39,3,STRETCH_GO_DOWN},
  {33,3,STRETCH_GO_DOWN},
  {28,3,STRETCH_GO_DOWN},
  {23,3,STRETCH_GO_DOWN},
  {18,3,STRETCH_GO_DOWN},
  {13,3,STRETCH_GO_DOWN},
  {8,3,STRETCH_GO_DOWN},
  {3,1,STRETCH_GO_DOWN},
};
StretchProgramStruct const stretchProgram_20[] =
{
  {28,3,STRETCH_GO_DOWN},
  {23,3,STRETCH_GO_DOWN},
  {18,3,STRETCH_GO_DOWN},
  {13,3,STRETCH_GO_DOWN},
  {8,3,STRETCH_GO_DOWN},
  {3,1,STRETCH_GO_DOWN},
};
StretchProgramStruct const stretchProgram_10[] =
{ 
  {19,3,STRETCH_GO_DOWN},
  {13,3,STRETCH_GO_DOWN},
  {8,3,STRETCH_GO_DOWN},
  {3,1,STRETCH_GO_DOWN},
};

//StretchProgramStruct const stretchProgram_10[] =
//{
//  {9,2,STRETCH_GO_DOWN},
//  {4,2,STRETCH_GO_DOWN},
//};
unsigned int p_BackLocation_test;
/******************************************************************
功能说明：拉筋程序
参数：无
返回值：无
其他说明：拉筋顺序 ①小腿到最高端靠背到指定位置，手臂左右气囊轮番充气
                   ②小腿收缩到内限位，足部气囊开始充气
                   ③足部气囊充气够3秒，小腿向外伸一段距离
                   ④小腿伸到指定位置后，足部和小腿开始充气
                   ⑤充气够6秒后，打开滚轮，并且打开足部腿部肩部气囊
                   ⑥足部腿部肩部充气够5秒后，椅子向下开始拉伸
                   ⑦拉到位置停留10秒后恢复初始位置重复进行  
******************************************************************/
void Valve_StretchControlProce(void)
{
    bool legFlag,BackFlag,SlideFlag;
    unsigned char FlexFlag;
    unsigned int p_BackLocation,p_LegLocation;
    bool bStatus,bBACKStatus;
    if(!st_Stretch.active) 
    {
        bAUTO1AirEnable = FALSE;
        unsigned int RunTime = Data_Get_TimeSecond();
        unsigned int Minutes,i;
        StretchProgramStruct const *p;
        unsigned int totalTimes;
        if(RunTime%60 != 0)  return; 
        
        if(w_PresetTime == RUN_TIME_10) 
        {
            p = stretchProgram_10;
            totalTimes = sizeof(stretchProgram_10)/sizeof(StretchProgramStruct);
        }
        else if(w_PresetTime == RUN_TIME_30) 
        {
            p = stretchProgram_30;
            totalTimes = sizeof(stretchProgram_30)/sizeof(StretchProgramStruct);
        }
        else
        {
            p = stretchProgram_20;
            totalTimes = sizeof(stretchProgram_20)/sizeof(StretchProgramStruct);
        } 
        Minutes = RunTime/60; //获取当前分钟数
        
        if(Minutes == 0) 
        {
            st_Stretch.times = 0;
            return; //最后一分钟停止拉腿
        }
        
        for(i=0;i<totalTimes;i++)
        {
            if(Minutes == (p+i)->time) 
            {
                st_Stretch.active = TRUE;
                st_Stretch.init = TRUE; 
                stretchMode = (p+i)->mode;
                // stretchMode = 0;
                st_Stretch.times = (p+i)->times;
                
                break;
            }
        }
        if(!st_Stretch.active)  return;
    }
    
    if(st_Stretch.init)
    {
        nStretchStep = 0;
        st_Stretch.step = 0;
        st_Stretch.timer = 0;
        st_Stretch.init = FALSE;
    }
    
    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT) BackMotor_Set_Location(BACK_MOTOR_MAX_LOCATION);
    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT) BackMotor_Set_Location(0);
    
    if(st_Stretch.times > 0)
    {
        bAUTO1AirEnable = TRUE;
        SetRockStep(StartRock);//将摇椅步骤置0
        switch(st_Stretch.step)
        {
        case  0:   //机芯动作初始化   机芯到底
            nStretchStep = 0;
            AutoDirector = AutoFunctionStretch[nStretchStep] ;//更新机芯数据
            refreshAutoDirector();
            st_Stretch.step++;
            legFlag = FALSE;
            BackFlag = FALSE;
            break;
        case  1:  //小腿到最高位置，靠背到指定位置
            p_BackLocation = Input_GetBackPosition(); //获取靠背位置
            legFlag = LegMotor_Control(STATE_RUN_LEG_UP);
            
            if(p_BackLocation > (MASSAGE_BACK_STRCHUP_LOCATION + 20))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                BackFlag = FALSE;
            }
            else if(p_BackLocation < (MASSAGE_BACK_STRCHUP_LOCATION - 20))
            {
                BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                BackFlag = FALSE;
            }
            else
            {
                BackFlag = BackMotor_Control(STATE_BACK_IDLE) ;
            }
            if((bWalkMotorInProcess == FALSE) &&
               (bKneadMotorInProcess == FALSE) &&
                   (bKnockMotorInProcess == FALSE)&&
                       (b3D_MotorInProcess == FALSE)&&
                           legFlag &&BackFlag)         //椅子到达指定位置,机芯动作执行完成
            {
                st_Stretch.step ++;
                st_Stretch.timer = 0; 
//                Valve_SetStretchCharge_FOOT(1);//打开脚部左右气囊
                //FlexMotorSetEnable();
            }
            else
            {
//                Valve_SetStretchCharge_ARM(0);//左右手部气囊轮番充气
            }
            Valve_SetStretchCharge_ARM(0);
            break;
        case 2: 
            //            BackMotor_Stretch_Control(STATE_BACK_IDLE) ;//靠背停止
            nStretchStep = 1;
            AutoDirector = AutoFunctionStretch[nStretchStep] ;//更新第二组数据
            refreshAutoDirector();
            //st_Stretch.step++;
            //Valve_SetStretchCharge_FOOT(1);
            // if(st_Stretch.timer > 40) 
            {
                st_Stretch.step++;
                st_Stretch.timer = 0;
                nSet_StretchStopTime(0);//nFlex_StretchIn_TimeStop设置为0
            }
            bHaveMan = FALSE;
            break;
        case 3: 
            Valve_SetStretchCharge_ARM(0);//手臂气囊轮番充气,小腿收缩到内限位或者向内运行13s
            //FlexFlag = FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
            FlexFlag = FlexMotor_Control(STATE_RUN_FLEX_STRETCH_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_2A);//向里收缩至里面限位
            if(FlexFlag )
            {
                //FlexMotorSetEnable();//拉伸过程中不要自动找脚
                st_Stretch.step++;
                st_Stretch.timer = 0;
                
            }
            if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) 
            {
                bHaveMan = TRUE;
            }
            //st_Stretch.step++;st_Stretch.timer = 0;
            break;
        case 4 :
            //足部左右气囊充气
            if(FlexMotorGetEnable() == false)//自动找脚完成后一段时间执行下一个case
            {
                Valve_SetStretchCharge_FOOT(1);
                if(st_Stretch.timer > 30)//60 
                { 
                    //Valve_SetStretchCharge_FOOT_THIGH(1);
                    st_Stretch.step++;
                    st_Stretch.timer = 0;
                }
            }
            else
            {
                st_Stretch.timer = 0;
            }
            if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) 
            {
                bHaveMan = TRUE;
            }
            nSet_StretchTime(0);//将w_Timer置0
            break;
        case 5:          //原来有脚向外运行到找不到脚，原来无脚向外运行2秒停止 
            FlexFlag = FlexMotor_Control(STATE_RUN_FLEX_STRETCH_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_2A);
            if( (FlexFlag== FLEX_STOP_AT_OUT)
               || (FlexFlag== FLEX_STOP_AT_ANGLE)
                   || (FlexFlag== FLEX_STOP_AT_GROUND)
                       || (FlexFlag == FLEX_STOP_AT_FOOT_LEAVE) )
            {
                Valve_SetStretchCharge_FOOT_THIGH(1);
                if(st_Stretch.timer > 100)//60时间太短
                {
                    st_Stretch.step++;
                    st_Stretch.timer = 0;
                }
                FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
            }
            //            if(bRollerEnable)
            //            {
            //                if(st_Stretch.times % 2== 0)
            //                {
            //                    RollerMotor_Control(ROLLER_SPEED_SLOW,0);
            //                }
            //                else
            //                {
            //                    RollerMotor_Control(ROLLER_SPEED_SLOW,1);
            //                }
            //            }
            break;
        case  6: 
            /*  if(FlexMotorGetEnable() == false)
            {
            Valve_SetStretchCharge_FOOT_LEG_SHOULD(1); 
            nStretchStep = 0;
            AutoDirector = AutoFunctionStretch[nStretchStep] ;
            refreshAutoDirector();
            
            
            if(bRollerEnable)
            {
            if(st_Stretch.times % 2== 0)
            {
            RollerMotor_Control(ROLLER_SPEED_SLOW,0);
        }
            else
            {
            RollerMotor_Control(ROLLER_SPEED_SLOW,1);
        }
        }
            if(st_Stretch.timer > 100) 
            {
            st_Stretch.step++;
            st_Stretch.timer = 0;
            
        }
        }
            else
            {
            RollerMotor_Control(ROLLER_SPEED_STOP,0);
            Valve_SetStretchCharge_ARM(0);
        }
            */
            if(bRollerEnable)
            {
                if(st_Stretch.times % 2== 0)
                {
                    RollerMotor_Control(ROLLER_SPEED_SLOW,0);
                }
                else
                {
                    RollerMotor_Control(ROLLER_SPEED_SLOW,1);
                }
            }
            st_Stretch.step++;
            break;
        case 7:
            // if(bWalkMotorInProcess == FALSE)
            {
                nStretchStep = 1;
                AutoDirector = AutoFunctionStretch[nStretchStep] ;
                refreshAutoDirector();
                st_Stretch.step++;
                st_Stretch.timer = 0;
            }
            break;
        case  8: 
            Valve_SetStretchCharge_FOOT_LEG_SHOULD(0); //打开腿部足部肩部气囊
            
            if(st_Stretch.timer >= 100)//50时间太短
            {  //判断是否已达充气时间
                st_Stretch.step++;
                st_Stretch.timer = 0;
            }
            break;
            
            
        case 9: 
            nStretchStep = 2;
            AutoDirector = AutoFunctionStretch[nStretchStep] ;
            refreshAutoDirector();
            
            st_Stretch.step++;
            st_Stretch.timer = 0;
            
            break;
        case 10:  //拉倒最低端        
            
            Valve_SetStretchCharge_FOOT_LEG_SHOULD(0); 
//            legFlag = LegMotor_Control(STATE_RUN_LEG_DOWN);
//            bBACKStatus = BackMotor_Control(STATE_RUN_BACK_DOWN) ;
            p_BackLocation = Input_GetBackPosition();  
            p_LegLocation = LegMotor_Get_Position(); 
            p_BackLocation_test = p_BackLocation;
            if(nStretchVigor==1)
            {
                if(p_BackLocation > (500 + 20))
                {
                    BackMotor_Control(STATE_RUN_BACK_UP) ;
                    bBACKStatus = FALSE;
                }
                else if(p_BackLocation < (500 - 20))
                {
                    BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                    bBACKStatus = FALSE;
                }
                else
                {
                    BackMotor_Control(STATE_BACK_IDLE) ;
                    bBACKStatus = TRUE;
                } 
                if(p_LegLocation > (900 + POSITION_CTRL_OFFSET))
                {
                    LegMotor_Control(STATE_RUN_LEG_DOWN) ;
                    legFlag = FALSE;
                }
                else if(p_LegLocation < (900 - POSITION_CTRL_OFFSET))
                {
                    LegMotor_Control(STATE_RUN_LEG_UP);
                    legFlag = FALSE;
                }
                else
                {
                    LegMotor_Control(STATE_LEG_IDLE);
                    legFlag = TRUE;
                }    
            }
            if(nStretchVigor==2)
            {
                if(p_BackLocation > (580 + 20))
                {
                    BackMotor_Control(STATE_RUN_BACK_UP) ;
                    bBACKStatus = FALSE;
                }
                else if(p_BackLocation < (580 - 20))
                {
                    BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                    bBACKStatus = FALSE;
                }
                else
                {
                    BackMotor_Control(STATE_BACK_IDLE) ;//BackMotor_Set_Pwm_Data(0);
                    bBACKStatus = TRUE;
                } 
                if(p_LegLocation > (600 + POSITION_CTRL_OFFSET))
                {
                    LegMotor_Control(STATE_RUN_LEG_DOWN) ;
                    legFlag = FALSE;
                }
                else if(p_LegLocation < (600 - POSITION_CTRL_OFFSET))
                {
                    LegMotor_Control(STATE_RUN_LEG_UP);//STATE_RUN_BACK_UP) ;
                    legFlag = FALSE;
                }
                else
                {
                    LegMotor_Control(STATE_LEG_IDLE);//STATE_BACK_IDLE) ;
                    legFlag = TRUE;
                }
            }
            if(nStretchVigor==3)
            {
                legFlag = LegMotor_Control(STATE_RUN_LEG_DOWN);
                bBACKStatus = BackMotor_Control(STATE_RUN_BACK_DOWN) ;  
            }
            if((legFlag==TRUE)&&(bBACKStatus==TRUE))
            {  
                if(bRollerEnable)
                {
                    RollerMotor_Control(ROLLER_SPEED_SLOW,0);
                }
                st_Stretch.step++;
                st_Stretch.timer = 0;
                nStretchStep = 3;
                AutoDirector = AutoFunctionStretch[nStretchStep] ;
                refreshAutoDirector();       
            }
            break;
        case 11:    //加压时间
            // Valve_SetStretchHold();
            Valve_SetStretchChargeSTEEL(0); 
            st_Stretch.step++;
            st_Stretch.timer = 0;
            
            
            break;
        case 12:
            Valve_SetStretchChargeSTEEL(0);//小腿、肩部气囊，足部交替充气
            if(st_Stretch.timer >= 100)//(Valve_GetAirBagStrength()*20)//修改为拉倒最低端停10s
            {  //判断是否已达加压时间
                st_Stretch.step++;
                st_Stretch.timer = 0;
                RollerMotor_Control(ROLLER_SPEED_STOP,0);
            }
            break;
        case 13:
            st_Stretch.step = 0;//一组拉伸完成后又执行第二组拉伸即从case0开始
            st_Stretch.timer = 0;
            st_Stretch.times--;//执行的拉腿组数减1
            Valve_SetStretchUp();  
            nStretchStep = 0; //机芯动作从0开始
            if(st_Stretch.times == 0)
            {
                nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION;//MASSAGE_RESET_POSITION;// MASSAGE_RESET_POSITION;//
                bMassagePositionUpdate = TRUE;
                Zero_mark=2;
                st_Stretch.bBackLegFlag = FALSE;
                st_Stretch.timer = 0;
                st_Stretch.active = FALSE;//拉腿次数完成又重新开始执行拉腿
                //bBackAutoModeInit = true;  //为了避免机芯出现差错，机芯按摩从头开始
                bDemoStretch = false;
//                
//                 if((nBackSubRunMode == BACK_SUB_MODE_5MIN_DEMO))
//                {
//                    bGetNextActionStep = TRUE ;
//                    nCurActionStep = 17;
//                }
//                else 
                
                if((nBackSubRunMode == BACK_SUB_MODE_AUTO_6))
                {
                    __NOP();
                    bGetNextActionStep = TRUE ;
                    nCurActionStep = nCurActionStepreturn;
                }      
                else if((nBackSubRunMode == BACK_SUB_MODE_AUTO_7))
                {
                    bGetNextActionStep = TRUE ;
                    nCurActionStep = nCurActionStepreturn;
                }
                else
                { 
                    __NOP();
                    bBackAutoModeInit = true;
                } 
                
            }
            break;
        default:
            break;
        }
    }   
    
}



//=================================================================

//void Valve_GrowthStretchControlProce(void)
//{
//    bool bStatus;
//  int legFlag,BackFlag,FlexFlag,SlideFlag;
// // static bool    stretchMode;// = STRETCH_GO_DOWN;
//  
//    if(bAngleNoChangeProcess == TRUE)
//  {
//    if(st_GrowthStretch.active)
//    {
//      st_Stretch.active = FALSE;
//      st_Stretch.step = 0;
//      st_Stretch.timer = 0;
//      st_Stretch.times = 0;
//      st_Stretch.init = FALSE;
//      LegMotor_Control(STATE_LEG_IDLE);
//      BackMotor_Control(STATE_BACK_IDLE);
//    //  FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
//      
//      return;
//    }
//    else
//    {
//      return;
//    }
//    
//  }
//  
//  
//  
//  
//  stretchMode = STRETCH_GO_DOWN;
//    if(!st_GrowthStretch.active) return;
//
//  if(st_GrowthStretch.init)
//  {
//    //printf("init\n");
//    st_GrowthStretch.step = 0;
//    st_GrowthStretch.timer = 0;
//    st_GrowthStretch.times = 3;
//    st_GrowthStretch.init = FALSE;
//    
//    if(Input_GetFlexFootSwitch())bEmcStaus=0;//cyw
//    else                bEmcStaus=1;
//  }
//
//  
//  
//  
//  
//  
//  if(st_GrowthStretch.times > 0)
//  {
//    bAUTO1AirEnable = TRUE;
//    switch(st_GrowthStretch.step)
//    {
//    case  0:   //机芯动作初始化
//      st_GrowthStretch.step++;
//      break;
//    case  1:  //按摩椅到最大位置
//      Valve_SetStretchUp();  
//	  RollerMotor_Control(ROLLER_SPEED_STOP,0);
//      
//      //LegKnead_Control(LEG_KNEAD_SPEED_STOP,LEG_KNEAD_TO_OUT);
//      SlideFlag = SlideMotorControl(STATE_RUN_SLIDE_FORWARD); 
//      
//      if(SlideFlag) //前滑电动缸必须先滑到前面
//      {
//        legFlag = LegMotor_Control(STATE_RUN_LEG_UP);
//        BackFlag = BackMotor_Control(STATE_RUN_BACK_DOWN);
// //       FlexFlag = Flex_ControlIn(FLEX_MOTOR_CURRENT_3A);
//        if(bEmcStaus)//在做emc测试,小腿缩到最里面 
//
//	{
//	  FlexFlag=1;
//	}
//        else
//	{
//        FlexFlag = FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlIn(FLEX_MOTOR_CURRENT_3A);
//        }
//        
//        
//        
//        if(/*(bWalkMotorInProcess == FALSE) &&
//             (bKneadMotorInProcess == FALSE) &&
//               (bKnockMotorInProcess == FALSE)&&
//                 (b3D_MotorInProcess == FALSE)&&*/
//                   legFlag &&
//                     BackFlag &&
//                       FlexFlag)
//        {
//          st_GrowthStretch.step ++;
//          st_GrowthStretch.timer = 0; 
//        }
//      }
//      break;
//    case 2: 
//            if(bEmcStaus)//在做emc测试
//            {
//                    st_GrowthStretch.step=6;
//            }
//            else
//            {
//                    st_GrowthStretch.step=3;//++;
//            }
//            st_GrowthStretch.timer = 0; 
//            FlexMotorSetDisable();
//            break;
//      
//    case 3:  //调整电动小腿位置
//
//        
//        FlexFlag = FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlOut(FLEX_MOTOR_CURRENT_5A);//按摩椅小腿往外拉  5cm,有可能碰到行程开关
//        if(FlexFlag )//|| st_Stretch.timer > 50)
//        {
//          bStatus = 1;
//          st_GrowthStretch.step++;
//          st_GrowthStretch.timer = 0; 
//          
//        }
//        else
//        {
//          bStatus = 0;
//          //st_Stretch.timer = 0;
//          
//          //if(st_Stretch.timer < 50)
//          //{
//            Valve_SetStretchChargeATOUT(1);//足部和坐垫先充气
//          //}
//          //else
//          //{
//          //  Valve_SetStretchChargeATOUT2(1);
//          //} 
//        }
//
//        if(bRollerEnable)
//        {
//          if(st_GrowthStretch.times % 2== 0)
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_IN);
//          }
//          else
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_OUT);
//          }
//        }
//      break;
//      
//    case 4:  //调整电动小腿位置
// 
//        Valve_SetStretchChargeATOUT2(1);
//        FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
//        if(st_GrowthStretch.timer>80)//按摩椅小腿往外拉  5cm,有可能碰到行程开关
//        {
//          st_GrowthStretch.step++;
//          st_GrowthStretch.timer = 0;
//          FlexMotorSetEnable();
//          Valve_SetStretchChargeATOUTFootHeelOFF(1);
//          
//        }
//
//        if(bRollerEnable)
//        {
//          if(st_GrowthStretch.times % 2== 0)
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_IN);
//          }
//          else
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_OUT);
//          }
//        }
//      break;  
//      
//      
//      
//    case  5: 
//     if(FlexMotorGetEnable() == false)
//     {
//       if(st_GrowthStretch.timer > 20) 
//       {
//         st_GrowthStretch.step++;
//       }
//        if(bRollerEnable)
//        {
//          if(st_GrowthStretch.times % 2== 0)
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_S_RUB);
//          }
//          else
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_S_RUB);
//          }
//        } 
//     }
//     else
//     {
//       RollerMotor_Control(ROLLER_SPEED_STOP,0);
//     }
//     break;
//     case 6:
//      //靠背不动，小腿不动，腿侧和足侧充气 持续时间为一直到小腿下降到最低点 
//    //  if(stretchMode == STRETCH_GO_OUT)
//    //  {
//     //   Valve_SetStretchChargeOut(1); 
//    //  }
//     // else
//     // {
//        Valve_SetStretchCharge(1); 
//     // }
//
//      
//      if(bRollerEnable)
//      {
//        if(st_GrowthStretch.times % 2== 0)
//        {
//          RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_S_INT_IN);
//        }
//        else
//        {
//          RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_S_INT_OUT);
//        }
//      }
//       if(st_GrowthStretch.timer > 160) 
//       {
//         st_GrowthStretch.step++;
//         st_GrowthStretch.timer = 0;
//         
//       }
//     
//      
//      break;
//    case  7: 
//   //  if(stretchMode == STRETCH_GO_OUT)
//    //  {
//   //     Valve_SetStretchChargeOut(0); 
//   //   }
//    //  else
//    //  {
//        Valve_SetStretchCharge(0); 
//    //  }
//
//      if(st_GrowthStretch.timer >= C_STRETCH_CHARGE_TIME)
//      {  //判断是否已达充气时间
//        st_GrowthStretch.step++;
//        st_GrowthStretch.timer = 0;
//      }
//      break;
//     
//    case 8: 
// ///    nStretchStep = 2;
////     AutoDirector = AutoFunctionStretch[nStretchStep] ;
////     refreshAutoDirector();
//     st_GrowthStretch.step++;
//     break;
//     case 9:          
//   
//        Valve_SetStretchChargeOut(0); 
//        //LegKnead_Control(LEG_KNEAD_SPEED_SLOW,LEG_KNEAD_TO_IN);
//        //LegKnead_Control(LEG_KNEAD_SPEED_STOP,LEG_KNEAD_TO_IN);
//        FlexFlag = TRUE;//Flex_ControlOut(FLEX_MOTOR_CURRENT_2A);
//        if(FlexFlag || st_GrowthStretch.timer > 100)
//        {
//          bStatus = 1;
//        }
//        else
//        {
//          bStatus = 0;
//        }
//      
//      
//      if(bStatus)
//      { 
//        //LegKnead_Control(LEG_KNEAD_SPEED_MID,LEG_KNEAD_TO_IN);
//        if(bRollerEnable)
//        {
//          if(st_GrowthStretch.times % 2== 0)
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_L_INT_IN);
//          }
//          else
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_L_INT_OUT);
//          }
//        }
//        //Flex_SetDirection(FLEX_MOTOR_STOP);
//        FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
//        st_GrowthStretch.step++;
//        st_GrowthStretch.timer = 0;
//        //nStretchStep = 3;
//        //AutoDirector = AutoFunctionStretch[nStretchStep] ;
//        //refreshAutoDirector();
//      }
//      break;
//
//     case 10:   //AIR      
//   //   if(stretchMode == STRETCH_GO_DOWN)   
//   //   {
//        Valve_SetStretchChargedown(1);
//        bLegAirBagOn = true;
//        //LegKnead_SetPower(LEG_KNEAD_ON);
//        //LegKnead_Control(LEG_KNEAD_SPEED_MID,LEG_KNEAD_TO_IN);
//        if(LEG_STOP_AT_DOWN == LegMotor_Control(STATE_RUN_LEG_DOWN))
//        {
//          bStatus = 1;
//        }
//        else
//        {
//          bStatus = 0;
//        }
//   //   }
//      if(bStatus)
//      { 
//        bLegAirBagOn = true;
//        //if(stretchMode != STRETCH_GO_DOWN)   
//        // {
//        //LegKnead_SetPower(LEG_KNEAD_ON);
//        //LegKnead_Control(LEG_KNEAD_SPEED_MID,LEG_KNEAD_TO_OUT);
//        // }
//        
//        if(bRollerEnable)
//        {
//          if(st_GrowthStretch.times % 2== 0)
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_IN);
//          }
//          else
//          {
//            RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_CON_OUT);
//          }
//        }
//        //Flex_SetDirection(FLEX_MOTOR_STOP);
//        FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
//        st_GrowthStretch.step++;
//        st_GrowthStretch.timer = 0;
//      }
//      break;
//    case 11:    //加压时间
//      Valve_SetStretchHold();
//      st_GrowthStretch.step++;
//      st_GrowthStretch.timer = 0;
//      break;
//    case 12:
//
//     if(st_GrowthStretch.times % 2== 0)
//     {
//       RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_S_RUB);
//     }
//     else
//     {
//       RollerMotor_Controlstrtch(ROLLER_SPEED_SLOW,ROLLER_MODE_L_RUB);
//     }
//     
//       if(st_GrowthStretch.timer >= 90)//(Valve_GetAirBagStrength()*22))
//       {  //判断是否已达加压时间
//         //st_Stretch.step++;
//         //st_Stretch.timer = 0;
//         RollerMotor_Control(ROLLER_SPEED_STOP,0);
//         bLegAirBagOn = FALSE;
//         //LegKnead_Control(LEG_KNEAD_SPEED_STOP,LEG_KNEAD_TO_IN);
//         Valve_SetStretchHoldHeelOFF();
//       }
//       if(st_GrowthStretch.timer >= 110)//(Valve_GetAirBagStrength()*22))
//       {  //判断是否已达加压时间
//         //st_Stretch.step++;
//         //st_Stretch.timer = 0;
//         RollerMotor_Control(ROLLER_SPEED_STOP,0);
//         bLegAirBagOn = FALSE;
//         //LegKnead_Control(LEG_KNEAD_SPEED_STOP,LEG_KNEAD_TO_IN);
//         Valve_SetStretchHoldHeelSCONDOFF();
//       }
//       if(st_GrowthStretch.timer >= 120)//(Valve_GetAirBagStrength()*22))
//       {  //判断是否已达加压时间
//         st_GrowthStretch.step++;
//         st_GrowthStretch.timer = 0;
//         RollerMotor_Control(ROLLER_SPEED_STOP,0);
//         bLegAirBagOn = FALSE;
//         //LegKnead_Control(LEG_KNEAD_SPEED_STOP,LEG_KNEAD_TO_IN);
//       }
//
//      break;
//    case 13:
//         st_GrowthStretch.step = 0;
//         st_GrowthStretch.timer = 0;
//         st_GrowthStretch.times--;
//         Valve_SetStretchUp();  
//    //     nStretchStep = 0;
//         if(st_GrowthStretch.times == 0)
//         {
//         // nZLB_RunState = 1;            //拉退动作完成强制回到第一个零重力点
//          nTargetMassagePosition =MASSAGE_OPTIMAL_POSITION;// MASSAGE_OPTIMAL2_POSITION; 
//          bMassagePositionUpdate = TRUE;
//          //bZLBMotorRunFlag = TRUE;
//          st_GrowthStretch.bBackLegFlag = FALSE;
//          st_GrowthStretch.timer = 0;
//          st_GrowthStretch.active = FALSE;
//          bBackAutoModeInit = true;  //为了避免机芯出现差错，机芯按摩从头开始
//         }
//         break;
//    default:
//      break;
//    }
//  }
//}



/******************************************************************************/

void Main_Valve_Proce(void)
{
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        Valve_SetBackMode(1);//bBackauto在自动时候都是1，控制肩部气囊在机芯超过一定位置时不能充气，在手、肩气囊控制函数中使用
    }
    else
    {
        Valve_SetBackMode(0);
    }
    unsigned char by_EngineeringAirBag = ReadEEByte(AIRBAG_STRETCH_ADDRESS + USER_DATA_BASE);//从内存中读取的气囊力度变量
    
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        if((Data_Get_ProgramExecTime() > VALVE_START_TIME) || !bMassagePositionUpdate )  
        {   //判断自动开始运行25s或者椅子到了最佳位置开始气囊动作
            goto VALVE_START; 
        }
        //    Valve_Control(VALVE_DISABLE,&st_AirBagAuto,by_EngineeringAirBag);
        
        Valve_Control(VALVE_DISABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
        Valve_Control(VALVE_DISABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
        
        Valve_BodyUpAirPumpACPowerOff();
        Valve_LegFootAirPumpACPowerOff();
        Valve_FootRollerProce(0, 0, &st_AirBagModeLegFootSeat);
        //Valve_LegKneadProce(0, 0, &st_AirBagModeLegFootSeat);
        return;
    }
    
VALVE_START:
    
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        Valve_SetEnableSholder(0);
    }
    else
    {
        Valve_SetEnableSholder(1);
        bAUTO1AirEnable = FALSE;
    }
    
    if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)//气囊部位是全身时
    {
        if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))//自动模式1执行拉伸程序
        {
            //自动程序中的拉腿程序
            Valve_StretchControlProce();  //执行拉退，气囊由算法控制
            if(st_Stretch.active == TRUE)
            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArm, 1); //在拉退时刻，由数组控制手臂气囊程序
            }
            else
            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
                Valve_Control(VALVE_ENABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
                Valve_FootRollerProce(bRollerEnable, 1, &st_AirBagModeLegFootSeat);
                //Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            }
        }
        else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_6)&&(bDemoStretch == true))
        {
            //自动程序中的拉腿程序
            Valve_StretchControlProce();  //执行拉退，气囊由算法控制
            if(st_Stretch.active == TRUE)
            {
                //Valve_Control(VALVE_ENABLE, &st_AirBagArm, 1); //在拉退时刻，由数组控制手臂气囊程序
            }
            else
            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
                Valve_Control(VALVE_ENABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
                Valve_FootRollerProce(bRollerEnable, 1, &st_AirBagModeLegFootSeat);
                //Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            }
        }
        else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_7)&&(bDemoStretch == true))
        {
            //自动程序中的拉腿程序
            Valve_StretchControlProce();  //执行拉退，气囊由算法控制
            if(st_Stretch.active == TRUE)
            {
                //Valve_Control(VALVE_ENABLE, &st_AirBagArm, 1); //在拉退时刻，由数组控制手臂气囊程序
                if(st_Stretch.step !=0)
                {
                    Valve_Control(VALVE_ENABLE, &st_AirBagArm, 1); //在拉退时刻，由数组控制手臂气囊程序
                }
                else
                {
                    Valve_Control(VALVE_DISABLE, &st_AirBagArm, by_EngineeringAirBag);  
                }
                
                
            }
            else
            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
                Valve_Control(VALVE_ENABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
                Valve_FootRollerProce(bRollerEnable, 1, &st_AirBagModeLegFootSeat);
                //Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            }
        }
        else//其他模式下的全身气囊时
        {  
            bAUTO1AirEnable = FALSE;
            if(st_Stretch.active||st_GrowthStretch.active)
            {
                st_Stretch.active = FALSE;
                st_GrowthStretch.active = FALSE;
                st_Stretch.init = FALSE;
                bKeyLegPadUp = FALSE ;
                bKeyLegPadDown = FALSE ;
                bLegPadLinkage = FALSE ;
                bKeyBackPadUp = FALSE ;
                bKeyBackPadDown = FALSE ;
            }
            Valve_Control(VALVE_ENABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
            Valve_FootRollerProce(bRollerEnable, 1, &st_AirBagModeLegFootSeat);
            //Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            
            Valve_Alone();
        }
    }
    else//非全身气囊时执行下面语句
    {
        bAUTO1AirEnable = FALSE;
        if(st_Stretch.active||st_GrowthStretch.active)
        {
            st_Stretch.active = FALSE;st_GrowthStretch.active = FALSE;
            st_Stretch.init = FALSE;
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
        }
        Valve_FootRollerProce(bRollerEnable, 0, &st_AirBagLegFoot);
        //w_KneadLegCount=0;
        //Valve_LegKneadProce(bLegKneadEnable, 0, &st_AirBagLegFoot);
        switch(nKeyAirBagLocate)
        {
        case  AIRBAG_LOCATE_NONE:
            Valve_Control(VALVE_DISABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagBackWaist, by_EngineeringAirBag);
            Valve_BodyUpAirPumpACPowerOff();
            Valve_LegFootAirPumpACPowerOff();
            break;
        case  AIRBAG_LOCATE_LEG_FOOT:
            Valve_Control(VALVE_ENABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagBackWaist, by_EngineeringAirBag);
            break;
        case AIRBAG_LOCATE_SEAT:
            Valve_Control(VALVE_DISABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagBackWaist, by_EngineeringAirBag);
            break;
        case AIRBAG_LOCATE_ARM_SHOLDER:
            Valve_Control(VALVE_DISABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagBackWaist, by_EngineeringAirBag);
            break;
        case AIRBAG_LOCATE_BACK_WAIST:
            Valve_Control(VALVE_DISABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_DISABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagBackWaist, by_EngineeringAirBag);
            break;
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_ARM_SHOLDER): 
            Valve_Control(VALVE_DISABLE, &st_AirBagSeat, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagLegFoot_ArmSholder, by_EngineeringAirBag);
            break;
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_SEAT):
            Valve_Control(VALVE_DISABLE, &st_AirBagArmSholder, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagLegFoot_Seat, by_EngineeringAirBag);
            break;
        case (AIRBAG_LOCATE_ARM_SHOLDER| AIRBAG_LOCATE_SEAT):
            Valve_Control(VALVE_DISABLE, &st_AirBagLegFoot, by_EngineeringAirBag);
            Valve_Control(VALVE_ENABLE, &st_AirBagArmSholder_Seat, by_EngineeringAirBag);
            break;    
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_ARM_SHOLDER | AIRBAG_LOCATE_SEAT):
            Valve_Control(VALVE_ENABLE, &st_AirBagLegFoot_ArmSholder_Seat, by_EngineeringAirBag);
            break;        
        }
    }
}

void Main_Massage_Position_Proce(void)
{
    bool bBackPadFinish,bLegPadFinish,bSliderFinish,bFlexPadFinish;
    bool bAdjFlex = 0;
    unsigned int w_BackPosition,w_LegPosition;
    
    if((bKeyBackPadUp == TRUE) || 
       (bKeyBackPadDown == TRUE) || 
           (bKeyLegPadUp == TRUE) || 
               (bKeyLegPadDown == TRUE) ||
                   (bKeyFlexOut == TRUE) ||
                       (bKeyFlexIn == TRUE) ||
                           (st_Stretch.active)||
                               (st_GrowthStretch.active)) 
    {
        bMassagePositionUpdate = 0;    //手动优先
        return;
    }
    if(GetbRockEnable())
    {
        return;
    }
    if(!bMassagePositionUpdate) 
    {
        return;
    }
    
#ifndef back_pluse
    BackMotor_Proce();
    w_BackPosition = BackMotor_Get_Position();//靠背时间计数
#else
    w_BackPosition = Input_GetBackPosition();//靠背脉冲计数
#endif
    
    LegMotor_Proce();//行走电机行走
    w_LegPosition = LegMotor_Get_Position(); 
    
    switch(nTargetMassagePosition)
    {
    case MASSAGE_POWER_ON_POSITION:  //开机运行
        if(Input_GetFlexInSwitch() == FLEX_AT_IN)
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
            bFlexPadFinish = FALSE;
        }
        break;
        
    case MASSAGE_QUICK_POSITION:    //QUICK模式使用（未使用）
        bBackPadFinish=1;
        BackMotor_Control(STATE_BACK_IDLE) ;
        w_LegPosition = LegMotor_Get_Position();
        if(w_LegPosition > (MASSAGE_LEG_QUICK_POSITION + 50))
        {
            LegMotor_Control(STATE_RUN_LEG_DOWN) ;
            bLegPadFinish = FALSE;
        }
        else if(w_LegPosition < (MASSAGE_LEG_QUICK_POSITION - 50))
        {
            LegMotor_Control(STATE_RUN_BACK_UP) ;
            bLegPadFinish = FALSE;
        }
        else
        {
            LegMotor_Control(STATE_BACK_IDLE) ;
            bLegPadFinish = TRUE;
        }
        break;  
        
    case MASSAGE_RESET_POSITION: 
        if(BackMotor_Control(STATE_RUN_BACK_UP) == TRUE)
        {
            bBackPadFinish = TRUE;
            if(SlideMotorControl(STATE_RUN_SLIDE_BACKWARD) == TRUE)  
            {
                bSliderFinish = TRUE;
            }
            else
            {
                bSliderFinish = FALSE;
            } 
        }
        else
        {
            bBackPadFinish = FALSE;
            bSliderFinish = FALSE;
        }
        if(LegMotor_Control(STATE_RUN_LEG_DOWN) == LEG_STOP_AT_DOWN)
        {
            bLegPadFinish = TRUE;
        }
        else
        {
            bLegPadFinish = FALSE;
        }
        
        if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A) == FLEX_STOP_AT_IN) //cyw
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
            bFlexPadFinish = FALSE;
        }
        break;
        
    case MASSAGE_INIT_POSITION://前滑电机到最前端，靠背最上端，小腿最下端，伸缩最里端
        FlexMotorSetDisable();//要打断自动找脚，否则在自动找脚时候关闭零重力伸缩不会和靠背和小腿一起收回
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            if(BackMotor_Control(STATE_RUN_BACK_UP) == TRUE)
            {
                bBackPadFinish = TRUE;
            }
            else
            {
                bBackPadFinish = FALSE;
            } 
            if(LegMotor_Control(STATE_RUN_LEG_DOWN) == TRUE)
            {
                bLegPadFinish = TRUE;
            }
            else
            {
                bLegPadFinish = FALSE;
            }
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A) == FLEX_STOP_AT_IN) //cyw
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }
        }
        else
        {
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
            bFlexPadFinish = FALSE;
        }
        break;
        
    case MASSAGE_OPTIMAL_POSITION://自动程序的椅子位置
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            
#ifndef back_pluse
            BackMotor_Proce();//时间计数
            w_BackPosition = BackMotor_Get_Position();//时间计数
#else
            w_BackPosition = Input_GetBackPosition();//靠背脉冲计数 
#endif         
            if(w_BackPosition >= (MASSAGE_BACK_OPTIMAL_POSITION + POSITION_CTRL_OFFSET))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                bBackPadFinish = FALSE;
            } 
            else if(w_BackPosition <= (MASSAGE_BACK_OPTIMAL_POSITION))  
            {
                BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                bBackPadFinish = FALSE;
            }
            else
            {
                BackMotor_Control(STATE_BACK_IDLE) ;
                bBackPadFinish = TRUE;
            } 
            
            w_LegPosition = LegMotor_Get_Position(); 
            if(w_LegPosition > (MASSAGE_LEG_OPTIMAL_POSITION + 50))
            {
                LegMotor_Control(STATE_RUN_LEG_DOWN) ;
                bLegPadFinish = FALSE;
            }
            else if(w_LegPosition < (MASSAGE_LEG_OPTIMAL_POSITION - 50))
            {
                LegMotor_Control(STATE_RUN_BACK_UP) ;
                bLegPadFinish = FALSE;
            }
            else
            {
                LegMotor_Control(STATE_BACK_IDLE) ;
                bLegPadFinish = TRUE;
            }
            bFlexPadFinish = TRUE;  
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
        } 
        break;
        
    case MASSAGE_OPTIMAL2_POSITION:
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
#ifndef back_pluse
            BackMotor_Proce();//时间计数
            w_BackPosition = BackMotor_Get_Position();//时间计数
#else
            w_BackPosition = Input_GetBackPosition();//靠背脉冲计数  
#endif      
            
            if((Zero_mark==1 && w_BackPosition<ZERO_POSITION_1)||
               (Zero_mark==2 && w_BackPosition<ZERO_POSITION_2)||
                   (Zero_mark==3 && w_BackPosition<ZERO_POSITION_3))
            {
                BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                bBackPadFinish = FALSE;
                nZero_OK = 0;
            }
            else if((Zero_mark==0)&&(w_BackPosition!=0)||
                    (Zero_mark==1 && w_BackPosition>ZERO_POSITION_1+30)||
                        (Zero_mark==2 && w_BackPosition>ZERO_POSITION_2+30)||
                            (Zero_mark==3 && w_BackPosition>ZERO_POSITION_3+30))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                bBackPadFinish = FALSE;
                nZero_OK=0;
            }
            else
            {
                BackMotor_Control(STATE_BACK_IDLE) ;
                bBackPadFinish = TRUE;
                nZero_OK =1;
            }
            
            w_LegPosition = LegMotor_Get_Position(); 
            if((Zero_mark==1 && w_LegPosition<700)||
               (Zero_mark==2 && w_LegPosition<950)||
                   (Zero_mark==3 && w_LegPosition<1200))
            {                
                LegMotor_Control(STATE_RUN_BACK_UP) ;
                bLegPadFinish = FALSE;
            }
            else if((Zero_mark==0 && w_LegPosition!=0)||
                    (Zero_mark==1 && w_LegPosition>700+50)||
                        (Zero_mark==2 && w_LegPosition>950+50)||
                            (Zero_mark==3 && w_LegPosition>1200+50))
            {
                LegMotor_Control(STATE_RUN_BACK_DOWN) ;
                bLegPadFinish = FALSE;
            }
            else 
            {
                LegMotor_Control(STATE_BACK_IDLE) ;
                bLegPadFinish = TRUE;
            }
            bFlexPadFinish = TRUE;    
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;		
            bLegPadFinish = FALSE;
        }
        break;  
        
    case MASSAGE_OPTIMAL_MED_POSITION:   //未使用
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            if(w_BackPosition > (MASSAGE_BACK_OPTIMAL_MED_POSITION + POSITION_CTRL_OFFSET))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                bBackPadFinish = FALSE;
            }
            else if(w_BackPosition < (MASSAGE_BACK_OPTIMAL_MED_POSITION - POSITION_CTRL_OFFSET))
            {
                BackMotor_Control(STATE_RUN_BACK_DOWN) ;
                bBackPadFinish = FALSE;
            }
            else
            {
                BackMotor_Control(STATE_BACK_IDLE) ;
                bBackPadFinish = TRUE;
            } 
            
            w_LegPosition = LegMotor_Get_Position(); 
            if(w_LegPosition > (MASSAGE_LEG_OPTIMAL_MED_POSITION + POSITION_CTRL_OFFSET))
            {
                LegMotor_Control(STATE_RUN_LEG_DOWN) ;
                bLegPadFinish = FALSE;
            }
            else if(w_LegPosition < (MASSAGE_LEG_OPTIMAL_MED_POSITION - POSITION_CTRL_OFFSET))
            {
                LegMotor_Control(STATE_RUN_BACK_UP) ;
                bLegPadFinish = FALSE;
            }
            else
            {
                LegMotor_Control(STATE_BACK_IDLE) ;
                bLegPadFinish = TRUE;
            }
            bFlexPadFinish = TRUE;  
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
        }
        break;  
        
    case MASSAGE_MAX_POSITION:  //未使用
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            if(BackMotor_Control(STATE_RUN_BACK_DOWN) == TRUE)
            {
                bBackPadFinish = TRUE;
            }
            else
            {
                bBackPadFinish = FALSE;
            } 
            if(LegMotor_Control(STATE_RUN_LEG_UP) == LEG_STOP_AT_UP)
            {
                bLegPadFinish = TRUE;
            }
            else
            {
                bLegPadFinish = FALSE;
            }
            bFlexPadFinish = TRUE; 
        }
        else
        {
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
            bFlexPadFinish = FALSE;
        }
        break;
        
    case MASSAGE_UNKNOW_POSITION:bMassagePositionUpdate = 0;break;
    case MASSAGE_ANY_POSITION:bMassagePositionUpdate = 0;break;
    case  MASSAGE_MEMORY_POSITION:   //记忆模式回到记忆的椅子位置
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            w_BackPosition = BackMotor_Get_Position();
            if(nM_BackAngle > POSITION_CTRL_OFFSET)
            {
                if(w_BackPosition > (nM_BackAngle + 80))//POSITION_CTRL_OFFSET))
                {
                    if(BackMotor_Control(STATE_RUN_BACK_UP)==true)
                    {
                        bBackPadFinish = true;
                    }
                    else
                    {
                        bBackPadFinish = FALSE;
                    }
                    
                }
                else if(w_BackPosition < (nM_BackAngle - POSITION_CTRL_OFFSET))
                {
                    if(BackMotor_Control(STATE_RUN_BACK_DOWN)==true)
                    {
                        bBackPadFinish = true;
                    }
                    else
                    {
                        bBackPadFinish = FALSE;
                    }
                }
                else
                {
                    BackMotor_Control(STATE_BACK_IDLE) ;
                    bBackPadFinish = TRUE;
                }  
            }
            else
            {
                if(BackMotor_Control(STATE_RUN_BACK_UP) == TRUE)
                {
                    bBackPadFinish = TRUE;
                }
                else
                {
                    bBackPadFinish = FALSE;
                } 
            } 
            
            w_LegPosition = LegMotor_Get_Position(); 
            if(nM_LegAngle > POSITION_CTRL_OFFSET)
            {
                if(w_LegPosition > (nM_LegAngle + POSITION_CTRL_OFFSET))
                {
                    if(LegMotor_Control(STATE_RUN_LEG_DOWN)==true)
                    {
                        bLegPadFinish = true;
                    }
                    else
                    {
                        bLegPadFinish = FALSE;
                    }
                }
                else if(w_LegPosition < (nM_LegAngle - POSITION_CTRL_OFFSET))
                {
                    if(LegMotor_Control(STATE_RUN_BACK_UP)==true)
                    {
                        bLegPadFinish = true;
                    }
                    else
                    {
                        bLegPadFinish = FALSE;
                    }
                }
                else
                {
                    LegMotor_Control(STATE_BACK_IDLE) ;
                    bLegPadFinish = TRUE;
                }          
            }
            else
            {
                if(LegMotor_Control(STATE_RUN_LEG_DOWN) == TRUE)
                {
                    bLegPadFinish = TRUE;
                }
                else
                {
                    bLegPadFinish = FALSE;
                }         
            }
            
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A) == FLEX_STOP_AT_IN) //cyw
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }     
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
        }
        break;  
    default:  
        bMassagePositionUpdate = 0;
        break;
    }
    if((bSliderFinish == TRUE) && (bBackPadFinish == TRUE) && (bLegPadFinish == TRUE)&& (bFlexPadFinish == TRUE))
    {
        bMassagePositionUpdate = 0;
        if(bAdjFlex)
        {
            FlexMotorSetEnable(); 
        }
    }
}

//靠背电动缸控制程序
void Main_BackPad_Proce(void)
{
    BackMotor_Proce();
    if(st_Stretch.active) return;
    if(st_GrowthStretch.active) return;
    if(bMassagePositionUpdate) return;
    if(bKeyBackPadUp == TRUE)
    {
        if(BackMotor_Control(STATE_RUN_BACK_UP) == TRUE)
        {
            if(SlideMotorControl(STATE_RUN_SLIDE_BACKWARD) == TRUE)
            {
                nBuzzerMode = BUZZER_MODE_FAST ;
                bSendBuzzerMode = TRUE ; 
            }
            else
            { 
                if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
                {
                   nBuzzerMode = BUZZER_MODE_SLOW ;
                   bSendBuzzerMode = TRUE ;
                }
            }
        }
        else
        {
            if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
            {			  
                nBuzzerMode = BUZZER_MODE_SLOW ;
                bSendBuzzerMode = TRUE ;
            }
        }
    }
    if(bKeyBackPadDown == TRUE)
    {
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)//(SlideMotor_Get_Location() == SLIDE_MOTOR_AT_FORWARD)
        {
            SlideMotorControl(STATE_LEG_IDLE);
            if(BackMotor_Control(STATE_RUN_BACK_DOWN) == TRUE)
            {
                if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
                {
                  nBuzzerMode = BUZZER_MODE_FAST ;
                  bSendBuzzerMode = TRUE ;
                }
            }
            else
            {
                if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
                {
                    nBuzzerMode = BUZZER_MODE_SLOW ;
                    bSendBuzzerMode = TRUE ;
                }
            }
        }
        else
        {
            if( (bBackLegPadSettle == FALSE)&& (GetnRockModeEnterExit() == ExitRock))
            {
                LegMotor_Control(STATE_LEG_IDLE);
                BackMotor_Control(STATE_BACK_IDLE);
                nBuzzerMode = BUZZER_MODE_SLOW ;
                bSendBuzzerMode = TRUE ;
            }
        }
    }
    if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE))
    {
            BackMotor_Control(STATE_BACK_IDLE) ;
            SlideMotorControl(STATE_SLIDE_IDLE);
    }
}

/******************************************************************************/
void BodyDataRefresh(void)
{
    
    unsigned short by_TopPosition = TOP_POSITION;

    if(nShoulderPosition >= (by_TopPosition - MAX_SHOULDER_ADJUST_DIFF))
    {
        nShoulderPositionTop = by_TopPosition ;
        nShoulderPositionBottom = nShoulderPosition - MAX_SHOULDER_ADJUST_DIFF ;
    }
    else if(nShoulderPosition < MAX_SHOULDER_ADJUST_DIFF)
    {
        nShoulderPositionTop = nShoulderPosition + MAX_SHOULDER_ADJUST_DIFF ;
        nShoulderPositionBottom = 0 ;
    }
    else
    {
        nShoulderPositionTop = nShoulderPosition + MAX_SHOULDER_ADJUST_DIFF ;
        nShoulderPositionBottom = nShoulderPosition - MAX_SHOULDER_ADJUST_DIFF ;
    }
}

//bool isZeroPosition(void)
//{
//    
//#ifdef back_pluse
//    
//    unsigned int w_BackPosition_3= Input_GetBackPosition();//BackMotor_Get_Position();
//#else
//    unsigned int w_BackPosition_3= BackMotor_Get_Position();
//#endif
//    unsigned int w_LegPosition_3 = LegMotor_Get_Position(); 
//    
//    
//    bool result;    
//    result = (w_BackPosition_3 < (MASSAGE_BACK_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
//    if(result) result = (w_BackPosition_3 > (MASSAGE_BACK_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
//    if(result) result = (w_LegPosition_3 > (MASSAGE_LEG_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
//    // if(result) result = (w_LegPosition_3 < (MASSAGE_LEG_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
//    return(result);   
//}


/*****************************************************************************/
uint8_t Zero_Grade(uint16_t wBackPosition)
{
    
    // #ifdef back_pluse
    //  
    //	unsigned int w_BackPosition_3= Input_GetBackPosition();//BackMotor_Get_Position();
    //#else
    //    unsigned int w_BackPosition_3= BackMotor_Get_Position();
    //#endif
    //	unsigned int w_LegPosition_3 = LegMotor_Get_Position(); 
    
    if(nCurBackLocate>=ZERO_POSITION_3) return 3;
    else if(nCurBackLocate>=ZERO_POSITION_2) return 2;
    else if(nCurBackLocate>=ZERO_POSITION_1) return 1;
    else   return 0;
    
    
    //    bool result;    
    //    result = (w_BackPosition_3 < (MASSAGE_BACK_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
    //    if(result) result = (w_BackPosition_3 > (MASSAGE_BACK_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
    //    if(result) result = (w_LegPosition_3 > (MASSAGE_LEG_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
    //   // if(result) result = (w_LegPosition_3 < (MASSAGE_LEG_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
    //    return(result);   
}
/*******************************************************************************/
void Main_Close_Power(void)
{
    //bool bEngineeringSettle = ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS);
    nKeyBackLocate = LOCATE_NONE;

    //气囊按摩停止
    nKeyAirBagLocate = AIRBAG_LOCATE_NONE;
    //振动功能停止
    //加热功能停止
    //bKeySeatVibrate = FALSE;
    bKeyWaistHeat = FALSE;
    //定时变量复位
    Data_Set_Start(0,0);
   bRollerEnable = FALSE; 
    //nRollerPWM = 0;
    //Valve_SetRollerPWM(nRollerPWM); 
    //bRunTimeChange = TRUE ;
}

void BackManualModeNoAction(void)
{
    nBackMainRunMode = BACK_MAIN_MODE_MANUAL ;
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION ;
    nKeyKneadKnockSpeed = SPEED_0 ;
    nCurKneadKnockSpeed = SPEED_0 ;
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_NO_ACTION ;
    ManualDirector[0].nKneadMotorState = KNEAD_STOP ;//KNEAD_STOP_AT_MAX ;
    ManualDirector[0].nKneadMotorCycles = 0 ;
    ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    nMaxActionStep = 1 ;
    nStartActionStep = 0 ;
    bBackManualModeInit = TRUE ;
}
/****************************
n485_2ms();

*****************************/
void n485_2ms()
{
    send_time_flag=true; 
}
/******************************

*********************************/
uint8_t Linbus_counter;
void Main_Send_Leg(void)
{

    unsigned char buffer;
    unsigned char cheksum;
    cheksum=0;
    if( bGet485Send()==false )//发送标志位有效
    {
        if(send_time_flag == true)//等待一段时间2ms等待发送完成，使能接收
        {
            send_time_flag = false ;
            UartLeg_CLR_TX_EN();
            bSet485Send(true);
        }
    }
    else
    {
        send_time_flag =false;  
    }
    
    
    if(bMasterSendLegPacket) 
    {  
        
//        if(Linbus_counter==1)
//        {
//            Linbus_counter=0;
//        }
//        else                 
//        {
//            Linbus_counter++; 
//        }
        if(Linbus_counter==0)
        {
            Linbus_counter=1;
        }
        else if(Linbus_counter==1)
        {
            Linbus_counter=2;
        }
        else 
        {
            Linbus_counter = 0;
        }
        switch (Linbus_counter)
        {
        case 0:  //3D机芯
            OutLegBuffer_3D[0] = SOI ;
            OutLegBuffer_3D[1] =0x02;//addr
            OutLegBuffer_3D[2] =0x02;
            OutLegBuffer_3D[3] =0x00;
            OutLegBuffer_3D[4] =0x00;
            cheksum+=OutLegBuffer_3D[1] ;//=0x02;//addr
            cheksum+=OutLegBuffer_3D[2];
            cheksum+=OutLegBuffer_3D[3];
            cheksum+=OutLegBuffer_3D[4];    
            cheksum = ~cheksum;
            cheksum &= 0x7f;
            OutLegBuffer_3D[5]=cheksum;
            OutLegBuffer_3D[6] = EOI;
            UartLeg_Transmit_Packet(OutLegBuffer_3D,7);           
            break;
            
        case 1:   //扶手
            OutArmBuffer[0] = 0xF0;
            OutArmBuffer[1] = 0X0C;//12
            OutArmBuffer[2] = outarmcmd;
            OutArmBuffer[3] = 0;
            OutArmBuffer[4] = 0;
            OutArmBuffer[5] = EOI;
            OutArmBuffer[6] = 0xaa;
            OutArmBuffer[7] = 0x55;
            nOutArmBufferCount = 8;
            
            UartLeg_Transmit_Packet(OutArmBuffer,nOutArmBufferCount);
            outarmcmd = 0x0;
            outarmcmdcount++; 
            break;
        case 2:
            OutVoiceBuffer[0] = 0xF0;
            OutVoiceBuffer[1] = 0x09;
            OutVoiceBuffer[2] = 0x02;
            OutVoiceBuffer[3] = 0x00;
            if((nChairRunState == CHAIR_STATE_SLEEP)||(nChairRunState == CHAIR_STATE_IDLE))
            {
               OutVoiceBuffer[3] |= 0<<0;
            }
            else
            {
               OutVoiceBuffer[3] |= 1<<0;
            }
            OutVoiceBuffer[3] |= ((bKeyWaistHeat & 0x01)<<1);
             
            if(bLanguageFlag == Language_Chinese)
            {  
               OutVoiceBuffer[4] = 0x01;
               OutVoiceBuffer[3] |= 0x02<<2;//1英文 2中文
            }
            else if(bLanguageFlag == Language_English)
            {
               OutVoiceBuffer[4] = 0x01;
               OutVoiceBuffer[3] |= 0x01<<2;
            }
            else
            {
                __NOP();
               OutVoiceBuffer[4] = 0x00;
            }
           
//            if((nChairRunState == CHAIR_STATE_SLEEP)||(nChairRunState == CHAIR_STATE_IDLE)||(nChairRunState == CHAIR_STATE_SETTLE))
//            {
//               OutVoiceBuffer[3] |= 0<<6;
//            }
//            else
//            {
            if(bBlueToothStatus == 1)
            {
               OutVoiceBuffer[3] |= 1<<6;
            }
            else
            {
               OutVoiceBuffer[3] |= 0<<6;
            }
            //}
            OutVoiceBuffer[3] &= 0x7f;
            
            cheksum+=OutVoiceBuffer[1];
            cheksum+=OutVoiceBuffer[2];
            cheksum+=OutVoiceBuffer[3];
            cheksum+=OutVoiceBuffer[4];
            cheksum = ~cheksum;
            cheksum &= 0x7f;
            OutVoiceBuffer[5] = cheksum;
            OutVoiceBuffer[6] = 0xF1;
            UartLeg_Transmit_Packet(OutVoiceBuffer,7);
            
            //                        OutLegBuffer[0] = SOI ;
            //                        OutLegBuffer[1] =0x01;
            //                        OutLegBuffer[2] =0x04;
            //                        //buffer 1
            //                        OutLegBuffer[3]=0;
            //                        OutLegBuffer[3] = Roller_GetSpeed() & 0x03;
            //                        buffer = Roller_GetMode() << 2;
            //                        OutLegBuffer[3] |= buffer;
            //                        OutLegBuffer[3] |= 1 << 6;  //allways on
            //                        //buffer 2
            //                        OutLegBuffer[4]=0;
            //                        OutLegBuffer[4] = Flex_GetDirection();
            //                        buffer = Flex_GetCurrent() << 2;
            //                        OutLegBuffer[4] |= buffer;
            //                        if(Flex_GetDisableAngle())  OutLegBuffer[4] |= (1<<5);
            //                        //buffer 3
            //                        OutLegBuffer[5] =0;
            //                        OutLegBuffer[5] = LegKnead_GetSpeed() & 0x03;
            //                        buffer = LegKnead_GetMode() << 2;
            //                        OutLegBuffer[5] |= buffer;
            //                        buffer = LegKnead_GetPower() << 4;
            //                        OutLegBuffer[5] |= buffer;
            //                        
            //                        //buffer 3
            //                        OutLegBuffer[6]=0;
            //                        unsigned char valve;
            //                        valve = BITS_ValveData[2].nByte;
            //                        
            //                        OutLegBuffer[6] = valve&0x3f;
            //                        cheksum += OutLegBuffer[1];
            //                        cheksum += OutLegBuffer[2];
            //                        cheksum  += OutLegBuffer[3];
            //                        cheksum  += OutLegBuffer[4];
            //                        cheksum  += OutLegBuffer[5];
            //                        cheksum  += OutLegBuffer[6];
            //                        cheksum = ~cheksum;
            //                        cheksum &= 0x7f;
            //                        OutLegBuffer[7]=cheksum;
            //                        
            //                        OutLegBuffer[8] = EOI;
            //                        UartLeg_Transmit_Packet(OutLegBuffer,9);        
            break;
        default:
            break;
        }
        bMasterSendLegPacket = FALSE ; 
    }
}
/*****************************************************************************/

bool isFIRSTZeroPosition(void)
{
    unsigned int w_BackPosition= Input_GetBackPosition();
    unsigned int w_LegPosition = LegMotor_Get_Position(); 
    bool result;    
    result = (w_BackPosition < (ZERO_POSITION_1 + 30));
    if(result) result = (w_BackPosition > (ZERO_POSITION_1 - 30));
    if(result) result = (w_LegPosition > (MASSAGE_LEG_OPTIMAL_POSITION - POSITION_DISPLAY_OFFSET));
    if(result) result = (w_LegPosition < (MASSAGE_LEG_OPTIMAL_POSITION + POSITION_DISPLAY_OFFSET));
    
    return(result);   
}
bool isZeroPosition(void)
{
    unsigned int is_BackLocation = Input_GetBackPosition();
    unsigned int w_LegPosition = LegMotor_Get_Position(); 
    bool result;        
    result = (is_BackLocation < (ZERO_POSITION_2 + 30));
    if(result) result = (is_BackLocation > (ZERO_POSITION_2 - 30));   
    if(result) result = (w_LegPosition > (MASSAGE_LEG_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
    if(result) result = (w_LegPosition < (MASSAGE_LEG_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
    return(result);   
}


void Main_Send(void)
{
    unsigned int Send_BackLocation = BackMotor_Get_Location();
    if(bMasterSendPacket)//控制此函数每50ms向手控器发送一次数据
    {
        //memset(OutBuffer,0,sizeof(OutBuffer));
        OutBuffer[0] = SOI ;
        
        //标识 1	按摩椅运行状态 1	按摩手法 3	按摩程序 3
        if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
        {
            OutBuffer[1] = 0<<6;//第一个字节的第6位，椅子状态，休眠为0，非休眠为1
        }
        else
        {
            OutBuffer[1] = 1<<6;
        }
        //+++++++++++++++++++++++++++++++++++++++
        /*
        if(nHeat_Degree == HEAT_LOW)
        {
        OutBuffer[1] |= 1<<1;
    }
      else if(nHeat_Degree == HEAT_MIDDLE)
        {
        OutBuffer[1] |= 2<<1;
    }
      else if(nHeat_Degree == HEAT_HIGH)
        {
        OutBuffer[1] |= 3<<1;
    }
      else//     if(nHeat_Degree == HEAT_OFF)
        {
        OutBuffer[1] |= 0<<1;
    }
        */   
        //-----------------------------------------
        /*****************************************************/
        //按摩手法显示
        if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            
            OutBuffer[1] |= 0<<3; //第一个字节的3、4、5位是按摩的手法，3D时按摩手法为停止
        }
        else
        {
            switch(nCurSubFunction)
            {
                //00：停止
                //01：揉捏
                //02：敲击
                //03：揉敲同步
                //04：叩击
                //05：指压
                //06：韵律按摩
                //07：保留
            case BACK_SUB_MODE_KNEAD			: OutBuffer[1] |= 1<<3;break;
            case BACK_SUB_MODE_KNOCK			: OutBuffer[1] |= 2<<3;break;
            case BACK_SUB_MODE_WAVELET		        : OutBuffer[1] |= 3<<3;break;
            case BACK_SUB_MODE_SOFT_KNOCK		        : OutBuffer[1] |= 4<<3;break;
            case BACK_SUB_MODE_PRESS			: OutBuffer[1] |= 5<<3;break;
            case BACK_SUB_MODE_MUSIC			: OutBuffer[1] |= 6<<3;break;
            case BACK_SUB_MODE_RUBBING                      : OutBuffer[1] |= 7<<3;break;
            default                                         : OutBuffer[1] |= 0<<3;break; 
            }        
        }
        if(GetbRockEnable() == true)
        {
            OutBuffer[1] |= 0x01;
        }
        else
        {
            OutBuffer[1] &= 0xfe;
        }
        
        
        /*
        if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)
        {
        OutBuffer[1] |=  7;
    }
        else if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
        {           
        BYTE mode = (nBackSubRunMode + 1);
        
        if(nChairRunState == CHAIR_STATE_DEMO)
        {
        mode &= bDisplayFlash;
    }
        
        OutBuffer[1] |= mode&0x7;
    }
        else if(nChairRunState == CHAIR_STATE_RUN)
        {
        OutBuffer[1] |=  7;
    }
        */
        //标识 1 加热 1	保留 1	按摩机芯速度 3 	揉捏头宽度位置 2
        //00-03 自定义
        unsigned char speed;
        if(nBackMainRunMode == BACK_MAIN_MODE_IDLE)
        {
            speed = 0;
        }
        else 
        {
            speed = nCurKneadKnockSpeed;
        }
        
        if(((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nMaunalSubMode == nMaunalSubMode_PRESS))||(nBackMainRunMode == BACK_MAIN_MODE_3D))
        {
            OutBuffer[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x0)<<2)|(Input_GetKneadPosition()&0x3);
        }
        else
        {
            if(nCurSubFunction == BACK_SUB_MODE_PRESS)
            {
                OutBuffer[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x0)<<2)|(Input_GetKneadPosition()&0x3);
            }
            else
            {
                OutBuffer[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x7)<<2)|(Input_GetKneadPosition()&0x3);
            }      
        }  
        
        if(bRollerEnable)
        {
            OutBuffer[2] |= (1<<5);
        }
        else
        {
            OutBuffer[2] &= ~(1<<5);
        } 
        // 标识 1	负离子开关 1 	 振动（或扭腰）强度 3	气压强度 3
        OutBuffer[3] = 0;
        OutBuffer[3] = (nKeySeatVibrateStrength&0x7)<<3;
        
        
        if(bOzonEnable)
        {
            OutBuffer[3] |= (1<<6);
        }
        else
        {
            OutBuffer[3] &= ~(1<<6);
        }
        
        if(nKeyAirBagLocate != AIRBAG_LOCATE_NONE)
        {
            OutBuffer[3] |= (Valve_GetAirBagStrength()&0x7);
        }
        //标识 1	机芯按摩部位 2	运行时间高5位 5
        //显示位置
        OutBuffer[4] = 0;           
        if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
        {
            if((nBackSubRunMode == BACK_SUB_MODE_AUTO_0) ||
               (nBackSubRunMode == BACK_SUB_MODE_AUTO_1) ||
                   (nBackSubRunMode == BACK_SUB_MODE_AUTO_2) ||
                       (nBackSubRunMode == BACK_SUB_MODE_AUTO_3) ||
                           (nBackSubRunMode == BACK_SUB_MODE_AUTO_4) ||              
                               (nBackSubRunMode == BACK_SUB_MODE_AUTO_5))
            {
                OutBuffer[4] = 1<<5;           
            }
            else
            {
                OutBuffer[4] = 2<<5;
            }
        }
        else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            OutBuffer[4] = 1 << 5;
        }
        else if(nBackMainRunMode == BACK_MAIN_MODE_IDLE)
        {
            OutBuffer[4] = 0 << 5;
        }
        else
        {
            switch(nKeyBackLocate)
            {
            case LOCATE_FULL_BACK:
                OutBuffer[4] = 1<<5;           
                break ;
            case LOCATE_PARTIAL:
                OutBuffer[4] = 2<<5;
                break ;
            case LOCATE_POINT:
                OutBuffer[4] = 3<<5; ;
                break ;
            default://include LOCATE_NONE
                break ;
            }
        }
#ifdef FORCE_CONTROLLER
        unsigned int time; 
        time = KneadMotor_GetCurrent();
        time *= 60;
#else
        unsigned int time = Data_Get_TimeSecond();
#endif    
        OutBuffer[4] |=(time>>7)& 0x1f;
        //标识 1	运行时间低7位 7
        OutBuffer[5] = time & 0x7f;
        
        OutBuffer[6] = 0x00;
        if( (bLeftFootAirBagValve) | (bRightFootAirBagValve) |(bFootHeelAirBagValve))
        {
            OutBuffer[6] |= 0x01;
        }
        
        if( (bLegLeftAirBagValve) |(bLegRightAirBagValve))
        {
            OutBuffer[6] |= 0x02;
        }
        if((bLeftThighAirBagValve) | (bRightThighAirBagValve ))
        {
            OutBuffer[6] |= 0x04;
        }
        if((bRightArmUpAirBagValve1) | (bRightArmUpAirBagValve2)| (bRightArmUpAirBagValve3)|(bLeftArmUpAirBagValve1) |(bLeftArmUpAirBagValve2 )|(bLeftArmUpAirBagValve3))
        {
            OutBuffer[6] |= 0x10;
        }
        if(bRollerEnable)
        {
            if(Valve_RollerIsAuto())
            {
                // if(bDisplayFlash) OutBuffer[6] |= (3<<5);
                // else  OutBuffer[6] |= (0<<5);
                unsigned int rollerPWM;
                rollerPWM = displayPWM;
                OutBuffer[6] &= 0x9f;
                if(rollerPWM == ROLLER_SPEED_STOP) OutBuffer[6] |= (0 << 5);
                else if(rollerPWM == ROLLER_SPEED_SLOW) OutBuffer[6] |= (1 << 5);
                else if(rollerPWM == ROLLER_SPEED_MID) OutBuffer[6] |= (2 << 5);
                else if(rollerPWM == ROLLER_SPEED_FAST) OutBuffer[6] |= (3 << 5);
            }
            else
            {
                OutBuffer[6] |= (Valve_GetRollerLevel() << 5);
            }
        }
        else
        {
            OutBuffer[6] |= (0 << 5);
        }
        OutBuffer[7] = 0x0;
        if((bLeftSholderAirBagValve) | (bRightSholderAirBagValve))
        {
            OutBuffer[7] |=  0x10;
        }
//        if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
//        {
//            OutBuffer[7] |= 0x70;
//        }
        /* if((bBackWaistRightUp) | (bBackWaistRightDown) |(bBackWaistLeftUp) | (bBackWaistLeftDown))
        {
        OutBuffer[7] |=  0x20;
    }
        */
        OutBuffer[7] &= 0xf0;
        
        BYTE state = nChairRunState;
        if(nChairRunState == CHAIR_STATE_SLEEP) 
        {
            state = CHAIR_STATE_IDLE;
        }
        if(nChairRunState == CHAIR_STATE_DEMO) 
        {
            state = CHAIR_STATE_RUN;
        }
        if(nChairRunState == CHAIR_STATE_CALIBRATION) 
        {
            state = CHAIR_STATE_RUN;
        }
        OutBuffer[7] |= (state&0x0f);
        /*
        unsigned int data = Input_GetWalkMotorPosition();
        data /= 33;//38;//31;
        if(data >= 12) data = 12;
        OutBuffer[8] = data;   
        OutBuffer[9] = 0;
        */
        OutBuffer[8] &= 0x00;
        unsigned int data = Input_GetWalkMotorPosition();
//        data /= 31;
        data /= 28;
        if(data >= 13) data = 13;
        OutBuffer[8] = data;  
        if(bZero_ShowFlag == 1)
        {
            if(bMassagePositionUpdate)
            {
                if((nTargetMassagePosition == MASSAGE_OPTIMAL2_POSITION)&&(Zero_mark==1))
                {
                    if(GetbRockEnable() == false)OutBuffer[8] |= (1<<5);	
                }
                else if((nTargetMassagePosition == MASSAGE_OPTIMAL2_POSITION)&&(Zero_mark==2))
                {
                    if(GetbRockEnable() == false)OutBuffer[8] |= (1<<6);	
                }
                else if((nTargetMassagePosition == MASSAGE_INIT_POSITION)&&(Zero_mark==0))
                {
                    OutBuffer[8] |= 0<<5; 
                    OutBuffer[8] |= 0<<6; 
                } 
            }
            else if(isFIRSTZeroPosition())//零重力提示,
            {
                if((GetbRockEnable() == false)&&(st_Stretch.active == false))
                    OutBuffer[8] |= 1<<5;  
            }
            else if(isZeroPosition())
            {
                if((GetbRockEnable() == false)&&(st_Stretch.active == false))
                    OutBuffer[8] |= 1<<6;	
            }
            else
            {
                if((GetbRockEnable() == false)&&(st_Stretch.active == false))
                    OutBuffer[8] |= 0<<6;
                
            }
        }
        else
        {
            OutBuffer[8] |= 0<<5; 
            OutBuffer[8] |= 0<<6;
        }
        
        OutBuffer[9] = 0;
        if((BodyDetectStep == DETECT_SHOULDER)&&((nBackMainRunMode == BACK_MAIN_MODE_3D)||(nBackMainRunMode == BACK_MAIN_MODE_AUTO)))//cyw 2017 12 01 
        {
            if((ShoulderSteps >= BODY_DETECT_PREPARE) && (ShoulderSteps < BODY_DETECT_OVER))
            { 
                OutBuffer[9] = 1<<6;
            }
            else
            {
                OutBuffer[9] = 0<<6;
            }
            
            if(ShoulderSteps == BODY_DETECT_ADJ)
            {
                OutBuffer[9] |= 1<<5;
                data = nShoulderPositionTop - nShoulderPositionBottom;
                time = data /15;
                data = (Input_GetWalkMotorPosition()-nShoulderPositionBottom) / time;
                if(data == 0) data = 1;
                if(data > 15) data = 15;
                
                OutBuffer[9] |= data&0x0f;
                
            }
        }
        //标识 1	运行指示 1	小腿电动缸运行方向指示 3	靠背电动缸运行方向指示 3
        OutBuffer[10] = 0;
        /*      if(isZeroPosition())
        {
        if((bRockEnable == FALSE)&&(bZeroflash == FALSE)&&(st_Stretch.active == FALSE) ) 
        {
        OutBuffer[10] = 1<<6; 
    }
        else
        {
        OutBuffer[10] = 0<<6;
    }
    }
        else//到位   闪烁 
        {
        if((bZeroflash == TRUE)&&(BackMotor_GetDirection() == BACK_MOTOR_GO_DOWN )  )
        {
        if(bZeroTimer100MS == TRUE)
        {
        bZeroTimer100MScount++;
    }            
        if(bZeroTimer100MScount<10)
        {
        if(bRockEnable == FALSE)
        {
        OutBuffer[10] = 1<<6;
    }
        else
        {
        OutBuffer[10] = 0<<6;
    }
        //OutBuffer[10] = 1<<6; 
    }            
        else if( (bZeroTimer100MScount>=10)&&(bZeroTimer100MScount<20))
        {
        OutBuffer[10] = 0<<6;
    }
        else
        {
        bZeroTimer100MScount =0;
    }            
        
    }
        else if((bZeroflash == TRUE)&&(BackMotor_GetDirection() == BACK_MOTOR_GO_UP )&&(Send_BackLocation > (MASSAGE_BACK_OPTIMAL1_LOCATION - 30))  )
        {
        if(bZeroTimer100MS == TRUE)
        {
        bZeroTimer100MScount++;
    }           
        if(bZeroTimer100MScount<10)
        {
        if(bRockEnable == FALSE)
        {
        OutBuffer[10] = 1<<6;
    }
        else
        {
        OutBuffer[10] = 0<<6;
    }
        //OutBuffer[10] = 1<<6; 
    }            
        else if( (bZeroTimer100MScount>=10)&&(bZeroTimer100MScount<20))
        {
        OutBuffer[10] = 0<<6;
    }
        else
        {
        bZeroTimer100MScount =0;
    }            
        
    }
        else
        {
        bZeroTimer100MScount =0;
        OutBuffer[10] = 0<<6;
    }
        
        
        
    }
        */
        /*  if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
        {
        if(SlideMotor_GetDirection() == SLIDE_MOTOR_GO_FORWARD)
        {
        OutBuffer[10] = 0x01<<4;
    }
        else
        {
        OutBuffer[10] = 0x02<<4;
    }
    }*/
        
        OutBuffer[10] = 0;
        if(BackMotor_GetPower() == BACK_MOTOR_POWER_ON)
        {
            if(BackMotor_GetDirection() == BACK_MOTOR_GO_UP)
            {
                OutBuffer[10] |= 0x01;
            }
            else
            {
                OutBuffer[10] |= 0x02;
            }
        }
        
        if(LegMotor_GetPower() == LEG_MOTOR_POWER_ON)
        {
            if(LegMotor_GetDirection() == LEG_MOTOR_GO_UP)
            {
                OutBuffer[10] |= (0x01<<2);
            }
            else
            {
                OutBuffer[10] |= (0x02<<2);
            }
        }
        
        //标识	1 蜂鸣器模式 2 音乐开关 1	音量 4
        if(bSendBuzzerMode == TRUE)
        {
            OutBuffer[11] = (nBuzzerMode&0x3)<<5;
            bSendBuzzerMode = FALSE ;
        }
        else
        {
            OutBuffer[11] = 0;
        }
        
        if(BlueToothMuteState() == BlueTooth_Speak_Out_On)
        {
            OutBuffer[11] |= 1 << 4;
        }
        else
        {
            OutBuffer[11] &= BlueTooth_MutePin_Value; //BlueTooth_MutePin_Value is equal to "0xef"
        }
        switch(w_PresetTime)
        {
        case RUN_TIME_10: OutBuffer[12] = 1;  break;
        case RUN_TIME_20: OutBuffer[12] = 2;  break;
        case RUN_TIME_30: OutBuffer[12] = 3;  break;
        default: OutBuffer[12] = 0; break;
        }
        OutBuffer[12] |= ((nKeyAirBagLocate & 0xff) << 2);
        //滚轮方向
        /* if(bRollerEnable)
        {
        // if(ReadRollerPhase() == 1)
        {
        OutBuffer[13] = 1;
    }
        // else if(ReadRollerPhase() == 0)
        {
        OutBuffer[13] = 2;
    }
        // else
        OutBuffer[13] = 0;
    }
        else
        {
        OutBuffer[13] = 0;
    }*/
        BYTE mode;
        if(nChairRunState == CHAIR_STATE_DEMO)
        {
            mode = 1 & bDisplayFlash;
            OutBuffer[13] |= mode << 2;
            time = Data_Get_ProgramExecTime()/60;
            OutBuffer[4] &= 0xE0;
            OutBuffer[4] |=(time>>7)& 0x1f;
            //标识 1	运行时间低7位 7
            OutBuffer[5] = time & 0x7f;
        }
        else
        { 
            OutBuffer[13] &= 0x03;
            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
            {
                mode = (nBackSubRunMode + 1);
                
                OutBuffer[13] |= (mode & 0x0f) << 2;
            }
            else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
            {
                
                OutBuffer[13] |=  0x0B << 2;
            }
            else if(nChairRunState == CHAIR_STATE_RUN)
            {
                OutBuffer[13] |=  7 << 2;
            }
        }

        if(nAxisUpdateCounter < 30)
        {
            if(nAxisUpdateCounter < 5)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
            else if(nAxisUpdateCounter < 10)  OutBuffer[14] = 0;
            else if(nAxisUpdateCounter < 15)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
            else if(nAxisUpdateCounter < 20)  OutBuffer[14] = 0;
            else if(nAxisUpdateCounter < 25)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
            else OutBuffer[14] = 0;
        }
        else
        {
            //OutBuffer[14] = (nFinalAxisStrength+1) & 0x07;
            //OutBuffer[14] = (nDisplayAxisStrength+1) & 0x07;//
            OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
        } 
        
        //OutBuffer[14] = (nAxisStrength+1) & 0x07;
        /*
        unsigned short curPosition = Input_GetAxisMotorPosition();
        
        curPosition /= 8;
        if(curPosition > 4) curPosition = 4;
        OutBuffer[14] = (unsigned char)((curPosition+1) & 0x07);
        */  
        if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            if(nBackSubRunMode == BACK_SUB_MODE_3D1)
            {
                OutBuffer[14] |= 1 << 3;
            }
            if(nBackSubRunMode == BACK_SUB_MODE_3D2)
            {
                OutBuffer[14] |= 2 << 3;
            }
            if(nBackSubRunMode == BACK_SUB_MODE_3D3)
            {
                OutBuffer[14] |= 3 << 3;
            }
        }
        else
        {
            OutBuffer[14] &= 0xc7;
        }
        //unsigned int pm25;
        //if(VoiceUart_GetPM25(&pm25) == -1)
        //{
        //  pm25 = 0;
        //}
        //else
        //{
        //  if(pm25 == 0)  pm25 = 1;
        //}
        // pm25 = 100; only test
        OutBuffer[15] = 0;//(unsigned char)(pm25&0x7f);
        
        OutBuffer[15] |= nStretchVigor<<0;
        if(bTapping == 0)          
        {
            OutBuffer[15] |= 1<<5; //点亮off,有叩击
        }
        else
        {
            OutBuffer[15] |= 0<<5; //点亮on,变指压
        }
        if(nCurSubFunction == BACK_SUB_MODE_KNEAD)
        {
            OutBuffer[15] |=  nKneadTurn<<3;
        }
        else
        {
            OutBuffer[15] |=  0<<3;
        }
        if(bLedFlag == 0)          
        {
            OutBuffer[15] |= 0<<2; //0关灯
        }
        else
        {
            OutBuffer[15] |= 1<<2; //1开灯
        }
        //      if(st_Stretch.active == true)
        //      {
        //         OutBuffer[15] |=  1<<6;
        //      }
        //      else
        //      {
        //         OutBuffer[15] |=  0<<6;
        //      } 
        OutBuffer[16] = 0;//(unsigned char)((pm25>>7)&0x7f);
        OutBuffer[17] = EOI;
        nOutBufferCount = 18;
        /*
        OutBuffer[13] = EOI;
        nOutBufferCount = 14;
        */
        //DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
        HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
        bMasterSendPacket = FALSE ;
    } 
    Main_Send_Leg();
    // Main_MassageSignalSend();
}


//void Main_Send(void)
//{
//    if(bMasterSendPacket)
//    { 
//        /***************************起始字节即第0个字节****************************/
//        OutBuffer[0] = SOI ;
//        /*******************************第1个字节*********************************
//            0         1 2        3  4  5              6            7
//        摇椅状态位  保留位   按摩椅的按摩手法   按摩椅运行状态   总是0
//        *************************************************************************/
//        if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
//        {
//            OutBuffer[1] = 0<<6;
//        }
//        else
//        {
//            OutBuffer[1] = 1<<6;
//        }
//        
//        switch(nCurSubFunction)
//        {
//        case BACK_SUB_MODE_KNEAD			: OutBuffer[1] |= 1<<3;break;
//        case BACK_SUB_MODE_KNOCK			: OutBuffer[1] |= 2<<3;break;
//        case BACK_SUB_MODE_WAVELET		        : OutBuffer[1] |= 3<<3;break;
//        case BACK_SUB_MODE_SOFT_KNOCK		        : OutBuffer[1] |= 4<<3;break;
//        case BACK_SUB_MODE_PRESS			: OutBuffer[1] |= 5<<3;break;
//        case BACK_SUB_MODE_MUSIC			: OutBuffer[1] |= 6<<3;break;
//        case BACK_SUB_MODE_RUBBING                      : OutBuffer[1] |= 7<<3;break;
//        default                                         : OutBuffer[1] |= 0<<3;break; 
//        }
//        OutBuffer[1] |= 0x01; 
//        /********************************第2个字节**************************************
//           0  1          2  3  4           5              6            7
//        揉捏头位置    揉捏/敲击速度    滚轮状态位     加热标志位     总是0
//        *******************************************************************************/
//        unsigned char speed;
//        if(nBackMainRunMode == BACK_MAIN_MODE_IDLE || nBackMainRunMode == BACK_MAIN_MODE_3D)
//        {
//            speed = 0;
//        }
//        else 
//        {
//            speed = nCurKneadKnockSpeed;
//        }
//        
//        if(nCurSubFunction==BACK_SUB_MODE_PRESS)// 指压时不显示力度
//        {
//            speed = 0;   
//        }
//        
//        OutBuffer[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x7)<<2)|(Input_GetKneadPosition()&0x3);
//        
//        if(bRollerEnable)
//        {
//            OutBuffer[2] |= (1<<5);
//        }
//        
//        /***************************第3个字节***********************************
//         0  1  2          3  4  5               6         7
//        气囊力度      震动力度（未使用）      未知      总是0
//        ***********************************************************************/
//        OutBuffer[3] = (nKeySeatVibrateStrength&0x7)<<3;
//        if(bOzonEnable)
//        {
//            OutBuffer[3] |= (1<<6);
//        }
//        else
//        {
//            OutBuffer[3] &= ~(1<<6);
//        }
//        
//        if(nKeyAirBagLocate != AIRBAG_LOCATE_NONE)
//        {
//            OutBuffer[3] |= (Valve_GetAirBagStrength()&0x7);
//        }
//        /****************************第4个字节********************************
//               0  1  2  3  4                    5  6          7
//        剩余按摩时间的高五位（单位是秒）    气囊充气部位    总是0
//        *********************************************************************/
//        OutBuffer[4] = 0;           
//        if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
//        {
//            OutBuffer[4] = 1<<5;  
//        }
//        else
//        {
//            switch(nKeyBackLocate)
//            {
//            case LOCATE_FULL_BACK:
//                OutBuffer[4] = 1<<5;           
//                break ;
//            case LOCATE_PARTIAL:
//                OutBuffer[4] = 2<<5;
//                break ;
//            case LOCATE_POINT:
//                OutBuffer[4] = 3<<5; ;
//                break ;
//            default:
//                break ;
//            }
//        }
//#ifdef FORCE_CONTROLLER
//        unsigned int time; 
//        time = KneadMotor_GetCurrent();
//        time *= 60;
//#else
//        unsigned int time = Data_Get_TimeSecond();
//#endif    
//        OutBuffer[4] |=(time>>7)& 0x1f;
//        
//        /****************************第5个字节**********************************
//           0 1 2 3 4 5 6          7
//        按摩剩余时间的低七位    总是0
//        ***********************************************************************/
//        OutBuffer[5] = time & 0x7f;
//        
//        /****************************第6个字节**********************************
//              0                1              2                 3
//        足部气囊标志位  小腿气囊标志位  大腿气囊标志位  坐垫气囊标志位（未使用）
//              4            5  6        7
//        手臂气囊标志位   滚轮速度   总是0
//        ***********************************************************************/
//        OutBuffer[6] = 0x00;
//        if( (bLeftFootAirBagValve) | (bRightFootAirBagValve) |(bFootHeelAirBagValve))
//        {
//            OutBuffer[6] |= 0x01;
//        }
//        
//        if( (bLegLeftAirBagValve) |(bLegRightAirBagValve))
//        {
//            OutBuffer[6] |= 0x02;
//        }
//        if((bLeftThighAirBagValve) | (bRightThighAirBagValve ))
//        {
//            OutBuffer[6] |= 0x04;
//        }
//        if((bRightArmUpAirBagValve1) | (bRightArmUpAirBagValve2)| (bRightArmUpAirBagValve3)|(bLeftArmUpAirBagValve1) |(bLeftArmUpAirBagValve2 )|(bLeftArmUpAirBagValve3))
//        {
//            OutBuffer[6] |= 0x10;
//        }
//        if(bRollerEnable)
//        {
//            if(Valve_RollerIsAuto())
//            {
////                if(Roller_GetSpeed() == ROLLER_SPEED_STOP) OutBuffer[6] |= (0 << 5);
////                else if(Roller_GetSpeed() == ROLLER_SPEED_SLOW) OutBuffer[6] |= (1 << 5);
////                else if(Roller_GetSpeed() == ROLLER_SPEED_MID) OutBuffer[6] |= (2 << 5);
////                else if(Roller_GetSpeed() == ROLLER_SPEED_FAST) OutBuffer[6] |= (3 << 5);
//                unsigned int rollerPWM;
//               rollerPWM = displayPWM;
//               OutBuffer[6] &= 0x9f;
//               if(rollerPWM == ROLLER_SPEED_STOP) OutBuffer[6] |= (0 << 5);
//               else if(rollerPWM == ROLLER_SPEED_SLOW) OutBuffer[6] |= (1 << 5);
//               else if(rollerPWM == ROLLER_SPEED_MID) OutBuffer[6] |= (2 << 5);
//               else if(rollerPWM == ROLLER_SPEED_FAST) OutBuffer[6] |= (3 << 5);
//            }
//            else
//            {
//                OutBuffer[6] |= (Valve_GetRollerLevel() << 5);
//            }
//        }
//        else
//        {
//            OutBuffer[6] |= (0 << 5);
//        }
//        /*****************************第7个字节*****************************************
//          0  1  2  3          4               5                 6                   7
//        按摩椅运行状态  肩部气囊标志位  背腰气囊标志位  颈部气囊标志位（未使用）  总是0
//        ********************************************************************************/
//        OutBuffer[7] = 0x0;
//        if((bLeftSholderAirBagValve) | (bRightSholderAirBagValve))
//        {
//            OutBuffer[7] |=  0x10;
//        }
//        if((bBackWaistRightUp) | (bBackWaistRightDown) |(bBackWaistLeftUp) | (bBackWaistLeftDown))
//        {
//            OutBuffer[7] |=  0x20;
//        }
//        
//        OutBuffer[7] &= 0xf0;
//        
//        BYTE state = nChairRunState;
//        if(nChairRunState == CHAIR_STATE_SLEEP) 
//        {
//            state = CHAIR_STATE_IDLE;
//        }
//        if(nChairRunState == CHAIR_STATE_DEMO) 
//        {
//            state = CHAIR_STATE_RUN;
//        }
//        if(nChairRunState == CHAIR_STATE_CALIBRATION) 
//        {
//            state = CHAIR_STATE_RUN;
//        }
//        OutBuffer[7] |= (state&0x0f);
//        /***************************第8个字节**********************************
//          0  1  2  3  4           5  6
//        机芯的位置（0~31）    零重力标志位
//        **********************************************************************/
//        OutBuffer[8] =0;
//        unsigned int data = Input_GetWalkMotorPosition();
//        data /= 31;
//        if(data >= 13) data = 13;
//        OutBuffer[8] = data;   
//        OutBuffer[8] |= (0 << 5);
//        /***************************第9个字节**********************************
//          0  1  2  3              4               5              6           7
//        体型检测的位置    体型检测结果显示   肩部调节指示   体型检测指示   总是0
//        **********************************************************************/
//        OutBuffer[9] = 0;
//        if(BodyDetectStep == DETECT_SHOULDER) 
//        {
//            if((ShoulderSteps > BODY_DETECT_PREPARE) && (ShoulderSteps < BODY_DETECT_OVER))
//            { 
//                OutBuffer[9] = 1<<6;
//            }
//            else
//            {
//                OutBuffer[9] = 0<<6;
//            }
//            
//            if(ShoulderSteps == BODY_DETECT_ADJ)
//            {
//                OutBuffer[9] |= 1<<5;
//                data = nShoulderPositionTop - nShoulderPositionBottom;
//                time = data /15;
//                data = (Input_GetWalkMotorPosition()-nShoulderPositionBottom) / time;
//                if(data == 0) data = 1;
//                if(data > 15) data = 15;
//                
//                OutBuffer[9] |= data&0x0f;
//            }
//        }
//        /***************************第10个字节**********************************
//               0  1               2  3            4          5 6           7
//        靠背电机运行状态    小腿电机运行状态   音乐开关   蜂鸣器模式     总是0
//        **********************************************************************/
//        OutBuffer[10] = 0;
//        
//        if(nCurBackLocate>=ZERO_POSITION_1)
//        {
//            if(!st_Stretch.active ) OutBuffer[10] = 1<<6;  
//        }
//        else
//        {
//            if(bMassagePositionUpdate)
//            {
//                if(nTargetMassagePosition == MASSAGE_OPTIMAL2_POSITION)
//                {
//                    if(bDisplayFlash)
//                    {
//                        OutBuffer[10] = (1<<6);  
//                    }
//                    else
//                    {
//                        OutBuffer[10] = 0;  
//                    } 
//                }
//            }
//        }
//        
//        if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
//        {
//            if(SlideMotor_GetDirection() == SLIDE_MOTOR_GO_FORWARD)
//            {
//                OutBuffer[10] |= 0x01<<4;
//            }
//            else
//            {
//                OutBuffer[10] |= 0x02<<4;
//            }
//        }
//        if(BackMotor_GetPower() == BACK_MOTOR_POWER_ON)
//        {
//            if(BackMotor_GetDirection() == BACK_MOTOR_GO_UP)
//            {
//                OutBuffer[10] |= 0x01;
//            }
//            else
//            {
//                OutBuffer[10] |= 0x02;
//            }
//        }
//        
//        if(LegMotor_GetPower() == LEG_MOTOR_POWER_ON)
//        {
//            if(LegMotor_GetDirection() == LEG_MOTOR_GO_UP)
//            {
//                OutBuffer[10] |= (0x01<<2);
//            }
//            else
//            {
//                OutBuffer[10] |= (0x02<<2);
//            }
//        }
//        
//        
//        OutBuffer[11] = 0;
//        //标识	1 蜂鸣器模式 2 音乐开关 1	音量 4
//        if((bSendBuzzerMode == TRUE)&(bRockEnable != true))
//        {
//            OutBuffer[11] = (nBuzzerMode&0x3)<<5;
//            // bSendBuzzerMode = FALSE ;  在蓝牙通讯中清零
//        }
//        else
//        {
//            OutBuffer[11] = 0;
//        }
//        
//        if(bRockEnable ==true)  //摇摆开始不显示零重力
//        {
//            OutBuffer[11] &= 0xF9;
//        }
//        else 
//        {
//            if(nZero_OK == 0)
//                OutBuffer[11] |= Zero_mark<<1; //零重力档位
//            else 
//                OutBuffer[11] |= Zero_Grade(BackMotor_Get_Position())<<1;
//        }
//        if(bBlueToothStatus)
//            //if(BlueToothMuteState() == BlueTooth_Speak_Out_On)
//        {
//            OutBuffer[11] |= 1 << 4;
//        }
//        else
//        {
//            OutBuffer[11] &= ~(1 << 4); //BlueTooth_MutePin_Value is equal to "0xef"
//        }
//        switch(w_PresetTime)
//        {
//        case RUN_TIME_10: OutBuffer[12] = 1;  break;
//        case RUN_TIME_20: OutBuffer[12] = 2;  break;
//        case RUN_TIME_30: OutBuffer[12] = 3;  break;
//        default: OutBuffer[12] = 0; break;
//        }
//        OutBuffer[12] |= ((nKeyAirBagLocate & 0x1F) << 2);
//        //滚轮方向
//        //      if(bRollerEnable)
//        //      {
//        //        // if(ReadRollerPhase() == 1)
//        //        {
//        //          OutBuffer[13] = 1;
//        //        }
//        //        // else if(ReadRollerPhase() == 0)
//        //        {
//        //          OutBuffer[13] = 2;
//        //        }
//        //        // else
//        //        OutBuffer[13] = 0;
//        //      }
//        //      else
//        //      {
//        //        OutBuffer[13] = 0;
//        //      }
//        OutBuffer[13] = 0;
////        if(bLegKneadEnable)
////        {
////            OutBuffer[13] |= (1<<6);
////        }
////        else
////        {
////            OutBuffer[13] = 0;
////        }
//        BYTE mode;
//        if(nChairRunState == CHAIR_STATE_DEMO)
//        {
//            mode = 1 & bDisplayFlash;
//            OutBuffer[13] |= mode << 2;
//            //wgh 20160803
//            time = Data_Get_ProgramExecTime()/60;
//            OutBuffer[4] &= 0xE0;
//            OutBuffer[4] |=(time>>7)& 0x1f;
//            //标识 1	运行时间低7位 7
//            OutBuffer[5] = time & 0x7f;
//        }
//        else
//        {
//            
//            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
//            {
//                mode = (nBackSubRunMode + 1);
//                OutBuffer[13] |= (mode & 0x0f) << 2;
//                if(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
//                {
//                    OutBuffer[13]  = 0;
//                    OutBuffer[13] |= 2<<2;
//                }
//                if(nBackSubRunMode ==BACK_SUB_MODE_AUTO_0)
//                {
//                    OutBuffer[13]  = 0;
//                    OutBuffer[13] |= 2<<1;
//                }
//                if(nBackSubRunMode ==BACK_SUB_MODE_AUTO_3)
//                {
//                    OutBuffer[13]  = 0;
//                    OutBuffer[13] |= 2<<3;
//                }
//                
//                
//            }
//            else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
//            {
//                OutBuffer[13] |=  0x0B << 2;
//            }
//            else if(nChairRunState == CHAIR_STATE_RUN)
//            {
//                OutBuffer[13] |=  7 << 2;
//            }
//        }
//        if(nAxisUpdateCounter < 30)
//        {
//            if(nAxisUpdateCounter < 5)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
//            else if(nAxisUpdateCounter < 10)  OutBuffer[14] = 0;
//            else if(nAxisUpdateCounter < 15)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
//            else if(nAxisUpdateCounter < 20)  OutBuffer[14] = 0;
//            else if(nAxisUpdateCounter < 25)  OutBuffer[14] = (nKeyAxisStrength+1) & 0x07;
//            else OutBuffer[14] = 0;
//        }
//        else
//        {
//            //OutBuffer[14] = (nFinalAxisStrength+1) & 0x07;
//            OutBuffer[14] = (nDisplayAxisStrength+1) & 0x07;//20150421 wgh 添加肩部显示
//        } 
//        
//        
//        if(nBackSubRunMode == BACK_SUB_MODE_3D1)
//        {
//            OutBuffer[14] |= 1 << 3;
//        }
//        if(nBackSubRunMode == BACK_SUB_MODE_3D2)
//        {
//            OutBuffer[14] |= 2 << 3;
//        }
//        if(nBackSubRunMode == BACK_SUB_MODE_3D3)
//        {
//            OutBuffer[14] |= 3 << 3;
//        }
//        OutBuffer[15] = EOI;
//        
//        
//        HandUart_Transmit_Packet(OutBuffer,16);
//        bMasterSendPacket = FALSE ;
//    } 
//    Main_Send_Leg();//用于将3D电机的控制命令进行打包
//}



void Main_BlueToothSend(void)
{
    static unsigned char OutBufferBlueTooth[MAX_OUTBUFFER_COUNT] ;
    static unsigned char OutBufferBlueTooth_Old[MAX_OUTBUFFER_COUNT] ;
    unsigned char nOutBufferBlueToothCount;
    
    if(bBlueToothStatus)
    {
        BlueToothOn();
    }
    else
    {
        BlueToothOff();
        bSendBuzzerMode = FALSE ;
        return;
    }
    if(bBlueToothMasterSendPacket)//控制此函数每50ms向手控器发送一次数据
    {
        OutBufferBlueTooth[0] = SOI ;
        //标识 1	按摩椅运行状态 1	按摩手法 3	按摩程序 3
        if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
        {
            OutBufferBlueTooth[1] = 0<<6;//第一个字节的第6位，椅子状态，休眠为0，非休眠为1
        }
        else
        {
            OutBufferBlueTooth[1] = 1<<6;
        }
        //按摩手法显示
        if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            
            OutBufferBlueTooth[1] |= 0<<3; //第一个字节的3、4、5位是按摩的手法，3D时按摩手法为停止
        }
        else
        {
            switch(nCurSubFunction)
            {
                //00：停止
                //01：揉捏
                //02：敲击
                //03：揉敲同步
                //04：叩击
                //05：指压
                //06：韵律按摩
                //07：保留
            case BACK_SUB_MODE_KNEAD			: OutBufferBlueTooth[1] |= 1<<3;break;
            case BACK_SUB_MODE_KNOCK			: OutBufferBlueTooth[1] |= 2<<3;break;
            case BACK_SUB_MODE_WAVELET		        : OutBufferBlueTooth[1] |= 3<<3;break;
            case BACK_SUB_MODE_SOFT_KNOCK		: OutBufferBlueTooth[1] |= 4<<3;break;
            case BACK_SUB_MODE_PRESS			: OutBufferBlueTooth[1] |= 5<<3;break;
            case BACK_SUB_MODE_MUSIC			: OutBufferBlueTooth[1] |= 6<<3;break;
            case BACK_SUB_MODE_RUBBING                  : OutBufferBlueTooth[1] |= 7<<3;break;
            default                                     : OutBufferBlueTooth[1] |= 0<<3;break; 
            }        
        }
        if(GetbRockEnable() == true)
        {
            OutBufferBlueTooth[1] |= 0x01;
        }
        else
        {
            OutBufferBlueTooth[1] &= 0xfe;
        }
        
        //标识 2 加热 1	保留 1	按摩机芯速度 3 	揉捏头宽度位置 2
        unsigned char speed;
        if(nBackMainRunMode == BACK_MAIN_MODE_IDLE)
        {
            speed = 0;
        }
        else 
        {
            speed = nCurKneadKnockSpeed;
        }
        
        if(((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nMaunalSubMode == nMaunalSubMode_PRESS))||(nBackMainRunMode == BACK_MAIN_MODE_3D))
        {
            OutBufferBlueTooth[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x0)<<2)|(Input_GetKneadPosition()&0x3);
        }
        else
        {
            if(nCurSubFunction == BACK_SUB_MODE_PRESS)
            {
                OutBufferBlueTooth[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x0)<<2)|(Input_GetKneadPosition()&0x3);
            }
            else
            {
                OutBufferBlueTooth[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x7)<<2)|(Input_GetKneadPosition()&0x3);
            }      
        }  
        
        if(bRollerEnable)
        {
            OutBufferBlueTooth[2] |= (1<<5);
        }
        else
        {
            OutBufferBlueTooth[2] &= ~(1<<5);
        } 
        // 标识 1	负离子开关 1 	 振动（或扭腰）强度 3	气压强度 3
        OutBufferBlueTooth[3] = 0;
        OutBufferBlueTooth[3] = (nKeySeatVibrateStrength&0x7)<<3;
        
        
        if(bOzonEnable)
        {
            OutBufferBlueTooth[3] |= (1<<6);
        }
        else
        {
            OutBufferBlueTooth[3] &= ~(1<<6);
        }
        
        if(nKeyAirBagLocate != AIRBAG_LOCATE_NONE)
        {
            OutBufferBlueTooth[3] |= (Valve_GetAirBagStrength()&0x7);
        }
        //标识 1	机芯按摩部位 2	运行时间高5位 5
        //显示位置
        OutBufferBlueTooth[4] = 0;           
        if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
        {
            if((nBackSubRunMode == BACK_SUB_MODE_AUTO_0) ||
               (nBackSubRunMode == BACK_SUB_MODE_AUTO_1) ||
                   (nBackSubRunMode == BACK_SUB_MODE_AUTO_2) ||
                       (nBackSubRunMode == BACK_SUB_MODE_AUTO_3) ||
                           (nBackSubRunMode == BACK_SUB_MODE_AUTO_4) ||              
                               (nBackSubRunMode == BACK_SUB_MODE_AUTO_5))
            {
                OutBufferBlueTooth[4] = 1<<5;           
            }
            else
            {
                OutBufferBlueTooth[4] = 2<<5;
            }
        }
        else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            OutBufferBlueTooth[4] = 1 << 5;
        }
        else if(nBackMainRunMode == BACK_MAIN_MODE_IDLE)
        {
            OutBufferBlueTooth[4] = 0 << 5;
        }
        else
        {
            switch(nKeyBackLocate)
            {
            case LOCATE_FULL_BACK:
                OutBufferBlueTooth[4] = 1<<5;           
                break ;
            case LOCATE_PARTIAL:
                OutBufferBlueTooth[4] = 2<<5;
                break ;
            case LOCATE_POINT:
                OutBufferBlueTooth[4] = 3<<5; ;
                break ;
            default://include LOCATE_NONE
                break ;
            }
        }
#ifdef FORCE_CONTROLLER
        unsigned int time; 
        time = KneadMotor_GetCurrent();
        time *= 60;
#else
        unsigned int time = Data_Get_TimeSecond();
#endif    
        OutBufferBlueTooth[4] |=(time>>7)& 0x1f;
        //标识 1	运行时间低7位 7
        OutBufferBlueTooth[5] = time & 0x7f;
        
        OutBufferBlueTooth[6] = 0x00;
        if( (bLeftFootAirBagValve) | (bRightFootAirBagValve) |(bFootHeelAirBagValve))
        {
            OutBufferBlueTooth[6] |= 0x01;
        }
        
        if( (bLegLeftAirBagValve) |(bLegRightAirBagValve))
        {
            OutBufferBlueTooth[6] |= 0x02;
        }
        if((bLeftThighAirBagValve) | (bRightThighAirBagValve ))
        {
            OutBufferBlueTooth[6] |= 0x04;
        }
        if((bRightArmUpAirBagValve1) | (bRightArmUpAirBagValve2)| (bRightArmUpAirBagValve3)|(bLeftArmUpAirBagValve1) |(bLeftArmUpAirBagValve2 )|(bLeftArmUpAirBagValve3))
        {
            OutBufferBlueTooth[6] |= 0x10;
        }
        if(bRollerEnable)
        {
            if(Valve_RollerIsAuto())
            {
                // if(bDisplayFlash) OutBufferBlueTooth[6] |= (3<<5);
                // else  OutBufferBlueTooth[6] |= (0<<5);
                unsigned int rollerPWM;
                rollerPWM = displayPWM;
                OutBufferBlueTooth[6] &= 0x9f;
                if(rollerPWM == ROLLER_SPEED_STOP) OutBufferBlueTooth[6] |= (0 << 5);
                else if(rollerPWM == ROLLER_SPEED_SLOW) OutBufferBlueTooth[6] |= (1 << 5);
                else if(rollerPWM == ROLLER_SPEED_MID) OutBufferBlueTooth[6] |= (2 << 5);
                else if(rollerPWM == ROLLER_SPEED_FAST) OutBufferBlueTooth[6] |= (3 << 5);
            }
            else
            {
                OutBufferBlueTooth[6] |= (Valve_GetRollerLevel() << 5);
            }
        }
        else
        {
            OutBufferBlueTooth[6] |= (0 << 5);
        }
        OutBufferBlueTooth[7] = 0x0;
        if((bLeftSholderAirBagValve) | (bRightSholderAirBagValve))
        {
            OutBufferBlueTooth[7] |=  0x10;
        }
        //        if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
        //        {
        //            OutBufferBlueTooth[7] |= 0x70;
        //        }
        /* if((bBackWaistRightUp) | (bBackWaistRightDown) |(bBackWaistLeftUp) | (bBackWaistLeftDown))
        {
        OutBufferBlueTooth[7] |=  0x20;
    }
        */
        OutBufferBlueTooth[7] &= 0xf0;
        
        BYTE state = nChairRunState;
        if(nChairRunState == CHAIR_STATE_SLEEP) 
        {
            state = CHAIR_STATE_IDLE;
        }
        if(nChairRunState == CHAIR_STATE_DEMO) 
        {
            state = CHAIR_STATE_RUN;
        }
        if(nChairRunState == CHAIR_STATE_CALIBRATION) 
        {
            state = CHAIR_STATE_RUN;
        }
        OutBufferBlueTooth[7] |= (state&0x0f);
        /*
        unsigned int data = Input_GetWalkMotorPosition();
        data /= 33;//38;//31;
        if(data >= 12) data = 12;
        OutBufferBlueTooth[8] = data;   
        OutBufferBlueTooth[9] = 0;
        */
        OutBufferBlueTooth[8] &= 0x00;
        unsigned int data = Input_GetWalkMotorPosition();
        data /= 31;
        if(data >= 13) data = 13;
        OutBufferBlueTooth[8] = data;  
        if(bMassagePositionUpdate)
        {
            if((nTargetMassagePosition == MASSAGE_OPTIMAL2_POSITION)&&(Zero_mark==1))
            {
                if(GetbRockEnable() == false)OutBufferBlueTooth[8] |= (1<<5);	
            }
            else if((nTargetMassagePosition == MASSAGE_OPTIMAL2_POSITION)&&(Zero_mark==2))
            {
                if(GetbRockEnable() == false)OutBufferBlueTooth[8] |= (1<<6);	
            }
            else if((nTargetMassagePosition == MASSAGE_INIT_POSITION)&&(Zero_mark==0))
            {
                OutBufferBlueTooth[8] |= 0<<5; 
                OutBufferBlueTooth[8] |= 0<<6; 
            } 
        }
        else if(isFIRSTZeroPosition())//零重力提示
        {
            if(GetbRockEnable() == false)
                OutBufferBlueTooth[8] |= 1<<5;  
        }
        else if(isZeroPosition())
        {
            if(GetbRockEnable() == false)
                OutBufferBlueTooth[8] |= 1<<6;	
        }
        else
        {
            if(GetbRockEnable() == false)
                OutBufferBlueTooth[8] |= 0<<6;
        }
        
        OutBufferBlueTooth[9] = 0;
        if((BodyDetectStep == DETECT_SHOULDER)&&((nBackMainRunMode == BACK_MAIN_MODE_3D)||(nBackMainRunMode == BACK_MAIN_MODE_AUTO)))//cyw 2017 12 01 
        {
            if((ShoulderSteps >= BODY_DETECT_PREPARE) && (ShoulderSteps < BODY_DETECT_OVER))
            { 
                OutBufferBlueTooth[9] = 1<<6;
            }
            else
            {
                OutBufferBlueTooth[9] = 0<<6;
            }
            
            if(ShoulderSteps == BODY_DETECT_ADJ)
            {
                OutBufferBlueTooth[9] |= 1<<5;
                data = nShoulderPositionTop - nShoulderPositionBottom;
                time = data /15;
                data = (Input_GetWalkMotorPosition()-nShoulderPositionBottom) / time;
                if(data == 0) data = 1;
                if(data > 15) data = 15;
                
                OutBufferBlueTooth[9] |= data&0x0f;
                
            }
        }
        //标识 1	运行指示 1	小腿电动缸运行方向指示 3	靠背电动缸运行方向指示 3
        OutBufferBlueTooth[10] = 0;
        /*      if(isZeroPosition())
        {
        if((bRockEnable == FALSE)&&(bZeroflash == FALSE)&&(st_Stretch.active == FALSE) ) 
        {
        OutBufferBlueTooth[10] = 1<<6; 
    }
        else
        {
        OutBufferBlueTooth[10] = 0<<6;
    }
    }
        else//到位   闪烁 
        {
        if((bZeroflash == TRUE)&&(BackMotor_GetDirection() == BACK_MOTOR_GO_DOWN )  )
        {
        if(bZeroTimer100MS == TRUE)
        {
        bZeroTimer100MScount++;
    }            
        if(bZeroTimer100MScount<10)
        {
        if(bRockEnable == FALSE)
        {
        OutBufferBlueTooth[10] = 1<<6;
    }
        else
        {
        OutBufferBlueTooth[10] = 0<<6;
    }
        //OutBufferBlueTooth[10] = 1<<6; 
    }            
        else if( (bZeroTimer100MScount>=10)&&(bZeroTimer100MScount<20))
        {
        OutBufferBlueTooth[10] = 0<<6;
    }
        else
        {
        bZeroTimer100MScount =0;
    }            
        
    }
        else if((bZeroflash == TRUE)&&(BackMotor_GetDirection() == BACK_MOTOR_GO_UP )&&(Send_BackLocation > (MASSAGE_BACK_OPTIMAL1_LOCATION - 30))  )
        {
        if(bZeroTimer100MS == TRUE)
        {
        bZeroTimer100MScount++;
    }           
        if(bZeroTimer100MScount<10)
        {
        if(bRockEnable == FALSE)
        {
        OutBufferBlueTooth[10] = 1<<6;
    }
        else
        {
        OutBufferBlueTooth[10] = 0<<6;
    }
        //OutBufferBlueTooth[10] = 1<<6; 
    }            
        else if( (bZeroTimer100MScount>=10)&&(bZeroTimer100MScount<20))
        {
        OutBufferBlueTooth[10] = 0<<6;
    }
        else
        {
        bZeroTimer100MScount =0;
    }            
        
    }
        else
        {
        bZeroTimer100MScount =0;
        OutBufferBlueTooth[10] = 0<<6;
    }
        
        
        
    }
        */
        /*  if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
        {
        if(SlideMotor_GetDirection() == SLIDE_MOTOR_GO_FORWARD)
        {
        OutBufferBlueTooth[10] = 0x01<<4;
    }
        else
        {
        OutBufferBlueTooth[10] = 0x02<<4;
    }
    }*/
        
        OutBufferBlueTooth[10] = 0;
        if(BackMotor_GetPower() == BACK_MOTOR_POWER_ON)
        {
            if(BackMotor_GetDirection() == BACK_MOTOR_GO_UP)
            {
                OutBufferBlueTooth[10] |= 0x01;
            }
            else
            {
                OutBufferBlueTooth[10] |= 0x02;
            }
        }
        
        if(LegMotor_GetPower() == LEG_MOTOR_POWER_ON)
        {
            if(LegMotor_GetDirection() == LEG_MOTOR_GO_UP)
            {
                OutBufferBlueTooth[10] |= (0x01<<2);
            }
            else
            {
                OutBufferBlueTooth[10] |= (0x02<<2);
            }
        }
        
        //标识	1 蜂鸣器模式 2 音乐开关 1	音量 4
        if(bSendBuzzerMode == TRUE)
        {
            OutBufferBlueTooth[11] = (nBuzzerMode&0x3)<<5;
            bSendBuzzerMode = FALSE ;
        }
        else
        {
            OutBufferBlueTooth[11] = 0;
        }
        
        if(BlueToothMuteState() == BlueTooth_Speak_Out_On)
        {
            OutBufferBlueTooth[11] |= 1 << 4;
        }
        else
        {
            OutBufferBlueTooth[11] &= BlueTooth_MutePin_Value; //BlueTooth_MutePin_Value is equal to "0xef"
        }
        switch(w_PresetTime)
        {
        case RUN_TIME_10: OutBufferBlueTooth[12] = 1;  break;
        case RUN_TIME_20: OutBufferBlueTooth[12] = 2;  break;
        case RUN_TIME_30: OutBufferBlueTooth[12] = 3;  break;
        default: OutBufferBlueTooth[12] = 0; break;
        }
        OutBufferBlueTooth[12] |= ((nKeyAirBagLocate & 0xff) << 2);
        //滚轮方向
        /* if(bRollerEnable)
        {
        // if(ReadRollerPhase() == 1)
        {
        OutBufferBlueTooth[13] = 1;
    }
        // else if(ReadRollerPhase() == 0)
        {
        OutBufferBlueTooth[13] = 2;
    }
        // else
        OutBufferBlueTooth[13] = 0;
    }
        else
        {
        OutBufferBlueTooth[13] = 0;
    }*/
        BYTE mode;
        if(nChairRunState == CHAIR_STATE_DEMO)
        {
            mode = 1 & bDisplayFlash;
            OutBufferBlueTooth[13] |= mode << 2;
            time = Data_Get_ProgramExecTime()/60;
            OutBufferBlueTooth[4] &= 0xE0;
            OutBufferBlueTooth[4] |=(time>>7)& 0x1f;
            //标识 1	运行时间低7位 7
            OutBufferBlueTooth[5] = time & 0x7f;
        }
        else
        { 
            OutBufferBlueTooth[13] &= 0x03;
            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
            {
                mode = (nBackSubRunMode + 1);
                
                OutBufferBlueTooth[13] |= (mode & 0x0f) << 2;
            }
            else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
            {
                
                OutBufferBlueTooth[13] |=  0x0B << 2;
            }
            else if(nChairRunState == CHAIR_STATE_RUN)
            {
                OutBufferBlueTooth[13] |=  7 << 2;
            }
        }
        
        if(nAxisUpdateCounter < 30)
        {
            if(nAxisUpdateCounter < 5)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
            else if(nAxisUpdateCounter < 10)  OutBufferBlueTooth[14] = 0;
            else if(nAxisUpdateCounter < 15)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
            else if(nAxisUpdateCounter < 20)  OutBufferBlueTooth[14] = 0;
            else if(nAxisUpdateCounter < 25)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
            else OutBufferBlueTooth[14] = 0;
        }
        else
        {
            OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
        } 
        
        if(nBackMainRunMode == BACK_MAIN_MODE_3D)
        {
            if(nBackSubRunMode == BACK_SUB_MODE_3D1)
            {
                OutBufferBlueTooth[14] |= 1 << 3;
            }
            if(nBackSubRunMode == BACK_SUB_MODE_3D2)
            {
                OutBufferBlueTooth[14] |= 2 << 3;
            }
            if(nBackSubRunMode == BACK_SUB_MODE_3D3)
            {
                OutBufferBlueTooth[14] |= 3 << 3;
            }
        }
        else
        {
            OutBufferBlueTooth[14] &= 0xc7;
        }
        OutBufferBlueTooth[15] = 0;
        
        OutBufferBlueTooth[15] |= nStretchVigor<<0;
        if(bTapping == 0)          
        {
            OutBufferBlueTooth[15] |= 1<<5; //点亮off,有叩击
        }
        else
        {
            OutBufferBlueTooth[15] |= 0<<5; //点亮on,变指压
        }
        if(nCurSubFunction == BACK_SUB_MODE_KNEAD)
        {
            OutBufferBlueTooth[15] |=  nKneadTurn<<3;
        }
        else
        {
            OutBufferBlueTooth[15] |=  0<<3;
        }
        OutBufferBlueTooth[16] = 0;
        OutBufferBlueTooth[17] = EOI;
        nOutBufferBlueToothCount = 18;
        /*
        OutBufferBlueTooth[13] = EOI;
        nOutBufferBlueToothCount = 14;
        */
        //DMAUart_Transmit_Packet(OutBufferBlueTooth,nOutBufferBlueToothCount);
        BlueToothUart_Transmit_Packet(OutBufferBlueTooth, nOutBufferBlueToothCount);
        bBlueToothMasterSendPacket = FALSE ;
    }
}
//---------------云养程序修改区
void Main_BlueToothSend_OLD(void)
{
  
  static unsigned char OutBufferBlueTooth[MAX_OUTBUFFER_COUNT] ;
  static unsigned char OutBufferBlueTooth_Old[MAX_OUTBUFFER_COUNT] ;
  unsigned char nOutBufferBlueToothCount;
  
  
  if(bBlueToothStatus)
       {
         BlueToothOn();
       }
          else
       {
         BlueToothOff();
         bSendBuzzerMode = FALSE ;
         return;
       }
  if(bBlueToothMasterSendPacket)
  {
    OutBufferBlueTooth[0] = SOI ;
    OutBufferBlueTooth[1] = 0;
    OutBufferBlueTooth[1] = 0x01;  //3D 标识
    OutBufferBlueTooth[1] |= 0x04;  //3D 标识
    //标识 1	按摩椅运行状态 1	按摩手法 3	按摩程序 3
    if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
    {
      OutBufferBlueTooth[1] |= 0 << 6;
    }
    else
    {
      OutBufferBlueTooth[1] |= 1 << 6;
    }
    
    /*****************************************************/
    //按摩手法显示
    switch(nCurSubFunction)
    {
      //00：停止
      //01：揉捏
      //02：敲击
      //03：揉敲同步
      //04：叩击
      //05：指压
      //06：韵律按摩
      //07：保留
    case BACK_SUB_MODE_KNEAD			:
      OutBufferBlueTooth[1] |= 1 << 3;
      break;
    case BACK_SUB_MODE_KNOCK			:
      OutBufferBlueTooth[1] |= 2 << 3;
      break;
    case BACK_SUB_MODE_WAVELET		        :
      OutBufferBlueTooth[1] |= 3 << 3;
      break;
    case BACK_SUB_MODE_SOFT_KNOCK		:
      OutBufferBlueTooth[1] |= 4 << 3;
      break;
    case BACK_SUB_MODE_PRESS			:
      OutBufferBlueTooth[1] |= 5 << 3;
      break;
    case BACK_SUB_MODE_MUSIC			:
      OutBufferBlueTooth[1] |= 6 << 3;
      break;
    default		:
      OutBufferBlueTooth[1] |= 0 << 3;
      break;
    case BACK_SUB_MODE_RUBBING:
      OutBufferBlueTooth[1] |= 7 << 3;
      break;
      break ;
    }
    /*****************************************************/

    //标识 1 加热 1	保留 1	按摩机芯速度 3 	揉捏头宽度位置 2
    //00-03 自定义
  
    unsigned char speed;
    if(nBackMainRunMode == BACK_MAIN_MODE_IDLE)
    {
      speed = 0;
    }
    else
    {
      speed = nCurKneadKnockSpeed;
    }
    OutBufferBlueTooth[2] = ((bKeyWaistHeat & 0x1) << 6) | ((speed & 0x7) << 2) | (Input_GetKneadPosition() & 0x3);
    
    if(bRollerEnable)
    {
      OutBufferBlueTooth[2] |= (1 << 5);
    }
    else
    {
      OutBufferBlueTooth[2] &= ~(1 << 5);
    }
    // 标识 1	负离子开关 1 	 振动（或扭腰）强度 3	气压强度 3
    OutBufferBlueTooth[3] = (nKeySeatVibrateStrength & 0x7) << 3;
    
    if(nKeyAirBagLocate != AIRBAG_LOCATE_NONE)
    {
      OutBufferBlueTooth[3] |= (Valve_GetAirBagStrength() & 0x7);
    }
    //标识 1	机芯按摩部位 2	运行时间高5位 5
    //显示位置
    OutBufferBlueTooth[4] = 0;
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
      if((nBackSubRunMode == BACK_SUB_MODE_AUTO_0) ||
         (nBackSubRunMode == BACK_SUB_MODE_AUTO_1) ||
           (nBackSubRunMode == BACK_SUB_MODE_AUTO_2) ||
             (nBackSubRunMode == BACK_SUB_MODE_AUTO_3))
      {
        OutBufferBlueTooth[4] = 1 << 5;
      }
      else
      {
        OutBufferBlueTooth[4] = 2 << 5;
      }
    }
    else
    {
      switch(nKeyBackLocate)
      {
      case LOCATE_FULL_BACK:
        OutBufferBlueTooth[4] = 1 << 5;
        break ;
      case LOCATE_PARTIAL:
        OutBufferBlueTooth[4] = 2 << 5;
        break ;
      case LOCATE_POINT:
        OutBufferBlueTooth[4] = 3 << 5; ;
        break ;
      default://include LOCATE_NONE
        //OutBufferBlueTooth[4] = 3<<5; ;
        break ;
      }
    }
    
#ifdef FORCE_CONTROLLER
    unsigned int time;
    //time = (KnockMotor_GetCurrent()&0x0f)<<4;
    time = KneadMotor_GetCurrent();
    time *= 60;
#else
    unsigned int time = Data_Get_TimeSecond();
#endif
    if(nChairRunState == CHAIR_STATE_DEMO)
    {
      time /= 60;    //demo模式 时间按分显示
    }
    OutBufferBlueTooth[4] |= (time >> 7) & 0x1f;
    //标识 1	运行时间低7位 7
    OutBufferBlueTooth[5] = time & 0x7f;

    OutBufferBlueTooth[6] = 0x00;
     if( (bLeftFootAirBagValve) | (bRightFootAirBagValve) |(bFootHeelAirBagValve))
      {
        OutBuffer[6] |= 0x01;
      }
      
      if( (bLegLeftAirBagValve) |(bLegRightAirBagValve))
      {
       OutBuffer[6] |= 0x02;
      }
    if((bLeftThighAirBagValve) | (bRightThighAirBagValve ))
    {
      OutBufferBlueTooth[6] |= 0x04;
    }
    if((bRightArmUpAirBagValve1) | (bRightArmUpAirBagValve2)| (bRightArmUpAirBagValve3)|(bLeftArmUpAirBagValve1) |(bLeftArmUpAirBagValve2 )|(bLeftArmUpAirBagValve3))
    {
      OutBufferBlueTooth[6] |= 0x10;
    }
    
    if(bRollerEnable)
        {
            if(Valve_RollerIsAuto())
            {
//                if(Roller_GetSpeed() == ROLLER_SPEED_STOP) OutBufferBlueTooth[6] |= (0 << 5);
//                else if(Roller_GetSpeed() == ROLLER_SPEED_SLOW) OutBufferBlueTooth[6] |= (1 << 5);
//                else if(Roller_GetSpeed() == ROLLER_SPEED_MID) OutBufferBlueTooth[6] |= (2 << 5);
//                else if(Roller_GetSpeed() == ROLLER_SPEED_FAST) OutBufferBlueTooth[6] |= (3 << 5);
                unsigned int rollerPWM;
                rollerPWM = displayPWM;
                OutBufferBlueTooth[6] &= 0x9f;
                if(rollerPWM == ROLLER_SPEED_STOP) OutBufferBlueTooth[6] |= (0 << 5);
                else if(rollerPWM == ROLLER_SPEED_SLOW)OutBufferBlueTooth[6] |= (1 << 5);
                else if(rollerPWM == ROLLER_SPEED_MID) OutBufferBlueTooth[6] |= (2 << 5);
                else if(rollerPWM == ROLLER_SPEED_FAST) OutBufferBlueTooth[6] |= (3 << 5);
            }
            else
            {
                OutBufferBlueTooth[6] |= (Valve_GetRollerLevel() << 5);
            }
        }
        else
        {
            OutBufferBlueTooth[6] |= (0 << 5);
        }

    OutBufferBlueTooth[7] = 0x0;
    
    if((bLeftSholderAirBagValve) | (bRightSholderAirBagValve))
    {
      OutBufferBlueTooth[7] |=  0x10;
    }
//    if((bBackWaistRightUp) | (bBackWaistRightDown) | (bBackWaistLeftUp) | (bBackWaistLeftDown))
//    {
//      OutBufferBlueTooth[7] |=  0x20;
//    }
    
    OutBufferBlueTooth[7] &= 0xf0;
    
    BYTE state = nChairRunState;
    if(nChairRunState == CHAIR_STATE_SLEEP)
    {
      state = CHAIR_STATE_IDLE;
    }
    if(nChairRunState == CHAIR_STATE_DEMO)
    {
      state = CHAIR_STATE_RUN;
    }
    OutBufferBlueTooth[7] |= (state & 0x0f);
    
    unsigned int data = Input_GetWalkMotorPosition();
    data /= 31;
    if(data >= 13) data = 13;
    OutBufferBlueTooth[8] = data;
    
    
     OutBufferBlueTooth[9] = 0;
    if(BodyDetectStep == DETECT_SHOULDER) 
      {
        if((ShoulderSteps > BODY_DETECT_PREPARE) && (ShoulderSteps < BODY_DETECT_OVER))
        { 
          OutBufferBlueTooth[9] = 1<<6;
        }
        else
        {
          OutBufferBlueTooth[9] = 0<<6;
        }
        
        if(ShoulderSteps == BODY_DETECT_ADJ)
        {
          OutBufferBlueTooth[9] |= 1<<5;
          data = nShoulderPositionTop - nShoulderPositionBottom;
          time = data /15;
          data = (Input_GetWalkMotorPosition()-nShoulderPositionBottom) / time;
          if(data == 0) data = 1;
          if(data > 15) data = 15;
          
          OutBufferBlueTooth[9] |= data&0x0f;
          
        }
      }
   
    OutBufferBlueTooth[10] = 0;
    if(isZeroPosition())
    {
      OutBufferBlueTooth[10] = 1 << 6;
    }
    if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
    {
      if(SlideMotor_GetDirection() == SLIDE_MOTOR_GO_FORWARD)
      {
        OutBufferBlueTooth[10] = 0x01 << 4;
      }
      else
      {
        OutBufferBlueTooth[10] = 0x02 << 4;
      }
    }
    if(BackMotor_GetPower() == BACK_MOTOR_POWER_ON)
    {
      if(BackMotor_GetDirection() == BACK_MOTOR_GO_UP)
      {
        OutBufferBlueTooth[10] |= 0x01;
      }
      else
      {
        OutBufferBlueTooth[10] |= 0x02;
      }
    }
    
    if(LegMotor_GetPower() == LEG_MOTOR_POWER_ON)
    {
      if(LegMotor_GetDirection() == LEG_MOTOR_GO_UP)
      {
        OutBufferBlueTooth[10] |= (0x01 << 2);
      }
      else
      {
        OutBufferBlueTooth[10] |= (0x02 << 2);
      }
    }
    
     //标识	1 蜂鸣器模式 2 音乐开关 1	音量 4
      if(bSendBuzzerMode == TRUE)
      {
        OutBufferBlueTooth[11] = (nBuzzerMode&0x3)<<5;
        bSendBuzzerMode = FALSE ;
      }
      else
      {
        OutBufferBlueTooth[11] = 0;
      }
    

    switch(w_PresetTime)
    {
    case RUN_TIME_10:
      OutBufferBlueTooth[12] = 1;
      break;
    case RUN_TIME_20:
      OutBufferBlueTooth[12] = 2;
      break;
    case RUN_TIME_30:
      OutBufferBlueTooth[12] = 3;
      break;
    default:
      OutBufferBlueTooth[12] = 0;
      break;
    }
    unsigned int locate = 0;
    switch(nKeyAirBagLocate)
    {
    case AIRBAG_LOCATE_NONE: break;
    case AIRBAG_LOCATE_LEG_FOOT:locate = 0x04;break;
    case AIRBAG_LOCATE_BACK_WAIST: locate = 0x08; break;
    case AIRBAG_LOCATE_ARM_SHOLDER: locate = 0x10; break;
    case AIRBAG_LOCATE_SEAT:locate = 0x20;break;
    case AIRBAG_LOCATE_AUTO:locate = 0x40;break;
    case AIRBAG_LOCATE_ARM:break;
    }
    
    OutBufferBlueTooth[12] |= locate;
    
  //---------------------------------------------     
   OutBufferBlueTooth[13] = 0;
    //滚轮方向
    if(bRollerEnable)
    {
     // if(ReadRollerPhase() == 1)
      if(1)
      {
        OutBufferBlueTooth[13] = 1;
      }

    }
    else
    {
      OutBufferBlueTooth[13] = 0;
    }

    //---------------------------------云养程序区
      BYTE mode;
     if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
        {
          switch(nBackSubRunMode)
          {
            case  BACK_SUB_MODE_AUTO_0: mode = 0x01; break;
            case  BACK_SUB_MODE_AUTO_1: mode = 0x02; break;
            case  BACK_SUB_MODE_AUTO_2: mode = 0x03; break;
            case  BACK_SUB_MODE_AUTO_3: mode = 0x04; break;
            case  BACK_SUB_MODE_AUTO_4: mode = 0x05; break;
            case  BACK_SUB_MODE_AUTO_5: mode = 0x06; break;
            case  BACK_SUB_MODE_NETCLOUD_1: mode = 0x08; break;
            case  BACK_SUB_MODE_NETCLOUD_2: mode = 0x09; break;
            case  BACK_SUB_MODE_NETCLOUD_3: mode = 0x0a; break;
            case  BACK_SUB_MODE_NETCLOUD_4: mode = 0x0b; break;
            case  BACK_SUB_MODE_DIY: mode = 0x0d; break;
            default: mode = 0x07; break;
          }
          OutBufferBlueTooth[13] |= (mode & 0x0f) << 2;
        }
    else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
    {
      OutBufferBlueTooth[13] |=  0x0c << 2;
    }
    else if(nChairRunState == CHAIR_STATE_RUN)
    {
        OutBufferBlueTooth[13] |=  7 << 2;
    }  
    
    //----------------------------------------------------------
    if(nAxisUpdateCounter < 30)
    {
      if(nAxisUpdateCounter < 5)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
      else if(nAxisUpdateCounter < 10)  OutBufferBlueTooth[14] = 0;
      else if(nAxisUpdateCounter < 15)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
      else if(nAxisUpdateCounter < 20)  OutBufferBlueTooth[14] = 0;
      else if(nAxisUpdateCounter < 25)  OutBufferBlueTooth[14] = (nKeyAxisStrength+1) & 0x07;
      else OutBufferBlueTooth[14] = 0;
    }
    else
    {
      //OutBufferBlueTooth[14] = (nFinalAxisStrength+1) & 0x07;
      OutBufferBlueTooth[14] = (nDisplayAxisStrength+1) & 0x07;// 20150421 wgh 添加肩部显示
    } 
    
    if(nBackSubRunMode == BACK_SUB_MODE_3D1)
    {
      OutBufferBlueTooth[14] |= 1 << 3;
    }
    if(nBackSubRunMode == BACK_SUB_MODE_3D2)
    {
      OutBufferBlueTooth[14] |= 2 << 3;
    }
    if(nBackSubRunMode == BACK_SUB_MODE_3D3)
    {
      OutBufferBlueTooth[14] |= 3 << 3;
    }
    
    unsigned char checkSum = 0;
    for(int i=1;i<15;i++)
    {
      checkSum += OutBufferBlueTooth[i];
    }
    checkSum = ~checkSum;
    checkSum &= 0x7f;
    OutBufferBlueTooth[15] = checkSum;
    OutBufferBlueTooth[16] = EOI;
    nOutBufferBlueToothCount = 17;
 //   BlueToothUart_Transmit_Packet(OutBufferBlueTooth, nOutBufferBlueToothCount);
 //   bBlueToothMasterSendPacket = FALSE ;
    
     if(memcmp(OutBufferBlueTooth,OutBufferBlueTooth_Old,nOutBufferBlueToothCount) != 0)
    {
      BlueToothUart_Transmit_Packet(OutBufferBlueTooth, nOutBufferBlueToothCount);
      memcpy(OutBufferBlueTooth_Old,OutBufferBlueTooth,nOutBufferBlueToothCount);  
    }
    else
    {
     OutBufferBlueTooth[0] = SOI;
     unsigned short ID;
     OutBufferBlueTooth[1] = 0x85; //信息帧识别码
     ID = *(unsigned int*)AUTO_NET_CLOUD1;
     if(ID == 0xffff) ID = 0;
     OutBufferBlueTooth[2] = (ID>>7)&0x7f;
     OutBufferBlueTooth[3] = (ID)&0x7f;
     ID = *(unsigned int*)AUTO_NET_CLOUD2;
     if(ID == 0xffff) ID = 0;
     OutBufferBlueTooth[4] = (ID>>7)&0x7f;
     OutBufferBlueTooth[5] = (ID)&0x7f;
     ID = *(unsigned int*)AUTO_NET_CLOUD3;
     if(ID == 0xffff) ID = 0;
     OutBufferBlueTooth[6] = (ID>>7)&0x7f;
     OutBufferBlueTooth[7] = (ID)&0x7f;
     ID = *(unsigned int*)AUTO_NET_CLOUD4;
     if(ID == 0xffff) ID = 0;
     OutBufferBlueTooth[8] = (ID>>7)&0x7f;
     OutBufferBlueTooth[9] = (ID)&0x7f;
     OutBufferBlueTooth[10] = EOI;
     nOutBufferBlueToothCount = 11;
     BlueToothUart_Transmit_Packet(OutBufferBlueTooth, nOutBufferBlueToothCount);
     OutBufferBlueTooth_Old[0] = 0;  //下一帧为状态帧
    }
    bBlueToothMasterSendPacket = FALSE ;   
    
    
    
    
    
    
  }
}

void Main_Initial_Data(void)
{
    bAxisUpdate = 1;  //上电后3D马达先归零
    
    GlobalFlags0.nByte = 0;
    GlobalFlags1.nByte = 0;
    GlobalFlags2.nByte = 0;
    GlobalFlags3.nByte = 0;
    GlobalFlags4.nByte = 0;
    GlobalFlags5.nByte = 0;
    GlobalFlags6.nByte = 0;
    GlobalFlags7.nByte = 0;
    GlobalFlags8.nByte = 0;
    GlobalFlags9.nByte = 0;
    GlobalFlags10.nByte = 0;
    
    
    unsigned int pw_Information[10];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    
    if((SOFT_MAIN_VER != ReadEEByte(USER_DATA_BASE + SOFT_MAIN_VER_ADDRESS)) || (SOFT_SECONDARY_VER != ReadEEByte(USER_DATA_BASE + SOFT_SECONDARY_VER_ADDRESS))) 
    {  //首次使用需要初始化user_Data中的数据
        *(pInformation + SOFT_MAIN_VER_ADDRESS) = SOFT_MAIN_VER;
        *(pInformation + SOFT_SECONDARY_VER_ADDRESS) = SOFT_SECONDARY_VER;
        *(pInformation + SETTLE_ADDRESS) = MEMORY_DEFAULT_SETTLE;        
        *(pInformation + AIRBAG_STRETCH_ADDRESS) = MEMORY_DEFAULT_AIR;             
        *(pInformation + SLIDE_MOTOR_ENABLE_ADDRESS) = SLIDE_DEFAULT_ENABLE; 
        *(pInformation + DEFAULT_TIME_ADDRESS) = RUN_TIME_20/60; 
        *(pInformation + BLUETOOTH_STATUS_ADDRESS) = BLUETOOTH_STATUS_DEFAULT; 
        *(pInformation + REST_SLEEP_MODE_ADDRESS) = REST_SLEEP_DEFAULT;//20150702
        *(pInformation + LANGUAGE_ADDRESS) = Language_English;
        //*(pInformation + ARM_MOTOR_SWITCH_ADDRESS) = ARM_DEFAULT_DISABLE;
        MEM_Write_Memory(pw_Information,8*2);
        //   xmodem__Erase_Block(CLOUD_PROGAME1_START_ADDRESS,CLOUD_PROGAME4_END_ADDRESS); 
    }
    
    //拉退程序依据行程开关控制
    st_Stretch.mode = STRETCH_MODE_SWITCH;
    st_Stretch.PresetTime = 200;
    st_Stretch.active = false;
    st_GrowthStretch.active = false;
    
    
    st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;//全身气囊①
    st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist)/sizeof(struct AirBagStruct);
    st_AirBagArmSholderBackWaist.locate = AIRBAG_LOCATE_ARM_SHOLDER_WAIST;
    
    //--------------------------------------------------------------------------------//add  
    st_AirBagModeLegFootSeat_Growth.pAirBagArray = AirBagModeLegFootSeat_Growth;
    st_AirBagModeLegFootSeat_Growth.nTotalSteps = sizeof(AirBagModeLegFootSeat_Growth) / sizeof(struct AirBagStruct);
    st_AirBagModeLegFootSeat_Growth.locate = AIRBAG_LOCATE_LEG_FOOT_SEAT;  
    //----------------------------------------------------------------------------------------
    st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;//全身气囊②，气囊复选
    st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat)/sizeof(struct AirBagStruct);
    st_AirBagModeLegFootSeat.locate = AIRBAG_LOCATE_LEG_FOOT_SEAT;
    
    st_AirBagLegFoot.pAirBagArray = AirBagModeLegFoot;//腿脚气囊
    st_AirBagLegFoot.nTotalSteps = sizeof(AirBagModeLegFoot)/sizeof(struct AirBagStruct);
    st_AirBagLegFoot.locate = AIRBAG_LOCATE_LEG_FOOT;
    
    st_AirBagBackWaist.pAirBagArray = AirBagModeBackWaist;//未使用
    st_AirBagBackWaist.nTotalSteps = sizeof(AirBagModeBackWaist)/sizeof(struct AirBagStruct);
    st_AirBagBackWaist.locate = AIRBAG_LOCATE_BACK_WAIST;
    
    st_AirBagArmSholder.pAirBagArray = AirBagModeArmSholder;//臂肩气囊
    st_AirBagArmSholder.nTotalSteps = sizeof(AirBagModeArmSholder)/sizeof(struct AirBagStruct);
    st_AirBagArmSholder.locate = AIRBAG_LOCATE_ARM_SHOLDER;
    
    st_AirBagSeat.pAirBagArray = AirBagModeSeat;//臀部气囊
    st_AirBagSeat.nTotalSteps = sizeof(AirBagModeSeat)/sizeof(struct AirBagStruct);
    st_AirBagSeat.locate = AIRBAG_LOCATE_SEAT;
    
    st_AirBagArm.pAirBagArray = AirBagModeArm;//拉腿程序控制手臂
    st_AirBagArm.nTotalSteps = sizeof(AirBagModeArm)/sizeof(struct AirBagStruct);
    st_AirBagArm.locate = AIRBAG_LOCATE_ARM;
    
    /**********************气囊复选增加内容start************************/
    st_AirBagLegFoot_Seat.pAirBagArray     = AirBagModeLegFoot_Seat;
    st_AirBagLegFoot_Seat.nTotalSteps = sizeof(AirBagModeLegFoot_Seat)/sizeof(struct AirBagStruct);
    st_AirBagLegFoot_Seat.locate = AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_SEAT;
    
    st_AirBagLegFoot_ArmSholder.pAirBagArray      = AirBagModeLegFoot_ArmSholder;
    st_AirBagLegFoot_ArmSholder.nTotalSteps = sizeof(AirBagModeLegFoot_ArmSholder)/sizeof(struct AirBagStruct);
    st_AirBagLegFoot_ArmSholder.locate = AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_ARM_SHOLDER;
    
    st_AirBagArmSholder_Seat.pAirBagArray         = AirBagModeArmSholder_Seat;
    st_AirBagArmSholder_Seat.nTotalSteps = sizeof(AirBagModeArmSholder_Seat)/sizeof(struct AirBagStruct);
    st_AirBagArmSholder_Seat.locate = AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT;
    
    st_AirBagLegFoot_ArmSholder_Seat.pAirBagArray = AirBagModeLegFoot_ArmSholder_Seat;
    st_AirBagLegFoot_ArmSholder_Seat.nTotalSteps = sizeof(AirBagModeLegFoot_ArmSholder_Seat)/sizeof(struct AirBagStruct);
    st_AirBagLegFoot_ArmSholder_Seat.locate = AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT;    
    /***********************气囊复选增加内容end*************************/
    
    
    //AirBagModeLegFoot_GrowthA 
    GrowthStepMaxA =85;// sizeof(AirBagModeLegFoot_GrowthA) / sizeof(struct AirBagStruct);  
    GrowthStepMaxB =82;// sizeof(AirBagModeLegFoot_GrowthB) / sizeof(struct AirBagStruct);
    //GrowthStepMaxB=sizeof(AirBagModeLegFootSeat_Growth) / sizeof(struct AirBagStruct);
    
    //bKneckCheckSwitchLast = Input_GetVout();
    
    //Back Variables
    nBackMainRunMode = BACK_MAIN_MODE_IDLE ;
    nKeyBackLocate = LOCATE_NONE;   //全程，局部，定点定位标志
    nKeyKneadWidth = KNEAD_WIDTH_UNKNOWN ;
    nKeyKneadKnockSpeed = SPEED_0 ;
    //Walk Motor Variables
    bWalkMotorInProcess = FALSE ;
    nWalkMotorControlParam1 = WALK_LOCATE_PARK ;
    nWalkMotorControlParam2 = 0 ;
    bUpdateLocate = TRUE ;     //行走电机坐标更新标志，置位时更新一次坐标
    nShoulderPosition = DEFAULT_SHOULDER_POSITION ;
    BodyDataRefresh() ;
    nKneadMotorControlParam1 = KNEAD_STOP ;
    nFinalKneadMotorState = STATE_IDLE ;
    //nLastKneadPosition = KNEAD_WIDTH_UNKNOWN ;
    // nCurBackPadMotorState = STATE_IDLE ;
    // nCurLegPadMotorState = STATE_IDLE ;
    
    nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
    nFinalWalkMotorLocate = TOP_POSITION;
    // bRunTimeChange = TRUE ;
    
    ////bMP3_AD_Enable = FALSE;
    //Communication
    bMasterSendPacket = FALSE ;  
    //nSendPacketID = PACKET_MASTER_GET_COMMAND ;
    nBuzzerMode = BUZZER_MODE_OFF ;
    bSendBuzzerMode = TRUE ;
    //刚上电时 ，小腿伸缩电机复位，方便EMC找脚
    nTargetMassagePosition =MASSAGE_POWER_ON_POSITION;// MASSAGE_RESET_POSITION;   //目标按摩位置
    bMassagePositionUpdate =1;// FALSE;
    
    w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60;
    
    bBlueToothStatus = ReadEEByte(USER_DATA_BASE + BLUETOOTH_STATUS_ADDRESS);
    bRestSleepStatus = 0;//ReadEEByte(USER_DATA_BASE + REST_SLEEP_MODE_ADDRESS); 
    //滚轮数据初始化
    //nRollerPWM = 0;
    bRollerEnable = false;
    //扭腰数据初始化
    
    Data_Init();
    // LEUART0_Initial_Data();
    
    SignalBoard_Initial_Data();//读取行程开关
    Flex_In_Fault=0;//新移植
    bTapping = 0;
    SetRockStep(StartRock);//摇椅步骤
    nKneadTurn = 0;
    
    // 3D_Massage_Initial_Data();//
    memset(OutBuffer,0,sizeof(OutBuffer))  ;
    memset(InBuffer,0,sizeof(InBuffer))  ;
    
    memset(&st_Stretch,0,sizeof(StretchStruct));
    
    Valve_Initial_Data();
    nCurActionStep = 0;
    
    ShoulderSteps = BODY_DETECT_OVER;
    BodyDetectStep = DETECT_NO_START;
    
    Timer_Initial();
    
    nKeyAxisStrength = 2;
    nVoicekey = H10_KEY_NONE;
    
    //---------------------------  //区分DIY  键和语音按键标志位
    bGetDIY_keyflag=0;
    //----------------------------     
    by_moni_cmd_tm_en = 0;
    
    
    nHeatStreng=0;
    bLanguageFlag = ReadEEByte(USER_DATA_BASE + LANGUAGE_ADDRESS);
    
    //    UartLeg_init_data();
    
    bAngleNoChangeProcess = FALSE;
    bAngleNoChangeCMD = FALSE; 
    
    bSet485Send(true);
    //bLegKneadEnable=0;
    SetRockStep(StartRock);
    SetbRockEnable(FALSE);
    SetnRockModeEnterExit(ExitRock);
    
    nStretchVigor=3; //默认拉筋是3档
    bLedFlag = 1;//LED默认是打开
    bZero_ShowFlag = 0;//零重力显示标志位
}
 
unsigned char Main_GetKey(void)
{
    //static int count = 0 ;
    unsigned char by_Key = H10_KEY_NONE;;
    if(HandUart_GetRXStatus() == TRUE)
    {
        HandUart_ClearRXStatus();
        by_Key = HandUart_GetKey();
        HandUart_SetKey(H10_KEY_NONE);
        return by_Key;
    }
    
    //    if(VoiceUart_GetRXStatus() == TRUE)
    //    { bGetDIY_keyflag=0;
    //        VoiceUart_ClearRXStatus();
    //        //printf("%d:[%d]\n",count++,VoiceUart_GetKey());
    //        switch (VoiceUart_GetKey())
    //       {
    //       case 0x01: by_Key = H10_KEY_CHAIR_AUTO_1 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //       bGetDIY_keyflag=0;
    //       break;  
    //       case 0x02: by_Key = H10_KEY_CHAIR_AUTO_3 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //       bGetDIY_keyflag=0;
    //       break;
    //       case 0x03: by_Key = H10_KEY_CHAIR_AUTO_0 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;
    //       case 0x04: by_Key = H10_KEY_CHAIR_AUTO_2 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;
    //       case 0x05: by_Key = H10_KEY_CHAIR_AUTO_4 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;
    //       case 0x06: by_Key = H10_KEY_CHAIR_AUTO_5 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;
    //       case 0x07: by_Key = H10_KEY_AIRBAG_AUTO | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;  
    //       case 0x08: by_Key = H10_KEY_3DMODE_1 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;  
    //       case 0x09: by_Key = H10_KEY_3DMODE_2 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;  
    //       case 0x0a: by_Key = H10_KEY_3DMODE_3 | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;  
    //       case 0x0b: by_Key = H10_KEY_POWER_SWITCH | VOICE_KEY_MASK;   BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;  
    //       case 0x20: by_Key = H10_KEY_VOICE_OFF;   BlueToothUart_AMP_Volume_Off();
    //        bGetDIY_keyflag=0;
    //       break;
    //       case 0x21: by_Key = H10_KEY_VOICE_ON;   //BlueToothUart_AMP_Volume_On();
    //        bGetDIY_keyflag=0;
    //       break;
    //       default: break;
    //       }
    //        return by_Key;
    //    }
    
    if(UartLeg_GetVoiceRXState() == TRUE)
    {
        UartLeg_ClearVoiceRXState();
        by_Key = UartLeg_GetVoiceKey();
        UartLeg_SetVoiceKey(H10_KEY_NONE);
        return by_Key;
    }
    
    if(BlueToothUart_GetRXStatus() == TRUE)//get_key
    {
        BlueToothUart_ClearRXStatus();
        by_Key = BlueToothUart_GetKey();
        BlueToothUart_SetKey(H10_KEY_NONE);
//        if(by_Key>=0x80)
//        {
//            bGetDIY_keyflag=1;
//        }
        return by_Key;
    }
    return by_Key;
}

void Main_Walk_Beep_Proce(void)
{
 
  if(bKeyWalkUp == TRUE)
  {
    if(((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)||(nBackMainRunMode == BACK_MAIN_MODE_3D) )&& ((nKeyBackLocate == LOCATE_POINT)||(nKeyBackLocate == LOCATE_PARTIAL)))
    {
      if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
      {
        //设置连续蜂鸣器声音
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
      }
      else
      {
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
      }
    }
    //else if(nBackMainRunMode == BACK_MAIN_MODE_3D)
    else if(/*(nBackMainRunMode == BACK_MAIN_MODE_AUTO) && */(ShoulderSteps == BODY_DETECT_ADJ))
    {
      if(Input_GetWalkMotorPosition() >= nShoulderPositionTop - 3)
      {
        //设置连续蜂鸣器声音
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
      }
      else
      {
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
      }
    }
  }
  if(bKeyWalkDown == TRUE)
  {
      if(((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)||(nBackMainRunMode == BACK_MAIN_MODE_3D) )&& ((nKeyBackLocate == LOCATE_POINT)||(nKeyBackLocate == LOCATE_PARTIAL)))
    {
      //设置连续蜂鸣器声音
      if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
      {
        //设置连续蜂鸣器声音
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
      }
      else
      {
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
      }
    }
    else if(/*(nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&*/ (ShoulderSteps == BODY_DETECT_ADJ))
    {
      if(Input_GetWalkMotorPosition() <= nShoulderPositionBottom + 3)
      {
        //设置连续蜂鸣器声音
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
      }
      else
      {
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
      }
    }
  }
}
//停止所有的执行装置
void Main_Stop_All(void)
{
    WaistHeat_Off();
    WalkMotor_Control(STATE_WALK_IDLE, 0);
    KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
    LegMotor_Control(STATE_LEG_IDLE);
    BackMotor_Control(STATE_BACK_IDLE);
    SlideMotorControl(STATE_SLIDE_IDLE);
    FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
    KnockMotor_Set_Pwm_Data(0);
    
    LED_RGB_Set_All(0);
    AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8);
    Valve_CloseAll();
    //LegKnead_SetPower(LEG_KNEAD_OFF);
    RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
}

void engineering_stop_all(void)
{
 Main_Stop_All(); 
}

BITS engineerData1old;
#define walk_up_old         engineerData1old.bD0
#define walk_down_old       engineerData1old.bD1
#define shoulder_detect_old engineerData1old.bD2
#define knead_width_min_old engineerData1old.bD3
#define knead_width_mid_old engineerData1old.bD4
#define knead_width_max_old engineerData1old.bD5
#define back_up_old         engineerData1old.bD6
#define back_down_old       engineerData1old.bD7
BITS engineerData2old;
#define leg_up_old          engineerData2old.bD0
#define leg_down_old        engineerData2old.bD1
#define test_finish         engineerData2old.bD2
#define foot_Switch_old     engineerData2old.bD3
#define _3D_Switch_Forward  engineerData2old.bD4
#define _3D_Switch_Back     engineerData2old.bD5
#define _3D_Switch_Pluse    engineerData2old.bD6


//#define test_finish     engineerData2old.bD2
BITS engineerData1;
#define walk_up         engineerData1.bD0
#define walk_down       engineerData1.bD1
#define shoulder_detect engineerData1.bD2
#define knead_width_min engineerData1.bD3
#define knead_width_mid engineerData1.bD4
#define knead_width_max engineerData1.bD5
#define back_up         engineerData1.bD6
#define back_down       engineerData1.bD7
BITS engineerData2;
#define leg_up          engineerData2.bD0
#define leg_down        engineerData2.bD1
#define has_leg         engineerData2.bD2
#define knock           engineerData2.bD3
#define roller          engineerData2.bD4
#define heat            engineerData2.bD5
#define has_heat        engineerData2.bD6
#define air_bag         engineerData2.bD7

BITS engineerData5;
#define slide_backward  engineerData5.bD0
#define slide_forward   engineerData5.bD1
#define flex_up         engineerData5.bD2
#define flex_down       engineerData5.bD3
#define foot_Switch     engineerData5.bD4
#define leg_angle       engineerData5.bD5
#define leg_ground      engineerData5.bD6
#define knead_phase     engineerData5.bD7

typedef union
{
    struct
    {
        unsigned bD0: 2 ;
        unsigned bD1: 2 ;
        unsigned bD2: 2 ;
        unsigned bD3: 2 ;
    } ;
    unsigned char nByte ;
} BITS2 ;
BITS2 engineerData3;
#define walk_check_count     engineerData3.bD0
#define shoulder_check_count engineerData3.bD1
#define knead_check_count    engineerData3.bD2
#define back_check_count     engineerData3.bD3

BITS2 engineerData4;
#define leg_check_count      engineerData4.bD0
#define TIME_COUNT      100
//此函数执行完毕会引起CPU复位
void Main_Engineering(void)
{
    unsigned short nLegAngleOld,nLegGroundOld;
    int leg_flex_step = 0;
    int slide_step = 0;
    has_heat = 1;
    has_leg = 1;
    heat = 1;
    knock = 1;
    roller = 1;
    //bool strengthMode,sleepMode;
    unsigned int back_position, walk_position;
    unsigned char oneKeyStep = 0, oneKeyStepLength = 4, enAirbagStep;
    unsigned char oneKeyLegCountDown = 0;
    unsigned int engineerTimeCount = 0, air_bagTimeCount = 0;
    unsigned short /*adcWalkCurrent,*/adcAxisCurrent/*,adcKnockCurrent*/,adc24,adcVcc,adc24_1,tempture;
    //unsigned int counter = 0;
    int engStatus = LINGO_ENG;
    unsigned int overCounter = 0;
    bool status = true;
    bool bProgram = false;
    char lingo;
    bool bHeat = false;
    char command;
    unsigned char PWM = 0;
    unsigned char ROLLER_PWM = 0;
    char airbagIndex = 1,airpumpIndex = 7;
    unsigned int airbag;
    unsigned int pw_Information[10];
    unsigned char strength;
    unsigned char rollerSpeed = 0;
    unsigned char rollerPhase = 0;
    unsigned char legKneadSpeed = 0;
    unsigned char legKneadPhase = 0;
    unsigned char color;
    unsigned char kneadSpeed = 0;
    unsigned char kneadPhase = 0;
    bool bUpKey = false;
    bool bDownKey = false;
    Power_All_On();
    IndicateLED_On();
    //  ADC_Get_Voltage(ADC_VCC,&adcVcc); 
    ADC_Get_Voltage(ADC_V24,&adc24); 
    //  ADC_Get_Voltage(ADC_V24_1,&adc24_1); 
    tempture = ADC_Get_Inttemp();
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);//从User_data内存空间的起始地址开始获取14个字节放入pw_Information中
    
    // BlueToothEnterCmdMode();  //蓝牙模块工作在命令模式
    
    //  BlueToothUart_GetName();
    
    while(status)
    { 
        Main_Send_Leg();
        //WDOG_Feed();
        lingo = Main_GetKey();
        switch(lingo)
        {
        case LINGO_AIRBAG: 
            {
                engStatus = LINGO_AIRBAG;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    airbagIndex &= 0x7f;
                    airbagIndex++;
                    airbagIndex %= 24;
                    break;
                case SYS_KEY_DOWN:
                    airbagIndex &= 0x7f;
                    airbagIndex--;
                    if(airbagIndex > 24)
                        airbagIndex = 23;
                    break;
                case SYS_KEY_LEFT:
                    airpumpIndex++;
                    airpumpIndex &= 0x03;
                    break;
                case SYS_KEY_RIGHT:
                    airpumpIndex--;
                    airpumpIndex &= 0x03;
                    break; 
                case SYS_KEY_ENTER:
                    airbagIndex |= 0x80;
                    break;   
                }
            }
            break;
            //用滚轮测试程序代替小腿揉搓程序    
        case LINGO_ROLLER_TEST: 
            {
                engStatus = LINGO_ROLLER_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    if(rollerSpeed < 3)
                        rollerSpeed++;
                    break;
                case SYS_KEY_DOWN:
                    if(rollerSpeed > 0)
                        rollerSpeed--;
                    break;
                case SYS_KEY_LEFT:
                case SYS_KEY_RIGHT:  
                    if(rollerPhase == 0)
                        rollerPhase = 1;
                    else
                        rollerPhase = 0;
                    break;
                case SYS_KEY_ENTER:
                    break;   
                }
            }
            break; 
            
            
        case LINGO_LEG_KNEAD_TEST:
            {
                engStatus = LINGO_LEG_KNEAD_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    if(legKneadSpeed < 3)
                        legKneadSpeed++;
                    break;
                case SYS_KEY_DOWN:
                    if(legKneadSpeed > 0)
                        legKneadSpeed--;
                    break;
                case SYS_KEY_LEFT:
                case SYS_KEY_RIGHT:  
                    if(legKneadPhase == 0)
                        legKneadPhase = 1;
                    else
                        legKneadPhase = 0;
                    break;
                case SYS_KEY_ENTER:
                    break;   
                }
            }
            break; 
            
        case LINGO_SLIDE_TEST: 
            {
                engStatus = LINGO_SLIDE_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;  
        case LINGO_BACK_TEST: 
            {
                engStatus = LINGO_BACK_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;
        case LINGO_LEG_TEST: 
            {
                engStatus = LINGO_LEG_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;               
        case LINGO_ONE_KEY_TEST:
            {
                engStatus = LINGO_ONE_KEY_TEST;
                command = HandUart_GetExternKey();
                engineerTimeCount = 1, air_bagTimeCount = 1; //清时间，不设零防止跳到下一步
                switch(command)
                {
                case SYS_KEY_UP://上一步
                    if(oneKeyStep > 1)oneKeyStep--;
                    else oneKeyStep = oneKeyStepLength;
                    if(test_finish && oneKeyStep == 0)oneKeyStep = oneKeyStepLength;
                    break;
                case SYS_KEY_DOWN://下一步
                    if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                    else oneKeyStep = 0;
                    break;
                case SYS_KEY_LEFT://开，并且下一步(或气囊：上一步)
                    switch(oneKeyStep)
                    {
                    case 1:
                        if(has_heat)heat = 1;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 2:
                        knock = 1;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 3:
                        roller = 1;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 4:
                        air_bag = 1;
                        if(enAirbagStep > 0)
                        {
                            enAirbagStep--;
                        }
                        else
                        {
                            enAirbagStep = 24;
                        }
                        break;
                    }
                    break;
                case SYS_KEY_RIGHT://关，并且下一步(或气囊：下一步)
                    switch(oneKeyStep)
                    {
                    case 1:
                        if(has_heat)heat = 0;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 2:
                        knock = 0;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 3:
                        roller = 0;
                        if(oneKeyStep < oneKeyStepLength)oneKeyStep++;
                        else oneKeyStep = 0;
                        break;
                    case 4:
                        air_bag = 1;
                        if(enAirbagStep < 24)
                        {
                            enAirbagStep++;
                        }
                        else
                        {
                            enAirbagStep = 0;
                        }
                        break;
                    }
                    break;
                case 248://菜单中进入此界面
                    //初始化
                    engineerData1old.nByte = 0;
                    engineerData2old.nByte = 0;
                    engineerData3.nByte = 0;
                    engineerData4.nByte = 0;
                    oneKeyStep = 0;
                    enAirbagStep = 0;
                    test_finish = 0;
                    heat = 1;
                    knock = 1;
                    roller = 1;
                    air_bag = 1;
                    walk_up = 0;
                    walk_down = 0;
                    shoulder_detect = 0;
                    knead_width_min = 0;
                    knead_width_mid = 0;
                    knead_width_max = 0;
                    leg_up = 0;
                    leg_down = 0;
                    back_up = 0;
                    back_down = 0;
                    back_position = 0;
                    walk_position = 0;
                    engineering_stop_all();
                    engineerData5.nByte = 0;
                    
                    leg_flex_step = 0;
                    slide_step = 0;
                    
                    nLegAngleOld = nLegAngle; 
                    //nLegGroundOld = nLegGround;
                    nLegGroundOld = Input_GetFlexGroundSwitch();
                    //leg_ground_old = Input_GetFlexGroundSwitch();   
                    
//                    if(nFlexStatus&0x04) 
//                    {
//                        foot_Switch_old = 1;
//                    }
//                    else
//                    {
//                        foot_Switch_old = 0;
//                    }
                    if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) 
                    {
                        foot_Switch_old = 1;
                    }
                    else
                    {
                        foot_Switch_old = 0;
                    }
                    shoulder_detect_old = Input_GetVout(); 
                    
                    break;
                case 15:
                    engineering_stop_all();
                    oneKeyStep = 0;
                    break;
                default:
                    break;
                }
            }
            break;   
            
        case LINGO_HEAT_TEST:
            {
                engStatus = LINGO_HEAT_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_ENTER:
                    if(bHeat) 
                    {
                        bHeat = 0;
                        WaistHeat_Off();
                    }
                    else
                    {
                        bHeat = 1;
                        WaistHeat_On();
                    } 
                    break;
                }
            }
            break;
            
        case LINGO_FLEX_TEST: 
            {
                engStatus = LINGO_FLEX_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;
            
        case LINGO_WALK_TEST: 
            {
                engStatus = LINGO_WALK_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;     
            
        case LINGO_3D_TEST: 
            {
                engStatus = LINGO_3D_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    bUpKey = true;
                    bDownKey = false;
                    break;
                case SYS_KEY_UP_RELEASE: 
                case SYS_KEY_DOWN_RELEASE: 
                    bUpKey = false;
                    bDownKey = false;
                    break;
                case SYS_KEY_DOWN:
                    bUpKey = false;
                    bDownKey = true;
                    break;
                }
            }
            break;     
            
        case LINGO_LED_TEST:  
            {
                engStatus = LINGO_LED_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    break;
                case SYS_KEY_DOWN:
                    break;
                case SYS_KEY_LEFT:
                case SYS_KEY_RIGHT:  
                    break;
                case SYS_KEY_ENTER:
                    color++;
                    color %= 3;
                    break;   
                }
            }
            break;
        case LINGO_KNEAD_TEST: 
            {
                engStatus = LINGO_KNEAD_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    if(kneadSpeed < 6)
                        kneadSpeed++;
                    break;
                case SYS_KEY_DOWN:
                    if(kneadSpeed > 0)
                        kneadSpeed--;
                    break;
                case SYS_KEY_LEFT:
                case SYS_KEY_RIGHT:  
                    if(kneadPhase == 0)
                        kneadPhase = 1;
                    else
                        kneadPhase = 0;
                    break;
                case SYS_KEY_ENTER:
                    break;   
                }
            }
            break;  
        case LINGO_KNOCK_TEST: 
            {
                engStatus = LINGO_KNOCK_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    if(kneadSpeed < 6)
                        kneadSpeed++;
                    break;
                case SYS_KEY_DOWN:
                    if(kneadSpeed > 0)
                        kneadSpeed--;
                    break;
                case SYS_KEY_LEFT:
                case SYS_KEY_RIGHT:  
                    if(kneadPhase == 0)
                        kneadPhase = 1;
                    else
                        kneadPhase = 0;
                    break;
                case SYS_KEY_ENTER:
                    break;   
                }
            }
            break;   
        case LINGO_INPUT: 
            {
                engStatus = LINGO_INPUT;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    break;
                case SYS_KEY_DOWN:
                    break;
                case SYS_KEY_LEFT:
                    break;
                case SYS_KEY_RIGHT:
                    break; 
                case SYS_KEY_ENTER:
                    break;   
                }
            }
            break;
        case LINGO_MUSIC_TEST:
            {
                engStatus = LINGO_MUSIC_TEST;
                command = HandUart_GetExternKey();
                switch(command)
                {
                case SYS_KEY_UP: 
                    break;
                case SYS_KEY_DOWN:
                    break;
                case SYS_KEY_LEFT:
                    break;
                case SYS_KEY_RIGHT:
                    break; 
                case SYS_KEY_ENTER:
                    //Power_AMP_Off();
                    Timer_Counter_Clear(C_TIMER_TEMP);
                    break;   
                }
            }
            break;
        case LINGO_PROGRAM: //设置更新标志p
            engStatus = LINGO_PROGRAM;
            if(*(pInformation + PROGRAM_ENABLE_ADDRESS) != PROGRAM_FLAG)
            {
                *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_FLAG; //写编程标志位
                MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            }
            bProgram = true;
            break;
        case LINGO_PROGRAM_BY_BLUETOOTH: 
            break;
        case LINGO_BLUETOOTH_BR115200:
            break;  
        case LINGO_ENG:
            {
                ADC_Stop();
                engStatus = LINGO_ENG;
                command = HandUart_GetExternKey(); 
                switch(command) 
                {
                case ENG_CMD_RESET:  //设置关机是否复位
                    
                    if(*(pInformation + SETTLE_ADDRESS))
                    {
                        *(pInformation + SETTLE_ADDRESS) = 0; 
                    }
                    else
                    {
                        *(pInformation + SETTLE_ADDRESS) = 1; 
                    }
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    break;  
                case ENG_CMD_DEC_STRENGTH:  //气囊力度减1（设置默认气囊力度）
                    strength = *(pInformation + AIRBAG_STRETCH_ADDRESS);
                    if(strength == 0) break;
                    strength--;
                    strength %= 3;  //防止因为断电等原因导致数据错误
                    *(pInformation + AIRBAG_STRETCH_ADDRESS) = strength; 
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    break;
                case ENG_CMD_ADD_STRENGTH:  //气囊力度加1（设置默认气囊力度）
                    strength = *(pInformation + AIRBAG_STRETCH_ADDRESS);
                    if(strength >= 2) break;
                    strength++;
                    *(pInformation + AIRBAG_STRETCH_ADDRESS) = strength; 
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    break;
                case ENG_CMD_SLIDE:   //滑动使能禁止
                    if(*(pInformation + SLIDE_MOTOR_ENABLE_ADDRESS))
                    {
                        *(pInformation + SLIDE_MOTOR_ENABLE_ADDRESS) = 0;   
                    }
                    else
                    {
                        *(pInformation + SLIDE_MOTOR_ENABLE_ADDRESS) = 1; 
                    }
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    break;
//                case ENG_CMD_ARM:
//                    if(*(pInformation + ARM_MOTOR_SWITCH_ADDRESS))
//                    {
//                        __NOP();
//                        *(pInformation + ARM_MOTOR_SWITCH_ADDRESS) = 0;   
//                    }
//                    else
//                    {
//                        __NOP();
//                        *(pInformation + ARM_MOTOR_SWITCH_ADDRESS) = 1; 
//                    }
//                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
//                    break;
                case ENG_CMD_REST_SLEEP:
                    if(*(pInformation + REST_SLEEP_MODE_ADDRESS))
                    {
                        *(pInformation + REST_SLEEP_MODE_ADDRESS) = 0; 
                    }
                    else
                    {
                        *(pInformation + REST_SLEEP_MODE_ADDRESS) = 1; 
                    }
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    
                    break;
                default: break;    
                }
            }
            break;
        case LINGO_RESET:  
            password = 0;  
            NVIC_SystemReset();
            break; //复位CPU
        case LINGO_MENU:  
            engStatus = LINGO_MENU;
            break; //复位CPU
        }
        /*******以下程序为气囊测试*************************/  
        switch(engStatus)
        {
            
        case LINGO_ONE_KEY_TEST:
            {
                //检测信号 TODO,测试无信号时的情况
                Input_Proce();
                //使用中断标志
                if(engineeringTime_10msFlag)
                {
                    engineerTimeCount++;
                    engineerTimeCount %= 10 * TIME_COUNT; //10秒走一步
                    air_bagTimeCount++;
                    air_bagTimeCount %= 7 * TIME_COUNT; //10秒走一步
                    if(oneKeyLegCountDown > 0)oneKeyLegCountDown--;
                    //时间中断清零
                    engineeringTime_10msFlag = 0;
                }
                //实现
                //参数
                //back_position = Input_GetBackMotorPosition();
                back_position = 0;
                walk_position = Input_GetWalkMotorPosition();
                //自动测试步骤
                if(oneKeyStep == 0)
                {
                    //行走
                    if(!walk_up)
                    {
                        if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
                        {
                            if(walk_up_old == 0)
                            {
                                if(walk_check_count < 3)
                                {
                                    walk_check_count++;
                                }
                                else
                                {
                                    //上行程OK
                                    walk_up = 1;
                                    //清零
                                    walk_check_count = 0;
                                }
                            }
                            WalkMotor_Control(STATE_RUN_WALK_DOWN, 0);
                        } 
                        else
                        {
                            WalkMotor_Control(STATE_RUN_WALK_UP, 0);
                        }
                    }//肩位
                    else if(!walk_down)
                    {
                        if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
                        {
                            Input_SetWalkMotorPosition(0);
                            if(walk_down_old == 0)
                            {
                                if(walk_check_count < 3)
                                {
                                    walk_check_count++;
                                }
                                else
                                {
                                    //下行程OK
                                    walk_down = 1;
                                    //清零
                                    walk_check_count = 0;
                                }
                            }
                            WalkMotor_Control(STATE_RUN_WALK_UP, 0);
                        }
                        else
                        {
                            WalkMotor_Control(STATE_RUN_WALK_DOWN, 0);
                        }
                    }
                    else
                    {
                        if(Input_GetWalkUpSwitch() != REACH_WALK_LIMIT)
                        {
                            WalkMotor_Control(STATE_RUN_WALK_UP, 0);
                        }
                        else
                        {
                            WalkMotor_Control(STATE_WALK_IDLE, 0);
                        }
                    }
                    //揉捏
                    if(!knead_width_min)
                    {
                        if(Input_GetKneadMin() == 0)
                        {
                            if(knead_width_min_old == 0)
                            {
                                if(knead_check_count < 3)
                                {
                                    knead_check_count++;
                                }
                                else
                                {
                                    //OK
                                    knead_width_min = 1;
                                    //清零
                                    knead_check_count = 0;
                                }
                            }
                            KneadMotor_Control(STATE_KNEAD_CLOCK_RUN, KNEAD_SPEED1_PWM);
                        }
                        else
                        {
                            KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN, KNEAD_SPEED1_PWM);
                        }
                    }
                    else if(!knead_width_mid)
                    {
                        if(Input_GetKneadMid() == 0)
                        {
                            if(knead_width_mid_old == 0)
                            {
                                if(knead_check_count < 3)
                                {
                                    knead_check_count++;
                                }
                                else
                                {
                                    //OK
                                    knead_width_mid = 1;
                                    //清零
                                    knead_check_count = 0;
                                }
                            }
                            KneadMotor_Control(STATE_KNEAD_CLOCK_RUN, KNEAD_SPEED6_PWM);
                        }
                        else
                        {
                            KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN, KNEAD_SPEED6_PWM);
                        }
                    }
                    else if(!knead_width_max)
                    {
                        if(Input_GetKneadMax() == 0)
                        {
                            if(knead_width_max_old == 0)
                            {
                                if(knead_check_count < 3)
                                {
                                    knead_check_count++;
                                }
                                else
                                {
                                    //OK
                                    knead_width_max = 1;
                                    //清零
                                    knead_check_count = 0;
                                }
                            }
                            KneadMotor_Control(STATE_KNEAD_CLOCK_RUN, KNEAD_SPEED1_PWM);
                        }
                        else
                        {
                            KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN, KNEAD_SPEED1_PWM);
                        }
                    }
                    else if (!_3D_Switch_Forward)
                    {
                        KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
                        if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_7))
                            //if(Input_Get3DFrontSwitch()) 
                        {
                            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
                            _3D_Switch_Forward = 1;
                            //printf("3d_forward\n");
                        }
                    }
                    else if (!_3D_Switch_Back)
                    {
                        if(AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_7))
                            //if(Input_Get3DBackSwitch()) 
                        {
                            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
                            _3D_Switch_Back = 1;
                            //printf("3d_back\n");
                        }
                    }
                    else if (!_3D_Switch_Pluse)
                    {
                        if(AxisMotor_Control(STATE_RUN_AXIS_REAL_POSITION,20,_3D_SPEED_7))
                        {
                            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
                            _3D_Switch_Pluse = 1;
                            // printf("3d_pluse\n");
                        }
                    }
                    else AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8); 
                    
                    //小腿
                    if(has_leg)
                    {
                        //                  Flex_SetDisableAngle(1);//cyw
                        if((!leg_up) &&(!leg_down)&&(!flex_up)&&(!flex_down))  
                        {   //测试小腿上行程开关
                            //FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                            FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
                            switch(leg_flex_step)
                            {
                            case 0:  //到达up位置
                                if(LegMotor_Control(STATE_RUN_LEG_UP)) 
                                {
                                    leg_flex_step++;
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                }
                                break;  
                            case 1:  //停在up位置0.5秒
                                LegMotor_Control(STATE_LEG_IDLE);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;  
                            case 2:  //离开up位置
                                LegMotor_Control(STATE_RUN_LEG_DOWN);
                                if(Input_GetLegUpSwitch() != REACH_LEG_LIMIT)
                                {
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                    leg_flex_step++;
                                }
                                break;
                            case 3:  //停0.5秒
                                LegMotor_Control(STATE_LEG_IDLE);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;
                            case 4:  //到达up位置
                                if(LegMotor_Control(STATE_RUN_LEG_UP)) 
                                {
                                    leg_flex_step = 0;
                                    leg_up = 1;
                                }
                                break;       
                            }
                        }
                        if((leg_up) &&(!leg_down)&&(!flex_up)&&(!flex_down))  
                        {//测试电动伸缩小腿上（外）行程开关
                            LegMotor_Control(STATE_LEG_IDLE);
                            switch(leg_flex_step)
                            {
                            case 0:  //到达up位置
                                //if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
                                if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlOut(FLEX_MOTOR_CURRENT_3A))
                                {
                                    leg_flex_step++;
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                }
                                break;  
                            case 1:  //停在up位置0.5秒
                                //FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;  
                            case 2:  //离开up位置
                                //FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlIn(FLEX_MOTOR_CURRENT_3A))
                                    //if(Input_GetFlexOutSwitch() != REACH_FLEX_LIMIT)
                                {
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                    leg_flex_step++;
                                }
                                break;
                            case 3:  //停0.5秒
                                //FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;
                            case 4:  //到达up位置
                                // if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
                                if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlOut(FLEX_MOTOR_CURRENT_3A))
                                {
                                    leg_flex_step = 0;
                                    flex_up = 1;
                                }
                                break;       
                            }
                        }
                        if((leg_up) &&(!leg_down)&&(flex_up)&&(!flex_down))  
                        {//测试电动伸缩小腿上（外）行程开关
                            LegMotor_Control(STATE_LEG_IDLE);
                            switch(leg_flex_step)
                            {
                            case 0:  //到达in位置
                                if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlIn(FLEX_MOTOR_CURRENT_3A))
                                    //if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
                                {
                                    leg_flex_step++;
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                }
                                break;  
                            case 1:  //停在in位置0.5秒
                                // FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;  
                            case 2:  //离开in位置
                                //FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                //if(Input_GetFlexInSwitch() != REACH_FLEX_LIMIT)
                                if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlOut(FLEX_MOTOR_CURRENT_3A))
                                {
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                    leg_flex_step++;
                                }
                                break;
                            case 3:  //停0.5秒
                                // FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;
                            case 4:  //到达In位置
                                // if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))
                                if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlIn(FLEX_MOTOR_CURRENT_3A))
                                {
                                    leg_flex_step = 0;
                                    flex_down = 1;
                                }
                                break;       
                            }
                        }
                        if((leg_up) &&(!leg_down)&&(flex_up)&&(flex_down))   
                        {   //测试小腿上行程开关
                            //FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A); //关闭电动伸缩小腿
                            switch(leg_flex_step)
                            {
                            case 0:  //到达down位置
                                if(LegMotor_Control(STATE_RUN_LEG_DOWN)) 
                                {
                                    leg_flex_step++;
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                }
                                break;  
                            case 1:  //停在DOWN位置0.5秒
                                LegMotor_Control(STATE_LEG_IDLE);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;  
                            case 2:  //离开DOWN位置
                                LegMotor_Control(STATE_RUN_LEG_UP) ;
                                if(Input_GetLegDownSwitch() != REACH_LEG_LIMIT);
                                {
                                    Timer_Counter_Clear(C_TIMER_ENG1);
                                    leg_flex_step++;
                                }
                                break;
                            case 3:  //停0.5秒
                                LegMotor_Control(STATE_LEG_IDLE);
                                if(Timer_Counter(C_TIMER_ENG1,5))
                                {
                                    leg_flex_step++;
                                }
                                break;
                            case 4:  //到达Down位置
                                if(LegMotor_Control(STATE_RUN_LEG_DOWN)) 
                                {
                                    leg_flex_step = 0;
                                    leg_down = 1;
                                }
                                break;       
                            }
                        }
                    }//has_leg
                    //靠背
                    
                    if(nLegAngle != nLegAngleOld)  
                    {
                        leg_angle = 1;
                    } 
//                    if(nLegGround != nLegGroundOld)  
//                    {
//                        leg_ground = 1;
//                    }
                    if(nLegGroundOld != Input_GetFlexGroundSwitch())
                    {
                        leg_ground = 1;
                    }
//                    if(nFlexStatus&0x04) 
//                    {
//                        if(foot_Switch_old == 0) foot_Switch = 1;
//                    }
//                    else
//                    {
//                        if(foot_Switch_old != 0) foot_Switch = 1;
//                    }
                    if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON)
                    {
                        if(foot_Switch_old == 0) foot_Switch = 1;
                    }
                    else
                    {
                        if(foot_Switch_old != 0) foot_Switch = 1;
                    }
                    if(Input_GetVout() == BODY_TOUCHED)
                    {
                        shoulder_detect = 1;
                    }
                    
                    if((!slide_backward) && (!slide_forward))
                    {   //测试前滑前行程开关
                        switch(slide_step)
                        {
                        case 0:  //到达最前位置
                            if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD))
                            {
                                slide_step++;
                                Timer_Counter_Clear(C_TIMER_ENG2);
                            }
                            break;  
                            //SlideMotorControl(STATE_RUN_SLIDE_BACKWARD);
                            //SlideMotorControl(STATE_SLIDE_IDLE);
                        case 1:  //停在最前位置0.5秒
                            SlideMotorControl(STATE_SLIDE_IDLE);
                            if(Timer_Counter(C_TIMER_ENG2,5))
                            {
                                slide_step++;
                            }
                            break;  
                        case 2: //离开最前位置
                            SlideMotorControl(STATE_RUN_SLIDE_BACKWARD);
                            if(Input_GetSlideForwardSwitch() != REACH_SLIDE_LIMIT)
                            {
                                Timer_Counter_Clear(C_TIMER_ENG2);
                                slide_step++;
                            }
                            break;
                        case 3:  //停0.5秒
                            SlideMotorControl(STATE_SLIDE_IDLE);
                            if(Timer_Counter(C_TIMER_ENG2,5))
                            {
                                slide_step++;
                            }
                            break;
                        case 4:  //到达最前位置
                            if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD))
                            {
                                slide_step = 0;
                                slide_forward = 1;
                            }
                            break;
                        } //end switch
                    }
                    
                    if((!slide_backward) && (slide_forward))
                    {   //测试前滑后行程开关
                        switch(slide_step)
                        {
                        case 0:  //到达最后位置
                            if(SlideMotorControl(STATE_RUN_SLIDE_BACKWARD))
                            {
                                slide_step++;
                                Timer_Counter_Clear(C_TIMER_ENG2);
                            }
                            break;  
                        case 1:  //停在最后位置0.5秒
                            SlideMotorControl(STATE_SLIDE_IDLE);
                            if(Timer_Counter(C_TIMER_ENG2,5))
                            {
                                slide_step++;
                            }
                            break;  
                        case 2: //离开最后位置
                            SlideMotorControl(STATE_RUN_SLIDE_FORWARD);
                            if(Input_GetSlideBackwardSwitch() != REACH_SLIDE_LIMIT)
                            {
                                Timer_Counter_Clear(C_TIMER_ENG2);
                                slide_step++;
                            }
                            break;
                        case 3:  //停0.5秒
                            SlideMotorControl(STATE_SLIDE_IDLE);
                            if(Timer_Counter(C_TIMER_ENG2,5))
                            {
                                slide_step++;
                            }
                            break;
                        case 4:  //到达最后位置
                            if(SlideMotorControl(STATE_RUN_SLIDE_BACKWARD))
                            {
                                slide_step = 0;
                                slide_backward = 1;
                            }
                            break;
                        } //end switch
                    }
                    if(!back_up)
                    {
                        if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
                        {
                            if(back_up_old == 0)
                            {
                                if(back_check_count < 3)
                                {
                                    back_check_count++;
                                }
                                else
                                {
                                    //OK
                                    back_up = 1;
                                    //清零
                                    back_check_count = 0;
                                }
                            }
                            BackMotor_Control(STATE_RUN_BACK_DOWN);
                        }
                        else
                        {
                            BackMotor_Control(STATE_RUN_BACK_UP);
                        }
                    }
                    else if(!back_down)
                    {
                        if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
                        {
                            if(back_down_old == 0)
                            {
                                if(back_check_count < 3)
                                {
                                    back_check_count++;
                                }
                                else
                                {
                                    //OK
                                    back_down = 1;
                                    //清零
                                    back_check_count = 0;
                                }
                            }
                            BackMotor_Control(STATE_RUN_BACK_UP);
                        }
                        else
                        {
                            BackMotor_Control(STATE_RUN_BACK_DOWN);
                        }
                    }
                    else
                    {
                        if(Input_GetBackUpSwitch() != REACH_BACK_LIMIT)
                        {
                            BackMotor_Control(STATE_RUN_BACK_UP);
                        }
                        else
                        {
                            BackMotor_Control(STATE_BACK_IDLE);
                        }
                    }
                    
                    if(walk_up && walk_down && shoulder_detect && knead_width_min && knead_width_mid
                       && knead_width_max && ((!has_leg) || (leg_up && leg_down)) && back_up && back_down 
                           && slide_backward && slide_forward && flex_up && flex_down && foot_Switch 
                               && leg_angle  && _3D_Switch_Forward && _3D_Switch_Back && _3D_Switch_Pluse)
                    {
                        if(oneKeyStep == 0)
                        {
                            oneKeyStep++;
                            engineerTimeCount = 1;
                        }
                    }
                }
                else
                {
                    if(Input_GetWalkUpSwitch() != REACH_WALK_LIMIT && walk_up)
                    {
                        WalkMotor_Control(STATE_RUN_WALK_UP, 0);
                    }
                    else
                    {
                        WalkMotor_Control(STATE_WALK_IDLE, 0);
                    }
                    if(Input_GetLegDownSwitch() != REACH_LEG_LIMIT && has_leg && leg_down)
                    {
                        LegMotor_Control(STATE_RUN_LEG_DOWN);
                    }
                    else
                    {
                        LegMotor_Control(STATE_LEG_IDLE);
                    }
                    if(Input_GetBackUpSwitch() != REACH_BACK_LIMIT && back_up)
                    {
                        BackMotor_Control(STATE_RUN_BACK_UP);
                    }
                    else
                    {
                        BackMotor_Control(STATE_BACK_IDLE);
                    }
                }
                //需手动配合的部分
                //加热
                if(has_heat)
                {
                    if(heat)WaistHeat_On();
                    else WaistHeat_Off();
                }
                //敲击
                if(knock == 1)
                {
                    if(engineerTimeCount < 9 * TIME_COUNT)
                    {
                        KnockMotor_ClockRun();
                        KnockMotor_Set_Pwm_Data(KNOCK_SPEED1_PWM);
                    }
                    else
                    {
                        KnockMotor_UnClockRun();
                        KnockMotor_Set_Pwm_Data(KNOCK_SPEED6_PWM);
                    }
                }
                else
                {
                    KnockMotor_Set_Pwm_Data(KNOCK_SPEED0_PWM);
                    KnockMotor_Break();
                }
                //滚轮
                if(roller)
                {
                    if(engineerTimeCount < 5 * TIME_COUNT)
                    {
                        RollerMotor_Control(ROLLER_SPEED_SLOW, 0);
                    }
                    else
                    {
                        RollerMotor_Control(ROLLER_SPEED_FAST, 1);
                    }
                }
                else
                {
                    RollerMotor_Control(ROLLER_SPEED_STOP, 0);
                }
                //气囊
                if(air_bag)
                {
                    // Vavle_Pump_Switch(0, 1);
                    // Vavle_Pump_Switch(1, 1);
                    Valve_BodyUpAirPumpACPowerOn();  //臂肩，背腰
                    Valve_LegFootAirPumpACPowerOn(); //小腿和臀部
                    
                    BITS_ValveData[0].nByte = 0;
                    BITS_ValveData[1].nByte = 0;
                    BITS_ValveData[2].nByte = 0;
                    if(enAirbagStep > 16)BITS_ValveData[2].nByte = (1 << (enAirbagStep - 17)) & 0xff;
                    else if(enAirbagStep > 8)BITS_ValveData[1].nByte = (1 << (enAirbagStep - 9)) & 0xff;
                    else BITS_ValveData[0].nByte = (1 << (enAirbagStep - 1)) & 0xff;
                    //10秒后自动下一步
                    if(air_bagTimeCount == 0)
                    {
                        air_bagTimeCount++;//防止循环内重复调用
                        enAirbagStep++;
                    }
                    //测试结束
                    if(enAirbagStep > 24)
                    {
                        enAirbagStep = 0;//清零
                        
                        if(walk_up && walk_down && shoulder_detect && knead_width_min && knead_width_mid
                           && knead_width_max && ((!has_leg) || (leg_up && leg_down)) && back_up && back_down 
                               && slide_backward && slide_forward && flex_up && flex_down && foot_Switch 
                                   && leg_angle && _3D_Switch_Forward && _3D_Switch_Back && _3D_Switch_Pluse)
                        {
                            test_finish = 1;
                            air_bag = 0;
                        }
                    }
                }
                else
                {
                    //Vavle_Pump_Switch(0, 0);
                    //Vavle_Pump_Switch(1, 0);
                    Valve_BodyUpAirPumpACPowerOff();  //臂肩，背腰
                    Valve_LegFootAirPumpACPowerOff(); //小腿和臀部
                    BITS_ValveData[0].nByte = 0;
                    BITS_ValveData[1].nByte = 0;
                    BITS_ValveData[2].nByte = 0;
                }
                Valve_Send_Data();
                //手动配合步骤
                //1：加热，2：敲击，3：滚轮，4：气囊,加热时不自动增加
                if(oneKeyStep > 0 && oneKeyStep < oneKeyStepLength)
                {
                    //10秒后自动下一步
                    if(engineerTimeCount == 0)
                    {
                        engineerTimeCount++;//防止循环内重复调用
                        switch(oneKeyStep)
                        {
                        case 2:
                            knock = 0;
                            break;
                        case 3:
                            roller = 0;
                            break;
                        }
                        oneKeyStep++;
                    }
                }
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI;
                    OutBuffer[1] = 0;
                    OutBuffer[1] |= heat;
                    OutBuffer[1] |= has_heat << 1;
                    OutBuffer[1] |= walk_up << 2;
                    OutBuffer[1] |= walk_down << 3;
                    //                OutBuffer[1] |=  Input_GetVout() << 4;
                    OutBuffer[1] |= shoulder_detect << 4;
                    
                    OutBuffer[1] |= knead_width_min << 5;
                    OutBuffer[1] |= knead_width_mid << 6;
                    OutBuffer[1] |= knead_width_max << 7;
                    OutBuffer[2] = 0;
                    OutBuffer[2] |= has_leg;
                    OutBuffer[2] |= leg_up << 1;
                    OutBuffer[2] |= leg_down << 2;
                    OutBuffer[2] |= back_up << 3;
                    OutBuffer[2] |= back_down << 4;
                    OutBuffer[2] |= (back_position & 0x7) << 5;
                    OutBuffer[3] = ((back_position >> 3) & 0x7f) | ((walk_position & 0x1) << 7);
                    OutBuffer[4] = (walk_position >> 1) & 0xff;
                    OutBuffer[5] = (enAirbagStep & 0x1f) | ((oneKeyStep & 0x7) << 5);
                    OutBuffer[6] = (knock << 7) | (roller << 6) | (test_finish << 5);
                    
                    OutBuffer[7] = 0;
                    OutBuffer[7] |= slide_backward;
                    OutBuffer[7] |= slide_forward << 1;
                    OutBuffer[7] |= flex_up << 2;
                    OutBuffer[7] |= flex_down << 3;
                    OutBuffer[7] |= foot_Switch << 4;
                    OutBuffer[7] |= leg_angle << 5;
                    OutBuffer[7] |= leg_ground << 6;
                    
                    OutBuffer[8] = 0;
                    OutBuffer[8] |= _3D_Switch_Forward;
                    OutBuffer[8] |= _3D_Switch_Back<<1;
                    OutBuffer[8] |= _3D_Switch_Pluse<<2;
                    
                    OutBuffer[9] = EOI;
                    nOutBufferCount = 10;
                    HandUart_Transmit_Packet(OutBuffer, nOutBufferCount);
                    bMasterSendPacket = FALSE;
                }
                Main_Send_Leg();
                walk_up_old = (Input_GetWalkUpSwitch() == REACH_WALK_LIMIT);
                walk_down_old = (Input_GetWalkDownSwitch() == REACH_WALK_LIMIT);
                shoulder_detect_old = (Input_GetVout() == BODY_TOUCHED);
                knead_width_min_old = (Input_GetKneadMin() == 0);
                knead_width_mid_old = (Input_GetKneadMid() == 0);
                knead_width_max_old = (Input_GetKneadMax() == 0);
                back_up_old = (Input_GetBackUpSwitch() == REACH_BACK_LIMIT);
                back_down_old = (Input_GetBackDownSwitch() == REACH_BACK_LIMIT);
                leg_up_old   = (Input_GetLegUpSwitch() == REACH_BACK_LIMIT);
                leg_down_old  = (Input_GetLegDownSwitch() == REACH_BACK_LIMIT);
                nLegAngleOld = (Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON);//20180710
                nLegGroundOld = (Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON);
            }
            break;  
            
        case LINGO_HEAT_TEST:
            {
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = (unsigned char)bHeat;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
            
        case LINGO_MUSIC_TEST:
            {
                if(Timer_Counter(C_TIMER_TEMP,1))
                {
                    //Power_AMP_On();  //0.1秒后开启蓝牙
                }
                if(bMasterSendPacket)  
                {/*
                    if(BlueToothUart_GetRXStatus())未使用
                    {
                    unsigned char *name;
                    BlueToothUart_GetModlueName(name);
                    nOutBufferCount = strlen(name) + 2;
                    OutBuffer[strlen(name)] = EOI;           
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
                  else
                    */
                    {
                        OutBuffer[0] = EOI;
                        OutBuffer[1] = 0;
                        OutBuffer[2] = SOI;
                        nOutBufferCount = 3;
                        HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                        bMasterSendPacket = FALSE ;
                    }
                }
            }
            break;
            
        case LINGO_LED_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                
                if(color == 0) 
                {
//                    LED_RGB_Red_Clear();
//                    LED_RGB_Green_Set();
//                    LED_RGB_Blue_Clear();                  
                    LED_RGB_Set_Red_Data(100);
                    LED_RGB_Set_Green_Data(0);
                    LED_RGB_Set_Blue_Data(0);
                }
                if(color == 2) 
                {
//                    LED_RGB_Red_Clear();
//                    LED_RGB_Green_Clear();
//                    LED_RGB_Blue_Set();                    
                    LED_RGB_Set_Red_Data(0);
                    LED_RGB_Set_Green_Data(0);
                    LED_RGB_Set_Blue_Data(100);
                } 
                if(color == 1) 
                {
//                    LED_RGB_Red_Set();
//                    LED_RGB_Green_Clear();
//                    LED_RGB_Blue_Clear();
                    LED_RGB_Set_Red_Data(0);
                    LED_RGB_Set_Green_Data(100);
                    LED_RGB_Set_Blue_Data(0);
                }
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = color;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_SLIDE_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                if(bUpKey) SlideMotorControl(STATE_RUN_SLIDE_FORWARD);
                if(bDownKey) SlideMotorControl(STATE_RUN_SLIDE_BACKWARD);
                if(!bUpKey && !bDownKey) SlideMotorControl(STATE_SLIDE_IDLE);
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)  OutBuffer[1] |= 0x01;
                    if(Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT) OutBuffer[1] |= 0x02;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_3D_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                Main_Send_Leg();
                // Main_MassageSignalSend();
                if(bUpKey) 
                    AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_3);
                if(bDownKey) 
                    AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_3);
                if(!bUpKey && !bDownKey) 
                    AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8);
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_Get3DFrontSwitch()) OutBuffer[1] |= 0x02;
                    if(Input_Get3DBackSwitch()) OutBuffer[1] |= 0x01;  
                    
                    OutBuffer[2] = Input_GetAxisMotorPosition();
                    //     ADC_Get_Voltage(ADC_Vaxis,&adcAxisCurrent);
                    OutBuffer[3] = adcAxisCurrent >> 8 ;
                    OutBuffer[4] = (unsigned char)adcAxisCurrent ;
                    OutBuffer[5] = EOI ;
                    nOutBufferCount = 6;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_BACK_TEST:
            {
                unsigned int w_backpulse= Input_GetBackPosition();
                Valve_Send_Data();
                Input_Proce();
                Main_Send_Leg();
                if(bUpKey) 
                    BackMotor_Control(STATE_RUN_BACK_UP);
                if(bDownKey) 
                    BackMotor_Control(STATE_RUN_BACK_DOWN);
                if(!bUpKey && !bDownKey) 
                    BackMotor_Control(STATE_BACK_IDLE);
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT) OutBuffer[1] |= 0x01;
                    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT) OutBuffer[1] |= 0x02;
                    OutBuffer[2] = (unsigned char)w_backpulse; //low
                    OutBuffer[3] = (unsigned char)(w_backpulse >>8);  //high
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_LEG_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                Main_Send_Leg();
                if(bUpKey) LegMotor_Control(STATE_RUN_LEG_UP);
                if(bDownKey) LegMotor_Control(STATE_RUN_LEG_DOWN);
                if(!bUpKey && !bDownKey) LegMotor_Control(STATE_LEG_IDLE);
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetLegUpSwitch() == REACH_BACK_LIMIT)
                    {
                        OutBuffer[1] |= 0x01;
                    }
                    if(Input_GetLegDownSwitch() == REACH_BACK_LIMIT)
                    {
                        OutBuffer[1] |= 0x02;
                    }
                    if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON) OutBuffer[1] |= 0x04; //小于15度
                    if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON) OutBuffer[1] |= 0x08; //碰到地面了
                    if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) OutBuffer[1] |= 0x10; //碰到脚了
                    //OutBuffer[2] = (nLegAngle >> 7) & 0x7f ;
                    //OutBuffer[3] = nLegAngle & 0x7f ;
                    OutBuffer[2] = (unsigned char)nLegAngle; //low
                    OutBuffer[3] = (unsigned char)(nLegAngle >>8);  //high
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_FLEX_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                Main_Send_Leg();
                if(bUpKey) 
                {
                    //Flex_SetDisableAngle(1);//测试小腿伸缩，屏蔽角度开关保护cyw
                    //Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
                    //Flex_SetDirection(FLEX_TO_OUT);
                    FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlOut(FLEX_MOTOR_CURRENT_5A);
                }
                if(bDownKey) 
                {
                    //Flex_SetDisableAngle(1);//cyw
                    //Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
                    //Flex_SetDirection(FLEX_TO_IN);
                    FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlIn(FLEX_MOTOR_CURRENT_5A);
                }
                if(!bUpKey && !bDownKey) 
                {
                    //Flex_SetDisableAngle(0);//cyw
                    //Flex_SetDirection(FLEX_MOTOR_STOP);
                    FlexMotor_Control(STATE_FLEX_IDLE, FLEX_SPEED_FAST, FLEX_CURRENT_3A);//Flex_ControlStop();
                }
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetFlexOutSwitch() ==  FLEX_AT_OUT) OutBuffer[1] |= 0x01;
                    if(Input_GetFlexInSwitch() ==  FLEX_AT_IN) OutBuffer[1] |= 0x02;
                     if(Input_GetFlexAngleSwitch() == LEGANGLE_SWITCH_ON) OutBuffer[1] |= 0x04; //小于15度
                  if(Input_GetFlexGroundSwitch() == LEGGROUND_SWITCH_ON) OutBuffer[1] |= 0x08; //碰到地面了
                  if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) OutBuffer[1] |= 0x10; //碰到脚了
                    //if(Input_GetFlexFootSwitch() == FOOT_SWITCH_ON) OutBuffer[1] |= 0x04;
                    OutBuffer[2] = (unsigned char)nLegAngle; //low
                    OutBuffer[3] = (unsigned char)(nLegAngle >>8);  //high
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_WALK_TEST:
            {//KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,KNEAD_SPEED3_PWM);
                
                //               KnockMotor_Set_Pwm_Data(KNOCK_SPEED2_PWM);//KNOCK_SPEED2_PWM
                // AxisMotor_Control(STATE_AXIS_IDLE,3,_3D_SPEED_5);
                AxisMotor_Control(STATE_RUN_AXIS_FORWARD,3,_3D_SPEED_5);
                Valve_Send_Data();
                Input_Proce();
                //Main_MassageSignalSend();
                if(bUpKey) WalkMotor_Control(STATE_RUN_WALK_UP,0);
                if(bDownKey) WalkMotor_Control(STATE_RUN_WALK_DOWN,0);
                if(!bUpKey && !bDownKey)
                {
                    WalkMotor_Control(STATE_WALK_IDLE,0);
                    //    KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED3_PWM);
                    KnockMotor_Set_Pwm_Data(0);
                    
                }
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT) OutBuffer[1] |= 0x01;
                    if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT) OutBuffer[1] |= 0x02;
                    if(Input_GetVout() == BODY_TOUCHED)
                    OutBuffer[1] |= 0x04;
                    OutBuffer[2] = Input_GetWalkMotorPosition() >> 8;
                    OutBuffer[3] = Input_GetWalkMotorPosition() ;
                    // ADC_Get_Voltage(ADC_Vwalk,&adcWalkCurrent);
                    // OutBuffer[4] = adcWalkCurrent >> 8;
                    // OutBuffer[5] = adcWalkCurrent;
                    OutBuffer[6] = EOI ;
                    nOutBufferCount = 7;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_LEG_KNEAD_TEST:
            {
                //                Main_Send_Leg();
                //                if(legKneadSpeed == 0)
                //                {
                //                    //LegKnead_SetPower(LEG_KNEAD_OFF);
                //                    //LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
                //                }
                //                else
                //                {
                //                   //LegKnead_SetPower(LEG_KNEAD_ON);
                //                    switch(legKneadSpeed)
                //                    {
                //                    default:  
                //                    case 1:LegKnead_SetSpeed(LEG_KNEAD_SPEED_SLOW);  break ;
                //                    case 2:LegKnead_SetSpeed(LEG_KNEAD_SPEED_MID);  break ;
                //                    case 3:LegKnead_SetSpeed(LEG_KNEAD_SPEED_FAST);  break ;
                //                    }
                //                    if(legKneadPhase == 0)
                //                        LegKnead_SetMode(LEG_KNEAD_TO_IN);
                //                    else
                //                        LegKnead_SetMode(LEG_KNEAD_TO_OUT);
                //                }
                //                if(bMasterSendPacket)
                //                {
                //                    OutBuffer[0] = SOI ;
                //                    OutBuffer[1] = legKneadSpeed;
                //                    OutBuffer[2] = legKneadPhase;
                //                    if(nFlexStatus&0x10) 
                //                    {
                //                      OutBuffer[3] = 1;
                //                    }
                //                    else 
                //                    {
                //                      OutBuffer[3] = 0;
                //                    }
                //                    OutBuffer[4] = EOI ;
                //                    nOutBufferCount = 5;
                //                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                //                    bMasterSendPacket = FALSE ;
                //                }
            }
            break;
        case LINGO_ROLLER_TEST:
            {
                switch(rollerSpeed)
                {
                default:  
                case 0:ROLLER_PWM = ROLLER_SPEED_STOP;  break;
                case 1:ROLLER_PWM = ROLLER_SPEED_SLOW;  break;
                case 2:ROLLER_PWM = ROLLER_SPEED_MID;   break;
                case 3:ROLLER_PWM = ROLLER_SPEED_FAST;  break;
                }
                if(rollerPhase == 0)
                    RollerMotor_Control(ROLLER_PWM,0);
                else
                    RollerMotor_Control(ROLLER_PWM,1);
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = rollerSpeed;
                    OutBuffer[2] = rollerPhase;
                    OutBuffer[3] = EOI ;
                    nOutBufferCount = 4;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_KNOCK_TEST:  
            {
                Valve_Send_Data();
                Input_Proce();
                
                
                
                
                
                if(kneadSpeed == 0)
                {
                    KnockMotor_Break();
                }
                else
                {
                    switch(kneadSpeed)
                    {
                    default:  
                    case 0:PWM = KNOCK_SPEED0_PWM;  break ;
                    case 1:PWM = KNOCK_SPEED1_PWM;  break ;
                    case 2:PWM = KNOCK_SPEED2_PWM;  break ;
                    case 3:PWM = KNOCK_SPEED3_PWM;  break ;
                    case 4:PWM = KNOCK_SPEED4_PWM;  break ;
                    case 5:PWM = KNOCK_SPEED5_PWM;  break ;
                    case 6:PWM = KNOCK_SPEED6_PWM;  break ;
                    }
                    if(kneadPhase == 0)
                        KnockMotor_ClockRun();
                    else
                        KnockMotor_UnClockRun();
                    
                    KnockMotor_Set_Pwm_Data(PWM);//KNOCK_SPEED2_PWM
                }
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = kneadSpeed;
                    OutBuffer[2] = kneadPhase;
                    OutBuffer[3] = Input_GetKneadPosition();
                    //ADC_Get_Voltage(ADC_Vknock,&adcKnockCurrent);
                    //OutBuffer[4] = adcKnockCurrent >> 8;
                    //OutBuffer[5] = adcKnockCurrent;
                    OutBuffer[6] = EOI ;
                    nOutBufferCount = 7;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_KNEAD_TEST:
            {
                Valve_Send_Data();
                //Main_MassageSignalSend();
                Input_Proce();
                if(kneadSpeed == 0)
                {
                    KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
                }
                else
                {
                    switch(kneadSpeed)
                    {
                    default:  
                    case 0:PWM = KNEAD_SPEED0_PWM;  break ;
                    case 1:PWM = KNEAD_SPEED1_PWM;  break ;
                    case 2:PWM = KNEAD_SPEED2_PWM;  break ;
                    case 3:PWM = KNEAD_SPEED3_PWM;  break ;
                    case 4:PWM = KNEAD_SPEED4_PWM;  break ;
                    case 5:PWM = KNEAD_SPEED5_PWM;  break ;
                    case 6:PWM = KNEAD_SPEED6_PWM;  break ;
                    }
                    if(kneadPhase == 0)
                        KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,PWM);
                    else
                        KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN,PWM);
                }
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = kneadSpeed;
                    OutBuffer[2] = kneadPhase;
                    //                    if(Input_GetKneadPosition()!=0)
                    //                      OutBuffer[3] = Input_GetKneadPosition();
                    OutBuffer[3] = Input_Get_Mim_Max();
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;  
        case LINGO_INPUT:
            if(bMasterSendPacket)
            {
                if(Timer_Counter(C_TIMER_TEMP+T_LOOP,10))
                {
                    //     ADC_Get_Voltage(ADC_VCC,&adcVcc); 
                    ADC_Get_Voltage(ADC_V24,&adc24); 
                    //    ADC_Get_Voltage(ADC_V24_1,&adc24_1); 
                    tempture = ADC_Get_Inttemp();
                }
                OutBuffer[0] = SOI ;
                //5V电压
                OutBuffer[1] = (unsigned char)(adcVcc/100);
                OutBuffer[2] = (unsigned char)(adcVcc%100);
                //24V马达电压
                OutBuffer[3] = (unsigned char)(adc24/100);
                OutBuffer[4] = (unsigned char)(adc24%100);
                //24V气阀电压
                OutBuffer[5] = (unsigned char)(adc24_1/100);
                OutBuffer[6] = (unsigned char)(adc24_1%100);
                //CPU温度
                OutBuffer[7] = (unsigned char)(tempture/100);
                OutBuffer[8] = (unsigned char)(tempture%100);
                
                //                unsigned int pm25;
                //                if(VoiceUart_GetPM25(&pm25) == -1)
                //                {
                //                  pm25 = 0x7f7f;
                //                }
                //                
                //                OutBuffer[9] = (unsigned char)(pm25);
                //                OutBuffer[10] = (unsigned char)(pm25>>8);
                
                OutBuffer[11] = EOI ;
                nOutBufferCount = 12;
                HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                bMasterSendPacket = FALSE ;
            }
            break;
        case LINGO_AIRBAG:
            Main_Send_Leg();
            if(bMasterSendPacket)
            {
                OutBuffer[0] = SOI ;
                OutBuffer[1] = airpumpIndex;
                OutBuffer[2] = airbagIndex;
                OutBuffer[3] = EOI ;
                nOutBufferCount = 4;
                HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                bMasterSendPacket = FALSE ;
            }
            if(airbagIndex & 0x80)
            {
                airbag = 0xffffff;
                Valve_Test_Set_Data(airbag);
            }
            else
            {
                airbag = 1 << airbagIndex;
                Valve_Test_Set_Data(airbag);
            }
            if(airpumpIndex&0x01)
            {
                Valve_BodyUpAirPumpACPowerOn();  
            }
            else
            {
                Valve_BodyUpAirPumpACPowerOff(); 
            }
            if(airpumpIndex&0x02)
            {
                Valve_LegFootAirPumpACPowerOn(); 
            }
            else
            {
                Valve_LegFootAirPumpACPowerOff(); //打开供应全身气囊
            }
            Valve_Send_Data();
            break;
        case LINGO_ENG:  
        case LINGO_MENU:   
            Main_Send_Leg();
            //LegKnead_SetPower(LEG_KNEAD_OFF);
            //LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
            KnockMotor_Set_Pwm_Data(KNOCK_SPEED0_PWM);
            RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
            KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
            Valve_BodyUpAirPumpACPowerOff();  //臂肩，背腰
            Valve_LegFootAirPumpACPowerOff(); //小腿和臀部
            Valve_Test_Set_Data(0);
            {
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    
                    unsigned int snH = DEVINFO->UNIQUEH;
                    unsigned int snL = DEVINFO->UNIQUEL;
                    
                    OutBuffer[1] = (unsigned char)(snH >> 24);
                    OutBuffer[2] = (unsigned char)(snH >> 16);
                    OutBuffer[3] = (unsigned char)(snH >> 8);
                    OutBuffer[4] = (unsigned char)(snH);
                    
                    OutBuffer[5] = (unsigned char)(snL >> 24);
                    OutBuffer[6] = (unsigned char)(snL >> 16);
                    OutBuffer[7] = (unsigned char)(snL >> 8);
                    OutBuffer[8] = (unsigned char)(snL);
                    
                    OutBuffer[9] = (unsigned char)ReadEEByte(USER_DATA_BASE+SOFT_MAIN_VER_ADDRESS);
                    OutBuffer[10] = (unsigned char)ReadEEByte(USER_DATA_BASE+SOFT_SECONDARY_VER_ADDRESS);
                    //OutBuffer[11] = (unsigned char)ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS);
                    OutBuffer[11] = 0; wgh =0;
                    wgh = (unsigned char)ReadEEByte(USER_DATA_BASE+REST_SLEEP_MODE_ADDRESS);
                    OutBuffer[11] = ((unsigned char)ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS)|(wgh<<2));
                    OutBuffer[12] = (unsigned char)ReadEEByte(USER_DATA_BASE+AIRBAG_STRETCH_ADDRESS);
                    OutBuffer[13] = (unsigned char)ReadEEByte(USER_DATA_BASE+SLIDE_MOTOR_ENABLE_ADDRESS);//(unsigned char)ReadEEByte(USER_DATA_BASE+ARM_MOTOR_SWITCH_ADDRESS);
                    
                    
                    // OutBuffer[14] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_0_ADDRESS);
                    // OutBuffer[15] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_1_ADDRESS);
                    // OutBuffer[16] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_2_ADDRESS);
                    // OutBuffer[17] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_3_ADDRESS);
                    
                    OutBuffer[14] = EOI ;
                    nOutBufferCount = 15;
                    HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_PROGRAM:  
            {
                Valve_BodyUpAirPumpACPowerOff();  //臂肩，背腰
                Valve_LegFootAirPumpACPowerOff(); //小腿和臀部
                Valve_Test_Set_Data(0);
                if(bMasterSendPacket)
                {
                    if(bProgram)
                    {
                        OutBuffer[0] = SOI ;
                        OutBuffer[1] = 'p';
                        OutBuffer[2] = 'r';
                        OutBuffer[3] = 'o' ;
                        OutBuffer[4] = 'g' ;
                        OutBuffer[5] = 'r' ;
                        OutBuffer[6] = 'a' ;
                        OutBuffer[7] = 'm' ;
                        OutBuffer[8] = EOI ;
                        nOutBufferCount = 9;
                        HandUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                        overCounter++;
                        if(overCounter >= 3)
                        {
                            password = 0;  
                            NVIC_SystemReset(); //复位CPU
                        }
                    }
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        default:
            Valve_BodyUpAirPumpACPowerOff();  //臂肩，背腰
            Valve_LegFootAirPumpACPowerOff(); //小腿和臀部
            Valve_Test_Set_Data(0);
            break;
        }
        /******************************/
        if(HandUart_GetCtrlType() != ENGGER_CTRL)
        {
            password = 0;  
            NVIC_SystemReset(); //复位CPU
        }
    }
    Main_Initial_Data(); //重新初始化数据
}

void main_200ms_int(void)
{
  bBlueToothMasterSendPacket = TRUE;
  bArmProtect = TRUE;
}

void main_50ms_int(void)
{
    
     bMasterSendPacket = TRUE;
}

void main_25ms_int(void)
{
    bMasterSendLegPacket = TRUE;
}

void main_100ms_int(void)
{
 
}
void main_5ms_int(void)
{
  
    bTimer5MS = TRUE ;
  
}

void main_10ms_int(void)
{
    bTimer10MS = TRUE ;
    engineeringTime_10msFlag = 1;
    
   
}

void main_30ms_int(void)
{
  
}

void Main_Save_Acctime(void)
{
    unsigned int time;
    time = Data_Get_ProgramExecTime();
    if(time == 0) return;
    Data_Clear_ProgramExecTime();
}
BYTE Main_GetKeyNoClear(void)
{
    BYTE by_Key = H10_KEY_NONE;
    if(HandUart_GetRXStatus() == TRUE)
    {
        //HandUart_ClearRXStatus();
        by_Key = HandUart_GetKey();
        //HandUart_SetKey(H10_KEY_NONE);
    }  
    //if The command is from Bluetooth ,then awake from sleep mode for there's keys arrive.
    if(BlueToothUart_GetRXStatus() == TRUE)//未使用
    {
        by_Key = BlueToothUart_GetKey();//未使用
    }
    return by_Key;
}

unsigned int Voice_UpTime,Voice_DownTime;
bool bVoice_WakeupFlag;
void Voice_1msInt(void)
{
    if(bVoice_WakeupFlag)
    {
        Voice_UpTime++;   
    }
    else
    {
        Voice_DownTime++;
    }
}
bool Main_GetVoiceStatus(void)
{
    if(GPIO_PinInGet(VOICE_WAKEUP_PORT,VOICE_WAKEUP_BIT))
    {
        bVoice_WakeupFlag = true;
        if(Voice_UpTime >= 50)
        {
            return 1;
        }
    }
    else
    {
        bVoice_WakeupFlag = false;
        if(Voice_DownTime >= 50)
        {
            return 0;
        }
    }
}
void Main_Sleep(void)
{
    bool bPowerOn = false;
    int powerCounter = 0;
    int ledCounter;
    BYTE key;
    nChairRunState = CHAIR_STATE_SLEEP; 
    nVoicekey = H10_KEY_NONE;
    Power_All_Off();
    //Power_5V_On();
    unsigned int pw_Information[10];
    bool bInformationUpdate = 0;
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);//将user_data中的数据放入到pw_Information数组中
    if(w_PresetTime != (ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60))
    {
        if(w_PresetTime == RUN_TIME_5)
        {
            
        }
        else
        {
            *(pInformation + DEFAULT_TIME_ADDRESS) = w_PresetTime/60; 
            bInformationUpdate = 1;
        }
    }
    if(bBlueToothStatus != ReadEEByte(USER_DATA_BASE + BLUETOOTH_STATUS_ADDRESS))
    {
        *(pInformation + BLUETOOTH_STATUS_ADDRESS) = bBlueToothStatus; 
        bInformationUpdate = 1;
    }
    if( bInformationUpdate)
    {
        MEM_Write_Memory(pw_Information,8*2);
    }
    //currentBackPadMotorState_reset();
    Main_Initial_Data();  //software initial
    //BlueToothUart_AMP_Volume_On();
    
    // BackPower_Off();
    //LegPower_Off();
    // WalkPower_Off();
    nChairRunState_Pre=nChairRunState;
    SingleLine_Play(4,1);  //暂停
    while(nChairRunState == CHAIR_STATE_SLEEP)
    {
        if(Main_GetVoiceStatus())
        {
            Power_5V_On();
        }
        else
        {
            Power_5V_Off();
        }

        if(HandUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
        /**********************云养程序区*********************/
        if(BlueToothUart_GetCtrlType()==PROGARM_CTRL)//sleep
        {
            if(*(pInformation + PROGRAM_ENABLE_ADDRESS) != PROGRAM_FLAG)
            {
                *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_FLAG; //写编程标志位
                MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            }
            NVIC_SystemReset();     
            return;     
        }    
        /*****************************************************/
        key = Main_GetKey();
        if(key != H10_KEY_NONE)
        {
            if( key == H10_KEY_POWER_SWITCH ||
               key == H10_KEY_BACKPAD_UP_START ||
                   key == H10_KEY_BACKPAD_DOWN_START ||
                       key == H10_KEY_LEGPAD_UP_START ||
                           key == H10_KEY_LEGPAD_DOWN_START ||
                               key == H10_KEY_LEGPAD_EXTEND_START ||
                                   key == H10_KEY_LEGPAD_CONTRACT_START)
            {
                bPowerOn = true;
                //Power_All_On();
                Power_3V3_On();
                Power_5V_On();
                //SingleLine_Query();
                handrail_flag = true;//用于控制开机扶手拥抱
                arm_step=0;          //用于控制开机扶手拥抱
            }
        }  
        if(key&VOICE_KEY_MASK)
        {
            if((key&VOICE_KEY_MASK) != H10_KEY_POWER_SWITCH)
            {
                bPowerOn = true;
                nVoicekey = key&0x7f;
                Power_All_On();
            }
        }
        if(bTimer10MS == TRUE)
        {
            ledCounter++;
            ledCounter %= 200;
            bTimer10MS = FALSE ;
            if(bPowerOn)
            {
                powerCounter++;   
                if(powerCounter > 4)
                {
                    nChairRunState = CHAIR_STATE_WAIT_COMMAND; 
                }
            }
            else
            {
                powerCounter = 0;   
            }
        }
        if(ledCounter < 10)
        {
            IndicateLED_On();
        }
        else
        {
            IndicateLED_Off();
        }
        
        if(bPowerOn)
        {
            Input_Proce();
            Valve_Send_Data();
        }
        Main_Send();
        Main_BlueToothSend();//sleep
    }
}
//bool RockBackLegProcess(void)
//{
//  unsigned int w_LegPosition;
//  bool bLegpositiondone;
//
//  w_LegPosition = LegMotor_Get_Position();
//
//  if(w_LegPosition <= MASSAGE_LEG_ROCK_POSITION)
//  {
//    bLegPadLinkage = FALSE;
//    bKeyLegPadUp = TRUE;
//    bKeyLegPadDown = FALSE;
//    bLegpositiondone = false;
//  }
//  else if(w_LegPosition >= MASSAGE_LEG_ROCK_POSITION + MASSAGE_DIFFERENT_POSITION)
//  {
//    bLegPadLinkage = FALSE;
//    bKeyLegPadUp = FALSE;
//    bKeyLegPadDown = TRUE;
//    bLegpositiondone = false;
//  }
//  else
//  {
//    bKeyLegPadUp = FALSE;
//    bKeyLegPadDown = FALSE;
//    bLegpositiondone = true;
//  }
//  //if((bLegpositiondone == true)&&(bBackpositiondone == true)) return true;  //到达了预定的位置
//  if(bLegpositiondone == true) return true;  //到达了预定的位置
//  else return false;  //未到达预定的位置
//}
//void RockFunctionEnable(bool Enable)
//{
//    bKeyBackPadUp = FALSE;
//    bKeyBackPadDown = FALSE;
//    bKeyLegPadUp = FALSE;
//    bKeyLegPadDown = FALSE;
//    switch(Enable)
//    {
//    case RockDisable:
//        bRockEnable = false;
//        break;
//    case RockEnable:
//        setBackPadRockingEnable(Enable);//摇摆模式靠背电机缓慢运动
//        nRockModeEnterEnable = EnterRock;
//        bRockEnable = true;
//        WorkStep = 0;//一旦刚进入该模式就开始尝试下躺
//        break;
//    default :
//        bRockEnable = false;
//        break;
//    }
//}

//void RockProcess(void)
//{
////#ifdef ROCK_TEST   //该语句不执行
////  
////  //没有在摇摆模式时就直接退出
////  if(nRockModeEnterEnable == ExitRock) return;
////  
////  unsigned int CurrentBackMotorPosition;//,w_BackPosition;
////  bool bBackupdone,bBackdowndone;
////  if(bRockEnable)
////  {
////    switch(WorkStep)
////    {
////    case StartRock:
////      //SlideMotorControl(STATE_RUN_SLIDE_FORWARD);
////      //w_BackPosition = BackMotor_Get_Position();
////      //if((Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)&&(bLegdowndone == true)&&(bBackdowndone == true))
////      //if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)
////      {
////        //131224
////        bKeyBackPadUp = FALSE;
////        bKeyBackPadDown = TRUE;
////        //bKeyLegPadUp = TRUE;
////        //bKeyLegPadDown = FALSE;
////        
////        //if(RockBackLegProcess() == true)
////        if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
////        //if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)
////        {
////          //BackMotor_Control(STATE_RUN_BACK_DOWN);
////          //if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
////          {
////            WorkStep++;
////          }
////        }
////      }
////      break;
////    case LieDown:
////      CurrentBackMotorPosition = Input_GetBackPosition();
////      if(CurrentBackMotorPosition < MASSAGE_BACK_DOWN_ROCK_POSITION)
////        //if(Input_GetSlideForwardSwitch() != REACH_SLIDE_LIMIT)
////      {
////        //SlideMotorControl(STATE_RUN_SLIDE_FORWARD);
////        //BackMotor_Control(STATE_RUN_BACK_DOWN);
////        bKeyBackPadUp = FALSE;
////        bKeyBackPadDown = TRUE;
////        bBackdowndone = false;
////      }
////      else
////      {
////        //SlideMotorControl(STATE_SLIDE_IDLE);
////        //BackMotor_Control(STATE_BACK_IDLE);
////        bKeyBackPadUp = FALSE;
////        bKeyBackPadDown = FALSE;
////        bBackdowndone = true;
////      }
////      if(/*(RockBackLegProcess() == true)&&*/(bBackdowndone == true))
////      {
////        WorkStep++;
////      }
////      break;
////    case LieUP:
////      CurrentBackMotorPosition = Input_GetBackPosition();
////      if(CurrentBackMotorPosition > MASSAGE_BACK_UP_ROCK_POSITION)
////        //if(Input_GetSlideBackwardSwitch() != REACH_SLIDE_LIMIT)
////      {
////        //SlideMotorControl(STATE_RUN_SLIDE_BACKWARD);
////        //BackMotor_Control(STATE_RUN_BACK_UP);
////        bKeyBackPadUp = TRUE;
////        bKeyBackPadDown = FALSE;
////        bBackupdone = false;
////      }
////      else
////      {
////        //SlideMotorControl(STATE_SLIDE_IDLE);
////        //BackMotor_Control(STATE_BACK_IDLE);
////        bKeyBackPadUp = FALSE;
////        bKeyBackPadDown = FALSE;
////        bBackupdone = true;
////      }
////      if(/*(RockBackLegProcess() == true)&&*/(bBackupdone == true))
////      {
////        WorkStep = LieDown;
////      }
////      break;
////    default :
////      break;
////    }
////  }
////  else
////  {
////    BackMotor_Control(STATE_BACK_IDLE);
////    nRockModeEnterEnable = ExitRock;
////  }
////  
////#else
//
//   static bool bNextRock=0;
//   static uint16_t Rock_Time;
//
//   static uint8_t  Rock_Start;
//  if(nBackMainRunMode == BACK_MAIN_MODE_AUTO && (nBackSubRunMode == BACK_SUB_MODE_AUTO_1))
//  {
//    //unsigned int CurTime = Data_Get_TimeSecond();
//    if(Rock_Time!=Data_Get_TimeSecond()) 
//    {
//      Rock_Time=Data_Get_TimeSecond();
//      if(Data_Get_TimeSecond()>10*60)CurTime++;
//      else CurTime=4*60;
//    }
//    
//    if(CurTime>5*60)CurTime = 0;
//    if((CurTime==0)&&(Rock_Start==0))    //开始摇摆
//    {
//      bNextRock=1;
//      Rock_Start = 1;
//      //RockFunctionEnable(true);
//    }
////    if((CurTime == 16 * 60) ||
////       (CurTime == 7 * 60)||(CurTime == 25 * 60)||(CurTime == 01 * 60))       //摇摆一段时间，禁止摇摆，
//   if((CurTime >= 4*60)&(Rock_Start==1)) //停止摇摆
//    {
//      Rock_Start = 0;
//      RockFunctionEnable(false);
//      nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION;      //回到类似第一零重力状态
//      bMassagePositionUpdate = TRUE;    
//    }
//   if(bNextRock)
//    {
//      RockFunctionEnable(true);
//      if(RockBackLegProcess())
//      {
//        RockFunctionEnable(true);
//        nTargetMassagePosition = MASSAGE_UNKNOW_POSITION;//fww
//        bNextRock=0;
//      }
//          
//    }
//    
//    
//  }


  
  
  
  //没有在摇摆模式时就直接退出
//  if(nRockModeEnterEnable == ExitRock) return;
  

//  unsigned int CurrentBackMotorPosition=0 ;
//  bool bBackupdone,bBackdowndone;
//  if(!bRockEnable)   return;
//  //{
//    bSendBuzzerMode = FALSE ;
//    switch(WorkStep)
//    {
//    case StartRock:     //0
//        bKeyBackPadUp = FALSE;
//        bKeyBackPadDown = TRUE;
//        RockBackLegProcess();//小腿到摇摆预定的位置。
//        if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
//        {
//          WorkStep++;
//        }
//      break;
//    case LieDown://1
//      CurrentBackMotorPosition = Input_GetBackPosition();
//      
//      if(CurrentBackMotorPosition < MASSAGE_BACK_DOWN_ROCK_POSITION)  //1、靠背向下、小腿向上走 
//      {
//        bKeyBackPadUp = FALSE;
//        bKeyBackPadDown = TRUE;
//        bBackdowndone = false;
//      }
//      else
//      {
//        bKeyBackPadUp = FALSE;
//        bKeyBackPadDown = FALSE;
//        bBackdowndone = true;
//      }
//      if((RockBackLegProcess() == true)&&(bBackdowndone == true))//靠背，小腿到达预定的 位置
//      {
//        WorkStep++;
//      }
//      break;
//
//    case LieUP://2       //电机向上，坐标减小   //2、靠背向上，小腿向下
//      CurrentBackMotorPosition = Input_GetBackPosition();
//      if(CurrentBackMotorPosition > MASSAGE_BACK_UP_ROCK_POSITION)
//      {
//        bKeyBackPadUp = TRUE;
//        bKeyBackPadDown = FALSE;
//        bBackupdone = false;
//      }
//      else
//      {
//        bKeyBackPadUp = FALSE;
//        bKeyBackPadDown = FALSE;
//        bBackupdone = true;
//      }
//      if((RockBackLegProcess() == true)&&(bBackupdone == true))
//      {
//        WorkStep = LieDown;
//      }
//      break;
//    default :
//      break;
//    }
////  }
////  else
////  {
////    BackMotor_Control(STATE_BACK_IDLE);
////    nRockModeEnterEnable = ExitRock;
////  }
////#endif
//}

#define CURRENT_POINT_COUNT 10
//肩位检测时行走电机向下走到最低点，3D电机力度调到最大，然后开始肩位检测，不同的人坐标不一样
void Auto_Calibration(int detect3D )
{
    static int steps = 0;
    static unsigned int positionCount,positionTicks;
    bool _b3D_OK,bKnead_OK,bWalk_OK;
    if(BodyDetectStep == DETECT_INITIAL)
    {
        BodyDetectStep = DETECT_SHOULDER;
        nShoulderPosition = DEFAULT_SHOULDER_POSITION;
        ShoulderSteps = BODY_DETECT_PREPARE;
        steps = 0;
        bShoulderOK = 0;
    }
    if(DETECT_SHOULDER == BodyDetectStep)
    {
        switch(ShoulderSteps)  
        {
        case BODY_DETECT_PREPARE:   //准备 停止敲击马达 3D马达揉捏头停在最前面，宽位置 
            {
                KnockMotor_Break();
                _b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,2,_3D_SPEED_5);
                //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_5);//STATE_RUN_AXIS_FORWARD
                //STATE_RUN_AXIS_BEHIND
                //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,3,_3D_SPEED_10);
                //bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MED,KNEAD_SPEED2_PWM);
                bKnead_OK = KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
                bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_UP,0);
                if(_b3D_OK && bKnead_OK && bWalk_OK)
                {
                    ShoulderSteps = BODY_DETECT_WALK_POSITION;
                }
            }
            break;  
        case BODY_DETECT_WALK_POSITION:                    //行走电机下行
            bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
            
            if((bWalk_OK))
            {
                //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
                //bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
                ShoulderSteps = BODY_DETECT_KNEAD_MIN;
            }
            //if(_b3D_OK && bWalk_OK && bKnead_OK)
            //{
            //  nShoulderPosition = DEFAULT_SHOULDER_POSITION;
            //  ShoulderSteps = BODY_DETECT_UP_AUTO;
            //}
            //waitingcount =0;
            break;
        case BODY_DETECT_KNEAD_MIN:
            bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MIN,KNEAD_SPEED2_PWM);
            if(bKnead_OK)
            {
                ShoulderSteps = BODY_DETECT_KNEAD_MAX;
            }
            break;
        case BODY_DETECT_KNEAD_MAX:
            bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
            if(bKnead_OK)
            {
                ShoulderSteps = BODY_DETECT_3D_FORWARD;
            }
            
            break;  
        case BODY_DETECT_3D_FORWARD:
            bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
            if((bWalk_OK))
            {
                _b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
                if(_b3D_OK )
                {
                    nShoulderPosition = DEFAULT_SHOULDER_POSITION;
                    ShoulderSteps = BODY_DETECT_UP_AUTO;
                }
            }
            break;
            /*case BODY_DETECT_WALK_POSITION:                    //行走电机下行
            bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
            
            if((bWalk_OK))
            {
            _b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
            bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
        }
            if(_b3D_OK && bWalk_OK && bKnead_OK)
            {
            nShoulderPosition = DEFAULT_SHOULDER_POSITION;
            ShoulderSteps = BODY_DETECT_UP_AUTO;
        }
            waitingcount =0;
            break;*/
        case BODY_DETECT_UP_AUTO:  //行走马达上行到脖子位置
            
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPosition))
            {
                ShoulderSteps = BODY_DETECT_DATA_REFRESH;
            }
            
            if(Input_GetVout() == BODY_TOUCHED)
            {
                //waitingcount++;
                if((Input_GetVout() == BODY_TOUCHED)&&(Input_GetWalkMotorPosition()>= LIMIT_POSITION))//&&(waitingcount>=1) )
                {
                    WalkMotor_Control(STATE_WALK_IDLE,0);
                    nShoulderPosition = Input_GetWalkMotorPosition()-5;//-40; //位置补偿 肩膀位置修正
                    //nShoulderPosition -= 20;  //位置补偿 肩膀位置修正
                    ShoulderSteps = BODY_DETECT_DATA_REFRESH;  
                    //                 if(nShoulderPosition+LIMIT_PRECISION > TOP_POSITION)
                    //                {
                    //                  nShoulderPosition = TOP_POSITION;
                    //                }
                    //                else
                    //                {
                    //                  nShoulderPosition += LIMIT_PRECISION;
                    //                }
                    //肩膀位置修正完成  
                } 
            }
            //            else
            //            {
            //              //waitingcount =0;
            //            }
            break;  
        case BODY_DETECT_DATA_REFRESH:  //数据刷新
            {
                BodyDataRefresh();
                if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPosition))  
                {
                    ShoulderSteps = BODY_DETECT_ADJ;
                    Timer_Counter_Clear(C_TIMER_5);
                }
            }
            break;
        case BODY_DETECT_ADJ:  //揉脖子并调整脖子位置
            KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,KNEAD_SPEED3_PWM);
            if(bKeyWalkUp)
            {
                if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPositionTop)) //nShoulderPositionBottom
                {
                    nBuzzerMode = BUZZER_MODE_FAST ;
                    bSendBuzzerMode = TRUE ;
                }
                else
                {
                    nBuzzerMode = BUZZER_MODE_SLOW ;
                    bSendBuzzerMode = TRUE ;
                    Timer_Counter_Clear(C_TIMER_5);//add by wgh 20150313
                }
            }
            if(bKeyWalkDown)
            {
                if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPositionBottom)) //nShoulderPositionBottom
                {
                    nBuzzerMode = BUZZER_MODE_FAST ;
                    bSendBuzzerMode = TRUE ;
                }
                else
                {
                    nBuzzerMode = BUZZER_MODE_SLOW ;
                    bSendBuzzerMode = TRUE ;
                    Timer_Counter_Clear(C_TIMER_5);//add by wgh 20150313
                }
            }
            if((!bKeyWalkUp) && (!bKeyWalkDown))
            {
                WalkMotor_Control(STATE_WALK_IDLE, 0);
                nBuzzerMode = BUZZER_MODE_OFF ;
                bSendBuzzerMode = TRUE ;
            }
            if(Timer_Counter(C_TIMER_5,10*10))
            {
                nShoulderPosition = Input_GetWalkMotorPosition();  
                ShoulderSteps = BODY_DETECT_OVER;
                break;
            }
            break;
        case BODY_DETECT_OVER:  
            bShoulderOK = 1;
            BodyDetectStep = DETECT_FINISH;//添加此语句，防止体型检测完成后标志位未设置导致再次进入时还是显示体型检测界面
            if(detect3D)
            {
                BodyDetectStep = DETECT_3D;
            }
            break;
        }
    }
    if(DETECT_3D == BodyDetectStep)
    {
        switch(steps)
        {
        case 0:   //准备
            {
                KnockMotor_Break();
                if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MED,KNEAD_SPEED2_PWM) && (AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_8)))    
                {
                    steps++;
                }
                positionCount = 0;
                positionTicks = nShoulderPosition/_3D_FULL_POINT;   //设置3D电流采集点之间的行走脉冲数量 
            }
            break;
        case 1:  
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,positionCount*positionTicks)) //到达行走位置点
            {
                steps++;
            }
            break;
        case 2:  //3D马达运动到最后面   
            {
                if(AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_8))
                {
                    steps++;
                    AxisMotor_UpdataPosition();
                }
            }
            break;    
        case 3:  //3D马达运动到最前面  
            {
                if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_8))
                {
                    steps++;
                }
                AxisMotor_StorageCurrent(positionCount,positionCount*positionTicks);  //存储电流值11*40个点
            }
            break;
        case 4:  //数据记录与处理
            {
                positionCount++;
                if(positionCount > _3D_FULL_POINT )  //一共采集数据_3D_FULL_POINT+1次
                {
                    steps++;
                    break;
                }
                steps = 1; 
            }
            break;
        case 5:  //结束
            {
                nChairRunState = CHAIR_STATE_RUN;
                BodyDetectStep = DETECT_FINISH;
                // bodyDectect = 1;
                AxisMotor_CurrentAdj();
            }
            break;  
        }//end switch
    } // end if
    /***************程序退出区**************************/
}
//void Auto_Calibration(int detect3D )
//{
//    static int steps = 0;
//    static unsigned int positionCount,positionTicks;
//    bool _b3D_OK,bKnead_OK,bWalk_OK;
//    if(BodyDetectStep == DETECT_INITIAL)
//    {
//      BodyDetectStep = DETECT_SHOULDER;
//      nShoulderPosition = DEFAULT_SHOULDER_POSITION;
//      ShoulderSteps = BODY_DETECT_PREPARE;
//      steps = 0;
//      bShoulderOK = 0;
//    }
//       if(DETECT_SHOULDER == BodyDetectStep)
//       {
//         switch(ShoulderSteps)  
//         {
//         case BODY_DETECT_PREPARE:   //准备 停止敲击马达 3D马达揉捏头停在最前面，宽位置 
//           {
//             KnockMotor_Break();
//             _b3D_OK = 1;//AxisMotor_Control(STATE_RUN_AXIS_POSITION,2,_3D_SPEED_5);
//             //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_5);//STATE_RUN_AXIS_FORWARD
//             //STATE_RUN_AXIS_BEHIND
//                //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,3,_3D_SPEED_10);
//             //bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MED,KNEAD_SPEED2_PWM);
//             bKnead_OK = KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
//             bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_UP,0);
//             if(_b3D_OK && bKnead_OK && bWalk_OK)
//             {
//               ShoulderSteps = BODY_DETECT_WALK_POSITION;
//             }
//           }
//           break;  
//        case BODY_DETECT_WALK_POSITION:                    //行走电机下行
//           bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
//           
//           if((bWalk_OK))
//           {
//             //_b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
//             //bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
//             ShoulderSteps =BODY_DETECT_KNEAD_MIN;
//           }
//           //if(_b3D_OK && bWalk_OK && bKnead_OK)
//           //{
//           //  nShoulderPosition = DEFAULT_SHOULDER_POSITION;
//           //  ShoulderSteps = BODY_DETECT_UP_AUTO;
//           //}
//           //waitingcount =0;
//          break;
//         case BODY_DETECT_KNEAD_MIN:
//           bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MIN,KNEAD_SPEED2_PWM);
//           if(bKnead_OK)
//           {
//             ShoulderSteps = BODY_DETECT_KNEAD_MAX;
//           }
//           break;
//         case BODY_DETECT_KNEAD_MAX:
//           bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
//           
//           if((bKnead_OK)& AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5))
//           {
//             ShoulderSteps = BODY_DETECT_3D_FORWARD;
//           }
//           
//           break;  
//         case BODY_DETECT_3D_FORWARD:
//           bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
//           if((bWalk_OK))
//           {
//            // _b3D_OK =1;// AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
//           //  if(_b3D_OK )
//           //  {
//               nShoulderPosition = DEFAULT_SHOULDER_POSITION;
//               ShoulderSteps = BODY_DETECT_UP_AUTO;
//            // }
//           }
//           break;
//        /*case BODY_DETECT_WALK_POSITION:                    //行走电机下行
//           bWalk_OK = WalkMotor_Control(STATE_RUN_WALK_POSITION,POSITION_T5);//WAIST_POSITION);
//           
//           if((bWalk_OK))
//           {
//             _b3D_OK = AxisMotor_Control(STATE_RUN_AXIS_POSITION,4,_3D_SPEED_5);
//             bKnead_OK = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM);
//           }
//           if(_b3D_OK && bWalk_OK && bKnead_OK)
//           {
//             nShoulderPosition = DEFAULT_SHOULDER_POSITION;
//             ShoulderSteps = BODY_DETECT_UP_AUTO;
//           }
//           waitingcount =0;
//          break;*/
//         case BODY_DETECT_UP_AUTO:  //行走马达上行到脖子位置
//            //    KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM);
//              KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,KNEAD_SPEED3_PWM);
//            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPosition))
//             {
//               ShoulderSteps = BODY_DETECT_DATA_REFRESH;
//
//             }
//            
//            if(Input_GetVout() == BODY_TOUCHED)
//            {
//              //waitingcount++;
//              if((Input_GetVout() == BODY_TOUCHED)&&(Input_GetWalkMotorPosition()>= LIMIT_POSITION))//&&(waitingcount>=1) )
//              {
//                WalkMotor_Control(STATE_WALK_IDLE,0);
//                nShoulderPosition = Input_GetWalkMotorPosition();
//                ShoulderSteps = BODY_DETECT_DATA_REFRESH;
//                nShoulderPosition -= 20;  //位置补偿
//             //肩膀位置修正   
//                 if(nShoulderPosition+LIMIT_PRECISION > TOP_POSITION)
//                {
//                  nShoulderPosition = TOP_POSITION;
//                }
//                else
//                {
//                  nShoulderPosition += LIMIT_PRECISION;
//                }
//               //肩膀位置修正完成  
//              } 
//            }
//            else
//            {
//              //waitingcount =0;
//            }
//           break;  
//         case BODY_DETECT_DATA_REFRESH:  //数据刷新
//           {
//            BodyDataRefresh();
//            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPosition))  
//            {
//             ShoulderSteps = BODY_DETECT_ADJ;
//             Timer_Counter_Clear(C_TIMER_5);
//            }
//           }
//           break;
//         case BODY_DETECT_ADJ:  //揉脖子并调整脖子位置
//            KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,KNEAD_SPEED3_PWM);
//            if(bKeyWalkUp)
//            {
//              if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPositionTop)) //nShoulderPositionBottom
//              {
//                nBuzzerMode = BUZZER_MODE_FAST ;
//                bSendBuzzerMode = TRUE ;
//              }
//              else
//              {
//                nBuzzerMode = BUZZER_MODE_SLOW ;
//                bSendBuzzerMode = TRUE ;
//                Timer_Counter_Clear(C_TIMER_5);//add by wgh 20150313
//              }
//            }
//            if(bKeyWalkDown)
//            {
//              if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPositionBottom)) //nShoulderPositionBottom
//              {
//                nBuzzerMode = BUZZER_MODE_FAST ;
//                bSendBuzzerMode = TRUE ;
//              }
//              else
//              {
//                nBuzzerMode = BUZZER_MODE_SLOW ;
//                bSendBuzzerMode = TRUE ;
//                Timer_Counter_Clear(C_TIMER_5);//add by wgh 20150313
//              }
//            }
//            if((!bKeyWalkUp) && (!bKeyWalkDown))
//            {
//              WalkMotor_Control(STATE_WALK_IDLE, 0);
//              nBuzzerMode = BUZZER_MODE_OFF ;
//              bSendBuzzerMode = TRUE ;
//            }
//            if(Timer_Counter(C_TIMER_5,5*10))
//            {
//              nShoulderPosition = Input_GetWalkMotorPosition();  
//              ShoulderSteps = BODY_DETECT_OVER;
//              break;
//            }
//            break;
//          case BODY_DETECT_OVER:  
//            bShoulderOK = 1;
//            if(detect3D)
//            {
//              BodyDetectStep = DETECT_3D;
//            }
//            break;
//         }
//       }
//       if(DETECT_3D == BodyDetectStep)
//       {
//         switch(steps)
//         {
//         case 0:   //准备
//           {
//             KnockMotor_Break();
//             if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MED,KNEAD_SPEED2_PWM) && (AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_8)))    
//             {
//               steps++;
//             }
//             positionCount = 0;
//             positionTicks = nShoulderPosition/_3D_FULL_POINT;   //设置3D电流采集点之间的行走脉冲数量 
//           }
//           break;
//         case 1:  
//           if(WalkMotor_Control(STATE_RUN_WALK_POSITION,positionCount*positionTicks)) //到达行走位置点
//           {
//             steps++;
//           }
//           break;
//         case 2:  //3D马达运动到最后面   
//           {
//             if(AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_8))
//             {
//               steps++;
//               AxisMotor_UpdataPosition();
//             }
//           }
//           break;    
//         case 3:  //3D马达运动到最前面  
//           {
//             if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,_3D_SPEED_8))
//             {
//               steps++;
//             }
//             AxisMotor_StorageCurrent(positionCount,positionCount*positionTicks);  //存储电流值11*40个点
//           }
//           break;
//         case 4:  //数据记录与处理
//           {
//             positionCount++;
//             if(positionCount > _3D_FULL_POINT )  //一共采集数据_3D_FULL_POINT+1次
//             {
//               steps++;
//               break;
//             }
//             steps = 1; 
//           }
//           break;
//         case 5:  //结束
//           {
//             nChairRunState = CHAIR_STATE_RUN;
//             BodyDetectStep = DETECT_FINISH;
//              // bodyDectect = 1;
//             AxisMotor_CurrentAdj();
//           }
//           break;  
//         }//end switch
//         } // end if
//   /***************程序退出区**************************/
//}

/******************************************************************************/
void Main_Settle_1ST(void)
{
    
    BYTE key;
    
    while(nChairRunState == CHAIR_STATE_SETTLE_1ST)
    {
        //按键处理区
        
        key = Main_GetKey();
        key &= 0x7f;
        
        
        if(H10_KEY_NONE != key)
        {
            Timer_Counter_Clear(C_TIMER_TEMP);
            switch(key)
            {
                /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
                
            case H10_KEY_MENU:
                break;
            case H10_KEY_POWER_SWITCH: 
                break ;
                
//            case H10_KEY_RESET_CONFIRM: 
//                bBackLegPadSettle = TRUE ;
//                nChairRunState = CHAIR_STATE_SETTLE ;
//                bTimeoverRestSleepStatus = FALSE;
//                nSettleMode = POWER_KEY_RESET;   
//                
//                break;
                
//            case H10_KEY_RESET_CANCLE :
//                __no_operation();
//                __no_operation();
//                __no_operation();
//                __no_operation();
//                __no_operation();
//                __no_operation();
//                if(nChairRunState_Pre==CHAIR_STATE_WAIT_COMMAND)
//                {
//                    nChairRunState = CHAIR_STATE_WAIT_COMMAND ;
//                    
//                    
//                }
//                
//                break;
		
            default:break;
            
            
            }
            
        }
        
        
        if(nChairRunState_Pre==CHAIR_STATE_WAIT_COMMAND)
        {
            Input_Proce();
            Valve_Send_Data();
            Main_Send();
            Main_BlueToothSend();
            //Main_MassageSignalSend();
            //靠背升降电机手动处理
            Main_BackPad_Proce();
            //小腿升降电机手动处理
            Main_LegPad_Proce();
            //小腿伸缩电机手动处理
            Main_FlexPad_Proce();
            Main_Massage_Position_Proce();
            FlexMotorFollowingFood();
            Main_Send_Leg();
            Problem_Proce();
            MusicSampling();
            //VoiceUart_Proce();  
            if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE) &&
               (bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE) &&
                   (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE)&&  
                (bKeyArmPadOut == FALSE) && (bKeyArmPadIn == FALSE))//cyw 20180305
            {
                if((nBuzzerMode == BUZZER_MODE_FAST) ||
                   (nBuzzerMode == BUZZER_MODE_SLOW))
                {
                    nBuzzerMode = BUZZER_MODE_OFF ;
                    bSendBuzzerMode = TRUE ;
                }
            }
            
        }
        
        
    }
}


/******************************************************************************/
void Main_Settle(void)
{
    bool bEngineeringSettle = ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS);
    int steps = 0;
    BYTE key;
    nHeatStreng=0;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    VoiceUart_PowerOff();  //复位过程中语音不起作用
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    bKeyLegPadUp = FALSE ;
    bKeyLegPadDown = FALSE ;        
    bAngleNoChangeProcess = FALSE;
    bAngleNoChangeCMD = FALSE;    
    nChairRunState = CHAIR_STATE_SETTLE ;//按摩椅处于收藏状态
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION ;
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    bBackLegPadSettle = TRUE ;
    Main_Close_Power();
    Valve_LegFootAirPumpACPowerOff();
    Valve_BodyUpAirPumpACPowerOff();
    Valve_CloseAll();
    //LegKnead_SetPower(LEG_KNEAD_OFF);
    //LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
    RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
    RockFunctionEnable(false);   
    nRockModeEnterEnable = ExitRock;//进入复位后将摇椅的标志位置0，防止时间结束后摇椅函数将标志置1导致椅子无法复位的问题
    BackMotor_Control(STATE_BACK_IDLE) ;
    LegMotor_Control(STATE_LEG_IDLE) ;
    SlideMotorControl(STATE_SLIDE_IDLE) ;
    Valve_OzonOff();
    bLedFlag = 0;//进入复位要关闭灯光
    // KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
    if(bEngineeringSettle || nSettleMode == POWER_KEY_RESET)//按了电源键关机复位会向下执行
    {
        if(bTimeoverRestSleepStatus)//
        {
            bMassagePositionUpdate = FALSE;//bZeroflash = FALSE;
        }
        else//按下电源键关机复位会执行下面语句
        {
            bBackLegPadSettle = TRUE ;
            nTargetMassagePosition = MASSAGE_RESET_POSITION;
            bMassagePositionUpdate = TRUE;          
        }
    }
    else//如果是时间结束关机则执行下面的语句
    {
        bMassagePositionUpdate = FALSE;
    }
    //BlueToothUart_AMP_Volume_On();
    SingleLine_Sound_ON=false;
    SingleLine_Send_Mode = 3;
    bTapping = 0;
    
    //主循环
    while(nChairRunState == CHAIR_STATE_SETTLE)
    {
        SingleLinr_Send();
        //按键处理区
        key = Main_GetKey();
        if(key != H10_KEY_NONE)
        {
            Power_All_Off();
            //Main_Initial_IO();
            //Main_Initial_Data();
            bBackLegPadSettle = FALSE;
            nChairRunState = CHAIR_STATE_SLEEP; 
        }
        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */    
        //时间处理区
        if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,SETTLE_INDICATE_TIME))
        {
            IndicateLED_Toggle();
        }
        Input_Proce();
        Valve_Send_Data();
        Main_Send();
        Main_BlueToothSend();
        Main_Massage_Position_Proce();
        Problem_Proce();
        MusicSampling();
        //VoiceUart_Proce();  
        switch(steps)  
        {
        case 0:   //揉捏马达停在最宽处
            KnockMotor_Break();
            if(KneadMotor_Control(STATE_KNEAD_IDLE,KNEAD_SPEED0_PWM)) 
                
                //if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED3_PWM))    
            {
                steps++;    
            }
            break;
        case 1:   //揉捏马达停在最宽处
            //KnockMotor_Break();
            if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED3_PWM))    
            {
                steps++;    
            }
            break;
            
        case 2: 
            if(bTimeoverRestSleepStatus )
            {
                
                if(Input_GetWalkMotorPosition() > _3D_MOTOR_WALK_MAX_POSITION)
                {
                    steps++;
                }
                else
                {
                    if( AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_5))
                        steps++;
                }
            }
            //if( AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_10))
            else if( AxisMotor_Control(STATE_RUN_AXIS_POSITION,2,_3D_SPEED_5))
            {
                steps++;    
            }  
            break;
            
            
        case 3:   //行走马达停在上行程开关位置
            if(bTimeoverRestSleepStatus )
            {
                steps++; 
            }
            else if(WalkMotor_Control(STATE_RUN_WALK_UP,0))
                {
                    steps++;    
                }  
            break;
            
        case 4:   //行走马达停在复位位置
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,RESET_POSITION))
            {
                steps++;    
            }  
            break;
        case 5: 
            if( AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,_3D_SPEED_8))
            {
                steps++;    
            }  
            break;
        default:    
            steps = 100;    
            break;
        }
        
        if((!bMassagePositionUpdate) && (steps == 100))
        {
            nChairRunState = CHAIR_STATE_SLEEP; 
        }
        
        if(Timer_Counter(C_TIMER_TEMP+T_LOOP,2*60*10))
        {
            nChairRunState = CHAIR_STATE_SLEEP;   //2分钟时间保护
        }
        LED_RGB_Proce(nChairRunState);
        
    } //end while
    /***************程序退出区**************************/
    WalkMotor_Control(STATE_WALK_IDLE,0);
    SlideMotorControl(STATE_LEG_IDLE);
    BackMotor_Control(STATE_BACK_IDLE) ;
    LegMotor_Control(STATE_LEG_IDLE) ;
    bMassagePositionUpdate = FALSE;
}

void Main_WaitCommand(void)
{
    BYTE key;
    bool bEnableDemo = false;//在commend里面按住行走的上下都会将其置1，够5s后就进入demo程序
    
    Power_All_On();
    Main_Stop_All();
    //VoiceUart_PowerOn();
    
    bBackLegPadSettle = FALSE ;
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    bKeyLegPadUp = FALSE ;
    bKeyLegPadDown = FALSE ;
    
    nBackMainRunMode = BACK_MAIN_MODE_IDLE ;
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION ;
    nCurSubFunction = BACK_SUB_MODE_NO_ACTION;
    nChairRunState = CHAIR_STATE_WAIT_COMMAND ;//按摩椅等待按键命令
    
    Data_Set_Start(0,0);
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Timer_Counter_Clear(C_TIMER_500MS);
    bDemoStretch = FALSE;
    unsigned int pw_Information[10];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
    //主循环
    //主循环
    bTimeoverRestSleepStatus = FALSE;//与Main_Settle有关的变量，与电源按键有关
    //BlueToothUart_AMP_Volume_On();
    //KneadMotor_Control(STATE_KNEAD_IDLE,0);
    nChairRunState_Pre=nChairRunState;//在Main_Settle_1ST函数中使用
    
    while(nChairRunState == CHAIR_STATE_WAIT_COMMAND)
    {
        //按键处理区
        if(nVoicekey != H10_KEY_NONE)
        {
            key = nVoicekey;
        }
        else
        {
            key = Main_GetKey();
            key &= 0x7f;
        }
        if(H10_KEY_NONE != key)
        {
            Timer_Counter_Clear(C_TIMER_TEMP);
            switch(key)
            {
                /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
                {
                case H10_KEY_MENU:
                    break;
                case H10_KEY_MEMORYA_OUT:      
                    Memory_Out(MEMORYA_ADDR_BASE);
                    Command_Memory_Out = 1;
                    //nBackSubRunMode = 0;
                    break;
                case H10_KEY_MEMORYB_OUT:
                    Memory_Out(MEMORYB_ADDR_BASE);
                    Command_Memory_Out = 1;
                    // nBackSubRunMode = 0;
                    break;
                case H10_KEY_POWER_SWITCH: 
                    {
                        //#ifdef Quick_Resetting   //按停止键快速复位
                        bBackLegPadSettle = TRUE ;
                        nChairRunState = CHAIR_STATE_SETTLE ;
                        bTimeoverRestSleepStatus = FALSE;
                        nSettleMode = POWER_KEY_RESET;       
                        SingleLine_Play(4,1);  //暂停
                        RockFunctionEnable(false);
                        handrail_flag = 0;//斷電扶手停止
                        bKeyArmPadOut = false;
                        bKeyArmPadIn = false;
                        //              #else
                        //               nChairRunState = CHAIR_STATE_SETTLE_1ST ;
                        //              #endif	
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break ;
                    
                    /**********************************扶手手动控制开始*****************************/
                case H10_KEY_HANDRAIL_OUT_START:
                    handrail_flag = 0;
                    outarmcmd = H10_KEY_HANDRAIL_OUT_START;
                    //outarmcmdmemory = outarmcmd;
                    bKeyArmPadOut = TRUE;
                    bKeyArmPadIn = false;
                    //            nBuzzerMode = BUZZER_MODE_ONETIME ;
                    //            bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_HANDRAIL_OUT_STOP:  
                    outarmcmd = H10_KEY_HANDRAIL_OUT_STOP;
                    //outarmcmdmemory = outarmcmd;
                    bKeyArmPadOut = false;
                    bKeyArmPadIn = false;
                    //            nBuzzerMode = BUZZER_MODE_ONETIME ;
                    //            bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_HANDRAIL_IN_START:
                    handrail_flag = 0;
                    outarmcmd = H10_KEY_HANDRAIL_IN_START;
                    //outarmcmdmemory = outarmcmd;
                    bKeyArmPadOut = false;
                    bKeyArmPadIn = true;
                    //            nBuzzerMode = BUZZER_MODE_ONETIME ;
                    //            bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_HANDRAIL_IN_STOP:
                    outarmcmd = H10_KEY_HANDRAIL_IN_STOP;
                    //outarmcmdmemory = outarmcmd;
                    bKeyArmPadOut = false;
                    bKeyArmPadIn = false;
                    //            nBuzzerMode = BUZZER_MODE_ONETIME ;
                    //            bSendBuzzerMode = TRUE ;
                    break;
                    /**********************************扶手手动控制结束*****************************/
                    
                    /**********************************语言标志控制开始**********************/
                case H10_KEY_LANGUAGE_ENGLISH:
                    bLanguageFlag = Language_English;
                    *(pInformation + LANGUAGE_ADDRESS) = Language_English; //写编程标志位
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
                    break;
                case H10_KEY_LANGUAGE_CHINESE:
                    bLanguageFlag = Language_Chinese;
                    *(pInformation + LANGUAGE_ADDRESS) = Language_Chinese; //写编程标志位
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
                    break; 
                case H10_KEY_LANGUAGE_ELSE:
                    bLanguageFlag = Language_Else;
                    *(pInformation + LANGUAGE_ADDRESS) = Language_Else; //写编程标志位
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
                    break; 
                    /**********************************语言标志控制结束**********************/
                    
                    /**********************************三挡拉筋控制开始**********************/
                case H10_KEY_STRETCH_VIGOR1:
                    nStretchVigor =1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_STRETCH_VIGOR2:
                    nStretchVigor=2;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;          
                case H10_KEY_STRETCH_VIGOR3:
                    nStretchVigor=3;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;       
                    /**********************************三挡拉筋控制结束**********************/
                    
                    /**********************************LED灯控制开始**********************/
                case H10_KEY_LED_SWITCH:
                    if(bLedFlag)
                    {
                        bLedFlag = 0;
                    }
                    else
                    {
                        bLedFlag = 1;
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                    /**********************************LED灯控制开始**********************/
                case H10_KEY_SWAY_ONOFF:  //wait                           //0X76        
                    RockFunctionEnable(true);
                    nChairRunState = CHAIR_STATE_RUN ;     
                    if(nKeyAirBagLocate != AIRBAG_LOCATE_AUTO)
                    {
                        nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;
                        nChairRunState = CHAIR_STATE_RUN ;
                        if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                        {
                            Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);          
                        }     
                        st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
                        st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
                        st_AirBagArmSholderBackWaist.init = TRUE;
                        st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
                        st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
                        st_AirBagModeLegFootSeat.init = TRUE;    
                        bRollerEnable = TRUE;
                    }
                    bZero_ShowFlag = 0;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;                
                    break;            
                    
                case H10_KEY_ZERO_1://waitcommend
                    nChairRunState = CHAIR_STATE_RUN;
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 1;
                    RockFunctionEnable(false);
                    st_Stretch.active = FALSE;
                    bMassagePositionUpdate = TRUE;
                    bZero_ShowFlag = 1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_ZERO_2:	
                    nChairRunState = CHAIR_STATE_RUN;
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 2;
                    RockFunctionEnable(false);
                    st_Stretch.active = FALSE;
                    bMassagePositionUpdate = TRUE;
                    bZero_ShowFlag = 1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;               
                case H10_KEY_ZERO_3:
                    nChairRunState = CHAIR_STATE_RUN;
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 3;
                    bMassagePositionUpdate = TRUE;
                    bZero_ShowFlag = 1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_ZERO_RESET:
                    if(Zero_mark ==0) break;
                    Zero_mark= 0;
                    RockFunctionEnable(false);
                    st_Stretch.active = FALSE;  
                    nChairRunState = CHAIR_STATE_RUN;
                    nTargetMassagePosition = MASSAGE_INIT_POSITION;
                    bMassagePositionUpdate = TRUE;
                    bZero_ShowFlag = 1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_TAPPING_ONOFF : 
                    if(bTapping == 0)
                    {
                        bTapping = 1;
                    }
                    else
                    {
                        bTapping = 0;
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_BLUETOOTH_POWER_SWITCH:
                    if(bBlueToothStatus)
                    {
                        bBlueToothStatus = 0;
                    }
                    else
                    {
                        bBlueToothStatus = 1;
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_CHAIR_AUTO_0:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_0;
                    RockFunctionEnable(false);
                    break ;
                case H10_KEY_CHAIR_AUTO_1:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_1;
                    RockFunctionEnable(false);
                    break ;
                case H10_KEY_CHAIR_AUTO_2:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_2;
                    RockFunctionEnable(false);
                    RockStartTimeFlag = TRUE;
                    break ;
                case H10_KEY_CHAIR_AUTO_3:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO; 
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_3;   //拉伸，舒展滚背
                    RockFunctionEnable(false);
                    break ;
                case H10_KEY_CHAIR_AUTO_4:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_4;   //腰椎舒缓
                    RockFunctionEnable(false);
                    break ;
                case H10_KEY_CHAIR_AUTO_5:
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_5;     //运动恢复
                    RockFunctionEnable(false);
                    break ;     
                case H10_KEY_CHAIR_AUTO_6:                //总裁养身
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_6;
                    break ;
                case H10_KEY_CHAIR_AUTO_7:                   //女王纤体
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_7;
                    break ;
                case H10_KEY_CHAIR_AUTO_8:                   //心灵spa
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_8;
                    break ;
                    
                    
                    //	    case H10_KEY_CHAIR_AUTO_EXAMINEE :
                    //	      nChairRunState = CHAIR_STATE_RUN ;
                    //              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    //              nBackSubRunMode = BACK_SUB_MODE_AUTO_6;
                    //	       RockFunctionEnable(false);  
                    //	      break;
                    
                    //	    case  H10_KEY_CHAIR_AUTO_HIGH_UP:
                    //	      nChairRunState = CHAIR_STATE_RUN ;
                    //              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    //              nBackSubRunMode = BACK_SUB_MODE_AUTO_7;  
                    //	       RockFunctionEnable(false);  
                    //	      break;
                    
                    //	     case H10_KEY_CHAIR_AUTO_GOLFER :
                    //	     nChairRunState = CHAIR_STATE_RUN ;
                    //              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    //              nBackSubRunMode = BACK_SUB_MODE_AUTO_8;         
                    //	        RockFunctionEnable(false);        
                    //	      break;
                    //	   case  H10_KEY_CHAIR_AUTO_9 :
                    //	      nChairRunState = CHAIR_STATE_RUN ;
                    //              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    //              nBackSubRunMode = BACK_SUB_MODE_AUTO_9;  
                    //	       RockFunctionEnable(false);  
                    //	      break;
                    //	      
                    //	    case   H10_KEY_CHAIR_AUTO_10:
                    //	      nChairRunState = CHAIR_STATE_RUN ;
                    //              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    //              nBackSubRunMode = BACK_SUB_MODE_AUTO_10;  
                    //	      
                    //	       RockFunctionEnable(false);  
                    //	      break;
                    //quick mode
                case H10_KEY_CHAIR_QUICK_FULL://20160808
                    
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_FULL;  
                    
                    RockFunctionEnable(false);  
                    
                    
                    break;
                case H10_KEY_CHAIR_QUICK_SHOULDER://20160808
                    
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_SHOULDER;  
                    
                    RockFunctionEnable(false);  
                    
                    
                    break;  
                case H10_KEY_CHAIR_QUICK_WAIST://20160808
                    
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_WAIST;  
                    
                    RockFunctionEnable(false);  
                    bShoulderOK = 1;
                    
                    break;  	  
                    
                case H10_KEY_CHAIR_QUICK_LEG://20160808
                    
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBackMainRunMode = BACK_MAIN_MODE_AUTO;
                    nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_LEG;  
                    
                    RockFunctionEnable(false);  
                    bShoulderOK = 1;
                    
                    break;  		  
                    
                case H10_KEY_3DMODE_1://waitcommend
                    nBackSubRunMode = BACK_SUB_MODE_3D1;
                    nBackMainRunMode = BACK_MAIN_MODE_3D;
                    nChairRunState = CHAIR_STATE_RUN ;
                    nKeyBackLocate =  LOCATE_FULL_BACK;
                    
                    //              bBackAutoModeInit = TRUE;     // 初始化自动模式
                    //              nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION; // MASSAGE_OPTIMAL_POSITION; 
                    //              bMassagePositionUpdate = TRUE;    // 靠背下趟开始
                    
                    
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 2;
                    //st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
                    bMassagePositionUpdate = TRUE;
                    break;
                case H10_KEY_3DMODE_2:
                    nBackSubRunMode = BACK_SUB_MODE_3D2;
                    nBackMainRunMode = BACK_MAIN_MODE_3D;
                    nChairRunState = CHAIR_STATE_RUN ;
                    nKeyBackLocate =  LOCATE_FULL_BACK;
                    
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 1;
                    bMassagePositionUpdate = TRUE;
                    break;  
                case H10_KEY_3DMODE_3:
                    nBackSubRunMode = BACK_SUB_MODE_3D3;
                    nBackMainRunMode = BACK_MAIN_MODE_3D;
                    nChairRunState = CHAIR_STATE_RUN ;
                    nKeyBackLocate =  LOCATE_FULL_BACK;
                    
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    Zero_mark = 1;
                    bMassagePositionUpdate = TRUE;
                    
                    break;  
                case H10_KEY_3DMODE:
                    nBackSubRunMode = BACK_SUB_MODE_3D1;
                    nBackMainRunMode = BACK_MAIN_MODE_3D;
                    nChairRunState = CHAIR_STATE_RUN ;
                    break;      
                    
                case H10_KEY_ZERO_START:
                    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;//bRestSleepStatus总是0
                    if(Zero_Grade(Input_GetBackPosition())<2)
                    {
                        nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                    }
                    else
                    {
                        nTargetMassagePosition = MASSAGE_INIT_POSITION; 
                        nZero_OK = 0;
                    }
                    
                    Zero_mark = Zero_Grade(Input_GetBackPosition())+1;
                    if(Zero_mark>=3) Zero_mark =0;
                    RockFunctionEnable(false);
                    st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
                    bMassagePositionUpdate = TRUE;
                    bZero_ShowFlag = 1;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case  H10_KEY_3D_STRENGTH:    
                    break;
                    
                    break;
                    
                case H10_KEY_WORK_TIME_10MIN:
                    w_PresetTime = RUN_TIME_10;
                    Data_Update_Time(w_PresetTime);
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_WORK_TIME_20MIN:
                    w_PresetTime = RUN_TIME_20;
                    Data_Update_Time(w_PresetTime);
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_WORK_TIME_30MIN:
                    w_PresetTime = RUN_TIME_30;
                    Data_Update_Time(w_PresetTime);
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_AIRBAG_AUTO://waitcommend
                    RockFunctionEnable(false);   //禁止摇椅
                    nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;//设置范围是全身气囊
                    if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                    {
                        Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);//设置初始气囊力度是3
                    }
                    st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
                    st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
                    st_AirBagArmSholderBackWaist.init = TRUE;
                    
                    st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
                    st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
                    st_AirBagModeLegFootSeat.init = TRUE; 
                    bRollerEnable = TRUE;
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break ;                
                case H10_KEY_AIRBAG_STRENGTH_1:
                    break;
                case H10_KEY_AIRBAG_STRENGTH_2:
                    break;
                case H10_KEY_AIRBAG_STRENGTH_3:
                    break;
                case H10_KEY_AIRBAG_STRENGTH_4:
                    break;
                case H10_KEY_AIRBAG_STRENGTH_5:
                    break;  
                case H10_KEY_AIRBAG_STRENGTH_OFF:
                    break;    
                    
                case H10_KEY_3DSPEED_1:
                case H10_KEY_3DSPEED_2:
                case H10_KEY_3DSPEED_3:
                case H10_KEY_3DSPEED_4:
                case H10_KEY_3DSPEED_5:
                    /*
                    if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))    
                    {
                    nKeyAxisStrength = H10_KEY_3DSPEED_5 - key;
                    nKeyAxisStrength %= 5;
                    bAxisUpdate = TRUE;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;   
                }
                    */
                    break;
                case H10_KEY_KNEAD_CLOCK://waitcommend
                    nKneadTurn = 1;
                    //RockFunctionEnable(false);
                    nMaunalSubMode = nMaunalSubMode_KNEAD;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    //nMaunalSubMode_Momery = nMaunalSubMode;
                    bMain_Start_Manual_WalkNoNeed = false;
                    break;
                case H10_KEY_KNEAD_ANTICLOCK://waitcommend
                    nKneadTurn = 2;
                    //RockFunctionEnable(false);
                    nMaunalSubMode = nMaunalSubMode_KNEAD;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    //nMaunalSubMode_Momery = nMaunalSubMode;
                    bMain_Start_Manual_WalkNoNeed = false;
                    break;  
                case H10_KEY_KNEAD://waitcommend
                    //RockFunctionEnable(false);   
                    nMaunalSubMode = nMaunalSubMode_KNEAD;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK;
                    break;
                case H10_KEY_KNOCK://waitcommend
                    //RockFunctionEnable(false);   
                    nMaunalSubMode = nMaunalSubMode_KNOCK;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    break;
                    
                case H10_KEY_WAVELET://waitcommend
                    //RockFunctionEnable(false);   
                    nMaunalSubMode = nMaunalSubMode_WAVELET;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    break;
                    
                case H10_KEY_SOFT_KNOCK://waitcommend
                    //RockFunctionEnable(false);   
                    
                    nMaunalSubMode = nMaunalSubMode_SOFT_KNOCK;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    break;
                    
                case H10_KEY_PRESS://waitcommend
                    //RockFunctionEnable(false);   	  
                    nMaunalSubMode = nMaunalSubMode_PRESS;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    bMain_Start_Manual_WalkNoNeed = false;
                    break;
                    
                case H10_KEY_MUSIC:   //waitcommend
                    //RockFunctionEnable(false);   
                    nMaunalSubMode = nMaunalSubMode_MUSIC;
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nChairRunState = CHAIR_STATE_RUN ;
                    bMain_Start_Manual_WalkNoNeed = false;
                    break;  
                case H10_KEY_MANUAL://waitcommend
                    nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                    nMaunalSubMode = 5;
                    nChairRunState = CHAIR_STATE_RUN ;
                    bMain_Start_Manual_WalkNoNeed = false;
                    break;
                    
                case H10_KEY_LOCATE_FULL:
                case H10_KEY_LOCATE_POINT:
                case H10_KEY_LOCATE_PART:  
                    break;
                case H10_KEY_OZON_SWITCH:
                    bOzonEnable = TRUE;
                    nChairRunState = CHAIR_STATE_RUN ;
                    if(Data_Get_Time() == 0)
                    {
                        Data_Set_Start(1, w_PresetTime);
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;  
                    //            case H10_KEY_SPEED_DECREASE:
                case H10_KEY_SPEED_1:
                case H10_KEY_SPEED_2:
                case H10_KEY_SPEED_3:
                case H10_KEY_SPEED_4:
                case H10_KEY_SPEED_5:  
                case H10_KEY_SPEED_6:
                    break ;
                case H10_KEY_WIDTH_INCREASE:
                case H10_KEY_WIDTH_DECREASE:
                case H10_KEY_WIDTH_MIN:  
                case H10_KEY_WIDTH_MED:  
                case H10_KEY_WIDTH_MAX: 
                    break ;
                    
                case H10_KEY_AIRBAG_LEG://waitcommend
                    RockFunctionEnable(false);   
                    nKeyAirBagLocate = AIRBAG_LOCATE_LEG_FOOT ;
                    st_AirBagLegFoot.init = TRUE ;
                    if(Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                    {
                        Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
                    }
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_AIRBAG_ARM: //waitcommend
                    RockFunctionEnable(false);   
                    nKeyAirBagLocate = AIRBAG_LOCATE_ARM_SHOLDER ;
                    st_AirBagArmSholder.init = TRUE ;
                    if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                    {
                        Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
                    }
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_AIRBAG_WAIST://waitcommend
                    RockFunctionEnable(false);   
                    nKeyAirBagLocate = AIRBAG_LOCATE_BACK_WAIST ;
                    st_AirBagBackWaist.init = TRUE ;
                    if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                    {
                        Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
                    }
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                case H10_KEY_AIRBAG_BUTTOCKS://waitcommend
                    RockFunctionEnable(false);   
                    nKeyAirBagLocate = AIRBAG_LOCATE_SEAT ;
                    st_AirBagSeat.init = TRUE ;
                    if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                    {
                        Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
                    }
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;  
                    
                case H10_KEY_WALK_UP_START:
                    Timer_Counter_Clear(C_TIMER_500MS);
                    bEnableDemo = true;
                    break ;
                case H10_KEY_WALK_UP_STOP:
                    Timer_Counter_Clear(C_TIMER_500MS);
                    bEnableDemo = false;
                    break ;
                case H10_KEY_WALK_DOWN_START:
                    Timer_Counter_Clear(C_TIMER_500MS);
                    bEnableDemo = true;
                    break ;
                case H10_KEY_WALK_DOWN_STOP:
                    Timer_Counter_Clear(C_TIMER_500MS);
                    bEnableDemo = false;
                    break ;
                    
                case H10_KEY_BACKPAD_UP_START://waitcommend
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyBackPadUp = TRUE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyLegPadDown = TRUE ;
                    bKeyLegPadUp = FALSE ;
                    bLegPadLinkage = TRUE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_BACKPAD_UP_STOP:
                    //st_Stretch.active = FALSE;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bKeyLegPadUp = FALSE ;
                    bLegPadLinkage = TRUE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_BACKPAD_DOWN_START:
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = TRUE ;
                    bKeyLegPadDown = FALSE ;
                    bKeyLegPadUp = TRUE ;
                    bLegPadLinkage = TRUE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_BACKPAD_DOWN_STOP:
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bKeyLegPadUp = FALSE ;
                    bLegPadLinkage = TRUE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_LEGPAD_EXTEND_START:
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = TRUE ;
                    bKeyFlexIn = FALSE ;
                    break;
                case H10_KEY_LEGPAD_EXTEND_STOP:
                case H10_KEY_LEGPAD_CONTRACT_STOP:
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE;
                    bKeyFlexIn = FALSE ;
                    break;
                case H10_KEY_LEGPAD_CONTRACT_START:
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE;
                    bKeyFlexIn = TRUE ;
                    break;
                case H10_KEY_LEGPAD_UP_START:
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyLegPadUp = TRUE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_LEGPAD_UP_STOP:
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_LEGPAD_DOWN_START:
                    handrail_flag = 0;
                    Timer_Counter_Clear(C_TIMER_TEMP);         
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = TRUE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                case H10_KEY_LEGPAD_DOWN_STOP:
                    bKeyLegPadUp = FALSE ;
                    bKeyLegPadDown = FALSE ;
                    bLegPadLinkage = FALSE ;
                    bKeyBackPadUp = FALSE ;
                    bKeyBackPadDown = FALSE ;
                    bKeyFlexOut = FALSE ;
                    bKeyFlexIn = FALSE ;
                    break ;
                    
                case H10_KEY_WHEEL_SPEED_OFF:
                    break;
                case H10_KEY_WHEEL_SPEED_SLOW:
                case H10_KEY_WHEEL_SPEED_MED:
                case H10_KEY_WHEEL_SPEED_FAST:
                    bRollerEnable = TRUE;
                    if(key ==  H10_KEY_WHEEL_SPEED_SLOW)
                    {
                        nRollerPWM = 1;
                    }
                    if(key ==  H10_KEY_WHEEL_SPEED_MED)
                    {
                        nRollerPWM = 2;
                    }
                    if(key ==  H10_KEY_WHEEL_SPEED_FAST)
                    {
                        nRollerPWM = 3;
                    }
                    Valve_SetRollerPWM(nRollerPWM);
                    if(nRollerPWM != 0)
                    {
                        nChairRunState = CHAIR_STATE_RUN ;
                        if(Data_Get_Time() == 0)
                        {
                            Data_Set_Start(1, w_PresetTime);
                        }
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;
                    
                case H10_KEY_LEG_WHEEL_OFF:
                    
                    //bLegKneadEnable=0;    
                    
                    break;    
                case H10_KEY_LEG_WHEEL_1:
                    //bLegKneadEnable=1;
                    // LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
                    //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_SLOW);//LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
                    nChairRunState = CHAIR_STATE_RUN ;
                    if(Data_Get_Time() == 0)
                    {Data_Set_Time(w_PresetTime);
                    Data_Set_Start(1, w_PresetTime);
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    
                    break;
                    
                case H10_KEY_LEG_WHEEL_2:
                    //bLegKneadEnable=1;
                    //    LegKneadSpeed=LEG_KNEAD_SPEED_MID  ;
                    //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_MID);
                    nChairRunState = CHAIR_STATE_RUN ;
                    if(Data_Get_Time() == 0)
                    {Data_Set_Time(w_PresetTime);
                    Data_Set_Start(1, w_PresetTime);
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    
                    break;     
                case H10_KEY_LEG_WHEEL_3:
                    //bLegKneadEnable=1;
                    // LegKneadSpeed=LEG_KNEAD_SPEED_FAST  ;
                    //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_FAST);
                    nChairRunState = CHAIR_STATE_RUN ;
                    if(Data_Get_Time() == 0)
                    {Data_Set_Time(w_PresetTime);
                    Data_Set_Start(1, w_PresetTime);
                    }
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    
                    break; 
                    
                case H10_KEY_HEAT_MED:
                    bKeyWaistHeat = TRUE ;
                    nHeatStreng = 2;
                    nHotTime = 0;  //要修改
                    WaistHeat_On();//要修改
                    nChairRunState = CHAIR_STATE_RUN ;
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    
                    break;
                case H10_KEY_HEAT:    //加热
                    RockFunctionEnable(false);   
#ifdef heat_1class
                    if(bKeyWaistHeat == FALSE)
                    {
                        bKeyWaistHeat = TRUE ;
                        
                        nChairRunState = CHAIR_STATE_RUN ;
                    }
                    else
                    {
                        bKeyWaistHeat = FALSE ;
                        
                    }
                    
#else
                    if(bKeyWaistHeat == FALSE)
                    {
                        bKeyWaistHeat = TRUE ;
                        nHeatStreng = 1;
                        nHotTime = 0;  //要修改
                        WaistHeat_On();//要修改
                        nChairRunState = CHAIR_STATE_RUN ;
                    }
                    else
                    {
                        nHeatStreng++;
                        if(nHeatStreng > 3)
                        {
                            bKeyWaistHeat = FALSE;
                            //140623
                            
                        }
                        else
                        {
                            nHotTime = 0;  //要修改
                            WaistHeat_On();//要修改
                        }
                        
                        
                        //bKeyWaistHeat = FALSE ;
                    }
#endif
                    nBuzzerMode = BUZZER_MODE_ONETIME ;
                    bSendBuzzerMode = TRUE ;
                    break;     
                default:       
                    break;
                }
            }
        }
        
        /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */    
        //时间处理区
        if(bEnableDemo)
        {
            if(Timer_Counter(C_TIMER_500MS,50))
            {
                nChairRunState = CHAIR_STATE_DEMO; 
            }
        }
        else
        {
            Timer_Counter_Clear(C_TIMER_500MS);
        }
        if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,WAIT_INDICATE_TIME))
        {
            IndicateLED_Toggle();
        }
        if(Timer_Counter(C_TIMER_TEMP,60*10))
        {
            nChairRunState = CHAIR_STATE_SLEEP; 
        }
        Input_Proce();
        Valve_Send_Data();
        
        Main_Send();
        Main_BlueToothSend();
        //Main_MassageSignalSend();
        //靠背升降电机手动处理
        Main_BackPad_Proce();
        //小腿升降电机手动处理
        Main_LegPad_Proce();
        //小腿伸缩电机手动处理
        Main_FlexPad_Proce();
        Main_Arm_Start();
        //扶手声音控制
        Main_ArmPad_Proce();
        
        
        Main_Massage_Position_Proce();
        FlexMotorFollowingFood();
        Main_Send_Leg();
        Problem_Proce();
        MusicSampling();
        //VoiceUart_Proce();  
        if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE) &&
           (bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE) &&
               (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE)&& 
                   (bKeyArmPadOut == FALSE) && (bKeyArmPadIn == FALSE))//cyw 20180305
        {
            if((nBuzzerMode == BUZZER_MODE_FAST) ||
               (nBuzzerMode == BUZZER_MODE_SLOW))
            {
                nBuzzerMode = BUZZER_MODE_OFF ;
                bSendBuzzerMode = TRUE ;
            }
        }
        
    } //end while
    
    
    /***************程序退出区**************************/
}
//开始自动程序
void Main_Start_Auto(void)
{
    st_RestSleep.step =0;//未使用
    if( (nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus) )//用于控制睡眠模式，不会执行
    {
        nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION;//改为零重力1位置
        bMassagePositionUpdate = TRUE;
    }
    
    if( (nBackMainRunMode ==BACK_MAIN_MODE_AUTO )&& (nBackSubRunMode == BACK_SUB_MODE_AUTO_2))
    {
        FlexAtuoEnable = TRUE;//打开小腿伸缩跟脚标志位，配合前后摇摆功能
        RockAtuoEnable = TRUE; //使能摇摆标志位
        nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION;
        bMassagePositionUpdate = TRUE;
    }
    else
    {
        if((nBackMainRunMode ==BACK_MAIN_MODE_AUTO )&&( nBackSubRunMode==BACK_SUB_MODE_AUTO_QUICK_FULL ||  nBackSubRunMode==BACK_SUB_MODE_AUTO_QUICK_SHOULDER \
            || nBackSubRunMode==BACK_SUB_MODE_AUTO_QUICK_WAIST || nBackSubRunMode==BACK_SUB_MODE_AUTO_QUICK_LEG))
        {
            nTargetMassagePosition = MASSAGE_QUICK_POSITION;
            bMassagePositionUpdate = TRUE;
        }
        else
        {
            nTargetMassagePosition = MASSAGE_OPTIMAL_POSITION;//MASSAGE_OPTIMAL_POSITION
            bMassagePositionUpdate = TRUE;
        } 
    }
    
    //================================================================
    
    //   if(  nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
    //	{
    //		  Examinee_Mode_Massage_Pointer_Control_Start();
    //
    //		 Set_Moni_cmd_tm(0);
    //		 by_moni_cmd_tm_en = 1;
    //			//防按了EXTEND 再切过来。
    //           st_Stretch.active = FALSE;
    //            bKeyLegPadUp = FALSE ;
    //            bKeyLegPadDown = FALSE ;
    //	    bLegPadLinkage = FALSE ;
    //	    bKeyBackPadUp = FALSE ;
    //	    bKeyBackPadDown = FALSE ;
    //	    bKeyFlexOut = FALSE ;
    //	    bKeyFlexIn = FALSE ;
    //	}
    //   
    //   if(nBackSubRunMode == BACK_SUB_MODE_AUTO_7)
    //	  {
    //	  HipUp_Mode_Massage_Pointer_Control_Start();
    //	  Set_Moni_cmd_tm(0);		
    //	  by_moni_cmd_tm_en = 1;
    //
    //			//防按了EXTEND 再切过来。
    //                   	st_Stretch.active = FALSE;
    //                   	bKeyLegPadUp = FALSE ;
    //                   	bKeyLegPadDown = FALSE ;
    //	            	bLegPadLinkage = FALSE ;
    //	            	bKeyBackPadUp = FALSE ;
    //	            	bKeyBackPadDown = FALSE ;
    //	            	bKeyFlexOut = FALSE ;
    //	            	bKeyFlexIn = FALSE ;
    //	  
    //	  } 
    //   
    //   if(  nBackSubRunMode == BACK_SUB_MODE_AUTO_8)
    //	{
    //	  
    //	    Golf_Mode_Massage_Pointer_Control_Start();
    //	  
    //	    by_moni_cmd_tm_en = 1;
    //
    //			//防按了EXTEND 再切过来。
    //                   	st_Stretch.active = FALSE;
    //                   	bKeyLegPadUp = FALSE ;
    //                   	bKeyLegPadDown = FALSE ;
    //	            	bLegPadLinkage = FALSE ;
    //	            	bKeyBackPadUp = FALSE ;
    //	            	bKeyBackPadDown = FALSE ;
    //	            	bKeyFlexOut = FALSE ;
    //	            	bKeyFlexIn = FALSE ;
    //	}
    //   if(nBackSubRunMode == BACK_SUB_MODE_AUTO_9)
    //   {
    //	 
    //	 	         by_moni_cmd_tm_en = 1;
    //
    //			//防按了EXTEND 再切过来。
    //                   	st_Stretch.active = FALSE;st_GrowthStretch.active = false;
    //                   	bKeyLegPadUp = FALSE ;
    //                   	bKeyLegPadDown = FALSE ;
    //	            	bLegPadLinkage = FALSE ;
    //	            	bKeyBackPadUp = FALSE ;
    //	            	bKeyBackPadDown = FALSE ;
    //	            	bKeyFlexOut = FALSE ;
    //	            	bKeyFlexIn = FALSE ;
    //                        Wrick_Mode_Massage_Pointer_Control_Start();   
    //	 
    //	 
    //   }
    //     if(  nBackSubRunMode == BACK_SUB_MODE_AUTO_10)//growth
    //	 {
    //	   			    by_moni_cmd_tm_en = 1;
    //
    //			//防按了EXTEND 再切过来。
    //                   	st_Stretch.active = FALSE;st_GrowthStretch.active = false;
    //                   	bKeyLegPadUp = FALSE ;
    //                   	bKeyLegPadDown = FALSE ;
    //	            	bLegPadLinkage = FALSE ;
    //	            	bKeyBackPadUp = FALSE ;
    //	            	bKeyBackPadDown = FALSE ;
    //	            	bKeyFlexOut = FALSE ;
    //	            	bKeyFlexIn = FALSE ;
    //	 }// bShoulderOK = 1;
    //   
    
    
    //====================================================================
    bBackAutoModeInit = TRUE ;
    
    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO)&&(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG))
    {
        if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
        {
            nRollerPWM = 0;
            Valve_SetRollerPWM(nRollerPWM);
            //bRollerEnable = FALSE;
            //bRollerEnableStore = FALSE;
            nKeyAirBagLocate = AIRBAG_LOCATE_NONE;
            //140531
        }
        if(nKeyAirBagLocate != AIRBAG_LOCATE_LEG_FOOT)
        {
            nKeyAirBagLocate = AIRBAG_LOCATE_LEG_FOOT ;

            st_AirBagLegFoot.init = TRUE ;
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
            } 
        }
        else
        {
            //    nKeyAirBagLocate = AIRBAG_LOCATE_NONE;
            //    bRollerEnable = FALSE;
        }		
    }
    else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO)&&(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_SHOULDER))
    {
        nKeyAirBagLocate = AIRBAG_LOCATE_ARM_SHOLDER ;
        if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
        {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
        }
        st_AirBagArmSholder.pAirBagArray =AirBagModeArmSholder ;
        st_AirBagArmSholder.nTotalSteps = sizeof(AirBagModeArmSholder) / sizeof(struct AirBagStruct);
        st_AirBagArmSholder.init = TRUE ;
    }
    else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO)&&(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_WAIST))
    {
        nKeyAirBagLocate = AIRBAG_LOCATE_SEAT_WAIST;
        
        if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
        {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
        }
        st_AirBagSeat.pAirBagArray = AirBagModeSeat;
        st_AirBagSeat.nTotalSteps = sizeof(AirBagModeSeat) / sizeof(struct AirBagStruct);
        // st_AirBagSeat.locate = AIRBAG_LOCATE_SEAT;
        st_AirBagBackWaist.pAirBagArray = AirBagModeBackWaist;
        st_AirBagBackWaist.nTotalSteps = sizeof(AirBagModeBackWaist) / sizeof(struct AirBagStruct);
        // st_AirBagBackWaist.locate = AIRBAG_LOCATE_BACK_WAIST;
        st_AirBagBackWaist.init = TRUE ;
        st_AirBagSeat.init = TRUE ; 
    }
    else
    {
        bRollerEnable = TRUE;
        if(nRollerPWM == 0)
        {
            nRollerPWM = 2;
            Valve_SetRollerPWM(nRollerPWM);
        }
        //设置气囊功能
        nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;
        if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
        {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
        }
        
        st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
        st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
        st_AirBagArmSholderBackWaist.init = true;
        st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
        st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
        st_AirBagModeLegFootSeat.init = true;
        
//        st_AirBagArm.pAirBagArray = AirBagModeArm;
//        st_AirBagArm.nTotalSteps = sizeof(AirBagModeArm)/sizeof(struct AirBagStruct);
//        st_AirBagArm.init = true;
    }
}

void Main_Start_3D(void)
{
  if(nTargetMassagePosition != MASSAGE_OPTIMAL2_POSITION)
  {
    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
    bMassagePositionUpdate = TRUE;
  }
  bRollerEnable = TRUE;
  bBackAutoModeInit = TRUE ;
  //设置气囊功能
  nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;
  if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
  {
    Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
  }
  st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
  st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
  st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
  st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
  st_AirBagModeLegFootSeat.init = true;
  st_AirBagArmSholderBackWaist.init = true;
  switch(nBackSubRunMode)
  {
   case  BACK_SUB_MODE_3D1: Data_Set_Start(1, 60*10);/*w_PresetTime= RUN_TIME_10; */break;
   case  BACK_SUB_MODE_3D2: Data_Set_Start(1, RUN_TIME_5); /*w_PresetTime= RUN_TIME_10;*/break;
   case  BACK_SUB_MODE_3D3: Data_Set_Start(1, RUN_TIME_5); /*w_PresetTime= RUN_TIME_10;*/break;  
  }
  nCurSubFunction = BACK_SUB_MODE_NO_ACTION;  //20150303增加，防止显示错乱
   
}


//---------------------------------DIY
void DIY_walkRefreshen(void)
{
// static 
   unsigned char bDIY_Locate;
//static 
unsigned short bDIYPartialTop,bDIYPartialBottom;
  
      bDIY_Locate=(DIYProgramContent>>3)&0x03;
          __no_operation();
      __no_operation();  
      
      if(bDIY_Locate==DIY_SHOULDER)
      {

    //    bDIYPartialTop=nShoulderPosition+DIY_HALF_PARTIAL_DIFF;
    //   if(bDIYPartialTop>TOP_POSITION)bDIYPartialTop=TOP_POSITION;
        if(nShoulderPosition >= (TOP_POSITION - HALF_PARTIAL_DIFF))
        {
          bDIYPartialTop = TOP_POSITION ;
          bDIYPartialBottom =nShoulderPosition - DIY_HALF_PARTIAL_DIFF ;
        }
        else
        {
          bDIYPartialTop =nShoulderPosition + HALF_PARTIAL_DIFF ;
          bDIYPartialBottom = nShoulderPosition - HALF_PARTIAL_DIFF ;
        }     
         

        
      }
      else if(bDIY_Locate==DIY_BACK)
      {
        
          bDIYPartialTop =nShoulderPosition - DIY_HALF_PARTIAL_DIFF_2 ;
          
          bDIYPartialBottom=WAIST_POSITION+DIY_HALF_PARTIAL_DIFF;
 
        
        
      }
      else if(bDIY_Locate==DIY_WAIST)
      {
          bDIYPartialTop =WAIST_POSITION + DIY_HALF_PARTIAL_DIFF ;
          
          bDIYPartialBottom=WAIST_POSITION-DIY_HALF_PARTIAL_DIFF_3;
        
        
        
      }
      else if(bDIY_Locate==DIY_BUTTOCKS)
      {
        
        
           bDIYPartialTop =BUTTOCKS_POSITION + DIY_HALF_PARTIAL_DIFF ;
          
          bDIYPartialBottom=BUTTOCKS_POSITION-DIY_HALF_PARTIAL_DIFF_3;
        
        
      }
      
          DIY_ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
          DIY_ManualDirector[0].nWalkMotorLocateParam =  bDIYPartialBottom;
          DIY_ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
          DIY_ManualDirector[1].nWalkMotorLocateParam =  bDIYPartialTop;        
}

//void Main_Start_DIY_Manual(void)
//{
// // DIYProgramContent
// // static  
//    unsigned char blikely,bDiyKneadKnockSpeed;
//
//   bDiyKneadKnockSpeed=DIYProgramContent&0x01;
//  
//    blikely=(DIYProgramContent&0x06)>>1;
//
//   // blikely=(blikely>>1)&0x03;//偏好
//    
//   
//  switch(blikely)	
//  {
//  case DIY_KNEAD: 
//    nBackSubRunMode = BACK_SUB_MODE_DIY;//BACK_SUB_MODE_KNEAD ;
//    if(bDiyKneadKnockSpeed == DIY_SLOW)
//    {
//      bDiyKneadKnockSpeed = SPEED_2 ;
//    }
//    else
//    {
//      bDiyKneadKnockSpeed = SPEED_4 ;
//    }
//    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
//    {
//      nKeyKneadWidth = KNEAD_WIDTH_MED ;
//    }
//    DIY_ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;
//    DIY_ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
//    DIY_ManualDirector[0].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
//    DIY_ManualDirector[0].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[0].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[0].n3D_MotorState = _3D_MANUAL;
//    
//    DIY_ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNEAD ;
//    DIY_ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
//    DIY_ManualDirector[1].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
//    DIY_ManualDirector[1].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[1].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[1].n3D_MotorState = _3D_MANUAL;
//
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKneadMotorState ;
//    nKneadMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKnockMotorState ;
//    nKnockMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = DIY_ManualDirector[nCurActionStep].nKnockMotorStopTime ;
//    nMaxActionStep = 2 ;
//    nStartActionStep = 0 ;
// //   bBackManualModeInit = TRUE ;
// //   bBackDIYManualModeInit=TRUE;
//    break;
//    
//  case DIY_KNOCK:
//    nBackSubRunMode = BACK_SUB_MODE_DIY;//BACK_SUB_MODE_KNOCK ;
//
//    if(bDiyKneadKnockSpeed == DIY_SLOW)
//    {
//      bDiyKneadKnockSpeed = SPEED_2 ;
//    }
//    else
//    {
//      bDiyKneadKnockSpeed = SPEED_4 ;
//    }  
//    
//    
//    
//    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
//    {
//      nKeyKneadWidth = KNEAD_WIDTH_MED ;
//    }
//    switch(nKeyKneadWidth)
//    {
//    case KNEAD_WIDTH_MIN:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      break ;
//    case KNEAD_WIDTH_MED:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      break ;
//    case KNEAD_WIDTH_MAX:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      break ;
//    }
//    DIY_ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNOCK ;
//    DIY_ManualDirector[0].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[0].nKnockMotorState = KNOCK_RUN_WIDTH ;
//    DIY_ManualDirector[0].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[0].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[0].n3D_MotorState = _3D_MANUAL;
//    DIY_ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNOCK ;
//    DIY_ManualDirector[1].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[1].nKnockMotorState = KNOCK_RUN_WIDTH ;
//    DIY_ManualDirector[1].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[1].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[1].n3D_MotorState = _3D_MANUAL;
//
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKneadMotorState ;
//    nKneadMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKnockMotorState ;
//    nKnockMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = DIY_ManualDirector[nCurActionStep].nKnockMotorStopTime ;
//    
//    nMaxActionStep = 2 ;
//    nStartActionStep = 0 ;
//  //  bBackManualModeInit = TRUE ;
//  //  bBackDIYManualModeInit=TRUE;
//    break;
//    
//  case DIY_WAVELET:
//
//    nBackSubRunMode = BACK_SUB_MODE_DIY;//BACK_SUB_MODE_WAVELET ;
//    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate和nKeyKneadWidth
//    if(bDiyKneadKnockSpeed == DIY_SLOW)
//    {
//      bDiyKneadKnockSpeed = SPEED_2 ;
//    }
//    else
//    {
//      bDiyKneadKnockSpeed = SPEED_4 ;
//    }  
//    
//    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
//    {
//      nKeyKneadWidth = KNEAD_WIDTH_MED ;
//    }
//    DIY_ManualDirector[0].nSubFunction = BACK_SUB_MODE_WAVELET ;
//    DIY_ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
//    DIY_ManualDirector[0].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[0].nKnockMotorState = KNOCK_RUN ;
//    DIY_ManualDirector[0].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[0].nKneadKnockSpeed =bDiyKneadKnockSpeed;// nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[0].n3D_MotorState = _3D_MANUAL;
//    DIY_ManualDirector[1].nSubFunction = BACK_SUB_MODE_WAVELET ;
//    DIY_ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
//    DIY_ManualDirector[1].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[1].nKnockMotorState = KNOCK_RUN ;
//    DIY_ManualDirector[1].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[1].nKneadKnockSpeed =bDiyKneadKnockSpeed;// nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[1].n3D_MotorState = _3D_MANUAL;
//
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKneadMotorState ;
//    nKneadMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKnockMotorState ;
//    nKnockMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = DIY_ManualDirector[nCurActionStep].nKnockMotorStopTime ;
//    
//    nMaxActionStep = 2 ;
//    nStartActionStep = 0 ;
//  //  bBackManualModeInit = TRUE ;
//  //  bBackDIYManualModeInit=TRUE;
//    break;
//    
//
//    
//  case DIY_PRESS:
//
//
//   /* if(nBackSubRunMode == BACK_SUB_MODE_DIY) 
//    {
//      //设置背部功能
//     // BackManualModeNoAction() ;
//      break ;
//    }*/
//    nBackSubRunMode = BACK_SUB_MODE_DIY;///BACK_SUB_MODE_PRESS ;
//    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
//    if(bDiyKneadKnockSpeed == DIY_SLOW)
//    {
//      bDiyKneadKnockSpeed = SPEED_2 ;
//    }
//    else
//    {
//      bDiyKneadKnockSpeed = SPEED_4 ;
//    }  
//    
//    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
//    {
//      nKeyKneadWidth = KNEAD_WIDTH_MED ;
//    }
//    switch(nKeyKneadWidth)
//    {
//    case KNEAD_WIDTH_MIN:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
//      break ;
//    case KNEAD_WIDTH_MED:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
//      break ;
//    case KNEAD_WIDTH_MAX:
//      DIY_ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      DIY_ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
//      break ;
//    }
//    DIY_ManualDirector[0].nSubFunction = BACK_SUB_MODE_PRESS ;
//    DIY_ManualDirector[0].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
//    DIY_ManualDirector[0].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[0].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[0].n3D_MotorState = _3D_MANUAL;
//    DIY_ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
//    DIY_ManualDirector[1].nKneadMotorCycles = 0 ;
//    DIY_ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
//    DIY_ManualDirector[1].nKnockMotorRunTime = 0 ;
//    DIY_ManualDirector[1].nKneadKnockSpeed = bDiyKneadKnockSpeed;//nKeyKneadKnockSpeed ;
//    DIY_ManualDirector[1].n3D_MotorState = _3D_MANUAL;
//    //设置揉捏电机
//    bKneadMotorInProcess = TRUE ;
//    nKneadMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKneadMotorState ;
//    nKneadMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKneadMotorCycles ;
//    //设置捶击电机
//    bKnockMotorInProcess = TRUE ;
//    nKnockMotorControlParam1 = DIY_ManualDirector[nCurActionStep].nKnockMotorState ;
//    nKnockMotorControlParam2 = DIY_ManualDirector[nCurActionStep].nKnockMotorRunTime ;
//    nKnockMotorControlParam3 = DIY_ManualDirector[nCurActionStep].nKnockMotorStopTime ;
//    
//    nMaxActionStep = 2 ;
//    nStartActionStep = 0 ;
////    bBackManualModeInit = TRUE ;
////    bBackDIYManualModeInit=TRUE;
//                               
//    break;
//    
//
//    
//  default:
//    //设置背部功能
//  //  BackManualModeNoAction() ;
//    break ;
//  }
//      __no_operation();
//      __no_operation();
//      __no_operation();
//      __no_operation(); 
//        __no_operation();
//      __no_operation();
//      __no_operation();
//      __no_operation();
// // walkRefreshen(nKeyBackLocate);
////  DIY_walkRefreshen(DIYProgramContent);
//  
//}









//-------------------------
//开始手动程序
void Main_Start_Manual(void)
{
    //    if(bEnableStretchDemoRun == true)//此变量是自动1快捷键的标志变量，wait_commend中按下行走向下5s后此变量孩置1
    //    {
    //        bEnableStretchDemoRun = false;
    //    }
    //    if(GetbRockEnable()== true )//在摇椅运动时，开始手动要将摇椅关掉,并将椅子回到零重力2的位置
    //    {
    //        RockFunctionEnable(false);
    //        //回到第2零重力状态
    //        SetMassagePosition(MASSAGE_OPTIMAL2_POSITION);
    //    }
    
    switch(nMaunalSubMode)	
    {
        //    case nMaunalSubMode_KNEAD: 
        //        if(nBackSubRunMode == BACK_SUB_MODE_KNEAD) 
        //        {
        //            //设置背部功能
        //            BackManualModeNoAction() ;
        //            break ;
        //        }
        //        nBackSubRunMode = BACK_SUB_MODE_KNEAD ;
        //        if(nKeyKneadKnockSpeed == SPEED_0)
        //        {
        //            nKeyKneadKnockSpeed = SPEED_2 ;
        //        }
        //        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        //        {
        //            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        //        }
        //        ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;
        //        ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
        //        ManualDirector[0].nKneadMotorCycles = 0 ;
        //        ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
        //        ManualDirector[0].nKnockMotorRunTime = 0 ;
        //        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        //        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        //        ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNEAD ;
        //        ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
        //        ManualDirector[1].nKneadMotorCycles = 0 ;
        //        ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
        //        ManualDirector[1].nKnockMotorRunTime = 0 ;
        //        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        //        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        //        ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNEAD ;
        //        ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
        //        ManualDirector[2].nKneadMotorCycles = 0 ;
        //        ManualDirector[2].nKnockMotorState = KNOCK_STOP ;
        //        ManualDirector[2].nKnockMotorRunTime = 0 ;
        //        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        //        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        //        ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNEAD ;
        //        ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
        //        ManualDirector[3].nKneadMotorCycles = 0 ;
        //        ManualDirector[3].nKnockMotorState = KNOCK_STOP ;
        //        ManualDirector[3].nKnockMotorRunTime = 0 ;
        //        ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        //        ManualDirector[3].n3D_MotorState = _3D_MANUAL;
        //        //设置揉捏电机
        //        bKneadMotorInProcess = TRUE ;
        //        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        //        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //        //设置捶击电机
        //        bKnockMotorInProcess = TRUE ;
        //        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        //        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        //        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        //        nMaxActionStep = 2 ;
        //        nStartActionStep = 0 ;
        //        bBackManualModeInit = TRUE ;
        //        break;
    case nMaunalSubMode_KNEAD: 
        if((nBackSubRunMode == BACK_SUB_MODE_KNEAD)&&(nPreKneadTurn == nKneadTurn))
        {
            BackManualModeNoAction() ;
            //nMaunalSubMode_Momery = nMaunalSubMode_NO;
            nKeyBackLocate = LOCATE_POINT;
            bManualReset = TRUE;
            nKneadTurn = 0;
            break;
        }
        nPreKneadTurn = nKneadTurn;             
        nBackSubRunMode = BACK_SUB_MODE_KNEAD ;
        if(bManualReset == TRUE)                
        {
            nKeyBackLocate = LOCATE_FULL_BACK;
            bManualReset = FALSE;
        } 
        if(nKneadTurn <= 1)//正向揉捏
        {
            // nKneadMotorControlParam1 = KNEAD_RUN ;
            ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
            ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
            ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
            ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
        }
        else//反向揉捏
        {
            //nKneadMotorControlParam1 = KNEAD_ANTIRUN ;
            ManualDirector[0].nKneadMotorState = KNEAD_ANTIRUN ;
            ManualDirector[1].nKneadMotorState = KNEAD_ANTIRUN ;
            ManualDirector[2].nKneadMotorState = KNEAD_ANTIRUN ;
            ManualDirector[3].nKneadMotorState = KNEAD_ANTIRUN ;
        }    
        
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
#ifdef US003PROGRAM
            nKeyKneadKnockSpeed = SPEED_1 ;            
#else
            nKeyKneadKnockSpeed = SPEED_1 ;          
#endif
        }
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;//记录次要状态
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[0].nKnockMotorRunTime = 0 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNEAD ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[1].nKnockMotorRunTime = 0 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNEAD ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[2].nKnockMotorRunTime = 0 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNEAD ;
        ManualDirector[3].nKneadMotorCycles = 0 ;
        ManualDirector[3].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[3].nKnockMotorRunTime = 0 ;
        ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[3].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        nMaxActionStep = 2 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        break;
        
    case nMaunalSubMode_KNOCK:
        if(nBackSubRunMode == BACK_SUB_MODE_KNOCK) 
        {
            //设置背部功能
            BackManualModeNoAction() ;
            break ;
        }
        nBackSubRunMode = BACK_SUB_MODE_KNOCK ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
            nKeyKneadKnockSpeed = SPEED_2 ;
        }
        
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        switch(nKeyKneadWidth)
        {
        case KNEAD_WIDTH_MIN:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            break ;
        case KNEAD_WIDTH_MED:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
            break ;
        case KNEAD_WIDTH_MAX:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            break ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNOCK ;
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_RUN_STOP;//KNOCK_RUN;//KNOCK_RUN_WIDTH ;
        ManualDirector[0].nKnockMotorRunTime = 1 ;
        ManualDirector[0].nKnockMotorStopTime = 4 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNOCK ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_RUN_STOP;//KNOCK_RUN;//KNOCK_RUN_WIDTH ;
        ManualDirector[1].nKnockMotorRunTime = 1 ;
        ManualDirector[1].nKnockMotorStopTime = 4 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNOCK ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_RUN_STOP;//KNOCK_RUN;//KNOCK_RUN_WIDTH ;
        ManualDirector[2].nKnockMotorRunTime = 1 ;
        ManualDirector[2].nKnockMotorStopTime = 4 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNOCK ;
        ManualDirector[3].nKneadMotorCycles = 0 ;
        ManualDirector[3].nKnockMotorState = KNOCK_RUN_STOP;//KNOCK_RUN;// KNOCK_RUN_WIDTH ;
        ManualDirector[3].nKnockMotorRunTime = 1 ;
        ManualDirector[3].nKnockMotorStopTime = 4 ;
        ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[3].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        
        nMaxActionStep = 2 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
        break;
        
    case nMaunalSubMode_WAVELET:
        if(nBackSubRunMode == BACK_SUB_MODE_WAVELET) 
        {
            //设置背部功能
            BackManualModeNoAction() ;
            break ;
        }
        nBackSubRunMode = BACK_SUB_MODE_WAVELET ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate和nKeyKneadWidth
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
            nKeyKneadKnockSpeed = SPEED_2 ;
        }
        
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_WAVELET ;
        ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_RUN ;
        ManualDirector[0].nKnockMotorRunTime = 0 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_WAVELET ;
        ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_RUN ;
        ManualDirector[1].nKnockMotorRunTime = 0 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_WAVELET ;
        ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_RUN ;
        ManualDirector[2].nKnockMotorRunTime = 0 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        ManualDirector[3].nSubFunction = BACK_SUB_MODE_WAVELET ;
        ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[3].nKneadMotorCycles = 0 ;
        ManualDirector[3].nKnockMotorState = KNOCK_RUN ;
        ManualDirector[3].nKnockMotorRunTime = 0 ;
        ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[3].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        
        nMaxActionStep = 2 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        break;
        
    case nMaunalSubMode_SOFT_KNOCK:
        if(nBackSubRunMode == BACK_SUB_MODE_SOFT_KNOCK) 
        {
            //设置背部功能
            BackManualModeNoAction() ;
            break ;
        }
        nBackSubRunMode = BACK_SUB_MODE_SOFT_KNOCK ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
            nKeyKneadKnockSpeed = SPEED_2 ;
        }
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        switch(nKeyKneadWidth)
        {
        case KNEAD_WIDTH_MIN:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            break ;
        case KNEAD_WIDTH_MED:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
            break ;
        case KNEAD_WIDTH_MAX:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            break ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_SOFT_KNOCK ;
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_RUN;//KNOCK_RUN_STOP ;
        ManualDirector[0].nKnockMotorRunTime = 1 ;
        ManualDirector[0].nKnockMotorStopTime = 4 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_SOFT_KNOCK ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_RUN;//KNOCK_RUN_STOP ;
        ManualDirector[1].nKnockMotorRunTime = 1 ;
        ManualDirector[1].nKnockMotorStopTime = 4 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_SOFT_KNOCK ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_RUN;//KNOCK_RUN_STOP ;
        ManualDirector[2].nKnockMotorRunTime = 1 ;
        ManualDirector[2].nKnockMotorStopTime = 4 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机(立即更新动作)
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机(立即更新动作)
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        
        nMaxActionStep = 2 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        break;
        
    case nMaunalSubMode_PRESS:
#ifdef _3D_MANUAL_TEST                                    
        {
            if(nBackSubRunMode == BACK_SUB_MODE_PRESS) 
            {
                //设置背部功能
                BackManualModeNoAction() ;
                break ;
            }
            nBackSubRunMode = BACK_SUB_MODE_PRESS ;
            //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
            if(nKeyKneadKnockSpeed == SPEED_0)
            {
                nKeyKneadKnockSpeed = SPEED_2 ;
            }
            
            if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
            {
                nKeyKneadWidth = KNEAD_WIDTH_MED ;
            }
            switch(nKeyKneadWidth)
            {
            case KNEAD_WIDTH_MIN:
                ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                break ;
            case KNEAD_WIDTH_MED:
                ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
                ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
                ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
                ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
                break ;
            case KNEAD_WIDTH_MAX:
                ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                break ;
            }
            ManualDirector[0].nSubFunction = BACK_SUB_MODE_PRESS ;
            ManualDirector[0].nKneadMotorCycles = 0 ;
            ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
            ManualDirector[0].nKnockMotorRunTime = 0 ;
            ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            ManualDirector[0].n3D_MotorControlState = _3D_MANUAL;
            ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
            ManualDirector[1].nKneadMotorCycles = 0 ;
            ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
            ManualDirector[1].nKnockMotorRunTime = 0 ;
            ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            ManualDirector[1].n3D_MotorControlState = _3D_MANUAL;
            
            
            //设置揉捏电机
            bKneadMotorInProcess = TRUE ;
            nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
            nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
            //设置捶击电机
            bKnockMotorInProcess = TRUE ;
            nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
            nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
            nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
            
            nMaxActionStep = 2 ;
            nStartActionStep = 0 ;
            bBackManualModeInit = TRUE ;  
        }
#else /*_3D_MANUAL_TEST    */
        if(nBackSubRunMode == BACK_SUB_MODE_PRESS) 
        {
            //设置背部功能
            BackManualModeNoAction() ;
            break ;
        }
        nBackSubRunMode = BACK_SUB_MODE_PRESS ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
            nKeyKneadKnockSpeed = SPEED_2 ;
        }
        
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        switch(nKeyKneadWidth)
        {
        case KNEAD_WIDTH_MIN:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
            break ;
        case KNEAD_WIDTH_MED:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
            break ;
        case KNEAD_WIDTH_MAX:
            ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
            break ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_PRESS ;
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[0].nKnockMotorRunTime = 0 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        
        
        //                          ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;
        //                          ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
        //                          ManualDirector[0].nKneadMotorCycles = 0 ;
        //                          ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
        //                          ManualDirector[0].nKnockMotorRunTime = 0 ;
        //                          ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        //                          ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[1].nKnockMotorRunTime = 0 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_PRESS ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_STOP ;
        ManualDirector[2].nKnockMotorRunTime = 0 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        
        nMaxActionStep = 2 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        
#endif /*_3D_MANUAL_TEST   */                                    
        break;
        
    case nMaunalSubMode_MUSIC:
        if(nBackSubRunMode == BACK_SUB_MODE_MUSIC) 
        {
            //设置背部功能
            BackManualModeNoAction() ;
            break ;
        }
        nBackSubRunMode = BACK_SUB_MODE_MUSIC ;
        //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
        if(nKeyKneadKnockSpeed == SPEED_0)
        {
            nKeyKneadKnockSpeed = SPEED_2 ;
        }
        // if((nKeyBackLocate == LOCATE_NONE) || (nKeyBackLocate == LOCATE_POINT))
        {
            //nKeyBackLocate = LOCATE_FULL_BACK ;
            
            ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
            ManualDirector[0].nWalkMotorLocateParam = 0 ;
            ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
            ManualDirector[1].nWalkMotorLocateParam = 0 ;
            ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
            ManualDirector[2].nWalkMotorLocateParam = 0 ;
            ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
            ManualDirector[3].nWalkMotorLocateParam = 0 ;
        }
        if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
        {
            nKeyKneadWidth = KNEAD_WIDTH_MED ;
        }
        ManualDirector[0].nSubFunction = BACK_SUB_MODE_MUSIC ;
        ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[0].nKneadMotorCycles = 0 ;
        ManualDirector[0].nKnockMotorState = KNOCK_RUN_MUSIC ;
        ManualDirector[0].nKnockMotorRunTime = 0 ;
        ManualDirector[0].nKnockMotorStopTime = 0 ;
        ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[0].n3D_MotorState = _3D_MANUAL;
        ManualDirector[1].nSubFunction = BACK_SUB_MODE_MUSIC ;
        ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
        ManualDirector[1].nKneadMotorCycles = 0 ;
        ManualDirector[1].nKnockMotorState = KNOCK_RUN_MUSIC ;
        ManualDirector[1].nKnockMotorRunTime = 0 ;
        ManualDirector[1].nKnockMotorStopTime = 0 ;
        ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[1].n3D_MotorState = _3D_MANUAL;
        ManualDirector[2].nSubFunction = BACK_SUB_MODE_MUSIC ;
        ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
        ManualDirector[2].nKneadMotorCycles = 0 ;
        ManualDirector[2].nKnockMotorState = KNOCK_RUN_MUSIC ;
        ManualDirector[2].nKnockMotorRunTime = 0 ;
        ManualDirector[2].nKnockMotorStopTime = 0 ;
        ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[2].n3D_MotorState = _3D_MANUAL;
        ManualDirector[3].nSubFunction = BACK_SUB_MODE_MUSIC ;
        ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
        ManualDirector[3].nKneadMotorCycles = 0 ;
        ManualDirector[3].nKnockMotorState = KNOCK_RUN_MUSIC ;
        ManualDirector[3].nKnockMotorRunTime = 0 ;
        ManualDirector[3].nKnockMotorStopTime = 0 ;
        ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
        ManualDirector[3].n3D_MotorState = _3D_MANUAL;
        //设置揉捏电机(立即更新动作)
        bKneadMotorInProcess = TRUE ;
        nKneadMotorControlParam1 = ManualDirector[nCurActionStep].nKneadMotorState ;
        nKneadMotorControlParam2 = ManualDirector[nCurActionStep].nKneadMotorCycles ;
        //设置捶击电机(立即更新动作)
        bKnockMotorInProcess = TRUE ;
        nKnockMotorControlParam1 = ManualDirector[nCurActionStep].nKnockMotorState ;
        nKnockMotorControlParam2 = ManualDirector[nCurActionStep].nKnockMotorRunTime ;
        nKnockMotorControlParam3 = ManualDirector[nCurActionStep].nKnockMotorStopTime ;
        
        nMaxActionStep = 4 ;
        nStartActionStep = 0 ;
        bBackManualModeInit = TRUE ;
        break;
        
    default:
        //设置背部功能
        BackManualModeNoAction() ;
        break ;
    }
    walkRefreshDown(nKeyBackLocate);
}


void Main_Work(void)
{
    //static uint8_t Main_Mark;
    BYTE key;
    nChairRunState_Pre=nChairRunState;
    BodyDetectStep = DETECT_INITIAL;
    
    bAutoProgramOver = false;
    Power_All_On();
    //VoiceUart_PowerOn();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Timer_Counter_Clear(C_TIMER_500MS);
    bDemoStretch = FALSE;
    unsigned int pw_Information[10];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
    //   w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
    if( (nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus) )//bRestSleepStatus是user_data内存中的第8位
    {
        //w_PresetTime = RUN_TIME_30;
        Data_Set_Start(1, RUN_TIME_30);
    }
    else
    { 
        if((nBackMainRunMode == BACK_MAIN_MODE_AUTO)&&((nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_FULL)|| \
            (nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_SHOULDER)|| \
                (nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_WAIST)|| \
                    (nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)))
        {
            w_PresetTime = RUN_TIME_5;
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
        }
        else
        {
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
        }
        
    }
    //   Data_Set_Start(1, 60*59); 
    // KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,KNEAD_SPEED3_PWM);
    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
    
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        Main_Start_Auto();
    }   
#ifdef SELECT_3D
    else if(nBackMainRunMode == BACK_MAIN_MODE_3D) //3D按摩
    {
        Main_Start_3D();
    }
#endif
    else if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL) //手动
    {
        if(bMassagePositionUpdateMemory == FALSE) bMassagePositionUpdate = false;
        Main_Start_Manual(); 
        
    }
    SingleLine_VOL = 10;
    
    //主循环
    while(CHAIR_STATE_RUN == nChairRunState) 
    {      
        //按键处理区
        key = Main_GetKey();
        key &= 0x7f;   
        
        SingleLinr_Send();
        //        
        //        if((Main_Mark==1)&(nBackSubRunMode != BACK_SUB_MODE_AUTO_1))
        //        {
        //          Main_Mark = 0;
        //          SingleLine_Send_Mode = 3;  //暂停
        //          SingleLine_Stop_Mark = 1;
        //        }
        //        else if(nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
        //        {
        //          Main_Mark=1;
        //          SingleLine_Stop_Mark = 0;
        //        }
        
        if(nBackSubRunMode != BACK_SUB_MODE_AUTO_1)
        {
            //          Main_Mark = 0;
            //          SingleLine_Send_Mode = 3;  //暂停
            SingleLine_Stop_Mark = true;
            SingleLine_Sound_ON = false;
        }
        else 
        {
            //  Main_Mark=1;
            SingleLine_Stop_Mark = false;
        }
        
        if(key!=0x7f)
        {
            __NOP();
        }
        
        //SingleLine_Analysis();
        
#ifdef back_pluse
        w_BackPosition_2 = Input_GetBackPosition();//BackMotor_Get_Position();//w_LegPosition_2
#else
        w_BackPosition_2=BackMotor_Get_Position();    
#endif
	w_LegPosition_2=LegMotor_Get_Position(); 
	
        
        switch(key)
        {
        case H10_KEY_MENU:
            break;
        case H10_KEY_MEMORYA_IN:      
            Memory_In(MEMORYA_ADDR_BASE);
            break;
        case H10_KEY_MEMORYA_OUT: 
            Memory_Out(MEMORYA_ADDR_BASE);
            //SingleLine_Play(4,1);  //暂停
            Command_Memory_Out = 1;
            Main_Start_Manual();
            break;
        case H10_KEY_MEMORYB_IN:
            Memory_In(MEMORYB_ADDR_BASE);
            break;
        case H10_KEY_MEMORYB_OUT:
            Memory_Out(MEMORYB_ADDR_BASE);
            Command_Memory_Out = 1;
            Main_Start_Manual();
            //SingleLine_Play(4,1);  //暂停
            break;
            /**********************************扶手手动控制开始*****************************/
            
        case H10_KEY_HANDRAIL_OUT_START:
            handrail_flag = 0;
            outarmcmd = H10_KEY_HANDRAIL_OUT_START;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = TRUE;
            bKeyArmPadIn = false;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_OUT_STOP:  
            outarmcmd = H10_KEY_HANDRAIL_OUT_STOP;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = false;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_IN_START:
            handrail_flag = 0;
            outarmcmd = H10_KEY_HANDRAIL_IN_START;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = true;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_IN_STOP:
            outarmcmd = H10_KEY_HANDRAIL_IN_STOP;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = false;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            /**********************************扶手手动控制结束*****************************/
            
        case H10_KEY_LANGUAGE_ENGLISH:
            bLanguageFlag = Language_English;
            *(pInformation + LANGUAGE_ADDRESS) = Language_English; 
            MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            break;
        case H10_KEY_LANGUAGE_CHINESE:
            bLanguageFlag = Language_Chinese;
            *(pInformation + LANGUAGE_ADDRESS) = Language_Chinese; 
            MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            break; 
        case H10_KEY_LANGUAGE_ELSE:
            bLanguageFlag = Language_Else;
            *(pInformation + LANGUAGE_ADDRESS) = Language_Else; 
            MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            break; 
            
            /**********************************三挡拉筋控制开始**********************/
        case H10_KEY_STRETCH_VIGOR1:
            nStretchVigor =1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_STRETCH_VIGOR2:
            nStretchVigor=2;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;          
        case H10_KEY_STRETCH_VIGOR3:
            nStretchVigor=3;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;       
            /**********************************三挡拉筋控制结束**********************/
            
            /**********************************LED灯控制开始**********************/
        case H10_KEY_LED_SWITCH:
            if(bLedFlag)
            {
                bLedFlag = 0;
            }
            else
            {
                bLedFlag = 1;
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            /**********************************LED灯控制结束**********************/
        case H10_KEY_SWAY_ONOFF:                             //0X76     
            if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)break;
            if(nBackMainRunMode == BACK_MAIN_MODE_3D)break;
            if( GetbRockEnable() == false)
            {
                RockFunctionEnable(true);
                nChairRunState = CHAIR_STATE_RUN ;
            }
            else
            {
                RockFunctionEnable(false);
            }      
            if(nKeyAirBagLocate != AIRBAG_LOCATE_AUTO)
            {
                nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;
                nChairRunState = CHAIR_STATE_RUN ;
                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                {
                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);          
                } 
                st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
                st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
                st_AirBagArmSholderBackWaist.init = TRUE;
                st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
                st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
                st_AirBagModeLegFootSeat.init = TRUE;    
                bRollerEnable = TRUE;
            }
            bZero_ShowFlag = 0;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;          
            
        case H10_KEY_TAPPING_ONOFF : 
            if(bTapping == 0)
            {
                bTapping = 1;
            }
            else
            {
                bTapping = 0;
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_MUSIC_LAST:
            if((SingleLine_Start_Mark==1)&(nBackSubRunMode == BACK_SUB_MODE_AUTO_1))
            {
                SingleLine_Play(3,0);  // 上一首
            }
            break;
            
        case H10_KEY_MUSIC_NEXT:
            if((SingleLine_Start_Mark==1)&(nBackSubRunMode == BACK_SUB_MODE_AUTO_1))
            {
                SingleLine_Play(3,0xff);  // 下一首
            }
            break;
            
        case H10_KEY_MUSIC_MINUS:
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            {
                if(SingleLine_VOL>3) SingleLine_VOL--;
                else SingleLine_VOL =3;
                SingleLine_Set_Vol(SingleLine_VOL);
            }
            break;
        case H10_KEY_MUSIC_ADD:
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            {
                if(SingleLine_VOL<30)  SingleLine_VOL++;
                SingleLine_Set_Vol(SingleLine_VOL);
            }
            break;
        case H10_KEY_BLUETOOTH_POWER_SWITCH:    
            if(bBlueToothStatus)
            {
                bBlueToothStatus = 0;
            }
            else
            {
                bBlueToothStatus = 1;
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_POWER_SWITCH: 
            {
                //按摩机构回
                //#ifdef Quick_Resetting   //按停止键快速复位
                nChairRunState = CHAIR_STATE_SETTLE ;
                bTimeoverRestSleepStatus = FALSE;
                nSettleMode = POWER_KEY_RESET;        
                SingleLine_Play(4,1);  //暂停
                RockFunctionEnable(false);
                handrail_flag = 0;//斷電扶手停止
                bKeyArmPadOut = false;
                bKeyArmPadIn = false;
                //		#else
                //			bWorkPower_Switch=1;//进入提示收藏标准
                //nChairRunState = CHAIR_STATE_SETTLE_1ST ;
                //		#endif
            }
            Zero_mark= 0;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break ;
            
            
            //        case H10_KEY_RESET_CONFIRM: 
            //            bBackLegPadSettle = TRUE ;
            //            nChairRunState = CHAIR_STATE_SETTLE ;
            //            bTimeoverRestSleepStatus = FALSE;
            //            nSettleMode = POWER_KEY_RESET;   
            //            bWorkPower_Switch=0;
            //            break;
            
            //        case H10_KEY_RESET_CANCLE :
            //            
            //            // if(nChairRunState_Pre==CHAIR_STATE_WAIT_COMMAND)
            //            {
            //                nChairRunState = CHAIR_STATE_RUN ;
            //                bWorkPower_Switch=0;
            //                
            //            }
            //            
            //            break;
            
        case H10_KEY_ANGLE_CONFIRM : 
            bAngleNoChangeProcess = TRUE;//确定要调整角度//确定要调整角度
            bAngleNoChangeCMD = FALSE;  
            if(CMDPRO == H10_KEY_ZERO_START)
            {
                
                close_auto_back_down();
                
                if(isZeroPosition())
                {
                    nTargetMassagePosition = MASSAGE_INIT_POSITION;
                }
                else
                {
                    nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
                }
                
                
                bMassagePositionUpdate = TRUE;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;
                bBlueToothSendBuzzerMode = TRUE;
                //------------------------------//按零重力键时，在三个自动程序中，靠背不会自动倒
                by_moni_cmd_tm_en = 0;	 
                //----------------------------------------
            }
            
            break;  
            
            
        case H10_KEY_ANGLE_CANCLE  :
            bAngleNoChangeProcess = FALSE;
            bAngleNoChangeCMD = FALSE; 
            //nChairRunState = CHAIR_STATE_RUN ; //CHAIR_STATE_ANGLE
            break ;                 
            
            
            
        case H10_KEY_CHAIR_AUTO_0:             //work运动恢复     
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_0)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_0 ;
            RockFunctionEnable(false);    
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto(); //设置滚轮、气囊、椅子位置的状态
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break ;
        case H10_KEY_CHAIR_AUTO_1:           //work,EXTEND
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_1) break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_1 ;
            RockFunctionEnable(false);    
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break ;
        case H10_KEY_CHAIR_AUTO_2://work,RELEX
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_2 ;
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            if(bRestSleepStatus)
            {
                Data_Set_Start(1, RUN_TIME_30);
            }
            else
            {
                if(w_PresetTime == RUN_TIME_5)
                {
                    w_PresetTime=RUN_TIME_20;
                    Data_Set_Time(w_PresetTime);
                }
                
                Data_Set_Start(1, w_PresetTime);
            }
            bZero_ShowFlag = 0;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            RockFunctionEnable(false);
            RockStartTimeFlag = TRUE;
            break ;
        case H10_KEY_CHAIR_AUTO_3:         //work,refresh
            // SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_3)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
            //nBackSubRunMode = BACK_SUB_MODE_AUTO_1;   //拉伸，舒展滚背
            nBackSubRunMode = BACK_SUB_MODE_AUTO_3 ;
            RockFunctionEnable(false);    
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break; 
        case H10_KEY_CHAIR_AUTO_4:           //work,UPPER BODY
            // SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_4)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_4 ;
            RockFunctionEnable(false);    
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break;   
        case H10_KEY_CHAIR_AUTO_5:        //work，LOWER BODY
            // SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_5)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_5;
	    RockFunctionEnable(false);    
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            Main_Start_Auto();  
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }    
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break;     
            
            
        case H10_KEY_CHAIR_AUTO_6:
            //SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_6;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            RockFunctionEnable(false);
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break; 
        case H10_KEY_CHAIR_AUTO_7:
            //SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_7)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_7;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            RockFunctionEnable(false);
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break; 
        case H10_KEY_CHAIR_AUTO_8:
            //SingleLine_Play(4,1);  //暂停
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_8)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_8;
            Main_Start_Auto(); 
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }
            st_Stretch.active = FALSE;
            st_GrowthStretch.active = false;
            RockFunctionEnable(false);
            bZero_ShowFlag = 0;
            Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;    
            break; 
            
            //       case H10_KEY_CHAIR_AUTO_EXAMINEE:
            //          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)  break;
            //          nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            //          nBackSubRunMode = BACK_SUB_MODE_AUTO_6;
            //	  
            //	  RockFunctionEnable(false);    
            //	  st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            //          Main_Start_Auto(); 
            //          
            //          
            //          if(BodyDetectStep != DETECT_FINISH)
            //          {
            //            BodyDetectStep = DETECT_INITIAL;
            //          }    
            //          
            //          //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //          //			
            //			if(w_PresetTime == RUN_TIME_5)
            //			 {
            //			   w_PresetTime=RUN_TIME_20;
            //			   Data_Set_Time(w_PresetTime);
            //			 }//w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //		  
            //          Data_Set_Start(1, w_PresetTime);
            //	  
            //
            //	
            //          nBuzzerMode = BUZZER_MODE_ONETIME ;
            //          bSendBuzzerMode = TRUE ;    
            //          break;    
            //	  
            //	  //////////////////////////////////////////////////
            //	   case H10_KEY_CHAIR_AUTO_HIGH_UP:
            //          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_7)  break;
            //          nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            //          nBackSubRunMode = BACK_SUB_MODE_AUTO_7;
            //	  
            //	  RockFunctionEnable(false);    
            //	  st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            //          Main_Start_Auto(); 
            //          
            //          
            //          if(BodyDetectStep != DETECT_FINISH)
            //          {
            //            BodyDetectStep = DETECT_INITIAL;
            //          }    
            //          
            //          //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //          //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //		  	if(w_PresetTime == RUN_TIME_5)
            //			 {
            //			   w_PresetTime=RUN_TIME_20;
            //			   Data_Set_Time(w_PresetTime);
            //			 }
            //		  
            //          Data_Set_Start(1, w_PresetTime);
            //	
            //          nBuzzerMode = BUZZER_MODE_ONETIME ;
            //          bSendBuzzerMode = TRUE ;    
            //          break;      
            //	/////////////////////////////////////////////
            //	case H10_KEY_CHAIR_AUTO_GOLFER  :
            //	  if(nBackSubRunMode == BACK_SUB_MODE_AUTO_8)  break;
            //          nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            //          nBackSubRunMode = BACK_SUB_MODE_AUTO_8;
            //	  
            //	  RockFunctionEnable(false);    
            //	  st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            //          Main_Start_Auto(); 
            //          
            //          
            //          if(BodyDetectStep != DETECT_FINISH)
            //          {
            //            BodyDetectStep = DETECT_INITIAL;
            //          }    
            //          
            //          //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //          //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //		  
            //		  	 if(w_PresetTime == RUN_TIME_5)
            //			 {
            //			   w_PresetTime=RUN_TIME_20;
            //			   Data_Set_Time(w_PresetTime);
            //			 }
            //		  
            //          Data_Set_Start(1, w_PresetTime);
            //
            //          nBuzzerMode = BUZZER_MODE_ONETIME ;
            //          bSendBuzzerMode = TRUE ;    
            //          break;        
            
            //	case H10_KEY_CHAIR_AUTO_9  ://care
            //	  if(nBackSubRunMode == BACK_SUB_MODE_AUTO_9)  break;
            //          nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            //          nBackSubRunMode = BACK_SUB_MODE_AUTO_9;
            //	  
            //	      RockFunctionEnable(false);    
            //          Main_Start_Auto(); 
            //          
            //          Wrick_Mode_Massage_Pointer_Control_Start();  
            //          if(BodyDetectStep != DETECT_FINISH)
            //          {
            //            BodyDetectStep = DETECT_INITIAL;
            //          }    
            //          
            //          //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //          //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //		  	if(w_PresetTime == RUN_TIME_5)
            //			 {
            //			   w_PresetTime=RUN_TIME_20;
            //			   Data_Set_Time(w_PresetTime);
            //			 }
            //		  
            //		  
            //          Data_Set_Start(1, w_PresetTime);
            //          nBuzzerMode = BUZZER_MODE_ONETIME ;
            //          bSendBuzzerMode = TRUE ;   
            //	  break;
            //	  
            //	case H10_KEY_CHAIR_AUTO_10://growth
            //	  
            //          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_10)  break;
            //          nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            //          nBackSubRunMode = BACK_SUB_MODE_AUTO_10;
            //	  
            //	     RockFunctionEnable(false);    
            //		 	st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            //          Main_Start_Auto(); 
            //          
            //          
            //          if(BodyDetectStep != DETECT_FINISH)
            //          {
            //            BodyDetectStep = DETECT_INITIAL;
            //          }    
            //          
            //          //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //          //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //		  	 if(w_PresetTime == RUN_TIME_5)
            //			 {
            //			   w_PresetTime=RUN_TIME_20;
            //			   Data_Set_Time(w_PresetTime);
            //			 }
            //		  
            //		  
            //		  
            //          Data_Set_Start(1, w_PresetTime);
            //          nBuzzerMode = BUZZER_MODE_ONETIME ;
            //          bSendBuzzerMode = TRUE ;   
            //	  break;
            
        case   H10_KEY_CHAIR_QUICK_FULL:
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_FULL)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_FULL;
            
            RockFunctionEnable(false);   
            st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            w_PresetTime = RUN_TIME_5;
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
            Main_Start_Auto(); 
            
            
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }    
            
            
            //    Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;  
            break;
            
        case H10_KEY_CHAIR_QUICK_SHOULDER://20160808
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_SHOULDER)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_SHOULDER;
            
            RockFunctionEnable(false);   
            st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            w_PresetTime = RUN_TIME_5;
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
            Main_Start_Auto(); 
            
            
            if(BodyDetectStep != DETECT_FINISH)
            {
                BodyDetectStep = DETECT_INITIAL;
            }    
            
            //BodyDetectStep = DETECT_FINISH;  //不进行体型检测
            //w_PresetTime = ReadEEByte(USER_DATA_BASE + DEFAULT_TIME_ADDRESS)*60; //lgt
            //   Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;  
            
            break;
            
        case H10_KEY_CHAIR_QUICK_WAIST://20160808
            
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_WAIST)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_WAIST;
            
            RockFunctionEnable(false);   
            st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            w_PresetTime = RUN_TIME_5;
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
            Main_Start_Auto(); 
            bShoulderOK = 1;
            //    Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;  
            
            
            break;
            
        case H10_KEY_CHAIR_QUICK_LEG://20160808
            
            if(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)  break;
            nBackMainRunMode = BACK_MAIN_MODE_AUTO;
            nBackSubRunMode = BACK_SUB_MODE_AUTO_QUICK_LEG;
            
            RockFunctionEnable(false);   
            st_Stretch.active = FALSE;st_GrowthStretch.active = false;
            w_PresetTime = RUN_TIME_5;
            Data_Set_Time(w_PresetTime);//add by taqisngso
            Data_Set_Start(1, w_PresetTime);
            Main_Start_Auto(); 
            bShoulderOK = 1;
            //     Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;  
            
            
            break;
            //	case  BACK_SUB_MODE_3D1: Data_Set_Start(1, RUN_TIME_10);/*w_PresetTime= RUN_TIME_10; */break;
            //   case  BACK_SUB_MODE_3D2: Data_Set_Start(1, RUN_TIME_5); /*w_PresetTime= RUN_TIME_10;*/break;
            //   case  BACK_SUB_MODE_3D3: Data_Set_Start(1, RUN_TIME_5); /*w_PresetTime= RUN_TIME_10;*/break;  	   
            
            
        case H10_KEY_3DMODE_1://work
            //SingleLine_Play(4,1);  //暂停
            Data_Set_Start(1, 10*60);
            RockFunctionEnable(false); 
            nBackSubRunMode = BACK_SUB_MODE_3D1;
            nBackMainRunMode = BACK_MAIN_MODE_3D;
            nChairRunState = CHAIR_STATE_RUN ;
            nKeyBackLocate =  LOCATE_FULL_BACK;
            /******************切换全身气囊*****************************/  
            nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;          
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
            }
            st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
            st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
            st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.init = TRUE;
            st_AirBagArmSholderBackWaist.init = TRUE;
            bRollerEnable = TRUE;
            /***********************END********************************/  
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 2;
            bZero_ShowFlag = 0;
            //st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bBackAutoModeInit = TRUE;     // 初始化自动模式
            //              nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION; // MASSAGE_OPTIMAL_POSITION; 
            //              bMassagePositionUpdate = TRUE;    // 靠背下趟开始
            break;
        case H10_KEY_3DMODE_2:
            RockFunctionEnable(false); 
            Data_Set_Start(1, RUN_TIME_5);
            // SingleLine_Play(4,1);  //暂停
            nBackSubRunMode = BACK_SUB_MODE_3D2;
            nBackMainRunMode = BACK_MAIN_MODE_3D;
            nChairRunState = CHAIR_STATE_RUN ;
            nKeyBackLocate =  LOCATE_FULL_BACK;
            bBackAutoModeInit = TRUE;     // 初始化自动模式20180806解决定点切换3D2无法切换的问题
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 1;
            bZero_ShowFlag = 0;
            bMassagePositionUpdate = TRUE;              
            //              bBackAutoModeInit = TRUE;     // 初始化自动模式
            //              nTargetMassagePosition =  MASSAGE_OPTIMAL2_POSITION;
            //              bMassagePositionUpdate = TRUE;  
            /******************切换全身气囊*****************************/  
            nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;          
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
            }
            st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
            st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
            st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.init = TRUE;
            st_AirBagArmSholderBackWaist.init = TRUE;
            bRollerEnable = TRUE;
            /***********************END********************************/ 
            
            break;  
        case H10_KEY_3DMODE_3:
            //SingleLine_Play(4,1);  //暂停
            RockFunctionEnable(false); 
            Data_Set_Start(1, RUN_TIME_5);
            nBackSubRunMode = BACK_SUB_MODE_3D3;
            nBackMainRunMode = BACK_MAIN_MODE_3D;
            nChairRunState = CHAIR_STATE_RUN ;
            nKeyBackLocate =  LOCATE_FULL_BACK;
            bBackAutoModeInit = TRUE;     // 初始化自动模式
            //                          nTargetMassagePosition =  MASSAGE_OPTIMAL2_POSITION;
            //                          bMassagePositionUpdate = TRUE;   
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 1;
            bZero_ShowFlag = 0;
            bMassagePositionUpdate = TRUE;
            /******************切换全身气囊*****************************/  
            nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;          
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
            }
            st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
            st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
            st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
            st_AirBagModeLegFootSeat.init = TRUE;
            st_AirBagArmSholderBackWaist.init = TRUE;
            bRollerEnable = TRUE;
            /***********************END********************************/ 
            
            
            break;  
        case H10_KEY_3DMODE:
            Data_Set_Start(1, RUN_TIME_5);
            nBackSubRunMode = BACK_SUB_MODE_3D1;
            nBackMainRunMode = BACK_MAIN_MODE_3D;
            bZero_ShowFlag = 0;
            nChairRunState = CHAIR_STATE_RUN ;
            break;   
        case H10_KEY_ZERO_START://零重力开始默认运行到零重力2位置
            if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;//bRestSleepStatus总是0
            if(Zero_Grade(Input_GetBackPosition())<2)
            {
                nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            }
            else
            {
                nTargetMassagePosition = MASSAGE_INIT_POSITION; 
                nZero_OK = 0;
            }
            
            Zero_mark = Zero_Grade(Input_GetBackPosition())+1;
            if(Zero_mark>=3) Zero_mark =0;
            RockFunctionEnable(false);
            st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_ZERO_1://work
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 1;
            RockFunctionEnable(false);
            st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_ZERO_2:	
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 2;
            RockFunctionEnable(false);
            st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;               
        case H10_KEY_ZERO_3:
            nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            Zero_mark = 3;
            st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_ZERO_RESET:
            if(Zero_mark ==0) break;
            Zero_mark= 0;
            RockFunctionEnable(false);
            st_Stretch.active = FALSE;
            nTargetMassagePosition = MASSAGE_INIT_POSITION; 
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;            
            
        case  H10_KEY_3D_STRENGTH:     
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))
            {
                nKeyAxisStrength++;
                nKeyAxisStrength %= 5;
                bAxisUpdate = TRUE;
                nAxisUpdateCounter = 0;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;   
            }
            break;
        case H10_KEY_WORK_TIME_10MIN:
            if( (nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus) )break;
            //if(nBackMainRunMode == BACK_MAIN_MODE_3D)break;
            w_PresetTime = RUN_TIME_10;
            Data_Update_Time(w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_WORK_TIME_20MIN:
            if( (nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus) )break;
            //if(nBackMainRunMode == BACK_MAIN_MODE_3D)break;
            w_PresetTime = RUN_TIME_20;
            Data_Update_Time(w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_WORK_TIME_30MIN:
            if( (nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus) )break;
            //if(nBackMainRunMode == BACK_MAIN_MODE_3D)break;
            w_PresetTime = RUN_TIME_30;
            Data_Update_Time(w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_AUTO://work
            if(nKeyAirBagLocate != AIRBAG_LOCATE_AUTO)
            {
                nKeyAirBagLocate = AIRBAG_LOCATE_AUTO ;
                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
                {
                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
                }
                st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
                st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist) / sizeof(struct AirBagStruct);
                st_AirBagArmSholderBackWaist.init = TRUE;
                
                st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
                st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat) / sizeof(struct AirBagStruct);
                st_AirBagModeLegFootSeat.init = TRUE;
                bRollerEnable = TRUE;
            }
            else
            {
                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
                nRollerPWM = 0;
                bRollerEnable = FALSE;
                Valve_SetRollerPWM(nRollerPWM); 
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_0);
            }
            
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            //Data_Set_Start(1, w_PresetTime);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break ;                
        case H10_KEY_AIRBAG_STRENGTH_1:
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_STRENGTH_2:
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_2);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_STRENGTH_3:
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_STRENGTH_4:
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_4);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_STRENGTH_5:
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_5);
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;  
        case H10_KEY_AIRBAG_STRENGTH_OFF:
            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            {
                nRollerPWM = 0;
                bRollerEnable = FALSE;
                Valve_SetRollerPWM(nRollerPWM);
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_0);
            }
            nKeyAirBagLocate = AIRBAG_LOCATE_NONE;
            break;    
            
        case H10_KEY_3DSPEED_1:
        case H10_KEY_3DSPEED_2:
        case H10_KEY_3DSPEED_3:
        case H10_KEY_3DSPEED_4:
        case H10_KEY_3DSPEED_5:
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))
            {
                // printf("[%d]\n",key);
                nKeyAxisStrength = key - H10_KEY_3DSPEED_1;// H10_KEY_3DSPEED_5 - key;
                nKeyAxisStrength %= 5;//0 1 2 3 4
                bAxisUpdate = TRUE;
                nAxisUpdateCounter = 0;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;   
            }
            break;
        case H10_KEY_KNEAD_CLOCK://work
        case H10_KEY_KNEAD_ANTICLOCK:
        case H10_KEY_KNEAD:
        case H10_KEY_KNOCK:
        case H10_KEY_WAVELET:
        case H10_KEY_SOFT_KNOCK:
        case H10_KEY_PRESS:
        case H10_KEY_MUSIC:             
        case H10_KEY_MANUAL:
            if((nBackMainRunMode == BACK_MAIN_MODE_AUTO)&&(nBackSubRunMode == BACK_SUB_MODE_AUTO_2))
            {
                RockFunctionEnable(false);
            }
            // SingleLine_Play(4,1);  //暂停
            if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL)
            {
                nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
                nMaunalSubMode = 5;
                nKeyBackLocate = LOCATE_FULL_BACK;//work
                //RockFunctionEnable(false); 
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            if(key == H10_KEY_MANUAL)
            { 
                //设置背部功能
                BackManualModeNoAction() ;
                
            }
            //设置气囊功能
            //设置运行时间
            
            switch(key)
            {
            case H10_KEY_KNEAD_CLOCK:
                nKneadTurn = 1;
                nMaunalSubMode = nMaunalSubMode_KNEAD;
                //                nMaunalSubMode_Momery = nMaunalSubMode;
                break;
            case H10_KEY_KNEAD_ANTICLOCK:
                nKneadTurn = 2;
                nMaunalSubMode = nMaunalSubMode_KNEAD;
                //                nMaunalSubMode_Momery = nMaunalSubMode;
                break;  
            case H10_KEY_KNEAD:       nMaunalSubMode = nMaunalSubMode_KNEAD;break;
            case H10_KEY_KNOCK:       nMaunalSubMode = nMaunalSubMode_KNOCK;break;
            case H10_KEY_WAVELET:     nMaunalSubMode = nMaunalSubMode_WAVELET;break;
            case H10_KEY_SOFT_KNOCK:  nMaunalSubMode = nMaunalSubMode_SOFT_KNOCK;break;
            case H10_KEY_PRESS:       nMaunalSubMode = nMaunalSubMode_PRESS;break;
            case H10_KEY_MUSIC:       nMaunalSubMode = nMaunalSubMode_MUSIC;break;
            case H10_KEY_MANUAL:
                nMaunalSubMode++;
                nMaunalSubMode %= 6;
                break;
            }
            Main_Start_Manual();
            
            if(w_PresetTime == RUN_TIME_5)
            {
                w_PresetTime=RUN_TIME_20;
                Data_Set_Time(w_PresetTime);
            }
            //          Data_Set_Start(1, w_PresetTime);
            
            
            break ;
        case H10_KEY_LOCATE_FULL:
        case H10_KEY_LOCATE_POINT:
        case H10_KEY_LOCATE_PART:  //新手控器为局部
            if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)// break ;
            {
                switch(key)
                {
                case H10_KEY_LOCATE_FULL:     nKeyBackLocate = LOCATE_FULL_BACK; break;
                case H10_KEY_LOCATE_PART:     nKeyBackLocate = LOCATE_PARTIAL; break;
                case H10_KEY_LOCATE_POINT:    nKeyBackLocate = LOCATE_POINT; break;
                }   
                walkRefreshDown(nKeyBackLocate);
                bBackManualModeInit = TRUE ;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;
            }
            if(nBackMainRunMode == BACK_MAIN_MODE_3D)
            {
                switch(key)
                {
                case H10_KEY_LOCATE_FULL:
                    nKeyBackLocate = LOCATE_FULL_BACK;
                    break;//work
                case H10_KEY_LOCATE_PART:
                    nKeyBackLocate = LOCATE_PARTIAL;
                    
                    //
                    if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
                    {
                        nPartialTop = TOP_POSITION ;
                        nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
                    }
                    else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
                    {
                        nPartialTop = PARTIAL_DIFF ;
                        nPartialBottom = 0 ;
                    }
                    else
                    {
                        nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
                        nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
                    }
                    if(n3Dpointturn%2==0)
                    {
                        bWalkMotorInProcess = TRUE ;
                        bUpdateLocate = TRUE ;
                        nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                        nWalkMotorControlParam2 = nPartialBottom ;
                    }
                    else
                    {
                        bWalkMotorInProcess = TRUE ;
                        bUpdateLocate = TRUE ;
                        nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                        nWalkMotorControlParam2 = nPartialTop ;
                    }
                    break;//work
                case H10_KEY_LOCATE_POINT:
                    nKeyBackLocate = LOCATE_POINT;
                    bWalkMotorInProcess = TRUE ;
                    bUpdateLocate = TRUE ;
                    nWalkMotorControlParam1 = WALK_LOCATE_PARK ;//AutoDirector.nWalkMotorLocateMethod ;
                    nWalkMotorControlParam2 = 0;//MAX_PARK_TIME ;//AutoDirector.nWalkMotorLocateParam ;
                    break;//work
                }   
                //walkRefreshen(nKeyBackLocate);
                //bBackManualModeInit = TRUE ;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ; 
                
            }
            break ;
        case H10_KEY_OZON_SWITCH:
            bOzonEnable = ~bOzonEnable;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            //        case H10_KEY_SPEED_DECREASE:
        case H10_KEY_SPEED_1:
        case H10_KEY_SPEED_2:
        case H10_KEY_SPEED_3:
        case H10_KEY_SPEED_4:
        case H10_KEY_SPEED_5:  
        case H10_KEY_SPEED_6:
            if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL) break;
            if((nBackSubRunMode == BACK_SUB_MODE_PRESS) || (nBackSubRunMode == BACK_SUB_MODE_NO_ACTION)) break ;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            if(key == H10_KEY_SPEED_1)
            {
                nKeyKneadKnockSpeed = 1;
            }
            
            if(key == H10_KEY_SPEED_2)
            {
                nKeyKneadKnockSpeed = 2;
            }
            if(key == H10_KEY_SPEED_3)
            {
                nKeyKneadKnockSpeed = 3;
            }
            if(key == H10_KEY_SPEED_4)
            {
                nKeyKneadKnockSpeed = 4;
            }
            if(key == H10_KEY_SPEED_5)
            {
                nKeyKneadKnockSpeed = 5;
            }
            if(key == H10_KEY_SPEED_6)
            {
                nKeyKneadKnockSpeed = 6;
            }
            ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
            nCurKneadKnockSpeed = nKeyKneadKnockSpeed ;    
            break ;
        case H10_KEY_WIDTH_INCREASE:
        case H10_KEY_WIDTH_DECREASE:
        case H10_KEY_WIDTH_MIN:  
        case H10_KEY_WIDTH_MED:  
        case H10_KEY_WIDTH_MAX: 
            if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL) break ;
            if(!((nBackSubRunMode == BACK_SUB_MODE_KNOCK) || (nBackSubRunMode == BACK_SUB_MODE_PRESS) || (nBackSubRunMode == BACK_SUB_MODE_SOFT_KNOCK))) break ;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            //          bKneadWidthChange = FALSE ;
            bKneadWidthChange = TRUE ;
            switch(key)
            {
            case  H10_KEY_WIDTH_INCREASE:
                {
                    if(nKeyKneadWidth < 3)
                    {
                        nKeyKneadWidth++ ;
                    }
                    else
                    {
                        nKeyKneadWidth = 1 ;
                    }
                }
                break;
            case H10_KEY_WIDTH_MIN:
                nKeyKneadWidth = KNEAD_WIDTH_MIN;
                break;
            case H10_KEY_WIDTH_MED:
                nKeyKneadWidth = KNEAD_WIDTH_MED;
                break;
            case H10_KEY_WIDTH_MAX:
                nKeyKneadWidth = KNEAD_WIDTH_MAX;
                break;
            }
            if(bKneadWidthChange == TRUE)
            {
                switch(nKeyKneadWidth)
                {
                case KNEAD_WIDTH_MIN:
                    ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                    ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MIN ;
                    break ;
                case KNEAD_WIDTH_MED:
                    ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MED ;
                    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MED ;
                    ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MED ;
                    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MED ;
                    break ;
                case KNEAD_WIDTH_MAX:
                    ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                    ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
                    break ;
                }
                ManualDirector[0].nKneadMotorCycles = 0 ;
                //重新定位
                nKneadMotorControlParam1 = ManualDirector[0].nKneadMotorState ;
                nKneadMotorControlParam2 = 0 ;
                bKneadMotorInProcess = TRUE ;
                //Knock motor 要等定位完成后进行
                bKnockMotorInProcess = TRUE ;
            }
            break ;           
        case H10_KEY_AIRBAG_LEG:     
            //            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            //            {
            //                bRollerEnable = false;
            //                nRollerPWM = 0;
            //                Valve_SetRollerPWM(nRollerPWM);
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE;             
            //            }
            //            if(nKeyAirBagLocate != AIRBAG_LOCATE_LEG_FOOT)
            //            {
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_LEG_FOOT ;
            //                st_AirBagLegFoot.init = TRUE ;
            //                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            //                {
            //                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            //                }
            //            }
            //            else
            //            {
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            //                nRollerPWM = 0;
            //                bRollerEnable = FALSE;
            //                Valve_SetRollerPWM(nRollerPWM);
            //            }
            //            if(w_PresetTime == RUN_TIME_5)
            //            {
            //                w_PresetTime=RUN_TIME_20;
            //                Data_Set_Time(w_PresetTime);
            //            }
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)//全身气囊程序
            {
                bRollerEnable = false;
                nKeyAirBagLocate  = AIRBAG_LOCATE_NONE;
            }
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            }
            switch(nKeyAirBagLocate)
            {
            case AIRBAG_LOCATE_NONE:
                nKeyAirBagLocate  = AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagLegFoot.init = TRUE ;
                break;
            case AIRBAG_LOCATE_LEG_FOOT:    
                nKeyAirBagLocate  = AIRBAG_LOCATE_NONE;
                st_AirBagLegFoot.init = FALSE ;
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_0);
                break;   
            case AIRBAG_LOCATE_ARM_SHOLDER:
                __NOP();
                nKeyAirBagLocate  |= AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagLegFoot_ArmSholder.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_SEAT:  
                __NOP();
                nKeyAirBagLocate  |= AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagLegFoot_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT: 
                __NOP();
                nKeyAirBagLocate  |= AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagLegFoot_ArmSholder_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_ARM_SHOLDER:
                __NOP();
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagArmSholder.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_SEAT: 
                __NOP();
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagSeat.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT: 
                __NOP();
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_LEG_FOOT;
                st_AirBagArmSholder_Seat.init = TRUE ;
                break;  
            }         
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_AIRBAG_ARM:
            //            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            //            {
            //                bRollerEnable = false;
            //                nRollerPWM = 0;
            //                Valve_SetRollerPWM(nRollerPWM);
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE;             
            //            }
            //
            //            if(nKeyAirBagLocate != AIRBAG_LOCATE_ARM_SHOLDER)
            //            {
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_ARM_SHOLDER ;
            //                st_AirBagArmSholder.init = TRUE ;
            //                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            //                {
            //                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            //                }
            //            }
            //            else
            //            {
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            //                nRollerPWM = 0;
            //                bRollerEnable = FALSE;
            //                Valve_SetRollerPWM(nRollerPWM);
            //            }
            //            if(w_PresetTime == RUN_TIME_5)
            //            {
            //                w_PresetTime=RUN_TIME_20;
            //                Data_Set_Time(w_PresetTime);
            //            } 
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            {
                bRollerEnable = false;
                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            }
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            }
            switch(nKeyAirBagLocate)
            {
            case AIRBAG_LOCATE_NONE:
                nKeyAirBagLocate  = AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagArmSholder.init = TRUE ;
                break;
            case AIRBAG_LOCATE_ARM_SHOLDER:
                nKeyAirBagLocate  = AIRBAG_LOCATE_NONE;
                st_AirBagArmSholder.init = FALSE ;
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_0);
                break;   
            case AIRBAG_LOCATE_LEG_FOOT:
                nKeyAirBagLocate  |= AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagLegFoot_ArmSholder.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_SEAT:  
                nKeyAirBagLocate  |= AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagArmSholder_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_SEAT: 
                nKeyAirBagLocate  |= AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagLegFoot_ArmSholder_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_LEG_FOOT:
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagLegFoot.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT: 
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagSeat.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_SEAT: 
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_ARM_SHOLDER;
                st_AirBagArmSholder_Seat.init = TRUE ;
                break;  
            }        
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_WAIST:
            //            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            //            {
            //                bRollerEnable = false;
            //                nRollerPWM = 0;
            //                Valve_SetRollerPWM(nRollerPWM);
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE;             
            //            }
            //            if(nKeyAirBagLocate == AIRBAG_LOCATE_BACK_WAIST)//AIRBAG_LOCATE_AUTO 20180327
            //            {               
            //                bRollerEnable = false;
            //                nRollerPWM = 0;
            //                Valve_SetRollerPWM(nRollerPWM);
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE;                 
            //            }
            //            else 
            //            {
            //                nKeyAirBagLocate = AIRBAG_LOCATE_BACK_WAIST ;
            //                st_AirBagBackWaist.init = TRUE ;
            //                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            //                {
            //                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            //                }
            //            }
            //            if(w_PresetTime == RUN_TIME_5)
            //            {
            //                w_PresetTime=RUN_TIME_20;
            //                Data_Set_Time(w_PresetTime);
            //            }
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_AIRBAG_BUTTOCKS:
            //            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            //            {
            //                bRollerEnable = false;
            //                nRollerPWM = 0;
            //                Valve_SetRollerPWM(nRollerPWM);
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE;             
            //            }
            //
            //             if(nKeyAirBagLocate != AIRBAG_LOCATE_SEAT)
            //             {
            //                bRollerEnable = FALSE;
            //                nKeyAirBagLocate = AIRBAG_LOCATE_SEAT ;
            //                st_AirBagSeat.init = TRUE ;
            //                if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            //                {
            //                    Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            //                }
            //            }
            //            else
            //            {
            //                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            //                nRollerPWM = 0;
            //                bRollerEnable = FALSE;
            //                Valve_SetRollerPWM(nRollerPWM);
            //            }
            //            if(w_PresetTime == RUN_TIME_5)
            //            {
            //                w_PresetTime=RUN_TIME_20;
            //                Data_Set_Time(w_PresetTime);
            //            }     
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
            {
                bRollerEnable = false;
                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            }
            if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
            {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_1);
            }
            switch(nKeyAirBagLocate)
            {
            case AIRBAG_LOCATE_NONE:
                nKeyAirBagLocate  = AIRBAG_LOCATE_SEAT;
                st_AirBagSeat.init = TRUE ;
                break;
            case AIRBAG_LOCATE_SEAT:
                st_AirBagSeat.init = false;
                nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_0);
                break;   
            case AIRBAG_LOCATE_ARM_SHOLDER:
                nKeyAirBagLocate  |= AIRBAG_LOCATE_SEAT;
                st_AirBagArmSholder_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_LEG_FOOT:  
                nKeyAirBagLocate  |= AIRBAG_LOCATE_SEAT;
                st_AirBagLegFoot_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_LEG_FOOT: 
                nKeyAirBagLocate  |= AIRBAG_LOCATE_SEAT;
                st_AirBagLegFoot_ArmSholder_Seat.init = TRUE ;
                break; 
            case AIRBAG_LOCATE_SEAT|AIRBAG_LOCATE_ARM_SHOLDER:
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_SEAT;
                st_AirBagArmSholder.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_SEAT|AIRBAG_LOCATE_LEG_FOOT: 
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_SEAT;
                st_AirBagLegFoot.init = TRUE ;
                break;  
            case AIRBAG_LOCATE_LEG_FOOT|AIRBAG_LOCATE_ARM_SHOLDER|AIRBAG_LOCATE_SEAT: 
                nKeyAirBagLocate  &= ~AIRBAG_LOCATE_SEAT;
                st_AirBagLegFoot_ArmSholder.init = TRUE ;
                break;  
            }        
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_WALK_UP_START:
            
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
            {
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                ManualDirector[0].nWalkMotorLocateParam = 0 ;
                bBackManualModeInit = TRUE ;
                bKeyWalkUp = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                //ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                //ManualDirector[0].nWalkMotorLocateParam = 0 ;
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                ManualDirector[0].nWalkMotorLocateParam = 0;      
                ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                ManualDirector[1].nWalkMotorLocateParam = 0;
                ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                ManualDirector[2].nWalkMotorLocateParam = 0;
                ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
                ManualDirector[3].nWalkMotorLocateParam = 0;            
                bBackManualModeInit = TRUE ;
                bKeyWalkUp = TRUE ;
            }
            ////////
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_POINT))
            {
                
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_TOP;//WALK_LOCATE_ABSULATE ;
                nWalkMotorControlParam2 = 0;//WALK_LOCATE_TOP ;
                bKeyWalkUp = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_TOP;//WALK_LOCATE_ABSULATE ;
                nWalkMotorControlParam2 = 0;//WALK_LOCATE_TOP ;
                bKeyWalkUp = TRUE ;
                
            }
            if(ShoulderSteps == BODY_DETECT_ADJ)
            {
                bKeyWalkUp = TRUE ;
            }
            break ;
        case H10_KEY_WALK_UP_STOP:
            bKeyWalkUp = FALSE ;
            bKeyWalkDown = FALSE ; //only pc test
            nBuzzerMode = BUZZER_MODE_OFF ;
            bSendBuzzerMode = TRUE ;
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
            {
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
                ManualDirector[0].nWalkMotorLocateParam = MAX_PARK_TIME ;
                bBackManualModeInit = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                walkRefreshUp(nKeyBackLocate);
                bBackManualModeInit = TRUE ;
            }
            /////
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_POINT))
            {
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_PARK ;//AutoDirector.nWalkMotorLocateMethod ;
                nWalkMotorControlParam2 = 0;//MAX_PARK_TIME ;//AutoDirector.nWalkMotorLocateParam ; 
                
                //WalkMotor_Control(STATE_WALK_IDLE,0);
                // nCurActionStepCounter = 0 ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
                {
                    nPartialTop = TOP_POSITION ;
                    nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
                }
                else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
                {
                    nPartialTop = PARTIAL_DIFF ;
                    nPartialBottom = 0 ;
                }
                else
                {
                    nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
                    nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
                }
                
                if(n3Dpointturn%2==0)
                {
                    bWalkMotorInProcess = TRUE ;
                    bUpdateLocate = TRUE ;
                    nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                    nWalkMotorControlParam2 = nPartialBottom ;
                }
                else
                {
                    bWalkMotorInProcess = TRUE ;
                    bUpdateLocate = TRUE ;
                    nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                    nWalkMotorControlParam2 = nPartialTop ;
                }
                
                
            }
            break ;
        case H10_KEY_WALK_DOWN_START:
            
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
            {
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                ManualDirector[0].nWalkMotorLocateParam = 0 ;
                bBackManualModeInit = TRUE ;
                bKeyWalkDown = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                //ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                //ManualDirector[0].nWalkMotorLocateParam = 0 ;
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                ManualDirector[0].nWalkMotorLocateParam = 0;      
                ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                ManualDirector[1].nWalkMotorLocateParam = 0;
                ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                ManualDirector[2].nWalkMotorLocateParam = 0;
                ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
                ManualDirector[3].nWalkMotorLocateParam = 0;       
                
                bBackManualModeInit = TRUE ;
                bKeyWalkDown = TRUE ;
            }
            
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_POINT))
            {
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                nWalkMotorControlParam2 = 0 ;
                bKeyWalkDown = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                nWalkMotorControlParam2 = 0 ;
                bKeyWalkDown = TRUE ;
            }
            if(ShoulderSteps == BODY_DETECT_ADJ)
            {
                bKeyWalkDown = TRUE ;
            }
            break ;
        case H10_KEY_WALK_DOWN_STOP:
            bKeyWalkDown = FALSE ;
            nBuzzerMode = BUZZER_MODE_OFF ;
            bSendBuzzerMode = TRUE ;
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
            {
                ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_PARK ;
                ManualDirector[0].nWalkMotorLocateParam = MAX_PARK_TIME ;
                bBackManualModeInit = TRUE ;
            }
            if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                walkRefreshDown(nKeyBackLocate);
                bBackManualModeInit = TRUE ;
            }
            ////
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_POINT))
            {
                bWalkMotorInProcess = TRUE ;
                bUpdateLocate = TRUE ;
                nWalkMotorControlParam1 = WALK_LOCATE_PARK ;//AutoDirector.nWalkMotorLocateMethod ;
                nWalkMotorControlParam2 = 0;//MAX_PARK_TIME ;//AutoDirector.nWalkMotorLocateParam ; 
            } 
            if((nBackMainRunMode == BACK_MAIN_MODE_3D)&&(nKeyBackLocate == LOCATE_PARTIAL))
            {
                if(Input_GetWalkMotorPosition() >= (TOP_POSITION - HALF_PARTIAL_DIFF))
                {
                    nPartialTop = TOP_POSITION ;
                    nPartialBottom = Input_GetWalkMotorPosition() - PARTIAL_DIFF ;
                }
                else if(Input_GetWalkMotorPosition() <= HALF_PARTIAL_DIFF)
                {
                    nPartialTop = PARTIAL_DIFF ;
                    nPartialBottom = 0 ;
                }
                else
                {
                    nPartialTop = Input_GetWalkMotorPosition() + HALF_PARTIAL_DIFF ;
                    nPartialBottom = Input_GetWalkMotorPosition() - HALF_PARTIAL_DIFF ;
                }
                if(n3Dpointturn%2==0)
                {
                    bWalkMotorInProcess = TRUE ;
                    bUpdateLocate = TRUE ;
                    nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                    nWalkMotorControlParam2 = nPartialBottom ;
                }
                else
                {
                    bWalkMotorInProcess = TRUE ;
                    bUpdateLocate = TRUE ;
                    nWalkMotorControlParam1 = WALK_LOCATE_ABSULATE ;
                    nWalkMotorControlParam2 = nPartialTop ;
                }
            }
            break ;
        case H10_KEY_BACKPAD_UP_START://work
            
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          )
            //                           
            //                           )
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_BACKPAD_UP_START;
            //                break;
            //            }  
            //    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;
            
            //if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            //      if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            RockFunctionEnable(false);
            bKeyBackPadUp = TRUE ;
            bKeyBackPadDown = FALSE ;
            //小腿联动设置
            bKeyLegPadDown = TRUE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            by_moni_cmd_tm_en = 0;	  
            bZero_ShowFlag = 0;
            
            
            break ;
        case H10_KEY_BACKPAD_UP_STOP:                          
            //st_Stretch.active = FALSE;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            //小腿联动设置
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            by_moni_cmd_tm_en = 0;	  
            
            break ;
        case H10_KEY_BACKPAD_DOWN_START:
            
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          ))
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_BACKPAD_DOWN_START;
            //                break;
            //            }
            //   if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;
            //if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            //     if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;
            RockFunctionEnable(false);
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = TRUE ;
            //小腿联动设置
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = TRUE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ; 
            by_moni_cmd_tm_en = 0;
            bZero_ShowFlag = 0;
            break ;
        case H10_KEY_BACKPAD_DOWN_STOP:
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            //小腿联动设置
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;	 
            break ;
        case H10_KEY_LEGPAD_EXTEND_START:
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          )
            //                           
            //                           )
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_LEGPAD_EXTEND_START;
            //                break;
            //            }  
            //            if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            ///  if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;
            RockFunctionEnable(false);
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = TRUE ;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;
            bZero_ShowFlag = 0;
            break;
        case H10_KEY_LEGPAD_EXTEND_STOP:
        case H10_KEY_LEGPAD_CONTRACT_STOP:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;	 
            break;
        case H10_KEY_LEGPAD_CONTRACT_START:
            
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          )
            //                           
            //                           )
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_LEGPAD_CONTRACT_START;
            //                break;
            //            }  
            
            
            //if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            //   if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;//可打断拉伸
            RockFunctionEnable(false);//可打断摇椅
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE;
            bKeyFlexIn = TRUE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            
            by_moni_cmd_tm_en = 0;
            bZero_ShowFlag = 0;
            break;
        case H10_KEY_LEGPAD_UP_START:
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          )
            //                           
            //                           )
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_LEGPAD_UP_START;
            //                break;
            //            }    
            
            
            //    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;
            
            //if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            //    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;//可打断拉伸
            RockFunctionEnable(false);//可打断摇椅
            bKeyLegPadUp = TRUE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;	 
            bZero_ShowFlag = 0;
            break ;
        case H10_KEY_LEGPAD_UP_STOP: 
            //   st_Stretch.active = FALSE;
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;	 
            
            break ;
        case H10_KEY_LEGPAD_DOWN_START:
            //            if((nChairRunState == CHAIR_STATE_RUN) 
            //               &&(bAngleNoChangeCMD == FALSE)
            //                   &&(bAngleNoChangeProcess == FALSE)
            //                       &&((nBackSubRunMode == BACK_SUB_MODE_AUTO_1)
            //                          ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)
            //                              ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_QUICK_LEG)
            //                                  ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_6)
            //                                      ||(nBackSubRunMode == BACK_SUB_MODE_AUTO_7) 
            //                                          )
            //                           
            //                           )
            //            {
            //                bAngleNoChangeCMD = TRUE ;//
            //                CMDPRO = H10_KEY_LEGPAD_UP_START;
            //                break;
            //            }  
            
            
            //    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;
            
            //if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_10))break;
            //   if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))break;
            handrail_flag = 0;
            st_Stretch.active = FALSE;//可打断拉伸
            RockFunctionEnable(false);//可打断摇椅
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = TRUE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            by_moni_cmd_tm_en = 0;	 
            bZero_ShowFlag = 0;
            break ;
        case H10_KEY_LEGPAD_DOWN_STOP://work
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            by_moni_cmd_tm_en = 0;	 
            nTargetMassagePosition = MASSAGE_ANY_POSITION;//fww
            break ;
        case H10_KEY_WHEEL_SPEED_OFF:
            bRollerEnable = FALSE;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            nRollerPWM = 0;
            Valve_SetRollerPWM(nRollerPWM);
            break;
        case H10_KEY_WHEEL_SPEED_SLOW:
        case H10_KEY_WHEEL_SPEED_MED:
        case H10_KEY_WHEEL_SPEED_FAST:
            if(bRollerEnable != FALSE)
            {
                if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO) break; //在自动气囊程序中滚速度不可以调整
            }
            if(bRollerEnable == FALSE)
            {
                bRollerEnable = TRUE;
            }
            if(key ==  H10_KEY_WHEEL_SPEED_SLOW)
            {
                nRollerPWM = 1;
            }
            if(key ==  H10_KEY_WHEEL_SPEED_MED)
            {
                nRollerPWM = 2;
            }
            if(key ==  H10_KEY_WHEEL_SPEED_FAST)
            {
                nRollerPWM = 3;
            }
            Valve_SetRollerPWM(nRollerPWM);
            if(nRollerPWM != 0)
            {
                nChairRunState = CHAIR_STATE_RUN ;
                //     Data_Set_Start(1, w_PresetTime);        
                if(Data_Get_Time() == 0)
                {
                    if(w_PresetTime == RUN_TIME_5)
                    {
                        w_PresetTime=RUN_TIME_20;
                        Data_Set_Time(w_PresetTime);
                    }
                    Data_Set_Start(1, w_PresetTime);
                }
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
        case H10_KEY_LEG_WHEEL_OFF:
            
            
            
            //bLegKneadEnable=0;
            
            //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_STOP);                                                 
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            bBlueToothSendBuzzerMode = TRUE;
            break;     
            
        case H10_KEY_LEG_WHEEL_1:
            //bLegKneadEnable=1;
            // LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_SLOW);//LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            if(Data_Get_Time() == 0)
            {              
                nChairRunState = CHAIR_STATE_RUN ;
                Data_Set_Time(w_PresetTime);
                Data_Set_Start(1, w_PresetTime);
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            break; 
            
        case H10_KEY_LEG_WHEEL_2:
            //bLegKneadEnable=1;
            // LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_MID);//LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            if(Data_Get_Time() == 0)
            {              
                nChairRunState = CHAIR_STATE_RUN ;
                Data_Set_Time(w_PresetTime);
                Data_Set_Start(1, w_PresetTime);
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            break; 
            
        case H10_KEY_LEG_WHEEL_3:
            //bLegKneadEnable=1;
            // LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            //Valve_SetLegKneadSpeed(LEG_KNEAD_SPEED_FAST);//LegKneadSpeed=LEG_KNEAD_SPEED_SLOW  ;
            if(Data_Get_Time() == 0)
            {              
                nChairRunState = CHAIR_STATE_RUN ;
                Data_Set_Time(w_PresetTime);
                Data_Set_Start(1, w_PresetTime);
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            break;    
            
        case H10_KEY_HEAT_MIN:
            
            nHeatStreng = 1;
            nHotTime = 0;	//要修改
            WaistHeat_On();	//要修改
            bKeyWaistHeat = TRUE ;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            break;	  
            
        case H10_KEY_HEAT_MED:
            nHeatStreng = 2;
            nHotTime = 0;	//要修改
            WaistHeat_On();	//要修改
            bKeyWaistHeat = TRUE ;
            
            
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            
            break;	  
            
        case H10_KEY_HEAT_MAX:
            nHeatStreng = 3;
            nHotTime = 0;	//要修改
            WaistHeat_On();	//要修改
            bKeyWaistHeat = TRUE ;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HEAT:    //加热
            
            if(WasiHeat_State())
            {
                WaistHeat_Off();
                bKeyWaistHeat = FALSE ;
            }
            else 
            {
                bKeyWaistHeat = TRUE ;
                WaistHeat_On();
            }
            nHeatStreng = 0; 
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;     
        default:       
            break;
        }
        /******************************key end *************************************************/       
        
        if(Data_Get_Time() == 0 || bAutoProgramOver)  
        { 
            RockFunctionEnable(false);   
            nRockModeEnterEnable = ExitRock;
            nChairRunState = CHAIR_STATE_SETTLE;  //按摩时间到
            nSettleMode = RUN_OVER_RESET;
            SingleLine_Delay(850);
            SingleLine_Play(0,1); //暂停
            if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))
            {
                bTimeoverRestSleepStatus = TRUE;
            }
            else
            {
                bTimeoverRestSleepStatus = FALSE;
            }
        }
        //时间处理区
        if(Timer_Counter(C_TIMER_RUN + T_LOOP,1))
        {
            if(nAxisUpdateCounter<255) nAxisUpdateCounter++;
            nCurActionStepCounter++ ;
            nCurShoulderAdjustCounter++ ;
            nCurKnockRunStopCounter++ ;
            nCur3D_MotorStopCounter++;
            //气囊记数器
            st_AirBagBackWaist.nAirBagCounter++;
            st_AirBagLegFoot.nAirBagCounter++ ;
            st_AirBagArmSholder.nAirBagCounter++ ;
            st_AirBagArm.nAirBagCounter++ ;
            st_AirBagSeat.nAirBagCounter++;
            st_AirBagModeLegFootSeat.nAirBagCounter++;
            st_AirBagArmSholderBackWaist.nAirBagCounter++;
            st_AirBagModeLegFootSeat_Growth.nAirBagCounter++;
            st_AirBagLegFoot_Seat.nAirBagCounter++;
            st_AirBagLegFoot_ArmSholder.nAirBagCounter++;
            st_AirBagArmSholder_Seat.nAirBagCounter++;
            st_AirBagLegFoot_ArmSholder_Seat.nAirBagCounter++;
            st_GrowthStretch.timer++;
            st_Stretch.timer++;
            n3DMotorRunCounter++;
            Rock_100ms_Count();
        }
        
        Input_Proce();
        Valve_Send_Data();//每10ms发送一次气阀控制数据
        Main_Send();
        Main_BlueToothSend();
        
        LED_RGB_Proce(nChairRunState);//work
        
        //        if(RockAtuoEnable&&(nBackSubRunMode == BACK_SUB_MODE_AUTO_1)&&(bShoulderOK)&&(nBackMainRunMode==BACK_MAIN_MODE_AUTO))//自动1体型检测完成并且摇摆模式开启时执行下面程序
        //        { 
        //            if((bMassagePositionUpdate==FALSE)&&(FlexAtuoEnable))
        //            {
        //                //  FlexMotorSetEnable(); //执行自动跟脚程序
        //                FlexAtuoEnable = FALSE;
        //                RockAtuoEnable = FALSE;
        //                RockFunctionEnable(true);//初始化摇摆程序
        //                nTargetMassagePosition = MASSAGE_UNKNOW_POSITION;    
        //            }
        //        }  
        
        
        
        main_GetKneadPosition();
        Data_Time_Counter_Proce();
        
        Main_Walk_Beep_Proce();
        //靠背升降电机手动处理
        Main_BackPad_Proce();
        //小腿升降电机手动处理
        Main_LegPad_Proce();
        //小腿伸缩电机手动处理
        Main_FlexPad_Proce();
        
        //扶手声音控制函数
        Main_ArmPad_Proce();
        Main_Arm_Start();
        Main_Massage_Position_Proce();//work
        FlexMotorFollowingFood();
        Main_Valve_Proce();//work
        
        Problem_Proce();
        MusicSampling();
        
        RockControl();
        //RockProcess();      //摇摆功能
        
        // Examinee_Mode_Massage_Pointer_Control_Proc();   
        // HipUp_Mode_Massage_Pointer_Control_Proc();
        // Golf_Mode_Massage_Pointer_Control_Proc();    
        // Wrick_Mode_Massage_Pointer_Control_Proc(); //care
        
        switch(nBackMainRunMode)
        {
        case  BACK_MAIN_MODE_AUTO:  
            { 
                if(bShoulderOK == 0)    
                {
                    st_RestSleep.step =0;
                    Auto_Calibration(0);  //进入主程序之前，先进行体型检测	
                }
                else
                {	
                    Main_BackProce();
                    _3DMotorControl(n3D_MotorControlState,n3D_MotorControlPosition,n3D_MotorControlSpeed,n3D_MotorControlStopTime);   
                    WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2) ;
                    KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2) ;
                    KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3) ;
                }
            }
            break;
        case  BACK_MAIN_MODE_3D:  
            {
                if(bShoulderOK == 0)    
                {
                    st_RestSleep.step =0;
                    Auto_Calibration(0);  //进入主程序之前，先进行体型检测
                }
                else
                {
                    Main_BackProce();
                    _3DMotorControl(n3D_MotorControlState,n3D_MotorControlPosition,n3D_MotorControlSpeed,n3D_MotorControlStopTime);   
                    WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2) ;
                    KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2) ;
                    KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3) ;
                }
            }
            break;  
        case  BACK_MAIN_MODE_MANUAL:  
            {
                ShoulderSteps = BODY_DETECT_PREPARE;
                Main_BackProce(); 
                _3DMotorControl(n3D_MotorControlState,n3D_MotorControlPosition,n3D_MotorControlSpeed,n3D_MotorControlStopTime);   
                WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2) ;
                KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2) ;
                KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3) ;
            }
            break;    
        default:break;
        
        }
        
        if((nBackMainRunMode == BACK_MAIN_MODE_IDLE) &&
           (nKeyAirBagLocate == AIRBAG_LOCATE_NONE) &&
               (bKeyWaistHeat == FALSE) &&
                   (bRollerEnable == FALSE)  &&
                       (bOzonEnable == FALSE))//&&bLegKneadEnable==FALSE
        {
            nChairRunState = CHAIR_STATE_WAIT_COMMAND ;
        }
        //加热处理
        
        if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE) &&
           (bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE) &&
               (bKeyWalkUp == FALSE) && (bKeyWalkDown == FALSE) &&
                   (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE)&& 
                       (bKeyArmPadOut == FALSE) && (bKeyArmPadIn == FALSE))//cyw 20180305
        {
            if((nBuzzerMode == BUZZER_MODE_FAST) ||
               (nBuzzerMode == BUZZER_MODE_SLOW))
            {
                {
                    nBuzzerMode = BUZZER_MODE_OFF ;
                    bSendBuzzerMode = TRUE ;
                }
            }
        } 
        
        
        
    } //end while
    /***************程序退出区**************************/
    if(nChairRunState == CHAIR_STATE_SETTLE)//快速停止
    {
        st_Stretch.init = false;
        bKeyBackPadUp = false;
        bKeyBackPadDown = false;
        bKeyLegPadUp = false;
        bKeyLegPadDown = false;
        bKeyFlexOut = false;
        bKeyFlexIn = false;
        st_Stretch.active = false; 
        bKeyWalkUp = false; 
        bKeyWalkDown = false; 
    }
    
    
}
void Main_Idle(void)
{
    BYTE key;
    unsigned int pw_Information[10];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(CHAIR_STATE_IDLE == nChairRunState)
    {
        if(HandUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
        //------------------------------------------------------ 云养程序区
        if(BlueToothUart_GetCtrlType()==PROGARM_CTRL)//idle
        {
            if(*(pInformation + PROGRAM_ENABLE_ADDRESS) != PROGRAM_FLAG)
            {
                *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_FLAG; //写编程标志位
                MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            }
            NVIC_SystemReset();
            return;        
        }    
        //按键处理区
        key = Main_GetKey();
        key &= 0x7f;
        if(H10_KEY_POWER_SWITCH == key)
        {
            nChairRunState = CHAIR_STATE_WAIT_COMMAND; //按了电源键后
            handrail_flag = true;//用于控制开机扶手拥抱
            arm_step=0;          //用于控制开机扶手拥抱
        }
        
        //------------------------------------------------------   

        //时间处理区
//        if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,CHAIR_STATE_IDLE))
//        {
//            IndicateLED_Toggle();
//        }
        if(Timer_Counter(C_TIMER_TEMP,30))
        {
            nChairRunState = CHAIR_STATE_SLEEP; 
        }
        Input_Proce();
        Valve_Send_Data();
        Main_Send();
        Main_BlueToothSend();
    } 
    /***************程序退出区**************************/
}

void Main_Demo(void)
{
    int demoStep = 0;
    BYTE key;
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Timer_Counter_Clear(C_TIMER_500MS);
    Data_Set_Start(1, w_PresetTime);
    
    nBackMainRunMode = BACK_MAIN_MODE_DEMO;
    nBackSubRunMode = BACK_SUB_MODE_DEMO;
    Main_Start_Auto();
    //主循环
    while(CHAIR_STATE_DEMO == nChairRunState)
    {
        //按键处理区
        key = Main_GetKey();
        switch(key)
        {
        case H10_KEY_MENU:
            break;
        case H10_KEY_POWER_SWITCH: 
            {
                nChairRunState = CHAIR_STATE_SETTLE ;
                bTimeoverRestSleepStatus = FALSE;
                nSettleMode = POWER_KEY_RESET;
                handrail_flag = 0;
                bKeyArmPadOut = false;
                bKeyArmPadIn = false;
            }
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            SingleLine_Play(4,1);  //暂停
            RockFunctionEnable(false);
            break ;
        case H10_KEY_HANDRAIL_OUT_START:
            handrail_flag = 0;
            outarmcmd = H10_KEY_HANDRAIL_OUT_START;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = TRUE;
            bKeyArmPadIn = false;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_OUT_STOP:  
            outarmcmd = H10_KEY_HANDRAIL_OUT_STOP;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = false;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_IN_START:
            handrail_flag = 0;
            outarmcmd = H10_KEY_HANDRAIL_IN_START;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = true;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_HANDRAIL_IN_STOP:
            outarmcmd = H10_KEY_HANDRAIL_IN_STOP;
            //outarmcmdmemory = outarmcmd;
            bKeyArmPadOut = false;
            bKeyArmPadIn = false;
            //            nBuzzerMode = BUZZER_MODE_ONETIME ;
            //            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_ZERO_START:
            
            //              if(isZeroPosition())
            //              {
            //                nTargetMassagePosition = MASSAGE_INIT_POSITION;
            //              }
            //              else
            //              {
            //                nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            //              }
            //              bMassagePositionUpdate = TRUE;
            //              nBuzzerMode = BUZZER_MODE_ONETIME ;
            //              bSendBuzzerMode = TRUE ;
            //              break;
            if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_2)&&(bRestSleepStatus))break;//bRestSleepStatus总是0
            if(Zero_Grade(Input_GetBackPosition())<2)
            {
                nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
            }
            else
            {
                nTargetMassagePosition = MASSAGE_INIT_POSITION; 
                nZero_OK = 0;
            }
            
            Zero_mark = Zero_Grade(Input_GetBackPosition())+1;
            if(Zero_mark>=3) Zero_mark =0;
            RockFunctionEnable(false);
            st_Stretch.active = FALSE;  // 按零重力按键 停止拉伸
            bMassagePositionUpdate = TRUE;
            bZero_ShowFlag = 1;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;
            break;
            
        case H10_KEY_WIDTH_INCREASE:
        case H10_KEY_WIDTH_DECREASE:
        case H10_KEY_WIDTH_MIN:  
        case H10_KEY_WIDTH_MED:  
        case H10_KEY_WIDTH_MAX: 
            break ;
            
        case H10_KEY_BACKPAD_UP_START:
            bKeyBackPadUp = TRUE ;
            bKeyBackPadDown = FALSE ;
            bKeyLegPadDown = TRUE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_BACKPAD_UP_STOP:
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_BACKPAD_DOWN_START:
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = TRUE ;
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = TRUE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_BACKPAD_DOWN_STOP:
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyLegPadDown = FALSE ;
            bKeyLegPadUp = FALSE ;
            bLegPadLinkage = TRUE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_LEGPAD_EXTEND_START:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = TRUE ;
            bKeyFlexIn = FALSE ;
            break;
        case H10_KEY_LEGPAD_EXTEND_STOP:
        case H10_KEY_LEGPAD_CONTRACT_STOP:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE;
            bKeyFlexIn = FALSE ;
            break;
        case H10_KEY_LEGPAD_CONTRACT_START:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE;
            bKeyFlexIn = TRUE ;
            break;
        case H10_KEY_LEGPAD_UP_START:
            bKeyLegPadUp = TRUE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_LEGPAD_UP_STOP:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_LEGPAD_DOWN_START:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = TRUE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
        case H10_KEY_LEGPAD_DOWN_STOP:
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
            bKeyFlexOut = FALSE ;
            bKeyFlexIn = FALSE ;
            break ;
            
        default:       
            break;
        }
        if((!bMassagePositionUpdate) && (!bKeyFlexIn) && (!bKeyFlexOut))
        {
            switch(demoStep)
            {
            default: 
                demoStep = 0;
            case 0: 
                if(FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlIn(FLEX_MOTOR_CURRENT_3A))
                {
                    demoStep++;
                    Timer_Counter_Clear(C_TIMER_TEMP);
                }
                break;
            case 1:
                {
                    if(Timer_Counter(C_TIMER_TEMP,15))
                    {
                        demoStep++;
                    }
                }
                break;
            case 2:
                if(FlexMotor_Control(STATE_RUN_FLEX_MANUAL_OUT, FLEX_SPEED_FAST, FLEX_CURRENT_3A))//Flex_ControlOut(FLEX_MOTOR_CURRENT_3A))
                {
                    demoStep++;
                    Timer_Counter_Clear(C_TIMER_TEMP);
                }
                break;
            case 3:
                {
                    if(Timer_Counter(C_TIMER_TEMP,15))
                    {
                        demoStep++;
                    }
                }
                break;  
            }
        }
        if(Data_Get_Time() == 0) 
        {
            Data_Set_Start(1, w_PresetTime);
        }
        //时间处理区
        if(Timer_Counter(C_TIMER_RUN + T_LOOP,1))//100ms执行一次
        {
            nCurActionStepCounter++ ;
            nCurShoulderAdjustCounter++ ;
            nCurKnockRunStopCounter++ ;
            nCur3D_MotorStopCounter++;
            //气囊记数器
            st_AirBagBackWaist.nAirBagCounter++;
            st_AirBagLegFoot.nAirBagCounter++ ;
            st_AirBagArmSholder.nAirBagCounter++ ;
            st_AirBagArm.nAirBagCounter++ ;
            st_AirBagSeat.nAirBagCounter++;
            st_AirBagModeLegFootSeat.nAirBagCounter++;
            st_AirBagArmSholderBackWaist.nAirBagCounter++;
            st_Stretch.timer++;
            n3DMotorRunCounter++;
        }
        if(Timer_Counter(C_TIMER_500MS + T_LOOP,5))
        {
            bDisplayFlash = ~bDisplayFlash ;
        }
        Input_Proce();
        Valve_Send_Data();
        Main_Send();
        Main_BlueToothSend();
        //Main_MassageSignalSend();
        LED_RGB_Proce(nChairRunState);//demo
        main_GetKneadPosition();
        Data_Time_Counter_Proce();
        
        Main_Walk_Beep_Proce();
        //靠背升降电机手动处理
        Main_BackPad_Proce();
        //小腿升降电机手动处理
        Main_LegPad_Proce();
        //小腿伸缩电机手动处理
        // Main_FlexPad_Proce();
        
        Main_Massage_Position_Proce();
        FlexMotorFollowingFood();//demo
        
        Problem_Proce();
        
        switch(nBackMainRunMode)
        {
        case  BACK_MAIN_MODE_AUTO:  
            break;
        case  BACK_MAIN_MODE_DEMO:  
            {
                Main_BackProce();
                _3DMotorControl(n3D_MotorControlState,n3D_MotorControlPosition,n3D_MotorControlSpeed,n3D_MotorControlStopTime);   
                WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2) ;
                KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2) ;
                KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3) ;
            }
            break;  
        case  BACK_MAIN_MODE_MANUAL:  
            break;    
        }
        
        Main_Valve_Proce();//demo
        if((nBackMainRunMode == BACK_MAIN_MODE_IDLE) &&
           (nKeyAirBagLocate == AIRBAG_LOCATE_NONE) &&
               (bKeyWaistHeat == FALSE) &&
                   (bRollerEnable == FALSE)  &&
                       (bOzonEnable == FALSE))
        {
            nChairRunState = CHAIR_STATE_WAIT_COMMAND ;
        }
        //加热处理
        if(bKeyWaistHeat == TRUE)
        {
            WaistHeat_On();
        }
        else
        {
            WaistHeat_Off();
        }
        
        if(bOzonEnable == TRUE)
        {
            Valve_OzonOn();
        }
        else
        {
            Valve_OzonOff();
        }
        
        if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE) &&
           (bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE) &&
               (bKeyWalkUp == FALSE) && (bKeyWalkDown == FALSE) &&
                   (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE) &&
                       (bKeyArmPadOut == FALSE) && (bKeyArmPadIn == FALSE))//cyw 20180305
        {
            if((nBuzzerMode == BUZZER_MODE_FAST) ||
               (nBuzzerMode == BUZZER_MODE_SLOW))
            {
                {
                    nBuzzerMode = BUZZER_MODE_OFF ;
                    bSendBuzzerMode = TRUE ;
                }
            }
        } 
        
        
    } //end while
    /***************程序退出区**************************/
}

void HeatProgram_temperatue(void)
{
  
  switch(nHeatStreng)
  {
     case 1://low tempratue
       
          if( (by_cur_adc_temperatue>=(nHeatStreng_tempetatue_1class-3))&& (by_cur_adc_temperatue<=(nHeatStreng_tempetatue_1class+3)))
	   {
	       WaistHeat_Off();
	  }
    
	  else   if(by_cur_adc_temperatue<(nHeatStreng_tempetatue_1class-3))
	  {
	       WaistHeat_On();
	  }
          else
          {
            WaistHeat_Off();
          }
       
      break;
    
    
     case 2://middle tempertuat
          if( (by_cur_adc_temperatue>=(nHeatStreng_tempetatue_2class-3))&& (by_cur_adc_temperatue<=(nHeatStreng_tempetatue_2class+3)))
	   {
	       WaistHeat_Off();
	  }
    
	  else if(by_cur_adc_temperatue<(nHeatStreng_tempetatue_2class-3))
	  {
	       WaistHeat_On();
	  }
          else
          {
            WaistHeat_Off();
          }
      
       break;
    
    
     case 3://high tempteruant
           if( (by_cur_adc_temperatue>=(nHeatStreng_tempetatue_3class-3))&& (by_cur_adc_temperatue<=(nHeatStreng_tempetatue_3class+3)))
	   {
	       WaistHeat_Off();
	  }
    
	  else if(by_cur_adc_temperatue<(nHeatStreng_tempetatue_3class-3))
	  {
	       WaistHeat_On();
	  }
           else
           {
                WaistHeat_Off();
           }
       
    
        break;
    
      default:
	WaistHeat_Off();
	break;
  }
}

//加热3档
void HeatProgram(void)
{
	nHotTime++;
	switch(nHeatStreng)
	{
		//1档=加热2秒, 停2秒
		case 1:
			if(nHotTime < 4)
			{
				WaistHeat_On();
			}
			else if(nHotTime < 8)
			{
				WaistHeat_Off();
			}
			else
			{
				nHotTime = 0;
				WaistHeat_On();
			}
			break;
		//2档=加热3秒, 停1秒
		case 2:
			if(nHotTime < 6)
			{
				WaistHeat_On();
			}
			else if(nHotTime < 8)
			{
				WaistHeat_Off();
			}
			else
			{
				nHotTime = 0;
				WaistHeat_On();
			}
			break;
		//3档=加热4秒, 停0秒
		case 3:
			WaistHeat_On();
			break;
		default:
			WaistHeat_Off();
			break;
	}
}

/*******************************************************
按摩椅初始化程序： 3D 马达复位

********************************************************/
void Main_Initial(void)
{
    //变量初始化区域
    //函数初始化区域
    unsigned int pw_Information[10];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(CHAIR_STATE_INITIAL == nChairRunState)
    {
        //按键处理区
        if(HandUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8);
            return;
        }
        Main_Send_Leg();
        //------------------------------------------------------ 云养程序区
        if(BlueToothUart_GetCtrlType()==PROGARM_CTRL)//initial
        {
            if(*(pInformation + PROGRAM_ENABLE_ADDRESS) != PROGRAM_FLAG)
            {
                *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_FLAG; //写编程标志位
                MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            }
            NVIC_SystemReset();
            return;     
        }    
        //------------------------------------------------------     
        //时间处理区
        if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,CHAIR_STATE_IDLE))
        {
            IndicateLED_Toggle();
        }
        Input_Proce();
        Valve_Send_Data();
        Main_Send();
        Main_BlueToothSend();
        Problem_Proce();
        nChairRunState = CHAIR_STATE_IDLE;
    } 
    /***************程序退出区**************************/
    AxisMotor_Control(STATE_AXIS_IDLE,0,_3D_SPEED_8);
}

void Main_Problem(void)
{
    BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(CHAIR_STATE_PROBLEM == nChairRunState)
    {
      //按键处理区
        key = Main_GetKey();
        if(H10_KEY_POWER_SWITCH == key)
        {
          nChairRunState = CHAIR_STATE_WAIT_COMMAND; //按了电源键后
        }
      //时间处理区
       if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,CHAIR_STATE_IDLE))
        {
          IndicateLED_Toggle();
        }
       Input_Proce();
       Valve_Send_Data();
       Main_Send();
       Main_BlueToothSend();
      //Main_MassageSignalSend();
    } //end while
   /***************程序退出区**************************/
}

void Main_MassageSignalTest(void)
{
  int indicateTime;
  Timer_Counter_Clear(C_TIMER_INDICATE);
  while(1)
  {

//    #ifdef SELECT_3D
    if(SignalBoard_isOK())
    {
      indicateTime = 10;
    }
    else
    {
      indicateTime = 2;
    } 
    if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,indicateTime))
    {
      IndicateLED_Toggle();
    }     
//#endif
  }
}

void Main_Auto_Program_Test(void)
{
  for(int j=0;j<6;j++) 
  { 
    for(int i=0;i< BACK_AUTO_STEPS[j];i++)
    {
      switch(j)
      {
      case 0: AutoDirector = AutoFunction0[i] ; break;
      case 1: AutoDirector = AutoFunction1[i] ; break;
      case 2: AutoDirector = AutoFunction2[i] ; break;
      case 3: AutoDirector = AutoFunction3[i] ; break;
      case 4: AutoDirector = AutoFunction4[i] ; break;
      case 5: AutoDirector = AutoFunction5[i] ; break;
      }
      
      switch(AutoDirector.nSubFunction)
      {
      case BACK_SUB_MODE_KNEAD:	
        {
          if((AutoDirector.nKneadMotorState == KNEAD_STOP)||(AutoDirector.nKnockMotorState != KNOCK_STOP))
          {
            printf("auto%d-KNEAD-step:[%d]\n",j,i);
          }
        }
        break;
        
      case BACK_SUB_MODE_KNOCK:			
        {
          if((AutoDirector.nKnockMotorState == KNOCK_STOP)||((AutoDirector.nKneadMotorState != KNEAD_STOP)
                                                             &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MIN)
                                                               &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MED)
                                                                 &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MAX)))
          {
            printf("auto%d-KNOCK-step:[%d]\n",j,i);
          }
        }
        break;
        
      case BACK_SUB_MODE_WAVELET:		        
        {
          if(AutoDirector.nKnockMotorState == KNOCK_STOP ||
             AutoDirector.nKneadMotorState == KNEAD_STOP )
          {
            printf("auto%d-WAVELET-step:[%d]\n",j,i);
          }
        }
        break;
      case BACK_SUB_MODE_SOFT_KNOCK:	
        {
          if((AutoDirector.nKnockMotorState != KNOCK_RUN_STOP)||((AutoDirector.nKneadMotorState != KNEAD_STOP)
                                                                 &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MIN)
                                                                   &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MED)
                                                                     &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MAX)))
          {
            printf("auto%d-SOFT_KNOCK-step:[%d]\n",j,i);
          }
        }
        break;
        
      case BACK_SUB_MODE_PRESS:			
        {
          if(AutoDirector.nKnockMotorState != KNOCK_STOP ||((AutoDirector.nKneadMotorState != KNEAD_STOP)
                                                            &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MIN)
                                                              &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MED)
                                                                &&(AutoDirector.nKneadMotorState != KNEAD_STOP_AT_MAX)))
          {
            printf("auto%d-PRESS-step:[%d]\n",j,i);
          }
        }
        break;
         case BACK_SUB_MODE_RUBBING:
        {
        if(AutoDirector.nKneadMotorState != KNEAD_RUN_RUBBING)
        {
        printf("auto%d-RUBBING-step:[%d]\n",j,i);
      }
      }
        break ;  
      case BACK_SUB_MODE_MUSIC:			
      default: 
        printf("error[%d]\n",j,0);
        break;
      }
    }
  }
  while(1);
}


#define PLANT_ADDR_BASE          ((uint32_t) 0x0001f800UL)//((uint32_t) 0x0FE00200UL)

const unsigned char AES_PlantTest1[16] = "Rongtai Health";

void AES_ECB_128bit_Encrypt(void)
{
    unsigned char AES_PlantTest2[16];
    unsigned char AES_PlantTest3[16];
    CMU_ClockEnable(cmuClock_AES, true);  
    for(unsigned char i = 0; i < 16; i++)
    {
        
        AES_PlantTest2[i] =0;    
        AES_PlantTest3[i] =0;
        
    }
    
    unsigned char g_ucKey[16] =
    {
        0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89,
        0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xF0, 0x00
    };  
    
    unsigned int PlantAddr = PLANT_ADDR_BASE;
    
    unsigned int snH = DEVINFO->UNIQUEH;
    unsigned int snL = DEVINFO->UNIQUEL;
    
    for(unsigned char i = 0; i < 16; i++)
    {    
        AES_PlantTest2[i] = ReadEEByte(PlantAddr);
        PlantAddr++;
    }
    
    g_ucKey[1] = (unsigned char)(snH >> 24);
    g_ucKey[2] = (unsigned char)(snH >> 16);
    g_ucKey[3] = (unsigned char)(snH >> 8);
    g_ucKey[4] = (unsigned char)(snH);
    
    g_ucKey[5] = (unsigned char)(snL >> 24);
    g_ucKey[6] = (unsigned char)(snL >> 16);
    g_ucKey[7] = (unsigned char)(snL >> 8);
    g_ucKey[8] = (unsigned char)(snL);
    
    //AES_ECB128(AES_PlantTest2,AES_PlantTest1,16,g_ucKey,true);
    
    AES_DecryptKey128(g_ucKey,g_ucKey);
    
    AES_ECB128(AES_PlantTest3,AES_PlantTest2,16,g_ucKey,false);
    if(strcmp(AES_PlantTest1,AES_PlantTest3) != 0)
    {
        while(1);
    }
    CMU_ClockEnable(cmuClock_AES, false);  
}

//------------------------------------云养程序区
#define CLOUD_PROGAME1_START_ADDRESS  ((uint32_t)0x16000)
#define CLOUD_PROGAME1_END_ADDRESS    ((uint32_t)0x17FFF)
#define CLOUD_PROGAME2_START_ADDRESS  ((uint32_t)0x18000)
#define CLOUD_PROGAME2_END_ADDRESS    ((uint32_t)0x19FFF)
#define CLOUD_PROGAME3_START_ADDRESS  ((uint32_t)0x1A000)
#define CLOUD_PROGAME3_END_ADDRESS    ((uint32_t)0x1BFFF)
#define CLOUD_PROGAME4_START_ADDRESS  ((uint32_t)0x1C000)
#define CLOUD_PROGAME4_END_ADDRESS    ((uint32_t)0x1DFFF)
#define LINGO_BY_BLUETOOTH    0x10
#define LINGO_EXIT_BLUETOOTH    0x11
#define CLOUD_DOWNLOAD_CMD   0x01
#define CLOUD_DELETE_CMD      0x02

void Main_Update(void)
{
 //  BuleTooth_xmodem_update();  
}

void SetMassagePosition(unsigned char position)
{
  nTargetMassagePosition = position;
  bMassagePositionUpdate = TRUE;  
}
//------------------------------------------------
extern unsigned short __checksum;
void main(void)
{
    SCB->VTOR = (uint32_t)(8 * 1024);   
    if(__checksum == 0) __checksum = 1;
    Main_Initial_IO();  //硬件初始化 
   // AES_ECB_128bit_Encrypt();
    Main_Initial_Data();  //software initial
    
    SingleLine_Rec_init();
    nChairRunState = CHAIR_STATE_INITIAL;//SLEEP;
    System_Delay_us(500000);
    SingleLine_Sound_ON = false;
    while(1)
    {
        switch(nChairRunState)
        {
        default:
        case CHAIR_STATE_INITIAL:       Main_Initial();break;  
        case CHAIR_STATE_IDLE:          Main_Idle();break;
        case CHAIR_STATE_SETTLE:        Main_Settle();break;
        case CHAIR_STATE_WAIT_COMMAND:  Main_WaitCommand();break; 
        case CHAIR_STATE_RUN:           Main_Work();break; 
        case CHAIR_STATE_PROBLEM:       Main_Problem();break;  
        case CHAIR_STATE_ENGINEERING:   Main_Engineering();break;
        case CHAIR_STATE_SLEEP:         Main_Sleep();break;
        case CHAIR_STATE_DEMO:          Main_Demo();break;
        case CHAIR_STATE_SETTLE_1ST:    Main_Settle_1ST();break; 
        // case CHAIR_STATE_UPDATE:        Main_Update();break;
        }
    }
}


void HardFault_Handler(void)
{
    while(1)
    {
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
        __no_operation();
    }
}