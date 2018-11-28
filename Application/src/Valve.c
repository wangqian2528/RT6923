#include "efm32_types.h"
#include "efm32_def.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "LegKnead_Uart.h"
#include "Roller_Uart.h"
#include "Flex_Uart.h"
#include "Valve.h"
#include "Input.h"
#include "backaction.h"

extern BITS GlobalFlags7;
#define bKeyArmPadIn             	        GlobalFlags7.bD5
#define bKeyArmPadOut 			        GlobalFlags7.bD6

static bool bAutoRoller,bManRollerZero;//����
unsigned int nRoller3sCnt;
extern bool  bLegKneadEnableonly;
extern bool  bAUTO1AirEnable;
#define VALVE_DATA_LENGTH   3//3// 2

unsigned char ucSendData[VALVE_DATA_LENGTH];
unsigned char ucReceiveData[VALVE_DATA_LENGTH];
//unsigned char* pValveData = ucSendData;
unsigned char* pInputData = ucReceiveData;
unsigned int w_RollerCounter,bSholderEnable;
unsigned int SholderTime = 0;
static bool bAutoRoller;
//�ֶ�ģʽPWM����
__no_init unsigned int w_RollerPWM;
//�ֶ�ģʽ �ٶȺͷ�ʽ
unsigned char LegKneadSpeed;
unsigned char LegKneadMode;
static bool bValveFlag,bRollerFlag;
extern StretchStruct st_Stretch;

extern  StretchStruct st_GrowthStretch;

extern unsigned int  GrowthStepMaxA;//  
extern unsigned int  GrowthStepMaxB;//
extern __no_init unsigned char nBackMainRunMode,nBackSubRunMode ;


__no_init static unsigned char nKeyAirBagStrength;
//74595����ת��(4Ƭ74595)
BITS BITS_ValveData[3];//��3��Ԫ�أ�ÿ��Ԫ�ص�ÿһλ����һ�����������ɿ���24������
//static bool bKneadLegEnable;
//unsigned int w_KneadLegCount;
bool bLegAirBagOn;

bool bBackauto;
void Valve_Initial_IO(void)
{
    USART_TypeDef *spi = VALVE_SPI;
    USART_InitSync_TypeDef InitSync_Init = VALVE_USART_INITSYNC;
    
    /* Clearing old transfers/receptions, and disabling interrupts */
    //spi->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    //spi->IEN = 0;
    
    USART_InitSync(spi,&InitSync_Init);
    
    USART0->ROUTE = (USART0->ROUTE & ~_USART_ROUTE_LOCATION_MASK) | USART_ROUTE_LOCATION_LOC1;
    /* Enabling pins and setting location */
    spi->ROUTE |= USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_CLKPEN;
    
    /* Clear previous interrupts */
    //spi->IFC = _USART_IFC_MASK;
    
    
    
    /*
    USART_TypeDef *spi = VALVE_SPI;
    USART_InitSync_TypeDef InitSync_Init = VALVE_USART_INITSYNC;
    
    spi->CMD   = USART_CMD_MASTEREN | USART_CMD_TXEN ;
    spi->CTRL |= USART_CTRL_AUTOCS;
    
    spi->IEN = 0;
    
    spi->ROUTE = USART_ROUTE_TXPEN | USART_ROUTE_CLKPEN | VALVE_SPI_ROUTE_LOCAITON;
    
    spi->IFC = _USART_IFC_MASK;
    
    USART_InitSync(spi,&InitSync_Init);
    
    IO configuration */
    // GPIO_PinModeSet(VALVE_POWER_PORT,VALVE_POWER_BIT,VALVE_POWER_MODE,0);
    //   GPIO_PinModeSet(VALVE_LOAD_PORT,VALVE_LOAD_BIT,VALVE_LOAD_MODE,0);
    GPIO_PinModeSet(VALVE_CLK_PORT,VALVE_CLK_BIT,VALVE_CLK_MODE,0);
    GPIO_PinModeSet(VALVE_LATCH_PORT,VALVE_LATCH_BIT,VALVE_LATCH_MODE,1);
    GPIO_PinModeSet(VALVE_DATA_PORT,VALVE_DATA_BIT,VALVE_DATA_MODE,1);
    // GPIO_PinModeSet(VALVE_DATA_IN_PORT,VALVE_DATA_IN_BIT,VALVE_DATA_IN_MODE,1);
    GPIO_PinModeSet(VALVE_AIRPUMP1_PORT,VALVE_AIRPUMP1_BIT,VALVE_AIRPUMP1_MODE,0);
    GPIO_PinModeSet(VALVE_AIRPUMP2_PORT,VALVE_AIRPUMP2_BIT,VALVE_AIRPUMP2_MODE,0);
    // GPIO_PinModeSet(VALVE_AIRPUMP3_PORT,VALVE_AIRPUMP3_BIT,VALVE_AIRPUMP3_MODE,0);
    // GPIO_PinModeSet(VALVE_OZON_PORT,VALVE_OZON_BIT,VALVE_OZON_MODE,0);
    
    //    Power_All_On();
    BITS_ValveData[0].nByte = 0;//0;
    BITS_ValveData[1].nByte =0;//0X0;
    BITS_ValveData[2].nByte =0;// 0;
}

void Valve_Initial_Data(void)
{
    w_RollerPWM = ROLLER_SPEED_STOP;
//    LegKneadSpeed = LEG_KNEAD_SPEED_STOP;
    nKeyAirBagStrength = 0;
}


void Valve_SetData(void)
{
    GPIO_PinOutSet(VALVE_DATA_PORT,VALVE_DATA_BIT);
}
void Valve_ClearData(void)
{
    GPIO_PinOutClear(VALVE_DATA_PORT,VALVE_DATA_BIT);
}

void Valve_SetClock(void)
{
    GPIO_PinOutSet(VALVE_CLK_PORT,VALVE_CLK_BIT);
}
void Valve_ClearClock(void)
{
    GPIO_PinOutClear(VALVE_CLK_PORT,VALVE_CLK_BIT);
}

