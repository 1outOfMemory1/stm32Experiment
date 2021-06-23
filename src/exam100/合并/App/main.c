/***********************************************************************************
 FatFS ��ֲ huo  2016-07-14  09:00
 SDIO IO��SDIO_D0-PC8  SDIO_D1-PC8  SDIO_D2-PC10  SDIO_D3-PC11
          SDIO_CK-PC12  SDIO_CMD-PD2
 USART1 IO��TX1-PA9 RX1-PA10 ֧��printf
 Led IO��Led-PF11 �͵�ƽ����
************************************************************************************/
#include "stm32f10x.h"			//STM32F10xͷ�ļ�
#include "BSP_Led.h"			//Ledͷ�ļ�
#include "BSP_UART.h"			//USART����ͷ�ļ�
#include "BSP_SDCard.h"
#include "malloc.h"
#include "ff.h"  
#include "exfuns.h"    


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
	u32 total,free;
	
	
	BSP_Led_Init();				//LED��GPIO��ʼ��
	BSP_PBus_Init();
	BSP_TFTLCD_Init();
	
	LcdClear(WHITE);
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
	
	
	
	
		
		
		
		
		
		
		
		
	
	
	
	
	
	
	
 

	BSP_Led_Init();				//LED��GPIO��ʼ��
	/* ֻҪ�����õ��жϣ�����Ҫ�����жϷ��飻��ʹ��Ĭ�Ϸ��鷽��  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	BSP_UART_Init(115200);
 	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
 	while(SD_Init())//��ⲻ��SD��
	{
		printf("SD Card Error! \n");
		DelayCount(0x4FFFFF);					
		printf("Please Check! \n");
		DelayCount(0x4FFFFF);
		BSP_Led_Toggle(Led1);//LED������˸
	}
	
 	exfuns_init();							//Ϊfatfs��ر��������ڴ�				 
 	f_mount(fs[0],"0:",1); 					//����SD�� 
	
	while(exf_getfree("0",&total,&free))	//�õ�SD������������ʣ������
	{
		printf("SD Card Fatfs Error! \n");
		DelayCount(0xFFFFF);
		BSP_Led_Toggle(Led1);//LED������˸
	}													  			    
	printf("FATFS OK! \n");	 
	printf("SD Total Size:%d     MB \n",total>>10);	 
	printf("SD  Free Size:%d     MB \n",free>>10); 	    

	while (1)
	{
//		BSP_Led_On(Led1);
//		DelayCount(0x4FFFFF);
//		BSP_Led_Off(Led1);
//		DelayCount(0x4FFFFF);
		
		BSP_Led_Toggle(Led1);
		DelayCount(0x4FFFFF);
		
//		printf("Hello World��\r\n");
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}

