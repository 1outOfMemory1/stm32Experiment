#include "key_led.h"



void key_led_gpio_config(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	/*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : KEY0_Pin */
  GPIO_InitStruct.Pin = KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LED0_Pin */
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY1_Pin */
  GPIO_InitStruct.Pin = KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);
	
}


uint8_t Key_Scan(uint8_t mode){
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0||HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0))
	{
	  HAL_Delay(10);//去抖动 
		key_up=0;
		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==0)return 1;
		else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==0)return 2;
	}else if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin)==1&&HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==1)key_up=1; 	    
 	return 0;// 无按键按下
}