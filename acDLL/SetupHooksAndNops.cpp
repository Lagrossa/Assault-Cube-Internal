#include "pch.h"
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"
#include "memory.h"
#include "infAmmo.h"
#include "oneShot.h"

Hook mainHackLoopTramp;
Hook infAmmoDetour;
Nop infAmmoNop;
Hook oneShotDetour;

void SetupHooksAndNops() {
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle(L"ac_client.exe"); //Get module base for AssaultCube. 
	BYTE* moduleBaseOpenGL = (BYTE*)GetModuleHandle(L"opengl32.dll"); //Module for OPEN GL

	//Main Hack Loop
	BYTE* mainHackLoopHookDst = (moduleBaseOpenGL + 0x4841E);
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//Inf Ammo Detour
	BYTE* infAmmoDetourDst = (moduleBaseAssaultCube + 0x637E6);
	Hook infAmmoDetourTemp(infAmmoDetourDst, (BYTE*)InfAmmo, 5);
	infAmmoDetour = infAmmoDetourTemp;

	//Inf Ammo NOP
	BYTE* infAmmoNopDst = (moduleBaseAssaultCube + 0x637E9);
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNop = infAmmoNopTemp;

	//One Shot Detour
	BYTE* oneShotDetourDst = (moduleBaseAssaultCube + 0x29D1F);
	Hook oneShotDetourTemp(oneShotDetourDst, (BYTE*)OneShot, 5);
	oneShotDetour = oneShotDetourTemp;
}
