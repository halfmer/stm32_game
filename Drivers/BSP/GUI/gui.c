#include "./BSP/GUI/gui.h"



/*--------------------------------------初始化--------------------------------------*/
//初始化函数，一般一次游戏中只会使用一次
void draw_start_page(void){
	LCD_ShowString(70+90,80+150,200,24,32,"AIRCRAFT");
	LCD_ShowString(85+90,111+150,200,24,32,"BATTLE");		
	
	draw_my_plane(90+100,180+210);
	draw_my_plane(120+100,180+210);
	draw_my_plane(150+100,180+210);
	
	LCD_ShowString(60+60,263+250,240,24,24,"Press START to start");
    draw_poisson_stars();
}

void init_play_interface(void){
	//设置基础界面
/*----------------顶部----------------*/
	LCD_DrawLine(1,1,479,1);
	LCD_DrawLine(1,40,479,40);
	
	LCD_DrawLine(1,1,1,40);
	LCD_DrawLine(479,1,479,40);
	
	LCD_DrawLine(130,1,130,40);
	
	LCD_ShowString(5,8,90,24,24,"SCROE:");	
	LCD_ShowString(135,8,90,24,24,"LIFE");
    
    LCD_ShowString(300,8,90,24,24,"BOMB");
/*----------------底部----------------*/
    LCD_DrawLine(1,755,479,755);
    LCD_ShowString(5,765,260,24,24,"press 'SEL' to STOP");
}

// game over界面
void draw_end(int *score,int *score_2, int *score_3){
	lcd_clear(BLACK);
	
	LCD_ShowString(70+90,80+120,200,24,32,"GAME OVER");
	LCD_ShowString(70+90,80+120,200,24,32,"GAME OVER");
	LCD_ShowString(85+90,111+150,200,24,24,"FIRST SCORE:");
	LCD_ShowxNum(95+90,140+150,*score,4,24,0);
	
	if(*score_2 == 0 && *score_3 == 0){
		*score_2 = *score;
	}else if(*score_2 != 0 && *score_3 == 0){
		*score_3 = *score_2;
		*score_2 = *score;
        LCD_ShowString(70+90,80+120,200,24,32,"GAME OVER");
        LCD_ShowString(85+90,111+150,200,24,24,"FIRST SCORE:");
        LCD_ShowxNum(95+90,140+150,*score_3,4,24,0);
		LCD_ShowString(85+90,111+220,200,24,24,"SECOND SCORE:");
		LCD_ShowxNum(95+90,140+220,*score_2,4,24,0);	
	}else if(*score_2 != 0 && *score_2 != 0){
        LCD_ShowString(70+90,80+120,200,24,32,"GAME OVER");
        LCD_ShowString(85+90,111+150,200,24,24,"FIRST SCORE:");
        LCD_ShowxNum(95+90,140+150,*score_3,4,24,0);
		LCD_ShowString(85+90,111+220,200,24,24,"SECOND SCORE:");
		LCD_ShowxNum(95+90,140+220,*score_2,4,24,0);	
		LCD_ShowString(85+50,111+290,200,24,24,"THE LASTEST SCORE:");
		LCD_ShowxNum(95+90,140+290,*score,4,24,0);	
	}
	*score = 0;
	
	draw_my_plane(90+90,260+300);
	draw_my_plane(120+90,260+300);
	draw_my_plane(150+90,260+300);
	
    //优化成随机填充
    draw_poisson_stars();
    
    LCD_ShowString(60+40,263+350,300,24,24,"Press START to CONTINUE");
}

void draw_stop(void){
    LCD_ShowString(340,761,200,24,32,"STOPING");
    LCD_ShowString(2,765,300,24,24,"press 'STA' to CONTINUE");
    while(1)
    {   
        if(debounced_joypad_read() ==  START){
        lcd_fill(0,761,480,800,BLACK);
        return;
        }
    }
}

/*--------------------------------------渲染函数--------------------------------------*/
//帧动画调用渲染
//包含分数/生命渲染
//我方子弹渲染
//敌方飞机渲染
//敌方子弹渲染

