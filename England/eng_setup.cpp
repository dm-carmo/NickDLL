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
#include "eng_league_trophy.h"
#include "eng_fa_trophy.h"
#include "eng_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* eng_charity_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x56D380);
static DWORD(__thiscall* eng_fa_trophy_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x570C00);

DWORD eng_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 10;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->contract_start_day_of_week = 5;
	
	nation_data->contract_end_day = 29;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->contract_end_day_of_week = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 8;
	}
	else {
		nation_data->num_of_comps = 12;
	}
	DWORD* nation_comps = (DWORD*)cm0102_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Premier League
	BYTE* pMem = (BYTE*)cm0102_new(0xEE);
	eng_premier_init(pMem, *current_year, get_comp(ENG_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Championship
	pMem = (BYTE*)cm0102_new(0xEE);
	eng_champ_init(pMem, *current_year, get_comp(ENG_CHAMP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League One
	pMem = (BYTE*)cm0102_new(0xEE);
	eng_league_1_init(pMem, *current_year, get_comp(ENG_LEAGUE_1_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Two
	pMem = (BYTE*)cm0102_new(0xEE);
	eng_league_2_init(pMem, *current_year, get_comp(ENG_LEAGUE_2_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// National League
		pMem = (BYTE*)cm0102_new(0xEE);
		eng_conf_init(pMem, *current_year, get_comp(ENG_CONFERENCE_9CF()));
		nation_comps[i++] = (DWORD)pMem;
		// National League North
		pMem = (BYTE*)cm0102_new(0xEE);
		eng_conf_n_init(pMem, *current_year, get_comp(ENG_CONFERENCE_NORTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
		// National League South
		pMem = (BYTE*)cm0102_new(0xEE);
		eng_conf_s_init(pMem, *current_year, get_comp(ENG_CONFERENCE_SOUTH_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// FA Cup
	pMem = (BYTE*)cm0102_new(0xB5);
	eng_fa_cup_init(pMem, *current_year, get_comp(ENG_FA_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Cup
	pMem = (BYTE*)cm0102_new(0xB3);
	eng_league_cup_init(pMem, *current_year, get_comp(ENG_LEAGUE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// League Trophy
	pMem = (BYTE*)cm0102_new(0xF6);
	eng_league_trophy_init(pMem, *current_year, get_comp(ENG_LEAGUE_TROPHY_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Charity Shield
	pMem = (BYTE*)cm0102_new(0xB2);
	eng_charity_setup(pMem, *current_year, get_comp(ENG_CHARITY_SHIELD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// FA Trophy
	if ((selected & 4) != 0) {
		pMem = (BYTE*)cm0102_new(0xB2);
		eng_fa_trophy_setup(pMem, *current_year, get_comp(ENG_FA_TROPHY_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, START_YEAR, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(ENG_CHARITY_SHIELD_9CF());
	return 1;
}

void setup_eng_nation() {
	setup_eng_premier();
	setup_eng_champ();
	setup_eng_league_1();
	setup_eng_league_2();
	setup_eng_conf();
	setup_eng_conf_n();
	setup_eng_conf_s();
	setup_eng_fa_cup();
	setup_eng_league_cup();
	setup_eng_league_trophy();
	setup_eng_fa_trophy();
	setup_eng_awards();

	WriteNOP(0x570cd2, 7);
	WriteNOP(0x56d452, 7);
}

void england_restructure() {
	if (configFile.GetBool("useEnglandAcademyTeams"))
	{
		cm3_club_comps* eng_academy = get_comp(ENG_ACADEMY_9CF());
		strcpy_s(eng_academy->ClubCompName, "English Academy League");
		strcpy_s(eng_academy->ClubCompNameShort, "Academy League");
		eng_academy->ClubCompReputation = 1;
		vector<string> eng_reserves = {
			"Arsenal FC U21",
			"Aston Villa U21",
			"Blackburn Rovers U23",
			"Brentford FC B",
			"Brighton & Hove Albion U21",
			"Bristol City U21",
			"Burnley FC U21",
			"Chelsea FC U21",
			"Crystal Palace U21",
			"Everton FC U21",
			"Fulham FC U23",
			"Ipswich Town U21",
			"Leeds United U21",
			"Leicester City U21",
			"Liverpool FC U21",
			"Manchester City U21",
			"Manchester United U21",
			"Middlesbrough FC U21",
			"Newcastle United U21",
			"Nottingham Forest U21",
			"Queens Park Rangers U23",
			"Reading FC U23",
			"Southampton FC B",
			"Stoke City U21",
			"Sunderland AFC U21",
			"Tottenham Hotspur U21",
			"West Bromwich Albion U21",
			"West Ham United U21",
			"Wolverhampton Wanderers U21",
		};
		for (string s : eng_reserves) {
			cm3_clubs* club = find_club(s.c_str());
			if (!club) {
				create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
				continue;
			}
			club->ClubDivision = eng_academy;
		}
	}
}