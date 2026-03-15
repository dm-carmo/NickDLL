#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "caf_champions_league.h"
#include "caf_confederation_cup.h"
#include "caf_super_cup.h"

static DWORD(__thiscall* caf_super_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x410650);

DWORD caf_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	caf_champions_league_init(pMem, *current_year, get_comp(CAF_CHAMPIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	caf_confederation_cup_init(pMem, *current_year, get_comp(CAF_CONFEDERATION_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	caf_super_cup_setup(pMem, *current_year, get_comp(CAF_SUPER_CUP_9CF()));
	get_comp(CAF_SUPER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_CYAN_2_9CF());
	get_comp(CAF_SUPER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 21, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_caf_continent() {
	setup_caf_champions_league();
	setup_caf_confederation_cup();
	setup_caf_super_cup();
}