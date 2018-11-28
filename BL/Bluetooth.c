#include "bluetooth.h"
#include <string.h>

void BL_Init(void)
{
  BL_UartInit(); 
}

void BL_Send(BL_DATA *data)
{
  BL_UartTXData(0,data->byteDataLEN,data->pabyData);
}

BOOL BL_Get_Status(void)
{
  return BL_HaveData();
}

BL_CMD BL_Get_Command(void)
{
    BYTE *ptrData = NULL;
    USHORT dataLen =  BL_UartGetRecvData(&ptrData);
    BL_CMD  cmd = BL_INVALID;
    if(dataLen)
    {
       if(strstr((char const*)ptrData,BL_CMD_GET_RTC))
       {
         cmd = BL_GET_RTC;
       }
       else if(strstr((char const*)ptrData,BL_CMD_SWITCH_ON))
       {
           cmd = BL_SW_ON;
       }
       else if(strstr((char const*)ptrData,BL_CMD_SWITCH_OFF))
       {
           cmd = BL_SW_OFF;
       }
       else if(strstr((char const*)ptrData,BL_CMD_EXIT))
       {
         cmd = BL_EXIT;
       }
    }
    return cmd;
}