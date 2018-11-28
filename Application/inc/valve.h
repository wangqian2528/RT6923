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

//0-20λΪ���Һ�����
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
#define PE1	                0x00000800UL//�����ͱۼ�
#define PE_ARM                  PE1
#define PE2	                0x00001000UL//С�Ⱥʹ���
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
//#define HAND_PALM_R            0x00000020UL //��3_����
//#define LEG_CALF_U             0x00000040UL //С���ϵ�
//#define HAND_ELBOW_R           0x00000080UL //��1_����
//#define HAND_PALM_L            0x00000100UL //��3_����
//#define LEG_CALF_D             0x00000200UL //С���µ�
//#define HAND_ELBOW_L           0x00000400UL //��1_����
//#define PE1	                0x00000800UL//�����ͱۼ�
//#define PE2	                0x00001000UL//С�Ⱥʹ���
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
//21-24λΪ������ת��ʽ
/*  
0-1λΪ����ٶ� 00 ֹͣ 01 ���� 10 ���� 11 ����
2-3λΪ��귽ʽ 00������ת 01������ת 10 ҡ��
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

//25-26λΪ������ת�ٶ�
/*0-1λΪ�����ٶ� 00 ֹͣ 01 ���� 10 ���� 11 ����*/
#define ROLLER_STOP	          (0x00<<25)
#define ROLLER_SLOW	          (0x01<<25)
#define ROLLER_MID	          (0x02<<25)
#define ROLLER_FAST	          (0x03<<25)
//27-29λΪ������ת��ʽ
/*  
000 ����������ת
001 ����������ת
010 �̼�Ъ����
011 �̼�Ъ����
100 ����Ъ����
101 ����Ъ����
110 ���г̴��
111 ���г̴��
*/
#define ROLLER_CON_IN	          (0x00<<27)//������ת
#define ROLLER_CON_OUT	          (0x01<<27)//������ת
#define ROLLER_S_INT_IN	          (0x02<<27)//����ת1sͣ1s
#define ROLLER_S_INT_OUT	      (0x03<<27)//����ת1sͣ1s
#define ROLLER_L_INT_IN	          (0x04<<27)//����ת3sͣ3s
#define ROLLER_L_INT_OUT	      (0x05<<27)//����ת3sͣ3s
#define ROLLER_S_RUB	          (0x06<<27)//����ת1s����ת1s
#define ROLLER_L_RUB	          (0x07<<27)//����ת3s����ת3s


#define ROLLER_INTERMITTENT_TIME      40
#define ROLLER_INTERMITTENT_ON_TIME   10
#define ROLLER_SEMI_CIRCLE_TIME       80
#define ROLLER_SEMI_CIRCLE_ON_TIME    30
//28-31λΪ������ת��ʽ
#define STRETCH_STOP		0x00000000  //0b0000 0000 ����
#define STRETCH_UP		0x10000000  //0b0001 0000�������ɣ�С��������һֱ��С����������ߵ�
#define STRETCH_DOWN		0x20000000  //0b0010 0000����������С���½���һֱ��С���½�����͵� 
#define STRETCH_RESET   	0x30000000  //0b0011 0000�����ص�һ���Ƕȣ�С�Ȳ��� 

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

#define VALVE_AIRPUMP2_PORT		gpioPortE  //��Ч����
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
//����λ��������
#define bLegLeftAirBagValve             BITS_ValveData[1].bD0 
#define bLegRightAirBagValve            BITS_ValveData[1].bD1  
#define bBackWaistRightDown                  BITS_ValveData[1].bD2  
#define bValveData1NC1 	                BITS_ValveData[1].bD3  
#define bValveData1NC2 	                BITS_ValveData[1].bD4  
#define bFootHeelAirBagValve            BITS_ValveData[1].bD5  
#define bLeftFootAirBagValve            BITS_ValveData[1].bD6  
#define bRightFootAirBagValve           BITS_ValveData[1].bD7  
//����λ��������
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
    UINT32 nPumpValveState ;//���ú�������״̬
    unsigned char nKeepTime1 ;//��ǰ״̬����ʱ��,��Ӧ������
    unsigned char nKeepTime2 ;//��ǰ״̬����ʱ��,��Ӧ������
    unsigned char nKeepTime3 ;//��ǰ״̬����ʱ��,��Ӧǿ����
};

#define STRETCH_MODE_TIME   1 //����ģʽ 1Ϊʱ�����
#define STRETCH_MODE_SWITCH 0 //����ģʽΪ�г̿���

typedef struct
{
    unsigned char timer;        //���˳����ʱ��ʱ������λ0.1s
    unsigned char step ;        //���˳�����
    unsigned char bBackLegFlag; //���˳����е綯�׵�״̬
    unsigned char active;
    unsigned char init;
    unsigned char times;        //���˳���ѭ������
    unsigned char mode;         //����ģʽ 1Ϊʱ����� 0Ϊ�г̿���
    unsigned char PresetTime;   //����ģʽΪʱ�����ʱ��Ԥ��ʱ�䣬��λ0.1��
}StretchStruct;

typedef struct
{
    unsigned char time;        //���˳���ִ��ʱ��
    unsigned char times;       //һ���غϵ����˴��� һ��Ϊ3��
    unsigned char mode;        //����ģʽ STRETCH_GO_OUT��ǰ�� STRETCH_GO_DOWN������
}StretchProgramStruct;

#define C_Stretch_Up    1
#define C_Stretch_Stop  2
#define C_STRETCH_HOLD_TIME   30 //��λ0.1s
#define C_STRETCH_RESET_TIME  100 //��λ0.1s
#define C_STRETCH_CHARGE_TIME 60 //��λ0.1s

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
    unsigned char speed;   //ҡ������ٶ� 0-3
    unsigned int  time;    //ҡ��������ʱ�� ��λ1sec  
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
