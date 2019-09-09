if !{defined __PAL__} {
define __PAL__()
print "included PAL.asm\n"

include "OS.asm"

scope PAL {

    OS.patch_start(0x3E0BC, OS.NULL)
    //dw 0x0404233A
    //dw 0x00000271
    //dw 0x00150C69
    //dw 0x0C6F0C6E
    //dw 0x00800300
    //dw 0x002F0269
    //dw 0x0009026B
    OS.patch_end()

    OS.patch_start(0x3E0E0, OS.NULL)
    //dw 0x002F0269
    //dw 0x0009026B
    OS.patch_end()

    scope update_vi_: {
        OS.patch_start(0x0003684C, 0x80035C4C)
        // j       update_vi_
        // nop
        _update_vi_return:
        OS.patch_end()

        lw      t9, 0x000C(s0)              // original line 1
        sw      t9, 0x0000(t0)              // original line 2

        // this block replaces the values of the video interface registers
        // at 0xA4400XX to match the PAL version of the game
        
        lui     t0, 0xA440                  // t0 = vi_registers
        li      t1, 0x0404233A              // ~
        sw      t1, 0x0014(t0)              // ~
        li      t1, 0x00000271              // ~
        sw      t1, 0x0018(t0)              // ~
        li      t1, 0x00150C69              // ~
        sw      t1, 0x001C(t0)              // ~
        li      t1, 0x0C6F0C6E              // ~
        sw      t1, 0x0020(t0)              // ~
        li      t1, 0x00800300              // ~
        sw      t1, 0x0024(t0)              // ~
        li      t1, 0x002F0269              // ~
        sw      t1, 0x0028(t0)              // ~
        li      t1, 0x0009026B              // ~
        sw      t1, 0x002C(t0)              // update VI registers
        j       _update_vi_return           // return to function
        nop
    }
}

} // __PAL__

