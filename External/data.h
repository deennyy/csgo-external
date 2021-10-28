#pragma once

#include <Windows.h>

struct s_module {
	DWORD base, size;
};

class c_local_player {
public:
	DWORD pointer = NULL;
	int team;
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
};

namespace globals {
	extern c_local_player local_player;
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
	extern bool shoud_continue;
};