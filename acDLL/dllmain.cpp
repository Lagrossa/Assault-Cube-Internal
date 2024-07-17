// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"

struct Offsets {
    char* healthOffset = (char*)0xF8;
    char* ammoOffset = (char*)0x150;
};

DWORD WINAPI HackThread(HMODULE hModule) {

    //Create Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    //Setup our hooks and NOPs
    SetupHooksAndNops();

    //Toggle the hooks we want
    mainHackLoopTramp.ToggleTrampSBL();

    std::cout << "Press NUMPAD0 for infAmmoDetour." << std::endl;
    std::cout << "Press NUMPAD1 for infAmmoNOP." << std::endl;
    std::cout << "Press NUMPAD2 to One Shot Red Team" << std::endl;
    std::cout << "Press END to uninject." << std::endl;

    while (!bBreakHackThreadWhileLoop) {

    }

    if (infAmmoDetour.bActive) { infAmmoDetour.ToggleDetour(); }
    if (infAmmoNop.bActive) { infAmmoNop.ToggleNop(); }
    if (oneShotDetour.bActive) { oneShotDetour.ToggleDetour(); }

    //release the console
    fclose(f);
    FreeConsole();

    //Unload library, close thread safely
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(NULL,NULL, (LPTHREAD_START_ROUTINE)HackThread, hModule, NULL, NULL));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

