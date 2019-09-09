#include "stddef.h"

void graphics_setColor(u16 color) {
    // fill alpha bit
    color = color | 1;

    // set fill color to color
    rcp_append(rcp_setFillColor(color));
}

void graphics_drawRectangle(u16 ulx, u16 uly, u16 width, u16 height) {
    // error checking
    if (width < 1 || height < 1) {
        return;
    } 
    
    // calculate other coordinates
    u16 lrx = ulx + width - 1;
    u16 lry = uly + height - 1;

    // set other modes to fill
    rcp_append(rcp_setOtherModesFill());

    // fill rectangle
    rcp_append(rcp_fillRectangle(ulx, uly, lrx, lry));

    // pipe sync
    rcp_append(rcp_syncPipe());
}

void graphics_drawTexture(u16 ulx, u16 uly, u16 width, u16 height, u16 * data) {
    // error checking
    if (width < 1 || height < 1) {
        return;
    }

    // make sure there aren't more than 4096 bytes (not enough video memory)
    u16 texels = width * height * sizeof(u16);
    if (texels > 4096) {
        // if there are, draw sections of the texture (all 5 tall except that last)
        // this is because max width (320) * 5 * sizeof(u16) < 4096
        while (height >= 5) {
            // draw the block
            graphics_drawTexture(ulx, uly, width, 5, data);

            // decrement total height
            height -= 5;

            // increment data pointer by how many texels were drawn (don't 
            // include the * sizeof(rgba5551) because it's a u16 pointer)
            data += (5 * width);

            // increment uly
            uly += 5;
        }

        // draw last block
        graphics_drawTexture(ulx, uly, width, height, data);
    }

    // calculate other coordinates
    u16 lrx = ulx + width - 1;
    u16 lry = uly + height - 1;

    // set other modes to copy
    rcp_append(rcp_setOtherModesCopy());

    // set texture image
    rcp_append(rcp_setTextureImage(data));

    // set tile (draw 16 bit rgba)
    rcp_append(rcp_setTile(width, rcp_RGBA_5551_FORMAT, rcp_RGBA_5551_SIZE));

    // load sync
    rcp_append(rcp_syncLoad());

    // load block
    rcp_append(rcp_loadBlock(width, height));

    // pipe sync
    rcp_append(rcp_syncPipe());

    // set tile (draw 16 bit rgba), possibly redundant
    rcp_append(rcp_setTile(width, rcp_RGBA_5551_FORMAT, rcp_RGBA_5551_SIZE));

    // set tile size
    rcp_append(rcp_setTileSize(width, height));

    // texture rectangle
    rcp_append(rcp_textureRectangle1(ulx, uly, lrx, lry));
    rcp_append(rcp_textureRectangle2());
    rcp_append(rcp_textureRectangle3());

    // pipe sync
    rcp_append(rcp_syncPipe());
}



void graphics_drawChar(u16 ulx, u16 uly, char c) {
    // get the address of the font
    unsigned char * data = font_rgba5551;

    // get the address of the character (assumes rgba5551)
    data += (c * font_WIDTH * font_HEIGHT * sizeof(u16));

    // draw character like texture
    graphics_drawTexture(ulx, uly, font_WIDTH, font_HEIGHT, (u16 *) data);
}

void graphics_drawString(u16 ulx, u16 uly, char * string) {
    // call graphics_drawChar() for every character in the null terminated string
    while (*string) {
        // draw character
        graphics_drawChar(ulx, uly, *string);
        
        // increment to next character
        ulx += font_WIDTH;
        string++;
    }
}

void graphics_drawStringLRX(u16 lrx, u16 uly, char * string) {
    // call graphics_drawChar() for every character
    // get number of characters to draw
    u32 length = string_length(string);
    
    // print the characters backwards from lrx
    for (int i = length; i > 0; i--) {
        graphics_drawChar(lrx, uly, string[i - 1]);
        lrx -= font_WIDTH;
    }
}

void graphics_drawIntLRX(u16 lrx, u16 uly, u32 num, u32 base) {
    // only looking for positive dec/hex values
    if (base != 10 && base != 16) {
        asm("break");
    }

    u32 i = 0;
    u32 remainder = 0;
    char buffer[16];

    // check if num is 0 (while loop will not run)
    if (num == 0) {
        buffer[i] = '0';
        i++;
    }

    // convert to string
    while (num != 0) {
        // find first digit
        remainder = num % base;

        // add digit
        if (remainder > 9) {
            // adding letter (A-F)
            buffer[i] = 'A' + remainder - 10;
        } else {
            // adding number (0-9)
            buffer[i] = '0' + remainder;
        } 

        num = num / base;
        i++;
    }

    // print the string in reverse
    for (int j = 0; j < i; j++) {
        graphics_drawChar(lrx, uly, buffer[j]);
        lrx -= font_WIDTH;
    }

}

void graphics_start(u64 * dlist) {
	rcp_flush();
	rcp_hook(dlist);
}

void graphics_end() {
	rcp_append(rcp_syncFull());
	rcp_append(rcp_endList());
}