#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "spa_first.h"
#include "spa_second.h"
#include "spa_third.h"
#include "spa_fourth.h"
#include "spa_cup.h"
#include "spa_super.h"

static DWORD(__thiscall* spa_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x8586B0);

DWORD spa_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 6;

	nation_data->contract_end_day = 10;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 6;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_first_init(pMem, *current_year, get_comp(SPA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_second_init(pMem, *current_year, get_comp(SPA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	spa_third_init(pMem, *current_year, get_comp(SPA_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		spa_fourth_init(pMem, *current_year, get_comp(SPA_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	spa_cup_init(pMem, *current_year, get_comp(SPA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	spa_super_setup(pMem, *current_year, get_comp(SPA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(SPA_SUPER_CUP_9CF());
	return 1;
}

void setup_spa_nation()
{
	setup_spa_first();
	setup_spa_second();
	setup_spa_third();
	setup_spa_fourth();
	setup_spa_cup();
	setup_spa_super();

	WriteNOP(0x84d036, 7);
	// disable offsets related to the inactive Spanish lower leagues
	WriteBytes(0x7E62FC, 1, 0xeb);
	WriteNOP(0x7e6f4a, 2);
	WriteNOP(0x4b070c, 2);
	WriteNOP(0x4c037d, 2);
	WriteNOP(0x4c03e0, 2);
}

void spain_restructure() {
	cm3_club_comps* d3 = get_comp(SPA_THIRD_9CF());
	vector<cm3_clubs*> d3_1 = find_clubs_of_comp(SPA_THIRD_G1_9CF());
	for (cm3_clubs* club : d3_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_2 = find_clubs_of_comp(SPA_THIRD_G2_9CF());
	for (cm3_clubs* club : d3_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	cm3_club_comps* d4 = get_comp(SPA_FOURTH_9CF());
	vector<cm3_clubs*> d4_1 = find_clubs_of_comp(SPA_FOURTH_G1_9CF());
	for (cm3_clubs* club : d4_1) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_2 = find_clubs_of_comp(SPA_FOURTH_G2_9CF());
	for (cm3_clubs* club : d4_2) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_3 = find_clubs_of_comp(SPA_FOURTH_G3_9CF());
	for (cm3_clubs* club : d4_3) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_4 = find_clubs_of_comp(SPA_FOURTH_G4_9CF());
	for (cm3_clubs* club : d4_4) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
	vector<cm3_clubs*> d4_5 = find_clubs_of_comp(SPA_FOURTH_G5_9CF());
	for (cm3_clubs* club : d4_5) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
}