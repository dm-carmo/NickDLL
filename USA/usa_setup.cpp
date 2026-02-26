#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "usa_mls.h"
#include "usa_champ.h"
#include "usa_cup.h"
#include "usa_awards.h"

static DWORD(__thiscall* usa_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x90AEB0);

DWORD usa_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 14;
	nation_data->contract_start_month = February;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 2;
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// MLS
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	usa_mls_init(pMem, start_year, get_comp(USA_MLS_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	usa_champ_init(pMem, start_year, get_comp(USA_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	usa_cup_setup(pMem, start_year, get_comp(USA_OPEN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, (DWORD*)-1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_usa_nation() {
	WriteDWORD(0x668F51 + 6, (DWORD)&usa_setup_c);
	setup_usa_mls();
	setup_usa_champ();
	setup_usa_cup();
	setup_usa_awards();
	// Start date
	WriteBytes(0x668fa0, 1, February);
	WriteBytes(0x668fa2, 1, 20);
	WriteBytes(0x66900f, 3, 0x6a, 0x0, 0x57);
}