#ifndef __CSS_H__
#define __CSS_H__

char * css_characters[] = {
    "Mario",
    "Fox",
    "Donkey Kong",
    "Samus",
    "Luigi",
    "Link",
    "Yoshi",
    "Captain Falcon",
    "Kirby",
    "Pikachu",
    "Jigglypuff",
    "Ness"
};

char * css_charactersShort[] = {
    "Mario",
    "Fox",
    "DK",
    "Samus",
    "Luigi",
    "Link",
    "Yoshi",
    "Falcon",
    "Kirby",
    "Rat",
    "Puff",
    "Ness"
};

char * css_types[] = {
    "Man",
    "CPU",
    "Disabled"
};

u16 css_colors[] = {
    color_RED,
    color_BLUE,
    color_YELLOW,
    color_GREEN
};

// @ Description
// The stick value is reduced by this factor (stickPos / css_HAND_REDUCER) in
// css_updateCursorPosition()
#define css_HAND_REDUCER 20

// @description
// When the chip is moving towards the hand, it much be within this x and y
// distance to be picked up.
#define css_HAND_CHIP_TOLERANCE 8

// @description
// When moving, the chip travels (1/css_HAND_SPEED)^n (eg 1/2, 1/4, 1/8...) 
// the distance to to the the hand
#define css_HAND_SPEED 2

// @description
// Number of characters available (for arrays and shit)
#define css_TOTAL_CHARACTERS 24

enum css_Team {
    css_RED,
    css_BLUE,
    css_GREEN
};

enum css_Type {
    css_MAN,
    css_CPU,
    css_NOT
};

enum css_Character {
    css_MARIO,
    css_FOX,
    css_DK,
    css_SAMUS,
    css_LUIGI,
    css_LINK,
    css_YOSHI,
    css_FALCON,
    css_KIRBY,
    css_PIKACHU,
    css_JIGGLYPUFF,
    css_NESS
};

// @description
// This is struct of size 0x74. The struct contains an abundance of
// data. The needed data to start a match, is included and the rest is update
// in game.
struct css_Player {
    u8 cpuLevel;            // 0x0000
    u8 handicap;            // 0x0001
    u8 type;                // 0x0002, enum css_Type
    u8 character;           // 0x0003, enum css_Character
    u8 teamShield;          // 0x0004, enum css_Team
    u8 team;                // 0x0005, enum css_Team
    u8 costume;             // 0x0006
    u8 _unknown0x0007;      // 0x0007
    u8 palleteIndex;        // 0x0008
    u8 _unknown0x0009;      // 0x0009 (something about stock icons)
    u8 playerIconIndex;     // 0x000A
    u8 stocks;              // 0x000B
};

// @description
// This is the global player struct offsets for versus mode (i.e. what you need
// to start a versus match)
struct css_Player * css_playersVS[] = {
    (void *) 0x800A4D28,
    (void *) 0x800A4D9C,
    (void *) 0x800A4E10,
    (void *) 0x800A4E84
};


#define css_TILE_HEIGHT 32
#define css_TILE_WIDTH 32

#define css_WINDOW_HEIGHT 100
#define css_WINDOW_WIDTH 65


// @description
// This is the line between the match options at the top and the character tiles
#define css_OPTIONS_TILES_DIV 30
#define css_TILES_WINDOWS_DIV 128

// @description
// These points from a rectangular boundary for the hand (implemented in 
// css_updatePosition())
#define css_MIN_HAND_X  28
#define css_MAX_HAND_X  (259 + css_TILE_WIDTH)
#define css_MIN_HAND_Y 10
#define css_MAX_HAND_Y 210

#define css_WINDOW_ULY 129

#define css_TILE_ULY 30
#define css_NUM_TILE_ROWS 3
#define css_TILE_LRY css_TILE_ULY + (css_NUM_TILE_ROWS * (css_TILE_WIDTH + 1))

// @description
// The initial starting hand positions.
#define css_handStartX(i)   (80 + ((i) * css_WINDOW_WIDTH + 1))
#define css_HAND_START_Y    css_WINDOW_ULY + 2



// tiles for all chars
struct css_Tile {
    u16 ulx;                        // tile x position
    u16 uly;                        // tile y position
    u16 * data;                     // image data
    enum css_Character character;   // character in the box
}; 

struct css_Tile css_tiles[] = {
    // row 1
    { 28, 30, NULL, css_MARIO},
    { 61, 30, NULL, css_FOX},
    { 94, 30, NULL, css_DK},
    {127, 30, NULL, css_SAMUS},
    {160, 30, NULL, css_LUIGI},
    {193, 30, NULL, css_LINK},
    {226, 30, NULL, css_YOSHI},
    {259, 30, NULL, css_FALCON},

    // row 2
    { 28, 63, NULL, css_KIRBY},
    { 61, 63, NULL, css_PIKACHU},
    { 94, 63, NULL, css_JIGGLYPUFF},
    {127, 63, NULL, css_NESS},
    {160, 63, NULL, 0},
    {193, 63, NULL, 0},
    {226, 63, NULL, 0},
    {259, 63, NULL, 0},

    // row 3
    { 28, 96, NULL, 0},
    { 61, 96, NULL, 0},
    { 94, 96, NULL, 0},
    {127, 96, NULL, 0},
    {160, 96, NULL, 0},
    {193, 96, NULL, 0},
    {226, 96, NULL, 0},
    {259, 96, NULL, 0}
};

