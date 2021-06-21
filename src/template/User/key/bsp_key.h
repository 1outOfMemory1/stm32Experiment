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



void Key_GPIO_Config(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK|KEY_UP_GPIO_CLK, ENABLE);	 //使能PE,PA端口时钟
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN|KEY1_GPIO_PIN;				 //KEY0 和 KEY1 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; 		 //上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化 KEY0 和 KEY1 
}
