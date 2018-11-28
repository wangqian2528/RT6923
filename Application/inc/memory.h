
#ifndef __MEMORY_H__
#define __MEMORY_H__

/**************************���书��********************************************/
#define MEMORYB_ADDR_BASE          ((uint32_t) 0x0001d000UL)//((uint32_t) 0x0FE00200UL)
#define MEMORYA_ADDR_BASE          ((uint32_t) 0x0001e000UL)//((uint32_t)

#define  BACK_MAIN_RUN_MODE_ADDRESS 0
#define  MANSUB_MODE_ADDRESS        1        
#define  KNEAD_WIDTH_ADDRESS        2
#define  KNEADKNOCK_SPEED_ADDRESS   3
#define  AIRLOCATE_ADDRESS          4          
#define  AIR_STRENGTH_ADDRESS       5
#define  AXIS_STRENGTH_ADDRESS      6
#define  HOT_ADDRESS                7

#define  ROLLER_ENABLE_ADDRESS      8
#define  ROLLER_PWM_ADDRESS         9
#define  LEGKNEAD_ENABLE_ADDRESS    10
#define  LEGKNEAD_PWM_ADDRESS       11

#define  BACK_ANGLE_H_ADDRESS       20
#define  BACK_ANGLE_L_ADDRESS       21
#define  LEG_ANGLE_H_ADDRESS        22
#define  LEG_ANGLE_L_ADDRESS        23
#define  WALK_MODE_ADDRESS          24
#define  WALK_POSITION_TOP_H_ADDRESS      25
#define  WALK_POSITION_TOP_L_ADDRESS      26
#define  WALK_POSITION_BOTTOM_H_ADDRESS   27
#define  WALK_POSITION_BOTTOM_L_ADDRESS   28



/****************************** END *******************************************/




#define MEMORY_LENGTH 13
//#define PRODUCT_ID_ADDR         ((uint32_t) (128*1024-5)) //((uint32_t) 0x0000FFFBUL) 
#define USER_DATA_BASE          ((uint32_t) 0x0FE00000UL)  /**< user data flash base address  */

//���µ�ַ�ǰ����ֽڴ��
#define SOFT_MAIN_VER_ADDRESS         0
#define SOFT_SECONDARY_VER_ADDRESS    1
#define SETTLE_ADDRESS                2  //��Ħ����Ƿ�λ ����Ϊ1��λ
#define AIRBAG_STRETCH_ADDRESS        3   //��Ħ���ڲ���������
#define SLIDE_MOTOR_ENABLE_ADDRESS    4   //�������ʹ�����ֹ
#define PROGRAM_ENABLE_ADDRESS        5   //����������ַ
#define DEFAULT_TIME_ADDRESS          6   //����Ĭ��ʱ���ַ
#define BLUETOOTH_STATUS_ADDRESS      7   //��������״̬
#define REST_SLEEP_MODE_ADDRESS       8
#define LANGUAGE_ADDRESS              9   //����״̬
//#define ARM_MOTOR_SWITCH_ADDRESS      10
#define DEMO_RUN_ON     0x5A

#define ACC_TIME_0_ADDRESS  0x10
#define ACC_TIME_1_ADDRESS  0x11
#define ACC_TIME_2_ADDRESS  0x12
#define ACC_TIME_3_ADDRESS  0x13

#define MEMORY_LENGTH_OF_BYTES      14
#define PROGRAM_FLAG               'p'
#define PROGRAM_BY_BLUETOOTH_FLAG  'l'

#define REST_SLEEP_DEFAULT     0// 1 30MIN; 0 20MIN
//2.2 ���Ӹ�λʱ�����������ֹͣ
//   �����綯����С�ȵ��������ֶ�ʱΪ3A�ڸ�λʱΪ2A
#define SOFT_MAIN_VER          1
#define SOFT_SECONDARY_VER     1// 1.00    6923�����汾1.01
//1.16  ���� С�� ���� ǰ�� �������Ĺ�����ѹ��24V ���Ӽ��ܳ��� �޸����ػ�ʱ�ٿ�������������





//------------------------����������
void xmodem(unsigned int start_addr,unsigned char *pw_Buffer ,int numBytes);
void Mem_Erase_Block(unsigned int start_addr);
void MEM_Write_Block(unsigned int start_addr,unsigned char *pw_Buffer ,int numBytes);
void MEM_Initial(void);
void MEMORYA_Write_Memory(PUINT32 pw_Buffer,int numBytes,uint32_t ADDR);
unsigned int Get_FlashPageSize(void);

//-------------------------------------------------------
/*
0: ��ʶID
1: ��ʶID
2: ����ǿ��
3: ����ǿ��
4: �ػ���λ
*************************************/
#define MEMORY_DEFAULT_AIR     1 //0,1,2
#define MEMORY_DEFAULT_SETTLE  0 //0: ���н����ػ�����λ,1:���н����ػ���λ
#define SLIDE_DEFAULT_ENABLE   1 //����״̬ 5Ϊ�г̿���
#define BLUETOOTH_STATUS_DEFAULT  1  //1 Ϊ�� 0Ϊ��
//#define ARM_DEFAULT_DISABLE       0 //������������Ĭ���ǹر�״̬
unsigned char ReadEEByte(unsigned int nAddress);
void MEM_Write_Memory(PUINT32 pw_Buffer,int numBytes);
void MEM_Read_Memory(PUINT32 pw_Buffer,int numBytes);
#endif