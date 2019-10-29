#include "header.h"

struct mem {

	HANDLE ProcessHandle;
	DWORD Client;
	DWORD Engine;
	

	struct MemFuncoes {

		HANDLE GetProcessHandle(std::wstring ProcessName);
		DWORD GetModuleAddress(std::wstring ModuleName, HANDLE Process);
		bool Attach();
		void Detach();
		bool ProcessActive();

		template <typename ReadType> void Read(ReadType* Buffer, DWORD Address) {
			if (ProcessActive()) {
				ReadProcessMemory(Mem.ProcessHandle, (LPVOID)(Address), Buffer, sizeof(ReadType), 0);
			}
		}

		template <typename WriteType> void Write(WriteType* Data, DWORD Address) {
			if (ProcessActive()) {
				WriteProcessMemory(Mem.ProcessHandle, (LPVOID)(Address), Data, sizeof(WriteType), 0);
			}
		}
	}
	Functions;

};

extern mem Mem;