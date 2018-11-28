/********************************
ת������ 		��ʾ 
\a 			����(����) 
\b 			���� 
\f 			��ҳ 
\n 			���� 
\r 			�س� 
\t 			ˮƽ�Ʊ� 
\v 			��ֱ�Ʊ� 
\�� 			������ 
\" 			˫���� 
\\ 			����б�� 
\? 			�����ʺ� 
\ooo 		�˽��Ʊ�ʾ��ASCII�ַ� 
\xhhh 		ʮ�����Ʊ�ʾ��ASCII�ַ� 
*********************************/
#define VIBRATION_ON	1
#define VIBRATION_OFF 	0

//nVibDescriptor
#define VIB_STEADY				0 //����ʽ
#define VIB_PULSE				1 //����ʽ(���ʽ)
#define VIB_WAVE				2 //����ʽ
#define VIB_INTERLACE			3 //����ʽ
//nVibTimeMode
#define TIME_MODE_SYSTEM		0
#define TIME_MODE_SELF			1
//nVibStrengthMode
#define STRENGTH_MODE_SYSTEM	0
#define STRENGTH_MODE_SELF		1
//�Զ���ģʽ�������񶯲���
#define TOTAL_AUTO_VIBRATE_ITEMS	3
//ͨ����ģ��(ָ��+�ṹ��ģ��,��Щ��Ƭ����������֧�ִ�ģʽ)
typedef struct Vibration_Struct_Point
{
	//������(����)
	unsigned char nVibDescriptor ;
	//��������
	unsigned char nVibTotalSteps ;
	//�������ָ��
	unsigned char const * pVibAction ;
	//������������ʱ��ģʽ
	//TIME_MODE_SYSTEM:�ɰ���ȷ�����ٶȾ���
	//TIME_MODE_SELF:�������ָ�����ȷ��
	unsigned char nVibTimeMode ;
	//������������ʱ��ָ��,��nVibTimeMode = TIME_MODE_SELFʱ��Ч
	unsigned char const * pVibTime ;
	//������������ģʽ
	//STRENGTH_MODE_SYSTEM:�ɰ���ȷ�������Ⱦ���
	//STRENGTH_MODE_SELF:�������ָ�����ȷ��
	unsigned char nVibStrengthMode ;
	//������������ָ��,��nVibStrengthMode = STRENGTH_MODE_SELFʱ��Ч
	unsigned char const * pVibStrength ;
} VIBRATION_STRUCT_POINT ;

//ͨ����ģ��(�ṹ��������ģ��,��һ�����������࣬��Щ��Ƭ����������֧�ִ�ģʽ)
typedef struct Vibration_Struct_Array
{
	//������(����)
	unsigned char nVibDescriptor ;
	//��������
	unsigned char nVibTotalSteps ;
	//�������
	unsigned char nVibAction ;
	//������������ʱ��ģʽ
	//TIME_MODE_SYSTEM:�ɰ���ȷ�����ٶȾ���
	//TIME_MODE_SELF:�������ֵȷ��
	unsigned char nVibTimeMode ;
	//������������ʱ��,��nVibTimeMode = TIME_MODE_SELFʱ��Ч
	unsigned char nVibTime ;
	//������������ģʽ
	//STRENGTH_MODE_SYSTEM:�ɰ���ȷ�������Ⱦ���
	//STRENGTH_MODE_SELF:�������ֵȷ��
	unsigned char nVibStrengthMode ;
	//������������,��nVibStrengthMode = STRENGTH_MODE_SELFʱ��Ч
	unsigned char nVibStrength ;
} VIBRATION_STRUCT_ARRAY ;

//ͨ����ģ��(һά����ģ��,�нϴ���������࣬���еĵ�Ƭ����������֧�ִ�ģʽ)
//��VIBRATION_STRUCT_ARRAY�ṹ��ÿ��Ԫ�ز�ֳ�һά���飬�ڴ�ʡ��

//ʱ�䵥λ:100ms
const VIBRATION_STRUCT_POINT VibrateAuto[] =
{
	{
		VIB_STEADY,
		12,
		"\x01\x02\x01\x02\x03\x00\x03\x00\x01\x02\x01\x02",
		TIME_MODE_SELF,
		"\x14\x14\x14\x14\xc8\x14\x14\x14\x14\x14\x14\x14",
		STRENGTH_MODE_SYSTEM,
		"\x0"
	},
	{
		VIB_WAVE,
		13,
		"\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03\x03",
		TIME_MODE_SELF,
		"\x0a\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x14\x0a",
		STRENGTH_MODE_SELF,
		"\x00\x03\x06\x09\x0c\x0f\x12\x0f\x0c\x09\x06\x03\x00"
	},
	{
		VIB_PULSE,
		28,
		"\x01\x02\x01\x02\x01\x02\x01\x02\x01\x02\x01\x02\x01\x02\x01\x03\x02\x00\x03\x00\x03\x00\x01\x02\x01\x02\x01\x00",
		TIME_MODE_SELF,
		"\x0a\x05\x0a\x05\x08\x04\x08\x04\x08\x04\x06\x03\x06\x03\x06\x03\x06\x03\x04\x02\x04\x02\x04\x02\x04\x02\x04\x02",
		STRENGTH_MODE_SYSTEM,
		"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	}
} ;

//3 shift strength
//convert to mark ratio

//���²��ֲο�2006/03/16�ʼ�
//��PWM����
#define VIB_PWM_PERIOD				18 //18*2ms=36ms
//���ֻ�����س���
#define MUSIC_AD_LOW_THRESHOLD		10	//���������ֻ���������ֵ,��Ӧ��ѹ0.13V
#define MUSIC_AD_HIGH_THRESHOLD		200 //ȫ�������ޣ���Ӧ��ѹ2.6V
#define MUSIC_VIB_AD_RATIO			4   //
/*
#define MUSIC_AD_LOW_THRESHOLD		10	//���������ֻ���������ֵ,��Ӧ��ѹ0.2V
#define MUSIC_AD_HIGH_THRESHOLD		172 //ȫ�������ޣ���Ӧ��ѹ3.37V
#define MUSIC_VIB_AD_RATIO			9   //
*/
