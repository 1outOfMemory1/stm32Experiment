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
#include "stdlib.h"

#include "BSP_ParallelBus.h"
#include "BSP_TFTLCD.h"
#include "BSP_Graphics.h"
#include "StartBMP.h"  //�״ΰ������Ժ���Բ��ٰ�����


BYTE buffer[1600]; 

/* ����ȷ��ʱ���� */
void DelayCount(uint32_t Count)
{
	while(Count--);
}


void myitoa(char *str,int n)
{
	int i,j = 0;
	while(n!=0)
	{
		*str = n%10 + '0';
		n/=10;
		j++;
		str++;
	}
	*str = '\0';
//	for(i=1;i<=j;i++)
//	{
//		//printf("%c",*(str-i));
//	}
	//printf("\n");
}



void myDrawAPixelLine(BYTE *buf,u16 width,u16 line_num){
	
	
	u16 w,h;
	for(w = 0; w< width*2; w+=2)
	{
		u16 x;
		x = buf[w+1]<<8 | buf[w];
		//printf("%x ",x);
		RA8875_PutPixelGUI(w/2, line_num, x);
	}
}


void myLoadPicFromSDcard(FIL fsrc,char * filename){
	int j = 0;
	FRESULT res;
	res = f_open(&fsrc, filename, FA_OPEN_EXISTING | FA_READ); 
	if (res)  
	{ 
			printf("cannot read %s \n",filename);	 
	}else{
		printf("read %s  success\n",filename);	 
	}
	
	while(1){
		res = f_read(&fsrc, buffer, sizeof(buffer), &br); 
    if (res || br == 0) break;   // error or eof 
		myDrawAPixelLine(buffer,800,j);
		j++;
	}
	f_close(&fsrc);
}





/* ������ */
int main(void)
{
	
	
	
	u16 x,y;
	u32 total,free;
	FIL fsrc;  
	FRESULT res;

	UINT br;  
	int i = 0;
	int j = 0;
	BSP_Led_Init();				//LED��GPIO��ʼ��
	BSP_PBus_Init();
	BSP_TFTLCD_Init();
	
	

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
	
	while(1){
		for(i = 1;i<=2;i++){
			char  a[100];
			myitoa(a,i);
			//printf("%s\n",a);
			myLoadPicFromSDcard(fsrc,strcat(a,".bin"));
			DelayMs(2000);
		}
	}
		
	//myLoadPicFromSDcard(fsrc,"1.bin");
	
//	while(exf_getfree("0",&total,&free))	//�õ�SD������������ʣ������
//	{
//		printf("SD Card Fatfs Error! \n");
//		DelayCount(0xFFFFF);
//		BSP_Led_Toggle(Led1);//LED������˸
//	}													  			    
//	printf("FATFS OK! \n");	 
//	printf("SD Total Size:%d     MB \n",total>>10);	 
//	printf("SD  Free Size:%d     MB \n",free>>10); 	    
		
}

