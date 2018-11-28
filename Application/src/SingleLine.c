//#include "AIIinclude.h"
#include <string.h>
#include <stdio.h>
#include "efm32.h"
#include "em_cmu.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "em_assert.h"

#include "em_letimer.h"
#include "SingleLine.h"

uint8_t Rec_data;     //���յ�һ���ֽڵ�ֵ
uint8_t Rec_Bit;      //���ջ���һ���ֽڵ�λ��

uint8_t Rec_TimeOut;  //ͨѶ��ʱ
uint8_t Rec_LEN;      //�����ֽڸ���
//uint8_t Rec_Set_LEN=7;

uint8_t SingleLine_Start_Mark;
 
uint8_t Rec_Buf[20];

uint8_t Send_BuF[20]={0xA0,0x06,0x02,0x1e,0xDA,0x0a}; 

uint8_t SendData;
uint8_t SingleLine_Receive_Send;  //ͨѶ״̬��־��ֵΪ1ʱ���ڷ�״̬��ֵΪ2ʱ Ϊ����״̬
uint16_t SingleLine_rec_OK;

uint8_t SingleLine_VOL=15;

uint8_t SingleLine_Send_Mode;
uint16_t SingleLine_Send_Time;

uint8_t SingleLine_Stop_Mark;
uint16_t SingleLine_Check_Time;
uint8_t  SingleLine_Sound_ON;
uint8_t  SingleLine_Test;
/**********************************************************************/
//1.���� BlueTooth.h
//	#define BlueTooth_Volum_PORT          gpioPortC//D
//	#define BlueTooth_Volum_BIT              4// 0
//	#define BlueTooth_Volum_MODE         gpioModeInput
/**********************************************************************/
    /* Set configurations for LETIMER 0 */
const LETIMER_Init_TypeDef letimerInit = 
    {
        .enable         = true,                   /* Start counting when init completed. */
        .debugRun       = false,                  /* Counter shall not keep running during debug halt. */
        .rtcComp0Enable = false,                  /* Don't start counting on RTC COMP0 match. */
        .rtcComp1Enable = false,                  /* Don't start counting on RTC COMP1 match. */
        .comp0Top       = true,                   /* Load COMP0 register into CNT when counter underflows. COMP0 is used as TOP */
        .bufTop         = false,                  /* Don't load COMP1 into COMP0 when REP0 reaches 0. */
        .out0Pol        = 0,                      /* Idle value for output 0. */
        .out1Pol        = 0,                      /* Idle value for output 1. */
        .ufoa0          = letimerUFOAPwm,         /* PWM output on output 0 */
        .ufoa1          = letimerUFOAPulse,       /* Pulse output on output 1*/
        .repMode        = letimerRepeatFree       /* Count until stopped */
    };
    

/******************************************************************************
* Name     :  LETIMER_setup(void)
* Param    :  None
* Return   :  None
* Function :  ��ʼ��LETIME0
* Remarks  :  
*******************************************************************************/
void LETIMER_setup(void)
{
    LETIMER_CompareSet(LETIMER0, 0, 32);  // 1s 32768
    
    /* Route LETIMER to location 0 (PD6 and PD7) and enable outputs */
    //LETIMER0->ROUTE = LETIMER_ROUTE_OUT0PEN | LETIMER_ROUTE_OUT1PEN | LETIMER_ROUTE_LOCATION_LOC0;
    /* Initialize LETIMER */
    LETIMER_Init(LETIMER0, &letimerInit); 
}
/******************************************************************************
* Name     :  SingleLine_Rec_init() 
* Param    :  None
* Return   :  None
* Function :  ͨѶ�˿ڽ��ճ�ʼ��
* Remarks  :  
*******************************************************************************/
void SingleLine_Rec_init(void)  
{
  GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_IN, 1); //����
  GPIO_IntConfig(SINGLELINE_PORT, SINGLELINE_BIT, false, true, true);   //�½����ж� 
