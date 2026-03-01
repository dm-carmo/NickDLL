#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "swe_premier.h"
#include "swe_first.h"
#include "swe_second.h"
#include "swe_third.h"
#include "swe_cup.h"

static DWORD(__thiscall* swe_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x88CBB0);

DWORD swe_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = March;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
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
	// Allsvenskan
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	swe_premier_init(pMem, start_year, get_comp(SWE_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Superettan
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	swe_first_init(pMem, start_year, get_comp(SWE_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ettan
	pMem = (BYTE*)sub_944CF1_operator_new(0x106);
	swe_second_init(pMem, start_year, get_comp(SWE_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Division 2
		pMem = (BYTE*)sub_944CF1_operator_new(0x11E);
		swe_third_init(pMem, start_year, get_comp(SWE_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	swe_cup_init(pMem, *current_year, get_comp(SWE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_swe_nation()
{
	WriteDWORD(0x668D74 + 6, (DWORD)&swe_setup_c);
	setup_swe_premier();
	setup_swe_first();
	setup_swe_second();
	setup_swe_third();
	setup_swe_cup();
}
