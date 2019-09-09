u32 string_length(char * string) {
    u32 length = 0;
    
    // iterate until null character
    while (*string != '\0') {
        length++;
        string++;
    }

    return length;
}
