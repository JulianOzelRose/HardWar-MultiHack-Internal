/*
	HardWar-Hack-Internal
	LocalPlayer.h
	11-1-2022
*/

#pragma once
#include <Windows.h>
#include "Entity.h"

class LocalPlayer : public Entity
{
public:
	LocalPlayer();
	LocalPlayer(DWORD modBase);
};