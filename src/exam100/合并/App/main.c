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
const char  PIC_DIRECTORY[100] = "/pic/";
const char  PIC_DIRECTORY_COPY[6] = "/pic";
BYTE buffer[1600]; 
char  a[100];
char tempChar[100];




/* ����ȷ��ʱ���� */
void DelayCount(uint32_t Count)
{
	while(Count--);
}


/**
	�˺��������ǻ�ȡһ���ļ������ļ�������
	�����еݹ����  ����������   
	@parm  path ָ���ļ��е��ַ��� ���� /pic ע�ⲻҪд�� /pic/ ������ʶ��
*/
int getDirFileNum(const char *path)
{
	int file_num = 0;
	//char pathBuff[256]; //����·������
	FRESULT res; //����������
	DIR dir; //����Ŀ¼����
	//UINT i; //�������
	static FILINFO fno; //���徲̬�ļ���Ϣ�ṹ����
	res = f_opendir(&dir,path); //��Ŀ¼������״̬ �� Ŀ¼�����ָ��
	
	if(res == FR_OK) //�򿪳ɹ�
	{
		for(;;) //����
		{
			res = f_readdir(&dir, &fno); //��ȡĿ¼������״̬ �� �ļ���Ϣ��ָ��
			if(res != FR_OK || fno.fname[0] == 0) 
 break; //����ʧ�� �� ����β�����˳�
			if(fno.fattrib & AM_DIR) //��Ŀ¼
			{
				//i = strlen(path); //��ȡԭĿ¼����
				//sprintf(&path[i],"/%s",fno.fname); //����Ŀ¼�����ԭĿ¼����
				//printf("��Ŀ¼::%s",path);
				//res = scan_files(path); //����Ŀ¼���еݹ����
				//if(res != FR_OK) break; //��ʧ�����˳�
				//path[i] = 0; 
			}else
			{
				//printf("���ļ�:%s/%s",path,fno.fname); //���ļ�
				file_num++;
				//strcpy(pathBuff, fno.fname); //���ļ�Ŀ¼�洢����
			}
		}
	}
	else
	{
		//printf("ʧ�� - %s",&res); //��ʧ��
	}
	f_closedir(&dir); //�ر�Ŀ¼
	return file_num; //�����ļ�����
}



/** 
	�˺���ʵ�ֵ���int������char*���͵�ת�� ���Ҵ��н���ת�� 
	���� ����10 ת��Ϊ ʮ�����ַ���  "10" 
	@parm  int num Ҫת���ַ���������
	@parm  
*/ 
char *myitoa(int num,char *str,int radix) 
{  
	/* ������ */ 
		char temp; 
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	unsigned unum; /* �м���� */ 
	int i=0,j,k; 
	/* ȷ��unum��ֵ */ 
	if(radix==10&&num<0) /* ʮ���Ƹ��� */ 
	{ 
		unum=(unsigned)-num; 
		str[i++]='-'; 
	} 
	else unum=(unsigned)num; /* ������� */ 
	/* ���� */ 
	do  
	{ 
		str[i++]=index[unum%(unsigned)radix]; 
		unum/=radix; 
	}while(unum); 
	str[i]='\0'; 
	/* ת�� */ 
	if(str[0]=='-') k=1; /* ʮ���Ƹ��� */ 
	else k=0; 
	/* ��ԭ���ġ�/2����Ϊ��/2.0������֤��num��16~255֮�䣬radix����16ʱ��Ҳ�ܵõ���ȷ��� */ 

	for(j=k;j<=(i-k-1)/2.0;j++) 
	{ 
		temp=str[j]; 
		str[j]=str[i-j-1]; 
		str[i-j-1]=temp; 
	} 
	return str; 
} 



