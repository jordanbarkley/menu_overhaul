// to do: add COP0 and COP1 instructions (maybe exception instructions)
// to do: test this stuff
#ifndef __MIPS_H__
#define __MIPS_H__

#include "shorthand.h"

void mips_restoreGP();

// mips general purpose registers (do not follow file_identifier format)
#define r0 0x00
#define at 0x01
#define v0 0x02
#define v1 0x03
#define a0 0x04
#define a1 0x05
#define a2 0x06
#define a3 0x07
#define t0 0x08
#define t1 0x09
#define t2 0x0A
#define t3 0x0B
#define t4 0x0C
#define t5 0x0D
#define t6 0x0E
#define t7 0x0F
#define s0 0x10
#define s1 0x11
#define s2 0x12
#define s3 0x13
#define s4 0x14
#define s5 0x15
#define s6 0x16
#define s7 0x17
#define t8 0x18
#define t9 0x19
#define k0 0x1A
#define k1 0x1B
#define gp 0x1C
#define sp 0x1D
#define s8 0x1E
#define ra 0x1F

// mips floating point registers
// (not actually defined, just used 0-31 in opcodes for f0-f31)

// mips helper macros
// r-type instructions (registers)
// op 	rd, rs, rt
// op   rd, rs, sa
// op     rs    rt    rd    sa    func
// 000000 00000 00000 00000 00000 000000
#define mips_R(op, rd, rs, rt, sa, func) \
	((op << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (sa << 6) | func)

#define mips_ADD(rd, rs, rt) 		mips_R(00, rd, rs, rt, 00, 32)
#define mips_ADDU(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 33)
#define mips_AND(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 36)
#define mips_DADD(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 44)
#define mips_DADDU(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 45)
#define mips_DDIV(rs, rt)			mips_R(00, 00, rs, rt, 00, 30)
#define mips_DDIVU(rs, rt)			mips_R(00, 00, rs, rt, 00, 31)
#define mips_DIV(rs, rt)			mips_R(00, 00, rs, rt, 00, 26)
#define mips_DIVU(rs, rt)			mips_R(00, 00, rs, rt, 00, 27)
#define mips_DMULT(rs, rt)			mips_R(00, 00, rs, rt, 00, 28)
#define mips_DMULTU(rs, rt)			mips_R(00, 00, rs, rt, 00, 29)
#define mips_DSLL(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 56)
#define mips_DSLL32(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 60)
#define mips_DSLLV(rd, rt, rs)		mips_R(00, rd, rs, rt, 00, 20)
#define mips_DSRA(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 59)
#define mips_DSRA32(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 63)
#define mips_DSRAV(rd, rt, rs)		mips_R(00, rd, rs, rt, 00, 23)
#define mips_DSRL(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 58)
#define mips_DSRL32(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 62)
#define mips_DSRLV(rd, rt, rs)		mips_R(00, rd, rs, rt, 00, 22)
#define mips_DSUB(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 46)
#define mips_DSUBU(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 47)
#define mips_MFHI(rd)				mips_R(00, rd, 00, 00, 00, 16)
#define mips_MFLO(rd)				mips_R(00, rd, 00, 00, 00, 18)
#define mips_MTHI(rs)				mips_R(00, 00, rs, 00, 00, 17)
#define mips_MTLO(rs)				mips_R(00, 00, rs, 00, 00, 19)
#define mips_MULT(rs, rt)			mips_R(00, 00, rs, rt, 00, 24)
#define mips_MULTU(rs, rt)			mips_R(00, 00, rs, rt, 00, 25)
#define mips_NOR(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 39)
#define mips_OR(rd, rs, rt)			mips_R(00, rd, rs, rt, 00, 37)
#define mips_SLL(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 00)
#define mips_SLLV(rd, rt, rs)		mips_R(00, rd, rs, rt, 00, 04)
#define mips_SLT(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 42)
#define mips_SLTU(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 43)
#define mips_SRA(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 03)
#define mips_SRAV(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 07)
#define mips_SRL(rd, rt, sa)		mips_R(00, rd, 00, rt, sa, 02)
#define mips_SRLV(rd, rt, rs)		mips_R(00, rd, rs, rt, 00, 06)
#define mips_SUB(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 34)
#define mips_SUBU(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 35)
#define mips_XOR(rd, rs, rt)		mips_R(00, rd, rs, rt, 00, 38)

// i-type instructions (immediate)
// op 	rt, rs, i
// op     rs    rt    immediate
// 000000 00000 00000 0000000000000000
#define mips_I(op, rt, rs, im) \
	((op << 26) | (rs << 21) | (rt << 16) | (im))

#define mips_ADDI(rt, rs, im)		mips_I(08, rt, rs, im)
#define mips_ADDIU(rt, rs, im)		mips_I(09, rt, rs, im)
#define mips_ANDI(rt, rs, im) 		mips_I(12, rt, rs, im)
#define mips_DADDI(rt, rs, im)		mips_I(24, rt, rs, im)
#define mips_DADDIU(rt, rs, im) 	mips_I(25, rt, rs, im)
#define mips_LUI(rt, im) 			mips_I(15, rt, 00, im)
#define mips_ORI(rt, rs, im)		mips_I(13, rt, rs, im)
#define mips_SLTI(rt, rs, im)		mips_I(10, rt, rs, im)
#define mips_SLTIU(rt, rs, im)		mips_I(11, rt, rs, im)
#define mips_XORI(rt, rs, im) 		mips_I(14, rt, rs, im)

// "m-type" instruction (load/store i-type)
// op 	rt, i(rs)
// op     rs    rt    immediate
// 000000 00000 00000 0000000000000000
#define mips_M(op, rt, im, rs) \
	mips_I(op, rt, rs, im)

#define mips_LB(rt, im, rs)			mips_M(32, rt, im, rs)
#define mips_LBU(rt, im, rs)		mips_M(36, rt, im, rs)
#define mips_LD(rt, im, rs)			mips_M(55, rt, im, rs)
#define mips_LDL(rt, im, rs)		mips_M(26, rt, im, rs)
#define mips_LDR(rt, im, rs)		mips_M(27, rt, im, rs)
#define mips_LH(rt, im, rs)			mips_M(33, rt, im, rs)
#define mips_LHU(rt, im, rs)		mips_M(37, rt, im, rs)
#define mips_LL(rt, im, rs)			mips_M(48, rt, im, rs)
#define mips_LLD(rt, im, rs)		mips_M(52, rt, im, rs)
#define mips_LW(rt, im, rs)			mips_M(35, rt, im, rs)
#define mips_LWL(rt, im, rs)		mips_M(34, rt, im, rs)
#define mips_LWR(rt, im, rs)		mips_M(38, rt, im, rs)
#define mips_LWU(rt, im, rs)		mips_M(39, rt, im, rs)
#define mips_SB(rt, im, rs)			mips_M(40, rt, im, rs)
#define mips_SC(rt, im, rs)			mips_M(56, rt, im, rs)
#define mips_SCD(rt, im, rs)		mips_M(60, rt, im, rs)
#define mips_SD(rt, im, rs)			mips_M(63, rt, im, rs)
#define mips_SDL(rt, im, rs)		mips_M(44, rt, im, rs)
#define mips_SDR(rt, im, rs)		mips_M(45, rt, im, rs)
#define mips_SH(rt, im, rs)			mips_M(41, rt, im, rs)
#define mips_SW(rt, im, rs)			mips_M(43, rt, im, rs)
#define mips_SWL(rt, im, rs)		mips_M(42, rt, im, rs)
#define mips_SWR(rt, im, rs)		mips_M(46, rt, im, rs)

// b-type instructions
// op   rs, rt, offset
// op     rs    rt    instruction to skip (signed)
// 000000 00000 00000 0000000000000000
#define mips_B(op, rs, rt, im) \
	((op << 26) | (rs & << 21) | (rt << 16) | (im))

#define mips_BEQ(rs, rt, im)		mips_B(04, rs, rt, im)
#define mips_BEQL(rs, rt, im)		mips_B(20, rs, rt, im)
#define mips_BGEZ(rs, im)			mips_B(01, rs, 01, im)
#define mips_BGEZAL(rs, im)			mips_B(01, rs, 17, im)
#define mips_BGEZALL(rs, im)		mips_B(01, rs, 19, im)
#define mips_BGEZL(rs, im)			mips_B(01, rs, 03, im)
#define mips_BGTZ(rs, im)			mips_B(07, rs, r0, im)
#define mips_BGTZL(rs, im)			mips_B(23, rs, r0, im)
#define mips_BLEZ(rs, im)			mips_B(06, rs, r0, im)
#define mips_BLEZL(rs, im)			mips_B(22, rs, r0, im)
#define mips_BLTZ (rs, im)			mips_B(01, rs, r0, im)
#define mips_BLTZAL(rs, im)			mips_B(01, rs, 16, im)
#define mips_BLTZALL(rs, im)		mips_B(01, rs, 18, im)
#define mips_BLTZL(rs, im)			mips_B(01, rs, 02, im)
#define mips_BNE(rs, rt, im)		mips_B(05, rs, rt, im)
#define mips_BNEL(rs, rt, im)		mips_B(21, rs, rt, im)
#define mips_BNEZ(rs, im)			mips_B(05, rs, r0, im)

// j-type
#define mips_J(im) 					(0x08000000 | ((im & 0xFFFFFF) >> 2))
#define mips_JAL(im) 				(0x0C000000 | ((im & 0xFFFFFF) >> 2))
#define mips_JR(rs)  				((rs << 21) | 8)

// others
#define mips_BREAK()				(0x0000000D)
#define mips_MFC0(rt, fs) 			((16 << 26) | (0 << 21) | (rt << 16) | (fs << 11))
#define mips_MTC0(rt, fs) 			((16 << 26) | (4 << 21) | (rt << 16) | (fs << 11))
#define mips_NOP() 					(0x00000000)

#endif
