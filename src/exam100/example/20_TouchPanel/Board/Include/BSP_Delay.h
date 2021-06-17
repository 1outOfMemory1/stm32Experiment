#ifndef _BSP_DELAY_H_
#define _BSP_DELAY_H_ 			   
#include "stm32f10x.h"
	 
void BSP_Delay_Init(void);
void BSP_Delay_us(uint32_t nus);
void BSP_Delay_ms(uint16_t nms);

#endif
