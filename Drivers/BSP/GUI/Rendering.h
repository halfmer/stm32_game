#ifndef _RENDERING_H
#define _RENDERING_H

// 帧缓冲结构体定义
typedef struct {
    unsigned char *buffer;  // 缓冲区指针
    int width;              // 宽度
    int height;             // 高度
    int bpp;                // 每像素位数 (Bits Per Pixel)
    int bytes_per_pixel;    // 每像素字节数
} FrameBuffer;

void clear_rect(FrameBuffer *fb, int x, int y, int w, int h);
void set_render_target(FrameBuffer *target);
void clear_buffer(FrameBuffer *buffer);
void clear_rect(FrameBuffer *buffer, int x, int y, int width, int height);
void swap_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer);
void init_frame_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer, int width, int height, int bpp);
void bomb_effect_demo(int center_x, int center_y);
    
#endif
