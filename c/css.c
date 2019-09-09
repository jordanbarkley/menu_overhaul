void css_init(void) {
    // actual css screen
    // initialize hands
    struct css_Hand * hand = NULL;
    for (int i = 0; i < 4; i++) {
        hand = &css_hands[i];
        // TODO: constants here
        hand->x = 80 + (i * (css_WINDOW_WIDTH + 1));   // offset + (i * some x constant)
        hand->y = 131;            // some y constant
        hand->state = css_HAND_POINTING_WINDOWS;
        hand->player = i;
    }

    // initialize chips
    struct css_Chip * chip = NULL;
    for (int i = 0; i < 4; i++) {
        chip = &css_chips[i];
        chip->x = 0;
        chip->y = 0;
        chip->state = css_CHIP_DISABLED;
        chip->player = i;
    }

    // initialize players
    struct css_Player * player = NULL;
    for (int i = 0; i < 4; i++) {
        player->type = css_MAN;
    }
}


void css_loop(void) {
    // update hand and chip
    css_updateCursorPosition();
    css_updateCursorState();

    // toggle betw
    css_toggleType();
    css_toggleTeams();

    // apply settings
    css_updatePlayers();

    // draw everything
    css_draw();

    // check for match start, any player presses start
    if (joypad_wasPressed(joypad_START, n64_ANY)) {
        css_startVersus();
    }

    // attempt to exit CSS
    if (css_exitTriggered()) {
        // TODO: play sound
        screen_pop();
    }
}

void css_draw(void) {
    struct css_Hand * hand = NULL;
    struct css_Chip * chip = NULL;
    struct css_Tile * tile = NULL;
    struct css_Window * window = NULL;
    struct css_Player * player = NULL;
    u16 x;
    u16 y;
    u16 color;
    char * characterString;

    // draw options at the top
    graphics_setColor(color_PURPLE);
    graphics_drawRectangle(10, 10, 300, 19);
    graphics_drawString(20, 15, "BACK");
    graphics_drawString(80, 15, "4-MAN SURVIVAL TEST!");


    // TODO: constants
    // draw teams logo
    if (css_settingsVS->teams != FALSE) {
        graphics_drawString(280, 15, "FFA");
    } else {
        graphics_drawString(280 - 16, 15, "TEAMS");
    }

    // draw character tiles
    graphics_setColor(color_WHITE);
    for (int i = 0; i < css_TOTAL_CHARACTERS; i++) {
        // get appropriate tile
        tile = &css_tiles[i];

        // draw a square
        graphics_drawRectangle(tile->ulx, tile->uly, css_TILE_WIDTH, css_TILE_HEIGHT);
    }

    // draw character windowws for each player
    // TODO: more than just VS.
    for (int i = 0; i < 4; i++) {
        // draw window
        window = &css_windows[i];
        color = css_colors[i];
        chip = &css_chips[i];
        player = css_playersVS[i];

        // draw window based on type (colored for human, grey for disabled/cpu)
        if (player->type == css_MAN) {
            graphics_setColor(color);
        } else if (player->type == css_MAN) {
            graphics_setColor(color - )
        } else {
            graphics_setColor(color_GREY);
        }

        graphics_drawRectangle(window->ulx, window->uly, css_WINDOW_WIDTH, css_WINDOW_HEIGHT);
        
        // TODO: debug/remove this
        graphics_drawString(window->ulx, window->uly, css_types[player->type]);

        // draw character string if chip not disabled
        if (chip->state != css_CHIP_DISABLED) {
            // get string
            characterString = css_charactersShort[player->character];
            
            // get string coordinate
            x = window->ulx;
            y = window->uly + css_WINDOW_HEIGHT - font_HEIGHT;
            
            // draw string
            graphics_drawString(x, y, characterString);
        }
    }

    // draw chip
    // for all players, draw chip
    for (int i = 0; i < 4; i++) {
        // get appropriate chip
        chip = &css_chips[i];
        color = css_colors[i];
        // TODO: more than just VS
        player = css_playersVS[i];

        // draw color for human, draw grey for CPU
        if (player->type == css_MAN) {
            graphics_setColor(color);
        } else {
            graphics_setColor(color_GREY);
        }

        // draw chip unless the chip is disabled
        if (chip->state != css_CHIP_DISABLED) {
            graphics_drawRectangle(chip->x, chip->y, 10, 10);
            graphics_drawChar(chip->x, chip->y, '1' + i);
        }
    }

    // draw hand
    // for all players, draw hand
    for (int i = 0; i < 4; i++) {
        hand = &css_hands[i];
        color = css_colors[i];

        graphics_setColor(color_BLACK);
        graphics_drawRectangle(hand->x - 1, hand->y - 1, 12, 12);
        graphics_setColor(color);
        graphics_drawRectangle(hand->x, hand->y, 10, 10);
        graphics_drawChar(hand->x, hand->y, '1' + i);

    }

}

