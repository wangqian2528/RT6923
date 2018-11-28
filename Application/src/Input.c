
/*
* Function: Input signal process
*/
/************************************************************************************/

#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "LegMotor.h"
#include "Valve.h"
#include "WalkMotor.h"
#include "AxisMotor.h"
#include "MassageStatus.h"
#include "memory.h"
#include "signalUart_new.h"
#include "backaction.h"
#include "BackPad.h"

#include "UartLeg.h"

#include "input.h"
#include "SingleLine.h"

BITS InputData1;
#define bLegDownSwitch 	        InputData1.bD0   
#define bLegUpSwitch		InputData1.bD1   
#define bSlidePadUpSwitch	InputData1.bD2  
#define bSlidePadDownSwitch	InputData1.bD3   
#define bWalkDownSwitch 	InputData1.bD4   
#define bWalkUpSwitch           InputData1.bD5   
#define bBackUpSwitch		InputData1.bD6
#define bBackDownSwitch		InputData1.bD7

BITS InputData2;

#define bShould         InputData2.bD0
#define bShouldDelay    InputData2.bD1
#define bVshoulder      InputData2.bD2
#define bFootSwitch     InputData2.bD3
#define bAngleSwitch    InputData2.bD4
#define bGroudSwitch    InputData2.bD5
#define bFlexInSwitch   InputData2.bD6
#define bFlexOutSwitch  InputData2.bD7

#define Data1Offset         0
#define Data2Offset         1
#define Data3Offset         2



typedef  struct
{
        unsigned char timer_H;
        unsigned char timer_L;
        unsigned char flag;
}INPUT_ST;
bool vReadSholuder=0;
bool bWalkChange,bInputReady;
bool _3DfrontSwitch, _3DBackSwitch;
  
INPUT_ST st_FlexGround,st_StretchOut,st_StretchIn,st_Foot,st_Angle,st_Vout,st_AxisSW;
INPUT_ST st_SlideUp,st_SlideDown,st_BackUp,st_BackDown,st_LegUp,st_LegDown,st_WalkUp,st_WalkDown;
bool b5msFlag;
BYTE nPulseHigh;
UINT16 WalkCount = 0xffff;  // 0xffff indicate no initial, at top =0 at bottom = maximal, up:dec down:add
BYTE by_KneadPosition = KNEAD_WIDTH_UNKNOWN;
volatile unsigned short nCurWalkLocate;
//unsigned short nCounterCurWalkLocate;
unsigned short nCurAxisLocate;
unsigned short nCounterCurAxisLocate;
unsigned int tickAxisCount;
bool bKneadMin,bKneadMid,bKneadMax,bBalance;
bool bWalkPulseCount,bPreWalkPulseCount;
//unsigned int axisTickTimedec[100];
//unsigned int axisTickTimeadd[100];


volatile unsigned int nCurBackLocate;


unsigned int tet,tet2;
unsigned int cont;

unsigned int phawe;
/***************************


��Ӽ粿��⵽λ������ʱ�����߼����ӣ����������ļ粿λ��
******************************/

/**************************************************************************//**
 * @brief GPIO_ODD_IRQHandler
 * Interrupt Service Routine Odd GPIO Interrupt Line

  if(GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT))//PHASE=1 ������ϣ����������С
  {
    if(w_Position > 0) w_Position--;  
  }
  else
  {
    if(w_Position < BACK_MOTOR_MAX_POSITION) w_Position++;  
  }
 *****************************************************************************/
//get backmotor's pulse
#define BACK_PULSE_CHECK_TIME 3
unsigned char BackPulseCountHigh = 0;
unsigned char BackPulseCountLow = 0;
static unsigned char BackPulseStep = 0;//���������ױ��Ż���ɿ�������ʧЧ

