#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f10x.h"

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

void BSP_Led_Init(void);
static void BSP_Led_GPIO_Init(void);
void BSP_Led_On(LedCount_TypeDef LedCount);
void BSP_Led_Off(LedCount_TypeDef LedCount);
void BSP_Led_Toggle(LedCount_TypeDef LedCount);

#endif
