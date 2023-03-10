#pragma once

#include "data.h"
#include "glow.h"
#include "chams.h"
#include "triggerbot.h"
#include "menu.h"
#include "bhop.h"
#include "radar.h"

namespace threads {
	void main_thread();
	void menu_thread();

	void run();
}