//   NVIC_EnableIRQ(GPIO_ODD_IRQn);
   NVIC_EnableIRQ(GPIO_EVEN_IRQn);
}

/******************************************************************************
* Name     :  SingleLine_Rec_Char()
* Param    :  None
* Return   :  0 or 1
* Function :  ͨѶ����һ���ֽڣ�����һ���ֽ���ɷ���1 ���չ����з���ֵ0
* Remarks  :  
*******************************************************************************/
uint8_t SingleLine_Rec_Char()
{
 static uint16_t data;
 if(GPIO_PinInGet(SINGLELINE_PORT,SINGLELINE_BIT)==0)  data |= 1;
// GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 1);
// SingleLine_Delay(30);
// GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 0);
 Rec_Bit++;
 Rec_TimeOut = 0;
 if(Rec_Bit>=10)
 {
  Rec_data = data>>1;
  data = 0;
  Rec_Bit =0;
  LETIMER_Enable(LETIMER0, false);   //ֹͣ��ʱ
  GPIO_IntConfig(SINGLELINE_PORT, SINGLELINE_BIT, false, true, true);   //�½����ж� 
  return 1;
 }
 else 
 {
   data= data<<1;
   return 0;
 } 
}

/******************************************************************************
* Name     :  SingleLine_Rec()
* Param    :  None
* Return   :  None
* Function :  ͨѶִ�з�����ִ�н��պ�����SingleLine_Receive_SendΪ1ʱ ��������
              ���ܣ������Զ����͡�SingleLine_Receive_SendΪ2ʱ���Ҷ˿ڴ��ڽ���
              ����״̬ʱ������ʵʱ��������
* Remarks  :  ��������LETIME0�ж���
*******************************************************************************/
void SingleLine_Rec()      // Ӧ���ڶ�ʱ���ж��� ���պ���
{
//  static uint8_t SendData;
  static uint8_t SendByt=0;
//  static uint8_t SendBit;
  if(SingleLine_Receive_Send==1)    //����
    {
      if(SendData&0x80) 
      {
        GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 1);
        SingleLine_Delay(850);
        GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 0);
      }
      else              
      {
        __NOP();
        GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 0);
        SingleLine_Delay(850);
        GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 1);
      }
      SendData=SendData<<1;
      
      Rec_Bit++;
      Rec_TimeOut=0;
      if(Rec_Bit>=8)
      {
       SendByt++;
       Rec_Bit = 0;
       SendData = Send_BuF[SendByt];
      }
      if(SendByt>=Send_BuF[1]) //�������
      {
       SendByt = 0;
       // �л�������ģʽ
       SingleLine_Receive_Send =2;
       LETIMER_Enable(LETIMER0, false);   //ֹͣ��ʱ
       SingleLine_Delay(850);
       GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_IN, 1);
       SingleLine_Rec_init();
       __NOP();
       __NOP();
      }
      
    } 
    else if(SingleLine_Receive_Send==2)
    {
  
         if(SingleLine_Rec_Char()==1)
         {
           Rec_Buf[Rec_LEN]=Rec_data;
           Rec_LEN++;
           if((Rec_Buf[0]==0xE5)|((Rec_LEN>=Rec_Buf[1]) & (Rec_LEN>2)))
             SingleLine_rec_OK=1;
             if(Rec_Buf[0]==0xE5) Rec_LEN = 0;
         }
//         if(Rec_LEN>=Rec_Set_LEN)
//         {
//           Rec_Bit =0;
//           Rec_data = 0;
//           Rec_LEN = 0;
//           LETIMER_Enable(LETIMER0, false);   //ֹͣ��ʱ
//           GPIO_IntConfig(SINGLELINE_PORT, SINGLELINE_BIT, false, true, true);   //�½����ж� 
//         }
         
    }

}
/******************************************************************************
* Name     :  SingleLine_TimeOut()
* Param    :  None
* Return   :  None
* Function :  ͨѶ��ʱ��������ʱ1ms�ۼ�һ�Σ�100ms��û�з��ͻ��߽���ͨѶ��ʱ��
              ͨѶ��ʱֹͣ��ʱ��������������շ�����ر�־��
* Remarks  :  ��������Systick�ж���
*******************************************************************************/
void SingleLine_TimeOut()
{
  if(SingleLine_Send_Time!=0)SingleLine_Send_Time++;
  SingleLine_Check_Time++;
 Rec_TimeOut++;
 if(Rec_TimeOut>100)  //100ms ͨѶ��ʱ
 {
  Rec_Bit =0;
  Rec_data =0;
  Rec_LEN =0;
  LETIMER_Enable(LETIMER0, false);   //ֹͣ��ʱ
 }
}
/******************************************************************************
* Name     :  SingleLine_Interruput()
* Param    :  None
* Return   :  None
* Function :  ����ͨѶ�˿��½����жϣ���ʼ�ź��жϣ��жϺ�ر��½����У�����
              ��ʱ������ʼ���ա�
* Remarks  :  �������ڶ˿��жϺ�����
*******************************************************************************/
void SingleLine_Interruput()
{
 if(GPIO_IntGet()&(1<<SINGLELINE_BIT))
  {
    GPIO_IntClear(1<<SINGLELINE_BIT);
    GPIO_IntConfig(SINGLELINE_PORT, SINGLELINE_BIT, false, false, false);   //�½����ж�
    Rec_TimeOut = 0;
    LETIMER_setup();
    LETIMER_RepeatSet(LETIMER0, 0,32);
    LETIMER0->CNT=7;
    LETIMER_Enable(LETIMER0, true); // ��ʼ��ʱ
//    GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 1);
//    SingleLine_Delay(30);
//    GPIO_PinModeSet(gpioPortD, 10, gpioModePushPull, 0);
  }
}
/******************************************************************************
* Name     :  SingleLine_Delay(uint16_t us)
* Param    :  us
* Return   :  None
* Function :  ��ʱ1us��������������ͨѶ������ʱ��
* Remarks  :  
*******************************************************************************/
void SingleLine_Delay(uint16_t us)
{
 uint16_t i;
 for(i=0;i<us;i++)
 {
  __NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();__NOP();
  __NOP();__NOP();__NOP();
 }
}
/******************************************************************************
* Name     :  SingleLine_Send_Start()
* Param    :  None
* Return   :  None
* Function :  ����ͨѶ���ͣ�������ʼλ���رն˿��½����жϣ�������ʱ������ʼ����
* Remarks  :  
*******************************************************************************/
void SingleLine_Send_Start()
{
 SendData = Send_BuF[0]; 
 Rec_TimeOut = 0;
 GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 1);
 GPIO_IntConfig(SINGLELINE_PORT, SINGLELINE_BIT, false, false, false);
 SingleLine_Receive_Send  =1;
 SingleLine_Delay(500);
 LETIMER_setup();
 LETIMER_RepeatSet(LETIMER0, 0,32);
 LETIMER_Enable(LETIMER0, true); // ��ʼ��ʱ
 GPIO_PinModeSet(SINGLELINE_PORT, SINGLELINE_BIT, SINGLELINE_MODE_OUT, 0);
 __NOP();
}


