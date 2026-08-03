#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "sco_premier.h"
#include "sco_champ.h"
#include "sco_league_1.h"
#include "sco_league_2.h"
#include "sco_highland.h"
#include "sco_lowland.h"
#include "sco_cup.h"
#include "sco_league_cup.h"
#include "sco_challenge_cup.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* sco_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x7ed310);
static DWORD(__thiscall* sco_challenge_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x570C00);

DWORD sco_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 7;
	}
	else {
		nation_data->num_of_comps = 9;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;

	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	sco_premier_init(pMem, *current_year, get_comp(SCO_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_champ_init(pMem, *current_year, get_comp(SCO_CHAMP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_league_1_init(pMem, *current_year, get_comp(SCO_LEAGUE_1_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xEE);
	sco_league_2_init(pMem, *current_year, get_comp(SCO_LEAGUE_2_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xEE);
		sco_highland_init(pMem, *current_year, get_comp(SCO_HIGHLAND_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)cm0102_new(0xEE);
		sco_lowland_init(pMem, *current_year, get_comp(SCO_LOWLAND_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)cm0102_new(0xB2);
	sco_cup_setup(pMem, *current_year, get_comp(SCO_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	sco_league_cup_init(pMem, *current_year, get_comp(SCO_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)cm0102_new(0xF6);
	sco_challenge_cup_init(pMem, *current_year, get_comp(SCO_CHALLENGE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_sco_nation() {
	setup_sco_premier();
	setup_sco_champ();
	setup_sco_league_1();
	setup_sco_league_2();
	setup_sco_highland();
	setup_sco_lowland();
	setup_sco_cup();
	setup_sco_league_cup();
	setup_sco_challenge_cup();

	WriteNOP(0x7ed3e2, 7);
}