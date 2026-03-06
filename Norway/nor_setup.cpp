#include <windows.h>
#include "Structures\CMHeader.h"
#include "Helpers\generic_functions.h"
#include <Helpers\9cf_constants.h>
#include "nor_premier.h"
#include "nor_first.h"
#include "nor_second.h"
#include "nor_third.h"
#include "nor_cup.h"
#include "nor_awards.h"

static DWORD(__thiscall* nor_cup_setup)(BYTE* _this, WORD year, cm3_club_comps* comp) =
(DWORD(__thiscall*)(BYTE * _this, WORD year, cm3_club_comps * comp))(0x78F020);

DWORD nor_setup_c(playable_nation_data* nation_data) {
	BYTE* start_date = new BYTE[8];
	sub_54C770((BYTE*)dd6ec8, start_date, 4);
	WORD start_year = *(WORD*)(start_date + 2);
	// contract start date?
	nation_data->contract_start_day = 1;
	nation_data->contract_start_month = March;
	nation_data->contract_start_year = start_year;
	nation_data->f55 = 6;
	// contract end date?
	nation_data->contract_end_day = 16;
	nation_data->contract_end_month = December;
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
	// Eliteserien
	BYTE* pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_premier_init(pMem, start_year, get_comp(NOR_PREMIER_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 1. divisjon
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_first_init(pMem, start_year, get_comp(NOR_FIRST_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	// 2. divisjon
	pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
	nor_second_init(pMem, start_year, get_comp(NOR_SECOND_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	if ((selected & 4) != 0) {
		// 3. divisjon
		pMem = (BYTE*)sub_944CF1_operator_new(0xEE);
		nor_third_init(pMem, start_year, get_comp(NOR_THIRD_9CF()));
		nation_comps[i++] = (DWORD)pMem;
	}
	// Cup
	pMem = (BYTE*)sub_944CF1_operator_new(0xB2);
	nor_cup_setup(pMem, *current_year, get_comp(NOR_CUP_9CF()));
	nation_comps[i++] = (DWORD)pMem;
	BYTE* cm_date = new BYTE[8];
	convert_to_cm_date(cm_date, 1, January, 2025, -1);
	nation_data->update_day = *(WORD*)cm_date;
	nation_data->update_year = start_year;
	nation_data->f29 = 1;
	nation_data->super_cup = 0;
	return 1;
}

void setup_nor_nation()
{
	WriteDWORD(0x66873E+ 6, (DWORD)&nor_setup_c);
	setup_nor_premier();
	setup_nor_first();
	setup_nor_second();
	setup_nor_third();
	setup_nor_cup();
	setup_nor_awards();

	WriteNOP(0x78f0f2, 7);
}

void norway_restructure() {
	cm3_nations* norway = get_country(NATION_NORWAY_9CF());
	cm3_club_comps* nor_premier = get_comp(NOR_PREMIER_9CF());
	cm3_club_comps* nor_first = get_comp(NOR_FIRST_9CF());
	cm3_club_comps* nor_second = get_comp(NOR_SECOND_9CF());
	nor_second->ClubCompNation = norway;
	nor_second->ClubCompReputation = 4;
	cm3_club_comps* nor_second_1 = get_comp(NOR_SECOND_G1_9CF());
	cm3_club_comps* nor_second_2 = get_comp(NOR_SECOND_G2_9CF());
	cm3_club_comps* nor_third = get_comp(NOR_THIRD_9CF());
	nor_third->ClubCompReputation = 2;
	cm3_club_comps* nor_third_1 = get_comp(NOR_THIRD_G1_9CF());
	nor_third_1->ClubCompReputation = 2;
	cm3_club_comps* nor_third_2 = get_comp(NOR_THIRD_G2_9CF());
	nor_third_2->ClubCompReputation = 2;
	cm3_club_comps* nor_third_3 = get_comp(NOR_THIRD_G3_9CF());
	nor_third_3->ClubCompReputation = 2;
	cm3_club_comps* nor_third_4 = get_comp(NOR_THIRD_G4_9CF());
	nor_third_4->ClubCompReputation = 2;
	cm3_club_comps* nor_third_5 = get_comp(NOR_THIRD_G5_9CF());
	nor_third_5->ClubCompReputation = 2;
	cm3_club_comps* nor_third_6 = get_comp(NOR_THIRD_G6_9CF());
	nor_third_6->ClubCompReputation = 2;
	cm3_club_comps* a_lower = get_comp(A_LOWER_9CF());

	vector<string> move_to_lower = {
		"Norwegian 2. Divisjon",
		"Norwegian 2. Divisjon Group 1",
		"Norwegian 2. Divisjon Group 2",
		"Norwegian 3. Divisjon",
		"Norwegian 3. Divisjon Group 1",
		"Norwegian 3. Divisjon Group 2",
		"Norwegian 3. Divisjon Group 3",
		"Norwegian 3. Divisjon Group 4",
		"Norwegian 3. Divisjon Group 5",
		"Norwegian 3. Divisjon Group 6",
	};
	for (string s : move_to_lower) {
		cm3_club_comps* comp = find_club_comp(s.c_str());
		if (comp)
		{
			vector<cm3_clubs*> lower_clubs = find_clubs_of_comp(comp->ClubCompID);
			for (cm3_clubs* c : lower_clubs) {
				c->ClubDivision = a_lower;
			}
		}
	}

	cm3_clubs* kvik_trondheim = find_club("FK Kvik");
	if (kvik_trondheim) {
		kvik_trondheim->ClubNation = norway;
	}

	vector<string> premier_clubs = {
		"FK Haugesund",
		"Strømsgodset IF",
	};
	vector<string> first_clubs = {
		"Skeid Oslo",
		"IL Hødd",
	};
	vector<string> second_1_clubs = {
		"Arendal Fotball",
		"SK Brann 2",
		"Brattvåg IL",
		"FK Eik Tønsberg 871",
		"Flekkerøy IF",
		"FK Jerv",
		"Lysekloster IL",
		"Notodden FK",
		"Pors Fotball",
		"Sandnes Ulf",
		"IL Sandviken",
		"Sotra SK",
		"SK Træff",
		"SK Vard Haugesund",
	};
	vector<string> second_2_clubs = {
		"Alta IF",
		"Asker Fotball",
		"Eidsvold Turn Fotball",
		"Follo FK",
		"Grorud IL",
		"Hønefoss BK",
		"Kjelsås IL",
		"Levanger FK",
		"Rana FK",
		"Stjørdals-Blink Fotball",
		"Strindheim TF",
		"Strømmen IF",
		"Tromsdalen UIL",
		"Ullensaker/Kisa IL",
	};
	vector<string> third_1_clubs = {
		"Junkeren IK",
		"Frigg Oslo FK",
		"Bærum SK",
		"Tromsø IL II",
		"Ullern IF",
		"IF Fløya",
		"Harstad IL",
		"Skjervøy IK",
		"Funnefoss/Vormsund",
		"Sortland IL",
		"Frøya", // Gamle Oslo
		"Årdal FK", // IL Ulfstind
		"Funnefoss/Vormsund IL", // KFUM-Kameratene Oslo 2
		"Florø SK", // Alta IF
	};
	vector<string> third_2_clubs = {
		"SK Trygg/Lade",
		"Melhus IL",
		"Volda TI",
		"Spjelkavik",
		"Rosenborg BK II",
		"Aalesunds FK II",
		"Nardo FK",
		"Byåsen TF",
		"Molde FK II",
		"Ranheim 2",
		"FK Kvik",
		"Kristiansund BK 2",
		"Surnadal IL",
		"Tiller IL",
	};
	vector<string> third_3_clubs = {
		"Lørenskog IF",
		"Elverum Fotball",
		"SK Gjøvik-Lyn",
		"Lillehammer FK",
		"Nordstrand IF",
		"Skjetten SK",
		"Kongsvinger IL II",
		"Lilleström SK 2",
		"Skedsmo",
		"Strømsgodset IF II",
		"Hamarkameratene 2",
		"Åssiden IL",
		"Ullensaker/Kisa IL 2",
		"Skeid Oslo II", // Bjørkelangen SF
	};
	vector<string> third_4_clubs = {
		"Idrettslaget Bjarg",
		"Førde IL",
		"Fana IL",
		"Os Turn Fotball",
		"FK Fyllingsdalen",
		"Sandefjord Fotball 2",
		"Vålerenga Fotball II",
		"Lyngbø",
		"Mjøndalen IF 2", // IL Gneist
		"Verdal IL", // Askøy FK
		"Orkla FK", // Åsane Fotball 2
		"Mosjøen IL", // Lyn 1896 FK 2
		"Mandalskameratene", // Fjøra FK
		"IK Start 2", // Loddefjord IL
	};
	vector<string> third_5_clubs = {
		"FK Vidar",
		"Vindbjart FK",
		"SK Djerv 1919",
		"Viking FK II",
		"Madla IL",
		"Brodd IL",
		"Stord T&IL",
		"Staal Jørpeland IL",
		"FK Haugesund 2",
		"Sola FK",
		"Sandnes Ulf 2",
		"Gjellerasen IF", // IK Våg
		"IL Hødd 2", // Hinna Fotball
		"FK Vigør", // Torvastad IL
	};
	vector<string> third_6_clubs = {
		"Kvik Halden",
		"IF Fram",
		"FK Ørn Horten",
		"Lokomotiv Oslo",
		"Grei SF",
		"Oppsal IF Fotball",
		"Odds BK II",
		"Stabaek IF II",
		"Drøbak-Frogn IL",
		"Sarpsborg 08 2",
		"IF Ready Fotball",
		"Fredrikstad FK 2",
		"Flint Fotball",
		"Pors Fotball II",
	};

	for (string s : premier_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_premier;
	}
	for (string s : first_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_first;
	}
	for (string s : second_1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_second;
		club->ClubReserveDivision = nor_second_1;
	}
	for (string s : second_2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_second;
		club->ClubReserveDivision = nor_second_2;
	}
	for (string s : third_1_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_1;
	}
	for (string s : third_2_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_2;
	}
	for (string s : third_3_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_3;
	}
	for (string s : third_4_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_4;
	}
	for (string s : third_5_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_5;
	}
	for (string s : third_6_clubs) {
		cm3_clubs* club = find_club(s.c_str());
		if (!club) {
			create_message_box("Error", (string("Could not find club: ") + s).c_str(), false);
			continue;
		}
		club->ClubDivision = nor_third;
		club->ClubReserveDivision = nor_third_6;
	}
}