/******************************************************************
����˵���������������������ÿ1ms���һ������˿ڵ�ֵ
��������
����ֵ����
����˵����1ms���һ������˿ڵ�ֵ��һ����ƽ���ֹ�4�μ�4ms�Ժ����Ϊ
          ��ȷ����һ����/�͵�ƽ��һ����-�͵ĵ�ƽת����Ϊ��һ��������
          ��
******************************************************************/
void Input_Back_Pulse1MS(void)
{
    bool flag = GPIO_PinInGet(INPUT_BACK_PULSE_PORT, INPUT_BACK_PULSE_BIT);
    if(flag == 0)
    {
        //�͵�ƽΪ������Ч
        BackPulseCountLow++;
    }
    else
    {
        BackPulseCountHigh++;
    }
    //�Ӹߵ����ٵ���Ϊ1����Ч��
    switch(BackPulseStep)
    {
    case 0:
        if((flag == 1) && (BackPulseCountHigh > BACK_PULSE_CHECK_TIME))
        {
            BackPulseCountLow = 0;
            BackPulseStep = 1;
        }
        break;
    case 1:
        //�Ӹߵ����ٵ���Ϊ1����Ч��
        if((flag == 0) && (BackPulseCountLow > BACK_PULSE_CHECK_TIME))
        {
            BackPulseCountHigh = 0;
            BackPulseStep = 0;
            //����
            if(!GPIO_PinOutGet(BACK_MOTOR_PHASE_PORT, BACK_MOTOR_PHASE_BIT) != 0)
            {
                if(nCurBackLocate > 0 )nCurBackLocate-- ;
            }
            else
            {
                nCurBackLocate++ ;
            }
        }
        break;
    default:
        BackPulseStep = 0;
        break;
    }
}







void GPIO_ODD_IRQHandler(void)
{
  /*
  //PHASE=1 ������ϣ����������С
if(GPIO_IntGet()&(1<<INPUT_BACK_PULSE_BIT))
	{
	  

		GPIO_IntClear(1<<INPUT_BACK_PULSE_BIT);//�������� �����������
		
		
		if(BackMotor_GetDirection() != BACK_MOTOR_GO_UP )//  BACK_MOTOR_GO_DOWN 
		{
			if(nCurBackLocate < BACK_MOTOR_MAX_POSITION_PULSE)//BACK_MOTOR_MAX_LOCATION)
			{
				nCurBackLocate++ ;
			}       
			if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)//���г̿���
			{
				nCurBackLocate = BACK_MOTOR_MAX_POSITION_PULSE;//BACK_MOTOR_MAX_LOCATION;
			}
			
		//	cont=200;
			
			
		}
		else//�����������������С
		{
		  
		  

	  
			if(nCurBackLocate > 0 )
			{
				nCurBackLocate-- ;
			}

			if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
			{
				nCurBackLocate =0;
			}
		}
	}
  
  */
}

void GPIO_EVEN_IRQHandler(void)
{ 
  SingleLine_Interruput();
  if(GPIO_IntGet()&(1<<INPUT_WALK_PULSE_BIT))//��ȡ3D��о�����ߵ�������ź�
  {
    bWalkChange = TRUE;
    GPIO_IntClear(1<<INPUT_WALK_PULSE_BIT);
    if(WalkMotor_GetDirection() != WALK_MOTOR_GO_UP)
    {
      if(nCurWalkLocate > 0 )
      {
          nCurWalkLocate-- ;
      }
    }
    else
    {
      if(nCurWalkLocate < 1000)
      {
          nCurWalkLocate++ ;
      }
    }
  } 
}

void Input_SetWalkMotorPosition(unsigned short locate)
{
//#ifdef RT8600S
      nCurWalkLocate = (unsigned short)locate<<2;
//#else
  
 //     nCurWalkLocate = (unsigned short)locate*2;
//#endif
  
}
unsigned short Input_GetWalkMotorPosition(void)//
{

       return(nCurWalkLocate>>2);//4��Ƶ

}

//�෴����
void Input_SetCounterWalkMotorPosition(unsigned short locate) //8600
{
  return;
  //nCounterCurWalkLocate = (unsigned short)locate;
  //nCounterCurWalkLocate *= 2;
}
/*
unsigned short Input_GetCounterWalkMotorPosition(void) //8600
{
  return(nCounterCurWalkLocate/2);
}
*/
void Input_SetAxisMotorPosition(unsigned short locate)//3D��о��������
{
  nCurAxisLocate = (unsigned short)locate;
}
unsigned short Input_GetAxisMotorPosition(void)
{
  return(nCurAxisLocate);
}

//�෴����
void Input_SetCounterAxisMotorPosition(unsigned short locate) //8600
{
  nCounterCurAxisLocate = (unsigned short)locate;
  nCounterCurAxisLocate *= 2;
}
unsigned short Input_GetCounterAxisMotorPosition(void) //8600
{
  return(nCounterCurAxisLocate/2);
}

