#include "./BSP/RUN/run.h"
int left_limit = 2;
int right_limit = 468;
int up_limit = 105;
int down_limit = 750;


//������ <= �ؿ� * 3,	
//һ��ֻ����һ���ɻ�
//���ɷɻ����� => ��Ӧ�ؿ�
void generate_enemy_planes(int level, int enemy_planes[10][2]){
	int i = 0;
	
	// ������ɵصз��ɻ�
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] == 0){
			if(i < level*3){
				if(rand()%99 < level + 3){
					enemy_planes[i][0] = rand()%450 + 14;
					enemy_planes[i][1] = 61;
				}
			}
			break;
		}
	}
}



void switch_my_act(int* bomb, int my_plane[2],int my_buttles[100][2],int enemy_plane[10][2],int enemy_buttles[100][2]){
	int i=0;
    int key=debounced_joypad_read();
	//���֮ǰ����
	lcd_fill(my_plane[0]-14,my_plane[1]-14,	my_plane[0]+14,my_plane[1]+14,BLACK);

	switch(key)
		{
			// right
			case RIGHT:
				if(my_plane[0]+10 < right_limit - 14){
				my_plane[0] = my_plane[0]+10;
			}
			
				break;
			
			//left
			case LEFT:
				if(my_plane[0]-10 > left_limit + 14){
				my_plane[0] = my_plane[0]-10;
			}
				break;
            
            //up
			case UP:
				if(my_plane[1]-10 > up_limit + 20){
				my_plane[1] = my_plane[1]-10;
			}
				break;
            
            //down
			case DOWN:
				if(my_plane[1] < down_limit - 28){
				my_plane[1] = my_plane[1]+10;
			}
				break;
			
			// attack
			case A_UP:				
				for(i=0; i<100; i++){
				if(my_buttles[i][0] == 0){
					my_buttles[i][0] = my_plane[0];
					my_buttles[i][1] = my_plane[1]-15;
					break;	
				}
			}

			default:
				break;
					
		} 
}	
	

void update_my_buttles(int my_buttles[100][2]){
	int i=0;
	
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			//���֮ǰ����
			lcd_fill(my_buttles[i][0]-1,my_buttles[i][1]-1,	my_buttles[i][0]+1,my_buttles[i][1]+1,BLACK);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			//������߽�ʱ����
			if(my_buttles[i][1] < 42){				
				my_buttles[i][0] = 0;
				my_buttles[i][1] = 0;
			}
		}
	}
	
}


void update_enemy_buttles(int enemy_buttles[300][2], int level){
	int i=0;
	
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] != 0){
			//���֮ǰ����
			lcd_fill(enemy_buttles[i][0]-1,enemy_buttles[i][1]-1,	enemy_buttles[i][0]+1,enemy_buttles[i][1]+1,BLACK);
			
			enemy_buttles[i][1] = enemy_buttles[i][1] + level + 1;
			
			//������߽�ʱ����
			if(enemy_buttles[i][1] > 748){				
				enemy_buttles[i][0] = 0;
				enemy_buttles[i][1] = 0;
		
			}
		}
	}
}

void update_enemy_planes(int enemy_planes[10][2], int level){
	int i=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//���֮ǰ����
			lcd_fill(enemy_planes[i][0]-14,enemy_planes[i][1]-14,	enemy_planes[i][0]+14,enemy_planes[i][1]+14,BLACK);
			
			enemy_planes[i][1] = enemy_planes[i][1] + level;
			//������߽�ʱ����
			if(enemy_planes[i][1] > 738){			
				enemy_planes[i][0] = 0;
				enemy_planes[i][1] = 0;
			}
		}
	}
}


