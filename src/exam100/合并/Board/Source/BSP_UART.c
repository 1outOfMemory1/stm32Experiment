/***********************************************************************************
 UART 驱动  huo  2016-12-23  10:30
 USART1 IO：TX1-PA9 RX1-PA10 支持printf
************************************************************************************/
#include "BSP_UART.h"					//USART驱动头文件

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数，使用USART1，USART1必须初始化才可用！ 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0) {};//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	

	return ch;
}
int GetKey (void)  
{ 
	while (!(USART1->SR & USART_FLAG_RXNE));

	return ((int)(USART1->DR & 0x1FF));
}
*/

/*
*********************************************************************************************************
*	函 数 名: BSP_UART_Init
*	功能说明: 板载UART初始化函数
*	形    参: Bound : 波特率
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_UART_Init(uint32_t BaudRate)
{
	BSP_UART_USART_Init(BaudRate);
	BSP_UART_GPIO_Init();
	BSP_UART_NVIC_Init();
}

/*
*********************************************************************************************************
*	函 数 名: BSP_UART_GPIO_Init
*	功能说明: 板载UART GPIO初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_UART_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能GPIOA时钟
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
}

/*
*********************************************************************************************************
*	函 数 名: BSP_UART_USART_Init
*	功能说明: 板载UART USART初始化函数
*	形    参: Bound : 波特率
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_UART_USART_Init(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//使能USART1时钟

  //USART 初始化设置
	USART_InitStructure.USART_BaudRate = BaudRate;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

/*
*********************************************************************************************************
*	函 数 名: BSP_UART_NVIC_Init
*	功能说明: 板载UART NVIC初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void BSP_UART_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}

/*
*********************************************************************************************************
*	函 数 名: BSP_UART_ISR
*	功能说明: 板载UART 中断服务功能函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_UART_ISR(void)
{
	uint16_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		USART_SendData(USART1,Res);
  } 
}
