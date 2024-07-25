#pragma once
#include "structs.h"

Entity* ClosestEnemy();
void Aimbot(Entity* lockOnTarget);

extern bool bAimBotStatus;

bool BeTargetable(Entity& target, Entity& myself);