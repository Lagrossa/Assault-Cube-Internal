#include "pch.h"
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"
#include "memory.h"
#include "oneShot.h"
#include "harvest.h"

Hook mainHackLoopTramp;
Nop infAmmoNop;
Hook oneShotDetour;
Hook harvestDataTramp;

void SetupHooksAndNops() {
	BYTE* moduleBaseAssaultCube = (BYTE*)GetModuleHandle(L"ac_client.exe"); //Get module base for AssaultCube. 
	BYTE* moduleBaseOpenGL = (BYTE*)GetModuleHandle(L"opengl32.dll"); //Module for OPEN GL

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

	BYTE* harvestDataTrampDst = (moduleBaseAssaultCube + 0x5BD76);
	Hook harvestDataTrampTemp(harvestDataTrampDst, (BYTE*)HarvestData, 6);
	harvestDataTramp = harvestDataTrampTemp;

}
