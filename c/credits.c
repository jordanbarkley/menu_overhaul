void credits_init(void) {
    credits_header = menu_initHeader(menu_ULX, menu_ULY, menu_WIDTH, 0x0001, "Credits");
    menu_addEntry(credits_header, "Cyjorg", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagNone);
    menu_addEntry(credits_header, "Fray", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagNone);
    menu_addEntry(credits_header, "tehz", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagNone);
    menu_addEntry(credits_header, "cennis", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagNone);

    credits_hasInit = TRUE;
}

void credits_loop(void) {
    // print menu
    menu_standard(credits_header);

    // add check for return
    if (joypad_wasPressed(joypad_B, n64_ANY)) {
        screen_pop();
    }
}