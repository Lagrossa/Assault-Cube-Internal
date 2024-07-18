#pragma once

struct Entity {
	BYTE* playerBase = nullptr;
	BYTE* bDead = nullptr;
	float* xCoord = nullptr;
	float* yCoord = nullptr;
	float* zCoord = nullptr;
	int* team = nullptr;
	int* playerNumber = nullptr;
	int* health = nullptr;
	char* name = nullptr;

	bool bChecked = false;
	float relativeX = NULL;
	float relativeY = NULL;
	float relativeZ = NULL;
	float distanceFromMe = 9999.0f;

	float* yaw = nullptr;
	float* pitch = nullptr;
	int* arAmmo = nullptr;
};

struct Offsets {
	DWORD xCoord = 0x34;
	DWORD yCoord = 0x38;
	DWORD zCoord = 0x3C;
	DWORD team = 0x32C;
	DWORD playerNumber = 0x1E4;
	DWORD bDead = 0x82;
	DWORD name = 0x225;
	DWORD health = 0xF8;

	DWORD yaw = 0x40;
	DWORD pitch = 0x44;
	DWORD arAmmo = 0x150;
};

extern Entity entity[32];
extern Entity myself;
extern Offsets offsets;

