#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "eng_premier.h"
#include "eng_champ.h"
#include "eng_league_1.h"
#include "eng_league_2.h"
#include "eng_conf.h"
#include "eng_conf_n.h"
#include "eng_conf_s.h"
#include "eng_fa_cup.h"
#include "eng_league_cup.h"
#include "eng_fa_trophy.h"
#include "eng_awards.h"
#include <Helpers\9cf_constants.h>

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
	eng_premier_init(pMem, *current_year, get_comp(ENG_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_champ_init(pMem, *current_year, get_comp(ENG_CHAMP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League One
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_league_1_init(pMem, *current_year, get_comp(ENG_LEAGUE_1_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Two
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	eng_league_2_init(pMem, *current_year, get_comp(ENG_LEAGUE_2_9CF()));
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
	eng_league_cup_init(pMem, *current_year, get_comp(ENG_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Trophy
	pMem = (BYTE*)sub_944CF1_operator_new(0xBA);
	eng_league_trophy_setup(pMem, *current_year, get_comp(ENG_LEAGUE_TROPHY_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Charity Shield
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	eng_charity_setup(pMem, *current_year, get_comp(ENG_CHARITY_SHIELD_9CF()));
	get_comp(ENG_CHARITY_SHIELD_9CF())->ClubCompForegroundColour = 0;
	get_comp(ENG_CHARITY_SHIELD_9CF())->ClubCompBackgroundColour = 0;
	nation_comps[i++] = (DWORD)pMem;
	// FA Trophy
	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
		eng_fa_trophy_setup(pMem, *current_year, get_comp(ENG_FA_TROPHY_9CF()));
		get_comp(ENG_FA_TROPHY_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_RED_1_9CF());
		get_comp(ENG_FA_TROPHY_9CF())->ClubCompForegroundColour = get_colour(COLOUR_GREEN_4_9CF());
		nation_comps[i++] = (DWORD)pMem;
	}
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ENG_CHARITY_SHIELD_9CF());
	return 1;
}

void setup_eng_nation() {
	WriteDWORD(0x667D97 + 6, (DWORD)&eng_setup_c);
	setup_eng_premier();
	setup_eng_champ();
	setup_eng_league_1();
	setup_eng_league_2();
	setup_eng_conf();
	setup_eng_conf_n();
	setup_eng_conf_s();
	setup_eng_fa_cup();
	setup_eng_league_cup();
	setup_eng_fa_trophy();
	setup_eng_awards();

	WriteNOP(0x570cd2, 7);
	WriteNOP(0x56d452, 7);
}

void england_restructure() {
	cm3_club_comps* nat_lge = get_comp(ENG_CONFERENCE_9CF());
	if (nat_lge) {
		cm3_clubs* club1 = find_club("Boston United");
		if (club1) {
			club1->ClubDivision = nat_lge;
		}
		cm3_clubs* club2 = find_club("Braintree Town");
		if (club2) {
			club2->ClubDivision = nat_lge;
		}
	}

	cm3_staff_comps* data = &(*awards)[ENG_CONFERENCE_N_MANAGER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_N_MANAGER_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 5;
	}
	data = &(*awards)[ENG_CONFERENCE_N_PLAYER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_N_TEAM_OF_WEEK_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_N_TEAM_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 5;
	}
	data = &(*awards)[ENG_CONFERENCE_N_YOUNG_PLAYER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 3;
	}
	data = &(*awards)[ENG_CONFERENCE_S_MANAGER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_S_MANAGER_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 5;
	}
	data = &(*awards)[ENG_CONFERENCE_S_PLAYER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_S_TEAM_OF_WEEK_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 4;
	}
	data = &(*awards)[ENG_CONFERENCE_S_TEAM_OF_YEAR_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 5;
	}
	data = &(*awards)[ENG_CONFERENCE_S_YOUNG_PLAYER_OF_MONTH_9CF()];
	if (data) {
		data->StaffCompNation = get_country(NATION_ENGLAND_9CF());
		data->StaffCompContinent = find_continent("Europe");
		data->StaffCompReputation = 3;
	}
}