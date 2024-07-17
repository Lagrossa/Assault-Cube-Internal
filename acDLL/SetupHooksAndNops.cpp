#include "pch.h"
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"
#include "memory.h"
#include "infAmmo.h"

Hook mainHackLoopTramp;
Hook infAmmoDetour;
Nop infAmmoNop;

void SetupHooksAndNops() {
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle(L"ac_client.exe"); //Get module base for AssaultCube. 
	BYTE* moduleBaseOpenGL = (BYTE*)GetModuleHandle(L"opengl32.dll");

	BYTE* mainHackLoopHookDst = (moduleBaseOpenGL + 0x4841E);
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//Info Ammo Detour
	BYTE* infAmmoDetourDst = (moduleBaseAssaultCube + 0x637E6);
	Hook infAmmoDetourTemp(infAmmoDetourDst, (BYTE*)InfAmmo, 5);
	infAmmoDetour = infAmmoDetourTemp;

	//Inf Ammo NOP
	BYTE* infAmmoNopDst = (moduleBaseAssaultCube + 0x637E9);
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNop = infAmmoNopTemp;
}
