

#include "NetCloud.h"


/*
#define AUTO_NET_CLOUD1 ((uint32_t) 0x00016000UL)
#define AUTO_NET_CLOUD2 ((uint32_t) 0x00018000UL)
#define AUTO_NET_CLOUD3 ((uint32_t) 0x0001A000UL)
#define AUTO_NET_CLOUD4 ((uint32_t) 0x0001C000UL)
#define CLOUD_TO_DATA 32*/
WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunctionNetCloud(unsigned int nAddress,unsigned int nCurActionStep)
{
  WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO *p;
  p=(WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO *)(nAddress+nCurActionStep*16+CLOUD_TO_DATA);
  return(*p);
}

unsigned int GetnMaxActionStep(unsigned int nAddress)
{
  unsigned int *p;
  p=(unsigned int *)(nAddress+4);
  return(*p/16);
} 

unsigned int IsNetCloud(unsigned int nAddress)
{
  unsigned int *p;
  p=(unsigned int *)(nAddress);
  if(*p==0||*p==0xffffffff)
    return(0);
  else
    return(1);
}

