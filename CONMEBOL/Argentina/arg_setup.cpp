#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\9cf_constants.h"
#include "arg_first.h"
#include "arg_second.h"
#include "arg_third_metro.h"
#include "arg_third_interior.h"
#include "arg_cup.h"
#include "arg_champ_cup.h"
#include "arg_super.h"
#include "Structures\vtable.h"

DWORD* arg_rules_vtable = (DWORD*)0x9674A0;

DWORD arg_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 6;

	nation_data->contract_end_day = 15;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xF6);
	arg_first_init(pMem, start_year, get_comp(ARG_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	arg_second_init(pMem, start_year, get_comp(ARG_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		arg_third_metro_init(pMem, start_year, get_comp(ARG_THIRD_METRO_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xF2);
		arg_third_interior_init(pMem, start_year, get_comp(ARG_THIRD_INTERIOR_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_cup_init(pMem, start_year, get_comp(ARG_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_champ_cup_init(pMem, start_year, get_comp(ARG_CHAMPIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_super_init(pMem, start_year, get_comp(ARG_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ARG_SUPER_CUP_9CF());
	return 1;
}

void arg_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	*((BYTE*)(fgn_rule_arr + 0x2)) = 5;
}

void __declspec(naked) arg_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call arg_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_argentina_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)arg_rules_vtable;
	*((BYTE*)(_this + 0x13)) = 6; // maximum number of foreign players at the club
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 14;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 10;
	windows[window_id].end_month = March;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 9;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 2;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_arg_nation() {
	setup_arg_first();
	setup_arg_second();
	setup_arg_third_metro();
	setup_arg_third_interior();
	setup_arg_cup();
	setup_arg_champ_cup();
	setup_arg_super();

	WriteVTablePtr(arg_rules_vtable, VTableRLoanOutsideWindow, 0x412dd0);
	WriteVTablePtr(arg_rules_vtable, VTableRForeignRules, (DWORD)arg_foreign_rules_c);
	WriteVTablePtr(arg_rules_vtable, VTableRLoanLength, 0x90f1a0);
}