void css_updateCursorPosition(void) {
    struct css_Hand * hand = NULL;
    struct css_Chip * chip = NULL;
    s16 differenceX = 0;
    s16 differenceY = 0;

    // for each player, update hand position
    for (int i = 0; i < 4; i++) {
        // get current players hand
        hand = &css_hands[i];

        // update hand position based on the control stick
        hand->x += (joypad_getStickX(i) / css_HAND_REDUCER);
        hand->y -= (joypad_getStickY(i) / css_HAND_REDUCER);

        // add limiter for how far hand can go
        // x direction
        if (hand->x > css_MAX_HAND_X) {
            hand->x = css_MAX_HAND_X;
        
        } else if (hand->x < css_MIN_HAND_X) {
            hand->x = css_MIN_HAND_X;
        }

        // y direction
        if (hand->y > css_MAX_HAND_Y) {
            hand->y = css_MAX_HAND_Y;
        
        } else if (hand->y < css_MIN_HAND_Y) {
            hand->y = css_MIN_HAND_Y;
        }
    }

    // todo: make seperate function
    // for each player, update chip position
    // when held, chip pos should just be +(2, 2) of hand pos
    for (int i = 0; i < 4; i++) {
        // get current players hand
        hand = &css_hands[i];

        // get the chip they're holding (if holding a chip)
        if (hand->state <= css_HAND_HOLDING_4) {
            chip = &css_chips[hand->state];
        
        // get their chip (if catching a chip)
        } else if (hand->state == css_HAND_CATCHING) {
            chip = &css_chips[i];

        // otherwise skip the rest
        } else {
            continue;
        }

        // move chip towards hand
        if (chip->state == css_CHIP_MOVING) {
            // get length of legs of triangle
            differenceX = hand->x - chip->x;
            differenceY = hand->y - chip->y;

            // update chip position
            chip->x += differenceX / css_HAND_SPEED;
            chip->y += differenceY / css_HAND_SPEED;
        
        // move chip with hand
        } else {
            chip->x = hand->x + 2;
            chip->y = hand->y + 2; 
        }
    }
}

