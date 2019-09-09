#ifndef __SSB_H__
#define __SSB_H__

#include "shorthand.h"

// ssb/ultra function named by me
extern void ssb_playFGM(u16 id);
extern void ssb_playBGM(u16 effect, u16 id);
extern u32  ssb_getRandomInt(u32 upperLimit);

// @ Description
// Copies nBytes from romSrc to ramDest
extern void ssb_dmaCopy(u32 * romSrc, u32 * ramDest, u32 nBytes);


// @ Description
// Starts a versus match
extern void ssb_startVersus();

// @ Description
// Writing 0x00000001 to this word will load the screen at ssb_currentScreen.
extern u32 ssb_screenInterrupt;

// @ Description
// Byte, Current screen value is here (CSS = 0x10, Debug = 0x03/0x04)
extern u8 ssb_currentScreen;

// @ Description
// Checks if a stick is pressed in the positive or negative direction
// @ Params
// u8 minimum, min coordinate to activate as true
// enum direction (u8 direction), left/right OR down/up
extern bool ssb_checkStickX(u8 minimum, u8 direction);
extern bool ssb_checkStickY(u8 minimum, u8 direction);






#endif