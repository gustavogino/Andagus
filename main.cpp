#include "header.h"

mem Mem;
VarGlobal Global;

DWORD WINAPI Bhop(LPVOID PARAMS) {

	while (Global.Funcoes.BhopAtivo) {
		// Chama a função do BunnyHop
		Sleep(1);
	}
	return 0;
}


DWORD WINAPI Main(LPVOID PARAMS) {
	MessageBoxW(NULL, L"A injeção foi um sucesso!.", L"Andagus", MB_OK);
	Global.Funcoes.BhopAtivo = false;

	while (!Mem.Functions.Attach()) { 
		Sleep(200); // Aguarda até que consiga Handle do processo
	}

	CreateThread(0, 0, &Bhop, 0, 0, 0);

	while (!Global.Finalizar) {

		if (GetAsyncKeyState(VK_END) < 0) {
			Beep(300, 200);
			Global.Finalizar = true;			
		}
		
		if (GetAsyncKeyState(VK_F1) < 0) {		
			Beep(400, 200);
			Global.Funcoes.BhopAtivo = !Global.Funcoes.BhopAtivo;
		}

		if (!Mem.Functions.ProcessActive()) {
			Mem.Functions.Detach(); // Se o processo não estiver ativo, fecha a Handle
		}

		Sleep(100);
	}

	Mem.Functions.Detach();
	MessageBoxW(NULL, L"Andagus finalizado!", L"Andagus", MB_OK);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(0, 0, &Main, 0, 0, 0);
		}
	}
	return TRUE;
}