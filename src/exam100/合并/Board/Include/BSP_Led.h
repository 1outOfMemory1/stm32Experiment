#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f10x.h"
#include "sys.h"
/*! 枚举Led编号 */
typedef enum
{
  LedAll = 0x0F,
  Led1   = 0x01,
  Led2   = 0x02,
  Led3   = 0x04,
  Led4   = 0x08,
}LedCount_TypeDef;

/* Led口 */
#define RCC_LEDALL      (RCC_APB2Periph_GPIOF)
#define GPIO_PORT_LED1  GPIOF
#define GPIO_PIN_LED1   GPIO_Pin_11


#define LED0_GPIO_PIN  GPIO_Pin_11
#define LED0_GPIO_PORT  GPIOF
#define LED0_GPIO_CLK  RCC_APB2Periph_GPIOF

#define KEY0_GPIO_PIN  GPIO_Pin_9
#define KEY0_GPIO_PORT  GPIOF
#define KEY0_GPIO_CLK  RCC_APB2Periph_GPIOF


#define KEY1_GPIO_PIN  GPIO_Pin_13
#define KEY1_GPIO_PORT  GPIOG
#define KEY1_GPIO_CLK  RCC_APB2Periph_GPIOG
#define KEY0  GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9)
#define KEY1  GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13)


#define LED0 BIT_ADDR(GPIOF_ODR_Addr,11)
#define LED1 BIT_ADDR(GPIOE_ODR_Addr,5)



u8 Key_Scan(u8 mode);
void BSP_Led_Key_Init(void);
static void BSP_Led_GPIO_Init(void);
static void BSP_Key_GPIO_Init(void);
void BSP_Led_On(LedCount_TypeDef LedCount);
void BSP_Led_Off(LedCount_TypeDef LedCount);
void BSP_Led_Toggle(LedCount_TypeDef LedCount);

#endif
