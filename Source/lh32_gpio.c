#include "lh32_gpio.h"

void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Configure pin parameters */    
    GPIO_InitStructure.Pin = GPIO_PIN_4;       // 485_DE Pin4
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;          // Drive capability: 4mA (Can be adjusted according to the load.2~16mA)
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = GPIOx_AF_GPIO;           // AF represents the ordinary IO function
    LHL_GPIO_Init(pGPIO1, &GPIO_InitStructure);
}
