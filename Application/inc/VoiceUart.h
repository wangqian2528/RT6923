#include "MassageStatus.h"

#define UART1_RX_PORT          1// gpioPortC
#define UART1_RX_BIT           1// 13
#define UART1_RX_MODE          1// gpioModeInputPull

#define UART1_TX_PORT           1//gpioPortC
#define UART1_TX_BIT            1//12
#define UART1_TX_MODE           1//gpioModePushPull

#define VOICE_POWER_PORT        1// gpioPortC
#define VOICE_POWER_BIT         1// 12
#define VOICE_POWER_MODE        1// gpioModePushPull

void UART1_Initial_IO(void);
//unsigned int uartGetData(unsigned char* dataPtr, unsigned int dataLen);
unsigned char VoiceUart_GetRXStatus(void);
unsigned char VoiceUart_GetKey(void);
void VoiceUart_SetKey(unsigned char by_Data);
unsigned char VoiceUart_GetExternKey(void);
void VoiceUart_ClearRXStatus(void);
//int VoiceUart_GetPM25(unsigned int* PM);
//void VoiceUart_1msInt(void);
//void VoiceUart_PowerOn(void);
void VoiceUart_PowerOff(void);

//void VoiceUart_SetMusicStatus(bool musicOn);

