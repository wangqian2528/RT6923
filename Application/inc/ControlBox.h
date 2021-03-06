#include "MassageStatus.h"
#define SOI                             0XF0
#define EOI                             0XF1
#define CONTROL_CODE                    0X82

#define NORMAL_CTRL                   CONTROL_CODE
#define ENGGER_CTRL                   0xBD

#define PROGARM_CTRL                   0xA5


#define H10_KEY_NONE			        0x7f
//Power Switch Key
#define H10_KEY_POWER_SWITCH			0x01
#define H10_KEY_MENU                    0x02


#define H10_KEY_ANGLE_CONFIRM                           0x77a//0x0a
#define H10_KEY_ANGLE_CANCLE                            0x0b0

#define H10_KEY_TAPPING_ONOFF                           0X0A

//ZONE1:自动程序键值
#define H10_KEY_CHAIR_AUTO_0	      0x10  //运行恢复
#define H10_KEY_CHAIR_AUTO_1	      0x11  //EXTEND
#define H10_KEY_CHAIR_AUTO_2	      0x12  //RELEX
#define H10_KEY_CHAIR_AUTO_3	      0x13  //refresh
#define H10_KEY_CHAIR_AUTO_4          0x14  //上半身自动
#define H10_KEY_CHAIR_AUTO_5          0x15  //下半身自动
#define H10_KEY_CHAIR_UP_BACK         H10_KEY_CHAIR_AUTO_4 
#define H10_KEY_CHAIR_DOWN_BACK	      H10_KEY_CHAIR_AUTO_5
#define H10_KEY_NECK_SHOULDER_AUTO    H10_KEY_CHAIR_UP_BACK
#define H10_KEY_BACK_WAIST_AUTO       H10_KEY_CHAIR_DOWN_BACK

#define H10_KEY_CHAIR_AUTO_6          0x16
#define H10_KEY_CHAIR_AUTO_7          0x17
#define H10_KEY_CHAIR_AUTO_8          0x18
/***********************************************/
#define H10_KEY_MEMORYA_OUT 0x170
#define H10_KEY_MEMORYA_IN  0x160
#define H10_KEY_MEMORYB_OUT 0x19
#define H10_KEY_MEMORYB_IN  0x180
/***********************************************/
//#define  H10_KEY_CHAIR_AUTO_EXAMINEE                   0X16
//#define H10_KEY_CHAIR_AUTO_HIGH_UP                     0X17
//
//#define H10_KEY_CHAIR_AUTO_GOLFER                     0X18

//#define H10_KEY_CHAIR_AUTO_9				0x19 //care 

//#define H10_KEY_CHAIR_AUTO_10                           0x1A //growth

#define H10_KEY_CHAIR_QUICK_FULL			0x0606 //quick full
#define H10_KEY_CHAIR_QUICK_SHOULDER	                0x86//0x07 //quick shoulder
#define H10_KEY_CHAIR_QUICK_WAIST		        0x82//0x08 //quick back
#define H10_KEY_CHAIR_QUICK_LEG				0x84//0x09 //quick leg


#define H10_KEY_STRETCH_VIGOR1                   0x0B
#define H10_KEY_STRETCH_VIGOR2                   0x0C
#define H10_KEY_STRETCH_VIGOR3                   0x0D

//ZONE2:手动程序键值
/**********************************************************/
#define H10_KEY_KNEAD_CLOCK                             0x04
#define H10_KEY_KNEAD_ANTICLOCK                         0x05
#define H10_KEY_KNEAD					0x20 
#define H10_KEY_KNOCK					0x21
#define H10_KEY_PRESS					0x22
#define H10_KEY_SOFT_KNOCK				0x23
#define H10_KEY_WAVELET					0x24 

#define H10_KEY_MANUAL					0x25 
#define H10_KEY_MUSIC                                   0x26
#define H10_KEY_HEAT_ON  				0x270 //背部加热开,未使用
#define H10_KEY_HEAT  				        0x27 //背部加热开

#define H10_KEY_LOCATE_PART			        0x28 //按摩部位局部
#define H10_KEY_LOCATE_POINT				0x29 //按摩部位定点
#define H10_KEY_LOCATE_FULL				0x2A //按摩部位全程

#define H10_KEY_WIDTH_MIN				0x2B
#define H10_KEY_WIDTH_MED				0x2C
#define H10_KEY_WIDTH_MAX				0x2D

#define H10_KEY_SPEED_1                                 0x2E //按摩速度1
#define H10_KEY_SPEED_2                                 0x2F //按摩速度2
#define H10_KEY_SPEED_3                                 0x30 //按摩速度3
#define H10_KEY_SPEED_4                                 0x31 //按摩速度4
#define H10_KEY_SPEED_5                                 0x32 //按摩速度5
#define H10_KEY_SPEED_6                                 0x33 //按摩速度6

