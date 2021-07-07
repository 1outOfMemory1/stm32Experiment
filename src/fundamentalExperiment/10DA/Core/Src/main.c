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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
const uint8_t sine_8bit[256] = {0x80,0x84,0x87,0x8A,0x8D,0x90,0x93,0x96,0x99,0x9D,0xA0,
	0xA3,0xA6,0xA9,0xAC,0xAF,0xB1,0xB4,0xB7,0xBA,0xBD,0xC0,0xC2,0xC5,0xC8,0xCA,0xCD,0xCF,
	0xD2,0xD4,0xD6,0xD9,0xDB,0xDD,0xDF,0xE1,0xE3,0xE5,0xE7,0xE9,0xEB,0xED,0xEE,0xF0,0xF1
	,0xF3,0xF4,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFD,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFD,0xFD,0xFC,0xFB,0xFA,0xF9,
	0xF8,0xF7,0xF6,0xF4,0xF3,0xF1,0xF0,0xEE,0xED,0xEB,0xE9,0xE7,0xE5,0xE3,0xE1,0xDF,0xDD,
	0xDB,0xD9,0xD6,0xD4,0xD2,0xCF,0xCD,0xCA,0xC8,0xC5,0xC2,0xC0,0xBD,0xBA,0xB7,0xB4,0xB1,
	0xAF,0xAC,0xA9,0xA6,0xA3,0xA0,0x9D,0x99,0x96,0x93,0x90,0x8D,0x8A,0x87,0x84,0x81,0x7D,
	0x7A,0x77,0x74,0x71,0x6E,0x6B,0x68,0x64,0x61,0x5E,0x5B,0x58,0x55,0x52,0x50,0x4D,0x4A,
	0x47,0x44,0x41,0x3F,0x3C,0x39,0x37,0x34,0x32,0x2F,0x2D,0x2B,0x28,0x26,0x24,0x22,0x20,
	0x1E,0x1C,0x1A,0x18,0x16,0x14,0x13,0x11,0x10,0x0E,0x0D,0x0B,0x0A,0x09,0x08,0x07,0x06,
	0x05,0x04,0x04,0x03,0x02,0x02,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x02,0x02,0x03,0x04,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0D,0x0E,0x10,0x11,0x13,
	0x14,0x16,0x18,0x1A,0x1C,0x1E,0x20,0x22,0x24,0x26,0x28,0x2B,0x2D,0x2F,0x32,0x34,0x37,
	0x39,0x3C,0x3F,0x41,0x44,0x47,0x4A,0x4D,0x50,0x52,0x55,0x58,0x5B,0x5E,0x61,0x64,0x68,
	0x6B,0x6E,0x71,0x74,0x77,0x7A,0x7D};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

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

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_DAC_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim6);

	//HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0x100); 
	//HAL_DAC_Start(&hdac,DAC_CHANNEL_1);
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)sine_8bit, 256, DAC_ALIGN_8B_R);
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
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
