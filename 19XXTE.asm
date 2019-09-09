// 19XX.asm
if !{defined __TE__} {
    define __CE__()
}

// copy fresh rom
origin  0x00000000
insert  "roms/original.z64"

// change ROM name
origin  0x00000020
db  "19XX Seabass"
db  0x00

// static
origin  0x01000000
base    0x80400000

c_start_:
insert  "19XXTE.bin"


include "mips/AI.asm"
include "mips/BGM.asm"
include "mips/Boot.asm"
include "mips/Camera.asm"
include "mips/Character.asm"
include "mips/Cheats.asm"
include "mips/Color.asm"
include "mips/Combo.asm"
include "mips/Costumes.asm"
include "mips/Crash.asm"
include "mips/FD.asm"
include "mips/FGM.asm"
include "mips/GameEnd.asm"
include "mips/Global.asm"
include "mips/Handicap.asm"
include "mips/Hazards.asm"
include "mips/Hitbox.asm"
include "mips/Joypad.asm"
include "mips/Menu.asm"
include "mips/OS.asm"
include "mips/Overlay.asm"
// include "mips/PAL.asm"
include "mips/Pause.asm"
include "mips/Practice.asm"
include "mips/RCP.asm"
include "mips/Settings.asm"
include "mips/Shield.asm"
include "mips/Spawn.asm"
include "mips/SRAM.asm"
include "mips/Stages.asm"
include "mips/String.asm"
include "mips/Texture.asm"
include "mips/TimedStock.asm"
include "mips/Timeouts.asm"
include "mips/Toggles.asm"
include "mips/Training.asm"

// extend ROM to 32 MBs
origin  0x1FFFFFF
db 0x00

// disable menu init on debug screen 80371414
// base    0x80369D78
// origin  0x001AC1E8
// jr      ra 
// nop
