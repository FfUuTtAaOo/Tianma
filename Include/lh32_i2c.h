#ifndef _LH32_I2C_H
#define _LH32_I2C_H

#include "lh32m0xx_lhl.h"

void i2c_init(void);

/* ---------------- AT24C04 (4Kbit = 512Byte, I2C0) ----------------
 * 阻塞式, 逐字节操作; 写一个字节内部会等满一次写周期(约 5ms)。
 * 地址 0x000~0x1FF。器件地址宏 AT24C04_BASE_ADDR 用 8 位写地址形式
 * (默认 0xA0 = 1010 000 0, A2/A1 接地), 不是 7 位的 0x50。
 * ----------------------------------------------------------------- */
LHL_StatusTypeDef at24c04_write_byte(uint16_t addr, uint8_t data);
LHL_StatusTypeDef at24c04_read_byte(uint16_t addr, uint8_t *data);
LHL_StatusTypeDef at24c04_write(uint16_t addr, const uint8_t *data, uint16_t len);
LHL_StatusTypeDef at24c04_read(uint16_t addr, uint8_t *data, uint16_t len);

#endif
