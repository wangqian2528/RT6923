#include "efm32.h"
#include "em_cmu.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "EFM32_def.h"
#include "EFM32_types.h"

#include <string.h>
#include <stdio.h>
#include "ControlBox.h"
#include "backaction.h"
#include "airbagaction.h"
#include "testCommand.h"

#include "system.h"
#include "ADC_Scan.h"
#include "AxisMotor.h"
#include "BackPad.h"
#include "KnockMotor_8840.h"
#include "IndicateLED.h"
#include "input.h"
#include "DMAUart.h"
#include "KneadMotor.h"
#include "LED_RGB.h"
#include "LegMotor.h"
#include "memory.h"
#include "Mp3Ctrl.h" 
#include "power.h"
#include "SlideMotor.h"
#include "Valve.h"
#include "WalkMotor.h"
#include "WaistHot.h"
#include "UartLeg.h"
#include "LegKnead_Uart.h"
#include "Data_Cul.h"
#include "timer.h"
#include "Roller_Uart.h"
#include "Flex_Uart.h"
#include "LegKnead_Uart.h"
#include "BlueTooth.h"
#include "LEUart_DMA.h"
#include "DMA_Ctrl.h"
#include "VoiceUart.h"
#include "main.h"

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
//#define bodyDetectSuccess	        GlobalFlags3.bD0
//#define bFail		                GlobalFlags3.bD1
//#define bKeyPowerSwitch 		GlobalFlags3.bD2
#define bKeyWaistHeat 			GlobalFlags3.bD3
#define bSlowDisplayFlash		GlobalFlags3.bD4
#define bKeySeatVibrate 		GlobalFlags3.bD5
#define bKeySeatEnable 			GlobalFlags3.bD6
#define bMP3RunMode	 		GlobalFlags3.bD7

//位变量
__no_init BITS GlobalFlags4 ;
#define bFastDisplayFlash 		GlobalFlags4.bD0
#define bTimer10MS 			GlobalFlags4.bD1
//#define bRunTimeChange 			GlobalFlags4.bD2
#define bWalkMotorPowerFlag 		GlobalFlags4.bD3
#define bKneadMotorPowerFlag 		GlobalFlags4.bD4
#define bKnockMotorPowerFlag 		GlobalFlags4.bD5
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
#define bVibMotorEnable 			GlobalFlags6.bD0
#define bMassagePositionUpdate 			GlobalFlags6.bD1
#define bMarkSpace				GlobalFlags6.bD2
#define bSendBuzzerMode 			GlobalFlags6.bD3
#define bSignalSendPacket 			GlobalFlags6.bD4
#define bMasterSendPacket 			GlobalFlags6.bD5 
#define bReconfigFlag 				GlobalFlags6.bD6
#define bKneadWidthChange			GlobalFlags6.bD7


__no_init BITS GlobalFlags7 ;
#define bKeyBackPadUp 				GlobalFlags7.bD0
#define bKeyBackPadDown 			GlobalFlags7.bD1
#define bOzonEnable 	                        GlobalFlags7.bD2
#define b3DMotorInProcess 	                GlobalFlags7.bD3
//#define bBackPadMotorPowerFlag		GlobalFlags7.bD4
#define bGetAirBagNextStep 			GlobalFlags7.bD5
#define bCurActionStepChange		        GlobalFlags7.bD6
#define bWalkLocateChange			GlobalFlags7.bD7

__no_init BITS GlobalFlags8 ;
#define bKeyLegPadUp 				GlobalFlags8.bD0
#define bKeyLegPadDown 				GlobalFlags8.bD1  //小腿起落电动缸落标志，在按键处理里面设置
#define bKeyFlexOut 		                GlobalFlags8.bD2
#define bKeyFlexIn 	                        GlobalFlags8.bD3
//#define bZeroPadMotorPowerFlag		GlobalFlags8.bD4
//#define bWalkMotorLocateChange 		GlobalFlags8.bD5
//#define bReachWalkUpLimitFlag		        GlobalFlags8.bD6
//#define bReachWalkDownLimitFlag		        GlobalFlags8.bD7

__no_init BITS GlobalFlags9 ;
#define bProgramMemorySet			GlobalFlags9.bD0
//#define bBodyDetectSuccess			GlobalFlags9.bD1
#define bKeyZeroUp			        GlobalFlags9.bD2
#define bGetArmAirBagNextStep 		        GlobalFlags9.bD3
#define bZeroTransition				GlobalFlags9.bD4
#define bZeroRestFlag				GlobalFlags9.bD5
#define bZeroRunFlag				GlobalFlags9.bD6
#define bGetBodyUpAirBagNextStep 	        GlobalFlags9.bD7

__no_init BITS GlobalFlags10 ;
#define bZeroRunUpFlag				GlobalFlags10.bD0
#define bZeroRunDownFlag			GlobalFlags10.bD1
#define bMP3_AD_Enable				GlobalFlags10.bD2
#define bKeyZeroDown    			GlobalFlags10.bD3
#define bBackMotorUpFlag			GlobalFlags10.bD4
#define bLegkMotorUpFlag			GlobalFlags10.bD5
#define bBlueToothMasterSendPacket		GlobalFlags10.bD6
#define bBlueToothSendBuzzerMode		GlobalFlags10.bD7
//MP3 变量

__no_init BITS GlobalFlags11 ;
//#define bKeyBackPadDownBack                     GlobalFlags11.bD0
#define bLegMotorReport				GlobalFlags11.bD1
#define bBackMotorReport			GlobalFlags11.bD2
#define bKneckCheckSwitchLast			GlobalFlags11.bD3
//#define bErrorOverFlag				GlobalFlags11.bD4
#define bRunOverFlag				GlobalFlags11.bD5
#define bDemoRun				GlobalFlags11.bD6
//#define bDemoFlag				GlobalFlags11.bD7
/******************************************************************/
#define MAX_INBUFFER_COUNT			10
#define MAX_OUTBUFFER_COUNT			20
/******************************************************************/
#define MAX_WAIT_COMMAND_TIME		120 //120*0.5s=60s=1min
/******************************************************************/
__no_init StretchStruct st_Stretch;
/******************************************************************/
__no_init unsigned char nIndicateTimer;
/******************************************************************/
__no_init unsigned char nBuzzerMode;
/******************************************************************/
__no_init unsigned char nChairStateCount ;//Wait_command记时
/******************************************************************/
__no_init unsigned char nBackMainRunMode,nBackSubRunMode ;
__no_init unsigned char nCurSubFunction ;        
__no_init unsigned char nCurKneadKnockSpeed ; 
/******************************************************************/
__no_init unsigned char nBackSettleStep ;
__no_init unsigned char nBackSettleReason ;
/******************************************************************/
__no_init unsigned int nCurActionStep ;
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
       
unsigned short nLegAngle;
unsigned char nFlexStatus;
unsigned char nLegReady;

unsigned int topPositionRefreshedFlag;
int shoulderPos[3];

//与通信相关的变量
//两种类型的数据包，命令包和状态包，命令包需要应答，状态包无需应答
__no_init unsigned char OutBuffer[MAX_OUTBUFFER_COUNT] ;
__no_init unsigned char OutBufferBlueTooth[MAX_OUTBUFFER_COUNT] ;
//__no_init unsigned char bMasterSendPacketWL;//140410
__no_init unsigned char InBuffer[MAX_INBUFFER_COUNT] ;
__no_init unsigned char nInBufferCount ;
__no_init unsigned char nOutBufferCount ;
__no_init unsigned char nOutBufferBlueToothCount;
__no_init unsigned char nSendCount ;
//__no_init unsigned char nCommandID ;
__no_init unsigned char nSendPacketID ;

__no_init unsigned char OutLegBuffer[MAX_OUTBUFFER_COUNT] ;
__no_init unsigned char InLegBuffer[MAX_INBUFFER_COUNT] ;
__no_init unsigned char nOutLegBufferCount;

__no_init unsigned char _3D_Mode_Step;

bool bMasterSendLegPacket;

unsigned int sysTimer;

bool bRollerEnable,bLegKneadEnable;
__no_init unsigned char nRollerPWM;

bool bFlexEnable;

unsigned char nFlexMode;
#define FLEX_AUTO   1
#define FLEX_MANUAL 0

unsigned char nFlexDirection;
#define FLEX_IN    0
#define FLEX_OUT   1
unsigned char nLegAirBagMode;
#define LEG_AIRBAG_MODE1  0x14
#define LEG_AIRBAG_MODE2  0x15
#define LEG_AIRBAG_MODE3  0x16

unsigned char nLegAirBagStrength;
#define LEG_AIRBAG_OFF     0x17
#define LEG_AIRBAG_WEAK    0x18
#define LEG_AIRBAG_MIDDLE  0x19
#define LEG_AIRBAG_STRONG  0x1a

bool bLegModulePower;

bool bLegHeat;
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
// nAxisStrength:总强度  
unsigned char  nAxisStrength,nAxisStrengthBase/*,nAxisAuto,nAxisMode*/; 
unsigned int nWidthOverTime;
unsigned int nPowerOverTime;
unsigned int nWalkOverTime;
unsigned int nBackOverTime;
unsigned int nLegOverTime;
unsigned int nZeroOverTime;
unsigned int nWaveOverTime;
unsigned int nFlexOverTime;

unsigned int w_KeyWalkHoldTimer;
/******************************************************************/
__no_init unsigned char nBackLegPadFlashCount ;  //没有具体的使用
/******************************************************************/
__no_init unsigned short nFinalWalkMotorLocate ;
/******************************************************************/
__no_init unsigned char nCurActionStepCounter;       //当前步骤时间计数器(适用于所有行走，揉捏，敲打电机)
__no_init unsigned char nCurKnockRunStopCounter;   
__no_init unsigned char nCurShoulderAdjustCounter ;
/******************************************************************/
unsigned char nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
__no_init unsigned char nCurKneadMotorCycles ;

unsigned char nCurKneadMotorState,nPrevKneadMotorState,nFinalKneadMotorState ;
unsigned char nCurKneadMotorStateCounter ;
/******************************************************************/
__no_init unsigned char nWalkMotorControlParam1;
__no_init unsigned short nWalkMotorControlParam2 ;
__no_init unsigned char nKneadMotorControlParam1,nKneadMotorControlParam2 ;
__no_init unsigned char nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3 ;
__no_init unsigned char n3DMotorControlParam1,n3DMotorControlParam2;

/******************************************************************/
__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoDirector;
__no_init WALK_KNEAD_KNOCK_MOTOR_STRUCT_MANUAL ManualDirector[4] ;

__no_init st_AirBag /*st_AirBagAuto,*/st_AirBagArmSholderBackWaist, st_AirBagModeLegFootSeat, st_AirBagLegFoot, st_AirBagArmSholder, st_AirBagBackWaist, st_AirBagSeat, st_AirBagArm;

/******************************************************************/
#define AUTO_FUNCTION_0_STEPS	sizeof(AutoFunction0)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_1_STEPS	sizeof(AutoFunction1)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_2_STEPS	sizeof(AutoFunction2)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_3_STEPS	sizeof(AutoFunction3)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_4_STEPS	sizeof(AutoFunction4)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)
#define AUTO_FUNCTION_5_STEPS	sizeof(AutoFunction5)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)

//自动程序步骤总数
const unsigned int BACK_AUTO_STEPS[] =
{
	AUTO_FUNCTION_0_STEPS,
	AUTO_FUNCTION_1_STEPS,
	AUTO_FUNCTION_2_STEPS,
	AUTO_FUNCTION_3_STEPS,
	AUTO_FUNCTION_4_STEPS,
	AUTO_FUNCTION_5_STEPS,
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
} ;
/******************************************************************/
__no_init unsigned char nDetectStep,nStretchStep;
/******************************************************************/
//unsigned int shoulderPositionScanStep;
/******************************************************************/
__no_init unsigned char nTimer100MS ;
__no_init unsigned char nTimer500MS ;
/******************************************************************/
__no_init unsigned short nPartialTop,nPartialBottom ;
/******************************************************************/
bool bKeyAxisForward,bKeyAxisBehind,bAxisUpdate,bAxisAutoUpdate;
/******************************************************************/

//函数声明
void BodyDataRefresh(void);
void Main_Initial_Data(void);

void Main_Initial_IO(void)
{
    __disable_irq();
    System_Initial_IO();
    Power_Initial_IO();
    IndicateLED_Initial_IO();
    KneadMotor_Initial_IO();
    UART0_Initial_IO();
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
    //LEUart_Initial_IO();
    LEUART0_Initial_IO();
    UART1_Initial_IO();
    __enable_irq();
   
}

unsigned int nAvrADResult0 ;
unsigned int nMusicKnockPWM ;//用于音乐互动
void MusicSampling(void)
{
    unsigned short adcAudio_L,adcAudio_R;
    if(ADC_Get_ADC(ADC_AUDIO_L,&adcAudio_L) < 1) return;
    if(ADC_Get_ADC(ADC_AUDIO_R,&adcAudio_R) < 1) return;
    
    if(adcAudio_L >= adcAudio_R)
    {
        nAvrADResult0 = adcAudio_L - adcAudio_R  ;
    }
    else
    {
        nAvrADResult0 = adcAudio_R - adcAudio_L  ;
    } 
}

#define		ADSTRONG1  10
#define		ADSTRONG2  30
#define		ADSTRONG3  50
#define		ADSTRONG4  100
#define		ADSTRONG5  150
#define		ADSTRONG6  200

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

