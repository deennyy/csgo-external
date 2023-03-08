#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>
#include <tchar.h>

#include "data.h"

#include <dwmapi.h>

#include "esp.h"
#include "aimbot.h"

namespace menu {
	void run();

	extern float chamscolor[3];
	extern float chamsbright;
	extern float glowcolor[4];
	extern float boxespcol[4];
	extern float nameespcol[4];
	extern float weaponespcol[4];
	extern float smooth;
	extern float rcs;
	extern float hpespcol[4];

	extern bool should_write;
};