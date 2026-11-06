#include "rs485_cmd.h"

static uint8_t  rx_state;
static uint8_t  rx_cmd;
static uint16_t rx_data;

extern volatile uint8_t uart_rx_count;
extern volatile uint8_t uart_tx_count;
extern volatile ZERO_Params_t g_zero;

/* Functions -----------------------------------------------------------------*/
static void proto_ack(uint8_t cmd)
{
    uint8_t frame[5];

    frame[0] = PROTO_HEAD0;
    frame[1] = PROTO_HEAD1;
    frame[2] = (uint8_t)(cmd | 0x80u);
    frame[3] = PROTO_TAIL0;
    frame[4] = PROTO_TAIL1;

    uart_send(frame, sizeof(frame));
}

static void proto_exec(uint8_t cmd, int16_t mv)
{
    float v = (float)mv * 0.001f;

    switch (cmd)
    {
    case PROTO_CMD_CLEAR:
        g_zero.zero_flag = 1;
        break;

    default:
        break;
    }
}

static void proto_feed(uint8_t byte)
{
    switch (rx_state)
    {
    case RX_ST_HEAD0:
        if (byte == PROTO_HEAD0) rx_state = RX_ST_HEAD1;
        break;

    case RX_ST_HEAD1:
        if (byte == PROTO_HEAD1)              rx_state = RX_ST_CMD;
        else if (byte != PROTO_HEAD0)         rx_state = RX_ST_HEAD0;  /* ?? 0xAA ??? */
        break;

    case RX_ST_CMD:
        if (byte == PROTO_CMD_CLEAR)
        {
            rx_cmd   = byte;
            rx_state = RX_ST_TAIL0;
        }
        else
        {
            rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        }
        break;

    case RX_ST_DATA_L:
        rx_data  = byte;
        rx_state = RX_ST_DATA_H;
        break;

    case RX_ST_DATA_H:
        rx_data |= (uint16_t)((uint16_t)byte << 8);
        rx_state = RX_ST_TAIL0;
        break;

    case RX_ST_TAIL0:
        if (byte == PROTO_TAIL0)              rx_state = RX_ST_TAIL1;
        else                                  rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        break;

    case RX_ST_TAIL1:
        if (byte == PROTO_TAIL1)
        {
            proto_exec(rx_cmd, (int16_t)rx_data);
            proto_ack(rx_cmd);
        }
        rx_state = (byte == PROTO_HEAD0) ? RX_ST_HEAD1 : RX_ST_HEAD0;
        break;

    default:
        rx_state = RX_ST_HEAD0;
        break;
    }
}

void uart_process(void)
{
    while (uart_rx_count != uart_tx_count)
    {
        proto_feed(uart_buffer[uart_tx_count++]);
    }
}
