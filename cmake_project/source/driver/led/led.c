#include "led.h"

void LED_init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_Init.Pin   = GPIO_PIN_5;
    GPIO_Init.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_Init.Pull  = GPIO_PULLUP;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOB, &GPIO_Init);
    HAL_GPIO_Init(GPIOE, &GPIO_Init);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
}

void LED0_SetStatus(uint32_t state)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
}

void LED1_SetStatus(uint32_t state)
{
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, state);
}