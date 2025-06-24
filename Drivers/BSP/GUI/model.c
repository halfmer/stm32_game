#include "./BSP/GUI/model.h"

extern int big_trigon_width;
extern int big_trigon_height;

extern int small_trigon_width;
extern int small_trigon_height;

extern int cross_width; 
extern int cross_height;

extern int heart_width;
extern int heart_height;

extern int buttle_width; 
extern int buttle_height;

extern int star_width;
extern int star_height;

/*---------------------------------模型设计---------------------------------*/
void draw_my_plane(int x, int y){
	draw_equal_triangle(x, y - 10, 6, 4);
	draw_rectangle(x - 2, y - 10, 4, 20);
	draw_left_triangle(x - 2, y + 2, 12, 9);
	draw_right_triangle(x + 2, y + 2, 12, 9);
	draw_trapezoid(x, y + 10, 6, 14, 4);
	
}

void draw_enemy_plane(int x ,int y){
	draw_reversed_equal_triangle(x, y + 10, 6, 4);
	draw_reversed_rectangle(x - 2, y - 10, 4, 20);
	draw_reversed_left_triangle(x + 2, y- 2, 12, 9);
	draw_reversed_right_triangle(x - 2, y - 2, 12, 9);
	draw_reversed_trapezoid(x, y - 10, 6, 14, 4);
}

void draw_boss(int x, int y, int size){
//	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, x7, y7, x8, y8, x9, y9, x10, y10,
//		x11, y11, x12, y12, x13, y13, x14, y14, x15, y15, x16, y16, x17, y17, x18, y18, x19, y19,
//	x20, y20, x21, y21, x22, y22;
//	
//	x1 = x - 15;
//	y1 = y + 40;
//	
//	x2 = x + 15;
//	y2 = y + 40;
//	
//	x3 = x - 20;
//	y3 = y + 20;
//	
//	x4 = x + 20;
//	y4 = y + 20;
//	
//	x5 = x3;
//	y5 = y3 - 5;
//	
//	x6 = x4;
//	y6 = y4 - 5;
//	
//	x7 = x5;
//	y7 = y5 - 10;
//	
//	x8 = x6;
//	y8 = y6 - 10;
//	
//	x9 = x7;
//	y9 = y7 - 30;
//	
//	x10 = x8;
//	y10 = y8 - 30;
//	
//	x11 = x9;
//	y11 = y9 - 10;
//	
//	x12 = x10;
//	y12 = y10 - 10;
//	
//	x13 = x11;
//	y13 = y11 - 5;
//	
//	x14 = x12;
//	y14 = y12 - 5;
//	
//	
//	x15 = x5 - 10;
//	y15 = y5;
//	
//	x16 = x6 + 10;
//	y16 = y6;
//	
//	x17 = x7 - 10;
//	y17 = y7;
//	
//	x18 = x8 +10;
//	y18 = y8;
//	
//	x19 = x9 - 10;
//	y19 = y9;
//	
//	x20 = x10 + 10;
//	y20 = y10;
//	
//	x21 = x11 - 10;
//	y21 = y11;
//	
//	x22 = x12 + 10;
//	y22 = y12;
//	
//	LCD_DrawLine(x1, y1, x2, y2);
//	LCD_DrawLine(x1, y1, x3, y3);
//	LCD_DrawLine(x2, y2, x4, y4);
//	
//	LCD_DrawLine(x3, y3, x13, y13);
//	LCD_DrawLine(x4, y4, x14, y14);
//	LCD_DrawLine(x13, y13, x14, y14);
//	
//	LCD_DrawLine(x5, y5, x15, y15);
//	LCD_DrawLine(x7, y7, x17, y17);
//	
//	LCD_DrawLine(x6, y6, x16, y16);
//	LCD_DrawLine(x8, y8, x18, y18);
//	
//	LCD_DrawLine(x9, y9, x19, y19);
//	LCD_DrawLine(x11, y11, x21, y21);
//	
//	LCD_DrawLine(x10, y10, x20, y20);
//	LCD_DrawLine(x12, y12, x22, y22);
//	
//	LCD_DrawLine(x15, y15 + 10, x17, y17 - 10);
//	LCD_DrawLine(x15, y15 + 10, x15 - 10, y15 + 10);
//	LCD_DrawLine(x17, y17 - 10, x17 - 10, y17 - 10);
//	LCD_DrawLine(x15 - 10, y15 + 10, x17 - 10, y17 - 10);
//	
//	LCD_DrawLine(x19, y19 + 10, x21, y21 - 5);
//	LCD_DrawLine(x19, y19 + 10, x19 - 10, y19 + 10);
//	LCD_DrawLine(x21, y21 - 5, x21 - 10, y21 - 5);
//	LCD_DrawLine(x19 - 10, y19 + 10, x21 - 10, y21 - 5);
//	
//	LCD_DrawLine(x16, y16 + 10, x18, y18 - 10);
//	LCD_DrawLine(x16, y16 + 10, x16 + 10, y16 + 10);
//	LCD_DrawLine(x18, y18 - 10, x18 + 10, y18 - 10);
//	LCD_DrawLine(x16 + 10, y16 + 10, x18 + 10, y18 - 10);
//	
//	LCD_DrawLine(x20, y20 + 10, x22, y22 - 5);
//	LCD_DrawLine(x20, y20 + 10, x20 + 10, y20 + 10);
//	LCD_DrawLine(x22, y22 - 5, x22 + 10, y22 - 5);
//	LCD_DrawLine(x20 + 10, y20 + 10, x22 + 10, y22 - 5);
//	
 // 主色调
    uint16_t main_color = YELLOW;    // 主体颜色
    uint16_t accent_color = RED;     // 强调色（如武器、能量点）
    uint16_t detail_color = WHITE;   // 细节色（如高光、装饰）
    
    // 计算基础尺寸
    int body_width = size * 2;       // 主体宽度
    int body_height = size * 3;      // 主体高度
    int wing_width = size * 1.5;     // 翅膀宽度
//    int wing_height = size * 2;      // 翅膀高度
    int core_size = size / 2;        // 核心大小
    
    // 绘制主体
//    lcd_draw_boss_rectangle(x - body_width/2, y - body_height/2 + 23, body_width, body_height-47, main_color);
    lcd_draw_circle(x, y, body_width/4, main_color);  // 中心圆
    lcd_draw_circle(x,y,body_width/2+7,main_color);
    
    // 绘制翅膀（斜角三角形）
    lcd_draw_line(x - body_width/2, y - body_height/4, 
                 x - body_width/2 - wing_width, y, main_color);
    lcd_draw_line(x - body_width/2, y + body_height/4, 
                 x - body_width/2 - wing_width, y, main_color);
    
    lcd_draw_line(x + body_width/2, y - body_height/4, 
                 x + body_width/2 + wing_width, y, main_color);
    lcd_draw_line(x + body_width/2, y + body_height/4, 
                 x + body_width/2 + wing_width, y, main_color);
    
    // 绘制核心（发光效果）
    lcd_draw_circle(x, y, core_size, accent_color);
    lcd_draw_circle(x, y, core_size/2, detail_color);
    
    
    // 绘制细节装饰（六边形）
    draw_hexagon(x - body_width/4 - 5, y, size/3, detail_color);
    draw_hexagon(x + body_width/4 + 5, y, size/3, detail_color);
    
    // 绘制能量线条（发光效果）
    for (int i = 0; i < 8; i++) {
        int angle = i * 45;
        int end_x = x + (body_width/2 + size/4) * cos(angle * 3.14159f / 180);
        int end_y = y + (body_width/2 + size/4) * sin(angle * 3.14159f / 180);
        lcd_draw_line(x, y, end_x, end_y, detail_color);
    }
}



