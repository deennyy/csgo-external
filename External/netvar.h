#pragma once

// this is completely skidded from https://www.unknowncheats.me/forum/counterstrike-global-offensive/342936-1337-external-netvars.html

#include <string>
#include "memory.h"

struct ghetto1 { // yes ik this is ghetto asf fight me
	char str[128];
};

struct ghetto2 {
	char str[128];
};

class NetvarsClass {
private:
	class RecvTable {
	public:
		std::string GetTableName() {
			DWORD offset = memory->read<DWORD>((DWORD)this + 0xC);
			ghetto1 ghetto = memory->read<ghetto1>(offset);
			return std::string(ghetto.str);
		}
		void* GetProperty(int i) { // RecvProp*
			return (void*)(memory->read<DWORD>((DWORD)this) + 0x3C * i);
		}
		int GetMaxProp() {
			return memory->read<int>((DWORD)this + 0x4);
		}
	};
	class ClientClass {
	public:
		void* GetTable() { // RecvTable*
			return memory->read<void*>((DWORD)this + 0xC);
		}
		void* GetNextClass() { // ClientClass*
			return memory->read<void*>((DWORD)this + 0x10);
		}
	};
	class RecvProp {
	public:
		std::string GetVarName() {
			DWORD offset = memory->read<DWORD>((DWORD)this);
			ghetto2 ghetto = memory->read<ghetto2>(offset);
			return std::string(ghetto.str);
		}
		int GetOffset() {
			return memory->read<int>((DWORD)this + 0x2C);
		}
		void* GetDataTable() { // RecvTable*
			return memory->read<void*>((DWORD)this + 0x28);
		}
	};
	DWORD CheckProps(RecvTable* DataTable, std::string NetVarName) {
		for (int i = 0; i < DataTable->GetMaxProp(); i++) {
			auto pRecvProp = reinterpret_cast<RecvProp*>(DataTable->GetProperty(i));
			auto VarName = pRecvProp->GetVarName();
			if (isdigit(VarName[0])) continue;
			if (NetVarName.compare(VarName) == 0) return pRecvProp->GetOffset();
			if (auto DataTable2 = reinterpret_cast<RecvTable*>(pRecvProp->GetDataTable()))
				if (auto Offset = CheckProps(DataTable2, NetVarName)) return Offset;
		}
		return NULL;
	}
	DWORD dwGetAllClasses;
public:
	NetvarsClass(DWORD Base) : dwGetAllClasses(Base) {}
	DWORD NETVAR(std::string ClassName, std::string NetVarName) {
		if (auto pClass = reinterpret_cast<ClientClass*>(dwGetAllClasses))
			for (; pClass != NULL; pClass = reinterpret_cast<ClientClass*>(pClass->GetNextClass()))
				if (auto Table = reinterpret_cast<RecvTable*>(pClass->GetTable()))
					if (Table->GetTableName().compare(ClassName) == 0)
						if (auto Offset = CheckProps(Table, NetVarName)) return Offset;
		return NULL;
	}
};