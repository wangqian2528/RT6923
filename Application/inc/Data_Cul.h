#ifndef __DATA_CUL_H__
#define __DATA_CUL_H__
#define DEFAULT_RUN_TIME 60*20
#define DEFAULT_RUN_TEST_TIME 60*1

#define RUN_TIME_5  60*5
#define RUN_TIME_10 60*10
#define RUN_TIME_20 60*20
#define RUN_TIME_30 60*30
#define RUN_TIME_14 60*14

#define VALVE_START_TIME  25//3*60
void Data_Init(void);
void Data_Flag_Int(void);
unsigned int Data_Get_Time(void);
void Data_Set_Time(unsigned int time);
unsigned int Data_Time_Counter_Proce(void);
unsigned int Data_Get_TimeSecond(void);
void Data_Set_Start(char by_Dat,unsigned int time);
void Data_Update_Time(unsigned int time);
//����ִ��ʱ�� ���ض�����
unsigned int Data_Get_ProgramExecTime(void);
void Data_Clear_ProgramExecTime(void);


void  Clr_Massage_Step_Timer(void);

#endif