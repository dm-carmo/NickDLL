#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\9cf_constants.h"
#include "irl_premier.h"
#include "irl_first.h"
#include "irl_second.h"
#include "irl_cup.h"
#include "irl_presidents.h"
#include "irl_awards.h"
#include "Structures\vtable.h"

DWORD* irl_rules_vtable = (DWORD*)0x96C190;

DWORD irl_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = February;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 6;
	
	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	irl_premier_init(pMem, start_year, get_comp(IRL_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	irl_first_init(pMem, start_year, get_comp(IRL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF2);
	irl_second_init(pMem, start_year, get_comp(IRL_NATIONAL_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	irl_cup_init(pMem, start_year, get_comp(IRL_CHALLENGE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	irl_presidents_init(pMem, start_year, get_comp(IRL_PRESIDENTS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(IRL_PRESIDENTS_CUP_9CF());
	return 1;
}

void irl_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	*((BYTE*)(fgn_rule_arr + 0x5)) = 4;
}

void __declspec(naked) irl_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call irl_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_ireland_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)irl_rules_vtable;
	//*((BYTE*)(_this + 0x12)) = 4; // maximum number of non-EU players at the club, not working
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
	windows[window_id].start_month = December;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 22;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 28;
	windows[window_id].end_month = July;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_irl_nation() {
	setup_irl_premier();
	setup_irl_first();
	setup_irl_second();
	setup_irl_cup();
	setup_irl_presidents();
	setup_irl_awards();

	WriteVTablePtr(irl_rules_vtable, VTableRForeignRules, (DWORD)irl_foreign_rules_c);
}