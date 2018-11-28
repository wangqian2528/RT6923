#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "Data_Cul.h"
__no_init static unsigned int w_Time;
__no_init static unsigned int programExecTime; //����ִ�е�ʱ�䣬�Զ������л���Ӱ�����ʱ��
__no_init static bool bStart ;
__no_init static bool bSecond;

void Data_Init(void)
{
  w_Time = DEFAULT_RUN_TIME;
  bStart = 0;
  bSecond = 0;
  programExecTime = 0;
}

void Data_Set_Start(char by_Dat,unsigned int time)
{
    if(by_Dat) 
    {
        bStart = 1;
        w_Time = time;
    }
    else 
    {
        bStart = 0;
        w_Time = 0;
    }
    if(bStart == 0)
    {
        programExecTime = 0; 
    }
}

void Data_Flag_Int(void)
{
   bSecond = 1;
}
unsigned int Data_Get_Time(void)
{
    unsigned int out = 0;
    
    out = w_Time/60;
    if((w_Time % 60) != 0) out++;  
    return(out);
}
unsigned int Data_Get_TimeSecond(void)
{
    return(w_Time);
}
unsigned int Data_Get_ProgramExecTime(void)
{
    return(programExecTime);
}
void Data_Clear_ProgramExecTime(void)
{
    programExecTime = 0;
}
void Data_Set_Time(unsigned int time)
{
    w_Time = time;
}
void Data_Update_Time(unsigned int time)
{
    if(!bStart) return;
    w_Time = time;
}

extern unsigned long massage_step_tm_flag;
extern unsigned long massage_step_tm;  //by_Time30s;
void  Clr_Massage_Step_Timer(void)
{
    
    massage_step_tm = 0; //by_Time30s = 0;	
    return;
}

/************************************************************
����˵����ÿ1sִ��һ�ν���Ħʱ�������1���������Ŀ���ʱ��ÿ1s��1
��������
����ֵ����ʵ������
����˵����������w_time�������ã����ڿ��ư�Ħ�εİ�Ħʱ��
************************************************************/
unsigned int Data_Time_Counter_Proce(void)
{
  if(!bStart) return(0);
  if(!bSecond) return(0);
  bSecond = 0;
 if(w_Time > 0) w_Time--;
 if(programExecTime >= 99*59*59)
   programExecTime = 0;
 else
   programExecTime++;
 
 
  //------------------------------------------------------------
 //---------��������Ķ�ʱ,����Ƚ�׼��---------
 //------------------------------------------------------------
	   if(massage_step_tm>=(60)) //60S
	   {
		    massage_step_tm = 0;
		    //
		    massage_step_tm_flag = 1;		//һ����ʱ���־λ		
	   }
	   else
	   {
		massage_step_tm++;

	   } 
 //----------------------------------------- 
 
 
 
 return(1);
}


