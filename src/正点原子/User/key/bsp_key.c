// bsp ：board support package 板级支持包  只能在特定的板子上运行 因为电路连接不一样
#include "bsp_key.h"
#include "delay.h"






void Key_GPIO_Config(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY0_GPIO_CLK|KEY_UP_GPIO_CLK, ENABLE);	 //使能PE,PA端口时钟
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN|KEY1_GPIO_PIN;				 //KEY0 和 KEY1 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(KEY0_GPIO_PORT, &GPIO_InitStruct);			 //根据设定参数初始化 KEY0 和 KEY1 
	
	// 初始化 key_up 按键
	GPIO_InitStruct.GPIO_Pin = KEY_UP_GPIO_PIN;   
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(KEY_UP_GPIO_PORT,&GPIO_InitStruct);
	
}


u8 Key_Scan(u8 mode){
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(WK_UP==1)return 3;
	}else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}