#define H10_KEY_WHEEL_SPEED_SLOW                        0x34 //滚轮速度慢
#define H10_KEY_WHEEL_SPEED_MED                         0x35 //滚轮速度中
#define H10_KEY_WHEEL_SPEED_FAST                        0x36 //滚轮速度快
#define H10_KEY_WHEEL_SPEED_OFF                         0x37 //滚轮关

#define H10_KEY_OZON_SWITCH                             0x38


#define H10_KEY_HEAT_MIN				0x3C
#define H10_KEY_HEAT_MED				0x3D
#define H10_KEY_HEAT_MAX				0x3E


//ZONE3:气囊设置程序键值
#define H10_KEY_AIRBAG_LEG			        0x40  //腿脚
#define H10_KEY_AIRBAG_ARM			        0x41  //臂肩
#define H10_KEY_AIRBAG_WAIST			        0x42  //背腰
#define H10_KEY_AIRBAG_BUTTOCKS			        0x43  //臀部
#define H10_KEY_AIRBAG_AUTO			        0x44  //全身自动

#define H10_KEY_AIRBAG_STRENGTH_1                       0x45  //气囊力度1
#define H10_KEY_AIRBAG_STRENGTH_WEAK                    0x45  //气囊力度弱
#define H10_KEY_AIRBAG_STRENGTH_2                       0x46  //气囊力度2
#define H10_KEY_AIRBAG_STRENGTH_3                       0x47  //气囊力度3
#define H10_KEY_AIRBAG_STRENGTH_MIDDLE                  0x47  //气囊力度中
#define H10_KEY_AIRBAG_STRENGTH_4                       0x48  //气囊力度4
#define H10_KEY_AIRBAG_STRENGTH_5                       0x49  //气囊力度5
#define H10_KEY_AIRBAG_STRENGTH_STRONG                  0x49  //气囊力度强
#define H10_KEY_AIRBAG_STRENGTH_OFF                     0x4A  //气囊关

//ZONE4:设置程序键值
#define H10_KEY_WORK_TIME_10MIN                         0x50  //按摩10分钟
#define H10_KEY_WORK_TIME_20MIN                         0x51  //按摩20分钟
#define H10_KEY_WORK_TIME_30MIN                         0x52  //按摩30分钟

#define H10_KEY_BACK_LIGHT_SLOW                         0x55  //背光强度弱 未使用
#define H10_KEY_BACK_LIGHT_MED                          0x56  //背光强度中 未使用
#define H10_KEY_BACK_LIGHT_HIGH                         0x57  //背光强度强 未使用

//ZONE5:机芯位置控制键值
#define H10_KEY_WALK_UP_START				0x60
#define H10_KEY_WALK_UP_STOP				0x61
#define H10_KEY_WALK_DOWN_START				0x62
#define H10_KEY_WALK_DOWN_STOP				0x63

//ZONE6:靠背电动缸控制键值
#define H10_KEY_BACKPAD_UP_START			0x64
#define H10_KEY_BACKPAD_UP_STOP				0x65
#define H10_KEY_BACKPAD_DOWN_START			0x66
#define H10_KEY_BACKPAD_DOWN_STOP			0x67

//ZONE7:小腿电动缸控制键值
#define H10_KEY_LEGPAD_UP_START				0x68
#define H10_KEY_LEGPAD_UP_STOP				0x69
#define H10_KEY_LEGPAD_DOWN_START			0x6A
#define H10_KEY_LEGPAD_DOWN_STOP			0x6B

#define H10_KEY_LEGPAD_EXTEND_START                     0x6C
#define H10_KEY_LEGPAD_EXTEND_STOP                      0x6D
#define H10_KEY_LEGPAD_CONTRACT_START                   0x6E
#define H10_KEY_LEGPAD_CONTRACT_STOP                    0x6F

#define H10_KEY_3DMODE_1                                0x39 
#define H10_KEY_3DMODE_2                                0x3A 
#define H10_KEY_3DMODE_3                                0x3B 
#define H10_KEY_3DMODE                                  0x13D//0x3B 
#define H10_KEY_3DSPEED_1                               0x58 //3D手法1
#define H10_KEY_3DSPEED_2                               0x59 //3D手法2
#define H10_KEY_3DSPEED_3                               0x5A //3D手法3
#define H10_KEY_3DSPEED_4                               0x5B //3D手法1
#define H10_KEY_3DSPEED_5                               0x5C //3D手法2

