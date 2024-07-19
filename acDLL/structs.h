#pragma once
#include <cstdint>

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

// Created with ReClass.NET 1.2 by KN4CK3R

class N00000052
{
public:
	char pad_0000[4]; //0x0000
	class EntList* pEntList; //0x0004
	char pad_0008[64]; //0x0008
}; //Size: 0x0048
static_assert(sizeof(N00000052) == 0x48);

class EntList
{
public:
	char pad_0000[68]; //0x0000
}; //Size: 0x0044
static_assert(sizeof(EntList) == 0x44);

class EntList
{
public:
	char pad_0000[4]; //0x0000
	class Ent* pEnt; //0x0004
	char pad_0008[60]; //0x0008
}; //Size: 0x0044
static_assert(sizeof(EntList) == 0x44);

class Ent
{
public:
	char pad_0000[4]; //0x0000
	float X_Coord; //0x0004
	float Y_Coord; //0x0008
	float Z_Coord; //0x000C
	char pad_0010[36]; //0x0010
	float Origin_X; //0x0034
	float Origin_Y; //0x0038
	float Origin_Z; //0x003C
	float yaw; //0x0040
	float pitch; //0x0044
	char pad_0048[58]; //0x0048
	bool bDead; //0x0082
	char pad_0083[117]; //0x0083
	int32_t health; //0x00F8
	char pad_00FC[84]; //0x00FC
	int32_t arAmmo; //0x0150
	char pad_0154[144]; //0x0154
	int32_t teamNumber; //0x01E4
	char pad_01E8[61]; //0x01E8
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	int32_t team; //0x032C
}; //Size: 0x0330

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