void Valve_ClearLatch(void)
{
    GPIO_PinOutClear(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
}
void Valve_SetLatch(void)
{
    GPIO_PinOutSet(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
}

void Valve_10ms_Int(void)
{
    bValveFlag = true;
    bRollerFlag = true;
    //    bLegKneadFlag = true;
    w_RollerCounter++;
    SholderTime++;
    
    //    if(bLegAirBagOn)
    //    {
    //      if(w_KneadLegCount >= 600)
    //      {
    //        bKneadLegEnable = true;
    //      }
    //      if(w_KneadLegCount < 600)
    //      {
    //        w_KneadLegCount++;  
    //      }
    //    }
    //    else
    //    {
    //      if(w_KneadLegCount < 200)
    //      {
    //        bKneadLegEnable = false;
    //      }
    //      if(w_KneadLegCount > 0) w_KneadLegCount--; 
    //    }  
}
void Valve_1ms_Int(void)
{
    //bValveFlag = true;
}

static unsigned char SPI_FlashWrite(unsigned char data)
{
    VALVE_SPI->TXDATA = data;
    while (!(VALVE_SPI->STATUS & USART_STATUS_TXC));//�ȴ��������
    return (uint8_t)(VALVE_SPI->RXDATA);
}

/*������10msִ��һ�Σ������������У����ݳ��ȹ̶�Ϊ4*/
void Valve_Send_Data(void)
{
    unsigned int i;
    unsigned char ucLength = VALVE_DATA_LENGTH;
    
    if(!bValveFlag) return;//���Ƴ���������һ��
    bValveFlag = false;
    
    for(int i = 0; i < ucLength; i++)
    {
        *(ucSendData + i) = BITS_ValveData[i].nByte;//��Ҫ���͵����ݷ��뵽����������
    }

    for(i = 0;i < ucLength;i++)
    {
        *(ucReceiveData + i) = SPI_FlashWrite(*(ucSendData + i));//�����������е�����ͨ�����Ͷ˷��ͳ�ȥ
    }
    
    for(i = 100;i > 0;i--) __no_operation();//���ͳɹ�������ʱ���ٽ��������������������
    
    GPIO_PinOutSet(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
    
    for( i = 100;i > 0;i--) __no_operation();
    
    GPIO_PinOutClear(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
}
/*************************************************************
����˵�����ȡ������ҿ��ƺ���
����1��Ϊ0ʱ�ر��ȡ��ŵ��������ң�Ϊ1ʱ�ɲ���2����Ҫ��������
����2��������1Ϊ1ʱ��������Ҫ�򿪺͹رյ��ȡ��Ŵ�������
����ֵ����
����˵������
*************************************************************/
void LegFootAirBagAction(bool Enable,unsigned int action)
{    
    if(FlexPower_Get() == FLEX_POWER_ON)//�����ȳ���û��ִ�в��������������ʱ�ر���������
    {
        if(!st_Stretch.active)//���ȳ���û��ִ��
        {
            bFootHeelAirBagValve = VALVE_OFF;
            bRightFootAirBagValve = VALVE_OFF;
            bLeftFootAirBagValve = VALVE_OFF;
            Enable = false; //С����������ڶ���ʱ���㲿���ҹر�
        }
    }
    if(!Enable)
    {
        bFootHeelAirBagValve = VALVE_OFF; //�ź������
        bRightFootAirBagValve = VALVE_OFF;//���Ҳ�����
        bLeftFootAirBagValve = VALVE_OFF; //���������
        bLegLeftAirBagValve = VALVE_OFF;  //��������		        
        bLegRightAirBagValve = VALVE_OFF; //��������	        
        return;
    }
    if(action & LEG_LEFT)
    {
        bLegRightAirBagValve = VALVE_ON ;
    }
    else
    {
        bLegRightAirBagValve = VALVE_OFF ;
    }
    
    if(action & LEG_RIGHT)
    {
        bLegLeftAirBagValve = VALVE_ON ;
    }
    else
    {
        bLegLeftAirBagValve = VALVE_OFF ;
    }
    
    if(action & F_L_SIDE)
    {
        bLeftFootAirBagValve = VALVE_ON ;
    }
    else
    {
        bLeftFootAirBagValve = VALVE_OFF ;
    }
    
    if(action & F_HEEL)
    {
        bFootHeelAirBagValve = VALVE_ON ;
    }
    else
    {
        bFootHeelAirBagValve = VALVE_OFF ;
    }
    
    if(action & F_R_SIDE)
    {
        bRightFootAirBagValve = VALVE_ON ;
    }
    else
    {
        bRightFootAirBagValve = VALVE_OFF ;
    }
}


//void BackWaistAirBagAction(bool Enable,unsigned int action)
//{  
//    if(!Enable)
//    {
//        bBackWaistRightUp	  =  VALVE_OFF ;
//        bBackWaistRightDown   =  VALVE_OFF ;
//        bBackWaistLeftUp      =  VALVE_OFF ;  
//        bBackWaistLeftDown    =  VALVE_OFF ;
//        return;
//    }
//    /*
//    if(action & PE1)
//    {
//        Valve_BodyUpAirPumpACPowerOn();
//    }
//    else
//    {
//        Valve_BodyUpAirPumpACPowerOff();
//    }
//    */
//    if(action & R_U_WAIST)
//    {
//        bBackWaistRightUp = VALVE_ON ;
//    }
//    else
//    {
//        bBackWaistRightUp = VALVE_OFF ;
//    }
//    if(action & R_D_WAIST)
//    {
//        bBackWaistRightDown = VALVE_ON ;
//    }
//    else
//    {
//        bBackWaistRightDown = VALVE_OFF ;
//    }
//    if(action & L_U_WAIST)
//    {
//        bBackWaistLeftUp = VALVE_ON ;
//    }
//    else
//    {
//        bBackWaistLeftUp = VALVE_OFF ;
//    }
//    if(action & L_D_WAIST)
//    {
//        bBackWaistLeftDown = VALVE_ON ;
//    }
//    else
//    {
//        bBackWaistLeftDown = VALVE_OFF ;
//    }
//}
/************************************************************************
����˵�����������ҿ��ƺ���
����1��Ϊ0ʱ�ر��������ң�Ϊ1ʱ�ɲ���2������������״̬
����2��������1Ϊ1ʱ����������������״̬
����ֵ����
����˵������
************************************************************************/
void SeatAirBagAction(bool Enable,unsigned int action)
{
    if(!Enable)
    {
        bLeftThighAirBagValve   =  VALVE_OFF ;
        bRightThighAirBagValve 	=  VALVE_OFF ;
        return;
    }

    if(action & R_THIGH)
    {
        bRightThighAirBagValve = VALVE_ON ;
    }
    else
    {
        bRightThighAirBagValve = VALVE_OFF ;
    }
    
    if(action & L_THIGH)
    {
        bLeftThighAirBagValve = VALVE_ON ;
    }
    else
    {
        bLeftThighAirBagValve = VALVE_OFF ;
    }
}
/**********************************************************************
����˵�����ֱۡ��粿���ҵĿ��ƺ���
����1��Ϊ0ʱ�ر��ֱۺͼ粿�����ң�Ϊ1ʱ�ɲ���2�����Ƽ粿���ֱ����ҵĿ���
����2��������1Ϊ1ʱ�������Ƽ粿���ֱ۵����ҿ���
����ֵ����
����˵�������е���о���е��������λ�ú��ֶ����ڷ���ʱ���粿���Ҳ������
**********************************************************************/
void ArmSholderAirBagAction(bool Enable,unsigned int action)
{    
    if(!Enable)
    {
        bRightArmUpAirBagValve1   =  VALVE_OFF ;
        bRightArmUpAirBagValve2   =  VALVE_OFF ;
        bRightArmUpAirBagValve3   =  VALVE_OFF ;
        bLeftArmUpAirBagValve1    =  VALVE_OFF ;
        bLeftArmUpAirBagValve2    =  VALVE_OFF ;
        bLeftArmUpAirBagValve3    =  VALVE_OFF ;
        bLeftSholderAirBagValve   =  VALVE_OFF ;
        bRightSholderAirBagValve  =  VALVE_OFF ;
        return;
    }
    
    unsigned short nCurWalkMotorLocate = Input_GetWalkMotorPosition();
    /*
    if(action & PE1)
    {
        Valve_BodyUpAirPumpACPowerOn();
    }
    else
    {
        Valve_BodyUpAirPumpACPowerOff();
    }
    */
  
      
    if(action & R_ARM_1)
    {
        bRightArmUpAirBagValve1 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve1 = VALVE_OFF ;
    }
    if(action & R_ARM_2)
    {
        bRightArmUpAirBagValve2 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve2 = VALVE_OFF ;
    }
    if(action & R_ARM_3)
    {
        bRightArmUpAirBagValve3 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve3 = VALVE_OFF ;
    }
    if(action & L_ARM_1)
    {
        bLeftArmUpAirBagValve1 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve1 = VALVE_OFF ;
    }
    if(action & L_ARM_2)
    {
        bLeftArmUpAirBagValve2 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve2 = VALVE_OFF ;
    }
    if(action & L_ARM_3)
    {
        bLeftArmUpAirBagValve3 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve3 = VALVE_OFF ;
    }
  
    if(nCurWalkMotorLocate > 230 && bBackauto)  //��о��������߶Ȳ�������
    {
       bLeftSholderAirBagValve = VALVE_OFF ;
       bRightSholderAirBagValve = VALVE_OFF ;
      
        /*ValveTimeFlag = 1;
        if(ValveTime>=50 && valveflag == 0)
        {
          bLeftSholderAirBagValve = VALVE_ON ;
          bRightSholderAirBagValve = VALVE_ON ;
          valveflag = 1;
        }
      
      
      if( ValveTime>=150 && valveflag == 1)
       
      {
       bLeftSholderAirBagValve = VALVE_OFF ;
        bRightSholderAirBagValve = VALVE_OFF ;
       ValveTime = 0;
       ValveTimeFlag = 0;
       valveflag = 0;
      
      }
      */
     
    }
    else
    {
       if(action & L_SHOLDER)
    {
        bLeftSholderAirBagValve = VALVE_ON ;
    }
    else
    {
        bLeftSholderAirBagValve = VALVE_OFF ;
    }
    if(action & R_SHOLDER)
    {
        bRightSholderAirBagValve = VALVE_ON ;
    }
    else
    {
        bRightSholderAirBagValve = VALVE_OFF ;
    }
    
    }
}

/************************************************************************
����˵�����ֱ����ҿ��ƺ���
����1��Ϊ0ʱ�ر��ֱ��������ң�Ϊ1ʱ���ݲ���2��ֵ�������ֱ����ҵ�ͨ��
����2��������1Ϊ1ʱ����2���������ֱ����ҵĿ���
����ֵ����
����˵������
************************************************************************/
void ArmAirBagAction(bool Enable,unsigned int action)
{    
     if(!Enable)
    {
        bRightArmUpAirBagValve1   =  VALVE_OFF ;
        bRightArmUpAirBagValve2   =  VALVE_OFF ;
        bRightArmUpAirBagValve3   =  VALVE_OFF ;
        bLeftArmUpAirBagValve1    =  VALVE_OFF ;
        bLeftArmUpAirBagValve2    =  VALVE_OFF ;
        bLeftArmUpAirBagValve3    =  VALVE_OFF ;
        return;
    }
    if(action & R_ARM_1)
    {
        bRightArmUpAirBagValve1 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve1 = VALVE_OFF ;
    }
    if(action & R_ARM_2)
    {
        bRightArmUpAirBagValve2 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve2 = VALVE_OFF ;
    }
    if(action & R_ARM_3)
    {
        bRightArmUpAirBagValve3 = VALVE_ON ;
    }
    else
    {
        bRightArmUpAirBagValve3 = VALVE_OFF ;
    }
    if(action & L_ARM_1)
    {
        bLeftArmUpAirBagValve1 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve1 = VALVE_OFF ;
    }
    if(action & L_ARM_2)
    {
        bLeftArmUpAirBagValve2 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve2 = VALVE_OFF ;
    }
    if(action & L_ARM_3)
    {
        bLeftArmUpAirBagValve3 = VALVE_ON ;
    }
    else
    {
        bLeftArmUpAirBagValve3 = VALVE_OFF ;
    }
}

/*******************************************************************
����˵��������һ�����ҳ���ʱ��ĺ�������һ�鶯������һ�鶯���л���ʱ�����
���������Ҷ�����������
����ֵ��ʱ�䵽����1��δ������0
����˵����ͨ���β��еĳ�����ʱ����nAirBagCounter��ʱ����Ʊ���nCurKeepTime1~5
          �����Ƴ���ʱ�䣬���ݲ�ͬ�����ȳ���ʱ�䲻һ��
*******************************************************************/
bool AirBagGetNextStep(st_AirBag* pBag)  //bNextStep�����٣��������Ƿ�ִ����һ����
{
    bool bNextStep = FALSE;
    unsigned char counter = pBag->nAirBagCounter;
    switch(nKeyAirBagStrength)
    {
    case 1:
        if(counter > pBag->nCurKeepTime1)
        {
            bNextStep = TRUE ;
        }
        break ;
    case 2:
        if(counter > pBag->nCurKeepTime2)
        {
            bNextStep = TRUE ;
        }
        break ;
    case 3:
        if(counter > pBag->nCurKeepTime3)
        {
            bNextStep = TRUE ;
        }
        break ;
    case 4:
        if(counter > pBag->nCurKeepTime4)
        {
            bNextStep = TRUE ;
        }
        break ;
    case 5:
        if(counter > pBag->nCurKeepTime5)
        {
            bNextStep = TRUE ;
        }
        break ;
    }
    return (bNextStep);
}

void Valve_CloseAll(void)  
{
    BITS_ValveData[0].nByte = 0;
    BITS_ValveData[1].nByte = 0;
    BITS_ValveData[2].nByte = 0;
    Valve_LegFootAirPumpACPowerOff();
    Valve_BodyUpAirPumpACPowerOff();
}
void Valve_SetStretchUp(void)
{
    static int step = 0;
    Valve_LegFootAirPumpACPowerOn();
    //�ۼ�����
    switch(step)
    {
    case 0: 
        //�㲿����
        bRightFootAirBagValve = VALVE_OFF;
        bLeftFootAirBagValve = VALVE_OFF;
        bFootHeelAirBagValve = VALVE_OFF;
        SholderTime = 0;
        step++;
        break;
    case 1: 
        if(SholderTime > 4000)
            step++;
        break;     
    case 2: 
        //�㲿����
        bRightFootAirBagValve = VALVE_ON;
        bLeftFootAirBagValve = VALVE_ON;
        bFootHeelAirBagValve = VALVE_OFF;
        SholderTime = 0;
        step++;
        break;
    case 3: 
        if(SholderTime > 4000)
            step++;
        break;       
    case 4:
        //�㲿����
        bRightFootAirBagValve = VALVE_OFF;
        bLeftFootAirBagValve = VALVE_OFF;
        bFootHeelAirBagValve = VALVE_OFF;
        step++;
        SholderTime = 0;
        break; 
    case 5: 
        if(SholderTime > 1000)
            step=2;
        break;       
    }  
    //Valve_LegFootAirPumpACPowerOff();
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    //bRightFootAirBagValve = VALVE_OFF;
    // bLeftFootAirBagValve = VALVE_OFF;
    //bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}

/*
void Valve_SetStretchUp(void)
{
  
 static int step = 0;
 Valve_LegFootAirPumpACPowerOn();
    //�ۼ�����
    switch(step)
    {
     case 0: 

      //�㲿����
      bRightFootAirBagValve = VALVE_ON;
      bLeftFootAirBagValve = VALVE_OFF;
      bFootHeelAirBagValve = VALVE_OFF;
      SholderTime = 0;
      step++;
      break;
     case 1: 
      if(SholderTime > 4000)
        step++;
      break;       
     case 2:

      //�㲿����
      bRightFootAirBagValve = VALVE_OFF;
      bLeftFootAirBagValve = VALVE_ON;
      bFootHeelAirBagValve = VALVE_OFF;
      step++;
      SholderTime = 0;
      break; 
     case 3: 
      if(SholderTime > 4000)
        step=0;
      break;       
                 
    }  
  
  
  
    //Valve_LegFootAirPumpACPowerOff();
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    //bRightFootAirBagValve = VALVE_OFF;
   // bLeftFootAirBagValve = VALVE_OFF;
    //bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
    bBackWaistRightUp	  =  VALVE_OFF ;
    bBackWaistRightDown   =  VALVE_OFF ;
    bBackWaistLeftUp      =  VALVE_OFF ;  
    bBackWaistLeftDown    =  VALVE_OFF ;

}
*/
void Valve_SetStretchCharge(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    //    bFootHeelAirBagValve = VALVE_ON;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_ON ;
    bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargedown(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
   // bFootHeelAirBagValve = VALVE_ON;
    //��������
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_ON ;
    bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargepre(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
  //  bFootHeelAirBagValve = VALVE_ON;
    //��������
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //�첲����
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargeATOUT(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       = VALVE_OFF; //VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;// V/ALVE_ON ;  
    //�첲����
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargeATOUT2(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =VALVE_OFF; // VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;/// VALVE_ON ;  
    //�첲����
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargeATOUTFootHeelOFF(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    if(start)
    {
        step =  0; 
        SholderTime = 0;
    }
    //�ۼ�����
    switch(step)
    {
    case 0: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ; 
    SholderTime = 0;
    step++;
    break;
    case 1: if(SholderTime > 500)
        step++;
        break;       
    case 2: bLeftSholderAirBagValve  = VALVE_ON ; 
    bRightSholderAirBagValve  = VALVE_ON ;
    step++;
    SholderTime = 0;
    break;       
    case 3: if(SholderTime > 200)
        step = 0;
        break;               
    }
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       = VALVE_OFF;// VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;// VALVE_ON ;  
    //�첲����
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargeOut(unsigned int start)
{
  Valve_SetStretchCharge(start);
   //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
}

void Valve_SetStretchHold(void)
{
   // static int step = 0;
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
   // bFootHeelAirBagValve = VALVE_ON;
    //��������
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchHoldHeelOFF(void)
{
   // static int step = 0;
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchHoldHeelSCONDOFF(void)
{
   // static int step = 0;
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //�㲿����
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}

unsigned char Valve_Level_Decrease(unsigned char by_Data)
{
    unsigned char retval;
    unsigned int w_Data;
    unsigned int mod;
    if(by_Data <= 5) 
    {
        retval = by_Data;
    }
    else
    {
        w_Data = by_Data;
        w_Data *= 10;
        mod = w_Data % 15;
        w_Data /= 15;
        if(mod > 7) w_Data++;
        by_Data = (unsigned char)w_Data;
        retval = by_Data;
    }
    return retval;
}

unsigned char Valve_Level_Increase(unsigned char by_Data)
{
    unsigned char retval;
    unsigned int w_Data;
    unsigned int mod;
    if(by_Data <= 5) 
    {
        retval = by_Data;
    }
    else
    {
        w_Data = by_Data;
        w_Data *= 15;
        w_Data /= 10;
        mod = w_Data % 10;
        if(mod > 5) w_Data++;
        if(w_Data > 255) w_Data = 255;
        by_Data = (unsigned char)w_Data;
        retval = by_Data;
    }
    return retval;
}

void Valve_SetEnableSholder(unsigned int enable) //������������ģʽΪ�Զ�ģʽʱ��0��������1��ʵ���ϴ˺���δʹ��
{
    bSholderEnable = enable;
}
#define VALVE_CLOSE_ALL_AIRPUMP  0
#define VALVE_OPEN_ALL_AIRPUMP   1
#define VALVE_NORMAL   2

/************************************************************
����˵�������ÿ��ؿ��ƺ���
������    VALVE_CLOSE_ALL_AIRPUMP  �������ö��ر�
          VALVE_OPEN_ALL_AIRPUMP   �������ö���
          ����ֵ                   ���ݲ��������Ҳ�ͬ�򿪶�Ӧ������
����ֵ����
����˵������
************************************************************/
void Valve_Airpump_Ctrl(unsigned int ctrl)
{
    if(ctrl == VALVE_CLOSE_ALL_AIRPUMP)
    {
        Valve_BodyUpAirPumpACPowerOff();
        Valve_LegFootAirPumpACPowerOff();
        return;
    }
    if(ctrl == VALVE_OPEN_ALL_AIRPUMP)
    {
        Valve_BodyUpAirPumpACPowerOn();
        Valve_LegFootAirPumpACPowerOn();
        return;
    }
    
if(bBackWaistRightUp ||
     bBackWaistRightDown ||
       bBackWaistLeftUp ||
         bBackWaistLeftDown ||
           bRightSholderAirBagValve ||
             bRightArmUpAirBagValve1 ||
               bRightArmUpAirBagValve2 ||
                 bRightArmUpAirBagValve3 ||
                   bLeftArmUpAirBagValve1 ||
                     bLeftArmUpAirBagValve2 ||
                       bLeftArmUpAirBagValve3 ||
                         bLeftSholderAirBagValve)
    {
        Valve_LegFootAirPumpACPowerOn();
    }
    else
    {
        //Valve_LegFootAirPumpACPowerOff();
    }       
}

/***********************************************************************
����˵�������ҿ��ƺ���������������ƣ�
����1��Ϊ0ʱ���ݲ���2��Ҫ�������Ҳ�λ����Ӧ��λ�����ҹرգ�Ϊ1ʱ��������2
       �е����ݶ����ҽ��п���
����2�����ҿ������飬��Ҫ������init ���ڵ�һ��������������ʱ��ʼ���������������͡�������ʱ����������
                               nCurAirBagStep ��������Ķ����������������Ϊ���������Ԫ�ظ���
                               nTotalSteps    ���������Ԫ�ظ��������������ֵ
                               nAirBagCounter ���ҳ���ʱ�䣬ÿ100ms��һ��
                               nCurKeepTime1; ���ݳ����������������ҵĳ���ʱ��
                               nCurKeepTime2; 
                               nCurKeepTime3; 
                               nCurKeepTime4;
                               nCurKeepTime5; 
                               locate         ���Ƶ����Ҳ�λ�� �Ƚ�
                                                               ����
                                                               ����
                                                               �ۼ�
                                                               �ֱ�
                                                               ȫ��
                                                               �ۼ���
                                                               �Ƚ�����
                               
                               nCurPumpValveState ���ҵĿ�������һ��������Ԫ��pAirBagArray�е�nPumpValveState����
                               pAirBagArray       �������ݺͳ���ʱ��洢�ڴ�������
                               
����3����user_data�ж�ȡ��������������
����ֵ����
����˵������
***********************************************************************/
void Valve_Control(unsigned char nAirBagSwitch,st_AirBag* pBag,unsigned char level)
{
    bool bNextStep = FALSE;
    if(nAirBagSwitch == VALVE_DISABLE)
    {
        switch(pBag->locate)
        {
        case AIRBAG_LOCATE_LEG_FOOT:        LegFootAirBagAction(FALSE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_SEAT:            SeatAirBagAction(FALSE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_BACK_WAIST:      break;
        case AIRBAG_LOCATE_ARM_SHOLDER:     ArmSholderAirBagAction(FALSE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_ARM:             ArmAirBagAction(FALSE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_AUTO:
            LegFootAirBagAction(FALSE,pBag->nCurPumpValveState);   //�Ƚ����� 5
            SeatAirBagAction(FALSE,pBag->nCurPumpValveState);      //�������� 2
            ArmSholderAirBagAction(FALSE,pBag->nCurPumpValveState);//�ۼ����� 6
            break;
        case AIRBAG_LOCATE_ARM_SHOLDER_WAIST:  
            ArmSholderAirBagAction(FALSE,pBag->nCurPumpValveState);
            break;
        case AIRBAG_LOCATE_LEG_FOOT_SEAT: 
            LegFootAirBagAction(FALSE,pBag->nCurPumpValveState); 
            SeatAirBagAction(FALSE,pBag->nCurPumpValveState);   
            break; 
        }
        return; 
    }
    if(pBag->init == TRUE)
    {
        bNextStep = TRUE;
    }
    else
    {
        bNextStep = AirBagGetNextStep(pBag);   
    }
    if(bNextStep == TRUE)
    {
        if(pBag->locate == AIRBAG_LOCATE_LEG_FOOT)
        {
            w_RollerCounter = 0;
        }
        if(pBag->init == TRUE)
        {
            pBag->init = FALSE;
            pBag->nCurAirBagStep = 0;
            pBag->nAirBagCounter = 0;
        }
        else
        {
            pBag->nCurAirBagStep++;
            if(pBag->nCurAirBagStep >= pBag->nTotalSteps)
            {
                pBag->nCurAirBagStep = 0;
            }
        }
        pBag->nCurPumpValveState = pBag->pAirBagArray[pBag->nCurAirBagStep].nPumpValveState ;
        pBag->nCurKeepTime1 = pBag->pAirBagArray[pBag->nCurAirBagStep].nKeepTime1 ;
        pBag->nCurKeepTime3 = pBag->pAirBagArray[pBag->nCurAirBagStep].nKeepTime2 ;
        pBag->nCurKeepTime5 = pBag->pAirBagArray[pBag->nCurAirBagStep].nKeepTime3 ;
        
        if(pBag->nCurPumpValveState != ALL_DIS)
        {
            if(level  == 0)
            {
                pBag->nCurKeepTime1 = Valve_Level_Decrease(pBag->nCurKeepTime1);
                pBag->nCurKeepTime3 = Valve_Level_Decrease(pBag->nCurKeepTime3);
                pBag->nCurKeepTime5 = Valve_Level_Decrease(pBag->nCurKeepTime5);
            }
            if(level  == 2)
            {
                pBag->nCurKeepTime1 = Valve_Level_Increase(pBag->nCurKeepTime1);
                pBag->nCurKeepTime3 = Valve_Level_Increase(pBag->nCurKeepTime3);
                pBag->nCurKeepTime5 = Valve_Level_Increase(pBag->nCurKeepTime5);
            }
        }
        pBag->nCurKeepTime2 = Middle(pBag->nCurKeepTime1,pBag->nCurKeepTime3);
        pBag->nCurKeepTime4 = Middle(pBag->nCurKeepTime3,pBag->nCurKeepTime5);
        pBag->nAirBagCounter = 0;
        switch(pBag->locate)
        {
        case AIRBAG_LOCATE_LEG_FOOT:        LegFootAirBagAction(TRUE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_SEAT:            SeatAirBagAction(TRUE,pBag->nCurPumpValveState); break;
        //case AIRBAG_LOCATE_BACK_WAIST:      BackWaistAirBagAction(TRUE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_ARM_SHOLDER:     ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_ARM:             ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState); break;
        case AIRBAG_LOCATE_AUTO:
            LegFootAirBagAction(TRUE,pBag->nCurPumpValveState); 
            SeatAirBagAction(TRUE,pBag->nCurPumpValveState); 
            //BackWaistAirBagAction(TRUE,pBag->nCurPumpValveState); 
            ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState); 
            break;
        case AIRBAG_LOCATE_ARM_SHOLDER_WAIST: 
            //BackWaistAirBagAction(TRUE,pBag->nCurPumpValveState); 
            ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState);
            break;
        case AIRBAG_LOCATE_LEG_FOOT_SEAT: 
            LegFootAirBagAction(TRUE,pBag->nCurPumpValveState); 
            SeatAirBagAction(TRUE,pBag->nCurPumpValveState); 
            break;   
            
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_ARM_SHOLDER):
            LegFootAirBagAction(TRUE,pBag->nCurPumpValveState);
            ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState);
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_SEAT):
            LegFootAirBagAction(TRUE,pBag->nCurPumpValveState);
            SeatAirBagAction(TRUE,pBag->nCurPumpValveState); 
        case (AIRBAG_LOCATE_ARM_SHOLDER| AIRBAG_LOCATE_SEAT):
            ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState);
            SeatAirBagAction(TRUE,pBag->nCurPumpValveState);
        case (AIRBAG_LOCATE_LEG_FOOT | AIRBAG_LOCATE_ARM_SHOLDER | AIRBAG_LOCATE_SEAT):
            LegFootAirBagAction(TRUE,pBag->nCurPumpValveState);
            ArmSholderAirBagAction(TRUE,pBag->nCurPumpValveState);
            SeatAirBagAction(TRUE,pBag->nCurPumpValveState);
        }
    }
    Valve_Airpump_Ctrl(VALVE_OPEN_ALL_AIRPUMP);
}


extern bool bRoll_InStretch;
void Valve_FootRollerProce(unsigned char   bRollerEnable,unsigned char Valve_Enable,st_AirBag* pBag)
{ 
    unsigned int RollerSpeed,RollerPWM,RollerPhaseMode;
    unsigned int RollerCounter =w_RollerCounter;
    if(bRollerFlag == 0) return;  //���ƺ���10msִ��һ��
    bRollerFlag = 0;   
    if(!bRollerEnable) //����1Ϊ0ʱֹͣ����
    {
        RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
        return;
    }
    if(FlexPower_Get() == FLEX_POWER_ON)  //�����������ʱ�رչ���
    {
        RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
        return;
    }
    if(Valve_Enable)  //�Զ�����ģʽ
    {
        bAutoRoller =true;
        //if(bRoll_InStretch ==  TRUE) return;
        // RollerSpeed =((pBag->nCurPumpValveState & 0x03000000) >> 24);
        RollerSpeed = ((pBag->nCurPumpValveState >> 25) & 0x03);
        // if(bRoll_InStretch ==  TRUE) RollerSpeed =1;
        RollerPhaseMode = ((pBag->nCurPumpValveState >> 27) & 0x07);
        //IR001 ����1������Ӵ���
//        if( (bGetAuto2RollerEnable() ==TRUE)&&(RollerSpeed >= 2))//�Զ�2ģʽִ��
//        {
//            RollerSpeed = 1; 
//        }     
        switch(RollerSpeed)
        { 
        default:  
        case 0:
            RollerPWM = ROLLER_SPEED_STOP;  
            break ;  
        case 1:
            RollerPWM = ROLLER_SPEED_SLOW;  
            break ;
        case 2:
            RollerPWM = ROLLER_SPEED_MID; 
            break ;
        case 3:
            RollerPWM = ROLLER_SPEED_FAST; 
            break ;
        }
        //RollerMotor_Control(RollerPWM,pBag->nCurPumpValveState&ROLLER_PHASE);  //�������ƹ���
        RollerMotor_Control(RollerPWM,RollerPhaseMode);
        w_RollerCounter = RollerCounter;
        return; 
    }
    bManRollerZero = FALSE;
    bAutoRoller = false;  //�ֶ�����ģʽ
    //RollerMotor_Control(w_RollerPWM,1);
    nRoller3sCnt++;
    if( nRoller3sCnt <= 1800)//��ת18s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else if(   ( nRoller3sCnt > 1800)&&(nRoller3sCnt < 3600)  )//��ת18~36s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 3600)&&(nRoller3sCnt < 7200)  )//��ת36~72s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else if(   ( nRoller3sCnt > 7200)&&(nRoller3sCnt < 9000)  )//��ת72~90s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }   
    else if(   ( nRoller3sCnt > 9000)&&(nRoller3sCnt < 9500)  )//��ת90~95s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 9500)&&(nRoller3sCnt < 10000)  )//��ת95~100s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt >10000)&&(nRoller3sCnt < 10500)  )//��ת100~105s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 10500)&&(nRoller3sCnt < 11000)  )//��ת105~110s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 11000)&&(nRoller3sCnt < 11500)  )//��ת110~115s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 11500)&&(nRoller3sCnt < 12000)  )//��ת115~120s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 12000)&&(nRoller3sCnt < 12100)  )//��ת120~121s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12100)&&(nRoller3sCnt < 12200)  )//121~122s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12200)&&(nRoller3sCnt < 12300)  )//122~123s����ת
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12300)&&(nRoller3sCnt < 12400)  )//123~124sֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12400)&&(nRoller3sCnt < 12500)  )//124~125s����ת
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 125000)&&(nRoller3sCnt < 12600)  )//125~126s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    } 
    else if(   ( nRoller3sCnt > 12600)&&(nRoller3sCnt < 12700)  )//126~127s����ת
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12700)&&(nRoller3sCnt < 12900)  )//127~129s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12900)&&(nRoller3sCnt < 13100)  )//129~131s����ת
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 13100)&&(nRoller3sCnt < 13300)  )//131~133s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 13300)&&(nRoller3sCnt < 13500)  )//133~135s����ת
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 13500)&&(nRoller3sCnt < 13700)  )//135~137s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    } 
    else if(   ( nRoller3sCnt > 13700)&&(nRoller3sCnt < 13900)  )//137~139s����ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 13900)&&(nRoller3sCnt < 14100)  )//139~141s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14100)&&(nRoller3sCnt < 14300)  )//141~143s����ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 14300)&&(nRoller3sCnt < 14500)  )//143~145s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14500)&&(nRoller3sCnt < 14700)  )//145~147s����ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 14700)&&(nRoller3sCnt < 14900)  )//147~149s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14900)&&(nRoller3sCnt < 15100)  )//149~151s����ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 15100)&&(nRoller3sCnt < 15500)  )//151~155s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 15500)&&(nRoller3sCnt < 15700)  )//155~157s����ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 15700)&&(nRoller3sCnt < 15900)  )//157~159s,ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 15900)&&(nRoller3sCnt < 16100)  )//159~161s,��ת
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 16100)&&(nRoller3sCnt < 16300)  )//161~163s��ֹͣ
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt >= 16300) )
    {
        nRoller3sCnt = 0;
    }
}


