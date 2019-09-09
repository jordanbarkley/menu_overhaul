#ifndef __19XXTE_H__
#define __19XXTE_H__

#include <stddef.h>
#include "shorthand.h"
#include "n64.h"
#include "ssb.h"
#include "rcp.h"
#include "string.h"
#include "screen.h"
#include "font.h"
#include "background.h"
#include "color.h"
#include "memory.h"
#include "graphics.h"
#include "home.h"
#include "adventure.h"
#include "menu.h"
#include "versus.h"
#include "credits.h"
#include "options.h"
#include "css.h"

#include "memory.c"
#include "rcp.c"
#include "joypad.c"
#include "mips.c"
#include "graphics.c"
#include "string.c"
#include "menu.c"
#include "screen.c"
#include "home.c"
#include "adventure.c"
#include "versus.c"
#include "credits.c" 
#include "options.c"
#include "css.c"

#define ENTRY __attribute__((section(".entry")))

#define GAME_LOOP_HOOK 0x80400000
void gameLoop(u64 * dlist);

#endif
