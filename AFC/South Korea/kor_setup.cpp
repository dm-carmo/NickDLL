#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "Helpers\9cf_constants.h"
#include "kor_first.h"
#include "kor_second.h"
#include "kor_cup.h"
#include "kor_super.h"
#include "kor_awards.h"
#include "Structures\vtable.h"

DWORD* kor_rules_vtable = (DWORD*)0x96CFEC;

DWORD kor_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = February;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 6;

	nation_data->contract_end_day = 20;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;
	// K1
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	kor_first_init(pMem, start_year, get_comp(KOR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// K2
	pMem = (BYTE*)cm0102_new(0xEE);
	kor_second_init(pMem, start_year, get_comp(KOR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	kor_cup_init(pMem, start_year, get_comp(KOR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	kor_super_init(pMem, start_year, get_comp(KOR_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(KOR_SUPER_CUP_9CF());
	return 1;
}

void kor_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 5;
	if (comp) {
		if (comp->ClubCompID == KOR_SECOND_9CF()) max_fgn = 4;
	}
	*((BYTE*)(fgn_rule_arr + 0x2)) = max_fgn;
}

void __declspec(naked) kor_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call kor_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_korea_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)kor_rules_vtable;
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
	windows[window_id].end_day = 27;
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
	windows[window_id].end_day = 19;
	windows[window_id].end_month = August;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_kor_nation() {
	setup_kor_first();
	setup_kor_second();
	setup_kor_cup();
	setup_kor_super();
	setup_kor_awards();

	// transfer windows
	WriteBytes(0x66e70a, 1, 15);
	WriteBytes(0x66e714, 1, 26);
	WriteBytes(0x66e720, 2, 9, July);
	WriteBytes(0x66e72a, 2, 19, August);

	WriteVTablePtr(kor_rules_vtable, VTableRLoanOutsideWindow, 0x412dd0);
	WriteVTablePtr(kor_rules_vtable, VTableRForeignRules, (DWORD)kor_foreign_rules_c);
}