#pragma once
#include "Windows.h"
#include "memory.h"

extern Hook mainHackLoopTramp;
extern Nop infAmmoNop;
extern Hook oneShotDetour;
extern Hook harvestDataTramp;

void SetupHooksAndNops();

