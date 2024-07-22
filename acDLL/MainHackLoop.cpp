#include "pch.h"
#include "MainHackLoop.h"
#include "SetupHooksAndNops.h"
#include <iostream>
#include "consoleAndInput.h"
#include "globals.h"
#include "structs.h"
#include "harvest.h"
#include "aimbot.h"

#define numberOfPlayers (gModuleBaseAssaultCube + 0x10F500)

void MoveEnemiesToPlayer(Entity entity) {
	*entity.xHeadCoord = *myself.xHeadCoord + 5;
	*entity.yHeadCoord = *myself.yHeadCoord;
	*entity.zHeadCoord = *myself.zHeadCoord;
}

void MainHackLoop() {
	static bool snakeUp = true;
	int currentNumbersOfPlayers = *(int*)(numberOfPlayers);
	
	if (gNumberOfPlayers != currentNumbersOfPlayers) {
		gNumberOfPlayers = currentNumbersOfPlayers;
		if (!harvestDataTramp.bActive) { harvestDataTramp.ToggleTrampSBF(); }
	}

	if (harvestDataTramp.bActive) { return; }

	UpdateEntInfo();

	Aimbot(ClosestEnemy());

	GetInput();
}

