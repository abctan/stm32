#ifndef _KEY_H
#define _KEY_H

#include "stm32f1xx_hal.h"

enum key_state {
    KEY_STATE_DOWN, // 按下
    KEY_STATE_UP,   // 释放
};

void KEY_init(void);
enum key_state KEY0_GetStatus(void);
enum key_state KEY1_GetStatus(void);

#endif