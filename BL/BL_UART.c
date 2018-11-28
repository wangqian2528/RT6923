#include "BL_UART.h"
#include <string.h>

__no_init static BYTE abyRXBuffer[BL_RAM_BUFFER_SIZE]; 
__no_init static BYTE abyTXBuffer[BL_RAM_BUFFER_SIZE];
__no_init volatile static BYTE byteCount;

//TXD
//abyRXTXBuffer[0] length = n + 3
//abyRXTXBuffer[1] command
//abyRXTXBuffer[2~n+1] n bytes Data
//abyRXTXBuffer[n+2] CRC
//RXD
//abyRXTXBuffer[0] length = n + 4
//abyRXTXBuffer[1] command
//abyRXTXBuffer[2] status
//abyRXTXBuffer[3~n+2] n bytes data
//abyRXTXBuffer[n+3] CRC


__no_init volatile static struct
{
    unsigned TX_ENABLE    :1;
    unsigned Time_Out     :1;
    
    unsigned RECV_Start   :1;  //ESC_BYTE received
    unsigned RECV_OK      :1;
}UART_Flags;

CALLBACK BL_UartRXDHandler(void);
CALLBACK BL_UartTXDHandler(void);
CALLBACK BL_Uart10MsInt(void);

__no_init static BL_TX_STATE T_State;
__no_init static BL_RX_STATE R_State;

__no_init static USHORT R_Len;

__no_init static USHORT T_Len;
__no_init static USHORT T_Index;

//==============================================================================
// BL_UartInit
 //=============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_UartInit"
void BL_UartInit(void)
{
    // Inital Data
    T_State = BL_DIDLE;
    R_State = BL_RIDLE;
    byteCount = 0;
    R_Len = 0;
    T_Len = 0;
    T_Index = 0;

    UART_Flags.TX_ENABLE = 1;
 
    UART_Flags.RECV_Start  = 0;
    UART_Flags.RECV_OK = 0;
    
    for(SHORT i = 0; i < BL_RAM_BUFFER_SIZE; i++)
    {
        abyRXBuffer[i] = 0;
        abyTXBuffer[i] = 0;
    }
    
    
    HalRegistISR(UART_TX_ISR,BL_UartTXDHandler);
    HalRegistISR(UART_RX_ISR,BL_UartRXDHandler);
    
    CMU_ClockEnable(BL_CMUCLOCK, true);
    GPIO_PinModeSet(BL_GPIOPORT,BL_TXPIN,gpioModePushPull,1);
    GPIO_PinModeSet(BL_GPIOPORT,BL_RXPIN,gpioModeInput,0);
    GPIO_PinModeSet(BL_GPIOPORT,RIFD_INTPIN,gpioModeInput,1);
    
    USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;
    
    uartInit.enable       = usartDisable;   /* Don't enable UART upon intialization */
    uartInit.refFreq      = 0;              /* Provide information on reference frequency. When set to 0, the reference frequency is */
    uartInit.baudrate     = 115200;         /* Baud rate */
    uartInit.oversampling = usartOVS16;     /* Oversampling. Range is 4x, 6x, 8x or 16x */
    uartInit.databits     = usartDatabits8; /* Number of data bits. Range is 4 to 10 */
    uartInit.parity       = usartNoParity;  /* Parity mode */
    uartInit.stopbits     = usartStopbits1; /* Number of stop bits. Range is 0 to 2 */
#if defined(_EFM32_GIANT_FAMILY) || defined(_EFM32_TINY_FAMILY)
     uartInit.mvdis        = false;          /* Disable majority voting */
     uartInit.prsRxEnable  = false;          /* Enable USART Rx via Peripheral Reflex System */
     uartInit.prsRxCh      = usartPrsRxCh0;  /* Select PRS channel if enabled */
#endif  
    USART_InitAsync(BL_UART, &uartInit);
    
    /* Prepare UART Rx and Tx interrupts */
    USART_IntClear(BL_UART, _UART_IF_MASK);  //Clear all interrupt flag
    USART_IntEnable(BL_UART, UART_IF_RXDATAV); //Enable interrupt on RX data. 
    USART_IntEnable(BL_UART, UART_IF_TXC);     //Enable interrupt on TX complete.
    NVIC_ClearPendingIRQ(UART0_RX_IRQn);
    NVIC_ClearPendingIRQ(UART0_TX_IRQn);
    NVIC_EnableIRQ(UART0_RX_IRQn);
    NVIC_EnableIRQ(UART0_TX_IRQn);
    
    
    /* Enable I/O pins at UART0 location #2 */
    BL_UART->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_TXPEN | UART_ROUTE_LOCATION_LOC2; 
    
    /* Enable UART */
    USART_Enable(BL_UART, usartEnable); //Enable both RX and TX.

    SetTimer(BL_Uart10MsInt,10);
}

