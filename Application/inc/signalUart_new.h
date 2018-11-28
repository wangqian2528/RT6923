#ifndef  __SIGNAL_BOARD_UART_H__
#define  __SIGNAL_BOARD_UART_H__

#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_dma.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"
#include "string.h"


#define BUFFER_LENGTH                  32

//Master->Slave Packet Type
#define PACKET_MASTER_GET_COMMAND 0x00
#define PACKET_MASTER_ACK_COMMAND 0x01
#define PACKET_MASTER_SET_STATE   0x02
//Slave->Master Packet Type
#define PACKET_SLAVE_SEND_COMMAND 0x03

void SignalBoard_Initial_IO(void);

void SignalBoard_Initial_Data(void);

void SignalBoard_10msInt(void);
bool SignalBoard_isOK(void);

unsigned char SignalBoard_GetMassageSignal(void);
unsigned char SignalBoard_GetSwitchSignal(void);
unsigned char SignalBoard_GetSwitchFlexSignal(void);

#endif

