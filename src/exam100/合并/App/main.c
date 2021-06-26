/***********************************************************************************
 FatFS 移植 huo  2016-07-14  09:00
 SDIO IO：SDIO_D0-PC8  SDIO_D1-PC8  SDIO_D2-PC10  SDIO_D3-PC11
          SDIO_CK-PC12  SDIO_CMD-PD2
 USART1 IO：TX1-PA9 RX1-PA10 支持printf
 Led IO：Led-PF11 低电平点亮
************************************************************************************/
#include "stm32f10x.h"			//STM32F10x头文件
#include "BSP_Led.h"			//Led头文件
#include "BSP_UART.h"			//USART驱动头文件
#include "BSP_SDCard.h"
#include "malloc.h"
#include "ff.h"  
#include "exfuns.h"    
#include "stdlib.h"

#include "BSP_ParallelBus.h"
#include "BSP_TFTLCD.h"
#include "BSP_Graphics.h"
#include "StartBMP.h"  //首次包含，以后可以不再包含！


BYTE buffer[1600]; 

/* 不精确延时函数 */
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





/* 主函数 */
int main(void)
{
	
	
	
	u16 x,y;
	u32 total,free;
	FIL fsrc;  
	FRESULT res;

	UINT br;  
	int i = 0;
	int j = 0;
	BSP_Led_Init();				//LED灯GPIO初始化
	BSP_PBus_Init();
	BSP_TFTLCD_Init();
	
	

	/* 只要工程用到中断，就需要设置中断分组；不使用默认分组方案  */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	BSP_UART_Init(115200);
 	my_mem_init(SRAMIN);		//初始化内部内存池
 	while(SD_Init())//检测不到SD卡
	{
		printf("SD Card Error! \n");
		DelayCount(0x4FFFFF);					
		printf("Please Check! \n");
		DelayCount(0x4FFFFF);
		BSP_Led_Toggle(Led1);//LED快速闪烁
	}
	
 	exfuns_init();							//为fatfs相关变量申请内存				 
 	f_mount(fs[0],"0:",1); 					//挂载SD卡 
	
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
	
//	while(exf_getfree("0",&total,&free))	//得到SD卡的总容量和剩余容量
//	{
//		printf("SD Card Fatfs Error! \n");
//		DelayCount(0xFFFFF);
//		BSP_Led_Toggle(Led1);//LED快速闪烁
//	}													  			    
//	printf("FATFS OK! \n");	 
//	printf("SD Total Size:%d     MB \n",total>>10);	 
//	printf("SD  Free Size:%d     MB \n",free>>10); 	    
		
}

