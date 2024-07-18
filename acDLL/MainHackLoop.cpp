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

	if (GetAsyncKeyState(VK_NUMPAD2) & 1) {	
		if (oneShotTramp.bActive)
		{
			oneShotTramp.ToggleTrampNSB();
			std::cout << "Disabling One Shot Trampoline." << std::endl;
		}
		oneShotDetour.ToggleDetour();
		std::cout << "One Shot Detour: " << (oneShotDetour.bActive) << std::endl;
	}

	if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
		if (oneShotDetour.bActive)
		{
			oneShotDetour.ToggleDetour();
			std::cout << "Disabling One Shot Detour." << std::endl;
		}
		oneShotTramp.ToggleTrampNSB();
		std::cout << "One Shot Trampoline: " << (oneShotTramp.bActive) << std::endl;
	}
}
