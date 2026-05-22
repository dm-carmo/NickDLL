#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "irl_premier.h"
#include "irl_first.h"
#include "irl_cup.h"
#include "irl_presidents.h"
#include "irl_awards.h"

static DWORD(__thiscall* irl_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x6340a0);
static DWORD(__thiscall* irl_presidents_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x639280);

DWORD irl_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = February;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	
	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	irl_premier_init(pMem, start_year, get_comp(IRL_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	irl_first_init(pMem, start_year, get_comp(IRL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	irl_cup_setup(pMem, start_year, get_comp(IRL_CHALLENGE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	irl_presidents_setup(pMem, start_year, get_comp(IRL_PRESIDENTS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(IRL_PRESIDENTS_CUP_9CF());
	return 1;
}

void setup_irl_nation() {
	setup_irl_premier();
	setup_irl_first();
	setup_irl_cup();
	setup_irl_presidents();
	setup_irl_awards();

	WriteNOP(0x634172, 7);
}