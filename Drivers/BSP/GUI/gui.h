#ifndef _GUI_H
#define _GUI_H
#include "./BSP/GUI/graph.h"
#include "./BSP/GUI/model.h"
#include "./BSP/GUI/rendering.h"
#include "./BSP/JOYPAD/joypad.h"
#include <stdio.h>
#include "string.h"

// ����������ṹ��
typedef struct {
    int x, y;
    int width, height;
    int is_dirty;
} DirtyRect;



//��ʼ��������һ��һ����Ϸ��ֻ��ʹ��һ��
void draw_start_page(void);
void init_play_interface(void);
void draw_end(int *score,int *score_2, int *score_3);
void draw_stop(void);

//����Ⱦ����Ⱦ�������
//��Щ�����ҲҪ��Ⱦ����һ���̶��Ͻ���Ч��
void draw_play_all(int score,int life,int bomb, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2],FrameBuffer *front_buffer, FrameBuffer *back_buffer);


#endif