//1. 我方飞机渲染
//2. boss渲染
//3. cross渲染
void draw_play_title(int score, int life, int bomb){
	//填充信息
	int i=0;
	int start_x = 195;
	
	//LCD_Fill(75,8,130,32,GRAY);
	LCD_ShowxNum(75,8,score,4,24,0);		//显示分数
	
	lcd_fill(190,15,226,25,BLACK);
        for(i=0; i<life; i++){	//显示生命值
            draw_heart(start_x+i*13, 20);
        }
        if(bomb!=0){
            for(i=0; i<bomb; i++){	//炸弹数量
                draw_heart(380+i*13, 20);
            }            
        }
        else{lcd_fill(375, 15, 388, 30, BLACK);}


}

//过滤 0，0
void draw_all_my_buttles(int my_buttles[100][2]){
	int i =0;
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
	}
}

//过滤 0，0
void draw_all_enemy_planes(int enemy_planes[10][2]){
	int i = 0;
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			draw_enemy_plane(enemy_planes[i][0],enemy_planes[i][1]);
		}
	}
}

//过滤 0，0
void draw_all_enemy_buttles(int enemy_buttles[300][2]){
	int i =0;
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] != 0){
			draw_enemy_bullet(enemy_buttles[i][0],enemy_buttles[i][1]);
		}
	}
}

////懒渲染，渲染所有组件，
////有些不变的也要渲染，会降低效率
//void draw_play_all(int score,int life,int bomb, int my_plane[2], int my_buttles[100][2], int boss[2], int enemy_planes[10][2], int enemy_buttles[300][2])
//    {
//	draw_play_title(score,life,bomb);
//	
//	draw_my_plane(my_plane[0],my_plane[1]);
//	draw_all_my_buttles(my_buttles);
//	if(boss[0]!= 0){
//		draw_boss(boss[0],boss[1]);
//	}
//	draw_all_enemy_planes(enemy_planes);
//	draw_all_enemy_buttles(enemy_buttles);
//}

void draw_play_all(int score, int life, int bomb, 
                        int my_plane[2], int my_buttles[100][2], 
                        int boss[2], int enemy_planes[10][2], 
                        int enemy_buttles[300][2],
                        FrameBuffer *front, FrameBuffer *back) {
    // 静态变量存储上一帧状态
    static int last_score = -1, last_life = -1, last_bomb = -1;
    static int last_my_plane[2] = {-1, -1};
    static int last_boss[2] = {-1, -1};
    static int first_frame = 1;
    
    // 设置渲染目标为后台缓冲区
    set_render_target(back);
    
    // 1. 渲染标题（仅在变化时）
    if (first_frame || score != last_score || life != last_life || bomb != last_bomb) {
        clear_rect(back, 0, 0, 320, 30);  // 假设标题区域
        draw_play_title(score, life, bomb);
        last_score = score;
        last_life = life;
        last_bomb = bomb;
    }
    
    // 2. 渲染玩家飞机（无论是否移动都渲染，但移动时先清除旧位置）
    if (!first_frame && (my_plane[0] != last_my_plane[0] || my_plane[1] != last_my_plane[1])) {
        // 飞机位置变化：清除旧位置（非第一帧时）
        clear_rect(back, last_my_plane[0]-10, last_my_plane[1]-10, 20, 20);  // 假设飞机大小20x20
    }
    // 无论飞机是否移动，都绘制当前位置（确保不消失）
    draw_my_plane(my_plane[0], my_plane[1]);
    last_my_plane[0] = my_plane[0];
    last_my_plane[1] = my_plane[1];
    
    // 3. 渲染Boss（类似飞机逻辑）
    if (boss[0] != 0) {
        if (!first_frame && boss[0] != last_boss[0] && boss[1] != last_boss[1]) {
            // Boss位置变化：清除旧位置（非第一帧时）
            clear_rect(back, last_boss[0]-25, last_boss[1]-25, 50, 50);  // 假设Boss大小50x50
        }
        // 无论Boss是否移动，都绘制当前位置
        draw_boss(boss[0], boss[1], 32);
        last_boss[0] = boss[0];
        last_boss[1] = boss[1];
    } else if (last_boss[0] != 0) {
        // Boss消失：清除旧位置
        clear_rect(back, last_boss[0]-25, last_boss[1]-25, 50, 50);
        last_boss[0] = 0;
        last_boss[1] = 0;
    }
    
    // 4. 渲染子弹和敌机（每次都渲染，但可优化为只渲染屏幕内的对象）
    draw_all_my_buttles(my_buttles);
    draw_all_enemy_planes(enemy_planes);
    draw_all_enemy_buttles(enemy_buttles);
    
    // 5. 交换缓冲区
    swap_buffers(front, back);
    
    first_frame = 0;
}

