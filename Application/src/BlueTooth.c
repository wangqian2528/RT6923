#include <stdio.h>
#include <stdbool.h>
#include "string.h"
#include "BlueTooth.h"
#include "HandUart_new.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"

//----------------------------------
#include "xmodem.h"//云养程序区 
//----------------------------------------

//#include "efm32.h"
//#include "em_cmu.h"
//#include "em_int.h"
//#include "em_gpio.h"
//#include "em_usart.h"
//#include "em_dma.h"

/* Declare some strings */
//const char     welcomeString[]  = "Energy Micro RS-232 - Please press a key\n";
//const char     overflowString[] = "\n---RX OVERFLOW---\n";
//const uint32_t welLen           = sizeof(welcomeString) - 1;
//const uint32_t ofsLen           = sizeof(overflowString) - 1;

/* Define termination character */
//#define TERMINATION_CHAR    '.'

/* Declare a circular buffer structure to use for Rx and Tx queues */
#define TX_BUFFER_LENGTH          32
#define RX_BUFFER_LENGTH          8

volatile struct circularBuffer
{
  uint8_t  data[TX_BUFFER_LENGTH];  /* data buffer */
 // uint32_t rdI;               /* read index */
  uint32_t wrI;               /* write index */
  uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
  bool     overflow;          /* buffer overflow indicator */
} BlueToothtxBuf = { 0, 0, 0, false };

/* Setup UART1 in async mode for RS232*/
static USART_TypeDef           * uart   = USART2;
static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

unsigned char ucBlueToothRXBuffer[RX_BUFFER_LENGTH] = {0};
//unsigned char ucTXBuffer[BUFFER_LENGTH] = {0};
static volatile int  rxWriteIndex = 0;
unsigned char BlueToothRX_Index;
bool  bBlueToothRXOK;
unsigned char by_Button;
unsigned int nctrlType = NORMAL_CTRL;
unsigned int RX_Counter,RX_Start;

#define BLUETOOTH_AT_CMD_MODE 0
#define BLUETOOTH_AT_DATA_MODE 1

