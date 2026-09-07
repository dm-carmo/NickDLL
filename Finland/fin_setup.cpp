#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fin_premier.h"
#include "fin_first.h"
#include "fin_second.h"
#include "fin_third.h"
#include "fin_cup.h"
#include "fin_league_cup.h"
#include "fin_awards.h"
#include <Structures/vtable.h>

DWORD* fin_rules_vtable = (DWORD*)0x96A75C;

DWORD fin_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
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
	// Veikkausliiga
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	fin_premier_init(pMem, start_year, get_comp(FIN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkösliiga
	pMem = (BYTE*)cm0102_new(0xEE);
	fin_first_init(pMem, start_year, get_comp(FIN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkönen
	pMem = (BYTE*)cm0102_new(0xEE);
	fin_second_init(pMem, start_year, get_comp(FIN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Kakkonen
		pMem = (BYTE*)cm0102_new(0xEE);
		fin_third_init(pMem, start_year, get_comp(FIN_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	fin_cup_init(pMem, start_year, get_comp(FIN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)cm0102_new(0xF6);
	fin_league_cup_init(pMem, start_year, get_comp(FIN_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void fin_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	*((BYTE*)(fgn_rule_arr + 0x5)) = 3;
}

void __declspec(naked) fin_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fin_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_finland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)fin_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 4;
	windows[window_id].start_month = February;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = April;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 29;
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 24;
	windows[window_id].end_month = August;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_fin_nation()
{
	setup_fin_premier();
	setup_fin_first();
	setup_fin_second();
	setup_fin_third();
	setup_fin_cup();
	setup_fin_league_cup();
	setup_fin_awards();

	WriteVTablePtr(fin_rules_vtable, VTableRForeignRules, (DWORD)fin_foreign_rules_c);
}

void finland_restructure() {
	cm3_club_comps* d3 = get_comp(FIN_THIRD_9CF());
	vector<cm3_clubs*> d3_a = find_clubs_of_comp(FIN_THIRD_A_9CF());
	for (cm3_clubs* club : d3_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_b = find_clubs_of_comp(FIN_THIRD_B_9CF());
	for (cm3_clubs* club : d3_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_c = find_clubs_of_comp(FIN_THIRD_C_9CF());
	for (cm3_clubs* club : d3_c) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
}