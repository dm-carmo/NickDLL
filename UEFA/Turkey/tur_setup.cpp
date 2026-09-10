#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "tur_first.h"
#include "tur_second.h"
#include "tur_third.h"
#include "tur_fourth.h"
#include "tur_cup.h"
#include "tur_super.h"
//#include "tur_awards.h"
#include "Helpers\9cf_constants.h"
#include "Structures\vtable.h"

DWORD* tur_rules_vtable = (DWORD*)0x97075C;

DWORD tur_setup_c(playable_nation_data* nation_data) {
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 6;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	tur_first_init(pMem, *current_year, get_comp(TUR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	tur_second_init(pMem, *current_year, get_comp(TUR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	tur_third_init(pMem, *current_year, get_comp(TUR_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		tur_fourth_init(pMem, *current_year, get_comp(TUR_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	tur_cup_init(pMem, *current_year, get_comp(TUR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	tur_super_init(pMem, *current_year, get_comp(TUR_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(TUR_SUPER_CUP_9CF());
	return 1;
}

void tur_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
	BYTE max_fgn = 14;
	if (comp) {
		if (comp->ClubCompID == TUR_SECOND_9CF()) max_fgn = 8;
		else if (comp->ClubCompID == TUR_THIRD_9CF() || comp->ClubCompID == TUR_FOURTH_9CF()) max_fgn = 0;
	}
	*((BYTE*)(fgn_rule_arr + 0x2)) = max_fgn;
}

void __declspec(naked) tur_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call tur_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_turkey_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)tur_rules_vtable;
	*((BYTE*)(_this + 0x13)) = 14; // maximum number of foreign players at the club
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
	windows[window_id].start_month = June;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 4;
	windows[window_id].end_month = September;
	windows[window_id].is_start_2 = 0;
	window_id++;

	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 1;
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 5;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_tur_nation() {
	setup_tur_first();
	setup_tur_second();
	setup_tur_third();
	setup_tur_fourth();
	setup_tur_cup();
	setup_tur_super();
	//setup_tur_awards();

	WriteVTablePtr(tur_rules_vtable, VTableRForeignRules, (DWORD)tur_foreign_rules_c);

	// foreign player limits
	WriteBytes(0x90220e, 1, 14);
	WriteBytes(0x902230, 1, 0);
	WriteBytes(0x902238, 1, 6);
	WriteDWORD(0x9021eb, 0x9CF8E0); // 2.Lig
	WriteDWORD(0x9021f5, 0x9CF8CC); // 3.Lig
	WriteDWORD(0x9021fd, 0x9CF8DC); // 1.Lig
}

void turkey_restructure() {
	cm3_club_comps* d3 = get_comp(TUR_THIRD_9CF());
	vector<cm3_clubs*> d3_1 = find_clubs_of_comp(TUR_THIRD_G1_9CF());
	for (cm3_clubs* club : d3_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_2 = find_clubs_of_comp(TUR_THIRD_G2_9CF());
	for (cm3_clubs* club : d3_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	cm3_club_comps* d4 = get_comp(TUR_FOURTH_9CF());
	vector<cm3_clubs*> d4_1 = find_clubs_of_comp(TUR_FOURTH_G1_9CF());
	for (cm3_clubs* club : d4_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_2 = find_clubs_of_comp(TUR_FOURTH_G2_9CF());
	for (cm3_clubs* club : d4_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_3 = find_clubs_of_comp(TUR_FOURTH_G3_9CF());
	for (cm3_clubs* club : d4_3) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
}