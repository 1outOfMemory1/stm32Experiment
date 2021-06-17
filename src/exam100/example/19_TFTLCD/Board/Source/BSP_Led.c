/***********************************************************************************
 Led 驱动  huo  2016-12-23  09:45
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "BSP_Led.h"					//Led驱动头文件

/*
*********************************************************************************************************
*	函 数 名: BSP_Led_Init
*	功能说明: 板载Led初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Led_Init(void)
{
	BSP_Led_GPIO_Init();
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Led_GPIO_Init
*	功能说明: 板载Led GPIO初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_Led_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_LEDALL, ENABLE);				//使能GPIOF时钟 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;			//Led引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);
	
	BSP_Led_Off(Led1);
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Led_On
*	功能说明: 板载Led点亮功能函数
*	形    参: LedCount : 指示Led序号
*	返 回 值: 无
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
*	函 数 名: BSP_Led_Off
*	功能说明: 板载Led熄灭功能函数
*	形    参: LedCount : 指示Led序号
*	返 回 值: 无
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
*	函 数 名: BSP_Led_Toggle
*	功能说明: 板载Led翻转功能函数
*	形    参: LedCount : 指示Led序号
*	返 回 值: 无
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

