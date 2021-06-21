#ifndef __BSP_BEEP_H 
#define __BSP_BEEP_H 

#include "stm32f10x.h"
#endif


#define BEEP_GPIO_PIN  GPIO_Pin_8
#define BEEP_GPIO_PORT  GPIOB
#define BEEP_GPIO_CLK  RCC_APB2Periph_GPIOB

void Beep_GPIO_Config(void);
