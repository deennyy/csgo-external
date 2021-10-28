#pragma once

#include "memory.h"
#include "data.h"
#include "menu.h"

namespace glow {
	void run();
	void undo();

	extern bool toggle;
	extern bool should_write;
};