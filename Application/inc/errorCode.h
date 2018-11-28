/* ��������б�
1 ��Դ	1	24V��Դ����	24V��Դ��ѹ����36V
	2	24V��Դ����	24V��Դ��ѹ����10V
	3	������Դ����	������ѹ����36V
	4	������Դ����	������ѹ����10V
	5	5V��ѹ����	5V��ѹ����5.5V
	6	5V��ѹ����	5V��ѹ����4.5V
2 �����綯��
        1	�����綯�׼���ź��쳣	�����źſ�·
	2	�����綯�������쳣	����
	3	�����綯�������쳣�򿿱��綯�׼���ź��쳣	������������ʱ�䳬��30��δ�����г̿���
3 С�ȵ綯��
        1	С�ȵ綯�׼���ź��쳣	�����źſ�·
	2	С�ȵ綯�������쳣	����
	3	С�ȵ綯�������쳣��С�ȵ綯�׼���ź��쳣	������������ʱ�䳬��30��δ�����г̿���
4 �������綯��
        1	�������綯�׼���ź��쳣	�����źſ�·
	2	�������綯�������쳣	����
	3	�������綯�������쳣���������綯�׼���ź��쳣	������������ʱ�䳬��30��δ�����г̿���
5 ǰ���綯��
	1	ǰ���綯�׼���ź��쳣	�����źſ�·
	2	ǰ���綯�������쳣	����
	3	ǰ���綯�������쳣��ǰ���綯�׼���ź��쳣	������������ʱ�䳬��30��δ�����г̿���
6 ������
	1	����խ�źż���쳣	�źſ�·
	2	�����������쳣	����
	3	�����������쳣�����խ�źż���쳣	������������ʱ�䳬��10��δ�����г̿���
7 �û����
	1	�û���������쳣	����
8 ���ߵ��
	1	���ߵ���������ź��쳣	���δ���У��������ź�
	2	���ߵ���г̼���ź��쳣	�г̼���źſ�·
	3	���ߵ�������쳣	����
	4	���ߵ�������쳣�����ź��쳣	���ߵ��������������ʱ�䳬��10���������ź�
9 �ŵ׹��ֵ��
	1	�ŵ׹��ֵ�������쳣	����
10 �綯С�ȵ��
	1	�綯С�ȼ���ź��쳣	�źſ�·
	2	�綯С�ȵ�������쳣	����
	3	�綯С�ȵ�������쳣���źż���쳣	������������ʱ�䳬��30��δ�����г̿���
*/


#define ERROR_CODE_NULL        0
//power
#define ERROR_CODE_POWER       1

  #define ERROR_CODE_POWER_MOTOR_HIGHER  1
  #define ERROR_CODE_POWER_MOTOR_LOWER   2
  #define ERROR_CODE_POWER_VALVE_HIGHER  3
  #define ERROR_CODE_POWER_VALVE_LOWER   4
  #define ERROR_CODE_POWER_VCC_HIGHER    5
  #define ERROR_CODE_POWER_VCC_LOWER     6
//backpad
#define ERROR_CODE_BACKPAD     2
  #define ERROR_CODE_BACKPAD_SWITCH     1
  #define ERROR_CODE_BACKPAD_OVERLOAD   2
  #define ERROR_CODE_BACKPAD_TIMEOVER   3
//legpad
#define LEGPAD_ERROR      3
  #define ERROR_CODE_LEGPAD_SWITCH     1
  #define ERROR_CODE_LEGPAD_OVERLOAD   2
  #define ERROR_CODE_LEGPAD_TIMEOVER   3
//zero motor
#define ZEROMOTOR_ERROR   4
  #define ERROR_CODE_ZEROPAD_SWITCH     1
  #define ERROR_CODE_ZEROPAD_OVERLOAD   2
  #define ERROR_CODE_ZEROPAD_TIMEOVER   3
//slide motor
#define SLIDEMOTOR_ERROR  5
  #define ERROR_CODE_SLIDEMOTOR_SWITCH     1
  #define ERROR_CODE_SLIDEMOTOR_OVERLOAD   2
  #define ERROR_CODE_SLIDEMOTOR_TIMEOVER   3
//knead motor
#define KNEADMOTOR_ERROR  6
  #define ERROR_CODE_KNEADMOTOR_SWITCH     1
  #define ERROR_CODE_KNEADMOTOR_OVERLOAD   2
  #define ERROR_CODE_KNEADMOTOR_TIMEOVER   3
//knoc kmotor
#define KNOCKMOTOR_ERROR  7
  #define ERROR_CODE_KNOCKMOTOR_OVERLOAD   2
//walk motor
#define WALKMOTOR_ERROR   8
  #define ERROR_CODE_WALKMOTOR_SWITCH     1
  #define ERROR_CODE_WALKMOTOR_OVERLOAD   2
  #define ERROR_CODE_WALKMOTOR_TIMEOVER   3
//roller motor
#define ROLLERMOTOR_ERROR 9
  #define ERROR_CODE_ROLLERMOTOR_OVERLOAD   2
//flex motor
#define FLEXMOTOR_ERROR   10
  #define ERROR_CODE_FLEXMOTOR_OVERLOAD   2

