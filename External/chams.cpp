#include "chams.h"

namespace chams {
	bool toggle = false;
}

void chams::run() { // from uc
	if (!globals::local_player.pointer)
		return;

	if (menu_bools.chams) {
		toggle = true;

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

			memory->write<BYTE>(globals::enemies[i] + offsets::m_clrRender, menu::chamscolor[0] * 255.f);
			memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x1), menu::chamscolor[1] * 255.f);
			memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x2), menu::chamscolor[2] * 255.f);
		}

		DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
		DWORD xored = *(DWORD*)&menu::chamsbright ^ thisPtr;
		memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
	}
	else {
		if (toggle) {
			toggle = false;

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

				memory->write<BYTE>(globals::enemies[i] + offsets::m_clrRender, 255.f);
				memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x1), 255.f);
				memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x2), 255.f);
			}

			DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
			float zero = 0.f;
			DWORD xored = *(DWORD*)&zero ^ thisPtr;
			memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
		}
	}
}

void chams::undo() {
	if (menu_bools.chams)
		return;

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

		memory->write<BYTE>(globals::enemies[i] + offsets::m_clrRender, 255.f);
		memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x1), 255.f);
		memory->write<BYTE>(globals::enemies[i] + (offsets::m_clrRender + 0x2), 255.f);
	}

	DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
	float zero = 0.f;
	DWORD xored = *(DWORD*)&zero ^ thisPtr;
	memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
}