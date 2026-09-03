#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "sui_premier.h"
#include "sui_first.h"
#include "sui_second.h"
#include "sui_cup.h"
#include "lie_cup.h"
#include <Helpers\9cf_constants.h>

DWORD sui_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	sui_premier_init(pMem, *current_year, get_comp(SUI_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	 pMem = (BYTE*)cm0102_new(0xEE);
	sui_first_init(pMem, *current_year, get_comp(SUI_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sui_second_init(pMem, *current_year, get_comp(SUI_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	sui_cup_init(pMem, *current_year, get_comp(SUI_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	lie_cup_init(pMem, *current_year, get_comp(LIE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_switzerland_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_SWITZERLAND_9CF();
	*((BYTE*)(_this + 0x5)) = RulesSwitzerland;
	*((BYTE*)(_this + 0x1F)) = RulesSwitzerland;
	return _this;
}

void setup_sui_nation() {
	setup_sui_premier();
	setup_sui_first();
	setup_sui_second();
	setup_sui_cup();
	setup_lie_cup();
}