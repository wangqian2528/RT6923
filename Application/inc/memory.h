
#ifndef __MEMORY_H__
#define __MEMORY_H__

/**************************记忆功能********************************************/
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

//以下地址是按照字节存放
#define SOFT_MAIN_VER_ADDRESS         0
#define SOFT_SECONDARY_VER_ADDRESS    1
#define SETTLE_ADDRESS                2  //按摩完成是否复位 数据为1复位
#define AIRBAG_STRETCH_ADDRESS        3   //按摩椅内部气囊力度
#define SLIDE_MOTOR_ENABLE_ADDRESS    4   //滑动马达使能与禁止
#define PROGRAM_ENABLE_ADDRESS        5   //程序升级地址
#define DEFAULT_TIME_ADDRESS          6   //程序默认时间地址
#define BLUETOOTH_STATUS_ADDRESS      7   //程序蓝牙状态
#define REST_SLEEP_MODE_ADDRESS       8
#define LANGUAGE_ADDRESS              9   //语言状态
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
//2.2 增加复位时按任意键可以停止
//   调整电动伸缩小腿的力度在手动时为3A在复位时为2A
#define SOFT_MAIN_VER          1
#define SOFT_SECONDARY_VER     1// 1.00    6923量产版本1.01
//1.16  靠背 小腿 行走 前滑 调整马达的工作电压到24V 增加加密程序 修复急关机时再开机抖动的问题





//------------------------云养程序区
void xmodem(unsigned int start_addr,unsigned char *pw_Buffer ,int numBytes);
void Mem_Erase_Block(unsigned int start_addr);
void MEM_Write_Block(unsigned int start_addr,unsigned char *pw_Buffer ,int numBytes);
void MEM_Initial(void);
void MEMORYA_Write_Memory(PUINT32 pw_Buffer,int numBytes,uint32_t ADDR);
unsigned int Get_FlashPageSize(void);

//-------------------------------------------------------
/*
0: 标识ID
1: 标识ID
2: 气囊强度
3: 拉退强度
4: 关机回位
*************************************/
#define MEMORY_DEFAULT_AIR     1 //0,1,2
#define MEMORY_DEFAULT_SETTLE  0 //0: 运行结束关机不复位,1:运行结束关机复位
#define SLIDE_DEFAULT_ENABLE   1 //拉退状态 5为行程开关
#define BLUETOOTH_STATUS_DEFAULT  1  //1 为开 0为关
//#define ARM_DEFAULT_DISABLE       0 //开机扶手扩张默认是关闭状态
unsigned char ReadEEByte(unsigned int nAddress);
void MEM_Write_Memory(PUINT32 pw_Buffer,int numBytes);
void MEM_Read_Memory(PUINT32 pw_Buffer,int numBytes);
#endif