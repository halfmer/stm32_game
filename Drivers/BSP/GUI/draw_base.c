#include "./BSP/GUI/draw_base.h"

//stm32f103zet6战舰所用lcd分辨率为480*800

/*-------------------------------基础设置-------------------------------*/
void LCD_ShowString(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t size, char *p)
{
    lcd_show_string(x,y,width,height,size,p,BLACK);
}

void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    lcd_draw_line(x1,y1,x2,y2,RED);
}

void LCD_DrawPoint(int x,int y)
{
    lcd_draw_point(x,y,BLACK);
}

uint32_t LCD_Pow(uint8_t m, uint8_t n) {
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}

void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r) {
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1);             //判断下个点位置的标志
	while (a <= b) {
		LCD_DrawPoint(x0 + a, y0 - b);             //5
		LCD_DrawPoint(x0 + b, y0 - a);             //0
		LCD_DrawPoint(x0 + b, y0 + a);             //4
		LCD_DrawPoint(x0 + a, y0 + b);             //6
		LCD_DrawPoint(x0 - a, y0 + b);             //1
		LCD_DrawPoint(x0 - b, y0 + a);
		LCD_DrawPoint(x0 - a, y0 - b);             //2
		LCD_DrawPoint(x0 - b, y0 - a);             //7
		a++;
		//使用Bresenham算法画圆     
		if (di < 0)
			di += 4 * a + 6;
		else {
			di += 10 + 4 * (a - b);
			b--;
		}
	}
}

void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len,uint8_t size, uint8_t mode) {
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++) {
		temp = (num / LCD_Pow(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1)) {
			if (temp == 0) {
				if (mode & 0X80)
					lcd_show_char(x + (size / 2) * t, y, '0', size, mode & 0X01,BLACK);
				else
					lcd_show_char(x + (size / 2) * t, y, ' ', size, mode & 0X01,BLACK);
				continue;
			} else
				enshow = 1;

		}
		lcd_show_char(x + (size / 2) * t, y, temp + '0', size, mode & 0X01,BLACK);
	}
}


