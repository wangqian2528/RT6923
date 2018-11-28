#ifndef __MASSAGE_STATUS_H__
#define __MASSAGE_STATUS_H__

#define CHAIR_STATE_IDLE			0  //待机状态
#define CHAIR_STATE_SETTLE			1  //回位状态（提示收藏中）
#define CHAIR_STATE_WAIT_COMMAND	        2  //等待按命令,相关的指示灯闪烁
#define CHAIR_STATE_RUN				3  //运行状态
#define CHAIR_STATE_WAIT_MEMORY		        4  
#define CHAIR_STATE_PROBLEM			5  //故障模式
#define CHAIR_STATE_ENGINEERING                 6  //工程模式
#define CHAIR_STATE_SLEEP			7  //椅子工作在睡眠模式，此时要求待机功耗小于0.5W


	#define CHAIR_STATE_DEMO                        8
	#define CHAIR_STATE_CALIBRATION                 9
	#define CHAIR_STATE_INITIAL                     10
	#define CHAIR_STATE_UPDATE                      11

#define  CHAIR_STATE_SETTLE_1ST       		   12


#define CHAIR_STATE_ANGLE                         13 //角度，在"拉伸-GROTH-CARE"不倾斜



//#ifdef Quick_Resetting   //
	//#define CHAIR_STATE_DEMO                        8
	//#define CHAIR_STATE_CALIBRATION                 9
	//#define CHAIR_STATE_INITIAL                     10
	//#define CHAIR_STATE_UPDATE                      11


//#else    //停止出现YES /NO
  //  #define  CHAIR_STATE_SETTLE_1ST       		   8
	//#define CHAIR_STATE_DEMO                       10
	//#define CHAIR_STATE_CALIBRATION                11
	///#define CHAIR_STATE_INITIAL                    12
	//#define CHAIR_STATE_UPDATE                     13


//#endif






#define MOTOR_STOP_BREAK    0  //马达停止并刹车
#define MOTOR_STOP_HZ       1  //马达停止，马达输出端口为高阻
#define MOTOR_RUN           2  //马达运行
#define MOTOR_STOP_HZ_TIME  10  //单位10ms 

#define POWER_KEY_RESET   0
#define RUN_OVER_RESET    1
         
extern unsigned char nChairRunState;



#endif /*__MASSAGE_STATUS_H__*/