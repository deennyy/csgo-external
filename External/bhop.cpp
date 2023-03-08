#include "bhop.h"

void bhop::run() {
	if (!menu_bools.bhop)
		return;

	if (!globals::local_player.pointer || globals::local_player.health <= 0 || globals::local_player.lifestate != 0)
		return;

	int flags = memory->read<int>(globals::local_player.pointer + offsets::m_fFlags);

	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && (flags & (1 << 0))) {
		memory->write<int>(modules::client.base + offsets::dwForceJump, 5);
	}
	else if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !(flags & (1 << 0))) {
		memory->write<int>(modules::client.base + offsets::dwForceJump, 4);
		memory->write<int>(modules::client.base + offsets::dwForceJump, 5);
		memory->write<int>(modules::client.base + offsets::dwForceJump, 4);
	}
}