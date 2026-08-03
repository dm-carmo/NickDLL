#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bel_first.h"
#include "bel_second.h"
#include "bel_third_vv.h"
#include "bel_third_ac.h"
#include "bel_fourth_vv.h"
#include "bel_fourth_ac.h"
#include "bel_cup.h"
#include "bel_super.h"
#include "bel_awards.h"

static DWORD(__thiscall* bel_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x41d050);
static DWORD(__thiscall* bel_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x420ef0);

DWORD bel_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 8;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	bel_first_init(pMem, *current_year, get_comp(BEL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_second_init(pMem, *current_year, get_comp(BEL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_third_vv_init(pMem, *current_year, get_comp(BEL_THIRD_VV_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	bel_third_ac_init(pMem, *current_year, get_comp(BEL_THIRD_ACFF_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0x104);
		bel_fourth_vv_init(pMem, *current_year, get_comp(BEL_FOURTH_VV_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xF2);
		bel_fourth_ac_init(pMem, *current_year, get_comp(BEL_FOURTH_ACFF_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	bel_cup_setup(pMem, *current_year, get_comp(BEL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	bel_super_setup(pMem, *current_year, get_comp(BEL_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BEL_SUPER_CUP_9CF());
	return 1;
}

void setup_bel_nation() {
	setup_bel_first();
	setup_bel_second();
	setup_bel_third_vv();
	setup_bel_third_ac();
	setup_bel_fourth_vv();
	setup_bel_fourth_ac();
	setup_bel_cup();
	setup_bel_super();
	setup_bel_awards();

	WriteNOP(0x41d122, 7);
}

void belgium_restructure() {
	cm3_club_comps* d4_vv = get_comp(BEL_FOURTH_VV_9CF());
	vector<cm3_clubs*> d4_vv_a = find_clubs_of_comp(BEL_FOURTH_VV_A_9CF());
	for (cm3_clubs* club : d4_vv_a) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4_vv;
	}
	vector<cm3_clubs*> d4_vv_b = find_clubs_of_comp(BEL_FOURTH_VV_B_9CF());
	for (cm3_clubs* club : d4_vv_b) {
		club->ClubReserveDivision = club->ClubDivision;
		club->ClubDivision = d4_vv;
	}
}