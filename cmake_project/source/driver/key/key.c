#include "key.h"

void KEY_init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_Init.Pin   = GPIO_PIN_0;
    GPIO_Init.Mode  = GPIO_MODE_INPUT;
    GPIO_Init.Pull  = GPIO_PULLDOWN;
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOA, &GPIO_Init);

    GPIO_Init.Pin   = GPIO_PIN_4;
    GPIO_Init.Pull  = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_Init);
}

enum key_state KEY0_GetStatus(void)
{
    HAL_Delay(10);
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    return (state == GPIO_PIN_SET ? KEY_STATE_DOWN : KEY_STATE_UP);
}

enum key_state KEY1_GetStatus(void)
{
    HAL_Delay(10);
    GPIO_PinState state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
    return (state == GPIO_PIN_SET ? KEY_STATE_DOWN : KEY_STATE_UP);
}