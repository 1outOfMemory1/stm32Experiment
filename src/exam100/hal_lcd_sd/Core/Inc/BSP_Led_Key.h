#ifndef _BSP_LED_H_
#define _BSP_LED_H_
#include "stm32f1xx_hal.h"


#define u16 uint16_t
#define u8 uint8_t
#define u32 uint32_t

#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOF
#define LED0_Pin GPIO_PIN_11
#define LED0_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOG



u8 Key_Scan(u8 mode);
void BSP_Led_Key_Init(void);


#endif
