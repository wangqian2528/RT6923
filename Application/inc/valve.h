#ifndef __VALVE_H__
#define __VALVE_H__
#include "efm32_def.h"
#include "efm32_types.h"
#define PUMP_ON				0
#define PUMP_OFF			1
#define VALVE_ON			1
#define VALVE_OFF			0

#define VALVE_DISABLE 0
#define VALVE_ENABLE  1

//0-20位为气囊和气泵
#define F_L_SIDE		0x00000001UL
#define F_R_SIDE		0x00000002UL
#define F_HEEL		        0x00000004UL
#define LEG_LEFT                0x00000008UL
#define LEG_RIGHT               0x00000010UL
#define R_ARM_1	                0x00000020UL
#define R_ARM_2     	        0x00000040UL
#define R_ARM_3	                0x00000080UL
#define L_ARM_1	                0x00000100UL
#define L_ARM_2	                0x00000200UL
#define L_ARM_3	                0x00000400UL
#define LEFT_ARM_1_CHR    L_ARM_1
#define LEFT_ARM_2_CHR    L_ARM_2
#define LEFT_ARM_3_CHR    L_ARM_3
#define RIGHT_ARM_1_CHR   R_ARM_1
#define RIGHT_ARM_2_CHR   R_ARM_2
#define RIGHT_ARM_3_CHR   R_ARM_3
#define PE1	                0x00000800UL//背腰和臂肩
#define PE_ARM                  PE1
#define PE2	                0x00001000UL//小腿和大腿
#define R_U_WAIST	        0x00002000UL
#define R_D_WAIST	        0x00004000UL
#define L_U_WAIST	        0x00008000UL
#define L_D_WAIST	        0x00010000UL
#define R_SHOLDER	        0x00020000UL
#define L_SHOLDER	        0x00040000UL
#define LEFT_SHOULDER_CHR       L_SHOLDER
#define RIGHT_SHOULDER_CHR      R_SHOLDER
#define R_THIGH	                0x00080000UL
#define L_THIGH	                0x00100000UL


//#define F_R_SIDE		0x00000001UL
//#define F_L_SIDE		0x00000002UL
//#define F_HEEL		        0x00000004UL
//#define LEG_LEFT                   0x00000008UL
//#define LEG_RIGHT                   0x00000010UL
//#define HAND_PALM_R            0x00000020UL //手3_肘左
//#define LEG_CALF_U             0x00000040UL //小腿上底
//#define HAND_ELBOW_R           0x00000080UL //手1_掌左
//#define HAND_PALM_L            0x00000100UL //手3_肘右
//#define LEG_CALF_D             0x00000200UL //小腿下底
//#define HAND_ELBOW_L           0x00000400UL //手1_掌右
//#define PE1	                0x00000800UL//背腰和臂肩
//#define PE2	                0x00001000UL//小腿和大腿
//#define R_U_WAIST	        0x00002000UL
//#define R_D_WAIST	        0x00004000UL
//#define L_U_WAIST	        0x00008000UL
//#define L_D_WAIST	        0x00010000UL
//#define R_SHOLDER	        0x00020000UL
//#define L_SHOLDER	        0x00040000UL
//#define R_THIGH	                0x00080000UL
//#define L_THIGH	                0x00100000UL
//
//#define LEFT_ARM_1_CHR    HAND_PALM_L
//#define LEFT_ARM_3_CHR    HAND_ELBOW_L
//#define RIGHT_ARM_1_CHR   HAND_PALM_R
//#define RIGHT_ARM_3_CHR   HAND_ELBOW_R
//#define PE_ARM                  PE1
//
//#define LEFT_SHOULDER_CHR       L_SHOLDER
//#define RIGHT_SHOULDER_CHR      R_SHOLDER
//
//#define LEG_U                   LEG_RIGHT
//#define LEG_D                   LEG_LEFT

#define ARM_MOTOR_HOLD  (0x00<<21)
#define ARM_MOTOR_DOWN  (0x01<<21)
#define ARM_MOTOR_UP    (0x02<<21)
#define ARM_MOTOR_STOP  (0x04<<21)
//21-24位为滚轮旋转方式
/*  
0-1位为揉搓速度 00 停止 01 慢速 10 中速 11 高速
2-3位为揉搓方式 00向里旋转 01向外旋转 10 摇摆
*/

