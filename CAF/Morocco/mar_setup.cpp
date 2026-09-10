#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "mar_first.h"
#include "mar_second.h"
#include "mar_cup.h"
#include "mar_league_cup.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

vtable* mar_rules_vtable = new vtable((BYTE*)0x96CFEC, 0x34);

DWORD mar_setup_c(playable_nation_data* nation_data) {
	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 12;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	mar_first_init(pMem, *current_year, get_comp(MAR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	mar_second_init(pMem, *current_year, get_comp(MAR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	mar_cup_init(pMem, *current_year, get_comp(MAR_THRONE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	mar_league_cup_init(pMem, *current_year, get_comp(MAR_EXCELLENCE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_morocco_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_MOROCCO_9CF();
	*((BYTE*)(_this + 0x5)) = RulesMorocco;
	*((BYTE*)(_this + 0x1F)) = RulesMorocco;
	return _this;
}

void mar_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	if (comp && comp->ClubCompID == MAR_EXCELLENCE_CUP_9CF()) {
		*((BYTE*)(fgn_rule_arr + 0x16)) = 23;
		*((BYTE*)(fgn_rule_arr + 0x17)) = 10;
	}
	else *((BYTE*)(fgn_rule_arr + 0x2)) = 3;
}

void __declspec(naked) mar_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call mar_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_morocco_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)mar_rules_vtable->vtable_ptr;
	*((BYTE*)(_this + 0x13)) = 5; // maximum number of foreign players at the club
	mar_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)mar_foreign_rules_c);
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
	windows[window_id].end_day = 25;
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
	windows[window_id].end_day = 31;
	windows[window_id].end_month = January;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_mar_nation() {
	setup_mar_first();
	setup_mar_second();
	setup_mar_cup();
	setup_mar_league_cup();
}