//捶击电机控制
void KnockMotorControl(unsigned char nKnockMotorState,unsigned char nKnockingMotorRunTime,unsigned char nKnockingMotorStopTime)
{
   if(nBackSubRunMode == BACK_SUB_MODE_3D1 ||
    nBackSubRunMode == BACK_SUB_MODE_3D2 ||
      nBackSubRunMode == BACK_SUB_MODE_3D3)
  {
    bKnockMotorInProcess = false;
    return;
  }

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
                while(1)
                {
                    //WDOG_Feed();
                }
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
                        
                        if(bWalkMotorInProcess == FALSE)
                        {
                            bKnockMotorInProcess = FALSE ;
                        }
                        
                    }
                    if(nCurKnockRunStopCounter >= (nKnockingMotorRunTime + nKnockingMotorStopTime))
                    {
                        nCurKnockRunStopCounter = 0 ;
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

void main_GetKneadPosition(void)
{            
    static unsigned char nLastKneadPosition = KNEAD_WIDTH_UNKNOWN ;
    unsigned char nNowKneadPosition = Input_GetKneadPosition();
    if(nNowKneadPosition != nLastKneadPosition) 
    {
        nWidthOverTime = 0;
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
void KneadMotorControl(unsigned char nKneadMotorState,unsigned char nKneadMotorCycles)
{
  if(nBackSubRunMode == BACK_SUB_MODE_3D1 ||
    nBackSubRunMode == BACK_SUB_MODE_3D2 ||
      nBackSubRunMode == BACK_SUB_MODE_3D3)
  {
    bKneadMotorInProcess = false;
    return;
  }
    unsigned int speed;
    unsigned int step;
    if(bKneadMotorInProcess == TRUE)
    {
        switch(nKneadMotorState)
        {
        default:
        case KNEAD_STOP:
            nFinalKneadMotorState = STATE_IDLE ;
            bKneadMotorInProcess = FALSE ;
            break ;
        case KNEAD_STOP_AT_MIN:
            if(nCurKneadWidth == KNEAD_WIDTH_MIN)
            {
                nFinalKneadMotorState = STATE_IDLE ;
                bKneadMotorInProcess = FALSE ;
            }
            else
            {
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    if(Input_GetKneadMin() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                }
            }
            break ;
        case KNEAD_STOP_AT_MED:
            if(nCurKneadWidth == KNEAD_WIDTH_MED)
            {
                nFinalKneadMotorState = STATE_IDLE ;
                bKneadMotorInProcess = FALSE ;
            }
            else
            {
                if(bHasKneadWidthMedPulse == TRUE)
                {
                    bHasKneadWidthMedPulse = FALSE ;
                    if(Input_GetKneadMid() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                }
            }
            break ;
        case KNEAD_STOP_AT_MAX:
            if(nCurKneadWidth == KNEAD_WIDTH_MAX)
            {
                nFinalKneadMotorState = STATE_IDLE ;
                bKneadMotorInProcess = FALSE ;
            }
            else
            {
                if(bHasKneadWidthMaxPulse == TRUE)
                {
                    bHasKneadWidthMaxPulse = FALSE ;
                    if(Input_GetKneadMax() == 0)
                    {
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_CLOCK ;
                }
            }
            break ;
        case KNEAD_RUN:
            nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
            nFinalKneadMotorState = STATE_RUN_CLOCK ;
            bKneadMotorInProcess = FALSE ;
            break ;
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
                        nCurKneadWidth = KNEAD_WIDTH_MIN ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
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
                        nCurKneadWidth = KNEAD_WIDTH_MED ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
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
                        nCurKneadWidth = KNEAD_WIDTH_MAX ;
                        nFinalKneadMotorState = STATE_IDLE ;
                        bKneadMotorInProcess = FALSE ;
                    }
                }
            }
            else
            {
                nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                nFinalKneadMotorState = STATE_RUN_CLOCK ;
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
            case 0: 
                /**************判断是否到达最窄处*************************/
                if(bHasKneadWidthMinPulse == TRUE)
                {
                    bHasKneadWidthMinPulse = FALSE ;
                    nCurKneadWidth = KNEAD_WIDTH_MIN ;
                    nCurKneadMotorCycles++ ;       //到达窄位置加1
                    Timer_Counter_Clear(C_TIME_RUBBING); 
                    nFinalKneadMotorState = STATE_IDLE ;
                }
                else
                {
                    nCurKneadWidth = KNEAD_WIDTH_UNKNOWN ;
                    nFinalKneadMotorState = STATE_RUN_UNCLOCK ; //还未到达最窄处，继续逆时针转动
                }
                /*********************************************/
                break; 
            case 1:  //停在最窄处
                /**************判断刹车时间************************/
                if(Timer_Counter(C_TIME_RUBBING,1)) 
                {
                    nCurKneadMotorCycles++ ;       //加1
                    nFinalKneadMotorState = STATE_RUN_CLOCK ; //从最窄到最宽，进行顺时针运动
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
        }
    }
    if(nFinalKneadMotorState == STATE_RUN_CLOCK)
    {
        KneadMotor_Control(STATE_KNEAD_CLOCK_RUN,speed);
    }
    if(nFinalKneadMotorState == STATE_RUN_UNCLOCK)
    {
        KneadMotor_Control(STATE_KNEAD_UNCLOCK_RUN,speed);
    }
    if(nFinalKneadMotorState == STATE_IDLE)
    {
        KneadMotor_Control(STATE_KNEAD_IDLE,speed);
    }
}

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
            break;
        case WALK_LOCATE_ABSULATE:    //运行到绝对位置
            nFinalWalkMotorLocate = nWalkMotorLocateParam ; 
            break ;
        case WALK_LOCATE_SHOULDER:    //运行到肩膀位置
            if(by_TopPosition - nWalkMotorLocateParam > nShoulderPosition)
            {
                nFinalWalkMotorLocate = nShoulderPosition + nWalkMotorLocateParam ;
            }
            else
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            break ;
        case WALK_LOCATE_TOP:  //运行到上端行程
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
            break ;
        case WALK_LOCATE_PARK: //停留在当前位置
            WalkMotor_Control(STATE_WALK_IDLE,0);
            nCurActionStepCounter = 0 ;
            break ;
            
        case WALK_LOCATE_NeckSwitch:
            nFinalWalkMotorLocate = by_TopPosition ;
            break;
            
        case WALK_LOCATE_NeckMed: //脖子位置
            if(nShoulderPosition >= by_TopPosition - Med_NECK_LENGTH)
            {
                nFinalWalkMotorLocate = by_TopPosition ;
            }
            else
            {
                nFinalWalkMotorLocate = nShoulderPosition + Med_NECK_LENGTH ;
            }
            
            break;
        case WALK_LOCATE_PressNeck: //肩膀位置
            nFinalWalkMotorLocate = nShoulderPosition;	// - 10 ;
            break;
        }//end switch
        //保证不超过最高位
        if(nFinalWalkMotorLocate > by_TopPosition)
            nFinalWalkMotorLocate = by_TopPosition;   
    }//end if
    
    //以下判断 walk 行程（bWalkMotorInProcess）何时停止 
    
    if(nWalkMotorLocateMethod == WALK_LOCATE_PARK)
    { //判断是否到达停留时间
        WalkMotor_Control(STATE_WALK_IDLE,0);
        if((nWalkMotorLocateParam != MAX_PARK_TIME) && 
           (nCurActionStepCounter >= nWalkMotorLocateParam))
        {
            bWalkMotorInProcess = FALSE ;
        }
    }
    else
    {
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
        {   //行程最终位置为任意位置
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nFinalWalkMotorLocate))
            {
                bWalkMotorInProcess = FALSE ;
            }
        }
    }
    return 0;
}

void refreshAutoDirector(void)
{
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
   // nAxisStrength = AutoDirector.nAxisMotorPosition ;
    bAxisUpdate = 1;
}
void Main_BackProce(void)
{        
    switch(nBackMainRunMode)
    {
    case BACK_MAIN_MODE_AUTO:
        if(bBackAutoModeInit == TRUE)
        {
            bBackAutoModeInit = FALSE;
            nMaxActionStep = BACK_AUTO_STEPS[nBackSubRunMode];
            nStartActionStep = BACK_AUTO_START_STEP[nBackSubRunMode];
            bGetNextActionStep = TRUE;
            nCurActionStep = 0;
            nDetectStep = 0;
            nStretchStep = 0;
            //如果不等当前的动作完成，而强行将InProcess置成FALSE，会造成冲顶
        }
        else
        {
            if((bWalkMotorInProcess == FALSE) &&
                    (bKneadMotorInProcess == FALSE) &&
                    (bKnockMotorInProcess == FALSE))
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
            /*
            if(nReworkShoulderPosition == 2 && nBackSubRunMode != BACK_SUB_MODE_AUTO_5)   //开始检测
            {
                //初始化检测参数检测      
                if(nDetectStep == 0) startBodyDetect();
                AutoDirector = AutoFunctionDetect[nDetectStep] ;
                nDetectStep++;
                if(nDetectStep >= (sizeof(AutoFunctionDetect)/sizeof(struct Walk_Knead_Knock_Motor_Struct_Auto)))
                {
                    nDetectStep = 0;
                    nReworkShoulderPosition = 0;
                }
            }
            else 
            */
            if(st_Stretch.active)
            {
                AutoDirector = AutoFunctionStretch[nStretchStep] ;
            }
            else
            {
                //do
                {
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
                        break ;
                    }
                    /*
                    if(((AutoDirector.nSubFunction == BACK_SUB_MODE_BODY_DETECT_0) ||
                        (AutoDirector.nSubFunction == BACK_SUB_MODE_BODY_DETECT_1)) &&
                        (bBodyDetectSuccess == TRUE)) //跳过肩膀位置检测程序
                    {
                        nCurActionStep++ ;
                        if(nCurActionStep >= nMaxActionStep)
                        {
                            nCurActionStep = nStartActionStep ;
                        }
                    }
                    else
                    {
                        break ;
                    }
                    */
                }/*while(TRUE) ;*/
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
            nCurActionStep = 0 ;
        }
        else
        {
            if((bWalkMotorInProcess == FALSE) &&
               (bKneadMotorInProcess == FALSE) &&
                 (bKnockMotorInProcess == FALSE)); 
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
           /*
            //设置3D电机
            if(nBackSubRunMode == BACK_SUB_MODE_3D1 ||
                nBackSubRunMode == BACK_SUB_MODE_3D2 ||
                  nBackSubRunMode == BACK_SUB_MODE_3D3)
            {
              b3DMotorInProcess = TRUE;
              n3DMotorControlParam1 = ManualDirector[nCurActionStep]._3D_Position;
              n3DMotorControlParam2 = ManualDirector[nCurActionStep]._3D_Speed;
            }
           else
            {
              b3DMotorInProcess = FALSE;
            }
            */
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
      if((nFlexStatus&0x03) ==  FLEX_AT_OUT || (nLegAngle > 320))
      {
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
       // bBlueToothSendBuzzerMode = TRUE;
        retval = 1; 
      }
      else      
      {
        Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
        Flex_SetDirection(FLEX_TO_OUT);
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
       // bBlueToothSendBuzzerMode = TRUE;
      }
    }
    if(bKeyFlexIn == TRUE)
    {
      if((nFlexStatus&0x03) ==  FLEX_AT_IN)
      {
        nBuzzerMode = BUZZER_MODE_FAST ;
        bSendBuzzerMode = TRUE ;
      //  bBlueToothSendBuzzerMode = TRUE;
        retval = 1; 
      }
      else      
      {
        Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
        Flex_SetDirection(FLEX_TO_IN);
        nBuzzerMode = BUZZER_MODE_SLOW ;
        bSendBuzzerMode = TRUE ;
      //  bBlueToothSendBuzzerMode = TRUE;
      }
    }
    if((bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE))
    {
        Flex_SetDirection(FLEX_MOTOR_STOP);
        retval = 0;
    }
    return retval;
}



//小腿起落电动缸控制程序
void Main_LegPad_Proce(void)
{   
    LegMotor_Proce();
    //if(st_Stretch.active) return;  //如果拉退程序有效，退出
    if(bMassagePositionUpdate) return; //在强制设置按摩位置时也会进行小腿处理，故当强制设置按摩位置时不执行此函数内容
    if(bLegPadLinkage == FALSE) //小腿单独动，此时不考虑前滑电动缸的位置
    {
        if(bKeyLegPadUp == TRUE)
        {
            FlexMotorSetEnable();
            if(LegMotor_Control(STATE_RUN_LEG_UP) != LEG_RUN)
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
                
                //FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_3A);
                
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

void Main_Valve_Proce(void)
{
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        Valve_SetBackMode(1);
    }
    else
    {
        Valve_SetBackMode(0);
    }

    unsigned char by_EngineeringAirBag = ReadEEByte(AIRBAG_STRETCH_ADDRESS + USER_DATA_BASE);

    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        if((Data_Get_ProgramExecTime() > VALVE_START_TIME) || !bMassagePositionUpdate )  //判断气阀开始时间是否到达
        {
            goto VALVE_START;  //如果按摩椅已经到达最佳位置
        }
//    Valve_Control(VALVE_DISABLE,&st_AirBagAuto,by_EngineeringAirBag);

        Valve_Control(VALVE_DISABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
        Valve_Control(VALVE_DISABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);

        Valve_BodyUpAirPumpACPowerOff();
        Valve_LegFootAirPumpACPowerOff();
        Valve_FootRollerProce(0, 0, &st_AirBagModeLegFootSeat);
        Valve_LegKneadProce(0, 0, &st_AirBagModeLegFootSeat);
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
    }

    if(nKeyAirBagLocate == AIRBAG_LOCATE_AUTO)
    {
        if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && ( nBackSubRunMode == BACK_SUB_MODE_AUTO_1))
        {
         
           /*
            bool us047_enable = ReadEEByte(USER_DATA_BASE + STRETCH_OUT_ADDRESS);
            if(us047_enable)
            { 
              Valve_StretchControlProce_US047();  //执行拉退，气囊由算法控制
            }
            else
            { 
              Valve_StretchControlProce();  //执行拉退，气囊由算法控制
            }
           */   
            if(st_Stretch.active == TRUE)
            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArm, 1); //在拉退时刻，由数组控制手臂气囊程序
            }
            else

            {
                Valve_Control(VALVE_ENABLE, &st_AirBagArmSholderBackWaist, by_EngineeringAirBag);
                Valve_Control(VALVE_ENABLE, &st_AirBagModeLegFootSeat, by_EngineeringAirBag);
                Valve_FootRollerProce(bRollerEnable, 1, &st_AirBagModeLegFootSeat);
                Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            }
        }
        else
        {

            if(st_Stretch.active)
            {
                st_Stretch.active = FALSE;
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
            Valve_LegKneadProce(bLegKneadEnable, 1, &st_AirBagModeLegFootSeat);
            
        }
    }
    else
    {

        if(st_Stretch.active)
        {
            st_Stretch.active = FALSE;
            st_Stretch.init = FALSE;
            bKeyLegPadUp = FALSE ;
            bKeyLegPadDown = FALSE ;
            bLegPadLinkage = FALSE ;
            bKeyBackPadUp = FALSE ;
            bKeyBackPadDown = FALSE ;
        }

        Valve_FootRollerProce(bRollerEnable, 0, &st_AirBagLegFoot);
        Valve_LegKneadProce(bLegKneadEnable, 0, &st_AirBagLegFoot);
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
        }
    }
}

#include "_3D_Position_TAB.c"
extern  const unsigned char _3D_Position[];
void Main_Axis_Proce_Old(void)
{   
  if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
  {
    unsigned int position = Input_GetWalkMotorPosition();
    float f_ShoulderPosition=(float)nShoulderPosition;
    float  f_positionStep = f_ShoulderPosition/50;
    float f_index;
    f_index =  (float)position/f_positionStep;
    unsigned int index = (unsigned int)f_index; 
     
    if(index > 49) index = 49;
    unsigned int _3D_Base_Position = _3D_Position[index];
    unsigned int _3D_Target_Position;
    
    switch(nAxisStrength)  //按键力度
    {
    case 0: 
      if((_3D_Base_Position - 10) > 0)  _3D_Target_Position = _3D_Base_Position - 10;
      else _3D_Target_Position = 0;
      break;
    case 1: 
      if((_3D_Base_Position - 5) > 0)  _3D_Target_Position = _3D_Base_Position - 5;
      else _3D_Target_Position = 0;
      break;
    default:
    case 2: 
      _3D_Target_Position = _3D_Base_Position; 
      break;
    case 3: 
      _3D_Target_Position = _3D_Base_Position + 5;
      break;
    case 4:   _3D_Target_Position = _3D_Base_Position + 10;
    break;
    }
    AxisMotor_Control(STATE_RUN_AXIS_REAL_POSITION,_3D_Target_Position,AXIS_SPEED_SLOW);
    return;
  }  
    if(bAxisUpdate)
    {
        if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,AXIS_SPEED_MID) == TRUE)
        {
            bAxisUpdate = FALSE;  
        }
    }
    if((bKeyAxisForward == FALSE) && (bKeyAxisBehind == FALSE) && (bAxisUpdate == FALSE))
    {
        AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
    }
}

void Main_3D_ModeProgram(void)
{
  int kneadMotorState,knockMotorState,_3D_MotorState;
  switch(nBackSubRunMode)
  {
  case BACK_SUB_MODE_3D1:
    {
      switch(_3D_Mode_Step)
      {
       case 0:
      default:  
         {
           kneadMotorState = KneadMotor_Control(STATE_KNEAD_STOP_AT_MIN,KNEAD_SPEED3_PWM);
           KnockMotor_Set_Pwm_Data(0);
           nAxisStrength = _3D_MIN_POSITION;
           _3D_MotorState = AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,AXIS_SPEED_MID);
           if(kneadMotorState && _3D_MotorState)
           {
             _3D_Mode_Step++;
           }
         }
         break;
      case 1:
        {
           KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
           KnockMotor_Set_Pwm_Data(0);
           nAxisStrength = _3D_MAX_POSITION;
           _3D_MotorState = AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,AXIS_SPEED_MID);
           if( _3D_MotorState)
           {
             _3D_Mode_Step++;
           }
         }
         break;
      case 2:
        {
           kneadMotorState = KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX, KNEAD_SPEED5_PWM);
           KnockMotor_Set_Pwm_Data(0);
           AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
           if( kneadMotorState)
           {
             _3D_Mode_Step++;
           }
         }
         break;   
       case 3:
        {
           KneadMotor_Control(STATE_KNEAD_IDLE, KNEAD_SPEED0_PWM);
           KnockMotor_Set_Pwm_Data(0);
           nAxisStrength = _3D_MIN_POSITION;
           _3D_MotorState = AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,AXIS_SPEED_MID);
           if(kneadMotorState && _3D_MotorState)
           {
             _3D_Mode_Step = 0;
           }
         }
         break;     
      }
    }
    break;
  case BACK_SUB_MODE_3D2:
    {
      
    }
    break;
  case BACK_SUB_MODE_3D3:
    {
      
    }
    break; 
  }
}


