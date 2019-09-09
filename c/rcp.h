#ifndef __RCP_H__
#define __RCP_H__

// only for use with rgba5551 textures

// https://dragonminded.com/n64dev/Reality%20Coprocessor.pdf
// http://wiki.cloudmodding.com/oot/F3DZEX/Opcode_Details (more accurate)

/*
smash rgba5551 textures go
G_SETTIMAGE
G_SETTILE 			// redundant(?)
G_RDPLOADSYNC
G_LOADBLOCK
G_RDPPIPESYNC
G_SETTTILE
G_SETTILESIZE
G_TEXRECT
G_RDPPIPESYNC
*/

u64 * rcp_displayListStart;
u64 * rcp_displayListEnd;
u64 * rcp_displayListCurr;

#define rcp_DISPLAY_LIST_SIZE 0x20000
#define rcp_RGBA_5551_FORMAT 0
#define rcp_RGBA_5551_SIZE 2

void rcp_init();
void rcp_append(u64 command);
void rcp_flush();

// n << s, result is always a 64 bit
#define rcp_s(n, s) \
	(((u64) n) << s)

// @ Description
// Sets the other mode bitfield of the RDP.
// @ Arguments
// high [h]
// low [l]
// @ Bytefield
// EFhhhhhh llllllll
// cycle type = 3 (fill)
#define rcp_setOtherModesFill() \
	rcp_s(0xEF, 56) | rcp_s(3, 52)

// cycle type = 2 (copy), alpha compare enabled
#define rcp_setOtherModesCopy() \
	rcp_s(0xEF, 56) | rcp_s(2, 52) | (1)

// @ Description
// Sets the fill color for use in fill mode, which allows clearing the current 
// color buffer
// @ Arguments
// fill color [f]
// @ Note
// 16 bit colors (rgba5551) should be packed 11112222. Otherwise, the RDP will 
// draw striped
// rectangles.
// @ Bytefield
// F7000000 ffffffff
#define rcp_setFillColor(color) \
	rcp_s(0xF7, 56) | rcp_s(color, 16) | (color)

// @ Description 
// Draws a solid colored (or striped) rectangle.
// @ Arguments
// fixed point (10.2) int ulx [X]
// fixed point (10.2) int [Y]
// fixed point (10.2) int [x]
// fixed point (10.2) int [y]
// @ Bytefield
// F6xxxyyy 00XXXYYY
#define rcp_fillRectangle(ulx, uly, lrx, lry) \
	rcp_s(0xF6, 56) | rcp_s(lrx << 2, 44) | rcp_s(lry << 2, 32) | \
	rcp_s(ulx << 2, 12) | (uly << 2)


// color format = rgba, pixel size = 16 bit (addr = RDRAM address), wdith = n/a
// @ Description
// This opcode sets the location in RAM of the image that will be used when 
// using any of the texture loading opcodes.
// @ Arguments
// RAM address [a]
// color format [f]
// color size [s]
// width = 0 (not used by us)
// @ Bitfield
//    F    D       
// 1111 1101 fffs s000 0000 00ww wwww wwww aaaa aaaa aaaa aaaa aaaa aaaa aaaa aaaa
/*
    // from 19XX RCP.asm image sizes
    constant G_IM_SIZ_4b(0x00)
    constant G_IM_SIZ_8b(0x01)
    constant G_IM_SIZ_16b(0x02)
    constant G_IM_SIZ_32b(0x03)
*/
#define rcp_setTextureImage(addr) \
	rcp_s(0xFD, 56) | rcp_s(rcp_RGBA_5551_SIZE, 51) | ((u32) addr)

// @ Description
// Sets many different parameters for tile descriptors.
// @ Given Arguments
// width 
// color format [f]
// color size [i]
// @ Calculated Arguments
// tile line size [?] (number of 64 bit values per row)
// tmem address [m] = 0
// tile [t] = 0
// palette [p] = 0
// cmT [c] = 0
// maskT [a] = 0
// shiftT [s] = 0
// cmS [d] = 0
// maskS [b] = 0
// shiftS [u] = 0
// @ Bitfield
//    F    5
// 1111 0101 fffi i0nn nnnn nnnm mmmm mmmm 0000 0ttt pppp ccaa aass ssdd bbbb uuuu

