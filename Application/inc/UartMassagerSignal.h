#ifndef __UART_LEG_H__
#define __UART_LEG_H__
//rx
#define UART_MASSAGER_SIGNAL_RX_PORT           gpioPortE
#define UART_MASSAGER_SIGNAL_RX_BIT            11
#define UART_MASSAGER_SIGNAL_RX_MODE           gpioModeInputPull
//tx
#define UART_MASSAGER_SIGNAL_TX_PORT           gpioPortE
#define UART_MASSAGER_SIGNAL_TX_BIT            10
#define UART_MASSAGER_SIGNAL_TX_MODE           gpioModeInputPull
void UartMassageSignal_Initial_IO(void);
void UartMassageSignal_Transmit_Packet(unsigned char* buf,unsigned int length);
unsigned char UartMassageSignal_GetRXStatus(void);
void UartMassageSignal_ClearRXStatus(void);
//ucRXBuffer[3]:存放高7位数据
//ucRXBuffer[2]:存放低7位数据
unsigned short UartMassageSignal_GetWalkPluse(void);
//ucRXBuffer[1]:存放3D脉冲
unsigned char UartMassageSignal_Get3DPluse(void);
//ucRXBuffer[0]:存放低7位数据
unsigned char UartMassageSignal_GetSignal(void);
#endif