void Valve_SetRollerPWM(unsigned char level)
{
    switch(level)
    {
    case 0:  w_RollerPWM = ROLLER_SPEED_STOP; break;
    case 1:  w_RollerPWM = ROLLER_SPEED_SLOW; break;
    case 2:  w_RollerPWM = ROLLER_SPEED_MID;  break;
    case 3:  w_RollerPWM = ROLLER_SPEED_FAST; break;
    }
}

unsigned char Valve_GetRollerLevel(void)
{
    if(bManRollerZero == TRUE)return 0;//����ֶ�ʱ�ٶ�Ϊ0�����ϴ��ֿ�������Ͳ�ٶ�Ϊ0��
    unsigned char level = 0;
    if(w_RollerPWM == ROLLER_SPEED_SLOW) level = 1;
    if(w_RollerPWM == ROLLER_SPEED_MID) level = 2;
    if(w_RollerPWM == ROLLER_SPEED_FAST) level = 3;
    return level;
}

//void Valve_SetLegKneadSpeed(unsigned char speed)
//{
//  if(speed > LEG_KNEAD_SPEED_FAST) return;
//  LegKneadSpeed = speed;
//}
//unsigned char Valve_GetLegKneadSpeed(void)
//{
//    return(LegKneadSpeed);
//}

