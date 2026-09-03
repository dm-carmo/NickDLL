#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "uefa_champions_league.h"
#include "uefa_europa_league.h"
#include "uefa_conference_league.h"
#include "uefa_super_cup.h"
#include <Helpers/constants.h>

static DWORD(__thiscall* uefa_super_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x57A100);

DWORD uefa_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 23;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = -1;

	nation_data->contract_end_day = 20;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year;
	nation_data->contract_end_day_of_week = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xB2);
	uefa_champions_league_init(pMem, *current_year, get_comp(UEFA_CHAMPIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB6);
	uefa_europa_league_init(pMem, *current_year, get_comp(UEFA_EUROPA_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB6);
	uefa_conference_league_init(pMem, *current_year, get_comp(UEFA_CONFERENCE_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	uefa_super_cup_setup(pMem, *current_year, get_comp(UEFA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 21, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_uefa_continent() {
	char* ucl = "Champions League";
	char* uel = "Europa League";
	WriteDWORD(0x494EA6 + 1, (DWORD)&ucl[0]);
	WriteDWORD(0x494E92 + 1, (DWORD)&uel[0]);
	WriteDWORD(0x494F0D, 0x9CF6F0);
	char* ucl_abbrev = "UCL";
	char* uel_abbrev = "UEL";
	char* uecl_abbrev = "UECL";
	WriteDWORD(0x49C884 + 1, (DWORD)&ucl_abbrev[0]);
	WriteDWORD(0x49C8DE + 1, (DWORD)&uel_abbrev[0]);
	WriteDWORD(0x49C93C + 1, (DWORD)&uecl_abbrev[0]);
	WriteDWORD(0x49C94C, 0x9CF6EC);
	WriteDWORD(0x633777, 0x9CF6EC);
	WriteBytes(0x782ED5, 1, 0xeb);
	WriteBytes(0x77FD94, 6, 0xE9, 0x1C, 0x01, 0x00, 0x00, 0x90);
	WriteBytes(0x77FEB8, 6, 0xE9, 0xF9, 0x00, 0x00, 0x00, 0x90);
	WriteDWORD(0x85AA1A, 0x9CF6EC);
	WriteDWORD(0x904ECB, 0x9CF6EC);
	WriteDWORD(0x904F69, 0x9CF6EC);
	WriteDWORD(0x90503F, 0x9CF6EC);
	WriteDWORD(0x906190, 0x9CF6EC);
	WriteDWORD(0x90609C, 0x9CF6EC);
	// to show all teams in the groups drawn news
	WriteBytes(0x684253 + 2, 1, 0x9);

	setup_uefa_champions_league();
	setup_uefa_europa_league();
	setup_uefa_conference_league();
	setup_uefa_super_cup();

	// others
	WriteBytes(0x58334a, 2, 0x74, 0x17);
	WriteBytes(0x847af6, 1, 0xeb);
	WriteWORD(0x847b03 + 3, 500);
	WriteNOP(0x85b2e9, 2);

	WriteDWORD(0x85b306 + 1, (DWORD)&register_msg1[0]);
	WriteDWORD(0x85b336 + 1, (DWORD)&register_msg2[0]);
	WriteDWORD(0x85b348 + 1, (DWORD)&register_msg3[0]);

	char* champions_path = "Champions Path";
	char* champions_path_short = "C.Path";
	WriteDWORD(0x4B6903 + 1, (DWORD)&champions_path[0]);
	WriteDWORD(0x4B9489 + 1, (DWORD)&champions_path_short[0]);
	char* league_path = "League Path";
	char* league_path_short = "L.Path";
	WriteDWORD(0x4B691D + 1, (DWORD)&league_path[0]);
	WriteDWORD(0x4B94A3 + 1, (DWORD)&league_path_short[0]);
	char* main_path = "Main Path";
	char* main_path_short = "M.Path";
	WriteDWORD(0x4B6298 + 1, (DWORD)&main_path[0]);
	WriteDWORD(0x4B8D85 + 1, (DWORD)&main_path_short[0]);
	WriteDWORD(0x4beacc, 0x4bb38b);
	char* knockout_text = "Knockout Phase Playoff";
	char* knockout_text_short = "KO Playoff";
	WriteDWORD(0x4B586a + 1, (DWORD)&knockout_text[0]);
	WriteDWORD(0x4B86f6 + 1, (DWORD)&knockout_text_short[0]);
	char* knockout_text_l1 = "Knockout Phase Playoff First Leg";
	char* knockout_text_l1_short = "KO Playoff Leg 1";
	WriteDWORD(0x4B5884 + 1, (DWORD)&knockout_text_l1[0]);
	WriteDWORD(0x4B8700 + 1, (DWORD)&knockout_text_l1_short[0]);
	char* knockout_text_l2 = "Knockout Phase Playoff Second Leg";
	char* knockout_text_l2_short = "KO Playoff Leg 2";
	WriteDWORD(0x4B589e + 1, (DWORD)&knockout_text_l2[0]);
	WriteDWORD(0x4B870a + 1, (DWORD)&knockout_text_l2_short[0]);
	char* league_phase_text = "League Phase";
	char* league_phase_text_short = "Lge Phase";
	WriteDWORD(0x4B59A2 + 1, (DWORD)&league_phase_text[0]);
	WriteDWORD(0x4B876E + 1, (DWORD)&league_phase_text_short[0]);
}