void Input_Initial_IO(void)
{
  /*
#ifdef RT8600S
  GPIO_PinModeSet(INPUT_WALK_PULSE_PORT, INPUT_WALK_PULSE_BIT, INPUT_WALK_PULSE_MODE, 1);
                     // GPIO_PinModeSet(INPUT_KNEAD_MAX_PORT, INPUT_KNEAD_MAX_BIT, INPUT_KNEAD_MAX_MODE, 1);
                     // GPIO_PinModeSet(INPUT_KNEAD_MID_PORT, INPUT_KNEAD_MID_BIT, INPUT_KNEAD_MID_MODE, 1);
                     // GPIO_PinModeSet(INPUT_KNEAD_MIN_PORT, INPUT_KNEAD_MIN_BIT, INPUT_KNEAD_MIN_MODE, 1);
                      
                    
                        
                      //GPIO_IntConfig(INPUT_KNEAD_MAX_PORT, INPUT_KNEAD_MAX_BIT, false, true, true);
                      //GPIO_IntConfig(INPUT_KNEAD_MID_PORT, INPUT_KNEAD_MID_BIT, false, true, true);
                      //GPIO_IntConfig(INPUT_KNEAD_MIN_PORT, INPUT_KNEAD_MIN_BIT, false, true, true);
                      
                      
                      //GPIO_PinModeSet(INPUT_LEG_FOOT_PORT, INPUT_LEG_FOOT_BIT, INPUT_LEG_FOOT_MODE, 1);
  
#else  */
  GPIO_PinModeSet(INPUT_WALK_PULSE_PORT, INPUT_WALK_PULSE_BIT, INPUT_WALK_PULSE_MODE, 1);
 // GPIO_IntConfig(INPUT_WALK_PULSE_PORT, INPUT_WALK_PULSE_BIT, false, true, true);
  
  
  GPIO_PinModeSet(INPUT_BACK_PULSE_PORT, INPUT_BACK_PULSE_BIT, INPUT_BACK_PULSE_MODE, 1);
//  GPIO_IntConfig(INPUT_BACK_PULSE_PORT, INPUT_BACK_PULSE_BIT, false, true, true);
  
  
  
  
 // NVIC_EnableIRQ(GPIO_ODD_IRQn);
//  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
//#endif
  
              //        GPIO_PinModeSet(INPUT_KNEAD_MAX_PORT, INPUT_KNEAD_MAX_BIT, INPUT_KNEAD_MAX_MODE, 1);
              //        GPIO_PinModeSet(INPUT_KNEAD_MID_PORT, INPUT_KNEAD_MID_BIT, INPUT_KNEAD_MID_MODE, 1);
              //        GPIO_PinModeSet(INPUT_KNEAD_MIN_PORT, INPUT_KNEAD_MIN_BIT, INPUT_KNEAD_MIN_MODE, 1);
 //  GPIO_PinModeSet(INPUT_SHOULDER_PULSE_PORT, INPUT_SHOULDER_PULSE_BIT, INPUT_SHOULDER_PULSE_MODE, 1);
  
                    //  GPIO_PinModeSet(INPUT_BACK_PULSE_PORT, INPUT_BACK_PULSE_BIT, INPUT_BACK_PULSE_MODE, 1);
                      //GPIO_IntConfig(INPUT_BACK_PULSE_PORT, INPUT_BACK_PULSE_BIT, false, true, true);
                    //  GPIO_PinModeSet(INPUT_AXIS_PULSE_PORT, INPUT_AXIS_PULSE_BIT, INPUT_AXIS_PULSE_MODE, 1);
                     // GPIO_IntConfig(INPUT_AXIS_PULSE_PORT, INPUT_AXIS_PULSE_BIT, false, true, true);
                     // GPIO_PinModeSet(INPUT_AXIS_SW_PORT, INPUT_AXIS_SW_BIT, INPUT_AXIS_SW_MODE, 1);
                    //  GPIO_PinModeSet(INPUT_VOUT_PORT, INPUT_VOUT_BIT, INPUT_VOUT_MODE, 1);
                      
                    //  GPIO_PinModeSet(INPUT_BACK_UP_PORT, INPUT_BACK_UP_BIT, INPUT_BACK_UP_MODE, 1); 
                    //  GPIO_PinModeSet(INPUT_BACK_DOWN_PORT, INPUT_BACK_DOWN_BIT, INPUT_BACK_DOWN_MODE, 1); 
                      
                    //  GPIO_PinModeSet(INPUT_LEG_UP_PORT, INPUT_LEG_UP_BIT, INPUT_LEG_UP_MODE, 1); 
                    //  GPIO_PinModeSet(INPUT_LEG_DOWN_PORT, INPUT_LEG_DOWN_BIT, INPUT_LEG_DOWN_MODE, 1); 
                      
                    //  GPIO_PinModeSet(INPUT_WALK_UP_PORT, INPUT_WALK_UP_BIT, INPUT_WALK_UP_MODE, 1); 
                    //  GPIO_PinModeSet(INPUT_WALK_DOWN_PORT, INPUT_WALK_DOWN_BIT, INPUT_WALK_DOWN_MODE, 1); 
                      
                    //  GPIO_PinModeSet(INPUT_ZERO_UP_PORT, INPUT_ZERO_UP_BIT, INPUT_ZERO_UP_MODE, 1); 
                    //  GPIO_PinModeSet(INPUT_ZERO_DOWN_PORT, INPUT_ZERO_DOWN_BIT, INPUT_ZERO_DOWN_MODE, 1); 
                      //  GPIO_PinModeSet(INPUT_WAVE_PORT, INPUT_WAVE_BIT, INPUT_WAVE_MODE, 1); 
                      
                      //  NVIC_EnableIRQ(GPIO_ODD_IRQn);
   // NVIC_EnableIRQ(GPIO_EVEN_IRQn);
}
void Input_5ms_Int(void)
{
    tickAxisCount++;
    if(AxisMotor_IsRun())
    {
      tickAxisCount++;
    }
    b5msFlag = 1;
}

