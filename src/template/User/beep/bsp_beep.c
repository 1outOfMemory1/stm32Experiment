#include "bsp_beep.h"




void Beep_GPIO_Config(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);	 //使能PB端口时钟
	GPIO_InitStruct.GPIO_Pin = BEEP_GPIO_PIN;				 //BEEP 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化 BEEP 和 BEEP1 
}
