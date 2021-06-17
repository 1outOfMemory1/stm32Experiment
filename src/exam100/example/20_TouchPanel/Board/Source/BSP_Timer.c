/***********************************************************************************
 Timer 驱动  huo  2016-12-23  10:30
 用于触摸屏中断扫描
************************************************************************************/
#include "BSP_Timer.h"				//Timer驱动头文件

/*
*********************************************************************************************************
*	函 数 名: BSP_Timer_Init
*	功能说明: 板载Timer初始化函数
*	形    参: usCount : 定时us时常计数
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Timer_Init(uint16_t usCount)
{
	BSP_Timer_TIM6_Init(usCount);
	BSP_Timer_NVIC_Init();
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Timer_TIM6_Init
*	功能说明: 板载Timer TIM6初始化函数
*	形    参: usCount : 定时us时常计数
*	返 回 值: 无
*********************************************************************************************************
*/
//这里时钟选择为APB1的2倍，而APB1为36M
static void BSP_Timer_TIM6_Init(uint16_t usCount)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能
	
	//定时器TIM6初始化
	TIM_TimeBaseStructure.TIM_Period = usCount; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM6,TIM_IT_Update | TIM_IT_Trigger,ENABLE ); //使能指定的TIM3中断,允许更新中断

	TIM_Cmd(TIM6, ENABLE);  //使能TIMx					 
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Timer_NVIC_Init
*	功能说明: 板载Timer NVIC初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_Timer_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Timer_ISR
*	功能说明: 板载Timer 中断服务函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Timer_ISR(void)
{
#ifndef BSP_TP_ISR_EN
	static u16 X,Y;
#endif
	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //检查TIM6更新中断发生与否
	{
#ifndef BSP_TP_ISR_EN
		if(GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_14))
			GSL2681_IRQ_Callback();
		if((X != PENX) || (Y != PENY))
		{
			printf("X: %d, Y: %d \r\n",PENX,PENY);
			X = PENX;
			Y = PENY;
		}
#endif
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //清除TIMx更新中断标志 
}

