#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fin_premier.h"
#include "fin_first.h"
#include "fin_second.h"
#include "fin_third.h"
#include "fin_cup.h"
#include "fin_league_cup.h"
#include "fin_awards.h"

static DWORD(__thiscall* fin_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x592250);

DWORD fin_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
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
	// Veikkausliiga
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	fin_premier_init(pMem, start_year, get_comp(FIN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkösliiga
	pMem = (BYTE*)cm0102_new(0xEE);
	fin_first_init(pMem, start_year, get_comp(FIN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ykkönen
	pMem = (BYTE*)cm0102_new(0xEE);
	fin_second_init(pMem, start_year, get_comp(FIN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Kakkonen
		pMem = (BYTE*)cm0102_new(0xEE);
		fin_third_init(pMem, start_year, get_comp(FIN_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	fin_cup_setup(pMem, start_year, get_comp(FIN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)cm0102_new(0xF6);
	fin_league_cup_init(pMem, start_year, get_comp(FIN_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 0;
	nation_data->super_cup = 0;
	return 1;
}

void setup_fin_nation()
{
	setup_fin_premier();
	setup_fin_first();
	setup_fin_second();
	setup_fin_third();
	setup_fin_cup();
	setup_fin_league_cup();
	setup_fin_awards();

	WriteNOP(0x592322, 7);
}

void finland_restructure() {
	cm3_club_comps* d3 = get_comp(FIN_THIRD_9CF());
	vector<cm3_clubs*> d3_a = find_clubs_of_comp(FIN_THIRD_A_9CF());
	for (cm3_clubs* club : d3_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_b = find_clubs_of_comp(FIN_THIRD_B_9CF());
	for (cm3_clubs* club : d3_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
	vector<cm3_clubs*> d3_c = find_clubs_of_comp(FIN_THIRD_C_9CF());
	for (cm3_clubs* club : d3_c) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d3;
	}
}