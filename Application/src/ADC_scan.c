/******************************************************************************
 * @file
 * @brief ADC scan conversion example
 * @author Energy Micro AS
 * @version 1.07
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2010 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_dma.h"
#include "em_adc.h"
//#include "rtcdrv.h"
#include "DMA_Ctrl.h"
#include "ADC_Scan.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** DMA channel used for scan sequence sampling adc channel 2, 3 and 4. */
#define DMA_ADC_CHANNEL    2

/*
#ifdef heat_1class     //1档加热

#define NUM_SAMPLES    6
#else
#define NUM_SAMPLES   7
#endif*/
#define NUM_SAMPLES   4
/*******************************************************************************
 ***************************   LOCAL FUNCTIONS   *******************************
 ******************************************************************************/
uint32_t samples[NUM_SAMPLES];
unsigned int* pADC = samples;
volatile bool bUpdataADC;
volatile bool bADC_Enable;
/**************************************************************************//**
 * @brief  Call-back called when ADC transfer is complete
 *****************************************************************************/
void transferComplete(unsigned int channel, bool primary, void *user)
{
  (void) channel;
  (void) primary;
  (void) user;

  /* Clearing flag to indicate that transfer is complete */
 // transferActive = false;  
  DMA_ActivateBasic(DMA_ADC_CHANNEL,
                      true,
                      false,
                      samples,
                      (void *)((uint32_t) &(ADC0->SCANDATA)),
                      NUM_SAMPLES - 1);
  bUpdataADC = true;
  ADC_Start(ADC0, adcStartScan);
}

/***************************************************************************//**
* @brief
*   Configure ADC for scan mode.
#define ADC_Heat        0
#define ADC_V24         1
#define ADC_AUDIO_L     2
#define ADC_AUDIO_R     3
*******************************************************************************/
static void ADCConfig(void)
{
  ADC_Init_TypeDef     init     = ADC_INIT_DEFAULT;
  ADC_InitScan_TypeDef scanInit = ADC_INITSCAN_DEFAULT;

  /* Init common issues for both single conversion and scan mode */
  init.timebase = ADC_TimebaseCalc(0);
  init.prescale = ADC_PrescaleCalc(7000000, 0);
  /* Set ADC clock to 1 MHz, use default HFPERCLK */
  //  init.prescale = ADC_PrescaleCalc(1000000, 0);
    
    /* Set an oversampling rate for more accuracy */
    init.ovsRateSel = adcOvsRateSel8;
  ADC_Init(ADC0, &init);

  /* Init for scan sequence use ( for dvk: accelerometer X, Y and Z axis). */
  scanInit.reference = adcRefVDD;
  /*
#ifdef heat_1class     //1档加热
    scanInit.input     = //ADC_SCANCTRL_INPUTMASK_CH0 |
                       //ADC_SCANCTRL_INPUTMASK_CH1 |
                       ADC_SCANCTRL_INPUTMASK_CH2 |
                       ADC_SCANCTRL_INPUTMASK_CH3 |
                       ADC_SCANCTRL_INPUTMASK_CH4 |
                       ADC_SCANCTRL_INPUTMASK_CH5 |
                       ADC_SCANCTRL_INPUTMASK_CH6 |
                       ADC_SCANCTRL_INPUTMASK_CH7;  
  
#else
  scanInit.input     = ADC_SCANCTRL_INPUTMASK_CH0 |
                       //ADC_SCANCTRL_INPUTMASK_CH1 |
                       ADC_SCANCTRL_INPUTMASK_CH2 |
                       ADC_SCANCTRL_INPUTMASK_CH3 |
                       ADC_SCANCTRL_INPUTMASK_CH4 |
                       ADC_SCANCTRL_INPUTMASK_CH5 |
                       ADC_SCANCTRL_INPUTMASK_CH6 |
                       ADC_SCANCTRL_INPUTMASK_CH7;     
#endif
  */
  
        scanInit.input  =                  ADC_SCANCTRL_INPUTMASK_CH4 |
                       ADC_SCANCTRL_INPUTMASK_CH5 |
                       ADC_SCANCTRL_INPUTMASK_CH6 |
                       ADC_SCANCTRL_INPUTMASK_CH7;    
  scanInit.acqTime = adcAcqTime16;
 // scanInit.rep = true;
  scanInit.prsEnable = true;
  if(bADC_Enable)
  {
    ADC_InitScan(ADC0, &scanInit);
  }
}


