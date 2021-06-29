#ifndef _BSP_PBUS_H
#define _BSP_PBUS_H
#include "stm32f10x.h"

#define Bank1_SRAM4_ADDR    ((u32)0x6C000000)

void BSP_PBus_Init(void);
void BSP_PBus_WriteBuffer(u16* pBuffer, u32 WriteAddr, u32 NumHalfwordToWrite);
void BSP_PBus_ReadBuffer(u16* pBuffer, u32 ReadAddr, u32 NumHalfwordToRead);

#endif 

