#include "radar.h"

void radar::run() {
	if (!menu::radar)
		return;

	if (!globals::local_player.pointer)
		return;

	for (int i = 0; i <= 31; i++) {
		if (!globals::enemies[i])
			continue;

		memory->write<bool>(globals::enemies[i] + offsets::m_bSpotted, true);
	}
}