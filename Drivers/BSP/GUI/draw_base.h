#ifndef _DRAW_BASE_H
#define _DRAW_BASE_H
#include "./BSP/LCD/lcd.h"


//»­Í¼º¯Êý£¬GUI°æ
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawPoint(int x,int y);
void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len,uint8_t size, uint8_t mode);
uint32_t LCD_Pow(uint8_t m, uint8_t n);

#endif
