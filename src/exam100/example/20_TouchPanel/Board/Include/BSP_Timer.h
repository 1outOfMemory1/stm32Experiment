#ifndef _BSP_TIMER_H_
#define _BSP_TIMER_H_
#include "stm32f10x.h"
#include "BSP_UART.h"					//USART驱动头文件
#include "BSP_TouchPanel.h"

void BSP_Timer_Init(uint16_t usCount);
static void BSP_Timer_TIM6_Init(uint16_t usCount);
static void BSP_Timer_NVIC_Init(void);
void BSP_Timer_ISR(void);
 
#endif
