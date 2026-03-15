#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "gre_first.h"
#include "gre_second.h"
#include "gre_cup.h"
#include "gre_super.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* gre_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5ec040);

DWORD gre_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 10;
	nation_data->contract_start_month = August;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	nation_data->num_of_comps = 4;
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Super League
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	gre_first_init(pMem, *current_year, get_comp(GRE_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Super League 2
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	gre_second_init(pMem, *current_year, get_comp(GRE_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	gre_cup_init(pMem, *current_year, get_comp(GRE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	gre_super_setup(pMem, *current_year, get_comp(GRE_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(GRE_SUPER_CUP_9CF());
	return 1;
}

void setup_gre_nation() {
	WriteDWORD(0x66817D + 6, (DWORD)&gre_setup_c);
	setup_gre_first();
	setup_gre_second();
	setup_gre_cup();
	setup_gre_super();
	// Bypass check for 14 teams in Greek leagues
	WriteBytes(0x8283b9, 1, 0xEB);
}

void greece_restructure() {
	cm3_nations* greece = get_country(NATION_GREECE_9CF());
	cm3_club_comps* gre_second = get_comp(GRE_SECOND_9CF());
	cm3_club_comps* gre_second_n = get_comp(GRE_SECOND_NORTH_9CF());
	gre_second_n->ClubCompNation = greece;
	gre_second_n->ClubCompReputation = 8;
	cm3_club_comps* gre_second_s = get_comp(GRE_SECOND_SOUTH_9CF());
	gre_second_s->ClubCompNation = greece;
	gre_second_s->ClubCompReputation = 8;
	cm3_club_comps* gre_lower = get_comp(GRE_LOWER_9CF());
	cm3_club_comps* swe_lower = get_comp(SWE_LOWER_9CF());

	vector<cm3_clubs*> clubs = find_clubs_of_comp(gre_second->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = gre_lower;
	}
	clubs = find_clubs_of_comp(gre_second_n->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = swe_lower;
	}
	clubs = find_clubs_of_comp(gre_second_s->ClubCompID);
	for (cm3_clubs* c : clubs) {
		c->ClubDivision = swe_lower;
	}

	vector<string> d2n_clubs = {
		"Anagennisi Karditsas",
		"Asteras Aktor B",
		"POT Iraklis Thessaloniki",
		"Kampaniakos",
		"AO Kavala",
		"Makedonikos Neapolis",
		"Nestos Chrysoupolis",
		"Niki Volou",
		"PAOK Thessaloniki B",
		"PAS Giannina",
	};
	vector<string> d2s_clubs = {
		"Athens Kallithea",
		"PAE Chania",
		"AO Egaleo",
		"Ellas Syrou",
		"GS Ilioupolis",
		"PS Kalamata",
		"GS Marko",
		"Olympiacos Piraeus B",
		"Panargiakos APO",
		"Panionios Athens",
	};

	for (string s : d2n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = gre_second;
		club->ClubReserveDivision = gre_second_n;
	}
	for (string s : d2s_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = gre_second;
		club->ClubReserveDivision = gre_second_s;
	}
}