/******************************************************************************
* Name     :  SingleLine_GetSum(uint8_t *p,uint8_t len)
* Param    :  uint8_t *p,uint8_t len
* Return   :  sum
* Function :  ����У��λ��У���ȡ����1
* Remarks  :  
*******************************************************************************/
uint8_t SingleLine_GetSum(uint8_t *p,uint8_t len)
{
	unsigned char sum = 0;
	do
	{
          sum += *p++;
	}while(--len);
	return ~sum + 1;
}
/******************************************************************************
* Name     :  SingleLine_Set_Vol(uint8_t Value)
* Param    :  Value��ȡֵ��Χ0--30
* Return   :  None
* Function :  ����������С��ֵԽ������Խ��
* Remarks  :  
*******************************************************************************/
void SingleLine_Set_Vol(uint8_t Value)
{
 Send_BuF[0]=0xA0;
 Send_BuF[1]=0x06;
 Send_BuF[2]=0x02;
 Send_BuF[3]=Value;
 Send_BuF[4]=SingleLine_GetSum(&Send_BuF[1],3);
 Send_BuF[5]=0x0A;
 SingleLine_Send_Start();  
}
/******************************************************************************
* Name     :  SingleLine_Play(uint8_t Mode,uint8_t ADDR)
* Param    :  Mode��ADDR
* Return   :  None
* Function :  ���ֲ��Ź��ܣ���ָ������ģʽ�Ͳ������ֵ�ַ
              Mode��0 ����  1 ����ѭ��  2�������� 
                    3 ˳��ѭ������      4 ��ͣ����
              ADDR: 1--254 ָ����ַ����
                    0 ������һ��  FF ������һ��
* Remarks  :  
*******************************************************************************/
void SingleLine_Play(uint8_t Mode,uint8_t ADDR)
{
 Send_BuF[0]=0xA0;
 Send_BuF[1]=0x07;
 Send_BuF[2]=0x01;
 Send_BuF[3]=Mode;
 Send_BuF[4]=ADDR;
 Send_BuF[5]=SingleLine_GetSum(&Send_BuF[1],4);
 Send_BuF[6]=0x0A;
 SingleLine_Send_Start();  
 if(Mode==4) SingleLine_Start_Mark = 0;
 else        SingleLine_Start_Mark = 1;
}

