#ifndef __SINGLELINE_H
#define __SINGLELINE_H

#ifdef __cplusplus
 extern "C" {
#endif
   
 #define SINGLELINE_PORT         1//gpioPortC
 #define SINGLELINE_BIT          4
 #define SINGLELINE_MODE_OUT         gpioModePushPull //output 
 #define SINGLELINE_MODE_IN     gpioModeInputPullFilter 


 extern  uint8_t SingleLine_Start_Mark;
 
 extern uint8_t SingleLine_VOL;
extern  uint8_t SingleLine_Send_Mode;
extern uint8_t SingleLine_Stop_Mark;
extern uint8_t  SingleLine_Sound_ON;
 //void SingleLine_Init();
//void LETIMER_setup(void);

void SingleLine_Interruput();
void SingleLine_Delay(uint16_t us);
uint8_t SingleLine_Rec_Char();
void SingleLine_Rec();
void SingleLine_TimeOut();

void SingleLine_Set_Vol(uint8_t Value);
void SingleLine_Play(uint8_t Mode,uint8_t ADDR);
void SingleLine_Analysis();
void SingleLinr_Send();
void SingleLine_Rec_init(void);

#ifdef __cplusplus
}
#endif
#endif /* __DAC_H */