#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "aut_first.h"
#include "aut_second.h"
#include "aut_cup.h"
#include <Helpers\9cf_constants.h>

DWORD aut_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	aut_first_init(pMem, *current_year, get_comp(AUT_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	aut_second_init(pMem, *current_year, get_comp(AUT_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	aut_cup_init(pMem, *current_year, get_comp(AUT_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

BYTE* rb_austria_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_AUSTRIA_9CF();
	*((BYTE*)(_this + 0x5)) = RulesAustria;
	*((BYTE*)(_this + 0x1F)) = RulesAustria;
	return _this;
}

void setup_aut_nation() {
	setup_aut_first();
	setup_aut_second();
	setup_aut_cup();
}