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

extern volatile ZERO_Params_t g_zero;

/* ---------------------------- 帧格式 ----------------------------
 *   AA 55 <cmd> [payload] 0D 0A
 *   cmd 应答 = cmd | 0x80
 *   数据帧 cmd = 0x02(连续发送) / 0x03(单次采集)
 * ----------------------------------------------------------------- */
#define PROTO_HEAD0             0xAAu
#define PROTO_HEAD1             0x55u
#define PROTO_TAIL0             0x0Du
#define PROTO_TAIL1             0x0Au

#define PROTO_CMD_STOP          0x01u   /* 停止连续发送      -> ACK 81 */
#define PROTO_CMD_START         0x02u   /* 开始连续发送      -> 数据帧 02 */
#define PROTO_CMD_SINGLE        0x03u   /* 单次采集          -> 数据帧 03 */
#define PROTO_CMD_BAUD          0x04u   /* 切波特率 + 1B 参数 -> 先 ACK 84 再切换 */
#define PROTO_CMD_COEF          0x20u   /* 写系数 + 1B 序号 + 4B float -> ACK A0 */
#define PROTO_CMD_ZERO          0x30u   /* 清零(采 20 点取平均)-> ACK B0 */
#define PROTO_CMD_OUT_HEX       0x31u   /* HEX 格式输出      -> ACK B1 */
#define PROTO_CMD_OUT_ASCII     0x32u   /* ASCII 格式输出    -> ACK B2 */
#define PROTO_CMD_UNIT_KG       0x33u   /* 单位 kg           -> ACK B3 */
#define PROTO_CMD_RAW_MV        0x34u   /* 原始电压值(mV)    -> ACK B4 */
#define PROTO_CMD_UNIT_N        0x35u   /* 单位 N (kg×9.80665)-> ACK B5 */
#define PROTO_CMD_ZERO_CANCEL   0x36u   /* 取消清零          -> ACK B6 */

void uart_process(void);

/* 上电初始化: 从 AT24C04 读回 a/b/c 系数(全 F 或读失败时保留默认值)。
 * 必须在 i2c_init() 之后调用。 */
void rs485_init(void);

/* 主循环每来一个新 ADC 采样调用一次(传清零后的电压 mV)。
 * 连续发送 / 单次采集的应答都在这里按当前输出格式发出去。 */
void rs485_report(float voltage_mv);

#endif
