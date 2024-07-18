#include "pch.h"
#include "harvest.h"
#include "structs.h"
#include "SetupHooksAndNops.h"
#include "globals.h"

void HarvestData() {
	int* currentPlayerNumber;
	BYTE* playerBase;

	__asm {
		push ebx

		lea ebx, [esi]
		mov playerBase, ebx 

		lea ebx, [esi + 0x1E4]
		mov currentPlayerNumber, ebx

		pop ebx
	}

	MoveDataIntoEnt(playerBase, currentPlayerNumber);

	for (int i = 0; i < gNumberOfPlayers; i++) {
		if (!entity[i].bChecked) {
			return;
		}
	}

	for (int i = 0; i < gNumberOfPlayers; i++) {
		entity[i].bChecked = false;
	}
	harvestDataTramp.ToggleTrampSBF();
}

void MoveDataIntoEnt(BYTE* playerBase, int* playerNumber) {
	entity[*playerNumber].playerBase = playerBase;
	entity[*playerNumber].bDead = playerBase + offsets.bDead;
	entity[*playerNumber].playerNumber = (int*)(playerBase + offsets.playerNumber);
	entity[*playerNumber].team = (int*)(playerBase + offsets.team);
	entity[*playerNumber].health = (int*)(playerBase + offsets.health);
	entity[*playerNumber].xCoord = (float*)(playerBase + offsets.xCoord);
	entity[*playerNumber].yCoord = (float*)(playerBase + offsets.yCoord);
	entity[*playerNumber].zCoord = (float*)(playerBase + offsets.zCoord);
	entity[*playerNumber].name = (char*)(playerBase + offsets.name);
	entity[*playerNumber].bChecked = true;

	if (*playerNumber == 0) {
		myself = entity[0];
		myself.pitch = (float*)(playerBase + offsets.pitch);
		myself.yaw = (float*)(playerBase + offsets.yaw);
		myself.arAmmo = (int*)(playerBase + offsets.arAmmo);
	}
}