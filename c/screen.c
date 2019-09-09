#include "screen.h"

void screen_init(void) {
    screen_stack = malloc(screen_STACK_SIZE);
    screen_push(screen_TagHome);
}

void screen_push(enum screen_Tag tag) {
    screen_stack++;
    *screen_stack = tag;
}

enum screen_Tag screen_pop() {
    enum screen_Tag ret = *screen_stack;
    screen_stack--;
    return ret;
}

void screen_unwind(enum screen_Tag tag) {
    while (screen_current != tag) {
        screen_pop();
    }
}
