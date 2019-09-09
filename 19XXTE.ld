/* 19XXTE.ld */

OUTPUT_FORMAT ("elf32-bigmips")
OUTPUT_ARCH (mips)
ENTRY (entry)

SECTIONS {

	/* start address at expansion pak */
	. = 0x80400000 ;

	/* smash functions */
	ssb_playFGM = 0x800269C0;
	ssb_playBGM = 0x80020AB4;
	ssb_dmaCopy = 0x80002CA0;
	ssb_getRandomInt = 0x80018994;
	ssb_startVersus = 0x800D6490;
	ssb_checkStickX = 0x8039089C;
	ssb_checkStickY = 0x80390950;

	/* smash variables */
	ssb_screenInterrupt = 0x800465D0;
	ssb_currentScreen = 0x800A4AD0;

	.text : 
	{
		FILL(0x00)
		LD_ADDR_TEXT_START = . ;
		*(.entry)
		*(.init)
		*(.text)
		*(.ctors)
		*(.dtors)
		*(.rodat)
		LD_ADDR_TEXT_END = . ;
	}

	.data : 
	{
		FILL(0xAA)
		LD_ADDR_DATA_START = . ;
		*(.data)
		*(.lit8)
		*(.lit4)
		. = ALIGN(16) ;
		_gp = . ;
		. += 8;
		LD_SSB_GP = . ;
		. += 8;
		*(.sdata)
		LD_ADDR_DATA_END = . ;
	}

	.bss(NOLOAD) : 
	{
		LD_ADDR_BSS_START = . ;
		*(.scommon)
		*(.sbss)
		*(COMMON)
		*(.bss)
		end = . ;
		LD_ADDR_BSS_END = . ;
		LD_ADDR_END = . ;
	}
	
}
