//#include "string.h"
#include "HandUart.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"


/* Declare a circular buffer structure to use for Rx and Tx queues */
#define BUFFERSIZE          256

volatile struct circularBuffer
{
  uint8_t  data[BUFFERSIZE];  /* data buffer */
  // uint32_t rdI;               /* read index */
  uint32_t wrI;               /* write index */
  uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
  bool     overflow;          /* buffer overflow indicator */
} txBuf = { 0, 0, 0, false };

/* Setup UART1 in async mode for RS232*/
static USART_TypeDef           * uart   = UART1;////0;
static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

unsigned char ucRXBuffer[BUFFER_LENGTH] = {0};
unsigned char ucTXBuffer[BUFFER_LENGTH] = {0};
static volatile int     rxWriteIndex = 0;
unsigned char RX_Index;
static bool  bRXOK;

//DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2];
static unsigned char by_Key,by_Key1;

unsigned int ctrlType = NORMAL_CTRL;

unsigned char *blueToothBuffer1 = "MS=02,";
unsigned char *blueToothBuffer2 = "RS=02,";
unsigned char blueToothAddr[12];
unsigned char blueToothAddrIndex;
unsigned char blueToothCompareStep = 0;
bool blueToothShouldConnect = false;
unsigned int blueToothCount = 0;
bool compareBluetoothMSG(uint8_t rxData);
bool compareBluetoothMSG2(uint8_t rxData);


/******************************************************************************
* @brief  uartSetup function
*
******************************************************************************/
void HAND_Initial_IO(void)
{
  /* Enable clock for GPIO module (required for pin configuration) */
  // CMU_ClockEnable(cmuClock_GPIO, true);
  /* Configure GPIO pins */
  GPIO_PinModeSet(HAND_TX_PORT,HAND_TX_BIT,HAND_TX_MODE, 1);
  GPIO_PinModeSet(HAND_RX_PORT,HAND_RX_BIT,HAND_RX_MODE, 0);
  
  /* Prepare struct for initializing UART in asynchronous mode*/
  uartInit.enable       = usartDisable;   /* Don't enable UART upon intialization */
  uartInit.refFreq      = 0;              /* Provide information on reference frequency. When set to 0, the reference frequency is */
  uartInit.baudrate     = 9600;//115200;         /* Baud rate */
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
  USART_IntClear(uart, _UART_IF_MASK);
  USART_IntEnable(uart, UART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(UART1_RX_IRQn);
  NVIC_ClearPendingIRQ(UART1_TX_IRQn);
  NVIC_EnableIRQ(UART1_RX_IRQn);
  NVIC_EnableIRQ(UART1_TX_IRQn);
  
  /* Enable I/O pins at UART1 location #3 */
  uart->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_TXPEN | UART_ROUTE_LOCATION_LOC0;////3;
  
  /* Enable UART */
  USART_Enable(uart, usartEnable);
  
}

unsigned char  AsciiToVal(unsigned char nAscii)
{
  if(nAscii>=0x30 && nAscii<=0x39) return(nAscii-0x30);
  if(nAscii>=0x41 && nAscii<=0x46) return(nAscii-0x37);
  if(nAscii>=0x61 && nAscii<=0x66) return(nAscii-0x57);
  return 0 ;
}

/**************************************************************************//**
* @brief UART0 RX IRQ Handler
*
* Set up the interrupt prior to use
*
* Note that this function handles overflows in a very simple way.
*
*****************************************************************************/
void UART1_RX_IRQHandler(void)
{
  unsigned char by_Data;
  /* Check for RX data valid interrupt */
  
  if (uart->STATUS & UART_STATUS_RXDATAV)
  {
    /* Copy data into RX Buffer */
    uint8_t rxData = USART_Rx(uart);
    
    if(rxData == SOI)
    {
      RX_Index = 0;  
    }
    else
    {
      if(rxData == EOI)
      {
        by_Data = ucRXBuffer[0];
        ctrlType = by_Data;
        by_Key = ucRXBuffer[1];
        if(by_Key < 0x80) //按键值0-127
        {
          bRXOK = 1;
        }
        by_Key1 = ucRXBuffer[2]; //常规模式无此按键，硬件测试时使用
      }
      else
      {
        ucRXBuffer[RX_Index] = rxData;
        RX_Index++;
        RX_Index %= BUFFER_LENGTH;
      }
    }
    
    /* Clear RXDATAV interrupt */
    USART_IntClear(UART1, UART_IF_RXDATAV);
  }
}

/**************************************************************************//**
* @brief UART1 TX IRQ Handler
*
* Set up the interrupt prior to use
*
*****************************************************************************/
void UART1_TX_IRQHandler(void)
{
  uint32_t irqFlags = USART_IntGet(UART1);
  
  /* Check TX buffer level status */
  if (uart->STATUS & UART_STATUS_TXBL)
  {
    if (txBuf.pendingBytes > 0)
    {
      /* Transmit pending character */
      USART_Tx(uart, txBuf.data[txBuf.wrI]);
      txBuf.wrI++;
      txBuf.pendingBytes--;
    }
    
    /* Disable Tx interrupt if no more bytes in queue */
    if (txBuf.pendingBytes == 0)
    {
      USART_IntDisable(uart, UART_IF_TXBL);
    }
  }
}

/******************************************************************************
* @brief  uartPutData function
*每50ms刷新数据
*****************************************************************************/
static void uartPutData(uint8_t * dataPtr, uint32_t dataLen)
{
  int i = 0;
  
  /* Check if buffer is large enough for data */
  if (dataLen > BUFFERSIZE)
  {
    /* Buffer can never fit the requested amount of data */
    return;
  }

  while (i < dataLen)
  {
    txBuf.wrI = 0;
    txBuf.data[i] = *(dataPtr + i);
    i++;
  }
  
  /* Increment pending byte counter */
  txBuf.pendingBytes = dataLen;
  
  /* Enable interrupt on USART TX Buffer*/
  USART_IntEnable(uart, UART_IF_TXBL);
}

void HandUart_Transmit_Packet(unsigned char* buf,unsigned int length)
{
  uartPutData(buf,length);
}
unsigned char HandUart_GetRXStatus(void)
{
  return((unsigned char)bRXOK);
}

unsigned char HandUart_GetKey(void)
{
  return((unsigned char)by_Key);
}
unsigned char HandUart_GetExternKey(void)
{
  return((unsigned char)by_Key1);
}


void HandUart_SetKey(unsigned char by_Data)
{
  by_Key = by_Data;
}
void HandUart_ClearRXStatus(void)
{
  bRXOK = 0;
} 

void HandUart_SetRXStatus(void)
{
  bRXOK = 1;
} 
unsigned int HandUart_GetCtrlType(void)
{
  return(ctrlType); 
}
