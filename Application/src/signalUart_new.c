#include "signalUart_new.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_dma.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"
#include "string.h"

static unsigned char massageSignal,SwtichSignal,FlexSwtichSignal;
static bool  bMassageSignalOK;
static unsigned char volatile errorCount;

/* Setup UART1 in async mode for RS232*/
static USART_TypeDef           *signalUart   = UART1;////0;
static USART_InitAsync_TypeDef signalUartInit = USART_INITASYNC_DEFAULT;

#define RXBUFSIZE  6

static volatile int     rxReadIndex  = 0;
static volatile int     rxWriteIndex = 0;
static volatile int     rxCount      = 0;
static volatile uint8_t rxBuffer[RXBUFSIZE];

void SignalBoard_Initial_Data(void)

{rxReadIndex  = 0;
bMassageSignalOK = false;
}

void SignalBoard_Initial_IO(void)
{
  GPIO_PinModeSet(gpioPortC, 12, gpioModePushPull, 1);
  /* Define input, no filtering */
  GPIO_PinModeSet(gpioPortC, 13, gpioModeInputPull, 0);
  
  /* Prepare struct for initializing UART in asynchronous mode*/
  signalUartInit.enable       = usartDisable;   /* Don't enable UART upon intialization */
  signalUartInit.refFreq      = 0;              /* Provide information on reference frequency. When set to 0, the reference frequency is */
  signalUartInit.baudrate     = 9600;//115200;         /* Baud rate */
  signalUartInit.oversampling = usartOVS16;     /* Oversampling. Range is 4x, 6x, 8x or 16x */
  signalUartInit.databits     = usartDatabits8; /* Number of data bits. Range is 4 to 10 */
  signalUartInit.parity       = usartNoParity;  /* Parity mode */
  signalUartInit.stopbits     = usartStopbits1; /* Number of stop bits. Range is 0 to 2 */
  
  /* Initialize USART with uartInit struct */
  USART_InitAsync(signalUart, &signalUartInit);
  
  /* Prepare UART Rx and Tx interrupts */
  USART_IntClear(signalUart, _UART_IF_MASK);
  USART_IntEnable(signalUart, UART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(UART1_RX_IRQn);
  NVIC_EnableIRQ(UART1_RX_IRQn);
  
  /* Enable I/O pins at UART1 location #3 */
  signalUart->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_LOCATION_LOC0;////3;
  
  /* Enable UART */
  USART_Enable(signalUart, usartEnable);
}


//-----------------------------------
//靠背，小腿，前滑拔掉行程开关应为高，默认通信协议为高

//宽，中、窄为低电平表示当前的位置中，短接相应的引脚为后，通信协议为高，默认为0，不在宽中窄位置
//肩位检测，当按下去为低电平，表示找到肩部位置 ，协议通信默认为高
//球不压为ON,默认为上拉   走到肩部位置以上释放揉捏球，球为OFF

//行走电机默认为下拉电阻，走到行程开关位置处为0，离开行程开关自动为高电平


void UART1_RX_IRQHandler(void)
{
    unsigned char  by_checkSum;
    /* Check for RX data valid interrupt */
    
    if(signalUart->STATUS & UART_STATUS_RXDATAV)
    {
        /*Copy data into RX Buffer*/
        unsigned char  rxData = USART_Rx(signalUart);
        
        if((rxData != 0x7e)&&(rxWriteIndex==0))return;
        if(rxData == 0x7e &&  rxWriteIndex == 0)
        {
            rxBuffer[rxWriteIndex] = rxData;//LEUART_Rx(LEUART_USED);
            rxWriteIndex++;
        }
        else
        {
            rxBuffer[rxWriteIndex] = rxData;//LEUART_Rx(LEUART_USED);
            rxWriteIndex++;
            // rxWriteIndex%=RXBUFSIZE;
            
            if (rxWriteIndex == RXBUFSIZE )
            {
                by_checkSum = rxBuffer[1];
                by_checkSum += rxBuffer[2];
                by_checkSum += rxBuffer[3];
                by_checkSum = ~by_checkSum;
                by_checkSum &= 0x7f;
                if(by_checkSum == rxBuffer[4])
                {
                    massageSignal = rxBuffer[1];
                    SwtichSignal = rxBuffer[2];
                    FlexSwtichSignal = rxBuffer[3];
                    bMassageSignalOK = true;
                    errorCount = 0;
                }
                rxWriteIndex = 0;
            }
            if (rxWriteIndex >RXBUFSIZE )
            {
                rxWriteIndex = 0;
            }     
        }   
        /* Clear RXDATAV interrupt */
        USART_IntClear(UART1, UART_IF_RXDATAV);
    }
}


bool SignalBoard_isOK(void)
{
  return(bMassageSignalOK);
}

unsigned char SignalBoard_GetMassageSignal(void)
{
  return(massageSignal);
}

unsigned char SignalBoard_GetSwitchSignal(void)
{
  return(SwtichSignal);
}

unsigned char SignalBoard_GetSwitchFlexSignal(void)
{
  return(FlexSwtichSignal);
}

void SignalBoard_10msInt(void)
{
  if(errorCount < 255) errorCount++;
  if(errorCount >10) bMassageSignalOK = false;
}