/**
	�˺�����Ҫ�ǻ���һ�е�����  ע�������buf������ ������BYTE ռ8bit
	����buf�д洢����ɫ��Ϣ  ������Ҫ����BYTEƴ�Ӳ��ܱ�� u16(ռ16��bit)
	@parm BYTE *buf  buf�ĳ�������Ҫ����ͼƬ��ȵ�2��  buf�д洢��ÿһ�����ص���ɫ��Ϣ 16bit���ݴӵ�λ����λ�� RGB 565 5+6+5 = 16
  @parm u16 width   ��ͼ�Ŀ��
	@parm u16 line_num Ҫ����һ��
*/
void myDrawAPixelLine(BYTE *buf,u16 width,u16 line_num){
	
	u16 w;
	for(w = 0; w< width*2; w+=2)
	{
		u16 x;
		x = buf[w+1]<<8 | buf[w];
		//printf("%x ",x);
		RA8875_PutPixelGUI(w/2, line_num, x);
	}
}


/**
�˺��������Ǵ�һ��λͼ�ļ� �����ݶ�ȡ����Ȼ��ÿ�����ػ���lcd�� �����ȡ���� lcd��ʾ��ɫ
@parm filepath Ҫ�򿪵��ļ�·��
*/
void myLoadPicFromSDcard(char * filepath){
	FIL fsrc;
	int j = 0;
	FRESULT res;
	res = f_open(&fsrc, filepath, FA_OPEN_EXISTING | FA_READ); 
	if (res)  
	{ 
			u16 w,h;
			for(h=0;h<480;h++)
			{
				for(w = 0; w< 800; w++)
				{
					RA8875_PutPixelGUI(w, h, RED);
				}
			}

			printf("cannot read %s \n",filepath);	 
	}else{
		printf("read %s  success\n",filepath);	 
	}
	
	while(1){
		res = f_read(&fsrc, buffer, sizeof(buffer), &br); 
    if (res || br == 0) break;   // error or eof 
		myDrawAPixelLine(buffer,800,j);
		j++;
	}
	f_close(&fsrc);
}




// ƴ��һ��·�����ļ����� �����PIC_DIRECTORY ����Ҫ��main.c�ʼָ����  ��������ͼ����ļ���
// �������ڸ�Ŀ¼�µ� pic/abc/efg �´����ͼƬ�ļ�
// ��Ҫ��д  �����PIC_DIRECTORY Ϊ /pic/abc/efg/     ��PIC_DIRECTORY_COPY Ϊ /pic/abc/efg һ��Ҫ�����������
/**
		@parm  char * filename ͼƬ����

*/
char* myConcatPath(char * filename){
	strcpy(tempChar,PIC_DIRECTORY);
	strcat(tempChar,filename);
	return tempChar;
}


/* ������ */
int main(void)
{
	
	
	
	//u32 total,free; 
	int dirFileNum = 0;
	int i = 0;
  BSP_Led_Key_Init();				//LED��GPIO��ʼ��
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
	LED0 =0;
	i = 0;
	myLoadPicFromSDcard(myConcatPath("0.bin"));
	dirFileNum = getDirFileNum(PIC_DIRECTORY_COPY);
	//myLoadPicFromSDcard(fsrc,"/pic/0.bin");
	printf("dirFileNum = %d\n",dirFileNum);
	while(1){
		u8 key = Key_Scan(0);  // ��ⰴ�� 
		switch(key){
			case 1:    // �����key0������ ��ô���л�Ϊ��һ��ͼƬ
				LED0=!LED0;
				i = (i+1)%dirFileNum; 
				printf("%d\n",i);
				myitoa(i,a,10);
				strcat(a,".bin");
				myLoadPicFromSDcard(myConcatPath(a));
				break;
			case 2:  // �����key1������ ��ô���л�Ϊ��һ��ͼƬ
				LED0=!LED0;
				if(i<=0)
					i = dirFileNum-1;
				else
					i = (i-1)%dirFileNum; 
				printf("%d\n",i);
				myitoa(i,a,10);
				strcat(a,".bin");
				myLoadPicFromSDcard(myConcatPath(a));
				break;
		}
	}
	
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

