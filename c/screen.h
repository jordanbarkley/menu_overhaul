#ifndef __SCREEN_H__
#define __SCREEN_H__

// maximum number of screens in stack
#define screen_STACK_SIZE 16

enum screen_Tag {
    screen_TagDebugMenu = 2,
    screen_TagHome = 0x100,
    screen_TagAdventure,
    screen_TagCharacterSelect,
    screen_TagCharacterSelectNoComs,
    screen_TagVersus,
    screen_TagStandard,
    screen_TagItemSwitch,
    screen_TagStageSwitch,
    screen_TagMusicSwitch,
    screen_TagOptions,
    screen_TagData,
    screen_TagCredits,
    screen_TagSnake,
    screen_TagNone,
    screen_TagDisabled
};

/*
 * @description
 * Array of size screen_STACK_SIZE used to display which screen should be used
 */
enum screen_Tag * screen_stack;

/*
 * @description
 * Allocates space for screen_stack
 */
void screen_init(void);

/*
 * @description
 * Add a screen onto the stack.
 */
void screen_push(enum screen_Tag tag);

/*
 * @description
 * Remove a screen from the stack
 */
enum screen_Tag screen_pop();

/*
 * @description
 * Remove every screen up until tag with pop.
 */
void screen_unwind(enum screen_Tag tag);

/*
 * @description
 * Get current screen
 */
#define screen_current  (*screen_stack)

#endif//__SCREEN_H__