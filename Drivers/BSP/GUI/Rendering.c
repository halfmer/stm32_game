#include <string.h>
#include <stdlib.h>
#include "./BSP/GUI/rendering.h"
#include "./BSP/LCD/lcd.h"
#include "./SYSTEM/delay/delay.h"

// ������ɫ����
typedef unsigned int color_t;

// ȫ�ֱ�������ǰ��ȾĿ��
static FrameBuffer *current_target = NULL;

// ������ȾĿ��
void set_render_target(FrameBuffer *target) {
    if (target != NULL) {
        current_target = target;
    }
}

// �������������
void clear_buffer(FrameBuffer *buffer) {
    if (buffer == NULL || buffer->buffer == NULL) {
        return;
    }
    
    // ���㻺������С���ֽ�����
    size_t buffer_size = buffer->width * buffer->height * buffer->bytes_per_pixel;
    
    // ���������������Ϊ��ɫ��0��
    memset(buffer->buffer, 0, buffer_size);
}

// ���ָ����������
void clear_rect(FrameBuffer *buffer, int x, int y, int width, int height) {
    if (buffer == NULL || buffer->buffer == NULL) {
        return;
    }
    
    // ȷ�����������ڻ�������Χ��
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x + width > buffer->width) width = buffer->width - x;
    if (y + height > buffer->height) height = buffer->height - y;
    
    if (width <= 0 || height <= 0) {
        return;
    }
    
    // ����ÿ�е��ֽ���
    int row_bytes = buffer->width * buffer->bytes_per_pixel;
    
    // ���������������
    for (int i = 0; i < height; i++) {
        unsigned char *row = buffer->buffer + (y + i) * row_bytes + x * buffer->bytes_per_pixel;
        memset(row, 0, width * buffer->bytes_per_pixel);
    }
}

// ����ǰ�󻺳���
void swap_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer) {
    if (front_buffer == NULL || back_buffer == NULL || 
        front_buffer->buffer == NULL || back_buffer->buffer == NULL) {
        return;
    }
    
    // �򵥽���������ָ��
    unsigned char *temp = front_buffer->buffer;
    front_buffer->buffer = back_buffer->buffer;
    back_buffer->buffer = temp;
    
    // �����ǰ��ȾĿ����ǰ������������Ϊ�µ�ǰ������
    if (current_target == front_buffer) {
        current_target = back_buffer;
    }
    
    // ����������ʵ�ʵ�Ӳ��ˢ�²��������罫���������ݷ��͵���ʾ�豸
    // ���ڲ�ͬ��Ӳ��ƽ̨���ⲿ�ִ��������Ҫ����
    // ���磺
    // refresh_display(front_buffer);
}

// ��ʼ��֡������
void init_frame_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer, 
                        int width, int height, int bpp) {
    if (front_buffer == NULL || back_buffer == NULL) {
        return;
    }
    
    // ����ÿ�����ֽ���
    int bytes_per_pixel = (bpp + 7) / 8;  // ����ȡ��
    
    // ���㻺������С���ֽ�����
    size_t buffer_size = width * height * bytes_per_pixel;
    
    // ����ǰ�������ڴ�
    front_buffer->buffer = (unsigned char *)malloc(buffer_size);
    if (front_buffer->buffer == NULL) {
        return;  // �ڴ����ʧ��
    }
    
    // ����󻺳����ڴ�
    back_buffer->buffer = (unsigned char *)malloc(buffer_size);
    if (back_buffer->buffer == NULL) {
        free(front_buffer->buffer);
        return;  // �ڴ����ʧ��
    }
    
    // ���û���������
    front_buffer->width = width;
    front_buffer->height = height;
    front_buffer->bpp = bpp;
    front_buffer->bytes_per_pixel = bytes_per_pixel;
    
    back_buffer->width = width;
    back_buffer->height = height;
    back_buffer->bpp = bpp;
    back_buffer->bytes_per_pixel = bytes_per_pixel;
    
    // ��ʼ������������Ϊ��ɫ
    clear_buffer(front_buffer);
    clear_buffer(back_buffer);
}

// �ͷ�֡�������ڴ�
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

// ը����Ч��ʾ����
void bomb_effect_demo(int center_x, int center_y) {
    // ��Ч��������
    int max_radius = 200;           // ��ը���뾶
    int radius_step = 18;            // ÿ֡�뾶������
    int num_circles = 3;            // ͬ��Բ����
    int frame_delay = 15;           // ֡���ʱ��(ms)
    
    // ��ɫ����
    uint16_t explosion_colors[3] = {
        YELLOW,  // ��Ȧ��ɫ��������
        ORANGE,  // ��Ȧ��ɫ
        RED      // ��Ȧ��ɫ�����
    };
    
    // ��ը����ѭ��
    for (int radius = 0; radius <= max_radius; radius += radius_step) {
        for (int i = 0; i < num_circles; i++) {
            int circle_radius = radius - i * (radius_step * 2);
            
            // ȷ���뾶Ϊ��
            if (circle_radius <= 0) continue;
            
            // ���㵱ǰԲ����ɫ����뾶�����𽥱䰵��
            uint16_t color = explosion_colors[i % 3];
            
            // ����Բ�α�ըЧ��
            lcd_draw_circle(center_x, center_y, circle_radius, color);
        }
        
        // ������ʱ�����ƶ����ٶ�
        delay_ms(frame_delay);
        
        // �����ǰ֡���������һ֡��
        if (radius < max_radius) {
            lcd_fill(center_x - max_radius, center_y - max_radius,
                    center_x + max_radius, center_y + max_radius, BLACK);
        }
    }
    
    // ��ը���������һ�����ݵ�����Ч��
    lcd_fill(center_x - max_radius/2, center_y - max_radius/2,
            center_x + max_radius/2, center_y + max_radius/2, WHITE);
    delay_ms(50);
    lcd_fill(center_x - max_radius/2, center_y - max_radius/2,
            center_x + max_radius/2, center_y + max_radius/2, BLACK);
}
