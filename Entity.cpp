/*
	HardWar-Hack-Internal
	Entity.cpp
	11-1-2022
*/

#include "Entity.h"
#include "Offsets.h"

Entity::Entity()
{
	pEntityAddress = 0;
	m_bStatus = 0;
	m_cName = "NULL";
	m_dwLocationType = 0;
	m_iCash = 0;
	m_pdwLocation = 0;
}

Entity::Entity(DWORD entityAddress)
{
	pEntityAddress = (DWORD*)(entityAddress);
	m_bStatus = 0;
	m_cName = "NULL";
	m_dwLocationType = 0;
	m_iCash = 0;
	m_pdwLocation = 0;
}

Entity::Entity(DWORD modBase, DWORD offset)
{
	pEntityAddress = (DWORD*)(modBase + offset);
	m_bStatus = 0;
	m_cName = "NULL";
	m_dwLocationType = 0;
	m_iCash = 0;
	m_pdwLocation = 0;
}

int Entity::GetCash()
{
	m_iCash = (int*)(*pEntityAddress + offsets::cash);
	return *m_iCash;
}

int Entity::GetEntityStatus()
{
	m_bStatus = (BYTE*)(*pEntityAddress + offsets::pilotStatus);
	return *m_bStatus;
}

DWORD Entity::GetEntityLocation()
{
	m_pdwLocation = (DWORD*)(*pEntityAddress + offsets::location);
	return *m_pdwLocation;
}

DWORD Entity::GetEntity()
{
	return *pEntityAddress;
}

char* Entity::GetEntityName()
{
	m_cName = (char*)(*pEntityAddress + offsets::entityName);
	return m_cName;
}

void Entity::SetEntityAddress(DWORD entityAddress)
{
	pEntityAddress = (DWORD*)(entityAddress);
}