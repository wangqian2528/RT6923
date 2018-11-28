#include "em_gpio.h"
#include "em_usart.h"
#include "UartLeg.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "input.h"
#include "system.h"
#define LEG_BUFFERSIZE          32
#define LEG_BUFFER_LENGTH       9//      32
#define VOICE_BUFFER_LENGTH     8

// unsigned char  TX_485_Finish;

//static bool b485_RX_STATUS=0;

static volatile unsigned  char b485_RX_Timeout=0;

//static bool UartLeg1ms_flag=0;
static volatile struct circularBuffer
{
    uint8_t  data[LEG_BUFFERSIZE];  /* data buffer */
    // uint32_t rdI;               /* read index */
    uint32_t wrI;               /* write index */
    uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
    bool     overflow;          /* buffer overflow indicator */
}txLegBuf = { 0, 0, 0, false };

static volatile unsigned char ucLegRXBuffer[LEG_BUFFER_LENGTH] = {0};
//static volatile unsigned char ucLegTXBuffer[LEG_BUFFER_LENGTH] = {0};

static volatile unsigned char ucCommonRXBuffer[LEG_BUFFER_LENGTH] = {0};

static volatile unsigned char uc3DMessageRXBuffer[LEG_BUFFER_LENGTH] = {0};

static volatile unsigned char ucVoiceMessageRXBuffer[LEG_BUFFER_LENGTH] = {0};

//--------------------------------------

static unsigned char massage3DSignal,massage3DPluse,massage3D_Speed;
static unsigned char volatile errorCount;

//-----------------------------------------

unsigned char RX_Leg_Index;
bool  bRXOK_Leg=0;

  bool  bRXOK_3D=0;
bool  bRXOK_Voice = 0;

static unsigned char by_Voice_Key;

static USART_TypeDef           * uart   = UART0;//1;
static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

//static USART_TypeDef           * uart   = UART1;////0;
//static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

#define SOI                    0XF0
#define EOI                    0XF1

#define ARM_BUFFER_LENGTH      8

unsigned int t1=0;
unsigned int t2=0;

unsigned char err=0;

//#define UARTLEG_CONTROL_PORT           gpioPortF//C
//#define UARTLEG_CONTROL_BIT            5//1
//#define UARTLEG_CONTROL_MODE           gpioModeInputPull
void UartLeg_Initial_IO(void)
{
    /* Enable clock for GPIO module (required for pin configuration) */
    // CMU_ClockEnable(cmuClock_GPIO, true);
    /* Configure GPIO pins */
    GPIO_PinModeSet(UARTLEG_TX_PORT,UARTLEG_TX_BIT,UARTLEG_TX_MODE, 1);
    GPIO_PinModeSet(UARTLEG_RX_PORT,UARTLEG_RX_BIT,UARTLEG_RX_MODE, 1);
    GPIO_PinModeSet(UARTLEG_CONTROL_PORT ,UARTLEG_CONTROL_BIT,UARTLEG_CONTROL_MODE, 0);//初始化为接收状态
    GPIO_PinModeSet(VOICE_WAKEUP_PORT ,VOICE_WAKEUP_BIT,VOICE_WAKEUP_MODE, 0);
    /* Prepare struct for initializing UART in asynchronous mode*/
    uartInit.enable       = usartDisable;   /* Don't enable UART upon intialization */
    uartInit.refFreq      = 0;              /* Provide information on reference frequency. When set to 0, the reference frequency is */
    uartInit.baudrate     = 115200;         /* Baud rate */
    uartInit.oversampling = usartOVS16;     /* Oversampling. Range is 4x, 6x, 8x or 16x */
    uartInit.databits     = usartDatabits8; /* Number of data bits. Range is 4 to 10 */
    uartInit.parity       = usartNoParity;  /* Parity mode */
    uartInit.stopbits     = usartStopbits1; /* Number of stop bits. Range is 0 to 2 */
    //uartInit.mvdis        = false;          /* Disable majority voting */
    //uartInit.prsRxEnable  = false;          /* Enable USART Rx via Peripheral Reflex System */
    //uartInit.prsRxCh      = usartPrsRxCh0;  /* Select PRS channel if enabled */
    
    /* Initialize USART with uartInit struct */
    USART_InitAsync(uart, &uartInit);
    
    /* Prepare UART Rx and Tx interrupts */
    USART_IntClear(uart, _USART_IF_MASK);
    USART_IntEnable(uart, USART_IF_RXDATAV);
    NVIC_ClearPendingIRQ(UART0_RX_IRQn);
    NVIC_ClearPendingIRQ(UART0_TX_IRQn);
    NVIC_EnableIRQ(UART0_RX_IRQn);
    NVIC_EnableIRQ(UART0_TX_IRQn);
    
    
    /* Enable I/O pins at UART1 location #3 */
    uart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC0;
    
    /* Enable UART */
    USART_Enable(uart, usartEnable);
    
    
    /* Write welcome message to UART */
    // uartPutData((uint8_t*) welcomeString, welLen);
}