//==============================================================================
// BL_UartTXData
// inputs:
//    command
//    data parameters length
//    the pointer to the data
//==============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_UartTXData"
BOOL BL_UartTXData(BYTE byteCmd, USHORT byteLen, const BYTE *ptrData)
{
    if(UART_Flags.TX_ENABLE == 0) return 0; 
    UART_Flags.TX_ENABLE = 0;
    
    memcpy(abyTXBuffer,ptrData,byteLen);
    
    T_State = BL_DData;         // prepare the send state machine
    
    T_Index = 0;
    T_Len = byteLen;
    
    USART_IntSet(BL_UART,UART_IF_TXC); //trigger the interrupt and start to send
    return 1;
}

//==============================================================================
// BL_UartRXDHandler
 //=============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_UartRXDHandler"
CALLBACK BL_UartRXDHandler(void)
{
    if ((BL_UART->STATUS & UART_STATUS_RXDATAV) == 0x00) return;
    BYTE rxData = USART_Rx(BL_UART);          //Check for RX data valid interrupt
    USART_IntClear(BL_UART, UART_IF_RXDATAV); //Clear RXDATAV interrupt
    
    //One byte has received, reset wait RX status
    UART_Flags.RECV_Start = 1;
    byteCount = 0;
    
    WDOG_Feed();
    switch(R_State)
    {
    case BL_RIDLE:
        R_State = BL_RData;
        R_Len = 0;
    case BL_RData:
        abyRXBuffer[R_Len] =  rxData;        
        if(R_Len < BL_RAM_BUFFER_SIZE - 1)
            R_Len++;
        else
        {
            R_State = BL_RIDLE;
        }
        break;
    default:
        break;
    }
}

//==============================================================================
// BL_UartTXDHandler
 //=============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_UartTXDHandler"
CALLBACK BL_UartTXDHandler(void)
{
    USART_IntClear(BL_UART,UART_IF_TXC);  //Clear interrupt flags by reading them. 
    WDOG_Feed();
    switch(T_State)
    {
    case BL_DData:
        USART_Tx(BL_UART,abyTXBuffer[T_Index]);
        T_Index++;
        if(T_Index >= T_Len)
        {
           T_State = BL_DIDLE;
           UART_Flags.TX_ENABLE = 1;
        }
        break;
    case BL_DIDLE:
        R_State = BL_RIDLE;
        break;
    default:
        break;
    }
}


//==============================================================================
// BL_Uart10MsInt
 //=============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_Uart10MsInt"
CALLBACK BL_Uart10MsInt(void)
{
    if(UART_Flags.RECV_Start)
    {
        if(byteCount++ >= BL_WAIT_REPLY_TIME)
        {
            byteCount = 0;
            UART_Flags.RECV_Start = 0;
            UART_Flags.RECV_OK = 1;
            
            R_State = BL_RIDLE;
        }
    }
}

//==============================================================================
// BL_UartGetRecvData
// return value:
//    the pointer to the RX data
//==============================================================================
#undef FUNC_NAME
#define FUNC_NAME "BL_UartGetRecvData"
USHORT BL_UartGetRecvData(BYTE **pptrData)
{
  USHORT retLen = R_Len;
  *pptrData = abyRXBuffer;
  abyRXBuffer[R_Len] = '\0';
  R_Len = 0;    
  return retLen;
}

BOOL BL_HaveData(void)
{
  return R_Len && R_State == BL_RIDLE;
}


