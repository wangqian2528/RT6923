#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_dma.h"
#include "em_leuart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"
#include "DMA_Ctrl.h"
#include "LEUart_DMA.h"
#include "string.h"

static unsigned char massageSignal,massage3DPluse,massage3D_Speed,SwtichSignal;
static bool  bMassageSignalOK;
static unsigned char volatile errorCount;

#define LEUART_USED     LEUART1
#define LEUART_IRQ      LEUART1_IRQn
#define LEUART_CLK      cmuClock_LEUART1

#define RXBUFSIZE  6

static volatile int     rxReadIndex  = 0;
static volatile int     rxWriteIndex = 0;
static volatile int     rxCount      = 0;
static volatile uint8_t rxBuffer[RXBUFSIZE];

void LEUART1_Initial_Data(void)

{rxReadIndex  = 0;
bMassageSignalOK = false;
}

void LEUART1_Initial_IO(void)
{
  LEUART_TypeDef *leuart = LEUART_USED;
  LEUART_Init_TypeDef init = LEUART_INIT_DEFAULT;
  
  
  /* Enable EFM32 to access peripheral Serial Port B */
  
  /* Enable CORE LE clock in order to access LE modules */
  CMU_ClockEnable(cmuClock_CORELE, true);
  
  /* Select LFXO for LEUARTs (and wait for it to stabilize) */
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
  // CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
  /* Do not prescale clock */
  CMU_ClockDivSet(LEUART_CLK, cmuClkDiv_1);
  
  /* Enable clock */
  CMU_ClockEnable(LEUART_CLK, true);
  
  /* Use default location 0: TX - Pin C6, RX - Pin C7 */
  /* To avoid false start, configure output as high */
  GPIO_PinModeSet(gpioPortC, 6, gpioModePushPull, 1);
  /* Define input, no filtering */
  GPIO_PinModeSet(gpioPortC, 7, gpioModeInput, 1);
  
  /* Enable pins at default location */
  leuart->ROUTE = LEUART_ROUTE_RXPEN | LEUART_ROUTE_TXPEN|LEUART_ROUTE_LOCATION_LOC0;
  
  /* Configure LEUART1 */
  init.enable = false;
  LEUART_Init(leuart, &init);
  
  /* Clear previous RX interrupts */
  LEUART_IntClear(leuart, LEUART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(LEUART1_IRQn);
  
  /* Enable RX interrupts */
  LEUART_IntEnable(leuart, LEUART_IF_RXDATAV);
  NVIC_EnableIRQ(LEUART1_IRQn);
  leuart->CTRL = LEUART_CTRL_RXDMAWU|LEUART_CTRL_TXDMAWU  ;
  //leuart->CMD = 5;           
  /* Finally enable it */
  LEUART_Enable(leuart, leuartEnable);
}


//-----------------------------------
//������С�ȣ�ǰ���ε��г̿���ӦΪ�ߣ�Ĭ��ͨ��Э��Ϊ��

//���С�խΪ�͵�ƽ��ʾ��ǰ��λ���У��̽���Ӧ������Ϊ��ͨ��Э��Ϊ�ߣ�Ĭ��Ϊ0�����ڿ���խλ��
//��λ��⣬������ȥΪ�͵�ƽ����ʾ�ҵ��粿λ�� ��Э��ͨ��Ĭ��Ϊ��
//��ѹΪON,Ĭ��Ϊ����   �ߵ��粿λ�������ͷ���������ΪOFF

//���ߵ��Ĭ��Ϊ�������裬�ߵ��г̿���λ�ô�Ϊ0���뿪�г̿����Զ�Ϊ�ߵ�ƽ

void LEUART1_IRQHandler(void)
{
  unsigned char  by_checkSum;
  if (LEUART_USED->IF & LEUART_IF_RXDATAV)
  {
    unsigned char  rxData =LEUART_Rx(LEUART_USED);
    
    if((rxData != 0x7e)&&(rxWriteIndex==0))return;
    if(   rxData==0x7e &&  rxWriteIndex==0)
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
          SwtichSignal=rxBuffer[2];
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
  }
  
  //  USART_IntClear(UART1, UART_IF_RXDATAV);
}


bool LEUART1_isOK(void)
{
  return(bMassageSignalOK);
}

unsigned char LEUART1_GetMassageSignal(void)
{
  return(massageSignal);
}

unsigned char LEUART1_GetSwitchSignal(void)
{
  return(SwtichSignal);
}


void LEUART1_10msInt(void)
{
  if(errorCount < 255) errorCount++;
  if(errorCount >10) bMassageSignalOK = false;
}

