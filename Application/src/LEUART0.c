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

static unsigned char ucRXBuffer1[BUFFER_LENGTH] = {0};
static unsigned char ucTXBuffer1[BUFFER_LENGTH] = {0};
/* DMA control block, must be aligned to 256. */
//#pragma data_alignment=256
//extern DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2];
static unsigned char massageSignal,massage3DPluse;
static unsigned short walkPluse;
static bool  bMassageSignalOK;
static unsigned char volatile errorCount;
void LEUART0_Initial_Data(void)
{
  bMassageSignalOK = false;
}
void LEUART0_Initial_IO(void)
{
  //test
    LEUART_Init_TypeDef Dmauart_Init = DMAUART_UART_Init;
    
    /* Reseting and initializing LEUART1 */
    LEUART_Reset(DMAUART);

    LEUART_Init(DMAUART, &Dmauart_Init);
    
    /* Route LEUART1 TX pin to DMA location 0 */
    DMAUART->ROUTE = DMAUART_ROUTE_EN | DMAUART_ROUTE_LOCATION;
    
    /* Enable GPIO for LEUART0.  */
    GPIO_PinModeSet(DMAUART_TX_PORT,DMAUART_TX_BIT,DMAUART_TX_MODE,1);
    GPIO_PinModeSet(DMAUART_RX_PORT,DMAUART_RX_BIT,DMAUART_RX_MODE,1);
    
    DMA_CfgChannel_TypeDef chnlRxCfg = DMAUART_RX_CfgChannel;
    DMA_CfgChannel(DMAUART_DMA_RX_CHANNEL, &chnlRxCfg);
    
    DMA_CfgDescr_TypeDef descrRxCfg = DMAUART_RX_CfgDescriptor;
    DMA_CfgDescr(DMAUART_DMA_RX_CHANNEL, true, &descrRxCfg);

    /* Starting the transfer. Using Basic Mode */
    DMA_ActivateBasic(DMAUART_DMA_RX_CHANNEL,     /* Activate channel selected */
                      true,                       /* Use primary descriptor */
                      false,                      /* No DMA burst */
                      (void *) &ucRXBuffer1,       /* Destination address */
                      (void *) &DMAUART->RXDATA,  /* Source address*/
                      BUFFER_LENGTH - 1);         /* Size of buffer minus1 */
    
    /* Set LEUART signal frame */
    DMAUART->SIGFRAME = EOI;
    
    DMAUART->STARTFRAME = SOI;
    
    
    /* Initial TX DMA */
    DMA_CfgChannel_TypeDef chnlTxCfg = DMAUART_TX_CfgChannel;
    DMA_CfgChannel(DMAUART_DMA_TX_CHANNEL, &chnlTxCfg);
    
    DMA_CfgDescr_TypeDef descrTxCfg = DMAUART_TX_CfgDescriptor;
    DMA_CfgDescr(DMAUART_DMA_TX_CHANNEL, true, &descrTxCfg);
    
    /* Set new DMA destination address directly in the DMA descriptor */
    (dmaControlBlock + DMAUART_DMA_TX_CHANNEL)->DSTEND = &DMAUART->TXDATA;
    
    
    /* Enable LEUART Signal Frame Interrupt */
    LEUART_IntEnable(DMAUART, DMAUART_IEN_STARTF | DMAUART_IEN_SIGF | DMAUART_IEN_TXC);
    
    /* Enable LEUART1 interrupt vector */
    NVIC_EnableIRQ(DMAUART_IRQ);
    
    /* Make sure the LEUART wakes up the DMA on RX data */
    DMAUART->CTRL = LEUART_CTRL_RXDMAWU;
     DMA->IEN &= ~0X0006;
}

void LEUART0_Transmit_Packet(unsigned char* buf,unsigned int length)
{
    memcpy(ucTXBuffer1,buf,length);
  
    (dmaControlBlock + DMAUART_DMA_TX_CHANNEL)->SRCEND = ucTXBuffer1 + length - 1;
    
    /* (Re)starting the transfer. Using Basic Mode */
    DMA_ActivateBasic(DMAUART_DMA_TX_CHANNEL,       /* Activate channel selected */
                    true,                         /* Use primary descriptor */
                    false,                        /* No DMA burst */
                    NULL,                         /* Keep destination address */
                    NULL,                         /* Keep source address*/
                    length - 1);           /* Size of buffer minus1 */
}

void LEUART0_IRQHandler(void)
{
  unsigned long leuartif;
  unsigned long len;
  /* Store and reset pending interupts */
  leuartif = LEUART_IntGet(DMAUART);
  LEUART_IntClear(DMAUART, leuartif);

  /* Signal frame found. */
  if (leuartif & LEUART_IF_SIGF)
  {  //接收到正确的结束祯信号，取出数据
    /* Zero-terminate rx buffer */
    len  = BUFFER_LENGTH - (dmaControlBlock->CTRL >> 4) & 0x3FF;
    
    if(len==6)  //判断数据长度
    {
       massageSignal = ucRXBuffer1[0];
       massage3DPluse = ucRXBuffer1[1];
       walkPluse = ucRXBuffer1[2];
       walkPluse = walkPluse << 7;
       walkPluse |= ucRXBuffer1[3];
       bMassageSignalOK = true;
       errorCount = 0;
    }
  }
  if(leuartif & LEUART_IF_STARTF)  //接收到正确的开始祯信号，重置DMA
  {
      /* Reactivate DMA */
      DMA_ActivateBasic(DMAUART_DMA_RX_CHANNEL,/* Activate DMA channel 0 */
                        true,            /* Activate using primary descriptor */
                        false,           /* No DMA burst */
                        NULL,            /* Keep source */
                        NULL,            /* Keep destination */
                        BUFFER_LENGTH - 1);/* Number of DMA transfer elements (minus 1) */
  }
  if (leuartif & LEUART_IF_TXBL)
  {
      len++; // just for test
  }
}

bool LEUART0_isOK(void)
{
  return(bMassageSignalOK);
}

unsigned char LEUART0_GetMassageSignal(void)
{
  return(massageSignal);
}

unsigned char LEUART0_Get3DPluse(void)
{
  return(massage3DPluse);
}
unsigned short LEUART0_GetWalkPluse(void)
{
  return(walkPluse);
}
void LEUART0_10msInt(void)
{
  if(errorCount < 255) errorCount++;
  if(errorCount > 20) bMassageSignalOK = false;
}

