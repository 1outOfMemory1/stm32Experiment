#ifndef __KEY_LED_H
#define __KEY_LED_H


#endif /* end of __KEY_LED_H */

#include "stm32f1xx_hal.h"
#include "stdint.h"


#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOF
#define LED0_Pin GPIO_PIN_11
#define LED0_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_13
#define KEY1_GPIO_Port GPIOG


void key_led_gpio_config();
uint8_t Key_Scan(uint8_t mode);
