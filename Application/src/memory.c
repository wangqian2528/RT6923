#include "efm32.h"
#include "em_chip.h"
#include "EFM32_def.h"
#include "EFM32_types.h"
#include "string.h"
#include "em_msc.h"
#include "memory.h"


//--------------------------------------------------------------
#include "timer.h"

//下面区域用于云端更新
uint32_t flashPageSize;

void MEM_Initial(void)
{
  uint8_t family = *(uint8_t*)0x0FE081FE;   //在DI的区域内

  if ( ( family == 71 ) || ( family == 73 ) )
  {
    flashPageSize = 512;                
  }
  else if ( family == 72 )
  {
    flashPageSize = 4096;              
  }
  else 
  {
    flashPageSize = 2048;               
  }


}

unsigned int Get_FlashPageSize(void)
{
  
  
  return flashPageSize;
}


void Mem_Erase_Block(unsigned int start_addr)
{

        MSC_Init();
       __disable_irq();
       MSC_ErasePage((uint32_t*)start_addr);
       __enable_irq();
       MSC_Deinit();         

}

void MEM_Write_Block(unsigned int start_addr,unsigned char *pw_Buffer ,int numBytes)
{

    MSC_Init();
  __disable_irq();
     
    MSC_WriteWord((uint32_t*)start_addr, pw_Buffer, numBytes);
    
  __enable_irq();
   MSC_Deinit();
}
//上面面区域用于云端更新
//-----------------------------------------------------------------------











//Internal information word Read
unsigned char ReadEEByte(unsigned int nAddress)
{
  uint32_t* p;
  p = (uint32_t*)(nAddress);
  return((unsigned char)*p);
}

void MEM_Write_Memory(PUINT32 pw_Buffer,int numBytes)
{
    MSC_Init();
    __disable_irq();
    
    MSC_ErasePage((uint32_t*)USER_DATA_BASE);
    
    MSC_WriteWord((uint32_t*)USER_DATA_BASE, pw_Buffer, numBytes);
    
    __enable_irq();
    MSC_Deinit();
}

void MEM_Read_Memory(PUINT32 pw_Buffer,int numBytes)
{
  memcpy(pw_Buffer,(uint32_t*)(USER_DATA_BASE),numBytes); 
}

/******************************************************************************/
void MEMORYA_Write_Memory(PUINT32 pw_Buffer,int numBytes,uint32_t ADDR)
{
  MSC_Init();
     __disable_irq();

  MSC_ErasePage((uint32_t*)ADDR);
  
  MSC_WriteWord((uint32_t*)ADDR, pw_Buffer, numBytes);
  
    __enable_irq();
  MSC_Deinit();
}