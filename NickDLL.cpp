#pragma warning (disable : 4786 4996)  // Stops all the weird STL warnings
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <vector>
#include <set>
#include <algorithm>

#include "Structures\CMHeader.h"
#include "Helpers\Helper.h"
#include "Helpers\YearChanger.h"

#include "CONCACAF\concacaf.h"
#include "CONMEBOL\sudamericana.h"
#include "CONMEBOL\libertadores.h"
#include "CONMEBOL\libertadores_calendar.h"

#include "inject_9cf_rename.h"
#include "setup_misc_functions.h"
#include <leagues_setup.h>

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

	// Increased exe speed for testing
	WriteDWORD(0x9472ce, 500);
#endif 

	// Fixes a slight bug where B-teams can't qualify for relegation playoffs if they have the "CantBePromoted" flag set
	WriteBytes(0x68527E, 1, 0xFC);

	// Shows more teams in Team Stats, up to 127
	WriteBytes(0x495976, 1, 0x7F);

	configFile.LoadConfig("NickDLL_config.json");

	if (configFile.GetBool("applyBrazil", true)) {
		dprintf("Applying Brazil changes\n");
		setup_bra_nation();
	}

	if (configFile.GetBool("applyCroatia", true)) {
		dprintf("Applying Croatia changes\n");
		setup_cro_nation();
	}

	if (configFile.GetBool("applyDenmark", true)) {
		dprintf("Applying Denmark changes\n");
		setup_den_nation();
	}

	if (configFile.GetBool("applyEngland", true)) {
		dprintf("Applying England changes\n");
		setup_eng_nation();
	}

	if (configFile.GetBool("applyFinland", true)) {
		dprintf("Applying Finland changes\n");
		setup_fin_nation();
	}

	if (configFile.GetBool("applyFrance", true)) {
		dprintf("Applying France changes\n");
		setup_fra_nation();
	}

	if (configFile.GetBool("applyGermany", true)) {
		dprintf("Applying Germany changes\n");
		setup_ger_nation();
	}
	else {
		setup_ger_awards_default();
	}

	if (configFile.GetBool("applyGreece", true)) {
		dprintf("Applying Greece changes\n");
		setup_gre_nation();
	}

	if (configFile.GetBool("applyHolland", true)) {
		dprintf("Applying Holland changes\n");
		setup_hol_nation();
	}

	if (configFile.GetBool("applyItaly", true)) {
		dprintf("Applying Italy changes\n");
		setup_ita_nation();
	}

	if (configFile.GetBool("applyJapan", true)) {
		dprintf("Applying Japan changes\n");
		setup_jpn_nation();
	}

	if (configFile.GetBool("applyNorway", true)) {
		dprintf("Applying Norway changes\n");
		setup_nor_nation();
	}

	if (configFile.GetBool("applyPoland", true)) {
		dprintf("Applying Poland changes\n");
		setup_pol_nation();
	}

	if (configFile.GetBool("applyPortugal", true)) {
		dprintf("Applying Portugal changes\n");
		setup_por_nation();
	}

	if (configFile.GetBool("applySouthKorea", true)) {
		dprintf("Applying South Korea changes\n");
		setup_kor_nation();
	}

	if (configFile.GetBool("applySweden", true)) {
		dprintf("Applying Sweden changes\n");
		setup_swe_nation();
	}

	if (configFile.GetBool("applyUSA", true)) {
		dprintf("Applying USA changes\n");
		setup_usa_nation();
	}

	if (configFile.GetBool("applyUEFA", true)) {
		dprintf("Applying UEFA changes\n");
		setup_uefa_continent();
	}

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

	setup_name_injection();
	setup_misc_functions();

	setup_leagues_setup();
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

