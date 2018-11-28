#ifndef __MASSAGE_STATUS_H__
#define __MASSAGE_STATUS_H__

#define CHAIR_STATE_IDLE			0  //����״̬
#define CHAIR_STATE_SETTLE			1  //��λ״̬����ʾ�ղ��У�
#define CHAIR_STATE_WAIT_COMMAND	        2  //�ȴ�������,��ص�ָʾ����˸
#define CHAIR_STATE_RUN				3  //����״̬
#define CHAIR_STATE_WAIT_MEMORY		        4  
#define CHAIR_STATE_PROBLEM			5  //����ģʽ
#define CHAIR_STATE_ENGINEERING                 6  //����ģʽ
#define CHAIR_STATE_SLEEP			7  //���ӹ�����˯��ģʽ����ʱҪ���������С��0.5W


	#define CHAIR_STATE_DEMO                        8
	#define CHAIR_STATE_CALIBRATION                 9
	#define CHAIR_STATE_INITIAL                     10
	#define CHAIR_STATE_UPDATE                      11

#define  CHAIR_STATE_SETTLE_1ST       		   12


#define CHAIR_STATE_ANGLE                         13 //�Ƕȣ���"����-GROTH-CARE"����б



//#ifdef Quick_Resetting   //
	//#define CHAIR_STATE_DEMO                        8
	//#define CHAIR_STATE_CALIBRATION                 9
	//#define CHAIR_STATE_INITIAL                     10
	//#define CHAIR_STATE_UPDATE                      11


//#else    //ֹͣ����YES /NO
  //  #define  CHAIR_STATE_SETTLE_1ST       		   8
	//#define CHAIR_STATE_DEMO                       10
	//#define CHAIR_STATE_CALIBRATION                11
	///#define CHAIR_STATE_INITIAL                    12
	//#define CHAIR_STATE_UPDATE                     13


//#endif






#define MOTOR_STOP_BREAK    0  //���ֹͣ��ɲ��
#define MOTOR_STOP_HZ       1  //���ֹͣ���������˿�Ϊ����
#define MOTOR_RUN           2  //�������
#define MOTOR_STOP_HZ_TIME  10  //��λ10ms 

#define POWER_KEY_RESET   0
#define RUN_OVER_RESET    1
         
extern unsigned char nChairRunState;



#endif /*__MASSAGE_STATUS_H__*/