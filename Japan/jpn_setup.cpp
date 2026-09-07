#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "jpn_first.h"
#include "jpn_second.h"
#include "jpn_third.h"
#include "jpn_jfl.h"
#include "jpn_cup.h"
#include "jpn_league_cup.h"
#include "jpn_super.h"
#include <Structures/vtable.h>

DWORD* jpn_rules_vtable = (DWORD*)0x96CCFC;

DWORD jpn_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 6;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 6;

	nation_data->contract_end_day = 8;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;
	// J1
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	jpn_first_init(pMem, *current_year, get_comp(JPN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// J2
	pMem = (BYTE*)cm0102_new(0xEE);
	jpn_second_init(pMem, *current_year, get_comp(JPN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// J3
	pMem = (BYTE*)cm0102_new(0xEE);
	jpn_third_init(pMem, *current_year, get_comp(JPN_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// JFL
		pMem = (BYTE*)cm0102_new(0xEE);
		jpn_jfl_init(pMem, *current_year, get_comp(JPN_JFL_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	jpn_cup_init(pMem, *current_year, get_comp(JPN_EMPEROR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	jpn_league_cup_init(pMem, *current_year, get_comp(JPN_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	jpn_super_init(pMem, *current_year, get_comp(JPN_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(JPN_SUPER_CUP_9CF());
	return 1;
}

void jpn_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 5;
	if (comp) {
		if (comp->ClubCompID == JPN_SECOND_9CF() || comp->ClubCompID == JPN_THIRD_9CF()) max_fgn = 4;
		else if (comp->ClubCompID == JPN_JFL_9CF()) max_fgn = 3;
	}
	*((BYTE*)(fgn_rule_arr + 0x2)) = max_fgn;
}

void __declspec(naked) jpn_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call jpn_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_japan_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)jpn_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 29;
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = Wednesday;
	windows[window_id].end_day = 16;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = February;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 3;
	windows[window_id].end_month = March;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_jpn_nation() {
	setup_jpn_first();
	setup_jpn_second();
	setup_jpn_third();
	setup_jpn_jfl();
	setup_jpn_cup();
	setup_jpn_league_cup();
	setup_jpn_super();

	WriteVTablePtr(jpn_rules_vtable, VTableRForeignRules, (DWORD)jpn_foreign_rules_c);
}