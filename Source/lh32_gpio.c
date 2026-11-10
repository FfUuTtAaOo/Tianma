#include "lh32_gpio.h"

void gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 先把 485 方向脚的数据锁存器拉低, 再打开输出驱动。
     * 否则从"输入"切到"推挽输出"的那一瞬间, 锁存器可能是上电默认的高电平,
     * WS3085 的 DE 会短暂为高、抢占总线, 正好把主机上电后发来的第一条指令撞掉。 */
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOEN_Msk, ENABLE);
    LHL_GPIO_ResetPins(pGPIO1, GPIO_PIN_4);

    /* Configure pin parameters */    
    GPIO_InitStructure.Pin = GPIO_PIN_4;       // 485_DE Pin4
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;          // Drive capability: 4mA (Can be adjusted according to the load.2~16mA)
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = GPIOx_AF_GPIO;           // AF represents the ordinary IO function
    LHL_GPIO_Init(pGPIO1, &GPIO_InitStructure);

    RS485_RX;                                  /* 显式确认一次: 接收态 */
}
