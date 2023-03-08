#include "cheat.h"

void cheat::startup() {
	data::screen_width = GetSystemMetrics(SM_CXSCREEN);
	data::screen_height = GetSystemMetrics(SM_CYSCREEN);

	modules::engine = memory->get_module(L"engine.dll");
	modules::client = memory->get_module(L"client.dll");

	if (!data::should_continue)
		return;

	offsets::dwClientState = memory->pattern_scan(modules::engine, L"A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", 0x1, 0x0, true, true);
	offsets::dwClientState_GetLocalPlayer = memory->pattern_scan(modules::engine, L"8B 80 ? ? ? ? 40 C3", 0x2, 0x0, true, false);
	offsets::dwEntityList = memory->pattern_scan(modules::client, L"BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", 0x1, 0x0, true, true);
	offsets::dwForceJump = memory->pattern_scan(modules::client, L"8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", 0x2, 0x0, true, true);
	offsets::model_ambient_min = memory->pattern_scan(modules::engine, L"F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C", 0x4, 0x0, true, true);
	offsets::dwGlowObjectManager = memory->pattern_scan(modules::client, L"A1 ? ? ? ? A8 01 75 4B", 0x1, 0x4, true, true);
	offsets::dwForceAttack = memory->pattern_scan(modules::client, L"89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", 0x2, 0x0, true, true);
	offsets::force_update_spectator_glow = memory->pattern_scan(modules::client, L"74 07 8B CB E8 ? ? ? ? 83 C7 10", 0x0, 0x0, false, true);
	offsets::m_bDormant = memory->pattern_scan(modules::client, L"8A 81 ? ? ? ? C3 32 C0", 0x2, 0x8, true, false);
	offsets::dwViewMatrix = memory->pattern_scan(modules::client, L"0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9", 0x3, 0xB0, true, true);
	offsets::dwClientState_PlayerInfo = memory->pattern_scan(modules::engine, L"8B 89 ? ? ? ? 85 C9 0F 84 ? ? ? ? 8B 01", 0x2, 0x0, true, false);
	offsets::dwClientState_ViewAngles = memory->pattern_scan(modules::engine, L"F3 0F 11 86 ? ? ? ? F3 0F 10 44 24 ? F3 0F 11 86", 0x4, 0x0, true, false);

	globals::client_state = memory->read<DWORD>(modules::engine.base + offsets::dwClientState);
	globals::user_info_table = memory->read<DWORD>(globals::client_state + offsets::dwClientState_PlayerInfo);
	globals::items = memory->read<DWORD>(memory->read<DWORD>(globals::user_info_table + 0x40) + 0xC);

	DWORD dwGetAllClasses = memory->pattern_scan(modules::client, L"A1 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC A1 ? ? ? ? B9", 0x1, 0x0, false, false);
	DWORD dwGetAllClasses_deref = memory->read<DWORD>(dwGetAllClasses);
	DWORD dwGetAllClasses_offset = memory->read<DWORD>(dwGetAllClasses_deref) - modules::client.base;

	std::unique_ptr<NetvarsClass> NetvarManager(new NetvarsClass(modules::client.base + dwGetAllClasses_offset));

	offsets::m_fFlags = NetvarManager->NETVAR("DT_CSPlayer", "m_fFlags");
	offsets::m_iTeamNum = NetvarManager->NETVAR("DT_BasePlayer", "m_iTeamNum");
	offsets::m_iGlowIndex = NetvarManager->NETVAR("DT_CSPlayer", "m_flFlashDuration") + 0x18;
	offsets::m_iCrosshairId = NetvarManager->NETVAR("DT_CSPlayer", "m_bHasDefuser") + 0x5C;
	offsets::m_bSpotted = NetvarManager->NETVAR("DT_BaseEntity", "m_bSpotted");
	offsets::m_iHealth = NetvarManager->NETVAR("DT_BasePlayer", "m_iHealth");
	offsets::m_lifeState = NetvarManager->NETVAR("DT_CSPlayer", "m_lifeState");
	offsets::m_bGunGameImmunity = NetvarManager->NETVAR("DT_CSPlayer", "m_bGunGameImmunity");
	offsets::m_clrRender = NetvarManager->NETVAR("DT_BaseEntity", "m_clrRender");
	offsets::m_vecOrigin = NetvarManager->NETVAR("DT_BasePlayer", "m_vecOrigin");
	offsets::m_hMyWeapons = NetvarManager->NETVAR("DT_BasePlayer", "m_hMyWeapons");
	offsets::m_vecViewOffset = NetvarManager->NETVAR("DT_CSPlayer", "m_vecViewOffset[0]");
	offsets::m_dwBoneMatrix = NetvarManager->NETVAR("DT_BaseAnimating", "m_nForceBone") + 0x1C;

	// these are offsets that i for some reason cannot get with the netvar manager, just wont work
	offsets::m_aimPunchAngle = 0x303C;
	offsets::m_iItemDefinitionIndex = 0x2FBA;
}

void cheat::shutdown() {
	menu::chams = false;
	chams::toggle = false;
	chams::undo();
	menu::glow = false;
	glow::toggle = false;
	glow::undo();
}

vec3 cheat::w2s(const vec3 pos) {
	auto matrix = memory->read<matrix4x4>(modules::client.base + offsets::dwViewMatrix);

	vec3 out;
	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

	_x *= 1.f / out.z;
	_y *= 1.f / out.z;

	int width = data::cs_window_width;
	int height = data::cs_window_height;

	out.x = width * .5f;
	out.y = height * .5f;

	out.x += 0.5f * _x * width + 0.5f;
	out.y -= 0.5f * _y * height + 0.5f;

	return out;
}

