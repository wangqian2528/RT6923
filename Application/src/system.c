//#include "efm32.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "em_letimer.h"
#include "em_vcmp.h"
#include "system.h"
#include "Timer.h"
#include "LegMotor.h"
#include "BackPad.h"
#include "WalkMotor.h"
#include "SlideMotor.h"
#include "em_gpio.h"
#include "input.h"
#include "Valve.h"
#include "Data_Cul.h"
#include "IndicateLED.h"
#include "ADC_Scan.h"
#include "LED_RGB.h"        
#include "KneadMotor.h"        
#include "Walkmotor.h"        
#include "AxisMotor.h"        
#include "em_wdog.h"
#include "HandUart_New.h"
#include "signalUart_new.h"
#include "VoiceUart.h"
#include "WaistHot.h"
#include "Flex_Uart.h"
#include "UartLeg.h"
#include "SingleLine.h"
#include "system.h"
#include "em_timer.h"
//-----------新程序增加参数（system.c文件使用）start---------
//bool TimeCountStart;
//int ProgTime;
extern unsigned int bkneadTime;
extern unsigned char bkneadTimeFlag;
extern unsigned char WalkTimeFlag;
extern unsigned int WalkTime;
extern bool bkneadStopTimeFlag;
extern unsigned int bkneadStopTime;
extern bool _3D_TimeStopFlag;
unsigned short _3D_TotalTime;
//extern bool WalkStopCounterFlag;
//unsigned int WalkStopCounter;
bool ValveTimeFlag;
extern bool _3D_PosStop_TimeFlag;
unsigned char _3D_PosStop_Time;
extern bool pwm_time_flag;
extern unsigned char pwm_time;
unsigned char ValveTime;
//st_LEDCtrlStruct1 BlueCtrlStruct,RedCtrlStruct,GreenCtrlStruct;
//-------------------------------end---------------------------
extern void FlexMotor_10ms_Int(void);

extern void main_30ms_int(void);
extern void main_50ms_int(void);
extern void main_10ms_int(void);
extern void main_100ms_int(void);

extern void main_5ms_int(void);
extern void main_200ms_int(void);
bool  bTimer2MS;
unsigned int sysCounter=0;

extern unsigned long by_moni_cmd_tm;
extern unsigned int arm_100ms_time;

