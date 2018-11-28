#ifndef __NetCloud_H__
#define __NetCloud_H_

#include "backaction.h"
//#define NETCLOUD_TEST //fww
#define AUTO_NET_CLOUD1 ((uint32_t) 0x00016000UL)
#define AUTO_NET_CLOUD2 ((uint32_t) 0x00018000UL)
#define AUTO_NET_CLOUD3 ((uint32_t) 0x0001A000UL)
#define AUTO_NET_CLOUD4 ((uint32_t) 0x0001C000UL)
#define CLOUD_TO_DATA 32
/*
typedef struct Walk_Knead_Knock_Motor_Struct_Auto
{
  //1st byte
  unsigned char nSubFunction ;
  unsigned char nWalkMotorLocateMethod ;
  //2nd byte
  unsigned short nWalkMotorLocateParam;  //长行程
  //3rd byte
  unsigned nKneadMotorState:4 ;
  unsigned nKneadMotorCycles:4 ;
  //4th byte(KNOCK_STOP,KNOCK_RUN_WIDTH,KNOCK_RUN,KNOCK_RUN_STOP,KNOCK_RUN_MUSIC)	


  //Only 4 states for auto mode
  unsigned nKnockMotorState:2 ;
  unsigned nKnockMotorRunTime:6 ;//敲打持续的时间


  //5th byte
  unsigned nKnockMotorStopTime:5 ;//敲打停顿的时间
  //unsigned nAxisMotorPosition ;//敲打停顿的时间
  unsigned nKneadKnockSpeed:3 ;


  unsigned char n3D_MotorState;
  unsigned char n3D_MotorPosition;
  unsigned char n3D_MotorSpeed;
  unsigned char n3D_MotorStopTime;


} WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO ;

*/


WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunctionNetCloud(unsigned int nAddress,unsigned int nCurActionStep);
unsigned int GetnMaxActionStep(unsigned int nAddress);
unsigned int IsNetCloud(unsigned int nAddress);

#endif