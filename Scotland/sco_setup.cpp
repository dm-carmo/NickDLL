#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "sco_premier.h"
#include "sco_champ.h"
#include "sco_league_1.h"
#include "sco_league_2.h"
#include "sco_highland.h"
#include "sco_lowland.h"
#include "sco_pyramid_playoff.h"
#include "sco_cup.h"
#include "sco_league_cup.h"
#include "sco_challenge_cup.h"
#include <Helpers\9cf_constants.h>
#include <Structures/vtable.h>

DWORD* sco_rules_vtable = (DWORD*)0x96F838;

DWORD sco_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 7;
	}
	else {
		nation_data->num_of_comps = 10;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	sco_premier_init(pMem, *current_year, get_comp(SCO_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_champ_init(pMem, *current_year, get_comp(SCO_CHAMP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_league_1_init(pMem, *current_year, get_comp(SCO_LEAGUE_1_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_league_2_init(pMem, *current_year, get_comp(SCO_LEAGUE_2_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		sco_highland_init(pMem, *current_year, get_comp(SCO_HIGHLAND_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xF2);
		sco_lowland_init(pMem, *current_year, get_comp(SCO_LOWLAND_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xEE);
		sco_pyramid_playoff_init(pMem, *current_year, get_comp(SCO_PYRAMID_PLAYOFF_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	sco_cup_init(pMem, *current_year, get_comp(SCO_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	sco_league_cup_init(pMem, *current_year, get_comp(SCO_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	sco_challenge_cup_init(pMem, *current_year, get_comp(SCO_CHALLENGE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void sco_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
}

void __declspec(naked) sco_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sco_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_scotland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)sco_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 15;
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 3;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 5;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 4;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_sco_nation() {
	setup_sco_premier();
	setup_sco_champ();
	setup_sco_league_1();
	setup_sco_league_2();
	setup_sco_highland();
	setup_sco_lowland();
	setup_sco_pyramid_playoff();
	setup_sco_cup();
	setup_sco_league_cup();
	setup_sco_challenge_cup();

	WriteVTablePtr(sco_rules_vtable, VTableRForeignRules, (DWORD)sco_foreign_rules_c);
}