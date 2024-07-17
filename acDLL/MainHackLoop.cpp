#include "pch.h"
#include "MainHackLoop.h"
#include "SetupHooksAndNops.h"
#include <iostream>

bool bBreakHackThreadWhileLoop = false;

void MainHackLoop() {
	if (GetAsyncKeyState(VK_END) & 1) {
		mainHackLoopTramp.ToggleTrampSBL();
		bBreakHackThreadWhileLoop = true;
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		if (infAmmoNop.bActive)
		{
			infAmmoNop.ToggleNop();
			std::cout << "Disabling NOP." << std::endl;
		}
		infAmmoDetour.ToggleDetour();
		std::cout << "Infinite Ammo Detour: " << (infAmmoDetour.bActive) << std::endl;
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		if (infAmmoDetour.bActive)
		{
			infAmmoDetour.ToggleDetour();
			std::cout << "Disabling Detour." << std::endl;
		}
		infAmmoNop.ToggleNop();
		std::cout << "Infinite Ammo NOP: " << (infAmmoNop.bActive) << std::endl;
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {		
		oneShotDetour.ToggleDetour();
		std::cout << "One Shot Red Team: " << (oneShotDetour.bActive) << std::endl;
	}
}
