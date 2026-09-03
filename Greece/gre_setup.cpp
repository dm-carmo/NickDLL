#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "gre_first.h"
#include "gre_second.h"
#include "gre_cup.h"
#include "gre_super.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* gre_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5ec040);

DWORD gre_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 10;
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
	// Super League
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	gre_first_init(pMem, *current_year, get_comp(GRE_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super League 2
	pMem = (BYTE*)cm0102_new(0xEE);
	gre_second_init(pMem, *current_year, get_comp(GRE_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	gre_cup_init(pMem, *current_year, get_comp(GRE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)cm0102_new(0xB2);
	gre_super_setup(pMem, *current_year, get_comp(GRE_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(GRE_SUPER_CUP_9CF());
	return 1;
}

void setup_gre_nation() {
	setup_gre_first();
	setup_gre_second();
	setup_gre_cup();
	setup_gre_super();
}

void greece_restructure() {
	cm3_club_comps* d2 = get_comp(GRE_SECOND_9CF());
	vector<cm3_clubs*> d2_n = find_clubs_of_comp(GRE_SECOND_NORTH_9CF());
	for (cm3_clubs* club : d2_n) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
	vector<cm3_clubs*> d2_s = find_clubs_of_comp(GRE_SECOND_SOUTH_9CF());
	for (cm3_clubs* club : d2_s) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d2;
	}
}