void check_my_plane_to_enemy_plane_collide(int *score,int *life,int *bomb,	int my_plane[2], int enemy_planes[10][2], int my_buttles[200][2], int enemy_buttles[300][2]){
	int i=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			//��ģ����ײ���
			if(abs(enemy_planes[i][0] - my_plane[0]) <= 28){
				if(abs(enemy_planes[i][1] - my_plane[1]) <= 28){
					lcd_fill(my_plane[0]-14,my_plane[1]-14,	my_plane[0]+14,my_plane[1]+14,BLACK);
					lcd_fill(enemy_planes[i][0]-14,enemy_planes[i][1]-14,	enemy_planes[i][0]+14,enemy_planes[i][1]+14,BLACK);
				
					my_plane[0] = 240;
					my_plane[1] = 720;
					
					enemy_planes[i][0] = 0;
					enemy_planes[i][1] = 0;
					
                    for(i=0; i<100; i++){
                        if(my_buttles[i][0] != 0){
                            my_buttles[i][0] = 0;
                            my_buttles[i][1] = 0;
                                }
                            }
                    for(i=0; i<300; i++){
                        if(enemy_buttles[i][0] != 0){
                            enemy_buttles[i][0] = 0;
                            enemy_buttles[i][1] = 0;
                                }
                            }
                    
					temp = (*score);
					(*score) = temp+1;
					
					temp = (*life);
					(*life) = temp-1;
                            
                    (*bomb) = 1;
					
					LED0(0);
					delay_ms(20);
					LED0(1);
					
					break;
				}
			}
		}
	}
}


void check_my_buttles_to_enemy_plane_collide(int *score,	int my_buttles[100][2], int enemy_planes[10][2]){
	int i=0;
	int j=0;
	int temp=0;
	
	for(i=0; i<10; i++){
		if(enemy_planes[i][0] != 0){
			for(j=0; j<100; j++){
				//��ײ���
				if(abs(my_buttles[j][0] - enemy_planes[i][0]) <= 15){
					if(abs(my_buttles[j][1] - enemy_planes[i][1]) <= 15){
						lcd_fill(enemy_planes[i][0]-14,enemy_planes[i][1]-14,	enemy_planes[i][0]+14,enemy_planes[i][1]+14,BLACK);

						my_buttles[j][0] = 0;
						my_buttles[j][1] = 0;
						
						enemy_planes[i][0] = 0;
						enemy_planes[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;
						
                      LED1(0);
					  delay_ms(20);
					  LED1(1);
					
						break;
					}
				}
			}
		}
	}
}

void check_my_buttles_to_boss_collide(int *score, int *boss_life,	int my_buttles[100][2], int boss[2]){
	int i = 0;
	int temp = 0;
	for(i=0; i<100; i++){
				//��ײ���
		if(my_buttles[i][0] != 0){
			if(abs(my_buttles[i][0] - boss[0]) <= 41){
					if(abs(my_buttles[i][1] - boss[1]) <= 41){
						lcd_fill(boss[0]-40, boss[1] - 40, boss[0] + 40, boss[1] + 40,BLACK);
					
						my_buttles[i][0] = 0;
						my_buttles[i][1] = 0;
						
						temp = (*score);
						(*score) = temp+1;
						
						temp = (*boss_life);
						(*boss_life) = temp-1;
						
						LED1(0);
					  delay_ms(20);
					  LED1(1);
			
						break;
					}
				}
		}
	}
}


void check_my_plane_to_enemy_buttles_collide(int *life,int *bomb,	int enemy_buttles[300][2],int my_buttles[300][2], int my_plane[2]){
	int temp = 0;
	int i = 0;
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] != 0){
			if(abs(enemy_buttles[i][0] - my_plane[0]) <= 15){
					if(abs(enemy_buttles[i][1] - my_plane[1]) <= 15){
						
						my_plane[0] = 240;
					  my_plane[1] = 720;
						
                        for(i=0; i<100; i++){
                        if(my_buttles[i][0] != 0){
                            my_buttles[i][0] = 0;
                            my_buttles[i][1] = 0;
                                }
                            }
                    for(i=0; i<300; i++){
                        if(enemy_buttles[i][0] != 0){
                            enemy_buttles[i][0] = 0;
                            enemy_buttles[i][1] = 0;
                                }
                            }
						
						temp = (*life);
					 (*life) = temp-1;
                            
                      (*bomb) = 1;
						
						LED0(0);
					  delay_ms(20);
					  LED0(1);
					
					  break;
					}
		}
	}
 }
}

