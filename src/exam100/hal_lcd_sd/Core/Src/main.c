/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "BSP_Graphics.h"
#include "BSP_TFTLCD.h"
#include "BSP_Led_Key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
const char  PIC_DIRECTORY[100] = "/pic/";
const char  PIC_DIRECTORY_COPY[6] = "/pic";
BYTE buffer[1600]; 
char  a[100];
char tempChar[100];
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
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
	int j = 0;
	FRESULT res;
	res = f_open(&SDFile, filepath, FA_OPEN_EXISTING | FA_READ); 
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
		unsigned int br;
		res = f_read(&SDFile, buffer, sizeof(buffer), &br); 
    if (res || br == 0) break;   // error or eof 
		myDrawAPixelLine(buffer,800,j);
		j++;
	}
	f_close(&SDFile);
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
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int c, FILE *stream)
{
	HAL_UART_Transmit(&huart1, (unsigned char *)&c, 1, 1000);
	return 1;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int dirFileNum = 0;
	int i = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SDIO_SD_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  MX_FSMC_Init();
  /* USER CODE BEGIN 2 */
	BSP_TFTLCD_Init();
	
	//LcdClear(YELLOW);
	

		 
 	retSD = f_mount(&SDFatFS,SDPath,1);					//挂载SD卡 
	if(retSD != FR_OK ){
		while(1){
				HAL_Delay(1000);
				printf("sdCard Error!!!");
		}
	}

	i = 0;
	myLoadPicFromSDcard(myConcatPath("0.bin"));
	dirFileNum = getDirFileNum(PIC_DIRECTORY_COPY);
	//myLoadPicFromSDcard(fsrc,"/pic/0.bin");
	printf("dirFileNum = %d\n",dirFileNum);
	while(1){
		u8 key = Key_Scan(0);  // 检测按键 
		switch(key){
			case 1:    // 如果是key0被按下 那么就切换为下一张图片
				HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
				i = (i+1)%dirFileNum; 
				printf("%d\n",i);
				myitoa(i,a,10);
				strcat(a,".bin");
				myLoadPicFromSDcard(myConcatPath(a));
				break;
			case 2:  // 如果是key1被按下 那么就切换为上一张图片
				HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
