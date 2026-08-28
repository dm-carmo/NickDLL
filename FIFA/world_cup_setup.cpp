#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fifa_world_cup.h"
#include "world_cup_quals_afc.h"
#include "world_cup_quals_caf.h"
#include "world_cup_quals_concacaf.h"
#include "world_cup_quals_ofc.h"
#include "world_cup_quals_conmebol.h"
#include "world_cup_quals_uefa.h"
#include "world_cup_playoffs.h"

DWORD world_cup_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 8;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0x192);
	fifa_world_cup_init(pMem, *current_year, get_comp(FIFA_WORLD_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_caf_init(pMem, *current_year, get_comp(WORLD_CUP_CAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_afc_init(pMem, *current_year, get_comp(WORLD_CUP_AFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_concacaf_init(pMem, *current_year, get_comp(WORLD_CUP_CONCACAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_uefa_init(pMem, *current_year, get_comp(WORLD_CUP_UEFA_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_quals_ofc_init(pMem, *current_year, get_comp(WORLD_CUP_OFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	world_cup_quals_conmebol_init(pMem, *current_year, get_comp(WORLD_CUP_CONMEBOL_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	world_cup_playoffs_init(pMem, *current_year, get_comp(WORLD_CUP_PLAYOFFS_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 25, July, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 2;
	nation_data->super_cup = 0;
	return 1;
}

void setup_world_cup_comps() {
	setup_fifa_world_cup();
	setup_world_cup_quals_afc();
	setup_world_cup_quals_caf();
	setup_world_cup_quals_concacaf();
	setup_world_cup_quals_ofc();
	setup_world_cup_quals_conmebol();
	setup_world_cup_quals_uefa();
	setup_world_cup_playoffs();
}