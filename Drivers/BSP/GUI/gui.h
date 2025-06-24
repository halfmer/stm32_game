#ifndef _GUI_H
#define _GUI_H
#include "./BSP/GUI/graph.h"
#include "./BSP/GUI/model.h"
#include "./BSP/GUI/rendering.h"
#include "./BSP/JOYPAD/joypad.h"
#include <stdio.h>
#include "string.h"

// 定义脏区域结构体
typedef struct {
    int x, y;
    int width, height;
    int is_dirty;
} DirtyRect;



//初始化函数，一般一次游戏中只会使用一次
void draw_start_page(void);
void init_play_interface(void);
void draw_end(int *score,int *score_2, int *score_3);
void draw_stop(void);

//懒渲染，渲染所有组件
//有些不变的也要渲染，会一定程度上降低效率
void draw_play_all(int score,int life,int bomb, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2],FrameBuffer *front_buffer, FrameBuffer *back_buffer);


#endif
