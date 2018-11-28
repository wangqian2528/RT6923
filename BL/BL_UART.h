#ifndef __BL_UART_H__
#define __BL_UART_H__

#include "BL_Config.h"

#define BL_START_BYTE  0x2B
#define BL_END_BYTE    0x03
#define BL_ESC_BYTE    0x10

#define BL_RAM_BUFFER_SIZE   512
#define BL_WAIT_REPLY_TIME   10 //1000ms

typedef enum{BL_RStart,BL_RLength,BL_RCommd,BL_RStatus,BL_RData,BL_RCRC,BL_REND,BL_RIDLE}   BL_RX_STATE;
typedef enum{BL_DStart,BL_DLength,BL_DCommd,BL_DData,BL_DCRC,BL_DEND,BL_DIDLE}   BL_TX_STATE;

void BL_UartInit(void);
BOOL BL_UartTXData(BYTE byteCmd, USHORT byteLen, const BYTE *ptrData);
USHORT BL_UartGetRecvData(BYTE **pptrData);
BOOL BL_HaveData(void);

#endif