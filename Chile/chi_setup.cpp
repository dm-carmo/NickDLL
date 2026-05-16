#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "chi_premier.h"
#include "chi_first.h"
#include "chi_cup.h"
#include "chi_league_cup.h"
#include "chi_super.h"
#include <Helpers\9cf_constants.h>

DWORD chi_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;

	nation_data->contract_end_day = 15;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	chi_premier_init(pMem, start_year, get_comp(CHI_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	chi_first_init(pMem, start_year, get_comp(CHI_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	chi_cup_init(pMem, start_year, get_comp(CHI_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	chi_league_cup_init(pMem, start_year, get_comp(CHI_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	chi_super_init(pMem, start_year, get_comp(CHI_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(CHI_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_chile_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_CHILE_9CF();
	*((BYTE*)(_this + 0x5)) = RulesChile;
	*((BYTE*)(_this + 0x1F)) = RulesChile;
	return _this;
}

void setup_chi_nation() {
	setup_chi_premier();
	setup_chi_first();
	setup_chi_cup();
	setup_chi_league_cup();
	setup_chi_super();
}