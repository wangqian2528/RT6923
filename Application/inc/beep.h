
#define C_BEEP_STOP     0
#define C_BEEP_SLOW     1
#define C_BEEP_FAST     2
#define C_BEEP_ONETIME  3
#define C_BEEP_TWOTIME  4

/*
#define BUZZER_MODE_OFF			0
#define BUZZER_MODE_SLOW		1   //�綯��������ת��ʾ��
#define BUZZER_MODE_FAST		2   //�綯�׵�λ����ʾ��
#define BUZZER_MODE_ONETIME		3   //������Ч��ʾ��
#define BUZZER_MODE_TWOTIME		4   //������Ч��ʾ�� 
*/

extern unsigned char by_BeepStatus;
void Beep_Set(unsigned char action);
unsigned char Beep_Get_Status(void);