#include "pch.h"
#include "oneShotTramp.h"

void __declspec()OneShotTramp() {
	__asm {
		mov ecx, ebx
		add ecx, 0x238
		cmp[ecx], 1 // Blue Team?
		je myTeam
		sub[ebx + 04], 0x64 // One Shot!

	myTeam :
		nop //nuthin'
	}
	
}
