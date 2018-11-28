#include "DMA_Ctrl.h"

/** DMA control block, requires proper alignment. */
#if defined (__ICCARM__)
#pragma data_alignment=256
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2];
#elif defined (__CC_ARM)
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2] __attribute__ ((aligned(256)));
#elif defined (__GNUC__)
DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2] __attribute__ ((aligned(256)));
#else
#error Undefined toolkit, need to define alignment
#endif

/* DMA callback structure */
DMA_CB_TypeDef cb[DMA_CHAN_COUNT];


void DMA_Ctrl_Init(void)
{
    CMU_ClockEnable(cmuClock_DMA, true);
    
    DMA_Init_TypeDef       dmaInit;
    
    /* Configure general DMA issues */
    dmaInit.hprot        = 0;
    dmaInit.controlBlock = dmaControlBlock;
    DMA_Init(&dmaInit);
}
