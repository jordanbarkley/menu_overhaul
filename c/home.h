#ifndef __HOME_H__
#define __HOME_H__

// initializes main menu "home"
void home_init(void);

bool home_hasInit = FALSE;
struct menu_Header * home_header = NULL;

// gameloop for home
void home_loop(void);

#endif//__HOME_H__