unsigned char Valve_GetAirBagStrength(void)
{
    return(nKeyAirBagStrength);
}

void Valve_SetAirBagStrength(unsigned char strength)
{
    nKeyAirBagStrength = strength;
}

void Valve_AddAirBagStrength(void)
{
    nKeyAirBagStrength++;
    if(nKeyAirBagStrength > 5) nKeyAirBagStrength =1;
}
//С�Ⱥ��β�
void Valve_LegFootAirPumpACPowerOn(void)
{
    GPIO_PinOutSet(VALVE_AIRPUMP2_PORT,VALVE_AIRPUMP2_BIT);
}
void Valve_LegFootAirPumpACPowerOff(void)
{
    GPIO_PinOutClear(VALVE_AIRPUMP2_PORT,VALVE_AIRPUMP2_BIT);
}
//�ۼ磬������
void Valve_BodyUpAirPumpACPowerOn(void)
{
    GPIO_PinOutSet(VALVE_AIRPUMP1_PORT,VALVE_AIRPUMP1_BIT);
}
void Valve_BodyUpAirPumpACPowerOff(void)
{
    GPIO_PinOutClear(VALVE_AIRPUMP1_PORT,VALVE_AIRPUMP1_BIT);
}

void Valve_Test_Set_Data(unsigned int ValveTestData)
{
    BITS_ValveData[0].nByte = (unsigned char)ValveTestData;
    BITS_ValveData[1].nByte = (unsigned char)(ValveTestData >> 8);
    BITS_ValveData[2].nByte = (unsigned char)(ValveTestData >> 16);
}

