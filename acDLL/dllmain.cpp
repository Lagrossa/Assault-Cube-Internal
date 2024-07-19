// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include "SetupHooksAndNops.h"
#include "MainHackLoop.h"
#include "consoleAndInput.h"

DWORD WINAPI HackThread(HMODULE hModule) {

    //Create Console
    ToggleConsole();

    //Setup our hooks and NOPs

    SetupHooksAndNops();

    //Toggle the hooks we want
    mainHackLoopTramp.ToggleTrampSBF();
    //harvestDataTramp.ToggleTrampSBF();

    PrintConsole();

    while (!bBreakHackThreadWhileLoop) {

    }

    //release the console
    ToggleConsole();

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

