#ifndef __DATA_H
#define __DATA_H  
#include "./SYSTEM/sys/sys.h"

#define my_buttle_max 200
#define enemy_buttle_max 300

#define enemy_plane_max 10

struct{
	int score;
	//简单记录三个分数
	int score_2;
	int score_3;
	
	int life;
    int bomb;
	
	int my_plane[2];
	int my_buttles[my_buttle_max][2];

	int level;
	int boss[2];
	int boss_life;
	int pace;
	
	int enemy_planes[enemy_plane_max][2];
	int enemy_buttles[enemy_buttle_max][2];
	
	int come_boss;
}interface;

#endif
