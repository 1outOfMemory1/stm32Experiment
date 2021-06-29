/***********************************************************************************
 Led 驱动  huo  2016-12-23  09:45
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "BSP_Led.h"					//Led驱动头文件
#include "sys.h"
/*
*********************************************************************************************************
*	函 数 名: BSP_Led_Init
*	功能说明: 板载Led初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Led_Key_Init(void)
{
	BSP_Led_GPIO_Init();
	BSP_Key_GPIO_Init();
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
GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK|KEY1_GPIO_CLK, ENABLE);	 //使能PE,PA端口时钟
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN|KEY1_GPIO_PIN;				 //KEY0 和 KEY1 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化 KEY0 和 KEY1 
}
















static void BSP_Key_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);	 //使能PB,PE端口时钟
	GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;				 //LED0-->PB.5 端口配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化GPIOB.5
		


}



u8 Key_Scan(u8 mode){
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
	  DelayMs(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
	}else if(KEY0==1&&KEY1==1)key_up=1; 	    
 	return 0;// 无按键按下
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

