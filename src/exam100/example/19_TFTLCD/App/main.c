/***********************************************************************************
 Graphics ����ͼ������  huo  2016-12-23  09:45
 �������ͼ�ι���ʵ��
 TFTLCD IO��FSMC  Bank1_SRAM4_ADDR ((u32)0x6C000000)
			LCD_COMM_ADD	*((vu16 *)0X6C000084)
			LCD_DATA_ADD	*((vu16 *)0X6C000080)
			INT-PG7  WAIT-PG11
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"		//STM32F10xͷ�ļ�
#include "BSP_Led.h"			//LEDͷ�ļ�
#include "BSP_ParallelBus.h"
#include "BSP_TFTLCD.h"
#include "BSP_Graphics.h"
#include "StartBMP.h"  //�״ΰ������Ժ���Բ��ٰ�����

/* ����ȷ��ʱ���� */
void DelayCount(uint32_t Count)
{
	while(Count--);
}

/* ������ */
int main(void)
{
	u16 x,y;

	BSP_Led_Init();				//LED��GPIO��ʼ��
	BSP_PBus_Init();
	BSP_TFTLCD_Init();
	
	LcdClear(WHITE);
//	PWM1_duty_cycle(duty_cycle);					//������
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

