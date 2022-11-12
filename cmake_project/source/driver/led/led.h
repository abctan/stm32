#ifndef _LED_H
#define _LED_H

#include "stm32f1xx_hal.h"

#define LED_OPEN  0
#define LED_CLOSE 1

void LED_init(void);
void LED0_SetStatus(uint32_t state);
void LED1_SetStatus(uint32_t state);

#endif