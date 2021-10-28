#include "bhop.h"

void bhop::run() {
	if (!menu::bhop)
		return;

	if (!(GetAsyncKeyState(VK_SPACE)))
		return;

	if (!globals::local_player.pointer)
		return;

	int flags = memory->read<int>(globals::local_player.pointer + offsets::m_fFlags);

	if (flags == 257) {
		memory->write<int>(modules::client.base + offsets::dwForceJump, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		memory->write<int>(modules::client.base + offsets::dwForceJump, 0);
	}
}