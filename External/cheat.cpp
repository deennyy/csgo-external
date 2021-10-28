#include "cheat.h"

void cheat::startup() {
	modules::engine = memory->get_module(L"engine.dll");
	modules::client = memory->get_module(L"client.dll");

	offsets::dwClientState = memory->pattern_scan(modules::engine, L"A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", 0x1, 0x0, true, true);
	offsets::dwClientState_GetLocalPlayer = memory->pattern_scan(modules::engine, L"8B 80 ? ? ? ? 40 C3", 0x2, 0x0, true, false);
	offsets::dwEntityList = memory->pattern_scan(modules::client, L"BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", 0x1, 0x0, true, true);
	offsets::dwForceJump = memory->pattern_scan(modules::client, L"8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", 0x2, 0x0, true, true);
	offsets::model_ambient_min = memory->pattern_scan(modules::engine, L"F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C", 0x4, 0x0, true, true);
	offsets::dwGlowObjectManager = memory->pattern_scan(modules::client, L"A1 ? ? ? ? A8 01 75 4B", 0x1, 0x4, true, true);
	offsets::dwForceAttack = memory->pattern_scan(modules::client, L"89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", 0x2, 0x0, true, true);
	offsets::force_update_spectator_glow = memory->pattern_scan(modules::client, L"74 07 8B CB E8 ? ? ? ? 83 C7 10", 0x0, 0x0, false, true);
	DWORD dwGetAllClasses = memory->pattern_scan(modules::client, L"A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", 0x1, 0x0, false, false);

	globals::client_state = memory->read<DWORD>(modules::engine.base + offsets::dwClientState);
	DWORD dwGetAllClasses_deref = memory->read<DWORD>(dwGetAllClasses);
	DWORD dwGetAllClasses_offset = memory->read<DWORD>(dwGetAllClasses_deref) - modules::client.base;

	std::unique_ptr<NetvarsClass> NetvarManager(new NetvarsClass(modules::client.base + dwGetAllClasses_offset));

	offsets::m_fFlags = NetvarManager->NETVAR("DT_CSPlayer", "m_fFlags");
	offsets::m_iTeamNum = NetvarManager->NETVAR("DT_BasePlayer", "m_iTeamNum");
	offsets::m_iGlowIndex = NetvarManager->NETVAR("DT_CSPlayer", "m_flFlashDuration") + 0x18;
	offsets::m_iCrosshairId = NetvarManager->NETVAR("DT_CSPlayer", "m_bHasDefuser") + 0x5C;
	offsets::m_bSpotted = NetvarManager->NETVAR("DT_BaseEntity", "m_bSpotted");
}

void cheat::shutdown() {
	menu::chams = false;
	chams::toggle = false;
	chams::undo();
	menu::glow = false;
	glow::toggle = false;
	glow::undo();
}