#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x_gpio.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"





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
	vu8 key=0;	
	delay_init();
	Beep_GPIO_Config();
	LED_GPIO_Config();
	Key_GPIO_Config();
	while(1)
	{
		u8 key = Key_Scan(0);
		switch(key){
			case 1:
				LED0=!LED0;
				break;
			case 2:
				LED1=!LED1;
				break;
			case 3:
				BEEP = !BEEP;
				break;
		}
		
	
	}
	
} 