void generate_enemy_buttles(int level, int enemy_plane[10][2],  int enemy_buttles[300][2]){
	int i = 0;
	int j = 0;
	for(i=0; i<10; i++){
		
		if(enemy_plane[i][0] != 0 && rand()%200 < level+1){
			for(j=0; j<300; j++){
				if(enemy_buttles[j][0] == 0){
					enemy_buttles[j][0] = enemy_plane[i][0];
					enemy_buttles[j][1] = enemy_plane[i][1] + 15;
					break;
				}
			}	
		}
	}
}

void generate_boss_buttles(int boss[2],  int enemy_buttles[300][2]){
	int i = 0;
	int j = 0;
	for(i=0; i<10; i++){
		
		if(rand()%200 < 4){
			for(j=0; j<300; j++){
				if(enemy_buttles[j][0] == 0){
					enemy_buttles[j][0] = boss[0] - 120 + i * 24;
					enemy_buttles[j][1] = boss[1] + 15;
					break;
				}
			}	
		}
	}
}

void clear_all_enemy_plane(int my_plane[2],	int enemy_plane[10][2], int my_buttles[100][2], int enemy_buttles[300][2]){
	int i=0;
	
	for(i=0; i<10; i++){
		enemy_plane[i][0] = 0;
		enemy_plane[i][1] = 0;
	}
	
	for(i=0; i<100; i++){
		if(my_buttles[i][0] != 0){
			my_buttles[i][0] = 0;
			my_buttles[i][1] = 0;
		}
	}
	
	for(i=0; i<300; i++){
		if(enemy_buttles[i][0] != 0){
			enemy_buttles[i][0] = 0;
			enemy_buttles[i][1] = 0;
		}
	}
	
	lcd_fill(1,41,479,750,BLACK);
	draw_my_plane(my_plane[0],my_plane[1]);
}

void bomb_all_enemy_plane(int *bomb, int my_plane[2],	int enemy_plane[10][2], int my_buttles[100][2], int enemy_buttles[300][2]){
        int temp;
        int i=0;
    
        bomb_effect_demo(240, 400);
    
        for(i=0; i<10; i++){
            enemy_plane[i][0] = 0;
            enemy_plane[i][1] = 0;
        }
        
        for(i=0; i<100; i++){
            if(my_buttles[i][0] != 0){
                my_buttles[i][0] = 0;
                my_buttles[i][1] = 0;
            }
        }
        
        for(i=0; i<300; i++){
            if(enemy_buttles[i][0] != 0){
                enemy_buttles[i][0] = 0;
                enemy_buttles[i][1] = 0;
            }
        }
    
        temp = (*bomb);
        (*bomb) = temp-1;

        lcd_fill(1,41,479,750,BLACK);
        draw_my_plane(my_plane[0],my_plane[1]);
}


void move_boss(int boss[2], int *pace, int size){
    // ����Bossʵ��ռ�õ������С��������ģ�͵�����
    int body_width = size * 2;       // ������
//    int body_height = size * 3;      // ����߶�
    int wing_width = size * 1.5;     // �����
//    int core_size = size / 2;        // ���Ĵ�С
    
    // ����Boss���ռ�÷�Χ����������Բ�����壩
    int boss_width = body_width + wing_width + 45;  // ���ҳ��+����+����߾�
    int boss_height = body_width + 14;             // ���±߽磨����Բ�����������
    
    // �����һ֡��Bossͼ�Σ������������ȷ����ȫ���ǣ�
    lcd_fill(boss[0] - boss_width/2 - 5, boss[1] - boss_height/2 - 5, 
             boss[0] + boss_width/2 + 5, boss[1] + boss_height/2 + 5, BLACK);
    
    // �ƶ�Boss
    boss[0] += (*pace);
    
    // �߽��飨������Ļ��Ⱥ�Bossʵ�ʴ�С��
    int screen_width = 480;
    int left_boundary = boss_width/2 + 30;       // ��߽磨+30��Ϊ�˰�ȫ�߾ࣩ
    int right_boundary = screen_width - boss_width/2 - 30;  // �ұ߽�
    
    if (boss[0] < left_boundary || boss[0] > right_boundary) {
        // �����߽磬�ı��ƶ�����
        (*pace) = -(*pace);
    }
}
