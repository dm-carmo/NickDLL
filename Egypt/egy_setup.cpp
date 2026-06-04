#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "egy_first.h"
#include "egy_second.h"
#include "egy_cup.h"
#include "egy_league_cup.h"
#include "egy_super.h"
#include <Helpers\9cf_constants.h>

DWORD egy_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 5;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	egy_first_init(pMem, *current_year, get_comp(EGY_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	egy_second_init(pMem, *current_year, get_comp(EGY_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	egy_cup_init(pMem, *current_year, get_comp(EGY_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF6);
	egy_league_cup_init(pMem, *current_year, get_comp(EGY_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	egy_super_init(pMem, *current_year, get_comp(EGY_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(EGY_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_egypt_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_EGYPT_9CF();
	*((BYTE*)(_this + 0x5)) = RulesEgypt;
	*((BYTE*)(_this + 0x1F)) = RulesEgypt;
	return _this;
}

void setup_egy_nation() {
	setup_egy_first();
	setup_egy_second();
	setup_egy_cup();
	setup_egy_league_cup();
	setup_egy_super();
}