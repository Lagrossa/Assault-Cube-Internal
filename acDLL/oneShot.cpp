#include "pch.h"
#include "oneShot.h"
#include "SetupHooksAndNops.h"

void __declspec(naked)OneShot() {

	__asm {
		mov eax, edi //Run Stolen Bytes First
		push ecx
		mov ecx, ebx
		add ecx, 0x238
		cmp[ecx], 1 // Blue Team?
		pop ecx
		je myTeam
		sub[ebx + 04], 0x3E8 // One Shot!
		jmp oneShotDetour.returnJumpDetour

	myTeam:
		jmp oneShotDetour.returnJumpDetour
	}
}
