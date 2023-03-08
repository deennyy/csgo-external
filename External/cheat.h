#pragma once

#define NOMINMAX
#include <memory>
#include "data.h"
#include "chams.h"
#include "glow.h"
#include "netvar.h"
#include <cmath>
#include <algorithm>

namespace cheat {
	void startup();
	void shutdown();
	vec3 w2s(const vec3 pos);
	float normalize_angle(float ang);
	void clamp_angles(qangle angle);
	const char* weapon_id_to_str(int id);
};