#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "spa_first.h"
#include "spa_second.h"
#include "spa_third.h"
#include "spa_fourth.h"
#include "spa_cup.h"
#include "spa_super.h"
#include <Structures/vtable.h>

DWORD* spa_rules_vtable = (DWORD*)0x96FDEC;

DWORD spa_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 6;

	nation_data->contract_end_day = 10;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 6;
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

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	spa_first_init(pMem, *current_year, get_comp(SPA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	spa_second_init(pMem, *current_year, get_comp(SPA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	spa_third_init(pMem, *current_year, get_comp(SPA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		spa_fourth_init(pMem, *current_year, get_comp(SPA_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	spa_cup_init(pMem, *current_year, get_comp(SPA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	spa_super_init(pMem, *current_year, get_comp(SPA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(SPA_SUPER_CUP_9CF());
	return 1;
}

void spa_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 2;
	if (comp) {
		if (comp->ClubCompID == SPA_FIRST_9CF() || comp->ClubCompID == SPA_CUP_9CF() || comp->ClubCompID == SPA_SUPER_CUP_9CF()) max_fgn = 3;
	}
	*((BYTE*)(fgn_rule_arr + 0x5)) = max_fgn;
}

void __declspec(naked) spa_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call spa_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_spain_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)spa_rules_vtable;
	*((BYTE*)(_this + 0x12)) = 3; // maximum number of non-EU players at the club
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
	windows[window_id].start_day = 2;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 2;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_spa_nation()
{
	setup_spa_first();
	setup_spa_second();
	setup_spa_third();
	setup_spa_fourth();
	setup_spa_cup();
	setup_spa_super();

	WriteVTablePtr(spa_rules_vtable, VTableRForeignRules, (DWORD)spa_foreign_rules_c);
}

void spain_restructure() {
	cm3_club_comps* d3 = get_comp(SPA_THIRD_9CF());
	vector<cm3_clubs*> d3_1 = find_clubs_of_comp(SPA_THIRD_G1_9CF());
	for (cm3_clubs* club : d3_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_2 = find_clubs_of_comp(SPA_THIRD_G2_9CF());
	for (cm3_clubs* club : d3_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	cm3_club_comps* d4 = get_comp(SPA_FOURTH_9CF());
	vector<cm3_clubs*> d4_1 = find_clubs_of_comp(SPA_FOURTH_G1_9CF());
	for (cm3_clubs* club : d4_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_2 = find_clubs_of_comp(SPA_FOURTH_G2_9CF());
	for (cm3_clubs* club : d4_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_3 = find_clubs_of_comp(SPA_FOURTH_G3_9CF());
	for (cm3_clubs* club : d4_3) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_4 = find_clubs_of_comp(SPA_FOURTH_G4_9CF());
	for (cm3_clubs* club : d4_4) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_5 = find_clubs_of_comp(SPA_FOURTH_G5_9CF());
	for (cm3_clubs* club : d4_5) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
}