//本函数工作在自动程序中
void Main_Axis_Proce(void)
{   
   unsigned int walkPosition = Input_GetWalkMotorPosition();
  // unsigned int _3D_WalkCount;
   //static unsigned int old_3D_WalkCount;
   if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
   {
     unsigned int _3D_WalkCount = _3D_GetWalkCount(walkPosition); //依据行走马达位置获取当前的3D电流上下位置
     unsigned int _3D_targetPosition = _3D_Get_3D_count(_3D_WalkCount,nAxisStrength);
     unsigned short curPosition = Input_GetAxisMotorPosition();
     if((curPosition+3 < _3D_targetPosition) || (curPosition > _3D_targetPosition+3))
     {
         AxisMotor_Control(STATE_RUN_AXIS_REAL_POSITION,_3D_targetPosition,AXIS_SPEED_MID);
     }
     else
       AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
     return;
   }
   if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)
     {
       if(nBackSubRunMode == BACK_SUB_MODE_3D1 ||
            nBackSubRunMode == BACK_SUB_MODE_3D2 ||
              nBackSubRunMode == BACK_SUB_MODE_3D3)
       {
         Main_3D_ModeProgram();
          /*
         if(b3DMotorInProcess)
         {
           nAxisStrength = n3DMotorControlParam1;
           if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,n3DMotorControlParam2))
           {
             bAxisUpdate = false;  
             b3DMotorInProcess  = false;
           }
         }
         else
         {
           AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);  
         }
         */
       }
       else  //以下3D马达由3d手动按键决定
       {
         if(walkPosition > 350)
         {
           bAxisUpdate = false;  
           unsigned int curPosition = Input_GetAxisMotorPosition();
           if(curPosition < 15)  AxisMotor_Control(STATE_RUN_AXIS_REAL_POSITION,20,AXIS_SPEED_MID);
         }
         else 
           if(bAxisUpdate)
           {
             if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,nAxisStrength,AXIS_SPEED_MID))
               bAxisUpdate = false;  
           }
           else
           {
             AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST); 
           }
       }
     }
   else
   {
     AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
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
       (st_Stretch.active)) 
    {
        bMassagePositionUpdate = 0;    //手动优先
        return;
    }
    
    w_BackPosition = BackMotor_Get_Position();
    w_LegPosition = LegMotor_Get_Position(); 
    
    if(!bMassagePositionUpdate) 
    {
        return;
    }
    switch(nTargetMassagePosition)
    {
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
          
        if((nFlexStatus&0x03) ==  FLEX_AT_IN) 
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
           Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
           Flex_SetDirection(FLEX_TO_IN);
           bFlexPadFinish = FALSE;
        }
        
        /*
        if(FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_RESET) == FLEX_STOP_AT_IN)
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
            bFlexPadFinish = FALSE;
        }*/ 
        break;
    case MASSAGE_INIT_POSITION:
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
              if((nFlexStatus&0x03) ==  FLEX_AT_IN) 
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
           Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
           Flex_SetDirection(FLEX_TO_IN);
           bFlexPadFinish = FALSE;
        }
            /*
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_3A) == FLEX_STOP_AT_IN)
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }*/
        }
        else
        {
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
            bFlexPadFinish = FALSE;
        }
        FlexMotorSetEnable();
        break;
    case MASSAGE_OPTIMAL_POSITION:
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            
            if(w_BackPosition > (MASSAGE_BACK_OPTIMAL_POSITION + 50))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                bBackPadFinish = FALSE;
            }
            else if(w_BackPosition < (MASSAGE_BACK_OPTIMAL_POSITION - 50))
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
              if((nFlexStatus&0x03) ==  FLEX_AT_IN) 
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
           Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
           Flex_SetDirection(FLEX_TO_IN);
           bFlexPadFinish = FALSE;
        }
            /*
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_3A) == FLEX_STOP_AT_IN)
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }*/
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
        }
        FlexMotorSetEnable();
        break;
        
    case MASSAGE_OPTIMAL2_POSITION:
        bAdjFlex = true;
        if(SlideMotorControl(STATE_RUN_SLIDE_FORWARD) == TRUE)  
        {
            bSliderFinish = TRUE;
            w_BackPosition = BackMotor_Get_Position();
            if(w_BackPosition > (MASSAGE_BACK_OPTIMAL1_POSITION + POSITION_CTRL_OFFSET))
            {
                BackMotor_Control(STATE_RUN_BACK_UP) ;
                bBackPadFinish = FALSE;
            }
            else if(w_BackPosition < (MASSAGE_BACK_OPTIMAL1_POSITION - POSITION_CTRL_OFFSET))
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
            if(w_LegPosition > (MASSAGE_LEG_OPTIMAL1_POSITION + POSITION_CTRL_OFFSET))
            {
                LegMotor_Control(STATE_RUN_LEG_DOWN) ;
                bLegPadFinish = FALSE;
            }
            else if(w_LegPosition < (MASSAGE_LEG_OPTIMAL1_POSITION - POSITION_CTRL_OFFSET))
            {
                LegMotor_Control(STATE_RUN_BACK_UP) ;
                bLegPadFinish = FALSE;
            }
            else
            {
                LegMotor_Control(STATE_BACK_IDLE) ;
                bLegPadFinish = TRUE;
            }
              if((nFlexStatus&0x03) ==  FLEX_AT_IN) 
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
           Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
           Flex_SetDirection(FLEX_TO_IN);
           bFlexPadFinish = FALSE;
        }
            /*
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_3A) == FLEX_STOP_AT_IN)
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }
            */
        }
        else
        {
            bFlexPadFinish = FALSE;
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
        }
        FlexMotorSetEnable();
        break;  
    case MASSAGE_MAX_POSITION:
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
              if((nFlexStatus&0x03) ==  FLEX_AT_IN) 
        {
            bFlexPadFinish = TRUE;
        }
        else
        {
           Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
           Flex_SetDirection(FLEX_TO_IN);
           bFlexPadFinish = FALSE;
        }
            /*
            if(FlexMotor_Control(STATE_RUN_FLEX_RESET,FLEX_SPEED_FAST,FLEX_CURRENT_3A) == FLEX_STOP_AT_IN)
            {
                bFlexPadFinish = TRUE;
            }
            else
            {
                bFlexPadFinish = FALSE;
            }*/ 
        }
        else
        {
            bSliderFinish = FALSE;
            bBackPadFinish = FALSE;
            bLegPadFinish = FALSE;
            bFlexPadFinish = FALSE;
        }
        FlexMotorSetEnable();
        break;
    case MASSAGE_ANY_POSITION:
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
                nBuzzerMode = BUZZER_MODE_SLOW ;
                bSendBuzzerMode = TRUE ;
            }
        }
        else
        {
            if(bBackLegPadSettle == FALSE/* && st_Stretch.bBackLegFlag == FALSE*/)
            {
                nBuzzerMode = BUZZER_MODE_SLOW ;
                bSendBuzzerMode = TRUE ;
            }
        }
    }
    if(bKeyBackPadDown == TRUE)
    {
        if(SlideMotor_Get_Location() == SLIDE_MOTOR_AT_FORWARD)
        {
            SlideMotorControl(STATE_LEG_IDLE);
            if(BackMotor_Control(STATE_RUN_BACK_DOWN) == TRUE)
            {
                {
                    nBuzzerMode = BUZZER_MODE_FAST ;
                    bSendBuzzerMode = TRUE ;
                }
            }
            else
            {
                if(bBackLegPadSettle == FALSE/* && st_Stretch.bBackLegFlag == FALSE*/)
                {
                    nBuzzerMode = BUZZER_MODE_SLOW ;
                    bSendBuzzerMode = TRUE ;
                }
            }
        }
        else
        {
            SlideMotorControl(STATE_RUN_SLIDE_FORWARD);
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

//小腿电动缸控制程序
/*
void Main_LegPad_Proce(void)
{
    LegMotor_Proce();
    if(st_Stretch.active) return;
    if(bMassagePositionUpdate) return;
    if(bLegPadLinkage == FALSE) //小腿单独动，此时不考虑前滑电动缸的位置
    {
        if(bKeyLegPadUp == TRUE)
        {
            FlexMotorSetEnable();
            if(LegMotor_Control(STATE_RUN_LEG_UP) != LEG_RUN)
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

                FlexMotor_Control(STATE_RUN_FLEX_RESET, FLEX_SPEED_FAST, FLEX_CURRENT_3A);

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
*/
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

bool isZeroPosition(void)
{
    unsigned int w_BackPosition = BackMotor_Get_Position();
    unsigned int w_LegPosition = LegMotor_Get_Position(); 
    bool result;    
    result = (w_BackPosition < (MASSAGE_BACK_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
    if(result) result = (w_BackPosition > (MASSAGE_BACK_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
    if(result) result = (w_LegPosition > (MASSAGE_LEG_OPTIMAL1_POSITION - POSITION_DISPLAY_OFFSET));
    if(result) result = (w_LegPosition < (MASSAGE_LEG_OPTIMAL1_POSITION + POSITION_DISPLAY_OFFSET));
    return(result);   
}

void Main_Close_Power(void)
{
    bool bEngineeringSettle = ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS);
    //bKeyPowerSwitch = FALSE;
    nKeyBackLocate = LOCATE_NONE;
    //电动缸回位
    if(bEngineeringSettle) //如果为真，则关机复位，否则关机不复位
    {
        bBackLegPadSettle = TRUE ;
        nTargetMassagePosition = MASSAGE_RESET_POSITION;
        bMassagePositionUpdate = TRUE;
    }
    //气囊按摩停止
    nKeyAirBagLocate = AIRBAG_LOCATE_NONE;
    //振动功能停止
    //加热功能停止
    bKeySeatVibrate = FALSE;
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

void Main_Send_Leg(void)
{
  unsigned char buffer;
  
    if(bMasterSendLegPacket)
    {
        OutLegBuffer[0] = SOI ;
        //buffer 1
        OutLegBuffer[1] = Roller_GetSpeed() & 0x03;
        buffer = Roller_GetMode() << 2;
        OutLegBuffer[1] |= buffer;
        OutLegBuffer[1] |= 1 << 6;  //allways on
        //buffer 2
        
        OutLegBuffer[2] = Flex_GetDirection();
        buffer = Flex_GetCurrent() << 2;
        OutLegBuffer[2] |= buffer;
        
        if(Flex_GetDisableAngle())  OutLegBuffer[2] |= (1<<5);
        
        //buffer 3
        
        OutLegBuffer[3] = LegKnead_GetSpeed() & 0x03;
        buffer = LegKnead_GetMode() << 2;
        OutLegBuffer[3] |= buffer;
        buffer = LegKnead_GetPower() << 4;
        OutLegBuffer[3] |= buffer;
        
        //buffer 3
        
        unsigned char valve;
        valve = BITS_ValveData[2].nByte;
        
        OutLegBuffer[4] = valve&0x3f;

        OutLegBuffer[5] = EOI;
        nOutLegBufferCount = 6;
        UartLeg_Transmit_Packet(OutLegBuffer,nOutLegBufferCount);
        bMasterSendLegPacket = FALSE ;
    }
    
   if(UartLeg_GetRXStatus())
   {
      UartLeg_ClearRXStatus(); 
      nLegAngle = UartLeg_GetAngle();
      nFlexStatus = UartLeg_GetFlexStatus();
      Flex_SetStatus(nFlexStatus);
      nLegReady = UartLeg_GetLegStatus();
   }
}
/*
void Main_MassageSignalSend(void)
{
  unsigned char outBuffer[5];
  int count;
    if(bSignalSendPacket)
    {
       outBuffer[0] = SOI ;
        
       if(WalkPower_Get() == WALK_MOTOR_POWER_ON)
       {
        outBuffer[1] = BIT0; 
       }
    
       if(WalkMotor_GetDirection() ==  WALK_MOTOR_GO_UP)
       {
        outBuffer[1] |= BIT1; 
       } 
       
       if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
       {
         outBuffer[1] |= BIT2; 
       }
       if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
       {
         outBuffer[1] |= BIT3; 
       }
       
       if(AxisMotor_IsRun())
       {
        outBuffer[1] |= BIT4; 
       } 
       
       if(AxisMotor_GetDirection() == AXIS_MOTOR_GO_FORWARD)     
       {
         outBuffer[1] |= BIT5; 
       }
       outBuffer[2] = ~outBuffer[1];
       outBuffer[2] &= 0x7f;
       outBuffer[3] = EOI;
       count = 4;
       LEUART0_Transmit_Packet(outBuffer,count);
       bSignalSendPacket = FALSE ;
    } 
}
*/ 
void Main_Send(void)
{
    if(bMasterSendPacket)
    {
        OutBuffer[0] = SOI ;
        //标识 1	按摩椅运行状态 1	按摩手法 3	按摩程序 3
        if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
        {
            OutBuffer[1] = 0<<6;
        }
        else
        {
            OutBuffer[1] = 1<<6;
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
        case BACK_SUB_MODE_KNEAD			: OutBuffer[1] |= 1<<3;break;
        case BACK_SUB_MODE_KNOCK			: OutBuffer[1] |= 2<<3;break;
        case BACK_SUB_MODE_WAVELET		        : OutBuffer[1] |= 3<<3;break;
        case BACK_SUB_MODE_SOFT_KNOCK		        : OutBuffer[1] |= 4<<3;break;
        case BACK_SUB_MODE_PRESS			: OutBuffer[1] |= 5<<3;break;
        case BACK_SUB_MODE_MUSIC			: OutBuffer[1] |= 6<<3;break;
        case BACK_SUB_MODE_RUBBING                      : OutBuffer[1] |= 7<<3;break;
        default                                         : OutBuffer[1] |= 0<<3;break; 
        }

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
        OutBuffer[2] =((bKeyWaistHeat&0x1)<<6)|((speed&0x7)<<2)|(Input_GetKneadPosition()&0x3);
        
        if(bRollerEnable)
        {
            OutBuffer[2] |= (1<<5);
        }
        else
        {
            OutBuffer[2] &= ~(1<<5);
        } 
        // 标识 1	负离子开关 1 	 振动（或扭腰）强度 3	气压强度 3
        OutBuffer[3] = (nKeySeatVibrateStrength&0x7)<<3;
        
        if(nKeyAirBagLocate != AIRBAG_LOCATE_NONE)
        {
          OutBuffer[3] |= (Valve_GetAirBagStrength()&0x7);
        }
        if(bOzonEnable)
        {
          OutBuffer[3] |= (1<<6);
        } 
        else
        {
          OutBuffer[3] &= ~(1<<6);
        }
        
        //标识 1	机芯按摩部位 2	运行时间高5位 5
        //显示位置
        OutBuffer[4] = 0;           
        if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
        {
            if((nBackSubRunMode == BACK_SUB_MODE_AUTO_0) ||
               (nBackSubRunMode == BACK_SUB_MODE_AUTO_1) ||
                   (nBackSubRunMode == BACK_SUB_MODE_AUTO_2) ||
                       (nBackSubRunMode == BACK_SUB_MODE_AUTO_3))
            {
                OutBuffer[4] = 1<<5;           
            }
            else
            {
                OutBuffer[4] = 2<<5;
            }
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
        /*
        if( (bLegDownUpAirBagValve) |(bLegSideAirBagValve))
        {
            OutBuffer[6] |= 0x02;
        }
        */
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
           OutBuffer[6] |= (Roller_GetSpeed() << 5);
        }
        else
        {
            OutBuffer[6] |= (0<<5);     
        }
        
        OutBuffer[7] = 0x0;
        if((bLeftSholderAirBagValve) | (bRightSholderAirBagValve))
        {
            OutBuffer[7] |=  0x10;
        }
        if((bBackWaistRightUp) | (bBackWaistRightDown) |(bBackWaistLeftUp) | (bBackWaistLeftDown))
        {
            OutBuffer[7] |=  0x20;
        }
        
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

        unsigned int data = Input_GetWalkMotorPosition();
        data /= 31;
        if(data >= 13) data = 13;
        OutBuffer[8] = data;   
         OutBuffer[9] = 0;
        if(BodyDetectStep == DETECT_SHOULDER) 
        {
          if((ShoulderSteps > BODY_DETECT_PREPARE) && (ShoulderSteps < BODY_DETECT_OVER))
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
        if(isZeroPosition())
        {
            OutBuffer[10] = 1<<6;  
        }
        if(SlideMotor_GetPower() == SLIDE_MOTOR_POWER_ON)
        {
            if(SlideMotor_GetDirection() == SLIDE_MOTOR_GO_FORWARD)
            {
                OutBuffer[10] = 0x01<<4;
            }
            else
            {
                OutBuffer[10] = 0x02<<4;
            }
        }
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
        
        
       // OutBuffer[11] |= ((nvcBluetoothPower&0x1)<<4);
        
        switch(w_PresetTime)
        {
        case RUN_TIME_10: OutBuffer[12] = 1;  break;
        case RUN_TIME_20: OutBuffer[12] = 2;  break;
        case RUN_TIME_30: OutBuffer[12] = 3;  break;
        default: OutBuffer[12] = 0; break;
        }
        OutBuffer[12] |= ((nKeyAirBagLocate & 0x07) << 2);
        
        
        
         
   
    //滚轮方向
    if(bRollerEnable)
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
    }
    if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)
    {
      OutBuffer[13] |=  7 << 2;
    }
    else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) /*|| (nBackMainRunMode == BACK_MAIN_MODE_SLEEP)*/)
    {
      
      BYTE mode = (nBackSubRunMode + 1);
     
      OutBuffer[13] |= (mode & 0x0f) << 2;
    }
    else  if(nChairRunState == CHAIR_STATE_RUN)
    {
      OutBuffer[13] |=  7 << 2;
    }
    
    OutBuffer[14] = (nAxisStrength+1) & 0x07;
    //OutBuffer[14] |=(nAxisMode&0x7+1) << 3;
    
   // OutBuffer[14] = 0;
    OutBuffer[15] = EOI;
    nOutBufferCount = 16;
   
        
        /*
        OutBuffer[13] = EOI;
        nOutBufferCount = 14;
        */
        DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
        
        bMasterSendPacket = FALSE ;
    } 
    Main_Send_Leg();
   // Main_MassageSignalSend();
}
//BlueTooth
void Main_BlueToothSend(void)
{
  if(bBlueToothMasterSendPacket)
  {
    OutBufferBlueTooth[0] = SOI ;
    //标识 1	按摩椅运行状态 1	按摩手法 3	按摩程序 3
    if(nChairRunState == CHAIR_STATE_IDLE || nChairRunState == CHAIR_STATE_SLEEP)
    {
      OutBufferBlueTooth[1] = 0 << 6;
    }
    else
    {
      OutBufferBlueTooth[1] = 1 << 6;
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
    
    if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)
    {
      OutBufferBlueTooth[1] |=  7;
    }
    else if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
      
      BYTE mode = (nBackSubRunMode + 1);
      
      if(nChairRunState == CHAIR_STATE_DEMO)
      {
        mode &= bDisplayFlash;
      }
      
      OutBufferBlueTooth[1] |= mode & 0x7;
    }
    else  if(nChairRunState == CHAIR_STATE_RUN)
    {
      OutBufferBlueTooth[1] |=  7;
    }
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
    /*
    unsigned int valveAction  = 0;
    
    switch(nKeyAirBagLocate)
    {
  case  AIRBAG_LOCATE_AUTO:
    valveAction = st_AirBagAuto.nCurPumpValveState;
    break;
  case  AIRBAG_LOCATE_LEG_FOOT:
    valveAction = st_AirBagLegFoot.nCurPumpValveState;
    break;
  case AIRBAG_LOCATE_SEAT:
    valveAction = st_AirBagSeat.nCurPumpValveState;
    break;
  case AIRBAG_LOCATE_ARM_SHOLDER:
    valveAction = st_AirBagArmSholder.nCurPumpValveState;
    break;
  case AIRBAG_LOCATE_BACK_WAIST:
    valveAction = st_AirBagBackWaist.nCurPumpValveState;
    break;
  }
    */
    OutBufferBlueTooth[6] = 0x00;
    /*
    if((bFootBackAirBagValve) | (bLeftFootAirBagValve) | (bRightFootAirBagValve) | (bFootHeelAirBagValve))
    {
      OutBufferBlueTooth[6] |= 0x01;
    }
    if((bLegDownBottomAirBagValve) | (bLegAirBagValve) | (bLegDownUpAirBagValve) | (bLegSideAirBagValve))
    {
      OutBufferBlueTooth[6] |= 0x02;
    }
    */
    if((bLeftThighAirBagValve) | (bRightThighAirBagValve ))
    {
      OutBufferBlueTooth[6] |= 0x04;
    }
    if((bRightArmUpAirBagValve1) | (bRightArmUpAirBagValve2) | (bRightArmUpAirBagValve3) | (bLeftArmUpAirBagValve1) | (bLeftArmUpAirBagValve2 ) | (bLeftArmUpAirBagValve3))
    {
      OutBufferBlueTooth[6] |= 0x10;
    }
    
    if(bRollerEnable)
    {
     // if(Valve_RollerIsAuto())
      if(0)
      {
        // if(bDisplayFlash) OutBufferBlueTooth[6] |= (3<<5);
        // else  OutBufferBlueTooth[6] |= (0<<5);
        unsigned int rollerPWM = 0;
        //rollerPWM = displayPWM;
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
    if((bBackWaistRightUp) | (bBackWaistRightDown) | (bBackWaistLeftUp) | (bBackWaistLeftDown))
    {
      OutBufferBlueTooth[7] |=  0x20;
    }
    
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
    
    /*
    int data;
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
    data = nFinalWalkMotorLocate; //自动模式使用肩膀位置
  }
    else
    {
    data = TOP_POSITION;   //手动模式使用自动形成
  }
    */
    unsigned int data = Input_GetWalkMotorPosition();
    data /= 31;
    if(data >= 13) data = 13;
    OutBufferBlueTooth[8] = data;
    
    /*
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO &&
       nReworkShoulderPosition == 2 && nBackSubRunMode != BACK_SUB_MODE_AUTO_5)   //开始检测
    {
      OutBufferBlueTooth[9] = 1 << 6;
    }
    else
    {
      OutBufferBlueTooth[9] = 0 << 6;
    }
    */
    if(nCurSubFunction == BACK_SUB_MODE_BODY_DETECT_1)
    {
      OutBufferBlueTooth[9] |= 1 << 5;
    }
    else
    {
      OutBufferBlueTooth[9] |= 0 << 5;
    }
    /*
    if(bFail == 0 && bodyDetectSuccess == 1)
    {
      OutBufferBlueTooth[9] |= 1 << 4;
    }
    else if(bFail == 1 && bodyDetectSuccess == 0)
    {
      OutBufferBlueTooth[9] |= 0 << 4;
    }
    */
    
    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && (nCurSubFunction == BACK_SUB_MODE_BODY_DETECT_1))
    {
      data = nShoulderPositionTop - nShoulderPositionBottom;
      time = data / 15;
      data = (Input_GetWalkMotorPosition() - nShoulderPositionBottom) / time;
      if(data == 0) data = 1;
      if(data > 15) data = 15;
    }
    else
      data = 0;
    
    OutBufferBlueTooth[9] |= data & 0x0f;
    
    // OutBufferBlueTooth[9] = Input_GetVout();
    
    //标识 1	运行指示 1	小腿电动缸运行方向指示 3	靠背电动缸运行方向指示 3
    //OutBuffer[10] = ((bLegPadMotorPowerFlag || bBackPadMotorPowerFlag)&0x1)<<6;
    //OutBuffer[10] |=(nCurLegPadMotorState&0x7)<<3;
    //OutBuffer[10] |= nCurBackPadMotorState&0x7;
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
    if(bBlueToothSendBuzzerMode == TRUE)
    {
      OutBufferBlueTooth[11] = (nBuzzerMode & 0x3) << 5;
      bBlueToothSendBuzzerMode = FALSE ;
    }
    else
    {
      OutBufferBlueTooth[11] = 0;
    }
//    OutBufferBlueTooth[11] |= ((nvcBluetoothPower & 0x1) << 4);
    
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
    OutBufferBlueTooth[12] |= ((nKeyAirBagLocate & 0x1F) << 2);
    
    //滚轮方向
    if(bRollerEnable)
    {
     // if(ReadRollerPhase() == 1)
      if(1)
      {
        OutBufferBlueTooth[13] = 1;
      }
      /*
      else if(ReadRollerPhase() == 0)
      {
        OutBufferBlueTooth[13] = 2;
      }
      else
        OutBufferBlueTooth[13] = 0;
      */
    }
    else
    {
      OutBufferBlueTooth[13] = 0;
    }
    if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL)
    {
      OutBufferBlueTooth[13] |=  7 << 2;
    }
    else if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
      
      BYTE mode = (nBackSubRunMode + 1);
     
      OutBufferBlueTooth[13] |= (mode & 0x0f) << 2;
    }
    else  if(nChairRunState == CHAIR_STATE_RUN)
    {
      OutBufferBlueTooth[13] |=  7 << 2;
    }
    //添加机器识别码
    //OutBufferBlueTooth[14] = MACHINEID;
    static char count = 0;
    count++;
    count &= 0x7f;
    OutBufferBlueTooth[14] = count;
    //OutBufferBlueTooth[14] = MACHINEID;
    unsigned char checkSum = 0;
    for(int i=1;i<=14;i++)
    {
       checkSum += OutBufferBlueTooth[i];
    }
    checkSum = ~checkSum;
    checkSum &= 0x7f;
    OutBufferBlueTooth[15] = checkSum;
    OutBufferBlueTooth[16] = EOI;
    nOutBufferBlueToothCount = 17;
    BlueToothUart_Transmit_Packet((char*)OutBufferBlueTooth, nOutBufferBlueToothCount);
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
    GlobalFlags11.nByte = 0;
    
    unsigned int pw_Information[5];
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    // 
    if((SOFT_MAIN_VER != ReadEEByte(USER_DATA_BASE + SOFT_MAIN_VER_ADDRESS)) || (SOFT_SECONDARY_VER != ReadEEByte(USER_DATA_BASE + SOFT_SECONDARY_VER_ADDRESS))) 
    {  //首次使用需要初始化数据
        *(pInformation + SOFT_MAIN_VER_ADDRESS) = SOFT_MAIN_VER;
        *(pInformation + SOFT_SECONDARY_VER_ADDRESS) = SOFT_SECONDARY_VER;
        *(pInformation + SETTLE_ADDRESS) = MEMORY_DEFAULT_SETTLE;          //气囊力度
        *(pInformation + AIRBAG_STRETCH_ADDRESS) = MEMORY_DEFAULT_AIR;               //
        *(pInformation + SLIDE_MOTOR_ENABLE_ADDRESS) = SLIDE_DEFAULT_ENABLE; 

        MEM_Write_Memory(pw_Information,5*2);
    }
    //拉退程序依据行程开关控制
    st_Stretch.mode = STRETCH_MODE_SWITCH;
    st_Stretch.PresetTime = 200;
    st_Stretch.active = false;
    
    st_AirBagArmSholderBackWaist.pAirBagArray = AirBagModeArmSholderBackWaist;
    st_AirBagArmSholderBackWaist.nTotalSteps = sizeof(AirBagModeArmSholderBackWaist)/sizeof(struct AirBagStruct);
    st_AirBagArmSholderBackWaist.locate = AIRBAG_LOCATE_ARM_SHOLDER_WAIST;
    
    st_AirBagModeLegFootSeat.pAirBagArray = AirBagModeLegFootSeat;
    st_AirBagModeLegFootSeat.nTotalSteps = sizeof(AirBagModeLegFootSeat)/sizeof(struct AirBagStruct);
    st_AirBagModeLegFootSeat.locate = AIRBAG_LOCATE_LEG_FOOT_SEAT;
    
    st_AirBagLegFoot.pAirBagArray = AirBagModeLegFoot;
    st_AirBagLegFoot.nTotalSteps = sizeof(AirBagModeLegFoot)/sizeof(struct AirBagStruct);
    st_AirBagLegFoot.locate = AIRBAG_LOCATE_LEG_FOOT;
    
    st_AirBagBackWaist.pAirBagArray = AirBagModeBackWaist;
    st_AirBagBackWaist.nTotalSteps = sizeof(AirBagModeBackWaist)/sizeof(struct AirBagStruct);
    st_AirBagBackWaist.locate = AIRBAG_LOCATE_BACK_WAIST;
    
    st_AirBagArmSholder.pAirBagArray = AirBagModeArmSholder;
    st_AirBagArmSholder.nTotalSteps = sizeof(AirBagModeArmSholder)/sizeof(struct AirBagStruct);
    st_AirBagArmSholder.locate = AIRBAG_LOCATE_ARM_SHOLDER;
    
    st_AirBagSeat.pAirBagArray = AirBagModeSeat;
    st_AirBagSeat.nTotalSteps = sizeof(AirBagModeSeat)/sizeof(struct AirBagStruct);
    st_AirBagSeat.locate = AIRBAG_LOCATE_SEAT;
    
    st_AirBagArm.pAirBagArray = AirBagModeArm;
    st_AirBagArm.nTotalSteps = sizeof(AirBagModeArm)/sizeof(struct AirBagStruct);
    st_AirBagArm.locate = AIRBAG_LOCATE_ARM;
    
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
    nSendPacketID = PACKET_MASTER_GET_COMMAND ;
    nBuzzerMode = BUZZER_MODE_OFF ;
    bSendBuzzerMode = TRUE ;
    
    nTargetMassagePosition = MASSAGE_RESET_POSITION;   //目标按摩位置
    bMassagePositionUpdate = FALSE;
    w_PresetTime = RUN_TIME_20;
     
    //滚轮数据初始化
    //nRollerPWM = 0;
    bRollerEnable = false;
    //扭腰数据初始化
    
    Data_Init();
    LEUART0_Initial_Data();
    
    memset(OutBuffer,0,sizeof(OutBuffer))  ;
    memset(InBuffer,0,sizeof(InBuffer))  ;
    
    memset(&st_Stretch,0,sizeof(StretchStruct));
    
    Valve_Initial_Data();
    nIndicateTimer = 0;
    nCurActionStep = 0;
    
    ShoulderSteps = BODY_DETECT_OVER;
    BodyDetectStep = DETECT_NO_START;
    
    Timer_Initial();
    _3D_Mode_Step = 0;
//    memset(cDeviceAddress,0,sizeof(cDeviceAddress));
}

__no_init unsigned char nBackSettleStep ;
__no_init unsigned char nBackSettleReason ;

void RunOverStop(void)
{
    bKeyLegPadUp = FALSE ;
    bKeyLegPadDown = FALSE ;
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    bLegPadLinkage = FALSE ;
    nChairRunState = CHAIR_STATE_SETTLE ;
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
        nBackSettleReason = PARK_AUTO_OVER ;
    }
    else
    {
        nBackSettleReason = PARK_MANUAL_OVER ;
    }
    nBackMainRunMode = BACK_MAIN_MODE_SETTLE ;
    nBackSettleStep = 0 ;
    Main_Close_Power();
    nBuzzerMode = BUZZER_MODE_TWOTIME ;
    bSendBuzzerMode = TRUE;
}
unsigned char Main_GetKey(void)
{
   unsigned char by_Key = H10_KEY_NONE;;
    if(DMAUart_GetRXStatus() == TRUE)
    {
        DMAUart_ClearRXStatus();
        VoiceUart_ClearRXStatus();
        by_Key = DMAUart_GetKey();
        DMAUart_SetKey(H10_KEY_NONE);
        return by_Key;
    }
    
    if(VoiceUart_GetRXStatus() == TRUE)
    {
        VoiceUart_ClearRXStatus();
        by_Key = VoiceUart_GetKey();
        VoiceUart_SetKey(H10_KEY_NONE);
        return by_Key;
    }
    
     if(BlueToothUart_GetRXStatus() == TRUE)
    {
      BlueToothUart_ClearRXStatus();
      by_Key = BlueToothUart_GetKey();
      return by_Key;
    }
   return by_Key;
}

void Main_Walk_Beep_Proce(void)
{
  if(bKeyWalkUp == TRUE)
  {
    if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
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
    else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && (nCurSubFunction == BACK_SUB_MODE_BODY_DETECT_1))
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
    if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
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
    else if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) && (nCurSubFunction == BACK_SUB_MODE_BODY_DETECT_1))
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
    Flex_SetDirection(FLEX_MOTOR_STOP);
    KnockMotor_Set_Pwm_Data(0);
    
    LED_RGB_Set_All(0);
    AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
    Valve_CloseAll();
    LegKnead_SetPower(LEG_KNEAD_OFF);
    Roller_SetSpeed(ROLLER_SPEED_STOP);
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
#define leg_angle_old       engineerData2old.bD3
#define leg_ground_old      engineerData2old.bD4
#define foot_Switch_old     engineerData2old.bD5

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
    unsigned short /*adcWalkCurrent,*/adcAxisCurrent/*,adcKnockCurrent*/,adc24,adcVcc,adc24_1,tempture;
    int engStatus = LINGO_ENG;
    unsigned int overCounter = 0;
    bool status = true;
    bool bProgram = false;
    char lingo;
    bool bHeat = false;
    char command;
    unsigned char PWM = 0;
    char airbagIndex = 1,airpumpIndex = 7;
    unsigned int airbag;
    unsigned int pw_Information[5];
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
    ADC_Get_Voltage(ADC_VCC,&adcVcc); 
    ADC_Get_Voltage(ADC_V24,&adc24); 
    ADC_Get_Voltage(ADC_V24_1,&adc24_1); 
    tempture = ADC_Get_Inttemp();
    memset(pw_Information,0,sizeof(pw_Information));
    PBYTE pInformation = (PBYTE)pw_Information;
    MEM_Read_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
    while(status)
    { 
        //WDOG_Feed();
        lingo = Main_GetKey();
        switch(lingo)
        {
        case LINGO_AIRBAG: 
            {
                engStatus = LINGO_AIRBAG;
                command = DMAUart_GetExternKey();
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
                case SYS_KEY_LEFT:airpumpIndex++;
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
        case LINGO_HEAT_TEST:
            {
                engStatus = LINGO_HEAT_TEST;
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
                command = DMAUart_GetExternKey();
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
        case LINGO_PROGRAM: 
            engStatus = LINGO_PROGRAM;
            if(*(pInformation + PROGRAM_ENABLE_ADDRESS) != PROGRAM_FLAG)
            {
                *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_FLAG; //写编程标志位
                MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            }
            bProgram = true;
            break;
        case LINGO_PROGRAM_BY_BLUETOOTH: 
            engStatus = LINGO_PROGRAM;
            *(pInformation + PROGRAM_ENABLE_ADDRESS) = PROGRAM_BY_BLUETOOTH_FLAG; //写蓝牙编程标志位
            MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);
            bProgram = true;
            break;
        case LINGO_BLUETOOTH_BR115200:
            while(!bMasterSendPacket);
            OutBuffer[0] = 'B' ;      OutBuffer[1] = 'C' ;      OutBuffer[2] = ':' ;
            OutBuffer[3] = 'B' ;      OutBuffer[4] = 'R' ;      OutBuffer[5] = '=' ;
            OutBuffer[6] = '0' ;      OutBuffer[7] = 'C' ;      OutBuffer[8] = '\r' ;
            OutBuffer[9] = '\n' ;
            nOutBufferCount = 10;
            DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
            bMasterSendPacket = FALSE;
            break;  
        case LINGO_ENG:
            {
                engStatus = LINGO_ENG;
                command = DMAUart_GetExternKey(); 
                switch(command) 
                {
                case ENG_CMD_RESET:  //关机是否复位
                    
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
                case ENG_CMD_DEC_STRENGTH:  //气囊力度减1
                    strength = *(pInformation + AIRBAG_STRETCH_ADDRESS);
                    if(strength == 0) break;
                    strength--;
                    strength %= 3;  //防止因为断电等原因导致数据错误
                    *(pInformation + AIRBAG_STRETCH_ADDRESS) = strength; 
                    MEM_Write_Memory(pw_Information,MEMORY_LENGTH_OF_BYTES);  
                    break;
                case ENG_CMD_ADD_STRENGTH:  //气囊力度加1
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
                }
            }
            break;
        case LINGO_RESET:  
            password = 0;  
            NVIC_SystemReset();
            break; //复位CPU
        case LINGO_MENU:  engStatus = LINGO_MENU;
        break; //复位CPU
        }
        /*******以下程序为气囊测试*************************/  
        switch(engStatus)
        {
        case LINGO_HEAT_TEST:
            {
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = (unsigned char)bHeat;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_LED_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                
                if(color == 0) 
                {
                    LED_RGB_Set_Red_Data(0);
                    LED_RGB_Set_Green_Data(100);
                    LED_RGB_Set_Blue_Data(0);
                }
                if(color == 1) 
                {
                    LED_RGB_Set_Red_Data(100);
                    LED_RGB_Set_Green_Data(0);
                    LED_RGB_Set_Blue_Data(0);
                } 
                if(color == 2) 
                {
                    LED_RGB_Set_Red_Data(0);
                    LED_RGB_Set_Green_Data(0);
                    LED_RGB_Set_Blue_Data(100);
                }
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = color;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
          
        case LINGO_3D_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
               // Main_MassageSignalSend();
                if(bUpKey) AxisMotor_Control(STATE_RUN_AXIS_F_FORWARD,0,AXIS_SPEED_FAST);
                if(bDownKey) AxisMotor_Control(STATE_RUN_AXIS_F_BEHIND,0,AXIS_SPEED_FAST);
//              if(bUpKey) AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0);
//              if(bDownKey) AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0);
                if(!bUpKey && !bDownKey) AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_Get3DFrontSwitch()) OutBuffer[1] |= 0x02;
                    if(Input_Get3DBackSwitch()) OutBuffer[1] |= 0x01;  

                    OutBuffer[2] = Input_GetAxisMotorPosition();
                    ADC_Get_Voltage(ADC_Vaxis,&adcAxisCurrent);
                    OutBuffer[3] = adcAxisCurrent >> 8 ;
                    OutBuffer[4] = (unsigned char)adcAxisCurrent ;
                    OutBuffer[5] = EOI ;
                    nOutBufferCount = 6;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_BACK_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                
                if(bUpKey) BackMotor_Control(STATE_RUN_BACK_UP);
                if(bDownKey) BackMotor_Control(STATE_RUN_BACK_DOWN);
                if(!bUpKey && !bDownKey) BackMotor_Control(STATE_BACK_IDLE);
                
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT) OutBuffer[1] |= 0x01;
                    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT) OutBuffer[1] |= 0x02;
                    OutBuffer[2] = EOI ;
                    nOutBufferCount = 3;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                    
                    OutBuffer[2] = (nLegAngle >> 7) & 0x7f ;
                    OutBuffer[3] = nLegAngle & 0x7f ;
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                  Flex_SetDisableAngle(1);
                  Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
                  Flex_SetDirection(FLEX_TO_OUT);
                }
                if(bDownKey) 
                {
                  Flex_SetDisableAngle(1);
                  Flex_SetCurrent(FLEX_MOTOR_CURRENT_4A);
                  Flex_SetDirection(FLEX_TO_IN);
                }
                if(!bUpKey && !bDownKey) 
                {
                  Flex_SetDisableAngle(0);
                  Flex_SetDirection(FLEX_MOTOR_STOP);
                }
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if((nFlexStatus&0x03) ==  FLEX_AT_OUT) OutBuffer[1] |= 0x01;
                    if((nFlexStatus&0x03) ==  FLEX_AT_IN) OutBuffer[1] |= 0x02;
                    if(nFlexStatus&0x04) OutBuffer[1] |= 0x04;
                    OutBuffer[2] = (unsigned char)nLegAngle; //low
                    OutBuffer[3] = (unsigned char)(nLegAngle >>8);  //high
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
            
        case LINGO_WALK_TEST:
            {
                Valve_Send_Data();
                Input_Proce();
                //Main_MassageSignalSend();
                if(bUpKey) WalkMotor_Control(STATE_RUN_WALK_UP,0);
                if(bDownKey) WalkMotor_Control(STATE_RUN_WALK_DOWN,0);
                if(!bUpKey && !bDownKey) WalkMotor_Control(STATE_WALK_IDLE,0);
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = 0;
                    if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT) OutBuffer[1] |= 0x01;
                    if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT) OutBuffer[1] |= 0x02;
                    if(Input_GetVout() == BODY_TOUCHED) OutBuffer[1] |= 0x04;
                    OutBuffer[2] = Input_GetWalkMotorPosition() >> 8;
                    OutBuffer[3] = Input_GetWalkMotorPosition() ;
                   // ADC_Get_Voltage(ADC_Vwalk,&adcWalkCurrent);
                   // OutBuffer[4] = adcWalkCurrent >> 8;
                   // OutBuffer[5] = adcWalkCurrent;
                    OutBuffer[6] = EOI ;
                    nOutBufferCount = 7;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;
        case LINGO_LEG_KNEAD_TEST:
          {
                Main_Send_Leg();
                if(legKneadSpeed == 0)
                {
                    LegKnead_SetPower(LEG_KNEAD_OFF);
                    LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
                }
                else
                {
                   LegKnead_SetPower(LEG_KNEAD_ON);
                    switch(legKneadSpeed)
                    {
                    default:  
                    case 1:LegKnead_SetSpeed(LEG_KNEAD_SPEED_SLOW);  break ;
                    case 2:LegKnead_SetSpeed(LEG_KNEAD_SPEED_MID);  break ;
                    case 3:LegKnead_SetSpeed(LEG_KNEAD_SPEED_FAST);  break ;
                    }
                    if(legKneadPhase == 0)
                        LegKnead_SetMode(LEG_KNEAD_TO_IN);
                    else
                        LegKnead_SetMode(LEG_KNEAD_TO_OUT);
                }
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = legKneadSpeed;
                    OutBuffer[2] = legKneadPhase;
                    OutBuffer[3] = EOI ;
                    nOutBufferCount = 4;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
          break;
        case LINGO_ROLLER_TEST:
          {
                Main_Send_Leg();
                if(rollerSpeed == 0)
                {
                    Roller_SetSpeed(ROLLER_SPEED_STOP);
                }
                else
                {
                    switch(rollerSpeed)
                    {
                    default:  
                    case 1:Roller_SetSpeed(ROLLER_SPEED_SLOW);  break ;
                    case 2:Roller_SetSpeed(ROLLER_SPEED_MID);  break ;
                    case 3:Roller_SetSpeed(ROLLER_SPEED_FAST);  break ;
                    }
                    if(rollerPhase == 0)
                        Roller_SetMode(ROLLER_MODE_CON_IN);
                    else
                        Roller_SetMode(ROLLER_MODE_CON_OUT);
                }
                if(bMasterSendPacket)
                {
                    OutBuffer[0] = SOI ;
                    OutBuffer[1] = rollerSpeed;
                    OutBuffer[2] = rollerPhase;
                    OutBuffer[3] = EOI ;
                    nOutBufferCount = 4;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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

                    KnockMotor_Set_Pwm_Data(PWM);
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
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                    OutBuffer[3] = Input_GetKneadPosition();
                    OutBuffer[4] = EOI ;
                    nOutBufferCount = 5;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
                    bMasterSendPacket = FALSE ;
                }
            }
            break;  
        case LINGO_INPUT:
            if(bMasterSendPacket)
            {
                if(Timer_Counter(C_TIMER_TEMP+T_LOOP,10))
                {
                    ADC_Get_Voltage(ADC_VCC,&adcVcc); 
                    ADC_Get_Voltage(ADC_V24,&adc24); 
                    ADC_Get_Voltage(ADC_V24_1,&adc24_1); 
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
                OutBuffer[9] = EOI ;
                nOutBufferCount = 10;
                DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                Valve_BodyUpAirPumpACPowerOn();  //臂肩，背腰
            }
            else
            {
                Valve_BodyUpAirPumpACPowerOff();  //臂肩，背腰
            }
            if(airpumpIndex&0x02)
            {
                Valve_LegFootAirPumpACPowerOn(); //小腿和臀部
            }
            else
            {
                Valve_LegFootAirPumpACPowerOff(); //小腿和臀部
            }
            Valve_Send_Data();
            break;
        case LINGO_ENG:  
        case LINGO_MENU:   
             Main_Send_Leg();
            LegKnead_SetPower(LEG_KNEAD_OFF);
            LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
            KnockMotor_Set_Pwm_Data(KNOCK_SPEED0_PWM);
            Roller_SetSpeed(ROLLER_SPEED_STOP);
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
                    OutBuffer[11] = (unsigned char)ReadEEByte(USER_DATA_BASE+SETTLE_ADDRESS);
                    OutBuffer[12] = (unsigned char)ReadEEByte(USER_DATA_BASE+AIRBAG_STRETCH_ADDRESS);
                    OutBuffer[13] = (unsigned char)ReadEEByte(USER_DATA_BASE+SLIDE_MOTOR_ENABLE_ADDRESS);
                    
                    // OutBuffer[14] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_0_ADDRESS);
                    // OutBuffer[15] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_1_ADDRESS);
                    // OutBuffer[16] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_2_ADDRESS);
                    // OutBuffer[17] = (unsigned char)ReadEEByte(USER_DATA_BASE+ACC_TIME_3_ADDRESS);
                    
                    OutBuffer[14] = EOI ;
                    nOutBufferCount = 15;
                    DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
                        DMAUart_Transmit_Packet(OutBuffer,nOutBufferCount);
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
        if(DMAUart_GetCtrlType() != ENGGER_CTRL)
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
}

void main_50ms_int(void)
{
    bMasterSendPacket = TRUE;
    bMasterSendLegPacket = TRUE;
    bSignalSendPacket =TRUE;
}

void main_10ms_int(void)
{
    bTimer10MS = TRUE ;
}

void Main_10ms_Proce(void)
{            
    //揉捏电机状态计数器,该变量未使用
    //nCurKneadMotorStateCounter++ ;
    sysTimer++;
    if((Data_Get_Time() == 0) && (nChairRunState == CHAIR_STATE_RUN)) 
    {
        bRunOverFlag = TRUE;
    }
    if(bRunOverFlag == TRUE)
    {
        bRunOverFlag = FALSE;
        RunOverStop();
        //if(bErrorOverFlag == TRUE)
        //{
            //bErrorOverFlag = FALSE;
        //}
    }
} 



void Main_100ms_Proce(void)
{
    
    if(w_KeyWalkHoldTimer != 0)
    {
        w_KeyWalkHoldTimer++;
        if((nChairRunState == CHAIR_STATE_WAIT_COMMAND) && (w_KeyWalkHoldTimer >50))
        {//进入工程模式
            bDemoRun = 1;
        }
    }
    
    unsigned short adc24,adcVcc,adc24_1;
    st_Stretch.timer++;  
    if(Power_Get() == 1)
    {
        ADC_Get_Voltage(ADC_V24,&adc24); 
        ADC_Get_Voltage(ADC_V24_1,&adc24_1); 
        
        if(adc24 > 3600) 
        {
            nPowerMotorHighTime++;
        }
        else
        {
            nPowerMotorHighTime = 0;
        } 
        
        if(adc24 < 1000)  
        {
            nPowerMotorLowTime++; 
        }
        else
        {
            nPowerMotorLowTime = 0; 
        }
        
        if(adc24_1 > 3600) 
        {
            nPowerValveHighTime++;
        }
        else
        {
            nPowerValveHighTime = 0;
        } 
        
        if(adc24_1 < 1000)  
        {
            nPowerValveLowTime++; 
        }
        else
        {
            nPowerValveLowTime = 0; 
        }
    }
    else
    {
        nPowerMotorHighTime = 0;
        nPowerMotorLowTime = 0;
        nPowerValveHighTime = 0;
        nPowerValveLowTime = 0;
    }
    
    ADC_Get_Voltage(ADC_VCC,&adcVcc); 
    if(adcVcc > 550) 
    {
        nPowerVCCHighTime++;
    }
    else
    {
        nPowerVCCHighTime = 0;
    } 
    
    if(adcVcc < 450)  
    {
        nPowerVCCLowTime++; 
    }
    else
    {
        nPowerVCCLowTime = 0; 
    }  
    if(KneadMotor_IsRun())
    {
        nWidthOverTime++;
    }
    else
    {
        nWidthOverTime = 0;
    }
    /*
    if(WalkPower_Get() == WALK_MOTOR_POWER_ON)
    {
        if(Input_GetWalkChange())
        {
            nWalkOverTime = 0;
            Input_ClearWalkChange();
        }
        else
        {
            nWalkOverTime++;
        }
    }
    else
    {
        nWalkOverTime = 0;
    }
    */
    if(BackMotor_GetPower() == BACK_MOTOR_POWER_ON)  
    {
        nBackOverTime++;
    }
    else
    {
        nBackOverTime = 0;
    }
    /*
    if(FlexPower_Get() == FLEX_POWER_ON)  
    {
        nFlexOverTime++;
    }
    else
    {
        nFlexOverTime = 0;
    }
    */
    if(SlideMotor_GetPower()== SLIDE_MOTOR_POWER_ON)
    {
        nZeroOverTime++;
    }
    else
    {
        nZeroOverTime = 0;
    }
    
    /********************************************/
    //按摩椅状态变换(不用频繁判断)
    if((nChairRunState == CHAIR_STATE_SETTLE) &&
       (bBackLegPadSettle != TRUE) &&
       (nBackMainRunMode != BACK_MAIN_MODE_SETTLE))
    {
        nChairRunState = CHAIR_STATE_IDLE ;
        nIndicateTimer = IDLE_INDICATE_TIME;
    }
   
    //100ms变量更新
    //电机过流计数器
    //动作持续时间
    nCurActionStepCounter++ ;
    nCurShoulderAdjustCounter++ ;
    nCurKnockRunStopCounter++ ;
    //气囊记数器
    st_AirBagBackWaist.nAirBagCounter++;
    st_AirBagLegFoot.nAirBagCounter++ ;
    st_AirBagArmSholder.nAirBagCounter++ ;
    st_AirBagArm.nAirBagCounter++ ;
    st_AirBagSeat.nAirBagCounter++;
    st_AirBagModeLegFootSeat.nAirBagCounter++;
    st_AirBagArmSholderBackWaist.nAirBagCounter++;
}

void  Main_500ms_Proce(void)
{
    //nBackLegPadFlashCount++ ;
    //if(nBackLegPadFlashCount >= 4)
    //{
    //    nBackLegPadFlashCount = 0 ;
    //}
    bDisplayFlash = ~bDisplayFlash ;
    nChairStateCount++;
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
  if(DMAUart_GetRXStatus() == TRUE)
  {
    //DMAUart_ClearRXStatus();
    by_Key = DMAUart_GetKey();
    //DMAUart_SetKey(H10_KEY_NONE);
  }  
  //if The command is from Bluetooth ,then awake from sleep mode for there's keys arrive.
  /*
  if(BlueToothUart_GetRXStatus() == TRUE)
  {
    by_Key = BlueToothUart_GetKey();
  }
  */
  return by_Key;
}
void Main_Sleep(void)
{
    bool bPowerOn = false;
    int powerCounter = 0;
    int ledCounter;
    BYTE key;
    nChairRunState = CHAIR_STATE_SLEEP; 
    //Power_Off();
    //Power_3V3_Off();
    Power_All_Off();
    while(nChairRunState == CHAIR_STATE_SLEEP)
    {
        if(DMAUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
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
        Main_BlueToothSend();
        //Main_MassageSignalSend();
    }
}

#define CURRENT_POINT_COUNT 10
/*
本程序实现无负载3D马达电流自动测量功能，记录在电流点上
LED指示：LED闪烁0.8秒亮，0.8秒灭
*/
void Main_Auto_Calibration(void)
{
   // bool ShoulderDetectSuccess = false;
    int ledCounter;
    int steps = 0;
    unsigned int positionCount,positionTicks;
    bool bKneckCheckPosition;
    //以下为碰触到揉捏头
  //  unsigned int neckPosition[LIMIT_POSITION/10+1];
    BYTE key;
    nShoulderPosition = DEFAULT_SHOULDER_POSITION;
    ShoulderSteps = BODY_DETECT_PREPARE;
    nChairRunState = CHAIR_STATE_CALIBRATION; 
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Timer_Counter_Clear(C_TIMER_5);
    BodyDetectStep = DETECT_SHOULDER;
    while(nChairRunState == CHAIR_STATE_CALIBRATION)
    {
        key = Main_GetKey();
        switch(key)
        {
         case H10_KEY_POWER_SWITCH: 
           nChairRunState = CHAIR_STATE_SETTLE;
           break;
         case H10_KEY_WALK_UP_START:
           bKeyWalkUp = true ;
           Timer_Counter_Clear(C_TIMER_5);
           break;
         case H10_KEY_WALK_UP_STOP:
           bKeyWalkUp = false ;
           Timer_Counter_Clear(C_TIMER_5);
           break; 
         case H10_KEY_WALK_DOWN_START:
           bKeyWalkDown = true ;
           Timer_Counter_Clear(C_TIMER_5);
           break;
         case H10_KEY_WALK_DOWN_STOP:
           bKeyWalkDown = false ;
           Timer_Counter_Clear(C_TIMER_5);
           break;  
           
        case H10_KEY_BACKPAD_UP_START:
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
          st_Stretch.active = FALSE;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyLegPadDown = FALSE ;
          bKeyLegPadUp = FALSE ;
          bLegPadLinkage = TRUE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_BACKPAD_DOWN_START:
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
        }
        if(bTimer10MS == TRUE)
        {
            ledCounter++;
            ledCounter %= 100;
            bTimer10MS = FALSE ;
        }
        if(ledCounter < 80)
        {
            IndicateLED_On();
        }
        else
        {
            IndicateLED_Off();
        }
       Input_Proce();
       Valve_Send_Data();
       
       Main_Send();
       Main_BlueToothSend();
       //Main_MassageSignalSend();
       
       main_GetKneadPosition();
       if(DETECT_SHOULDER == BodyDetectStep)
       {
         switch(ShoulderSteps)  
         {
         case BODY_DETECT_PREPARE:   //准备 停止敲击马达 3D马达揉捏头停在最前面，宽位置 
           {
             KnockMotor_Break();
             if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,AXIS_SPEED_FAST) && 
                KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM) &&
                  WalkMotor_Control(STATE_RUN_WALK_UP,0))
             {
               ShoulderSteps = BODY_DETECT_WALK_POSITION;
               //positionCount = 0;
              // memset(neckPosition,0,sizeof(neckPosition));
             }
           }
           break;
           
         case BODY_DETECT_WALK_POSITION:                    //行走电机下行
           if(WalkMotor_Control(STATE_RUN_WALK_POSITION,LIMIT_POSITION))
           {
            // ShoulderDetectSuccess = false;
             nShoulderPosition = DEFAULT_SHOULDER_POSITION;
             ShoulderSteps = BODY_DETECT_UP_AUTO;
           }
           if(bKneckCheckPosition == BODY_TOUCHED)   //碰到肩膀位置信号
            {
              WalkMotor_Control(STATE_WALK_IDLE,0);
             // ShoulderDetectSuccess = true;
              nShoulderPosition = Input_GetWalkMotorPosition();;
              ShoulderSteps = BODY_DETECT_UP_AUTO;
            }
          break;
         case BODY_DETECT_UP_AUTO:  //行走马达上行到脖子位置
           {
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,nShoulderPosition))
             {
               ShoulderSteps = BODY_DETECT_DATA_REFRESH;
             }
           }
           break;    
         case BODY_DETECT_DATA_REFRESH:  //数据刷新
           {
             BodyDataRefresh(); 
             ShoulderSteps = BODY_DETECT_ADJ;
             Timer_Counter_Clear(C_TIMER_5);
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
            BodyDetectStep = DETECT_3D;
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
             if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MED,KNEAD_SPEED2_PWM) && (AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,AXIS_SPEED_FAST)))    
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
             if(AxisMotor_Control(STATE_RUN_AXIS_BEHIND,0,AXIS_SPEED_FAST))
             {
               steps++;
               AxisMotor_UpdataPosition();
             }
           }
           break;    
         case 3:  //3D马达运动到最前面  
           {
             if(AxisMotor_Control(STATE_RUN_AXIS_FORWARD,0,AXIS_SPEED_FAST))
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
           }
           break;  
         }//end switch
         } // end if
       
        Data_Time_Counter_Proce();
       
        Main_BackPad_Proce();
        //小腿升降电机手动处理
        Main_LegPad_Proce();
        //小腿伸缩电机手动处理
        Main_FlexPad_Proce();
        
        Main_Massage_Position_Proce();
        FlexMotorFollowingFood();
        Main_Valve_Proce();
        LED_RGB_Proce(nChairRunState);
        
       if(Timer_Counter(C_TIMER_RUN + T_LOOP,1))
       {
         //气囊记数器
         st_AirBagBackWaist.nAirBagCounter++;
         st_AirBagLegFoot.nAirBagCounter++ ;
         st_AirBagArmSholder.nAirBagCounter++ ;
         st_AirBagArm.nAirBagCounter++ ;
         st_AirBagSeat.nAirBagCounter++;
         st_AirBagModeLegFootSeat.nAirBagCounter++;
         st_AirBagArmSholderBackWaist.nAirBagCounter++;
       }
    } //end while
   /***************程序退出区**************************/
   AxisMotor_CurrentAdj();
}

