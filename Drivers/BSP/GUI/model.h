#ifndef _MODEL_H
#define _MODEL_H
#include "./BSP/GUI/draw_base.h"
#include "./BSP/GUI/graph.h"

//21*41
void draw_my_plane(int x, int y);
void draw_enemy_plane(int x ,int y);

//
void draw_boss(int x, int y, int size);

void draw_my_bullet(int x, int y);
void draw_enemy_bullet(int x, int y);

void draw_cross(int x, int y);
void draw_heart(int x, int y);

#endif
