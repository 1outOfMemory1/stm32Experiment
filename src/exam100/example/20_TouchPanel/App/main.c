/***********************************************************************************
 TouchPanel ����  huo  2016-08-26  09:00
 IIC IO��IIC_SCL-PB6  IIC_SDA-PB7
 TouchPanel_ADDR  0x80
 Timer6���ڴ�������ʱɨ��
 Delay ������ʱ
 USART1 IO��TX1-PA9 RX1-PA10 ֧��printf
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "BSP_Led.h"		//LEDͷ�ļ�
#include "BSP_UART.h"		//USART����ͷ�ļ�
#include "BSP_Delay.h"		//Delay����ͷ�ļ�
#include "MyIIC.h"
#include "BSP_TouchPanel.h"
#include "BSP_Timer.h"		//Timer����ͷ�ļ�

/* ����ȷ��ʱ���� */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* ������ */
int main(void)
{
	BSP_Led_Init();				//LED��GPIO��ʼ��
	/* ֻҪ�����õ��жϣ�����Ҫ�����жϷ��飻��ʹ��Ĭ�Ϸ��鷽��  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	BSP_UART_Init(115200);
	BSP_Delay_Init();
	BSP_TP_Init();				//��������ʼ����֧���ж��������ʵ��Ĭ��ʹ�ö�ʱɨ��
	BSP_Timer_Init(10*1000);	//��ʱ 10*1000us = 10ms�����ڶ�ʱɨ�败�����Ƿ���
	
	while (1)
	{
		BSP_Led_On(Led1);
//		DelayCount(0x4FFFFF);
		BSP_Delay_ms(500);
		BSP_Led_Off(Led1);
//		DelayCount(0x4FFFFF);
		BSP_Delay_ms(500);
		
//		BSP_Led_Toggle(Led1);
////		DelayCount(0x4FFFFF);
//		BSP_Delay_ms(500);

//		printf("Hello World��\r\n");
	}
}
