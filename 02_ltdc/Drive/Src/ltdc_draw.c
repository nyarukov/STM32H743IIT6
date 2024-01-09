#include "ltdc_draw.h"

static u32 index(u16 x, u16 y);

void LCD_Draw_Point(u16 x, u16 y, u32 color)
{
    *(SDRAM_LCD_BUF1+index(x, y)) = color;
}
u32 LCD_Read_Point(u16 x, u16 y)
{
    u32 rgb;
    rgb = *(SDRAM_LCD_BUF1+index(x, y));
    return rgb;
}
u32 index(u16 x, u16 y)
{
    return (y * 1024 + x);
}

void LCD_Cler(u32 color)
{
    u32 size;
    u32 i;
    size = 1024 * 600;
    for (i = 0; i < size; i++)
    {
        *(SDRAM_LCD_BUF1+i) = color;
    }
}
void LCD_Fill(u16 xStrat, u16 yStrat, u16 xEnd, u16 yEnd, u32 color)
{
    u16 i, j;
    for (i = xStrat; i < xEnd; i++)
    {
        for (j = yStrat; j < yEnd; j++)
        {
            *(SDRAM_LCD_BUF1+index(i, j)) = color;
        }
    }
}

/*
 * FGMAR: 前景内存地址寄存器, 指定前景图像数据的存储起始地址.
 * FGOR: 前景偏移寄存器, 指定前景图像数据的行与行之间的偏移量.
 * FGPFCCR: 前景PFC控制寄存器, 配置前景图像的像素格式和PFC选项.
 * FGCOLOR: 前景颜色寄存器, 指定前景图像的颜色.
 * FGCMAR: 前景CLUT内存地址寄存器, 指定前景图像的颜色查找表的存储起始地址.
 * FGCLUT: 前景CLUT, 包含前景图像的颜色查找表.
 */
/*
 * BGMAR: 背景内存地址寄存器, 指定背景图像数据的存储起始地址.
 * BGOR: 背景偏移寄存器, 指定背景图像数据的行与行之间的偏移量.
 * BGPFCCR: 背景PFC控制寄存器, 配置背景图像的像素格式和PFC选项.
 * BGCOLR: 背景颜色寄存器, 指定背景图像的颜色.
 * BGCMAR: 背景CLUT内存地址寄存器, 指定背景图像的颜色查找表的存储起始地址.
 * BGCLUT: 背景CLUT, 包含背景图像的颜色查找表.
 */
/*
 * OMAR: 输出内存地址寄存器, 指定输出图像数据的存储起始地址.
 * OOR: 输出偏移寄存器, 指定输出图像数据的行与行之间的偏移量.
 * OCOLR: 输出颜色寄存器, 指定输出图像的颜色.
 * NLR: 行数寄存器, 指定图像的行数.
 * OPFCCR: 输出PFC控制寄存器, 配置输出图像的像素格式和PFC选项.
 * LWR: 行水印寄存器, 指定何时生成行中断.
 * AMTCR: AXI主定时器配置寄存器, 配置AXI主定时器的工作方式.
 */


void LCD_DMA2D_Fill(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,u16 Color){
    __HAL_RCC_DMA2D_CLK_ENABLE();
    u32 BuffAdd;
    u32 OffLine;
    
    BuffAdd=((u32)SDRAM_LCD_BUF1+index(xStart,yStart)*2);
    OffLine= ABS(1024-(xEnd-xStart));
    
    __WRITE_REG(DMA2D->CR,0x00030000UL);                    
    
    __WRITE_REG(DMA2D->OMAR,(u32)BuffAdd);                   
    __WRITE_REG(DMA2D->OCOLR,Color);                         
    __WRITE_REG(DMA2D->OOR,OffLine);                         
    __WRITE_REG(DMA2D->OPFCCR,LTDC_PIXEL_FORMAT_RGB565);
    
    __WRITE_REG(DMA2D->NLR,((xEnd-xStart)<<16)| (yEnd-yStart));
    
    __SET_BIT(DMA2D->CR,DMA2D_CR_START);
    
    while(DMA2D->CR & DMA2D_CR_START){}
}

/**
 * @brief 
 * 
 * @param xStart 图像的起始 x 坐标
 * @param yStart 图像的起始 y 坐标
 * @param xEnd 图像的结束 x 坐标
 * @param yEnd 图像的结束 y 坐标
 * @param Image 图像数据
 */
void LCD_DMA2D_Image(u16 xStart,u16 yStart,u16 xEnd,u16 yEnd,void *Image){
    __HAL_RCC_DMA2D_CLK_ENABLE();
    u32 BuffAdd;
    u32 OffLine;

    BuffAdd=((u32)SDRAM_LCD_BUF1+index(xStart,yStart)*2);
    OffLine= ABS(1024-(xEnd-xStart));

    __WRITE_REG(DMA2D->CR,0x00000000UL);                     
   
    __WRITE_REG(DMA2D->FGMAR,(u32)Image);
    __WRITE_REG(DMA2D->FGOR,0);
    __WRITE_REG(DMA2D->FGPFCCR,LTDC_PIXEL_FORMAT_RGB565);
    
    __WRITE_REG(DMA2D->OMAR,(u32)BuffAdd);
    __WRITE_REG(DMA2D->OOR,OffLine);
    __WRITE_REG(DMA2D->OPFCCR,LTDC_PIXEL_FORMAT_RGB565);
    
    __WRITE_REG(DMA2D->NLR,((xEnd-xStart)<<16)| (yEnd-yStart));
    
    __SET_BIT(DMA2D->CR,DMA2D_CR_START);

    while(DMA2D->CR & DMA2D_CR_START){}
}
