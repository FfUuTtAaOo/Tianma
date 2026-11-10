#include "lh32_uart.h"
#include "lh32_gpio.h"          /* RS485_TX / RS485_RX: WS3085 方向控制 */

/* ---- 串口引脚(改线只改这几行) ----
 * P1.5 = SIN0(RX), P1.6 = SOUT0(TX), 115200 8N1 */
#define UART_RX_PORT        pGPIO1
#define UART_RX_PIN         GPIO_PIN_5
#define UART_RX_AF          GPIO1_5_AF_SIN0

#define UART_TX_PORT        pGPIO1
#define UART_TX_PIN         GPIO_PIN_6
#define UART_TX_AF          GPIO1_6_AF_SOUT0

#define UART_BAUD_RATE      115200

/* 单次进中断最多取走的字节数: 线路异常时不至于把 CPU 困在中断里 */
#define UART_RX_DRAIN_MAX   32u

/* 连续"查不到中断原因"的次数上限: 超过就关掉 RX 中断保命。
 * 正常情况下 IER 只开了 ERBFI, 不可能走到这里。 */
#define UART_RX_SPURIOUS_MAX 64u

/* ---- RX FIFO (FCR) ----
 * 这颗 UART 与 DesignWare 兼容: 偏移 0x08 读是 IIR, **写是 FCR**。
 * 库函数 LHL_UART_Init 只配波特率/LCR, 从来没写过 FCR, FIFO 是否打开
 * 完全取决于复位值。这里显式打开 16 字节接收 FIFO:
 *   - 触发深度保持 1 字节(bit7:6=00), 中断延迟和现在一样, 不牺牲实时性;
 *   - 主循环里较长的不被打断的段落(读 EEPROM、uart_send 等)期间,
 *     接收最多能攒 16 字节, ISR 晚来几十微秒也不会丢整帧开头。
 * 上电阶段收到的第一条指令正好落在这类窗口里, 所以这条对"首帧无响应"
 * 有直接帮助; 中断里 0x0C(字符超时) 分支本来就已经处理了。 */
#define UART_FCR_RX_EN          0x01u
#define UART_FCR_RX_RESET       0x02u
#define UART_FCR_TX_RESET       0x04u
#define UART_FCR_TRIGGER_1      0x00u

/* DE 拉高后到第一个起始位之间留一点建立时间。
 * WS3085 的 DE 使能只要几十 ns, 但兼容芯片和长线缆会慢一些;
 * 16MHz 下 CoreClockShift=0, 8 次空循环约 2µs, 对 50Hz 上报完全无感。 */
#define RS485_DE_SETTLE()       LHL_Delay_uS(8u)

uint8_t uart_buffer[UART_SIZE] = {0};       // 串口收发缓存
volatile uint8_t uart_rx_count = 0;
volatile uint8_t uart_tx_count = 0;

/* 调试观察用: >0 表示 RX 中断因为空转被自动关闭 */
volatile uint32_t uart_rx_spurious;
volatile uint32_t uart_rx_disabled;

void uart_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;

    /* 上电默认处于接收态: RS485 总线由其他节点驱动时本机不能抢总线 */
    RS485_RX;

    /* Configure UART GPIO multiplexing pins */
    GPIO_InitStructure.Pin = UART_RX_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;          // RO 是推挽输出, 不需要上下拉
    GPIO_InitStructure.SchmittTrigger = ENABLE;
    GPIO_InitStructure.Alternate = UART_RX_AF;
    LHL_GPIO_Init(UART_RX_PORT, &GPIO_InitStructure);                           // UART_RX

    GPIO_InitStructure.Pin = UART_TX_PIN;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Current = GPIO_CURRENT_4mA;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.SchmittTrigger = DISABLE;
    GPIO_InitStructure.Alternate = UART_TX_AF;
    LHL_GPIO_Init(UART_TX_PORT, &GPIO_InitStructure);                           // UART_TX

    /* Set UART parameters */
    UART_InitStructure.UART_BaudRate = UART_BAUD_RATE;                          // The maximum baud rate must be less than the clock frequency / 16
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;                    // data: 8
    UART_InitStructure.UART_StopBits = UART_StopBits_1;                         // stop: 1
    UART_InitStructure.UART_Parity = UART_Parity_None;                          // parity: None
    LHL_UART_Init(pUART0, &UART_InitStructure);

    /* ⚠️ 顺序很重要: 必须先把环形缓冲指针清零/把引脚上电期间的残留字节清掉,
     * 再打开接收中断。main() 里原来在初始化全部结束后才清零这两个指针,
     * 结果是"上电头几十毫秒内收到的第一帧"已经被中断存进缓冲, 随后又被清零,
     * 表现为开机后第一条指令不管是什么都没有回应, 第二条才正常。
     * 现在指针在开中断前就归零, 初始化期间收到的帧会留在缓冲里, 主循环一跑就处理。 */
    uart_rx_count = 0u;
    uart_tx_count = 0u;

    /* 打开并清空 RX/TX FIFO（写 IIR 的地址就是写 FCR, 见上面说明）。
     * 必须先于下面的"清残留字节"和开中断, 否则 FIFO 里上电期间的旧字节
     * 会和主机的第一帧粘在一起。 */
    pUART0->IIR = (UART_FCR_RX_EN | UART_FCR_RX_RESET | UART_FCR_TX_RESET
                   | UART_FCR_TRIGGER_1);

    /* 清掉复位/上电过程中可能残留在接收寄存器里的字节和线路错误标志,
     * 否则一开中断就立刻进一次, 把噪声当成数据帧的开头。 */
    while ((pUART0->LSR & UART_FLAG_DR) != 0u)
    {
        (void)LHL_UART_ReadData(pUART0);
    }
    (void)pUART0->LSR;                                 /* 读 LSR 清 OE/FE/PE/BI */

    /* 开启UART中断并设置优先级 */
    LHL_UART_ITConfig(pUART0, UART_IT_ERBFI, ENABLE);                           // 使能UART0接收中断
    NVIC_ClearPendingIRQ(UART0_IRQn);                                           // 清掉上电残留的 pending
    NVIC_EnableIRQ(UART0_IRQn);                                                 // 开启NVIC中断
    NVIC_SetPriority(UART0_IRQn, 1);                                            // 设置NVIC优先级为1
}

