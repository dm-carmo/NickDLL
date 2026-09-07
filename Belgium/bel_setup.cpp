#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bel_first.h"
#include "bel_second.h"
#include "bel_third_vv.h"
#include "bel_third_ac.h"
#include "bel_fourth_vv.h"
#include "bel_fourth_ac.h"
#include "bel_cup.h"
#include "bel_super.h"
#include "bel_awards.h"
#include <Structures/vtable.h>

DWORD* bel_rules_vtable = (DWORD*)0x967C10;

DWORD bel_setup_c(playable_nation_data* nation_data) {

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
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 8;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	bel_first_init(pMem, *current_year, get_comp(BEL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_second_init(pMem, *current_year, get_comp(BEL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_third_vv_init(pMem, *current_year, get_comp(BEL_THIRD_VV_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_third_ac_init(pMem, *current_year, get_comp(BEL_THIRD_ACFF_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0x104);
		bel_fourth_vv_init(pMem, *current_year, get_comp(BEL_FOURTH_VV_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xF2);
		bel_fourth_ac_init(pMem, *current_year, get_comp(BEL_FOURTH_ACFF_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	bel_cup_init(pMem, *current_year, get_comp(BEL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	bel_super_init(pMem, *current_year, get_comp(BEL_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BEL_SUPER_CUP_9CF());
	return 1;
}

void bel_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
}

void __declspec(naked) bel_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call bel_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_belgium_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)bel_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 16;
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
	windows[window_id].end_day = 2;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_bel_nation() {
	setup_bel_first();
	setup_bel_second();
	setup_bel_third_vv();
	setup_bel_third_ac();
	setup_bel_fourth_vv();
	setup_bel_fourth_ac();
	setup_bel_cup();
	setup_bel_super();
	setup_bel_awards();

	WriteVTablePtr(bel_rules_vtable, VTableR5, 0x8e8560);
	WriteVTablePtr(bel_rules_vtable, VTableRForeignRules, (DWORD)bel_foreign_rules_c);
}

void belgium_restructure() {
	cm3_club_comps* d4_vv = get_comp(BEL_FOURTH_VV_9CF());
	vector<cm3_clubs*> d4_vv_a = find_clubs_of_comp(BEL_FOURTH_VV_A_9CF());
	for (cm3_clubs* club : d4_vv_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4_vv;
	}
	vector<cm3_clubs*> d4_vv_b = find_clubs_of_comp(BEL_FOURTH_VV_B_9CF());
	for (cm3_clubs* club : d4_vv_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4_vv;
	}
}