#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "por_first.h"
#include "por_second.h"
#include "por_third.h"
#include "por_fourth.h"
#include "por_cup.h"
#include "por_league_cup.h"
#include "por_super.h"
#include "por_awards.h"
#include <Structures/vtable.h>

DWORD* por_rules_vtable = (DWORD*)0x96E9C0;

DWORD por_setup_c(playable_nation_data* nation_data) {
	
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
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Liga 1
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	por_first_init(pMem, *current_year, get_comp(POR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 2
	pMem = (BYTE*)cm0102_new(0xEE);
	por_second_init(pMem, *current_year, get_comp(POR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 3
	pMem = (BYTE*)cm0102_new(0xEE);
	por_third_init(pMem, *current_year, get_comp(POR_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Campeonato de Portugal
		pMem = (BYTE*)cm0102_new(0xEE);
		por_fourth_init(pMem, *current_year, get_comp(POR_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	por_cup_init(pMem, *current_year, get_comp(POR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	por_league_cup_init(pMem, *current_year, get_comp(POR_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	por_super_init(pMem, *current_year, get_comp(POR_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(POR_SUPER_CUP_9CF());
	return 1;
}

void por_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
}

void __declspec(naked) por_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call por_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_portugal_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)por_rules_vtable;
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
	windows[window_id].end_day = 4;
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
	windows[window_id].end_day = 3;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_por_nation()
{
	setup_por_first();
	setup_por_second();
	setup_por_third();
	setup_por_fourth();
	setup_por_cup();
	setup_por_league_cup();
	setup_por_super();
	setup_por_awards();

	WriteVTablePtr(por_rules_vtable, VTableRForeignRules, (DWORD)por_foreign_rules_c);
	WriteVTablePtr(por_rules_vtable, VTableRLoanOutsideWindow, 0x412dd0);
	WriteVTablePtr(por_rules_vtable, VTableRLoanLength, 0x90f1a0);
}

void portugal_restructure() {
	cm3_club_comps* l3 = get_comp(POR_THIRD_9CF());
	vector<cm3_clubs*> l3_a = find_clubs_of_comp(POR_THIRD_A_9CF());
	for (cm3_clubs* club : l3_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = l3;
	}
	vector<cm3_clubs*> l3_b = find_clubs_of_comp(POR_THIRD_B_9CF());
	for (cm3_clubs* club : l3_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = l3;
	}
	cm3_club_comps* cdp = get_comp(POR_FOURTH_9CF());
	vector<cm3_clubs*> cdp_a = find_clubs_of_comp(POR_FOURTH_A_9CF());
	for (cm3_clubs* club : cdp_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_b = find_clubs_of_comp(POR_FOURTH_B_9CF());
	for (cm3_clubs* club : cdp_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_c = find_clubs_of_comp(POR_FOURTH_C_9CF());
	for (cm3_clubs* club : cdp_c) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_d = find_clubs_of_comp(POR_FOURTH_D_9CF());
	for (cm3_clubs* club : cdp_d) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
}