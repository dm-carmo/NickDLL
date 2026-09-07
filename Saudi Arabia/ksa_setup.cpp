#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ksa_premier.h"
#include "ksa_first.h"
#include "ksa_cup.h"
#include "ksa_super.h"
#include <Helpers\9cf_constants.h>
#include "Structures\vtable.h"

vtable* ksa_rules_vtable = new vtable((BYTE*)0x96F340, 0x34);

DWORD ksa_setup_c(playable_nation_data* nation_data) {

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
	ksa_premier_init(pMem, *current_year, get_comp(KSA_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	ksa_first_init(pMem, *current_year, get_comp(KSA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	ksa_cup_init(pMem, *current_year, get_comp(KSA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	ksa_super_init(pMem, *current_year, get_comp(KSA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(KSA_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_saudi_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_SAUDI_ARABIA_9CF();
	*((BYTE*)(_this + 0x5)) = RulesSaudi;
	*((BYTE*)(_this + 0x1F)) = RulesSaudi;
	return _this;
}

void ksa_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	if (comp) {
		if (comp->ClubCompID == KSA_PREMIER_9CF()) *((BYTE*)(fgn_rule_arr + 0x2)) = 8;
		else if (comp->ClubCompID == KSA_FIRST_9CF()) *((BYTE*)(fgn_rule_arr + 0x2)) = 4;
	}
}

void __declspec(naked) ksa_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ksa_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_saudi_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)ksa_rules_vtable->vtable_ptr;
	*((BYTE*)(_this + 0x13)) = 10; // maximum number of foreign players at the club
	ksa_rules_vtable->SetPointer(VTableRForeignRules, (DWORD)ksa_foreign_rules_c);
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 22;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 6;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 3;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 31;
	windows[window_id].end_month = January;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_ksa_nation() {
	setup_ksa_premier();
	setup_ksa_first();
	setup_ksa_cup();
	setup_ksa_super();
}