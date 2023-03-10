#pragma once

#include <Windows.h>

struct s_module {
	DWORD base, size;
};

struct vec3 {
	float x, y, z;

	vec3(void) {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3(const vec3& vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	vec3 operator+(vec3 vec) {
		return vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	vec3 operator-(vec3 vec) {
		return vec3(x - vec.x, y - vec.y, z - vec.z);
	}
};

struct qangle {
	float pitch, yaw, roll;

	qangle(void) {
		this->pitch = 0;
		this->yaw = 0;
		this->roll = 0;
	}

	qangle(float pitch, float yaw, float roll) {
		this->pitch = pitch;
		this->yaw = yaw;
		this->roll = roll;
	}

	qangle(const qangle& ang) {
		this->pitch = ang.pitch;
		this->yaw = ang.yaw;
		this->roll = ang.roll;
	}

	qangle operator+(qangle ang) {
		return qangle(pitch + ang.pitch, yaw + ang.yaw, roll + ang.roll);
	}

	qangle operator/(float factor) {
		return qangle(pitch / factor, yaw / factor, roll / factor);
	}

	qangle operator-(qangle ang) {
		return qangle(pitch - ang.pitch, yaw - ang.yaw, roll - ang.roll);
	}

	qangle operator*(float factor) {
		return qangle(pitch * factor, yaw * factor, roll * factor);
	}
};

struct s_local_player {
	DWORD pointer;
	int team, health;
	BYTE lifestate;
	vec3 origin;
};

struct matrix4x4 {
	float matrix[16];
};

struct matrix3x4 {
	float matrix[3][4];
};

struct player_info {
	__int64         unknown;            
	union {
		__int64       steamID64;          
		struct {
			__int32     xuid_low;
			__int32     xuid_high;
		};
	};
	char            szName[128];        
	int             userId;             
	char            szSteamID[20];      
	char            pad_0x00A8[0x10];   
	unsigned long   iSteamID;           
	char            szFriendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customfiles[4];
	unsigned char   filesdownloaded;
};

enum en_item_definition_index : short {
	weapon_deagle = 1,
	weapon_elite,
	weapon_fiveseven,
	weapon_glock,
	weapon_ak47 = 7,
	weapon_aug,
	weapon_awp,
	weapon_famas,
	weapon_g3sg1,
	weapon_galilar = 13,
	weapon_m249,
	weapon_m4a1 = 16,
	weapon_mac10,
	weapon_p90 = 19,
	weapon_zone_repulsor,
	weapon_mp5sd = 23,
	weapon_ump45,
	weapon_xm1014,
	weapon_bizon,
	weapon_mag7,
	weapon_negev,
	weapon_sawedoff,
	weapon_tec9,
	weapon_taser,
	weapon_hkp2000,
	weapon_mp7,
	weapon_mp9,
	weapon_nova,
	weapon_p250,
	weapon_shield,
	weapon_scar20,
	weapon_sg556,
	weapon_ssg08,
	weapon_knifegg,
	weapon_knife,
	weapon_flashbang,
	weapon_hegrenade,
	weapon_smokegrenade,
	weapon_molotov,
	weapon_decoy,
	weapon_incgrenade,
	weapon_c4,
	item_kevlar,
	item_assaultsuit,
	item_heavyassaultsuit,
	item_nvg = 54,
	item_defuser,
	item_cutters,
	weapon_healthshot,
	weapon_knife_t = 59,
	weapon_m4a1_silencer,
	weapon_usp_silencer,
	weapon_cz75a = 63,
	weapon_revolver,
	weapon_tagrenade = 68,
	weapon_fists,
	weapon_breachcharge,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe,
	weapon_hammer,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb,
	weapon_diversion,
	weapon_frag_grenade,
	weapon_snowball,
	weapon_bumpmine,
	weapon_bayonet = 500,
	weapon_knife_css = 503,
	weapon_knife_flip = 505,
	weapon_knife_gut,
	weapon_knife_karambit,
	weapon_knife_m9_bayonet,
	weapon_knife_tactical,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly,
	weapon_knife_push,
	weapon_knife_cord,
	weapon_knife_canis,
	weapon_knife_ursus,
	weapon_knife_gypsy_jackknife,
	weapon_knife_outdoor,
	weapon_knife_stiletto,
	weapon_knife_widowmaker,
	weapon_knife_skeleton = 525,
	customplayer_tm_professional_varf5 = 4613,
	customplayer_ctm_st6_variantj = 4619,
	customplayer_ctm_st6_variantl = 4680,
	customplayer_ctm_swat_variante = 4711,
	customplayer_ctm_swat_variantf,
	customplayer_ctm_swat_variantg,
	customplayer_ctm_swat_varianth,
	customplayer_ctm_swat_varianti,
	customplayer_ctm_swat_variantj,
	customplayer_tm_balkan_variantk = 4718,
	studded_brokenfang_gloves = 4725,
	customplayer_tm_professional_varf,
	customplayer_tm_professional_varg,
	customplayer_tm_professional_varh,
	customplayer_tm_professional_varj = 4730,
	customplayer_tm_professional_vari = 4732,
	customplayer_tm_professional_varf1,
	customplayer_tm_professional_varf2,
	customplayer_tm_professional_varf3,
	customplayer_tm_professional_varf4,
	customplayer_ctm_gendarmerie_varianta = 4749,
	customplayer_ctm_gendarmerie_variantb,
	customplayer_ctm_gendarmerie_variantc,
	customplayer_ctm_gendarmerie_variantd,
	customplayer_ctm_gendarmerie_variante,
	customplayer_ctm_swat_variantk = 4756,
	customplayer_ctm_diver_varianta,
	customplayer_ctm_diver_variantb = 4771,
	customplayer_ctm_diver_variantc,
	customplayer_tm_jungle_raider_varianta,
	customplayer_tm_jungle_raider_variantb,
	customplayer_tm_jungle_raider_variantc,
	customplayer_tm_jungle_raider_variantd,
	customplayer_tm_jungle_raider_variante,
	customplayer_tm_jungle_raider_variantf,
	customplayer_tm_jungle_raider_variantb2 = 4780,
	customplayer_tm_jungle_raider_variantf2,
	studded_bloodhound_gloves = 5027,
	t_gloves,
	ct_gloves,
	sporty_gloves,
	slick_gloves,
	leather_handwraps,
	motorcycle_gloves,
	specialist_gloves,
	studded_hydra_gloves,
	customplayer_t_map_based,
	customplayer_ct_map_based,
	customplayer_tm_anarchist,
	customplayer_tm_anarchist_varianta,
	customplayer_tm_anarchist_variantb,
	customplayer_tm_anarchist_variantc,
	customplayer_tm_anarchist_variantd,
	customplayer_tm_pirate,
	customplayer_tm_pirate_varianta,
	customplayer_tm_pirate_variantb,
	customplayer_tm_pirate_variantc,
	customplayer_tm_pirate_variantd,
	customplayer_tm_professional,
	customplayer_tm_professional_var1,
	customplayer_tm_professional_var2,
	customplayer_tm_professional_var3,
	customplayer_tm_professional_var4,
	customplayer_tm_separatist,
	customplayer_tm_separatist_varianta,
	customplayer_tm_separatist_variantb,
	customplayer_tm_separatist_variantc,
	customplayer_tm_separatist_variantd,
	customplayer_ctm_gign,
	customplayer_ctm_gign_varianta,
	customplayer_ctm_gign_variantb,
	customplayer_ctm_gign_variantc,
	customplayer_ctm_gign_variantd,
	customplayer_ctm_gsg9,
	customplayer_ctm_gsg9_varianta,
	customplayer_ctm_gsg9_variantb,
	customplayer_ctm_gsg9_variantc,
	customplayer_ctm_gsg9_variantd,
	customplayer_ctm_idf,
	customplayer_ctm_idf_variantb,
	customplayer_ctm_idf_variantc,
	customplayer_ctm_idf_variantd,
	customplayer_ctm_idf_variante,
	customplayer_ctm_idf_variantf,
	customplayer_ctm_swat,
	customplayer_ctm_swat_varianta,
	customplayer_ctm_swat_variantb,
	customplayer_ctm_swat_variantc,
	customplayer_ctm_swat_variantd,
	customplayer_ctm_sas_varianta,
	customplayer_ctm_sas_variantb,
	customplayer_ctm_sas_variantc,
	customplayer_ctm_sas_variantd,
	customplayer_ctm_st6,
	customplayer_ctm_st6_varianta,
	customplayer_ctm_st6_variantb,
	customplayer_ctm_st6_variantc,
	customplayer_ctm_st6_variantd,
	customplayer_tm_balkan_variante,
	customplayer_tm_balkan_varianta,
	customplayer_tm_balkan_variantb,
	customplayer_tm_balkan_variantc,
	customplayer_tm_balkan_variantd,
	customplayer_tm_jumpsuit_varianta,
	customplayer_tm_jumpsuit_variantb,
	customplayer_tm_jumpsuit_variantc,
	customplayer_tm_phoenix_heavy,
	customplayer_ctm_heavy,
	customplayer_tm_leet_varianta = 5100,
	customplayer_tm_leet_variantb,
	customplayer_tm_leet_variantc,
	customplayer_tm_leet_variantd,
	customplayer_tm_leet_variante,
	customplayer_tm_leet_variantg,
	customplayer_tm_leet_varianth,
	customplayer_tm_leet_varianti,
	customplayer_tm_leet_variantf,
	customplayer_tm_leet_variantj,
	customplayer_tm_phoenix = 5200,
	customplayer_tm_phoenix_varianta,
	customplayer_tm_phoenix_variantb,
	customplayer_tm_phoenix_variantc,
	customplayer_tm_phoenix_variantd,
	customplayer_tm_phoenix_varianth,
	customplayer_tm_phoenix_variantf,
	customplayer_tm_phoenix_variantg,
	customplayer_tm_phoenix_varianti,
	customplayer_ctm_fbi = 5300,
	customplayer_ctm_fbi_varianta,
	customplayer_ctm_fbi_variantc,
	customplayer_ctm_fbi_variantd,
	customplayer_ctm_fbi_variante,
	customplayer_ctm_fbi_variantf,
	customplayer_ctm_fbi_variantg,
	customplayer_ctm_fbi_varianth,
	customplayer_ctm_fbi_variantb,
	customplayer_ctm_st6_variantk = 5400,
	customplayer_ctm_st6_variante,
	customplayer_ctm_st6_variantg,
	customplayer_ctm_st6_variantm,
	customplayer_ctm_st6_varianti,
	customplayer_ctm_st6_variantn,
	customplayer_tm_balkan_variantf = 5500,
	customplayer_tm_balkan_varianti,
	customplayer_tm_balkan_variantg,
	customplayer_tm_balkan_variantj,
	customplayer_tm_balkan_varianth,
	customplayer_tm_balkan_variantl,
	customplayer_ctm_sas = 5600,
	customplayer_ctm_sas_variantf,
	customplayer_ctm_sas_variantg
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
	extern DWORD dwViewMatrix;
	extern DWORD m_vecOrigin;
	extern DWORD dwClientState_PlayerInfo;
	extern DWORD m_hMyWeapons;
	extern DWORD m_vecViewOffset;
	extern DWORD dwClientState_ViewAngles;
	extern DWORD m_aimPunchAngle;
	extern DWORD m_dwBoneMatrix;
	extern DWORD m_iItemDefinitionIndex;
};

namespace globals {
	extern s_local_player local_player;
	extern DWORD client_state;
	extern DWORD glow_object_manager;
	extern DWORD enemies[64];
	extern DWORD user_info_table;
	extern DWORD items;
};

namespace modules {
	extern s_module client;
	extern s_module engine;
};

namespace data {
	extern LPCWSTR game_name;
	extern bool should_continue;
	extern int screen_width;
	extern int screen_height;
	extern int cs_window_width;
	extern int cs_window_height;
};

struct s_menu_bools {
	bool open = true;
	bool chams = false;
	bool triggerbot = false;
	bool glow = false;
	bool bhop = false;
	bool radar = false;
	bool boxesp = false;
	bool nameesp = false;
	bool weaponesp = false;
	bool aimbot = false;
	bool hpesp = false;
};

extern s_menu_bools menu_bools;
