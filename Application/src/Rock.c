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
#define bKeyBackPadUp 				GlobalFlags7.bD0  //靠背起落电动缸  起标志，在按键处理里面设置
#define bKeyBackPadDown 			GlobalFlags7.bD1  //靠背起落电动缸  起标志，在按键处理里面设置
extern  BITS GlobalFlags8 ;
#define bKeyLegPadUp 				GlobalFlags8.bD0  //小腿起落电动缸  起标志，在按键处理里面设置
#define bKeyLegPadDown 				GlobalFlags8.bD1  //小腿起落电动缸落标志，在按键处理里面设置
extern  BITS GlobalFlags1 ;
#define bLegPadLinkage 			GlobalFlags1.bD7          //连动起落电动缸标志，在按键处理里面设置
extern  BITS GlobalFlags3 ;
#define bShoulderOK	                GlobalFlags3.bD0          //肩部标志，体形检测1完成

extern  unsigned int w_PresetTime;
extern bool RockStartTimeFlag;
__no_init BYTE nRockModeEnterExit;//查询软件，查询此状态，退出状态（ExitRock），进入状态（EnterRock）则进入摇摆处理
bool bRockEnable;//摇摆使能
//bool isRocking = false;//摇摆状态，只提供backpad.c用
__no_init BYTE RockStep; //摇摆步骤
extern BYTE nBackMainRunMode,nBackSubRunMode ;

UINT16  nRockInterrupTime; //换向 间隔时间（程序为1秒）SetMassagePosition

/***************************************************
功能说明：摇椅模式起始位置控制函数
参数：无
返回值：动作完成返回1，未完成返回0
其他说明：
****************************************************/
bool RockBackLegProcess(void)
{
    UINT w_LegPosition;
    UINT r_BackLocation;
    
    bool bBackpositiondone,bLegpositiondone;
    
    //采取靠背 小腿位置
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

        //比较靠背位置
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
            //比较小腿位置
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
   
    //结论
    if((bLegpositiondone == true)&&(bBackpositiondone == true))
    {
        return true;  //到达了预定的位置
    }
    else
    {
        return false;  //未到达预定的位置
    }
    
}
/***************************************************
函数功能          :摇摆功能
                   1.关闭靠背小腿动作
                   2.开启关闭使能
输入              :  有，输入摇摆开启 或关闭
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华

****************************************************/
void RockFunctionEnable(bool Enable)
{
    bKeyBackPadUp = FALSE;
    bKeyBackPadDown = FALSE;
    bKeyLegPadUp = FALSE;
    bKeyLegPadDown = FALSE;
    // 1-5：函数或过程处理语句的开始、结构的定义及循环、判断等内部语句中的代码都要采用缩进风格，
    // case语句下的情况处理语句也要遵从语句缩进要求
    switch(Enable)
    {
    case RockDisable://关闭
        SetbRockEnable(FALSE);//bRockEnable = false;
        //SetRockingEnable(Enable);
        break;
    case RockEnable://打开
        bLegPadLinkage = TRUE ;
        nRockModeEnterExit = EnterRock;
        SetbRockEnable(TRUE);
        SetRockStep(StartRock);//一旦刚进入该模式就开始尝试下躺
        break;
    default ://否，关闭
        SetbRockEnable(FALSE);//bRockEnable = false;
        break;
    }
}
/*
相对独立的程序块之间、变量说明之后必须加空行。
*/
/***************************************************
函数功能          :摇摆控制发出函数 
                   时间到，开启摇摆
                   时间到，关闭摇摆
输入              :  无
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华

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
                if(RockStartTimeFlag == TRUE)//按下自动模式2体型检测完成后获取摇椅的开始时间
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
                FlexMotorSetDisable();//摇椅中禁止自动找脚
            }
        }
    }
    //没有在摇摆模式时就直接退出
    if(nRockModeEnterExit == ExitRock) return;
    
    
    //获取位置
    if(Input_GetBackDownSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(BACK_MOTOR_MAX_LOCATION);
    }
    if(Input_GetBackUpSwitch() == REACH_BACK_LIMIT)
    {
        BackMotor_Set_Location(0);
    }
    rock_BackLocation = Input_GetBackPosition();  
    
    //开始分步动作
    if( GetbRockEnable())
    {
        switch(RockStep)
        {
        case StartRock://停1s
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep ++;
            }
            
            break;    
        case LiePreDown://下躺到下位置
            if(RockBackLegProcess() == true)
            {
                RockStep++;
            }
            nRockInterrupTime = 0;
            break;
        case LieDownFlexSetEnable://启动自动找脚
            FlexMotorSetEnable();  
            RockStep ++;
            break;
        case LieDownFlexOver:   //自动找脚完成
            if(FlexMotorGetEnable() == false) 
            {
                RockStep ++;
                FlexMotorSetDisable();
            }
            break;
        case LieDownStop://停1s
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep ++;
            }
            FlexMotorSetDisable();
            break; 
        case LieUP://靠背上升到指定位置
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
        case LieUpStop://停1秒
            Back_Flag = BackMotor_Control(STATE_BACK_IDLE) ;
            leg_Flag = LegMotor_Control(STATE_LEG_IDLE) ;
            if( (Back_Flag)&&(leg_Flag) )
            {
                if(nRockInterrupTime >= 10)RockStep++;
            }
            FlexMotorSetDisable();
            break; 
        case LieDown://靠背下躺到下位置
            if(RockBackLegProcess() == true)
            {
                RockStep++;
            }
            nRockInterrupTime = 0;
            break;
        default :
            RockStep = LieDownStop;//到步骤4，在下位置停1s
            break;
        }
    }
    else
    {
        nRockModeEnterExit = ExitRock;
    }
}

/***************************************************
函数功能          :获取摇摆使能
输入              :  无
输出              :  有，使能

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
bool GetbRockEnable(void)
{
    return bRockEnable;
}
/***************************************************
函数功能          :设置摇摆使能
输入              :  有，使能
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
void SetbRockEnable(bool enable)
{
    bRockEnable = enable;
}
/***************************************************
函数功能          :设置摇摆步骤，大多用于初始化变量
输入              :  有，步骤
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
void SetRockStep(BYTE step)
{
    RockStep = step;
}
/***************************************************
函数功能          :获取摇摆进入 或退出
输入              :  无
输出              :  有，进入 或退出

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
BYTE GetnRockModeEnterExit(void)
{
    return nRockModeEnterExit;
}
/***************************************************
函数功能          :设置摇摇摆进入 或退出
输入              :  有，入 或退出
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
void SetnRockModeEnterExit(BYTE nRockMode)
{
    nRockModeEnterExit = nRockMode;
}
/***************************************************
函数功能          :间隔时间累计处理
输入              :  无
输出              :  无

其他说明          : 
修改时间          :20160908
修改人            :王贵华
****************************************************/
void Rock_100ms_Count(void)
{
    nRockInterrupTime++;
}
/*void SetRockingEnable(bool flag)
{
  isRocking = flag;
}*/






