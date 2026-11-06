#ifndef _LH32_RS485_CMD_H
#define _LH32_RS485_CMD_H

#include "lh32m0xx_lhl.h"
#include "lh32_uart.h"

typedef struct {
    float fz_zero_v;
    uint8_t zero_flag;
    float fz_sum;
    uint8_t zero_count;
} ZERO_Params_t;

enum {
    RX_ST_HEAD0 = 0,
    RX_ST_HEAD1,
    RX_ST_CMD,
    RX_ST_DATA_L,
    RX_ST_DATA_H,
    RX_ST_TAIL0,
    RX_ST_TAIL1
};

#define PROTO_HEAD0             0xAAu
#define PROTO_HEAD1             0x55u
#define PROTO_TAIL0             0x0Du
#define PROTO_TAIL1             0x0Au

#define PROTO_CMD_CLEAR         0x30u

void uart_process(void);

#endif
