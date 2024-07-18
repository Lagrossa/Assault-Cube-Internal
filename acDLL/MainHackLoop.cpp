#include "pch.h"
#include "MainHackLoop.h"
#include "SetupHooksAndNops.h"
#include <iostream>
#include "consoleAndInput.h"
#include "globals.h"
#include "structs.h"

#define numberOfPlayers (gModuleBaseAssaultCube + 0x10F500)

void MainHackLoop() {
	int currentNumbersOfPlayers = *(int*)(numberOfPlayers);
	
	if (gNumberOfPlayers != currentNumbersOfPlayers) {
		gNumberOfPlayers = currentNumbersOfPlayers;
		if (!harvestDataTramp.bActive) { harvestDataTramp.ToggleTrampSBF(); }
	}

	if (harvestDataTramp.bActive) { return; }

	*myself.arAmmo = 999;

	for (int i = 0; i < gNumberOfPlayers; i++) {
		if (*entity[i].team != *myself.team) {
			*entity[i].health = 1;
		}
	
	}

	GetInput();
}
