
#ifndef __ROCK_H__
#define __ROCK_H__

#define bool _Bool
#define RockDisable                   false
#define RockEnable                    true

#define ExitRock                      0//�Ƴ�
#define EnterRock                     1//����
/*
#define StartRock                     0//��ʼŶ
#define LieDown                       1//����
#define LieDownStop                   2//����ͣ
#define LieUP                         3//��
#define LieUpStop                     4//��ͣ
*/

//#define LieStop                   0//����ͣ
#define StartRock                 0//LieStop//��ʼŶ
#define LiePreDown                1

#define LieDownFlexSetEnable      2
#define LieDownFlexOver           3

#define LieDownStop               4//����ͣ
#define LieUP                     5//��
#define LieUpStop                 6//��ͣ
#define LieDown                   7//����SetMassagePosition

#define MASSAGE_BACK_OPTIMAL_LOCATION  276
#define MASSAGE_BACK_OPTIMAL1_LOCATION  568 //1000//1100
#define MASSAGE_BACK_ROCK_LOCATION       600//1500

//void SetRockingEnable(bool flag);
bool RockBackLegProcess(void);
void RockFunctionEnable(bool Enable);
void RockControl(void);
bool GetbRockEnable(void);
void SetbRockEnable(bool enable);
void SetRockStep(unsigned char step);
unsigned char GetnRockModeEnterExit(void);
void SetnRockModeEnterExit(unsigned char nRockMode);
void Rock_100ms_Count(void);

#endif