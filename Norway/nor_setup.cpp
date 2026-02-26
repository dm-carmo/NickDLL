#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "nor_premier.h"
#include "nor_first.h"
#include "nor_second.h"
#include "nor_third.h"
#include "nor_cup.h"
#include "nor_awards.h"

static DWORD(__thiscall* nor_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x78F020);

DWORD nor_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = March;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 4;
	}
	else {
		nation_data->num_of_comps = 5;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Eliteserien
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_premier_init(pMem, start_year, get_comp(NOR_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 1. divisjon
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_first_init(pMem, start_year, get_comp(NOR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2. divisjon
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_second_init(pMem, start_year, get_comp(NOR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// 3. divisjon
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		nor_third_init(pMem, start_year, get_comp(NOR_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	nor_cup_setup(pMem, *current_year, get_comp(NOR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_nor_nation()
{
	WriteDWORD(0x66873E+ 6, (DWORD)&nor_setup_c);
	setup_nor_premier();
	setup_nor_first();
	setup_nor_second();
	setup_nor_third();
	setup_nor_cup();
	setup_nor_awards();
}
