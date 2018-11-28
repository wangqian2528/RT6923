#include "em_gpio.h"
#include "em_usart.h"
#include "UartMassagerSignal.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#define BUFFERSIZE                8
#define BUFFER_LENGTH             8

static volatile struct circularBuffer
{
    uint8_t  data[BUFFERSIZE];  /* data buffer */
    uint32_t wrI;               /* write index */
    uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
    bool     overflow;          /* buffer overflow indicator */
}txBuf = { 0, 0, 0, false };

static volatile unsigned char ucRXBuffer[BUFFER_LENGTH] = {0};
static volatile unsigned char ucTXBuffer[BUFFER_LENGTH] = {0};

static unsigned char RX_Index;
static bool  bRXOK;
unsigned char by_MassageSignal,by_Massage3DPluse;
static USART_TypeDef           * uart   = USART0;
static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;
#define SOI                    0XF0
#define EOI                    0XF1

void USART0_RX_IRQHandler(void);
void USART0_TX_IRQHandler(void);

void UartMassageSignal_Initial_IO(void)
{
    /* Enable clock for GPIO module (required for pin configuration) */
    // CMU_ClockEnable(cmuClock_GPIO, true);
    /* Configure GPIO pins */
    GPIO_PinModeSet(UART_MASSAGER_SIGNAL_TX_PORT,UART_MASSAGER_SIGNAL_TX_BIT,UART_MASSAGER_SIGNAL_TX_MODE, 1);
    GPIO_PinModeSet(UART_MASSAGER_SIGNAL_RX_PORT,UART_MASSAGER_SIGNAL_RX_BIT,UART_MASSAGER_SIGNAL_RX_MODE, 1);
    
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
    USART_IntClear(uart, _USART_IF_MASK);
    USART_IntEnable(uart, USART_IF_RXDATAV);
    NVIC_ClearPendingIRQ(USART0_RX_IRQn);
    NVIC_ClearPendingIRQ(USART0_TX_IRQn);
    NVIC_EnableIRQ(USART0_RX_IRQn);
    NVIC_EnableIRQ(USART0_TX_IRQn);
    
    
    /* Enable I/O pins at USART0 location #0 */
    uart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC0;
    
    /* Enable UART */
    USART_Enable(uart, usartEnable);
    
    
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
void USART0_RX_IRQHandler(void)
{
    if (uart->STATUS & USART_STATUS_RXDATAV)
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
                bRXOK = 1;    
            }
            else
            {
                ucRXBuffer[RX_Index] = rxData;
                RX_Index++;
                RX_Index %= BUFFER_LENGTH;
            }
        }
        /* Clear RXDATAV interrupt */
        USART_IntClear(uart, USART_IF_RXDATAV);
    }
}

/**************************************************************************//**
* @brief UART1 TX IRQ Handler
*
* Set up the interrupt prior to use
*
*****************************************************************************/
void USART0_TX_IRQHandler(void)
{
    uint32_t irqFlags = USART_IntGet(uart);
    
    /* Check TX buffer level status */
    if (uart->STATUS & USART_STATUS_TXBL)
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
            USART_IntDisable(uart, USART_IF_TXBL);
        }
    }
}

static void uartPutData(uint8_t * dataPtr, uint32_t dataLen)
{
  int i = 0;

  /* Check if buffer is large enough for data */
  if (dataLen > BUFFERSIZE)
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
    txBuf.wrI = 0;
    txBuf.data[i] = *(dataPtr + i);
    i++;
  }

  /* Increment pending byte counter */
  txBuf.pendingBytes = dataLen;

  /* Enable interrupt on USART TX Buffer*/
  USART_IntEnable(uart, USART_IF_TXBL);
}

void UartMassageSignal_Transmit_Packet(unsigned char* buf,unsigned int length)
{
   uartPutData(buf,length);
}

unsigned char UartMassageSignal_GetRXStatus(void)
{
  return((unsigned char)bRXOK);
}

void UartMassageSignal_ClearRXStatus(void)
{
  bRXOK = 0;
}
//ucRXBuffer[3]:存放高7位数据
//ucRXBuffer[2]:存放低7位数据
unsigned short UartMassageSignal_GetWalkPluse(void)
{
    unsigned short pluse;
    pluse = (ucRXBuffer[3] & (~BIT7));
    pluse = pluse << 7;
    pluse |= (ucRXBuffer[2] & (~BIT7));
    return(pluse);
}
//ucRXBuffer[1]:存放3D脉冲
unsigned char UartMassageSignal_Get3DPluse(void)
{
    unsigned char pluse;
    pluse = ucRXBuffer[1];
    pluse &= (~BIT7);
    return(pluse);
}
//ucRXBuffer[0]:存放低7位数据
unsigned char UartMassageSignal_GetSignal(void)
{
    unsigned char signal;
    signal = ucRXBuffer[0];
    signal &= (~BIT7);
    return(signal);
}
