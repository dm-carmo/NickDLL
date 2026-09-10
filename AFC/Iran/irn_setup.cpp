#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "irn_first.h"
#include "irn_second.h"
#include "irn_cup.h"
#include "irn_super.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

vtable* irn_rules_vtable = new vtable((BYTE*)0x96F340, 0x34);

DWORD irn_setup_c(playable_nation_data* nation_data) {
	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	irn_first_init(pMem, *current_year, get_comp(IRN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	irn_second_init(pMem, *current_year, get_comp(IRN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	irn_cup_init(pMem, *current_year, get_comp(IRN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	irn_super_init(pMem, *current_year, get_comp(IRN_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(IRN_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_iran_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_IRAN_9CF();
	*((BYTE*)(_this + 0x5)) = RulesIran;
	*((BYTE*)(_this + 0x1F)) = RulesIran;
	return _this;
}

void irn_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 8;
	if (comp) {
		if (comp->ClubCompID == IRN_SECOND_9CF()) max_fgn = 4;
	}
	*((BYTE*)(fgn_rule_arr + 0x2)) = max_fgn;
}

void __declspec(naked) irn_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irn_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_iran_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)irn_rules_vtable->vtable_ptr;
	*((BYTE*)(_this + 0x13)) = 8; // maximum number of foreign players at the club
	irn_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)irn_foreign_rules_c);
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 21;
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 26;
	windows[window_id].end_month = August;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 20;
	windows[window_id].start_month = December;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 25;
	windows[window_id].end_month = January;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_irn_nation() {
	setup_irn_first();
	setup_irn_second();
	setup_irn_cup();
	setup_irn_super();
}