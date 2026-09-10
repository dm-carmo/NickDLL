#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\9cf_constants.h"
#include "fra_first.h"
#include "fra_second.h"
#include "fra_third.h"
#include "fra_cup.h"
#include "fra_super.h"
#include "Structures\vtable.h"

DWORD* fra_rules_vtable = (DWORD*)0x96AE48;

DWORD fra_setup_c(playable_nation_data* nation_data) {
	nation_data->contract_start_day = 4;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;
	// Ligue 1
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	fra_first_init(pMem, *current_year, get_comp(FRA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ligue 2
	pMem = (BYTE*)cm0102_new(0xEE);
	fra_second_init(pMem, *current_year, get_comp(FRA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// National
	pMem = (BYTE*)cm0102_new(0xEE);
	fra_third_init(pMem, *current_year, get_comp(FRA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	fra_cup_init(pMem, *current_year, get_comp(FRA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	fra_super_init(pMem, *current_year, get_comp(FRA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(FRA_SUPER_CUP_9CF());
	return 1;
}

void fra_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 4;
	if (comp) {
		if (comp->ClubCompID == FRA_THIRD_9CF()) max_fgn = 3;
	}
	*((BYTE*)(fgn_rule_arr + 0x5)) = max_fgn;
}

void __declspec(naked) fra_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call fra_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_france_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)fra_rules_vtable;
	//*((BYTE*)(_this + 0x12)) = 4; // maximum number of non-UE players at the club, not working
	BYTE num_of_windows = 3;
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
	windows[window_id].end_day = 1;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 2;
	windows[window_id].start_month = September;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 31;
	windows[window_id].end_month = December;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_fra_nation()
{
	setup_fra_first();
	setup_fra_second();
	setup_fra_third();
	setup_fra_cup();
	setup_fra_super();

	WriteVTablePtr(fra_rules_vtable, VTableRForeignRules, (DWORD)fra_foreign_rules_c);
}