#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "afc_champions_league_elite.h"
#include "afc_champions_league_2.h"
#include "afc_challenge_league.h"

DWORD afc_setup_c(playable_nation_data* nation_data) {
	
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
	afc_champions_league_elite_init(pMem, *current_year, get_comp(AFC_CHAMPIONS_LEAGUE_ELITE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	afc_champions_league_2_init(pMem, *current_year, get_comp(AFC_CHAMPIONS_LEAGUE_TWO_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	afc_challenge_league_init(pMem, *current_year, get_comp(AFC_CHALLENGE_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 21, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_afc_continent() {
	setup_afc_champions_league_elite();
	setup_afc_champions_league_2();
	setup_afc_challenge_league();
}