void css_updateCursorState(void) {
    struct css_Hand * hand = NULL;
    struct css_Chip * chip = NULL;
    s16 differenceX = 0;
    s16 differenceY = 0;

    // for all players
    for (int i = 0; i < 4; i++) {
        // get current players hand
        hand = &css_hands[i];

        // get the chip they're holding or their chip
        if (hand->state <= css_HAND_HOLDING_4) {
            chip = &css_chips[hand->state];
        } else {
            chip = &css_chips[i];
        }
        
        // if in the options area
        if (hand->y < css_OPTIONS_TILES_DIV) {
            // set hand to pointing
            hand->state = css_HAND_POINTING_OPTIONS;

            // set chip to disabled (if it's not currently being held or down)
            if (chip->state == (enum css_ChipState) hand->player || \
            (chip->state > css_CHIP_HELD_4 && chip->state != css_CHIP_DOWN)) {
                chip->state = css_CHIP_DISABLED;
            }

        // if in the character windows area
        } else if (hand->y > css_TILES_WINDOWS_DIV) {
            // set hand to pointing
            hand->state = css_HAND_POINTING_WINDOWS;

            // set chip to disabled (if it's not currently being held or down)
            if (chip->state == (enum css_ChipState) hand->player || \
            (chip->state > css_CHIP_HELD_4 && chip->state != css_CHIP_DOWN)) {
                chip->state = css_CHIP_DISABLED;
            }

            // also add the ability to disable a chip here with a b press
            if (joypad_wasPressed(joypad_B, i)) {
                chip->state = css_CHIP_DISABLED;
            }

        // if in the character tiles area
        } else {

            // if chip is moving, check if chip has been caught
            if (chip->state == css_CHIP_MOVING) {
                // get the difference in pixels
                differenceX = hand->x - chip->x;
                differenceY = hand->y - chip->y;

                // make sure the difference is positive
                if (differenceX < 0) {
                    differenceX *= -1;
                }

                if (differenceY < 0) {
                    differenceY *= -1;
                }

                // check for catch based on difference
                if (differenceX <= css_HAND_CHIP_TOLERANCE && differenceY <= css_HAND_CHIP_TOLERANCE) {
                    chip->state = css_CHIP_HELD_1 + i;
                    hand->state = css_HAND_HOLDING_1 + i;
                }
            
            
            // chip is held by current player, check for drop
            } else if (chip->state == (enum css_ChipState) hand->player) {
                // drop on a press
                if (joypad_wasPressed(joypad_A, i)) {
                    hand->state = css_HAND_EMPTY;
                    chip->state = css_CHIP_DOWN;
                }
            
            // hand is empty, hand should stay empty or picked up on this frame
            } else if (hand->state == css_HAND_EMPTY) {
                // if b pressed and that chip is not held, start moving chip
                if (chip->state > css_CHIP_HELD_4 && joypad_wasPressed(joypad_B, i)) {
                    hand->state = css_HAND_CATCHING;
                    chip->state = css_CHIP_MOVING;
                    
                // if a pressed, chick for direct pickup
                } else if (joypad_wasPressed(joypad_A, i)) {
                    // for all chips
                    for (int j = 0; j < 4; j++) {
                        // get a chip
                        chip = &css_chips[j];

                        // check if around the area
                        differenceX = hand->x - chip->x;
                        differenceY = hand->y - chip->y;

                        // make sure the difference is positive
                        if (differenceX < 0) {
                            differenceX *= -1;
                        }

                        if (differenceY < 0) {
                            differenceY *= -1;
                        }

                        // if above, set chip to held and hand to holding, then break
                        if (differenceX <= css_HAND_CHIP_TOLERANCE && differenceY <= css_HAND_CHIP_TOLERANCE) {
                            hand->state = css_HAND_HOLDING_1 + j;
                            chip->state = css_CHIP_HELD_1 + i;
                            break;
                        }
                    }
                }
        
            // if your chip is not held by anyone and is not down, pick up your own chip
            } else if (chip->state > css_CHIP_HELD_4 && chip->state != css_CHIP_DOWN) {
                hand->state = css_HAND_HOLDING_1 + i;
                chip->state = css_CHIP_HELD_1 + i;
            
            // otherwise, your hand should just be set to empty
            } else {
                hand->state = css_HAND_EMPTY;
            }
        }
    }
}

void css_updatePlayers(void) {
    struct css_Tile * tile = NULL;
    struct css_Chip * chip = NULL;
    struct css_Player * player = NULL;

    // for all players
    for (int i = 0; i < 4; i++) {
        // get chip and window for current player
        // TODO: for modes outside of VS.
        chip = &css_chips[i];
        player = css_playersVS[i];

        // if the chip is disabled, skip the rest of this iteration
        // also set player to NOT
        if (chip->state == css_CHIP_DISABLED) {
            player->type = css_NOT;
            continue;
        }

        // for all tiles
        for (int j = 0; j < css_TOTAL_CHARACTERS; j++) {
            // get a tile
            tile = &css_tiles[j];

            // check if the chip is hovering over given tile (in the square)
            if (chip->x >= tile->ulx &&
                chip->x <= tile->ulx + css_TILE_WIDTH + 1 && \
                chip->y >= tile->uly && \
                chip->y <= tile->uly + css_TILE_HEIGHT + 1) {
                
                // set the player's character to the character in the tile
                // and enable the player to play
                player->character = tile->character;
                
                // enable a human player UNLESS port is already a CPU
                if (player->type == css_NOT) {
                    player->type = css_MAN;
                }
            }
        
        }
    }
}

