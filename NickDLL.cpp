#pragma warning (disable : 4786)  // Stops all the weird STL warnings
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <set>
#include <algorithm>

#include "CMHeader.h"
#include "Helper.h"
#include "concacaf.h"
#include "sudamericana.h"
#include "libertadores.h"
#include "libertadores_calendar.h"
#include "inject_club_renames.h"
//#include "european_cup.h"

using namespace std;

void Setup()
{
	srand((unsigned int)time(NULL));

#ifdef _DEBUG
	szDebugFile = "c:\\nicklog.txt";
	DeleteFile(szDebugFile);

	// All the below is just to force the console window visible in x64dbg
	if (!AttachConsole(ATTACH_PARENT_PROCESS))
		AllocConsole();
	HWND hCon = GetConsoleWindow();
	if (hCon)
	{
		ShowWindow(hCon, SW_SHOW);
		SetForegroundWindow(hCon);
	}

	freopen("CONOUT$", "w", stdout);
	dprintf("Hello Out There!\n");

	// Ignore Player Histories On Load for quick loading while debugging
	WriteBytes(0x7C02A1, 5, 0xe9, 0x30, 0xa, 0, 0, 90);

	// Allow multiple CM0102 instances
	//WriteBytes(0x68D3B6, 1, 0xEB);

	// Disable splash screen
	WriteBytes(0x5CCD3C, 6, 0xe9, 0x72, 0x03, 0x00, 0x00, 0x90);
#endif 

	setup_name_injection();

	configFile.LoadConfig("NickDLL_config.json");

	if (configFile.GetBool("applyLibertadores", true)) {
		dprintf("Applying Libertadores changes\n");
		setup_libertadores();
		setup_libertadores_calendar();
	}

	if (configFile.GetBool("applySudamericana", true)) {
		dprintf("Applying Sudamericana changes\n");
		setup_sudamericana();
	}

	if (configFile.GetBool("applyConcacafCup", true)) {
		dprintf("Applying CONCACAF Champions Cup changes\n");
		setup_concacaf();
	}
	//setup_european_cup();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Setup();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

