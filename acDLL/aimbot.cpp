#include "pch.h"
#include "aimbot.h"
#include "globals.h"
#include "structs.h"
#include <cmath>
#include <iostream>

#define FindTargetOffset 0x8ABD0


bool bAimBotStatus = FALSE;

Entity* ClosestEnemy() {
	Entity* closestEnemy = nullptr;
	float closestDistance = 9999.0f;	
	for (int i = 1; i < gNumberOfPlayers; i++)
	{
		if (entity[i].distanceFromMe < closestDistance) {
			
			if (*entity[i].bDead || *entity[i].team == *myself.team || entity[i].bTargetable == 0) { continue; }

			closestEnemy = (Entity*)(&entity[i]);
			closestDistance = entity[i].distanceFromMe;
		}
	}

	return closestEnemy;	 
}

void Aimbot(Entity* lockOnTarget) {
	if (!lockOnTarget) { return; }

	float tempYaw = atan2(lockOnTarget->relativeY, lockOnTarget->relativeX);
	tempYaw = (tempYaw * 180 / gPI) + 90;
	float tempPitch = atan2(lockOnTarget->relativeZ, lockOnTarget->distanceFromMe);
	tempPitch *= (180 / gPI);

	*myself.yaw = tempYaw;
	*myself.pitch = tempPitch;
}

bool BeTargetable(Entity& target, Entity& myself) {
	
	bool bTargetable = 0; //Need a return that is referencable in manual function call

	void* FindTarget = (void*)(gModuleBaseAssaultCube + FindTargetOffset); //Casted as void* because it is a function. 
	
	//Parameters
	float fromX = *target.xHeadCoord;
	float fromY = *target.yHeadCoord;
	float fromZ = *target.zHeadCoord;
	float toX = *myself.xHeadCoord;
	float toY = *myself.yHeadCoord;
	float toZ = *myself.zHeadCoord;


	__asm {
		push toZ
		push toY
		push toX
		push fromZ
		push fromY
		push fromX

		mov eax, 0
		mov cl, 0

		call FindTarget

		mov [bTargetable], al
		add esp, 0x18
	}

	return bTargetable;
}