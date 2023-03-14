#include "esp.h"

namespace esp {
	vec3 head, feet;
	float width, height, dist;
}

void esp::box(ImDrawList* draw_list, DWORD entity) {
	if (feet.z > 0.01f) {
		draw_list->AddRect(ImVec2(head.x + (width / 2), head.y - (dist / 45.f)), ImVec2(head.x - (width / 2), feet.y - (dist / 45.f)), ImColor(ImVec4(menu::boxespcol[0], menu::boxespcol[1], menu::boxespcol[2], menu::boxespcol[3])));
	}
}

void esp::name(ImDrawList* draw_list, DWORD entity) {
	if (feet.z > 0.01f) {
		player_info _player_info;

		int index = memory->read<int>(entity + 0x64);
		_player_info = memory->read<player_info>(memory->read<DWORD>(globals::items + 0x28 + ((index - 1) * 0x34)));

		draw_list->AddText(ImVec2(head.x + (width / 2), head.y - (dist / 45.f) - 10.f), ImColor(ImVec4(menu::nameespcol[0], menu::nameespcol[1], menu::nameespcol[2], menu::nameespcol[3])), _player_info.szName);
	}
}

void esp::weapon(ImDrawList* draw_list, DWORD entity) {
	if (feet.z > 0.01f) {
		DWORD active_weapon_handle = memory->read<DWORD>(entity + offsets::m_hMyWeapons);
		DWORD weapon_entity = memory->read<DWORD>(modules::client.base + offsets::dwEntityList + ((active_weapon_handle & 0xFFF) - 1) * 0x10);
		int weapon_index = memory->read<int>(weapon_entity + offsets::m_iItemDefinitionIndex);

		draw_list->AddText(ImVec2(head.x + (width / 2), feet.y - (dist / 45.f)), ImColor(ImVec4(menu::weaponespcol[0], menu::weaponespcol[1], menu::weaponespcol[2], menu::weaponespcol[3])), cheat::weapon_id_to_str(weapon_index));
	}
}

void esp::health(ImDrawList* draw_list, DWORD entity) {
	if (feet.z > 0.01f) {
		int entityhealth = memory->read<int>(entity + offsets::m_iHealth);

		draw_list->AddText(ImVec2(head.x + (width / 2) - 20.f, head.y - (dist / 45.f)), ImColor(ImVec4(menu::hpespcol[0], menu::hpespcol[1], menu::hpespcol[2], menu::hpespcol[3])), std::to_string(entityhealth).c_str());
	}
}

void esp::ammo(ImDrawList* draw_list, DWORD entity) {
	if (feet.z > 0.01f) {
		DWORD active_weapon_handle = memory->read<DWORD>(entity + offsets::m_hMyWeapons) & 0xFFF;
		DWORD weapon_entity = memory->read<DWORD>(modules::client.base + offsets::dwEntityList + ((active_weapon_handle - 1) * 0x10));
		int entityammo = memory->read<int>(weapon_entity + offsets::m_iClip1);

		draw_list->AddText(ImVec2(head.x + (width / 2), feet.y - (dist / 45.f) + 10.f), ImColor(ImVec4(menu::nameespcol[0], menu::nameespcol[1], menu::nameespcol[2], menu::nameespcol[3])), std::to_string(entityammo).c_str());
	}
}

void esp::run(ImDrawList* draw_list) {
    if (!globals::local_player.pointer)
        return;

	for (int i = 0; i < 64; i++) {
		if (!globals::enemies[i])
			continue;

		int entityteam = memory->read<int>(globals::enemies[i] + offsets::m_iTeamNum);
		int entityhealth = memory->read<int>(globals::enemies[i] + offsets::m_iHealth);
		bool entitydormant = memory->read<bool>(globals::enemies[i] + offsets::m_bDormant);
		BYTE entitylifestate = memory->read<BYTE>(globals::enemies[i] + offsets::m_lifeState);
		int entityclassid = memory->read<int>(memory->read<int>(memory->read<int>(memory->read<int>(globals::enemies[i] + 0x8) + 0x8) + 0x1) + 0x14);

		if (entityteam == globals::local_player.team || entityhealth <= 0 || entitydormant || entitylifestate != 0 || entityclassid != 40)
			continue;

		vec3 entity_origin = memory->read<vec3>(globals::enemies[i] + offsets::m_vecOrigin);
		feet = cheat::w2s(entity_origin);
		vec3 entity_head(entity_origin.x, entity_origin.y, entity_origin.z + 72.f);
		head = cheat::w2s(entity_head);
		dist = sqrt(pow(entity_origin.x - globals::local_player.origin.x, 2) + pow(entity_origin.y - globals::local_player.origin.y, 2)) * 0.0254f;
		height = head.y - feet.y;
		width = height / 2.4f;

		if (menu_bools.boxesp)
			box(draw_list, globals::enemies[i]);

		if (menu_bools.nameesp)
			name(draw_list, globals::enemies[i]);

		if (menu_bools.weaponesp)
			weapon(draw_list, globals::enemies[i]);

		if (menu_bools.hpesp)
			health(draw_list, globals::enemies[i]);

		if (menu_bools.ammoesp)
			ammo(draw_list, globals::enemies[i]);
	}
}