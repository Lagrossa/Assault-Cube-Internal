#pragma once

struct Hook{
	BYTE* hookPosition{ nullptr };
	BYTE stolenBytes[20]{ 0 };
	int lengthOfHook;
	bool bActive = false;

	//Tramp Hook Setup
	BYTE* desiredFunction{ nullptr };
	DWORD hookToTrampJump;
	DWORD trampToFuncCall;
	DWORD returnJump;
	BYTE* trampoline{ nullptr };
	BYTE preserveStack[2]{ 0x60, 0x9C }; //pushad, pushfd
	BYTE releaseStack[2]{ 0x9D, 0x61 }; //popfd, popad
	bool bTrampBuilt = false;

	//Detouy Hook Setup
	DWORD hookToDetourJump;
	DWORD returnJumpDetour;

	void ToggleTrampSBF();
	void ToggleTrampSBL();
	void ToggleTrampNSB(); // No Stolen Bytes are run! In the future I could just specify which from which point the bytes are run. TTSBF(3,5)
	void ToggleDetour();

	Hook(BYTE* hookPosition, BYTE* desiredFunction, int lengthOfHook);
	Hook();
};

struct Nop {
	BYTE* nopPosition{ nullptr };
	int length{ 0 };
	BYTE stolenbytes[30]{ 0 };

	bool bActive = false;

	void ToggleNop();

	Nop(BYTE* nopPosition, int length);
	Nop();
};

