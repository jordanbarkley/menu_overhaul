// original plan: break this down completely lol (bad)

_0x80131B58:
addiu   a2, r0, 0x0001          // a2 = 1, TRUE, etc.
lui     a3, 0x800A              // ~
lui     at, 0x8013              // ~
addiu   a3, a3, 0x4D08          // a3 = 0x 800A4D08 (address of VS struct in Global.asm)
sw      a2, 0x2960(at)          // 0x80132960 = 1 (?)
andi    v0, r0, 0x00FF          // v0 = 0
sb      v0, 0x0004(a3)          // 0x0004(vs_struct, unknown, 0c) = 0
sb      r0, 0x0005(a3)          // 0x0005(vs_struct, unknown, 0d) = 0
lui     a0, 0x800A              // ~
lbu     a0, 0x4D2A(a0)          // a0 = *0x800A4D2A (part of player 1 vs struct, unknown)
lui     v1, 0x800A              // ~
lui     at, 0x800A              // ~

// case 1
beql    a0, r0, 0x80131BA4      // ~
lbu     t6, 0x0004(a3)          // t6 = 0x0004(vs_struct, unknown, 0c) = 0

// case 2
beq     a0, a2, 0x80131BB0      // ~
addiu   t8, v0, 0x0001          // t8 = v0 + 1 = 1

// case 3
beq     r0, r0, 0x80131BB4      // ~
nop

// default(?)
lbu     t6, 0x0004(a3)          // same as case 1

_0x80131BA4:
addiu   t7, t6, 0x0001          // t7 = t6 + 1 = 1
beq     r0, r0, 0x80131BB4      // ~
sb      t7, 0x0004(a3)          // 0x 800A4D08 (address of VS struct in Global.asm) = 1
sb      t8, 0x0005(a3)          // 0x 800A4D09 (global.vs.stage) = ?

_0x80131BB4:
sb      r0, 0x4D2C(at)          // 0x800A4D2C = 0 (part of player 1 vs struct, unknown)
lui     at, 0x800A              // ~
sb      r0, 0x4D30(at)          // 0x800A4D30 = 0
lui     at, 0x800A              // ~
sb      r0, 0x4D32(at)          // 0x800A4D32 = 0
lbu     v1, 0x4D9E(v1)          // v1 = *800A4D9E (some global)
lui     at, 0x800A              // ~
addiu   t7, r0, 0x0002          // t7 = 2
beq     v1, r0, 0x80131BEC      // ~
addiu   t8, r0, 0x0002          // t8 = 2
beql    v1, a2, 0x80131C00      // ~

... this is dumb

// new plan, keep track of writes
vaddr       value       size    notes (where value came from, what value means)
80132690    0x00000001  word    a2 of function
800A4D0D    0x00        byte    r0
800A4D0C    0x01        byte    (0x0004(a3)) + 1
800A4D30    0x00        byte    r0
800A4D32    0x02        byte    0x0004(a3) + 1, literally 0x4(a3)++, a3 struct important
800A4DA4    0x01        byte    direct write


03090005 03000001 03010300
