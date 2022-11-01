/*
	HardWar-Hack-Internal
	Hangar.h
	11-1-2022
*/

#pragma once
#include <Windows.h>

class Hangar
{
public:
	Hangar();
	Hangar(DWORD hangarAddress);
	Hangar(DWORD modBase, DWORD offset);
	DWORD GetHangarEntity();
	int GetCashHeld();
	char* GetHangarName();
	DWORD GetEnemyList();
	DWORD GetBay0();
	DWORD GetBay1();
	DWORD GetBay2();
	DWORD GetBay3();
	DWORD GetBay4();
	DWORD GetBay5();
	void SetHangarAddress(DWORD hangarAddress);
private:
	char* m_cTerminalName;
	char* m_cDisplayName;
	int* m_iClearanceLvl;
	int* m_iCashHeld;
	DWORD* m_pdwEnemyList;
	DWORD* m_pdwOwner;
	DWORD* m_pdwBay0;
	DWORD* m_pdwBay1;
	DWORD* m_pdwBay2;
	DWORD* m_pdwBay3;
	DWORD* m_pdwBay4;
	DWORD* m_pdwBay5;
protected:
	DWORD pHangarAddress;
};