#include "shorthand.h"
#include "joypad.h"
#include "n64.h"

s8 joypad_getStickX(enum n64_Player player) {
    // lazy handle
    if (player == n64_ALL || player == n64_ANY) {
        return 0;
    }

    return joypad_infoArray[player]->stickX;
}


s8 joypad_getStickY(enum n64_Player player) {
    // lazy handle
    if (player == n64_ALL || player == n64_ANY) {
        return 0;
    }

    return joypad_infoArray[player]->stickY;
}

bool joypad_stickWasPushed(enum joypad_Direction direction, enum n64_Player player) {
    u16 framesHeld;

    // if checking any player pressed, run function recursively
    if (player == n64_ANY) {
        return \
        joypad_stickWasPushed(direction, n64_P1) || \
        joypad_stickWasPushed(direction, n64_P2) || \
        joypad_stickWasPushed(direction, n64_P3) || \
        joypad_stickWasPushed(direction, n64_P4) ;
    
    // if checking all players pressed, run fucntion recursively
    } else if (player == n64_ALL) {
        return \
        joypad_stickWasPushed(direction, n64_P1) && \
        joypad_stickWasPushed(direction, n64_P2) && \
        joypad_stickWasPushed(direction, n64_P3) && \
        joypad_stickWasPushed(direction, n64_P4) ;
    
    } 
    

    // if the direction is incorrect, return false;
    if (direction != joypad_lastDirection[player]) {
        return FALSE;
    }

    // get frames held
    framesHeld = joypad_framesHeldStick[player];

    // case 1: frames_held = 0, return false
    // return false if not pushed
    if (framesHeld < joypad_MIN_FRAMES) {
        return FALSE;
    
    // return true if just pushed
    } else if (framesHeld == joypad_MIN_FRAMES) {
        return TRUE;
    
    // add a buffer period
    } else if (framesHeld > joypad_MIN_FRAMES && framesHeld < joypad_BUFFER_FRAMES) {
        return FALSE;

    // return true every four frames after 28
    } else if (framesHeld % joypad_BUFFER_RATE == 0) {
        return TRUE;
    
    }

    return FALSE;
}

void joypad_updateStick() {
    struct joypad_Info * info = NULL;
    u16 * framesHeld;
    enum joypad_Direction * direction;

    // update framesHeld for all players
    for (int i = 0; i < 4; i++) {
        info = joypad_infoArray[i];
        framesHeld = &joypad_framesHeldStick[i];
        direction = &joypad_lastDirection[i];

        // if stick direction held, increment framesHeld
        // right
        if (info->stickX > joypad_STICK_MINIMUM) {
            *framesHeld += 1;
            *direction = joypad_SR;

        // left
        } else if (info->stickX < -joypad_STICK_MINIMUM) {
            *framesHeld += 1;
            *direction = joypad_SL;

        // up
        } else if (info->stickY > joypad_STICK_MINIMUM) {
            *framesHeld += 1;
            *direction = joypad_SU;

        // down
        } else if (info->stickY < -joypad_STICK_MINIMUM) {
            *framesHeld += 1;
            *direction = joypad_SD;
        
        // none
        } else {
            *framesHeld = 0;
            *direction = joypad_NEUTRAL;
        }
    }
}

bool joypad_checkButtons(u16 buttonMask, enum n64_Player player, enum joypad_Type type) {
    struct joypad_Info * info = NULL;

    // if checking any player pressed, run function recursively
    if (player == n64_ANY) {
        return \
        joypad_checkButtons(buttonMask, n64_P1, type) || \
        joypad_checkButtons(buttonMask, n64_P2, type) || \
        joypad_checkButtons(buttonMask, n64_P3, type) || \
        joypad_checkButtons(buttonMask, n64_P4, type) ;
    
    // if checking all players pressed, run fucntion recursively
    } else if (player == n64_ALL) {
        return \
        joypad_checkButtons(buttonMask, n64_P1, type) && \
        joypad_checkButtons(buttonMask, n64_P2, type) && \
        joypad_checkButtons(buttonMask, n64_P3, type) && \
        joypad_checkButtons(buttonMask, n64_P4, type) ;
    
    // set joypad_Info pointer to correct player
    } else {
        info = joypad_infoArray[player];
    }

    // check if button mask matches the given type mask
    if (type == joypad_HELD && buttonMask == info->isHeld) {
        return TRUE;
    
    } else if (type == joypad_PRESSED && buttonMask == info->wasPressed) {
        return TRUE;

    } else if (type == joypad_TURBO && buttonMask == info->turbo) {
        return TRUE;

    } else if (type == joypad_RELEASED && buttonMask == info->wasReleased) {
        return TRUE;

    }

    // ...if not, return false
    return FALSE;
}