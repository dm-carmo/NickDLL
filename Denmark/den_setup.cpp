#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "den_premier.h"
#include "den_first.h"
#include "den_second.h"
#include "den_third.h"
#include "den_cup.h"
#include "den_awards.h"

static DWORD(__thiscall* den_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5509B0);

DWORD den_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 14;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 6;
	
	nation_data->contract_end_day = 14;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Superliga
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	den_premier_init(pMem, *current_year, get_comp(DEN_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 1
	pMem = (BYTE*)cm0102_new(0xEE);
	den_first_init(pMem, *current_year, get_comp(DEN_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 2
	pMem = (BYTE*)cm0102_new(0xEE);
	den_second_init(pMem, *current_year, get_comp(DEN_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Division 3
	pMem = (BYTE*)cm0102_new(0xEE);
	den_third_init(pMem, *current_year, get_comp(DEN_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	den_cup_setup(pMem, *current_year, get_comp(DEN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_den_nation()
{
	setup_den_premier();
	setup_den_first();
	setup_den_second();
	setup_den_third();
	setup_den_cup();
	setup_den_awards();

	WriteNOP(0x550a7a, 7);
}