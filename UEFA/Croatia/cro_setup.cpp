#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cro_first.h"
#include "cro_second.h"
#include "cro_third.h"
#include "cro_cup.h"
#include "cro_super.h"
#include "cro_awards.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

DWORD* cro_rules_vtable = (DWORD*)0x969394;

DWORD cro_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	cro_first_init(pMem, *current_year, get_comp(CRO_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)cm0102_new(0xEE);
	cro_second_init(pMem, *current_year, get_comp(CRO_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)cm0102_new(0xEE);
	cro_third_init(pMem, *current_year, get_comp(CRO_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	cro_cup_init(pMem, *current_year, get_comp(CRO_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)cm0102_new(0xB2);
	cro_super_init(pMem, *current_year, get_comp(CRO_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(CRO_SUPER_CUP_9CF());
	return 1;
}

void cro_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 6;
	if (comp) {
		if (comp->ClubCompID == CRO_SECOND_9CF()) max_fgn = 3;
		else if (comp->ClubCompID == CRO_THIRD_9CF()) max_fgn = 2;
	}
	*((BYTE*)(fgn_rule_arr + 0x5)) = max_fgn;
}

void __declspec(naked) cro_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call cro_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_croatia_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)cro_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 27;
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 7;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 10;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 17;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_cro_nation() {
	setup_cro_first();
	setup_cro_second();
	setup_cro_third();
	setup_cro_cup();
	setup_cro_super();
	setup_cro_awards();

	WriteVTablePtr(cro_rules_vtable, VTableRForeignRules, (DWORD)cro_foreign_rules_c);
}