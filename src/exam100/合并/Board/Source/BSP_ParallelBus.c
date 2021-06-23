/***********************************************************************************
 ParallelBus ����  huo  2016-12-23  09:45
 ParallelBus IO��FSMC  Bank1_SRAM4_ADDR ((u32)0x6C000000)
************************************************************************************/
#include "BSP_ParallelBus.h"

/*
*********************************************************************************************************
*	�� �� ��: BSP_PBus_Init
*	����˵��: ����Led��ʼ������
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BSP_PBus_Init(void)
{
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  p;
	GPIO_InitTypeDef GPIO_InitStructure; 

	/*ʹ��FSMCʱ�� */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE); //ʹ��FSMCʱ��
	/*FSMC����ʹ�õ�GPIO��ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOG | RCC_APB2Periph_GPIOE |
							 RCC_APB2Periph_GPIOF, ENABLE);

	/*FSMC������FSMC_D[0:15]��ʼ�������츴�����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
											GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
											GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
											GPIO_Pin_15;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/*FSMC��ַ��FSMC_A[0:17]��ʼ�������츴�����*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
											GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | 
											GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | 
											GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13; 
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC NOE��NWE���Ի������츴�����*/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/*FSMC NE4���Ի������츴�����*/  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/*FSMC NBL0��NBL1���Ի������츴�����*/  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; 
//	GPIO_Init(GPIOE, &GPIO_InitStructure); 

	/*--------------FSMC ���� �洢����������------------------------------*/
	p.FSMC_AddressSetupTime = 0;           //��ַ����ʱ��    
	p.FSMC_AddressHoldTime = 0;            //��ַ����ʱ��  
	p.FSMC_DataSetupTime = 3;              //���ݽ���ʱ��
	p.FSMC_BusTurnAroundDuration = 0;      //���߻ָ�ʱ��
	p.FSMC_CLKDivision = 0;                // ʱ�ӷ�Ƶ���� 
	p.FSMC_DataLatency = 0;          	   //���ݲ���ʱ��
	p.FSMC_AccessMode =  FSMC_AccessMode_A; //FSMC NOR������ʱ��

	/*--------------FSMC ���� ��������------------------------------*/
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;                  //ʹ����FSMC��BANK1���Ӱ��4             
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;//��ֹ��ַ�����߸���
	FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;           //�洢������ΪSRAM
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;  //�洢�����ݿ��Ϊ16λ
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable; //�ر�ͻ��ģʽ����
	//�ȴ��ź����ȼ���ֻ����ʹ��ͻ������ģʽ����Ч
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low; 
	//�ر�Wrapped burst access mode��ֻ����ʹ��ͻ������ģʽ����Ч
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;         
	//�ȴ��ź����ã�ֻ����ʹ��ͻ������ģʽ����Ч
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;     //ʹ�����BANK��д����
	//ʹ��/�رյȴ���Ϣ���ã�ֻ��ʹ��ͻ������ģʽ����Ч
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;     
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; //�ر�Extend Mode
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;     //�ر�Write Burst Mode   
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;               //������ʱ�����
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;                   //д����ʱ�����

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

	/*--------------ʹ��BANK1���Ӱ��4------------------------------*/
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

