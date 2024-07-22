#include "pch.h"
#include "aimbot.h"
#include "globals.h"
#include "structs.h"
#include <cmath>

int ClosestEnemy() {
	int closestEnemy = 0;
	float closestDistance = 9999.0f;

	for (int i = 1; i < gNumberOfPlayers; i++)
	{
		if (entity[i].distanceFromMe < closestDistance) {
			
			if (*entity[i].bDead || *entity[i].team == *myself.team ) { continue; }
			
			closestEnemy = i;
			closestDistance = entity[i].distanceFromMe;
		}
	}

	return closestEnemy;
}

void Aimbot(int lockOnTarget) {
	if (!lockOnTarget) { return; }

	float tempYaw = atan2(entity[lockOnTarget].relativeY, entity[lockOnTarget].relativeX);
	tempYaw = (tempYaw * 180 / gPI) + 90;
	float tempPitch = atan2(entity[lockOnTarget].relativeZ, entity[lockOnTarget].distanceFromMe);
	tempPitch *= (180 / gPI);

	*myself.yaw = tempYaw;
	*myself.pitch = tempPitch;
}