#ifndef  __DMA_UART_H__
#define  __DMA_UART_H__

#define DMAUART_DMA_RX_CHANNEL         2
#define DMAUART_DMA_TX_CHANNEL         3
#define BUFFER_LENGTH                  32

#define DMAUART_TX_PORT           gpioPortE
#define DMAUART_TX_BIT            14
#define DMAUART_TX_MODE           gpioModePushPull

#define DMAUART_RX_PORT           gpioPortE
#define DMAUART_RX_BIT            15
#define DMAUART_RX_MODE           gpioModeInputPull

#define DMAUART                   LEUART0
#define DMAUART_ROUTE_EN          LEUART_ROUTE_TXPEN | LEUART_ROUTE_RXPEN
#define DMAUART_ROUTE_LOCATION    LEUART_ROUTE_LOCATION_LOC2
#define DMAUART_IEN_STARTF        LEUART_IEN_STARTF
#define DMAUART_IEN_SIGF          LEUART_IEN_SIGF
#define DMAUART_IEN_TXC           LEUART_IEN_TXC

#define DMAUART_IRQ               LEUART0_IRQn

//Master->Slave Packet Type
#define PACKET_MASTER_GET_COMMAND 0x00
#define PACKET_MASTER_ACK_COMMAND 0x01
#define PACKET_MASTER_SET_STATE   0x02
//Slave->Master Packet Type
#define PACKET_SLAVE_SEND_COMMAND 0x03

#define DMAUART_UART_Init  \
{                          \
    leuartEnable,          \
    0,                     \
    9600,                  \
    leuartDatabits8,       \
    leuartNoParity,        \
    leuartStopbits1,       \
}

#define DMAUART_DMA_Init   \
{                             \
    0,                        \
    dmaControlBlock,        \
}

#define DMAUART_RX_CfgChannel   \
{                               \
    false,                      \
    true,                      \
    DMAREQ_LEUART0_RXDATAV,     \
    NULL,                       \
}

#define DMAUART_RX_CfgDescriptor  \
{                                 \
    dmaDataInc1,                  \
    dmaDataIncNone,               \
    dmaDataSize1,                 \
    dmaArbitrate1,                \
    0,                            \
}

#define DMAUART_TX_CfgChannel   \
{                               \
    false,                      \
    true,                      \
    DMAREQ_LEUART0_TXBL,        \
    NULL,                       \
}

#define DMAUART_TX_CfgDescriptor  \
{                                 \
    dmaDataIncNone,               \
    dmaDataInc1,                  \
    dmaDataSize1,                 \
    dmaArbitrate1,                \
    0,                            \
}

void LEUART0_Initial_IO(void);
void LEUART0_Initial_Data(void);
void LEUART0_Transmit_Packet(unsigned char* buf,unsigned int length);
//unsigned char LEUART0_GetRXStatus(void);
//void LEUART0_ClearRXStatus(void);
unsigned char LEUART0_GetMassageSignal(void);
unsigned char LEUART0_Get3DPluse(void);
unsigned short LEUART0_GetWalkPluse(void);
void LEUART0_10msInt(void);
bool LEUART0_isOK(void);
#endif