/******************************************************************************
* Name     :  SingleLine_Query()
* Param    :  None
* Return   :  None
* Function :  ��ѯ����״ָ̬��
* Remarks  :  
*******************************************************************************/
void SingleLine_Query()
{
 Send_BuF[0]=0xA0;
 Send_BuF[1]=0x05;
 Send_BuF[2]=0x03;
 Send_BuF[3]=SingleLine_GetSum(&Send_BuF[1],2);
 Send_BuF[4]=0x0A;
 SingleLine_Send_Start();  
}

/******************************************************************************
* Name     :  SigleLine_Check()
* Param    :  None
* Return   :  None
* Function :  1s��ѯһ������״̬
* Remarks  :  
*******************************************************************************/
void SigleLine_Check()
{
 if(SingleLine_Check_Time<1000) return;
 SingleLine_Check_Time=0;
 SingleLine_Query();
}

void SingleLine_Analysis()
{
  uint8_t LEN;
  if(SingleLine_rec_OK!=1) return;
  SingleLine_rec_OK = 0;
  __NOP();
  if(Rec_Buf[0]==0xE5)     
  {
    Rec_Buf[5]=0;
    return;
  }
  LEN = Rec_Buf[1];
  if(Rec_Buf[LEN-2]==SingleLine_GetSum(&Rec_Buf[1],LEN-3))
  {
   SingleLine_VOL = Rec_Buf[8];
  }
  
  if(SingleLine_Sound_ON==false)
  {
    if(Rec_Buf[5]!= 0 | Rec_Buf[5]!= 4)
    {
     SingleLine_Delay(2000); 
     SingleLine_Send_Mode = 3;
     SingleLine_Check_Time = 0;
    }
  }
  else 
  {
    if(Rec_Buf[5]== 0 | Rec_Buf[5]== 4)
    {
     SingleLine_Delay(2000); 
     SingleLine_Send_Mode = 1;
     SingleLine_Check_Time = 0;
    }
  }
}

