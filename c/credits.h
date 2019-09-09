#ifndef __CREDITS_H__
#define __CREDITS_H__

void credits_init(void);
bool credits_hasInit = FALSE;
struct menu_Header * credits_header = NULL;
void credits_loop(void);

#endif//__CREDITS_H__