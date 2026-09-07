#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "ita_ser_a.h"
#include "ita_ser_b.h"
#include "ita_ser_c.h"
#include "ita_cup.h"
#include "ita_super.h"
#include "ita_c_cup.h"
#include "ita_c_supercup.h"
#include "ita_awards.h"
#include <Structures/vtable.h>

DWORD* ita_rules_vtable = (DWORD*)0x96C96C;

DWORD ita_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 6;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 6;
	
	nation_data->contract_end_day = 8;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 7;
	}
	else { // C2 selected, not used for now
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Serie A
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	ita_ser_a_init(pMem, *current_year, get_comp(ITA_SERIE_A_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Serie B
	pMem = (BYTE*)cm0102_new(0xEE);
	ita_ser_b_init(pMem, *current_year, get_comp(ITA_SERIE_B_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Serie C
	pMem = (BYTE*)cm0102_new(0xEE);
	ita_ser_c_init(pMem, *current_year, get_comp(ITA_SERIE_C_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// not used for now
	}
	// Coppa Italia
	pMem = (BYTE*)cm0102_new(0xB2);
	ita_cup_init(pMem, *current_year, get_comp(ITA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Italia
	pMem = (BYTE*)cm0102_new(0xB2);
	ita_super_init(pMem, *current_year, get_comp(ITA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Coppa Serie C
	pMem = (BYTE*)cm0102_new(0xB2);
	ita_c_cup_init(pMem, *current_year, get_comp(ITA_SERIE_C_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercoppa Serie C
	pMem = (BYTE*)cm0102_new(0xEE);
	ita_c_supercup_init(pMem, *current_year, get_comp(ITA_C1_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ITA_SUPER_CUP_9CF());
	return 1;
}

void ita_foreign_rules(BYTE* _this, cm3_club_comps* comp, BYTE* fgn_rule_arr) {
	memset(fgn_rule_arr, -1, 42);
}

void __declspec(naked) ita_foreign_rules_c()
{
	__asm
	{
		mov eax, esp
		push dword ptr[eax + 0x8]
		push dword ptr[eax + 0x4]
		push ecx
		call ita_foreign_rules
		add esp, 0xc
		ret 8
	}
}

BYTE* setup_italy_rules(BYTE* _this, char idx, DWORD country_id, DWORD continent_id, int a5, int a6) {
	generic_rules_setup(_this, idx, country_id, continent_id, a5, a6);
	*((DWORD*)(_this)) = (DWORD)ita_rules_vtable;
	BYTE num_of_windows = 2;
	*((BYTE*)(_this + 0x8)) = num_of_windows;
	BYTE* wMem = (BYTE*)cm0102_malloc(num_of_windows * 12);
	transfer_window* windows = (transfer_window*)wMem;
	*((DWORD*)(_this + 0x4)) = (DWORD)wMem;

	BYTE window_id = 0;
	windows[window_id].idx_1 = windows[window_id].idx_2 = idx;
	windows[window_id].window_num_1 = windows[window_id].window_num_2 = window_id;
	windows[window_id].start_day_of_week = -1;
	windows[window_id].start_day = 29;
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
	windows[window_id].start_month = January;
	windows[window_id].is_start_1 = 1;
	windows[window_id].end_day_of_week = -1;
	windows[window_id].end_day = 1;
	windows[window_id].end_month = February;
	windows[window_id].is_start_2 = 0;

	return _this;
}

void setup_ita_nation() {
	setup_ita_ser_a();
	setup_ita_ser_b();
	setup_ita_ser_c();
	setup_ita_cup();
	setup_ita_super();
	setup_ita_c_cup();
	setup_ita_c_supercup();
	setup_ita_awards();

	WriteVTablePtr(ita_rules_vtable, VTableRForeignRules, (DWORD)ita_foreign_rules_c);
	// more loans allowed
	WriteBytes(0x6618a4, 1, 9);
	WriteDWORD(0x6618ba, 0x9C44D4);

	WriteDWORD(0x661803, 0x9CF908);
	WriteDWORD(0x66180D, 0x9CF908);
	WriteDWORD(0x66180D, 0x9CF908);
	WriteDWORD(0x661815, 0x9CF908);
	WriteDWORD(0x66181D, 0x9CF908);
	WriteDWORD(0x661825, 0x9CF908);
}

void italy_restructure() {
	cm3_club_comps* ser_c = get_comp(ITA_SERIE_C_9CF());
	vector<cm3_clubs*> ser_c_a = find_clubs_of_comp(ITA_SERIE_C_A_9CF());
	for (cm3_clubs* club : ser_c_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = ser_c;
	}
	vector<cm3_clubs*> ser_c_b = find_clubs_of_comp(ITA_SERIE_C_B_9CF());
	for (cm3_clubs* club : ser_c_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = ser_c;
	}
	vector<cm3_clubs*> ser_c_c = find_clubs_of_comp(ITA_SERIE_C_C_9CF());
	for (cm3_clubs* club : ser_c_c) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = ser_c;
	}
}