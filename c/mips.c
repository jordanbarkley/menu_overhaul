#include "mips.h"
#include "shorthand.h"

void mips_setGP() {
	// this makes sure that my code is never reordered
	__asm__ volatile(".set noreorder");

	// save current gp
	__asm__ volatile("addiu $sp, $sp, 0xFFF8");
	__asm__ volatile("sw	$t0, 0x0004($sp)");
	__asm__ volatile("la 	$t0, LD_SSB_GP");
	__asm__ volatile("sw 	$gp, 0x0000($t0)");
	__asm__ volatile("lw 	$t0, 0x0004($sp)");
	__asm__ volatile("addiu $sp, $sp, 0x0008");

	// get new gp
	__asm__ volatile("la 	$gp, _gp");
}

void mips_restoreGP() {
	__asm__ volatile("la 	$gp, LD_SSB_GP");
	__asm__ volatile("lw 	$gp, 0x0000($gp)");
}

