#include "Rock.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "efm32_types.h"
#include "efm32_def.h"
#include "input.h"
#include "BackPad.h"
#include "LegMotor.h"
#include "main.h"
#include "Data_Cul.h"
#include "backaction.h"
#include "Flex_Uart.h"
#include "SlideMotor.h"

extern BITS GlobalFlags7 ;
#define bKeyBackPadUp 				GlobalFlags7.bD0  //��������綯��  ���־���ڰ���������������
#define bKeyBackPadDown 			GlobalFlags7.bD1  //��������綯��  ���־���ڰ���������������
extern  BITS GlobalFlags8 ;
#define bKeyLegPadUp 				GlobalFlags8.bD0  //С������綯��  ���־���ڰ���������������
#define bKeyLegPadDown 				GlobalFlags8.bD1  //С������綯�����־���ڰ���������������
extern  BITS GlobalFlags1 ;
#define bLegPadLinkage 			GlobalFlags1.bD7          //��������綯�ױ�־���ڰ���������������
extern  BITS GlobalFlags3 ;
#define bShoulderOK	                GlobalFlags3.bD0          //�粿��־�����μ��1���

extern  unsigned int w_PresetTime;
extern bool RockStartTimeFlag;
__no_init BYTE nRockModeEnterExit;//��ѯ�������ѯ��״̬���˳�״̬��ExitRock��������״̬��EnterRock�������ҡ�ڴ���
bool bRockEnable;//ҡ��ʹ��
//bool isRocking = false;//ҡ��״̬��ֻ�ṩbackpad.c��
__no_init BYTE RockStep; //ҡ�ڲ���
extern BYTE nBackMainRunMode,nBackSubRunMode ;

UINT16  nRockInterrupTime; //���� ���ʱ�䣨����Ϊ1�룩SetMassagePosition

