/***********************************************************************************
 ParallelBus 驱动  huo  2016-12-23  09:45
 ParallelBus IO：FSMC  Bank1_SRAM4_ADDR ((u32)0x6C000000)
************************************************************************************/
#include "BSP_ParallelBus.h"

/*
*********************************************************************************************************
*	函 数 名: BSP_PBus_Init
*	功能说明: 板载Led初始化函数
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_PBus_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;
	GPIO_InitTypeDef GPIO_InitStructure; 

	/*使能FSMC时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); //使能FSMC时钟
	/*FSMC总线使用的GPIO组时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
							 RCC_APB2Periph_GPIOF, ENABLE);

	/*FSMC数据线FSMC_D[0:15]初始化，推挽复用输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
											GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
											GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
											GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*FSMC地址线FSMC_A[0:17]初始化，推挽复用输出*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
											GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | 
											GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
											GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC NOE和NWE初试化，推挽复用输出*/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC NE4初试化，推挽复用输出*/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/*FSMC NBL0和NBL1初试化，推挽复用输出*/  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
//	GPIO_Init(GPIOE, &GPIO_InitStructure); 

	/*--------------FSMC 总线 存储器参数配置------------------------------*/
	p.FSMC_AddressSetupTime = 0;           //地址建立时间    
	p.FSMC_AddressHoldTime = 0;            //地址保持时间  
	p.FSMC_DataSetupTime = 3;              //数据建立时间
	p.FSMC_BusTurnAroundDuration = 0;      //总线恢复时间
	p.FSMC_CLKDivision = 0;                // 时钟分频因子 
	p.FSMC_DataLatency = 0;          	   //数据产生时间
	p.FSMC_AccessMode =  FSMC_AccessMode_A; //FSMC NOR控制器时序

	/*--------------FSMC 总线 参数配置------------------------------*/
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;                  //使用了FSMC的BANK1的子板块4             
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;//禁止地址数据线复用
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;           //存储器类型为SRAM
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;  //存储器数据宽度为16位
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //关闭突发模式访问
	//等待信号优先级，只有在使能突发访问模式才有效
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; 
	//关闭Wrapped burst access mode，只有在使能突发访问模式才有效
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;         
	//等待信号设置，只有在使能突发访问模式才有效
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;     //使能这个BANK的写操作
	//使能/关闭等待信息设置，只在使能突发访问模式才有效
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;     
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; //关闭Extend Mode
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;     //关闭Write Burst Mode   
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;               //读操作时序参数
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;                   //写操作时序参数

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	/*--------------使能BANK1的子板块4------------------------------*/
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  
}

/*******************************************************************************
* Function Name  : BSP_PBus_WriteBuffer
* Description    : Writes a Half-word buffer to the FSMC SRAM memory. 
* Input          : - pBuffer : pointer to buffer. 
*                  - WriteAddr : SRAM memory internal address from which the data 
*                    will be written.
*                  - NumHalfwordToWrite : number of half-words to write. 
*                    
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_PBus_WriteBuffer(u16* pBuffer, u32 WriteAddr, u32 NumHalfwordToWrite)
{
  for(; NumHalfwordToWrite != 0; NumHalfwordToWrite--) /* while there is data to write */
  {
    /* Transfer data to the memory */
    *(u16 *) (Bank1_SRAM4_ADDR + WriteAddr) = *pBuffer++;
//    *(u16 *) (Bank1_SRAM4_ADDR + WriteAddr) = *pBuffer;
    
    /* Increment the address*/  
    WriteAddr += 2;
  }   
}

/*******************************************************************************
* Function Name  : BSP_PBus_ReadBuffer
* Description    : Reads a block of data from the FSMC SRAM memory.
* Input          : - pBuffer : pointer to the buffer that receives the data read 
*                    from the SRAM memory.
*                  - ReadAddr : SRAM memory internal address to read from.
*                  - NumHalfwordToRead : number of half-words to read.
* Output         : None
* Return         : None
*******************************************************************************/
void BSP_PBus_ReadBuffer(u16* pBuffer, u32 ReadAddr, u32 NumHalfwordToRead)
{
  for(; NumHalfwordToRead != 0; NumHalfwordToRead--) /* while there is data to read */
  {
    /* Read a half-word from the memory */
    *pBuffer++ = *(vu16*) (Bank1_SRAM4_ADDR + ReadAddr);

    /* Increment the address*/  
    ReadAddr += 2;
  }  
}