//void  UartLeg_init_data(void)
//{ 
//    b485_RX_STATUS=0;
//    //TX_485_Finish=0;
//    //RX_Leg_Index = 0; 
//}

//unsigned char UartLeg_TX_STATUS(void)
//{
//  return TX_485_Finish;
//  
//}


//unsigned char UartLeg_RX_STATUS(void)
//{
//  
// return   b485_RX_STATUS;
//  
//}
/*****************************************************************************/
void UartLeg_SET_TX_EN(void)//保留 发送使能
{
    
    GPIO_PinOutSet(UARTLEG_CONTROL_PORT,UARTLEG_CONTROL_BIT);
    
}
void UartLeg_CLR_TX_EN(void)//保留 接收使能
{
    
    GPIO_PinOutClear(UARTLEG_CONTROL_PORT,UARTLEG_CONTROL_BIT);
    
}
/******************************************************************************/
//void UartLeg_TX_RX_STATUS(void)
//{
// if( TX_485_Finish)
// {
//  // UartLeg_SET_TX_EN();
//   
// }
//  else
//  {
//    
//   if(UartLeg1ms_flag)
//   {
//   UartLeg_CLR_TX_EN();
//   }
//   
//    
//  }
//  
//}




/**************************************************************************//**
* @brief UART0 RX IRQ Handler
*
* Set up the interrupt prior to use
*
* Note that this function handles overflows in a very simple way.
*
*****************************************************************************/
void UART0_RX_IRQHandler(void)
{
    static uint8_t chksum;
    uint8_t i;
    uint8_t rxData; 
    uint8_t rXOver;
    
    USART_IntClear(UART0, USART_IF_RXDATAV);
    rxData  = USART_Rx(uart);
    chksum = 0;
    rXOver = FALSE;
    if(ucCommonRXBuffer[0]==SOI)      // 开始接收
    {
        ucCommonRXBuffer[RX_Leg_Index]=rxData;
        RX_Leg_Index++;
        if(rxData==EOI) 
        {
            rXOver =TRUE;   // 接收完成
        }
    }
    else 
    {
        RX_Leg_Index=1;
        ucCommonRXBuffer[0] = rxData;
    }
    
    if(RX_Leg_Index>LEG_BUFFER_LENGTH)
    {
        RX_Leg_Index=1;
        ucCommonRXBuffer[0] = 0;
        return;
    }
    
    if(rXOver == TRUE)   // 接收完成后数据处理
    {
        rxData = 0; 
        
        if(ucCommonRXBuffer[1] ==12)
        {
            //            for(i=1;i<7;i++)
            //            {
            //                rxData +=ucCommonRXBuffer[i];
            //            }
            //            chksum = (~rxData)&0X7F;
            //            if(chksum ==ucCommonRXBuffer[7])
            //            {
            //                bRXOK_Leg = 1;    
            //                UartLegCopyData();
            //            }
            memcpy(ucLegRXBuffer,ucCommonRXBuffer,ARM_BUFFER_LENGTH);
        }
        else if(ucCommonRXBuffer[1] ==2)
        {
            for(i=1;i<5;i++)
            {
                rxData +=ucCommonRXBuffer[i];
            }
            chksum = ~rxData;
            chksum  &=0x7F;
            if(chksum ==ucCommonRXBuffer[5])   //接收成功
            {
                errorCount=0;
                bRXOK_3D = 1;    
                memcpy(uc3DMessageRXBuffer,ucCommonRXBuffer,LEG_BUFFER_LENGTH);
            }
        }
        else if(ucCommonRXBuffer[1] ==9)//语音模块
        {
            for(i=1;i<6;i++)
            {
                rxData +=ucCommonRXBuffer[i];
            }
            chksum = ~rxData;
            chksum  &=0x7F;
            if(chksum == ucCommonRXBuffer[6])   //接收成功
            {
                errorCount=0;
                memcpy(ucVoiceMessageRXBuffer,ucCommonRXBuffer,8);
                by_Voice_Key = ucCommonRXBuffer[3];
                if(by_Voice_Key < 0x7f)
                {
                   bRXOK_Voice = 1;
                }
            }
        }
        
        ucCommonRXBuffer[0] = 0;
        RX_Leg_Index=1;
    }
    
    
    
    
    /***********************************************************************/
    //    if (uart->STATUS & USART_STATUS_RXDATAV)
    //    {
    //
    //        uint8_t rxData = USART_Rx(uart);
    //        if((rxData != SOI)&&(RX_Leg_Index==0))return;
    //        if((rxData == SOI)&&(RX_Leg_Index==0))
    //        {
    //           b485_RX_STATUS=1;
    //           b485_RX_Timeout=0;
    //            ucCommonRXBuffer[RX_Leg_Index]=rxData;
    //            RX_Leg_Index++;
    //            
    //        }
    //        else
    //        {
    //            ucCommonRXBuffer[RX_Leg_Index]=rxData;
    //            RX_Leg_Index++;
    //            RX_Leg_Index %= LEG_BUFFER_LENGTH;
    //          if( ucCommonRXBuffer[1]==0x01)
    //          {    
    //            if(rxData==EOI)
    //            {
    //              chksum=0;
    //              for(i=1;i<3+ucCommonRXBuffer[2];i++)
    //              {
    //                
    //                chksum+=ucCommonRXBuffer[i];
    //              }
    //              chksum  = ~chksum;
    //              chksum  &=   0x7f;
    //              if(chksum==ucCommonRXBuffer[3+ucCommonRXBuffer[2]])
    //              {  
    //                 t1++;
    //               //  b485_RX_STATUS=0;
    //                  RX_Leg_Index=0;
    //               //   t1=chksum;
    //              //    t3=ucCommonRXBuffer[3+ucCommonRXBuffer[2]];
    //                  bRXOK_Leg = 1;    
    //                  UartLegCopyData();
    //                
    //              }
    //            } 
    //          }
    //          else   if( ucCommonRXBuffer[1]==0x02)
    //          { //bRXOK_3D = 1;   
    //       //     t2++;
    //          //  if(RX_Leg_Index==(5+ucLegRXBuffer[2])&&rxData==EOI)
    //          //   if(RX_Leg_Index==(5+ucCommonRXBuffer[2]))
    //            if(rxData==EOI)
    //            {
    //              chksum=0;
    //              for(i=1;i<3+ucCommonRXBuffer[2];i++)
    //              {
    //                
    //                chksum+=ucCommonRXBuffer[i];
    //              }
    //              chksum  = ~chksum;
    //              chksum  &=   0x7f;
    //              if(chksum==ucCommonRXBuffer[3+ucCommonRXBuffer[2]])
    //              {  // b485_RX_STATUS=0;
    //                t2++;
    //                errorCount=0;
    //                  RX_Leg_Index=0;
    //                  bRXOK_3D = 1;    
    //                  memcpy(uc3DMessageRXBuffer,ucCommonRXBuffer,LEG_BUFFER_LENGTH);
    //              }
    //            }  
    //          }
    //        }
    //
    //        /* Clear RXDATAV interrupt */
    //        USART_IntClear(UART0, USART_IF_RXDATAV);
    //    }
}

