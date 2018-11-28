#include "HandUart_New.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_leuart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"
#include "DMA_Ctrl.h"
#include "signalUart_new.h"
#include "string.h"


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

#define LEUART_USED     LEUART1
#define LEUART_IRQ      LEUART1_IRQn
#define LEUART_CLK      cmuClock_LEUART1

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
  /*********************LEUART*********************************/
  LEUART_TypeDef *leuart = LEUART_USED;
  LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
  
  /* Enable EFM32 to access peripheral Serial Port B */
  
  /* Enable CORE LE clock in order to access LE modules */
  CMU_ClockEnable(cmuClock_CORELE, true);
  
  /* Select LFXO for LEUARTs (and wait for it to stabilize) */
  //CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);//屏蔽掉，防止外部晶振因受潮不能正常起震时程序死在这里
  // CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
  /* Do not prescale clock */
  CMU_ClockDivSet(LEUART_CLK, cmuClkDiv_1);
  
  /* Enable clock */
  CMU_ClockEnable(LEUART_CLK, true);
  
  /* Use default location 0: TX - Pin C6, RX - Pin C7 */
  /* Configure GPIO pins */
  GPIO_PinModeSet(HAND_TX_PORT,HAND_TX_BIT,HAND_TX_MODE, 1);
  GPIO_PinModeSet(HAND_RX_PORT,HAND_RX_BIT,HAND_RX_MODE, 0);

  
  /* Enable pins at default location */
  leuart->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN|LEUART_ROUTE_LOCATION_LOC0;
  
  /* Configure LEUART1 */
  init.enable = false;
  LEUART_Init(leuart, &init);
  
  /* Clear previous RX interrupts */
  LEUART_IntClear(leuart, LEUART_IF_RXDATAV);
  LEUART_IntClear(leuart, LEUART_IF_TXBL);
  NVIC_ClearPendingIRQ(LEUART1_IRQn);
  
  /* Enable RX interrupts */
  LEUART_IntEnable(leuart, LEUART_IF_RXDATAV);
  LEUART_IntEnable(leuart, LEUART_IF_TXBL);
  NVIC_EnableIRQ(LEUART1_IRQn);
  leuart->CTRL = LEUART_CTRL_RXDMAWU|LEUART_CTRL_TXDMAWU  ;
  //leuart->CMD = 5;           
  /* Finally enable it */
  LEUART_Enable(leuart, leuartEnable);
}

unsigned char  AsciiToVal(unsigned char nAscii)
{
    if(nAscii>=0x30 && nAscii<=0x39) return(nAscii-0x30);
    if(nAscii>=0x41 && nAscii<=0x46) return(nAscii-0x37);
    if(nAscii>=0x61 && nAscii<=0x66) return(nAscii-0x57);
    return 0 ;
}

void LEUART1_IRQHandler(void)
{
    unsigned char by_Data;
    if (LEUART_USED->IF & LEUART_IF_RXDATAV)
    {
        unsigned char  rxData =LEUART_Rx(LEUART_USED);
        
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
        LEUART_IntClear(LEUART_USED, LEUART_IF_RXDATAV);
    }
    
    /* Check TX buffer level status */
    if (LEUART_USED->IF & LEUART_IF_TXBL)
    {
        if (txBuf.pendingBytes > 0)
        {
            /* Transmit pending character */
            LEUART_Tx(LEUART_USED, txBuf.data[txBuf.wrI]); 
            txBuf.wrI++;
            txBuf.pendingBytes--;
        }
        
        /* Disable Tx interrupt if no more bytes in queue */
        if (txBuf.pendingBytes == 0)
        {
            LEUART_IntDisable(LEUART_USED, LEUART_IF_TXBL);
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
  LEUART_IntEnable(LEUART_USED, LEUART_IF_TXBL);
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