//#define KNEAD_LEG_STOP        (0x00<<21)//0b00000000   
//#define KNEAD_SLOW_IN         (0x01<<21)//0b00000001   
//#define KNEAD_SLOW_OUT        (0x05<<21)//0b00000101   
//#define KNEAD_SLOW_SWAY       (0x09<<21)//0b00001001   
//#define KNEAD_MID_IN          (0x02<<21)//0b00000010   
//#define KNEAD_MID_OUT         (0x06<<21)//0b00000110   
//#define KNEAD_MID_SWAY        (0x0A<<21)//0b00001010   
//#define KNEAD_FAST_IN         (0x03<<21)//0b00000011   
//#define KNEAD_FAST_OUT        (0x07<<21)//0b00000111   
//#define KNEAD_FAST_SWAY       (0x0B<<21)//0b00001011  
//#define ROLLER_MID_CON	  0x0e000000
//#define ROLLER_SLOW_CON	  0x0d000000//0b00001101
//#define ROLLER_FAST_CON	  0x0f000000//0b00001111

//25-26位为滚轮旋转速度
/*0-1位为滚轮速度 00 停止 01 慢速 10 中速 11 高速*/
#define ROLLER_STOP	          (0x00<<25)
#define ROLLER_SLOW	          (0x01<<25)
#define ROLLER_MID	          (0x02<<25)
#define ROLLER_FAST	          (0x03<<25)
//27-29位为滚轮旋转方式
/*  
000 连续向里旋转
001 连续向外旋转
010 短间歇向里
011 短间歇向外
100 长间歇向里
101 长间歇向外
110 短行程搓脚
111 长行程搓脚
*/
#define ROLLER_CON_IN	          (0x00<<27)//连续正转
#define ROLLER_CON_OUT	          (0x01<<27)//连续反转
#define ROLLER_S_INT_IN	          (0x02<<27)//正向转1s停1s
#define ROLLER_S_INT_OUT	      (0x03<<27)//反向转1s停1s
#define ROLLER_L_INT_IN	          (0x04<<27)//正向转3s停3s
#define ROLLER_L_INT_OUT	      (0x05<<27)//反向转3s停3s
#define ROLLER_S_RUB	          (0x06<<27)//正向转1s反向转1s
#define ROLLER_L_RUB	          (0x07<<27)//正向转3s反向转3s


#define ROLLER_INTERMITTENT_TIME      40
#define ROLLER_INTERMITTENT_ON_TIME   10
#define ROLLER_SEMI_CIRCLE_TIME       80
#define ROLLER_SEMI_CIRCLE_ON_TIME    30
//28-31位为滚轮旋转方式
#define STRETCH_STOP		0x00000000  //0b0000 0000 靠背
#define STRETCH_UP		0x10000000  //0b0001 0000靠背后躺，小腿上升，一直到小腿上升到最高点
#define STRETCH_DOWN		0x20000000  //0b0010 0000靠背不动，小腿下降，一直到小腿下降到最低点 
#define STRETCH_RESET   	0x30000000  //0b0011 0000靠背回到一定角度，小腿不动 

#define ALL_DIS			0x00000000

#define VALVE_CLK_PORT               gpioPortE
#define VALVE_CLK_BIT                5
#define VALVE_CLK_MODE               gpioModePushPull

#define VALVE_LATCH_PORT             gpioPortE   //DRV8804 latch 
#define VALVE_LATCH_BIT              4
#define VALVE_LATCH_MODE             gpioModePushPull

#define VALVE_DATA_PORT              gpioPortE   //drv8804 serial data in SPI MOSI
#define VALVE_DATA_BIT               7
#define VALVE_DATA_MODE              gpioModePushPull

//----------------------------------------------------------------
#define VALVE_SPI                    USART0
#define VALVE_SPI_ROUTE_LOCAITON     USART_ROUTE_LOCATION_LOC1
#define VALVE_CMU_SPI                cmuClock_USART0     


#define VALVE_AIRPUMP1_PORT        gpioPortD  
#define VALVE_AIRPUMP1_BIT         8
#define VALVE_AIRPUMP1_MODE          gpioModePushPull

#define VALVE_AIRPUMP2_PORT		gpioPortE  //有效气囊
#define VALVE_AIRPUMP2_BIT		0
#define VALVE_AIRPUMP2_MODE		gpioModePushPull

extern BITS BITS_ValveData[3] ;

