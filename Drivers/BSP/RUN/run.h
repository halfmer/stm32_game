#ifndef __RUN_H
#define __RUN_H	
#include "./SYSTEM/sys/sys.h"
#include "./BSP/RUN/util.h"
#include "./BSP/GUI/gui.h"
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/JOYPAD/joypad.h"
#include <stdlib.h>
#include "stm32f1xx_hal.h"


//生成敌人飞机
void generate_enemy_planes(int level, int enemy_planes[10][2]);


//检测操作来更新
void switch_my_act(int* bomb, int my_plane[2],int my_buttles[100][2],int enemy_plane[10][2],int enemy_buttles[100][2]);

//自动更新我的所有子弹
void update_my_buttles(int my_buttles[100][2]);

void update_enemy_buttles(int enemy_buttles[300][2], int level);

//更新敌人飞机位置
void update_enemy_planes(int enemy_planes[10][2], int level);

//炸弹爆炸的能力
void bomb_all_enemy_plane(int *bomb, int my_plane[2],	int enemy_plane[10][2], int my_buttles[100][2], int enemy_buttles[300][2]);

void check_my_plane_to_enemy_plane_collide(int *score,int *life,int *bomb,	int my_plane[2], int enemy_planes[10][2], int my_buttles[200][2], int enemy_buttles[300][2]);
void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[300][2], int enemy_planes[10][2]);

void check_my_plane_to_enemy_buttles_collide(int *life,int *bomb,	int enemy_buttles[300][2],int my_buttles[300][2], int my_plane[2]);

void generate_enemy_buttles(int level, int enemy_plane[10][2],  int enemy_buttles[300][2]);

void generate_boss_buttles(int boss[2],  int enemy_buttles[300][2]);
	
void clear_all_enemy_plane(int my_plane[2],	int enemy_plane[10][2], int my_buttles[100][2], int enemy_buttles[300][2]);

void check_my_buttles_to_boss_collide(int *score, int *boss_life,	int my_buttles[100][2], int boss[2]);

void move_boss(int boss[2], int *pace,int size);
#endif

