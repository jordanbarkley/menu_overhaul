#ifndef __JOYPAD_H__
#define __JOYPAD_H__

#include "n64.h"

// @description
// The Nintendo 64 joystick can read -127 to 128 (only about -80 to 80 reachable) 
// on each axis. This is the minimum absolute value needed to say "the stick 
// has been" pushed
#define joypad_STICK_MINIMUM 30

// @description
// In order to avoid the hovering issue (polling the stick at barely below and
// barely above joypad_STIC_MINIMUM, this number represents how many frames the
// stick has to be pushed past that value
#define joypad_MIN_FRAMES 2

// @description
// After holding the stick for joypad_BUFFER_FRAMES number of frames, 
// joypad_stickWasPushed() will return true every joypad_BUFFER_RATE frames 
// instead of just on the initial push
#define joypad_BUFFER_FRAMES 30
#define joypad_BUFFER_RATE 6

/*
 * @description
 * The controller sturct the game reads from. All 16 bit masks.
 */
struct joypad_Info {
    u16 isHeld;             // if button currenlty held
    u16 wasPressed;         // check for !isHeld -> isHeald
    u16 turbo;              // isHeld but continually goes on and off
    u16 wasReleased;        // check for isHeld -> !isHeald
    s8 stickX;              // stick x coordinates
    s8 stickY;              // stick y coordinates
    u16 _;                  // padding (DO NOT READ)
};

/*
 * @description
 * Pointers to joypad_Info struct for each player
 */
struct joypad_Info * joypad_infoArray[] = {
    (void *) 0x80045228,
    (void *) 0x80045232,
    (void *) 0x8004523C,
    (void *) 0x80045246
};

/*
 * @description
 * Button masks for joypad_Info structs
 */
enum joypad_Input {
    joypad_A        = 0x8000,
    joypad_B        = 0x4000,
    joypad_Z        = 0x2000,
    joypad_START    = 0x1000,
    joypad_DU       = 0x0800,
    joypad_DD       = 0x0400,
    joypad_DL       = 0x0200,
    joypad_DR       = 0x0100,
    joypad_L        = 0x0020,
    joypad_R        = 0x0010,
    joypad_CU       = 0x0008,
    joypad_CD       = 0x0004,
    joypad_CL       = 0x0002,
    joypad_CR       = 0x0001
};

// @description
// Enum for stick direction (seperate from input)
enum joypad_Direction {
//  joypad_Stick<Direction>
    joypad_SU,
    joypad_SD,
    joypad_SL,
    joypad_SR,
    joypad_NEUTRAL
};

/*
 * @description
 * Type of input to check for.
 */
enum joypad_Type {
    joypad_HELD,
    joypad_PRESSED,
    joypad_TURBO,
    joypad_RELEASED
};


// @description
// Amount of frames a stick has been held in a given direction
u16 joypad_framesHeldStick[] = {
    0,
    0,
    0,
    0
};

// @description
// Array of last direction pushed for each player
enum joypad_Direction joypad_lastDirection[] = {
    joypad_NEUTRAL,
    joypad_NEUTRAL,
    joypad_NEUTRAL,
    joypad_NEUTRAL
};

// @description
// Returns the value of the the stick in the x or y direciton
s8 joypad_getStickX(enum n64_Player player);
s8 joypad_getStickY(enum n64_Player player);


// @description
// Returns true if a direction has been pushed. It also includes a "turbo return" 
// for holding over a given length (for scrolling through menus)
// @params
// enum direction (left/right/up/down)
bool joypad_stickWasPushed(enum joypad_Direction direction, enum n64_Player player);

// @description
// Sets up data structures related to joypad stick
void joypad_updateStick();

/*
 * @description
 * Returns true if a button mask was in a given state (type) and false otherwise.
 */
bool joypad_checkButtons(u16 buttonMask, enum n64_Player player, enum joypad_Type type);

/** 
 * @description
 * Macros to make calling joypad_checkButtons() more readable
 */
#define joypad_isHeld(b, p)         joypad_checkButtons(b, p, joypad_HELD)
#define joypad_wasPressed(b, p)     joypad_checkButtons(b, p, joypad_PRESSED)
#define joypad_turbo(b, p)          joypad_checkButtons(b, p, joypad_TURBO)
#define joypad_wasReleased(b, p)    joypad_checkButtons(b, p, joypad_RELEASED)


#endif