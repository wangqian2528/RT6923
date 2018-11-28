#ifndef __INDICATELED_H__
#define __INDICATELED_H__

#define INDICATE_LED_PORT   gpioPortC
#define INDICATE_LED_BIT    14//8
#define INDICATE_LED_MODE   gpioModePushPull

void IndicateLED_Initial_IO(void);
void IndicateLED_On(void);
void IndicateLED_Off(void);
void IndicateLED_Toggle(void);
#endif
