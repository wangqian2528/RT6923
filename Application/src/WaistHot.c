#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "WaistHot.h"
#include "ADC_Scan.h"
#define HEAT_SET_VOLTAGE 2600
unsigned int heatOnTime = 8;
unsigned int heatCounter;  
void WaistHeat_Initial_IO(void)
{
    GPIO_PinModeSet(WAIST_HEAT_PORT, WAIST_HEAT_BIT, WAIST_HEAT_MODE, 0);   
}

void WaistHeat_100ms_Int(void)
{
  heatCounter++;
}

unsigned int WaistHeat_VoltageAdj(unsigned int setDuty)
{
  unsigned short adc24;      //此处的电压值已经扩大了100倍
  ADC_Get_Voltage(ADC_V24,&adc24);     
  if(adc24 <= HEAT_SET_VOLTAGE) 
  {
    return setDuty;        //电压值偏低，返回预设值
  }
  unsigned int scale = HEAT_SET_VOLTAGE * 100 / adc24; //计算与设定电压的比例值,百分之scale
  setDuty *= scale;
  unsigned int yushu = setDuty  % 100;
  setDuty /= 100;   //setDuty乘以百分之scale
  if(yushu > 50) setDuty++;
  
  if(setDuty >= 10)
  {
    setDuty = 10; 
  }
  return setDuty; 
  
}

void WaistHeat_On(void)
{
  #ifdef heat_1class   //1档加热
	  unsigned int timeCounter;
	  timeCounter = heatCounter;
	  if(timeCounter < heatOnTime)//unsigned int heatOnTime = 8;  800ms
	   {
		//GPIO_PinOutClear(WAIST_HEAT_PORT, WAIST_HEAT_BIT);    
             
             GPIO_PinOutSet(WAIST_HEAT_PORT, WAIST_HEAT_BIT);   
	   }//
	   else if(timeCounter < 10)//1000ms
	   {
		//GPIO_PinOutSet(WAIST_HEAT_PORT, WAIST_HEAT_BIT);    
             GPIO_PinOutClear(WAIST_HEAT_PORT, WAIST_HEAT_BIT); 
             
	   }
	   else 
	   {
		 heatOnTime = WaistHeat_VoltageAdj(10);
		heatCounter = 0;
	   }
   #else
          
   GPIO_PinOutSet(WAIST_HEAT_PORT, WAIST_HEAT_BIT);   
   #endif

}

void WaistHeat_Off(void)
{
   GPIO_PinOutClear(WAIST_HEAT_PORT, WAIST_HEAT_BIT); 
}

uint8_t WasiHeat_State()
{
 if(GPIO_PinOutGet(WAIST_HEAT_PORT,WAIST_HEAT_BIT))
   return 1;
 else return 0;
}