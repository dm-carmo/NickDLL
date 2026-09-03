#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "arg_first.h"
#include "arg_second.h"
#include "arg_third_metro.h"
#include "arg_third_interior.h"
#include "arg_cup.h"
#include "arg_champ_cup.h"
#include "arg_super.h"

DWORD arg_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);

	nation_data->contract_start_day = 15;
	nation_data->contract_start_month = January;
	nation_data->contract_start_year = start_year;
	nation_data->contract_start_day_of_week = 6;

	nation_data->contract_end_day = 15;
	nation_data->contract_end_month = December;
	nation_data->contract_end_year = start_year;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 7;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xF6);
	arg_first_init(pMem, start_year, get_comp(ARG_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	arg_second_init(pMem, start_year, get_comp(ARG_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		arg_third_metro_init(pMem, start_year, get_comp(ARG_THIRD_METRO_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xF2);
		arg_third_interior_init(pMem, start_year, get_comp(ARG_THIRD_INTERIOR_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_cup_init(pMem, start_year, get_comp(ARG_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_champ_cup_init(pMem, start_year, get_comp(ARG_CHAMPIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	arg_super_init(pMem, start_year, get_comp(ARG_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ARG_SUPER_CUP_9CF());
	return 1;
}

void setup_arg_nation() {
	setup_arg_first();
	setup_arg_second();
	setup_arg_third_metro();
	setup_arg_third_interior();
	setup_arg_cup();
	setup_arg_champ_cup();
	setup_arg_super();

	// transfer window adjustment
	WriteBytes(0x40a6ae, 1, Saturday);
	WriteBytes(0x40a6af, 1, 0x14);
	WriteBytes(0x40a6b4, 1, 0xb);
	WriteBytes(0x40a6c9, 1, Tuesday);
	WriteBytes(0x40a6ca, 1, 0x1b);
	WriteBytes(0x40a6cf, 1, 0x0);
	WriteBytes(0x40a6e4, 1, 0x6);
	WriteBytes(0x40a6e6, 4, 0xc6, 0x40, 0x4, 0x6);
	WriteBytes(0x40a701, 1, 0x1e);
	WriteBytes(0x40a706, 1, 0x7);
	// loans adjustment - only full season loans + can't loan outside transfer window
	WriteDWORD(0x9674c0, 0x412dd0);
	WriteDWORD(0x9674c8, 0x90f1a0);
	// Max foreign players in club - separate from match restriction
	WriteBytes(0x40a5d9, 1, 0x6);
}