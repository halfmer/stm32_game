/**
 ****************************************************************************************************
 * @file        joypad.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-26
 * @brief       ��Ϸ�ֱ� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20200426
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#ifndef __JOYPAD_H
#define __JOYPAD_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* ���� ���� */

#define JOYPAD_CLK_GPIO_PORT            GPIOD
#define JOYPAD_CLK_GPIO_PIN             GPIO_PIN_3
#define JOYPAD_CLK_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOD_CLK_ENABLE(); }while(0)   /* PD��ʱ��ʹ�� */

#define JOYPAD_LAT_GPIO_PORT            GPIOB
#define JOYPAD_LAT_GPIO_PIN             GPIO_PIN_11
#define JOYPAD_LAT_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)    /* PB��ʱ��ʹ�� */

#define JOYPAD_DATA_GPIO_PORT           GPIOB
#define JOYPAD_DATA_GPIO_PIN            GPIO_PIN_10
#define JOYPAD_DATA_GPIO_CLK_ENABLE()   do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)    /* PB��ʱ��ʹ�� */

/******************************************************************************************/

/* �ֱ��������� */
#define JOYPAD_CLK(x)   do{ x ? \
                              HAL_GPIO_WritePin(JOYPAD_CLK_GPIO_PORT, JOYPAD_CLK_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(JOYPAD_CLK_GPIO_PORT, JOYPAD_CLK_GPIO_PIN, GPIO_PIN_RESET); \
                        }while(0)   /* JOYPAD_CLK */

#define JOYPAD_LAT(x)   do{ x ? \
                              HAL_GPIO_WritePin(JOYPAD_LAT_GPIO_PORT, JOYPAD_LAT_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(JOYPAD_LAT_GPIO_PORT, JOYPAD_LAT_GPIO_PIN, GPIO_PIN_RESET); \
                        }while(0)   /* JOYPAD_LATCH */

#define JOYPAD_DATA     HAL_GPIO_ReadPin(JOYPAD_DATA_GPIO_PORT, JOYPAD_DATA_GPIO_PIN)   /* JOYPAD_DATA */

#define RIGHT   128
#define LEFT    64
#define DOWN    32
#define UP      16
#define START   8
#define SELECT  4
#define B_UP    2
#define A_UP    1
                        
/* ��̬���� */
static void joypad_delay(uint16_t t);   /* JOYPAD ��ʱ */

/* �ӿں��� */
void joypad_init(void);     /* JOYPAD ��ʼ�� */
uint8_t joypad_read(void);  /* JOYPAD ��ȡ���� */
uint8_t joypad_Scan(uint8_t mode);
uint8_t debounced_joypad_read(void);
                        
#endif
















