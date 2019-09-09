ROOTDIR         = ./tools
GCCN64PREFIX    = $(ROOTDIR)/bin/mips64-elf-
LINKFLAGS       = -L $(ROOTDIR)/lib -L $(ROOTDIR)/mips64-elf/lib -T19XXTE.ld -nostdlib
CFLAGS          = -std=gnu99 -march=vr4300 -mtune=vr4300 -mfix4300 -mabi=eabi -mgp32 -mlong32 -O0 -Wall -Werror -I./c -I./c/textures -I./libn64/include -c -G0
GCC             = $(GCCN64PREFIX)gcc
LD              = $(GCCN64PREFIX)ld
OBJCOPY         = $(GCCN64PREFIX)objcopy
BASS            = $(ROOTDIR)/_bass 
CRC             = $(ROOTDIR)/n64crc

PROG_NAME       = 19XXTE

all:
	$(GCC) 		$(PROG_NAME).c -o $(PROG_NAME).o $(CFLAGS) 
	$(LD)       $(PROG_NAME).o -o $(PROG_NAME).elf $(LINKFLAGS)
	$(OBJCOPY)  $(PROG_NAME).elf $(PROG_NAME).bin -O binary
	$(BASS)     -o $(PROG_NAME).z64 $(PROG_NAME).asm
	$(CRC)      $(PROG_NAME).z64
	rm -f *.o *.elf *.bin
	date

debug:
	$(GCC) 		$(PROG_NAME).c -o $(PROG_NAME).o $(CFLAGS) 
	$(LD)       $(PROG_NAME).o -o $(PROG_NAME).elf $(LINKFLAGS) 
	$(OBJCOPY)  $(PROG_NAME).elf $(PROG_NAME).bin -O binary
	$(BASS)     -o $(PROG_NAME).z64 $(PROG_NAME).asm
	$(CRC)      $(PROG_NAME).z64
	nm 			$(PROG_NAME).elf
	date

build:
	# clean
	# make clean

	# build tools
	cd tools; make
	cp tools/bass/bass/bass tools/_bass

	# remove bass git repository
	rm -rf tools/bass

clean:
	rm -f *.bin *.o *.elf *.z64

