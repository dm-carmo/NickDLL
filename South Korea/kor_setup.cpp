#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "kor_first.h"
#include "kor_second.h"
#include "kor_cup.h"
#include "kor_super.h"
#include "kor_awards.h"

static DWORD(__thiscall* kor_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x66A460);
static DWORD(__thiscall* kor_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x66D820);

DWORD kor_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = February;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 6;
	
	nation_data->contract_end_day = 20;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// K1
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	kor_first_init(pMem, start_year, get_comp(KOR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// K2
	pMem = (BYTE*)cm0102_new(0xEE);
	kor_second_init(pMem, start_year, get_comp(KOR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	kor_cup_setup(pMem, start_year, get_comp(KOR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super Cup
	pMem = (BYTE*)cm0102_new(0xB2);
	kor_super_setup(pMem, start_year, get_comp(KOR_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(KOR_SUPER_CUP_9CF());
	return 1;
}

void setup_kor_nation() {
	setup_kor_first();
	setup_kor_second();
	setup_kor_cup();
	setup_kor_super();
	setup_kor_awards();
	// foreign player limits
	WriteBytes(0x66e765, 1, 0x5);
	WriteNOP(0x66e738, 4);

	WriteNOP(0x66a52a, 7);
}