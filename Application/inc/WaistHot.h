#ifndef __WAISTHOT_H__
#define __WAISTHOT_H__

#define WAIST_HEAT_PORT   gpioPortA
#define WAIST_HEAT_BIT   10// 7
#define WAIST_HEAT_MODE   gpioModePushPull

void WaistHeat_Initial_IO(void);
void WaistHeat_On(void);
void WaistHeat_Off(void);
void WaistHeat_100ms_Int(void);
uint8_t WasiHeat_State();
#endif
