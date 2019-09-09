// Pause.asm (original by Fray)
if !{defined __PAUSE__} {
define __PAUSE__()
print "included Pause.asm\n"

// @ Description
// Hold to pause is implemented in this file.

include "Toggles.asm"
include "OS.asm"

scope Pause {

    // @ Description
    // number of frames pause needs to be held to pause
    constant NUM_FRAMES(30)
    
    // @ Description
    // This is a hook into the pause function. It increment input_table[player] until that value
    // reaches NUM_FRAMES. One NUM_FRAMES is reached, the function continues as normal.
    scope hold_: {
        OS.patch_start(0x0008F88C, 0x8011408C)
        j       Pause.hold_
        nop
        _hold_return:
        OS.patch_end()

        // s1 holds button pressed/held etc. struct
        // s3 holds port number checking for pause
        // t7 needs to hold 0 at the end of this function to prevent pause

        lhu     t6, 0x0002(s1)              // original line 1
        andi    t7, t6, 0x1000              // original line 2

        // this feature is always enabled in TE. It is toggleable in CE.
if {defined __CE__} {
        Toggles.guard(Toggles.entry_hold_to_pause, _hold_return)
} // __CE__

        addiu   sp, sp,-0x0010              // allocate stack space
        sw      t0, 0x0004(sp)              // ~
        sw      t1, 0x0008(sp)              // ~
        sw      t2, 0x000C(sp)              // save registers

        li      t0, input_table             // t0 = input_table
        add     t0, t0, s3                  // t0 = input_table + offset
        lhu     t6, 0x0000(s1)              // original line 1 (modified)
        andi    t7, t6, 0x1000              // original line 2
        beqz    t7 ,_end                    // return
        or      t1, r0, r0                  // t1 = pX_frames = 0

        _held:
        lb      t1, 0x0000(t0)              // t1 = pX_frames
        addiu   t1, t1, 0x0001              // pX_frames++	
        li      t2, NUM_FRAMES              // t2 = NUM_FRAMES
        slt     t7, t2, t1                  // t7 = 1 if NUM_FRAMES < pX_frames; else t7 = 0
        bnel    t7, r0, _end                // if t7 == 1, run next line
        or      t1, r0, r0                  // t1 = 0 (hitstun bug fix)

        _end:
        sb      t1, 0x0000(t0)              // set pX frames held
        lw      t0, 0x0004(sp)              // ~
        lw      t1, 0x0008(sp)              // ~
        lw      t2, 0x000C(sp)              // restore registers
        addiu   sp, sp, 0x0010              // deallocate stack space
        j       _hold_return                // return
        nop

        input_table:
        db 0x00                             // p1
        db 0x00                             // p2
        db 0x00                             // p3
        db 0x00                             // p4
    }

}

} // __PAUSE__