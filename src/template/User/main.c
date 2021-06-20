#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "delay.h"
#define LED0_GPIO_PIN  GPIO_Pin_5
#define LED0_GPIO_PORT  GPIOB
#define LED0_GPIO_CLK  RCC_APB2Periph_GPIOB



#define LED1_GPIO_PIN  GPIO_Pin_5
#define LED1_GPIO_PORT  GPIOE
#define LED1_GPIO_CLK  RCC_APB2Periph_GPIOE
void myDelay(int count){
	int i = 0;
	for(;i<count;i++){
		
	}
	return;
}


void LED_GPIO_Config(void){
 GPIO_InitTypeDef  GPIO_InitStruct;
	
  RCC_APB2PeriphClockCmd(LED0_GPIO_CLK|LED1_GPIO_CLK, ENABLE);	 //使能PB,PE端口时钟
  GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;				 //LED0-->PB.5 端口配置
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);					 //根据设定参数初始化GPIOB.5
	
	
  GPIO_InitStruct.GPIO_Pin = LED1_GPIO_PIN;				 //LED1-->PB.5 端口配置
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStruct);					 //根据设定参数初始化GPIOB.5

}

int main(void)
{ 

	LED_GPIO_Config();
	while(1)
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
			GPIO_SetBits(GPIOE,GPIO_Pin_5);  
			myDelay(3000000);  		   //延时300ms
			GPIO_SetBits(GPIOB,GPIO_Pin_5);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
			myDelay(3000000);                     //延时300ms
	}
} 

