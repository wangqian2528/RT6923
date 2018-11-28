#ifndef __DMA_CTRL_H__
#define __DMA_CTRL_H__

#include <stdio.h>
#include "efm32.h"
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_dma.h"

extern DMA_DESCRIPTOR_TypeDef dmaControlBlock[DMA_CHAN_COUNT * 2];
extern DMA_CB_TypeDef cb[DMA_CHAN_COUNT];

void DMA_Ctrl_Init(void);

#endif