// windows for p1-p4
// tiles for all chars
struct css_Window {
    u16 ulx;                        // tile x position
    u16 uly;                        // tile y position
    u16 * data;                     // image data of char
};

struct css_Window css_windows[] = {
    { 28, css_WINDOW_ULY, NULL},
    { 94, css_WINDOW_ULY, NULL},
    {160, css_WINDOW_ULY, NULL},
    {226, css_WINDOW_ULY, NULL}
};


// @description
// Updates the player structs based on current selections and settings on the
// CSS.
void css_updatePlayers(void);

// @description
// States for the hands that modify the character select screen. The states are
// described below
enum css_HandState {
    css_HAND_HOLDING_1 = 0,     // hand is holding p1 chip
    css_HAND_HOLDING_2 = 1,     // hand is holding p2 chip
    css_HAND_HOLDING_3 = 2,     // hand is holding p3 chip
    css_HAND_HOLDING_4 = 3,     // hand is holding p4 chip
    css_HAND_POINTING_WINDOWS,  // hand in initial state around windows
    css_HAND_POINTING_OPTIONS,  // hand pointing but at the options
    css_HAND_EMPTY,             // hand does not have chip (chip down)
    css_HAND_CATCHING,          // hand does not have chip (chip moving)
    css_HAND_DISABLED,          // hand is disabled (when controller not plugged in)
};

// @description
// Holds (x, y) position of the hand as well as what state the hand is in
struct css_Hand {
    u16 x;
    u16 y;
    enum css_HandState state;
    enum n64_Player player;
};

// @description
// An uninitalized array of four hands (one for each player).
struct css_Hand css_hands[4];

// States for the chips that select a character on the CSS. The states are
// described below
enum css_ChipState {
    css_CHIP_HELD_1 = 0,    // chip in hand of p1
    css_CHIP_HELD_2 = 1,    // chip in hand of p2
    css_CHIP_HELD_3 = 2,    // chip in hand of p3
    css_CHIP_HELD_4 = 3,    // chip in hand of p4 
    css_CHIP_DOWN,          // character selected
    css_CHIP_MOVING,        // chip moving from selected to hand
    css_CHIP_DISABLED       // chip offscreen/disabled
};

// @description
// Holds (x, y) position of the chip as well as what state the chip is in
struct css_Chip {
    u16 x;
    u16 y;
    enum css_ChipState state;
    enum n64_Player player;
};

// @description
// An uninitalized array of four chips (one for each player).
struct css_Chip css_chips[4];

// @description
// Initializes contents of the CSS (pretty simple)
void css_init(void);

// @description
// main() of the character select screen.
void css_loop(void);

// @description
// Draws the contents of the character select screen.
void css_draw(void);

// @description
// Updates the position of chips and hands on the character select screen. For
void css_updateCursorPosition(void);

// @description
// Updates the state of the chips and hand on the character select screen.
void css_updateCursorState(void);

// @description
// This is function actually launches the fight screen for VS. The css_Player
// struct for each player needs to be filled in first.
void css_startVersus(void);

// @description
// Number of frames that B has been held for on character select screen (one 
// value for each player)
u8 css_framesHeldB[4] = {
    0, 0, 0, 0
};

// @description
// Check for exit conditions. If exit condition met, returns TRUE.
bool css_exitTriggered(void);

// @description
// How many frames B must be held to exit the character select screen 
// (implemented in css_checkForExit())
#define css_HOLD_B_FRAMES 60

// @description
// When the hand is left of this value in the options screen.
#define css_BACK_BUTTON_RX 50

// TODO
// update costumes

// TODO
// implement MAN/COM/NOT
// @description
// Toggles what type (human, cpu, disabled) a window is. Unlike other Smash
// iterations, any player can toggle any players window, regardless if they
// have a character selected or a chip down. Functionally, this fixes the afk
// issue with ease.
void css_toggleType(void);

// @description 
// "from global.asm"
struct css_MatchSettings {
    u8 _0x0000;                 // 0x0000, unknown
    u8 stage;                   // contains the versus stage stage id
    u8 _0x0002;                 // 0x0002
    bool teams;                 // if teams are enabled, 0 = off, 1 = on
    u8 gameMode;                // 1 = time, 2 = stock, 3 = both
    u8 timeLimit;               // 2 = 2 min, 100 = infinite
    u8 stocks;                  // 0 = 1 stock
    u8 handicap;                // 0 = off, 1 = on, 2 = auto
    bool teamAttackEnabled;     // 0 off, 1 on
    bool stageSelectEnabled;    // 0 off, 1 on
    u8 damage;                  // 50 = 50%, 200 = 200%
};

struct css_MatchSettings * css_settingsVS = (void *) 0x800A4D08;
// TODO: better
#define css_TEAMS_ENABLE_X 280 - 16

// @description
// checks if teams should be toggled
void css_toggleTeams(void);

/*
        // keep this here for now
        // @ Description
        // Byte, 50 = 50%, 200 = 200%
        constant damage(0x800A4D13)

        // @ Description
        // Word, timer in second
        constant timer(0x800A4D1C)

        // @ Description
        // Byte, 0 = none, 5 = high
        constant item_frequency(0x800A4D24)

*/

// TODO
// selectable options screen

// TODO
// toggle teams

// TODO
// make man/com/not a button

// TODO
// check if ready to start match

// TODO
// no coms init

// TODO
// classic mode, btp, btt

#endif//__CSS_H__
