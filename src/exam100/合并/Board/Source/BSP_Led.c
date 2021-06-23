/***********************************************************************************
 Led ����  huo  2016-12-23  09:45
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "BSP_Led.h"					//Led����ͷ�ļ�

/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_Init
*	����˵��: ����Led��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Led_Init(void)
{
	BSP_Led_GPIO_Init();
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_GPIO_Init
*	����˵��: ����Led GPIO��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_Led_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_LEDALL, ENABLE);				//ʹ��GPIOFʱ�� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;			//Led����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);
	
	BSP_Led_Off(Led1);
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_On
*	����˵��: ����Led�������ܺ���
*	��    ��: LedCount : ָʾLed���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Led_On(LedCount_TypeDef LedCount)
{
	if (LedCount & Led1)
		GPIO_PORT_LED1->BRR = GPIO_PIN_LED1;
	if (LedCount & Led2)
		;
	if (LedCount & Led3)
		;
	if (LedCount & Led4)
		;
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_Off
*	����˵��: ����LedϨ���ܺ���
*	��    ��: LedCount : ָʾLed���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Led_Off(LedCount_TypeDef LedCount)
{
	if (LedCount & Led1)
		GPIO_PORT_LED1->BSRR = GPIO_PIN_LED1;
	if (LedCount & Led2)
		;
	if (LedCount & Led3)
		;
	if (LedCount & Led4)
		;
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Led_Toggle
*	����˵��: ����Led��ת���ܺ���
*	��    ��: LedCount : ָʾLed���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Led_Toggle(LedCount_TypeDef LedCount)
{
	if (LedCount & Led1)
		GPIO_PORT_LED1->ODR ^= GPIO_PIN_LED1;
	if (LedCount & Led2)
		;
	if (LedCount & Led3)
		;
	if (LedCount & Led4)
		;
}

