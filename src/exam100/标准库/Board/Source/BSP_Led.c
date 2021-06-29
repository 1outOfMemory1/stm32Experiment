/***********************************************************************************
 Led ����  huo  2016-12-23  09:45
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "BSP_Led.h"					//Led����ͷ�ļ�
#include "sys.h"
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
	BSP_Led_GPIO_Init();
	BSP_Key_GPIO_Init();
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
GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK|KEY1_GPIO_CLK, ENABLE);	 //ʹ��PE,PA�˿�ʱ��
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN|KEY1_GPIO_PIN;				 //KEY0 �� KEY1 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; 		 //��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);			 //�����趨������ʼ�� KEY0 �� KEY1 
}
















static void BSP_Key_GPIO_Init(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(LED0_GPIO_CLK, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	GPIO_InitStruct.GPIO_Pin = LED0_GPIO_PIN;				 //LED0-->PB.5 �˿�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStruct);			 //�����趨������ʼ��GPIOB.5
		


}



u8 Key_Scan(u8 mode){
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
	  DelayMs(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
	}else if(KEY0==1&&KEY1==1)key_up=1; 	    
 	return 0;// �ް�������
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

