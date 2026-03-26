#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "bel_first.h"
#include "bel_second.h"
#include "bel_third_vv.h"
#include "bel_third_ac.h"
#include "bel_fourth_vv.h"
#include "bel_fourth_ac.h"
#include "bel_cup.h"
#include "bel_super.h"
//#include "bel_awards.h"

static DWORD(__thiscall* bel_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x41d050);
static DWORD(__thiscall* bel_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x420ef0);

DWORD bel_setup_c(playable_nation_data* nation_data) {

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
		nation_data->num_of_comps = 6;
	}
	else {
		nation_data->num_of_comps = 8;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;

	BYTE i = 0;

	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bel_first_init(pMem, *current_year, get_comp(BEL_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bel_second_init(pMem, *current_year, get_comp(BEL_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bel_third_vv_init(pMem, *current_year, get_comp(BEL_THIRD_VV_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	bel_third_ac_init(pMem, *current_year, get_comp(BEL_THIRD_ACFF_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	if ((selected & 4) != 0) {
		pMem = (BYTE*)sub_944CF1_operator_new(0x104);
		bel_fourth_vv_init(pMem, *current_year, get_comp(BEL_FOURTH_VV_9CF()));
		nation_comps[i++] = (DWORD)pMem;

		pMem = (BYTE*)sub_944CF1_operator_new(0xF2);
		bel_fourth_ac_init(pMem, *current_year, get_comp(BEL_FOURTH_ACFF_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bel_cup_setup(pMem, *current_year, get_comp(BEL_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	bel_super_setup(pMem, *current_year, get_comp(BEL_SUPER_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(BEL_SUPER_CUP_9CF());
	return 1;
}

void setup_bel_nation() {
	WriteDWORD(0x6679f9 + 6, (DWORD)&bel_setup_c);
	setup_bel_first();
	setup_bel_second();
	setup_bel_third_vv();
	setup_bel_third_ac();
	setup_bel_fourth_vv();
	setup_bel_fourth_ac();
	setup_bel_cup();
	setup_bel_super();
	//setup_bel_awards();
}

void belgium_restructure() {
	cm3_club_comps* bel_second = get_comp(BEL_SECOND_9CF());
	cm3_club_comps* bel_third = get_comp(BEL_THIRD_9CF());
	cm3_club_comps* bel_third_vv = get_comp(BEL_THIRD_VV_9CF());
	cm3_club_comps* bel_third_acff = get_comp(BEL_THIRD_ACFF_9CF());
	cm3_club_comps* bel_fourth_vv = get_comp(BEL_FOURTH_VV_9CF());
	cm3_club_comps* bel_fourth_vv_a = get_comp(BEL_FOURTH_VV_A_9CF());
	cm3_club_comps* bel_fourth_vv_b = get_comp(BEL_FOURTH_VV_B_9CF());
	cm3_club_comps* bel_fourth_acff = get_comp(BEL_FOURTH_ACFF_9CF());
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<DWORD> move_to_lower = {
		BEL_THIRD_VV_9CF(),
		BEL_THIRD_ACFF_9CF(),
		BEL_FOURTH_VV_9CF(),
		BEL_FOURTH_VV_A_9CF(),
		BEL_FOURTH_VV_B_9CF(),
		BEL_FOURTH_ACFF_9CF(),
	};
	for (DWORD id : move_to_lower) {
		vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(id);
		for (cm3_clubs* c : lower_clubs) {
			c->ClubDivision = a_lower;
		}
	}
	cm3_clubs* bel_reserve = find_club("Beerschot VA U21");
	if (bel_reserve) {
		bel_reserve->ClubDivision = a_lower;
	}

	vector<string> d2_clubs = {
		"Beerschot VA",
		"KV Kortrijk",
	};
	vector<string> d3vv_clubs = {
		"Cercle Brugge B",
		"Oud-Heverlee Leuven U23",
		"Sporting Hasselt",
		"K. Lyra-Lierse",
		"RFC Knokke",
		"KVK Tienen",
		"KFC Dessel Sport",
		"Hoogstraten VV",
		"KVK Ninove",
		"KFC Merelbeke",
		"KVV Thes Sport",
		"Diegem Sport",
		"KVV Zelzate",
		"KFC Houtvenne",
		"Belisia Bilzen",
		"SK Roeselare",
	};
	vector<string> d3ac_clubs = {
		"Royal Union Tubize-Braine",
		"Renaissance AEC Mons",
		"Royal Excelsior Virton",
		"Union Rochefortoise",
		"RRC Stockay Saint-Georges S/M",
		"RSC Charleroi B",
		"Union Saint-Gilloise U23",
		"Union Namur",
		"Standard de Liège 16 FC",
		"Crossing Schaerbeek",
		"RFC Meux",
		"RSC Habay-La-Neuve",
	};
	vector<string> d4vv_a_clubs = {
		"KRC Gent",
		"KV Mechelen U23",
		"KSV Oudenaarde",
		"RFC Wetteren",
		"KVK Westhoek",
		"KFC VW Hamme",
		"KM Torhout",
		"RFC Mandel United",
		"Racing Club Harelbeke",
		"KV Diksmuide Oostende",
		"KFC Sparta Petegem",
		"KFC Hoger Op Kalken",
		"Zulte-Waregem B",
		"KSV Oostkamp",
		"FC Lebbeke",
		"FC Gullegem",
	};
	vector<string> d4vv_b_clubs = {
		"Royal Antwerp FC B",
		"KRC Mechelen",
		"Berchem Sport",
		"Royal Cappellen FC",
		"KSK Tongeren",
		"STVV Youth",
		"Bocholt VV",
		"KFC Nijlen",
		"FC Rupel Boom",
		"KVK Wellen",
		"KSK Heist",
		"KVV Berg en Dal",
		"SK Londerzeel",
		"Sportief Rotselaar",
		"Eendracht Termien",
		"RC Hades",
	};
	vector<string> d4ac_clubs = {
		"RFC Tournai",
		"Stade Verviétois",
		"RCS Braine",
		"Union Hutoise",
		"RSC Tilffois",
		"RFC Raeren-Eynatten",
		"RSD Jette",
		"RFCU Kelmis",
		"Royal Aywaille",
		"RE Acren-Lessines",
		"RUS Binche",
		"Sporting Bruxelles",
		"CS Onhaye",
		"FC Ganshoren",
		"CS Entité Manageoise",
		"CS Pays Vert Ostiches Ath",
		"FC Flénu",
		"FC United Richelle",
	};

	for (string s : d2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_second;
	}
	for (string s : d3vv_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_third_vv;
	}
	for (string s : d3ac_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_third_acff;
	}
	for (string s : d4vv_a_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_fourth_vv;
		club->ClubReserveDivision = bel_fourth_vv_a;
	}
	for (string s : d4vv_b_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_fourth_vv;
		club->ClubReserveDivision = bel_fourth_vv_b;
	}
	for (string s : d4ac_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = bel_fourth_acff;
	}
}