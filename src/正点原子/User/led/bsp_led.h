#ifndef __BSP_LED_H 
#define __BSP_LED_H 

#include "stm32f10x.h"
#endif

// LED0  对应接口 PB5   LED1 对应接口 PE5

#define LED0 BIT_ADDR(GPIOB_ODR_Addr,5)
#define LED1 BIT_ADDR(GPIOE_ODR_Addr,5)


#define LED0_GPIO_PIN  GPIO_Pin_11
#define LED0_GPIO_PORT  GPIOF
#define LED0_GPIO_CLK  RCC_APB2Periph_GPIOF

#define LED1_GPIO_PIN  GPIO_Pin_5
#define LED1_GPIO_PORT  GPIOE
#define LED1_GPIO_CLK  RCC_APB2Periph_GPIOE


void LED_GPIO_Config(void);