uint16_t SYS_Back_time;
void System_Initial_IO(void)
{
    CHIP_Init();
    CMU_HFRCOBandSet(cmuHFRCOBand_28MHz);  /** main system clock - internal RC 28MHz*/
    SystemCoreClockUpdate();
    CMU_ClockEnable(cmuClock_HFPER,true);  /** High frequency peripheral clock */
    CMU_ClockEnable(cmuClock_CORELE, true);/* Enable CORELE clock */
    CMU_ClockEnable(cmuClock_GPIO,true);   /** General purpose input/output clock. */
    CMU_ClockEnable(cmuClock_USART0,true); //165和valve
    CMU_ClockEnable(cmuClock_USART1,true); //与小腿通讯接口
    CMU_ClockEnable(cmuClock_USART2,true); //wifi接口
    CMU_ClockEnable(cmuClock_UART0,true);  //手控器接口
    CMU_ClockEnable(cmuClock_UART1,true);  //语音模块接口
    CMU_ClockEnable(cmuClock_LEUART1,true);  //机芯接口
    CMU_ClockEnable(cmuClock_ADC0, true);  
    CMU_ClockEnable(cmuClock_TIMER0,true); 
    CMU_ClockEnable(cmuClock_TIMER1,true);
    CMU_ClockEnable(cmuClock_TIMER2,true);
    CMU_ClockEnable(cmuClock_TIMER3,true);
    //CMU_ClockEnable(cmuClock_PRS, true);
    CMU_ClockEnable(cmuClock_DMA, true);        /* Enable DMA clock */
    //CMU_ClockEnable(cmuClock_LEUART0, true);    /* Enable LEUART1 clock */
    SysTick_Config(SystemCoreClock / 1000); //set 1ms interupt using systick
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO); //LFA选择内部32768时钟
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO);
    //GPIO_PinModeSet(TEST_PORT, TEST_BIT, TEST_MODE, 1);
    CMU_ClockEnable(cmuClock_LETIMER0, true);  
    //LETIMER_setup();
    /* Enable underflow interrupt */  
    LETIMER_IntEnable(LETIMER0, LETIMER_IF_UF);  
    /* Enable LETIMER0 interrupt vector in NVIC*/
    NVIC_EnableIRQ(LETIMER0_IRQn);
    
    CMU_IntClear(CMU_IFC_LFXORDY);
    CMU_IntEnable(CMU_IEN_LFXORDY);
    NVIC_EnableIRQ(CMU_IRQn);
    CMU_OscillatorEnable(cmuOsc_LFXO,1,0);
    
    VCMP_Init_TypeDef vcmp =
    {
        true,                               /* Half bias current */
        0,                                  /* Bias current configuration */
        true,                               /* Enable interrupt for falling edge */
        false,                              /* Enable interrupt for rising edge */
        vcmpWarmTime256Cycles,              /* Warm-up time in clock cycles */
        vcmpHyst20mV,                       /* Hysteresis configuration */
        1,                                  /* Inactive comparator output value */
        false,                              /* Enable low power mode */
        VCMP_VoltageToLevel(2.5), /* Trigger level */
        false                               /* Enable VCMP after configuration */
    };
    /* Initialize VCMP */
    CMU_ClockEnable(cmuClock_VCMP, true);
    VCMP_Init(&vcmp);
    
    /* Enable VCMP interrupt lines */
    NVIC_EnableIRQ(VCMP_IRQn);
    VCMP_IntEnable(VCMP_IEN_EDGE | VCMP_IEN_WARMUP);
    
    /* Enable VCMP and wait for warm-up complete */
    VCMP_Enable(); 
}
//1ms interupt

bool bFlag1ms;
unsigned char count_25ms=0;
void SysTick_Handler(void)
{
    static BYTE by_Time5ms = 0;
    static BYTE by_Time10ms = 0;
    static BYTE by_Time50ms = 0;
    static BYTE by_Time100ms = 0;
    static BYTE by_Time200ms = 0;
    static uint16_t Time_1s; 
    Time_1s++;
    if(Time_1s>=1000)
    {
        Time_1s =0;
        Data_Flag_Int();
    }
    SingleLine_TimeOut();  
    
    bFlag1ms = 1;
    if(sysCounter>=2)
    {
        sysCounter=0;
        n485_2ms();
    }
    else
    {
        sysCounter++;
    }
    
    //  Valve_1ms_Int();
    Voice_1msInt();
    Input_Back_Pulse1MS();
    
    //  UartLeg_RX_TimeoutInt();
    
    if(by_Time5ms >= 4)
    { 
        count_25ms++;
        if(count_25ms == 5)
        {
            count_25ms = 0 ;
            main_25ms_int();
        }
        by_Time5ms=0;
        
        Valve_10ms_Int();
        Input_5ms_Int();
        Axis_5ms_Int();
        //  main_5ms_int();
        //LED_RGB_5ms_Int();
        
    }                          
    else ++by_Time5ms;
    if(by_Time10ms >= 9)
    { 
        
        by_Time10ms = 0;  
        WDOG_Feed();
        
        SlideMotor_10ms_Int();
        LegMotor_10ms_int();
        KneadMotor_10ms_Int();
        main_10ms_int();
        LED_RGB_10ms_Int();
        BackMotor_10ms_int();
        SignalBoard_10msInt();//读取电机行程 开关计数
        AxisMotor_10msInt();
        WalkMotor_10msInt();
        Problem_10ms_Int();
        KnockMotor_10msInt();
        FlexMotor_10ms_Int();//新移植
        UartLeg_10msInt();//3D
        RollerMotor_10msInt();//新移植
        if(_3D_PosStop_TimeFlag)
        {
            _3D_PosStop_Time++;
        }
        if(bkneadTimeFlag)
        {
            bkneadTime++;
        }
        if(WalkTimeFlag)
        {
            WalkTime++;
        }
        
    }                          
    else ++by_Time10ms;
    
    
    
    if(by_Time50ms >= 50)
    {              
        
        by_Time50ms = 0;         
        main_50ms_int();
        
    }                          
    else ++by_Time50ms;
    
    if(by_Time100ms >= 100)
    {                          
        by_Time100ms = 0;  
        nValveAloneTime++;
        LED_RGB_100ms_Int();
        WaistHeat_100ms_Int();
        //   VoiceUart_100msInt();
        
        AxisMotor_100msInt();
        Timer_Flag_100ms_Int();
        //        Flex_100msInt();
	FlexMotor_100ms_Int();//新移植
        if(bkneadStopTimeFlag)
        {
            bkneadStopTime++;
        }
        if(ValveTimeFlag)
        {
            ValveTime++;
        }
        //main_100ms_int();//100ms上传手控器一次 数据给
        
        if(by_moni_cmd_tm>1)by_moni_cmd_tm--;   // 减到1不减。
        
	arm_100ms_time++;
    }                          
    else ++by_Time100ms;
    if(by_Time200ms >= 200)
    {                 
        by_Time200ms = 0;
        main_200ms_int();
        SYS_Back_time++;
    }                          
    else ++by_Time200ms;
}

