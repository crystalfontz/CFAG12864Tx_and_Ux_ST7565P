#ifndef __LCD_DRAW_H__
#define __LCD_DRAW_H__
//============================================================================
extern uint8_t framebuffer[8][128];
//----------------------------------------------------------------------------
void Fill_Framebuffer(uint8_t data1, uint8_t data2);
void Send_Framebuffer_To_Display(void);
void logo_to_framebuffer(void);
void Put_Pixel(uint8_t x, uint8_t y, uint8_t set);
void LCD_Line(uint8_t x0, uint8_t y0,
               uint8_t x1, uint8_t y1,
               uint8_t set);
void LCD_Circle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t set);
void put_string(uint8_t x, uint8_t y, uint8_t Field_Width, const char *input);
void invert_string(uint8_t x, uint8_t y, uint8_t Field_Width);
void horizontal_line(uint8_t x1, uint8_t y, uint8_t x2);
void vertical_line(uint8_t x, uint8_t y1, uint8_t y2);
void outline_rectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void clear_rectangle(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
void Rounded_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t radius,uint8_t set);
//============================================================================
#endif //  __LCD_DRAW_H__
