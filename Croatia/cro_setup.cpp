#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cro_first.h"
#include "cro_second.h"
#include "cro_third.h"
#include "cro_cup.h"
#include "cro_super.h"
#include "cro_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* cro_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x517480);

DWORD cro_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// HNL
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	cro_first_init(pMem, *current_year, get_comp(CRO_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 1.NL
	pMem = (BYTE*)cm0102_new(0xEE);
	cro_second_init(pMem, *current_year, get_comp(CRO_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2.NL
	pMem = (BYTE*)cm0102_new(0xEE);
	cro_third_init(pMem, *current_year, get_comp(CRO_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	cro_cup_setup(pMem, *current_year, get_comp(CRO_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)cm0102_new(0xB2);
	cro_super_init(pMem, *current_year, get_comp(CRO_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(CRO_SUPER_CUP_9CF());
	return 1;
}

void setup_cro_nation() {
	setup_cro_first();
	setup_cro_second();
	setup_cro_third();
	setup_cro_cup();
	setup_cro_super();
	setup_cro_awards();

	WriteNOP(0x517552, 7);
}