void System_Delay_us(uint32_t ulData)
{
    while(ulData > 0)
    {
      __NOP();__NOP();__NOP();__NOP();__NOP();
      __NOP();__NOP();__NOP();__NOP();__NOP();
      __NOP();__NOP();__NOP();__NOP();__NOP();
      __NOP();__NOP();__NOP();__NOP();__NOP();
      ulData--;
    }
}

void CMU_IRQHandler(void)
{
    NVIC_DisableIRQ(CMU_IRQn);
    CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);  //选择外部32768时钟
    CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);  //选择外部32768时钟
    CMU_OscillatorEnable(cmuOsc_LFRCO,0,0);  //禁止内部32768时钟，省电 
}
/**************************************************************************//**
* @brief LETIMER0_IRQHandler
* Interrupt Service Routine for LETIMER
* 中断时间1秒钟
*****************************************************************************/
void LETIMER0_IRQHandler(void)
{ 
    /* Clear LETIMER0 underflow interrupt flag */
    LETIMER_IntClear(LETIMER0, LETIMER_IF_UF);
   // Data_Flag_Int();
    SingleLine_Rec();
}


unsigned int  System_GetCounter(void)
{ 
    return(sysCounter);
}

void System_clr_Counter(void)
{
  
  sysCounter=0;
}
/***************************************************************************//**
* @brief
*   VCMP interrupt handler, triggers on EDGE and WARMUP events
******************************************************************************/
extern unsigned int password;
void VCMP_IRQHandler()
{
    /* Execute on WARMUP interrupt */
    if (VCMP->IF & VCMP_IF_WARMUP)
    {
        /* Enable Low Power Reference */
        // VCMP_LowPowerRefSet(true);
        
        /* Clear interrupt flag */
        VCMP_IntClear(VCMP_IFC_WARMUP);
    }
    
    /* Execute on EDGE interrupt */
    if (VCMP->IF & VCMP_IF_EDGE)
    {
        /* Low voltage warning */
        password = 0;  //低电压清除password
        
        /* Clear interrupt flag */
        VCMP_IntClear(VCMP_IFC_EDGE);
    }
}