/******************************************************************************/
///******************************************************************************/
//void SingleLinr_Send()
//{
//  static uint8_t Send_Mark;
//  if(SingleLine_Test)__NOP();
//  switch(SingleLine_Send_Mode)
//  {
//  case 0:  SingleLine_Check_Time  SingleLine_Check_Mark
//        SingleLine_Analysis();
//        if(SingleLine_Stop_Mark==1)SigleLine_Check();
//
//        if(Send_Mark==1)
//        {
//         if(Rec_Buf[0]==0xE5)         // �յ�Ӧ��ֵ
//         {
//
//           if(SingleLine_Send_Time>200)
//           {
//           Rec_Buf[0] = 0;
//           Send_Mark = 0;
//           SingleLine_Send_Mode = 2;
//           SingleLine_Send_Time = 0;
//           }
//         }
//         else if(SingleLine_Send_Time>350) // 50ms δ�յ�Ӧ��ֵ
//         {
//           SingleLine_Send_Mode = 1;
//          SingleLine_Send_Time = 0;
//         }
//        }
////        else if(Send_Mark==2)
////        {
////         if(Rec_Buf[0]==0xE5)         // �յ�Ӧ��ֵ
////         {
////           Rec_Buf[0] = 0;
////           Send_Mark = 0;
////           SingleLine_Send_Mode = 0;
////           SingleLine_Send_Time = 0;
////         }
////         else if(SingleLine_Send_Time>300) // 50ms δ�յ�Ӧ��ֵ
////         {
////           SingleLine_Send_Mode = 2;
////           SingleLine_Send_Time = 0;
////         }
////        }
//      else if(Send_Mark==3)
//        {
//         if(Rec_Buf[0]==0xE5)         // �յ�Ӧ��ֵ
//         {
//           Rec_Buf[0] = 0;
//           Send_Mark = 0;
//           SingleLine_Send_Mode = 0;
//           SingleLine_Send_Time = 0;
//         }
//         else if(SingleLine_Send_Time>300) // 50ms δ�յ�Ӧ��ֵ
//         {
//           SingleLine_Send_Mode = 3;
//           SingleLine_Send_Time = 0;
//         }
//        }
//
//      break;
//  case 1:
//        SingleLine_Set_Vol(20);
//        SingleLine_VOL = 14;
//        Send_Mark = 1;
//        SingleLine_Send_Mode = 0;
//        SingleLine_Send_Time = 1; //��ʼ��ʱ
//        SingleLine_Test =1;
//      break;
//      
//  case 2: 
//        SingleLine_Play(7,1);
//        Send_Mark = 0;
//        SingleLine_Send_Mode = 0;
//        SingleLine_Send_Time = 0;
//        SingleLine_Test = 7;        
//      break;
//  case 3: 
//        SingleLine_Play(0,1); //��ͣ
//        Send_Mark = 3;
//        SingleLine_Send_Mode = 0;
//        SingleLine_Send_Time = 1;//��ʼ��ʱ
//        SingleLine_Test = 3;
//      break;
//  }
//}

/******************************************************************************/
void SingleLinr_Send()
{
  static uint8_t Send_Mark;
  if(SingleLine_Test)__NOP();
  
   SigleLine_Check();
   SingleLine_Analysis();
  
  switch(SingleLine_Send_Mode)
  {
  case 0:   
        if(Send_Mark==1)
        {
           if(SingleLine_Send_Time>200)
           {
           Send_Mark = 0;
           SingleLine_Send_Mode = 2;
           SingleLine_Send_Time = 0;
           }
        }
      break;
  case 1:
        SingleLine_Set_Vol(15);
        SingleLine_VOL = 14;
        Send_Mark = 1;
        SingleLine_Send_Mode = 0;
        SingleLine_Send_Time = 1; //��ʼ��ʱ
        SingleLine_Test =1;
      break;
      
  case 2: 
        SingleLine_Play(7,1);
        Send_Mark = 0;
        SingleLine_Send_Mode = 0;
        SingleLine_Send_Time = 0;
        SingleLine_Test = 7;        
      break;
  case 3: 
        SingleLine_Play(0,1); //��ͣ
        Send_Mark = 3;
        SingleLine_Send_Mode = 0;
        SingleLine_Send_Time = 0;//��ʼ��ʱ
        SingleLine_Test = 3;
      break;
  }
}