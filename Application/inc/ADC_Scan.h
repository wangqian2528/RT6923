#ifndef __ADC_H__
#define __ADC_H__
/*
#ifdef heat_1class     //1µµº”»»
#define ADC_Vaxis       0
#define ADC_VCC         1
#define ADC_V24         2
#define ADC_V24_1       3
#define ADC_AUDIO_L     4
#define ADC_AUDIO_R     5


#else
#define ADC_Heat      0
#define ADC_Vaxis      1
#define ADC_VCC         2
#define ADC_V24         3
#define ADC_V24_1       4
#define ADC_AUDIO_L     5
#define ADC_AUDIO_R     6

#endif*/

#define ADC_Heat        0
#define ADC_V24         1
#define ADC_AUDIO_L     2
#define ADC_AUDIO_R     3


#define ADC_INITSINGLE_RT8600S                                                      \
  { adcPRSSELCh0,              /* PRS ch0 (if enabled). */                          \
    adcAcqTime1,               /* 1 ADC_CLK cycle acquisition time. */              \
    adcRef1V25,                /* 1.25V internal reference. */                      \
    adcRes8Bit,               /* 12 bit resolution. */                             \
    adcSingleInpCh4,           /* CH4 input selected. */                            \
    false,                     /* Single ended input. */                            \
    false,                     /* PRS disabled. */                                  \
    false,                     /* Right adjust. */                                  \
    false                      /* Deactivate conversion after one scan sequence. */ \
  }

extern unsigned int* pADC;

void ADC_1ms_Int(void);
void ADC_Data_Init(void);
//int ADC_Get_ADC(unsigned char channel,unsigned short* ADC);
int ADC_Get_ADC(unsigned short* ADC_L,unsigned short* ADC_R);
unsigned short ADC_Get_Voltage(unsigned char channel,unsigned short* voltage);
unsigned int ADC_Get_Inttemp(void);
int ADC_Get_Updata(void);

unsigned short ADC_Convert_Voltage_heat(unsigned short adc);


#endif /*__ADC_H__*/