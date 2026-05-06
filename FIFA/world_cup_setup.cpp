#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
//#include "world_cup.h"

static DWORD(__thiscall* world_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x92BF50);
static DWORD(__thiscall* wcq_uefa_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x918200);
static DWORD(__thiscall* wcq_afc_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x911BF0);
static DWORD(__thiscall* wcq_caf_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x90F210);
static DWORD(__thiscall* wcq_concacaf_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x9149F0);
static DWORD(__thiscall* wcq_conmebol_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x9202B0);
static DWORD(__thiscall* wcq_ofc_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x91DF90);
DWORD world_cup_setup_c(playable_nation_data* nation_data) {

	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;

	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 7;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0x192);
	world_cup_setup(pMem, *current_year, get_comp(FIFA_WORLD_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xBB);
	wcq_caf_setup(pMem, *current_year, get_comp(WORLD_CUP_CAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xFB);
	wcq_afc_setup(pMem, *current_year, get_comp(WORLD_CUP_AFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xBD);
	wcq_concacaf_setup(pMem, *current_year, get_comp(WORLD_CUP_CONCACAF_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0x102);
	wcq_uefa_setup(pMem, *current_year, get_comp(WORLD_CUP_UEFA_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF7);
	wcq_ofc_setup(pMem, *current_year, get_comp(WORLD_CUP_OFC_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xF0);
	wcq_conmebol_setup(pMem, *current_year, get_comp(WORLD_CUP_CONMEBOL_QUALIFYING_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 25, July, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = 1996; //*current_year;
	nation_data->f29 = 2;
	nation_data->super_cup = 0;
	return 1;
}

void setup_world_cup_comps() {

}