void Input_High(INPUT_ST* p)
{
  p->timer_L = 0;
  p->timer_H ++; 
  if((p->timer_H) >= 2)
  {
    p->timer_H = 2;
    p->flag = 1;
  }
}
void Input_Low(INPUT_ST* p)
{
  p->timer_H = 0;
  p->timer_L ++; 
  if((p->timer_L) >= 2)
  {
    p->timer_L = 2;
    p->flag = 0;
  }
}
/*

BITS InputData1;
#define bLegDownSwitch 	        InputData1.bD0   
#define bLegUpSwitch		InputData1.bD1   
#define bSlidePadUpSwitch	InputData1.bD2  
#define bSlidePadDownSwitch	InputData1.bD3   
#define bWalkDownSwitch 	InputData1.bD4   
#define bWalkUpSwitch           InputData1.bD5   
#define bBackUpSwitch		InputData1.bD6
#define bBackDownSwitch		InputData1.bD7
*/


void Input_Proce(void)
{
    unsigned char signal,switch_signal;
    unsigned char switch_Flexsignal;
    static int counter;  
    static unsigned short nOldCurAxisLocate = 0;
    if(!b5msFlag) return;//���ƴ˺���ÿ5smִ��һ��	
    b5msFlag = 0;
    if(++counter >= 4) bInputReady = true;//20ms���˱�����1һ�Σ����Ǳ���δʹ��
    
    if(UartLeg_Get3DMessage_RXStatus())
    {
        UartLeg_Clr_3DMessageStatus();
        UartLeg_3DMessageCopyData ();  
    }
    
    nCurAxisLocate = UartLeg_Get3DPluse();//3D��о����λ������
    if(nOldCurAxisLocate |= nCurAxisLocate);
    {
        AxisMotor_UpdataPosition();
        nOldCurAxisLocate = nCurAxisLocate;
    }
    /***************************************************************************************************
    ��о��������źţ�
           0            1             2            3         4             5             6            7  
          ��           ��            խ                  bShould       3D����λ      3Dǰ��λ
    ***************************************************************************************************/
    signal = UartLeg_Get3DMassageSignal();
    if(signal&BIT0)
    {
        by_KneadPosition = KNEAD_WIDTH_MAX;  
        bKneadMin = 1;
        bKneadMid = 1; 
        bKneadMax = 0;
    }
    if(signal&BIT1)
    {
        by_KneadPosition = KNEAD_WIDTH_MED;    
        bKneadMin = 1;
        bKneadMid = 0; 
        bKneadMax = 1;
    }
    if(signal&BIT2)
    {
        by_KneadPosition = KNEAD_WIDTH_MIN;    
        bKneadMin = 0;
        bKneadMid = 1; 
        bKneadMax = 1;
    }
    KneadMotor_CalculateSpeed(by_KneadPosition);
    if(signal&BIT4)
    {
        bShould = 1;
        bShouldDelay =1;
    }
    else
    {
        bShould = 0;
        bShouldDelay =0;
    }
    if(signal&BIT5)
    {
        _3DBackSwitch = 1;
    }
    else
    {
        _3DBackSwitch = 0;
    }
    if(signal&BIT6)
    {
        _3DfrontSwitch = 1;
    }
    else
    {
        _3DfrontSwitch = 0; 
    }
    /***************************************************************************************************
    �źŰ�����ĵ�1֡�źţ�
            0 	   1		 2	      3         4             5             6            7        
	                                           С������λ    С������λ    ��������λ    ��������λ
    ***************************************************************************************************/
    signal = SignalBoard_GetMassageSignal();
    if(signal&BIT4)
    {
        bLegUpSwitch=1; 
    }
    else
    {
        bLegUpSwitch=0;
    }
    if(signal&BIT5)  
    {
        bLegDownSwitch=1;
    }
    else
    {
        bLegDownSwitch=0; 
    }  
    if(signal&BIT6)  
    {
        bBackUpSwitch =1;
    }
    else
    {
        bBackUpSwitch=0;
    }  
    if(signal&BIT7)   
    {
        bBackDownSwitch=1;
    }
    else
    {
        bBackDownSwitch=0;
    }  
    /**************************************************************************************************************
    �źŰ�����ĵ�2֡�źţ�
                 0            1             2            3         4             5             6            7       
            ��������λ    ��������λ     �ŵ׿���               ���ؿ���      �Ƕȿ���     ��������λ   ����ǰ��λ
    **************************************************************************************************************/
    switch_signal = SignalBoard_GetSwitchSignal();
    if(switch_signal&BIT0)
    {
        bWalkDownSwitch=1;
    }
    else
    {
        bWalkDownSwitch=0; 
    }  
    if(switch_signal&BIT1)
    {
        bWalkUpSwitch=1; 
    }
    else
    {
        bWalkUpSwitch=0;
    }  
    if(switch_signal&BIT2)
    {
        bFootSwitch=0;//�ŵ׸�Ӧ��Ч��0
    }
    else
   {
       bFootSwitch=1; //��Ч��1
   } 
   if(switch_signal&BIT4)
   {
     bGroudSwitch=0;//����λ��0
   }
   else
   {
     bGroudSwitch=1; //δ��������λ��1
   }    
   
   if(switch_signal&BIT5)
   {
     bAngleSwitch=0;//δ��Σ����λ
   }
   else
   {
     bAngleSwitch=1; //��Σ����λ
   } 
    if(switch_signal&BIT6)
    {
        bSlidePadDownSwitch=1; 
    }
    else
    {
        bSlidePadDownSwitch=0;
    }    
    if(switch_signal&BIT7)
    {
        bSlidePadUpSwitch=1; 
    }
    else
    {
        bSlidePadUpSwitch=0; 
    }  
    /***********************************************************************************************
    �źŰ���յĵ�3֡����:
             0            1             2            3         4             5          6         7   
	��������λ    ��������λ
    ***********************************************************************************************/
    switch_Flexsignal = SignalBoard_GetSwitchFlexSignal();
   if(switch_Flexsignal&BIT0)
   {
     bFlexOutSwitch=1;
   }
   else
   {
     bFlexOutSwitch=0;//bFlexOutSwitch=0; 
   }   
   if(switch_Flexsignal&BIT1)
   {
     bFlexInSwitch=1;//bFlexInSwitch=1;
   }
   else
   {
     bFlexInSwitch=0;//bFlexInSwitch=0; 
   } 
    
//    bLegStretchGroundSwitch?Input_High(&st_FlexGround):Input_Low(&st_FlexGround);
//    bLegUpSwitch ? Input_High(&st_LegUp):Input_Low(&st_LegUp);
//    bLegDownSwitch ? Input_High(&st_LegDown):Input_Low(&st_LegDown); 
//    bBackUpSwitch ? Input_High(&st_BackUp):Input_Low(&st_BackUp);  
//    bBackDownSwitch ? Input_High(&st_BackDown):Input_Low(&st_BackDown);			
      bSlidePadUpSwitch ? Input_High(&st_SlideUp):Input_Low(&st_SlideUp);
      bSlidePadDownSwitch ? Input_High(&st_SlideDown):Input_Low(&st_SlideDown);
//    bWalkUpSwitch ? Input_High(&st_WalkUp):Input_Low(&st_WalkUp);
//    bWalkDownSwitch ? Input_High(&st_WalkDown):Input_Low(&st_WalkDown);
    
    //#ifndef RT8600S
    bWalkPulseCount = GPIO_PinInGet(INPUT_WALK_PULSE_PORT, INPUT_WALK_PULSE_BIT);
    if(bPreWalkPulseCount != bWalkPulseCount)
    { 
        if(WalkMotor_GetDirection() != WALK_MOTOR_GO_UP)//�������
        {
            if(nCurWalkLocate > 0 )
            {
                nCurWalkLocate-- ;
            }
            if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(0);
            }
        }
        else
        {
            if(nCurWalkLocate < 2000)
            {
                nCurWalkLocate++ ;
            }
            if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
            {
                Input_SetWalkMotorPosition(TOP_POSITION);//1
            }
        }
    }
    bPreWalkPulseCount = bWalkPulseCount;
}
  


