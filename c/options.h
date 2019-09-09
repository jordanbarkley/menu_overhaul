#ifndef __OPTIONS_H__
#define __OPTIONS_H__

void options_init(void);
bool options_hasInit = FALSE;
struct menu_Header * options_header = NULL;
void options_loop(void);

#endif//__OPTIONS_H__