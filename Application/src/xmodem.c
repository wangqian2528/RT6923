

#include <stdio.h>
#include <stdbool.h>
#include "string.h"
#include "BlueTooth.h"
#include "HandUart_New.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"

#include "xmodem.h"
#include "timer.h"
#include "memory.h"
/*bluetooh修改接收中断函数，增加XOMDEM文件，覆盖 MEMORY文件


meomory文件需要增加函数与main_update配合*/



static bool  bCloud_BlueToothRXOK=0;
//static bool  bColud_BlueTooth_5msFlag;
static bool  bColud_BlueTooth_Busy;
static unsigned char by_lingo=0;
static unsigned char by_command=0;
static bool bCloud_Xmodem_Start_Rec=0;
unsigned char by_Cloud_Xmodem_Rec_Data[136];//[128];
unsigned int Rec_Xmodem_index;
bool  bbCloud_Xmodem_Start_Rec_ok=0;
unsigned char by_Cloud_checksum;
//static bool bCloud_50msFlag=0;
unsigned int w_Cloud_Checksum=0;
unsigned short w_Cloud_progarm_ID;
#define bCloud_Packet_Len    133
#define BLUETOOTH_LEN    8



#define LINGO_BY_BLUETOOTH       0x10
#define LINGO_EXIT_BLUETOOTH     0x11
#define CLOUD_DOWNLOAD_CMD       0x01
#define CLOUD_DELETE_CMD         0x02





unsigned char BlueToothCloud_GetRXStatus(void)
{
  return((unsigned char)bCloud_BlueToothRXOK);
  
}
void Cloud_Bluetooth_command_mode(void)
{
  
bCloud_Xmodem_Start_Rec=0;

}


void BlueToothCloud_Clr_RXStatus(void)
{
  bCloud_BlueToothRXOK=0;
}


unsigned char BlueTooth_Cloud_Get_LINGO(void)
{
    return((unsigned char)by_lingo);
}


unsigned char BlueTooth_Cloud_Get_COMMAND(void)
{
    return((unsigned char)by_command);
}


unsigned short BlueTooth_Cloud_Get_PROG_ID(void)
{
    return((unsigned short)w_Cloud_progarm_ID);
}
  

unsigned char BuleTooth_Cloud_GetBusyFlag(void)
{
  
  return ((unsigned char)bColud_BlueTooth_Busy);
  
}





unsigned char BlueTooth_Cloud_checksum(unsigned char*PDATA)
{

  return 0;
  
}


 unsigned char BuleTooth_Cloud_rxByte(void)
{
 return 0;
}


int BuleTooth_Cloud_txByte(unsigned char data)
   
{

 return 0;
}





 unsigned short CRC_calc(unsigned char  *start, unsigned char *end)
{ return 0;

}



 int Cloud_verifyPacketChecksum(unsigned char *pkt, int sequenceNumber,unsigned char by_checksum)
 {
   

   
    return 0;
   
   
 }


//bCloud_Xmodem_Start_Rec
unsigned char Cloud_Xmodem_Start_Rec_status(void)
{
  
    return bCloud_Xmodem_Start_Rec;
    
}


 void Cloud_Xmodem_Rec_packet(unsigned char rxData)
 {
   


 }


int BlueTooth_Cloud_Xmodem(unsigned int baseAddress, unsigned int endAddress)
{
 return 0;
   
  
}
void xmodem__Erase_Block(unsigned int start_addr,unsigned int end_addr)
{
    MEM_Initial();
    Timer_Initial();
    for (unsigned int addr = start_addr; addr < end_addr; addr += Get_FlashPageSize())//efm32lg=2kbytes
    {
               Mem_Erase_Block(addr);
               Timer_Counter_Clear(1);
               while( Timer_Counter(1,1)==0);  
       
    }

}

//unsigned int lenght1,lenght2,lenght3,psum,pID;
//unsigned char bCloud_OutBuffer[12];
void BuleTooth_xmodem_update(void)
{
  
  
 
  }













//----------------------------------------------------------------------------
