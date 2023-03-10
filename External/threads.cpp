#include "threads.h"

void threads::main_thread() {
	while (data::should_continue && FindWindow(NULL, data::game_name)) {
		data::should_continue = true;

		if (GetAsyncKeyState(VK_INSERT) & 1)
			menu_bools.open = !menu_bools.open;

		if (globals::client_state) {
			globals::local_player.pointer = memory->read<DWORD>(modules::client.base + offsets::dwEntityList + (memory->read<int>(globals::client_state + offsets::dwClientState_GetLocalPlayer)) * 0x10);
			if (globals::local_player.pointer) {
				globals::local_player.team = memory->read<int>(globals::local_player.pointer + offsets::m_iTeamNum);
				globals::local_player.health = memory->read<int>(globals::local_player.pointer + offsets::m_iHealth);
				globals::local_player.lifestate = memory->read<BYTE>(globals::local_player.pointer + offsets::m_lifeState);
				globals::local_player.origin = memory->read<vec3>(globals::local_player.pointer + offsets::m_vecOrigin);

				for (int i = 0; i < 64; i++) {
					DWORD entity = memory->read<DWORD>(modules::client.base + offsets::dwEntityList + i * 0x10);

					if (!entity)
						continue;

					globals::enemies[i] = entity;
				}

				static bool init = false;
				if (!init) {
					init = true;
					globals::glow_object_manager = memory->read<DWORD>(modules::client.base + offsets::dwGlowObjectManager);
				}
			}
		}

		chams::run();
		glow::run();
		radar::run();
		triggerbot::run();
		bhop::run();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	data::should_continue = false;
}

void threads::menu_thread() {
	menu::run();
}

void threads::run() {
	std::thread main_thread(threads::main_thread);
	std::thread menu_thread(threads::menu_thread);

	if (!main_thread.joinable()) {
		MessageBox(NULL, L"cant join main thread", L"error", MB_OK);
		return;
	}

	if (!menu_thread.joinable()) {
		MessageBox(NULL, L"cant join menu thread", L"error", MB_OK);
		return;
	}

	main_thread.join();
	menu_thread.join();
}