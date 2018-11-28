#include "EFM32_def.h"
#include "EFM32_types.h"
#include "efm32.h"
#include "em_chip.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "MassageStatus.h"
#include "ZeroMotor.h"
#include "AxisMotor.h"
#include "Flex_Uart.h"
#include "input.h"
#include "problem.h"     

#define _3D_MAX_RUN_TIME    10
#define FLEX_MAX_RUN_TIME   20

static bool bFlag10ms;
static int _3D_ForwardCount;
static int _3D_BackCount;
static int flexOutCount;
static int flexInCount;
     
bool b3DOverTime,bFlexOverTime,bWalkSwitchFail;

void Problem_10ms_Int(void)
{
  bFlag10ms = true;
}
  
void Problem_Proce(void)
{
    if(!bFlag10ms) return;//���ƺ���ÿ10msִ��һ��
    bFlag10ms = false;

    if(AxisMotor_IsRun())//���ڱ���3D�������������ʱ�䳬���������ʱ�䣨δʹ�ã�
    {
        if(AxisMotor_GetDirection() ==  AXIS_MOTOR_GO_FORWARD)
        {
            _3D_ForwardCount++;
            _3D_BackCount = 0;
        }
        else
        {
            _3D_BackCount++;
            _3D_ForwardCount = 0;
        } 
        if(_3D_ForwardCount > _3D_MAX_RUN_TIME || _3D_BackCount > _3D_MAX_RUN_TIME)
        {
            _3D_ForwardCount = 0;
            _3D_BackCount = 0;
            b3DOverTime = true; 
        }
    }
    else
    {
        _3D_ForwardCount = 0;
        _3D_BackCount = 0;
        // b3DOverTime = false; 
    }

    if(FlexPower_Get() == FLEX_POWER_ON)//����С�����������δʹ�ã�
    {
        if(Flex_GetDirection() == 1)
        {
            flexOutCount++;
            flexInCount = 0;
        }
        else
        {
            flexInCount++;
            flexOutCount = 0;
        } 
        if(flexOutCount > FLEX_MAX_RUN_TIME || flexInCount > FLEX_MAX_RUN_TIME)
        {
            flexOutCount = 0;
            flexInCount = 0;
            bFlexOverTime = true; 
        }
    }
    else
    {
        flexOutCount = 0;
        flexInCount = 0;
    }
    
    if(Input_GetWalkDownSwitch() == REACH_WALK_LIMIT && Input_GetWalkUpSwitch() == REACH_WALK_LIMIT)
    { //����������λͬʱ��Чʱֹͣ3D�����������3D������ƺ�����
        bWalkSwitchFail = true;
    }
    else
    {
        bWalkSwitchFail = false;
    } 
}
bool Problem_GetWalkSwitchFault(void)
{
  return(bWalkSwitchFail);
}

bool Problem_Get3DFault(void)
{
  return(b3DOverTime);
}
bool Problem_GetFlexFault(void)
{
  return(bFlexOverTime);
}
