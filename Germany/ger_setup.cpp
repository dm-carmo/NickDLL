#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include "ger_first.h"
#include "ger_second.h"
#include "ger_third.h"
#include "ger_regional.h"
#include "ger_cup.h"
#include "ger_super.h"
#include "ger_awards.h"
#include <Helpers\9cf_constants.h>

static DWORD(__thiscall* ger_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x5D8C20);
static DWORD(__thiscall* ger_super_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x92B4B0);

DWORD ger_setup_c(playable_nation_data* nation_data) {
	
	nation_data->contract_start_day = 21;
	nation_data->contract_start_month = July;
	nation_data->contract_start_year = *current_year;
	nation_data->f55 = 5;
	
	nation_data->contract_end_day = 31;
	nation_data->contract_end_month = May;
	nation_data->contract_end_year = *current_year + 1;
	nation_data->f70 = 5;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 5;
	}
	else {
		nation_data->num_of_comps = 6;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	
	BYTE i = 0;
	// Bundesliga
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_first_init(pMem, *current_year, get_comp(GER_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2. Bundesliga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_second_init(pMem, *current_year, get_comp(GER_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 3. Liga
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	ger_third_init(pMem, *current_year, get_comp(GER_THIRD_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Regionalliga
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		ger_regional_init(pMem, *current_year, get_comp(GER_REGIONAL_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_cup_setup(pMem, *current_year, get_comp(GER_CUP_9CF()));
	get_comp(GER_CUP_9CF())->ClubCompBackgroundColour = get_colour(COLOUR_CYAN_2_9CF());
	get_comp(GER_CUP_9CF())->ClubCompForegroundColour = get_colour(COLOUR_WHITE_9CF());
	nation_comps[i++] = (DWORD)pMem;
	// Supercup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	ger_super_setup(pMem, *current_year, get_comp(GER_SUPER_CUP_9CF()));
	get_comp(GER_SUPER_CUP_9CF())->ClubCompBackgroundColour = 0;
	get_comp(GER_SUPER_CUP_9CF())->ClubCompForegroundColour = 0;
	nation_comps[i++] = (DWORD)pMem;

	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 20, June, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = *current_year;
	nation_data->f29 = 1;
	nation_data->super_cup = get_comp(GER_SUPER_CUP_9CF());
	return 1;
}

void setup_ger_nation()
{
	WriteDWORD(0x66807B + 6, (DWORD)&ger_setup_c);
	setup_ger_first();
	setup_ger_second();
	setup_ger_third();
	setup_ger_regional();
	setup_ger_cup();
	setup_ger_super();
	setup_ger_awards();

	WriteNOP(0x5d8cf2, 7);
}

void germany_restructure() {
	cm3_club_comps* ger_regional = get_comp(GER_REGIONAL_9CF());
	ger_regional->ClubCompNation = get_country(NATION_GERMANY_9CF());
	ger_regional->ClubCompContinent = get_continent(EUROPE_9CF());
	ger_regional->ClubCompReputation = 4;

	cm3_club_comps* ger_third = get_comp(GER_THIRD_9CF());
	cm3_club_comps* ger_reg_n = get_comp(GER_REGIONAL_NORTH_9CF());
	cm3_club_comps* ger_reg_ne = get_comp(GER_REGIONAL_NORTHEAST_9CF());
	cm3_club_comps* ger_reg_w = get_comp(GER_REGIONAL_WEST_9CF());
	cm3_club_comps* ger_reg_sw = get_comp(GER_REGIONAL_SOUTHWEST_9CF());
	cm3_club_comps* ger_reg_bayern = get_comp(GER_REGIONAL_BAYERN_9CF());
	ger_reg_bayern->ClubCompNation = get_country(NATION_GERMANY_9CF());
	ger_reg_bayern->ClubCompContinent = get_continent(EUROPE_9CF());
	ger_reg_bayern->ClubCompReputation = 4;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<cm3_clubs*> club_list = find_clubs_of_comp(GER_REGIONAL_NORTH_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}
	club_list = find_clubs_of_comp(GER_REGIONAL_SOUTHWEST_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}
	club_list = find_clubs_of_comp(A_LOWER_B_9CF(), NATION_GERMANY_9CF());
	for (cm3_clubs* c : club_list) {
		c->ClubDivision = a_lower;
	}

	vector<string> liga3_clubs = {
		"Alemannia Aachen",
		"FC Erzgebirge Aue",
		"FC Energie Cottbus",
		"MSV Duisburg",
		"Rot-Weiss Essen",
		"TSV Havelse",
		"TSG 1899 Hoffenheim II",
		"FC Ingolstadt 04",
		"FC Viktoria Köln",
		"SV Waldhof Mannheim",
		"TSV 1860 München",
		"VfL Osnabrück",
		"SSV Jahn Regensburg",
		"FC Hansa Rostock",
		"1.FC Saarbrücken",
		"1.FC Schweinfurt 05",
		"VfB Stuttgart Amateure",
		"SSV Ulm 1846",
		"SC Verl",
		"SV Wehen Wiesbaden"
	};
	vector<string> reg_n_clubs = {
		"SV Meppen",
		"VfB Oldenburg",
		"SV Drochtersen/Assel",
		"SSV Jeddeloh",
		"1.FC Phönix Lübeck",
		"Hamburger SV Amateure",
		"Hannover 96 Amateure",
		"Bremer SV",
		"SC Weiche Flensburg 08",
		"VfB Lübeck",
		"SV Werder Bremen Amateure",
		"Kickers Emden",
		"HSC Hannover",
		//"FSV Schöningen",
		"FC Teutonia 05 Ottensen", //replaces above
		"Eintracht Norderstedt",
		"Blau-Weiß Lohne",
		"Altona 93",
		"FC St. Pauli Amateure",
	};
	vector<string> reg_ne_clubs = {
		"1. FC Lokomotive Leipzig",
		"FC Carl Zeiss Jena",
		"Rot-Weiß Erfurt",
		"FSV Zwickau",
		"VSG Altglienicke",
		"Hallescher FC",
		//"1.FC Magdeburg II",
		"Eintracht Hohkeppel", //replaces above
		//"BFC Preussen",
		"FC Gießen", //replaces above
		"FSV 63 Luckenwalde",
		"Chemnitzer FC",
		"Hertha BSC Amateure",
		"SV Babelsberg 03",
		"ZFC Meuselwitz",
		"Greifswalder FC",
		"BFC Dynamo",
		"BSG Chemie Leipzig",
		"FC Eilenburg",
		"FC Hertha 03 Zehlendorf",
	};
	vector<string> reg_w_clubs = {
		"SC Fortuna Köln",
		"FC Gütersloh",
		"Rot-Weiß Oberhausen",
		"FC Schalke 04 Amateure",
		"Sportfreunde Siegen",
		"Borussia Dortmund Amateure",
		"Bor. M'gladbach Amateure",
		"1.FC Köln Amateure",
		"Sportfreunde Lotte",
		"1.FC Bocholt",
		"Bonner SC",
		"SC Paderborn 07 Reserves",
		"Fortuna Düsseldorf II",
		"SV Rödinghausen",
		"Wuppertaler SV",
		"VfL Bochum Amateure",
		"SC Wiedenbrück",
		"SSVg Velbert 02",
	};
	vector<string> reg_sw_clubs = {
		"SGV Freiberg",
		"SG Sonnenhof Großaspach",
		"FSV Mainz 05 II",
		"FSV Frankfurt",
		"SV Sandhausen",
		"FC 08 Homburg",
		"TSV Steinbach Haiger",
		"FC-Astoria Walldorf",
		"Stuttgarter Kickers",
		"KSV Hessen Kassel",
		"SV Eintracht Trier 05",
		"Kickers Offenbach",
		"SG Barockstadt Fulda-Lehnerz",
		"SC Freiburg Amateure",
		"FC Bayern Alzenau",
		"TSG Balingen",
		"Bahlinger SC",
		"TSV Schott Mainz",
	};
	vector<string> reg_bay_clubs = {
		"1.FC Nürnberg Amateure",
		"DJK Vilzing",
		"FC Augsburg II",
		"FC Bayern München Amateure",
		"FC Memmingen",
		"FV Illertissen",
		"Schwaben Augsburg",
		"SpVgg Ansbach",
		"SpVgg Bayreuth",
		"SpVgg Greuther Fürth II",
		"SpVgg Hankofen-Hailing",
		"SpVgg Unterhaching",
		"SV Viktoria Aschaffenburg",
		"SV Wacker Burghausen",
		"TSV Aubstadt",
		"TSV Buchbach",
		"VfB Eichstätt",
		"Würzburger Kickers",
	};

	for (string s : liga3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_third;
	}
	for (string s : reg_n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_regional;
		club->ClubReserveDivision = ger_reg_n;
	}
	for (string s : reg_ne_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_regional;
		club->ClubReserveDivision = ger_reg_ne;
	}
	for (string s : reg_w_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_regional;
		club->ClubReserveDivision = ger_reg_w;
	}
	for (string s : reg_sw_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_regional;
		club->ClubReserveDivision = ger_reg_sw;
	}
	for (string s : reg_bay_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = ger_regional;
		club->ClubReserveDivision = ger_reg_bayern;
	}

	vector<string> extinct_ger = {
		"VfL Wolfsburg Amateure",
		"MSV Duisburg Amateure",
		"Bayer Leverkusen (A)",
		"FC Energie Cottbus II",
		"SG Hoechst II",
		"FC Carl Zeiss Jena II",
		"RW Oberhausen Amateure",
		"1.FC Saarbrücken II",
		"Stuttgarter Kickers II",
		"SSV Ulm 1846 II",
		"SG Wattenscheid 09 II",
	};
	for (string s : extinct_ger) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubNation = 0;
	}
}