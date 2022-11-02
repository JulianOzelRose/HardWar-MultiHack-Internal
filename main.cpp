/*
	HardWar-Hack-Internal
	main.cpp
	11-1-2022
*/

#include <iostream>
#include <string>
#include "Memory.h"
#include "LocalPlayer.h"
#include "Offsets.h"
#include "Moth.h"
#include "Hangar.h"
#include "Entity.h"
#include "Client.h"

typedef void(__stdcall* _PrintHUD)(int xCord, int yCord, const char* string, ...);
_PrintHUD PrintHUD;

DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "Injection successful\n";

	DWORD dwModuleBase = (DWORD)GetModuleHandle(NULL);

	// Game HUD print function
	PrintHUD = (_PrintHUD)(dwModuleBase + 0x7B950);

	int x = 285;
	int y = 115;

	// Game constants
	const DWORD IN_HANGAR = 0x7FFF;
	const DWORD FP_MOTH = 0x18FCC4;
	const DWORD TP_MOTH = 0x596FB04;
	const DWORD MAX_DMG = 0x4000;

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

		if (!bRunOnce)
		// Print injection message on screen
		{
			for (int i = 0; i < 700; i++)
			{
				PrintHUD(x + 25, y, "INJECTION SUCCESSFUL");
				Sleep(2);
			}

			bRunOnce = !bRunOnce;
		}

		if ((playerMoth.GetMothStatus() != IN_HANGAR) && (client.GetNavMenu() == 0))
		// Print in-game GUI
		{
			PrintHUD(5, y, "MULTIHACK MENU");
			PrintHUD(5, y + 15, "[DEL]");
			PrintHUD(45, y + 15, "SPEEDHACK:");
			if (bSpeedHack) { PrintHUD(130, y + 15, "ON"); }
			else { PrintHUD(130, y + 15, "OFF"); }
			PrintHUD(5, y + 30, "SHIELD: %d/16384", playerMoth.GetShields());
			PrintHUD(5, y + 45, "INSTAKILL:");
			PrintHUD(75, y + 45, "ON");
		}

		if (bInstakill)
		// Instakill on keypress
		{
			if (playerMoth.GetTargetEntity() != NULL)
			{
				if ((playerMoth.GetTargetStructureDmg() != 0x4000) && (playerMoth.GetTargetStatus() != 2) && (playerMoth.bIsTargetMoth()))
				{
					playerMoth.SetTargetStructureDmg(0x4000);

					for (int i = 0; i < 700; i++)
					{
						PrintHUD(x + 25, y, "%s PWNED", playerMoth.GetTargetPilotName());
						Sleep(2);
					}
				}
			}

			bInstakill = !bInstakill;
		}

		if (bStallNegate)
		// Negate Stall
		{
			if (playerMoth.GetStallLvl() > 0)
			{
				playerMoth.NegateStall();
			}
		}

		if (bSpeedHack)
		// Enable Speedhack
		{
			playerMoth.SetThrust(0x4000 * 6);
		}

		if (bInvincibility)
		// Enable Invicibility
		{
			if (playerMoth.GetShields() < 0x4000) { playerMoth.SetShields(MAX_DMG); }
		}

		if (GetAsyncKeyState(VK_DELETE) & 1)
		// Toggle Speedhack
		{
			bSpeedHack = !bSpeedHack;
			if (!bSpeedHack) { playerMoth.SetThrust(0); }
		}

		if (GetAsyncKeyState(VK_INSERT) & 1)
		// Trigger Instakill
		{
			bInstakill = !bInstakill;
		}

		if (GetAsyncKeyState(VK_END) & 1)
		// Un-inject DLL
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