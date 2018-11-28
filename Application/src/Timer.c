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
����˵������ʱ��������ָ����ʱ�䷵��1�����򷵻�0
����1��������ʵ�ֶ�ʱʱ��ʹ�õ�����ͨ�������Ϊ8
����2�����ڿ��ƶ�ʱ�ĳ��̣���ʱʱ��Ϊ������2*100��ms��
����ֵ������ʱʱ�䷵��1��û������0
����˵���� ��ʱʱ�䣺(w_Dat/10)s
*************************************************************/
char Timer_Counter(char by_Mode,unsigned int w_Dat)
{
  char b_Out,by_Channel,by_Mask;
  b_Out=0;
  by_Channel=by_Mode & 0x7f;//0x01
  by_Mask = 0x01 << by_Channel;//0x02
  if((by_Timer_Flag & by_Mask)==0) return(0);//by_Timer_Flagÿ100ms��Ϊ0xff
  by_Timer_Flag &= ~by_Mask;  //by_Timer_Flag���û�е�100ms��Ϊ0xff������洢����by_Mask�ķ��룬����by_Mask��������0������������������
  
  if(w_Timer_Data[by_Channel] <= w_Dat) ++w_Timer_Data[by_Channel];
  if(w_Timer_Data[by_Channel] == w_Dat) b_Out=1;
  if(w_Timer_Data[by_Channel] >= w_Dat) if(by_Mode & 0x80) w_Timer_Data[by_Channel]=0;
   
  return(b_Out);     
}
