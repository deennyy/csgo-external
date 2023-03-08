#include "memory.h"
#include "data.h"
#include "threads.h"
#include "cheat.h"

c_memory* memory;

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	FreeConsole();

	memory = new c_memory(data::game_name);

	cheat::startup();

	threads::run();

	cheat::shutdown();

	delete memory;

	return EXIT_SUCCESS;
}