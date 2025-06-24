#include "./BSP/GUI/gui.h"



/*--------------------------------------��ʼ��--------------------------------------*/
//��ʼ��������һ��һ����Ϸ��ֻ��ʹ��һ��
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
	//���û�������
/*----------------����----------------*/
	LCD_DrawLine(1,1,479,1);
	LCD_DrawLine(1,40,479,40);
	
	LCD_DrawLine(1,1,1,40);
	LCD_DrawLine(479,1,479,40);
	
	LCD_DrawLine(130,1,130,40);
	
	LCD_ShowString(5,8,90,24,24,"SCROE:");	
	LCD_ShowString(135,8,90,24,24,"LIFE");
    
    LCD_ShowString(300,8,90,24,24,"BOMB");
/*----------------�ײ�----------------*/
    LCD_DrawLine(1,755,479,755);
    LCD_ShowString(5,765,260,24,24,"press 'SEL' to STOP");
}

// game over����
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
	
    //�Ż���������
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

/*--------------------------------------��Ⱦ����--------------------------------------*/
//֡����������Ⱦ
//��������/������Ⱦ
//�ҷ��ӵ���Ⱦ
//�з��ɻ���Ⱦ
//�з��ӵ���Ⱦ

//1. �ҷ��ɻ���Ⱦ
//2. boss��Ⱦ
//3. cross��Ⱦ
void draw_play_title(int score, int life, int bomb){
	//�����Ϣ
	int i=0;
	int start_x = 195;
	
	//LCD_Fill(75,8,130,32,GRAY);
	LCD_ShowxNum(75,8,score,4,24,0);		//��ʾ����
	
	lcd_fill(190,15,226,25,BLACK);
        for(i=0; i<life; i++){	//��ʾ����ֵ
            draw_heart(start_x+i*13, 20);
        }
        if(bomb!=0){
            for(i=0; i<bomb; i++){	//ը������
                draw_heart(380+i*13, 20);
            }            
        }
        else{lcd_fill(375, 15, 388, 30, BLACK);}


}

//���� 0��0
void draw_all_my_buttles(int my_buttles[100][2]){
	int i =0;
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			draw_my_bullet(my_buttles[i][0],my_buttles[i][1]);
		}
	}
}

//���� 0��0
void draw_all_enemy_planes(int enemy_planes[10][2]){
	int i = 0;
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			draw_enemy_plane(enemy_planes[i][0],enemy_planes[i][1]);
		}
	}
}

//���� 0��0
void draw_all_enemy_buttles(int enemy_buttles[300][2]){
	int i =0;
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] != 0){
			draw_enemy_bullet(enemy_buttles[i][0],enemy_buttles[i][1]);
		}
	}
}

////����Ⱦ����Ⱦ���������
////��Щ�����ҲҪ��Ⱦ���ή��Ч��
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
    // ��̬�����洢��һ֡״̬
    static int last_score = -1, last_life = -1, last_bomb = -1;
    static int last_my_plane[2] = {-1, -1};
    static int last_boss[2] = {-1, -1};
    static int first_frame = 1;
    
    // ������ȾĿ��Ϊ��̨������
    set_render_target(back);
    
    // 1. ��Ⱦ���⣨���ڱ仯ʱ��
    if (first_frame || score != last_score || life != last_life || bomb != last_bomb) {
        clear_rect(back, 0, 0, 320, 30);  // �����������
        draw_play_title(score, life, bomb);
        last_score = score;
        last_life = life;
        last_bomb = bomb;
    }
    
    // 2. ��Ⱦ��ҷɻ��������Ƿ��ƶ�����Ⱦ�����ƶ�ʱ�������λ�ã�
    if (!first_frame && (my_plane[0] != last_my_plane[0] || my_plane[1] != last_my_plane[1])) {
        // �ɻ�λ�ñ仯�������λ�ã��ǵ�һ֡ʱ��
        clear_rect(back, last_my_plane[0]-10, last_my_plane[1]-10, 20, 20);  // ����ɻ���С20x20
    }
    // ���۷ɻ��Ƿ��ƶ��������Ƶ�ǰλ�ã�ȷ������ʧ��
    draw_my_plane(my_plane[0], my_plane[1]);
    last_my_plane[0] = my_plane[0];
    last_my_plane[1] = my_plane[1];
    
    // 3. ��ȾBoss�����Ʒɻ��߼���
    if (boss[0] != 0) {
        if (!first_frame && boss[0] != last_boss[0] && boss[1] != last_boss[1]) {
            // Bossλ�ñ仯�������λ�ã��ǵ�һ֡ʱ��
            clear_rect(back, last_boss[0]-25, last_boss[1]-25, 50, 50);  // ����Boss��С50x50
        }
        // ����Boss�Ƿ��ƶ��������Ƶ�ǰλ��
        draw_boss(boss[0], boss[1], 32);
        last_boss[0] = boss[0];
        last_boss[1] = boss[1];
    } else if (last_boss[0] != 0) {
        // Boss��ʧ�������λ��
        clear_rect(back, last_boss[0]-25, last_boss[1]-25, 50, 50);
        last_boss[0] = 0;
        last_boss[1] = 0;
    }
    
    // 4. ��Ⱦ�ӵ��͵л���ÿ�ζ���Ⱦ�������Ż�Ϊֻ��Ⱦ��Ļ�ڵĶ���
    draw_all_my_buttles(my_buttles);
    draw_all_enemy_planes(enemy_planes);
    draw_all_enemy_buttles(enemy_buttles);
    
    // 5. ����������
    swap_buffers(front, back);
    
    first_frame = 0;
}

