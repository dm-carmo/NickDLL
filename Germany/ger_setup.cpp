#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ger_first.h"
#include "ger_second.h"
#include "ger_third.h"
#include "ger_regional.h"
#include "ger_cup.h"
#include "ger_super.h"
#include "ger_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* ger_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5D8C20);
static DWORD(__thiscall* ger_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x92B4B0);

DWORD ger_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 21;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
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
	// Bundesliga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_first_init(pMem, *current_year, get_comp(GER_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2. Bundesliga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_second_init(pMem, *current_year, get_comp(GER_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 3. Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_third_init(pMem, *current_year, get_comp(GER_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Regionalliga
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ger_regional_init(pMem, *current_year, get_comp(GER_REGIONAL_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_cup_setup(pMem, *current_year, get_comp(GER_CUP_9CF()));
	get_comp(GER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_CYAN_2_9CF());
	get_comp(GER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_super_setup(pMem, *current_year, get_comp(GER_SUPER_CUP_9CF()));
	get_comp(GER_SUPER_CUP_9CF())->ClubCompBackgroundColour = 0;
	get_comp(GER_SUPER_CUP_9CF())->ClubCompForegroundColour = 0;
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(GER_SUPER_CUP_9CF());
	return 1;
}

void setup_ger_nation()
{
	setup_ger_first();
	setup_ger_second();
	setup_ger_third();
	setup_ger_regional();
	setup_ger_cup();
	setup_ger_super();
	setup_ger_awards();

	WriteNOP(0x5d8cf2, 7);
}

void germany_restructure() {
	cm3_club_comps* regional = get_comp(GER_REGIONAL_9CF());
	vector<cm3_clubs*> reg_n = find_clubs_of_comp(GER_REGIONAL_NORTH_9CF());
	for (cm3_clubs* club : reg_n) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_ne = find_clubs_of_comp(GER_REGIONAL_NORTHEAST_9CF());
	for (cm3_clubs* club : reg_ne) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_sw = find_clubs_of_comp(GER_REGIONAL_SOUTHWEST_9CF());
	for (cm3_clubs* club : reg_sw) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_w = find_clubs_of_comp(GER_REGIONAL_WEST_9CF());
	for (cm3_clubs* club : reg_w) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
	vector<cm3_clubs*> reg_bay = find_clubs_of_comp(GER_REGIONAL_BAYERN_9CF());
	for (cm3_clubs* club : reg_bay) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = regional;
	}
}