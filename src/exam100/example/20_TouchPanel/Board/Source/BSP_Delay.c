/***********************************************************************************
 Delay 驱动  huo  2016-12-23  10:30
 用于延时
************************************************************************************/
#include "BSP_Delay.h"			//Delay驱动头文件

static uint8_t  fac_us=0;							//us延时倍乘数			   
static uint16_t fac_ms=0;							//ms延时倍乘数
	
/*
*********************************************************************************************************
*	函 数 名: BSP_Delay_Init
*	功能说明: 板载Delay初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void BSP_Delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  
	fac_ms=(uint16_t)fac_us*1000;					//代表每个ms需要的systick时钟数   
}								    

/*
*********************************************************************************************************
*	函 数 名: BSP_Delay_us
*	功能说明: 板载Delay微秒功能函数
*	形    参: nus : 要延时的us数
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Delay_ms
*	功能说明: 板载Delay毫秒功能函数
*	形    参: nms : 要延时的ms数，nms<=1864
*	返 回 值: 无
*********************************************************************************************************
*/
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void BSP_Delay_ms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  	    
} 
