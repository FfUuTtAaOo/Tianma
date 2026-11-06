#include "lh32_i2c.h"

/* Global --------------------------------------------------------------------*/
I2C_HandleTypeDef hI2C;

/* Extern --------------------------------------------------------------------*/
extern uint8_t I2C_RX_Data[10];
extern uint8_t I2C_TX_Data[10];

/* ------------------------- AT24C04 参数 -------------------------
 * ⚠️ 库函数 LHL_I2C_Send7bitAddress() 是把参数直接写进 DR 的, 不会左移
 *    一位, 所以这里必须用"8 位写地址"形式(和 STM32 标准库 EEPROM_ADDRESS
 *    0xA0 的用法一样), 不能填 0x50。
 *
 * 8 位地址 = 1010 A2 A1 P0 R/W:
 *   A2/A1 接地 -> 0xA0; P0 是存储地址的第 8 位:
 *   低 256B(0x000~0x0FF) -> P0 = 0 (0xA0), 高 256B -> P0 = 1 (0xA2)。
 * 页大小 16B。库函数只支持单字节读写, 这里逐字节写, 每次写完等
 * 满一个写周期(tWR max 5ms), 避免跨页回卷和"写周期未完成就发下一笔"。
 * --------------------------------------------------------------- */
#define AT24C04_BASE_ADDR    0xA0u          /* 8 位地址(含 R/W 位位置) */
#define AT24C04_TIMEOUT      10000u
#define AT24C04_WRITE_US     5200u

static uint8_t at24c04_dev_addr(uint16_t addr)
{
    return (uint8_t)(AT24C04_BASE_ADDR | ((addr >> 7) & 0x02u));
}

/* 失败时补一个 STOP, 把总线从"已发 START/地址"的状态里释放出来 */
static void at24c04_bus_release(void)
{
    LHL_I2C_GenerateSTOP(ENABLE);
}

LHL_StatusTypeDef at24c04_write_byte(uint16_t addr, uint8_t data)
{
    uint8_t           buf = data;
    LHL_StatusTypeDef st;

    st = LHL_I2C_Write(&buf, at24c04_dev_addr(addr),
                       (uint16_t)(addr & 0x00FFu), AT24C04_TIMEOUT);
    if (st != LHL_OK)
    {
        at24c04_bus_release();
        return st;
    }

    LHL_Delay_uS(AT24C04_WRITE_US);                     /* tWR: 最长 5ms */
    return LHL_OK;
}

LHL_StatusTypeDef at24c04_read_byte(uint16_t addr, uint8_t *data)
{
    LHL_StatusTypeDef st;

    st = LHL_I2C_Read(data, at24c04_dev_addr(addr),
                      (uint16_t)(addr & 0x00FFu), AT24C04_TIMEOUT);
    if (st != LHL_OK)
    {
        at24c04_bus_release();
    }
    return st;
}

LHL_StatusTypeDef at24c04_write(uint16_t addr, const uint8_t *data, uint16_t len)
{
    uint16_t          i;
    LHL_StatusTypeDef st = LHL_OK;

    for (i = 0u; i < len; i++)
    {
        st = at24c04_write_byte((uint16_t)(addr + i), data[i]);
        if (st != LHL_OK)
        {
            break;
        }
    }
    return st;
}

LHL_StatusTypeDef at24c04_read(uint16_t addr, uint8_t *data, uint16_t len)
{
    uint16_t          i;
    LHL_StatusTypeDef st = LHL_OK;

    for (i = 0u; i < len; i++)
    {
        st = at24c04_read_byte((uint16_t)(addr + i), &data[i]);
        if (st != LHL_OK)
        {
            break;
        }
    }
    return st;
}

void i2c_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 1. Set I2C GPIO multiplexing */
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;              // I2C SCL Floating open output
    GPIO_InitStructure.Current = GPIO_CURRENT_8mA;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.SchmittTrigger = ENABLE;
    GPIO_InitStructure.Alternate = GPIO0_1_AF_SCL;
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_2;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;              // I2C SDA Floating open output
    GPIO_InitStructure.Current = GPIO_CURRENT_8mA;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.SchmittTrigger = ENABLE;
    GPIO_InitStructure.Alternate = GPIO0_2_AF_SDA;
    LHL_GPIO_Init(pGPIO0, &GPIO_InitStructure);

    /* 2. Configure I2C peripheral */
    LHL_I2C_DeInit();                                           /* Reset the I2C peripheral */

    hI2C.Mode = I2C_MODE_MASTER_TRANSMITTER;                    // Host transmitter mode
    hI2C.Size = 1;                                              // Data bulk
    hI2C.Count = 0;                                             // The quantity of data that has been sent
    hI2C.Status = I2C_STATE_IDLE;                               // Initial idle state
    hI2C.RxData = I2C_RX_Data;                                  // Receiving cache
    hI2C.TxData = I2C_TX_Data;                                  // Send cache
    hI2C.Init.Speed = I2C_STANDARD_SPEED;                       // 100KHz Standard I2C Speed
    hI2C.Init.Address = I2C_SLAVE_ADDRESS;                      // Master mode slave address; Slave mode own address
    hI2C.Init.ACK = I2C_ACK_ENABLE;                             // Automatic ACK
    hI2C.Init.AddressMode = I2C_ADDRESSMODE_7BIT;               // 7-bit address
    LHL_I2C_Init(&hI2C);

    /* 3. I2C Clock extension function */
    LHL_I2C_StretchClockCmd(ENABLE);                            /* The clock extension is enabled by default. Here, it is explicitly enabled again. */

//    /* 4. Enable I2C interrupt */
//    LHL_I2C_ITConfig(I2C_IT_EVT|I2C_IT_BUF|I2C_IT_ERR, ENABLE);
//    NVIC_SetPriority(I2C1_EV_IRQn,0);                           /* The highest priority of NVIC is 0. */
//    NVIC_EnableIRQ(I2C1_EV_IRQn);
}