unsigned int Input_GetKneadMax(void)
{
    return(bKneadMax);
}

unsigned int Input_GetKneadMid(void)
{
    return(bKneadMid);
}

unsigned int Input_GetKneadMin(void)
{
    return(bKneadMin);
}

bool Input_Get3DFrontSwitch(void)
{
    return(_3DfrontSwitch);
} 

bool Input_Get3DBackSwitch(void)
{
  return(_3DBackSwitch);
} 

unsigned int Input_GetVout(void)
{
    if(bShouldDelay==0) return BODY_TOUCHED; //����ģʽ���Ǽ������Ч��
    return BODY_NO_TOUCHED;
}

unsigned int Input_GetLegUpSwitch(void)
{
    return(bLegUpSwitch);
}

unsigned int Input_GetLegDownSwitch(void)
{
    return(bLegDownSwitch);
}

unsigned int Input_GetBackUpSwitch(void)
{
    return(bBackUpSwitch);
} 

unsigned int Input_GetBackDownSwitch(void)
{
    return(bBackDownSwitch);
}   

unsigned int Input_GetWalkUpSwitch(void)
{
    return(bWalkUpSwitch);
}

unsigned int Input_GetWalkDownSwitch(void)
{
    return(bWalkDownSwitch);
}

unsigned int Input_GetFlexFootSwitch(void)
{
    return bFootSwitch;
}

