#ifndef __UART_LEG_H__
#define __UART_LEG_H__

#define UARTLEG_TX_PORT           gpioPortF//C
#define UARTLEG_TX_BIT           6// 0
#define UARTLEG_TX_MODE           gpioModePushPull

#define UARTLEG_RX_PORT           gpioPortF//C
#define UARTLEG_RX_BIT           7// 1
#define UARTLEG_RX_MODE           gpioModeInputPull


#define UARTLEG_CONTROL_PORT           gpioPortF//C
#define UARTLEG_CONTROL_BIT            5//1
#define UARTLEG_CONTROL_MODE           gpioModeInputPull

#define VOICE_WAKEUP_PORT           gpioPortF
#define VOICE_WAKEUP_BIT            8
#define VOICE_WAKEUP_MODE           gpioModeInputPull


void UartLeg_Initial_IO(void);
void UartLeg_Transmit_Packet(unsigned char* buf,unsigned int length);
unsigned char UartLeg_GetRXStatus(void);
void UartLeg_ClearRXStatus(void);
unsigned short UartLeg_GetAngle(void);
unsigned char UartLeg_GetFlexStatus(void);
unsigned char UartLeg_GetLegStatus(void);
void UartLeg_SET_TX_EN(void);
void UartLeg_CLR_TX_EN(void);

void  UartLeg_init_data(void);
void UartLeg_TX_RX_STATUS(void);

void UartLegCopyData (void);

void UartLeg_Clr_3DMessageStatus(void);

unsigned char UartLeg_Get3DMessage_RXStatus(void);

unsigned char UartLeg_Get3D_Speed(void);
unsigned char UartLeg_Get3DMassageSignal(void);
unsigned char UartLeg_Get3DPluse(void);

void  UartLeg_3DMessageCopyData (void);

void UartLeg_10msInt(void);

//unsigned char UartLeg_RX_STATUS(void);
void UartLeg_RX_TimeoutInt(void);

unsigned int Input_GetArmStatus(void);

bool bGet485Send(void);
void bSet485Send(bool v);

unsigned char UartLeg_GetVoiceKey(void);
bool UartLeg_GetVoiceRXState(void);
void UartLeg_ClearVoiceRXState(void);
void UartLeg_SetVoiceKey(unsigned char data);



#endif