/*
	HardWar-Hack-Internal
	Entity.h
	11-1-2022
*/

#pragma once
#include <Windows.h>

class Entity
{
public:
	Entity();
	Entity(DWORD entityAddress);
	Entity(DWORD modBase, DWORD offset);
	DWORD GetEntity();
	DWORD GetEntityLocation();
	int GetCash();
	int GetEntityStatus();
	char* GetEntityName();
	void SetEntityAddress(DWORD entityAddress);
private:
	char* m_cName;
	int* m_iCash;
	BYTE* m_bStatus;
	DWORD* m_dwLocationType;
	DWORD* m_pdwLocation;
protected:
	DWORD *pEntityAddress;
};