#define bLeftArmUpAirBagValve1		BITS_ValveData[0].bD0  
#define bLeftArmUpAirBagValve2		BITS_ValveData[0].bD1   
#define bLeftArmUpAirBagValve3		BITS_ValveData[0].bD2   
#define bLeftSholderAirBagValve	        BITS_ValveData[0].bD3   
#define bValveData1NC0        	        BITS_ValveData[0].bD4   
#define bBackWaistLeftUp		BITS_ValveData[0].bD5   
#define bBackWaistLeftDown		BITS_ValveData[0].bD6  
#define bBackWaistRightUp          	BITS_ValveData[0].bD7   
//气阀位变量定义
#define bLegLeftAirBagValve             BITS_ValveData[1].bD0 
#define bLegRightAirBagValve            BITS_ValveData[1].bD1  
#define bBackWaistRightDown                  BITS_ValveData[1].bD2  
#define bValveData1NC1 	                BITS_ValveData[1].bD3  
#define bValveData1NC2 	                BITS_ValveData[1].bD4  
#define bFootHeelAirBagValve            BITS_ValveData[1].bD5  
#define bLeftFootAirBagValve            BITS_ValveData[1].bD6  
#define bRightFootAirBagValve           BITS_ValveData[1].bD7  
//气阀位变量定义
#define bValveData1NC3                  BITS_ValveData[2].bD0  
#define bValveData1NC4                  BITS_ValveData[2].bD1 
#define bRightThighAirBagValve   	BITS_ValveData[2].bD2  
#define bLeftThighAirBagValve		BITS_ValveData[2].bD3  
#define bRightArmUpAirBagValve1	        BITS_ValveData[2].bD4  
#define bRightArmUpAirBagValve2         BITS_ValveData[2].bD5  
#define bRightArmUpAirBagValve3         BITS_ValveData[2].bD6  
#define bRightSholderAirBagValve        BITS_ValveData[2].bD7 



struct AirBagStruct
{
    UINT32 nPumpValveState ;//气泵和气阀的状态
    unsigned char nKeepTime1 ;//当前状态保持时间,对应弱力度
    unsigned char nKeepTime2 ;//当前状态保持时间,对应中力度
    unsigned char nKeepTime3 ;//当前状态保持时间,对应强力度
};

#define STRETCH_MODE_TIME   1 //拉退模式 1为时间控制
#define STRETCH_MODE_SWITCH 0 //拉退模式为行程控制

typedef struct
{
    unsigned char timer;        //拉退程序计时定时器，单位0.1s
    unsigned char step ;        //拉退程序步骤
    unsigned char bBackLegFlag; //拉退程序中电动缸的状态
    unsigned char active;
    unsigned char init;
    unsigned char times;        //拉退程序循环次数
    unsigned char mode;         //拉退模式 1为时间控制 0为行程控制
    unsigned char PresetTime;   //拉退模式为时间控制时的预设时间，单位0.1秒
}StretchStruct;

typedef struct
{
    unsigned char time;        //拉退程序执行时间
    unsigned char times;       //一个回合的拉退次数 一般为3次
    unsigned char mode;        //拉退模式 STRETCH_GO_OUT向前拉 STRETCH_GO_DOWN向下拉
}StretchProgramStruct;

#define C_Stretch_Up    1
#define C_Stretch_Stop  2
#define C_STRETCH_HOLD_TIME   30 //单位0.1s
#define C_STRETCH_RESET_TIME  100 //单位0.1s
#define C_STRETCH_CHARGE_TIME 60 //单位0.1s

#define VALVE_USART_INITSYNC                                                                  \
    {                                                                                             \
        usartEnable,       /* Enable RX/TX when init completed. */                                \
        0,                 /* Use current configured reference clock for configuring baudrate. */ \
        200000,           /* 1 Mbits/s. */                                                       \
        usartDatabits8,    /* 8 databits. */                                                      \
        true,              /* Master mode. */                                                     \
        true,              /* Send least significant bit first. */                                 \
        usartClockMode0    /* Clock idle low, sample on rising edge. */                           \
    }
/*
#define AIRBAG_LOCATE_NONE            0
#define AIRBAG_LOCATE_LEG_FOOT        1
#define AIRBAG_LOCATE_BACK_WAIST      2
#define AIRBAG_LOCATE_ARM_SHOLDER     3
#define AIRBAG_LOCATE_SEAT            4
#define AIRBAG_LOCATE_AUTO            5
#define AIRBAG_LOCATE_ARM             6

#define AIRBAG_LOCATE_ARM_SHOLDER_WAIST   7
#define AIRBAG_LOCATE_LEG_FOOT_SEAT       8
*/

#define AIRBAG_LOCATE_NONE            0x0
#define AIRBAG_LOCATE_LEG_FOOT        0x01
#define AIRBAG_LOCATE_BACK_WAIST      0x02
#define AIRBAG_LOCATE_ARM_SHOLDER     0x04//0x04
#define AIRBAG_LOCATE_SEAT            0x08//0x08
#define AIRBAG_LOCATE_AUTO            0x10//0x10
#define AIRBAG_LOCATE_ARM             17

