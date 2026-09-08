#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "rus_premier.h"
#include "rus_first.h"
#include "rus_second_a.h"
#include "rus_cup.h"
#include "rus_super.h"
#include "rus_awards.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

DWORD* rus_rules_vtable = (DWORD*)0x96F340;

DWORD rus_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	rus_premier_init(pMem, *current_year, get_comp(RUS_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	rus_first_init(pMem, *current_year, get_comp(RUS_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	rus_second_a_init(pMem, *current_year, get_comp(RUS_SECOND_A_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	rus_cup_init(pMem, *current_year, get_comp(RUS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	rus_super_init(pMem, *current_year, get_comp(RUS_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(RUS_SUPER_CUP_9CF());
	return 1;
}

void rus_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 8;
	if (comp) {
		if (comp->ClubCompID == RUS_FIRST_9CF()) max_fgn = 4;
		else if (comp->ClubCompID == RUS_SECOND_A_9CF()) max_fgn = 0;
	}
	*((BYTE*)(fgn_rule_arr + 0x2)) = max_fgn;
}

void __declspec(naked) rus_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call rus_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_russia_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)rus_rules_vtable;
	*((BYTE*)(_this + 0x13)) = 10; // maximum number of foreign players at the club
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 18;
	windows[window_id].start_month = July;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 10;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 23;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 19;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_rus_nation() {
	setup_rus_premier();
	setup_rus_first();
	setup_rus_second_a();
	setup_rus_cup();
	setup_rus_super();
	setup_rus_awards();

	WriteVTablePtr(rus_rules_vtable, VTableRForeignRules, (DWORD)rus_foreign_rules_c);
}

void russia_restructure() {
	cm3_club_comps* d2 = get_comp(RUS_SECOND_A_9CF());
	vector<cm3_clubs*> d2_g = find_clubs_of_comp(RUS_SECOND_A_GOLD_9CF());
	for (cm3_clubs* club : d2_g) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
	vector<cm3_clubs*> d2_s = find_clubs_of_comp(RUS_SECOND_A_SILVER_9CF());
	for (cm3_clubs* club : d2_s) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
}