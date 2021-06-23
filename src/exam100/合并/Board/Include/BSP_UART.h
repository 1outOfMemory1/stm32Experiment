#ifndef _BSP_UART_H_
#define _BSP_UART_H_
#include <stdio.h>
#include "stm32f10x.h"

void BSP_UART_Init(uint32_t BaudRate);
static void BSP_UART_GPIO_Init(void);
static void BSP_UART_USART_Init(uint32_t BaudRate);
static void BSP_UART_NVIC_Init(void);
void BSP_UART_ISR(void);

#endif
