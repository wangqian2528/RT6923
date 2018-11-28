#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__
#include "MassageStatus.h"

#define BlueTooth_TX_PORT           gpioPortC
#define BlueTooth_TX_BIT            2
#define BlueTooth_TX_MODE           gpioModePushPull

#define BlueTooth_RX_PORT           gpioPortC
#define BlueTooth_RX_BIT            3
#define BlueTooth_RX_MODE           gpioModeInputPull

#define BlueTooth_IO1_PORT          gpioPortC
#define BlueTooth_IO1_BIT           4
#define BlueTooth_IO1_MODE          gpioModePushPull

#define BlueTooth_IO2_PORT          1//gpioPortC
#define BlueTooth_IO2_BIT           5
#define BlueTooth_IO2_MODE          gpioModePushPull

#define BlueTooth_IO3_PORT          1//gpioPortB
#define BlueTooth_IO3_BIT           6
#define BlueTooth_IO3_MODE          gpioModePushPull

/*
#ifdef RT8600S
	#define BlueTooth_Volum_PORT          gpioPortB
	#define BlueTooth_Volum_BIT           1
	#define BlueTooth_Volum_MODE          gpioModeInput
	//BlueTooth's Switch Port=蓝牙供电开关 =0=给蓝牙供电
	
	//BlueTooth's Switch Po
	#define BlueTooth_MUTE_PORT         gpioPortF
	#define BlueTooth_MUTE_BIT          3
	#define BlueTooth_MUTE_MODE         gpioModePushPull
	#define BlueTooth_MUTE_INIT_ON      0
	
#else */
	
//	#define BlueTooth_Volum_PORT          gpioPortC//D
//	#define BlueTooth_Volum_BIT          4// 0
//	#define BlueTooth_Volum_MODE          gpioModeInput
	
	//BlueTooth's Switch Port=蓝牙供电开关 =0=给蓝牙供电
	#define BlueTooth_MUTE_PORT         gpioPortF//E
	#define BlueTooth_MUTE_BIT         4// 11
	#define BlueTooth_MUTE_MODE         gpioModePushPull
	#define BlueTooth_MUTE_INIT_ON      0


//#endif



#define BlueTooth_UART              USART2
#define BlueTooth_CLK               cmuClock_USART2
#define BlueTooth_RX                USART_Rx
#define BlueTooth_LOCATION          USART_ROUTE_LOCATION_LOC0

#define DMAUART_IRQn              USART2_RX_IRQn

#define BlueTooth_SOI                0XF0
#define BlueTooth_EOI                0XF1
//Master->Slave Packet Type
#define PACKET_MASTER_GET_COMMAND 0x00
#define PACKET_MASTER_ACK_COMMAND 0x01
#define PACKET_MASTER_SET_STATE   0x02
//Slave->Master Packet Type
#define PACKET_SLAVE_SEND_COMMAND 0x03

//BlueTooth'mute pin State
#define BlueTooth_Speak_Out_On          0
#define BlueTooth_Speak_Out_Off         1
#define BlueTooth_MutePin_Value         0xef    //将第四位，即是输出Buffer的第4位清零

void BlueToothUart_Initial_IO(void);
void BlueToothUart_Transmit_Packet(unsigned char* buf,unsigned int length);
unsigned char BlueToothUart_GetRXStatus(void);
unsigned char BlueToothUart_GetKey(void);
void BlueToothUart_SetKey(unsigned char by_Data);
void BlueToothUart_ClearRXStatus(void);
unsigned int BlueToothUart_GetCtrlType(void);
unsigned char BlueToothMuteState(void);
void BlueToothOff(void);
void BlueToothOn(void);

void BlueToothUart_GetModlueName(unsigned char* str);
void BlueToothUart_10ms_Int(void);
void BlueToothUart_AMP_Volume_On(void);
void BlueToothUart_AMP_Volume_Off(void);



#endif // __BLUETOOTH_H__