#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "ofc_nations_cup.h"
#include "african_nations.h"
#include "african_nations_quals.h"

static DWORD(__thiscall* olympic_games_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x79f530);
static DWORD(__thiscall* uefa_euro_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x57a890);
static DWORD(__thiscall* uefa_euro_quals_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x57ce10);
static DWORD(__thiscall* copa_america_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5e0660);
static DWORD(__thiscall* gold_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x929140);
static DWORD(__thiscall* asian_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x40e860);

DWORD fifa_national_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 9;
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xF6);
	olympic_games_setup(pMem, *current_year, get_comp(OLYMPIC_GAMES_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF4);
	african_nations_init(pMem, *current_year, get_comp(AFRICAN_CUP_OF_NATIONS_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xB2);
	african_nations_quals_init(pMem, *current_year, get_comp(AFRICAN_CUP_OF_NATIONS_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF4);
	asian_cup_setup(pMem, *current_year, get_comp(ASIAN_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF4);
	gold_cup_setup(pMem, *current_year, get_comp(GOLD_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x142);
	uefa_euro_setup(pMem, *current_year, get_comp(UEFA_EURO_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0x102);
	uefa_euro_quals_setup(pMem, *current_year, get_comp(UEFA_EURO_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF4);
	ofc_nations_cup_init(pMem, *current_year, get_comp(OFC_NATIONS_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	copa_america_setup(pMem, *current_year, get_comp(COPA_AMERICA_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 15, August, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 2;
	nation_data->super_cup = 0;
	return 1;
}

void setup_fifa_national_comps() {
	setup_ofc_nations_cup();
	setup_african_nations();
	setup_african_nations_quals();
}