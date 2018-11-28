#ifndef __HAND_UART_NEW_H__
#define __HAND_UART_NEW_H__

#include "MassageStatus.h"

#define HAND_TX_PORT           gpioPortC
#define HAND_TX_BIT            6
#define HAND_TX_MODE           gpioModePushPull

#define HAND_RX_PORT           gpioPortC
#define HAND_RX_BIT            7
#define HAND_RX_MODE           gpioModeInputPull

#define BUFFER_LENGTH          32

#define PACKET_MASTER_GET_COMMAND 0x00
#define PACKET_MASTER_ACK_COMMAND 0x01
#define PACKET_MASTER_SET_STATE   0x02
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

#endif
