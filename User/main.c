#include <stdlib.h>
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/RUN/run.h"
#include "./BSP/GUI/gui.h"
#include "./BSP/GUI/data.h"

void all_init(void);
void init_interface_info(void);
void init_interface_info_second_time(void);
void draw_all_through_struct(void);

// 在main函数外定义帧缓冲区变量
static FrameBuffer front_buffer = {0};
static FrameBuffer back_buffer = {0};

 int main(void)
 {

     
	all_init();
	draw_all_through_struct();
	delay_ms(500);
	 
	while(1){
		while(1){            
			if(interface.life == 0 || interface.boss_life == 0){break;}
            
            if(debounced_joypad_read()==B_UP && debounced_joypad_read() != A_UP){
                if(interface.bomb != 0){
                    bomb_all_enemy_plane(&(interface.bomb), interface.my_plane,	interface.enemy_planes, interface.my_buttles, interface.enemy_buttles);
                }
           }
            
            if(debounced_joypad_read()==SELECT){draw_stop();LCD_ShowString(5,765,260,24,24,"press 'SEL' to STOP");}
           
			if(interface.score >= 50 && interface.come_boss == 1){
				interface.boss[0] = 210;
				interface.boss[1] = 105;
				interface.come_boss = 0;
				
				clear_all_enemy_plane(interface.my_plane,	interface.enemy_planes, interface.my_buttles, interface.enemy_buttles);
			}
			if(interface.score % 10 == 0){
				interface.level = interface.score/10 + 1;

				if(interface.level > 4){
					interface.level = 4;
				}
			}
			
			switch_my_act(&(interface.bomb),interface.my_plane,interface.my_buttles,interface.enemy_planes,interface.enemy_buttles);
			update_my_buttles(interface.my_buttles);
			
			if(interface.boss[0] == 0){
				update_enemy_planes(interface.enemy_planes, interface.level);
				update_enemy_buttles(interface.enemy_buttles, interface.level);
				
				generate_enemy_planes(interface.level,interface.enemy_planes);
				generate_enemy_buttles(interface.level, interface.enemy_planes, interface.enemy_buttles);
				
				check_my_plane_to_enemy_plane_collide(&(interface.score),&(interface.life),&(interface.bomb),	interface.my_plane,interface.enemy_planes,interface.my_buttles,interface.enemy_buttles);
				check_my_plane_to_enemy_buttles_collide(&(interface.life),&(interface.bomb),	interface.enemy_buttles, interface.my_buttles, interface.my_plane);
				check_my_buttles_to_enemy_plane_collide(&(interface.score),	interface.my_buttles, interface.enemy_planes);
				
			}
			else{
				update_enemy_buttles(interface.enemy_buttles, 1);
				move_boss(interface.boss, &(interface.pace), 32);
				generate_boss_buttles(interface.boss, interface.enemy_buttles);
				check_my_plane_to_enemy_buttles_collide(&(interface.life),&(interface.bomb),	interface.enemy_buttles, interface.my_buttles, interface.my_plane);
				check_my_buttles_to_boss_collide(&(interface.score), &(interface.boss_life),	interface.my_buttles, interface.boss);
			}
				
			
			draw_all_through_struct();	 
			delay_ms(20);
		}	
		
		draw_end(&(interface.score),&(interface.score_2),&(interface.score_3));		
		KEY0_to_skip(); 
		lcd_clear(BLACK);
		//初始界面初始化
		draw_start_page(); 
        KEY0_to_skip();
		lcd_clear(BLACK);
		
		//游玩界面数据初始化
		init_interface_info_second_time();
		
		//游玩界面初始化
		init_play_interface();
		
		draw_all_through_struct();
		delay_ms(500);
	}
}
 

void draw_all_through_struct(void){
	draw_play_all(interface.score,          interface.life,
                  interface.bomb,           interface.my_plane,
                  interface.my_buttles,     interface.boss,
                  interface.enemy_planes,   interface.enemy_buttles,
                  &front_buffer,            &back_buffer);
}


void all_init(void){
    HAL_Init();                                         /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);                 /* 设置时钟, 72Mhz */
    delay_init(72);                                     /* 延时初始化 */
    usart_init(115200);                                 /* 串口初始化为115200 */
    led_init();                                         /* 初始化LED */
    lcd_init();                                         /* 初始化LCD */
	joypad_init();          	//初始化与按键连接的硬件接口
	lcd_clear(BLACK);
	
    init_frame_buffers(&front_buffer, &back_buffer, 480, 800, 16);
    
	//初始界面初始化
	draw_start_page();
	KEY0_to_skip();
	lcd_clear(BLACK);
	
	//游玩界面数据初始化
	init_interface_info();
	
	//游玩界面初始化
	init_play_interface();
}



void init_interface_info(void){
	int i=0;
	
	interface.score = 0;
	interface.score_2 = 0;
	interface.score_3 = 0;
	
	interface.life = 3;
    interface.bomb = 1;
	
	interface.my_plane[0] = 240;	interface.my_plane[1] = 720;
	
	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}
	
	interface.level = 1;
	interface.boss[0] = 0;
	interface.boss[1] = 0;
	interface.boss_life = 20;
	interface.pace = 2;
	interface.come_boss = 1;	
	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}
	
	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}

void init_interface_info_second_time(void){
	int i=0;
	
	interface.life = 3;
    interface.bomb = 1;
	
	interface.my_plane[0] = 240;	interface.my_plane[1] = 720;
	
	for(i=0; i<my_buttle_max; i++){
		interface.my_buttles[i][0] = 0;
		interface.my_buttles[i][1] = 0;
	}
	
	interface.level = 1;
	interface.boss[0] = 0;
	interface.boss[1] = 0;
	interface.boss_life = 20;
	interface.pace = 2;
	interface.come_boss = 1;
		
	for(i=0; i<enemy_plane_max; i++){
		interface.enemy_planes[i][0] = 0;
		interface.enemy_planes[i][1] = 0;
	}
	
	for(i=0; i<enemy_buttle_max; i++){
		interface.enemy_buttles[i][0] = 0;
		interface.enemy_buttles[i][1] = 0;
	}
}
