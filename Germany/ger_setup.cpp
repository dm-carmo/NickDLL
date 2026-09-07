#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ger_first.h"
#include "ger_second.h"
#include "ger_third.h"
#include "ger_regional.h"
#include "ger_cup.h"
#include "ger_super.h"
#include "ger_awards.h"
#include <Helpers\9cf_constants.h>
#include <Structures/vtable.h>

DWORD* ger_rules_vtable = (DWORD*)0x96B3CC;

DWORD ger_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 21;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 6;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Bundesliga
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	ger_first_init(pMem, *current_year, get_comp(GER_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2. Bundesliga
	pMem = (BYTE*)cm0102_new(0xEE);
	ger_second_init(pMem, *current_year, get_comp(GER_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 3. Liga
	pMem = (BYTE*)cm0102_new(0xEE);
	ger_third_init(pMem, *current_year, get_comp(GER_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Regionalliga
		pMem = (BYTE*)cm0102_new(0xEE);
		ger_regional_init(pMem, *current_year, get_comp(GER_REGIONAL_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	ger_cup_init(pMem, *current_year, get_comp(GER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)cm0102_new(0xB2);
	ger_super_init(pMem, *current_year, get_comp(GER_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(GER_SUPER_CUP_9CF());
	return 1;
}

void ger_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	if (comp) {
		if (comp->ClubCompID == GER_THIRD_9CF()) *((BYTE*)(fgn_rule_arr + 0x5)) = 3;
		else if (comp->ClubCompID == GER_REGIONAL_9CF()) *((BYTE*)(fgn_rule_arr + 0x5)) = 0;
	}
}

void __declspec(naked) ger_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ger_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_germany_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)ger_rules_vtable;
	*((BYTE*)(_this + 0x12)) = 38; // maximum number of non-EU players at the club
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_ger_nation()
{
	setup_ger_first();
	setup_ger_second();
	setup_ger_third();
	setup_ger_regional();
	setup_ger_cup();
	setup_ger_super();
	setup_ger_awards();

	WriteVTablePtr(ger_rules_vtable, VTableRForeignRules, (DWORD)ger_foreign_rules_c);
	WriteVTablePtr(ger_rules_vtable, VTableRLoanOutsideWindow, 0x412dd0);
}

void germany_restructure() {
	cm3_club_comps* regional = get_comp(GER_REGIONAL_9CF());
	vector<cm3_clubs*> reg_n = find_clubs_of_comp(GER_REGIONAL_NORTH_9CF());
	for (cm3_clubs* club : reg_n) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_ne = find_clubs_of_comp(GER_REGIONAL_NORTHEAST_9CF());
	for (cm3_clubs* club : reg_ne) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_sw = find_clubs_of_comp(GER_REGIONAL_SOUTHWEST_9CF());
	for (cm3_clubs* club : reg_sw) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_w = find_clubs_of_comp(GER_REGIONAL_WEST_9CF());
	for (cm3_clubs* club : reg_w) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_bay = find_clubs_of_comp(GER_REGIONAL_BAYERN_9CF());
	for (cm3_clubs* club : reg_bay) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
}