//void TIMER2_IRQHandler(void)  
//{
//    TIMER_IntClear(TIMER2,TIMER_IFC_OF);  //清除定时中断标志 
//    if(nChairRunState != CHAIR_STATE_RUN)
//    {       
//         LED_RGB_Red_Clear();
//         LED_RGB_Green_Clear();
//         LED_RGB_Blue_Clear();
//         TIMER_IntDisable(TIMER2,TIMER_IF_OF);
//         return;
//    }
//    BlueCtrlStruct.LEDLowTime_Init = 100 - BlueCtrlStruct.LEDHighTime_Init;
//    BlueCtrlStruct.LEDLowTime_Target = 100 - BlueCtrlStruct.LEDHighTime_Target;
//    RedCtrlStruct.LEDLowTime_Init = 100 - RedCtrlStruct.LEDHighTime_Init;
//    RedCtrlStruct.LEDLowTime_Target = 100 - RedCtrlStruct.LEDHighTime_Target;
//    GreenCtrlStruct.LEDLowTime_Init = 100 - GreenCtrlStruct.LEDHighTime_Init;
//    GreenCtrlStruct.LEDLowTime_Target = 100 - GreenCtrlStruct.LEDHighTime_Target;
//    
//    if((BlueCtrlStruct.LEDHighTime > 0)&&(BlueCtrlStruct.LEDHighTime <= 100))
//    {
//      LED_RGB_Blue_Set();
//      BlueCtrlStruct.LEDHighTime-- ;
//    }
//    else if(( BlueCtrlStruct.LEDLowTime > 0)&&(BlueCtrlStruct.LEDLowTime <= 100))
//    {
//      LED_RGB_Blue_Clear();
//      BlueCtrlStruct.LEDLowTime-- ;
//    }
//    else
//    {  
//        BlueCtrlStruct.LEDCycount++;
//        if(BlueCtrlStruct.LEDCycount < 2)
//        {
//          BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//          BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//        }
//        else
//        {
//            BlueCtrlStruct.LEDCycount = 0;
//            if((BlueCtrlStruct.LEDCtrlMode == LED_LIGHT)||(BlueCtrlStruct.LEDCtrlMode == LED_DARK))
//            {
//                 BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//                 BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//            }
//            else if(BlueCtrlStruct.LEDCtrlMode == LED_SLOWLY_LIGHT)
//            {
//                if((BlueCtrlStruct.LEDHighTime_Init == BlueCtrlStruct.LEDHighTime_Target)||(BlueCtrlStruct.LEDLowTime_Init == BlueCtrlStruct.LEDLowTime_Target))
//                {
//                     BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//                     BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     BlueCtrlStruct.LEDHighTime_Init += 1;
//                     BlueCtrlStruct.LEDLowTime_Init -= 1;
//                     BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//                     BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//                }
//            }
//            else if(BlueCtrlStruct.LEDCtrlMode == LED_SLOWLY_DARK)
//            {
//                if((BlueCtrlStruct.LEDHighTime_Init == BlueCtrlStruct.LEDHighTime_Target)||(BlueCtrlStruct.LEDLowTime_Init == BlueCtrlStruct.LEDLowTime_Target))
//                {
//                     BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//                     BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     BlueCtrlStruct.LEDHighTime_Init -= 1;
//                     BlueCtrlStruct.LEDLowTime_Init += 1;
//                     BlueCtrlStruct.LEDHighTime = BlueCtrlStruct.LEDHighTime_Init;
//                     BlueCtrlStruct.LEDLowTime =  BlueCtrlStruct.LEDLowTime_Init;
//                }
//            }
//        }
//    } 
//    if((RedCtrlStruct.LEDHighTime > 0)&&(RedCtrlStruct.LEDHighTime <= 100))
//    {
//      LED_RGB_Red_Set();
//      RedCtrlStruct.LEDHighTime--;
//    }
//    else if((RedCtrlStruct.LEDLowTime > 0)&&(RedCtrlStruct.LEDLowTime <= 100))
//    {
//      LED_RGB_Red_Clear();
//      RedCtrlStruct.LEDLowTime--;
//    }
//    else
//    {      
//        RedCtrlStruct.LEDCycount++;
//        if(RedCtrlStruct.LEDCycount < 2)
//        {
//          RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//          RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//        }
//        else
//        {
//            RedCtrlStruct.LEDCycount = 0;
//            if((RedCtrlStruct.LEDCtrlMode == LED_LIGHT)||(RedCtrlStruct.LEDCtrlMode == LED_DARK))
//            {
//                 RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//                 RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//            }
//            else if(RedCtrlStruct.LEDCtrlMode == LED_SLOWLY_LIGHT)
//            {
//                if((RedCtrlStruct.LEDHighTime_Init == RedCtrlStruct.LEDHighTime_Target)||(RedCtrlStruct.LEDLowTime_Init == RedCtrlStruct.LEDLowTime_Target))
//                {
//                     RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//                     RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     RedCtrlStruct.LEDHighTime_Init += 1;
//                     RedCtrlStruct.LEDLowTime_Init -= 1;
//                     RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//                     RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//                }
//            }
//            else if(RedCtrlStruct.LEDCtrlMode == LED_SLOWLY_DARK)
//            {
//                if((RedCtrlStruct.LEDHighTime_Init == RedCtrlStruct.LEDHighTime_Target)||(RedCtrlStruct.LEDLowTime_Init == RedCtrlStruct.LEDLowTime_Target))
//                {
//                     RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//                     RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     RedCtrlStruct.LEDHighTime_Init -= 1;
//                     RedCtrlStruct.LEDLowTime_Init += 1;
//                     RedCtrlStruct.LEDHighTime = RedCtrlStruct.LEDHighTime_Init;
//                     RedCtrlStruct.LEDLowTime =  RedCtrlStruct.LEDLowTime_Init;
//                }
//            }
//        }
//    }
//    
//    if((GreenCtrlStruct.LEDHighTime > 0)&&(GreenCtrlStruct.LEDHighTime <= 100))
//    {
//      LED_RGB_Green_Set();
//      GreenCtrlStruct.LEDHighTime--;
//    }
//    else if((GreenCtrlStruct.LEDLowTime > 0)&&(GreenCtrlStruct.LEDLowTime <= 100))
//    {
//      LED_RGB_Green_Clear();
//      GreenCtrlStruct.LEDLowTime--;
//    }
//    else
//    {  
//        GreenCtrlStruct.LEDCycount++;
//        if(GreenCtrlStruct.LEDCycount < 2)
//        {
//          GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//          GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//        }
//        else
//        {
//            GreenCtrlStruct.LEDCycount = 0;
//            if((GreenCtrlStruct.LEDCtrlMode == LED_LIGHT)||(GreenCtrlStruct.LEDCtrlMode == LED_DARK))
//            {
//                 GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//                 GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//            }
//            else if(GreenCtrlStruct.LEDCtrlMode == LED_SLOWLY_LIGHT)
//            {
//                if((GreenCtrlStruct.LEDHighTime_Init == GreenCtrlStruct.LEDHighTime_Target)||(GreenCtrlStruct.LEDLowTime_Init == GreenCtrlStruct.LEDLowTime_Target))
//                {
//                     GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//                     GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     GreenCtrlStruct.LEDHighTime_Init += 1;
//                     GreenCtrlStruct.LEDLowTime_Init -= 1;
//                     GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//                     GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//                }
//            }
//            else if(GreenCtrlStruct.LEDCtrlMode == LED_SLOWLY_DARK)
//            {
//                if((GreenCtrlStruct.LEDHighTime_Init == GreenCtrlStruct.LEDHighTime_Target)||(GreenCtrlStruct.LEDLowTime_Init == GreenCtrlStruct.LEDLowTime_Target))
//                {
//                     GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//                     GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//                }
//                else
//                {
//                     GreenCtrlStruct.LEDHighTime_Init -= 1;
//                     GreenCtrlStruct.LEDLowTime_Init += 1;
//                     GreenCtrlStruct.LEDHighTime = GreenCtrlStruct.LEDHighTime_Init;
//                     GreenCtrlStruct.LEDLowTime =  GreenCtrlStruct.LEDLowTime_Init;
//                }
//            }
//        }
//    }
//} 
