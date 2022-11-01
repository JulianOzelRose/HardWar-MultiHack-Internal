/*
	HardWar-Hack-Internal
	Moth.h
	11-1-2022
*/

#pragma once
#include <Windows.h>

class Moth
{
public:
	Moth();
	Moth(DWORD mothAddress);
	DWORD GetMothEntity();
	DWORD GetTargetEntity();
	DWORD GetMothHangarEntity();
	DWORD GetPilotEntity();
	DWORD GetMothStatus();
	char* GetMothPilotName();
	char* GetTargetPilotName();
	char* GetMothHangarName();
	int GetShields();
	int GetStructureDmg();
	int GetTargetStructureDmg();
	int GetStallLvl();
	void SetTargetStructureDmg(DWORD dmg);
	int GetTargetStatus();
	void SetShields(int newShields);
	void SetThrust(DWORD newThrust);
	void NegateStall();
	bool bIsTargetMoth();
	void SetMothAddress(DWORD mothAddress);
private:
	DWORD* m_pHangar;
	DWORD* m_dwStatus;
	DWORD* m_pOwner;
	int* m_pTarget;
	int* m_iCurrentWeapon;
	int* m_iWeapon1Ammo;
	int* m_iWeapon2Ammo;
	int* m_iWeapon3Ammo;
	int* m_iWeapon4Ammo;
	DWORD* m_pdwPilot;
	DWORD* m_pdwPassenger;
	int* m_iShields;
	int* m_iEngineDmg;
	int* m_iStructureDmg;
	int* m_iCpuDmg;
	int* m_iPowerDmg;
	int* m_iWeaponsDmg;
	int* m_iStallLvl;
	char* m_cDisplayName;
	DWORD* m_dwThrust;
protected:
	DWORD pMothAddress;
};
