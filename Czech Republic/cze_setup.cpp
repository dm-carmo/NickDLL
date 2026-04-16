#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "cze_first.h"
//#include "cze_second.h"
//#include "cze_third.h"
//#include "cze_cup.h"
#include <Helpers\9cf_constants.h>

DWORD cze_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 1;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	cze_first_init(pMem, *current_year, get_comp(CZE_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	//cze_second_init(pMem, *current_year, get_comp(CZE_SECOND_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	//cze_third_init(pMem, *current_year, get_comp(CZE_THIRD_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	//pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	//cze_cup_setup(pMem, *current_year, get_comp(CZE_CUP_9CF()));
	//nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_czech_init(BYTE* _this, int* a2) {
	rb_croatia_setup ( _this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_CZECH_REPUBLIC_9CF();
	*((BYTE*)(_this + 0x5)) = RulesCzech;
	*((BYTE*)(_this + 0x1F)) = RulesCzech;
	return _this;
}

void setup_cze_nation() {
	setup_cze_first();
	//setup_cze_second();
	//setup_cze_third();
	//setup_cze_cup();
}