//void UartLegCopyData (void)
//{
//  
//  memcpy(ucLegRXBuffer,ucCommonRXBuffer,LEG_BUFFER_LENGTH);
//  
//  
//}

void  UartLeg_3DMessageCopyData (void)//保留
{
    massage3DSignal=uc3DMessageRXBuffer[3];
    massage3DPluse=uc3DMessageRXBuffer[4];
    massage3D_Speed=5;
}

unsigned char UartLeg_Get3D_Speed(void)//保留
{
    return(massage3D_Speed);
}
unsigned char UartLeg_Get3DMassageSignal(void)//保留
{
    return(massage3DSignal);//3D机芯开关状态信号
}

unsigned char UartLeg_Get3DPluse(void)//保留
{
    return(massage3DPluse);  
}


/**************************************************************************//**
* @brief UART1 TX IRQ Handler
*
* Set up the interrupt prior to use
*
*****************************************************************************/
//bool send_time_flag;
bool b485Send;
void UART0_TX_IRQHandler(void)
{
    /* Check TX buffer level status */
    if (uart->STATUS & USART_STATUS_TXBL)
    {
        if (txLegBuf.pendingBytes > 0)
        {
            bSet485Send(true);
            /* Transmit pending character */
            USART_Tx(uart, txLegBuf.data[txLegBuf.wrI]);
            txLegBuf.wrI++;
            txLegBuf.pendingBytes--;
        }
        
        /* Disable Tx interrupt if no more bytes in queue */
        if (txLegBuf.pendingBytes == 0)
        {
            USART_IntDisable(uart, USART_IF_TXBL);
            while (!(uart->STATUS & USART_STATUS_TXBL));
            bSet485Send(false);
        }
    }
}
/**********************

***********************/


