#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "bsp_led.h"
#include "bsp_beep.h"


void myDelay(int count){
	int i = 0;
	for(;i<count;i++){
		
	}
	return;
}




int main(void)
{ 

	/*LED_GPIO_Config();
	while(1)
	{
		GPIO_ResetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);  //LED0对应引脚GPIOB.5拉低，亮  等同LED0=0;
		GPIO_SetBits(LED1_GPIO_PORT,LED1_GPIO_PIN); 
		myDelay(3000000);  		   //延时1s
		GPIO_SetBits(LED0_GPIO_PORT,LED0_GPIO_PIN);	   //LED0对应引脚GPIOB.5拉高，灭  等同LED0=1;
		GPIO_ResetBits(LED1_GPIO_PORT,LED1_GPIO_PIN);
		myDelay(3000000);                     //延时1s
	}*/
	
	Beep_GPIO_Config();
	while(1)
	{
		GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);  
		myDelay(3000000);  		   //延时1s
		GPIO_SetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);	
		myDelay(3000000);       //延时1s
	}
	
} 