void Valve_SetBackMode(int backauto) //�����Զ�ģʽʱ��1��������0
{
    bBackauto = (bool)backauto;
}

void  Valve_OzonOn(void)
{
     // GPIO_PinOutSet(VALVE_OZON_PORT,VALVE_OZON_BIT);
}
void  Valve_OzonOff(void)
{
   //  GPIO_PinOutClear(VALVE_OZON_PORT,VALVE_OZON_BIT);
}

int Valve_RollerIsAuto(void)
{
    return (bAutoRoller) ;
}


/******************************************************************************/
uint8_t nValveAlone=0;
uint16_t nValveAloneTime;
void Valve_Alone()
{
    if(nValveAlone!=1) 
    {
        nValveAloneTime = 0;
        return;
    }
    
    ArmSholderAirBagAction(true,L_SHOLDER|R_SHOLDER);
    SeatAirBagAction(true,L_THIGH|R_THIGH);
    
    // BackWaistAirBagAction(true,0);
    //LegFootAirBagAction(true,0);
    if(nValveAloneTime>300)//8S
    {
        nValveAlone = 0; //�˳����������������
    }
}
/******************************************************************************/


//�򿪽Ų�����
void Valve_SetStretchCharge_FOOT(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
     bLeftArmUpAirBagValve1    =  VALVE_OFF ; //������������
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ; //������������ 	  
     bRightArmUpAirBagValve1   =  VALVE_OFF ; 
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ;
    //�粿����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������
    //    bBackWaistRightUp	  =  VALVE_OFF ;
    //    bBackWaistRightDown   =  VALVE_OFF ;
    //    bBackWaistLeftUp      =  VALVE_OFF ;  
    //    bBackWaistLeftDown    =  VALVE_OFF ;
}


