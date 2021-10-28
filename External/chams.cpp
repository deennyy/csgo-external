#include "chams.h"

namespace chams {
	bool toggle = false;
}

void chams::run() { // from uc
	if (!globals::local_player.pointer)
		return;

	if (menu::chams) {
		toggle = true;

		for (int i = 0; i <= 31; i++) {
			memory->write<BYTE>(globals::enemies[i] + 0x70, menu::chamscolor[0] * 255.f);
			memory->write<BYTE>(globals::enemies[i] + 0x71, menu::chamscolor[1] * 255.f);
			memory->write<BYTE>(globals::enemies[i] + 0x72, menu::chamscolor[2] * 255.f);
		}

		DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
		DWORD xored = *(DWORD*)&menu::chamsbright ^ thisPtr;
		memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
	}
	else {
		if (toggle) {
			toggle = false;

			for (int i = 0; i <= 31; i++) {
				memory->write<BYTE>(globals::enemies[i] + 0x70, 255.f);
				memory->write<BYTE>(globals::enemies[i] + 0x71, 255.f);
				memory->write<BYTE>(globals::enemies[i] + 0x72, 255.f);
			}

			DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
			float zero = 0.f;
			DWORD xored = *(DWORD*)&zero ^ thisPtr;
			memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
		}
	}
}

void chams::undo() {
	if (menu::chams)
		return;

	if (!globals::local_player.pointer)
		return;

	for (int i = 0; i <= 31; i++) {
		memory->write<BYTE>(globals::enemies[i] + 0x70, 255.f);
		memory->write<BYTE>(globals::enemies[i] + 0x71, 255.f);
		memory->write<BYTE>(globals::enemies[i] + 0x72, 255.f);
	}

	DWORD thisPtr = (int)(modules::engine.base + offsets::model_ambient_min - 0x2c);
	float zero = 0.f;
	DWORD xored = *(DWORD*)&zero ^ thisPtr;
	memory->write<DWORD>(modules::engine.base + offsets::model_ambient_min, xored);
}