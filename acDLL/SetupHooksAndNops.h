#pragma once
#include "Windows.h"
#include "memory.h"

extern Hook mainHackLoopTramp;
extern Hook infAmmoDetour;
extern Nop infAmmoNop;
extern Hook oneShotDetour;

void SetupHooksAndNops();

