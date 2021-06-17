/***********************************************************************************
 TouchPanel 驱动  huo  2016-08-26  09:00
 IIC IO：IIC_SCL-PB6  IIC_SDA-PB7
 TouchPanel_ADDR  0x80
 Timer6用于触摸屏定时扫描
 Delay 用于延时
 USART1 IO：TX1-PA9 RX1-PA10 支持printf
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "BSP_Led.h"		//LED头文件
#include "BSP_UART.h"		//USART驱动头文件
#include "BSP_Delay.h"		//Delay驱动头文件
#include "MyIIC.h"
#include "BSP_TouchPanel.h"
#include "BSP_Timer.h"		//Timer驱动头文件

/* 不精确延时函数 */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* 主函数 */
int main(void)
{
	BSP_Led_Init();				//LED灯GPIO初始化
	/* 只要工程用到中断，就需要设置中断分组；不使用默认分组方案  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	BSP_UART_Init(115200);
	BSP_Delay_Init();
	BSP_TP_Init();				//触摸屏初始化，支持中断输出，本实验默认使用定时扫描
	BSP_Timer_Init(10*1000);	//定时 10*1000us = 10ms，用于定时扫描触摸屏是否按下
	
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

//		printf("Hello World！\r\n");
	}
}
