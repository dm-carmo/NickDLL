#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "den_premier.h"
#include "den_first.h"
#include "den_second.h"
#include "den_third.h"
#include "den_cup.h"
#include "den_awards.h"
#include <Structures/vtable.h>

DWORD* den_rules_vtable = (DWORD*)0x969860;

DWORD den_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 14;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 6;
	
	nation_data->contract_end_day = 14;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Superliga
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	den_premier_init(pMem, *current_year, get_comp(DEN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 1
	pMem = (BYTE*)cm0102_new(0xEE);
	den_first_init(pMem, *current_year, get_comp(DEN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 2
	pMem = (BYTE*)cm0102_new(0xEE);
	den_second_init(pMem, *current_year, get_comp(DEN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 3
	pMem = (BYTE*)cm0102_new(0xEE);
	den_third_init(pMem, *current_year, get_comp(DEN_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	den_cup_init(pMem, *current_year, get_comp(DEN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void den_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
}

void __declspec(naked) den_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call den_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_denmark_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)den_rules_vtable;
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
	windows[window_id].end_day = 2;
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
	windows[window_id].end_day = 2;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_den_nation()
{
	setup_den_premier();
	setup_den_first();
	setup_den_second();
	setup_den_third();
	setup_den_cup();
	setup_den_awards();

	WriteVTablePtr(den_rules_vtable, VTableR5, 0x8e8560);
	WriteVTablePtr(den_rules_vtable, VTableRForeignRules, (DWORD)den_foreign_rules_c);
	WriteVTablePtr(den_rules_vtable, VTableRLoanOutsideWindow, 0x412dd0);
}