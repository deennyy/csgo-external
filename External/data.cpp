#include "data.h"

namespace offsets {
	DWORD dwClientState = NULL;
	DWORD dwClientState_GetLocalPlayer = NULL;
	DWORD dwEntityList = NULL;
	DWORD m_fFlags = NULL;
	DWORD dwForceJump = NULL;
	DWORD m_iTeamNum = NULL;
	DWORD model_ambient_min = NULL;
	DWORD dwGlowObjectManager = NULL;
	DWORD m_iGlowIndex = NULL;
	DWORD m_iCrosshairId = NULL;
	DWORD dwForceAttack = NULL;
	DWORD force_update_spectator_glow = NULL;
	DWORD m_bSpotted = NULL;
	DWORD m_bDormant = NULL;
	DWORD m_iHealth = NULL;
	DWORD m_lifeState = NULL;
	DWORD m_bGunGameImmunity = NULL;
	DWORD m_clrRender = NULL;
};

namespace globals {
	s_local_player local_player;
	DWORD client_state = NULL;
	DWORD glow_object_manager = NULL;
	DWORD enemies[32] = { NULL };
};

namespace modules {
	s_module client = { NULL, NULL };
	s_module engine = { NULL, NULL };
};

namespace data {
	LPCWSTR game_name = L"Counter-Strike: Global Offensive";
	bool should_continue = true;
};