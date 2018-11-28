

#ifndef __XMODEM_H__
#define __XMODEM_H__

#define PROGARM_CTRL             0xA5

#define XMODEM_SOH                1       //0x01   标题开始  start of heading
#define XMODEM_EOT                4       //0x04     end of transmission  传输结束
#define XMODEM_ACK                6       //0x06 acknowledge  收到通知
#define XMODEM_NAK                21      //0x15 negative acknowlege 拒绝接受
#define XMODEM_CAN                24      //0x18  cancel 取消
#define XMODEM_NCG                67      //0x43  大写字母C

#define XMODEM_DATA_SIZE          128

//----------------------------------------------
#define XMODEM_ERROR               85//处理APK异常退出

#define MAX_DATA_LEN               8160 //最大按摩手法长度
//-----------------------------------------------

#define CLOUD_PROGAME1_START_ADDRESS  ((uint32_t)0x16000)//CLOUD_PROGAME4_END_ADDRESS
#define CLOUD_PROGAME1_END_ADDRESS    ((uint32_t)0x17FFF)

#define CLOUD_PROGAME2_START_ADDRESS  ((uint32_t)0x18000)
#define CLOUD_PROGAME2_END_ADDRESS    ((uint32_t)0x19FFF)

#define CLOUD_PROGAME3_START_ADDRESS  ((uint32_t)0x1A000)
#define CLOUD_PROGAME3_END_ADDRESS    ((uint32_t)0x1BFFF)

#define CLOUD_PROGAME4_START_ADDRESS  ((uint32_t)0x1C000)
#define CLOUD_PROGAME4_END_ADDRESS    ((uint32_t)0x1DFFF)

#define CLUDE_AUTO_ID_ADDRESS    0  //32位
#define CLUDE_AUTO_SIZE_ADDRESS  4  //16位
#define CLUDE_AUTO_CHECKSUM_ADDRESS  8//16位
#define CLUDE_AUTO_VERSION_ADDRESS  12//16位
#define CLUDE_AUTO_PROGRAM_OFFSET  32




//void BuleTooth_Cloud_5ms_Int(void);
unsigned char BlueToothCloud_GetRXStatus(void);
unsigned char BuleTooth_Cloud_Get5msFlag(void);
unsigned char BuleTooth_Cloud_GetBusyFlag(void);
//void BuleTooth_Cloud_Clr_5msFlag(void);
void BlueToothCloud_Clr_RXStatus(void);

//unsigned char BlueTooth_Cloud_checksum(void);

unsigned char BlueTooth_Cloud_Get_LINGO(void);
unsigned char BlueTooth_Cloud_Get_COMMAND(void);
unsigned short BlueTooth_Cloud_Get_PROG_ID(void);
unsigned char BuleTooth_Cloud_rxByte(void);

int BuleTooth_Cloud_txByte(unsigned char data);

int BlueTooth_Cloud_Xmodem(unsigned int baseAddress, unsigned int endAddress);

int Cloud_verifyPacketChecksum(unsigned char *pkt, int sequenceNumber,unsigned char by_checksum);
 
unsigned short CRC_calc(unsigned char  *start, unsigned char *end);


void Cloud_Bluetooth_command_mode(void);

void BuleTooth_xmodem_update(void);

unsigned char Cloud_Xmodem_Start_Rec_status(void);
void Cloud_Xmodem_Rec_packet(unsigned char rxData);
unsigned char BlueTooth_Cloud_checksum(unsigned char*PDATA);


void xmodem__Erase_Block(unsigned int start_addr,unsigned int end_addr);

 void BlueToothEnterDataMode(void);
#endif

//------------------------------------------------------------------------------------------------
