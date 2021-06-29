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
const char  PIC_DIRECTORY[100] = "/pic/";
const char  PIC_DIRECTORY_COPY[6] = "/pic";
BYTE buffer[1600]; 
char  a[100];
char tempChar[100];




/* 不精确延时函数 */
void DelayCount(uint32_t Count)
{
	while(Count--);
}


/**
	此函数作用是获取一个文件夹中文件的数量
	不进行递归查找  ！！！！！   
	@parm  path 指定文件夹的字符串 比如 /pic 注意不要写成 /pic/ 这样不识别
*/
int getDirFileNum(const char *path)
{
	int file_num = 0;
	//char pathBuff[256]; //定义路径数组
	FRESULT res; //定义结果对象
	DIR dir; //定义目录对象
	//UINT i; //定义变量
	static FILINFO fno; //定义静态文件信息结构对象
	res = f_opendir(&dir,path); //打开目录，返回状态 和 目录对象的指针
	
	if(res == FR_OK) //打开成功
	{
		for(;;) //遍历
		{
			res = f_readdir(&dir, &fno); //读取目录，返回状态 和 文件信息的指针
			if(res != FR_OK || fno.fname[0] == 0) 
 break; //若打开失败 或 到结尾，则退出
			if(fno.fattrib & AM_DIR) //是目录
			{
				//i = strlen(path); //获取原目录长度
				//sprintf(&path[i],"/%s",fno.fname); //将新目录添加在原目录后面
				//printf("是目录::%s",path);
				//res = scan_files(path); //将新目录进行递归调用
				//if(res != FR_OK) break; //打开失败则退出
				//path[i] = 0; 
			}else
			{
				//printf("是文件:%s/%s",path,fno.fname); //是文件
				file_num++;
				//strcpy(pathBuff, fno.fname); //将文件目录存储起来
			}
		}
	}
	else
	{
		//printf("失败 - %s",&res); //打开失败
	}
	f_closedir(&dir); //关闭目录
	return file_num; //返回文件数量
}



/** 
	此函数实现的是int类型向char*类型的转换 而且带有进制转换 
	比如 数字10 转换为 十进制字符串  "10" 
	@parm  int num 要转成字符串的数字
	@parm  
*/ 
char *myitoa(int num,char *str,int radix) 
{  
	/* 索引表 */ 
		char temp; 
	char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
	unsigned unum; /* 中间变量 */ 
	int i=0,j,k; 
	/* 确定unum的值 */ 
	if(radix==10&&num<0) /* 十进制负数 */ 
	{ 
		unum=(unsigned)-num; 
		str[i++]='-'; 
	} 
	else unum=(unsigned)num; /* 其他情况 */ 
	/* 逆序 */ 
	do  
	{ 
		str[i++]=index[unum%(unsigned)radix]; 
		unum/=radix; 
	}while(unum); 
	str[i]='\0'; 
	/* 转换 */ 
	if(str[0]=='-') k=1; /* 十进制负数 */ 
	else k=0; 
	/* 将原来的“/2”改为“/2.0”，保证当num在16~255之间，radix等于16时，也能得到正确结果 */ 

	for(j=k;j<=(i-k-1)/2.0;j++) 
	{ 
		temp=str[j]; 
		str[j]=str[i-j-1]; 
		str[i-j-1]=temp; 
	} 
	return str; 
} 



/**
	此函数主要是画出一行的像素  注意这里的buf很特殊 类型是BYTE 占8bit
	但是buf中存储这颜色信息  所以需要两个BYTE拼接才能变成 u16(占16个bit)
	@parm BYTE *buf  buf的长度是你要画的图片宽度的2倍  buf中存储这每一个像素的颜色信息 16bit数据从低位到高位是 RGB 565 5+6+5 = 16
  @parm u16 width   画图的宽度
	@parm u16 line_num 要画哪一行
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
此函数功能是打开一个位图文件 将内容读取出来然后每个像素画在lcd上 如果读取出错 lcd显示红色
@parm filepath 要打开的文件路径
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




// 拼接一下路径和文件名称 这里的PIC_DIRECTORY 是需要在main.c最开始指定的  就是你存放图像的文件夹
// 比如你在根目录下的 pic/abc/efg 下存放了图片文件
// 需要填写  这里的PIC_DIRECTORY 为 /pic/abc/efg/     而PIC_DIRECTORY_COPY 为 /pic/abc/efg 一定要分清楚这两个
/**
		@parm  char * filename 图片名字

*/
char* myConcatPath(char * filename){
	strcpy(tempChar,PIC_DIRECTORY);
	strcat(tempChar,filename);
	return tempChar;
}


/* 主函数 */
int main(void)
{
	
	
	
	//u32 total,free; 
	int dirFileNum = 0;
	int i = 0;
  BSP_Led_Key_Init();				//LED灯GPIO初始化
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
	LED0 =0;
	i = 0;
	myLoadPicFromSDcard(myConcatPath("0.bin"));
	dirFileNum = getDirFileNum(PIC_DIRECTORY_COPY);
	//myLoadPicFromSDcard(fsrc,"/pic/0.bin");
	printf("dirFileNum = %d\n",dirFileNum);
	while(1){
		u8 key = Key_Scan(0);  // 检测按键 
		switch(key){
			case 1:    // 如果是key0被按下 那么就切换为下一张图片
				LED0=!LED0;
				i = (i+1)%dirFileNum; 
				printf("%d\n",i);
				myitoa(i,a,10);
				strcat(a,".bin");
				myLoadPicFromSDcard(myConcatPath(a));
				break;
			case 2:  // 如果是key1被按下 那么就切换为上一张图片
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

