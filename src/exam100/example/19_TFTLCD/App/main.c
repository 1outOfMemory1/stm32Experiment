/***********************************************************************************
 Graphics 基本图形驱动  huo  2016-12-23  09:45
 各类基本图形功能实现
 TFTLCD IO：FSMC  Bank1_SRAM4_ADDR ((u32)0x6C000000)
			LCD_COMM_ADD	*((vu16 *)0X6C000084)
			LCD_DATA_ADD	*((vu16 *)0X6C000080)
			INT-PG7  WAIT-PG11
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"		//STM32F10x头文件
#include "BSP_Led.h"			//LED头文件
#include "BSP_ParallelBus.h"
#include "BSP_TFTLCD.h"
#include "BSP_Graphics.h"
#include "StartBMP.h"  //首次包含，以后可以不再包含！

/* 不精确延时函数 */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* 主函数 */
int main(void)
{
	u16 x,y;

	BSP_Led_Init();				//LED灯GPIO初始化
	BSP_PBus_Init();
	BSP_TFTLCD_Init();
	
	LcdClear(WHITE);
//	PWM1_duty_cycle(duty_cycle);					//开背光
/*
	LcdPrintHorz(0,240,800,BLACK);
	LcdPrintVert(400,0,480,BLACK);
	LcdPrint16bitBmp((u16*)0x0800F000,0,0,400,240);
	LcdFillRec(450,60,550,180,0,BLACK);
	LcdFillRec(650,60,750,180,1,BLACK);
	LcdPrintHorzZuHe(0,240,200,BLACK);
	LcdPrintStr("Clear",400,240,BLACK,WHITE,0);
	LcdPrintBIAS(400,480,800,240,BLACK);
*/

	RA8875_DrawHLine(0,240,800,BLACK);
	RA8875_DrawVLine(400,0,480,BLACK);
	LcdPrint16bitBmp((u16*)0x0800F000,0,0,400,240);
	for(x=0;x<400;x++)
		for(y=0;y<240;y++)
		{
			RA8875_PutPixelGUI(x,y+240,RA8875_GetPixelGUI(x,y));
		}
	LcdFillRec(450,60,550,180,0,BLACK);
	RA8875_RTERect(650,60,750,180,BLACK);
	LcdPrintStr("Clear",400,240,BLACK,WHITE,0);
	LcdPrintBIAS(400,480,800,240,BLACK);

	while (1)
	{
//		BSP_Led_On(Led1);
//		DelayCount(0x4FFFFF);
//		BSP_Led_Off(Led1);
//		DelayCount(0x4FFFFF);
		
		BSP_Led_Toggle(Led1);
		DelayCount(0x4FFFFF);
	}
}