void draw_my_bullet(int x, int y){
	lcd_draw_point(x, y-1, MAGENTA);
	lcd_draw_point(x-1, y, MAGENTA);
	lcd_draw_point(x, y, MAGENTA);
	lcd_draw_point(x+1, y, MAGENTA);
	lcd_draw_point(x-1, y+1, MAGENTA);
	lcd_draw_point(x, y+1, MAGENTA);
	lcd_draw_point(x+1, y+1, MAGENTA);
//	LCD_DrawPoint(x,y-1);
//
//	LCD_DrawPoint(x-1,y);
//	LCD_DrawPoint(x,y);
//	LCD_DrawPoint(x+1,y);
//
//	LCD_DrawPoint(x-1,y+1);
//	LCD_DrawPoint(x,y+1);
//	LCD_DrawPoint(x+1,y+1);
}

void draw_enemy_bullet(int x, int y){
	lcd_draw_point(x-1,y-1,GREEN);
	lcd_draw_point(x,y-1,GREEN);
	lcd_draw_point(x+1,y-1,GREEN);
	
	lcd_draw_point(x-1,y,GREEN);
	lcd_draw_point(x,y,GREEN);
	lcd_draw_point(x+1,y,GREEN);

	lcd_draw_point(x,y+1,GREEN);
}

//画十字，用于结算界面点缀
void draw_cross(int x, int y){
	LCD_DrawLine(x-cross_width/2,y-cross_height/2, x+cross_width/2,y+cross_height/2);
	LCD_DrawLine(x-cross_width/2,y+cross_height/2, x+cross_width/2,y-cross_height/2);
}

void draw_heart(int x, int y){
	LCD_DrawLine(x-heart_width/2,y-heart_height/2, x+heart_width/2,y+heart_height/2);
	LCD_DrawLine(x-heart_width/2,y+heart_height/2, x+heart_width/2,y-heart_height/2);
	
	LCD_DrawLine(x-heart_width/2,y, x+heart_width/2,y);
	LCD_DrawLine(x,y+heart_height/2, x,y-heart_height/2);
}