#define H10_KEY_3D_STRENGTH                             0x57 //3D手法2
#define H10_KEY_VOICE_ON                                0x5D //语音模块控制音乐关闭
#define H10_KEY_VOICE_OFF                               0x5E //语音模块控制音乐打开
#define H10_KEY_RESET                                   0x7E

//ZONE8:零重力键值
#define H10_KEY_ZERO_START                              0x70
#define H10_KEY_ZERO_1	                                0x07//0x81//0x71
#define H10_KEY_ZERO_2	                                0x08//0x82//0x72
#define H10_KEY_ZERO_3	                                0x83//0x73
#define H10_KEY_ZERO_RESET	                            0x09//0x74

#define H10_KEY_WIDTH_INCREASE                          0x90
#define H10_KEY_WIDTH_DECREASE                          0x91
#define H10_KEY_BLUETOOTH_POWER_SWITCH  	        0x53

/************************************扶手键值开始*******************************/
#define H10_KEY_HANDRAIL_OUT_START			0X71
#define H10_KEY_HANDRAIL_OUT_STOP		        0x72
#define H10_KEY_HANDRAIL_IN_START			0x73
#define H10_KEY_HANDRAIL_IN_STOP			0x74
#define H10_KEY_HANDRAIL_RESET          		0x85
/************************************扶手键值结束*******************************/

//语言按键值
#define H10_KEY_LANGUAGE_CHINESE                        0x0E//0x0D
#define H10_KEY_LANGUAGE_ENGLISH                        0x0F
#define H10_KEY_LANGUAGE_ELSE                           0x06
//LED灯开关键
#define H10_KEY_LED_SWITCH                              0X3F
/************************************************/
#define nMaunalSubMode_KNEAD		0
#define nMaunalSubMode_KNOCK		3
#define nMaunalSubMode_WAVELET		2
#define nMaunalSubMode_SOFT_KNOCK	1
#define nMaunalSubMode_PRESS		4
#define nMaunalSubMode_MUSIC		5

#define nMaunalSubMode_3DMODE_1         6
#define nMaunalSubMode_3DMODE_2         7
#define nMaunalSubMode_3DMODE_3         8

/************************************************/

#define LED_OFF			        0 
#define LED_ON			        1

#define BUZZER_MODE_OFF			0
#define BUZZER_MODE_SLOW		1
#define BUZZER_MODE_FAST		2
#define BUZZER_MODE_ONETIME		3 // ONE TIME BEEP
#define BUZZER_MODE_TWOTIME		4

#define ENG_CMD_RESET                   1
#define ENG_CMD_DEC_STRENGTH            2
#define ENG_CMD_ADD_STRENGTH            3
#define ENG_CMD_SLIDE                   4
#define ENG_CMD_REST_SLEEP              6
//#define ENG_CMD_ARM                     4//7
#define VOICE_KEY_MASK                          0x80

#define H10_KEY_LEG_WHEEL_OFF			0x75        //小腿滚轮关闭
#define H10_KEY_LEG_WHEEL_1			0x87//0x76   //小腿滚轮上到中
#define H10_KEY_LEG_WHEEL_2			0x77   //小腿滚轮中到下
#define H10_KEY_LEG_WHEEL_3             	0x78   //小腿滚轮上到下


#define H10_KEY_MUSIC_LAST                              0x7A
#define H10_KEY_MUSIC_NEXT                              0x7B
#define H10_KEY_MUSIC_ADD                              0x7c
#define H10_KEY_MUSIC_MINUS                            0x7d
#define H10_KEY_SWAY_ONOFF  				0x76 //背部摇摆开关

//--------------------------------------云养程序区

//#define H10_KEY_CHAIR_AUTO_NETCLOUD_1			        0x71//fww
//#define H10_KEY_CHAIR_AUTO_NETCLOUD_2			        0x72
//#define H10_KEY_CHAIR_AUTO_NETCLOUD_3			        0x73
//#define H10_KEY_CHAIR_AUTO_NETCLOUD_4			        0x74

//-----------------------------------------------------------
#define DIY_Program_Key  	        0x80   //0B10XX XXXX 未使用
#define DIY_KNEAD	0
#define DIY_PRESS       1
#define DIY_KNOCK       2
#define DIY_WAVELET     3

#define DIY_SHOULDER	0
#define DIY_BACK       1
#define DIY_WAIST       2
#define DIY_BUTTOCKS     3

#define DIY_SLOW    0

#define DIY_FAST   1

#define  DIY_HALF_PARTIAL_DIFF     25

#define  DIY_HALF_PARTIAL_DIFF_2     40

#define  DIY_HALF_PARTIAL_DIFF_3     45
//------------------------------------------------------










