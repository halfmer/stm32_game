#ifndef _RENDERING_H
#define _RENDERING_H

// ֡����ṹ�嶨��
typedef struct {
    unsigned char *buffer;  // ������ָ��
    int width;              // ���
    int height;             // �߶�
    int bpp;                // ÿ����λ�� (Bits Per Pixel)
    int bytes_per_pixel;    // ÿ�����ֽ���
} FrameBuffer;

void clear_rect(FrameBuffer *fb, int x, int y, int w, int h);
void set_render_target(FrameBuffer *target);
void clear_buffer(FrameBuffer *buffer);
void clear_rect(FrameBuffer *buffer, int x, int y, int width, int height);
void swap_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer);
void init_frame_buffers(FrameBuffer *front_buffer, FrameBuffer *back_buffer, int width, int height, int bpp);
void bomb_effect_demo(int center_x, int center_y);
    
#endif
