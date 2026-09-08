#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "srb_first.h"
#include "srb_second.h"
#include "srb_vojvodina.h"
#include "srb_east.h"
#include "srb_west.h"
#include "srb_belgrade.h"
#include "srb_cup.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

vtable* srb_rules_vtable = new vtable((BYTE*)0x969394, 0x34);

DWORD srb_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 15;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 3;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	srb_first_init(pMem, *current_year, get_comp(SRB_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	srb_second_init(pMem, *current_year, get_comp(SRB_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		srb_vojvodina_init(pMem, *current_year, get_comp(SRB_VOJVODINA_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xEE);
		srb_belgrade_init(pMem, *current_year, get_comp(SRB_BELGRADE_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xEE);
		srb_east_init(pMem, *current_year, get_comp(SRB_EAST_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xEE);
		srb_west_init(pMem, *current_year, get_comp(SRB_WEST_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	srb_cup_init(pMem, *current_year, get_comp(SRB_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_serbia_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_SERBIA_9CF();
	*((BYTE*)(_this + 0x5)) = RulesSerbia;
	*((BYTE*)(_this + 0x1F)) = RulesSerbia;
	return _this;
}

void srb_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 4;
	if (comp) {
		if (comp->ClubCompID == SRB_SECOND_9CF()) max_fgn = 2;
		else if (comp->ClubCompID == SRB_VOJVODINA_9CF() || comp->ClubCompID == SRB_BELGRADE_9CF() || comp->ClubCompID == SRB_EAST_9CF() || comp->ClubCompID == SRB_WEST_9CF()) max_fgn = 1;
	}
	*((BYTE*)(fgn_rule_arr + 0x5)) = max_fgn;
}

void __declspec(naked) srb_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call srb_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_serbia_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)srb_rules_vtable->vtable_ptr;
	srb_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)srb_foreign_rules_c);
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 2;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 18;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 15;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 13;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_srb_nation() {
	setup_srb_first();
	setup_srb_second();
	setup_srb_vojvodina();
	setup_srb_east();
	setup_srb_west();
	setup_srb_belgrade();
	setup_srb_cup();
}