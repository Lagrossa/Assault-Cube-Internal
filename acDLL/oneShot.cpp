#include "pch.h"
#include "oneShot.h"
#include "SetupHooksAndNops.h"

void __declspec(naked)OneShot() {

	__asm {
		mov eax, edi //Run Stolen Bytes First
		push ecx
		mov ecx, ebx
		cmp[ecx + 238], 1 // Blue Team?
		pop ecx
		je myTeam
		sub[ebx + 04], edi
		jmp oneShotDetour.returnJumpDetour

	myTeam:
		jmp oneShotDetour.returnJumpDetour
	}
}
