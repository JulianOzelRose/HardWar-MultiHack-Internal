/*
	HardWar-Hack-Internal
	Client.cpp
	11-1-2022
*/

#include <Windows.h>
#include "Client.h"

Client::Client(DWORD modBase)
{
	moduleBase = modBase;
}

DWORD Client::GetTxtMode()
{
	return *m_dwTxtMode;
}

DWORD Client::GetNavMenu()
{
	m_dwNavMenu = (DWORD*)(moduleBase + offsets::navMenu);
	return *m_dwNavMenu;
}