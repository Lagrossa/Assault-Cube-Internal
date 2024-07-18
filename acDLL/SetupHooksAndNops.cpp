#include "pch.h"
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"
#include "memory.h"
#include "oneShot.h"

Hook mainHackLoopTramp;
Nop infAmmoNop;
Hook oneShotDetour;

void SetupHooksAndNops() {
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle("ac_client.exe"); //Get module base for AssaultCube. 
	BYTE* moduleBaseOpenGL = (BYTE*)GetModuleHandle("opengl32.dll"); //Module for OPEN GL

	//Main Hack Loop
	BYTE* mainHackLoopHookDst = (moduleBaseOpenGL + 0x4841E);
	Hook mainHackLoopTrampTemp(mainHackLoopHookDst, (BYTE*)MainHackLoop, 5);
	mainHackLoopTramp = mainHackLoopTrampTemp;

	//Inf Ammo NOP
	BYTE* infAmmoNopDst = (moduleBaseAssaultCube + 0x637E9);
	Nop infAmmoNopTemp(infAmmoNopDst, 2);
	infAmmoNop = infAmmoNopTemp;

	//One Shot Detour
	BYTE* oneShotDetourDst = (moduleBaseAssaultCube + 0x29D1F);
	Hook oneShotDetourTemp(oneShotDetourDst, (BYTE*)OneShot, 5);
	oneShotDetour = oneShotDetourTemp;
}