unsigned int Input_GetFlexGroundSwitch(void)
{
    return bGroudSwitch;   
}

unsigned int Input_GetFlexAngleSwitch(void)
{
    return bAngleSwitch;
}

unsigned int Input_GetSlideBackwardSwitch(void)
{
    bool enable = ReadEEByte(USER_DATA_BASE + SLIDE_MOTOR_ENABLE_ADDRESS);
    if(enable)
        return(st_SlideDown.flag);
    else return(1);
}

unsigned int Input_GetSlideForwardSwitch(void)
{
    bool enable = ReadEEByte(USER_DATA_BASE + SLIDE_MOTOR_ENABLE_ADDRESS);
    if(enable)
        return(st_SlideUp.flag);
    else
        return(1);
}

unsigned int Input_GetFlexInSwitch(void)
{
    return bFlexInSwitch;   
}       

unsigned int Input_GetFlexOutSwitch(void)
{
    return bFlexOutSwitch;
}  

/********���ڹ���ģʽ����ʾ����խֵ*********/
uint8_t Input_Get_Mim_Max()
{
    if(bKneadMin==0) return 1;
    else if(bKneadMid==0) return 2;
    else  if(bKneadMax==0) return 3;
}

unsigned char Input_GetBalance(void)
{
    return(bBalance);
}

unsigned int Input_GetKneadPosition(void)
{
    return (unsigned int)by_KneadPosition;
}

/*
unsigned int Input_GetAxisSW(void)
{
  return(st_AxisSW.flag);
}
*/
//unsigned int Input_GetFlexGroundSwitch(void)
//{
 // return(st_FlexGround.flag);
//}

unsigned int Input_GetMp3Status(void)
{
    return 1;
}
unsigned int Input_PowerCheck(void)
{
    return 1;
}

/*
bool Input_GetWalkChange(void)
{
  return(bWalkChange);
}

void Input_ClearWalkChange(void)
{
  bWalkChange = 0;
}
*/
unsigned int Input_GetWalkPosition(void)
{
    if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT)
        return WALK_MOTOR_AT_BOTTOM;
    if(Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
        return WALK_MOTOR_AT_TOP;
    else
        return WALK_MOTOR_AT_MID;
}

unsigned int Input_GetReady(void)
{
    if(bInputReady) return 1;
    return 0;
} 

//��ȡ�����綯�׵��������λ��
unsigned int Input_GetBackPosition(void)
{
    return nCurBackLocate;
}
void Input_SetBackMotorPosition(unsigned int Position)
{
    nCurBackLocate = Position;
}
                                      
void BackMotor_Set_Location(unsigned short locate)
{
   nCurBackLocate = locate;
}



 