void Main_Settle(void)
{
    int steps = 0;
    BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    bKeyLegPadUp = FALSE ;
    bKeyLegPadDown = FALSE ;
    //bKeyPowerSwitch = TRUE ;
    nChairRunState = CHAIR_STATE_SETTLE ;//按摩椅处于收藏状态
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION ;
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    bBackLegPadSettle = TRUE ;
    Main_Close_Power();
    Valve_LegFootAirPumpACPowerOff();
    Valve_BodyUpAirPumpACPowerOff();
    Valve_CloseAll();
    LegKnead_SetSpeed(LEG_KNEAD_SPEED_STOP);
    Roller_SetSpeed(ROLLER_SPEED_STOP);
    //主循环
    nTargetMassagePosition = MASSAGE_RESET_POSITION;
    bMassagePositionUpdate = TRUE;
    while(nChairRunState == CHAIR_STATE_SETTLE)
    {
      //按键处理区
        key = Main_GetKey();
        if(key != H10_KEY_NONE)
        {
          Power_All_Off();
          Main_Initial_IO();
          Main_Initial_Data();
          bBackLegPadSettle = FALSE;
          nChairRunState = CHAIR_STATE_IDLE; 
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
         switch(steps)  
         {
         case 0:   //揉捏马达停在最宽处
           KnockMotor_Break();
           if(KneadMotor_Control(STATE_KNEAD_STOP_AT_MAX,KNEAD_SPEED2_PWM))    
           {
             steps++;    
           }
           break;
         case 1:   //行走马达停在上行程开关位置
            if(WalkMotor_Control(STATE_RUN_WALK_UP,0))
            {
             steps++;    
            }  
           break;
           
         case 2:   //行走马达停在复位位置
            if(WalkMotor_Control(STATE_RUN_WALK_POSITION,RESET_POSITION))
            {
             steps++;    
            }  
           break;
         case 3:    
         default:    
            steps = 100;    
            break;
         }
        //判断所有的电动缸和机芯是否复位
        if((Input_GetBackUpSwitch() == REACH_BACK_LIMIT) &&
                (Input_GetLegDownSwitch() == REACH_LEG_LIMIT) &&
                   (Input_GetSlideBackwardSwitch() == REACH_SLIDE_LIMIT) &&
                     (steps == 100))
            {
               nChairRunState = CHAIR_STATE_SLEEP; 
            }
        
    } //end while
   /***************程序退出区**************************/
    WalkMotor_Control(STATE_WALK_IDLE,0);
}
void Main_WaitCommand(void)
{
    BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    bBackLegPadSettle = FALSE ;
    bKeyBackPadUp = FALSE ;
    bKeyBackPadDown = FALSE ;
    bKeyLegPadUp = FALSE ;
    bKeyLegPadDown = FALSE ;
    nCurSubFunction = BACK_SUB_MODE_NO_ACTION;
    nChairRunState = CHAIR_STATE_WAIT_COMMAND ;//按摩椅等待按键命令
    nChairStateCount = 0 ;
    Data_Set_Start(0,0);
    nBackSubRunMode = BACK_SUB_MODE_NO_ACTION ;
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Main_Stop_All();
    //主循环
    while(nChairRunState == CHAIR_STATE_WAIT_COMMAND)
    {
      //按键处理区
        key = Main_GetKey();
        if(H10_KEY_NONE != key)
        {
         // printf("key:%02x\n",key); 
          Timer_Counter_Clear(C_TIMER_TEMP);
          switch(key)
          {
            /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
            {
            case H10_KEY_MENU:
              nChairStateCount = 0 ;
              break;
            case H10_KEY_POWER_SWITCH: 
              {
                bBackLegPadSettle = TRUE ;
                nChairRunState = CHAIR_STATE_SETTLE ;
                Main_Close_Power();
              }
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break ;
            case H10_KEY_BLUETOOTH_POWER_SWITCH:
              if(BlueToothMuteState() == BlueTooth_Speak_Out_On)
              {
                BlueToothOff();
              }
              else
              {
                BlueToothOn();
              }
              break;
            case H10_KEY_CHAIR_AUTO_0:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_0;
             // printf("auto0\n\r");
              break ;
            case H10_KEY_CHAIR_AUTO_1:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_1;
              // printf("auto1\n\r");
              break ;
            case H10_KEY_CHAIR_AUTO_2:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_2;
               //printf("auto2\n\r");
              break ;
            case H10_KEY_CHAIR_AUTO_3:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_3;
              // printf("auto3\n\r");
              break ;
            case H10_KEY_CHAIR_AUTO_4:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_4;
              // printf("auto4\n\r");
              break ;
            case H10_KEY_CHAIR_AUTO_5:
              nChairRunState = CHAIR_STATE_RUN ;
              nBackMainRunMode = BACK_MAIN_MODE_AUTO;
              nBackSubRunMode = BACK_SUB_MODE_AUTO_5;
              // printf("auto\n\r");
              break ;                      
            case H10_KEY_ZERO_START:
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
              break;
            case  H10_KEY_3D_STRENGTH:     
              if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))
              {
                nAxisStrength++;
                nAxisStrength %= 5;
                bAxisUpdate = TRUE;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;   
              }
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
              
            case H10_KEY_AIRBAG_AUTO:
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
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
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
              if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))    
              {
                nAxisStrength = H10_KEY_3DSPEED_5 - key;
                nAxisStrength %= 5;
                bAxisUpdate = TRUE;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;   
              }
              break;
            case H10_KEY_KNEAD:
              nMaunalSubMode = nMaunalSubMode_KNEAD;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
            case H10_KEY_KNOCK:
              nMaunalSubMode = nMaunalSubMode_KNOCK;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
              
            case H10_KEY_WAVELET:
              nMaunalSubMode = nMaunalSubMode_WAVELET;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
              
            case H10_KEY_SOFT_KNOCK:
              nMaunalSubMode = nMaunalSubMode_SOFT_KNOCK;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
              
            case H10_KEY_PRESS:
              nMaunalSubMode = nMaunalSubMode_PRESS;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
              
            case H10_KEY_MUSIC:             
              nMaunalSubMode = nMaunalSubMode_MUSIC;
              nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
              nChairRunState = CHAIR_STATE_RUN ;
              break;
              
            case H10_KEY_MANUAL: break;
            case H10_KEY_LOCATE_FULL:
            case H10_KEY_LOCATE_POINT:
            case H10_KEY_LOCATE_PART:  
              break;
            case H10_KEY_OZON_SWITCH:
              bOzonEnable = TRUE;
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
               if(Data_Get_Time() == 0)
                {
                  Data_Set_Start(1, w_PresetTime);
                }
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;
            case H10_KEY_SPEED_DECREASE:
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
              
            case H10_KEY_AIRBAG_LEG:
              nKeyAirBagLocate = AIRBAG_LOCATE_LEG_FOOT ;
              st_AirBagLegFoot.init = TRUE ;
              if(Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
              {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
              }
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;
            case H10_KEY_AIRBAG_ARM:
              nKeyAirBagLocate = AIRBAG_LOCATE_ARM_SHOLDER ;
              st_AirBagArmSholder.init = TRUE ;
              if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
              {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
              }
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;
            case H10_KEY_AIRBAG_WAIST:
              nKeyAirBagLocate = AIRBAG_LOCATE_BACK_WAIST ;
              st_AirBagBackWaist.init = TRUE ;
              if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
              {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
              }
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;
            case H10_KEY_AIRBAG_BUTTOCKS:
              nKeyAirBagLocate = AIRBAG_LOCATE_SEAT ;
              st_AirBagSeat.init = TRUE ;
              if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
              {
                Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
              }
              nChairRunState = CHAIR_STATE_RUN ;
              nIndicateTimer = RUN_INDICATE_TIME;
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;  
              
            case H10_KEY_WALK_UP_START:
              break ;
            case H10_KEY_WALK_UP_STOP:
              break ;
            case H10_KEY_WALK_DOWN_START:
              break ;
            case H10_KEY_WALK_DOWN_STOP:
              break ;
              
            case H10_KEY_BACKPAD_UP_START:
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
              st_Stretch.active = FALSE;
              bKeyBackPadUp = FALSE ;
              bKeyBackPadDown = FALSE ;
              bKeyLegPadDown = FALSE ;
              bKeyLegPadUp = FALSE ;
              bLegPadLinkage = TRUE ;
              bKeyFlexOut = FALSE ;
              bKeyFlexIn = FALSE ;
              break ;
            case H10_KEY_BACKPAD_DOWN_START:
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
                nIndicateTimer = RUN_INDICATE_TIME;
                if(Data_Get_Time() == 0)
                {
                  Data_Set_Start(1, w_PresetTime);
                }
              }
              nBuzzerMode = BUZZER_MODE_ONETIME ;
              bSendBuzzerMode = TRUE ;
              break;
            case H10_KEY_HEAT:    //加热
              {
                nChairRunState = CHAIR_STATE_RUN ;
                bKeyWaistHeat = true;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;
              }
              break;     
            default:       
              break;
            }
          }
        }
    /*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */    
      //时间处理区
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
        
        Main_Massage_Position_Proce();
        FlexMotorFollowingFood();
        Main_Send_Leg();
        if((bKeyBackPadUp == FALSE) && (bKeyBackPadDown == FALSE) &&
                (bKeyLegPadUp == FALSE) && (bKeyLegPadDown == FALSE) &&
                 (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE))  
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
}


