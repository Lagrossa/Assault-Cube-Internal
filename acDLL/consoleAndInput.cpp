#include "pch.h"
#include "consoleAndInput.h"
#include <iostream>
#include "SetupHooksAndNops.h"

bool bBreakHackThreadWhileLoop = false;

const char* otter = "\n\
             ,d      ,d\n\
             88      88\n\
 ,adPPYba, MM88MMM MM88MMM ,adPPYba, 8b,dPPYba,\n\
a8"     "8a  88      88   a8P_____88 88P'   Y8\n\
8b       d8  88      88   8PP\"\"\"\"\"\"\" 88\n\
\"8a,   ,a8\"  88,     88,  \"8b,   ,aa 88\n\
 `\"YbbdP\"\'   \"Y888   \"Y888 `\"Ybbd8\"\' 88";

void GetInput() {
	if (GetAsyncKeyState(VK_END) & 1) {
        BreakHackLoop();
	}

	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		infAmmoNop.ToggleNop();
        PrintConsole();
	}

	if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
		oneShotDetour.ToggleDetour();
        PrintConsole();
	}
}

void PrintConsole() {
    system("CLS");
    std::cout << otter << std::endl;
    std::cout << "\n==================================================" << std::endl;
    std::cout << "Press NUMPAD0 for infAmmoNOP." << std::endl;
    std::cout << "Press NUMPAD1 to One Shot & Godmode" << std::endl;
    std::cout << "Press END to uninject." << std::endl;
    std::cout << "==================================================" << std::endl;
    std::cout << "Infinite Ammo: " << (infAmmoNop.bActive) << std::endl;
    std::cout << "One Shot & Godmode: " << (oneShotDetour.bActive) << std::endl;
}

void BreakHackLoop() {
    if (infAmmoNop.bActive) { infAmmoNop.ToggleNop(); }
    if (oneShotDetour.bActive) { oneShotDetour.ToggleDetour(); }

	mainHackLoopTramp.ToggleTrampSBF();
	bBreakHackThreadWhileLoop = true;
}

void ToggleConsole() {

}