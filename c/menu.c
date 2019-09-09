#include "menu.h"

struct menu_Header * menu_initHeader(u16 ulx, u16 uly, u16 width, u16 color, char * title) {
    // create and intialize menu header
    struct menu_Header * header = malloc(sizeof(struct menu_Header));
    header->title = title;
    header->ulx = ulx;
    header->uly = uly;
    header->width = width;
    header->selection = 0;
    header->totalEntries = 0;
    header->color = color;
    header->head = NULL;
    return header;
}

void menu_addEntry(struct menu_Header * header, char * description, enum menu_Type type, u32 value, u32 min, u32 max, void * funcPtr, char ** strings, void * copyAddress, enum screen_Tag nextScreen) {
    // avoid null errors
    if (header == NULL) {
        return;
    }
    
    // increment total entries
    header->totalEntries++;
    
    // create and initialize menu entry
    struct menu_Entry * entry = malloc(sizeof(struct menu_Entry));
    entry->description = description;
    entry->type = type;
    entry->value = 0;
    entry->min = min;
    entry->max = max;
    entry->funcPtr = funcPtr;
    entry->strings = strings;
    entry->copyAddress = copyAddress;
    entry->nextScreen = nextScreen;

    // check for adding the first entry
    if (header->head == NULL) {
        header->head = entry;
        return;
    }

    // iterate through linked list until NULL found 
    struct menu_Entry * curr = header->head;
    while (curr->nextEntry != NULL) {
        curr = curr->nextEntry;
    }

    // append newly created entry
    curr->nextEntry = entry;
}

void menu_print(struct menu_Header * header) {
    // avoid null errors
    if (header == NULL) {
        return;
    }

    // exit if there are no entries
    if (header->totalEntries <= 0) {
        return;
    }

    // draw menu
    if (header->color != 0) {
        graphics_setColor(header->color);
        // graphics_drawRectangle(0, 0, 320, 240);
    }

    // print menu title and increment row height (uly)
    u16 uly = header->uly;
    graphics_drawString(header->ulx + font_WIDTH, uly, header->title);
    uly += font_WIDTH + 2;

    // get the first entry
    struct menu_Entry * currEntry = header->head;


    // iterate over the linked list
    u32 i = 0;

    while (currEntry != NULL) {
        // draw string on every iteration (leave room for blue dot)
        graphics_drawString(header->ulx + font_WIDTH, uly, currEntry->description);

        // check if current entry is selected, if so draw cursor
        if (header->selection == i) {
            // draw underline
            graphics_setColor(color_ORANGE);
            graphics_drawRectangle(header->ulx, uly + font_HEIGHT, header->width - font_WIDTH, 1);
    
            // draw dot
            graphics_drawRectangle(header->ulx, uly, menu_CURSOR_WIDTH, menu_CURSOR_HEIGHT);
        }

        // draw value to the right

        // strings
        if (currEntry->strings != NULL) {
            graphics_drawStringLRX(header->width, uly, currEntry->strings[currEntry->value]);

        // unsinged ints, base 10
        } else if (currEntry->type == menu_TypeU8 || currEntry->type == menu_TypeU16 || currEntry->type == menu_TypeU32) {
            graphics_drawIntLRX(header->width, uly, currEntry->value, 10);

        // unsigned ints, base 16
        } else if (currEntry->type == menu_TypeX8 || currEntry->type == menu_TypeX16 || currEntry->type == menu_TypeX32) {
            graphics_drawIntLRX(header->width, uly, currEntry->value, 16);
        
        // boolean
        } else if (currEntry->type == menu_TypeBool) {
            graphics_drawStringLRX(header->width, uly, menu_booleanStrings[currEntry->value]);
        
        }

        // increment and repeat
        uly += font_HEIGHT + 2;
        currEntry = currEntry->nextEntry;
        i++;
    }

}

