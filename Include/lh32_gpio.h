#ifndef _LH32_GPIO_H
#define _LH32_GPIO_H

#include "lh32m0xx_lhl.h"

#define RS485_TX    LHL_GPIO_SetPins(pGPIO1, GPIO_PIN_4);
#define RS485_RX    LHL_GPIO_ResetPins(pGPIO1, GPIO_PIN_4);

void gpio_init(void);

#endif
