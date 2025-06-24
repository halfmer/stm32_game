/**
 ****************************************************************************************************
 * @file        joypad.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-26
 * @brief       游戏手柄 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200426
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "./BSP/JOYPAD/joypad.h"
#include "./BSP/RUN/util.h"
#include "./SYSTEM/delay/delay.h"

// 系统时间计数器，单位：毫秒
volatile uint32_t system_tick = 0;
/**
 * 定时器中断服务函数
 * 每1毫秒被调用一次，更新系统时间计数器
 */
void timer_isr(void) {
    system_tick++;
}

/**
 * 获取系统时间
 * @return 当前系统时间戳(毫秒)
 */
uint32_t get_system_time(void) {
    uint32_t tick;
    
    // 为了避免在读取过程中被中断更新，需要禁用中断
    __disable_irq();
    tick = system_tick;
    __enable_irq();
    
    return tick;
}

/**
 * @brief       初始化手柄接口
 * @param       无
 * @retval      无
 */
void joypad_init(void)
{
    JOYPAD_CLK_GPIO_CLK_ENABLE();  /* CLK   所在IO时钟初始化 */
    JOYPAD_LAT_GPIO_CLK_ENABLE();  /* LATCH 所在IO时钟初始化 */
    JOYPAD_DATA_GPIO_CLK_ENABLE(); /* DATA  所在IO时钟初始化 */

    GPIO_InitTypeDef gpio_init_struct;
    gpio_init_struct.Pin = JOYPAD_CLK_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(JOYPAD_CLK_GPIO_PORT, &gpio_init_struct); /* JOYPAD_CLK  引脚模式设置 */

    gpio_init_struct.Pin = JOYPAD_LAT_GPIO_PIN;
    HAL_GPIO_Init(JOYPAD_LAT_GPIO_PORT, &gpio_init_struct); /* JOYPAD_LAT  引脚模式设置 */

    gpio_init_struct.Pin = JOYPAD_DATA_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;
    gpio_init_struct.Pull = GPIO_PULLUP;
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(JOYPAD_DATA_GPIO_PORT, &gpio_init_struct); /* JOYPAD_DATA 引脚模式设置 */
}

/**
 * @brief       手柄延迟函数
 * @param       t    : 要延时的时间
 * @retval      无
 */
void joypad_delay(uint16_t t)
{
    // 使用硬件定时器实现更精确的延时
    // 这里仅为示例，具体实现取决于硬件平台
    uint16_t i;
    for(i=0; i < t; i++){
        // 等待一个系统时钟周期
        __asm("nop");
        }
}

/**
 * @brief       读取手柄按键值
 *   @note      FC手柄数据输出格式:
 *              每给一个脉冲,输出一位数据,输出顺序:
 *              A -> B -> SELECT -> START -> UP -> DOWN -> LEFT -> RIGHT.
 *              总共8位, 对于有C按钮的手柄, 按下C其实就等于 A + B 同时按下.
 *              按下是1,松开是0.
 * @param       无
 * @retval      按键结果, 格式如下:
 *              [7]:右
 *              [6]:左
 *              [5]:下
 *              [4]:上
 *              [3]:Start
 *              [2]:Select
 *              [1]:B
 *              [0]:A
 */
uint8_t joypad_read(void)
{
    volatile uint8_t temp = 0;
    uint8_t t;
    JOYPAD_LAT(1);          /* 锁存当前状态 */
    joypad_delay(80);
    JOYPAD_LAT(0);

    for (t = 0; t < 8; t++) /* 移位输出数据 */
    {
        temp >>= 1;

        if (JOYPAD_DATA == 0)
        {
            temp |= 0x80;   /* LOAD之后，就得到第一个数据 */
        }

        JOYPAD_CLK(1);      /* 每给一次脉冲，收到一个数据 */
        joypad_delay(80);
        JOYPAD_CLK(0);
        joypad_delay(80);
    }
    return temp;
}


//按键模式，1表示可以连续按，0表示不支持连续按
uint8_t joypad_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;
    uint8_t key_value;
    uint16_t timeout = 0;
    
    if (mode) key_up = 1;
    
    key_value = debounced_joypad_read();
    
    if (key_up && (key_value == RIGHT || key_value == LEFT || key_value == A_UP || key_value == B_UP || key_value == START))
    {
        joypad_delay(10);
        key_up = 0;
        
        // 再次读取确认按键，添加超时处理
        while (timeout < 1000) {
            key_value = debounced_joypad_read();
            if (key_value == RIGHT) return RIGHT;
            else if (key_value == LEFT) return LEFT;
            else if (key_value == A_UP) return A_UP;
            else if (key_value == B_UP) return B_UP;
            else if (key_value == START) return START;
            
            timeout++;
            joypad_delay(1);
        }
    }
    else if (key_value != RIGHT && key_value != LEFT && key_value != A_UP && key_value != B_UP && key_value != START)
    {
        key_up = 1;
    }
    
    return 0;
}

uint8_t debounced_joypad_read(void) {
    uint8_t reading1 = joypad_read();
    joypad_delay(20);  // 延时
    uint8_t reading2 = joypad_read();
    
    // 如果两次读取结果相同，认为是有效的按键
    if (reading1 == reading2) {
        return reading1;
    }
    
    return 0;  // 读取不一致，返回无按键
}
