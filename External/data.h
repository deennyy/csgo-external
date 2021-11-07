#pragma once

#include <Windows.h>

struct s_module {
	DWORD base, size;
};

struct s_local_player {
	DWORD pointer = NULL;
	int team, health;
	BYTE lifestate;
};

namespace offsets {
	extern DWORD dwClientState;
	extern DWORD dwClientState_GetLocalPlayer;
	extern DWORD dwEntityList;
	extern DWORD m_fFlags;
	extern DWORD dwForceJump;
	extern DWORD m_iTeamNum;
	extern DWORD model_ambient_min;
	extern DWORD dwGlowObjectManager;
	extern DWORD m_iGlowIndex;
	extern DWORD m_iCrosshairId;
	extern DWORD dwForceAttack;
	extern DWORD force_update_spectator_glow;
	extern DWORD m_bSpotted;
	extern DWORD m_bDormant;
	extern DWORD m_iHealth;
	extern DWORD m_lifeState;
	extern DWORD m_bGunGameImmunity;
	extern DWORD m_clrRender;
};

namespace globals {
	extern s_local_player local_player;
	extern DWORD client_state;
	extern DWORD glow_object_manager;
	extern DWORD enemies[32];
};

namespace modules {
	extern s_module client;
	extern s_module engine;
};

namespace data {
	extern LPCWSTR game_name;
	extern bool should_continue;
};