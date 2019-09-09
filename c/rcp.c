#include "shorthand.h"
#include "rcp.h"

u64 * rcp_displayListStart;
u64 * rcp_displayListCurr;

#define rcp_DISPLAY_LIST_SIZE 0x20000

void rcp_init() {
    // allocate memory for displaylist
    rcp_displayListStart = malloc(rcp_DISPLAY_LIST_SIZE);
    rcp_displayListCurr = rcp_displayListStart;
    rcp_displayListEnd = rcp_displayListStart + rcp_DISPLAY_LIST_SIZE;
}

void rcp_append(u64 command) {
    if (rcp_displayListEnd == rcp_displayListCurr) {
        // TODO: handle display list too long
        asm("break");
    }

    // append command and increment displayList pointer
    *rcp_displayListCurr = command;
    rcp_displayListCurr++;
}

void rcp_flush() {
    rcp_displayListCurr = rcp_displayListStart;
}


void rcp_hook(u64 * dlist) {
    *dlist = rcp_branchList(rcp_displayListStart);
}