#define AIRBAG_LOCATE_ARM_SHOLDER_WAIST   18
#define AIRBAG_LOCATE_LEG_FOOT_SEAT       19


#define AIRBAG_LOCATE_SEAT_WAIST     0x0A



typedef struct
{
    unsigned char init; 
    unsigned char active; 
    unsigned char nCurAirBagStep;
    unsigned char nCurKeepTime1;
    unsigned char nCurKeepTime2; 
    unsigned char nCurKeepTime3; 
    unsigned char nCurKeepTime4;
    unsigned char nCurKeepTime5; 
    const struct AirBagStruct * pAirBagArray;
    UINT32 nCurPumpValveState;
    UINT16 nTotalSteps;
    unsigned char nAirBagCounter ;
    unsigned char locate ;
}st_AirBag;                                               


struct WaveMotorStruct
{
    unsigned char speed;   //摇摆马达速度 0-3
    unsigned int  time;    //摇摆马达持续时间 单位1sec  
};

extern unsigned char* pValveData;
extern unsigned char* pInputData;

extern unsigned char LegKneadSpeed;

void Valve_Initial_IO(void);
//void Valve_Send_Data(unsigned char * ucData,unsigned char ucLength);
//void Valve_Send_Data(unsigned char * ucSendData,unsigned char * ucReceiveData,unsigned char ucLength);
void Valve_Send_Data(void);
void Valve_10ms_Int(void);
void Valve_SetData(void);
void Valve_ClearData(void);
void Valve_SetClock(void);
void Valve_ClearClock(void);
void Valve_ClearLatch(void);
void Valve_SetLatch(void);

void Valve_LegFootAirPumpACPowerOn(void);
void Valve_LegFootAirPumpACPowerOff(void);
void Valve_BodyUpAirPumpACPowerOn(void);
void Valve_BodyUpAirPumpACPowerOff(void);
//void Valve_ArmAirPumpACPowerOn(void);
//void Valve_ArmAirPumpACPowerOff(void);
unsigned char Valve_GetAirBagStrength(void);
void Valve_SetAirBagStrength(unsigned char strength);
void Valve_AddAirBagStrength(void);

void Valve_FootRollerProce(unsigned char bRollerEnable,unsigned char Valve_Enable,st_AirBag* pBag);
//void Valve_LegKneadProce(unsigned char bLegKneadEnable,unsigned char Valve_Enable,st_AirBag* pBag);
void Valve_SetRollerPWM(unsigned char level);

void Valve_SetStretchUp(void);
void Valve_SetStretchCharge(unsigned int start);
void Valve_SetStretchHold(void);

void Valve_Test_Set_Data(unsigned int ValveTestData);

void Valve_Control(unsigned char nAirBagSwitch,st_AirBag* pBag,unsigned char level);

unsigned char Valve_Level_Decrease(unsigned char by_Data);
unsigned char Valve_Level_Increase(unsigned char by_Data);

void Valve_SetEnableSholder(unsigned int enable);
void Valve_1ms_Int(void);
//unsigned char Valve_GetRollerLevel(void);
void Valve_SetBackMode(int backauto);
void Valve_Initial_Data(void);
void Valve_CloseAll(void);  

void  Valve_OzonOn(void);
void  Valve_OzonOff(void);
unsigned char Valve_GetRollerLevel(void);
void Valve_SetStretchChargeOut(unsigned int start);

int Valve_RollerIsAuto(void);
void Valve_SetStretchChargeATOUT(unsigned int start);
void Valve_SetStretchChargeATOUT2(unsigned int start);


void Valve_SetStretchChargeATOUTFootHeelOFF(unsigned int start);
void Valve_SetStretchChargedown(unsigned int start);
void Valve_SetStretchHoldHeelOFF(void);
void Valve_SetStretchHoldHeelSCONDOFF(void);
unsigned char Valve_GetLegKneadSpeed(void);
//void Valve_SetLegKneadSpeed(unsigned char speed);

void ArmSholderAirBagAction(bool Enable,unsigned int action);
void SeatAirBagAction(bool Enable,unsigned int action);
void Valve_Alone();

extern uint8_t nValveAlone;
extern uint16_t nValveAloneTime;

void Valve_SetStretchCharge_FOOT(unsigned int start);
void Valve_SetStretchChargeSTEEL(unsigned int start);

#endif
