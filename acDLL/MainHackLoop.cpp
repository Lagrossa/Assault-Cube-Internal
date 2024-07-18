#include "pch.h"
#include "MainHackLoop.h"
#include "SetupHooksAndNops.h"
#include <iostream>
#include "consoleAndInput.h"
#include "globals.h"
#include "structs.h"

#define numberOfPlayers (gModuleBaseAssaultCube + 0x10F500)

void MoveEnemiesToPlayer(Entity entity) {
	*entity.xCoord = *myself.xCoord + 5;
	*entity.yCoord = *myself.yCoord;
	*entity.zCoord = *myself.zCoord;
}

void MainHackLoop() {
	static bool snakeUp = true;
	int currentNumbersOfPlayers = *(int*)(numberOfPlayers);
	
	if (gNumberOfPlayers != currentNumbersOfPlayers) {
		gNumberOfPlayers = currentNumbersOfPlayers;
		if (!harvestDataTramp.bActive) { harvestDataTramp.ToggleTrampSBF(); }
	}

	if (harvestDataTramp.bActive) { return; }

	if (*myself.arAmmo >= 200) { snakeUp = FALSE; }
	if (*myself.arAmmo <= 1) { snakeUp = TRUE; }

	if (snakeUp) {
		*myself.arAmmo += 1;
	}
	else {
		*myself.arAmmo -= 1;
	}

	*myself.health = 9999;

	for (int i = 0; i < gNumberOfPlayers; i++) {
		if (*entity[i].team != *myself.team) {
			*entity[i].health = 1;
			MoveEnemiesToPlayer(entity[i]);
		}
	
	}

	GetInput();
}