bool bGet485Send(void)
{
    return (b485Send);   
}
/**********************

***********************/
void bSet485Send(bool v)
{ 
    b485Send = v;  
}


void uartLegPutData(uint8_t * dataPtr, uint32_t dataLen)//保留
{
    int i = 0;
    
    /* Check if buffer is large enough for data */
    if (dataLen > LEG_BUFFERSIZE)
    {
        /* Buffer can never fit the requested amount of data */
        return;
    }
    while (i < dataLen)
    {
        txLegBuf.wrI = 0;
        txLegBuf.data[i] = *(dataPtr + i);
        i++;
    }
    
    /* Increment pending byte counter */
    txLegBuf.pendingBytes = dataLen;
    
    /* Enable interrupt on USART TX Buffer*/
    USART_IntEnable(uart, USART_IF_TXBL);
}

void UartLeg_Transmit_Packet(unsigned char* buf,unsigned int length)//保留
{
    UartLeg_SET_TX_EN();   
    uartLegPutData(buf,length);
}

//unsigned char UartLeg_GetRXStatus(void)
//{
//  return((unsigned char)bRXOK_Leg);
//}
//
//void UartLeg_ClearRXStatus(void)
//{
//  bRXOK_Leg = 0;
//}


void UartLeg_Clr_3DMessageStatus(void)
{
  bRXOK_3D=0;


}
unsigned char UartLeg_Get3DMessage_RXStatus(void)
{
  
    return((unsigned char)bRXOK_3D);
  
}


//unsigned short UartLeg_GetAngle(void)
//{
//    unsigned short angle;
//    angle = ucLegRXBuffer[1+3];
//    angle = angle << 7;
//    angle |= ucLegRXBuffer[0+3];
//    return(angle);
//}
//unsigned char UartLeg_GetFlexStatus(void)
//{
//    unsigned char status;
//    status = ucLegRXBuffer[2+3];
//    status &= (~BIT7);
//    return((unsigned char)status);
//}
//unsigned char UartLeg_GetLegStatus(void)
//{
//    unsigned char status;
//    status = ucLegRXBuffer[3+3];
//    status &= (~BIT7);
//    return((unsigned char)status);
//}



void UartLeg_10msInt(void)
{
    if(errorCount < 255) errorCount++;
    if(errorCount >10) bRXOK_3D = false;
}

//void UartLeg_RX_TimeoutInt(void)//5ms接受时间
//{
//  
// if( b485_RX_Timeout<255)b485_RX_Timeout++;
// 
// if(b485_RX_Timeout>=5)b485_RX_STATUS=0;
//  
//  
//}

unsigned int Input_GetArmStatus(void)
{
    if(  ucLegRXBuffer[3]&0x01 && ucLegRXBuffer[4]&0x01   )//20170718左右扶手都到内限位才算到限位
    {
        return( ARM_IN_LIMIT );
    }
    if(  ucLegRXBuffer[3]&0x02 && ucLegRXBuffer[4]&0x02   )//20180718左右扶手都到外限位才算到限位
    {
        return( ARM_OUT_LIMIT );
    }
    
    if(  ucLegRXBuffer[3]&0x04 && ucLegRXBuffer[4]&0x04   )
    {
        return( ARM_IN_RUN );
    }
    if(  ucLegRXBuffer[3]&0x08 && ucLegRXBuffer[4]&0x08   )
    {
        return( ARM_OUT_RUN );    
    }
    if(  ucLegRXBuffer[3]&0x10 && ucLegRXBuffer[4]&0x10   )
    {
        return( ARM_IN_PROTECT );
    }
    if(  ucLegRXBuffer[3]== 0 && ucLegRXBuffer[4]== 0 )
    {
        return( 0 );      
    }
    return( 0 );   
}

unsigned char UartLeg_GetVoiceKey(void)
{
   return by_Voice_Key;
}


bool UartLeg_GetVoiceRXState(void)
{
   return bRXOK_Voice;
}

void UartLeg_ClearVoiceRXState(void)
{
   bRXOK_Voice = 0;
}

void UartLeg_SetVoiceKey(unsigned char data)
{
   by_Voice_Key = data;
}



