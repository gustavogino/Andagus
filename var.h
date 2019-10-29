#include "header.h"

struct VarGlobal
{
    VarGlobal();
    struct
    {
        DWORD EntitySize = 0x10;
    } Offsets;

	struct 
	{
		bool BhopAtivo;
	} Funcoes;

    struct
    {
        std::wstring ProcessName;
        std::wstring ClientModule;
        std::wstring EngineModule;
    } Infos;

	bool Finalizar;    
};

extern VarGlobal Global;