#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ksa_premier.h"
#include "ksa_first.h"
#include "ksa_cup.h"
#include "ksa_super.h"
#include <Helpers\9cf_constants.h>

DWORD ksa_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ksa_premier_init(pMem, *current_year, get_comp(KSA_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ksa_first_init(pMem, *current_year, get_comp(KSA_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ksa_cup_init(pMem, *current_year, get_comp(KSA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ksa_super_init(pMem, *current_year, get_comp(KSA_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(KSA_SUPER_CUP_9CF());
	return 1;
}

BYTE* rb_saudi_init(BYTE* _this, int* a2) {
	rb_croatia_setup(_this, a2);
	*((DWORD*)(_this + 0x17)) = NATION_SAUDI_ARABIA_9CF();
	*((BYTE*)(_this + 0x5)) = RulesSaudi;
	*((BYTE*)(_this + 0x1F)) = RulesSaudi;
	return _this;
}

void setup_ksa_nation() {
	setup_ksa_premier();
	setup_ksa_first();
	setup_ksa_cup();
	setup_ksa_super();
}