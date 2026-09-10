#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "sui_premier.h"
#include "sui_first.h"
#include "sui_second.h"
#include "sui_cup.h"
#include "lie_cup.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

vtable* sui_rules_vtable = new vtable((BYTE*)0x96B3CC, 0x34);

DWORD sui_setup_c(playable_nation_data* nation_data) {
	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	sui_premier_init(pMem, *current_year, get_comp(SUI_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	 pMem = (BYTE*)cm0102_new(0xEE);
	sui_first_init(pMem, *current_year, get_comp(SUI_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sui_second_init(pMem, *current_year, get_comp(SUI_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	sui_cup_init(pMem, *current_year, get_comp(SUI_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	lie_cup_init(pMem, *current_year, get_comp(LIE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_switzerland_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_SWITZERLAND_9CF();
	*((BYTE*)(_this + 0x5)) = RulesSwitzerland;
	*((BYTE*)(_this + 0x1F)) = RulesSwitzerland;
	return _this;
}

void sui_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 5;
	if (comp) {
		if (comp->ClubCompID == SUI_FIRST_9CF() || comp->ClubCompID == SUI_SECOND_9CF()) max_fgn = 3;
	}
	*((BYTE*)(fgn_rule_arr + 0x5)) = max_fgn;
}

void __declspec(naked) sui_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call sui_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_switzerland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)sui_rules_vtable->vtable_ptr;
	//*((BYTE*)(_this + 0x12)) = 10; // maximum number of non-EU players at the club, not working
	sui_rules_vtable->SetPointer(VTableRLoanOutsideWindow, 0x412dd0);
	sui_rules_vtable->SetPointer(VTableRSendWindowNews, 0x8e9080);
	sui_rules_vtable->SetPointer(VTableR5, 0x8e8560);
	sui_rules_vtable->SetPointer(VTableRLoanRules, 0x40a610);
	sui_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)sui_foreign_rules_c);
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = Tuesday;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = Tuesday;
	windows[window_id].end_day = 8;
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
	windows[window_id].end_day = 15;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_sui_nation() {
	setup_sui_premier();
	setup_sui_first();
	setup_sui_second();
	setup_sui_cup();
	setup_lie_cup();
}