void Main_WalkFullBackSetProgram(void)
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
void Main_Start_Manual(void)
{
  switch(nMaunalSubMode)	
  {
  case nMaunalSubMode_KNEAD: 
    nBackSubRunMode = BACK_SUB_MODE_KNEAD ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate和nKeyKneadWidth
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    nKeyBackLocate = LOCATE_FULL_BACK ; //全程
    {
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
    }
    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
    {
      nKeyKneadWidth = KNEAD_WIDTH_MED ;
    }
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[0].nKneadMotorCycles = 0 ;
    ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    nBackSubRunMode = BACK_SUB_MODE_KNOCK ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    nKeyBackLocate = LOCATE_FULL_BACK ;
    ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
    ManualDirector[0].nWalkMotorLocateParam = 0 ;
    ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
    ManualDirector[1].nWalkMotorLocateParam = 0 ;    
    
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
    ManualDirector[0].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    //  if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
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
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    //if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
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
    ManualDirector[0].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 1 ;
    ManualDirector[0].nKnockMotorStopTime = 4 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_SOFT_KNOCK ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 1 ;
    ManualDirector[1].nKnockMotorStopTime = 4 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
#ifdef RUBBING_MANUAL_TEST                                    
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
    nKeyKneadKnockSpeed = SPEED_6 ;
    //if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
    }
    
    ManualDirector[0].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN_RUBBING ;
    
    
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[0].nKneadMotorCycles = 4 ;
    ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[1].nKneadMotorCycles = 4 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    
#else /*RUBBING_MANUAL_TEST  */
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
    //if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
      ManualDirector[0].nWalkMotorLocateParam = 0 ;
      ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
      ManualDirector[1].nWalkMotorLocateParam = 0 ;
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
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    
#endif /*RUBBING_MANUAL_TEST  */                                    
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
      nKeyBackLocate = LOCATE_FULL_BACK ;
      
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
    
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKnockMotorStopTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKnockMotorStopTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKnockMotorStopTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
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
}


