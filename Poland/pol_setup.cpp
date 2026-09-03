#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "pol_first.h"
#include "pol_second.h"
#include "pol_third.h"
#include "pol_cup.h"
#include "pol_super.h"
#include "pol_awards.h"

static DWORD(__thiscall* pol_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7C7D80);
static DWORD(__thiscall* pol_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7CC920);

DWORD pol_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 17;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 3;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Ekstraklasa
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	pol_first_init(pMem, *current_year, get_comp(POL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// I Liga
	pMem = (BYTE*)cm0102_new(0xEE);
	pol_second_init(pMem, *current_year, get_comp(POL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// II Liga
	pMem = (BYTE*)cm0102_new(0xEE);
	pol_third_init(pMem, *current_year, get_comp(POL_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	pol_cup_setup(pMem, *current_year, get_comp(POL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	pol_super_setup(pMem, *current_year, get_comp(POL_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(POL_SUPER_CUP_9CF());
	return 1;
}

void setup_pol_nation()
{
	setup_pol_first();
	setup_pol_second();
	setup_pol_third();
	setup_pol_cup();
	setup_pol_super();
	setup_pol_awards();

	WriteNOP(0x7c7e52, 7);
}