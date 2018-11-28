#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "BL_Config.h"
#include "BL_UART.h"

//COMMNDS
#define BL_CMD_GET_RTC     "getRTC"
#define BL_CMD_SWITCH_ON   "switchON"
#define BL_CMD_SWITCH_OFF  "switchOFF"
#define BL_CMD_EXIT   "exit"

#define BL_MAX_FRAME_DATA_LEN   256

typedef struct tag_BL_DATA
{
    USHORT  byteDataLEN;
    BYTE    *pabyData;
}BL_DATA;

typedef enum
{
  BL_GET_RTC = 0,
  BL_SW_ON,
  BL_SW_OFF,
  BL_EXIT,
  BL_INVALID = 0xFFFF
} BL_CMD;

void BL_Init(void);
void BL_Send(BL_DATA *data);
BOOL BL_Get_Status(void);
BL_CMD BL_Get_Command(void);

#endif