int BlueToothGetMode(void);
//
/******************************************************************************
* @brief  uartSetup function
*
******************************************************************************/
void BlueToothUart_Initial_IO(void)
{
  /* Init BlueTooth's GPIO (the bluetooth switch channel) */
  GPIO_PinModeSet(BlueTooth_MUTE_PORT,BlueTooth_MUTE_BIT,BlueTooth_MUTE_MODE,BlueTooth_MUTE_INIT_ON);
  GPIO_PinModeSet(BlueTooth_IO1_PORT,BlueTooth_IO1_BIT,BlueTooth_IO1_MODE,1);
  //GPIO_PinModeSet(BlueTooth_IO2_PORT,BlueTooth_IO2_BIT,BlueTooth_IO2_MODE,0);
  //GPIO_PinModeSet(BlueTooth_IO3_PORT,BlueTooth_IO3_BIT,BlueTooth_IO3_MODE,0);
  
  //GPIO_PinModeSet(BlueTooth_Volum_PORT,BlueTooth_Volum_BIT,gpioModeInput,0);//AD 采样
 
  //GPIO_DriveModeSet(BlueTooth_IO1_PORT,gpioDriveModeStandard);
  //GPIO_DriveModeSet(BlueTooth_IO3_PORT,gpioDriveModeStandard);
  
  /* Configure GPIO pins For BlueTooth channel(USART0 #2) */
  GPIO_PinModeSet(BlueTooth_TX_PORT,BlueTooth_TX_BIT,BlueTooth_TX_MODE, 1);
  GPIO_PinModeSet(BlueTooth_RX_PORT,BlueTooth_RX_BIT,BlueTooth_RX_MODE, 0);

  /* Prepare struct for initializing UART in asynchronous mode*/
  uartInit.enable       = usartDisable;   /* Don't enable UART upon intialization */
  uartInit.refFreq      = 0;              /* Provide information on reference frequency. When set to 0, the reference frequency is */
  uartInit.baudrate     = 115200;         /* Baud rate */
  uartInit.oversampling = usartOVS6;      /* Oversampling. Range is 4x, 6x, 8x or 16x */
  uartInit.databits     = usartDatabits8; /* Number of data bits. Range is 4 to 10 */
  uartInit.parity       = usartNoParity;  /* Parity mode */
  uartInit.stopbits     = usartStopbits1; /* Number of stop bits. Range is 0 to 2 */
  //uartInit.mvdis        = false;          /* Disable majority voting */
  //uartInit.prsRxEnable  = false;          /* Enable USART Rx via Peripheral Reflex System */
  //uartInit.prsRxCh      = usartPrsRxCh0;  /* Select PRS channel if enabled */

  /* Initialize USART with uartInit struct */
  USART_InitAsync(uart, &uartInit);

  /* Prepare UART Rx and Tx interrupts */
  USART_IntClear(uart, _UART_IF_MASK);
  USART_IntEnable(uart, UART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(USART2_RX_IRQn);
  NVIC_ClearPendingIRQ(USART2_TX_IRQn);
  NVIC_EnableIRQ(USART2_RX_IRQn);
  NVIC_EnableIRQ(USART2_TX_IRQn);
  

  /* Enable I/O pins at UART1 location #3 */
  uart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | UART_ROUTE_LOCATION_LOC0;

  /* Enable UART */
  USART_Enable(USART2, usartEnable);
  
  
  /* Write welcome message to UART */
 // uartPutData((uint8_t*) welcomeString, welLen);
}
/**************************************************************************//**
 * @brief UART0 RX IRQ Handler
 *
 * Set up the interrupt prior to use
 *
 * Note that this function handles overflows in a very simple way.
 *
 *****************************************************************************/
/*
void USART2_RX_IRQHandler(void)
{
  unsigned char checkSum;

  
  if (uart->STATUS & USART_STATUS_RXDATAV)
  {

    uint8_t rxData = USART_Rx(uart);
   RX_Counter = 0;
   RX_Start = 1;
   if(BlueToothGetMode() == BLUETOOTH_AT_CMD_MODE)    
   {
     ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
     BlueToothRX_Index++;
     BlueToothRX_Index %= BUFFER_LENGTH;
   }
    else
    {
      if(rxData == BlueTooth_SOI)
      {
        BlueToothRX_Index = 0;  
        ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
        BlueToothRX_Index++;  
      }
      else
        if(rxData == BlueTooth_EOI)
        {
          if(ucBlueToothRXBuffer[0] == BlueTooth_SOI)
          {
            checkSum = ucBlueToothRXBuffer[1];
            checkSum += ucBlueToothRXBuffer[2];
            checkSum = ~checkSum;
            checkSum &= 0x7f;
            if(checkSum == ucBlueToothRXBuffer[3])
            {
              nctrlType = ucBlueToothRXBuffer[1];屏蔽
              by_Button = ucBlueToothRXBuffer[2];屏蔽
              bBlueToothRXOK = 1;
            }
          }
        }
        else
        {
          ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
          BlueToothRX_Index++;
          BlueToothRX_Index %= BUFFER_LENGTH;
        }
    }

    USART_IntClear(uart, USART_IF_RXDATAV);
  }
}*/
//--------------------------------------------------------------------------------
void USART2_RX_IRQHandler(void)//云养程序修改区
{
    unsigned char checkSum;
    if (uart->STATUS & USART_STATUS_RXDATAV)
    { 
        uint8_t rxData = USART_Rx(uart);  
        if(Cloud_Xmodem_Start_Rec_status())
        {
            Cloud_Xmodem_Rec_packet(rxData);           
        }
        else
        {
            RX_Counter = 0;
            RX_Start = 1;     
            if(BlueToothGetMode() == BLUETOOTH_AT_CMD_MODE)//蓝牙芯片的工作状态，命令状态
            {
                ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
                BlueToothRX_Index++;
                BlueToothRX_Index %= BUFFER_LENGTH;
            }
            else                                             //蓝牙芯片工作在数据状态
            {
                if(rxData == BlueTooth_SOI)///开始字节（SOI）：0XF0 数据帧开始字节
                {
                    BlueToothRX_Index = 0;  
                    ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
                    BlueToothRX_Index++;  
                }
                else if(rxData == BlueTooth_EOI)
                {
                    if(ucBlueToothRXBuffer[0] == BlueTooth_SOI && ucBlueToothRXBuffer[1] != PROGARM_CTRL)
                    {
                        checkSum = ucBlueToothRXBuffer[1];
                        checkSum += ucBlueToothRXBuffer[2];
                        checkSum = ~checkSum;
                        checkSum &= 0x7f;
                        if(checkSum == ucBlueToothRXBuffer[3])
                        {
                            nctrlType = ucBlueToothRXBuffer[1];
                            by_Button = ucBlueToothRXBuffer[2];
                            bBlueToothRXOK = 1;
                        }
                    }
                    if(ucBlueToothRXBuffer[0] == BlueTooth_SOI && ucBlueToothRXBuffer[1] == PROGARM_CTRL)
                    {
                        checkSum = ucBlueToothRXBuffer[1];
                        checkSum += ucBlueToothRXBuffer[2];
                        checkSum = ~checkSum;
                        checkSum &= 0x7f;
                        if(checkSum == ucBlueToothRXBuffer[3])
                        {
                           nctrlType = ucBlueToothRXBuffer[1];
                        }
//                        if(BlueTooth_Cloud_checksum(ucBlueToothRXBuffer))
//                        {
//                            nctrlType = ucBlueToothRXBuffer[1];//手控器标识（ID）
//                        }
                    }
                }
                else
                {
                    ucBlueToothRXBuffer[BlueToothRX_Index] = rxData;
                    BlueToothRX_Index++;
                    BlueToothRX_Index %= BUFFER_LENGTH;
                }      
            }
        }
        USART_IntClear(uart, USART_IF_RXDATAV);
    }
}




/**************************************************************************//**
 * @brief UART1 TX IRQ Handler
 *
 * Set up the interrupt prior to use
 *
 *****************************************************************************/
void USART2_TX_IRQHandler(void)
{
  uint32_t irqFlags = USART_IntGet(uart);

  /* Check TX buffer level status */
  if (uart->STATUS & USART_STATUS_TXBL)
  {
    if (BlueToothtxBuf.pendingBytes > 0)
    {
      /* Transmit pending character */
      USART_Tx(uart, BlueToothtxBuf.data[BlueToothtxBuf.wrI]);
      BlueToothtxBuf.wrI++;
      BlueToothtxBuf.pendingBytes--;
    }

    /* Disable Tx interrupt if no more bytes in queue */
    if (BlueToothtxBuf.pendingBytes == 0)
    {
      USART_IntDisable(uart, USART_IF_TXBL);
    }
  }
}

/******************************************************************************
 * @brief  uartPutData function
 *每50ms刷新数据
 *****************************************************************************/
void uartBlueToothPutData(uint8_t * dataPtr, uint32_t dataLen)
{
  int i = 0;

  /* Check if buffer is large enough for data */
  if (dataLen > TX_BUFFER_LENGTH)
  {
    /* Buffer can never fit the requested amount of data */
    return;
  }
  /*
  if ((txBuf.pendingBytes + dataLen) > BUFFERSIZE)
  {
    while ((txBuf.pendingBytes + dataLen) > BUFFERSIZE) ;
  }
  */
  while (i < dataLen)
  {
    BlueToothtxBuf.wrI = 0;
    BlueToothtxBuf.data[i] = *(dataPtr + i);
    i++;
  }

  /* Increment pending byte counter */
  BlueToothtxBuf.pendingBytes = dataLen;

  /* Enable interrupt on USART TX Buffer*/
  USART_IntEnable(uart, UART_IF_TXBL);
}

void BlueToothUart_Transmit_Packet(unsigned char* buf,unsigned int length)
{
   uartBlueToothPutData(buf,length);
}
unsigned char BlueToothUart_GetRXStatus(void)
{
  return((unsigned char)bBlueToothRXOK);
}

unsigned char BlueToothUart_GetKey(void)
{
  return((unsigned char)by_Button);
}
                                  
void BlueToothUart_SetKey(unsigned char by_Data)
{
  by_Button = by_Data;
}
void BlueToothUart_ClearRXStatus(void)
{
  bBlueToothRXOK = 0;
} 

void BlueToothUart_SetRXStatus(void)
{
  bBlueToothRXOK = 1;
} 
unsigned int BlueToothUart_GetCtrlType(void)
{
  return(nctrlType); 
}
void BlueToothOff(void)
{
  GPIO_PinOutSet(BlueTooth_MUTE_PORT,BlueTooth_MUTE_BIT);
}
void BlueToothOn(void)
{
  GPIO_PinOutClear(BlueTooth_MUTE_PORT,BlueTooth_MUTE_BIT);
}
unsigned char BlueToothMuteState(void)
{
  return GPIO_PinOutGet(BlueTooth_MUTE_PORT,BlueTooth_MUTE_BIT);
}
void BlueToothEnterDataMode(void)
{
 GPIO_PinOutSet(BlueTooth_IO1_PORT,BlueTooth_IO1_BIT);
}
void BlueToothEnterCmdMode(void)
{
 GPIO_PinOutClear(BlueTooth_IO1_PORT,BlueTooth_IO1_BIT);
}

int BlueToothGetMode(void)
{
  int retval;
  if(GPIO_PinOutGet(BlueTooth_IO1_PORT,BlueTooth_IO1_BIT))
  {
    retval = BLUETOOTH_AT_DATA_MODE;
  }
  else
  {
    retval = BLUETOOTH_AT_CMD_MODE;
  }
  return retval;
}

void BlueToothUart_GetName(void)
{
  char* str ="AT+GETNAME\n";
  unsigned int length;
  length = strlen(str);
  BlueToothRX_Index = 0;  //接收指针为零
  BlueToothUart_ClearRXStatus();
  uartBlueToothPutData(str,length);
}


void BlueToothUart_GetModlueName(unsigned char* str)
{
  str =  ucBlueToothRXBuffer;
}

void BlueToothUart_AMP_Volume_Off(void)
{
//  GPIO_PinModeSet(BlueTooth_Volum_PORT,BlueTooth_Volum_BIT,gpioModePushPull,0);
}
void BlueToothUart_AMP_Volume_On(void)
{
//  GPIO_PinModeSet(BlueTooth_Volum_PORT,BlueTooth_Volum_BIT,gpioModeInput,0);
}
