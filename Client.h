/*
	HardWar-Hack-Internal
	Client.h
	11-1-2022
*/

#pragma once
#include <Windows.h>
#include "Offsets.h"

class Client
{
public:
	Client(DWORD modBase);
	DWORD GetTxtMode();
	DWORD GetNavMenu();
private:
	DWORD* m_dwNavMenu;
	DWORD* m_dwTxtMode = (DWORD*)(0x534F6C);
	DWORD moduleBase;
};