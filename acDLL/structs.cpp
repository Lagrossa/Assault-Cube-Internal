#include "pch.h"
#include "structs.h"
#include "globals.h"
#include <cmath>
#include "aimbot.h"

Entity entity[32];
Entity myself;
Offsets offsets;

void UpdateEntInfo() {
	for (int i = 1; i < gNumberOfPlayers; i++) {
		//if(*entity[i].team != *myself.team) *entity[i].pitch = 88.000f;
		entity[i].relativeX = (*entity[i].xHeadCoord - *myself.xHeadCoord);
		entity[i].relativeY = (*entity[i].yHeadCoord - *myself.yHeadCoord);
		entity[i].relativeZ = (*entity[i].zHeadCoord - *myself.zHeadCoord);
		entity[i].distanceFromMe = sqrt((entity[i].relativeX * entity[i].relativeX) + (entity[i].relativeY * entity[i].relativeY));
		entity[i].bTargetable = BeTargetable(entity[i], myself);
	}
}