// @description
void css_startVersus(void) {
    // *fill in the rest of the player structs*
    struct css_Player * player = NULL;

    // for all players
    // TODO: more than just VS.
    // TODO: rest of this lol
    for (int i = 0; i < 4; i++) {
        player = css_playersVS[i];

        player->cpuLevel = 3;   // change
        player->handicap = 9;   // change
        // player->type already set
        // player->character alread set
        player->teamShield = i; // change i think lol
        player->team = 0;       // team
        player->costume = 0;    // change

        // literally i have nothing of this done yet lmaooooooo
    }
    
    // actually launch the match
    ssb_startVersus();

}

bool css_exitTriggered(void) {
    struct css_Hand * hand = NULL;
    u8 * framesHeld = NULL;

    // for all players
    for (int i = 0; i < 4; i++) {
        // get vars for players
        framesHeld = &css_framesHeldB[i];
        hand = &css_hands[i];

        // if B held, increment
        if (joypad_isHeld(joypad_B, i)) {
            *framesHeld += 1;
        
        // otherwise, set to zero
        } else {
            *framesHeld = 0;

        }

        // check if we should exit because of B hold
        if (*framesHeld == css_HOLD_B_FRAMES) {
            // trigger exit
            return TRUE;
        }

        // check if we should exit because of back Button
        if (hand->state == css_HAND_POINTING_OPTIONS && \
            hand->x < css_BACK_BUTTON_RX && \
            joypad_wasPressed(joypad_A, i)) {
            
            // trigger exit
            return TRUE;
        }
    }

    // default
    return FALSE;
}


void css_toggleType() {
    struct css_Chip * chip = NULL;
    struct css_Hand * hand = NULL;
    // TODO: peep handMoving logic, if necessary
    struct css_Hand * handMoving = NULL;
    struct css_Window * window = NULL;
    struct css_Player * player = NULL;

    // for all players
    for (int i = 0; i < 4; i++) {
        hand = &css_hands[i];

        // for all windows
        for (int j = 0; j < 4; j++) {
            // TODO: all not VS
            chip = &css_chips[j];
            window = &css_windows[j];
            player = css_playersVS[j];
            handMoving = &css_hands[j];

            // check if in window
            if (hand->state == css_HAND_POINTING_WINDOWS && \
                hand->x >= window->ulx && \
                hand->x <= (window->ulx + css_WINDOW_WIDTH)) {

                // check for A press
                if (joypad_wasPressed(joypad_A, i)) {
                    ssb_playFGM(0xA4);
                    // toggle the window/player type
                    player->type += 1;

                    // loop through types
                    if (player->type > css_NOT) {
                        player->type = css_MAN;
                    }

                    // random for chip
                    if (player->type != css_CPU) {
                        chip->state = css_CHIP_DOWN;
                        chip->x = css_MIN_HAND_X + ssb_getRandomInt(css_MAX_HAND_X - css_MIN_HAND_X);
                        chip->y = css_TILE_ULY + ssb_getRandomInt(css_TILE_LRY - css_TILE_ULY);
                    }

                    // if the type is disabled, set chip to disabled
                    // and reset hand position
                    if (player->type == css_NOT) {
                        chip->state = css_CHIP_DISABLED;
                        handMoving->x = css_handStartX(j);
                        handMoving->y = css_HAND_START_Y;
                    }
                }
            }
        }
    }
}

void css_toggleTeams(void) {
    struct css_Hand * hand = NULL;

    // check for all players
    for (int i = 0; i < 4; i++) {
        // get the players ahand
        hand = &css_hands[i];
    
        // if in range
        if (hand->state == css_HAND_POINTING_OPTIONS && \
            hand->x > css_TEAMS_ENABLE_X && \
            joypad_wasPressed(joypad_A, i)) {
            
            // set teams to the opposite
            css_settingsVS->teams = !css_settingsVS->teams;
        }
    }
}
