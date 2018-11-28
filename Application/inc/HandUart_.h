#include "MassageStatus.h"
/*
#define UART0_TX_PORT           gpioPortC
#define UART0_TX_BIT           12// 14
#define UART0_TX_MODE           gpioModePushPull

#define UART0_RX_PORT           gpioPortC
#define UART0_RX_BIT          13//  15
#define UART0_RX_MODE           gpioModeInputPull
*/

#define HAND_TX_PORT           gpioPortC
#define HAND_TX_BIT           12// 14
#define HAND_TX_MODE           gpioModePushPull

#define HAND_RX_PORT           gpioPortC
#define HAND_RX_BIT          13//  15
#define HAND_RX_MODE           gpioModeInputPull


//uart0 location 3
//#define DMAUART_UART              UART0
//#define DMAUART_CLK               cmuClock_UART0
//#define DMAUART_RX                UART_Rx
//#define DMAUART_LOCATION          UART_ROUTE_LOCATION_LOC3

//#define DMAUART_IRQn              UART0_RX_IRQn

#define BUFFER_LENGTH             32
/*
#ifdef RT8301_CONTROL 
  #define SOI			0x7e
  #define EOI			0x0d
#else
  #define SOI                    0XF0
  #define EOI                    0XF1
#endif
*/
//Master->Slave Packet Type
#define PACKET_MASTER_GET_COMMAND 0x00
#define PACKET_MASTER_ACK_COMMAND 0x01
#define PACKET_MASTER_SET_STATE   0x02
//Slave->Master Packet Type
#define PACKET_SLAVE_SEND_COMMAND 0x03

void HAND_Initial_IO(void);
void uartPutData(unsigned char* dataPtr, unsigned int dataLen);
unsigned int uartGetData(unsigned char* dataPtr, unsigned int dataLen);
void HandUart_Transmit_Packet(unsigned char* buf,unsigned int length);
unsigned char HandUart_GetRXStatus(void);
unsigned char HandUart_GetKey(void);
void DMAUart_SetKey(unsigned char by_Data);
unsigned char HandUart_GetExternKey(void);
void HandUart_ClearRXStatus(void);
unsigned int HandUart_GetCtrlType(void);
void HandUart_SetKey(unsigned char by_Data);