void Valve_SetStretchCharge_ARM(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    static int step = 0;
    switch(step)
    {
    case 0: 
        bLeftArmUpAirBagValve1    =  VALVE_OFF ; //������������
        bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
        bLeftArmUpAirBagValve3    =  VALVE_OFF ; //������������ 	  
        bRightArmUpAirBagValve1   =  VALVE_OFF ; 
        bRightArmUpAirBagValve2   =  VALVE_OFF ;
        bRightArmUpAirBagValve3   =  VALVE_OFF ;
        if(SholderTime > 200)
        {
            step++;
            SholderTime = 0;
        }
        break;
    case 1: 
        bLeftArmUpAirBagValve1    =  VALVE_OFF ; 	 
        bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
        bLeftArmUpAirBagValve3    =  VALVE_OFF ;
        bRightArmUpAirBagValve1   =  VALVE_ON ; //�ұ��������ҿ�       
        bRightArmUpAirBagValve2   =  VALVE_ON ;
        bRightArmUpAirBagValve3   =  VALVE_ON ;
        //SholderTime = 0;
        //step++;
        if(SholderTime > 300)
        {
            step++;
            SholderTime = 0;
        }
        break;
    case 2: 
        bLeftArmUpAirBagValve1    =  VALVE_ON ; 	 
        bLeftArmUpAirBagValve2    =  VALVE_ON ; 
        bLeftArmUpAirBagValve3    =  VALVE_ON ;
        bRightArmUpAirBagValve1   =  VALVE_OFF ;        
        bRightArmUpAirBagValve2   =  VALVE_OFF ;
        bRightArmUpAirBagValve3   =  VALVE_OFF ;
        //SholderTime = 0;
        //step++;
        if(SholderTime > 300)
        {
            step = 1;
            SholderTime = 0;
        }
        break;   
    default:
        step =0;
        SholderTime =0;
        bLeftThighAirBagValve   =  VALVE_OFF ;
        bRightThighAirBagValve 	=  VALVE_OFF ; 
        break;  
    }
    //С������
    bLegLeftAirBagValve  = VALVE_OFF;		
    bLegRightAirBagValve = VALVE_OFF;   
    //�㲿����
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //�������� 
    //bhand_elbow_lAirBagValve   =  VALVE_OFF ; 	 
    //bhand_palm_lAirBagValve    =  VALVE_OFF ;  	  
    //bhand_palm_rAirBagValve    =  VALVE_OFF ;        
    //bhand_elbow_rAirBagValve   =  VALVE_OFF ;  
}
//�Ų����Ȳ����Ҷ�����
void Valve_SetStretchCharge_FOOT_THIGH(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //�ۼ�����
    //С������
    bLegLeftAirBagValve  = VALVE_ON;//VALVE_OFF;		
    bLegRightAirBagValve = VALVE_ON;//VALVE_OFF;              
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������    
    bLeftThighAirBagValve       =  VALVE_OFF;//N ;//US003
    bRightThighAirBagValve 	=  VALVE_OFF;//N ; //us003     
    //�첲����
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //��������   
    bLeftArmUpAirBagValve1    =  VALVE_OFF ; 	 
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ;
     bRightArmUpAirBagValve1   =  VALVE_OFF ;        
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ; 
}