//开始手动程序
void Main_Start_Manual_New(void)
{
  switch(nMaunalSubMode)	
  {
  case nMaunalSubMode_KNEAD: 
    nBackSubRunMode = BACK_SUB_MODE_KNEAD ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate和nKeyKneadWidth
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ; //全程
      Main_WalkFullBackSetProgram();
    }
    if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
    {
      nKeyKneadWidth = KNEAD_WIDTH_MED ;
    }
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[0].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[0].nKneadMotorCycles = 0 ;
    ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNEAD ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    nBackSubRunMode = BACK_SUB_MODE_KNOCK ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram();
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
    ManualDirector[0].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_KNOCK ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN_WIDTH ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    
  case nMaunalSubMode_WAVELET:
    nBackSubRunMode = BACK_SUB_MODE_WAVELET ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate和nKeyKneadWidth
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram(); 
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
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_WAVELET ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    nBackSubRunMode = BACK_SUB_MODE_SOFT_KNOCK ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram();
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
    ManualDirector[0].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 1 ;
    ManualDirector[0].nKnockMotorStopTime = 4 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_SOFT_KNOCK ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 1 ;
    ManualDirector[1].nKnockMotorStopTime = 4 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
#ifdef RUBBING_MANUAL_TEST                                    
    nBackSubRunMode = BACK_SUB_MODE_PRESS ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    nKeyKneadKnockSpeed = SPEED_6 ;
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram();
    }
    
    ManualDirector[0].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[1].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN_RUBBING ;
    ManualDirector[3].nKneadMotorState = KNEAD_RUN_RUBBING ;
    
    
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[0].nKneadMotorCycles = 4 ;
    ManualDirector[0].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[1].nKneadMotorCycles = 4 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    
