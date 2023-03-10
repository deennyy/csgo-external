#pragma once

#include "menu.h"
#include "cheat.h"

namespace esp {
	void box(ImDrawList* draw_list, DWORD entity);
	void name(ImDrawList* draw_list, DWORD entity);
	void weapon(ImDrawList* draw_list, DWORD entity);
	void health(ImDrawList* draw_list, DWORD entity);
	
	void run(ImDrawList* draw_list);

	extern vec3 head, feet;
	extern float width, height, dist;
}