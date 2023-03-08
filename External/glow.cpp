#include "glow.h"

struct glow_object_t {
	int   m_nNextFreeSlot;
	DWORD entity;
	float m_flRed;
	float m_flGreen;
	float m_flBlue;
	float m_flAlpha;
	bool  m_bGlowAlphaCappedByRenderAlpha;
	float m_flGlowAlphaFunctionOfMaxVelocity;
	float m_flGlowAlphaMax;
	float m_flGlowPulseOverdrive;
	bool  m_bRenderWhenOccluded;
	bool  m_bRenderWhenUnoccluded;
	bool  m_bFullBloomRender;
	int   m_nFullBloomStencilTestValue;
	int   m_nGlowStyle;
	int   m_nSplitScreenSlot;
};

namespace glow {
	bool toggle = false;
	bool should_write = true;
}

void glow::run() {
	if (!globals::local_player.pointer)
		return;

	if (menu_bools.glow) {
		toggle = true;

		for (int i = 0; i <= 31; i++) {
			if (!globals::enemies[i])
				continue;

			int glow_index = memory->read<int>(globals::enemies[i] + offsets::m_iGlowIndex);
			DWORD glow_object_address = globals::glow_object_manager + glow_index * sizeof(glow_object_t);

			if (!glow_object_address)
				return;

			glow_object_t glow_object = memory->read<glow_object_t>(glow_object_address);

			glow_object.m_flRed = menu::glowcolor[0];
			glow_object.m_flGreen = menu::glowcolor[1];
			glow_object.m_flBlue = menu::glowcolor[2];
			glow_object.m_flAlpha = menu::glowcolor[3];
			glow_object.m_bRenderWhenOccluded = true;

			memory->write<glow_object_t>(glow_object_address, glow_object);
		}

		if (should_write) {
			should_write = false;
			memory->write<BYTE>(modules::client.base + offsets::force_update_spectator_glow, 0xEB);
		}
	}
	else {
		if (toggle) {
			toggle = false;

			for (int i = 0; i <= 31; i++) {
				if (!globals::enemies[i])
					continue;

				int glow_index = memory->read<int>(globals::enemies[i] + offsets::m_iGlowIndex);
				DWORD glow_object_address = globals::glow_object_manager + glow_index * sizeof(glow_object_t);

				if (!glow_object_address)
					return;

				glow_object_t glow_object = memory->read<glow_object_t>(glow_object_address);

				glow_object.m_bRenderWhenOccluded = false;

				memory->write<glow_object_t>(glow_object_address, glow_object);
			}

			if (!should_write) {
				should_write = true;
				memory->write<BYTE>(modules::client.base + offsets::force_update_spectator_glow, 0x74);
			}
		}
	}
}

void glow::undo() {
	if (menu_bools.glow)
		return;

	if (!globals::local_player.pointer)
		return;

	for (int i = 0; i <= 31; i++) {
		if (!globals::enemies[i])
			continue;

		int glow_index = memory->read<int>(globals::enemies[i] + offsets::m_iGlowIndex);
		DWORD glow_object_address = globals::glow_object_manager + glow_index * sizeof(glow_object_t);

		if (!glow_object_address)
			return;

		glow_object_t glow_object = memory->read<glow_object_t>(glow_object_address);

		glow_object.m_bRenderWhenOccluded = false;

		memory->write<glow_object_t>(glow_object_address, glow_object);
	}

	memory->write<BYTE>(modules::client.base + offsets::force_update_spectator_glow, 0x74);
}