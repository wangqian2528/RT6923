//#include "string.h"
#include "VoiceUart.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "ControlBox.h"

/* Declare a circular buffer structure to use for Rx and Tx queues */
//#define test_blue  1
//#define BUFFERSIZE          16
#define BUFFER_LENGTH       8

/* Setup UART1 in async mode for RS232*/
static USART_TypeDef           * uart   = UART1;
static USART_InitAsync_TypeDef uartInit = USART_INITASYNC_DEFAULT;

//static unsigned char ucRXBuffer[BUFFER_LENGTH] = {0};
//__no_init static char TxBuffer[BUFFER_LENGTH];

static volatile struct circularBuffer
{
    uint8_t  data[BUFFER_LENGTH];  /* data buffer */
    // uint32_t rdI;               /* read index */
    uint32_t wrI;               /* write index */
    uint32_t pendingBytes;      /* count of how many bytes are not yet handled */
    bool     overflow;          /* buffer overflow indicator */
} txBuf = { 0, 0, 0, false };


static volatile int     rxWriteIndex = 0;
//static unsigned char RX_Index;
static bool bPM25OK,bVoiceKeyOK;
static unsigned char voiceKey;
static unsigned int PM25 = NORMAL_CTRL;

static bool bEnablePluse;
static bool bMusicOn;
static unsigned int enablePluseCount;
static bool b100ms;
static unsigned int musicOnCounter,musicOffCounter;
static unsigned int pm25_FailCount;

/******************************************************************************
* @brief  uartSetup function
*
******************************************************************************/




/**************************************************************************//**
* @brief UART1 RX IRQ Handler
*
* Set up the interrupt prior to use
*
* Note that this function handles overflows in a very simple way.
*
*****************************************************************************/

/**************************************************************************//**
* @brief UART1 TX IRQ Handler
*
* Set up the interrupt prior to use
*
*****************************************************************************/



unsigned char VoiceUart_GetRXStatus(void)
{
    return((unsigned char)bVoiceKeyOK);
}

unsigned char VoiceUart_GetKey(void)
{
  return((unsigned char)voiceKey);
}

void VoiceUart_SetKey(unsigned char by_Data)
{
    voiceKey = by_Data;
}
void VoiceUart_ClearRXStatus(void)
{
    bVoiceKeyOK = 0;
} 

void VoiceUart_SetRXStatus(void)
{
    bVoiceKeyOK = 1;
} 

//int VoiceUart_GetPM25(unsigned int* PM)
//{
//    if(bPM25OK)
//    {
//      //bPM25OK = false;
//      *PM = PM25; 
//      return(1); 
//    }
//    else
//    {
//      //*PM = 10;
//      return(-1); 
//    } 
//}
//
//void VoiceUart_1msInt(void)
//{
//  return;  
//  //static bool justMustOn = false;
//   if(bEnablePluse)
//   {
//     enablePluseCount++;
//     if(enablePluseCount == 10)
//     {
//       if(bMusicOn) 
//       {
//    
//         UART1->ROUTE &= ~UART_ROUTE_RXPEN;
//         GPIO_PinModeSet(UART1_RX_PORT,UART1_RX_BIT,gpioModePushPull, 0);
//         __no_operation();
//       }
//     }
//     if(enablePluseCount == 20)
//     {
//       //GPIO_PinModeSet(UART1_RX_PORT,UART1_RX_BIT,UART1_RX_MODE, 1);
//    
//       UART1->ROUTE &= ~UART_ROUTE_RXPEN;
//       GPIO_PinModeSet(UART1_RX_PORT,UART1_RX_BIT,UART1_RX_MODE, 1);
//     }
//     else if(enablePluseCount > 20)
//     {
//       bEnablePluse = 0;
//       enablePluseCount = 0;
//     }
//   }
//}
void VoiceUart_100msInt(void)
{
  b100ms = 1; 
  if(pm25_FailCount > 50) //15
  {
     bPM25OK = false;
  }
  else
  {
    pm25_FailCount++; 
  }
}

//void VoiceUart_PowerOn(void)
//{
//  GPIO_PinOutSet(VOICE_POWER_PORT,VOICE_POWER_BIT); 
//}
void VoiceUart_PowerOff(void)
{
  GPIO_PinOutClear(VOICE_POWER_PORT,VOICE_POWER_BIT); 
}

void VoiceUart_SetMusicStatus(bool musicOn)
{
  if(!b100ms) return;
  b100ms = 0;
  if(musicOn) 
  {
    musicOffCounter = 0;
    
    ///*
    if(musicOnCounter > 5)
    {
      bMusicOn = 1;
    }
    else
    {
      musicOnCounter++;  
    }
    //*/
    /*
    if(musicOnCounter == 5)
    {
      VoiceUart_PowerOff();
      bMusicOn = 1;
    }
    if(musicOnCounter == 10)
    {
      VoiceUart_PowerOn();
    }
    if(musicOnCounter > 10)
    {
      musicOnCounter = 100;   
    }
    */
  }
  else
  {
    musicOnCounter = 0;
    if(musicOffCounter > 5)
    {
      bMusicOn = 0;
    }
    else
    {
      musicOffCounter++;   
    }
  }
}

