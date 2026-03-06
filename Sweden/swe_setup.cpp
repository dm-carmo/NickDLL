#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "swe_premier.h"
#include "swe_first.h"
#include "swe_second.h"
#include "swe_third.h"
#include "swe_cup.h"

static DWORD(__thiscall* swe_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x88CBB0);

DWORD swe_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = March;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 30;
	nation_data->contract_end_month = November;
	nation_data->contract_end_year = start_year;
	nation_data->f70 = 6;
	BYTE selected = nation_data->nation->NationLeagueSelected;
	if ((selected & 4) == 0) {
		nation_data->num_of_comps = 4;
	}
	else {
		nation_data->num_of_comps = 5;
	}
	DWORD* nation_comps = (DWORD*)sub_944E46_malloc(nation_data->num_of_comps * 4);
	nation_data->comps_list = (DWORD)nation_comps;
	// start calling each league's functions
	BYTE i = 0;
	// Allsvenskan
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	swe_premier_init(pMem, start_year, get_comp(SWE_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Superettan
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	swe_first_init(pMem, start_year, get_comp(SWE_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// Ettan
	pMem = (BYTE*)sub_944CF1_operator_new(0x106);
	swe_second_init(pMem, start_year, get_comp(SWE_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// Division 2
		pMem = (BYTE*)sub_944CF1_operator_new(0x11E);
		swe_third_init(pMem, start_year, get_comp(SWE_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	swe_cup_init(pMem, *current_year, get_comp(SWE_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_swe_nation()
{
	WriteDWORD(0x668D74 + 6, (DWORD)&swe_setup_c);
	setup_swe_premier();
	setup_swe_first();
	setup_swe_second();
	setup_swe_third();
	setup_swe_cup();

	WriteNOP(0x88ccb1, 7);
}

void sweden_restructure() {
	cm3_club_comps* swe_premier = get_comp(SWE_PREMIER_9CF());
	cm3_club_comps* swe_first = get_comp(SWE_FIRST_9CF());
	cm3_club_comps* swe_second = get_comp(SWE_SECOND_9CF());
	swe_second->ClubCompReputation = 4;
	cm3_club_comps* swe_second_n = get_comp(SWE_SECOND_NORTH_9CF());
	swe_second_n->ClubCompReputation = 4;
	cm3_club_comps* swe_second_s = get_comp(SWE_SECOND_SOUTH_9CF());
	cm3_club_comps* swe_third = get_comp(SWE_THIRD_9CF());
	swe_third->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ng = get_comp(SWE_THIRD_NORTH_GOTALAND_9CF());
	swe_third_ng->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ns = get_comp(SWE_THIRD_NORTH_SVEALAND_9CF());
	swe_third_ns->ClubCompReputation = 2;
	cm3_club_comps* swe_third_n = get_comp(SWE_THIRD_NORRLAND_9CF());
	swe_third_n->ClubCompReputation = 2;
	cm3_club_comps* swe_third_sg = get_comp(SWE_THIRD_SOUTH_GOTALAND_9CF());
	swe_third_sg->ClubCompReputation = 2;
	cm3_club_comps* swe_third_ss = get_comp(SWE_THIRD_SOUTH_SVEALAND_9CF());
	swe_third_ss->ClubCompReputation = 2;
	cm3_club_comps* swe_third_wg = get_comp(SWE_THIRD_WEST_GOTALAND_9CF());
	swe_third_wg->ClubCompReputation = 2;
	cm3_club_comps* swe_lower = get_comp(SWE_LOWER_9CF());

	vector<string> move_to_lower = {
		"Swedish Division 2 East Svealand",
		"Swedish Division 2 Middle Gotaland",
		"Swedish Division 2 Middle Norrland",
		"Swedish Division 2 North Norrland",
		"Swedish Division 2 North Svealand",
		"Swedish Division 2 Northeast Gotaland",
		"Swedish Division 2 Northwest Gotaland",
		"Swedish Division 2 South Gotaland",
		"Swedish Division 2 South Norrland",
		"Swedish Division 2 Southeast Gotaland",
		"Swedish Division 2 Southwest Gotaland",
		"Swedish Division 2 West Svealand",
		"Swedish Ettan East Gotaland",
		"Swedish Ettan East Svealand",
		"Swedish Ettan North",
		"Swedish Ettan South Gotaland",
		"Swedish Ettan West Gotaland",
		"Swedish Ettan West Svealand",
	};
	for (string s : move_to_lower) {
		cm3_club_comps* comp = find_club_comp(s.c_str());
		if (comp)
		{
			vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(comp->ClubCompID);
			for (cm3_clubs* c : lower_clubs) {
				c->ClubDivision = swe_lower;
			}
		}
	}

	cm3_nations* sweden = get_country(NATION_SWEDEN_9CF());
	cm3_clubs* tidaholms_goif = find_club("Tidaholms GoIF");
	if (tidaholms_goif) {
		tidaholms_goif->ClubNation = sweden;
	}

	vector<string> premier_clubs = {
		"Degerfors IF",
		"Östers IF",
	};
	vector<string> first_clubs = {
		"Trelleborgs FF",
		"Utsiktens BK",
	};
	vector<string> second_n_clubs = {
		"Nordic United FC",
		"Hammarby TFF",
		"Vasalunds IF",
		"FC Stockholm",
		"IF Karlstad Fotboll",
		"Assyriska FF",
		"FC Arlanda",
		"AFC Eskilstuna",
		"Karlbergs BK",
		"Sollentuna FK",
		"Enköpings SK",
		"IFK Stocksund",
		"Gefle IF",
		"IFK Haninge",
		"Örebro Syrianska IF",
		"Team TG FF",
	};
	vector<string> second_s_clubs = {
		"Ljungskile SK",
		"Norrby IF",
		"Jönköpings Södra IF",
		"Hässleholms IF",
		"Lunds BK",
		"Ariana FC",
		"FC Trollhättan",
		"BK Olympic",
		"Ängelholms FF",
		"Eskilsminne IF",
		"FC Rosengård",
		"Skövde AIK",
		"Oskarshamns AIK",
		"Torslanda IK",
		"Husqvarna FF",
		"IFK Skövde",
	};
	vector<string> third_ng_clubs = {
		"FBK Karlstad",
		"Motala AIF",
		"Lidköpings FK",
		"Ahlafors IF",
		"IK Kongahälla",
		"Grebbestads IF",
		"Vänersborgs IF",
		"Vänersborgs FK",
		"IK Tord",
		"IFK Kumla",
		"Tidaholms GoIF",
		"IK Gauthiod", // missing Herrestads AIF
		"Säffle FF", // missing Skara FC
		"Stenungsunds IF", // missing IF Haga
	};
	vector<string> third_ns_clubs = {
		"FC Järfälla",
		"Viggbyholms IK",
		"Nacka FC",
		"IK Franke",
		"Täby FK",
		"Kungsängens IF",
		"Skiljebo SK",
		"Korsnäs IF",
		"FC Gute",
		"Ytterhogdals IK",
		"Österåker United FK",
		"Sandvikens AIK", // missing Falu BS
		"Hudiksvalls FF", // missing Bollstanäs SK
		"Dalkurd FF", // missing Sunnersta AIF
	};
	vector<string> third_n_clubs = {
		"Piteå IF",
		"Skellefteå FF",
		"IFK Luleå",
		"Bergnäsets AIK",
		"Bodens BK",
		"Kiruna FF",
		"IFK Östersund",
		"Umeå FC Akademi",
		"Gottne IF",
		"Friska Viljor FC",
		"Lucksta IF",
		"Täfteå IK",
		"Frösö IF", // missing Boden City
		"Älgarna-Härnösand IF", // missing Kubikenborgs IF
	};
	vector<string> third_sg_clubs = {
		"Kristianstad FC",
		"FK Karlskrona",
		"IFK Trelleborg",
		"Sölvesborgs GoIF",
		"Växjö Norra IF",
		"Räppe GoIF",
		"Torns IF",
		"Nosaby IF",
		"IFK Karlshamn",
		"Österlen FF",
		"Högaborgs BK",
		"IFK Hässleholm",
		"FBK Balkan",
		"Lödde IF", // missing Linero IF
	};
	vector<string> third_ss_clubs = {
		"Åtvidabergs FF",
		"Rågsveds IF",
		"IF Sylvia",
		"IK Sleipner",
		"FOC Farsta",
		"Enskede IK",
		"Smedby AIS",
		"Nyköpings BIS",
		"BK Forward",
		"Syrianska FC",
		"IF Eker Örebro",
		"Huddinge IF",
		"Arameisk-Syrianska IF",
		"Syrianska Eskilstuna IF",
	};
	vector<string> third_wg_clubs = {
		"Laholms FK",
		"Tvååkers IF",
		"Åstorps FF",
		"Onsala BK",
		"Västra Frölunda IF",
		"Lindome GIF",
		"Qviding FIF",
		"BK Astrio",
		"Landvetter IS",
		"Hestrafors IF",
		"Varbergs GIF",
		"Sävedalens IF", // missing Jonsereds IF
		"Öckerö IF", // missing IF Böljan
		"Hittarps IK", // missing Bergdalens IK
	};

	for (string s : premier_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_premier;
	}
	for (string s : first_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_first;
	}
	for (string s : second_n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_second;
		club->ClubReserveDivision = swe_second_n;
	}
	for (string s : second_s_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_second;
		club->ClubReserveDivision = swe_second_s;
	}
	for (string s : third_ng_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ng;
	}
	for (string s : third_ns_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ns;
	}
	for (string s : third_n_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_n;
	}
	for (string s : third_sg_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_sg;
	}
	for (string s : third_ss_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_ss;
	}
	for (string s : third_wg_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = swe_third;
		club->ClubReserveDivision = swe_third_wg;
	}
}