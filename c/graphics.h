#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

void graphics_setColor(u16 color);
void graphics_drawRectangle(u16 ulx, u16 uly, u16 width, u16 height);
void graphics_drawTexture(u16 ulx, u16 uly, u16 width, u16 height, u16 * data);
void graphics_drawChar(u16 ulx, u16 uly, char c);
void graphics_drawString(u16 ulx, u16 uly, char * string);
void graphics_drawStringLRX(u16 lrx, u16 uly, char * string);
void graphics_drawIntLRX(u16 lrx, u16 uly, u32 num, u32 base);
void graphics_start(u64 * dlist);
void graphics_end();

#endif // __GRAPHICS_H__