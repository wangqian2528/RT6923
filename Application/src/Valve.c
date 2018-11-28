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

static bool bAutoRoller,bManRollerZero;//新增
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
//手动模式PWM设置
__no_init unsigned int w_RollerPWM;
//手动模式 速度和方式
unsigned char LegKneadSpeed;
unsigned char LegKneadMode;
static bool bValveFlag,bRollerFlag;
extern StretchStruct st_Stretch;

extern  StretchStruct st_GrowthStretch;

extern unsigned int  GrowthStepMaxA;//  
extern unsigned int  GrowthStepMaxB;//
extern __no_init unsigned char nBackMainRunMode,nBackSubRunMode ;


__no_init static unsigned char nKeyAirBagStrength;
//74595串并转换(4片74595)
BITS BITS_ValveData[3];//共3个元素，每个元素的每一位控制一个气阀，共可控制24个气阀
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
    while (!(VALVE_SPI->STATUS & USART_STATUS_TXC));//等待发送完成
    return (uint8_t)(VALVE_SPI->RXDATA);
}

/*本程序10ms执行一次，放在主程序中，数据长度固定为4*/
void Valve_Send_Data(void)
{
    unsigned int i;
    unsigned char ucLength = VALVE_DATA_LENGTH;
    
    if(!bValveFlag) return;//控制程序多久运行一次
    bValveFlag = false;
    
    for(int i = 0; i < ucLength; i++)
    {
        *(ucSendData + i) = BITS_ValveData[i].nByte;//将要发送的数据放入到发送数组中
    }

    for(i = 0;i < ucLength;i++)
    {
        *(ucReceiveData + i) = SPI_FlashWrite(*(ucSendData + i));//将发送数组中的数据通过发送端发送出去
    }
    
    for(i = 100;i > 0;i--) __no_operation();//发送成功进行延时后再将数据锁存至并行输出端
    
    GPIO_PinOutSet(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
    
    for( i = 100;i > 0;i--) __no_operation();
    
    GPIO_PinOutClear(VALVE_LATCH_PORT,VALVE_LATCH_BIT);
}
/*************************************************************
功能说明：腿、脚气囊控制函数
参数1：为0时关闭腿、脚的所有气囊，为1时由参数2控制要开的气囊
参数2：当参数1为1时，来控制要打开和关闭的腿、脚处的气囊
返回值：无
其他说明：无
*************************************************************/
void LegFootAirBagAction(bool Enable,unsigned int action)
{    
    if(FlexPower_Get() == FLEX_POWER_ON)//在拉腿程序还没有执行并且伸缩电机运行时关闭所有气囊
    {
        if(!st_Stretch.active)//拉腿程序还没有执行
        {
            bFootHeelAirBagValve = VALVE_OFF;
            bRightFootAirBagValve = VALVE_OFF;
            bLeftFootAirBagValve = VALVE_OFF;
            Enable = false; //小腿伸缩电机在动的时候足部气囊关闭
        }
    }
    if(!Enable)
    {
        bFootHeelAirBagValve = VALVE_OFF; //脚后跟气囊
        bRightFootAirBagValve = VALVE_OFF;//脚右侧气囊
        bLeftFootAirBagValve = VALVE_OFF; //脚左侧气囊
        bLegLeftAirBagValve = VALVE_OFF;  //左腿气囊		        
        bLegRightAirBagValve = VALVE_OFF; //右腿气囊	        
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
功能说明：坐垫气囊控制函数
参数1：为0时关闭坐垫气囊，为1时由参数2控制坐垫气囊状态
参数2：当参数1为1时用来控制坐垫气囊状态
返回值：无
其他说明：无
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
功能说明：手臂、肩部气囊的控制函数
参数1：为0时关闭手臂和肩部的气囊，为1时由参数2来控制肩部、手臂气囊的开关
参数2：当参数1为1时用来控制肩部和手臂的气囊开关
返回值：无
其他说明：其中当机芯运行到肩膀以上位置和手动调节扶手时，肩部气囊不会充气
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
  
    if(nCurWalkMotorLocate > 230 && bBackauto)  //机芯超过这个高度不允许动作
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
功能说明：手臂气囊控制函数
参数1：为0时关闭手臂所有气囊，为1时根据参数2的值来控制手臂气囊的通断
参数2：当参数1为1时参数2用来控制手臂气囊的开关
返回值：无
其他说明：无
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
功能说明：控制一组气囊充气时间的函数，即一组动作向下一组动作切换的时间控制
参数：气囊动作控制数组
返回值：时间到返回1，未到返回0
其他说明：通过形参中的充气计时变量nAirBagCounter和时间控制变量nCurKeepTime1~5
          来控制充气时间，根据不同的力度充气时间不一样
*******************************************************************/
bool AirBagGetNextStep(st_AirBag* pBag)  //bNextStep是真或假，即返回是否执行下一步骤
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
    //臂肩气囊
    switch(step)
    {
    case 0: 
        //足部气囊
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
        //足部气囊
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
        //足部气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    //bRightFootAirBagValve = VALVE_OFF;
    // bLeftFootAirBagValve = VALVE_OFF;
    //bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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
    //臂肩气囊
    switch(step)
    {
     case 0: 

      //足部气囊
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

      //足部气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    //bRightFootAirBagValve = VALVE_OFF;
   // bLeftFootAirBagValve = VALVE_OFF;
    //bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    //    bFootHeelAirBagValve = VALVE_ON;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_ON ;
    bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
   // bFootHeelAirBagValve = VALVE_ON;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_ON ;
    bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
  //  bFootHeelAirBagValve = VALVE_ON;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //胳膊气囊
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       = VALVE_OFF; //VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;// V/ALVE_ON ;  
    //胳膊气囊
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =VALVE_OFF; // VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;/// VALVE_ON ;  
    //胳膊气囊
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
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
    //臂肩气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       = VALVE_OFF;// VALVE_ON ;
    bRightThighAirBagValve 	= VALVE_OFF;// VALVE_ON ;  
    //胳膊气囊
    //bLeftSholderAirBagValve   =  VALVE_ON ;
    //bRightSholderAirBagValve  =  VALVE_ON ;
    //背腰气囊
//    bBackWaistRightUp	  =  VALVE_OFF ;
//    bBackWaistRightDown   =  VALVE_OFF ;
//    bBackWaistLeftUp      =  VALVE_OFF ;  
//    bBackWaistLeftDown    =  VALVE_OFF ;
}
void Valve_SetStretchChargeOut(unsigned int start)
{
  Valve_SetStretchCharge(start);
   //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
}

void Valve_SetStretchHold(void)
{
   // static int step = 0;
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //小腿气囊
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
   // bFootHeelAirBagValve = VALVE_ON;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_ON ;
    bRightThighAirBagValve 	=  VALVE_ON ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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
    //小腿气囊
    bLegLeftAirBagValve = VALVE_ON;
    bLegRightAirBagValve = VALVE_ON;
    //足部气囊
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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

void Valve_SetEnableSholder(unsigned int enable) //当背部主运行模式为自动模式时置0，否则置1，实际上此函数未使用
{
    bSholderEnable = enable;
}
#define VALVE_CLOSE_ALL_AIRPUMP  0
#define VALVE_OPEN_ALL_AIRPUMP   1
#define VALVE_NORMAL   2

/************************************************************
功能说明：气泵开关控制函数
参数：    VALVE_CLOSE_ALL_AIRPUMP  两个气泵都关闭
          VALVE_OPEN_ALL_AIRPUMP   两个气泵都打开
          其他值                   根据操作的气囊不同打开对应的气泵
返回值：无
其他说明：无
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
功能说明：气囊控制函数（根据数组控制）
参数1：为0时根据参数2中要控制气囊部位将对应部位的气囊关闭，为1时根据数组2
       中的数据对气囊进行控制
参数2：气囊控制数组，主要包括：init 用于第一次运行气囊数组时初始化“动作索引”和“充气计时”两个变量
                               nCurAirBagStep 气囊数组的动作索引变量，最大为气囊数组的元素个数
                               nTotalSteps    动作数组的元素个数，即索引最大值
                               nAirBagCounter 气囊充气时间，每100ms加一次
                               nCurKeepTime1; 根据充气力度来控制气囊的充气时间
                               nCurKeepTime2; 
                               nCurKeepTime3; 
                               nCurKeepTime4;
                               nCurKeepTime5; 
                               locate         控制的气囊部位： 腿脚
                                                               坐垫
                                                               背腰
                                                               臂肩
                                                               手臂
                                                               全身
                                                               臂肩腰
                                                               腿脚坐垫
                               
                               nCurPumpValveState 气囊的控制数，一般由数组元素pAirBagArray中的nPumpValveState赋予
                               pAirBagArray       控制数据和充气时间存储在此数组中
                               
参数3：从user_data中读取的气囊力度数据
返回值：无
其他说明：无
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
            LegFootAirBagAction(FALSE,pBag->nCurPumpValveState);   //腿脚气囊 5
            SeatAirBagAction(FALSE,pBag->nCurPumpValveState);      //坐垫气囊 2
            ArmSholderAirBagAction(FALSE,pBag->nCurPumpValveState);//臂肩气囊 6
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
    if(bRollerFlag == 0) return;  //控制函数10ms执行一次
    bRollerFlag = 0;   
    if(!bRollerEnable) //参数1为0时停止滚轮
    {
        RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
        return;
    }
    if(FlexPower_Get() == FLEX_POWER_ON)  //伸缩电机运行时关闭滚轮
    {
        RollerMotor_Break();//Roller_SetSpeed(ROLLER_SPEED_STOP);
        return;
    }
    if(Valve_Enable)  //自动滚轮模式
    {
        bAutoRoller =true;
        //if(bRoll_InStretch ==  TRUE) return;
        // RollerSpeed =((pBag->nCurPumpValveState & 0x03000000) >> 24);
        RollerSpeed = ((pBag->nCurPumpValveState >> 25) & 0x03);
        // if(bRoll_InStretch ==  TRUE) RollerSpeed =1;
        RollerPhaseMode = ((pBag->nCurPumpValveState >> 27) & 0x07);
        //IR001 定制1档，添加处理
//        if( (bGetAuto2RollerEnable() ==TRUE)&&(RollerSpeed >= 2))//自动2模式执行
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
        //RollerMotor_Control(RollerPWM,pBag->nCurPumpValveState&ROLLER_PHASE);  //气阀控制滚轮
        RollerMotor_Control(RollerPWM,RollerPhaseMode);
        w_RollerCounter = RollerCounter;
        return; 
    }
    bManRollerZero = FALSE;
    bAutoRoller = false;  //手动滚轮模式
    //RollerMotor_Control(w_RollerPWM,1);
    nRoller3sCnt++;
    if( nRoller3sCnt <= 1800)//正转18s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else if(   ( nRoller3sCnt > 1800)&&(nRoller3sCnt < 3600)  )//反转18~36s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 3600)&&(nRoller3sCnt < 7200)  )//正转36~72s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else if(   ( nRoller3sCnt > 7200)&&(nRoller3sCnt < 9000)  )//反转72~90s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }   
    else if(   ( nRoller3sCnt > 9000)&&(nRoller3sCnt < 9500)  )//正转90~95s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 9500)&&(nRoller3sCnt < 10000)  )//反转95~100s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt >10000)&&(nRoller3sCnt < 10500)  )//正转100~105s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 10500)&&(nRoller3sCnt < 11000)  )//反转105~110s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 11000)&&(nRoller3sCnt < 11500)  )//正转110~115s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 11500)&&(nRoller3sCnt < 12000)  )//反转115~120s
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else if(   ( nRoller3sCnt > 12000)&&(nRoller3sCnt < 12100)  )//正转120~121s
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12100)&&(nRoller3sCnt < 12200)  )//121~122s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12200)&&(nRoller3sCnt < 12300)  )//122~123s，正转
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12300)&&(nRoller3sCnt < 12400)  )//123~124s停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12400)&&(nRoller3sCnt < 12500)  )//124~125s，正转
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 125000)&&(nRoller3sCnt < 12600)  )//125~126s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    } 
    else if(   ( nRoller3sCnt > 12600)&&(nRoller3sCnt < 12700)  )//126~127s，正转
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 12700)&&(nRoller3sCnt < 12900)  )//127~129s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 12900)&&(nRoller3sCnt < 13100)  )//129~131s，正转
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 13100)&&(nRoller3sCnt < 13300)  )//131~133s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 13300)&&(nRoller3sCnt < 13500)  )//133~135s，正转
    {
        RollerMotor_Control(w_RollerPWM,0);
    }
    else  if(   ( nRoller3sCnt > 13500)&&(nRoller3sCnt < 13700)  )//135~137s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    } 
    else if(   ( nRoller3sCnt > 13700)&&(nRoller3sCnt < 13900)  )//137~139s，反转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 13900)&&(nRoller3sCnt < 14100)  )//139~141s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14100)&&(nRoller3sCnt < 14300)  )//141~143s，反转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 14300)&&(nRoller3sCnt < 14500)  )//143~145s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14500)&&(nRoller3sCnt < 14700)  )//145~147s，反转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 14700)&&(nRoller3sCnt < 14900)  )//147~149s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 14900)&&(nRoller3sCnt < 15100)  )//149~151s，反转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 15100)&&(nRoller3sCnt < 15500)  )//151~155s，停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 15500)&&(nRoller3sCnt < 15700)  )//155~157s，正转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 15700)&&(nRoller3sCnt < 15900)  )//157~159s,停止
    {
        RollerMotor_Control(0,0);
        bManRollerZero = TRUE;
    }
    else if(   ( nRoller3sCnt > 15900)&&(nRoller3sCnt < 16100)  )//159~161s,正转
    {
        RollerMotor_Control(w_RollerPWM,1);
    }
    else  if(   ( nRoller3sCnt > 16100)&&(nRoller3sCnt < 16300)  )//161~163s，停止
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
    if(bManRollerZero == TRUE)return 0;//如果手动时速度为0，则上传手控器“滚筒速度为0”
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
//小腿和臀部
void Valve_LegFootAirPumpACPowerOn(void)
{
    GPIO_PinOutSet(VALVE_AIRPUMP2_PORT,VALVE_AIRPUMP2_BIT);
}
void Valve_LegFootAirPumpACPowerOff(void)
{
    GPIO_PinOutClear(VALVE_AIRPUMP2_PORT,VALVE_AIRPUMP2_BIT);
}
//臂肩，背腰，
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

void Valve_SetBackMode(int backauto) //背部自动模式时置1，否则置0
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
        nValveAlone = 0; //退出，由数组控制气囊
    }
}
/******************************************************************************/


//打开脚部气囊
void Valve_SetStretchCharge_FOOT(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //小腿气囊
    bLegLeftAirBagValve = VALVE_OFF;
    bLegRightAirBagValve = VALVE_OFF;
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
     bLeftArmUpAirBagValve1    =  VALVE_OFF ; //手肘左右气囊
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ; //手掌左右气囊 	  
     bRightArmUpAirBagValve1   =  VALVE_OFF ; 
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ;
    //肩部气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊
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
        bLeftArmUpAirBagValve1    =  VALVE_OFF ; //手肘左右气囊
        bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
        bLeftArmUpAirBagValve3    =  VALVE_OFF ; //手掌左右气囊 	  
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
        bRightArmUpAirBagValve1   =  VALVE_ON ; //右边两个气囊开       
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
    //小腿气囊
    bLegLeftAirBagValve  = VALVE_OFF;		
    bLegRightAirBagValve = VALVE_OFF;   
    //足部气囊
    bRightFootAirBagValve = VALVE_OFF;
    bLeftFootAirBagValve = VALVE_OFF;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊 
    //bhand_elbow_lAirBagValve   =  VALVE_OFF ; 	 
    //bhand_palm_lAirBagValve    =  VALVE_OFF ;  	  
    //bhand_palm_rAirBagValve    =  VALVE_OFF ;        
    //bhand_elbow_rAirBagValve   =  VALVE_OFF ;  
}
//脚部和腿部气囊都充气
void Valve_SetStretchCharge_FOOT_THIGH(unsigned int start)
{
    Valve_BodyUpAirPumpACPowerOn();
    Valve_LegFootAirPumpACPowerOn();
    //臂肩气囊
    //小腿气囊
    bLegLeftAirBagValve  = VALVE_ON;//VALVE_OFF;		
    bLegRightAirBagValve = VALVE_ON;//VALVE_OFF;              
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊    
    bLeftThighAirBagValve       =  VALVE_OFF;//N ;//US003
    bRightThighAirBagValve 	=  VALVE_OFF;//N ; //us003     
    //胳膊气囊
    bLeftSholderAirBagValve   =  VALVE_OFF ;
    bRightSholderAirBagValve  =  VALVE_OFF ;
    //背腰气囊   
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
    //小腿气囊
    bLegLeftAirBagValve  = VALVE_ON;//VALVE_OFF;		
    bLegRightAirBagValve = VALVE_ON;//VALVE_OFF;              
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    bFootHeelAirBagValve = VALVE_OFF;
    //大腿气囊
    bLeftThighAirBagValve       =  VALVE_OFF ;
    bRightThighAirBagValve 	=  VALVE_OFF ;  
    //胳膊气囊
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
    //背腰气囊  
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
    //小腿气囊
    bLegLeftAirBagValve  = VALVE_ON;		
    bLegRightAirBagValve = VALVE_ON;              
    //足部气囊
    bRightFootAirBagValve = VALVE_ON;
    bLeftFootAirBagValve = VALVE_ON;
    //大腿气囊
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
    //手臂气囊  
   bLeftArmUpAirBagValve1    =  VALVE_OFF ; 	 
     bLeftArmUpAirBagValve2    =  VALVE_OFF ; 
     bLeftArmUpAirBagValve3    =  VALVE_OFF ;
     bRightArmUpAirBagValve1   =  VALVE_OFF ;        
     bRightArmUpAirBagValve2   =  VALVE_OFF ;
     bRightArmUpAirBagValve3   =  VALVE_OFF ; 
}


