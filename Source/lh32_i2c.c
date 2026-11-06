#include "lh32_i2c.h"

/* Global --------------------------------------------------------------------*/
I2C_HandleTypeDef hI2C;

/* Extern --------------------------------------------------------------------*/
extern uint8_t I2C_RX_Data[10];
extern uint8_t I2C_TX_Data[10];

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