float cheat::normalize_angle(float ang)
{
	if (!std::isfinite(ang)) {
		return 0.0f;
	}

	return std::remainder(ang, 360.0f);
}

void cheat::clamp_angles(qangle angle) {
	angle.pitch = std::max(-89.0f, std::min(89.0f, normalize_angle(angle.pitch)));
	angle.yaw = normalize_angle(angle.yaw);
	angle.roll = 0.0f;
}

const char* cheat::weapon_id_to_str(int id) {
	switch (id) {
	case weapon_deagle:
		return "deagle";
		break;
	case weapon_elite:
		return "dualies";
		break;
	case weapon_fiveseven:
		return "five-seven";
		break;
	case weapon_glock:
		return "glock";
		break;
	case weapon_ak47:
		return "ak-47";
		break;
	case weapon_aug:
		return "aug";
		break;
	case weapon_awp:
		return "awp";
		break;
	case weapon_famas:
		return "famas";
		break;
	case weapon_g3sg1:
		return "g3sg1";
		break;
	case weapon_galilar:
		return "galil";
		break;
	case weapon_m249:
		return "m249";
		break;
	case weapon_m4a1:
		return "m4a4";
		break;
	case weapon_mac10:
		return "mac-10";
		break;
	case weapon_p90:
		return "p90";
		break;
	case weapon_mp5sd:
		return "mp5";
		break;
	case weapon_ump45:
		return "ump";
		break;
	case weapon_xm1014:
		return "xm";
		break;
	case weapon_bizon:
		return "bizon";
		break;
	case weapon_mag7:
		return "mag-7";
		break;
	case weapon_negev:
		return "negev";
		break;
	case weapon_sawedoff:
		return "sawed-off";
		break;
	case weapon_tec9:
		return "tec-9";
		break;
	case weapon_taser:
		return "taser";
		break;
	case weapon_hkp2000:
		return "p2k";
		break;
	case weapon_mp7:
		return "mp-7";
		break;
	case weapon_mp9:
		return "mp-9";
		break;
	case weapon_nova:
		return "nova";
		break;
	case weapon_p250:
		return "p250";
		break;
	case weapon_shield:
		return "riot shield";
		break;
	case weapon_scar20:
		return "scar-20";
		break;
	case weapon_sg556:
		return "sg-553";
		break;
	case weapon_ssg08:
		return "scout";
		break;
	case weapon_knifegg:
		return "knife";
		break;
	case weapon_knife:
		return "knife";
		break;
	case weapon_flashbang:
		return "flash";
		break;
	case weapon_hegrenade:
		return "frag";
		break;
	case weapon_smokegrenade:
		return "smoke";
		break;
	case weapon_molotov:
		return "molotov";
		break;
	case weapon_decoy:
		return "decoy";
		break;
	case weapon_incgrenade:
		return "incendiary";
		break;
	case weapon_c4:
		return "c4";
		break;
	case weapon_healthshot:
		return "health-shot";
		break;
	case weapon_knife_t:
		return "knife";
		break;
	case weapon_m4a1_silencer:
		return "m4a1";
		break;
	case weapon_usp_silencer:
		return "usp";
		break;
	case weapon_cz75a:
		return "cz";
		break;
	case weapon_revolver:
		return "revolver";
		break;
	case weapon_tagrenade:
		return "TA grenade";
		break;
	case weapon_fists:
		return "fists";
		break;
	case weapon_breachcharge:
		return "breach charge";
		break;
	case weapon_tablet:
		return "tablet";
		break;
	case weapon_melee:
		return "knife";
		break;
	case weapon_axe:
		return "axe";
		break;
	case weapon_hammer:
		return "hammer";
		break;
	case weapon_spanner:
		return "wrench";
		break;
	case weapon_firebomb:
		return "fire bomb";
		break;
	case weapon_diversion:
		return "diversion device";
		break;
	case weapon_frag_grenade:
		return "frag";
		break;
	case weapon_snowball:
		return "snowball";
		break;
	case weapon_bumpmine:
		return "bump mine";
		break;
	case weapon_knife_ghost:
		return "knife";
		break;
	case weapon_bayonet:
		return "knife";
		break;
	case weapon_knife_css:
		return "knife";
		break;
	case weapon_knife_flip:
		return "knife";
		break;
	case weapon_knife_gut:
		return "knife";
		break;
	case weapon_knife_karambit:
		return "knife";
		break;
	case weapon_knife_m9_bayonet:
		return "knife";
		break;
	case weapon_knife_tactical:
		return "knife";
		break;
	case weapon_knife_falchion:
		return "knife";
		break;
	case weapon_knife_survival_bowie:
		return "knife";
		break;
	case weapon_knife_butterfly:
		return "knife";
		break;
	case weapon_knife_push:
		return "knife";
		break;
	case weapon_knife_cord:
		return "knife";
		break;
	case weapon_knife_canis:
		return "knife";
		break;
	case weapon_knife_ursus:
		return "knife";
		break;
	case weapon_knife_gypsy_jackknife:
		return "knife";
		break;
	case weapon_knife_outdoor:
		return "knife";
		break;
	case weapon_knife_stiletto:
		return "knife";
		break;
	case weapon_knife_widowmaker:
		return "knife";
		break;
	case weapon_knife_skeleton:
		return "knife";
		break;
	default:
		return "unknown";
		break;
	}

	return "unknown";
}