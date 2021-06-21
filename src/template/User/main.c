#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bsp_led.h"



void myDelay(int count){
	int i = 0;
	for(;i<count;i++){
		
	}
	return;
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

