#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "ofc_nations_cup.h"
#include "african_nations.h"
#include "african_nations_quals.h"
#include "asian_cup.h"
#include "asian_cup_quals.h"
#include "euro_champ.h"
#include "euro_champ_quals.h"
#include "uefa_nations_league.h"
#include "concacaf_nations_league.h"
#include "copa_america.h"
#include "copa_america_quals.h"
#include "gold_cup.h"
#include "gold_cup_quals.h"
#include "olympics.h"

DWORD fifa_national_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 14;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	olympics_init(pMem, *current_year, get_comp(OLYMPIC_GAMES_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	african_nations_init(pMem, *current_year, get_comp(AFCON_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	african_nations_quals_init(pMem, *current_year, get_comp(AFCON_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	asian_cup_init(pMem, *current_year, get_comp(ASIAN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	asian_cup_quals_init(pMem, *current_year, get_comp(ASIAN_CUP_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	euro_champ_init(pMem, *current_year, get_comp(UEFA_EURO_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	euro_champ_quals_init(pMem, *current_year, get_comp(UEFA_EURO_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	uefa_nations_league_init(pMem, *current_year, get_comp(UEFA_NATIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	gold_cup_init(pMem, *current_year, get_comp(GOLD_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	gold_cup_quals_init(pMem, *current_year, get_comp(GOLD_CUP_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	concacaf_nations_league_init(pMem, *current_year, get_comp(CONCACAF_NATIONS_LEAGUE_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	ofc_nations_cup_init(pMem, *current_year, get_comp(OFC_NATIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	copa_america_init(pMem, *current_year, get_comp(COPA_AMERICA_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	copa_america_quals_init(pMem, *current_year, get_comp(COPA_AMERICA_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 6, August, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 2;
	nation_data->super_cup = 0;
	return 1;
}

void setup_fifa_national_comps() {
	setup_ofc_nations_cup();
	setup_african_nations();
	setup_african_nations_quals();
	setup_asian_cup();
	setup_asian_cup_quals();
	setup_euro_champ();
	setup_euro_champ_quals();
	setup_uefa_nations_league();
	setup_concacaf_nations_league();
	setup_copa_america();
	setup_copa_america_quals();
	setup_gold_cup();
	setup_gold_cup_quals();
	setup_olympics();
}