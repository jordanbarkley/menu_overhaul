void home_init(void) {
    // create menu header
    home_header = menu_initHeader(menu_ULX, menu_ULY, menu_WIDTH, 0x0001, "19XX Seabass");
    menu_addEntry(home_header, "Adventure", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagAdventure);
    menu_addEntry(home_header, "Versus", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagVersus);
    menu_addEntry(home_header, "Options", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagOptions);
    menu_addEntry(home_header, "Data", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagData);
    menu_addEntry(home_header, "Credits", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCredits);

    // set init finished
    home_hasInit = TRUE;
}

void home_loop(void) {
    // print the home menu (no back check)
    menu_standard(home_header);
}