// for rgba5551
// tls = width * 2 / 8
// or
// tls = (width << 1) >> 3

// generally
// tls = width * n / 8
// or
// tls = (width << (bytes_per_pixel)) >> 3

// size will come as one of these
// constant G_IM_SIZ_4b(0x0000)
// constant G_IM_SIZ_8b(0x0001)
// constant G_IM_SIZ_16b(0x0002)
// constant G_IM_SIZ_32b(0x0003)

// therefore
// tls = (width << (size)) >> 4
#define rcp_setTile(width, f, i) \
	rcp_s(0xF5, 56) | rcp_s(f, 53) | rcp_s(i, 51) | rcp_s((width << i) >> 4, 41)
	// op			  format         size           tls


// @ Description
// Sets the size of the texture for tile descriptor tile.
// @ Given Arguments
// width
// height
// @ Calculated Arguments
// int (10.2) lrs [u] = width - 1
// int (10.2) lrs [v] = height - 1
// int (10.2) uls [s] = 0
// int (10.2) ult [t] = 0
// @ Bytefield
// F2sssttt 0iuuuvvv
#define rcp_setTileSize(width, height) \
	rcp_s(0xF2, 56) | rcp_s((width - 1) << 2, 12) | ((height - 1) << 2)

// @ Description
// Loads a texture into TMEM as one long line of data (texels + 1 bytes).
// @ Given Arguments
// a0 - width
// a1 - height
// uls [s] = 0
// ult [t] = 0
// texels [x] = width * height - 1
// dxt [d] = 0
// tile index [i] = 0
// @ Bytefield
// F3sssttt 0ixxxddd
#define rcp_loadBlock(width, height) \
	rcp_s(0xF3, 56) | rcp_s((width * height) - 1, 12)

// @ Description
// Draws a textured rectangle
// @ Arguments
// a0 - int ulx [X]
// a1 - int uly [Y]
// a2 - int lrx [x]
// a3 - int lry [y]
// texture index [i] = 0
// s coodrdinate [s] = 0
// t coodrdinate [t] = 0
// dsdx [d] = 1 (why?)
// dtdy [e] = 4 (why?)
// @ Bytefield
// E4xxxyyy 0iXXXYYY
// E1000000 sssstttt
// F1000000 ddddeeee
#define rcp_textureRectangle1(ulx, uly, lrx, lry) \
	rcp_s(0xE4, 56) | rcp_s(lrx << 2, 44) | rcp_s(lry << 2, 32) | \
	rcp_s(ulx << 2, 12) | (uly << 2)

#define rcp_textureRectangle2() \
	((u64) 0xE100000000000000)

#define rcp_textureRectangle3() \
	((u64) 0xF100000010000400)

// @ Description
// This forces a wait for a texture to load, in order to synchronize with pixel 
// rendering. This ensures that loading a new texture won't disrupt the 
// rendering of primitives mid-render.
// @ Bytefield
// E6000000 00000000
#define rcp_syncLoad() \
	((u64) 0xE600000000000000)

// @ Description
// Waits for the RDP to finish rendering its currently-rendering primitive, 
// before updating RDP attributes. This avoids altering the rendering of a 
// primitive in the middle of its render.
// @ Bytefield
// E7000000 00000000
#define rcp_syncPipe() \
	((u64) 0xE700000000000000)

// @ Description
// Forces a wait for rendering to finish before updating tile descriptor
// attributes, so as to not disrupt rendering of primitives mid-render.
// @ Bytefield
// E8000000 00000000
#define rcp_syncTile() \
	((u64) 0xE800000000000000)

// @ Description
// Generates an interrupt for the main CPU when the RDP has finished doing everything. 
// This is typically the last opcode before the "end display list" opcode.
// @ Bytefield
// E9000000 00000000
#define rcp_syncFull() \
	((u64) 0xE900000000000000)

// @ Description
// The jr ra equivalent of display lists
// @ Bytefield
// DF000000 00000000
#define rcp_endList() \
	((u64) 0xDF00000000000000)

#define rcp_branchList(addr) \
	rcp_s(0xDE, 56) | rcp_s(1, 48) | ((u32) addr)


#endif
