#include "header.h"

HANDLE mem::MemFuncoes::GetProcessHandle(std::wstring ProcessName) {
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE SnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (Process32First(SnapHandle, &ProcessEntry) == TRUE) {
		if (!_wcsicmp(ProcessEntry.szExeFile, ProcessName.c_str())) {
			HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
			return ProcessHandle;
		}
		else {
			while (Process32Next(SnapHandle, &ProcessEntry) == TRUE) {
				if (!_wcsicmp(ProcessEntry.szExeFile, ProcessName.c_str())) {
					HANDLE ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessEntry.th32ProcessID);
					return ProcessHandle;
				}
			}
		}
	}
	CloseHandle(SnapHandle);
	return 0;
}

DWORD mem::MemFuncoes::GetModuleAddress(std::wstring ModuleName, HANDLE Process) {
	MODULEENTRY32 ModuleEntry;
	ModuleEntry.dwSize = sizeof(MODULEENTRY32);
	HANDLE SnapHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetProcessId(Process));
	if (Module32First(SnapHandle, &ModuleEntry) == TRUE) {
		if (!_wcsicmp(ModuleEntry.szModule, ModuleName.c_str())) {
			DWORD ModuleAddress = (DWORD)ModuleEntry.modBaseAddr;
			return ModuleAddress;
		}
		else {
			while (Module32Next(SnapHandle, &ModuleEntry) == TRUE) {
				if (!_wcsicmp(ModuleEntry.szModule, ModuleName.c_str())) {
					DWORD ModuleAddress = (DWORD)ModuleEntry.modBaseAddr;
					return ModuleAddress;
				}
			}
		}
	}
	CloseHandle(SnapHandle);
	return 0;
}

bool mem::MemFuncoes::ProcessActive() {
	DWORD ExitCode;
	GetExitCodeProcess(Mem.ProcessHandle, &ExitCode);
	if (ExitCode == STILL_ACTIVE) {
		return true;
	}
	return false;
}

bool mem::MemFuncoes::Attach() {
	Mem.ProcessHandle = GetProcessHandle(Global.Infos.ProcessName);
	if (Mem.ProcessHandle) {
		Mem.Client = GetModuleAddress(Global.Infos.ClientModule, Mem.ProcessHandle);
		Mem.Engine = GetModuleAddress(Global.Infos.EngineModule, Mem.ProcessHandle);
		if (Mem.Client && Mem.Engine) {
			return true;
		}
	}
	else {
		return false;
	}
}

void mem::MemFuncoes::Detach() {
	if (Mem.ProcessHandle) {
		CloseHandle(Mem.ProcessHandle);
	}
}