#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "conmebol_libertadores.h"
#include "conmebol_sudamericana.h"
#include "conmebol_recopa.h"

static DWORD(__thiscall* conmebol_recopa_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x632080);

DWORD conmebol_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = June;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 1;
	nation_data->contract_end_month = June;
	nation_data->contract_end_year = *current_year;
	nation_data->f70 = 5;
	// call 6699D0 removed so the comps always load
	nation_data->num_of_comps = 3;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	conmebol_libertadores_init(pMem, *current_year, get_comp(COPA_LIBERTADORES_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	conmebol_sudamericana_init(pMem, *current_year, get_comp(COPA_SUDAMERICANA_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	conmebol_recopa_setup(pMem, *current_year, get_comp(RECOPA_9CF()));
	get_comp(RECOPA_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_BLUE_4_9CF());
	get_comp(RECOPA_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 2, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_conmebol_continent() {
	WriteDWORD(0x6675b7 + 6, (DWORD)&conmebol_setup_c);

	setup_conmebol_libertadores();
	setup_conmebol_sudamericana();
	setup_conmebol_recopa();
}