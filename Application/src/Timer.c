#include "timer.h"
static char by_Timer_Flag;
__no_init static unsigned int w_Timer_Data[8]; 

void Timer_Initial(void)
{
  char by_Loop;
  by_Timer_Flag=0;
  for(by_Loop=0;by_Loop < 8;by_Loop++) w_Timer_Data[by_Loop]=0;
}
void Timer_Flag_100ms_Int(void)
{
  by_Timer_Flag=0xff;
}
void Timer_Counter_Clear(char by_Index)
{
   w_Timer_Data[by_Index]=0;
}

/*************************************************************
功能说明：定时函数，到指定的时间返回1，否则返回0
参数1：用于在实现定时时所使用的数组通道，最大为8
参数2：用于控制定时的长短，定时时长为：参数2*100（ms）
返回值：到定时时间返回1，没到返回0
其他说明： 定时时间：(w_Dat/10)s
*************************************************************/
char Timer_Counter(char by_Mode,unsigned int w_Dat)
{
  char b_Out,by_Channel,by_Mask;
  b_Out=0;
  by_Channel=by_Mode & 0x7f;//0x01
  by_Mask = 0x01 << by_Channel;//0x02
  if((by_Timer_Flag & by_Mask)==0) return(0);//by_Timer_Flag每100ms变为0xff
  by_Timer_Flag &= ~by_Mask;  //by_Timer_Flag如果没有到100ms变为0xff，则其存储的是by_Mask的反码，则与by_Mask相与总是0，则函数不向下面运行
  
  if(w_Timer_Data[by_Channel] <= w_Dat) ++w_Timer_Data[by_Channel];
  if(w_Timer_Data[by_Channel] == w_Dat) b_Out=1;
  if(w_Timer_Data[by_Channel] >= w_Dat) if(by_Mode & 0x80) w_Timer_Data[by_Channel]=0;
   
  return(b_Out);     
}
