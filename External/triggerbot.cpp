#include "triggerbot.h"

void triggerbot::run() {
	if (!menu::triggerbot)
		return;

	if (!(GetAsyncKeyState(VK_XBUTTON2)))
		return;

	if (!globals::local_player.pointer || globals::local_player.health <= 0 || globals::local_player.lifestate != 0)
		return;

	int xhair_id = memory->read<int>(globals::local_player.pointer + offsets::m_iCrosshairId);

	if (xhair_id > 0 && xhair_id <= 64) {
		DWORD entity = memory->read<DWORD>(modules::client.base + offsets::dwEntityList + (xhair_id - 1) * 0x10);

		if (!entity)
			return;

		int entityteam = memory->read<int>(entity + offsets::m_iTeamNum);
		int entityhealth = memory->read<int>(entity + offsets::m_iHealth);
		bool entitydormant = memory->read<bool>(entity + offsets::m_bDormant);

		if (entityteam == globals::local_player.team || entityhealth <= 0 || entitydormant)
			return;

		memory->write<int>(modules::client.base + offsets::dwForceAttack, 5);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		memory->write<int>(modules::client.base + offsets::dwForceAttack, 4);
	}
}