#else /*RUBBING_MANUAL_TEST  */
    nBackSubRunMode = BACK_SUB_MODE_PRESS ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    if(nKeyBackLocate == LOCATE_NONE)
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram();
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
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_PRESS ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
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
    
#endif /*RUBBING_MANUAL_TEST  */                                    
    break;
    
  case nMaunalSubMode_MUSIC:
    nBackSubRunMode = BACK_SUB_MODE_MUSIC ;
    //根据当前的状态设置nKeyKneadKnockSpeed,nKeyBackLocate
    if(nKeyKneadKnockSpeed == SPEED_0)
    {
      nKeyKneadKnockSpeed = SPEED_2 ;
    }
    // if((nKeyBackLocate == LOCATE_NONE) || (nKeyBackLocate == LOCATE_POINT))
    {
      nKeyBackLocate = LOCATE_FULL_BACK ;
      Main_WalkFullBackSetProgram();
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
    
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKnockMotorStopTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[2].nKneadMotorState = KNEAD_RUN ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKnockMotorStopTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_MUSIC ;
    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN_MUSIC ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKnockMotorStopTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    
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
    //刮痧
    case nMaunalSubMode_3DMODE_1:
    {
    nBackSubRunMode = BACK_SUB_MODE_3D1; 
          if(nKeyBackLocate == LOCATE_NONE)
          {
            nKeyBackLocate = LOCATE_FULL_BACK ;
            Main_WalkFullBackSetProgram();
          }
     _3D_Mode_Step = 0;     
     /*     
    //step0 停到最窄处 3D强度最弱
    ManualDirector[0].nSubFunction = BACK_SUB_MODE_3D1 ;
    ManualDirector[0].nKneadMotorState = KNEAD_STOP_AT_MIN ;
    ManualDirector[0].nKneadMotorCycles = 0 ;
    ManualDirector[0].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[0].nKnockMotorRunTime = 0 ;
    ManualDirector[0].nKnockMotorStopTime = 0 ;
    ManualDirector[0].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[0]._3D_Position = _3D_MIN_POSITION ;
    ManualDirector[0]._3D_Speed = AXIS_SPEED_MID;
    
    //step1 停到最窄处 3D到最强
    ManualDirector[1].nSubFunction = BACK_SUB_MODE_3D1 ;
    ManualDirector[1].nKneadMotorState = KNEAD_STOP_AT_MIN ;
    ManualDirector[1].nKneadMotorCycles = 0 ;
    ManualDirector[1].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[1].nKnockMotorRunTime = 0 ;
    ManualDirector[1].nKnockMotorStopTime = 0 ;
    ManualDirector[1].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[1]._3D_Position = _3D_MAX_POSITION ;
    ManualDirector[1]._3D_Speed = AXIS_SPEED_FAST;
    //step2 由窄到宽 3D位置不动
    ManualDirector[2].nSubFunction = BACK_SUB_MODE_3D1 ;
    ManualDirector[2].nKneadMotorState = KNEAD_STOP_AT_MAX ;
    ManualDirector[2].nKneadMotorCycles = 0 ;
    ManualDirector[2].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[2].nKnockMotorRunTime = 0 ;
    ManualDirector[2].nKnockMotorStopTime = 0 ;
    ManualDirector[2].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[2]._3D_Position = _3D_MAX_POSITION ;
    ManualDirector[2]._3D_Speed = AXIS_SPEED_STOP;
    //step3 由窄到宽 3D到最后
    ManualDirector[3].nSubFunction = BACK_SUB_MODE_3D1 ;
    ManualDirector[3].nKneadMotorState = KNEAD_STOP_AT_MAX ;
    ManualDirector[3].nKneadMotorCycles = 0 ;
    ManualDirector[3].nKnockMotorState = KNOCK_RUN_STOP ;
    ManualDirector[3].nKnockMotorRunTime = 0 ;
    ManualDirector[3].nKnockMotorStopTime = 0 ;
    ManualDirector[3].nKneadKnockSpeed = nKeyKneadKnockSpeed ;
    ManualDirector[3]._3D_Position = _3D_MAX_POSITION ;
    ManualDirector[3]._3D_Speed = AXIS_SPEED_MID;
    
    //设置揉捏电机
    bKneadMotorInProcess = FALSE ;
    KneadMotor_Control(STATE_KNEAD_IDLE,0);
    //设置捶击电机
    bKnockMotorInProcess = FALSE ;
    KnockMotor_Set_Pwm_Data(0);
    //设置3D电机
    b3DMotorInProcess = TRUE;
    
    nMaxActionStep = 4 ;
    nStartActionStep = 0 ;
    bBackManualModeInit = TRUE ;
     */
    }
    break;
  //深度指压
case nMaunalSubMode_3DMODE_2:    
  {
    nBackSubRunMode = BACK_SUB_MODE_3D2; 
   if(nKeyKneadWidth == KNEAD_WIDTH_UNKNOWN)
    {
      nKeyKneadWidth = KNEAD_WIDTH_MED ;
    }
   _3D_Mode_Step = 0;
  }
    break;
 //力度渐进式揉捏
  case nMaunalSubMode_3DMODE_3:
    {
      nBackSubRunMode = BACK_SUB_MODE_3D3; 
      if(nKeyBackLocate == LOCATE_NONE)
       {
         nKeyBackLocate = LOCATE_FULL_BACK ;
         Main_WalkFullBackSetProgram();
       }
      _3D_Mode_Step = 0;
    }
    break;
  default:
    //设置背部功能
    BackManualModeNoAction() ;
    break ;
  }
}
void Main_Work(void)
{
    bool bodyDectect = false;
    BYTE key;
    Power_All_On();
    nAxisStrength = 2;
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    Data_Set_Start(1, w_PresetTime);
    if(nBackMainRunMode == BACK_MAIN_MODE_AUTO)
    {
     if(nTargetMassagePosition != MASSAGE_OPTIMAL2_POSITION)
      {
        nTargetMassagePosition = MASSAGE_OPTIMAL2_POSITION;
        bMassagePositionUpdate = TRUE;
      }
     Main_Start_Auto();
     Main_Auto_Calibration();  //进入主程序之前，先进行体型检测
     bodyDectect = true;
      
   }   
    else if(nBackMainRunMode == BACK_MAIN_MODE_MANUAL) //手动
    {
       bMassagePositionUpdate = false;
       Main_Start_Manual(); 
    }
    else
    {
      nBackSubRunMode = BACK_SUB_MODE_NO_ACTION;
      nBackMainRunMode = BACK_MAIN_MODE_IDLE;
    }
    //主循环
    while(CHAIR_STATE_RUN == nChairRunState)
    {
      //按键处理区
        key = Main_GetKey();
        switch(key)
        {
        case H10_KEY_MENU:
          break;
        case H10_KEY_BLUETOOTH_POWER_SWITCH:    
          if(BlueToothMuteState() == BlueTooth_Speak_Out_On)
          {
            BlueToothOff();
          }
          else
          {
            BlueToothOn();
          }
          break;
        case H10_KEY_POWER_SWITCH: 
          {
            //按摩机构回位
            nChairRunState = CHAIR_STATE_SETTLE ;
            nBackMainRunMode = BACK_MAIN_MODE_SETTLE ;
            nBackSettleReason = PARK_KEY_STOP ;
            bBackLegPadSettle = TRUE ;
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break ;
        case H10_KEY_CHAIR_AUTO_0:
          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_0)  break;
          if(!bodyDectect)
          {
            Main_Auto_Calibration();  //进入主程序之前，先进行体型检测
            bodyDectect = true;
          }
          nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
          nBackSubRunMode = BACK_SUB_MODE_AUTO_0 ;
          Main_Start_Auto(); 
          Data_Set_Start(1, w_PresetTime);
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break ;
        case H10_KEY_CHAIR_AUTO_1:
          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_1)  break;
          if(!bodyDectect)
          {
            Main_Auto_Calibration();  //进入主程序之前，先进行体型检测
            bodyDectect = true;
          }
          
          nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
          nBackSubRunMode = BACK_SUB_MODE_AUTO_1 ;
          Main_Start_Auto(); 
          Data_Set_Start(1, w_PresetTime);
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break ;
        case H10_KEY_CHAIR_AUTO_2:
          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_2)  break;
          if(!bodyDectect)
          {
            Main_Auto_Calibration();  //进入主程序之前，先进行体型检测
            bodyDectect = true;
          }
          nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
          nBackSubRunMode = BACK_SUB_MODE_AUTO_2 ;
          Main_Start_Auto(); 
          Data_Set_Start(1, w_PresetTime);
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break ;
        case H10_KEY_CHAIR_AUTO_3:
          if(nBackSubRunMode == BACK_SUB_MODE_AUTO_3)  break;
          if(!bodyDectect)
          {
            Main_Auto_Calibration();  //进入主程序之前，先进行体型检测
            bodyDectect = true;
          }
          nBackMainRunMode = BACK_MAIN_MODE_AUTO ;
          nBackSubRunMode = BACK_SUB_MODE_AUTO_3 ;
          Main_Start_Auto(); 
          Data_Set_Start(1, w_PresetTime);
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;    
          break; 
          
        case H10_KEY_ZERO_START:
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
          break;
        case  H10_KEY_3D_STRENGTH:     
          if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))
          {
            nAxisStrength++;
            nAxisStrength %= 5;
            bAxisUpdate = TRUE;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;   
          }
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
          
        case H10_KEY_CHAIR_AUTO_4:
          break ;
        case H10_KEY_CHAIR_AUTO_5:
          break ;                                  
        case H10_KEY_AIRBAG_AUTO:
          if(nKeyAirBagLocate != AIRBAG_LOCATE_AUTO)
          {
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
          }
          else
          {
            nKeyAirBagLocate = AIRBAG_LOCATE_NONE ;
            nRollerPWM = 0;
            bRollerEnable = FALSE;
            Valve_SetRollerPWM(nRollerPWM);
          }
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
          if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) || (nBackMainRunMode == BACK_MAIN_MODE_AUTO))
          {
            nAxisStrength = H10_KEY_3DSPEED_5 - key;
            nAxisStrength %= 5;
            bAxisUpdate = TRUE;
            nBuzzerMode = BUZZER_MODE_ONETIME ;
            bSendBuzzerMode = TRUE ;   
          }
          break;
        case H10_KEY_KNEAD:
        case H10_KEY_KNOCK:
        case H10_KEY_WAVELET:
        case H10_KEY_SOFT_KNOCK:
        case H10_KEY_PRESS:
        case H10_KEY_MUSIC:             
        case H10_KEY_MANUAL:
        case H10_KEY_3DMODE_1:
        case H10_KEY_3DMODE_2:
        case H10_KEY_3DMODE_3:
          if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL)
          {
            nBackMainRunMode = BACK_MAIN_MODE_MANUAL;
            nMaunalSubMode = 5;
          }
          nChairRunState = CHAIR_STATE_RUN ;
          nIndicateTimer = RUN_INDICATE_TIME;
          if(key == H10_KEY_MANUAL)
          { 
            //设置背部功能
            BackManualModeNoAction() ;
          }
          
          //设置气囊功能
          //设置运行时间
          if(Data_Get_Time() == 0)
          {
            Data_Set_Start(1,w_PresetTime); 
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          
        //  key = H10_KEY_3DMODE_1;  //only test
          
          switch(key)
          {
          case H10_KEY_KNEAD:       nMaunalSubMode = nMaunalSubMode_KNEAD;break;
          case H10_KEY_KNOCK:       nMaunalSubMode = nMaunalSubMode_KNOCK;break;
          case H10_KEY_WAVELET:     nMaunalSubMode = nMaunalSubMode_WAVELET;break;
          case H10_KEY_SOFT_KNOCK:  nMaunalSubMode = nMaunalSubMode_SOFT_KNOCK;break;
          case H10_KEY_PRESS:       nMaunalSubMode = nMaunalSubMode_PRESS;break;
          case H10_KEY_MUSIC:       nMaunalSubMode = nMaunalSubMode_MUSIC;break;
          case H10_KEY_3DMODE_1:    nMaunalSubMode = nMaunalSubMode_3DMODE_1;break;
          case H10_KEY_3DMODE_2:    nMaunalSubMode = nMaunalSubMode_3DMODE_2;break;
          case H10_KEY_3DMODE_3:    nMaunalSubMode = nMaunalSubMode_3DMODE_3;break;
          case H10_KEY_MANUAL:
            nMaunalSubMode++;
            nMaunalSubMode %= 9;
            break;
          }
          Main_Start_Manual();
          break ;
          
        case H10_KEY_LOCATE_FULL:
        case H10_KEY_LOCATE_POINT:
        case H10_KEY_LOCATE_PART:  //新手控器为局部
          //  if(bKeyPowerSwitch == FALSE) break ;
          if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL) break ;
          
          switch(key)
          {
          case H10_KEY_LOCATE_FULL:     nKeyBackLocate = LOCATE_FULL_BACK; break;
          case H10_KEY_LOCATE_PART:     nKeyBackLocate = LOCATE_PARTIAL; break;
          case H10_KEY_LOCATE_POINT:    nKeyBackLocate = LOCATE_POINT; break;
          }   
          if(nKeyBackLocate == LOCATE_FULL_BACK)		//全程
          {
            nKeyBackLocate = LOCATE_FULL_BACK;
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
              ManualDirector[0].nWalkMotorLocateParam = nPartialBottom ;
              ManualDirector[1].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
              ManualDirector[1].nWalkMotorLocateParam = nPartialTop ; ;
              ManualDirector[2].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
              ManualDirector[2].nWalkMotorLocateParam = nPartialBottom ;
              ManualDirector[3].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
              ManualDirector[3].nWalkMotorLocateParam = nPartialTop ; ;
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
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break ;
        case H10_KEY_OZON_SWITCH:
          bOzonEnable = ~bOzonEnable;
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
        case H10_KEY_SPEED_DECREASE:
          break;
        case H10_KEY_SPEED_1:
        case H10_KEY_SPEED_2:
        case H10_KEY_SPEED_3:
        case H10_KEY_SPEED_4:
        case H10_KEY_SPEED_5:  
        case H10_KEY_SPEED_6:
          // if(bKeyPowerSwitch == FALSE) break ;
          if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL) break;
          if((nBackSubRunMode == BACK_SUB_MODE_PRESS) || (nBackSubRunMode == BACK_SUB_MODE_NO_ACTION)) break ;
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          /*
          if(key == H10_KEY_SPEED_INCREASE)
          {
            if(nKeyKneadKnockSpeed < 6)
            {
              nKeyKneadKnockSpeed++ ;
            }
            else
            {
              nKeyKneadKnockSpeed = 1;
            }
          }
          */
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
          //  if(bKeyPowerSwitch == FALSE) break ;
          if(nBackMainRunMode != BACK_MAIN_MODE_MANUAL) break ;
          if(!((nBackSubRunMode == BACK_SUB_MODE_KNOCK) || (nBackSubRunMode == BACK_SUB_MODE_PRESS) || (nBackSubRunMode == BACK_SUB_MODE_SOFT_KNOCK))) break ;
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          bKneadWidthChange = FALSE ;
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
          nKeyAirBagLocate = AIRBAG_LOCATE_LEG_FOOT ;
          st_AirBagLegFoot.init = TRUE ;
          if(Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
          {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
        case H10_KEY_AIRBAG_ARM:
          nKeyAirBagLocate = AIRBAG_LOCATE_ARM_SHOLDER ;
          st_AirBagArmSholder.init = TRUE ;
          if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
          {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
        case H10_KEY_AIRBAG_WAIST:
          nKeyAirBagLocate = AIRBAG_LOCATE_BACK_WAIST ;
          st_AirBagBackWaist.init = TRUE ;
          if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
          {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
        case H10_KEY_AIRBAG_BUTTOCKS:
          nKeyAirBagLocate = AIRBAG_LOCATE_SEAT ;
          st_AirBagSeat.init = TRUE ;
          if( Valve_GetAirBagStrength() == AIRBAG_STRENGTH_0)
          {
            Valve_SetAirBagStrength(AIRBAG_STRENGTH_3);
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
        case H10_KEY_WALK_UP_START:
          w_KeyWalkHoldTimer = 1;
          if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
          {
            ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_TOP ;
            ManualDirector[0].nWalkMotorLocateParam = 0 ;
            bBackManualModeInit = TRUE ;
            bKeyWalkUp = TRUE ;
          }
          break ;
        case H10_KEY_WALK_UP_STOP:
          w_KeyWalkHoldTimer = 0;
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
          break ;
        case H10_KEY_WALK_DOWN_START:
          
          if((nBackMainRunMode == BACK_MAIN_MODE_MANUAL) && (nKeyBackLocate == LOCATE_POINT))
          {
            ManualDirector[0].nWalkMotorLocateMethod = WALK_LOCATE_ABSULATE ;
            ManualDirector[0].nWalkMotorLocateParam = 0 ;
            bBackManualModeInit = TRUE ;
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
          
          break ;
          
        case H10_KEY_BACKPAD_UP_START:
          // bKeyAxisForward = true;
          // bKeyAxisBehind = false;
          st_Stretch.active = FALSE;
          bKeyBackPadUp = TRUE ;
          bKeyBackPadDown = FALSE ;
          //小腿联动设置
          bKeyLegPadDown = TRUE ;
          bKeyLegPadUp = FALSE ;
          bLegPadLinkage = TRUE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_BACKPAD_UP_STOP:
          //bKeyAxisForward = false;
          //bKeyAxisBehind = false;
          st_Stretch.active = FALSE;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          //小腿联动设置
          bKeyLegPadDown = FALSE ;
          bKeyLegPadUp = FALSE ;
          bLegPadLinkage = TRUE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_BACKPAD_DOWN_START:
          //bKeyAxisForward = false;
          //bKeyAxisBehind = true;
          st_Stretch.active = FALSE;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = TRUE ;
          //小腿联动设置
          bKeyLegPadDown = FALSE ;
          bKeyLegPadUp = TRUE ;
          bLegPadLinkage = TRUE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_BACKPAD_DOWN_STOP:
          //bKeyAxisForward = false;
          //bKeyAxisBehind = false;
          st_Stretch.active = FALSE;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          //小腿联动设置
          bKeyLegPadDown = FALSE ;
          bKeyLegPadUp = FALSE ;
          bLegPadLinkage = TRUE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_LEGPAD_EXTEND_START:
          st_Stretch.active = FALSE;
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
          st_Stretch.active = FALSE;
          bKeyLegPadUp = FALSE ;
          bKeyLegPadDown = FALSE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE;
          bKeyFlexIn = FALSE ;
          break;
        case H10_KEY_LEGPAD_CONTRACT_START:
          st_Stretch.active = FALSE;
          bKeyLegPadUp = FALSE ;
          bKeyLegPadDown = FALSE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE;
          bKeyFlexIn = TRUE ;
          break;
        case H10_KEY_LEGPAD_UP_START:
          st_Stretch.active = FALSE;
          bKeyLegPadUp = TRUE ;
          bKeyLegPadDown = FALSE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_LEGPAD_UP_STOP:
          st_Stretch.active = FALSE;
          bKeyLegPadUp = FALSE ;
          bKeyLegPadDown = FALSE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_LEGPAD_DOWN_START:
          st_Stretch.active = FALSE;
          bKeyLegPadUp = FALSE ;
          bKeyLegPadDown = TRUE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
        case H10_KEY_LEGPAD_DOWN_STOP:
          st_Stretch.active = FALSE;
          bKeyLegPadUp = FALSE ;
          bKeyLegPadDown = FALSE ;
          bLegPadLinkage = FALSE ;
          bKeyBackPadUp = FALSE ;
          bKeyBackPadDown = FALSE ;
          bKeyFlexOut = FALSE ;
          bKeyFlexIn = FALSE ;
          break ;
          
        case H10_KEY_WHEEL_SPEED_OFF:
          //  if(bKeyPowerSwitch == FALSE) break ;
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
            nIndicateTimer = RUN_INDICATE_TIME;
            if(Data_Get_Time() == 0)
            {
              Data_Set_Start(1, w_PresetTime);
            }
          }
          nBuzzerMode = BUZZER_MODE_ONETIME ;
          bSendBuzzerMode = TRUE ;
          break;
          
        case H10_KEY_HEAT:    //加热
              {
                bKeyWaistHeat = ~bKeyWaistHeat;
                nBuzzerMode = BUZZER_MODE_ONETIME ;
                bSendBuzzerMode = TRUE ;
              }
              break;     
        default:       
          break;
        }
     if(H10_KEY_POWER_SWITCH == key)
       {
          nChairRunState = CHAIR_STATE_SETTLE; //按了电源键后
       }  
        
     if((Data_Get_Time() == 0) && (nChairRunState == CHAIR_STATE_RUN)) 
       {
         nChairRunState = CHAIR_STATE_SETTLE;  //按摩时间到
       }
        
      //时间处理区
       if(Timer_Counter(C_TIMER_RUN + T_LOOP,1))
       {
         nCurActionStepCounter++ ;
         nCurShoulderAdjustCounter++ ;
         nCurKnockRunStopCounter++ ;
         //气囊记数器
         st_AirBagBackWaist.nAirBagCounter++;
         st_AirBagLegFoot.nAirBagCounter++ ;
         st_AirBagArmSholder.nAirBagCounter++ ;
         st_AirBagArm.nAirBagCounter++ ;
         st_AirBagSeat.nAirBagCounter++;
         st_AirBagModeLegFootSeat.nAirBagCounter++;
         st_AirBagArmSholderBackWaist.nAirBagCounter++;
       }
       Input_Proce();
       Valve_Send_Data();
       Main_Send();
       Main_BlueToothSend();
       //Main_MassageSignalSend();
       LED_RGB_Proce(nChairRunState);
       
        main_GetKneadPosition();
        Data_Time_Counter_Proce();
         //蜂鸣器的处理
        Main_Walk_Beep_Proce();
        //靠背升降电机手动处理
        Main_BackPad_Proce();
        //小腿升降电机手动处理
        Main_LegPad_Proce();
        //小腿伸缩电机手动处理
        Main_FlexPad_Proce();
        
        Main_Massage_Position_Proce();
        FlexMotorFollowingFood();
        //背部功能处理
        Main_BackProce();
        //不管行走电机是否完成自己的动作，都要时刻监控行程开关，以免冲击行程
        WalkMotorControl(nWalkMotorControlParam1,nWalkMotorControlParam2) ;
        //揉捏电机完成步骤要求动作后，无论其它电机完成与否，都不再处理
        KneadMotorControl(nKneadMotorControlParam1,nKneadMotorControlParam2) ;
        //捶击电机完成步骤要求动作后，无论其它电机完成与否，都不再处理
        KnockMotorControl(nKnockMotorControlParam1,nKnockMotorControlParam2,nKnockMotorControlParam3) ;
        
        if((nBackSubRunMode == BACK_SUB_MODE_AUTO_0) || (nBackSubRunMode == BACK_SUB_MODE_AUTO_1))
         {
            Main_Axis_Proce_Old();
         }
        else
        {
            Main_Axis_Proce();
         }
        Main_Valve_Proce();
        
        MusicSampling();
        
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
                 (bKeyFlexOut == FALSE) && (bKeyFlexIn == FALSE))  
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
    Valve_OzonOff();
}
void Main_Idle(void)
{
    BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(CHAIR_STATE_IDLE == nChairRunState)
    {
      //按键处理区
        key = Main_GetKey();
        if(H10_KEY_POWER_SWITCH == key)
        {
          nChairRunState = CHAIR_STATE_WAIT_COMMAND; //按了电源键后
        }
        if(DMAUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
      //时间处理区
       if(Timer_Counter(C_TIMER_INDICATE + T_LOOP,CHAIR_STATE_IDLE))
        {
          IndicateLED_Toggle();
        }
        if(Timer_Counter(C_TIMER_TEMP,100))
        {
          nChairRunState = CHAIR_STATE_SLEEP; 
        }
       Input_Proce();
       Valve_Send_Data();
       Main_Send();
       Main_BlueToothSend();
       //Main_MassageSignalSend();
    } //end while
   /***************程序退出区**************************/
}


void _3D_test(void)
{
    int testStep = 0,/*positionLevel = 0,*/position = 0;    
    //BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(1)
    {
      //按键处理区
       // key = Main_GetKey();
        /*
        if(H10_KEY_POWER_SWITCH == key)
        {
          nChairRunState = CHAIR_STATE_WAIT_COMMAND; //按了电源键后
        }
        
        if(DMAUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
        */
     /*   
     switch(testStep) 
     {
      case 0:
        if(AxisMotor_Control(STATE_RUN_AXIS_F_BEHIND,0))
        {
          testStep++;
          Timer_Counter_Clear(C_TIMER_TEMP);
        }
        break;
      case 1:  
          if(Timer_Counter(C_TIMER_TEMP,10)) testStep++;
      case 2:
        if(AxisMotor_Control(STATE_RUN_AXIS_F_FORWARD,0))
        {
          testStep++;
          Timer_Counter_Clear(C_TIMER_TEMP);
        }
        break;  
       case 3:  
          if(Timer_Counter(C_TIMER_TEMP,10)) testStep = 0;
        break;
     }  
     */
     /*
     switch(testStep) 
    {
     default: 
     case 0:
        if(AxisMotor_Control(STATE_RUN_AXIS_POSITION,positionLevel))
        {
          testStep++;
          positionLevel++;
          positionLevel %= 5;
          Timer_Counter_Clear(C_TIMER_TEMP);
        }
        break;
      case 1:  
          if(Timer_Counter(C_TIMER_TEMP,10)) testStep = 0;
      }
     */
    switch(testStep) 
    {
     default: 
     case 0:
        if(AxisMotor_Control(STATE_RUN_AXIS_REAL_POSITION,position,AXIS_SPEED_FAST))
        {
          testStep++;
          position += 5;
          position %= 40;
          Timer_Counter_Clear(C_TIMER_TEMP);
        }
        break;
      case 1:  
          if(Timer_Counter(C_TIMER_TEMP,10)) testStep = 0;
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

/*******************************************************
按摩椅初始化程序： 3D 马达复位

********************************************************/
void Main_Initial(void)
{
    bool bMassageSignalOK = false;
//    bool bLegSignalOK = false;
    bool b3DMotorInit = false;
    
   // BYTE key;
    //变量初始化区域
    //函数初始化区域
    Power_All_On();
    Timer_Counter_Clear(C_TIMER_INDICATE);
    Timer_Counter_Clear(C_TIMER_TEMP);
    //主循环
    while(CHAIR_STATE_INITIAL == nChairRunState)
    {
      //按键处理区
    //    key = Main_GetKey();
        /*
        if(H10_KEY_POWER_SWITCH == key)
        {
          nChairRunState = CHAIR_STATE_WAIT_COMMAND; //按了电源键后
        }
        */
        if(DMAUart_GetCtrlType() == ENGGER_CTRL)
        {
            nChairRunState = CHAIR_STATE_ENGINEERING;
            return;
        }
       bMassageSignalOK = LEUART0_isOK();
       if(bMassageSignalOK) 
       {
         if(!b3DMotorInit)
         {
           if(AxisMotor_Control(STATE_RUN_AXIS_F_BEHIND,0,AXIS_SPEED_FAST))
           {
             b3DMotorInit = true;  
           }
         }
         else
         {
           AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
         }
       }
       else
       {
         AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
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
       
       if(b3DMotorInit)
       {
         nChairRunState = CHAIR_STATE_IDLE;
       }
    } //end while
   /***************程序退出区**************************/
   AxisMotor_Control(STATE_AXIS_IDLE,0,AXIS_SPEED_FAST);
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
    //Main_MassageSignalSend();
    
    if(LEUART0_isOK())
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
  }
}
/*
void _3D_Data_Test(void)
{
  int 3Dposition;
  unsigned int walkPosition ;
  unsigned int strength = 2;
  _3D_Set_3D_data();  
 for(walkPosition = 0; walkPosition++;walkPosition<300)
 {
   3Dposition =  _3D_calculate_3D_count();
   printf("%d\n\r",position);
 }
 while(1);
}
*/

void Main_Key_Test(void)
{
    char key;
    nChairRunState = CHAIR_STATE_RUN;
    while(1)
    {
      //按键处理区
        key = Main_GetKey();
        if(key != H10_KEY_NONE)
        {
          printf("key:%02x\n",key); 
        }
       Main_Send();
    } //end while
}
void Main_Voice_Test(void)
{
    char key;
    nChairRunState = CHAIR_STATE_RUN;
    while(1)
    {
      //按键处理区
        key = Main_GetKey();
        if(key != H10_KEY_NONE)
        {
          printf("key:%02x\n",key); 
        }
       Main_Send();
    } //end while
}

void main(void)
{
    Main_Initial_IO(); 
    Power_All_On();
    Main_Initial_Data();  //software initial
    nChairRunState = CHAIR_STATE_INITIAL;
    Timer_Counter_Clear(C_TIMER_TEMP);
    //Main_Key_Test();
    //Main_Voice_Test();
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
       // case CHAIR_STATE_DEMO:         Main_Demo();break;
        case CHAIR_STATE_CALIBRATION:   Main_Auto_Calibration();break;
        }
    }
}

