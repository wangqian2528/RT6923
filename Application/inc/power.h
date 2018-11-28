#ifndef __POWER_H__
#define __POWER_H__

//��Դ�ܿ���
#define POWER_GENERAL_PORT      gpioPortF//D
#define POWER_GENERAL_BIT       3//10
#define POWER_GENERAL_MODE      gpioModePushPull
//3.3V LDO ��Դʹ��
#define POWER_3V3_PORT          gpioPortC
#define POWER_3V3_BIT           15// 11
#define POWER_3V3_MODE          gpioModePushPull
//AMP ��Դʹ��
#define POWER_5V_PORT           gpioPortE//C
#define POWER_5V_BIT            2//10
#define POWER_5V_MODE           gpioModePushPull

#define GENERAL_POWER_ON   1
#define GENERAL_POWER_OFF  0
#define GENERAL_3V3_ON   1
#define GENERAL_3V3_OFF  0
#define GENERAL_5V_ON   1
#define GENERAL_5V_OFF  0

void Power_Initial_IO(void);

void Power_On(void);
void Power_Off(void);
void Power_3V3_On(void);
void Power_3V3_Off(void);
void Power_5V_On(void);

unsigned int Power_Get(void);
void Power_All_Off(void);
void Power_All_On(void);

#endif /*__POWER_H__*/
