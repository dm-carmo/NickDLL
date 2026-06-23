#pragma warning (disable : 4786 4996 6031)  // Stops all the weird STL warnings

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
#include "Helpers\generic_functions.h"
#include "Helpers\Helper.h"
#include "Helpers\YearChanger.h"

#include "inject_9cf_rename.h"
#include "setup_misc_functions.h"
#include <leagues_setup.h>
#include <currency.h>
#include <discipline_setup.h>
#include <rules_setup.h>

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
		SetConsoleOutputCP(65001); // CP_UTF8
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

	// See any team's finances
	WriteBytes(0x46066F, 4, 0xb8, 0x01, 0x00, 0x00);
	WriteBytes(0x4608EA, 4, 0xb8, 0x01, 0x00, 0x00);

	// Manage any team
	WriteNOP(0x482a74, 6);
	WriteNOP(0x46A357, 5);
	WriteBytes(0x482C9E, 19, 0x8b, 0x74, 0x24, 0x1c, 0x36, 0x8b, 0x86, 0xcf, 0x00, 0x00, 0x00, 0x85, 0xc0, 0x75, 0x57, 0xeb, 0x09, 0x90, 0x90);
	WriteBytes(0x482CB6, 2, 0x74, 0x4c);
	WriteBytes(0x5448aa, 2, 0x00, 0x75);
#endif 

	bool result = configFile.LoadConfig("NickDLL_config.json");
	result = prizeMoneyFile.LoadConfig("NickDLL_prize_money.json");

	dprintf("Applying Argentina changes\n");
	setup_arg_nation();
	dprintf("Applying Australia changes\n");
	setup_aus_nation();
	dprintf("Applying Belgium changes\n");
	setup_bel_nation();
	dprintf("Applying Brazil changes\n");
	setup_bra_nation();
	dprintf("Applying Croatia changes\n");
	setup_cro_nation();
	dprintf("Applying Denmark changes\n");
	setup_den_nation();
	dprintf("Applying England changes\n");
	setup_eng_nation();
	dprintf("Applying Finland changes\n");
	setup_fin_nation();
	dprintf("Applying France changes\n");
	setup_fra_nation();
	dprintf("Applying Germany changes\n");
	setup_ger_nation();
	dprintf("Applying Greece changes\n");
	setup_gre_nation();
	dprintf("Applying Holland changes\n");
	setup_hol_nation();
	dprintf("Applying Ireland changes\n");
	setup_irl_nation();
	dprintf("Applying Italy changes\n");
	setup_ita_nation();
	dprintf("Applying Japan changes\n");
	setup_jpn_nation();
	dprintf("Applying Northern Ireland changes\n");
	setup_nir_nation();
	dprintf("Applying Norway changes\n");
	setup_nor_nation();
	dprintf("Applying Poland changes\n");
	setup_pol_nation();
	dprintf("Applying Portugal changes\n");
	setup_por_nation();
	dprintf("Applying Russia changes\n");
	setup_rus_nation();
	dprintf("Applying Scotland changes\n");
	setup_sco_nation();
	dprintf("Applying South Korea changes\n");
	setup_kor_nation();
	dprintf("Applying Spain changes\n");
	setup_spa_nation();
	dprintf("Applying Sweden changes\n");
	setup_swe_nation();
	dprintf("Applying Turkey changes\n");
	setup_tur_nation();
	dprintf("Applying USA changes\n");
	setup_usa_nation();
	dprintf("Applying Wales changes\n");
	setup_wal_nation();

	dprintf("------------------------------\n");
	dprintf("New nation: Austria\n");
	setup_aut_nation();
	dprintf("New nation: Chile\n");
	setup_chi_nation();
	dprintf("New nation: Czech Republic\n");
	setup_cze_nation();
	dprintf("New nation: Egypt\n");
	setup_egy_nation();
	dprintf("New nation: Saudi Arabia\n");
	setup_ksa_nation();
	dprintf("New nation: Switzerland\n");
	setup_sui_nation();
	dprintf("------------------------------\n");

	dprintf("Applying FIFA changes (club comps)\n");
	setup_fifa_club_comps();
	dprintf("Applying AFC changes\n");
	setup_afc_continent();
	dprintf("Applying CAF changes\n");
	setup_caf_continent();
	dprintf("Applying CONCACAF changes\n");
	setup_concacaf_continent();
	dprintf("Applying CONMEBOL changes\n");
	setup_conmebol_continent();
	dprintf("Applying OFC changes\n");
	setup_ofc_continent();
	dprintf("Applying UEFA changes\n");
	setup_uefa_continent();

	dprintf("------------------------------\n");

	setup_name_injection();
	setup_misc_functions();
	setup_currency();

	setup_leagues_setup();
	setup_discipline_setup();
	setup_rules_setup();
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

