/***********************************************************************************
 Timer ����  huo  2016-12-23  10:30
 ���ڴ������ж�ɨ��
************************************************************************************/
#include "BSP_Timer.h"				//Timer����ͷ�ļ�

/*
*********************************************************************************************************
*	�� �� ��: BSP_Timer_Init
*	����˵��: ����Timer��ʼ������
*	��    ��: usCount : ��ʱusʱ������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Timer_Init(uint16_t usCount)
{
	BSP_Timer_TIM6_Init(usCount);
	BSP_Timer_NVIC_Init();
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Timer_TIM6_Init
*	����˵��: ����Timer TIM6��ʼ������
*	��    ��: usCount : ��ʱusʱ������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
static void BSP_Timer_TIM6_Init(uint16_t usCount)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM6��ʼ��
	TIM_TimeBaseStructure.TIM_Period = usCount; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM6,TIM_IT_Update | TIM_IT_Trigger,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	TIM_Cmd(TIM6, ENABLE);  //ʹ��TIMx					 
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Timer_NVIC_Init
*	����˵��: ����Timer NVIC��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_Timer_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_Timer_ISR
*	����˵��: ����Timer �жϷ�����
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_Timer_ISR(void)
{
#ifndef BSP_TP_ISR_EN
	static u16 X,Y;
#endif
	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)  //���TIM6�����жϷ������
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
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);  //���TIMx�����жϱ�־ 
}

