/***********************************************************************************
 UART ����  huo  2016-12-23  10:30
 USART1 IO��TX1-PA9 RX1-PA10 ֧��printf
************************************************************************************/
#include "BSP_UART.h"					//USART����ͷ�ļ�

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc������ʹ��USART1��USART1�����ʼ���ſ��ã� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0) {};//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
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
*	�� �� ��: BSP_UART_Init
*	����˵��: ����UART��ʼ������
*	��    ��: Bound : ������
*	�� �� ֵ: ��
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
*	�� �� ��: BSP_UART_GPIO_Init
*	����˵��: ����UART GPIO��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_UART_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��
	
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_UART_USART_Init
*	����˵��: ����UART USART��ʼ������
*	��    ��: Bound : ������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_UART_USART_Init(uint32_t BaudRate)
{
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);	//ʹ��USART1ʱ��

  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = BaudRate;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_UART_NVIC_Init
*	����˵��: ����UART NVIC��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void BSP_UART_NVIC_Init(void)
{
 	NVIC_InitTypeDef NVIC_InitStructure;

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x03 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}

/*
*********************************************************************************************************
*	�� �� ��: BSP_UART_ISR
*	����˵��: ����UART �жϷ����ܺ���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_UART_ISR(void)
{
	uint16_t Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		USART_SendData(USART1,Res);
  } 
}
