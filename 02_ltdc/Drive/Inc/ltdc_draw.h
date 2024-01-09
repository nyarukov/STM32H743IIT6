#ifndef __LTDC_DRAW_H
#define __LTDC_DRAW_H

#include "ltdc_driver.h"

// 定义RGB565颜色编码宏
#define RGB565(r, g, b) (((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3))

// 颜色常量定义
#define LCD_BLUE           RGB565(0, 0, 255)       // 纯蓝色
#define LCD_GREEN          RGB565(0, 255, 0)       // 纯绿色
#define LCD_RED            RGB565(255, 0, 0)       // 纯红色
#define LCD_CYAN           RGB565(0, 255, 255)     // 青色（绿+蓝）
#define LCD_MAGENTA        RGB565(255, 0, 255)     // 洋红色（红+蓝）
#define LCD_YELLOW         RGB565(255, 255, 0)     // 黄色（红+绿）
#define LCD_LIGHTBLUE      RGB565(128, 128, 255)   // 亮蓝色
#define LCD_LIGHTGREEN     RGB565(128, 255, 128)   // 亮绿色
#define LCD_LIGHTRED       RGB565(255, 128, 128)   // 亮红色
#define LCD_LIGHTCYAN      RGB565(128, 255, 255)   // 亮青色
#define LCD_LIGHTMAGENTA   RGB565(255, 128, 255)   // 亮洋红色
#define LCD_LIGHTYELLOW    RGB565(255, 255, 128)   // 亮黄色
#define LCD_DARKBLUE       RGB565(0, 0, 128)       // 深蓝色
#define LCD_DARKGREEN      RGB565(0, 128, 0)       // 深绿色
#define LCD_DARKRED        RGB565(128, 0, 0)       // 深红色
#define LCD_DARKCYAN       RGB565(0, 128, 128)     // 深青色
#define LCD_DARKMAGENTA    RGB565(128, 0, 128)     // 深洋红色
#define LCD_DARKYELLOW     RGB565(128, 128, 0)     // 深黄色
#define LCD_WHITE          RGB565(255, 255, 255)   // 纯白色
#define LCD_LIGHTGRAY      RGB565(211, 211, 211)   // 亮灰色
#define LCD_GRAY           RGB565(128, 128, 128)   // 灰色
#define LCD_DARKGRAY       RGB565(64, 64, 64)      // 深灰色
#define LCD_BLACK          RGB565(0, 0, 0)         // 纯黑色
#define LCD_BROWN          RGB565(165, 42, 42)     // 棕色
#define LCD_ORANGE         RGB565(255, 165, 0)      // 橙色
#define LCD_TRANSPARENT    RGB565(0, 0, 0)         // 透明色

void LCD_Draw_Point(u16 x,u16 y,u32 color);
u32 LCD_Read_Point(u16 x,u16 y);
void LCD_Cler(u32 color);
void LCD_Fill(u16 x0,u16 y0,u16 x1,u16 y1,u32 color);
void LCD_DMA2D_Fill(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,u16 Color);
void LCD_DMA2D_Image(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,void *Image);
#endif // !__LTDC_DRAW_H




