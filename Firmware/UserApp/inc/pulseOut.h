#ifndef __PULSE_OUT_H
#define __PULSE_OUT_H
#include "user_main.h"
#define pulseEnablePin (!HAL_GPIO_ReadPin(PULSE_ENABLE_GPIO_Port,PULSE_ENABLE_Pin))
void pluseOutInit(void);
#endif
