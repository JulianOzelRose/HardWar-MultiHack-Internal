/*
	HardWar-Hack-Internal
	main.cpp
	11-1-2022
*/

#include <iostream>
#include <string>
#include "LocalPlayer.h"
#include "Offsets.h"
#include "Moth.h"
#include "Hangar.h"
#include "Entity.h"
#include "Client.h"

typedef void(__stdcall* _PrintHUD)(int xCord, int yCord, const char* cString, ...);
_PrintHUD PrintHUD;

DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	DWORD dwModuleBase = (DWORD)GetModuleHandle(NULL);

	// Game HUD print function
	PrintHUD = (_PrintHUD)(dwModuleBase + 0x7B950);

	// Game constants
	const DWORD IN_HANGAR = 0x7FFF;
	const DWORD FP_MOTH = 0x18FCC4;
	const DWORD TP_MOTH = 0x596FB04;
	const DWORD MAX_DMG = 0x4000;
	const DWORD MAX_THRUST = 0x4000;

	// Entities
	DWORD dwPlayerEntity;
	DWORD dwPlayerMoth;

	// Toggle variables
	bool bToggle = TRUE;
	bool bSpeedHack = FALSE;
	bool bRunOnce = FALSE;
	bool bInvincibility = TRUE;
	bool bInstakill = FALSE;
	bool bStallNegate = TRUE;

	while (TRUE)
	{
		LocalPlayer lPlayer = LocalPlayer(dwModuleBase);
		Client client(dwModuleBase);

		dwPlayerEntity = lPlayer.GetEntity();
		dwPlayerMoth = lPlayer.GetEntityLocation();

		Moth playerMoth = Moth(dwPlayerMoth);

		// Print injection message on screen
		if (!bRunOnce)
		{
			for (int i = 0; i < 700; i++)
			{
				PrintHUD(300, 115, "HARDWAR-MULTIHACK-INTERNAL");
				PrintHUD(315, 130, "INJECTION SUCCESSFUL");
				Sleep(2);
			}

			bRunOnce = !bRunOnce;
		}

		// Print in-game GUI
		if ((playerMoth.GetMothStatus() != IN_HANGAR) && (client.GetNavMenu() == 0))
		{
			PrintHUD(5, 115, "MULTIHACK MENU");
			PrintHUD(5, 130, "[DEL]");
			PrintHUD(45, 130, "SPEEDHACK:");
			if (bSpeedHack) { PrintHUD(130, 130, "ON"); }
			else { PrintHUD(130, 130, "OFF"); }
			PrintHUD(5, 145, "SHIELD: %d/16384", playerMoth.GetShields());
			PrintHUD(5, 160, "INSTAKILL:");
			PrintHUD(75, 160, "ON");
		}

		// Instakill on keypress
		if (bInstakill)
		{
			if (playerMoth.GetTargetEntity() != NULL)
			{
				if ((playerMoth.GetTargetStructureDmg() != MAX_DMG) && (playerMoth.GetTargetStatus() != 2) && (playerMoth.bIsTargetMoth()))
				{
					playerMoth.SetTargetStructureDmg(MAX_DMG);

					for (int i = 0; i < 700; i++)
					{
						PrintHUD(310, 115, "%s PWNED", playerMoth.GetTargetPilotName());
						Sleep(2);
					}
				}
			}

			bInstakill = !bInstakill;
		}

		// Negate Stall
		if (bStallNegate)
		{
			if (playerMoth.GetStallLvl() > 0)
			{
				playerMoth.NegateStall();
			}
		}

		// Enable Speedhack
		if (bSpeedHack)
		{
			playerMoth.SetThrust(MAX_THRUST * 6);
		}

		// Enable Invicibility
		if (bInvincibility)
		{
			if (playerMoth.GetShields() < MAX_DMG) { playerMoth.SetShields(MAX_DMG); }
		}

		// Toggle Speedhack
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			bSpeedHack = !bSpeedHack;
			if (!bSpeedHack) { playerMoth.SetThrust(0); }
		}

		// Trigger Instakill
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			bInstakill = !bInstakill;
		}

		// Un-inject DLL
		if (GetAsyncKeyState(VK_END) & 1)
		{
			break;
		}

		Sleep(2);
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}