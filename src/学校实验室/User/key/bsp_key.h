#ifndef __BSP_KEY_H 
#define __BSP_KEY_H 

#include "stm32f10x.h"
#endif



#define KEY0_GPIO_PIN  GPIO_Pin_9
#define KEY0_GPIO_PORT  GPIOF
#define KEY0_GPIO_CLK  RCC_APB2Periph_GPIOF


#define KEY1_GPIO_PIN  GPIO_Pin_13
#define KEY1_GPIO_PORT  GPIOG
#define KEY1_GPIO_CLK  RCC_APB2Periph_GPIOG

#define KEY_UP_GPIO_PIN  GPIO_Pin_0
#define KEY_UP_GPIO_PORT  GPIOA
#define KEY_UP_GPIO_CLK  RCC_APB2Periph_GPIOA



#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)
#define KEY1  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13)
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)



/* 接口图
vcc3.3 key_up  wk_up  PA0
gnd key0 key0  PE4
gnd key1 key1  PE3
*/

void Key_GPIO_Config(void); // IO初始化
u8 Key_Scan(u8);  //按键扫描函数

