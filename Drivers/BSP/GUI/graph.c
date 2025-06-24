#include "./BSP/GUI/graph.h"
#include "./SYSTEM/sys/sys.h"
// ʹ��SysTick��Ϊʱ��Դ
static uint32_t sys_tick = 0;

int big_trigon_width = 21;
int big_trigon_height = 35;

int small_trigon_width = 11;
int small_trigon_height = 11;

int cross_width = 15; 
int cross_height = 15;

int heart_width = 11;
int heart_height = 11;

int buttle_width = 3; 
int buttle_height = 3;

int star_width = 5;
int star_height = 9;

/*-------------------------------------�����ͼ��-------------------------------------*/
//�ȱ�������
void draw_equal_triangle(int x, int y, int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x;
	y1 = y - height;
	
	x2 = x - width / 2;
	y2 = y;
	
	x3 = x + width / 2;
	y3 = y;
	
	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	//lcd_draw_line(x2,y2,x3,y3);
}

//���������Σ����ױ�ˮƽ�����㳯�ϵ������Σ�
void draw_forward_trigon(int x,int y,int width, int height){
	int x1,y1,x2,y2,x3,y3;
	x1 = x-width/2;	y1 = y;
	x2 = x;	y2 = y - height;
	x3 = x+width/2;	y3 = y;
	
	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	lcd_draw_line(x2,y2,x3,y3,BLUE);
}

//����
void draw_rectangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x;
	y1 = y;

	x2 = x + width;
	y2 = y;

	x3 = x1;
	y3 = y + height;

	x4 = x2;
	y4 = y3;

	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	lcd_draw_line(x4,y4,x2,y2,BLUE);
	lcd_draw_line(x4,y4,x3,y3,BLUE);
}

//����ߵ�������
void draw_left_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	x1 = x;
	y1 = y;

	x2 = x - width;
	y2 = y;

	x3 = x;
	y3 = y - height;

	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	lcd_draw_line(x2,y2,x3,y3,BLUE);
}

//���ұߵ�������
void draw_right_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	x1 = x;
	y1 = y;

	x2 = x + width;
	y2 = y;

	x3 = x;
	y3 = y - height;

	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	lcd_draw_line(x2,y2,x3,y3,BLUE);
}

//����
void draw_trapezoid(int x, int y, int upper_width, int lower_width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x - upper_width/2;
	y1 = y;

	x2 = x + upper_width/2;
	y2 = y;

	x3 = x - lower_width/2;
	y3 = y + height;

	x4 = x + lower_width/2;
	y4 = y + height;

	lcd_draw_line(x1,y1,x2,y2,BLUE);
	lcd_draw_line(x1,y1,x3,y3,BLUE);
	lcd_draw_line(x4,y4,x2,y2,BLUE);
	lcd_draw_line(x4,y4,x3,y3,BLUE);

}

/*-------------------------------------�з���ͼ��-------------------------------------*/
//����
void draw_reversed_rectangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x;
	y1 = y;

	x2 = x + width;
	y2 = y;

	x3 = x1;
	y3 = y + height;

	x4 = x2;
	y4 = y3;

	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x4,y4,x2,y2);
	LCD_DrawLine(x4,y4,x3,y3);
}

//�ȱ�������
void draw_reversed_equal_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	
	x1 = x - width / 2;
	y1 = y;
	
	x2 = x + width / 2;
	y2 = y;
	
	x3 = x;
	y3 = y + height;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
	
}

//��ߵ�������
void draw_reversed_left_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	
	x1 = x;
	y1 = y;
	
	x2 = x + width;
	y2 = y;
	
	x3 = x;
	y3 = y + height;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
	
}

//�ұߵ�������
void draw_reversed_right_triangle(int x, int y, int width, int height){
	int x1, y1, x2, y2, x3, y3;
	
	x1 = x;
	y1 = y;
	
	x2 = x - width;
	y2 = y;
	
	x3 = x;
	y3 = y + height;
	
	LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x2,y2,x3,y3);
	
}

//����
void draw_reversed_trapezoid(int x, int y, int upper_width, int lower_width, int height){
	int x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = x - upper_width/2;
	y1 = y;
	
	x2 = x + upper_width/2;
	y2 = y;
	
	x3 = x - lower_width/2;
	y3 = y - height;
	
	x4 = x + lower_width/2;
	y4 = y - height;
	
	//LCD_DrawLine(x1,y1,x2,y2);
	LCD_DrawLine(x1,y1,x3,y3);
	LCD_DrawLine(x4,y4,x2,y2);
	LCD_DrawLine(x4,y4,x3,y3);
	
}

// ��������������������
void draw_hexagon(int x, int y, int size, uint16_t color) {
    int points[6][2];
    
    // ���������ε���������
    for (int i = 0; i < 6; i++) {
        int angle = 60 * i - 30;  // ��ת30�ȣ�ʹ������ˮƽ����
        points[i][0] = x + size * cos(angle * 3.14159f / 180);
        points[i][1] = y + size * sin(angle * 3.14159f / 180);
    }
    
    // ������������
    for (int i = 0; i < 6; i++) {
        lcd_draw_line(points[i][0], points[i][1], 
                     points[(i+1)%6][0], points[(i+1)%6][1], color);
    }
}

// �������������ƾ��Σ����߿���ɫ������
void lcd_draw_boss_rectangle(int x, int y, int width, int height, uint16_t color) {
    lcd_draw_line(x, y, x + width, y, color);
    lcd_draw_line(x, y, x, y + height, color);
    lcd_draw_line(x + width, y + height, x + width, y, color);
    lcd_draw_line(x + width, y + height, x, y + height, color);
}
/*-------------------------------------������ͼ��-------------------------------------*/
void draw_star(int x,int y){
	//����ϳ�
	LCD_DrawLine(x,y-star_height/2, x,y+star_height/2);
	//����϶�
	LCD_DrawLine(x-star_width/2,y, x+star_width/2,y);
}

void update_sys_tick(void) {
    sys_tick++;
}

// �Զ���time����
uint64_t time(uint64_t *t) {
    uint64_t now = sys_tick / 1000;  // ת��Ϊ��
    if (t) {
        *t = now;
    }
    return now;
}

void draw_poisson_stars(void) {
    srand((unsigned int)time(NULL));
    
    // ���Ʋ�ͬ�ܶȵ�����
    for (int i = 0; i < STAR_COUNT; i++) {
        // �ײ�����y��600���ܶ����
        if (i < STAR_COUNT / 4) {
            int x = rand() % SCREEN_WIDTH;
            int y = 500 + rand() % 200;
            draw_star(x, y);
        }
        // �в�����200��y<600���ܶ��е�
        else if (i < STAR_COUNT / 2) {
            int x = rand() % SCREEN_WIDTH;
            int y = 200 + rand() % 300;
            draw_star(x, y);
        }
        // ��������y<200���ܶ����
        else if (i < STAR_COUNT * 3 / 4) 
            {
             int x = rand() % SCREEN_WIDTH;
            int y = rand() % 200;
            draw_star(x, y);    }
            }
}
