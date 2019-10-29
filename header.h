#pragma once

//Excluir itens raramente usados dos cabe�alhos do Windows:
#define WIN32_LEAN_AND_MEAN     

//Define a plataforma Windows mais alta dispon�vel:
#include <SDKDDKVer.h>			
    
// Cabe�alhos do Windows:
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <string>
#include <TlHelp32.h>
#include <random>
#include <sstream>
#include <fstream>
#include <io.h>
#include <iostream>
#include <algorithm>
#include <future>

// Cabe�alhos do Programa:
#include "var.h"
#include "memory.h"
