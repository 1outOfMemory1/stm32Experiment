// bsp ：board support package 板级支持包  只能在特定的板子上运行 因为电路连接不一样
#include "bsp_led.h"


void LED_GPIO_Config(void){
 GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK|LED1_GPIO_CLK, ENABLE);	 //使能PB,PE端口时钟
	GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;				 //LED0-->PB.5 端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化GPIOB.5
		
	GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;				 //LED1-->PB.5 端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化GPIOE.5

}
