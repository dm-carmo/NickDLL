#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "uru_first.h"
//#include "uru_second.h"
//#include "uru_cup.h"
//#include "uru_league_cup.h"
//#include "uru_super.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

vtable* uru_rules_vtable = new vtable((BYTE*)0x9674A0, 0x34);

DWORD uru_setup_c(playable_nation_data* nation_data) {
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
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xF2);
	uru_first_init(pMem, start_year, get_comp(URU_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)cm0102_new(0xF2);
	//uru_second_init(pMem, start_year, get_comp(URU_SECOND_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)cm0102_new(0xB2);
	//uru_cup_init(pMem, start_year, get_comp(URU_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)cm0102_new(0xB2);
	//uru_league_cup_init(pMem, start_year, get_comp(URU_LEAGUE_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)cm0102_new(0xB2);
	//uru_super_init(pMem, start_year, get_comp(URU_SUPER_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(URU_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_uruguay_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_URUGUAY_9CF();
	*((BYTE*)(_this + 0x5)) = RulesUruguay;
	*((BYTE*)(_this + 0x1F)) = RulesUruguay;
	return _this;
}

void uru_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	*((BYTE*)(fgn_rule_arr + 0x2)) = 5;
}

void __declspec(naked) uru_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call uru_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_uruguay_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)uru_rules_vtable->vtable_ptr;
	uru_rules_vtable->SetPointer(VTableRLoanOutsideWindow, 0x412dd0);
	uru_rules_vtable->SetPointer(VTableRLoanLength, 0x90f1a0);
	uru_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)uru_foreign_rules_c);
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
	windows[window_id].start_day = 1;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 25;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 8;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_uru_nation() {
	setup_uru_first();
	//setup_uru_second();
	//setup_uru_cup();
	//setup_uru_league_cup();
	//setup_uru_super();
}