#ifndef __MENU_H__
#define __MENU_H__

#define menu_CURSOR_WIDTH 6
#define menu_CURSOR_HEIGHT 6

#define menu_ULX 20
#define menu_ULY 20
#define menu_WIDTH 260 // 320 total - 10 scissor from each side - 20 from each side

// strings used in boolean type
char * menu_booleanStrings[] = {
    "OFF",
    "ON"
};

// type of entry
enum menu_Type {
//  menu_TypeS8,		// signed 8 bit integer
    menu_TypeU8,		// unsigned 8 bit integer
    menu_TypeX8,		// hexadecimal 8 bit integer
    
//  menu_TypeS16,		// signed 16 bit integer
    menu_TypeU16,		// unsigned 16 bit integer
    menu_TypeX16, 		// hexadecimal 16 bit integer

//  menu_TypeS32,		// signed 32 bit integer
    menu_TypeU32,		// unsigned 32 bit integer
    menu_TypeX32, 		// hexadecimal 32 bit integer

    menu_TypeTitle,     // none
    menu_TypeBool,		// boolean (on/off)
//  menu_TypeFunction,  // function runs when selected
//  menu_TypeString     // list of strings
};

// this is a page in the text menu
struct menu_Header {
    u16 ulx;                    // upper left x of menu
    u16 uly;                    // upper left y of mneu
    u16 width;                  // width of the menu
    u16 selection;				// currently selected row
    u16 totalEntries;           // total number of entries
    u16 color;                  // rgba5551 color of menu
    char * title;               // title of whole menu
    struct menu_Entry * head;	// first entry in linked list of menu_Entry
};

// this is a listener sort of action for menu_update
enum menu_Event {
    menu_EventUp,
    menu_EventDown,
    menu_EventLeft,
    menu_EventRight,
    menu_EventCancel,
    menu_EventConfirm
};

// this is a row in the text menu
struct menu_Entry {
    char * description;             // description of the row
    enum menu_Type type; 	        // type of entry
    u32 value;				        // current value
    u32 min;				        // minimum value allowed
    u32 max;				        // maximium value allowed
    enum screen_Tag nextScreen;     // next screen parameter
    void (*funcPtr)(); 		        // if not null and nextScreen = -1, function ran on a press
    char ** strings;                // if not null, array of strings to pull from
    void * copyAddress;             // if not null, menu_Entry.value is copied here
    struct menu_Entry * nextEntry;  // pointer to next in the list
};

/*
 * @description
 * Initializes all text menus.
 */
void menu_init();


/*
 * @description
 * Initializes a menu_Header (see the menu_Header struct above for paramater 
 * details).
 * 
 * @notes
 * selection   initialized to 0
 * head        initialized to NULL
 */
struct menu_Header * menu_initHeader(u16 ulx, u16 uly, u16 width, u16 color, char * title);

/*
 * @description
 * Initializes a menu_Entry (see the menu_Entry struct for parameter details)
 * and appends it to a menu_Header.
 * 
 * @notes
 * The functions following simplify life a little.
 */
void menu_addEntry(struct menu_Header * header, char * description, enum menu_Type type, u32 value, u32 min, u32 max, void * funcPtr, char ** strings, void * copyAddress, enum screen_Tag nextScreen);

/*
 * @description
 * Prints the contents of a menu as well as the cursor.
 */
void menu_print(struct menu_Header * header);

/*
 * @description
 * Copies all the values of entries to their copy addresses.
 */
void menu_copy(struct menu_Header * header);

/*
 * @description
 * Updates the menu for a given action. See menu_Event enum above for details. 
 */
void menu_update(struct menu_Header * header, enum menu_Event event);

/*
 * @description
 * Updates the menu in a "standard" way. Full control can be achieved by using
 * menu_update directly.
 */
void menu_standard(struct menu_Header * header);

/*
 * @description
 * Gets and entry based on current selection
 */
struct menu_Entry * menu_getEntry(struct menu_Header * header);

#endif