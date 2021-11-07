#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <cstdio>
#include "data.h"

#define in_range(x, a, b) (x >= a && x <= b)
#define get_bits(x) (in_range(x, '0', '9') ? (x - '0') : ((x & (~0x20)) - 'A' + 0xa))
#define get_byte(x) (get_bits(x[0]) << 4 | get_bits(x[1]))

class c_memory {
public:
	c_memory(LPCWSTR game_name) {
		if (!get_window_handle(game_name)) {
			MessageBox(NULL, L"failed to open handle", L"error", MB_OK);
			data::should_continue = false;
		}

		if (data::should_continue && !get_process_id()) {
			MessageBox(NULL, L"failed to get pid", L"error", MB_OK);
			data::should_continue = false;
		}

		if (data::should_continue && !open_process()) {
			MessageBox(NULL, L"failed to open process", L"error", MB_OK);
			data::should_continue = false;
		}
	}

	~c_memory() {
		CloseHandle(handle);
	}

	s_module get_module(LPCWSTR module_name) {
		s_module mod = { NULL, NULL };
		if (!data::should_continue)
			return mod;

		s_module temp = get_module_info(module_name);

		if (!temp.base) {
			wchar_t buffer[64];
			swprintf_s(buffer, L"failed getting %s", module_name);
			MessageBox(NULL, buffer, L"error", MB_OK);
			data::should_continue = false;
			return mod;
		}

		return temp;
	}

	template <class T>
	T read(DWORD address) {
		T buffer;
		ReadProcessMemory(handle, (LPCVOID)address, &buffer, sizeof(buffer), 0);
		return buffer;
	}

	template <class T>
	void write(DWORD address, T value) {
		WriteProcessMemory(handle, (LPVOID)address, &value, sizeof(value), 0);
	}

	// https://github.com/nbqofficial/nbqmemory
	DWORD pattern_scan(s_module mod, const wchar_t* pattern, int offset, int extra, bool relative, bool subtract) {
		DWORD address = 0;

		byte* data = new byte[mod.size];
		ReadProcessMemory(handle, (LPCVOID)mod.base, data, mod.size, NULL);

		for (DWORD i = 0x1000; i < mod.size; i++) {
			if (compare_memory((const byte*)(data + i), pattern)) {
				address = mod.base + i + offset;
				if (relative) { ReadProcessMemory(handle, LPCVOID(address), &address, sizeof(DWORD), NULL); }
				if (subtract) { address -= mod.base; }
				address += extra;
				break;
			}
		}

		delete[] data;
		return address;
	}

private:
	HWND get_window_handle(LPCWSTR window_name) {
		hwnd = FindWindow(NULL, window_name);
		return hwnd;
	}

	DWORD get_process_id() {
		GetWindowThreadProcessId(hwnd, &pid);
		return pid;
	}

	HANDLE open_process() {
		handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		return handle;
	}

	s_module get_module_info(LPCWSTR module_name) { // stolen from some 2017 uc thread
		if (EnumProcessModules(handle, module_array, sizeof(module_array), &cbNeeded)) {
			for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
				wchar_t _module_name[MAX_PATH];

				if (GetModuleBaseName(handle, module_array[i], _module_name, sizeof(_module_name) / sizeof(wchar_t))) {
					if (!wcscmp(_module_name, module_name)) {
						MODULEINFO modinfo;
						GetModuleInformation(handle, module_array[i], &modinfo, sizeof(modinfo));
						s_module mod = { (DWORD)module_array[i], modinfo.SizeOfImage };
						return mod;
					}
				}
			}
		}

		s_module mod = { NULL, NULL };
		return mod;
	}

	bool compare_memory(const byte* data, const wchar_t* pattern) {
		for (; *pattern; *pattern != ' ' ? ++data : data, ++pattern) {
			if (*pattern == ' ' || *pattern == '?') continue;
			if (*data != get_byte(pattern)) return false;
			++pattern;
		}

		return true;
	}

	HWND hwnd = NULL;
	DWORD pid = NULL;
	HMODULE module_array[1024];
	DWORD cbNeeded;
	HANDLE handle = NULL;
};

extern c_memory* memory;