/*
	HardWar-Hack-Internal
	LocalPlayer.cpp
	11-1-2022
*/

#include "LocalPlayer.h"
#include "Offsets.h"

LocalPlayer::LocalPlayer() {}

LocalPlayer::LocalPlayer(DWORD modBase)
{
	pEntityAddress = (DWORD*)(modBase + offsets::localPlayer);
}