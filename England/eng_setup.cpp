#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "eng_third.h"
#include "eng_conf.h"
#include "eng_conf_n.h"
#include "eng_conf_s.h"
#include "eng_fa_cup.h"
#include "eng_prm.h"
#include "eng_first.h"
#include "eng_fa_trophy.h"
#include "eng_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* eng_prm_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x573380);
static DWORD(__thiscall* eng_second_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5754A0);
static DWORD(__thiscall* eng_league_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56C2A0);
static DWORD(__thiscall* eng_charity_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56D380);
static DWORD(__thiscall* eng_fa_trophy_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x570C00);
static DWORD(__thiscall* eng_league_trophy_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56AA30);

DWORD eng_setup_c(playable_nation_data* nation_data) {
	// contract start date?
	nation_data->contract_start_day = 10;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	// contract end date?
	nation_data->contract_end_day = 29;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 8;
	}
	else {
		nation_data->num_of_comps = 12;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Premier League
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_prm_setup(pMem, *current_year, get_comp(ENG_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_first_init(pMem, *current_year, get_comp(ENG_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League One
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_second_setup(pMem, *current_year, get_comp(ENG_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Two
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_third_init(pMem, *current_year, get_comp(ENG_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// National League
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		eng_conf_init(pMem, *current_year, get_comp(ENG_CONFERENCE_9CF()));
		nation_comps[i++] = (DWORD)pMem;
		// National League North
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		eng_conf_n_init(pMem, *current_year, get_comp(ENG_CONFERENCE_NORTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
		// National League South
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		eng_conf_s_init(pMem, *current_year, get_comp(ENG_CONFERENCE_SOUTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// FA Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB5);
	eng_fa_cup_init(pMem, *current_year, get_comp(ENG_FA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB3);
	eng_league_cup_setup(pMem, *current_year, get_comp(ENG_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Trophy
	pMem = (BYTE*)sub_944CF1_operator_new(0xBA);
	eng_league_trophy_setup(pMem, *current_year, get_comp(ENG_LEAGUE_TROPHY_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Charity Shield
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	eng_charity_setup(pMem, *current_year, get_comp(ENG_CHARITY_SHIELD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// FA Trophy
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
		eng_fa_trophy_setup(pMem, *current_year, get_comp(ENG_FA_TROPHY_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, (DWORD*)-1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ENG_CHARITY_SHIELD_9CF());
	return 1;
}

void setup_eng_nation() {
	WriteDWORD(0x667D97 + 6, (DWORD)&eng_setup_c);
	setup_eng_prm();
	setup_eng_third();
	setup_eng_conf();
	setup_eng_conf_n();
	setup_eng_conf_s();
	setup_eng_fa_cup();
	setup_eng_fa_trophy();
	setup_eng_awards();
}