#ifndef _GRAPH_H
#define _GRAPH_H
#include "./BSP/GUI/draw_base.h"
#include "math.h"

#define STAR_COUNT      24     // 星星数量
#define SCREEN_WIDTH    480
#define SCREEN_HEIGHT   800

void draw_equal_triangle(int x, int y, int width, int height);

void draw_rectangle(int x, int y, int width, int height);

void draw_left_triangle(int x, int y, int width, int height);

void draw_right_triangle(int x, int y, int width, int height);

void draw_trapezoid(int x, int y, int upper_width, int lower_width, int height);

void draw_reversed_rectangle(int x, int y, int width, int height);

void draw_reversed_equal_triangle(int x, int y, int width, int height);

void draw_reversed_left_triangle(int x, int y, int width, int height);

void draw_reversed_right_triangle(int x, int y, int width, int height);
	
void draw_reversed_trapezoid(int x, int y, int upper_width, int lower_width, int height);

void draw_hexagon(int x, int y, int size, uint16_t color);

void lcd_draw_boss_rectangle(int x, int y, int width, int height, uint16_t color);

//在stm32f1xx_it.c调用中添加了
void update_sys_tick(void);

void draw_poisson_stars(void);

#endif
