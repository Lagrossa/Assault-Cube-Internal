#include "pch.h"
#include "infAmmo.h"
#include "SetupHooksAndNops.h"

void __declspec(naked)InfAmmo() {

	__asm {
		mov esi, [esi + 0x14]
		inc[esi]
		jmp infAmmoDetour.returnJumpDetour
	}
}