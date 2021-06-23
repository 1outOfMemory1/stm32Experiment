#ifndef __BSP_KEY_H 
#define __BSP_KEY_H 

#include "stm32f10x.h"
#endif



#define KEY0_GPIO_PIN  GPIO_Pin_4
#define KEY0_GPIO_PORT  GPIOE
#define KEY0_GPIO_CLK  RCC_APB2Periph_GPIOE


#define KEY1_GPIO_PIN  GPIO_Pin_3
#define KEY1_GPIO_PORT  GPIOE
#define KEY1_GPIO_CLK  RCC_APB2Periph_GPIOE

#define KEY_UP_GPIO_PIN  GPIO_Pin_0
#define KEY_UP_GPIO_PORT  GPIOA
#define KEY_UP_GPIO_CLK  RCC_APB2Periph_GPIOA



#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)



/* 接口图
vcc3.3 key_up  wk_up  PA0
gnd key0 key0  PE4
gnd key1 key1  PE3
*/

void Key_GPIO_Config(void); // IO初始化
u8 Key_Scan(u8);  //按键扫描函数

