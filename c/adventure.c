void adventure_init(void) {
    adventure_header = menu_initHeader(menu_ULX, menu_ULY, menu_WIDTH, 0x0001, "Adventure");
    menu_addEntry(adventure_header, "Classic", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelectNoComs);
    menu_addEntry(adventure_header, "Training", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelect);
    menu_addEntry(adventure_header, "Break the Targets", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelectNoComs);
    menu_addEntry(adventure_header, "Board the Platforms", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelectNoComs);

    adventure_hasInit = TRUE;
}

void adventure_loop(void) {
    // print menu
    menu_standard(adventure_header);

    // add check for return
    if (joypad_wasPressed(joypad_B, n64_P1)) {
        screen_pop();
    }
}