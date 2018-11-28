#ifndef  __DMA_UART_H__
#define  __DMA_UART_H__

#define DMAUART_DMA_RX_CHANNEL         0
#define DMAUART_DMA_TX_CHANNEL         1
#define BUFFER_LENGTH                  32

#define DMAUART_TX_PORT           gpioPortC
#define DMAUART_TX_BIT            6
#define DMAUART_TX_MODE           gpioModePushPull

#define DMAUART_RX_PORT           gpioPortC
#define DMAUART_RX_BIT            7
#define DMAUART_RX_MODE           gpioModeInputPull

#define DMAUART                  LEUART1
#define DMAUART_ROUTE_EN         LEUART_ROUTE_RXPEN
#define DMAUART_ROUTE_LOCATION   LEUART_ROUTE_LOCATION_LOC0//2
#define DMAUART_IEN_STARTF       LEUART_IEN_STARTF
#define DMAUART_IEN_SIGF         LEUART_IEN_SIGF
#define DMAUART_IEN_TXC          LEUART_IEN_TXC

#define DMAUART_IRQ              LEUART1_IRQn // LEUART0_IRQn

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
    DMAREQ_LEUART1_TXBL,        \
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

void LEUART1_Initial_IO(void);

void LEUART1_Initial_Data(void);

void LEUART1_10msInt(void);
bool LEUART1_isOK(void);

unsigned char LEUART1_GetMassageSignal(void);
unsigned char LEUART1_GetSwitchSignal(void);


#endif