void Valve_SetStretchCharge_FOOT_LEG_SHOULD(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve  = VALVE_ON;//VALVE_OFF;		
    bLegRightAirBagValve = VALVE_ON;//VALVE_OFF;              
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //�첲����
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    if((bKeyArmPadOut == TRUE)||(bKeyArmPadIn == TRUE))
    {
        bLeftSholderAirBagValve   =  VALVE_OFF ;
        bRightSholderAirBagValve  =  VALVE_OFF ; 
    }
    else
    {
        bLeftSholderAirBagValve   =  VALVE_ON ;
        bRightSholderAirBagValve  =  VALVE_ON ;      
    } 
    //��������  
    bLeftArmUpAirBagValve1    =  VALVE_OFF ; 	 
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ;
     bRightArmUpAirBagValve1   =  VALVE_OFF ;        
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ;  
}

void Valve_SetStretchChargeSTEEL(unsigned int start)
{
    static int step = 0;
    switch(step)
    {
    case 0:   	  
        bFootHeelAirBagValve    =  VALVE_OFF ;        
        if(SholderTime > 100)
        {
            step++;
            SholderTime = 0;
        }
        break;
    case 1:   	  
        bFootHeelAirBagValve    =  VALVE_ON ;     
        if(SholderTime > 300)
        {step++;SholderTime = 0;}
        break;   
    default:
        step =0;
        SholderTime =0;  	  
        bFootHeelAirBagValve    =  VALVE_OFF ;   
        break;   
    }
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //С������
    bLegLeftAirBagValve  = VALVE_ON;		
    bLegRightAirBagValve = VALVE_ON;              
    //�㲿����
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    //��������
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;   
    if((bKeyArmPadOut == TRUE)||(bKeyArmPadIn == TRUE))
    {
        bLeftSholderAirBagValve   =  VALVE_OFF ;
        bRightSholderAirBagValve  =  VALVE_OFF ; 
    }
    else
    {
        bLeftSholderAirBagValve   =  VALVE_ON ;
        bRightSholderAirBagValve  =  VALVE_ON ;      
    }   
    //�ֱ�����  
   bLeftArmUpAirBagValve1    =  VALVE_OFF ; 	 
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ;
     bRightArmUpAirBagValve1   =  VALVE_OFF ;        
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ; 
}


