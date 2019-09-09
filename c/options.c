
char * options_cinematicCamera[] = {
    "OFF",
    "ON",
    "RANDOM"
};

char * options_resultsScreen[] = {
    "SHOW",
    "SKIP"
};

char * options_sound[] = {
    "MONO",
    "STEREO"
};


void options_init(void) {
    options_header = menu_initHeader(menu_ULX, menu_ULY, menu_WIDTH, 0x0001, "Options");

    // menu_addEntry(header, description, type, value, min, max, funcPtr, strings, copyAddress, nextScreen);
    menu_addEntry(options_header, "Cinematic Camera", menu_TypeU8, 0, 0, 2, NULL, options_cinematicCamera, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Color Overlays", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Flash On Z-Cancel", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Hitbox Display", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Hold to Pause", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Improved Combo Meter", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Tech Chase Combo Meter", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Improved AI", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Neutral Spawns", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Results Screen", menu_TypeU8, FALSE, FALSE, TRUE, NULL, options_resultsScreen, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Salty Runback", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Screen Adjust", menu_TypeTitle, 0, 0, 0, NULL, NULL, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Sound", menu_TypeU8, FALSE, FALSE, TRUE, NULL, options_sound, NULL /* copyAddress */, screen_TagNone);
    menu_addEntry(options_header, "Stock Handicap", menu_TypeBool, FALSE, FALSE, TRUE, NULL, NULL, NULL /* copyAddress */, screen_TagNone);

    options_hasInit = TRUE;
}

void options_loop(void) {
    // print menu
    menu_standard(options_header);

    // add check for return
    if (joypad_wasPressed(joypad_B, n64_ANY)) {
        screen_pop();
    }
}