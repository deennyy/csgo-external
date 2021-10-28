#include "memory.h"
#include "data.h"
#include "threads.h"
#include "cheat.h"

c_memory* memory;

int main() {
	FreeConsole();

	memory = new c_memory(data::game_name);

	if (!data::shoud_continue) {
		delete memory;
		return EXIT_FAILURE;
	}

	cheat::startup();

	threads::run();

	cheat::shutdown();
	delete memory;

	return EXIT_SUCCESS;
}