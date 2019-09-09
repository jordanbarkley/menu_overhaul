void versus_init(void) {
    versus_header = menu_initHeader(menu_ULX, menu_ULY, menu_WIDTH, 0x0001, "Versus");
    menu_addEntry(versus_header, "Standard", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagStandard);
    menu_addEntry(versus_header, "Tournament", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelect);
    menu_addEntry(versus_header, "Special", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL, screen_TagCharacterSelect);

    versus_hasInit = TRUE;
}

void versus_loop(void) {
    // print menu
    menu_standard(versus_header);

    // add check for return
    if (joypad_wasPressed(joypad_B, n64_ANY)) {
        screen_pop();
    }
}