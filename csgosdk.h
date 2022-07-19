#pragma once
#include "csgo.hpp"
#include <Windows.h>

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class Ent
{
public:

    // be sure to put all the offsets you pad this way in a union
    union
    {
        //              Type     Name    Offset
        DEFINE_MEMBER_N(int, clientId, 0x64);
        DEFINE_MEMBER_N(int, m_iHealth, hazedumper::netvars::m_iHealth);
		DEFINE_MEMBER_N(int, m_bDormant, hazedumper::signatures::m_bDormant);
    };

};

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual void* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(int hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					GetMaxEntities() = 0;
};

typedef void* (__cdecl* tCreateInterface)(const char* name, int* returnCode);

void* GetInterface(const char* dllmain, const char* interfacename)
{
	tCreateInterface CreateInterface = (tCreateInterface)(GetProcAddress(GetModuleHandleA(dllmain), "CreateInterface"));
	int returnCode = 0;
	void* interfaceAddr = CreateInterface(interfacename, &returnCode);
	return interfaceAddr;
}