void menu_copy(struct menu_Header * header) {
    // avoid null errors
    if (header == NULL) {
        return;
    }

    // exit if there are no entries
    if (header->totalEntries <= 0) {
        return;
    }

    // get first menu entry
    struct menu_Entry * entry = header->head;

    // loop through all menu entries
    while (entry != NULL) {
        // 

        // always update copy address if not null
        if (entry->copyAddress != NULL) {
            // handle each menu type for updates
            
            // 8 bit unsigned
            if (entry->type == menu_TypeU8 || entry->type == menu_TypeX8) {
                *((u8 *) entry->copyAddress) = entry->value;

            // 16 bit unsigned
            } else if (entry->type == menu_TypeU16 || entry->type == menu_TypeX16) {
                *((u16 *) entry->copyAddress) = entry->value;

            // 32 bit unsigned
            } else if (entry->type == menu_TypeU32 || entry->type == menu_TypeX32) {
                *((u32 *) entry->copyAddress) = entry->value;
            
            // boolean
            } else if (entry->type == menu_TypeBool) {
                *((bool *) entry->copyAddress) = entry->value;
            }

        }

        // increment entry
        entry = entry->nextEntry;
    }
}

void menu_update(struct menu_Header * header, enum menu_Event event) {
    // avoid null errors
    if (header == NULL) {
        return;
    }

    // exit if there are no entries
    if (header->totalEntries <= 0) {
        return;
    }

    // get menu entry
    struct menu_Entry * entry = menu_getEntry(header);


    // up pressed, decrement selection and loop if necessary, play sound
    if (event == menu_EventUp) {
        if (header->selection <= 0) {
            header->selection = header->totalEntries - 1;
        } else {
            header->selection--;
        }            
        ssb_playFGM(0xA4);
    
    // down pressed, increment selection and loop if necessary, play sound
    } else if (event == menu_EventDown) {
        if (header->selection >= header->totalEntries - 1) {
            header->selection = 0;
        } else {
            header->selection++;
        }
        ssb_playFGM(0xA4);

    // left pressed, decrement value and loop if necessary, play sound
    } else if (event == menu_EventLeft) {
        if (entry->value <= entry->min) {
            entry->value = entry->max;
        } else {
            entry->value--;
        }
        ssb_playFGM(0xA4);
    
    // right pressed, increment value and loop if necessary, play sound
    } else if (event == menu_EventRight) {
        if (entry->value >= entry->max) {
            entry->value = entry->min;
        } else {
            entry->value++;
        }
        ssb_playFGM(0xA4);

    // a pressed, go to next screen, run function, or do nothing, play a sound
    } else if (event == menu_EventConfirm) {

        // do nothing (play sound for debug)
        if (entry->nextScreen == screen_TagNone) {
            ssb_playFGM(0x00);

        // run funciton
        } else if (entry->funcPtr != NULL) {
            entry->funcPtr();
            ssb_playFGM(0xA4);
        
        // go to next menu screen
        } else {
            screen_push(entry->nextScreen);
            ssb_playFGM(0xA4);
        }
    }

}

void menu_standard(struct menu_Header * header) {
    // check for down
    if (joypad_stickWasPushed(joypad_SD, n64_ANY)) {
		menu_update(header, menu_EventDown);
	
	// check for up
	} else if (joypad_stickWasPushed(joypad_SU, n64_ANY)) {
		menu_update(header, menu_EventUp);
	
	// check for left
	} else if (joypad_stickWasPushed(joypad_SL, n64_ANY)) {
		menu_update(header, menu_EventLeft);
	
	// check for right
	} else if (joypad_stickWasPushed(joypad_SR, n64_ANY)) {
		menu_update(header, menu_EventRight);
	
    // check for a
    } else if (joypad_wasPressed(joypad_A, n64_ANY)) {
		menu_update(header, menu_EventConfirm);
    }

    // copy values menu
    menu_copy(header);

    // draw the menu
    menu_print(header);
}

 struct menu_Entry * menu_getEntry(struct menu_Header * header) {
    // makes sure that we have at least 1 entry
    if (header->totalEntries <= 0) {
        asm("break");
    }

    // get first entry
    struct menu_Entry * currEntry = header->head;

    // iterate throuight list
    for (int i = 0; i < header->selection; i++) {
        currEntry = currEntry->nextEntry;
    }

    return currEntry;
}