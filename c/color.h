#ifndef __COLOR_H__
#define __COLOR_H__
#include "shorthand.h"


// http://htmlcolorcodes.com/color-names/
//            rgba
#define color_5551(r, g, b) \
	(((u32) r & 0xF8) << 8) | \
	(((u32) g & 0xF8) << 3) | \
	(((u32) b & 0xF8) >> 2) | \
	(1)

// typedef u16 rgba5551;

void color_lighten(u16 rgba5551, float32 amount) {
	u8 red = (rgba5551 >> 8);
	u8 green;
	u8 blue;

}

#define color_RED 		color_5551(0xFF, 0x00, 0x00)
#define color_ORANGE	color_5551(0xFF, 0xA5, 0x00)
#define color_YELLOW 	color_5551(0xFF, 0xFF, 0x00)
#define color_GREEN 	color_5551(0x00, 0x80, 0x00)
#define color_BLUE 		color_5551(0x00, 0x00, 0xFF)
#define color_PURPLE	color_5551(0x80, 0x00, 0x80)
#define color_PINK 		color_5551(0xFF, 0xC0, 0xCB)
#define color_BROWN 	color_5551(0xA5, 0x2A, 0x2A)
#define color_BLACK 	color_5551(0x00, 0x00, 0x00)
#define color_GREY 		color_5551(0x80, 0x80, 0x80)
#define color_WHITE 	color_5551(0xFF, 0xFF, 0xFF)
#define color_CLEAR 	0x0000

#endif