/* UART0 接收中断。
 * ⚠️ 必须先看 IIR 的中断源再决定做什么:
 *   - 收到数据(0x04) / FIFO 字符超时(0x0C) / 接收线路错误(0x06) -> 把数据读走
 *   - 其它原因 -> 读一次 LSR 清标志后返回
 * 早期版本在 default 分支里什么都不做, 结果线路一有错误标志就反复触发中断,
 * CPU 出不了中断, 表现就是"一直进串口中断、主程序不跑"。 */
void UART0_IRQHandler(void)
{
    uint32_t it = (uint32_t)LHL_UART_GetITStatus(pUART0) & 0x0Fu;
    uint8_t  n  = 0u;

    if ((it == UART_IT_RXNE) || (it == 0x0Cu) || (it == UART_IT_ERROR))
    {
        uart_rx_spurious = 0u;

        /* 限次把所有可读字节取空(FIFO 里可能不止一个) */
        while ((n < UART_RX_DRAIN_MAX) && ((pUART0->LSR & UART_FLAG_DR) != 0u))
        {
            uint8_t data = LHL_UART_ReadData(pUART0);
            uint8_t next = (uint8_t)(uart_rx_count + 1u);

            n++;

            if (next != uart_tx_count)              // 还有空位才存, 满了丢新字节
            {
                uart_buffer[uart_rx_count] = data;
                uart_rx_count = next;
            }
        }
        return;
    }

    (void)pUART0->LSR;                              // 读 LSR 清线路错误标志, 防止中断重复触发

    if (++uart_rx_spurious > UART_RX_SPURIOUS_MAX)
    {
        LHL_UART_ITConfig(pUART0, UART_IT_ERBFI, DISABLE);
        NVIC_DisableIRQ(UART0_IRQn);
        uart_rx_disabled = 1u;
    }
}

/* 阻塞式发送: 每写一个字节前先等 THRE, 避免覆盖还没移出的数据。
 * 只在主循环里调用(不要在中断里用)。
 *
 * RS485 半双工方向控制(WS3085, DE/RE 共用一个引脚):
 *   发送前 DE=1 抢占总线 -> 发完必须等 TEMT(移位寄存器也空) 再 DE=0,
 *   否则最后一个字节的停止位会被截断, 从机收到的是坏帧。 */
void uart_send(const uint8_t *data, uint16_t len)
{
    if ((data == 0) || (len == 0u))
    {
        return;
    }

    RS485_TX;                                                   /* 切到发送 */
    RS485_DE_SETTLE();                                          /* 等收发器方向建立 */

    while (len--)
    {
        while ((pUART0->LSR & UART_FLAG_THRE) == 0u)
        {
        }
        LHL_UART_WriteData(pUART0, *data++);
    }

    while ((pUART0->LSR & UART_FLAG_TEMT) == 0u)                /* 最后一个字节完全移出 */
    {
    }

    RS485_RX;                                                   /* 释放总线, 切回接收 */
}

/* 运行时切换波特率(LHL_UART_SetBaudrate 只改 DLL/DLM/DLF, IER 不变)。
 * 调用者必须已经把应答帧发完: 这里再等一次 TEMT, 防止最后一个字节
 * 还在移位寄存器里时就把分频改掉。 */
void uart_set_baud(uint32_t baud)
{
    if (baud == 0u)
    {
        return;
    }

    while ((pUART0->LSR & UART_FLAG_TEMT) == 0u)
    {
    }

    (void)LHL_UART_SetBaudrate(pUART0, baud);
}

/* printf 重定向(见 Include/lh32m0xx_lhl.h, 已关闭库里的默认实现)。
 * MicroLIB 的 printf 是逐字符调 fputc, 所以这里每发一个字节都要自己控制方向;
 * 调试打印用, 命令应答请走 uart_send(整帧一个发送窗口)。 */
int fputc(int ch, FILE *f)
{
    (void)f;

    RS485_TX;
    RS485_DE_SETTLE();

    while ((pUART0->LSR & UART_FLAG_THRE) == 0u)
    {
    }
    LHL_UART_WriteData(pUART0, (uint8_t)ch);
    while ((pUART0->LSR & UART_FLAG_TEMT) == 0u)
    {
    }

    RS485_RX;

    return ch;
}
