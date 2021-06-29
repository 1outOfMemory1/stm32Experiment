/***********************************************************************************
 Led ����  huo  2016-12-23  09:45
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "BSP_Led_Key.h"					//Led����ͷ�ļ�
#include "stm32f1xx_hal_gpio.h"
/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_Init
*	����˵��: ����Led��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Led_Key_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = LED0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY1_GPIO_Port, &GPIO_InitStruct);
}




u8 Key_Scan(u8 mode){
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin) == 0 ||HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0))
	{
	  HAL_Delay(10);//ȥ���� 
		key_up=0;
		if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin) == 0)return 1;
		else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 0)return 2;
	}else if(HAL_GPIO_ReadPin(KEY0_GPIO_Port,KEY0_Pin) == 1&&HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin) == 1)key_up=1; 	    
 	return 0;// �ް�������
}
