#include "./BSP/RUN/run.h"
int left_limit = 2;
int right_limit = 468;
int up_limit = 105;
int down_limit = 750;


//敌人数 <= 关卡 * 3,	
//一次只生成一个飞机
//生成飞机概率 => 对应关卡
void generate_enemy_planes(int level, int enemy_planes[10][2]){
	int i = 0;
	
	// 随机生成地敌方飞机
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
	//清除之前所画
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
			//清除之前所画
			lcd_fill(my_buttles[i][0]-1,my_buttles[i][1]-1,	my_buttles[i][0]+1,my_buttles[i][1]+1,BLACK);
			
			my_buttles[i][1] = my_buttles[i][1] - 3;
			
			//当到达边界时销毁
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
			//清除之前所画
			lcd_fill(enemy_buttles[i][0]-1,enemy_buttles[i][1]-1,	enemy_buttles[i][0]+1,enemy_buttles[i][1]+1,BLACK);
			
			enemy_buttles[i][1] = enemy_buttles[i][1] + level + 1;
			
			//当到达边界时销毁
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
			//清除之前所画
			lcd_fill(enemy_planes[i][0]-14,enemy_planes[i][1]-14,	enemy_planes[i][0]+14,enemy_planes[i][1]+14,BLACK);
			
			enemy_planes[i][1] = enemy_planes[i][1] + level;
			//当到达边界时销毁
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
			//盒模型碰撞检测
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
				//碰撞检测
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
				//碰撞检测
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
    // 计算Boss实际占用的区域大小（根据新模型调整）
    int body_width = size * 2;       // 主体宽度
//    int body_height = size * 3;      // 主体高度
    int wing_width = size * 1.5;     // 翅膀宽度
//    int core_size = size / 2;        // 核心大小
    
    // 计算Boss最大占用范围（包括翅膀和圆形主体）
    int boss_width = body_width + wing_width + 45;  // 左右翅膀+主体+额外边距
    int boss_height = body_width + 14;             // 上下边界（根据圆形主体调整）
    
    // 清除上一帧的Boss图形（扩大清除区域，确保完全覆盖）
    lcd_fill(boss[0] - boss_width/2 - 5, boss[1] - boss_height/2 - 5, 
             boss[0] + boss_width/2 + 5, boss[1] + boss_height/2 + 5, BLACK);
    
    // 移动Boss
    boss[0] += (*pace);
    
    // 边界检查（考虑屏幕宽度和Boss实际大小）
    int screen_width = 480;
    int left_boundary = boss_width/2 + 30;       // 左边界（+30是为了安全边距）
    int right_boundary = screen_width - boss_width/2 - 30;  // 右边界
    
    if (boss[0] < left_boundary || boss[0] > right_boundary) {
        // 碰到边界，改变移动方向
        (*pace) = -(*pace);
    }
}
