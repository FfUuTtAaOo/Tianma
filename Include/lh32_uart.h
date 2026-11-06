#ifndef _LH32_UART_H
#define _LH32_UART_H

#include "lh32m0xx_lhl.h"

#define UART_SIZE 256                   /* RX 环形缓冲区长度 */

/* RX 环形缓冲:
 *   uart_rx_count —— 中断里写(写指针)
 *   uart_tx_count —— 主循环里写(读指针, 即已处理到的位置)
 * 两个都是 uint8_t, 天然按 256 回绕; "写指针+1 == 读指针" 表示满。
 * 两个都在中断和主循环两边访问, 必须 volatile。 */
extern uint8_t uart_buffer[UART_SIZE];
extern volatile uint8_t uart_rx_count;
extern volatile uint8_t uart_tx_count;

void uart_init(void);

/* 阻塞式发送一段数据(等 THRE 后再写 THR, 不会覆盖还没发完的字节) */
void uart_send(const uint8_t *data, uint16_t len);

/* 运行时改波特率(指令 0x04)。只改分频, 不动 GPIO/中断配置。
 * 调用前必须保证待发的数据已经完全移出(等 TEMT)。 */
void uart_set_baud(uint32_t baud);

#endif
