/*
	HardWar-Hack-Internal
	Moth.cpp
	11-1-2022
*/

#include <Windows.h>
#include "Moth.h"
#include "Offsets.h"

Moth::Moth()
{
	pMothAddress = 0;
	m_pHangar = 0;
	m_dwStatus = 0;
	m_pOwner = 0;
	m_pTarget = 0;
	m_iCurrentWeapon = 0;
	m_iWeapon1Ammo = 0;
	m_iWeapon2Ammo = 0;
	m_iWeapon3Ammo = 0;
	m_iWeapon4Ammo = 0;
	m_pdwPilot = 0;
	m_pdwPassenger = 0;
	m_iShields = 0;
	m_iEngineDmg = 0;
	m_iStructureDmg = 0;
	m_iCpuDmg = 0;
	m_iPowerDmg = 0;
	m_iWeaponsDmg = 0;
	m_iStallLvl = 0;
	m_cDisplayName = "NULL";
	m_dwThrust = 0;
}

Moth::Moth(DWORD mothAddress)
{
	pMothAddress = (DWORD)(mothAddress);
	m_pHangar = 0;
	m_dwStatus = 0;
	m_pOwner = 0;
	m_pTarget = 0;
	m_iCurrentWeapon = 0;
	m_iWeapon1Ammo = 0;
	m_iWeapon2Ammo = 0;
	m_iWeapon3Ammo = 0;
	m_iWeapon4Ammo = 0;
	m_pdwPilot = 0;
	m_pdwPassenger = 0;
	m_iShields = 0;
	m_iEngineDmg = 0;
	m_iStructureDmg = 0;
	m_iCpuDmg = 0;
	m_iPowerDmg = 0;
	m_iWeaponsDmg = 0;
	m_iStallLvl = 0;
	m_cDisplayName = "NULL";
	m_dwThrust = 0;
}

int Moth::GetShields()
{
	m_iShields = (int*)(pMothAddress + offsets::shields);
	return *m_iShields;
}

DWORD Moth::GetTargetEntity()
{
	return *(DWORD*)(pMothAddress + offsets::target);
}

DWORD Moth::GetMothHangarEntity()
{
	return *(DWORD*)(pMothAddress + offsets::hangar);
}

char* Moth::GetMothHangarName()
{
	m_pHangar = (DWORD*)(pMothAddress + offsets::hangar);
	char* cHangarName = (char*)(*m_pHangar + 0x10);

	return cHangarName;
}

int Moth::GetStructureDmg()
{
	m_iStructureDmg = (int*)(pMothAddress + offsets::structureDmg);
	return *m_iStructureDmg;
}

int Moth::GetTargetStructureDmg()
{
	m_pTarget = (int*)(pMothAddress + offsets::target);
	int* iTargetStructureDmg = (int*)(*m_pTarget + offsets::structureDmg);
	return *iTargetStructureDmg;
}

DWORD Moth::GetMothStatus()
{
	m_dwStatus = (DWORD*)(pMothAddress + offsets::mothStatus);
	return *m_dwStatus;
}

void Moth::SetThrust(DWORD newThrust)
{
	m_dwThrust = (DWORD*)(pMothAddress + offsets::thrust);
	*m_dwThrust = newThrust;
}

DWORD Moth::GetPilotEntity()
{
	m_pdwPilot = (DWORD*)(pMothAddress + 0x2DC);
	return *m_pdwPilot;
}

DWORD Moth::GetMothEntity()
{
	return pMothAddress;
}

int Moth::GetStallLvl()
{
	m_iStallLvl = (int*)(pMothAddress + 0x390);
	return *m_iStallLvl;
}

void Moth::NegateStall()
{
	m_iStallLvl = (int*)(pMothAddress + 0x390);
	*m_iStallLvl = 0;
}

char* Moth::GetTargetPilotName()
{
	m_pTarget = (int*)(pMothAddress + offsets::target);
	int* pTargetEntity = (int*)(*m_pTarget + 0x1D8);
	char* cTargetName = (char*)(*pTargetEntity + 0x4);

	return cTargetName;
}

char* Moth::GetMothPilotName()
{
	int* pEntity = (int*)(pMothAddress + offsets::pilot);
	char* cEntityName = (char*)(*pEntity + 0x4);

	return cEntityName;
}

void Moth::SetTargetStructureDmg(DWORD dmg)
{
	m_pTarget = (int*)(pMothAddress + offsets::target);
	DWORD* dwTargetStructureDmg = (DWORD*)(*m_pTarget + offsets::structureDmg);
	*dwTargetStructureDmg = dmg;
}

void Moth::SetShields(int newShields)
{
	m_iShields = (int*)(pMothAddress + offsets::shields);
	*m_iShields = newShields;
}

int Moth::GetTargetStatus()
{
	m_pTarget = (int*)(pMothAddress + offsets::target);
	
	int* iTargetStatus = (int*)(*m_pTarget + offsets::mothStatus);
	return *iTargetStatus;
}

bool Moth::bIsTargetMoth()
{
	m_pTarget = (int*)(pMothAddress + offsets::target);
	DWORD* dwTargetSignature = (DWORD*)(*m_pTarget + 0x330);

	if ((DWORD)(*dwTargetSignature) == 0x7FFF) { return TRUE; }
	else { return FALSE;  }
}

void Moth::SetMothAddress(DWORD mothAddress)
{
	pMothAddress = (DWORD)(mothAddress);
}