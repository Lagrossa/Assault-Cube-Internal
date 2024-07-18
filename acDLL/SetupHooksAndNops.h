#pragma once
#include "Windows.h"
#include "memory.h"

extern Hook mainHackLoopTramp;
extern Nop infAmmoNop;
extern Hook oneShotDetour;

void SetupHooksAndNops();

