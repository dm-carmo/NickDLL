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
#include <Helpers\9cf_constants.h>

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

void setup_tur_nation() {
	setup_tur_first();
	setup_tur_second();
	setup_tur_third();
	setup_tur_fourth();
	setup_tur_cup();
	setup_tur_super();
	//setup_tur_awards();

	WriteNOP(0x8fc482, 7);

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
	vector<cm3_clubs*> d4_4 = find_clubs_of_comp(TUR_FOURTH_G4_9CF());
	for (cm3_clubs* club : d4_4) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4;
	}
}