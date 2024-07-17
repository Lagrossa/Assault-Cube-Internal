#include "pch.h"
#include "memory.h"
#include <iostream>
#include "SetupHooksAndNops.h"

Hook::Hook(BYTE* hookPosition, BYTE* desiredFunction, int lengthOfHook) {
	if (lengthOfHook < 5) {
		std::cout << "Hook could not be created. Length less than 5 bytes." << std::endl;
		delete this;
	}
	this->hookPosition = hookPosition;
	this->desiredFunction = desiredFunction;
	this->lengthOfHook = lengthOfHook;

	memcpy(stolenBytes, hookPosition, lengthOfHook);

	trampoline = (BYTE*)VirtualAlloc(nullptr, 30, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	hookToTrampJump = (DWORD)(trampoline - hookPosition) - 5;
	returnJump = (DWORD)(hookPosition + lengthOfHook) - (DWORD)(trampoline + lengthOfHook +
		sizeof(preserveStack) + 5 + sizeof(releaseStack)) - 5;

	hookToDetourJump = (DWORD)(desiredFunction - hookPosition) - 5;
	std::cout << hookToDetourJump << std::endl;

	returnJumpDetour = (DWORD)(hookPosition + lengthOfHook);

}

Hook::Hook() {

}

void Hook::ToggleTrampSBF() {
	bActive = !bActive;

	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);

		if (bTrampBuilt) { goto  TrampAlreadyBuilt; }

		trampToFuncCall = (DWORD)desiredFunction - (DWORD)(trampoline + lengthOfHook + sizeof(preserveStack)) - 5;

		memcpy(trampoline, (void*)hookPosition, lengthOfHook);
		memcpy(trampoline + lengthOfHook, preserveStack, sizeof(preserveStack));
		memset(trampoline + lengthOfHook + sizeof(preserveStack), 0xE8, 1);
		*(DWORD*)(trampoline + lengthOfHook + sizeof(preserveStack) + 1) = trampToFuncCall;

		//Release stack
		memcpy(trampoline + lengthOfHook + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack));
		memset(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack), 0xE9, 1);
		*(DWORD*)(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 1) = returnJump;

		bTrampBuilt = true;

	TrampAlreadyBuilt:
		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToTrampJump;

		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}

	if (!bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}
}

void Hook::ToggleTrampSBL() {
	bActive = !bActive;

	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);

		if (bTrampBuilt) { goto  TrampAlreadyBuilt; }

		trampToFuncCall = (DWORD)desiredFunction - (DWORD)(trampoline + sizeof(preserveStack)) - 5;

		memcpy(trampoline, preserveStack, sizeof(preserveStack)); // Preserves Stack
		memset(trampoline + sizeof(preserveStack), 0xE8, 1); // Call
		*(DWORD*)(trampoline + sizeof(preserveStack) + 1) = trampToFuncCall; // Function Address

		//Release stack
		memcpy(trampoline + sizeof(preserveStack) + 5, releaseStack, sizeof(releaseStack)); //Releases Stack
		memcpy(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack), (void*)hookPosition, lengthOfHook); // Runs Stolen Bytes
		memset(trampoline + sizeof(preserveStack) + 5 + sizeof(releaseStack) + lengthOfHook, 0xE9, 1); // Jump Back
		*(DWORD*)(trampoline + lengthOfHook + sizeof(preserveStack) + 5 + sizeof(releaseStack) + 1) = returnJump;

		bTrampBuilt = true;

	TrampAlreadyBuilt:
		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToTrampJump;

		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}

	if (!bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}
}

void Hook::ToggleDetour() {
	bActive = !bActive;
	
	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memset(hookPosition, 0x90, lengthOfHook);
		*(BYTE*)hookPosition = 0xE9;
		*(DWORD*)(hookPosition + 1) = hookToDetourJump;
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}
	if (!bActive) {
		DWORD oldProtection;
		VirtualProtect(hookPosition, lengthOfHook, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(hookPosition, stolenBytes, lengthOfHook);
		VirtualProtect(hookPosition, lengthOfHook, oldProtection, nullptr);
	}
}


Nop::Nop(BYTE* nopPosition, int length) {
	this->nopPosition = nopPosition;
	this->length = length;
	memcpy(stolenbytes, nopPosition, length);
}

Nop::Nop() {

}

void Nop::ToggleNop() {

	bActive = !bActive;

	if (bActive) {
		DWORD oldProtection;
		VirtualProtect(nopPosition, length, PAGE_EXECUTE_READWRITE, &oldProtection);
		memset(nopPosition, 0x90, length);
		VirtualProtect(nopPosition, length, oldProtection, &oldProtection);
	}

	if (!bActive) {
		DWORD oldProtection;
		VirtualProtect(nopPosition, length, PAGE_EXECUTE_READWRITE, &oldProtection);
		memcpy(nopPosition, stolenbytes, length);
		VirtualProtect(nopPosition, length, oldProtection, &oldProtection);
	}
}
