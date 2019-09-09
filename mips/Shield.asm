// Shield.asm
if {defined __CE__} {
if !{defined __SHIELD__} {
define __SHIELD__()
print "included Shield.asm\n"

// @ Description
// Thise file changes shield colors to match port colors.

include "OS.asm"
include "Global.asm"
include "Color.asm"
include "Character.asm"

scope Shield {

    // @ Description
    // This function overwrites the logic to generate a shield color. This is a controversial "fix"
    // and will soon be replaced by selectable shield colors.
    scope color_fix_: {
        OS.patch_start(0x0007C8E8, 0x801010E8)
        j       color_fix_
        nop
        _color_fix_return:
        OS.patch_end()

        or      t6, t7, t5                  // original line 1
        // t8 needs to hold rgba32 color by end of function

        addiu   sp, sp,-0x0020              // allocate stack space
        sw      t0, 0x0004(sp)              // ~
        sw      t1, 0x0008(sp)              // ~
        sw      t2, 0x000C(sp)              // ~
        sw      a0, 0x0010(sp)              // ~
        sw      ra, 0x0014(sp)              // ~
        sw      v0, 0x0018(sp)              // save registers

        lw      t1, 0x0084(a0)              // t1 = ?
        lw      t1, 0x0018(t1)              // t1 = port shielding
        move    a0, t1                      // a0 - player
        jal     Character.get_struct_       // a0 - player (p1 = 0, p4 = 3)
        nop
        move    t0, v0                      // t0 = player pointer

        _teams_check:
        li      t2, Global.vs.teams         // t2 = pointer to teams byte
        lb      t2, 0x0000(t2)              // t2 = teams
        beqz    t2, _cpu                    // if (!teams), skip
        nop
        lb      t1, 0x000C(t0)              // t1 = team

        // team 0 = red, team 1 = blue, team 2 green
        // green is in not in table[2], it's in table[3]
        // 0 = 0b00, 1 = 0b01, 2 = 0b10
        // *shift team right 1*
        // (0 >> 1) = 0b00, (1 >> 1) = 0b00, (2 >> 1) = 0b01 
        // so t1 + (t1 >> 1) = team color

        srl     t2, t1, 0x0001              // t2 = (t1 >> 1)
        add     t1, t1, t2                  // t2 = correct team color
        b       _human_or_team              // ~
        nop

        _cpu:
        lb      t0, 0x0023(t0)              // t6 = type (player = 0, cpu = 1)
        bne     t0, r0, _return             // branch to human/cpu
        ori     t8, r0, 0x00C0              // cpu shield = 0x000000C0

        _human_or_team:
        sll     t1, t1, 0x0002              // ~
        li      t8, table                   // ~
        add     t8, t8, t1                  // ~
        lw      t8, 0x0000(t8)              // t8 = table[player_or_team]
        ori     t8, t8, 0x00C0              // set alpha channel

        _return:
        lw      t0, 0x0004(sp)              // ~
        lw      t1, 0x0008(sp)              // ~
        lw      a0, 0x0010(sp)              // ~
        lw      ra, 0x0014(sp)              // ~
        lw      v0, 0x0018(sp)              // restore registers
        addiu   sp, sp, 0x0020              // deallocate stack space
        j       _color_fix_return           // return
        nop

        table:
        dw (0xFFFFFF00 & Color.high.RED)    // p1
        dw (0xFFFFFF00 & Color.high.BLUE)   // p2
        dw (0xFFFFFF00 & Color.high.YELLOW) // p3
        dw (0xFFFFFF00 & Color.high.GREEN)  // p4
    }

}

} // __SHIELD__
} // __CE__