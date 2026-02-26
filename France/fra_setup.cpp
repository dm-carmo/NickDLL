#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "fra_first.h"
#include "fra_second.h"
#include "fra_third.h"
#include "fra_cup.h"
#include "fra_super.h"

static DWORD(__thiscall* fra_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5BA130);
static DWORD(__thiscall* fra_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5BF320);

DWORD fra_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 4;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Ligue 1
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fra_first_init(pMem, *current_year, get_comp(FRA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ligue 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fra_second_init(pMem, *current_year, get_comp(FRA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// National
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	fra_third_init(pMem, *current_year, get_comp(FRA_NATIONAL_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	fra_cup_setup(pMem, *current_year, get_comp(FRA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	fra_super_setup(pMem, *current_year, get_comp(FRA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(FRA_SUPER_CUP_9CF());
	return 1;
}

void setup_fra_nation()
{
	WriteDWORD(0x667FB5 + 6, (DWORD)&fra_setup_c);
	// Removes reference to League Cup in nation table
	WriteNOP(0x6680b2, 6);
	setup_fra_first();
	setup_fra_second();
	setup_fra_third();
	setup_fra_cup();
	setup_fra_super();
}
