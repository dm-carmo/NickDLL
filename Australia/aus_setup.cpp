#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "aus_league.h"
#include "aus_cup.h"
#include <Helpers\9cf_constants.h>

DWORD aus_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 7;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 2;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	aus_league_init(pMem, *current_year, get_comp(AUS_A_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	aus_cup_init(pMem, *current_year, get_comp(AUS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;


	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_aus_nation() {
	setup_aus_league();
	setup_aus_cup();
}