/***************************************************
����˵����ҡ��ģʽ��ʼλ�ÿ��ƺ���
��������
����ֵ��������ɷ���1��δ��ɷ���0
����˵����
****************************************************/
bool RockBackLegProcess(void)
{
    UINT w_LegPosition;
    UINT r_BackLocation;
    
    bool bBackpositiondone,bLegpositiondone;
    
    //��ȡ���� С��λ��
    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(BACK_MOTOR_MAX_LOCATION);
    }
    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(0);
    }
    w_LegPosition = LegMotor_Get_Position();
    r_BackLocation= Input_GetBackPosition();
    if( GetbRockEnable() == FALSE) 
    {
        return 1;
    }

        //�ȽϿ���λ��
        if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
        {
            bKeyBackPadUp = FALSE;
            bKeyBackPadDown = FALSE;
            bBackpositiondone = true;
        }
        else if(r_BackLocation <= MASSAGE_BACK_ROCK_LOCATION)
        {
            bKeyBackPadUp = FALSE;
            bKeyBackPadDown = TRUE;
            bBackpositiondone = false;
        }
        else if(r_BackLocation >= (MASSAGE_BACK_ROCK_LOCATION + 70))
        {
            bKeyBackPadUp = TRUE;
            bKeyBackPadDown = FALSE;
            bBackpositiondone = false;
        }
        else 
        {
            bKeyBackPadUp = FALSE;
            bKeyBackPadDown = FALSE;
            bBackpositiondone = true;
        }
        
        if(Input_GetSlideForwardSwitch() == REACH_SLIDE_LIMIT)
        {
            //�Ƚ�С��λ��
            if(Input_GetLegUpSwitch() == REACH_LEG_LIMIT)
            {
                bKeyLegPadUp = FALSE;
                bKeyLegPadDown = FALSE;
                bLegpositiondone = true;
            }
            if(w_LegPosition <= MASSAGE_LEG_ROCK_POSITION)
            {
                bKeyLegPadUp = TRUE;
                bKeyLegPadDown = FALSE;
                bLegPadLinkage = FALSE;
                bLegpositiondone = false;
            }
            else if(w_LegPosition >= MASSAGE_LEG_ROCK_POSITION + MASSAGE_DIFFERENT_POSITION)
            {
                bKeyLegPadUp = FALSE;
                bKeyLegPadDown = TRUE;
                bLegPadLinkage = FALSE;
                bLegpositiondone = false;
            }
            else
            {
                bKeyLegPadUp = FALSE;
                bKeyLegPadDown = FALSE;
                bLegpositiondone = true;
            }
        }
   
    //����
    if((bLegpositiondone == true)&&(bBackpositiondone == true))
    {
        return true;  //������Ԥ����λ��
    }
    else
    {
        return false;  //δ����Ԥ����λ��
    }
    
}
/***************************************************
��������          :ҡ�ڹ���
                   1.�رտ���С�ȶ���
                   2.�����ر�ʹ��
����              :  �У�����ҡ�ڿ��� ��ر�
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����

****************************************************/
void RockFunctionEnable(bool Enable)
{
    bKeyBackPadUp = FALSE;
    bKeyBackPadDown = FALSE;
    bKeyLegPadUp = FALSE;
    bKeyLegPadDown = FALSE;
    // 1-5����������̴������Ŀ�ʼ���ṹ�Ķ��弰ѭ�����жϵ��ڲ�����еĴ��붼Ҫ�����������
    // case����µ�����������ҲҪ����������Ҫ��
    switch(Enable)
    {
    case RockDisable://�ر�
        SetbRockEnable(FALSE);//bRockEnable = false;
        //SetRockingEnable(Enable);
        break;
    case RockEnable://��
        bLegPadLinkage = TRUE ;
        nRockModeEnterExit = EnterRock;
        SetbRockEnable(TRUE);
        SetRockStep(StartRock);//һ���ս����ģʽ�Ϳ�ʼ��������
        break;
    default ://�񣬹ر�
        SetbRockEnable(FALSE);//bRockEnable = false;
        break;
    }
}
/*
��Զ����ĳ����֮�䡢����˵��֮�����ӿ��С�
*/
/***************************************************
��������          :ҡ�ڿ��Ʒ������� 
                   ʱ�䵽������ҡ��
                   ʱ�䵽���ر�ҡ��
����              :  ��
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����

****************************************************/
UINT RockStartTime;
void RockControl(void)
{
    UINT rock_BackLocation;  
    BYTE leg_Flag,Back_Flag;//,SlideFlag;
    UINT CurTime = Data_Get_Time();

    if((nBackMainRunMode == BACK_MAIN_MODE_AUTO) &&
       (nBackSubRunMode == BACK_SUB_MODE_AUTO_2))
    {
        if(bRockEnable == false)
        {
            if(bShoulderOK == 1)
            {
                if(RockStartTimeFlag == TRUE)//�����Զ�ģʽ2���ͼ����ɺ��ȡҡ�εĿ�ʼʱ��
                {
                    RockStartTimeFlag = FALSE;
                    RockStartTime = Data_Get_Time();
                }
                if(CurTime == RockStartTime)
                {
                    if(RockStartTime == RockStartTime%6)
                    {
                       RockFunctionEnable(true);
                    }
                    else
                    {
                       RockFunctionEnable(true);
                       RockStartTime -= 6;
                    }
                }
            } 
        }
        else
        {
            if((CurTime == RockStartTime+1))
            {
                RockFunctionEnable(false);  
                SetMassagePosition(MASSAGE_OPTIMAL_POSITION);  
                FlexMotorSetDisable();//ҡ���н�ֹ�Զ��ҽ�
            }
        }
    }
    //û����ҡ��ģʽʱ��ֱ���˳�
    if(nRockModeEnterExit == ExitRock) return;
    
    
    //��ȡλ��
    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(BACK_MOTOR_MAX_LOCATION);
    }
    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(0);
    }
    rock_BackLocation = Input_GetBackPosition();  
    
    //��ʼ�ֲ�����
    if( GetbRockEnable())
    {
        switch(RockStep)
        {
        case StartRock://ͣ1s
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep ++;
            }
            
            break;    
        case LiePreDown://���ɵ���λ��
            if(RockBackLegProcess() == true)
            {
                RockStep++;
            }
            nRockInterrupTime = 0;
            break;
        case LieDownFlexSetEnable://�����Զ��ҽ�
            FlexMotorSetEnable();  
            RockStep ++;
            break;
        case LieDownFlexOver:   //�Զ��ҽ����
            if(FlexMotorGetEnable() == false) 
            {
                RockStep ++;
                FlexMotorSetDisable();
            }
            break;
        case LieDownStop://ͣ1s
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep ++;
            }
            FlexMotorSetDisable();
            break; 
        case LieUP://����������ָ��λ��
            if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
            {
                bKeyBackPadUp = FALSE;
                bKeyBackPadDown = FALSE;
                RockStep++;
            }
            else
            {
                if(rock_BackLocation > MASSAGE_BACK_OPTIMAL_LOCATION)
                {
                    bKeyBackPadUp = TRUE;
                    bKeyBackPadDown = FALSE;
                }
                else
                {
                    bKeyBackPadUp = FALSE;
                    bKeyBackPadDown = FALSE;
                    RockStep++;
                }       
            }
            nRockInterrupTime = 0;
            break;
        case LieUpStop://ͣ1��
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep++;
            }
            FlexMotorSetDisable();
            break; 
        case LieDown://�������ɵ���λ��
            if(RockBackLegProcess() == true)
            {
                RockStep++;
            }
            nRockInterrupTime = 0;
            break;
        default :
            RockStep = LieDownStop;//������4������λ��ͣ1s
            break;
        }
    }
    else
    {
        nRockModeEnterExit = ExitRock;
    }
}

/***************************************************
��������          :��ȡҡ��ʹ��
����              :  ��
���              :  �У�ʹ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
bool GetbRockEnable(void)
{
    return bRockEnable;
}
/***************************************************
��������          :����ҡ��ʹ��
����              :  �У�ʹ��
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
void SetbRockEnable(bool enable)
{
    bRockEnable = enable;
}
/***************************************************
��������          :����ҡ�ڲ��裬������ڳ�ʼ������
����              :  �У�����
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
void SetRockStep(BYTE step)
{
    RockStep = step;
}
/***************************************************
��������          :��ȡҡ�ڽ��� ���˳�
����              :  ��
���              :  �У����� ���˳�

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
BYTE GetnRockModeEnterExit(void)
{
    return nRockModeEnterExit;
}
/***************************************************
��������          :����ҡҡ�ڽ��� ���˳�
����              :  �У��� ���˳�
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
void SetnRockModeEnterExit(BYTE nRockMode)
{
    nRockModeEnterExit = nRockMode;
}
/***************************************************
��������          :���ʱ���ۼƴ���
����              :  ��
���              :  ��

����˵��          : 
�޸�ʱ��          :20160908
�޸���            :����
****************************************************/
void Rock_100ms_Count(void)
{
    nRockInterrupTime++;
}
/*void SetRockingEnable(bool flag)
{
  isRocking = flag;
}*/






