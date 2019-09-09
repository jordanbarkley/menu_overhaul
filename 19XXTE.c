#include "19XXTE.h"

void gameLoop(u64 * dlist) {
	// redefine global pointer
	mips_setGP();

	// update stick
	joypad_updateStick();

	// start graphics
	graphics_start(dlist);


	// checks for current screen (screw switch statements) when debug menu is up
	if (ssb_currentScreen == screen_TagDebugMenu) {
		graphics_drawTexture(10, 10, background_WIDTH, background_HEIGHT - 1, (u16 *) background_rgba5551);

		if (screen_current == screen_TagHome) {
			home_loop();
		
		} else if (screen_current == screen_TagAdventure) {
			adventure_loop();

		} else if (screen_current == screen_TagVersus) {
			versus_loop();

		} else if (screen_current == screen_TagCredits) {
			credits_loop();
		
		} else if (screen_current == screen_TagOptions) {
			options_loop();
		
		} else if (screen_current == screen_TagCharacterSelect) {
			css_loop();

		} else if (screen_current == screen_TagDisabled) {
			// do nothing
		
		} else {
			// screen not implemented, warn user
			graphics_drawString(30, 20, "Screen invalid. Press 'B' to return.");
			
			// add check for return
			if (joypad_wasPressed(joypad_B, n64_ANY)) {
				screen_pop();
			}
		}

	}

	// end graphics
	graphics_end();

	// exit
	mips_restoreGP();
}

ENTRY void entry() {
	// redefine global pointer
	mips_setGP();

	// check for expansion pack
	u32 * expansion = (u32 *) 0x80000318;
	if (*expansion == 0x00800000) {
		ssb_playFGM(0xA4);
		ssb_playBGM(0, 0);
	} else {
		ssb_playFGM(0x00);
	}

	// inits
	memory_init();
	rcp_init();
	screen_init();
	home_init();
	adventure_init();
	versus_init();
	credits_init();
	options_init();
	css_init();

	// set hook to gameLoop
	u32 * hook = (u32 *) GAME_LOOP_HOOK;
	*hook = mips_J((u32) &gameLoop);
	hook++;
	*hook = mips_NOP();

	// restore gp and move on
	mips_restoreGP();
}

