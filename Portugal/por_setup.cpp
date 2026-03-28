#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "por_first.h"
#include "por_second.h"
#include "por_third.h"
#include "por_fourth.h"
#include "por_cup.h"
#include "por_league_cup.h"
#include "por_super.h"
#include "por_awards.h"

static DWORD(__thiscall* por_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CD980);
static DWORD(__thiscall* por_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7D2E40);

DWORD por_setup_c(playable_nation_data* nation_data) {
	
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
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Liga 1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_first_init(pMem, *current_year, get_comp(POR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_second_init(pMem, *current_year, get_comp(POR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Liga 3
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	por_third_init(pMem, *current_year, get_comp(POR_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Campeonato de Portugal
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		por_fourth_init(pMem, *current_year, get_comp(POR_FOURTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_cup_setup(pMem, *current_year, get_comp(POR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_league_cup_init(pMem, *current_year, get_comp(POR_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	por_super_setup(pMem, *current_year, get_comp(POR_SUPER_CUP_9CF()));
	get_comp(POR_SUPER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_ORANGE_1_9CF());
	get_comp(POR_SUPER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(POR_SUPER_CUP_9CF());
	return 1;
}

void setup_por_nation()
{
	setup_por_first();
	setup_por_second();
	setup_por_third();
	setup_por_fourth();
	setup_por_cup();
	setup_por_league_cup();
	setup_por_super();
	setup_por_awards();

	WriteNOP(0x7cda4a, 7);
}

void portugal_restructure() {
	cm3_club_comps* l3 = get_comp(POR_THIRD_9CF());
	vector<cm3_clubs*> l3_a = find_clubs_of_comp(POR_THIRD_A_9CF());
	for (cm3_clubs* club : l3_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = l3;
	}
	vector<cm3_clubs*> l3_b = find_clubs_of_comp(POR_THIRD_B_9CF());
	for (cm3_clubs* club : l3_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = l3;
	}
	cm3_club_comps* cdp = get_comp(POR_FOURTH_9CF());
	vector<cm3_clubs*> cdp_a = find_clubs_of_comp(POR_FOURTH_A_9CF());
	for (cm3_clubs* club : cdp_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_b = find_clubs_of_comp(POR_FOURTH_B_9CF());
	for (cm3_clubs* club : cdp_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_c = find_clubs_of_comp(POR_FOURTH_C_9CF());
	for (cm3_clubs* club : cdp_c) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
	vector<cm3_clubs*> cdp_d = find_clubs_of_comp(POR_FOURTH_D_9CF());
	for (cm3_clubs* club : cdp_d) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = cdp;
	}
}