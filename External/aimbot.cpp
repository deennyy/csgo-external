#include "aimbot.h"

void aimbot::run() {
	if (!globals::local_player.pointer)
		return;

	vec3 viewoffset = memory->read<vec3>(globals::local_player.pointer + offsets::m_vecViewOffset);
	vec3 eyeangles = viewoffset + globals::local_player.origin;

	qangle viewangles = memory->read<qangle>(globals::client_state + offsets::dwClientState_ViewAngles);
	qangle punchangles = memory->read<qangle>(globals::local_player.pointer + offsets::m_aimPunchAngle);

	for (int i = 0; i < 64; i++) {
		if (!globals::enemies[i])
			continue;

		int entityteam = memory->read<int>(globals::enemies[i] + offsets::m_iTeamNum);
		int entityhealth = memory->read<int>(globals::enemies[i] + offsets::m_iHealth);
		bool entitydormant = memory->read<bool>(globals::enemies[i] + offsets::m_bDormant);
		BYTE entitylifestate = memory->read<BYTE>(globals::enemies[i] + offsets::m_lifeState);
		int entityclassid = memory->read<int>(memory->read<int>(memory->read<int>(memory->read<int>(globals::enemies[i] + 0x8) + 0x8) + 0x1) + 0x14);
		bool entityimmunity = memory->read<bool>(globals::enemies[i] + offsets::m_bGunGameImmunity);

		if (entityteam == globals::local_player.team || entityhealth <= 0 || entitydormant || entitylifestate != 0 || entityclassid != 40 || entityimmunity)
			continue;

		DWORD bonematrix_address = memory->read<DWORD>(globals::enemies[i] + offsets::m_dwBoneMatrix);
		matrix3x4 bonematrix = memory->read<matrix3x4>(bonematrix_address + 0x30 * 8);

		vec3 head(bonematrix.matrix[0][3], bonematrix.matrix[1][3], bonematrix.matrix[2][3]);

		vec3 delta = head - eyeangles;

		qangle angles = ((qangle(atan2(-delta.z, hypot(delta.x, delta.y) * 180.0f / M_PI), atan2(delta.y, delta.x) * (180.0f / M_PI), 0.f) - (viewangles + (punchangles * menu::rcs))) / menu::smooth) + viewangles;
		qangle fov_angles = (qangle(atan2(-delta.z, hypot(delta.x, delta.y) * 180.0f / M_PI), atan2(delta.y, delta.x) * (180.0f / M_PI), 0.f) - (viewangles + (punchangles)));

		const auto fov = std::hypot(fov_angles.pitch, fov_angles.yaw);

		if (GetAsyncKeyState(VK_LBUTTON) && fov < menu::aimbotfov) {
			cheat::clamp_angles(angles);
			memory->write<qangle>(globals::client_state + offsets::dwClientState_ViewAngles, angles);
		}
	}
}