#ifndef __ADVENTURE_H__
#define __ADVENTURE_H__

void adventure_init(void);
bool adventure_hasInit = FALSE;
struct menu_Header * adventure_header = NULL;
void adventure_loop(void);

#endif//__ADVENTURE_H__