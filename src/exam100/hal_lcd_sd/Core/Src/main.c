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
	

		 
 	retSD = f_mount(&SDFatFS,SDPath,1);					//����SD�� 
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
		u8 key = Key_Scan(0);  // ��ⰴ�� 
		switch(key){
			case 1:    // �����key0������ ��ô���л�Ϊ��һ��ͼƬ
				HAL_GPIO_TogglePin(LED0_GPIO_Port,LED0_Pin);
				i = (i+1)%dirFileNum; 
				printf("%d\n",i);
				myitoa(i,a,10);
				strcat(a,".bin");
				myLoadPicFromSDcard(myConcatPath(a));
				break;
			case 2:  // �����key1������ ��ô���л�Ϊ��һ��ͼƬ
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