/***************************************************************************//**
* @brief
*   Configure DMA usage for this application.
*******************************************************************************/
static void DMAConfig(void)
{
  
  DMA_CfgDescr_TypeDef   descrCfg;
  DMA_CfgChannel_TypeDef chnlCfg;

  
  cb[DMA_ADC_CHANNEL].cbFunc  = transferComplete;
  cb[DMA_ADC_CHANNEL].userPtr = NULL;

  chnlCfg.highPri   = false;
  chnlCfg.enableInt = true;
  chnlCfg.select    = DMAREQ_ADC0_SCAN;
 // chnlCfg.cb        = &(cb);
  chnlCfg.cb        = &cb[DMA_ADC_CHANNEL];
  DMA_CfgChannel(DMA_ADC_CHANNEL, &chnlCfg);

  descrCfg.dstInc  = dmaDataInc4;
  descrCfg.srcInc  = dmaDataIncNone;
  descrCfg.size    = dmaDataSize4;
  descrCfg.arbRate = dmaArbitrate1;
  descrCfg.hprot   = 0;
  DMA_CfgDescr(DMA_ADC_CHANNEL, true, &descrCfg);
  DMA_ActivateBasic(DMA_ADC_CHANNEL,
                      true,
                      false,
                      samples,
                      (void *)((uint32_t) &(ADC0->SCANDATA)),
                      NUM_SAMPLES - 1);
}

void ADC_Data_Init(void)
{
  bADC_Enable = true;
  ADCConfig();
  DMAConfig();
  ADC_Start(ADC0, adcStartScan);
}

int ADC_Get_Updata(void)
{
  if(!bUpdataADC) 
    {
      return -1;
    }
    bUpdataADC = false;    
    return 1;
}

int ADC_Get_ADC(unsigned short* ADC_L,unsigned short* ADC_R)
{
    int retval  = -1;
    if(!bUpdataADC) 
    {
      return retval;
    }
    bUpdataADC = false;    
    *ADC_L = samples[ADC_AUDIO_L];
    *ADC_R = samples[ADC_AUDIO_R];
    retval = 1;
    return retval;
}

unsigned short ADC_Convert_Voltage(unsigned short adc)
{
    unsigned int result;
    result = adc;
    result *= 3630;  //4.7K电阻和47K电阻 扩大11倍，并且还要扩大100倍
    result /= 4095;  //此处的电压值扩大了100倍
    return((unsigned short)result);
}
unsigned short ADC_Convert_Voltage_heat(unsigned short adc)//返回AD采样的毫伏
{
    unsigned int result;
    result = adc;
    result *= 3300;  //，并且还要扩大1000倍
    result /= 4095;  //此//返回AD采样的毫伏
    return((unsigned short)result);


}

/**************************************************************************//**
* @brief Convert ADC sample values to celsius.
* @note See section 2.3.4 in the reference manual for details on this
*       calculatoin
* @param adcSample Raw value from ADC to be converted to celsius
* @return The temperature in degrees Celsius.
*****************************************************************************/
float convertToCelsius(uint32_t adcSample)
{
    float temp;
    /* Factory calibration temperature from device information page. */
    float cal_temp_0 = (float)((DEVINFO->CAL & _DEVINFO_CAL_TEMP_MASK) 
                               >> _DEVINFO_CAL_TEMP_SHIFT);
    
    float cal_value_0 = (float)((DEVINFO->ADC0CAL2 
                                 & _DEVINFO_ADC0CAL2_TEMP1V25_MASK) 
                                >> _DEVINFO_ADC0CAL2_TEMP1V25_SHIFT);
    
    /* Temperature gradient (from datasheet) */
    float t_grad = -6.27;
    
    temp = (cal_temp_0 - ((cal_value_0 - adcSample)  / t_grad));
    
    return temp;
}

unsigned int ADC_Get_Inttemp(void)
{
  //  unsigned int intTemp = (unsigned int)(convertToCelsius(w_ADC_Result[ADC_TEMP]) * 10);
    unsigned int intTemp = 2500;
    return(intTemp);
}
unsigned short ADC_Get_Voltage(unsigned char channel,unsigned short* voltage)
{
    int retval  = -1;
    switch(channel)
    {
   /*   
    case ADC_Vwalk:
        *voltage = ADC_Convert_Voltage(samples[ADC_Vwalk]);
        break;
    case ADC_Vknock:
        *voltage = ADC_Convert_Voltage(samples[ADC_Vknock]);
        break;
   */   
    case  ADC_Heat:
      *voltage = ADC_Convert_Voltage_heat(samples[ADC_Heat]);
      break;
   // case ADC_Vaxis:
    //    *voltage = ADC_Convert_Voltage(samples[ADC_Vaxis]);
    //    break;    
    case ADC_V24:
        *voltage = ADC_Convert_Voltage(samples[ADC_V24]);
        break;
 //   case ADC_VCC:
  //      *voltage = ADC_Convert_Voltage(samples[ADC_VCC]);
  //      break;
  //  case ADC_V24_1:
  ////      *voltage = ADC_Convert_Voltage(samples[ADC_V24_1]);
   //     break;
        
	
	
	
    case ADC_AUDIO_L:
    case ADC_AUDIO_R:
   // case ADC_VDDCPU:
   // case ADC_TEMP:
    default: return retval;
    }
    retval = 1;
    return retval;
}
 
void ADC_Stop (void)
{
  bADC_Enable = true;
}
void ADC_Enable(void)
{
  bADC_Enable = false;
  ADC_Start(ADC0, adcStartScan);
}
