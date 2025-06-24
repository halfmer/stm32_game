#include <string.h>
#include <stdlib.h>
#include "./BSP/GUI/rendering.h"
#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/delay/delay.h"

// 定义颜色类型
typedef unsigned int color_t;

// 全局变量：当前渲染目标
static FrameBuffer *current_target = NULL;

// 设置渲染目标
void set_render_target(FrameBuffer *target) {
    if (target != NULL) {
        current_target = target;
    }
}

// 清除整个缓冲区
void clear_buffer(FrameBuffer *buffer) {
    if (buffer == NULL || buffer->buffer == NULL) {
        return;
    }
    
    // 计算缓冲区大小（字节数）
    size_t buffer_size = buffer->width * buffer->height * buffer->bytes_per_pixel;
    
    // 将整个缓冲区填充为黑色（0）
    memset(buffer->buffer, 0, buffer_size);
}

// 清除指定矩形区域
void clear_rect(FrameBuffer *buffer, int x, int y, int width, int height) {
    if (buffer == NULL || buffer->buffer == NULL) {
        return;
    }
    
    // 确保矩形区域在缓冲区范围内
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > buffer->width) width = buffer->width - x;
    if (y + height > buffer->height) height = buffer->height - y;
    
    if (width <= 0 || height <= 0) {
        return;
    }
    
    // 计算每行的字节数
    int row_bytes = buffer->width * buffer->bytes_per_pixel;
    
    // 逐行清除矩形区域
    for (int i = 0; i < height; i++) {
        unsigned char *row = buffer->buffer + (y + i) * row_bytes + x * buffer->bytes_per_pixel;
        memset(row, 0, width * buffer->bytes_per_pixel);
    }
}

// 交换前后缓冲区
void swap_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer) {
    if (front_buffer == NULL || back_buffer == NULL || 
        front_buffer->buffer == NULL || back_buffer->buffer == NULL) {
        return;
    }
    
    // 简单交换缓冲区指针
    unsigned char *temp = front_buffer->buffer;
    front_buffer->buffer = back_buffer->buffer;
    back_buffer->buffer = temp;
    
    // 如果当前渲染目标是前缓冲区，更新为新的前缓冲区
    if (current_target == front_buffer) {
        current_target = back_buffer;
    }
    
    // 这里可以添加实际的硬件刷新操作，例如将缓冲区内容发送到显示设备
    // 对于不同的硬件平台，这部分代码可能需要调整
    // 例如：
    // refresh_display(front_buffer);
}

// 初始化帧缓冲区
void init_frame_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer, 
                        int width, int height, int bpp) {
    if (front_buffer == NULL || back_buffer == NULL) {
        return;
    }
    
    // 计算每像素字节数
    int bytes_per_pixel = (bpp + 7) / 8;  // 向上取整
    
    // 计算缓冲区大小（字节数）
    size_t buffer_size = width * height * bytes_per_pixel;
    
    // 分配前缓冲区内存
    front_buffer->buffer = (unsigned char *)malloc(buffer_size);
    if (front_buffer->buffer == NULL) {
        return;  // 内存分配失败
    }
    
    // 分配后缓冲区内存
    back_buffer->buffer = (unsigned char *)malloc(buffer_size);
    if (back_buffer->buffer == NULL) {
        free(front_buffer->buffer);
        return;  // 内存分配失败
    }
    
    // 设置缓冲区属性
    front_buffer->width = width;
    front_buffer->height = height;
    front_buffer->bpp = bpp;
    front_buffer->bytes_per_pixel = bytes_per_pixel;
    
    back_buffer->width = width;
    back_buffer->height = height;
    back_buffer->bpp = bpp;
    back_buffer->bytes_per_pixel = bytes_per_pixel;
    
    // 初始化缓冲区内容为黑色
    clear_buffer(front_buffer);
    clear_buffer(back_buffer);
}

// 释放帧缓冲区内存
void free_frame_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer) {
    if (front_buffer != NULL && front_buffer->buffer != NULL) {
        free(front_buffer->buffer);
        front_buffer->buffer = NULL;
    }
    
    if (back_buffer != NULL && back_buffer->buffer != NULL) {
        free(back_buffer->buffer);
        back_buffer->buffer = NULL;
    }
}

// 炸弹特效演示函数
void bomb_effect_demo(int center_x, int center_y) {
    // 特效参数配置
    int max_radius = 200;           // 爆炸最大半径
    int radius_step = 18;            // 每帧半径增加量
    int num_circles = 3;            // 同心圆数量
    int frame_delay = 15;           // 帧间隔时间(ms)
    
    // 颜色定义
    uint16_t explosion_colors[3] = {
        YELLOW,  // 内圈颜色（最亮）
        ORANGE,  // 中圈颜色
        RED      // 外圈颜色（最暗）
    };
    
    // 爆炸动画循环
    for (int radius = 0; radius <= max_radius; radius += radius_step) {
        for (int i = 0; i < num_circles; i++) {
            int circle_radius = radius - i * (radius_step * 2);
            
            // 确保半径为正
            if (circle_radius <= 0) continue;
            
            // 计算当前圆的颜色（随半径增大逐渐变暗）
            uint16_t color = explosion_colors[i % 3];
            
            // 绘制圆形爆炸效果
            lcd_draw_circle(center_x, center_y, circle_radius, color);
        }
        
        // 短暂延时，控制动画速度
        delay_ms(frame_delay);
        
        // 清除当前帧（除了最后一帧）
        if (radius < max_radius) {
            lcd_fill(center_x - max_radius, center_y - max_radius,
                    center_x + max_radius, center_y + max_radius, BLACK);
        }
    }
    
    // 爆炸结束后，添加一个短暂的闪光效果
    lcd_fill(center_x - max_radius/2, center_y - max_radius/2,
            center_x + max_radius/2, center_y + max_radius/2, WHITE);
    delay_ms(50);
    lcd_fill(center_x - max_radius/2, center_y - max_radius/2,
            center_x + max_radius/2, center_y + max_radius/2, BLACK);
}
